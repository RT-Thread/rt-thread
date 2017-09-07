# for module compiling
import os
Import('RTT_ROOT')
from building import *

cwd = str(Dir('#'))
src = Glob('*.c')
objs = []
list = os.listdir(cwd)

for d in list:
    path = os.path.join(cwd, d)
    if os.path.isfile(os.path.join(path, 'SConscript')):
        objs = objs + SConscript(os.path.join(d, 'SConscript'))

group = DefineGroup('', src, depend = [''], CPPPATH = [])
#objs += group
Return('objs')
