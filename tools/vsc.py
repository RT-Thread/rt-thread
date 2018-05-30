"""
Utils for VSCode
"""

import os
import json
import utils
import rtconfig

def GenerateCFiles(env):
    """
    Generate c_cpp_properties files
    """
    if not os.path.exists('.vscode'):
        os.mkdir('.vscode')

    vsc_file = file('.vscode/c_cpp_properties.json', 'wb')
    if vsc_file:
        info = utils.ProjectInfo(env)

        cc = os.path.join(rtconfig.EXEC_PATH, rtconfig.CC)
        cc = os.path.abspath(cc).replace('\\', '/')

        config_obj = {}
        config_obj['name'] = 'Win32'
        config_obj['includePath'] = info['CPPPATH']
        config_obj['defines'] = info['CPPDEFINES']
        config_obj['intelliSenseMode'] = 'clang-x64'
        config_obj['compilerPath'] = cc
        config_obj['cStandard'] = "c99"
        config_obj['cppStandard'] = "c++11"

        json_obj = {}
        json_obj['configurations'] = [config_obj]

        vsc_file.write(json.dumps(json_obj))
        vsc_file.close()

    return

def GenerateVSCode(env):
    print('Update setting files for VSCode...'),
    GenerateCFiles(env)
    print('Done!')

    return
