# 📊 RT-Thread BSP Support Summary

This document is based on the RT-Thread mainline repository and categorizes the driver support status by architecture and chip vendor series.

## 📋 Legend

**Maintenance Status**:
- 🟢 **Actively Maintained**: BSPs jointly and actively maintained by RT-Thread official and the chip manufacturer.
- 🟡 **Well Maintained**: BSPs maintained by the RT-Thread open-source community.
- ⚪ **Basic Support**: BSPs with limited maintenance support.

**Support Status**: ✅ indicates supported, - indicates not supported or not mentioned.

---

## BSP Support Summary

### ARM Architecture Series

#### 🟢 Infineon

| BSP Name | GPIO | UART | ADC | DAC | Ethernet | FLASH | I2C | HWTimer | PWM | RTC | SD Card | Soft I2C | SPI | WDT |
|----------|------|------|-----|-----|----------|-------|-----|---------|-----|-----|---------|----------|-----|-----|
| [psoc6-cy8ckit-062-BLE](Infineon/psoc6-cy8ckit-062-BLE) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [psoc6-cy8ckit-062-WIFI-BT](Infineon/psoc6-cy8ckit-062-WIFI-BT) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [psoc6-cy8ckit-062S2-43012](Infineon/psoc6-cy8ckit-062S2-43012) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [psoc6-cy8ckit-062s4](Infineon/psoc6-cy8ckit-062s4) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [psoc6-cy8cproto-062S3-4343W](Infineon/psoc6-cy8cproto-062S3-4343W) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [psoc6-evaluationkit-062S2](Infineon/psoc6-evaluationkit-062S2) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [psoc6-pioneerkit_modus](Infineon/psoc6-pioneerkit_modus) | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - |
| [xmc7100d-f144k4160aa](Infineon/xmc7100d-f144k4160aa) | ✅ | ✅ | - | - | - | - | ✅ | - | - | - | - | - | ✅ | - |
| [xmc7200-kit_xmc7200_evk](Infineon/xmc7200-kit_xmc7200_evk) | ✅ | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - |

#### 🟢 Renesas

| BSP Name | GPIO | UART | ADC | CAN | CANFD | DAC | Ethernet | HWTimer | I2C | PWM | RTC | SPI | Soft SPI | Flash | SDHI | SCI | SDRAM | LCD | **RS485** | Other |
|----------|------|------|-----|-----|-------|-----|----------|---------|-----|-----|-----|-----|----------|-------|------|-----|-------|-----|-------|-------|
| [ebf_qi_min_6m5](renesas/ebf_qi_min_6m5) | ✅ | ✅ | ✅ | - | - | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | - |
| [ra2a1-ek](renesas/ra2a1-ek) | ✅ | ✅ | ✅ | - | - | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | - |
| [ra2e2-ek](renesas/ra2e2-ek) | ✅ | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - |
| [ra2l1-cpk](renesas/ra2l1-cpk) | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |
| [ra4e2-eco](renesas/ra4e2-eco) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - |
| [ra4e2-ek](renesas/ra4e2-ek) | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [ra4m1-ek](renesas/ra4m1-ek) | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - |
| [ra4m2-eco](renesas/ra4m2-eco) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | ✅ | - | - | - | ✅ | - | - | - | - |
| [ra6e2-ek](renesas/ra6e2-ek) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [ra6e2-fpb](renesas/ra6e2-fpb) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [ra6m3-ek](renesas/ra6m3-ek) | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | ✅ | - | - |
| [ra6m3-hmi-board](renesas/ra6m3-hmi-board) | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [ra6m4-cpk](renesas/ra6m4-cpk) | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | - | - | ✅ |
| [ra6m4-iot](renesas/ra6m4-iot) | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | - | - | - |
| [ra8d1-ek](renesas/ra8d1-ek) | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ |
| [ra8d1-vision-board](renesas/ra8d1-vision-board) | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ |
| [ra8p1-titan-board](renesas/ra8p1-titan-board) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [ra8m1-ek](renesas/ra8m1-ek) | ✅ | ✅ | ✅ | - | - | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |
| [rzn2l_etherkit](renesas/rzn2l_etherkit) | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |
| [rzn2l_rsk](renesas/rzn2l_rsk) | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | - | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |
| [rzt2m_rsk](renesas/rzt2m_rsk) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |

#### 🟢 STM32

| BSP Name | GPIO | UART | ADC | CAN | DAC | CANFD | Ethernet | HWTimer | I2C | PWM | RTC | SPI | Soft SPI | Flash | SDIO | SCI | WDT | LCD | LPTIM | Pulse Encoder | NAND | LCD MIPI | QSPI | PM | USBD | SDMMC | USBH |
|----------|------|------|-----|-----|-----|-------|----------|---------|-----|-----|-----|-----|----------|-------|------|-----|-----|-----|-------|---------------|------|----------|------|----|------|-------|------|
| [stm32f072-st-nucleo](stm32/stm32f072-st-nucleo) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | - | - | - | - | - |
| [stm32f091-st-nucleo](stm32/stm32f091-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | ✅ |
| [stm32f103-100ask-mini](stm32/stm32f103-100ask-mini) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | ✅ | - | - | - |
| [stm32f103-100ask-pro](stm32/stm32f103-100ask-pro) | ✅ | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f103-atk-nano](stm32/stm32f103-atk-nano) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32f103-atk-warshipv3](stm32/stm32f103-atk-warshipv3) | ✅ | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - |
| [stm32f103-blue-pill](stm32/stm32f103-blue-pill) | ✅ | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | ✅ | - | - |
| [stm32f103-dofly-M3S](stm32/stm32f103-dofly-M3S) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | - | ✅ | - | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f103-dofy-lyc8](stm32/stm32f103-dofy-lyc8) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f103-fire-arbitrary](stm32/stm32f103-fire-arbitrary) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | - |
| [stm32f103-gizwits-gokitv21](stm32/stm32f103-gizwits-gokitv21) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f103-hw100k-ibox](stm32/stm32f103-hw100k-ibox) | ✅ | ✅ | ✅ | - | - | - | ✅ | - | ✅ | - | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32f103-keysking-leaming](stm32) | ✅ | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | - | - | - | - | - | - | - | - | - | ✅ | - | - | - | - | - | - | - |
| [stm32f103-onenet-nbiot](stm32/stm32f103-onenet-nbiot) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f103-yf-ufun](stm32/stm32f103-yf-ufun) | ✅ | ✅ | - | - | - | - | - | - | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f103-ys-f1pro](stm32/stm32f103-ys-f1pro) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f107-uc-eval](stm32/stm32f107-uc-eval) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f207-st-nucleo](stm32/stm32f207-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f302-st-nucleo](stm32/stm32f302-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f334-st-nucleo](stm32/stm32f334-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f401-st-nucleo](stm32/stm32f401-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f401-weact-blackpill](stm32/stm32f401-weact-blackpill) | ✅ | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f405-smdz-breadfruit](stm32/stm32f405-smdz-breadfruit) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f405zg-mini-template](stm32/stm32f405zg-mini-template) | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f407-armfly-v5](stm32/stm32f407-armfly-v5) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32f407-atk-explorer](stm32/stm32f407-atk-explorer) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | - | ✅ | - | ✅ |
| [stm32f407-fk407m2-zgt6](stm32/stm32f407-fk407m2-zgt6) | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | ✅ | - | ✅ |
| [stm32f407-lckfb-skystar](stm32/stm32f407-lckfb-skystar) | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | ✅ | ✅ | - | - |
| [stm32f407-micu](stm32/stm32f407-micu) | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | - | - | - | - |
| [stm32f407-robomaster-c](stm32/stm32f407-robomaster-c) | ✅ | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f407-rt-spark](stm32/stm32f407-rt-spark) | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | ✅ | - | ✅ |
| [stm32f407-st-discovery](stm32/stm32f407-st-discovery) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f410-st-nucleo](stm32/stm32f410-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f411-atk-nano](stm32/stm32f411-atk-nano) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32f411-st-nucleo](stm32/stm32f411-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32f411-weact-blackpill](stm32/stm32f411-weact-blackpill) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | ✅ | - | - |
| [stm32f412-st-nucleo](stm32/stm32f412-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | ✅ | - | - |
| [stm32f413-st-nucleo](stm32/stm32f413-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | ✅ | - | - |
| [stm32f427-robomaster-a](stm32/stm32f427-robomaster-a) | ✅ | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | - | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f429-armfly-v6](stm32/stm32f429-armfly-v6) | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | - | - | - | - | - | - | - | - |
| [stm32f429-atk-apollo](stm32/stm32f429-atk-apollo) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | ✅ |
| [stm32f429-fire-challenger](stm32/stm32f429-fire-challenger) | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | - | - | - | - | - | - | - | - |
| [stm32f429-st-disco](stm32/stm32f429-st-disco) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | - | ✅ | - | - | - | - | - | ✅ | - | - | - | - | ✅ | - | ✅ | - | - |
| [stm32f446-st-nucleo](stm32/stm32f446-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f469-st-disco](stm32/stm32f469-st-disco) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | - | - | ✅ | - | - | - | - | ✅ | - | ✅ | - | - |
| [stm32f723-st-disco](stm32/stm32f723-st-disco) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f746-st-disco](stm32/stm32f746-st-disco) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | - | ✅ | ✅ | - | - | - | - | ✅ | - | - | - | - |
| [stm32f746-st-nucleo](stm32/stm32f746-st-nucleo) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | ✅ | ✅ | - | - |
| [stm32f767-atk-apollo](stm32/stm32f767-atk-apollo) | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | - | - | - | ✅ |
| [stm32f767-fire-challenger-v1](stm32/stm32f767-fire-challenger-v1) | ✅ | ✅ | ✅ | - | - | - | - | - | ✅ | - | ✅ | - | - | ✅ | ✅ | - | ✅ | ✅ | - | - | - | - | ✅ | - | - | - | - |
| [stm32f767-st-nucleo](stm32/stm32f767-st-nucleo) | ✅ | ✅ | - | - | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32f769-st-disco](stm32/stm32f769-st-disco) | ✅ | ✅ | - | - | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32g030-tiny-board](stm32/stm32g030-tiny-board) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32g070-st-nucleo](stm32/stm32g070-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32g071-st-nucleo](stm32/stm32g071-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32g431-st-nucleo](stm32/stm32g431-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32g474-st-nucleo](stm32/stm32g474-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32g491-st-nucleo](stm32/stm32g491-st-nucleo) | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | - | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32h503-st-nucleo](stm32/stm32h503-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32h563-st-nucleo](stm32/stm32h563-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32h723-lxb-disco](stm32) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32h723-st-nucleo](stm32/stm32h723-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32h730-esphosted-evb](stm32/stm32h730-esphosted-evb) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32h743-armfly-v7](stm32/stm32h743-armfly-v7) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32h743-atk-apollo](stm32/stm32h743-atk-apollo) | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | - | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | - | - | ✅ | - | - | - | - | - |
| [stm32h743-openmv-h7plus](stm32/stm32h743-openmv-h7plus) | ✅ | ✅ | - | - | - | - | - | - | ✅ | ✅ | ✅ | - | - | - | ✅ | - | - | - | - | - | - | - | ✅ | - | ✅ | - | - |
| [stm32h743-st-nucleo](stm32/stm32h743-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32h747-st-discovery](stm32/stm32h747-st-discovery) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - |
| [stm32h750-armfly-h7-tool](stm32/stm32h750-armfly-h7-tool) | ✅ | ✅ | ✅ | - | - | - | ✅ | - | ✅ | ✅ | - | - | - | - | ✅ | - | - | ✅ | - | - | - | - | ✅ | - | ✅ | - | - |
| [stm32h750-artpi](stm32/stm32h750-artpi) | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | - | - | - | ✅ | - | ✅ | - | ✅ |
| [stm32h750-fk750m1-vbt6](stm32/stm32h750-fk750m1-vbt6) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | - | ✅ | - | - | - | - |
| [stm32h750-weact-ministm32h7xx](stm32/stm32h750-weact-ministm32h7xx) | ✅ | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | - | - | ✅ | - | - | - | - | - | ✅ | ✅ | - | - |
| [stm32h7r7-artpi2](stm32/stm32h7r7-artpi2) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | ✅ | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | ✅ | - | ✅ |
| [stm32h7s7-st-disco](stm32/stm32h7s7-st-disco) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | ✅ | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | ✅ | - | ✅ |
| [stm32l010-st-nucleo](stm32/stm32l010-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32l053-st-nucleo](stm32/stm32l053-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32l412-st-nucleo](stm32/stm32l412-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | ✅ | - | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32l431-BearPi](stm32/stm32l431-BearPi) | ✅ | ✅ | ✅ | - | ✅ | - | - | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | ✅ | - | - | - | - | - | - | - | - | - |
| [stm32l431-tencentos-tiny-EVB_MX+](stm32/stm32l431-tencentos-tiny-EVB_MX+) | ✅ | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | ✅ | ✅ | - | - | ✅ | - | - | - | - | - | - | - | ✅ | - | - | - | - |
| [stm32l432-st-nucleo](stm32/stm32l432-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | ✅ | - | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32l433-ali-startkit](stm32/stm32l433-ali-startkit) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32l433-st-nucleo](stm32/stm32l433-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32l452-st-nucleo](stm32/stm32l452-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | - | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32l475-atk-pandora](stm32/stm32l475-atk-pandora) | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | - | - | - | ✅ | - | ✅ | - | - |
| [stm32l475-st-discovery](stm32/stm32l475-st-discovery) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32l476-st-nucleo](stm32/stm32l476-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32l496-ali-developer](stm32/stm32l496-ali-developer) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [stm32l496-st-discovery](stm32/stm32l496-st-discovery) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32l496-st-nucleo](stm32/stm32l496-st-nucleo) | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | ✅ | - | ✅ | - | - |
| [stm32l4r5-st-nucleo](stm32/stm32l4r5-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | ✅ | - | - |
| [stm32l4r9-st-eval](stm32/stm32l4r9-st-eval) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | - | - | - | - | - | - | - | ✅ | - | - | - | - | - | - | - | - | - |
| [stm32l4r9-st-sensortile-box](stm32/stm32l4r9-st-sensortile-box) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | ✅ | - | - |
| [stm32l552-st-nucleo](stm32/stm32l552-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32mp157a-st-discovery](stm32/stm32mp157a-st-discovery) | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | ✅ | - | - | - |
| [stm32mp157a-st-ev1](stm32/stm32mp157a-st-ev1) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | - | ✅ | - | - | - | ✅ | - | ✅ | ✅ | - | - | - |
| [stm32u575-st-nucleo](stm32/stm32u575-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32u585-iot02a](stm32/stm32u585-iot02a) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32wb55-st-nucleo](stm32/stm32wb55-st-nucleo) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32wl55-st-nucleo](stm32/stm32wl55-st-nucleo) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32wle5-yizhilian-lm401](stm32/stm32wle5-yizhilian-lm401) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [stm32wle5-yizhilian-lm402](stm32/stm32wle5-yizhilian-lm402) | ✅ | ✅ | - | - | - | - | - | - | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |

#### 🟢 NXP

| BSP Name | GPIO | UART | ADC | CAN | DAC | Ethernet | Flash | HWTimer | I2C | LCD | NAND | PWM | RTC | SD Card | SDIO | SDMMC | Soft I2C | Soft SPI | SPI | SPIM | USBD | USBH | WDT |
|----------|------|------|-----|-----|-----|----------|-------|---------|-----|-----|------|-----|-----|---------|------|-------|----------|----------|-----|------|------|------|-----|
| [imx6sx](nxp/imx/imx6sx) | - | ✅ | - | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [imx6ul](nxp/imx/imx6ul) | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [imx6ull-smart (RT-Smart)](nxp/imx/imx6ull-smart) | ✅ | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | ✅ | - | ✅ |
| [imxrt1021-nxp-evk](nxp/imx/imxrt/imxrt1021-nxp-evk) | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - |
| [imxrt1052-atk-commander](nxp/imx/imxrt/imxrt1052-atk-commander) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | ✅ | - | ✅ | - | - |
| [imxrt1052-fire-pro](nxp/imx/imxrt/imxrt1052-fire-pro) | ✅ | ✅ | - | ✅ | - | - | - | ✅ | ✅ | - | - | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - |
| [imxrt1052-nxp-evk](nxp/imx/imxrt/imxrt1052-nxp-evk) | ✅ | ✅ | - | - | - | ✅ | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [imxrt1052-seeed-ArchMix](nxp/imx/imxrt/imxrt1052-seeed-ArchMix) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | ✅ | - | - | - | - |
| [imxrt1060-nxp-evk](nxp/imx/imxrt/imxrt1060-nxp-evk) | ✅ | ✅ | - | - | - | ✅ | - | - | ✅ | ✅ | - | - | ✅ | - | ✅ | - | - | - | ✅ | - | - | ✅ | - |
| [imxrt1061-forlinx-OK1061-S](nxp/imx/imxrt/imxrt1061-forlinx-OK1061-S) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [imxrt1064-nxp-evk](nxp/imx/imxrt/imxrt1064-nxp-evk) | ✅ | ✅ | - | - | - | ✅ | - | - | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [imxrt1170-nxp-evk](nxp/imx/imxrt/imxrt1170-nxp-evk) | ✅ | ✅ | - | ✅ | - | ✅ | - | - | - | - | - | - | ✅ | - | ✅ | - | - | - | ✅ | - | - | ✅ | - |
| [lpc1114](nxp/lpc/lpc1114) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [lpc176x](nxp/lpc/lpc176x) | ✅ | ✅ | - | - | - | ✅ | - | - | - | - | - | - | - | - | ✅ | - | - | - | ✅ | - | - | - | - |
| [lpc178x](nxp/lpc/lpc178x) | ✅ | ✅ | - | - | - | ✅ | - | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [lpc2148](nxp/lpc/lpc2148) | - | ✅ | - | - | - | ✅ | - | - | - | - | - | - | - | - | ✅ | - | - | - | - | - | - | - | - |
| [lpc408x](nxp/lpc/lpc408x) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [lpc43xx](nxp/lpc/lpc43xx) | - | ✅ | - | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [lpc5114-lite](nxp) | ✅ | ✅ | - | - | - | - | - | - | ✅ | - | - | - | - | - | ✅ | - | - | - | ✅ | - | - | - | - |
| [lpc54608-LPCXpresso](nxp/lpc/lpc54608-LPCXpresso) | ✅ | ✅ | - | - | - | - | - | - | - | ✅ | - | - | - | - | ✅ | - | - | - | - | - | - | - | - |
| [lpc5s06_nxp_evk](nxp) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |
| [lpc5s16_nxp_evk](nxp) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |
| [lpc5s28_nxp_evk](nxp) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |
| [lpc5s36_nxp_evk](nxp) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |
| [lpc5s69_nxp_evk](nxp) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |
| [lpc824](nxp/lpc/lpc824) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [frdm-mcxa153](nxp/mcx/mcxa/frdm-mcxa153) | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | ✅ | - | - | ✅ | - | - | - | - | - | - | ✅ | - | - | - | ✅ |
| [frdm-mcxa156](nxp/mcx/mcxa/frdm-mcxa156) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | - | ✅ |
| [frdm-mcxa346](nxp/mcx/mcxa/frdm-mcxa346) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | - | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | - | ✅ |
| [frdm-mcxc444](nxp/mcx/mcxc/frdm-mcxc444) | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | - | - | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | - | ✅ |
| [frdm-mcxe247](nxp/mcx/mcxe/frdm-mcxe247) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | - | - | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | - | ✅ |
| [frdm-mcxn236](nxp/mcx/mcxn/frdm-mcxn236) | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | - | - | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | - | ✅ |
| [frdm-mcxn947](nxp/mcx/mcxn/frdm-mcxn947) | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | ✅ | ✅ | ✅ |

#### 🟢 GD32

| BSP Name | GPIO | UART | ADC | CAN | I2C | HWTimer | PWM | RTC | SDIO | SDRAM | SPI | SPI Flash | WDT |
|----------|------|------|-----|-----|-----|---------|-----|-----|------|-------|-----|----------|-----|
| [gd32103c-eval](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32105c-eval](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32105r-start](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32107c-eval](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32205r-start](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32207i-eval](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32303c-start](gd32) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - |
| [gd32303e-eval](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32305r-start](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32307e-start](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32405rg](gd32) | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32407v-ickfb](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32407v-start](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32450z-eval](gd32) | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32470i-eval](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ |
| [gd32470z-ickfb](gd32) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ |
| [gd32527l-eval](gd32/gd32527l-eval) | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ |
| [gd32e230-lckfb](gd32/gd32e230-lckfb) | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | ✅ | - | ✅ |
| [gd32e503v-eval](gd32/gd32e503v-eval) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | - | ✅ | - | ✅ |
| [gd32h759i-eval](gd32/gd32h759i-eval) | ✅ | ✅ | - | - | ✅ | - | - | - | - | - | ✅ | - | - |
| [gd32h759i-start](gd32/gd32h759i-start) | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | - | - | - |
| [gd32vf103r-start](gd32/gd32vf103r-start) | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | ✅ | - | ✅ |
| [gd32vf103v-eval](gd32/gd32vf103v-eval) | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | - | - | ✅ | - | ✅ |

#### 🟢 CVITEK (RT-Smart)

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | HWTimer | PWM | RTC | SDH | Ethernet |
|----------|------|------|-----|-----|-----|-----|---------|-----|-----|-----|----------|
| [c906_little](cvitek/c906_little) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | - |
| [cv18xx_aarch64 (RT-Smart)](cvitek/cv18xx_aarch64) | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - | - |
| [milkv-duo](cvitek/milkv-duo) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [milkv-duo256m](cvitek/milkv-duo256m) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [milkv-duos](cvitek/milkv-duos) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### 🟢 QEMU VExpress A9 (RT-Smart) (SMP)

| BSP Name | GPIO | UART | LCD | Keyboard | Mouse | SDIO | Timer | RTC | VirtIO |
|----------|------|------|-----|----------|-------|------|-------|-----|--------|
| [qemu-vexpress-a9](qemu-vexpress-a9) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | - |

#### 🟢 QEMU Virt64 AArch64 (RT-Smart) (SMP)

| BSP Name | GPIO | UART | RTC | VirtIO-BLK | VirtIO-NET | VirtIO-Console | VirtIO-GPU | VirtIO-Input |
|----------|------|------|-----|-----------|-----------|---------------|-----------|--------------|
| [qemu-virt64-aarch64](qemu-virt64-aarch64) | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |

#### 🟡 Phytium (RT-Smart) (SMP)

| BSP Name | GPIO | UART | ADC | CAN | I2C | SPI | QSPI | PWM | Timer | WDT | MIO | TACHO |
|----------|------|------|-----|-----|-----|-----|------|-----|-------|-----|-----|-------|
| [e2000d-demo](phytium) | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - |
| [e2000q-demo](phytium) | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - |
| [phytiumpi-firefly](phytium) | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [pd2408-test-a](phytium) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - |
| [pd2408-test-b](phytium) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - |

#### 🟡 Raspberry Pico (SMP)

| BSP Name | GPIO | UART | I2C | SPI | ADC | WDT | RTC | PWM | Onchip Flash | HWTimer |
|----------|------|------|-----|-----|-----|-----|-----|-----|-------------|---------|
| [RP2040](raspberry-pico/RP2040) | ✅ | ✅ | - | - | - | - | - | - | - | - |
| [RP2350](raspberry-pico/RP2350) | ✅ | ✅ | - | - | - | - | - | - | - | - |

#### 🟡 Raspberry Pi

| BSP Name | GPIO | UART | I2C | SPI | RTC | SD Card | SDIO | MailBox | WDT | SMP | HDMI | Timer | Bluetooth | Ethernet | MIPI DSI | ILI9486 SPI LCD | XPT2046 TOUCH |
|----------|------|------|-----|-----|-----|---------|------|---------|-----|-----|------|-------|-----------|----------|----------|-----------------|----------------|
| [raspi-dm2.0](raspberry-pi/raspi-dm2.0) | - | ✅ | - | - | - | ✅ | - | - | - | - | - | - | - | - | - | - | - |
| [raspi2](raspberry-pi/raspi2) | - | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [raspi3-32](raspberry-pi/raspi3-32) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | - | - | - |
| [raspi3-64](raspberry-pi/raspi3-64) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | - | - | - | - |
| [raspi4-32](raspberry-pi/raspi4-32) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [raspi4-64](raspberry-pi/raspi4-64) | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - |

#### 🟡 AT32

| BSP Name | GPIO | UART | ADC | CAN | DAC | Ethernet | Flash | HWTimer | I2C | PWM | QSPI | RTC | SDIO | SDRAM | Soft I2C | SPI | USBD | USBOTG | WDT |
|----------|------|------|-----|-----|-----|----------|-------|---------|-----|-----|------|-----|------|-------|----------|-----|------|--------|-----|
| [at32a403a-start](at32/at32a403a-start) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | ✅ |
| [at32a423-start](at32/at32a423-start) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | ✅ | ✅ |
| [at32f402-start](at32/at32f402-start) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - |
| [at32f403a-start](at32/at32f403a-start) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | ✅ |
| [at32f405-start](at32/at32f405-start) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | - | ✅ | ✅ |
| [at32f407-start](at32/at32f407-start) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | - |
| [at32f413-start](at32/at32f413-start) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | ✅ |
| [at32f415-start](at32/at32f415-start) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | ✅ |
| [at32f421-start](at32/at32f421-start) | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | - | ✅ |
| [at32f423-start](at32/at32f423-start) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | ✅ | ✅ |
| [at32f425-start](at32/at32f425-start) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | ✅ | ✅ |
| [at32f435-start](at32/at32f435-start) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ |
| [at32f437-start](at32/at32f437-start) | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ |
| [at32f455-start](at32/at32f455-start) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ |
| [at32f456-start](at32/at32f456-start) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ |
| [at32f457-start](at32/at32f457-start) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ |
| [at32m412-start](at32/at32m412-start) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | - | ✅ |
| [at32m416-start](at32/at32m416-start) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | ✅ | - | - | ✅ |

#### 🟡 HC32

| BSP Name | GPIO | UART | ADC | CAN | DAC | Ethernet | Flash | HWTimer | I2C | NAND | PM | Pulse Encoder | USBD | QSPI | PWM | SDIO | RTC | Soft I2C | SDRAM | USBH | SPI | WDT |
|----------|------|------|-----|-----|-----|----------|-------|---------|-----|------|----|-------------|------|------|-----|------|-----|----------|-------|------|-----|-----|
| [ev_hc32f334_lqfp64](hc32/ev_hc32f334_lqfp64) | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | - | ✅ | ✅ | - | - | ✅ | - | ✅ | - | - | - | ✅ | ✅ |
| [ev_hc32f448_lqfp80](hc32/ev_hc32f448_lqfp80) | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ | ✅ |
| [ev_hc32f460_lqfp100_v2](hc32/ev_hc32f460_lqfp100_v2) | ✅ | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ |
| [ev_hc32f472_lqfp100](hc32/ev_hc32f472_lqfp100) | ✅ | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ |
| [ev_hc32f4a0_lqfp176](hc32/ev_hc32f4a0_lqfp176) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ |
| [ev_hc32f4a8_lqfp176](hc32/ev_hc32f4a8_lqfp176) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ |
| [lckfb-hc32f4a0-lqfp100](hc32/lckfb-hc32f4a0-lqfp100) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ |

#### 🟡 N32

| BSP Name | GPIO | UART | ADC | CAN | DAC | HWTimer | I2C | RTC | SPI | WDT |
|----------|------|------|-----|-----|-----|---------|-----|-----|-----|-----|
| [n32g43xcl-stb](n32/n32gxx_lxx/n32g43xcl-stb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32g457gel-stb](n32/n32gxx_lxx/n32g457gel-stb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32g45xcl-stb](n32/n32gxx_lxx/n32g45xcl-stb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32g45xml-stb](n32/n32gxx_lxx/n32g45xml-stb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32g45xrl-stb](n32/n32gxx_lxx/n32g45xrl-stb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32g45xvl-stb](n32/n32gxx_lxx/n32g45xvl-stb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32g47rml-stb](n32/n32gxx_lxx/n32g47rml-stb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32l40xcl-stb](n32/n32gxx_lxx/n32l40xcl-stb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32l436-evb](n32/n32gxx_lxx/n32l436-evb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32l43xml-stb](n32/n32gxx_lxx/n32l43xml-stb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32l43xrl-stb](n32/n32gxx_lxx/n32l43xrl-stb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32wb45xl-evb](n32/n32gxx_lxx/n32wb45xl-evb) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [n32h760zil7-stb](n32/n32hxxx/n32h760zil7-stb) | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | ✅ | - |

#### 🟡 NRF5x

| BSP Name | GPIO | UART | ADC | QSPI Flash | HWTimer | I2C | PWM | RTC | SPI | SPIM | WDT |
|----------|------|------|-----|-----------|---------|-----|-----|-----|-----|------|-----|
| [nrf51822](nrf5x/nrf51822) | ✅ | ✅ | - | - | - | - | - | - | - | - | - |
| [nrf52832](nrf5x/nrf52832) | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [nrf52833](nrf5x/nrf52833) | ✅ | ✅ | - | - | - | - | - | - | - | - | - |
| [nrf52840](nrf5x/nrf52840) | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [nrf5340](nrf5x/nrf5340) | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ |

#### 🟡 Rockchip

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | HWTimer | PWM | RTC | SDIO | CAN | PCI |
|----------|------|------|-----|-----|-----|-----|---------|-----|-----|------|-----|------|
| [rk2108](rockchip/rk2108) | - | ✅ | - | - | - | - | - | - | - | - | - | - |
| [rk3300](rockchip/rk3300) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - |
| [rk3500](rockchip/rk3500) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### 🟡 APM32

| BSP Name | GPIO | UART | ADC | CAN | DAC | Ethernet | HWTimer | I2C_SW | PWM | RTC | SPI | Flash | WDT | SDIO | Other |
|----------|------|------|-----|-----|-----|----------|---------|--------|-----|-----|-----|-------|-----|------|-------|
| [apm32e103ze-evalboard](apm32/apm32e103ze-evalboard) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - |
| [apm32e103ze-tinyboard](apm32/apm32e103ze-tinyboard) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - |
| [apm32f030r8-miniboard](apm32/apm32f030r8-miniboard) | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [apm32f051r8-evalboard](apm32/apm32f051r8-evalboard) | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [apm32f072vb-miniboard](apm32/apm32f072vb-miniboard) | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [apm32f091vc-miniboard](apm32/apm32f091vc-miniboard) | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [apm32f103vb-miniboard](apm32/apm32f103vb-miniboard) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [apm32f103xe-miniboard](apm32/apm32f103xe-miniboard) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [apm32f107vc-evalboard](apm32/apm32f107vc-evalboard) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [apm32f407ig-miniboard](apm32/apm32f407ig-miniboard) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [apm32f407zg-evalboard](apm32/apm32f407zg-evalboard) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [apm32s103vb-miniboard](apm32/apm32s103vb-miniboard) | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |

#### 🟡 Nuvoton

| BSP Name | GPIO | UART | ADC | PWM | CRC | Crypto | FMC | I2C | Soft I2C | RTC | QSPI | SPI | HWTimer | WDT | USBD | USBH | LCD | SDIO | CANFD | I2S | WHC | Ethernet |
|----------|------|------|-----|-----|-----|--------|-----|-----|----------|-----|------|-----|---------|-----|------|------|-----|------|-------|-----|-----|----------|
| [ma35-rtp](nuvoton/ma35-rtp) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [nk-980iot](nuvoton/nk-980iot) | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | ✅ | - | - | - | ✅ | ✅ | - | ✅ | - | - | - | ✅ |
| [nk-n9h30](nuvoton/nk-n9h30) | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | - | - | - | ✅ |
| [nk-rtu980](nuvoton/nk-rtu980) | ✅ | ✅ | - | - | - | - | - | - | - | - | ✅ | - | - | - | ✅ | ✅ | - | - | - | - | - | ✅ |
| [numaker-hmi-ma35d1](nuvoton/numaker-hmi-ma35d1) | ✅ | ✅ | - | ✅ | - | - | - | ✅ | - | - | ✅ | - | - | - | - | ✅ | ✅ | ✅ | - | - | - | - |
| [numaker-iot-m467](nuvoton/numaker-iot-m467) | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | - | - | - | ✅ |
| [numaker-iot-m487](nuvoton/numaker-iot-m487) | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | - | - | - | ✅ |
| [numaker-iot-ma35d1](nuvoton/numaker-iot-ma35d1) | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | ✅ | - | - | - | - | ✅ | - | ✅ | - | - | - | ✅ |
| [numaker-m032ki](nuvoton/numaker-m032ki) | ✅ | ✅ | - | - | - | - | - | - | - | - | ✅ | - | - | - | - | - | ✅ | - | - | - | - | - |
| [numaker-m2354](nuvoton/numaker-m2354) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | ✅ | ✅ | ✅ | ✅ | - | - | - | - |
| [numaker-m467hj](nuvoton/numaker-m467hj) | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ |
| [numaker-pfm-m487](nuvoton/numaker-pfm-m487) | ✅ | ✅ | - | - | - | - | - | ✅ | - | - | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | - | - | - | ✅ |

#### 🟡 ESSEMI

| BSP Name | GPIO | UART | ADC | CAN | Ethernet | Flash | HWTimer | I2C | LCD | PWM | RTC | SPI | SD Card | Other |
|----------|------|------|-----|-----|----------|-------|---------|-----|-----|-----|-----|-----|---------|-------|
| [es32f0654](essemi/es32f0654) | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ |
| [es32f365x](essemi/es32f365x) | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | - |
| [es32f369x](essemi/es32f369x) | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | - |
| [es32vf2264](essemi/es32vf2264) | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | - | - |

#### 🟡 HT32

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [ht32f12366](ht32/ht32f12366) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [ht32f52352](ht32/ht32f52352) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [ht32f53252](ht32/ht32f53252) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### ⚪ Microchip

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [samc21](microchip/samc21) | - | ✅ | ✅ | ✅ | - | - |
| [samd51-adafruit-metro-m4](microchip/samd51-adafruit-metro-m4) | - | ✅ | ✅ | ✅ | - | - |
| [samd51-seeed-wio-terminal](microchip/samd51-seeed-wio-terminal) | - | ✅ | ✅ | ✅ | - | - |
| [same54](microchip/same54) | - | ✅ | ✅ | ✅ | - | - |
| [same70](Infineon/psoc6-evaluationkit-062S2/packages/ili9341-latest/.git/objects/70) | - | ✅ | ✅ | ✅ | - | - |
| [saml10](Infineon/psoc6-evaluationkit-062S2/packages/ili9341-latest/.git/objects/10) | - | ✅ | - | ✅ | - | - |

#### ⚪ Synwit

| BSP Name | GPIO | UART | ADC | HWTimer | I2C | PWM |
|----------|------|------|-----|---------|-----|-----|
| [swm320-mini](synwit/swm320-mini) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [swm341-mini](synwit/swm341-mini) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### ⚪ N32G452xx
| BSP Name | GPIO | UART | ADC | CAN | DAC | Flash | HWTimer | I2C | PWM | RTC | SDIO | SPI | WDT |
|----------|------|------|-----|-----|-----|-------|---------|-----|-----|-----|------|-----|-----|
| [n32g452xx-mini-system](n32g452xx/n32g452xx-mini-system) | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |

#### ⚪ W60x
| BSP Name | GPIO | UART | ADC | Crypto | Flash | HWTimer | WDT | PWM | I2C | SPI |
|----------|------|------|-----|--------|-------|---------|-----|-----|-----|-----|
| [w60x](w60x) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### ⚪ Allwinner Tina
| BSP Name | GPIO | UART | SPI | SDIO |
|----------|------|------|-----|------|
| [allwinner_tina](allwinner_tina) | ✅ | ✅ | ✅ | ✅ |

#### ⚪ HC321136
| BSP Name | GPIO | UART | I2C |
|----------|------|------|-----|
| [hc321136](hc32/hc321136) | ✅ | ✅ | ✅ |

#### ⚪ HC321196
| BSP Name | GPIO | UART |
|----------|------|------|
| [hc321196](hc32/hc321196) | ✅ | ✅ |

#### ⚪ Amebaz
| BSP Name | GPIO | UART | WLAN |
|----------|------|------|------|
| [amebaz](amebaz) | - | ✅ | ✅ |

#### ⚪ CME_M7

| BSP Name | GPIO | UART | Ethernet |
|----------|------|------|----------|
| [CME_M7](CME_M7) | ✅ | ✅ | ✅ |

#### ⚪ Vango

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [v85xx](Vango/v85xx) | ✅ | ✅ | - | - | ✅ | - |
| [v85xxp](Vango/v85xxp) | ✅ | ✅ | - | - | - | - |

#### ⚪ ACM32

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [acm32f0x0-nucleo](acm32/acm32f0x0-nucleo) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [acm32f4xx-nucleo](acm32/acm32f4xx-nucleo) | ✅ | ✅ | - | - | - | - |

#### ⚪ Airm2m

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [air105](airm2m/air105) | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [air32f103](airm2m/air32f103) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### ⚪ Apollo2

| BSP Name | GPIO | UART | ADC |
|----------|------|------|-----|
| [apollo2](apollo2) | ✅ | ✅ | ✅ |

#### ⚪ ASM9260T

| BSP Name | GPIO | UART | HWTimer |
|----------|------|------|---------|
| [asm9260t](asm9260t) | ✅ | ✅ | ✅ |

#### ⚪ AT91

| BSP Name | UART | LED | I2C |
|----------|------|-----|-----|
| [at91sam9260](at91/at91sam9260) | ✅ | ✅ | ✅ |
| [at91sam9g45](at91/at91sam9g45) | ✅ | - | ✅ |

#### ⚪ Beaglebone

| BSP Name | UART | GPIO |
|----------|------|------|
| [beaglebone](beaglebone) | ✅ | ✅ |

#### ⚪ BM3803

| BSP Name | UART |
|----------|------|
| [bm3803](bm3803) | ✅ |

#### ⚪ Bouffalo Lab

| BSP Name | UART |
|----------|------|
| [b160x](Infineon/psoc6-evaluationkit-062S2/packages/rt_vsnprintf_full-latest/.git/objects/16) | ✅ |
| [b161x](Infineon/psoc6-evaluationkit-062S2/packages/rt_vsnprintf_full-latest/.git/objects/16) | ✅ |
| [b170x](Infineon/psoc6-evaluationkit-062S2/packages/ili9341-latest/.git/objects/70) | ✅ |
| [b1808](Infineon/psoc6-evaluationkit-062S2/packages/ili9341-latest/.git/objects/80) | ✅ |

#### ⚪ EFM32

| BSP Name | GPIO | UART | ADC |
|----------|------|------|-----|
| [efm32](efm32) | ✅ | ✅ | ✅ |

#### ⚪ FM33LC026

| BSP Name | GPIO | UART |
|----------|------|------|
| [fm33lc026](fm33lc026) | ✅ | ✅ |

#### ⚪ FRDM-K64F

| BSP Name | LED | UART | Ethernet |
|----------|-----|------|----------|
| [frdm-k64f](frdm-k64f) | ✅ | ✅ | ✅ |

#### ⚪ FT2004

| BSP Name | GPIO | UART | CAN |
|----------|------|------|-----|
| [ft2004](ft2004) | ✅ | ✅ | ✅ |

#### ⚪ FT32

| BSP Name | GPIO | UART |
|----------|------|------|
| [ft32f072xb-starter](ft32/ft32f072xb-starter) | ✅ | ✅ |
| [ft32f407xe-starter](ft32/ft32f407xe-starter) | ✅ | ✅ |

#### ⚪ Fujitsu

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [mb9bf500r](fujitsu/mb9x/mb9bf500r) | ✅ | ✅ | ✅ | - | - | - |
| [mb9bf506r](fujitsu/mb9x/mb9bf506r) | - | ✅ | - | - | - | - |
| [mb9bf568r](fujitsu/mb9x/mb9bf568r) | - | ✅ | - | - | - | - |
| [mb9bf618s](fujitsu/mb9x/mb9bf618s) | - | ✅ | - | - | - | - |

#### ⚪ HK32

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [hk32f030c8-mini](hk32/hk32f030c8-mini) | ✅ | ✅ | ✅ | - | ✅ | - |

#### ⚪ Jutcevm

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [juicevm](juicevm) | - | ✅ | - | - | - | - | ✅ | - | ✅ |

#### ⚪ LM3S8962

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [lm3s8962](lm3s8962) | ✅ | ✅ | - | - | - | - | ✅ | - | - |

#### ⚪ LM3S9B9x

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [lm3s9b9x](lm3s9b9x) | ✅ | ✅ | - | - | - | - | ✅ | - | - |

#### ⚪ LM4F232

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [lm4f232](lm4f232) | ✅ | ✅ | - | - | - | - | ✅ | - | - |

#### ⚪ Maxim

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [max32660-evsys](maxim/max32660-evsys) | ✅ | ✅ | - | ✅ | ✅ | - |

#### ⚪ Mini2440

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [mini2440](mini2440) | ✅ | ✅ | - | - | - | - | ✅ | - | - |

#### ⚪ Mini4020

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [mini4020](mini4020) | ✅ | ✅ | - | - | - | - | - | - | - |

#### ⚪ MM32

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [mm32f3270-100ask-pitaya](mm32/mm32f3270-100ask-pitaya) | ✅ | ✅ | - | - | - | - |

#### ⚪ MM32F103x

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [mm32f103x](mm32f103x) | ✅ | ✅ | - | - | - | - | - | - | - |

#### ⚪ MM32F327x

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [mm32f327x](mm32f327x) | ✅ | ✅ | - | ✅ | - | - | ✅ | - | - |

#### ⚪ MM32F526x

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [mm32f526x](mm32f526x) | ✅ | ✅ | ✅ | - | - | - | - | - | - |

#### ⚪ MM32L07x

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [mm32l07x](mm32l07x) | - | ✅ | - | - | - | - | - | - | - |

#### ⚪ MM32L3xx

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [mm32l3xx](mm32l3xx) | ✅ | ✅ | - | - | - | - | - | - | - |

#### ⚪ MSP432E401Y-LaunchPad

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [msp432e401y-launchpad](msp432e401y-launchpad) | ✅ | ✅ | - | - | - | - | - | - | - |

#### ⚪ NV32F100x

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [nv32f100x](nv32f100x) | ✅ | ✅ | - | - | ✅ | - | - | - | - |

#### ⚪ PIC32Ethernet

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [pic32ethernet](pic32ethernet) | - | - | - | - | - | - | - | - | - |

#### ⚪ RM48x50

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [rm48x50](rm48x50) | - | - | - | - | - | - | ✅ | - | - |

#### ⚪ SAM7x

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [sam7x](sam7x) | ✅ | ✅ | - | ✅ | - | - | - | - | - |

#### ⚪ SAMD21

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [samd21](samd21) | ✅ | ✅ | - | - | - | - | ✅ | - | - |

#### ⚪ SEP6200

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [sep6200](sep6200) | ✅ | ✅ | - | - | - | - | - | - | - |

#### ⚪ SmartFusion2

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [smartfusion2](smartfusion2) | ✅ | ✅ | - | - | - | - | - | - | - |

#### ⚪ Synopsys

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [synopsys](synopsys) | ✅ | ✅ | - | - | - | - | - | - | - |

#### ⚪ TAE32F5300

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [tae32f5300](tae32f5300) | ✅ | ✅ | ✅ | - | ✅ | - | - | ✅ | - |

#### ⚪ Taihu

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [taihu](taihu) | ✅ | ✅ | - | - | - | - | - | - | - |

#### ⚪ TKM32F499

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [tkm32F499](tkm32F499) | ✅ | ✅ | - | ✅ | ✅ | - | - | - | - |

#### ⚪ TM4C123BSP

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [tm4c123bsp](ti) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### ⚪ TM4C129x

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [tm4c129x](ti) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### ⚪ UPD70F3454

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [upd70f3454](upd70f3454) | - | ✅ | - | - | - | - | ✅ | - | - |

#### ⚪ Xplorer4330

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [xplorer4330](ti) | - | ✅ | - | - | - | - | - | - | - |

#### ⚪ Yichip

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [yc3121-pos](yichip/yc3121-pos) | ✅ | ✅ | - | - | - | - |
| [yc3122-pos](yichip/yc3122-pos) | ✅ | ✅ | - | - | - | - |

---

### RISC-V Architecture Series

#### 🟢 HPMicro

| BSP Name | GPIO | UART | ADC | CAN | Ethernet | RTC | SDXC | HWTimer | I2C | SPI | PWM | USBD | USBH | WDT |
|----------|------|------|-----|-----|----------|-----|------|---------|-----|-----|-----|------|------|-----|
| [hpm5300evk](hpmicro/hpm5300evk) | ✅ | ✅ | ✅ | ✅ | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [hpm5301evklite](hpmicro/hpm5301evklite) | ✅ | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [hpm5e00evk](hpmicro/hpm5e00evk) | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [hpm6200evk](hpmicro/hpm6200evk) | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [hpm6300evk](hpmicro/hpm6300evk) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [hpm6750evk](hpmicro/hpm6750evk) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [hpm6750evk2](hpmicro/hpm6750evk2) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [hpm6750evkmini](hpmicro/hpm6750evkmini) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [hpm6800evk](hpmicro/hpm6800evk) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [hpm6e00evk](hpmicro/hpm6e00evk) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [hpm6p00evk](hpmicro/hpm6p00evk) | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### 🟢 K230 (RT-Smart)

| BSP Name | GPIO | UART | I2C | RTC | ADC | PWM | SDIO | HWTimer | WDT | SPI | GNNE |
|----------|------|------|-----|-----|-----|-----|------|---------|-----|-----|------|
| [k230](k230) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### 🟢 Xuantie (RT-Smart)

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [e901](xuantie/smartl/e901) | - | ✅ | - | - | - | - |
| [e902](xuantie/smartl/e902) | - | ✅ | - | - | - | - |
| [e906](xuantie/smartl/e906) | - | ✅ | - | - | - | - |
| [e907](xuantie/smartl/e907) | - | ✅ | - | - | - | - |
| [c906 (RT-Smart)](xuantie/virt64/c906) | - | ✅ | - | - | - | - |
| [c907](xuantie/xiaohui/c907) | - | ✅ | - | - | - | - |
| [c908](xuantie/xiaohui/c908) | - | ✅ | - | - | - | - |
| [c910](xuantie/xiaohui/c910) | - | ✅ | - | - | - | - |
| [r908](xuantie/xiaohui/r908) | - | ✅ | - | - | - | - |
| [r910](xuantie/xiaohui/r910) | - | ✅ | - | - | - | - |
| [r920](xuantie/xiaohui/r920) | - | ✅ | - | - | - | - |

#### 🟢 QEMU Virt64 RISC-V (RT-Smart) (SMP doing)

| BSP Name | UART | VirtIO |
|----------|------|--------|
| [qemu-virt64-riscv](qemu-virt64-riscv) | ✅ | ✅ |

#### 🟢 WCH

| BSP Name | GPIO | UART | ADC | CAN | DAC | Ethernet | Flash | HWTimer | I2C | SPI | RTC | PWM | WDT | USBD | USBH |
|----------|------|------|-----|-----|-----|----------|-------|---------|-----|-----|-----|-----|-----|------|------|
| [arm](airm2m/air32f103/libraries/Startup/arm) | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [ch32f103c8-core](wch/arm/ch32f103c8-core) | ✅ | ✅ | - | - | - | - | - | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [ch32f203r-evt](wch/arm/ch32f203r-evt) | ✅ | ✅ | - | - | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | - | - |
| [ch579m](wch/arm/ch579m) | ✅ | ✅ | - | - | - | ✅ | - | - | - | - | - | - | - | - | ✅ |
| [ch32v103r-evt](wch/risc-v/ch32v103r-evt) | ✅ | ✅ | - | - | - | - | - | - | - | - | - | - | - | - | - |
| [ch32v208w-r0](wch/risc-v/ch32v208w-r0) | ✅ | ✅ | ✅ | ✅ | ✅ | - | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | - |
| [ch32v307v-r1](wch/risc-v/ch32v307v-r1) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [ch569w-evt](wch/risc-v/ch569w-evt) | ✅ | ✅ | - | - | - | - | - | ✅ | - | ✅ | - | - | - | - | - |
| [yd-ch32v307vct6](wch/risc-v/yd-ch32v307vct6) | ✅ | ✅ | ✅ | ✅ | ✅ | - | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | - | - |

#### 🟡 Ultrarisc (RT-Smart) (SMP)
| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [ur_dp1000_evb](ultrarisc/ur_dp1000_evb) | - | ✅ | - | - | ✅ | - |

#### 🟡 Allwinner (RT-Smart)

| BSP Name | GPIO | UART | SPI | I2C | WDT | PWM | LCD | RTC | SDMMC | TOUCH |
|----------|------|------|-----|-----|-----|-----|-----|-----|-------|-------|
| [d1](allwinner/d1) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [d1s](allwinner/d1s) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### 🟡 K210 (SMP)

| BSP Name | GPIO | UART | I2C | LCD | Camera | SPI |
|----------|------|------|-----|-----|--------|-----|
| [k210](k210) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### 🟡 Nuclei

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [gd32vf103_rvstar](gd32/gd32vf103_rvstar) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| [nuclei_fpga_eval](nuclei/nuclei_fpga_eval) | ✅ | ✅ | - | - | - | - |

#### 🟡 ESP32_C3

| BSP Name | GPIO | UART | ADC | I2C | SPI | Soft I2C | HWTimer | PWM | WiFi |
|----------|------|------|-----|-----|-----|----------|---------|-----|------|
| [ESP32_C3](ESP32_C3) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### 🟡 Bluetrum

| BSP Name | GPIO | UART | ADC | Flash | HWTimer | IRRX | PWM | RTC | SDIO | Soft I2C | WDT |
|----------|------|------|-----|-------|---------|------|-----|-----|------|----------|-----|
| [ab32vg1-ab-prougen](bluetrum/ab32vg1-ab-prougen) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

#### ⚪ Core-V-MCU
| BSP Name | UART |
|----------|------|
| [core-v-cv32e40p](core-v-mcu/core-v-cv32e40p) | ✅ |

#### ⚪ HiFive1
| BSP Name | GPIO | UART |
|----------|------|------|
| [hifive1](hifive1) | ✅ | ✅ |

#### ⚪ Sparkfun-RedV
| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [sparkfun-redv](sparkfun-redv) | ✅ | ✅ | - | - | - | - | ✅ | - | - |

#### ⚪ THead-Smart
| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [thead-smart](thead-smart) | ✅ | ✅ | - | - | - | - | ✅ | - | - |

#### ⚪ CK802

| BSP Name | GPIO | UART |
|----------|------|------|
| [ck802](ck802) | ✅ | ✅ |

#### ⚪ RV32M1_Vega

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [ri5cy](rv32m1_vega/ri5cy) | ✅ | ✅ | - | - | - | - |
| [rv32m1_sdk_riscv](rv32m1_vega/rv32m1_sdk_riscv) | ✅ | ✅ | - | - | - | - |

---

### AVR Architecture Series

#### ⚪ AVR32

| BSP Name | UART | GPIO | Soft I2C |
|----------|------|------|----------|
| [at32uc3a0256](avr32/at32uc3a0256) | ✅ | ✅ | ✅ |
| [at32uc3b0256](avr32/at32uc3b0256) | ✅ | ✅ | ✅ |

---

### MIPS Architecture Series

#### ⚪ Loongson

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [ls1bdev](loongson/ls1bdev) | - | ✅ | - | - | - | - |
| [ls1cdev](loongson/ls1cdev) | ✅ | ✅ | - | ✅ | ✅ | ✅ |
| [ls2kdev](loongson/ls2kdev) | ✅ | ✅ | - | - | ✅ | - |

#### ⚪ DM365

| BSP Name | GPIO | UART | Ethernet |
|----------|------|------|----------|
| [dm365](dm365) | ✅ | ✅ | ✅ |

#### ⚪ MLPSSIM

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [mipssim](mipssim) | ✅ | ✅ | - | - | - | - | ✅ | - | - |

#### ⚪ M16C62p

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [m16c62p](m16c62p) | ✅ | ✅ | - | - | - | - | - | - | - |

---

### DSP Architecture Series

#### ⚪ TI

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT |
|----------|------|------|-----|-----|-----|-----|
| [tms320f28379d](ti/c28x/tms320f28379d) | ✅ | ✅ | ✅ | - | - | - |

---

### x86 Architecture Series

#### ⚪ x86

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [x86](x86) | - | ✅ | - | - | - | - | - | - | - |

---

### FPGA Architecture Series

#### ⚪ ZynqMP-A53-DFZU2EG

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [zynqmp-a53-dfzu2eg](zynqmp-a53-dfzu2eg) | ✅ | ✅ | - | - | - | - | - | - | ✅ |

#### ⚪ ZynqMP-R5-AXU4EV

| BSP Name | GPIO | UART | ADC | I2C | SPI | WDT | Timer | PWM | RTC |
|----------|------|------|-----|-----|-----|-----|-------|-----|-----|
| [zynqmp-r5-axu4ev](zynqmp-r5-axu4ev) | ✅ | ✅ | - | - | - | - | ✅ | - | - |

---

*📅 Document Update Time: 2025-11-12 13:50:00*
