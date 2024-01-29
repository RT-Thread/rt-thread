import os
import sys
import shutil
cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))

# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'Libraries')
    library_dir  = os.path.join(dist_dir, 'Libraries')
    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'drivers'), os.path.join(library_dir, 'drivers'))
    print("=> copy bsp CMSIS")
    bsp_copy_files(os.path.join(library_path, 'CMSIS'), os.path.join(library_dir, 'CMSIS'))
    print("=> copy bsp library")
    bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE), os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))
    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))
