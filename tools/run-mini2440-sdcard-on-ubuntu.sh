#!/bin/bash
./qemu-system-arm-on-ubuntu -M mini2440 -kernel ../bsp/mini2440/rtthread-mini2440.axf -show-cursor -sd SDCARD -serial vc:80Cx24C -serial file:virtualkbd

