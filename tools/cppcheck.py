# File      : cppcheck.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
#
# Change Logs:
# Date           Author       Notes
# 2023-05-10     dejavudwh    first version

import subprocess
import os
import sys
import argparse

OUTPUT_FILENAME = "ignore_files.txt"

def cppcheck(path):
	print("is reading from the list of files to be ignored...")

	with open(OUTPUT_FILENAME, 'r') as f:
		ignore_files = [line.strip() for line in f.readlines()]

	print("ignore file path: " + ignore_files[0])

	print("In the list of files being read for this PR modification...")

	result = subprocess.run(['git', 'diff', '--name-only', 'HEAD^', 'HEAD', '--diff-filter=ACMR', '--no-renames', '--full-index'], stdout=subprocess.PIPE)
	file_list = result.stdout.decode().strip().split('\n')

	# result = subprocess.run(['realpath'] + file_list, stdout=subprocess.PIPE)
	# file_list_filtered = result.stdout.decode().strip().split('\n')
	# print("modified files:")
	# print(file_list_filtered)
	# file_list_filtered = [file for file in file_list_filtered if file.endswith(('.c', '.cpp', '.cc', '.cxx'))]
	file_list_filtered = [file for file in file_list if file.endswith(('.c', '.cpp', '.cc', '.cxx'))]
	print("modified files include c||cpp|cc|cxx:")
	print(file_list_filtered)

	print("is determining whether this modified file should ignore cppcheck...")
 	
	file_list_filtered = [file for file in file_list_filtered if file not in ignore_files]

	print("files that need to be checked:")
	print(file_list_filtered)

	os.chdir(path)
	print("cd " + path)
	print("start cppcheck execution")
	
	for file in file_list_filtered:
		result = subprocess.run(['cppcheck', '--enable=warning', 'performance', 'portability', '--inline-suppr', '--error-exitcode=1', '--force', file], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
		print(result.stdout.decode())
		if result.stderr:
			sys.exit(1)
  
if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Process a path and find ignore_format.yml files')
	parser.add_argument('path', type=str, help='path to process')
	args = parser.parse_args()
 
	cppcheck(args.path)
 
	os.remove(OUTPUT_FILENAME)