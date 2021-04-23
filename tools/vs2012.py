#
# File      : vs2012.py
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
import building
import uuid

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent
import utils

fs_encoding = sys.getfilesystemencoding()

#reference
# http://woodpecker.org.cn/diveintopython3/xml.html
# https://pycoders-weekly-chinese.readthedocs.org/en/latest/issue6/processing-xml-in-python-with-element-tree.html
# http://www.cnblogs.com/ifantastic/archive/2013/04/12/3017110.html

filter_project = etree.Element('Project', attrib={'ToolsVersion':'4.0'})
def get_uuid():
    id = uuid.uuid1()  # UUID('3e5526c0-2841-11e3-a376-20cf3048bcb3')
    if sys.version > '3':
        idstr = id.urn[9:] #'urn:uuid:3e5526c0-2841-11e3-a376-20cf3048bcb3'[9:]
    else:
        # python3 is no decode function
        idstr = id.get_urn()[9:] #'urn:uuid:3e5526c0-2841-11e3-a376-20cf3048bcb3'[9:]
    
    return '{'+idstr+'}'

def VS2012_AddGroup(parent, group_name, files, project_path):
    for f in files:
        fn = f.rfile()
        name = fn.name
        path = os.path.dirname(fn.abspath)

        path = _make_path_relative(project_path, path)
        path = os.path.join(path, name)

        ClCompile = SubElement(parent, 'ClCompile')

        if sys.version > '3':
            ClCompile.set('Include', path)
        else:
            # python3 is no decode function
            ClCompile.set('Include', path.decode(fs_encoding))

        Filter = SubElement(ClCompile, 'Filter')
        Filter.text='Source Files\\'+group_name

def VS2012_CreateFilter(script, project_path):
    c_ItemGroup = SubElement(filter_project, 'ItemGroup')
    filter_ItemGroup = SubElement(filter_project, 'ItemGroup')

    Filter = SubElement(filter_ItemGroup, 'Filter')
    Filter.set('Include', 'Source Files')
    UniqueIdentifier = SubElement(Filter, 'UniqueIdentifier')
    UniqueIdentifier.text = get_uuid()
    Extensions = SubElement(Filter, 'Extensions')
    Extensions.text = 'cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx'

    Filter = SubElement(filter_ItemGroup, 'Filter')
    Filter.set('Include', 'Header Files')
    UniqueIdentifier = SubElement(Filter, 'UniqueIdentifier')
    UniqueIdentifier.text = get_uuid()
    Extensions = SubElement(Filter, 'Extensions')
    Extensions.text = 'h;hpp;hxx;hm;inl;inc;xsd'
    for group in script:
        VS2012_AddGroup(c_ItemGroup, group['name'], group['src'], project_path)
        Filter = SubElement(filter_ItemGroup, 'Filter')
        Filter.set('Include', 'Source Files\\'+group['name'])
        UniqueIdentifier = SubElement(Filter, 'UniqueIdentifier')
        UniqueIdentifier.text = get_uuid()

#program: object from scons
# parent: xml node
# file_type: C or H
# files: c/h list
# project_path
def VS_add_ItemGroup(parent, file_type, files, project_path):
    from building import Rtt_Root
    RTT_ROOT = os.path.normpath(Rtt_Root)

    file_dict = {'C':"ClCompile", 'H':'ClInclude'}
    item_tag = file_dict[file_type]

    ItemGroup = SubElement(parent, 'ItemGroup')
    for f in files:
        fn = f.rfile()
        name = fn.name
        path = os.path.dirname(fn.abspath)

        objpath = path.lower()
        if len(project_path) >= len(RTT_ROOT) :
            if objpath.startswith(project_path.lower()) :
                objpath = ''.join('bsp'+objpath[len(project_path):])
            else :
                objpath = ''.join('kernel'+objpath[len(RTT_ROOT):])
        else :
            if objpath.startswith(RTT_ROOT.lower()) :
                objpath = ''.join('kernel'+objpath[len(RTT_ROOT):])
            else :
                objpath = ''.join('bsp'+objpath[len(project_path):])
        path = _make_path_relative(project_path, path)
        path = os.path.join(path, name)

        File = SubElement(ItemGroup, item_tag)

        if sys.version > '3':
            File.set('Include', path)
        else:
            # python3 is no decode function
            File.set('Include', path.decode(fs_encoding))

        if file_type == 'C' :
            ObjName = SubElement(File, 'ObjectFileName')
            ObjName.text = ''.join('$(IntDir)'+objpath+'\\')

def VS_add_HeadFiles(program, elem, project_path):
    utils.source_ext = []
    utils.source_ext = ["h"]
    for item in program:
        utils.walk_children(item)    
    utils.source_list.sort()
    # print utils.source_list
    ItemGroup = SubElement(elem, 'ItemGroup')

    filter_h_ItemGroup = SubElement(filter_project, 'ItemGroup')
    for f in utils.source_list:
        path = _make_path_relative(project_path, f)
        File = SubElement(ItemGroup, 'ClInclude')

        if sys.version > '3':
            File.set('Include', path)
        else:
            # python3 is no decode function
            File.set('Include', path.decode(fs_encoding))

        # add project.vcxproj.filter
        ClInclude = SubElement(filter_h_ItemGroup, 'ClInclude')

        if sys.version > '3':
            ClInclude.set('Include', path)
        else:
            # python3 is no decode function
            ClInclude.set('Include', path.decode(fs_encoding))

        Filter = SubElement(ClInclude, 'Filter')
        Filter.text='Header Files'

def VS2012Project(target, script, program):
    project_path = os.path.dirname(os.path.abspath(target))
    
    tree = etree.parse('template_vs2012.vcxproj')
    root = tree.getroot()
    elem = root

    out = open(target, 'w')
    out.write('<?xml version="1.0" encoding="UTF-8"?>\r\n')

    ProjectFiles = []

    # add "*.c or *.h" files

    VS2012_CreateFilter(script, project_path)
    # add "*.c" files
    for group in script:
        VS_add_ItemGroup(elem, 'C', group['src'], project_path)

    # add "*.h" files
    VS_add_HeadFiles(program, elem, project_path)

    # write head include path
    if 'CPPPATH' in building.Env:
        cpp_path = building.Env['CPPPATH']
        paths = set()
        for path in cpp_path:
            inc = _make_path_relative(project_path, os.path.normpath(path))
            paths.add(inc) #.replace('\\', '/')
    
        paths = [i for i in paths]
        paths.sort()
        cpp_path = ';'.join(paths) + ';%(AdditionalIncludeDirectories)'

        # write include path
        for elem in tree.iter(tag='AdditionalIncludeDirectories'):
            elem.text = cpp_path
            break

    # write cppdefinitons flags
    if 'CPPDEFINES' in building.Env:
        for elem in tree.iter(tag='PreprocessorDefinitions'):
            CPPDEFINES = building.Env['CPPDEFINES']
            definitions = []
            if type(CPPDEFINES[0]) == type(()):
                for item in CPPDEFINES:
                    definitions += [i for i in item]
                definitions = ';'.join(definitions)
            else:
                definitions = ';'.join(building.Env['CPPDEFINES'])

            definitions = definitions + ';%(PreprocessorDefinitions)'
            elem.text = definitions
            break
    # write link flags

    # write lib dependence (Link)
    if 'LIBS' in building.Env:
        for elem in tree.iter(tag='AdditionalDependencies'):
            libs_with_extention = [i+'.lib' for i in building.Env['LIBS']]
            libs = ';'.join(libs_with_extention) + ';%(AdditionalDependencies)'
            elem.text = libs
            break

    # write lib include path
    if 'LIBPATH' in building.Env:
        lib_path = building.Env['LIBPATH']
        paths  = set()
        for path in lib_path:
            inc = _make_path_relative(project_path, os.path.normpath(path))
            paths.add(inc)
    
        paths = [i for i in paths]
        paths.sort()
        lib_paths = ';'.join(paths) + ';%(AdditionalLibraryDirectories)'
        for elem in tree.iter(tag='AdditionalLibraryDirectories'):
            elem.text = lib_paths
            break

    xml_indent(root)

    if sys.version > '3':
        vcxproj_string = etree.tostring(root, encoding='unicode')
    else:
        # python3 is no decode function
        vcxproj_string = etree.tostring(root, encoding='utf-8')

    root_node=r'<Project DefaultTargets="Build" ToolsVersion="4.0">'
    out.write(r'<Project DefaultTargets="Build" ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">')
    out.write(vcxproj_string[len(root_node):])
    out.close()

    xml_indent(filter_project)

    if sys.version > '3':
        filter_string = etree.tostring(filter_project, encoding='unicode')
    else:
        # python3 is no decode function
        filter_string = etree.tostring(filter_project, encoding='utf-8')

    out = open('project.vcxproj.filters', 'w')
    out.write('<?xml version="1.0" encoding="UTF-8"?>\r\n')
    root_node=r'<Project ToolsVersion="4.0">'
    out.write(r'<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">')
    out.write(filter_string[len(root_node):])
    out.close()

