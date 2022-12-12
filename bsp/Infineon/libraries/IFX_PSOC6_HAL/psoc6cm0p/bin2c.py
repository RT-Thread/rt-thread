#!/usr/bin/env python

###############################################################################
# File Name: elf2c.py
#
# Description:
# Basic python script to convert the binary output from objcopy into a basic c
# array.
#
###############################################################################
# Copyright 2019-2021 Cypress Semiconductor Corporation (an Infineon company)
# or an affiliate of Cypress Semiconductor Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################

import os
import sys
import argparse
import binascii

number_of_columns = 16

copyright = """/***************************************************************************//**
* \\file {}
*
* \\brief
* Cortex-M0+ prebuilt application image.
*
********************************************************************************
* \\copyright
* Copyright (c) 2018-2021 Cypress Semiconductor Corporation (an Infineon
* company) or an affiliate of Cypress Semiconductor Corporation
* SPDX-License-Identifier: LicenseRef-PBL
*
* Licensed under the Permissive Binary License
*******************************************************************************/

"""

header = """
#if defined(__APPLE__) && defined(__clang__)
__attribute__ ((__section__("__CY_M0P_IMAGE,__cy_m0p_image"), used))
#elif defined(__GNUC__) || defined(__ARMCC_VERSION)
__attribute__ ((__section__(".cy_m0p_image"), used))
#elif defined(__ICCARM__)
#pragma  location=".cy_m0p_image"
#else
#error "An unsupported toolchain"
#endif
const uint8_t cy_m0p_image[] = {
"""

c_list = []


# Get component name from the command line
parser = argparse.ArgumentParser()
parser.add_argument("bin_path", help="Specify path the input binary file to be converted to a C array.")
parser.add_argument("c_path", help="Specify path the output C file with the C array.")
parser.add_argument("c_macro", help="Specify the C preprocessor macro to wrap the variable.")
args = parser.parse_args()
bin_path = args.bin_path
c_path = args.c_path
c_macro = args.c_macro

c_file=os.path.basename(c_path)

f = open(bin_path, "rb")
data = list(f.read())

with open(c_path, "w") as c_fd:

    # Clear content of the file
    c_fd.seek(0)
    c_fd.truncate()

    # Write copyright
    c_fd.write(copyright.format(c_file))

    # Include headers
    c_fd.write("#include <stdint.h>\n")
    c_fd.write("#include \"cy_device_headers.h\"\n")
    c_fd.write("\n")

    # Open conditional block
    if c_macro:
        c_fd.write("#if defined(" + c_macro + ")\n")

    # Write template
    c_fd.write(header)

    # Generate list of the data bytes
    for n in data:
        c_list.append(format(n, '#04x'))

    for i in range(int(len(c_list) / number_of_columns) + 1):
        line_list = c_list[i * number_of_columns: (i + 1) * number_of_columns]
        c_fd.write("   ")
        for item in line_list:
            c_fd.write(" %su," % item)
        c_fd.write("\n")

    c_fd.write("};\n")

    # Close conditional block
    if c_macro:
        c_fd.write("#endif /* defined(" + c_macro + ") */")
    c_fd.write("\n")
f.close()
