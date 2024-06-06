/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fpsci.c
 * Created Date: 2023-06-21 10:36:53
 * Last Modified: 2023-06-30 13:32:06
 * Description:  This file is for
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0      huanghe   2023-06-21    first release
 */


#include <stdio.h>
#include "fsmcc.h" /* 根据你的平台和编译环境来确定这个路径 */
#include "fpsci.h"
#include "fassert.h"
#include "fcompiler.h"
#include "fcpu_info.h"
#include "rtdbg.h"

/* 定义PSCI 函数值 */
#define FPSCI_0_2_FN32_BASE             0x84000000
#define FPSCI_0_2_FN64_BASE             0xC4000000
#define FPSCI_VERSION                   (FPSCI_0_2_FN32_BASE + 0x000)
#define FPSCI_FEATURES                  (FPSCI_0_2_FN32_BASE + 0x00a)
#define FPSCI_CPU_SUSPEND_AARCH32            (FPSCI_0_2_FN32_BASE + 0x001)
#define FPSCI_CPU_SUSPEND_AARCH64            (FPSCI_0_2_FN64_BASE + 0x001)
#define FPSCI_CPU_OFF                        (FPSCI_0_2_FN32_BASE + 0x002)
#define FPSCI_CPU_ON_AARCH32                 (FPSCI_0_2_FN32_BASE + 0x003)
#define FPSCI_CPU_ON_AARCH64                 (FPSCI_0_2_FN64_BASE + 0x003)
#define FPSCI_FAFFINITY_INFO_AARCH32          (FPSCI_0_2_FN32_BASE + 0x004)
#define FPSCI_FAFFINITY_INFO_AARCH64          (FPSCI_0_2_FN64_BASE + 0x004)
#define FPSCI_SYSTEM_OFF                     (FPSCI_0_2_FN32_BASE + 0x008)
#define FPSCI_SYSTEM_RESET                   (FPSCI_0_2_FN32_BASE + 0x009)
#define FPSCI_SYSTEM_SUSPEND                   (FPSCI_0_2_FN32_BASE + 0x00E)

/* 定义每个PSCI函数ID的位标记 */
#define FPSCI_PSCI_VERSION_BIT               (1 << 0)
#define FPSCI_PSCI_FEATURES_BIT              (1 << 1)
#define FPSCI_CPU_SUSPEND_AARCH32_BIT        (1 << 2)
#define FPSCI_CPU_SUSPEND_AARCH64_BIT        (1 << 3)
#define FPSCI_CPU_OFF_BIT                    (1 << 4)
#define FPSCI_CPU_ON_AARCH32_BIT             (1 << 5)
#define FPSCI_CPU_ON_AARCH64_BIT             (1 << 6)
#define FPSCI_AFFINITY_INFO_AARCH32_BIT      (1 << 7)
#define FPSCI_AFFINITY_INFO_AARCH64_BIT      (1 << 8)
#define FPSCI_SYSTEM_OFF_BIT                 (1 << 9)
#define FPSCI_SYSTEM_RESET_BIT               (1 << 10)


static int fpsci_ringt_bit_flg = 0;

/* 定义函数指针 */
typedef void (*FPsciInvokeFun)(unsigned long arg0, unsigned long arg1,
                               unsigned long arg2, unsigned long arg3,
                               unsigned long arg4, unsigned long arg5,
                               unsigned long arg6, unsigned long arg7,
                               struct FSmcccRes *res);

/* 为函数指针初始化为默认的函数 */
FPsciInvokeFun f_psci_invoke = FSmcccSmcCall;


/**
 * @name: FPsciVersion
 * @msg: Get the version of the PSCI implementation.
 * @return {int}: The version information of the PSCI implementation.
 * @note: This function returns the version information obtained from the PSCI VERSION function.
 */
int FPsciVersion(void)
{
    struct FSmcccRes res;
    FASSERT((*f_psci_invoke));
    (*f_psci_invoke)(FPSCI_VERSION, 0, 0, 0, 0, 0, 0, 0, &res);
    return res.a0;
}

/**
 * @name: FPsciFeatures
 * @msg: Check whether a PSCI function is supported.
 * @param {u32} psci_fid: The function ID of the PSCI function to be checked.
 * @return {int}: 1 if the function is supported; 0 otherwise.
 * @note: This function returns whether the PSCI function represented by psci_fid is supported or not.
 */
int FPsciFeatures(u32 psci_fid)
{
    struct FSmcccRes res;
    FASSERT((*f_psci_invoke));
    (*f_psci_invoke)(FPSCI_FEATURES, psci_fid, 0, 0, 0, 0, 0, 0, &res);
    return res.a0 == FPSCI_SUCCESS ? 1 : 0;
}

/**
 * @name: FPsciCpuSuspend
 * @msg: Suspend execution on a particular CPU.
 * @param {u32} power_state: The power state to be entered.
 * @param {unsigned long} entry_point_address: The address to be executed upon waking up.
 * @param {unsigned long} context_id: The context-specific identifier.
 * @return {int}: The status code of the operation, as defined by the PSCI specification.
 * @note: This function suspends the execution on a particular CPU and returns a status code indicating whether the operation was successful or not.
 */
int FPsciCpuSuspend(u32 power_state, unsigned long entry_point_address, unsigned long context_id)
{
    struct FSmcccRes res;
    FASSERT((fpsci_ringt_bit_flg & FPSCI_CPU_SUSPEND_AARCH32_BIT) != 0);
    FASSERT((*f_psci_invoke));
    (*f_psci_invoke)(FPSCI_CPU_SUSPEND_AARCH32, power_state, entry_point_address, context_id, 0, 0, 0, 0, &res);
    return res.a0;
}


/**
 * @name: FPsciCpuOn
 * @msg: Power on a particular CPU.
 * @param {unsigned long} target_cpu: The target CPU to be powered on.
 * @param {unsigned long} entry_point_address: The address to be executed upon waking up.
 * @param {unsigned long} context_id: The context-specific identifier.
 * @return {int}: The status code of the operation, as defined by the PSCI specification.
 * @note: This function powers on a particular CPU and returns a status code indicating whether the operation was successful or not.
 */
int FPsciCpuOn(unsigned long target_cpu, unsigned long entry_point_address, unsigned long context_id)
{
    struct FSmcccRes res;
    unsigned long cpu_on_id  ;

#if defined(FAARCH64_USE)
    cpu_on_id = FPSCI_CPU_ON_AARCH64 ;
#else
    cpu_on_id = FPSCI_CPU_ON_AARCH32;
#endif

    FASSERT((fpsci_ringt_bit_flg & (FPSCI_CPU_ON_AARCH32_BIT | FPSCI_CPU_ON_AARCH64_BIT)) != 0);
    FASSERT((*f_psci_invoke));
    (*f_psci_invoke)(cpu_on_id, target_cpu, entry_point_address, context_id, 0, 0, 0, 0, &res);
    return res.a0;
}

/**
 * @name: FPsciCpuOff
 * @msg: This is a wrapper for the PSCI CPU Off interface, intended to turn off the current CPU.
 * @return: Returns the 'a0' field of the 'FSmcccRes' structure, indicating the result of the call. A return value of 0 (PSCI_SUCCESS) indicates success, any other value indicates an error occurred.
 * @note: A core that is powered down by CPU_OFF can only be powered up again in response to a CPU_ON.
 */
int FPsciCpuOff(void)
{
    struct FSmcccRes res;
    FASSERT((fpsci_ringt_bit_flg & FPSCI_CPU_OFF_BIT) != 0);
    FASSERT((*f_psci_invoke));
    (*f_psci_invoke)(FPSCI_CPU_OFF, 0, 0, 0, 0, 0, 0, 0, &res);
    return res.a0;
}



/**
 * @name: FPsciAffinityInfo
 * @msg: Get the power state of a particular affinity level.
 * @param {unsigned long} target_affinity: The target affinity level.
 * @param {u32} lowest_affinity_level: The lowest affinity level.
 * @return {int}: The power state of the specified affinity level, as defined by the PSCI specification.
 * @note: This function returns the power state of a particular affinity level.
 */
int FPsciAffinityInfo(unsigned long target_affinity, u32 lowest_affinity_level)
{
    struct FSmcccRes res;
    FASSERT((fpsci_ringt_bit_flg & (FPSCI_AFFINITY_INFO_AARCH32_BIT | FPSCI_AFFINITY_INFO_AARCH64_BIT)) != 0);
    FASSERT((*f_psci_invoke));

    (*f_psci_invoke)(FPSCI_FAFFINITY_INFO_AARCH32, target_affinity, lowest_affinity_level, 0, 0, 0, 0, 0, &res);
    return res.a0;
}

/**
 * @name: FPsciSystemReset
 * @msg: Reset the system.
 * @param {u32} reset_type: The type of the system reset (cold/warm).
 * @note: This function resets the system. The reset type is specified by the parameter reset_type.
 */
void FPsciSystemReset(u32 reset_type)
{
    struct FSmcccRes res;
    FASSERT((fpsci_ringt_bit_flg & FPSCI_SYSTEM_RESET_BIT) != 0);
    FASSERT((*f_psci_invoke));
    (*f_psci_invoke)(FPSCI_SYSTEM_RESET, reset_type, 0, 0, 0, 0, 0, 0, &res);
}


/**
 * @name: FPsciCheckFeatures
 * @msg: This function checks for the availability of various PSCI features and sets the corresponding bits in the 'fpsci_ringt_bit_flg' global flag accordingly.
 * @return: This function does not return a value.
 */
static void FPsciCheckFeatures(void)
{
    LOG_I("Checking PSCI features...\r\n");
    fpsci_ringt_bit_flg = 0 ;
    if (FPsciFeatures(FPSCI_CPU_SUSPEND_AARCH32))
    {
        fpsci_ringt_bit_flg |= FPSCI_CPU_SUSPEND_AARCH32_BIT;
        LOG_I("CPU_SUSPEND_AARCH32 supported.\r\n");
    }
    else
    {
        LOG_E("CPU_SUSPEND_AARCH32 not supported.\r\n");
    }

    if (FPsciFeatures(FPSCI_CPU_OFF))
    {
        fpsci_ringt_bit_flg |= FPSCI_CPU_OFF_BIT;
        LOG_I("CPU_OFF supported.\r\n");
    }
    else
    {
        LOG_E("CPU_OFF not supported.\r\n");
    }

#if defined(FAARCH64_USE)
    if (FPsciFeatures(FPSCI_CPU_ON_AARCH64))
    {
        fpsci_ringt_bit_flg |= FPSCI_CPU_ON_AARCH64_BIT;
        LOG_I("CPU_ON_AARCH64 supported.\r\n");
    }
    else
    {
        LOG_E("CPU_ON_AARCH64 not supported.\r\n");
    }
#else
    if (FPsciFeatures(FPSCI_CPU_ON_AARCH32))
    {
        fpsci_ringt_bit_flg |= FPSCI_CPU_ON_AARCH32_BIT;
        LOG_I("CPU_ON_AARCH32 supported.\r\n");
    }
    else
    {
        LOG_E("CPU_ON_AARCH32 not supported.\r\n");
    }
#endif


#if defined(FAARCH64_USE)
    if (FPsciFeatures(FPSCI_FAFFINITY_INFO_AARCH64))
    {
        fpsci_ringt_bit_flg |= FPSCI_AFFINITY_INFO_AARCH64_BIT;
        LOG_I("AFFINITY_INFO_AARCH64 supported.\r\n");
    }
    else
    {
        LOG_E("AFFINITY_INFO_AARCH64 not supported.\r\n");
    }

#else
    if (FPsciFeatures(FPSCI_FAFFINITY_INFO_AARCH32))
    {
        fpsci_ringt_bit_flg |= FPSCI_AFFINITY_INFO_AARCH32_BIT;
        LOG_I("FPSCI_AFFINITY_INFO_AARCH32 supported.\r\n");
    }
    else
    {
        LOG_E("AFFINITY_INFO_AARCH32 not supported.\r\n");
    }
#endif

    if (FPsciFeatures(FPSCI_SYSTEM_OFF))
    {
        fpsci_ringt_bit_flg |= FPSCI_SYSTEM_OFF_BIT;
        LOG_I("SYSTEM_OFF supported.\r\n");
    }
    else
    {
        LOG_E("SYSTEM_OFF not supported.\r\n");
    }

    if (FPsciFeatures(FPSCI_SYSTEM_RESET))
    {
        fpsci_ringt_bit_flg |= FPSCI_SYSTEM_RESET_BIT;
        LOG_I("SYSTEM_RESET supported.\r\n");
    }
    else
    {
        LOG_E("SYSTEM_RESET not supported.\r\n");
    }
}


/**
 * @name: FPsci_CpuOn
 * @msg:  Power up a core
 * @in param cpu_id_mask: cpu id mask
 * @in param bootaddr:  a 32-bit entry point physical address (or IPA).
 * @return int
 */
int FPsciCpuMaskOn(s32 cpu_id_mask, uintptr bootaddr)
{
    FError ret ;
    u64 cluster = 0;
    ret = GetCpuAffinityByMask(cpu_id_mask, &cluster);
    if (ret != ERR_SUCCESS)
    {
        return FPSCI_INVALID_PARAMS;
    }
    return FPsciCpuOn(cluster, (unsigned long)bootaddr, 0) ;
}


static void FSmccInit(int method)
{
    if (method == 1)
    {
        f_psci_invoke = FSmcccHvcCall;
    }
    else
    {
        f_psci_invoke = FSmcccSmcCall;
    }
}

int FPsciInit(void)
{
    int psci_version = 0;
    FSmccInit(0);
    psci_version = FPsciVersion() ;
    LOG_I("major is 0x%x,minor is 0x%x \r\n", FPSCI_MAJOR_VERSION(psci_version), FPSCI_MINOR_VERSION(psci_version)) ;
    FPsciCheckFeatures();
    return 0;
}



