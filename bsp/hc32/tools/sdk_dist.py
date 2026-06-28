import os
import sys
import shutil

cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))


def update_dist_project_paths(dist_dir):
    tests_sconscript = os.path.join(os.path.dirname(dist_dir), 'tests', 'SConscript')
    if os.path.isfile(tests_sconscript):
        with open(tests_sconscript, 'r') as f:
            data = f.read()

        data = data.replace('../../../components', '../project/rt-thread/components')

        with open(tests_sconscript, 'w') as f:
            f.write(data)


# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    print("=> copy hc32 bsp library")
    library_dir = os.path.join(dist_dir, 'libraries')
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    if rtconfig.BSP_LIBRARY_TYPE is not None:
        bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE),
                    os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))

    print("=> copy bsp drivers")
    bsp_copy_files(os.path.join(library_path, 'hc32_drivers'), os.path.join(library_dir, 'hc32_drivers'))
    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))

    print("=> copy hc32 platform")
    bsp_copy_files(os.path.join(os.path.dirname(BSP_ROOT), 'platform'), os.path.join(os.path.dirname(dist_dir), 'platform'))

    print("=> copy hc32 tests")
    bsp_copy_files(os.path.join(os.path.dirname(BSP_ROOT), 'tests'), os.path.join(os.path.dirname(dist_dir), 'tests'))
    update_dist_project_paths(dist_dir)
