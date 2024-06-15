#
# File      : gcc.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Change Logs:
# Date           Author       Notes
# 2018-05-22     Bernard      The first version
# 2023-11-03     idings       return file path in GetHeader

import os
import re
import platform
import subprocess

def GetGCCRoot(rtconfig):
    exec_path = rtconfig.EXEC_PATH
    prefix = rtconfig.PREFIX

    if prefix.endswith('-'):
        prefix = prefix[:-1]

    if exec_path == '/usr/bin':
        root_path = os.path.join('/usr/lib', prefix)
    else:
        root_path = os.path.join(exec_path, '..', prefix)

    return root_path

# https://stackoverflow.com/questions/4980819/what-are-the-gcc-default-include-directories
# https://stackoverflow.com/questions/53937211/how-can-i-parse-gcc-output-by-regex-to-get-default-include-paths
def match_pattern(pattern, input, start = 0, stop = -1, flags = 0):
    length = len(input)

    if length == 0:
        return None

    end_it = max(0, length - 1)

    if start >= end_it:
        return None

    if stop<0:
        stop = length

    if stop <= start:
        return None

    for it in range(max(0, start), min(stop, length)):
        elem = input[it]
        match = re.match(pattern, elem, flags)
        if match:
            return it

def GetGccDefaultSearchDirs(rtconfig):
    start_pattern = r' *#include <\.\.\.> search starts here: *'
    end_pattern = r' *End of search list\. *'

    gcc_cmd = os.path.join(rtconfig.EXEC_PATH, rtconfig.CC)
    device_flags = rtconfig.DEVICE.split()
    command = [gcc_cmd] + device_flags + ['-xc', '-E', '-v', os.devnull]

    # if gcc_cmd can not access , return empty list
    if not os.access(gcc_cmd, os.X_OK):
        return []

    if(platform.system() == 'Windows'):
        child = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    else:
        child = subprocess.Popen(' '.join(command), stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)

    stdout = child.communicate()
    stdout_string = (b''.join(stdout)).decode()
    lines = stdout_string.splitlines()

    start_it = match_pattern(start_pattern, lines)
    if start_it == None:
        return []

    end_it = match_pattern(end_pattern, lines, start_it)
    if end_it == None:
        return []

    # theres no paths between them
    if (end_it - start_it) == 1:
        return []

    return lines[start_it + 1 : end_it]

def GetHeader(rtconfig, filename):
    include_dirs = GetGccDefaultSearchDirs(rtconfig)
    for directory in include_dirs:
        fn = os.path.join(directory, filename).strip()
        if os.path.isfile(fn):
            return fn

    # fallback to use fixed method if can't autodetect
    root = GetGCCRoot(rtconfig)
    fn = os.path.join(root, 'include', filename)
    if os.path.isfile(fn):
        return fn

    # Usually the cross compiling gcc toolchain has directory as:
    #
    # bin
    # lib
    # share
    # arm-none-eabi
    #    bin
    #    include
    #    lib
    #    share
    prefix = rtconfig.PREFIX
    if prefix.endswith('-'):
        prefix = prefix[:-1]

    fn = os.path.join(root, prefix, 'include', filename)
    if os.path.isfile(fn):
        return fn

    return None

# GCC like means the toolchains which are compatible with GCC
def GetGCCLikePLATFORM():
    return ['gcc', 'armclang', 'llvm-arm']

def GetPicoLibcVersion(rtconfig):
    version = None
    try:
        rtconfig.PREFIX
    except:
        return version

    # get version from picolibc.h
    fn = GetHeader(rtconfig, 'picolibc.h')

    if fn:
        f = open(fn, 'r')
        if f:
            for line in f:
                if line.find('__PICOLIBC_VERSION__') != -1 and line.find('"') != -1:
                    version = re.search(r'\"([^"]+)\"', line).groups()[0]
            f.close()

    return version

def GetNewLibVersion(rtconfig):
    version = None

    try:
        rtconfig.PREFIX
    except:
        return version

    # if find picolibc.h, use picolibc
    fn = GetHeader(rtconfig, 'picolibc.h')
    if fn:
        return version

    # get version from _newlib_version.h file
    fn = GetHeader(rtconfig, '_newlib_version.h')

    # get version from newlib.h
    if not fn:
        fn = GetHeader(rtconfig, 'newlib.h')

    if fn:
        f = open(fn, 'r')
        for line in f:
            if line.find('_NEWLIB_VERSION') != -1 and line.find('"') != -1:
                version = re.search(r'\"([^"]+)\"', line).groups()[0]
        f.close()

    return version

# FIXME: there is no musl version or musl macros can be found officially
def GetMuslVersion(rtconfig):
    version = None

    try:
        rtconfig.PREFIX
    except:
        return version

    if 'musl' in rtconfig.PREFIX:
        version = 'unknown'
    return version

def GCCResult(rtconfig, str):
    result = ''

    def checkAndGetResult(pattern, string):
        if re.search(pattern, string):
            return re.search(pattern, string).group(0)
        return None

    gcc_cmd = os.path.join(rtconfig.EXEC_PATH, rtconfig.CC)

    # use temp file to get more information
    f = open('__tmp.c', 'w')
    if f:
        f.write(str)
        f.close()

        # '-fdirectives-only',
        if(platform.system() == 'Windows'):
            child = subprocess.Popen([gcc_cmd, '-E', '-P', '__tmp.c'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        else:
            child = subprocess.Popen(gcc_cmd + ' -E -P __tmp.c', stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)

        stdout, stderr = child.communicate()

        # print(stdout)
        if stderr != '' and stderr != b'':
            print(stderr)

        have_fdset = 0
        have_sigaction = 0
        have_sigevent = 0
        have_siginfo = 0
        have_sigval = 0
        version = None
        stdc = '1989'
        posix_thread = 0

        for line in stdout.split(b'\n'):
            line = line.decode()
            if re.search('fd_set', line):
                have_fdset = 1

            # check for sigal
            if re.search('struct[ \t]+sigaction', line):
                have_sigaction = 1
            if re.search('struct[ \t]+sigevent', line):
                have_sigevent = 1
            if re.search('siginfo_t', line):
                have_siginfo = 1
            if re.search('union[ \t]+sigval', line):
                have_sigval = 1

            if re.search(r'char\* version', line):
                version = re.search(r'"([^"]+)"', line).groups()[0]

            if re.findall(r'iso_c_visible = \d+', line):
                stdc = re.findall(r'\d+', line)[0]

            if re.findall('pthread_create', line):
                posix_thread = 1

        if have_fdset:
            result += '#define HAVE_FDSET 1\n'

        if have_sigaction:
            result += '#define HAVE_SIGACTION 1\n'
        if have_sigevent:
            result += '#define HAVE_SIGEVENT 1\n'
        if have_siginfo:
            result += '#define HAVE_SIGINFO 1\n'
        if have_sigval:
            result += '#define HAVE_SIGVAL 1\n'

        if version:
            result += '#define GCC_VERSION_STR "%s"\n' % version

        result += '#define STDC "%s"\n' % stdc

        if posix_thread:
            result += '#define LIBC_POSIX_THREADS 1\n'

        os.remove('__tmp.c')
    return result
