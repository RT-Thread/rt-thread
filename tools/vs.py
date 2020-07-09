#
# File      : vs.py
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
import utils

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent
fs_encoding = sys.getfilesystemencoding()

def VS_AddGroup(ProjectFiles, parent, name, files, libs, project_path):
    Filter = SubElement(parent, 'Filter')
    Filter.set('Name', name) #set group name to group

    for f in files:
        fn = f.rfile()
        name = fn.name
        path = os.path.dirname(fn.abspath)

        path = _make_path_relative(project_path, path)
        path = os.path.join(path, name)

        File = SubElement(Filter, 'File')
        File.set('RelativePath', path.decode(fs_encoding))

    for lib in libs:
        name = os.path.basename(lib)
        path = os.path.dirname(lib)

        path = _make_path_relative(project_path, path)
        path = os.path.join(path, name)

        File = SubElement(Filter, 'File')
        File.set('RelativePath', path.decode(fs_encoding))

def VS_AddHeadFilesGroup(program, elem, project_path):
    utils.source_ext = []
    utils.source_ext = ["h"]
    for item in program:
        utils.walk_children(item)    
    utils.source_list.sort()
    # print utils.source_list
    
    for f in utils.source_list:
        path = _make_path_relative(project_path, f)
        File = SubElement(elem, 'File')
        File.set('RelativePath', path.decode(fs_encoding))

def VSProject(target, script, program):
    project_path = os.path.dirname(os.path.abspath(target))
    
    tree = etree.parse('template_vs2005.vcproj')
    root = tree.getroot()
    
    out = open(target, 'w')
    out.write('<?xml version="1.0" encoding="UTF-8"?>\r\n')
    
    ProjectFiles = []
    
    # add "*.c" files group
    for elem in tree.iter(tag='Filter'):
        if elem.attrib['Name'] == 'Source Files':
            #print elem.tag, elem.attrib
            break

    for group in script:
        libs = []
        if 'LIBS' in group and group['LIBS']:
            for item in group['LIBS']:
                lib_path = ''
                for path_item in group['LIBPATH']:
                    full_path = os.path.join(path_item, item + '.lib')
                    if os.path.isfile(full_path): # has this library
                        lib_path = full_path

                if lib_path != '':
                    libs.append(lib_path)

        group_xml = VS_AddGroup(ProjectFiles, elem, group['name'], group['src'], libs, project_path)

    # add "*.h" files group
    for elem in tree.iter(tag='Filter'):
        if elem.attrib['Name'] == 'Header Files':
            break
    VS_AddHeadFilesGroup(program, elem, project_path)
    
    # write head include path
    if 'CPPPATH' in building.Env:
        cpp_path = building.Env['CPPPATH']
        paths  = set()
        for path in cpp_path:
            inc = _make_path_relative(project_path, os.path.normpath(path))
            paths.add(inc) #.replace('\\', '/')
    
        paths = [i for i in paths]
        paths.sort()
        cpp_path = ';'.join(paths)

        # write include path, definitions
        for elem in tree.iter(tag='Tool'):
            if elem.attrib['Name'] == 'VCCLCompilerTool':
                #print elem.tag, elem.attrib
                break
        elem.set('AdditionalIncludeDirectories', cpp_path)

    # write cppdefinitons flags
    if 'CPPDEFINES' in building.Env:
        CPPDEFINES = building.Env['CPPDEFINES']
        definitions = []
        if type(CPPDEFINES[0]) == type(()):
            for item in CPPDEFINES:
                definitions += [i for i in item]
            definitions = ';'.join(definitions)
        else:
            definitions = ';'.join(building.Env['CPPDEFINES'])
        elem.set('PreprocessorDefinitions', definitions)
    # write link flags

    # write lib dependence 
    if 'LIBS' in building.Env:
        for elem in tree.iter(tag='Tool'):
            if elem.attrib['Name'] == 'VCLinkerTool':
                break
        libs_with_extention = [i+'.lib' for i in building.Env['LIBS']]
        libs = ' '.join(libs_with_extention)
        elem.set('AdditionalDependencies', libs)

    # write lib include path
    if 'LIBPATH' in building.Env:
        lib_path = building.Env['LIBPATH']
        paths  = set()
        for path in lib_path:
            inc = _make_path_relative(project_path, os.path.normpath(path))
            paths.add(inc) #.replace('\\', '/')
    
        paths = [i for i in paths]
        paths.sort()
        lib_paths = ';'.join(paths)
        elem.set('AdditionalLibraryDirectories', lib_paths)

    xml_indent(root)
    out.write(etree.tostring(root, encoding='utf-8'))
    out.close()
