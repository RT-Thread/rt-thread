"""
Utils for CMake
Author: https://github.com/klivelinux
"""

import os
import re
import utils
import rtconfig


def GenerateCFiles(env,project):
    """
    Generate CMakeLists.txt files
    """

    info = utils.ProjectInfo(env)
    
    CC = os.path.join(rtconfig.EXEC_PATH, rtconfig.CC)
    CXX = os.path.join(rtconfig.EXEC_PATH, rtconfig.CXX)
    AS = os.path.join(rtconfig.EXEC_PATH, rtconfig.AS)
    AR = os.path.join(rtconfig.EXEC_PATH, rtconfig.AR)
    LINK = os.path.join(rtconfig.EXEC_PATH, rtconfig.LINK)
    SIZE = os.path.join(rtconfig.EXEC_PATH, rtconfig.SIZE)
    OBJDUMP = os.path.join(rtconfig.EXEC_PATH, rtconfig.OBJDUMP)
    OBJCOPY = os.path.join(rtconfig.EXEC_PATH, rtconfig.OBJCPY)

    cm_file = open('CMakeLists.txt', 'w')
    if cm_file:
        cm_file.write("CMAKE_MINIMUM_REQUIRED(VERSION 3.10)\n\n")

        cm_file.write("SET(CMAKE_SYSTEM_NAME Generic)\n")
        cm_file.write("#SET(CMAKE_VERBOSE_MAKEFILE ON)\n\n")

        cm_file.write("SET(CMAKE_C_COMPILER \""+ CC + "\")\n")
        cm_file.write("SET(CMAKE_CXX_COMPILER \""+ CXX + "\")\n")
        cm_file.write("SET(CMAKE_ASM_COMPILER \""+ AS + "\")\n")
        cm_file.write("SET(CMAKE_OBJCOPY \""+ OBJCOPY + "\")\n")
        cm_file.write("SET(CMAKE_SIZE \""+ SIZE + "\")\n\n")


        cm_file.write("SET(CMAKE_C_FLAGS \""+ rtconfig.CFLAGS + "\")\n")
        cm_file.write("SET(CMAKE_CXX_FLAGS \""+ rtconfig.CXXFLAGS + "\")\n")
        cm_file.write("SET(CMAKE_ASM_FLAGS \""+ rtconfig.AFLAGS + "\")\n")
        cm_file.write("SET(CMAKE_EXE_LINKER_FLAGS \""+ re.sub('-T(\s*)', '-T ${CMAKE_SOURCE_DIR}/',rtconfig.LFLAGS) + "\")\n\n")
        
        cm_file.write("SET(CMAKE_CXX_STANDARD 14)\n")
        cm_file.write("PROJECT(rtthread C CXX ASM)\n")
                
        cm_file.write("INCLUDE_DIRECTORIES(\n")
        for i in info['CPPPATH']:
                cm_file.write( "\t" +i + "\n")
        cm_file.write(")\n\n")


        cm_file.write("ADD_DEFINITIONS(\n")
        for i in info['CPPDEFINES']:
                cm_file.write("\t-D" + i + "\n")
        cm_file.write(")\n\n")

        cm_file.write("SET(PROJECT_SOURCES\n")
        for group in project:
            for f in group['src']:
                cm_file.write( "\t"+os.path.normpath(f.rfile().abspath)+"\n" )
        cm_file.write(")\n\n")
        
        cm_file.write("LINK_DIRECTORIES(\n")
        for group in project:
            if 'LIBPATH' in group.keys():
                for f in group['LIBPATH']:
                    cm_file.write( "\t"+ f + "\n" )
        cm_file.write(")\n\n")

        cm_file.write("LINK_LIBRARIES(\n")
        for group in project:
            if 'LIBS' in group.keys():
                for f in group['LIBS']:
                    cm_file.write( "\t"+ "{}\n".format(f))
        cm_file.write(")\n\n")

        cm_file.write("ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${PROJECT_SOURCES})\n")
        cm_file.write("ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD \nCOMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf)")

        cm_file.close()

    return

def CMakeProject(env,project):
    print('Update setting files for CMakeLists.txt...')
    GenerateCFiles(env,project)
    print('Done!')

    return
