/*
 * File      : core_ck802.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-01-01     Urey      first version
 */

#ifndef __CORE_CK802_H_GENERIC
#define __CORE_CK802_H_GENERIC

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *                 CSI definitions
 ******************************************************************************/
/**
  \ingroup Ck802
  @{
 */

/*  CSI CK802 definitions */
#define __CK802_CSI_VERSION_MAIN  (0x04U)                                      /*!< [31:16] CSI HAL main version */
#define __CK802_CSI_VERSION_SUB   (0x1EU)                                      /*!< [15:0]  CSI HAL sub version */
#define __CK802_CSI_VERSION       ((__CK802_CSI_VERSION_MAIN << 16U) | \
                                   __CK802_CSI_VERSION_SUB           )        /*!< CSI HAL version number */

#define __CK80X                (0x02U)                                         /*!< CK80X Core */

/** __FPU_USED indicates whether an FPU is used or not.
    This core does not support an FPU at all
*/
#define __FPU_USED       0U

#if defined ( __GNUC__ )
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
#error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
#endif
#endif

#include "csi_gcc.h"

#ifdef __cplusplus
}
#endif

#endif /* __CORE_CK802_H_GENERIC */

#ifndef __CSI_GENERIC

#ifndef __CORE_CK802_H_DEPENDANT
#define __CORE_CK802_H_DEPENDANT

#ifdef __cplusplus
extern "C" {
#endif

/* check device defines and use defaults */
//#if defined __CHECK_DEVICE_DEFINES
#ifndef __CK802_REV
#define __CK802_REV               0x0000U
//#warning "__CK802_REV not defined in device header file; using default!"
#endif

#ifndef __NVIC_PRIO_BITS
#define __NVIC_PRIO_BITS          2U
//#warning "__NVIC_PRIO_BITS not defined in device header file; using default!"
#endif

#ifndef __Vendor_SysTickConfig
#define __Vendor_SysTickConfig    0U
//#warning "__Vendor_SysTickConfig not defined in device header file; using default!"
#endif

#ifndef __GSR_GCR_PRESENT
#define __GSR_GCR_PRESENT         0U
//#warning "__GSR_GCR_PRESENT not defined in device header file; using default!"
#endif

#ifndef __MGU_PRESENT
#define __MGU_PRESENT             0U
//#warning "__MGU_PRESENT not defined in device header file; using default!"
#endif
//#endif

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CSI_glob_defs CSI Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
#ifdef __cplusplus
#define   __I     volatile             /*!< Defines 'read only' permissions */
#else
#define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/*@} end of group CK802 */

/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
  - Core NVIC Register
  - Core SCB Register
  - Core SysTick Register
 ******************************************************************************/
/**
  \defgroup CSI_core_register Defines and Type Definitions
  \brief Type definitions and defines for CK80X processor based devices.
*/

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_CORE  Status and Control Registers
  \brief      Core Register type definitions.
  @{
 */

/**
  \brief  访问处理器状态寄存器(PSR)的联合体定义.
 */
typedef union
{
    struct
    {
        uint32_t C: 1;                       /*!< bit:      0  条件码／进位位 */
        uint32_t _reserved0: 5;              /*!< bit:  2.. 5  保留 */
        uint32_t IE: 1;                      /*!< bit:      6  中断有效控制位 */
        uint32_t IC: 1;                      /*!< bit:      7  中断控制位 */
        uint32_t EE: 1;                      /*!< bit:      8  异常有效控制位 */
        uint32_t MM: 1;                      /*!< bit:      9  不对齐异常掩盖位 */
        uint32_t _reserved1: 6;              /*!< bit: 10..15  保留 */
        uint32_t VEC: 8;                     /*!< bit: 16..23  异常事件向量值 */
        uint32_t _reserved2: 7;              /*!< bit: 24..30  保留 */
        uint32_t S: 1;                       /*!< bit:     31  超级用户模式设置位 */
    } b;                                   /*!< Structure    用来按位访问 */
    uint32_t w;                            /*!< Type         整个寄存器访问 */
} PSR_Type;

/* PSR Register Definitions */
#define PSR_S_Pos                          31U                                            /*!< PSR: S Position */
#define PSR_S_Msk                          (1UL << PSR_S_Pos)                             /*!< PSR: S Mask */

#define PSR_VEC_Pos                        16U                                            /*!< PSR: VEC Position */
#define PSR_VEC_Msk                        (0x7FUL << PSR_VEC_Pos)                        /*!< PSR: VEC Mask */

#define PSR_MM_Pos                         9U                                             /*!< PSR: MM Position */
#define PSR_MM_Msk                         (1UL << PSR_MM_Pos)                            /*!< PSR: MM Mask */

#define PSR_EE_Pos                         8U                                             /*!< PSR: EE Position */
#define PSR_EE_Msk                         (1UL << PSR_EE_Pos)                            /*!< PSR: EE Mask */

#define PSR_IC_Pos                         7U                                             /*!< PSR: IC Position */
#define PSR_IC_Msk                         (1UL << PSR_IC_Pos)                            /*!< PSR: IC Mask */

#define PSR_IE_Pos                         6U                                             /*!< PSR: IE Position */
#define PSR_IE_Msk                         (1UL << PSR_IE_Pos)                            /*!< PSR: IE Mask */

#define PSR_C_Pos                          0U                                             /*!< PSR: C Position */
#define PSR_C_Msk                          (1UL << PSR_C_Pos)                             /*!< PSR: C Mask */

/**
  \brief  访问高速缓存配置寄存器(CCR, CR<18, 0>)的联合体定义.
 */
typedef union
{
    struct
    {
        uint32_t MP: 1;                      /*!< bit:      0  内存保护设置位 */
        uint32_t _reserved0: 6;              /*!< bit:  1.. 6  保留 */
        uint32_t BE: 1;                      /*!< bit:      7  Endian模式 */
        uint32_t SCK: 3;                     /*!< bit:  8..10  系统和处理器的时钟比 */
        uint32_t _reserved1: 2;              /*!< bit: 11..12  保留 */
        uint32_t BE_V2: 1;                   /*!< bit:     13  V2版本大小端 */
        uint32_t _reserved2: 18;             /*!< bit: 14..31  保留 */
    } b;                                   /*!< Structure    用来按位访问 */
    uint32_t w;                            /*!< Type         整个寄存器访问 */
} CCR_Type;

/* CCR Register Definitions */
#define CCR_BE_V2_Pos                     13U                                            /*!< CCR: BE_V2 Position */
#define CCR_BE_V2_Msk                     (0x1UL << CCR_ISR_Pos)                         /*!< CCR: BE_V2 Mask */

#define CCR_SCK_Pos                       8U                                             /*!< CCR: SCK Position */
#define CCR_SCK_Msk                       (0x3UL << CCR_SCK_Pos)                         /*!< CCR: SCK Mask */

#define CCR_BE_Pos                        7U                                             /*!< CCR: BE Position */
#define CCR_BE_Msk                        (0x1UL << CCR_BE_Pos)                          /*!< CCR: BE Mask */

#define CCR_MP_Pos                        0U                                             /*!< CCR: MP Position */
#define CCR_MP_Msk                        (0x1UL << CCR_MP_Pos)                          /*!< CCR: MP Mask */

/**
  \brief  访问可高缓和访问权限配置寄存器(CAPR, CR<19,0>)的联合体定义..
 */
typedef union
{
    struct
    {
        uint32_t X0: 1;                      /*!< bit:      0  不可执行属性设置位 */
        uint32_t X1: 1;                      /*!< bit:      1  不可执行属性设置位 */
        uint32_t X2: 1;                      /*!< bit:      2  不可执行属性设置位 */
        uint32_t X3: 1;                      /*!< bit:      3  不可执行属性设置位 */
        uint32_t X4: 1;                      /*!< bit:      4  不可执行属性设置位 */
        uint32_t X5: 1;                      /*!< bit:      5  不可执行属性设置位 */
        uint32_t X6: 1;                      /*!< bit:      6  不可执行属性设置位 */
        uint32_t X7: 1;                      /*!< bit:      7  不可执行属性设置位 */
        uint32_t AP0: 2;                     /*!< bit:  8.. 9  访问权限设置位 */
        uint32_t AP1: 2;                     /*!< bit: 10..11  访问权限设置位 */
        uint32_t AP2: 2;                     /*!< bit: 12..13  访问权限设置位 */
        uint32_t AP3: 2;                     /*!< bit: 14..15  访问权限设置位 */
        uint32_t AP4: 2;                     /*!< bit: 16..17  访问权限设置位 */
        uint32_t AP5: 2;                     /*!< bit: 18..19  访问权限设置位 */
        uint32_t AP6: 2;                     /*!< bit: 20..21  访问权限设置位 */
        uint32_t AP7: 2;                     /*!< bit: 22..23  访问权限设置位 */
        uint32_t S0: 1;                      /*!< bit:     24  安全属性设置位 */
        uint32_t S1: 1;                      /*!< bit:     25  安全属性设置位 */
        uint32_t S2: 1;                      /*!< bit:     26  安全属性设置位 */
        uint32_t S3: 1;                      /*!< bit:     27  安全属性设置位 */
        uint32_t S4: 1;                      /*!< bit:     28  安全属性设置位 */
        uint32_t S5: 1;                      /*!< bit:     29  安全属性设置位 */
        uint32_t S6: 1;                      /*!< bit:     30  安全属性设置位 */
        uint32_t S7: 1;                      /*!< bit:     31  安全属性设置位 */
    } b;                                   /*!< Structure    用来按位访问 */
    uint32_t w;                            /*!< Type         整个寄存器访问 */
} CAPR_Type;

/* CAPR Register Definitions */
#define CAPR_S7_Pos                        31U                                            /*!< CAPR: S7 Position */
#define CAPR_S7_Msk                        (1UL << CAPR_S7_Pos)                           /*!< CAPR: S7 Mask */

#define CAPR_S6_Pos                        30U                                            /*!< CAPR: S6 Position */
#define CAPR_S6_Msk                        (1UL << CAPR_S6_Pos)                           /*!< CAPR: S6 Mask */

#define CAPR_S5_Pos                        29U                                            /*!< CAPR: S5 Position */
#define CAPR_S5_Msk                        (1UL << CAPR_S5_Pos)                           /*!< CAPR: S5 Mask */

#define CAPR_S4_Pos                        28U                                            /*!< CAPR: S4 Position */
#define CAPR_S4_Msk                        (1UL << CAPR_S4_Pos)                           /*!< CAPR: S4 Mask */

#define CAPR_S3_Pos                        27U                                            /*!< CAPR: S3 Position */
#define CAPR_S3_Msk                        (1UL << CAPR_S3_Pos)                           /*!< CAPR: S3 Mask */

#define CAPR_S2_Pos                        26U                                            /*!< CAPR: S2 Position */
#define CAPR_S2_Msk                        (1UL << CAPR_S2_Pos)                           /*!< CAPR: S2 Mask */

#define CAPR_S1_Pos                        25U                                            /*!< CAPR: S1 Position */
#define CAPR_S1_Msk                        (1UL << CAPR_S1_Pos)                           /*!< CAPR: S1 Mask */

#define CAPR_S0_Pos                        24U                                            /*!< CAPR: S0 Position */
#define CAPR_S0_Msk                        (1UL << CAPR_S0_Pos)                           /*!< CAPR: S0 Mask */

#define CAPR_AP7_Pos                       22U                                            /*!< CAPR: AP7 Position */
#define CAPR_AP7_Msk                       (0x3UL << CAPR_AP7_Pos)                        /*!< CAPR: AP7 Mask */

#define CAPR_AP6_Pos                       20U                                            /*!< CAPR: AP6 Position */
#define CAPR_AP6_Msk                       (0x3UL << CAPR_AP6_Pos)                        /*!< CAPR: AP6 Mask */

#define CAPR_AP5_Pos                       18U                                            /*!< CAPR: AP5 Position */
#define CAPR_AP5_Msk                       (0x3UL << CAPR_AP5_Pos)                        /*!< CAPR: AP5 Mask */

#define CAPR_AP4_Pos                       16U                                            /*!< CAPR: AP4 Position */
#define CAPR_AP4_Msk                       (0x3UL << CAPR_AP4_Pos)                        /*!< CAPR: AP4 Mask */

#define CAPR_AP3_Pos                       14U                                            /*!< CAPR: AP3 Position */
#define CAPR_AP3_Msk                       (0x3UL << CAPR_AP3_Pos)                        /*!< CAPR: AP3 Mask */

#define CAPR_AP2_Pos                       12U                                            /*!< CAPR: AP2 Position */
#define CAPR_AP2_Msk                       (0x3UL << CAPR_AP2_Pos)                        /*!< CAPR: AP2 Mask */

#define CAPR_AP1_Pos                       10U                                            /*!< CAPR: AP1 Position */
#define CAPR_AP1_Msk                       (0x3UL << CAPR_AP1_Pos)                        /*!< CAPR: AP1 Mask */

#define CAPR_AP0_Pos                       8U                                             /*!< CAPR: AP0 Position */
#define CAPR_AP0_Msk                       (0x3UL << CAPR_AP0_Pos)                        /*!< CAPR: AP0 Mask */

#define CAPR_X7_Pos                        7U                                             /*!< CAPR: X7 Position */
#define CAPR_X7_Msk                        (0x1UL << CAPR_X7_Pos)                         /*!< CAPR: X7 Mask */

#define CAPR_X6_Pos                        6U                                             /*!< CAPR: X6 Position */
#define CAPR_X6_Msk                        (0x1UL << CAPR_X6_Pos)                         /*!< CAPR: X6 Mask */

#define CAPR_X5_Pos                        5U                                             /*!< CAPR: X5 Position */
#define CAPR_X5_Msk                        (0x1UL << CAPR_X5_Pos)                         /*!< CAPR: X5 Mask */

#define CAPR_X4_Pos                        4U                                             /*!< CAPR: X4 Position */
#define CAPR_X4_Msk                        (0x1UL << CAPR_X4_Pos)                         /*!< CAPR: X4 Mask */

#define CAPR_X3_Pos                        3U                                             /*!< CAPR: X3 Position */
#define CAPR_X3_Msk                        (0x1UL << CAPR_X3_Pos)                         /*!< CAPR: X3 Mask */

#define CAPR_X2_Pos                        2U                                             /*!< CAPR: X2 Position */
#define CAPR_X2_Msk                        (0x1UL << CAPR_X2_Pos)                         /*!< CAPR: X2 Mask */

#define CAPR_X1_Pos                        1U                                             /*!< CAPR: X1 Position */
#define CAPR_X1_Msk                        (0x1UL << CAPR_X1_Pos)                         /*!< CAPR: X1 Mask */

#define CAPR_X0_Pos                        0U                                             /*!< CAPR: X0 Position */
#define CAPR_X0_Msk                        (0x1UL << CAPR_X0_Pos)                         /*!< CAPR: X0 Mask */

/**
  \brief  访问保护区控制寄存器(PACR, CR<20,0>)的联合体定义.
 */
typedef union
{
    struct
    {
        uint32_t E: 1;                       /*!< bit:      0  保护区有效设置 */
        uint32_t Size: 5;                    /*!< bit:  1.. 5  保护区大小 */
        uint32_t _reserved0: 4;              /*!< bit:  6.. 9  保留 */
        uint32_t base_addr: 22;              /*!< bit: 10..31  保护区地址的高位 */
    } b;                                   /*!< Structure    用来按位访问 */
    uint32_t w;                            /*!< Type         整个寄存器访问 */
} PACR_Type;

/* PACR Register Definitions */
#define PACR_BASE_ADDR_Pos                 10U                                            /*!< PACR: base_addr Position */
#define PACK_BASE_ADDR_Msk                 (0x3FFFFFUL << PACR_BASE_ADDR_Pos)             /*!< PACR: base_addr Mask */

#define PACR_SIZE_Pos                      1U                                             /*!< PACR: Size Position */
#define PACK_SIZE_Msk                      (0x1FUL << PACR_SIZE_Pos)                      /*!< PACR: Size Mask */

#define PACR_E_Pos                         0U                                             /*!< PACR: E Position */
#define PACK_E_Msk                         (0x1UL << PACR_E_Pos)                          /*!< PACR: E Mask */

/**
  \brief  访问保护区选择寄存器(PRSR,CR<21,0>)的联合体定义.
 */
typedef union
{
    struct
    {
        uint32_t RID: 3;                     /*!< bit:  0.. 2  保护区索引值 */
        uint32_t _reserved0: 30;             /*!< bit:  3..31  保留 */
    } b;                                   /*!< Structure    用来按位访问 */
    uint32_t w;                            /*!< Type         整个寄存器访问 */
} PRSR_Type;

/* PRSR Register Definitions */
#define PRSR_RID_Pos                       0U                                            /*!< PRSR: RID Position */
#define PRSR_RID_Msk                       (0x7UL << PRSR_RID_Pos)                       /*!< PRSR: RID Mask */

/*@} end of group CSI_CORE */


/**
  \ingroup    CSI_core_register
  \defgroup   CSI_NVIC Vectored Interrupt Controller (NVIC)
  \brief      Type definitions for the NVIC Registers
  @{
 */

/**
  \brief 访问矢量中断控制器的结构体.
 */
typedef struct
{
    __IOM uint32_t ISER[1U];               /*!< Offset: 0x000 (R/W)  中断使能设置寄存器 */
    uint32_t RESERVED0[15U];
    __IOM uint32_t IWER[1U];               /*!< Offset: 0x040 (R/W)  中断低功耗唤醒设置寄存器 */
    uint32_t RESERVED1[15U];
    __IOM uint32_t ICER[1U];               /*!< Offset: 0x080 (R/W)  中断使能清除寄存器 */
    uint32_t RESERVED2[15U];
    __IOM uint32_t IWDR[1U];               /*!< Offset: 0x0c0 (R/W)  中断低功耗唤醒清除寄存器 */
    uint32_t RESERVED3[15U];
    __IOM uint32_t ISPR[1U];               /*!< Offset: 0x100 (R/W)  中断等待设置寄存器 */
    uint32_t RESERVED4[15U];
    __IOM uint32_t ISSR[1U];               /*!< Offset: 0x140 (R/W)  安全中断使能设置寄存器 */
    uint32_t RESERVED5[15U];
    __IOM uint32_t ICPR[1U];               /*!< Offset: 0x180 (R/W)  中断等待清除寄存器 */
    uint32_t RESERVED6[31U];
    __IOM uint32_t IABR[1U];               /*!< Offset: 0x200 (R/W)  中断响应状态寄存器 */
    uint32_t RESERVED7[63U];
    __IOM uint32_t IPR[8U];                /*!< Offset: 0x300 (R/W)  中断优先级设置寄存器 */
    uint32_t RESERVED8[504U];
    __IM  uint32_t ISR;                    /*!< Offset: 0xB00 (R/ )  中断状态寄存器 */
    __IOM uint32_t IPTR;                   /*!< Offset: 0xB04 (R/W)  中断优先级阈值寄存器 */
} NVIC_Type;

/*@} end of group CSI_NVIC */

/**
  \ingroup  CSI_core_register
  \defgroup CSI_SysTick     System Tick Timer (CORET)
  \brief    Type definitions for the System Timer Registers.
  @{
 */

/**
  \brief  访问系统计时器的数据结构.
 */
typedef struct
{
    __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  控制状态寄存器 */
    __IOM uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  回填值寄存器 */
    __IOM uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  当前值寄存器 */
    __IM  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  校准寄存器 */
} CORET_Type;

/* CORET Control / Status Register Definitions */
#define CORET_CTRL_COUNTFLAG_Pos           16U                                            /*!< CORET CTRL: COUNTFLAG Position */
#define CORET_CTRL_COUNTFLAG_Msk           (1UL << CORET_CTRL_COUNTFLAG_Pos)              /*!< CORET CTRL: COUNTFLAG Mask */

#define CORET_CTRL_CLKSOURCE_Pos            2U                                            /*!< CORET CTRL: CLKSOURCE Position */
#define CORET_CTRL_CLKSOURCE_Msk           (1UL << CORET_CTRL_CLKSOURCE_Pos)              /*!< CORET CTRL: CLKSOURCE Mask */

#define CORET_CTRL_TICKINT_Pos              1U                                            /*!< CORET CTRL: TICKINT Position */
#define CORET_CTRL_TICKINT_Msk             (1UL << CORET_CTRL_TICKINT_Pos)                /*!< CORET CTRL: TICKINT Mask */

#define CORET_CTRL_ENABLE_Pos               0U                                            /*!< CORET CTRL: ENABLE Position */
#define CORET_CTRL_ENABLE_Msk              (1UL /*<< CORET_CTRL_ENABLE_Pos*/)             /*!< CORET CTRL: ENABLE Mask */

/* CORET Reload Register Definitions */
#define CORET_LOAD_RELOAD_Pos               0U                                            /*!< CORET LOAD: RELOAD Position */
#define CORET_LOAD_RELOAD_Msk              (0xFFFFFFUL /*<< CORET_LOAD_RELOAD_Pos*/)      /*!< CORET LOAD: RELOAD Mask */

/* CORET Current Register Definitions */
#define CORET_VAL_CURRENT_Pos               0U                                            /*!< CORET VAL: CURRENT Position */
#define CORET_VAL_CURRENT_Msk              (0xFFFFFFUL /*<< CORET_VAL_CURRENT_Pos*/)      /*!< CORET VAL: CURRENT Mask */

/* CORET Calibration Register Definitions */
#define CORET_CALIB_NOREF_Pos               31U                                           /*!< CORET CALIB: NOREF Position */
#define CORET_CALIB_NOREF_Msk              (1UL << CORET_CALIB_NOREF_Pos)                 /*!< CORET CALIB: NOREF Mask */

#define CORET_CALIB_SKEW_Pos                30U                                           /*!< CORET CALIB: SKEW Position */
#define CORET_CALIB_SKEW_Msk               (1UL << CORET_CALIB_SKEW_Pos)                  /*!< CORET CALIB: SKEW Mask */

#define CORET_CALIB_TENMS_Pos               0U                                            /*!< CORET CALIB: TENMS Position */
#define CORET_CALIB_TENMS_Msk              (0xFFFFFFUL /*<< CORET_CALIB_TENMS_Pos*/)      /*!< CORET CALIB: TENMS Mask */

/*@} end of group CSI_SysTick */

/**
  \ingroup  CSI_core_register
  \defgroup CSI_DCC
  \brief    Type definitions for the DCC.
  @{
 */

/**
  \brief  访问DCC的数据结构.
 */
typedef struct
{
    uint32_t RESERVED0[13U];
    __IOM uint32_t HCR;                    /*!< Offset: 0x034 (R/W) */
    __IM uint32_t EHSR;                    /*!< Offset: 0x03C (R/ ) */
    uint32_t RESERVED1[6U];
    union
    {
        __IM uint32_t DERJW;                 /*!< Offset: 0x058 (R/ )  数据交换寄存器 CPU读*/
        __OM uint32_t DERJR;                 /*!< Offset: 0x058 ( /W)  数据交换寄存器 CPU写*/
    };

} DCC_Type;

#define DCC_HCR_JW_Pos                   18U                                            /*!< DCC HCR: jw_int_en Position */
#define DCC_HCR_JW_Msk                   (1UL << DCC_HCR_JW_Pos)                        /*!< DCC HCR: jw_int_en Mask */

#define DCC_HCR_JR_Pos                   19U                                            /*!< DCC HCR: jr_int_en Position */
#define DCC_HCR_JR_Msk                   (1UL << DCC_HCR_JR_Pos)                        /*!< DCC HCR: jr_int_en Mask */

#define DCC_EHSR_JW_Pos                  1U                                             /*!< DCC EHSR: jw_vld Position */
#define DCC_EHSR_JW_Msk                  (1UL << DCC_EHSR_JW_Pos)                       /*!< DCC EHSR: jw_vld Mask */

#define DCC_EHSR_JR_Pos                  2U                                             /*!< DCC EHSR: jr_vld Position */
#define DCC_EHSR_JR_Msk                  (1UL << DCC_EHSR_JR_Pos)                       /*!< DCC EHSR: jr_vld Mask */

/*@} end of group CSI_DCC */


/**
  \ingroup    CSI_core_register
  \defgroup   CSI_core_bitfield     Core register bit field macros
  \brief      Macros for use with bit field definitions (xxx_Pos, xxx_Msk).
  @{
 */

/**
  \brief   Mask and shift a bit field value for use in a register bit range.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of the bit field.
  \return           Masked and shifted value.
*/
#define _VAL2FLD(field, value)    ((value << field ## _Pos) & field ## _Msk)

/**
  \brief     Mask and shift a register value to extract a bit filed value.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of register.
  \return           Masked and shifted bit field value.
*/
#define _FLD2VAL(field, value)    ((value & field ## _Msk) >> field ## _Pos)

/*@} end of group CSI_core_bitfield */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */

/* Memory mapping of CK802 Hardware */
#define TCIP_BASE           (0xE000E000UL)                            /*!< Titly Coupled IP Base Address */
#define CORET_BASE          (TCIP_BASE +  0x0010UL)                   /*!< CORET Base Address */
#define NVIC_BASE           (TCIP_BASE +  0x0100UL)                   /*!< NVIC Base Address */
#define DCC_BASE            (0xE0011000UL)                            /*!< DCC Base Address */

#define CORET               ((CORET_Type   *)     CORET_BASE  )       /*!< SysTick configuration struct */
#define NVIC                ((NVIC_Type    *)     NVIC_BASE   )       /*!< NVIC configuration struct */
#define DCC                 ((DCC_Type     *)     DCC_BASE    )       /*!< DCC configuration struct */

/*@} */

#ifdef __cplusplus
}
#endif

#endif /* __CORE_CK802_H_DEPENDANT */

#endif /* __CSI_GENERIC */
