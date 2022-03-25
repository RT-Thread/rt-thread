# for module compiling
import os
Import('RTT_ROOT')
Import('rtconfig')
from building import *

cwd = GetCurrentDir()
src = []
CPPPATH = []
list = os.listdir(cwd)

if rtconfig.PLATFORM == 'iar':
    print("\nThe current project does not support iar build\n")
    Return('group')
elif rtconfig.PLATFORM == 'gcc':
    CPPPATH = [cwd]
    src = Glob('./src/*.c')
elif rtconfig.PLATFORM == 'armclang':
    if GetOption('target') != 'mdk5':
        CPPPATH = [cwd]
        src = Glob('./src/*.c')

group = DefineGroup('Applications', src, depend = [''], CPPPATH = CPPPATH)

for d in list:
    path = os.path.join(cwd, d)
    if os.path.isfile(os.path.join(path, 'SConscript')):
        group = group + SConscript(os.path.join(d, 'SConscript'))

Return('group')
