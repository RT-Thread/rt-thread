/**
 *******************************************************************************
 * @file  hc32_ll_clk.c
 * @brief This file provides firmware functions to manage the Clock(CLK).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-09-30       CDT             Modify API CLK_Xtal32Cmd(), CLK_MrcCmd() and CLK_LrcCmd(), use DDL_DelayUS() to replace CLK_Delay()
   2023-12-15       CDT             Refine API CLK_XtalStdInit. and add API CLK_XtalStdCmd, CLK_SetXtalStdExceptionType
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_clk.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_CLK CLK
 * @brief Clock Driver Library
 * @{
 */

#if (LL_CLK_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CLK_Local_Macros CLK Local Macros
 * @{
 */

/**
 * @brief CLK_FREQ Clock frequency definition
 */
#define CLK_FREQ_48M                    (48UL*1000UL*1000UL)
#define CLK_FREQ_64M                    (64UL*1000UL*1000UL)
#define CLK_FREQ_32M                    (32UL*1000UL*1000UL)

/**
 * @brief Be able to modify TIMEOUT according to board condition.
 */
#define CLK_TIMEOUT                     ((uint32_t)0x1000UL)
#define CLK_LRC_TIMEOUT                 (160U)
#define CLK_MRC_TIMEOUT                 (1U)
#define CLK_XTAL32_TIMEOUT              (160U)

/**
 * @brief XTALSTD exception type mask
 */
#define CLK_XTALSTD_EXP_TYPE_MASK       (CMU_XTALSTDCR_XTALSTDIE | CMU_XTALSTDCR_XTALSTDRE | CMU_XTALSTDCR_XTALSTDRIS)

/**
 * @brief LRC State ON or OFF
 */
#define CLK_LRC_OFF                     (CMU_LRCCR_LRCSTP)
#define CLK_LRC_ON                      (0x00U)

/**
 * @brief MRC State ON or OFF
 */
#define CLK_MRC_OFF                     (CMU_MRCCR_MRCSTP)
#define CLK_MRC_ON                      (0x80U)

/**
 * @brief Clk PLL Relevant Parameter Range Definition
 */
#define CLK_PLLP_DEFAULT                (0x01UL)
#define CLK_PLLQ_DEFAULT                (0x01UL)
#define CLK_PLLR_DEFAULT                (0x01UL)
#define CLK_PLLN_DEFAULT                (0x13UL)
#define CLK_PLLM_DEFAULT                (0x00UL)

#define CLK_PLLR_DIV_MIN                (2UL)
#define CLK_PLLR_DIV_MAX                (16UL)
#define CLK_PLLQ_DIV_MIN                (2UL)
#define CLK_PLLQ_DIV_MAX                (16UL)
#define CLK_PLLP_DIV_MIN                (2UL)
#define CLK_PLLP_DIV_MAX                (16UL)

#define CLK_PLL_FREQ_MIN                (375UL*100UL*1000UL)
#define CLK_PLL_VCO_IN_MIN              (8UL*1000UL*1000UL)
#define CLK_PLL_VCO_IN_MAX              (25UL*1000UL*1000UL)
#define CLK_PLL_VCO_OUT_MIN             (600UL*1000UL*1000UL)
#define CLK_PLL_VCO_OUT_MAX             (1200UL*1000UL*1000UL)
#define CLK_PLLM_DIV_MIN                (1UL)
#define CLK_PLLM_DIV_MAX                (4UL)
#define CLK_PLLN_MULTI_MIN              (25UL)
#define CLK_PLLN_MULTI_MAX              (150UL)
#define CLK_PLL_FREQ_MAX                (200UL*1000UL*1000UL)

/**
 * @brief Clk PLL Register Redefinition
 */
#define PLL_SRC_REG                     (CM_CMU->PLLHCFGR)
#define PLL_SRC_BIT                     (CMU_PLLHCFGR_PLLSRC)
#define PLL_SRC_POS                     (CMU_PLLHCFGR_PLLSRC_POS)
#define PLL_SRC                         ((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLSRC) >> CMU_PLLHCFGR_PLLSRC_POS)
#define PLL_EN_REG                      (CM_CMU->PLLHCR)

/**
 * @brief Switch clock stable time
 * @note Approx. 30us
 */
#define CLK_SYSCLK_SW_STB               (30U)

/**
 * @brief Clk FCG Default Value
 */
#define CLK_FCG0_DEFAULT                (0xFFFFFA0EUL)
#define CLK_FCG1_DEFAULT                (0xFFFFFFFFUL)
#define CLK_FCG2_DEFAULT                (0xFFFFFFFFUL)
#define CLK_FCG3_DEFAULT                (0xFFFFFFFFUL)

/**
 * @defgroup CLK_Check_Parameters_Validity CLK Check Parameters Validity
 * @{
 */
/* Check CLK register lock status. */
#define IS_CLK_UNLOCKED()               ((CM_PWC->FPRC & PWC_FPRC_FPRCB0) == PWC_FPRC_FPRCB0)
#define IS_PWC_UNLOCKED()               ((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)

/* Parameter valid check for XTAL state */
#define IS_CLK_XTAL_STATE(x)                                                   \
(   ((x) == CLK_XTAL_OFF)                         ||                           \
    ((x) == CLK_XTAL_ON))

/* Parameter valid check for XTAL mode */
#define IS_CLK_XTAL_MD(x)                                                      \
(   ((x) == CLK_XTAL_MD_OSC)                      ||                           \
    ((x) == CLK_XTAL_MD_EXCLK))

/* Parameter valid check for XTAL driver ability mode */
#define IS_CLK_XTAL_DRV_MD(x)                                                  \
(   ((x) == CLK_XTAL_DRV_HIGH)                    ||                           \
    ((x) == CLK_XTAL_DRV_MID)                     ||                           \
    ((x) == CLK_XTAL_DRV_LOW)                     ||                           \
    ((x) == CLK_XTAL_DRV_ULOW))

/* Parameter valid check for XTAL stable time selection */
#define IS_CLK_XTAL_STB_SEL(x)                                                 \
(   ((x) == CLK_XTAL_STB_133US)                   ||                           \
    ((x) == CLK_XTAL_STB_255US)                   ||                           \
    ((x) == CLK_XTAL_STB_499US)                   ||                           \
    ((x) == CLK_XTAL_STB_988US)                   ||                           \
    ((x) == CLK_XTAL_STB_2MS)                     ||                           \
    ((x) == CLK_XTAL_STB_4MS)                     ||                           \
    ((x) == CLK_XTAL_STB_8MS)                     ||                           \
    ((x) == CLK_XTAL_STB_16MS)                    ||                           \
    ((x) == CLK_XTAL_STB_31MS))

/* Parameter valid check for XTALDIV state */
#define IS_CLK_XTALDIV_STATE(x)                                                \
(   ((x) == CLK_XTALDIV_OFF)                      ||                           \
    ((x) == CLK_XTALDIV_ON))

/* Parameter valid check for XTALSTD state */
#define IS_CLK_XTALSTD_STATE(x)                                                \
(   ((x) == CLK_XTALSTD_OFF)                      ||                           \
    ((x) == CLK_XTALSTD_ON))

/* Parameter valid check for XTALSTD exception type */
#define IS_CLK_XTALSTD_EXP_TYPE(x)                                             \
(   ((x) == CLK_XTALSTD_EXP_TYPE_NONE)            ||                           \
    ((x) == CLK_XTALSTD_EXP_TYPE_RST)             ||                           \
    ((x) == CLK_XTALSTD_EXP_TYPE_INT))

/* Parameter valid check for PLL state */
#define IS_CLK_PLL_STATE(x)                                                    \
(   ((x) == CLK_PLL_OFF)                          ||                           \
    ((x) == CLK_PLL_ON))

/* Parameter validity check for PLL input source */
#define IS_CLK_PLL_SRC(x)                                                      \
(   ((x) == CLK_PLL_SRC_XTAL)                     ||                           \
    ((x) == CLK_PLL_SRC_HRC))

/* Parameter validity check for PLL frequency range */
#define IS_CLK_PLL_FREQ(x)                                                     \
(   ((x) <= CLK_PLL_FREQ_MAX)                     &&                           \
    ((x) >= CLK_PLL_FREQ_MIN))

/* Parameter validity check for PLL M divide */
#define IS_CLK_PLLM_DIV(x)                                                     \
(   ((x) <= CLK_PLLM_DIV_MAX)                     &&                           \
    ((x) >= CLK_PLLM_DIV_MIN))

/* Parameter validity check for PLL N multi- */
#define IS_CLK_PLLN_MULTI(x)                                                   \
(   ((x) <= CLK_PLLN_MULTI_MAX)                   &&                           \
    ((x) >= CLK_PLLN_MULTI_MIN))

/* Parameter validity check for PLL P divide */
#define IS_CLK_PLLP_DIV(x)                                                     \
(   ((x) <= CLK_PLLP_DIV_MAX)                     &&                           \
    ((x) >= CLK_PLLP_DIV_MIN))

/* Parameter validity check for PLL_input freq./PLLM(vco_in) */
#define IS_CLK_PLL_VCO_IN(x)                                                   \
(   ((x) <= CLK_PLL_VCO_IN_MAX)                   &&                           \
    ((x) >= CLK_PLL_VCO_IN_MIN))

/* Parameter validity check for PLL vco_in*PLLN(vco_out) */
#define IS_CLK_PLL_VCO_OUT(x)                                                  \
(   ((x) <= CLK_PLL_VCO_OUT_MAX)                  &&                           \
    ((x) >= CLK_PLL_VCO_OUT_MIN))

/* Parameter validity check for PLL R divide */
#define IS_CLK_PLLR_DIV(x)                                                     \
(   ((x) <= CLK_PLLR_DIV_MAX)                     &&                           \
    ((x) >= CLK_PLLR_DIV_MIN))

/* Parameter validity check for PLL Q divide */
#define IS_CLK_PLLQ_DIV(x)                                                     \
(   ((x) <= CLK_PLLQ_DIV_MAX)                     &&                           \
    ((x) >= CLK_PLLQ_DIV_MIN))

/* Parameter valid check for XTAL32 state */
#define IS_CLK_XTAL32_STATE(x)                                                 \
(   ((x) == CLK_XTAL32_OFF)                       ||                           \
    ((x) == CLK_XTAL32_ON))

/* Parameter valid check for XTAL32 driver ability mode */
#define IS_CLK_XTAL32_DRV_MD(x)                                                \
(   ((x) == CLK_XTAL32_DRV_MID)                   ||                           \
    ((x) == CLK_XTAL32_DRV_HIGH))

/* Parameter valid check for XTAL32 filtering selection */
#define IS_CLK_XTAL32_FILT_SEL(x)                                              \
(   ((x) == CLK_XTAL32_FILTER_ALL_MD)             ||                           \
    ((x) == CLK_XTAL32_FILTER_RUN_MD)             ||                           \
    ((x) == CLK_XTAL32_FILTER_OFF))

/* Parameter valid check for system clock source */
#define IS_CLK_SYSCLK_SRC(x)                                                   \
(   ((x) == CLK_SYSCLK_SRC_HRC)                   ||                           \
    ((x) == CLK_SYSCLK_SRC_MRC)                   ||                           \
    ((x) == CLK_SYSCLK_SRC_LRC)                   ||                           \
    ((x) == CLK_SYSCLK_SRC_XTAL)                  ||                           \
    ((x) == CLK_SYSCLK_SRC_XTAL32)                ||                           \
    ((x) == CLK_SYSCLK_SRC_PLL))

/* Parameter valid check for CLK stable flag. */
#define IS_CLK_STB_FLAG(x)                                                     \
(   ((x) != 0x00U)                                &&                           \
    (((x) | CLK_STB_FLAG_MASK) == CLK_STB_FLAG_MASK))

/* Parameter valid check for bus clock category */
#define IS_CLK_BUS_CLK_CATE(x)                   (((x) & CLK_BUS_CLK_ALL) != (0x00U))

/* Parameter valid check for HCLK divider */
#define IS_CLK_HCLK_DIV(x)                                                     \
(   ((x) == CLK_HCLK_DIV1)                        ||                           \
    ((x) == CLK_HCLK_DIV2)                        ||                           \
    ((x) == CLK_HCLK_DIV4)                        ||                           \
    ((x) == CLK_HCLK_DIV8)                        ||                           \
    ((x) == CLK_HCLK_DIV16)                       ||                           \
    ((x) == CLK_HCLK_DIV32)                       ||                           \
    ((x) == CLK_HCLK_DIV64))

/* Parameter valid check for PCLK1 divider */
#define IS_CLK_PCLK1_DIV(x)                                                    \
(   ((x) == CLK_PCLK1_DIV1)                       ||                           \
    ((x) == CLK_PCLK1_DIV2)                       ||                           \
    ((x) == CLK_PCLK1_DIV4)                       ||                           \
    ((x) == CLK_PCLK1_DIV8)                       ||                           \
    ((x) == CLK_PCLK1_DIV16)                      ||                           \
    ((x) == CLK_PCLK1_DIV32)                      ||                           \
    ((x) == CLK_PCLK1_DIV64))

/* Parameter valid check for PCLK4 divider */
#define IS_CLK_PCLK4_DIV(x)                                                    \
(   ((x) == CLK_PCLK4_DIV1)                       ||                           \
    ((x) == CLK_PCLK4_DIV2)                       ||                           \
    ((x) == CLK_PCLK4_DIV4)                       ||                           \
    ((x) == CLK_PCLK4_DIV8)                       ||                           \
    ((x) == CLK_PCLK4_DIV16)                      ||                           \
    ((x) == CLK_PCLK4_DIV32)                      ||                           \
    ((x) == CLK_PCLK4_DIV64))

/* Parameter valid check for PCLK3 divider */
#define IS_CLK_PCLK3_DIV(x)                                                    \
(   ((x) == CLK_PCLK3_DIV1)                       ||                           \
    ((x) == CLK_PCLK3_DIV2)                       ||                           \
    ((x) == CLK_PCLK3_DIV4)                       ||                           \
    ((x) == CLK_PCLK3_DIV8)                       ||                           \
    ((x) == CLK_PCLK3_DIV16)                      ||                           \
    ((x) == CLK_PCLK3_DIV32)                      ||                           \
    ((x) == CLK_PCLK3_DIV64))

/* Parameter valid check for EXCLK divider */
#define IS_CLK_EXCLK_DIV(x)                                                    \
(   ((x) == CLK_EXCLK_DIV1)                       ||                           \
    ((x) == CLK_EXCLK_DIV2)                       ||                           \
    ((x) == CLK_EXCLK_DIV4)                       ||                           \
    ((x) == CLK_EXCLK_DIV8)                       ||                           \
    ((x) == CLK_EXCLK_DIV16)                      ||                           \
    ((x) == CLK_EXCLK_DIV32)                      ||                           \
    ((x) == CLK_EXCLK_DIV64))

/* Parameter valid check for PCLK0 divider */
#define IS_CLK_PCLK0_DIV(x)                                                    \
(   ((x) == CLK_PCLK0_DIV1)                       ||                           \
    ((x) == CLK_PCLK0_DIV2)                       ||                           \
    ((x) == CLK_PCLK0_DIV4)                       ||                           \
    ((x) == CLK_PCLK0_DIV8)                       ||                           \
    ((x) == CLK_PCLK0_DIV16)                      ||                           \
    ((x) == CLK_PCLK0_DIV32)                      ||                           \
    ((x) == CLK_PCLK0_DIV64))

/* Parameter valid check for PCLK2 divider */
#define IS_CLK_PCLK2_DIV(x)                                                    \
(   ((x) == CLK_PCLK2_DIV1)                       ||                           \
    ((x) == CLK_PCLK2_DIV2)                       ||                           \
    ((x) == CLK_PCLK2_DIV4)                       ||                           \
    ((x) == CLK_PCLK2_DIV8)                       ||                           \
    ((x) == CLK_PCLK2_DIV16)                      ||                           \
    ((x) == CLK_PCLK2_DIV32)                      ||                           \
    ((x) == CLK_PCLK2_DIV64))

/* Parameter valid check for bus clock */
#define IS_CLK_BUS_CLK(x)                                                      \
(   ((x) == CLK_BUS_HCLK)                         ||                           \
    ((x) == CLK_BUS_EXCLK)                        ||                           \
    ((x) == CLK_BUS_PCLK0)                        ||                           \
    ((x) == CLK_BUS_PCLK1)                        ||                           \
    ((x) == CLK_BUS_PCLK2)                        ||                           \
    ((x) == CLK_BUS_PCLK3)                        ||                           \
    ((x) == CLK_BUS_PCLK4))

/* Parameter valid check for CAN clock source */
#define IS_CLK_CANCLK(x)                                                       \
(   ((x) == CLK_MCANCLK_SYSCLK_DIV2)              ||                           \
    ((x) == CLK_MCANCLK_SYSCLK_DIV3)              ||                           \
    ((x) == CLK_MCANCLK_SYSCLK_DIV4)              ||                           \
    ((x) == CLK_MCANCLK_SYSCLK_DIV5)              ||                           \
    ((x) == CLK_MCANCLK_SYSCLK_DIV6)              ||                           \
    ((x) == CLK_MCANCLK_SYSCLK_DIV7)              ||                           \
    ((x) == CLK_MCANCLK_SYSCLK_DIV8)              ||                           \
    ((x) == CLK_MCANCLK_PLLQ)                     ||                           \
    ((x) == CLK_MCANCLK_PLLR)                     ||                           \
    ((x) == CLK_MCANCLK_XTAL ))

/* Parameter valid check for CAN channel for clock source config */
#define IS_CLK_CAN_UNIT(x)                                                     \
(   ((x) == CLK_MCAN1)                            ||                           \
    ((x) == CLK_MCAN2))

/* Parameter valid check for peripheral source */
#define IS_CLK_PERIPHCLK_SRC(x)                                                \
(   ((x) == CLK_PERIPHCLK_PCLK)                   ||                           \
    ((x) == CLK_PERIPHCLK_PLLQ)                   ||                           \
    ((x) == CLK_PERIPHCLK_PLLR))

/* Parameter valid check for TPIU clock divider */
#define IS_CLK_TPIUCLK_DIV(x)                                                 \
(   ((x) == CLK_TPIUCLK_DIV1)                     ||                          \
    ((x) == CLK_TPIUCLK_DIV2)                     ||                          \
    ((x) == CLK_TPIUCLK_DIV4))

/* Parameter valid check for CLK MCO clock source  . */
#define IS_CLK_MCO_SRC(x)                                                      \
(   ((x) == CLK_MCO_SRC_HRC)                      ||                           \
    ((x) == CLK_MCO_SRC_MRC)                      ||                           \
    ((x) == CLK_MCO_SRC_LRC)                      ||                           \
    ((x) == CLK_MCO_SRC_XTAL)                     ||                           \
    ((x) == CLK_MCO_SRC_XTAL32)                   ||                           \
    ((x) == CLK_MCO_SRC_PLLP)                     ||                           \
    ((x) == CLK_MCO_SRC_PLLQ)                     ||                           \
    ((x) == CLK_MCO_SRC_HCLK))

/* Parameter valid check for CLK MCO clock divide. */
#define IS_CLK_MCO_DIV(x)                                                      \
(   ((x) == CLK_MCO_DIV1)                         ||                           \
    ((x) == CLK_MCO_DIV2)                         ||                           \
    ((x) == CLK_MCO_DIV4)                         ||                           \
    ((x) == CLK_MCO_DIV8)                         ||                           \
    ((x) == CLK_MCO_DIV16)                        ||                           \
    ((x) == CLK_MCO_DIV32)                        ||                           \
    ((x) == CLK_MCO_DIV64)                        ||                           \
    ((x) == CLK_MCO_DIV128))

/* Parameter valid check for CLK MCO channel. */
#define IS_CLK_MCO_CH(x)                                                       \
(   ((x) == CLK_MCO1)                             ||                           \
    ((x) == CLK_MCO2))
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CLK_Local_Functions CLK Local Functions
 * @{
 */
/**
 * @brief  Wait clock stable flag.
 * @param  [in] u8Flag      Specifies the stable flag to be wait. @ref CLK_STB_Flag
 * @param  [in] u32Time     Specifies the time to wait while the flag not be set.
 * @retval int32_t
 */
static int32_t CLK_WaitStable(uint8_t u8Flag, uint32_t u32Time)
{
    __IO uint32_t u32Timeout = 0UL;
    int32_t i32Ret = LL_ERR_TIMEOUT;

    while (u32Timeout <= u32Time) {
        if (SET == CLK_GetStableStatus(u8Flag)) {
            i32Ret = LL_OK;
            break;
        }
        u32Timeout++;
    }
    return i32Ret;
}

static void SetSysClockSrc(uint8_t u8Src)
{
    uint8_t u8TmpFlag = 0U;
    /* backup FCGx setting */
    __IO uint32_t fcg0 = CM_PWC->FCG0;
    __IO uint32_t fcg1 = CM_PWC->FCG1;
    __IO uint32_t fcg2 = CM_PWC->FCG2;
    __IO uint32_t fcg3 = CM_PWC->FCG3;

    DDL_ASSERT(IS_CLK_SYSCLK_SRC(u8Src));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Only current system clock source or target system clock source is PLLH
    need to close fcg0~fcg3 and open fcg0~fcg3 during switch system clock source.
    We need to backup fcg0~fcg3 before close them. */
    if (CLK_SYSCLK_SRC_PLL == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW) || (CLK_SYSCLK_SRC_PLL == u8Src)) {
        u8TmpFlag = 1U;
        /* FCG0 protect judgment */
        DDL_ASSERT((CM_PWC->FCG0PC & PWC_FCG0PC_PRT0) == PWC_FCG0PC_PRT0);
        /* Close FCGx. */
        WRITE_REG32(CM_PWC->FCG0, CLK_FCG0_DEFAULT);
        WRITE_REG32(CM_PWC->FCG1, CLK_FCG1_DEFAULT);
        WRITE_REG32(CM_PWC->FCG2, CLK_FCG2_DEFAULT);
        WRITE_REG32(CM_PWC->FCG3, CLK_FCG3_DEFAULT);
        /* Wait stable after close FCGx. */
        DDL_DelayUS(CLK_SYSCLK_SW_STB);
    }
    /* Set system clock source */
    WRITE_REG8(CM_CMU->CKSWR, u8Src);
    /* Wait stable after setting system clock source */
    DDL_DelayUS(CLK_SYSCLK_SW_STB);
    if (1U == u8TmpFlag) {
        WRITE_REG32(CM_PWC->FCG0, fcg0);
        WRITE_REG32(CM_PWC->FCG1, fcg1);
        WRITE_REG32(CM_PWC->FCG2, fcg2);
        WRITE_REG32(CM_PWC->FCG3, fcg3);
        /* Wait stable after open fcg. */
        DDL_DelayUS(CLK_SYSCLK_SW_STB);
    }
}

static void GetClockFreq(stc_clock_freq_t *pstcClockFreq)
{
    stc_clock_scale_t *pstcClockScale;
    uint32_t u32HrcValue;
    uint8_t plln;
    uint8_t pllp;
    uint8_t pllm;

    switch (READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW)) {
        case CLK_SYSCLK_SRC_HRC:
            /* HRC is used to system clock */
            pstcClockFreq->u32SysclkFreq = HRC_VALUE;
            break;
        case CLK_SYSCLK_SRC_MRC:
            /* MRC is used to system clock */
            pstcClockFreq->u32SysclkFreq = MRC_VALUE;
            break;
        case CLK_SYSCLK_SRC_LRC:
            /* LRC is used to system clock */
            pstcClockFreq->u32SysclkFreq = LRC_VALUE;
            break;
        case CLK_SYSCLK_SRC_XTAL:
            /* XTAL is used to system clock */
            pstcClockFreq->u32SysclkFreq = XTAL_VALUE;
            break;
        case CLK_SYSCLK_SRC_XTAL32:
            /* XTAL32 is used to system clock */
            pstcClockFreq->u32SysclkFreq = XTAL32_VALUE;
            break;
        case CLK_SYSCLK_SRC_PLL:
            /* PLLHP is used as system clock. */
            pllp = (uint8_t)((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHP) >> CMU_PLLHCFGR_PLLHP_POS);
            plln = (uint8_t)((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHN) >> CMU_PLLHCFGR_PLLHN_POS);
            pllm = (uint8_t)((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHM) >> CMU_PLLHCFGR_PLLHM_POS);
            /* pll = ((pllin / pllm) * plln) / pllp */
            if (CLK_PLL_SRC_XTAL == PLL_SRC) {
                pstcClockFreq->u32SysclkFreq = ((XTAL_VALUE / (pllm + 1UL)) * (plln + 1UL)) / (pllp + 1UL);
            } else {
                u32HrcValue = HRC_VALUE;
                pstcClockFreq->u32SysclkFreq = ((u32HrcValue / (pllm + 1UL)) * (plln + 1UL)) / (pllp + 1UL);
            }
            break;
        default:
            break;
    }

    pstcClockScale = (stc_clock_scale_t *)((uint32_t)&CM_CMU->SCFGR);
    pstcClockScale->SCFGR = READ_REG32(CM_CMU->SCFGR);
    /* Get hclk. */
    pstcClockFreq->u32HclkFreq = pstcClockFreq->u32SysclkFreq >> pstcClockScale->SCFGR_f.HCLKS;
    /* Get pclk1. */
    pstcClockFreq->u32Pclk1Freq = pstcClockFreq->u32SysclkFreq >> pstcClockScale->SCFGR_f.PCLK1S;
    /* Get pclk4. */
    pstcClockFreq->u32Pclk4Freq = pstcClockFreq->u32SysclkFreq >> pstcClockScale->SCFGR_f.PCLK4S;
    /* Get pclk3. */
    pstcClockFreq->u32Pclk3Freq = pstcClockFreq->u32SysclkFreq >> pstcClockScale->SCFGR_f.PCLK3S;
    /* Get exclk. */
    pstcClockFreq->u32ExclkFreq = pstcClockFreq->u32SysclkFreq >> pstcClockScale->SCFGR_f.EXCKS;
    /* Get pclk0. */
    pstcClockFreq->u32Pclk0Freq = pstcClockFreq->u32SysclkFreq >> pstcClockScale->SCFGR_f.PCLK0S;
    /* Get pclk2. */
    pstcClockFreq->u32Pclk2Freq = pstcClockFreq->u32SysclkFreq >> pstcClockScale->SCFGR_f.PCLK2S;
}

static void SetSysClockDiv(uint32_t u32Clock, uint32_t u32Div)
{
    uint8_t u8TmpFlag = 0U;

    /* backup FCGx setting */
    __IO uint32_t fcg0 = CM_PWC->FCG0;
    __IO uint32_t fcg1 = CM_PWC->FCG1;
    __IO uint32_t fcg2 = CM_PWC->FCG2;
    __IO uint32_t fcg3 = CM_PWC->FCG3;

    DDL_ASSERT(IS_CLK_HCLK_DIV(u32Div & CMU_SCFGR_HCLKS));
    DDL_ASSERT(IS_CLK_PCLK1_DIV(u32Div & CMU_SCFGR_PCLK1S));
    DDL_ASSERT(IS_CLK_PCLK4_DIV(u32Div & CMU_SCFGR_PCLK4S));
    DDL_ASSERT(IS_CLK_EXCLK_DIV(u32Div & CMU_SCFGR_EXCKS));
    DDL_ASSERT(IS_CLK_PCLK0_DIV(u32Div & CMU_SCFGR_PCLK0S));
    DDL_ASSERT(IS_CLK_PCLK2_DIV(u32Div & CMU_SCFGR_PCLK2S));
    DDL_ASSERT(IS_CLK_PCLK3_DIV(u32Div & CMU_SCFGR_PCLK3S));
    DDL_ASSERT(IS_CLK_BUS_CLK_CATE(u32Clock));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Only current system clock source or target system clock source is PLLH
    need to close fcg0~fcg3 and open fcg0~fcg3 during switch system clock source.
    We need to backup fcg0~fcg3 before close them. */
    if (CLK_SYSCLK_SRC_PLL == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW)) {
        u8TmpFlag = 1U;
        DDL_ASSERT((CM_PWC->FCG0PC & PWC_FCG0PC_PRT0) == PWC_FCG0PC_PRT0);
        /* Close FCGx. */
        WRITE_REG32(CM_PWC->FCG0, CLK_FCG0_DEFAULT);
        WRITE_REG32(CM_PWC->FCG1, CLK_FCG1_DEFAULT);
        WRITE_REG32(CM_PWC->FCG2, CLK_FCG2_DEFAULT);
        WRITE_REG32(CM_PWC->FCG3, CLK_FCG3_DEFAULT);
        /* Wait stable after close FCGx. */
        DDL_DelayUS(CLK_SYSCLK_SW_STB);
    }
    MODIFY_REG32(CM_CMU->SCFGR, u32Clock, u32Div);
    DDL_DelayUS(CLK_SYSCLK_SW_STB);
    if (1U == u8TmpFlag) {
        WRITE_REG32(CM_PWC->FCG0, fcg0);
        WRITE_REG32(CM_PWC->FCG1, fcg1);
        WRITE_REG32(CM_PWC->FCG2, fcg2);
        WRITE_REG32(CM_PWC->FCG3, fcg3);
        /* Wait stable after open fcg. */
        DDL_DelayUS(CLK_SYSCLK_SW_STB);
    }
}

/**
 * @}
 */

/**
 * @defgroup CLK_Global_Functions CLK Global Functions
 * @{
 */
/**
 * @brief  LRC function enable/disable.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *         - LL_OK: LRC operate successfully
 *         - LL_ERR_BUSY: LRC is the system clock, CANNOT stop it.
 * @note   DO NOT STOP LRC while using it as system clock.
 */
int32_t CLK_LrcCmd(en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (DISABLE == enNewState) {
        if (CLK_SYSCLK_SRC_LRC == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW)) {
            i32Ret = LL_ERR_BUSY;
        } else {
            WRITE_REG8(CM_CMU->LRCCR, CLK_LRC_OFF);
        }
    } else {
        WRITE_REG8(CM_CMU->LRCCR, CLK_LRC_ON);
    }
    /* wait approx, 5 * LRC cycle */
    DDL_DelayUS(CLK_LRC_TIMEOUT);

    return i32Ret;
}

/**
 * @brief  MRC function enable/disable.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *         - LL_OK: MRC operate successfully
 *         - LL_ERR_BUSY: MRC is the system clock, CANNOT stop it.
 * @note   DO NOT STOP MRC while using it as system clock.
 */
int32_t CLK_MrcCmd(en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (DISABLE == enNewState) {
        if (CLK_SYSCLK_SRC_MRC == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW)) {
            i32Ret = LL_ERR_BUSY;
        } else {
            WRITE_REG8(CM_CMU->MRCCR, CLK_MRC_OFF);
        }
    } else {
        WRITE_REG8(CM_CMU->MRCCR, CLK_MRC_ON);
    }
    /* Wait approx. 5 * MRC cycle */
    DDL_DelayUS(CLK_MRC_TIMEOUT);

    return i32Ret;
}

/**
 * @brief  HRC function enable/disable.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *         - LL_OK: HRC operate successfully
 *         - LL_ERR_BUSY: HRC is the system clock or as the PLL source clock, CANNOT stop it.
 *         - LL_ERR_TIMEOUT: HRC operate Timeout
 * @note   DO NOT STOP HRC while using it as system clock or as the PLL source clock.
 */
int32_t CLK_HrcCmd(en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (DISABLE == enNewState) {
        if (CLK_SYSCLK_SRC_HRC == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW)) {
            i32Ret = LL_ERR_BUSY;
        } else if (CLK_PLL_SRC_HRC == PLL_SRC) {
            /* HRC as PLL clock source and PLL is working */
            if (0UL == PLL_EN_REG) {
                i32Ret = LL_ERR_BUSY;
            } else {
                WRITE_REG8(CM_CMU->HRCCR, CLK_HRC_OFF);
            }
        } else {
            WRITE_REG8(CM_CMU->HRCCR, CLK_HRC_OFF);
        }
    } else {
        WRITE_REG8(CM_CMU->HRCCR, CLK_HRC_ON);
        i32Ret = CLK_WaitStable(CLK_STB_FLAG_HRC, CLK_TIMEOUT);
    }

    return i32Ret;
}

/**
 * @brief  Set HRC trimming value.
 * @param  [in] i8TrimVal specifies the trimming value for HRC.
 * @retval None
 */
void CLK_HrcTrim(int8_t i8TrimVal)
{
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG8(CM_CMU->HRCTRM, i8TrimVal);
}

/**
 * @brief  Set MRC trimming value.
 * @param  [in] i8TrimVal specifies the trimming value for MRC.
 * @retval None
 */
void CLK_MrcTrim(int8_t i8TrimVal)
{
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG8(CM_CMU->MRCTRM, i8TrimVal);
}

/**
 * @brief  Set LRC trimming value.
 * @param  [in] i8TrimVal specifies the trimming value for LRC.
 * @retval None
 */
void CLK_LrcTrim(int8_t i8TrimVal)
{
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG8(CM_CMU->LRCTRM, i8TrimVal);
}

/**
 * @brief  Init Xtal initial structure with default value.
 * @param  [in] pstcXtalInit specifies the Parameter of XTAL.
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t CLK_XtalStructInit(stc_clock_xtal_init_t *pstcXtalInit)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcXtalInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Configure to default value */
        pstcXtalInit->u8State = CLK_XTAL_OFF;
        pstcXtalInit->u8Mode  = CLK_XTAL_MD_OSC;
        pstcXtalInit->u8Drv = CLK_XTAL_DRV_HIGH;
        pstcXtalInit->u8StableTime = CLK_XTAL_STB_2MS;
    }
    return i32Ret;
}

/**
 * @brief  XTAL initialize.
 * @param  [in] pstcXtalInit specifies the XTAL initial config.
 * @retval int32_t:
 *         - LL_OK: XTAL initial successfully.
 *         - LL_ERR_TIMEOUT: XTAL operate timeout.
 *         - LL_ERR_BUSY: XTAL is the system clock, CANNOT stop it.
 *         - LL_ERR_INVD_PARAM: NULL pointer.
 * @note   DO NOT STOP XTAL while using it as system clock.
 */
int32_t CLK_XtalInit(const stc_clock_xtal_init_t *pstcXtalInit)
{
    int32_t i32Ret;

    if (NULL == pstcXtalInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_CLK_XTAL_STATE(pstcXtalInit->u8State));
        DDL_ASSERT(IS_CLK_XTAL_DRV_MD(pstcXtalInit->u8Drv));
        DDL_ASSERT(IS_CLK_XTAL_MD(pstcXtalInit->u8Mode));
        DDL_ASSERT(IS_CLK_XTAL_STB_SEL(pstcXtalInit->u8StableTime));
        DDL_ASSERT(IS_CLK_UNLOCKED());

        WRITE_REG8(CM_CMU->XTALSTBCR, pstcXtalInit->u8StableTime);
        WRITE_REG8(CM_CMU->XTALCFGR, (0x80U | pstcXtalInit->u8Drv | pstcXtalInit->u8Mode));
        if (CLK_XTAL_ON == pstcXtalInit->u8State) {
            i32Ret = CLK_XtalCmd(ENABLE);
        } else {
            i32Ret = CLK_XtalCmd(DISABLE);
        }
    }

    return i32Ret;
}

/**
 * @brief  XTAL function enable/disable.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *         - LL_OK: XTAL operate successfully
 *         - LL_ERR_BUSY: XTAL is the system clock or as the PLL source clock, CANNOT stop it.
 *         - LL_ERR_TIMEOUT: XTAL operate timeout.
 * @note   DO NOT STOP XTAL while using it as system clock or as the PLL source clock.
 */
int32_t CLK_XtalCmd(en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (DISABLE == enNewState) {
        if (CLK_SYSCLK_SRC_XTAL == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW)) {
            i32Ret = LL_ERR_BUSY;
        } else if (CLK_PLL_SRC_XTAL == PLL_SRC) {
            /* XTAL as PLL clock source and PLL is working */
            if (0UL == PLL_EN_REG) {
                i32Ret = LL_ERR_BUSY;
            } else {
                WRITE_REG8(CM_CMU->XTALCR, CLK_XTAL_OFF);
            }
        } else {
            WRITE_REG8(CM_CMU->XTALCR, CLK_XTAL_OFF);
        }
    } else {
        WRITE_REG8(CM_CMU->XTALCR, CLK_XTAL_ON);
        i32Ret = CLK_WaitStable(CLK_STB_FLAG_XTAL, CLK_TIMEOUT);
    }

    return i32Ret;
}

/**
 * @brief  XTAL divide function enable/disable.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CLK_XtalDivCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (DISABLE == enNewState) {
        CLR_REG32_BIT(CM_CMU->XTALDIVCR, CMU_XTALDIVCR_FRADIVEN);
    } else {
        SET_REG32_BIT(CM_CMU->XTALDIVCR, CMU_XTALDIVCR_FRADIVEN);
    }
}

/**
 * @brief  Init Xtal divide initial structure with default value.
 * @param  [in] pstcXtalDivInit specifies the Parameter of XTAL.
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t CLK_XtalDivStructInit(stc_clock_xtaldiv_init_t *pstcXtalDivInit)
{
    int32_t i32Ret = LL_OK;;

    if (NULL == pstcXtalDivInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcXtalDivInit->u32State = CLK_XTALDIV_OFF;
        pstcXtalDivInit->u32Num = 0x3D09U;
        pstcXtalDivInit->u32Den = 0x40U;
    }

    return i32Ret;
}

/**
 * @brief  XTAL divide initialize.
 * @param  [in] pstcXtalDivInit specifies the XTAL initial config.
 *   @arg  u32State  : The new state of the XTAL divide.
 *   @arg  u32Num    : The numerator of XTAL divide.
 *   @arg  u32Den    : The denominator of XTAL divide.
 * @retval int32_t:
 *         - LL_OK: XTAL divide initial successfully.
 *         - LL_ERR_INVD_PARAM: NULL pointer.
 */
int32_t CLK_XtalDivInit(const stc_clock_xtaldiv_init_t *pstcXtalDivInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcXtalDivInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_CLK_UNLOCKED());
        DDL_ASSERT(IS_CLK_XTALDIV_STATE(pstcXtalDivInit->u32State));

        WRITE_REG32(CM_CMU->XTALDIVR, (uint32_t)pstcXtalDivInit->u32Num << CMU_XTALDIVR_NUMER_POS | pstcXtalDivInit->u32Den);
        WRITE_REG32(CM_CMU->XTALDIVCR, pstcXtalDivInit->u32State);
    }
    return i32Ret;
}

/**
 * @brief  XTAL status detection function enable/disable.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CLK_XtalStdCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (DISABLE == enNewState) {
        CLR_REG8_BIT(CM_CMU->XTALSTDCR, CMU_XTALSTDCR_XTALSTDE);
    } else {
        SET_REG8_BIT(CM_CMU->XTALSTDCR, CMU_XTALSTDCR_XTALSTDE);
    }
}

/**
 * @brief  Initialise the XTAL status detection.
 * @param  [in] u8State specifies the Parameter of XTALSTD.
 * @param  [in] u8ExceptionType specifies the Parameter of XTALSTD.
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t CLK_XtalStdInit(uint8_t u8State, uint8_t u8ExceptionType)
{
    int32_t i32Ret = LL_OK;

    /* Parameter valid check */
    DDL_ASSERT(IS_CLK_XTALSTD_STATE(u8State));
    DDL_ASSERT(IS_CLK_XTALSTD_EXP_TYPE(u8ExceptionType));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if ((CLK_PLL_SRC_XTAL == PLL_SRC) && (u8ExceptionType == CLK_XTALSTD_EXP_TYPE_INT)) {
        if (0UL == PLL_EN_REG) {
            /* while xtal used as PLL clock source, XTALSTD only choose reset exception */
            i32Ret = LL_ERR_INVD_PARAM;
        }
    }
    if (LL_OK == i32Ret) {
        /* Initialize XTALSTD */
        WRITE_REG8(CM_CMU->XTALSTDCR, u8State | u8ExceptionType);
    }

    return i32Ret;
}

/**
 * @brief  Set XTALSTD exception type.
 * @param  [in] u8ExceptionType specifies the XTALSTD exception type.
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t CLK_SetXtalStdExceptionType(uint8_t u8ExceptionType)
{
    int32_t i32Ret = LL_OK;

    /* Parameter valid check */
    DDL_ASSERT(IS_CLK_XTALSTD_EXP_TYPE(u8ExceptionType));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if ((CLK_PLL_SRC_XTAL == PLL_SRC) && (u8ExceptionType == CLK_XTALSTD_EXP_TYPE_INT)) {
        if (0UL == PLL_EN_REG) {
            /* while xtal used as PLL clock source, XTALSTD only choose reset exception */
            i32Ret = LL_ERR_INVD_PARAM;
        }
    }
    if (LL_OK == i32Ret) {
        /* Set exception type */
        MODIFY_REG8(CM_CMU->XTALSTDCR, CLK_XTALSTD_EXP_TYPE_MASK, u8ExceptionType);
    }

    return i32Ret;
}

/**
 * @brief  Clear the XTAL error flag.
 * @param  None
 * @retval None
 * @note   The system clock should not be XTAL before call this function.
 */
void CLK_ClearXtalStdStatus(void)
{
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (0x01U == READ_REG8(CM_CMU->XTALSTDSR)) {
        /* Clear the XTAL STD flag */
        WRITE_REG8(CM_CMU->XTALSTDSR, 0x00U);
    }
}

/**
 * @brief  Get the XTAL error flag.
 * @param  None
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t CLK_GetXtalStdStatus(void)
{
    return ((0x00U != READ_REG8(CM_CMU->XTALSTDSR)) ? SET : RESET);
}

/**
 * @brief  Init Xtal32 initial structure with default value.
 * @param  [in] pstcXtal32Init specifies the Parameter of XTAL32.
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t CLK_Xtal32StructInit(stc_clock_xtal32_init_t *pstcXtal32Init)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcXtal32Init) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Configure to default value */
        pstcXtal32Init->u8State  = CLK_XTAL32_ON;
        pstcXtal32Init->u8Drv    = CLK_XTAL32_DRV_MID;
        pstcXtal32Init->u8Filter = CLK_XTAL32_FILTER_ALL_MD;
    }

    return i32Ret;
}

/**
 * @brief  XTAL32 initialize.
 * @param  [in] pstcXtal32Init specifies the XTAL32 initial config.
 *   @arg  u8State  : The new state of the XTAL32.
 *   @arg  u8Drv    : The XTAL32 drive capacity.
 *   @arg  u8Filter : The XTAL32 noise filter on or off.
 * @retval int32_t:
 *         - LL_OK: XTAL32 initial successfully.
 *         - LL_ERR_BUSY: XTAL32 is the system clock, CANNOT stop it.
 *         - LL_ERR_INVD_PARAM: NULL pointer.
 * @note   DO NOT STOP XTAL32 while using it as system clock.
 */
int32_t CLK_Xtal32Init(const stc_clock_xtal32_init_t *pstcXtal32Init)
{
    int32_t i32Ret;

    if (NULL == pstcXtal32Init) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Parameters check */
        DDL_ASSERT(IS_CLK_XTAL32_STATE(pstcXtal32Init->u8State));
        DDL_ASSERT(IS_CLK_XTAL32_DRV_MD(pstcXtal32Init->u8Drv));
        DDL_ASSERT(IS_CLK_XTAL32_FILT_SEL(pstcXtal32Init->u8Filter));
        DDL_ASSERT(IS_CLK_UNLOCKED());

        WRITE_REG8(CM_CMU->XTAL32CFGR, pstcXtal32Init->u8Drv);
        WRITE_REG8(CM_CMU->XTAL32NFR, pstcXtal32Init->u8Filter);
        if (CLK_XTAL32_ON == pstcXtal32Init->u8State) {
            i32Ret = CLK_Xtal32Cmd(ENABLE);
        } else {
            i32Ret = CLK_Xtal32Cmd(DISABLE);
        }
    }

    return i32Ret;
}

/**
 * @brief  XTAL32 function enable/disable.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *         - LL_OK: XTAL32 operate successfully
 *         - LL_ERR_BUSY: XTAL32 is the system clock, CANNOT stop it.
 * @note   DO NOT STOP XTAL32 while using it as system clock.
 */
int32_t CLK_Xtal32Cmd(en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (DISABLE == enNewState) {
        if (CLK_SYSCLK_SRC_XTAL32 == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW)) {
            i32Ret = LL_ERR_BUSY;
        } else {
            WRITE_REG8(CM_CMU->XTAL32CR, CLK_XTAL32_OFF);
        }
    } else {
        WRITE_REG8(CM_CMU->XTAL32CR, CLK_XTAL32_ON);
        /* wait stable*/
    }
    /* wait approx. 5 * xtal32 cycle */
    DDL_DelayUS(CLK_XTAL32_TIMEOUT);

    return i32Ret;
}

/**
 * @brief  Set PLL source clock.
 * @param  [in] u32PllSrc PLL source clock.
 *   @arg  CLK_PLL_SRC_XTAL
 *   @arg  CLK_PLL_SRC_HRC
 * @retval None
 */
void CLK_SetPLLSrc(uint32_t u32PllSrc)
{
    DDL_ASSERT(IS_CLK_PLL_SRC(u32PllSrc));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    MODIFY_REG32(PLL_SRC_REG, PLL_SRC_BIT, u32PllSrc << PLL_SRC_POS);
}

/**
 * @brief  Init PLL initial structure with default value.
 * @param  [in] pstcPLLInit specifies the Parameter of PLL.
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t CLK_PLLStructInit(stc_clock_pll_init_t *pstcPLLInit)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcPLLInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Configure to default value */
        pstcPLLInit->PLLCFGR          = 0UL;
        pstcPLLInit->PLLCFGR_f.PLLSRC = CLK_PLL_SRC_XTAL;
        pstcPLLInit->PLLCFGR_f.PLLM   = CLK_PLLM_DEFAULT;
        pstcPLLInit->PLLCFGR_f.PLLN   = CLK_PLLN_DEFAULT;
        pstcPLLInit->PLLCFGR_f.PLLP   = CLK_PLLP_DEFAULT;
        pstcPLLInit->PLLCFGR_f.PLLQ   = CLK_PLLQ_DEFAULT;
        pstcPLLInit->PLLCFGR_f.PLLR   = CLK_PLLR_DEFAULT;
        pstcPLLInit->u8PLLState       = CLK_PLL_OFF;
    }
    return i32Ret;
}

/**
 * @brief  PLL initialize.
 * @param  [in] pstcPLLInit specifies the structure of PLLH initial config.
 *   @arg  u8PLLState  : The new state of the PLLH.
 *   @arg  PLLCFGR     : PLLH config.
 * @retval int32_t:
 *         - LL_OK: PLLH initial successfully
 *         - LL_ERR_TIMEOUT: PLLH initial timeout
 *         - LL_ERR_BUSY: PLLH is the source clock, CANNOT stop it.
 *         - LL_ERR_INVD_PARAM: NULL pointer
 * @note   The pll_input/PLLM (VCOIN) must between 8 ~ 24MHz.
 *         The VCOIN*PLLN (VCOOUT) is between 600 ~ 1200MHz.
 *         The PLLH frequency (VCOOUT/PLLHP_Q_R) is between 40 ~ 240MHz.
 */
int32_t CLK_PLLInit(const stc_clock_pll_init_t *pstcPLLInit)
{
    int32_t i32Ret;
#ifdef __DEBUG
    uint32_t vcoIn;
    uint32_t vcoOut;
#endif

    if (NULL == pstcPLLInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_CLK_PLL_SRC(pstcPLLInit->PLLCFGR_f.PLLSRC));
        DDL_ASSERT(IS_CLK_PLLM_DIV(pstcPLLInit->PLLCFGR_f.PLLM + 1UL));
        DDL_ASSERT(IS_CLK_PLLN_MULTI(pstcPLLInit->PLLCFGR_f.PLLN + 1UL));
        DDL_ASSERT(IS_CLK_PLLP_DIV(pstcPLLInit->PLLCFGR_f.PLLP + 1UL));
#ifdef __DEBUG
        vcoIn = ((CLK_PLL_SRC_XTAL == pstcPLLInit->PLLCFGR_f.PLLSRC ?
                  XTAL_VALUE : HRC_VALUE) / (pstcPLLInit->PLLCFGR_f.PLLM + 1UL));
        vcoOut = vcoIn * (pstcPLLInit->PLLCFGR_f.PLLN + 1UL);
        DDL_ASSERT(IS_CLK_PLL_VCO_IN(vcoIn));
        DDL_ASSERT(IS_CLK_PLL_VCO_OUT(vcoOut));
        DDL_ASSERT(IS_CLK_PLL_FREQ(vcoOut / (pstcPLLInit->PLLCFGR_f.PLLP + 1UL)));
        DDL_ASSERT(IS_CLK_PLLQ_DIV(pstcPLLInit->PLLCFGR_f.PLLQ + 1UL));
        DDL_ASSERT(IS_CLK_PLLR_DIV(pstcPLLInit->PLLCFGR_f.PLLR + 1UL));
        DDL_ASSERT(IS_CLK_PLL_FREQ(vcoOut / (pstcPLLInit->PLLCFGR_f.PLLR + 1UL)));
        DDL_ASSERT(IS_CLK_PLL_FREQ(vcoOut / (pstcPLLInit->PLLCFGR_f.PLLQ + 1UL)));
#endif /* __DEBUG */
        DDL_ASSERT(IS_CLK_PLL_STATE(pstcPLLInit->u8PLLState));
        DDL_ASSERT(IS_CLK_UNLOCKED());

        /* set PLL source in advance */
        MODIFY_REG32(PLL_SRC_REG, PLL_SRC_BIT, pstcPLLInit->PLLCFGR_f.PLLSRC << PLL_SRC_POS);
        WRITE_REG32(CM_CMU->PLLHCFGR, pstcPLLInit->PLLCFGR);
        if (CLK_PLL_ON == pstcPLLInit->u8PLLState) {
            i32Ret = CLK_PLLCmd(ENABLE);
        } else {
            i32Ret = CLK_PLLCmd(DISABLE);
        }
    }

    return i32Ret;
}

/**
 * @brief  PLL function enable/disable.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *         - LL_OK: PLL operate successfully
 *         - LL_ERR_BUSY: PLL is the system clock, CANNOT stop it.
 *         - LL_ERR_TIMEOUT: PLL operate timeout
 * @note   DO NOT STOP PLL while using it as system clock.
 */
int32_t CLK_PLLCmd(en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (DISABLE == enNewState) {
        if (CLK_SYSCLK_SRC_PLL == READ_REG8_BIT(CM_CMU->CKSWR, CMU_CKSWR_CKSW)) {
            i32Ret = LL_ERR_BUSY;
        } else {
            WRITE_REG8(PLL_EN_REG, CLK_PLL_OFF);
        }
    } else {
        if (CLK_PLL_SRC_XTAL == PLL_SRC) {
            i32Ret = CLK_WaitStable(CLK_STB_FLAG_XTAL, CLK_TIMEOUT);
        } else {
            i32Ret = CLK_WaitStable(CLK_STB_FLAG_HRC, CLK_TIMEOUT);
        }
        if (LL_OK == i32Ret) {
            WRITE_REG8(PLL_EN_REG, CLK_PLL_ON);
            i32Ret = CLK_WaitStable(CLK_STB_FLAG_PLL, CLK_TIMEOUT);
        }
    }

    return i32Ret;
}

/**
 * @brief  Selects the clock source to output on MCO pin.
 * @param  [in] u8Ch        Specifies the MCO channel. @ref CLK_MCO_Channel_Sel
 * @param  [in] u8Src       Specifies the clock source to output. @ref CLK_MCO_Clock_Source
 * @param  [in] u8Div       Specifies the MCOx prescaler. @ref CLK_MCO_Clock_Prescaler
 * @retval None
 * @note   MCO pin should be configured in alternate function 1 mode.
 */
void CLK_MCOConfig(uint8_t u8Ch, uint8_t u8Src, uint8_t u8Div)
{
    __IO uint8_t *MCOCFGRx;

    /* Check the parameters. */
    DDL_ASSERT(IS_CLK_MCO_SRC(u8Src));
    DDL_ASSERT(IS_CLK_MCO_DIV(u8Div));
    DDL_ASSERT(IS_CLK_MCO_CH(u8Ch));
    /* enable register write. */
    DDL_ASSERT(IS_CLK_UNLOCKED());

    MCOCFGRx = &(*(__IO uint8_t *)((uint32_t)&CM_CMU->MCO1CFGR + u8Ch));
    /* Config the MCO */
    MODIFY_REG8(*MCOCFGRx, (CMU_MCOCFGR_MCOSEL | CMU_MCOCFGR_MCODIV), (u8Src | u8Div));
}

/**
 * @brief  Enable or disable the MCO1 output.
 * @param  [in] u8Ch        Specifies the MCO channel. @ref CLK_MCO_Channel_Sel
 * @param  [in] enNewState  An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CLK_MCOCmd(uint8_t u8Ch, en_functional_state_t enNewState)
{
    __IO uint8_t *MCOCFGRx;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());
    DDL_ASSERT(IS_CLK_MCO_CH(u8Ch));

    MCOCFGRx = &(*(__IO uint8_t *)((uint32_t)&CM_CMU->MCO1CFGR + u8Ch));
    /* Enable or disable clock output. */
    MODIFY_REG8(*MCOCFGRx, CMU_MCOCFGR_MCOEN, (uint8_t)enNewState << CMU_MCOCFGR_MCOEN_POS);
}

/**
 * @brief  PLL/XTAL/HRC stable flag read.
 * @param  [in] u8Flag      specifies the stable flag to be read. @ref CLK_STB_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t CLK_GetStableStatus(uint8_t u8Flag)
{
    DDL_ASSERT(IS_CLK_STB_FLAG(u8Flag));

    return ((0x00U != READ_REG8_BIT(CM_CMU->OSCSTBSR, u8Flag)) ? SET : RESET);
}

/**
 * @brief  Set the system clock source.
 * @param  [in] u8Src specifies the source of system clock. @ref CLK_System_Clock_Source
 * @retval None
 */
void CLK_SetSysClockSrc(uint8_t u8Src)
{
    /* Set system clock source */
    SetSysClockSrc(u8Src);
    /* Update system clock */
    SystemCoreClockUpdate();
}

/**
 * @brief  Get bus clock frequency.
 * @param  [out] pstcClockFreq specifies the pointer to get bus frequency.
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t CLK_GetClockFreq(stc_clock_freq_t *pstcClockFreq)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcClockFreq) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        GetClockFreq(pstcClockFreq);
    }
    return i32Ret;
}

/**
 * @brief  Get bus clock frequency.
 * @param  [in] u32Clock specifies the bus clock to get frequency. @ref CLK_Bus_Clock_Sel
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: NULL pointer
 */
uint32_t CLK_GetBusClockFreq(uint32_t u32Clock)
{
    uint32_t u32ClockFreq;
    DDL_ASSERT(IS_CLK_BUS_CLK(u32Clock));

    switch (u32Clock) {
        case CLK_BUS_HCLK:
            u32ClockFreq = SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_HCLKS) >> CMU_SCFGR_HCLKS_POS);
            break;
        case CLK_BUS_PCLK1:
            u32ClockFreq = SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS);
            break;
        case CLK_BUS_PCLK4:
            u32ClockFreq = SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK4S) >> CMU_SCFGR_PCLK4S_POS);
            break;
        case CLK_BUS_PCLK3:
            u32ClockFreq = SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK3S) >> CMU_SCFGR_PCLK3S_POS);
            break;
        case CLK_BUS_EXCLK:
            u32ClockFreq = SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_EXCKS) >> CMU_SCFGR_EXCKS_POS);
            break;
        case CLK_BUS_PCLK0:
            u32ClockFreq = SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK0S) >> CMU_SCFGR_PCLK0S_POS);
            break;
        case CLK_BUS_PCLK2:
            u32ClockFreq = SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK2S) >> CMU_SCFGR_PCLK2S_POS);
            break;
        default:
            u32ClockFreq = SystemCoreClock;
            break;
    }
    return u32ClockFreq;
}

/**
 * @brief  Get PLL clock frequency.
 * @param  [out] pstcPllClkFreq specifies the pointer to get PLL frequency.
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t CLK_GetPLLClockFreq(stc_pll_clock_freq_t *pstcPllClkFreq)
{
    int32_t i32Ret = LL_OK;
    uint32_t pllin;
    uint32_t plln;
    uint32_t pllm;
    uint32_t pllp;
    uint32_t pllq;
    uint32_t pllr;

    if (NULL == pstcPllClkFreq) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pllp = (uint32_t)((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHP) >> CMU_PLLHCFGR_PLLHP_POS);
        pllq = (uint32_t)((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHQ) >> CMU_PLLHCFGR_PLLHQ_POS);
        pllr = (uint32_t)((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHR) >> CMU_PLLHCFGR_PLLHR_POS);
        plln = (uint32_t)((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHN) >> CMU_PLLHCFGR_PLLHN_POS);
        pllm = (uint32_t)((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHM) >> CMU_PLLHCFGR_PLLHM_POS);

        /* PLLHP is used as system clock. */
        if (CLK_PLL_SRC_XTAL == PLL_SRC) {
            pllin = XTAL_VALUE;
        } else {
            pllin = HRC_VALUE;
        }
        pstcPllClkFreq->u32PllVcin = (pllin / (pllm + 1UL));
        pstcPllClkFreq->u32PllVco = ((pllin / (pllm + 1UL)) * (plln + 1UL));
        pstcPllClkFreq->u32PllP = ((pllin / (pllm + 1UL)) * (plln + 1UL)) / (pllp + 1UL);
        pstcPllClkFreq->u32PllQ = ((pllin / (pllm + 1UL)) * (plln + 1UL)) / (pllq + 1UL);
        pstcPllClkFreq->u32PllR = ((pllin / (pllm + 1UL)) * (plln + 1UL)) / (pllr + 1UL);
    }
    return i32Ret;
}

/**
 * @brief  HCLK/PCLK divide setting.
 * @param  [in] u32Clock specifies the clock to be divided.  @ref CLK_Bus_Clock_Sel
 * @param  [in] u32Div specifies the clock divide factor. @ref CLK_Clock_Divider
 * @retval None
 * @note   u32Div could choose CLK_HCLK_Divider, CLK_PCLK0_Divider, CLK_PCLK1_Divider,
 * CLK_PCLK2_Divider, CLK_PCLK3_Divider, CLK_PCLK4_Divider, CLK_EXCLK_Divider, according to the MCU
 */
void CLK_SetClockDiv(uint32_t u32Clock, uint32_t u32Div)
{
    /* Set clock divider */
    SetSysClockDiv(u32Clock, u32Div);
    /* Update system clock */
    SystemCoreClockUpdate();
}

/**
 * @brief  Set peripheral clock source.
 * @param  [in] u16Src specifies the peripheral clock source. @ref CLK_PERIPH_Sel
 * @retval None
 */
void CLK_SetPeriClockSrc(uint16_t u16Src)
{
    DDL_ASSERT(IS_CLK_PERIPHCLK_SRC(u16Src));
    DDL_ASSERT(IS_CLK_UNLOCKED());
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG8(CM_CMU->PERICKSEL, u16Src);
}

/**
 * @brief  CAN clock source config.
 * @param  [in] u8Unit specifies the CAN channel for clock source. @ref CLK_CAN_Sel
 * @param  [in] u8Src specifies the CAN clock source. @ref CLK_CANCLK_Sel
 * @retval None
 */
void CLK_SetCANClockSrc(uint8_t u8Unit, uint8_t u8Src)
{
    uint32_t u32UnitPos = 0UL;

    DDL_ASSERT(IS_CLK_CAN_UNIT(u8Unit));
    DDL_ASSERT(IS_CLK_CANCLK(u8Src));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    while (0UL != u8Unit) {
        if (0UL != (u8Unit & 0x1UL)) {
            MODIFY_REG16(CM_CMU->CANCKCFGR, (uint32_t)CMU_CANCKCFGR_MCAN1CKS << u32UnitPos, (uint32_t)u8Src << u32UnitPos);
        }
        u8Unit >>= 1UL;
        u32UnitPos += 4U;
    }
}

/**
 * @brief  Enable or disable the TPIU clock.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CLK_TpiuClockCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    MODIFY_REG8(CM_CMU->TPIUCKCFGR, CMU_TPIUCKCFGR_TPIUCKOE, (uint8_t)enNewState << CMU_TPIUCKCFGR_TPIUCKOE_POS);
}

/**
 * @brief  TPIU clock divider config.
 * @param  [in] u8Div specifies the TPIU clock divide factor. @ref CLK_TPIU_Divider
 *   @arg  CLK_TPIUCLK_DIV1: TPIU clock no divide
 *   @arg  CLK_TPIUCLK_DIV2: TPIU clock divide by 2
 *   @arg  CLK_TPIUCLK_DIV4: TPIU clock divide by 4
 * @retval None
 */
void CLK_SetTpiuClockDiv(uint8_t u8Div)
{
    DDL_ASSERT(IS_CLK_TPIUCLK_DIV(u8Div));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    MODIFY_REG8(CM_CMU->TPIUCKCFGR, CMU_TPIUCKCFGR_TPIUCKS, u8Div);
}
/**
 * @}
 */

#endif /* LL_CLK_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
