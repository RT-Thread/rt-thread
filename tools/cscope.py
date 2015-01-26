#
# File      : cscope.py
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

def _get_src(project):
    li = []
    for group in project:
        for f in group['src']:
            li.append(os.path.normpath(f.rfile().abspath))
    return li

def _get_header_dir(dirp):
    li = []
    for root, dirs, files in os.walk(dirp):
        for d in dirs:
            fpath = os.path.join(root, d)
            li.extend(_get_header_dir(fpath))

        for f in files:
            if f[-2:] == '.h':
                fpath = os.path.join(root, f)
                li.append(os.path.normpath(fpath))
    return li

def _get_header(project):
    li = []
    for g in project:
        for d in g.get('CPPPATH', []):
            li.extend(_get_header_dir(d))
    return li

def CscopeDatabase(project):
    files = set(_get_src(project) + _get_header(project))
    with open('cscope.files', 'w') as db:
        db.write('-k\n-q\n')
        db.write('\n'.join(files))
        db.flush() # let cscope see the full content
        os.system('cscope -b')

