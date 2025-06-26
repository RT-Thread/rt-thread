# -*- coding: utf-8 -*-
#
# File      : __init__.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
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
# 2025-01-XX     Bernard      Create targets module for IDE project generators

# Import all target generators
from . import keil
from . import iar
from . import vs
from . import vs2012
from . import codeblocks
from . import ua
from . import vsc
from . import cdk
from . import ses
from . import eclipse
from . import codelite
from . import cmake
from . import xmake
from . import esp_idf
from . import zigbuild
from . import makefile
from . import rt_studio

# Export all target generator functions
__all__ = [
    # Keil MDK
    'keil',
    # IAR
    'iar', 
    # Visual Studio
    'vs',
    'vs2012',
    # Code::Blocks
    'codeblocks',
    # Universal ARM
    'ua',
    # VSCode
    'vsc',
    # CDK
    'cdk',
    # SEGGER Embedded Studio
    'ses',
    # Eclipse
    'eclipse',
    # CodeLite
    'codelite',
    # CMake
    'cmake',
    # XMake
    'xmake',
    # ESP-IDF
    'esp_idf',
    # Zig
    'zigbuild',
    # Make
    'makefile',
    # RT-Studio
    'rt_studio'
] 