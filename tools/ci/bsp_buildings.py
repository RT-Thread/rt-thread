# 
# Copyright (c) 2025, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2025-04-21     supperthomas add the smart yml support and add env 
#
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

SCONS_FATAL_PATTERNS = (
    re.compile(r'No SConstruct file found', re.IGNORECASE),
    re.compile(r'SConscript.*No such file or directory', re.IGNORECASE),
    re.compile(r'No such file or directory.*SConscript', re.IGNORECASE),
    re.compile(r"(can'?t|cannot|unable to)\s+(read|open|find).*SConscript", re.IGNORECASE),
    re.compile(r'FileNotFoundError:.*SConscript', re.IGNORECASE),
    re.compile(r'scons:\s+\*\*\*', re.IGNORECASE),
)

def add_summary(text):
    """
    add summary to github action.
    """
    summary_file = os.getenv('GITHUB_STEP_SUMMARY')
    if summary_file:
        with open(summary_file, 'a', encoding='utf-8') as file:
            file.write(text + '\n')

def normalize_returncode(status):
    """
    normalize os.system status to command exit code.
    """
    if status == 0:
        return 0

    if os.name == 'nt':
        return status

    if hasattr(os, 'waitstatus_to_exitcode'):
        try:
            return os.waitstatus_to_exitcode(status)
        except ValueError:
            return status

    return status >> 8

def contains_scons_fatal_error(output):
    """
    check whether scons output contains a fatal build-script error.
    """
    output_str = ''.join(output) if isinstance(output, list) else str(output)
    return any(pattern.search(output_str) for pattern in SCONS_FATAL_PATTERNS)

def check_bsp_build_scripts(bsp_dir):
    """
    check whether the BSP has the basic scons build entry files.
    """
    missing = []
    for filename in ('SConstruct', 'SConscript'):
        if not os.path.isfile(os.path.join(bsp_dir, filename)):
            missing.append(filename)

    if missing:
        print(f"::error::missing {', '.join(missing)} in {bsp_dir}")
        return False

    return True

def run_cmd(cmd, output_info=True):
    """
    run command and return output and result.
    """
    print('\033[1;32m' + cmd + '\033[0m')

    output_str_list = []
    res = 0
    output_file = f'output_{os.getpid()}_{threading.get_ident()}.txt'
    devnull = os.devnull

    if output_info:
        res = os.system(cmd + f" > {output_file} 2>&1")
    else:
        res = os.system(cmd + f" > {devnull} 2>{output_file}")

    with open(output_file, "r") as file:
        output_str_list = file.readlines()

    for line in output_str_list:
        print(line, end='')

    os.remove(output_file)

    res = normalize_returncode(res)
    if contains_scons_fatal_error(output_str_list):
        print(f"::error::scons fatal error detected while running: {cmd}")
        if res == 0:
            res = 1

    return output_str_list, res

def is_env_enabled(name, default=False):
    value = os.getenv(name)
    if value is None:
        return default

    return value.lower() not in ('', '0', 'false', 'no', 'off')

def get_ci_scons_args(scons_args=''):
    args = scons_args.strip()
    if os.getenv('RTT_TOOL_CHAIN') == 'armclang' and '--exec-path' not in args:
        exec_path = os.getenv('RTT_EXEC_PATH')
        if exec_path:
            args = f'{args} --exec-path="{exec_path}"'.strip()

    return args

def run_dist_build_check(bsp, scons_args=''):
    """
    build BSP distribution and verify that the generated project can compile.
    """
    scons_args = get_ci_scons_args(scons_args)
    os.chdir(rtt_root)
    bsp_dir = os.path.join(rtt_root, 'bsp', bsp)
    if not check_bsp_build_scripts(bsp_dir):
        return False

    dist_root = os.path.join(rtt_root, 'bsp', bsp, 'dist')
    dist_project = os.path.join(dist_root, 'project')
    if os.path.exists(dist_root):
        shutil.rmtree(dist_root)

    old_rtt_root = None
    try:
        _, res = run_cmd(f'scons --dist -C bsp/{bsp} {scons_args}', output_info=True)
        if res != 0:
            print(f"::error::scons --dist failed for {bsp}")
            return False

        if not os.path.exists(dist_project):
            print(f"::error::dist project not found: {dist_project}")
            return False

        if not check_bsp_build_scripts(dist_project):
            return False

        old_rtt_root = os.environ.pop('RTT_ROOT', None)
        _, res = run_cmd(f'scons --pyconfig-silent -C {dist_project} {scons_args}', output_info=True)
        if res != 0:
            print(f"::error::dist project pyconfig failed for {bsp}")
            return False

        nproc = multiprocessing.cpu_count()
        _, res = run_cmd(f'scons -C {dist_project} -j{nproc} {scons_args}', output_info=True)
        if res != 0:
            print(f"::error::dist project build failed for {bsp}")
            return False
    finally:
        if old_rtt_root is not None:
            os.environ['RTT_ROOT'] = old_rtt_root
        os.chdir(rtt_root)
        if os.path.exists(dist_root):
            shutil.rmtree(dist_root)

    return True


def build_bsp(bsp, scons_args='',name='default', pre_build_commands=None, post_build_command=None,build_check_result = None,bsp_build_env=None):
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
    bsp_dir = os.path.join(rtt_root, 'bsp', bsp)

    if not os.path.isdir(bsp_dir):
        print(f"::error::BSP directory not found: {bsp_dir}")
        return False

    if not check_bsp_build_scripts(bsp_dir):
        return False

    scons_args = get_ci_scons_args(scons_args)

    # 设置环境变量
    if bsp_build_env is not None:
        print("Setting environment variables:")
        for key, value in bsp_build_env.items():
            print(f"{key}={value}")
            os.environ[key] = value  # 设置环境变量
    os.chdir(rtt_root)
    os.makedirs(f'{rtt_root}/output/bsp/{bsp}', exist_ok=True)
    if os.path.exists(f"{rtt_root}/bsp/{bsp}/Kconfig"):
        os.chdir(rtt_root)
        _, res = run_cmd(f'scons -C bsp/{bsp} --pyconfig-silent {scons_args}', output_info=True)
        if res != 0:
            print(f"::error::pyconfig failed for {bsp}")
            success = False

        os.chdir(f'{rtt_root}/bsp/{bsp}')
        _, res = run_cmd('pkgs --update-force', output_info=True)
        if res != 0:
            print(f"::error::pkgs --update-force failed for {bsp}")
            success = False
        _, res = run_cmd('pkgs --list')
        if res != 0:
            print(f"::error::pkgs --list failed for {bsp}")
            success = False
    else:
        print(f"Kconfig not found, skip pyconfig and package update: {os.path.join(bsp_dir, 'Kconfig')}")

    nproc = multiprocessing.cpu_count()
    if pre_build_commands is not None:
        print("Pre-build commands:")
        print(pre_build_commands)
        for command in pre_build_commands:
            print(command)
            output, returncode = run_cmd(command, output_info=True)
            print(output)
            if returncode != 0:
                print(f"Pre-build command failed: {command}")
                print(output)
                success = False
    os.chdir(rtt_root)
    # scons 编译命令
    cmd = f'scons -C bsp/{bsp} -j{nproc} {scons_args}' # --debug=time for debug time
    output, res = run_cmd(cmd, output_info=True)
    if build_check_result is not None:
        if res != 0 or not check_output(output, build_check_result):
                print("Build failed or build check result not found")
                print(output)
                success = False
    if res != 0:
        success = False
    if success:
        #拷贝当前的文件夹下面的所有以elf结尾的文件拷贝到rt-thread/output文件夹下
        import glob
        # 拷贝编译生成的文件到output目录,文件拓展为 elf,bin,hex
        for file_type in ['*.elf', '*.bin', '*.hex']:
            files = glob.glob(f'{rtt_root}/bsp/{bsp}/{file_type}')
            for file in files:
                if not os.path.isfile(file):
                    continue
                shutil.copy(file, f'{rtt_root}/output/bsp/{bsp}/{name.replace("/", "_")}.{file_type[2:]}')
        if is_env_enabled('RTT_CI_BUILD_DIST'):
            print(f"::group::\tChecking dist project: {bsp} {name}")
            dist_res = run_dist_build_check(bsp, scons_args)
            print("::endgroup::")
            if not dist_res:
                add_summary(f'\t- ❌ dist build {bsp} {name} failed.')
                success = False
            else:
                add_summary(f'\t- ✅ dist build {bsp} {name} success.')

    os.chdir(f'{rtt_root}/bsp/{bsp}')
    if post_build_command is not None:
        for command in post_build_command:
            output, returncode = run_cmd(command, output_info=True)
            print(output)
            if returncode != 0:
                print(f"Post-build command failed: {command}")
                print(output)
                success = False
    _, clean_res = run_cmd(f'scons -c {scons_args}', output_info=False)
    if clean_res != 0:
        print(f"::error::scons clean failed for {bsp}")
        success = False

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
    if not os.path.isfile(config_file):
        print(f"::error::.config not found: {config_file}")
        return False

    attachconfig_dir = os.path.join(rtt_root, 'bsp', bsp, '.ci/attachconfig')
    attach_path = os.path.join(attachconfig_dir, attach_file)
    if not os.path.isfile(attach_path):
        print(f"::error::attach config not found: {attach_path}")
        return False

    shutil.copyfile(config_file, config_bacakup)

    try:
        append_file(attach_path, config_file)

        scons_args = check_scons_args(attach_path)

        res = build_bsp(bsp, scons_args,name=attach_file)
    finally:
        shutil.copyfile(config_bacakup, config_file)
        os.remove(config_bacakup)

    return res

def check_output(output, check_string):
    """检查输出中是否包含指定字符串"""
    output_str = ''.join(output) if isinstance(output, list) else str(output)
    flag = check_string in output_str
    if flag == True:
        print('Success: find string ' + check_string)
    else:
        print(output)
        print(f"::error:: can not find string {check_string}  output: {output_str}")

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
    attachconfig_rtt_bsp_env = os.getenv('ATTACHCONFIG_RTT_BSP')
    attachconfig_rtt_bsp = None
    if attachconfig_rtt_bsp_env:
        attachconfig_rtt_bsp = {
            bsp.strip()
            for bsp in attachconfig_rtt_bsp_env.split(',')
            if bsp.strip()
        }
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

        if attachconfig_rtt_bsp is not None and bsp not in attachconfig_rtt_bsp:
            print(f"Skip attachconfig build for {bsp}")
            add_summary(f'\t- ⏭️ skip attachconfig build {bsp}.')
            continue

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
        bsp_build_env = None
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
                    else:
                        build_check_result = None
                    if details.get("msh_cmd") is not None:
                        commands = details.get("msh_cmd").splitlines()
                    else:
                        msh_cmd = None
                    if details.get("checkresult") is not None:
                        check_result = details.get("checkresult")
                    else:
                        check_result = None
                    if details.get("ci_build_run_flag") is not None:
                        ci_build_run_flag = details.get("ci_build_run_flag")
                    else:
                        ci_build_run_flag = None
                    if details.get("pre_build") is not None:
                        pre_build_commands = details.get("pre_build").splitlines()
                    if details.get("env") is not None:
                        bsp_build_env = details.get("env")
                    else:
                        bsp_build_env = None
                    if details.get("build_cmd") is not None:
                        build_command = details.get("build_cmd").splitlines()
                    else:
                        build_command = None
                    if details.get("post_build") is not None:
                        post_build_command = details.get("post_build").splitlines()
                    if details.get("run_cmd") is not None:
                        qemu_command = details.get("run_cmd")
                    else:
                        qemu_command = None
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
                # #开始编译bsp
                res = build_bsp(bsp, scons_arg_str,name=name,pre_build_commands=pre_build_commands,post_build_command=post_build_command,build_check_result=build_check_result,bsp_build_env =bsp_build_env)
                if not res:
                    print(f"::error::build {bsp} {name} failed.")
                    add_summary(f'\t- ❌ build {bsp} {name} failed.')
                    failed += 1
                else:
                    add_summary(f'\t- ✅ build {bsp} {name} success.')
                print("::endgroup::")


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
