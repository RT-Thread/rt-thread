## [STM32F401] How to create a new project

***info:***
:bulb: Download the latest RT-Thread studio from link -
https://www.rt-thread.io/studio.html 
and follow the instructions to install it on your windows machine. 

## 1 Create a new project

### 1.1 Go to File -> Import.

![](./figures/HjMyZCg.png)

### 1.2 Select RT-Thread Bsp Project into Workspace.

![](./figures/jcwFf24.png)

### 1.3 Import Projects from BSP.

![](./figures/XZZOTbT.png)

### 1.4 Browse Bsp Location to rt-threadx\bsp\stm32\stm32f401-st-nucleo, then click Select Folder.

![](./figures/osnThIA.png)

### 1.5 Fill up the rest of the information and select ST-LINK for debugger. Then, click finish button. There will be a newly created project at the workspace. 

![](./figures/1sLBJ88.png)

![](./figures/0Z4ahmr.png)

![](./figures/o3kdLrx.png)

## 2 Tool Chain

### 2.1 Select the latest tool chain version to resolve the warning.

![](./figures/aqCQRRX.png)

![](./figures/CJ38q4n.png)

### 2.2 If there is no latest tool chain version, click SDK manager to download the latest version.

![](./figures/rG3DJM6.png)

> Select the latest version from the RT-Thread SDK Manager window and click install packages button. After installation, click Exit SDK Manger button again.

![](./figures/BNvMNzb.png)

> Then select the latest version from the Open Build Settings Dialog.

## 3 RT-Thread Setting

### 3.1 In order to configure kernel and to enable add-on software packages, click RT-Thread Settings. Then, click detail button.

![](./figures/OOJq4U8.png)

![](./figures/jctYIJA.png)

![](./figures/bonMpvv.png)

### 3.2 After configuration, click save to update the latest configuration.

![](./figures/yubp4yc.png)

![](./figures/Bz4BwWm.png)

## 4 Compilation

### 4.1 In order to complie the project, select the project and ensure that it is [Active - Debug ] state.

![](./figures/YM6wXdr.png)

### 4.2 Click compilation icon at the menu bar to compile the project.

![](./figures/FVTw9CD.png)

![](./figures/M6OMuLM.png)

## 5 Terminal 

To access the development board, click terminal icon at the menu ba and select the correct serial port.

![](./figures/HFzLRi9.png)

## 6 Additional Info 

If you need addtional information, visit to 

https://www.rt-thread.io/document/site/programming-manual/interrupt/interrupt/

## 

###### Author
###### Stanley Lwin [04 / 11 / 2023]