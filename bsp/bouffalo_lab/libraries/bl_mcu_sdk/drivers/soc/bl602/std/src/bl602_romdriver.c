/**
  ******************************************************************************
  * @file    bl602_romdriver.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
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

#include "bl602_romdriver.h"
#include <string.h>

/** @addtogroup  BL602_Periph_Driver
 *  @{
 */

/** @defgroup ROMDRIVER
 *  @brief ROMDRIVER common functions
 *  @{
 */

/** @defgroup ROMDRIVER_Private_Type
 *  @{
 */

/*@} end of group ROMDRIVER_Private_Type*/

/** @defgroup ROMDRIVER_Private_Defines
 *  @{
 */

/*@} end of group ROMDRIVER_Private_Defines */

/** @defgroup ROMDRIVER_Private_Variables
 *  @{
 */

/*@} end of group ROMDRIVER_Private_Variables */

/** @defgroup ROMDRIVER_Global_Variables
 *  @{
 */

uint32_t const romDriverTable[] = {
    0x06020002,
    0x00000000,
    0x00000000,
    0x00000000,

    [ROM_API_INDEX_AON_Power_On_MBG] = (uint32_t)AON_Power_On_MBG,
    [ROM_API_INDEX_AON_Power_Off_MBG] = (uint32_t)AON_Power_Off_MBG,
    [ROM_API_INDEX_AON_Power_On_XTAL] = (uint32_t)AON_Power_On_XTAL,
    [ROM_API_INDEX_AON_Set_Xtal_CapCode] = (uint32_t)AON_Set_Xtal_CapCode,
    [ROM_API_INDEX_AON_Get_Xtal_CapCode] = (uint32_t)AON_Get_Xtal_CapCode,
    [ROM_API_INDEX_AON_Power_Off_XTAL] = (uint32_t)AON_Power_Off_XTAL,
    [ROM_API_INDEX_AON_Power_On_BG] = (uint32_t)AON_Power_On_BG,
    [ROM_API_INDEX_AON_Power_Off_BG] = (uint32_t)AON_Power_Off_BG,
    [ROM_API_INDEX_AON_Power_On_LDO11_SOC] = (uint32_t)AON_Power_On_LDO11_SOC,
    [ROM_API_INDEX_AON_Power_Off_LDO11_SOC] = (uint32_t)AON_Power_Off_LDO11_SOC,
    [ROM_API_INDEX_AON_Power_On_LDO15_RF] = (uint32_t)AON_Power_On_LDO15_RF,
    [ROM_API_INDEX_AON_Power_Off_LDO15_RF] = (uint32_t)AON_Power_Off_LDO15_RF,
    [ROM_API_INDEX_AON_Power_On_SFReg] = (uint32_t)AON_Power_On_SFReg,
    [ROM_API_INDEX_AON_Power_Off_SFReg] = (uint32_t)AON_Power_Off_SFReg,
    [ROM_API_INDEX_AON_LowPower_Enter_PDS0] = (uint32_t)AON_LowPower_Enter_PDS0,
    [ROM_API_INDEX_AON_LowPower_Exit_PDS0] = (uint32_t)AON_LowPower_Exit_PDS0,

    [ROM_API_INDEX_ASM_Delay_Us] = (uint32_t)ASM_Delay_Us,

    [ROM_API_INDEX_BL602_Delay_US] = (uint32_t)BL602_Delay_US,
    [ROM_API_INDEX_BL602_Delay_MS] = (uint32_t)BL602_Delay_MS,
    [ROM_API_INDEX_BL602_MemCpy] = (uint32_t)BL602_MemCpy,
    [ROM_API_INDEX_BL602_MemCpy4] = (uint32_t)BL602_MemCpy4,
    [ROM_API_INDEX_BL602_MemCpy_Fast] = (uint32_t)BL602_MemCpy_Fast,
    [ROM_API_INDEX_BL602_MemSet] = (uint32_t)BL602_MemSet,
    [ROM_API_INDEX_BL602_MemSet4] = (uint32_t)BL602_MemSet4,
    [ROM_API_INDEX_BL602_MemCmp] = (uint32_t)BL602_MemCmp,

    [ROM_API_INDEX_EF_Ctrl_Sw_AHB_Clk_0] = (uint32_t)EF_Ctrl_Sw_AHB_Clk_0,
    [ROM_API_INDEX_EF_Ctrl_Program_Efuse_0] = (uint32_t)EF_Ctrl_Program_Efuse_0,
    [ROM_API_INDEX_EF_Ctrl_Load_Efuse_R0] = (uint32_t)EF_Ctrl_Load_Efuse_R0,
    [ROM_API_INDEX_EF_Ctrl_Busy] = (uint32_t)EF_Ctrl_Busy,
    [ROM_API_INDEX_EF_Ctrl_AutoLoad_Done] = (uint32_t)EF_Ctrl_AutoLoad_Done,
    [ROM_API_INDEX_EF_Ctrl_Get_Trim_Parity] = (uint32_t)EF_Ctrl_Get_Trim_Parity,
    [ROM_API_INDEX_EF_Ctrl_Read_RC32M_Trim] = (uint32_t)EF_Ctrl_Read_RC32M_Trim,
    [ROM_API_INDEX_EF_Ctrl_Read_RC32K_Trim] = (uint32_t)EF_Ctrl_Read_RC32K_Trim,
    [ROM_API_INDEX_EF_Ctrl_Clear] = (uint32_t)EF_Ctrl_Clear,

    [ROM_API_INDEX_GLB_Get_Root_CLK_Sel] = (uint32_t)GLB_Get_Root_CLK_Sel,
    [ROM_API_INDEX_GLB_Set_System_CLK_Div] = (uint32_t)GLB_Set_System_CLK_Div,
    [ROM_API_INDEX_GLB_Get_BCLK_Div] = (uint32_t)GLB_Get_BCLK_Div,
    [ROM_API_INDEX_GLB_Get_HCLK_Div] = (uint32_t)GLB_Get_HCLK_Div,

    [ROM_API_INDEX_Update_SystemCoreClockWith_XTAL] = (uint32_t)Update_SystemCoreClockWith_XTAL,

    [ROM_API_INDEX_GLB_Set_System_CLK] = (uint32_t)GLB_Set_System_CLK,

    [ROM_API_INDEX_System_Core_Clock_Update_From_RC32M] = (uint32_t)System_Core_Clock_Update_From_RC32M,

    [ROM_API_INDEX_GLB_Set_SF_CLK] = (uint32_t)GLB_Set_SF_CLK,
    [ROM_API_INDEX_GLB_Set_PKA_CLK_Sel] = (uint32_t)GLB_Set_PKA_CLK_Sel,
    [ROM_API_INDEX_GLB_SW_System_Reset] = (uint32_t)GLB_SW_System_Reset,
    [ROM_API_INDEX_GLB_SW_CPU_Reset] = (uint32_t)GLB_SW_CPU_Reset,
    [ROM_API_INDEX_GLB_SW_POR_Reset] = (uint32_t)GLB_SW_POR_Reset,
    [ROM_API_INDEX_GLB_Select_Internal_Flash] = (uint32_t)GLB_Select_Internal_Flash,
    [ROM_API_INDEX_GLB_Select_External_Flash] = (uint32_t)GLB_Select_External_Flash,
    [ROM_API_INDEX_GLB_Deswap_Flash_Pin] = (uint32_t)GLB_Deswap_Flash_Pin,
    [ROM_API_INDEX_GLB_Swap_Flash_Pin] = (uint32_t)GLB_Swap_Flash_Pin,
    [ROM_API_INDEX_GLB_GPIO_Init] = (uint32_t)GLB_GPIO_Init,
    [ROM_API_INDEX_GLB_GPIO_OUTPUT_Enable] = (uint32_t)GLB_GPIO_OUTPUT_Enable,
    [ROM_API_INDEX_GLB_GPIO_OUTPUT_Disable] = (uint32_t)GLB_GPIO_OUTPUT_Disable,
    [ROM_API_INDEX_GLB_GPIO_Set_HZ] = (uint32_t)GLB_GPIO_Set_HZ,
    [ROM_API_INDEX_GLB_GPIO_Get_Fun] = (uint32_t)GLB_GPIO_Get_Fun,

    [ROM_API_INDEX_HBN_Mode_Enter] = (uint32_t)HBN_Mode_Enter,
    [ROM_API_INDEX_HBN_Power_Down_Flash] = (uint32_t)HBN_Power_Down_Flash,
    [ROM_API_INDEX_HBN_Enable] = (uint32_t)HBN_Enable,
    [ROM_API_INDEX_HBN_Reset] = (uint32_t)HBN_Reset,
    [ROM_API_INDEX_HBN_Set_Ldo11_Aon_Vout] = (uint32_t)HBN_Set_Ldo11_Aon_Vout,
    [ROM_API_INDEX_HBN_Set_Ldo11_Rt_Vout] = (uint32_t)HBN_Set_Ldo11_Rt_Vout,
    [ROM_API_INDEX_HBN_Set_Ldo11_Soc_Vout] = (uint32_t)HBN_Set_Ldo11_Soc_Vout,
    [ROM_API_INDEX_HBN_32K_Sel] = (uint32_t)HBN_32K_Sel,
    [ROM_API_INDEX_HBN_Set_ROOT_CLK_Sel] = (uint32_t)HBN_Set_ROOT_CLK_Sel,
    [ROM_API_INDEX_HBN_Power_On_Xtal_32K] = (uint32_t)HBN_Power_On_Xtal_32K,
    [ROM_API_INDEX_HBN_Power_Off_Xtal_32K] = (uint32_t)HBN_Power_Off_Xtal_32K,
    [ROM_API_INDEX_HBN_Power_On_RC32K] = (uint32_t)HBN_Power_On_RC32K,
    [ROM_API_INDEX_HBN_Power_Off_RC32K] = (uint32_t)HBN_Power_Off_RC32K,
    [ROM_API_INDEX_HBN_Trim_RC32K] = (uint32_t)HBN_Trim_RC32K,
    [ROM_API_INDEX_HBN_Hw_Pu_Pd_Cfg] = (uint32_t)HBN_Hw_Pu_Pd_Cfg,
    [ROM_API_INDEX_HBN_Pin_WakeUp_Mask] = (uint32_t)HBN_Pin_WakeUp_Mask,
    [ROM_API_INDEX_HBN_GPIO7_Dbg_Pull_Cfg] = (uint32_t)HBN_GPIO7_Dbg_Pull_Cfg,
    [ROM_API_INDEX_HBN_Set_Embedded_Flash_Pullup] = (uint32_t)HBN_Set_Embedded_Flash_Pullup,

    [ROM_API_INDEX_L1C_Set_Wrap] = (uint32_t)L1C_Set_Wrap,
    [ROM_API_INDEX_L1C_Set_Way_Disable] = (uint32_t)L1C_Set_Way_Disable,
    [ROM_API_INDEX_L1C_IROM_2T_Access_Set] = (uint32_t)L1C_IROM_2T_Access_Set,

    [ROM_API_INDEX_PDS_Reset] = (uint32_t)PDS_Reset,
    [ROM_API_INDEX_PDS_Enable] = (uint32_t)PDS_Enable,
    [ROM_API_INDEX_PDS_Force_Config] = (uint32_t)PDS_Force_Config,
    [ROM_API_INDEX_PDS_RAM_Config] = (uint32_t)PDS_RAM_Config,
    [ROM_API_INDEX_PDS_Default_Level_Config] = (uint32_t)PDS_Default_Level_Config,
    [ROM_API_INDEX_PDS_Trim_RC32M] = (uint32_t)PDS_Trim_RC32M,
    [ROM_API_INDEX_PDS_Select_RC32M_As_PLL_Ref] = (uint32_t)PDS_Select_RC32M_As_PLL_Ref,
    [ROM_API_INDEX_PDS_Select_XTAL_As_PLL_Ref] = (uint32_t)PDS_Select_XTAL_As_PLL_Ref,
    [ROM_API_INDEX_PDS_Power_On_PLL] = (uint32_t)PDS_Power_On_PLL,
    [ROM_API_INDEX_PDS_Enable_PLL_All_Clks] = (uint32_t)PDS_Enable_PLL_All_Clks,
    [ROM_API_INDEX_PDS_Disable_PLL_All_Clks] = (uint32_t)PDS_Disable_PLL_All_Clks,
    [ROM_API_INDEX_PDS_Enable_PLL_Clk] = (uint32_t)PDS_Enable_PLL_Clk,
    [ROM_API_INDEX_PDS_Disable_PLL_Clk] = (uint32_t)PDS_Disable_PLL_Clk,
    [ROM_API_INDEX_PDS_Power_Off_PLL] = (uint32_t)PDS_Power_Off_PLL,

    [ROM_API_INDEX_SEC_Eng_Turn_On_Sec_Ring] = (uint32_t)SEC_Eng_Turn_On_Sec_Ring,
    [ROM_API_INDEX_SEC_Eng_Turn_Off_Sec_Ring] = (uint32_t)SEC_Eng_Turn_Off_Sec_Ring,

    [ROM_API_INDEX_SFlash_Init] = (uint32_t)SFlash_Init,
    [ROM_API_INDEX_SFlash_SetSPIMode] = (uint32_t)SFlash_SetSPIMode,
    [ROM_API_INDEX_SFlash_Read_Reg] = (uint32_t)SFlash_Read_Reg,
    [ROM_API_INDEX_SFlash_Write_Reg] = (uint32_t)SFlash_Write_Reg,
    [ROM_API_INDEX_SFlash_Busy] = (uint32_t)SFlash_Busy,
    [ROM_API_INDEX_SFlash_Write_Enable] = (uint32_t)SFlash_Write_Enable,
    [ROM_API_INDEX_SFlash_Qspi_Enable] = (uint32_t)SFlash_Qspi_Enable,
    [ROM_API_INDEX_SFlash_Volatile_Reg_Write_Enable] = (uint32_t)SFlash_Volatile_Reg_Write_Enable,
    [ROM_API_INDEX_SFlash_Chip_Erase] = (uint32_t)SFlash_Chip_Erase,
    [ROM_API_INDEX_SFlash_Sector_Erase] = (uint32_t)SFlash_Sector_Erase,
    [ROM_API_INDEX_SFlash_Blk32_Erase] = (uint32_t)SFlash_Blk32_Erase,
    [ROM_API_INDEX_SFlash_Blk64_Erase] = (uint32_t)SFlash_Blk64_Erase,
    [ROM_API_INDEX_SFlash_Erase] = (uint32_t)SFlash_Erase,
    [ROM_API_INDEX_SFlash_Program] = (uint32_t)SFlash_Program,
    [ROM_API_INDEX_SFlash_GetUniqueId] = (uint32_t)SFlash_GetUniqueId,
    [ROM_API_INDEX_SFlash_GetJedecId] = (uint32_t)SFlash_GetJedecId,
    [ROM_API_INDEX_SFlash_GetDeviceId] = (uint32_t)SFlash_GetDeviceId,
    [ROM_API_INDEX_SFlash_Powerdown] = (uint32_t)SFlash_Powerdown,
    [ROM_API_INDEX_SFlash_Releae_Powerdown] = (uint32_t)SFlash_Releae_Powerdown,
    [ROM_API_INDEX_SFlash_SetBurstWrap] = (uint32_t)SFlash_SetBurstWrap,
    [ROM_API_INDEX_SFlash_DisableBurstWrap] = (uint32_t)SFlash_DisableBurstWrap,
    [ROM_API_INDEX_SFlash_Software_Reset] = (uint32_t)SFlash_Software_Reset,
    [ROM_API_INDEX_SFlash_Reset_Continue_Read] = (uint32_t)SFlash_Reset_Continue_Read,
    [ROM_API_INDEX_SFlash_Set_IDbus_Cfg] = (uint32_t)SFlash_Set_IDbus_Cfg,
    [ROM_API_INDEX_SFlash_IDbus_Read_Enable] = (uint32_t)SFlash_IDbus_Read_Enable,
    [ROM_API_INDEX_SFlash_Cache_Enable_Set] = (uint32_t)SFlash_Cache_Enable_Set,
    [ROM_API_INDEX_SFlash_Cache_Flush] = (uint32_t)SFlash_Cache_Flush,
    [ROM_API_INDEX_SFlash_Cache_Read_Enable] = (uint32_t)SFlash_Cache_Read_Enable,
    [ROM_API_INDEX_SFlash_Cache_Hit_Count_Get] = (uint32_t)SFlash_Cache_Hit_Count_Get,
    [ROM_API_INDEX_SFlash_Cache_Miss_Count_Get] = (uint32_t)SFlash_Cache_Miss_Count_Get,
    [ROM_API_INDEX_SFlash_Cache_Read_Disable] = (uint32_t)SFlash_Cache_Read_Disable,
    [ROM_API_INDEX_SFlash_Read] = (uint32_t)SFlash_Read,
    [ROM_API_INDEX_SFlash_Read_Reg_With_Cmd] = (uint32_t)SFlash_Read_Reg_With_Cmd,
    [ROM_API_INDEX_SFlash_Write_Reg_With_Cmd] = (uint32_t)SFlash_Write_Reg_With_Cmd,
    [ROM_API_INDEX_SFlash_Restore_From_Powerdown] = (uint32_t)SFlash_Restore_From_Powerdown,

    [ROM_API_INDEX_SF_Cfg_Init_Ext_Flash_Gpio] = (uint32_t)SF_Cfg_Init_Ext_Flash_Gpio,
    [ROM_API_INDEX_SF_Cfg_Init_Internal_Flash_Gpio] = (uint32_t)SF_Cfg_Init_Internal_Flash_Gpio,
    [ROM_API_INDEX_SF_Cfg_Deinit_Ext_Flash_Gpio] = (uint32_t)SF_Cfg_Deinit_Ext_Flash_Gpio,
    [ROM_API_INDEX_SF_Cfg_Restore_GPIO17_Fun] = (uint32_t)SF_Cfg_Restore_GPIO17_Fun,
    [ROM_API_INDEX_SF_Cfg_Get_Flash_Cfg_Need_Lock] = (uint32_t)SF_Cfg_Get_Flash_Cfg_Need_Lock,
    [ROM_API_INDEX_SF_Cfg_Init_Flash_Gpio] = (uint32_t)SF_Cfg_Init_Flash_Gpio,
    [ROM_API_INDEX_SF_Cfg_Flash_Identify] = (uint32_t)SF_Cfg_Flash_Identify,
    [ROM_API_INDEX_SF_Ctrl_Enable] = (uint32_t)SF_Ctrl_Enable,
    [ROM_API_INDEX_SF_Ctrl_Select_Pad] = (uint32_t)SF_Ctrl_Select_Pad,
    [ROM_API_INDEX_SF_Ctrl_Set_Owner] = (uint32_t)SF_Ctrl_Set_Owner,
    [ROM_API_INDEX_SF_Ctrl_Disable] = (uint32_t)SF_Ctrl_Disable,
    [ROM_API_INDEX_SF_Ctrl_AES_Enable_BE] = (uint32_t)SF_Ctrl_AES_Enable_BE,
    [ROM_API_INDEX_SF_Ctrl_AES_Enable_LE] = (uint32_t)SF_Ctrl_AES_Enable_LE,
    [ROM_API_INDEX_SF_Ctrl_AES_Set_Region] = (uint32_t)SF_Ctrl_AES_Set_Region,
    [ROM_API_INDEX_SF_Ctrl_AES_Set_Key] = (uint32_t)SF_Ctrl_AES_Set_Key,
    [ROM_API_INDEX_SF_Ctrl_AES_Set_Key_BE] = (uint32_t)SF_Ctrl_AES_Set_Key_BE,
    [ROM_API_INDEX_SF_Ctrl_AES_Set_IV] = (uint32_t)SF_Ctrl_AES_Set_IV,
    [ROM_API_INDEX_SF_Ctrl_AES_Set_IV_BE] = (uint32_t)SF_Ctrl_AES_Set_IV_BE,
    [ROM_API_INDEX_SF_Ctrl_AES_Enable] = (uint32_t)SF_Ctrl_AES_Enable,
    [ROM_API_INDEX_SF_Ctrl_AES_Disable] = (uint32_t)SF_Ctrl_AES_Disable,
    [ROM_API_INDEX_SF_Ctrl_Set_Flash_Image_Offset] = (uint32_t)SF_Ctrl_Set_Flash_Image_Offset,
    [ROM_API_INDEX_SF_Ctrl_Get_Flash_Image_Offset] = (uint32_t)SF_Ctrl_Get_Flash_Image_Offset,
    [ROM_API_INDEX_SF_Ctrl_Select_Clock] = (uint32_t)SF_Ctrl_Select_Clock,
    [ROM_API_INDEX_SF_Ctrl_SendCmd] = (uint32_t)SF_Ctrl_SendCmd,
    [ROM_API_INDEX_SF_Ctrl_Icache_Set] = (uint32_t)SF_Ctrl_Icache_Set,
    [ROM_API_INDEX_SF_Ctrl_Icache2_Set] = (uint32_t)SF_Ctrl_Icache2_Set,
    [ROM_API_INDEX_SF_Ctrl_GetBusyState] = (uint32_t)SF_Ctrl_GetBusyState,
    [ROM_API_INDEX_SF_Ctrl_Is_AES_Enable] = (uint32_t)SF_Ctrl_Is_AES_Enable,
    [ROM_API_INDEX_SF_Ctrl_Get_Clock_Delay] = (uint32_t)SF_Ctrl_Get_Clock_Delay,
    [ROM_API_INDEX_SF_Ctrl_Set_Clock_Delay] = (uint32_t)SF_Ctrl_Set_Clock_Delay,

    [ROM_API_INDEX_XIP_SFlash_State_Save] = (uint32_t)XIP_SFlash_State_Save,
    [ROM_API_INDEX_XIP_SFlash_State_Restore] = (uint32_t)XIP_SFlash_State_Restore,
    [ROM_API_INDEX_XIP_SFlash_Erase_Need_Lock] = (uint32_t)XIP_SFlash_Erase_Need_Lock,
    [ROM_API_INDEX_XIP_SFlash_Write_Need_Lock] = (uint32_t)XIP_SFlash_Write_Need_Lock,
    [ROM_API_INDEX_XIP_SFlash_Read_Need_Lock] = (uint32_t)XIP_SFlash_Read_Need_Lock,
    [ROM_API_INDEX_XIP_SFlash_GetJedecId_Need_Lock] = (uint32_t)XIP_SFlash_GetJedecId_Need_Lock,
    [ROM_API_INDEX_XIP_SFlash_GetDeviceId_Need_Lock] = (uint32_t)XIP_SFlash_GetDeviceId_Need_Lock,
    [ROM_API_INDEX_XIP_SFlash_GetUniqueId_Need_Lock] = (uint32_t)XIP_SFlash_GetUniqueId_Need_Lock,
    [ROM_API_INDEX_XIP_SFlash_Read_Via_Cache_Need_Lock] = (uint32_t)XIP_SFlash_Read_Via_Cache_Need_Lock,
    [ROM_API_INDEX_XIP_SFlash_Read_With_Lock] = (uint32_t)XIP_SFlash_Read_With_Lock,
    [ROM_API_INDEX_XIP_SFlash_Write_With_Lock] = (uint32_t)XIP_SFlash_Write_With_Lock,
    [ROM_API_INDEX_XIP_SFlash_Erase_With_Lock] = (uint32_t)XIP_SFlash_Erase_With_Lock,
    [ROM_API_INDEX_XIP_SFlash_Opt_Enter] = (uint32_t)XIP_SFlash_Opt_Enter,
    [ROM_API_INDEX_XIP_SFlash_Opt_Exit] = (uint32_t)XIP_SFlash_Opt_Exit,

    [ROM_API_INDEX_BFLB_Soft_CRC32] = (uint32_t)BFLB_Soft_CRC32,

    [ROM_API_INDEX_FUNC_EMPTY_START... ROM_API_INDEX_FUNC_EMPTY_END] = 0xdeedbeef,
};

/*@} end of group ROMDRIVER_Global_Variables */

/** @defgroup ROMDRIVER_Private_FunctionDeclaration
 *  @{
 */

/*@} end of group ROMDRIVER_Private_FunctionDeclaration */

/** @defgroup ROMDRIVER_Private_Functions
 *  @{
 */

/*@} end of group ROMDRIVER_Private_Functions */

/** @defgroup ROMDRIVER_Public_Functions
 *  @{
 */

/*@} end of group ROMDRIVER_Public_Functions */

/*@} end of group ROMDRIVER_COMMON */

/*@} end of group BL602_Periph_Driver */
