import os
import sys

from utils import *
from utils import _make_path_relative
import rtconfig

def TargetMakefile(env):
    project = ProjectInfo(env)

    make = open('config.mk', 'w')

    BSP_ROOT = os.path.abspath(env['BSP_ROOT'])
    RTT_ROOT = os.path.abspath(env['RTT_ROOT'])

    make.write('BSP_ROOT ?= %s\n' % BSP_ROOT.replace('\\', '\\\\'))
    make.write('RTT_ROOT ?= %s\n' % RTT_ROOT.replace('\\', '\\\\'))
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

    path = ''
    paths = [_make_path_relative(BSP_ROOT, os.path.normpath(i)) for i in project['CPPPATH']]
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

    src = open('src.mk', 'w')
    files = [_make_path_relative(BSP_ROOT, os.path.normpath(i)) for i in Files]
    src.write('SRC_FILES :=\n')
    for item in files:
        src.write('SRC_FILES +=%s\n' % item)

    return
