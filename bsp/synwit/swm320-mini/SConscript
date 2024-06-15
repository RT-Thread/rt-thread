import os
from building import *

cwd  = GetCurrentDir()
objs = []

for name in os.listdir(cwd):
    if os.path.isfile(os.path.join(cwd, name, 'SConscript')):
        objs += SConscript(os.path.join(name, 'SConscript'))

Return('objs')
