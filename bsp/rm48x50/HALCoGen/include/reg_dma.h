/** @file reg_dma.h
*   @brief DMA Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   .
*   which are relevant for the DMA driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_DMA_H__
#define __REG_DMA_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* DMA Register Frame Definition */
/** @struct dmaBase
*   @brief DMA Register Frame Definition
*
*   This type is used to access the DMA Registers.
*/
/** @struct dmaBASE_t
*   @brief DMA Register Definition
*
*   This structure is used to access the DMA module egisters.
*/
typedef volatile struct dmaBase
{

    uint32 GCTRL;      /**<  0x0000: Global Control Register                */
    uint32 PEND;       /**<  0x0004: Channel Pending Register               */
    uint32 FBREG;      /**<  0x0008: Fall Back Register                     */
    uint32 DMASTAT;    /**<  0x000C: Status Register                        */
    uint32  rsvd1;     /**<  0x0010: Reserved                               */
    uint32 HWCHENAS;   /**<  0x0014: HW Channel Enable Set                  */
    uint32  rsvd2;     /**<  0x0018: Reserved                               */
    uint32 HWCHENAR;   /**<  0x001C: HW Channel Enable Reset                */
    uint32  rsvd3;     /**<  0x0020: Reserved                               */
    uint32 SWCHENAS;   /**<  0x0024: SW Channel Enable Set                  */
    uint32  rsvd4;     /**<  0x0028: Reserved                               */
    uint32 SWCHENAR;   /**<  0x002C: SW Channel Enable Reset                */
    uint32  rsvd5;     /**<  0x0030: Reserved                               */
    uint32 CHPRIOS;    /**<  0x0034: Channel Priority Set                   */
    uint32  rsvd6;     /**<  0x0038: Reserved                               */
    uint32 CHPRIOR;    /**<  0x003C: Channel Priority Reset                 */
    uint32  rsvd7;     /**<  0x0040: Reserved                               */
    uint32 GCHIENAS;   /**<  0x0044: Global Channel Interrupt Enable Set    */
    uint32  rsvd8;     /**<  0x0048: Reserved                               */
    uint32 GCHIENAR;   /**<  0x004C: Global Channel Interrupt Enable Set    */
    uint32  rsvd9;     /**<  0x0050: Reserved                               */
    uint32 DREQASI[8U];/**<  0x0054 - 0x70: DMA Request Assignment Register */
    uint32  rsvd10[8U];/**<  0x0074 - 0x90: Reserved                        */
    uint32 PAR[4U];    /**<  0x0094 - 0xA0: Port Assignment Register        */
    uint32  rsvd11[4U];/**<  0x00A4 - 0xB0: Reserved                        */
    uint32 FTCMAP;     /**<  0x00B4: FTC Interrupt Mapping Register         */
    uint32  rsvd12;    /**<  0x00B8: Reserved                               */
    uint32 LFSMAP;     /**<  0x00BC: LFS Interrupt Mapping Register         */
    uint32  rsvd13;    /**<  0x00C0: Reserved                               */
    uint32 HBCMAP;     /**<  0x00C4: HBC Interrupt Mapping Register         */
    uint32  rsvd14;    /**<  0x00C8: Reserved                               */
    uint32 BTCMAP;     /**<  0x00CC: BTC Interrupt Mapping Register         */
    uint32  rsvd15;    /**<  0x00D0: Reserved                               */
    uint32 BERMAP;     /**<  0x00D4: BER Interrupt Mapping Register         */
    uint32  rsvd16;    /**<  0x00D8: Reserved                               */
    uint32 FTCINTENAS; /**<  0x00DC: FTC Interrupt Enable Set               */
    uint32  rsvd17;    /**<  0x00E0: Reserved                               */
    uint32 FTCINTENAR; /**<  0x00E4: FTC Interrupt Enable Reset             */
    uint32  rsvd18;    /**<  0x00E8: Reserved                               */
    uint32 LFSINTENAS; /**<  0x00EC: LFS Interrupt Enable Set               */
    uint32  rsvd19;    /**<  0x00F0: Reserved                               */
    uint32 LFSINTENAR; /**<  0x00F4: LFS Interrupt Enable Reset             */
    uint32  rsvd20;    /**<  0x00F8: Reserved                               */
    uint32 HBCINTENAS; /**<  0x00FC: HBC Interrupt Enable Set               */
    uint32  rsvd21;    /**<  0x0100: Reserved                               */
    uint32 HBCINTENAR; /**<  0x0104: HBC Interrupt Enable Reset             */
    uint32  rsvd22;    /**<  0x0108: Reserved                               */
    uint32 BTCINTENAS; /**<  0x010C: BTC Interrupt Enable Set               */
    uint32  rsvd23;    /**<  0x0110: Reserved                               */
    uint32 BTCINTENAR; /**<  0x0114: BTC Interrupt Enable Reset             */
    uint32  rsvd24;    /**<  0x0118: Reserved                               */
    uint32 GINTFLAG;   /**<  0x011C: Global Interrupt Flag Register         */
    uint32  rsvd25;    /**<  0x0120: Reserved                               */
    uint32 FTCFLAG;    /**<  0x0124: FTC Interrupt Flag Register            */
    uint32  rsvd26;    /**<  0x0128: Reserved                               */
    uint32 LFSFLAG;    /**<  0x012C: LFS Interrupt Flag Register            */
    uint32  rsvd27;    /**<  0x0130: Reserved                               */
    uint32 HBCFLAG;    /**<  0x0134: HBC Interrupt Flag Register            */
    uint32  rsvd28;    /**<  0x0138: Reserved                               */
    uint32 BTCFLAG;    /**<  0x013C: BTC Interrupt Flag Register            */
    uint32  rsvd29;    /**<  0x0140: Reserved                               */
    uint32 BERFLAG;    /**<  0x0144: BER Interrupt Flag Register            */
    uint32  rsvd30;    /**<  0x0148: Reserved                               */
    uint32 FTCAOFFSET; /**<  0x014C: FTCA Interrupt Channel Offset Register */
    uint32 LFSAOFFSET; /**<  0x0150: LFSA Interrupt Channel Offset Register */
    uint32 HBCAOFFSET; /**<  0x0154: HBCA Interrupt Channel Offset Register */
    uint32 BTCAOFFSET; /**<  0x0158: BTCA Interrupt Channel Offset Register */
    uint32 BERAOFFSET; /**<  0x015C: BERA Interrupt Channel Offset Register */
    uint32 FTCBOFFSET; /**<  0x0160: FTCB Interrupt Channel Offset Register */
    uint32 LFSBOFFSET; /**<  0x0164: LFSB Interrupt Channel Offset Register */
    uint32 HBCBOFFSET; /**<  0x0168: HBCB Interrupt Channel Offset Register */
    uint32 BTCBOFFSET; /**<  0x016C: BTCB Interrupt Channel Offset Register */
    uint32 BERBOFFSET; /**<  0x0170: BERB Interrupt Channel Offset Register */
    uint32  rsvd31;    /**<  0x0174: Reserved                               */
    uint32 PTCRL;      /**<  0x0178: Port Control Register                  */
    uint32 RTCTRL;     /**<  0x017C: RAM Test Control Register              */
    uint32 DCTRL;      /**<  0x0180: Debug Control                          */
    uint32 WPR;        /**<  0x0184: Watch Point Register                   */
    uint32 WMR;        /**<  0x0188: Watch Mask Register                    */
    uint32 PAACSADDR;  /**<  0x018C:           */
    uint32 PAACDADDR;  /**<  0x0190:           */
    uint32 PAACTC;     /**<  0x0194:           */
    uint32 PBACSADDR;  /**<  0x0198: Port B Active Channel Source Address Register       */
    uint32 PBACDADDR;  /**<  0x019C: Port B Active Channel Destination Address Register  */
    uint32 PBACTC;     /**<  0x01A0: Port B Active Channel Transfer Count Register       */
    uint32  rsvd32;    /**<  0x01A4: Reserved                               */
    uint32 DMAPCR;     /**<  0x01A8: Parity Control Register                */
    uint32 DMAPAR;     /**<  0x01AC: DMA Parity Error Address Register      */
    uint32 DMAMPCTRL;  /**<  0x01B0: DMA Memory Protection Control Register */
    uint32 DMAMPST;    /**<  0x01B4: DMA Memory Protection Status Register  */
    struct
    {
    	uint32 STARTADD; /**<  0x01B8, 0x01C0, 0x01C8, 0x1D0: DMA Memory Protection Region Start Address Register  */
    	uint32 ENDADD;   /**<  0x01B8, 0x01C0, 0x01C8, 0x1D0: DMA Memory Protection Region Start Address Register  */
    }DMAMPR[4U];
} dmaBASE_t;


/** @def dmaREG
*   @brief DMA1 Register Frame Pointer
*
*   This pointer is used by the DMA driver to access the DMA module registers.
*/
#define dmaREG ((dmaBASE_t *)0xFFFFF000U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
