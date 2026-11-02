/*
 * This is a generated file
 * 
 * Copyright 2021 QuickLogic
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __CORE_V_MCU_CONFIG_H_
#define __CORE_V_MCU_CONFIG_H_
#define NEW_BIT_FILE	1
#define OLD_BIT_FILE	0

#if (NEW_BIT_FILE == 1 )
#define BUILD_DATE 0x20220127
#define BUILD_TIME 0x00215431

#define FAKE_PLL		0
#define PERCEPTIA_PLL	1
//  SOC options
#define N_IO                 48
#define N_SYSIO              3
#define N_GPIO               32  
#define N_APBIO              51
#define NBIT_PADCFG          6
#define NBIT_PADMUX          2
#define N_UART               2
#define N_QSPIM              2      // two QSPI  master 
#define N_I2CM               2          // two I2C master  
#define N_I2SC               0
#define N_CSI2               0
#define N_HYPER              0
#define N_SDIO               1
#define N_CAM                1
#define N_JTAG               0
#define N_MRAM               0
#define N_FILTER             1
#define N_FPGA               0
#define N_EXT_PER            0
#define N_EFPGA_TCDM_PORTS   4
#define N_FPGAIO             43
#define N_EFPGA_EVENTS       16

//  UDMA configuration information
#define UDMA_START_ADDR         0x1A102000
#define UDMA_CH_SIZE            (0x80)
//  peripheral channel definitions
#define UDMA_CH_ADDR_CTRL       (0x1A102000)
#define UDMA_CH_ADDR_UART       (0x1A102000 + 1 * 0x80)
#define UDMA_UART_ID(id)        (0 + id)
#define UDMA_CH_ADDR_UART0      (0x1A102000 + 1 * 0x80)
#define UDMA_CH_ADDR_UART1      (0x1A102000 + 2 * 0x80)
#define UDMA_CH_ADDR_QSPIM      (0x1A102000 + 3 * 0x80)
#define UDMA_QSPIM_ID(id)       (2 + id)
#define UDMA_CH_ADDR_QSPIM0     (0x1A102000 + 3 * 0x80)
#define UDMA_CH_ADDR_QSPIM1     (0x1A102000 + 4 * 0x80)
#define UDMA_CH_ADDR_I2CM       (0x1A102000 + 5 * 0x80)
#define UDMA_I2CM_ID(id)        (4 + id)
#define UDMA_CH_ADDR_I2CM0      (0x1A102000 + 5 * 0x80)
#define UDMA_CH_ADDR_I2CM1      (0x1A102000 + 6 * 0x80)
#define UDMA_CH_ADDR_I2SC       (0x1A102000 + 7 * 0x80)
#define UDMA_I2SC_ID(id)        (6 + id)
#define UDMA_CH_ADDR_I2SC0      (0x1A102000 + 7 * 0x80)
#define UDMA_CH_ADDR_CSI2       (0x1A102000 + 7 * 0x80)
#define UDMA_CSI2_ID(id)        (6 + id)
#define UDMA_CH_ADDR_CSI20      (0x1A102000 + 7 * 0x80)
#define UDMA_CH_ADDR_HYPER      (0x1A102000 + 7 * 0x80)
#define UDMA_HYPER_ID(id)       (6 + id)
#define UDMA_CH_ADDR_HYPER0     (0x1A102000 + 7 * 0x80)
#define UDMA_CH_ADDR_SDIO       (0x1A102000 + 7 * 0x80)
#define UDMA_SDIO_ID(id)        (6 + id)
#define UDMA_CH_ADDR_SDIO0      (0x1A102000 + 7 * 0x80)
#define UDMA_CH_ADDR_CAM        (0x1A102000 + 8 * 0x80)
#define UDMA_CAM_ID(id)         (7 + id)
#define UDMA_CH_ADDR_CAM0       (0x1A102000 + 8 * 0x80)
#define UDMA_CH_ADDR_JTAG       (0x1A102000 + 9 * 0x80)
#define UDMA_JTAG_ID(id)        (8 + id)
#define UDMA_CH_ADDR_JTAG0      (0x1A102000 + 9 * 0x80)
#define UDMA_CH_ADDR_MRAM       (0x1A102000 + 9 * 0x80)
#define UDMA_MRAM_ID(id)        (8 + id)
#define UDMA_CH_ADDR_MRAM0      (0x1A102000 + 9 * 0x80)
#define UDMA_CH_ADDR_FILTER     (0x1A102000 + 9 * 0x80)
#define UDMA_FILTER_ID(id)      (8 + id)
#define UDMA_CH_ADDR_FILTER0    (0x1A102000 + 9 * 0x80)
#define UDMA_CH_ADDR_FPGA       (0x1A102000 + 10 * 0x80)
#define UDMA_FPGA_ID(id)        (9 + id)
#define UDMA_CH_ADDR_FPGA0      (0x1A102000 + 10 * 0x80)
#define UDMA_CH_ADDR_EXT_PER    (0x1A102000 + 10 * 0x80)
#define UDMA_EXT_PER_ID(id)     (9 + id)
#define UDMA_CH_ADDR_EXT_PER0   (0x1A102000 + 10 * 0x80)

//  Peripheral clock enable masks
#define UDMA_CTRL_UART0_CLKEN      (1 << 0)
#define UDMA_CTRL_UART1_CLKEN      (1 << 1)
#define UDMA_CTRL_QSPIM0_CLKEN     (1 << 2)
#define UDMA_CTRL_QSPIM1_CLKEN     (1 << 3)
#define UDMA_CTRL_I2CM0_CLKEN      (1 << 4)
#define UDMA_CTRL_I2CM1_CLKEN      (1 << 5)
#define UDMA_CTRL_I2SC0_CLKEN      (1 << 6)
#define UDMA_CTRL_CSI20_CLKEN      (1 << 6)
#define UDMA_CTRL_HYPER0_CLKEN     (1 << 6)
#define UDMA_CTRL_SDIO0_CLKEN      (1 << 6)
#define UDMA_CTRL_CAM0_CLKEN       (1 << 7)
#define UDMA_CTRL_JTAG0_CLKEN      (1 << 8)
#define UDMA_CTRL_MRAM0_CLKEN      (1 << 8)
#define UDMA_CTRL_FILTER0_CLKEN    (1 << 8)
#define UDMA_CTRL_FPGA0_CLKEN      (1 << 9)
#define UDMA_CTRL_EXT_PER0_CLKEN   (1 << 9)

//  FLL configuration information
#define FLL1_START_ADDR 0x1A100000

#define FLL2_START_ADDR 0x1A100020

#define FLL3_START_ADDR 0x1A100040


//  GPIO configuration information
#define GPIO_START_ADDR 0x1A101000

#define SOC_EVENT_GEN_START_ADDR 0x1A106000
//  I2C Slave configuration information
#define I2CS_START_ADDR 0x1A107000

//  EFPGAIO configuration information
#define EFPGAIO_START_ADDR 0x1A300000

//  SOC controller configuration information
#define SOC_CTRL_START_ADDR 0x1A104000

//  Event Unit (Interrupts) configuration information
#define EU_START_ADDR 0x1A109000

//  Timer configuration information
#define TIMER_START_ADDR 0x1A10B000

//  AdvTimer configuration information
#define ADV_TIMER_START_ADDR 0x1A105000

//  EFPGA configuration information (FCB)
#define EFPGA_CONFIG_START_ADDR 0x1A200000

#elif (OLD_BIT_FILE == 1)

#define BUILD_DATE 0x20210623
#define BUILD_TIME 0x00111431

#define FAKE_PLL		0
#define PERCEPTIA_PLL	1

//  SOC options
#define N_IO                 48
#define N_SYSIO              3
#define N_GPIO               32
#define N_APBIO              50
#define NBIT_PADCFG          6
#define NBIT_PADMUX          2
#define N_UART               2
#define N_QSPIM              1
#define N_I2CM               2
#define N_I2SC               0
#define N_CSI2               0
#define N_HYPER              0
#define N_SDIO               1
#define N_CAM                1
#define N_JTAG               0
#define N_MRAM               0
#define N_FILTER             1
#define N_FPGA               1
#define N_EXT_PER            0
#define N_EFPGA_TCDM_PORTS   4
#define N_FPGAIO             43
#define N_EFPGA_EVENTS       16

//  UDMA configuration information
#define UDMA_START_ADDR         0x1A102000
#define UDMA_CH_SIZE            (0x80)
//  peripheral channel definitions
#define UDMA_CH_ADDR_CTRL       (0x1A102000)
#define UDMA_CH_ADDR_UART       (0x1A102000 + 1 * 0x80)
#define UDMA_UART_ID(id)        (0 + id)
#define UDMA_CH_ADDR_UART0      (0x1A102000 + 1 * 0x80)
#define UDMA_CH_ADDR_UART1      (0x1A102000 + 2 * 0x80)
#define UDMA_CH_ADDR_QSPIM      (0x1A102000 + 3 * 0x80)
#define UDMA_QSPIM_ID(id)       (2 + id)
#define UDMA_CH_ADDR_QSPIM0     (0x1A102000 + 3 * 0x80)
#define UDMA_CH_ADDR_I2CM       (0x1A102000 + 4 * 0x80)
#define UDMA_I2CM_ID(id)        (3 + id)
#define UDMA_CH_ADDR_I2CM0      (0x1A102000 + 4 * 0x80)
#define UDMA_CH_ADDR_I2CM1      (0x1A102000 + 5 * 0x80)
#define UDMA_CH_ADDR_I2SC       (0x1A102000 + 6 * 0x80)
#define UDMA_I2SC_ID(id)        (5 + id)
#define UDMA_CH_ADDR_I2SC0      (0x1A102000 + 6 * 0x80)
#define UDMA_CH_ADDR_CSI2       (0x1A102000 + 6 * 0x80)
#define UDMA_CSI2_ID(id)        (5 + id)
#define UDMA_CH_ADDR_CSI20      (0x1A102000 + 6 * 0x80)
#define UDMA_CH_ADDR_HYPER      (0x1A102000 + 6 * 0x80)
#define UDMA_HYPER_ID(id)       (5 + id)
#define UDMA_CH_ADDR_HYPER0     (0x1A102000 + 6 * 0x80)
#define UDMA_CH_ADDR_SDIO       (0x1A102000 + 6 * 0x80)
#define UDMA_SDIO_ID(id)        (5 + id)
#define UDMA_CH_ADDR_SDIO0      (0x1A102000 + 6 * 0x80)
#define UDMA_CH_ADDR_CAM        (0x1A102000 + 7 * 0x80)
#define UDMA_CAM_ID(id)         (6 + id)
#define UDMA_CH_ADDR_CAM0       (0x1A102000 + 6 * 0x80)
#define UDMA_CH_ADDR_JTAG       (0x1A102000 + 7 * 0x80)
#define UDMA_JTAG_ID(id)        (6 + id)
#define UDMA_CH_ADDR_JTAG0      (0x1A102000 + 7 * 0x80)
#define UDMA_CH_ADDR_MRAM       (0x1A102000 + 7 * 0x80)
#define UDMA_MRAM_ID(id)        (6 + id)
#define UDMA_CH_ADDR_MRAM0      (0x1A102000 + 7 * 0x80)
#define UDMA_CH_ADDR_FILTER     (0x1A102000 + 7 * 0x80)
#define UDMA_FILTER_ID(id)      (6 + id)
#define UDMA_CH_ADDR_FILTER0    (0x1A102000 + 7 * 0x80)
#define UDMA_CH_ADDR_FPGA       (0x1A102000 + 8 * 0x80)
#define UDMA_FPGA_ID(id)        (7 + id)
#define UDMA_CH_ADDR_FPGA0      (0x1A102000 + 8 * 0x80)
#define UDMA_CH_ADDR_EXT_PER    (0x1A102000 + 9 * 0x80)
#define UDMA_EXT_PER_ID(id)     (8 + id)
#define UDMA_CH_ADDR_EXT_PER0   (0x1A102000 + 9 * 0x80)

//  Peripheral clock enable masks
#define UDMA_CTRL_UART0_CLKEN      (1 << 0)
#define UDMA_CTRL_UART1_CLKEN      (1 << 1)
#define UDMA_CTRL_QSPIM0_CLKEN     (1 << 2)
#define UDMA_CTRL_I2CM0_CLKEN      (1 << 3)
#define UDMA_CTRL_I2CM1_CLKEN      (1 << 4)
#define UDMA_CTRL_I2SC0_CLKEN      (1 << 5)
#define UDMA_CTRL_CSI20_CLKEN      (1 << 5)
#define UDMA_CTRL_HYPER0_CLKEN     (1 << 5)
#define UDMA_CTRL_SDIO0_CLKEN      (1 << 5)
#define UDMA_CTRL_CAM0_CLKEN       (1 << 6)
#define UDMA_CTRL_JTAG0_CLKEN      (1 << 6)
#define UDMA_CTRL_MRAM0_CLKEN      (1 << 6)
#define UDMA_CTRL_FILTER0_CLKEN    (1 << 6)
#define UDMA_CTRL_FPGA0_CLKEN      (1 << 7)
#define UDMA_CTRL_EXT_PER0_CLKEN   (1 << 8)

//  FLL configuration information
#define FLL1_START_ADDR 0x1A100000

#define FLL2_START_ADDR 0x1A100020

#define FLL3_START_ADDR 0x1A100040

//  GPIO configuration information
#define GPIO_START_ADDR 0x1A101000

#define SOC_EVENT_GEN_START_ADDR 0x1A106000
//  I2C Slave configuration information
#define I2CS_START_ADDR 0x1A107000

//  EFPGAIO configuration information
#define EFPGAIO_START_ADDR 0x1A300000

//  SOC controller configuration information
#define SOC_CTRL_START_ADDR 0x1A104000

//  Event Unit (Interrupts) configuration information
#define EU_START_ADDR 0x1A109000

//  Timer configuration information
#define TIMER_START_ADDR 0x1A10B000

//  AdvTimer configuration information
#define ADV_TIMER_START_ADDR 0x1A105000

//  EFPGA configuration information (FCB)
#define EFPGA_CONFIG_START_ADDR 0x1A200000
#endif

#endif //__CORE_V_MCU_CONFIG_H_
