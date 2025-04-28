import rtconfig
from building import *
import os

cwd  = GetCurrentDir()
path = [cwd]
src  = Glob('*.c')

group = DefineGroup('Applications', src, depend = [''], CPPPATH = path)

list = os.listdir(cwd)
for item in list:
    if os.path.isfile(os.path.join(cwd, item, 'SConscript')):
        group = group + SConscript(os.path.join(item, 'SConscript'))

Return('group')
