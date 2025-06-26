@echo off
set OBJDUMP=D:\RT-ThreadStudio\repo\Extract\ToolChain_Support_Packages\RISC-V\XTGccElfNewlib\V3.0.1\R\bin\riscv64-unknown-elf-objdump
set TARGET=E:\rt-thread\bsp\xuantie\smartl\e906\rtthread.elf
set OUTPUT=rtthread.asm

%OBJDUMP% -d %TARGET% > %OUTPUT%
echo Disassembly generated to %OUTPUT%
pause