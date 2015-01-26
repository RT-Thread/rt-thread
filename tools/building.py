#
# File      : building.py
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

from SCons.Script import *
from utils import _make_path_relative

BuildOptions = {}
Projects = []
Rtt_Root = ''
Env = None

class Win32Spawn:
    def spawn(self, sh, escape, cmd, args, env):
        # deal with the cmd build-in commands which cannot be used in
        # subprocess.Popen
        if cmd == 'del':
            for f in args[1:]:
                try:
                    os.remove(f)
                except Exception as e:
                    print 'Error removing file: %s' % e
                    return -1
            return 0

        import subprocess

        newargs = string.join(args[1:], ' ')
        cmdline = cmd + " " + newargs

        # Make sure the env is constructed by strings
        _e = dict([(k, str(v)) for k, v in env.items()])

        # Windows(tm) CreateProcess does not use the env passed to it to find
        # the executables. So we have to modify our own PATH to make Popen
        # work.
        old_path = os.environ['PATH']
        os.environ['PATH'] = _e['PATH']

        try:
            proc = subprocess.Popen(cmdline, env=_e, shell=False)
        except Exception as e:
            print 'Error in calling:\n%s' % cmdline
            print 'Exception: %s: %s' % (e, os.strerror(e.errno))
            return e.errno
        finally:
            os.environ['PATH'] = old_path

        return proc.wait()

def PrepareBuilding(env, root_directory, has_libcpu=False, remove_components = []):
    import SCons.cpp
    import rtconfig

    global BuildOptions
    global Projects
    global Env
    global Rtt_Root

    Env = env
    Rtt_Root = root_directory

    # add compability with Keil MDK 4.6 which changes the directory of armcc.exe
    if rtconfig.PLATFORM == 'armcc':
        if not os.path.isfile(os.path.join(rtconfig.EXEC_PATH, 'armcc.exe')):
            if rtconfig.EXEC_PATH.find('bin40') > 0:
                rtconfig.EXEC_PATH = rtconfig.EXEC_PATH.replace('bin40', 'armcc/bin')
                Env['LINKFLAGS']=Env['LINKFLAGS'].replace('RV31', 'armcc')

        # reset AR command flags
        env['ARCOM'] = '$AR --create $TARGET $SOURCES'
        env['LIBPREFIX']   = ''
        env['LIBSUFFIX']   = '.lib'
        env['LIBLINKPREFIX'] = ''
        env['LIBLINKSUFFIX']   = '.lib'
        env['LIBDIRPREFIX'] = '--userlibpath '

    # patch for win32 spawn
    if env['PLATFORM'] == 'win32':
        win32_spawn = Win32Spawn()
        win32_spawn.env = env
        env['SPAWN'] = win32_spawn.spawn

    if env['PLATFORM'] == 'win32':
        os.environ['PATH'] = rtconfig.EXEC_PATH + ";" + os.environ['PATH']
    else:
        os.environ['PATH'] = rtconfig.EXEC_PATH + ":" + os.environ['PATH']

    # add program path
    env.PrependENVPath('PATH', rtconfig.EXEC_PATH)

    # add library build action
    act = SCons.Action.Action(BuildLibInstallAction, 'Install compiled library... $TARGET')
    bld = Builder(action = act)
    Env.Append(BUILDERS = {'BuildLib': bld})

    # parse rtconfig.h to get used component
    PreProcessor = SCons.cpp.PreProcessor()
    f = file('rtconfig.h', 'r')
    contents = f.read()
    f.close()
    PreProcessor.process_contents(contents)
    BuildOptions = PreProcessor.cpp_namespace

    # add copy option
    AddOption('--copy',
                      dest='copy',
                      action='store_true',
                      default=False,
                      help='copy rt-thread directory to local.')
    AddOption('--copy-header',
                      dest='copy-header',
                      action='store_true',
                      default=False,
                      help='copy header of rt-thread directory to local.')
    AddOption('--cscope',
                      dest='cscope',
                      action='store_true',
                      default=False,
                      help='Build Cscope cross reference database. Requires cscope installed.')
    AddOption('--clang-analyzer',
                      dest='clang-analyzer',
                      action='store_true',
                      default=False,
                      help='Perform static analyze with Clang-analyzer. '+\
                           'Requires Clang installed.\n'+\
                           'It is recommended to use with scan-build like this:\n'+\
                           '`scan-build scons --clang-analyzer`\n'+\
                           'If things goes well, scan-build will instruct you to invoke scan-view.')

    if GetOption('clang-analyzer'):
        # perform what scan-build does
        env.Replace(
                CC   = 'ccc-analyzer',
                CXX  = 'c++-analyzer',
                # skip as and link
                LINK = 'true',
                AS   = 'true',)
        env["ENV"].update(x for x in os.environ.items() if x[0].startswith("CCC_"))
        # only check, don't compile. ccc-analyzer use CCC_CC as the CC.
        # fsyntax-only will give us some additional warning messages
        env['ENV']['CCC_CC']  = 'clang'
        env.Append(CFLAGS=['-fsyntax-only', '-Wall', '-Wno-invalid-source-encoding'])
        env['ENV']['CCC_CXX'] = 'clang++'
        env.Append(CXXFLAGS=['-fsyntax-only', '-Wall', '-Wno-invalid-source-encoding'])
        # remove the POST_ACTION as it will cause meaningless errors(file not
        # found or something like that).
        rtconfig.POST_ACTION = ''

    # add build library option
    AddOption('--buildlib',
                      dest='buildlib',
                      type='string',
                      help='building library of a component')
    AddOption('--cleanlib',
                      dest='cleanlib',
                      action='store_true',
                      default=False,
                      help='clean up the library by --buildlib')

    # add target option
    AddOption('--target',
                      dest='target',
                      type='string',
                      help='set target project: mdk/iar/vs/ua')

    #{target_name:(CROSS_TOOL, PLATFORM)}
    tgt_dict = {'mdk':('keil', 'armcc'),
                'mdk4':('keil', 'armcc'),
                'mdk5':('keil', 'armcc'),
                'iar':('iar', 'iar'),
                'vs':('msvc', 'cl'),
                'vs2012':('msvc', 'cl'),
                'cb':('keil', 'armcc'),
                'ua':('keil', 'armcc')}
    tgt_name = GetOption('target')
    if tgt_name:
        # --target will change the toolchain settings which clang-analyzer is
        # depend on
        if GetOption('clang-analyzer'):
            print '--clang-analyzer cannot be used with --target'
            sys.exit(1)

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

    # add comstr option
    AddOption('--verbose',
                dest='verbose',
                action='store_true',
                default=False,
                help='print verbose information during build')

    if not GetOption('verbose'):
        # override the default verbose command string
        env.Replace(
            ARCOMSTR = 'AR $TARGET',
            ASCOMSTR = 'AS $TARGET',
            ASPPCOMSTR = 'AS $TARGET',
            CCCOMSTR = 'CC $TARGET',
            CXXCOMSTR = 'CXX $TARGET',
            LINKCOMSTR = 'LINK $TARGET'
        )

    # we need to seperate the variant_dir for BSPs and the kernels. BSPs could
    # have their own components etc. If they point to the same folder, SCons
    # would find the wrong source code to compile.
    bsp_vdir = 'build/bsp'
    kernel_vdir = 'build/kernel'
    # board build script
    objs = SConscript('SConscript', variant_dir=bsp_vdir, duplicate=0)
    # include kernel
    objs.extend(SConscript(Rtt_Root + '/src/SConscript', variant_dir=kernel_vdir + '/src', duplicate=0))
    # include libcpu
    if not has_libcpu:
        objs.extend(SConscript(Rtt_Root + '/libcpu/SConscript',
                    variant_dir=kernel_vdir + '/libcpu', duplicate=0))

    # include components
    objs.extend(SConscript(Rtt_Root + '/components/SConscript',
                           variant_dir=kernel_vdir + '/components',
                           duplicate=0,
                           exports='remove_components'))

    return objs

def PrepareModuleBuilding(env, root_directory):
    import rtconfig

    global Env
    global Rtt_Root

    Env = env
    Rtt_Root = root_directory

    # add build/clean library option for library checking
    AddOption('--buildlib',
              dest='buildlib',
              type='string',
              help='building library of a component')
    AddOption('--cleanlib',
              dest='cleanlib',
              action='store_true',
              default=False,
              help='clean up the library by --buildlib')

    # add program path
    env.PrependENVPath('PATH', rtconfig.EXEC_PATH)

def GetConfigValue(name):
    assert type(name) == str, 'GetConfigValue: only string parameter is valid'
    try:
        return BuildOptions[name]
    except:
        return ''

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
    if group.has_key('LIBS'):
        if src_group.has_key('LIBS'):
            src_group['LIBS'] = src_group['LIBS'] + group['LIBS']
        else:
            src_group['LIBS'] = group['LIBS']
    if group.has_key('LIBPATH'):
        if src_group.has_key('LIBPATH'):
            src_group['LIBPATH'] = src_group['LIBPATH'] + group['LIBPATH']
        else:
            src_group['LIBPATH'] = group['LIBPATH']

def DefineGroup(name, src, depend, **parameters):
    global Env
    if not GetDepend(depend):
        return []

    # find exist group and get path of group
    group_path = ''
    for g in Projects:
        if g['name'] == name:
            group_path = g['path']
    if group_path == '':
        group_path = GetCurrentDir()

    group = parameters
    group['name'] = name
    group['path'] = group_path
    if type(src) == type(['src1']):
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

    # check whether to clean up library
    if GetOption('cleanlib') and os.path.exists(os.path.join(group['path'], GroupLibFullName(name, Env))):
        if group['src'] != []:
            print 'Remove library:', GroupLibFullName(name, Env)
            do_rm_file(os.path.join(group['path'], GroupLibFullName(name, Env)))

    # check whether exist group library
    if not GetOption('buildlib') and os.path.exists(os.path.join(group['path'], GroupLibFullName(name, Env))):
        group['src'] = []
        if group.has_key('LIBS'): group['LIBS'] = group['LIBS'] + [GroupLibName(name, Env)]
        else : group['LIBS'] = [GroupLibName(name, Env)]
        if group.has_key('LIBPATH'): group['LIBPATH'] = group['LIBPATH'] + [GetCurrentDir()]
        else : group['LIBPATH'] = [GetCurrentDir()]

    if group.has_key('LIBS'):
        Env.Append(LIBS = group['LIBS'])
    if group.has_key('LIBPATH'):
        Env.Append(LIBPATH = group['LIBPATH'])

    if group.has_key('LIBRARY'):
        objs = Env.Library(name, group['src'])
    else:
        objs = group['src']

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

PREBUILDING = []
def RegisterPreBuildingAction(act):
    global PREBUILDING
    assert callable(act), 'Could only register callable objects. %s received' % repr(act)
    PREBUILDING.append(act)

def PreBuilding():
    global PREBUILDING
    for a in PREBUILDING:
        a()

def GroupLibName(name, env):
    import rtconfig
    if rtconfig.PLATFORM == 'armcc':
        return name + '_rvds'
    elif rtconfig.PLATFORM == 'gcc':
        return name + '_gcc'

    return name

def GroupLibFullName(name, env):
    return env['LIBPREFIX'] + GroupLibName(name, env) + env['LIBSUFFIX']

def BuildLibInstallAction(target, source, env):
    lib_name = GetOption('buildlib')
    for Group in Projects:
        if Group['name'] == lib_name:
            lib_name = GroupLibFullName(Group['name'], env)
            dst_name = os.path.join(Group['path'], lib_name)
            print 'Copy %s => %s' % (lib_name, dst_name)
            do_copy_file(lib_name, dst_name)
            break

def DoBuilding(target, objects):
    program = None
    # check whether special buildlib option
    lib_name = GetOption('buildlib')
    if lib_name:
        # build library with special component
        for Group in Projects:
            if Group['name'] == lib_name:
                lib_name = GroupLibName(Group['name'], Env)
                objects = Env.Object(Group['src'])
                program = Env.Library(lib_name, objects)

                # add library copy action
                Env.BuildLib(lib_name, program)

                break
    else:
        program = Env.Program(target, objects)

    EndBuilding(target, program)

def EndBuilding(target, program = None):
    import rtconfig

    Env.AddPostAction(target, rtconfig.POST_ACTION)

    if GetOption('target') == 'mdk':
        from keil import MDKProject
        from keil import MDK4Project
        from keil import MDK5Project

        template = os.path.isfile('template.Uv2')
        if template:
            MDKProject('project.Uv2', Projects)
        else:
            template = os.path.isfile('template.uvproj')
            if template:
                MDK4Project('project.uvproj', Projects)
            else:
                template = os.path.isfile('template.uvprojx')
                if template:
                    MDK5Project('project.uvprojx', Projects)
                else:
                    print 'No template project file found.'


    if GetOption('target') == 'mdk4':
        from keil import MDK4Project
        MDK4Project('project.uvproj', Projects)

    if GetOption('target') == 'mdk5':
        from keil import MDK5Project
        MDK5Project('project.uvprojx', Projects)

    if GetOption('target') == 'iar':
        from iar import IARProject
        IARProject('project.ewp', Projects)

    if GetOption('target') == 'vs':
        from vs import VSProject
        VSProject('project.vcproj', Projects, program)

    if GetOption('target') == 'vs2012':
        from vs2012 import VS2012Project
        VS2012Project('project.vcxproj', Projects, program)

    if GetOption('target') == 'cb':
        from codeblocks import CBProject
        CBProject('project.cbp', Projects, program)

    if GetOption('target') == 'ua':
        from ua import PrepareUA
        PrepareUA(Projects, Rtt_Root, str(Dir('#')))

    if GetOption('copy') and program != None:
        MakeCopy(program)
    if GetOption('copy-header') and program != None:
        MakeCopyHeader(program)

    if GetOption('cscope'):
        from cscope import CscopeDatabase
        CscopeDatabase(Projects)

def SrcRemove(src, remove):
    if not src:
        return

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

def GlobSubDir(sub_dir, ext_name):
    import os
    import glob

    def glob_source(sub_dir, ext_name):
        list = os.listdir(sub_dir)
        src = glob.glob(os.path.join(sub_dir, ext_name))

        for item in list:
            full_subdir = os.path.join(sub_dir, item)
            if os.path.isdir(full_subdir):
                src += glob_source(full_subdir, ext_name)
        return src

    dst = []
    src = glob_source(sub_dir, ext_name)
    for item in src:
        dst.append(os.path.relpath(item, sub_dir))
    return dst

def file_path_exist(path, *args):
    return os.path.exists(os.path.join(path, *args))

def do_rm_file(src):
    if os.path.exists(src):
       os.unlink(src)

def do_copy_file(src, dst):
    import shutil
    # check source file
    if not os.path.exists(src):
        return

    path = os.path.dirname(dst)
    # mkdir if path not exist
    if not os.path.exists(path):
        os.makedirs(path)

    shutil.copy2(src, dst)

def do_copy_folder(src_dir, dst_dir):
    import shutil
    # check source directory
    if not os.path.exists(src_dir):
        return

    if os.path.exists(dst_dir):
        shutil.rmtree(dst_dir)

    shutil.copytree(src_dir, dst_dir)

source_ext = ["c", "h", "s", "S", "cpp", "xpm"]
source_list = []

def walk_children(child):
    global source_list
    global source_ext

    # print child
    full_path = child.rfile().abspath
    file_type  = full_path.rsplit('.',1)[1]
    #print file_type
    if file_type in source_ext:
        if full_path not in source_list:
            source_list.append(full_path)

    children = child.all_children()
    if children != []:
        for item in children:
            walk_children(item)

def MakeCopy(program):
    global source_list
    global Rtt_Root
    global Env

    target_path = os.path.join(Dir('#').abspath, 'rt-thread')

    if Env['PLATFORM'] == 'win32':
        RTT_ROOT = Rtt_Root.lower()
    else:
        RTT_ROOT = Rtt_Root

    if target_path.startswith(RTT_ROOT):
        return

    for item in program:
        walk_children(item)

    source_list.sort()

    # filte source file in RT-Thread
    target_list = []
    for src in source_list:
        if Env['PLATFORM'] == 'win32':
            src = src.lower()

        if src.startswith(RTT_ROOT):
            target_list.append(src)

    source_list = target_list
    # get source path
    src_dir = []
    for src in source_list:
        src = src.replace(RTT_ROOT, '')
        if src[0] == os.sep or src[0] == '/':
            src = src[1:]

        path = os.path.dirname(src)
        sub_path = path.split(os.sep)
        full_path = RTT_ROOT
        for item in sub_path:
            full_path = os.path.join(full_path, item)
            if full_path not in src_dir:
                src_dir.append(full_path)

    for item in src_dir:
        source_list.append(os.path.join(item, 'SConscript'))

    for src in source_list:
        dst = src.replace(RTT_ROOT, '')
        if dst[0] == os.sep or dst[0] == '/':
            dst = dst[1:]
        print '=> ', dst
        dst = os.path.join(target_path, dst)
        do_copy_file(src, dst)

    # copy tools directory
    print "=>  tools"
    do_copy_folder(os.path.join(RTT_ROOT, "tools"), os.path.join(target_path, "tools"))
    do_copy_file(os.path.join(RTT_ROOT, 'AUTHORS'), os.path.join(target_path, 'AUTHORS'))
    do_copy_file(os.path.join(RTT_ROOT, 'COPYING'), os.path.join(target_path, 'COPYING'))

def MakeCopyHeader(program):
    global source_ext
    source_ext = []
    source_ext = ["h", "xpm"]
    global source_list
    global Rtt_Root
    global Env

    target_path = os.path.join(Dir('#').abspath, 'rt-thread')

    if Env['PLATFORM'] == 'win32':
        RTT_ROOT = Rtt_Root.lower()
    else:
        RTT_ROOT = Rtt_Root

    if target_path.startswith(RTT_ROOT):
        return

    for item in program:
        walk_children(item)

    source_list.sort()

    # filte source file in RT-Thread
    target_list = []
    for src in source_list:
        if Env['PLATFORM'] == 'win32':
            src = src.lower()

        if src.startswith(RTT_ROOT):
            target_list.append(src)

    source_list = target_list

    for src in source_list:
        dst = src.replace(RTT_ROOT, '')
        if dst[0] == os.sep or dst[0] == '/':
            dst = dst[1:]
        print '=> ', dst
        dst = os.path.join(target_path, dst)
        do_copy_file(src, dst)

    # copy tools directory
    print "=>  tools"
    do_copy_folder(os.path.join(RTT_ROOT, "tools"), os.path.join(target_path, "tools"))
    do_copy_file(os.path.join(RTT_ROOT, 'AUTHORS'), os.path.join(target_path, 'AUTHORS'))
    do_copy_file(os.path.join(RTT_ROOT, 'COPYING'), os.path.join(target_path, 'COPYING'))
