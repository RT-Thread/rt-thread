#
# File      : win32spawn.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2025, RT-Thread Development Team
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
import subprocess
import tempfile

# CreateProcess rejects a command line longer than 32767 characters.
_WIN32_CMDLINE_LIMIT = 32000

def _response_file_arg(arg):
    # GCC's @file reader (buildargv) treats '\' as an escape character,
    # unlike the Windows command line, so backslashes must be doubled.
    arg = arg.replace('\\', '\\\\')
    # Arguments SCons already quoted keep their own grouping.
    if '"' not in arg and (' ' in arg or '\t' in arg):
        arg = '"' + arg + '"'
    return arg

def _write_response_file(args):
    fd, path = tempfile.mkstemp(prefix='rtthread-', suffix='.rsp')
    with os.fdopen(fd, 'w') as f:
        # A space separator matches the original command line: whitespace
        # inside quotes stays part of the argument, as it does on Windows.
        f.write(' '.join(_response_file_arg(arg) for arg in args))
    return path

class Win32Spawn:
    def __init__(self, gnu_response_file=False):
        self.gnu_response_file = gnu_response_file

    def spawn(self, sh, escape, cmd, args, env):
        # deal with the cmd build-in commands which cannot be used in
        # subprocess.Popen
        if cmd == 'del':
            for f in args[1:]:
                try:
                    os.remove(f)
                except Exception as e:
                    print('Error removing file: ' + e)
                    return -1
            return 0

        newargs = ' '.join(args[1:])
        cmdline = cmd + " " + newargs

        rsp = None
        if self.gnu_response_file and len(cmdline) > _WIN32_CMDLINE_LIMIT:
            rsp = _write_response_file(args[1:])
            cmdline = cmd + ' @"' + rsp + '"'

        # Make sure the env is constructed by strings
        _e = dict([(k, str(v)) for k, v in env.items()])

        # Windows(tm) CreateProcess does not use the env passed to it to find
        # the executables. So we have to modify our own PATH to make Popen
        # work.
        old_path = os.environ['PATH']
        os.environ['PATH'] = _e['PATH']

        try:
            try:
                proc = subprocess.Popen(cmdline, env=_e, shell=False)
            except Exception as e:
                print('Error in calling command:' + cmdline.split(' ')[0])
                print('Exception: ' + str(e))
                if e.errno == 2 and getattr(e, 'winerror', None) != 206:
                    print ("\nPlease check Toolchains PATH setting.\n")

                return e.errno
            return proc.wait()
        finally:
            os.environ['PATH'] = old_path
            if rsp is not None:
                try:
                    os.remove(rsp)
                except OSError:
                    pass
