board info:
STM32F429I-DISC1
http://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-mcu-discovery-kits/32f429idiscovery.html

note:
in drivers/stm32f4xx_conf.h
 /* Redefine the HSE value; it's equal to 8 MHz on the STM32F429I-DISC1 Kit */
 #define HSE_VALUE    ((uint32_t)8000000)


 **TODO**
 auto add *.icf by scons script
