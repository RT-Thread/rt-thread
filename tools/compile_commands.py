#
# File      : compile_commands.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Change Logs:
# Date           Author       Notes
# 2025-03-02     ZhaoCake    Create compile_commands.json without bear.

import os
import json
import re
from SCons.Script import *

def collect_compile_info(env):
    """收集编译命令和文件信息"""
    print("=> Starting compile command collection")
    compile_commands = []
    collected_files = set()

    def get_command_string(source, target, env, for_signature):
        """从SCons获取实际的编译命令"""
        if env.get('CCCOMSTR'):
            return env.get('CCCOM')
        return '${CCCOM}'

    def on_compile(target, source, env):
        """编译动作的回调函数"""
        print(f"   Processing compilation for {len(source)} source files")
        for src in source:
            src_path = str(src)
            if src_path in collected_files:
                continue
                
            collected_files.add(src_path)
            directory = os.path.abspath(os.path.dirname(src_path))
            
            # 构建编译命令
            command = env.subst(get_command_string(source, target, env, True))
            
            # 解析include路径
            includes = []
            for path in env.get('CPPPATH', []):
                includes.append('-I' + str(path))
            
            # 添加编译命令记录
            entry = {
                'directory': directory,
                'command': f"{command} {' '.join(includes)}",
                'file': os.path.abspath(src_path),
                'output': str(target[0]) if target else ''
            }
            compile_commands.append(entry)
            print(f"   Added compile command for: {os.path.basename(src_path)}")
            
    return on_compile, compile_commands

def generate_compile_commands(env):
    """生成compile_commands.json"""
    print("=> Enabling compile commands generation...")
    
    # 获取输出路径并存储到环境变量
    output_path = GetOption('compile-commands-out') or 'compile_commands.json'
    env['COMPILE_COMMANDS_OUT'] = output_path
    print(f"   Compile commands will be written to: {os.path.abspath(output_path)}")
    
    # 注册编译回调并保存到环境变量
    callback, compile_commands = collect_compile_info(env)
    env['COMPILE_COMMANDS'] = compile_commands
    env.AddPreAction('*.o', callback)
    print("   Registered compile command collector")
    
    # 定义后处理动作
    def write_compile_commands(target, source, env):
        print("\n=> [DEBUG] Entering write_compile_commands callback")
        print(f"   Target: {target}")
        print(f"   Source: {source}")
        
        output_path = env.get('COMPILE_COMMANDS_OUT', 'compile_commands.json')
        compile_commands = env.get('COMPILE_COMMANDS', [])
        
        try:
            if not compile_commands:
                print("Warning: No compile commands collected, skipping file generation")
                return

            print(f"\n=> Writing compile_commands.json ({len(compile_commands)} entries)")
            with open(output_path, 'w') as f:
                json.dump(compile_commands, f, indent=2)
            print(f"=> Successfully generated: {os.path.abspath(output_path)}")

        except PermissionError:
            print(f"\nError: Permission denied when writing to {output_path}")
            print("Please check file permissions and try again")
        except Exception as e:
            print(f"\nError writing compile_commands.json: {str(e)}")
            import traceback
            traceback.print_exc()
    
    # 使用None作为目标以确保总是执行
    print("=> Adding post-build action for compile_commands generation")
    env.AddPostAction(None, write_compile_commands)

def parse_compile_paths(json_path, rt_thread_root=None):
    """解析compile_commands.json并提取RT-Thread相关的包含路径
    
    Args:
        json_path: compile_commands.json的路径
        rt_thread_root: RT-Thread根目录路径,默认使用环境变量RTT_ROOT
        
    Returns:
        dict: 包含以下键的字典:
            'sources': RT-Thread源文件的相对路径列表 
            'includes': RT-Thread头文件目录的相对路径列表
    """
    if rt_thread_root is None:
        rt_thread_root = os.getenv('RTT_ROOT')
        if not rt_thread_root:
            raise ValueError("RT-Thread根目录未指定")
    
    rt_thread_root = os.path.abspath(rt_thread_root)
    result = {
        'sources': set(),
        'includes': set()
    }
    
    try:
        with open(json_path, 'r') as f:
            compile_commands = json.load(f)
            
        for entry in compile_commands:
            # 处理源文件
            src_file = entry.get('file', '')
            if src_file.startswith(rt_thread_root):
                rel_path = os.path.relpath(src_file, rt_thread_root)
                result['sources'].add(os.path.dirname(rel_path))
            
            # 处理包含路径 
            command = entry.get('command', '')
            include_paths = [p[2:] for p in command.split() if p.startswith('-I')]
            
            for inc_path in include_paths:
                if inc_path.startswith(rt_thread_root):
                    rel_path = os.path.relpath(inc_path, rt_thread_root)
                    result['includes'].add(rel_path)
        
        # 转换为排序列表
        result['sources'] = sorted(list(result['sources']))
        result['includes'] = sorted(list(result['includes']))
        
        return result
        
    except Exception as e:
        print(f"Error parsing compile_commands.json: {str(e)}")
        return None

def get_minimal_dist_paths(json_path=None, rt_thread_root=None):
    """获取最小化发布所需的路径
    
    Args:
        json_path: compile_commands.json的路径,默认为当前目录下的compile_commands.json
        rt_thread_root: RT-Thread根目录路径
        
    Returns:
        list: 需要包含在发布包中的相对路径列表
    """
    if json_path is None:
        json_path = 'compile_commands.json'
        
    paths = parse_compile_paths(json_path, rt_thread_root)
    if not paths:
        return []
    
    # 合并源码和头文件路径
    all_paths = set(paths['sources']) | set(paths['includes'])
    
    return sorted(list(all_paths))
