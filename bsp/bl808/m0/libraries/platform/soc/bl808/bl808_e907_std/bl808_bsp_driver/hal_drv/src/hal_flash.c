/**
 * @file hal_flash.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "bl808_glb.h"
#include "bl808_xip_sflash.h"
#include "bl808_sf_cfg.h"
#include "bl808_romapi_patch.h"
#include "hal_flash.h"

static uint32_t g_jedec_id = 0;
static SPI_Flash_Cfg_Type g_flash_cfg;

/**
 * @brief flash_get_jedecid
 *
 * @return BL_Err_Type
 */
uint32_t flash_get_jedecid(void)
{
    uint32_t jid = 0;

    jid = ((g_jedec_id&0xff)<<16) + (g_jedec_id&0xff00) + ((g_jedec_id&0xff0000)>>16);
    return jid;
}

/**
 * @brief flash_get_cfg
 *
 * @return BL_Err_Type
 */
BL_Err_Type flash_get_cfg(uint8_t **cfg_addr, uint32_t *len)
{
    *cfg_addr = (uint8_t *)&g_flash_cfg;
    *len = sizeof(SPI_Flash_Cfg_Type);

    return SUCCESS;
}

/**
 * @brief flash_get_clock_delay
 *
 * @return BL_Err_Type
 */
static BL_Err_Type flash_get_clock_delay(SPI_Flash_Cfg_Type *cfg)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(SF_CTRL_BASE, SF_CTRL_0);
    /* bit0-3 for clk delay */
    if (BL_IS_REG_BIT_SET(tmpVal, SF_CTRL_SF_IF_READ_DLY_EN)) {
        cfg->clkDelay = BL_GET_REG_BITS_VAL(tmpVal, SF_CTRL_SF_IF_READ_DLY_N)+1;
    } else {
        cfg->clkDelay = 0;
    }
    cfg->clkInvert = 0;
    /* bit0 for clk invert */
    cfg->clkInvert |= ((BL_GET_REG_BITS_VAL(tmpVal, SF_CTRL_SF_CLK_OUT_INV_SEL)&1)<<0);
    /* bit1 for rx clk invert */
    cfg->clkInvert |= ((BL_GET_REG_BITS_VAL(tmpVal, SF_CTRL_SF_CLK_SF_RX_INV_SEL)&1)<<1);

    tmpVal = BL_RD_REG(SF_CTRL_BASE, SF_CTRL_SF_IF_IO_DLY_1);
    /* bit4-6 for do delay */
    cfg->clkDelay |= ((BL_GET_REG_BITS_VAL(tmpVal, SF_CTRL_IO_0_DO_DLY_SEL)&7)<<4);
    /* bit2-4 for di delay */
    cfg->clkInvert |= ((BL_GET_REG_BITS_VAL(tmpVal, SF_CTRL_IO_0_DI_DLY_SEL)&7)<<2);
    /* bit5-7 for oe delay */
    cfg->clkInvert |= ((BL_GET_REG_BITS_VAL(tmpVal, SF_CTRL_IO_0_OE_DLY_SEL)&7)<<5);

    return SUCCESS;
}

/**
 * @brief flash_set_qspi_enable
 *
 * @return BL_Err_Type
 */
static BL_Err_Type ATTR_TCM_SECTION flash_set_qspi_enable(SPI_Flash_Cfg_Type *p_flash_cfg)
{
    if ((p_flash_cfg->ioMode & 0x0f) == SF_CTRL_QO_MODE || (p_flash_cfg->ioMode & 0x0f) == SF_CTRL_QIO_MODE) {
        SFlash_Qspi_Enable(p_flash_cfg);
    }

    return SUCCESS;
}

/**
 * @brief flash_set_l1c_wrap
 *
 * @return BL_Err_Type
 */
static BL_Err_Type ATTR_TCM_SECTION flash_set_l1c_wrap(SPI_Flash_Cfg_Type *p_flash_cfg)
{
    if (((p_flash_cfg->ioMode >> 4) & 0x01) == 1) {
        L1C_Set_Wrap(DISABLE);
    } else {
        L1C_Set_Wrap(ENABLE);
        if ((p_flash_cfg->ioMode & 0x0f) == SF_CTRL_QO_MODE || (p_flash_cfg->ioMode & 0x0f) == SF_CTRL_QIO_MODE) {
            SFlash_SetBurstWrap(p_flash_cfg);
        }
    }

    return SUCCESS;
}

/**
 * @brief flash_config_init
 *
 * @return BL_Err_Type
 */
static BL_Err_Type ATTR_TCM_SECTION flash_config_init(SPI_Flash_Cfg_Type *p_flash_cfg, uint8_t *jedec_id)
{
    BL_Err_Type ret = ERROR;
    uint8_t isAesEnable = 0;
    uint32_t jid = 0;
    uint32_t offset = 0;

    cpu_global_irq_disable();
    XIP_SFlash_Opt_Enter(&isAesEnable);
    XIP_SFlash_State_Save(p_flash_cfg, &offset, 0, 0);
    SFlash_GetJedecId(p_flash_cfg, (uint8_t *)&jid);
    arch_memcpy(jedec_id, (uint8_t *)&jid, 3);
    jid &= 0xFFFFFF;
    g_jedec_id = jid;
    ret = SF_Cfg_Get_Flash_Cfg_Need_Lock_Ext(jid, p_flash_cfg, 0, 0);
    if (ret == SUCCESS) {
        p_flash_cfg->mid = (jid & 0xff);
    }

    /* Set flash controler from p_flash_cfg */
    flash_set_qspi_enable(p_flash_cfg);
    flash_set_l1c_wrap(p_flash_cfg);
    XIP_SFlash_State_Restore(p_flash_cfg, offset, 0, 0);
    XIP_SFlash_Opt_Exit(isAesEnable);
    cpu_global_irq_enable();

    return ret;
}

/**
 * @brief multi flash adapter
 *
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_TCM_SECTION flash_init(void)
{
    BL_Err_Type ret = ERROR;
    uint32_t jedec_id = 0;

    jedec_id = GLB_Get_Flash_Id_Value();
    if (jedec_id != 0) {
        ret = SF_Cfg_Get_Flash_Cfg_Need_Lock_Ext(jedec_id, &g_flash_cfg, 0, 0);
        if (ret == SUCCESS) {
            g_jedec_id = jedec_id;
            flash_get_clock_delay(&g_flash_cfg);
            return SUCCESS;
        }
    }

    cpu_global_irq_disable();
    L1C_ICache_Invalid_All();
    SF_Cfg_Get_Flash_Cfg_Need_Lock_Ext(0, &g_flash_cfg, 0, 0);
    L1C_ICache_Invalid_All();
    cpu_global_irq_enable();
    if (g_flash_cfg.mid != 0xff) {
        flash_get_clock_delay(&g_flash_cfg);
        return SUCCESS;
    }

    ret = flash_config_init(&g_flash_cfg, (uint8_t *)&jedec_id);
#ifdef HAL_FLASH_MSG
    MSG("flash ID = %08x\r\n", jedec_id);
    bflb_platform_dump((uint8_t *)&g_flash_cfg, sizeof(g_flash_cfg));
    if (ret != SUCCESS) {
        MSG("flash config init fail!\r\n");
    }
#endif
    flash_get_clock_delay(&g_flash_cfg);
    GLB_Set_Flash_Id_Value(g_jedec_id);

    return ret;
}

/**
 * @brief read jedec id
 *
 * @param data
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_TCM_SECTION flash_read_jedec_id(uint8_t *data)
{
    uint32_t jid = 0;

    cpu_global_irq_disable();
    XIP_SFlash_GetJedecId_Need_Lock(&g_flash_cfg, (uint8_t *)&jid, 0, 0);
    cpu_global_irq_enable();
    jid &= 0xFFFFFF;
    arch_memcpy(data, (void *)&jid, 4);

    return SUCCESS;
}

/**
 * @brief read flash data via xip
 *
 * @param flash xip addr or flash absolute addr
 * @param data
 * @param len
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_TCM_SECTION flash_read_via_xip(uint32_t addr, uint8_t *data, uint32_t len)
{
    addr = addr & (BL808_FLASH_XIP_END-BL808_FLASH_XIP_BASE-1);

    cpu_global_irq_disable();
    L1C_ICache_Invalid_All();
    XIP_SFlash_Read_Via_Cache_Need_Lock(addr, data, len, 0, 0);
    L1C_ICache_Invalid_All();
    cpu_global_irq_enable();

    return SUCCESS;
}

/**
 * @brief read flash data via sbus
 *
 * @param flash absolute addr
 * @param data
 * @param len
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_TCM_SECTION flash_read(uint32_t addr, uint8_t *data, uint32_t len)
{
    BL_Err_Type stat;

    if (addr >= BL808_FLASH_XIP_END-BL808_FLASH_XIP_BASE) {
        return ERROR;
    }

    cpu_global_irq_disable();
    stat = XIP_SFlash_Read_Need_Lock(&g_flash_cfg, addr, data, len, 0, 0);
    cpu_global_irq_enable();

    return stat;
}

/**
 * @brief write flash data via sbus
 *
 * @param flash absolute addr
 * @param data
 * @param len
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_TCM_SECTION flash_write(uint32_t addr, uint8_t *data, uint32_t len)
{
    BL_Err_Type stat;

    if (addr >= BL808_FLASH_XIP_END-BL808_FLASH_XIP_BASE) {
        return ERROR;
    }

    cpu_global_irq_disable();
    stat = XIP_SFlash_Write_Need_Lock(&g_flash_cfg, addr, data, len, 0, 0);
    cpu_global_irq_enable();

    return stat;
}

/**
 * @brief erase flash via sbus
 *
 * @param flash absolute startaddr
 * @param flash absolute endaddr
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_TCM_SECTION flash_erase(uint32_t startaddr, uint32_t len)
{
    BL_Err_Type stat;

    if (startaddr >= BL808_FLASH_XIP_END-BL808_FLASH_XIP_BASE) {
        return ERROR;
    }

    cpu_global_irq_disable();
    stat = XIP_SFlash_Erase_Need_Lock(&g_flash_cfg, startaddr, len, 0, 0);
    cpu_global_irq_enable();

    return stat;
}

/**
 * @brief set flash cache
 *
 * @param cont_read
 * @param cache_enable
 * @param cache_way_disable
 * @param flash_offset
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_TCM_SECTION flash_set_cache(uint8_t cont_read, uint8_t cache_enable, uint8_t cache_way_disable, uint32_t flash_offset)
{
    uint8_t isAesEnable = 0;
    uint32_t tmp[1];
    BL_Err_Type stat;

    SF_Ctrl_Set_Owner(SF_CTRL_OWNER_SAHB);

    XIP_SFlash_Opt_Enter(&isAesEnable);
    /* To make it simple, exit cont read anyway */
    SFlash_Reset_Continue_Read(&g_flash_cfg);

    if (g_flash_cfg.cReadSupport == 0) {
        cont_read = 0;
    }

    if (cont_read == 1) {
        stat = SFlash_Read(&g_flash_cfg, g_flash_cfg.ioMode & 0xf, 1, 0x00000000, (uint8_t *)tmp, sizeof(tmp));

        if (SUCCESS != stat) {
            XIP_SFlash_Opt_Exit(isAesEnable);
            return ERROR;
        }
    }

    /* TODO: Set default value */

    SF_Ctrl_Set_Flash_Image_Offset(flash_offset, 0, 0);
    SFlash_IDbus_Read_Enable(&g_flash_cfg, g_flash_cfg.ioMode & 0xf, cont_read, SF_CTRL_FLASH_BANK0);

    XIP_SFlash_Opt_Exit(isAesEnable);

    return SUCCESS;
}
