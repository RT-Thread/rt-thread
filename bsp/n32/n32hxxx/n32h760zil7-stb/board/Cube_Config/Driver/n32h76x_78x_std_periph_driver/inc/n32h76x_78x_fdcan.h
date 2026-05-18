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
 * @file n32h76x_78x_fdcan.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76X_78X_FDCAN_H__
#define __N32H76X_78X_FDCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/** FDCAN Message RAM blocks **/
typedef struct
{
    uint32_t StdFilterStrAddr;      /* Specifies the Standard Filter List Start Address.
                                        This parameter must be 32-bit alignment      */
    uint32_t ExtFilterStrAddr;      /* Specifies the Extended Filter List Start Address.
                                        This parameter must be a 32-bit alignment      */
    uint32_t RxFIFO0StrAddr;        /* Specifies the Rx FIFO 0 Start Address.
                                        This parameter must be a 32-bit alignment      */
    uint32_t RxFIFO1StrAddr;        /* Specifies the Rx FIFO 1 Start Address.
                                        This parameter must be a 32-bit alignment      */
    uint32_t RxBufferStrAddr;       /* Specifies the Rx Buffer Start Address.
                                        This parameter must be a 32-bit alignment      */
    uint32_t TxEventFIFOStrAddr;    /* Specifies the Tx Event FIFO Start Address.
                                        This parameter must be a 32-bit alignment      */
    uint32_t TxBufferStrAddr;       /* Specifies the Tx Buffers Start Address.
                                        This parameter must be a 32-bit alignment      */
    uint32_t TxFIFOQueueStrAddr;    /* Specifies the Tx FIFO/Queue Start Address.
                                        This parameter must be a 32-bit alignment      */
    uint32_t TTMemoryStrAddr;       /* Specifies the Trigger Memory Start Address.
                                        This parameter must be a 32-bit alignment      */
    uint32_t EndAddress;            /* Specifies the End Address of the allocated RAM.
                                        This parameter must be a 32-bit alignment      */
    uint32_t LastTxFifoQReqBuf;     /* FDCAN Tx buffer index of latest Tx FIFO/Queue request */
    uint32_t RxFifo0Size;           /* Specifies the number of Rx FIFO0 Elements.
                                        This parameter must be a value between 0 and 64. */
    uint32_t RxFifo1Size;           /* Specifies the number of Rx FIFO1 Elements.
                                        This parameter must be a value between 0 and 64. */
    uint32_t RxBufferSize;          /* Specifies the number of Dedicated Rx Buffer elements.
                                        This parameter must be a value between 0 and 64. */
    uint32_t TxBufferSize;          /* Specifies the number of Dedicated Tx Buffers.
                                        This parameter must be a value between 0 and 32. */
    uint32_t RxFifo0DataSize;       /* Specifies the Data Field Size in an Rx FIFO 0 element,counted in words.
                                        This parameter must be one of the following values:
                                        - FDCAN_DATA_BYTES_8 
                                        - FDCAN_DATA_BYTES_12
                                        - FDCAN_DATA_BYTES_16
                                        - FDCAN_DATA_BYTES_20
                                        - FDCAN_DATA_BYTES_24
                                        - FDCAN_DATA_BYTES_32
                                        - FDCAN_DATA_BYTES_48
                                        - FDCAN_DATA_BYTES_64   */
    uint32_t RxFifo1DataSize;       /* Specifies the Data Field Size in an Rx FIFO 1 element,counted in words.    
                                        This parameter must be one of the following values:
                                        - FDCAN_DATA_BYTES_8 
                                        - FDCAN_DATA_BYTES_12
                                        - FDCAN_DATA_BYTES_16
                                        - FDCAN_DATA_BYTES_20
                                        - FDCAN_DATA_BYTES_24
                                        - FDCAN_DATA_BYTES_32
                                        - FDCAN_DATA_BYTES_48
                                        - FDCAN_DATA_BYTES_64   */
    uint32_t RxBufferDataSize;      /* Specifies the Data Field Size in an Rx Buffer element,counted in words.    
                                        This parameter must be one of the following values:
                                        - FDCAN_DATA_BYTES_8 
                                        - FDCAN_DATA_BYTES_12
                                        - FDCAN_DATA_BYTES_16
                                        - FDCAN_DATA_BYTES_20
                                        - FDCAN_DATA_BYTES_24
                                        - FDCAN_DATA_BYTES_32
                                        - FDCAN_DATA_BYTES_48
                                        - FDCAN_DATA_BYTES_64   */
    uint32_t TxBufferDataSize;      /* Specifies the Data Field Size in a Dedicated Tx Buffer element,counted in words.
                                        This parameter must be one of the following values:
                                        - FDCAN_DATA_BYTES_8 
                                        - FDCAN_DATA_BYTES_12
                                        - FDCAN_DATA_BYTES_16
                                        - FDCAN_DATA_BYTES_20
                                        - FDCAN_DATA_BYTES_24
                                        - FDCAN_DATA_BYTES_32
                                        - FDCAN_DATA_BYTES_48
                                        - FDCAN_DATA_BYTES_64   */
} FDCAN_MsgRamType;

/** FDCAN Init Structure Definition **/
typedef struct
{
    uint32_t FrameFormat;               /* FDCAN frame format. This parameter must be one of the following values:
                                            - FDCAN_FRAME_CLASSIC  
                                            - FDCAN_FRAME_FD_NO_BRS
                                            - FDCAN_FRAME_FD_BRS   */
    uint32_t Mode;                      /* FDCAN operation mode. This parameter must be one of the following values:
                                            - FDCAN_MODE_NORMAL              
                                            - FDCAN_MODE_RESTRICTED_OPERATION
                                            - FDCAN_MODE_BUS_MONITORING      
                                            - FDCAN_MODE_INTERNAL_LOOPBACK   
                                            - FDCAN_MODE_EXTERNAL_LOOPBACK   */
    uint32_t Prescaler;                 /* Specifies the Nominal Bit Rate Prescaler. 
                                            This parameter must be a value between 1 and 512. */
    uint32_t SyncJumpWidth;             /* Specifies the Nominal (Re)Synchronization Jump Width.
                                            This parameter must be a value between 1 and 128. */
    uint32_t TimeSeg1;                  /* Specifies the Nominal time segment before sample point.
                                            This parameter must be a value between 2 and 256. */
    uint32_t TimeSeg2;                  /* Specifies the Nominal time segment after sample point.
                                            This parameter must be a value between 2 and 128. */
    
    uint32_t DataPrescaler;             /* Specifies the Data Bit Rate Prescaler.
                                            This parameter must be a value between 1 and 32. */
    uint32_t DataSyncJumpWidth;         /* Specifies the Data (Re)Synchronization Jump Width.
                                            This parameter must be a value between 1 and 16. */
    uint32_t DataTimeSeg1;              /* Specifies the Data time segment before sample point.
                                            This parameter must be a value between 1 and 32. */
    uint32_t DataTimeSeg2;              /* Specifies the Data time segment after sample point.
                                            This parameter must be a value between 1 and 16. */
    
    uint32_t MsgRamStrAddr;             /* Specifies the Message RAM start address.  
                                           This parameter must be one of the following values:
                                            - FDCAN_START_ADDRESS_SRAM5BANK1 , 0x30050000 as FDCAN base address.
                                            - FDCAN_START_ADDRESS_SRAM5BANK2 , 0x30054000 as FDCAN base address.*/
    uint32_t MsgRamOffset;              /* Specifies the valid Message RAM word address offset, Overall offset of FDCAN nodes.
                                            This parameter must be a value between 0 and 0x4000 */
    uint32_t StdFilterSize;             /* Specifies the number of standard Message ID filters.
                                            This parameter must be a value between 0 and 128. */
    uint32_t ExtFilterSize;             /* pecifies the number of extended Message ID filters.
                                            This parameter must be a value between 0 and 64. */
    uint32_t RxFifo0Size;               /* Specifies the number of Rx FIFO0 Elements.
                                            This parameter must be a value between 0 and 64. */
    uint32_t RxFifo1Size;               /* Specifies the number of Rx FIFO1 Elements.
                                            This parameter must be a value between 0 and 64. */
    uint32_t RxBufferSize;              /* Specifies the number of Dedicated Rx Buffer elements.
                                            This parameter must be a value between 0 and 64. */
    uint32_t TxEventSize;               /* Specifies the number of Tx Event FIFO elements.
                                            This parameter must be a value between 0 and 32. */
    uint32_t TxBufferSize;              /* Specifies the number of Dedicated Tx Buffers.
                                            This parameter must be a value between 0 and 32. */
    uint32_t RxFifo0DataSize;           /* Specifies the Data Field Size in an Rx FIFO 0 element,counted in words.
                                            This parameter must be one of the following values:
                                            - FDCAN_DATA_BYTES_8 
                                            - FDCAN_DATA_BYTES_12
                                            - FDCAN_DATA_BYTES_16
                                            - FDCAN_DATA_BYTES_20
                                            - FDCAN_DATA_BYTES_24
                                            - FDCAN_DATA_BYTES_32
                                            - FDCAN_DATA_BYTES_48
                                            - FDCAN_DATA_BYTES_64   */
    uint32_t RxFifo1DataSize;           /* Specifies the Data Field Size in an Rx FIFO 1 element,counted in words.    
                                            This parameter must be one of the following values:
                                            - FDCAN_DATA_BYTES_8 
                                            - FDCAN_DATA_BYTES_12
                                            - FDCAN_DATA_BYTES_16
                                            - FDCAN_DATA_BYTES_20
                                            - FDCAN_DATA_BYTES_24
                                            - FDCAN_DATA_BYTES_32
                                            - FDCAN_DATA_BYTES_48
                                            - FDCAN_DATA_BYTES_64   */
    uint32_t RxBufferDataSize;          /* Specifies the Data Field Size in an Rx Buffer element,counted in words.    
                                            This parameter must be one of the following values:
                                            - FDCAN_DATA_BYTES_8 
                                            - FDCAN_DATA_BYTES_12
                                            - FDCAN_DATA_BYTES_16
                                            - FDCAN_DATA_BYTES_20
                                            - FDCAN_DATA_BYTES_24
                                            - FDCAN_DATA_BYTES_32
                                            - FDCAN_DATA_BYTES_48
                                            - FDCAN_DATA_BYTES_64   */
    uint32_t TxBufferDataSize;          /* Specifies the Data Field Size in a Dedicated Tx Buffer element,counted in words.
                                            This parameter must be one of the following values:
                                            - FDCAN_DATA_BYTES_8 
                                            - FDCAN_DATA_BYTES_12
                                            - FDCAN_DATA_BYTES_16
                                            - FDCAN_DATA_BYTES_20
                                            - FDCAN_DATA_BYTES_24
                                            - FDCAN_DATA_BYTES_32
                                            - FDCAN_DATA_BYTES_48
                                            - FDCAN_DATA_BYTES_64   */
    
    uint32_t TxFifoQueueMode;           /* Tx FIFO/Queue Mode selection. 
                                            This parameter must be one of the following values:
                                            - FDCAN_TX_FIFO_MODE 
                                            - FDCAN_TX_QUEUE_MODE  */
    uint32_t TxFifoQueueSize;           /* Specifies the number of Tx Buffers used for Tx FIFO/Queue.
                                            This parameter must be a value between 0 and 32. */
    FDCAN_MsgRamType *pMsgInfo;         /* Pointer to the message info block used for current FDCANx . */
    FunctionalState AutoRetransmission; /* Enable or disable the automatic retransmission mode.
                                            This parameter must be set to ENABLE or DISABLE. */
    FunctionalState TransmitPause;      /* Enable or disable the Transmit Pause feature.
                                            This parameter must be set to ENABLE or DISABLE. */
    FunctionalState ProtocolException;  /* Enable or disable the Protocol Exception Handling.
                                            This parameter must be set to ENABLE or DISABLE. */
} FDCAN_InitType;

/** FDCAN filter structure definition **/
typedef struct
{
    uint32_t IdType;            /* Specifies the identifier type.
                                    This parameter must be one of the following values:
                                    - FDCAN_STANDARD_ID
                                    - FDCAN_EXTENDED_ID   */
    uint32_t FilterIndex;       /* Specifies the filter which will be initialized. 
                                    This parameter must be a value between:
                                    - 0 and 127, if IdType is FDCAN_STANDARD_ID
                                    - 0 and 63, if IdType is FDCAN_EXTENDED_ID   */
    uint32_t FilterType;        /* Specifies the filter type. 
                                    This parameter must be one of the following values:
                                    - FDCAN_FILTER_RANGE        
                                    - FDCAN_FILTER_DUAL         
                                    - FDCAN_FILTER_MASK         
                                    - FDCAN_FILTER_RANGE_NO_EIDM    */
    uint32_t FilterConfig;      /* Specifies the filter configuration. 
                                    This parameter must be one of the following values:
                                    -FDCAN_FILTER_DISABLE      
                                    -FDCAN_FILTER_TO_RXFIFO0   
                                    -FDCAN_FILTER_TO_RXFIFO1   
                                    -FDCAN_FILTER_REJECT       
                                    -FDCAN_FILTER_HP           
                                    -FDCAN_FILTER_TO_RXFIFO0_HP
                                    -FDCAN_FILTER_TO_RXFIFO1_HP
                                    -FDCAN_FILTER_TO_RXBUFFER       */
    uint32_t FilterID1;         /* Specifies the filter identification 1. 
                                    This parameter must be a value between:
                                    - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                    - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID   */
    uint32_t FilterID2;         /* Specifies the filter identification 2. 
                                    This parameter must be a value between:
                                    - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                    - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID  
                                    This parameter is ignored if FilterConfig is set to FDCAN_FILTER_TO_RXBUFFER. */
    uint32_t RxBufferIndex;     /* Specifies the index of Rx buffer in which the matching message will be stored.
                                    This parameter must be a value between 0 and 63.
                                    And it is ignored if FilterConfig is not FDCAN_FILTER_TO_RXBUFFER  */
} FDCAN_FilterType;


/** FDCAN Tx buffer header structure definition **/
typedef struct
{
    uint32_t IdType;        /* Specifies the identifier type for the message that will be transmitted. 
                                This parameter must be one of the following values:
                                - FDCAN_STANDARD_ID
                                - FDCAN_EXTENDED_ID   */
    uint32_t ID;            /* Specifies the identifier. 
                                This parameter must be a value between:
                                - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID  */
    uint32_t TxFrameType;   /* Specifies the frame type of the message that will be transmitted. 
                                This parameter must be one of the following values:
                                - FDCAN_DATA_FRAME  
                                - FDCAN_REMOTE_FRAME   */
    uint32_t DataLength;    /* Specifies the length of the data frame that will be transmitted. 
                                This parameter must be one of the following values:
                                - FDCAN_DLC_BYTES_0 
                                - FDCAN_DLC_BYTES_1 
                                - FDCAN_DLC_BYTES_2 
                                - FDCAN_DLC_BYTES_3 
                                - FDCAN_DLC_BYTES_4 
                                - FDCAN_DLC_BYTES_5 
                                - FDCAN_DLC_BYTES_6 
                                - FDCAN_DLC_BYTES_7 
                                - FDCAN_DLC_BYTES_8 
                                - FDCAN_DLC_BYTES_12
                                - FDCAN_DLC_BYTES_16
                                - FDCAN_DLC_BYTES_20
                                - FDCAN_DLC_BYTES_24
                                - FDCAN_DLC_BYTES_32
                                - FDCAN_DLC_BYTES_48
                                - FDCAN_DLC_BYTES_64   */
    uint32_t ErrorState;    /* Specifies the error state indicator. 
                                This parameter must be one of the following values:
                                - FDCAN_ESI_ACTIVE 
                                - FDCAN_ESI_PASSIVE   */
    uint32_t BitRateSwitch; /* Specifies whether the data frame transmitted with or without bit rate switching.  
                                This parameter must be one of the following values:
                                - FDCAN_BRS_OFF
                                - FDCAN_BRS_ON    */
    uint32_t FDFormat;      /* Specifies whether the Tx frame transmitted in classic or FD format. 
                                This parameter must be one of the following values:
                                - FDCAN_CLASSIC_CAN
                                - FDCAN_FD_CAN        */
    uint32_t TxEventFifo;   /* Specifies the event FIFO control. 
                                This parameter must be one of the following values:
                                - FDCAN_NO_TX_EVENTS   
                                - FDCAN_STORE_TX_EVENTS   */
    uint32_t MsgMarker;     /* Specifies the message marker copied into Tx Event FIFO element.
                                This parameter must be a value between 0 and 0xFF   */
} FDCAN_TxHeaderType;

/** FDCAN Rx header structure definition **/
typedef struct
{
    uint32_t IdType;        /* Specifies the identifier type of the received message.
                                This parameter must be one of the following values:
                                - FDCAN_STANDARD_ID
                                - FDCAN_EXTENDED_ID   */
    uint32_t ID;            /* Specifies the identifier type for the message that will be transmitted. 
                                This parameter must be a value between:
                                - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID  */
    uint32_t RxFrameType;   /* Specifies the the received message frame type.
                                This parameter must be one of the following values:
                                - FDCAN_DATA_FRAME  
                                - FDCAN_REMOTE_FRAME   */
    uint32_t DataLength;    /* Specifies the received frame length.
                                This parameter must be one of the following values:
                                - FDCAN_DLC_BYTES_0 
                                - FDCAN_DLC_BYTES_1 
                                - FDCAN_DLC_BYTES_2 
                                - FDCAN_DLC_BYTES_3 
                                - FDCAN_DLC_BYTES_4 
                                - FDCAN_DLC_BYTES_5 
                                - FDCAN_DLC_BYTES_6 
                                - FDCAN_DLC_BYTES_7 
                                - FDCAN_DLC_BYTES_8 
                                - FDCAN_DLC_BYTES_12
                                - FDCAN_DLC_BYTES_16
                                - FDCAN_DLC_BYTES_20
                                - FDCAN_DLC_BYTES_24
                                - FDCAN_DLC_BYTES_32
                                - FDCAN_DLC_BYTES_48
                                - FDCAN_DLC_BYTES_64   */
    uint32_t ErrorState;    /* Specifies the error state indicator.
                                This parameter must be one of the following values:
                                - FDCAN_ESI_ACTIVE 
                                - FDCAN_ESI_PASSIVE   */
    uint32_t BitRateSwitch; /* Specifies whether the Rx frame is received with or without bit
                                This parameter must be one of the following values:
                                - FDCAN_BRS_OFF
                                - FDCAN_BRS_ON    */
    uint32_t FDFormat;      /* Specifies whether the Rx frame is received in classic or FD
                                This parameter must be one of the following values:
                                - FDCAN_CLASSIC_CAN
                                - FDCAN_FD_CAN        */
    uint32_t RxTimestamp;   /* Specifies the timestamp counter value captured on start of frame reception.
                                This parameter must be a value between 0 and 0xFFFF  */
    uint32_t FilterIndex;   /* Specifies the index of matching Rx acceptance filter element.
                                This parameter must be a value between:
                                - 0 and 127, if IdType is FDCAN_STANDARD_ID
                                - 0 and 63, if IdType is FDCAN_EXTENDED_ID  */
    uint32_t Matching;      /* Specifies whether the accepted frame did not match any Rx filter.
                                This parameter must be one of the following values:
                                - FDCAN_ACCEPT_MACHING_FIDX
                                - FDCAN_ACCEPT_NON_MATCHING   */

} FDCAN_RxHeaderType;

/** FDCAN Tx event FIFO structure definition **/
typedef struct
{
    uint32_t IdType;        /* Specifies the identifier type for the message that will be transmitted. 
                                This parameter must be one of the following values:
                                - FDCAN_STANDARD_ID
                                - FDCAN_EXTENDED_ID   */
    uint32_t ID;            /* Specifies the identifier. 
                                This parameter must be a value between:
                                - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID  */
    uint32_t TxFrameType;   /* Specifies the frame type of the message that will be transmitted. 
                                This parameter must be one of the following values:
                                - FDCAN_DATA_FRAME  
                                - FDCAN_REMOTE_FRAME   */
    uint32_t DataLength;    /* Specifies the length of the data frame that will be transmitted. 
                                This parameter must be one of the following values:
                                - FDCAN_DLC_BYTES_0 
                                - FDCAN_DLC_BYTES_1 
                                - FDCAN_DLC_BYTES_2 
                                - FDCAN_DLC_BYTES_3 
                                - FDCAN_DLC_BYTES_4 
                                - FDCAN_DLC_BYTES_5 
                                - FDCAN_DLC_BYTES_6 
                                - FDCAN_DLC_BYTES_7 
                                - FDCAN_DLC_BYTES_8 
                                - FDCAN_DLC_BYTES_12
                                - FDCAN_DLC_BYTES_16
                                - FDCAN_DLC_BYTES_20
                                - FDCAN_DLC_BYTES_24
                                - FDCAN_DLC_BYTES_32
                                - FDCAN_DLC_BYTES_48
                                - FDCAN_DLC_BYTES_64   */
    uint32_t ErrorState;    /* Specifies the error state indicator. 
                                This parameter must be one of the following values:
                                - FDCAN_ESI_ACTIVE 
                                - FDCAN_ESI_PASSIVE   */
    uint32_t BitRateSwitch; /* Specifies whether the data frame transmitted with or without bit rate switching.  
                                This parameter must be one of the following values:
                                - FDCAN_BRS_OFF
                                - FDCAN_BRS_ON    */
    uint32_t FDFormat;      /* Specifies whether the Tx frame transmitted in classic or FD format. 
                                This parameter must be one of the following values:
                                - FDCAN_CLASSIC_CAN
                                - FDCAN_FD_CAN        */
    uint32_t TxTimestamp;   /* Specifies the timestamp counter value captured on start of frame transmission.
                                This parameter must be a value between 0 and 0xFFFF  */
    uint32_t MsgMarker;     /* Specifies the message marker copied from Tx buffer.
                                This parameter must be a value between 0 and 0xFF                */
    uint32_t EventType;     /* Specifies the event type.
                                This parameter must be one of the following values:
                                - FDCAN_TX_EVENT            
                                - FDCAN_TX_IN_SPITE_OF_ABORT   */
} FDCAN_TxEventFifoType;

/** FDCAN High Priority Message Status structure definition **/
typedef struct
{
    uint32_t FilterList;    /* Specifies the filter list of the matching filter element.
                                This parameter can be one of the following values:
                                - FDCAN_HP_STANDARD_FILTER_LIST
                                - FDCAN_HP_EXTENDED_FILTER_LIST  */
    uint32_t FilterIndex;   /* Specifies the index of matching filter element.
                                This parameter can be a value between:
                                - 0 and 127, if FilterList is FDCAN_HP_STANDARD_FILTER_LIST
                                - 0 and 63, if FilterList is FDCAN_HP_EXTENDED_FILTER_LIST  */
    uint32_t MsgStore;      /* Specifies the HP Message Storage.
                                This parameter can be one of the following values:
                                - FDCAN_HP_STORAGE_NO_FIFO 
                                - FDCAN_HP_STORAGE_MSG_LOST
                                - FDCAN_HP_STORAGE_RXFIFO0 
                                - FDCAN_HP_STORAGE_RXFIFO1    */
    uint32_t MsgIndex;      /* Specifies the Index of Rx FIFO element to which the message was stored.
                                This parameter is valid only when MessageStorage is one of the following values
                                - FDCAN_HP_STORAGE_RXFIFO0
                                - FDCAN_HP_STORAGE_RXFIFO1                                 */
} FDCAN_HpMsgStatus;

/** FDCAN Protocol Status structure definition **/
typedef struct
{
    uint32_t LastError;     /* Specifies the type of the last error that occurred on the FDCAN bus.
                                This parameter can be one of the following values:
                                - FDCAN_LAST_ERROR_NONE     
                                - FDCAN_LAST_ERROR_STUFF    
                                - FDCAN_LAST_ERROR_FORM     
                                - FDCAN_LAST_ERROR_ACK      
                                - FDCAN_LAST_ERROR_BIT1     
                                - FDCAN_LAST_ERROR_BIT0     
                                - FDCAN_LAST_ERROR_CRC      
                                - FDCAN_LAST_ERROR_NO_CHANGE   */
    uint32_t LastDataError; /* Specifies the type of the last error that occurred in the data phase of a CAN FD frame.
                                This parameter can be one of the following values:
                                - FDCAN_LAST_DATA_ERROR_NONE     
                                - FDCAN_LAST_DATA_ERROR_STUFF    
                                - FDCAN_LAST_DATA_ERROR_FORM     
                                - FDCAN_LAST_DATA_ERROR_ACK      
                                - FDCAN_LAST_DATA_ERROR_BIT1     
                                - FDCAN_LAST_DATA_ERROR_BIT0     
                                - FDCAN_LAST_DATA_ERROR_CRC      
                                - FDCAN_LAST_DATA_ERROR_NO_CHANGE   */
    uint32_t Activity;      /* Specifies the FDCAN module communication state.
                                This parameter can be one of the following values:
                                - FDCAN_COM_STATE_SYNC
                                - FDCAN_COM_STATE_IDLE
                                - FDCAN_COM_STATE_RX  
                                - FDCAN_COM_STATE_TX  */
    uint32_t Error;         /* Specifies the FDCAN module error status.
                                This parameter can be one of the following values:
                                - FDCAN_ERROR_ACTIVE
                                - FDCAN_ERROR_PASSIVE  */
    uint32_t Warning;       /* Specifies the FDCAN module warning status.
                                This parameter can be one of the following values:
                                - FDCAN_WARNING_BELOW_96
                                - FDCAN_WARNING_REACH_96  */
    uint32_t BusOff;        /* Specifies the FDCAN module Bus_Off status.
                                This parameter can be one of the following values:
                                - FDCAN_BUS_ON
                                - FDCAN_BUS_OFF  */
    uint32_t RxESIflag;     /* Specifies ESI flag of last received CAN FD message.
                                This parameter can be one of the following values:
                                - FDCAN_ESI_NOT_SET
                                - FDCAN_ESI_SET  */
    uint32_t RxBRSflag;     /* Specifies BRS flag of last received CAN FD message.
                                This parameter can be one of the following values:
                                - FDCAN_BRS_NOT_SET
                                - FDCAN_BRS_SET  */
    uint32_t RxFDFflag;     /* Specifies if CAN FD message (FDF flag set) has been received since last protocol status.
                                This parameter can be one of the following values:
                                - FDCAN_FDMSG_NOT_RECEIVED
                                - FDCAN_FDMSG_RECEIVED  */
    uint32_t Exception;     /* Specifies the FDCAN module Protocol Exception status.
                                This parameter can be one of the following values:
                                - FDCAN_NO_EXCEPTION
                                - FDCAN_HAVE_EXCEPTION  */
    uint32_t TDCvalue;      /* Specifies the Transmitter Delay Compensation Value.
                                    This parameter can be a value between 0 and 127         */

} FDCAN_ProtocolStatus;

/**FDCAN Error Counters structure definition **/
typedef struct
{
    uint32_t TxErrorCnt;        /* Specifies the Transmit Error Counter Value.
                                    This parameter can be a value between 0 and 255                                         */
    uint32_t RxErrorCnt;        /* Specifies the Receive Error Counter Value.
                                    This parameter can be a value between 0 and 127                                         */
    uint32_t RxErrorPassive;    /* Specifies the Receive Error Passive status.
                                    This parameter can be one of the following values:
                                    - FDCAN_RX_ERROR_BELOW_128
                                    - FDCAN_RX_ERROR_REACH_128      */
    uint32_t ErrorLogging;      /* Specifies the Transmit/Receive error logging counter value.
                                    This parameter can be a value between 0 and 255.   */
} FDCAN_ErrorCounters;

/** FDCAN TT Init structure definition **/
typedef struct
{
    uint32_t OperationMode;     /* Specifies the FDCAN Operation Mode.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_COMMUNICATION_LEVEL1
                                    - FDCAN_TT_COMMUNICATION_LEVEL2
                                    - FDCAN_TT_COMMUNICATION_LEVEL0     */
    uint32_t GapEnable;         /* Specifies the FDCAN TT Operation.
                                    This parameter must be one of the following values:
                                    - FDCAN_STRICTLY_TT_OPERATION
                                    - FDCAN_EXT_EVT_SYNC_TT_OPERATION   */
    uint32_t TimeMaster;        /* Specifies whether the instance is a slave or a potential master.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_SLAVE
                                    - FDCAN_TT_POTENTIAL_MASTER         */
    uint32_t SyncDevLimit;      /* Specifies the Synchronization Deviation Limit SDL of the TUR
                                    numerator : TUR = (Numerator +/- SDL) / Denominator.
                                    With : SDL = 2^(SyncDevLimit+5).
                                    This parameter must be a value between 0 and 7                          */
    uint32_t InitRefTrigOffset; /* Specifies the Initial Reference Trigger Offset.
                                    This parameter must be a value between 0 and 127                        */
    uint32_t ExternalClkSync;   /* Enable or disable External Clock Synchronization.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_EXT_CLK_SYNC_DISABLE
                                    - FDCAN_TT_EXT_CLK_SYNC_ENABLE         
                                    This parameter is ignored if OperationMode is FDCAN_TT_COMMUNICATION_LEVEL1 */
    uint32_t AppWdgLimit;       /* Specifies the Application Watchdog Limit .
                                    This parameter must be a value between 0 and 255.
                                    This parameter is ignored if OperationMode is FDCAN_TT_COMMUNICATION_LEVEL0 */
    uint32_t GlobalTimeFilter;  /* Enable or disable Global Time Filtering.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_GLOB_TIME_FILT_DISABLE
                                    - FDCAN_TT_GLOB_TIME_FILT_ENABLE          
                                    This parameter is ignored if OperationMode is set to FDCAN_TT_COMMUNICATION_LEVEL1 */
    uint32_t ClockCalibration;  /* Enable or disable Automatic Clock Calibration.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_AUTO_CLK_CALIB_DISABLE
                                    - FDCAN_TT_AUTO_CLK_CALIB_ENABLE          
                                    This parameter is ignored if OperationMode is set to FDCAN_TT_COMMUNICATION_LEVEL1 */
    uint32_t EvtTrigPolarity;   /* Specifies the Event Trigger Polarity.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_EVT_TRIG_POL_RISING 
                                    - FDCAN_TT_EVT_TRIG_POL_FALLING         
                                    This parameter is ignored if OperationMode is set to FDCAN_TT_COMMUNICATION_LEVEL0 */
    uint32_t BasicCycles;       /* Specifies the number of basic cycles in the system matrix.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_CYCLES_PER_MATRIX_1 
                                    - FDCAN_TT_CYCLES_PER_MATRIX_2          
                                    - FDCAN_TT_CYCLES_PER_MATRIX_4 
                                    - FDCAN_TT_CYCLES_PER_MATRIX_8          
                                    - FDCAN_TT_CYCLES_PER_MATRIX_16
                                    - FDCAN_TT_CYCLES_PER_MATRIX_32         
                                    - FDCAN_TT_CYCLES_PER_MATRIX_64     */
    uint32_t CycleStartSync;    /* Enable or disable synchronization pulse output at pin fdcan1_soc.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_NO_SYNC_PULSE         
                                    - FDCAN_TT_SYNC_BASIC_CYCLE_START         
                                    - FDCAN_TT_SYNC_MATRIX_START          */
    uint32_t TxEnableWindow;    /* Specifies the length of Tx enable window in NTUs.
                                    This parameter must be a value between 1 and 16                         */
    uint32_t ExpTxTrigSize;     /* Specifies the number of expected Tx_Triggers in the system matrix.
                                    This is the sum of Tx_Triggers for exclusive, single arbitrating and
                                    merged arbitrating windows.
                                    This parameter must be a value between 0 and 4095                       */
    uint32_t TURNumerator;      /* Specifies the TUR (Time Unit Ratio) numerator.
                                    It is advised to set this parameter to the largest applicable value.
                                    This parameter must be a value between 0x10000 and 0x1FFFF              */
    uint32_t TURDenominator;    /* Specifies the TUR (Time Unit Ratio) denominator.
                                    This parameter must be a value between 0x0001 and 0x3FFF                */
    uint32_t TrigMemorySize;    /* Specifies the number of trigger memory elements.
                                    This parameter must be a value between 0 and 64                         */
    uint32_t StopWatchTrigSel;  /* Specifies the input to be used as stop watch trigger.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_STOP_WATCH_TRIGGER_0
                                    - FDCAN_TT_STOP_WATCH_TRIGGER_1         
                                    - FDCAN_TT_STOP_WATCH_TRIGGER_2         
                                    - FDCAN_TT_STOP_WATCH_TRIGGER_3      */
    uint32_t EventTrigSel;      /* Specifies the input to be used as event trigger.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_EVENT_TRIGGER_0
                                    - FDCAN_TT_EVENT_TRIGGER_1         
                                    - FDCAN_TT_EVENT_TRIGGER_2         
                                    - FDCAN_TT_EVENT_TRIGGER_3      */

} FDCAN_TT_InitType;

/** FDCAN Trigger structure definition **/
typedef struct
{
    uint32_t TriggerIndex;  /* Specifies the trigger which will be configured.
                                This parameter must be a number between 0 and 63                                 */
    uint32_t TimeMark;      /* Specifies the cycle time for which the trigger becomes active.
                                This parameter must be a number between 0 and 0xFFFF                             */
    uint32_t RepeatFactor;  /* Specifies the trigger repeat factor.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_REPEAT_EVERY_CYCLE     
                                    - FDCAN_TT_REPEAT_EVERY_2ND_CYCLE          
                                    - FDCAN_TT_REPEAT_EVERY_4TH_CYCLE          
                                    - FDCAN_TT_REPEAT_EVERY_8TH_CYCLE          
                                    - FDCAN_TT_REPEAT_EVERY_16TH_CYCLE         
                                    - FDCAN_TT_REPEAT_EVERY_32ND_CYCLE         
                                    - FDCAN_TT_REPEAT_EVERY_64TH_CYCLE      */
    uint32_t StartCycle;    /* Specifies the index of the first cycle in which the trigger becomes active.
                                This parameter must be a value between 0 and RepeatFactor.
                                This parameter is ignored if RepeatFactor is set to FDCAN_TT_REPEAT_EVERY_CYCLE. */
    uint32_t TmEventInt;    /* Enable or disable the internal time mark event.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_TM_NO_INTERNAL_EVENT 
                                    - FDCAN_TT_TM_GEN_INTERNAL_EVENT    */
    uint32_t TmEventExt;    /* Enable or disable the external time mark event.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_TM_NO_EXTERNAL_EVENT 
                                    - FDCAN_TT_TM_GEN_EXTERNAL_EVENT   */
    uint32_t TriggerType;   /* Specifies the trigger type.
                                    This parameter must be one of the following values:
                                    - FDCAN_TT_TX_REF_TRIGGER        
                                    - FDCAN_TT_TX_REF_TRIGGER_GAP    
                                    - FDCAN_TT_TX_TRIGGER_SINGLE     
                                    - FDCAN_TT_TX_TRIGGER_CONTINUOUS 
                                    - FDCAN_TT_TX_TRIGGER_ARBITRATION
                                    - FDCAN_TT_TX_TRIGGER_MERGED     
                                    - FDCAN_TT_WATCH_TRIGGER         
                                    - FDCAN_TT_WATCH_TRIGGER_GAP     
                                    - FDCAN_TT_RX_TRIGGER            
                                    - FDCAN_TT_TIME_BASE_TRIGGER     
                                    - FDCAN_TT_END_OF_LIST             */
    uint32_t FilterType;    /* Specifies the filter identifier type.
                                    This parameter must be one of the following values:
                                    - FDCAN_STANDARD_ID
                                    - FDCAN_EXTENDED_ID     */
    uint32_t TxBufferIndex; /* Specifies the index of the Tx buffer for which the trigger is valid.
                                    This parameter must be one of the following values:
                                    - FDCAN_TX_BUFFER0 
                                    - FDCAN_TX_BUFFER1 
                                    - FDCAN_TX_BUFFER2 
                                    - FDCAN_TX_BUFFER3 
                                    - FDCAN_TX_BUFFER4 
                                    - FDCAN_TX_BUFFER5 
                                    - FDCAN_TX_BUFFER6 
                                    - FDCAN_TX_BUFFER7 
                                    - FDCAN_TX_BUFFER8 
                                    - FDCAN_TX_BUFFER9 
                                    - FDCAN_TX_BUFFER10
                                    - FDCAN_TX_BUFFER11
                                    - FDCAN_TX_BUFFER12
                                    - FDCAN_TX_BUFFER13
                                    - FDCAN_TX_BUFFER14
                                    - FDCAN_TX_BUFFER15
                                    - FDCAN_TX_BUFFER16
                                    - FDCAN_TX_BUFFER17
                                    - FDCAN_TX_BUFFER18
                                    - FDCAN_TX_BUFFER19
                                    - FDCAN_TX_BUFFER20
                                    - FDCAN_TX_BUFFER21
                                    - FDCAN_TX_BUFFER22
                                    - FDCAN_TX_BUFFER23
                                    - FDCAN_TX_BUFFER24
                                    - FDCAN_TX_BUFFER25
                                    - FDCAN_TX_BUFFER26
                                    - FDCAN_TX_BUFFER27
                                    - FDCAN_TX_BUFFER28
                                    - FDCAN_TX_BUFFER29
                                    - FDCAN_TX_BUFFER30
                                    - FDCAN_TX_BUFFER31     */
    uint32_t FilterIndex;   /* Specifies the filter for which the trigger is valid.
                                This parameter must be a number between:
                                    - 0 and 127, if FilterType is FDCAN_STANDARD_ID
                                    - 0 and 63, if FilterType is FDCAN_EXTENDED_ID     */
} FDCAN_TriggerType;

/** FDCAN TT Operation Status structure definition **/
typedef struct
{
    uint32_t ErrorLevel;       /* Specifies the type of the TT operation error level.
                                    This parameter can be one of the following values:
                                    - FDCAN_TT_NO_ERROR    
                                    - FDCAN_TT_WARNING     
                                    - FDCAN_TT_ERROR       
                                    - FDCAN_TT_SEVERE_ERROR    */
    uint32_t MasterState;      /* Specifies the type of the TT master state.
                                    This parameter can be one of the following values:
                                    - FDCAN_TT_MASTER_OFF         
                                    - FDCAN_TT_TIME_SLAVE         
                                    - FDCAN_TT_BACKUP_TIME_MASTER 
                                    - FDCAN_TT_CURRENT_TIME_MASTER    */
    uint32_t SyncState;        /* Specifies the type of the TT synchronization state.
                                    This parameter can be one of the following values:
                                    - FDCAN_TT_OUT_OF_SYNC  
                                    - FDCAN_TT_SYNCHRONIZING
                                    - FDCAN_TT_IN_GAP       
                                    - FDCAN_TT_IN_SCHEDULE      */
    uint32_t GTimeQuality;     /* Specifies the Quality of Global Time Phase.
                                    This parameter is only relevant in Level 0 and Level 2, otherwise fixed to 0.
                                    This parameter can be:
                                    - FDCAN_TT_GTIME_NOT_VALID      
                                    - FDCAN_TT_GTIME_IN_MASTER_PHASE                                  */
    uint32_t ClockQuality;     /* Specifies the Quality of Clock Speed.
                                    This parameter is only relevant in Level 0 and Level 2, otherwise fixed to 1.
                                    This parameter can be:
                                    - FDCAN_TT_LOCAL_CLOCK_NOT_SYNC  
                                    - FDCAN_TT_SYNC_DEV_LESS_THAN_SDL          */
    uint32_t RefTrigOffset;    /* Specifies the Actual Reference Trigger Offset Value.
                                    This parameter can be a number between 0 and 0xFF      */
    uint32_t GTimeDiscPending; /* Specifies the Global Time Discontinuity State.
                                    This parameter can be:
                                    - FDCAN_TT_NO_GTIME_PENDING      
                                    - FDCAN_TT_WATI_GTIMESYNC_PRESENT                   */
    uint32_t GapFinished;      /* Specifies whether a Gap is finished.
                                    This parameter can be:
                                    - FDCAN_TT_GAP_RESET   
                                    - FDCAN_TT_GAP_FINISHED                             */
    uint32_t MasterPriority;   /* Specifies the Priority of actual Time Master.
                                    This parameter can be a number between 0 and 0x7      */
    uint32_t GapStarted;       /* Specifies whether a Gap is started.
                                    This parameter can be:
                                    - FDCAN_TT_NO_GAP     
                                    - FDCAN_TT_GAP_STARTED                                */
    uint32_t WaitForEvt;       /* Specifies whether a Gap is announced.
                                    This parameter can be:
                                    - FDCAN_TT_GAP_NOT_ANNOUNCED
                                    - FDCAN_TT_REF_MSG_RECEIVED         */
    uint32_t AppWdgEvt;        /* Specifies the Application Watchdog State.
                                    This parameter can be:
                                    - FDCAN_TT_WATCHDOG_VALID  
                                    - FDCAN_TT_WATCHDOG_INVALID                           */
    uint32_t ECSPending;       /* Specifies the External Clock Synchronization State.
                                    This parameter can be:
                                    - FDCAN_TT_NO_EXT_CLOCK_SYNC  
                                    - FDCAN_TT_WAIT_EXT_CLOCK_SYNC           */
    uint32_t PhaseLock;        /* Specifies the Phase Lock State.
                                    This parameter can be:
                                    - FDCAN_TT_PHASE_OUT_OF_RANGE
                                    - FDCAN_TT_PHASE_IN_RANGE       */
} FDCAN_TT_Status;


/** FDCAN timeout constant define **/
#define FDCAN_TIMEOUT_VALUE         (600000U)    /*10ms*/
#define FDCAN_TIMEOUT_COUNT         (50U)

/*** FDCAN message ram define ***/

/*** FDCAN Message ram size define ***/
#define FDCAN_MESSAGE_RAM_SIZE      (0x1000UL*4UL) /* max 0x1000 words */

/*** FDCAN Message element size define, conuted in word(32bit) ***/
#define FDCAN_STD_FILTER_WORDS      (1U)
#define FDCAN_EXT_FILTER_WORDS      (2U)
#define FDCAN_TX_EVENT_FIFO_WORDS   (2U)
#define FDCAN_TT_MEMORY_WORDS       (2U)

/*** FD CAN message element bit define for Rx FIFO0/1, Rx buffer, Tx buffer, and Tx evnet fifo  ***/
/** Element 1st byte define, used for both Rx FIFO0/1, Rx buffer, Tx buffer, and Tx evnet fifo   **/
#define FDCAN_ELEMENT_ESI           ((uint32_t)0x80000000U)  /* Error State Indicator       */
#define FDCAN_ELEMENT_XTD           ((uint32_t)0x40000000U)  /* Extended Identifier         */
#define FDCAN_ELEMENT_RTR           ((uint32_t)0x20000000U)  /* Remote Transmission Request */
#define FDCAN_ELEMENT_EXTID         ((uint32_t)0x1FFFFFFFU)  /* Extended Identifier         */
#define FDCAN_ELEMENT_STDID         ((uint32_t)0x1FFC0000U)  /* Standard Identifier         */

/** Part of element 2nd byte define, used for both Rx FIFO0/1, Rx buffer, Tx buffer, and Tx evnet fifo   **/
#define FDCAN_ELEMENT_FDF           ((uint32_t)0x00200000U)  /* FD Format                   */
#define FDCAN_ELEMENT_BRS           ((uint32_t)0x00100000U)  /* Bit Rate Switch             */
#define FDCAN_ELEMENT_DLC           ((uint32_t)0x000F0000U)  /* Data Length Code            */

/** Part of element 2nd byte define, used for both Rx FIFO0/1, Rx buffer  **/
#define FDCAN_ELEMENT_ANMF          ((uint32_t)0x80000000U)  /* Accepted Non-matching Frame */
#define FDCAN_ELEMENT_FIDX          ((uint32_t)0x7F000000U)  /* Filter Index                */

/** Part of element 2nd byte define, used for both Rx FIFO0/1, Rx buffer, and Tx evnet fifo   **/
#define FDCAN_ELEMENT_TS            ((uint32_t)0x0000FFFFU)  /* Timestamp                   */

/** Part of element 2nd byte define, used for Tx buffer and Tx evnet fifo **/
#define FDCAN_ELEMENT_MM            ((uint32_t)0xFF000000U)  /* Message Marker              */

/** Part of element 2nd byte define, just used for Tx buffer  **/
#define FDCAN_ELEMENT_EFC           ((uint32_t)0x00800000U)  /* Event FIFO Control          */

/** Part of element 2nd byte define, just used for Tx evnet fifo **/
#define FDCAN_ELEMENT_ET            ((uint32_t)0x00C00000U)  /* Event type                  */

/** Bit offset define **/
#define FDCAN_ELEMENT_STDID_OFFSET  (REG_BIT18_OFFSET)
#define FDCAN_ELEMENT_FIDX_OFFSET   (REG_BIT24_OFFSET)
#define FDCAN_ELEMENT_DLC_OFFSET    (REG_BIT16_OFFSET)
#define FDCAN_ELEMENT_MM_OFFSET     (REG_BIT24_OFFSET)

/** FDCAN Error State Indicator, used for elememnt FDCAN_ELEMENT_ESI **/
#define FDCAN_ESI_ACTIVE            ((uint32_t)0x00000000U)  /* Transmitting node is error active  */
#define FDCAN_ESI_PASSIVE           (FDCAN_ELEMENT_ESI)     /* Transmitting node is error passive */

/** ID type define, used for elememnt FDCAN_ELEMENT_XTD and register TTRMC **/
#define FDCAN_STANDARD_ID           ((uint32_t)0x00000000U)  /* Standard ID element */
#define FDCAN_EXTENDED_ID           (FDCAN_ELEMENT_XTD)     /* Extended ID element */

/** Standard frame type define, used for elememnt FDCAN_ELEMENT_RTR **/
#define FDCAN_DATA_FRAME            ((uint32_t)0x00000000U)  /* Data frame   */
#define FDCAN_REMOTE_FRAME          (FDCAN_ELEMENT_RTR)     /* Remote frame */

/** FDCAN format define, used for elememnt FDCAN_ELEMENT_FDF **/
#define FDCAN_CLASSIC_CAN           ((uint32_t)0x00000000U)  /* Frame transmitted/received in Classic CAN format */
#define FDCAN_FD_CAN                (FDCAN_ELEMENT_FDF)     /* Frame transmitted/received in FDCAN format       */

/** FDCAN Bit Rate Switching define, used for elememnt FDCAN_ELEMENT_BRS **/
#define FDCAN_BRS_OFF               ((uint32_t)0x00000000U)  /* FDCAN frames transmitted/received without bit rate switching */
#define FDCAN_BRS_ON                (FDCAN_ELEMENT_BRS)     /* FDCAN frames transmitted/received with bit rate switching    */

/** FDCAN Data Length Code define, used for element FDCAN_ELEMENT_DLC **/
#define FDCAN_DLC_BYTES_0           ((uint32_t)0x00000000U)  /* 0 bytes data field  */
#define FDCAN_DLC_BYTES_1           ((uint32_t)0x00010000U)  /* 1 bytes data field  */
#define FDCAN_DLC_BYTES_2           ((uint32_t)0x00020000U)  /* 2 bytes data field  */
#define FDCAN_DLC_BYTES_3           ((uint32_t)0x00030000U)  /* 3 bytes data field  */
#define FDCAN_DLC_BYTES_4           ((uint32_t)0x00040000U)  /* 4 bytes data field  */
#define FDCAN_DLC_BYTES_5           ((uint32_t)0x00050000U)  /* 5 bytes data field  */
#define FDCAN_DLC_BYTES_6           ((uint32_t)0x00060000U)  /* 6 bytes data field  */
#define FDCAN_DLC_BYTES_7           ((uint32_t)0x00070000U)  /* 7 bytes data field  */
#define FDCAN_DLC_BYTES_8           ((uint32_t)0x00080000U)  /* 8 bytes data field  */
#define FDCAN_DLC_BYTES_12          ((uint32_t)0x00090000U)  /* 12 bytes data field */
#define FDCAN_DLC_BYTES_16          ((uint32_t)0x000A0000U)  /* 16 bytes data field */
#define FDCAN_DLC_BYTES_20          ((uint32_t)0x000B0000U)  /* 20 bytes data field */
#define FDCAN_DLC_BYTES_24          ((uint32_t)0x000C0000U)  /* 24 bytes data field */
#define FDCAN_DLC_BYTES_32          ((uint32_t)0x000D0000U)  /* 32 bytes data field */
#define FDCAN_DLC_BYTES_48          ((uint32_t)0x000E0000U)  /* 48 bytes data field */
#define FDCAN_DLC_BYTES_64          (FDCAN_ELEMENT_DLC)     /* 64 bytes data field */

/** FDCAN accept non-natching frame define, used for element FDCAN_ELEMENT_ANMF **/
#define FDCAN_ACCEPT_MACHING_FIDX   ((uint32_t)0x00000000U)  /* Accepted frame matches the ID indecated by FIDX */
#define FDCAN_ACCEPT_NON_MATCHING   (FDCAN_ELEMENT_ANMF)    /* Accepted frame does't match and ID */

/** FDCAN Event FIFO control define, used for element **/
#define FDCAN_NO_TX_EVENTS          ((uint32_t)0x00000000U)  /* Do not store Tx events */
#define FDCAN_STORE_TX_EVENTS       (FDCAN_ELEMENT_EFC)     /* Store Tx events        */

/** FDCAN Event Type, used for element FDCAN_ELEMENT_ET **/
#define FDCAN_TX_EVENT             ((uint32_t)0x00400000U)   /* Tx event                              */
#define FDCAN_TX_IN_SPITE_OF_ABORT ((uint32_t)0x00800000U)   /* Transmission in spite of cancellation */

/*** FD CAN message element bit define for Standard and Extended message ID filter  ***/
/** FDCAN Filter element define, used for Standard filter **/
#define FDCAN_ELEMENT_SFT           ((uint32_t)0xC0000000U)  /* Standard Filter Type */
#define FDCAN_ELEMENT_SFEC          ((uint32_t)0x38000000U)  /* Standard Filter Element Configuration */
#define FDCAN_ELEMENT_SFID1         ((uint32_t)0x07FF0000U)  /* Standard Filter ID 1 */
#define FDCAN_ELEMENT_SFID2         ((uint32_t)0x000007FFU)  /* Standard Filter ID 2 */

/** FDCAN Filter element define, used for Externded filter **/
/* Byte 0 */
#define FDCAN_ELEMENT_EFEC          ((uint32_t)0xE0000000U)  /* Externded Filter Element Configuration */
#define FDCAN_ELEMENT_EFID1         ((uint32_t)0x1FFFFFFFU)  /* Externded Filter ID 1 */

/* Byte 1 */
#define FDCAN_ELEMENT_EFT           ((uint32_t)0xC0000000U)  /* Externded Filter Type */
#define FDCAN_ELEMENT_EFID2         ((uint32_t)0x1FFFFFFFU)  /* Externded Filter ID 1 */

/** FDCAN Filter Type, used for both FDCAN_ELEMENT_EFT and FDCAN_ELEMENT_SFT **/
#define FDCAN_FILTER_RANGE          ((uint32_t)0x00000000U)   /* Range filter from FilterID1 to FilterID2                        */
#define FDCAN_FILTER_DUAL           ((uint32_t)0x40000000U)   /* Dual ID filter for FilterID1 or FilterID2                       */
#define FDCAN_FILTER_MASK           ((uint32_t)0x80000000U)   /* Classic filter: FilterID1 = filter, FilterID2 = mask            */
#define FDCAN_FILTER_RANGE_NO_EIDM  (FDCAN_ELEMENT_EFT)      /* Range filter from FilterID1 to FilterID2, EIDM mask not applied */

/** FDCAN Filter Configuration, usd for FDCAN_ELEMENT_EFEC and FDCAN_ELEMENT_SFEC, it must be used with bit offset **/
#define FDCAN_FILTER_DISABLE        ((uint32_t)0x0000000U)   /* Disable filter element                                    */
#define FDCAN_FILTER_TO_RXFIFO0     ((uint32_t)0x0000001U)   /* Store in Rx FIFO 0 if filter matches                      */
#define FDCAN_FILTER_TO_RXFIFO1     ((uint32_t)0x0000002U)   /* Store in Rx FIFO 1 if filter matches                      */
#define FDCAN_FILTER_REJECT         ((uint32_t)0x0000003U)   /* Reject ID if filter matches                               */
#define FDCAN_FILTER_HP             ((uint32_t)0x0000004U)   /* Set high priority if filter matches                       */
#define FDCAN_FILTER_TO_RXFIFO0_HP  ((uint32_t)0x0000005U)   /* Set high priority and store in FIFO 0 if filter matches   */
#define FDCAN_FILTER_TO_RXFIFO1_HP  ((uint32_t)0x0000006U)   /* Set high priority and store in FIFO 1 if filter matches   */
#define FDCAN_FILTER_TO_RXBUFFER    ((uint32_t)0x0000007U)   /* Store into Rx Buffer, configuration of FilterType ignored */

/** Bit offset define **/
#define  FDCAN_ELEMENT_SFEC_OFFSET  (REG_BIT27_OFFSET)
#define  FDCAN_ELEMENT_ID1_OFFSET   (REG_BIT16_OFFSET)
#define  FDCAN_ELEMENT_EFEC_OFFSET  (REG_BIT29_OFFSET)

/*** FD CAN message element bit define for Trigger Memory  ***/
/* Byte 0 */
#define FDCAN_ELEMENT_TM            ((uint32_t)0xFFFF0000U)  /* Time Mark                */
#define FDCAN_ELEMENT_CC            ((uint32_t)0x00007F00U)  /* Cycle Code               */
#define FDCAN_ELEMENT_TMIN          ((uint32_t)0x00000020U)  /* Internal Time Mark Event */
#define FDCAN_ELEMENT_TMEX          ((uint32_t)0x00000010U)  /* External Time Mark Event */
#define FDCAN_ELEMENT_TYPE          ((uint32_t)0x0000000FU)  /* Trigger Type             */

/* Byte 1 */
#define FDCAN_ELEMENT_FTYPE         ((uint32_t)0x00800000U)  /* Filter Type          */
#define FDCAN_ELEMENT_MNR           ((uint32_t)0x007F0000U)  /* Message Number       */
#define FDCAN_ELEMENT_MSC           ((uint32_t)0x00000007U)  /* Message Status Count */

/** Bit offset define **/
#define  FDCAN_ELEMENT_TM_OFFSET    (REG_BIT16_OFFSET)
#define  FDCAN_ELEMENT_CC_OFFSET    (REG_BIT8_OFFSET)
#define  FDCAN_ELEMENT_MNR_OFFSET   (REG_BIT16_OFFSET)

/** FDCAN TT trigger valid cycle code, used for both FDCAN_ELEMENT_CC and register TTTMK **/
#define FDCAN_TT_REPEAT_EVERY_CYCLE         ((uint32_t)0x00000000U) /* Trigger valid for all cycles   */
#define FDCAN_TT_REPEAT_EVERY_2ND_CYCLE     ((uint32_t)0x00000002U) /* Trigger valid every 2nd cycle  */
#define FDCAN_TT_REPEAT_EVERY_4TH_CYCLE     ((uint32_t)0x00000004U) /* Trigger valid every 4th cycle  */
#define FDCAN_TT_REPEAT_EVERY_8TH_CYCLE     ((uint32_t)0x00000008U) /* Trigger valid every 8th cycle  */
#define FDCAN_TT_REPEAT_EVERY_16TH_CYCLE    ((uint32_t)0x00000010U) /* Trigger valid every 16th cycle */
#define FDCAN_TT_REPEAT_EVERY_32ND_CYCLE    ((uint32_t)0x00000020U) /* Trigger valid every 32nd cycle */
#define FDCAN_TT_REPEAT_EVERY_64TH_CYCLE    ((uint32_t)0x00000040U) /* Trigger valid every 64th cycle */

/** FDCAN TT time mark event internal, used for FDCAN_ELEMENT_TMIN **/
#define FDCAN_TT_TM_NO_INTERNAL_EVENT   ((uint32_t)0x00000000U) /* No action                                               */
#define FDCAN_TT_TM_GEN_INTERNAL_EVENT  (FDCAN_ELEMENT_TMIN)    /* Internal event is generated when trigger becomes active */

/** FDCAN TT time mark event external, used for FDCAN_ELEMENT_TMEX **/
#define FDCAN_TT_TM_NO_EXTERNAL_EVENT   ((uint32_t)0x00000000U) /* No action                                                       */
#define FDCAN_TT_TM_GEN_EXTERNAL_EVENT  (FDCAN_ELEMENT_TMEX)    /* External event (pulse) is generated when trigger becomes active */

/** FDCAN TT trigger type,used for FDCAN_ELEMENT_TYPE **/
#define FDCAN_TT_TX_REF_TRIGGER         ((uint32_t)0x00000000U)  /* Transmit reference message in strictly time-triggered operation                                                     */
#define FDCAN_TT_TX_REF_TRIGGER_GAP     ((uint32_t)0x00000001U)  /* Transmit reference message in external event-synchronized time-triggered operation                                  */
#define FDCAN_TT_TX_TRIGGER_SINGLE      ((uint32_t)0x00000002U)  /* Start a single transmission in an exclusive time window                                                             */
#define FDCAN_TT_TX_TRIGGER_CONTINUOUS  ((uint32_t)0x00000003U)  /* Start a continuous transmission in an exclusive time window                                                         */
#define FDCAN_TT_TX_TRIGGER_ARBITRATION ((uint32_t)0x00000004U)  /* Start a transmission in an arbitration time window                                                                  */
#define FDCAN_TT_TX_TRIGGER_MERGED      ((uint32_t)0x00000005U)  /* Start a merged arbitration window                                                                                   */
#define FDCAN_TT_WATCH_TRIGGER          ((uint32_t)0x00000006U)  /* Check for missing reference messages in strictly time-triggered operation                                           */
#define FDCAN_TT_WATCH_TRIGGER_GAP      ((uint32_t)0x00000007U)  /* Check for missing reference messages in external event-synchronized time-triggered operation                        */
#define FDCAN_TT_RX_TRIGGER             ((uint32_t)0x00000008U)  /* Check for the reception of periodic messages in exclusive time windows                                              */
#define FDCAN_TT_TIME_BASE_TRIGGER      ((uint32_t)0x00000009U)  /* Generate internal/external events depending on TmEventInt/TmEventExt configuration                                  */
#define FDCAN_TT_END_OF_LIST            ((uint32_t)0x0000000AU)  /* Illegal trigger, to be assigned to the unused triggers after a FDCAN_TT_WATCH_TRIGGER or FDCAN_TT_WATCH_TRIGGER_GAP */

/** FDCAN TT trigger type,used for FDCAN_ELEMENT_FTYPE **/
#define FDCAN_FILTER_STANDARD_ID        ((uint32_t)0x00000000U)  /* Standard ID element */
#define FDCAN_FILTER_EXTENDED_ID        (FDCAN_ELEMENT_FTYPE)    /* Extended ID element */

/*** FDCAN register define ***/

/** FDCAN frame format define **/
#define FDCAN_FRAME_CLASSIC             ((uint32_t)0x00000000U)           /* Classic mode                      */
#define FDCAN_FRAME_FD_NO_BRS           (FDCAN_CCCR_FDOE)                 /* FD mode without BitRate Switching */
#define FDCAN_FRAME_FD_BRS              (FDCAN_CCCR_FDOE|FDCAN_CCCR_BRSE) /* FD mode with BitRate Switching    */

/** FDCAN operatioin mode define **/
#define FDCAN_MODE_NORMAL               ((uint32_t)0x00000000U)          /* Normal mode               */
#define FDCAN_MODE_RESTRICTED_OPERATION (FDCAN_CCCR_ASM)                 /* Restricted Operation mode */
#define FDCAN_MODE_BUS_MONITORING       (FDCAN_CCCR_MON)                 /* Bus Monitoring mode       */
#define FDCAN_MODE_INTERNAL_LOOPBACK    (FDCAN_CCCR_TEST|FDCAN_CCCR_MON) /* Internal LoopBack mode    */
#define FDCAN_MODE_EXTERNAL_LOOPBACK    (FDCAN_CCCR_TEST)                /* External LoopBack mode    */

/** FDCAN Tx FIFO and Tx Queue operation modes define **/
#define FDCAN_TX_FIFO_MODE              ((uint32_t)0x00000000U)      /* FIFO mode  */
#define FDCAN_TX_QUEUE_MODE             ((uint32_t)FDCAN_TXBC_TFQM) /* Queue mode */

/** FDCAN data field size define, conuted in words, used for both Rx FIFO0/1, Rx buffer, Tx buffer **/
#define FDCAN_DATA_BYTES_8              ((uint32_t)0x00000004U)  /* 8 bytes data field  */
#define FDCAN_DATA_BYTES_12             ((uint32_t)0x00000005U)  /* 12 bytes data field */
#define FDCAN_DATA_BYTES_16             ((uint32_t)0x00000006U)  /* 16 bytes data field */
#define FDCAN_DATA_BYTES_20             ((uint32_t)0x00000007U)  /* 20 bytes data field */
#define FDCAN_DATA_BYTES_24             ((uint32_t)0x00000008U)  /* 24 bytes data field */
#define FDCAN_DATA_BYTES_32             ((uint32_t)0x0000000AU)  /* 32 bytes data field */
#define FDCAN_DATA_BYTES_48             ((uint32_t)0x0000000EU)  /* 48 bytes data field */
#define FDCAN_DATA_BYTES_64             ((uint32_t)0x00000012U)  /* 64 bytes data field */

/** FDCAN FDCAN Tx Location bit define, used for TXBRP, TXBAR, TXBCR, TXBTO, TXBCF, TXBTIE, TXBCIE registers **/
#define FDCAN_TX_BUFFER0                (FDCAN_TXBRP_TRP0 ) /* Tx Buffer 0  bit */
#define FDCAN_TX_BUFFER1                (FDCAN_TXBRP_TRP1 ) /* Tx Buffer 1  bit */
#define FDCAN_TX_BUFFER2                (FDCAN_TXBRP_TRP2 ) /* Tx Buffer 2  bit */
#define FDCAN_TX_BUFFER3                (FDCAN_TXBRP_TRP3 ) /* Tx Buffer 3  bit */
#define FDCAN_TX_BUFFER4                (FDCAN_TXBRP_TRP4 ) /* Tx Buffer 4  bit */
#define FDCAN_TX_BUFFER5                (FDCAN_TXBRP_TRP5 ) /* Tx Buffer 5  bit */
#define FDCAN_TX_BUFFER6                (FDCAN_TXBRP_TRP6 ) /* Tx Buffer 6  bit */
#define FDCAN_TX_BUFFER7                (FDCAN_TXBRP_TRP7 ) /* Tx Buffer 7  bit */
#define FDCAN_TX_BUFFER8                (FDCAN_TXBRP_TRP8 ) /* Tx Buffer 8  bit */
#define FDCAN_TX_BUFFER9                (FDCAN_TXBRP_TRP9 ) /* Tx Buffer 9  bit */
#define FDCAN_TX_BUFFER10               (FDCAN_TXBRP_TRP10) /* Tx Buffer 10 bit */
#define FDCAN_TX_BUFFER11               (FDCAN_TXBRP_TRP11) /* Tx Buffer 11 bit */
#define FDCAN_TX_BUFFER12               (FDCAN_TXBRP_TRP12) /* Tx Buffer 12 bit */
#define FDCAN_TX_BUFFER13               (FDCAN_TXBRP_TRP13) /* Tx Buffer 13 bit */
#define FDCAN_TX_BUFFER14               (FDCAN_TXBRP_TRP14) /* Tx Buffer 14 bit */
#define FDCAN_TX_BUFFER15               (FDCAN_TXBRP_TRP15) /* Tx Buffer 15 bit */
#define FDCAN_TX_BUFFER16               (FDCAN_TXBRP_TRP16) /* Tx Buffer 16 bit */
#define FDCAN_TX_BUFFER17               (FDCAN_TXBRP_TRP17) /* Tx Buffer 17 bit */
#define FDCAN_TX_BUFFER18               (FDCAN_TXBRP_TRP18) /* Tx Buffer 18 bit */
#define FDCAN_TX_BUFFER19               (FDCAN_TXBRP_TRP19) /* Tx Buffer 19 bit */
#define FDCAN_TX_BUFFER20               (FDCAN_TXBRP_TRP20) /* Tx Buffer 20 bit */
#define FDCAN_TX_BUFFER21               (FDCAN_TXBRP_TRP21) /* Tx Buffer 21 bit */
#define FDCAN_TX_BUFFER22               (FDCAN_TXBRP_TRP22) /* Tx Buffer 22 bit */
#define FDCAN_TX_BUFFER23               (FDCAN_TXBRP_TRP23) /* Tx Buffer 23 bit */
#define FDCAN_TX_BUFFER24               (FDCAN_TXBRP_TRP24) /* Tx Buffer 24 bit */
#define FDCAN_TX_BUFFER25               (FDCAN_TXBRP_TRP25) /* Tx Buffer 25 bit */
#define FDCAN_TX_BUFFER26               (FDCAN_TXBRP_TRP26) /* Tx Buffer 26 bit */
#define FDCAN_TX_BUFFER27               (FDCAN_TXBRP_TRP27) /* Tx Buffer 27 bit */
#define FDCAN_TX_BUFFER28               (FDCAN_TXBRP_TRP28) /* Tx Buffer 28 bit */
#define FDCAN_TX_BUFFER29               (FDCAN_TXBRP_TRP29) /* Tx Buffer 29 bit */
#define FDCAN_TX_BUFFER30               (FDCAN_TXBRP_TRP30) /* Tx Buffer 30 bit */
#define FDCAN_TX_BUFFER31               (FDCAN_TXBRP_TRP31) /* Tx Buffer 31 bit */

/** FDCAN Rx buffer index define **/
#define FDCAN_RX_BUFFER0                ((uint32_t)0x00000000U)  /* Rx Buffer 0  */
#define FDCAN_RX_BUFFER1                ((uint32_t)0x00000001U)  /* Rx Buffer 1  */
#define FDCAN_RX_BUFFER2                ((uint32_t)0x00000002U)  /* Rx Buffer 2  */
#define FDCAN_RX_BUFFER3                ((uint32_t)0x00000003U)  /* Rx Buffer 3  */
#define FDCAN_RX_BUFFER4                ((uint32_t)0x00000004U)  /* Rx Buffer 4  */
#define FDCAN_RX_BUFFER5                ((uint32_t)0x00000005U)  /* Rx Buffer 5  */
#define FDCAN_RX_BUFFER6                ((uint32_t)0x00000006U)  /* Rx Buffer 6  */
#define FDCAN_RX_BUFFER7                ((uint32_t)0x00000007U)  /* Rx Buffer 7  */
#define FDCAN_RX_BUFFER8                ((uint32_t)0x00000008U)  /* Rx Buffer 8  */
#define FDCAN_RX_BUFFER9                ((uint32_t)0x00000009U)  /* Rx Buffer 9  */
#define FDCAN_RX_BUFFER10               ((uint32_t)0x0000000AU)  /* Rx Buffer 10 */
#define FDCAN_RX_BUFFER11               ((uint32_t)0x0000000BU)  /* Rx Buffer 11 */
#define FDCAN_RX_BUFFER12               ((uint32_t)0x0000000CU)  /* Rx Buffer 12 */
#define FDCAN_RX_BUFFER13               ((uint32_t)0x0000000DU)  /* Rx Buffer 13 */
#define FDCAN_RX_BUFFER14               ((uint32_t)0x0000000EU)  /* Rx Buffer 14 */
#define FDCAN_RX_BUFFER15               ((uint32_t)0x0000000FU)  /* Rx Buffer 15 */
#define FDCAN_RX_BUFFER16               ((uint32_t)0x00000010U)  /* Rx Buffer 16 */
#define FDCAN_RX_BUFFER17               ((uint32_t)0x00000011U)  /* Rx Buffer 17 */
#define FDCAN_RX_BUFFER18               ((uint32_t)0x00000012U)  /* Rx Buffer 18 */
#define FDCAN_RX_BUFFER19               ((uint32_t)0x00000013U)  /* Rx Buffer 19 */
#define FDCAN_RX_BUFFER20               ((uint32_t)0x00000014U)  /* Rx Buffer 20 */
#define FDCAN_RX_BUFFER21               ((uint32_t)0x00000015U)  /* Rx Buffer 21 */
#define FDCAN_RX_BUFFER22               ((uint32_t)0x00000016U)  /* Rx Buffer 22 */
#define FDCAN_RX_BUFFER23               ((uint32_t)0x00000017U)  /* Rx Buffer 23 */
#define FDCAN_RX_BUFFER24               ((uint32_t)0x00000018U)  /* Rx Buffer 24 */
#define FDCAN_RX_BUFFER25               ((uint32_t)0x00000019U)  /* Rx Buffer 25 */
#define FDCAN_RX_BUFFER26               ((uint32_t)0x0000001AU)  /* Rx Buffer 26 */
#define FDCAN_RX_BUFFER27               ((uint32_t)0x0000001BU)  /* Rx Buffer 27 */
#define FDCAN_RX_BUFFER28               ((uint32_t)0x0000001CU)  /* Rx Buffer 28 */
#define FDCAN_RX_BUFFER29               ((uint32_t)0x0000001DU)  /* Rx Buffer 29 */
#define FDCAN_RX_BUFFER30               ((uint32_t)0x0000001EU)  /* Rx Buffer 30 */
#define FDCAN_RX_BUFFER31               ((uint32_t)0x0000001FU)  /* Rx Buffer 31 */
#define FDCAN_RX_BUFFER32               ((uint32_t)0x00000020U)  /* Rx Buffer 32 */
#define FDCAN_RX_BUFFER33               ((uint32_t)0x00000021U)  /* Rx Buffer 33 */
#define FDCAN_RX_BUFFER34               ((uint32_t)0x00000022U)  /* Rx Buffer 34 */
#define FDCAN_RX_BUFFER35               ((uint32_t)0x00000023U)  /* Rx Buffer 35 */
#define FDCAN_RX_BUFFER36               ((uint32_t)0x00000024U)  /* Rx Buffer 36 */
#define FDCAN_RX_BUFFER37               ((uint32_t)0x00000025U)  /* Rx Buffer 37 */
#define FDCAN_RX_BUFFER38               ((uint32_t)0x00000026U)  /* Rx Buffer 38 */
#define FDCAN_RX_BUFFER39               ((uint32_t)0x00000027U)  /* Rx Buffer 39 */
#define FDCAN_RX_BUFFER40               ((uint32_t)0x00000028U)  /* Rx Buffer 40 */
#define FDCAN_RX_BUFFER41               ((uint32_t)0x00000029U)  /* Rx Buffer 41 */
#define FDCAN_RX_BUFFER42               ((uint32_t)0x0000002AU)  /* Rx Buffer 42 */
#define FDCAN_RX_BUFFER43               ((uint32_t)0x0000002BU)  /* Rx Buffer 43 */
#define FDCAN_RX_BUFFER44               ((uint32_t)0x0000002CU)  /* Rx Buffer 44 */
#define FDCAN_RX_BUFFER45               ((uint32_t)0x0000002DU)  /* Rx Buffer 45 */
#define FDCAN_RX_BUFFER46               ((uint32_t)0x0000002EU)  /* Rx Buffer 46 */
#define FDCAN_RX_BUFFER47               ((uint32_t)0x0000002FU)  /* Rx Buffer 47 */
#define FDCAN_RX_BUFFER48               ((uint32_t)0x00000030U)  /* Rx Buffer 48 */
#define FDCAN_RX_BUFFER49               ((uint32_t)0x00000031U)  /* Rx Buffer 49 */
#define FDCAN_RX_BUFFER50               ((uint32_t)0x00000032U)  /* Rx Buffer 50 */
#define FDCAN_RX_BUFFER51               ((uint32_t)0x00000033U)  /* Rx Buffer 51 */
#define FDCAN_RX_BUFFER52               ((uint32_t)0x00000034U)  /* Rx Buffer 52 */
#define FDCAN_RX_BUFFER53               ((uint32_t)0x00000035U)  /* Rx Buffer 53 */
#define FDCAN_RX_BUFFER54               ((uint32_t)0x00000036U)  /* Rx Buffer 54 */
#define FDCAN_RX_BUFFER55               ((uint32_t)0x00000037U)  /* Rx Buffer 55 */
#define FDCAN_RX_BUFFER56               ((uint32_t)0x00000038U)  /* Rx Buffer 56 */
#define FDCAN_RX_BUFFER57               ((uint32_t)0x00000039U)  /* Rx Buffer 57 */
#define FDCAN_RX_BUFFER58               ((uint32_t)0x0000003AU)  /* Rx Buffer 58 */
#define FDCAN_RX_BUFFER59               ((uint32_t)0x0000003BU)  /* Rx Buffer 59 */
#define FDCAN_RX_BUFFER60               ((uint32_t)0x0000003CU)  /* Rx Buffer 60 */
#define FDCAN_RX_BUFFER61               ((uint32_t)0x0000003DU)  /* Rx Buffer 61 */
#define FDCAN_RX_BUFFER62               ((uint32_t)0x0000003EU)  /* Rx Buffer 62 */
#define FDCAN_RX_BUFFER63               ((uint32_t)0x0000003FU)  /* Rx Buffer 63 */

/** FDCAN virtual index define for Rx FIFO and Tx envent FIFO  **/
#define FDCAN_RX_FIFO0                  ((uint32_t)0x00000040U)  /* Rx FIFO 0    */
#define FDCAN_RX_FIFO1                  ((uint32_t)0x00000041U)  /* Rx FIFO 1    */
#define FDCAN_TX_EVENT_FIFO             ((uint32_t)0x00000042U)  /* Tx event FIFO */

/** FDCAN High Priority Message Storage **/
#define FDCAN_HP_STANDARD_FILTER_LIST   (FDCAN_HPMS_FLST_STD)  /* Standard filter list  */
#define FDCAN_HP_EXTENDED_FILTER_LIST   (FDCAN_HPMS_FLST_EXT)  /* Extended filter list  */

/** FDCAN High Priority Message Storage **/
#define FDCAN_HP_STORAGE_NO_FIFO        (FDCAN_HPMS_MSI_NO_FIFO )   /* No FIFO selected         */
#define FDCAN_HP_STORAGE_MSG_LOST       (FDCAN_HPMS_MSI_MSG_LOST)   /* FIFO message lost        */
#define FDCAN_HP_STORAGE_RXFIFO0        (FDCAN_HPMS_MSI_FIFO0   )   /* Message stored in FIFO 0 */
#define FDCAN_HP_STORAGE_RXFIFO1        (FDCAN_HPMS_MSI_FIFO0   )   /* Message stored in FIFO 1 */

/** FDCAN receive error passive **/
#define FDCAN_RX_ERROR_BELOW_128        ((uint32_t)0x00000000U) /* The receive error counter is below the error passive level of 128    */
#define FDCAN_RX_ERROR_REACH_128        (FDCAN_ECR_RP)          /*  The receive error counter has reached the error passive level of 128    */

/** FDCAN protocol error code **/
#define FDCAN_LAST_ERROR_NONE           (FDCAN_PSR_LEC_NONE     )   /* No error occurred         */
#define FDCAN_LAST_ERROR_STUFF          (FDCAN_PSR_LEC_STUFF    )   /* Stuff error               */
#define FDCAN_LAST_ERROR_FORM           (FDCAN_PSR_LEC_FORM     )   /* Form error                */
#define FDCAN_LAST_ERROR_ACK            (FDCAN_PSR_LEC_ACK      )   /* Acknowledge error         */
#define FDCAN_LAST_ERROR_BIT1           (FDCAN_PSR_LEC_BIT1     )   /* Bit 1 (recessive) error   */
#define FDCAN_LAST_ERROR_BIT0           (FDCAN_PSR_LEC_BIT0     )   /* Bit 0 (dominant) error    */
#define FDCAN_LAST_ERROR_CRC            (FDCAN_PSR_LEC_CRC      )   /* CRC check sum error       */
#define FDCAN_LAST_ERROR_NO_CHANGE      (FDCAN_PSR_LEC_NO_CHANGE)   /* No change since last read */

#define FDCAN_LAST_DATA_ERROR_NONE      (FDCAN_PSR_DLEC_NONE     )  /* No error occurred         */
#define FDCAN_LAST_DATA_ERROR_STUFF     (FDCAN_PSR_DLEC_STUFF    )  /* Stuff error               */
#define FDCAN_LAST_DATA_ERROR_FORM      (FDCAN_PSR_DLEC_FORM     )  /* Form error                */
#define FDCAN_LAST_DATA_ERROR_ACK       (FDCAN_PSR_DLEC_ACK      )  /* Acknowledge error         */
#define FDCAN_LAST_DATA_ERROR_BIT1      (FDCAN_PSR_DLEC_BIT1     )  /* Bit 1 (recessive) error   */
#define FDCAN_LAST_DATA_ERROR_BIT0      (FDCAN_PSR_DLEC_BIT0     )  /* Bit 0 (dominant) error    */
#define FDCAN_LAST_DATA_ERROR_CRC       (FDCAN_PSR_DLEC_CRC      )  /* CRC check sum error       */
#define FDCAN_LAST_DATA_ERROR_NO_CHANGE (FDCAN_PSR_DLEC_NO_CHANGE)  /* No change since last read */

/** FDCAN protocol communication state **/
#define FDCAN_COM_STATE_SYNC            (FDCAN_PSR_ACT_SYNC) /* Node is synchronizing on CAN communication */
#define FDCAN_COM_STATE_IDLE            (FDCAN_PSR_ACT_IDLE) /* Node is neither receiver nor transmitter   */
#define FDCAN_COM_STATE_RX              (FDCAN_PSR_ACT_RX  ) /* Node is operating as receiver              */
#define FDCAN_COM_STATE_TX              (FDCAN_PSR_ACT_TX  ) /* Node is operating as transmitter           */

/** FDCAN protocol error passive **/
#define FDCAN_ERROR_ACTIVE              ((uint32_t)0x00000000U) /* Node is active error state */
#define FDCAN_ERROR_PASSIVE             (FDCAN_PSR_EP)          /* Node is passive error state */

/** FDCAN protocol warning status **/
#define FDCAN_WARNING_BELOW_96          ((uint32_t)0x00000000U) /* RxErrorCnt and TxErrorCnt are below the Error_Warning limit of 96 */
#define FDCAN_WARNING_REACH_96          (FDCAN_PSR_EW)          /* At least one of error counters has reached the Error_Warning limit of 96 */

/** FDCAN protocol bus off status **/
#define FDCAN_BUS_ON                    ((uint32_t)0x00000000U) /* Node is not bus off state */
#define FDCAN_BUS_OFF                   (FDCAN_PSR_BO)          /* Node is bus off state */

/** FDCAN protocol ESI flag of last received FDCAN message **/
#define FDCAN_ESI_NOT_SET               ((uint32_t)0x00000000U) /* ESI flag of last received FDCAN message is not set */
#define FDCAN_ESI_SET                   (FDCAN_PSR_RESI)        /* ESI flag of last received FDCAN message is set */

/** FDCAN protocol BRS flag of last received FDCAN message **/
#define FDCAN_BRS_NOT_SET               ((uint32_t)0x00000000U) /* BSR flag of last received FDCAN message is not set */
#define FDCAN_BRS_SET                   (FDCAN_PSR_RBRS)        /* BSR flag of last received FDCAN message is set */

/** FDCAN protocol received a FDCAN message  **/
#define FDCAN_FDMSG_NOT_RECEIVED        ((uint32_t)0x00000000U) /* Have not received any FDCAN message after CPU reset */
#define FDCAN_FDMSG_RECEIVED            (FDCAN_PSR_RFDF)        /* Have received FDCAN message after CPU reset */

/** FDCAN protocol exception event   **/
#define FDCAN_NO_EXCEPTION              ((uint32_t)0x00000000U) /* No protocol exception event occurred since last read access */
#define FDCAN_HAVE_EXCEPTION            (FDCAN_PSR_PXE)         /* Protocol exception event occurred */

/** FDCAN FIFO operation mode, used for both Rx FIFO 0 and FIFO 1 **/
#define FDCAN_RX_FIFO_BLOCKING          ((uint32_t)0x00000000U) /* Rx FIFO blocking mode  */
#define FDCAN_RX_FIFO_OVERWRITE         (FDCAN_RXF0C_F0OM)      /* Rx FIFO overwrite mode */

/** FDCAN non-matching frames **/
#define FDCAN_ACCEPT_STD_IN_RX_FIFO0    ((uint32_t)0x00000000U) /* Accept Standard Frame in Rx FIFO 0 */
#define FDCAN_ACCEPT_STD_IN_RX_FIFO1    (FDCAN_GFC_ANFS_0)      /* Accept Standard Frame in Rx FIFO 1 */
#define FDCAN_REJECT_STD                (FDCAN_GFC_ANFS_1)      /* Reject Standard Frame              */

#define FDCAN_ACCEPT_EXT_IN_RX_FIFO0    ((uint32_t)0x00000000U) /* Accept Extended Frame in Rx FIFO 0 */
#define FDCAN_ACCEPT_EXT_IN_RX_FIFO1    (FDCAN_GFC_ANFE_0)      /* Accept Extended Frame in Rx FIFO 1 */
#define FDCAN_REJECT_EXT                (FDCAN_GFC_ANFE_1)      /* Reject Extended Frame              */

/** FDCAN reject remote frames **/
#define FDCAN_FILTER_STD_REMOTE         ((uint32_t)0x00000000U) /* Filter Standard remote frames */
#define FDCAN_REJECT_STD_REMOTE         (FDCAN_GFC_RRFS)        /* Reject all Standard remote frames */
#define FDCAN_FILTER_EXT_REMOTE         ((uint32_t)0x00000000U) /* Filter Extended remote frames */
#define FDCAN_REJECT_EXT_REMOTE         (FDCAN_GFC_RRFE)        /* Reject all Extended remote frames */

/** FDCAN interrupt line **/
#define FDCAN_INTERRUPT_LINE0           (FDCAN_ILE_EINT0)  /* Interrupt Line 0 */
#define FDCAN_INTERRUPT_LINE1           (FDCAN_ILE_EINT1)  /* Interrupt Line 1 */

/** FDCAN timestamp select define **/
#define FDCAN_TIMESTAMP_DISABLE         (FDCAN_TSCC_CONSTANT)  /* Timestamp counter value is always 0x0000 */
#define FDCAN_TIMESTAMP_INTERNAL        (FDCAN_TSCC_INC_TCP)   /* Timestamp counter value incremented according to TCP */
#define FDCAN_TIMESTAMP_EXTERNAL        (FDCAN_TSCC_USE_EXT)   /* External timestamp counter value used                */

/** FDCAN internal timestamp prescaler define **/
#define FDCAN_TIMESTAMP_PRESC_1         (FDCAN_TSCC_TCP_DIV1 ) /* Timestamp counter time unit in equal to CAN bit time                 */
#define FDCAN_TIMESTAMP_PRESC_2         (FDCAN_TSCC_TCP_DIV2 ) /* Timestamp counter time unit in equal to CAN bit time multiplied by 2  */
#define FDCAN_TIMESTAMP_PRESC_3         (FDCAN_TSCC_TCP_DIV3 ) /* Timestamp counter time unit in equal to CAN bit time multiplied by 3  */
#define FDCAN_TIMESTAMP_PRESC_4         (FDCAN_TSCC_TCP_DIV4 ) /* Timestamp counter time unit in equal to CAN bit time multiplied by 4  */
#define FDCAN_TIMESTAMP_PRESC_5         (FDCAN_TSCC_TCP_DIV5 ) /* Timestamp counter time unit in equal to CAN bit time multiplied by 5  */
#define FDCAN_TIMESTAMP_PRESC_6         (FDCAN_TSCC_TCP_DIV6 ) /* Timestamp counter time unit in equal to CAN bit time multiplied by 6  */
#define FDCAN_TIMESTAMP_PRESC_7         (FDCAN_TSCC_TCP_DIV7 ) /* Timestamp counter time unit in equal to CAN bit time multiplied by 7  */
#define FDCAN_TIMESTAMP_PRESC_8         (FDCAN_TSCC_TCP_DIV8 ) /* Timestamp counter time unit in equal to CAN bit time multiplied by 8  */
#define FDCAN_TIMESTAMP_PRESC_9         (FDCAN_TSCC_TCP_DIV9 ) /* Timestamp counter time unit in equal to CAN bit time multiplied by 9  */
#define FDCAN_TIMESTAMP_PRESC_10        (FDCAN_TSCC_TCP_DIV10) /* Timestamp counter time unit in equal to CAN bit time multiplied by 10 */
#define FDCAN_TIMESTAMP_PRESC_11        (FDCAN_TSCC_TCP_DIV11) /* Timestamp counter time unit in equal to CAN bit time multiplied by 11 */
#define FDCAN_TIMESTAMP_PRESC_12        (FDCAN_TSCC_TCP_DIV12) /* Timestamp counter time unit in equal to CAN bit time multiplied by 12 */
#define FDCAN_TIMESTAMP_PRESC_13        (FDCAN_TSCC_TCP_DIV13) /* Timestamp counter time unit in equal to CAN bit time multiplied by 13 */
#define FDCAN_TIMESTAMP_PRESC_14        (FDCAN_TSCC_TCP_DIV14) /* Timestamp counter time unit in equal to CAN bit time multiplied by 14 */
#define FDCAN_TIMESTAMP_PRESC_15        (FDCAN_TSCC_TCP_DIV15) /* Timestamp counter time unit in equal to CAN bit time multiplied by 15 */
#define FDCAN_TIMESTAMP_PRESC_16        (FDCAN_TSCC_TCP_DIV16) /* Timestamp counter time unit in equal to CAN bit time multiplied by 16 */

/** FDCAN external timestamp clock divider define **/
#define FDCAN_EXT_TIMESTAMP_DISABLE     ((uint32_t)0x00000000U) /* Extenal timestamp clock disable */
#define FDCAN_EXT_TIMESTAMP_ENABLE      (FDCAN_TTSS_TS_EN)      /* Extenal timestamp clock enable  */

/** FDCAN external timestamp clock divider define **/
#define FDCAN_EXT_TIMESTAMP_DIV_4       (FDCAN_TTSS_TS_SEL_DIV4  )  /* Extenal timestamp clock is PCLK divided by 4   */
#define FDCAN_EXT_TIMESTAMP_DIV_8       (FDCAN_TTSS_TS_SEL_DIV8  )  /* Extenal timestamp clock is PCLK divided by 8   */
#define FDCAN_EXT_TIMESTAMP_DIV_16      (FDCAN_TTSS_TS_SEL_DIV16 )  /* Extenal timestamp clock is PCLK divided by 16  */
#define FDCAN_EXT_TIMESTAMP_DIV_32      (FDCAN_TTSS_TS_SEL_DIV32 )  /* Extenal timestamp clock is PCLK divided by 32  */
#define FDCAN_EXT_TIMESTAMP_DIV_64      (FDCAN_TTSS_TS_SEL_DIV64 )  /* Extenal timestamp clock is PCLK divided by 64  */
#define FDCAN_EXT_TIMESTAMP_DIV_128     (FDCAN_TTSS_TS_SEL_DIV128)  /* Extenal timestamp clock is PCLK divided by 128 */
#define FDCAN_EXT_TIMESTAMP_DIV_256     (FDCAN_TTSS_TS_SEL_DIV256)  /* Extenal timestamp clock is PCLK divided by 256 */
#define FDCAN_EXT_TIMESTAMP_DIV_512     (FDCAN_TTSS_TS_SEL_DIV512)  /* Extenal timestamp clock is PCLK divided by 512 */

/** FDCAN timeout operation define **/
#define FDCAN_TIMEOUT_CONTINUOUS        (FDCAN_TOCC_TOS_CONTINUOUS   ) /* Timeout continuous operation        */
#define FDCAN_TIMEOUT_TX_EVENT_FIFO     (FDCAN_TOCC_TOS_TX_EVENT_FIFO) /* Timeout controlled by Tx Event FIFO */
#define FDCAN_TIMEOUT_RX_FIFO0          (FDCAN_TOCC_TOS_RX_FIFO0     ) /* Timeout controlled by Rx FIFO 0     */
#define FDCAN_TIMEOUT_RX_FIFO1          (FDCAN_TOCC_TOS_RX_FIFO1     ) /* Timeout controlled by Rx FIFO 1     */

/* FDCAN modify on read function define */
#define FDCAN_ENABLE_MODIFY_ON_READ     ((uint32_t)0x00000000U)     /* Modify on read enable    */
#define FDCAN_DISABLE_MODIFY_ON_READ    (FDCAN_TTSS_MRD)            /* Modify on read disable   */

/*** TT-CAN register define ***/

/** FDCAN TT reference message payload **/
#define FDCAN_TT_REF_MSG_NO_PAYLOAD     ((uint32_t)0x00000000U)      /* Reference message has no additional payload  */
#define FDCAN_TT_REF_MSG_ADD_PAYLOAD    ((uint32_t)FDCAN_TTRMC_RMPS) /* Additional payload is taken from Tx Buffer 0 */

/** FDCAN Operation Mode **/
#define FDCAN_TT_COMMUNICATION_LEVEL1       (FDCAN_TTOCF_OM_LEVEL1) /* Time triggered communication, level 1 */
#define FDCAN_TT_COMMUNICATION_LEVEL2       (FDCAN_TTOCF_OM_LEVEL2) /* Time triggered communication, level 2 */
#define FDCAN_TT_COMMUNICATION_LEVEL0       (FDCAN_TTOCF_OM_LEVEL0) /* Time triggered communication, level 0 */

/** FDCAN TT Operation **/
#define FDCAN_STRICTLY_TT_OPERATION         ((uint32_t)0x00000000U)     /* Strictly time-triggered operation                    */
#define FDCAN_EXT_EVT_SYNC_TT_OPERATION     ((uint32_t)FDCAN_TTOCF_GEN) /* External event-synchronized time-triggered operation */

/** FDCAN TT Time Master **/
#define FDCAN_TT_SLAVE                      ((uint32_t)0x00000000U)    /* Time slave            */
#define FDCAN_TT_POTENTIAL_MASTER           ((uint32_t)FDCAN_TTOCF_TM) /* Potential time master */

/** FDCAN TT External Clock Synchronization **/
#define FDCAN_TT_EXT_CLK_SYNC_DISABLE       ((uint32_t)0x00000000U)      /* External clock synchronization in Level 0,2 disabled */
#define FDCAN_TT_EXT_CLK_SYNC_ENABLE        ((uint32_t)FDCAN_TTOCF_EECS) /* External clock synchronization in Level 0,2 enabled  */

/** FDCAN TT Global Time Filtering **/
#define FDCAN_TT_GLOB_TIME_FILT_DISABLE     ((uint32_t)0x00000000U)      /* Global time filtering in Level 0,2 disabled */
#define FDCAN_TT_GLOB_TIME_FILT_ENABLE      ((uint32_t)FDCAN_TTOCF_EGTF) /* Global time filtering in Level 0,2 enabled  */

/** FDCAN TT Automatic Clock Calibration **/
#define FDCAN_TT_AUTO_CLK_CALIB_DISABLE     ((uint32_t)0x00000000U)    /* Automatic clock calibration in Level 0,2 disabled */
#define FDCAN_TT_AUTO_CLK_CALIB_ENABLE      ((uint32_t)FDCAN_TTOCF_ECC) /* Automatic clock calibration in Level 0,2 enabled  */

/**FDCAN TT Event Trigger Polarity **/
#define FDCAN_TT_EVT_TRIG_POL_RISING        ((uint32_t)0x00000000U)     /* Rising edge trigger  */
#define FDCAN_TT_EVT_TRIG_POL_FALLING       ((uint32_t)FDCAN_TTOCF_EVTP) /* Falling edge trigger */

/** FDCAN TT Basic Cycle Number **/
#define FDCAN_TT_CYCLES_PER_MATRIX_1        (FDCAN_TTMLM_CCM_NUM1 ) /* 1 Basic Cycle per Matrix   */
#define FDCAN_TT_CYCLES_PER_MATRIX_2        (FDCAN_TTMLM_CCM_NUM2 ) /* 2 Basic Cycles per Matrix  */
#define FDCAN_TT_CYCLES_PER_MATRIX_4        (FDCAN_TTMLM_CCM_NUM4 ) /* 4 Basic Cycles per Matrix  */
#define FDCAN_TT_CYCLES_PER_MATRIX_8        (FDCAN_TTMLM_CCM_NUM8 ) /* 8 Basic Cycles per Matrix  */
#define FDCAN_TT_CYCLES_PER_MATRIX_16       (FDCAN_TTMLM_CCM_NUM16) /* 16 Basic Cycles per Matrix */
#define FDCAN_TT_CYCLES_PER_MATRIX_32       (FDCAN_TTMLM_CCM_NUM32) /* 32 Basic Cycles per Matrix */
#define FDCAN_TT_CYCLES_PER_MATRIX_64       (FDCAN_TTMLM_CCM_NUM64) /* 64 Basic Cycles per Matrix */

/** FDCAN TT Cycle Start Sync **/
#define FDCAN_TT_NO_SYNC_PULSE              (FDCAN_TTMLM_CSS_NONE)   /* No sync pulse                      */
#define FDCAN_TT_SYNC_BASIC_CYCLE_START     (FDCAN_TTMLM_CSS_BASIC ) /* Sync pulse at start of basic cycle */
#define FDCAN_TT_SYNC_MATRIX_START          (FDCAN_TTMLM_CSS_MATRIX) /* Sync pulse at start of matrix      */

/** FDCAN TT Stop Watch Trigger Selection **/
#define FDCAN_TT_STOP_WATCH_TRIGGER_0       (FDCAN_TTSS_SSWT_0) /* GTIMx selected as stop watch trigger  */
#define FDCAN_TT_STOP_WATCH_TRIGGER_1       (FDCAN_TTSS_SSWT_1) /* GTIMx selected as stop watch trigger  */
#define FDCAN_TT_STOP_WATCH_TRIGGER_2       (FDCAN_TTSS_SSWT_2) /* ETHx selected as stop watch trigger   */
#define FDCAN_TT_STOP_WATCH_TRIGGER_3       (FDCAN_TTSS_SSWT_3) /* SHRTIMx selected as stop watch trigger */

/**FDCAN TT Event Trigger Selection **/
#define FDCAN_TT_EVENT_TRIGGER_0            (FDCAN_TTSS_SEVT_0) /* GTIMx selected as event trigger  */
#define FDCAN_TT_EVENT_TRIGGER_1            (FDCAN_TTSS_SEVT_1) /* GTIMx selected as event trigger  */
#define FDCAN_TT_EVENT_TRIGGER_2            (FDCAN_TTSS_SEVT_2) /* ETHx selected as event trigger   */
#define FDCAN_TT_EVENT_TRIGGER_3            (FDCAN_TTSS_SEVT_3) /* SHRTIMx selected as event trigger */

/** FDCAN TT Stop Watch Source **/
#define FDCAN_TT_STOP_WATCH_DISABLED        (FDCAN_TTOCN_SWS_STOP)    /* Stop Watch disabled                                            */
#define FDCAN_TT_STOP_WATCH_CYCLE_TIME      (FDCAN_TTOCN_SWS_CYCLE  ) /* Cycle time is copied to Capture Time register  */
#define FDCAN_TT_STOP_WATCH_LOCAL_TIME      (FDCAN_TTOCN_SWS_LOCAL  ) /* Local time is copied to Capture Time register  */
#define FDCAN_TT_STOP_WATCH_GLOBAL_TIME     (FDCAN_TTOCN_SWS_GLOBAL ) /* Global time is copied to Capture Time register */

/** FDCAN TT Stop Watch Polarity **/
#define FDCAN_TT_STOP_WATCH_RISING          ((uint32_t)0x00000000U)/* Stop watch source is captured at rising edge of fdcan1_swt  */
#define FDCAN_TT_STOP_WATCH_FALLING         (FDCAN_TTOCN_SWP)      /* Stop watch source is captured at falling edge of fdcan1_swt */

/** FDCAN TT Time Mark Source **/
#define FDCAN_TT_REG_TIMEMARK_DIABLED       (FDCAN_TTOCN_TMC_NONE) /* No Register Time Mark Interrupt generated               */
#define FDCAN_TT_REG_TIMEMARK_CYCLE_TIME    (FDCAN_TTOCN_TMC_BASIC  ) /* Register Time Mark Interrupt if Time Mark = cycle time  */
#define FDCAN_TT_REG_TIMEMARK_LOCAL_TIME    (FDCAN_TTOCN_TMC_LOCAL  ) /* Register Time Mark Interrupt if Time Mark = local time  */
#define FDCAN_TT_REG_TIMEMARK_GLOBAL_TIME   (FDCAN_TTOCN_TMC_GLOBAL ) /* Register Time Mark Interrupt if Time Mark = global time */

/** FDCAN TT Error Level **/
#define FDCAN_TT_NO_ERROR                   (FDCAN_TTOST_EL_S0) /* Severity 0 - No Error     */
#define FDCAN_TT_WARNING                    (FDCAN_TTOST_EL_S1) /* Severity 1 - Warning      */
#define FDCAN_TT_ERROR                      (FDCAN_TTOST_EL_S2) /* Severity 2 - Error        */
#define FDCAN_TT_SEVERE_ERROR               (FDCAN_TTOST_EL_S3) /* Severity 3 - Severe Error */

/** FDCAN TT Master State **/
#define FDCAN_TT_MASTER_OFF                 (FDCAN_TTOST_MS_NONE   ) /* Master_Off, no master properties relevant */
#define FDCAN_TT_TIME_SLAVE                 (FDCAN_TTOST_MS_SLAVE  ) /* Operating as Time Slave                   */
#define FDCAN_TT_BACKUP_TIME_MASTER         (FDCAN_TTOST_MS_BACKUP ) /* Operating as Backup Time Master           */
#define FDCAN_TT_CURRENT_TIME_MASTER        (FDCAN_TTOST_MS_CURRENT) /* Operating as current Time Master          */

/** FDCAN TT Synchronization State **/
#define FDCAN_TT_OUT_OF_SYNC                (FDCAN_TTOST_SYS_NONE       ) /* Out of Synchronization         */
#define FDCAN_TT_SYNCHRONIZING              (FDCAN_TTOST_SYS_SYNC       ) /* Synchronizing to communication */
#define FDCAN_TT_IN_GAP                     (FDCAN_TTOST_SYS_IN_GAP     ) /* Schedule suspended by Gap      */
#define FDCAN_TT_IN_SCHEDULE                (FDCAN_TTOST_SYS_IN_SCHEDULE) /* Synchronized to schedule       */

/** FDCAN TT Quality of global time phase. **/
#define FDCAN_TT_GTIME_NOT_VALID            ((uint32_t)0x00000000U) /* Global time not valid                 */
#define FDCAN_TT_GTIME_IN_MASTER_PHASE      (FDCAN_TTOST_QGTP    )  /* Global time in phase with Time Master */

/** FDCAN TT Quality of clock Speed **/
#define FDCAN_TT_LOCAL_CLOCK_NOT_SYNC       ((uint32_t)0x00000000U) /* Local clock speed not synchronized to Time Master clock speed */
#define FDCAN_TT_SYNC_DEV_LESS_THAN_SDL     (FDCAN_TTOST_QCS     )  /* Synchronization Deviation <= SDL */

/** FDCAN TT Wait for global time discontinuity **/
#define FDCAN_TT_NO_GTIME_PENDING           ((uint32_t)0x00000000U) /* No global time preset pending */
#define FDCAN_TT_WATI_GTIMESYNC_PRESENT     (FDCAN_TTOST_WGTD    )  /* Node waits for the global time preset to take effect */

/** FDCAN TT Gap finished Indicator **/
#define FDCAN_TT_GAP_RESET                  ((uint32_t)0x00000000U) /* Reset at the end of each reference message */
#define FDCAN_TT_GAP_FINISHED               (FDCAN_TTOST_GFI     )  /* Gap finished by FDCAN */

/** FDCAN TT Gap started Indicator **/
#define FDCAN_TT_NO_GAP                     ((uint32_t)0x00000000U) /* No Gap in schedule */
#define FDCAN_TT_GAP_STARTED                (FDCAN_TTOST_GSI     )  /* Gap time after basic cycle has started */

/** FDCAN TT Wait for event **/
#define FDCAN_TT_GAP_NOT_ANNOUNCED          ((uint32_t)0x00000000U) /* No Gap announced */
#define FDCAN_TT_REF_MSG_RECEIVED           (FDCAN_TTOST_WFE     )  /* Reference message with Next_is_Gap = 1 received */

/** FDCAN TT Application watchdog event. **/
#define FDCAN_TT_WATCHDOG_VALID             ((uint32_t)0x00000000U) /* Application watchdog served in time */
#define FDCAN_TT_WATCHDOG_INVALID           (FDCAN_TTOST_AWE     )  /* Failed to serve application watchdog in time */

/** FDCAN TT  Wait for external clock synchronization **/
#define FDCAN_TT_NO_EXT_CLOCK_SYNC          ((uint32_t)0x00000000U) /* No external clock synchronization pending. */
#define FDCAN_TT_WAIT_EXT_CLOCK_SYNC        (FDCAN_TTOST_WECS    )  /* Node waits for external clock synchronization to take effect.  */

/** FDCAN TT  Schedule phase lock. **/
#define FDCAN_TT_PHASE_OUT_OF_RANGE         ((uint32_t)0x00000000U) /* Phase outside range. */
#define FDCAN_TT_PHASE_IN_RANGE             (FDCAN_TTOST_SPL     )  /* Phase inside range.  */

/** FDCAN Interrupt masks **/
#define FDCAN_INT_MASK                      ((uint32_t)0x3FFFFFFFU)/* FDCAN interrupts mask */

/** FDCAN Flags **/
#define FDCAN_FLAG_RESERVED_ADDRESS_ACCESS  (FDCAN_IR_ARA ) /* Access to reserved address occurred                   */
#define FDCAN_FLAG_DATA_PROTOCOL_ERROR      (FDCAN_IR_PED ) /* Protocol error in data phase detected                 */
#define FDCAN_FLAG_ARB_PROTOCOL_ERROR       (FDCAN_IR_PEA ) /* Protocol error in arbitration phase detected          */
#define FDCAN_FLAG_RAM_WATCHDOG             (FDCAN_IR_WDI ) /* Message RAM Watchdog event due to missing READY       */
#define FDCAN_FLAG_BUS_OFF                  (FDCAN_IR_BO  ) /* Bus_Off status changed                                */
#define FDCAN_FLAG_ERROR_WARNING            (FDCAN_IR_EW  ) /* Error_Warning status changed                          */
#define FDCAN_FLAG_ERROR_PASSIVE            (FDCAN_IR_EP  ) /* Error_Passive status changed                          */
#define FDCAN_FLAG_ERROR_LOGGING_OVERFLOW   (FDCAN_IR_ELO ) /* Overflow of FDCAN Error Logging Counter occurred      */
#define FDCAN_FLAG_BITERROR_CORRECTED       (FDCAN_IR_BEC ) /* Bit Error Corrected                                   */
#define FDCAN_FLAG_BITERROR_UNCORRECTED     (FDCAN_IR_BEU ) /* Bit Error Uncorrected                                 */
#define FDCAN_FLAG_RX_BUFFER_NEW_MESSAGE    (FDCAN_IR_DRX ) /* At least one received message stored into a Rx Buffer */
#define FDCAN_FLAG_TIMEOUT_OCCURRED         (FDCAN_IR_TOO ) /* Timeout reached                                       */
#define FDCAN_FLAG_RAM_ACCESS_FAILURE       (FDCAN_IR_MRAF) /* Message RAM access failure occurred                   */
#define FDCAN_FLAG_TIMESTAMP_WRAPAROUND     (FDCAN_IR_TSW ) /* Timestamp counter wrapped around                      */
#define FDCAN_FLAG_TX_EVT_FIFO_ELT_LOST     (FDCAN_IR_TEFL) /* Tx Event FIFO element lost                            */
#define FDCAN_FLAG_TX_EVT_FIFO_FULL         (FDCAN_IR_TEFF) /* Tx Event FIFO full                                    */
#define FDCAN_FLAG_TX_EVT_FIFO_WATERMARK    (FDCAN_IR_TEFW) /* Tx Event FIFO fill level reached watermark            */
#define FDCAN_FLAG_TX_EVT_FIFO_NEW_DATA     (FDCAN_IR_TEFN) /* Tx Handler wrote Tx Event FIFO element                */
#define FDCAN_FLAG_TX_FIFO_EMPTY            (FDCAN_IR_TFE ) /* Tx FIFO Empty                                         */
#define FDCAN_FLAG_TX_ABORT_COMPLETE        (FDCAN_IR_TCF ) /* Transmission Cancellation Finished                    */
#define FDCAN_FLAG_TX_COMPLETE              (FDCAN_IR_TC  ) /* Transmission Completed                                */
#define FDCAN_FLAG_RX_HIGH_PRIORITY_MSG     (FDCAN_IR_HPM ) /* High priority message received                        */
#define FDCAN_FLAG_RX_FIFO1_MESSAGE_LOST    (FDCAN_IR_RF1L) /* Rx FIFO 1 message lost                                */
#define FDCAN_FLAG_RX_FIFO1_FULL            (FDCAN_IR_RF1F) /* Rx FIFO 1 full                                        */
#define FDCAN_FLAG_RX_FIFO1_WATERMARK       (FDCAN_IR_RF1W) /* Rx FIFO 1 fill level reached watermark                */
#define FDCAN_FLAG_RX_FIFO1_NEW_MESSAGE     (FDCAN_IR_RF1N) /* New message written to Rx FIFO 1                      */
#define FDCAN_FLAG_RX_FIFO0_MESSAGE_LOST    (FDCAN_IR_RF0L) /* Rx FIFO 0 message lost                                */
#define FDCAN_FLAG_RX_FIFO0_FULL            (FDCAN_IR_RF0F) /* Rx FIFO 0 full                                        */
#define FDCAN_FLAG_RX_FIFO0_WATERMARK       (FDCAN_IR_RF0W) /* Rx FIFO 0 fill level reached watermark                */
#define FDCAN_FLAG_RX_FIFO0_NEW_MESSAGE     (FDCAN_IR_RF0N) /* New message written to Rx FIFO 0                      */

/** FDCAN Tx Interrupts **/
#define FDCAN_INT_TX_COMPLETE               (FDCAN_IE_TCE ) /* Transmission Completed                                */
#define FDCAN_INT_TX_ABORT_COMPLETE         (FDCAN_IE_TCFE) /* Transmission Cancellation Finished                    */
#define FDCAN_INT_TX_FIFO_EMPTY             (FDCAN_IE_TFEE) /* Tx FIFO Empty                                         */

/**FDCAN Rx Interrupts **/
#define FDCAN_INT_RX_HIGH_PRIORITY_MSG      (FDCAN_IE_HPME) /* High priority message received                        */
#define FDCAN_INT_RX_BUFFER_NEW_MESSAGE     (FDCAN_IE_DRXE) /* At least one received message stored into a Rx Buffer */

/** FDCAN Counter Interrupts **/
#define FDCAN_INT_TIMESTAMP_WRAPAROUND      (FDCAN_IE_TSWE) /* Timestamp counter wrapped around                      */
#define FDCAN_INT_TIMEOUT_OCCURRED          (FDCAN_IE_TOOE) /* Timeout reached                                       */

/** FDCAN Tx Event FIFO Interrupts **/
#define FDCAN_INT_TX_EVT_FIFO_ELT_LOST      (FDCAN_IE_TEFLE) /* Tx Event FIFO element lost                 */
#define FDCAN_INT_TX_EVT_FIFO_FULL          (FDCAN_IE_TEFFE) /* Tx Event FIFO full                         */
#define FDCAN_INT_TX_EVT_FIFO_WATERMARK     (FDCAN_IE_TEFWE) /* Tx Event FIFO fill level reached watermark */
#define FDCAN_INT_TX_EVT_FIFO_NEW_DATA      (FDCAN_IE_TEFNE) /* Tx Handler wrote Tx Event FIFO element     */

/** FDCAN Rx FIFO 0 Interrupts **/
#define FDCAN_INT_RX_FIFO0_MESSAGE_LOST     (FDCAN_IE_RF0LE) /* Rx FIFO 0 message lost                 */
#define FDCAN_INT_RX_FIFO0_FULL             (FDCAN_IE_RF0FE) /* Rx FIFO 0 full                         */
#define FDCAN_INT_RX_FIFO0_WATERMARK        (FDCAN_IE_RF0WE) /* Rx FIFO 0 fill level reached watermark */
#define FDCAN_INT_RX_FIFO0_NEW_MESSAGE      (FDCAN_IE_RF0NE) /* New message written to Rx FIFO 0       */

/** FDCAN Rx FIFO 1 Interrupts **/
#define FDCAN_INT_RX_FIFO1_MESSAGE_LOST     (FDCAN_IE_RF1LE) /* Rx FIFO 1 message lost                 */
#define FDCAN_INT_RX_FIFO1_FULL             (FDCAN_IE_RF1FE) /* Rx FIFO 1 full                         */
#define FDCAN_INT_RX_FIFO1_WATERMARK        (FDCAN_IE_RF1WE) /* Rx FIFO 1 fill level reached watermark */
#define FDCAN_INT_RX_FIFO1_NEW_MESSAGE      (FDCAN_IE_RF1NE) /* New message written to Rx FIFO 1       */

/** FDCAN Error Interrupts **/
#define FDCAN_INT_RAM_ACCESS_FAILURE        (FDCAN_IE_MRAFE) /* Message RAM access failure occurred              */
#define FDCAN_INT_ERROR_LOGGING_OVERFLOW    (FDCAN_IE_ELOE ) /* Overflow of FDCAN Error Logging Counter occurred */
#define FDCAN_INT_RAM_WATCHDOG              (FDCAN_IE_WDIE ) /* Message RAM Watchdog event due to missing READY  */
#define FDCAN_INT_ARB_PROTOCOL_ERROR        (FDCAN_IE_PEAE ) /* Protocol error in arbitration phase detected     */
#define FDCAN_INT_DATA_PROTOCOL_ERROR       (FDCAN_IE_PEDE ) /* Protocol error in data phase detected            */
#define FDCAN_INT_RESERVED_ADDRESS_ACCESS   (FDCAN_IE_ARAE ) /* Access to reserved address occurred              */

/** FDCAN Error Status Interrupts **/
#define FDCAN_INT_ERROR_PASSIVE             (FDCAN_IE_EPE) /* Error_Passive status changed */
#define FDCAN_INT_ERROR_WARNING             (FDCAN_IE_EWE) /* Error_Warning status changed */
#define FDCAN_INT_BUS_OFF                   (FDCAN_IE_BOE) /* Bus_Off status changed       */

/** SRAM Bit Error Status Interrupts **/
#define FDCAN_INT_BITERROR_CORRECTED        (FDCAN_IE_BECE) /* Bit Error Corrected */
#define FDCAN_INT_BITERROR_UNCORRECTED      (FDCAN_IE_BEUE) /* Bit Error Uncorrected */

/** FDCAN TT Interrupt masks **/
#define FDCAN_TT_INT_MASK                   ((uint32_t)0x0007FFFFU) /* FDCAN TT interrupts mask */

/** FDCAN TT Flags **/
#define FDCAN_TT_FLAG_BASIC_CYCLE_START     (FDCAN_TTIR_SBC ) /* Start of Basic Cycle             */
#define FDCAN_TT_FLAG_MATRIX_CYCLE_START    (FDCAN_TTIR_SMC ) /* Start of Matrix Cycle            */
#define FDCAN_TT_FLAG_SYNC_MODE_CHANGE      (FDCAN_TTIR_CSM ) /* Change of Synchronization Mode   */
#define FDCAN_TT_FLAG_START_OF_GAP          (FDCAN_TTIR_SOG ) /* Start of Gap                     */
#define FDCAN_TT_FLAG_REG_TIME_MARK         (FDCAN_TTIR_RTMI) /* Register Time Mark Interrupt     */
#define FDCAN_TT_FLAG_TRIG_TIME_MARK        (FDCAN_TTIR_TTMI) /* Trigger Time Mark Event Internal */
#define FDCAN_TT_FLAG_STOP_WATCH            (FDCAN_TTIR_SWE ) /* Stop Watch Event                 */
#define FDCAN_TT_FLAG_GLOBAL_TIME_WRAP      (FDCAN_TTIR_GTW ) /* Global Time Wrap                 */
#define FDCAN_TT_FLAG_GLOBAL_TIME_DISC      (FDCAN_TTIR_GTD ) /* Global Time Discontinuity        */
#define FDCAN_TT_FLAG_GLOBAL_TIME_ERROR     (FDCAN_TTIR_GTE ) /* Global Time Error                */
#define FDCAN_TT_FLAG_TX_COUNT_UNDERFLOW    (FDCAN_TTIR_TXU ) /* Tx Count Underflow               */
#define FDCAN_TT_FLAG_TX_COUNT_OVERFLOW     (FDCAN_TTIR_TXO ) /* Tx Count Overflow                */
#define FDCAN_TT_FLAG_SCHEDULING_ERROR_1    (FDCAN_TTIR_SE1 ) /* Scheduling Error 1               */
#define FDCAN_TT_FLAG_SCHEDULING_ERROR_2    (FDCAN_TTIR_SE2 ) /* Scheduling Error 2               */
#define FDCAN_TT_FLAG_ERROR_LEVEL_CHANGE    (FDCAN_TTIR_ELC ) /* Error Level Changed              */
#define FDCAN_TT_FLAG_INIT_WATCH_TRIGGER    (FDCAN_TTIR_IWT ) /* Initialization Watch Trigger     */
#define FDCAN_TT_FLAG_WATCH_TRIGGER         (FDCAN_TTIR_WT  ) /* Watch Trigger                    */
#define FDCAN_TT_FLAG_APPLICATION_WATCHDOG  (FDCAN_TTIR_AW  ) /* Application Watchdog             */
#define FDCAN_TT_FLAG_CONFIG_ERROR          (FDCAN_TTIR_CER ) /* Configuration Error              */

/** FDCAN TT Schedule Synchronization Interrupts **/
#define FDCAN_TT_INT_BASIC_CYCLE_START       (FDCAN_TTIE_SBCE) /* Start of Basic Cycle           */
#define FDCAN_TT_INT_MATRIX_CYCLE_START      (FDCAN_TTIE_SMCE) /* Start of Matrix Cycle          */
#define FDCAN_TT_INT_SYNC_MODE_CHANGE        (FDCAN_TTIE_CSME) /* Change of Synchronization Mode */
#define FDCAN_TT_INT_START_OF_GAP            (FDCAN_TTIE_SOGE) /* Start of Gap                   */

/** FDCAN TT Time Mark Interrupts **/
#define FDCAN_TT_INT_REG_TIME_MARK           (FDCAN_TTIE_RTMIE) /* Register Time Mark Interrupt     */
#define FDCAN_TT_INT_TRIG_TIME_MARK          (FDCAN_TTIE_TTMIE) /* Trigger Time Mark Event Internal */

/** FDCAN TT Stop Watch Interrupt **/
#define FDCAN_TT_INT_STOP_WATCH              (FDCAN_TTIE_SWEE) /* Stop Watch Event */

/** FDCAN TT Global Time Interrupts **/
#define FDCAN_TT_INT_GLOBAL_TIME_WRAP        (FDCAN_TTIE_GTWE) /* Global Time Wrap          */
#define FDCAN_TT_INT_GLOBAL_TIME_DISC        (FDCAN_TTIE_GTDE) /* Global Time Discontinuity */

/** FDCAN TT Disturbing Error Interrupts **/
#define FDCAN_TT_INT_GLOBAL_TIME_ERROR       (FDCAN_TTIE_GTEE) /* Global Time Error   */
#define FDCAN_TT_INT_TX_COUNT_UNDERFLOW      (FDCAN_TTIE_TXUE) /* Tx Count Underflow  */
#define FDCAN_TT_INT_TX_COUNT_OVERFLOW       (FDCAN_TTIE_TXOE) /* Tx Count Overflow   */
#define FDCAN_TT_INT_SCHEDULING_ERROR_1      (FDCAN_TTIE_SE1E) /* Scheduling Error 1  */
#define FDCAN_TT_INT_SCHEDULING_ERROR_2      (FDCAN_TTIE_SE2E) /* Scheduling Error 2  */
#define FDCAN_TT_INT_ERROR_LEVEL_CHANGE      (FDCAN_TTIE_ELCE) /* Error Level Changed */

/** FDCAN TT Fatal Error Interrupts **/
#define FDCAN_TT_INT_INIT_WATCH_TRIGGER      (FDCAN_TTIE_IWTE) /* Initialization Watch Trigger */
#define FDCAN_TT_INT_WATCH_TRIGGER           (FDCAN_TTIE_WTE ) /* Watch Trigger                */
#define FDCAN_TT_INT_APPLICATION_WATCHDOG    (FDCAN_TTIE_AWE ) /* Application Watchdog         */
#define FDCAN_TT_INT_CONFIG_ERROR            (FDCAN_TTIE_CERE) /* Configuration Error          */

/*** Registers bit offset define ***/

/** FDCAN DBTP register bit offset define **/
#define FDCAN_DBTP_DTSEG2_OFFSET            (REG_BIT4_OFFSET)   /* Date time segment after sample point */
#define FDCAN_DBTP_DTSEG1_OFFSET            (REG_BIT8_OFFSET)   /* Date time segment before sample point */
#define FDCAN_DBTP_DBRP_OFFSET              (REG_BIT16_OFFSET)  /* Date Bit Rate Prescaler */
#define FDCAN_DBTP_DSJW_OFFSET              (REG_BIT0_OFFSET)   /* Date (Re)Synchronization Jump Width */

/** FDCAN NBTP register bit offset define **/
#define FDCAN_NBTP_NTSEG2_OFFSET            (REG_BIT0_OFFSET)   /* Nominal time segment after sample point */
#define FDCAN_NBTP_NTSEG1_OFFSET            (REG_BIT8_OFFSET)   /* Nominal time segment before sample point */
#define FDCAN_NBTP_NBRP_OFFSET              (REG_BIT16_OFFSET)  /* Nominal Bit Rate Prescaler */
#define FDCAN_NBTP_NSJW_OFFSET              (REG_BIT25_OFFSET)  /* Nominal (Re)Synchronization Jump Width */

/** FDCAN TOCC register bit offset define **/
#define FDCAN_TOCC_TOP_OFFSET               (REG_BIT16_OFFSET)  /* Timeout Period */

/** FDCAN ECR register bit offset define **/ 
#define FDCAN_ECR_REC_OFFSET                (REG_BIT8_OFFSET)   /* Receive Error Counter */
#define FDCAN_ECR_CEL_OFFSET                (REG_BIT16_OFFSET)  /* FDCAN Error Logging*/

/** FDCAN PSR register bit offset define **/ 
#define FDCAN_PSR_TDCV_OFFSET               (REG_BIT16_OFFSET)  /* FDCAN Transmitter Delay Compensation Value */

/** FDCAN TDCR register bit offset define **/
#define FDCAN_TDCR_TDCO_OFFSET              (REG_BIT8_OFFSET)  /* ransmitter Delay Compensation SSP Offset */

/** FDCAN HPMS register bit offset define **/
#define FDCAN_HPMS_FIDX_OFFSET              (REG_BIT8_OFFSET)   /* Filter Index */

/** FDCAN RXESC register bit offset define **/
#define FDCAN_RXESC_F0DS_OFFSET             (REG_BIT0_OFFSET )  /* FDCAN Rx FIFO 0 element size */
#define FDCAN_RXESC_F1DS_OFFSET             (REG_BIT4_OFFSET )  /* FDCAN Rx FIFO 1 element size */
#define FDCAN_RXESC_RBDS_OFFSET             (REG_BIT8_OFFSET )  /* FDCAN Rx Buffer element size */

/** FDCAN RXF0C/RXF1C register bit offset define **/
#define FDCAN_RXFXC_FXWM_OFFSET             (REG_BIT24_OFFSET ) /* FDCAN Rx FIFO 0/1 watermark */

/** FDCAN RXF0C/RXF1C register bit offset define **/
#define FDCAN_RXFXS_FXGI_OFFSET             (REG_BIT8_OFFSET )  /* FDCAN Rx FIFO 0/1 Get Index */

/** FDCAN start address and size bit offset define, used for:
    - Standard filter list
    - Extended filter list 
    - Rx FIFO0 
    - Rx FIFO1
    - Rx buffer
    - Tx event FIFO 
    - Tx buffer
    - Trigger Memory
    **/
#define FDCAN_START_ADDRESS_OFFSET          (REG_BIT2_OFFSET)   /* Start address        */
#define FDCAN_SIZE_NUMBER_OFFSET            (REG_BIT16_OFFSET)  /* Number of elements   */

/** FDCAN TXBC register bit offset define **/
#define FDCAN_TXBC_TFQS_OFFSET              (REG_BIT24_OFFSET)  /* Tx FIFO/queue elements number */
#define FDCAN_TXBC_NDTB_OFFSET              (REG_BIT16_OFFSET)  /* Number of Dedicated Transmit Buffers */

/** FDCAN TXFQS register bit offset define **/
#define FDCAN_TXFQS_TFQPI_OFFSET            (REG_BIT16_OFFSET)  /* Tx FIFO/Queue Put Index */

/** FDCAN TXEFS register bit offset define **/
#define FDCAN_TXEFS_EFGI_OFFSET             (REG_BIT8_OFFSET)   /** FDCAN Tx event fifo get index */

/* FDCAN start address SRAM5 BANK select */
#define FDCAN_START_ADDRESS_SRAM5BANK1      ((uint32_t)0x30050000U)   /* Select SRAM5 BANK1: 0x30050000 as FDCAN base address.  */
#define FDCAN_START_ADDRESS_SRAM5BANK2      ((uint32_t)0x30054000U)   /* Select SRAM5 BANK2: 0x30054000 as FDCAN base address.  */
#define FDCAN_START_ADDRESS_RAMSEL          (FDCAN_TTSS_RAMSEL)      /* Message RAM select.  */
/** FDCAN TTRMC register bit offset define **/ 
#define FDCAN_TTRMC_STD_ID_OFFSET           (REG_BIT18_OFFSET)  /* TT Standard Reference Identifier */

/** FDCAN TTOCF register bit offset define **/ 
#define FDCAN_TTOCF_LDSDL_OFFSET            (REG_BIT5_OFFSET)   /* TT LD of Synchronization Deviation Limit */
#define FDCAN_TTOCF_IRTO_OFFSET             (REG_BIT8_OFFSET)   /* TT Initial Reference Trigger Offset*/
#define FDCAN_TTOCF_AWL_OFFSET              (REG_BIT16_OFFSET)  /* TT Application Watchdog Limit */

/** FDCAN TTMLM register bit offset define **/ 
#define FDCAN_TTMLM_TXEW_OFFSET             (REG_BIT8_OFFSET)   /* TT Tx Enable Window */
#define FDCAN_TTMLM_ENIT_OFFSET             (REG_BIT16_OFFSET)  /* TT Expected Number of Tx Triggers */

/** FDCAN TURCF register bit offset define **/ 
#define FDCAN_TURCF_DC_OFFSET               (REG_BIT16_OFFSET)  /* TT Time Unit Ratio */

/** FDCAN TTGTP register bit offset define **/ 
#define FDCAN_TTGTP_CTP_OFFSET              (REG_BIT16_OFFSET)  /* TT Cycle Time Target Phase */

/** FDCAN TTTMK register bit offset define **/ 
#define FDCAN_TTTMK_TICC_OFFSET             (REG_BIT16_OFFSET)  /* TT Time Mark Cycle Code */

/** FDCAN TTOST register bit offset define **/
#define FDCAN_TTOST_RTO_OFFSET              (REG_BIT8_OFFSET)   /* TT Reference trigger offset */
#define FDCAN_TTOST_TMP_OFFSET              (REG_BIT24_OFFSET)  /* TT Time master priority */
/** Variable declaration **/
extern FDCAN_MsgRamType  FDCAN_MsgRam;

/** Function declaration **/
void FDCAN_DeInit(FDCAN_Module* FDCANx);
ErrorStatus FDCAN_Init(FDCAN_Module* FDCANx, FDCAN_InitType *FDCAN_InitParam);
ErrorStatus FDCAN_EnterSleep(FDCAN_Module *FDCANx);
ErrorStatus FDCAN_ExitSleep(FDCAN_Module *FDCANx);
void FDCAN_EnableISOMode(FDCAN_Module *FDCANx);
void FDCAN_DisableISOMode(FDCAN_Module *FDCANx);
void FDCAN_EnableEdgeFilter(FDCAN_Module *FDCANx);
void FDCAN_DisableEdgeFilter(FDCAN_Module *FDCANx);
void FDCAN_Start(FDCAN_Module *FDCANx);
ErrorStatus FDCAN_Stop(FDCAN_Module *FDCANx);
void FDCAN_GetProtocolStatus(FDCAN_Module *FDCANx, FDCAN_ProtocolStatus *ProtocolStatus);
void FDCAN_GetErrorCounters(FDCAN_Module *FDCANx, FDCAN_ErrorCounters *ErrorCounters);
void FDCAN_ConfigRamWatchdog(FDCAN_Module *FDCANx, uint32_t Value);
uint32_t FDCAN_CheckRestrictedMode(FDCAN_Module *FDCANx);
void FDCAN_ExitRestrictedMode(FDCAN_Module *FDCANx);

void FDCAN_ConfigFilter(FDCAN_Module *FDCANx, FDCAN_FilterType *sFilterConfig);
void FDCAN_ConfigGlobalFilter(FDCAN_Module *FDCANx, 
                            uint32_t NonMatchingStd,
                            uint32_t NonMatchingExt,
                            uint32_t RejectRemoteStd,
                            uint32_t RejectRemoteExt);
void FDCAN_ConfigExtIdMask(FDCAN_Module *FDCANx, uint32_t Mask);


void FDCAN_ConfigRxFifoMode(FDCAN_Module *FDCANx, uint32_t RxFifo, uint32_t Mode);
void FDCAN_ConfigFifoWatermark(FDCAN_Module *FDCANx, uint32_t FIFO, uint32_t Watermark);
uint32_t FDCAN_GetRxFifoFillLevel(FDCAN_Module *FDCANx, uint32_t RxFifo);

ErrorStatus FDCAN_GetRxMsg(FDCAN_Module *FDCANx, uint32_t RxLocation, FDCAN_RxHeaderType *pRxHeader, uint8_t *pRxData);
void FDCAN_GetHpMsgStatus(FDCAN_Module *FDCANx, FDCAN_HpMsgStatus *HpMsgStatus);
ErrorStatus FDCAN_CheckNewRxBufMsg(FDCAN_Module *FDCANx, uint32_t Index);

void FDCAN_ConfigTSPrescaler(FDCAN_Module *FDCANx, uint32_t Prescaler);
void FDCAN_Config_TS(FDCAN_Module *FDCANx, uint32_t Select);
uint16_t FDCAN_Get_TS(FDCAN_Module *FDCANx);
void FDCAN_Reset_TS(FDCAN_Module *FDCANx);
void FDCAN_ConfigExtTSDivider(FDCAN_Module *FDCANx, uint32_t Div);
void FDCAN_EnableExtTS(FDCAN_Module *FDCANx, FunctionalState Cmd);
void FDCAN_ConfigTimeoutCounter(FDCAN_Module *FDCANx, uint32_t TimeoutSelect, uint32_t TimeoutPeriod);
void FDCAN_EnableTimeoutCounter(FDCAN_Module *FDCANx);
void FDCAN_DisableTimeoutCounter(FDCAN_Module *FDCANx);
uint16_t FDCAN_GetTimeoutCounter(FDCAN_Module *FDCANx);
void FDCAN_ResetTimeoutCounter(FDCAN_Module *FDCANx);

void FDCAN_ConfigTxDelayCompensation(FDCAN_Module *FDCANx, uint32_t Offset, uint32_t Filter);
void FDCAN_EnableTxDelayCompensation(FDCAN_Module *FDCANx);
void FDCAN_DisableTxDelayCompensation(FDCAN_Module *FDCANx);

ErrorStatus FDCAN_AddMsgToTxFifoQ(FDCAN_Module *FDCANx, FDCAN_TxHeaderType *pTxHeader, uint8_t *pTxData);
ErrorStatus FDCAN_AddMsgToTxBuffer(FDCAN_Module *FDCANx, FDCAN_TxHeaderType *pTxHeader, uint8_t *pTxData, uint32_t BufferIndex);
void FDCAN_EnableTxBufferRequest(FDCAN_Module *FDCANx, uint32_t BufferIndex);
uint32_t FDCAN_GetLastTxFifoQReqBuf(FDCAN_Module *FDCANx);
void FDCAN_AbortTxRequest(FDCAN_Module *FDCANx, uint32_t BufferIndex);
ErrorStatus FDCAN_GetTxEvent(FDCAN_Module *FDCANx, FDCAN_TxEventFifoType *pTxEvent);
FlagStatus FDCAN_CheckTxBufRequest(FDCAN_Module *FDCANx, uint32_t IndexBit);
FlagStatus FDCAN_CheckBufTxResult(FDCAN_Module *FDCANx, uint32_t IndexBit);
FlagStatus FDCAN_CheckBufTxCancel(FDCAN_Module *FDCANx, uint32_t IndexBit);
uint32_t FDCAN_GetTxFifoFreeLevel(FDCAN_Module *FDCANx);

ErrorStatus FDCAN_TT_Init(FDCAN_Module *FDCANx, FDCAN_TT_InitType *pTTParams);
void FDCAN_TT_ConfigRefMsg(FDCAN_Module *FDCANx, uint32_t IdType, uint32_t ID, uint32_t Payload);
void FDCAN_TT_ConfigTrigger(FDCAN_Module *FDCANx, FDCAN_TriggerType *sTriggerConfig);
ErrorStatus FDCAN_TT_SetGlobalTime(FDCAN_Module *FDCANx, uint32_t TimePreset);
ErrorStatus FDCAN_TT_SetClockSync(FDCAN_Module *FDCANx, uint32_t NewTURNumerator);
ErrorStatus FDCAN_TT_ConfigStopWatch(FDCAN_Module *FDCANx, uint32_t Source, uint32_t Polarity);
ErrorStatus FDCAN_TT_ConfigRegTimeMark(FDCAN_Module *FDCANx,
                                        uint32_t TimeMarkSource, uint32_t TimeMarkValue,
                                        uint32_t RepeatFactor, uint32_t StartCycle);
ErrorStatus FDCAN_TT_EnableRegTMPulse(FDCAN_Module *FDCANx, FunctionalState Cmd);
ErrorStatus FDCAN_TT_EnableTrigTMPulse(FDCAN_Module *FDCANx, FunctionalState Cmd);
ErrorStatus FDCAN_TT_EnableGapPinCtrl(FDCAN_Module *FDCANx, FunctionalState Cmd);
ErrorStatus FDCAN_TT_EnableTMGapCtrl(FDCAN_Module *FDCANx, FunctionalState Cmd);
ErrorStatus FDCAN_TT_SetNextIsGap(FDCAN_Module *FDCANx);
ErrorStatus FDCAN_TT_SetEndOfGap(FDCAN_Module *FDCANx);
ErrorStatus FDCAN_TT_ConfigExtSyncPhase(FDCAN_Module *FDCANx, uint32_t TargetPhase);
ErrorStatus FDCAN_TT_EnableExtSync(FDCAN_Module *FDCANx, FunctionalState Cmd);
void FDCAN_TT_GetStatus(FDCAN_Module *FDCANx, FDCAN_TT_Status *TTStatus);

FlagStatus FDCAN_GetFlag(FDCAN_Module *FDCANx, uint32_t Flag);
void FDCAN_ClearFlag(FDCAN_Module *FDCANx, uint32_t Flag);
void FDCAN_ConfigIntLine(FDCAN_Module *FDCANx, uint32_t Int, uint32_t IntLine);
void FDCAN_EnableInt(FDCAN_Module *FDCANx, uint32_t Int);
void FDCAN_DisableInt(FDCAN_Module *FDCANx, uint32_t Int);
FlagStatus FDCAN_GetIntFlag(FDCAN_Module *FDCANx, uint32_t Flag);
ErrorStatus FDCAN_ActivateInt(FDCAN_Module *FDCANx, uint32_t Int, uint32_t BufferIndexes);
void FDCAN_DeactivateInt(FDCAN_Module *FDCANx, uint32_t Int);

FlagStatus FDCAN_TT_GetIntFlag(FDCAN_Module *FDCANx, uint32_t TT_Flag);
FlagStatus FDCAN_TT_GetFlag(FDCAN_Module *FDCANx, uint32_t TT_Flag);
void FDCAN_TT_ClearFlag(FDCAN_Module *FDCANx, uint32_t TT_Flag);
void FDCAN_TT_ConfigIntLine(FDCAN_Module *FDCANx, uint32_t TT_Int, uint32_t IntLine);
void FDCAN_TT_EnableInt(FDCAN_Module *FDCANx, uint32_t TT_Int, FunctionalState Cmd);
void FDCAN_TT_DisableInt(FDCAN_Module *FDCANx, uint32_t TT_Int);
FlagStatus FDCAN_TT_GetInt(FDCAN_Module *FDCANx, uint32_t TT_Flag);
ErrorStatus FDCAN_TT_ActivateInt(FDCAN_Module *FDCANx, uint32_t TT_Int);
void FDCAN_TT_DeactivateInt(FDCAN_Module *FDCANx, uint32_t TT_Int);

#ifdef __cplusplus
}
#endif

#endif /* __N32H76X_78X_FDCAN_H__ */


