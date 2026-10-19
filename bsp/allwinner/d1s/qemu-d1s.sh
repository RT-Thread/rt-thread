#!/bin/sh
#
# Copyright (c) 2006-2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Boot this BSP's rtthread.bin on the d1s QEMU machine from
# https://github.com/cms19859230182-lang/d1s-qemu
#
# Usage (after building d1s-qemu and running scons in this directory):
#   D1S_QEMU_DIR=/path/to/d1s-qemu ./qemu-d1s.sh [extra run.sh options]
#
# sbi.bin and u-boot.dtb are taken from this directory; the console of
# this BSP is UART0, so it is connected to the terminal.

set -eu

here=$(cd "$(dirname "$0")" && pwd)
dir=${D1S_QEMU_DIR:-}

if [ -z "$dir" ] || [ ! -x "$dir/run.sh" ]; then
    echo "please set D1S_QEMU_DIR to a built d1s-qemu checkout" >&2
    echo "see https://github.com/cms19859230182-lang/d1s-qemu" >&2
    exit 1
fi

if [ ! -f "$here/rtthread.bin" ]; then
    echo "$here/rtthread.bin not found, run scons first" >&2
    exit 1
fi

exec "$dir/run.sh" "$here/rtthread.bin" --bsp "$here" --console uart0 "$@"
