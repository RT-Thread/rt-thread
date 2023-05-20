# Copyright (c) 2006-2022, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2021-10-11     Meco Man     First version

# STM32 startup assembly language file:
# 1.replace main to entry (GCC)
# 2.reduce the heap size as 0x000 (Keil IAR)
# 3.extend the GCC stack size as 0x400, which is the same as Keil and IAR startup files.

import os
import re

# replace 'bl main' to 'bl entry'
def stm32update_main2entry(path):
    oldline = ''
    newline = ''

    for root, dirs, files in os.walk(path):
        for file in files:
            if os.path.splitext(file)[1] == '.s': # find .s files (Keil MDK)
                file_path = os.path.join(root,file)
                flag_need_replace = False
                with open(file_path,'r+',) as f:
                    while True:
                        line = f.readline()
                        if line == '':
                            break
                        elif ('bl' in line) and ('main' in line): # find 'bl main'
                            oldline = line # bl main
                            newline = line.replace('main', 'entry') # use 'entry' to replace 'main'
                            flag_need_replace = True # mark that need to be replaced
                            break

                    if (flag_need_replace == True): # use 'entry' to replace 'main'
                        f.seek(0)
                        content = f.read()
                        f.seek(0)
                        f.truncate()
                        newcontent = content.replace(oldline, newline)
                        f.write(newcontent)

#reduce the heap size as 0x000
def stm32update_heap2zero(path):
    oldline = ''
    newline = ''
    for root, dirs, files in os.walk(path):
        for file in files:
            file_path = os.path.join(root,file)
            if os.path.splitext(file)[1] == '.s': # find .s files (Keil MDK)
                with open(file_path,'r+',) as f:
                    flag_need_replace = False
                    while True:
                        line = f.readline()
                        if line == '':
                            break

                        re_result = re.match('\s*Heap_Size\s+EQU\s+0[xX][0-9a-fA-F]+', line)
                        if re_result != None:
                            oldline = line
                            newline = re.sub('0[xX][0-9a-fA-F]+','0x00000000', oldline)
                            flag_need_replace = True
                            break

                    if flag_need_replace == True:
                        f.seek(0)
                        content = f.read()
                        f.seek(0)
                        f.truncate()
                        newcontent = content.replace(oldline, newline)
                        f.write(newcontent)

            elif os.path.splitext(file)[1] == '.icf': # find .icf files (IAR)
                with open(file_path,'r+',) as f:
                    flag_need_replace = False
                    while True:
                        line = f.readline()
                        if line == '':
                            break

                        re_result = re.match('\s*define\s+symbol\s+__ICFEDIT_size_heap__\s*=\s*0[xX][0-9a-fA-F]+', line)
                        if re_result != None:
                            oldline = line
                            newline = re.sub('0[xX][0-9a-fA-F]+','0x000', oldline)
                            flag_need_replace = True
                            break

                    if flag_need_replace == True:
                        f.seek(0)
                        content = f.read()
                        f.seek(0)
                        f.truncate()
                        newcontent = content.replace(oldline, newline)
                        f.write(newcontent)

            elif os.path.splitext(file)[1] == '.lds': # find .lds files (GCC)
                with open(file_path,'r+',) as f:
                    flag_need_replace = False
                    while True:
                        line = f.readline()
                        if line == '':
                            break

                        re_result = re.match('\s*_system_stack_size\s*=\s*0[xX][0-9a-fA-F]+', line)
                        if re_result != None:
                            oldline = line
                            newline = re.sub('0[xX][0-9a-fA-F]+','0x400', oldline)
                            flag_need_replace = True
                            break

                    if flag_need_replace == True:
                        f.seek(0)
                        content = f.read()
                        f.seek(0)
                        f.truncate()
                        newcontent = content.replace(oldline, newline)
                        f.write(newcontent)


def stm32_update(path):
    stm32update_main2entry(path)
    stm32update_heap2zero(path)
