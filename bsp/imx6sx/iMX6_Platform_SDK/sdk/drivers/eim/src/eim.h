/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __EIM_HDR__
#define __EIM_HDR__

#include "sdk.h"
#include "eim/eim_ifc.h"
#include "registers/regseim.h"

enum eim_reg_e {
    EIM_GCR1 = 0,
    EIM_GCR2 = 1,
    EIM_RCR1 = 2,
    EIM_RCR2 = 3,
    EIM_WCR1 = 4,
    EIM_WCR2 = 5,
    EIM_WCR = 6,
    EIM_WIAR = 7,
    EIM_NUM_REG = 8            //EAR is read only
};

//#define REG_CSCFG_MSK_CSEN ((uint32_t)0x00000001)
//#define REG_CSCFG_MSK_DSZ  ((uint32_t)0x00070000)
//#define REG_CSCFG_MSK_MUM  ((uint32_t)0x00000008)
//#define REG_CSCFG_MSK_SHFT ((uint32_t)0x00800000)
//#define REG_CSCFG_DSZ_SHIFT 16
#define REG_CSCFG_MAX_DSZ 7
#define REG_CSCFG_MIN_DSZ 1

typedef struct {
    volatile hw_eim_cs0gcr1_t GCR1; //!< Chip Select n General Configuration Register 1
    volatile hw_eim_cs0gcr2_t GCR2; //!< Chip Select n General Configuration Register 2
    volatile hw_eim_cs0rcr1_t RCR1; //!< Chip Select n Read Configuration Register 1
    volatile hw_eim_cs0rcr2_t RCR2; //!< Chip Select n Read Configuration Register 2
    volatile hw_eim_cs0wcr1_t WCR1; //!< Chip Select n Write Configuration Register 1
    volatile hw_eim_cs0wcr2_t WCR2; //!< Chip Select n Write Configuration Register 2
} eim_cs_reg_t;

#define HW_EIM_CS_REGS ((volatile eim_cs_reg_t *)HW_EIM_CS0GCR1_ADDR)

/*
typedef struct {
    eim_cs_reg_t reg_cs[EIM_NUM_CS];

    volatile uint32_t wcr;
    volatile uint32_t wiar;
    volatile uint32_t ear;
} eim_reg_t, *eim_reg_p;
*/
typedef struct {
    uint8_t id;                 //!< parameter ID
    uint8_t boolean;            //!< boolean or integer
    uint8_t shift;              //!< bit shift in register
    uint8_t reg;                //!< which register
    uint32_t mask;              //!< CFG mask
} eim_cfg_t;

#endif
