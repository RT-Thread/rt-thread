/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_pwr.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_pwr.h"
#include "n32h76x_78x_rcc.h"
#include "misc.h"

#define   GRAPHIC_MODULE_MASK    ((uint32_t)0x0000001FU)
#define   HSC1_MODULE_MASK       ((uint32_t)0x00000700U)
#define   HSC2_MODULE_MASK       ((uint32_t)0x000000E0U)
/**
*\*\name    PWR_DeInit.
*\*\fun     Deinitializes the PWR peripheral registers to their default reset values.
*\*\param   none
*\*\return  none
**/
void PWR_DeInit(void)
{
    RCC_EnableAHB5PeriphReset2(RCC_AHB5_PERIPHRST_PWR);
}

/**
*\*\name  PWR_BackupAccessEnable.
*\*\fun   Enables or disables access to the RTC and backup registers.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_BackupAccessEnable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
      PWR->SYSCTRL1 |= PWR_DBKPEN;
    }
    else
    {
      PWR->SYSCTRL1 &= ~PWR_DBKPEN;
    }
}

/**
*\*\name    PWR_PvdEnable.
*\*\fun     Enables or disables the Power Voltage Detector(PVD).
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_PvdEnable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->SYSCTRL1 |= PWR_PVDEN;
    }
    else
    {
        PWR->SYSCTRL1 &= ~PWR_PVDEN;
    }
}

/**
*\*\name    PWR_AvdEnable.
*\*\fun     Enables or disables the Power Analog Voltage Detector(AVD).
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_AvdEnable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->SYSCTRL1 |= PWR_AVDEN;
    }
    else
    {
        PWR->SYSCTRL1 &= ~PWR_AVDEN;
    }
}

/**
*\*\name    PWR_EnableMRInStandby.
*\*\fun     Enables or disables the MR power when the system enters into standby mode .
*\*\param   Cmd: 
*\*\          - ENABLE  : MR is on when system enters into Standby mode.
*\*\          - DISABLE : MR is off when system enters into Standby mode.
*\*\return  none
**/
void PWR_EnableMRInStandby(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->SYSCTRL2 &= ~PWR_MROFF_IN_STANDBY;
    }
    else
    {
        PWR->SYSCTRL2 |= PWR_MROFF_IN_STANDBY;
    }
}


/**
*\*\name    PWR_ConfigDigitalFilterOnNRST.
*\*\fun     Config the digital glitch filtered pulse width  on NRST .
*\*\param   cycle_cnt(The input parameters must be the following values): 
*\*\          - 0x000U - 0xFFFU .
*\*\param   Cmd: 
*\*\          - ENABLE .
*\*\          - DISABLE.
*\*\return  none
**/
void PWR_ConfigDigitalFilterOnNRST(uint32_t cycle_cnt, FunctionalState Cmd)
{
    __IO uint32_t tempreg;
    /* Get the old register value */
    tempreg = PWR->SYSCTRL1;
    if(Cmd == ENABLE)
    {
        tempreg &= ~(PWR_NRST_DGF_BP | PWR_NRST_DGF_CNT_MASK);
        tempreg |= (cycle_cnt << PWR_NRST_DGF_CNT_BIT_OFFSET);
    }
    else
    {
        tempreg |= PWR_NRST_DGF_BP;
    }
    /* Set new configuration */
    PWR->SYSCTRL1 = tempreg;
}

/**
*\*\name    PWR_EnableBKPLDO.
*\*\fun     Enables or disables the backup LDO.
*\*\param   Cmd: 
*\*\          - ENABLE  : Enable the backup LDO.
*\*\          - DISABLE : Disable the backup LDO.
*\*\return  none
**/
void PWR_EnableBKPLDO(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->SYSCTRL1 |= ~PWR_BKPLDOEN;
    }
    else
    {
        PWR->SYSCTRL1 &= PWR_BKPLDOEN;
    }
}


/**
*\*\name    PWR_PVDLevelConfig.
*\*\fun     Configures the voltage threshold detected by the Power Voltage Detector(PVD).
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_PVD_LEVEL_2V28    PVD level is 2.28V
*\*\          - PWR_PVD_LEVEL_2V38    PVD level is 2.38V
*\*\          - PWR_PVD_LEVEL_2V48    PVD level is 2.48V
*\*\          - PWR_PVD_LEVEL_2V58    PVD level is 2.58V
*\*\          - PWR_PVD_LEVEL_2V68    PVD level is 2.68V
*\*\          - PWR_PVD_LEVEL_2V78    PVD level is 2.78V
*\*\          - PWR_PVD_LEVEL_2V88    PVD level is 2.88V
*\*\          - PWR_PVD_LEVEL_3V28    PVD level is 3.28V
*\*\          - PWR_PVD_LEVEL_3V38    PVD level is 3.38V
*\*\          - PWR_PVD_LEVEL_3V48    PVD level is 3.48V
*\*\          - PWR_PVD_LEVEL_3V58    PVD level is 3.58V
*\*\return  none
**/
void PWR_PVDLevelConfig(uint32_t level)
{
    uint32_t temp_value;

    temp_value = *(__IO uint32_t *)PVD_ContrlBaseAddress;
    /* Clear MSB and PLS[2:0] bits bit */
    temp_value &= PWR_PVD_LEVEL_MASK;
    /* Set PLS[3:0] bits according to level value */
    temp_value |= level;
    /* Store the new value */
    *(__IO uint32_t *)PVD_ContrlBaseAddress = temp_value;
}

/**
*\*\name    PWR_AVDLevelConfig.
*\*\fun     Configure the voltage threshold to be detected by the Analog Power Voltage Detector(AVD).
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_AVD_LEVEL_2V28    AVD level is 2.28V
*\*\          - PWR_AVD_LEVEL_2V38    AVD level is 2.38V
*\*\          - PWR_AVD_LEVEL_2V48    AVD level is 2.48V
*\*\          - PWR_AVD_LEVEL_2V58    AVD level is 2.58V
*\*\          - PWR_AVD_LEVEL_2V68    AVD level is 2.68V
*\*\          - PWR_AVD_LEVEL_2V78    AVD level is 2.78V
*\*\          - PWR_AVD_LEVEL_2V88    AVD level is 2.88V
*\*\          - PWR_AVD_LEVEL_3V28    AVD level is 3.28V
*\*\          - PWR_AVD_LEVEL_3V38    AVD level is 3.38V
*\*\          - PWR_AVD_LEVEL_3V48    AVD level is 3.48V
*\*\          - PWR_AVD_LEVEL_3V58    AVD level is 3.58V
*\*\return  none
**/
void PWR_AVDLevelConfig(uint32_t level)
{
    uint32_t temp_value;

    temp_value = *(__IO uint32_t *)AVD_ContrlBaseAddress;
    /* Clear ALS[3:0] bits bit */
    temp_value &= PWR_AVD_LEVEL_MASK;
    /* Set ALS[3:0] bits according to level value */
    temp_value |= level;
    /* Store the new value */
    *(__IO uint32_t *)AVD_ContrlBaseAddress = temp_value;
}

/**
*\*\name    PWR_VDDDPORLevelConfig.
*\*\fun     Configure the voltage Power-on reset (POR) / power-down reset (PDR) of VDDD.
*\*\param   mode (The input parameters must be the following values):
*\*\          - SYSTEM_RUN_MODE
*\*\          - SYSTEM_LOW_POWER_MODE
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_VDDD_POR_Level_0V70    POR level is 0.70V, PDR level is 0.65V
*\*\          - PWR_VDDD_POR_Level_0V75    POR level is 0.75V, PDR level is 0.70V
*\*\          - PWR_VDDD_POR_Level_0V80    POR level is 0.80V, PDR level is 0.75V
*\*\return  none
**/
void PWR_VDDDPORLevelConfig(SYSTEM_POWER_TYPE mode, uint32_t level)
{
    __IO uint32_t temp_value;
    uint32_t bitoffset ;

    temp_value = PWR->SYSCTRL4;
    if(mode == SYSTEM_RUN_MODE)
    {
        bitoffset = PWR_VDDD_POR_LEVEL_OFFSET;
    }
    else
    {
        bitoffset = PWR_VDDD_LPPOR_LEVEL_OFFSET;
    }
    /* Clear ALS[3:0] bits bit */
    temp_value &= ~(PWR_VDDD_POR_Level_MASK << bitoffset);
    /* Set ALS[3:0] bits according to level value */
    temp_value |= (level << bitoffset);
    /* Store the new value */
    PWR->SYSCTRL4 = temp_value;
}

/**
*\*\name    PWR_DCDCPORLevelConfig.
*\*\fun     Configure the voltage Power-on reset (POR) / power-down reset (PDR) of DCDC.
*\*\param   mode (The input parameters must be the following values):
*\*\          - SYSTEM_RUN_MODE
*\*\          - SYSTEM_LOW_POWER_MODE
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_DCDC_POR_Level_0V80    POR level is 0.80V, PDR level is 0.75V
*\*\          - PWR_DCDC_POR_Level_0V85    POR level is 0.85V, PDR level is 0.80V
*\*\          - PWR_DCDC_POR_Level_0V90    POR level is 0.90V, PDR level is 0.85V
*\*\return  none
**/
void PWR_DCDCPORLevelConfig(SYSTEM_POWER_TYPE mode, uint32_t level) 
{
    __IO uint32_t* ControlRegAddr;
    __IO uint32_t temp_value;
    uint32_t bitoffset ;

    if(mode == SYSTEM_RUN_MODE)
    {
        bitoffset = PWR_DCDC_POR_LEVEL_OFFSET;
        temp_value = *(__IO uint32_t *)DCDC_ContrlBaseAddress;
        ControlRegAddr = (__IO uint32_t*)DCDC_ContrlBaseAddress;
    }
    else
    {
        bitoffset = PWR_DCDC_LPPOR_LEVEL_OFFSET;
        ControlRegAddr = &PWR->SYSCTRL4;
        temp_value = PWR->SYSCTRL4;
    }
    /* Clear ALS[3:0] bits bit */
    temp_value &= ~(PWR_DCDC_POR_Level_MASK << bitoffset);
    /* Set ALS[3:0] bits according to level value */
    temp_value |= (level << bitoffset);
    /* Store the new value */
    *ControlRegAddr = temp_value;
}

/**
*\*\name    PWR_MLDOOutputVoltageConfig.
*\*\fun     Configure the voltage output of LDO.
*\*\param   mode (The input parameters must be the following values):
*\*\          - SYSTEM_RUN_MODE
*\*\          - SYSTEM_LOW_POWER_MODE
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_MLDO_VOLTAGE_OUTPUT_LEVEL_0V80    LDO level is 0.80V
*\*\          - PWR_MLDO_VOLTAGE_OUTPUT_LEVEL_0V85    LDO level is 0.85V
*\*\          - PWR_MLDO_VOLTAGE_OUTPUT_LEVEL_0V90    LDO level is 0.90V
*\*\return  none
**/
void PWR_MLDOOutputVoltageConfig(SYSTEM_POWER_TYPE mode, uint32_t level)  
{
    __IO uint32_t temp_value;
    uint32_t bitoffset ;
    /* Get the old register value */
    temp_value = PWR->SYSCTRL4;
    if(mode == SYSTEM_RUN_MODE)
    {
        bitoffset = PWR_MLDO_VOLT_OUTPUT_LEVEL_OFFSET;
    }
    else
    {
        bitoffset = PWR_MLDO_LP_VOLT_OUTPUT_LEVEL_OFFSET;
    }
    /* Clear ALS[3:0] bits bit */
    temp_value &= ~(PWR_MLDO_VOLTAGE_OUTPUT_LEVEL_MASK << bitoffset);
    /* Set ALS[3:0] bits according to level value */
    temp_value |= (level << bitoffset);
    /* Store the new value */
    PWR->SYSCTRL4 = temp_value;
}

/**
*\*\name    PWR_DCDCOutputVoltageConfig.
*\*\fun     Configure the voltage output of DCDC.
*\*\param   mode (The input parameters must be the following values):
*\*\          - SYSTEM_RUN_MODE
*\*\          - SYSTEM_LOW_POWER_MODE
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_DCDC_VOLTAGE_OUTPUT_LEVEL_0V80    DCDC level is 0.80V
*\*\          - PWR_DCDC_VOLTAGE_OUTPUT_LEVEL_0V85    DCDC level is 0.85V
*\*\          - PWR_DCDC_VOLTAGE_OUTPUT_LEVEL_0V90    DCDC level is 0.90V
*\*\return  none
**/
void PWR_DCDCOutputVoltageConfig(SYSTEM_POWER_TYPE mode, uint32_t level) 
{
    __IO uint32_t* ControlRegAddr;
    __IO uint32_t temp_value;
    uint32_t bitoffset ;
    
    if(mode == SYSTEM_RUN_MODE)
    {
        bitoffset = PWR_DCDC_VOLT_OUTPUT_LEVEL_OFFSET;
        temp_value = *(__IO uint32_t *)DCDC_ContrlBaseAddress;
        ControlRegAddr = (__IO uint32_t*)DCDC_ContrlBaseAddress;
    }
    else
    {
        bitoffset = PWR_DCDC_LP_VOLT_OUTPUT_LEVEL_OFFSET;
        ControlRegAddr = &PWR->SYSCTRL4;
        temp_value = PWR->SYSCTRL4;
    }
    /* Clear ALS[3:0] bits bit */
    temp_value &= ~(PWR_DCDC_VOLTAGE_OUTPUT_LEVEL_MASK << bitoffset);
    /* Set ALS[3:0] bits according to level value */
    temp_value |= (level << bitoffset);
    /* Store the new value */
    *ControlRegAddr = temp_value;
}

/**
*\*\name    PWR_BKPLDOOutputVoltageConfig.
*\*\fun     Configure the voltage output of BKPLDO.
*\*\param   mode (The input parameters must be the following values):
*\*\          - SYSTEM_RUN_MODE
*\*\          - SYSTEM_LOW_POWER_MODE
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_BKPLDO_VOLTAGE_OUTPUT_LEVEL_0V80    BKPLDO level is 0.80V
*\*\          - PWR_BKPLDO_VOLTAGE_OUTPUT_LEVEL_0V90    BKPLDO level is 0.90V
*\*\return  none
**/
void PWR_BKPLDOOutputVoltageConfig(SYSTEM_POWER_TYPE mode, uint32_t level) 
{
    __IO uint32_t temp_value;
    uint32_t bitoffset ;
    /* Get the old register value */
    temp_value = PWR->SYSCTRL4;
    if(mode == SYSTEM_RUN_MODE)
    {
        bitoffset = PWR_BKPLDO_VOLT_OUTPUT_LEVEL_OFFSET;
    }
    else
    {
        bitoffset = PWR_BKPLDO_LP_VOLT_OUTPUT_LEVEL_OFFSET;
    }
    /* Clear bits bit */
    temp_value &= ~(PWR_BKPLDO_VOLTAGE_OUTPUT_LEVEL_MASK << bitoffset);
    /* Set bits according to level value */
    temp_value |= (level << bitoffset);
    /* Store the new value */
    PWR->SYSCTRL4 = temp_value;
}

/**
*\*\name    PWR_EnableLPMRVoltageOutput.
*\*\fun     Enables or disables the Voltage scaling of MR in Low power mode.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_EnableLPMRVoltageOutput(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->SYSCTRL4 |= PWR_MR_LPVSELEN;
    }
    else
    {
        PWR->SYSCTRL4 &= ~PWR_MR_LPVSELEN;
    }
}
/**
*\*\name    PWR_EnableOPTC_LPMode.
*\*\fun     Configure the OPTC PWR Mode.
*\*\param   ChipStatus (The input parameters must be the following values):
*\*\          - PWR_SYSTEM_RUN 
*\*\          - PWR_SYSTEM_STOP0 
*\*\          - PWR_SYSTEM_STOP2 
*\*\param   OPTC_Mode :
*\*\          - OPTC_POWER_ENTER_STANDBY_MODE
*\*\          - OPTC_POWER_ENTER_DEEPSTANDBY_MODE 
*\*\          - OPTC_POWER_ENTER_RUN_MODE 
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_EnableOPTC_LPMode(SYSTEM_OPTC_STATUS ChipStatus, uint32_t OPTC_Mode, FunctionalState Cmd)
{
    __IO uint32_t tempreg;
    /* Get the old register value */
    tempreg = PWR->SYSCTRL2;
    if(Cmd == ENABLE)
    {
        if(ChipStatus == PWR_SYSTEM_RUN)
        {
            /* Clear the old  value */
            tempreg &= (~(OPTC_POWER_ENTER_MODE_MASK<<22U));
            /* Set the new values */
            tempreg |= (OPTC_Mode << 22U);    
        }
        else if(ChipStatus == PWR_SYSTEM_STOP0)
        {
            /* Clear the old  value */
            tempreg &= (~(OPTC_POWER_ENTER_MODE_MASK<<20U));
            /* Set the new values */
            tempreg |= (OPTC_Mode << 20U);   
        }
        else
        {
            /* Clear the old  value */
            tempreg &= (~(OPTC_POWER_ENTER_MODE_MASK<<18U));
            /* Set the new values */
            tempreg |= (OPTC_Mode << 18U);  
        } 
    }
    else
    {
        if(ChipStatus == PWR_SYSTEM_RUN)
        {
            /* Clear the old  value */
            tempreg &= (~(OPTC_POWER_ENTER_MODE_MASK<<22U));  
        }
        else if(ChipStatus == PWR_SYSTEM_STOP0)
        {
            /* Clear the old  value */
            tempreg &= (~(OPTC_POWER_ENTER_MODE_MASK<<20U));  
        }
        else
        {
            /* Clear the old  value */
            tempreg &= (~(OPTC_POWER_ENTER_MODE_MASK<<18U)); 
        } 
    }
    /* Set the power supply configuration */
    PWR->SYSCTRL2 = tempreg;
}

/**
*\*\name    PWR_EnableTCMPiece.
*\*\fun     Enable the TCM Piece PWR.
*\*\param   PieceIndex (The input parameters must be the following values):
*\*\          - 0-63 
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_EnableTCMPiece(uint32_t PieceIndex, FunctionalState Cmd)
{
    __IO uint32_t* ControlRegAddr;
    __IO uint32_t* ReadyRegAddr;
    if(Cmd == ENABLE)
    {
        if(PieceIndex < 32U )
        {
            ReadyRegAddr = &PWR->M7TCMPRDY0;
            if(*ReadyRegAddr & (1U<< PieceIndex))
            {
                return;
            }
            ControlRegAddr = &PWR->M7TCMPG0;
        }
        else
        {
            PieceIndex = PieceIndex - 32U; 
            ReadyRegAddr = &PWR->M7TCMPRDY1;
            if(*ReadyRegAddr & (1UL<< PieceIndex))
            {
                return;
            }
            ControlRegAddr = &PWR->M7TCMPG1;
        } 
        /* Enable TCM Piece Bit */
        *ControlRegAddr &= ~(1UL<< PieceIndex);
        /* Wait TCM Piece Power on Ready */
        while((*ReadyRegAddr & (1UL<< PieceIndex)) != (1UL<< PieceIndex));
    }
    else
    {
        if(PieceIndex < 32U )
        {
            ReadyRegAddr = &PWR->M7TCMPRDY0;
            if((*ReadyRegAddr & (1UL<< PieceIndex)) == RESET )
            {
                return;
            }
            ControlRegAddr = &PWR->M7TCMPG0;
        }
        else
        {
            PieceIndex = PieceIndex-32U; 
            ReadyRegAddr = &PWR->M7TCMPRDY1;
            if((*ReadyRegAddr & (1UL<< PieceIndex)) == RESET )
            {
                return;
            }
            ControlRegAddr = &PWR->M7TCMPG1;
        } 
        /* Disable TCM Piece Bit */
        *ControlRegAddr |= (1UL<< PieceIndex);
        /* Wait TCM Piece Power down Ready */
        while((*ReadyRegAddr & (1UL<< PieceIndex)) == (1UL<< PieceIndex)) ;
    }
}
/**
*\*\name    PWR_TCMModeSelInSTOP2.
*\*\fun     Config TCM memory the low power mode when the system enter into STOP2 Enable the.
*\*\param   PieceIndex (The input parameters must be the following values):
*\*\          - 0-63 
*\*\param   Mode :
*\*\          - SYSTEM_MEMORY_STATUS_PD
*\*\          - SYSTEM_MEMORY_STATUS_RETENTION_1 
*\*\          - SYSTEM_MEMORY_STATUS_RETENTION_2 
*\*\return  none
**/
void PWR_TCMModeSelInSTOP2(uint32_t PieceIndex, uint32_t Mode)
{
    __IO uint32_t* ControlRegAddrLow;
    __IO uint32_t* ControlRegAddrHigh;
    if(PieceIndex < 32U )
    {
        ControlRegAddrLow = &PWR->M7TCMRET1N0;
        ControlRegAddrHigh = &PWR->M7TCMRET2N0;
    }
    else
    {
        PieceIndex = PieceIndex - 32U; 
        ControlRegAddrLow = &PWR->M7TCMRET1N1;
        ControlRegAddrHigh = &PWR->M7TCMRET2N1;
    }
    if(Mode == SYSTEM_MEMORY_STATUS_PD)
    {
        /* Set [M7TCMRET2Nx M7TCMRET1Nx] = [00]*/
        *ControlRegAddrLow  &= ~(1UL<< PieceIndex);
        *ControlRegAddrHigh &= ~(1UL<< PieceIndex);
    }
    else if(Mode == SYSTEM_MEMORY_STATUS_RETENTION_1)
    {
        /* Set [M7TCMRET2Nx M7TCMRET1Nx] = [11]*/
        *ControlRegAddrLow  |= (1UL<< PieceIndex);
        *ControlRegAddrHigh |= (1UL<< PieceIndex);
    }
    else if(Mode == SYSTEM_MEMORY_STATUS_RETENTION_2) 
    {
        /* Set [M7TCMRET2Nx M7TCMRET1Nx] = [10]*/
        *ControlRegAddrLow  &= ~(1UL<< PieceIndex);
        *ControlRegAddrHigh |= (1UL<< PieceIndex);
    }
    else
    {
       /* no process*/
    }
}
/**
*\*\name    PWR_SystemMemoryModeSelInSTOP2.
*\*\fun     Config system memory the low power mode when the system enter into STOP2.
*\*\param   SysMemoryType (The input parameters must be the following values):
*\*\          - SYSTEM_MEMORY_AXISRAM 
*\*\          - SYSTEM_MEMORY_AHBSRAM1 
*\*\          - SYSTEM_MEMORY_AHBSRAM2 
*\*\          - SYSTEM_MEMORY_AHBSRAM3 
*\*\          - SYSTEM_MEMORY_AHBSRAM4 
*\*\          - SYSTEM_MEMORY_AHBSRAM5S1 
*\*\          - SYSTEM_MEMORY_AHBSRAM5S2 
*\*\param   Mode :
*\*\          - SYSTEM_MEMORY_STATUS_PD
*\*\          - SYSTEM_MEMORY_STATUS_RETENTION_1 
*\*\          - SYSTEM_MEMORY_STATUS_RETENTION_2 
*\*\return  none
**/
void PWR_SystemMemoryModeSelInSTOP2(SYSTEM_MEMORY_TYPE SysMemoryType, uint32_t Mode)
{
    __IO uint32_t tempreg;
    uint32_t bitoffset ;
    
    bitoffset  = SYSTEM_MEMORY_AXISRAM_BITOFFSET;
    bitoffset += 2u*((uint32_t)SysMemoryType);
    
    /* Get the old register value */
    tempreg = PWR->SYSMEMLPCTRL;
    /* Clear the old  value */
    tempreg &= (~(SYSTEM_MEMORY_STATUS_MASK<< bitoffset));
    /* Set the new values */
    tempreg |= (Mode << bitoffset); 
    /* Store the new values */
    PWR->SYSMEMLPCTRL = tempreg;
}

/**
*\*\name    PWR_SystemMemoryModeSelInSTOP0.
*\*\fun     Config system memory the low power mode when the system enter into STOP0.
*\*\param   Mode (The input parameters must be the following values):
*\*\          - ALL_SYSTEM_MEMORY_STATUS_CHIP_DISABLE
*\*\          - ALL_SYSTEM_MEMORY_STATUS_PRECHARGE 
*\*\          - ALL_SYSTEM_MEMORY_STATUS_RETENTION_1 
*\*\return  none
**/
void PWR_SystemMemoryModeSelInSTOP0(uint32_t Mode)
{
    __IO uint32_t tempreg;
    
    /* Get the old register value */
    tempreg = PWR->SYSMEMLPCTRL;
    /* Clear the old  value */
    tempreg &= (~ALL_SYSTEM_MEMORY_STATUS_MASK);
    /* Set the new values */
    tempreg |= Mode; 
    /* Store the new values */
    PWR->SYSMEMLPCTRL = tempreg;
}

/**
*\*\name    PWR_EnableSystemMemory.
*\*\fun     Enable or disable system memory power when the system in SYSTEM_RUN mode.
*\*\param   SysMemoryType (The input parameters must be the following values):
*\*\          - SYSTEM_MEMORY_AXISRAM 
*\*\          - SYSTEM_MEMORY_AHBSRAM1 
*\*\          - SYSTEM_MEMORY_AHBSRAM2 
*\*\          - SYSTEM_MEMORY_AHBSRAM3 
*\*\          - SYSTEM_MEMORY_AHBSRAM4 
*\*\          - SYSTEM_MEMORY_AHBSRAM5S1 
*\*\          - SYSTEM_MEMORY_AHBSRAM5S2 
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_EnableSystemMemory(SYSTEM_MEMORY_TYPE SysMemoryType, FunctionalState Cmd)
{
    uint8_t bitoffset ;

    bitoffset = (uint8_t)SysMemoryType;
    if(Cmd == ENABLE)
    {
        /* Enable system memory power */
        PWR->SYSMEMLPCTRL &= (~((uint32_t)0x01u << bitoffset));
    }
    else
    {
        /* Disable system memory power */
        PWR->SYSMEMLPCTRL |= ((uint32_t)0x01u << bitoffset);
    }
}
/**
*\*\name    PWR_HSC1_HSC2_GRAPHIC_DomainEnable.
*\*\fun     Enables or disables HSC1/HSC2/Grpahic Domain power.
*\*\param   DOMAIN_Type:
*\*\          - HSC1_Domain
*\*\          - HSC2_Domain
*\*\          - GRAPHIC_Domain
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
static void PWR_HSC1_HSC2_GRAPHIC_DomainEnable(DOMAIN_Type DomainType, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        /*Select the switcher mode  */
        PWR->SYSCTRL3 |= (PWR_SYSCTRL3_GRC_PSWACK1<< DomainType);
        /*Enable the domain power */
        PWR->SYSCTRL3 |= (PWR_SYSCTRL3_GRC_PWREN<< DomainType);
        /*wait power on ready flag */
        while( (PWR->SYSCTRL3& (PWR_SYSCTRL3_GRC_PWRRDY<< DomainType)) != (PWR_SYSCTRL3_GRC_PWRRDY<< DomainType));
        /*Set domain out of reset state*/
        PWR->SYSCTRL3 |= (PWR_SYSCTRL3_GRC_FUCEN<< DomainType);
        /* remove isolation on domain output signals*/
        PWR->SYSCTRL3 |= (PWR_SYSCTRL3_GRC_ISNEN<< DomainType);
    }
    else
    {
        /* Apply isolation on domain domain output signals*/
        PWR->SYSCTRL3 &= ~(PWR_SYSCTRL3_GRC_ISNEN<< DomainType);
        /*Set domain domain reset state*/
        PWR->SYSCTRL3 &= ~(PWR_SYSCTRL3_GRC_FUCEN<< DomainType);
        /*Disable the domain power */
        PWR->SYSCTRL3 &= ~(PWR_SYSCTRL3_GRC_PWREN<< DomainType);

        /*wait the power down ready flag */
        while((PWR->SYSCTRL3& (PWR_SYSCTRL3_GRC_PWRRDY<< DomainType)) == (PWR_SYSCTRL3_GRC_PWRRDY<< DomainType)); 
    }
}


/**
*\*\name    PWR_ESC_DomainEnable.
*\*\fun     Enables or disables ESC Domain power.
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
static void PWR_ESC_DomainEnable(FunctionalState Cmd)
{
  if(Cmd == ENABLE)
  {
      /*Select the switcher mode  */
      PWR->ESCCTRL |= (ESC_PSWACK1);
      /*Enable the ESC power */
      PWR->ESCCTRL |= (ESC_POWER_ENABLE);
      /*wait power on ready flag */
      while((PWR->ESCCTRL& (ESC_POWER_RDY)) != ESC_POWER_RDY);
      /*Set ESC out of reset state*/
      PWR->ESCCTRL |= (ESC_FUNCTION_ENABLE);
      /* remove isolation on ESC output signals*/
      PWR->ESCCTRL |= (ESC_ISOLATION_ENABLE);
  }
  else
  {
      /* Apply isolation on ESC output signals*/
      PWR->ESCCTRL &= ~(ESC_ISOLATION_ENABLE);
      /*Set ESC reset state*/
      PWR->ESCCTRL &= ~(ESC_FUNCTION_ENABLE);
      /*Disable the ESC power */
      PWR->ESCCTRL &= ~(ESC_POWER_ENABLE);

      /*wait the power down ready flag */
      while((PWR->ESCCTRL& ESC_POWER_RDY) == ESC_POWER_RDY);
  }
}

/**
*\*\name    PWR_MDMA_DomainEnable.
*\*\fun     Enables or disables MDMA power.
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void PWR_MDMA_DomainEnable(FunctionalState Cmd)
{
  if(Cmd == ENABLE)
  {
      /*Select the switcher mode  */
      PWR->MDMACTRL |= (MDMA_PSWACK1);
      /*Enable the MDMA power */
      PWR->MDMACTRL |= (MDMA_POWER_ENABLE);
      /*wait power on ready flag */
      while((PWR->MDMACTRL& (MDMA_POWER_RDY)) != MDMA_POWER_RDY);
      /*Set MDMA out of reset state*/
      PWR->MDMACTRL |= (MDMA_FUNCTION_ENABLE);
      /* remove isolation on MDMA output signals*/
      PWR->MDMACTRL |= (MDMA_ISOLATION_ENABLE);
  }
  else
  {
      /* Apply isolation on MDMA output signals*/
      PWR->MDMACTRL &= ~(MDMA_ISOLATION_ENABLE);
      /*Set MDMA reset state*/
      PWR->MDMACTRL &= ~(MDMA_FUNCTION_ENABLE);
      /*Disable the MDMA power */
      PWR->MDMACTRL &= ~(MDMA_POWER_ENABLE);

      /*wait the power down ready flag */
      while((PWR->MDMACTRL& MDMA_POWER_RDY) == MDMA_POWER_RDY); 
  }
}

/**
*\*\name    PWR_SHRTIM_DomainEnable.
*\*\fun     Enables or disables shrtimx power.
*\*\param   shrtimx :
*\*\          - Power_SHRTIM1
*\*\          - Power_SHRTIM2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void PWR_SHRTIM_DomainEnable(SHRTIM_PowerType shrtimx, FunctionalState Cmd) //test
{
  if(Cmd == ENABLE)
  {
      if((PWR->SHRTIMCTRL& SHRTIMA_POWER_RDY) != SHRTIMA_POWER_RDY)
      {
          /*Power on SHRTIM AFE First */
          /*Select the switcher mode */
          PWR->SHRTIMCTRL |= (SHRTIMA_PSWACK1);
          /*Enable the  SHRTIM AFE power */
          PWR->SHRTIMCTRL |= (SHRTIMA_POWER_ENABLE);
          /*wait power on ready flag */
          while((PWR->SHRTIMCTRL& SHRTIMA_POWER_RDY) != SHRTIMA_POWER_RDY);
          /*Set  SHRTIM AFE out of reset state*/
          PWR->SHRTIMCTRL |= (SHRTIMA_FUNCTION_ENABLE);
          /* remove isolation on  SHRTIM AFE output signals*/
          PWR->SHRTIMCTRL |= (SHRTIMA_ISOLATION_ENABLE);
      }
      else
      {
         /*no process*/
      }

      /*Then power on SHRTIM1 or SHRTIM2 */
      /*Select the switcher mode */
      PWR->SHRTIMCTRL |= (SHRTIM1_PSWACK1<<(8U*(uint32_t)shrtimx));
      /*Enable the  SHRTIM AFE power */
      PWR->SHRTIMCTRL |= (SHRTIM1_POWER_ENABLE<<(8U*(uint32_t)shrtimx));
      /*wait power on ready flag */
      while((PWR->SHRTIMCTRL& (SHRTIM1_POWER_RDY<<(8U*(uint32_t)shrtimx))) != (SHRTIM1_POWER_RDY<< (8U*(uint32_t)shrtimx)));
      /*Set  SHRTIM AFE out of reset state*/
      PWR->SHRTIMCTRL |= (SHRTIM1_FUNCTION_ENABLE<<(8U*(uint32_t)shrtimx));
      /* remove isolation on  SHRTIM AFE output signals*/
      PWR->SHRTIMCTRL |= (SHRTIM1_ISOLATION_ENABLE<<(8U*(uint32_t)shrtimx));
  }
  else
  {
      /*Power off SHRTIM1 or SHRTIM2 First */
      /* Apply isolation on  SHRTIM AFE output signals*/
      PWR->SHRTIMCTRL &= ~(SHRTIM1_ISOLATION_ENABLE<<(8U*(uint32_t)shrtimx));
      /*Set  SHRTIM AFE reset state*/
      PWR->SHRTIMCTRL &= ~(SHRTIM1_FUNCTION_ENABLE<<(8U*(uint32_t)shrtimx));
      /*Disable the SHRTIM AFE power */
      PWR->SHRTIMCTRL &= ~(SHRTIM1_POWER_ENABLE<<(8U*(uint32_t)shrtimx));

      /*wait the power down ready flag */
      while((PWR->SHRTIMCTRL& (SHRTIM1_POWER_RDY<<(8U*(uint32_t)shrtimx))) == (SHRTIM1_POWER_RDY<<(8U*(uint32_t)shrtimx))); 
      
      /*if Both SHRTIM1 and SHRTIM2 off, then power off SHRTIM AFE */
      if( (((PWR->SHRTIMCTRL&SHRTIM2_POWER_RDY) != SHRTIM2_POWER_RDY )&&(shrtimx == Power_SHRTIM1))
        ||(((PWR->SHRTIMCTRL&SHRTIM1_POWER_RDY) != SHRTIM1_POWER_RDY )&&(shrtimx == Power_SHRTIM2)) )
      {
          /* Apply isolation on  SHRTIM AFE output signals*/
          PWR->SHRTIMCTRL &= ~(SHRTIMA_ISOLATION_ENABLE);
          /*Set  SHRTIM AFE reset state*/
          PWR->SHRTIMCTRL &= ~(SHRTIMA_FUNCTION_ENABLE);
          /*Disable the SHRTIM AFE power */
          PWR->SHRTIMCTRL &= ~(SHRTIMA_POWER_ENABLE);

          /*wait the power down ready flag */
          while((PWR->SHRTIMCTRL& SHRTIMA_POWER_RDY) == SHRTIMA_POWER_RDY); 
      }
      else
      {
         /*no process*/
      }
  }
}

/**
*\*\name    PWR_MoudlePowerEnable.
*\*\fun     Enables or disables the specified module power.
*\*\param   module :
*\*\          - GRAPHIC_GPU_PWRCTRL
*\*\          - GRAPHIC_LCDC_PWRCTRL
*\*\          - GRAPHIC_JPEG_PWRCTRL
*\*\          - GRAPHIC_DSI_PWRCTRL
*\*\          - GRAPHIC_DVP_PWRCTRL
*\*\          - HSC2_ETH2_PWRCTRL
*\*\          - HSC2_USB2_PWRCTRL
*\*\          - HSC2_SDMMC2_PWRCTRL
*\*\          - HSC1_ETH1_PWRCTRL
*\*\          - HSC1_USB1_PWRCTRL
*\*\          - HSC1_SDMMC1_PWRCTRL
*\*\          - FMAC_PWRCTRL
*\*\          - ESC_PWRCTRL
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void PWR_MoudlePowerEnable(uint32_t module, FunctionalState Cmd) 
{
    if( (module == GRAPHIC_GPU_PWRCTRL) ||(module == GRAPHIC_LCDC_PWRCTRL)|| \
        (module == GRAPHIC_JPEG_PWRCTRL)||(module == GRAPHIC_DSI_PWRCTRL) || (module == GRAPHIC_DVP_PWRCTRL))
    {
        if(Cmd == ENABLE)
        {
            PWR->IPMEMCTRL &= (~module);
            while((PWR->IPMEMCTRLSTS & module ) != module);
            if( (PWR->SYSCTRL3&PWR_SYSCTRL3_GRC_PWRRDY) != PWR_SYSCTRL3_GRC_PWRRDY)
            {
                PWR_HSC1_HSC2_GRAPHIC_DomainEnable(GRAPHIC_Domain, ENABLE);
            }
            else
            {
                /*no process*/
            }
        }
        else
        {
            if((PWR->IPMEMCTRLSTS&GRAPHIC_MODULE_MASK) == module)
            {
                PWR_HSC1_HSC2_GRAPHIC_DomainEnable(GRAPHIC_Domain, DISABLE);
            }
            else
            {
                /*no process*/
            }
            PWR->IPMEMCTRL |= module;
            while((PWR->IPMEMCTRLSTS & module ) == module);
        }
    }
    else if((module == HSC2_ETH2_PWRCTRL) ||(module == HSC2_USB2_PWRCTRL)||(module == HSC2_SDMMC2_PWRCTRL))
    {
        if(Cmd == ENABLE)
        {
            PWR->IPMEMCTRL &= (~module);
            while((PWR->IPMEMCTRLSTS & module ) != module);
            if( (PWR->SYSCTRL3&PWR_SYSCTRL3_HSC2_PWRRDY) != PWR_SYSCTRL3_HSC2_PWRRDY)
            {
                PWR_HSC1_HSC2_GRAPHIC_DomainEnable(HSC2_Domain, ENABLE);
            }
            else
            {
                /*no process*/
            }
        }
        else
        {
            if((PWR->IPMEMCTRLSTS&HSC2_MODULE_MASK) == module)
            {
                PWR_HSC1_HSC2_GRAPHIC_DomainEnable(HSC2_Domain, DISABLE);
            }
            else
            {
                /*no process*/
            }
            PWR->IPMEMCTRL |= module;
            while((PWR->IPMEMCTRLSTS & module ) == module);
        }
    }
    else if((module == HSC1_ETH1_PWRCTRL) ||(module == HSC1_USB1_PWRCTRL)||(module == HSC1_SDMMC1_PWRCTRL))
    {
        if(Cmd == ENABLE)
        {
            PWR->IPMEMCTRL &= (~module);
            while((PWR->IPMEMCTRLSTS & module ) != module);
            if( (PWR->SYSCTRL3&PWR_SYSCTRL3_HSC1_PWRRDY) != PWR_SYSCTRL3_HSC1_PWRRDY)
            {
                PWR_HSC1_HSC2_GRAPHIC_DomainEnable(HSC1_Domain, ENABLE);
            }
            else
            {
                /*no process*/
            }
        }
        else
        {
            if((PWR->IPMEMCTRLSTS&HSC1_MODULE_MASK) == module)
            {
                PWR_HSC1_HSC2_GRAPHIC_DomainEnable(HSC1_Domain, DISABLE);
            }
            else
            {
                /*no process*/
            }
            PWR->IPMEMCTRL |= module;
            while((PWR->IPMEMCTRLSTS & module ) == module);
        }
    }
    else if(module == ESC_PWRCTRL) 
    {
        if(Cmd == ENABLE)
        {
            PWR->IPMEMCTRL &= (~ESC_PWRCTRL);
            while((PWR->IPMEMCTRLSTS & ESC_PWRRDY_FLAG ) != ESC_PWRRDY_FLAG);
            PWR_ESC_DomainEnable(ENABLE);
        }
        else
        {
            PWR_ESC_DomainEnable(DISABLE);
            PWR->IPMEMCTRL |= ESC_PWRCTRL;
            while((PWR->IPMEMCTRLSTS & ESC_PWRRDY_FLAG) == ESC_PWRRDY_FLAG);
        }
    }
    else if(module == FMAC_PWRCTRL) 
    {
        if(Cmd == ENABLE)
        {
            PWR->IPMEMCTRL &= (~FMAC_PWRCTRL);
            while((PWR->IPMEMCTRLSTS & FMAC_PWRRDY_FLAG ) != FMAC_PWRRDY_FLAG);
        }
        else
        { 
            PWR->IPMEMCTRL |= FMAC_PWRCTRL;
            while((PWR->IPMEMCTRLSTS & FMAC_PWRRDY_FLAG) == FMAC_PWRRDY_FLAG);
        }
    }
    else
    {
        /*no process */
    }
}

/**
*\*\name    PWR_EnableBKPSRAMRetainInStandbyMode.
*\*\fun     Enable or disable BKP SRAM retain in standby mode.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void PWR_EnableBKPSRAMRetainInStandbyMode(FunctionalState Cmd)
{ 
    if(Cmd == ENABLE)
    {
       /* Set BSRSTBRET bit */
       //*ControlRegAddr |= PWR_STBRET_ENABLE;
        PWR->M4CTRL2 |= PWR_STBRET_ENABLE; 
        PWR->M7CTRL2 |= PWR_STBRET_ENABLE; 
    }
    else
    {
       /* Reset BSRSTBRET bit */
       //*ControlRegAddr &= (~PWR_STBRET_ENABLE);
        PWR->M4CTRL2 &= (~PWR_STBRET_ENABLE);
        PWR->M7CTRL2 &= (~PWR_STBRET_ENABLE); 
    }  
}


/**
*\*\name    PWR_EnableBKPSRAMRetainInVbatMode.
*\*\fun     Enable or disable BKP SRAM retain in Vbat mode.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void PWR_EnableBKPSRAMRetainInVbatMode(FunctionalState Cmd)
{ 
    __IO uint32_t* ControlRegAddr;
    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr = &PWR->M7CTRL2;
    }
    else
    {
        ControlRegAddr = &PWR->M4CTRL2;
    }
    if(Cmd == ENABLE)
    {
       /* Set BSRVBRET bit */
       *ControlRegAddr |= PWR_VBATRET_ENABLE;
    }
    else
    {
       /* Reset BSRVBRET bit */
       *ControlRegAddr &= (~PWR_VBATRET_ENABLE);
    } 
}

/**
*\*\name    PWR_WakeUpPinEnable.
*\*\fun     Enables the Wakeup Pin functionality.
*\*\param   pin (The input parameters must be the following values):
*\*\          - WAKEUP_PIN0EN   WKUP0(PA0)
*\*\          - WAKEUP_PIN1EN   WKUP1(PA2)
*\*\          - WAKEUP_PIN2EN   WKUP2(PC13)
*\*\          - WAKEUP_PIN3EN   WKUP3(PI8)
*\*\          - WAKEUP_PIN4EN   WKUP4(PI11)
*\*\          - WAKEUP_PIN5EN   WKUP5(PC1)
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_WakeUpPinEnable(uint32_t pin, FunctionalState Cmd)
{
    __IO uint32_t* ControlRegAddr;
    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr = &PWR->M7CTRLSTS;
    }
    else
    {
        ControlRegAddr = &PWR->M4CTRLSTS;
    }

    if(Cmd == ENABLE)
    {
        /* Set WKUPxEN bit */
        *ControlRegAddr |= pin;
    }
    else
    {
        /* Clear WKUPxEN bit*/
        *ControlRegAddr &= (~pin);
    }
}

/**
*\*\name    PWR_WakeUpPinPolarity.
*\*\fun     Enables the Wakeup Pin polarity.
*\*\param   pin (The input parameters must be the following values):
*\*\          - WAKEUP_PIN0POL   WKUP0(PA0)
*\*\          - WAKEUP_PIN1POL   WKUP1(PA2)
*\*\          - WAKEUP_PIN2POL   WKUP2(PC13)
*\*\          - WAKEUP_PIN3POL   WKUP3(PI8)
*\*\          - WAKEUP_PIN4POL   WKUP4(PI11)
*\*\          - WAKEUP_PIN5POL   WKUP5(PC1)
*\*\param   polarity (The input parameters must be the following values): 
*\*\          - POL_HIGH
*\*\          - POL_LOW
*\*\return  none
**/
void PWR_WakeUpPinPolarity(uint32_t pin, WAKEUP_PIN_POL polarity)
{
    __IO uint32_t* ControlRegAddr;

    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr = &PWR->M7CTRLSTS;
    }
    else
    {
        ControlRegAddr = &PWR->M4CTRLSTS;
    }

    if(polarity == POL_LOW)
    {
        /* Set WKUPxPOL bit */
        *ControlRegAddr |= pin;
    }
    else
    {
        /* Clear WKUPxPOL bit*/
        *ControlRegAddr &= (~pin);
    }
}


/**
*\*\name   PWR_GetFlagStatus.
*\*\fun    Checks whether the specified PWR flag is set or not.
*\*\param PWR_FLAG (specifies the flag to check):
*\*\      This parameter can be one of the following values:
*\*\          - PWR_FLAG_WKUP0     PA0 Wake Up flag
*\*\          - PWR_FLAG_WKUP1     PA2 Wake Up flag
*\*\          - PWR_FLAG_WKUP2     PC13 Wake Up flag
*\*\          - PWR_FLAG_WKUP3     PI8 Wake Up flag
*\*\          - PWR_FLAG_WKUP4     PI11 Wake Up flag
*\*\          - PWR_FLAG_WKUP5     PC1 Wake Up flag
*\*\          - PWR_FLAG_WKUPP     RTC Wake Up flag
*\*\          - PWR_FLAG_STANDBY   StandBy mode flag
*\*\          - PWR_FLAG_VBAT      VBAT mode flag
*\*\return The new state of PWR_FLAG 
*\*\          - SET
*\*\          - RESET
 */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus;
    __IO uint32_t* ControlRegAddr;
    
    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr = &PWR->M7CTRLSTS;
    }
    else
    {
        ControlRegAddr = &PWR->M4CTRLSTS;
    }
    /* Check the parameters */
    if (((*ControlRegAddr) & PWR_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}

/**
*\*\name   PWR_GetSystemFlagStatus.
*\*\fun    Checks whether the specified System PWR flag is set or not.
*\*\param PWR_FLAG (specifies the flag to check):
*\*\      This parameter can be one of the following values:
*\*\          - PWR_SYSFLAG_PVDO  
*\*\          - PWR_SYSFLAG_AVDO
*\*\          - PWR_SYSFLAG_OTPRDY 
*\*\          - PWR_FLAG_DCDCBP  
*\*\return The new state of PWR_FLAG 
*\*\          - SET
*\*\          - RESET
 */
FlagStatus PWR_GetSystemFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus;

    /* Check the parameters */
    if ((PWR->SYSCTRLSTS & PWR_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}
/**
*\*\name   PWR_ClearFlag.
*\*\fun    Clears the PWR's pending flags.
*\*\param  PWR_FLAG (specifies the flag to clear):
*\*\       This parameter can be one of the following values:
*\*\          - PWR_CLR_WKUPx     PA0/PA2/PC13/PI8/PI11/PC1/RTC Wake Up flag
*\*\          - PWR_CLR_STANDBY   StandBy mode flag
*\*\          - PWR_CLR_VBAT      VBAT mode flag
*\*\return  none
 */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
    __IO uint32_t* ControlRegAddr;
    
    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr = &PWR->M7CTRL1;
    }
    else
    {
        ControlRegAddr = &PWR->M4CTRL1;
    }
    /* Clear PWR_CLR_WKUPx or PWR_CLR_STANDBY PWR_CLR_VBAT bit */
    *ControlRegAddr |= PWR_FLAG;     
}


/**
*\*\name    PWR_WakeUpRTCEnable.
*\*\fun     Enables the Wakeup RTC functionality.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_WakeUpRTCEnable(FunctionalState Cmd)
{
    __IO uint32_t* ControlRegAddr;
    
    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr = &PWR->M7CTRL2;
    }
    else
    {
        ControlRegAddr = &PWR->M4CTRL2;
    }
    if(Cmd == ENABLE)
    {
        *ControlRegAddr |=  WAKEUP_RTCEN;
    }
    else
    {
        *ControlRegAddr &= ~WAKEUP_RTCEN;
    }
}

/**
*\*\name    PWR_WakeUpNRSTEnable.
*\*\fun     Enable or Disable NRST Wakeup functionality in standby mode.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_WakeUpNRSTEnable(FunctionalState Cmd)
{
    __IO uint32_t* ControlRegAddr;
    
    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr = &PWR->M7CTRL2;
    }
    else
    {
        ControlRegAddr = &PWR->M4CTRL2;
    }
    if(Cmd == ENABLE)
    {
        *ControlRegAddr |=  WAKEUP_NRSTEN;
    }
    else
    {
        *ControlRegAddr &= ~WAKEUP_NRSTEN;
    }
}


/**
*\*\name    PWR_EnterSLEEPMode.
*\*\fun     System Enters SLEEP mode.
*\*\param   SLEEPONEXIT (The input parameters must be the following values):
*\*\          - PWR_SLEEP_ON_EXIT
*\*\          - PWR_SLEEP_NOW
*\*\param   PWR_STOPEntry (The input parameters must be the following values):
*\*\          - PWR_SLEEPENTRY_WFI    enter SLEEP mode with WFI instruction
*\*\          - PWR_SLEEPENTRY_WFE    enter SLEEP mode with WFE instruction
*\*\return  none
**/
void PWR_EnterSLEEPMode(uint8_t SLEEPONEXIT, uint8_t PWR_SLEEPEntry)
{
    __IO uint32_t* ControlRegAddr;
    
    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr = &PWR->M7CTRL2;
    }
    else
    {
        ControlRegAddr = &PWR->M4CTRL2;
    }
    /* Clear STOP2S bits */
    *ControlRegAddr &= ~PWR_STOP2EN;

    /* CLEAR SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP);

    /* Select SLEEPONEXIT mode entry ------------------------------------------*/
    if(SLEEPONEXIT == 1)
    {
      /* the MCU enters Sleep mode as soon as it exits the lowest priority ISR */
      SCB->SCR |= SCB_SCR_SLEEPONEXIT;
    }
    else if(SLEEPONEXIT == 0)
    {
      /* Sleep-now */
      SCB->SCR &= (uint32_t)(~(uint32_t)SCB_SCR_SLEEPONEXIT);
    }
    else
    {
      /* no process */
    }

    /* Select SLEEP mode entry ------------------------------------------------*/
    if(PWR_SLEEPEntry == PWR_SLEEPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
}


/**
*\*\name    PWR_EnterSTOP0Mode.
*\*\fun     System Enters STOP0 mode.
*\*\param   PWR_STOPEntry (The input parameters must be the following values):
*\*\          - PWR_STOPENTRY_WFI    enter STOP mode with WFI instruction
*\*\          - PWR_STOPENTRY_WFE    enter STOP mode with WFE instruction
*\*\return  none
**/
void PWR_EnterSTOP0Mode(uint8_t PWR_STOPEntry)
{
    __IO uint32_t* ControlRegAddr1;
    __IO uint32_t* ControlRegAddr2;
    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr1 = &PWR->M7CTRL1;
        ControlRegAddr2 = &PWR->M7CTRL2;
    }
    else
    {
        ControlRegAddr1 = &PWR->M4CTRL1;
        ControlRegAddr2 = &PWR->M4CTRL2;
    }
    /* Clear PDDS */
    *ControlRegAddr1 &= ~PWR_PDSEN;
    /* Clear STOP2S bits */
    *ControlRegAddr2 &= ~PWR_STOP2EN;
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    /* Select STOP mode entry -----------------------------*/
    if (PWR_STOPEntry == PWR_STOPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)(~(uint32_t)SCB_SCR_SLEEPDEEP);
}


/**
*\*\name    PWR_EnterSTOP2Mode.
*\*\fun     System Enters STOP2 mode.
*\*\param   PWR_STOPEntry (The input parameters must be the following values):
*\*\          - PWR_STOPENTRY_WFI    enter STOP mode with WFI instruction
*\*\          - PWR_STOPENTRY_WFE    enter STOP mode with WFE instruction
*\*\return  none
**/
void PWR_EnterSTOP2Mode(uint8_t PWR_STOPEntry)
{
    __IO uint32_t* ControlRegAddr1;
    __IO uint32_t* ControlRegAddr2;
    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr1 = &PWR->M7CTRL1;
        ControlRegAddr2 = &PWR->M7CTRL2;
    }
    else
    {
        ControlRegAddr1 = &PWR->M4CTRL1;
        ControlRegAddr2 = &PWR->M4CTRL2;
    }
    /* Clear PDDS */
    *ControlRegAddr1 &= ~PWR_PDSEN;
    /* Clear STOP2S bits */
    *ControlRegAddr2 |= PWR_STOP2EN;

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    /* Select STOP mode entry -----------------------------*/
    if (PWR_STOPEntry == PWR_STOPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)(~(uint32_t)SCB_SCR_SLEEPDEEP);
}

/**
*\*\name    PWR_EnterSTANDBYMode.
*\*\fun     System Enters STANDBY mode.
*\*\param   none
*\*\return  none
**/
void PWR_EnterSTANDBYMode(void)
{
    __IO uint32_t* ControlRegAddr1;
    __IO uint32_t* ControlRegAddr2;
    /*Get contrl register address*/
    if(Get_CurrentCPU() == CM7_CPU)
    {
        ControlRegAddr1 = &PWR->M7CTRL1;
        ControlRegAddr2 = &PWR->M7CTRL2;
    }
    else
    {
        ControlRegAddr1 = &PWR->M4CTRL1;
        ControlRegAddr2 = &PWR->M4CTRL2;
    }
    /* Clear Wake-up flag */
    *ControlRegAddr1 |= PWR_CLR_WKUPx;
    /* Clear STOP2S bits */
    *ControlRegAddr2 &= ~PWR_STOP2EN;
    /* Set PDDS bit to select STANDBY mode */
    *ControlRegAddr1 |= PWR_PDSEN;
    /*Off BG , 1A version ,1B version will remove this*/
    PWR->SYSCTRL2 &= ~0x400U;

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

/* This option is used to ensure that store operations are completed */
#if defined(__CC_ARM)
    __force_stores();
#endif
    /* Request Wait For Interrupt */
    __WFI();

}

