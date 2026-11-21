# Avaota F2 E907 — 验收边界（PR 阶段 B）

## 本阶段宣称

- E907 上 RT-Thread：banner + UART/`msh`
- E907 拉起 C907 后，DRAM 槽最小异构：`HETERO-OK`
- 同槽多轮往返：`RPMSG-OK`（**非** OpenAMP）

## 本阶段不宣称

- 硬件 MSGBOX 门铃
- 完整 OpenAMP / virtio-rpmsg
- MMC / 文件系统
