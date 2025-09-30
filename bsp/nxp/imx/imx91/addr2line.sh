#!/bin/bash
aarch64-none-elf-addr2line -e rtthread.elf -a -f $*
