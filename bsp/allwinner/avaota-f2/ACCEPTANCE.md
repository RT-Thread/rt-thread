# Avaota F2 / V861 验收（C907 侧）

## 已证实

- C907 单核交互
- C907 双核 SMP：`SMP-OK hart0=0 hart1=1`（solo，绑核到 hart1）
- DT UART（`uart-from-fdt`）
- 异构从核：magic / ping 应答；E907 侧见 `HETERO-OK`
- 硬件 MSGBOX 收门铃（`MSGBOX-OK`，或与 E907 `MSGBOX-LIVE` 配对）
- OpenAMP 形 slave：LINK + 三轮 payload echo（见 E907 `OPENAMP-EPT-OK`）
- MMC0 identify + 读扇区 0（solo `c907_boot`）：`mmc0 card OK` / `mmc0 read OK`，MBR `sig=55aa`
  - 证据：`mmc-uart-20261121-163257.log`（`PASS=True`）

## 未证实

- 文件系统 / DFS / 写块
- libmetal / virtio-rpmsg 全栈
- 主仓合入（以实际 PR 为准）

异构主入口与通过口见 `../avaota-f2-e907/ACCEPTANCE.md`。
