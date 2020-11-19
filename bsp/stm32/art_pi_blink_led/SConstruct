import os
import sys
import rtconfig

if os.path.exists('rt-thread'):
    RTT_ROOT = os.path.normpath(os.getcwd() + '/rt-thread')
else:
    RTT_ROOT = os.path.normpath(os.getcwd() + '../../../rt-thread')

sys.path = sys.path + [os.path.join(RTT_ROOT, 'tools')]
try:
    from building import *
except Exception as e:
    print("Error message:", e.message)
    print('Cannot found RT-Thread root directory, please check RTT_ROOT')
    print(RTT_ROOT)
    sys.exit(-1)

TARGET = 'rt-thread.elf'

DefaultEnvironment(tools=[])
env = Environment(tools = ['mingw'],
    AS = rtconfig.AS, ASFLAGS = rtconfig.AFLAGS,
    CC = rtconfig.CC, CCFLAGS = rtconfig.CFLAGS,
    AR = rtconfig.AR, ARFLAGS = '-rc',
    CXX = rtconfig.CXX, CXXFLAGS = rtconfig.CXXFLAGS,
    LINK = rtconfig.LINK, LINKFLAGS = rtconfig.LFLAGS)
env.PrependENVPath('PATH', rtconfig.EXEC_PATH)

env.AppendUnique(CPPDEFINES = [])

Export('RTT_ROOT')
Export('rtconfig')

if os.path.exists('libraries'):
    libraries_path_prefix = 'libraries'
else:
    libraries_path_prefix = '../../libraries'

SDK_LIB = libraries_path_prefix
Export('SDK_LIB')

# prepare building environment
objs = PrepareBuilding(env, RTT_ROOT, has_libcpu=False)

stm32_library = 'STM32H7xx_HAL'
rtconfig.BSP_LIBRARY_TYPE = stm32_library

if not os.path.exists('libraries'):
    # include libraries
    objs.extend(SConscript(os.path.join(libraries_path_prefix, 'SConscript')))

    # include applications
    #objs.extend(SConscript(os.path.join(APP_ROOT, 'applications', 'SConscript')))

#objs += PrepareBuilding(env, LIB_ROOT, has_libcpu=False)
# make a building
DoBuilding(TARGET, objs)
