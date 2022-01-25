import os
import sys
import shutil

cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))


# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    print("=> copy maxim bsp library")
    library_dir = os.path.join(dist_dir, 'libraries')
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')

    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'HAL_Drivers'), os.path.join(library_dir, 'HAL_Drivers'))
    bsp_copy_files(os.path.join(library_path, 'MAX32660PeriphDriver'), os.path.join(library_dir, 'MAX32660PeriphDriver'))
    