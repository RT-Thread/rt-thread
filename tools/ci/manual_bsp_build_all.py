#
# Copyright (c) 2006-2024, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2024-07-25     supperthomas the first version
#

"""
这个脚本用来编译所有的bsp
这里的脚本是用的arm-none-eabi-gcc, 默认根据本机已经安装的gcc来编译
其他的工具链暂时不支持，其实主要根据运行的环境中支持不支持，目前只打算支持主流的
失败的bsp会存到failed_bsp.log里面
"""

import os
import sys
import shutil
import multiprocessing
from multiprocessing import Process
import yaml

#help说明
def usage():
    print('%s all     -- build all GCC bsp' % os.path.basename(sys.argv[0]))
    print('%s clean   -- clean all bsp' % os.path.basename(sys.argv[0]))
    print('%s update  -- update all prject files' % os.path.basename(sys.argv[0]))

def add_summary(text):
    """
    add summary to github action.
    """
    os.system(f'echo "{text}" >> $GITHUB_STEP_SUMMARY ;')

def run_cmd(cmd, output_info=True):
    """
    这个函数用来执行命令
    run command and return output and result.
    """
    print('\033[1;32m' + cmd + '\033[0m   ' + os.getcwd())

    output_str_list = []
    res = 0
    
    if output_info:
        res = os.system(cmd + " > output.txt 2>&1")
    else:
        res = os.system(cmd + " > /dev/null 2>output.txt")
    try:
        with open("output.txt", "r") as file:
            output_str_list = file.readlines()
    except FileNotFoundError:
        with open("output.txt", "w") as file:
            file.write("new file")

    for line in output_str_list:
        print(line, end='')

    os.remove("output.txt")

    return output_str_list, res


def build_bsp(bsp, scons_args=''):
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
    pwd = os.getcwd()
    print('======pwd==='+ os.getcwd()+'===bsp:=='+bsp)

    os.chdir(rtt_root)
    #有Kconfig 说明可以执行menuconfig
    if os.path.exists(f"{rtt_root}/bsp/{bsp}/Kconfig"):
        os.chdir(rtt_root)
        print('======pwd==='+ os.getcwd()+'===bsp:=='+bsp)
        run_cmd(f'scons -C bsp/{bsp} --pyconfig-silent', output_info=True)
        os.chdir(f'{rtt_root}/bsp/{bsp}')
        print('======pwd222==='+ os.getcwd()+'===bsp:=='+bsp)
        run_cmd('pkgs --update', output_info=True)
        run_cmd('pkgs --list')
        nproc = multiprocessing.cpu_count()
        os.chdir(rtt_root)
        cmd = f'scons -C bsp/{bsp} -j{nproc} {scons_args}'
        result_log, res = run_cmd(cmd, output_info=True)

        if res != 0:
            # 将失败的bsp写入特定的txt文件
            with open(os.path.join(rtt_root, 'failed_bsp_list.txt'), 'a') as file:
                file.write(bsp + '\n')
            # 打印失败的bsp的log，把它放到对应的文件名文bsp的txt文件中
            with open(os.path.join(rtt_root, 'failed_bsp.log'), 'a') as file:
                file.write(f'===================={bsp}====================\n')
                for line in result_log:
                    file.write(line)
            print(f"::error::build {bsp} failed")
            add_summary(f"- ❌ build {bsp} failed.")
            success = False
    else:
        # 如果没有Kconfig直接执行scons
        os.chdir(f'{rtt_root}/bsp/{bsp}')
        run_cmd('scons', output_info=True)

    # 删除packages文件夹
    pkg_dir = os.path.join(rtt_root, 'bsp', bsp, 'packages')
    shutil.rmtree(pkg_dir, ignore_errors=True)
    #恢复到原目录
    os.chdir(pwd)
    return success

#判断参数是否是2个
if len(sys.argv) != 2:
    usage()
    sys.exit(0)
#更新MDK等文件
def update_project_file(project_dir):
    if os.path.isfile(os.path.join(project_dir, 'template.Uv2')):
        print('prepare MDK3 project file on ' + project_dir)
        command = ' --target=mdk -s'
        os.system('scons --directory=' + project_dir + command + ' > 1.txt')

    if os.path.isfile(os.path.join(project_dir, 'template.uvproj')):
        print('prepare MDK4 project file on ' + project_dir)
        command = ' --target=mdk4 -s'
        os.system('scons --directory=' + project_dir + command + ' > 1.txt')

    if os.path.isfile(os.path.join(project_dir, 'template.uvprojx')):
        print('prepare MDK5 project file on ' + project_dir)
        command = ' --target=mdk5 -s'
        os.system('scons --directory=' + project_dir + command + ' > 1.txt')

    if os.path.isfile(os.path.join(project_dir, 'template.ewp')):
        print('prepare IAR project file on ' + project_dir)
        command = ' --target=iar -s'
        os.system('scons --directory=' + project_dir + command + ' > 1.txt')

#更新所有可以scons的文件夹文件，先执行menuconfig --silent 再执行scons --target=mdk5
#处理带有sconstruct的文件夹
def update_all_project_files(sconstruct_paths):
    for projects in sconstruct_paths:
        try:
            # update rtconfig.h and .config
            #执行menuconfig
            if os.path.isfile(os.path.join(projects, 'Kconfig')):
                if "win32" in sys.platform:
                    retval = os.getcwd()
                    os.chdir(projects)
                    os.system("menuconfig --silent")
                    os.chdir(retval)
                else:
                    os.system('scons --pyconfig-silent -C {0}'.format(projects))
                print('==menuconfig=======projects='+ projects)
            else:
                print('==no kconfig=in==!!!!!=projects='+ projects)
            # update mdk, IAR etc file
            update_project_file(projects)
        except Exception as e:
            print("error message: {}".format(e))
            sys.exit(-1)

#找到带有Sconstruct的文件夹

def find_sconstruct_paths(project_dir, exclude_paths, include_paths):
    sconstruct_paths = []
    bsp_detail_path = os.path.join(rtt_root, 'tools', 'ci', 'bsp_detail.yml')
    if os.path.exists(bsp_detail_path):
        with open(bsp_detail_path, 'r') as file:
            bsp_detail = yaml.safe_load(file)
    for root, dirs, files in os.walk(project_dir):
        if include_paths:
            if any(include_path in root for include_path in include_paths) and all(exclude_path not in root for exclude_path in exclude_paths):
                if 'SConstruct' in files:
                    bsp_name = os.path.relpath(root, bsp_root)
                    if bsp_name in bsp_detail and bsp_detail[bsp_name].get('gcc') == 'arm-none-eabi-gcc':
                        sconstruct_paths.append(root)
        else:
            if all(exclude_path not in root for exclude_path in exclude_paths):
                if 'SConstruct' in files:
                    bsp_name = os.path.relpath(root, bsp_root)
                    if bsp_name in bsp_detail and bsp_detail[bsp_name].get('gcc') == 'arm-none-eabi-gcc':
                        sconstruct_paths.append(root)
    return sconstruct_paths

#检查EXE命令是否存在，判断环境
def check_command_availability(cmd):
    """
    Check if a command is available.
    """
    cmd_path = shutil.which(cmd)
    if cmd_path is not None:
        #print(f"{cmd} command is available at {cmd_path}")
        return True
    else:
        print(f"{cmd} command is not available")
        return False
# Find the rt-thread root directory
rtt_root = os.getcwd()
while not os.path.exists(os.path.join(rtt_root, 'LICENSE')):
    rtt_root = os.path.dirname(rtt_root)

bsp_root = os.path.join(rtt_root, 'bsp')

#需要排除的文件夹名字
exclude_paths = ['templates', 'doc', 'libraries', 'Libraries', 'template']
include_paths = []#['nrf5x','qemu-vexpress-a9', 'ESP32_C3','simulator']

sconstruct_paths = find_sconstruct_paths(bsp_root, exclude_paths,include_paths)

# get command options
command = ''
command_clean_flag = False

print(rtt_root)

if sys.argv[1] == 'all':
    if os.path.exists(os.path.join(rtt_root, 'failed_bsp_list.txt')):
        os.remove(os.path.join(rtt_root, 'failed_bsp_list.txt'))
    if os.path.exists(os.path.join(rtt_root, 'failed_bsp.log')):
        os.remove(os.path.join(rtt_root, 'failed_bsp.log'))
    command = ' '
#更新所有的工程
    print('begin to update all the bsp projects')
    update_all_project_files(sconstruct_paths)
#iarbuild .\project.ewp -clean rt-thread
elif sys.argv[1] == 'clean':
    command = ' -c'
    command_clean_flag = True
    print('begin to clean all the bsp projects')
# 执行所有其他IDE的 update 但是不编译,这个一般不会出错
elif sys.argv[1] == 'update':
    print('begin to update all the bsp projects')
#更新所有的工程
    update_all_project_files(sconstruct_paths)
    print('finished!')
    sys.exit(0)
else:
    usage()
    sys.exit(0)

if sconstruct_paths:
    print("包含 'SConstruct' 文件的路径:")
    for path in sconstruct_paths:
        print(path)
else:
    print("未找到包含 'SConstruct' 文件的路径")

#遍历所有的sconstruct_paths  路径中的文件夹

def bsp_scons_worker(project_dir):
    print('=========project_dir===='+ project_dir)
#判断有没有SConstruct 文件，
    if os.path.isfile(os.path.join(project_dir, 'SConstruct')):
        print('==menuconfig=======rtt_root='+ rtt_root)
        print('==project_dir=======project_dir='+ project_dir)

        # 去掉 'bsp' 前面的三级目录
        parts = project_dir.split(os.sep)
        if 'bsp' in parts:
            bsp_index = parts.index('bsp')
            new_project_dir = os.sep.join(parts[bsp_index+1:])
        else:
            new_project_dir = project_dir
        print('==project_dir=======new_project_dir='+ new_project_dir)
        #开始编译bsp
        build_bsp(new_project_dir)

# 发现有keil相关的，执行keil相关的命令，先检查一下UV4.exe命令有没有，然后执行UV4.exe
    if check_command_availability('UV4.exe') :
        """      
        UV4.exe -b project.uvprojx -q -j0 -t rt-thread -o action_runner.log
        ls
        sleep 10
        cat action_runner.log
        """
        if os.path.isfile(os.path.join(project_dir, 'template.uvprojx')):
            if check_command_availability('UV4.exe'):
                print('Start to build keil project======')
                os.chdir(f'{project_dir}')
                print('clean keil project======')
                run_cmd('UV4.exe -c project.uvprojx -q')
                ___, res = run_cmd('UV4.exe -b project.uvprojx -q -j0 -t rt-thread -o keil.log')
                os.chdir(f'{rtt_root}')
            else:
                print('UV4.exe is not available, please check your keil installation')
    if check_command_availability('iarbuild.exe') :
        """      
        iarbuild .\project.ewp rt-thread
        """
        if os.path.isfile(os.path.join(project_dir, 'template.ewp')):
            if check_command_availability('iarbuild.exe'):
                print('Start to build iar project======')
                os.chdir(f'{project_dir}')
                ___, res = run_cmd('iarbuild .\project.ewp -clean rt-thread')                    
                if res != 0:
                    print('run clean failed!!')
                ___, res = run_cmd('iarbuild .\project.ewp rt-thread > iar.log')
                if res != 0:
                    print('run_cmd1 failed!!')
                os.chdir(f'{rtt_root}')
            else:
                print('iarbuild is not available, please check your iar installation')

processes = []
for project_dir in sconstruct_paths:
    bsp_scons_worker(project_dir)
    #p = Process(target=bsp_scons_worker, args=(project_dir,))
    #p.start()
    #processes.append(p)

#for p in processes:
#    p.join()  # 等待所有进程完成

print('finished!')

# 将failed_bsp_list.txt的内容追加到failed_bsp.log文件中
if os.path.exists(os.path.join(rtt_root, 'failed_bsp_list.txt')):
    with open(os.path.join(rtt_root, 'failed_bsp_list.txt'), 'r') as file:
        failed_bsp_list = file.read()
if os.path.exists(os.path.join(rtt_root, 'failed_bsp.log')):
    with open(os.path.join(rtt_root, 'failed_bsp.log'), 'a') as file:
        file.write(failed_bsp_list)