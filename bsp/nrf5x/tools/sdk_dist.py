import os
import sys
import shutil
cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))

# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    library_dir  = os.path.join(dist_dir, 'libraries')

    print("=> copy nrf52 bsp libraries")
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')

    bsp_copy_files(library_path, library_dir)
