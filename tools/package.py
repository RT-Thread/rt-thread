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
from building import *

def ExtendPackageVar(package, var):
    v = []
    if var not in package:
        return v

    for item in package[var]:
        v = v + [item]

    return v

def BuildPackage(package):
    import json
    f = open(package)
    package_json = f.read()

    # get package.json path
    cwd = os.path.dirname(package)

    package = json.loads(package_json)

    # check package name 
    if 'name' not in package:
        return []

    # get depends
    depend = ExtendPackageVar(package, 'depends')

    src = []
    if 'source_files' in package:
        for src_file in package['source_files']:
            src_file = os.path.join(cwd, src_file)
            src += Glob(src_file)

    CPPPATH = []
    if 'CPPPATH' in package:
        for path in package['CPPPATH']:
            if path.startswith('/') and os.path.isdir(path):
                CPPPATH = CPPPATH + [path]
            else:
                CPPPATH = CPPPATH + [os.path.join(cwd, path)]

    CPPDEFINES = ExtendPackageVar(package, 'CPPDEFINES')

    objs = DefineGroup(package['name'], src, depend = depend, CPPPATH = CPPPATH, CPPDEFINES = CPPDEFINES)

    return objs
