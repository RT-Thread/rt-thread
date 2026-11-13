#!/usr/bin/env bash
# Send a file to the temporary usbcrc command over the F101 CDC ACM device.

set -euo pipefail

usage()
{
    printf 'Usage: %s <file> [tty] [target-command]\n' "$0" >&2
    printf 'Example: %s /home/gui/Desktop/rt-thread/test.jpg /dev/ttyACM0 usbjpeg\n' "$0" >&2
    exit 2
}

file=${1:-}
device=${2:-/dev/ttyACM0}
target_command=${3:-usbcrc}
chunk_size=512
chunk_delay=0.03

[[ -n "$file" ]] || usage
[[ -r "$file" ]] || { printf 'Cannot read: %s\n' "$file" >&2; exit 1; }
[[ -c "$device" ]] || { printf 'Not a serial device: %s\n' "$device" >&2; exit 1; }

size=$(wc -c < "$file")

printf 'On the board, run:\n\n  %s %s\n\n' "$target_command" "$size"
read -r -p 'Press Enter after the board reports ready: '

stty -F "$device" raw -echo -ixon -ixoff -icrnl -inlcr -onlcr

for ((offset = 0; offset < size; offset += chunk_size)); do
    dd if="$file" of="$device" bs="$chunk_size" \
        skip=$((offset / chunk_size)) count=1 status=none
    sleep "$chunk_delay"
done

printf 'Sent %s bytes to %s.\n' "$size" "$device"
