import os
import sys
import shutil

cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))

def bsp_update_board_kconfig(dist_dir):
    # change board/kconfig path
    if not os.path.isfile(os.path.join(dist_dir, 'board/Kconfig')):
        return

    with open(os.path.join(dist_dir, 'board/Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'board/Kconfig'), 'w') as f:
        for line in data:
            if line.find('../libraries/gd32_drivers/Kconfig') != -1:
                position = line.find('../libraries/gd32_drivers/Kconfig')
                line = line[0:position] + 'libraries/gd32_drivers/Kconfig"\n'
            f.write(line)
            
# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    print("=> copy gd32 bsp library")
    library_dir = os.path.join(dist_dir, 'libraries')
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    # Only copy specific library when BSP_LIBRARY_TYPE is not None
    if rtconfig.BSP_LIBRARY_TYPE is not None:
        bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE),
                       os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))

    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'gd32_drivers'), os.path.join(library_dir, 'gd32_drivers'))
    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))
    
    bsp_update_board_kconfig(dist_dir)
