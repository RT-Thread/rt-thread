board info:
STM32F4 discovery
http://www.st.com/internet/evalboard/product/252419.jsp

note:
in drivers/stm32f4xx_conf.h
 /* Redefine the HSE value; it's equal to 8 MHz on the STM32F4-DISCOVERY Kit */
 #define HSE_VALUE    ((uint32_t)8000000)

该修改一下STM32F4xx_StdPeriph_Driver 版本了
