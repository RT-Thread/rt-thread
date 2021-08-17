/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-27 15:08:44
 * @LastEditTime: 2021-04-27 15:08:44
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#ifndef FT_CAN_H
#define FT_CAN_H

#include "ft_types.h"
#include "ft_error_code.h"

#define FCAN_SUCCESS FST_SUCCESS                                                     /* SUCCESS */
#define FCAN_FAILURE FT_MAKE_ERRCODE(errCan, errBspGeneral, FST_FAILURE)             /* Normal */
#define FCAN_TIMEOUT FT_MAKE_ERRCODE(errCan, errBspGeneral, FST_TIMEOUT)             /* Timeout */
#define FCAN_EILSEQ FT_MAKE_ERRCODE(errCan, errBspGeneral, FST_EILSEQ)               /* Illegal byte sequence. */
#define FCAN_INVALID_PARAM FT_MAKE_ERRCODE(errCan, errBspGeneral, FST_INVALID_PARAM) /* Invalid param. */

#define FCAN_HANDLER_SEND 1U  /**< Handler type for frame sending interrupt */
#define FCAN_HANDLER_RECV 2U  /**< Handler type for frame reception interrupt*/
#define FCAN_HANDLER_ERROR 3U /**< Handler type for error interrupt */
#define FCAN_DATA_LENGTH 8U

/* CAN payload length and DLC definitions according to ISO 11898-1 */
#define CAN_MAX_DLC 8
#define CAN_MAX_DLEN 8
#define CAN_MAX_CTL 3
#define CAN_SFF_ID_BITS 11
#define CAN_EFF_ID_BITS 29

/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000U /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000U /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000U /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFU /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFU /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFU /* omit EFF, RTR, ERR flags */

/* Frame type */
#define STANDARD_FRAME 0 /* standard frame */
#define EXTEND_FRAME 1   /* extended frame */

typedef void (*FCan_irqHandler_t)(void *Args);

struct FCan_Frame
{
    u32 CanId;
    u8 CanDlc;
    u8 data[FCAN_DATA_LENGTH];
};

struct FCan_Bittiming
{
    u32 bitrate;      /* Bit-rate in bits/second */
    u32 sample_point; /* Sample point in one-tenth of a percent */
    u32 tq;           /* Time quanta (TQ) in nanoseconds */
    u32 prop_seg;     /* Propagation segment in TQs */
    u32 phase_seg1;   /* Phase buffer segment 1 in TQs */
    u32 phase_seg2;   /* Phase buffer segment 2 in TQs */
    u32 sjw;          /* Synchronisation jump width in TQs */
    u32 brp;          /* Bit-rate prescaler */
};

typedef struct
{
    u32 InstanceId;     /* Id of device */
    u32 CanBaseAddress; /* Can base Address */
    u32 IrqNum;
    u32 BaudRate;
    u32 TxFifoDeepth; /* The depth of the full frame , */
} FCan_Config_t;

typedef struct
{
    FCan_Config_t Config;
    u32 IsReady; /* Device is initialized and ready */

    volatile u32 TxFifoCnt;

    FCan_irqHandler_t SendHandler;
    void *SendRef;

    FCan_irqHandler_t RecvHandler;
    void *RecvRef;

    FCan_irqHandler_t ErrorHandler;
    void *ErrorRef;

} FCan_t;

FCan_Config_t *FCan_LookupConfig(u32 InstanceId);

/**
 * @name: FCan_CfgInitialize
 * @msg:  This function initializes a Can instance/driver.
 * @in param Can_p:    Can_p is a pointer to the FCan_t instance.
 * @in param Config_p: Config_p points to the FCan_t device configuration structure.
 * @return {*}
 */
ft_error_t FCan_CfgInitialize(FCan_t *Can_p, FCan_Config_t *Config_p);

/**
 * @name: FCan_SetHandler
 * @msg:  This routine installs an asynchronous callback function for the given
 * @inout param Can_p: Can_p is a pointer to the FCan_t instance.
 * @in param HandlerType:  specifies which handler is to be attached.
 * @in param IrqCallBackFunc: IrqCallBackFunc is the address of the callback function.
 * @in param IrqCallBackRef: IrqCallBackRef is a user data item that will be passed to the
 *      callback function when it is invoked.
 * @return {*}
 * @param {FCan_t} *Can_p
 * @param {u32} HandlerType
 * @param {FCan_irqHandler_t} *IrqCallBackFunc
 * @param {void} *IrqCallBackRef
 */
ft_error_t FCan_SetHandler(FCan_t *Can_p, u32 HandlerType, FCan_irqHandler_t IrqCallBackFunc, void *IrqCallBackRef);

ft_error_t FCan_SetTiming(FCan_t *Can_p,
                          struct FCan_Bittiming *Bittiming_p);

void FCan_IntrHandler(void *InstancePtr);

ft_error_t FCan_CalcBittiming(struct FCan_Bittiming *Bt_p);

u32 FCan_SendByIrq(FCan_t *Can_p,
                   struct FCan_Frame *Frame_p,
                   u32 FrameNumber, void (*UserIrqWait)(void));

u32 FCan_RecvByIrq(FCan_t *Can_p, struct FCan_Frame *Frame_p, u32 FrameNumber);

void FCan_Enable(FCan_t *Can_p);

#endif // !FT_CAN_H
