#ifndef __SDHCI_MMC_H__
#define __SDHCI_MMC_H__

#include <rtthread.h>
#include <drivers/mmcsd_cmd.h>
#include <drivers/mmcsd_core.h>
#include <drivers/mmcsd_host.h>
#define mmc_dev(x) ((x)->parent)

#define MMC_SEND_TUNING_BLOCK_HS200 SEND_TUNING_BLOCK_HS200
#define MMC_SEND_TUNING_BLOCK SEND_TUNING_BLOCK
#define MMC_STOP_TRANSMISSION STOP_TRANSMISSION
#define MMC_BUS_TEST_R           14   /* adtc                    R1  */
#define MMC_WRITE_MULTIPLE_BLOCK WRITE_MULTIPLE_BLOCK
#define MMC_READ_MULTIPLE_BLOCK READ_MULTIPLE_BLOCK

#define MMC_TIMING_UHS_DDR50 MMCSD_TIMING_UHS_DDR50
#define MMC_TIMING_UHS_SDR50 MMCSD_TIMING_UHS_SDR50
#define MMC_TIMING_MMC_HS200 MMCSD_TIMING_MMC_HS200
#define MMC_TIMING_MMC_HS400 MMCSD_TIMING_MMC_HS400
#define MMC_TIMING_UHS_SDR104 MMCSD_TIMING_UHS_SDR104
#define MMC_TIMING_UHS_SDR25 MMCSD_TIMING_UHS_SDR25
#define MMC_TIMING_MMC_DDR52 MMCSD_TIMING_MMC_DDR52
#define MMC_TIMING_UHS_SDR12 MMCSD_TIMING_UHS_SDR12
#define MMC_TIMING_SD_HS MMCSD_TIMING_SD_HS
#define  MMC_TIMING_MMC_HS  MMCSD_TIMING_MMC_HS

#define MMC_POWER_OFF       MMCSD_POWER_OFF
#define MMC_POWER_UP        MMCSD_POWER_UP
#define MMC_POWER_ON        MMCSD_POWER_ON
#define MMC_POWER_UNDEFINED 3

#define MMC_SET_DRIVER_TYPE_B   0
#define MMC_SET_DRIVER_TYPE_A   1
#define MMC_SET_DRIVER_TYPE_C   2
#define MMC_SET_DRIVER_TYPE_D   3

#define MMC_SIGNAL_VOLTAGE_330  0
#define MMC_SIGNAL_VOLTAGE_180  1
#define MMC_SIGNAL_VOLTAGE_120  2

#define MMC_RSP_PRESENT (1 << 16)
#define MMC_RSP_136 (1 << 17)       /* 136 bit response */
#define MMC_RSP_CRC (1 << 18)       /* expect valid crc */
#define MMC_RSP_BUSY    (1 << 19)       /* card may send busy */
#define MMC_RSP_OPCODE  (1 << 20)       /* response contains opcode */

/*
 * These are the native response types, and correspond to valid bit
 * patterns of the above flags.  One additional valid pattern
 * is all zeros, which means we don't expect a response.
 */
#define MMC_RSP_NONE    (0)
#define MMC_RSP_R1  (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R1B (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE|MMC_RSP_BUSY)
#define MMC_RSP_R2  (MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC)
#define MMC_RSP_R3  (MMC_RSP_PRESENT)
#define MMC_RSP_R4  (MMC_RSP_PRESENT)
#define MMC_RSP_R5  (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R6  (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R7  (MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)

#define MMC_CMD_ADTC CMD_ADTC

#define MMC_BUS_WIDTH_8 MMCSD_BUS_WIDTH_8
#define MMC_BUS_WIDTH_4 MMCSD_BUS_WIDTH_4
#define MMC_BUS_WIDTH_1 MMCSD_BUS_WIDTH_1

static inline rt_bool_t mmc_op_multi(rt_uint32_t opcode)
{
	return opcode == MMC_WRITE_MULTIPLE_BLOCK ||
	       opcode == MMC_READ_MULTIPLE_BLOCK;
}

static inline rt_bool_t mmc_op_tuning(rt_uint32_t opcode)
{
	return opcode == MMC_SEND_TUNING_BLOCK ||
			opcode == MMC_SEND_TUNING_BLOCK_HS200;
}

static inline int mmc_card_is_removable(struct mmc_host *host)
{
    return !(host->caps & MMC_CAP_NONREMOVABLE);
}

int mmc_gpio_get_cd(struct mmc_host *host)
{
    return -ENOSYS;
}

void mmc_detect_change(struct mmc_host *host, unsigned long delay)
{

}

int mmc_regulator_set_vqmmc(struct mmc_host *mmc, struct mmc_ios *ios)
{
    return 0;
}

rt_bool_t mmc_can_gpio_ro(struct mmc_host *host)
{
    return RT_FALSE;
}

int mmc_gpio_get_ro(struct mmc_host *host)
{
    return 0;
}

/************************************************************************************************ */
#endif