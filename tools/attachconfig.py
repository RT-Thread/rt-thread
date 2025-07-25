import os
import sys
import shutil
import yaml

from SCons.Script import *

# SCons AttachConfig Command Function
def GenAttachConfigProject(program = None):
    Rtt_Root = os.getcwd()
    config_file = os.path.join(os.getcwd(), 'rtt_root', Rtt_Root, '.config')
    config_bacakup = config_file+'.origin'
    rtconfig_file = os.path.join(os.getcwd(), 'rtt_root', Rtt_Root, 'rtconfig.h')
    rtconfig__bacakup = rtconfig_file+'.origin'
    if GetOption('attach') == '?':
        attachconfig=[]
        GetAttachConfig("get",attachconfig,0)
        print("\033[32m✅ AttachConfig has: \033[0m")
        prefix=attachconfig[0]
        for line in attachconfig:
            temp_prefix=line.split(".", 1)
            if prefix!=temp_prefix[0]:
                print("\033[42m \033[30m------"+temp_prefix[0]+"------\033[0m")
                prefix=temp_prefix[0]
            print(line)
            
            
    elif GetOption('attach') == 'default':
        if os.path.exists(config_bacakup):
            shutil.copyfile(config_bacakup, config_file)
            os.remove(config_bacakup)
        if os.path.exists(rtconfig__bacakup):
            shutil.copyfile(rtconfig__bacakup, rtconfig_file)
            os.remove(rtconfig__bacakup)
        print("\033[32m✅ Default .config and rtconfig.h recovery success!\033[0m")
    else:
        attachconfig=GetOption('attach')
        attachconfig_result=[]
        GetAttachConfig("search",attachconfig,attachconfig_result)
        if attachconfig_result==[]:
            print("❌\033[31m Without this AttachConfig:"+attachconfig+"\033[0m")
            return
        if os.path.exists(config_bacakup)==False:
            shutil.copyfile(config_file, config_bacakup)
        if os.path.exists(rtconfig__bacakup)==False:
            shutil.copyfile(rtconfig_file, rtconfig__bacakup)
        with open(config_file, 'a') as destination:
            for line in attachconfig_result:
                destination.write(line + '\n')
        from env_utility import defconfig
        defconfig(Rtt_Root)
        print("\033[32m✅ AttachConfig add success!\033[0m")

def GetAttachConfig(action,attachconfig,attachconfig_result):
    rtt_root = os.getcwd()
    yml_files_content = []
    directory = os.path.join(rtt_root, 'rtt_root', rtt_root, '.ci/attachconfig')
    if os.path.exists(directory):
            for root, dirs, files in os.walk(directory):
                for filename in files:
                    if filename.endswith('attachconfig.yml'):
                        file_path = os.path.join(root, filename)
                        if os.path.exists(file_path):
                            try:
                                with open(file_path, 'r') as file:
                                    content = yaml.safe_load(file)
                                    if content is None:
                                        continue
                                    yml_files_content.append(content)
                            except yaml.YAMLError as e:
                                print(f"::error::Error parsing YAML file: {e}")
                                continue
                            except Exception as e:
                                print(f"::error::Error reading file: {e}")
                                continue
    for projects in yml_files_content:
            for name, details in projects.items():
                if details.get("kconfig") is None:
                    continue
                if(projects.get(name) is not None):
                    if action == "get":
                        attachconfig.append(name)
                    if action == "search" and name == attachconfig:
                        from ci.bsp_buildings import get_details_and_dependencies
                        detail_list=get_details_and_dependencies([name],projects)
                        for line in detail_list:
                            attachconfig_result.append(line)