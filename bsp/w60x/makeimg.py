# -*- coding: utf-8 -*-  

import os
import sys
import shutil
import subprocess
import time
import platform

# if debug_info=True, Debugging Print Information will be turned on
debug_info=False
# if make_fal=True, Partition tables are put into firmware
make_fal=False
# Setting firmware output directory
out_path='./Bin'
# Setting the bin file path
bin_file='./rtthread.bin'
# Setting winnermicro libraries path
wmlib_path='./packages/wm_libraries-'
# Setting the 1M flash layout file
layout_1M_file='.'
# Setting the 2M flash layout file
layout_2M_file='.'
# Setting the makeimg by adding rtt flash original fls
makeimg_new_fls='.'

def execute_command(cmdstring, cwd=None, shell=True):
    """Execute the system command at the specified address."""

    if shell:
        cmdstring_list = cmdstring

    sub = subprocess.Popen(cmdstring_list, cwd=cwd, stdin=subprocess.PIPE,
                           stdout=subprocess.PIPE, shell=shell, bufsize=8192)

    stdout_str = ""
    while sub.poll() is None:
        stdout_str += str(sub.stdout.read())
        time.sleep(0.1)

    return stdout_str

def copy_file(name, path):
    res = True
    if os.path.exists(path):
        shutil.copy(path, out_path)
    else:
        print('makeimg err! No ' + name + ' file found: ' + path)
        res = False
    return res

def is_exists(name, path):
    res = True
    if not os.path.exists(path):
        print('makeimg err! No ' + name + ' file found: ' + path)
        res = False
    return res

def get_exec_path(path):
    (file_path, file_name) = os.path.split(path)
    (name, extend) = os.path.splitext(file_name)

    exec_path = ''
    if (platform.system() == "Windows"):
        exec_path = os.path.abspath(file_path + '/' + name + '.exe')
    elif (platform.system() == "Linux"):
        exec_path = os.path.abspath(file_path + '/' + name)

    if debug_info:
        print('file_path: ' + file_path)
        print('file_name: ' + file_name)
        print('name: ' + name)
        print('extend: ' + extend)

    return exec_path

def do_makeimg(tool_path, param):
    str = "\"" + tool_path +  "\"" + ' ' + param
    if debug_info:
        print('exec cmd: ' + str);

    execute_command(str)

def get_wmlib_path_full(path):
    (_wmlib_path,_wmlib_name) = os.path.split(path)
    files = os.listdir(_wmlib_path)
    for f in files:
        if _wmlib_name in f:
            return _wmlib_path + '/' + f
    return path

if __name__=='__main__':
    # find winnermicro libraries full path
    wmlib_path_full = get_wmlib_path_full(wmlib_path)
    # Setting the version.txt file path
    version_file=wmlib_path_full + '/Tools/version.txt'
    # Setting the secboot.img file path
    secboot_file=wmlib_path_full + '/Tools/secboot.img'
    # Setting the wm_gzip.exe file path
    wm_gzip_file=wmlib_path_full + '/Tools/wm_gzip.exe'
    # Setting the makeimg.exe file path
    makeimg_file=wmlib_path_full + '/Tools/makeimg.exe'
    # Setting the makeimg_all.exe file path
    makeimg_all_file=wmlib_path_full + '/Tools/makeimg_all.exe'

    if (platform.system() == "Linux"):
        wm_gzip_file=wmlib_path_full + '/Tools/wm_gzip.py'
        makeimg_file=wmlib_path_full + '/Tools/makeimg'
        makeimg_all_file=wmlib_path_full + '/Tools/makeimg_all'

    # Get absolute path
    out_path = os.path.abspath(out_path).replace('\\', '/');
    bin_file = os.path.abspath(bin_file).replace('\\', '/');
    version_file = os.path.abspath(version_file).replace('\\', '/');
    secboot_file = os.path.abspath(secboot_file).replace('\\', '/');
    wm_gzip_file = os.path.abspath(wm_gzip_file).replace('\\', '/');
    makeimg_file = os.path.abspath(makeimg_file).replace('\\', '/');
    makeimg_all_file = os.path.abspath(makeimg_all_file).replace('\\', '/');

    # Create the output directory
    if not os.path.exists(out_path): os.mkdir(out_path)

    # Copy file
    if not copy_file('bin', bin_file): exit(0)
    if not copy_file('version', version_file): exit(0)
    if not copy_file('secboot', secboot_file): exit(0)

    # Check the existence of packaging tools
    if not is_exists('wm_gzip', wm_gzip_file): exit(0)
    if not is_exists('makeimg', makeimg_file): exit(0)
    if not is_exists('makeimg_all', makeimg_all_file): exit(0)

    # Get File Names and File Extensions
    (bin_file_path,bin_file_name) = os.path.split(bin_file)
    (bin_name,bin_extend) = os.path.splitext(bin_file_name)
    (version_file_path,version_file_name) = os.path.split(version_file)
    (secboot_file_path,secboot_file_name) = os.path.split(secboot_file)

    # print debug Information
    if debug_info: print('bin_file_name:' + bin_file_name + 'bin_name:' + bin_name + 'bin_extend:' + bin_extend + 'version_file_name:' + version_file_name + 'secboot_file_name:' + secboot_file_name)

    print('makeimg 1M Flash...')
    file_pos_1M='_1M'
    gzip_param = "\"" + out_path + '/' + bin_file_name + "\""
    make_img_param = "\"" + out_path + '/' + bin_file_name + "\"" + ' ' + "\"" + out_path + '/' + bin_name + file_pos_1M + '.img' + "\"" + ' 0' + ' 0' + ' ' + "\"" + out_path + '/' + version_file_name + "\"" + ' 90000' + ' 10100'
    make_GZ_param = "\"" + out_path + '/' + bin_file_name + '.gz' + "\"" + ' ' + "\"" + out_path + '/' + bin_name + '_GZ' + file_pos_1M + '.img' +"\"" + ' 0' + ' 1' + ' ' + "\"" + out_path + '/' + version_file_name + "\"" + ' 90000' + ' 10100' + ' ' + "\"" + out_path + '/' + bin_file_name + "\""
    make_SEC_param = "\"" + out_path + '/' + bin_file_name + "\"" + ' ' + "\"" + out_path + '/' + bin_name + '_SEC' + file_pos_1M + '.img' + "\"" + ' 0' + ' 0' + ' ' + "\"" + out_path + '/' + version_file_name + "\"" + ' 90000' + ' 10100'
    make_FLS_param = "\"" + out_path + '/' + secboot_file_name + "\"" + ' ' + "\"" + out_path + '/' + bin_name + file_pos_1M + '.img' + "\"" + ' ' + "\"" + out_path + '/' + bin_name + file_pos_1M + '.FLS' + "\""

    if debug_info:
        print('gzip_param' + gzip_param)
        print('make_img_param' + make_img_param)
        print('make_GZ_param' + make_GZ_param)
        print('make_SEC_param' + make_SEC_param)
        print('make_FLS_param' + make_FLS_param)

    if (platform.system() == "Linux"):
        do_makeimg("python",wm_gzip_file + " " + gzip_param)
    else:
        do_makeimg(wm_gzip_file, gzip_param)
    do_makeimg(makeimg_file, make_img_param)
    do_makeimg(makeimg_file, make_GZ_param)
    do_makeimg(makeimg_file, make_SEC_param)
    do_makeimg(makeimg_all_file, make_FLS_param)

    rm_file = out_path + '/' + bin_name + file_pos_1M + '.img'
    if os.path.exists(rm_file):
        os.remove(rm_file)
    rm_file = out_path + '/' + bin_file_name + '.gz'
    if os.path.exists(rm_file):
        os.remove(rm_file)

    print('makeimg 2M Flash...')
    file_pos_2M='_2M'
    gzip_param = "\"" + out_path + '/' + bin_file_name + "\""
    make_img_param = "\"" + out_path + '/' + bin_file_name + "\"" + ' ' + "\"" + out_path + '/' + bin_name + file_pos_2M + '.img' + "\"" + ' 3' + ' 0' + ' ' + "\"" + out_path + '/' + version_file_name + "\"" + ' 100000' + ' 10100'
    make_GZ_param = "\"" + out_path + '/' + bin_file_name + '.gz' + "\"" + ' ' + "\"" + out_path + '/' + bin_name + '_GZ' + file_pos_2M + '.img' +"\"" + ' 3' + ' 1' + ' ' + "\"" + out_path + '/' + version_file_name + "\"" + ' 100000' + ' 10100' + ' ' + "\"" + out_path + '/' + bin_file_name + "\""
    make_SEC_param = "\"" + out_path + '/' + bin_file_name + "\"" + ' ' + "\"" + out_path + '/' + bin_name + '_SEC' + file_pos_2M + '.img' + "\"" + ' 3' + ' 0' + ' ' + "\"" + out_path + '/' + version_file_name + "\"" + ' 100000' + ' 10100'
    make_FLS_param = "\"" + out_path + '/' + secboot_file_name + "\"" + ' ' + "\"" + out_path + '/' + bin_name + file_pos_2M + '.img' + "\"" + ' ' + "\"" + out_path + '/' + bin_name + file_pos_2M + '.FLS' + "\""

    if debug_info:
        print('gzip_param' + gzip_param)
        print('make_img_param' + make_img_param)
        print('make_GZ_param' + make_GZ_param)
        print('make_SEC_param' + make_SEC_param)
        print('make_FLS_param' + make_FLS_param)

    if (platform.system() == "Linux"):
        do_makeimg("python",wm_gzip_file + " " + gzip_param)
    else:
        do_makeimg(wm_gzip_file, gzip_param)
    do_makeimg(makeimg_file, make_img_param)
    do_makeimg(makeimg_file, make_GZ_param)
    do_makeimg(makeimg_file, make_SEC_param)
    do_makeimg(makeimg_all_file, make_FLS_param)

    rm_file = out_path + '/' + bin_name + file_pos_2M + '.img'
    if os.path.exists(rm_file):
        os.remove(rm_file)
    rm_file = out_path + '/' + bin_file_name + '.gz'
    if os.path.exists(rm_file):
        os.remove(rm_file)

    if make_fal:
        # Get absolute path
        layout_1M_file = os.path.abspath(layout_1M_file).replace('\\', '/');
        layout_2M_file = os.path.abspath(layout_2M_file).replace('\\', '/');
        makeimg_new_fls = os.path.abspath(makeimg_new_fls).replace('\\', '/');

        # Create command parameters to new fls
        makeimg_new_cmd="\"" + out_path + '/' + bin_name + file_pos_1M + '.FLS' + "\"" + ' ' + "\"" + layout_1M_file + "\"" + ' ' + "\"" + out_path + '/'+ bin_name + '_layout' + file_pos_1M+'.FLS' +"\""
        do_makeimg(makeimg_new_fls, makeimg_new_cmd)

        makeimg_new_cmd="\"" + out_path + '/' + bin_name + file_pos_2M + '.FLS' + "\"" + ' ' + "\"" + layout_2M_file + "\"" + ' ' + "\"" + out_path + '/'+ bin_name + '_layout' + file_pos_2M+'.FLS' +"\""
        do_makeimg(makeimg_new_fls, makeimg_new_cmd)

        # Delete temporary files
        rm_file = out_path + '/' + bin_name + file_pos_1M + '.FLS'
        if os.path.exists(rm_file):
            os.remove(rm_file)
        rm_file = out_path + '/' + bin_name + file_pos_2M + '.FLS'
        if os.path.exists(rm_file):
            os.remove(rm_file)

    print('end')
