import os
import re
import utils
from utils import _make_path_relative

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
        for group in project:
            for f in group['src']:
                path = _make_path_relative(main_component_dir, os.path.normpath(f.rfile().abspath))
                cm_file.write( "\t" + path.replace("\\", "/") + "\n" ) 
                src = open(f.rfile().abspath, 'r')
                for line in src.readlines():
                    if re.match('INIT_(BOARD|PREV|DEVICE|COMPONENT|ENV|APP)_EXPORT\(.+\)', line):
                        init_export.append(re.search('\(.+\)', line).group(0)[1:-1])
                src.close()

        cm_file.write("\n")

        cm_file.write("\tINCLUDE_DIRS\n")
        for i in info['CPPPATH']:
            path = _make_path_relative(main_component_dir, i)
            cm_file.write( "\t" + path.replace("\\", "/") + "\n")
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
