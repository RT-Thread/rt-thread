import rtconfig
from building import *

cwd     = GetCurrentDir()
CPPPATH = [cwd, str(Dir('#'))]
src     = Split("""
main.c
""")

if GetDepend(['RT_USING_DFS']):
    src += ['mnt.c']

group = DefineGroup('Applications', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
