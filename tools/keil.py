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
# 2015-01-20     Bernard      Add copyright information
#

import os
import sys
import string

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent

fs_encoding = sys.getfilesystemencoding()

def _get_filetype(fn):
    if fn.rfind('.cpp') != -1 or fn.rfind('.cxx') != -1:
        return 8

    if fn.rfind('.c') != -1 or fn.rfind('.C') != -1:
        return 1

    # assemble file type
    if fn.rfind('.s') != -1 or fn.rfind('.S') != -1:
        return 2

    # header type
    if fn.rfind('.h') != -1:
        return 5

    if fn.rfind('.lib') != -1:
        return 4

    # other filetype
    return 5

def MDK4AddGroupForFN(ProjectFiles, parent, name, filename, project_path):
    group = SubElement(parent, 'Group')
    group_name = SubElement(group, 'GroupName')
    group_name.text = name

    name = os.path.basename(filename)
    path = os.path.dirname (filename)

    basename = os.path.basename(path)
    path = _make_path_relative(project_path, path)
    path = os.path.join(path, name)
    files = SubElement(group, 'Files')
    file = SubElement(files, 'File')
    file_name = SubElement(file, 'FileName')
    name = os.path.basename(path)

    if name.find('.cpp') != -1:
        obj_name = name.replace('.cpp', '.o')
    elif name.find('.c') != -1:
        obj_name = name.replace('.c', '.o')
    elif name.find('.s') != -1:
        obj_name = name.replace('.s', '.o')
    elif name.find('.S') != -1:
        obj_name = name.replace('.s', '.o')
    else:
        obj_name = name

    if ProjectFiles.count(obj_name):
        name = basename + '_' + name
    ProjectFiles.append(obj_name)
    file_name.text = name.decode(fs_encoding)
    file_type = SubElement(file, 'FileType')
    file_type.text = '%d' % _get_filetype(name)
    file_path = SubElement(file, 'FilePath')

    file_path.text = path.decode(fs_encoding)

def MDK4AddLibToGroup(ProjectFiles, group, name, filename, project_path):
    name = os.path.basename(filename)
    path = os.path.dirname (filename)

    basename = os.path.basename(path)
    path = _make_path_relative(project_path, path)
    path = os.path.join(path, name)
    files = SubElement(group, 'Files')
    file = SubElement(files, 'File')
    file_name = SubElement(file, 'FileName')
    name = os.path.basename(path)

    if name.find('.cpp') != -1:
        obj_name = name.replace('.cpp', '.o')
    elif name.find('.c') != -1:
        obj_name = name.replace('.c', '.o')
    elif name.find('.s') != -1:
        obj_name = name.replace('.s', '.o')
    elif name.find('.S') != -1:
        obj_name = name.replace('.s', '.o')
    else:
        obj_name = name

    if ProjectFiles.count(obj_name):
        name = basename + '_' + name
    ProjectFiles.append(obj_name)
    file_name.text = name.decode(fs_encoding)
    file_type = SubElement(file, 'FileType')
    file_type.text = '%d' % _get_filetype(name)
    file_path = SubElement(file, 'FilePath')

    file_path.text = path.decode(fs_encoding)

def MDK4AddGroup(ProjectFiles, parent, name, files, project_path):
    # don't add an empty group
    if len(files) == 0:
        return

    group = SubElement(parent, 'Group')
    group_name = SubElement(group, 'GroupName')
    group_name.text = name

    for f in files:
        fn = f.rfile()
        name = fn.name
        path = os.path.dirname(fn.abspath)

        basename = os.path.basename(path)
        path = _make_path_relative(project_path, path)
        path = os.path.join(path, name)

        files = SubElement(group, 'Files')
        file = SubElement(files, 'File')
        file_name = SubElement(file, 'FileName')
        name = os.path.basename(path)

        if name.find('.cpp') != -1:
            obj_name = name.replace('.cpp', '.o')
        elif name.find('.c') != -1:
            obj_name = name.replace('.c', '.o')
        elif name.find('.s') != -1:
            obj_name = name.replace('.s', '.o')
        elif name.find('.S') != -1:
            obj_name = name.replace('.s', '.o')

        if ProjectFiles.count(obj_name):
            name = basename + '_' + name
        ProjectFiles.append(obj_name)
        file_name.text = name.decode(fs_encoding)
        file_type = SubElement(file, 'FileType')
        file_type.text = '%d' % _get_filetype(name)
        file_path = SubElement(file, 'FilePath')

        file_path.text = path.decode(fs_encoding)

    return group

# The common part of making MDK4/5 project 
def MDK45Project(tree, target, script):
    project_path = os.path.dirname(os.path.abspath(target))

    root = tree.getroot()
    out = file(target, 'wb')
    out.write('<?xml version="1.0" encoding="UTF-8" standalone="no" ?>\n')

    CPPPATH = []
    CPPDEFINES = []
    LINKFLAGS = ''
    CCFLAGS = ''
    ProjectFiles = []

    # add group
    groups = tree.find('Targets/Target/Groups')
    if groups is None:
        groups = SubElement(tree.find('Targets/Target'), 'Groups')
    groups.clear() # clean old groups
    for group in script:
        group_tree = MDK4AddGroup(ProjectFiles, groups, group['name'], group['src'], project_path)

        # for local CPPPATH/CPPDEFINES
        if (group_tree != None) and (group.has_key('LOCAL_CPPPATH') or group.has_key('LOCAL_CCFLAGS')):
            GroupOption     = SubElement(group_tree,  'GroupOption')
            GroupArmAds     = SubElement(GroupOption, 'GroupArmAds')
            Cads            = SubElement(GroupArmAds, 'Cads')
            VariousControls = SubElement(Cads, 'VariousControls')
            MiscControls    = SubElement(VariousControls, 'MiscControls')
            if group.has_key('LOCAL_CCFLAGS'):
                MiscControls.text = group['LOCAL_CCFLAGS']
            else:
                MiscControls.text = ' '
            Define          = SubElement(VariousControls, 'Define')
            if group.has_key('LOCAL_CPPDEFINES'):
                Define.text     = ', '.join(set(group['LOCAL_CPPDEFINES']))
            else:
                Define.text     = ' '
            Undefine        = SubElement(VariousControls, 'Undefine')
            Undefine.text   = ' '
            IncludePath     = SubElement(VariousControls, 'IncludePath')
            if group.has_key('LOCAL_CPPPATH'):
                IncludePath.text = ';'.join([_make_path_relative(project_path, os.path.normpath(i)) for i in group['LOCAL_CPPPATH']])
            else:
                IncludePath.text = ' '

        # get each include path
        if group.has_key('CPPPATH') and group['CPPPATH']:
            if CPPPATH:
                CPPPATH += group['CPPPATH']
            else:
                CPPPATH += group['CPPPATH']

        # get each group's definitions
        if group.has_key('CPPDEFINES') and group['CPPDEFINES']:
            if CPPDEFINES:
                CPPDEFINES += group['CPPDEFINES']
            else:
                CPPDEFINES = group['CPPDEFINES']

        # get each group's link flags
        if group.has_key('LINKFLAGS') and group['LINKFLAGS']:
            if LINKFLAGS:
                LINKFLAGS += ' ' + group['LINKFLAGS']
            else:
                LINKFLAGS += group['LINKFLAGS']

        if group.has_key('LIBS') and group['LIBS']:
            for item in group['LIBS']:
                lib_path = ''
                for path_item in group['LIBPATH']:
                    full_path = os.path.join(path_item, item + '.lib')
                    if os.path.isfile(full_path): # has this library
                        lib_path = full_path

                if lib_path != '':
                    if (group_tree != None):
                        MDK4AddLibToGroup(ProjectFiles, group_tree, group['name'], lib_path, project_path)
                    else:
                        MDK4AddGroupForFN(ProjectFiles, groups, group['name'], lib_path, project_path)

    # write include path, definitions and link flags
    IncludePath = tree.find('Targets/Target/TargetOption/TargetArmAds/Cads/VariousControls/IncludePath')
    IncludePath.text = ';'.join([_make_path_relative(project_path, os.path.normpath(i)) for i in CPPPATH])

    Define = tree.find('Targets/Target/TargetOption/TargetArmAds/Cads/VariousControls/Define')
    Define.text = ', '.join(set(CPPDEFINES))

    Misc = tree.find('Targets/Target/TargetOption/TargetArmAds/LDads/Misc')
    Misc.text = LINKFLAGS

    xml_indent(root)
    out.write(etree.tostring(root, encoding='utf-8'))
    out.close()

def MDK4Project(target, script):
    template_tree = etree.parse('template.uvproj')

    MDK45Project(template_tree, target, script)

    # remove project.uvopt file
    project_uvopt = os.path.abspath(target).replace('uvproj', 'uvopt')
    if os.path.isfile(project_uvopt):
        os.unlink(project_uvopt)

    # copy uvopt file
    if os.path.exists('template.uvopt'):
        import shutil
        shutil.copy2('template.uvopt', 'project.uvopt')

def MDK5Project(target, script):

    template_tree = etree.parse('template.uvprojx')

    MDK45Project(template_tree, target, script)

    # remove project.uvopt file
    project_uvopt = os.path.abspath(target).replace('uvprojx', 'uvoptx')
    if os.path.isfile(project_uvopt):
        os.unlink(project_uvopt)
    # copy uvopt file
    if os.path.exists('template.uvoptx'):
        import shutil
        shutil.copy2('template.uvoptx', 'project.uvoptx')

def MDKProject(target, script):
    template = file('template.Uv2', "rb")
    lines = template.readlines()

    project = file(target, "wb")
    project_path = os.path.dirname(os.path.abspath(target))

    line_index = 5
    # write group
    for group in script:
        lines.insert(line_index, 'Group (%s)\r\n' % group['name'])
        line_index += 1

    lines.insert(line_index, '\r\n')
    line_index += 1

    # write file

    ProjectFiles = []
    CPPPATH = []
    CPPDEFINES = []
    LINKFLAGS = ''
    CCFLAGS = ''

    # number of groups
    group_index = 1
    for group in script:
        # print group['name']

        # get each include path
        if group.has_key('CPPPATH') and group['CPPPATH']:
            if CPPPATH:
                CPPPATH += group['CPPPATH']
            else:
                CPPPATH += group['CPPPATH']

        # get each group's definitions
        if group.has_key('CPPDEFINES') and group['CPPDEFINES']:
            if CPPDEFINES:
                CPPDEFINES += group['CPPDEFINES']
            else:
                CPPDEFINES = group['CPPDEFINES']

        # get each group's link flags
        if group.has_key('LINKFLAGS') and group['LINKFLAGS']:
            if LINKFLAGS:
                LINKFLAGS += ' ' + group['LINKFLAGS']
            else:
                LINKFLAGS += group['LINKFLAGS']

        # generate file items
        for node in group['src']:
            fn = node.rfile()
            name = fn.name
            path = os.path.dirname(fn.abspath)
            basename = os.path.basename(path)
            path = _make_path_relative(project_path, path)
            path = os.path.join(path, name)
            if ProjectFiles.count(name):
                name = basename + '_' + name
            ProjectFiles.append(name)
            lines.insert(line_index, 'File %d,%d,<%s><%s>\r\n'
                % (group_index, _get_filetype(name), path, name))
            line_index += 1

        group_index = group_index + 1

    lines.insert(line_index, '\r\n')
    line_index += 1

    # remove repeat path
    paths = set()
    for path in CPPPATH:
        inc = _make_path_relative(project_path, os.path.normpath(path))
        paths.add(inc) #.replace('\\', '/')

    paths = [i for i in paths]
    CPPPATH = string.join(paths, ';')

    definitions = [i for i in set(CPPDEFINES)]
    CPPDEFINES = string.join(definitions, ', ')

    while line_index < len(lines):
        if lines[line_index].startswith(' ADSCINCD '):
            lines[line_index] = ' ADSCINCD (' + CPPPATH + ')\r\n'

        if lines[line_index].startswith(' ADSLDMC ('):
            lines[line_index] = ' ADSLDMC (' + LINKFLAGS + ')\r\n'

        if lines[line_index].startswith(' ADSCDEFN ('):
            lines[line_index] = ' ADSCDEFN (' + CPPDEFINES + ')\r\n'

        line_index += 1

    # write project
    for line in lines:
        project.write(line)

    project.close()
