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
#include "bl_efuse.h"
#ifdef BL808
#include <bl808_ef_ctrl.h>
#include "bl808_mfg_media.h"
#include "bl808_glb.h"
#endif

int bl_efuse_read_mac(uint8_t mac[6])
{
    EF_Ctrl_Read_MAC_Address(mac);
    return 0;
}

int bl_efuse_read_mac_factory(uint8_t mac[6])
{
 //   if (0 == mfg_media_read_macaddr(mac, 1)) {
   //     return 0;
   //zys }
    return -1;
}

int bl_efuse_read_capcode(uint8_t *capcode)
{
//    if (0 == mfg_media_read_xtal_capcode(capcode, 1)) {
  //      return 0;
   //zys  }
    return -1;
}

int bl_efuse_read_pwroft(int8_t poweroffset[14])
{
  //  if (0 == mfg_media_read_poweroffset(poweroffset, 1)) {
    //    return 0;
    //}
    return -1;
}

int bl_efuse_ctrl_program_R0(uint32_t index, uint32_t *data, uint32_t len)
{
    uint8_t hdiv=0, bdiv=0;
    HBN_MCU_ROOT_CLK_Type rtClk=(HBN_MCU_ROOT_CLK_Type)HBN_Get_MCU_Root_CLK_Sel();

//    bdiv=GLB_Get_BCLK_Div();
//    hdiv=GLB_Get_HCLK_Div();
    hdiv = BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_SYS_CFG0), GLB_REG_HCLK_DIV);
    bdiv = BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_SYS_CFG0), GLB_REG_BCLK_DIV);

    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
    
    EF_Ctrl_Program_Direct_R0(index, data, len);
    
    GLB_Set_System_CLK_Div(hdiv, bdiv);
    HBN_Set_MCU_Root_CLK_Sel(rtClk);

    return 0;
}

int bl_efuse_ctrl_read_R0(uint32_t index, uint32_t *data, uint32_t len)
{
    uint8_t hdiv=0, bdiv=0;
    HBN_MCU_ROOT_CLK_Type rtClk=(HBN_MCU_ROOT_CLK_Type)HBN_Get_MCU_Root_CLK_Sel();

//    bdiv=GLB_Get_BCLK_Div();
//    hdiv=GLB_Get_HCLK_Div();
    hdiv = BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_SYS_CFG0), GLB_REG_HCLK_DIV);
    bdiv = BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_SYS_CFG0), GLB_REG_BCLK_DIV);


    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
    
    EF_Ctrl_Read_Direct_R0(index, data, len);
    
    GLB_Set_System_CLK_Div(hdiv, bdiv);
    HBN_Set_MCU_Root_CLK_Sel(rtClk);

    return 0;
}

int bl_efuse_read_mac_opt(uint8_t slot, uint8_t mac[6], uint8_t reload)
{
    uint8_t hdiv=0, bdiv=0;
    HBN_MCU_ROOT_CLK_Type rtClk=(HBN_MCU_ROOT_CLK_Type)HBN_Get_MCU_Root_CLK_Sel();

//    bdiv=GLB_Get_BCLK_Div();
//    hdiv=GLB_Get_HCLK_Div();
    hdiv = BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_SYS_CFG0), GLB_REG_HCLK_DIV);
    bdiv = BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_SYS_CFG0), GLB_REG_BCLK_DIV);

    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
    
//    EF_Ctrl_Read_MAC_Address_Opt(slot, mac, reload); 
    EF_Ctrl_Read_MAC_Address_Raw(mac);

    GLB_Set_System_CLK_Div(hdiv, bdiv);
    HBN_Set_MCU_Root_CLK_Sel(rtClk);

    return 0;
}
