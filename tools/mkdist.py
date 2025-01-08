#
# File      : mkdir.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
# 2017-10-04     Bernard      The first version
# 2025-01-07     ZhaoCake     components copy and gen doc

import os
import subprocess
import shutil
from shutil import ignore_patterns
from SCons.Script import *
import time

def do_copy_file(src, dst):
    # check source file
    if not os.path.exists(src):
        return

    path = os.path.dirname(dst)
    # mkdir if path not exist
    if not os.path.exists(path):
        os.makedirs(path)

    shutil.copy2(src, dst)

def do_copy_folder(src_dir, dst_dir, ignore=None):
    # check source directory
    if not os.path.exists(src_dir):
        return

    try:
        if os.path.exists(dst_dir):
            shutil.rmtree(dst_dir)
    except:
        print('Deletes folder: %s failed.' % dst_dir)
        return

    shutil.copytree(src_dir, dst_dir, ignore = ignore)

source_ext = ['c', 'h', 's', 'S', 'cpp', 'cxx', 'cc', 'xpm']
source_list = []

def walk_children(child):
    global source_list
    global source_ext

    # print child
    full_path = child.rfile().abspath
    file_type  = full_path.rsplit('.',1)[1]
    #print file_type
    if file_type in source_ext:
        if full_path not in source_list:
            source_list.append(full_path)

    children = child.all_children()
    if children != []:
        for item in children:
            walk_children(item)

def walk_kconfig(RTT_ROOT, source_list):
    for parent, dirnames, filenames in os.walk(RTT_ROOT):
        if 'bsp' in parent:
            continue
        if '.git' in parent:
            continue
        if 'tools' in parent:
            continue

        if 'Kconfig' in filenames:
            pathfile = os.path.join(parent, 'Kconfig')
            source_list.append(pathfile)
        if 'KConfig' in filenames:
            pathfile = os.path.join(parent, 'KConfig')
            source_list.append(pathfile)

def bsp_copy_files(bsp_root, dist_dir):
    # copy BSP files
    do_copy_folder(os.path.join(bsp_root), dist_dir,
        ignore_patterns('build','__pycache__','dist', '*.pyc', '*.old', '*.map', 'rtthread.bin', '.sconsign.dblite', '*.elf', '*.axf', 'cconfig.h'))

def bsp_update_sconstruct(dist_dir):
    with open(os.path.join(dist_dir, 'SConstruct'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'SConstruct'), 'w') as f:
        for line in data:
            if line.find('RTT_ROOT') != -1:
                if line.find('sys.path') != -1:
                    f.write('# set RTT_ROOT\n')
                    f.write('if not os.getenv("RTT_ROOT"): \n    RTT_ROOT="rt-thread"\n\n')
            f.write(line)

def bsp_update_kconfig_testcases(dist_dir):
    # delete testcases in rt-thread/Kconfig
    if not os.path.isfile(os.path.join(dist_dir, 'rt-thread/Kconfig')):
        return

    with open(os.path.join(dist_dir, 'rt-thread/Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'rt-thread/Kconfig'), 'w') as f:
        for line in data:
            if line.find('examples/utest/testcases/Kconfig') == -1:
                f.write(line)

def bsp_update_kconfig(dist_dir):
    # change RTT_ROOT in Kconfig
    if not os.path.isfile(os.path.join(dist_dir, 'Kconfig')):
        return

    with open(os.path.join(dist_dir, 'Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'Kconfig'), 'w') as f:
        for line in data:
            if line.find('RTT_DIR') != -1 and line.find(':=') != -1:
                line = 'RTT_DIR := rt-thread\n'
            f.write(line)

def bsp_update_kconfig_library(dist_dir):
    # change RTT_ROOT in Kconfig
    if not os.path.isfile(os.path.join(dist_dir, 'Kconfig')):
        return

    with open(os.path.join(dist_dir, 'Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'Kconfig'), 'w') as f:
        for line in data:
            if line.find('source') != -1 and line.find('../libraries') != -1:
                line = line.replace('../libraries', 'libraries')
            f.write(line)

    # change board/kconfig path
    if not os.path.isfile(os.path.join(dist_dir, 'board/Kconfig')):
        return

    with open(os.path.join(dist_dir, 'board/Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(dist_dir, 'board/Kconfig'), 'w') as f:
        for line in data:
            if line.find('source') != -1 and line.find('../libraries') != -1:
                line = line.replace('../libraries', 'libraries')
            f.write(line)

def zip_dist(dist_dir, dist_name):
    import zipfile

    zip_filename = os.path.join(dist_dir)
    zip = zipfile.ZipFile(zip_filename + '.zip', 'w')
    pre_len = len(os.path.dirname(dist_dir))

    for parent, dirnames, filenames in os.walk(dist_dir):
        for filename in filenames:
            pathfile = os.path.join(parent, filename)
            arcname = pathfile[pre_len:].strip(os.path.sep)
            zip.write(pathfile, arcname)

    zip.close()

def parse_components_from_config(config_file):
    """Parse enabled components from .config file"""
    enabled_components = set()
    
    if not os.path.exists(config_file):
        print(f"Error: {config_file} does not exist")
        return enabled_components
        
    with open(config_file, 'r') as f:
        for line in f:
            line = line.strip()
            # Skip empty lines and comments
            if not line or line.startswith('#'):
                continue
                
            if line.startswith('CONFIG_'):
                if '=' in line:
                    config = line.split('=')[0][7:]  # Remove CONFIG_ prefix
                    if config.startswith('RT_USING_'):
                        component = config[9:].lower()  # Remove RT_USING_ prefix
                        enabled_components.add(component)
    return enabled_components

def scan_components_dir(RTT_ROOT):
    """Scan component directory structure and generate component mapping"""
    components_map = {}
    components_root = os.path.join(RTT_ROOT, 'components')
    
    def parse_kconfig(kconfig_file):
        """Parse configuration options from Kconfig file"""
        components = set()
        try:
            with open(kconfig_file, 'r') as f:
                content = f.read()
                # Find configurations in the form of config RT_USING_XXX
                import re
                matches = re.finditer(r'config\s+RT_USING_(\w+)', content)
                for match in matches:
                    component_name = match.group(1).lower()
                    components.add(component_name)
        except Exception as e:
            print(f"Warning: Failed to parse {kconfig_file}: {str(e)}")
        return components

    def get_relative_path(full_path):
        """Get path relative to RTT_ROOT"""
        rel_path = os.path.relpath(os.path.dirname(full_path), RTT_ROOT)
        # Skip if path is directly under components directory
        if rel_path == 'components' or rel_path == os.path.join('components', ''):
            return None
        return rel_path

    # Scan all component directories
    for root, dirs, files in os.walk(components_root):
        if 'Kconfig' in files:
            kconfig_path = os.path.join(root, 'Kconfig')
            component_configs = parse_kconfig(kconfig_path)
            rel_path = get_relative_path(kconfig_path)
            
            # Only add component if it has a valid sub-path
            if rel_path:
                for comp_name in component_configs:
                    components_map[comp_name] = rel_path

    return components_map

def get_component_path(component_name, RTT_ROOT):
    """Get actual path of component"""
    # Get dynamic component mapping
    dynamic_map = scan_components_dir(RTT_ROOT)
    return dynamic_map.get(component_name)

def generate_dist_doc(dist_dir, enabled_components, project_name, BSP_ROOT, RTT_ROOT):
    """Generate distribution package documentation"""
    doc_lines = []  # Store document content in a list
    
    # Basic information
    doc_lines.extend([
        "# RT-Thread Distribution Package\n",
        "\n## Basic Information\n\n",
        f"- Project Name: {project_name}\n",
        f"- Generation Time: {time.strftime('%Y-%m-%d %H:%M:%S')}\n",
        f"- BSP: {os.path.basename(BSP_ROOT)}\n",
        "\n## Components\n\n",
        "### Included Components:\n\n"
    ])

    # Add component information
    for comp in sorted(enabled_components):
        path = get_component_path(comp, RTT_ROOT)
        if path:
            doc_lines.append(f"- {comp}\n  - Path: {path}\n")

    # Add configuration information
    doc_lines.extend(["\n## Configuration\n\n"])
    config_file = os.path.join(BSP_ROOT, '.config')
    if os.path.exists(config_file):
        doc_lines.extend([
            "### Main Configuration Items:\n\n```\n"
        ])
        with open(config_file, 'r') as f:
            for line in f:
                if line.startswith('CONFIG_'):
                    doc_lines.append(line)
        doc_lines.append("```\n")
    
    # Add simplified directory structure
    doc_lines.extend(["\n## Directory Structure\n\n```\n"])
    
    # Show only top-level directories
    items = os.listdir(dist_dir)
    items.sort()
    for item in items:
        if item.startswith('.') or item == 'dist':
            continue
        path = os.path.join(dist_dir, item)
        if os.path.isdir(path):
            doc_lines.append(f"├── {item}/\n")
        else:
            doc_lines.append(f"├── {item}\n")
    
    doc_lines.append("```\n")
    
    # Add build instructions
    doc_lines.extend(["""
## Build Instructions

1. Requirements:
   - Python 3.x
   - SCons build tool
   - Appropriate cross-compiler toolchain

2. Build Steps:
   ```bash
   scons
   ```

3. Clean Build:
   ```bash
   scons -c
   ```

## Notes

1. Make sure the toolchain environment variables are properly set
2. To modify configuration, use menuconfig:
   ```bash
   scons --menuconfig
   ```

## License

See `COPYING` file for details.
"""])
    
    # Write documentation
    doc_file = os.path.join(dist_dir, 'dist_readme.md')
    with open(doc_file, 'w', encoding='utf-8') as f:
        f.writelines(doc_lines)
    
    print(f"=> Generated distribution documentation: {doc_file}")

def is_text_file(filepath):
    """Check if a file is a text file"""
    text_extensions = {
        '.h', '.c', '.cpp', '.hpp', '.S', '.s', '.asm',
        '.txt', '.md', '.rst', '.ini', '.conf',
        'Kconfig', 'SConscript', 'SConstruct',
        '.json', '.yml', '.yaml',
        '.cmake', 'CMakeLists.txt',
        '.py', '.sh', '.bat',
        'README', 'LICENSE', 'Makefile'
    }
    
    # Check by extension
    ext = os.path.splitext(filepath)[1].lower()
    if ext in text_extensions or os.path.basename(filepath) in text_extensions:
        return True
        
    # Additional check for files without extension
    if '.' not in os.path.basename(filepath):
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                f.read(1024)  # Try to read as text
            return True
        except:
            return False
            
    return False

def copy_component_dependencies(src_path, dst_base, RTT_ROOT, copied_files=None):
    """Copy component dependencies (text files) from parent directories"""
    if copied_files is None:
        copied_files = set()
        
    # Get relative path from RTT_ROOT
    rel_path = os.path.relpath(src_path, RTT_ROOT)
    parent_path = os.path.dirname(rel_path)
    
    # Process all parent directories until RTT_ROOT
    while parent_path and parent_path != '.':
        src_dir = os.path.join(RTT_ROOT, parent_path)
        
        # Copy all text files in the directory (not recursively)
        for item in os.listdir(src_dir):
            src_file = os.path.join(src_dir, item)
            if os.path.isfile(src_file) and src_file not in copied_files:
                if is_text_file(src_file):
                    dst_file = os.path.join(dst_base, parent_path, item)
                    dst_dir = os.path.dirname(dst_file)
                    
                    if not os.path.exists(dst_dir):
                        os.makedirs(dst_dir)
                        
                    do_copy_file(src_file, dst_file)
                    copied_files.add(src_file)
                    print(f'    => copying {item} from {parent_path}')
        
        parent_path = os.path.dirname(parent_path)
    
    return copied_files

def get_essential_paths():
    """Get essential paths that must be included"""
    return {
        'components/libc/compilers',  # Common compiler support
        'components/drivers/include',        # Driver headers
        'components/drivers/core',         # Driver core
        'components/utilities',              # Utility functions
        'components/mm',                    # Memory management
        'components/legacy/ipc',            # IPC support, not always used, but have no config option for it
    }

def copy_essential_paths(RTT_ROOT, rtt_dir_path, copied_files=None):
    """Copy essential paths and their build files"""
    if copied_files is None:
        copied_files = set()
        
    print('=> copying essential paths')
    for path in get_essential_paths():
        src_path = os.path.join(RTT_ROOT, path)
        if os.path.exists(src_path):
            dst_path = os.path.join(rtt_dir_path, path)
            print(f'    => copying {path}')
            do_copy_folder(src_path, dst_path)
            
            # Copy build files for this path
            copied_files = copy_component_dependencies(src_path, rtt_dir_path, RTT_ROOT, copied_files)
            
    return copied_files

def components_copy_files(RTT_ROOT, rtt_dir_path, config_file):
    """Copy components based on configuration"""
    print('=> components (selective copy)')
    
    # Track copied build files to avoid duplication
    copied_files = set()
    
    # Copy components/SConscript first
    components_sconscript = os.path.join(RTT_ROOT, 'components', 'SConscript')
    if os.path.exists(components_sconscript):
        dst_dir = os.path.join(rtt_dir_path, 'components')
        if not os.path.exists(dst_dir):
            os.makedirs(dst_dir)
        do_copy_file(components_sconscript, os.path.join(dst_dir, 'SConscript'))
        copied_files.add(components_sconscript)
    
    # Copy essential paths first
    copied_files = copy_essential_paths(RTT_ROOT, rtt_dir_path, copied_files)
    
    # Get enabled components
    enabled_components = parse_components_from_config(config_file)
    if not enabled_components:
        print("Warning: No components found in config file")
        return enabled_components
    
    # Copy each enabled component
    for comp_name in enabled_components:
        comp_path = get_component_path(comp_name, RTT_ROOT)
        if comp_path:
            src_path = os.path.join(RTT_ROOT, comp_path)
            dst_path = os.path.join(rtt_dir_path, comp_path)
            
            if os.path.exists(src_path):
                print(f'    => copying {comp_name} from {comp_path}')
                do_copy_folder(src_path, dst_path)
                
                # Copy parent directory build files
                copied_files = copy_component_dependencies(src_path, rtt_dir_path, RTT_ROOT, copied_files)
            else:
                print(f"Warning: Component path not found: {src_path}")
        else:
            print(f"Note: Skipping system feature: {comp_name}")
            
    return enabled_components

def MkDist(program, BSP_ROOT, RTT_ROOT, Env, project_name, project_path):
    print('make distribution....')

    if project_path == None:
        dist_dir = os.path.join(BSP_ROOT, 'dist', project_name)
    else:
        dist_dir = project_path

    rtt_dir_path = os.path.join(dist_dir, 'rt-thread')

    # Copy BSP files
    print('=> %s' % os.path.basename(BSP_ROOT))
    bsp_copy_files(BSP_ROOT, dist_dir)

    # Do BSP special dist handle
    if 'dist_handle' in Env:
        print("=> start dist handle")
        dist_handle = Env['dist_handle']
        dist_handle(BSP_ROOT, dist_dir)

    # Use new component copy function and get list of enabled components
    config_file = os.path.join(BSP_ROOT, '.config')
    enabled_components = components_copy_files(RTT_ROOT, rtt_dir_path, config_file)
    
    # Skip documentation directory
    # Skip examples

    # Copy include directory
    print('=> include')
    do_copy_folder(os.path.join(RTT_ROOT, 'include'), os.path.join(rtt_dir_path, 'include'))

    # Copy all libcpu/ARCH directory
    print('=> libcpu')
    import rtconfig
    do_copy_folder(os.path.join(RTT_ROOT, 'libcpu', rtconfig.ARCH), os.path.join(rtt_dir_path, 'libcpu', rtconfig.ARCH))
    do_copy_file(os.path.join(RTT_ROOT, 'libcpu', 'Kconfig'), os.path.join(rtt_dir_path, 'libcpu', 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'libcpu', 'SConscript'), os.path.join(rtt_dir_path, 'libcpu', 'SConscript'))

    # Copy src directory
    print('=> src')
    do_copy_folder(os.path.join(RTT_ROOT, 'src'), os.path.join(rtt_dir_path, 'src'))

    # Copy tools directory
    print('=> tools')
    do_copy_folder(os.path.join(RTT_ROOT, 'tools'), os.path.join(rtt_dir_path, 'tools'), ignore_patterns('*.pyc'))

    # Copy necessary files
    do_copy_file(os.path.join(RTT_ROOT, 'Kconfig'), os.path.join(rtt_dir_path, 'Kconfig'))
    do_copy_file(os.path.join(RTT_ROOT, 'AUTHORS'), os.path.join(rtt_dir_path, 'AUTHORS'))
    do_copy_file(os.path.join(RTT_ROOT, 'COPYING'), os.path.join(rtt_dir_path, 'COPYING'))
    do_copy_file(os.path.join(RTT_ROOT, 'README.md'), os.path.join(rtt_dir_path, 'README.md'))
    do_copy_file(os.path.join(RTT_ROOT, 'README_zh.md'), os.path.join(rtt_dir_path, 'README_zh.md'))

    print('Update configuration files...')
    bsp_update_sconstruct(dist_dir)
    bsp_update_kconfig(dist_dir)
    bsp_update_kconfig_library(dist_dir)
    bsp_update_kconfig_testcases(dist_dir)

    # Generate documentation
    generate_dist_doc(dist_dir, enabled_components, project_name+'-dist', BSP_ROOT, RTT_ROOT)

    print('dist project successfully!')
