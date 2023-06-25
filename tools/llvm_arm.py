#
# File      : llvm_arm.py
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
# 2023-05-17     Flybreak     The first version

import os
import re
import platform

def GetLLVM_ARMRoot(rtconfig):
    exec_path = rtconfig.EXEC_PATH
    lib_path = 'lib/clang-runtimes/arm-none-eabi'
    root_path = os.path.join(exec_path, '..', lib_path)

    return root_path

def CheckHeader(rtconfig, filename):
    root = GetLLVM_ARMRoot(rtconfig)
    config = re.findall(r"--config (.*)\.cfg", rtconfig.CFLAGS)
    if config:
        fn = os.path.join(root, config[0], 'include', filename)
        if os.path.isfile(fn):
            return True

    return False

def GetPicoLibcVersion(rtconfig):
    version = None
    root = GetLLVM_ARMRoot(rtconfig)
    if CheckHeader(rtconfig, 'picolibc.h'): # get version from picolibc.h file
        config = re.findall(r"--config (.*)\.cfg", rtconfig.CFLAGS)
        fn = os.path.join(root, config[0], 'include', 'picolibc.h')
        f = open(fn, 'r')
        if f:
            for line in f:
                if line.find('__PICOLIBC_VERSION__') != -1 and line.find('"') != -1:
                    version = re.search(r'\"([^"]+)\"', line).groups()[0]
            f.close()
    return version
