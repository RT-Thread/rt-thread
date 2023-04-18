# Peripheral Driver Addition Guide of RA Series

## 1. Introduction

This document is intended for developers who need to add more peripheral drivers to their existing RA series BSPs. By reading this article, developers can add their own drivers to existing BSPs according to their actual situation.

## 2. Prerequisites

- Proficiency in using ENV tools, reference: [RT-Thread env tools user manual](https://www.rt-thread.org/document/site/#/development-tools/env/env)
- Familiar with [Kconfig](https://www.rt-thread.org/document/site/#/development-tools/kconfig/kconfig) programmer
- Familiar with  [FSP](https://www2.renesas.cn/jp/zh/software-tool/flexible-software-package-fsp) tool
- Understanding RT-Thread [Device Driver Framework](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/programming-manual/device/device)

## 3. How to add more peripheral driver options

This section uses the example of adding on-chip peripheral drivers to explain how to add more drivers available to BSPs. If the on-chip peripherals you want to use are not available in the 'On-chip peripheral configuration menu', you need to add them yourself. Below we will demonstrate how to add a UART9 port for ra6m4-cpk.

Adding peripheral support for UART requires the following steps:

### 3.1 Modify the Kconfig file

Open the board\kconfig file in the BSP and add the UART9 configuration.

![image-20220221161853343](figures_en/add_uart.png) 

![image-20220221163152761](figures_en/add_uart1.png) 

After the modification is complete, open the ENV tool in the BSP directory and enter the 'menuconfig' command on the command line to see if the UART9 configuration has been added.

![image-20220221164229974](figures_en/add_uart2.png) 

### 3.2 Modify the uart_config.h file

Once the configuration of Kconfig is added, you also need to add the corresponding configuration in the configuration file and driver file.

Open the file `libraries\HAL_Drivers\config\ra6m4\uart_config.h` to add the UART9 configuration.

![image-20220221170945734](figures_en/add_uart3.png) 

### 3.3 Modify the drv_usart_v2.h file

Open `librariesHAL_Driversdrv_usart_v2.c' and add the following code:

![image-20220221171806580](figures_en/add_uart4.png) 

![image-20220221172034531](figures_en/add_uart5.png) 

### 3.4 Test validation

1. Open UART9 in menuconfig and save the configuration, regenerating the MDK project using the 'scons --target=mdk5' command.
2. Open the FSP Configuration Tool from the project project and add the UART9 port

![image-20220221180942314](figures_en/add_uart6.png) 

![image-20220221183752087](figures_en/add_uart8.png) 

3. Configure the CORRESPONDING IO pin of UART9, save and exit.

![image-20220221183405828](figures_en/add_uart7.png) 

4. Compile, debug download, enter list_device command to see that the uart9 device has been registered to the kernel, indicating that the device was added successfully, and then you can use the UART9 port to communicate.

![image-20220221185534932](figures_en/add_uart9.png) 



This tutorial translated by [Josh Zou](https://github.com/Firmament-Autopilot)