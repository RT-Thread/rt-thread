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
# 2023-03-03     Supperthomas Add the vscode workspace config file

"""
Utils for VSCode
"""

import os
import json
import utils
import rtconfig
import pyocdconf
from utils import _make_path_relative

def delete_repeatelist(data):
    temp_dict = set([str(item) for item in data])
    data = [eval(i) for i in temp_dict]
    return data

def GenerateCFiles(env):
    """
    Generate c_cpp_properties files
    """
    if not os.path.exists('.vscode'):
        os.mkdir('.vscode')

    vsc_file = open('.vscode/c_cpp_properties.json', 'w')
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
                includePath.append(_make_path_relative(os.getcwd(), i[1:len(i) - 2]))
            else:
                includePath.append(_make_path_relative(os.getcwd(), i))
        config_obj['includePath'] = includePath

        json_obj = {}
        json_obj['configurations'] = [config_obj]

        vsc_file.write(json.dumps(json_obj, ensure_ascii=False, indent=4))
        vsc_file.close()

    """
    Generate vscode.code-workspace files
    """
    vsc_space_file = open('vscode.code-workspace', 'w')
    if vsc_space_file:
        info = utils.ProjectInfo(env)
        path_list = []
        for i in info['CPPPATH']:
            if  _make_path_relative(os.getcwd(), i)[0] == '.':
                if i[0] == '\"' and i[len(i) - 2:len(i)] == '\",':
                    path_list.append({'path':_make_path_relative(os.getcwd(), i[1:len(i) - 2])})
                else:
                    path_list.append({'path':_make_path_relative(os.getcwd(), i)})
        for i in info['DIRS']:
            if  _make_path_relative(os.getcwd(), i)[0] == '.':
                if i[0] == '\"' and i[len(i) - 2:len(i)] == '\",':
                    path_list.append({'path':_make_path_relative(os.getcwd(), i[1:len(i) - 2])})
                else:
                    path_list.append({'path':_make_path_relative(os.getcwd(), i)})

        json_obj = {}
        path_list = delete_repeatelist(path_list)
        path_list = sorted(path_list, key=lambda x: x["path"])
        target_path_list = []
        for path in path_list:
            if path['path'] != '.':
                path['name'] = 'rtthread/' + '/'.join([p for p in path['path'].split('\\') if p != '..'])
        json_obj['folders'] = path_list
        vsc_space_file.write(json.dumps(json_obj, ensure_ascii=False, indent=4))
        vsc_space_file.close()

    res_pyocdconf = pyocdconf.get_cmsisPack_targetId()
    cmsispack = res_pyocdconf[0]
    targetId = res_pyocdconf[1]

    """
    Generate .vscode/launch.json files
    """

    vsc_launch_file = open('.vscode/launch.json', 'w')
    if vsc_launch_file:
        config_obj = {}
        config_obj['name'] = 'Cortex Debug'
        config_obj['cwd'] = '${workspaceFolder}'
        config_obj['executable'] = 'rt-thread.elf'
        config_obj['request'] = 'launch'
        config_obj['type'] = 'cortex-debug'
        config_obj['runToEntryPoint'] = 'Reset_Handler'
        config_obj['servertype'] = 'pyocd'
        config_obj['toolchainPrefix'] = 'arm-none-eabi'
        config_obj['targetId'] = targetId
        config_obj['cmsisPack'] = cmsispack

        json_obj = {}
        json_obj['version'] = '0.2.0'
        json_obj['configurations'] = [config_obj]
        vsc_launch_file.write(json.dumps(json_obj, ensure_ascii=False, indent=4))
        vsc_launch_file.close()

    """
    Generate .vscode/tasks.json files
    """

    vsc_tasks_file = open('.vscode/tasks.json', 'w')
    if vsc_tasks_file:
        task_build_obj = {}
        task_build_obj['type'] = 'shell'
        task_build_obj['label'] = 'Build target files'
        task_build_obj['command'] = 'scons'
        task_build_obj['args'] = ['-j12']
        task_build_obj['problemMatcher'] = ['$gcc']
        task_build_obj['group'] = 'build'

        task_download_obj = {}
        task_download_obj['type'] = 'shell'
        task_download_obj['label'] = 'Download code to flash memory'
        task_download_obj['command'] = 'python'
        task_download_obj['args'] = ['-m', 'pyocd', 'flash', '--erase', 'chip', '--target', \
                                    targetId, '--pack', cmsispack, 'rt-thread.elf']
        task_download_obj['problemMatcher'] = ['$gcc']
        task_download_obj['group'] = 'build'

        task_build_download_obj = task_download_obj.copy()
        task_build_download_obj['label'] = 'Build and Download'
        task_build_download_obj['dependsOn'] = 'Build target files'

        json_obj = {}
        json_obj['version'] = '2.0.0'
        json_obj['tasks'] = [task_build_obj, task_download_obj, task_build_download_obj]
        vsc_tasks_file.write(json.dumps(json_obj, ensure_ascii=False, indent=4))
        vsc_tasks_file.close()

    return

def GenerateVSCode(env):
    print('Update setting files for VSCode...')
    GenerateCFiles(env)
    print('Done!')

    return
