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

class Win32Spawn:
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

        # Make sure the env is constructed by strings
        _e = dict([(k, str(v)) for k, v in env.items()])

        # Windows(tm) CreateProcess does not use the env passed to it to find
        # the executables. So we have to modify our own PATH to make Popen
        # work.
        old_path = os.environ['PATH']
        os.environ['PATH'] = _e['PATH']

        try:
            # On Windows, CreateProcess has a ~32K command line limit.
            # When the link command gets very long (many object files),
            # use a GCC @response file to shorten the command line.
            if len(cmdline) > 25000 and (cmd.find('gcc') != -1 or cmd.find('g++') != -1):
                # Split args: object files go into response file;
                # flags stay on command line. Libraries (-l*, -L*) must
                # come after object files for proper symbol resolution.
                pre_obj_flags = []
                post_obj_flags = []
                obj_args = []
                seen_obj = False
                for arg in args[1:]:
                    stripped = arg.strip('"')
                    if stripped.endswith('.o') or stripped.endswith('.a'):
                        obj_args.append(stripped)
                        seen_obj = True
                    elif not seen_obj:
                        pre_obj_flags.append(stripped)
                    else:
                        post_obj_flags.append(stripped)

                # Create response file for object files
                fd, rsp_path = tempfile.mkstemp(suffix='.rsp', prefix='scons_link_')
                with os.fdopen(fd, 'w') as f:
                    for obj in obj_args:
                        # GCC @file treats backslash as escape char;
                        # use forward slashes for Windows paths
                        f.write(obj.replace('\\', '/') + '\n')
                rsp_args = [cmd] + pre_obj_flags + ['@' + rsp_path] + post_obj_flags
                proc = subprocess.Popen(rsp_args, env=_e, shell=False)
            else:
                proc = subprocess.Popen(cmdline, env=_e, shell=False)
        except Exception as e:
            print('Error in calling command:' + cmdline.split(' ')[0])
            print('Exception: ' + os.strerror(e.errno))
            if (os.strerror(e.errno) == "No such file or directory"):
                print ("\nPlease check Toolchains PATH setting.\n")

            return e.errno
        finally:
            os.environ['PATH'] = old_path

        ret = proc.wait()

        # Clean up response file if used
        if len(cmdline) > 25000 and (cmd.find('gcc') != -1 or cmd.find('g++') != -1):
            try:
                os.unlink(rsp_path)
            except:
                pass

        return ret
