# STM32F103C8 Blue Pill Board BSP Introduction

 [[中文版]](README_zh.md)

This document records the guide of the BSP (board support package) provided by the RT-Thread development team for the STM32F103C8 Blue Pill development board.

The document is covered in four parts:

- Onboard Resources
- Quickly Get Started
- Advanced Features
- References

By reading the ***Quickly Get Started*** section developers can quickly get their hands on this BSP and run RT-Thread on the board. More advanced features will be introduced in the Advanced Features section to help developers take advantage of RT-Thread to drive more on-board resources.



## Onboard Resources

The "blue pill" is a STM32F103 based development board with Cortex-M3 ARM CPU that runs at 72 MHz, 20 kB of RAM and 64 or 128 kB of flash memory. The microcontroller (MCU) has USB port, two serial ports, 16 bit PWM pins and 12 bit ADC pins. It runs at 3.3V, but some of its pins are 5V tolerant.

- MCU：STM32F103C8T6 @ 72MHz, 64KB FLASH , 20KB RAM

- Peripherals
  
  - LED：PC13
  
- Debug IO interface type: SWD / ST-LINK

  

![board](figures/board1.jpg)





## Quickly Get Started

This BSP provides MDK4, MDK5, and IAR projects for developers and it supports the GCC development environment. Here's an example of the MDK5 development environment, to introduce how to run the system.

### Hardware connection

1) Use a Type-A to Mini-B cable to connect the development board to the PC and turn on the power switch. 

2) Use FTDI adapter(USB to UART) to connect the BluePill board's PA9(Tx) and PA10(Rx) pins.

![connection](figures/connection.jpg)

### Compile and Download

Double-click the `project.uvprojx` file, to open the MDK5 project, compile and download the program to the board.

### Running Results

After the program is successfully downloaded, the system runs automatically. Observe the running results of the LED on the development board, and you will see LED is flashing periodically.

The USB virtual COM port connects to USART1(PA9-Tx, PA10-Rx) by default, and when the corresponding serial port (115200-8-1-N) is opened in the terminal tool, the output information of RT-Thread can be seen when the device is reset:

```shell
 \ | /
- RT -     Thread Operating System
 / | \     4.0.0 build Dec 21 2018
 2006 - 2018 Copyright by rt-thread team
msh >
```



## **Advanced Features**

This BSP only enables GPIO and USART2 by default. If you need more advanced features such as SPI, I2C, you need to configure the BSP with RT-Thread [ENV tools](https://www.rt-thread.io/download.html?download=Env) , as follows:

1. Open the ENV tool under the specific BSP folder;
2. Enter `menuconfig` command to configure the project, then save and exit;
3. Enter `pkgs --update` command to update the package;
4. Enter `scons --target=mdk4/mdk5/iar` command to regenerate the project.

Learn how to use RT-Thread ENV, click [Here](https://github.com/RT-Thread/rtthread-manual-doc/blob/master/env/env.md).



## References

- [[STM32 Blue Pill vs Black Pill Microcontroller Boards]](https://www.youtube.com/watch?v=QCdnO43RBK4&t=875s)

- [[STM32F103C8 datasheet]]( https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)

- [[STM32F103C8 More Information]](https://www.st.com/en/microcontrollers-microprocessors/stm32f103c8.html#overview)




## Maintained By

Meco Man @ rt-thread community

jiantingman@foxmail.com 

https://github.com/mysterywolf