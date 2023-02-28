#
# File      : options.py
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
# 2022-04-20     WuGensheng  Add Options to SCons
#

from SCons.Script import AddOption
import platform

def AddOptions():
    ''' ===== Add generic options to SCons ===== '''

    AddOption('--dist',
                      dest = 'make-dist',
                      action = 'store_true',
                      default = False,
                      help = 'make distribution')
    AddOption('--dist-strip',
                      dest = 'make-dist-strip',
                      action = 'store_true',
                      default = False,
                      help = 'make distribution and strip useless files')
    AddOption('--dist-ide', '--dist-rtstudio',
                      dest = 'make-dist-ide',
                      action = 'store_true',
                      default = False,
                      help = 'make distribution for RT-Thread Studio IDE')
    AddOption('--project-path',
                      dest = 'project-path',
                      type = 'string',
                      default = None,
                      help = 'set project output path')
    AddOption('--project-name',
                      dest = 'project-name',
                      type = 'string',
                      default = "project",
                      help = 'set project name')
    AddOption('--reset-project-config',
                      dest = 'reset-project-config',
                      action = 'store_true',
                      default = False,
                      help = 'reset the project configurations to default')
    AddOption('--cscope',
                      dest = 'cscope',
                      action = 'store_true',
                      default = False,
                      help = 'Build Cscope cross reference database. Requires cscope installed.')
    AddOption('--clang-analyzer',
                      dest = 'clang-analyzer',
                      action = 'store_true',
                      default = False,
                      help = 'Perform static analyze with Clang-analyzer. ' + \
                           'Requires Clang installed.\n' + \
                           'It is recommended to use with scan-build like this:\n' + \
                           '`scan-build scons --clang-analyzer`\n' + \
                           'If things goes well, scan-build will instruct you to invoke scan-view.')
    AddOption('--buildlib',
                      dest = 'buildlib',
                      type = 'string',
                      help = 'building library of a component')
    AddOption('--cleanlib',
                      dest = 'cleanlib',
                      action = 'store_true',
                      default = False,
                      help = 'clean up the library by --buildlib')
    AddOption('--target',
                      dest = 'target',
                      type = 'string',
                      help = 'set target project: mdk/mdk4/mdk5/iar/vs/vsc/ua/cdk/ses/makefile/eclipse/codelite/cmake')
    AddOption('--strict',
                dest='strict-compiling',
                help='Compiling project with strict mode and ALL warning will be errors',
                action='store_true',
                default=False)
    AddOption('--cc-prefix', '--exec-prefix',
                dest = 'exec-prefix',
                type = 'string',
                help = 'set RTT_CC_PREFIX temperately')
    AddOption('--cc-path', '--exec-path',
                dest = 'exec-path',
                type = 'string',
                help = 'set RTT_EXEC_PATH temperately')
    AddOption('--stackanalysis',
                dest = 'stackanalysis',
                action = 'store_true',
                default = False,
                help = 'thread stack static analysis')
    AddOption('--genconfig',
                dest = 'genconfig',
                action = 'store_true',
                default = False,
                help = 'Generate .config from rtconfig.h')
    AddOption('--useconfig',
                dest = 'useconfig',
                type = 'string',
                help = 'make rtconfig.h from config file.')
    AddOption('--verbose',
                dest = 'verbose',
                action = 'store_true',
                default = False,
                help = 'print verbose information during build')
    AddOption('--pyconfig',
                dest = 'pyconfig',
                action = 'store_true',
                default = False,
                help = 'Python GUI menuconfig for RT-Thread BSP')
    AddOption('--pyconfig-silent',
                dest = 'pyconfig_silent',
                action = 'store_true',
                default = False,
                help = 'Don`t show pyconfig window')
    if platform.system() != 'Windows':
        AddOption('--menuconfig',
                    dest = 'menuconfig',
                    action = 'store_true',
                    default = False,
                    help = 'make menuconfig for RT-Thread BSP')
