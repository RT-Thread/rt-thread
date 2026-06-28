import os
import sys
import shutil
cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))

def update_rtt_root_path(path):
    if not os.path.isfile(path):
        return

    with open(path, 'r') as f:
        data = f.read()

    data = data.replace("RTT_ROOT = os.path.normpath(os.getcwd() + '/../../..')",
                        "RTT_ROOT = os.path.join(os.getcwd(), 'rt-thread')")
    data = data.replace('RTT_ROOT = os.path.normpath(os.getcwd() + "/../../..")',
                        "RTT_ROOT = os.path.join(os.getcwd(), 'rt-thread')")

    with open(path, 'w') as f:
        f.write(data)


def update_dist_project_paths(dist_dir):
    update_rtt_root_path(os.path.join(dist_dir, 'SConstruct'))
    update_rtt_root_path(os.path.join(dist_dir, 'rtconfig.py'))

    kconfig_path = os.path.join(dist_dir, 'Kconfig')
    if os.path.isfile(kconfig_path):
        with open(kconfig_path, 'r') as f:
            data = f.read()

        data = data.replace('rsource "../libraries/Kconfig"',
                            'rsource "libraries/Kconfig"')

        with open(kconfig_path, 'w') as f:
            f.write(data)

# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    library_dir  = os.path.join(dist_dir, 'libraries')

    print("=> copy HPMicro bsp libraries")
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')

    bsp_copy_files(library_path, library_dir)
    update_dist_project_paths(dist_dir)
