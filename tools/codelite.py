#
# File      : codelite.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2020, RT-Thread Development Team
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
# 2020-10-14     LiuMin       Add copyright information
#

import os
import sys
import string
import building
import rtconfig

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent

import utils

fs_encoding = sys.getfilesystemencoding()

def CLSetCFlags(root, flags):
    node = root.find('Settings').find('Configuration').find('Compiler')
    node.attrib['C_Options'] = flags

def CLSetCxxFlags(root, flags):
    node = root.find('Settings').find('Configuration').find('Compiler')
    node.attrib['Options'] = flags

def CLSetAsFlags(root, flags):
    node = root.find('Settings').find('Configuration').find('Compiler')
    node.attrib['Assembler'] = flags

def CLAddIncludePath(root, path):
    node = root.find('Settings').find('Configuration').find('Compiler')
    node = SubElement(node, 'IncludePath')
    node.attrib['Value'] = path

def CLAddPreprocessor(root, value):
    node = root.find('Settings').find('Configuration').find('Compiler')
    node = SubElement(node, 'Preprocessor')
    node.attrib['Value'] = value


def CLSetLdFlags(root, flags):
    node = root.find('Settings').find('Configuration').find('Linker')
    node.attrib['Options'] = flags

def CLAddLibrary_path(root, path):
    node = root.find('Settings').find('Configuration').find('Linker')
    node = SubElement(node, 'LibraryPath')
    node.attrib['Value'] = path

def CLAddLibrary(root, lib):
    node = root.find('Settings').find('Configuration').find('Linker')
    node = SubElement(node, 'Library')
    node.attrib['Value'] = lib

def CLAddFile(root, file_path):
    file_path = file_path.replace('\\', '/')

    dir_list = file_path.split('/')
    dir_list.pop()
    if not len(dir_list):
        dir_list.append(os.path.abspath('.').replace('\\', '/').split('/')[-1])

    parent = root
    for dir_name in dir_list:
        if dir_name == '..':
            continue

        node = None
        nodes = parent.findall('VirtualDirectory')
        for iter in nodes:
            if iter.attrib['Name'] == dir_name:
                node = iter
                break
        if node is None:
            node = SubElement(parent, 'VirtualDirectory')
            node.attrib['Name'] = dir_name
        parent = node

    if parent != root:
        node = SubElement(parent, 'File')
        node.attrib['Name'] = file_path

def CLAddHeaderFiles(parent, program, project_path):
    utils.source_ext = []
    utils.source_ext = ["h"]
    for item in program:
        utils.walk_children(item)
    utils.source_list.sort()

    for f in utils.source_list:
        path = _make_path_relative(project_path, f)
        CLAddFile(parent, path)

def CLAddCFiles(parent, files, project_path):
    for f in files:
        fn = f.rfile()
        name = fn.name
        path = os.path.dirname(fn.abspath)

        path = _make_path_relative(project_path, path)
        path = os.path.join(path, name)
        CLAddFile(parent, path)



def CLGenWorkspace(project_name, project_path):
    if os.path.isfile('codelite_template.workspace'):
        tree = etree.parse('codelite_template.workspace')
    else:
        tree = etree.parse(os.path.join(os.path.dirname(__file__), 'codelite_template.workspace'))

    root = tree.getroot()
    root.attrib['Name'] = project_name

    node = root.find('Project')
    node.attrib['Name'] = project_name
    node.attrib['Path'] = project_name + '.project'

    node = root.find('BuildMatrix').find('WorkspaceConfiguration').find('Project')
    node.attrib['Name'] = project_name

    out = open(project_name + '.workspace', 'w')
    out.write('<?xml version="1.0" encoding="UTF-8"?>\n')
    xml_indent(root)
    out.write(etree.tostring(root, encoding='utf-8'))
    out.close()

def TargetCodelite(script, program):
    project_name = os.path.abspath('.').replace('\\', '/').split('/')[-1]
    #project_name.replace('-', '_')
    project_path = os.path.abspath('.')
    CLGenWorkspace(project_name, project_path)

    if os.path.isfile('codelite_template.project'):
        tree = etree.parse('codelite_template.project')
    else:
        tree = etree.parse(os.path.join(os.path.dirname(__file__), 'codelite_template.project'))

    root = tree.getroot()
    root.attrib['Name'] = project_name

    out = open(project_name + '.project', 'w')
    out.write('<?xml version="1.0" encoding="UTF-8"?>\n')

    # add files
    for group in script:
        CLAddCFiles(root, group['src'], project_path)
    # add header file
    CLAddHeaderFiles(root, program, project_path)

    # SECTION 2.
    # write head include path

    if 'CPPPATH' in building.Env:
        cpp_path = building.Env['CPPPATH']
        paths  = set()
        for path in cpp_path:
            inc = _make_path_relative(project_path, os.path.normpath(path))
            paths.add(inc) #.replace('\\', '/')

        paths = [i for i in paths]
        paths.sort()

        # write include path, definitions
        for elem in tree.iter(tag='Compiler'):
            break

        for path in paths:
            CLAddIncludePath(root, path)


        #print building.Env.get('LIBPATH', [])
        #print building.Env.get('LIBS', [])

        CLSetCFlags(root, building.Env.get('CFLAGS', []))
        CLSetCxxFlags(root, building.Env.get('CFLAGS', []))

        asflags = building.Env.get('ASFLAGS', [])
        asflags = asflags.replace('-ffunction-sections', '')
        asflags = asflags.replace('-fdata-sections', '')
        asflags = asflags.replace('-x', '')
        asflags = asflags.replace('-Wa,', '')
        asflags = asflags.replace('assembler-with-cpp', '')
        CLSetAsFlags(root, asflags)
        CLSetLdFlags(root, building.Env.get('LINKFLAGS', []))

        for macro in building.Env.get('CPPDEFINES', []):
            for d in macro:
                CLAddPreprocessor(root, d)

    xml_indent(root)
    out.write(etree.tostring(root, encoding='utf-8'))
    out.close()
