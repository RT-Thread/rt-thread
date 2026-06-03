import os


def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files

    print("=> copy raspberry-pico drivers")
    bsp_copy_files(
        os.path.join(os.path.dirname(BSP_ROOT), 'libraries', 'Drivers'),
        os.path.join(os.path.dirname(dist_dir), 'libraries', 'Drivers'),
    )
