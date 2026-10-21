#!/bin/sh
# Kept for compatibility; see target-qemu/run-qemu.sh
exec "$(cd "$(dirname "$0")" && pwd)/target-qemu/run-qemu.sh" "$@"
