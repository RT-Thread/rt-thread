import subprocess
import threading
import time
import logging
import sys
import os
import shutil
import re
import multiprocessing
import yaml

def add_summary(text):
    """
    add summary to github action.
    """
    os.system(f'echo "{text}" >> $GITHUB_STEP_SUMMARY ;')


def run_cmd(cmd, output_info=True):
    """
    run command and return output and result.
    """
    print('\033[1;32m' + cmd + '\033[0m')

    output_str_list = []
    res = 0

    if output_info:
        res = os.system(cmd + " > output.txt 2>&1")
    else:
        res = os.system(cmd + " > /dev/null 2>output.txt")

    with open("output.txt", "r") as file:
        output_str_list = file.readlines()

    for line in output_str_list:
        print(line, end='')

    os.remove("output.txt")

    return output_str_list, res


def build_bsp(bsp, scons_args='',name='default'):
    """
    build bsp.

    cd {rtt_root}
    scons -C bsp/{bsp} --pyconfig-silent > /dev/null

    cd {rtt_root}/bsp/{bsp}
    pkgs --update > /dev/null
    pkgs --list

    cd {rtt_root}
    scons -C bsp/{bsp} -j{nproc} {scons_args}

    cd {rtt_root}/bsp/{bsp}
    scons -c > /dev/null
    rm -rf packages

    """
    success = True
    os.chdir(rtt_root)
    os.makedirs(f'{rtt_root}/output/bsp/{bsp}', exist_ok=True)
    if os.path.exists(f"{rtt_root}/bsp/{bsp}/Kconfig"):
        os.chdir(rtt_root)
        run_cmd(f'scons -C bsp/{bsp} --pyconfig-silent', output_info=False)

        os.chdir(f'{rtt_root}/bsp/{bsp}')
        run_cmd('pkgs --update-force', output_info=False)
        run_cmd('pkgs --list')

        nproc = multiprocessing.cpu_count()
        os.chdir(rtt_root)
        cmd = f'scons -C bsp/{bsp} -j{nproc} {scons_args}' # --debug=time for debug time
        __, res = run_cmd(cmd, output_info=True)

        if res != 0:
            success = False
        else:
            #拷贝当前的文件夹下面的所有以elf结尾的文件拷贝到rt-thread/output文件夹下
            import glob
            # 拷贝编译生成的文件到output目录,文件拓展为 elf,bin,hex
            for file_type in ['*.elf', '*.bin', '*.hex']:
                files = glob.glob(f'{rtt_root}/bsp/{bsp}/{file_type}')
                for file in files:
                    shutil.copy(file, f'{rtt_root}/output/bsp/{bsp}/{name.replace("/", "_")}.{file_type[2:]}')

    os.chdir(f'{rtt_root}/bsp/{bsp}')
    run_cmd('scons -c', output_info=False)

    return success


def append_file(source_file, destination_file):
    """
    append file to another file.
    """
    with open(source_file, 'r') as source:
        with open(destination_file, 'a') as destination:
            for line in source:
                destination.write(line)

def check_scons_args(file_path):
    args = []
    with open(file_path, 'r') as file:
        for line in file:
            match = re.search(r'#\s*scons:\s*(.*)', line)
            if match:
                args.append(match.group(1).strip())
    return ' '.join(args)

def get_details_and_dependencies(details, projects, seen=None):
    if seen is None:
        seen = set()
    detail_list = []
    if details is not None:
        for dep in details:
            if dep not in seen:
                dep_details=projects.get(dep)
                seen.add(dep)
                if dep_details is not None:
                    if dep_details.get('depends') is not None:
                        detail_temp=get_details_and_dependencies(dep_details.get('depends'), projects, seen)
                        for line in detail_temp:
                            detail_list.append(line)
                    if dep_details.get('kconfig') is not None:
                        for line in dep_details.get('kconfig'):
                            detail_list.append(line)
            else:
                print(f"::error::There are some problems with attachconfig depend: {dep}");
    return detail_list

def build_bsp_attachconfig(bsp, attach_file):
    """
    build bsp with attach config.

    cp bsp/{bsp}/.config bsp/{bsp}/.config.origin
    cat .ci/attachconfig/{attach_file} >> bsp/{bsp}/.config

    build_bsp()

    cp bsp/{bsp}/.config.origin bsp/{bsp}/.config
    rm bsp/{bsp}/.config.origin

    """
    config_file = os.path.join(rtt_root, 'bsp', bsp, '.config')
    config_bacakup = config_file+'.origin'
    shutil.copyfile(config_file, config_bacakup)

    attachconfig_dir = os.path.join(rtt_root, 'bsp', bsp, '.ci/attachconfig')
    attach_path = os.path.join(attachconfig_dir, attach_file)

    append_file(attach_path, config_file)

    scons_args = check_scons_args(attach_path)

    res = build_bsp(bsp, scons_args,name=attach_file)

    shutil.copyfile(config_bacakup, config_file)
    os.remove(config_bacakup)

    return res

# 配置日志
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s: %(message)s')
logger = logging.getLogger(__name__)

class QemuManager:
    def __init__(self, qemu_cmd, idle_timeout=5, checkresult=None):
        """
        初始化QEMU管理器
        :param qemu_cmd: QEMU启动命令
        :param idle_timeout: 日志空闲超时时间（秒）
        """
        self.qemu_cmd = qemu_cmd
        self.idle_timeout = idle_timeout
        self.qemu_process = None
        self.log_thread = None
        self.checkresult = checkresult
        self.last_log_time = time.time()
        self.logs = []
        self.running = False
        self.checkresult_found = False  # 标记是否找到checkresult
    def start_qemu(self):
        """启动QEMU进程"""
        logger.info("Starting QEMU...")
        self.qemu_process = subprocess.Popen(
            self.qemu_cmd,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            shell=True,
            bufsize=0,
            text=True
        )
        self.running = True
        logger.info("QEMU started successfully.")

    def log_monitor(self):
        """监控QEMU输出日志"""
        logger.info("Starting log monitor...")
        while self.running:
            line = self.qemu_process.stdout.readline()
            if line:
                line = line.strip()
                self.logs.append(line)
                self.last_log_time = time.time()  # 更新最后日志时间
                logger.info(f"QEMU Output: {line}")  # 实时打印日志
            # 检查是否包含checkresult
            if self.checkresult and self.checkresult in line:
                logger.info(f"Checkresult '{self.checkresult}' found in logs. Success...")
                self.checkresult_found = True
                #self.running = False  # 停止监控
                #break
            else:
                time.sleep(0.1)

    def send_command(self, command):
        """向QEMU发送命令"""
        if not self.running or not self.qemu_process:
            logger.error("QEMU is not running.")
            return False

        logger.info(f"Sending command: {command}")
        try:
            self.qemu_process.stdin.write(command + "\n")
            self.qemu_process.stdin.flush()
            return True
        except Exception as e:
            logger.error(f"Failed to send command: {e}")
            return False

    def stop_qemu(self):
        """停止QEMU进程"""
        if self.qemu_process:
            logger.info("Stopping QEMU...")
            self.running = False
            self.qemu_process.terminate()
            self.qemu_process.wait(timeout=5)
            logger.info("QEMU stopped.")



    def run(self,commands):
        """主运行逻辑"""
        try:
            # 启动QEMU
            self.start_qemu()

            # 启动日志监控线程
            self.log_thread = threading.Thread(target=self.log_monitor, daemon=True)
            self.log_thread.start()

            # 等待QEMU启动完成
            time.sleep(5)

            for cmd in commands:
                if not self.send_command(cmd):
                    break
                time.sleep(2)  # 命令之间间隔2秒

            # 监控日志输出，超时退出
            while self.running:
                idle_time = time.time() - self.last_log_time
                if idle_time > self.idle_timeout :
                    if not self.checkresult_found:
                        logger.info(f"No logs for {self.idle_timeout} seconds. ::error:: Exiting...")
                    else:
                        logger.info(f"No logs for {self.idle_timeout} seconds. ::check success:: Exiting...")
                    break
                time.sleep(0.1)

        except KeyboardInterrupt:
            logger.info("Script interrupted by user.")
        except Exception as e:
            logger.error(f"An error occurred: {e}")
        finally:
            self.stop_qemu()

def run_command(command, timeout=None):
    """运行命令并返回输出和结果"""
    print(command)
    result = subprocess.run(command, shell=True, capture_output=True, text=True, timeout=timeout)
    return result.stdout, result.returncode

def check_output(output, check_string):
    """检查输出中是否包含指定字符串"""
    flag = check_string in output
    if flag == True:
        print('find string ' + check_string)
    else:
        print('::error:: can not find string ' + check_string + output)

    return flag
if __name__ == "__main__":
    """
    build all bsp and attach config.

    1. build all bsp.
    2. build all bsp with attach config.

    """
    failed = 0
    count = 0
    ci_build_run_flag = False
    qemu_timeout_second = 50

    rtt_root = os.getcwd()
    srtt_bsp = os.getenv('SRTT_BSP').split(',')
    print(srtt_bsp)
    for bsp in srtt_bsp:
        count += 1
        print(f"::group::Compiling BSP: =={count}=== {bsp} ====")
        res = build_bsp(bsp)
        if not res:
            print(f"::error::build {bsp} failed")
            add_summary(f"- ❌ build {bsp} failed.")
            failed += 1
        else:
            add_summary(f'- ✅ build {bsp} success.')
        print("::endgroup::")

        yml_files_content = []
        directory = os.path.join(rtt_root, 'bsp', bsp, '.ci/attachconfig')
        if os.path.exists(directory):
            for root, dirs, files in os.walk(directory):
                for filename in files:
                    if filename.endswith('attachconfig.yml'):
                        file_path = os.path.join(root, filename)
                        if os.path.exists(file_path):
                            try:
                                with open(file_path, 'r') as file:
                                    content = yaml.safe_load(file)
                                    if content is None:
                                        continue
                                    yml_files_content.append(content)
                            except yaml.YAMLError as e:
                                print(f"::error::Error parsing YAML file: {e}")
                                continue
                            except Exception as e:
                                print(f"::error::Error reading file: {e}")
                                continue
        
        config_file = os.path.join(rtt_root, 'bsp', bsp, '.config')
        # 在使用 pre_build_commands 之前，确保它被定义
        pre_build_commands = None
        build_command = None
        post_build_command = None
        qemu_command = None
        build_check_result = None
        commands = None
        check_result = None
        for projects in yml_files_content:
            for name, details in projects.items():
                # 如果是bsp_board_info，读取基本的信息
                if(name == 'bsp_board_info'):
                    print(details)
                    pre_build_commands = details.get("pre_build").splitlines()
                    build_command = details.get("build_cmd").splitlines()
                    post_build_command = details.get("post_build").splitlines()
                    qemu_command = details.get("run_cmd")
                
                if details.get("kconfig") is not None:
                    if details.get("buildcheckresult")  is not None:
                        build_check_result = details.get("buildcheckresult")
                    if details.get("msh_cmd") is not None:
                        commands = details.get("msh_cmd").splitlines()
                    if details.get("checkresult") is not None:
                        check_result = details.get("checkresult")
                    if details.get("ci_build_run_flag") is not None:
                        ci_build_run_flag = details.get("ci_build_run_flag")
                    if details.get("pre_build") is not None:
                        pre_build_commands = details.get("pre_build").splitlines()
                    if details.get("build_cmd") is not None:
                        build_command = details.get("build_cmd").splitlines()
                    if details.get("post_build") is not None:
                        post_build_command = details.get("post_build").splitlines()
                    if details.get("run_cmd") is not None:
                        qemu_command = details.get("run_cmd")
                count += 1
                config_bacakup = config_file+'.origin'
                shutil.copyfile(config_file, config_bacakup)
                #加载yml中的配置放到.config文件
                with open(config_file, 'a') as destination:
                    if details.get("kconfig") is None:
                        #如果没有Kconfig，读取下一个配置
                        continue
                    if(projects.get(name) is not None):
                        # 获取Kconfig中所有的信息
                        detail_list=get_details_and_dependencies([name],projects)
                        for line in detail_list:
                            destination.write(line + '\n')
                scons_arg=[]
                #如果配置中有scons_arg
                if details.get('scons_arg') is not None:
                    for line in details.get('scons_arg'):
                        scons_arg.append(line)
                scons_arg_str=' '.join(scons_arg) if scons_arg else ' '
                print(f"::group::\tCompiling yml project: =={count}==={name}=scons_arg={scons_arg_str}==")

                #开始编译bsp
                res = build_bsp(bsp, scons_arg_str,name=name)
                
                if not res:
                    print(f"::error::build {bsp} {name} failed.")
                    add_summary(f'\t- ❌ build {bsp} {name} failed.')
                    failed += 1
                else:
                    add_summary(f'\t- ✅ build {bsp} {name} success.')
                print("::endgroup::")

                # print(commands)
                # print(check_result)
                # print(build_check_result)
                # print(qemu_command)
                # print(pre_build_commands)
                # print(ci_build_run_flag)

                #执行编译前的命令
                if pre_build_commands is not None:
                    for command in pre_build_commands:
                        output, returncode = run_command(command)
                        print(output)
                        if returncode != 0:
                            print(f"Pre-build command failed: {command}")
                            print(output)
                #执行编译命令
                if build_command is not None:
                    for command in build_command:
                        output, returncode = run_command(command)
                        print(output)
                        if returncode != 0 or not check_output(output, build_check_result):
                                print("Build failed or build check result not found")
                                print(output)
                #执行编译后的命令
                if post_build_command is not None:
                    for command in post_build_command:
                        output, returncode = run_command(command)
                        print(output)
                        if returncode != 0:
                            print(f"Post-build command failed: {post_build_command}")
                            print(output)
                #执行qemu中的执行命令
                if ci_build_run_flag is True:
                    print(qemu_command)
                    #exit(1)
                    print(os.getcwd())
                    qemu_manager = QemuManager(qemu_cmd=qemu_command, idle_timeout=qemu_timeout_second,checkresult=check_result)
                    qemu_manager.run(commands)

                shutil.copyfile(config_bacakup, config_file)
                os.remove(config_bacakup)



        attach_dir = os.path.join(rtt_root, 'bsp', bsp, '.ci/attachconfig')
        attach_list = []
        #这里是旧的文件方式
        for root, dirs, files in os.walk(attach_dir):
            for file in files:
                if file.endswith('attach'):
                    file_path = os.path.join(root, file)
                    relative_path = os.path.relpath(file_path, attach_dir)
                    attach_list.append(relative_path)

        for attach_file in attach_list:
            count += 1
            print(f"::group::\tCompiling BSP: =={count}=== {bsp} {attach_file}===")
            res = build_bsp_attachconfig(bsp, attach_file)
            if not res:
                print(f"::error::build {bsp} {attach_file} failed.")
                add_summary(f'\t- ❌ build {attach_file} failed.')
                failed += 1
            else:
                add_summary(f'\t- ✅ build {attach_file} success.')
            print("::endgroup::")

    exit(failed)
