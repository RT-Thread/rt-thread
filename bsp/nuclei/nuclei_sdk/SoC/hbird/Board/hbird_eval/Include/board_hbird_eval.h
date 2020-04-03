// See LICENSE for license details.
#ifndef _BOARD_HBIRD_EVAL_H_
#define _BOARD_HBIRD_EVAL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "nuclei_sdk_soc.h"

#define SOC_DEBUG_UART      UART0

// Interrupt Numbers
#define SOC_BUTTON_1_IRQn           SOC_INT49_IRQn
#define SOC_BUTTON_2_IRQn           SOC_INT50_IRQn
// Interrupt Handler Definitions
#define SOC_BUTTON_1_HANDLER        eclic_irq49_handler
#define SOC_BUTTON_2_HANDLER        eclic_irq50_handler
// GPIO Bit Offset
#define SOC_LED_RED_GPIO_OFS        19
#define SOC_LED_GREEN_GPIO_OFS      21
#define SOC_LED_BLUE_GPIO_OFS       22
#define SOC_BUTTON_1_GPIO_OFS       30
#define SOC_BUTTON_2_GPIO_OFS       31

// GPIO Bit Mask
#define SOC_LED_RED_GPIO_MASK       (1<<SOC_LED_RED_GPIO_OFS)
#define SOC_LED_GREEN_GPIO_MASK     (1<<SOC_LED_GREEN_GPIO_OFS)
#define SOC_LED_BLUE_GPIO_MASK      (1<<SOC_LED_BLUE_GPIO_OFS)
#define SOC_BUTTON_1_GPIO_MASK      (1<<SOC_BUTTON_1_GPIO_OFS)
#define SOC_BUTTON_2_GPIO_MASK      (1<<SOC_BUTTON_2_GPIO_OFS)
#define SOC_BUTTON_GPIO_MASK        (SOC_BUTTON_1_GPIO_MASK | SOC_BUTTON_2_GPIO_MASK)
#define SOC_LED_GPIO_MASK           (SOC_LED_RED_GPIO_MASK | SOC_LED_GREEN_GPIO_MASK | SOC_LED_BLUE_GPIO_MASK)

#ifdef __cplusplus
}
#endif
#endif
