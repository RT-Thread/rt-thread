#
# Copyright (c) 2006-2023, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2023-06-27     dejavudwh    the first version
#

import subprocess
import logging
import os

CONFIG_BSP_USING_X = ["CONFIG_BSP_USING_UART", "CONFIG_BSP_USING_I2C", "CONFIG_BSP_USING_SPI", "CONFIG_BSP_USING_ADC", "CONFIG_BSP_USING_DAC"]

def init_logger():
    log_format = "[%(filename)s %(lineno)d %(levelname)s] %(message)s "
    date_format = '%Y-%m-%d  %H:%M:%S %a '
    logging.basicConfig(level=logging.INFO,
                        format=log_format,
                        datefmt=date_format,
                        )

def diff():
    result = subprocess.run(['git', 'diff', '--name-only', 'HEAD', 'origin/master', '--diff-filter=ACMR', '--no-renames', '--full-index'], stdout = subprocess.PIPE)
    file_list = result.stdout.decode().strip().split('\n')
    logging.info(file_list)
    bsp_paths = set()
    for file in file_list:
        if "bsp/" in file:
            logging.info("Modifed file: {}".format(file))
            bsp_paths.add(file)
    
    dirs = set()
    for dir in bsp_paths:
        dir = os.path.dirname(dir)    
        while "bsp/" in dir:
            files = os.listdir(dir)
            if ".config" in files and "rt-thread.elf" not in files and not dir.endswith("bsp"):
                logging.info("Found bsp path: {}".format(dir))
                dirs.add(dir)
                break
            new_dir = os.path.dirname(dir)    
            dir = new_dir

    return dirs

def check_config_in_line(line):
    for config in CONFIG_BSP_USING_X:
        if config in line and '#' in line:
            logging.info("Found in {}".format(line))
            return config    
    
    return ""

def check_config_in_file(file_path):
    configs = set()
    found = False
    try:
        with open(file_path, 'r') as file:
            for line in file:
                line.strip()
                if found:
                    res = check_config_in_line(line)
                    if res:
                        configs.add(res)
                elif "On-chip Peripheral Drivers" in line:
                    logging.info("Found On-chip Peripheral Drivers")
                    found = True
    except FileNotFoundError:
        logging.error("The .config file does not exist for this BSP, please recheck the file directory!")

    return configs

def modify_config(file_path, configs): 
    with open(file_path + "/rtconfig.h", 'a') as file:
        for item in configs:
            define1 = item.replace("CONFIG_BSP", "BSP")
            define2 = item.replace("CONFIG_BSP", "RT")
            file.write("#define " + define1 + "\n")
            file.write("#define " + define2 + "\n")

def recompile_bsp(dir):
    logging.info("recomplie bsp: {}".format(dir))
    os.system("scons -C " + dir)

if __name__ == '__main__':
    init_logger()
    recompile_bsp_dirs = diff()
    for dir in recompile_bsp_dirs:
        dot_config_path = dir + "/" + ".config"
        configs = check_config_in_file(dot_config_path)
        logging.info("add config:")
        logging.info(configs)
        logging.info("Add configurations and recompile!")
        modify_config(dir, configs)
        recompile_bsp(dir)