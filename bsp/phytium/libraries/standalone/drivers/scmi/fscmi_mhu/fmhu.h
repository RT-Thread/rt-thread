/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: fmhu.h
 * Date: 2022-12-29 18:07:43
 * LastEditTime: 2022-12-29 18:07:43
 * Description:  This file is for mhu function support and data struct
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0 liushengming 2023/01/04 init
 */
#ifndef FMHU_H
#define FMHU_H

#include "ftypes.h"
#include "ferror_code.h"


#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
#define FMHU_SUCCESS          FT_SUCCESS
#define FMHU_ERR_INVAL_PARM   FT_MAKE_ERRCODE(ErrModBsp, ErrBspMhu, 1)
#define FMHU_ERR_NOT_READY    FT_MAKE_ERRCODE(ErrModBsp, ErrBspMhu, 2)
#define FMHU_ERR_TIMEOUT      FT_MAKE_ERRCODE(ErrModBsp, ErrBspMhu, 3)
#define FMHU_ERR_NOT_SUPPORT  FT_MAKE_ERRCODE(ErrModBsp, ErrBspMhu, 4)
#define FMHU_ERR_INVAL_STATE  FT_MAKE_ERRCODE(ErrModBsp, ErrBspMhu, 5)

#define FSCMI_MBOX_TX_QUEUE_LEN 20

typedef void (*FMhuEvtHandler)(void *instance_p, void *param);

typedef struct
{
    u32         mhu_chan_id;    /* Mhu chan id */
    uintptr     base_addr;      /* Device base address */
    u32         irq_num;        /* Device intrrupt id */
    u32         irq_prority;    /* Device intrrupt priority */
    u32         work_mode;      /* Device work mode intr or poll */
} FMhuConfig;

typedef struct
{
    FMhuConfig      config;     /* Current active configs */
    u32             is_ready;   /* Device is initialized and ready */
    volatile u32    status;     /* Mhu working or idle */
    FMhuEvtHandler  slot_msg_recv;/* for interrupt handle */
} FMhu;

typedef struct
{
    FMhu            mhu;/* mbox object instance */
    boolean         tx_complete ;
    /* send message */
    u32             msg_count, msg_free;
    void            *msg_data[FSCMI_MBOX_TX_QUEUE_LEN];
    void            *payload; /* share memory */
    void            (*send_data)( uintptr addr , u32 chan);
    void            (*startup)( uintptr addr );
    void            (*shutdown)( uintptr addr );
    u32             (*last_tx_done)( uintptr addr );
} FScmiMhu;

void FMhuGetDefConfig(FMhuConfig *config_p,u32 chan_id);
void FMhuChanProbe(FScmiMhu *instance_p);
void FMhuChanRemove(FScmiMhu *instance_p);

#ifdef __cplusplus
}
#endif

#endif
