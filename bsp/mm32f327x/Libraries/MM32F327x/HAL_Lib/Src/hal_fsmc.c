////////////////////////////////////////////////////////////////////////////////
/// @file     hal_fsmc.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE FSMC FIRMWARE FUNCTIONS.
///                Interface with SRAM, PSRAM, NOR memories
///                Interrupts and flags management
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _HAL_FSMC_C_

// Files includes
#include "reg_rcc.h"
#include "reg_syscfg.h"
#include "hal_fsmc.h"


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup FSMC_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup FSMC_Exported_Functions
/// @{


void FSMC_NORSRAMStructInit(FSMC_InitTypeDef* init_struct)
{
    init_struct->FSMC_Mode = FSMC_Mode_NorFlash;
    init_struct->FSMC_AddrDataMode = FSMC_AddrDataDeMUX;

    init_struct->FSMC_TimingRegSelect = FSMC_TimingRegSelect_0;
    init_struct->FSMC_MemSize = FSMC_MemSize_64MB;
    init_struct->FSMC_MemType = FSMC_MemType_NorSRAM;
}
void FSMC_NORSRAM_BankStructInit(FSMC_NORSRAM_Bank_InitTypeDef* init_struct)
{

    init_struct->FSMC_SMReadPipe    = 0;
    init_struct->FSMC_ReadyMode     = 0;
    init_struct->FSMC_WritePeriod   = 0x2;
    init_struct->FSMC_WriteHoldTime = 1;
    init_struct->FSMC_AddrSetTime   = 3;
    init_struct->FSMC_ReadPeriod    = 0x1;
    init_struct->FSMC_DataWidth     = FSMC_DataWidth_16bits;
}
void FSMC_NORSRAMInit(FSMC_InitTypeDef* init_struct)
{
    SYSCFG->CFGR &= ~(SYSCFG_CFGR_FSMC_MODE | SYSCFG_CFGR_FSMC_AF_ADDR | SYSCFG_CFGR_FSMC_SYNC_EN);
    SYSCFG->CFGR |= (u32)init_struct->FSMC_Mode | \
                    (u32)init_struct->FSMC_AddrDataMode;

    FSMC->SMSKR = (u32)init_struct->FSMC_TimingRegSelect | \
                  (u32)init_struct->FSMC_MemSize | \
                  (u32)init_struct->FSMC_MemType;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Initialize the FSMC_NORSRAM Timing according to the specified
///         parameters in the FSMC_NORSRAM_TimingTypeDef
/// @param  FSMC_Bank_InitStruct: Timing Pointer to NORSRAM Timing structure
/// @param  Bank: NORSRAM bank number
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FSMC_NORSRAM_Bank_Init(FSMC_NORSRAM_Bank_InitTypeDef* FSMC_Bank_InitStruct, FSMC_NORSRAM_BANK_TypeDef bank)
{
    // Set FSMC_NORSRAM device timing parameters
    if(bank == FSMC_NORSRAM_BANK0) {
        FSMC->SMTMGR_SET0 = (u32)(FSMC_Bank_InitStruct->FSMC_SMReadPipe << FSMC_SMTMGR_SET_SM_READ_PIPE_Pos)    | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_ReadyMode << FSMC_SMTMGR_SET_READ_MODE_Pos)     | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_WritePeriod << FSMC_SMTMGR_SET_T_WP_Pos)   | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_WriteHoldTime << FSMC_SMTMGR_SET_T_WR_Pos)  | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_AddrSetTime << FSMC_SMTMGR_SET_T_AS_Pos)    | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_ReadPeriod << FSMC_SMTMGR_SET_T_RC_Pos ) ;
        FSMC->SMCTLR &= ~FSMC_SMCTLR_SM_DATA_WIDTH_SET0;
        FSMC->SMCTLR |= (FSMC_Bank_InitStruct->FSMC_DataWidth) << FSMC_SMCTLR_SM_DATA_WIDTH_SET0_Pos;
    }
    else if(bank == FSMC_NORSRAM_BANK1) {
        FSMC->SMTMGR_SET1 = (u32)(FSMC_Bank_InitStruct->FSMC_SMReadPipe << FSMC_SMTMGR_SET_SM_READ_PIPE_Pos)    | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_ReadyMode << FSMC_SMTMGR_SET_READ_MODE_Pos)     | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_WritePeriod << FSMC_SMTMGR_SET_T_WP_Pos)   | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_WriteHoldTime << FSMC_SMTMGR_SET_T_WR_Pos)  | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_AddrSetTime << FSMC_SMTMGR_SET_T_AS_Pos)    | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_ReadPeriod << FSMC_SMTMGR_SET_T_RC_Pos ) ;
        FSMC->SMCTLR &= ~FSMC_SMCTLR_SM_DATA_WIDTH_SET1;
        FSMC->SMCTLR |= (FSMC_Bank_InitStruct->FSMC_DataWidth) << FSMC_SMCTLR_SM_DATA_WIDTH_SET1_Pos;
    }
    else if(bank == FSMC_NORSRAM_BANK2) {
        FSMC->SMTMGR_SET2 = (u32)(FSMC_Bank_InitStruct->FSMC_SMReadPipe << FSMC_SMTMGR_SET_SM_READ_PIPE_Pos)    | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_ReadyMode << FSMC_SMTMGR_SET_READ_MODE_Pos)     | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_WritePeriod << FSMC_SMTMGR_SET_T_WP_Pos)   | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_WriteHoldTime << FSMC_SMTMGR_SET_T_WR_Pos)  | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_AddrSetTime << FSMC_SMTMGR_SET_T_AS_Pos)    | \
                            (u32)(FSMC_Bank_InitStruct->FSMC_ReadPeriod << FSMC_SMTMGR_SET_T_RC_Pos ) ;
        FSMC->SMCTLR &= ~FSMC_SMCTLR_SM_DATA_WIDTH_SET2;
        FSMC->SMCTLR |= (FSMC_Bank_InitStruct->FSMC_DataWidth) << FSMC_SMCTLR_SM_DATA_WIDTH_SET2_Pos;
    }
}




/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
