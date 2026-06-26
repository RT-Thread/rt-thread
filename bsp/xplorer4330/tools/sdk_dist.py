import os


def update_sconscript_path(dist_dir):
    sconscript_path = os.path.join(dist_dir, 'SConscript')
    if not os.path.isfile(sconscript_path):
        return

    with open(sconscript_path, 'r') as f:
        data = f.read()

    data = data.replace("if (d != 'M4' and d != 'M0'):",
                        "if (d != 'M4' and d != 'M0' and d != 'project'):")

    with open(sconscript_path, 'w') as f:
        f.write(data)


def dist_do_building(BSP_ROOT, dist_dir):
    from mkdist import bsp_copy_files

    dist_root = os.path.dirname(dist_dir)
    bsp_root = os.path.dirname(BSP_ROOT)

    for dirname in ['applications', 'drivers', 'Libraries']:
        print("=> copy xplorer4330 %s" % dirname)
        bsp_copy_files(os.path.join(bsp_root, dirname), os.path.join(dist_root, dirname))

    update_sconscript_path(dist_dir)
