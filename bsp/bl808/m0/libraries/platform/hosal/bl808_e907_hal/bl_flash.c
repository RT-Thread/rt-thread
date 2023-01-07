/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <blog.h>
#ifdef BL808
#include <bl808_glb.h>
#include <bl808_xip_sflash.h>
#include <bl808_sf_cfg.h>
#include <bl808_romdriver_e907.h>
#elif defined(BL606P)
#include <bl606p_glb.h>
#include <bl606p_xip_sflash.h>
#include <bl606p_sf_cfg.h>
#include <bl606p_sf_cfg_ext.h>
#include <bl606p_romdriver_e907.h>
#else
#error "Use CHIP BL808/BL606P for this module"
#endif

#include "bl_irq.h"

#define XIP_START_ADDR    (0x58000000)
#define ADDR_LIMIT        (0x1000000)

#define USER_UNUSED(a) ((void)(a))
static SPI_Flash_Cfg_Type g_flash_cfg;

/**
 * @brief flash read data
 *
 * @param addr
 * @param data
 * @param len
 * @return BL_Err_Type
 */
int ATTR_TCM_SECTION bl_flash_read(uint32_t startaddr, void *data, uint32_t len)
{
    BL_Err_Type stat;
    uint8_t isAesEnable=0;

    GLOBAL_IRQ_SAVE();
    XIP_SFlash_Opt_Enter(&isAesEnable);
    stat = XIP_SFlash_Read_Need_Lock(&g_flash_cfg, startaddr, data, len, 0, 0);
    XIP_SFlash_Opt_Exit(isAesEnable);
    GLOBAL_IRQ_RESTORE();

    return stat;
}

/**
 * @brief flash write data
 *
 * @param addr
 * @param data
 * @param len
 * @return BL_Err_Type
 */
int ATTR_TCM_SECTION bl_flash_write(uint32_t startaddr, void *data, uint32_t len)
{
    BL_Err_Type stat;
    uint8_t isAesEnable=0;

    GLOBAL_IRQ_SAVE();
    XIP_SFlash_Opt_Enter(&isAesEnable);
    stat = XIP_SFlash_Write_Need_Lock(&g_flash_cfg, startaddr, data, len, 0, 0);
    XIP_SFlash_Opt_Exit(isAesEnable);
    GLOBAL_IRQ_RESTORE();

    return stat;
}

/**
 * @brief flash erase
 *
 * @param startaddr
 * @param endaddr
 * @return BL_Err_Type
 */
int ATTR_TCM_SECTION bl_flash_erase(uint32_t startaddr, uint32_t len)
{
    BL_Err_Type stat;
    uint8_t isAesEnable=0;

    GLOBAL_IRQ_SAVE();
    XIP_SFlash_Opt_Enter(&isAesEnable);
    stat = XIP_SFlash_Erase_Need_Lock(&g_flash_cfg, startaddr, len-1, 0, 0);
    XIP_SFlash_Opt_Exit(isAesEnable);
    GLOBAL_IRQ_RESTORE();

    return stat;
}

/**
 * @brief flash read from xip
 *
 * @param xip addr
 * @param dst
 * @param len
 * @return BL_Err_Type
 */
int bl_flash_read_byxip(uint32_t addr, uint8_t *dst, int len)
{
    uint32_t offset;
    uint32_t xipaddr;

    offset = RomDriver_SF_Ctrl_Get_Flash_Image_Offset(0, 0);

    if ((addr < offset) || (addr >= ADDR_LIMIT)) {
        // not support or arg err ?
        return -1;
    }

    xipaddr =  XIP_START_ADDR - offset + addr;
    memcpy(dst, (void *)xipaddr, len);

    return 0;
}

/**
 * @brief multi flash adapter
 *
 * @return BL_Err_Type
 */
int ATTR_TCM_SECTION bl_flash_init(void)
{
    uint8_t isAesEnable=0;

    /* Get flash config identify */
    GLOBAL_IRQ_SAVE();
    XIP_SFlash_Opt_Enter(&isAesEnable);
    SF_Cfg_Flash_Identify_Ext(1, 0x80, 0, &g_flash_cfg, 0, 0);
    XIP_SFlash_Opt_Exit(isAesEnable);
    GLOBAL_IRQ_RESTORE();

    return 0;
}

static void _dump_flash_config()
{
    extern uint8_t __boot2_flashCfg_src;

    USER_UNUSED(__boot2_flashCfg_src);
    
    blog_info("======= FlashCfg magiccode @%p=======\r\n", &__boot2_flashCfg_src);
    blog_info("mid \t\t0x%X\r\n", g_flash_cfg.mid);
    blog_info("clkDelay \t0x%X\r\n", g_flash_cfg.clkDelay);
    blog_info("clkInvert \t0x%X\r\n", g_flash_cfg.clkInvert);
    blog_info("sector size\t%uKBytes\r\n", g_flash_cfg.sectorSize);
    blog_info("page size\t%uBytes\r\n", g_flash_cfg.pageSize);
    blog_info("---------------------------------------------------------------\r\n");
}

int bl_flash_config_update(void)
{
    _dump_flash_config();

    return 0;
}
