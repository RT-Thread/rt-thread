/**********************************************************************
* $Id$      lpc_emc.h           2011-06-02
*//**
* @file     lpc_emc.h
* @brief    Contains all macro definitions and function prototypes
*           support for EMC firmware library on LPC
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

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup EMC   EMC (External Memory Controller)
 * @ingroup LPC_CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC_EMC_H_
#define __LPC_EMC_H_

#include "lpc_types.h"
#include "LPC407x_8x_177x_8x.h"


/** @defgroup EMC_Private_Macros EMC Private Macros
 * @{
 */

/***********************************************************************
 * EMC Control Register (EMCControl)
 **********************************************************************/
/* Control register mask */
#define EMC_Control_MASK            ((uint32_t )0x07)
/* Control register EMC: Enable control. */
#define EMC_Control_E               ((uint32_t )(1<<0))
/* Control register EMC: Address mirror control. */
#define EMC_Control_M               ((uint32_t )(1<<1))
/* Control register EMC: Low-power mode control. */
#define EMC_Control_L               ((uint32_t )(1<<2))

/***********************************************************************
 * EMC Status Register (EMCStatus)
 **********************************************************************/
/* Status register mask */
#define EMC_Status_MASK             ((uint32_t )0x07)
/* Status register EMC: Busy. */
#define EMC_Status_B                ((uint32_t )(1<<0))
/* Status register EMC: Write buffer status. */
#define EMC_Status_S                ((uint32_t )(1<<1))
/* Status register EMC: Self-refresh acknowledge.. */
#define EMC_Status_SA               ((uint32_t )(1<<2))

/***********************************************************************
 * EMC Configuration register (EMCConfig)
 **********************************************************************/
/* EMC Configuration register : Little Endian. */
#define EMC_Config_Little_Endian_Mode       ((uint32_t )(0<<0))
/* EMC Configuration register : Big Endian. */
#define EMC_Config_Big_Endian_Mode      ((uint32_t )(1<<0))
/* EMC Configuration: Endian Mask */
#define EMC_Config_Endian_Mask           (0x01<<0)

/* EMC Configuration register: CLKOUT ratio 1:1. */
#define EMC_Config_CCLK_1_1             ((uinr32_t)(0<<8))
/* EMC Configuration register: CLKOUT ratio 1:1. */
#define EMC_Config_CCLK_1_2             ((uinr32_t)(1<<8))

/* EMC Configuration register mask */
#define EMC_Config_MASK             ((uint32_t)(0x101))


/***********************************************************************
 * Dynamic Memory Control register (EMCDynamicControl)
 **********************************************************************/
/* Dynamic Memory Control register EMC: Dynamic memory clock enable. */
#define EMC_DYNAMIC_CTRL_MEMCLK_EN_POS              (0)
#define EMC_DYNAMIC_CTRL_MEMCLK_EN_BMASK            (1<<EMC_DYNAMIC_CTRL_MEMCLK_EN_POS)

#define EMC_DYNAMIC_CTRL_CE_SAVEPWR                 (0<<EMC_DYNAMIC_CTRL_MEMCLK_EN_POS)
#define EMC_DYNAMIC_CTRL_CE_ALLCLK_HI               (1<<EMC_DYNAMIC_CTRL_MEMCLK_EN_POS)

/* Dynamic Memory Control register EMC: Dynamic memory clock control */
#define EMC_DYNAMIC_CTRL_CLKCTRL_POS                (1)
#define EMC_DYNAMIC_CTRL_CLKCTRL_BMASK              (1<<EMC_DYNAMIC_CTRL_CLKCTRL_POS)

#define EMC_DYNAMIC_CTRL_CS_CLKOUT_STOP             (0<<EMC_DYNAMIC_CTRL_CLKCTRL_POS)
#define EMC_DYNAMIC_CTRL_CE_CLKOUT_CONT             (1<<EMC_DYNAMIC_CTRL_CLKCTRL_POS)

/* Dynamic Memory Control register EMC: Self-refresh request, EMCSREFREQ*/
#define EMC_DYNAMIC_CTRL_SELFREFRESH_REQ_POS            (2)
#define EMC_DYNAMIC_CTRL_SELFREFRESH_REQ_BMASK          (1<<EMC_DYNAMIC_CTRL_SELFREFRESH_REQ_POS)

#define EMC_DYNAMIC_CTRL_SR_NORMALMODE              (0<<EMC_DYNAMIC_CTRL_SELFREFRESH_REQ_POS)
#define EMC_DYNAMIC_CTRL_SR_SELFREFRESH             (1<<EMC_DYNAMIC_CTRL_SELFREFRESH_REQ_POS)

/* Dynamic Memory Control register EMC: Memory clock control (MMC)*/
#define EMC_DYNAMIC_CTRL_MMC_CLKOUTCTRL_POS         (5)
#define EMC_DYNAMIC_CTRL_MMC_CLKOUTCTRL_BMASK       (1<<EMC_DYNAMIC_CTRL_MMC_CLKOUTCTRL_POS)

#define EMC_DYNAMIC_CTRL_MMC_CLKOUT_ENABLED         (0<<EMC_DYNAMIC_CTRL_MMC_CLKOUTCTRL_POS)
#define EMC_DYNAMIC_CTRL_MMC_CLKOUT_DISABLED        (1<<EMC_DYNAMIC_CTRL_MMC_CLKOUTCTRL_POS)


/* Dynamic Memory Control register EMC: SDRAM initialization*/
#define EMC_DYNAMIC_CTRL_SDRAM_INIT_POS             (7)
#define EMC_DYNAMIC_CTRL_SDRAM_INIT_BMASK           (0x03<<EMC_DYNAMIC_CTRL_SDRAM_INIT_POS)

#define EMC_DYNAMIC_CTRL_SDRAM_NORMAL           (0<<EMC_DYNAMIC_CTRL_SDRAM_INIT_POS)
#define EMC_DYNAMIC_CTRL_SDRAM_MODE             (1<<EMC_DYNAMIC_CTRL_SDRAM_INIT_POS)
#define EMC_DYNAMIC_CTRL_SDRAM_PALL             (2<<EMC_DYNAMIC_CTRL_SDRAM_INIT_POS)
#define EMC_DYNAMIC_CTRL_SDRAM_NOP              (3<<EMC_DYNAMIC_CTRL_SDRAM_INIT_POS)

/* Dynamic Memory Control register EMC: Low-power SDRAM deep-sleep mode (DP)*/
#define EMC_DYNAMIC_CTRL_SDRAM_PWRMODE_POS          (13)
#define EMC_DYNAMIC_CTRL_SDRAM_PWRMODE_BMASK        (0x01<<EMC_DYNAMIC_CTRL_SDRAM_PWRMODE_POS)

#define EMC_DYNAMIC_CTRL_DP_NORMAL                  (0<<EMC_DYNAMIC_CTRL_SDRAM_PWRMODE_POS)
#define EMC_DYNAMIC_CTRL_DP_DEEPSLEEP               (1<<EMC_DYNAMIC_CTRL_SDRAM_PWRMODE_POS)


/***********************************************************************
 * Dynamic Memory Refresh Timer register (EMCDynamicRefresh)
 **********************************************************************/
/* Dynamic Memory Refresh Timer register EMC: Refresh timer (REFRESH) */
#define EMC_DynamicRefresh_REFRESH(n)   ((uint32_t ) (n & 0x3ff))

/***********************************************************************
 * Dynamic Memory Read Configuration register (EMCDynamicReadConfig)
 **********************************************************************/
/* EMCDynamicReadConfig register EMC:Read data strategy (RD) */
#define EMC_DynamicReadConfig_RD(n)     ((uint32_t )(n & 0x03))

/***********************************************************************
 * Dynamic Memory Percentage Command Period register (EMCDynamictRP)
 **********************************************************************/
/* EMCDynamictRP register EMC: Precharge command period (tRP). */
#define EMC_DynamictRP_tRP(n)           ((uint32_t )(n & 0x0f))

/***********************************************************************
 * Dynamic Memory Active to Precharge Command Period register (EMCDynamictRAS)
 **********************************************************************/
/* EMCDynamictRAS register EMC: Active to precharge command period (tRAS) */
#define EMC_DynamictRP_tRAS(n)          ((uint32_t )(n & 0x0f))

/***********************************************************************
 * Dynamic Memory Self-refresh Exit Time register (EMCDynamictSREX)
 **********************************************************************/
/* EMCDynamictSREX register EMC: self-refresh exit time (tSREX)) */

#define EMC_DynamictRP_tSREX(n)         ((uint32_t )(n & 0x0f))

/***********************************************************************
 * Dynamic Memory Last Data Out to Active Time register (EMCDynamictAPR)
 **********************************************************************/
/* EMCDynamictAPR register EMC: Last-data-out to active command time (tAPR) */
#define EMC_DynamictAPR_tAPR(n)         ((uint32_t )(n & 0x0f))

/***********************************************************************
 * Dynamic Memory Data-in to Active Command Time register (EMCDynamictDAL)
 **********************************************************************/
/* EMCDynamictDAL register EMC: Data-in to active command (tDAL)*/
#define EMC_DynamictDAL_tDAL(n)         ((uint32_t )(n & 0x0f))

/***********************************************************************
 * Dynamic Memory Write Recovery Time register (EMCDynamictWR)
 **********************************************************************/
/* EMCDynamictWR register EMC: Write recovery time (tWR)*/
#define EMC_DynamictWR_tWR(n)           (uint32_t )(n & 0x0f)

/***********************************************************************
 * Dynamic Memory Active to Active Command Period register (EMCDynamictRC)
 **********************************************************************/
/* EMCDynamictRC register EMC: Active to active command period (tRC)*/
#define EMC_DynamictRC_tRC(n)           (uint32_t )(n & 0x1f)

/***********************************************************************
 * Dynamic Memory Auto-refresh Period register (EMCDynamictRFC)
 **********************************************************************/
/* EMCDynamictRFC register EMC: Auto-refresh period and auto-refresh to active command period (tRFC)*/
#define EMC_DynamictRFC_tRFC(n)         ((uint32_t )(n & 0x1f))

/***********************************************************************
 * Dynamic Memory Exit Self-refresh register (EMCDynamictXSR)
 **********************************************************************/
/* EMCDynamictXSR register EMC: Exit self-refresh to active command time (tXSR)*/
#define EMC_DynamictXSR_tXSR(n)         ((uint32_t )(n & 0x1f))

/***********************************************************************
 * Dynamic Memory Active Bank A to Active Bank B Time register (EMCDynamictRRD)
 **********************************************************************/
/* EMCDynamictRRD register EMC: Active bank A to active bank B latency (tRRD )*/
#define EMC_DynamictRRD_tRRD(n)         ((uint32_t )(n & 0x0f))

/***********************************************************************
 Dynamic Memory Load Mode register to Active Command Time (EMCDynamictMRD)
 **********************************************************************/
/* EMCDynamictMRD register EMC: Load mode register to active command time (tMRD)*/
#define EMC_DynamictMRD_tMRD(n)         ((uint32_t )(n & 0x1f))

/***********************************************************************
 * Static Memory Extended Wait Register (EMCStaticExtendedWait)
 **********************************************************************/
/* StaticExtendedWait register EMC: External wait time out. */
#define EMC_StaticExtendedWait_EXTENDEDWAIT(n)          ((uint32_t )(n & 0x3ff))


/***********************************************************************
 * Dynamic Memory Configuration registers (EMCDynamicConfig0-3)
 **********************************************************************/
/* DynamicConfig register EMC: Memory device (MD). */
#define EMC_DYNAMIC_CFG_MEMDEV_POS              (3)
#define EMC_DYNAMIC_CFG_MEMDEV_BMASK                (0x03 << EMC_DYNAMIC_CFG_MEMDEV_POS)

#define EMC_DYNAMIC_CFG_MEMDEV_SDRAM                (0 << EMC_DYNAMIC_CFG_MEMDEV_POS)
#define EMC_DYNAMIC_CFG_MEMDEV_LOWPWR_SDRAM         (1 << EMC_DYNAMIC_CFG_MEMDEV_POS)

/* DynamicConfig register EMC: Address mapping (AM) */
#define EMC_DYNAMIC_CFG_ADD_MAP_P1_POS                      (7)
#define EMC_DYNAMIC_CFG_ADD_MAP_P1_MASK                     (0x3F<<EMC_DYNAMIC_CFG_ADD_MAP_P1_POS)
#define EMC_DYNAMIC_CFG_ADD_MAP_P2_POS                      (12)
#define EMC_DYNAMIC_CFG_ADD_MAP_P2_MASK                     (0x01 << EMC_DYNAMIC_CFG_ADD_MAP_P2_POS)
#define EMC_DYNAMIC_CFG_ADD_MAP_P3_POS                      (14)
#define EMC_DYNAMIC_CFG_ADD_MAP_P3_MASK                     (0x01 << EMC_DYNAMIC_CFG_ADD_MAP_P3_POS)

#define EMC_DYNAMIC_CFG_ADD_MAP_P1(n)                         (  (n<<EMC_DYNAMIC_CFG_ADD_MAP_P1_POS)&EMC_DYNAMIC_CFG_ADD_MAP_P1_MASK)
#define EMC_DYNAMIC_CFG_ADD_MAP_P2(n)                         (  (n<<EMC_DYNAMIC_CFG_ADD_MAP_P2_POS)&EMC_DYNAMIC_CFG_ADD_MAP_P2_MASK)
#define EMC_DYNAMIC_CFG_ADD_MAP_P3(n)                         (  (n<<EMC_DYNAMIC_CFG_ADD_MAP_P3_POS)&EMC_DYNAMIC_CFG_ADD_MAP_P3_MASK)

#define EMC_ADD_MAP_ROW_BANK_COL                               (0)
#define EMC_ADD_MAP_BANK_ROW_COL                               (1)


/* DynamicConfig register EMC: Buffer enable */
#define EMC_DYNAMIC_CFG_BUFFENABLE_POS          (19)
#define EMC_DYNAMIC_CFG_BUFFENABLE_BMASK        (0x01<<EMC_DYNAMIC_CFG_BUFFENABLE_POS)

#define EMC_DYNAMIC_CFG_BUFF_DISABLED           (0<<EMC_DYNAMIC_CFG_BUFFENABLE_POS)
#define EMC_DYNAMIC_CFG_BUFF_ENABLED            (1<<EMC_DYNAMIC_CFG_BUFFENABLE_POS)


/* DynamicConfig register EMC: Write protect (P) */
#define EMC_DYNAMIC_CFG_WRPROTECT_POS           (20)
#define EMC_DYNAMIC_CFG_WRPROTECT_BMASK         (0x01<<EMC_DYNAMIC_CFG_WRPROTECT_POS)

#define EMC_DYNAMIC_CFG_WR_UNPROTECTED          (0<<EMC_DYNAMIC_CFG_WRPROTECT_POS)
#define EMC_DYNAMIC_CFG_WR_PROTECTED            (1<<EMC_DYNAMIC_CFG_WRPROTECT_POS)

/***********************************************************************
 * Dynamic Memory RAS & CAS Delay registers (EMCDynamicRASCAS0-3)
 **********************************************************************/
/* DynamicRASCAS register EMC: RAS latency (active to read/write delay) (RAS). */
#define EMC_DYNAMIC_RASCAS_RASCFG_POS           (0)
#define EMC_DYNAMIC_RASCAS_RASCFG_BMASK         (0x03<<EMC_DYNAMIC_RASCAS_RASCFG_POS)

#define EMC_DYNAMIC_RASCAS_RASLATENCY_RESVD     (0<<EMC_DYNAMIC_RASCAS_RASCFG_POS)
#define EMC_DYNAMIC_RASCAS_RASLATENCY_1CLK      (1<<EMC_DYNAMIC_RASCAS_RASCFG_POS)
#define EMC_DYNAMIC_RASCAS_RASLATENCY_2CLK      (2<<EMC_DYNAMIC_RASCAS_RASCFG_POS)
#define EMC_DYNAMIC_RASCAS_RASLATENCY_3CLK      (3<<EMC_DYNAMIC_RASCAS_RASCFG_POS)


/* DynamicRASCAS register EMC: CAS latency (CAS)*/
#define EMC_DYNAMIC_RASCAS_CASCFG_POS           (8)
#define EMC_DYNAMIC_RASCAS_CASCFG_BMASK         (0x03<<EMC_DYNAMIC_RASCAS_CASCFG_POS)

#define EMC_DYNAMIC_RASCAS_CASLATENCY_RESVD     (0<<EMC_DYNAMIC_RASCAS_CASCFG_POS)
#define EMC_DYNAMIC_RASCAS_CASLATENCY_1CLK      (1<<EMC_DYNAMIC_RASCAS_CASCFG_POS)
#define EMC_DYNAMIC_RASCAS_CASLATENCY_2CLK      (2<<EMC_DYNAMIC_RASCAS_CASCFG_POS)
#define EMC_DYNAMIC_RASCAS_CASLATENCY_3CLK      (3<<EMC_DYNAMIC_RASCAS_CASCFG_POS)

/***********************************************************************
 * Static Memory Configuration registers (EMCStaticConfig0-3)
 **********************************************************************/
/* StaticConfig register EMC: Memory width (MW). */
#define EMC_STATIC_CFG_MEMWIDTH_POS     (0)
#define EMC_STATIC_CFG_MEMWIDTH_BMASK   (0x03<<EMC_STATIC_CFG_MEMWIDTH_POS)
#define EMC_StaticConfig_MW(n)          ((uint32_t )((n<<EMC_STATIC_CFG_MEMWIDTH_POS) & EMC_STATIC_CFG_MEMWIDTH_BMASK))

/* StaticConfig register EMC: Memory width 8bit . */
#define EMC_STATIC_CFG_MW_8BITS         (EMC_StaticConfig_MW(0))

/* StaticConfig register EMC: Memory width 16bit . */
#define EMC_STATIC_CFG_MW_16BITS        (EMC_StaticConfig_MW(1))

/* StaticConfig register EMC: Memory width 32bit . */
#define EMC_STATIC_CFG_MW_32BITS        (EMC_StaticConfig_MW(2))

/* StaticConfig register EMC: Page mode (PM) */
#define EMC_STATIC_CFG_PAGEMODE_POS                 (3)
#define EMC_STATIC_CFG_PAGEMODE_MASK                (1<<EMC_STATIC_CFG_PAGEMODE_POS)

#define EMC_CFG_PM_DISABLE                      (0<<EMC_STATIC_CFG_PAGEMODE_POS)
#define EMC_CFG_PM_ASYNC_ENABLE                 (1<<EMC_STATIC_CFG_PAGEMODE_POS)


/* StaticConfig register EMC: Chip select polarity (PC) */
#define EMC_STATIC_CFG_CHIPPOLARITY_POS             (6)
#define EMC_STATIC_CFG_CHIPPOLARITY_MASK            (1<<EMC_STATIC_CFG_CHIPPOLARITY_POS)

#define EMC_CFG_BYTELAND_PC_ACTIVE_LO               (0<<EMC_STATIC_CFG_CHIPPOLARITY_POS)
#define EMC_CFG_BYTELAND_PC_ACTIVE_HI               (1<<EMC_STATIC_CFG_CHIPPOLARITY_POS)


/* StaticConfig register EMC: Byte lane state (PB) */
#define EMC_STATIC_CFG_BYTELAND_POS                 (7)
#define EMC_STATIC_CFG_BYTELAND_MASK                (1<<EMC_STATIC_CFG_BYTELAND_POS)

#define EMC_CFG_BYTELAND_READ_BITSHIGH              (0<<EMC_STATIC_CFG_BYTELAND_POS)
#define EMC_CFG_BYTELAND_READ_BITSLOW               (1<<EMC_STATIC_CFG_BYTELAND_POS)


/* StaticConfig register EMC: Extended wait (EW) */
#define EMC_STATIC_CFG_EXTWAIT_POS              (8)
#define EMC_STATIC_CFG_EXTWAIT_MASK             (1<<EMC_STATIC_CFG_EXTWAIT_POS)

#define EMC_CFG_EW_DISABLED                 (0<<EMC_STATIC_CFG_EXTWAIT_POS)
#define EMC_CFG_EW_ENABLED                  (1<<EMC_STATIC_CFG_EXTWAIT_POS)


/* StaticConfig register EMC: Buffer enable (B) */
#define EMC_STATIC_CFG_BUFENABLE_POS                (19)
#define EMC_STATIC_CFG_BUFENABLE_MASK               (1<<EMC_STATIC_CFG_BUFENABLE_POS)

#define EMC_CFG_BUF_DISABLED                    (0<<EMC_STATIC_CFG_BUFENABLE_POS)
#define EMC_CFG_BUF_ENABLED                     (1<<EMC_STATIC_CFG_BUFENABLE_POS)

/* StaticConfig register EMC: Write protect (P) */
#define EMC_STATIC_CFG_WRIEPROTECT_POS              (20)
#define EMC_STATIC_CFG_WRIEPROTECT_MASK             (1<<EMC_STATIC_CFG_WRIEPROTECT_POS)

#define EMC_CFG_WRITEPROTECT_DISABLED               (0<<EMC_STATIC_CFG_WRIEPROTECT_POS)
#define EMC_CFG_WRITEPROTECT_ENABLED                (1<<EMC_STATIC_CFG_WRIEPROTECT_POS)

/***********************************************************************
 * Static Memory Write Enable Delay registers (EMCStaticWaitWen0-3)
 **********************************************************************/
/* StaticWaitWen register EMC: Wait write enable (WAITWEN). */
#define EMC_StaticWaitWen_WAITWEN(n)    ((uint32_t )(n & 0x0f))

/***********************************************************************
 * Static Memory Output Enable Delay registers (EMCStaticWaitOen0-3)
 **********************************************************************/
/* StaticWaitOen register EMC: Wait output enable (WAITOEN). */
#define EMC_StaticWaitOen_WAITOEN(n)    ((uint32_t )(n & 0x0f))

/***********************************************************************
 * Static Memory Read Delay registers (EMCStaticWaitRd0-3)
 **********************************************************************/
/* StaticWaitRd register EMC: Non-page mode read wait states or asynchronous page mode
read first access wait state (WAITRD) */
#define EMC_StaticWaitRd_WAITRD(n)      ((uint32_t )(n & 0x1f))

/***********************************************************************
 * Static Memory Page Mode Read Delay registers (EMCStaticwaitPage0-3)
 **********************************************************************/
/* StaticwaitPage register EMC: Asynchronous page mode read after the first
read wait states (WAITPAGE). */
#define EMC_StaticwaitPage_WAITPAGE(n)  ((uint32_t )(n & 0x1f))

/***********************************************************************
 * Static Memory Write Delay registers (EMCStaticWaitwr0-3)
 **********************************************************************/
/* StaticWaitwr register EMC: Write wait states (WAITWR). */
#define EMC_StaticWaitwr_WAITWR(n)      ((uint32_t )(n & 0x1f))

/***********************************************************************
 * Static Memory Turn Round Delay registers (EMCStaticWaitTurn0-3)
 **********************************************************************/
/* StaticWaitTurn register EMC: Bus turnaround cycles (WAITTURN). */
#define EMC_StaticWaitTurn_WAITTURN(n)  ((uint32_t )(n & 0x0f))

/***********************************************************************
 * Delay Control register (EMCDLYCTL)
 **********************************************************************/
#define EMC_DLYCTL_CMDDLY(n)        ((uint32_t)(n&0x1F))
#define EMC_DLYCTL_FBCLKDLY(n)      ((uint32_t)((n&0x1F)<<8))
#define EMC_DLYCTL_CLKOUT0DLY(n)    ((uint32_t)((n&0x1F)<<16))
#define EMC_DLYCTL_CLKOUT1DLY(n)    ((uint32_t)((n&0x1F)<<24))

/***********************************************************************
 * EMC Calibration register (EMCCAL)
 **********************************************************************/
#define EMC_CAL_CALVALUE(n)         ((uint32_t)(n&0xFF))
#define EMC_CAL_START               ((uint32_t)(1<<14))
#define EMC_CAL_DONE                ((uint32_t)(1<<15))

/***********************************************************************
 * EMC Function Return codes
 **********************************************************************/
 typedef int32_t EMC_FUNC_CODE;
#define  EMC_FUNC_OK                            (0)
#define  EMC_FUNC_ERR                           (0x01)
#define  EMC_FUNC_INVALID_PARAM                 (0x02)


/**
 * @}
 */


/* Public Types --------------------------------------------------------------- */
/** @defgroup EMC_Public_Types EMC Public Types
 * @{
 */
/*EMC dynamic memory registers enum*/
typedef enum
{
  EMC_DYN_MEM_REFRESH_TIMER,
  EMC_DYN_MEM_READ_CONFIG,
  EMC_DYN_MEM_TRP,
  EMC_DYN_MEM_TRAS,
  EMC_DYN_MEM_TSREX,
  EMC_DYN_MEM_TAPR,
  EMC_DYN_MEM_TDAL,
  EMC_DYN_MEM_TWR,
  EMC_DYN_MEM_TRC,
  EMC_DYN_MEM_TRFC,
  EMC_DYN_MEM_TXSR,
  EMC_DYN_MEM_TRRD,
  EMC_DYN_MEM_TMRD
} EMC_DYN_MEM_PAR;

/*EMC static memory registers enum*/
typedef enum
{
  EMC_STA_MEM_WAITWEN,
  EMC_STA_MEM_WAITOEN,
  EMC_STA_MEM_WAITRD,
  EMC_STA_MEM_WAITPAGE,
  EMC_STA_MEM_WAITWR,
  EMC_STA_MEM_WAITTURN,
} EMC_STA_MEM_PAR;

/* SDRAM Config Struct */
typedef struct
{
    uint8_t  CSn;         // 0/1/2/3
    uint32_t TotalSize;   // SDRAM TotalSize
    uint16_t ChipSize;    // chip size(Mb): 16Mb, 64Mb, 128Mb, 256Mb, 512Mb
    uint8_t   DataWidth;  // 8bit, 16 bit, 32bit
    uint8_t   AddrBusWidth;  // 16bit, 32bit
    uint8_t   AddrMap;           // EMC_ADD_MAP_BANK_ROW_COL/ EMC_ADD_MAP_ROW_BANK_COL

    /* timming */
    uint16_t RefreshTime;  // Dynamic Refresh Time
    uint8_t  ReadConfig;    // Read Config Strategy
    uint8_t  PrechargeCmdPeriod;  // Precharge Command Period (tRP)
    uint8_t SeftRefreshExitTime; // Self-Refresh Exit Time (tSREX)
    uint8_t DataOut2ActiveTime;            // the last-data-out to active command time (tAPR)
    uint8_t DataIn2ActiveTime;      //  the data-in to active command time (tDAL, or tAPW)
    uint8_t WriteRecoveryTime;      // the write recovery time (tWR, tDPL, tRWL, or tRDL)
    uint8_t Active2ActivePeriod;       // the active to active command period (tRC)
    uint8_t AutoRefrehPeriod;      // the auto-refresh period and auto-refresh to active command period (tRFC/tRC)
    uint8_t ExitSelfRefreshTime; // the exit self-refresh to active command time (tXSR)
    uint8_t ActiveBankLatency;  // the active bank A to active bank B latency (tRRD)
    uint8_t LoadModeReg2Active;            // the load mode register to active command time (tMRD)
    uint8_t Active2PreChargeTime;     // Active to precharge command period (tRAS)
    uint8_t  RASLatency;          // RAS Delay
    uint8_t  CASLatency;          // CAS Delay
    
} EMC_DYN_MEM_Config_Type;

typedef struct
{
    uint8_t  CSn;         // 0/1/2/3
    uint8_t DataWidth;    // 8bit, 16bit, 32bit
    uint8_t PageMode;   // 1: asynchronous page mode enabled
    uint8_t ByteLane;   // 1: Read when active bits are low, 0: read when acrive bits are High
    uint8_t ExtendedWait;  //1: enabled
    uint8_t AddressMirror; // 1: reset memory map, 0: normal memory map

    uint8_t  WaitWEn;       // Delay from the chip select to the write enable (CCLK cycles) 
    uint8_t  WaitOEn;       // Delay from the chip select or address change to output enable (CCLK cycles)
    uint8_t  WaitRd;        // Delay from the chip select to the read access (CCLK cycles)
    uint8_t  WaitPage;      // Delay for asynchronous page mode sequential accesses (CCLK cycles)
    uint8_t  WaitWr;        // Delay from the chip select to the write access (CCLK cycles)
    uint8_t  WaitTurn;      // The number of bus turnaround cycles
} EMC_STATIC_MEM_Config_Type;
/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup EMC_Public_Functions EMC Public Functions
 * @{
 */
 uint32_t EMC_SDRAM_REFRESH(uint32_t time);
 uint32_t EMC_NS2CLK(uint32_t time);
 EMC_FUNC_CODE DynMem_Init(EMC_DYN_MEM_Config_Type* pConfig);
 EMC_FUNC_CODE StaticMem_Init(EMC_STATIC_MEM_Config_Type* pConfig);
 EMC_FUNC_CODE EMC_Init(void);
 EMC_FUNC_CODE EMC_ConfigEndianMode(uint32_t endian_mode);
 EMC_FUNC_CODE EMC_DynCtrlClockEnable(uint32_t clock_enable);
 EMC_FUNC_CODE EMC_DynCtrlClockControl(int32_t clock_control);
 EMC_FUNC_CODE EMC_DynCtrlSelfRefresh(uint32_t self_refresh_mode);
 EMC_FUNC_CODE EMC_DynCtrlMMC(uint32_t MMC_val);
 EMC_FUNC_CODE EMC_DynCtrlSDRAMInit(uint32_t SDRAM_command);
 EMC_FUNC_CODE EMC_DynCtrlPowerDownMode(uint32_t SDRAM_command);
 EMC_FUNC_CODE EMC_SetDynMemoryParameter(EMC_DYN_MEM_PAR par, uint32_t val);
 EMC_FUNC_CODE EMC_StaticExtendedWait(uint32_t Extended_wait_time_out);
 EMC_FUNC_CODE EMC_DynMemConfigMD(uint32_t index , uint32_t mem_dev);
 EMC_FUNC_CODE EMC_DynMemConfigAM(uint32_t index , uint8_t addr_bus_width, uint8_t addr_map,uint8_t data_bus_width,uint16_t chip_size);
 EMC_FUNC_CODE EMC_DynMemConfigB(uint32_t index , uint32_t buff_control);
 EMC_FUNC_CODE EMC_DynMemConfigP(uint32_t index , uint32_t permission);
 EMC_FUNC_CODE EMC_DynMemRAS(uint32_t index , uint32_t ras_val);
 EMC_FUNC_CODE EMC_DynMemCAS(uint32_t index , uint32_t cas_val);
 EMC_FUNC_CODE EMC_StaMemConfigMW(uint32_t index , uint32_t mem_width);
 EMC_FUNC_CODE EMC_StaMemConfigPM(uint32_t index , uint32_t page_mode);
 EMC_FUNC_CODE EMC_StaMemConfigPC(uint32_t index , uint32_t pol_val);
 EMC_FUNC_CODE EMC_StaMemConfigPB(uint32_t index , uint32_t pb_val);
 EMC_FUNC_CODE EMC_StaMemConfigEW(uint32_t index , uint32_t ex_wait);
 EMC_FUNC_CODE EMC_StaMemConfigB(uint32_t index , uint32_t buf_val);
 EMC_FUNC_CODE EMC_StaMemConfigpP(uint32_t index , uint32_t per_val);
 EMC_FUNC_CODE EMC_SetStaMemoryParameter(uint32_t index ,EMC_STA_MEM_PAR par, uint32_t val);

/**
 * @}
 */


#endif /* __LPC_EMC_H_ */

/**
 * @}
 */



