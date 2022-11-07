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
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef BOARD_E2000_PARAMTERERS_COMMON_H
#define BOARD_E2000_PARAMTERERS_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/
#if !defined(__ASSEMBLER__)
#include "ftypes.h"
#endif

/************************** Constant Definitions *****************************/
/* CACHE */
#define CACHE_LINE_ADDR_MASK 0x3FU
#define CACHE_LINE  64U

/* DEVICE Register Address */
#define FT_DEV_BASE_ADDR 0x28000000U
#define FT_DEV_END_ADDR 0x2FFFFFFFU

/* PCI */
#define FT_PCIE_NUM 1
#define FT_PCIE0_ID 0
#define FT_PCIE0_MISC_IRQ_NUM 40

#define FT_PCIE_CFG_MAX_NUM_OF_BUS 256
#define FT_PCIE_CFG_MAX_NUM_OF_DEV 32
#define FT_PCIE_CFG_MAX_NUM_OF_FUN 8

#define FT_PCI_CONFIG_BASEADDR 0x40000000U
#define FT_PCI_CONFIG_REG_LENGTH 0x10000000U

#define FT_PCI_IO_CONFIG_BASEADDR 0x50000000U
#define FT_PCI_IO_CONFIG_REG_LENGTH 0x08000000U

#define FT_PCI_MEM32_BASEADDR 0x58000000U
#define FT_PCI_MEM32_REG_LENGTH 0x27FFFFFFU

#define FT_PCI_MEM64_BASEADDR 0x1000000000U
#define FT_PCI_MEM64_REG_LENGTH 0x1000000000U

#define FT_PCI_EU0_C0_CONTROL_BASEADDR 0x29000000U
#define FT_PCI_EU0_C1_CONTROL_BASEADDR 0x29010000U
#define FT_PCI_EU0_C2_CONTROL_BASEADDR 0x29020000U
#define FT_PCI_EU1_C0_CONTROL_BASEADDR 0x29030000U
#define FT_PCI_EU1_C1_CONTROL_BASEADDR 0x29040000U
#define FT_PCI_EU1_C2_CONTROL_BASEADDR 0x29050000U

#define FT_PCI_EU0_CONFIG_BASEADDR 0x29100000U
#define FT_PCI_EU1_CONFIG_BASEADDR 0x29101000U

#define FT_PCI_INTA_IRQ_NUM     36
#define FT_PCI_INTB_IRQ_NUM     37
#define FT_PCI_INTC_IRQ_NUM     38
#define FT_PCI_INTD_IRQ_NUM     39

#define FT_PCI_NEED_SKIP        0

#define FT_PCI_INTX_PEU0_STAT   0x29100000U
#define FT_PCI_INTX_PEU1_STAT   0x29101000U

#define FT_PCI_INTX_EU0_C0_CONTROL  0x29000184U
#define FT_PCI_INTX_EU0_C1_CONTROL  0x29010184U
#define FT_PCI_INTX_EU0_C2_CONTROL  0x29020184U
#define FT_PCI_INTX_EU1_C0_CONTROL  0x29030184U
#define FT_PCI_INTX_EU1_C1_CONTROL  0x29040184U
#define FT_PCI_INTX_EU1_C2_CONTROL  0x29050184U

#define FT_PCI_INTX_CONTROL_NUM 6 /* Total number of controllers */
#define FT_PCI_INTX_SATA_NUM 2 /* Total number of controllers */


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
#define FSATA0_BASEADDR 0x31A40000U
#define FSATA1_BASEADDR 0x32014000U

#define FSATA0_IRQNUM   74
#define FSATA1_IRQNUM   75

#if !defined(__ASSEMBLER__)
typedef enum
{
    FSATA_INSTANCE_0 = 0,
    FSATA_INSTANCE_1 = 1,

    FSATA_INSTANCE_NUM
} FSataInstance;
#endif

/* Generic Timer */
#define GENERIC_TIMER_CLK_FREQ_MHZ 48U
#define GENERIC_TIMER_NS_IRQ_NUM 30U
#define GENERIC_TIMER_NS_CLK_FREQ 2000000U
#define COUNTS_PER_SECOND GENERIC_TIMER_NS_CLK_FREQ

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

#define ARM_GIC_NR_IRQS 160U
#define ARM_GIC_IRQ_START 0U
#define FGIC_NUM 1U

#define ARM_GIC_IPI_COUNT 16U /* MPCore IPI count         */
#define SGI_INT_MAX 16U
#define SPI_START_INT_NUM 32U /* SPI start at ID32        */
#define PPI_START_INT_NUM 16U /* PPI start at ID16        */
#define GIC_INT_MAX_NUM 1020U /* GIC max interrupts count */

#define GICV3_BASEADDRESS 0x30800000U
#define GICV3_DISTRIBUTOR_BASEADDRESS (GICV3_BASEADDRESS + 0)
#define GICV3_RD_BASEADDRESS (GICV3_BASEADDRESS + 0x80000U)
#define GICV3_RD_OFFSET (2U << 16)
#define FT_GICV3_VECTORTABLE_NUM GIC_INT_MAX_NUM

/* GPIO */
#define FGPIO_ID_0                      0U
#define FGPIO_ID_1                      1U
#define FGPIO_ID_2                      2U
#define FGPIO_WITH_PIN_IRQ              2U /* max id of gpio assign irq for each pin */
#define FGPIO_ID_3                      3U
#define FGPIO_ID_4                      4U
#define FGPIO_ID_5                      5U
#define FGPIO_NUM                       6U

#define FGPIO_0_BASE_ADDR               0x28034000U
#define FGPIO_1_BASE_ADDR               0x28035000U
#define FGPIO_2_BASE_ADDR               0x28036000U
#define FGPIO_3_BASE_ADDR               0x28037000U
#define FGPIO_4_BASE_ADDR               0x28038000U
#define FGPIO_5_BASE_ADDR               0x28039000U

#define FGPIO_CTRL_PIN_NUM              16U

#define FGPIO_PIN_IRQ_BASE              140U
#define FGPIO_PIN_IRQ_NUM_GET(id, pin)  (FGPIO_PIN_IRQ_BASE + FGPIO_CTRL_PIN_NUM * (id) + (pin))

#define FGPIO_3_IRQ_NUM                 188U
#define FGPIO_4_IRQ_NUM                 189U
#define FGPIO_5_IRQ_NUM                 190U

#define FGPIO_PIN_IRQ_TOTAL             51U

/* SPI */
#define FSPI0_BASE 0x2803A000U
#define FSPI1_BASE 0x2803B000U
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

#define FSPI_FREQ 50000000U
#define FSPI_DEVICE_NUM 4U

/* XMAC */
#define FT_XMAC_NUM 4U

#define FT_XMAC0_ID 0U
#define FT_XMAC1_ID 1U
#define FT_XMAC2_ID 2U
#define FT_XMAC3_ID 3U

#define FT_XMAC0_BASEADDRESS 0x3200C000U
#define FT_XMAC1_BASEADDRESS 0x3200E000U
#define FT_XMAC2_BASEADDRESS 0x32010000U
#define FT_XMAC3_BASEADDRESS 0x32012000U

#define FT_XMAC0_MODE_SEL_BASEADDRESS 0x3200DC00U
#define FT_XMAC0_LOOPBACK_SEL_BASEADDRESS 0x3200DC04U
#define FT_XMAC1_MODE_SEL_BASEADDRESS 0x3200FC00U
#define FT_XMAC1_LOOPBACK_SEL_BASEADDRESS 0x3200FC04U
#define FT_XMAC2_MODE_SEL_BASEADDRESS 0x32011C00U
#define FT_XMAC2_LOOPBACK_SEL_BASEADDRESS 0x32011C04U
#define FT_XMAC3_MODE_SEL_BASEADDRESS 0x32013C00U
#define FT_XMAC3_LOOPBACK_SEL_BASEADDRESS 0x32013C04U

#define FT_XMAC0_PCLK 50000000U
#define FT_XMAC1_PCLK 50000000U
#define FT_XMAC2_PCLK 50000000U
#define FT_XMAC3_PCLK 50000000U
#define FT_XMAC0_HOTPLUG_IRQ_NUM (53U + 30U)
#define FT_XMAC1_HOTPLUG_IRQ_NUM (54U + 30U)
#define FT_XMAC2_HOTPLUG_IRQ_NUM (55U + 30U)
#define FT_XMAC3_HOTPLUG_IRQ_NUM (56U + 30U)

#define FT_XMAC_QUEUE_MAX_NUM 16U

#define FT_XMAC0_QUEUE0_IRQ_NUM (57U + 30U)
#define FT_XMAC0_QUEUE1_IRQ_NUM (58U + 30U)
#define FT_XMAC0_QUEUE2_IRQ_NUM (59U + 30U)
#define FT_XMAC0_QUEUE3_IRQ_NUM (60U + 30U)
#define FT_XMAC0_QUEUE4_IRQ_NUM (30U + 30U)
#define FT_XMAC0_QUEUE5_IRQ_NUM (31U + 30U)
#define FT_XMAC0_QUEUE6_IRQ_NUM (32U + 30U)
#define FT_XMAC0_QUEUE7_IRQ_NUM (33U + 30U)

#define FT_XMAC1_QUEUE0_IRQ_NUM (61U + 30U)
#define FT_XMAC1_QUEUE1_IRQ_NUM (62U + 30U)
#define FT_XMAC1_QUEUE2_IRQ_NUM (63U + 30U)
#define FT_XMAC1_QUEUE3_IRQ_NUM (64U + 30U)

#define FT_XMAC2_QUEUE0_IRQ_NUM (66U + 30U)
#define FT_XMAC2_QUEUE1_IRQ_NUM (67U + 30U)
#define FT_XMAC2_QUEUE2_IRQ_NUM (68U + 30U)
#define FT_XMAC2_QUEUE3_IRQ_NUM (69U + 30U)

#define FT_XMAC3_QUEUE0_IRQ_NUM (70U + 30U)
#define FT_XMAC3_QUEUE1_IRQ_NUM (71U + 30U)
#define FT_XMAC3_QUEUE2_IRQ_NUM (72U + 30U)
#define FT_XMAC3_QUEUE3_IRQ_NUM (73U + 30U)

#define FT_XMAC_PHY_MAX_NUM 32U

/* QSPI */

#define FQSPI_BASEADDR 0x028008000U

#if !defined(__ASSEMBLER__)

typedef enum
{
    FQSPI_INSTANCE_0 = 0,

    FQSPI_INSTANCE_NUM
} FQspiInstance;

/* FQSPI cs 0_3, chip number */
typedef enum
{
    FQSPI_CS_0 = 0,
    FQSPI_CS_1 = 1,
    FQSPI_CS_2 = 2,
    FQSPI_CS_3 = 3,
    FQSPI_CS_NUM
} FQspiChipCS;

#endif

#define FQSPI_MEM_START_ADDR 0x0U
#define FQSPI_MEM_END_ADDR 0x0FFFFFFFU /* 256MB */
#define FQSPI_MEM_START_ADDR_64 0x100000000U
#define FQSPI_MEM_END_ADDR_64 0x17FFFFFFFU /* 2GB */

/* TIMER and TACHO */
#define TIMER_NUM 38U
#define TACHO_NUM 16U
#define TIMER_CLK_FREQ_HZ 50000000U /* 50MHz */
#define TIMER_TICK_PERIOD_NS 20U      /* 20ns */
#define TIMER_TACHO_IRQ_ID(n) (226U + (n))
#define TIMER_TACHO_BASE_ADDR(n) (0x28054000U + 0x1000U * (n))

#if !defined(__ASSEMBLER__)
typedef enum
{
    TACHO_INSTANCE_0 = 0,
    TACHO_INSTANCE_1 = 1,
    TACHO_INSTANCE_2 = 2,
    TACHO_INSTANCE_3 = 3,
    TACHO_INSTANCE_4 = 4,
    TACHO_INSTANCE_5 = 5,
    TACHO_INSTANCE_6 = 6,
    TACHO_INSTANCE_7 = 7,
    TACHO_INSTANCE_8 = 8,
    TACHO_INSTANCE_9 = 9,
    TACHO_INSTANCE_10 = 10,
    TACHO_INSTANCE_11 = 11,
    TACHO_INSTANCE_12 = 12,
    TACHO_INSTANCE_13 = 13,
    TACHO_INSTANCE_14 = 14,
    TACHO_INSTANCE_15 = 15,

    TACHO_INSTANCE_NUM
} TachoInstance;
#endif

/* GDMA */
#define FGDMA0_ID           0U
#define FGDMA0_BASE_ADDR    0x32B34000U
#define FGDMA0_IRQ_NUM      266U

#define FGDMA_INSTANCE_NUM  1U

/* CANFD */
#define FCAN_REF_CLOCK 200000000U

#define FCAN0_BASEADDR 0x2800A000U
#define FCAN1_BASEADDR 0x2800B000U

#define FCAN0_IRQNUM 113U
#define FCAN1_IRQNUM 114U

#if !defined(__ASSEMBLER__)
typedef enum
{
    FCAN_INSTANCE_0 = 0,
    FCAN_INSTANCE_1 = 1,

    FCAN_INSTANCE_NUM
} FCanInstance;
#endif

/* WDT */
#if !defined(__ASSEMBLER__)
typedef enum
{
    FWDT_INSTANCE_0 = 0,
    FWDT_INSTANCE_1,

    FWDT_INSTANCE_NUM
} FWdtInstance;
#endif

#define FWDT0_REFRESH_BASE 0x28040000U
#define FWDT0_CONTROL_BASE 0x28041000U
#define FWDT1_REFRESH_BASE 0x28042000U
#define FWDT1_CONTROL_BASE 0x28043000U

#define FWDT0_INTR_IRQ 196U
#define FWDT1_INTR_IRQ 197U

#define FWDT_CLK 48000000U /* 48MHz */

/*MIO*/
#define FMIO_NUM 16
#define FMIO_BASE_ADDR(n) (0x28014000 + 0x2000 * (n))
#define FMIO_CONF_ADDR(n) FMIO_BASE_ADDR(n)+0x1000
#define FMIO_IRQ_NUM(n) (124+n)
#define MIO_REF_CLK_HZ 50000000 /* 50MHz */

#if !defined(__ASSEMBLER__)
typedef enum
{
    MIO_INSTANCE_0 = 0,
    MIO_INSTANCE_1,
    MIO_INSTANCE_2,
    MIO_INSTANCE_3,
    MIO_INSTANCE_4,
    MIO_INSTANCE_5,
    MIO_INSTANCE_6,
    MIO_INSTANCE_7,
    MIO_INSTANCE_8,
    MIO_INSTANCE_9,
    MIO_INSTANCE_10,
    MIO_INSTANCE_11,
    MIO_INSTANCE_12,
    MIO_INSTANCE_13,
    MIO_INSTANCE_14,
    MIO_INSTANCE_15,

    MIO_INSTANCE_NUM
} MioInstance;
#endif

#if !defined(__ASSEMBLER__)
/*I2C0 -> PMBUS0
* I2C1 -> PMBUS1
* I2C2 -> SMBUS0
*/
typedef enum
{
    I2C_INSTANCE_0 = 0,
    I2C_INSTANCE_1,
    I2C_INSTANCE_2,

    I2C_INSTANCE_NUM
} I2cInstance;
#endif

#define I2C_0_BASEADDR 0x28011000
#define I2C_1_BASEADDR 0x28012000
#define I2C_2_BASEADDR 0x28013000

#define I2C_0_INTR_IRQ 121
#define I2C_1_INTR_IRQ 122
#define I2C_2_INTR_IRQ 123

#define I2C_REF_CLK_HZ 50000000 /* 50MHz */

/* SDIO */
#if !defined(__ASSEMBLER__)
enum
{
    FSDIO_HOST_INSTANCE_0 = 0,
    FSDIO_HOST_INSTANCE_1,

    FSDIO_HOST_INSTANCE_NUM
};
#endif

#define FSDIO_HOST_0_BASE_ADDR 0x28000000U
#define FSDIO_HOST_1_BASE_ADDR 0x28001000U

#define FSDIO_HOST_0_IRQ_NUM 104U
#define FSDIO_HOST_1_IRQ_NUM 105U

#define FSDIO_CLK_RATE_HZ (1200000000UL) /* 1.2GHz */

/* NAND */
#define FNAND_NUM 1U
#define FNAND_INSTANCE0 0U
#define FNAND_BASEADDRESS 0x28002000U
#define FNAND_IRQ_NUM (106U)
#define FNAND_CONNECT_MAX_NUM 1U

#define FIOPAD_BASE_ADDR            0x32B30000U

/* DDMA */
#define FDDMA0_ID                0U
#define FDDMA0_BASE_ADDR         0x28003000U
#define FDDMA0_IRQ_NUM           107U

#define FDDMA1_ID                1U
#define FDDMA1_BASE_ADDR         0x28004000U
#define FDDMA1_IRQ_NUM           108U

#define FDDMA_INSTANCE_NUM       2U

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

#define FDDMA_MIN_SLAVE_ID               0U
#define FDDMA_MAX_SLAVE_ID               31U

/* ADC */
#if !defined(__ASSEMBLER__)
typedef enum
{
    FADC_INSTANCE_0 = 0,
    FADC_INSTANCE_1,

    FADC_INSTANCE_NUM
} FAdcInstance;

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

#define FADC0_CONTROL_BASE 0x2807B000U
#define FADC1_CONTROL_BASE 0x2807C000U

#define FADC0_INTR_IRQ 264U
#define FADC1_INTR_IRQ 265U

/* PWM */
#if !defined(__ASSEMBLER__)
typedef enum
{
    FPWM_INSTANCE_0 = 0,
    FPWM_INSTANCE_1,
    FPWM_INSTANCE_2,
    FPWM_INSTANCE_3,
    FPWM_INSTANCE_4,
    FPWM_INSTANCE_5,
    FPWM_INSTANCE_6,
    FPWM_INSTANCE_7,

    FPWM_INSTANCE_NUM
} FPwmInstance;

typedef enum
{
    FPWM_CHANNEL_0 = 0,
    FPWM_CHANNEL_1,

    FPWM_CHANNEL_NUM
} FPwmChannel;
#endif

#define FPWM_CONTROL_BASE 0x2804A000U

#define FPWM_CLK 50000000U /* 50MHz */

#define FPWM0_INTR_IRQ 205U
#define FPWM1_INTR_IRQ 206U
#define FPWM2_INTR_IRQ 207U
#define FPWM3_INTR_IRQ 208U
#define FPWM4_INTR_IRQ 209U
#define FPWM5_INTR_IRQ 210U
#define FPWM6_INTR_IRQ 211U
#define FPWM7_INTR_IRQ 212U
#define FPWM8_INTR_IRQ 213U
#define FPWM9_INTR_IRQ 214U
#define FPWM10_INTR_IRQ 215U
#define FPWM11_INTR_IRQ 216U
#define FPWM12_INTR_IRQ 217U
#define FPWM13_INTR_IRQ 218U
#define FPWM14_INTR_IRQ 219U
#define FPWM15_INTR_IRQ 220U

/* Semaphore */
#define FSEMA0_ID               0U
#define FSEMA0_BASE_ADDR        0x32B36000U
#define FSEMA_INSTANCE_NUM      1U

/* LSD Config */
#define FLSD_CONFIG_BASE            0x2807E000U
#define FLSD_NAND_MMCSD_HADDR       0xC0U
#define FLSD_CK_STOP_CONFIG0_HADDR  0x10U

/* USB3 */
#define FUSB3_ID_0         0U
#define FUSB3_ID_1         1U
#define FUSB3_NUM          2U
#define FUSB3_XHCI_OFFSET  0x8000U
#define FUSB3_0_BASE_ADDR  0x31A00000U
#define FUSB3_1_BASE_ADDR  0x31A20000U
#define FUSB3_0_IRQ_NUM    48U
#define FUSB3_1_IRQ_NUM    49U
/*****************************************************************************/

#ifdef __cplusplus
}

#endif

#endif