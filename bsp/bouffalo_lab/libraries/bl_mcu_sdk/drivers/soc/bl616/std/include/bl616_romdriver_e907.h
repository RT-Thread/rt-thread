/**
  ******************************************************************************
  * @file    bl616_romdriver_e907.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
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
#ifndef __BL616_ROMDRIVER_E907_H__
#define __BL616_ROMDRIVER_E907_H__

#include "bl616_glb.h"
#include "bl616_glb_gpio.h"
#include "bl616_pds.h"
#include "bl616_hbn.h"
#include "bl616_clock.h"
#include "bl616_ef_ctrl.h"
#include "bflb_sf_ctrl.h"
#include "bflb_sflash.h"
#include "bflb_sf_cfg.h"
#include "bflb_xip_sflash.h"
// #include "bl616_uart.h"

/** @addtogroup  bl616_Peripheral_Driver
 *  @{
 */

/** @addtogroup  ROMDRIVER
 *  @{
 */

/** @defgroup  ROMDRIVER_Public_Types
 *  @{
 */

#define ROMAPI_INDEX_SECT_SIZE     (0x800)
#define ROMAPI_INDEX_MAX           (ROMAPI_INDEX_SECT_SIZE / 4 - 1)

typedef enum {
    ROM_API_INDEX_VERSION = 0,
    ROM_API_INDEX_RSVD_0 ,
    ROM_API_INDEX_RSVD_1,
    ROM_API_INDEX_RSVD_LAST,


    ROM_API_INDEX_AON_Power_Off_BG,
    ROM_API_INDEX_AON_Power_Off_LDO15_RF,
    ROM_API_INDEX_AON_Power_Off_MBG,
    ROM_API_INDEX_AON_Power_Off_SFReg,
    ROM_API_INDEX_AON_Power_Off_XTAL,
    ROM_API_INDEX_AON_Power_On_BG,
    ROM_API_INDEX_AON_Power_On_LDO15_RF,
    ROM_API_INDEX_AON_Power_On_MBG,
    ROM_API_INDEX_AON_Power_On_SFReg,
    ROM_API_INDEX_AON_Power_On_XTAL,
    ROM_API_INDEX_AON_Set_Xtal_CapCode,
    ROM_API_INDEX_AON_Trim_DcdcDis,
    ROM_API_INDEX_AON_Trim_DcdcVoutSel,
    ROM_API_INDEX_AON_Trim_DcdcVoutTrim,
    ROM_API_INDEX_AON_Trim_Ldo11socVoutTrim,
    ROM_API_INDEX_AON_Trim_Usb20RcalCode,
    ROM_API_INDEX_AON_Get_Xtal_CapCode,

    ROM_API_INDEX_CPU_MTimer_Delay_MS,
    ROM_API_INDEX_CPU_MTimer_Delay_US,
    ROM_API_INDEX_CPU_Reset_MTimer,
    ROM_API_INDEX_CPU_Set_MTimer_CLK,
    ROM_API_INDEX_CPU_Set_MTimer_RST,
    ROM_API_INDEX_CPU_Get_MTimer_Clock,
    ROM_API_INDEX_CPU_Get_MTimer_Source_Clock,

    ROM_API_INDEX_Clock_Audio_ADC_Clock_Get,
    ROM_API_INDEX_Clock_Get_ISP_Clk,
    ROM_API_INDEX_Clock_Get_PSRAMB_Clk,
    ROM_API_INDEX_Clock_Peripheral_Clock_Get,
    ROM_API_INDEX_Clock_System_Clock_Get,

    ROM_API_INDEX_SystemCoreClockGet,

    ROM_API_INDEX_CPU_Get_CPU_Cycle,
    ROM_API_INDEX_CPU_Get_MTimer_Counter,
    ROM_API_INDEX_CPU_Get_MTimer_MS,
    ROM_API_INDEX_CPU_Get_MTimer_US,

    ROM_API_INDEX_EF_Ctrl_Crc_Result,
    ROM_API_INDEX_EF_Ctrl_Get_Customer_PIDVID,
    ROM_API_INDEX_EF_Ctrl_Read_Chip_ID,
    ROM_API_INDEX_EF_Ctrl_Read_MAC_Address,
    ROM_API_INDEX_EF_Ctrl_Read_MAC_Address_Raw,
    ROM_API_INDEX_EF_Ctrl_AutoLoad_Done,
    ROM_API_INDEX_EF_Ctrl_Busy,
    ROM_API_INDEX_EF_Ctrl_Crc_Is_Busy,
    ROM_API_INDEX_EF_Ctrl_Get_Trim_Parity,
    ROM_API_INDEX_EF_Ctrl_Is_All_Bits_Zero,
    ROM_API_INDEX_EF_Ctrl_Read_FlashDlyCoe,
    ROM_API_INDEX_EF_Ctrl_Clear,
    ROM_API_INDEX_EF_Ctrl_Crc_Enable,
    ROM_API_INDEX_EF_Ctrl_Crc_Set_Golden,
    ROM_API_INDEX_EF_Ctrl_Load_Efuse_R0,
    ROM_API_INDEX_EF_Ctrl_Program_Direct_R0,
    ROM_API_INDEX_EF_Ctrl_Program_Efuse_0,
    ROM_API_INDEX_EF_Ctrl_Read_ADC_Gain_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_AES_Key,
    ROM_API_INDEX_EF_Ctrl_Read_Dbg_Pwd,
    ROM_API_INDEX_EF_Ctrl_Read_DcdcDis_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_DcdcVoutSel_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_DcdcVoutTrim_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_Device_Info,
    ROM_API_INDEX_EF_Ctrl_Read_Direct_R0,
    ROM_API_INDEX_EF_Ctrl_Read_Ldo11socVoutTrim_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_Ldo18ioBypass_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_Ldo18ioVoutSel_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_Ldo18ioVoutTrim_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_Ldo33VoutTrim_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_RC32K_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_RC32M_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_Secure_Boot,
    ROM_API_INDEX_EF_Ctrl_Read_Secure_Cfg,
    ROM_API_INDEX_EF_Ctrl_Read_Sw_Usage,
    ROM_API_INDEX_EF_Ctrl_Read_TSEN_Trim,
    ROM_API_INDEX_EF_Ctrl_Read_Usb20RcalCode_Trim,
    ROM_API_INDEX_EF_Ctrl_Readlock_AES_Key,
    ROM_API_INDEX_EF_Ctrl_Readlock_Dbg_Pwd,
    ROM_API_INDEX_EF_Ctrl_Set_sf_key_re_sel,
    ROM_API_INDEX_EF_Ctrl_Sw_AHB_Clk_0,
    ROM_API_INDEX_EF_Ctrl_Write_AES_Key,
    ROM_API_INDEX_EF_Ctrl_Write_Dbg_Pwd,
    ROM_API_INDEX_EF_Ctrl_Write_MAC_Address,
    ROM_API_INDEX_EF_Ctrl_Write_Secure_Boot,
    ROM_API_INDEX_EF_Ctrl_Write_Secure_Cfg,
    ROM_API_INDEX_EF_Ctrl_Write_Sw_Usage,
    ROM_API_INDEX_EF_Ctrl_Writelock_AES_Key,
    ROM_API_INDEX_EF_Ctrl_Writelock_Dbg_Pwd,
    ROM_API_INDEX_EF_Ctrl_Writelock_MAC_Address,
    ROM_API_INDEX_EF_Ctrl_Writelock_Sw_Usage,

    ROM_API_INDEX_GLB_AHB_MCU_Software_Reset,
    ROM_API_INDEX_GLB_AUPLL_Ref_Clk_Sel,
    ROM_API_INDEX_GLB_BMX_TO_Init,
    ROM_API_INDEX_GLB_Clr_BMX_TO_Status,
    ROM_API_INDEX_GLB_Clr_EMI_Reset_Gate,
    ROM_API_INDEX_GLB_Clr_Reset_Reason,
    ROM_API_INDEX_GLB_Config_SDIO_Host_Interrupt_CPU,
    ROM_API_INDEX_GLB_Config_SDIO_Host_Reset_SDU,
    ROM_API_INDEX_GLB_Config_SDIO_Host_Reset_System,
    ROM_API_INDEX_GLB_Get_Auto_Calc_Xtal_Type,
    ROM_API_INDEX_GLB_Get_MCU_System_CLK_Div,
    ROM_API_INDEX_GLB_Get_Reset_Reason,
    ROM_API_INDEX_GLB_IR_RX_GPIO_Sel,
    ROM_API_INDEX_GLB_Invert_ETH_REF_O_CLK,
    ROM_API_INDEX_GLB_Invert_ETH_RX_CLK,
    ROM_API_INDEX_GLB_Invert_ETH_TX_CLK,
    ROM_API_INDEX_GLB_MCU_SW_System_Reset,
    ROM_API_INDEX_GLB_PER_Clock_Gate,
    ROM_API_INDEX_GLB_PER_Clock_UnGate,
    ROM_API_INDEX_GLB_PLL_CGEN_Clock_Gate,
    ROM_API_INDEX_GLB_PLL_CGEN_Clock_UnGate,
    ROM_API_INDEX_GLB_Platform_Wakeup_PDS_Enable,
    ROM_API_INDEX_GLB_Power_Off_AUPLL,
    ROM_API_INDEX_GLB_Power_Off_WIFIPLL,
    ROM_API_INDEX_GLB_Power_On_AUPLL,
    ROM_API_INDEX_GLB_Power_On_WIFIPLL,
    ROM_API_INDEX_GLB_Power_On_XTAL_And_PLL_CLK,
    ROM_API_INDEX_GLB_SPI_Sig_Swap_Set,
    ROM_API_INDEX_GLB_SW_CPU_Reset,
    ROM_API_INDEX_GLB_SW_POR_Reset,
    ROM_API_INDEX_GLB_SW_System_Reset,
    ROM_API_INDEX_GLB_Sel_MCU_TMR_GPIO_Clock,
    ROM_API_INDEX_GLB_Set_ADC_CLK,
    ROM_API_INDEX_GLB_Set_Audio_ADC_CLK,
    ROM_API_INDEX_GLB_Set_Audio_AUTO_CLK,
    ROM_API_INDEX_GLB_Set_Audio_SOLO_CLK,
    ROM_API_INDEX_GLB_Set_Auto_Calc_Xtal_Type,
    ROM_API_INDEX_GLB_Set_CAM_CLK,
    ROM_API_INDEX_GLB_Set_CPU_Reset_Address,
    ROM_API_INDEX_GLB_Set_Chip_Clock_Out_Sel,
    ROM_API_INDEX_GLB_Set_DBI_CLK,
    ROM_API_INDEX_GLB_Set_DIG_32K_CLK,
    ROM_API_INDEX_GLB_Set_DIG_512K_CLK,
    ROM_API_INDEX_GLB_Set_DIG_CLK_Sel,
    ROM_API_INDEX_GLB_Set_DMA_CLK,
    ROM_API_INDEX_GLB_Set_EM_Sel,
    ROM_API_INDEX_GLB_Set_ETH_REF_O_CLK_Sel,
    ROM_API_INDEX_GLB_Set_ETH_REF_O_CLK_Sel_2,
    ROM_API_INDEX_GLB_Set_I2C_CLK,
    ROM_API_INDEX_GLB_Set_I2S_CLK,
    ROM_API_INDEX_GLB_Set_IR_CLK,
    ROM_API_INDEX_GLB_Set_ISP_Muxpll_80M_Sel,
    ROM_API_INDEX_GLB_Set_MCU_Muxpll_160M_Sel,
    ROM_API_INDEX_GLB_Set_MCU_Muxpll_80M_Sel,
    ROM_API_INDEX_GLB_Set_MCU_SPI_0_ACT_MOD_Sel,
    ROM_API_INDEX_GLB_Set_MCU_System_CLK,
    ROM_API_INDEX_GLB_Set_MCU_System_CLK_Div,
    ROM_API_INDEX_GLB_Set_PDM_IO_Sel,
    ROM_API_INDEX_GLB_Set_PKA_CLK_Sel,
    ROM_API_INDEX_GLB_Set_PSRAMB_CLK_Sel,
    ROM_API_INDEX_GLB_Set_PWM1_IO_Sel,
    ROM_API_INDEX_GLB_Set_Peripheral_DMA_CN,
    ROM_API_INDEX_GLB_Set_SDH_CLK,
    ROM_API_INDEX_GLB_Set_SF_CLK,
    ROM_API_INDEX_GLB_Set_SFlash2_IO_PARM,
    ROM_API_INDEX_GLB_Set_SFlash_IO_PARM,
    ROM_API_INDEX_GLB_Set_SPI_CLK,
    ROM_API_INDEX_GLB_Set_SRAM_PARM,
    ROM_API_INDEX_GLB_Set_SRAM_RET,
    ROM_API_INDEX_GLB_Set_SRAM_SLP,
    ROM_API_INDEX_GLB_Set_SSC_CLK_From_WIFIPLL,
    ROM_API_INDEX_GLB_Set_Slave_Grp_0_CLK,
    ROM_API_INDEX_GLB_Set_UART_CLK,
    ROM_API_INDEX_GLB_Set_USB_CLK_From_WIFIPLL,
    ROM_API_INDEX_GLB_Swap_MCU_SPI_0_MOSI_With_MISO,
    ROM_API_INDEX_GLB_Trim_Ldo18ioBypass,
    ROM_API_INDEX_GLB_Trim_Ldo18ioVoutSel,
    ROM_API_INDEX_GLB_Trim_Ldo18ioVoutTrim,
    ROM_API_INDEX_GLB_UART_Fun_Sel,
    ROM_API_INDEX_GLB_UART_Sig_Swap_Set,
    ROM_API_INDEX_GLB_WIFIPLL_Ref_Clk_Sel,
    ROM_API_INDEX_GLB_Get_Core_Type,
    ROM_API_INDEX_GLB_Get_MCU_Muxpll_160M_Sel,
    ROM_API_INDEX_GLB_Get_MCU_Muxpll_80M_Sel,
    ROM_API_INDEX_GLB_Get_SRAM_PARM,
    ROM_API_INDEX_GLB_Get_SRAM_RET,
    ROM_API_INDEX_GLB_Get_SRAM_SLP,
    ROM_API_INDEX_GLB_Get_BMX_TO_Status,
    ROM_API_INDEX_GLB_Clr_GPIO_IntStatus,
    ROM_API_INDEX_GLB_Embedded_Flash_Pad_Enable,
    ROM_API_INDEX_GLB_GPIO_Clr,
    ROM_API_INDEX_GLB_GPIO_Fifo_Clear,
    ROM_API_INDEX_GLB_GPIO_Fifo_Init,
    ROM_API_INDEX_GLB_GPIO_Fifo_IntClear,
    ROM_API_INDEX_GLB_GPIO_Fifo_IntMask,
    ROM_API_INDEX_GLB_GPIO_Fifo_Push,
    ROM_API_INDEX_GLB_GPIO_Func_Init,
    ROM_API_INDEX_GLB_GPIO_Init,
    ROM_API_INDEX_GLB_GPIO_Input_Disable,
    ROM_API_INDEX_GLB_GPIO_Input_Enable,
    ROM_API_INDEX_GLB_GPIO_IntMask,
    ROM_API_INDEX_GLB_GPIO_Int_Init,
    ROM_API_INDEX_GLB_GPIO_Output_Disable,
    ROM_API_INDEX_GLB_GPIO_Output_Enable,
    ROM_API_INDEX_GLB_GPIO_Set,
    ROM_API_INDEX_GLB_GPIO_Set_HZ,
    ROM_API_INDEX_GLB_GPIO_Write,
    ROM_API_INDEX_GLB_GPIO_Fifo_Disable,
    ROM_API_INDEX_GLB_GPIO_Fifo_Enable,
    ROM_API_INDEX_GLB_GPIO_Fifo_GetIntStatus,
    ROM_API_INDEX_GLB_Get_GPIO_IntStatus,
    ROM_API_INDEX_GLB_GPIO_Fifo_GetCount,
    ROM_API_INDEX_GLB_GPIO_Read,
    ROM_API_INDEX_GLB_GPIO_Get_Fun,

    ROM_API_INDEX_HBN_32K_Sel,
    ROM_API_INDEX_HBN_Aon_Pad_Cfg,
    ROM_API_INDEX_HBN_Aon_Pad_Cfg_Set,
    ROM_API_INDEX_HBN_Aon_Pad_Ctrl,
    ROM_API_INDEX_HBN_Aon_Pad_WakeUpCfg,
    ROM_API_INDEX_HBN_Clear_Gpio_Keep,
    ROM_API_INDEX_HBN_Clear_IRQ,
    ROM_API_INDEX_HBN_Clear_PDS_Gpio_Keep,
    ROM_API_INDEX_HBN_Clear_RTC_Counter,
    ROM_API_INDEX_HBN_Clear_RTC_INT,
    ROM_API_INDEX_HBN_Disable_AComp0_IRQ,
    ROM_API_INDEX_HBN_Disable_AComp1_IRQ,
    ROM_API_INDEX_HBN_Disable_BOD_IRQ,
    ROM_API_INDEX_HBN_Enable_AComp0_IRQ,
    ROM_API_INDEX_HBN_Enable_AComp1_IRQ,
    ROM_API_INDEX_HBN_Enable_BOD_IRQ,
    ROM_API_INDEX_HBN_Enable_RTC_Counter,
    ROM_API_INDEX_HBN_GPIO_INT_Disable,
    ROM_API_INDEX_HBN_GPIO_INT_Enable,
    ROM_API_INDEX_HBN_Get_Flash_Power_Delay,
    ROM_API_INDEX_HBN_Get_Gpio_Keep,
    ROM_API_INDEX_HBN_Get_Ldo18io_Power_Delay_Config,
    ROM_API_INDEX_HBN_Get_PDS_Gpio_Keep,
    ROM_API_INDEX_HBN_Get_RTC_Timer_Val,
    ROM_API_INDEX_HBN_Get_Xtal_Type,
    ROM_API_INDEX_HBN_Hw_Pu_Pd_Cfg,
    ROM_API_INDEX_HBN_Keep_On_RC32K,
    ROM_API_INDEX_HBN_PIR_Disable,
    ROM_API_INDEX_HBN_PIR_Enable,
    ROM_API_INDEX_HBN_PIR_HPF_Sel,
    ROM_API_INDEX_HBN_PIR_INT_Config,
    ROM_API_INDEX_HBN_PIR_LPF_Sel,
    ROM_API_INDEX_HBN_Pin_WakeUp_Mask,
    ROM_API_INDEX_HBN_Power_Off_RC32K,
    ROM_API_INDEX_HBN_Power_Off_Xtal_32K,
    ROM_API_INDEX_HBN_Power_On_Xtal_32K,
    ROM_API_INDEX_HBN_Reset,
    ROM_API_INDEX_HBN_Set_BOD_Cfg,
    ROM_API_INDEX_HBN_Set_BOD_Config,
    ROM_API_INDEX_HBN_Set_Core_Reboot_Config,
    ROM_API_INDEX_HBN_Set_Flash_Power_Delay,
    ROM_API_INDEX_HBN_Set_GPADC_CLK_Sel,
    ROM_API_INDEX_HBN_Set_Gpio_Keep,
    ROM_API_INDEX_HBN_Set_HRAM_Ret,
    ROM_API_INDEX_HBN_Set_HRAM_slp,
    ROM_API_INDEX_HBN_Set_Ldo11_All_Vout,
    ROM_API_INDEX_HBN_Set_Ldo11_Aon_Vout,
    ROM_API_INDEX_HBN_Set_Ldo11_Rt_Vout,
    ROM_API_INDEX_HBN_Set_Ldo11_Soc_Vout,
    ROM_API_INDEX_HBN_Set_Ldo18io_Power_Delay_Config,
    ROM_API_INDEX_HBN_Set_MCU_Root_CLK_Sel,
    ROM_API_INDEX_HBN_Set_MCU_XCLK_Sel,
    ROM_API_INDEX_HBN_Set_PDS_Gpio_Keep,
    ROM_API_INDEX_HBN_Set_PIR_Interval,
    ROM_API_INDEX_HBN_Set_PIR_Threshold,
    ROM_API_INDEX_HBN_Set_RTC_Timer,
    ROM_API_INDEX_HBN_Set_Status_Flag,
    ROM_API_INDEX_HBN_Set_UART_CLK_Sel,
    ROM_API_INDEX_HBN_Set_User_Boot_Config,
    ROM_API_INDEX_HBN_Set_Wakeup_Addr,
    ROM_API_INDEX_HBN_Set_Xtal_Type,
    ROM_API_INDEX_HBN_Trim_Ldo33VoutTrim,
    ROM_API_INDEX_HBN_Trim_RC32K,
    ROM_API_INDEX_HBN_Get_BOD_OUT_State,
    ROM_API_INDEX_HBN_Get_INT_State,
    ROM_API_INDEX_HBN_Get_MCU_Root_CLK_Sel,
    ROM_API_INDEX_HBN_Get_MCU_XCLK_Sel,
    ROM_API_INDEX_HBN_Get_PIR_Interval,
    ROM_API_INDEX_HBN_Get_PIR_Threshold,
    ROM_API_INDEX_HBN_Get_Status_Flag,
    ROM_API_INDEX_HBN_Get_Wakeup_Addr,
    ROM_API_INDEX_HBN_Get_Core_Unhalt_Config,
    ROM_API_INDEX_HBN_Get_Pin_Wakeup_Mode,
    ROM_API_INDEX_HBN_Get_User_Boot_Config,
    ROM_API_INDEX_HBN_Enable,
    ROM_API_INDEX_HBN_Mode_Enter,
    ROM_API_INDEX_HBN_Power_Down_Flash,

    ROM_API_INDEX_L1C_DCache_Clean_All,
    ROM_API_INDEX_L1C_DCache_Clean_By_Addr,
    ROM_API_INDEX_L1C_DCache_Clean_Invalid_All,
    ROM_API_INDEX_L1C_DCache_Clean_Invalid_By_Addr,
    ROM_API_INDEX_L1C_DCache_Disable,
    ROM_API_INDEX_L1C_DCache_Enable,
    ROM_API_INDEX_L1C_DCache_Invalid_All,
    ROM_API_INDEX_L1C_DCache_Invalid_By_Addr,
    ROM_API_INDEX_L1C_ICache_Disable,
    ROM_API_INDEX_L1C_ICache_Enable,
    ROM_API_INDEX_L1C_ICache_Invalid_All,
    ROM_API_INDEX_L1C_ICache_Invalid_By_Addr,
    ROM_API_INDEX_L1C_Set_Cache_Setting_By_ID,
    ROM_API_INDEX_L1C_Set_Wrap,
    ROM_API_INDEX_L1C_DCache_Write_Set,

    ROM_API_INDEX_PDS_Default_Level_Config,
    ROM_API_INDEX_PDS_Disable_GPIO_Keep,
    ROM_API_INDEX_PDS_Enable,
    ROM_API_INDEX_PDS_Force_Config,
    ROM_API_INDEX_PDS_IntClear,
    ROM_API_INDEX_PDS_IntMask,
    ROM_API_INDEX_PDS_RAM_Config,
    ROM_API_INDEX_PDS_Set_Flash_Pad_Pull_None,
    ROM_API_INDEX_PDS_Set_Flash_Pad_Pull_None_Fast,
    ROM_API_INDEX_PDS_Set_GPIO_Pad_IntClr,
    ROM_API_INDEX_PDS_Set_GPIO_Pad_IntMask,
    ROM_API_INDEX_PDS_Set_GPIO_Pad_IntMode,
    ROM_API_INDEX_PDS_Set_GPIO_Pad_Pn_Pu_Pd_Ie,
    ROM_API_INDEX_PDS_Set_MCU0_Clock_Disable,
    ROM_API_INDEX_PDS_Set_MCU0_Clock_Enable,
    ROM_API_INDEX_PDS_Set_MCU0_Reset_Address,
    ROM_API_INDEX_PDS_Set_USB_Resume,
    ROM_API_INDEX_PDS_Set_USB_Suspend,
    ROM_API_INDEX_PDS_Trim_RC32M,
    ROM_API_INDEX_PDS_Turn_Off_USB,
    ROM_API_INDEX_PDS_Turn_On_USB,
    ROM_API_INDEX_PDS_Get_GPIO_Pad_IntStatus,
    ROM_API_INDEX_PDS_Get_IntStatus,

    ROM_API_INDEX_SF_Cfg_Deinit_Ext_Flash_Gpio,
    ROM_API_INDEX_SF_Cfg_Flash_Init,
    ROM_API_INDEX_SF_Cfg_Get_Flash_Cfg_Need_Lock,
    ROM_API_INDEX_SF_Cfg_Init_Ext_Flash_Gpio,
    ROM_API_INDEX_SF_Cfg_Init_Flash2_Gpio,
    ROM_API_INDEX_SF_Cfg_Init_Flash_Gpio,
    ROM_API_INDEX_SF_Cfg_Sbus2_Flash_Init,
    ROM_API_INDEX_SF_Cfg_Flash_Identify,
    ROM_API_INDEX_SF_Ctrl_GetBusyState,
    ROM_API_INDEX_SF_Ctrl_Is_AES_Enable,
    ROM_API_INDEX_SF_Ctrl_Is_Sbus2_Enable,
    ROM_API_INDEX_SF_Ctrl_Get_Flash_Image_Offset,
    ROM_API_INDEX_SF_Ctrl_Get_Clock_Delay,
    ROM_API_INDEX_SF_Ctrl_Get_Wrap_Queue_Value,
    ROM_API_INDEX_SF_Ctrl_32bits_Addr_En,
    ROM_API_INDEX_SF_Ctrl_AES_Disable,
    ROM_API_INDEX_SF_Ctrl_AES_Enable,
    ROM_API_INDEX_SF_Ctrl_AES_Enable_BE,
    ROM_API_INDEX_SF_Ctrl_AES_Enable_LE,
    ROM_API_INDEX_SF_Ctrl_AES_Set_IV,
    ROM_API_INDEX_SF_Ctrl_AES_Set_IV_BE,
    ROM_API_INDEX_SF_Ctrl_AES_Set_Key,
    ROM_API_INDEX_SF_Ctrl_AES_Set_Key_BE,
    ROM_API_INDEX_SF_Ctrl_AES_Set_Mode,
    ROM_API_INDEX_SF_Ctrl_AES_Set_Region,
    ROM_API_INDEX_SF_Ctrl_AES_XTS_Set_IV,
    ROM_API_INDEX_SF_Ctrl_AES_XTS_Set_IV_BE,
    ROM_API_INDEX_SF_Ctrl_AES_XTS_Set_Key,
    ROM_API_INDEX_SF_Ctrl_AES_XTS_Set_Key_BE,
    ROM_API_INDEX_SF_Ctrl_Bank2_Enable,
    ROM_API_INDEX_SF_Ctrl_Cmds_Set,
    ROM_API_INDEX_SF_Ctrl_Disable,
    ROM_API_INDEX_SF_Ctrl_Disable_Wrap_Access,
    ROM_API_INDEX_SF_Ctrl_Enable,
    ROM_API_INDEX_SF_Ctrl_Flash2_Read_Icache_Set,
    ROM_API_INDEX_SF_Ctrl_Flash_Read_Icache_Set,
    ROM_API_INDEX_SF_Ctrl_Lock_Flash_Image_Offset,
    ROM_API_INDEX_SF_Ctrl_Remap_Set,
    ROM_API_INDEX_SF_Ctrl_Sbus2_Hold_Sram,
    ROM_API_INDEX_SF_Ctrl_Sbus2_Release_Sram,
    ROM_API_INDEX_SF_Ctrl_Sbus2_Replace,
    ROM_API_INDEX_SF_Ctrl_Sbus2_Revoke_replace,
    ROM_API_INDEX_SF_Ctrl_Sbus2_Set_Delay,
    ROM_API_INDEX_SF_Ctrl_Sbus_Select_Bank,
    ROM_API_INDEX_SF_Ctrl_Select_Pad,
    ROM_API_INDEX_SF_Ctrl_SendCmd,
    ROM_API_INDEX_SF_Ctrl_Set_Clock_Delay,
    ROM_API_INDEX_SF_Ctrl_Set_Flash_Image_Offset,
    ROM_API_INDEX_SF_Ctrl_Set_IO_Delay,
    ROM_API_INDEX_SF_Ctrl_Set_Owner,

    ROM_API_INDEX_SFlash_Blk32_Erase,
    ROM_API_INDEX_SFlash_Blk64_Erase,
    ROM_API_INDEX_SFlash_Chip_Erase,
    ROM_API_INDEX_SFlash_Erase,
    ROM_API_INDEX_SFlash_Erase_Security_Register,
    ROM_API_INDEX_SFlash_IDbus_Read_Enable,
    ROM_API_INDEX_SFlash_Program,
    ROM_API_INDEX_SFlash_Program_Security_Register,
    ROM_API_INDEX_SFlash_Qspi_Disable,
    ROM_API_INDEX_SFlash_Qspi_Enable,
    ROM_API_INDEX_SFlash_RCV_Enable,
    ROM_API_INDEX_SFlash_Read,
    ROM_API_INDEX_SFlash_Read_Reg,
    ROM_API_INDEX_SFlash_Read_Reg_With_Cmd,
    ROM_API_INDEX_SFlash_Read_Security_Register,
    ROM_API_INDEX_SFlash_Restore_From_Powerdown,
    ROM_API_INDEX_SFlash_Sector_Erase,
    ROM_API_INDEX_SFlash_Set32BitsAddrMode,
    ROM_API_INDEX_SFlash_SetSPIMode,
    ROM_API_INDEX_SFlash_Set_IDbus_Cfg,
    ROM_API_INDEX_SFlash_Software_Reset,
    ROM_API_INDEX_SFlash_Write_Enable,
    ROM_API_INDEX_SFlash_Write_Reg,
    ROM_API_INDEX_SFlash_Write_Reg_With_Cmd,
    ROM_API_INDEX_SFlash_Busy,
    ROM_API_INDEX_SFlash_DisableBurstWrap,
    ROM_API_INDEX_SFlash_GetDeviceId,
    ROM_API_INDEX_SFlash_GetJedecId,
    ROM_API_INDEX_SFlash_GetUniqueId,
    ROM_API_INDEX_SFlash_IDbus_Read_Disable,
    ROM_API_INDEX_SFlash_Init,
    ROM_API_INDEX_SFlash_Powerdown,
    ROM_API_INDEX_SFlash_Release_Powerdown,
    ROM_API_INDEX_SFlash_Reset_Continue_Read,
    ROM_API_INDEX_SFlash_SetBurstWrap,
    ROM_API_INDEX_SFlash_Volatile_Reg_Write_Enable,

    ROM_API_INDEX_UART_AutoBaudDetection,
    ROM_API_INDEX_UART_ClrRtsValue,
    ROM_API_INDEX_UART_ClrTxValue,
    ROM_API_INDEX_UART_DeInit,
    ROM_API_INDEX_UART_Disable,
    ROM_API_INDEX_UART_Enable,
    ROM_API_INDEX_UART_FifoConfig,
    ROM_API_INDEX_UART_GetBitWidth0X55,
    ROM_API_INDEX_UART_Init,
    ROM_API_INDEX_UART_IntClear,
    ROM_API_INDEX_UART_IntMask,
    ROM_API_INDEX_UART_IrConfig,
    ROM_API_INDEX_UART_RxFifoClear,
    ROM_API_INDEX_UART_SendData,
    ROM_API_INDEX_UART_SendDataBlock,
    ROM_API_INDEX_UART_SetAllowableError0X55,
    ROM_API_INDEX_UART_SetBaudrate,
    ROM_API_INDEX_UART_SetDeglitchCount,
    ROM_API_INDEX_UART_SetRS485,
    ROM_API_INDEX_UART_SetRtsValue,
    ROM_API_INDEX_UART_SetRxByteCount,
    ROM_API_INDEX_UART_SetRxDataLength,
    ROM_API_INDEX_UART_SetRxTimeoutValue,
    ROM_API_INDEX_UART_SetTxDataLength,
    ROM_API_INDEX_UART_SetTxValue,
    ROM_API_INDEX_UART_TxFifoClear,
    ROM_API_INDEX_UART_TxFreeRun,
    ROM_API_INDEX_UART_GetIntStatus,
    ROM_API_INDEX_UART_GetOverflowStatus,
    ROM_API_INDEX_UART_GetRxBusBusyStatus,
    ROM_API_INDEX_UART_GetTxBusBusyStatus,
    ROM_API_INDEX_UART_GetAutoBaudCount,
    ROM_API_INDEX_UART_GetRxByteCount,
    ROM_API_INDEX_UART_ReceiveData,
    ROM_API_INDEX_UART_GetRxFifoCount,
    ROM_API_INDEX_UART_GetTxFifoCount,

    ROM_API_INDEX_XIP_SFlash_Erase_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_GetDeviceId_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_GetJedecId_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_GetUniqueId_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_Read_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_Read_Via_Cache_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_State_Restore,
    ROM_API_INDEX_XIP_SFlash_State_Save,
    ROM_API_INDEX_XIP_SFlash_Write_Need_Lock,
    ROM_API_INDEX_XIP_SFlash_Opt_Enter,
    ROM_API_INDEX_XIP_SFlash_Opt_Exit,

    ROM_API_INDEX_MD_Clr_GPIO_IntStatus,
    ROM_API_INDEX_MD_Embedded_Flash_Pad_Enable,
    ROM_API_INDEX_MD_GPIO_Clr,
    ROM_API_INDEX_MD_GPIO_Init,
    ROM_API_INDEX_MD_GPIO_Input_Disable,
    ROM_API_INDEX_MD_GPIO_Input_Enable,
    ROM_API_INDEX_MD_GPIO_IntMask,
    ROM_API_INDEX_MD_GPIO_Int_Init,
    ROM_API_INDEX_MD_GPIO_Output_Disable,
    ROM_API_INDEX_MD_GPIO_Output_Enable,
    ROM_API_INDEX_MD_GPIO_Set,
    ROM_API_INDEX_MD_GPIO_Set_HZ,
    ROM_API_INDEX_MD_GPIO_Write,
    ROM_API_INDEX_MD_Get_GPIO_IntStatus,
    ROM_API_INDEX_MD_GPIO_Read,
    ROM_API_INDEX_MD_GPIO_Get_Fun,

    ROM_API_INDEX_FUNC_EMPTY_START,

    ROM_API_INDEX_FUNC_EMPTY_END = ROMAPI_INDEX_MAX

} ROM_API_INDEX_e;

/*@} end of group ROMDRIVER_Public_Types */

/** @defgroup  ROMDRIVER_Public_Constants
 *  @{
 */

/*@} end of group ROMDRIVER_Public_Constants */

/** @defgroup  ROMDRIVER_Public_Macros
 *  @{
 */


#define ROM_APITABLE            ((uint32_t *)0x90015800)


#define RomDriver_AON_Power_Off_BG                        \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Power_Off_BG])

#define RomDriver_AON_Power_Off_LDO15_RF                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Power_Off_LDO15_RF])

#define RomDriver_AON_Power_Off_MBG                       \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Power_Off_MBG])

#define RomDriver_AON_Power_Off_SFReg                     \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Power_Off_SFReg])

#define RomDriver_AON_Power_Off_XTAL                      \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Power_Off_XTAL])

#define RomDriver_AON_Power_On_BG                         \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Power_On_BG])

#define RomDriver_AON_Power_On_LDO15_RF                   \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Power_On_LDO15_RF])

#define RomDriver_AON_Power_On_MBG                        \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Power_On_MBG])

#define RomDriver_AON_Power_On_SFReg                      \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Power_On_SFReg])

#define RomDriver_AON_Power_On_XTAL                       \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Power_On_XTAL])

#define RomDriver_AON_Set_Xtal_CapCode                    \
    ((BL_Err_Type (*) (uint8_t capIn, uint8_t capOut))ROM_APITABLE[ROM_API_INDEX_AON_Set_Xtal_CapCode])

#define RomDriver_AON_Trim_DcdcDis                        \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Trim_DcdcDis])

#define RomDriver_AON_Trim_DcdcVoutSel                    \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Trim_DcdcVoutSel])

#define RomDriver_AON_Trim_DcdcVoutTrim                   \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Trim_DcdcVoutTrim])

#define RomDriver_AON_Trim_Ldo11socVoutTrim               \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Trim_Ldo11socVoutTrim])

#define RomDriver_AON_Trim_Usb20RcalCode                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Trim_Usb20RcalCode])

#define RomDriver_AON_Get_Xtal_CapCode                    \
    ((uint8_t (*) (void))ROM_APITABLE[ROM_API_INDEX_AON_Get_Xtal_CapCode])

#define RomDriver_CPU_MTimer_Delay_MS                     \
    ((BL_Err_Type (*) (uint32_t cnt))ROM_APITABLE[ROM_API_INDEX_CPU_MTimer_Delay_MS])

#define RomDriver_CPU_MTimer_Delay_US                     \
    ((BL_Err_Type (*) (uint32_t cnt))ROM_APITABLE[ROM_API_INDEX_CPU_MTimer_Delay_US])

#define RomDriver_CPU_Reset_MTimer                        \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_CPU_Reset_MTimer])

#define RomDriver_CPU_Set_MTimer_CLK                      \
    ((BL_Err_Type (*) (uint8_t enable, BL_MTimer_Source_Clock_Type mTimerSourceClockType, uint16_t div))ROM_APITABLE[ROM_API_INDEX_CPU_Set_MTimer_CLK])

#define RomDriver_CPU_Set_MTimer_RST                      \
    ((BL_Err_Type (*) (uint8_t rstEn))ROM_APITABLE[ROM_API_INDEX_CPU_Set_MTimer_RST])

#define RomDriver_CPU_Get_MTimer_Clock                    \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_CPU_Get_MTimer_Clock])

#define RomDriver_CPU_Get_MTimer_Source_Clock             \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_CPU_Get_MTimer_Source_Clock])

#define RomDriver_Clock_Audio_ADC_Clock_Get               \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_Clock_Audio_ADC_Clock_Get])

#define RomDriver_Clock_Get_ISP_Clk                       \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_Clock_Get_ISP_Clk])

#define RomDriver_Clock_Get_PSRAMB_Clk                    \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_Clock_Get_PSRAMB_Clk])

#define RomDriver_Clock_Peripheral_Clock_Get              \
    ((uint32_t (*) (BL_Peripheral_Type type))ROM_APITABLE[ROM_API_INDEX_Clock_Peripheral_Clock_Get])

#define RomDriver_Clock_System_Clock_Get                  \
    ((uint32_t (*) (BL_System_Clock_Type type))ROM_APITABLE[ROM_API_INDEX_Clock_System_Clock_Get])

#define RomDriver_SystemCoreClockGet                      \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_SystemCoreClockGet])

#define RomDriver_CPU_Get_CPU_Cycle                       \
    ((uint64_t (*) (void))ROM_APITABLE[ROM_API_INDEX_CPU_Get_CPU_Cycle])

#define RomDriver_CPU_Get_MTimer_Counter                  \
    ((uint64_t (*) (void))ROM_APITABLE[ROM_API_INDEX_CPU_Get_MTimer_Counter])

#define RomDriver_CPU_Get_MTimer_MS                       \
    ((uint64_t (*) (void))ROM_APITABLE[ROM_API_INDEX_CPU_Get_MTimer_MS])

#define RomDriver_CPU_Get_MTimer_US                       \
    ((uint64_t (*) (void))ROM_APITABLE[ROM_API_INDEX_CPU_Get_MTimer_US])

#define RomDriver_EF_Ctrl_Crc_Result                      \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Crc_Result])

#define RomDriver_EF_Ctrl_Get_Customer_PIDVID             \
    ((BL_Err_Type (*) (uint16_t pid[1], uint16_t vid[1]))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Get_Customer_PIDVID])

#define RomDriver_EF_Ctrl_Read_Chip_ID                    \
    ((BL_Err_Type (*) (uint8_t chipID[8]))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Chip_ID])

#define RomDriver_EF_Ctrl_Read_MAC_Address                \
    ((BL_Err_Type (*) (uint8_t mac[6]))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_MAC_Address])

#define RomDriver_EF_Ctrl_Read_MAC_Address_Raw            \
    ((BL_Err_Type (*) (uint8_t mac[7]))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_MAC_Address_Raw])

#define RomDriver_EF_Ctrl_AutoLoad_Done                   \
    ((BL_Sts_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_AutoLoad_Done])

#define RomDriver_EF_Ctrl_Busy                            \
    ((BL_Sts_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Busy])

#define RomDriver_EF_Ctrl_Crc_Is_Busy                     \
    ((BL_Sts_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Crc_Is_Busy])

#define RomDriver_EF_Ctrl_Get_Trim_Parity                 \
    ((uint8_t (*) (uint32_t val, uint8_t len))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Get_Trim_Parity])

#define RomDriver_EF_Ctrl_Is_All_Bits_Zero                \
    ((uint8_t (*) (uint32_t val, uint8_t start, uint8_t len))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Is_All_Bits_Zero])

#define RomDriver_EF_Ctrl_Read_FlashDlyCoe                \
    ((uint8_t (*) (void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_FlashDlyCoe])

#define RomDriver_EF_Ctrl_Clear                           \
    ((void (*) (uint32_t index, uint32_t len))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Clear])

#define RomDriver_EF_Ctrl_Crc_Enable                      \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Crc_Enable])

#define RomDriver_EF_Ctrl_Crc_Set_Golden                  \
    ((void (*) (uint32_t goldenValue))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Crc_Set_Golden])

#define RomDriver_EF_Ctrl_Load_Efuse_R0                   \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Load_Efuse_R0])

#define RomDriver_EF_Ctrl_Program_Direct_R0               \
    ((void (*) (uint32_t index, uint32_t *data, uint32_t len))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Program_Direct_R0])

#define RomDriver_EF_Ctrl_Program_Efuse_0                 \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Program_Efuse_0])

#define RomDriver_EF_Ctrl_Read_ADC_Gain_Trim              \
    ((void (*) (Efuse_ADC_Gain_Coeff_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_ADC_Gain_Trim])

#define RomDriver_EF_Ctrl_Read_AES_Key                    \
    ((void (*) (uint8_t index, uint32_t *keyData, uint32_t len))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_AES_Key])

#define RomDriver_EF_Ctrl_Read_Dbg_Pwd                    \
    ((void (*) (uint8_t slot, uint32_t *passWdLow, uint32_t *passWdHigh))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Dbg_Pwd])

#define RomDriver_EF_Ctrl_Read_DcdcDis_Trim               \
    ((void (*) (Efuse_Ana_DcdcDis_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_DcdcDis_Trim])

#define RomDriver_EF_Ctrl_Read_DcdcVoutSel_Trim           \
    ((void (*) (Efuse_Ana_DcdcVoutSel_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_DcdcVoutSel_Trim])

#define RomDriver_EF_Ctrl_Read_DcdcVoutTrim_Trim          \
    ((void (*) (Efuse_Ana_DcdcVoutTrim_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_DcdcVoutTrim_Trim])

#define RomDriver_EF_Ctrl_Read_Device_Info                \
    ((void (*) (Efuse_Device_Info_Type *deviceInfo))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Device_Info])

#define RomDriver_EF_Ctrl_Read_Direct_R0                  \
    ((void (*) (uint32_t index, uint32_t *data, uint32_t len))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Direct_R0])

#define RomDriver_EF_Ctrl_Read_Ldo11socVoutTrim_Trim      \
    ((void (*) (Efuse_Ana_Ldo11socVoutTrim_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Ldo11socVoutTrim_Trim])

#define RomDriver_EF_Ctrl_Read_Ldo18ioBypass_Trim         \
    ((void (*) (Efuse_Ana_Ldo18ioBypass_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Ldo18ioBypass_Trim])

#define RomDriver_EF_Ctrl_Read_Ldo18ioVoutSel_Trim        \
    ((void (*) (Efuse_Ana_Ldo18ioVoutSel_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Ldo18ioVoutSel_Trim])

#define RomDriver_EF_Ctrl_Read_Ldo18ioVoutTrim_Trim       \
    ((void (*) (Efuse_Ana_Ldo18ioVoutTrim_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Ldo18ioVoutTrim_Trim])

#define RomDriver_EF_Ctrl_Read_Ldo33VoutTrim_Trim         \
    ((void (*) (Efuse_Ana_Ldo33VoutTrim_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Ldo33VoutTrim_Trim])

#define RomDriver_EF_Ctrl_Read_RC32K_Trim                 \
    ((void (*) (Efuse_Ana_RC32K_Trim_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_RC32K_Trim])

#define RomDriver_EF_Ctrl_Read_RC32M_Trim                 \
    ((void (*) (Efuse_Ana_RC32M_Trim_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_RC32M_Trim])

#define RomDriver_EF_Ctrl_Read_Secure_Boot                \
    ((void (*) (EF_Ctrl_SF_AES_Type aes[2]))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Secure_Boot])

#define RomDriver_EF_Ctrl_Read_Secure_Cfg                 \
    ((void (*) (EF_Ctrl_Sec_Param_Type *cfg))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Secure_Cfg])

#define RomDriver_EF_Ctrl_Read_Sw_Usage                   \
    ((void (*) (uint32_t index, uint32_t *usage))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Sw_Usage])

#define RomDriver_EF_Ctrl_Read_TSEN_Trim                  \
    ((void (*) (Efuse_TSEN_Refcode_Corner_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_TSEN_Trim])

#define RomDriver_EF_Ctrl_Read_Usb20RcalCode_Trim         \
    ((void (*) (Efuse_Ana_Usb20RcalCode_Type *trim))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Read_Usb20RcalCode_Trim])

#define RomDriver_EF_Ctrl_Readlock_AES_Key                \
    ((void (*) (uint8_t index, uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Readlock_AES_Key])

#define RomDriver_EF_Ctrl_Readlock_Dbg_Pwd                \
    ((void (*) (uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Readlock_Dbg_Pwd])

#define RomDriver_EF_Ctrl_Set_sf_key_re_sel               \
    ((void (*) (uint8_t ef_sf_key_re_sel))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Set_sf_key_re_sel])

#define RomDriver_EF_Ctrl_Sw_AHB_Clk_0                    \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Sw_AHB_Clk_0])

#define RomDriver_EF_Ctrl_Write_AES_Key                   \
    ((void (*) (uint8_t index, uint32_t *keyData, uint32_t len, uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Write_AES_Key])

#define RomDriver_EF_Ctrl_Write_Dbg_Pwd                   \
    ((void (*) (uint8_t slot, uint32_t passWdLow, uint32_t passWdHigh, uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Write_Dbg_Pwd])

#define RomDriver_EF_Ctrl_Write_MAC_Address               \
    ((void (*) (uint8_t mac[6], uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Write_MAC_Address])

#define RomDriver_EF_Ctrl_Write_Secure_Boot               \
    ((void (*) (EF_Ctrl_Sign_Type sign[1], EF_Ctrl_SF_AES_Type aes[1], uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Write_Secure_Boot])

#define RomDriver_EF_Ctrl_Write_Secure_Cfg                \
    ((void (*) (EF_Ctrl_Sec_Param_Type *cfg, uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Write_Secure_Cfg])

#define RomDriver_EF_Ctrl_Write_Sw_Usage                  \
    ((void (*) (uint32_t index, uint32_t usage, uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Write_Sw_Usage])

#define RomDriver_EF_Ctrl_Writelock_AES_Key               \
    ((void (*) (uint8_t index, uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Writelock_AES_Key])

#define RomDriver_EF_Ctrl_Writelock_Dbg_Pwd               \
    ((void (*) (uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Writelock_Dbg_Pwd])

#define RomDriver_EF_Ctrl_Writelock_MAC_Address           \
    ((void (*) (uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Writelock_MAC_Address])

#define RomDriver_EF_Ctrl_Writelock_Sw_Usage              \
    ((void (*) (uint32_t index, uint8_t program))ROM_APITABLE[ROM_API_INDEX_EF_Ctrl_Writelock_Sw_Usage])

#define RomDriver_GLB_AHB_MCU_Software_Reset              \
    ((BL_Err_Type (*) (GLB_AHB_MCU_SW_Type swrst))ROM_APITABLE[ROM_API_INDEX_GLB_AHB_MCU_Software_Reset])

#define RomDriver_GLB_AUPLL_Ref_Clk_Sel                   \
    ((BL_Err_Type (*) (GLB_PLL_REF_CLK_Type refClk))ROM_APITABLE[ROM_API_INDEX_GLB_AUPLL_Ref_Clk_Sel])

#define RomDriver_GLB_BMX_TO_Init                         \
    ((BL_Err_Type (*) (BMX_TO_Cfg_Type *BmxCfg))ROM_APITABLE[ROM_API_INDEX_GLB_BMX_TO_Init])

#define RomDriver_GLB_Clr_BMX_TO_Status                   \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Clr_BMX_TO_Status])

#define RomDriver_GLB_Clr_EMI_Reset_Gate                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Clr_EMI_Reset_Gate])

#define RomDriver_GLB_Clr_Reset_Reason                    \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Clr_Reset_Reason])

#define RomDriver_GLB_Config_SDIO_Host_Interrupt_CPU      \
    ((BL_Err_Type (*) (uint8_t enable))ROM_APITABLE[ROM_API_INDEX_GLB_Config_SDIO_Host_Interrupt_CPU])

#define RomDriver_GLB_Config_SDIO_Host_Reset_SDU          \
    ((BL_Err_Type (*) (uint8_t enable))ROM_APITABLE[ROM_API_INDEX_GLB_Config_SDIO_Host_Reset_SDU])

#define RomDriver_GLB_Config_SDIO_Host_Reset_System       \
    ((BL_Err_Type (*) (uint8_t enable))ROM_APITABLE[ROM_API_INDEX_GLB_Config_SDIO_Host_Reset_System])

#define RomDriver_GLB_Get_Auto_Calc_Xtal_Type             \
    ((BL_Err_Type (*) (GLB_XTAL_Type *calcXtalType))ROM_APITABLE[ROM_API_INDEX_GLB_Get_Auto_Calc_Xtal_Type])

#define RomDriver_GLB_Get_MCU_System_CLK_Div              \
    ((BL_Err_Type (*) (uint8_t *mcuClkDiv, uint8_t *mcuPBclkDiv))ROM_APITABLE[ROM_API_INDEX_GLB_Get_MCU_System_CLK_Div])

#define RomDriver_GLB_Get_Reset_Reason                    \
    ((BL_Err_Type (*) (GLB_RESET_RECORD_Type *reason))ROM_APITABLE[ROM_API_INDEX_GLB_Get_Reset_Reason])

#define RomDriver_GLB_IR_RX_GPIO_Sel                      \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpio))ROM_APITABLE[ROM_API_INDEX_GLB_IR_RX_GPIO_Sel])

#define RomDriver_GLB_Invert_ETH_REF_O_CLK                \
    ((BL_Err_Type (*) (uint8_t enable))ROM_APITABLE[ROM_API_INDEX_GLB_Invert_ETH_REF_O_CLK])

#define RomDriver_GLB_Invert_ETH_RX_CLK                   \
    ((BL_Err_Type (*) (uint8_t enable))ROM_APITABLE[ROM_API_INDEX_GLB_Invert_ETH_RX_CLK])

#define RomDriver_GLB_Invert_ETH_TX_CLK                   \
    ((BL_Err_Type (*) (uint8_t enable))ROM_APITABLE[ROM_API_INDEX_GLB_Invert_ETH_TX_CLK])

#define RomDriver_GLB_MCU_SW_System_Reset                 \
    ((BL_Err_Type (*) (GLB_MCU_SW_SYSTEM_Type sysPart))ROM_APITABLE[ROM_API_INDEX_GLB_MCU_SW_System_Reset])

#define RomDriver_GLB_PER_Clock_Gate                      \
    ((BL_Err_Type (*) (uint64_t ips))ROM_APITABLE[ROM_API_INDEX_GLB_PER_Clock_Gate])

#define RomDriver_GLB_PER_Clock_UnGate                    \
    ((BL_Err_Type (*) (uint64_t ips))ROM_APITABLE[ROM_API_INDEX_GLB_PER_Clock_UnGate])

#define RomDriver_GLB_PLL_CGEN_Clock_Gate                 \
    ((BL_Err_Type (*) (GLB_PLL_CGEN_Type clk))ROM_APITABLE[ROM_API_INDEX_GLB_PLL_CGEN_Clock_Gate])

#define RomDriver_GLB_PLL_CGEN_Clock_UnGate               \
    ((BL_Err_Type (*) (GLB_PLL_CGEN_Type clk))ROM_APITABLE[ROM_API_INDEX_GLB_PLL_CGEN_Clock_UnGate])

#define RomDriver_GLB_Platform_Wakeup_PDS_Enable          \
    ((BL_Err_Type (*) (uint8_t enable))ROM_APITABLE[ROM_API_INDEX_GLB_Platform_Wakeup_PDS_Enable])

#define RomDriver_GLB_Power_Off_AUPLL                     \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Power_Off_AUPLL])

#define RomDriver_GLB_Power_Off_WIFIPLL                   \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Power_Off_WIFIPLL])

#define RomDriver_GLB_Power_On_AUPLL                      \
    ((BL_Err_Type (*) (const GLB_WA_PLL_Cfg_Type *const cfg, uint8_t waitStable))ROM_APITABLE[ROM_API_INDEX_GLB_Power_On_AUPLL])

#define RomDriver_GLB_Power_On_WIFIPLL                    \
    ((BL_Err_Type (*) (const GLB_WA_PLL_Cfg_Type *const cfg, uint8_t waitStable))ROM_APITABLE[ROM_API_INDEX_GLB_Power_On_WIFIPLL])

#define RomDriver_GLB_Power_On_XTAL_And_PLL_CLK           \
    ((BL_Err_Type (*) (GLB_XTAL_Type xtalType, GLB_PLL_Type pllType))ROM_APITABLE[ROM_API_INDEX_GLB_Power_On_XTAL_And_PLL_CLK])

#define RomDriver_GLB_SPI_Sig_Swap_Set                    \
    ((BL_Err_Type (*) (GLB_SPI_SIG_SWAP_GRP_Type group, uint8_t swap))ROM_APITABLE[ROM_API_INDEX_GLB_SPI_Sig_Swap_Set])

#define RomDriver_GLB_SW_CPU_Reset                        \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_SW_CPU_Reset])

#define RomDriver_GLB_SW_POR_Reset                        \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_SW_POR_Reset])

#define RomDriver_GLB_SW_System_Reset                     \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_SW_System_Reset])

#define RomDriver_GLB_Sel_MCU_TMR_GPIO_Clock              \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_Sel_MCU_TMR_GPIO_Clock])

#define RomDriver_GLB_Set_ADC_CLK                         \
    ((BL_Err_Type (*) (uint8_t enable, GLB_ADC_CLK_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_ADC_CLK])

#define RomDriver_GLB_Set_Audio_ADC_CLK                   \
    ((BL_Err_Type (*) (uint8_t enable, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_Audio_ADC_CLK])

#define RomDriver_GLB_Set_Audio_AUTO_CLK                  \
    ((BL_Err_Type (*) (uint8_t divEn))ROM_APITABLE[ROM_API_INDEX_GLB_Set_Audio_AUTO_CLK])

#define RomDriver_GLB_Set_Audio_SOLO_CLK                  \
    ((BL_Err_Type (*) (uint8_t enable, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_Audio_SOLO_CLK])

#define RomDriver_GLB_Set_Auto_Calc_Xtal_Type             \
    ((BL_Err_Type (*) (GLB_XTAL_Type calcXtalType))ROM_APITABLE[ROM_API_INDEX_GLB_Set_Auto_Calc_Xtal_Type])

#define RomDriver_GLB_Set_CAM_CLK                         \
    ((BL_Err_Type (*) (uint8_t enable, GLB_CAM_CLK_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_CAM_CLK])

#define RomDriver_GLB_Set_CPU_Reset_Address               \
    ((BL_Err_Type (*) (GLB_CORE_ID_Type coreID, uint32_t addr))ROM_APITABLE[ROM_API_INDEX_GLB_Set_CPU_Reset_Address])

#define RomDriver_GLB_Set_Chip_Clock_Out_Sel              \
    ((BL_Err_Type (*) (GLB_CHIP_CLK_OUT_CFG_Type *cfg))ROM_APITABLE[ROM_API_INDEX_GLB_Set_Chip_Clock_Out_Sel])

#define RomDriver_GLB_Set_DBI_CLK                         \
    ((BL_Err_Type (*) (uint8_t enable, GLB_DBI_CLK_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_DBI_CLK])

#define RomDriver_GLB_Set_DIG_32K_CLK                     \
    ((BL_Err_Type (*) (uint8_t enable, uint8_t compensationEn, uint16_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_DIG_32K_CLK])

#define RomDriver_GLB_Set_DIG_512K_CLK                    \
    ((BL_Err_Type (*) (uint8_t enable, uint8_t compensationEn, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_DIG_512K_CLK])

#define RomDriver_GLB_Set_DIG_CLK_Sel                     \
    ((BL_Err_Type (*) (GLB_DIG_CLK_Type clkSel))ROM_APITABLE[ROM_API_INDEX_GLB_Set_DIG_CLK_Sel])

#define RomDriver_GLB_Set_DMA_CLK                         \
    ((BL_Err_Type (*) (uint8_t enable, GLB_DMA_CLK_ID_Type clk))ROM_APITABLE[ROM_API_INDEX_GLB_Set_DMA_CLK])

#define RomDriver_GLB_Set_EM_Sel                          \
    ((BL_Err_Type (*) (GLB_EM_Type emType))ROM_APITABLE[ROM_API_INDEX_GLB_Set_EM_Sel])

#define RomDriver_GLB_Set_ETH_REF_O_CLK_Sel               \
    ((BL_Err_Type (*) (GLB_ETH_REF_CLK_OUT_Type clkSel))ROM_APITABLE[ROM_API_INDEX_GLB_Set_ETH_REF_O_CLK_Sel])

#define RomDriver_GLB_Set_I2C_CLK                         \
    ((BL_Err_Type (*) (uint8_t enable, GLB_I2C_CLK_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_I2C_CLK])

#define RomDriver_GLB_Set_I2S_CLK                         \
    ((BL_Err_Type (*) (uint8_t refClkEn, uint8_t refClkDiv, GLB_I2S_DI_REF_CLK_Type inRef, GLB_I2S_DO_REF_CLK_Type outRef))ROM_APITABLE[ROM_API_INDEX_GLB_Set_I2S_CLK])

#define RomDriver_GLB_Set_IR_CLK                          \
    ((BL_Err_Type (*) (uint8_t enable, GLB_IR_CLK_SRC_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_IR_CLK])

#define RomDriver_GLB_Set_ISP_Muxpll_80M_Sel              \
    ((BL_Err_Type (*) (GLB_ISP_MUXPLL_80M_CLK_SEL_Type clkSel))ROM_APITABLE[ROM_API_INDEX_GLB_Set_ISP_Muxpll_80M_Sel])

#define RomDriver_GLB_Set_MCU_Muxpll_160M_Sel             \
    ((BL_Err_Type (*) (GLB_MCU_MUXPLL_160M_CLK_SEL_Type clkSel))ROM_APITABLE[ROM_API_INDEX_GLB_Set_MCU_Muxpll_160M_Sel])

#define RomDriver_GLB_Set_MCU_Muxpll_80M_Sel              \
    ((BL_Err_Type (*) (GLB_MCU_MUXPLL_80M_CLK_SEL_Type clkSel))ROM_APITABLE[ROM_API_INDEX_GLB_Set_MCU_Muxpll_80M_Sel])

#define RomDriver_GLB_Set_MCU_SPI_0_ACT_MOD_Sel           \
    ((BL_Err_Type (*) (GLB_SPI_PAD_ACT_AS_Type mod))ROM_APITABLE[ROM_API_INDEX_GLB_Set_MCU_SPI_0_ACT_MOD_Sel])

#define RomDriver_GLB_Set_MCU_System_CLK                  \
    ((BL_Err_Type (*) (GLB_MCU_SYS_CLK_Type clkFreq))ROM_APITABLE[ROM_API_INDEX_GLB_Set_MCU_System_CLK])

#define RomDriver_GLB_Set_MCU_System_CLK_Div              \
    ((BL_Err_Type (*) (uint8_t mcuClkDiv, uint8_t mcuPBclkDiv))ROM_APITABLE[ROM_API_INDEX_GLB_Set_MCU_System_CLK_Div])

#define RomDriver_GLB_Set_PDM_IO_Sel                      \
    ((BL_Err_Type (*) (GLB_PDM_IO_SEL_Type ioSel))ROM_APITABLE[ROM_API_INDEX_GLB_Set_PDM_IO_Sel])

#define RomDriver_GLB_Set_PKA_CLK_Sel                     \
    ((BL_Err_Type (*) (GLB_PKA_CLK_Type clkSel))ROM_APITABLE[ROM_API_INDEX_GLB_Set_PKA_CLK_Sel])

#define RomDriver_GLB_Set_PSRAMB_CLK_Sel                  \
    ((BL_Err_Type (*) (uint8_t enable, GLB_PSRAMB_PLL_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_PSRAMB_CLK_Sel])

#define RomDriver_GLB_Set_PWM1_IO_Sel                     \
    ((BL_Err_Type (*) (GLB_PWM1_IO_SEL_Type ioSel))ROM_APITABLE[ROM_API_INDEX_GLB_Set_PWM1_IO_Sel])

#define RomDriver_GLB_Set_Peripheral_DMA_CN               \
    ((BL_Err_Type (*) (GLB_PERI_DMA_Type peri, GLB_PERI_DMA_CN_SEL_Type cn))ROM_APITABLE[ROM_API_INDEX_GLB_Set_Peripheral_DMA_CN])

#define RomDriver_GLB_Set_SDH_CLK                         \
    ((BL_Err_Type (*) (uint8_t enable, GLB_SDH_CLK_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_SDH_CLK])

#define RomDriver_GLB_Set_SF_CLK                          \
    ((BL_Err_Type (*) (uint8_t enable, GLB_SFLASH_CLK_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_SF_CLK])

#define RomDriver_GLB_Set_SFlash2_IO_PARM                 \
    ((BL_Err_Type (*) (uint8_t swapIo3Io0))ROM_APITABLE[ROM_API_INDEX_GLB_Set_SFlash2_IO_PARM])

#define RomDriver_GLB_Set_SFlash_IO_PARM                  \
    ((BL_Err_Type (*) (uint8_t selEmbedded, uint8_t swapIo3Io0, uint8_t swapIo2Cs))ROM_APITABLE[ROM_API_INDEX_GLB_Set_SFlash_IO_PARM])

#define RomDriver_GLB_Set_SPI_CLK                         \
    ((BL_Err_Type (*) (uint8_t enable, GLB_SPI_CLK_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_SPI_CLK])

#define RomDriver_GLB_Set_SRAM_PARM                       \
    ((BL_Err_Type (*) (uint32_t value))ROM_APITABLE[ROM_API_INDEX_GLB_Set_SRAM_PARM])

#define RomDriver_GLB_Set_SRAM_RET                        \
    ((BL_Err_Type (*) (uint32_t value))ROM_APITABLE[ROM_API_INDEX_GLB_Set_SRAM_RET])

#define RomDriver_GLB_Set_SRAM_SLP                        \
    ((BL_Err_Type (*) (uint32_t value))ROM_APITABLE[ROM_API_INDEX_GLB_Set_SRAM_SLP])

#define RomDriver_GLB_Set_SSC_CLK_From_WIFIPLL            \
    ((BL_Err_Type (*) (uint8_t enable))ROM_APITABLE[ROM_API_INDEX_GLB_Set_SSC_CLK_From_WIFIPLL])

#define RomDriver_GLB_Set_Slave_Grp_0_CLK                 \
    ((BL_Err_Type (*) (GLB_SLAVE_GRP_0_Type slave, uint8_t enable, GLB_SLAVE_GRP_0_CLK_SEL_Type clkSel, uint32_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_Slave_Grp_0_CLK])

#define RomDriver_GLB_Set_UART_CLK                        \
    ((BL_Err_Type (*) (uint8_t enable, HBN_UART_CLK_Type clkSel, uint8_t div))ROM_APITABLE[ROM_API_INDEX_GLB_Set_UART_CLK])

#define RomDriver_GLB_Set_USB_CLK_From_WIFIPLL            \
    ((BL_Err_Type (*) (uint8_t enable))ROM_APITABLE[ROM_API_INDEX_GLB_Set_USB_CLK_From_WIFIPLL])

#define RomDriver_GLB_Swap_MCU_SPI_0_MOSI_With_MISO       \
    ((BL_Err_Type (*) (BL_Fun_Type newState))ROM_APITABLE[ROM_API_INDEX_GLB_Swap_MCU_SPI_0_MOSI_With_MISO])

#define RomDriver_GLB_Trim_Ldo18ioBypass                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Trim_Ldo18ioBypass])

#define RomDriver_GLB_Trim_Ldo18ioVoutSel                 \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Trim_Ldo18ioVoutSel])

#define RomDriver_GLB_Trim_Ldo18ioVoutTrim                \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Trim_Ldo18ioVoutTrim])

#define RomDriver_GLB_UART_Fun_Sel                        \
    ((BL_Err_Type (*) (GLB_UART_SIG_Type sig, GLB_UART_SIG_FUN_Type fun))ROM_APITABLE[ROM_API_INDEX_GLB_UART_Fun_Sel])

#define RomDriver_GLB_UART_Sig_Swap_Set                   \
    ((BL_Err_Type (*) (GLB_UART_SIG_SWAP_GRP_Type group, uint8_t swap))ROM_APITABLE[ROM_API_INDEX_GLB_UART_Sig_Swap_Set])

#define RomDriver_GLB_WIFIPLL_Ref_Clk_Sel                 \
    ((BL_Err_Type (*) (GLB_PLL_REF_CLK_Type refClk))ROM_APITABLE[ROM_API_INDEX_GLB_WIFIPLL_Ref_Clk_Sel])

#define RomDriver_GLB_Get_Core_Type                       \
    ((GLB_CORE_ID_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Get_Core_Type])

#define RomDriver_GLB_Get_MCU_Muxpll_160M_Sel             \
    ((GLB_MCU_MUXPLL_160M_CLK_SEL_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Get_MCU_Muxpll_160M_Sel])

#define RomDriver_GLB_Get_MCU_Muxpll_80M_Sel              \
    ((GLB_MCU_MUXPLL_80M_CLK_SEL_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Get_MCU_Muxpll_80M_Sel])

#define RomDriver_GLB_Get_SRAM_PARM                       \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Get_SRAM_PARM])

#define RomDriver_GLB_Get_SRAM_RET                        \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Get_SRAM_RET])

#define RomDriver_GLB_Get_SRAM_SLP                        \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Get_SRAM_SLP])

#define RomDriver_GLB_Get_BMX_TO_Status                   \
    ((uint8_t (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_Get_BMX_TO_Status])

#define RomDriver_GLB_Clr_GPIO_IntStatus                  \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_Clr_GPIO_IntStatus])

#define RomDriver_GLB_Embedded_Flash_Pad_Enable           \
    ((BL_Err_Type (*) (uint8_t swapIo2Cs))ROM_APITABLE[ROM_API_INDEX_GLB_Embedded_Flash_Pad_Enable])

#define RomDriver_GLB_GPIO_Clr                            \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Clr])

#define RomDriver_GLB_GPIO_Fifo_Clear                     \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Fifo_Clear])

#define RomDriver_GLB_GPIO_Fifo_Init                      \
    ((BL_Err_Type (*) (GLB_GPIO_FIFO_CFG_Type *cfg))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Fifo_Init])

#define RomDriver_GLB_GPIO_Fifo_IntClear                  \
    ((BL_Err_Type (*) (GLB_GPIO_FIFO_INT_Type intType))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Fifo_IntClear])

#define RomDriver_GLB_GPIO_Fifo_IntMask                   \
    ((BL_Err_Type (*) (GLB_GPIO_FIFO_INT_Type intType, BL_Mask_Type intMask))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Fifo_IntMask])

#define RomDriver_GLB_GPIO_Fifo_Push                      \
    ((BL_Err_Type (*) (uint16_t *data, uint16_t len))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Fifo_Push])

#define RomDriver_GLB_GPIO_Func_Init                      \
    ((BL_Err_Type (*) (GLB_GPIO_FUNC_Type gpioFun, GLB_GPIO_Type *pinList, uint8_t cnt))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Func_Init])

#define RomDriver_GLB_GPIO_Init                           \
    ((BL_Err_Type (*) (GLB_GPIO_Cfg_Type *cfg))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Init])

#define RomDriver_GLB_GPIO_Input_Disable                  \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Input_Disable])

#define RomDriver_GLB_GPIO_Input_Enable                   \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Input_Enable])

#define RomDriver_GLB_GPIO_IntMask                        \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin, BL_Mask_Type intMask))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_IntMask])

#define RomDriver_GLB_GPIO_Int_Init                       \
    ((BL_Err_Type (*) (GLB_GPIO_INT_Cfg_Type *intCfg))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Int_Init])

#define RomDriver_GLB_GPIO_Output_Disable                 \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Output_Disable])

#define RomDriver_GLB_GPIO_Output_Enable                  \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Output_Enable])

#define RomDriver_GLB_GPIO_Set                            \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Set])

#define RomDriver_GLB_GPIO_Set_HZ                         \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Set_HZ])

#define RomDriver_GLB_GPIO_Write                          \
    ((BL_Err_Type (*) (GLB_GPIO_Type gpioPin, uint32_t val))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Write])

#define RomDriver_GLB_GPIO_Fifo_Disable                   \
    ((BL_Sts_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Fifo_Disable])

#define RomDriver_GLB_GPIO_Fifo_Enable                    \
    ((BL_Sts_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Fifo_Enable])

#define RomDriver_GLB_GPIO_Fifo_GetIntStatus              \
    ((BL_Sts_Type (*) (GLB_GPIO_FIFO_INT_Type intType))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Fifo_GetIntStatus])

#define RomDriver_GLB_Get_GPIO_IntStatus                  \
    ((BL_Sts_Type (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_Get_GPIO_IntStatus])

#define RomDriver_GLB_GPIO_Fifo_GetCount                  \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Fifo_GetCount])

#define RomDriver_GLB_GPIO_Read                           \
    ((uint32_t (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Read])

#define RomDriver_GLB_GPIO_Get_Fun                        \
    ((uint8_t (*) (GLB_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_GLB_GPIO_Get_Fun])

#define RomDriver_HBN_32K_Sel                             \
    ((BL_Err_Type (*) (HBN_32K_CLK_Type clkType))ROM_APITABLE[ROM_API_INDEX_HBN_32K_Sel])

#define RomDriver_HBN_Aon_Pad_Cfg                         \
    ((BL_Err_Type (*) (uint8_t aonPadHwCtrlEn, HBN_AON_PAD_Type aonGpio, HBN_AON_PAD_CFG_Type *aonPadCfg))ROM_APITABLE[ROM_API_INDEX_HBN_Aon_Pad_Cfg])

#define RomDriver_HBN_Aon_Pad_Cfg_Set                     \
    ((BL_Err_Type (*) (uint8_t aonPadHwCtrlEn, HBN_AON_PAD_Type aonGpio))ROM_APITABLE[ROM_API_INDEX_HBN_Aon_Pad_Cfg_Set])

#define RomDriver_HBN_Aon_Pad_Ctrl                        \
    ((BL_Err_Type (*) (uint32_t aonPadCtl1, uint32_t aonPadCtl2))ROM_APITABLE[ROM_API_INDEX_HBN_Aon_Pad_Ctrl])

#define RomDriver_HBN_Aon_Pad_WakeUpCfg                   \
    ((BL_Err_Type (*) (BL_Fun_Type puPdEn, HBN_GPIO_INT_Trigger_Type trigMode, uint32_t maskVal, BL_Fun_Type dlyEn, uint8_t dlySec))ROM_APITABLE[ROM_API_INDEX_HBN_Aon_Pad_WakeUpCfg])

#define RomDriver_HBN_Clear_Gpio_Keep                     \
    ((BL_Err_Type (*) (uint8_t gpioKeep))ROM_APITABLE[ROM_API_INDEX_HBN_Clear_Gpio_Keep])

#define RomDriver_HBN_Clear_IRQ                           \
    ((BL_Err_Type (*) (HBN_INT_Type irqType))ROM_APITABLE[ROM_API_INDEX_HBN_Clear_IRQ])

#define RomDriver_HBN_Clear_PDS_Gpio_Keep                 \
    ((BL_Err_Type (*) (uint8_t gpioKeep))ROM_APITABLE[ROM_API_INDEX_HBN_Clear_PDS_Gpio_Keep])

#define RomDriver_HBN_Clear_RTC_Counter                   \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Clear_RTC_Counter])

#define RomDriver_HBN_Clear_RTC_INT                       \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Clear_RTC_INT])

#define RomDriver_HBN_Disable_AComp0_IRQ                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Disable_AComp0_IRQ])

#define RomDriver_HBN_Disable_AComp1_IRQ                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Disable_AComp1_IRQ])

#define RomDriver_HBN_Disable_BOD_IRQ                     \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Disable_BOD_IRQ])

#define RomDriver_HBN_Enable_AComp0_IRQ                   \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Enable_AComp0_IRQ])

#define RomDriver_HBN_Enable_AComp1_IRQ                   \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Enable_AComp1_IRQ])

#define RomDriver_HBN_Enable_BOD_IRQ                      \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Enable_BOD_IRQ])

#define RomDriver_HBN_Enable_RTC_Counter                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Enable_RTC_Counter])

#define RomDriver_HBN_GPIO_INT_Disable                    \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_GPIO_INT_Disable])

#define RomDriver_HBN_GPIO_INT_Enable                     \
    ((BL_Err_Type (*) (HBN_GPIO_INT_Trigger_Type gpioIntTrigType))ROM_APITABLE[ROM_API_INDEX_HBN_GPIO_INT_Enable])

#define RomDriver_HBN_Get_Flash_Power_Delay               \
    ((BL_Err_Type (*) (uint8_t *flashPwrDly))ROM_APITABLE[ROM_API_INDEX_HBN_Get_Flash_Power_Delay])

#define RomDriver_HBN_Get_Gpio_Keep                       \
    ((BL_Err_Type (*) (uint8_t *gpioKeep))ROM_APITABLE[ROM_API_INDEX_HBN_Get_Gpio_Keep])

#define RomDriver_HBN_Get_Ldo18io_Power_Delay_Config      \
    ((BL_Err_Type (*) (uint16_t *pwrOffDly, uint16_t *pwrOnDly))ROM_APITABLE[ROM_API_INDEX_HBN_Get_Ldo18io_Power_Delay_Config])

#define RomDriver_HBN_Get_PDS_Gpio_Keep                   \
    ((BL_Err_Type (*) (uint8_t *gpioKeep))ROM_APITABLE[ROM_API_INDEX_HBN_Get_PDS_Gpio_Keep])

#define RomDriver_HBN_Get_RTC_Timer_Val                   \
    ((BL_Err_Type (*) (uint32_t *valLow, uint32_t *valHigh))ROM_APITABLE[ROM_API_INDEX_HBN_Get_RTC_Timer_Val])

#define RomDriver_HBN_Get_Xtal_Type                       \
    ((BL_Err_Type (*) (uint8_t *xtalType))ROM_APITABLE[ROM_API_INDEX_HBN_Get_Xtal_Type])

#define RomDriver_HBN_Hw_Pu_Pd_Cfg                        \
    ((BL_Err_Type (*) (uint8_t enable))ROM_APITABLE[ROM_API_INDEX_HBN_Hw_Pu_Pd_Cfg])

#define RomDriver_HBN_Keep_On_RC32K                       \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Keep_On_RC32K])

#define RomDriver_HBN_PIR_Disable                         \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_PIR_Disable])

#define RomDriver_HBN_PIR_Enable                          \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_PIR_Enable])

#define RomDriver_HBN_PIR_HPF_Sel                         \
    ((BL_Err_Type (*) (HBN_PIR_HPF_Type hpf))ROM_APITABLE[ROM_API_INDEX_HBN_PIR_HPF_Sel])

#define RomDriver_HBN_PIR_INT_Config                      \
    ((BL_Err_Type (*) (HBN_PIR_INT_CFG_Type *pirIntCfg))ROM_APITABLE[ROM_API_INDEX_HBN_PIR_INT_Config])

#define RomDriver_HBN_PIR_LPF_Sel                         \
    ((BL_Err_Type (*) (HBN_PIR_LPF_Type lpf))ROM_APITABLE[ROM_API_INDEX_HBN_PIR_LPF_Sel])

#define RomDriver_HBN_Pin_WakeUp_Mask                     \
    ((BL_Err_Type (*) (uint8_t maskVal))ROM_APITABLE[ROM_API_INDEX_HBN_Pin_WakeUp_Mask])

#define RomDriver_HBN_Power_Off_RC32K                     \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Power_Off_RC32K])

#define RomDriver_HBN_Power_Off_Xtal_32K                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Power_Off_Xtal_32K])

#define RomDriver_HBN_Power_On_Xtal_32K                   \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Power_On_Xtal_32K])

#define RomDriver_HBN_Reset                               \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Reset])

#define RomDriver_HBN_Set_BOD_Cfg                         \
    ((BL_Err_Type (*) (HBN_BOD_CFG_Type *cfg))ROM_APITABLE[ROM_API_INDEX_HBN_Set_BOD_Cfg])

#define RomDriver_HBN_Set_BOD_Config                      \
    ((BL_Err_Type (*) (uint8_t enable, HBN_BOD_THRES_Type threshold, HBN_BOD_MODE_Type mode))ROM_APITABLE[ROM_API_INDEX_HBN_Set_BOD_Config])

#define RomDriver_HBN_Set_Core_Reboot_Config              \
    ((BL_Err_Type (*) (uint8_t core, uint8_t hcfg))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Core_Reboot_Config])

#define RomDriver_HBN_Set_Flash_Power_Delay               \
    ((BL_Err_Type (*) (uint8_t flashPwrDly))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Flash_Power_Delay])

#define RomDriver_HBN_Set_GPADC_CLK_Sel                   \
    ((BL_Err_Type (*) (HBN_GPADC_CLK_Type clkSel))ROM_APITABLE[ROM_API_INDEX_HBN_Set_GPADC_CLK_Sel])

#define RomDriver_HBN_Set_Gpio_Keep                       \
    ((BL_Err_Type (*) (uint8_t gpioKeep))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Gpio_Keep])

#define RomDriver_HBN_Set_HRAM_Ret                        \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Set_HRAM_Ret])

#define RomDriver_HBN_Set_HRAM_slp                        \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Set_HRAM_slp])

#define RomDriver_HBN_Set_Ldo11_All_Vout                  \
    ((BL_Err_Type (*) (HBN_LDO_LEVEL_Type ldoLevel))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Ldo11_All_Vout])

#define RomDriver_HBN_Set_Ldo11_Aon_Vout                  \
    ((BL_Err_Type (*) (HBN_LDO_LEVEL_Type ldoLevel))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Ldo11_Aon_Vout])

#define RomDriver_HBN_Set_Ldo11_Rt_Vout                   \
    ((BL_Err_Type (*) (HBN_LDO_LEVEL_Type ldoLevel))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Ldo11_Rt_Vout])

#define RomDriver_HBN_Set_Ldo11_Soc_Vout                  \
    ((BL_Err_Type (*) (HBN_LDO_LEVEL_Type ldoLevel))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Ldo11_Soc_Vout])

#define RomDriver_HBN_Set_Ldo18io_Power_Delay_Config      \
    ((BL_Err_Type (*) (uint16_t pwrOffDly, uint16_t pwrOnDly))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Ldo18io_Power_Delay_Config])

#define RomDriver_HBN_Set_MCU_Root_CLK_Sel                \
    ((BL_Err_Type (*) (HBN_MCU_ROOT_CLK_Type rootClk))ROM_APITABLE[ROM_API_INDEX_HBN_Set_MCU_Root_CLK_Sel])

#define RomDriver_HBN_Set_MCU_XCLK_Sel                    \
    ((BL_Err_Type (*) (HBN_MCU_XCLK_Type xclk))ROM_APITABLE[ROM_API_INDEX_HBN_Set_MCU_XCLK_Sel])

#define RomDriver_HBN_Set_PDS_Gpio_Keep                   \
    ((BL_Err_Type (*) (uint8_t gpioKeep))ROM_APITABLE[ROM_API_INDEX_HBN_Set_PDS_Gpio_Keep])

#define RomDriver_HBN_Set_PIR_Interval                    \
    ((BL_Err_Type (*) (uint16_t interval))ROM_APITABLE[ROM_API_INDEX_HBN_Set_PIR_Interval])

#define RomDriver_HBN_Set_PIR_Threshold                   \
    ((BL_Err_Type (*) (uint16_t threshold))ROM_APITABLE[ROM_API_INDEX_HBN_Set_PIR_Threshold])

#define RomDriver_HBN_Set_RTC_Timer                       \
    ((BL_Err_Type (*) (HBN_RTC_INT_Delay_Type delay, uint32_t compValLow, uint32_t compValHigh, uint8_t compMode))ROM_APITABLE[ROM_API_INDEX_HBN_Set_RTC_Timer])

#define RomDriver_HBN_Set_Status_Flag                     \
    ((BL_Err_Type (*) (uint32_t flag))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Status_Flag])

#define RomDriver_HBN_Set_UART_CLK_Sel                    \
    ((BL_Err_Type (*) (HBN_UART_CLK_Type clkSel))ROM_APITABLE[ROM_API_INDEX_HBN_Set_UART_CLK_Sel])

#define RomDriver_HBN_Set_User_Boot_Config                \
    ((BL_Err_Type (*) (uint8_t ubCfg))ROM_APITABLE[ROM_API_INDEX_HBN_Set_User_Boot_Config])

#define RomDriver_HBN_Set_Wakeup_Addr                     \
    ((BL_Err_Type (*) (uint32_t addr))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Wakeup_Addr])

#define RomDriver_HBN_Set_Xtal_Type                       \
    ((BL_Err_Type (*) (uint8_t xtalType))ROM_APITABLE[ROM_API_INDEX_HBN_Set_Xtal_Type])

#define RomDriver_HBN_Trim_Ldo33VoutTrim                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Trim_Ldo33VoutTrim])

#define RomDriver_HBN_Trim_RC32K                          \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Trim_RC32K])

#define RomDriver_HBN_Get_BOD_OUT_State                   \
    ((BL_Sts_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Get_BOD_OUT_State])

#define RomDriver_HBN_Get_INT_State                       \
    ((BL_Sts_Type (*) (HBN_INT_Type irqType))ROM_APITABLE[ROM_API_INDEX_HBN_Get_INT_State])

#define RomDriver_HBN_Get_MCU_Root_CLK_Sel                \
    ((HBN_MCU_ROOT_CLK_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Get_MCU_Root_CLK_Sel])

#define RomDriver_HBN_Get_MCU_XCLK_Sel                    \
    ((HBN_MCU_XCLK_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Get_MCU_XCLK_Sel])

#define RomDriver_HBN_Get_PIR_Interval                    \
    ((uint16_t (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Get_PIR_Interval])

#define RomDriver_HBN_Get_PIR_Threshold                   \
    ((uint16_t (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Get_PIR_Threshold])

#define RomDriver_HBN_Get_Status_Flag                     \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Get_Status_Flag])

#define RomDriver_HBN_Get_Wakeup_Addr                     \
    ((uint32_t (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Get_Wakeup_Addr])

#define RomDriver_HBN_Get_Core_Unhalt_Config              \
    ((uint8_t (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Get_Core_Unhalt_Config])

#define RomDriver_HBN_Get_Pin_Wakeup_Mode                 \
    ((uint8_t (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Get_Pin_Wakeup_Mode])

#define RomDriver_HBN_Get_User_Boot_Config                \
    ((uint8_t (*) (void))ROM_APITABLE[ROM_API_INDEX_HBN_Get_User_Boot_Config])

#define RomDriver_HBN_Enable                              \
    ((void (*) (uint32_t aGPIOIeCfg, HBN_LDO_LEVEL_Type ldoLevel, HBN_LEVEL_Type hbnLevel, uint8_t dcdcPuSeq))ROM_APITABLE[ROM_API_INDEX_HBN_Enable])

#define RomDriver_HBN_Mode_Enter                          \
    ((void (*) (HBN_APP_CFG_Type *cfg))ROM_APITABLE[ROM_API_INDEX_HBN_Mode_Enter])

#define RomDriver_HBN_Power_Down_Flash                    \
    ((void (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_HBN_Power_Down_Flash])

#define RomDriver_L1C_DCache_Clean_All                    \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_L1C_DCache_Clean_All])

#define RomDriver_L1C_DCache_Clean_By_Addr                \
    ((BL_Err_Type (*) (uintptr_t addr, uint32_t len))ROM_APITABLE[ROM_API_INDEX_L1C_DCache_Clean_By_Addr])

#define RomDriver_L1C_DCache_Clean_Invalid_All            \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_L1C_DCache_Clean_Invalid_All])

#define RomDriver_L1C_DCache_Clean_Invalid_By_Addr        \
    ((BL_Err_Type (*) (uintptr_t addr, uint32_t len))ROM_APITABLE[ROM_API_INDEX_L1C_DCache_Clean_Invalid_By_Addr])

#define RomDriver_L1C_DCache_Disable                      \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_L1C_DCache_Disable])

#define RomDriver_L1C_DCache_Enable                       \
    ((BL_Err_Type (*) (uint8_t wayDsiable))ROM_APITABLE[ROM_API_INDEX_L1C_DCache_Enable])

#define RomDriver_L1C_DCache_Invalid_All                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_L1C_DCache_Invalid_All])

#define RomDriver_L1C_DCache_Invalid_By_Addr              \
    ((BL_Err_Type (*) (uintptr_t addr, uint32_t len))ROM_APITABLE[ROM_API_INDEX_L1C_DCache_Invalid_By_Addr])

#define RomDriver_L1C_ICache_Disable                      \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_L1C_ICache_Disable])

#define RomDriver_L1C_ICache_Enable                       \
    ((BL_Err_Type (*) (uint8_t wayDsiable))ROM_APITABLE[ROM_API_INDEX_L1C_ICache_Enable])

#define RomDriver_L1C_ICache_Invalid_All                  \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_L1C_ICache_Invalid_All])

#define RomDriver_L1C_ICache_Invalid_By_Addr              \
    ((BL_Err_Type (*) (uintptr_t addr, uint32_t len))ROM_APITABLE[ROM_API_INDEX_L1C_ICache_Invalid_By_Addr])

#define RomDriver_L1C_Set_Cache_Setting_By_ID             \
    ((BL_Err_Type (*) (uint8_t core, L1C_CACHE_Cfg_Type *cacheSetting))ROM_APITABLE[ROM_API_INDEX_L1C_Set_Cache_Setting_By_ID])

#define RomDriver_L1C_Set_Wrap                            \
    ((BL_Err_Type (*) (uint8_t en))ROM_APITABLE[ROM_API_INDEX_L1C_Set_Wrap])

#define RomDriver_L1C_DCache_Write_Set                    \
    ((void (*) (BL_Fun_Type wtEn, BL_Fun_Type wbEn, BL_Fun_Type waEn))ROM_APITABLE[ROM_API_INDEX_L1C_DCache_Write_Set])

#define RomDriver_PDS_Default_Level_Config                \
    ((BL_Err_Type (*) (PDS_DEFAULT_LV_CFG_Type *defaultLvCfg, uint32_t pdsSleepCnt))ROM_APITABLE[ROM_API_INDEX_PDS_Default_Level_Config])

#define RomDriver_PDS_Disable_GPIO_Keep                   \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_PDS_Disable_GPIO_Keep])

#define RomDriver_PDS_Enable                              \
    ((BL_Err_Type (*) (PDS_CTL_Type *cfg, PDS_CTL4_Type *cfg4, uint32_t pdsSleepCnt))ROM_APITABLE[ROM_API_INDEX_PDS_Enable])

#define RomDriver_PDS_Force_Config                        \
    ((BL_Err_Type (*) (PDS_CTL2_Type *cfg2, PDS_CTL3_Type *cfg3, PDS_CTL5_Type *cfg5))ROM_APITABLE[ROM_API_INDEX_PDS_Force_Config])

#define RomDriver_PDS_IntClear                            \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_PDS_IntClear])

#define RomDriver_PDS_IntMask                             \
    ((BL_Err_Type (*) (PDS_INT_Type intType, BL_Mask_Type intMask))ROM_APITABLE[ROM_API_INDEX_PDS_IntMask])

#define RomDriver_PDS_RAM_Config                          \
    ((BL_Err_Type (*) (PDS_CTRL_RAM1_Type *ram1Cfg, PDS_CTRL_RAM2_Type *ram2Cfg, PDS_CTRL_RAM3_Type *ram3Cfg, PDS_CTRL_RAM4_Type *ram4Cfg))ROM_APITABLE[ROM_API_INDEX_PDS_RAM_Config])

#define RomDriver_PDS_Set_Flash_Pad_Pull_None             \
    ((BL_Err_Type (*) (uint8_t pinCfg))ROM_APITABLE[ROM_API_INDEX_PDS_Set_Flash_Pad_Pull_None])

#define RomDriver_PDS_Set_Flash_Pad_Pull_None_Fast        \
    ((BL_Err_Type (*) (uint8_t pinCfg))ROM_APITABLE[ROM_API_INDEX_PDS_Set_Flash_Pad_Pull_None_Fast])

#define RomDriver_PDS_Set_GPIO_Pad_IntClr                 \
    ((BL_Err_Type (*) (PDS_GPIO_INT_SET_Type set))ROM_APITABLE[ROM_API_INDEX_PDS_Set_GPIO_Pad_IntClr])

#define RomDriver_PDS_Set_GPIO_Pad_IntMask                \
    ((BL_Err_Type (*) (GLB_GPIO_Type pad, BL_Mask_Type intMask))ROM_APITABLE[ROM_API_INDEX_PDS_Set_GPIO_Pad_IntMask])

#define RomDriver_PDS_Set_GPIO_Pad_IntMode                \
    ((BL_Err_Type (*) (PDS_GPIO_INT_SET_Type set, PDS_GPIO_INT_TRIG_Type trig))ROM_APITABLE[ROM_API_INDEX_PDS_Set_GPIO_Pad_IntMode])

#define RomDriver_PDS_Set_GPIO_Pad_Pn_Pu_Pd_Ie            \
    ((BL_Err_Type (*) (PDS_GPIO_GROUP_SET_Type grp, uint8_t pu, uint8_t pd, uint8_t ie))ROM_APITABLE[ROM_API_INDEX_PDS_Set_GPIO_Pad_Pn_Pu_Pd_Ie])

#define RomDriver_PDS_Set_MCU0_Clock_Disable              \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_PDS_Set_MCU0_Clock_Disable])

#define RomDriver_PDS_Set_MCU0_Clock_Enable               \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_PDS_Set_MCU0_Clock_Enable])

#define RomDriver_PDS_Set_MCU0_Reset_Address              \
    ((BL_Err_Type (*) (uint32_t addr))ROM_APITABLE[ROM_API_INDEX_PDS_Set_MCU0_Reset_Address])

#define RomDriver_PDS_Set_USB_Resume                      \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_PDS_Set_USB_Resume])

#define RomDriver_PDS_Set_USB_Suspend                     \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_PDS_Set_USB_Suspend])

#define RomDriver_PDS_Trim_RC32M                          \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_PDS_Trim_RC32M])

#define RomDriver_PDS_Turn_Off_USB                        \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_PDS_Turn_Off_USB])

#define RomDriver_PDS_Turn_On_USB                         \
    ((BL_Err_Type (*) (uint8_t waitReady))ROM_APITABLE[ROM_API_INDEX_PDS_Turn_On_USB])

#define RomDriver_PDS_Get_GPIO_Pad_IntStatus              \
    ((BL_Sts_Type (*) (GLB_GPIO_Type pad))ROM_APITABLE[ROM_API_INDEX_PDS_Get_GPIO_Pad_IntStatus])

#define RomDriver_PDS_Get_IntStatus                       \
    ((BL_Sts_Type (*) (PDS_INT_Type intType))ROM_APITABLE[ROM_API_INDEX_PDS_Get_IntStatus])

#define RomDriver_SF_Cfg_Deinit_Ext_Flash_Gpio            \
    ((int (*) (uint8_t extFlashPin))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Deinit_Ext_Flash_Gpio])

#define RomDriver_SF_Cfg_Flash_Init                       \
    ((int (*) (uint8_t sel, const struct sf_ctrl_cfg_type *pSfCtrlCfg, const struct sf_ctrl_bank2_cfg *pBank2Cfg))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Flash_Init])

#define RomDriver_SF_Cfg_Get_Flash_Cfg_Need_Lock          \
    ((int (*) (uint32_t flashID, spi_flash_cfg_type *pFlashCfg))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Get_Flash_Cfg_Need_Lock])

#define RomDriver_SF_Cfg_Init_Ext_Flash_Gpio              \
    ((int (*) (uint8_t extFlashPin))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Init_Ext_Flash_Gpio])

#define RomDriver_SF_Cfg_Init_Flash2_Gpio                 \
    ((int (*) (uint8_t swap))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Init_Flash2_Gpio])

#define RomDriver_SF_Cfg_Init_Flash_Gpio                  \
    ((int (*) (uint8_t flashPinCfg, uint8_t restoreDefault))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Init_Flash_Gpio])

#define RomDriver_SF_Cfg_Sbus2_Flash_Init                 \
    ((int (*) (uint8_t sel, const struct sf_ctrl_bank2_cfg *pBank2Cfg))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Sbus2_Flash_Init])

#define RomDriver_SF_Cfg_Flash_Identify                   \
    ((uint32_t (*) (uint8_t callFromFlash, uint8_t flashPinCfg, uint8_t restoreDefault, spi_flash_cfg_type *pFlashCfg, uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_SF_Cfg_Flash_Identify])

#define RomDriver_SF_Ctrl_GetBusyState                    \
    ((int (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_GetBusyState])

#define RomDriver_SF_Ctrl_Is_AES_Enable                   \
    ((int (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Is_AES_Enable])

#define RomDriver_SF_Ctrl_Is_Sbus2_Enable                 \
    ((int (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Is_Sbus2_Enable])

#define RomDriver_SF_Ctrl_Get_Flash_Image_Offset          \
    ((uint32_t (*) (uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Get_Flash_Image_Offset])

#define RomDriver_SF_Ctrl_Get_Clock_Delay                 \
    ((uint8_t (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Get_Clock_Delay])

#define RomDriver_SF_Ctrl_Get_Wrap_Queue_Value            \
    ((uint8_t (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Get_Wrap_Queue_Value])

#define RomDriver_SF_Ctrl_32bits_Addr_En                  \
    ((void (*) (BL_Fun_Type en32BitsAddr))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_32bits_Addr_En])

#define RomDriver_SF_Ctrl_AES_Disable                     \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Disable])

#define RomDriver_SF_Ctrl_AES_Enable                      \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Enable])

#define RomDriver_SF_Ctrl_AES_Enable_BE                   \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Enable_BE])

#define RomDriver_SF_Ctrl_AES_Enable_LE                   \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Enable_LE])

#define RomDriver_SF_Ctrl_AES_Set_IV                      \
    ((void (*) (uint8_t region, uint8_t *iv, uint32_t addrOffset))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_IV])

#define RomDriver_SF_Ctrl_AES_Set_IV_BE                   \
    ((void (*) (uint8_t region, uint8_t *iv, uint32_t addrOffset))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_IV_BE])

#define RomDriver_SF_Ctrl_AES_Set_Key                     \
    ((void (*) (uint8_t region, uint8_t *key, uint8_t keyType))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_Key])

#define RomDriver_SF_Ctrl_AES_Set_Key_BE                  \
    ((void (*) (uint8_t region, uint8_t *key, uint8_t keyType))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_Key_BE])

#define RomDriver_SF_Ctrl_AES_Set_Mode                    \
    ((void (*) (uint8_t mode))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_Mode])

#define RomDriver_SF_Ctrl_AES_Set_Region                  \
    ((void (*) (uint8_t region, uint8_t enable, uint8_t hwKey, uint32_t startAddr, uint32_t endAddr, uint8_t locked))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_Set_Region])

#define RomDriver_SF_Ctrl_AES_XTS_Set_IV                  \
    ((void (*) (uint8_t region, uint8_t *iv, uint32_t addrOffset))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_XTS_Set_IV])

#define RomDriver_SF_Ctrl_AES_XTS_Set_IV_BE               \
    ((void (*) (uint8_t region, uint8_t *iv, uint32_t addrOffset))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_XTS_Set_IV_BE])

#define RomDriver_SF_Ctrl_AES_XTS_Set_Key                 \
    ((void (*) (uint8_t region, uint8_t *key, uint8_t keyType))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_XTS_Set_Key])

#define RomDriver_SF_Ctrl_AES_XTS_Set_Key_BE              \
    ((void (*) (uint8_t region, uint8_t *key, uint8_t keyType))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_AES_XTS_Set_Key_BE])

#define RomDriver_SF_Ctrl_Bank2_Enable                    \
    ((void (*) (const struct sf_ctrl_bank2_cfg *bank2Cfg))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Bank2_Enable])

#define RomDriver_SF_Ctrl_Cmds_Set                        \
    ((void (*) (struct sf_ctrl_cmds_cfg *cmdsCfg, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Cmds_Set])

#define RomDriver_SF_Ctrl_Disable                         \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Disable])

#define RomDriver_SF_Ctrl_Disable_Wrap_Access             \
    ((void (*) (uint8_t disable))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Disable_Wrap_Access])

#define RomDriver_SF_Ctrl_Enable                          \
    ((void (*) (const struct sf_ctrl_cfg_type *cfg))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Enable])

#define RomDriver_SF_Ctrl_Flash2_Read_Icache_Set          \
    ((void (*) (struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmdValid))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Flash2_Read_Icache_Set])

#define RomDriver_SF_Ctrl_Flash_Read_Icache_Set           \
    ((void (*) (struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmdValid))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Flash_Read_Icache_Set])

#define RomDriver_SF_Ctrl_Lock_Flash_Image_Offset         \
    ((void (*) (uint8_t lock))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Lock_Flash_Image_Offset])

#define RomDriver_SF_Ctrl_Remap_Set                       \
    ((void (*) (uint8_t remap, uint8_t lock))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Remap_Set])

#define RomDriver_SF_Ctrl_Sbus2_Hold_Sram                 \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Sbus2_Hold_Sram])

#define RomDriver_SF_Ctrl_Sbus2_Release_Sram              \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Sbus2_Release_Sram])

#define RomDriver_SF_Ctrl_Sbus2_Replace                   \
    ((void (*) (uint8_t pad))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Sbus2_Replace])

#define RomDriver_SF_Ctrl_Sbus2_Revoke_replace            \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Sbus2_Revoke_replace])

#define RomDriver_SF_Ctrl_Sbus2_Set_Delay                 \
    ((void (*) (uint8_t clkDelay, uint8_t rxClkInvert))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Sbus2_Set_Delay])

#define RomDriver_SF_Ctrl_Sbus_Select_Bank                \
    ((void (*) (uint8_t bank))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Sbus_Select_Bank])

#define RomDriver_SF_Ctrl_Select_Pad                      \
    ((void (*) (uint8_t sel))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Select_Pad])

#define RomDriver_SF_Ctrl_SendCmd                         \
    ((void (*) (struct sf_ctrl_cmd_cfg_type *cfg))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_SendCmd])

#define RomDriver_SF_Ctrl_Set_Clock_Delay                 \
    ((void (*) (uint8_t delay))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Set_Clock_Delay])

#define RomDriver_SF_Ctrl_Set_Flash_Image_Offset          \
    ((void (*) (uint32_t addrOffset, uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Set_Flash_Image_Offset])

#define RomDriver_SF_Ctrl_Set_IO_Delay                    \
    ((void (*) (uint8_t pad, uint8_t doDelay, uint8_t diDelay, uint8_t oeDelay))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Set_IO_Delay])

#define RomDriver_SF_Ctrl_Set_Owner                       \
    ((void (*) (uint8_t owner))ROM_APITABLE[ROM_API_INDEX_SF_Ctrl_Set_Owner])

#define RomDriver_SFlash_Blk32_Erase                      \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint32_t blkNum))ROM_APITABLE[ROM_API_INDEX_SFlash_Blk32_Erase])

#define RomDriver_SFlash_Blk64_Erase                      \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint32_t blkNum))ROM_APITABLE[ROM_API_INDEX_SFlash_Blk64_Erase])

#define RomDriver_SFlash_Chip_Erase                       \
    ((int (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Chip_Erase])

#define RomDriver_SFlash_Erase                            \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint32_t startaddr, uint32_t endaddr))ROM_APITABLE[ROM_API_INDEX_SFlash_Erase])

#define RomDriver_SFlash_Erase_Security_Register          \
    ((int (*) (spi_flash_cfg_type *pFlashCfg, struct sflash_sec_reg_cfg *pSecRegCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Erase_Security_Register])

#define RomDriver_SFlash_IDbus_Read_Enable                \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint8_t ioMode, uint8_t contRead, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_SFlash_IDbus_Read_Enable])

#define RomDriver_SFlash_Program                          \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint8_t ioMode, uint32_t addr, uint8_t *data, uint32_t len))ROM_APITABLE[ROM_API_INDEX_SFlash_Program])

#define RomDriver_SFlash_Program_Security_Register        \
    ((int (*) (spi_flash_cfg_type *pFlashCfg, struct sflash_sec_reg_cfg *pSecRegCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Program_Security_Register])

#define RomDriver_SFlash_Qspi_Disable                     \
    ((int (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Qspi_Disable])

#define RomDriver_SFlash_Qspi_Enable                      \
    ((int (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Qspi_Enable])

#define RomDriver_SFlash_RCV_Enable                       \
    ((int (*) (spi_flash_cfg_type *pFlashCfg, uint8_t rCmd, uint8_t wCmd, uint8_t bitPos))ROM_APITABLE[ROM_API_INDEX_SFlash_RCV_Enable])

#define RomDriver_SFlash_Read                             \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint8_t ioMode, uint8_t contRead, uint32_t addr, uint8_t *data, uint32_t len))ROM_APITABLE[ROM_API_INDEX_SFlash_Read])

#define RomDriver_SFlash_Read_Reg                         \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint8_t regIndex, uint8_t *regValue, uint8_t regLen))ROM_APITABLE[ROM_API_INDEX_SFlash_Read_Reg])

#define RomDriver_SFlash_Read_Reg_With_Cmd                \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint8_t readRegCmd, uint8_t *regValue, uint8_t regLen))ROM_APITABLE[ROM_API_INDEX_SFlash_Read_Reg_With_Cmd])

#define RomDriver_SFlash_Read_Security_Register           \
    ((int (*) (struct sflash_sec_reg_cfg *pSecRegCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Read_Security_Register])

#define RomDriver_SFlash_Restore_From_Powerdown           \
    ((int (*) (spi_flash_cfg_type *pFlashCfg, uint8_t flashContRead, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_SFlash_Restore_From_Powerdown])

#define RomDriver_SFlash_Sector_Erase                     \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint32_t secNum))ROM_APITABLE[ROM_API_INDEX_SFlash_Sector_Erase])

#define RomDriver_SFlash_Set32BitsAddrMode                \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint8_t en32BitsAddr))ROM_APITABLE[ROM_API_INDEX_SFlash_Set32BitsAddrMode])

#define RomDriver_SFlash_SetSPIMode                       \
    ((int (*) (uint8_t mode))ROM_APITABLE[ROM_API_INDEX_SFlash_SetSPIMode])

#define RomDriver_SFlash_Set_IDbus_Cfg                    \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint8_t ioMode, uint8_t contRead, uint32_t addr, uint32_t len, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_SFlash_Set_IDbus_Cfg])

#define RomDriver_SFlash_Software_Reset                   \
    ((int (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Software_Reset])

#define RomDriver_SFlash_Write_Enable                     \
    ((int (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Write_Enable])

#define RomDriver_SFlash_Write_Reg                        \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint8_t regIndex, uint8_t *regValue, uint8_t regLen))ROM_APITABLE[ROM_API_INDEX_SFlash_Write_Reg])

#define RomDriver_SFlash_Write_Reg_With_Cmd               \
    ((int (*) (spi_flash_cfg_type *flashCfg, uint8_t writeRegCmd, uint8_t *regValue, uint8_t regLen))ROM_APITABLE[ROM_API_INDEX_SFlash_Write_Reg_With_Cmd])

#define RomDriver_SFlash_Busy                             \
    ((int (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Busy])

#define RomDriver_SFlash_DisableBurstWrap                 \
    ((void (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_DisableBurstWrap])

#define RomDriver_SFlash_GetDeviceId                      \
    ((void (*) (uint8_t *data, uint8_t is32BitsAddr))ROM_APITABLE[ROM_API_INDEX_SFlash_GetDeviceId])

#define RomDriver_SFlash_GetJedecId                       \
    ((void (*) (spi_flash_cfg_type *flashCfg, uint8_t *data))ROM_APITABLE[ROM_API_INDEX_SFlash_GetJedecId])

#define RomDriver_SFlash_GetUniqueId                      \
    ((void (*) (uint8_t *data, uint8_t idLen))ROM_APITABLE[ROM_API_INDEX_SFlash_GetUniqueId])

#define RomDriver_SFlash_IDbus_Read_Disable               \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_SFlash_IDbus_Read_Disable])

#define RomDriver_SFlash_Init                             \
    ((void (*) (const struct sf_ctrl_cfg_type *pSfCtrlCfg, const struct sf_ctrl_bank2_cfg *pBank2Cfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Init])

#define RomDriver_SFlash_Powerdown                        \
    ((void (*) (void))ROM_APITABLE[ROM_API_INDEX_SFlash_Powerdown])

#define RomDriver_SFlash_Release_Powerdown                \
    ((void (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Release_Powerdown])

#define RomDriver_SFlash_Reset_Continue_Read              \
    ((void (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Reset_Continue_Read])

#define RomDriver_SFlash_SetBurstWrap                     \
    ((void (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_SetBurstWrap])

#define RomDriver_SFlash_Volatile_Reg_Write_Enable        \
    ((void (*) (spi_flash_cfg_type *flashCfg))ROM_APITABLE[ROM_API_INDEX_SFlash_Volatile_Reg_Write_Enable])

#define RomDriver_UART_AutoBaudDetection                  \
    ((BL_Err_Type (*) (UART_ID_Type uartId, BL_Fun_Type autoBaud))ROM_APITABLE[ROM_API_INDEX_UART_AutoBaudDetection])

#define RomDriver_UART_ClrRtsValue                        \
    ((BL_Err_Type (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_ClrRtsValue])

#define RomDriver_UART_ClrTxValue                         \
    ((BL_Err_Type (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_ClrTxValue])

#define RomDriver_UART_DeInit                             \
    ((BL_Err_Type (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_DeInit])

#define RomDriver_UART_Disable                            \
    ((BL_Err_Type (*) (UART_ID_Type uartId, UART_Direction_Type direct))ROM_APITABLE[ROM_API_INDEX_UART_Disable])

#define RomDriver_UART_Enable                             \
    ((BL_Err_Type (*) (UART_ID_Type uartId, UART_Direction_Type direct))ROM_APITABLE[ROM_API_INDEX_UART_Enable])

#define RomDriver_UART_FifoConfig                         \
    ((BL_Err_Type (*) (UART_ID_Type uartId, UART_FifoCfg_Type *fifoCfg))ROM_APITABLE[ROM_API_INDEX_UART_FifoConfig])

#define RomDriver_UART_GetBitWidth0X55                    \
    ((BL_Err_Type (*) (UART_ID_Type uartId, uint16_t *width))ROM_APITABLE[ROM_API_INDEX_UART_GetBitWidth0X55])

#define RomDriver_UART_Init                               \
    ((BL_Err_Type (*) (UART_ID_Type uartId, UART_CFG_Type *uartCfg))ROM_APITABLE[ROM_API_INDEX_UART_Init])

#define RomDriver_UART_IntClear                           \
    ((BL_Err_Type (*) (UART_ID_Type uartId, UART_INT_Type intType))ROM_APITABLE[ROM_API_INDEX_UART_IntClear])

#define RomDriver_UART_IntMask                            \
    ((BL_Err_Type (*) (UART_ID_Type uartId, UART_INT_Type intType, BL_Mask_Type intMask))ROM_APITABLE[ROM_API_INDEX_UART_IntMask])

#define RomDriver_UART_IrConfig                           \
    ((BL_Err_Type (*) (UART_ID_Type uartId, UART_IrCfg_Type *irCfg))ROM_APITABLE[ROM_API_INDEX_UART_IrConfig])

#define RomDriver_UART_RxFifoClear                        \
    ((BL_Err_Type (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_RxFifoClear])

#define RomDriver_UART_SendData                           \
    ((BL_Err_Type (*) (UART_ID_Type uartId, uint8_t *data, uint32_t len))ROM_APITABLE[ROM_API_INDEX_UART_SendData])

#define RomDriver_UART_SendDataBlock                      \
    ((BL_Err_Type (*) (UART_ID_Type uartId, uint8_t *data, uint32_t len))ROM_APITABLE[ROM_API_INDEX_UART_SendDataBlock])

#define RomDriver_UART_SetAllowableError0X55              \
    ((BL_Err_Type (*) (UART_ID_Type uartId, uint8_t allowableError))ROM_APITABLE[ROM_API_INDEX_UART_SetAllowableError0X55])

#define RomDriver_UART_SetBaudrate                        \
    ((BL_Err_Type (*) (UART_ID_Type uartId, UART_AutoBaudDetection_Type autoBaudDet))ROM_APITABLE[ROM_API_INDEX_UART_SetBaudrate])

#define RomDriver_UART_SetDeglitchCount                   \
    ((BL_Err_Type (*) (UART_ID_Type uartId, uint8_t deglitchCnt))ROM_APITABLE[ROM_API_INDEX_UART_SetDeglitchCount])

#define RomDriver_UART_SetRS485                           \
    ((BL_Err_Type (*) (UART_ID_Type uartId, BL_Fun_Type enable, UART_RS485Polarity_Type polarity))ROM_APITABLE[ROM_API_INDEX_UART_SetRS485])

#define RomDriver_UART_SetRtsValue                        \
    ((BL_Err_Type (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_SetRtsValue])

#define RomDriver_UART_SetRxByteCount                     \
    ((BL_Err_Type (*) (UART_ID_Type uartId, uint16_t count))ROM_APITABLE[ROM_API_INDEX_UART_SetRxByteCount])

#define RomDriver_UART_SetRxDataLength                    \
    ((BL_Err_Type (*) (UART_ID_Type uartId, uint16_t length))ROM_APITABLE[ROM_API_INDEX_UART_SetRxDataLength])

#define RomDriver_UART_SetRxTimeoutValue                  \
    ((BL_Err_Type (*) (UART_ID_Type uartId, uint8_t time))ROM_APITABLE[ROM_API_INDEX_UART_SetRxTimeoutValue])

#define RomDriver_UART_SetTxDataLength                    \
    ((BL_Err_Type (*) (UART_ID_Type uartId, uint16_t length))ROM_APITABLE[ROM_API_INDEX_UART_SetTxDataLength])

#define RomDriver_UART_SetTxValue                         \
    ((BL_Err_Type (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_SetTxValue])

#define RomDriver_UART_TxFifoClear                        \
    ((BL_Err_Type (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_TxFifoClear])

#define RomDriver_UART_TxFreeRun                          \
    ((BL_Err_Type (*) (UART_ID_Type uartId, BL_Fun_Type txFreeRun))ROM_APITABLE[ROM_API_INDEX_UART_TxFreeRun])

#define RomDriver_UART_GetIntStatus                       \
    ((BL_Sts_Type (*) (UART_ID_Type uartId, UART_INT_Type intType))ROM_APITABLE[ROM_API_INDEX_UART_GetIntStatus])

#define RomDriver_UART_GetOverflowStatus                  \
    ((BL_Sts_Type (*) (UART_ID_Type uartId, UART_Overflow_Type overflow))ROM_APITABLE[ROM_API_INDEX_UART_GetOverflowStatus])

#define RomDriver_UART_GetRxBusBusyStatus                 \
    ((BL_Sts_Type (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_GetRxBusBusyStatus])

#define RomDriver_UART_GetTxBusBusyStatus                 \
    ((BL_Sts_Type (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_GetTxBusBusyStatus])

#define RomDriver_UART_GetAutoBaudCount                   \
    ((uint16_t (*) (UART_ID_Type uartId, UART_AutoBaudDetection_Type autoBaudDet))ROM_APITABLE[ROM_API_INDEX_UART_GetAutoBaudCount])

#define RomDriver_UART_GetRxByteCount                     \
    ((uint16_t (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_GetRxByteCount])

#define RomDriver_UART_ReceiveData                        \
    ((uint32_t (*) (UART_ID_Type uartId, uint8_t *data, uint32_t maxLen))ROM_APITABLE[ROM_API_INDEX_UART_ReceiveData])

#define RomDriver_UART_GetRxFifoCount                     \
    ((uint8_t (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_GetRxFifoCount])

#define RomDriver_UART_GetTxFifoCount                     \
    ((uint8_t (*) (UART_ID_Type uartId))ROM_APITABLE[ROM_API_INDEX_UART_GetTxFifoCount])

#define RomDriver_XIP_SFlash_Erase_Need_Lock              \
    ((BL_Err_Type (*) (spi_flash_cfg_type *pFlashCfg, uint32_t startaddr, int len, uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Erase_Need_Lock])

#define RomDriver_XIP_SFlash_GetDeviceId_Need_Lock        \
    ((BL_Err_Type (*) (spi_flash_cfg_type *pFlashCfg, BL_Fun_Type is32BitsAddr, uint8_t *data, uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_GetDeviceId_Need_Lock])

#define RomDriver_XIP_SFlash_GetJedecId_Need_Lock         \
    ((BL_Err_Type (*) (spi_flash_cfg_type *pFlashCfg, uint8_t *data, uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_GetJedecId_Need_Lock])

#define RomDriver_XIP_SFlash_GetUniqueId_Need_Lock        \
    ((BL_Err_Type (*) (spi_flash_cfg_type *pFlashCfg, uint8_t *data, uint8_t idLen, uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_GetUniqueId_Need_Lock])

#define RomDriver_XIP_SFlash_Read_Need_Lock               \
    ((BL_Err_Type (*) (spi_flash_cfg_type *pFlashCfg, uint32_t addr, uint8_t *data, uint32_t len, uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Read_Need_Lock])

#define RomDriver_XIP_SFlash_Read_Via_Cache_Need_Lock     \
    ((BL_Err_Type (*) (uint32_t addr, uint8_t *data, uint32_t len))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Read_Via_Cache_Need_Lock])

#define RomDriver_XIP_SFlash_State_Restore                \
    ((BL_Err_Type (*) (spi_flash_cfg_type *pFlashCfg, uint32_t offset, uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_State_Restore])

#define RomDriver_XIP_SFlash_State_Save                   \
    ((BL_Err_Type (*) (spi_flash_cfg_type *pFlashCfg, uint32_t *offset, uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_State_Save])

#define RomDriver_XIP_SFlash_Write_Need_Lock              \
    ((BL_Err_Type (*) (spi_flash_cfg_type *pFlashCfg, uint32_t addr, uint8_t *data, uint32_t len, uint8_t group, uint8_t bank))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Write_Need_Lock])

#define RomDriver_XIP_SFlash_Opt_Enter                    \
    ((void (*) (uint8_t *aesEnable))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Opt_Enter])

#define RomDriver_XIP_SFlash_Opt_Exit                     \
    ((void (*) (uint8_t aesEnable))ROM_APITABLE[ROM_API_INDEX_XIP_SFlash_Opt_Exit])

#define RomDriver_MD_Clr_GPIO_IntStatus                   \
    ((BL_Err_Type (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_Clr_GPIO_IntStatus])

#define RomDriver_MD_Embedded_Flash_Pad_Enable            \
    ((BL_Err_Type (*) (void))ROM_APITABLE[ROM_API_INDEX_MD_Embedded_Flash_Pad_Enable])

#define RomDriver_MD_GPIO_Clr                             \
    ((BL_Err_Type (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Clr])

#define RomDriver_MD_GPIO_Init                            \
    ((BL_Err_Type (*) (MD_GPIO_Cfg_Type *cfg))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Init])

#define RomDriver_MD_GPIO_Input_Disable                   \
    ((BL_Err_Type (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Input_Disable])

#define RomDriver_MD_GPIO_Input_Enable                    \
    ((BL_Err_Type (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Input_Enable])

#define RomDriver_MD_GPIO_IntMask                         \
    ((BL_Err_Type (*) (MD_GPIO_Type gpioPin, BL_Mask_Type intMask))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_IntMask])

#define RomDriver_MD_GPIO_Int_Init                        \
    ((BL_Err_Type (*) (MD_GPIO_INT_Cfg_Type *intCfg))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Int_Init])

#define RomDriver_MD_GPIO_Output_Disable                  \
    ((BL_Err_Type (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Output_Disable])

#define RomDriver_MD_GPIO_Output_Enable                   \
    ((BL_Err_Type (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Output_Enable])

#define RomDriver_MD_GPIO_Set                             \
    ((BL_Err_Type (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Set])

#define RomDriver_MD_GPIO_Set_HZ                          \
    ((BL_Err_Type (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Set_HZ])

#define RomDriver_MD_GPIO_Write                           \
    ((BL_Err_Type (*) (MD_GPIO_Type gpioPin, uint32_t val))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Write])

#define RomDriver_MD_Get_GPIO_IntStatus                   \
    ((BL_Sts_Type (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_Get_GPIO_IntStatus])

#define RomDriver_MD_GPIO_Read                            \
    ((uint32_t (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Read])

#define RomDriver_MD_GPIO_Get_Fun                         \
    ((uint8_t (*) (MD_GPIO_Type gpioPin))ROM_APITABLE[ROM_API_INDEX_MD_GPIO_Get_Fun])

/*@} end of group ROMDRIVER_Public_Macros */

/** @defgroup  ROMDRIVER_Public_Functions
 *  @{
 */

/*@} end of group ROMDRIVER_Public_Functions */

/*@} end of group ROMDRIVER */

/*@} end of group bl616_Peripheral_Driver */

#endif /* __bl616_ROMDRIVER_H__ */
