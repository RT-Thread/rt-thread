#!/bin/sh
#
# Copyright (c) 2006-2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#
# Boot this BSP's rtthread.bin on the d1s QEMU machine from
# https://github.com/cms19859230182-lang/d1s-qemu
#
# Usage (after building d1s-qemu and running scons in bsp/allwinner/d1s):
#   D1S_QEMU_DIR=/path/to/d1s-qemu ./target-qemu/run-qemu.sh [run.sh options]
#
# Environment:
#   D1S_QEMU_DIR   built d1s-qemu checkout (must contain executable run.sh)
#   QEMU_TIMEOUT   seconds before QEMU is killed (default 0 = no limit,
#                  set e.g. 30 for CI / AI smoke tests)
#
# sbi.bin and u-boot.dtb are taken from the BSP directory; the console of
# this BSP is UART0, so it is connected to the terminal.

set -eu

here=$(cd "$(dirname "$0")" && pwd)
bsp=$(cd "$here/.." && pwd)
dir=${D1S_QEMU_DIR:-}
tmo=${QEMU_TIMEOUT:-0}

if [ -z "$dir" ] || [ ! -x "$dir/run.sh" ]; then
    echo "please set D1S_QEMU_DIR to a built d1s-qemu checkout" >&2
    echo "see https://github.com/cms19859230182-lang/d1s-qemu" >&2
    exit 1
fi

if [ ! -f "$bsp/rtthread.bin" ]; then
    echo "$bsp/rtthread.bin not found, run scons in $bsp first" >&2
    exit 1
fi

if [ "$tmo" -gt 0 ] 2>/dev/null; then
    exec timeout --foreground "$tmo" \
        "$dir/run.sh" "$bsp/rtthread.bin" --bsp "$bsp" --console uart0 "$@"
fi

exec "$dir/run.sh" "$bsp/rtthread.bin" --bsp "$bsp" --console uart0 "$@"
