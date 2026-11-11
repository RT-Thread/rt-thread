import os


def update_dm_paths(dm_dir, dist_dir):
    components_dir = os.path.join(dist_dir, 'rt-thread', 'components')

    for root, dirs, files in os.walk(dm_dir):
        if 'SConscript' not in files:
            continue

        sconscript_path = os.path.join(root, 'SConscript')
        component_path = os.path.relpath(components_dir, root).replace(os.path.sep, '/')
        with open(sconscript_path, 'r') as f:
            data = f.read()

        data = data.replace('../../../../components', component_path)

        with open(sconscript_path, 'w') as f:
            f.write(data)


def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files

    dm_dir = os.path.join(os.path.dirname(dist_dir), 'dm')

    print("=> copy rockchip dm")
    bsp_copy_files(os.path.join(os.path.dirname(BSP_ROOT), 'dm'),
                   dm_dir)
    update_dm_paths(dm_dir, dist_dir)
