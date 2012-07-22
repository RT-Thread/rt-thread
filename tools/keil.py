import os
import sys
import string

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent

fs_encoding = sys.getfilesystemencoding()

def _get_filetype(fn):
    if fn.rfind('.c') != -1 or fn.rfind('.C') != -1 or fn.rfind('.cpp') != -1:
        return 1

    # assemble file type
    if fn.rfind('.s') != -1 or fn.rfind('.S') != -1:
        return 2

    # header type
    if fn.rfind('.h') != -1:
        return 5

    # other filetype
    return 5

def MDK4AddGroup(ProjectFiles, parent, name, files, project_path):
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
        if ProjectFiles.count(name):
            name = basename + '_' + name
        ProjectFiles.append(name)
        file_name.text = name.decode(fs_encoding)
        file_type = SubElement(file, 'FileType')
        file_type.text = '%d' % _get_filetype(name)
        file_path = SubElement(file, 'FilePath')
        
        file_path.text = path.decode(fs_encoding)

def MDK4Project(target, script):
    project_path = os.path.dirname(os.path.abspath(target))
    
    tree = etree.parse('template.uvproj')
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
    for group in script:
        group_xml = MDK4AddGroup(ProjectFiles, groups, group['name'], group['src'], project_path)
        
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
                CPPDEFINES += group['CPPDEFINES']
        
        # get each group's link flags
        if group.has_key('LINKFLAGS') and group['LINKFLAGS']:
            if LINKFLAGS:
                LINKFLAGS += ' ' + group['LINKFLAGS']
            else:
                LINKFLAGS += group['LINKFLAGS']
    
    # remove repeat path
    paths = set()
    for path in CPPPATH:
        inc = _make_path_relative(project_path, os.path.normpath(path))
        paths.add(inc) #.replace('\\', '/')
    
    paths = [i for i in paths]
    paths.sort()
    CPPPATH = string.join(paths, ';')
    
    definitions = [i for i in set(CPPDEFINES)]
    CPPDEFINES = string.join(definitions, ', ')
    
    # write include path, definitions and link flags
    IncludePath = tree.find('Targets/Target/TargetOption/TargetArmAds/Cads/VariousControls/IncludePath')
    IncludePath.text = CPPPATH
    
    Define = tree.find('Targets/Target/TargetOption/TargetArmAds/Cads/VariousControls/Define')
    Define.text = CPPDEFINES

    Misc = tree.find('Targets/Target/TargetOption/TargetArmAds/LDads/Misc')
    Misc.text = LINKFLAGS
    
    xml_indent(root)
    out.write(etree.tostring(root, encoding='utf-8'))
    out.close()
    
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
                CPPDEFINES += ';' + group['CPPDEFINES']
            else:
                CPPDEFINES += group['CPPDEFINES']

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
