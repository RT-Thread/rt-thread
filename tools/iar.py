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

iar_workspace = '''<?xml version="1.0" encoding="iso-8859-1"?>

<workspace>
  <project>
    <path>$WS_DIR$\%s</path>
  </project>
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

def IARWorkspace(target):
    # make an workspace
    workspace = target.replace('.ewp', '.eww')
    out = open(workspace, 'w')
    xml = iar_workspace % target
    out.write(xml)
    out.close()

def IARProject(target, script):
    project_path = os.path.dirname(os.path.abspath(target))

    tree = etree.parse('template.ewp')
    root = tree.getroot()

    out = open(target, 'w')

    CPPPATH = []
    CPPDEFINES = []
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

        # get each group's definitions
        if 'CPPDEFINES' in group and group['CPPDEFINES']:
            CPPDEFINES += group['CPPDEFINES']

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
    paths = set()
    for path in CPPPATH:
        inc = _make_path_relative(project_path, os.path.normpath(path))
        paths.add(inc) #.replace('\\', '/')

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

    IARWorkspace(target)

def IARPath():
    import rtconfig

    # backup environ
    old_environ = os.environ
    os.environ['RTT_CC'] = 'iar'
    utils.ReloadModule(rtconfig)

    # get iar path
    path = rtconfig.EXEC_PATH

    # restore environ
    os.environ = old_environ
    utils.ReloadModule(rtconfig)

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
    iar_version = re.search('[\d\.]+', stdout).group(0)
    return iar_version
