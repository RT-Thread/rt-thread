#******************************************************************************
#
# Makefile - Rules for building the driver library.
#
# Copyright (c) 2011 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 8049 of the Stellaris Peripheral Driver Library.
#
#******************************************************************************

all:
	@make -f Makefile.driverlib-cm3
	@make -f Makefile.driverlib-cm4f

clean:
	@make -f Makefile.driverlib-cm3 clean
	@make -f Makefile.driverlib-cm4f clean

realclean:
	@make -f Makefile.driverlib-cm3 realclean
	@make -f Makefile.driverlib-cm4f realclean
