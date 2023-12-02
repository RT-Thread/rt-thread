#
# File      : mkdir.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Change Logs:
# Date           Author       Notes
# 2017-10-04     Bernard      The first version

import os
import subprocess
import shutil
from shutil import ignore_patterns
from SCons.Script import *

def do_copy_file(src, dst):
    # check source file
    if not os.path.exists(src):
        return

    path = os.path.dirname(dst)
    # mkdir if path not exist
    if not os.path.exists(path):
        os.makedirs(path)

    shutil.copy2(src, dst)

def do_copy_folder(src_dir, dst_dir, ignore=None):
    import shutil
    # check source directory
    if not os.path.exists(src_dir):
        return

    try:
        if os.path.exists(dst_dir):
            shutil.rmtree(dst_dir)
    except:
        print('Deletes folder: %s failed.' % dst_dir)
        return

    shutil.copytree(src_dir, dst_dir, ignore = ignore)

source_ext = ['c', 'h', 's', 'S', 'cpp', 'xpm']
source_list = []

def walk_children(child):
    global source_list
    global source_ext

    # print child
    full_path = child.rfile().abspath
    file_type  = full_path.rsplit('.',1)[1]
    #print file_type
    if file_type in source_ext:
        if full_path not in source_list:
            source_list.append(full_path)

    children = child.all_children()
    if children != []:
        for item in children:
            walk_children(item)

def walk_kconfig(RTT_ROOT, source_list):
    for parent, dirnames, filenames in os.walk(RTT_ROOT):
        if 'bsp' in parent:
            continue
        if '.git' in parent:
            continue
        if 'tools' in parent:
            continue

        if 'Kconfig' in filenames:
            pathfile = os.path.join(parent, 'Kconfig')
            source_list.append(pathfile)
        if 'KConfig' in filenames:
            pathfile = os.path.join(parent, 'KConfig')
            source_list.append(pathfile)

def bsp_copy_files(bsp_root, dist_dir):
    # copy BSP files
    do_copy_folder(os.path.join(bsp_root), dist_dir,
        ignore_patterns('build', 'dist', '*.pyc', '*.old', '*.map', 'rtthread.bin', '.sconsign.dblite', '*.elf', '*.axf', 'cconfig.h'))

def bsp_update_sconstruct(dist_dir):
    with open(os.path.join(dist_dir, 'SConstruct'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'SConstruct'), 'w') as f:
        for line in data:
            if line.find('RTT_ROOT') != -1:
                if line.find('sys.path') != -1:
                    f.write('# set RTT_ROOT\n')
                    f.write('if not os.getenv("RTT_ROOT"): \n    RTT_ROOT="rt-thread"\n\n')
            f.write(line)

def bsp_update_kconfig_testcases(dist_dir):
    # delete testcases in rt-thread/Kconfig
    if not os.path.isfile(os.path.join(dist_dir, 'rt-thread/Kconfig')):
        return

    with open(os.path.join(dist_dir, 'rt-thread/Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'rt-thread/Kconfig'), 'w') as f:
        for line in data:
            if line.find('examples/utest/testcases/Kconfig') == -1:
                f.write(line)

def bsp_update_kconfig(dist_dir):
    # change RTT_ROOT in Kconfig
    if not os.path.isfile(os.path.join(dist_dir, 'Kconfig')):
        return

    with open(os.path.join(dist_dir, 'Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'Kconfig'), 'w') as f:
        found = 0
        for line in data:
            if line.find('RTT_ROOT') != -1:
                found = 1
            if line.find('default') != -1 and found:
                position = line.find('default')
                line = line[0:position] + 'default "rt-thread"\n'
                found = 0
            f.write(line)

def bsp_update_kconfig_library(dist_dir):
    # change RTT_ROOT in Kconfig
    if not os.path.isfile(os.path.join(dist_dir, 'Kconfig')):
        return

    with open(os.path.join(dist_dir, 'Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'Kconfig'), 'w') as f:
        found = 0
        for line in data:
            if line.find('RTT_ROOT') != -1:
                found = 1
            if line.find('../libraries') != -1 and found:
                position = line.find('../libraries')
                line = line[0:position] + 'libraries/Kconfig"\n'
                found = 0
            f.write(line)

    # change board/kconfig path
    if not os.path.isfile(os.path.join(dist_dir, 'board/Kconfig')):
        return

    with open(os.path.join(dist_dir, 'board/Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'board/Kconfig'), 'w') as f:
        for line in data:
            if line.find('../libraries/HAL_Drivers/drivers/Kconfig') != -1:
                position = line.find('../libraries/HAL_Drivers/drivers/Kconfig')
                line = line[0:position] + 'libraries/HAL_Drivers/drivers/Kconfig"\n'
            f.write(line)

def zip_dist(dist_dir, dist_name):
    import zipfile

    zip_filename = os.path.join(dist_dir)
    zip = zipfile.ZipFile(zip_filename + '.zip', 'w')
    pre_len = len(os.path.dirname(dist_dir))

    for parent, dirnames, filenames in os.walk(dist_dir):
        for filename in filenames:
            pathfile = os.path.join(parent, filename)
            arcname = pathfile[pre_len:].strip(os.path.sep)
            zip.write(pathfile, arcname)

    zip.close()

def MkDist(program, BSP_ROOT, RTT_ROOT, Env, project_name, project_path):
    print('make distribution....')

    if project_path == None:
        dist_dir = os.path.join(BSP_ROOT, 'dist', project_name)
    else:
        dist_dir = project_path

    rtt_dir_path = os.path.join(dist_dir, 'rt-thread')

    # copy BSP files
    print('=> %s' % os.path.basename(BSP_ROOT))
    bsp_copy_files(BSP_ROOT, dist_dir)

    # do bsp special dist handle
    if 'dist_handle' in Env:
        print("=> start dist handle")
        dist_handle = Env['dist_handle']
        dist_handle(BSP_ROOT, dist_dir)

    # copy tools directory
    print('=> components')
    do_copy_folder(os.path.join(RTT_ROOT, 'components'), os.path.join(rtt_dir_path, 'components'))

    # skip documentation directory
    # skip examples

    # copy include directory
    print('=> include')
    do_copy_folder(os.path.join(RTT_ROOT, 'include'), os.path.join(rtt_dir_path, 'include'))

    # copy all libcpu/ARCH directory
    print('=> libcpu')
    import rtconfig
    do_copy_folder(os.path.join(RTT_ROOT, 'libcpu', rtconfig.ARCH), os.path.join(rtt_dir_path, 'libcpu', rtconfig.ARCH))
    do_copy_file(os.path.join(RTT_ROOT, 'libcpu', 'Kconfig'), os.path.join(rtt_dir_path, 'libcpu', 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'libcpu', 'SConscript'), os.path.join(rtt_dir_path, 'libcpu', 'SConscript'))

    # copy src directory
    print('=> src')
    do_copy_folder(os.path.join(RTT_ROOT, 'src'), os.path.join(rtt_dir_path, 'src'))

    # copy tools directory
    print('=> tools')
    do_copy_folder(os.path.join(RTT_ROOT, 'tools'), os.path.join(rtt_dir_path, 'tools'), ignore_patterns('*.pyc'))

    do_copy_file(os.path.join(RTT_ROOT, 'Kconfig'), os.path.join(rtt_dir_path, 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'AUTHORS'), os.path.join(rtt_dir_path, 'AUTHORS'))
    do_copy_file(os.path.join(RTT_ROOT, 'COPYING'), os.path.join(rtt_dir_path, 'COPYING'))
    do_copy_file(os.path.join(RTT_ROOT, 'README.md'), os.path.join(rtt_dir_path, 'README.md'))
    do_copy_file(os.path.join(RTT_ROOT, 'README_zh.md'), os.path.join(rtt_dir_path, 'README_zh.md'))

    print('Update configuration files...')
    # change RTT_ROOT in SConstruct
    bsp_update_sconstruct(dist_dir)
    # change RTT_ROOT in Kconfig
    bsp_update_kconfig(dist_dir)
    bsp_update_kconfig_library(dist_dir)
    # delete testcases in Kconfig
    bsp_update_kconfig_testcases(dist_dir)

    target_project_type = GetOption('target')
    if target_project_type:
        child = subprocess.Popen('scons --target={} --project-name="{}"'.format(target_project_type, project_name), cwd=dist_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        stdout, stderr = child.communicate()
        if child.returncode == 0:
            print(stdout)
        else:
            print(stderr)
    else:
        print('suggest to use command scons --dist [--target=xxx] [--project-name="xxx"] [--project-path="xxx"]')

    # make zip package
    if project_path == None:
        zip_dist(dist_dir, project_name)

    print('dist project successfully!')
