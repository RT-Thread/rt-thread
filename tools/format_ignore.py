# File      : format_ignore.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
#
# Change Logs:
# Date           Author       Notes
# 2023-05-10     dejavudwh    first version

import os
import yaml
import argparse

IGNORE_FORMAT_FILENAME = ".ignore_format.yml"
OUTPUT_FILENAME = "ignore_files.txt"

def add_file(path):
	with open(OUTPUT_FILENAME, 'a') as output_file:
		output_file.write(path + '\n')

def add_dir(path):
	for root, dirs, files in os.walk(path):
		for file in files:
			abs_file_path = os.path.abspath(os.path.join(root, file))
			with open(OUTPUT_FILENAME, 'a') as output_file:
				output_file.write(abs_file_path + '\n')

def process_ignore_format_file(ignore_file_path, root_path):
	with open(ignore_file_path, 'r') as f:
		ignore_data = yaml.safe_load(f)
		for path in ignore_data.get('dir_path', []):
			abs_path = os.path.abspath(os.path.join(root_path, path))
			if os.path.isfile(abs_path):
				add_file(abs_path)
			elif os.path.isdir(abs_path):
				add_dir(abs_path)

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Process a path and find ignore_format.yml files')
	parser.add_argument('path', type=str, help='path to process')
	args = parser.parse_args()

	for root, dirs, files in os.walk(args.path):
		if IGNORE_FORMAT_FILENAME in files:
			ignore_file_path = os.path.abspath(os.path.join(root, IGNORE_FORMAT_FILENAME))
			process_ignore_format_file(ignore_file_path, args.path)
