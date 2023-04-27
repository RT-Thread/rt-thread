#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2022, RT-Thread Development Team
#
# SPDX-License-Identifier: GPL-2.0
#
# Change Logs:
# Date           Author       Notes
# 2022-02-1      Bernard      The first version
#
import os
import sys
import shutil
import platform
import requests
import time
import zipfile
class CI:
    def downloadFile(self, name, url):
        headers = {'Proxy-Connection':'keep-alive'}
        r = requests.get(url, stream=True, headers=headers)
        length = float(r.headers['content-length'])
        f = open(name, 'wb')
        count = 0
        count_tmp = 0
        time1 = time.time()
        for chunk in r.iter_content(chunk_size = 512):
            if chunk:
                f.write(chunk)
                count += len(chunk)
                if time.time() - time1 > 2:
                    p = count / length * 100
                    speed = (count - count_tmp) / 1024 / 1024 / 2
                    count_tmp = count
                    print(name + ': ' + '{:.2f}'.format(p) + '%')
                    time1 = time.time()
        print(name + ': 100%')
        f.close()
    def extractZipFile(self, zfile, folder):
        # self.delTree(folder)
        if not os.path.exists(folder):
            os.makedirs(folder)
        if platform.system() == 'Windows':
            zip_file = zipfile.ZipFile(zfile)
            zip_list = zip_file.namelist()
            for item in zip_list:
                print(item)
                zip_file.extract(item, folder)
            zip_file.close()
        elif platform.system() == 'Linux':
            if zfile.endswith('tar.gz'):
                os.system('tar zxvf %s -C %s' % (zfile, folder))
            elif zfile.endswith('tar.bz2'):
                os.system('tar jxvf %s -C %s' % (zfile, folder))
            elif zfile.endswith('.zip'):
                os.system('unzip %s -d %s' % (zfile, folder))
        return
    def zipFolder(self, folder, zfile):
        zip_filename = os.path.join(folder)
        zip = zipfile.ZipFile(zfile, 'w', compression=zipfile.ZIP_BZIP2)
        pre_len = len(os.path.dirname(folder))
        for parent, dirnames, filenames in os.walk(folder):
            for filename in filenames:
                pathfile = os.path.join(parent, filename)
                arcname = pathfile[pre_len:].strip(os.path.sep)
                zip.write(pathfile, arcname)
        zip.close()
        return
    def touchDir(self, d):
        if not os.path.exists(d):
            os.makedirs(d)
    def gitUpdate(self, url, folder, branch = 'master'):
        cwd = os.getcwd()
        if os.path.exists(folder):
            os.chdir(folder)
            os.system('git pull origin')
            if branch != 'master':
                os.system('git checkout -b %s origin/%s' % (branch, branch))
            os.system('git submodule init')
            os.system('git submodule update')
        else:
            os.system('git clone %s %s' % (url, folder))
            os.chdir(folder)
            os.system('git submodule init')
            os.system('git submodule update')
        os.chdir(cwd)
    def installEnv(self, folder):
        env_path = folder
        cwd = os.getcwd()
        os.chdir(env_path)
        self.touchDir(os.path.join(env_path, 'local_pkgs'))
        self.touchDir(os.path.join(env_path, 'packages'))
        self.touchDir(os.path.join(env_path, 'tools'))
        self.gitUpdate('https://gitee.com/RT-Thread-Mirror/env.git', 'tools/script')
        self.gitUpdate('https://gitee.com/RT-Thread-Mirror/packages.git', 'packages/packages')
        kconfig = open(os.path.join(env_path, 'packages', 'Kconfig'), 'w')
        kconfig.write('source "$PKGS_DIR/packages/Kconfig"')
        kconfig.close()
        os.chdir(cwd)
        return
    def pkgsUpdate(self, env_folder):
        self.touchDir(env_folder)
        self.installEnv(env_folder)
        os.environ['PKGS_DIR'] = env_folder
        os.system('python %s package --update' % (os.path.join(env_folder, 'tools', 'script', 'env.py')))
        return
    def delTree(self, folder):
        if os.path.exists(folder):
            shutil.rmtree(folder)
    def delFile(self, file):
        if os.path.exists(file):
            os.remove(file)
    def appendFile(self, srcFile, otherFile):
        f = open(otherFile, 'r')
        s = f.read()
        f.close()
        f = open(srcFile, 'a')
        f.write(s)
        f.close()
    def copyTree(self, srcTree, dstTree):
        if os.path.exists(dstTree):
            shutil.rmtree(dstTree)
        shutil.copytree(srcTree, dstTree)
    def run(self, cmds):
        cwd = os.getcwd()
        cmds = cmds.split('\n')
        for item in cmds:
            item = item.lstrip()
            if item == '':
                continue
            if item[0] == '-':
                os.system(item[1:].lstrip())
        # keep current directory
        os.chdir(cwd)
        return
if __name__ == '__main__':
    ci = CI()
    env_folder = os.path.abspath(os.path.join('.', 'env_test'))
    # ci.pkgsUpdate(env_folder)
    cmds = '''
        # test
        - dir
        - dir tools
    '''
    ci.run(cmds)