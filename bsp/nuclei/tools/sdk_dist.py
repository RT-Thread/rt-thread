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

    print("=> copy nuclei bsp library")
    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    library_dir  = os.path.join(dist_dir, 'libraries')
    bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE), os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))
