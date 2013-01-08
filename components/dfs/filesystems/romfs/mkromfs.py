import sys
import os
import string

basename = ''
output = ''

def mkromfs_output(out):
    # print '%s' % out,
    output.write(out)

def mkromfs_file(filename, arrayname):
    f = file(filename, "rb")
    arrayname = arrayname.replace('.', '_')
    arrayname = arrayname.replace('-', '_')
    mkromfs_output('const static unsigned char %s[] = {\n' % arrayname)

    count = 0
    while True:
        byte = f.read(1)

        if len(byte) != 1:
            break

        mkromfs_output('0x%02x,' % ord(byte))
        
        count = count + 1
        if count == 16:
            count = 0
            mkromfs_output('\n')
    
    if count == 0:
        mkromfs_output('};\n\n')
    else:
        mkromfs_output('\n};\n\n')

    f.close()

def mkromfs_dir(dirname, is_root = False):
    list = os.listdir(dirname)
    path = os.path.abspath(dirname)
    
    # make for directory 
    for item in list:
        fullpath = os.path.join(path, item)
        if os.path.isdir(fullpath):
            # if it is an empty directory, ignore it
            l = os.listdir(fullpath)
            if len(l):
                mkromfs_dir(fullpath)
    
    # make for files
    for item in list:
        fullpath = os.path.join(path, item)
        if os.path.isfile(fullpath):
            subpath = fullpath[len(basename):]
            array = subpath.split('\\')
            arrayname = string.join(array, '_')
            mkromfs_file(fullpath, arrayname)

    subpath = path[len(basename):]
    dir = subpath.split('\\')
    direntname = string.join(dir, '_')
    if is_root:
        mkromfs_output('const struct romfs_dirent _root_dirent[] = {\n')
    else:
        mkromfs_output(('const static struct romfs_dirent %s[] = {\n' % direntname))
    
    for item in list:
        fullpath = os.path.join(path, item)
        fn = fullpath[len(dirname):]
        if fn[0] == '\\':
            fn = fn[1:]
        fn = fn.replace('\\', '/')

        subpath = fullpath[len(basename):]
        items = subpath.split('\\')
        item_name = string.join(items, '_')
        item_name = item_name.replace('.', '_')
        item_name = item_name.replace('-', '_')
        subpath = subpath.replace('\\', '/')
        if subpath[0] == '/':
            subpath = subpath[1:]

        if not os.path.isfile(fullpath):
            l = os.listdir(fullpath)
            if len(l):
                mkromfs_output(('\t{ROMFS_DIRENT_DIR, "%s", (rt_uint8_t*) %s, sizeof(%s)/sizeof(%s[0])},\n' % (fn, item_name, item_name, item_name)))
            else:
                mkromfs_output(('\t{ROMFS_DIRENT_DIR, "%s", RT_NULL, 0},\n' % fn))

    for item in list:
        fullpath = os.path.join(path, item)
        fn = fullpath[len(dirname):]
        if fn[0] == '\\':
            fn = fn[1:]
        fn = fn.replace('\\', '/')
    
        subpath = fullpath[len(basename):]
        items = subpath.split('\\')
        item_name = string.join(items, '_')
        item_name = item_name.replace('.', '_')
        item_name = item_name.replace('-', '_')
        subpath = subpath.replace('\\', '/')
        if subpath[0] == '/':
            subpath = subpath[1:]
    
        if os.path.isfile(fullpath):
            mkromfs_output(('\t{ROMFS_DIRENT_FILE, "%s", %s, sizeof(%s)},\n' % (fn, item_name, item_name)))
    
    mkromfs_output('};\n\n')

if __name__ == "__main__":
    try:
        basename = os.path.abspath(sys.argv[1])
        filename = os.path.abspath(sys.argv[2])
    except IndexError:
        print "Usage: %s <dirname> <filename>" % sys.argv[0]
        raise SystemExit

    output = file(filename, 'wt')
    mkromfs_output("#include <dfs_romfs.h>\n\n")
    mkromfs_dir(basename, is_root = True)
    
    mkromfs_output("const struct romfs_dirent romfs_root = {ROMFS_DIRENT_DIR, \"/\", (rt_uint8_t*) _root_dirent, sizeof(_root_dirent)/sizeof(_root_dirent[0])};\n\n")
