#
# File      : upgrade.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2021, RT-Thread Development Team
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
# 2021-10-11     Meco Man     First version
#

# 本文件用于在HAL库更新之后
# 1.对gcc的汇编启动文件中main替换为entry函数
# 2.将启动文件heap降为0(Keil IAR)
# 3.将GCC的堆大小扩展到0x400，与Keil IAR保持一致


#使用方法：运行脚本，将bsp/stm32的绝对路径传给脚本即可，如：C:\Users\92036\Desktop\rt-thread\bsp\stm32

#特别说明：此脚本是借用RTT原BSP中STM32的，对ST的开源表示非常感谢！！！

import os
import re

#将'bl main' 替换为 'bl entry'
def main2entry(path):
    oldline = ''
    newline = ''

    for root, dirs, files in os.walk(path): #递归扫描里面的所有文件
        for file in files:
            if os.path.splitext(file)[1] == '.s': #找.s文件
                file_path = os.path.join(root,file)
                flag_need_replace = False
                with open(file_path,'r+',) as f:
                    while True:
                        line = f.readline()
                        if line == '':
                            break
                        elif ('bl' in line) and ('main' in line): #发现'bl main'
                            oldline = line # bl main
                            newline = line.replace('main', 'entry') #将main替换为entry，形成新的字符串
                            flag_need_replace = True #标记该文件需要做entry替换
                            break

                    if (flag_need_replace == True): #若该文件需要将main替换为entry
                        f.seek(0)
                        content = f.read()
                        f.seek(0)
                        f.truncate()
                        newcontent = content.replace(oldline, newline)
                        f.write(newcontent)

#将启动文件的heap降为0
def heap2zero(path):
    oldline = ''
    newline = ''
    for root, dirs, files in os.walk(path): #递归扫描里面的所有文件
        for file in files:
            file_path = os.path.join(root,file)
            if os.path.splitext(file)[1] == '.s': #找.s文件
                with open(file_path,'r+',) as f:
                    flag_need_replace = False
                    while True:
                        line = f.readline()
                        if line == '':
                            break

                        re_result = re.match('\s*Heap_Size\s+EQU\s+0[xX][0-9a-fA-F]+', line) #MDK的表示方法
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

            elif os.path.splitext(file)[1] == '.icf': #找.icf文件(IAR)
                with open(file_path,'r+',) as f:
                    flag_need_replace = False
                    while True:
                        line = f.readline()
                        if line == '':
                            break

                        re_result = re.match('\s*define\s+symbol\s+__ICFEDIT_size_heap__\s*=\s*0[xX][0-9a-fA-F]+', line) #IAR的表示方法
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

            elif os.path.splitext(file)[1] == '.lds': #找.lds文件(GCC)
                with open(file_path,'r+',) as f:
                    flag_need_replace = False
                    while True:
                        line = f.readline()
                        if line == '':
                            break

                        re_result = re.match('\s*_system_stack_size\s*=\s*0[xX][0-9a-fA-F]+', line) #GCC的表示方法, 将默认的栈大小增加到0x400
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

folder_path = input('please input path:')
main2entry(folder_path)
heap2zero(folder_path)
