# FRDM-IMX91 RT-Thread BSP

This folder contains the RT-Thread BSP for the NXP FRDM-IMX91 development board.

## Board Overview

## Build and Run

### Setup RT-Thread Development Environment

### Setup Network and TFTP Server for FRDM-IMX91

### Build RT-Thread BSP for FRDM-IMX91

1. Clone the RT-Thread repository:
   ```
   git clone https://github.com/RT-Thread/rt-thread.git
   ```

2. Navigate to the BSP folder:
   ```
   cd rt-thread/bsp/nxp/imx/imx91
   ```

3. Build the BSP:
   ```
   scons -j 8
   ```

4. copy the `rtthread.bin` to the TFTP server working directory:
   ```
   cp rtthread.bin /path/to/tftp_work_dir/
   ```

### Run RT-Thread on FRDM-IMX91 with u-boot

```sh
setenv bootcmd "tftp 0x80000000 rtthread.bin; dcache flush; icache flush; go 0x80000000"
saveenv
reset
```
