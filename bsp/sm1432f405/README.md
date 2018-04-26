## board info:

    SM1432F405
    http://sanmuchina.taobao.com

## note:

in drivers/stm32f4xx_conf.h

```
    /* Redefine the HSE value; it's equal to 8 MHz on the STM32F4-DISCOVERY Kit */
    efine HSE_VALUE    ((uint32_t)8000000)
```
 
 **================= IAR WARNING =================**
 
After use `scons --target=iar -s` command to product IAR project, you have to add iar link file manually.

IAR IDE steps:
1. Project-->Options-->Linker
2. Config-->Linker Configuration file
3. select `Override Default`, then select `bsp/stm32f40x/stm32f40x_flash.icf`
4. rebuild project

**TODO**

auto add *.icf by scons script

**log**
add dfu tools
add stm32f405
