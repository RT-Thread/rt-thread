import os
import sys
import shutil

cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))


def update_dist_project_paths(dist_dir):
    sconstruct_path = os.path.join(dist_dir, 'SConstruct')
    if not os.path.isfile(sconstruct_path):
        return

    with open(sconstruct_path, 'r') as f:
        data = f.read()

    data = data.replace("os.path.join(libraries_path_prefix, 'STD_Drivers', 'SConscript')",
                        "os.path.join(libraries_path_prefix, 'Drivers', 'SConscript')")
    data = data.replace("variant_dir='../libraries/Drivers'",
                        "variant_dir='build/libraries/Drivers'")
    data = data.replace('variant_dir="../libraries/Drivers"',
                        'variant_dir="build/libraries/Drivers"')

    with open(sconstruct_path, 'w') as f:
        f.write(data)


# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    print("=> copy ft32 bsp library")
    library_dir = os.path.join(dist_dir, 'libraries')
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    if rtconfig.BSP_LIBRARY_TYPE is not None:
        bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE),
                       os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))

    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'Drivers'), os.path.join(library_dir, 'Drivers'))
    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))
    update_dist_project_paths(dist_dir)
