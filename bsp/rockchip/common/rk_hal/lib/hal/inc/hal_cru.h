/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

#ifdef HAL_CRU_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup CRU
 *  @{
 */

#ifndef _HAL_CRU_H_
#define _HAL_CRU_H_

#include "hal_def.h"

/*************************** MACRO Definition ****************************/
/** @defgroup CRU_Exported_Definition_Group1 Basic Definition
 *  @{
 */

#define MHZ 1000000
#define KHZ 1000

#ifndef PLL_INPUT_OSC_RATE
#define PLL_INPUT_OSC_RATE (24 * MHZ)
#endif

#define CLK_RESET_GET_REG_OFFSET(x) ((uint32_t)((x) / 16))
#define CLK_RESET_GET_BITS_SHIFT(x) ((uint32_t)((x) % 16))

#define CLK_GATE_GET_REG_OFFSET(x) ((uint32_t)((x) / 16))
#define CLK_GATE_GET_BITS_SHIFT(x) ((uint32_t)((x) % 16))

#define CLK_GET_MUX(x) ((x) & 0x0F0F00FFU)
#define CLK_GET_DIV(x) ((((x) & 0xFF00U) >> 8) | (((x) & 0xF0F00000U) >> 4))

#define WIDTH_TO_MASK(width) ((1 << (width)) - 1)

#define CLK_MUX_REG_OFFSET_SHIFT 0U
#define CLK_MUX_REG_OFFSET_MASK  0x0000FFFFU
#define CLK_MUX_SHIFT_SHIFT      16U
#define CLK_MUX_SHIFT_MASK       0x00FF0000U
#define CLK_MUX_WIDTH_SHIFT      24U
#define CLK_MUX_WIDTH_MASK       0xFF000000U

#define CLK_MUX_GET_REG_OFFSET(x) \
    (((uint32_t)(x) & CLK_MUX_REG_OFFSET_MASK) >> CLK_MUX_REG_OFFSET_SHIFT)
#define CLK_MUX_GET_BITS_SHIFT(x) \
    (((uint32_t)(x) & CLK_MUX_SHIFT_MASK) >> CLK_MUX_SHIFT_SHIFT)
#define CLK_MUX_GET_MASK(x)                                                      \
    WIDTH_TO_MASK((((uint32_t)(x) & CLK_MUX_WIDTH_MASK) >> CLK_MUX_WIDTH_SHIFT)) \
        << CLK_MUX_GET_BITS_SHIFT(x)

#define CLK_DIV_REG_OFFSET_SHIFT 0U
#define CLK_DIV_REG_OFFSET_MASK  0x0000FFFFU
#define CLK_DIV_SHIFT_SHIFT      16U
#define CLK_DIV_SHIFT_MASK       0x00FF0000U
#define CLK_DIV_WIDTH_SHIFT      24U
#define CLK_DIV_WIDTH_MASK       0xFF000000U

#define CLK_DIV_GET_REG_OFFSET(x) \
    (((uint32_t)(x) & CLK_DIV_REG_OFFSET_MASK) >> CLK_DIV_REG_OFFSET_SHIFT)
#define CLK_DIV_GET_BITS_SHIFT(x) \
    (((uint32_t)(x) & CLK_DIV_SHIFT_MASK) >> CLK_DIV_SHIFT_SHIFT)
#define CLK_DIV_GET_MASK(x)                                                      \
    WIDTH_TO_MASK((((uint32_t)(x) & CLK_DIV_WIDTH_MASK) >> CLK_DIV_WIDTH_SHIFT)) \
        << CLK_DIV_GET_BITS_SHIFT(x)

#define RK_PLL_RATE(_rate, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, \
                    _frac)                                                \
    {                                                                     \
        .rate = _rate##U, .fbDiv = _fbdiv, .postDiv1 = _postdiv1,         \
        .refDiv = _refdiv, .postDiv2 = _postdiv2, .dsmpd = _dsmpd,        \
        .frac = _frac,                                                    \
    }

struct PLL_CONFIG {
    uint32_t rate;
    uint32_t fbDiv;
    uint32_t postDiv1;
    uint32_t refDiv;
    uint32_t postDiv2;
    uint32_t dsmpd;
    uint32_t frac;
};

struct PLL_SETUP {
    __IO uint32_t *conOffset0;
    __IO uint32_t *conOffset1;
    __IO uint32_t *conOffset2;
    __IO uint32_t *conOffset3;
    __IO uint32_t *modeOffset;
    __I uint32_t *stat0;
    uint32_t modeShift;
    uint32_t lockShift;
    uint32_t modeMask;
    const struct PLL_CONFIG *rateTable;
};

typedef enum {
    GLB_SRST_FST = 0xfdb9,
    GLB_SRST_SND = 0xeca8,
} eCRU_GlbSrstType;

typedef enum {
    GLB_RST_FST_WDT0 = 0U,
    GLB_RST_SND_WDT0,
    GLB_RST_FST_WDT1,
    GLB_RST_SND_WDT1,
    GLB_RST_FST_WDT2,
    GLB_RST_SND_WDT2,
} eCRU_WdtRstType;

/***************************** Structure Definition **************************/

/** @} */
/***************************** Function Declare ******************************/
/** @defgroup CRU_Public_Function_Declare Public Function Declare
 *  @{
 */
uint32_t HAL_CRU_GetPllFreq(struct PLL_SETUP *pSetup);
HAL_Status HAL_CRU_SetPllFreq(struct PLL_SETUP *pSetup, uint32_t rate);
HAL_Status HAL_CRU_SetPllPowerUp(struct PLL_SETUP *pSetup);
HAL_Status HAL_CRU_SetPllPowerDown(struct PLL_SETUP *pSetup);

HAL_Check HAL_CRU_ClkIsEnabled(uint32_t clk);
HAL_Status HAL_CRU_ClkEnable(uint32_t clk);
HAL_Status HAL_CRU_ClkDisable(uint32_t clk);

HAL_Check HAL_CRU_ClkIsReset(uint32_t clk);
HAL_Status HAL_CRU_ClkResetAssert(uint32_t clk);
HAL_Status HAL_CRU_ClkResetDeassert(uint32_t clk);

HAL_Status HAL_CRU_ClkSetDiv(uint32_t divName, uint32_t divValue);
uint32_t HAL_CRU_ClkGetDiv(uint32_t divName);

HAL_Status HAL_CRU_ClkSetMux(uint32_t muxName, uint32_t muxValue);
uint32_t HAL_CRU_ClkGetMux(uint32_t muxName);

HAL_Status HAL_CRU_FracdivGetConfig(uint32_t rateOut, uint32_t rate,
                                    uint32_t *numerator,
                                    uint32_t *denominator);

uint32_t HAL_CRU_ClkGetFreq(eCLOCK_Name clockName);
HAL_Status HAL_CRU_ClkSetFreq(eCLOCK_Name clockName, uint32_t rate);

HAL_Status HAL_CRU_VopDclkEnable(uint32_t gateId);
HAL_Status HAL_CRU_VopDclkDisable(uint32_t gateId);

HAL_Status HAL_CRU_ClkNp5BestDiv(eCLOCK_Name clockName, uint32_t rate, uint32_t pRate, uint32_t *bestdiv);

HAL_Status HAL_CRU_SetGlbSrst(eCRU_GlbSrstType type);

HAL_Status HAL_CRU_WdtGlbRstEnable(eCRU_WdtRstType wdtType);

HAL_Status HAL_CRU_PllCompensation(eCLOCK_Name clockName, int ppm);

#ifdef HAL_CRU_AS_FEATURE_ENABLED
/**
 * @brief  it is for AS init.
 */
void HAL_CRU_AsInit(void);

/**
 * @brief  it is for AS enable.
 * @param  ch: channel
 * @param  en: 1 is enable, 0 is disable.
 */
void HAL_CRU_AsEnable(uint8_t ch, uint8_t en);
#endif

/** @} */

#endif

/** @} */

/** @} */

#endif /* HAL_CRU_MODULE_ENABLED */
