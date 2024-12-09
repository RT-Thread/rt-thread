/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_otp_drv.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
#define SHADOW_INDEX_IN_PMIC_OTP_END (15U)
#define OTP_UNLOCK_MAGIC_NUM (0x4E45504FUL) /*!< ASCII: OPEN */
#define OTP_LOCK_MAGIC_NUM (~OTP_UNLOCK_MAGIC_NUM)
#define OTP_CMD_PROGRAM      (0x574F4C42UL) /*!< ASCII: BLOW */
#define OTP_CMD_READ         (0x44414552UL) /*!< ASCII: READ */


/***********************************************************************************************************************
 * Codes
 **********************************************************************************************************************/
void otp_init(void)
{

}

void otp_deinit(void)
{

}

uint32_t otp_read_from_shadow(uint32_t addr)
{
    uint32_t ret_val = 0;
    if (addr < ARRAY_SIZE(HPM_OTP->SHADOW)) {
        ret_val = (addr <= SHADOW_INDEX_IN_PMIC_OTP_END) ? HPM_OTP->SHADOW[addr] : HPM_OTPSHW->SHADOW[addr];
    }

    return ret_val;
}

uint32_t otp_read_from_ip(uint32_t addr)
{
    uint32_t  ret_val = 0;
    if (addr < ARRAY_SIZE(HPM_OTP->SHADOW)) {
        ret_val = HPM_OTP->FUSE[addr];
    }
    return ret_val;
}

hpm_stat_t otp_program(uint32_t addr, const uint32_t *src, uint32_t num_of_words)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        uint32_t fuse_idx_max = ARRAY_SIZE(HPM_OTP->SHADOW);
        HPM_BREAK_IF((addr >= fuse_idx_max) || (num_of_words > fuse_idx_max) || (addr + num_of_words > fuse_idx_max));

        /* Enable 2.5V LDO for FUSE programming */
        uint32_t reg_val = (HPM_PCFG->LDO2P5 & ~PCFG_LDO2P5_VOLT_MASK) | PCFG_LDO2P5_ENABLE_MASK | PCFG_LDO2P5_VOLT_SET(2500);
        HPM_PCFG->LDO2P5 = reg_val;
        /* Wait until LDO is ready */
        while (!IS_HPM_BITMASK_SET(HPM_PCFG->LDO2P5, PCFG_DCDC_MODE_READY_MASK)) {
        }
        HPM_OTP->UNLOCK = OTP_UNLOCK_MAGIC_NUM;
        for (uint32_t i = 0; i < num_of_words; i++) {
            HPM_OTP->FUSE[addr++] = *src++;
        }
        HPM_OTP->UNLOCK = OTP_LOCK_MAGIC_NUM;
        /* Disable 2.5V LDO after FUSE programming for saving power */
        HPM_PCFG->LDO2P5 &= ~PCFG_LDO2P5_ENABLE_MASK;
        status = status_success;
    } while (false);

    return status;
}

hpm_stat_t otp_reload(otp_region_t region)
{
    hpm_stat_t status = status_invalid_argument;
    if ((uint32_t)region < 0x10 && (region >= otp_region0_mask)) {
        HPM_OTP->LOAD_REQ = (uint32_t)region;
        HPM_OTP->LOAD_COMP = (uint32_t)region;
        while (!IS_HPM_BITMASK_SET(HPM_OTP->LOAD_COMP, region)) {

        }
        status = status_success;
    }

    return status;
}

hpm_stat_t otp_lock_otp(uint32_t addr, otp_lock_option_t lock_option)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        HPM_BREAK_IF(addr >= ARRAY_SIZE(HPM_OTP->SHADOW) || (lock_option > otp_lock_option_max));

        OTP_Type *otp_base = (addr <= SHADOW_INDEX_IN_PMIC_OTP_END) ? HPM_OTP : HPM_OTPSHW;

        uint32_t lock_reg_idx = (addr << 1) / 32;
        uint32_t lock_reg_offset = (addr << 1) % 32;

        uint32_t lock_mask = ((uint32_t)lock_option) << lock_reg_offset;

        otp_base->FUSE_LOCK[lock_reg_idx] = lock_mask;

        status = status_success;
    } while (false);

    return status;
}

hpm_stat_t otp_lock_shadow(uint32_t addr, otp_lock_option_t lock_option)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        HPM_BREAK_IF(addr >= ARRAY_SIZE(HPM_OTP->SHADOW) || (lock_option > otp_lock_option_max));

        OTP_Type *otp_base = (addr <= SHADOW_INDEX_IN_PMIC_OTP_END) ? HPM_OTP : HPM_OTPSHW;

        uint32_t lock_reg_idx = (addr << 1) / 32;
        uint32_t lock_reg_offset = (addr << 1) % 32;

        uint32_t lock_mask = ((uint32_t)lock_option) << lock_reg_offset;

        otp_base->SHADOW_LOCK[lock_reg_idx] = lock_mask;

        status = status_success;
    } while (false);

    return status;
}

hpm_stat_t otp_set_configurable_region(uint32_t start, uint32_t num_of_words)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        uint32_t max_fuse_idx = ARRAY_SIZE(HPM_OTP->SHADOW);
        HPM_BREAK_IF((start >= max_fuse_idx) || (num_of_words > max_fuse_idx) || ((start  + num_of_words) > max_fuse_idx));

        HPM_OTP->REGION[3] = OTP_REGION_START_SET(start)
            | OTP_REGION_STOP_SET(start + num_of_words);

        status = status_success;
    } while (false);

    return status;
}

hpm_stat_t otp_write_shadow_register(uint32_t addr, uint32_t val)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        HPM_BREAK_IF(addr >= ARRAY_SIZE(HPM_OTP->SHADOW));

        uint32_t lock_reg_idx = (addr << 1) / 32;
        uint32_t lock_reg_offset = (addr << 1) % 32;
        uint32_t lock_mask = 3U << lock_reg_offset;

        OTP_Type *otp_base = (addr <= SHADOW_INDEX_IN_PMIC_OTP_END) ? HPM_OTP : HPM_OTPSHW;
        otp_lock_option_t lock_opt = (otp_lock_option_t) ((otp_base->SHADOW_LOCK[lock_reg_idx] & lock_mask)
                >> lock_reg_offset);

        if (lock_opt != otp_no_lock) {
            status = otp_write_disallowed;
            break;
        }

        otp_base->SHADOW[addr] = val;

        status = status_success;
    } while (false);

    return status;
}
