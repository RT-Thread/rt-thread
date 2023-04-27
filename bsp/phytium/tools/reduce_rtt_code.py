#!/usr/bin/env python3
# Copyright : (C) 2022 Phytium Information Technology, Inc. 
# All Rights Reserved.
 
# This program is OPEN SOURCE software: you can redistribute it and/or modify it  
# under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
# either version 1.0 of the License, or (at your option) any later version. 
 
# This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the Phytium Public License for more details. 
 
# FilePath: reduce_rtt_cde.py
# Date: 2021-10-14 08:19:30
# LastEditTime: 2022-02-18 09:26:24
# Description:  This files is for install phytiunm standalone sdk

# Modify History: 
#  Ver   Who        Date         Changes
# ----- ------     --------    --------------------------------------
# 1.0   zhugengyu  2023/1/12   init commit

#
# ./reduce_rtt_code.py -i=/mnt/d/proj/rt-thread/rt-thread-base -o=/mnt/d/proj/rt-thread/rt-thread-lite
#


import sys
import os
import argparse
import shutil

src_path = []
dst_path = []

dry_run = False #True

def append_path(path):
    src_path.append(os.path.abspath(path))

parser = argparse.ArgumentParser()
parser.description='please enter two parameters <input-PATH> and <export-PATH> ...'
parser.add_argument("-i", "--input", help="input PATH of RTT", type=str, default="./rt-thread")
parser.add_argument("-o", "--output", help="export PATH for RTT",  type=str, default="./rt-thread-lite")
args = parser.parse_args()

rtt_src_dir = os.path.abspath(args.input)
rtt_dst_dir = os.path.abspath(args.output)

os.chdir(rtt_src_dir) # change to rt-thread folder

# append path and files need to reserve

## root
append_path(r'./.git')
append_path(r'./.gitee')
append_path(r'./.github')
append_path(r'./.gitattributes')
append_path(r'./.gitignore')
append_path(r'./ChangeLog.md')
append_path(r'./Kconfig')
append_path(r'./LICENSE')
append_path(r'./README.md')
append_path(r'./README_de.md')
append_path(r'./README_es.md')
append_path(r'./README_zh.md')

## bsp
append_path(r'./bsp/phytium')

## components
append_path(r'./components')

## examples
append_path(r'./examples')

## include
append_path(r'./include')

## libcpu
append_path(r'./libcpu/Kconfig')
append_path(r'./libcpu/SConscript')
append_path(r'./libcpu/aarch64')
append_path(r'./libcpu/arm')

## src
append_path(r'./src')

## tools
append_path(r'./tools')

print('Source path ======')
for path in src_path:
    print(path)
print('====================')

for path in src_path:
    dst_path.append(path.replace(rtt_src_dir, rtt_dst_dir))

print('Destination path ======')
for path in dst_path:
    print(path)
print('====================')

print('Total {} items'.format(len(src_path)))
print('Current dir: {}'.format(os.getcwd()))

if dry_run:
    for i in range(len(src_path)):
        print('copy {} to {}'.format(src_path[i], dst_path[i]))           
else:
    root_dir = r'.' + rtt_dst_dir
    if os.path.exists(root_dir):
        shutil.rmtree(root_dir)

    for i in range(len(src_path)):
        if os.path.exists(dst_path[i]):
            continue

        # do real copy !!!!
        if os.path.isdir(src_path[i]):
            shutil.copytree(src_path[i], dst_path[i])
        else:
            file_dir = os.path.dirname(dst_path[i])
            if not os.path.exists(file_dir):
                os.mkdir(file_dir)
            shutil.copyfile(src_path[i], dst_path[i])


    os.chdir(rtt_dst_dir) # change to rt-thread folder
