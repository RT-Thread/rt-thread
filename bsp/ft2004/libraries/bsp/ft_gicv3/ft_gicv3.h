/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-27 16:01:32
 * @Description:  This files is for gic v3.0
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */
#ifndef FT_GICV3_H
#define FT_GICV3_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_parameters.h"
#include "ft_types.h"
#include "ft_status.h"

#include "ft_error_code.h"

#define FGICV3_SUCCESS FST_SUCCESS                                                       /* SUCCESS */
#define FGICV3_FAILURE FT_MAKE_ERRCODE(errGicV3, errBspGeneral, FST_FAILURE)             /* Normal */
#define FGICV3_TIMEOUT FT_MAKE_ERRCODE(errGicV3, errBspGeneral, FST_TIMEOUT)             /* Timeout */
#define FGICV3_EILSEQ FT_MAKE_ERRCODE(errGicV3, errBspGeneral, FST_EILSEQ)               /* Illegal byte sequence. */
#define FGICV3_INVALID_PARAM FT_MAKE_ERRCODE(errGicV3, errBspGeneral, FST_INVALID_PARAM) /* Invalid param. */

    typedef void (*FGicv3_InterruptHandler_t)(void *data);

    /***************************Type Definitions*************************************/
    /*
        Handler 是对应与中断向量表中的函数
        Args 是默认传入的参数
    */
    typedef struct
    {
        FGicv3_InterruptHandler_t Handler;
        void *Args;
    } FGicv3_VectorTableEntry_t;

    /***** Typedef contains configuration for the device *******/
    typedef struct
    {
        u32 InstanceId;                                                  /* Id of device */
        u32 Gicv3BaseAddress;                                            /* gicv3 base Address */
        u32 Gicv3DistributorAddress;                                     /* gicv3 Distributor Address */
        u32 Gicv3RdAddress;                                              /*  the overall behavior of the Redistributor, for controlling LPIs, and for generating */
        u32 Gicv3SgiAddress;                                             /*  controlling and generating PPIs and SGIs. */
        FGicv3_VectorTableEntry_t HanderTable[FT_GICV3_VECTORTABLE_NUM]; /* Vector table */
    } FGicv3_Config_t;

    typedef struct
    {
        FGicv3_Config_t *Config;
        u32 IsReady;             /* Device is initialised and ready */
        u32 UnhandledInterrupts; /**< Intc Statistics */
    } FGicv3;

    s32 FGicv3_Config_tInitalize(FGicv3 *GicPtr, FGicv3_Config_t *ConfigPtr);
    s32 FGicV3_Connect(FGicv3 *GicPtr,
                       u32 InterruptID,
                       FGicv3_InterruptHandler_t InterruptHandler,
                       u32 Priority,
                       void *Args);
    void FGicV3_Disconnect(FGicv3 *GicPtr,
                           u32 InterruptID);
    void FGicV3_Enable(FGicv3 *GicPtr,
                       u32 InterruptID);
    void FGicV3_Disable(FGicv3 *GicPtr,
                        u32 InterruptID);
    FGicv3_Config_t *FGicv3_LookupConfig(u32 InstanceId);
    void System_IrqHandler(u32 IccIar_num);
    void FGicV3_SetPriority(FGicv3 *GicPtr, u32 InterruptID, u32 Priority);

#ifdef __cplusplus
}
#endif

#endif // !