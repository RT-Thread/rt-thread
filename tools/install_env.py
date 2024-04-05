#! /usr/bin/env python
#coding=utf-8

#
# File      : env.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2024, RT-Thread Development Team
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
# 2024-04-05     Bernard      Add copyright information
#

import os
import sys
import platform
import shutil
import zipfile

PKG_URL = 'https://github.com/RT-Thread/packages.git'
SDK_URL = 'https://github.com/RT-Thread/sdk.git'
ENV_URL = 'https://github.com/RT-Thread/env.git'

def help_info():
    print("**********************************************************************************\n"
          "* Help infomation:\n"
          "* Git tool install step.\n"
          "* If your system is linux, you can use command below to install git.\n"
          "* $ sudo yum install git\n"
          "* $ sudo apt-get install git\n"
          "* If your system is windows, you should download git software(msysGit).\n"
          "* Download path: http://git-scm.com/download/win\n"
          "* After you install it, be sure to add the git command execution PATH \n"
          "* to your system PATH.\n"
          "* Usually, git command PATH is $YOUR_INSTALL_DIR\\Git\\bin\n"
          "* If your system is OSX, please download git and install it.\n"
          "* Download path:  http://git-scm.com/download/mac\n"
          "**********************************************************************************\n")

def touch_env():
    if sys.platform != 'win32':
        home_dir = os.environ['HOME']
    else:
        home_dir = os.environ['USERPROFILE']

    pkg_url = os.getenv('RTT_PACKAGE_URL') or PKG_URL
    sdk_url = os.getenv('RTT_SDK_URL') or SDK_URL
    env_url = os.getenv('RTT_ENV_URL') or ENV_URL
    if len(sys.argv) == 2 and sys.argv[1] == '--gitee':
        # "Install RT-Thread Environment from Gitee"
        sdk_url = 'https://gitee.com/RT-Thread-Mirror/sdk.git'
        pkg_url = 'https://gitee.com/RT-Thread-Mirror/packages.git'
        env_url = 'https://gitee.com/RT-Thread-Mirror/env.git'

    # make .env and other directories
    env_dir  = os.path.join(home_dir, '.env')
    if not os.path.exists(env_dir):
        os.mkdir(env_dir)
        os.mkdir(os.path.join(env_dir, 'local_pkgs'))
        os.mkdir(os.path.join(env_dir, 'packages'))
        os.mkdir(os.path.join(env_dir, 'tools'))
        kconfig = open(os.path.join(env_dir, 'packages', 'Kconfig'), 'w')
        kconfig.close()

    # git clone packages
    if not os.path.exists(os.path.join(env_dir, 'packages', 'packages')):
        try:
            ret = os.system('git clone %s %s' % (pkg_url, os.path.join(env_dir, 'packages', 'packages')))
            if ret != 0:
                shutil.rmtree(os.path.join(env_dir, 'packages', 'packages'))
                print("********************************************************************************\n"
                      "* Warnning:\n"
                      "* Run command error for \"git clone https://github.com/RT-Thread/packages.git\".\n"
                      "* This error may have been caused by not found a git tool or network error.\n"
                      "* If the git tool is not installed, install the git tool first.\n"
                      "* If the git utility is installed, check whether the git command is added to \n"
                      "* the system PATH.\n"
                      "* This error may cause the RT-Thread packages to not work properly.\n"
                      "********************************************************************************\n")
                help_info()
            else:
                kconfig = open(os.path.join(env_dir, 'packages', 'Kconfig'), 'w')
                kconfig.write('source "$PKGS_DIR/packages/Kconfig"')
                kconfig.close()
        except:
            print("**********************************************************************************\n"
                  "* Warnning:\n"
                  "* Run command error for \"git clone https://github.com/RT-Thread/packages.git\". \n"
                  "* This error may have been caused by not found a git tool or git tool not in \n"
                  "* the system PATH. \n"
                  "* This error may cause the RT-Thread packages to not work properly. \n"
                  "**********************************************************************************\n")
            help_info()

    # git clone env scripts
    if not os.path.exists(os.path.join(env_dir, 'tools', 'scripts')):
        try:
            ret = os.system('git clone %s %s' % (env_url, os.path.join(env_dir, 'tools', 'scripts')))
            if ret != 0:
                shutil.rmtree(os.path.join(env_dir, 'tools', 'scripts'))
                print("********************************************************************************\n"
                      "* Warnning:\n"
                      "* Run command error for \"git clone https://github.com/RT-Thread/env.git\".\n"
                      "* This error may have been caused by not found a git tool or network error.\n"
                      "* If the git tool is not installed, install the git tool first.\n"
                      "* If the git utility is installed, check whether the git command is added \n"
                      "* to the system PATH.\n"
                      "* This error may cause script tools to fail to work properly.\n"
                      "********************************************************************************\n")
                help_info()
        except:
            print("********************************************************************************\n"
                  "* Warnning:\n"
                  "* Run command error for \"git clone https://github.com/RT-Thread/env.git\". \n"
                  "* This error may have been caused by not found a git tool or git tool not in \n"
                  "* the system PATH. \n"
                  "* This error may cause script tools to fail to work properly. \n"
                  "********************************************************************************\n")
            help_info()

    # git clone sdk
    if not os.path.exists(os.path.join(env_dir, 'packages', 'sdk')):
        try:
            ret = os.system('git clone %s %s' % (sdk_url, os.path.join(env_dir, 'packages', 'sdk')))
            if ret != 0:
                shutil.rmtree(os.path.join(env_dir, 'packages', 'sdk'))
                print("********************************************************************************\n"
                      "* Warnning:\n"
                      "* Run command error for \"git clone https://github.com/RT-Thread/sdk.git\".\n"
                      "* This error may have been caused by not found a git tool or network error.\n"
                      "* If the git tool is not installed, install the git tool first.\n"
                      "* If the git utility is installed, check whether the git command is added \n"
                      "* to the system PATH.\n"
                      "* This error may cause the RT-Thread SDK to not work properly.\n"
                      "********************************************************************************\n")
                help_info()
        except:
            print("********************************************************************************\n"
                  "* Warnning:\n"
                  "* Run command error for \"https://github.com/RT-Thread/sdk.git\".\n"
                  "* This error may have been caused by not found a git tool or git tool not in \n"
                  "* the system PATH. \n"
                  "* This error may cause the RT-Thread SDK to not work properly. \n"
                  "********************************************************************************\n")
            help_info()

    # try to create an empty .config file
    if not os.path.exists(os.path.join(env_dir, 'tools', '.config')):
        kconfig = open(os.path.join(env_dir, 'tools', '.config'), 'w')
        kconfig.close()

    # copy env.sh or env.ps1, Kconfig
    shutil.copy(os.path.join(env_dir, 'tools', 'scripts', 'Kconfig'), os.path.join(home_dir, '.env', 'tools'))
    if sys.platform != 'win32':
        shutil.copy(os.path.join(env_dir, 'tools', 'scripts', 'env.sh'), os.path.join(home_dir, '.env', 'env.sh'))
    else:
        shutil.copy(os.path.join(env_dir, 'tools', 'scripts', 'env.ps1'), os.path.join(home_dir, '.env', 'env.ps1'))
        # unzip kconfig-mconf.zip
        zip_file = os.path.join(env_dir, 'tools', 'scripts', 'kconfig-mconf.zip')
        if os.path.exists(zip_file):
            zip_file_dir = os.path.join(env_dir, 'tools', 'bin')
            if os.path.exists(zip_file_dir):
                shutil.rmtree(zip_file_dir)
            zip_file_obj = zipfile.ZipFile(zip_file, 'r')
            for file in zip_file_obj.namelist():
                zip_file_obj.extract(file, zip_file_dir)
            zip_file_obj.close()

def main():
    print("Install RT-Thread Environment")

    touch_env()

    return

if __name__ == "__main__":
    main()
