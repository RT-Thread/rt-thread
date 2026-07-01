import os
import sys
import shutil

cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))

def update_kconfig_library_path(dist_dir):
    kconfig_path = os.path.join(dist_dir, 'Kconfig')
    if not os.path.isfile(kconfig_path):
        return

    with open(kconfig_path, 'r') as f:
        data = f.read()

    data = data.replace('LIB_DIR := ../libraries/HAL_Drivers',
                        'LIB_DIR := libraries/HAL_Drivers')

    with open(kconfig_path, 'w') as f:
        f.write(data)

# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    print("=> copy novosns bsp library")
    library_dir = os.path.join(dist_dir, 'libraries')
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    if rtconfig.BSP_LIBRARY_TYPE is not None:
        bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE),
                    os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))

    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'HAL_Drivers'), os.path.join(library_dir, 'HAL_Drivers'))

    print("=> update Kconfig library path")
    update_kconfig_library_path(dist_dir)
