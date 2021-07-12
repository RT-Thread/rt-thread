#
# File      : menuconfig.py
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
# 2017-12-29     Bernard      The first version
# 2018-07-31     weety        Support pyconfig
# 2019-07-13     armink       Support guiconfig

import os
import re
import sys
import shutil
import hashlib
import operator

# make rtconfig.h from .config

def is_pkg_special_config(config_str):
    ''' judge if it's CONFIG_PKG_XX_PATH or CONFIG_PKG_XX_VER'''

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
                    rtconfig.write('#define %s %s\n' % (setting[0], re.findall(r"^.*?=(.*)$",line)[0]))

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

def config():
    mk_rtconfig('.config')

def get_env_dir():
    if os.environ.get('ENV_ROOT'):
        return os.environ.get('ENV_ROOT')

    if sys.platform == 'win32':
        home_dir = os.environ['USERPROFILE']
        env_dir  = os.path.join(home_dir, '.env')
    else:
        home_dir = os.environ['HOME']
        env_dir  = os.path.join(home_dir, '.env')

    if not os.path.exists(env_dir):
        return None

    return env_dir

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

    env_dir  = os.path.join(home_dir, '.env')
    if not os.path.exists(env_dir):
        os.mkdir(env_dir)
        os.mkdir(os.path.join(env_dir, 'local_pkgs'))
        os.mkdir(os.path.join(env_dir, 'packages'))
        os.mkdir(os.path.join(env_dir, 'tools'))
        kconfig = open(os.path.join(env_dir, 'packages', 'Kconfig'), 'w')
        kconfig.close()

    if not os.path.exists(os.path.join(env_dir, 'packages', 'packages')):
        try:
            ret = os.system('git clone https://github.com/RT-Thread/packages.git %s' % os.path.join(env_dir, 'packages', 'packages'))
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

    if not os.path.exists(os.path.join(env_dir, 'tools', 'scripts')):
        try:
            ret = os.system('git clone https://github.com/RT-Thread/env.git %s' % os.path.join(env_dir, 'tools', 'scripts'))
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

    if sys.platform != 'win32':
        env_sh = open(os.path.join(env_dir, 'env.sh'), 'w')
        env_sh.write('export PATH=~/.env/tools/scripts:$PATH')
    else:
        if os.path.exists(os.path.join(env_dir, 'tools', 'scripts')):
            os.environ["PATH"] = os.path.join(env_dir, 'tools', 'scripts') + ';' + os.environ["PATH"]

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

# menuconfig for Linux
def menuconfig(RTT_ROOT):

    # Exclude utestcases 
    exclude_utestcases(RTT_ROOT)

    kconfig_dir = os.path.join(RTT_ROOT, 'tools', 'kconfig-frontends')
    os.system('scons -C ' + kconfig_dir)

    touch_env()
    env_dir = get_env_dir()

    os.environ['PKGS_ROOT'] = os.path.join(env_dir, 'packages')

    fn = '.config'
    fn_old = '.config.old'

    kconfig_cmd = os.path.join(RTT_ROOT, 'tools', 'kconfig-frontends', 'kconfig-mconf')
    os.system(kconfig_cmd + ' Kconfig')

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
    import pyguiconfig

    # Exclude utestcases 
    exclude_utestcases(RTT_ROOT)

    if sys.platform != 'win32':
        touch_env()

    env_dir = get_env_dir()

    os.environ['PKGS_ROOT'] = os.path.join(env_dir, 'packages')

    fn = '.config'
    fn_old = '.config.old'

    sys.argv = ['guiconfig', 'Kconfig']
    pyguiconfig._main()

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
def guiconfig_silent(RTT_ROOT):
    import defconfig

    # Exclude utestcases 
    exclude_utestcases(RTT_ROOT)
    
    if sys.platform != 'win32':
        touch_env()

    env_dir = get_env_dir()

    os.environ['PKGS_ROOT'] = os.path.join(env_dir, 'packages')

    fn = '.config'

    sys.argv = ['defconfig', '--kconfig', 'Kconfig', '.config']
    defconfig.main()

    # silent mode, force to make rtconfig.h
    mk_rtconfig(fn)
