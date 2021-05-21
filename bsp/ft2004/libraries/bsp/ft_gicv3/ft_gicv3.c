/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-18 18:07:24
 * @Description:  This files is for gic v3.0
 * 
 * @Modify History: 
 * Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_types.h"
#include "ft_assert.h"
#include "ft_printf.h"
#include "ft_io.h"
#include "ft_gicv3_hw.h"
#include "ft_gicv3.h"

/************************** Variable Definitions *****************************/
static u32 CpuId = 0;

/************************** Function Prototypes ******************************/

static void FGicv3_stubHandler(void *Args)
{
    Ft_assertVoid(Args != NULL);

    ((FGicv3 *)Args)->UnhandledInterrupts++;
}

/**
 * @name: Ft_GicV3_ConfigInitalize 
 * @msg:  gicv3 initialization
 * @param {FGicv3} *GicPtr
 * @param {Ft_Gicv3_Config} *ConfigPtr
 * @return {*}
 */
s32 FGicv3_Config_tInitalize(FGicv3 *GicPtr, FGicv3_Config_t *ConfigPtr)
{
    u32 InstanceId;
    Ft_assertNonvoid(GicPtr != NULL);
    Ft_assertNonvoid(ConfigPtr != NULL);

    if (GicPtr->IsReady != FT_COMPONENT_IS_READLY)
    {

        GicPtr->IsReady = 0U;
        GicPtr->Config = ConfigPtr;

        for (InstanceId = 0; InstanceId < FT_GICV3_VECTORTABLE_NUM; InstanceId++)
        {
            if (GicPtr->Config->HanderTable[InstanceId].Handler == NULL)
            {
                GicPtr->Config->HanderTable[InstanceId].Handler = FGicv3_stubHandler;
            }
            GicPtr->Config->HanderTable[InstanceId].Args = GicPtr;
        }

        FGicV3_Stop(GicPtr->Config, CpuId);
        FGicv3_InstanceInitialize(GicPtr->Config);
        GicPtr->IsReady = FT_COMPONENT_IS_READLY;
    }
    else
    {
        FGicv3_InstanceInitialize(GicPtr->Config);
    }

    return FST_SUCCESS;
}

/**
 * @name: Ft_GicV3_Connect
 * @msg:  使中断处理函数与中断源进行连接，Args 作为参数，在调用时被传入中断处理函数
 * @param {FGicv3} GicPtr
 * @param {u32} InterruptID
 * @param {Ft_FGicv3_InterruptHandler} InterruptHandler
 * @param {void *} Args
 * @return {s32}
 */
s32 FGicV3_Connect(FGicv3 *GicPtr,
                   u32 InterruptID,
                   FGicv3_InterruptHandler_t InterruptHandler,
                   u32 Priority,
                   void *Args)
{
    Ft_assertNonvoid(GicPtr != NULL);
    Ft_assertNonvoid(InterruptID < GIC_INT_MAX_NUM);
    Ft_assertNonvoid(NULL != InterruptHandler);
    Ft_assertNonvoid(GicPtr->IsReady == FT_COMPONENT_IS_READLY);

    if (FST_SUCCESS == FGicv3_RegisterHandler(GicPtr->Config, InterruptID, InterruptHandler, Args))
    {
        return FGicV3_SetPriTrigTypeByDistAddr(GicPtr->Config->Gicv3DistributorAddress,
                                               InterruptID,
                                               GIC_TRIGGER_LEVEL_SENSITIVE,
                                               Priority);
    }
    else
    {
        return FST_FAILURE;
    }
}

/**
 * @name: FGicV3_Disconnect
 * @msg:  断开中断源与中断函数间联系，并且关闭中断
 * @param {FGicv3}     
 * @param {InterruptID} 中断ID号
 * @return {*}
 */
void FGicV3_Disconnect(FGicv3 *GicPtr,
                       u32 InterruptID)
{
    Ft_assertVoid(GicPtr != NULL);
    Ft_assertVoid(InterruptID < GIC_INT_MAX_NUM);
    Ft_assertVoid(GicPtr->IsReady == FT_COMPONENT_IS_READLY);

    FGicV3_DisableInterrupt(GicPtr->Config, InterruptID);

    GicPtr->Config->HanderTable[InterruptID].Handler = FGicv3_stubHandler;
    GicPtr->Config->HanderTable[InterruptID].Args = GicPtr;
}

/**
 * @name: FGicV3_Enable 
 * @msg:  开启Gic 中对应InterruptID 的中断
 * @param {FGicv3 *} GicPtr
 * @param {InterruptID} 中断ID
 * @return {void}
 */
void FGicV3_Enable(FGicv3 *GicPtr,
                   u32 InterruptID)
{
    Ft_assertVoid(GicPtr != NULL);
    Ft_assertVoid(InterruptID < GIC_INT_MAX_NUM);
    Ft_assertVoid(GicPtr->IsReady == FT_COMPONENT_IS_READLY);

    FGicV3_EnableInterrupt(GicPtr->Config, InterruptID);
}

/**
 * @name: FGicV3_SetPriority
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 */
void FGicV3_SetPriority(FGicv3 *GicPtr,
                        u32 InterruptID, u32 Priority)
{
    Ft_assertVoid(GicPtr != NULL);
    Ft_assertVoid(InterruptID < GIC_INT_MAX_NUM);
    Ft_assertVoid(GicPtr->IsReady == FT_COMPONENT_IS_READLY);
    FGicV3_SetPriTrigTypeByDistAddr(GicPtr->Config->Gicv3DistributorAddress,
                                    InterruptID,
                                    GIC_TRIGGER_LEVEL_SENSITIVE,
                                    Priority);
}

/**
 * @name: FGicV3_Disable
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 */
void FGicV3_Disable(FGicv3 *GicPtr,
                    u32 InterruptID)
{
    Ft_assertVoid(GicPtr != NULL);
    Ft_assertVoid(InterruptID < GIC_INT_MAX_NUM);
    Ft_assertVoid(GicPtr->IsReady == FT_COMPONENT_IS_READLY);

    FGicV3_DisableInterrupt(GicPtr->Config, InterruptID);
}

/**
 * @name: System_IrqHandler
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {u32} IccIar_num
 */
void System_IrqHandler(u32 IccIar_num)
{
    FGicv3_InterruptHandler(IccIar_num & 0x3FFUL, 0);
}
