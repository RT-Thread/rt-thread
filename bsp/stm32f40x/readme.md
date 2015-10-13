board info:
STM32F4 discovery
http://www.st.com/internet/evalboard/product/252419.jsp

note:
in drivers/stm32f4xx_conf.h
 /* Redefine the HSE value; it's equal to 8 MHz on the STM32F4-DISCOVERY Kit */
 #define HSE_VALUE    ((uint32_t)8000000)
 
 
 
 **================= IAR WARNING =================**
 
 after use `scons --target=iar -s` cmd to product IAR project, you have to add iar link file by hand
 
 IAR steps:
 1. Project-->Options-->Linker
 2. Config-->Linker Configuration file
 3. select `Override Default`, then select `bsp/stm32f40x/stm32f40x_flash.icf`
 4. rebuild project
 
 
 **TODO**
 auto add *.icf by scons script

