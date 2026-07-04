#
# File      : makefile.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
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
# 2015-01-20     Bernard      Add copyright information

import os
import sys

# Add parent directory to path to import utils
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from utils import *
from utils import _make_path_relative
import rtconfig

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__))))
import target_utils

makefile = '''phony := all
all:

include config.mk

ifneq ($(MAKE_LIB),1)
TARGET := rtthread.elf
include src.mk
endif

$(if $(strip $(RTT_ROOT)),,$(error RTT_ROOT not defined))

include $(RTT_ROOT)/tools/rtthread.mk
'''

def TargetMakefile(env):
    project = ProjectInfo(env)

    BSP_ROOT = os.path.abspath(env['BSP_ROOT'])
    RTT_ROOT = os.path.abspath(env['RTT_ROOT'])

    match_bsp = False
    if BSP_ROOT.startswith(RTT_ROOT):
        match_bsp = True

    make = open('config.mk', 'w')

    make.write('BSP_ROOT ?= %s\n' % BSP_ROOT.replace('\\', '/'))
    make.write('RTT_ROOT ?= %s\n' % RTT_ROOT.replace('\\', '/'))
    make.write('\n')

    cross = os.path.abspath(rtconfig.EXEC_PATH)
    cross = os.path.join(cross, rtconfig.PREFIX)
    make.write('CROSS_COMPILE ?=%s' % cross.replace('\\', '\\\\'))
    make.write('\n')
    make.write('\n')

    make.write('CFLAGS :=%s' % (rtconfig.CFLAGS))
    make.write('\n')
    make.write('AFLAGS :=%s' % (rtconfig.AFLAGS))
    make.write('\n')
    make.write('LFLAGS :=%s' % (rtconfig.LFLAGS))
    make.write('\n')
    if 'CXXFLAGS' in dir(rtconfig):
        make.write('CXXFLAGS :=%s' % (rtconfig.CXXFLAGS))
        make.write('\n')
    if ('LIBS' in env):
        make.write('EXTERN_LIB := ')
        for tlib in env['LIBS']:
            # quote so a lib name / path with a space cannot break the recipe
            make.write('-l%s ' % target_utils.make_quote(tlib))
        if ('LIBPATH' in env):
            for tlibpath in env['LIBPATH']:
                make.write('-L%s ' % target_utils.make_quote(tlibpath))
        make.write('\n')

    make.write('\n')

    Files   = project['FILES']
    Headers = project['HEADERS']
    CPPDEFINES = project['CPPDEFINES']

    paths = [os.path.normpath(i) for i in project['CPPPATH']]
    CPPPATH = []
    for path in paths:
        fn = os.path.normpath(path)
        if match_bsp:
            if fn.startswith(BSP_ROOT):
                fn = '$(BSP_ROOT)' + fn.replace(BSP_ROOT, '')
            elif fn.startswith(RTT_ROOT):
                fn = '$(RTT_ROOT)' + fn.replace(RTT_ROOT, '')
        else:
            if fn.startswith(RTT_ROOT):
                fn = '$(RTT_ROOT)' + fn.replace(RTT_ROOT, '')
            elif fn.startswith(BSP_ROOT):
                fn = '$(BSP_ROOT)' + fn.replace(BSP_ROOT, '')

        CPPPATH.append(fn)

    path = ''
    paths = CPPPATH
    for item in paths:
        # make_quote escapes spaces / '#' but keeps the $(BSP_ROOT) prefix intact
        path += '\t-I%s \\\n' % target_utils.make_quote(item)

    make.write('CPPPATHS :=')
    if path[0] == '\t': path = path[1:]
    length = len(path)
    if path[length - 2] == '\\': path = path[:length - 2]
    make.write(path)
    make.write('\n')
    make.write('\n')

    # -D<macro> list, make-quoted so a value with a space cannot split the flag
    define_flags = ['-D' + d for d in target_utils.normalize_defines(project['CPPDEFINES'])]
    make.write('DEFINES :=')
    if define_flags:
        make.write(' ' + target_utils.make_join(define_flags))
    make.write('\n')

    files = Files
    Files = []
    for file in files:
        fn = os.path.normpath(file)
        if match_bsp:
            if fn.startswith(BSP_ROOT):
                fn = '$(BSP_ROOT)' + fn.replace(BSP_ROOT, '')
            elif fn.startswith(RTT_ROOT):
                fn = '$(RTT_ROOT)' + fn.replace(RTT_ROOT, '')
        else:
            if fn.startswith(RTT_ROOT):
                fn = '$(RTT_ROOT)' + fn.replace(RTT_ROOT, '')
            elif fn.startswith(BSP_ROOT):
                fn = '$(BSP_ROOT)' + fn.replace(BSP_ROOT, '')

        Files.append(fn)
        # print(fn)

    src = open('src.mk', 'w')
    files = Files
    src.write('SRC_FILES :=\n')
    for item in files:
        # forward slashes, then make-quote so a space / '#' in the path is safe
        # while the leading $(BSP_ROOT)/$(RTT_ROOT) variable is preserved
        src.write('SRC_FILES +=%s\n' % target_utils.make_quote(item.replace('\\', '/')))

    make = open('Makefile', 'w')
    make.write(makefile)
    make.close()

    return
