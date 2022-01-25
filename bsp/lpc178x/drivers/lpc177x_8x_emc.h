/**********************************************************************
* $Id$      lpc177x_8x_emc.h            2011-06-02
*//**
* @file     lpc177x_8x_emc.h
* @brief    Contains all macro definitions and function prototypes
*           support for EMC firmware library on LPC177x_8x
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

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup EMC   EMC (External Memory Controller)
 * @ingroup LPC177x_8xCMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC177X_8X_EMC_H_
#define __LPC177X_8X_EMC_H_

#include "lpc_types.h"
#include "LPC177x_8x.h"


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
/* EMC Configuration register : Enable control. */
#define EMC_Config_Endian_Mode      ((uint32_t )(1<<0))
/* EMC Configuration register: CCLK. */
#define EMC_Config_CCLK             ((uinr32_t)(1<<8))
/* EMC Configuration register mask */
#define EMC_Config_MASK             ((uint32_t)(0x101))


/***********************************************************************
 * Dynamic Memory Control register (EMCDynamicControl)
 **********************************************************************/
/* Dynamic Memory Control register EMC: Dynamic memory clock enable. */
#define EMC_DynamicControl_CE           ((uint32_t )(1<<0))
/* Dynamic Memory Control register EMC: Dynamic memory clock control */
#define EMC_DynamicControl_CS           ((uint32_t )(1<<1))
/* Dynamic Memory Control register EMC: Self-refresh request, EMCSREFREQ*/
#define EMC_DynamicControl_SR           ((uint32_t )(1<<2))
/* Dynamic Memory Control register EMC: Memory clock control (MMC)*/
#define EMC_DynamicControl_MMC          ((uint32_t )(1<<5))
/* Dynamic Memory Control register EMC: SDRAM initialization*/
#define EMC_DynamicControl_I(n)         ((uint32_t )(n<<7))
/* Dynamic Memory Control register EMC: Low-power SDRAM deep-sleep mode (DP)*/
#define EMC_DynamicControl_DP           ((uint32_t ) (1<<13))

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
#define EMC_DynamicConfig_MD(n)         ((uint32_t )(n << 3))
/* DynamicConfig register EMC: Address mapping (AM) */
#define EMC_DynamicConfig_AM1(n)        ((uint32_t )(n << 7))
/* DynamicConfig register EMC: Address mapping (AM) */
#define EMC_DynamicConfig_AM2(n)        ((uint32_t )(1 << 14))
/* DynamicConfig register EMC: Buffer enable */
#define EMC_DynamicConfig_B             ((uint32_t )(1 << 19))
/* DynamicConfig register EMC: Write protect (P) */
#define EMC_DynamicConfig_P             ((uint32_t )(1 << 20))

/***********************************************************************
 * Dynamic Memory RAS & CAS Delay registers (EMCDynamicRASCAS0-3)
 **********************************************************************/
/* DynamicRASCAS register EMC: RAS latency (active to read/write delay) (RAS). */
#define EMC_DynamicConfig_RAS(n)            ((uint32_t )(n & 0x03))
/* DynamicRASCAS register EMC: CAS latency (CAS)*/
#define EMC_DynamicConfig_CAS(n)            ((uint32_t )(n << 8))

/***********************************************************************
 * Static Memory Configuration registers (EMCStaticConfig0-3)
 **********************************************************************/
/* StaticConfig register EMC: Memory width (MW). */
#define EMC_StaticConfig_MW(n)          ((uint32_t )(n & 0x03))
/* StaticConfig register EMC: Memory width 8bit . */
#define EMC_StaticConfig_MW_8BITS       (EMC_StaticConfig_MW(0))
/* StaticConfig register EMC: Memory width 16bit . */
#define EMC_StaticConfig_MW_16BITS      (EMC_StaticConfig_MW(1))
/* StaticConfig register EMC: Memory width 32bit . */
#define EMC_StaticConfig_MW_32BITS      (EMC_StaticConfig_MW(2))
/* StaticConfig register EMC: Page mode (PM) */
#define EMC_StaticConfig_PM             ((uint32_t )(1 << 3))
/* StaticConfig register EMC: Chip select polarity (PC) */
#define EMC_StaticConfig_PC             ((uint32_t )(1 << 6))
/* StaticConfig register EMC: Byte lane state (PB) */
#define EMC_StaticConfig_PB             ((uint32_t )(1 << 7))
/* StaticConfig register EMC: Extended wait (EW) */
#define EMC_StaticConfig_EW             ((uint32_t )(1 << 8))
/* StaticConfig register EMC: Buffer enable (B) */
#define EMC_StaticConfig_B              ((uint32_t )(1 << 19))
/* StaticConfig register EMC: Write protect (P) */
#define EMC_StaticConfig_P              ((uint32_t )(1 << 20))

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

#define EMC_LITTLE_ENDIAN_MODE      ((uint32_t)(0))
#define EMC_BIG_ENDIAN_MODE         ((uint32_t)(1))

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

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup EMC_Public_Functions EMC Public Functions
 * @{
 */

extern void EMC_Init(void);
extern void EMC_ConfigEndianMode(uint32_t endian_mode);
extern void EMC_DynCtrlClockEnable(uint32_t clock_enable);
extern void EMC_DynCtrlClockControl(int32_t clock_control);
extern void EMC_DynCtrlSelfRefresh(uint32_t self_refresh_mode);
extern void EMC_DynCtrlMMC(uint32_t MMC_val);
extern void EMC_DynCtrlSDRAMInit(uint32_t SDRAM_command);
extern void EMC_DynCtrlPowerDownMode(uint32_t SDRAM_command);
extern void EMC_SetDynMemoryParameter(EMC_DYN_MEM_PAR par, uint32_t val);
extern void EMC_StaticExtendedWait(uint32_t Extended_wait_time_out);
extern void EMC_DynMemConfigMD(uint32_t index , uint32_t mem_dev);
extern void EMC_DynMemConfigAM(uint32_t index , uint32_t add_mapped);
extern void EMC_DynMemConfigB(uint32_t index , uint32_t buff_control);
extern void EMC_DynMemConfigP(uint32_t index , uint32_t permission);
extern void EMC_DynMemRAS(uint32_t index , uint32_t ras_val);
extern void EMC_DynMemCAS(uint32_t index , uint32_t cas_val);
extern void EMC_StaMemConfigMW(uint32_t index , uint32_t mem_width);
extern void EMC_StaMemConfigPM(uint32_t index , uint32_t page_mode);
extern void EMC_StaMemConfigPC(uint32_t index , uint32_t pol_val);
extern void EMC_StaMemConfigPB(uint32_t index , uint32_t pb_val);
extern void EMC_StaMemConfigEW(uint32_t index , uint32_t ex_wait);
extern void EMC_StaMemConfigB(uint32_t index , uint32_t buf_val);
extern void EMC_StaMemConfigpP(uint32_t index , uint32_t per_val);
extern void EMC_SetStaMemoryParameter(uint32_t index ,EMC_STA_MEM_PAR par, uint32_t val);

/**
 * @}
 */


#endif /* __LPC177X_8X_EMC_H_ */

/**
 * @}
 */



