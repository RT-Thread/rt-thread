#
# File      : keil.py
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
# 2017-10-16     Tanek        Add CDK IDE support
#

import os
import sys
import string

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent

def SDKAddGroup(ProjectFiles, parent, name, files, project_path):
    # don't add an empty group
    if len(files) == 0:
        return

    group = SubElement(parent, 'VirtualDirectory', attrib={'Name': name})

    for f in files:
        fn = f.rfile()
        name = fn.name
        path = os.path.dirname(fn.abspath)

        basename = os.path.basename(path)
        path = _make_path_relative(project_path, path)
        elm_attr_name = os.path.join(path, name)

        file = SubElement(group, 'File', attrib={'Name': elm_attr_name})

    return group

def _CDKProject(tree, target, script):

    project_path = os.path.dirname(os.path.abspath(target))

    root = tree.getroot()
    out = open(target, 'w')
    out.write('<?xml version="1.0" encoding="UTF-8"?>\n')

    CPPPATH = []
    CPPDEFINES = []
    LINKFLAGS = ''
    CCFLAGS = ''
    ProjectFiles = []

    for child in root:
        if child.tag == 'VirtualDirectory':
            root.remove(child)
    
    for group in script:
        group_tree = SDKAddGroup(ProjectFiles, root, group['name'], group['src'], project_path)

        # get each include path
        if 'CPPPATH' in group and group['CPPPATH']:
            if CPPPATH:
                CPPPATH += group['CPPPATH']
            else:
                CPPPATH += group['CPPPATH']

        # get each group's definitions
        if 'CPPDEFINES' in group and group['CPPDEFINES']:
            if CPPDEFINES:
                CPPDEFINES += group['CPPDEFINES']
            else:
                CPPDEFINES += group['CPPDEFINES']

        # get each group's cc flags
        if 'CCFLAGS' in group and group['CCFLAGS']:
            if CCFLAGS:
                CCFLAGS += ' ' + group['CCFLAGS']
            else:
                CCFLAGS += group['CCFLAGS']   
                
        # get each group's link flags
        if 'LINKFLAGS' in group and group['LINKFLAGS']:
            if LINKFLAGS:
                LINKFLAGS += ' ' + group['LINKFLAGS']
            else:
                LINKFLAGS += group['LINKFLAGS']

        # todo: cdk add lib

    # write include path, definitions and link flags
    text = ';'.join([_make_path_relative(project_path, os.path.normpath(i)) for i in CPPPATH])
    IncludePath = tree.find('BuildConfigs/BuildConfig/Compiler/IncludePath')
    IncludePath.text = text
    IncludePath = tree.find('BuildConfigs/BuildConfig/Asm/IncludePath')
    IncludePath.text = text

    Define = tree.find('BuildConfigs/BuildConfig/Compiler/Define')
    Define.text = ', '.join(set(CPPDEFINES))

    CC_Misc = tree.find('BuildConfigs/BuildConfig/Compiler/OtherFlags')
    CC_Misc.text = CCFLAGS
    
    LK_Misc = tree.find('BuildConfigs/BuildConfig/Linker/OtherFlags')
    LK_Misc.text = LINKFLAGS

    xml_indent(root)
    out.write(etree.tostring(root, encoding='utf-8'))
    out.close()

def CDKProject(target, script):
    template_tree = etree.parse('template.cdkproj')

    _CDKProject(template_tree, target, script)
