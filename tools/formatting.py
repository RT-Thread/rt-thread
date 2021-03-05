#
# File      : formatting.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
# 2021-03-02     Meco Man     The first version
# 2021-03-04     Meco Man     增加统一转换成UTF-8编码格式功能


#本文件会自动对指定路径下的所有文件包括子文件夹的文件（仅针对.c.h）进行扫描
#   1)将源文件编码统一为UTF-8;
#   2)将TAB键替换为空格;
#   3)将每行末尾多余的空格删除，并统一换行符为'\n'; 
#使用时只需要双击本文件，输入要扫描的文件夹路径即可
#不能保证100%全部成功转换为UTF-8，有一些编码特殊或识别不准确会在终端打印信息，需人工转换

#欢迎对本文件的功能继续做出补充，欢迎提交PR

import os
import chardet

#用空格代替TAB键
#这里并不是简单的将TAB替换成4个空格
#空格个数到底是多少需要计算，因为TAB制表本身有自动对齐的功能
def tab2spaces(line):
    list_str = list(line) #字符串打散成列表，放边操作
    i = list_str.count('\t')
    
    while i > 0:
        ptr = list_str.index('\t')
        del list_str[ptr]
        space_need_to_insert = 4 - (ptr%4)
        j = 0
        while j < space_need_to_insert:
            list_str.insert(ptr,' ')
            j = j+1
        
        i = i-1

    line = ''.join(list_str) #列表恢复成字符串
    return line

#删除每行末尾多余的空格 统一使用\n作为结尾
def formattail(line):
    line = line.rstrip()
    line = line + '\n'
    return line

#对单个文件进行格式整理
def format_codes(filename):
    try:
        file=open(filename,'r',encoding = 'utf-8')
        file_temp=open('temp','w',encoding = 'utf-8')
        for line in file:
            line = tab2spaces(line)
            line = formattail(line)
            file_temp.write(line)
        file_temp.close()
        file.close()
        os.remove(filename)
        os.rename('temp',filename)

def get_encode_info(file):
    with open(file, 'rb') as f:
        code = chardet.detect(f.read())['encoding']       
        #charde库有一定几率对当前文件的编码识别不准确        
        if code == 'EUC-JP': #容易将含着少量中文的英文字符文档识别为日语编码格式
            code = 'GB2312'
        elif code == 'ISO-8859-1': #部分文件GB2312码会被识别成ISO-8859-1
            code = 'GB2312'

        if not (code == 'ascii' or code == 'utf-8' or code == 'GB2312' #编码识别正确
                or code == 'Windows-1252'): # Windows-1252 是由于意法半导体是法国企业's的'是法语的'导致的
            if code != None:
                print('未处理，需人工确认：'+code+':'+file) #需要人工确认
                code = None

        return code

#将单个文件转为UTF-8编码
def conver_to_utf_8 (path):
    try: 
        info = get_encode_info(path)
        if info == None:
            return 0 #0 失败

        file=open(path,'rb+')
        data = file.read()
        string = data.decode(info)
        utf = string.encode('utf-8')
        file.seek(0)
        file.write(utf)
        file.close()
        return 1 #1成功
    except UnicodeDecodeError:
        print("UnicodeDecodeError未处理，需人工确认"+path)
        return 0
    except UnicodeEncodeError:
        print("UnicodeEncodeError未处理，需人工确认"+path)
        return 0

# 递归扫描目录下的所有文件
def traversalallfile(path):
    filelist=os.listdir(path)
    for file in filelist:
        filepath=os.path.join(path,file)
        if os.path.isdir(filepath):
            traversalallfile(filepath)
        elif os.path.isfile(filepath):
            if filepath.endswith(".c") == True or filepath.endswith(".h") == True: #只处理.c和.h文件
                if conver_to_utf_8(filepath) == 1: #先把这个文件转为UTF-8编码,1成功
                    format_codes(filepath) #再对这个文件进行格式整理

def formatfiles():
    workpath = input('enter work path: ')
    traversalallfile(workpath)

if __name__ == '__main__':
    formatfiles()
