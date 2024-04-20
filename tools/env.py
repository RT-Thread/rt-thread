#! /usr/bin/env python
#coding=utf-8
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

def GetEnvPath():
    env = os.environ.get('ENV_ROOT')

    if env is None:
        if platform.system() == 'Windows':
            return os.path.join(os.environ['USERPROFILE'], '.env')
        else:
            return os.path.join(os.environ['HOME'], '.env')

    return env

def GetSDKPackage():
    env = GetEnvPath()

    if env:
        return os.path.join(env, 'tools', 'packages')

    return None

def GetSDKPath(name):
    env = GetEnvPath()

    if env:
        #read packages.json under env/tools/packages
        with open(os.path.join(env, 'tools', 'packages', 'pkgs.json'), 'r', encoding='utf-8') as f:
            # packages_json = f.read()
            packages = json.load(f)

            for item in packages:
                package_path = os.path.join(GetEnvPath(), 'packages', item['path'], 'package.json')
                # read package['path']/package.json under env/packages
                with open(package_path, 'r', encoding='utf-8') as f:
                    # package_json = f.read()
                    package = json.load(f)

                    if package['name'] == name:
                        return os.path.join(GetSDKPackage(), package['name'] + '-' + item['ver'])

    # not found named package
    return None
