"""
Utils for CMake
Author: https://github.com/klivelinux
"""

import os
import sys
import re
import utils
import rtconfig
from utils import _make_path_relative
from collections import defaultdict, Counter


def GenerateCFiles(env, project, project_name):
    """
    Generate CMakeLists.txt files
    """
    info = utils.ProjectInfo(env)
    
    PROJECT_NAME = project_name if project_name != "project" else "rtthread"

    tool_path_conv = defaultdict(lambda : {"name":"", "path": ""})
    tool_path_conv_helper = lambda tool: {"name": tool, "path": os.path.join(rtconfig.EXEC_PATH, tool).replace('\\', "/")}
    
    tool_path_conv["CMAKE_C_COMPILER"] = tool_path_conv_helper(rtconfig.CC)
    if 'CXX' in dir(rtconfig):
        tool_path_conv["CMAKE_CXX_COMPILER"] = tool_path_conv_helper(rtconfig.CXX)
    tool_path_conv["CMAKE_ASM_COMPILER"] = tool_path_conv_helper(rtconfig.AS)
    tool_path_conv["CMAKE_AR"] = tool_path_conv_helper(rtconfig.AR)
    tool_path_conv["CMAKE_LINKER"] = tool_path_conv_helper(rtconfig.LINK)
    if rtconfig.PLATFORM in ['gcc']:
        tool_path_conv["CMAKE_SIZE"] = tool_path_conv_helper(rtconfig.SIZE)
        tool_path_conv["CMAKE_OBJDUMP"] = tool_path_conv_helper(rtconfig.OBJDUMP)
        tool_path_conv["CMAKE_OBJCOPY"] = tool_path_conv_helper(rtconfig.OBJCPY)
    elif rtconfig.PLATFORM in ['armcc', 'armclang']:
        tool_path_conv["CMAKE_FROMELF"] = tool_path_conv_helper(rtconfig.FROMELF)
        
    CC = tool_path_conv["CMAKE_C_COMPILER"]["path"]
    CXX = tool_path_conv["CMAKE_CXX_COMPILER"]["path"]
    AS = tool_path_conv["CMAKE_ASM_COMPILER"]["path"]
    AR = tool_path_conv["CMAKE_AR"]["path"]
    LINK = tool_path_conv["CMAKE_LINKER"]["path"]
    SIZE = tool_path_conv["CMAKE_SIZE"]["path"]
    OBJDUMP = tool_path_conv["CMAKE_OBJDUMP"]["path"]
    OBJCOPY = tool_path_conv["CMAKE_OBJCOPY"]["path"]
    FROMELF = tool_path_conv["CMAKE_FROMELF"]["path"]

    CFLAGS = rtconfig.CFLAGS.replace('\\', "/").replace('\"', "\\\"")
    if 'CXXFLAGS' in dir(rtconfig):
        CXXFLAGS = rtconfig.CXXFLAGS.replace('\\', "/").replace('\"', "\\\"")
    else:
        CXXFLAGS = CFLAGS
    AFLAGS = rtconfig.AFLAGS.replace('\\', "/").replace('\"', "\\\"")
    LFLAGS = env['LINKFLAGS'].replace('\\', "/").replace('\"', "\\\"")
    
    POST_ACTION = rtconfig.POST_ACTION
    # replace the tool name with the cmake variable
    for cmake_var, each_tool in tool_path_conv.items():
        tool_name = each_tool['name']
        if tool_name == "": continue
        if "win32" in sys.platform:
            while f"{tool_name}.exe" in POST_ACTION:    # find the tool with `.exe` suffix first
                POST_ACTION = POST_ACTION.replace(tool_name, "string_to_replace")
        while tool_name in POST_ACTION:
            POST_ACTION = POST_ACTION.replace(tool_name, "string_to_replace")
        while "string_to_replace" in POST_ACTION:
            POST_ACTION = POST_ACTION.replace("string_to_replace", f"${{{cmake_var}}}")
    # replace the `$TARGET` with `${CMAKE_PROJECT_NAME}.elf`
    while "$TARGET" in POST_ACTION:
        POST_ACTION = POST_ACTION.replace("$TARGET", "${CMAKE_PROJECT_NAME}.elf")
    # add COMMAAND before each command
    POST_ACTION = POST_ACTION.split('\n')
    POST_ACTION = [each_line.strip() for each_line in POST_ACTION]
    POST_ACTION = [f"\tCOMMAND {each_line}" for each_line in POST_ACTION if each_line != '']
    POST_ACTION = "\n".join(POST_ACTION)

    if "win32" in sys.platform:
        CC += ".exe"
        if CXX != '':
            CXX += ".exe"
        AS += ".exe"
        AR += ".exe"
        LINK += ".exe"
        if rtconfig.PLATFORM in ['gcc']:
            SIZE += ".exe"
            OBJDUMP += ".exe"
            OBJCOPY += ".exe"
        elif rtconfig.PLATFORM in ['armcc', 'armclang']:
            FROMELF += ".exe"

    if not os.path.exists(CC) or not os.path.exists(AS) or not os.path.exists(AR) or not os.path.exists(LINK):
        print("'Cannot found toolchain directory, please check RTT_CC and RTT_EXEC_PATH'")
        sys.exit(-1)

    with open("CMakeLists.txt", "w") as cm_file:
        cm_file.write("CMAKE_MINIMUM_REQUIRED(VERSION 3.10)\n\n")

        cm_file.write("SET(CMAKE_SYSTEM_NAME Generic)\n")
        cm_file.write("SET(CMAKE_SYSTEM_PROCESSOR " + rtconfig.CPU +")\n")
        cm_file.write("#SET(CMAKE_VERBOSE_MAKEFILE ON)\n\n")
        cm_file.write("SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n")

        cm_file.write("SET(CMAKE_C_COMPILER \""+ CC + "\")\n")
        cm_file.write("SET(CMAKE_ASM_COMPILER \""+ AS + "\")\n")
        cm_file.write("SET(CMAKE_C_FLAGS \""+ CFLAGS + "\")\n")
        cm_file.write("SET(CMAKE_ASM_FLAGS \""+ AFLAGS + "\")\n")
        cm_file.write("SET(CMAKE_C_COMPILER_WORKS TRUE)\n\n")

        if CXX != '':
            cm_file.write("SET(CMAKE_CXX_COMPILER \""+ CXX + "\")\n")
            cm_file.write("SET(CMAKE_CXX_FLAGS \""+ CXXFLAGS + "\")\n")
            cm_file.write("SET(CMAKE_CXX_COMPILER_WORKS TRUE)\n\n")

        if rtconfig.PLATFORM in ['gcc']:
            cm_file.write("SET(CMAKE_OBJCOPY \""+ OBJCOPY + "\")\n")
            cm_file.write("SET(CMAKE_SIZE \""+ SIZE + "\")\n\n")
        elif rtconfig.PLATFORM in ['armcc', 'armclang']:
            cm_file.write("SET(CMAKE_FROMELF \""+ FROMELF + "\")\n\n")

        LINKER_FLAGS = ''
        LINKER_LIBS = ''
        if rtconfig.PLATFORM in ['gcc']:
            LINKER_FLAGS += '-T'
        elif rtconfig.PLATFORM in ['armcc', 'armclang']:
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

        # get the c/cpp standard version from compilation flags
        # not support the version with alphabet in `-std` param yet
        pattern = re.compile('-std=[\w+]+')
        c_standard = 11
        if '-std=' in CFLAGS:
            c_standard = re.search(pattern, CFLAGS).group(0)
            c_standard = "".join([each for each in c_standard if each.isdigit()])
        else:
            print(f"Cannot find the param of the c standard in build flag, set to default {c_standard}")
        cm_file.write(f"SET(CMAKE_C_STANDARD {c_standard})\n")

        if CXX != '':
            cpp_standard = 17
            if '-std=' in CXXFLAGS:
                cpp_standard = re.search(pattern, CXXFLAGS).group(0)
                cpp_standard = "".join([each for each in cpp_standard if each.isdigit()])
            else:
                print(f"Cannot find the param of the cpp standard in build flag, set to default {cpp_standard}")
            cm_file.write(f"SET(CMAKE_CXX_STANDARD {cpp_standard})\n")
        
        cm_file.write('\n')

        cm_file.write(f"PROJECT({PROJECT_NAME} C {'CXX' if CXX != '' else ''} ASM)\n")
        
        cm_file.write('\n')

        cm_file.write("INCLUDE_DIRECTORIES(\n")
        for i in info['CPPPATH']:
            # use relative path
            path = _make_path_relative(os.getcwd(), i)
            cm_file.write( "\t" + path.replace("\\", "/") + "\n")
        cm_file.write(")\n\n")

        cm_file.write("ADD_DEFINITIONS(\n")
        for i in info['CPPDEFINES']:
            cm_file.write("\t-D" + i + "\n")
        cm_file.write(")\n\n")

        libgroups = []
        interfacelibgroups = []
        for group in project:
            if group['name'] == 'Applications':
                continue

            # When a group is provided without sources, add it to the <INTERFACE> library list
            if len(group['src']) == 0:
                interfacelibgroups.append(group)
            else:
                libgroups.append(group)

        # Process groups whose names differ only in capitalization.
        # (Groups have same name should be merged into one before)
        for group in libgroups:
            group['alias'] = group['name'].lower()
        names = [group['alias'] for group in libgroups]
        counter = Counter(names)
        names = [name for name in names if counter[name] > 1]
        for group in libgroups:
            if group['alias'] in names:
                counter[group['alias']] -= 1
                group['alias'] = f"{group['name']}_{counter[group['alias']]}"
                print(f"Renamed {group['name']} to {group['alias']}")
                group['name'] = group['alias']

        cm_file.write("# Library source files\n")
        for group in project:
            cm_file.write("SET(RT_{:s}_SOURCES\n".format(group['name'].upper()))
            for f in group['src']:
                # use relative path
                path = _make_path_relative(os.getcwd(), os.path.normpath(f.rfile().abspath))
                cm_file.write( "\t" + path.replace("\\", "/") + "\n" )
            cm_file.write(")\n\n")

        cm_file.write("# Library search paths\n")
        for group in libgroups + interfacelibgroups:
            if not 'LIBPATH' in group.keys():
                continue

            if len(group['LIBPATH']) == 0:
                continue

            cm_file.write("SET(RT_{:s}_LINK_DIRS\n".format(group['name'].upper()))
            for f in group['LIBPATH']:
                cm_file.write("\t"+ f.replace("\\", "/") + "\n" )
            cm_file.write(")\n\n")

        cm_file.write("# Library local macro definitions\n")
        for group in libgroups:
            if not 'LOCAL_CPPDEFINES' in group.keys():
                continue

            if len(group['LOCAL_CPPDEFINES']) == 0:
                continue

            cm_file.write("SET(RT_{:s}_DEFINES\n".format(group['name'].upper()))
            for f in group['LOCAL_CPPDEFINES']:
                cm_file.write("\t"+ f.replace("\\", "/") + "\n" )
            cm_file.write(")\n\n")

        cm_file.write("# Library dependencies\n")
        for group in libgroups + interfacelibgroups:
            if not 'LIBS' in group.keys():
                continue

            if len(group['LIBS']) == 0:
                continue

            cm_file.write("SET(RT_{:s}_LIBS\n".format(group['name'].upper()))
            for f in group['LIBS']:
                cm_file.write("\t"+ "{}\n".format(f.replace("\\", "/")))
            cm_file.write(")\n\n")

        cm_file.write("# Libraries\n")
        for group in libgroups:
            cm_file.write("ADD_LIBRARY(rtt_{:s} OBJECT ${{RT_{:s}_SOURCES}})\n"
                          .format(group['name'], group['name'].upper()))

        cm_file.write("\n")

        cm_file.write("# Interface libraries\n")
        for group in interfacelibgroups:
            cm_file.write("ADD_LIBRARY(rtt_{:s} INTERFACE)\n".format(group['name']))

        cm_file.write("\n")

        cm_file.write("# Private macros\n")
        for group in libgroups:
            if not 'LOCAL_CPPDEFINES' in group.keys():
                continue

            if len(group['LOCAL_CPPDEFINES']) == 0:
                continue

            cm_file.write("TARGET_COMPILE_DEFINITIONS(rtt_{:s} PRIVATE ${{RT_{:s}_DEFINES}})\n"
              .format(group['name'], group['name'].upper()))

        cm_file.write("\n")

        cm_file.write("# Interface library search paths\n")
        if rtconfig.PLATFORM in ['gcc']:
            for group in libgroups:
                if not 'LIBPATH' in group.keys():
                    continue

                if len(group['LIBPATH']) == 0:
                    continue

                cm_file.write("TARGET_LINK_DIRECTORIES(rtt_{:s} INTERFACE ${{RT_{:s}_LINK_DIRS}})\n"
                              .format(group['name'], group['name'].upper()))

            for group in libgroups:
                if not 'LIBS' in group.keys():
                    continue

                if len(group['LIBS']) == 0:
                    continue

                cm_file.write("TARGET_LINK_LIBRARIES(rtt_{:s} INTERFACE ${{RT_{:s}_LIBS}})\n"
                              .format(group['name'], group['name'].upper()))

        cm_file.write("\n")

        cm_file.write("ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${RT_APPLICATIONS_SOURCES})\n")

        cm_file.write("TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}.elf\n")
        for group in libgroups + interfacelibgroups:
            cm_file.write("\trtt_{:s}\n".format(group['name']))
        cm_file.write(")\n\n")

        cm_file.write("ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD \n" + POST_ACTION + '\n)\n')

        # auto inclue `custom.cmake` for user custom settings
        custom_cmake = \
            '''
            # if custom.cmake is exist, add it
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/custom.cmake)
                include(${CMAKE_CURRENT_SOURCE_DIR}/custom.cmake)
            endif()
            '''
        custom_cmake = custom_cmake.split('\n')
        custom_cmake = [each.strip() for each in custom_cmake]
        custom_cmake = "\n".join(custom_cmake)
        cm_file.write(custom_cmake)

    return

def CMakeProject(env, project, project_name):
    print('Update setting files for CMakeLists.txt...')
    GenerateCFiles(env, project, project_name)
    print('Done!')

    return
