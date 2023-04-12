# [STM32F401] How to create a new project

:::info
:bulb: Download the latest RT-Thread studio from link -
https://www.rt-thread.io/studio.html 
and follow the instructions to install it on your windows machine. 
:::

### Create a new project

- Go to File -> Import.

![](https://i.imgur.com/HjMyZCg.png)


- Select RT-Thread Bsp Project into Workspace.

![](https://i.imgur.com/jcwFf24.png)

- Import Projects from BSP.

![](https://i.imgur.com/XZZOTbT.png)

- Browse Bsp Location to rt-threadx\bsp\stm32\stm32f401-st-nucleo, then click Select Folder.

![](https://i.imgur.com/osnThIA.png)

- Fill up the rest of the information and select ST-LINK for debugger. Then, click finish button. There will be a newly created project at the workspace. 

![](https://i.imgur.com/1sLBJ88.png)

![](https://i.imgur.com/0Z4ahmr.png)

![](https://i.imgur.com/o3kdLrx.png)

### Tool Chain

- Select the latest tool chain version to resolve the warning.

![](https://i.imgur.com/aqCQRRX.png)

![](https://i.imgur.com/CJ38q4n.png)

- **If** there is no latest tool chain version, click SDK manager to download the latest version.

![](https://i.imgur.com/rG3DJM6.png)

> - Select the latest version from the RT-Thread SDK Manager window and click install packages button. After installation, click Exit SDK Manger button again.

![](https://i.imgur.com/BNvMNzb.png)

> - Then select the latest version from the Open Build Settings Dialog.

### RT-Thread Setting

- In order to configure kernel and to enable add-on software packages, click RT-Thread Settings. Then, click detail button.

![](https://i.imgur.com/OOJq4U8.png)

![](https://i.imgur.com/jctYIJA.png)

![](https://i.imgur.com/bonMpvv.png)

- After configuration, click save to update the latest configuration.

![](https://i.imgur.com/yubp4yc.png)

![](https://i.imgur.com/Bz4BwWm.png)

### Compilation

- In order to complie the project, select the project and ensure that it is [Active - Debug ] state.

![](https://i.imgur.com/YM6wXdr.png)

- Click compilation icon at the menu bar to compile the project.

![](https://i.imgur.com/FVTw9CD.png)

![](https://i.imgur.com/M6OMuLM.png)

### Terminal 

- To access the development board, click terminal icon at the menu ba and select the correct serial port.

![](https://i.imgur.com/HFzLRi9.png)

### Additional Info 

- If you need addtional information, visit to 

https://www.rt-thread.io/document/site/programming-manual/interrupt/interrupt/


## 
###### Author
###### Stanley Lwin [04 / 11 / 2023]