import os
import sys
import rtconfig

from rtconfig import RTT_ROOT

sys.path = sys.path + [os.path.join(RTT_ROOT, 'tools')]
from building import *

TARGET = 'rtthread.' + rtconfig.TARGET_EXT

DefaultEnvironment(tools=[])
env = Environment(tools = ['mingw'],
	AS = rtconfig.AS, ASFLAGS = rtconfig.AFLAGS,
	CC = rtconfig.CC, CCFLAGS = rtconfig.CFLAGS,
	CXX = rtconfig.CXX, CXXFLAGS = rtconfig.CXXFLAGS,
	AR = rtconfig.AR, ARFLAGS = '-rc',
	LINK = rtconfig.LINK, LINKFLAGS = rtconfig.LFLAGS)
env.PrependENVPath('PATH', rtconfig.EXEC_PATH)
env['ASCOM'] = env['ASPPCOM']

Export('RTT_ROOT')
Export('rtconfig')


# prepare building environment
objs = PrepareBuilding(env, RTT_ROOT)

rtconfig.LFLAGS += " -Ttext 0xffffffff80200000"
env.Replace(LINKFLAGS = rtconfig.LFLAGS)

if GetDepend('RT_USING_FPU'):
    env['CCFLAGS']   = env['CCFLAGS'].replace('-msoft-float', '-mhard-float')
    env['ASFLAGS']   = env['ASFLAGS'].replace('-msoft-float', '-mhard-float')
    env['CXXFLAGS']  = env['CXXFLAGS'].replace('-msoft-float', '-mhard-float')
    env['LINKFLAGS'] = env['LINKFLAGS'].replace('-msoft-float', '-mhard-float')

# make a building
DoBuilding(TARGET, objs)
