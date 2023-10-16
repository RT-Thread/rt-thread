# Microchip BSP

## 1. Microchip BSP Introduction

Supported Microchip SAM (ARM Cortex-Mx Core) MCU is as following：

### ARM Cortex-M23 Series

- saml10 | 3.3V Cortex-M23 with ultra low power
- saml11 | 3.3V Cortex-M23 with ultra low power and trust-zone

### ARM Cortex-M0+ Series

- samc21 | 5V Cortex-M0+ with 2 CAN-FD support
- saml21 | 3.3V low power Cortex-M0+
- samd21 | 3.3V industrial level Cortex-M0+

### ARM Cortex-M4 Series

- same54 | 3.3V 120MHz Cortex-M4F core with CAN-FD/USB/Ethernet support

### ARM Cortex-M7 Series

- same70 | 3.3V 300MHz Cortex-M7 core with CAN-FD/High speed USB/Ethernet support

### Directory description：

	* applications: 
		* user main function entrance,
		* driver example - like i2c, can, adc ...
		* application example
	* board: 
		* user board initialization
		* user driver adpater code, like console device, ethernet device
	* bsp:
		* MCU BSP files - startup file, peripheral drivers, configuation headers and linker script
		* generated from start.atmel.com - DO NOT modify it

## 2. RT-Thread porting guide of Microchip SAM MCU

### 2.1 Configure project BSP on Atmel Start

Visit <https://start.atmel.com/#> and click CREATE NEW PROJECT.

![](doc/2-1-1-atmel-start-online.png)

Input MCU part number and then select device, click CREATE NEW PROJECT.

![](doc/2-1-2-atmel-start-newproject.png)

Add STDIO and other driver/middleware to project.

![](doc/2-1-3-atmel-start-add-STDIO.png)

Configure STDIO driver.

![](doc/2-1-4-atmel-start-driver-stdio.png)

Configure CAN module clock.

![](doc/2-1-5-atmel-start-can-clock.png)

Configure CAN module driver.

![](doc/2-1-6-atmel-start-driver-can0.png)

![](doc/2-1-6-atmel-start-driver-can1.png)

Add LED pin description.

![](doc/2-1-8-atmel-start-add-LED0.png)

Rename project.

![](doc/2-1-7-atmel-start-rename-project.png)

Save project configuration.

![](doc/2-1-9-atmel-start-save-configuration.png)

Export project source code.

![](doc/2-1-10-atmel-start-export-project.png)

### 2.2 Add project to RT-Thread source code

Link: <https://github.com/RT-Thread/rt-thread> and download RT souce code.

![](doc/2-2-1-atmel-start-download-RT-Thread.png)

Unzip downloaded RT-Thread and SAME70 CAN Example

![](doc/2-2-2-atmel-start-unzip-file.png)

Enter *rt-thread-xxx/bsp/microchip* directory and copy **same70** folder and rename it to **same70q20**.

![](doc/2-2-3-atmel-start-copy-file.png)

Enter same70q20 directory and remove all files except SConscript file.

![](doc/2-2-4-atmel-start-remove-old-files.png)

Copy all files from SAME70 CAN Example to rt-thread-xxx/bsp/microchip/same70q20/bsp.

![](doc/2-2-5-atmel-start-copy-files.png)

Modify rt-thread-xxx\bsp\microchip\same70q20\rtconfig.py.

![](doc/2-2-6-atmel-start-modify-file0.png)

Modify rt-thread-xxx\bsp\microchip\same70q20\bsp\SConscript.

![](doc/2-2-6-atmel-start-modify-file1.png)

Modify rt-thread-xxx\bsp\microchip\same70q20\bsp\same70b\gcc\gcc\same70q20b_flash.ld.

![](doc/2-2-6-atmel-start-modify-file2.png)

Modify rt-thread-xxx\bsp\microchip\same70q20\bsp\same70b\gcc\gcc\startup_same70q20b.c.

![](doc/2-2-6-atmel-start-modify-file3.png)

Alright, now you can use RT-Thread env tools to compile the project.

### 2.3 Compile project with RT-Thread env tools

About RT-Thread env tools, click [Here](https://github.com/RT-Thread/rt-thread/blob/master/documentation/env/env.md).

Download RT-Thread env tools <https://www.rt-thread.org/download.html#download-rt-thread-env-tool>

![](doc/2-3-1-atmel-start-download-env-tools.png)

Unzip downloaded file and run env.exe.

![](doc/2-3-2-atmel-start-run-env-tools.png)

Enter your project directory and run scons command to compile it.

![](doc/2-3-3-atmel-start-env-tools-compile.png)

Compile error you may have and proposed solution.

![](doc/2-3-4-atmel-start-env-tools-errors.png)

Fix compiling error

![](doc/2-3-5-atmel-start-env-tools-fixerrors.png)

Compiling success

![](doc/2-3-6-atmel-start-env-tools-compiling-OK.png)

In the following chapter I will show you how to debug RT-Thread with Studio 7.

## 3. RT-Thread debugging with Microchip IDE

Link: <https://www.microchip.com/en-us/tools-resources/develop/microchip-studio>, download & install Microchip Studio 7.

![](doc/3-1-1-atmel-start-Studio7-download.png)

Open installed Microchip Studio 7 and open object file for debugging.

![](doc/3-1-2-atmel-start-Studio7-open-objects.png)

Choose object file, fill project name and select where to save this project.

![](doc/3-1-3-atmel-start-Studio7-import-debug.png)

Select the right part number and complete object set up.

![](doc/3-1-4-atmel-start-Studio7-select-device.png)

Object file import complete and you can see related files are linked to project.

![](doc/3-1-5-atmel-start-Studio7-project-complete.png)

Right click the project and choose the debug tools in project propertities setting.

![](doc/3-1-6-atmel-start-Studio7-project-properties.png)

Choose debugger/programmer and debugger interface - SWD or JTGA.

![](doc/3-1-7-atmel-start-Studio7-select-tools.png)

Press debugging button and enjoy your debugging journey.

![](doc/3-1-8-atmel-start-Studio7-start-debugging1.png)

Debugging start and you can add breakpoint.

![](doc/3-1-8-atmel-start-Studio7-start-debugging2.png)

Debugging paused at breakpoint and you can monitor local variables at Watch window.

![](doc/3-1-8-atmel-start-Studio7-start-debugging3.png)

Debugging message output.

![](doc/3-1-9-atmel-start-rt-thread-run.png)

## 4. Reconfigure MCU BSP

Visit <https://start.atmel.com/#> and upload project configuration.

![](doc/4-1-1-atmel-start-Studio7-reimport-project.png)

Now you can reconfigure your project.

![](doc/4-1-2-atmel-start-Studio7-project-configurtion.png)


## 5. Microchip SAM MCU BSP configuration and user guide

Please refer to [ASF4 API Reference Manual](https://ww1.microchip.com/downloads/en/DeviceDoc/50002633B.pdf) for more details

### 5.1 SAMC2x/E5x/E70 CAN Driver

CAN driver configuration.

![](doc/5-1-1-atmel-start-driver-can0.png)
![](doc/5-1-1-atmel-start-driver-can1.png)

CAN driver user guide - see [ASF4 API Reference Manual](https://ww1.microchip.com/downloads/en/DeviceDoc/50002633B.pdf) P121 for more details. 

To be continued.

## 6. Contact Info

- [Kevin Liu](https://github.com/klmchp), email: <kevin.liu.mchp@gmail.com>
- [luhuadong](https://github.com/luhuadong), email: <luhuadong@163.com>
