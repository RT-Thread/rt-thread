#
# File      : utils.py
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
# 2024-04-21     Bernard      Add ImportModule to import local module

import sys
import os
import re

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


source_ext = ["c", "h", "s", "S", "cpp", "cxx", "cc", "xpm"]
source_list = []

def walk_children(child):
    global source_list
    global source_ext

    # print child
    full_path = child.rfile().abspath
    file_type_list  = full_path.rsplit('.',1)
    #print file_type
    if (len(file_type_list) > 1):
        file_type = full_path.rsplit('.',1)[1]

        if file_type in source_ext:
            if full_path not in source_list:
                source_list.append(full_path)

    children = child.all_children()
    if children != []:
        for item in children:
            walk_children(item)

def PrefixPath(prefix, path):
    path = os.path.abspath(path)
    prefix = os.path.abspath(prefix)

    if sys.platform == 'win32':
        prefix = prefix.lower()
        path = path.lower()

    if path.startswith(prefix):
        return True

    return False

def ListMap(l):
    ret_list = []
    for item in l:
        if type(item) == type(()):
            ret = ListMap(item)
            ret_list += ret
        elif type(item) == type([]):
            ret = ListMap(item)
            ret_list += ret
        else:
            ret_list.append(item)

    return ret_list

def TargetGetList(env, postfix):
    global source_ext
    global source_list

    target = env['target']

    source_ext = postfix
    for item in target:
        walk_children(item)

    source_list.sort()

    return source_list

def ProjectInfo(env):

    project  = env['project']
    RTT_ROOT = env['RTT_ROOT']
    BSP_ROOT = env['BSP_ROOT']

    FILES       = []
    DIRS        = []
    HEADERS     = []
    CPPPATH     = []
    CPPDEFINES  = []

    for group in project:
        # get each files
        if 'src' in group and group['src']:
            FILES += group['src']

        # get each include path
        if 'CPPPATH' in group and group['CPPPATH']:
            CPPPATH += group['CPPPATH']

    if 'CPPDEFINES' in env:
        CPPDEFINES = env['CPPDEFINES']
        CPPDEFINES = ListMap(CPPDEFINES)

    # process FILES and DIRS
    if len(FILES):
        # use absolute path
        for i in range(len(FILES)):
            FILES[i] = os.path.abspath(str(FILES[i]))
            DIRS.append(os.path.dirname(FILES[i]))

        FILES.sort()
        DIRS = list(set(DIRS))
        DIRS.sort()

    # process HEADERS
    HEADERS = TargetGetList(env, ['h'])

    # process CPPPATH
    if len(CPPPATH):
        # use absolute path
        for i in range(len(CPPPATH)):
            CPPPATH[i] = os.path.abspath(CPPPATH[i])

        # remove repeat path
        paths = []
        for p in CPPPATH:
            if p not in paths:
                paths.append(p)

        CPPPATH = []
        for path in paths:
            if PrefixPath(RTT_ROOT, path):
                CPPPATH += [os.path.abspath(path).replace('\\', '/')]

            elif PrefixPath(BSP_ROOT, path):
                CPPPATH += [os.path.abspath(path).replace('\\', '/')]

            else:
                CPPPATH += ['"%s",' % path.replace('\\', '/')]

    # process CPPDEFINES
    if len(CPPDEFINES):
        CPPDEFINES = [i for i in set(CPPDEFINES)]

        CPPDEFINES.sort()

    proj = {}
    proj['FILES']       = FILES
    proj['DIRS']        = DIRS
    proj['HEADERS']     = HEADERS
    proj['CPPPATH']     = CPPPATH
    proj['CPPDEFINES']  = CPPDEFINES

    return proj

def VersionCmp(ver1, ver2):
    la=[]
    if ver1:
        la = re.split("[. ]", ver1)
    lb = re.split("[. ]", ver2)

    f = 0
    if len(la) > len(lb):
        f = len(la)
    else:
        f = len(lb)
    for i in range(f):
        try:
            if int(la[i]) > int(lb[i]):
                return 1
            elif int(la[i]) == int(lb[i]):
                continue
            else:
                return -1
        except (IndexError, ValueError) as e:
            if len(la) > len(lb):
                return 1
            else:
                return -1
    return 0

def GCCC99Patch(cflags):
    import building
    gcc_version = building.GetDepend('GCC_VERSION_STR')
    if gcc_version:
        gcc_version = gcc_version.replace('"', '')
    if VersionCmp(gcc_version, "4.8.0") == 1:
        # remove -std=c99 after GCC 4.8.x
        cflags = cflags.replace('-std=c99', '')

    return cflags

def ReloadModule(module):
    import sys
    if sys.version_info.major >= 3:
        import importlib
        importlib.reload(module)
    else:
        reload(module)

def ImportModule(module):
    import sys
    if sys.version_info.major >= 3:
        import importlib.util
        path = os.path.dirname(__file__)
        spec = importlib.util.spec_from_file_location(module, os.path.join(path, module+".py"))
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        return module
    else:
        return __import__(module, fromlist=[module])

def VerTuple(version_str):
    ver_parts = version_str.split('.')
    ver = tuple(int(part) for part in ver_parts)

    return ver

def CmdExists(cmd):
    # Check if the path directly points to an existing file.
    if os.path.isfile(cmd):
        return True
    else:
        # On Windows systems, check for common script file extensions
        # if the file does not exist as specified.
        if sys.platform.startswith('win'):
            # Loop through possible extensions to cover cases where the extension is omitted in the input.
            for ext in ['.exe', '.bat', '.ps1']:
                # Append the extension to the command path and check if this file exists.
                if os.path.isfile(cmd + ext):
                    return True

    # If none of the checks confirm the file exists, return False.
    return False
