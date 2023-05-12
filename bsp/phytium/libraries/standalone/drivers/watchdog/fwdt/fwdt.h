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
 * FilePath: fwdt.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:24:34
 * Description:  This file is for wdt ctrl function definition.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   Wangxiaodong 2021/8/26   init
 * 1.1   Wangxiaodong 2021/11/5    restruct
 */

#ifndef FWDT_H
#define FWDT_H

#include "ftypes.h"
#include "fdebug.h"
#include "ferror_code.h"
#include "fkernel.h"
#include "fassert.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FWDT_SUCCESS           FT_SUCCESS
#define FWDT_ERR_INVAL_PARM    FT_MAKE_ERRCODE(ErrModBsp, ErrBspWdt, 1)
#define FWDT_NOT_READY         FT_MAKE_ERRCODE(ErrModBsp, ErrBspWdt, 2)
#define FWDT_NOT_SUPPORT       FT_MAKE_ERRCODE(ErrModBsp, ErrBspWdt, 3)
#define FWDT_TIMEOUT           FT_MAKE_ERRCODE(ErrModBsp, ErrBspWdt, 4)

/* max timeout = 0xFFFFFFFF/ WDT_CLK = 89 */
#define FWDT_MAX_TIMEOUT 89

typedef struct
{
    u16 version;    /* wdt version */
    u8 continuation_code;/* JEP106 continuation code of the implementer */
    u8 identity_code;   /* JEP106 identity code of the implementer */
} FWdtIdentifier; /* wdt Identifier*/

typedef struct
{
    u32 instance_id;/* wdt id */
    uintptr refresh_base_addr;/* wdt refresh base addr */
    uintptr control_base_addr;/* wdt control base addr */
    u32 irq_num;    /* wdt irq num */
    u32 irq_prority;/* wdt irq priority */
    u32 irq_twice_num;    /* wdt twice irq num */
    u32 irq_twice_prority;/* wdt twice irq priority */
    const char *instance_name;/* instance name */
} FWdtConfig; /* wdt config */

typedef struct
{
    FWdtConfig config;  /* wdt config */
    u32 is_ready;   /* wdt initialize the complete flag */
} FWdtCtrl;


/* get wdt default configs */
const FWdtConfig *FWdtLookupConfig(u32 instance_id);

/* wdt config init */
FError FWdtCfgInitialize(FWdtCtrl *pctrl, const FWdtConfig *input_config_p);

/* wdt config deinit */
void FWdtDeInitialize(FWdtCtrl *pctrl);

/* set wdt timeout value*/
FError FWdtSetTimeout(FWdtCtrl *pCtrl, u32 timeout);

u32 FWdtGetTimeleft(FWdtCtrl *pctrl);

/* fresh the wdt */
FError FWdtRefresh(FWdtCtrl *pCtrl);

/* start wdt*/
FError FWdtStart(FWdtCtrl *pCtrl);

/* stop wdt*/
FError FWdtStop(FWdtCtrl *pCtrl);

/* read wdt w_iidr register*/
FError FWdtReadFWdtReadWIIDR(FWdtCtrl *pctrl, FWdtIdentifier *wdt_identify);

#ifdef __cplusplus
}
#endif

#endif