/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 *  Date: 2021-03-30 14:57:03
 * @LastEditTime: 2021-05-24 14:35:00
 *  Description:  definitions of BSP parameters
 *  Modify History:
 * * * Ver   Who        Date            Changes
 * * ----- ------     --------    ----------------------------------------------
 *   1.00   Huanghe   2021/3/1     init
 */

#ifndef FT_PARAMETERS_H
#define FT_PARAMETERS_H

/*  Device register address */
#define FT_DEV_BASE_ADDR 0x28000000
#define FT_DEV_END_ADDR 0x2FFFFFFF

/******** UART  ************/

#define FT_UART_NUM 4
#define FT_UART_REG_LENGTH 0x18000

#define FT_UART0_ID 0
#define FT_UART0_BASE_ADDR 0x28000000
#define FT_UART0_CLK_FREQ_HZ 48000000

#define FT_UART1_ID 1
#define FT_UART1_BASE_ADDR 0x28001000
#define FT_UART1_CLK_FREQ_HZ 48000000

#define FT_UART2_ID 2
#define FT_UART2_BASE_ADDR 0x28002000
#define FT_UART2_CLK_FREQ_HZ 48000000

#define FT_UART3_BASE_ADDR 0x28003000
#define FT_UART3_ID 3
#define FT_UART3_CLK_FREQ_HZ 48000000

#define FT_STDOUT_BASEADDRESS FT_UART1_BASE_ADDR
#define FT_STDIN_BASEADDRESS FT_UART1_BASE_ADDR

/****** GIC v3  *****/
#define FT_GICV3_INSTANCES_NUM 1U
#define GICV3_REG_LENGTH 0x00009000

/*
 * The maximum priority value that can be used in the GIC.
 */
#define GICV3_MAX_INTR_PRIO_VAL 240U
#define GICV3_INTR_PRIO_MASK 0x000000f0U

#define ARM_GIC_IPI_COUNT 16 /* MPCore IPI count         */
#define SGI_INT_MAX 16
#define SPI_START_INT_NUM 32 /* SPI start at ID32        */
#define PPI_START_INT_NUM 16 /* PPI start at ID16        */
#define GIC_INT_MAX_NUM 1020 /* GIC max interrupts count */

#define FT_GICV3_BASEADDRESS 0x29900000U
#define FT_GICV3_DISTRIBUTOR_BASEADDRESS (FT_GICV3_BASEADDRESS + 0)
#define FT_GICV3_RD_BASEADDRESS (FT_GICV3_BASEADDRESS + 0x80000U)
#define FT_GICV3_SGI_BASEADDRESS (FT_GICV3_RD_BASEADDRESS + (1U << 16))

#define FT_GICV3_VECTORTABLE_NUM GIC_INT_MAX_NUM

/** Gmac **/
#define FT_GMAC_INSTANCES_NUM 2U
#define FT_GMAC_REG_LENGTH 0x00009000

#define FT_GMAC_COMMON_ADDR 0x2820B000U

#define FT_GMAC0_ID 0
#define FT_GMAC0_BASEADDR 0x2820C000U
#define FT_GMAC0_DEFAULT_ADDR          \
  {                                    \
    0x11, 0x1c, 0x2c, 0x5c, 0x66, 0x88 \
  }

#define FT_GMAC1_ID 1
#define FT_GMAC1_BASEADDR 0x28210000U

/** @defgroup ENET_Buffers_setting
  * @{
  */
#define GMAC_MAX_PACKET_SIZE 1600 /* GMAC_HEADER + GMAC_EXTRA + VLAN_TAG + MAX_GMAC_PAYLOAD + GMAC_CRC */
#define GMAC_HEADER 14            /* 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define GMAC_CRC 4                /* Gmac CRC */
#define GMAC_EXTRA 2              /* Extra bytes in some cases */
#define VLAN_TAG 4                /* optional 802.1q VLAN Tag */
#define MIN_GMAC_PAYLOAD 46       /* Minimum Gmac payload size */
#define MAX_GMAC_PAYLOAD 1500     /* Maximum Gmac payload size */
#define JUMBO_FRAME_PAYLOAD 9000  /* Jumbo frame payload size */
#define RX_DESCNUM 1024U          /* Rx buffers of size GMAC_MAX_PACKET_SIZE  */
#define TX_DESCNUM 1024U          /* Tx buffers of size GMAC_MAX_PACKET_SIZE  */

#define PHY_USING_AR8035

#define GMAC0_ISRNUM 81
#define GMAC0_ISRPRIORITY 0

#define GMAC1_ISRNUM 82
#define GMAC1_ISRPRIORITY 0

/* SDC */
#define FT_SDC_NUM 1
#define FT_SDC_INSTANCE 0
#define FT_SDC_BASEADDR 0x28207C00U
#define FT_SDC_REG_LENGTH 0x4000
#define FT_SDC_FREQ 600000000

/* pin MUX/DEMUX */

#define FT_PIN_MUX_BASEADDR 0x28180000
#define FT_PIN_MUX_REG_LENGTH 0x10000

/* CAN */

#define FT_CAN_NUM 3
#define FT_CAN_REG_LENGTH 0x1000
#define FT_CAN0_BASEADDR 0x28207000
#define FT_CAN1_BASEADDR 0x28207400
#define FT_CAN2_BASEADDR 0x28207800
#define FT_CAN0_IRQNUM 119
#define FT_CAN1_IRQNUM 123
#define FT_CAN2_IRQNUM 124
#define FT_CAN_BAUDRATE 1000000 /* 1M */
#define FT_CAN_CLK 600000000

/* pci  */

#define FT_PCI_CONFIG_BASEADDR 0x40000000
#define FT_PCI_CONFIG_REG_LENGTH 0x10000000

#define FT_PCI_IO_CONFIG_BASEADDR 0x50000000
#define FT_PCI_IO_CONFIG_REG_LENGTH 0x08000000

#define FT_PCI_MEM32_BASEADDR 0x58000000
#define FT_PCI_MEM32_REG_LENGTH 0x27000000

/*  qspi  */
#define FT_QSPI_NUM 1U
#define FT_QSPI_INSTANCE 0
#define FT_QSPI_MAX_CS_NUM 4
#define FT_QSPI_BASEADDR 0x28014000

#define FT_QSPI_FLASH_CAP_4MB 0
#define FT_QSPI_FLASH_CAP_8MB 1
#define FT_QSPI_FLASH_CAP_16MB 2
#define FT_QSPI_FLASH_CAP_32MB 3
#define FT_QSPI_FLASH_CAP_64MB 4
#define FT_QSPI_FLASH_CAP_128MB 5
#define FT_QSPI_FLASH_CAP_256MB 6

#define FT_QSPI_ADDR_SEL_3 0
#define FT_QSPI_ADDR_SEL_4 1

#define FT_QSPI_SCK_DIV_128 0
#define FT_QSPI_SCK_DIV_2 1
#define FT_QSPI_SCK_DIV_4 2
#define FT_QSPI_SCK_DIV_8 3
#define FT_QSPI_SCK_DIV_16 4
#define FT_QSPI_SCK_DIV_32 5
#define FT_QSPI_SCK_DIV_64 6

#define FT_QSPI_TRANSFER_1_1_1 0
#define FT_QSPI_TRANSFER_1_1_2 1
#define FT_QSPI_TRANSFER_1_1_4 2
#define FT_QSPI_TRANSFER_1_2_2 3
#define FT_QSPI_TRANSFER_1_4_4 4
#define FT_QSPI_TRANSFER_2_2_2 5
#define FT_QSPI_TRANSFER_4_4_4 6

/* smp */

#define FT_SMP_EN

#endif // !
