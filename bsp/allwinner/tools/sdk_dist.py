import os
import sys
import shutil

cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))


def update_kconfig_library_path(dist_dir):
    library_dir = os.path.join(dist_dir, 'libraries')
    if not os.path.isdir(library_dir):
        return

    for root, dirs, files in os.walk(library_dir):
        if 'Kconfig' not in files:
            continue

        kconfig_path = os.path.join(root, 'Kconfig')
        with open(kconfig_path, 'r') as f:
            data = f.read()

        data = data.replace('$(BSP_DIR)/../libraries', 'libraries')
        data = data.replace('$BSP_DIR/../libraries', 'libraries')
        data = data.replace('../libraries', 'libraries')

        with open(kconfig_path, 'w') as f:
            f.write(data)


# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    print("=> copy libraries")
    library_dir = os.path.join(dist_dir, 'libraries')
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE),
                   os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))

    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'drivers'), os.path.join(library_dir, 'drivers'))

    print("=> copy bsp libos")
    bsp_copy_files(os.path.join(library_path, 'libos'), os.path.join(library_dir, 'libos'))

    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))
    update_kconfig_library_path(dist_dir)
