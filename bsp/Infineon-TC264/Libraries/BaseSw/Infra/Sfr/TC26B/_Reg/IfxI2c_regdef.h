/**
 * \file IfxI2c_regdef.h
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
 * \defgroup IfxLld_I2c I2c
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_I2c_Bitfields Bitfields
 * \ingroup IfxLld_I2c
 * 
 * \defgroup IfxLld_I2c_union Union
 * \ingroup IfxLld_I2c
 * 
 * \defgroup IfxLld_I2c_struct Struct
 * \ingroup IfxLld_I2c
 * 
 */
#ifndef IFXI2C_REGDEF_H
#define IFXI2C_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_I2c_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_I2C_ACCEN0_Bits
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
} Ifx_I2C_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_I2C_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_I2C_ACCEN1_Bits;

/** \brief  Address Configuration Register */
typedef struct _Ifx_I2C_ADDRCFG_Bits
{
    unsigned int ADR:10;                    /**< \brief [9:0] I2C-bus Device Address (rw) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int TBAM:1;                    /**< \brief [16:16] Ten Bit Address Mode (rw) */
    unsigned int GCE:1;                     /**< \brief [17:17] General Call Enable (rw) */
    unsigned int MCE:1;                     /**< \brief [18:18] Master Code Enable (rw) */
    unsigned int MnS:1;                     /**< \brief [19:19] Master / not Slave (rw) */
    unsigned int SONA:1;                    /**< \brief [20:20] Stop on Not-acknowledge (rw) */
    unsigned int SOPE:1;                    /**< \brief [21:21] Stop on Packet End (rw) */
    unsigned int reserved_22:10;            /**< \brief \internal Reserved */
} Ifx_I2C_ADDRCFG_Bits;

/** \brief  Bus Status Register */
typedef struct _Ifx_I2C_BUSSTAT_Bits
{
    unsigned int BS:2;                      /**< \brief [1:0] Bus Status (rh) */
    unsigned int RnW:1;                     /**< \brief [2:2] Read/not Write (rh) */
    unsigned int reserved_3:29;             /**< \brief \internal Reserved */
} Ifx_I2C_BUSSTAT_Bits;

/** \brief  Clock Control 1 Register */
typedef struct _Ifx_I2C_CLC1_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int SPEN:1;                    /**< \brief [2:2] Module Suspend Enable Bit for OCDS (rw) */
    unsigned int EDIS:1;                    /**< \brief [3:3] External Request Disable (rw) */
    unsigned int SBWE:1;                    /**< \brief [4:4] Module Suspend Bit Write Enable for OCDS (w) */
    unsigned int FSOE:1;                    /**< \brief [5:5] Fast Switch Off Enable (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int RMC:8;                     /**< \brief [15:8] Clock Divider for Standard Run Mode (rwh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_I2C_CLC1_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_I2C_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_I2C_CLC_Bits;

/** \brief  End Data Control Register */
typedef struct _Ifx_I2C_ENDDCTRL_Bits
{
    unsigned int SETRSC:1;                  /**< \brief [0:0] Set Restart Condition (w) */
    unsigned int SETEND:1;                  /**< \brief [1:1] Set End of Transmission (w) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_I2C_ENDDCTRL_Bits;

/** \brief  Error Interrupt Request Source Clear Register */
typedef struct _Ifx_I2C_ERRIRQSC_Bits
{
    unsigned int RXF_UFL:1;                 /**< \brief [0:0] RX FIFO Underflow (w) */
    unsigned int RXF_OFL:1;                 /**< \brief [1:1] RX FIFO Overflow (w) */
    unsigned int TXF_UFL:1;                 /**< \brief [2:2] TX FIFO Underflow (w) */
    unsigned int TXF_OFL:1;                 /**< \brief [3:3] TX FIFO Overflow (w) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_I2C_ERRIRQSC_Bits;

/** \brief  Error Interrupt Request Source Mask Register */
typedef struct _Ifx_I2C_ERRIRQSM_Bits
{
    unsigned int RXF_UFL:1;                 /**< \brief [0:0] RX FIFO Underflow (rw) */
    unsigned int RXF_OFL:1;                 /**< \brief [1:1] RX FIFO Overflow (rw) */
    unsigned int TXF_UFL:1;                 /**< \brief [2:2] TX FIFO Underflow (rw) */
    unsigned int TXF_OFL:1;                 /**< \brief [3:3] TX FIFO Overflow (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_I2C_ERRIRQSM_Bits;

/** \brief  Error Interrupt Request Source Status Register */
typedef struct _Ifx_I2C_ERRIRQSS_Bits
{
    unsigned int RXF_UFL:1;                 /**< \brief [0:0] RX FIFO Underflow (rh) */
    unsigned int RXF_OFL:1;                 /**< \brief [1:1] RX FIFO Overflow (rh) */
    unsigned int TXF_UFL:1;                 /**< \brief [2:2] TX FIFO Underflow (rh) */
    unsigned int TXF_OFL:1;                 /**< \brief [3:3] TX FIFO Overflow (rh) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_I2C_ERRIRQSS_Bits;

/** \brief  Fractional Divider Configuration Register */
typedef struct _Ifx_I2C_FDIVCFG_Bits
{
    unsigned int DEC:11;                    /**< \brief [10:0] Decrement Value of Fractional Divider (rw) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int INC:8;                     /**< \brief [23:16] Increment Value of Fractional Divider (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_I2C_FDIVCFG_Bits;

/** \brief  Fractional Divider High-speed Mode Configuration Register */
typedef struct _Ifx_I2C_FDIVHIGHCFG_Bits
{
    unsigned int DEC:11;                    /**< \brief [10:0] Decrement Value of Fractional Divider (rw) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int INC:8;                     /**< \brief [23:16] Increment Value of Fractional Divider (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_I2C_FDIVHIGHCFG_Bits;

/** \brief  Filled FIFO Stages Status Register */
typedef struct _Ifx_I2C_FFSSTAT_Bits
{
    unsigned int FFS:6;                     /**< \brief [5:0] Filled FIFO Stages (rh) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_I2C_FFSSTAT_Bits;

/** \brief  FIFO Configuration Register */
typedef struct _Ifx_I2C_FIFOCFG_Bits
{
    unsigned int RXBS:2;                    /**< \brief [1:0] RX Burst Size (rw) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int TXBS:2;                    /**< \brief [5:4] TX Burst Size (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int RXFA:2;                    /**< \brief [9:8] RX FIFO Alignment (rw) */
    unsigned int reserved_10:2;             /**< \brief \internal Reserved */
    unsigned int TXFA:2;                    /**< \brief [13:12] TX FIFO Alignment (rw) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int RXFC:1;                    /**< \brief [16:16] RX FIFO Flow Control (rw) */
    unsigned int TXFC:1;                    /**< \brief [17:17] TX FIFO Flow Control (rw) */
    unsigned int reserved_18:14;            /**< \brief \internal Reserved */
} Ifx_I2C_FIFOCFG_Bits;

/** \brief  General Purpose Control Register */
typedef struct _Ifx_I2C_GPCTL_Bits
{
    unsigned int PISEL:3;                   /**< \brief [2:0] Port Input Select (rw) */
    unsigned int reserved_3:29;             /**< \brief \internal Reserved */
} Ifx_I2C_GPCTL_Bits;

/** \brief  Interrupt Clear Register */
typedef struct _Ifx_I2C_ICR_Bits
{
    unsigned int LSREQ_INT:1;               /**< \brief [0:0] Last Single Request Interrupt (w) */
    unsigned int SREQ_INT:1;                /**< \brief [1:1] Single Request Interrupt (w) */
    unsigned int LBREQ_INT:1;               /**< \brief [2:2] Last Burst Request Interrupt (w) */
    unsigned int BREQ_INT:1;                /**< \brief [3:3] Burst Request Interrupt (w) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_I2C_ICR_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_I2C_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODNUMBER:8;               /**< \brief [15:8] Module Number Value (r) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_I2C_ID_Bits;

/** \brief  Interrupt Mask Control Register */
typedef struct _Ifx_I2C_IMSC_Bits
{
    unsigned int LSREQ_INT:1;               /**< \brief [0:0] Last Single Request Interrupt (rw) */
    unsigned int SREQ_INT:1;                /**< \brief [1:1] Single Request Interrupt (rw) */
    unsigned int LBREQ_INT:1;               /**< \brief [2:2] Last Burst Request Interrupt (rw) */
    unsigned int BREQ_INT:1;                /**< \brief [3:3] Burst Request Interrupt (rw) */
    unsigned int I2C_ERR_INT:1;             /**< \brief [4:4] I2C Error Interrupt (rw) */
    unsigned int I2C_P_INT:1;               /**< \brief [5:5] I2C Protocol Interrupt (rw) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_I2C_IMSC_Bits;

/** \brief  Interrupt Set Register */
typedef struct _Ifx_I2C_ISR_Bits
{
    unsigned int LSREQ_INT:1;               /**< \brief [0:0] Last Single Request Interrupt (w) */
    unsigned int SREQ_INT:1;                /**< \brief [1:1] Single Request Interrupt (w) */
    unsigned int LBREQ_INT:1;               /**< \brief [2:2] Last Burst Request Interrupt (w) */
    unsigned int BREQ_INT:1;                /**< \brief [3:3] Burst Request Interrupt (w) */
    unsigned int I2C_ERR_INT:1;             /**< \brief [4:4] I2C Error Interrupt (w) */
    unsigned int I2C_P_INT:1;               /**< \brief [5:5] I2C Protocol Interrupt (w) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_I2C_ISR_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_I2C_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_I2C_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_I2C_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_I2C_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_I2C_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_I2C_KRSTCLR_Bits;

/** \brief  Masked Interrupt Status Register */
typedef struct _Ifx_I2C_MIS_Bits
{
    unsigned int LSREQ_INT:1;               /**< \brief [0:0] Last Single Request Interrupt (rh) */
    unsigned int SREQ_INT:1;                /**< \brief [1:1] Single Request Interrupt (rh) */
    unsigned int LBREQ_INT:1;               /**< \brief [2:2] Last Burst Request Interrupt (rh) */
    unsigned int BREQ_INT:1;                /**< \brief [3:3] Burst Request Interrupt (rh) */
    unsigned int I2C_ERR_INT:1;             /**< \brief [4:4] I2C Error Interrupt (rh) */
    unsigned int I2C_P_INT:1;               /**< \brief [5:5] I2C Protocol Interrupt (rh) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_I2C_MIS_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_I2C_MODID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_I2C_MODID_Bits;

/** \brief  Maximum Received Packet Size Control Register */
typedef struct _Ifx_I2C_MRPSCTRL_Bits
{
    unsigned int MRPS:14;                   /**< \brief [13:0] Maximum Received Packet Size (rwh) */
    unsigned int reserved_14:18;            /**< \brief \internal Reserved */
} Ifx_I2C_MRPSCTRL_Bits;

/** \brief  Protocol Interrupt Request Source Clear Register */
typedef struct _Ifx_I2C_PIRQSC_Bits
{
    unsigned int AM:1;                      /**< \brief [0:0] Address Match (w) */
    unsigned int GC:1;                      /**< \brief [1:1] General Call (w) */
    unsigned int MC:1;                      /**< \brief [2:2] Master Code (w) */
    unsigned int AL:1;                      /**< \brief [3:3] Arbitration Lost (w) */
    unsigned int NACK:1;                    /**< \brief [4:4] Not-acknowledge Received (w) */
    unsigned int TX_END:1;                  /**< \brief [5:5] Transmission End (w) */
    unsigned int RX:1;                      /**< \brief [6:6] Receive Mode (w) */
    unsigned int reserved_7:25;             /**< \brief \internal Reserved */
} Ifx_I2C_PIRQSC_Bits;

/** \brief  Protocol Interrupt Request Source Mask Register */
typedef struct _Ifx_I2C_PIRQSM_Bits
{
    unsigned int AM:1;                      /**< \brief [0:0] Address Match (rw) */
    unsigned int GC:1;                      /**< \brief [1:1] General Call (rw) */
    unsigned int MC:1;                      /**< \brief [2:2] Master Code (rw) */
    unsigned int AL:1;                      /**< \brief [3:3] Arbitration Lost (rw) */
    unsigned int NACK:1;                    /**< \brief [4:4] Not-acknowledge Received (rw) */
    unsigned int TX_END:1;                  /**< \brief [5:5] Transmission End (rw) */
    unsigned int RX:1;                      /**< \brief [6:6] Receive Mode (rw) */
    unsigned int reserved_7:25;             /**< \brief \internal Reserved */
} Ifx_I2C_PIRQSM_Bits;

/** \brief  Protocol Interrupt Request Source Status Register */
typedef struct _Ifx_I2C_PIRQSS_Bits
{
    unsigned int AM:1;                      /**< \brief [0:0] Address Match (rh) */
    unsigned int GC:1;                      /**< \brief [1:1] General Call (rh) */
    unsigned int MC:1;                      /**< \brief [2:2] Master Code (rh) */
    unsigned int AL:1;                      /**< \brief [3:3] Arbitration Lost (rh) */
    unsigned int NACK:1;                    /**< \brief [4:4] Not-acknowledge Received (rh) */
    unsigned int TX_END:1;                  /**< \brief [5:5] Transmission End (rh) */
    unsigned int RX:1;                      /**< \brief [6:6] Receive Mode (rh) */
    unsigned int reserved_7:25;             /**< \brief \internal Reserved */
} Ifx_I2C_PIRQSS_Bits;

/** \brief  Raw Interrupt Status Register */
typedef struct _Ifx_I2C_RIS_Bits
{
    unsigned int LSREQ_INT:1;               /**< \brief [0:0] Last Single Request Interrupt (rh) */
    unsigned int SREQ_INT:1;                /**< \brief [1:1] Single Request Interrupt (rh) */
    unsigned int LBREQ_INT:1;               /**< \brief [2:2] Last Burst Request Interrupt (rh) */
    unsigned int BREQ_INT:1;                /**< \brief [3:3] Burst Request Interrupt (rh) */
    unsigned int I2C_ERR_INT:1;             /**< \brief [4:4] I2C Error Interrupt (rh) */
    unsigned int I2C_P_INT:1;               /**< \brief [5:5] I2C Protocol Interrupt (rh) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_I2C_RIS_Bits;

/** \brief  Received Packet Size Status Register */
typedef struct _Ifx_I2C_RPSSTAT_Bits
{
    unsigned int RPS:14;                    /**< \brief [13:0] Received Packet Size (rh) */
    unsigned int reserved_14:18;            /**< \brief \internal Reserved */
} Ifx_I2C_RPSSTAT_Bits;

/** \brief  RUN Control Register */
typedef struct _Ifx_I2C_RUNCTRL_Bits
{
    unsigned int RUN:1;                     /**< \brief [0:0] Enable I2C-bus Interface (rw) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_I2C_RUNCTRL_Bits;

/** \brief  Reception Data Register */
typedef struct _Ifx_I2C_RXD_Bits
{
    unsigned int RXD:32;                    /**< \brief [31:0] Reception Data (rh) */
} Ifx_I2C_RXD_Bits;

/** \brief  Timing Configuration Register */
typedef struct _Ifx_I2C_TIMCFG_Bits
{
    unsigned int SDA_DEL_HD_DAT:6;          /**< \brief [5:0] SDA Delay Stages for Data Hold Time (rw) */
    unsigned int HS_SDA_DEL_HD_DAT:3;       /**< \brief [8:6] SDA Delay Stages for Data Hold Time in High-speed Mode (rw) */
    unsigned int SCL_DEL_HD_STA:3;          /**< \brief [11:9] SCL Delay Stages for Hold Time Start (Restart) Bit (rw) */
    unsigned int reserved_12:2;             /**< \brief \internal Reserved */
    unsigned int EN_SCL_LOW_LEN:1;          /**< \brief [14:14] Enable Direct Configuration of SCL Low Period Length in Fast Mode (rw) */
    unsigned int FS_SCL_LOW:1;              /**< \brief [15:15] Set Fast Mode SCL Low Period Timing (rw) */
    unsigned int HS_SDA_DEL:3;              /**< \brief [18:16] SDA Delay Stages for Start/Stop bit in High-speed Mode (rw) */
    unsigned int reserved_19:5;             /**< \brief \internal Reserved */
    unsigned int SCL_LOW_LEN:8;             /**< \brief [31:24] SCL Low Length in Fast Mode (rw) */
} Ifx_I2C_TIMCFG_Bits;

/** \brief  Transmit Packet Size Control Register */
typedef struct _Ifx_I2C_TPSCTRL_Bits
{
    unsigned int TPS:14;                    /**< \brief [13:0] Transmit Packet Size (rwh) */
    unsigned int reserved_14:18;            /**< \brief \internal Reserved */
} Ifx_I2C_TPSCTRL_Bits;

/** \brief  Transmission Data Register */
typedef struct _Ifx_I2C_TXD_Bits
{
    unsigned int TXD:32;                    /**< \brief [31:0] Transmission Data (rw) */
} Ifx_I2C_TXD_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_I2c_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_ACCEN0_Bits B;                  /**< \brief Bitfield access */
} Ifx_I2C_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_ACCEN1_Bits B;                  /**< \brief Bitfield access */
} Ifx_I2C_ACCEN1;

/** \brief  Address Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_ADDRCFG_Bits B;                 /**< \brief Bitfield access */
} Ifx_I2C_ADDRCFG;

/** \brief  Bus Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_BUSSTAT_Bits B;                 /**< \brief Bitfield access */
} Ifx_I2C_BUSSTAT;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_I2C_CLC;

/** \brief  Clock Control 1 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_CLC1_Bits B;                    /**< \brief Bitfield access */
} Ifx_I2C_CLC1;

/** \brief  End Data Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_ENDDCTRL_Bits B;                /**< \brief Bitfield access */
} Ifx_I2C_ENDDCTRL;

/** \brief  Error Interrupt Request Source Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_ERRIRQSC_Bits B;                /**< \brief Bitfield access */
} Ifx_I2C_ERRIRQSC;

/** \brief  Error Interrupt Request Source Mask Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_ERRIRQSM_Bits B;                /**< \brief Bitfield access */
} Ifx_I2C_ERRIRQSM;

/** \brief  Error Interrupt Request Source Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_ERRIRQSS_Bits B;                /**< \brief Bitfield access */
} Ifx_I2C_ERRIRQSS;

/** \brief  Fractional Divider Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_FDIVCFG_Bits B;                 /**< \brief Bitfield access */
} Ifx_I2C_FDIVCFG;

/** \brief  Fractional Divider High-speed Mode Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_FDIVHIGHCFG_Bits B;             /**< \brief Bitfield access */
} Ifx_I2C_FDIVHIGHCFG;

/** \brief  Filled FIFO Stages Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_FFSSTAT_Bits B;                 /**< \brief Bitfield access */
} Ifx_I2C_FFSSTAT;

/** \brief  FIFO Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_FIFOCFG_Bits B;                 /**< \brief Bitfield access */
} Ifx_I2C_FIFOCFG;

/** \brief  General Purpose Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_GPCTL_Bits B;                   /**< \brief Bitfield access */
} Ifx_I2C_GPCTL;

/** \brief  Interrupt Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_ICR_Bits B;                     /**< \brief Bitfield access */
} Ifx_I2C_ICR;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_I2C_ID;

/** \brief  Interrupt Mask Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_IMSC_Bits B;                    /**< \brief Bitfield access */
} Ifx_I2C_IMSC;

/** \brief  Interrupt Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_ISR_Bits B;                     /**< \brief Bitfield access */
} Ifx_I2C_ISR;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_KRST0_Bits B;                   /**< \brief Bitfield access */
} Ifx_I2C_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_KRST1_Bits B;                   /**< \brief Bitfield access */
} Ifx_I2C_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_KRSTCLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_I2C_KRSTCLR;

/** \brief  Masked Interrupt Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_MIS_Bits B;                     /**< \brief Bitfield access */
} Ifx_I2C_MIS;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_MODID_Bits B;                   /**< \brief Bitfield access */
} Ifx_I2C_MODID;

/** \brief  Maximum Received Packet Size Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_MRPSCTRL_Bits B;                /**< \brief Bitfield access */
} Ifx_I2C_MRPSCTRL;

/** \brief  Protocol Interrupt Request Source Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_PIRQSC_Bits B;                  /**< \brief Bitfield access */
} Ifx_I2C_PIRQSC;

/** \brief  Protocol Interrupt Request Source Mask Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_PIRQSM_Bits B;                  /**< \brief Bitfield access */
} Ifx_I2C_PIRQSM;

/** \brief  Protocol Interrupt Request Source Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_PIRQSS_Bits B;                  /**< \brief Bitfield access */
} Ifx_I2C_PIRQSS;

/** \brief  Raw Interrupt Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_RIS_Bits B;                     /**< \brief Bitfield access */
} Ifx_I2C_RIS;

/** \brief  Received Packet Size Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_RPSSTAT_Bits B;                 /**< \brief Bitfield access */
} Ifx_I2C_RPSSTAT;

/** \brief  RUN Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_RUNCTRL_Bits B;                 /**< \brief Bitfield access */
} Ifx_I2C_RUNCTRL;

/** \brief  Reception Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_RXD_Bits B;                     /**< \brief Bitfield access */
} Ifx_I2C_RXD;

/** \brief  Timing Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_TIMCFG_Bits B;                  /**< \brief Bitfield access */
} Ifx_I2C_TIMCFG;

/** \brief  Transmit Packet Size Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_TPSCTRL_Bits B;                 /**< \brief Bitfield access */
} Ifx_I2C_TPSCTRL;

/** \brief  Transmission Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_I2C_TXD_Bits B;                     /**< \brief Bitfield access */
} Ifx_I2C_TXD;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_I2c_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  I2C object */
typedef volatile struct _Ifx_I2C
{
    Ifx_I2C_CLC1 CLC1;                      /**< \brief 0, Clock Control 1 Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_I2C_ID ID;                          /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_I2C_RUNCTRL RUNCTRL;                /**< \brief 10, RUN Control Register */
    Ifx_I2C_ENDDCTRL ENDDCTRL;              /**< \brief 14, End Data Control Register */
    Ifx_I2C_FDIVCFG FDIVCFG;                /**< \brief 18, Fractional Divider Configuration Register */
    Ifx_I2C_FDIVHIGHCFG FDIVHIGHCFG;        /**< \brief 1C, Fractional Divider High-speed Mode Configuration Register */
    Ifx_I2C_ADDRCFG ADDRCFG;                /**< \brief 20, Address Configuration Register */
    Ifx_I2C_BUSSTAT BUSSTAT;                /**< \brief 24, Bus Status Register */
    Ifx_I2C_FIFOCFG FIFOCFG;                /**< \brief 28, FIFO Configuration Register */
    Ifx_I2C_MRPSCTRL MRPSCTRL;              /**< \brief 2C, Maximum Received Packet Size Control Register */
    Ifx_I2C_RPSSTAT RPSSTAT;                /**< \brief 30, Received Packet Size Status Register */
    Ifx_I2C_TPSCTRL TPSCTRL;                /**< \brief 34, Transmit Packet Size Control Register */
    Ifx_I2C_FFSSTAT FFSSTAT;                /**< \brief 38, Filled FIFO Stages Status Register */
    unsigned char reserved_3C[4];           /**< \brief 3C, \internal Reserved */
    Ifx_I2C_TIMCFG TIMCFG;                  /**< \brief 40, Timing Configuration Register */
    unsigned char reserved_44[28];          /**< \brief 44, \internal Reserved */
    Ifx_I2C_ERRIRQSM ERRIRQSM;              /**< \brief 60, Error Interrupt Request Source Mask Register */
    Ifx_I2C_ERRIRQSS ERRIRQSS;              /**< \brief 64, Error Interrupt Request Source Status Register */
    Ifx_I2C_ERRIRQSC ERRIRQSC;              /**< \brief 68, Error Interrupt Request Source Clear Register */
    unsigned char reserved_6C[4];           /**< \brief 6C, \internal Reserved */
    Ifx_I2C_PIRQSM PIRQSM;                  /**< \brief 70, Protocol Interrupt Request Source Mask Register */
    Ifx_I2C_PIRQSS PIRQSS;                  /**< \brief 74, Protocol Interrupt Request Source Status Register */
    Ifx_I2C_PIRQSC PIRQSC;                  /**< \brief 78, Protocol Interrupt Request Source Clear Register */
    unsigned char reserved_7C[4];           /**< \brief 7C, \internal Reserved */
    Ifx_I2C_RIS RIS;                        /**< \brief 80, Raw Interrupt Status Register */
    Ifx_I2C_IMSC IMSC;                      /**< \brief 84, Interrupt Mask Control Register */
    Ifx_I2C_MIS MIS;                        /**< \brief 88, Masked Interrupt Status Register */
    Ifx_I2C_ICR ICR;                        /**< \brief 8C, Interrupt Clear Register */
    Ifx_I2C_ISR ISR;                        /**< \brief 90, Interrupt Set Register */
    unsigned char reserved_94[32620];       /**< \brief 94, \internal Reserved */
    Ifx_I2C_TXD TXD;                        /**< \brief 8000, Transmission Data Register */
    unsigned char reserved_8004[16380];     /**< \brief 8004, \internal Reserved */
    Ifx_I2C_RXD RXD;                        /**< \brief C000, Reception Data Register */
    unsigned char reserved_C004[16380];     /**< \brief C004, \internal Reserved */
    Ifx_I2C_CLC CLC;                        /**< \brief 10000, Clock Control Register */
    Ifx_I2C_MODID MODID;                    /**< \brief 10004, Module Identification Register */
    Ifx_I2C_GPCTL GPCTL;                    /**< \brief 10008, General Purpose Control Register */
    Ifx_I2C_ACCEN0 ACCEN0;                  /**< \brief 1000C, Access Enable Register 0 */
    Ifx_I2C_ACCEN1 ACCEN1;                  /**< \brief 10010, Access Enable Register 1 */
    Ifx_I2C_KRST0 KRST0;                    /**< \brief 10014, Kernel Reset Register 0 */
    Ifx_I2C_KRST1 KRST1;                    /**< \brief 10018, Kernel Reset Register 1 */
    Ifx_I2C_KRSTCLR KRSTCLR;                /**< \brief 1001C, Kernel Reset Status Clear Register */
    unsigned char reserved_10020[224];      /**< \brief 10020, \internal Reserved */
} Ifx_I2C;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXI2C_REGDEF_H */
