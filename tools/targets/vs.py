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
import uuid
import utils
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent

# Add parent directory to path to import building
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import building

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import target_utils

import xml.etree.ElementTree as etree
fs_encoding = sys.getfilesystemencoding()

def VS_AddGroup(ProjectFiles, parent, name, files, libs, project_path):
    Filter = SubElement(parent, 'Filter')
    Filter.set('Name', name) #set group name to group

    for f in files:
        fn = f.rfile()
        name = fn.name
        dir_path = os.path.dirname(fn.abspath)

        # stable, single-separator RelativePath (was _make_path_relative +
        # os.path.join, which mixed '/' and '\\'); ElementTree escapes on write
        path = target_utils.normalize_group_file_path(project_path, dir_path, name)
        File = SubElement(Filter, 'File')
        File.set('RelativePath', path)

    for lib in libs:
        name = os.path.basename(lib)
        dir_path = os.path.dirname(lib)

        path = target_utils.normalize_group_file_path(project_path, dir_path, name)
        File = SubElement(Filter, 'File')
        File.set('RelativePath', path)

def VS_AddHeadFilesGroup(program, elem, project_path):
    utils.source_ext = []
    utils.source_ext = ["h"]
    for item in program:
        utils.walk_children(item)
    utils.source_list.sort()
    # print utils.source_list

    for f in utils.source_list:
        path = target_utils.normalize_group_file_path(project_path, f)
        File = SubElement(elem, 'File')
        File.set('RelativePath', path)

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
        paths = [_make_path_relative(project_path, os.path.normpath(path)) for path in cpp_path]
        # de-duplicate (keep order) then sort for stable output; ElementTree
        # escapes the attribute, so quotes/'&' in a path cannot break the XML
        paths = sorted(target_utils.ordered_unique(paths))
        cpp_path = target_utils.xml_list_value(paths)

        # write include path, definitions
        for elem in tree.iter(tag='Tool'):
            if elem.attrib['Name'] == 'VCCLCompilerTool':
                #print elem.tag, elem.attrib
                break
        elem.set('AdditionalIncludeDirectories', cpp_path)

    # write cppdefinitons flags
    if 'CPPDEFINES' in building.Env:
        # fold ('FOO','1') into 'FOO=1' -- the old code flattened tuples into
        # separate 'FOO' and '1' entries, emitting a bogus "FOO;1" macro
        definitions = target_utils.xml_list_value(
            target_utils.normalize_defines(building.Env['CPPDEFINES']))
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
        paths = [_make_path_relative(project_path, os.path.normpath(path)) for path in lib_path]
        paths = sorted(target_utils.ordered_unique(paths))
        lib_paths = target_utils.xml_list_value(paths)
        elem.set('AdditionalLibraryDirectories', lib_paths)

    xml_indent(root)
    text = etree.tostring(root, encoding='utf-8')
    try:
        text = text.decode(encoding="utf-8")
    except:
        text = text
    out.write(text)
    out.close()
