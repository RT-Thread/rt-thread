import os
import sys
import string
import building

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement
from utils import _make_path_relative
from utils import xml_indent
fs_encoding = sys.getfilesystemencoding()

def VS_AddGroup(ProjectFiles, parent, name, files, project_path):
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

def VSProject(target, script):
    project_path = os.path.dirname(os.path.abspath(target))
    
    tree = etree.parse('template.vcproj')
    root = tree.getroot()
    
    out = file(target, 'wb')
    out.write('<?xml version="1.0" encoding="UTF-8"?>\r\n')
    
    CPPPATH = []
    CPPDEFINES = []
    LINKFLAGS = ''
    CCFLAGS = ''
    ProjectFiles = []
    
    # add group
    for elem in tree.iter(tag='Filter'):
        if elem.attrib['Name'] == 'Source Files':
            #print elem.tag, elem.attrib
            break

    for group in script:
        group_xml = VS_AddGroup(ProjectFiles, elem, group['name'], group['src'], project_path)
        
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
    
    # write include path, definitions
    for elem in tree.iter(tag='Tool'):
        if elem.attrib['Name'] == 'VCCLCompilerTool':
            #print elem.tag, elem.attrib
            break
    elem.set('AdditionalIncludeDirectories', CPPPATH)

    definitions = ';'.join(building.Env['CPPDEFINES'])
    elem.set('PreprocessorDefinitions', definitions)
    # write link flags

    # write lib dependence 
    for elem in tree.iter(tag='Tool'):
        if elem.attrib['Name'] == 'VCLinkerTool':
            break
    libs_with_extention = [i+'.lib' for i in building.Env['LIBS']]
    libs = ' '.join(libs_with_extention)
    elem.set('AdditionalDependencies', libs)

    if building.Env.has_key('LIBPATH'):
    #if building.Env['LIBPATH']:
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
