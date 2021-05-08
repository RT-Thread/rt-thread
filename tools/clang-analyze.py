"""
Tool-specific initialization for Clang static analyzer

There normally shouldn't be any need to import this module directly.
It will usually be imported through the generic SCons.Tool.Tool()
selection method.
"""

__revision__ = "tools/clang-analyze.py 2013-09-06 grissiom"

import os
import os.path

import SCons.Action
import SCons.Builder
import SCons.Defaults
import SCons.Tool
import SCons.Util

import rtconfig

def generate(env):
    assert(rtconfig.CROSS_TOOL == 'clang-analyze')
    # let gnu_tools setup a basic env(learnt from SCons/Tools/mingw.py)
    gnu_tools = ['gcc', 'g++', 'gnulink', 'ar', 'gas', 'm4']
    for tool in gnu_tools:
        SCons.Tool.Tool(tool)(env)

    # then we could stand on the shoulders of gaints
    env['CC']   = 'ccc-analyzer'
    env['CXX']  = 'c++-analyzer'
    env['AS']   = 'true'
    env['AR']   = 'true'
    env['LINK'] = 'true'

    env['CFLAGS']    = ['-fsyntax-only', '-Wall', '-Wno-invalid-source-encoding', '-m32']
    env['LINKFLAGS'] = '-Wl,--gc-sections'
    env['ARFLAGS']   = '-rc'

    # only check, don't compile. ccc-analyzer use CCC_CC as the CC.
    # fsyntax-only will give us some additional warning messages
    env['ENV']['CCC_CC'] = 'clang'
    env['ENV']['CCC_CXX'] = 'clang++'

    # setup the output dir and format
    env['ENV']['CCC_ANALYZER_HTML'] = './build/'
    env['ENV']['CCC_ANALYZER_OUTPUT_FORMAT'] = 'html'

    # Some setting from the platform also have to be overridden:
    env['OBJSUFFIX'] = '.o'
    env['LIBPREFIX'] = 'lib'
    env['LIBSUFFIX'] = '.a'

    if rtconfig.EXEC_PATH:
        if not os.path.exists(rtconfig.EXEC_PATH):
            print()
            print('warning: rtconfig.EXEC_PATH(%s) does not exists.' % rtconfig.EXEC_PATH)
            print()
            return
        env.AppendENVPath('PATH', rtconfig.EXEC_PATH)

def exists(env):
    return env.Detect(['ccc-analyzer', 'c++-analyzer'])

# Local Variables:
# tab-width:4
# indent-tabs-mode:nil
# End:
# vim: set expandtab tabstop=4 shiftwidth=4:
