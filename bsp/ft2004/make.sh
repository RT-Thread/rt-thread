###
 # @Author: hh
 # @Date: 2020-12-23 13:53:50
 # @LastEditTime: 2021-05-18 16:48:25
 # @LastEditors: Please set LastEditors
 # @Description: In User Settings Edit
 # @FilePath: \ft\bare\2_base\factory.sh
### 
#/bin/sh
# scons --clean
# ./update.sh 
scons -j8
rm /mnt/d/project/tftp/rtthread.bin
cp ./rtthread.bin /mnt/d/project/tftp/

# arm-none-eabi-objdump -D -m arm ft2004.elf > rtt.dis