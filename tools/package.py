#
# File      : package.py
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
# 2015-04-10     Bernard      First version
#

# this script is used to build group with package.json instead of SConscript
import os
import json

from building import *

def ExtendPackageVar(package, var):
    v = []
    if var not in package:
        return v

    for item in package[var]:
        v = v + [item]

    return v

def BuildPackage(package = None):
    if package is None:
        package = os.path.join(GetCurrentDir(), 'package.json')
    elif os.path.isdir(package):
        # support directory path
        package = os.path.join(package, 'package.json')

    # get package.json path
    cwd = os.path.dirname(os.path.abspath(package))

    if not os.path.isfile(package):
        # silent return for conditional usage
        return []

    with open(package, 'r') as f:
        package_json = f.read()
        package = json.loads(package_json)

        # check package name
        if 'name' not in package or 'type' not in package or package['type'] != 'rt-thread-component':
            return []

        # get depends
        depend = []
        if 'dependencies' in package:
            depend = ExtendPackageVar(package, 'dependencies')

        # check dependencies
        if depend:
            group_enable = False
            for item in depend:
                if GetDepend(item):
                    group_enable = True
                    break
            if not group_enable:
                return []

        CPPDEFINES = []
        if 'defines' in package:
            CPPDEFINES = ExtendPackageVar(package, 'defines')

        src = []
        CPPPATH = []
        if 'sources' in package:
            src_depend = []
            src_CPPPATH = []
            for item in package['sources']:
                if 'includes' in item:
                    includes = item['includes']
                    for include in includes:
                        if include.startswith('/') and os.path.isdir(include):
                            src_CPPPATH = src_CPPPATH + [include]
                        else:
                            path = os.path.abspath(os.path.join(cwd, include))
                            src_CPPPATH = src_CPPPATH + [path]

                if 'dependencies' in item:
                    src_depend = src_depend + ExtendPackageVar(item, 'dependencies')

                src_enable = False
                if src_depend == []:
                    src_enable = True
                else:
                    for d in src_depend:
                        if GetDepend(d):
                            src_enable = True
                            break

                if src_enable:
                    files = []
                    src_files = []
                    if 'files' in item:
                        files += ExtendPackageVar(item, 'files')

                    for item in files:
                        # handle glob patterns relative to package.json directory
                        old_dir = os.getcwd()
                        os.chdir(cwd)
                        try:
                            src_files += Glob(item)
                        finally:
                            os.chdir(old_dir)

                    src += src_files

            CPPPATH += src_CPPPATH

    objs = DefineGroup(package['name'], src, depend = depend, CPPPATH = CPPPATH, CPPDEFINES = CPPDEFINES)

    return objs
