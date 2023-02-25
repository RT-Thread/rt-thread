import os
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
        found = 0
        for line in data:
            if line.find('RTT_ROOT') != -1:
                found = 1
            if line.find('../libraries') != -1 and found:
                position = line.find('../libraries')
                line = line[0:position] + 'libraries/Kconfig"\n'
                found = 0
            f.write(line)

# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    print("=> copy at32 bsp library")
    library_dir = os.path.join(dist_dir, 'libraries')
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE),
                   os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))

    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'rt_drivers'), os.path.join(library_dir, 'rt_drivers'))
    bsp_copy_files(os.path.join(library_path, 'usbd_library'), os.path.join(library_dir, 'usbd_library'))
    bsp_copy_files(os.path.join(library_path, 'usbfs_library'), os.path.join(library_dir, 'usbfs_library'))
    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))
    bsp_update_kconfig_library(dist_dir)