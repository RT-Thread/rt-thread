#
# Copyright (c) 2006-2023, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Change Logs:
# Date           Author       Notes
# 2023-05-10     GuEe-GUI     the first version
#

import os, re

from building import *

__dtc_install_tip = """
You should install dtc (devicetree compiler) in your system:
    Linux:
        Debian/Ubuntu: apt-get install device-tree-compiler
        Arch/Manjaro: pacman -Sy dtc

    MacOS:
        brew install dtc

    Windows (MinGW):
        msys2: pacman -S dtc
"""

def __check_dtc(value):
    if value != 0 and os.system("dtc -v") != 0:
        print(__dtc_install_tip)

def dts_to_dtb(RTT_ROOT, dts_list, options = "", include_paths = [], ignore_warning = []):
    path = GetCurrentDir() + '/'
    warning_ops = ""
    for warning in ignore_warning:
        warning_ops += " -W no-" + warning
    for dts in dts_list:
        dtb = dts.replace('.dts', '.dtb')
        if not os.path.exists(path + dtb) or os.path.getmtime(path + dtb) < os.path.getmtime(path + dts):
            tmp_dts = dts + '.tmp'
            Preprocessing(dts, None, output = tmp_dts, CPPPATH=[RTT_ROOT + '/components/drivers/include'] + include_paths)
            ret = os.system("dtc -I dts -O dtb -@ -A {} {} {} -o {}".format(warning_ops, options, path + tmp_dts, path + dtb))
            __check_dtc(ret)
            if os.path.exists(path + tmp_dts):
                os.remove(path + tmp_dts)

def dtb_to_dts(RTT_ROOT, dtb_name, dts_name = None, options = ""):
    path = GetCurrentDir() + '/'
    if dts_name == None:
        dts_name = re.sub(r'\.dtb[o]*$', '.dts', dtb_name)
    ret = os.system("dtc -I dtb -O dts {} {} -o {}".format(options, path + dtb_name, path + dts_name))
    __check_dtc(ret)
