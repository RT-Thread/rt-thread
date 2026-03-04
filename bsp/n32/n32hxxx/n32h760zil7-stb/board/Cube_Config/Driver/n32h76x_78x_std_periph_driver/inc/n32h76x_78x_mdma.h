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
 * @file n32h76x_78x_mdma.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76x_78x_MDMA_H__
#define __N32H76x_78x_MDMA_H__


#include <stdio.h>
#include "n32h76x_78x.h"


#if defined (MDMA)


/** MDMA Channel Numbers per MDMA Controller definition **/
#define MDMA_NUM_CHANNELS (16U)

/** MDMA Channel Enable/Disable definition **/
#define MDMA_CH_ENABLE  ((uint32_t)(MDMA_CHEN_CH0WEN | MDMA_CHEN_CH0))
#define MDMA_CH_DISABLE ((uint32_t)(MDMA_CHEN_CH0WEN & (~MDMA_CHEN_CH0)))

/** MDMA Channel Suspend/Resume definition **/
#define MDMA_CH_SUSPEND ((uint32_t)(MDMA_CHSUSP_CH0WEN | MDMA_CHSUSP_CH0))
#define MDMA_CH_RESUME  ((uint32_t)(MDMA_CHSUSP_CH0WEN & (~MDMA_CHSUSP_CH0)))

/** MDMA Common Register Interrupt definition **/
#define MDMA_COMMON_INT_SIURDEI    ((uint32_t)MDMA_CRINTSTSEN_SIURDEIS)    /* Slave Interface Undefined Register Decode Error Interrupt */
#define MDMA_COMMON_INT_SICRWOHEI  ((uint32_t)MDMA_CRINTSTSEN_SICRWOHEIS)  /* Slave Interface Common Register Write On Hold Error Interrupt */
#define MDMA_COMMON_INT_SICRR2WOEI ((uint32_t)MDMA_CRINTSTSEN_SICRR2WOEIS) /* Slave Interface Common Register Read to Write Only Error Interrupt */
#define MDMA_COMMON_INT_SICRW2ROEI ((uint32_t)MDMA_CRINTSTSEN_SICRW2ROEIS) /* Slave Interface Common Register Write to Read Only Error Interrupt */
#define MDMA_COMMON_INT_SICRDEI    ((uint32_t)MDMA_CRINTSTSEN_SICRDEIS)    /* Slave Interface Common Register Decode Error Interrupt */

/** MDMA Clear Common Register Interrupt definition **/
#define MDMA_COMMON_INT_CLEAR ((uint32_t)(MDMA_CRINTCLR_SIURDEIC    | \
                                          MDMA_CRINTCLR_SICRWOHEIC  | \
                                          MDMA_CRINTCLR_SICRR2WOEIC | \
                                          MDMA_CRINTCLR_SICRW2ROEIC | \
                                          MDMA_CRINTCLR_SICRDEIC))

/** MDMA Common Register Interrupt Status Enable register mask definition **/
#define MDMA_COMMON_INT_STS_MASK ((uint32_t)(MDMA_CRINTSTSEN_SIURDEIS    | \
                                             MDMA_CRINTSTSEN_SICRWOHEIS  | \
                                             MDMA_CRINTSTSEN_SICRR2WOEIS | \
                                             MDMA_CRINTSTSEN_SICRW2ROEIS | \
                                             MDMA_CRINTSTSEN_SICRDEIS))

/** MDMA Common Register Interrupt Signal Enable register mask definition **/
#define MDMA_COMMON_INT_SGL_MASK ((uint32_t)(MDMA_CRINTSGLEN_SIURDEIS    | \
                                             MDMA_CRINTSGLEN_SICRWOHEIS  | \
                                             MDMA_CRINTSGLEN_SICRR2WOEIS | \
                                             MDMA_CRINTSGLEN_SICRW2ROEIS | \
                                             MDMA_CRINTSGLEN_SICRDEIS))

/** MDMA Channel Interrupt definition **/
#define MDMA_CH_INT_CH_ABORTED                ((uint32_t)MDMA_CHNINTSTSEN_CHA)
#define MDMA_CH_INT_CH_DISABLED               ((uint32_t)MDMA_CHNINTSTSEN_CHD)
#define MDMA_CH_INT_CH_SUSPENDED              ((uint32_t)MDMA_CHNINTSTSEN_CHS)
#define MDMA_CH_INT_CH_SRC_SUSPENDED          ((uint32_t)MDMA_CHNINTSTSEN_CHSS)
#define MDMA_CH_INT_CH_LOCK_CLEARED           ((uint32_t)MDMA_CHNINTSTSEN_CHLC)
#define MDMA_CH_INT_SLV_IF_W_ON_HOLD_ERR      ((uint32_t)MDMA_CHNINTSTSEN_SIWOHE)
#define MDMA_CH_INT_SLV_IF_W_ON_CH_EN_ERR     ((uint32_t)MDMA_CHNINTSTSEN_SIWOCEE)
#define MDMA_CH_INT_SLV_IF_R2WO_ERR           ((uint32_t)MDMA_CHNINTSTSEN_SIRTWOE)
#define MDMA_CH_INT_SLV_IF_W2RO_ERR           ((uint32_t)MDMA_CHNINTSTSEN_SIWTROE)
#define MDMA_CH_INT_SLV_IF_DEC_ERR            ((uint32_t)MDMA_CHNINTSTSEN_SIDE)
#define MDMA_CH_INT_SLV_IF_MULTI_BLK_TYPE_ERR ((uint32_t)MDMA_CHNINTSTSEN_SIMBTE)
#define MDMA_CH_INT_SDW_REG_LLI_INVALID_ERR   ((uint32_t)MDMA_CHNINTSTSEN_SLIE)
#define MDMA_CH_INT_LLI_W_SLV_ERR             ((uint32_t)MDMA_CHNINTSTSEN_LWSE)
#define MDMA_CH_INT_LLI_R_SLV_ERR             ((uint32_t)MDMA_CHNINTSTSEN_LRSE)
#define MDMA_CH_INT_LLI_W_DEC_ERR             ((uint32_t)MDMA_CHNINTSTSEN_LWDE)
#define MDMA_CH_INT_LLI_R_DEC_ERR             ((uint32_t)MDMA_CHNINTSTSEN_LRDE)
#define MDMA_CH_INT_DST_SLV_ERR               ((uint32_t)MDMA_CHNINTSTSEN_DSTSE)
#define MDMA_CH_INT_SRC_SLV_ERR               ((uint32_t)MDMA_CHNINTSTSEN_SRCSE)
#define MDMA_CH_INT_DST_DEC_ERR               ((uint32_t)MDMA_CHNINTSTSEN_DSTDE)
#define MDMA_CH_INT_SRC_DEC_ERR               ((uint32_t)MDMA_CHNINTSTSEN_SRCDE)
#define MDMA_CH_INT_DST_TRAN_COMPLE           ((uint32_t)MDMA_CHNINTSTSEN_DSTTC)
#define MDMA_CH_INT_SRC_TRAN_COMPLE           ((uint32_t)MDMA_CHNINTSTSEN_SRCTC)
#define MDMA_CH_INT_DMA_TRF_DONE              ((uint32_t)MDMA_CHNINTSTSEN_DMATD)
#define MDMA_CH_INT_BLK_TRF_DONE              ((uint32_t)MDMA_CHNINTSTSEN_BLKTD)

/** MDMA Clear Channel Interrupt definition **/
#define MDMA_CH_INT_CLEAR ((uint32_t)(MDMA_CHNINTCLR_CHA     | \
                                      MDMA_CHNINTCLR_CHD     | \
                                      MDMA_CHNINTCLR_CHS     | \
                                      MDMA_CHNINTCLR_CHSS    | \
                                      MDMA_CHNINTCLR_CHLC    | \
                                      MDMA_CHNINTCLR_SIWOHE  | \
                                      MDMA_CHNINTCLR_SIWOCEE | \
                                      MDMA_CHNINTCLR_SIRTWOE | \
                                      MDMA_CHNINTCLR_SIWTROE | \
                                      MDMA_CHNINTCLR_SIDE    | \
                                      MDMA_CHNINTCLR_SIMBTE  | \
                                      MDMA_CHNINTCLR_SLIE    | \
                                      MDMA_CHNINTCLR_LWSE    | \
                                      MDMA_CHNINTCLR_LRSE    | \
                                      MDMA_CHNINTCLR_LWDE    | \
                                      MDMA_CHNINTCLR_LRDE    | \
                                      MDMA_CHNINTCLR_DSTSE   | \
                                      MDMA_CHNINTCLR_SRCSE   | \
                                      MDMA_CHNINTCLR_DSTDE   | \
                                      MDMA_CHNINTCLR_SRCDE   | \
                                      MDMA_CHNINTCLR_DSTTC   | \
                                      MDMA_CHNINTCLR_SRCTC   | \
                                      MDMA_CHNINTCLR_DMATD   | \
                                      MDMA_CHNINTCLR_BLKTD))

/** MDMA Channel Interrupt Status Enable register mask definition **/
#define MDMA_CH_INT_STS_MASK ((uint32_t)(MDMA_CHNINTSTSEN_CHA     | \
                                         MDMA_CHNINTSTSEN_CHD     | \
                                         MDMA_CHNINTSTSEN_CHS     | \
                                         MDMA_CHNINTSTSEN_CHSS    | \
                                         MDMA_CHNINTSTSEN_CHLC    | \
                                         MDMA_CHNINTSTSEN_SIWOHE  | \
                                         MDMA_CHNINTSTSEN_SIWOCEE | \
                                         MDMA_CHNINTSTSEN_SIRTWOE | \
                                         MDMA_CHNINTSTSEN_SIWTROE | \
                                         MDMA_CHNINTSTSEN_SIDE    | \
                                         MDMA_CHNINTSTSEN_SIMBTE  | \
                                         MDMA_CHNINTSTSEN_SLIE    | \
                                         MDMA_CHNINTSTSEN_LWSE    | \
                                         MDMA_CHNINTSTSEN_LRSE    | \
                                         MDMA_CHNINTSTSEN_LWDE    | \
                                         MDMA_CHNINTSTSEN_LRDE    | \
                                         MDMA_CHNINTSTSEN_DSTSE   | \
                                         MDMA_CHNINTSTSEN_SRCSE   | \
                                         MDMA_CHNINTSTSEN_DSTDE   | \
                                         MDMA_CHNINTSTSEN_SRCDE   | \
                                         MDMA_CHNINTSTSEN_DSTTC   | \
                                         MDMA_CHNINTSTSEN_SRCTC   | \
                                         MDMA_CHNINTSTSEN_DMATD   | \
                                         MDMA_CHNINTSTSEN_BLKTD))

/** MDMA Channel Interrupt Signal Enable register mask definition **/
#define MDMA_CH_INT_SGL_MASK ((uint32_t)(MDMA_CHNINTSGLEN_CHA     | \
                                         MDMA_CHNINTSGLEN_CHD     | \
                                         MDMA_CHNINTSGLEN_CHS     | \
                                         MDMA_CHNINTSGLEN_CHSS    | \
                                         MDMA_CHNINTSGLEN_CHLC    | \
                                         MDMA_CHNINTSGLEN_SIWOHE  | \
                                         MDMA_CHNINTSGLEN_SIWOCEE | \
                                         MDMA_CHNINTSGLEN_SIRTWOE | \
                                         MDMA_CHNINTSGLEN_SIWTROE | \
                                         MDMA_CHNINTSGLEN_SIDE    | \
                                         MDMA_CHNINTSGLEN_SIMBTE  | \
                                         MDMA_CHNINTSGLEN_SLIE    | \
                                         MDMA_CHNINTSGLEN_LWSE    | \
                                         MDMA_CHNINTSGLEN_LRSE    | \
                                         MDMA_CHNINTSGLEN_LWDE    | \
                                         MDMA_CHNINTSGLEN_LRDE    | \
                                         MDMA_CHNINTSGLEN_DSTSE   | \
                                         MDMA_CHNINTSGLEN_SRCSE   | \
                                         MDMA_CHNINTSGLEN_DSTDE   | \
                                         MDMA_CHNINTSGLEN_SRCDE   | \
                                         MDMA_CHNINTSGLEN_DSTTC   | \
                                         MDMA_CHNINTSGLEN_SRCTC   | \
                                         MDMA_CHNINTSGLEN_DMATD   | \
                                         MDMA_CHNINTSGLEN_BLKTD))



/** MDMA Channel Number typedef **/
typedef enum
{
    MDMA_CHANNEL_0  = 0x0UL,
    MDMA_CHANNEL_1  = 0x1UL,
    MDMA_CHANNEL_2  = 0x2UL,
    MDMA_CHANNEL_3  = 0x3UL,
    MDMA_CHANNEL_4  = 0x4UL,
    MDMA_CHANNEL_5  = 0x5UL,
    MDMA_CHANNEL_6  = 0x6UL,
    MDMA_CHANNEL_7  = 0x7UL,
    MDMA_CHANNEL_8  = 0x8UL,
    MDMA_CHANNEL_9  = 0x9UL,
    MDMA_CHANNEL_10 = 0xAUL,
    MDMA_CHANNEL_11 = 0xBUL,
    MDMA_CHANNEL_12 = 0xCUL,
    MDMA_CHANNEL_13 = 0xDUL,
    MDMA_CHANNEL_14 = 0xEUL,
    MDMA_CHANNEL_15 = 0xFUL
} MDMA_ChNumType;

/** MDMA Channel Status typedef **/
typedef enum
{
    MDMA_CH_STS_OK = 0, /* MDMA status OK */
    MDMA_CH_STS_ERROR,  /* MDMA status Error */
    MDMA_CH_STS_BUSY    /* MDMA status Busy */
} MDMA_ChStatusType;

/** MDMA Channel Master Select typedef **/
typedef enum
{
    MDMA_CH_MASTER_1 = 0, /* AXI master 1 */
    MDMA_CH_MASTER_2      /* AXI master 2 */
} MDMA_ChMasterSelType;

/** MDMA channel multi block transfer type typedef **/
typedef enum
{
    MDMA_CH_MULTI_BLOCK_CONTIGUOUS  = 0x0UL, /* Contiguous Multiblock Type */
    MDMA_CH_MULTI_BLOCK_RELOAD      = 0x1UL, /* Reload Multiblock Type */
    MDMA_CH_MULTI_BLOCK_LINKED_LIST = 0x3UL  /* Linked List based Multiblock Type */
} MDMA_ChMultBlkTfrType;

/** MDMA channel transfer type and flow control typedef **/
typedef enum
{
    MDMA_CH_TRANSFER_FLOW_M2M_MDMA   = 0x0UL, /* Memory to memory (MDMA flow controller) */
    MDMA_CH_TRANSFER_FLOW_M2P_MDMA   = 0x1UL, /* Memory to peripheral (MDMA flow controller) */
    MDMA_CH_TRANSFER_FLOW_P2M_MDMA   = 0x2UL, /* Peripheral to memory (MDMA flow controller) */
    MDMA_CH_TRANSFER_FLOW_P2P_MDMA   = 0x3UL, /* Peripheral to peripheral (MDMA flow controller) */
    MDMA_CH_TRANSFER_FLOW_P2M_SRCPER = 0x4UL, /* Peripheral to memory (Source Peripheral flow controller) */
    MDMA_CH_TRANSFER_FLOW_P2P_SRCPER = 0x5UL, /* Peripheral to peripheral (Source peripheral flow controller) */
    MDMA_CH_TRANSFER_FLOW_M2P_DSTPER = 0x6UL, /* Memory to peripheral (Destination Peripheral flow controller) */
    MDMA_CH_TRANSFER_FLOW_P2P_DSTPER = 0x7UL  /* Peripheral to peripheral (Destination peripheral flow controller) */
} MDMA_ChTfrFlowType;

/** MDMA channel transfer width typedef **/
typedef enum
{
    MDMA_CH_TRANSFER_WIDTH_8  = 0x0UL, /* 8-bit transfer width */
    MDMA_CH_TRANSFER_WIDTH_16 = 0x1UL, /* 16-bit transfer width */
    MDMA_CH_TRANSFER_WIDTH_32 = 0x2UL, /* 32-bit transfer width */
    MDMA_CH_TRANSFER_WIDTH_64 = 0x3UL  /* 64-bit transfer width */
} MDMA_ChTfrWidthType;

/** MDMA channel burst transaction length typedef **/
typedef enum
{
    MDMA_CH_BURST_TRAN_LEN_1    = 0x0UL, /* 1 Data Item read from Source in the burst transaction */
    MDMA_CH_BURST_TRAN_LEN_4    = 0x1UL, /* 4 Data Item read from Source in the burst transaction */
    MDMA_CH_BURST_TRAN_LEN_8    = 0x2UL, /* 8 Data Item read from Source in the burst transaction */
    MDMA_CH_BURST_TRAN_LEN_16   = 0x3UL, /* 16 Data Item read from Source in the burst transaction */
    MDMA_CH_BURST_TRAN_LEN_32   = 0x4UL, /* 32 Data Item read from Source in the burst transaction */
    MDMA_CH_BURST_TRAN_LEN_64   = 0x5UL, /* 64 Data Item read from Source in the burst transaction */
    MDMA_CH_BURST_TRAN_LEN_128  = 0x6UL, /* 128 Data Item read from Source in the burst transaction */
} MDMA_ChBurstTranLenType;

/** MDMA channel address count mode typedef **/
typedef enum
{
    MDMA_CH_ADDRESS_COUNT_MODE_INCREMENT = 0x0UL, /* Address count mode: increment */
    MDMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE = 0x1UL  /* Address count mode: no change */
} MDMA_ChAddrCountType;

/** MDMA channel priorities typedef **/
typedef enum
{
    MDMA_CH_PRIORITY_0  = 0x0UL, /* MDMA channel priority 0 (low) */
    MDMA_CH_PRIORITY_1  = 0x1UL, /* MDMA channel priority 1 */
    MDMA_CH_PRIORITY_2  = 0x2UL, /* MDMA channel priority 2 */
    MDMA_CH_PRIORITY_3  = 0x3UL, /* MDMA channel priority 3 */
    MDMA_CH_PRIORITY_4  = 0x4UL, /* MDMA channel priority 4 */
    MDMA_CH_PRIORITY_5  = 0x5UL, /* MDMA channel priority 5 */
    MDMA_CH_PRIORITY_6  = 0x6UL, /* MDMA channel priority 6 */
    MDMA_CH_PRIORITY_7  = 0x7UL, /* MDMA channel priority 7 */
    MDMA_CH_PRIORITY_8  = 0x8UL, /* MDMA channel priority 8 */
    MDMA_CH_PRIORITY_9  = 0x9UL, /* MDMA channel priority 9 */
    MDMA_CH_PRIORITY_10 = 0xAUL, /* MDMA channel priority 10 */
    MDMA_CH_PRIORITY_11 = 0xBUL, /* MDMA channel priority 11 */
    MDMA_CH_PRIORITY_12 = 0xCUL, /* MDMA channel priority 12 */
    MDMA_CH_PRIORITY_13 = 0xDUL, /* MDMA channel priority 13 */
    MDMA_CH_PRIORITY_14 = 0xEUL, /* MDMA channel priority 14 */
    MDMA_CH_PRIORITY_15 = 0xFUL  /* MDMA channel priority 15 (high) */
} MDMA_ChPriorType;

/** MDMA channel Source handshake interface typedef **/
typedef enum
{
    MDMA_CH_SRC_HANDSHAKING_HARDWARE = 0x0UL, /* Source: hardware handshake */
    MDMA_CH_SRC_HANDSHAKING_SOFTWARE = 0x1UL  /* Source: software handshake */
} MDMA_ChSrcHsType;

/** MDMA channel Destination handshake interface typedef **/
typedef enum
{
    MDMA_CH_DST_HANDSHAKING_HARDWARE = 0x0UL, /* Destination: hardware handshake */
    MDMA_CH_DST_HANDSHAKING_SOFTWARE = 0x1UL  /* Destination: software handshake */
} MDMA_ChDstHsType;

/** MDMA channel hardware handshaking interface typedef, available when MDMA is flow controller **/
typedef enum
{
    MDMA_CH_HARDWARE_HANDSHAKING_IF_0   = 0x0UL,  /* Hardware handshaking interface 0  */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_1   = 0x1UL,  /* Hardware handshaking interface 1  */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_2   = 0x2UL,  /* Hardware handshaking interface 2  */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_3   = 0x3UL,  /* Hardware handshaking interface 3  */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_4   = 0x4UL,  /* Hardware handshaking interface 4  */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_5   = 0x5UL,  /* Hardware handshaking interface 5  */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_6   = 0x6UL,  /* Hardware handshaking interface 6  */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_7   = 0x7UL,  /* Hardware handshaking interface 7  */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_8   = 0x8UL,  /* Hardware handshaking interface 8  */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_9   = 0x9UL,  /* Hardware handshaking interface 9  */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_10  = 0xAUL,  /* Hardware handshaking interface 10 */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_11  = 0xBUL,  /* Hardware handshaking interface 11 */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_12  = 0xCUL,  /* Hardware handshaking interface 12 */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_13  = 0xDUL,  /* Hardware handshaking interface 13 */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_14  = 0xEUL,  /* Hardware handshaking interface 14 */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_15  = 0xFUL   /* Hardware handshaking interface 15 */
} MDMA_ChHwHsIfType;

/** MDMA channel hardware handshaking interface polarity typedef **/
typedef enum
{
    MDMA_CH_HARDWARE_HANDSHAKING_IF_POL_H = 0x0UL, /* Active HIGH */
    MDMA_CH_HARDWARE_HANDSHAKING_IF_POL_L = 0x1UL  /* Active LOW */
} MDMA_ChHwHsIfPolType;

/** MDMA Channel Software Handshake transfer types typedef **/
typedef enum
{
    MDMA_CH_SOFTWARE_HANDSHAKING_TFR_SINGLE, /* Single DMA transfer */
    MDMA_CH_SOFTWARE_HANDSHAKING_TFR_BURST   /* Burst transfer */
} MDMA_ChSwHsTfrType;


/** Start of section using anonymous unions **/
#if defined (__CC_ARM)
    /* Save the current compiler state (Keil only) */
    #pragma push
    /* Enable anonymous unions */
    #pragma anon_unions
#elif defined(__ICCARM__)
    /* Enable anonymous consortia */
    #pragma language=extended
#elif defined(__GNUC__) 
    /* GCC supports anonymous unions by default */
#else
    #warning "Anonymous unions may not be supported by this compiler. Check compiler documentation."
#endif

/** MDMA channel linked list item structure, 64-bits alignment **/
typedef struct __MDMA_LinkListItemType
{
    uint64_t SrcAddr;                      /* Source address */
    
    uint64_t DstAddr;                      /* Destination address */
    
    uint32_t BlkSize;                      /* MDMA block size for MDMA controlled transfers [max. 8191] */
    
    uint32_t RESERVED0;                    /* Reserved */
    
    struct __MDMA_LinkListItemType *pNext; /* The next linked list item pointer */
    
    union
    {
        uint64_t ChCtrl;
        struct
        {
            uint64_t SrcMasterSel: 1;      /* Source Master Select "0: AXI master 1, 1: AXI Master 2" */
            uint64_t : 1;
            uint64_t DstMasterSel: 1;      /* Destination Master Select "0: AXI master 1, 1: AXI Master 2" */
            uint64_t : 1;
            uint64_t SrcAddrInc: 1;        /* Source Address Increment */
            uint64_t : 1;
            uint64_t DstAddrInc: 1;        /* Destination Address Increment */
            uint64_t : 1;
            uint64_t SrcTfrWidth: 3;       /* Source Transfer width */
            uint64_t DstTfrWidth: 3;       /* Destination Transfer width */
            uint64_t SrcBurstTranLen:  4;  /* Source Burst Transaction Length */
            uint64_t DstBurstTranLen:  4;  /* Destination Burst Transaction Length */
            uint64_t : 8;
            uint64_t NonPosLastWriteEn: 1; /* Non Posted Last Write Enable */
            uint64_t : 1;

            uint64_t : 6;
            uint64_t SrcBurstLenEn: 1;     /* Source Burst Length Enable */
            uint64_t SrcBurstLen: 8;       /* Source Burst Length */
            uint64_t DstBurstLenEn: 1;     /* Destination Burst Length Enable */
            uint64_t DstBurstLen: 8;       /* Destination Burst Length */
            uint64_t : 2;
            uint64_t IocBlkTfr: 1;         /* Interrupt On completion of Block Transfer */
            uint64_t : 3;
            uint64_t SdwLlILast: 1;        /* Last Linked List Item */
            uint64_t SdwLlIValid: 1;       /* Linked List Item (LLI) valid */
        };
    };

} MDMA_LinkListItemType;

/** MDMA Channel Initialize configuration structure **/
typedef struct
{
    union
    {
        uint64_t ChCtrl;
        struct
        {
            uint64_t SrcMasterSel: 1;      /* Source Master Select "0: AXI master 1, 1: AXI Master 2" */
            uint64_t : 1;
            uint64_t DstMasterSel: 1;      /* Destination Master Select "0: AXI master 1, 1: AXI Master 2" */
            uint64_t : 1;
            uint64_t SrcAddrInc: 1;        /* Source Address Increment */
            uint64_t : 1;
            uint64_t DstAddrInc: 1;        /* Destination Address Increment */
            uint64_t : 1;
            uint64_t SrcTfrWidth: 3;       /* Source Transfer width */
            uint64_t DstTfrWidth: 3;       /* Destination Transfer width */
            uint64_t SrcBurstTranLen: 4;   /* Source Burst Transaction Length */
            uint64_t DstBurstTranLen: 4;   /* Destination Burst Transaction Length */
            uint64_t : 8;
            uint64_t NonPosLastWriteEn: 1; /* Non Posted Last Write Enable */
            uint64_t : 1;

            uint64_t : 6;
            uint64_t SrcBurstLenEn: 1;     /* Source Burst Length Enable */
            uint64_t SrcBurstLen: 8;       /* Source Burst Length */
            uint64_t DstBurstLenEn: 1;     /* Destination Burst Length Enable */
            uint64_t DstBurstLen: 8;       /* Destination Burst Length */
            uint64_t : 2;
            uint64_t IocBlkTfr: 1;         /* Interrupt On completion of Block Transfer */
            uint64_t : 3;
            uint64_t SdwLlILast: 1;        /* Last Linked List Item */
            uint64_t SdwLlIValid: 1;       /* Linked List Item (LLI) valid */
        };
    };

    uint64_t SrcAddr;                      /* Source address */
    uint64_t DstAddr;                      /* Destination address */
    MDMA_LinkListItemType *pLinkListItem;  /* Linked list item pointer */

    uint32_t              BlkSize;           /* MDMA block size for MDMA controlled transfers [max. 8191] */
    MDMA_ChPriorType      ChannelPriority;   /* MDMA channel priority */

    MDMA_ChSrcHsType      SrcHandshaking;    /* MDMA source handshaking interface */
    MDMA_ChHwHsIfType     SrcHsInterface;    /* MDMA source assigned handshaking interface */
    MDMA_ChHwHsIfPolType  SrcHsInterfacePol; /* MDMA source hardware handshaking interface polarity */
    MDMA_ChDstHsType      DstHandshaking;    /* MDMA destination handshaking interface */
    MDMA_ChHwHsIfType     DstHsInterface;    /* MDMA destination assigned handshaking interface */
    MDMA_ChHwHsIfPolType  DstHsInterfacePol; /* MDMA destination hardware handshaking interface polarity */

    MDMA_ChTfrFlowType    TfrTypeFlowCtrl;   /* MDMA transfer type and flow control */
    MDMA_ChMultBlkTfrType SrcMultBlkTfrType; /* Source Multi Block Transfer Type */
    MDMA_ChMultBlkTfrType DstMultBlkTfrType; /* Destination Multi Block Transfer Type */

} MDMA_ChInitType;

/** End of section using anonymous unions (Keil only) **/
#if defined (__CC_ARM)
    /* Restore compiler settings */
    #pragma pop
#endif


void MDMA_ControllerCmd(MDMA_Module *const MDMAy, FunctionalStatus Cmd);
bool MDMA_ControllerIsEnabled(MDMA_Module *const MDMAy);
void MDMA_ControllerSoftReset(MDMA_Module *const MDMAy);
void MDMA_ChannelCmd(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, FunctionalStatus Cmd);
bool MDMA_ChannelIsEnabled(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum);
MDMA_ChStatusType MDMA_ChannelInit(MDMA_Module *const MDMAy, MDMA_ChInitType *const MDMA_ChInitParam, MDMA_ChNumType ChNum);
void MDMA_ChannelStructInit(MDMA_ChInitType *const MDMA_ChInitParam);
void MDMA_ChannelSuspend(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum);
bool MDMA_ChannelIsSuspended(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum);
void MDMA_ChannelResume(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum);

void MDMA_GlobalInterruptCmd(MDMA_Module *const MDMAy, FunctionalStatus Cmd);
void MDMA_CommonInterruptStatusCmd(MDMA_Module *const MDMAy, uint32_t Interrupt, FunctionalStatus Cmd);
void MDMA_CommonInterruptSignalCmd(MDMA_Module *const MDMAy, uint32_t Interrupt, FunctionalStatus Cmd);
void MDMA_ClearCommonInterruptStatus(MDMA_Module *const MDMAy, uint32_t Interrupt);
uint64_t MDMA_GetCombinedStatus(MDMA_Module *const MDMAy);
INTStatus MDMA_GetCommonInterruptStatus(MDMA_Module *const MDMAy, uint32_t Interrupt);
void MDMA_ChannelInterruptStatusCmd(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint32_t Interrupt, FunctionalStatus Cmd);
void MDMA_ChannelInterruptSignalCmd(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint32_t Interrupt, FunctionalStatus Cmd);
void MDMA_ClearChannelInterruptStatus(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint32_t Interrupt);
INTStatus MDMA_GetChannelInterruptStatus(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint32_t Interrupt);

void MDMA_SetChannelSourceAddress(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint64_t Addr);
void MDMA_SetChannelDestinationAddress(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint64_t Addr);
void MDMA_SetChannelBlockSize(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint32_t Size);
uint32_t MDMA_GetTransferredNumber(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum);
void MDMA_SetChannelLinkedListPointer(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint64_t StrAddr);
void MDMA_SetChannelSrcMultiBlockType(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, MDMA_ChMultBlkTfrType Type);
void MDMA_SetChannelDstMultiBlockType(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, MDMA_ChMultBlkTfrType Type);
void MDMA_TriggerSourceRequest(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, MDMA_ChSwHsTfrType Type, bool isLast);
void MDMA_TriggerDestinationRequest(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, MDMA_ChSwHsTfrType Type, bool isLast);
void MDMA_BlockTransferResumeRequest(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum);

void MDMA_SetChannelLinkedListItemValid(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum);
bool MDMA_ChannelLinkedListItemIsValid(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum);
void MDMA_SetChannelLastLinkedListItem(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum);



#ifdef __cplusplus
}
#endif

#endif /* defined (MDMA) */
#endif /* __N32H76x_78x_MDMA_H__ */

