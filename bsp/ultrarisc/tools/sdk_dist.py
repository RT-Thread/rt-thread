import os


def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files

    dist_root = os.path.dirname(dist_dir)

    print("=> copy ultrarisc drivers")
    bsp_copy_files(os.path.join(os.path.dirname(BSP_ROOT), 'drivers'), os.path.join(dist_root, 'drivers'))

    print("=> copy ultrarisc arch")
    bsp_copy_files(os.path.join(os.path.dirname(BSP_ROOT), 'arch'), os.path.join(dist_root, 'arch'))
