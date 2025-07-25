## 概述

CSI 是针对嵌入式系统，定义了CPU内核移植 接口、外围设备操作接口统一软件接口规范，消除不同芯片的差异，简化软件的使用及提高软件的移植性。通过CSI 接口规范，可以快>速实现芯片对接到YoC 平台。

CSI 的具体内容包括：

-  **CSI-CORE**：定义了CPU和相关紧耦合外设的接口规范
-  **CSI-DRIVER**：定义了常用的驱动的接口规范
-  **CSI-KERNEL**： 定义实时操作系统的接口规范


## 组件安装

```bash
yoc init
yoc install csi
```

## 接口

[CSI接口描述](https://www.xrvm.cn/document?temp=csi&slug=csi-chn)
