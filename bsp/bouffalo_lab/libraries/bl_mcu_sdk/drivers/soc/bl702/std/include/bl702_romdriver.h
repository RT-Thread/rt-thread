/**
  ******************************************************************************
  * @file    bl702_romdriver.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 Bouffalo Lab</center></h2>
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
  *
  ******************************************************************************
  */
#ifndef __BL702_ROMDRIVER_H__
#define __BL702_ROMDRIVER_H__

#include "bl702_common.h"
#include "bl702_aon.h"
#include "bl702_glb.h"
#include "bl702_hbn.h"
#include "bflb_spi_psram.h"
#include "bflb_xip_sflash.h"
#include "bflb_sflash.h"
#include "bflb_sf_ctrl.h"
// #include "softcrc.h"

#define ROMAPI_INDEX_SECT_SIZE (0x800)
#define ROMAPI_INDEX_MAX       (ROMAPI_INDEX_SECT_SIZE / 4 - 1)

typedef enum {
    ROM_API_INDEX_REV = 0,

    ROM_API_INDEX_FUNC_START = 4,

    ROM_API_INDEX_AON_Power_On_MBG = ROM_API_INDEX_FUNC_START,
    ROM_API_INDEX_AON_Power_Off_MBG,
    ROM_API_INDEX_AON_Power_On_XTAL,
    ROM_API_INDEX_AON_Set_Xtal_CapCode,
    ROM_API_INDEX_AON_Power_Off_XTAL,

    ROM_API_INDEX_ASM_Delay_Us,
    ROM_API_INDEX_BL702_Delay_US,
    ROM_API_INDEX_BL702_Delay_MS,
    ROM_API_INDEX_BL702_MemCpy,
    ROM_API_INDEX_BL702_MemCpy4,
    ROM_API_INDEX_BL702_MemCpy_Fast,
    ROM_API_INDEX_ARCH_MemCpy_Fast,
    ROM_API_INDEX_BL702_MemSet,
    ROM_API_INDEX_BL702_MemSet4,
    ROM_API_INDEX_BL702_MemCmp,
    ROM_API_INDEX_BFLB_Soft_CRC32,

    ROM_API_INDEX_GLB_Get_Root_CLK_Sel,
    ROM_API_INDEX_GLB_Set_System_CLK_Div,
    ROM_API_INDEX_GLB_Get_BCLK_Div,
    ROM_API_INDEX_GLB_Get_HCLK_Div,
    ROM_API_INDEX_Update_SystemCoreClockWith_XTAL,
    ROM_API_INDEX_GLB_Set_System_CLK,
    ROM_API_INDEX_System_Core_Clock_Update_From_RC32M,
    ROM_API_INDEX_GLB_Set_SF_CLK,
    ROM_API_INDEX_GLB_Power_Off_DLL,
    ROM_API_INDEX_GLB_Power_On_DLL,
    ROM_API_INDEX_GLB_Enable_DLL_All_Clks,
    ROM_API_INDEX_GLB_Enable_DLL_Clk,
    ROM_API_INDEX_GLB_Disable_DLL_All_Clks,
    ROM_API_INDEX_GLB_Disable_DLL_Clk,
    ROM_API_INDEX_GLB_SW_System_Reset,
    ROM_API_INDEX_GLB_SW_CPU_Reset,
    ROM_API_INDEX_GLB_SW_POR_Reset,
    ROM_API_INDEX_GLB_Select_Internal_Flash,
    ROM_API_INDEX_GLB_Swap_Flash_Pin,
    ROM_API_INDEX_GLB_Swap_Flash_CS_IO2_Pin,
    ROM_API_INDEX_GLB_Swap_Flash_IO0_IO3_Pin,
    ROM_API_INDEX_GLB_Select_Internal_PSram,
    ROM_API_INDEX_GLB_GPIO_Init,
    ROM_API_INDEX_GLB_GPIO_OUTPUT_Enable,
    ROM_API_INDEX_GLB_GPIO_OUTPUT_Disable,
    ROM_API_INDEX_GLB_GPIO_Set_HZ,
    ROM_API_INDEX_GLB_Deswap_Flash_Pin,
    ROM_API_INDEX_GLB_Select_External_Flash,
    ROM_API_INDEX_GLB_GPIO_Get_Fun,

    ROM_API_INDEX_EF_Ctrl_Busy,
    ROM_API_INDEX_EF_Ctrl_Sw_AHB_Clk_0,
    ROM_API_INDEX_EF_Ctrl_Load_Efuse_R0,
    ROM_API_INDEX_EF_Ctrl_Clear,
    ROM_API_INDEX_EF_Ctrl_Get_Trim_Parity,
    ROM_API_INDEX_EF_Ctrl_Read_RC32K_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_RC32M_Trim,

    ROM_API_INDEX_PDS_Trim_RC32M,
    ROM_API_INDEX_PDS_Select_RC32M_As_PLL_Ref,
    ROM_API_INDEX_PDS_Select_XTAL_As_PLL_Ref,
    ROM_API_INDEX_PDS_Power_On_PLL,
    ROM_API_INDEX_PDS_Enable_PLL_All_Clks,
    ROM_API_INDEX_PDS_Disable_PLL_All_Clks,
    ROM_API_INDEX_PDS_Enable_PLL_Clk,
    ROM_API_INDEX_PDS_Disable_PLL_Clk,
    ROM_API_INDEX_PDS_Power_Off_PLL,
    ROM_API_INDEX_PDS_Reset,
    ROM_API_INDEX_PDS_Enable,
    ROM_API_INDEX_PDS_Auto_Time_Config,
    ROM_API_INDEX_PDS_Auto_Enable,
    ROM_API_INDEX_PDS_Manual_Force_Turn_Off,
    ROM_API_INDEX_PDS_Manual_Force_Turn_On,

    ROM_API_INDEX_HBN_Enable,
    ROM_API_INDEX_HBN_Reset,
    ROM_API_INDEX_HBN_GPIO_Dbg_Pull_Cfg,
    ROM_API_INDEX_HBN_Trim_RC32K,
    ROM_API_INDEX_HBN_Set_ROOT_CLK_Sel,

    ROM_API_INDEX_XIP_SFlash_State_Save,
    ROM_API_INDEX_XIP_SFlash_State_Restore,
    ROM_API_INDEX_XIP_SFlash_Erase_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_Write_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_Read_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_GetJedecId_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_GetDeviceId_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_GetUniqueId_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_Read_Via_Cache_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_Read_With_Lock,
    ROM_API_INDEX_XIP_SFlash_Write_With_Lock,
    ROM_API_INDEX_XIP_SFlash_Erase_With_Lock,

    ROM_API_INDEX_SFlash_Init,
    ROM_API_INDEX_SFlash_SetSPIMode,
    ROM_API_INDEX_SFlash_Read_Reg,
    ROM_API_INDEX_SFlash_Write_Reg,
    ROM_API_INDEX_SFlash_Read_Reg_With_Cmd,
    ROM_API_INDEX_SFlash_Write_Reg_With_Cmd,
    ROM_API_INDEX_SFlash_Busy,
    ROM_API_INDEX_SFlash_Write_Enable,
    ROM_API_INDEX_SFlash_Qspi_Enable,
    ROM_API_INDEX_SFlash_Volatile_Reg_Write_Enable,
    ROM_API_INDEX_SFlash_Chip_Erase,
    ROM_API_INDEX_SFlash_Sector_Erase,
    ROM_API_INDEX_SFlash_Blk32_Erase,
    ROM_API_INDEX_SFlash_Blk64_Erase,
    ROM_API_INDEX_SFlash_Erase,
    ROM_API_INDEX_SFlash_Program,
    ROM_API_INDEX_SFlash_GetUniqueId,
    ROM_API_INDEX_SFlash_GetJedecId,
    ROM_API_INDEX_SFlash_GetDeviceId,
    ROM_API_INDEX_SFlash_Powerdown,
    ROM_API_INDEX_SFlash_Releae_Powerdown,
    ROM_API_INDEX_SFlash_Restore_From_Powerdown,
    ROM_API_INDEX_SFlash_SetBurstWrap,
    ROM_API_INDEX_SFlash_DisableBurstWrap,
    ROM_API_INDEX_SFlash_Software_Reset,
    ROM_API_INDEX_SFlash_Reset_Continue_Read,
    ROM_API_INDEX_SFlash_Set_IDbus_Cfg,
    ROM_API_INDEX_SFlash_IDbus_Read_Enable,
    ROM_API_INDEX_SFlash_Cache_Read_Enable,
    ROM_API_INDEX_SFlash_Cache_Read_Disable,
    ROM_API_INDEX_SFlash_Read,

    ROM_API_INDEX_L1C_Cache_Enable_Set,
    ROM_API_INDEX_L1C_Cache_Write_Set,
    ROM_API_INDEX_L1C_Cache_Flush,
    ROM_API_INDEX_L1C_Cache_Hit_Count_Get,
    ROM_API_INDEX_L1C_Cache_Miss_Count_Get,
    ROM_API_INDEX_L1C_Cache_Read_Disable,
    ROM_API_INDEX_L1C_Set_Wrap,
    ROM_API_INDEX_L1C_Set_Way_Disable,
    ROM_API_INDEX_L1C_IROM_2T_Access_Set,

    ROM_API_INDEX_SF_Ctrl_Enable,
    ROM_API_INDEX_SF_Ctrl_Psram_Init,
    ROM_API_INDEX_SF_Ctrl_Get_Clock_Delay,
    ROM_API_INDEX_SF_Ctrl_Set_Clock_Delay,
    ROM_API_INDEX_SF_Ctrl_Cmds_Set,
    ROM_API_INDEX_SF_Ctrl_Set_Owner,
    ROM_API_INDEX_SF_Ctrl_Disable,
    ROM_API_INDEX_SF_Ctrl_Select_Pad,
    ROM_API_INDEX_SF_Ctrl_Select_Bank,
    ROM_API_INDEX_SF_Ctrl_AES_Enable_BE,
    ROM_API_INDEX_SF_Ctrl_AES_Enable_LE,
    ROM_API_INDEX_SF_Ctrl_AES_Set_Region,
    ROM_API_INDEX_SF_Ctrl_AES_Set_Key,
    ROM_API_INDEX_SF_Ctrl_AES_Set_Key_BE,
    ROM_API_INDEX_SF_Ctrl_AES_Set_IV,
    ROM_API_INDEX_SF_Ctrl_AES_Set_IV_BE,
    ROM_API_INDEX_SF_Ctrl_AES_Enable,
    ROM_API_INDEX_SF_Ctrl_AES_Disable,
    ROM_API_INDEX_SF_Ctrl_Is_AES_Enable,
    ROM_API_INDEX_SF_Ctrl_Set_Flash_Image_Offset,
    ROM_API_INDEX_SF_Ctrl_Get_Flash_Image_Offset,
    ROM_API_INDEX_SF_Ctrl_Select_Clock,
    ROM_API_INDEX_SF_Ctrl_SendCmd,
    ROM_API_INDEX_SF_Ctrl_Flash_Read_Icache_Set,
    ROM_API_INDEX_SF_Ctrl_Psram_Write_Icache_Set,
    ROM_API_INDEX_SF_Ctrl_Psram_Read_Icache_Set,
    ROM_API_INDEX_SF_Ctrl_GetBusyState,
    ROM_API_INDEX_SF_Cfg_Deinit_Ext_Flash_Gpio,
    ROM_API_INDEX_SF_Cfg_Init_Ext_Flash_Gpio,
    ROM_API_INDEX_SF_Cfg_Get_Flash_Cfg_Need_Lock,
    ROM_API_INDEX_SF_Cfg_Init_Flash_Gpio,
    ROM_API_INDEX_SF_Cfg_Flash_Identify,

    ROM_API_INDEX_Psram_Init,
    ROM_API_INDEX_Psram_ReadReg,
    ROM_API_INDEX_Psram_WriteReg,
    ROM_API_INDEX_Psram_SetDriveStrength,
    ROM_API_INDEX_Psram_SetBurstWrap,
    ROM_API_INDEX_Psram_ReadId,
    ROM_API_INDEX_Psram_EnterQuadMode,
    ROM_API_INDEX_Psram_ExitQuadMode,
    ROM_API_INDEX_Psram_ToggleBurstLength,
    ROM_API_INDEX_Psram_SoftwareReset,
    ROM_API_INDEX_Psram_Set_IDbus_Cfg,
    ROM_API_INDEX_Psram_Cache_Write_Set,
    ROM_API_INDEX_Psram_Write,
    ROM_API_INDEX_Psram_Read,

    ROM_API_INDEX_FUNC_LAST = ROM_API_INDEX_Psram_Read,

    ROM_API_INDEX_FUNC_INVALID_START,

    ROM_API_INDEX_FUNC_LAST_ENTRY = ROMAPI_INDEX_MAX
} ROM_API_INDEX_e;

/** @addtogroup  BL702_Peripheral_Driver
 *  @{
 */

/** @addtogroup  ROMDRIVER
 *  @{
 */

/** @defgroup  ROMDRIVER_Public_Types
 *  @{
 */
#define ROM_APITABLE ((uint32_t *)0x21018800)

#define RomDriver_AON_Power_On_MBG \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_AON_Power_On_MBG])
#define RomDriver_AON_Power_Off_MBG \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_AON_Power_Off_MBG])
#define RomDriver_AON_Power_On_XTAL \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_AON_Power_On_XTAL])
#define RomDriver_AON_Set_Xtal_CapCode \
    ((BL_Err_Type(*)(uint8_t capIn, uint8_t capOut))ROM_APITABLE[ROM_API_INDEX_AON_Set_Xtal_CapCode])
#define RomDriver_AON_Power_Off_XTAL \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_AON_Power_Off_XTAL])

#define RomDriver_ASM_Delay_Us \
    ((void (*)(uint32_t core, uint32_t cnt))ROM_APITABLE[ROM_API_INDEX_ASM_Delay_Us])
#define RomDriver_BL702_Delay_US \
    ((void (*)(uint32_t cnt))ROM_APITABLE[ROM_API_INDEX_BL702_Delay_US])
#define RomDriver_BL702_Delay_MS \
    ((void (*)(uint32_t cnt))ROM_APITABLE[ROM_API_INDEX_BL702_Delay_MS])
#define RomDriver_BL702_MemCpy \
    ((void *(*)(void *dst, const void *src, uint32_t n))ROM_APITABLE[ROM_API_INDEX_BL702_MemCpy])
#define RomDriver_BL702_MemCpy4 \
    ((uint32_t * (*)(uint32_t * dst, const uint32_t *src, uint32_t n)) ROM_APITABLE[ROM_API_INDEX_BL702_MemCpy4])
#define RomDriver_BL702_MemCpy_Fast \
    ((void *(*)(void *pdst, const void *psrc, uint32_t n))ROM_APITABLE[ROM_API_INDEX_BL702_MemCpy_Fast])
#define RomDriver_ARCH_MemCpy_Fast \
    ((void *(*)(void *pdst, const void *psrc, uint32_t n))ROM_APITABLE[ROM_API_INDEX_ARCH_MemCpy_Fast])
#define RomDriver_BL702_MemSet \
    ((void *(*)(void *s, uint8_t c, uint32_t n))ROM_APITABLE[ROM_API_INDEX_BL702_MemSet])
#define RomDriver_BL702_MemSet4 \
    ((uint32_t * (*)(uint32_t * dst, const uint32_t val, uint32_t n)) ROM_APITABLE[ROM_API_INDEX_BL702_MemSet4])
#define RomDriver_BL702_MemCmp \
    ((int (*)(const void *s1, const void *s2, uint32_t n))ROM_APITABLE[ROM_API_INDEX_BL702_MemCmp])
#define RomDriver_BFLB_Soft_CRC32 \
    ((uint32_t(*)(void *dataIn, uint32_t len))ROM_APITABLE[ROM_API_INDEX_BFLB_Soft_CRC32])

#define RomDriver_GLB_Get_Root_CLK_Sel \
    ((GLB_ROOT_CLK_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Get_Root_CLK_Sel])
#define RomDriver_GLB_Set_System_CLK_Div \
    ((BL_Err_Type(*)(uint8_t hclkDiv, uint8_t bclkDiv))ROM_APITABLE[ROM_API_INDEX_GLB_Set_System_CLK_Div])
#define RomDriver_GLB_Get_BCLK_Div \
    ((uint8_t(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Get_BCLK_Div])
#define RomDriver_GLB_Get_HCLK_Div \
    ((uint8_t(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Get_HCLK_Div])
#define RomDriver_Update_SystemCoreClockWith_XTAL \
    ((BL_Err_Type(*)(GLB_DLL_XTAL_Type xtalType))ROM_APITABLE[ROM_API_INDEX_Update_SystemCoreClockWith_XTAL])
#define RomDriver_GLB_Set_System_CLK \
    ((BL_Err_Type(*)(GLB_DLL_XTAL_Type xtalType, GLB_SYS_CLK_Type clkFreq))ROM_APITABLE[ROM_API_INDEX_GLB_Set_System_CLK])
#define RomDriver_System_Core_Clock_Update_From_RC32M \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_System_Core_Clock_Update_From_RC32M])
#define RomDriver_GLB_Set_SF_CLK \
    ((BL_Err_Type(*)(uint8_t enable, GLB_SFLASH_CLK_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_SF_CLK])
#define RomDriver_GLB_Power_Off_DLL \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Power_Off_DLL])
#define RomDriver_GLB_Power_On_DLL \
    ((BL_Err_Type(*)(GLB_DLL_XTAL_Type xtalType))ROM_APITABLE[ROM_API_INDEX_GLB_Power_On_DLL])
#define RomDriver_GLB_Enable_DLL_All_Clks \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Enable_DLL_All_Clks])
#define RomDriver_GLB_Enable_DLL_Clk \
    ((BL_Err_Type(*)(GLB_DLL_CLK_Type dllClk))ROM_APITABLE[ROM_API_INDEX_GLB_Enable_DLL_Clk])
#define RomDriver_GLB_Disable_DLL_All_Clks \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Disable_DLL_All_Clks])
#define RomDriver_GLB_Disable_DLL_Clk \
    ((BL_Err_Type(*)(GLB_DLL_CLK_Type dllClk))ROM_APITABLE[ROM_API_INDEX_GLB_Disable_DLL_Clk])
#define RomDriver_GLB_SW_System_Reset \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_SW_System_Reset])
#define RomDriver_GLB_SW_CPU_Reset \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_SW_CPU_Reset])
#define RomDriver_GLB_SW_POR_Reset \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_SW_POR_Reset])
#define RomDriver_GLB_Select_Internal_Flash \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Select_Internal_Flash])
#define RomDriver_GLB_Swap_Flash_Pin \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Swap_Flash_Pin])
#define RomDriver_GLB_Swap_Flash_CS_IO2_Pin \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Swap_Flash_CS_IO2_Pin])
#define RomDriver_GLB_Swap_Flash_IO0_IO3_Pin \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Swap_Flash_IO0_IO3_Pin])
#define RomDriver_GLB_Select_Internal_PSram \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Select_Internal_PSram])
#define RomDriver_GLB_GPIO_Init \
    ((BL_Err_Type(*)(GLB_GPIO_Cfg_Type * cfg)) ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Init])
#define RomDriver_GLB_GPIO_OUTPUT_Enable \
    ((BL_Err_Type(*)(GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_OUTPUT_Enable])
#define RomDriver_GLB_GPIO_OUTPUT_Disable \
    ((BL_Err_Type(*)(GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_OUTPUT_Disable])
#define RomDriver_GLB_GPIO_Set_HZ \
    ((BL_Err_Type(*)(GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Set_HZ])
#define RomDriver_GLB_Deswap_Flash_Pin \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Deswap_Flash_Pin])
#define RomDriver_GLB_Select_External_Flash \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_GLB_Select_External_Flash])
#define RomDriver_GLB_GPIO_Get_Fun \
    ((uint8_t(*)(GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Get_Fun])

#define RomDriver_EF_Ctrl_Busy \
    ((BL_Sts_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Busy])
#define RomDriver_EF_Ctrl_Sw_AHB_Clk_0 \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Sw_AHB_Clk_0])
#define RomDriver_EF_Ctrl_Load_Efuse_R0 \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Load_Efuse_R0])
#define RomDriver_EF_Ctrl_Clear \
    ((void (*)(uint32_t index, uint32_t len))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Clear])
#define RomDriver_EF_Ctrl_Get_Trim_Parity \
    ((uint8_t(*)(uint32_t val, uint8_t len))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Get_Trim_Parity])
#define RomDriver_EF_Ctrl_Read_RC32K_Trim \
    ((void (*)(Efuse_Ana_RC32K_Trim_Type * trim)) ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_RC32K_Trim])
#define RomDriver_EF_Ctrl_Read_RC32M_Trim \
    ((void (*)(Efuse_Ana_RC32M_Trim_Type * trim)) ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_RC32M_Trim])

#define RomDriver_PDS_Trim_RC32M \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_PDS_Trim_RC32M])
#define RomDriver_PDS_Select_RC32M_As_PLL_Ref \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_PDS_Select_RC32M_As_PLL_Ref])
#define RomDriver_PDS_Select_XTAL_As_PLL_Ref \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_PDS_Select_XTAL_As_PLL_Ref])
#define RomDriver_PDS_Power_On_PLL \
    ((BL_Err_Type(*)(PDS_PLL_XTAL_Type xtalType))ROM_APITABLE[ROM_API_INDEX_PDS_Power_On_PLL])
#define RomDriver_PDS_Enable_PLL_All_Clks \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_PDS_Enable_PLL_All_Clks])
#define RomDriver_PDS_Disable_PLL_All_Clks \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_PDS_Disable_PLL_All_Clks])
#define RomDriver_PDS_Enable_PLL_Clk \
    ((BL_Err_Type(*)(PDS_PLL_CLK_Type pllClk))ROM_APITABLE[ROM_API_INDEX_PDS_Enable_PLL_Clk])
#define RomDriver_PDS_Disable_PLL_Clk \
    ((BL_Err_Type(*)(PDS_PLL_CLK_Type pllClk))ROM_APITABLE[ROM_API_INDEX_PDS_Disable_PLL_Clk])
#define RomDriver_PDS_Power_Off_PLL \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_PDS_Power_Off_PLL])
#define RomDriver_PDS_Reset \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_PDS_Reset])
#define RomDriver_PDS_Enable \
    ((void (*)(PDS_CFG_Type * cfg, uint32_t pdsSleepCnt)) ROM_APITABLE[ROM_API_INDEX_PDS_Enable])
#define RomDriver_PDS_Auto_Time_Config \
    ((void (*)(uint32_t sleepDuration))ROM_APITABLE[ROM_API_INDEX_PDS_Auto_Time_Config])
#define RomDriver_PDS_Auto_Enable \
    ((void (*)(PDS_AUTO_POWER_DOWN_CFG_Type * powerCfg, PDS_AUTO_NORMAL_CFG_Type * normalCfg, BL_Fun_Type enable)) ROM_APITABLE[ROM_API_INDEX_PDS_Auto_Enable])
#define RomDriver_PDS_Manual_Force_Turn_Off \
    ((void (*)(PDS_FORCE_Type domain))ROM_APITABLE[ROM_API_INDEX_PDS_Manual_Force_Turn_Off])
#define RomDriver_PDS_Manual_Force_Turn_On \
    ((void (*)(PDS_FORCE_Type domain))ROM_APITABLE[ROM_API_INDEX_PDS_Manual_Force_Turn_On])

#define RomDriver_HBN_Enable \
    ((void (*)(uint8_t aGPIOIeCfg, HBN_LDO_LEVEL_Type ldoLevel, HBN_LEVEL_Type hbnLevel))ROM_APITABLE[ROM_API_INDEX_HBN_Enable])
#define RomDriver_HBN_Reset \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_HBN_Reset])
#define RomDriver_HBN_GPIO_Dbg_Pull_Cfg \
    ((BL_Err_Type(*)(BL_Fun_Type pupdEn, BL_Fun_Type dlyEn, uint8_t dlySec, HBN_INT_Type gpioIrq, BL_Mask_Type gpioMask))ROM_APITABLE[ROM_API_INDEX_HBN_GPIO_Dbg_Pull_Cfg])
#define RomDriver_HBN_Trim_RC32K \
    ((BL_Err_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_HBN_Trim_RC32K])
#define RomDriver_HBN_Set_ROOT_CLK_Sel \
    ((BL_Err_Type(*)(HBN_ROOT_CLK_Type rootClk))ROM_APITABLE[ROM_API_INDEX_HBN_Set_ROOT_CLK_Sel])

#define RomDriver_XIP_SFlash_State_Save \
    ((int(*)(spi_flash_cfg_type * pFlashCfg, uint32_t * offset)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_State_Save])
#define RomDriver_XIP_SFlash_State_Restore \
    ((int(*)(spi_flash_cfg_type * pFlashCfg, uint8_t ioMode, uint32_t offset)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_State_Restore])
#define RomDriver_XIP_SFlash_Erase_Need_Lock \
    ((int(*)(spi_flash_cfg_type * pFlashCfg, uint8_t ioMode, uint32_t startaddr, uint32_t endaddr)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Erase_Need_Lock])
#define RomDriver_XIP_SFlash_Write_Need_Lock \
    ((int(*)(spi_flash_cfg_type * pFlashCfg, uint8_t ioMode, uint32_t addr, uint8_t * data, uint32_t len)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Write_Need_Lock])
#define RomDriver_XIP_SFlash_Read_Need_Lock \
    ((int(*)(spi_flash_cfg_type * pFlashCfg, uint8_t ioMode, uint32_t addr, uint8_t * data, uint32_t len)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Read_Need_Lock])
#define RomDriver_XIP_SFlash_GetJedecId_Need_Lock \
    ((int(*)(spi_flash_cfg_type * pFlashCfg, uint8_t ioMode, uint8_t * data)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_GetJedecId_Need_Lock])
#define RomDriver_XIP_SFlash_GetDeviceId_Need_Lock \
    ((int(*)(spi_flash_cfg_type * pFlashCfg, uint8_t ioMode, uint8_t * data)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_GetDeviceId_Need_Lock])
#define RomDriver_XIP_SFlash_GetUniqueId_Need_Lock \
    ((int(*)(spi_flash_cfg_type * pFlashCfg, uint8_t ioMode, uint8_t * data, uint8_t idLen)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_GetUniqueId_Need_Lock])
#define RomDriver_XIP_SFlash_Read_Via_Cache_Need_Lock \
    ((int(*)(uint32_t addr, uint8_t * data, uint32_t len)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Read_Via_Cache_Need_Lock])
#define RomDriver_XIP_SFlash_Read_With_Lock \
    ((int (*)(spi_flash_cfg_type * pFlashCfg, uint8_t ioMode, uint32_t addr, uint8_t * dst, int len)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Read_With_Lock])
#define RomDriver_XIP_SFlash_Write_With_Lock \
    ((int (*)(spi_flash_cfg_type * pFlashCfg, uint8_t ioMode, uint32_t addr, uint8_t * src, int len)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Write_With_Lock])
#define RomDriver_XIP_SFlash_Erase_With_Lock \
    ((int (*)(spi_flash_cfg_type * pFlashCfg, uint8_t ioMode, uint32_t addr, int len)) ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Erase_With_Lock])

#define RomDriver_SFlash_Init \
    ((void (*)(const struct sf_ctrl_cfg_type *pSfCtrlCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Init])
#define RomDriver_SFlash_SetSPIMode \
    ((int(*)(uint8_t mode))ROM_APITABLE[ROM_API_INDEX_SFlash_SetSPIMode])
#define RomDriver_SFlash_Read_Reg \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint8_t regIndex, uint8_t * regValue, uint8_t regLen)) ROM_APITABLE[ROM_API_INDEX_SFlash_Read_Reg])
#define RomDriver_SFlash_Write_Reg \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint8_t regIndex, uint8_t * regValue, uint8_t regLen)) ROM_APITABLE[ROM_API_INDEX_SFlash_Write_Reg])
#define RomDriver_SFlash_Read_Reg_With_Cmd \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint8_t readRegCmd, uint8_t * regValue, uint8_t regLen)) ROM_APITABLE[ROM_API_INDEX_SFlash_Read_Reg_With_Cmd])
#define RomDriver_SFlash_Write_Reg_With_Cmd \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint8_t writeRegCmd, uint8_t * regValue, uint8_t regLen)) ROM_APITABLE[ROM_API_INDEX_SFlash_Write_Reg_With_Cmd])
#define RomDriver_SFlash_Busy \
    ((int(*)(spi_flash_cfg_type * flashCfg)) ROM_APITABLE[ROM_API_INDEX_SFlash_Busy])
#define RomDriver_SFlash_Write_Enable \
    ((int(*)(spi_flash_cfg_type * flashCfg)) ROM_APITABLE[ROM_API_INDEX_SFlash_Write_Enable])
#define RomDriver_SFlash_Qspi_Enable \
    ((int(*)(spi_flash_cfg_type * flashCfg)) ROM_APITABLE[ROM_API_INDEX_SFlash_Qspi_Enable])
#define RomDriver_SFlash_Volatile_Reg_Write_Enable \
    ((void (*)(spi_flash_cfg_type * flashCfg)) ROM_APITABLE[ROM_API_INDEX_SFlash_Volatile_Reg_Write_Enable])
#define RomDriver_SFlash_Chip_Erase \
    ((int(*)(spi_flash_cfg_type * flashCfg)) ROM_APITABLE[ROM_API_INDEX_SFlash_Chip_Erase])
#define RomDriver_SFlash_Sector_Erase \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint32_t secNum)) ROM_APITABLE[ROM_API_INDEX_SFlash_Sector_Erase])
#define RomDriver_SFlash_Blk32_Erase \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint32_t blkNum)) ROM_APITABLE[ROM_API_INDEX_SFlash_Blk32_Erase])
#define RomDriver_SFlash_Blk64_Erase \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint32_t blkNum)) ROM_APITABLE[ROM_API_INDEX_SFlash_Blk64_Erase])
#define RomDriver_SFlash_Erase \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint32_t startaddr, uint32_t endaddr)) ROM_APITABLE[ROM_API_INDEX_SFlash_Erase])
#define RomDriver_SFlash_Program \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint8_t ioMode, uint32_t addr, uint8_t * data, uint32_t len)) ROM_APITABLE[ROM_API_INDEX_SFlash_Program])
#define RomDriver_SFlash_GetUniqueId \
    ((void (*)(uint8_t * data, uint8_t idLen)) ROM_APITABLE[ROM_API_INDEX_SFlash_GetUniqueId])
#define RomDriver_SFlash_GetJedecId \
    ((void (*)(spi_flash_cfg_type * flashCfg, uint8_t * data)) ROM_APITABLE[ROM_API_INDEX_SFlash_GetJedecId])
#define RomDriver_SFlash_GetDeviceId \
    ((void (*)(uint8_t * data)) ROM_APITABLE[ROM_API_INDEX_SFlash_GetDeviceId])
#define RomDriver_SFlash_Powerdown \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_SFlash_Powerdown])
#define RomDriver_SFlash_Releae_Powerdown \
    ((void (*)(spi_flash_cfg_type * flashCfg)) ROM_APITABLE[ROM_API_INDEX_SFlash_Releae_Powerdown])
#define RomDriver_SFlash_Restore_From_Powerdown \
    ((int(*)(spi_flash_cfg_type * pFlashCfg, uint8_t flashcont_read)) ROM_APITABLE[ROM_API_INDEX_SFlash_Restore_From_Powerdown])
#define RomDriver_SFlash_SetBurstWrap \
    ((void (*)(spi_flash_cfg_type * flashCfg)) ROM_APITABLE[ROM_API_INDEX_SFlash_SetBurstWrap])
#define RomDriver_SFlash_DisableBurstWrap \
    ((void (*)(spi_flash_cfg_type * flashCfg)) ROM_APITABLE[ROM_API_INDEX_SFlash_DisableBurstWrap])
#define RomDriver_SFlash_Software_Reset \
    ((int(*)(spi_flash_cfg_type * flashCfg)) ROM_APITABLE[ROM_API_INDEX_SFlash_Software_Reset])
#define RomDriver_SFlash_Reset_Continue_Read \
    ((void (*)(spi_flash_cfg_type * flashCfg)) ROM_APITABLE[ROM_API_INDEX_SFlash_Reset_Continue_Read])
#define RomDriver_SFlash_Set_IDbus_Cfg \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint8_t ioMode, uint8_t cont_read, uint32_t addr, uint32_t len)) ROM_APITABLE[ROM_API_INDEX_SFlash_Set_IDbus_Cfg])
#define RomDriver_SFlash_IDbus_Read_Enable \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint8_t ioMode, uint8_t cont_read)) ROM_APITABLE[ROM_API_INDEX_SFlash_IDbus_Read_Enable])
#define RomDriver_SFlash_Cache_Read_Enable \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint8_t ioMode, uint8_t cont_read, uint8_t wayDisable)) ROM_APITABLE[ROM_API_INDEX_SFlash_Cache_Read_Enable])
#define RomDriver_SFlash_Cache_Read_Disable \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_SFlash_Cache_Read_Disable])
#define RomDriver_SFlash_Read \
    ((int(*)(spi_flash_cfg_type * flashCfg, uint8_t ioMode, uint8_t cont_read, uint32_t addr, uint8_t * data, uint32_t len)) ROM_APITABLE[ROM_API_INDEX_SFlash_Read])

#define RomDriver_L1C_Cache_Enable_Set \
    ((BL_Err_Type(*)(uint8_t wayDisable))ROM_APITABLE[ROM_API_INDEX_L1C_Cache_Enable_Set])
#define RomDriver_L1C_Cache_Write_Set \
    ((void (*)(BL_Fun_Type wtEn, BL_Fun_Type wbEn, BL_Fun_Type waEn))ROM_APITABLE[ROM_API_INDEX_L1C_Cache_Write_Set])
#define RomDriver_L1C_Cache_Flush \
    ((BL_Err_Type(*)(uint8_t wayDisable))ROM_APITABLE[ROM_API_INDEX_L1C_Cache_Flush])
#define RomDriver_L1C_Cache_Hit_Count_Get \
    ((void (*)(uint32_t * hitCountLow, uint32_t * hitCountHigh)) ROM_APITABLE[ROM_API_INDEX_L1C_Cache_Hit_Count_Get])
#define RomDriver_L1C_Cache_Miss_Count_Get \
    ((uint32_t(*)(void))ROM_APITABLE[ROM_API_INDEX_L1C_Cache_Miss_Count_Get])
#define RomDriver_L1C_Cache_Read_Disable \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_L1C_Cache_Read_Disable])
#define RomDriver_L1C_Set_Wrap \
    ((BL_Err_Type(*)(BL_Fun_Type wrap))ROM_APITABLE[ROM_API_INDEX_L1C_Set_Wrap])
#define RomDriver_L1C_Set_Way_Disable \
    ((BL_Err_Type(*)(uint8_t disableVal))ROM_APITABLE[ROM_API_INDEX_L1C_Set_Way_Disable])
#define RomDriver_L1C_IROM_2T_Access_Set \
    ((BL_Err_Type(*)(uint8_t enable))ROM_APITABLE[ROM_API_INDEX_L1C_IROM_2T_Access_Set])

#define RomDriver_SF_Ctrl_Enable \
    ((void (*)(const struct sf_ctrl_cfg_type *cfg))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Enable])
#define RomDriver_SF_Ctrl_Psram_Init \
    ((void (*)(struct sf_ctrl_psram_cfg * sfCtrlPsramCfg)) ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Psram_Init])
#define RomDriver_SF_Ctrl_Get_Clock_Delay \
    ((uint8_t(*)(void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Get_Clock_Delay])
#define RomDriver_SF_Ctrl_Set_Clock_Delay \
    ((void (*)(uint8_t delay))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Set_Clock_Delay])
#define RomDriver_SF_Ctrl_Cmds_Set \
    ((void (*)(struct sf_ctrl_cmds_cfg * cmdsCfg)) ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Cmds_Set])
#define RomDriver_SF_Ctrl_Set_Owner \
    ((void (*)(uint8_t owner))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Set_Owner])
#define RomDriver_SF_Ctrl_Disable \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Disable])
#define RomDriver_SF_Ctrl_Select_Pad \
    ((void (*)(uint8_t sel))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Select_Pad])
#define RomDriver_SF_Ctrl_Select_Bank \
    ((void (*)(uint8_t sel))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Select_Bank])
#define RomDriver_SF_Ctrl_AES_Enable_BE \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Enable_BE])
#define RomDriver_SF_Ctrl_AES_Enable_LE \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Enable_LE])
#define RomDriver_SF_Ctrl_AES_Set_Region \
    ((void (*)(uint8_t region, uint8_t enable, uint8_t hwKey, uint32_t startAddr, uint32_t endAddr, uint8_t locked))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_Region])
#define RomDriver_SF_Ctrl_AES_Set_Key \
    ((void (*)(uint8_t region, uint8_t * key, uint8_t keyType)) ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_Key])
#define RomDriver_SF_Ctrl_AES_Set_Key_BE \
    ((void (*)(uint8_t region, uint8_t * key, uint8_t keyType)) ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_Key_BE])
#define RomDriver_SF_Ctrl_AES_Set_IV \
    ((void (*)(uint8_t region, uint8_t * iv, uint32_t addrOffset)) ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_IV])
#define RomDriver_SF_Ctrl_AES_Set_IV_BE \
    ((void (*)(uint8_t region, uint8_t * iv, uint32_t addrOffset)) ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_IV_BE])
#define RomDriver_SF_Ctrl_AES_Enable \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Enable])
#define RomDriver_SF_Ctrl_AES_Disable \
    ((void (*)(void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Disable])
#define RomDriver_SF_Ctrl_Is_AES_Enable \
    ((uint8_t(*)(void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Is_AES_Enable])
#define RomDriver_SF_Ctrl_Set_Flash_Image_Offset \
    ((void (*)(uint32_t addrOffset))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Set_Flash_Image_Offset])
#define RomDriver_SF_Ctrl_Get_Flash_Image_Offset \
    ((uint32_t(*)(void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Get_Flash_Image_Offset])
#define RomDriver_SF_Ctrl_Select_Clock \
    ((void (*)(uint8_t sahbType))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Select_Clock])
#define RomDriver_SF_Ctrl_SendCmd \
    ((void (*)(struct sf_ctrl_cmd_cfg_type * cfg)) ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_SendCmd])
#define RomDriver_SF_Ctrl_Flash_Read_Icache_Set \
    ((void (*)(struct sf_ctrl_cmd_cfg_type * cfg, uint8_t cmdValid)) ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Flash_Read_Icache_Set])
#define RomDriver_SF_Ctrl_Psram_Write_Icache_Set \
    ((void (*)(struct sf_ctrl_cmd_cfg_type * cfg, uint8_t cmdValid)) ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Psram_Write_Icache_Set])
#define RomDriver_SF_Ctrl_Psram_Read_Icache_Set \
    ((void (*)(struct sf_ctrl_cmd_cfg_type * cfg, uint8_t cmdValid)) ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Psram_Read_Icache_Set])
#define RomDriver_SF_Ctrl_GetBusyState \
    ((BL_Sts_Type(*)(void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_GetBusyState])
#define RomDriver_SF_Cfg_Deinit_Ext_Flash_Gpio \
    ((int (*)(uint8_t extFlashPin))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Deinit_Ext_Flash_Gpio])
#define RomDriver_SF_Cfg_Init_Ext_Flash_Gpio \
    ((void (*)(uint8_t extFlashPin))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Init_Ext_Flash_Gpio])
#define RomDriver_SF_Cfg_Get_Flash_Cfg_Need_Lock \
    ((BL_Err_Type(*)(uint32_t flashID, spi_flash_cfg_type * pFlashCfg)) ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Get_Flash_Cfg_Need_Lock])
#define RomDriver_SF_Cfg_Init_Flash_Gpio \
    ((void (*)(uint8_t flashPinCfg, uint8_t restoreDefault))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Init_Flash_Gpio])
#define RomDriver_SF_Cfg_Flash_Identify \
    ((uint32_t(*)(uint8_t callFromFlash, uint32_t autoScan, uint32_t flashPinCfg, uint8_t restoreDefault, spi_flash_cfg_type * pFlashCfg)) ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Flash_Identify])

#define RomDriver_Psram_Init \
    ((void (*)(struct spi_psram_cfg_type * psramCfg, struct sf_ctrl_cmds_cfg * cmdsCfg, struct sf_ctrl_psram_cfg * sfCtrlPsramCfg)) ROM_APITABLE[ROM_API_INDEX_Psram_Init])
#define RomDriver_Psram_ReadReg \
    ((void (*)(struct spi_psram_cfg_type * psramCfg, uint8_t * regValue)) ROM_APITABLE[ROM_API_INDEX_Psram_ReadReg])
#define RomDriver_Psram_WriteReg \
    ((void (*)(struct spi_psram_cfg_type * psramCfg, uint8_t * regValue)) ROM_APITABLE[ROM_API_INDEX_Psram_WriteReg])
#define RomDriver_Psram_SetDriveStrength \
    ((int(*)(struct spi_psram_cfg_type * psramCfg)) ROM_APITABLE[ROM_API_INDEX_Psram_SetDriveStrength])
#define RomDriver_Psram_SetBurstWrap \
    ((int(*)(struct spi_psram_cfg_type * psramCfg)) ROM_APITABLE[ROM_API_INDEX_Psram_SetBurstWrap])
#define RomDriver_Psram_ReadId \
    ((void (*)(struct spi_psram_cfg_type * psramCfg, uint8_t * data)) ROM_APITABLE[ROM_API_INDEX_Psram_ReadId])
#define RomDriver_Psram_EnterQuadMode \
    ((int(*)(struct spi_psram_cfg_type * psramCfg)) ROM_APITABLE[ROM_API_INDEX_Psram_EnterQuadMode])
#define RomDriver_Psram_ExitQuadMode \
    ((int(*)(struct spi_psram_cfg_type * psramCfg)) ROM_APITABLE[ROM_API_INDEX_Psram_ExitQuadMode])
#define RomDriver_Psram_ToggleBurstLength \
    ((int(*)(struct spi_psram_cfg_type * psramCfg, uint8_t ctrlMode)) ROM_APITABLE[ROM_API_INDEX_Psram_ToggleBurstLength])
#define RomDriver_Psram_SoftwareReset \
    ((int(*)(struct spi_psram_cfg_type * psramCfg, uint8_t ctrlMode)) ROM_APITABLE[ROM_API_INDEX_Psram_SoftwareReset])
#define RomDriver_Psram_Set_IDbus_Cfg \
    ((int(*)(struct spi_psram_cfg_type * psramCfg, uint8_t ioMode, uint32_t addr, uint32_t len)) ROM_APITABLE[ROM_API_INDEX_Psram_Set_IDbus_Cfg])
#define RomDriver_Psram_Cache_Write_Set \
    ((int(*)(struct spi_psram_cfg_type * psramCfg, uint8_t ioMode, uint8_t wtEn, uint8_t wbEn, uint8_t waEn)) ROM_APITABLE[ROM_API_INDEX_Psram_Cache_Write_Set])
#define RomDriver_Psram_Write \
    ((int(*)(struct spi_psram_cfg_type * psramCfg, uint8_t ioMode, uint32_t addr, uint8_t * data, uint32_t len)) ROM_APITABLE[ROM_API_INDEX_Psram_Write])
#define RomDriver_Psram_Read \
    ((int(*)(struct spi_psram_cfg_type * psramCfg, uint8_t ioMode, uint32_t addr, uint8_t * data, uint32_t len)) ROM_APITABLE[ROM_API_INDEX_Psram_Read])
/*@} end of group ROMDRIVER_Public_Types */

/** @defgroup  ROMDRIVER_Public_Constants
 *  @{
 */

/*@} end of group ROMDRIVER_Public_Constants */

/** @defgroup  ROMDRIVER_Public_Macros
 *  @{
 */

/*@} end of group ROMDRIVER_Public_Macros */

/** @defgroup  ROMDRIVER_Public_Functions
 *  @{
 */

/*@} end of group ROMDRIVER_Public_Functions */

/*@} end of group ROMDRIVER */

/*@} end of group BL702_Peripheral_Driver */

#endif /* __BL702_ROMDRIVER_H__ */
