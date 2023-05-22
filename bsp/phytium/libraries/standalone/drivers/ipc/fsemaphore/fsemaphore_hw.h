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
 * FilePath: fsemaphore_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:52
 * Description:  This file is for semaphore register definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/5/23    init commit
 */


#ifndef  FSEMAPHORE_HW_H
#define  FSEMAPHORE_HW_H
/***************************** Include Files *********************************/

#include "fparameters.h"
#include "ftypes.h"
#include "fio.h"
#include "fassert.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
/** @name Register Map
 *
 * Register offsets from the base address of an Semaphore.
 * @{
 */
#define FSEMA_RST_REG_OFFSET             0x0U /* 写 1 复位所有信号量 */
#define FSEMA_IND_RST_REG_OFFSET         0x4U /* 写信号量独热码为 1，复位对应信号量 */
#define FSEMA_STATE_REG_OFFSET           0x8U /* 信号量 0 ~ 31的状态 */
#define FSEMA_RLOCK_X_REG_OFFSET(x)      (0x10U + (x) * 4)  /* 信号量 X 读锁定寄存器 */

/** @name FSEMA_RST_REG_OFFSET Register
 */
#define FSEMA_RST_ALL                   BIT(0) /* 写 1 复位所有信号量 */

/** @name FSEMA_IND_RST_REG_OFFSET Register
 */
#define FSEMA_IND_RSET(locker_idx)      BIT(locker_idx) /* 写信号量独热码为 1，复位对应信号量 */

/** @name FSEMA_STATE_REG_OFFSET Register
 */
#define FSEMA_LOCKER_STATE(locker_idx)  BIT(locker_idx) /* 状态:0 表示解锁，1 表示锁定 */

/** @name FSEMA_RLOCK_X_REG_OFFSET Register
 */
#define FSEMA_RLOCK_X_UNLOCK               0  /* 写 0：信号量被解锁 */
/* 读返回 0：信号量当前未被锁定，读后被锁定
   读返回 1：信号量当前已经被锁定，锁定失败 */
#define FSEMA_RLOCK_X_IS_LOCKED         1
#define FSEMA_RLOCK_X_TAKE_LOCKER       0

#define FSEMA_MIN_LOCKER_IDX            0
#define FSEMA_MAX_LOCKER_IDX            31

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
static u32 FSemaReadReg(uintptr base_addr, u32 reg_off)
{
    return FtIn32(base_addr + reg_off);
}

static inline void FSemaWriteReg(uintptr base_addr, u32 reg_off, u32 reg_val)
{
    FtOut32(base_addr + reg_off, reg_val);
    return;
}

/**
 * @name: FSemaHwResetAll
 * @msg: 强制解除所有锁定
 * @return {void} 无
 * @param {uintptr} base_addr, Semaphore 控制器基地址
 */
static inline void FSemaHwResetAll(uintptr base_addr)
{
    FSemaWriteReg(base_addr, FSEMA_RST_REG_OFFSET, FSEMA_RST_ALL);
}

/**
 * @name: FSemaHwResetLocker
 * @msg: 强制解除指定锁定
 * @return {void} 无
 * @param {uintptr} base_addr, Semaphore 控制器基地址
 * @param {u32} locker_idx, Semaphore锁id
 */
static inline void FSemaHwResetLocker(uintptr base_addr, u32 locker_idx)
{
    u32 reg_val = FSemaReadReg(base_addr, FSEMA_IND_RST_REG_OFFSET);
    reg_val |= FSEMA_IND_RSET(locker_idx);
    FSemaWriteReg(base_addr, FSEMA_IND_RST_REG_OFFSET, reg_val);
    return;
}

/**
 * @name: FSemaHwGetStatus
 * @msg: 获取锁定状态
 * @return {boolean} TRUE: 被锁定, FALSE: 未被锁定
 * @param {uintptr} base_addr, Semaphore 控制器基地址
 * @param {u32} locker_idx, Semaphore锁id
 */
static inline boolean FSemaHwGetStatus(uintptr base_addr, u32 locker_idx)
{
    u32 reg_val = FSemaReadReg(base_addr, FSEMA_STATE_REG_OFFSET);
    return (reg_val & FSEMA_LOCKER_STATE(locker_idx)) ? TRUE : FALSE;
}

/**
 * @name: FSemaTryLockOnce
 * @msg: 尝试锁定
 * @return {boolean} TRUE: 锁定成功
 * @param {uintptr} base_addr, Semaphore 控制器基地址
 * @param {u32} locker_idx, Semaphore锁id
 */
static inline boolean FSemaTryLockOnce(uintptr base_addr, u32 locker_idx)
{
    boolean lock_success = FALSE;
    u32 reg_val = FSemaReadReg(base_addr, FSEMA_RLOCK_X_REG_OFFSET(locker_idx)); /* 读寄存器，尝试上锁 */

    /* 读返回 1：信号量之前已经被锁定，本次锁定失败
       读返回 0：信号量之前未被锁定，本次锁定成功 */
    return (FSEMA_RLOCK_X_IS_LOCKED & reg_val) ? FALSE : TRUE;
}

/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif