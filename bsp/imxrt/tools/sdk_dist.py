import os
import sys
import shutil
cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))

# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir=None):
    from mkdist import bsp_copy_files
    import rtconfig
    
    if dist_dir is None:
        dist_dir  = os.path.join(BSP_ROOT, 'dist', os.path.basename(BSP_ROOT))

    print("=> copy imxrt bsp library")
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    library_dir  = os.path.join(dist_dir, 'libraries')
    bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE), 
                   os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))
    
    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'drivers'), os.path.join(library_dir, 'drivers'))
    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))

    print("=> copy bsp peripherals")
    bsp_copy_files(os.path.join(library_path, 'peripherals'), os.path.join(library_dir, 'peripherals'))
