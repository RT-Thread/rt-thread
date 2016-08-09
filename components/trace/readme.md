##How to use the Segger SystemView trace componment

### 1. Copy description file
Copy the '.\SystemView_Src_Vxxx\Description\SYSVIEW_RTThread.txt' to folder '%SystemView_Install_Folder%\Description\'.
### 2. Enable trace componment
Add `RT_USING_TRACE` define in your bsp's rtconfig.h
```c
// <bool name="RT_USING_TRACE" description="Enable trace" default="true" />
#define RT_USING_TRACE
```
### 3. Connect to target board debug interface
Segger SystemView only support Segger J-Link and Segger J-Link OB. If you using the origin development boards from vendor, you can upgrade the on board debugger to J-Link OB.

* For ST ST-Link, here is the [ST-Link upgrade utility download page](https://www.segger.com/jlink-st-link.html)
* For Atmel EDBG, here is the [EDBG upgrade utility download page](https://www.segger.com/jlink-edbg.html)
* For Freescale(NXP) OpenSDA/OpenSDA-V2, here is the [OpenSDA upgrade utility download page](https://www.segger.com/opensda.html)
* For NXP LPC Link 2, here is the [LPC link 2 upgrade utility download page](https://www.segger.com/lpc-link-2.html)
* NXP LPCXpresso, here is the [LPCXpresso upgrade utility download page](https://www.segger.com/jlink-lpcxpresso-ob.html)

### 4. Intergration (Porting) limitation

* Can only trace thread, scheduler and interrupt. 
* Tracing RT-Thread IPC componment is not supported.
