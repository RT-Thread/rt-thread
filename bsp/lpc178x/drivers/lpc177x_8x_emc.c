/**********************************************************************
* $Id$      lpc177x_8x_emc.c            2011-06-02
*//**
* @file     lpc177x_8x_emc.c
* @brief    Contains all functions support for EMC firmware library
*           on LPC177x_8x
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
**********************************************************************/

#include "lpc177x_8x_emc.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_pinsel.h"


/*********************************************************************//**
 * @brief       EMC initialize
 * @param[in]   None
 * @return      None
 **********************************************************************/
void EMC_Init(void)
{
    uint8_t i;

    /* Enable clock for EMC */
//  CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCEMC, ENABLE);
//  LPC_EMC->Control    = 0x00000001;
//  LPC_EMC->Config     = 0x00000000;

      LPC_SC->PCONP     |= 0x00000800;
      LPC_SC->EMCDLYCTL   = 0x00001010;
      LPC_EMC->Control  = 0x00000001;
      LPC_EMC->Config   = 0x00000000;

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
   * P2.22 - EMC_DYCS1
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

    PINSEL_ConfigPin(5,0,1);
    PINSEL_ConfigPin(5,1,1);

    for(i = 0; i < 32; i++)
    {
        PINSEL_ConfigPin(3,i,1);
        PINSEL_ConfigPin(4,i,1);
    }
}
/*********************************************************************//**
 * @brief       Configure Little Endian/Big Endian mode for EMC
 * @param[in]   endia_mode  Endian mode, should be:
 *              - EMC_LITTLE_ENDIAN_MODE:   Little-endian mode
 *              - EMC_BIG_ENDIAN_MODE   :   Big-endian mode
 * @return      None
 **********************************************************************/
void EMC_ConfigEndianMode(uint32_t endian_mode)
{
   LPC_EMC->Config = ((LPC_EMC->Config & 0x01)|endian_mode) & EMC_Config_MASK;
}

/****************** Group of Dynamic control functions************************/
/*********************************************************************//**
 * @brief       Set the value for dynamic clock enable bit
 * @param[in]   clock_enable    clock enable mode, should be:
 *                  - 0: Clock enable of idle devices are deasserted to
 *                      save power
 *                  - 1: All clock enables are driven HIGH continuously
 * @return      None
 **********************************************************************/
void EMC_DynCtrlClockEnable(uint32_t clock_enable)
{
   LPC_EMC->DynamicControl = ((LPC_EMC->DynamicControl) |clock_enable);
}

/*********************************************************************//**
 * @brief       Set the value for dynamic memory clock control:
 *              stops or runs continuously
 * @param[in]   clock_control   clock control mode, should be:
 *                  - 0: CLKOUT stops when all SDRAMs are idle and
 *                      during self-refresh mode
 *                  - 1: CLKOUT runs continuously
 * @return      None
 **********************************************************************/
void EMC_DynCtrlClockControl(int32_t clock_control)
{
   uint32_t mask = ~(uint32_t)(2);
   LPC_EMC->DynamicControl = ((LPC_EMC->DynamicControl & mask) |clock_control);
}

/*********************************************************************//**
 * @brief       Switch the Self-refresh mode between normal and self-refresh mode
 * @param[in]   self_refresh_mode   self refresh mode, should be:
 *                  - 0: Normal mode
 *                  - 1: Enter self-refresh mode
 * @return      None
 **********************************************************************/
void EMC_DynCtrlSelfRefresh(uint32_t self_refresh_mode)
{
   uint32_t mask = ~(uint32_t)(4);
   LPC_EMC->DynamicControl = ((LPC_EMC->DynamicControl & mask) |self_refresh_mode);
}

/*********************************************************************//**
 * @brief       Enable/disable CLKOUT
 * @param[in]   MMC_val Memory clock control mode, should be:
 *                  - 0: CLKOUT enabled
 *                  - 1: CLKOUT disabled
 * @return      None
 **********************************************************************/
void EMC_DynCtrlMMC(uint32_t MMC_val)
{
   uint32_t mask = ~(uint32_t)(_BIT(5));
   LPC_EMC->DynamicControl = ((LPC_EMC->DynamicControl & mask) |MMC_val);
}

/*********************************************************************//**
 * @brief       Issue SDRAM command
 * @param[in]   SDRAM_command   Command mode, should be:
 *                  - 0x00: Issue SDRAM NORMAL operation command
 *                  - 0x01: Issue SDRAM MODE command
 *                  - 0x02: Issue SDRAM PALL (precharge all) command
 *                  - 0x03: Issue SRAM NOP (no operation) command
 * @return      None
 **********************************************************************/
void EMC_DynCtrlSDRAMInit(uint32_t SDRAM_command)
{
   uint32_t mask = ~(uint32_t)(_SBF(7,0x03));
   LPC_EMC->DynamicControl = ((LPC_EMC->DynamicControl & mask)|SDRAM_command);
}

/*********************************************************************//**
 * @brief       Switch between Normal operation and deep sleep power mode
 * @param[in]   Power_command   Low-power SDRAM deep-sleep mode, should be:
 *                  - 0: Normal operation
 *                  - 1: Enter deep-sleep mode
 * @return      None
 **********************************************************************/
void EMC_DynCtrlPowerDownMode(uint32_t Power_command)
{
   uint32_t mask = ~(uint32_t)(_BIT(13));
   LPC_EMC->DynamicControl = ((LPC_EMC->DynamicControl & mask)|Power_command);
}

/*********************************************************************//**
 * @brief       Set the value of EMC dynamic memory registers
 * @param[in]   par EMC register that will set value, should be:
 *                  - EMC_DYN_MEM_REFRESH_TIMER: Dynamic Refresh register
 *                  - EMC_DYN_MEM_READ_CONFIG: Dynamic Read Config register
 *                  - EMC_DYN_MEM_TRP: Dynamic RP register
 *                  - EMC_DYN_MEM_TRAS: Dynamic RAS register
 *                  - EMC_DYN_MEM_TSREX: Dynamic SREX register
 *                  - EMC_DYN_MEM_TAPR: Dynamic APR register
 *                  - EMC_DYN_MEM_TDAL: Dynamic DAL register
 *                  - EMC_DYN_MEM_TWR: Dynamic WR register
 *                  - EMC_DYN_MEM_TRC: Dynamic RC register
 *                  - EMC_DYN_MEM_TRFC: Dynamic RFC register
 *                  - EMC_DYN_MEM_TXSR: Dynamic XSR register
 *                  - EMC_DYN_MEM_TRRD: Dynamic RRD register
 *                  - EMC_DYN_MEM_TMRD: Dynamic MRD register
 * @return      None
 **********************************************************************/
void EMC_SetDynMemoryParameter(EMC_DYN_MEM_PAR par, uint32_t val)
{
   switch ( par)
   {
      case EMC_DYN_MEM_REFRESH_TIMER:
         LPC_EMC->DynamicRefresh = val;
         break;
      case EMC_DYN_MEM_READ_CONFIG:
         LPC_EMC->DynamicReadConfig = val;
         break;
      case EMC_DYN_MEM_TRP:
         LPC_EMC->DynamicRP = val;
         break;
      case EMC_DYN_MEM_TRAS:
         LPC_EMC->DynamicRAS = val;
         break;
      case EMC_DYN_MEM_TSREX:
         LPC_EMC->DynamicSREX = val;
         break;
      case EMC_DYN_MEM_TAPR:
         LPC_EMC->DynamicAPR = val;
         break;
      case EMC_DYN_MEM_TDAL:
         LPC_EMC->DynamicDAL = val;
         break;
      case EMC_DYN_MEM_TWR:
         LPC_EMC->DynamicWR = val;
         break;
      case EMC_DYN_MEM_TRC:
         LPC_EMC->DynamicRC = val;
         break;
      case EMC_DYN_MEM_TRFC:
         LPC_EMC->DynamicRFC = val;
         break;
      case EMC_DYN_MEM_TXSR:
         LPC_EMC->DynamicXSR = val;
         break;
      case EMC_DYN_MEM_TRRD:
         LPC_EMC->DynamicRRD = val;
         break;
      case EMC_DYN_MEM_TMRD:
         LPC_EMC->DynamicMRD = val;
         break;
   }
}

/*********************************************************************//**
 * @brief       Set extended wait time out for accessing static memory
 * @param[in]   Extended_wait_time_out timeout value that will be set
 * @return      None
 **********************************************************************/
void EMC_StaticExtendedWait(uint32_t Extended_wait_time_out)
{
   LPC_EMC->StaticExtendedWait = Extended_wait_time_out;
}

/*********************************************************************//**
 * @brief       Configure the memory device
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   mem_dev Memory device, should be:
 *                  - 0x00: SDRAM
 *                  - 0x01: Low-power SDRAM
 *                  - 0x02: Micron Syncflash
 * @return      None
 **********************************************************************/
void EMC_DynMemConfigMD(uint32_t index , uint32_t mem_dev)
{
   uint32_t mask = ~(uint32_t)(_SBF(3, 0x03));
   switch ( index)
   {
      case 0:
         LPC_EMC->DynamicConfig0 = (LPC_EMC->DynamicConfig0 & mask) | mem_dev;
       break;
      case 1:
         LPC_EMC->DynamicConfig1 = (LPC_EMC->DynamicConfig1 & mask) | mem_dev;
       break;
      case 2:
         LPC_EMC->DynamicConfig2 =(LPC_EMC->DynamicConfig2 & mask) | mem_dev;
       break;
      case 3:
         LPC_EMC->DynamicConfig3 = (LPC_EMC->DynamicConfig3 & mask) | mem_dev;
       break;
   }
}

/*********************************************************************//**
 * @brief       Map the address for the memory device
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   add_mapped address where the memory will be mapped
 * @return      None
 **********************************************************************/
void EMC_DynMemConfigAM(uint32_t index , uint32_t add_mapped)
{
   uint32_t mask = ~(uint32_t)(_SBF(7, 0x3f)) | ~(uint32_t)(_BIT(14))  ;

   switch ( index)
   {
      case 0:
         LPC_EMC->DynamicConfig0 = ( LPC_EMC->DynamicConfig0 & mask) | add_mapped;
       break;
      case 1:
         LPC_EMC->DynamicConfig1 = (LPC_EMC->DynamicConfig1 & mask) | add_mapped;
       break;
      case 2:
         LPC_EMC->DynamicConfig2 = (LPC_EMC->DynamicConfig2 & mask) | add_mapped;
       break;
      case 3:
         LPC_EMC->DynamicConfig3 = (LPC_EMC->DynamicConfig3 & mask) | add_mapped;
       break;
   }
}

/*********************************************************************//**
 * @brief       Enable/disable the buffer
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   buff_control buffer control mode, should be:
 *                  - ENABLE
 *                  - DISABLE
 * @return      None
 **********************************************************************/
void EMC_DynMemConfigB(uint32_t index , uint32_t buff_control)
{
   uint32_t mask =  ~(uint32_t)(_BIT(19))  ;
   switch ( index)
   {
      case 0:
         LPC_EMC->DynamicConfig0 = (LPC_EMC->DynamicConfig0 & mask) | buff_control;
       break;
      case 1:
         LPC_EMC->DynamicConfig1 = ( LPC_EMC->DynamicConfig1 & mask) | buff_control;
       break;
      case 2:
         LPC_EMC->DynamicConfig2 = (LPC_EMC->DynamicConfig2 & mask)| buff_control;
       break;
      case 3:
         LPC_EMC->DynamicConfig3 = (LPC_EMC->DynamicConfig3 & mask) | buff_control;
       break;
   }
}


/*********************************************************************//**
 * @brief       Configure write permission: protect or not
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   permission  permission mode, should be:
 *                  - ENABLE: protect
 *                  - DISABLE: not protect
 * @return      None
 **********************************************************************/
void EMC_DynMemConfigP(uint32_t index , uint32_t permission)
{
   uint32_t mask =  ~(uint32_t)(_BIT(20))  ;
   switch ( index)
   {
      case 0:
         LPC_EMC->DynamicConfig0 = (LPC_EMC->DynamicConfig0 & mask) | permission;
       break;
      case 1:
         LPC_EMC->DynamicConfig1 = (LPC_EMC->DynamicConfig1 & mask) | permission;
       break;
      case 2:
         LPC_EMC->DynamicConfig2 = ( LPC_EMC->DynamicConfig2 & mask) | permission;
       break;
      case 3:
         LPC_EMC->DynamicConfig3 = (LPC_EMC->DynamicConfig3 & mask) | permission;
       break;
   }
}

/*********************************************************************//**
 * @brief       Set value for RAS latency
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   ras_val  RAS value should be in range: 0..3
 * @return      None
 **********************************************************************/
void EMC_DynMemRAS(uint32_t index , uint32_t ras_val)
{
   uint32_t mask =  ~(uint32_t)(0x03)  ;

   switch ( index)
   {
      case 0:
         LPC_EMC->DynamicRasCas0 = (LPC_EMC->DynamicRasCas0 & mask) | ras_val;
       break;
      case 1:
         LPC_EMC->DynamicRasCas1 = (LPC_EMC->DynamicRasCas1 & mask) | ras_val;
       break;
      case 2:
         LPC_EMC->DynamicRasCas2 = (LPC_EMC->DynamicRasCas2 & mask) | ras_val;
       break;
      case 3:
         LPC_EMC->DynamicRasCas3 = (LPC_EMC->DynamicRasCas3 & mask) | ras_val;
       break;
   }
}

/*********************************************************************//**
 * @brief       Set value for CAS latency
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   ras_val  CAS value should be in range: 0..3
 * @return      None
 **********************************************************************/
void EMC_DynMemCAS(uint32_t index , uint32_t cas_val)
{
   uint32_t mask =  ~(uint32_t)(_SBF(8, 0x03))  ;
   switch ( index)
   {
      case 0:
         LPC_EMC->DynamicRasCas0 = (LPC_EMC->DynamicRasCas0 & mask) | cas_val;
       break;
      case 1:
         LPC_EMC->DynamicRasCas1 = (LPC_EMC->DynamicRasCas1 & mask) | cas_val;
       break;
      case 2:
         LPC_EMC->DynamicRasCas2 = (LPC_EMC->DynamicRasCas2 & mask )| cas_val;
       break;
      case 3:
         LPC_EMC->DynamicRasCas3 = ( LPC_EMC->DynamicRasCas3 & mask) | cas_val;
       break;
   }
}
/*********************************************************************//**
 * @brief       Configure the memory width
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   mem_width  memory width, should be:
 *                  - 0x00: 8-bits
 *                  - 0x01: 16-bits
 *                  - 0x02: 32-bits
 * @return      None
 **********************************************************************/
void EMC_StaMemConfigMW(uint32_t index , uint32_t mem_width)
{
   uint32_t mask =  ~(uint32_t)(0x03)  ;
   switch ( index)
   {
      case 0:
         LPC_EMC->StaticConfig0 = (LPC_EMC->StaticConfig0 & mask) | mem_width;
       break;
      case 1:
         LPC_EMC->StaticConfig1 = (LPC_EMC->StaticConfig1 & mask) | mem_width;
       break;
      case 2:
         LPC_EMC->StaticConfig2 = (LPC_EMC->StaticConfig2 & mask)| mem_width;
       break;
      case 3:
         LPC_EMC->StaticConfig3 = (LPC_EMC->StaticConfig3 & mask) | mem_width;
       break;
   }
}
/*********************************************************************//**
 * @brief       Configure the page mode
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   page_mode  page mode, should be:
 *                  - 0: disable
 *                  - 1: asynchronous page mode enable
 * @return      None
 **********************************************************************/
void EMC_StaMemConfigPM(uint32_t index , uint32_t page_mode)
{
   uint32_t mask =  ~(uint32_t)(_BIT(3))  ;
   switch ( index)
   {
      case 0:
         LPC_EMC->StaticConfig0 = (LPC_EMC->StaticConfig0 & mask) | page_mode;
       break;
      case 1:
         LPC_EMC->StaticConfig1 = (LPC_EMC->StaticConfig1 & mask) | page_mode;
       break;
      case 2:
         LPC_EMC->StaticConfig2 = (LPC_EMC->StaticConfig2  & mask)| page_mode;
       break;
      case 3:
         LPC_EMC->StaticConfig3 = (LPC_EMC->StaticConfig3  & mask)| page_mode;
       break;
   }
}
/*********************************************************************//**
 * @brief       Configure the chip select polarity
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   pagepol_val_mode  page mode, should be:
 *                  - 0: Active LOW ship select
 *                  - 1: Active HIGH chip select
 * @return      None
 **********************************************************************/
void EMC_StaMemConfigPC(uint32_t index , uint32_t pol_val)
{
   uint32_t mask =  ~(uint32_t)(_BIT(6))  ;
   switch ( index)
   {
      case 0:
         LPC_EMC->StaticConfig0 = (LPC_EMC->StaticConfig0 & mask) | pol_val;
       break;
      case 1:
         LPC_EMC->StaticConfig1 = (LPC_EMC->StaticConfig1  & mask)| pol_val;
       break;
      case 2:
         LPC_EMC->StaticConfig2 = (LPC_EMC->StaticConfig2 & mask) | pol_val;
       break;
      case 3:
         LPC_EMC->StaticConfig3 = (LPC_EMC->StaticConfig3 & mask) | pol_val;
       break;
   }
}

/*********************************************************************//**
 * @brief       Configure the byte lane state
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   pb_val  Byte lane state, should be:
 *                  - 0: For reads all bits in BLSn[3:0] are HIGH.
 *                  - 1: For reads all bits in BLSn[3:0] are LOW.
 * @return      None
 **********************************************************************/
void EMC_StaMemConfigPB(uint32_t index , uint32_t pb_val)
{
   uint32_t mask =  ~(uint32_t)(_BIT(7))  ;
   switch ( index)
   {
      case 0:
         LPC_EMC->StaticConfig0 = (LPC_EMC->StaticConfig0  & mask)| pb_val;
       break;
      case 1:
         LPC_EMC->StaticConfig1 = (LPC_EMC->StaticConfig1  & mask)| pb_val;
       break;
      case 2:
         LPC_EMC->StaticConfig2 =( LPC_EMC->StaticConfig2  & mask)| pb_val;
       break;
      case 3:
         LPC_EMC->StaticConfig3 = (LPC_EMC->StaticConfig3  & mask)| pb_val;
       break;
   }
}

/*********************************************************************//**
 * @brief       Configure the extended wait value
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   ex_wait  Extended wait mode, should be:
 *                  - 0: Extended wait disabled.
 *                  - 1: Extended wait enabled.
 * @return      None
 **********************************************************************/
void EMC_StaMemConfigEW(uint32_t index , uint32_t ex_wait)
{
   uint32_t mask =  ~(uint32_t)(_BIT(8))  ;
   switch ( index)
   {
      case 0:
         LPC_EMC->StaticConfig0 = (LPC_EMC->StaticConfig0 & mask) | ex_wait;
       break;
      case 1:
         LPC_EMC->StaticConfig1 = (LPC_EMC->StaticConfig1 & mask) | ex_wait;
       break;
      case 2:
         LPC_EMC->StaticConfig2 = (LPC_EMC->StaticConfig2 & mask) | ex_wait;
       break;
      case 3:
         LPC_EMC->StaticConfig3 =( LPC_EMC->StaticConfig3 & mask) | ex_wait;
       break;
   }
}

/*********************************************************************//**
 * @brief       Configure the buffer enable value
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   buf_val  Buffer mode, should be:
 *                  - 0: Buffer disabled.
 *                  - 1: Buffer enabled.
 * @return      None
 **********************************************************************/
void EMC_StaMemConfigB(uint32_t index , uint32_t buf_val)
{
   uint32_t mask =  ~(uint32_t)(_BIT(19))  ;
   switch ( index)
   {
      case 0:
         LPC_EMC->StaticConfig0 = (LPC_EMC->StaticConfig0 & mask) | buf_val;
       break;
      case 1:
         LPC_EMC->StaticConfig1 = (LPC_EMC->StaticConfig1 & mask) | buf_val;
       break;
      case 2:
         LPC_EMC->StaticConfig2 = (LPC_EMC->StaticConfig2 & mask) | buf_val;
       break;
      case 3:
         LPC_EMC->StaticConfig3 = (LPC_EMC->StaticConfig3 & mask) | buf_val;
       break;
   }
}

/*********************************************************************//**
 * @brief       Configure the write permission
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   per_val  Permission mode, should be:
 *                  - 0: Write not protected.
 *                  - 1: Write protected.
 * @return      None
 **********************************************************************/
void EMC_StaMemConfigpP(uint32_t index , uint32_t per_val)
{
   uint32_t mask =  ~(uint32_t)(_BIT(20))  ;
   switch ( index)
   {
      case 0:
         LPC_EMC->StaticConfig0 = (LPC_EMC->StaticConfig0 & mask)  | per_val;
       break;
      case 1:
         LPC_EMC->StaticConfig1 = (LPC_EMC->StaticConfig1 & mask)  | per_val;
       break;
      case 2:
         LPC_EMC->StaticConfig2 = (LPC_EMC->StaticConfig2 & mask)  | per_val;
       break;
      case 3:
         LPC_EMC->StaticConfig3 = (LPC_EMC->StaticConfig3 & mask)  | per_val;
       break;
   }
}

/*********************************************************************//**
 * @brief       Set the value of LPC_EMC static memory registers
 * @param[in]   index index number, should be from 0 to 3
 * @param[in]   EMC_STA_MEM_PAR  Static register, should be:
 *                  - EMC_STA_MEM_WAITWEN: StaticWaitWen0 register
 *                  - EMC_STA_MEM_WAITOEN: StaticWaitOen0 register
 *                  - EMC_STA_MEM_WAITRD: StaticWaitRd0 register
 *                  - EMC_STA_MEM_WAITPAGE: StaticWaitPage0 register
 *                  - EMC_STA_MEM_WAITWR: StaticWaitWr0 register
 *                  - EMC_STA_MEM_WAITTURN: StaticWaitTurn0 register
 * @return      None
 **********************************************************************/
void EMC_SetStaMemoryParameter(uint32_t index ,EMC_STA_MEM_PAR par, uint32_t val)
{
   switch (index)
   {
    case 0:
         switch ( par)
         {
            case EMC_STA_MEM_WAITWEN:
               LPC_EMC->StaticWaitWen0 = val;
               break;
            case EMC_STA_MEM_WAITOEN:
               LPC_EMC->StaticWaitOen0 = val;
               break;
            case EMC_STA_MEM_WAITRD:
               LPC_EMC->StaticWaitRd0 = val;
               break;
            case EMC_STA_MEM_WAITPAGE:
               LPC_EMC->StaticWaitPage0 = val;
               break;
            case EMC_STA_MEM_WAITWR:
               LPC_EMC->StaticWaitWr0 = val;
               break;
            case EMC_STA_MEM_WAITTURN:
               LPC_EMC->StaticWaitTurn0 = val;
               break;
         }
       break;
    case 1:
         switch ( par)
         {
            case EMC_STA_MEM_WAITWEN:
               LPC_EMC->StaticWaitWen1 = val;
               break;
            case EMC_STA_MEM_WAITOEN:
               LPC_EMC->StaticWaitOen1 = val;
               break;
            case EMC_STA_MEM_WAITRD:
               LPC_EMC->StaticWaitRd1 = val;
               break;
            case EMC_STA_MEM_WAITPAGE:
               LPC_EMC->StaticWaitPage1 = val;
               break;
            case EMC_STA_MEM_WAITWR:
               LPC_EMC->StaticWaitWr1 = val;
               break;
            case EMC_STA_MEM_WAITTURN:
               LPC_EMC->StaticWaitTurn1 = val;
               break;
         }
       break;
    case 2:
         switch ( par)
         {
            case EMC_STA_MEM_WAITWEN:
               LPC_EMC->StaticWaitWen2 = val;
               break;
            case EMC_STA_MEM_WAITOEN:
               LPC_EMC->StaticWaitOen2 = val;
               break;
            case EMC_STA_MEM_WAITRD:
               LPC_EMC->StaticWaitRd2 = val;
               break;
            case EMC_STA_MEM_WAITPAGE:
               LPC_EMC->StaticWaitPage2 = val;
               break;
            case EMC_STA_MEM_WAITWR:
               LPC_EMC->StaticWaitWr2 = val;
               break;
            case EMC_STA_MEM_WAITTURN:
               LPC_EMC->StaticWaitTurn2 = val;
               break;
         }
       break;
    case 3:
         switch ( par)
         {
            case EMC_STA_MEM_WAITWEN:
               LPC_EMC->StaticWaitWen3 = val;
               break;
            case EMC_STA_MEM_WAITOEN:
               LPC_EMC->StaticWaitOen3 = val;
               break;
            case EMC_STA_MEM_WAITRD:
               LPC_EMC->StaticWaitRd3 = val;
               break;
            case EMC_STA_MEM_WAITPAGE:
               LPC_EMC->StaticWaitPage3 = val;
               break;
            case EMC_STA_MEM_WAITWR:
               LPC_EMC->StaticWaitWr3 = val;
               break;
            case EMC_STA_MEM_WAITTURN:
               LPC_EMC->StaticWaitTurn3 = val;
               break;
         }
       break;
   }
}







