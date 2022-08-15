#!/usr/bin/env bash

###############################################################################
# File Name: elf2c.sh
#
# Description:
# Basic bash shell script to convert the programmable sections of an *.elf file
# into a basic c array. This uses objcopy and python.
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

# Path to the current script
SCRIPTPATH="$(dirname "$0")"

# Enable error mode and verbose tracing
set -ex

# Path to Elf2Bin tool
# ELF2BIN="C:/Program Files (x86)/GNU Tools ARM Embedded/7 2018-q2-update/bin/arm-none-eabi-objcopy.exe"
[[ -n "$ELF2BIN" ]] || ELF2BIN="${USERPROFILE:-$HOME}/ModusToolbox/tools_2.1/gcc-7.2.1/bin/arm-none-eabi-objcopy.exe"

# Path to Python executable
[[ -n "$PYTHON" ]] || PYTHON=python

# This function converts ELF executable to C file
# Additionally, it generates HEX file
# arg#1: path to ELF file
# arg#2: path to C file
# arg#3: C preprocessor guard macro (optional)
function elf2c()
{
    [[ $# -ge 2 ]] || { echo >&2 "Error: expected 2 or 3 arguments: <path-to-elf> <path-to-c> [c-macro]"; exit 1; }

    local ELF_PATH="$1"
    local HEX_PATH="${ELF_PATH%.*}.hex"
    local BIN_PATH="${ELF_PATH%.*}.bin"
    local C_PATH="$2"
    local C_MACRO="$3"

    file "$ELF_PATH" || { echo >&2 "Error: $ELF_PATH is not found, exiting"; exit 1; }
    "$ELF2BIN" -O ihex "$ELF_PATH" "$HEX_PATH"
    "$ELF2BIN" -O binary "$ELF_PATH" "$BIN_PATH"
    "$PYTHON" "$SCRIPTPATH/bin2c.py" "$BIN_PATH" "$C_PATH" "$C_MACRO"
    echo "Successfully converted $ELF_PATH to $C_PATH"
}

# Check ELF2BIN
"$ELF2BIN" --version || { echo >&2 "Error: $ELF2BIN is not found, exiting"; exit 1; }

# Check python
"$PYTHON" --version || { echo >&2 "Error: python executable is not found, exiting"; exit 1; }

# Convert ELF to C
elf2c $@
