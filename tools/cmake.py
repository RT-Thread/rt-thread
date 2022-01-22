"""
Utils for CMake
Author: https://github.com/klivelinux
"""

import os
import sys
import re
import utils
import rtconfig


def GenerateCFiles(env,project):
    """
    Generate CMakeLists.txt files
    """
    info = utils.ProjectInfo(env)

    CC = os.path.join(rtconfig.EXEC_PATH, rtconfig.CC).replace('\\', "/")
    if 'CXX' in dir(rtconfig):
        CXX = os.path.join(rtconfig.EXEC_PATH, rtconfig.CXX).replace('\\', "/")
    else:
        CXX = ''
    AS = os.path.join(rtconfig.EXEC_PATH, rtconfig.AS).replace('\\', "/")
    AR = os.path.join(rtconfig.EXEC_PATH, rtconfig.AR).replace('\\', "/")
    LINK = os.path.join(rtconfig.EXEC_PATH, rtconfig.LINK).replace('\\', "/")
    if rtconfig.PLATFORM == 'gcc':
        SIZE = os.path.join(rtconfig.EXEC_PATH, rtconfig.SIZE).replace('\\', "/")
        OBJDUMP = os.path.join(rtconfig.EXEC_PATH, rtconfig.OBJDUMP).replace('\\', "/")
        OBJCOPY = os.path.join(rtconfig.EXEC_PATH, rtconfig.OBJCPY).replace('\\', "/")
    elif rtconfig.CROSS_TOOL == 'keil':
        FROMELF = os.path.join(rtconfig.EXEC_PATH, 'fromelf').replace('\\', "/")

    CFLAGS = rtconfig.CFLAGS.replace('\\', "/").replace('\"', "\\\"")
    if 'CXXFLAGS' in dir(rtconfig):
        CXXFLAGS = rtconfig.CXXFLAGS.replace('\\', "/").replace('\"', "\\\"")
    else:
        CXXFLAGS = CFLAGS
    AFLAGS = rtconfig.AFLAGS.replace('\\', "/").replace('\"', "\\\"")
    LFLAGS = rtconfig.LFLAGS.replace('\\', "/").replace('\"', "\\\"")

    if "win32" in sys.platform:
        CC += ".exe"
        if CXX != '':
            CXX += ".exe"
        AS += ".exe"
        AR += ".exe"
        LINK += ".exe"
        if rtconfig.PLATFORM == 'gcc':
            SIZE += ".exe"
            OBJDUMP += ".exe"
            OBJCOPY += ".exe"
        elif rtconfig.CROSS_TOOL == 'keil':
            FROMELF += ".exe"

    if not os.path.exists(CC) or not os.path.exists(AS) or not os.path.exists(AR) or not os.path.exists(LINK):
        print("'Cannot found toolchain directory, please check RTT_CC and RTT_EXEC_PATH'")
        sys.exit(-1)

    cm_file = open('CMakeLists.txt', 'w')
    if cm_file:
        cm_file.write("CMAKE_MINIMUM_REQUIRED(VERSION 3.10)\n\n")

        cm_file.write("SET(CMAKE_SYSTEM_NAME Generic)\n")
        cm_file.write("SET(CMAKE_SYSTEM_PROCESSOR " + rtconfig.CPU +")\n")
        cm_file.write("#SET(CMAKE_VERBOSE_MAKEFILE ON)\n\n")

        cm_file.write("SET(CMAKE_C_COMPILER \""+ CC + "\")\n")
        cm_file.write("SET(CMAKE_ASM_COMPILER \""+ AS + "\")\n")
        cm_file.write("SET(CMAKE_C_FLAGS \""+ CFLAGS + "\")\n")
        cm_file.write("SET(CMAKE_ASM_FLAGS \""+ AFLAGS + "\")\n")
        cm_file.write("SET(CMAKE_C_COMPILER_WORKS TRUE)\n\n")

        if CXX != '':
            cm_file.write("SET(CMAKE_CXX_COMPILER \""+ CXX + "\")\n")
            cm_file.write("SET(CMAKE_CXX_FLAGS \""+ CXXFLAGS + "\")\n")
            cm_file.write("SET(CMAKE_CXX_COMPILER_WORKS TRUE)\n\n")

        if rtconfig.PLATFORM == 'gcc':
            cm_file.write("SET(CMAKE_OBJCOPY \""+ OBJCOPY + "\")\n")
            cm_file.write("SET(CMAKE_SIZE \""+ SIZE + "\")\n\n")
        elif rtconfig.CROSS_TOOL == 'keil':
            cm_file.write("SET(CMAKE_FROMELF \""+ FROMELF + "\")\n\n")

        LINKER_FLAGS = ''
        LINKER_LIBS = ''
        if rtconfig.PLATFORM == 'gcc':
            LINKER_FLAGS += '-T'
        elif rtconfig.CROSS_TOOL == 'keil':
            LINKER_FLAGS += '--scatter'
            for group in project:
                if 'LIBPATH' in group.keys():
                    for f in group['LIBPATH']:
                        LINKER_LIBS += ' --userlibpath ' + f.replace("\\", "/")
            for group in project:
                if 'LIBS' in group.keys():
                    for f in group['LIBS']:
                        LINKER_LIBS += ' ' + f.replace("\\", "/") + '.lib'
        cm_file.write("SET(CMAKE_EXE_LINKER_FLAGS \""+ re.sub(LINKER_FLAGS + '(\s*)', LINKER_FLAGS + ' ${CMAKE_SOURCE_DIR}/', LFLAGS) + LINKER_LIBS + "\")\n\n")

        if CXX != '':
            cm_file.write("SET(CMAKE_CXX_STANDARD 14)\n")
            cm_file.write("PROJECT(rtthread C CXX ASM)\n")
        else:
            cm_file.write("PROJECT(rtthread C ASM)\n")

        cm_file.write("INCLUDE_DIRECTORIES(\n")
        for i in info['CPPPATH']:
            cm_file.write( "\t" + i.replace("\\", "/") + "\n")
        cm_file.write(")\n\n")

        cm_file.write("ADD_DEFINITIONS(\n")
        for i in info['CPPDEFINES']:
            cm_file.write("\t-D" + i + "\n")
        cm_file.write(")\n\n")

        cm_file.write("SET(PROJECT_SOURCES\n")
        for group in project:
            for f in group['src']:
                cm_file.write( "\t" + os.path.normpath(f.rfile().abspath).replace("\\", "/") + "\n" )
        cm_file.write(")\n\n")

        if rtconfig.PLATFORM == 'gcc':
            cm_file.write("LINK_DIRECTORIES(\n")
            for group in project:
                if 'LIBPATH' in group.keys():
                    for f in group['LIBPATH']:
                        cm_file.write( "\t"+ f.replace("\\", "/") + "\n" )
            cm_file.write(")\n\n")

            cm_file.write("LINK_LIBRARIES(\n")
            for group in project:
                if 'LIBS' in group.keys():
                    for f in group['LIBS']:
                        cm_file.write( "\t"+ "{}\n".format(f.replace("\\", "/")))
            cm_file.write(")\n\n")

            cm_file.write("ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${PROJECT_SOURCES})\n")
            cm_file.write("ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD \nCOMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf)")
        elif rtconfig.CROSS_TOOL == 'keil':
            cm_file.write("ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})\n")
            cm_file.write("ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD \nCOMMAND ${CMAKE_FROMELF} --bin ${CMAKE_PROJECT_NAME}.elf --output ${CMAKE_PROJECT_NAME}.bin COMMAND ${CMAKE_FROMELF} -z ${CMAKE_PROJECT_NAME}.elf)")

        cm_file.close()

    return

def CMakeProject(env,project):
    print('Update setting files for CMakeLists.txt...')
    GenerateCFiles(env,project)
    print('Done!')

    return
