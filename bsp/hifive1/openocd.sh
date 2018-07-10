#!/bin/bash

openocd -f openocd.cfg & riscv64-unknown-elf-gdb rtthread.elf --batch -ex "set remotetimeout 240" -ex "target extended-remote localhost:3333" -ex "monitor reset halt" -ex "monitor flash protect 0 64 last off" -ex "load" -ex "monitor resume" -ex "monitor shutdown" -ex "quit" && \
echo "Successfully uploaded 'hello' to freedom-e300-hifive1."

