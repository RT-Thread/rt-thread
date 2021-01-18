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
import shutil

from shutil import ignore_patterns

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
            if line.find('../libraries/HAL_Drivers/Kconfig') != -1:
                position = line.find('../libraries/HAL_Drivers/Kconfig')
                line = line[0:position] + 'libraries/HAL_Drivers/Kconfig"\n'
            f.write(line)

def bs_update_ide_project(bsp_root, rtt_root, rttide = None):
    import subprocess
    # default update the projects which have template file

    if rttide == None:
        tgt_dict = {'mdk4':('keil', 'armcc'),
                    'mdk5':('keil', 'armcc'),
                    'iar':('iar', 'iar'),
                    'vs':('msvc', 'cl'),
                    'vs2012':('msvc', 'cl'),
                    'cdk':('gcc', 'gcc')}
    else:
        item = 'eclipse --project-name=' + rttide['project_name']
        tgt_dict = {item:('gcc', 'gcc')}

    scons_env = os.environ.copy()
    scons_env['RTT_ROOT'] = rtt_root

    for item in tgt_dict:
        child = subprocess.Popen('scons --target=' + item, cwd=bsp_root, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        stdout, stderr = child.communicate()
        if child.returncode == 0:
            print('update %s project' % item)

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

def MkDist_Strip(program, BSP_ROOT, RTT_ROOT, Env):
    global source_list

    print('make distribution and strip useless files....')

    dist_name = os.path.basename(BSP_ROOT)
    dist_dir  = os.path.join(BSP_ROOT, 'dist-strip', dist_name)
    target_path = os.path.join(dist_dir, 'rt-thread')

    print('=> %s' % os.path.basename(BSP_ROOT))
    bsp_copy_files(BSP_ROOT, dist_dir)

    # copy stm32 bsp libiary files
    if os.path.basename(os.path.dirname(BSP_ROOT)) == 'stm32':
        print("=> copy stm32 bsp library")
        library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
        library_dir  = os.path.join(dist_dir, 'libraries')
        bsp_copy_files(os.path.join(library_path, 'HAL_Drivers'), os.path.join(library_dir, 'HAL_Drivers'))
        bsp_copy_files(os.path.join(library_path, Env['bsp_lib_type']), os.path.join(library_dir, Env['bsp_lib_type']))
        shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))

    # do bsp special dist handle
    if 'dist_handle' in Env:
        print("=> start dist handle")
        dist_handle = Env['dist_handle']
        dist_handle(BSP_ROOT, dist_dir)

    # get all source files from program
    for item in program:
        walk_children(item)
    source_list.sort()

    # copy the source files without libcpu and components/libc in RT-Thread
    target_list = []
    libcpu_dir = os.path.join(RTT_ROOT, 'libcpu').lower()
    libc_dir = os.path.join(RTT_ROOT, 'components', 'libc', 'compilers').lower()
    sal_dir = os.path.join(RTT_ROOT, 'components', 'net', 'sal_socket').lower()
    sources_include_sal = False
    for src in source_list:
        if src.lower().startswith(BSP_ROOT.lower()):
            continue

        # skip libc and libcpu dir
        if src.lower().startswith(libcpu_dir):
            continue
        if src.lower().startswith(libc_dir):
            continue
        if src.lower().startswith(sal_dir):
            sources_include_sal = True
            continue

        if src.lower().startswith(RTT_ROOT.lower()):
            target_list.append(src)
    source_list = target_list

    # get source directory
    src_dir = []
    for src in source_list:
        src = src.replace(RTT_ROOT, '')
        if src[0] == os.sep or src[0] == '/':
            src = src[1:]

        path = os.path.dirname(src)
        sub_path = path.split(os.sep)
        full_path = RTT_ROOT
        for item in sub_path:
            full_path = os.path.join(full_path, item)
            if full_path not in src_dir:
                src_dir.append(full_path)

    # add all of SConscript files
    for item in src_dir:
        source_list.append(os.path.join(item, 'SConscript'))

    # add all of Kconfig files
    walk_kconfig(RTT_ROOT, source_list)

    # copy all files to target directory
    source_list.sort()
    for src in source_list:
        dst = src.replace(RTT_ROOT, '')
        if dst[0] == os.sep or dst[0] == '/':
            dst = dst[1:]

        print('=> %s' % dst)
        dst = os.path.join(target_path, dst)
        do_copy_file(src, dst)

    # copy tools directory
    print('=> tools')
    do_copy_folder(os.path.join(RTT_ROOT, 'tools'), os.path.join(target_path, 'tools'), ignore_patterns('*.pyc'))
    do_copy_file(os.path.join(RTT_ROOT, 'Kconfig'), os.path.join(target_path, 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'AUTHORS'), os.path.join(target_path, 'AUTHORS'))
    do_copy_file(os.path.join(RTT_ROOT, 'COPYING'), os.path.join(target_path, 'COPYING'))
    do_copy_file(os.path.join(RTT_ROOT, 'README.md'), os.path.join(target_path, 'README.md'))
    do_copy_file(os.path.join(RTT_ROOT, 'README_zh.md'), os.path.join(target_path, 'README_zh.md'))

    print('=> %s' % os.path.join('components', 'libc', 'compilers'))
    do_copy_folder(os.path.join(RTT_ROOT, 'components', 'libc', 'compilers'), os.path.join(target_path, 'components', 'libc', 'compilers'))

    if sources_include_sal:
        print('=> %s' % os.path.join('components', 'net', 'sal_socket'))
        do_copy_folder(os.path.join(RTT_ROOT, 'components', 'net', 'sal_socket'), os.path.join(target_path, 'components', 'net', 'sal_socket'))

    # copy all libcpu/ARCH directory
    import rtconfig
    print('=> %s' % (os.path.join('libcpu', rtconfig.ARCH, rtconfig.CPU)))
    do_copy_folder(os.path.join(RTT_ROOT, 'libcpu', rtconfig.ARCH, rtconfig.CPU), os.path.join(target_path, 'libcpu', rtconfig.ARCH, rtconfig.CPU))
    if os.path.exists(os.path.join(RTT_ROOT, 'libcpu', rtconfig.ARCH, 'common')):
        print('=> %s' % (os.path.join('libcpu', rtconfig.ARCH, 'common')))
        do_copy_folder(os.path.join(RTT_ROOT, 'libcpu', rtconfig.ARCH, 'common'), os.path.join(target_path, 'libcpu', rtconfig.ARCH, 'common'))
    do_copy_file(os.path.join(RTT_ROOT, 'libcpu', 'Kconfig'), os.path.join(target_path, 'libcpu', 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'libcpu', 'SConscript'), os.path.join(target_path, 'libcpu', 'SConscript'))

    # change RTT_ROOT in SConstruct
    bsp_update_sconstruct(dist_dir)
    # change RTT_ROOT in Kconfig
    bsp_update_kconfig(dist_dir)
    bsp_update_kconfig_library(dist_dir)
    # update all project files
    bs_update_ide_project(dist_dir, target_path)

    # make zip package
    zip_dist(dist_dir, dist_name)

    print('done!')

def MkDist(program, BSP_ROOT, RTT_ROOT, Env, rttide = None):
    print('make distribution....')

    dist_name = os.path.basename(BSP_ROOT)

    if rttide == None:
        dist_dir = os.path.join(BSP_ROOT, 'dist', dist_name)
    else:
        dist_dir = rttide['project_path']

    target_path = os.path.join(dist_dir, 'rt-thread')

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
    do_copy_folder(os.path.join(RTT_ROOT, 'components'), os.path.join(target_path, 'components'))

    # skip documentation directory
    # skip examples

    # copy include directory
    print('=> include')
    do_copy_folder(os.path.join(RTT_ROOT, 'include'), os.path.join(target_path, 'include'))

    # copy all libcpu/ARCH directory
    print('=> libcpu')
    import rtconfig
    do_copy_folder(os.path.join(RTT_ROOT, 'libcpu', rtconfig.ARCH), os.path.join(target_path, 'libcpu', rtconfig.ARCH))
    do_copy_file(os.path.join(RTT_ROOT, 'libcpu', 'Kconfig'), os.path.join(target_path, 'libcpu', 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'libcpu', 'SConscript'), os.path.join(target_path, 'libcpu', 'SConscript'))

    # copy src directory
    print('=> src')
    do_copy_folder(os.path.join(RTT_ROOT, 'src'), os.path.join(target_path, 'src'))

    # copy tools directory
    print('=> tools')
    do_copy_folder(os.path.join(RTT_ROOT, 'tools'), os.path.join(target_path, 'tools'), ignore_patterns('*.pyc'))

    do_copy_file(os.path.join(RTT_ROOT, 'Kconfig'), os.path.join(target_path, 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'AUTHORS'), os.path.join(target_path, 'AUTHORS'))
    do_copy_file(os.path.join(RTT_ROOT, 'COPYING'), os.path.join(target_path, 'COPYING'))
    do_copy_file(os.path.join(RTT_ROOT, 'README.md'), os.path.join(target_path, 'README.md'))
    do_copy_file(os.path.join(RTT_ROOT, 'README_zh.md'), os.path.join(target_path, 'README_zh.md'))

    # change RTT_ROOT in SConstruct
    bsp_update_sconstruct(dist_dir)
    # change RTT_ROOT in Kconfig
    bsp_update_kconfig(dist_dir)
    bsp_update_kconfig_library(dist_dir)

    # update all project files
    if rttide == None:
        bs_update_ide_project(dist_dir, target_path)
    else:
        bs_update_ide_project(dist_dir, target_path, rttide)

    # make zip package
    if rttide == None:
        zip_dist(dist_dir, dist_name)

    print('done!')

