#! /usr/bin/env python
#coding=utf-8

"""
wizard.py - a script to generate SConscript in RT-Thread RTOS. 

`wizard --component name' to generate SConscript for name component.
`wizard --bridge' to generate SConscript as a bridge to connect each 
SConscript script file of sub-directory. 
"""

import sys

SConscript_com = '''# RT-Thread building script for component

from building import *

cwd = GetCurrentDir()
src = Glob('*.c')
CPPPATH = [cwd]

group = DefineGroup('COMPONENT_NAME', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
'''

SConscript_bridge = '''# RT-Thread building script for bridge

import os
from building import *

cwd = GetCurrentDir()
objs = []
list = os.listdir(cwd)

for d in list:
    path = os.path.join(cwd, d)
    if os.path.isfile(os.path.join(path, 'SConscript')):
        objs = objs + SConscript(os.path.join(d, 'SConscript'))

Return('objs')
'''

def usage():
    print 'wizard --component name'
    print 'wizard --bridge'

def gen_component(name):
    print 'generate SConscript for ' + name
    text = SConscript_com.replace('COMPONENT_NAME', name)
    f = file('SConscript', 'w')
    f.write(text)
    f.close()

def gen_bridge():
    print 'generate SConscript for bridge'
    f = file('SConscript', 'w')
    f.write(SConscript_bridge)
    f.close()

if __name__ == '__main__':
    if len(sys.argv) == 1:
        usage()
        sys.exit(2)
    
    if sys.argv[1] == '--component':
        gen_component(sys.argv[2])
    elif sys.argv[1] == '--bridge':
        gen_bridge()
    else:
        usage()
