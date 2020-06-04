/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_tsc.h
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G45X_TSC_H__
#define __N32G45X_TSC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup TSC
 * @{
 */

/**
 * @brief detection period
 */
#define TSC_DET_PERIOD_MASK      (0x0F) // period bit mask
#define TSC_DET_PERIOD_OFFSET    (0x00) // period offset
#define TSC_DET_PERIOD_8_32KHZ   (0x00) // 8 x 32KHz =244.1us
#define TSC_DET_PERIOD_16_32KHZ  (0x01) // 16 x 32KHz =488.28us
#define TSC_DET_PERIOD_24_32KHZ  (0x02) // 24 x 32KHz =732.42us
#define TSC_DET_PERIOD_32_32KHZ  (0x03) // 32 x 32KHz =976.56us(default)
#define TSC_DET_PERIOD_40_32KHZ  (0x04) // 40 x 32KHz =1220.7us
#define TSC_DET_PERIOD_48_32KHZ  (0x05) // 48 x 32KHz =1464.84us
#define TSC_DET_PERIOD_56_32KHZ  (0x06) // 56 x 32KHz =1708.98us
#define TSC_DET_PERIOD_64_32KHZ  (0x07) // 64 x 32KHz =1953.13us
#define TSC_DET_PERIOD_72_32KHZ  (0x08) // 72 x 32KHz =2197.27us
#define TSC_DET_PERIOD_80_32KHZ  (0x09) // 80 x 32KHz =2441.41us
#define TSC_DET_PERIOD_88_32KHZ  (0x0A) // 88 x 32KHz =2685.55us
#define TSC_DET_PERIOD_96_32KHZ  (0x0B) // 96 x 32KHz =2929.69us
#define TSC_DET_PERIOD_104_32KHZ (0x0C) // 104 x 32KHz =3173.83us

// filter number
#define TSC_HW_DET_BITS_MASK (0x03) // filter width bit mask
#define TSC_HW_DET_OFFSET    (0x04) // filter offset
#define TSC_HW_DET_FILTER_1  (0x00) // interrupt over 1 time valid detect
#define TSC_HW_DET_FILTER_2  (0x10) // interrupt over 2 times valid detect
#define TSC_HW_DET_FILTER_3  (0x20) // interrupt over 3 times valid detect
#define TSC_HW_DET_FILTER_4  (0x30) // interrupt over 4 times valid detect

// comparator speed configuration
#define TSC_CMP_MASK    (0x03) // comparator offset bit mask
#define TSC_CMP_OFFSET  (0x04) // offset of comparator speed configuration
#define TSC_CMP_SPEED_0 (0x00) // 100KHZ~200KHZ
#define TSC_CMP_SPEED_1 (0x10) // 300KHZ~700KHZ
#define TSC_CMP_SPEED_2 (0x20) // 300KHZ~700KHZ
#define TSC_CMP_SPEED_3 (0x30) // 300KHZ~700KHZ

// resistance selection
#define TSC_RESIST_SEL_MASK   (0x01) // resistance selection bit mask
#define TSC_RESIST_SEL_OFFSET (0x06) // resistance selection offset
#define TSC_INNER_RESIST      (0x00) // internal resistance
#define TSC_EXT_RESIST        (0x04) // external resistance

// resistance value configuration
#define TSC_RESIST_1M   (0x00) // 1M
#define TSC_RESIST_875K (0x01) // 875K
#define TSC_RESIST_750K (0x02) // 750K
#define TSC_RESIST_625K (0x03) // 625K
#define TSC_RESIST_500K (0x04) // 500K
#define TSC_RESIST_375K (0x05) // 375K
#define TSC_RESIST_250K (0x06) // 250K
#define TSC_RESIST_125K (0x07) // 125K

// hardware detection mode
#define TSC_HW_DET_ENABLE (0x40)
#define TSC_HW_CHN_MASK   (0xFFFFFF)

// hardware detection status
#define TSC_HW_DET_ST (0x80)

// Enable detection below threshold(BASE-DELTA)
#define TSC_HW_LESS_DET_SEL (0x100)

// Enable detection above threshold(BASE+DELTA)
#define TSC_HW_GREAT_DET_SEL    (0x200)
#define TSC_HW_BASE_BITS_OFFSET (0)
#define TSC_HW_BASE_BITS_WIDTH  (0x7FF)

#define TSC_HW_DELTA_BITS_OFFSET (16)
#define TSC_HW_DELTA_BITS_WIDTH  (0xFF)

// enable detection interrupt
#define TSC_HW_DET_INTEN (0x400)

// tsc soft channel bit width
#define TSC_SW_CHN_VAILD_WIDTH (0x1F)

// TSC channel addr width(4bytes)
#define TSC_CHN_ADDR_WIDTH (4)

// TSC RESIS bit width
#define TSC_RES_BIT_VALID_BITS   (0x07)
#define TSC_RES_BIT_OFFSET_WIDTH (4)

// ad_tsc_out mux to timer4 etr port
#define TSC_SW_TIM_WIDTH   (0x3)
#define TSC_SW_TIM_OFFSET  (12)
#define TSC_SW_TM4_ETR_SEL (0x1000)

// ad_tsc_out mux to timer2 etr port
#define TSC_SW_TM2_ETR_SEL (0x2000)

// Enable software mode
#define TSC_SW_CHN_ENABLE (0x20)

// TSC status of hardware detection
#define TSC_HW_CNT_VAL_OFFSET        (0)
#define TSC_HW_CNT_VAL_BITS_MASK     (0x7FF)
#define TSC_HW_LESS_DET_FLAG_OFFSET  (12)
#define TSC_HW_LESS_DET_FLAG_MASK    (0x01)
#define TSC_HW_GREAT_DET_FLAG_OFFSET (13)
#define TSC_HW_GREAT_DET_FLAG_MASK   (0x01)
#define TSC_HW_CHN_NUM_OFFSET        (16)
#define TSC_HW_CHN_NUM_FLAG_MASK     (0x1F)

// TSC maximum channels of hardware detection
#define TSC_DET_MAX_CHN_COUNT (24)

/**
 * @brief define tsc channel num
 */
typedef enum
{
    TSC_CHN0  = 0x00000001, ///< tsc channel 0
    TSC_CHN1  = 0x00000002, ///< tsc channel 1
    TSC_CHN2  = 0x00000004, ///< tsc channel 2
    TSC_CHN3  = 0x00000008, ///< tsc channel 3
    TSC_CHN4  = 0x00000010, ///< tsc channel 4
    TSC_CHN5  = 0x00000020, ///< tsc channel 5
    TSC_CHN6  = 0x00000040, ///< tsc channel 6
    TSC_CHN7  = 0x00000080, ///< tsc channel 7
    TSC_CHN8  = 0x00000100, ///< tsc channel 8
    TSC_CHN9  = 0x00000200, ///< tsc channel 9
    TSC_CHN10 = 0x00000400, ///< tsc channel 10
    TSC_CHN11 = 0x00000800, ///< tsc channel 11
    TSC_CHN12 = 0x00001000, ///< tsc channel 12
    TSC_CHN13 = 0x00002000, ///< tsc channel 13
    TSC_CHN14 = 0x00004000, ///< tsc channel 14
    TSC_CHN15 = 0x00008000, ///< tsc channel 15
    TSC_CHN16 = 0x00010000, ///< tsc channel 16
    TSC_CHN17 = 0x00020000, ///< tsc channel 17
    TSC_CHN18 = 0x00040000, ///< tsc channel 18
    TSC_CHN19 = 0x00080000, ///< tsc channel 19
    TSC_CHN20 = 0x00100000, ///< tsc channel 20
    TSC_CHN21 = 0x00200000, ///< tsc channel 21
    TSC_CHN22 = 0x00400000, ///< tsc channel 22
    TSC_CHN23 = 0x00800000  ///< tsc channel 23
} TSC_Channel;

/**
 * @brief define tsc status type
 */
typedef enum
{
    TSC_STS_CNTVALUE  = 0, ///< tsc count of hardware detect
    TSC_STS_LESS_DET  = 1, ///< tsc less flag of hardware detect
    TSC_STS_GREAT_DET = 2, ///< tsc great flag  of hardware detect
    TSC_STS_CHN_NUM   = 3, ///< tsc chn number  of hardware detect
    TSC_DET_DET_ST    = 4, ///< tsc hw detect mode start status
} TSC_Status;

/**
 * @brief  TSC Init structure definition
 */
typedef struct
{
    uint8_t TSC_DetIntEnable; // Enable interrupt by hardware detection or not
    uint8_t TSC_GreatEnable;  // Enable detection above threshold.Interrupt if the pulse count is great than base+delta.
    uint8_t TSC_LessEnable;   // Enable detection below threshold.Interrupt if the pulse count is less than base-delta.
    uint8_t TSC_FilterCount;  // filter count of detection
    uint8_t TSC_DetPeriod;    // detection period
} TSC_InitType;

/**
 * @brief Channels setting of hardware detection
 */
typedef struct
{
    uint16_t TSC_Base;       // base value
    uint8_t TSC_Delta;      // offset value
    uint8_t TSC_ResisValue; // resistance value configuration
} TSC_ChnCfg;

/**
 * @brief Analog parameter configuration
 */
typedef struct
{
    uint8_t TSC_AnaoptrSpeedOption; // speed option
    uint8_t TSC_AnaoptrResisOption; // internal or external resistance option select
} TSC_AnaoCfg;

void TSC_Init(TSC_Module* TSC_Def, TSC_InitType* CtrlCfg);
void TSC_SetChannelCfg(TSC_Module* TSC_Def, TSC_ChnCfg* ChnCfg, uint32_t Channels);
void TSC_GetChannelCfg(TSC_Module* TSC_Def, TSC_ChnCfg* ChnCfg, uint32_t Channel);
void TSC_SetAnaoCfg(TSC_Module* TSC_Def, TSC_AnaoCfg* AnaoCfg);
void TSC_SW_SwtichChn(TSC_Module* TSC_Def, uint32_t Channel, TIM_Module* TIMx, FunctionalState Cmd);
void TSC_Cmd(TSC_Module* TSC_Def, uint32_t Channels, FunctionalState Cmd);
uint32_t TSC_GetStatus(TSC_Module* TSC_Def, TSC_Status type);
void TSC_SW_SwtichChn_Skip(uint32_t Channel);
void TSC_SW_Init_Skip(void);
#ifdef __cplusplus
}
#endif

#endif /* __N32G45X_TSC_H__ */

/**
 * @}
 */

/**
 * @}
 */
