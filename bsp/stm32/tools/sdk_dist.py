import os
import sys
import shutil

cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))


# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    print("=> copy stm32 bsp library")
    library_dir = os.path.join(dist_dir, 'libraries')
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    if rtconfig.BSP_LIBRARY_TYPE is not None:
        bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE),
                    os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))

    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'HAL_Drivers'), os.path.join(library_dir, 'HAL_Drivers'))
    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))
