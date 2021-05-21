/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-27 16:02:36
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef SYSTEM_GIC_H
#define SYSTEM_GIC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"
#include "ft_gicv3.h"
#include "ft_error_code.h"

#define SYSGIC_SUCCESS FST_SUCCESS                                                 /* SUCCESS */
#define SYSGIC_FAILURE FT_MAKE_ERRCODE(errGicV3, errPort, FST_FAILURE)             /* Normal */
#define SYSGIC_TIMEOUT FT_MAKE_ERRCODE(errGicV3, errPort, FST_TIMEOUT)             /* Timeout */
#define SYSGIC_EILSEQ FT_MAKE_ERRCODE(errGicV3, errPort, FST_EILSEQ)               /* Illegal byte sequence. */
#define SYSGIC_INVALID_PARAM FT_MAKE_ERRCODE(errGicV3, errPort, FST_INVALID_PARAM) /* Invalid param. */

    void System_Gic_Init(void);
    void System_Gic_Enable(u32 InterruptID, FGicv3_InterruptHandler_t InterruptHandler, u32 Priority, void *Args);
    void System_Gic_Disable(u32 InterruptID);
    void System_GicMask(u32 InterruptID);
    void System_GicUnMask(u32 InterruptID);
    void System_GicAck(s32 InterruptID);
    void System_GicSetPriority(u32 InterruptID, u32 Priority);
    s32 System_GicGetActiveIrq(void);
    ft_error_t System_IpiGen(s32 InterruptID, s32 CpuId);

#ifdef __cplusplus
}
#endif

#endif // !