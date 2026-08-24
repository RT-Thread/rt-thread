#
# File      : iar.py
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
#

import os
import sys
import string
import utils

from SCons.Script import *

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent

fs_encoding = sys.getfilesystemencoding()

iar_workspace = r'''<?xml version="1.0" encoding="iso-8859-1"?>

<workspace>
  <project>
    <path>$WS_DIR$\%(project)s</path>
  </project>%(active_config)s
  <batchBuild/>
</workspace>


'''


def IARAddGroup(parent, name, files, project_path):
    group = SubElement(parent, 'group')
    group_name = SubElement(group, 'name')
    group_name.text = name

    for f in files:
        fn = f.rfile()
        name = fn.name
        path = os.path.dirname(fn.abspath)
        basename = os.path.basename(path)
        path = _make_path_relative(project_path, path)
        path = os.path.join(path, name)

        file = SubElement(group, 'file')
        file_name = SubElement(file, 'name')

        if os.path.isabs(path):
            file_name.text = path # path.decode(fs_encoding)
        else:
            file_name.text = '$PROJ_DIR$\\' + path # ('$PROJ_DIR$\\' + path).decode(fs_encoding)

def _update_iar_wsdt(wsdt_path, project_name, active_config):
    """Update <CurrentConfigs><Project> in the IAR session file to set the active configuration."""
    config_str = '%s/%s' % (project_name, active_config)

    if not os.path.exists(wsdt_path):
        # create a minimal wsdt if it does not exist yet
        os.makedirs(os.path.dirname(wsdt_path), exist_ok=True)
        content = '<?xml version="1.0"?>\n<Workspace>\n    <ConfigDictionary>\n        <CurrentConfigs>\n            <Project>%s</Project>\n        </CurrentConfigs>\n    </ConfigDictionary>\n</Workspace>\n' % config_str
        with open(wsdt_path, 'w') as f:
            f.write(content)
        return

    try:
        tree = etree.parse(wsdt_path)
        root = tree.getroot()
        proj_elem = root.find('ConfigDictionary/CurrentConfigs/Project')
        if proj_elem is not None:
            proj_elem.text = config_str
        else:
            # create the elements if missing
            cfg_dict = root.find('ConfigDictionary')
            if cfg_dict is None:
                cfg_dict = SubElement(root, 'ConfigDictionary')
            cur_cfgs = cfg_dict.find('CurrentConfigs')
            if cur_cfgs is None:
                cur_cfgs = SubElement(cfg_dict, 'CurrentConfigs')
            proj_elem = SubElement(cur_cfgs, 'Project')
            proj_elem.text = config_str
        tree.write(wsdt_path, encoding='unicode', xml_declaration=True)
    except Exception as e:
        print('Warning: could not update %s: %s' % (wsdt_path, e))

def IARWorkspace(target, active_config=None):
    # make an workspace, optionally setting the active configuration
    workspace = target.replace('.ewp', '.eww')
    project_name = os.path.splitext(os.path.basename(target))[0]
    active_elem = ''
    if active_config:
        active_elem = '\n  <activeConfig>\n    <name>%s/%s</name>\n  </activeConfig>' % (project_name, active_config)
    out = open(workspace, 'w')
    xml = iar_workspace % {'project': target, 'active_config': active_elem}
    out.write(xml)
    out.close()

def IARProject(env, target, script):
    project_path = os.path.dirname(os.path.abspath(target))

    tree = etree.parse('template.ewp')
    root = tree.getroot()

    out = open(target, 'w')

    CPPPATH = []
    CPPDEFINES = env.get('CPPDEFINES', [])

    LOCAL_CPPDEFINES = []
    LINKFLAGS = ''
    CFLAGS = ''
    Libs = []
    lib_prefix = ['lib', '']
    lib_suffix = ['.a', '.o', '']

    def searchLib(group):
        for path_item in group['LIBPATH']:
            for prefix_item in lib_prefix:
                for suffix_item in lib_suffix:
                    lib_full_path = os.path.join(path_item, prefix_item + item + suffix_item)
                    if os.path.isfile(lib_full_path):
                        return lib_full_path
        else:
            return ''

    # add group
    for group in script:
        IARAddGroup(root, group['name'], group['src'], project_path)

        # get each include path
        if 'CPPPATH' in group and group['CPPPATH']:
            CPPPATH += group['CPPPATH']


        if 'LOCAL_CPPDEFINES' in group and group['LOCAL_CPPDEFINES']:
            LOCAL_CPPDEFINES += group['LOCAL_CPPDEFINES']

        # get each group's link flags
        if 'LINKFLAGS' in group and group['LINKFLAGS']:
            LINKFLAGS += group['LINKFLAGS']

        if 'LIBS' in group and group['LIBS']:
            for item in group['LIBS']:
                lib_path = searchLib(group)
                if lib_path != '':
                    lib_path = _make_path_relative(project_path, lib_path)
                    Libs += [lib_path]
                    # print('found lib isfile: ' + lib_path)
                else:
                    print('not found LIB: ' + item)

    # make relative path
    paths = {}
    for path in CPPPATH:
        inc = _make_path_relative(project_path, os.path.normpath(path))
        paths[inc] = None  # 使用 dict 去重并保持插入顺序
    paths = list(paths.keys())

    # setting options
    options = tree.findall('configuration/settings/data/option')
    for option in options:
        # print option.text
        name = option.find('name')

        if name.text == 'CCIncludePath2' or name.text == 'newCCIncludePaths':
            for path in paths:
                state = SubElement(option, 'state')
                if os.path.isabs(path) or path.startswith('$'):
                    state.text = path
                else:
                    state.text = '$PROJ_DIR$\\' + path

        if name.text == 'CCDefines':
            for define in CPPDEFINES:
                state = SubElement(option, 'state')
                state.text = define

            for define in LOCAL_CPPDEFINES:
                state = SubElement(option, 'state')
                state.text = define

        if name.text == 'IlinkConfigDefines':
            # write bare symbol=value tokens from LINKFLAGS as IAR linker defines
            import re
            for token in re.findall(r'\S+', LINKFLAGS):
                state = SubElement(option, 'state')
                state.text = token

        if name.text == 'IlinkAdditionalLibs':
            for path in Libs:
                state = SubElement(option, 'state')
                if os.path.isabs(path) or path.startswith('$'):
                    path = path.decode(fs_encoding)
                else:
                    path = ('$PROJ_DIR$\\' + path).decode(fs_encoding)
                state.text = path

    xml_indent(root)
    out.write(etree.tostring(root, encoding='utf-8').decode())
    out.close()

    # Determine the active configuration from the BSP via an optional board-specific hook.
    active_config = None
    try:
        import rtconfig
        if hasattr(rtconfig, 'iar_get_active_config'):
            active_config = rtconfig.iar_get_active_config()
    except Exception as e:
        print('Warning: could not get IAR active config: %s' % e)

    IARWorkspace(target, active_config)

    # update settings/project.wsdt to set the active configuration
    if active_config:
        wsdt_path = os.path.join('settings', os.path.splitext(os.path.basename(target))[0] + '.wsdt')

        project_name = os.path.splitext(os.path.basename(target))[0]
        _update_iar_wsdt(wsdt_path, project_name, active_config)

    # copy template.ewd (debugger settings) and template.ewt (build settings) to project files
    import shutil
    ewd_template = target.replace('.ewp', '.ewd').replace('project', 'template')
    ewd_target   = target.replace('.ewp', '.ewd')
    if not os.path.exists(ewd_template):
        ewd_template = 'template.ewd'
    if os.path.exists(ewd_template):
        shutil.copy2(ewd_template, ewd_target)

    ewt_template = target.replace('.ewp', '.ewt').replace('project', 'template')
    ewt_target   = target.replace('.ewp', '.ewt')
    if not os.path.exists(ewt_template):
        ewt_template = 'template.ewt'
    if os.path.exists(ewt_template):
        shutil.copy2(ewt_template, ewt_target)

def IARPath():
    import rtconfig

    # backup environ
    old_environ = os.environ
    os.environ['RTT_CC'] = 'iar'

    # get iar path
    path = rtconfig.EXEC_PATH

    # restore environ
    os.environ = old_environ

    return path

def IARVersion():
    import subprocess
    import re

    path = IARPath()

    if os.path.exists(path):
        cmd = os.path.join(path, 'iccarm.exe')
    else:
        return "0.0"

    child = subprocess.Popen([cmd, '--version'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    stdout, stderr = child.communicate()
    if not isinstance(stdout, str):
        stdout = str(stdout, 'utf8') # Patch for Python 3
    # example stdout: IAR ANSI C/C++ Compiler V8.20.1.14183/W32 for ARM
    iar_version = re.search(r'[\d\.]+', stdout).group(0)
    return iar_version
