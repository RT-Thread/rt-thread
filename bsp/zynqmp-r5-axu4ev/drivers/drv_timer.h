#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TTC_CLK_CNTRL(hw_base)      __REG32(hw_base + 0x00)
#define TTC_CLK_CNTRL_PS_EN_MASK        0x00000001      /**< Prescale enable */
#define TTC_CLK_CNTRL_PS_VAL_MASK       0x0000001E      /**< Prescale value */
#define TTC_CLK_CNTRL_PS_VAL_SHIFT      1               /**< Prescale shift */
#define TTC_CLK_CNTRL_PS_DISABLE        16              /**< Prescale disable */
#define TTC_CLK_CNTRL_SRC_MASK          0x00000020      /**< Clock source */
#define TTC_CLK_CNTRL_EXT_EDGE_MASK     0x00000040      /**< External Clock edge */

#define TTC_CNT_CNTRL(hw_base) __REG32(hw_base + 0x0C)
#define TTC_CNT_CNTRL_DIS_MASK      0x00000001      /**< Disable the counter */
#define TTC_CNT_CNTRL_INT_MASK      0x00000002      /**< interval mode */
#define TTC_CNT_CNTRL_DECR_MASK     0x00000004      /**< Decrement mode */
#define TTC_CNT_CNTRL_MATCH_MASK    0x00000008      /**< Match mode */
#define TTC_CNT_CNTRL_RST_MASK      0x00000010      /**< Reset counter */
#define TTC_CNT_CNTRL_EN_WAVE_MASK  0x00000020      /**< Enable waveform */
#define TTC_CNT_CNTRL_POL_WAVE_MASK 0x00000040      /**< Waveform polarity */
#define TTC_CNT_CNTRL_RESET_VALUE   0x00000021      /**< Reset value */

#define TTC_COUNT_VALUE(hw_base)    __REG32(hw_base + 0x18)
#define TTC_INTERVAL_VAL(hw_base)   __REG32(hw_base + 0x24)
#define TTC_MATCH_0(hw_base)        __REG32(hw_base + 0x30)
#define TTC_MATCH_1(hw_base)        __REG32(hw_base + 0x3C)
#define TTC_MATCH_2(hw_base)        __REG32(hw_base + 0x48)

#define TTC_ISR(hw_base)            __REG32(hw_base + 0x54)
#define TTC_IXR_INTERVAL_MASK       0x00000001      /**< interval Interrupt */
#define TTC_IXR_MATCH_0_MASK        0x00000002      /**< Match 1 Interrupt */
#define TTC_IXR_MATCH_1_MASK        0x00000004      /**< Match 2 Interrupt */
#define TTC_IXR_MATCH_2_MASK        0x00000008      /**< Match 3 Interrupt */
#define TTC_IXR_CNT_OVR_MASK        0x00000010      /**< Counter Overflow */
#define TTC_IXR_ALL_MASK            0x0000001F      /**< All valid Interrupts */

#define TTC_IER(hw_base)    __REG32(hw_base + 0x60)

#ifdef __cplusplus
}
#endif

#endif