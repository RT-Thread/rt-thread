# for module compiling
import os
Import('env')
from building import *

cwd = GetCurrentDir()
objs = []
list = os.listdir(cwd)

# STM32H743xx || STM32H750xx || STM32F753xx
# You can select chips from the list above
env.Append(CPPDEFINES = ['STM32H750xx'])

for d in list:
    path = os.path.join(cwd, d)
    if os.path.isfile(os.path.join(path, 'SConscript')):
        objs = objs + SConscript(os.path.join(d, 'SConscript'))

Return('objs')
