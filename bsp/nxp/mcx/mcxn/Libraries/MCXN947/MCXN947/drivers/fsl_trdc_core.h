/*
 * Copyright 2022-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_TRDC_CORE_H_
#define FSL_TRDC_CORE_H_

#include "fsl_trdc_soc.h"

/*!
 * @addtogroup trdc_core
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!@brief TRDC general configuration register definition. */
typedef struct _TRDC_General_Type
{
    __IO uint32_t TRDC_CR; /**< TRDC Register, offset: 0x0 */
    uint8_t RESERVED_0[236];
    __I uint32_t TRDC_HWCFG0; /**< TRDC Hardware Configuration Register 0, offset: 0xF0 */
    __I uint32_t TRDC_HWCFG1; /**< TRDC Hardware Configuration Register 1, offset: 0xF4 */
    __I uint32_t TRDC_HWCFG2; /**< TRDC Hardware Configuration Register 2, offset: 0xF8 */
    __I uint32_t TRDC_HWCFG3; /**< TRDC Hardware Configuration Register 3, offset: 0xFC */
    __I uint8_t DACFG[8];     /**< Domain Assignment Configuration Register, array offset: 0x100, array step: 0x1 */
    uint8_t RESERVED_1[184];
    __IO uint32_t TRDC_IDAU_CR; /**< TRDC IDAU Control Register, offset: 0x1C0 */
} TRDC_General_Type;

/*!@brief TRDC flash logical control register definition. */
typedef struct _TRDC_FLW_Type
{
    __IO uint32_t TRDC_FLW_CTL;   /**< TRDC FLW Control, offset: 0x1E0 */
    __I uint32_t TRDC_FLW_PBASE;  /**< TRDC FLW Physical Base, offset: 0x1E4 */
    __IO uint32_t TRDC_FLW_ABASE; /**< TRDC FLW Array Base, offset: 0x1E8 */
    __IO uint32_t TRDC_FLW_BCNT;  /**< TRDC FLW Block Count, offset: 0x1EC */
} TRDC_FLW_Type;

/*!@brief TRDC domain error register definition. */
typedef struct _TRDC_DomainError_Type
{
    __IO uint32_t TRDC_FDID;       /**< TRDC Fault Domain ID, offset: 0x1FC */
    __I uint32_t TRDC_DERRLOC[16]; /**< TRDC Domain Error Location Register, array offset: 0x200, array step: 0x4 */
    uint8_t RESERVED_4[448];
    struct
    {                    /* offset: 0x400, array step: 0x10 */
        __I uint32_t W0; /**< MBC Domain Error Word0 Register, array offset: 0x400, array step: 0x10 */
        __I uint32_t W1; /**< MBC Domain Error Word1 Register, array offset: 0x404, array step: 0x10 */
        uint8_t RESERVED_0[4];
        __O uint32_t W3; /**< MBC Domain Error Word3 Register, array offset: 0x40C, array step: 0x10 */
    } MBC_DERR[8];
    struct
    {                    /* offset: 0x480, array step: 0x10 */
        __I uint32_t W0; /**< MRC Domain Error Word0 Register, array offset: 0x480, array step: 0x10 */
        __I uint32_t W1; /**< MRC Domain Error Word1 Register, array offset: 0x484, array step: 0x10 */
        uint8_t RESERVED_0[4];
        __O uint32_t W3; /**< MRC Domain Error Word3 Register, array offset: 0x48C, array step: 0x10 */
    } MRC_DERR[8];
} TRDC_DomainError_Type;

/*!@brief TRDC master domain assignment register definition. */
typedef struct _TRDC_DomainAssignment_Type
{
    __IO uint32_t PID[8]; /**< Process Identifier, array offset: 0x700, array step: 0x4 */
    uint8_t RESERVED_7[224];
    union
    {
        struct
        {                                 /* offset: 0x800, array step: 0x20 */
            __IO uint32_t MDA_W_DFMT0[8]; /**< DAC Master Domain Assignment Register, array offset: 0x800, array step:
                                             index*0x20, index2*0x4 */
        } MDA_DFMT0[8];
        struct
        {                                 /* offset: 0x800, array step: 0x20 */
            __IO uint32_t MDA_W_DFMT1[1]; /**< DAC Master Domain Assignment Register, array offset: 0x800, array step:
                                             index*0x20, index2*0x4 */
            uint8_t RESERVED_0[28];
        } MDA_DFMT1[8];
    };
} TRDC_DomainAssignment_Type;

/*!@brief TRDC MBC control register definition. */
typedef struct _TRDC_MBC_Type
{
    __I uint32_t MBC_MEM_GLBCFG[4];  /**< MBC Global Configuration Register, array offset: 0x10000, array step:
                                        index*0x2000, index2*0x4 */
    __IO uint32_t MBC_NSE_BLK_INDEX; /**< MBC NonSecure Enable Block Index, array offset: 0x10010, array step: 0x2000 */
    __O uint32_t MBC_NSE_BLK_SET;    /**< MBC NonSecure Enable Block Set, array offset: 0x10014, array step: 0x2000 */
    __O uint32_t MBC_NSE_BLK_CLR;    /**< MBC NonSecure Enable Block Clear, array offset: 0x10018, array step: 0x2000 */
    __O uint32_t
        MBC_NSE_BLK_CLR_ALL; /**< MBC NonSecure Enable Block Clear All, array offset: 0x1001C, array step: 0x2000 */
    __IO uint32_t MBC_MEMN_GLBAC[8]; /**< MBC Global Access Control, array offset: 0x10020, array step: index*0x2000,
                                        index2*0x4 */
    __IO uint32_t MBC_DOM0_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x10040, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM0_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10140, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM0_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10180, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM0_MEM1_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x101A0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM0_MEM2_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x101A8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM0_MEM2_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x101C8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM0_MEM3_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x101D0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM0_MEM3_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x101F0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_0[72];
    __IO uint32_t MBC_DOM1_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x10240, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM1_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10340, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM1_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10380, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM1_MEM1_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x103A0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM1_MEM2_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x103A8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM1_MEM2_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x103C8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM1_MEM3_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x103D0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM1_MEM3_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x103F0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_1[72];
    __IO uint32_t MBC_DOM2_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x10440, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM2_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10540, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM2_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10580, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM2_MEM1_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x105A0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM2_MEM2_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x105A8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM2_MEM2_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x105C8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM2_MEM3_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x105D0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM2_MEM3_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x105F0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_2[72];
    __IO uint32_t MBC_DOM3_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x10640, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM3_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10740, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM3_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10780, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM3_MEM1_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x107A0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM3_MEM2_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x107A8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM3_MEM2_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x107C8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM3_MEM3_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x107D0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM3_MEM3_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x107F0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_3[72];
    __IO uint32_t MBC_DOM4_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x10840, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM4_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10940, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM4_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10980, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM4_MEM1_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x109A0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM4_MEM2_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x109A8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM4_MEM2_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x109C8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM4_MEM3_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x109D0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM4_MEM3_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x109F0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_4[72];
    __IO uint32_t MBC_DOM5_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x10A40, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM5_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10B40, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM5_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10B80, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM5_MEM1_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10BA0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM5_MEM2_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10BA8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM5_MEM2_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10BC8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM5_MEM3_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10BD0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM5_MEM3_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10BF0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_5[72];
    __IO uint32_t MBC_DOM6_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x10C40, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM6_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10D40, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM6_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10D80, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM6_MEM1_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10DA0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM6_MEM2_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10DA8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM6_MEM2_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10DC8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM6_MEM3_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10DD0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM6_MEM3_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10DF0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_7[72];
    __IO uint32_t MBC_DOM7_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x10E40, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM7_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10F40, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM7_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10F80, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM7_MEM1_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10FA0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM7_MEM2_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10FA8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM7_MEM2_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10FC8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM7_MEM3_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x10FD0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM7_MEM3_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x10FF0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_8[72];
    __IO uint32_t MBC_DOM8_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x11040, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM8_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11140, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM8_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x11180, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM8_MEM1_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x111A0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM8_MEM2_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x111A8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM8_MEM2_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x111C8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM8_MEM3_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x111D0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM8_MEM3_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x111F0, array
                                                  step: index*0x2000, index2*0x4 */

    __IO uint32_t MBC_DOM9_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x11240, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM9_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11340, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM9_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x11380, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM9_MEM1_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x113A0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM9_MEM2_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x113A8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM9_MEM2_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x113C8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM9_MEM3_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x113D0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM9_MEM3_BLK_NSE_W[2];  /**< MBC Memory Block NonSecure Enable Word, array offset: 0x113F0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_9[72];
    __IO uint32_t MBC_DOM10_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x11440, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM10_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11540,
                                                   array step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM10_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x11580, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM10_MEM1_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x115A0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM10_MEM2_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x115A8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM10_MEM2_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x115C8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM10_MEM3_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x115D0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM10_MEM3_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x115F0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_10[72];
    __IO uint32_t MBC_DOM11_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x11640, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM11_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11740,
                                                   array step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM11_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x11780, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM11_MEM1_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x117A0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM11_MEM2_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x117A8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM11_MEM2_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x117C8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM11_MEM3_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x117D0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM11_MEM3_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x117F0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_11[72];
    __IO uint32_t MBC_DOM12_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x11840, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM12_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11940,
                                                   array step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM12_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x11980, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM12_MEM1_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x119A0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM12_MEM2_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x119A8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM12_MEM2_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x119C8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM12_MEM3_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x119D0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM12_MEM3_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x119F0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_12[72];
    __IO uint32_t MBC_DOM13_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x11A40, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM13_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11B40,
                                                   array step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM13_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x11B80, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM13_MEM1_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11BA0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM13_MEM2_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x11BA8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM13_MEM2_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11BC8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM13_MEM3_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x11BD0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM13_MEM3_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11BF0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_13[72];
    __IO uint32_t MBC_DOM14_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x11C40, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM14_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11D40,
                                                   array step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM14_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x11D80, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM14_MEM1_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11DA0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM14_MEM2_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x11DA8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM14_MEM2_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11DC8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM14_MEM3_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x11DD0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM14_MEM3_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11DF0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_14[72];
    __IO uint32_t MBC_DOM15_MEM0_BLK_CFG_W[64]; /**< MBC Memory Block Configuration Word, array offset: 0x11E40, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM15_MEM0_BLK_NSE_W[16]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11F40,
                                                   array step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM15_MEM1_BLK_CFG_W[8];  /**< MBC Memory Block Configuration Word, array offset: 0x11F80, array
                                                   step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM15_MEM1_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11FA0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM15_MEM2_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x11FA8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM15_MEM2_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11FC8, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM15_MEM3_BLK_CFG_W[8]; /**< MBC Memory Block Configuration Word, array offset: 0x11FD0, array
                                                  step: index*0x2000, index2*0x4 */
    __IO uint32_t MBC_DOM15_MEM3_BLK_NSE_W[2]; /**< MBC Memory Block NonSecure Enable Word, array offset: 0x11FF0, array
                                                  step: index*0x2000, index2*0x4 */
    uint8_t RESERVED_15[8];
} TRDC_MBC_Type;

/*!@brief TRDC MRC control register definition. MRC_DOM0_RGD_W[region][word] */
typedef struct _TRDC_MRC_Type
{
    __I uint32_t MRC_GLBCFG; /**< MRC Global Configuration Register, array offset: 0x14000, array step: 0x1000 */
    uint8_t RESERVED_0[12];
    __IO uint32_t
        MRC_NSE_RGN_INDIRECT; /**< MRC NonSecure Enable Region Indirect, array offset: 0x14010, array step: 0x1000 */
    __O uint32_t MRC_NSE_RGN_SET; /**< MRC NonSecure Enable Region Set, array offset: 0x14014, array step: 0x1000 */
    __O uint32_t MRC_NSE_RGN_CLR; /**< MRC NonSecure Enable Region Clear, array offset: 0x14018, array step: 0x1000 */
    __O uint32_t
        MRC_NSE_RGN_CLR_ALL; /**< MRC NonSecure Enable Region Clear All, array offset: 0x1401C, array step: 0x1000 */
    __IO uint32_t
        MRC_GLBAC[8]; /**< MRC Global Access Control, array offset: 0x14020, array step: index*0x1000, index2*0x4 */
    __IO uint32_t MRC_DOM0_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                            0x14040, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM0_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x140C0, array step: 0x1000 */
    uint8_t RESERVED_1[124];
    __IO uint32_t MRC_DOM1_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                            0x14140, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM1_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x141C0, array step: 0x1000 */
    uint8_t RESERVED_2[124];
    __IO uint32_t MRC_DOM2_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                            0x14240, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM2_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x142C0, array step: 0x1000 */
    uint8_t RESERVED_3[124];
    __IO uint32_t MRC_DOM3_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                            0x14340, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM3_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x143C0, array step: 0x1000 */
    uint8_t RESERVED_4[124];
    __IO uint32_t MRC_DOM4_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                            0x14440, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM4_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x144C0, array step: 0x1000 */
    uint8_t RESERVED_5[124];
    __IO uint32_t MRC_DOM5_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                            0x14540, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM5_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x145C0, array step: 0x1000 */
    uint8_t RESERVED_6[124];
    __IO uint32_t MRC_DOM6_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                            0x14640, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM6_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x146C0, array step: 0x1000 */
    uint8_t RESERVED_7[124];
    __IO uint32_t MRC_DOM7_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                            0x14740, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM7_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x147C0, array step: 0x1000 */
    uint8_t RESERVED_8[124];
    __IO uint32_t MRC_DOM8_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                            0x14840, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM8_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x148C0, array step: 0x1000 */
    uint8_t RESERVED_9[124];
    __IO uint32_t MRC_DOM9_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                            0x14940, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM9_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x149C0, array step: 0x1000 */
    uint8_t RESERVED_10[124];
    __IO uint32_t MRC_DOM10_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                             0x14A40, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM10_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x14AC0, array step: 0x1000 */
    uint8_t RESERVED_11[124];
    __IO uint32_t MRC_DOM11_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                             0x14B40, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM11_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x14BC0, array step: 0x1000 */
    uint8_t RESERVED_12[124];
    __IO uint32_t MRC_DOM12_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                             0x14C40, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM12_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x14CC0, array step: 0x1000 */
    uint8_t RESERVED_13[124];
    __IO uint32_t MRC_DOM13_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                             0x14D40, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM13_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x14DC0, array step: 0x1000 */
    uint8_t RESERVED_14[124];
    __IO uint32_t MRC_DOM14_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                             0x14E40, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM14_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x14EC0, array step: 0x1000 */
    uint8_t RESERVED_15[124];
    __IO uint32_t MRC_DOM15_RGD_W[16][2]; /**< MRC Region Descriptor Word 0..MRC Region Descriptor Word 1, array offset:
                                             0x14F40, array step: index*0x1000, index2*0x8, index3*0x4 */
    __IO uint32_t
        MRC_DOM15_RGD_NSE; /**< MRC Region Descriptor NonSecure Enable, array offset: 0x14FC0, array step: 0x1000 */
} TRDC_MRC_Type;

/*!@brief TRDC base address convert macro */
#define TRDC_GENERAL_BASE(base)      ((TRDC_General_Type *)((base)))
#define TRDC_FLW_BASE(base)          ((TRDC_FLW_Type *)(((uint32_t)(uintptr_t)(base) + (uint32_t)TRDC_FLW_OFFSET)))
#define TRDC_DOMAIN_ERROR_BASE(base) ((TRDC_DomainError_Type *)(((uint32_t)(uintptr_t)(base) + (uint32_t)TRDC_DOMAIN_ERROR_OFFSET)))
#define TRDC_DOMAIN_ASSIGNMENT_BASE(base) \
    ((TRDC_DomainAssignment_Type *)(((uint32_t)(uintptr_t)(base) + (uint32_t)TRDC_DOMAIN_ASSIGNMENT_OFFSET)))
#define TRDC_MBC_BASE(base, instance) \
    ((TRDC_MBC_Type *)((uint32_t)(uintptr_t)(base) + (uint32_t)TRDC_MBC_OFFSET(base) + (instance) * (uint32_t)TRDC_MBC_ARRAY_STEP))
#define TRDC_MRC_BASE(base, instance) \
    ((TRDC_MRC_Type *)((uint32_t)(uintptr_t)(base) + (uint32_t)TRDC_MRC_OFFSET(base) + (instance) * (uint32_t)TRDC_MRC_ARRAY_STEP))

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* FSL_TRDC_CORE_H_ */
