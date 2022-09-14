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

        print(init_export)
        n = len(init_export)
        if n:
            cm_file.write("target_link_libraries(${COMPONENT_LIB}\n")
            for i in range(n):
                cm_file.write("\tINTERFACE \"-u __rt_init_" + init_export[i] + "\"\n")
            cm_file.write(")\n")

def ESPIDFProject(env,project):
    print('Update setting files for CMakeLists.txt...')
    GenerateCFiles(env,project)
    print('Done!')
