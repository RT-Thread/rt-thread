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
 * @file n32wb452_tsc.h
 * @author Nations
 * @version v1.0.3
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32WB452_TSC_H__
#define __N32WB452_TSC_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "n32wb452.h"

/** @addtogroup N32WB452_StdPeriph_Driver
 * @{
 */

/** @addtogroup TSC
 * @{
 */

/**
 * @brief   TSC error code
 */
 typedef enum {
    TSC_ERROR_OK            = 0x00U,  /*!< No error   */
    TSC_ERROR_CLOCK         = 0x01U,  /*!< clock config error */
    TSC_ERROR_PARAMETER     = 0x02U,  /*!< parameter error */
    TSC_ERROR_HW_MODE       = 0x02U,  /*!< Exit hw mode timeout */

 }TSC_ErrorTypeDef;
 /**
  * @
  */

/**
 * @brief   TSC clock source
 */
#define TSC_CLK_SRC_LSI                 (0x00000000)            /*!< LSI*/
#define TSC_CLK_SRC_LSE                 (RCC_LSE_ENABLE)        /*!< LSE */
#define TSC_CLK_SRC_LSE_BYPASS          (RCC_LSE_BYPASS)        /*!< LSE bypass */
/**
 * @
 */


/**
 * @defgroup Detect_Period
 */
#define TSC_DET_PERIOD_8    (0x00000000U)                       /*!< DET_PERIOD[3:0] = 8/TSC_CLOCK   */
#define TSC_DET_PERIOD_16   (0x01UL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x00000001U DET_PERIOD[3:0] = 16/TSC_CLOCK  */
#define TSC_DET_PERIOD_24   (0x02UL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x00000002U DET_PERIOD[3:0] = 24/TSC_CLOCK  */
#define TSC_DET_PERIOD_32   (0x03UL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x00000003U DET_PERIOD[3:0] = 32/TSC_CLOCK(default)  */
#define TSC_DET_PERIOD_40   (0x04UL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x00000004U DET_PERIOD[3:0] = 40/TSC_CLOCK  */
#define TSC_DET_PERIOD_48   (0x05UL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x00000005U DET_PERIOD[3:0] = 48/TSC_CLOCK  */
#define TSC_DET_PERIOD_56   (0x06UL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x00000006U DET_PERIOD[3:0] = 56/TSC_CLOCK  */
#define TSC_DET_PERIOD_64   (0x07UL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x00000007U DET_PERIOD[3:0] = 64/TSC_CLOCK  */
#define TSC_DET_PERIOD_72   (0x08UL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x00000008U DET_PERIOD[3:0] = 72/TSC_CLOCK  */
#define TSC_DET_PERIOD_80   (0x09UL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x00000009U DET_PERIOD[3:0] = 80/TSC_CLOCK  */
#define TSC_DET_PERIOD_88   (0x0AUL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x0000000AU DET_PERIOD[3:0] = 88/TSC_CLOCK  */
#define TSC_DET_PERIOD_96   (0x0BUL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x0000000BU DET_PERIOD[3:0] = 96/TSC_CLOCK  */
#define TSC_DET_PERIOD_104  (0x0CUL << TSC_CTRL_DET_PERIOD_SHIFT) /*!< 0x0000000CU DET_PERIOD[3:0] = 104/TSC_CLOCK   */

#define TSC_DET_PERIOD_8_32KHZ      ((uint8_t)TSC_DET_PERIOD_8)
#define TSC_DET_PERIOD_16_32KHZ     ((uint8_t)TSC_DET_PERIOD_16)
#define TSC_DET_PERIOD_24_32KHZ     ((uint8_t)TSC_DET_PERIOD_24)
#define TSC_DET_PERIOD_32_32KHZ     ((uint8_t)TSC_DET_PERIOD_32)
#define TSC_DET_PERIOD_40_32KHZ     ((uint8_t)TSC_DET_PERIOD_40)
#define TSC_DET_PERIOD_48_32KHZ     ((uint8_t)TSC_DET_PERIOD_48)
#define TSC_DET_PERIOD_56_32KHZ     ((uint8_t)TSC_DET_PERIOD_56)
#define TSC_DET_PERIOD_64_32KHZ     ((uint8_t)TSC_DET_PERIOD_64)
#define TSC_DET_PERIOD_72_32KHZ     ((uint8_t)TSC_DET_PERIOD_72)
#define TSC_DET_PERIOD_80_32KHZ     ((uint8_t)TSC_DET_PERIOD_80)
#define TSC_DET_PERIOD_88_32KHZ     ((uint8_t)TSC_DET_PERIOD_88)
#define TSC_DET_PERIOD_96_32KHZ     ((uint8_t)TSC_DET_PERIOD_96)
#define TSC_DET_PERIOD_104_32KHZ    ((uint8_t)TSC_DET_PERIOD_104)
/**
 * @
 */

/**
 * @defgroup Detect_Filter
 */
#define TSC_DET_FILTER_1    (0x00000000U)                       /*!< DET_FILTER[3:0] = 1 sample   */
#define TSC_DET_FILTER_2    (0x01UL << TSC_CTRL_DET_FILTER_SHIFT) /*!< 0x00000010U DET_FILTER[3:0] = 2 samples */
#define TSC_DET_FILTER_3    (0x02UL << TSC_CTRL_DET_FILTER_SHIFT) /*!< 0x00000020U DET_FILTER[3:0] = 3 samples  */
#define TSC_DET_FILTER_4    (0x03UL << TSC_CTRL_DET_FILTER_SHIFT) /*!< 0x00000030U DET_FILTER[3:0] = 4 samples  */

#define TSC_HW_DET_FILTER_1     ((uint8_t)TSC_DET_FILTER_1)
#define TSC_HW_DET_FILTER_2     ((uint8_t)TSC_DET_FILTER_2)
#define TSC_HW_DET_FILTER_3     ((uint8_t)TSC_DET_FILTER_3)
#define TSC_HW_DET_FILTER_4     ((uint8_t)TSC_DET_FILTER_4)

/**
 * @
 */

/**
 * @defgroup HW_Detect_Mode
 */
#define TSC_HW_DET_MODE_DISABLE (0x00000000U)                           /*!< Hardware detect mode disable   */
#define TSC_HW_DET_MODE_ENABLE  (0x01UL << TSC_CTRL_HW_DET_MODE_SHIFT)    /*!< 0x00000040U Hardware detect mode enable */

#define TSC_HW_DET_ENABLE       TSC_HW_DET_MODE_ENABLE
/**
 * @
 */

/**
 * @defgroup Detect_Type
 */
#define TSC_DET_TYPE_MASK       (TSC_CTRL_LESS_DET_SEL_MASK|TSC_CTRL_GREAT_DET_SEL_MASK)
#define TSC_DET_TYPE_SHIFT      (TSC_CTRL_LESS_DET_SEL_SHIFT)

#define TSC_DET_TYPE_NONE       (0UL)                           /*!< 0x00000000U Disable detect */
#define TSC_DET_TYPE_LESS       (0x01UL << TSC_DET_TYPE_SHIFT)    /*!< 0x00000100U Less detect enable */
#define TSC_DET_TYPE_GREAT      (0x02UL << TSC_DET_TYPE_SHIFT)    /*!< 0x00000200U Great detect enable */
#define TSC_DET_TYPE_PERIOD     (0x03UL << TSC_DET_TYPE_SHIFT)    /*!< 0x00000300U Both great and less detct enable */
/**
 * @
 */

/**
 * @defgroup TSC_Interrupt
 */
#define TSC_IT_DET_ENABLE       (TSC_CTRL_DET_INTEN)    /*!< Enable TSC detect interrupt */
#define TSC_IT_DET_DISABLE      (0UL)                   /*!< Disable TSC detect interrupt */
/**
 * @
 */

/**
 * @defgroup TSC_Out
 */
#define TSC_OUT_PIN         (0x00000000U)                   /*!< TSC output to TSC_OUT pin */
#define TSC_OUT_TIM4_ETR    (0x1UL << TSC_CTRL_TM4_ETR_SHIFT) /*!< TSC output to TIM4 ETR */
#define TSC_OUT_TIM2_ETR    (0x2UL << TSC_CTRL_TM4_ETR_SHIFT) /*!< TSC output to TIM2 ETR and TIM2 CH1*/
/**
 * @
 */

/**
 * @defgroup TSC_Flag
 */
#define TSC_FLAG_HW         (0x1UL << TSC_CTRL_HW_DET_ST_SHIFT)       /*!< Flag of hardware detect mode */

#define TSC_FLAG_GREAT_DET  (0x1UL << TSC_STS_GREAT_DET_SHIFT)        /*!< Flag of great detect type */
#define TSC_FLAG_LESS_DET   (0x1UL << TSC_STS_LESS_DET_SHIFT)         /*!< Flag of less detect type */
#define TSC_FLAG_PERIOD_DET (TSC_FLAG_GREAT_DET|TSC_FLAG_LESS_DET)  /*!< Flag of period detect type */
/**
 * @
 */

/**
 * @defgroup TSC_SW_Detect
 */
#define TSC_SW_MODE_DISABLE (0x00000000U)                           /*!< Disable software detect mode */
#define TSC_SW_MODE_ENABLE  (0x1UL << TSC_ANA_CTRL_SW_TSC_EN_SHIFT)   /*!< Enable software detect mode */
/**
 * @
 */

/**
 * @defgroup TSC_PadOption
 */
#define TSC_PAD_INTERNAL_RES    (0x00000000U)                       /*!< Use internal resistor */
#define TSC_PAD_EXTERNAL_RES    (0x1UL << TSC_ANA_SEL_PAD_OPT_SHIFT)  /*!< Use external resistor */

#define TSC_INNER_RESIST        TSC_PAD_INTERNAL_RES

/**
 * @
 */

/**
 * @defgroup TSC_PadSpeed
 */
#define TSC_PAD_SPEED_0     (0x00000000U)                       /*!< Low speed,about 100K */
#define TSC_PAD_SPEED_1     (0x1UL << TSC_ANA_SEL_SP_OPT_SHIFT)   /*!< Middle spped */
#define TSC_PAD_SPEED_2     (0x2UL << TSC_ANA_SEL_SP_OPT_SHIFT)   /*!< Middle spped */
#define TSC_PAD_SPEED_3     (0x3UL << TSC_ANA_SEL_SP_OPT_SHIFT)   /*!< Middle spped */

#define TSC_CMP_MASK        (0x03UL) // comparator offset bit mask
#define TSC_CMP_OFFSET      TSC_ANA_SEL_SP_OPT_SHIFT // offset of comparator speed configuration
#define TSC_CMP_SPEED_0     TSC_PAD_SPEED_0 // 100KHZ~200KHZ
#define TSC_CMP_SPEED_1     TSC_PAD_SPEED_1 // 300KHZ~700KHZ
#define TSC_CMP_SPEED_2     TSC_PAD_SPEED_2 // 300KHZ~700KHZ
#define TSC_CMP_SPEED_3     TSC_PAD_SPEED_3 // 300KHZ~700KHZ

/**
 * @
 */

/**
 * @defgroup TSC_Touch_Lib
 */
#define TSC_RESIST_1M       TSC_RESR_CHN_RESIST_1M
#define TSC_RESIST_875K     TSC_RESR_CHN_RESIST_875K
#define TSC_RESIST_750K     TSC_RESR_CHN_RESIST_750K
#define TSC_RESIST_625K     TSC_RESR_CHN_RESIST_625K
#define TSC_RESIST_500K     TSC_RESR_CHN_RESIST_500K
#define TSC_RESIST_375K     TSC_RESR_CHN_RESIST_375K
#define TSC_RESIST_250K     TSC_RESR_CHN_RESIST_250K
#define TSC_RESIST_125K     TSC_RESR_CHN_RESIST_125K

#define TSC_HW_CHN_MASK             (0x00FFFFFF)
#define TSC_CHN_ADDR_WIDTH          (4)

#define TSC_HW_BASE_BITS_OFFSET     (0)
#define TSC_HW_DELTA_BITS_OFFSET    (16)

/**
 * @
 */

/**
 * @defgroup TSC_Constant
 */
#define TSC_CHN_SEL_ALL             (TSC_CHNEN_CHN_SEL_MASK)
#define MAX_TSC_HW_CHN              (24)        /*Maximum number of tsc pin*/
#define TSC_DET_MAX_CHN_COUNT       MAX_TSC_HW_CHN
#define MAX_TSC_THRESHOLD_BASE      (2047)      /*Maximum detect base value of threshold*/
#define MAX_TSC_THRESHOLD_DELTA     (255)       /*Maximum detect delta value of threshold*/
#define TSC_TIMEOUT                 (0x01000000)   /*TSC normal timeout */
/**
 * @
 */

/* TSC Exported macros -----------------------------------------------------------*/
/** @defgroup TSC_Exported_Macros
 * @{
 */

/** @brief  Enable the TSC HW detect mode
 * @param  None
 * @retval None
 */
#define __TSC_HW_ENABLE()       SET_BIT(TSC->CTRL, TSC_HW_DET_MODE_ENABLE)

/** @brief  Disable the TSC HW detect mode
 * @param  None
 * @retval None
 */
#define __TSC_HW_DISABLE()      CLEAR_BIT(TSC->CTRL, TSC_HW_DET_MODE_ENABLE)

/** @brief  Config TSC detect period for HW detect mode
 * @param  __PERIOD__  specifies the TSC detect period during HW detect mode
 *     @arg TSC_DET_PERIOD_8:  Detect period = 8/TSC_CLK
 *     @arg TSC_DET_PERIOD_16: Detect Period = 1/TSC_CLK
 *     @arg TSC_DET_PERIOD_24: Detect Period = 2/TSC_CLK
 *     @arg TSC_DET_PERIOD_32: Detect Period = 3/TSC_CLK
 *     @arg TSC_DET_PERIOD_40: Detect Period = 4/TSC_CLK
 *     @arg TSC_DET_PERIOD_48: Detect Period = 5/TSC_CLK
 *     @arg TSC_DET_PERIOD_56: Detect Period = 6/TSC_CLK
 *     @arg TSC_DET_PERIOD_64: Detect Period = 7/TSC_CLK
 *     @arg TSC_DET_PERIOD_72: Detect Period = 7/TSC_CLK
 *     @arg TSC_DET_PERIOD_80: Detect Period = 7/TSC_CLK
 *     @arg TSC_DET_PERIOD_88: Detect Period = 7/TSC_CLK
 *     @arg TSC_DET_PERIOD_96: Detect Period = 7/TSC_CLK
 *     @arg TSC_DET_PERIOD_104:Detect Period = 7/TSC_CLK
 * @retval None
 */
#define __TSC_PERIOD_CONFIG(__PERIOD__)     MODIFY_REG(TSC->CTRL, TSC_CTRL_DET_PERIOD_MASK,__PERIOD__)

/** @brief  Config TSC detect filter for HW detect mode
 * @param  __FILTER__  specifies the least usefull continuous samples during HW detect mode
 *     @arg TSC_DET_FILTER_1: Detect filter = 1 pulse
 *     @arg TSC_DET_FILTER_2: Detect filter = 2 pulse
 *     @arg TSC_DET_FILTER_3: Detect filter = 3 pulse
 *     @arg TSC_DET_FILTER_4: Detect filter = 4 pulse
 * @retval None
 */
#define __TSC_FILTER_CONFIG(__FILTER__)     MODIFY_REG(TSC->CTRL, TSC_CTRL_DET_FILTER_MASK,__FILTER__)

/** @brief  Config TSC detect type for HW detect mode,less great or both
 * @param  __TYPE__  specifies the detect type of a sample during HW detect mode
 *     @arg TSC_DET_TYPE_NONE:  Detect disable
 *     @arg TSC_DET_TYPE_LESS:  Pulse number must be greater than the threshold(basee-delta) during a sample time
 *     @arg TSC_DET_TYPE_GREAT: Pulse number must be less than the threshold(basee+delta) during a sample time
 *     @arg TSC_DET_TYPE_PERIOD:Pulse number must be greater than (basee-delta)
                                 and also be less than (basee+delta) during a sample time
 * @retval None
 */
#define __TSC_LESS_GREAT_CONFIG(__TYPE__)   MODIFY_REG(TSC->CTRL,                                           \
                                                       (TSC_CTRL_LESS_DET_SEL_MASK|TSC_CTRL_GREAT_DET_SEL_MASK),  \
                                                       __TYPE__)

/** @brief  Enable TSC interrupt
 * @param  None
 * @retval None
 */
#define __TSC_INT_ENABLE()                  SET_BIT(TSC->CTRL, TSC_IT_DET_ENABLE)

/** @brief  Disable TSC interrupt
 * @param  None
 * @retval None
 */
#define __TSC_INT_DISABLE()                  CLEAR_BIT(TSC->CTRL, TSC_IT_DET_ENABLE)

/** @brief  Config the TSC output
 * @param  __OUT__  specifies where the TSC output should go
 *     @arg TSC_OUT_PIN:      TSC output to the TSC_OUT pin
 *     @arg TSC_OUT_TIM4_ETR: TSC output to TIM4 as ETR
 *     @arg TSC_OUT_TIM2_ETR: TSC output to TIM2 as ETR
 * @retval None
 */
#define __TSC_OUT_CONFIG(__OUT__)           MODIFY_REG( TSC->CTRL,  \
                                                        (TSC_CTRL_TM4_ETR_MASK|TSC_CTRL_TM2_ETR_CH1_MASK),\
                                                        __OUT__)

/** @brief  Config the TSC channel
 * @param  __CHN__  specifies the pin of channels used for detect
 *              This parameter:bit[0:23] used,bit[24:31] must be 0
 *                  bitx: TSC channel x
 * @retval None
 */
#define __TSC_CHN_CONFIG(__CHN__)           WRITE_REG(TSC->CHNEN,  __CHN__)

/** @brief  Enable the TSC SW detect mode
 * @param  None
 * @retval None
 */
#define __TSC_SW_ENABLE()           SET_BIT(TSC->ANA_CTRL, TSC_ANA_CTRL_SW_TSC_EN)

/** @brief  Disable the TSC SW detect mode
 * @param  None
 * @retval None
 */
#define __TSC_SW_DISABLE()          CLEAR_BIT(TSC->ANA_CTRL, TSC_ANA_CTRL_SW_TSC_EN)

/** @brief  Config the detect channel number during SW detect mode
 * @param  __NUM__  specifies channel number,must be less than MAX_TSC_HW_CHN
 * @retval None
 */
#define __TSC_SW_CHN_NUM_CONFIG(__NUM__)    MODIFY_REG(TSC->ANA_CTRL, TSC_ANA_CTRL_SW_PAD_MUX_MASK,__NUM__)

/** @brief  Config the pad charge type
 * @param  __OPT__  specifies which resistor is used for charge
 *     @arg TSC_PAD_INTERNAL_RES: Internal resistor is used
 *     @arg TSC_PAD_EXTERNAL_RES: External resistor is used
 * @retval None
 */
#define __TSC_PAD_OPT_CONFIG(__OPT__)       MODIFY_REG(TSC->ANA_SEL, TSC_ANA_SEL_PAD_OPT_MASK,__OPT__)

/** @brief  Config TSC speed
 * @param  __SPEED__  specifies the TSC speed range
 *     @arg TSC_PAD_SPEED_0: Low speed
 *     @arg TSC_PAD_SPEED_1: Middle speed
 *     @arg TSC_PAD_SPEED_2: Middle speed
 *     @arg TSC_PAD_SPEED_3: High speed
 * @retval None
 */
#define __TSC_PAD_SPEED_CONFIG(__SPEED__)   MODIFY_REG(TSC->ANA_SEL, TSC_ANA_SEL_SP_OPT_MASK,__SPEED__)


/** @brief  Check if the HW detect mode is enable
 * @param  None
 * @retval Current state of HW detect mode
 */
#define __TSC_GET_HW_MODE()                 (((TSC->CTRL) & TSC_FLAG_HW) == (TSC_FLAG_HW))

/** @brief  Check the detect type during HW detect mode
 * @param  __FLAG__  specifies the flag of detect type
 *     @arg TSC_FLAG_LESS_DET:   Flag of less detect type
 *     @arg TSC_FLAG_GREAT_DET:  Flag of great detect type
 *     @arg TSC_FLAG_PERIOD_DET: Flag of priod detect type
 * @retval Current state of flag
 */
#define __TSC_GET_HW_DET_TYPE(__FLAG__)     (((TSC->STS) & (__FLAG__))==(__FLAG__))

/** @brief  Get the number of channel which is detected now
 * @param  None
 * @retval Current channel number
 */
#define __TSC_GET_CHN_NUMBER()              (((TSC->STS) & TSC_STS_CHN_NUM_MASK) >> TSC_STS_CHN_NUM_SHIFT )

/** @brief  Get the count value of pulse
 * @param  None
 * @retval Pulse count of current channel
 */
#define __TSC_GET_CHN_CNT()                 (((TSC->STS) & TSC_STS_CNT_VAL_MASK ) >> TSC_STS_CNT_VAL_SHIFT )

/** @brief  Get the base value of one channel
 * @param  __NUM__  specifies channel number,must be less than MAX_TSC_HW_CHN
 * @retval base value of the channel
 */
#define __TSC_GET_CHN_BASE(__NUM__)   ((*((&(TSC->THRHD0))+(__NUM__)) & TSC_THRHD_BASE_MASK ) >> TSC_THRHD_BASE_SHIFT)

/** @brief  Get the delta value of one channel
 * @param  __NUM__  specifies channel number,must be less than MAX_TSC_HW_CHN
 * @retval delta value of the channel
 */
#define __TSC_GET_CHN_DELTA(__NUM__)  ((*((&(TSC->THRHD0))+(__NUM__)) & TSC_THRHD_DELTA_MASK ) >> TSC_THRHD_DELTA_SHIFT )

/** @brief  Get the internal resist value of one channel
 * @param  __NUM__  specifies channel number,must be less than MAX_TSC_HW_CHN
 * @retval resist value of the channel
 */
#define __TSC_GET_CHN_RESIST(__NUM__)  (((*((&(TSC->RESR0))+((__NUM__)>>3))) >>(((__NUM__) & 0x7UL)*4)) & TSC_RESR_CHN_RESIST_MASK)

/* Private macros ------------------------------------------------------------*/
/** @defgroup TSC_Private_Macros
 * @{
 */
#define IS_TSC_DET_PERIOD(_PERIOD_)   \
        (((_PERIOD_)==TSC_DET_PERIOD_8)  ||((_PERIOD_)==TSC_DET_PERIOD_16)||((_PERIOD_)==TSC_DET_PERIOD_24)       \
        ||((_PERIOD_)==TSC_DET_PERIOD_32)||((_PERIOD_)==TSC_DET_PERIOD_40)||((_PERIOD_)==TSC_DET_PERIOD_48)     \
        ||((_PERIOD_)==TSC_DET_PERIOD_56)||((_PERIOD_)==TSC_DET_PERIOD_64)||((_PERIOD_)==TSC_DET_PERIOD_72)     \
        ||((_PERIOD_)==TSC_DET_PERIOD_80)||((_PERIOD_)==TSC_DET_PERIOD_88)||((_PERIOD_)==TSC_DET_PERIOD_96)     \
        ||((_PERIOD_)==TSC_DET_PERIOD_104)  )

#define IS_TSC_FILTER(_FILTER_)   \
        (   ((_FILTER_)==TSC_DET_FILTER_1) ||((_FILTER_)==TSC_DET_FILTER_2)\
          ||((_FILTER_)==TSC_DET_FILTER_3) ||((_FILTER_)==TSC_DET_FILTER_4) )

#define IS_TSC_DET_MODE(_MODE_)   \
        ( ((_MODE_)==TSC_HW_DETECT_MODE) ||((_MODE_)==TSC_SW_DETECT_MODE)   )

#define IS_TSC_DET_TYPE(_TYPE_)   \
        ( ((_TYPE_)==TSC_DET_TYPE_GREAT) ||((_TYPE_)==TSC_DET_TYPE_LESS)    \
        ||((_TYPE_)==TSC_DET_TYPE_PERIOD)|| ((_TYPE_)==TSC_DET_TYPE_NONE) )

#define IS_TSC_INT(_INT_)           (((_INT_)==TSC_IT_DET_ENABLE)||((_INT_)==TSC_IT_DET_DISABLE))

#define IS_TSC_OUT(_ETR_)           (((_ETR_)==TSC_OUT_PIN)||((_ETR_)==TSC_OUT_TIM2_ETR)||((_ETR_)==TSC_OUT_TIM4_ETR))

#define IS_TSC_CHN(_CHN_)           (0==((_CHN_)&(~TSC_CHNEN_CHN_SEL_MASK)))

#define IS_TSC_CHN_NUMBER(_NUM_)    ((uint32_t)(_NUM_)<MAX_TSC_HW_CHN)

#define IS_TSC_PAD_OPTION(_OPT_)    (((_OPT_)==TSC_PAD_INTERNAL_RES)||((_OPT_)==TSC_PAD_EXTERNAL_RES))

#define IS_TSC_PAD_SPEED(_SPEED_)       \
        ( ((_SPEED_)==TSC_PAD_SPEED_0)||((_SPEED_)==TSC_PAD_SPEED_1)        \
        ||((_SPEED_)==TSC_PAD_SPEED_2)||((_SPEED_)==TSC_PAD_SPEED_3)  )

#define IS_TSC_RESISTOR_VALUE(_RES_)     \
        ( ((_RES_)==TSC_RESR_CHN_RESIST_1M)  ||((_RES_)==TSC_RESR_CHN_RESIST_875K)        \
        ||((_RES_)==TSC_RESR_CHN_RESIST_750K)||((_RES_)==TSC_RESR_CHN_RESIST_625K)        \
        ||((_RES_)==TSC_RESR_CHN_RESIST_500K)||((_RES_)==TSC_RESR_CHN_RESIST_375K)        \
        ||((_RES_)==TSC_RESR_CHN_RESIST_250K)||((_RES_)==TSC_RESR_CHN_RESIST_125K)  )

#define IS_TSC_THRESHOLD_BASE(_BASE_)       ( (_BASE_)<=MAX_TSC_THRESHOLD_BASE)


#define IS_TSC_THRESHOLD_DELTA(_DELTA_)     ( (_DELTA_)<=MAX_TSC_THRESHOLD_DELTA)

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
 * @brief define tsc status type for function TSC_GetStatus
 */
#define TSC_GET_STS_CNTVALUE    0   ///< tsc count of hardware detect
#define TSC_GET_STS_LESS_DET    1   ///< tsc less flag of hardware detect
#define TSC_GET_STS_GREAT_DET   2   ///< tsc great flag  of hardware detect
#define TSC_GET_STS_CHN_NUM     3   ///< tsc chn number  of hardware detect
#define TSC_GET_STS_DET_ST      4   ///< tsc hw detect mode start status

/**
* @brief TSC Init structure definition
*/

typedef struct
{
    uint8_t TSC_DetIntEnable;   /*!< Enalbe the TSC interrupt for hardware mode.
                                    This parameter can be ENABLE or DISABLE */
    uint8_t TSC_GreatEnable;    /*!< Enable pulse count greater above threshold for single detection
                                    This parameter can be ENABLE or DISABLE */
    uint8_t TSC_LessEnable;     /*!< Enable pulse conut less than threshold for single detection
                                    This parameter can be ENABLE or DISABLE */
    uint8_t TSC_FilterCount;    /*!< Config how many detections for filter
                                    This parameter can be one value of @ref Detect_Filter */
    uint8_t TSC_DetPeriod;      /*!< Config the detect time period for single detection
                                    This parameter can be one value of @ref Detect_Period */
}TSC_InitType;

typedef struct
{
    uint16_t    TSC_Base;       /*!< base value */
    uint8_t     TSC_Delta;      /*!< offset value  */
    uint8_t     TSC_ResisValue; /*!< resistance value configuration*/
} TSC_ChnCfg;

/**
 * @brief Analog parameter configuration
 */
typedef struct
{
    uint8_t TSC_AnaoptrSpeedOption; // speed option
    uint8_t TSC_AnaoptrResisOption; // internal or external resistance option select
} TSC_AnaoCfg;

TSC_ErrorTypeDef TSC_Init(TSC_Module* TSC_Def, TSC_InitType* CtrlCfg);
TSC_ErrorTypeDef TSC_ClockConfig(uint32_t TSC_ClkSource);
TSC_ErrorTypeDef TSC_ConfigInternalResistor(TSC_Module* TSC_Def, uint32_t Channels, uint32_t res );
TSC_ErrorTypeDef TSC_ConfigThreshold(  TSC_Module* TSC_Def, uint32_t Channels, uint32_t base, uint32_t delta);
TSC_ErrorTypeDef TSC_GetChannelCfg(TSC_Module* TSC_Def, TSC_ChnCfg* ChnCfg, uint32_t Channels);

uint32_t TSC_GetStatus(TSC_Module* TSC_Def, uint32_t type);
TSC_ErrorTypeDef TSC_Cmd(TSC_Module* TSC_Def, uint32_t Channels, FunctionalState Cmd);
TSC_ErrorTypeDef TSC_SW_SwtichChn(TSC_Module* TSC_Def, uint32_t Channel, TIM_Module* TIMx, FunctionalState Cmd);
TSC_ErrorTypeDef TSC_SetAnaoCfg(TSC_Module* TSC_Def, TSC_AnaoCfg* AnaoCfg);
TSC_ErrorTypeDef TSC_SetChannelCfg(TSC_Module* TSC_Def, TSC_ChnCfg* ChnCfg, uint32_t Channels);

#ifdef __cplusplus
}
#endif

#endif /* __N32WB452_TSC_H__ */

/**
 * @}
 */

/**
 * @}
 */
