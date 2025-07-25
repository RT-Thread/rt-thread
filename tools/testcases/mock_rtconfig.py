# -*- coding: utf-8 -*-
#
# Mock rtconfig module for testing purposes
#

# Mock configuration variables
CROSS_TOOL = 'gcc'
PLATFORM = 'gcc'
CC = 'gcc'
CXX = 'g++'
AS = 'as'
AR = 'ar'
LINK = 'gcc'
EXEC_PATH = '/usr/bin'

# Mock functions
def GetDepend(depend):
    return True

# Mock environment
class MockEnv:
    def __init__(self):
        self.CPPPATH = []
        self.CPPDEFINES = []
        self.LIBS = []
        self.LIBPATH = []
        self.CFLAGS = []
        self.CXXFLAGS = []
        self.LINKFLAGS = []
        self.ASFLAGS = []

# Global variables
Env = MockEnv()
Rtt_Root = '/mock/rt-thread'
Projects = [] 