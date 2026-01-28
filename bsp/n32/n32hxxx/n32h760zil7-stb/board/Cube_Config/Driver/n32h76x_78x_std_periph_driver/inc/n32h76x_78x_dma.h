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
 * @file n32h76x_78x_dma.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76x_78x_DMA_H__
#define __N32H76x_78x_DMA_H__


#include <stdio.h>
#include "n32h76x_78x.h"


#if defined(DMA1) || defined(DMA2) || defined(DMA3)



/** DMA Channel Numbers per DMA Controller definition **/
#define DMA_NUM_CHANNELS 8

/** DMA Channel Enable/Disable definition **/
#define DMA_CH_ENABLE  ((uint32_t)(DMA_CHEN_CH0WEN | DMA_CHEN_CH0))
#define DMA_CH_DISABLE ((uint32_t)(DMA_CHEN_CH0WEN & (~DMA_CHEN_CH0)))

/** DMA Interrupt Mask/Unmask definition **/
#define DMA_INT_UNMASK ((uint32_t)(DMA_TCINTMSK_CH0WEN | DMA_TCINTMSK_CH0))
#define DMA_INT_MASK   ((uint32_t)(DMA_TCINTMSK_CH0WEN & (~DMA_TCINTMSK_CH0)))

/** DMA Source Single Transaction Request Enable/Disable definition **/
#define DMA_SSTR_ENABLE  ((uint32_t)(DMA_SRCSGTREQ_CH0WEN | DMA_SRCSGTREQ_CH0))
#define DMA_SSTR_DISABLE ((uint32_t)(DMA_SRCSGTREQ_CH0WEN & (~DMA_SRCSGTREQ_CH0)))

/** DMA Source Last Transaction Request Enable/Disable definition **/
#define DMA_SLTR_ENABLE  ((uint32_t)(DMA_SRCLTREQ_CH0WEN | DMA_SRCLTREQ_CH0))
#define DMA_SLTR_DISABLE ((uint32_t)(DMA_SRCLTREQ_CH0WEN & (~DMA_SRCLTREQ_CH0)))

/** DMA Source Transaction Request Enable/Disable definition **/
#define DMA_STR_ENABLE  ((uint32_t)(DMA_SRCSWTREQ_CH0WEN | DMA_SRCSWTREQ_CH0))
#define DMA_STR_DISABLE ((uint32_t)(DMA_SRCSWTREQ_CH0WEN & (~DMA_SRCSWTREQ_CH0)))

/** DMA Destination Single Transaction Request Enable/Disable definition **/
#define DMA_DSTR_ENABLE  ((uint32_t)(DMA_DSTSGTREQ_CH0WEN | DMA_DSTSGTREQ_CH0))
#define DMA_DSTR_DISABLE ((uint32_t)(DMA_DSTSGTREQ_CH0WEN & (~DMA_DSTSGTREQ_CH0)))

/** DMA Destination Last Transaction Request Enable/Disable definition **/
#define DMA_DLTR_ENABLE  ((uint32_t)(DMA_DSTLTREQ_CH0WEN | DMA_DSTLTREQ_CH0))
#define DMA_DLTR_DISABLE ((uint32_t)(DMA_DSTLTREQ_CH0WEN & (~DMA_DSTLTREQ_CH0)))

/** DMA Destination Transaction Request Enable/Disable definition **/
#define DMA_DTR_ENABLE  ((uint32_t)(DMA_DSTSWTREQ_CH0WEN | DMA_DSTSWTREQ_CH0))
#define DMA_DTR_DISABLE ((uint32_t)(DMA_DSTSWTREQ_CH0WEN & (~DMA_DSTSWTREQ_CH0)))

/** DMA Channel Bus Lock Level definition **/
#define DMA_CH_BUS_LOCK_LEVEL_OCDMATFR    ((uint64_t)(DMA_CHNCFG_LOCKBL_0 \
                                                    & DMA_CHNCFG_LOCKBL_1)) /* Over complete DMA transfer */
#define DMA_CH_BUS_LOCK_LEVEL_OCDMABLKTFR ((uint64_t)(DMA_CHNCFG_LOCKBL_0)) /* Over complete DMA block transfer */
#define DMA_CH_BUS_LOCK_LEVEL_OCDMATRAN   ((uint64_t)(DMA_CHNCFG_LOCKBL_1)) /* Over complete DMA transfer */

/** DMA Channel Lock Level definition **/
#define DMA_CH_LOCK_LEVEL_OCDMATFR    ((uint64_t)(DMA_CHNCFG_LOCKCHL_0 \
                                                & DMA_CHNCFG_LOCKCHL_1)) /* Over complete DMA transfer */
#define DMA_CH_LOCK_LEVEL_OCDMABLKTFR ((uint64_t)(DMA_CHNCFG_LOCKCHL_0)) /* Over complete DMA block transfer */
#define DMA_CH_LOCK_LEVEL_OCDMATRAN   ((uint64_t)(DMA_CHNCFG_LOCKCHL_1)) /* Over complete DMA transfer */

/** DMA Channel interrupt event definition **/
#define DMA_EVENT_TRANSFER_COMPLETE        ((uint32_t)DMA_TCINTSTS_CH0)  /* IntTfr: Transfer complete interrupt event */
#define DMA_EVENT_BLOCK_TRANSFER_COMPLETE  ((uint32_t)DMA_BTCINTSTS_CH0) /* IntBlock: Block transfer complete interrupt event */
#define DMA_EVENT_SRC_TRANSACTION_COMPLETE ((uint32_t)DMA_STCINTSTS_CH0) /* IntSrcTran: Source transaction complete interrupt event */
#define DMA_EVENT_DST_TRANSACTION_COMPLETE ((uint32_t)DMA_DTCINTSTS_CH0) /* IntDstTran: Destination transaction complete interrupt event */
#define DMA_EVENT_ERROR                    ((uint32_t)DMA_ERRINTSTS_CH0) /* IntErr: Error interrupt event */


/** DMA Channel Number typedef **/
typedef enum
{
    DMA_CHANNEL_0 = 0x0UL,
    DMA_CHANNEL_1 = 0x1UL,
    DMA_CHANNEL_2 = 0x2UL,
    DMA_CHANNEL_3 = 0x3UL,
    DMA_CHANNEL_4 = 0x4UL,
    DMA_CHANNEL_5 = 0x5UL,
    DMA_CHANNEL_6 = 0x6UL,
    DMA_CHANNEL_7 = 0x7UL
} DMA_ChNumType;

/** DMA Channel Status typedef **/
typedef enum
{
    DMA_CH_STS_OK = 0, /* DMA status OK */
    DMA_CH_STS_ERROR,  /* DMA status Error */
    DMA_CH_STS_BUSY    /* DMA status Busy */
} DMA_ChStatusType;

/** DMA channel transfer types typedef **/
typedef enum
{
    DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK,                                /* Single block */
    DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_CONTIGUOUS_DSTADR_RELOAD, /* Multi-block: src address contiguous, dst address reload */
    DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_RELOAD_DSTADR_CONTIGUOUS, /* Multi-block: src address reload, dst address contiguous */
    DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_RELOAD_DSTADR_RELOAD,     /* Multi-block: src address reload, dst address reload */
    DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_CONTIGUOUS_DSTADR_LINKED, /* Multi-block: src address contiguous, dst address linked */
    DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_RELOAD_DSTADR_LINKED,     /* Multi-block: src address reload, dst address linked */
    DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_LINKED_DSTADR_CONTIGUOUS, /* Multi-block: src address linked, dst address contiguous */
    DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_LINKED_DSTADR_RELOAD,     /* Multi-block: src address linked, dst address reload */
    DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_LINKED_DSTADR_LINKED      /* Multi-block: src address linked, dst address linked */
} DMA_ChTfrType;

/** DMA channel transfer flow modes typedef **/
typedef enum
{
    DMA_CH_TRANSFER_FLOW_M2M_DMA    = 0x0UL, /* Memory to memory (DMA flow controller) */
    DMA_CH_TRANSFER_FLOW_M2P_DMA    = 0x1UL, /* Memory to peripheral (DMA flow controller) */
    DMA_CH_TRANSFER_FLOW_P2M_DMA    = 0x2UL, /* Peripheral to memory (DMA flow controller) */
    DMA_CH_TRANSFER_FLOW_P2P_DMA    = 0x3UL, /* Peripheral to peripheral (DMA flow controller) */
    DMA_CH_TRANSFER_FLOW_P2M_PER    = 0x4UL, /* Peripheral to memory (Peripheral flow controller) */
    DMA_CH_TRANSFER_FLOW_P2P_SRCPER = 0x5UL, /* Peripheral to peripheral (Source peripheral flow controller) */
    DMA_CH_TRANSFER_FLOW_M2P_PER    = 0x6UL, /* Memory to peripheral (Peripheral flow controller) */
    DMA_CH_TRANSFER_FLOW_P2P_DSTPER = 0x7UL  /* Peripheral to peripheral (Destination peripheral flow controller) */
} DMA_ChTfrFlowType;

/** DMA channel master interface layer select typedef **/
typedef enum
{
    DMA_CH_AHB_MASTER_1 = 0x0UL, /* AHB master 1 */
    DMA_CH_AHB_MASTER_2 = 0x1UL  /* AHB master 2 */
} DMA_ChMstSelType;

/** DMA channel valid burst length value typedef **/
typedef enum
{
    DMA_CH_BURST_LENGTH_1   = 0x0UL,  /* Burst length: 1   data item  */
    DMA_CH_BURST_LENGTH_4   = 0x1UL,  /* Burst length: 4   data items */
    DMA_CH_BURST_LENGTH_8   = 0x2UL,  /* Burst length: 8   data items */
    DMA_CH_BURST_LENGTH_16  = 0x3UL,  /* Burst length: 16  data items */
    DMA_CH_BURST_LENGTH_32  = 0x4UL,  /* Burst length: 32  data items */
    DMA_CH_BURST_LENGTH_64  = 0x5UL,  /* Burst length: 64  data items */
    DMA_CH_BURST_LENGTH_128 = 0x6UL,  /* Burst length: 128 data items */
    DMA_CH_BURST_LENGTH_256 = 0x7UL   /* Burst length: 256 data items */
} DMA_ChBurstLenType;

/** DMA channel valid transfer width values typedef **/
typedef enum
{
    DMA_CH_TRANSFER_WIDTH_8   = 0x0UL,  /* 8-bit transfer width */
    DMA_CH_TRANSFER_WIDTH_16  = 0x1UL,  /* 16-bit transfer width */
    DMA_CH_TRANSFER_WIDTH_32  = 0x2UL,  /* 32-bit transfer width */
} DMA_ChTfrWidthType;

/** DMA channel address count mode typedef **/
typedef enum
{
    DMA_CH_ADDRESS_COUNT_MODE_INCREMENT = 0x0UL, /* Address count mode: increment */
    DMA_CH_ADDRESS_COUNT_MODE_DECREMENT = 0x1UL, /* Address count mode: decrement */
    DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE = 0x2UL  /* Address count mode: no change */
} DMA_ChAddrCountType;

/** DMA channel priorities typedef **/
typedef enum
{
    DMA_CH_PRIORITY_0 = 0x0UL, /* DMA channel priority 0 (low) */
    DMA_CH_PRIORITY_1 = 0x1UL, /* DMA channel priority 1 */
    DMA_CH_PRIORITY_2 = 0x2UL, /* DMA channel priority 2 */
    DMA_CH_PRIORITY_3 = 0x3UL, /* DMA channel priority 3 */
    DMA_CH_PRIORITY_4 = 0x4UL, /* DMA channel priority 4 */
    DMA_CH_PRIORITY_5 = 0x5UL, /* DMA channel priority 5 */
    DMA_CH_PRIORITY_6 = 0x6UL, /* DMA channel priority 6 */
    DMA_CH_PRIORITY_7 = 0x7UL  /* DMA channel priority 7 (high) */
} DMA_ChPriorType;

/** DMA channel Source handshake interface typedef **/
typedef enum
{
    DMA_CH_SRC_HANDSHAKING_HARDWARE = 0x0UL, /* Source: hardware handshake */
    DMA_CH_SRC_HANDSHAKING_SOFTWARE = 0x1UL  /* Source: software handshake */
} DMA_ChSrcHsType;

/** DMA channel Destination handshake interface typedef **/
typedef enum
{
    DMA_CH_DST_HANDSHAKING_HARDWARE = 0x0UL, /* Destination: hardware handshake */
    DMA_CH_DST_HANDSHAKING_SOFTWARE = 0x1UL  /* Destination: software handshake */
} DMA_ChDstHsType;

/** DMA channel hardware handshaking interface, available when DMA is flow controller typedef **/
typedef enum
{
    DMA_CH_HARDWARE_HANDSHAKING_IF_0  = 0x0UL, /* Hardware handshaking interface 0  */
    DMA_CH_HARDWARE_HANDSHAKING_IF_1  = 0x1UL, /* Hardware handshaking interface 1  */
    DMA_CH_HARDWARE_HANDSHAKING_IF_2  = 0x2UL, /* Hardware handshaking interface 2  */
    DMA_CH_HARDWARE_HANDSHAKING_IF_3  = 0x3UL, /* Hardware handshaking interface 3  */
    DMA_CH_HARDWARE_HANDSHAKING_IF_4  = 0x4UL, /* Hardware handshaking interface 4  */
    DMA_CH_HARDWARE_HANDSHAKING_IF_5  = 0x5UL, /* Hardware handshaking interface 5  */
    DMA_CH_HARDWARE_HANDSHAKING_IF_6  = 0x6UL, /* Hardware handshaking interface 6  */
    DMA_CH_HARDWARE_HANDSHAKING_IF_7  = 0x7UL, /* Hardware handshaking interface 7  */
} DMA_ChHwHsIfType;

/* DMA channel handshaking interface polarity typedef */
typedef enum
{
    DMA_CH_HANDSHAKING_IF_POL_H = 0x0UL, /* Active HIGH */
    DMA_CH_HANDSHAKING_IF_POL_L = 0x1UL, /* Active LOW */
} DMA_ChHsIfPolType;

/** DMA Channel events typedef **/
typedef enum
{
    DMA_CH_EVENT_TRANSFER_COMPLETE        = 0x1UL, /* Transfer complete event */
    DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE  = 0x2UL, /* Block transfer complete event */
    DMA_CH_EVENT_SRC_TRANSACTION_COMPLETE = 0x4UL, /* Source transaction complete event */
    DMA_CH_EVENT_DST_TRANSACTION_COMPLETE = 0x8UL, /* Destination transaction complete event */
    DMA_CH_EVENT_ERROR                    = 0x10UL /* DMA error event */
} DMA_ChEventType;

/** DMA Channel Transaction types typedef **/
typedef enum
{
    DMA_CH_TRANSACTION_TYPE_SINGLE, /* Single DMA transaction */
    DMA_CH_TRANSACTION_TYPE_BURST   /* Burst transaction */
} DMA_ChTransacType;



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

/** DMA channel linked list item structure, 32-bits alignment **/
typedef struct __DMA_LinkListItemType
{
    uint32_t SrcAddr;                     /* Source address */
    uint32_t DstAddr;                     /* Destination address */
    struct __DMA_LinkListItemType *pNext; /* The next linked list item pointer */

    union
    {
        uint32_t ChCtrlL32;
        struct
        {
            uint32_t IntEn: 1;            /* Enable interrupts? */
            uint32_t DstTfrWidth: 3;      /* Destination transfer width */
            uint32_t SrcTfrWidth: 3;      /* Source transfer width */
            uint32_t DstAddrCountMode: 2; /* Destination address count mode */
            uint32_t SrcAddrCountMode: 2; /* Source address count mode */
            uint32_t DstBurstLen: 3;      /* Destination burst length */
            uint32_t SrcBurstLen: 3;      /* Source burst length */
            uint32_t SrcGatherEn: 1;      /* Enable source gather? */
            uint32_t DstScatterEn: 1;     /* Enable destination scatter? */
            uint32_t : 1;
            uint32_t TfrTypeFlowCtrl: 3;  /* Transfer Type and Flow Control */
            uint32_t : 4;
            uint32_t DstLinkedListEn: 1;  /* Enable destination linked list? */
            uint32_t SrcLinkedListEn: 1;  /* Enable source linked list? */
            uint32_t : 3;
        };
    };
    
    union
    {
        uint32_t ChCtrlH32;
        struct
        {
            uint32_t BlkTfrSize: 12;      /* DMA block size for DMA controlled transfers [max. 4095]*/
            uint32_t DoneFlag: 1;         /* Block transfer complete flag */
            uint32_t : 19;
        };
    };
    
} DMA_LinkListItemType;

/** DMA Channel Initialize configuration structure **/
typedef struct
{
    union
    {
        uint64_t ChCtrl;
        struct
        {
            uint64_t IntEn: 1;            /* Enable interrupts? */
            uint64_t DstTfrWidth: 3;      /* Destination transfer width */
            uint64_t SrcTfrWidth: 3;      /* Source transfer width */
            uint64_t DstAddrCountMode: 2; /* Destination address count mode */
            uint64_t SrcAddrCountMode: 2; /* Source address count mode */
            uint64_t DstBurstLen: 3;      /* Destination burst length */
            uint64_t SrcBurstLen: 3;      /* Source burst length */
            uint64_t SrcGatherEn: 1;      /* Enable source gather? */
            uint64_t DstScatterEn: 1;     /* Enable destination scatter? */
            uint64_t : 1;
            uint64_t TfrTypeFlowCtrl: 3;  /* Transfer Type and Flow Control */
            uint64_t DstMasterSelect: 2;  /* Destination Master Interface layer */
            uint64_t SrcMasterSelect: 2;  /* Source Master Interface layer */
            uint64_t : 5;
            uint64_t BlkTfrSize: 12;      /* DMA block size for DMA controlled transfers [max. 4095]*/
            uint64_t : 20;
        };
    };

    uint32_t SrcAddr;                     /* Source address */
    uint32_t DstAddr;                     /* Destination address */
    DMA_LinkListItemType* pLinkListItem;  /* Linked list item pointer */

    union
    {
        uint32_t SrcGatherCtrl;
        struct
        {
            uint32_t SrcGatherInterval: 20; /* Source gather interval */
            uint32_t SrcGatherCount: 12;    /* Source gather count */
        };
    };

    union
    {
        uint32_t DstScatterCtrl;
        struct
        {
            uint32_t DstScatterInterval: 20; /* Destination scatter interval */
            uint32_t DstScatterCount: 12;    /* Destination scatter count */
        };
    };

    DMA_ChTfrType       TfrType;         /* DMA transfer type */
    DMA_ChPriorType     ChannelPriority; /* DMA channel priority */
    DMA_ChSrcHsType     SrcHandshaking;  /* DMA source handshaking interface */
    DMA_ChHwHsIfType    SrcHsInterface;  /* DMA source assigned handshaking interface */
    DMA_ChHsIfPolType SrcHsInterfacePol; /* DMA source handshaking interface polarity */
    DMA_ChDstHsType     DstHandshaking;  /* DMA destination handshaking interface */
    DMA_ChHwHsIfType    DstHsInterface;  /* DMA destination assigned handshaking interface */
    DMA_ChHsIfPolType DstHsInterfacePol; /* DMA destination handshaking interface polarity */

} DMA_ChInitType;


/** End of section using anonymous unions (Keil only) **/
#if defined (__CC_ARM)
    /* Restore compiler settings */
    #pragma pop
#endif


void DMA_ControllerCmd(DMA_Module *const DMAy, FunctionalStatus Cmd);
bool DMA_ControllerIsEnabled(DMA_Module *const DMAy);
void DMA_ChannelCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd);
bool DMA_ChannelIsEnabled(DMA_Module *const DMAy, DMA_ChNumType ChNum);
DMA_ChStatusType DMA_ChannelInit(DMA_Module *const DMAy, DMA_ChInitType *const DMA_ChInitParam, DMA_ChNumType ChNum);
void DMA_ChannelStructInit(DMA_ChInitType *const DMA_ChInitParam);
void DMA_ChannelSuspend(DMA_Module *const DMAy, DMA_ChNumType ChNum);
bool DMA_ChannelIsSuspended(DMA_Module *const DMAy, DMA_ChNumType ChNum);
void DMA_ChannelResume(DMA_Module *const DMAy, DMA_ChNumType ChNum);

void DMA_ChannelEventCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t Event, FunctionalStatus Cmd);
void DMA_ClearChannelEventStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t Event);
uint8_t DMA_GetCombinedStatus(DMA_Module *const DMAy);
INTStatus DMA_GetChannelIntTfrStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum);
INTStatus DMA_GetChannelIntBlockStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum);
INTStatus DMA_GetChannelIntSrcTranStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum);
INTStatus DMA_GetChannelIntDstTranStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum);
INTStatus DMA_GetChannelIntErrStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum);

void DMA_ChannelSourceGatherCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd);
void DMA_SetChannelSourceGather(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t Interval, uint16_t Count);
void DMA_ChannelDestinationScatterCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd);
void DMA_SetChannelDestinationScatter(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t Interval, uint16_t Count);

void DMA_SetChannelSourceAddress(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t *pAddr);
void DMA_SetChannelDestinationAddress(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t *pAddr);
void DMA_SetChannelBlockSize(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t Size);
uint16_t DMA_GetTransferredNumber(DMA_Module *const DMAy, DMA_ChNumType ChNum);
void DMA_SetChannelLinkedListPointer(DMA_Module *const DMAy, DMA_ChNumType ChNum, DMA_LinkListItemType* pStr);
void DMA_TriggerSourceRequest(DMA_Module *const DMAy, DMA_ChNumType ChNum, DMA_ChTransacType Type, bool isLast);
void DMA_TriggerDestinationRequest(DMA_Module *const DMAy, DMA_ChNumType ChNum, DMA_ChTransacType Type, bool isLast);
void DMA_ChannelSourceAddressReloadCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd);
void DMA_ChannelDestinationAddressReloadCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd);

void DMA_ChannelBusLockCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd);
void DMA_ChannelLockCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd);
void DMA_SetChannelBusLockLevel(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint64_t Level);
void DMA_SetChannelLockLevel(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint64_t Level);



#ifdef __cplusplus
}
#endif


#endif /* ( defined(DMA1) || defined(DMA2) || defined(DMA3) ) */
#endif /* __N32H76x_H78x_DMA_H__ */

