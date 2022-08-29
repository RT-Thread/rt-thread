# SEGGER Embedded Studio Project Generator

import os
import sys

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent
from utils import ProjectInfo

def SDKAddGroup(parent, name, files, project_path):
    # don't add an empty group
    if len(files) == 0:
        return

    group = SubElement(parent, 'folder', attrib={'Name': name})

    for f in files:
        fn = f.rfile()
        name = fn.name
        path = os.path.dirname(fn.abspath)

        basename = os.path.basename(path)
        path = _make_path_relative(project_path, path)
        elm_attr_name = os.path.join(path, name)

        file = SubElement(group, 'file', attrib={'file_name': elm_attr_name})

    return group

def SESProject(env) :
    target = 'project.emProject'
    tree = etree.parse('template.emProject')
    # print(etree.dump(tree.getroot()))
    # etree.dump(tree.getroot())

    project = ProjectInfo(env)
    # print(project)
    # return

    project_path = os.path.abspath(env['BSP_ROOT'])
    script = env['project']

    root = tree.getroot()
    out = file(target, 'w')
    out.write('<!DOCTYPE CrossStudio_Project_File>\n')

    CPPPATH = []
    CPPDEFINES = []
    LINKFLAGS = ''
    CFLAGS = ''

    project_node = tree.find('project')

    for group in script:
        # print(group)

        group_tree = SDKAddGroup(project_node, group['name'], group['src'], project_path)

        # get each group's cc flags
        if 'CFLAGS' in group and group['CFLAGS']:
            if CFLAGS:
                CFLAGS += ' ' + group['CFLAGS']
            else:
                CFLAGS += group['CFLAGS']

        # get each group's link flags
        if 'LINKFLAGS' in group and group['LINKFLAGS']:
            if LINKFLAGS:
                LINKFLAGS += ' ' + group['LINKFLAGS']
            else:
                LINKFLAGS += group['LINKFLAGS']

    # write include path, definitions and link flags
    path = ';'.join([_make_path_relative(project_path, os.path.normpath(i)) for i in project['CPPPATH']])
    path = path.replace('\\', '/')
    defines = ';'.join(set(project['CPPDEFINES']))

    node = tree.findall('project/configuration')
    for item in node:
        if item.get('c_preprocessor_definitions'):
            item.set('c_preprocessor_definitions', defines)

        if item.get('c_user_include_directories'):
            item.set('c_user_include_directories', path)

    xml_indent(root)
    out.write(etree.tostring(root, encoding='utf-8'))
    out.close()

    return
