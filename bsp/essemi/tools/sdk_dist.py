import os


def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files

    print("=> copy es32f369x libraries")
    bsp_copy_files(
        os.path.join(os.path.dirname(BSP_ROOT), 'es32f369x'),
        os.path.join(os.path.dirname(dist_dir), 'es32f369x'),
    )
