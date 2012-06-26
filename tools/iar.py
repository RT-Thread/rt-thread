import os
import sys
import string

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
        file_name.text = ('$PROJ_DIR$\\' + path).decode(fs_encoding)

def IARWorkspace(target):
    # make an workspace 
    workspace = target.replace('.ewp', '.eww')
    out = file(workspace, 'wb')
    xml = iar_workspace % target
    out.write(xml)
    out.close()
    
def IARProject(target, script):
    project_path = os.path.dirname(os.path.abspath(target))

    tree = etree.parse('template.ewp')
    root = tree.getroot()

    out = file(target, 'wb')

    CPPPATH = []
    CPPDEFINES = []
    LINKFLAGS = ''
    CCFLAGS = ''
    
    # add group
    for group in script:
        IARAddGroup(root, group['name'], group['src'], project_path)

        # get each include path
        if group.has_key('CPPPATH') and group['CPPPATH']:
            CPPPATH += group['CPPPATH']
        
        # get each group's definitions
        if group.has_key('CPPDEFINES') and group['CPPDEFINES']:
            CPPDEFINES += group['CPPDEFINES']
        
        # get each group's link flags
        if group.has_key('LINKFLAGS') and group['LINKFLAGS']:
            LINKFLAGS += group['LINKFLAGS']
    
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
                state.text = '$PROJ_DIR$\\' + path
        if name.text == 'CCDefines':
            for define in CPPDEFINES:
                state = SubElement(option, 'state')
                state.text = define
    
    xml_indent(root)
    out.write(etree.tostring(root, encoding='utf-8'))
    out.close()
    
    IARWorkspace(target)
