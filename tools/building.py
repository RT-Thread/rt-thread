import os
import sys
import string

from SCons.Script import *
from utils import _make_path_relative

BuildOptions = {}
Projects = []
Rtt_Root = ''
Env = None

class Win32Spawn:
    def spawn(self, sh, escape, cmd, args, env):
        import subprocess

        newargs = string.join(args[1:], ' ')
        cmdline = cmd + " " + newargs
        startupinfo = subprocess.STARTUPINFO()
        # startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
        penv = {}
        for key, value in env.iteritems():
            penv[key] = str(value)

        proc = subprocess.Popen(cmdline, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            stderr=subprocess.PIPE, startupinfo=startupinfo, shell = False, env=penv)
        data, err = proc.communicate()
        rv = proc.wait()
        if data:
            print data
        if err:
            print err

        if rv:
            return rv
        return 0

def GetVersion():
    import SCons.cpp
    import string

    rtdef = os.path.join(Rtt_Root, 'include', 'rtdef.h')

    # parse rtdef.h to get RT-Thread version 
    prepcessor = SCons.cpp.PreProcessor()
    f = file(rtdef, 'r')
    contents = f.read()
    f.close()
    prepcessor.process_contents(contents)
    def_ns = prepcessor.cpp_namespace

    version = int(filter(lambda ch: ch in '0123456789.', def_ns['RT_VERSION']))
    subversion = int(filter(lambda ch: ch in '0123456789.', def_ns['RT_SUBVERSION']))

    if def_ns.has_key('RT_REVISION'):
        revision = int(filter(lambda ch: ch in '0123456789.', def_ns['RT_REVISION']))
        return '%d.%d.%d' % (version, subversion, revision)

    return '0.%d.%d' % (version, subversion)

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
    from keil import MDKProject
    from keil import MDK4Project
    from iar import IARProject

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

def GetVersion():
    import SCons.cpp
    import string

    rtdef = os.path.join(Rtt_Root, 'include', 'rtdef.h')

    # parse rtdef.h to get RT-Thread version 
    prepcessor = SCons.cpp.PreProcessor()
    f = file(rtdef, 'r')
    contents = f.read()
    f.close()
    prepcessor.process_contents(contents)
    def_ns = prepcessor.cpp_namespace

    version = int(filter(lambda ch: ch in '0123456789.', def_ns['RT_VERSION']))
    subversion = int(filter(lambda ch: ch in '0123456789.', def_ns['RT_SUBVERSION']))

    if def_ns.has_key('RT_REVISION'):
        revision = int(filter(lambda ch: ch in '0123456789.', def_ns['RT_REVISION']))
        return '%d.%d.%d' % (version, subversion, revision)

    return '0.%d.%d' % (version, subversion)
