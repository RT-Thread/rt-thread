
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
import platform
from ci import CI
toolchains_config = {
    'arm':
    {
        'Linux': 'arm-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2',
        'Windows': 'arm-linux-musleabi_for_i686-w64-mingw32_latest.zip'
    },
    'aarch64':
    {
        'Linux' : 'aarch64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2',
        'Windows' : 'aarch64-linux-musleabi_for_i686-w64-mingw32_latest.zip'
    },
    'riscv64':
    {
        'Linux': 'riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2',
        'Windows': 'riscv64-linux-musleabi_for_i686-w64-mingw32_latest.zip'
    }
}
if __name__ == '__main__':
    # download toolchain
    if len(sys.argv) > 1:
        target = sys.argv[1]
    else:
        target = 'aarch64'
    ci = CI()
    toolchain_path = os.path.join(os.path.abspath('.'), 'gnu_gcc')
    platform = platform.system()
    try:
        zfile = toolchains_config[target][platform]
        URL = 'http://117.143.63.254:9012/www/rt-smart/' + zfile
    except:
        print('not found target')
        exit(0)
    ci.downloadFile(zfile, URL)
    ci.extractZipFile(zfile, toolchain_path)
    ci.delFile(zfile)