#
# File      : vsc.py
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
# 2018-05-30     Bernard      The first version

"""
Utils for VSCode
"""

import os
import json
import utils
import rtconfig

def GenerateCFiles(env):
    """
    Generate c_cpp_properties files
    """
    if not os.path.exists('.vscode'):
        os.mkdir('.vscode')

    vsc_file = file('.vscode/c_cpp_properties.json', 'wb')
    if vsc_file:
        info = utils.ProjectInfo(env)

        cc = os.path.join(rtconfig.EXEC_PATH, rtconfig.CC)
        cc = os.path.abspath(cc).replace('\\', '/')

        config_obj = {}
        config_obj['name'] = 'Win32'
        config_obj['defines'] = info['CPPDEFINES']
        config_obj['intelliSenseMode'] = 'clang-x64'
        config_obj['compilerPath'] = cc
        config_obj['cStandard'] = "c99"
        config_obj['cppStandard'] = "c++11"

        # format "a/b," to a/b. remove first quotation mark("),and remove end (",)
        includePath = []
        for i in info['CPPPATH']:
            if i[0] == '\"' and i[len(i) - 2:len(i)] == '\",':
                includePath.append(i[1:len(i) - 2])
            else:
                includePath.append(i)
        config_obj['includePath'] = includePath

        json_obj = {}
        json_obj['configurations'] = [config_obj]

        vsc_file.write(json.dumps(json_obj, indent=4))
        vsc_file.close()

    """
    Generate launch.json files (used to debug)
    """
    vsc_debug_file = file('.vscode/launch.json', 'wb')
    if vsc_debug_file:
        debug_cfg_obj = {}
        config_files = []
        config_files.append(
            'example:/usr/share/openocd/scripts/interface/stlink-v2.cfg')
        config_files.append(
            'example:/usr/share/openocd/scripts/target/stm32f1x_stlink.cfg')
        debug_cfg_obj['configFiles'] = config_files

        searchdir = []
        searchdir.append('example:/usr/share/openocd/scripts/')
        debug_cfg_obj['searchDir'] = searchdir

        debug_cfg_obj['svdFile'] = 'example:~/.vscode/extensions/marus25.cortex-debug-0.1.21/data/STMicro/STM32F103xx.svd'

        debug_cfg_obj['runToMain'] = True
        debug_cfg_obj['v1'] = False
        debug_cfg_obj['showDevDebugOutput'] = True
        debug_cfg_obj['servertype'] = 'openocd'
        debug_cfg_obj['type'] = 'cortex-debug'
        debug_cfg_obj['request'] = 'launch'
        debug_cfg_obj['name'] = 'rt-thread debug'
        debug_cfg_obj['executable'] = './rtthread-stm32.elf'
        debug_cfg_obj['cwd'] = '${workspaceRoot}'

        json_obj = {}
        json_obj['configurations'] = [debug_cfg_obj]

        vsc_debug_file.write(json.dumps(json_obj, indent=4))
        vsc_debug_file.close()
    return

def GenerateVSCode(env):
    print('Update setting files for VSCode...'),
    GenerateCFiles(env)
    print('Done!')

    return
