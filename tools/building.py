import os
import sys
import string

import xml.etree.ElementTree as etree
from xml.etree.ElementTree import SubElement

from SCons.Script import *

BuildOptions = {}
Projects = []
Rtt_Root = ''
Env = None
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

def splitall(loc):
    """
    Return a list of the path components in loc. (Used by relpath_).

    The first item in the list will be  either ``os.curdir``, ``os.pardir``, empty,
    or the root directory of loc (for example, ``/`` or ``C:\\).

    The other items in the list will be strings.

    Adapted from *path.py* by Jason Orendorff.
    """
    parts = []
    while loc != os.curdir and loc != os.pardir:
        prev = loc
        loc, child = os.path.split(prev)
        if loc == prev:
            break
        parts.append(child)
    parts.append(loc)
    parts.reverse()
    return parts

def _make_path_relative(origin, dest):
    """
    Return the relative path between origin and dest.

    If it's not possible return dest.


    If they are identical return ``os.curdir``

    Adapted from `path.py <http://www.jorendorff.com/articles/python/path/>`_ by Jason Orendorff.
    """
    origin = os.path.abspath(origin).replace('\\', '/')
    dest = os.path.abspath(dest).replace('\\', '/')
    #
    orig_list = splitall(os.path.normcase(origin))
    # Don't normcase dest!  We want to preserve the case.
    dest_list = splitall(dest)
    #
    if orig_list[0] != os.path.normcase(dest_list[0]):
        # Can't get here from there.
        return dest
    #
    # Find the location where the two paths start to differ.
    i = 0
    for start_seg, dest_seg in zip(orig_list, dest_list):
        if start_seg != os.path.normcase(dest_seg):
            break
        i += 1
    #
    # Now i is the point where the two paths diverge.
    # Need a certain number of "os.pardir"s to work up
    # from the origin to the point of divergence.
    segments = [os.pardir] * (len(orig_list) - i)
    # Need to add the diverging part of dest_list.
    segments += dest_list[i:]
    if len(segments) == 0:
        # If they happen to be identical, use os.curdir.
        return os.curdir
    else:
        # return os.path.join(*segments).replace('\\', '/')
        return os.path.join(*segments)

def xml_indent(elem, level=0):
    i = "\n" + level*"  "
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + "  "
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
        for elem in elem:
            xml_indent(elem, level+1)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i

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

iar_workspace = '''<?xml version="1.0" encoding="iso-8859-1"?>

<workspace>
  <project>
    <path>$WS_DIR$\%s</path>
  </project>
  <batchBuild/>
</workspace>


'''

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
        
        if name.text == 'CCIncludePath2':
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
    if not groups:
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
                CPPDEFINES += ';' + group['CPPDEFINES']
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

def BuilderProject(target, script):
    project = file(target, "wb")
    project_path = os.path.dirname(os.path.abspath(target))

    # write file

    CPPPATH = []
    CPPDEFINES = []
    LINKFLAGS = ''
    CCFLAGS = ''

    # number of groups
    group_index = 1
    for group in script:
        # print group['name']

        # generate file items
        for node in group['src']:
            fn = node.rfile()
            name = fn.name
            path = os.path.dirname(fn.abspath)
            path = _make_path_relative(project_path, path)
            path = os.path.join(path, name)
            project.write('%s\r\n' % path)

        group_index = group_index + 1

    project.close()

class Win32Spawn:
    def spawn(self, sh, escape, cmd, args, env):
        import subprocess

        newargs = string.join(args[1:], ' ')
        cmdline = cmd + " " + newargs
        startupinfo = subprocess.STARTUPINFO()
        # startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
        proc = subprocess.Popen(cmdline, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            stderr=subprocess.PIPE, startupinfo=startupinfo, shell = False)
        data, err = proc.communicate()
        rv = proc.wait()
        if rv:
            print err
            return rv

        if data:
            print data
        return 0

def PrepareBuilding(env, root_directory, has_libcpu=False):
    import SCons.cpp
    import rtconfig

    global BuildOptions
    global Projects
    global Env
    global Rtt_Root

    Env = env
    Rtt_Root = root_directory

    # patch for win32 spawn
    if env['PLATFORM'] == 'win32' and rtconfig.PLATFORM == 'gcc':
        win32_spawn = Win32Spawn()
        win32_spawn.env = env
        env['SPAWN'] = win32_spawn.spawn

    # add program path
    env.PrependENVPath('PATH', rtconfig.EXEC_PATH)

    # parse rtconfig.h to get used component
    PreProcessor = SCons.cpp.PreProcessor()
    f = file('rtconfig.h', 'r')
    contents = f.read()
    f.close()
    PreProcessor.process_contents(contents)
    BuildOptions = PreProcessor.cpp_namespace

    # add target option
    AddOption('--target',
                      dest='target',
                      type='string',
                      help='set target project: mdk')

    #{target_name:(CROSS_TOOL, PLATFORM)}
    tgt_dict = {'mdk':('keil', 'armcc'),
                'mdk4':('keil', 'armcc'),
                'iar':('iar', 'iar')}
    tgt_name = GetOption('target')
    if tgt_name:
        SetOption('no_exec', 1)
        try:
            rtconfig.CROSS_TOOL, rtconfig.PLATFORM = tgt_dict[tgt_name]
        except KeyError:
            print 'Unknow target: %s. Avaible targets: %s' % \
                    (tgt_name, ', '.join(tgt_dict.keys()))
            sys.exit(1)
    elif (GetDepend('RT_USING_NEWLIB') == False and GetDepend('RT_USING_NOLIBC') == False) \
	   and rtconfig.PLATFORM == 'gcc':
        AddDepend('RT_USING_MINILIBC')

    #env['CCCOMSTR'] = "CC $TARGET"
    #env['ASCOMSTR'] = "AS $TARGET"
    #env['LINKCOMSTR'] = "Link $TARGET"

    # board build script
    objs = SConscript('SConscript', variant_dir='build/bsp', duplicate=0)
    Repository(Rtt_Root)
    # include kernel
    objs.append(SConscript('src/SConscript', variant_dir='build/src', duplicate=0))
    # include libcpu
    if not has_libcpu:
        objs.append(SConscript('libcpu/SConscript', variant_dir='build/libcpu', duplicate=0))
    # include components
    objs.append(SConscript('components/SConscript', variant_dir='build/components', duplicate=0))

    return objs

def PrepareModuleBuilding(env, root_directory):
    import SCons.cpp
    import rtconfig

    global BuildOptions
    global Projects
    global Env
    global Rtt_Root

    Env = env
    Rtt_Root = root_directory

    # add program path
    env.PrependENVPath('PATH', rtconfig.EXEC_PATH)

def GetDepend(depend):
    building = True
    if type(depend) == type('str'):
        if not BuildOptions.has_key(depend) or BuildOptions[depend] == 0:
            building = False
        elif BuildOptions[depend] != '':
            return BuildOptions[depend]
          
        return building

    # for list type depend
    for item in depend:
        if item != '':
            if not BuildOptions.has_key(item) or BuildOptions[item] == 0:
                building = False

    return building

def AddDepend(option):
    BuildOptions[option] = 1

def MergeGroup(src_group, group):
    src_group['src'] = src_group['src'] + group['src']
    if group.has_key('CCFLAGS'):
        if src_group.has_key('CCFLAGS'):
            src_group['CCFLAGS'] = src_group['CCFLAGS'] + group['CCFLAGS']
        else:
            src_group['CCFLAGS'] = group['CCFLAGS']
    if group.has_key('CPPPATH'):
        if src_group.has_key('CPPPATH'):
            src_group['CPPPATH'] = src_group['CPPPATH'] + group['CPPPATH']
        else:
            src_group['CPPPATH'] = group['CPPPATH']
    if group.has_key('CPPDEFINES'):
        if src_group.has_key('CPPDEFINES'):
            src_group['CPPDEFINES'] = src_group['CPPDEFINES'] + group['CPPDEFINES']
        else:
            src_group['CPPDEFINES'] = group['CPPDEFINES']
    if group.has_key('LINKFLAGS'):
        if src_group.has_key('LINKFLAGS'):
            src_group['LINKFLAGS'] = src_group['LINKFLAGS'] + group['LINKFLAGS']
        else:
            src_group['LINKFLAGS'] = group['LINKFLAGS']
    if group.has_key('LIBRARY'):
        if src_group['LIBRARY'].has_key('LIBRARY'):
            src_group['LIBRARY'] = src_group['LIBRARY'] + group['LIBRARY']
        else:
            src_group['LIBRARY'] = group['LIBRARY']

def DefineGroup(name, src, depend, **parameters):
    global Env
    if not GetDepend(depend):
        return []

    group = parameters
    group['name'] = name
    if type(src) == type(['src1', 'str2']):
        group['src'] = File(src)
    else:
        group['src'] = src

    if group.has_key('CCFLAGS'):
        Env.Append(CCFLAGS = group['CCFLAGS'])
    if group.has_key('CPPPATH'):
        Env.Append(CPPPATH = group['CPPPATH'])
    if group.has_key('CPPDEFINES'):
        Env.Append(CPPDEFINES = group['CPPDEFINES'])
    if group.has_key('LINKFLAGS'):
        Env.Append(LINKFLAGS = group['LINKFLAGS'])

    objs = Env.Object(group['src'])

    if group.has_key('LIBRARY'):
        objs = Env.Library(name, objs)

    # merge group 
    for g in Projects:
        if g['name'] == name:
            # merge to this group
            MergeGroup(g, group)
            return objs

    # add a new group 
    Projects.append(group)

    return objs

def GetCurrentDir():
    conscript = File('SConscript')
    fn = conscript.rfile()
    name = fn.name
    path = os.path.dirname(fn.abspath)
    return path

def EndBuilding(target):
    import rtconfig
    Env.AddPostAction(target, rtconfig.POST_ACTION)

    if GetOption('target') == 'mdk':
        template = os.path.isfile('template.Uv2')
        if template:
            MDKProject('project.Uv2', Projects)
        else:
            template = os.path.isfile('template.uvproj')
            if template:
                MDK4Project('project.uvproj', Projects)
            else:
                print 'No template project file found.'

    if GetOption('target') == 'mdk4':
        MDK4Project('project.uvproj', Projects)

    if GetOption('target') == 'iar':
        IARProject('project.ewp', Projects) 

def SrcRemove(src, remove):
	if type(src[0]) == type('str'):
		for item in src:
			if os.path.basename(item) in remove:
				src.remove(item)
		return

	for item in src:
		if os.path.basename(item.rstr()) in remove:
			src.remove(item)
