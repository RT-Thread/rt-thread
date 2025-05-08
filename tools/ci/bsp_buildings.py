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
        run_cmd(f'scons -C bsp/{bsp} --pyconfig-silent', output_info=True)

        os.chdir(f'{rtt_root}/bsp/{bsp}')
        run_cmd('pkgs --update-force', output_info=True)
        run_cmd('pkgs --list')

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
        os.chdir(rtt_root)
        # scons 编译命令
        cmd = f'scons -C bsp/{bsp} -j{nproc} {scons_args}' # --debug=time for debug time
        output, res = run_cmd(cmd, output_info=True)
        if build_check_result is not None:
            if res != 0 or not check_output(output, build_check_result):
                    print("Build failed or build check result not found")
                    print(output)
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
    if post_build_command is not None:
        for command in post_build_command:
            output, returncode = run_cmd(command, output_info=True)
            print(output)
            if returncode != 0:
                print(f"Post-build command failed: {command}")
                print(output)
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
