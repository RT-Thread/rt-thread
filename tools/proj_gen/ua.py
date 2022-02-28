#
# File      : ua.py
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
from utils import _make_path_relative

def PrefixPath(prefix, path):
    path = os.path.abspath(path)
    prefix = os.path.abspath(prefix)

    if sys.platform == 'win32':
        prefix = prefix.lower()
        path = path.lower()

    if path.startswith(prefix):
        return True
    
    return False

def PrepareUA(project, RTT_ROOT, BSP_ROOT):
    with open('rtua.py', 'w') as ua:
        # ua.write('import os\n')
        # ua.write('import sys\n')
        ua.write('\n')
        
        print(RTT_ROOT)
        
        CPPPATH = []
        CPPDEFINES = []

        for group in project:
            # get each include path
            if 'CPPPATH' in group and group['CPPPATH']:
                CPPPATH += group['CPPPATH']

            # get each group's definitions
            if 'CPPDEFINES' in group and group['CPPDEFINES']:
                CPPDEFINES += group['CPPDEFINES']

        if len(CPPPATH):
            # use absolute path 
            for i in range(len(CPPPATH)):
                CPPPATH[i] = os.path.abspath(CPPPATH[i])

            # remove repeat path
            paths = [i for i in set(CPPPATH)]
            CPPPATH = []
            for path in paths:
                if PrefixPath(RTT_ROOT, path):
                    CPPPATH += ['RTT_ROOT + "/%s",' % _make_path_relative(RTT_ROOT, path).replace('\\', '/')]
                
                elif PrefixPath(BSP_ROOT, path):
                    CPPPATH += ['BSP_ROOT + "/%s",' % _make_path_relative(BSP_ROOT, path).replace('\\', '/')]
                else:
                    CPPPATH += ['"%s",' % path.replace('\\', '/')]

            CPPPATH.sort()
            ua.write('def GetCPPPATH(BSP_ROOT, RTT_ROOT):\n')
            ua.write('\tCPPPATH=[\n')
            for path in CPPPATH:
                ua.write('\t\t%s\n' % path)
            ua.write('\t]\n\n')
            ua.write('\treturn CPPPATH\n\n')
        else:
            ua.write('def GetCPPPATH(BSP_ROOT, RTT_ROOT):\n')
            ua.write('\tCPPPATH=[]\n\n')
            ua.write('\treturn CPPPATH\n\n')

        if len(CPPDEFINES):
            CPPDEFINES = [i for i in set(CPPDEFINES)]

            ua.write('def GetCPPDEFINES():\n')
            ua.write('\tCPPDEFINES=%s\n' % str(CPPDEFINES))
            ua.write('\treturn CPPDEFINES\n\n')

        else:
            ua.write('def GetCPPDEFINES():\n')
            ua.write('\tCPPDEFINES=""\n\n')
            ua.write('\treturn CPPDEFINES\n\n')
