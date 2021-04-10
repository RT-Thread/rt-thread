# -*- coding: UTF-8 -*- 

# File      : release.py
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
# 
# Change Logs:
# Date           Author       Notes
# 2021-04-10     Meco Man     The first version

# 本文件主要用于在RT-Thread版本发布之前，对仓库版本截止年份进行提升以及整理文件格式
# 直接运行本文件即可 python3 release.py
# 依赖软件包，请提前安装: chardet

# 本文件会自动对指定路径下的所有文件包括子文件夹的文件（.c/.h/.cpp）进行扫描
# 仅针对RT-Thread所属且编码为UTF-8的文件进行为进行格式化处理
# 判断机制为文件前10行是否带有RT-Thread或Real-Thread字样
# 格式化整理为：
#   1)将TAB键替换为空格
#   2)将每行末尾多余的空格删除，并统一换行符为'\n'
#   3)将RT-Thread版权信息的截至年份修改至今年
#   4)将上海睿赛德版权信息的截至年份修改至今年

# 欢迎对本文件的功能继续做出补充，欢迎提交PR

import os
import re
import chardet
import datetime

# 用空格代替TAB键
# 这里并不是简单的将TAB替换成4个空格
# 空格个数到底是多少需要计算，因为TAB制表本身有自动对齐的功能
def tab2spaces(line):
    list_str = list(line)  # 字符串打散成列表，方便操作
    i = list_str.count('\t')

    while i > 0:
        ptr = list_str.index('\t')
        del list_str[ptr]
        space_need_to_insert = 4 - (ptr % 4)
        j = 0
        while j < space_need_to_insert:
            list_str.insert(ptr, ' ')
            j = j + 1

        i = i - 1

    line = ''.join(list_str)  # 列表恢复成字符串
    return line

# 删除每行末尾多余的空格 统一使用\n作为结尾
def formattail(line):
    line = line.rstrip()
    line = line + '\n'
    return line

#搜索RT-Thread版权信息的截至年份修改至今年
def change_rtthread_copyright_year(line):
    search_result = re.search('200[0-9]-20[0-9][0-9]', line, flags=0) # 搜索200x-20xx字样
    if search_result != None:
        if re.search('RT-Thread', line, flags=0) != None: # 同时可以在本行中搜索到‘RT-Thread’字样
            end = search_result.end()
            str_year = str(datetime.datetime.now().year)
            line = line.replace(line[end-4:end], str_year)# 将20xx替换为今年
    return line

#搜索Real-Thread睿赛德版权信息的截至年份修改至今年
def change_realthread_copyright_year(line):
    search_result = re.search('20[0-9][0-9]-20[0-9][0-9]', line, flags=0) # 搜索20xx-20xx字样
    if search_result != None:
        if re.search('Real-Thread', line, flags=0) != None: # 同时可以在本行中搜索到‘Real-Thread’字样
            end = search_result.end()
            str_year = str(datetime.datetime.now().year)
            line = line.replace(line[end-4:end], str_year)# 将20xx替换为今年
    return line

# 对单个文件进行格式整理
def format_codes(filename):
    try:
        file = open(filename, 'r', encoding='utf-8')
        file_temp = open('temp', 'w', encoding='utf-8')
        line_num = 0
        for line in file:
            line = tab2spaces(line)
            line = formattail(line)

            line_num = line_num + 1
            if line_num < 20: #文件前20行对版权头注释进行扫描，找到截至年份并修改至今年
                line = change_rtthread_copyright_year(line)
                line = change_realthread_copyright_year(line)

            file_temp.write(line)
        file_temp.close()
        file.close()
        os.remove(filename)
        os.rename('temp', filename)
    except UnicodeDecodeError:
        print("解码失败，该文件处理失败" + filename)
        file_temp.close()
        file.close()
    except UnicodeEncodeError:
        print("编码失败，该文件处理失败" + filename)
        file_temp.close()
        file.close()


def is_rtthread_code(filename):
    try:
        res = False
        file = open(filename, 'r', encoding='utf-8')
        line_num = 0
        for line in file:
            if re.search('RT-Thread', line, flags=0) != None or re.search('Real-Thread', line, flags=0) != None: # 行中搜索到‘RT-Thread’或者'Real-Thread'字样
                res = True
                break

            line_num = line_num + 1
            if line_num > 10:
                res = False
                break

        file.close()
        return res
    except UnicodeDecodeError:
        print("解码失败，该文件处理失败" + filename)
        file.close()
        return False
    except UnicodeEncodeError:
        print("编码失败，该文件处理失败" + filename)
        file.close()
        return False


def get_encode_info(file):
    encoding = None
    with open(file, 'rb') as f:
        encode_info = chardet.detect(f.read())
        encoding = encode_info['encoding']

    return encoding


# 将单个文件转为UTF-8编码
def is_utf_8(path):
    encoding = get_encode_info(path)
    if encoding == None:
        return False  # 转换失败

    if encoding == 'utf-8' or encoding == 'ascii':  # 若检测到编码为UTF-8则直接返回成功
        return True


# 递归扫描目录下的所有文件
def traversalallfile(path):
    filelist = os.listdir(path)
    for file in filelist:
        filepath = os.path.join(path, file)
        if os.path.isdir(filepath):
            traversalallfile(filepath)
        elif os.path.isfile(filepath):
            if filepath.endswith(".c") == True or \
               filepath.endswith(".cpp") == True or \
               filepath.endswith(".h") == True:
                # 若为.c/.h/.cpp文件，则开始进行处理
                if is_utf_8(filepath) == True:  # 判断是否为UTF-8编码，仅处理UTF-8格式文件
                    if is_rtthread_code(filepath) == True: # 判断该文件的版权是否是RT-Thread
                        format_codes(filepath)  # 再对这个文件进行格式整理


def formatfiles():
    workpath = input('请输入扫描路径: ')
    print('扫描时间较长，请耐心等待...')
    traversalallfile(workpath)


if __name__ == '__main__':
    formatfiles()
