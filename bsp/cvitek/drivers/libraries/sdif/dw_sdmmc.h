/*
* Copyright (C) Cvitek Co., Ltd. 2019-2029. All rights reserved.
*/
#ifndef __MMC_H__
#define __MMC_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "drv_ioremap.h"

#define TOP_BASE        0x03000000
#define DW_SDIO0_BASE               0x04320000
#define DW_SDIO1_BASE               0x04310000
#define DW_SDIO2_BASE               0x04300000

#define CONFIG_SDIO_NUM   3

#define MMC_CMD0            0
#define MMC_CMD1            1
#define MMC_CMD2            2
#define MMC_CMD3            3
#define MMC_CMD5            5
#define MMC_CMD6            6
#define MMC_CMD7            7
#define MMC_CMD8            8
#define MMC_CMD9            9
#define MMC_CMD11           11
#define MMC_CMD12           12
#define MMC_CMD13           13
#define MMC_CMD16           16
#define MMC_CMD17           17
#define MMC_CMD18           18
#define MMC_CMD19           19
#define MMC_CMD21           21
#define MMC_CMD23           23
#define MMC_CMD24           24
#define MMC_CMD25           25
#define MMC_CMD32           32
#define MMC_CMD33           33
#define MMC_CMD35           35
#define MMC_CMD36           36
#define MMC_CMD38           38
#define MMC_CMD52           52
#define MMC_CMD53           53
#define MMC_CMD55           55
#define SD_ACMD6            6
#define SD_ACMD13           13
#define SD_ACMD41           41
#define SD_ACMD42           42
#define SD_ACMD51           51

static inline int mmc_op_multi(uint32_t opcode)
{
    return opcode == MMC_CMD25 || opcode == MMC_CMD18;
}

#define SDIO0_IRQ           36
#define SDIO1_IRQ           38
#define SDIO2_IRQ           34
#define SDIO0_BASE          DRV_IOREMAP((void *)DW_SDIO1_BASE, 0x1000)
#define SDIO1_BASE          DRV_IOREMAP((void *)DW_SDIO0_BASE, 0x1000)
#define SDIO2_BASE          DRV_IOREMAP((void *)DW_SDIO2_BASE, 0x1000)

#define SDIF_DMA_ADDRESS               0x00
#define SDIF_BLOCK_SIZE                0x04
#define SDIF_MAKE_BLKSZ(dma, blksz)    ((((dma) & 0x7) << 12) | ((blksz) & 0xFFF))
#define SDIF_BLOCK_COUNT               0x06
#define SDIF_ARGUMENT                  0x08
#define SDIF_TRANSFER_MODE             0x0C
#define SDIF_TRNS_DMA                  BIT(0)
#define SDIF_TRNS_BLK_CNT_EN           BIT(1)
#define SDIF_TRNS_ACMD12               BIT(2)
#define SDIF_TRNS_READ                 BIT(4)
#define SDIF_TRNS_MULTI                BIT(5)
#define SDIF_TRNS_RESP_INT             BIT(8)
#define SDIF_COMMAND                   0x0E
#define SDIF_CMD_RESP_MASK             0x03
#define SDIF_CMD_CRC                   0x08
#define SDIF_CMD_INDEX                 0x10
#define SDIF_CMD_DATA                  0x20
#define SDIF_CMD_ABORTCMD              0xC0
#define SDIF_CMD_RESP_NONE             0x00
#define SDIF_CMD_RESP_LONG             0x01
#define SDIF_CMD_RESP_SHORT            0x02
#define SDIF_CMD_RESP_SHORT_BUSY       0x03
#define SDIF_MAKE_CMD(c, f)            ((((c) & 0xff) << 8) | ((f) & 0xff))
#define SDIF_RESPONSE_01               0x10
#define SDIF_RESPONSE_23               0x14
#define SDIF_RESPONSE_45               0x18
#define SDIF_RESPONSE_67               0x1C

#define SDIF_RESPONSE           0x10

#define SDIF_BUFFER         0x20

#define SDIF_PRESENT_STATE      0x24
#define SDIF_DATA_INHIBIT       0x00000002
#define SDIF_DOING_WRITE        0x00000100
#define SDIF_DOING_READ     0x00000200
#define SDIF_SPACE_AVAILABLE    0x00000400
#define SDIF_DATA_AVAILABLE 0x00000800
#define SDIF_CARD_PRESENT       0x00010000
#define SDIF_WRITE_PROTECT      0x00080000
#define SDIF_DATA_LVL_MASK      0x00F00000
#define SDIF_DATA_LVL_SHIFT 20
#define SDIF_DATA_0_LVL_MASK    0x00100000
#define SDIF_CMD_LVL            0x01000000

#define SDIF_CMD_INHIBIT               BIT(0)
#define SDIF_CMD_INHIBIT_DAT           BIT(1)
#define SDIF_CARD_INSERTED             BIT(16)
#define SDIF_CARD_STABLE               BIT(17)
#define SDIF_WR_PROTECT_SW_LVL         BIT(19)
#define SDIF_DAT_XFER_WIDTH            BIT(1)
#define SDIF_CTRL_SDMA                 0x00
#define SDIF_CTRL_HISPD                0x04
#define SDIF_BUS_VOL_VDD1_1_8V         0xC
#define SDIF_BUS_VOL_VDD1_3_0V         0xE
#define SDIF_CTRL_DMA_MASK             0x18
#define SDIF_BUF_DATA_R                0x20
#define SDIF_HOST_CONTROL              0x28
#define SDIF_PWR_CONTROL               0x29
#define SDIF_BLOCK_GAP_CONTROL         0x2A
#define SDIF_WAKE_UP_CONTROL           0x2B
#define SDIF_CLK_CTRL                  0x2C
#define SDIF_TOUT_CTRL                 0x2E
#define SDIF_SOFTWARE_RESET            0x2F
#define SDIF_RESET_CMD                 0x02
#define SDIF_RESET_DATA                0x04
#define SDIF_INT_STATUS                0x30
#define SDIF_ERR_INT_STATUS            0x32
#define SDIF_INT_ENABLE                0x34
#define SDIF_INT_XFER_COMPLETE         BIT(1)
#define SDIF_INT_BUF_RD_READY          BIT(5)
#define SDIF_INT_STATUS_EN             0x34
#define SDIF_ERR_INT_STATUS_EN         0x36
#define SDIF_SIGNAL_ENABLE             0x38
#define SDIF_ERROR_SIGNAL_ENABLE       0x3A
#define SDIF_AUTO_CMD_STATUS           0x3C
#define SDIF_HOST_CONTROL2             0x3E
#define SDIF_CAPABILITIES              0x40
#define SDIF_CAPABILITIES_1            0x44
#define SDIF_MAX_CURRENT               0x48
#define SDIF_ADMA_ERROR                0x54
#define SDIF_ADMA_ADDRESS              0x58
#define SDIF_ADMA_ADDRESS_HI           0x5C
#define SDIF_SLOT_INT_STATUS          0xFC
#define SDIF_HOST_VERSION              0xFE
#define SDIF_INT_XFER_COMPLETE_EN      BIT(1)
#define SDIF_INT_DMA_END_EN            BIT(3)
#define SDIF_INT_ERROR_EN              BIT(15)
#define SDIF_HOST_ADMA2_LEN_MODE       BIT(10)
#define SDIF_CTRL_UHS_MASK          0x0007
#define SDIF_CTRL_UHS_SDR12         0x0000
#define SDIF_CTRL_UHS_SDR25         0x0001
#define SDIF_CTRL_UHS_SDR50         0x0002
#define SDIF_CTRL_UHS_SDR104        0x0003
#define SDIF_CTRL_UHS_DDR50         0x0004
#define SDIF_CTRL_HS400         0x0005 /* Non-standard */
#define SDIF_CTRL_DRV_TYPE_MASK     0x0030
#define SDIF_CTRL_DRV_TYPE_B        0x0000
#define SDIF_CTRL_DRV_TYPE_A        0x0010
#define SDIF_CTRL_DRV_TYPE_C        0x0020
#define SDIF_CTRL_DRV_TYPE_D        0x0030
#define SDIF_CTRL_EXEC_TUNING       0x0040
#define SDIF_CTRL_TUNED_CLK         0x0080
#define SDIF_CTRL_PRESET_VAL_ENABLE   0x8000

#define SDIF_GET_CMD(c) ((c>>8) & 0x3f)

#define SDIF_INT_RESPONSE       0x00000001
#define SDIF_INT_DATA_END       0x00000002
#define SDIF_INT_BLK_GAP        0x00000004
#define SDIF_INT_DMA_END        0x00000008
#define SDIF_INT_SPACE_AVAIL    0x00000010
#define SDIF_INT_DATA_AVAIL 0x00000020
#define SDIF_INT_CARD_INSERT    0x00000040
#define SDIF_INT_CARD_REMOVE    0x00000080
#define SDIF_INT_CARD_INT       0x00000100
#define SDIF_INT_RETUNE     0x00001000
#define SDIF_INT_ERROR          0x00008000
#define SDIF_INT_TIMEOUT        0x00010000
#define SDIF_INT_CRC            0x00020000
#define SDIF_INT_END_BIT        0x00040000
#define SDIF_INT_INDEX          0x00080000
#define SDIF_INT_DATA_TIMEOUT   0x00100000
#define SDIF_INT_DATA_CRC       0x00200000
#define SDIF_INT_DATA_END_BIT   0x00400000
#define SDIF_INT_BUS_POWER      0x00800000
#define SDIF_INT_ACMD12ERR      0x01000000
#define SDIF_INT_ADMA_ERROR 0x02000000

#define SDIF_INT_CMD_MASK   (SDIF_INT_RESPONSE | SDIF_INT_TIMEOUT | \
        SDIF_INT_CRC | SDIF_INT_END_BIT | SDIF_INT_INDEX)
#define SDIF_INT_DATA_MASK  (SDIF_INT_DATA_END | SDIF_INT_DMA_END | \
        SDIF_INT_DATA_AVAIL | SDIF_INT_SPACE_AVAIL | \
        SDIF_INT_DATA_TIMEOUT | SDIF_INT_DATA_CRC | \
        SDIF_INT_DATA_END_BIT | SDIF_INT_ADMA_ERROR | \
        SDIF_INT_BLK_GAP)

#define SDIF_HOST_VER4_ENABLE          BIT(12)
#define SDIF_CAPABILITIES1             0x40
#define SDIF_CAPABILITIES2             0x44
#define SDIF_ADMA_SA_LOW               0x58
#define SDIF_ADMA_SA_HIGH              0x5C
#define SDIF_HOST_CNTRL_VERS            0xFE
#define SDIF_UHS_2_TIMER_CNTRL          0xC2

#define P_VENDOR_SPECIFIC_AREA          0xE8
#define P_VENDOR2_SPECIFIC_AREA         0xEA
#define VENDOR_SD_CTRL                  0x2C


#define DEFAULT_DIV_SD_INIT_CLOCK 0x2

/*execute tuning register and bit flag*/
#define SDIF_PHY_TX_RX_DLY  0x40
#define SDIF_PHY_CONFIG     0x4c

/*SDIO 0 register and bit flag*/
#define REG_SDIO0_PAD_MASK      (0xFFFFFFF3)
#define REG_SDIO0_PAD_SHIFT     (2)

#define REG_SDIO0_CD_PAD_REG        (PINMUX_BASE + 0x900)
#define REG_SDIO0_CD_PAD_VALUE      (1)

#define REG_SDIO0_PWR_EN_PAD_REG    (PINMUX_BASE + 0x904)
#define REG_SDIO0_PWR_EN_PAD_VALUE  (2)

#define REG_SDIO0_CLK_PAD_REG       (PINMUX_BASE + 0xA00)
#define REG_SDIO0_CLK_PAD_VALUE     (2)

#define REG_SDIO0_CMD_PAD_REG       (PINMUX_BASE + 0xA04)
#define REG_SDIO0_CMD_PAD_VALUE     (1)

#define REG_SDIO0_DAT0_PAD_REG      (PINMUX_BASE + 0xA08)
#define REG_SDIO0_DAT0_PAD_VALUE    (1)

#define REG_SDIO0_DAT1_PAD_REG      (PINMUX_BASE + 0xA0C)
#define REG_SDIO0_DAT1_PAD_VALUE    (1)

#define REG_SDIO0_DAT2_PAD_REG      (PINMUX_BASE + 0xA10)
#define REG_SDIO0_DAT2_PAD_VALUE    (1)

#define REG_SDIO0_DAT3_PAD_REG      (PINMUX_BASE + 0xA14)
#define REG_SDIO0_DAT3_PAD_VALUE    (1)

#define REG_SDIO0_CD_PIO_REG        (PINMUX_BASE + 0x34)
#define REG_SDIO0_CD_PIO_VALUE      (0x3)

#define REG_SDIO0_PWR_EN_PIO_REG    (PINMUX_BASE + 0x38)
#define REG_SDIO0_PWR_EN_PIO_VALUE  (0x0)

#define REG_SDIO0_CLK_PIO_REG       (PINMUX_BASE + 0x1C)
#define REG_SDIO0_CLK_PIO_VALUE     (0x0)

#define REG_SDIO0_CMD_PIO_REG       (PINMUX_BASE + 0x20)
#define REG_SDIO0_CMD_PIO_VALUE     (0x0)

#define REG_SDIO0_DAT0_PIO_REG      (PINMUX_BASE + 0x24)
#define REG_SDIO0_DAT0_PIO_VALUE    (0x0)

#define REG_SDIO0_DAT1_PIO_REG      (PINMUX_BASE + 0x28)
#define REG_SDIO0_DAT1_PIO_VALUE    (0x0)

#define REG_SDIO0_DAT2_PIO_REG      (PINMUX_BASE + 0x2C)
#define REG_SDIO0_DAT2_PIO_VALUE    (0x0)

#define REG_SDIO0_DAT3_PIO_REG      (PINMUX_BASE + 0x30)
#define REG_SDIO0_DAT3_PIO_VALUE    (0x0)

/*SDIO 1 register and bit flag*/
#define RTCIO_BASE                 (uintptr_t)DRV_IOREMAP((void *)0x5027000, 0x1000)
#define REG_SDIO1_PAD_MASK      (0xFFFFFFF3)
#define REG_SDIO1_PAD_SHIFT     (2)

#define REG_SDIO1_CLK_PAD_REG       (RTCIO_BASE + 0x6C)
#define REG_SDIO1_CLK_PAD_VALUE     (2)

#define REG_SDIO1_CMD_PAD_REG       (RTCIO_BASE + 0x68)
#define REG_SDIO1_CMD_PAD_VALUE     (1)

#define REG_SDIO1_DAT0_PAD_REG      (RTCIO_BASE + 0x64)
#define REG_SDIO1_DAT0_PAD_VALUE    (1)

#define REG_SDIO1_DAT1_PAD_REG      (RTCIO_BASE + 0x60)
#define REG_SDIO1_DAT1_PAD_VALUE    (1)

#define REG_SDIO1_DAT2_PAD_REG      (RTCIO_BASE + 0x5C)
#define REG_SDIO1_DAT2_PAD_VALUE    (1)

#define REG_SDIO1_DAT3_PAD_REG      (RTCIO_BASE + 0x58)
#define REG_SDIO1_DAT3_PAD_VALUE    (1)

#define REG_SDIO1_CLK_PIO_REG       (PINMUX_BASE + 0xE4)
#define REG_SDIO1_CLK_PIO_VALUE     (0x0)

#define REG_SDIO1_CMD_PIO_REG       (PINMUX_BASE + 0xE0)
#define REG_SDIO1_CMD_PIO_VALUE     (0x0)

#define REG_SDIO1_DAT0_PIO_REG      (PINMUX_BASE + 0xDC)
#define REG_SDIO1_DAT0_PIO_VALUE    (0x0)

#define REG_SDIO1_DAT1_PIO_REG      (PINMUX_BASE + 0xD8)
#define REG_SDIO1_DAT1_PIO_VALUE    (0x0)

#define REG_SDIO1_DAT2_PIO_REG      (PINMUX_BASE + 0xD4)
#define REG_SDIO1_DAT2_PIO_VALUE    (0x0)

#define REG_SDIO1_DAT3_PIO_REG      (PINMUX_BASE + 0xD0)
#define REG_SDIO1_DAT3_PIO_VALUE    (0x0)

#define RTC_CTRL_BASE       (uintptr_t)DRV_IOREMAP((void *)0x5025000, 0x1000)
#define RTCSYS_CLKMUX       (RTC_CTRL_BASE + 0x1C)
#define RTCSYS_CLKBYP       (RTC_CTRL_BASE + 0x30)
#define RTCSYS_MCU51_ICTRL1 (RTC_CTRL_BASE + 0x7C)

#define RTCSYS_CTRL_BASE    (uintptr_t)DRV_IOREMAP((void *)0x03000000, 0x1000)
#define RTCSYS_CTRL         (RTCSYS_CTRL_BASE + 0x248)

/*SDIO 2 register and bit flag*/
#define REG_SDIO2_PAD_MASK (0xFFFFFFF3)
#define REG_SDIO2_PAD_SHIFT (2)

#define REG_SDIO2_RSTN_PAD_REG (PINMUX_BASE + 0x914)
#define REG_SDIO2_RSTN_PAD_VALUE (1)

#define REG_SDIO2_CLK_PAD_REG (PINMUX_BASE + 0x91C)
#define REG_SDIO2_CLK_PAD_VALUE (2)

#define REG_SDIO2_CMD_PAD_REG (PINMUX_BASE + 0x928)
#define REG_SDIO2_CMD_PAD_VALUE (1)

#define REG_SDIO2_DAT0_PAD_REG (PINMUX_BASE + 0x920)
#define REG_SDIO2_DAT0_PAD_VALUE (1)

#define REG_SDIO2_DAT1_PAD_REG (PINMUX_BASE + 0x92C)
#define REG_SDIO2_DAT1_PAD_VALUE (1)

#define REG_SDIO2_DAT2_PAD_REG (PINMUX_BASE + 0x918)
#define REG_SDIO2_DAT2_PAD_VALUE (1)

#define REG_SDIO2_DAT3_PAD_REG (PINMUX_BASE + 0x924)
#define REG_SDIO2_DAT3_PAD_VALUE (1)

#define REG_SDIO2_RSTN_PIO_REG (PINMUX_BASE + 0x48)
#define REG_SDIO2_RSTN_PIO_VALUE (0x0)

#define REG_SDIO2_CLK_PIO_REG (PINMUX_BASE + 0x50)
#define REG_SDIO2_CLK_PIO_VALUE (0x0)

#define REG_SDIO2_CMD_PIO_REG (PINMUX_BASE + 0x5C)
#define REG_SDIO2_CMD_PIO_VALUE (0x0)

#define REG_SDIO2_DAT0_PIO_REG (PINMUX_BASE + 0x54)
#define REG_SDIO2_DAT0_PIO_VALUE (0x0)

#define REG_SDIO2_DAT1_PIO_REG (PINMUX_BASE + 0x60)
#define REG_SDIO2_DAT1_PIO_VALUE (0x0)

#define REG_SDIO2_DAT2_PIO_REG (PINMUX_BASE + 0x4C)
#define REG_SDIO2_DAT2_PIO_VALUE (0x0)

#define REG_SDIO2_DAT3_PIO_REG (PINMUX_BASE + 0x58)
#define REG_SDIO2_DAT3_PIO_VALUE (0x0)

#define CLK_DIV_BASE           (uintptr_t)DRV_IOREMAP((void *)0x3002000, 0x1000)
#define MMC_SDIO0_PLL_REGISTER (CLK_DIV_BASE + 0x70)
#define MMC_SDIO1_PLL_REGISTER (CLK_DIV_BASE + 0x7C)
#define MMC_SDIO2_PLL_REGISTER (CLK_DIV_BASE + 0x64)
#define MMC_MAX_CLOCK_DIV_VALUE (0x40009)
#define CLOCK_BYPASS_SELECT_REGISTER (0x3002030)

#endif /* __HAL_DW_SDIO_H_ */
