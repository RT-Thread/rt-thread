## On-chip peripheral configuration of imxrt1180-nxp-evk --FlexSPI1

### 1. Demo feature list

- [x] use MCUX_Config software to set pin_mux, clock.
- [x] board boots up from CMSIS-DAP. (FlexSPI1_A- QSPI Flash W25Q128 is used for CM33 XIP boot-up)
- [x] FlexSPI1_B is set to octal mode for hyperFlash(MT35XU512ABA2G12-0AAT) reading&writing
- [x] when BSP_USING_DMA is enabled, eDMA4 CH0 is used for TX and CH2 for RX for CPU offload.
- [x] flexspi_test command is used for test in MSH console.

### 2. Hardware configuration

### 2.1 pin configuration in MCUX_Config software

![pin_config](.\figures\pin_config.png)



### 2.2 hardware change on top

![HW_change_top](.\figures\HW_change_top.png)

### 2.3 hardware change on bottom

![HW_change_bottom](.\figures\HW_change_bottom.png)

do hardware change to enable path for hyper Flash.

### 2.4 chip sdk change

![MIMXRT1180_SConsript_add](.\figures\MIMXRT1180_SConsript_add.png)

add these codes above to "nxp-imxrt-sdk-latest/MIMXRT1180/SConscript" to enable chip specific drivers.

### 3. FlexSPI1_b octal mode test

![flexspi_test result](.\figures\flexspi_test result.png)

### 4. limitation

- only use MCUX_Config for pin_mux, clock configuration, providing enough flexibility on drv_flexspi.
- merge official examples on FlexSPI octal polling and DMA mode for hyper Flash operation. XIP and FLASH_ADESTO are not supported.
- Only support booting from CMSIS-DAP due to hardware limitation.

