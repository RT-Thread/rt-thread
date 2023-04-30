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

import os
import re
import platform

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

def CheckHeader(rtconfig, filename):
    root = GetGCCRoot(rtconfig)

    fn = os.path.join(root, 'include', filename)
    if os.path.isfile(fn):
        return True

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
        return True

    return False

def GetNewLibVersion(rtconfig):
    version = None
    root = GetGCCRoot(rtconfig)
    if CheckHeader(rtconfig, '_newlib_version.h'): # get version from _newlib_version.h file
        f = open(os.path.join(root, 'include', '_newlib_version.h'), 'r')
        if f:
            for line in f:
                if line.find('_NEWLIB_VERSION') != -1 and line.find('"') != -1:
                    version = re.search(r'\"([^"]+)\"', line).groups()[0]
            f.close()
    elif CheckHeader(rtconfig, 'newlib.h'): # get version from newlib.h
        f = open(os.path.join(root, 'include', 'newlib.h'), 'r')
        if f:
            for line in f:
                if line.find('_NEWLIB_VERSION') != -1 and line.find('"') != -1:
                    version = re.search(r'\"([^"]+)\"', line).groups()[0]
            f.close()
    return version

# FIXME: there is no musl version or musl macros can be found officially
def GetMuslVersion(rtconfig):
    version = None
    if 'musl' in rtconfig.PREFIX:
        version = 'unknown'
    return version

def GCCResult(rtconfig, str):
    import subprocess

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

            if re.search('char\* version', line):
                version = re.search(r'\"([^"]+)\"', line).groups()[0]

            if re.findall('iso_c_visible = [\d]+', line):
                stdc = re.findall('[\d]+', line)[0]

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

def GenerateGCCConfig(rtconfig):
    # The cconfig.h will NOT generate in the lastest RT-Thread code.
    # When you want to use it, you can uncomment out the following code.

    # str = ''
    # cc_header = ''
    # cc_header += '#ifndef CCONFIG_H__\n'
    # cc_header += '#define CCONFIG_H__\n'
    # cc_header += '/* Automatically generated file; DO NOT EDIT. */\n'
    # cc_header += '/* compiler configure file for RT-Thread in GCC*/\n\n'

    # if CheckHeader(rtconfig, 'newlib.h'):
    #     str += '#include <newlib.h>\n'
    #     cc_header += '#define HAVE_NEWLIB_H 1\n'
    #     cc_header += '#define LIBC_VERSION "newlib %s"\n\n' % GetNewLibVersion(rtconfig)

    # if CheckHeader(rtconfig, 'sys/signal.h'):
    #     str += '#include <sys/signal.h>\n'
    #     cc_header += '#define HAVE_SYS_SIGNAL_H 1\n'
    # if CheckHeader(rtconfig, 'sys/select.h'):
    #     str += '#include <sys/select.h>\n'
    #     cc_header += '#define HAVE_SYS_SELECT_H 1\n'
    # if CheckHeader(rtconfig, 'pthread.h'):
    #     str += "#include <pthread.h>\n"
    #     cc_header += '#define HAVE_PTHREAD_H 1\n'

    # # if CheckHeader(rtconfig, 'sys/dirent.h'):
    # #    str += '#include <sys/dirent.h>\n'

    # # add some common features
    # str += 'const char* version = __VERSION__;\n'
    # str += 'const int iso_c_visible = __ISO_C_VISIBLE;\n'
    # str += '\n#ifdef HAVE_INITFINI_ARRAY\n'
    # str += 'const int init_fini_array = HAVE_INITFINI_ARRAY;\n'
    # str += '#endif\n'

    # cc_header += '\n'
    # cc_header += GCCResult(rtconfig, str)
    # cc_header += '\n#endif\n'

    # cc_file = open('cconfig.h', 'w')
    # if cc_file:
    #     cc_file.write(cc_header)
    #     cc_file.close()
    pass
