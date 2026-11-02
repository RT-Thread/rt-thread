## On-chip peripheral configuration of imxrt1180-nxp-evk --LPADC1

### 1. Demo feature list

- [x] use MCUX_Config software to set pin_mux, clock and LPADC1 peripheral.
- [x] board boots up from XIP (FlexSPI1_A- QSPI Flash W25Q128)
- [x] multichannel ADC enables to sample voltage from arduino connector.
- [x] only LPADC1 enabled, eDMA4 CH0 is optional to use for CPU offload.
- [x] channel  A1_4, A1_5, A1_7; B1_5, B1_6, B1_7 of LPADC1 are verified.

### 1. Hardware configuration

### 1.1 pin configuration in MCUX_Config software

![lpadc1_pin_mux](.\figures\lpadc1_pin_mux.png)

### 1.2 channel allocation in hardware

![drv_lpadc1_multich_test](.\figures\drv_lpadc1_multich_test.png)

### 2. LPADC1 configurations

### 2.1 General configuration

![img](./figures/lpadc1_periph_config.png)

- LPADC1 Clock: 80Mhz
- enable doze mode to reduce current leakage
- enable auto calibration, offset calibration
- VREFH select VDDA_ADC_1P8, selecting from power pin directly
- enable FIFO 0 watermark event for DMA trigger 

### 2.2 Command configuration

Command settings are consisted of group A and group B (GRPA, GRPB). GRPA is used for channel A1_4, A1_5, A1_7, while GRPB is used for channelB1_5, B1_6, B1_7. 

![lpadc1_GRPA_command](.\figures\lpadc1_GRPA_command.png)

- next command: 2
- sample mode: single
- channel starts from A1_4
- auto channel increment enabled, conversion continues to the end.
- full scale, which means max input of analog pin is 1.8V
- conversion resolution: 16-bit
- wait for software trigger

![lpadc1_GRPB_command](.\figures\lpadc1_GRPB_command.png)

- next command: none

- sample mode: single

- channel starts from B1_5

- auto channel increment enabled, conversion continues to the end.

- full scale, which means max input of analog pin is 1.8V

- conversion resolution: 16-bit

- loop count: 2

  

### 2.3 trigger configuration

![lpadc1_TRIG_config](.\figures\lpadc1_TRIG_config.png)

software trigger TRIG is used to trigger command group A.

### 2.4 EDMA configuration

![edma4_ch0](.\figures\edma4_ch0.png)

- Channel ID: CH0
- request source: #57: ADC1 Request 0
- enable peripheral request to trigger DMA

![edma4_ch0_transfer](.\figures\edma4_ch0_transfer.png)

- source address: ADC1 result register
- destination address: NONCACHEABLE memory
- minor loop transfer: 4
- major loop count: 7
- adjust address after each transfer: -28

## 3. RTT &chip sdk configuration

type "menuconfig.exe" in env tool, go to "Hardware Drivers Config"  --> "On-chip Peripheral Drivers":

![RTT_Config1](.\figures\RTT_Config1.png)



![RTT_Config2](.\figures\RTT_Config2.png)

The codes below shall be added to sdk module to enable codes chip-specific adding to the project.

![imxrt1180_sdk_SConscript-change](.\figures\imxrt1180_sdk_SConscript-change.png)



## 4. LPADC1 test

in MSH console, the command below can be entered to start LPDAC1 driver test.

![drv_adc test](.\figures\drv_adc test.png)

## 5. limitation for this demo

- Strongly relying on MCUX_Config for LPADC1 peripheral initialization, lack flexible for drv_lpadc
- Only demonstrate how to implement multichannel ADC sampling
- Max supported number of single end channel is eight, limited from RTT device driver level. verified channel in this demo is channel 4-7 representing A1_4, B1_5, A1_6, A1_7 separately.