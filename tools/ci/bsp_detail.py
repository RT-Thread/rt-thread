# 
# Copyright (c) 2024, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2024-08-24     supperthomas the first version
#

# 这个文件会根据bsp中的信息生成对应的bsp_detail.yml文件，这个文件会包含bsp中的一些信息，比如是否有Kconfig文件，是否有template.uvprojx文件等等
# 根据生成的bsp_detail.yml文件，会生成一个toolchain_bsp.yml文件，这个文件会包含所有的gcc编译器的信息，以及对应的bsp文件夹

import os
import pandas as pd
import yaml
from datetime import datetime
import subprocess
#pip install pandas
#pip install tabulate


# 产生toolchain.yml文件
def generate_toolchain_yaml(input_file, output_file, header_comment):
    with open(input_file, 'r', encoding='utf-8') as file:
        data = yaml.safe_load(file)
    
    toolchain_data = {}
    for folder, details in data.items():
        gcc = details.get('gcc')
        if gcc:
            if gcc not in toolchain_data:
                toolchain_data[gcc] = {'bsp': []}
            toolchain_data[gcc]['bsp'].append(folder)
    
    with open(output_file, 'w', encoding='utf-8') as file:
        file.write(f"# {header_comment}\n")
        yaml.dump(toolchain_data, file, default_flow_style=False, allow_unicode=True)


# 这个脚本主要用来生成一个bsp相关的信息的文件放到bsp根目录下面
def check_files(root_dir, file_list):
    data = []
    folders_checked = set()
    for projects in sconstruct_paths:
        if projects not in folders_checked:
            #file_dict = {file: True if os.path.isfile(os.path.join(projects, file)) else '' for file in file_list}
            file_dict = {}
            for file in file_list:
                file_exists = os.path.isfile(os.path.join(projects, file))
                if file == 'template.uvprojx':
                    file_dict['mdk5'] = True if file_exists else False
                elif file == 'template.ewp':
                    file_dict['iar'] = True if file_exists else False
                elif file == 'template.uvproj':
                    file_dict['mdk4'] = True if file_exists else False
                elif file == 'template.Uv2':
                    file_dict['mdk3'] = True if file_exists else False
                elif file == 'Kconfig':
                    file_dict['menuconfig'] = True if file_exists else False
                else:
                    file_dict[file] = True if file_exists else False

            # 提取 rtconfig.py 中的 PREFIX 信息
            rtconfig_path = os.path.join(projects, 'rtconfig.py')
            if os.path.isfile(rtconfig_path):
                print(f"Reading {rtconfig_path}")
                with open(rtconfig_path, 'r') as f:
                    for line in f:
                        if line.strip().startswith('PREFIX'):
                            prefix_value = line.split('=')[1].strip().strip("'\"")
                            # 只提取实际的编译器前缀
                            if 'os.getenv' in prefix_value:
                                prefix_value = prefix_value.split('or')[-1].strip().strip("'\"")
                            file_dict['gcc'] = f"{prefix_value}gcc"
                            print(f"Found PREFIX: {prefix_value} in {rtconfig_path}")
                            break
                    else:
                        print(f"No PREFIX found in {rtconfig_path}")


            # 去掉路径中的 '/workspaces/rt-thread/bsp/' 部分
            projects2 = projects.replace(root_dir + '/', '')
            file_dict['Folder'] = projects2
            data.append(file_dict)
            #data.append({'Folder': projects2, **file_dict})
            folders_checked.add(projects)
    df = pd.DataFrame(data)
    return df

def find_sconstruct_paths(project_dir, exclude_paths):
    sconstruct_paths = []
    for root, dirs, files in os.walk(project_dir):
        
        if all(exclude_path not in root for exclude_path in exclude_paths):
            
            if 'SConstruct' in files:
                sconstruct_paths.append(root)
    return sconstruct_paths

def output_to_markdown(df, output_file):
    with open(output_file, 'w', encoding='utf-8') as file:
        file.write(df.to_markdown(index=False))

def output_to_yaml(dataframe, output_file, header_comment):
    data = dataframe.to_dict(orient='records')
    yaml_data = {}
    for item in data:
        folder = item.pop('Folder')
        filtered_item = {k: v for k, v in item.items() if v is True or isinstance(v, str)}
        yaml_data[folder] = filtered_item
    with open(output_file, 'w', encoding='utf-8') as file:
        file.write(f"# {header_comment}\n")
        yaml.dump(yaml_data, file, default_flow_style=False, allow_unicode=True)

# 示例用法:
# Find the rt-thread root directory
rtt_root = os.getcwd()
while not os.path.exists(os.path.join(rtt_root, 'LICENSE')):
    rtt_root = os.path.dirname(rtt_root)
bsp_root = os.path.join(rtt_root, 'bsp')

exclude_paths = ['templates', 'doc']
files_to_check = ['README.md','rtconfig.h', '.config','Kconfig', 'template.uvprojx','template.ewp', 'README.md', 'README_ZH.md', 'template.Uv2','template.uvproj']
sconstruct_paths = find_sconstruct_paths(bsp_root, exclude_paths)
result_table = check_files(bsp_root, files_to_check)
print(result_table)
output_file = 'output.md'

output_to_markdown(result_table, output_file)

# 将 output.yml 和 toolchain.yml 文件保存到 bsp 目录下

# 获取今天的日期
today_date = datetime.today().strftime('%Y-%m-%d')

# 获取当前年份
current_year = datetime.today().year

def get_git_user_name():
    try:
        result = subprocess.run(['git', 'config', 'user.name'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode == 0:
            return result.stdout.strip()
        else:
            return "Unknown Author"
    except Exception as e:
        return "Unknown Author"

# 获取 Git 用户名
author_name = get_git_user_name()

# 头部注释
header_comment = f"""
# Copyright (c) {current_year}, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# {today_date}     {author_name} the first version
#
"""
# 将 output.yml 和 toolchain.yml 文件保存到 tools/ci 目录下
ci_dir = os.path.join(rtt_root, 'tools', 'ci')
os.makedirs(ci_dir, exist_ok=True)

bsp_detail_file = os.path.join(ci_dir, 'bsp_detail.yml')
output_to_yaml(result_table, bsp_detail_file, header_comment)

toolchain_output_file = os.path.join(ci_dir, 'toolchain_bsp.yml')
generate_toolchain_yaml(bsp_detail_file, toolchain_output_file, header_comment)