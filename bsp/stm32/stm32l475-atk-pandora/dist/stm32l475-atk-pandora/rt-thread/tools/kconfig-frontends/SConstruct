import os

env = Environment()
env['CPPPATH'] = ['libs/parser', 'libs']
env['CPPDEFINES'] = ['CURSES_LOC=\\"ncurses.h\\"', 'HAVE_CONFIG_H', 
    'ROOTMENU=\\"Configuration\\"', 
    'CONFIG_=\\"CONFIG_\\"', 
    'KBUILD_NO_NLS',
    'GPERF_LEN_TYPE=unsigned int']
env['LIBS'] = ['ncurses']

src = Split('''
libs/lxdialog/checklist.c
libs/lxdialog/inputbox.c
libs/lxdialog/menubox.c
libs/lxdialog/textbox.c
libs/lxdialog/util.c
libs/lxdialog/yesno.c

libs/parser/yconf.c

frontends/mconf/mconf.c
''')

env.Program('kconfig-mconf', src)
