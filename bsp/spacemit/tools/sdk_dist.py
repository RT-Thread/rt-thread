#
# Copyright (c) 2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#

import os

def update_dm_paths(dm_dir, dist_dir):
    components_dir = os.path.join(dist_dir, 'rt-thread', 'components')

    for root, _, files in os.walk(dm_dir):
        if 'SConscript' not in files:
            continue

        sconscript_path = os.path.join(root, 'SConscript')
        component_path = os.path.relpath(components_dir, root).replace(os.path.sep, '/')

        with open(sconscript_path, 'r') as f:
            data = f.read()

        data = data.replace('../../../../components', component_path)

        with open(sconscript_path, 'w') as f:
            f.write(data)


def update_dm_kconfig_paths(dm_dir):
    for root, _, files in os.walk(dm_dir):
        for name in files:
            if not name.startswith('Kconfig'):
                continue

            path = os.path.join(root, name)
            with open(path, 'r') as f:
                data = f.read()

            data = data.replace('../dm/', 'dm/')

            with open(path, 'w') as f:
                f.write(data)


def update_bsp_sconscript(dist_dir):
    sconscript_path = os.path.join(dist_dir, 'SConscript')

    with open(sconscript_path, 'r') as f:
        data = f.read()

    data = data.replace("cwd + '/../dm/SConscript', variant_dir = 'dm'",
                        "cwd + '/dm/SConscript', variant_dir = 'dm-build'")
    data = data.replace('for d in list:\n',
                        "for d in list:\n    if d == 'dm':\n        continue\n")

    with open(sconscript_path, 'w') as f:
        f.write(data)


def update_bsp_paths(dist_dir):
    for name in ('Kconfig', '.config', 'rtconfig.h'):
        path = os.path.join(dist_dir, name)

        with open(path, 'r') as f:
            data = f.read()

        data = data.replace('../dm/', 'dm/')

        with open(path, 'w') as f:
            f.write(data)


def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files, do_copy_file

    dm_dir = os.path.join(dist_dir, 'dm')

    print('=> copy spacemit dm')
    bsp_copy_files(os.path.join(os.path.dirname(BSP_ROOT), 'dm'), dm_dir)
    do_copy_file(os.path.join(BSP_ROOT, 'drivers', 'esos.elf'),
                 os.path.join(dist_dir, 'drivers', 'esos.elf'))
    update_dm_paths(dm_dir, dist_dir)
    update_dm_kconfig_paths(dm_dir)
    update_bsp_sconscript(dist_dir)
    update_bsp_paths(dist_dir)
