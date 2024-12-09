#! /usr/bin/env python
# coding=utf-8
#
# Copyright (c) 2024, RT-Thread Development Team
#
# SPDX-License-Identifier: GPL-2.0
#
# Change Logs:
# Date           Author       Notes
# 2024-04-20     Bernard      the first version

import os
import json
import platform
import re
import sys
import shutil
import hashlib
import operator


def GetEnvPath():
    if "ENV_ROOT" in os.environ:
        return os.environ["ENV_ROOT"]

    if platform.system() == 'Windows':
        env_root = os.path.join(os.environ['USERPROFILE'], '.env')
    else:
        env_root = os.path.join(os.environ['HOME'], '.env')

    return env_root


def GetPkgPath():
    if "PKGS_DIR" in os.environ:
        return os.environ["PKGS_DIR"]
    elif "PKGS_ROOT" in os.environ:
        return os.environ["PKGS_ROOT"]
    elif GetEnvPath():
        return os.path.join(GetEnvPath(), "packages")
    else:
        return None

def GetSDKPackagePath():
    env = GetEnvPath()

    if env:
        return os.path.join(env, "tools", "scripts", "packages")

    return None

# get SDK path based on name
# for example, GetSDKPath('arm-none-eabi') = '.env/tools/scripts/packages/arm-none-eabi-gcc-v10.3'
def GetSDKPath(name):
    sdk_pkgs = GetSDKPackagePath()

    if sdk_pkgs:
        # read packages.json under env/tools/scripts/packages
        with open(os.path.join(sdk_pkgs, 'pkgs.json'), 'r', encoding='utf-8') as f:
            # packages_json = f.read()
            packages = json.load(f)

            for item in packages:
                package_path = os.path.join(GetEnvPath(), 'packages', item['path'], 'package.json')
                # read package['path']/package.json under env/packages
                with open(package_path, 'r', encoding='utf-8') as f:
                    # package_json = f.read()
                    package = json.load(f)

                    if package['name'] == name:
                        return os.path.join(sdk_pkgs, package['name'] + '-' + item['ver'])

    # not found named package
    return None

def help_info():
    print(
        "**********************************************************************************\n"
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
        "**********************************************************************************\n"
    )


def touch_env(use_gitee=False):
    if sys.platform != 'win32':
        home_dir = os.environ['HOME']
    else:
        home_dir = os.environ['USERPROFILE']

    if use_gitee:
        # "Install RT-Thread Environment from Gitee"
        sdk_url = 'https://gitee.com/RT-Thread-Mirror/sdk.git'
        pkg_url = 'https://gitee.com/RT-Thread-Mirror/packages.git'
        env_url = 'https://gitee.com/RT-Thread-Mirror/env.git'
    else:
        pkg_url = 'https://github.com/RT-Thread/packages.git'
        sdk_url = 'https://github.com/RT-Thread/sdk.git'
        env_url = 'https://github.com/RT-Thread/env.git'

    pkg_url = os.getenv('RTT_PACKAGE_URL') or pkg_url
    sdk_url = os.getenv('RTT_SDK_URL') or sdk_url
    env_url = os.getenv('RTT_ENV_URL') or env_url

    # make .env and other directories
    env_dir = os.path.join(home_dir, '.env')
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
                print(
                    "********************************************************************************\n"
                    "* Warnning:\n"
                    "* Run command error for \"git clone https://github.com/RT-Thread/packages.git\".\n"
                    "* This error may have been caused by not found a git tool or network error.\n"
                    "* If the git tool is not installed, install the git tool first.\n"
                    "* If the git utility is installed, check whether the git command is added to \n"
                    "* the system PATH.\n"
                    "* This error may cause the RT-Thread packages to not work properly.\n"
                    "********************************************************************************\n"
                )
                help_info()
            else:
                kconfig = open(os.path.join(env_dir, 'packages', 'Kconfig'), 'w')
                kconfig.write('source "$PKGS_DIR/packages/Kconfig"')
                kconfig.close()
        except:
            print(
                "**********************************************************************************\n"
                "* Warnning:\n"
                "* Run command error for \"git clone https://github.com/RT-Thread/packages.git\". \n"
                "* This error may have been caused by not found a git tool or git tool not in \n"
                "* the system PATH. \n"
                "* This error may cause the RT-Thread packages to not work properly. \n"
                "**********************************************************************************\n"
            )
            help_info()

    # git clone env scripts
    if not os.path.exists(os.path.join(env_dir, 'tools', 'scripts')):
        try:
            ret = os.system('git clone %s %s' % (env_url, os.path.join(env_dir, 'tools', 'scripts')))
            if ret != 0:
                shutil.rmtree(os.path.join(env_dir, 'tools', 'scripts'))
                print(
                    "********************************************************************************\n"
                    "* Warnning:\n"
                    "* Run command error for \"git clone https://github.com/RT-Thread/env.git\".\n"
                    "* This error may have been caused by not found a git tool or network error.\n"
                    "* If the git tool is not installed, install the git tool first.\n"
                    "* If the git utility is installed, check whether the git command is added \n"
                    "* to the system PATH.\n"
                    "* This error may cause script tools to fail to work properly.\n"
                    "********************************************************************************\n"
                )
                help_info()
        except:
            print(
                "********************************************************************************\n"
                "* Warnning:\n"
                "* Run command error for \"git clone https://github.com/RT-Thread/env.git\". \n"
                "* This error may have been caused by not found a git tool or git tool not in \n"
                "* the system PATH. \n"
                "* This error may cause script tools to fail to work properly. \n"
                "********************************************************************************\n"
            )
            help_info()

    # git clone sdk
    if not os.path.exists(os.path.join(env_dir, 'packages', 'sdk')):
        try:
            ret = os.system('git clone %s %s' % (sdk_url, os.path.join(env_dir, 'packages', 'sdk')))
            if ret != 0:
                shutil.rmtree(os.path.join(env_dir, 'packages', 'sdk'))
                print(
                    "********************************************************************************\n"
                    "* Warnning:\n"
                    "* Run command error for \"git clone https://github.com/RT-Thread/sdk.git\".\n"
                    "* This error may have been caused by not found a git tool or network error.\n"
                    "* If the git tool is not installed, install the git tool first.\n"
                    "* If the git utility is installed, check whether the git command is added \n"
                    "* to the system PATH.\n"
                    "* This error may cause the RT-Thread SDK to not work properly.\n"
                    "********************************************************************************\n"
                )
                help_info()
        except:
            print(
                "********************************************************************************\n"
                "* Warnning:\n"
                "* Run command error for \"https://github.com/RT-Thread/sdk.git\".\n"
                "* This error may have been caused by not found a git tool or git tool not in \n"
                "* the system PATH. \n"
                "* This error may cause the RT-Thread SDK to not work properly. \n"
                "********************************************************************************\n"
            )
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
        # zip_file = os.path.join(env_dir, 'tools', 'scripts', 'kconfig-mconf.zip')
        # if os.path.exists(zip_file):
        #     zip_file_dir = os.path.join(env_dir, 'tools', 'bin')
        #     if os.path.exists(zip_file_dir):
        #         shutil.rmtree(zip_file_dir)
        #     zip_file_obj = zipfile.ZipFile(zip_file, 'r')
        #     for file in zip_file_obj.namelist():
        #         zip_file_obj.extract(file, zip_file_dir)
        #     zip_file_obj.close()


def is_pkg_special_config(config_str):
    '''judge if it's CONFIG_PKG_XX_PATH or CONFIG_PKG_XX_VER'''

    if type(config_str) == type('a'):
        if config_str.startswith("PKG_") and (config_str.endswith('_PATH') or config_str.endswith('_VER')):
            return True
    return False


def mk_rtconfig(filename):
    try:
        config = open(filename, 'r')
    except:
        print('open config:%s failed' % filename)
        return

    rtconfig = open('rtconfig.h', 'w')
    rtconfig.write('#ifndef RT_CONFIG_H__\n')
    rtconfig.write('#define RT_CONFIG_H__\n\n')

    empty_line = 1

    for line in config:
        line = line.lstrip(' ').replace('\n', '').replace('\r', '')

        if len(line) == 0:
            continue

        if line[0] == '#':
            if len(line) == 1:
                if empty_line:
                    continue

                rtconfig.write('\n')
                empty_line = 1
                continue

            if line.startswith('# CONFIG_'):
                line = ' ' + line[9:]
            else:
                line = line[1:]
                rtconfig.write('/*%s */\n' % line)

            empty_line = 0
        else:
            empty_line = 0
            setting = line.split('=')
            if len(setting) >= 2:
                if setting[0].startswith('CONFIG_'):
                    setting[0] = setting[0][7:]

                # remove CONFIG_PKG_XX_PATH or CONFIG_PKG_XX_VER
                if is_pkg_special_config(setting[0]):
                    continue

                if setting[1] == 'y':
                    rtconfig.write('#define %s\n' % setting[0])
                else:
                    rtconfig.write('#define %s %s\n' % (setting[0], re.findall(r"^.*?=(.*)$", line)[0]))

    if os.path.isfile('rtconfig_project.h'):
        rtconfig.write('#include "rtconfig_project.h"\n')

    rtconfig.write('\n')
    rtconfig.write('#endif\n')
    rtconfig.close()


def get_file_md5(file):
    MD5 = hashlib.new('md5')
    with open(file, 'r') as fp:
        MD5.update(fp.read().encode('utf8'))
        fp_md5 = MD5.hexdigest()
        return fp_md5


# Exclude utestcases
def exclude_utestcases(RTT_ROOT):
    if os.path.isfile(os.path.join(RTT_ROOT, 'examples/utest/testcases/Kconfig')):
        return

    if not os.path.isfile(os.path.join(RTT_ROOT, 'Kconfig')):
        return

    with open(os.path.join(RTT_ROOT, 'Kconfig'), 'r') as f:
        data = f.readlines()
    with open(os.path.join(RTT_ROOT, 'Kconfig'), 'w') as f:
        for line in data:
            if line.find('examples/utest/testcases/Kconfig') == -1:
                f.write(line)


# fix locale for kconfiglib
def kconfiglib_fix_locale():
    import os
    import locale

    # Get the list of supported locales
    supported_locales = set(locale.locale_alias.keys())

    # Check if LANG is set and its value is not in the supported locales
    if 'LANG' in os.environ and os.environ['LANG'] not in supported_locales:
        os.environ['LANG'] = 'C'


def kconfiglib_check_installed():
    try:
        import kconfiglib
    except ImportError as e:
        print("\033[1;31m**ERROR**: Failed to import kconfiglib, " + str(e))
        print("")
        print("You may need to install it using:")
        print("    pip install kconfiglib\033[0m")
        print("")
        sys.exit(1)

    # set PKGS_DIR envrionment
    pkg_dir = GetPkgPath()
    if os.path.exists(pkg_dir):
        os.environ["PKGS_DIR"] = pkg_dir
    elif sys.platform != 'win32':
        touch_env()
        os.environ["PKGS_DIR"] = GetPkgPath()
    else:
        print("\033[1;33m**WARNING**: PKGS_DIR not found, please install ENV tools\033[0m")


# menuconfig for Linux and Windows
def menuconfig(RTT_ROOT):
    kconfiglib_check_installed()

    import menuconfig

    # Exclude utestcases
    exclude_utestcases(RTT_ROOT)

    fn = '.config'
    fn_old = '.config.old'

    sys.argv = ['menuconfig', 'Kconfig']

    # fix vscode console
    kconfiglib_fix_locale()

    menuconfig._main()

    if os.path.isfile(fn):
        if os.path.isfile(fn_old):
            diff_eq = operator.eq(get_file_md5(fn), get_file_md5(fn_old))
        else:
            diff_eq = False
    else:
        sys.exit(-1)

    # make rtconfig.h
    if diff_eq == False:
        shutil.copyfile(fn, fn_old)
        mk_rtconfig(fn)


# guiconfig for windows and linux
def guiconfig(RTT_ROOT):
    kconfiglib_check_installed()

    import guiconfig

    # Exclude utestcases
    exclude_utestcases(RTT_ROOT)

    fn = '.config'
    fn_old = '.config.old'

    sys.argv = ['guiconfig', 'Kconfig']
    guiconfig._main()

    if os.path.isfile(fn):
        if os.path.isfile(fn_old):
            diff_eq = operator.eq(get_file_md5(fn), get_file_md5(fn_old))
        else:
            diff_eq = False
    else:
        sys.exit(-1)

    # make rtconfig.h
    if diff_eq == False:
        shutil.copyfile(fn, fn_old)
        mk_rtconfig(fn)


# defconfig for windows and linux
def defconfig(RTT_ROOT):
    kconfiglib_check_installed()

    import defconfig

    # Exclude utestcases
    exclude_utestcases(RTT_ROOT)

    fn = '.config'

    sys.argv = ['defconfig', '--kconfig', 'Kconfig', '.config']
    defconfig.main()

    # silent mode, force to make rtconfig.h
    mk_rtconfig(fn)


def genconfig():
    from SCons.Script import SCons

    PreProcessor = SCons.cpp.PreProcessor()

    try:
        f = open('rtconfig.h', 'r')
        contents = f.read()
        f.close()
    except:
        print("Open rtconfig.h file failed.")

    PreProcessor.process_contents(contents)
    options = PreProcessor.cpp_namespace

    try:
        f = open('.config', 'w')
        for opt, value in options.items():
            if type(value) == type(1):
                f.write("CONFIG_%s=%d\n" % (opt, value))

            if type(value) == type('') and value == '':
                f.write("CONFIG_%s=y\n" % opt)
            elif type(value) == type('str'):
                f.write("CONFIG_%s=%s\n" % (opt, value))

        print("Generate .config done!")
        f.close()
    except:
        print("Generate .config file failed.")
