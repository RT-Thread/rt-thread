/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-08-16     zhujiale     first version
 */
#ifndef __RT_SDHCI_HW_H
#define __RT_SDHCI_HW_H

#include "sdhci_host.h"
#include "sdhci_misc.h"
#include "sdhci-platform.h"
#include <drivers/mmcsd_cmd.h>
#include <drivers/dev_mmcsd_core.h>
#include <drivers/mmcsd_host.h>
#include <rtdevice.h>

#define lower_32_bits(n) ((rt_uint32_t)((n) & 0xffffffff))
#define upper_32_bits(n) ((rt_uint32_t)(((n) >> 16) >> 16))

#define MAX_TUNING_LOOP 40
/*
 * Controller registers
 */
#define RT_SDHCI_DMA_ADDRESS   0x00
#define RT_SDHCI_ARGUMENT2     RT_SDHCI_DMA_ADDRESS
#define RT_SDHCI_32BIT_BLK_CNT RT_SDHCI_DMA_ADDRESS

#define RT_SDHCI_BLOCK_SIZE             0x04
#define RT_SDHCI_MAKE_BLKSZ(dma, blksz) (((dma & 0x7) << 12) | (blksz & 0xFFF))

#define RT_SDHCI_BLOCK_COUNT 0x06

#define RT_SDHCI_ARGUMENT 0x08

#define RT_SDHCI_TRANSFER_MODE   0x0C
#define RT_SDHCI_TRNS_DMA        0x01
#define RT_SDHCI_TRNS_BLK_CNT_EN 0x02
#define RT_SDHCI_TRNS_AUTO_CMD12 0x04
#define RT_SDHCI_TRNS_AUTO_CMD23 0x08
#define RT_SDHCI_TRNS_AUTO_SEL   0x0C
#define RT_SDHCI_TRNS_READ       0x10
#define RT_SDHCI_TRNS_MULTI      0x20

#define RT_SDHCI_COMMAND       0x0E
#define RT_SDHCI_CMD_RESP_MASK 0x03
#define RT_SDHCI_CMD_CRC       0x08
#define RT_SDHCI_CMD_INDEX     0x10
#define RT_SDHCI_CMD_DATA      0x20
#define RT_SDHCI_CMD_ABORTCMD  0xC0

#define RT_SDHCI_CMD_RESP_NONE       0x00
#define RT_SDHCI_CMD_RESP_LONG       0x01
#define RT_SDHCI_CMD_RESP_SHORT      0x02
#define RT_SDHCI_CMD_RESP_SHORT_BUSY 0x03

#define RT_SDHCI_MAKE_CMD(c, f) (((c & 0xff) << 8) | (f & 0xff))
#define RT_SDHCI_GET_CMD(c)     ((c >> 8) & 0x3f)

#define RT_SDHCI_RESPONSE 0x10

#define RT_SDHCI_BUFFER 0x20

#define RT_SDHCI_PRESENT_STATE   0x24
#define RT_SDHCI_CMD_INHIBIT     0x00000001
#define RT_SDHCI_DATA_INHIBIT    0x00000002
#define RT_SDHCI_DOING_WRITE     0x00000100
#define RT_SDHCI_DOING_READ      0x00000200
#define RT_SDHCI_SPACE_AVAILABLE 0x00000400
#define RT_SDHCI_DATA_AVAILABLE  0x00000800
#define RT_SDHCI_CARD_PRESENT    0x00010000
#define RT_SDHCI_CARD_PRES_SHIFT 16
#define RT_SDHCI_CD_STABLE       0x00020000
#define RT_SDHCI_CD_LVL          0x00040000
#define RT_SDHCI_CD_LVL_SHIFT    18
#define RT_SDHCI_WRITE_PROTECT   0x00080000
#define RT_SDHCI_DATA_LVL_MASK   0x00F00000
#define RT_SDHCI_DATA_LVL_SHIFT  20
#define RT_SDHCI_DATA_0_LVL_MASK 0x00100000
#define RT_SDHCI_CMD_LVL         0x01000000

#define RT_SDHCI_HOST_CONTROL    0x28
#define RT_SDHCI_CTRL_LED        0x01
#define RT_SDHCI_CTRL_4BITBUS    0x02
#define RT_SDHCI_CTRL_HISPD      0x04
#define RT_SDHCI_CTRL_DMA_MASK   0x18
#define RT_SDHCI_CTRL_SDMA       0x00
#define RT_SDHCI_CTRL_ADMA1      0x08
#define RT_SDHCI_CTRL_ADMA32     0x10
#define RT_SDHCI_CTRL_ADMA64     0x18
#define RT_SDHCI_CTRL_ADMA3      0x18
#define RT_SDHCI_CTRL_8BITBUS    0x20
#define RT_SDHCI_CTRL_CDTEST_INS 0x40
#define RT_SDHCI_CTRL_CDTEST_EN  0x80

#define RT_SDHCI_POWER_CONTROL 0x29
#define RT_SDHCI_POWER_ON      0x01
#define RT_SDHCI_POWER_180     0x0A
#define RT_SDHCI_POWER_300     0x0C
#define RT_SDHCI_POWER_330     0x0E
/*
 * VDD2 - UHS2 or PCIe/NVMe
 * VDD2 power on/off and voltage select
 */
#define RT_SDHCI_VDD2_POWER_ON  0x10
#define RT_SDHCI_VDD2_POWER_120 0x80
#define RT_SDHCI_VDD2_POWER_180 0xA0

#define RT_SDHCI_BLOCK_GAP_CONTROL 0x2A

#define RT_SDHCI_WAKE_UP_CONTROL 0x2B
#define RT_SDHCI_WAKE_ON_INT     0x01
#define RT_SDHCI_WAKE_ON_INSERT  0x02
#define RT_SDHCI_WAKE_ON_REMOVE  0x04

#define RT_SDHCI_CLOCK_CONTROL    0x2C
#define RT_SDHCI_DIVIDER_SHIFT    8
#define RT_SDHCI_DIVIDER_HI_SHIFT 6
#define RT_SDHCI_DIV_MASK         0xFF
#define RT_SDHCI_DIV_MASK_LEN     8
#define RT_SDHCI_DIV_HI_MASK      0x300
#define RT_SDHCI_PROG_CLOCK_MODE  0x0020
#define RT_SDHCI_CLOCK_CARD_EN    0x0004
#define RT_SDHCI_CLOCK_PLL_EN     0x0008
#define RT_SDHCI_CLOCK_INT_STABLE 0x0002
#define RT_SDHCI_CLOCK_INT_EN     0x0001

#define RT_SDHCI_TIMEOUT_CONTROL 0x2E

#define RT_SDHCI_SOFTWARE_RESET 0x2F
#define RT_SDHCI_RESET_ALL      0x01
#define RT_SDHCI_RESET_CMD      0x02
#define RT_SDHCI_RESET_DATA     0x04

#define RT_SDHCI_INT_STATUS       0x30
#define RT_SDHCI_INT_ENABLE       0x34
#define RT_SDHCI_SIGNAL_ENABLE    0x38
#define RT_SDHCI_INT_RESPONSE     0x00000001
#define RT_SDHCI_INT_DATA_END     0x00000002
#define RT_SDHCI_INT_BLK_GAP      0x00000004
#define RT_SDHCI_INT_DMA_END      0x00000008
#define RT_SDHCI_INT_SPACE_AVAIL  0x00000010
#define RT_SDHCI_INT_DATA_AVAIL   0x00000020
#define RT_SDHCI_INT_CARD_INSERT  0x00000040
#define RT_SDHCI_INT_CARD_REMOVE  0x00000080
#define RT_SDHCI_INT_CARD_INT     0x00000100
#define RT_SDHCI_INT_RETUNE       0x00001000
#define RT_SDHCI_INT_CQE          0x00004000
#define RT_SDHCI_INT_ERROR        0x00008000
#define RT_SDHCI_INT_TIMEOUT      0x00010000
#define RT_SDHCI_INT_CRC          0x00020000
#define RT_SDHCI_INT_END_BIT      0x00040000
#define RT_SDHCI_INT_INDEX        0x00080000
#define RT_SDHCI_INT_DATA_TIMEOUT 0x00100000
#define RT_SDHCI_INT_DATA_CRC     0x00200000
#define RT_SDHCI_INT_DATA_END_BIT 0x00400000
#define RT_SDHCI_INT_BUS_POWER    0x00800000
#define RT_SDHCI_INT_AUTO_CMD_ERR 0x01000000
#define RT_SDHCI_INT_ADMA_ERROR   0x02000000

#define RT_SDHCI_INT_NORMAL_MASK 0x00007FFF
#define RT_SDHCI_INT_ERROR_MASK  0xFFFF8000

#define RT_SDHCI_INT_CMD_MASK  (RT_SDHCI_INT_RESPONSE | RT_SDHCI_INT_TIMEOUT | RT_SDHCI_INT_CRC | RT_SDHCI_INT_END_BIT | RT_SDHCI_INT_INDEX | RT_SDHCI_INT_AUTO_CMD_ERR)
#define RT_SDHCI_INT_DATA_MASK (RT_SDHCI_INT_DATA_END | RT_SDHCI_INT_DMA_END | RT_SDHCI_INT_DATA_AVAIL | RT_SDHCI_INT_SPACE_AVAIL | RT_SDHCI_INT_DATA_TIMEOUT | RT_SDHCI_INT_DATA_CRC | RT_SDHCI_INT_DATA_END_BIT | RT_SDHCI_INT_ADMA_ERROR | RT_SDHCI_INT_BLK_GAP)
#define RT_SDHCI_INT_ALL_MASK  ((unsigned int)-1)

#define RT_SDHCI_CQE_INT_ERR_MASK ( \
    RT_SDHCI_INT_ADMA_ERROR | RT_SDHCI_INT_BUS_POWER | RT_SDHCI_INT_DATA_END_BIT | RT_SDHCI_INT_DATA_CRC | RT_SDHCI_INT_DATA_TIMEOUT | RT_SDHCI_INT_INDEX | RT_SDHCI_INT_END_BIT | RT_SDHCI_INT_CRC | RT_SDHCI_INT_TIMEOUT)

#define RT_SDHCI_CQE_INT_MASK (RT_SDHCI_CQE_INT_ERR_MASK | RT_SDHCI_INT_CQE)

#define RT_SDHCI_AUTO_CMD_STATUS  0x3C
#define RT_SDHCI_AUTO_CMD_TIMEOUT 0x00000002
#define RT_SDHCI_AUTO_CMD_CRC     0x00000004
#define RT_SDHCI_AUTO_CMD_END_BIT 0x00000008
#define RT_SDHCI_AUTO_CMD_INDEX   0x00000010

#define RT_SDHCI_HOST_CONTROL2          0x3E
#define RT_SDHCI_CTRL_UHS_MASK          0x0007
#define RT_SDHCI_CTRL_UHS_SDR12         0x0000
#define RT_SDHCI_CTRL_UHS_SDR25         0x0001
#define RT_SDHCI_CTRL_UHS_SDR50         0x0002
#define RT_SDHCI_CTRL_UHS_SDR104        0x0003
#define RT_SDHCI_CTRL_UHS_DDR50         0x0004
#define RT_SDHCI_CTRL_HS400             0x0005 /* Non-standard */
#define RT_SDHCI_CTRL_VDD_180           0x0008
#define RT_SDHCI_CTRL_DRV_TYPE_MASK     0x0030
#define RT_SDHCI_CTRL_DRV_TYPE_B        0x0000
#define RT_SDHCI_CTRL_DRV_TYPE_A        0x0010
#define RT_SDHCI_CTRL_DRV_TYPE_C        0x0020
#define RT_SDHCI_CTRL_DRV_TYPE_D        0x0030
#define RT_SDHCI_CTRL_EXEC_TUNING       0x0040
#define RT_SDHCI_CTRL_TUNED_CLK         0x0080
#define RT_SDHCI_CMD23_ENABLE           0x0800
#define RT_SDHCI_CTRL_V4_MODE           0x1000
#define RT_SDHCI_CTRL_64BIT_ADDR        0x2000
#define RT_SDHCI_CTRL_PRESET_VAL_ENABLE 0x8000

#define RT_SDHCI_CAPABILITIES       0x40
#define RT_SDHCI_TIMEOUT_CLK_MASK   RT_GENMASK(5, 0)
#define RT_SDHCI_TIMEOUT_CLK_SHIFT  0
#define RT_SDHCI_TIMEOUT_CLK_UNIT   0x00000080
#define RT_SDHCI_CLOCK_BASE_MASK    RT_GENMASK(13, 8)
#define RT_SDHCI_CLOCK_BASE_SHIFT   8
#define RT_SDHCI_CLOCK_V3_BASE_MASK RT_GENMASK(15, 8)
#define RT_SDHCI_MAX_BLOCK_MASK     0x00030000
#define RT_SDHCI_MAX_BLOCK_SHIFT    16
#define RT_SDHCI_CAN_DO_8BIT        0x00040000
#define RT_SDHCI_CAN_DO_ADMA2       0x00080000
#define RT_SDHCI_CAN_DO_ADMA1       0x00100000
#define RT_SDHCI_CAN_DO_HISPD       0x00200000
#define RT_SDHCI_CAN_DO_SDMA        0x00400000
#define RT_SDHCI_CAN_DO_SUSPEND     0x00800000
#define RT_SDHCI_CAN_VDD_330        0x01000000
#define RT_SDHCI_CAN_VDD_300        0x02000000
#define RT_SDHCI_CAN_VDD_180        0x04000000
#define RT_SDHCI_CAN_64BIT_V4       0x08000000
#define RT_SDHCI_CAN_64BIT          0x10000000

#define RT_SDHCI_CAPABILITIES_1            0x44
#define RT_SDHCI_SUPPORT_SDR50             0x00000001
#define RT_SDHCI_SUPPORT_SDR104            0x00000002
#define RT_SDHCI_SUPPORT_DDR50             0x00000004
#define RT_SDHCI_DRIVER_TYPE_A             0x00000010
#define RT_SDHCI_DRIVER_TYPE_C             0x00000020
#define RT_SDHCI_DRIVER_TYPE_D             0x00000040
#define RT_SDHCI_RETUNING_TIMER_COUNT_MASK RT_GENMASK(11, 8)
#define RT_SDHCI_USE_SDR50_TUNING          0x00002000
#define RT_SDHCI_RETUNING_MODE_MASK        RT_GENMASK(15, 14)
#define RT_SDHCI_CLOCK_MUL_MASK            RT_GENMASK(23, 16)
#define RT_SDHCI_CAN_DO_ADMA3              0x08000000
#define RT_SDHCI_SUPPORT_HS400             0x80000000 /* Non-standard */

#define RT_SDHCI_MAX_CURRENT            0x48
#define RT_SDHCI_MAX_CURRENT_LIMIT      RT_GENMASK(7, 0)
#define RT_SDHCI_MAX_CURRENT_330_MASK   RT_GENMASK(7, 0)
#define RT_SDHCI_MAX_CURRENT_300_MASK   RT_GENMASK(15, 8)
#define RT_SDHCI_MAX_CURRENT_180_MASK   RT_GENMASK(23, 16)
#define RT_SDHCI_MAX_CURRENT_MULTIPLIER 4

/* 4C-4F reserved for more max current */

#define RT_SDHCI_SET_ACMD12_ERROR 0x50
#define RT_SDHCI_SET_INT_ERROR    0x52

#define RT_SDHCI_ADMA_ERROR 0x54

/* 55-57 reserved */

#define RT_SDHCI_ADMA_ADDRESS    0x58
#define RT_SDHCI_ADMA_ADDRESS_HI 0x5C

/* 60-FB reserved */

#define RT_SDHCI_PRESET_FOR_HIGH_SPEED 0x64
#define RT_SDHCI_PRESET_FOR_SDR12      0x66
#define RT_SDHCI_PRESET_FOR_SDR25      0x68
#define RT_SDHCI_PRESET_FOR_SDR50      0x6A
#define RT_SDHCI_PRESET_FOR_SDR104     0x6C
#define RT_SDHCI_PRESET_FOR_DDR50      0x6E
#define RT_SDHCI_PRESET_FOR_HS400      0x74 /* Non-standard */
#define RT_SDHCI_PRESET_DRV_MASK       RT_GENMASK(15, 14)
#define BIT(nr)                     ((1) << (nr))

#define RT_SDHCI_PRESET_CLKGEN_SEL      BIT(10)
#define RT_SDHCI_PRESET_SDCLK_FREQ_MASK RT_GENMASK(9, 0)

#define RT_SDHCI_SLOT_INT_STATUS 0xFC

#define RT_SDHCI_HOST_VERSION     0xFE
#define RT_SDHCI_VENDOR_VER_MASK  0xFF00
#define RT_SDHCI_VENDOR_VER_SHIFT 8
#define RT_SDHCI_SPEC_VER_MASK    0x00FF
#define RT_SDHCI_SPEC_VER_SHIFT   0
#define RT_SDHCI_SPEC_100         0
#define RT_SDHCI_SPEC_200         1
#define RT_SDHCI_SPEC_300         2
#define RT_SDHCI_SPEC_400         3
#define RT_SDHCI_SPEC_410         4
#define RT_SDHCI_SPEC_420         5

/*
 * End of controller registers.
 */

#define RT_SDHCI_MAX_DIV_SPEC_200 256
#define RT_SDHCI_MAX_DIV_SPEC_300 2046

/*
 * Host SDMA buffer boundary. Valid values from 4K to 512K in powers of 2.
 */
#define RT_SDHCI_DEFAULT_BOUNDARY_SIZE (512 * 1024)
#define ilog2(v)                    __rt_ffs(v)
#define RT_SDHCI_DEFAULT_BOUNDARY_ARG  (ilog2(RT_SDHCI_DEFAULT_BOUNDARY_SIZE) - 12)
#define RT_SDHCI_MAX_SEGS 128

/* Allow for a command request and a data request at the same time */
#define RT_SDHCI_MAX_MRQS 2
#define MMC_CMD_TRANSFER_TIME (10 * 1000000L) /* max 10 ms */


enum rt_sdhci_cookie
{
    COOKIE_UNMAPPED,
    COOKIE_PRE_MAPPED, /* mapped by sdhci_pre_req() */
    COOKIE_MAPPED,     /* mapped by sdhci_prepare_data() */
};

struct rt_sdhci_host
{
    const char *hw_name; /* Hardware bus name */

    unsigned int quirks; /* Deviations from spec. */

    void *data_buf;
/* Controller doesn't honor resets unless we touch the clock register */
#define RT_SDHCI_QUIRK_CLOCK_BEFORE_RESET (1 << 0)
/* Controller has bad caps bits, but really supports DMA */
#define RT_SDHCI_QUIRK_FORCE_DMA (1 << 1)
/* Controller doesn't like to be reset when there is no card inserted. */
#define RT_SDHCI_QUIRK_NO_CARD_NO_RESET (1 << 2)
/* Controller doesn't like clearing the power reg before a change */
#define RT_SDHCI_QUIRK_SINGLE_POWER_WRITE (1 << 3)
/* Controller has an unusable DMA engine */
#define RT_SDHCI_QUIRK_BROKEN_DMA (1 << 5)
/* Controller has an unusable ADMA engine */
#define RT_SDHCI_QUIRK_BROKEN_ADMA (1 << 6)
/* Controller can only DMA from 32-bit aligned addresses */
#define RT_SDHCI_QUIRK_32BIT_DMA_ADDR (1 << 7)
/* Controller can only DMA chunk sizes that are a multiple of 32 bits */
#define RT_SDHCI_QUIRK_32BIT_DMA_SIZE (1 << 8)
/* Controller can only ADMA chunks that are a multiple of 32 bits */
#define RT_SDHCI_QUIRK_32BIT_ADMA_SIZE (1 << 9)
/* Controller needs to be reset after each request to stay stable */
#define RT_SDHCI_QUIRK_RESET_AFTER_REQUEST (1 << 10)
/* Controller needs voltage and power writes to happen separately */
#define RT_SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER (1 << 11)
/* Controller provides an incorrect timeout value for transfers */
#define RT_SDHCI_QUIRK_BROKEN_TIMEOUT_VAL (1 << 12)
/* Controller has an issue with buffer bits for small transfers */
#define RT_SDHCI_QUIRK_BROKEN_SMALL_PIO (1 << 13)
/* Controller does not provide transfer-complete interrupt when not busy */
#define RT_SDHCI_QUIRK_NO_BUSY_IRQ (1 << 14)
/* Controller has unreliable card detection */
#define RT_SDHCI_QUIRK_BROKEN_CARD_DETECTION (1 << 15)
/* Controller reports inverted write-protect state */
#define RT_SDHCI_QUIRK_INVERTED_WRITE_PROTECT (1 << 16)
/* Controller has unusable command queue engine */
#define RT_SDHCI_QUIRK_BROKEN_CQE (1 << 17)
/* Controller does not like fast PIO transfers */
#define RT_SDHCI_QUIRK_PIO_NEEDS_DELAY (1 << 18)
/* Controller does not have a LED */
#define RT_SDHCI_QUIRK_NO_LED (1 << 19)
/* Controller has to be forced to use block size of 2048 bytes */
#define RT_SDHCI_QUIRK_FORCE_BLK_SZ_2048 (1 << 20)
/* Controller cannot do multi-block transfers */
#define RT_SDHCI_QUIRK_NO_MULTIBLOCK (1 << 21)
/* Controller can only handle 1-bit data transfers */
#define RT_SDHCI_QUIRK_FORCE_1_BIT_DATA (1 << 22)
/* Controller needs 10ms delay between applying power and clock */
#define RT_SDHCI_QUIRK_DELAY_AFTER_POWER (1 << 23)
/* Controller uses SDCLK instead of TMCLK for data timeouts */
#define RT_SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK (1 << 24)
/* Controller reports wrong base clock capability */
#define RT_SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN (1 << 25)
/* Controller cannot support End Attribute in NOP ADMA descriptor */
#define RT_SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC (1 << 26)
/* Controller uses Auto CMD12 command to stop the transfer */
#define RT_SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12 (1 << 28)
/* Controller doesn't have HISPD bit field in HI-SPEED SD card */
#define RT_SDHCI_QUIRK_NO_HISPD_BIT (1 << 29)
/* Controller treats ADMA descriptors with length 0000h incorrectly */
#define RT_SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC (1 << 30)
/* The read-only detection via RT_SDHCI_PRESENT_STATE register is unstable */
#define RT_SDHCI_QUIRK_UNSTABLE_RO_DETECT (1 << 31)

    unsigned int quirks2; /* More deviations from spec. */

#define RT_SDHCI_QUIRK2_HOST_OFF_CARD_ON (1 << 0)
#define RT_SDHCI_QUIRK2_HOST_NO_CMD23    (1 << 1)
/* The system physically doesn't support 1.8v, even if the host does */
#define RT_SDHCI_QUIRK2_NO_1_8_V             (1 << 2)
#define RT_SDHCI_QUIRK2_PRESET_VALUE_BROKEN  (1 << 3)
#define RT_SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON (1 << 4)
/* Controller has a non-standard host control register */
#define RT_SDHCI_QUIRK2_BROKEN_HOST_CONTROL (1 << 5)
/* Controller does not support HS200 */
#define RT_SDHCI_QUIRK2_BROKEN_HS200 (1 << 6)
/* Controller does not support DDR50 */
#define RT_SDHCI_QUIRK2_BROKEN_DDR50 (1 << 7)
/* Stop command (CMD12) can set Transfer Complete when not using MMC_RSP_BUSY */
#define RT_SDHCI_QUIRK2_STOP_WITH_TC (1 << 8)
/* Controller does not support 64-bit DMA */
#define RT_SDHCI_QUIRK2_BROKEN_64_BIT_DMA (1 << 9)
/* need clear transfer mode register before send cmd */
#define RT_SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD (1 << 10)
/* Capability register bit-63 indicates HS400 support */
#define RT_SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400 (1 << 11)
/* forced tuned clock */
#define RT_SDHCI_QUIRK2_TUNING_WORK_AROUND (1 << 12)
/* disable the block count for single block transactions */
#define RT_SDHCI_QUIRK2_SUPPORT_SINGLE (1 << 13)
/* Controller broken with using ACMD23 */
#define RT_SDHCI_QUIRK2_ACMD23_BROKEN (1 << 14)
/* Broken Clock divider zero in controller */
#define RT_SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN (1 << 15)
/* Controller has CRC in 136 bit Command Response */
#define RT_SDHCI_QUIRK2_RSP_136_HAS_CRC (1 << 16)

#define RT_SDHCI_QUIRK2_DISABLE_HW_TIMEOUT (1 << 17)

#define RT_SDHCI_QUIRK2_USE_32BIT_BLK_CNT (1 << 18)
/* Issue CMD and DATA reset together */
#define RT_SDHCI_QUIRK2_ISSUE_CMD_DAT_RESET_TOGETHER (1 << 19)

    int          irq;           /* Device IRQ */
    void        *ioaddr;        /* Mapped address */
    char        *bounce_buffer; /* For packing SDMA reads/writes */
    rt_uint64_t  bounce_addr;
    unsigned int bounce_buffer_size;

    const struct rt_sdhci_ops *ops; /* Low level hw interface */

    /* Internal data */
    struct rt_mmc_host    *mmc;          /* MMC structure */
    struct mmc_host_ops mmc_host_ops; /* MMC host ops */
    rt_uint64_t         dma_mask;     /* custom DMA mask */

    rt_spinlock_t lock;
    int           flags;                             /* Host attributes */
#define RT_SDHCI_USE_SDMA           (1 << 0)            /* Host is SDMA capable */
#define RT_SDHCI_USE_ADMA           (1 << 1)            /* Host is ADMA capable */
#define RT_SDHCI_REQ_USE_DMA        (1 << 2)            /* Use DMA for this req. */
#define RT_SDHCI_DEVICE_DEAD        (1 << 3)            /* Device unresponsive */
#define RT_SDHCI_SDR50_NEEDS_TUNING (1 << 4)            /* SDR50 needs tuning */
#define RT_SDHCI_AUTO_CMD12         (1 << 6)            /* Auto CMD12 support */
#define RT_SDHCI_AUTO_CMD23         (1 << 7)            /* Auto CMD23 support */
#define RT_SDHCI_PV_ENABLED         (1 << 8)            /* Preset value enabled */
#define RT_SDHCI_USE_64_BIT_DMA     (1 << 12)           /* Use 64-bit DMA */
#define RT_SDHCI_HS400_TUNING       (1 << 13)           /* Tuning for HS400 */
#define RT_SDHCI_SIGNALING_330      (1 << 14)           /* Host is capable of 3.3V signaling */
#define RT_SDHCI_SIGNALING_180      (1 << 15)           /* Host is capable of 1.8V signaling */
#define RT_SDHCI_SIGNALING_120      (1 << 16)           /* Host is capable of 1.2V signaling */

    unsigned int version;                            /* RT_SDHCI spec. version */

    unsigned int max_clk;                            /* Max possible freq (MHz) */
    unsigned int timeout_clk;                        /* Timeout freq (KHz) */
    rt_uint8_t   max_timeout_count;                  /* Vendor specific max timeout count */
    unsigned int clk_mul;                            /* Clock Muliplier value */

    unsigned int clock;                              /* Current clock (MHz) */
    rt_uint8_t   pwr;                                /* Current voltage */
    rt_uint8_t   drv_type;                           /* Current UHS-I driver type */
    rt_bool_t    reinit_uhs;                         /* Force UHS-related re-initialization */

    rt_bool_t runtime_suspended;                     /* Host is runtime suspended */
    rt_bool_t bus_on;                                /* Bus power prevents runtime suspend */
    rt_bool_t preset_enabled;                        /* Preset is enabled */
    rt_bool_t pending_reset;                         /* Cmd/data reset is pending */
    rt_bool_t irq_wake_enabled;                      /* IRQ wakeup is enabled */
    rt_bool_t v4_mode;                               /* Host Version 4 Enable */
    rt_bool_t always_defer_done;                     /* Always defer to complete requests */

    struct rt_mmcsd_req  *mrqs_done[RT_SDHCI_MAX_MRQS]; /* Requests done */
    struct rt_mmcsd_cmd  *cmd;                       /* Current command */
    struct rt_mmcsd_cmd  *data_cmd;                  /* Current data command */
    struct rt_mmcsd_cmd  *deferred_cmd;              /* Deferred command */
    struct rt_mmcsd_data *data;                      /* Current data request */
    unsigned int          data_early : 1;            /* Data finished before cmd */

    unsigned int blocks;                /* remaining PIO blocks */
    size_t align_buffer_sz;             /* Bounce buffer size */
    rt_uint64_t align_addr;             /* Mapped bounce buffer */

    struct rt_workqueue *complete_wq;   /* Request completion wq */
    struct rt_work       complete_work; /* Request completion work */

    struct rt_workqueue *irq_wq;
    struct rt_work       irq_work;

    struct rt_timer timer;                    /* Timer for timeouts */
    struct rt_timer data_timer;               /* Timer for data timeouts */

    rt_uint32_t caps;                         /* CAPABILITY_0 */
    rt_uint32_t caps1;                        /* CAPABILITY_1 */
    rt_bool_t   read_caps;                    /* Capability flags have been read */

    rt_bool_t    sdhci_core_to_disable_vqmmc; /* sdhci core can disable vqmmc */
    unsigned int ocr_avail_sdio;              /* OCR bit masks */
    unsigned int ocr_avail_sd;
    unsigned int ocr_avail_mmc;
    rt_uint32_t  ocr_mask; /* available voltages */

    unsigned timing;       /* Current timing */

    rt_uint32_t thread_isr;

    /* cached registers */
    rt_uint32_t ier;

    rt_bool_t   cqe_on;         /* CQE is operating */
    rt_uint32_t cqe_ier;        /* CQE interrupt mask */
    rt_uint32_t cqe_err_ier;    /* CQE error interrupt mask */

    rt_wqueue_t  buf_ready_int; /* Waitqueue for Buffer Read Ready interrupt */
    unsigned int tuning_done;   /* Condition flag set when CMD19 succeeds */

    unsigned int tuning_count;  /* Timer count for re-tuning */
    unsigned int tuning_mode;   /* Re-tuning mode supported by host */
    unsigned int tuning_err;    /* Error code for re-tuning */
#define RT_SDHCI_TUNING_MODE_1 0
#define RT_SDHCI_TUNING_MODE_2 1
#define RT_SDHCI_TUNING_MODE_3 2
    /* Delay (ms) between tuning commands */
    int tuning_delay;
    int tuning_loop_count;

    /* Host SDMA buffer boundary. */
    rt_uint32_t sdma_boundary;
    rt_uint64_t data_timeout;

    unsigned long private[];
};

static inline rt_uint8_t u8_read(const volatile void *addr)
{
    return *(const volatile rt_uint8_t *)addr;
}

static inline rt_uint16_t u16_read(const volatile void *addr)
{
    return *(const volatile rt_uint16_t *)addr;
}

static inline rt_uint32_t u32_read(const volatile void *addr)
{
    return *(const volatile rt_uint32_t *)addr;
}

static inline void u8_write(rt_uint8_t value, volatile void *addr)
{
    *(volatile rt_uint8_t *)addr = value;
}

static inline void u16_write(rt_uint16_t value, volatile void *addr)
{
    *(volatile rt_uint16_t *)addr = value;
}

static inline void u32_write(rt_uint32_t value, volatile void *addr)
{
    *(volatile rt_uint32_t *)addr = value;
}

#define readb(c)        u8_read(c)
#define readw(c)        u16_read(c)
#define readl(c)        u32_read(c)
#define readsb(p, d, l) ({ __raw_readsb(p,d,l); __iormb(); })
#define readsw(p, d, l) ({ __raw_readsw(p,d,l); __iormb(); })
#define readsl(p, d, l) ({ __raw_readsl(p,d,l); __iormb(); })

#define writeb(v, c)     u8_write(v, c)
#define writew(v, c)     u16_write(v, c)
#define writel(v, c)     u32_write(v, c)
#define writesb(p, d, l) ({ __iowmb(); __raw_writesb(p,d,l); })
#define writesw(p, d, l) ({ __iowmb(); __raw_writesw(p,d,l); })
#define writesl(p, d, l) ({ __iowmb(); __raw_writesl(p,d,l); })

static inline void rt_sdhci_writel(struct rt_sdhci_host *host, rt_uint32_t val, int reg)
{
    writel(val, host->ioaddr + reg);
}

static inline void rt_sdhci_writew(struct rt_sdhci_host *host, rt_uint16_t val, int reg)
{
    writew(val, host->ioaddr + reg);
}

static inline void rt_sdhci_writeb(struct rt_sdhci_host *host, rt_uint8_t val, int reg)
{
    writeb(val, host->ioaddr + reg);
}

static inline rt_uint32_t rt_sdhci_readl(struct rt_sdhci_host *host, int reg)
{
    return readl(host->ioaddr + reg);
}

static inline rt_uint16_t rt_sdhci_readw(struct rt_sdhci_host *host, int reg)
{
    return readw(host->ioaddr + reg);
}

static inline rt_uint8_t rt_sdhci_readb(struct rt_sdhci_host *host, int reg)
{
    return readb(host->ioaddr + reg);
}


struct rt_sdhci_ops
{
    void (*set_clock)(struct rt_sdhci_host *host, unsigned int clock);
    void (*set_power)(struct rt_sdhci_host *host, unsigned char mode,
                      unsigned short vdd);
    rt_uint32_t (*irq)(struct rt_sdhci_host *host, rt_uint32_t intmask);
    int (*set_dma_mask)(struct rt_sdhci_host *host);
    int (*enable_dma)(struct rt_sdhci_host *host);
    unsigned int (*get_max_clock)(struct rt_sdhci_host *host);
    unsigned int (*get_min_clock)(struct rt_sdhci_host *host);
    unsigned int (*get_timeout_clock)(struct rt_sdhci_host *host);
    unsigned int (*get_max_timeout_count)(struct rt_sdhci_host *host);
    void (*set_timeout)(struct rt_sdhci_host   *host,
                        struct rt_mmcsd_cmd *cmd);
    void (*set_bus_width)(struct rt_sdhci_host *host, int width);
    unsigned int (*get_ro)(struct rt_sdhci_host *host);
    void (*reset)(struct rt_sdhci_host *host, rt_uint8_t mask);
    int (*platform_execute_tuning)(struct rt_sdhci_host *host, rt_uint32_t opcode);
    void (*set_uhs_signaling)(struct rt_sdhci_host *host, unsigned int uhs);
    void (*hw_reset)(struct rt_sdhci_host *host);
    void (*card_event)(struct rt_sdhci_host *host);
    void (*voltage_switch)(struct rt_sdhci_host *host);
    void (*request_done)(struct rt_sdhci_host   *host,
                         struct rt_mmcsd_req *mrq);
};


struct rt_sdhci_host *rt_sdhci_alloc_host(struct rt_device *dev, size_t priv_size);
void               rt_sdhci_free_host(struct rt_sdhci_host *host);

static inline void *sdhci_priv(struct rt_sdhci_host *host)
{
    return host->private;
}

void        rt_sdhci_read_caps(struct rt_sdhci_host *host, const rt_uint16_t *ver,
                       const rt_uint32_t *caps, const rt_uint32_t *caps1);
int         rt_sdhci_setup_host(struct rt_sdhci_host *host);
void        rt_sdhci_cleanup_host(struct rt_sdhci_host *host);
int         rt_sdhci_set_and_add_host(struct rt_sdhci_host *host);
int         rt_sdhci_init_host(struct rt_sdhci_host *host);
void        rt_sdhci_uninit_host(struct rt_sdhci_host *host, int dead);

rt_uint16_t rt_sdhci_clk_set(struct rt_sdhci_host *host, unsigned int clock,
                           unsigned int *actual_clock);
void        rt_sdhci_set_clock(struct rt_sdhci_host *host, unsigned int clock);
void        rt_sdhci_clk_enable(struct rt_sdhci_host *host, rt_uint16_t clk);
void        rt_sdhci_set_power(struct rt_sdhci_host *host, unsigned char mode,unsigned short vdd);
void        rt_read_reg(struct rt_sdhci_host* host);

void        rt_sdhci_set_power_with_noreg(struct rt_sdhci_host *host, unsigned char mode,
                                  unsigned short vdd);
void        rt_sdhci_start_request(struct rt_mmc_host *mmc, struct rt_mmcsd_req *mrq);
int         rt_sdhci_start_request_atomic(struct rt_mmc_host *mmc, struct rt_mmcsd_req *mrq);
void        rt_sdhci_set_bus_width(struct rt_sdhci_host *host, int width);
void        rt_sdhci_reset(struct rt_sdhci_host *host, rt_uint8_t mask);
void        rt_sdhci_set_uhs(struct rt_sdhci_host *host, unsigned timing);
int         rt_sdhci_execute_tuning(struct rt_mmc_host *mmc, rt_uint32_t opcode);
int         __sdhci_execute_tuning(struct rt_sdhci_host *host, rt_uint32_t opcode);
void        rt_sdhci_ios_set(struct rt_mmc_host *mmc, struct rt_mmcsd_io_cfg *ios);
int         rt_sdhci_start_signal_voltage_switch(struct rt_mmc_host        *mmc,
                                              struct rt_mmcsd_io_cfg *ios);
void        rt_sdhci_enable_io_irq(struct rt_mmc_host *mmc, int enable);
void        rt_sdhci_start_tuning(struct rt_sdhci_host *host);
void        rt_sdhci_end_tuning(struct rt_sdhci_host *host);
void        rt_sdhci_reset_tuning(struct rt_sdhci_host *host);
void        rt_sdhci_send_tuning(struct rt_sdhci_host *host, rt_uint32_t opcode);
void        rt_sdhci_abort_tuning(struct rt_sdhci_host *host, rt_uint32_t opcode);
void        rt_sdhci_data_irq_timeout(struct rt_sdhci_host *host, rt_bool_t enable);
void        rt_sdhci_timeout_set(struct rt_sdhci_host *host, struct rt_mmcsd_cmd *cmd);
void        rt_read_reg_debug(struct rt_sdhci_host* host);

#endif /* __RT_SDHCI_HW_H */
