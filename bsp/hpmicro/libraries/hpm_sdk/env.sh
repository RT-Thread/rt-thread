#
# Copyright (c) 2021 hpmicro
#
# SPDX-License-Identifier: BSD-3-Clause
#

if [ "X$MSYSTEM" "==" "X" ]; then
    if [ "X$name" "==" "Xenv.sh" ]; then
        echo "Please source this file, rather than executing it."
        exit
    fi
    env_name=$0
else
    env_name=$1
fi

script=$(cd -P -- "$(dirname -- "$env_name")" && printf '%s\n' "$(pwd -P)/$(basename -- "$env_name")")
if [ "X$MSYSTEM" "==" "X" ]; then
    export HPM_SDK_BASE=$(dirname "$script")
else
    export HPM_SDK_BASE=$script
fi

echo $HPM_SDK_BASE

export OPENOCD_SCRIPTS=${HPM_SDK_BASE}/boards/openocd

