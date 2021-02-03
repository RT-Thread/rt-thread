/**
 * \file IfxHsct_regdef.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC26XB_UM_V1.2.R0
 * Specification: tc26xB_um_v1.2_MCSFR.xml (Revision: UM_V1.2)
 * MAY BE CHANGED BY USER [yes/no]: No
 *
 *                                 IMPORTANT NOTICE
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Hsct Hsct
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Hsct_Bitfields Bitfields
 * \ingroup IfxLld_Hsct
 * 
 * \defgroup IfxLld_Hsct_union Union
 * \ingroup IfxLld_Hsct
 * 
 * \defgroup IfxLld_Hsct_struct Struct
 * \ingroup IfxLld_Hsct
 * 
 */
#ifndef IFXHSCT_REGDEF_H
#define IFXHSCT_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Hsct_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_HSCT_ACCEN0_Bits
{
    unsigned int EN0:1;                     /**< \brief [0:0] Access Enable for Master TAG ID 0 (rw) */
    unsigned int EN1:1;                     /**< \brief [1:1] Access Enable for Master TAG ID 1 (rw) */
    unsigned int EN2:1;                     /**< \brief [2:2] Access Enable for Master TAG ID 2 (rw) */
    unsigned int EN3:1;                     /**< \brief [3:3] Access Enable for Master TAG ID 3 (rw) */
    unsigned int EN4:1;                     /**< \brief [4:4] Access Enable for Master TAG ID 4 (rw) */
    unsigned int EN5:1;                     /**< \brief [5:5] Access Enable for Master TAG ID 5 (rw) */
    unsigned int EN6:1;                     /**< \brief [6:6] Access Enable for Master TAG ID 6 (rw) */
    unsigned int EN7:1;                     /**< \brief [7:7] Access Enable for Master TAG ID 7 (rw) */
    unsigned int EN8:1;                     /**< \brief [8:8] Access Enable for Master TAG ID 8 (rw) */
    unsigned int EN9:1;                     /**< \brief [9:9] Access Enable for Master TAG ID 9 (rw) */
    unsigned int EN10:1;                    /**< \brief [10:10] Access Enable for Master TAG ID 10 (rw) */
    unsigned int EN11:1;                    /**< \brief [11:11] Access Enable for Master TAG ID 11 (rw) */
    unsigned int EN12:1;                    /**< \brief [12:12] Access Enable for Master TAG ID 12 (rw) */
    unsigned int EN13:1;                    /**< \brief [13:13] Access Enable for Master TAG ID 13 (rw) */
    unsigned int EN14:1;                    /**< \brief [14:14] Access Enable for Master TAG ID 14 (rw) */
    unsigned int EN15:1;                    /**< \brief [15:15] Access Enable for Master TAG ID 15 (rw) */
    unsigned int EN16:1;                    /**< \brief [16:16] Access Enable for Master TAG ID 16 (rw) */
    unsigned int EN17:1;                    /**< \brief [17:17] Access Enable for Master TAG ID 17 (rw) */
    unsigned int EN18:1;                    /**< \brief [18:18] Access Enable for Master TAG ID 18 (rw) */
    unsigned int EN19:1;                    /**< \brief [19:19] Access Enable for Master TAG ID 19 (rw) */
    unsigned int EN20:1;                    /**< \brief [20:20] Access Enable for Master TAG ID 20 (rw) */
    unsigned int EN21:1;                    /**< \brief [21:21] Access Enable for Master TAG ID 21 (rw) */
    unsigned int EN22:1;                    /**< \brief [22:22] Access Enable for Master TAG ID 22 (rw) */
    unsigned int EN23:1;                    /**< \brief [23:23] Access Enable for Master TAG ID 23 (rw) */
    unsigned int EN24:1;                    /**< \brief [24:24] Access Enable for Master TAG ID 24 (rw) */
    unsigned int EN25:1;                    /**< \brief [25:25] Access Enable for Master TAG ID 25 (rw) */
    unsigned int EN26:1;                    /**< \brief [26:26] Access Enable for Master TAG ID 26 (rw) */
    unsigned int EN27:1;                    /**< \brief [27:27] Access Enable for Master TAG ID 27 (rw) */
    unsigned int EN28:1;                    /**< \brief [28:28] Access Enable for Master TAG ID 28 (rw) */
    unsigned int EN29:1;                    /**< \brief [29:29] Access Enable for Master TAG ID 29 (rw) */
    unsigned int EN30:1;                    /**< \brief [30:30] Access Enable for Master TAG ID 30 (rw) */
    unsigned int EN31:1;                    /**< \brief [31:31] Access Enable for Master TAG ID 31 (rw) */
} Ifx_HSCT_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_HSCT_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_HSCT_ACCEN1_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_HSCT_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (r) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_HSCT_CLC_Bits;

/** \brief  Configuration physical layer register */
typedef struct _Ifx_HSCT_CONFIGPHY_Bits
{
    unsigned int reserved_0:1;              /**< \brief \internal Reserved */
    unsigned int PLLPON:1;                  /**< \brief [1:1] PLL Power On (Master Mode only) (rw) */
    unsigned int PLLPE:6;                   /**< \brief [7:2] PLL phase enable - allows to enable/disable each of the 6 Phase outputs. (rw) */
    unsigned int PLLWMF:6;                  /**< \brief [13:8] PLL frequency control word multiplication factor (rw) */
    unsigned int PLLKPKI:1;                 /**< \brief [14:14] KP/KI Setting (rw) */
    unsigned int PHYRST:1;                  /**< \brief [15:15] Physical Layer Reset (rw) */
    unsigned int PLLKP:3;                   /**< \brief [18:16] KP of PLL - Configuration of PLL beta coefficients of proportional part of loop filter (rw) */
    unsigned int PLLKI:3;                   /**< \brief [21:19] KI of PLL - Configuration of PLL alpha coefficients of integral part of loop filter (rw) */
    unsigned int PLLIVR:4;                  /**< \brief [25:22] Adjustment for integrated voltage regulator (rw) */
    unsigned int reserved_26:2;             /**< \brief \internal Reserved */
    unsigned int OSCCLKEN:1;                /**< \brief [28:28] Enable Oscillator Clock as PLL reference clock (rw) */
    unsigned int reserved_29:3;             /**< \brief \internal Reserved */
} Ifx_HSCT_CONFIGPHY_Bits;

/** \brief  Clear To Send Control Register */
typedef struct _Ifx_HSCT_CTSCTRL_Bits
{
    unsigned int CTS_FRAME:1;               /**< \brief [0:0] Transmit CTS Frame Generation (rw) */
    unsigned int CTS_TXD:1;                 /**< \brief [1:1] Disable TX CTS signaling (rw) */
    unsigned int CTS_RXD:1;                 /**< \brief [2:2] Disable RX CTS detection (rw) */
    unsigned int HSSL_CTS_FBD:1;            /**< \brief [3:3] Disable HSSL interface CTS Frame Blocking (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_HSCT_CTSCTRL_Bits;

/** \brief  Transmission Disable Register */
typedef struct _Ifx_HSCT_DISABLE_Bits
{
    unsigned int TX_DIS:1;                  /**< \brief [0:0] Disable HSCT Transmit path in Master interface (rw) */
    unsigned int RX_DIS:1;                  /**< \brief [1:1] Disable HSCT Receive path in Master interface (rw) */
    unsigned int RX_HEPD:1;                 /**< \brief [2:2] Disable RX Header Error Discard Payload data. (rw) */
    unsigned int reserved_3:29;             /**< \brief \internal Reserved */
} Ifx_HSCT_DISABLE_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_HSCT_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_HSCT_ID_Bits;

/** \brief  CPU transfer control register */
typedef struct _Ifx_HSCT_IFCTRL_Bits
{
    unsigned int IFCVS:8;                   /**< \brief [7:0] Master Mode - Interface Control Value to be send to Slave interface (rw) */
    unsigned int SIFCV:1;                   /**< \brief [8:8] Master Mode - Slave IF control frame trigger (w) */
    unsigned int reserved_9:7;              /**< \brief \internal Reserved */
    unsigned int MRXSPEED:2;                /**< \brief [17:16] Master Mode RX speed (rw) */
    unsigned int MTXSPEED:2;                /**< \brief [19:18] Master Mode TX speed (rw) */
    unsigned int IFTESTMD:1;                /**< \brief [20:20] Master Mode Interface Test Mode (rw) */
    unsigned int reserved_21:11;            /**< \brief \internal Reserved */
} Ifx_HSCT_IFCTRL_Bits;

/** \brief  Interface Status Register */
typedef struct _Ifx_HSCT_IFSTAT_Bits
{
    unsigned int RX_STAT:3;                 /**< \brief [2:0] HSCT slave interface Status for RX link (rh) */
    unsigned int TX_STAT:2;                 /**< \brief [4:3] HSCT slave interface Status for TX link (rh) */
    unsigned int reserved_5:27;             /**< \brief \internal Reserved */
} Ifx_HSCT_IFSTAT_Bits;

/** \brief  Initialization register */
typedef struct _Ifx_HSCT_INIT_Bits
{
    unsigned int reserved_0:1;              /**< \brief \internal Reserved */
    unsigned int SYS_CLK_EN:1;              /**< \brief [1:1] Enable SysClk in Master interface (rw) */
    unsigned int SRCF:1;                    /**< \brief [2:2] Select SysClk / Reference Clock Frequency rate (rw) */
    unsigned int IFM:1;                     /**< \brief [3:3] Select Interface Mode (rw) */
    unsigned int reserved_4:6;              /**< \brief \internal Reserved */
    unsigned int LHLR:1;                    /**< \brief [10:10] Loopback path at Slave interface side at higher layer system RAM. (rw) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int TXHD:3;                    /**< \brief [18:16] Transmit High Speed Divider. (rw) */
    unsigned int RXHD:3;                    /**< \brief [21:19] Receive High Speed Divider. (rw) */
    unsigned int reserved_22:10;            /**< \brief \internal Reserved */
} Ifx_HSCT_INIT_Bits;

/** \brief  Interrupt register */
typedef struct _Ifx_HSCT_IRQ_Bits
{
    unsigned int reserved_0:1;              /**< \brief \internal Reserved */
    unsigned int HER:1;                     /**< \brief [1:1] Header error detected (rh) */
    unsigned int PYER:1;                    /**< \brief [2:2] Payload error detected (rh) */
    unsigned int CER:1;                     /**< \brief [3:3] HSCT command error (rh) */
    unsigned int IFCFS:1;                   /**< \brief [4:4] HSCT interface control frame send (rh) */
    unsigned int SMER:1;                    /**< \brief [5:5] Speed Mode Switch Error (Master Mode only) (rh) */
    unsigned int USMSF:1;                   /**< \brief [6:6] Unsolicited message frame send finished (rh) */
    unsigned int PLER:1;                    /**< \brief [7:7] PLL lost lock error (rh) */
    unsigned int USM:1;                     /**< \brief [8:8] Unsolicited Message Received (rh) */
    unsigned int PAR:1;                     /**< \brief [9:9] PING Answer Received (rh) */
    unsigned int TXTE:1;                    /**< \brief [10:10] TX transfer error occurred on a disabled TX channel. (rh) */
    unsigned int SFO:1;                     /**< \brief [11:11] Synchronization FIFO overflow (in RX direction) (rh) */
    unsigned int SFU:1;                     /**< \brief [12:12] Synchronization FIFO underflow (in TX direction) (rh) */
    unsigned int reserved_13:19;            /**< \brief \internal Reserved */
} Ifx_HSCT_IRQ_Bits;

/** \brief  Interrupt clear register */
typedef struct _Ifx_HSCT_IRQCLR_Bits
{
    unsigned int reserved_0:1;              /**< \brief \internal Reserved */
    unsigned int HERCLR:1;                  /**< \brief [1:1] Header error detected interrupt clear (w) */
    unsigned int PYERCLR:1;                 /**< \brief [2:2] Payload error detected interrupt clear (w) */
    unsigned int CERCLR:1;                  /**< \brief [3:3] HSCT command error interrupt clear (w) */
    unsigned int IFCFSCLR:1;                /**< \brief [4:4] HSCT interface control command send interrupt clear (w) */
    unsigned int SMERCLR:1;                 /**< \brief [5:5] Speed Mode Switch Error interrupt clear (w) */
    unsigned int USMSFCLR:1;                /**< \brief [6:6] Unsolicited message frame send finished interrupt clear (w) */
    unsigned int PLERCLR:1;                 /**< \brief [7:7] PLL lost lock error interrupt clear (w) */
    unsigned int USMCLR:1;                  /**< \brief [8:8] Unsolicited Message received clear (w) */
    unsigned int PARCLR:1;                  /**< \brief [9:9] PING Answer received clear (w) */
    unsigned int TXTECLR:1;                 /**< \brief [10:10] TX disable error interrupt clear (w) */
    unsigned int SFOCLR:1;                  /**< \brief [11:11] Synchronization FIFO overflow (in RX direction) interrupt clear (w) */
    unsigned int SFUCLR:1;                  /**< \brief [12:12] Synchronization FIFO underflow (in TX direction) interrupt clear (w) */
    unsigned int reserved_13:19;            /**< \brief \internal Reserved */
} Ifx_HSCT_IRQCLR_Bits;

/** \brief  Interrupt enable register */
typedef struct _Ifx_HSCT_IRQEN_Bits
{
    unsigned int reserved_0:1;              /**< \brief \internal Reserved */
    unsigned int HEREN:1;                   /**< \brief [1:1] Header error detected interrupt enable (rw) */
    unsigned int PYEREN:1;                  /**< \brief [2:2] Payload error detected interrupt enable (rw) */
    unsigned int CEREN:1;                   /**< \brief [3:3] HSCT command error interrupt enable (rw) */
    unsigned int IFCFSEN:1;                 /**< \brief [4:4] HSCT interface control command send enable (rw) */
    unsigned int SMEREN:1;                  /**< \brief [5:5] Speed Mode Switch Error interrupt enable (rw) */
    unsigned int USMSFEN:1;                 /**< \brief [6:6] Unsolicited message frame send finished (rw) */
    unsigned int PLEREN:1;                  /**< \brief [7:7] PLL lost lock error interrupt enable (rw) */
    unsigned int USMEN:1;                   /**< \brief [8:8] Unsolicited Message received enable (rw) */
    unsigned int PAREN:1;                   /**< \brief [9:9] PING Answer Received enable (rw) */
    unsigned int TXTEEN:1;                  /**< \brief [10:10] TX disable error interrupt enable (rw) */
    unsigned int SFOEN:1;                   /**< \brief [11:11] Synchronization FIFO overflow (in RX direction) interrupt enable (rw) */
    unsigned int SFUEN:1;                   /**< \brief [12:12] Synchronization FIFO underflow (in TX direction) interrupt enable (rw) */
    unsigned int reserved_13:19;            /**< \brief \internal Reserved */
} Ifx_HSCT_IRQEN_Bits;

/** \brief  Reset Register 0 */
typedef struct _Ifx_HSCT_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_HSCT_KRST0_Bits;

/** \brief  Reset Register 1 */
typedef struct _Ifx_HSCT_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_HSCT_KRST1_Bits;

/** \brief  Reset Status Clear Register */
typedef struct _Ifx_HSCT_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_HSCT_KRSTCLR_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_HSCT_OCS_Bits
{
    unsigned int TGS:2;                     /**< \brief [1:0] Trigger Set for OTGB0/1 (rw) */
    unsigned int TGB:1;                     /**< \brief [2:2] OTGB0/1 Bus Select (rw) */
    unsigned int TG_P:1;                    /**< \brief [3:3] TGS, TGB Write Protection (w) */
    unsigned int reserved_4:20;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_HSCT_OCS_Bits;

/** \brief  Sleep Control Register */
typedef struct _Ifx_HSCT_SLEEPCTRL_Bits
{
    unsigned int SLPEN:1;                   /**< \brief [0:0] Sleep mode enabled (rw) */
    unsigned int SLPCLKG:1;                 /**< \brief [1:1] Clock Gating in Sleep Mode (rw) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_HSCT_SLEEPCTRL_Bits;

/** \brief  Status Register */
typedef struct _Ifx_HSCT_STAT_Bits
{
    unsigned int RX_PSIZE:3;                /**< \brief [2:0] RX (receiving) Payload Size (rh) */
    unsigned int RX_CHANNEL:4;              /**< \brief [6:3] RX (receiving) Logical Channel Type (rh) */
    unsigned int RX_SLEEP:1;                /**< \brief [7:7] RX (receiving) Sleep Mode Status (rh) */
    unsigned int TX_SLEEP:1;                /**< \brief [8:8] TX (transmitting) Sleep Mode Status (rh) */
    unsigned int reserved_9:3;              /**< \brief \internal Reserved */
    unsigned int TX_PSIZE:3;                /**< \brief [14:12] Transmission Payload Size (rh) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int TX_CHANNEL_TYPE:4;         /**< \brief [19:16] Transmission Logical Channel Type (rh) */
    unsigned int reserved_20:4;             /**< \brief \internal Reserved */
    unsigned int LIFCCMDR:8;                /**< \brief [31:24] Last Interface Control Command Received (rh) */
} Ifx_HSCT_STAT_Bits;

/** \brief  STATPHY */
typedef struct _Ifx_HSCT_STATPHY_Bits
{
    unsigned int PLOCK:1;                   /**< \brief [0:0] PLL locked (rh) */
    unsigned int RXLSA:1;                   /**< \brief [1:1] Receiver in Low speed (rh) */
    unsigned int TXLSA:1;                   /**< \brief [2:2] Transmitter in Low speed (rh) */
    unsigned int reserved_3:29;             /**< \brief \internal Reserved */
} Ifx_HSCT_STATPHY_Bits;

/** \brief  Unsolicited Status Message Received */
typedef struct _Ifx_HSCT_USMR_Bits
{
    unsigned int USMR:32;                   /**< \brief [31:0] Unsolicited status message received (rh) */
} Ifx_HSCT_USMR_Bits;

/** \brief  Unsolicited Status Message Send */
typedef struct _Ifx_HSCT_USMS_Bits
{
    unsigned int USMS:32;                   /**< \brief [31:0] Unsolicited status message send (rw) */
} Ifx_HSCT_USMS_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Hsct_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_ACCEN0_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSCT_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_ACCEN1_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSCT_ACCEN1;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_CLC_Bits B;                    /**< \brief Bitfield access */
} Ifx_HSCT_CLC;

/** \brief  Configuration physical layer register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_CONFIGPHY_Bits B;              /**< \brief Bitfield access */
} Ifx_HSCT_CONFIGPHY;

/** \brief  Clear To Send Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_CTSCTRL_Bits B;                /**< \brief Bitfield access */
} Ifx_HSCT_CTSCTRL;

/** \brief  Transmission Disable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_DISABLE_Bits B;                /**< \brief Bitfield access */
} Ifx_HSCT_DISABLE;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_ID_Bits B;                     /**< \brief Bitfield access */
} Ifx_HSCT_ID;

/** \brief  CPU transfer control register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_IFCTRL_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSCT_IFCTRL;

/** \brief  Interface Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_IFSTAT_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSCT_IFSTAT;

/** \brief  Initialization register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_INIT_Bits B;                   /**< \brief Bitfield access */
} Ifx_HSCT_INIT;

/** \brief  Interrupt register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_IRQ_Bits B;                    /**< \brief Bitfield access */
} Ifx_HSCT_IRQ;

/** \brief  Interrupt clear register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_IRQCLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSCT_IRQCLR;

/** \brief  Interrupt enable register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_IRQEN_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSCT_IRQEN;

/** \brief  Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_KRST0_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSCT_KRST0;

/** \brief  Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_KRST1_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSCT_KRST1;

/** \brief  Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_KRSTCLR_Bits B;                /**< \brief Bitfield access */
} Ifx_HSCT_KRSTCLR;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_OCS_Bits B;                    /**< \brief Bitfield access */
} Ifx_HSCT_OCS;

/** \brief  Sleep Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_SLEEPCTRL_Bits B;              /**< \brief Bitfield access */
} Ifx_HSCT_SLEEPCTRL;

/** \brief  Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_STAT_Bits B;                   /**< \brief Bitfield access */
} Ifx_HSCT_STAT;

/** \brief  STATPHY */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_STATPHY_Bits B;                /**< \brief Bitfield access */
} Ifx_HSCT_STATPHY;

/** \brief  Unsolicited Status Message Received */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_USMR_Bits B;                   /**< \brief Bitfield access */
} Ifx_HSCT_USMR;

/** \brief  Unsolicited Status Message Send */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSCT_USMS_Bits B;                   /**< \brief Bitfield access */
} Ifx_HSCT_USMS;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Hsct_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  HSCT object */
typedef volatile struct _Ifx_HSCT
{
    Ifx_HSCT_CLC CLC;                       /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_HSCT_ID ID;                         /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_HSCT_INIT INIT;                     /**< \brief 10, Initialization register */
    Ifx_HSCT_IFCTRL IFCTRL;                 /**< \brief 14, CPU transfer control register */
    Ifx_HSCT_SLEEPCTRL SLEEPCTRL;           /**< \brief 18, Sleep Control Register */
    Ifx_HSCT_CTSCTRL CTSCTRL;               /**< \brief 1C, Clear To Send Control Register */
    Ifx_HSCT_DISABLE DISABLE;               /**< \brief 20, Transmission Disable Register */
    Ifx_HSCT_STAT STAT;                     /**< \brief 24, Status Register */
    Ifx_HSCT_IFSTAT IFSTAT;                 /**< \brief 28, Interface Status Register */
    unsigned char reserved_2C[4];           /**< \brief 2C, \internal Reserved */
    Ifx_HSCT_CONFIGPHY CONFIGPHY;           /**< \brief 30, Configuration physical layer register */
    Ifx_HSCT_STATPHY STATPHY;               /**< \brief 34, STATPHY */
    unsigned char reserved_38[8];           /**< \brief 38, \internal Reserved */
    Ifx_HSCT_IRQ IRQ;                       /**< \brief 40, Interrupt register */
    Ifx_HSCT_IRQEN IRQEN;                   /**< \brief 44, Interrupt enable register */
    Ifx_HSCT_IRQCLR IRQCLR;                 /**< \brief 48, Interrupt clear register */
    unsigned char reserved_4C[4];           /**< \brief 4C, \internal Reserved */
    Ifx_HSCT_USMR USMR;                     /**< \brief 50, Unsolicited Status Message Received */
    Ifx_HSCT_USMS USMS;                     /**< \brief 54, Unsolicited Status Message Send */
    unsigned char reserved_58[65424];       /**< \brief 58, \internal Reserved */
    Ifx_HSCT_OCS OCS;                       /**< \brief FFE8, OCDS Control and Status */
    Ifx_HSCT_KRSTCLR KRSTCLR;               /**< \brief FFEC, Reset Status Clear Register */
    Ifx_HSCT_KRST1 KRST1;                   /**< \brief FFF0, Reset Register 1 */
    Ifx_HSCT_KRST0 KRST0;                   /**< \brief FFF4, Reset Register 0 */
    Ifx_HSCT_ACCEN1 ACCEN1;                 /**< \brief FFF8, Access Enable Register 1 */
    Ifx_HSCT_ACCEN0 ACCEN0;                 /**< \brief FFFC, Access Enable Register 0 */
} Ifx_HSCT;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXHSCT_REGDEF_H */
