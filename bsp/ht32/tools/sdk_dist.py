import os
import re
import sys
import shutil

cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))


def bsp_update_kconfig_library(dist_dir):
    # change RTT_ROOT in Kconfig
    if not os.path.isfile(os.path.join(dist_dir, 'Kconfig')):
        return

    with open(os.path.join(dist_dir, 'Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'Kconfig'), 'w') as f:
        for line in data:
            if line.find('source') != -1 and line.find('../libraries') != -1:
                line = line.replace('../libraries', 'libraries')
            f.write(line)


# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    print("=> copy ht32 bsp library")
    library_dir = os.path.join(dist_dir, 'libraries')
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE), os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))

    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'ht32_drivers'), os.path.join(library_dir, 'ht32_drivers'))
    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))
    bsp_update_kconfig_library(dist_dir)


def get_source(ic_model, file_path, system_path, base_path):
    source_path = []
    files_list = []
    readafter = 0
    if not os.path.isfile(file_path):
        return

    with open(file_path, 'r') as file:
        # content = file.read()
        for line in file:
            if readafter == 2 and line.find('>') != -1:
                break
            if readafter == 2:
                files_list.append(line.strip())
            if line.find(ic_model) != -1:
                readafter = 1
            if readafter == 1 and line.find('<') != -1:
                readafter = 2
    for line in files_list:
        if line.find('system') != -1:
            source_path.append(os.path.join(system_path, line.strip()))
        else:
            source_path.append(os.path.join(base_path, line.strip()))
    return source_path
