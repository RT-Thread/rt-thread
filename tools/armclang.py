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
# 2018-09-9     liruncong    The first version

import os
import re
import platform 

def ARMLANG_GetRoot(rtconfig):
    root_path = os.path.join(rtconfig.EXEC_PATH, '..')
    return root_path

def ARMLANG_CheckHeader(rtconfig, filename):
    root = ARMLANG_GetRoot(rtconfig)

    fn = os.path.join(root, 'include', filename)
    if os.path.isfile(fn):
        return True

    return False

def ARMCLANG_Result(rtconfig, str):
    import subprocess

    result = ''

    def checkAndGetResult(pattern, string):
        if re.search(pattern, string):
            return re.search(pattern, string).group(0)
        return None

    armclang_cmd = os.path.join(rtconfig.EXEC_PATH, rtconfig.CC)

    # use temp file to get more information 
    f = file('__tmp.c', 'w')
    if f:
        f.write(str)
        f.close()

        # '-fdirectives-only', 
        if(platform.system() == 'Windows'):
            argstr = armclang_cmd + rtconfig.CFLAGS + ' -E -dD __tmp.c'
            args = argstr.split()
            child = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        else:
            print("Unsupported now!")
            sys.exit(1)
        
        stdout, stderr = child.communicate()

        #print(stdout)
        if stderr != '':
            print(stderr)

        os.remove('__tmp.c')

    return result

def ARMCLANG_GenerateConfig(rtconfig):
    str = ''
    cc_header = ''
    cc_header += '#ifndef CCONFIG_H__\n'
    cc_header += '#define CCONFIG_H__\n'
    cc_header += '/* Automatically generated file; DO NOT EDIT. */\n'
    cc_header += '/* compiler configure file for RT-Thread in GCC*/\n\n'

    if ARMLANG_CheckHeader(rtconfig, 'signal.h'):
        str += '#include <signal.h>\n'
        cc_header += '#define HAVE_SYS_SIGNAL_H 1\n'

    # if ARMLANG_CheckHeader(rtconfig, 'sys/dirent.h'):
    #    str += '#include <sys/dirent.h>\n'

    # add some common features
    str += 'const char* version = __VERSION__;\n'

    cc_header += '\n'
    cc_header += ARMCLANG_Result(rtconfig, str)
    cc_header += '\n#endif\n'

    cc_file = file('cconfig.h', 'w')
    if cc_file:
        cc_file.write(cc_header)
        cc_file.close()
