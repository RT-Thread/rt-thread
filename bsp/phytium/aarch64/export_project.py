#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2022, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Email: opensource_embedded@phytium.com.cn
#
#
# Change Logs:
# Date           Author       Notes
# 2022-11-15     zhugengyu    The first version
#

import os
import shutil
import argparse

parser = argparse.ArgumentParser()
parser.description='please enter two parameters <project-name> and <export-path> ...'
parser.add_argument("-n", "--name", help="project name", type=str, default="phytium-a64")
parser.add_argument("-o", "--output", help="export path",  type=str, default="./phytium-a64")
args = parser.parse_args()

print('=== Exporting Phytium BSP for RT-Studio ====')

board_src_path = os.path.abspath(r'../board')
librs_src_path = os.path.abspath(r'../libraries')

board_dst_path = os.path.abspath(r'./board')
librs_dst_path = os.path.abspath(r'./libraries')

print(' Copying BSP board from {} to {}'.format(board_src_path, board_dst_path))
print(' Copying BSP libraries from {} to {}'.format(librs_src_path, librs_dst_path))

if os.path.exists(board_dst_path):
    shutil.rmtree(board_dst_path)

if os.path.exists(librs_dst_path):
    shutil.rmtree(librs_dst_path)

shutil.copytree(board_src_path, board_dst_path)
shutil.copytree(librs_src_path, librs_dst_path)

os.system('scons --dist-ide --project-name={} --project-path={}'.format(args.name, args.output))

if os.path.exists(board_dst_path):
    shutil.rmtree(board_dst_path)

if os.path.exists(librs_dst_path):
    shutil.rmtree(librs_dst_path)