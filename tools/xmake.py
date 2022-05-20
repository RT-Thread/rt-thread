"""
Utils for CMake
Author: https://github.com/klivelinux
"""

import os
import utils
from string import Template
import rtconfig

from utils import _make_path_relative


class XmakeProject:
    def __init__(self, env, project):
        self.env = env
        self.project = project
        self.sdkdir = ""
        self.toolchain = ""
        self.src_path = ""
        self.inc_path = ""
        self.cflags = ""
        self.cxxflags = ""
        self.ldflags = ""
        self.asflags = ""
        self.define = ""

    def set_toolchain_path(self):
        self.sdkdir = os.path.abspath(rtconfig.EXEC_PATH).replace('\\', "/")
        # delete -
        self.toolchain = rtconfig.PREFIX[:-1]

    def set_target_config(self):
        info = utils.ProjectInfo(self.env)
        # 1. config src path
        for group in self.project:
            for f in group['src']:
                # use relative path
                path = _make_path_relative(os.getcwd(), os.path.normpath(f.rfile().abspath))
                self.src_path += "\t\"{0}\",\n".format(path.replace("\\", "/"))
        self.src_path = self.src_path[:-2]
        # 2. config dir path
        for i in info['CPPPATH']:
            # use relative path
            path = _make_path_relative(os.getcwd(), i)
            self.inc_path += "\t\"{0}\",\n".format(path.replace("\\", "/"))
        self.inc_path = self.inc_path[:-2]
        # 3. config cflags
        self.cflags = rtconfig.CFLAGS.replace('\\', "/").replace('\"', "\\\"")
        # 4. config cxxflags
        if 'CXXFLAGS' in dir(rtconfig):
            self.cxxflags = rtconfig.CXXFLAGS.replace('\\', "/").replace('\"', "\\\"")
        else:
            self.cxxflags = self.cflags
        # 5. config asflags
        self.asflags = rtconfig.AFLAGS.replace('\\', "/").replace('\"', "\\\"")
        # 6. config lflags
        self.ldflags = rtconfig.LFLAGS.replace('\\', "/").replace('\"', "\\\"")
        # 7. config define
        for i in info['CPPDEFINES']:
            self.define += "\t\"{0}\",\n".format(i)
        self.define = self.define[:-2]

    def generate_xmake_file(self):
        if os.getenv('RTT_ROOT'):
            RTT_ROOT = os.getenv('RTT_ROOT')
        else:
            RTT_ROOT = os.path.normpath(os.getcwd() + '/../../..')

        template_path = os.path.join(RTT_ROOT, "tools", "xmake.lua")
        with open(template_path, "r") as f:
            data = f.read()
        data = Template(data)
        data = data.safe_substitute(toolchain=self.toolchain, sdkdir=self.sdkdir, src_path=self.src_path, inc_path=self.inc_path, 
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