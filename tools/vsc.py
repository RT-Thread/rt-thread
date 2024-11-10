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

from utils import _make_path_relative

def delete_repeatelist(data):
    temp_dict = set([str(item) for item in data])
    data = [eval(i) for i in temp_dict]
    return data

def GenerateCFiles(env):
    """
    Generate c_cpp_properties.json and build/compile_commands.json files
    """
    if not os.path.exists('.vscode'):
        os.mkdir('.vscode')

    vsc_file = open('.vscode/c_cpp_properties.json', 'w')
    if vsc_file:
        info = utils.ProjectInfo(env)

        cc = os.path.join(rtconfig.EXEC_PATH, rtconfig.CC)
        cc = os.path.abspath(cc).replace('\\', '/')

        config_obj = {}
        config_obj['name'] = 'rt-thread'
        config_obj['defines'] = info['CPPDEFINES']

        intelliSenseMode = 'gcc-arm'
        if cc.find('aarch64') != -1:
            intelliSenseMode = 'gcc-arm64'
        elif cc.find('arm') != -1:
            intelliSenseMode = 'gcc-arm'
        config_obj['intelliSenseMode'] = intelliSenseMode
        config_obj['compilerPath'] = cc
        config_obj['cStandard'] = "c99"
        config_obj['cppStandard'] = "c++11"
        config_obj['compileCommands'] ="build/compile_commands.json"

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
    return

def GenerateProjectFiles(env):
    """
    Generate project.json file
    """
    if not os.path.exists('.vscode'):
        os.mkdir('.vscode')

    project = env['project']
    vsc_file = open('.vscode/project.json', 'w')
    if vsc_file:
        groups = []
        for group in project:
            if len(group['src']) > 0:
                item = {}
                item['name'] = group['name']
                item['path'] = _make_path_relative(os.getcwd(), group['path'])
                item['files'] = []

                for fn in group['src']:
                    item['files'].append(str(fn))

                # append SConscript if exist
                if os.path.exists(os.path.join(item['path'], 'SConscript')):
                    item['files'].append(os.path.join(item['path'], 'SConscript'))

                groups.append(item)

        json_dict = {}
        json_dict['RT-Thread'] = env['RTT_ROOT']
        json_dict['Groups'] = groups

        # write groups to project.json
        vsc_file.write(json.dumps(json_dict, ensure_ascii=False, indent=4))
        vsc_file.close()

    return

def GenerateVSCode(env):
    print('Update setting files for VSCode...')

    GenerateProjectFiles(env)
    GenerateCFiles(env)
    print('Done!')

    return
