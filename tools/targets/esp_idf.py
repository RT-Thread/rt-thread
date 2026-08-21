import os
import re
import sys
import utils
from utils import _make_path_relative

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import target_utils

def GenerateCFiles(env,project):
    """
    Generate CMakeLists.txt files
    """
    info = utils.ProjectInfo(env)
    init_export = []

    main_component_dir = os.path.join(os.getcwd(), 'main')
    cm_file = open(os.path.join(main_component_dir, 'CMakeLists.txt'), 'w')
    if cm_file:
        cm_file.write("idf_component_register(\n")

        cm_file.write("\tSRCS\n")
        src_paths = []
        for group in project:
            for f in group['src']:
                path = _make_path_relative(main_component_dir, os.path.normpath(f.rfile().abspath))
                src_paths.append(path.replace("\\", "/"))
                src = open(f.rfile().abspath, 'r')
                for line in src.readlines():
                    if re.match(r'INIT_(BOARD|PREV|DEVICE|COMPONENT|ENV|APP)_EXPORT\(.+\)', line):
                        init_export.append(re.search(r'\(.+\)', line).group(0)[1:-1])
                src.close()
        # double-quote each item so a path with a space is one CMake argument,
        # and cmake_quote escapes an embedded ';' / '"' / '\\'; also de-duplicated
        for p in target_utils.ordered_unique(src_paths):
            cm_file.write('\t"' + target_utils.cmake_quote(p) + '"\n')

        cm_file.write("\n")

        cm_file.write("\tINCLUDE_DIRS\n")
        inc_paths = [_make_path_relative(main_component_dir, i).replace("\\", "/") for i in info['CPPPATH']]
        for p in target_utils.ordered_unique(inc_paths):
            cm_file.write('\t"' + target_utils.cmake_quote(p) + '"\n')
        cm_file.write(")\n\n")

        n = len(init_export)
        if n:
            cm_file.write("target_link_libraries(${COMPONENT_LIB}\n")
            for i in range(n):
                cm_file.write("\tINTERFACE \"-u __rt_init_" + init_export[i] + "\"\n")
            cm_file.write(")\n")
        cm_file.close()

    cm_file = open('CMakeLists.txt', 'w')
    if cm_file:
        cm_file.write("cmake_minimum_required(VERSION 3.16)\n")
        cm_file.write("set(COMPONENTS esptool_py main)\n")
        cm_file.write("include($ENV{IDF_PATH}/tools/cmake/project.cmake)\n")
        freertos_root = os.getcwd().replace('\\', '/') + '/packages/FreeRTOS_Wrapper-latest/FreeRTOS'
        cm_file.write("set(freertos_root " + freertos_root + ')\n')
        cm_file.write("project(rtthread)\n")
        cm_file.close()

def ESPIDFProject(env,project):
    print('Update setting files for CMakeLists.txt...')
    GenerateCFiles(env,project)
    print('Done!')
