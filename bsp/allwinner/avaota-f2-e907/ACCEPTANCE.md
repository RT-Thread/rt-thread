# Avaota F2 / V861 验收（E907 + 异构）

## 已证实

- E907 单核：banner + `avaota-f2 v861 e907` + `msh >`
- 拉起 C907；最小异构：`HETERO-OK`
- 硬件 MSGBOX（Tina DTB）：views `0x06020000` / `0x0800b000`，`ver=0x00020000`；门铃 `MSGBOX-OK` / `MSGBOX-LIVE`
- OpenAMP **形**端点（非 libmetal / virtio-rpmsg）：ept `avaota-ept`，SHM `@0x41001000`，LINK/QUEUE 踢醒 + 多字节回显
  - 证据：`openamp-uart-20261121-160325.log` → `[E907] OPENAMP-EPT-OK name=avaota-ept tx=3 rx=3`

## 未证实 / 不要宣称

- libmetal / 完整 OpenAMP、仓内 virtio-rpmsg、Linux remoteproc
- MMC 认卡、文件系统
- 已合入主仓（以实际 PR 为准）

## 冷链

1. `xfel version` → `V881`
2. `init_dram_efex.bin` @`0x100000` write + exec
3. `avaota-f2/rtthread.bin` @`0x40000000`
4. `avaota-f2-e907/rtthread.bin` @`0x42000000`
5. `xfel exec 0x42000000`
6. 串口 115200 8N1，DTR/RTS 关

## 通过口

串口出现 `[E907] OPENAMP-EPT-OK`（可附带 `HETERO-OK` / `MSGBOX-LIVE`）。缺 EPT 则记「端点通路未证实」。
