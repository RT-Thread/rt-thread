# USB 3.0 Host 控制器 (XHCI)

- Phytium PI 和 Phyium E2000 系列开发板提供符合 XHCI 1.1 规范的 USB 3.0 Host 控制器, 其它 Phytium 系列平台可以通过 PCIe 扩展卡获得 XHCI 控制器
- 相关的使用例程可以在 Phytium PI（飞腾派）、E2000 D/Q Demo 板以及 D2000 和后续平台上运行，例程包括

---------------------------------------------

- FreeRTOS

- - 1. [XHCI 平台控制器使用鼠标/键盘/U盘功能](https://gitee.com/phytium_embedded/phytium-free-rtos-sdk/tree/master/example/peripheral/usb/xhci_platform/README.md)
- - 2. [XHCI PCIe控制器使用鼠标/键盘/U盘功能](https://gitee.com/phytium_embedded/phytium-free-rtos-sdk/tree/master/example/peripheral/usb/xhci_pcie/README.md)
- - 3. [LVGL 中使用 XHCI 平台控制器连接的鼠标/键盘/U盘](https://gitee.com/phytium_embedded/phytium-free-rtos-sdk/blob/master/example/peripheral/media/lvgl_indev/README.md)

---------------------------------------------

- RT-Thread 

- - 1. [XHCI 平台控制器识别鼠标/键盘/U盘](https://github.com/RT-Thread/rt-thread/blob/master/bsp/phytium/doc/use_cherryusb.md)

---------------------------------------------

- Standalone 裸机

- - 暂不支持 

---------------------------------------------

- XHCI 的驱动功能以静态库的方式提供，仅限在 Phytium 系列 CPU 平台使用，

- - libxhci_a64.a : AARCH64 驱动库
- - libxhci_a32_hardfp.a : AARCH32 驱动库，使用硬浮点
- - libxhci_a32_softfp.a : AARCH32 驱动库，使用软浮点

需要获取源代码请联系 `opensource_embedded@phytium.com.cn` 获取，如需移植运行到非 Phytium 系列 CPU 平台请提前联系`opensource_embedded@phytium.com.cn`获得允许

# USB 3.0 Host Controller (XHCI)

- The Phytium PI and Phytium E2000 series development boards provide USB 3.0 Host controllers that conform to the XHCI 1.1 specification. Other Phytium series platforms can obtain XHCI controllers through PCIe expansion cards.
- Related example routines can be run on Phytium PI (Fetion Pi), E2000 D/Q Demo boards, and D2000 and later platforms. Examples include:

---------------------------------------------

- FreeRTOS

  - 1. [XHCI platform controller for mouse/keyboard/USB drive functions](https://gitee.com/phytium_embedded/phytium-free-rtos-sdk/tree/master/example/peripheral/usb/xhci_platform/README.md)
  - 2. [XHCI PCIe controller for mouse/keyboard/USB drive functions](https://gitee.com/phytium_embedded/phytium-free-rtos-sdk/tree/master/example/peripheral/usb/xhci_pcie/README.md)
  - 3. [Using XHCI platform controller-connected mouse/keyboard/USB drive in LVGL](https://gitee.com/phytium_embedded/phytium-free-rtos-sdk/blob/master/example/peripheral/media/lvgl_indev/README.md)

---------------------------------------------

- RT-Thread

  - 1. [XHCI platform controller recognizing mouse/keyboard/USB drive](https://github.com/RT-Thread/rt-thread/blob/master/bsp/phytium/doc/use_cherryusb.md)

---------------------------------------------

- Standalone (Bare Metal)

  - Not supported yet

---------------------------------------------

- This XHCI driver functionality is provided as a static library and is only available for Phytium series CPU platforms. 

  - - `libxhci_a64.a` : Driver library for AARCH64
  - - `libxhci_a32_hardfp.a` : Driver library for AARCH32, using hard floating point
  - - `libxhci_a32_softfp.a` : Driver library for AARCH32, using soft floating point

- To obtain the source code, please contact `opensource_embedded@phytium.com.cn`. 
- For porting to non-Phytium CPU platforms, shall contact `opensource_embedded@phytium.com.cn` in advance for permission.