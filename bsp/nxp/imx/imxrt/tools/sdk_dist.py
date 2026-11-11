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

    data = data.replace('../../libraries', 'libraries')
    data = data.replace('../libraries', 'libraries')

    with open(kconfig_path, 'w') as f:
        f.write(data)


def update_sconstruct_library_path(dist_dir):
    sconstruct_path = os.path.join(dist_dir, 'SConstruct')
    if not os.path.isfile(sconstruct_path):
        return

    with open(sconstruct_path, 'r') as f:
        data = f.read()

    data = data.replace("SDK_ROOT = os.path.abspath('./..')",
                        "SDK_ROOT = os.path.abspath('./')")

    with open(sconstruct_path, 'w') as f:
        f.write(data)


# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir=None):
    from mkdist import bsp_copy_files
    import rtconfig
    
    if dist_dir is None:
        dist_dir  = os.path.join(BSP_ROOT, 'dist', os.path.basename(BSP_ROOT))

    print("=> copy imxrt bsp library")
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    if not os.path.isdir(library_path):
        library_path = os.path.join(os.path.dirname(os.path.dirname(BSP_ROOT)), 'libraries')
    library_dir  = os.path.join(dist_dir, 'libraries')
    
    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'drivers'), os.path.join(library_dir, 'drivers'))
    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))

    print("=> copy bsp peripherals")
    bsp_copy_files(os.path.join(library_path, 'peripherals'), os.path.join(library_dir, 'peripherals'))
    update_kconfig_library_path(dist_dir)
    update_sconstruct_library_path(dist_dir)
