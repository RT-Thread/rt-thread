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
#

import sys
import os

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
        if group.has_key('src') and group['src']:
            FILES += group['src']

        # get each include path
        if group.has_key('CPPPATH') and group['CPPPATH']:
            CPPPATH += group['CPPPATH']

    if env.has_key('CPPDEFINES'):
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
        paths = [i for i in set(CPPPATH)]
        CPPPATH = []
        for path in paths:
            if PrefixPath(RTT_ROOT, path):
                CPPPATH += [os.path.abspath(path).replace('\\', '/')]

            elif PrefixPath(BSP_ROOT, path):
                CPPPATH += [os.path.abspath(path).replace('\\', '/')]

            else:
                CPPPATH += ['"%s",' % path.replace('\\', '/')]

        CPPPATH.sort()

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
