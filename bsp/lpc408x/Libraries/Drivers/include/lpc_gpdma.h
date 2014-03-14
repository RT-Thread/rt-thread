/**********************************************************************
* $Id$      lpc_gpdma.h         2011-06-02
*//**
* @file     lpc_gpdma.h
* @brief    Contains all macro definitions and function prototypes
*           support for GPDMA firmware library on LPC
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
/** @defgroup GPDMA GPDMA (General Purpose Direct Memory Access)
 * @ingroup LPC_CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC_GPDMA_H_
#define __LPC_GPDMA_H_

/* Includes ------------------------------------------------------------------- */
#include "LPC407x_8x_177x_8x.h"
#include "lpc_types.h"


#ifdef __cplusplus
extern "C"
{
#endif

/* Public Macros -------------------------------------------------------------- */
/** @defgroup GPDMA_Public_Macros GPDMA Public Macros
 * @{
 */

/** DMA Connection number definitions */
#define GPDMA_CONN_MCI              ((1UL))         /** SD card */
#define GPDMA_CONN_SSP0_Tx          ((2UL))         /**< SSP0 Tx */
#define GPDMA_CONN_SSP0_Rx          ((3UL))         /**< SSP0 Rx */
#define GPDMA_CONN_SSP1_Tx          ((4UL))         /**< SSP1 Tx */
#define GPDMA_CONN_SSP1_Rx          ((5UL))         /**< SSP1 Rx */
#define GPDMA_CONN_SSP2_Tx          ((6UL))         /**< SSP2 Tx */
#define GPDMA_CONN_SSP2_Rx          ((7UL))         /**< SSP2 Rx */
#define GPDMA_CONN_ADC              ((8UL))         /**< ADC */
#define GPDMA_CONN_DAC              ((9UL))         /**< DAC */
#define GPDMA_CONN_UART0_Tx         ((10UL))        /**< UART0 Tx */
#define GPDMA_CONN_UART0_Rx         ((11UL))        /**< UART0 Rx */
#define GPDMA_CONN_UART1_Tx         ((12UL))        /**< UART1 Tx */
#define GPDMA_CONN_UART1_Rx         ((13UL))        /**< UART1 Rx */
#define GPDMA_CONN_UART2_Tx         ((14UL))        /**< UART2 Tx */
#define GPDMA_CONN_UART2_Rx         ((15UL))        /**< UART2 Rx */
#define GPDMA_CONN_MAT0_0           ((16UL))        /**< MAT0.0 */
#define GPDMA_CONN_MAT0_1           ((17UL))        /**< MAT0.1 */
#define GPDMA_CONN_MAT1_0           ((18UL))        /**< MAT1.0 */
#define GPDMA_CONN_MAT1_1           ((19UL))        /**< MAT1.1 */
#define GPDMA_CONN_MAT2_0           ((20UL))        /**< MAT2.0 */
#define GPDMA_CONN_MAT2_1           ((21UL))        /**< MAT2.1 */
#define GPDMA_CONN_I2S_Channel_0    ((22UL))        /**< I2S channel 0 */
#define GPDMA_CONN_I2S_Channel_1    ((23UL))        /**< I2S channel 1 */
#define GPDMA_CONN_UART3_Tx         ((26UL))        /**< UART3 Tx */
#define GPDMA_CONN_UART3_Rx         ((27UL))        /**< UART3 Rx */
#define GPDMA_CONN_UART4_Tx         ((28UL))        /**< UART3 Tx */
#define GPDMA_CONN_UART4_Rx         ((29UL))        /**< UART3 Rx */
#define GPDMA_CONN_MAT3_0           ((30UL))        /**< MAT3.0 */
#define GPDMA_CONN_MAT3_1           ((31UL))        /**< MAT3.1 */

/** GPDMA Transfer type definitions: Memory to memory - DMA control */
#define GPDMA_TRANSFERTYPE_M2M      ((0UL))
/** GPDMA Transfer type definitions: Memory to peripheral - DMA control */
#define GPDMA_TRANSFERTYPE_M2P      ((1UL))
/** GPDMA Transfer type definitions: Peripheral to memory - DMA control */
#define GPDMA_TRANSFERTYPE_P2M      ((2UL))
/** Source peripheral to destination peripheral - DMA control */
#define GPDMA_TRANSFERTYPE_P2P      ((3UL))
/** Memory to peripheral - Destination peripheral control */
#define GPDMA_TRANSFERTYPE_M2P_DEST_CTRL        ((5UL))
/** Peripheral to memory - Source peripheral control */
#define GPDMA_TRANSFERTYPE_P2M_SRC_CTRL         ((6UL))

/** Burst size in Source and Destination definitions */
#define GPDMA_BSIZE_1   ((0UL)) /**< Burst size = 1 */
#define GPDMA_BSIZE_4   ((1UL)) /**< Burst size = 4 */
#define GPDMA_BSIZE_8   ((2UL)) /**< Burst size = 8 */
#define GPDMA_BSIZE_16  ((3UL)) /**< Burst size = 16 */
#define GPDMA_BSIZE_32  ((4UL)) /**< Burst size = 32 */
#define GPDMA_BSIZE_64  ((5UL)) /**< Burst size = 64 */
#define GPDMA_BSIZE_128 ((6UL)) /**< Burst size = 128 */
#define GPDMA_BSIZE_256 ((7UL)) /**< Burst size = 256 */

/** Width in Source transfer width and Destination transfer width definitions */
#define GPDMA_WIDTH_BYTE        ((0UL)) /**< Width = 1 byte */
#define GPDMA_WIDTH_HALFWORD    ((1UL)) /**< Width = 2 bytes */
#define GPDMA_WIDTH_WORD        ((2UL)) /**< Width = 4 bytes */

/** DMA Request Select Mode definitions */
#define GPDMA_REQSEL_UART   ((0UL)) /**< UART TX/RX is selected */
#define GPDMA_REQSEL_TIMER  ((1UL)) /**< Timer match is selected */

/**
 * @}
 */


/* Private Macros ------------------------------------------------------------- */
/** @defgroup GPDMA_Private_Macros GPDMA Private Macros
 * @{
 */

/* --------------------- BIT DEFINITIONS -------------------------------------- */
/*********************************************************************//**
 * Macro defines for DMA Interrupt Status register
 **********************************************************************/
#define GPDMA_DMACIntStat_Ch(n)         (((1UL<<n)&0xFF))
#define GPDMA_DMACIntStat_BITMASK       ((0xFF))

/*********************************************************************//**
 * Macro defines for DMA Interrupt Terminal Count Request Status register
 **********************************************************************/
#define GPDMA_DMACIntTCStat_Ch(n)       (((1UL<<n)&0xFF))
#define GPDMA_DMACIntTCStat_BITMASK     ((0xFF))

/*********************************************************************//**
 * Macro defines for DMA Interrupt Terminal Count Request Clear register
 **********************************************************************/
#define GPDMA_DMACIntTCClear_Ch(n)      (((1UL<<n)&0xFF))
#define GPDMA_DMACIntTCClear_BITMASK    ((0xFF))

/*********************************************************************//**
 * Macro defines for DMA Interrupt Error Status register
 **********************************************************************/
#define GPDMA_DMACIntErrStat_Ch(n)      (((1UL<<n)&0xFF))
#define GPDMA_DMACIntErrStat_BITMASK    ((0xFF))

/*********************************************************************//**
 * Macro defines for DMA Interrupt Error Clear register
 **********************************************************************/
#define GPDMA_DMACIntErrClr_Ch(n)       (((1UL<<n)&0xFF))
#define GPDMA_DMACIntErrClr_BITMASK     ((0xFF))

/*********************************************************************//**
 * Macro defines for DMA Raw Interrupt Terminal Count Status register
 **********************************************************************/
#define GPDMA_DMACRawIntTCStat_Ch(n)    (((1UL<<n)&0xFF))
#define GPDMA_DMACRawIntTCStat_BITMASK  ((0xFF))

/*********************************************************************//**
 * Macro defines for DMA Raw Error Interrupt Status register
 **********************************************************************/
#define GPDMA_DMACRawIntErrStat_Ch(n)   (((1UL<<n)&0xFF))
#define GPDMA_DMACRawIntErrStat_BITMASK ((0xFF))

/*********************************************************************//**
 * Macro defines for DMA Enabled Channel register
 **********************************************************************/
#define GPDMA_DMACEnbldChns_Ch(n)       (((1UL<<n)&0xFF))
#define GPDMA_DMACEnbldChns_BITMASK     ((0xFF))

/*********************************************************************//**
 * Macro defines for DMA Software Burst Request register
 **********************************************************************/
#define GPDMA_DMACSoftBReq_Src(n)       (((1UL<<n)&0xFFFF))
#define GPDMA_DMACSoftBReq_BITMASK      ((0xFFFF))

/*********************************************************************//**
 * Macro defines for DMA Software Single Request register
 **********************************************************************/
#define GPDMA_DMACSoftSReq_Src(n)       (((1UL<<n)&0xFFFF))
#define GPDMA_DMACSoftSReq_BITMASK      ((0xFFFF))

/*********************************************************************//**
 * Macro defines for DMA Software Last Burst Request register
 **********************************************************************/
#define GPDMA_DMACSoftLBReq_Src(n)      (((1UL<<n)&0xFFFF))
#define GPDMA_DMACSoftLBReq_BITMASK     ((0xFFFF))

/*********************************************************************//**
 * Macro defines for DMA Software Last Single Request register
 **********************************************************************/
#define GPDMA_DMACSoftLSReq_Src(n)      (((1UL<<n)&0xFFFF))
#define GPDMA_DMACSoftLSReq_BITMASK     ((0xFFFF))

/*********************************************************************//**
 * Macro defines for DMA Configuration register
 **********************************************************************/
#define GPDMA_DMACConfig_E              ((0x01))     /**< DMA Controller enable*/
#define GPDMA_DMACConfig_M              ((0x02))     /**< AHB Master endianness configuration*/
#define GPDMA_DMACConfig_BITMASK        ((0x03))

/*********************************************************************//**
 * Macro defines for DMA Synchronization register
 **********************************************************************/
#define GPDMA_DMACSync_Src(n)           (((1UL<<n)&0xFFFF))
#define GPDMA_DMACSync_BITMASK          ((0xFFFF))

/*********************************************************************//**
 * Macro defines for DMA Request Select register
 **********************************************************************/
#define GPDMA_DMAReqSel_Input(n)        (((1UL<<(n-8))&0xFF))
#define GPDMA_DMAReqSel_BITMASK         ((0xFF))

/*********************************************************************//**
 * Macro defines for DMA Channel Linked List Item registers
 **********************************************************************/
/** DMA Channel Linked List Item registers bit mask*/
#define GPDMA_DMACCxLLI_BITMASK         ((0xFFFFFFFC))

/*********************************************************************//**
 * Macro defines for DMA channel control registers
 **********************************************************************/
/** Transfer size*/
#define GPDMA_DMACCxControl_TransferSize(n) (((n&0xFFF)<<0))
/** Source burst size*/
#define GPDMA_DMACCxControl_SBSize(n)       (((n&0x07)<<12))
/** Destination burst size*/
#define GPDMA_DMACCxControl_DBSize(n)       (((n&0x07)<<15))
/** Source transfer width*/
#define GPDMA_DMACCxControl_SWidth(n)       (((n&0x07)<<18))
/** Destination transfer width*/
#define GPDMA_DMACCxControl_DWidth(n)       (((n&0x07)<<21))
/** Source increment*/
#define GPDMA_DMACCxControl_SI              ((1UL<<26))
/** Destination increment*/
#define GPDMA_DMACCxControl_DI              ((1UL<<27))
/** Indicates that the access is in user mode or privileged mode*/
#define GPDMA_DMACCxControl_Prot1           ((1UL<<28))
/** Indicates that the access is bufferable or not bufferable*/
#define GPDMA_DMACCxControl_Prot2           ((1UL<<29))
/** Indicates that the access is cacheable or not cacheable*/
#define GPDMA_DMACCxControl_Prot3           ((1UL<<30))
/** Terminal count interrupt enable bit */
#define GPDMA_DMACCxControl_I               ((1UL<<31))
/** DMA channel control registers bit mask */
#define GPDMA_DMACCxControl_BITMASK         ((0xFCFFFFFF))

/*********************************************************************//**
 * Macro defines for DMA Channel Configuration registers
 **********************************************************************/
/** DMA control enable*/
#define GPDMA_DMACCxConfig_E                    ((1UL<<0))
/** Source peripheral*/
#define GPDMA_DMACCxConfig_SrcPeripheral(n)     (((n&0x1F)<<1))
/** Destination peripheral*/
#define GPDMA_DMACCxConfig_DestPeripheral(n)    (((n&0x1F)<<6))
/** This value indicates the type of transfer*/
#define GPDMA_DMACCxConfig_TransferType(n)      (((n&0x7)<<11))
/** Interrupt error mask*/
#define GPDMA_DMACCxConfig_IE                   ((1UL<<14))
/** Terminal count interrupt mask*/
#define GPDMA_DMACCxConfig_ITC                  ((1UL<<15))
/** Lock*/
#define GPDMA_DMACCxConfig_L                    ((1UL<<16))
/** Active*/
#define GPDMA_DMACCxConfig_A                    ((1UL<<17))
/** Halt*/
#define GPDMA_DMACCxConfig_H                    ((1UL<<18))
/** DMA Channel Configuration registers bit mask */
#define GPDMA_DMACCxConfig_BITMASK              ((0x7FFFF))

/**
 * @}
 */


/* Public Types --------------------------------------------------------------- */
/** @defgroup GPDMA_Public_Types GPDMA Public Types
 * @{
 */

/**
 * @brief GPDMA Status enumeration
 */
typedef enum {
    GPDMA_STAT_INT,         /**< GPDMA Interrupt Status */
    GPDMA_STAT_INTTC,       /**< GPDMA Interrupt Terminal Count Request Status */
    GPDMA_STAT_INTERR,      /**< GPDMA Interrupt Error Status */
    GPDMA_STAT_RAWINTTC,    /**< GPDMA Raw Interrupt Terminal Count Status */
    GPDMA_STAT_RAWINTERR,   /**< GPDMA Raw Error Interrupt Status */
    GPDMA_STAT_ENABLED_CH   /**< GPDMA Enabled Channel Status */
} GPDMA_Status_Type;

/**
 * @brief GPDMA Interrupt clear status enumeration
 */
typedef enum{
    GPDMA_STATCLR_INTTC,    /**< GPDMA Interrupt Terminal Count Request Clear */
    GPDMA_STATCLR_INTERR    /**< GPDMA Interrupt Error Clear */
}GPDMA_StateClear_Type;

/**
 * @brief GPDMA Channel configuration structure type definition
 */
typedef struct {
    uint32_t ChannelNum;    /**< DMA channel number, should be in
                                range from 0 to 7.
                                Note: DMA channel 0 has the highest priority
                                and DMA channel 7 the lowest priority.
                                */
    uint32_t TransferSize;  /**< Length/Size of transfer */
    uint32_t TransferWidth; /**< Transfer width - used for TransferType is GPDMA_TRANSFERTYPE_M2M only */
    uint32_t SrcMemAddr;    /**< Physical Source Address, used in case TransferType is chosen as
                                 GPDMA_TRANSFERTYPE_M2M or GPDMA_TRANSFERTYPE_M2P */
    uint32_t DstMemAddr;    /**< Physical Destination Address, used in case TransferType is chosen as
                                 GPDMA_TRANSFERTYPE_M2M or GPDMA_TRANSFERTYPE_P2M */
    uint32_t TransferType;  /**< Transfer Type, should be one of the following:
                            - GPDMA_TRANSFERTYPE_M2M: Memory to memory - DMA control
                            - GPDMA_TRANSFERTYPE_M2P: Memory to peripheral - DMA control
                            - GPDMA_TRANSFERTYPE_P2M: Peripheral to memory - DMA control
                            - GPDMA_TRANSFERTYPE_P2P: Source peripheral to destination peripheral - DMA control
                            */
    uint32_t SrcConn;       /**< Peripheral Source Connection type, used in case TransferType is chosen as
                            GPDMA_TRANSFERTYPE_P2M or GPDMA_TRANSFERTYPE_P2P, should be one of
                            following:
                             - GPDMA_CONN_SSP0_Tx: SSP0, Tx
                             - GPDMA_CONN_SSP0_Rx: SSP0, Rx
                             - GPDMA_CONN_SSP1_Tx: SSP1, Tx
                             - GPDMA_CONN_SSP1_Rx: SSP1, Rx
                             - GPDMA_CONN_ADC: ADC
                             - GPDMA_CONN_I2S_Channel_0: I2S Channel 0
                             - GPDMA_CONN_I2S_Channel_1: I2S Channel 1
                             - GPDMA_CONN_DAC: DAC
                             - GPDMA_CONN_UART0_Tx_MAT0_0: UART0 Tx / MAT0.0
                             - GPDMA_CONN_UART0_Rx_MAT0_1: UART0 Rx / MAT0.1
                             - GPDMA_CONN_UART1_Tx_MAT1_0: UART1 Tx / MAT1.0
                             - GPDMA_CONN_UART1_Rx_MAT1_1: UART1 Rx / MAT1.1
                             - GPDMA_CONN_UART2_Tx_MAT2_0: UART2 Tx / MAT2.0
                             - GPDMA_CONN_UART2_Rx_MAT2_1: UART2 Rx / MAT2.1
                             - GPDMA_CONN_UART3_Tx_MAT3_0: UART3 Tx / MAT3.0
                             - GPDMA_CONN_UART3_Rx_MAT3_1: UART3 Rx / MAT3.1
                             */
    uint32_t DstConn;       /**< Peripheral Destination Connection type, used in case TransferType is chosen as
                            GPDMA_TRANSFERTYPE_M2P or GPDMA_TRANSFERTYPE_P2P, should be one of
                            following:
                             - GPDMA_CONN_SSP0_Tx: SSP0, Tx
                             - GPDMA_CONN_SSP0_Rx: SSP0, Rx
                             - GPDMA_CONN_SSP1_Tx: SSP1, Tx
                             - GPDMA_CONN_SSP1_Rx: SSP1, Rx
                             - GPDMA_CONN_ADC: ADC
                             - GPDMA_CONN_I2S_Channel_0: I2S Channel 0
                             - GPDMA_CONN_I2S_Channel_1: I2S Channel 1
                             - GPDMA_CONN_DAC: DAC
                             - GPDMA_CONN_UART0_Tx_MAT0_0: UART0 Tx / MAT0.0
                             - GPDMA_CONN_UART0_Rx_MAT0_1: UART0 Rx / MAT0.1
                             - GPDMA_CONN_UART1_Tx_MAT1_0: UART1 Tx / MAT1.0
                             - GPDMA_CONN_UART1_Rx_MAT1_1: UART1 Rx / MAT1.1
                             - GPDMA_CONN_UART2_Tx_MAT2_0: UART2 Tx / MAT2.0
                             - GPDMA_CONN_UART2_Rx_MAT2_1: UART2 Rx / MAT2.1
                             - GPDMA_CONN_UART3_Tx_MAT3_0: UART3 Tx / MAT3.0
                             - GPDMA_CONN_UART3_Rx_MAT3_1: UART3 Rx / MAT3.1
                             */
    uint32_t DMALLI;        /**< Linker List Item structure data address
                            if there's no Linker List, set as '0'
                            */
} GPDMA_Channel_CFG_Type;

/**
 * @brief GPDMA Linker List Item structure type definition
 */
typedef struct {
    uint32_t SrcAddr;   /**< Source Address */
    uint32_t DstAddr;   /**< Destination address */
    uint32_t NextLLI;   /**< Next LLI address, otherwise set to '0' */
    uint32_t Control;   /**< GPDMA Control of this LLI */
} GPDMA_LLI_Type;


/**
 * @}
 */

/* Public Functions ----------------------------------------------------------- */
/** @defgroup GPDMA_Public_Functions GPDMA Public Functions
 * @{
 */

void GPDMA_Init(void);
Status GPDMA_Setup(GPDMA_Channel_CFG_Type *GPDMAChannelConfig);
IntStatus GPDMA_IntGetStatus(GPDMA_Status_Type type, uint8_t channel);
void GPDMA_ClearIntPending(GPDMA_StateClear_Type type, uint8_t channel);
void GPDMA_ChannelCmd(uint8_t channelNum, FunctionalState NewState);
//void GPDMA_IntHandler(void);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* __LPC_GPDMA_H_ */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
