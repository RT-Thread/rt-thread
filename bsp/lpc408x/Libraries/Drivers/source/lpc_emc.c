/**********************************************************************
* $Id$      lpc_emc.c           2011-06-02
*//**
* @file     lpc_emc.c
* @brief    Contains all functions support for EMC firmware library
*           on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _EMC

#include "lpc_emc.h"
#include "lpc_clkpwr.h"
#include "lpc_pinsel.h"

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup EMC
 * @{
 */
 
/** @defgroup EMC_Public_Functions
 * @{
 */

/*********************************************************************
 * @brief        Calculate refresh timer (the multiple of 16 CCLKs)
 * @param[in]    freq - frequency of EMC Clk
 * @param[in]    time - micro second
 * @return       None
 **********************************************************************/
uint32_t EMC_SDRAM_REFRESH(uint32_t time)
{
    uint32_t emc_freq = CLKPWR_GetCLK(CLKPWR_CLKTYPE_EMC);
    return (((uint64_t)((uint64_t)time * emc_freq)/16000000ull)+1);
}
/*********************************************************************
 * @brief        Calculate EMC Clock from nano second
 * @param[in]    time - nano second
 * @return       None
 **********************************************************************/
uint32_t EMC_NS2CLK(uint32_t time){
    uint32_t emc_freq = CLKPWR_GetCLK(CLKPWR_CLKTYPE_EMC);
    return (((uint64_t)time*emc_freq/1000000000ull));
}

/*********************************************************************
 * @brief        Power on EMC Block
 * @param[in]    None
 * @return       None
 **********************************************************************/
EMC_FUNC_CODE EMC_PwrOn(void)
{
    // If CPU clock is > 80 MHz, then divide it by two to create the EMC clock
    if(CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU) > 80000000) {
        CLKPWR_SetCLKDiv(CLKPWR_CLKTYPE_EMC, 1); // CPU clock / 2
    } else {
        CLKPWR_SetCLKDiv(CLKPWR_CLKTYPE_EMC, 0); // Same clock as CPU
    }

    // Power on
    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCEMC, ENABLE);

    // Enable
    LPC_EMC->Control = EMC_Control_E;

    return EMC_FUNC_OK;
}
/*********************************************************************//**
 * @brief         Initialize external dynamic memory
 * @param[in]    pConfig    Configuration
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM/EMC_FUNC_ERR
 **********************************************************************/
EMC_FUNC_CODE DynMem_Init(EMC_DYN_MEM_Config_Type* pConfig)
{
     uint32_t i = 0;
     EMC_FUNC_CODE ret = EMC_FUNC_OK;

    /* Pin configuration:
    * P2.16 - /EMC_CAS
    * P2.17 - /EMC_RAS
    * P2.18 - EMC_CLK[0]
    * P2.19 - EMC_CLK[1]
    *
    * P2.20 - EMC_DYCS0
    * P2.21 - EMC_DYCS1
    * P2.22 - EMC_DYCS2
    * P2.23 - EMC_DYCS3
    *
    * P2.24 - EMC_CKE0
    * P2.25 - EMC_CKE1
    * P2.26 - EMC_CKE2
    * P2.27 - EMC_CKE3
    *
    * P2.28 - EMC_DQM0
    * P2.29 - EMC_DQM1
    * P2.30 - EMC_DQM2
    * P2.31 - EMC_DQM3
    *
    * P3.0-P3.31 - EMC_D[0-31]
    * P4.0-P4.23 - EMC_A[0-23]
    * P5.0-P5.1  - EMC_A[24-25]
    *
    * P4.25 - EMC_WE
    */
    PINSEL_ConfigPin(2,16,1);
    PINSEL_ConfigPin(2,17,1);
    PINSEL_ConfigPin(2,18,1);
    PINSEL_ConfigPin(2,19,1);
    PINSEL_ConfigPin(2,20,1);
    PINSEL_ConfigPin(2,21,1);
    PINSEL_ConfigPin(2,22,1);
    PINSEL_ConfigPin(2,23,1);
    PINSEL_ConfigPin(2,24,1);
    PINSEL_ConfigPin(2,25,1);
    PINSEL_ConfigPin(2,26,1);
    PINSEL_ConfigPin(2,27,1);
    PINSEL_ConfigPin(2,28,1);
    PINSEL_ConfigPin(2,29,1);
    PINSEL_ConfigPin(2,30,1);
    PINSEL_ConfigPin(2,31,1);

    for(i = 0; i < 32; i++)
    {
        PINSEL_ConfigPin(3,i,1);
        PINSEL_ConfigPin(4,i,1);
    }
    PINSEL_ConfigPin(5,0,1);
    PINSEL_ConfigPin(5,1,1);


    // Power On
    ret |= EMC_PwrOn();

    /*Init SDRAM controller*/
    LPC_SC->EMCDLYCTL |= (8<<0);
    /*Set data read delay*/
    LPC_SC->EMCDLYCTL |=(8<<8);
    LPC_SC->EMCDLYCTL |= (0x08 <<16);

    ret |= EMC_ConfigEndianMode(EMC_Config_Little_Endian_Mode);
    
         /* Dynamic memory setting */
    ret |= EMC_DynCtrlSelfRefresh(EMC_DYNAMIC_CTRL_SR_NORMALMODE);
    ret |= EMC_DynCtrlPowerDownMode(EMC_DYNAMIC_CTRL_DP_NORMAL);
    ret |= EMC_DynCtrlClockEnable(EMC_DYNAMIC_CTRL_CE_ALLCLK_HI);
    ret |= EMC_DynCtrlMMC(EMC_DYNAMIC_CTRL_MMC_CLKOUT_ENABLED);
    ret |= EMC_DynCtrlClockControl(EMC_DYNAMIC_CTRL_CE_CLKOUT_CONT);

    /* Timing */
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_REFRESH_TIMER, pConfig->RefreshTime);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_READ_CONFIG, pConfig->ReadConfig);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TRP, pConfig->PrechargeCmdPeriod);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TRAS, pConfig->Active2PreChargeTime);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TSREX, pConfig->SeftRefreshExitTime);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TAPR, pConfig->DataOut2ActiveTime);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TDAL, pConfig->DataIn2ActiveTime);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TWR, pConfig->WriteRecoveryTime);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TRC, pConfig->Active2ActivePeriod);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TRFC, pConfig->AutoRefrehPeriod);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TXSR, pConfig->ExitSelfRefreshTime);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TRRD, pConfig->ActiveBankLatency);
    ret |= EMC_SetDynMemoryParameter(EMC_DYN_MEM_TMRD, pConfig->LoadModeReg2Active);
    ret |= EMC_DynMemRAS(pConfig->CSn,pConfig->RASLatency);
    ret |= EMC_DynMemCAS(pConfig->CSn,pConfig->CASLatency);

    ret |= EMC_DynMemConfigMD(pConfig->CSn,EMC_DYNAMIC_CFG_MEMDEV_SDRAM);
    ret |= EMC_DynMemConfigAM(pConfig->CSn, pConfig->AddrBusWidth, pConfig->AddrMap, pConfig->DataWidth, pConfig->ChipSize);

    return ret;
}

/*********************************************************************//**
 * @brief         Initialize external static memory
 * @param[in]    pConfig    Configuration
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM/EMC_FUNC_ERR
 **********************************************************************/
EMC_FUNC_CODE StaticMem_Init(EMC_STATIC_MEM_Config_Type* pConfig)
{
    uint32_t i;
    EMC_FUNC_CODE ret = EMC_FUNC_OK;
    /* Pin configuration:
    * P4.30 - /EMC_CS0
    * P4.31 - /EMC_CS1
    * P2.14 - /EMC_CS2
    * P2.15 - /EMC_CS3
    *
    *
    * P3.0-P3.31 - EMC_D[0-31]
    * P4.0-P4.23 - EMC_A[0-23]
    * P5.0-P5.1  - EMC_A[24-25]
    *
    * P4.24 - /EMC_OE
    * P4.25 - /EMC_WE
    *

    */
    PINSEL_ConfigPin(2,14,1);
    PINSEL_ConfigPin(2,15,1);

    for(i = 0; i < 32; i++)
    {
        PINSEL_ConfigPin(3,i,1);
        PINSEL_ConfigPin(4,i,1);
    }
    PINSEL_ConfigPin(5,0,1);
    PINSEL_ConfigPin(5,1,1);

    // Power On
    ret |= EMC_PwrOn();

    // Configuration
    if(pConfig->AddressMirror)
    {
        LPC_EMC->Control |= EMC_Control_M;
    }

     ret |= EMC_StaMemConfigMW(pConfig->CSn,pConfig->DataWidth);
    
    if(pConfig->PageMode)
         ret |= EMC_StaMemConfigPM(pConfig->CSn,EMC_CFG_PM_ASYNC_ENABLE);
    else
         ret |= EMC_StaMemConfigPM(pConfig->CSn,EMC_CFG_PM_DISABLE);

    if(pConfig->ByteLane)
         ret |= EMC_StaMemConfigPB(pConfig->CSn, EMC_CFG_BYTELAND_READ_BITSLOW);
    else
         ret |= EMC_StaMemConfigPB(pConfig->CSn, EMC_CFG_BYTELAND_READ_BITSHIGH);

    if(pConfig->ExtendedWait)
         ret |= EMC_StaMemConfigEW(pConfig->CSn,EMC_CFG_EW_ENABLED);
    else
         ret |= EMC_StaMemConfigEW(pConfig->CSn,EMC_CFG_EW_DISABLED);

    // Timing
     ret |= EMC_SetStaMemoryParameter(pConfig->CSn,EMC_STA_MEM_WAITWEN, pConfig->WaitWEn);
     ret |= EMC_SetStaMemoryParameter(pConfig->CSn,EMC_STA_MEM_WAITOEN, pConfig->WaitOEn);
     ret |= EMC_SetStaMemoryParameter(pConfig->CSn,EMC_STA_MEM_WAITRD, pConfig->WaitRd);
     ret |= EMC_SetStaMemoryParameter(pConfig->CSn,EMC_STA_MEM_WAITPAGE, pConfig->WaitPage);
     ret |= EMC_SetStaMemoryParameter(pConfig->CSn,EMC_STA_MEM_WAITWR, pConfig->WaitWr);
     ret |= EMC_SetStaMemoryParameter(pConfig->CSn,EMC_STA_MEM_WAITTURN, pConfig->WaitTurn);


    return ret;
}

/*********************************************************************//**
 * @brief         EMC initialize (power on block, config EMC pins).
 * @param[in]    None
 * @return         None
 **********************************************************************/
EMC_FUNC_CODE EMC_Init(void)
{
    uint8_t i;
    // If CPU clock is > 80 MHz, then divide it by two to create the EMC clock
    if(CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU) > 80000000) {
        CLKPWR_SetCLKDiv(CLKPWR_CLKTYPE_EMC, 1); // CPU clock / 2
    } else {
        CLKPWR_SetCLKDiv(CLKPWR_CLKTYPE_EMC, 0); // Same clock as CPU
    }

    LPC_SC->PCONP       |= 0x00000800;
    LPC_SC->EMCDLYCTL   = 0x00001010;
    LPC_EMC->Control     = 0x00000001;
    LPC_EMC->Config      = 0x00000000;

    /* Pin configuration:
    * P2.14 - /EMC_CS2
    * P2.15 - /EMC_CS3
    *
    * P2.16 - /EMC_CAS
    * P2.17 - /EMC_RAS
    * P2.18 - EMC_CLK[0]
    * P2.19 - EMC_CLK[1]
    *
    * P2.20 - EMC_DYCS0
    * P2.21 - EMC_DYCS1
    * P2.22 - EMC_DYCS2
    * P2.23 - EMC_DYCS3
    *
    * P2.24 - EMC_CKE0
    * P2.25 - EMC_CKE1
    * P2.26 - EMC_CKE2
    * P2.27 - EMC_CKE3
    *
    * P2.28 - EMC_DQM0
    * P2.29 - EMC_DQM1
    * P2.30 - EMC_DQM2
    * P2.31 - EMC_DQM3
    *
    * P3.0-P3.31 - EMC_D[0-31]
    * P4.0-P4.23 - EMC_A[0-23]
     * P5.0-P5.1  - EMC_A[24-25]
    *
    * P4.24 - /EMC_OE
    * P4.25 - /EMC_WE
    *
    * P4.30 - /EMC_CS0
    * P4.31 - /EMC_CS1
    */
    PINSEL_ConfigPin(2,14,1);
    PINSEL_ConfigPin(2,15,1);
    PINSEL_ConfigPin(2,16,1);
    PINSEL_ConfigPin(2,17,1);
    PINSEL_ConfigPin(2,18,1);
    PINSEL_ConfigPin(2,19,1);
    PINSEL_ConfigPin(2,20,1);
    PINSEL_ConfigPin(2,21,1);
    PINSEL_ConfigPin(2,22,1);
    PINSEL_ConfigPin(2,23,1);
    PINSEL_ConfigPin(2,24,1);
    PINSEL_ConfigPin(2,25,1);
    PINSEL_ConfigPin(2,26,1);
    PINSEL_ConfigPin(2,27,1);
    PINSEL_ConfigPin(2,28,1);
    PINSEL_ConfigPin(2,29,1);
    PINSEL_ConfigPin(2,30,1);
    PINSEL_ConfigPin(2,31,1);

    for(i = 0; i < 32; i++)
    {
        PINSEL_ConfigPin(3,i,1);
        PINSEL_ConfigPin(4,i,1);
    }
    PINSEL_ConfigPin(5,0,1);
    PINSEL_ConfigPin(5,1,1);

    return EMC_FUNC_OK;
}


/*********************************************************************//**
 * @brief         Configure Little Endian/Big Endian mode for EMC
 *
 * @param[in]    endia_mode    Endian mode, should be:
 *
 *                 - EMC_Config_Little_Endian_Mode:    Little-endian mode
 *
 *                 - EMC_Config_Big_Endian_Mode    :    Big-endian mode
 *
 * @return         EMC_FUNC_OK
 **********************************************************************/
EMC_FUNC_CODE  EMC_ConfigEndianMode(uint32_t endian_mode)
{
    LPC_EMC->Config &= ~(EMC_Config_Endian_Mask);
    LPC_EMC->Config |= (endian_mode&EMC_Config_Endian_Mask);
    return EMC_FUNC_OK;
}

/****************** Group of Dynamic control functions************************/

/*********************************************************************//**
 * @brief         Set the dsvalue for dynamic clock enable bit
 *
 * @param[in]    clock_enable    clock enable mode, should be:
 *
 *                - EMC_DYNAMIC_CTRL_CE_SAVEPWR: Clock enable of idle devices
 *                are deasserted to save power
 *
 *                - EMC_DYNAMIC_CTRL_CE_ALLCLK_HI: All clock enables are driven
 *                HIGH continuously
 *
 * @return         EMC_FUNC_CODE
 **********************************************************************/
EMC_FUNC_CODE EMC_DynCtrlClockEnable(uint32_t clock_enable)
{
    LPC_EMC->DynamicControl &= ~(EMC_DYNAMIC_CTRL_MEMCLK_EN_BMASK);
    LPC_EMC->DynamicControl |= clock_enable & EMC_DYNAMIC_CTRL_MEMCLK_EN_BMASK;
    return EMC_FUNC_OK;
}


/*********************************************************************//**
 * @brief         Set the value for dynamic memory clock control: stops or
 *                runs continuously
 *
 * @param[in]    clock_control    clock control mode, should be:
 *
 *                - EMC_DYNAMIC_CTRL_CS_CLKOUT_STOP: CLKOUT stops when all
 *                SDRAMs are idle and during self-refresh mode
 *
 *                - EMC_DYNAMIC_CTRL_CS_CLKOUT_CONT: CLKOUT runs continuously
 *
 * @return         EMC_FUNC_OK
 **********************************************************************/
EMC_FUNC_CODE EMC_DynCtrlClockControl(int32_t clock_control)
{
    LPC_EMC->DynamicControl  &= ~EMC_DYNAMIC_CTRL_CLKCTRL_BMASK;
    LPC_EMC->DynamicControl |= clock_control & EMC_DYNAMIC_CTRL_CLKCTRL_BMASK;
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Switch the Self-refresh mode between normal and self-refresh mode
 *
 * @param[in]    self_refresh_mode    self refresh mode, should be:
 *
 *                - EMC_DYNAMIC_CTRL_SR_NORMALMODE: Normal mode
 *
 *                - EMC_DYNAMIC_CTRL_SR_SELFREFRESH: Enter self-refresh mode
 *
 * @return         EMC_FUNC_OK
 **********************************************************************/
EMC_FUNC_CODE EMC_DynCtrlSelfRefresh(uint32_t self_refresh_mode)
{
    LPC_EMC->DynamicControl &= ~EMC_DYNAMIC_CTRL_SELFREFRESH_REQ_BMASK;
    LPC_EMC->DynamicControl =self_refresh_mode & EMC_DYNAMIC_CTRL_SELFREFRESH_REQ_BMASK;
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Enable/disable CLKOUT
 *
 * @param[in]    MMC_val    Memory clock control mode, should be:
 *
 *                     - EMC_DYNAMIC_CTRL_MMC_CLKOUT_ENABLED: CLKOUT enabled
 *
 *                     - EMC_DYNAMIC_CTRL_MMC_CLKOUT_DISABLED: CLKOUT disabled
 *
 * @return         EMC_FUNC_OK
 **********************************************************************/
EMC_FUNC_CODE EMC_DynCtrlMMC(uint32_t MMC_val)
{
    LPC_EMC->DynamicControl &= ~EMC_DYNAMIC_CTRL_MMC_CLKOUTCTRL_BMASK;
    LPC_EMC->DynamicControl |=MMC_val & EMC_DYNAMIC_CTRL_MMC_CLKOUTCTRL_BMASK;
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Issue SDRAM command
 *
 * @param[in]    SDRAM_command    Command mode, should be:
 *
 *                - EMC_DYNAMIC_CTRL_SDRAM_NORMAL: Issue SDRAM NORMAL operation command
 *
 *                - EMC_DYNAMIC_CTRL_SDRAM_MODE: Issue SDRAM MODE command
 *
 *                - EMC_DYNAMIC_CTRL_SDRAM_PALL: Issue SDRAM PALL (precharge all) command
 *
 *                - EMC_DYNAMIC_CTRL_SDRAM_NOP: Issue SRAM NOP (no operation) command
 *
 * @return         EMC_FUNC_OK
 **********************************************************************/
EMC_FUNC_CODE EMC_DynCtrlSDRAMInit(uint32_t SDRAM_command)
{
    LPC_EMC->DynamicControl &= ~EMC_DYNAMIC_CTRL_SDRAM_INIT_BMASK;
    LPC_EMC->DynamicControl |= SDRAM_command & EMC_DYNAMIC_CTRL_SDRAM_INIT_BMASK;
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Switch between Normal operation and deep sleep power mode
 *
 * @param[in]    Power_command    Low-power SDRAM deep-sleep mode, should be:
 *
 *                - EMC_DYNAMIC_CTRL_DP_NORMAL: Normal operation
 *
 *                - EMC_DYNAMIC_CTRL_DP_DEEPSLEEP: Enter deep-sleep mode
 *
 * @return         EMC_FUNC_OK
 **********************************************************************/
EMC_FUNC_CODE EMC_DynCtrlPowerDownMode(uint32_t Power_command)
{
    LPC_EMC->DynamicControl &= ~EMC_DYNAMIC_CTRL_SDRAM_PWRMODE_BMASK;
    LPC_EMC->DynamicControl |= Power_command & EMC_DYNAMIC_CTRL_SDRAM_PWRMODE_BMASK;
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Set the value of EMC dynamic memory registers
 *
 * @param[in]    par    EMC register that will set value, should be:
 *                    - EMC_DYN_MEM_REFRESH_TIMER: Dynamic Refresh register
 *                    - EMC_DYN_MEM_READ_CONFIG: Dynamic Read Config register
 *                    - EMC_DYN_MEM_TRP: Dynamic RP register
 *                    - EMC_DYN_MEM_TRAS: Dynamic RAS register
 *                    - EMC_DYN_MEM_TSREX: Dynamic SREX register
 *                    - EMC_DYN_MEM_TAPR: Dynamic APR register
 *                    - EMC_DYN_MEM_TDAL: Dynamic DAL register
 *                    - EMC_DYN_MEM_TWR: Dynamic WR register
 *                    - EMC_DYN_MEM_TRC: Dynamic RC register
 *                    - EMC_DYN_MEM_TRFC: Dynamic RFC register
 *                    - EMC_DYN_MEM_TXSR: Dynamic XSR register
 *                    - EMC_DYN_MEM_TRRD: Dynamic RRD register
 *                    - EMC_DYN_MEM_TMRD: Dynamic MRD register
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_SetDynMemoryParameter(EMC_DYN_MEM_PAR par, uint32_t val)
{
    switch ( par)
    {
        case EMC_DYN_MEM_REFRESH_TIMER:
            LPC_EMC->DynamicRefresh = EMC_DynamicRefresh_REFRESH(val);
            break;
        
        case EMC_DYN_MEM_READ_CONFIG:
            LPC_EMC->DynamicReadConfig = EMC_DynamicReadConfig_RD(val);
            break;
        
        case EMC_DYN_MEM_TRP:
            LPC_EMC->DynamicRP = EMC_DynamictRP_tRP(val);
            break;
        
        case EMC_DYN_MEM_TRAS:
            LPC_EMC->DynamicRAS = EMC_DynamictRP_tRAS(val);
            break;
        
        case EMC_DYN_MEM_TSREX:
            LPC_EMC->DynamicSREX = EMC_DynamictRP_tSREX(val);
            break;
        
        case EMC_DYN_MEM_TAPR:
            LPC_EMC->DynamicAPR = EMC_DynamictAPR_tAPR(val);
            break;
        
        case EMC_DYN_MEM_TDAL:
            LPC_EMC->DynamicDAL =EMC_DynamictDAL_tDAL(val);
            break;
        
        case EMC_DYN_MEM_TWR:
            LPC_EMC->DynamicWR = EMC_DynamictWR_tWR(val);
            break;
        
        case EMC_DYN_MEM_TRC:
            LPC_EMC->DynamicRC = EMC_DynamictRC_tRC(val);
            break;
        
        case EMC_DYN_MEM_TRFC:
            LPC_EMC->DynamicRFC = EMC_DynamictRFC_tRFC(val);
            break;
        
        case EMC_DYN_MEM_TXSR:
            LPC_EMC->DynamicXSR = EMC_DynamictXSR_tXSR(val);
            break;
        
        case EMC_DYN_MEM_TRRD:
            LPC_EMC->DynamicRRD = EMC_DynamictRRD_tRRD(val);
            break;
        
        case EMC_DYN_MEM_TMRD:
            LPC_EMC->DynamicMRD = EMC_DynamictMRD_tMRD(val);
            break;
        default:
            return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Configure the memory device
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]    mem_dev Memory device, should be:
 *
 *                    - EMC_DYNAMIC_CFG_MEMDEV_SDRAM: SDRAM
 *
 *                    - EMC_DYNAMIC_CFG_MEMDEV_LOWPWR_SDRAM: Low-power SDRAM
 *
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_DynMemConfigMD(uint32_t index , uint32_t mem_dev)
{
    switch (index)
    {
        case 0:
            LPC_EMC->DynamicConfig0  &= ~EMC_DYNAMIC_CFG_MEMDEV_BMASK;
            LPC_EMC->DynamicConfig0 |=  mem_dev & EMC_DYNAMIC_CFG_MEMDEV_BMASK;
            break;
        
        case 1:
            LPC_EMC->DynamicConfig1  &= ~EMC_DYNAMIC_CFG_MEMDEV_BMASK;
            LPC_EMC->DynamicConfig1 |= mem_dev & EMC_DYNAMIC_CFG_MEMDEV_BMASK;
            break;
        
        case 2:
            LPC_EMC->DynamicConfig2  &= ~EMC_DYNAMIC_CFG_MEMDEV_BMASK;
            LPC_EMC->DynamicConfig2 |= mem_dev & EMC_DYNAMIC_CFG_MEMDEV_BMASK;
            break;
        
        case 3:
            LPC_EMC->DynamicConfig3  &= ~EMC_DYNAMIC_CFG_MEMDEV_BMASK;
            LPC_EMC->DynamicConfig3 |=  mem_dev & EMC_DYNAMIC_CFG_MEMDEV_BMASK;
            break;
        default:
            return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Map the address for the memory device
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     add_mapped address where the memory will be mapped
 *
 * @return         EMC_FUNC_OK
 **********************************************************************/
EMC_FUNC_CODE EMC_DynMemConfigAM(uint32_t index , 
                                                                       uint8_t addr_bus_width, uint8_t addr_map,
                                                                       uint8_t data_bus_width,
                                                                       uint16_t chip_size)
{
    const     int  chip_max_size   =  512;  // 512Mb
    uint8_t     data_bus_max_size = 0;
    uint32_t  add_mapped_p1 = 0x00, add_mapped_p2 = 0x00, add_mapped_p3 = 0x00;
    uint32_t tmp = 16, i = 0, j = 0;

     /* Get part 3 of address map */
    switch(addr_bus_width)
    {
       case 16:
          add_mapped_p3 = 0;
          data_bus_max_size = 16;
          break;
       case 32:
           add_mapped_p3 = 1;
          data_bus_max_size = 32;
          break;
       default:
            return EMC_FUNC_INVALID_PARAM;
     }

      /* Get part 2 of address map */
     add_mapped_p2 = EMC_DYNAMIC_CFG_ADD_MAP_P2(addr_map);


     /* Get part 1 of address map */
     if(chip_size == 16)
     {
          if(data_bus_width == 8)
               add_mapped_p1 = 0;
          else  if(data_bus_width == 16)
               add_mapped_p1 = 1;
          else
         return EMC_FUNC_INVALID_PARAM;     
     }
     else
     {
           while(1)
           {
                i++;
                tmp = 16*(0x01 << (i+1));
                if(tmp == chip_size)
                {
                    for(j = 0; (8<<j)<=data_bus_max_size;j++)
                    {
                         if((8<<j) == data_bus_width)
                             break;
                    }
                    if( (8<<j) > data_bus_max_size)
                         return EMC_FUNC_INVALID_PARAM;
            
                    add_mapped_p1 = (i<<2) + j;
                    break;
                }
                if(tmp >= chip_max_size)
                {
                    return EMC_FUNC_INVALID_PARAM;
                }
           }
       }
      
    switch ( index)
    {
        case 0:
            LPC_EMC->DynamicConfig0 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P1_MASK;
            LPC_EMC->DynamicConfig0 |=  EMC_DYNAMIC_CFG_ADD_MAP_P1(add_mapped_p1);
            LPC_EMC->DynamicConfig0 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P2_MASK;
            LPC_EMC->DynamicConfig0 |=  EMC_DYNAMIC_CFG_ADD_MAP_P2(add_mapped_p2);
            LPC_EMC->DynamicConfig0 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P3_MASK;
            LPC_EMC->DynamicConfig0 |=  EMC_DYNAMIC_CFG_ADD_MAP_P3(add_mapped_p3);
            break;
        
        case 1:
            LPC_EMC->DynamicConfig1 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P1_MASK;
            LPC_EMC->DynamicConfig1 |=  EMC_DYNAMIC_CFG_ADD_MAP_P1(add_mapped_p1);
            LPC_EMC->DynamicConfig1 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P2_MASK;
            LPC_EMC->DynamicConfig1 |=  EMC_DYNAMIC_CFG_ADD_MAP_P2(add_mapped_p2);
            LPC_EMC->DynamicConfig1 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P3_MASK;
            LPC_EMC->DynamicConfig1 |=  EMC_DYNAMIC_CFG_ADD_MAP_P3(add_mapped_p3);

            break;
        
        case 2:
            LPC_EMC->DynamicConfig2 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P1_MASK;
            LPC_EMC->DynamicConfig2 |=  EMC_DYNAMIC_CFG_ADD_MAP_P1(add_mapped_p1);
            LPC_EMC->DynamicConfig2 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P2_MASK;
            LPC_EMC->DynamicConfig2 |= EMC_DYNAMIC_CFG_ADD_MAP_P2( add_mapped_p2);
            LPC_EMC->DynamicConfig2 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P3_MASK;
            LPC_EMC->DynamicConfig2 |=  EMC_DYNAMIC_CFG_ADD_MAP_P3(add_mapped_p3);

            break;
        
        case 3:
            LPC_EMC->DynamicConfig3 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P1_MASK;
            LPC_EMC->DynamicConfig3 |=  EMC_DYNAMIC_CFG_ADD_MAP_P1(add_mapped_p1);
            LPC_EMC->DynamicConfig3 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P2_MASK;
            LPC_EMC->DynamicConfig3 |=  EMC_DYNAMIC_CFG_ADD_MAP_P2(add_mapped_p2);
            LPC_EMC->DynamicConfig3 &= ~EMC_DYNAMIC_CFG_ADD_MAP_P3_MASK;
            LPC_EMC->DynamicConfig3 |=  EMC_DYNAMIC_CFG_ADD_MAP_P3(add_mapped_p3);

            break;
        default:
            return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Enable/disable the buffer
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     buff_control buffer control mode, should be:
 *
 *                - EMC_DYNAMIC_CFG_BUFF_DISABLED: buffer is disabled
 *
 *                - EMC_DYNAMIC_CFG_BUFF_ENABLED: buffer is enable
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_DynMemConfigB(uint32_t index , uint32_t buff_control)
{
    switch ( index)
    {
        case 0:
            LPC_EMC->DynamicConfig0 &= ~EMC_DYNAMIC_CFG_BUFFENABLE_BMASK;
            LPC_EMC->DynamicConfig0 |=  buff_control & EMC_DYNAMIC_CFG_BUFFENABLE_BMASK;
            break;
        
        case 1:
            LPC_EMC->DynamicConfig1 &= ~EMC_DYNAMIC_CFG_BUFFENABLE_BMASK;
            LPC_EMC->DynamicConfig1 |= buff_control& EMC_DYNAMIC_CFG_BUFFENABLE_BMASK;
            break;

        case 2:
            LPC_EMC->DynamicConfig2 &= ~EMC_DYNAMIC_CFG_BUFFENABLE_BMASK;
            LPC_EMC->DynamicConfig2 |= buff_control& EMC_DYNAMIC_CFG_BUFFENABLE_BMASK;
            break;

        case 3:
            LPC_EMC->DynamicConfig3 &= ~EMC_DYNAMIC_CFG_BUFFENABLE_BMASK;
            LPC_EMC->DynamicConfig3|= buff_control& EMC_DYNAMIC_CFG_BUFFENABLE_BMASK;
            break;
    default:
       return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}


/*********************************************************************//**
 * @brief         Configure write permission: protect or not
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     permission  permission mode, should be:
 *
 *                - EMC_DYNAMIC_CFG_WR_UNPROTECTED: will not protect
 *
 *                - EMC_DYNAMIC_CFG_WR_PROTECTED: will protect
 *
 * @return         EMC_FUNC_OK
 **********************************************************************/
EMC_FUNC_CODE EMC_DynMemConfigP(uint32_t index , uint32_t permission)
{

    switch ( index)
    {
        case 0:
            LPC_EMC->DynamicConfig0 &= ~ EMC_DYNAMIC_CFG_WRPROTECT_BMASK;
            LPC_EMC->DynamicConfig0 |= permission&EMC_DYNAMIC_CFG_WRPROTECT_BMASK;
            break;
        
        case 1:
            LPC_EMC->DynamicConfig1 &= ~ EMC_DYNAMIC_CFG_WRPROTECT_BMASK;
            LPC_EMC->DynamicConfig1 |= permission&EMC_DYNAMIC_CFG_WRPROTECT_BMASK;
            break;
        
        case 2:
            LPC_EMC->DynamicConfig2 &= ~ EMC_DYNAMIC_CFG_WRPROTECT_BMASK;
            LPC_EMC->DynamicConfig2 |= permission&EMC_DYNAMIC_CFG_WRPROTECT_BMASK;
            break;
        
        case 3:
            LPC_EMC->DynamicConfig3 &= ~ EMC_DYNAMIC_CFG_WRPROTECT_BMASK;
            LPC_EMC->DynamicConfig3 |= permission&EMC_DYNAMIC_CFG_WRPROTECT_BMASK;
            break;
    default:
       return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Set value for RAS latency
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     ras_val  RAS value should be in range: 0..3
 *
 * @return         EMC_FUNC_OK
 **********************************************************************/
EMC_FUNC_CODE EMC_DynMemRAS(uint32_t index , uint32_t ras_val)
{
    switch ( index)
    {
        case 0:
            LPC_EMC->DynamicRasCas0 &= ~EMC_DYNAMIC_RASCAS_RASCFG_BMASK;
            LPC_EMC->DynamicRasCas0 |=( ras_val << EMC_DYNAMIC_RASCAS_RASCFG_POS)
                                                &EMC_DYNAMIC_RASCAS_RASCFG_BMASK;
            break;
        
        case 1:
            LPC_EMC->DynamicRasCas1 &= ~EMC_DYNAMIC_RASCAS_RASCFG_BMASK;
            LPC_EMC->DynamicRasCas1 |= ( ras_val << EMC_DYNAMIC_RASCAS_RASCFG_POS)
                                            &EMC_DYNAMIC_RASCAS_RASCFG_BMASK;
            break;
        
        case 2:
            LPC_EMC->DynamicRasCas2 &= ~EMC_DYNAMIC_RASCAS_RASCFG_BMASK;
            LPC_EMC->DynamicRasCas2 |= ( ras_val << EMC_DYNAMIC_RASCAS_RASCFG_POS)
                                            &EMC_DYNAMIC_RASCAS_RASCFG_BMASK;
            break;
        
        case 3:
            LPC_EMC->DynamicRasCas3 &= ~EMC_DYNAMIC_RASCAS_RASCFG_BMASK;
            LPC_EMC->DynamicRasCas3 |= ( ras_val << EMC_DYNAMIC_RASCAS_RASCFG_POS)
                                            &EMC_DYNAMIC_RASCAS_RASCFG_BMASK;
            break;
    default:
       return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}


/*********************************************************************//**
 * @brief         Set value for CAS latency
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     ras_val  CAS value should be in range: 0..3
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_DynMemCAS(uint32_t index , uint32_t cas_val)
{    
    switch ( index)
    {
        case 0:
            LPC_EMC->DynamicRasCas0 &= ~EMC_DYNAMIC_RASCAS_CASCFG_BMASK;
            LPC_EMC->DynamicRasCas0 |= (cas_val<<EMC_DYNAMIC_RASCAS_CASCFG_POS)
                                            &EMC_DYNAMIC_RASCAS_CASCFG_BMASK;
            break;
        
        case 1:
            LPC_EMC->DynamicRasCas1 &= ~EMC_DYNAMIC_RASCAS_CASCFG_BMASK;
            LPC_EMC->DynamicRasCas1 |= (cas_val<<EMC_DYNAMIC_RASCAS_CASCFG_POS)
                                            &EMC_DYNAMIC_RASCAS_CASCFG_BMASK;
            break;
        
        case 2:
            LPC_EMC->DynamicRasCas2 &= ~EMC_DYNAMIC_RASCAS_CASCFG_BMASK;
            LPC_EMC->DynamicRasCas2 |= (cas_val<<EMC_DYNAMIC_RASCAS_CASCFG_POS)
                                            &EMC_DYNAMIC_RASCAS_CASCFG_BMASK;
            break;
        
        case 3:
            LPC_EMC->DynamicRasCas3 &= ~EMC_DYNAMIC_RASCAS_CASCFG_BMASK;
            LPC_EMC->DynamicRasCas3 |= (cas_val<<EMC_DYNAMIC_RASCAS_CASCFG_POS)
                                            &EMC_DYNAMIC_RASCAS_CASCFG_BMASK;
            break;
    default:
       return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Set extended wait time out for accessing static memory
 *
 * @param[in]    Extended_wait_time_out timeout value that will be set
 *
 * @return         EMC_FUNC_OK
 **********************************************************************/
EMC_FUNC_CODE EMC_StaticExtendedWait(uint32_t Extended_wait_time_out)
{
    LPC_EMC->StaticExtendedWait = EMC_StaticExtendedWait_EXTENDEDWAIT(Extended_wait_time_out);
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Configure the memory width
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     mem_width  memory width, should be:
 *
 *                - EMC_STATIC_CFG_MW_8BITS: 8-bits
 *
 *                - EMC_STATIC_CFG_MW_16BITS: 16-bits
 *
 *                - EMC_STATIC_CFG_MW_32BITS02: 32-bits
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_StaMemConfigMW(uint32_t index , uint32_t mem_width)
{
    uint32_t mem_width_flg = 0;
    switch(mem_width)
    {
        case 8:
            mem_width_flg = EMC_STATIC_CFG_MW_8BITS;
            break;
        case 16:
            mem_width_flg = EMC_STATIC_CFG_MW_16BITS;
            break;
        case 32:
            mem_width_flg = EMC_STATIC_CFG_MW_32BITS;
            break;
        default:
            return EMC_FUNC_INVALID_PARAM;
    }
    switch ( index)
    {
        case 0:
            LPC_EMC->StaticConfig0 &= ~ EMC_STATIC_CFG_MEMWIDTH_BMASK;
            LPC_EMC->StaticConfig0 |= mem_width_flg;
            break;
        
        case 1:
            LPC_EMC->StaticConfig1 &= ~ EMC_STATIC_CFG_MEMWIDTH_BMASK;
            LPC_EMC->StaticConfig1 |= mem_width_flg;
            break;
        
        case 2:
            LPC_EMC->StaticConfig2 &= ~ EMC_STATIC_CFG_MEMWIDTH_BMASK;
            LPC_EMC->StaticConfig2 |= mem_width_flg;
            break;
        
        case 3:
            LPC_EMC->StaticConfig3 &= ~ EMC_STATIC_CFG_MEMWIDTH_BMASK;
            LPC_EMC->StaticConfig3 |= mem_width_flg;
            break;
    default:
            return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}
/*********************************************************************//**
 * @brief         Configure the page mode
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     page_mode  page mode, should be:
 *
 *                - EMC_CFG_PM_DISABLE: disable
 *
 *                 - EMC_CFG_PM_ASYNC_ENABLE: asynchronous page mode enable
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_StaMemConfigPM(uint32_t index , uint32_t page_mode)
{
    switch ( index)
    {
        case 0:
            LPC_EMC->StaticConfig0  &= ~EMC_STATIC_CFG_PAGEMODE_MASK;
            LPC_EMC->StaticConfig0 |= page_mode&EMC_STATIC_CFG_PAGEMODE_MASK;
            break;
        
        case 1:
            LPC_EMC->StaticConfig1  &= ~EMC_STATIC_CFG_PAGEMODE_MASK;
            LPC_EMC->StaticConfig1  |= page_mode&EMC_STATIC_CFG_PAGEMODE_MASK;
            break;
        
        case 2:
            LPC_EMC->StaticConfig2  &= ~EMC_STATIC_CFG_PAGEMODE_MASK;
            LPC_EMC->StaticConfig2  |= page_mode&EMC_STATIC_CFG_PAGEMODE_MASK;
            break;
        
        case 3:
            LPC_EMC->StaticConfig3  &= ~EMC_STATIC_CFG_PAGEMODE_MASK;
            LPC_EMC->StaticConfig3  |= page_mode&EMC_STATIC_CFG_PAGEMODE_MASK;
            break;
    default:
            return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}


/*********************************************************************//**
 * @brief         Configure the chip select polarity
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     pagepol_val_mode  page mode, should be:
 *
 *                 - EMC_CFG_BYTELAND_PC_ACTIVE_LO: Active LOW ship select
 *
 *                 - EMC_CFG_BYTELAND_PC_ACTIVE_HI: Active HIGH chip select
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_StaMemConfigPC(uint32_t index , uint32_t pol_val)
{
    switch ( index)
    {
        case 0:
            LPC_EMC->StaticConfig0 &= ~EMC_STATIC_CFG_CHIPPOLARITY_MASK;
            LPC_EMC->StaticConfig0  |=  pol_val&EMC_STATIC_CFG_CHIPPOLARITY_MASK;
            break;
            
        case 1:
            LPC_EMC->StaticConfig1 &= ~EMC_STATIC_CFG_CHIPPOLARITY_MASK;
            LPC_EMC->StaticConfig1  |=  pol_val&EMC_STATIC_CFG_CHIPPOLARITY_MASK;
            break;
            
        case 2:
            LPC_EMC->StaticConfig2 &= ~EMC_STATIC_CFG_CHIPPOLARITY_MASK;
            LPC_EMC->StaticConfig2 |=  pol_val&EMC_STATIC_CFG_CHIPPOLARITY_MASK;
            break;
            
        case 3:
            LPC_EMC->StaticConfig3 &= ~EMC_STATIC_CFG_CHIPPOLARITY_MASK;
            LPC_EMC->StaticConfig3  |=  pol_val&EMC_STATIC_CFG_CHIPPOLARITY_MASK;
            break;
    default:
            return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}


/*********************************************************************//**
 * @brief         Configure the byte lane state
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     pb_val  Byte lane state, should be:
 *
 *                 - EMC_CFG_BYTELAND_READ_BITSHIGH: For reads all bits 
 *                in BLSn[3:0] are HIGH.
 *
 *                 - EMC_CFG_BYTELAND_READ_BITSLOW: For reads all bits 
 *                in BLSn[3:0] are LOW.
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_StaMemConfigPB(uint32_t index , uint32_t pb_val)
{
    switch ( index)
    {
        case 0:
            LPC_EMC->StaticConfig0 &= ~EMC_STATIC_CFG_BYTELAND_MASK;
            LPC_EMC->StaticConfig0 |= pb_val&EMC_STATIC_CFG_BYTELAND_MASK;
            break;

        case 1:
            LPC_EMC->StaticConfig1 &= ~EMC_STATIC_CFG_BYTELAND_MASK;
            LPC_EMC->StaticConfig1 |= pb_val&EMC_STATIC_CFG_BYTELAND_MASK;
            break;

        case 2:
            LPC_EMC->StaticConfig2 &= ~EMC_STATIC_CFG_BYTELAND_MASK;
            LPC_EMC->StaticConfig2 |= pb_val&EMC_STATIC_CFG_BYTELAND_MASK;
            break;

        case 3:
            LPC_EMC->StaticConfig3 &= ~EMC_STATIC_CFG_BYTELAND_MASK;
            LPC_EMC->StaticConfig3 |= pb_val&EMC_STATIC_CFG_BYTELAND_MASK;
            break;
    default:
            return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Configure the extended wait value
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     ex_wait  Extended wait mode, should be:
 *
 *                - EMC_CFG_EW_DISABLED: Extended wait disabled.
 *
 *                - EMC_CFG_EW_ENABLED: Extended wait enabled.
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_StaMemConfigEW(uint32_t index , uint32_t ex_wait)
{
    switch ( index)
    {
        case 0:
            LPC_EMC->StaticConfig0 &= ~EMC_STATIC_CFG_EXTWAIT_MASK;
            LPC_EMC->StaticConfig0 |=  ex_wait&EMC_STATIC_CFG_EXTWAIT_MASK;
            break;
        
        case 1:
            LPC_EMC->StaticConfig1 &= ~EMC_STATIC_CFG_EXTWAIT_MASK;
            LPC_EMC->StaticConfig1 |=  ex_wait&EMC_STATIC_CFG_EXTWAIT_MASK;
            break;
        
        case 2:
            LPC_EMC->StaticConfig2 &= ~EMC_STATIC_CFG_EXTWAIT_MASK;
            LPC_EMC->StaticConfig2  |=  ex_wait&EMC_STATIC_CFG_EXTWAIT_MASK;
            break;
        
        case 3:
            LPC_EMC->StaticConfig3 &= ~EMC_STATIC_CFG_EXTWAIT_MASK;
            LPC_EMC->StaticConfig3  |=  ex_wait&EMC_STATIC_CFG_EXTWAIT_MASK;
            break;
    default:
            return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Configure the buffer enable value
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     buf_val  Buffer mode, should be:
 *
 *                - EMC_CFG_BUF_DISABLED: Buffer disabled.
 *
 *                - EMC_CFG_BUF_ENABLED: Buffer enabled.
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_StaMemConfigB(uint32_t index , uint32_t buf_val)
{    
    switch ( index)
    {
        case 0:
            LPC_EMC->StaticConfig0 &= ~EMC_STATIC_CFG_BUFENABLE_MASK;
            LPC_EMC->StaticConfig0 |=  buf_val&EMC_STATIC_CFG_BUFENABLE_MASK;
            break;
        
        case 1:
            LPC_EMC->StaticConfig1 &= ~EMC_STATIC_CFG_BUFENABLE_MASK;
            LPC_EMC->StaticConfig1  |=  buf_val&EMC_STATIC_CFG_BUFENABLE_MASK;
            break;
        
        case 2:
            LPC_EMC->StaticConfig2 &= ~EMC_STATIC_CFG_BUFENABLE_MASK;
            LPC_EMC->StaticConfig2  |=  buf_val&EMC_STATIC_CFG_BUFENABLE_MASK;
            break;
        
        case 3:
            LPC_EMC->StaticConfig3 &= ~EMC_STATIC_CFG_BUFENABLE_MASK;
            LPC_EMC->StaticConfig3  |=  buf_val&EMC_STATIC_CFG_BUFENABLE_MASK;
            break;
    default:
            return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Configure the write permission
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     per_val  Permission mode, should be:
 *
 *                - EMC_CFG_WRITEPROTECT_DISABLED: Write not protected.
 *
 *                - EMC_CFG_WRITEPROTECT_ENABLED: Write protected.
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_StaMemConfigpP(uint32_t index , uint32_t per_val)
{
    switch ( index)
    {
        case 0:
            LPC_EMC->StaticConfig0 &= ~EMC_STATIC_CFG_WRIEPROTECT_MASK;
            LPC_EMC->StaticConfig0  |=  per_val&EMC_STATIC_CFG_WRIEPROTECT_MASK;
            break;
        
        case 1:
            LPC_EMC->StaticConfig1 &= ~EMC_STATIC_CFG_WRIEPROTECT_MASK;
            LPC_EMC->StaticConfig1  |=  per_val&EMC_STATIC_CFG_WRIEPROTECT_MASK;
            break;
        
        case 2:
            LPC_EMC->StaticConfig2 &= ~EMC_STATIC_CFG_WRIEPROTECT_MASK;
            LPC_EMC->StaticConfig2  |=  per_val&EMC_STATIC_CFG_WRIEPROTECT_MASK;
            break;
        
        case 3:
            LPC_EMC->StaticConfig3 &= ~EMC_STATIC_CFG_WRIEPROTECT_MASK;
            LPC_EMC->StaticConfig3  |=  per_val&EMC_STATIC_CFG_WRIEPROTECT_MASK;
            break;
    default:
            return EMC_FUNC_INVALID_PARAM;
    }
    return EMC_FUNC_OK;
}

/*********************************************************************//**
 * @brief         Set the value of LPC_EMC static memory registers
 *
 * @param[in]    index index number, should be from 0 to 3
 *
 * @param[in]     EMC_STA_MEM_PAR  Static register, should be:
 *
 *                - EMC_STA_MEM_WAITWEN: StaticWaitWen0 register
 *                - EMC_STA_MEM_WAITOEN: StaticWaitOen0 register
 *                - EMC_STA_MEM_WAITRD: StaticWaitRd0 register
 *                - EMC_STA_MEM_WAITPAGE: StaticWaitPage0 register
 *                - EMC_STA_MEM_WAITWR: StaticWaitWr0 register
 *                - EMC_STA_MEM_WAITTURN: StaticWaitTurn0 register
 *
 * @return         EMC_FUNC_OK/EMC_FUNC_INVALID_PARAM
 **********************************************************************/
EMC_FUNC_CODE EMC_SetStaMemoryParameter(uint32_t index ,EMC_STA_MEM_PAR par, uint32_t val)
{
    switch (index)
    {
        case 0:
            switch ( par)
            {
                case EMC_STA_MEM_WAITWEN:
                    LPC_EMC->StaticWaitWen0 = EMC_StaticWaitWen_WAITWEN(val);
                    break; 
                
                case EMC_STA_MEM_WAITOEN:
                    LPC_EMC->StaticWaitOen0 = EMC_StaticWaitOen_WAITOEN(val);
                    break;
                
                case EMC_STA_MEM_WAITRD:
                    LPC_EMC->StaticWaitRd0 = EMC_StaticWaitRd_WAITRD(val);
                    break;
                
                case EMC_STA_MEM_WAITPAGE:
                    LPC_EMC->StaticWaitPage0 = EMC_StaticwaitPage_WAITPAGE(val);
                    break;
                
                case EMC_STA_MEM_WAITWR:
                    LPC_EMC->StaticWaitWr0 = EMC_StaticWaitwr_WAITWR(val);
                    break;
                
                case EMC_STA_MEM_WAITTURN:
                    LPC_EMC->StaticWaitTurn0 =EMC_StaticWaitTurn_WAITTURN(val);
                    break;
          default:
                    return EMC_FUNC_INVALID_PARAM;
            }
            break;
            
        case 1:
            switch ( par)
            {
                case EMC_STA_MEM_WAITWEN:
                    LPC_EMC->StaticWaitWen1 = EMC_StaticWaitWen_WAITWEN(val);
                    break;
                
                case EMC_STA_MEM_WAITOEN:
                    LPC_EMC->StaticWaitOen1 = EMC_StaticWaitOen_WAITOEN(val);
                    break;
                
                case EMC_STA_MEM_WAITRD:
                    LPC_EMC->StaticWaitRd1 = EMC_StaticWaitRd_WAITRD(val);
                    break;
                
                case EMC_STA_MEM_WAITPAGE:
                    LPC_EMC->StaticWaitPage1 = EMC_StaticwaitPage_WAITPAGE(val);
                    break;
                
                case EMC_STA_MEM_WAITWR:
                    LPC_EMC->StaticWaitWr1 = EMC_StaticWaitwr_WAITWR(val);
                    break;
                
                case EMC_STA_MEM_WAITTURN:
                    LPC_EMC->StaticWaitTurn1 =EMC_StaticWaitTurn_WAITTURN(val);
                    break;
           default:
         return EMC_FUNC_INVALID_PARAM;

            }
            break;
            
        case 2:
            switch ( par)
            {
                case EMC_STA_MEM_WAITWEN:
                    LPC_EMC->StaticWaitWen2 = EMC_StaticWaitWen_WAITWEN(val);
                    break;
                
                case EMC_STA_MEM_WAITOEN:
                    LPC_EMC->StaticWaitOen2 = EMC_StaticWaitOen_WAITOEN(val);
                    break;
                
                case EMC_STA_MEM_WAITRD:
                    LPC_EMC->StaticWaitRd2 = EMC_StaticWaitRd_WAITRD(val);
                    break;
                
                case EMC_STA_MEM_WAITPAGE:
                    LPC_EMC->StaticWaitPage2 = EMC_StaticwaitPage_WAITPAGE(val);
                    break;
                
                case EMC_STA_MEM_WAITWR:
                    LPC_EMC->StaticWaitWr2 = EMC_StaticWaitwr_WAITWR(val);
                    break;
                
                case EMC_STA_MEM_WAITTURN:
                    LPC_EMC->StaticWaitTurn2 =EMC_StaticWaitTurn_WAITTURN(val);
                    break;
           default:
         return EMC_FUNC_INVALID_PARAM;

            }
            break;
        
        case 3:
            switch ( par)
            {
                case EMC_STA_MEM_WAITWEN:
                    LPC_EMC->StaticWaitWen3 = EMC_StaticWaitWen_WAITWEN(val);
                    break;
                
                case EMC_STA_MEM_WAITOEN:
                    LPC_EMC->StaticWaitOen3 = EMC_StaticWaitOen_WAITOEN(val);
                    break;
                
                case EMC_STA_MEM_WAITRD:
                    LPC_EMC->StaticWaitRd3 = EMC_StaticWaitRd_WAITRD(val);
                    break;
                
                case EMC_STA_MEM_WAITPAGE:
                    LPC_EMC->StaticWaitPage3 = EMC_StaticwaitPage_WAITPAGE(val);
                    break;
                
                case EMC_STA_MEM_WAITWR:
                    LPC_EMC->StaticWaitWr3 = EMC_StaticWaitwr_WAITWR(val);
                    break;
                
                case EMC_STA_MEM_WAITTURN:
                    LPC_EMC->StaticWaitTurn3 =EMC_StaticWaitTurn_WAITTURN(val);
                    break;
           default:
        return EMC_FUNC_INVALID_PARAM;
            }
            break;
    }
    return EMC_FUNC_OK;
}
/**
 * @}
 */
 
 /**
 * @}
 */
#endif /*_EMC*/






