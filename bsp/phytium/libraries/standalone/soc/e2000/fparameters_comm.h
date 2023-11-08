/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fparameters_comm.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-17 18:01:11
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FPARAMTERERS_COMMON_H
#define FPARAMTERERS_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/
#if !defined(__ASSEMBLER__)
#include "ftypes.h"
#endif

#define SOC_TARGET_E2000
/************************** Constant Definitions *****************************/
/* CACHE */
#define CACHE_LINE_ADDR_MASK 0x3FUL
#define CACHE_LINE  64U

/* DEVICE Register Address */
#define FT_DEV_BASE_ADDR 0x28000000U
#define FT_DEV_END_ADDR 0x2FFFFFFFU

/* PCIE */

/* PCIE ECAM */

/* Pci express  */
#define FPCIE_ECAM_INSTANCE_NUM 1
#define FPCIE_ECAM_INSTANCE0 0

#define FPCIE_ECAM_MAX_OUTBOUND_NUM 8

/* Bus, Device and Function */
#define FPCIE_ECAM_CFG_MAX_NUM_OF_BUS 256
#define FPCIE_ECAM_CFG_MAX_NUM_OF_DEV 32
#define FPCIE_ECAM_CFG_MAX_NUM_OF_FUN 8

#define FPCIE_ECAM_INTA_IRQ_NUM     36
#define FPCIE_ECAM_INTB_IRQ_NUM     37
#define FPCIE_ECAM_INTC_IRQ_NUM     38
#define FPCIE_ECAM_INTD_IRQ_NUM     39

/*  max scan*/
#define FPCIE_MAX_SCAN_NUMBER 128

/* memory space */
#define FPCI_ECAM_CONFIG_BASE_ADDR 0x40000000        /* ecam */
#define FPCI_ECAM_CONFIG_REG_LENGTH 0x10000000

#define FPCI_ECAM_IO_CONFIG_BASE_ADDR 0x50000000     /* io address space */
#define FPCI_ECAM_IO_CONFIG_REG_LENGTH 0x08000000

#define FPCI_ECAM_MEM32_BASE_ADDR 0x58000000         /* mmio 32 */
#define FPCI_ECAM_MEM32_REG_LENGTH 0x27ffffff

#define FPCI_ECAM_MEM64_BASE_ADDR 0x1000000000       /* mmio 64 */
#define FPCI_ECAM_MEM64_REG_LENGTH 0x1fffffffff


/* FPCIE Controler */
#define FPCIEC_INSTANCE_NUM 6

#define FPCIEC_INSTANCE0_INDEX 0 /* psu.c0 */
#define FPCIEC_INSTANCE1_INDEX 1 /* psu.c1 */
#define FPCIEC_INSTANCE2_INDEX 2 /* peu.c0 */
#define FPCIEC_INSTANCE3_INDEX 3 /* peu.c1 */
#define FPCIEC_INSTANCE4_INDEX 4 /* peu.c2 */
#define FPCIEC_INSTANCE5_INDEX 5 /* peu.c3 */

#define FPCIEC_INSTANCE0_MISC_IRQ_NUM 42

#define FPCIEC_INSTANCE3_MISC_IRQ_NUM 40

#define FPCIEC_INSTANCE0_NUM 0 /* psu.c0 */
#define FPCIEC_INSTANCE1_NUM 1 /* psu.c1 */
#define FPCIEC_INSTANCE2_NUM 0 /* peu.c0 */
#define FPCIEC_INSTANCE3_NUM 1 /* peu.c1 */
#define FPCIEC_INSTANCE4_NUM 2 /* peu.c2 */
#define FPCIEC_INSTANCE5_NUM 3 /* peu.c3 */

#define FPCIEC_INSTANCE0_CONTROL_BASE 0x31000000U
#define FPCIEC_INSTANCE1_CONTROL_BASE 0x31020000U
#define FPCIEC_INSTANCE2_CONTROL_BASE 0x31040000U
#define FPCIEC_INSTANCE3_CONTROL_BASE 0x31060000U
#define FPCIEC_INSTANCE4_CONTROL_BASE 0x31080000U
#define FPCIEC_INSTANCE5_CONTROL_BASE 0x310a0000U

#define FPCIEC_INSTANCE0_CONFIG_BASE 0x31100000U
#define FPCIEC_INSTANCE1_CONFIG_BASE 0x31100000U
#define FPCIEC_INSTANCE2_CONFIG_BASE 0x31101000U
#define FPCIEC_INSTANCE3_CONFIG_BASE 0x31101000U
#define FPCIEC_INSTANCE4_CONFIG_BASE 0x31101000U
#define FPCIEC_INSTANCE5_CONFIG_BASE 0x31101000U

#define FPCIEC_INSTANCE0_DMA_NUM      2
#define FPCIEC_INSTANCE1_DMA_NUM      0
#define FPCIEC_INSTANCE2_DMA_NUM      2
#define FPCIEC_INSTANCE3_DMA_NUM      0
#define FPCIEC_INSTANCE4_DMA_NUM      0
#define FPCIEC_INSTANCE5_DMA_NUM      0

#define FPCIEC_INSTANCE0_DMABASE      (0x31000000U + 0x400U)
#define FPCIEC_INSTANCE1_DMABASE      (0U)
#define FPCIEC_INSTANCE2_DMABASE      (0x31040000U + 0x400U)
#define FPCIEC_INSTANCE3_DMABASE      (0U)
#define FPCIEC_INSTANCE4_DMABASE      (0U)
#define FPCIEC_INSTANCE5_DMABASE      (0U)

#define FPCIEC_MAX_OUTBOUND_NUM         8


/* platform ahci host */
#define PLAT_AHCI_HOST_MAX_COUNT 5
#define AHCI_BASE_0     0
#define AHCI_BASE_1     0
#define AHCI_BASE_2     0
#define AHCI_BASE_3     0
#define AHCI_BASE_4     0

#define AHCI_IRQ_0      0
#define AHCI_IRQ_1      0
#define AHCI_IRQ_2      0
#define AHCI_IRQ_3      0
#define AHCI_IRQ_4      0

/* sata controller */
#define FSATA0_BASE_ADDR 0x31A40000U
#define FSATA1_BASE_ADDR 0x32014000U

#define FSATA0_IRQ_NUM   74
#define FSATA1_IRQ_NUM   75

#define FSATA0_ID  0
#define FSATA1_ID  1
#define FSATA_NUM  2


/* SCMI and MHU */
#define FSCMI_MHU_BASE_ADDR 0x32a00000
#define FSCMI_MHU_IRQ_NUM   (22U + 32U)
#define FSCMI_SHR_MEM_ADDR  0x32a11400
#define FSCMI_MEM_TX_OFSET  0x1400
#define FSCMI_MEM_RX_OFSET  0x1000
#define FSCMI_SHR_MEM_SIZE  0x400

#define FSCMI_MSG_SIZE			128	
#define FSCMI_MAX_STR_SIZE		16
#define FSCMI_MAX_NUM_SENSOR	16
#define FSCMI_MAX_PROTOCOLS_IMP	16
#define FSCMI_MAX_PERF_DOMAINS  3
#define FSCMI_MAX_OPPS		    4

/* UART */
#define FUART_NUM 4U
#define FUART_REG_LENGTH 0x18000U

#define FUART0_ID 0U
#define FUART0_IRQ_NUM (85 + 30)
#define FUART0_BASE_ADDR 0x2800c000U
#define FUART0_CLK_FREQ_HZ 100000000U

#define FUART1_ID 1U
#define FUART1_IRQ_NUM (86 + 30)
#define FUART1_BASE_ADDR 0x2800d000U
#define FUART1_CLK_FREQ_HZ 100000000U

#define FUART2_ID 2U
#define FUART2_IRQ_NUM (87 + 30)
#define FUART2_BASE_ADDR 0x2800e000U
#define FUART2_CLK_FREQ_HZ 100000000U

#define FUART3_BASE_ADDR 0x2800f000U
#define FUART3_ID 3U
#define FUART3_IRQ_NUM (88 + 30)
#define FUART3_CLK_FREQ_HZ 100000000U

#define FT_STDOUT_BASE_ADDR FUART1_BASE_ADDR
#define FT_STDIN_BASE_ADDR FUART1_BASE_ADDR

/****** GIC v3  *****/
#define FT_GICV3_INSTANCES_NUM 1U
#define GICV3_REG_LENGTH 0x00009000U

/*
 * The maximum priority value that can be used in the GIC.
 */
#define GICV3_MAX_INTR_PRIO_VAL 240U
#define GICV3_INTR_PRIO_MASK 0x000000f0U

#define ARM_GIC_NR_IRQS 270U
#define ARM_GIC_IRQ_START 0U
#define FGIC_NUM 1U

#define ARM_GIC_IPI_COUNT 16U /* MPCore IPI count         */
#define SGI_INT_MAX 16U
#define SPI_START_INT_NUM 32U /* SPI start at ID32        */
#define PPI_START_INT_NUM 16U /* PPI start at ID16        */
#define GIC_INT_MAX_NUM 1020U /* GIC max interrupts count */

#define GICV3_BASE_ADDR 0x30800000U
#define GICV3_DISTRIBUTOR_BASE_ADDR (GICV3_BASE_ADDR + 0)
#define GICV3_RD_BASE_ADDR (GICV3_BASE_ADDR + 0x80000U)
#define GICV3_RD_OFFSET (2U << 16)
#define FT_GICV3_VECTORTABLE_NUM GIC_INT_MAX_NUM

/* GPIO */
#define FGPIO0_ID   0
#define FGPIO1_ID   1
#define FGPIO2_ID   2   
#define FGPIO3_ID   3
#define FGPIO4_ID   4
#define FGPIO5_ID   5
#define FGPIO_NUM   6


#define FGPIO_WITH_PIN_IRQ              2U /* max id of gpio assign irq for each pin */

#define FGPIO0_BASE_ADDR               0x28034000U
#define FGPIO1_BASE_ADDR               0x28035000U
#define FGPIO2_BASE_ADDR               0x28036000U
#define FGPIO3_BASE_ADDR               0x28037000U
#define FGPIO4_BASE_ADDR               0x28038000U
#define FGPIO5_BASE_ADDR               0x28039000U

#define FGPIO_CTRL_PIN_NUM              16U

#define FGPIO_PIN_IRQ_BASE              140U
#define FGPIO_PIN_IRQ_NUM_GET(id, pin)  (FGPIO_PIN_IRQ_BASE + FGPIO_CTRL_PIN_NUM * (id) + (pin))

#define FGPIO_3_IRQ_NUM                 188U
#define FGPIO_4_IRQ_NUM                 189U
#define FGPIO_5_IRQ_NUM                 190U

#define FGPIO_PIN_IRQ_TOTAL             51U

/* SPI */
#define FSPI0_BASE_ADDR 0x2803A000U
#define FSPI1_BASE_ADDR 0x2803B000U
#define FSPI2_BASE 0x2803C000U
#define FSPI3_BASE 0x2803D000U
#define FSPI0_ID   0U
#define FSPI1_ID   1U
#define FSPI2_ID   2U
#define FSPI3_ID   3U

#define FSPI0_IRQ_NUM 191U
#define FSPI1_IRQ_NUM 192U
#define FSPI2_IRQ_NUM 193U
#define FSPI3_IRQ_NUM 194U

#define FSPI_CLK_FREQ_HZ 50000000U
#define FSPI_NUM 4U

/* XMAC */
#define FXMAC_NUM 4U

#define FXMAC0_ID 0U
#define FXMAC1_ID 1U
#define FXMAC2_ID 2U
#define FXMAC3_ID 3U

#define FXMAC0_BASE_ADDR 0x3200C000U
#define FXMAC1_BASE_ADDR 0x3200E000U
#define FXMAC2_BASE_ADDR 0x32010000U
#define FXMAC3_BASE_ADDR 0x32012000U

#define FXMAC0_MODE_SEL_BASE_ADDR 0x3200DC00U
#define FXMAC0_LOOPBACK_SEL_BASE_ADDR 0x3200DC04U
#define FXMAC1_MODE_SEL_BASE_ADDR 0x3200FC00U
#define FXMAC1_LOOPBACK_SEL_BASE_ADDR 0x3200FC04U
#define FXMAC2_MODE_SEL_BASE_ADDR 0x32011C00U
#define FXMAC2_LOOPBACK_SEL_BASE_ADDR 0x32011C04U
#define FXMAC3_MODE_SEL_BASE_ADDR 0x32013C00U
#define FXMAC3_LOOPBACK_SEL_BASE_ADDR 0x32013C04U

#define FXMAC0_PCLK 50000000U
#define FXMAC1_PCLK 50000000U
#define FXMAC2_PCLK 50000000U
#define FXMAC3_PCLK 50000000U
#define FXMAC0_HOTPLUG_IRQ_NUM (53U + 30U)
#define FXMAC1_HOTPLUG_IRQ_NUM (54U + 30U)
#define FXMAC2_HOTPLUG_IRQ_NUM (55U + 30U)
#define FXMAC3_HOTPLUG_IRQ_NUM (56U + 30U)

#define FXMAC_QUEUE_MAX_NUM 16U

#define FXMAC0_QUEUE0_IRQ_NUM (57U + 30U)
#define FXMAC0_QUEUE1_IRQ_NUM (58U + 30U)
#define FXMAC0_QUEUE2_IRQ_NUM (59U + 30U)
#define FXMAC0_QUEUE3_IRQ_NUM (60U + 30U)
#define FXMAC0_QUEUE4_IRQ_NUM (30U + 30U)
#define FXMAC0_QUEUE5_IRQ_NUM (31U + 30U)
#define FXMAC0_QUEUE6_IRQ_NUM (32U + 30U)
#define FXMAC0_QUEUE7_IRQ_NUM (33U + 30U)

#define FXMAC1_QUEUE0_IRQ_NUM (61U + 30U)
#define FXMAC1_QUEUE1_IRQ_NUM (62U + 30U)
#define FXMAC1_QUEUE2_IRQ_NUM (63U + 30U)
#define FXMAC1_QUEUE3_IRQ_NUM (64U + 30U)

#define FXMAC2_QUEUE0_IRQ_NUM (66U + 30U)
#define FXMAC2_QUEUE1_IRQ_NUM (67U + 30U)
#define FXMAC2_QUEUE2_IRQ_NUM (68U + 30U)
#define FXMAC2_QUEUE3_IRQ_NUM (69U + 30U)

#define FXMAC3_QUEUE0_IRQ_NUM (70U + 30U)
#define FXMAC3_QUEUE1_IRQ_NUM (71U + 30U)
#define FXMAC3_QUEUE2_IRQ_NUM (72U + 30U)
#define FXMAC3_QUEUE3_IRQ_NUM (73U + 30U)

#define FXMAC_PHY_MAX_NUM 32U

#define FXMAC_CLK_TYPE_0

/* IOPAD */
#define FIOPAD0_ID 0
#define FIOPAD_NUM 1

/* QSPI */
#define FQSPI0_ID   0
#define FQSPI_NUM   1

/* FQSPI cs 0_3, chip number */

#define FQSPI_CS_0    0
#define FQSPI_CS_1    1
#define FQSPI_CS_2    2
#define FQSPI_CS_3    3
#define FQSPI_CS_NUM     4
#define FQSPI_BASE_ADDR 0x028008000U

#define FQSPI_MEM_START_ADDR 0x0U
#define FQSPI_MEM_END_ADDR 0x0FFFFFFFU /* 256MB */
#define FQSPI_MEM_START_ADDR_64 0x100000000U
#define FQSPI_MEM_END_ADDR_64 0x17FFFFFFFU /* 2GB */

/* TIMER and TACHO */
#define FTIMER_NUM 38U
#define FTIMER_CLK_FREQ_HZ 50000000ULL /* 50MHz */
#define FTIMER_TICK_PERIOD_NS 20U      /* 20ns */
#define FTIMER_TACHO_IRQ_NUM(n) (226U + (n))
#define FTIMER_TACHO_BASE_ADDR(n) (0x28054000U + 0x1000U * (n))


#define FTACHO0_ID 0 
#define FTACHO1_ID 1 
#define FTACHO2_ID 2 
#define FTACHO3_ID 3 
#define FTACHO4_ID 4 
#define FTACHO5_ID 5 
#define FTACHO6_ID 6 
#define FTACHO7_ID 7 
#define FTACHO8_ID 8 
#define FTACHO9_ID 9 
#define FTACHO10_ID 10 
#define FTACHO11_ID 11 
#define FTACHO12_ID 12 
#define FTACHO13_ID 13 
#define FTACHO14_ID 14 
#define FTACHO15_ID 15 
#define FTACHO_NUM  16

/* GDMA */
#define FGDMA0_ID           0U
#define FGDMA0_BASE_ADDR    0x32B34000U
#define FGDMA0_CHANNEL0_IRQ_NUM      266U
#define FGDMA_NUM_OF_CHAN   16
#define FGDMA_INSTANCE_NUM  1U
#define FGDMA0_CAPACITY (1U<<0) 

/* CANFD */
#define FCAN_CLK_FREQ_HZ 200000000U

#define FCAN0_BASE_ADDR 0x2800A000U
#define FCAN1_BASE_ADDR 0x2800B000U

#define FCAN0_IRQ_NUM 113U
#define FCAN1_IRQ_NUM 114U


#define  FCAN0_ID  0
#define  FCAN1_ID  1
#define  FCAN_NUM  2

/* WDT */

#define FWDT0_ID    0
#define FWDT1_ID    1
#define FWDT_NUM    2

#define FWDT0_REFRESH_BASE_ADDR 0x28040000U
#define FWDT1_REFRESH_BASE_ADDR 0x28042000U

#define FWDT_CONTROL_BASE_ADDR(x) ((x)+0x1000)

#define FWDT0_IRQ_NUM 196U
#define FWDT1_IRQ_NUM 197U

#define FWDT_CLK_FREQ_HZ 48000000U /* 48MHz */

/*MIO*/
#define FMIO_BASE_ADDR(n) (0x28014000 + 0x2000 * (n))
#define FMIO_CONF_ADDR(n) FMIO_BASE_ADDR(n)+0x1000
#define FMIO_IRQ_NUM(n) (124+n)
#define FMIO_CLK_FREQ_HZ 50000000 /* 50MHz */


#define  FMIO0_ID 0 
#define  FMIO1_ID 1 
#define  FMIO2_ID 2 
#define  FMIO3_ID 3 
#define  FMIO4_ID 4 
#define  FMIO5_ID 5 
#define  FMIO6_ID 6 
#define  FMIO7_ID 7 
#define  FMIO8_ID 8 
#define  FMIO9_ID 9 
#define  FMIO10_ID 10 
#define  FMIO11_ID 11 
#define  FMIO12_ID 12 
#define  FMIO13_ID 13 
#define  FMIO14_ID 14 
#define  FMIO15_ID 15 
#define  FMIO_NUM 16

/*I2C0 -> PMBUS0
* I2C1 -> PMBUS1
* I2C2 -> SMBUS0
*/


#define FI2C0_ID 0
#define FI2C1_ID 1
#define FI2C2_ID 2
#define FI2C_NUM 3

#define FI2C0_BASE_ADDR 0x28011000
#define FI2C1_BASE_ADDR 0x28012000
#define FI2C2_BASE_ADDR 0x28013000

#define FI2C0_IRQ_NUM 121
#define FI2C1_IRQ_NUM 122
#define FI2C2_IRQ_NUM 123

#define FI2C_CLK_FREQ_HZ 50000000 /* 50MHz */

/* SDIF */
#define FSDIF0_ID  0
#define FSDIF1_ID  1
#define FSDIF_NUM  2


#define FSDIF0_BASE_ADDR 0x28000000U
#define FSDIF1_BASE_ADDR 0x28001000U

#define FSDIF0_IRQ_NUM 104U
#define FSDIF1_IRQ_NUM 105U

#define FSDIF_CLK_FREQ_HZ (1200000000UL) /* 1.2GHz */

/* NAND */
#define FNAND_NUM 1U
#define FNAND_INSTANCE0 0U
#define FNAND_BASE_ADDR 0x28002000U
#define FNAND_IRQ_NUM (106U)
#define FNAND_CONNECT_MAX_NUM 1U

#define FIOPAD_BASE_ADDR            0x32B30000U

/* DDMA */
#define FDDMA0_ID                0U
#define FDDMA0_BASE_ADDR         0x28003000U
#define FDDMA0_IRQ_NUM           107U
#define FDDMA0_CAPACITY          (1U<<1) 

#define FDDMA1_ID                1U
#define FDDMA1_BASE_ADDR         0x28004000U
#define FDDMA1_IRQ_NUM           108U
#define FDDMA1_CAPACITY          (1U<<1) 

#define FDDMA2_I2S_ID            2U
#define FDDMA2_BASE_ADDR         0x28005000U
#define FDDMA2_IRQ_NUM           109U
#define FDDMA2_CAPACITY          (1U<<0) 

#define FDDMA3_DP0_I2S_ID        3U
#define FDDMA3_BASE_ADDR         0x32008000U
#define FDDMA3_IRQ_NUM           79U
#define FDDMA3_CAPACITY          (1U<<0) 

#define FDDMA4_DP1_I2S_ID        4U
#define FDDMA4_BASE_ADDR         0x3200A000U
#define FDDMA4_IRQ_NUM           80U
#define FDDMA4_CAPACITY          (1U<<0) 

#define FDDMA_INSTANCE_NUM       5U

#define FDDMA0_UART0_TX_SLAVE_ID          2U  /* uart0 tx slave-id */
#define FDDMA0_UART1_TX_SLAVE_ID          3U  /* uart1 tx slave-id */
#define FDDMA0_UART2_TX_SLAVE_ID          4U  /* uart2 tx slave-id */
#define FDDMA0_UART3_TX_SLAVE_ID          5U  /* uart3 tx slave-id */

#define FDDMA0_SPIM0_TX_SLAVE_ID          6U  /* spi0 tx slave-id */
#define FDDMA0_SPIM1_TX_SLAVE_ID          7U  /* spi1 tx slave-id */
#define FDDMA0_SPIM2_TX_SLAVE_ID          8U  /* spi2 tx slave-id */
#define FDDMA0_SPIM3_TX_SLAVE_ID          9U  /* spi3 tx slave-id */

#define FDDMA0_UART0_RX_SLAVE_ID          15U  /* uart0 rx slave-id */
#define FDDMA0_UART1_RX_SLAVE_ID          16U  /* uart1 rx slave-id */
#define FDDMA0_UART2_RX_SLAVE_ID          17U  /* uart2 rx slave-id */
#define FDDMA0_UART3_RX_SLAVE_ID          18U  /* uart3 rx slave-id */

#define FDDMA0_SPIM0_RX_SLAVE_ID          19U /* spi0 rx slave-id */
#define FDDMA0_SPIM1_RX_SLAVE_ID          20U /* spi1 rx slave-id */
#define FDDMA0_SPIM2_RX_SLAVE_ID          21U /* spi2 rx slave-id */
#define FDDMA0_SPIM3_RX_SLAVE_ID          22U /* spi3 rx slave-id */

/* FDDMA1_ID */
#define FDDMA1_MIO0_TX_SLAVE_ID          0U  /* mio0 rx slave-id */
#define FDDMA1_MIO1_TX_SLAVE_ID          1U  /* mio1 rx slave-id */
#define FDDMA1_MIO2_TX_SLAVE_ID          2U  /* mio2 rx slave-id */
#define FDDMA1_MIO3_TX_SLAVE_ID          3U  /* mio3 rx slave-id */
#define FDDMA1_MIO4_TX_SLAVE_ID          4U  /* mio4 rx slave-id */
#define FDDMA1_MIO5_TX_SLAVE_ID          5U  /* mio5 rx slave-id */
#define FDDMA1_MIO6_TX_SLAVE_ID          6U  /* mio6 rx slave-id */
#define FDDMA1_MIO7_TX_SLAVE_ID          7U  /* mio7 rx slave-id */
#define FDDMA1_MIO8_TX_SLAVE_ID          8U  /* mio8 rx slave-id */
#define FDDMA1_MIO9_TX_SLAVE_ID          9U  /* mio9 rx slave-id */
#define FDDMA1_MIO10_TX_SLAVE_ID         10U  /* mio10 rx slave-id */
#define FDDMA1_MIO11_TX_SLAVE_ID         11U  /* mio11 rx slave-id */
#define FDDMA1_MIO12_TX_SLAVE_ID         12U  /* mio12 rx slave-id */
#define FDDMA1_MIO13_TX_SLAVE_ID         13U  /* mio13 rx slave-id */
#define FDDMA1_MIO14_TX_SLAVE_ID         14U  /* mio14 rx slave-id */
#define FDDMA1_MIO15_TX_SLAVE_ID         15U  /* mio15 rx slave-id */

#define FDDMA1_MIO0_RX_SLAVE_ID         16U  /* mio0 tx slave-id */
#define FDDMA1_MIO1_RX_SLAVE_ID         17U  /* mio1 tx slave-id */
#define FDDMA1_MIO2_RX_SLAVE_ID         18U  /* mio2 tx slave-id */
#define FDDMA1_MIO3_RX_SLAVE_ID         19U  /* mio3 tx slave-id */
#define FDDMA1_MIO4_RX_SLAVE_ID         20U  /* mio4 tx slave-id */
#define FDDMA1_MIO5_RX_SLAVE_ID         21U  /* mio5 tx slave-id */
#define FDDMA1_MIO6_RX_SLAVE_ID         22U  /* mio6 tx slave-id */
#define FDDMA1_MIO7_RX_SLAVE_ID         23U  /* mio7 tx slave-id */
#define FDDMA1_MIO8_RX_SLAVE_ID         24U  /* mio8 tx slave-id */
#define FDDMA1_MIO9_RX_SLAVE_ID         25U  /* mio9 tx slave-id */
#define FDDMA1_MIO10_RX_SLAVE_ID        26U  /* mio10 tx slave-id */
#define FDDMA1_MIO11_RX_SLAVE_ID        27U  /* mio11 tx slave-id */
#define FDDMA1_MIO12_RX_SLAVE_ID        28U  /* mio12 tx slave-id */
#define FDDMA1_MIO13_RX_SLAVE_ID        29U  /* mio13 tx slave-id */
#define FDDMA1_MIO14_RX_SLAVE_ID        30U  /* mio14 tx slave-id */
#define FDDMA1_MIO15_RX_SLAVE_ID        31U  /* mio15 tx slave-id */

#define FDDMA_MIN_SLAVE_ID               0U
#define FDDMA_MAX_SLAVE_ID               31U

/* ADC */
#define  FADC0_ID    0
#define  FADC_NUM    1

#if !defined(__ASSEMBLER__)
typedef enum
{
    FADC_CHANNEL_0 = 0,
    FADC_CHANNEL_1 = 1,
    FADC_CHANNEL_2,
    FADC_CHANNEL_3,
    FADC_CHANNEL_4,
    FADC_CHANNEL_5,
    FADC_CHANNEL_6,
    FADC_CHANNEL_7,

    FADC_CHANNEL_NUM
} FAdcChannel;

#endif

#define FADC0_BASE_ADDR 0x2807B000U

#define FADC0_IRQ_NUM 264U

/* PWM */
#define FPWM0_ID    0
#define FPWM1_ID    1
#define FPWM2_ID    2
#define FPWM3_ID    3
#define FPWM4_ID    4
#define FPWM5_ID    5
#define FPWM6_ID    6
#define FPWM7_ID    7
#define FPWM_NUM    8

#define FPWM_CHANNEL_0  0
#define FPWM_CHANNEL_1  1
#define FPWM_CHANNEL_NUM 2


#define FPWM_BASE_ADDR 0x2804A000U

#define FPWM_CLK_FREQ_HZ 50000000U /* 50MHz */

#define FPWM0_IRQ_NUM 205U
#define FPWM1_IRQ_NUM 206U
#define FPWM2_IRQ_NUM 207U
#define FPWM3_IRQ_NUM 208U
#define FPWM4_IRQ_NUM 209U
#define FPWM5_IRQ_NUM 210U
#define FPWM6_IRQ_NUM 211U
#define FPWM7_IRQ_NUM 212U
#define FPWM8_IRQ_NUM 213U
#define FPWM9_IRQ_NUM 214U
#define FPWM10_IRQ_NUM 215U
#define FPWM11_IRQ_NUM 216U
#define FPWM12_IRQ_NUM 217U
#define FPWM13_IRQ_NUM 218U
#define FPWM14_IRQ_NUM 219U
#define FPWM15_IRQ_NUM 220U

/* Semaphore */
#define FSEMA0_ID               0U
#define FSEMA0_BASE_ADDR        0x32B36000U
#define FSEMA_INSTANCE_NUM      1U

/* LSD Config */
#define FLSD_CONFIG_BASE            0x2807E000U
#define FLSD_NAND_MMCSD_HADDR       0xC0U
#define FLSD_CK_STOP_CONFIG0_HADDR  0x10U

/* USB3 */
#define FUSB3_ID_0 0U
#define FUSB3_ID_1 1U
#define FUSB3_NUM 2U
#define FUSB3_XHCI_OFFSET 0x8000U
#define FUSB3_0_BASE_ADDR 0x31A00000U
#define FUSB3_1_BASE_ADDR 0x31A20000U
#define FUSB3_0_IRQ_NUM 48U
#define FUSB3_1_IRQ_NUM 49U


/*I2S*/

#define FI2S0_ID 0U
#define FI2S1_ID 1U
#define FI2S2_ID 2U
#define FI2S_NUM 3U

#define FI2S0_BASE_ADDR 0x28009000 
#define FI2S0_IRQ_NUM 112

#define FI2S1_BASE_ADDR 0x32009000 /*i2s for dp0*/
#define FI2S1_IRQ_NUM 77

#define FI2S2_BASE_ADDR 0x3200B000 /*i2s for dp1*/
#define FI2S2_IRQ_NUM 78


/* DcDp */
#if !defined(__ASSEMBLER__)

typedef enum
{
    FDCDP_ID0 = 0,
    FDCDP_ID1,

    FDCDP_INSTANCE_NUM
} FDcDpNum;

#endif

#define FDC_CTRL_BASE_OFFSET 0x32000000U

#define FDC0_CHANNEL_BASE_OFFSET 0x32001000U
#define FDC1_CHANNEL_BASE_OFFSET (FDC0_CHANNEL_BASE_OFFSET + 0x1000U)

#define FDP0_CHANNEL_BASE_OFFSET 0x32004000U
#define FDP1_CHANNEL_BASE_OFFSET (FDP0_CHANNEL_BASE_OFFSET + 0x1000U)

#define FDP0_PHY_BASE_OFFSET 0x32300000U
#define FDP1_PHY_BASE_OFFSET (FDP0_PHY_BASE_OFFSET + 0x100000U)

#define FDCDP_IRQ_NUM 76

/* generic timer */
/* non-secure physical timer int id */
#define GENERIC_TIMER_NS_IRQ_NUM 30U

/* virtual timer int id */
#define GENERIC_VTIMER_IRQ_NUM 27U


#define GENERIC_TIMER_ID0   0 /* non-secure physical timer */
#define GENERIC_TIMER_ID1   1 /* virtual timer */
#define GENERIC_TIMER_NUM   2

/*****************************************************************************/

#ifdef __cplusplus
}

#endif

#endif