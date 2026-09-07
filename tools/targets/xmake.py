"""
Utils for CMake
Author: https://github.com/klivelinux
"""

import os
import sys
import utils
from string import Template
import rtconfig

from utils import _make_path_relative

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import target_utils


class XmakeProject:
    def __init__(self, env, project):
        self.env = env
        self.project = project
        self.sdkdir = ""
        self.bindir = ""
        self.toolchain = ""
        self.src_path = ""
        self.inc_path = ""
        self.cflags = ""
        self.cxxflags = ""
        self.ldflags = ""
        self.asflags = ""
        self.define = ""

    def set_toolchain_path(self):
        self.bindir = os.path.abspath(rtconfig.EXEC_PATH).replace('\\', "/")
        self.sdkdir = self.bindir[:-4]
        # delete -
        self.toolchain = rtconfig.PREFIX[:-1]

    def set_target_config(self):
        info = utils.ProjectInfo(self.env)
        # 1. config src path -- relative, de-duplicated, Lua-quoted list
        src_files = []
        for group in self.project:
            for f in group['src']:
                path = _make_path_relative(os.getcwd(), os.path.normpath(f.rfile().abspath))
                src_files.append(path.replace("\\", "/"))
        self.src_path = target_utils.lua_list(target_utils.ordered_unique(src_files))
        # 2. config dir path
        inc_dirs = [_make_path_relative(os.getcwd(), i).replace("\\", "/") for i in info['CPPPATH']]
        self.inc_path = target_utils.lua_list(target_utils.ordered_unique(inc_dirs))
        # 3. config cflags
        self.cflags = target_utils.escape_quoted_flags(rtconfig.CFLAGS)
        # 4. config cxxflags
        if 'CXXFLAGS' in dir(rtconfig):
            self.cxxflags = target_utils.escape_quoted_flags(rtconfig.CXXFLAGS)
        else:
            self.cxxflags = self.cflags
        # 5. config asflags
        self.asflags = target_utils.escape_quoted_flags(rtconfig.AFLAGS)
        # 6. config lflags
        self.ldflags = target_utils.escape_quoted_flags(rtconfig.LFLAGS)
        # 7. config define -- tuple macros fold to FOO=1 (never FOO, 1)
        self.define = target_utils.lua_list(target_utils.normalize_defines(info['CPPDEFINES']))

    def generate_xmake_file(self):
        if os.getenv('RTT_ROOT'):
            RTT_ROOT = os.getenv('RTT_ROOT')
        else:
            RTT_ROOT = os.path.normpath(os.getcwd() + '/../../..')

        template_path = os.path.join(RTT_ROOT, "tools", "targets", "xmake.lua")
        with open(template_path, "r") as f:
            data = f.read()
        data = Template(data)
        data = data.safe_substitute(toolchain=self.toolchain, sdkdir=self.sdkdir, bindir=self.bindir, src_path=self.src_path, inc_path=self.inc_path,
                                    define=self.define, cflags=self.cflags, cxxflags=self.cxxflags, asflags=self.asflags,
                                    ldflags=self.ldflags, target="rt-thread")
        with open("xmake.lua", "w") as f:
            f.write(data)


def XMakeProject(env,project):
    print('Update setting files for xmake.lua...')

    xmake_project = XmakeProject(env, project)
    xmake_project.set_toolchain_path()
    xmake_project.set_target_config()
    xmake_project.generate_xmake_file()

    print('Done!')

    return
