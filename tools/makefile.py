import os
import sys

from utils import *
from utils import _make_path_relative
import rtconfig

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
        path += '\t-I%s \\\n' % item

    make.write('CPPPATHS :=')
    if path[0] == '\t': path = path[1:]
    length = len(path)
    if path[length - 2] == '\\': path = path[:length - 2]
    make.write(path)
    make.write('\n')
    make.write('\n')

    defines = ''
    for item in project['CPPDEFINES']:
        defines += ' -D%s' % item
    make.write('DEFINES :=')
    make.write(defines)
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
        src.write('SRC_FILES +=%s\n' % item.replace('\\', '/'))

    make = open('Makefile', 'w')
    make.write(makefile)
    make.close()

    return
