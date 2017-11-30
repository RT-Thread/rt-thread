import os
import shutil

from shutil import ignore_patterns

def do_copy_file(src, dst):
    # check source file
    if not os.path.exists(src):
        return

    path = os.path.dirname(dst)
    # mkdir if path not exist
    if not os.path.exists(path):
        os.makedirs(path)

    shutil.copy2(src, dst)

def do_copy_folder(src_dir, dst_dir, ignore=None):
    import shutil
    # check source directory
    if not os.path.exists(src_dir):
        return

    try:
        if os.path.exists(dst_dir):
            shutil.rmtree(dst_dir)
    except:
        print('Deletes folder: %s failed.' % dst_dir)
        return

    shutil.copytree(src_dir, dst_dir, ignore = ignore)

source_ext = ["c", "h", "s", "S", "cpp", "xpm"]
source_list = []

def walk_children(child):
    global source_list
    global source_ext

    # print child
    full_path = child.rfile().abspath
    file_type  = full_path.rsplit('.',1)[1]
    #print file_type
    if file_type in source_ext:
        if full_path not in source_list:
            source_list.append(full_path)

    children = child.all_children()
    if children != []:
        for item in children:
            walk_children(item)

def walk_kconfig(RTT_ROOT, source_list):
    for parent, dirnames, filenames in os.walk(RTT_ROOT):
        if 'bsp' in parent:
            continue
        if '.git' in parent:
            continue
        if 'tools' in parent:
            continue

        if 'Kconfig' in filenames:
            pathfile = os.path.join(parent, 'Kconfig')
            source_list.append(pathfile)
        if 'KConfig' in filenames:
            pathfile = os.path.join(parent, 'KConfig')
            source_list.append(pathfile)


def MakeCopy(program, BSP_ROOT, RTT_ROOT, Env):
    global source_list

    target_path = os.path.join(BSP_ROOT, 'rt-thread')

    if target_path.startswith(RTT_ROOT):
        print('please use scons --dist to make a distribution')
        return

    for item in program:
        walk_children(item)

    source_list.sort()

    # fill source file in RT-Thread
    target_list = []
    for src in source_list:
        if Env['PLATFORM'] == 'win32':
            src = src.lower()

        if src.startswith(RTT_ROOT):
            target_list.append(src)

    source_list = target_list
    # get source directory
    src_dir = []
    for src in source_list:
        src = src.replace(RTT_ROOT, '')
        if src[0] == os.sep or src[0] == '/':
            src = src[1:]

        path = os.path.dirname(src)
        sub_path = path.split(os.sep)
        full_path = RTT_ROOT
        for item in sub_path:
            full_path = os.path.join(full_path, item)
            if full_path not in src_dir:
                src_dir.append(full_path)

    for item in src_dir:
        source_list.append(os.path.join(item, 'SConscript'))
    walk_kconfig(RTT_ROOT, source_list)

    for src in source_list:
        dst = src.replace(RTT_ROOT, '')
        if dst[0] == os.sep or dst[0] == '/':
            dst = dst[1:]
        print '=> ', dst
        dst = os.path.join(target_path, dst)
        do_copy_file(src, dst)

    # copy tools directory
    print("=> tools")
    do_copy_folder(os.path.join(RTT_ROOT, "tools"), os.path.join(target_path, "tools"), ignore_patterns('*.pyc'))
    do_copy_file(os.path.join(RTT_ROOT, 'Kconfig'), os.path.join(target_path, 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'AUTHORS'), os.path.join(target_path, 'AUTHORS'))
    do_copy_file(os.path.join(RTT_ROOT, 'COPYING'), os.path.join(target_path, 'COPYING'))
    do_copy_file(os.path.join(RTT_ROOT, 'README.md'), os.path.join(target_path, 'README.md'))
    do_copy_file(os.path.join(RTT_ROOT, 'README_zh.md'), os.path.join(target_path, 'README_zh.md'))
    print('=> libc')
    do_copy_folder(os.path.join(RTT_ROOT, "components", 'libc', 'compilers'), os.path.join(target_path, "components", 'libc', 'compilers'))

    print('done!')

def MakeCopyHeader(program, BSP_ROOT, RTT_ROOT, Env):
    global source_list
    global source_ext
    source_ext = []
    source_ext = ["h", "xpm"]

    target_path = os.path.join(BSP_ROOT, 'rt-thread')

    if target_path.startswith(RTT_ROOT):
        print('please use scons --dist to make a distribution')
        return

    for item in program:
        walk_children(item)

    source_list.sort()

    # fill source file in RT-Thread
    target_list = []
    for src in source_list:
        if Env['PLATFORM'] == 'win32':
            src = src.lower()

        if src.startswith(RTT_ROOT):
            target_list.append(src)

    source_list = target_list

    for src in source_list:
        dst = src.replace(RTT_ROOT, '')
        if dst[0] == os.sep or dst[0] == '/':
            dst = dst[1:]
        print '=> ', dst
        dst = os.path.join(target_path, dst)
        do_copy_file(src, dst)

    # copy tools directory
    print "=>  tools"
    do_copy_folder(os.path.join(RTT_ROOT, "tools"), os.path.join(target_path, "tools"), ignore_patterns('*.pyc'))
    do_copy_file(os.path.join(RTT_ROOT, 'Kconfig'), os.path.join(target_path, 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'AUTHORS'), os.path.join(target_path, 'AUTHORS'))
    do_copy_file(os.path.join(RTT_ROOT, 'COPYING'), os.path.join(target_path, 'COPYING'))
    do_copy_file(os.path.join(RTT_ROOT, 'README.md'), os.path.join(target_path, 'README.md'))
    do_copy_file(os.path.join(RTT_ROOT, 'README_zh.md'), os.path.join(target_path, 'README_zh.md'))

    print('done!')

def MkDist(program, BSP_ROOT, RTT_ROOT, Env):
    print("make distribution....")

    dist_name = os.path.basename(BSP_ROOT)
    dist_dir  = os.path.join(BSP_ROOT, 'dist', dist_name)

    # copy BSP files
    do_copy_folder(os.path.join(BSP_ROOT), dist_dir, 
        ignore_patterns('build', 'dist', '*.pyc', '*.old', '*.map', 'rtthread.bin', '.sconsign.dblite', '*.elf', '*.axf'))

    global source_list

    target_path = os.path.join(dist_dir, 'rt-thread')

    for item in program:
        walk_children(item)

    source_list.sort()

    # copy the source files in RT-Thread
    target_list = []
    for src in source_list:
        if src.lower().startswith(BSP_ROOT.lower()):
            continue
        
        if src.lower().startswith(RTT_ROOT.lower()):
            target_list.append(src)

    source_list = target_list

    # get source directory
    src_dir = []
    for src in source_list:
        src = src.replace(RTT_ROOT, '')
        if src[0] == os.sep or src[0] == '/':
            src = src[1:]

        path = os.path.dirname(src)
        sub_path = path.split(os.sep)
        full_path = RTT_ROOT
        for item in sub_path:
            full_path = os.path.join(full_path, item)
            if full_path not in src_dir:
                src_dir.append(full_path)

    for item in src_dir:
        source_list.append(os.path.join(item, 'SConscript'))

    # add all of Kconfig files
    walk_kconfig(RTT_ROOT, source_list)

    source_list.sort()
    for src in source_list:
        dst = src.replace(RTT_ROOT, '')
        if dst[0] == os.sep or dst[0] == '/':
            dst = dst[1:]

        print('=> %s' % dst)
        dst = os.path.join(target_path, dst)
        do_copy_file(src, dst)

    # copy tools directory
    print("=> tools")
    do_copy_folder(os.path.join(RTT_ROOT, "tools"), os.path.join(target_path, "tools"), ignore_patterns('*.pyc'))
    do_copy_file(os.path.join(RTT_ROOT, 'Kconfig'), os.path.join(target_path, 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'AUTHORS'), os.path.join(target_path, 'AUTHORS'))
    do_copy_file(os.path.join(RTT_ROOT, 'COPYING'), os.path.join(target_path, 'COPYING'))
    do_copy_file(os.path.join(RTT_ROOT, 'README.md'), os.path.join(target_path, 'README.md'))
    do_copy_file(os.path.join(RTT_ROOT, 'README_zh.md'), os.path.join(target_path, 'README_zh.md'))
    print('=> libc')
    do_copy_folder(os.path.join(RTT_ROOT, "components", 'libc', 'compilers'), os.path.join(target_path, "components", 'libc', 'compilers'))

    # change RTT_ROOT in SConstruct
    try:
        sconstruct = file(os.path.join(BSP_ROOT, 'SConstruct'))
        out = file(os.path.join(dist_dir, 'SConstruct'), 'w')

        for line in sconstruct:
            if line.find('RTT_ROOT') != -1:
                if line.find('sys.path') != -1:
                    out.write('# set RTT_ROOT\n')
                    out.write("if not os.getenv('RTT_ROOT'): \n    RTT_ROOT='rt-thread'\n\n")

            out.write(line)
    except :
        print('')

    # change RTT_ROOT in Kconfig
    try:
        if os.path.exists(os.path.join(BSP_ROOT, 'Kconfig')):
            Kconfig = file(os.path.join(BSP_ROOT, 'Kconfig'))
            out = file(os.path.join(dist_dir, 'Kconfig'), 'w')

            found = 0
            for line in Kconfig:
                if line.find('RTT_ROOT') != -1:
                    found = 1
                
                if line.find('default') != -1 and found:
                    position = line.find('default')
                    line = line[0:position] + 'default: "rt-thread"\n'
                    found = 0

                out.write(line)

            out.close()
    except :
        print('')

    # make zip package
    import zipfile
    
    zip_filename = os.path.join(BSP_ROOT, 'dist', dist_name)
    zip = zipfile.ZipFile(zip_filename + ".zip", 'w')
    pre_len = len(os.path.dirname(dist_dir))

    for parent, dirnames, filenames in os.walk(dist_dir):
        for filename in filenames:
            pathfile = os.path.join(parent, filename)
            arcname = pathfile[pre_len:].strip(os.path.sep)
            zip.write(pathfile, arcname)

    zip.close()

    print('done!')
