import os
import sys
import shutil

cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))


# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    library_path = os.path.join(os.path.dirname(BSP_ROOT), '../libraries')
    print("library_path   ", library_path)
    library_dir = os.path.join(dist_dir, 'libraries')
    print("library_dir   ", library_dir)
    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'rt_drivers'), os.path.join(library_dir, 'rt_drivers'))
    print("=> copy bsp CMSIS")
    bsp_copy_files(os.path.join(library_path, 'bl_mcu_sdk'), os.path.join(library_dir, 'bl_mcu_sdk'))
    print("=> copy bsp library")

    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))

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
