#!/bin/python
# -*- coding: utf-8 -*-
import os, sys, re

with open('rtconfig.h', 'r') as file:
	rtconfig_header = file.read()

if os.getenv('RTT_QEMU_ROOT'):
	RTT_QEMU_ROOT = os.getenv('RTT_QEMU_ROOT')
else:
	RTT_QEMU_ROOT = ""

opt = sys.argv

q_graphic = "-nographic"
q_debug = ""

def is_opt(key, inkey):
	if str("-" + key) == inkey:
		return True
	return False

for i in range(len(opt)):
	if i == 0:
		continue
	inkey = opt[i]

	if is_opt("debug", inkey): q_debug = "-S -s"
	if is_opt("graphic", inkey): q_graphic = ""

mem = int(re.findall(r'#define\s+ARCH_HEAP_SIZE\s+(.+)', rtconfig_header)[0], 16)
mem += int(re.findall(r'#define\s+ARCH_INIT_PAGE_SIZE\s+(.+)', rtconfig_header)[0], 16)
mem = 128 + int(mem / (1024 * 1024))

os.system("""
{}qemu-system-aarch64 \
	-M xlnx-zcu102 \
	-m {} \
	-kernel rtthread.bin \
	{} \
	{} \
	-serial mon:stdio
""".format(RTT_QEMU_ROOT, mem, q_graphic, q_debug))
