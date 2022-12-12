/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-24 14:32:56
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.00a hh  2021-02-05 First release
 */

#ifndef FT_GMAC_H
#define FT_GMAC_H

#include "ft_types.h"
#define GMAC_INC_DESC(x, y) (x) = (((x) + 1) % y)
/**
 * @name: Callback invoked when frame(s) have been sent or received in interrupt
 *          driven DMA mode .to set the send callback ,invoke FGmac_SetHandler()
 * @msg:
 * @param {void} *CallBackRef
 * @return {*}
 */
typedef void (*FGmac_IntrCallback_t)(void *CallBackRef);

/**
 * @name:  FGmac_ErrIntrCallback_t
 * @msg:   Callback whem asynchronous error occurs. To set this callback, invoke
 *          FGmac_ErrIntrCallback_t .
 * @param {void} *CallBackRef
 * @param {u32} ErrorWord  definition varies with Error
 * @return {*}
 */
typedef void (*FGmac_ErrIntrCallback_t)(void *CallBackRef, u32 ErrorWord);

/**
 *
 *
 */
typedef void (*Ft_Gmac_MacPhyStatus_Callback)(void *CallBackRef, u32 MacPhyStatus);

/** GMAC_SPEED   */
#define GMAC_SPEED_10M 0x00000001U
#define GMAC_SPEED_100M 0x00000002U
#define GMAC_SPEED_1000M 0x00000004U

#define IS_RIGHT_SPEED()

/* GMAC_AutoNegotiation */
#define GMAC_AUTONEGOTIATION_ENABLE 0x00000001U
#define GMAC_AUTONEGOTIATION_DISABLE 0x00000000U

/* GMAC_Duplex_Mode */
#define GMAC_MODE_FULLDUPLEX 0x00000001U
#define GMAC_MODE_HALFDUPLEX 0x00000000U

/* GMAC_Rx_Mode */
#define GMAC_RXPOLLING_MODE 0x00000000U
#define GMAC_RXINTERRUPT_MODE 0x00000001U

/* GMAC_Checksum_Mode */
#define GMAC_CHECKSUM_BY_SOFTWARE 0x00000000U
#define GMAC_CHECKSUM_BY_HARDWARE 0x00000001U

/* GMAC_Media_Interface */
#define GMAC_MEDIA_INTERFACE_RGMII 0x00000000U
#define GMAC_MEDIA_INTERFACE_MII 0x00000001U

/* Gmac Error value */

#define GMAC_ERROR_TRANSMIT_PROCESS_STOPPED 0x00000001U
#define GMAC_ERROR_TRANSMIT_UNAVAILABLE_STATUS 0x00000002U
#define GMAC_ERROR_TRANSMIT_JABBER_TIMEOUT 0x00000004U
#define GMAC_ERROR_RECEIVE_FIFO_OVERFLOW 0x00000008U
#define GMAC_ERROR_TRANSMIT_UNDERFLOW 0x00000010U
#define GMAC_ERROR_RECEIVE_BUFFER_UNAVAILABLE 0x00000020U
#define GMAC_ERROR_RECEIVE_PROCESS_STOPPED 0x00000040U
#define GMAC_ERROR_RECEIVE_WATCHDOG_TIMEOUT 0x00000080U
#define GMAC_ERROR_EARLY_TRANSMIT_INTERRUPT 0x000000100U
#define GMAC_ERROR_FATAL_BUS_ERROR 0x000000200U
#define GMAC_ERROR_UNDEFINED 0x000000400U

typedef enum
{
    FT_GMAC_TX_COMPLETE_CB_ID = 0x01U,    /*!< Gmac Tx Complete Callback ID        */
    FT_GMAC_RX_COMPLETE_CB_ID = 0x02U,    /*!< Gmac Rx Complete Callback ID        */
    FT_GMAC_DMA_ERROR_CB_ID = 0x03U,      /*!< Gmac DMA Error Callback ID          */
    FT_GMAC_MAC_PHY_STATUS_CB_ID = 0x04U, /*!<           */
} FGmac_IsrCallbackSelect_t;

/* Gmac DMA Descriptors data structure definition */

typedef struct
{
    volatile u32 Status;     /*!< Status */
    u32 Control;             /*!< Control and Buffer1, Buffer2 lengths */
    u32 Buffer1Addr;         /*!< Buffer1 address pointer */
    u32 Buffer2NextDescAddr; /*!< Buffer2 or next descriptor address pointer */
} FGmac_DmaDesc_t;

/*  Received Frame Informations structure definition */
typedef struct
{
    FGmac_DmaDesc_t *FSRxDesc; /*!< First Segment Rx Desc */
    FGmac_DmaDesc_t *LSRxDesc; /*!< Last Segment Rx Desc */
    u32 SegCount;              /*!< Segment count */
    u32 length;                /*!< Frame length */
    u32 buffer;                /*!< Frame buffer */
} FGmac_DmaRxFrameInfos;

typedef struct
{
    u32 InstanceId;          /* Id of device */
    uintptr_t CommonAddress; /* Gmac Common Register */
    uintptr_t BaseAddress;   /* Physical base address of Mac Private Address */
    u32 IRQ_NUM;
    u32 IRQPriority;
    s32 PhyAddr;         /* Phy Ic Addre1 ,-1 is need to auto check*/
    u32 clkMDC;          /* MDC clock access PHY. [1.0MHz ~2.5MHz] */
    u32 AutoNegotiation; /* Selects or not the AutoNegotiation mode for the external PHY
                                                           The AutoNegotiation allows an automatic setting of the Speed (10/100/1000Mbps)
                                                           and the mode (half/full-duplex).
                                                           This parameter can be a value of @ref GMAC_AutoNegotiation */
    u32 Speed;           /* Sets the Ethernet speed: 10/100/1000 Mbps.
                                                           This parameter can be a value of @ref GMAC_SPEED */
    u32 DuplexMode;      /* Selects the MAC duplex mode: Half-Duplex or Full-Duplex mode
                                                           This parameter can be a value of @ref GMAC_Duplex_Mode */
    u32 RxMode;          /* Selects the Ethernet Rx mode: Polling mode, Interrupt mode.
                                                           This parameter can be a value of @ref GMAC_Rx_Mode */
    u32 ChecksumMode;    /* Selects if the checksum is check by hardware or by software.
                                                         This parameter can be a value of @ref GMAC_Checksum_Mode */
    u32 MediaInterface;  /* Selects the media-independent interface or the reduced media-independent interface.
                                                         This parameter can be a value of @ref GMAC_Media_Interface */
    u8 MacAddr[6];       /* 6 bytes Mac address */

} FGmac_Config_t;

/* Only for Dma ring structure */
struct DescRingData
{
    u32 DescIndex;     /* For Current Desc position */
    u32 DescBufIndex;  /* For Current Desc buffer buf position */
    u32 DescMaxNumber; /* Max Number for  Desc and Desc buffer */
    u8 *DescBufBase;   /*  Desc buffer Base */
};

typedef struct
{
    FGmac_Config_t Config; /* Hardware configuration */
    u32 IsReady;           /* Device is initialised and ready */
    u32 Options;           /* Current options word  */

    FGmac_DmaDesc_t *RxDesc; /*!< Rx descriptor to Get   */
    struct DescRingData RxDescRingData;
    FGmac_DmaDesc_t *TxDesc; /*!< Tx descriptor to Set   */
    struct DescRingData TxDescRingData;

    FGmac_IntrCallback_t SendHandler;
    FGmac_IntrCallback_t RecvHandler;
    Ft_Gmac_MacPhyStatus_Callback StatusHandler;
    void *SendArgs;
    void *RecvArgs;
    void *StatusArgs;
    FGmac_ErrIntrCallback_t ErrorHandler;
    void *ErrorArgs;

    FGmac_DmaRxFrameInfos DMARxFrameInfos; /* Only for chain structure */

} Ft_Gmac_t;

/**
 * @name: FGmac_DmaRxDescRingInit
 * @msg:  化标准 DMA 接收描述符 在ring结构下的初始化。
 * @param {Ft_Gmac_t} *Gmac  Gmac对象
 * @param {FGmac_DmaDesc_t} *DMARxDescTab 用户定义的静态 DMA 接收描述符表格
 * @param {u8} *RxBuff 用户定义的用于匹配 DMA 接收描述符表格的缓冲区
 * @param {u32} DescBufPerLength 每个缓冲区的大小
 * @param {u32} RxBuffCount 缓冲区的总数量
 * @return {s32} Common_status 参数。
 */
s32 FGmac_DmaRxDescRingInit(Ft_Gmac_t *Gmac,
                            FGmac_DmaDesc_t *DMATxDescTab,
                            u8 *TxBuff,
                            u32 DescBufPerLength,
                            u32 TxBuffCount);

/**
 * @name: FGmac_DmaTxDescRingInit
 * @msg:  标准 DMA 发送描述符 在ring结构下的初始化。
 * @param {Ft_Gmac_t} *Gmac Gmac对象
 * @param {FGmac_DmaDesc_t} *DMATxDescTab 用户定义的静态 DMA 发送描述符表格
 * @param {u8} *TxBuff  用户定义的用于匹配 DMA 发送描述符表格的缓冲区
 * @param {u32} DescBufPerLength 每个缓冲区的大小
 * @param {u32} TxBuffCount 缓冲区的总数量
 * @return {s32} Common_status 参数
 */
s32 FGmac_DmaTxDescRingInit(Ft_Gmac_t *Gmac,
                            FGmac_DmaDesc_t *DMATxDescTab,
                            u8 *TxBuff,
                            u32 DescBufPerLength,
                            u32 TxBuffCount);

/**
 * @name: FGmac_TransmitframeRingPoll
 * @msg:  轮询的方式发送DMA发送表述符
 * @param {Ft_Gmac_t} *Gmac Gmac对象
 * @param {uint32_t} FrameLength 需要发送数据的有效长度
 * @return {s32} Common_status 参数
 */
s32 FGmac_TransmitframeRingPoll(Ft_Gmac_t *Gmac, uint32_t FrameLength);

/**
 * @name: FGmac_RingGetReceivedFrame_IT
 * @msg:  检查标准ring结构的DMA接收符中是否有完整的数据包。
 * @param {Ft_Gmac_t} *Gmac Gmac对象
 * @return {s32} Common_status 参数
 */
s32 FGmac_RingGetReceivedFrame_IT(Ft_Gmac_t *Gmac);

/**
 * @name: FGmac_ResumeTransmission
 * @msg:  检查 DMA_STATUS_TU 符号是否存在，如果存在将其置位，恢复DMA 描述符的发送 。
 * @param {Ft_Gmac_t} *Gmac Gmac对象
 * @return {void}
 */
void FGmac_ResumeTransmission(Ft_Gmac_t *Gmac);

/**
 * @name: FGmac_SetTransmitUnderflow
 * @msg:  检查 DMA_STATUS_UNF 符号是否存在，如果存在将其置位，恢复DMA 描述符的发送 。
 * @param {Ft_Gmac_t} *Gmac Gmac对象
 * @return {void}
 */
void FGmac_SetTransmitUnderflow(Ft_Gmac_t *Gmac);

/**
 * @name: FGmac_ResumeTransmissionReception
 * @msg:  检查 DMA_STATUS_RU 符号是否存在，如果存在将其置位，恢复DMA 描述符的接收 。
 * @param {Ft_Gmac_t} *Gmac
 * @return {void}
 */
void FGmac_ResumeTransmissionReception(Ft_Gmac_t *Gmac);

/**
 * @name: Ft_Gmac_LookupConfig
 * @msg:  获取 Gmac 静态预设配置参数 。
 * @param {u32} InstanceId Gmac 实例编号。
 * @return {FGmac_Config_t *} 返回Gmac的静态配置
 */
FGmac_Config_t *Ft_Gmac_LookupConfig(u32 InstanceId);

/**
 * @name: Ft_Gmac_HwInitialize
 * @msg:  对于Gmac Mac 层 与Phy 层的硬件部分进行预设初始化配置
 * @param {Ft_Gmac_t} *Gmac Gmac对象。
 * @return {s32} Common_status 参数
 */
s32 Ft_Gmac_HwInitialize(Ft_Gmac_t *Gmac);

/**
 * @name: Ft_GmacCfgInitialize
 * @msg:  初始化，硬件配置相关参数。
 * @param {Ft_Gmac_t} *Gmac Gmac对象。
 * @param {FGmac_Config_t} *Config
 * @return {s32} Common_status 参数
 */
s32 Ft_GmacCfgInitialize(Ft_Gmac_t *Gmac, FGmac_Config_t *Config);

/**
 * @name: Ft_Gmac_Start
 * @msg:  开启Gmac 的 发送接收功能，并且开启中断功能。
 * @param {Ft_Gmac_t} *Gmac Gmac对象。
 * @return {s32}  Common_status 参数
 */
s32 Ft_Gmac_Start(Ft_Gmac_t *Gmac);

/**
 * @name: Ft_Gmac_Stop
 * @msg:  关闭Gmac 的 发送接收功能。
 * @param {Ft_Gmac_t} *Gmac Gmac对象。
 * @return {s32} Common_status 参数
 */
s32 Ft_Gmac_Stop(Ft_Gmac_t *Gmac);

/**
 * @name: FGmac_IntrHandler
 * @msg:  Gmac 中断函数，用于响应Gmac 相关所以函数
 * @param {void} *Args Ft_Gmac_t *Gmac 参数传入
 * @return {void}
 */
void FGmac_IntrHandler(void *Args);

/**
 * @name: FGmac_SetHandler
 * @msg:  根据SelectIndex 配置 中断过程中响应函数
 * @param {Ft_Gmac_t} *Gmac Gmac对象。
 * @param {FGmac_IsrCallbackSelect_t} SelectIndex
 * @param {void} *FuncPtr
 * @param {void} *Args
 * @return {s32} Common_status 参数
 */
s32 FGmac_SetHandler(Ft_Gmac_t *Gmac, FGmac_IsrCallbackSelect_t SelectIndex, void *FuncPtr, void *Args);

void Ft_Gmac_Phy_Debug(Ft_Gmac_t *Gmac);

/**
 * @name: Ft_Gmac_UseDefaultMacAddr
 * @msg:  在有uboot的模式之下，使用默认的Mac0配置参数。
 * @in param{Ft_Gmac_t *}:  Gmac对象
 * @out param{u8 *}:  输出的Mac参数
 * @return {None}:
 */
void Ft_Gmac_UseDefaultMacAddr(Ft_Gmac_t *Gmac, u8 *MacAddr);

#endif // !GMAC_H
