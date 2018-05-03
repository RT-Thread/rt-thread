@echo off
@echo get and update RT-Thread kernel source
svn co https://rt-thread.googlecode.com/svn/trunk/src/                  ./rt-thread/src
@echo get and update RT-Thread include file
svn co https://rt-thread.googlecode.com/svn/trunk/include/              ./rt-thread/include
@echo get and update Nios II architecture for RT-Thread
svn co https://rt-thread.googlecode.com/svn/trunk/libcpu/nios/nios_ii/  ./rt-thread/libcpu/nios/nios_ii
pause
