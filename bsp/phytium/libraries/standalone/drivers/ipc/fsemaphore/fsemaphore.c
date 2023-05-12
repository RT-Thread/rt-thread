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
 * FilePath: fsemaphore.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This file is for semaphore user api implmentation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/5/23    init commit
 */


/***************************** Include Files *********************************/
#include <string.h>

#include "fio.h"
#include "ferror_code.h"
#include "ftypes.h"
#include "fdebug.h"
#include "fassert.h"

#include "fsemaphore_hw.h"
#include "fsemaphore.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSEMA_DEBUG_TAG "SEMA"
#define FSEMA_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSEMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSEMA_WARN(format, ...)    FT_DEBUG_PRINT_W(FSEMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSEMA_INFO(format, ...)    FT_DEBUG_PRINT_I(FSEMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSEMA_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSEMA_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @name: FSemaCfgInitialize
 * @msg: 初始化Semaphore控制器
 * @return {FError} FSEMA_SUCCESS 表示初始化成功
 * @param {FSema} *instance, Semaphore控制器实例
 * @param {FSemaConfig} *input_config, Semaphore控制器配置
 */
FError FSemaCfgInitialize(FSema *const instance, const FSemaConfig *input_config)
{
    FASSERT(instance && input_config);
    uintptr base_addr = input_config->base_addr;
    FASSERT_MSG((0 != base_addr), "invalid base addr.");
    FError ret = FSEMA_SUCCESS;

    if (FT_COMPONENT_IS_READY == instance->is_ready)
    {
        FSEMA_WARN("Device is already initialized!!!");
    }

    if (&instance->config != input_config)
    {
        instance->config = *input_config;
    }

    FSemaHwResetAll(base_addr); /* 重置所有的锁 */

    if (FSEMA_SUCCESS == ret)
    {
        instance->is_ready = FT_COMPONENT_IS_READY;
    }

    return ret;
}

/**
 * @name: FSemaDeInitialize
 * @msg: 去初始化Semaphore控制器
 * @return {void} 无
 * @param {FSema} *instance, Semaphore控制器实例
 */
void FSemaDeInitialize(FSema *const instance)
{
    FASSERT(instance);
    u32 loop;
    uintptr base_addr = instance->config.base_addr;

    for (loop = 0; loop < FSEMA_NUM_OF_LOCKER; loop++)
    {
        if (NULL != instance->locker[loop])
        {
            FSEMA_WARN("locker %d @%p is not yet deleted !!!", loop, instance->locker[loop]);
            memset(instance->locker[loop], 0, sizeof(*instance->locker[loop]));
        }

    }

    if (0 != base_addr) /* 如果base addr为0，实例可能还没有初始化 */
    {
        FSemaHwResetAll(base_addr);
    }

    memset(instance, 0, sizeof(*instance));

    return;
}

/**
 * @name: FSemaCreateLocker
 * @msg: 分配和创建Semaphore锁
 * @return {FError} FSEMA_SUCCESS 表示分配成功
 * @param {FSema} *instance, Semaphore控制器实例
 * @param {FSemaLocker} *locker, Semaphore锁的实例
 */
FError FSemaCreateLocker(FSema *const instance, FSemaLocker *const locker)
{
    FASSERT(instance && locker);
    u32 locker_idx;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FSEMA_ERROR("Device@%p is not yet inited !!!", instance->config.base_addr);
        return FSEMA_ERR_NOT_INIT;
    }

    for (locker_idx = 0; locker_idx < FSEMA_NUM_OF_LOCKER; locker_idx++)
    {
        /* 分配一把未创建的锁 */
        if (NULL == instance->locker[locker_idx])
        {
            FSEMA_INFO("Allocate locker %d.", locker_idx);
            break;
        }
    }

    if (locker_idx >= FSEMA_NUM_OF_LOCKER)
    {
        FSEMA_ERROR("No locker available !!!");
        return FSEMA_ERR_NO_AVAILABLE_LOCKER; /* 所有的锁都已经分配创建 */
    }

    instance->locker[locker_idx] = locker;
    locker->index = locker_idx; /* 分配锁，将锁的实例挂在控制器实例上 */

    locker->owner = FSEMA_OWNER_NONE; /* 当前锁还没有owner */
    locker->name[0] = '\0';
    locker->sema = instance;

    return FSEMA_SUCCESS;
}

/**
 * @name: FSemaTryLock
 * @msg: 尝试获取Semaphore锁
 * @return {FError} FSEMA_SUCCESS 表示成功获取锁，FSEMA_ERR_LOCK_TIMEOUT 表示锁已经被占用
 * @param {FSemaLocker} *locker, Semaphore锁的实例
 * @param {u32} owner, 当前尝试获取锁的是谁
 * @param {u32} try_times, 尝试获取的次数
 * @param {FSemaRelaxHandler} relax_handler, 每次尝试获取锁失败后的relax函数
 */
FError FSemaTryLock(FSemaLocker *const locker, u32 owner, u32 try_times, FSemaRelaxHandler relax_handler)
{
    FASSERT(locker && locker->sema);
    FSema *const instance = locker->sema;
    uintptr base_addr = instance->config.base_addr;
    boolean lock_success = FALSE;
    FError ret = FSEMA_SUCCESS;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FSEMA_ERROR("Device@%p is not yet inited !!!", instance->config.base_addr);
        return FSEMA_ERR_NOT_INIT;
    }

    while (try_times > 0)
    {
        /* 尝试获取锁 */
        lock_success = FSemaTryLockOnce(base_addr, locker->index);
        if (TRUE == lock_success)
        {
            break;
        }

        if (relax_handler)
        {
            relax_handler(instance);
        }

        try_times--;
    }

    if (FALSE == lock_success)
    {
        ret = FSEMA_ERR_LOCK_TIMEOUT;
        FSEMA_ERROR("locker-%d has been taken by owner 0x%x.", locker->index, locker->owner);
    }
    else
    {
        locker->owner = owner; /* 记录当前locker的owner */
        FSEMA_INFO("locker-%d  is taken successfully by owner 0x%x.", locker->index, owner);
    }

    return ret;
}

/**
 * @name: FSemaUnlock
 * @msg: 尝试释放Semaphore锁
 * @return {FError} FSEMA_SUCCESS释放锁成功
 * @param {FSemaLocker} *locker, Semaphore锁实例
 * @param {u32} owner, 当前尝试释放锁的身份
 */
FError FSemaUnlock(FSemaLocker *const locker, u32 owner)
{
    FASSERT(locker && locker->sema);
    FSema *const instance = locker->sema;
    uintptr base_addr = instance->config.base_addr;
    FError ret = FSEMA_SUCCESS;
    u32 reg_val;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FSEMA_ERROR("Device@%p is not yet inited !!!", instance->config.base_addr);
        return FSEMA_ERR_NOT_INIT;
    }

    if (locker->owner != owner)
    {
        FSEMA_ERROR("locker is owned by 0x%x, 0x%x has no premission to unlock it !!!",
                    locker->owner, owner);
        return FSEMA_ERR_NO_PERMISSION;
    }

    if (FALSE == FSemaHwGetStatus(base_addr, locker->index))
    {
        FSEMA_INFO("locker-%d is not in locked status 0x%x!!!",
                   locker->index, FSemaReadReg(base_addr, FSEMA_STATE_REG_OFFSET));
        return ret;
    }

    reg_val = FSEMA_RLOCK_X_UNLOCK;
    FSemaWriteReg(base_addr, FSEMA_RLOCK_X_REG_OFFSET(locker->index), reg_val); /* 写0解锁信号量 */
    locker->owner = FSEMA_OWNER_NONE; /* 解锁成功，当前锁持有者为None */

    return ret;
}

/**
 * @name: FSemaUnlockAll
 * @msg: 强制解除所有Semaphore锁
 * @return {FError} FSEMA_SUCCESS表示强制解锁成功
 * @param {FSema} *instance, Semaphore控制器实例
 */
FError FSemaUnlockAll(FSema *const instance)
{
    FASSERT(instance);
    uintptr base_addr = instance->config.base_addr;
    u32 loop;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FSEMA_ERROR("Device@%p is not yet inited !!!", instance->config.base_addr);
        return FSEMA_ERR_NOT_INIT;
    }

    FSemaHwResetAll(base_addr);

    for (loop = 0; loop < FSEMA_NUM_OF_LOCKER; loop++)
    {
        if (NULL != instance->locker[loop])
        {
            instance->locker[loop]->owner = FSEMA_OWNER_NONE; /* 解锁成功，当前锁持有者为None */
        }
    }

    return FSEMA_SUCCESS;
}

/**
 * @name: FSemaDeleteLocker
 * @msg: 强制解除Semaphore锁并删除锁实例
 * @return {FError} FSEMA_SUCCESS 表示删除锁成功
 * @param {FSemaLocker} *locker, Semaphore锁实例
 */
FError FSemaDeleteLocker(FSemaLocker *const locker)
{
    FASSERT(locker && locker->sema);
    FSema *const instance = locker->sema;
    uintptr base_addr = instance->config.base_addr;
    u32 locker_idx = locker->index;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FSEMA_ERROR("Device@%p is not yet inited !!!", instance->config.base_addr);
        return FSEMA_ERR_NOT_INIT;
    }

    if (TRUE == FSemaHwGetStatus(base_addr, locker_idx))
    {
        FSEMA_WARN("Caution, locker-%d has been taken by 0x%x !!!",
                   locker_idx, locker->owner);
    }

    FASSERT_MSG((instance->locker[locker_idx] == locker), "invalid locker index %d.", locker_idx);

    FSemaWriteReg(base_addr, FSEMA_RLOCK_X_REG_OFFSET(locker->index), FSEMA_RLOCK_X_UNLOCK); /* 写0解锁信号量 */

    instance->locker[locker_idx] = NULL;
    memset(locker, 0, sizeof(*locker));

    return FSEMA_SUCCESS;
}

/**
 * @name: FSemaIsLocked
 * @msg: 检查指定Semaphore锁是否处于锁定状态
 * @return {boolean} TRUE: 处于锁定状态
 * @param {FSemaLocker} *locker, Semaphore锁实例
 */
boolean FSemaIsLocked(FSemaLocker *locker)
{
    FASSERT(locker && locker->sema);
    FSema *const instance = locker->sema;
    uintptr base_addr = instance->config.base_addr;

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FSEMA_ERROR("Device@%p is not yet inited !!!", instance->config.base_addr);
        return FSEMA_ERR_NOT_INIT;
    }

    return FSemaHwGetStatus(base_addr, locker->index);
}