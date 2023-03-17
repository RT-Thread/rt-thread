#include "bl702_romdriver.h"
#include <string.h>

/** @addtogroup  BL702_Periph_Driver
 *  @{
 */

/** @defgroup ROMDRIVER
 *  @brief ROMDRIVER common functions
 *  @{
 */

/** @defgroup ROMDRIVER_Private_Type
 *  @{
 */
uint32_t const romDriverTable[] = {
    0x07020001,
    0x00000000,
    0x00000000,
    0x00000000,

    [ROM_API_INDEX_AON_Power_On_MBG] = (uint32_t)AON_Power_On_MBG,
    [ROM_API_INDEX_AON_Power_Off_MBG] = (uint32_t)AON_Power_Off_MBG,
    [ROM_API_INDEX_AON_Power_On_XTAL] = (uint32_t)AON_Power_On_XTAL,
    [ROM_API_INDEX_AON_Set_Xtal_CapCode] = (uint32_t)AON_Set_Xtal_CapCode,
    [ROM_API_INDEX_AON_Power_Off_XTAL] = (uint32_t)AON_Power_Off_XTAL,

    [ROM_API_INDEX_ASM_Delay_Us] = (uint32_t)ASM_Delay_Us,
    [ROM_API_INDEX_BL702_Delay_US] = (uint32_t)BL702_Delay_US,
    [ROM_API_INDEX_BL702_Delay_MS] = (uint32_t)BL702_Delay_MS,
    [ROM_API_INDEX_BL702_MemCpy] = (uint32_t)BL702_MemCpy,
    [ROM_API_INDEX_BL702_MemCpy4] = (uint32_t)BL702_MemCpy4,
    [ROM_API_INDEX_BL702_MemCpy_Fast] = (uint32_t)BL702_MemCpy_Fast,
    [ROM_API_INDEX_ARCH_MemCpy_Fast] = (uint32_t)ARCH_MemCpy_Fast,
    [ROM_API_INDEX_BL702_MemSet] = (uint32_t)BL702_MemSet,
    [ROM_API_INDEX_BL702_MemSet4] = (uint32_t)BL702_MemSet4,
    [ROM_API_INDEX_BL702_MemCmp] = (uint32_t)BL702_MemCmp,
    [ROM_API_INDEX_BFLB_Soft_CRC32] = (uint32_t)BFLB_Soft_CRC32,

    [ROM_API_INDEX_GLB_Get_Root_CLK_Sel] = (uint32_t)GLB_Get_Root_CLK_Sel,
    [ROM_API_INDEX_GLB_Set_System_CLK_Div] = (uint32_t)GLB_Set_System_CLK_Div,
    [ROM_API_INDEX_GLB_Get_BCLK_Div] = (uint32_t)GLB_Get_BCLK_Div,
    [ROM_API_INDEX_GLB_Get_HCLK_Div] = (uint32_t)GLB_Get_HCLK_Div,
    [ROM_API_INDEX_Update_SystemCoreClockWith_XTAL] = (uint32_t)Update_SystemCoreClockWith_XTAL,
    [ROM_API_INDEX_GLB_Set_System_CLK] = (uint32_t)GLB_Set_System_CLK,
    [ROM_API_INDEX_System_Core_Clock_Update_From_RC32M] = (uint32_t)System_Core_Clock_Update_From_RC32M,
    [ROM_API_INDEX_GLB_Set_SF_CLK] = (uint32_t)GLB_Set_SF_CLK,
    [ROM_API_INDEX_GLB_Power_Off_DLL] = (uint32_t)GLB_Power_Off_DLL,
    [ROM_API_INDEX_GLB_Power_On_DLL] = (uint32_t)GLB_Power_On_DLL,
    [ROM_API_INDEX_GLB_Enable_DLL_All_Clks] = (uint32_t)GLB_Enable_DLL_All_Clks,
    [ROM_API_INDEX_GLB_Enable_DLL_Clk] = (uint32_t)GLB_Enable_DLL_Clk,
    [ROM_API_INDEX_GLB_Disable_DLL_All_Clks] = (uint32_t)GLB_Disable_DLL_All_Clks,
    [ROM_API_INDEX_GLB_Disable_DLL_Clk] = (uint32_t)GLB_Disable_DLL_Clk,
    [ROM_API_INDEX_GLB_SW_System_Reset] = (uint32_t)GLB_SW_System_Reset,
    [ROM_API_INDEX_GLB_SW_CPU_Reset] = (uint32_t)GLB_SW_CPU_Reset,
    [ROM_API_INDEX_GLB_SW_POR_Reset] = (uint32_t)GLB_SW_POR_Reset,
    [ROM_API_INDEX_GLB_Select_Internal_Flash] = (uint32_t)GLB_Select_Internal_Flash,
    [ROM_API_INDEX_GLB_Swap_Flash_Pin] = (uint32_t)GLB_Swap_Flash_Pin,
    [ROM_API_INDEX_GLB_Swap_Flash_CS_IO2_Pin] = (uint32_t)GLB_Swap_Flash_CS_IO2_Pin,
    [ROM_API_INDEX_GLB_Swap_Flash_IO0_IO3_Pin] = (uint32_t)GLB_Swap_Flash_IO0_IO3_Pin,
    [ROM_API_INDEX_GLB_Select_Internal_PSram] = (uint32_t)GLB_Select_Internal_PSram,
    [ROM_API_INDEX_GLB_GPIO_Init] = (uint32_t)GLB_GPIO_Init,
    [ROM_API_INDEX_GLB_GPIO_OUTPUT_Enable] = (uint32_t)GLB_GPIO_OUTPUT_Enable,
    [ROM_API_INDEX_GLB_GPIO_OUTPUT_Disable] = (uint32_t)GLB_GPIO_OUTPUT_Disable,
    [ROM_API_INDEX_GLB_GPIO_Set_HZ] = (uint32_t)GLB_GPIO_Set_HZ,
    [ROM_API_INDEX_GLB_Deswap_Flash_Pin] = (uint32_t)GLB_Deswap_Flash_Pin,
    [ROM_API_INDEX_GLB_Select_External_Flash] = (uint32_t)GLB_Select_External_Flash,
    [ROM_API_INDEX_GLB_GPIO_Get_Fun] = (uint32_t)GLB_GPIO_Get_Fun,

    [ROM_API_INDEX_EF_Ctrl_Busy] = (uint32_t)EF_Ctrl_Busy,
    [ROM_API_INDEX_EF_Ctrl_Sw_AHB_Clk_0] = (uint32_t)EF_Ctrl_Sw_AHB_Clk_0,
    [ROM_API_INDEX_EF_Ctrl_Load_Efuse_R0] = (uint32_t)EF_Ctrl_Load_Efuse_R0,
    [ROM_API_INDEX_EF_Ctrl_Clear] = (uint32_t)EF_Ctrl_Clear,
    [ROM_API_INDEX_EF_Ctrl_Get_Trim_Parity] = (uint32_t)EF_Ctrl_Get_Trim_Parity,
    [ROM_API_INDEX_EF_Ctrl_Read_RC32K_Trim] = (uint32_t)EF_Ctrl_Read_RC32K_Trim,
    [ROM_API_INDEX_EF_Ctrl_Read_RC32M_Trim] = (uint32_t)EF_Ctrl_Read_RC32M_Trim,

    [ROM_API_INDEX_PDS_Trim_RC32M] = (uint32_t)PDS_Trim_RC32M,
    [ROM_API_INDEX_PDS_Select_RC32M_As_PLL_Ref] = (uint32_t)PDS_Select_RC32M_As_PLL_Ref,
    [ROM_API_INDEX_PDS_Select_XTAL_As_PLL_Ref] = (uint32_t)PDS_Select_XTAL_As_PLL_Ref,
    [ROM_API_INDEX_PDS_Power_On_PLL] = (uint32_t)PDS_Power_On_PLL,
    [ROM_API_INDEX_PDS_Enable_PLL_All_Clks] = (uint32_t)PDS_Enable_PLL_All_Clks,
    [ROM_API_INDEX_PDS_Disable_PLL_All_Clks] = (uint32_t)PDS_Disable_PLL_All_Clks,
    [ROM_API_INDEX_PDS_Enable_PLL_Clk] = (uint32_t)PDS_Enable_PLL_Clk,
    [ROM_API_INDEX_PDS_Disable_PLL_Clk] = (uint32_t)PDS_Disable_PLL_Clk,
    [ROM_API_INDEX_PDS_Power_Off_PLL] = (uint32_t)PDS_Power_Off_PLL,
    [ROM_API_INDEX_PDS_Reset] = (uint32_t)PDS_Reset,
    [ROM_API_INDEX_PDS_Enable] = (uint32_t)PDS_Enable,
    [ROM_API_INDEX_PDS_Auto_Time_Config] = (uint32_t)PDS_Auto_Time_Config,
    [ROM_API_INDEX_PDS_Auto_Enable] = (uint32_t)PDS_Auto_Enable,
    [ROM_API_INDEX_PDS_Manual_Force_Turn_Off] = (uint32_t)PDS_Manual_Force_Turn_Off,
    [ROM_API_INDEX_PDS_Manual_Force_Turn_On] = (uint32_t)PDS_Manual_Force_Turn_On,

    [ROM_API_INDEX_HBN_Enable] = (uint32_t)HBN_Enable,
    [ROM_API_INDEX_HBN_Reset] = (uint32_t)HBN_Reset,
    [ROM_API_INDEX_HBN_GPIO_Dbg_Pull_Cfg] = (uint32_t)HBN_GPIO_Dbg_Pull_Cfg,
    [ROM_API_INDEX_HBN_Trim_RC32K] = (uint32_t)HBN_Trim_RC32K,
    [ROM_API_INDEX_HBN_Set_ROOT_CLK_Sel] = (uint32_t)HBN_Set_ROOT_CLK_Sel,

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

    [ROM_API_INDEX_SFlash_Init] = (uint32_t)SFlash_Init,
    [ROM_API_INDEX_SFlash_SetSPIMode] = (uint32_t)SFlash_SetSPIMode,
    [ROM_API_INDEX_SFlash_Read_Reg] = (uint32_t)SFlash_Read_Reg,
    [ROM_API_INDEX_SFlash_Write_Reg] = (uint32_t)SFlash_Write_Reg,
    [ROM_API_INDEX_SFlash_Read_Reg_With_Cmd] = (uint32_t)SFlash_Read_Reg_With_Cmd,
    [ROM_API_INDEX_SFlash_Write_Reg_With_Cmd] = (uint32_t)SFlash_Write_Reg_With_Cmd,
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
    [ROM_API_INDEX_SFlash_Restore_From_Powerdown] = (uint32_t)SFlash_Restore_From_Powerdown,
    [ROM_API_INDEX_SFlash_SetBurstWrap] = (uint32_t)SFlash_SetBurstWrap,
    [ROM_API_INDEX_SFlash_DisableBurstWrap] = (uint32_t)SFlash_DisableBurstWrap,
    [ROM_API_INDEX_SFlash_Software_Reset] = (uint32_t)SFlash_Software_Reset,
    [ROM_API_INDEX_SFlash_Reset_Continue_Read] = (uint32_t)SFlash_Reset_Continue_Read,
    [ROM_API_INDEX_SFlash_Set_IDbus_Cfg] = (uint32_t)SFlash_Set_IDbus_Cfg,
    [ROM_API_INDEX_SFlash_IDbus_Read_Enable] = (uint32_t)SFlash_IDbus_Read_Enable,
    [ROM_API_INDEX_SFlash_Cache_Read_Enable] = (uint32_t)SFlash_Cache_Read_Enable,
    [ROM_API_INDEX_SFlash_Cache_Read_Disable] = (uint32_t)SFlash_Cache_Read_Disable,
    [ROM_API_INDEX_SFlash_Read] = (uint32_t)SFlash_Read,

    [ROM_API_INDEX_L1C_Cache_Enable_Set] = (uint32_t)L1C_Cache_Enable_Set,
    [ROM_API_INDEX_L1C_Cache_Write_Set] = (uint32_t)L1C_Cache_Write_Set,
    [ROM_API_INDEX_L1C_Cache_Flush] = (uint32_t)L1C_Cache_Flush,
    [ROM_API_INDEX_L1C_Cache_Hit_Count_Get] = (uint32_t)L1C_Cache_Hit_Count_Get,
    [ROM_API_INDEX_L1C_Cache_Miss_Count_Get] = (uint32_t)L1C_Cache_Miss_Count_Get,
    [ROM_API_INDEX_L1C_Cache_Read_Disable] = (uint32_t)L1C_Cache_Read_Disable,
    [ROM_API_INDEX_L1C_Set_Wrap] = (uint32_t)L1C_Set_Wrap,
    [ROM_API_INDEX_L1C_Set_Way_Disable] = (uint32_t)L1C_Set_Way_Disable,
    [ROM_API_INDEX_L1C_IROM_2T_Access_Set] = (uint32_t)L1C_IROM_2T_Access_Set,

    [ROM_API_INDEX_SF_Ctrl_Enable] = (uint32_t)SF_Ctrl_Enable,
    [ROM_API_INDEX_SF_Ctrl_Psram_Init] = (uint32_t)SF_Ctrl_Psram_Init,
    [ROM_API_INDEX_SF_Ctrl_Get_Clock_Delay] = (uint32_t)SF_Ctrl_Get_Clock_Delay,
    [ROM_API_INDEX_SF_Ctrl_Set_Clock_Delay] = (uint32_t)SF_Ctrl_Set_Clock_Delay,
    [ROM_API_INDEX_SF_Ctrl_Cmds_Set] = (uint32_t)SF_Ctrl_Cmds_Set,
    [ROM_API_INDEX_SF_Ctrl_Set_Owner] = (uint32_t)SF_Ctrl_Set_Owner,
    [ROM_API_INDEX_SF_Ctrl_Disable] = (uint32_t)SF_Ctrl_Disable,
    [ROM_API_INDEX_SF_Ctrl_Select_Pad] = (uint32_t)SF_Ctrl_Select_Pad,
    [ROM_API_INDEX_SF_Ctrl_Select_Bank] = (uint32_t)SF_Ctrl_Select_Bank,
    [ROM_API_INDEX_SF_Ctrl_AES_Enable_BE] = (uint32_t)SF_Ctrl_AES_Enable_BE,
    [ROM_API_INDEX_SF_Ctrl_AES_Enable_LE] = (uint32_t)SF_Ctrl_AES_Enable_LE,
    [ROM_API_INDEX_SF_Ctrl_AES_Set_Region] = (uint32_t)SF_Ctrl_AES_Set_Region,
    [ROM_API_INDEX_SF_Ctrl_AES_Set_Key] = (uint32_t)SF_Ctrl_AES_Set_Key,
    [ROM_API_INDEX_SF_Ctrl_AES_Set_Key_BE] = (uint32_t)SF_Ctrl_AES_Set_Key_BE,
    [ROM_API_INDEX_SF_Ctrl_AES_Set_IV] = (uint32_t)SF_Ctrl_AES_Set_IV,
    [ROM_API_INDEX_SF_Ctrl_AES_Set_IV_BE] = (uint32_t)SF_Ctrl_AES_Set_IV_BE,
    [ROM_API_INDEX_SF_Ctrl_AES_Enable] = (uint32_t)SF_Ctrl_AES_Enable,
    [ROM_API_INDEX_SF_Ctrl_AES_Disable] = (uint32_t)SF_Ctrl_AES_Disable,
    [ROM_API_INDEX_SF_Ctrl_Is_AES_Enable] = (uint32_t)SF_Ctrl_Is_AES_Enable,
    [ROM_API_INDEX_SF_Ctrl_Set_Flash_Image_Offset] = (uint32_t)SF_Ctrl_Set_Flash_Image_Offset,
    [ROM_API_INDEX_SF_Ctrl_Get_Flash_Image_Offset] = (uint32_t)SF_Ctrl_Get_Flash_Image_Offset,
    [ROM_API_INDEX_SF_Ctrl_Select_Clock] = (uint32_t)SF_Ctrl_Select_Clock,
    [ROM_API_INDEX_SF_Ctrl_SendCmd] = (uint32_t)SF_Ctrl_SendCmd,
    [ROM_API_INDEX_SF_Ctrl_Flash_Read_Icache_Set] = (uint32_t)SF_Ctrl_Flash_Read_Icache_Set,
    [ROM_API_INDEX_SF_Ctrl_Psram_Write_Icache_Set] = (uint32_t)SF_Ctrl_Psram_Write_Icache_Set,
    [ROM_API_INDEX_SF_Ctrl_Psram_Read_Icache_Set] = (uint32_t)SF_Ctrl_Psram_Read_Icache_Set,
    [ROM_API_INDEX_SF_Ctrl_GetBusyState] = (uint32_t)SF_Ctrl_GetBusyState,
    [ROM_API_INDEX_SF_Cfg_Deinit_Ext_Flash_Gpio] = (uint32_t)SF_Cfg_Deinit_Ext_Flash_Gpio,
    [ROM_API_INDEX_SF_Cfg_Init_Ext_Flash_Gpio] = (uint32_t)SF_Cfg_Init_Ext_Flash_Gpio,
    [ROM_API_INDEX_SF_Cfg_Get_Flash_Cfg_Need_Lock] = (uint32_t)SF_Cfg_Get_Flash_Cfg_Need_Lock,
    [ROM_API_INDEX_SF_Cfg_Init_Flash_Gpio] = (uint32_t)SF_Cfg_Init_Flash_Gpio,
    [ROM_API_INDEX_SF_Cfg_Flash_Identify] = (uint32_t)SF_Cfg_Flash_Identify,

    [ROM_API_INDEX_Psram_Init] = (uint32_t)Psram_Init,
    [ROM_API_INDEX_Psram_ReadReg] = (uint32_t)Psram_ReadReg,
    [ROM_API_INDEX_Psram_WriteReg] = (uint32_t)Psram_WriteReg,
    [ROM_API_INDEX_Psram_SetDriveStrength] = (uint32_t)Psram_SetDriveStrength,
    [ROM_API_INDEX_Psram_SetBurstWrap] = (uint32_t)Psram_SetBurstWrap,
    [ROM_API_INDEX_Psram_ReadId] = (uint32_t)Psram_ReadId,
    [ROM_API_INDEX_Psram_EnterQuadMode] = (uint32_t)Psram_EnterQuadMode,
    [ROM_API_INDEX_Psram_ExitQuadMode] = (uint32_t)Psram_ExitQuadMode,
    [ROM_API_INDEX_Psram_ToggleBurstLength] = (uint32_t)Psram_ToggleBurstLength,
    [ROM_API_INDEX_Psram_SoftwareReset] = (uint32_t)Psram_SoftwareReset,
    [ROM_API_INDEX_Psram_Set_IDbus_Cfg] = (uint32_t)Psram_Set_IDbus_Cfg,
    [ROM_API_INDEX_Psram_Cache_Write_Set] = (uint32_t)Psram_Cache_Write_Set,
    [ROM_API_INDEX_Psram_Write] = (uint32_t)Psram_Write,
    [ROM_API_INDEX_Psram_Read] = (uint32_t)Psram_Read,

    [ROM_API_INDEX_FUNC_INVALID_START... ROM_API_INDEX_FUNC_LAST_ENTRY] = 0xdeedbeef,
};

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

/*@} end of group BL702_Periph_Driver */
