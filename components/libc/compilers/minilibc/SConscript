from building import *
Import('rtconfig')

src = Glob('*.c') + Glob('*.cpp')
cwd = GetCurrentDir()
group = []

CPPPATH = [cwd]
CPPDEFINES = ['RT_USING_MINILIBC']

if rtconfig.PLATFORM == 'gcc' and rtconfig.ARCH != 'sim' and not GetDepend('RT_USING_LIBC'):
    group = DefineGroup('libc', src, depend = [''],
        CPPPATH = CPPPATH, CPPDEFINES = CPPDEFINES)

Return('group')
