#
# File      : codeblocks.py
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

def CB_AddHeadFiles(program, elem, project_path):
    utils.source_ext = []
    utils.source_ext = ["h"]
    for item in program:
        utils.walk_children(item)
    utils.source_list.sort()
    # print utils.source_list

    for f in utils.source_list:
        # stable, single-separator path; ElementTree escapes & < > " on write.
        # (was path.decode(fs_encoding) -- str has no .decode on Python 3)
        path = target_utils.normalize_group_file_path(project_path, f)
        Unit = SubElement(elem, 'Unit')
        Unit.set('filename', path)

def CB_AddCFiles(ProjectFiles, parent, gname, files, project_path):
    for f in files:
        fn = f.rfile()
        name = fn.name
        dir_path = os.path.dirname(fn.abspath)

        # normalized relative path (was _make_path_relative + os.path.join,
        # which mixed '/' and '\\'; and path.decode crashed on Python 3)
        path = target_utils.normalize_group_file_path(project_path, dir_path, name)

        Unit = SubElement(parent, 'Unit')
        Unit.set('filename', path)
        Option = SubElement(Unit, 'Option')
        Option.set('compilerVar', "CC")

def CBProject(target, script, program):
    project_path = os.path.dirname(os.path.abspath(target))

    if os.path.isfile('template.cbp'):
        tree = etree.parse('template.cbp')
    else:
        tree = etree.parse(os.path.join(os.path.dirname(__file__), 'template.cbp'))

    root = tree.getroot()

    out = open(target, 'w')
    out.write('<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>\n')

    ProjectFiles = []

    # SECTION 1. add "*.c|*.h" files group
    for elem in tree.iter(tag='Project'):
        # print elem.tag, elem.attrib
        break
    # add c files
    for group in script:
        group_xml = CB_AddCFiles(ProjectFiles, elem, group['name'], group['src'], project_path)
    # add h files
    CB_AddHeadFiles(program, elem, project_path)

    # SECTION 2.
    # write head include path
    if 'CPPPATH' in building.Env:
        cpp_path = building.Env['CPPPATH']
        # order-preserving de-dup, then sort (set() reordered non-deterministically)
        paths = target_utils.normalize_paths(
            [_make_path_relative(project_path, os.path.normpath(path)) for path in cpp_path])
        paths.sort()
        # write include path, definitions
        for elem in tree.iter(tag='Compiler'):
            break
        for path in paths:
            Add = SubElement(elem, 'Add')
            Add.set('directory', path)

        # one <Add option="-D<macro>"/> per define. The old `for d in macro`
        # iterated the *characters* of a string macro (leaving only -D<last char>)
        # and dropped the name of a ('STM32','1') tuple; normalize_defines folds
        # tuples to STM32=1 and yields one complete macro per entry.
        for macro in target_utils.normalize_defines(building.Env.get('CPPDEFINES', [])):
            Add = SubElement(elem, 'Add')
            Add.set('option', "-D" + macro)

        # write link flags
    '''
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
    '''
    xml_indent(root)
    # encoding='unicode' yields str for the text-mode file; encoding='utf-8'
    # returns bytes and raised TypeError on write under Python 3
    out.write(etree.tostring(root, encoding='unicode'))
    out.close()
