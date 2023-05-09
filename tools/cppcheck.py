# File      : cppcheck.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
#
# Change Logs:
# Date           Author       Notes
# 2023-05-10     dejavudwh    first version

import subprocess
import os

OUTPUT_FILENAME = "ignore_files.txt"

with open(OUTPUT_FILENAME, 'r') as f:
    ignore_files = [line.strip() for line in f.readlines()]

result = subprocess.run(['git', 'diff', '--name-only', '--diff-filter=ACMR', '--no-renames', '--full-index'], stdout=subprocess.PIPE)
file_list = result.stdout.decode().strip().split('\n')

result = subprocess.run(['realpath'] + file_list, stdout=subprocess.PIPE)
file_list_filtered = result.stdout.decode().strip().split('\n')
file_list_filtered = [file for file in file_list_filtered if file.endswith(('.c', '.cpp', '.cc', '.cxx'))]

file_list_filtered = [file for file in file_list_filtered if file not in ignore_files]

for file in file_list_filtered:
    subprocess.run(['cppcheck', '--enable=warning', 'performance', 'portability', '--inline-suppr', '--error-exitcode=1', '--force', file])

os.remove(OUTPUT_FILENAME)