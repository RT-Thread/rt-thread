/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_esc_drv.h"

#ifndef HPM_ESC_DRV_DEFAULT_RETRY_COUNT
#define HPM_ESC_DRV_DEFAULT_RETRY_COUNT (0xA0000000U)
#endif

hpm_stat_t esc_mdio_read(ESC_Type *ptr, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
{
    uint32_t retry;

    ptr->MIIM_PDI_ACC_STAT = 1; /* PDI access MII management interface */

    /* wait for MII idle */
    retry = 0;
    while ((ptr->MII_MNG_CS & ESC_MII_MNG_CS_BUSY_MASK) != 0) {
        if (retry > HPM_ESC_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_ESC_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    /* set PHY address and register address */
    ptr->PHY_ADDR = phy_addr;
    ptr->PHY_REG_ADDR = reg_addr;

    /* read command */
    ptr->MII_MNG_CS = (ptr->MII_MNG_CS & ~ESC_MII_MNG_CS_CMD_MASK) | ESC_MII_MNG_CS_CMD_SET(1);

    /* wait command done */
    retry = 0;
    while ((ptr->MII_MNG_CS & ESC_MII_MNG_CS_BUSY_MASK) != 0) {
        if (retry > HPM_ESC_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_ESC_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    /* check error status */
    if ((ptr->MII_MNG_CS & ESC_MII_MNG_CS_CMD_ERR_MASK) != 0) {
        return status_fail;
    }

    /* check error status */
    if ((ptr->MII_MNG_CS & ESC_MII_MNG_CS_CMD_ERR_MASK) != 0) {
        return status_fail;
    }

    *data = ptr->PHY_DATA;

    return status_success;
}

hpm_stat_t esc_mdio_write(ESC_Type *ptr, uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
{
    uint32_t retry;

    ptr->MIIM_PDI_ACC_STAT = 1; /* PDI access MII management interface */

    /* wait for MII idle */
    retry = 0;
    while ((ptr->MII_MNG_CS & ESC_MII_MNG_CS_BUSY_MASK) != 0) {
        if (retry > HPM_ESC_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_ESC_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }


    /* set PHY address, register address and register value */
    ptr->PHY_ADDR = phy_addr;
    ptr->PHY_REG_ADDR = reg_addr;
    ptr->PHY_DATA = data;

    /* write command */
    ptr->MII_MNG_CS = (ptr->MII_MNG_CS & ~ESC_MII_MNG_CS_CMD_MASK) | ESC_MII_MNG_CS_WEN_MASK | ESC_MII_MNG_CS_CMD_SET(2);

    /* wait command done */
    retry = 0;
    while ((ptr->MII_MNG_CS & ESC_MII_MNG_CS_BUSY_MASK) != 0) {
        if (retry > HPM_ESC_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_ESC_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    /* check error status */
    if ((ptr->MII_MNG_CS & ESC_MII_MNG_CS_CMD_ERR_MASK) != 0) {
        return status_fail;
    }

    /* check error status */
    if ((ptr->MII_MNG_CS & ESC_MII_MNG_CS_CMD_ERR_MASK) != 0) {
        return status_fail;
    }

    return status_success;
}

/* Loding ESC EEPROM, EtherCAT communication is possible even if the EEPROM is blank */
hpm_stat_t esc_check_eeprom_loading(ESC_Type *ptr)
{
    hpm_stat_t stat = status_success;
    uint32_t retry = 0;

    while (1) {
        /* 0x110 bit0 eeprom load correctly */
        if ((ptr->ESC_DL_STAT & ESC_ESC_DL_STAT_EPLC_MASK) == ESC_ESC_DL_STAT_EPLC_MASK) {
            stat = status_success; /* Loading successful, PDI operations */
            break;
        }

        /* 0x502 bit13 ack or cmd error */
        if ((ptr->EEPROM_CTRL_STAT & ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_MASK) == ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_MASK) { /* ACMDERR = 1 */
            stat = status_esc_eeprom_ack_error; /* I2C bus error */
            break;
        } else {
            if ((ptr->EEPROM_CTRL_STAT & ESC_EEPROM_CTRL_STAT_CKSM_ERR_MASK) == ESC_EEPROM_CTRL_STAT_CKSM_ERR_MASK) {   /* ACMDERR,CKSUMERR = 01 */
                stat = status_esc_eeprom_checksum_error; /* EEPROM is loaded, but it is blank and cause checksum error  */
                break;
            }
        }

        if (retry > HPM_ESC_DRV_DEFAULT_RETRY_COUNT) {
            stat = status_timeout;
            break;
        }
        retry++;
    }

    return stat;
}
