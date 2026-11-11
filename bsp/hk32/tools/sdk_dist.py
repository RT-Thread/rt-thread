import os


def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files

    print("=> copy hk32 libraries")
    bsp_copy_files(
        os.path.join(os.path.dirname(BSP_ROOT), 'libraries'),
        os.path.join(dist_dir, 'libraries'),
    )
