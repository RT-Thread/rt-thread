import os
import sys
import shutil
cwd_path = os.getcwd()
sys.path.append(os.path.join(os.path.dirname(cwd_path), 'rt-thread', 'tools'))

def dist_modify_relative_path(board_kconfig_path):
    # Read in the file
    with open(board_kconfig_path, 'r') as file :
        filedata = file.read()

    # Replace the target string
    filedata = filedata.replace('$BSP_DIR/../libraries', './libraries')

    # Write the file out again
    with open(board_kconfig_path, 'w') as file:
        file.write(filedata)

# BSP dist function
def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files
    import rtconfig

    library_path = os.path.join(os.path.dirname(BSP_ROOT), 'libraries')
    library_dir  = os.path.join(dist_dir, 'libraries')

    print('=> copy nuvoton bsp drivers')
    bsp_copy_files(os.path.join(library_path, rtconfig.BSP_LIBRARY_TYPE), 
                   os.path.join(library_dir, rtconfig.BSP_LIBRARY_TYPE))

    print('=> copy nu_packages')
    bsp_copy_files(os.path.join(library_path, 'nu_packages'), 
                   os.path.join(library_dir, 'nu_packages'))

    print('=> copy Kconfig')
    shutil.copyfile(os.path.join(library_path, 'Kconfig'), os.path.join(library_dir, 'Kconfig'))

    print('=> Modify libraries relative path in board/Kconfig ')
    dist_modify_relative_path(os.path.join(dist_dir, 'board', 'Kconfig'))