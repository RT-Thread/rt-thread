###
###
 # Copyright : (C) 2022 Phytium Information Technology, Inc. 
 # All Rights Reserved.
 #  
 # This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 # under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 # either version 1.0 of the License, or (at your option) any later version. 
 #  
 # This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 # without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 # See the Phytium Public License for more details. 
 #  
 # 
 # FilePath: make.sh
 # Date: 2022-10-13 16:03:41
 # LastEditTime: 2022-10-13 16:03:41
 # Description:  This file is for 
 # 
 # Modify History: 
 #  Ver   Who  Date   Changes
 # ----- ------  -------- --------------------------------------
### 

#/bin/sh

scons && cp rtthread_a32.bin D:\tftboot\rtthread_a32.bin && ls D:\tftboot\rtthread_a32.bin
#scons && cp rtthread_a32.bin /mnt/d/tftboot/rtthread_a32.bin && ls /mnt/d/tftboot/rtthread_a32.bin
arm-none-eabi-objdump -S  rtthread.elf > rtthread.dis