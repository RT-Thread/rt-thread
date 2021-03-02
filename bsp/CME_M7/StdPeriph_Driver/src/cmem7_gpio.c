/**
    *****************************************************************************
    * @file     cmem7_gpio.c
    *
    * @brief    CMEM7 GPIO source file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#include "cmem7_gpio.h"

#define GPIO_GROUP_GPIO_H                   (GPIO_GROUP_GPIO + 1)
#define GPIO_GROUP_GPIO_N                   (GPIO_GROUP_GPIO + 2)

#define IS_INNER_GPIO_GROUP(GROUP)  (((GROUP) == GPIO_GROUP_GPIO) || \
                                                                            ((GROUP) == GPIO_GROUP_GPIO_H) || \
                                                                            ((GROUP) == GPIO_GROUP_GPIO_N))

#define GPIO_PWM_CHANNEL_GPIO_H_9   (GPIO_PWM_CHANNEL_GPIO_31 + 1)
#define GPIO_PWM_CHANNEL_GPIO_H_19  (GPIO_PWM_CHANNEL_GPIO_31 + 2)
#define GPIO_PWM_CHANNEL_GPIO_H_20  (GPIO_PWM_CHANNEL_GPIO_31 + 3)

#define IS_INNER_GPIO_PWM_CHANNEL(CHANNEL)  (((CHANNEL) == GPIO_PWM_CHANNEL_GPIO_31) || \
                                       ((CHANNEL) == GPIO_PWM_CHANNEL_GPIO_H_9) || \
                                       ((CHANNEL) == GPIO_PWM_CHANNEL_GPIO_H_19) || \
                                       ((CHANNEL) == GPIO_PWM_CHANNEL_GPIO_H_20))
static uint32_t gpio_GetClock() {
    return SYSTEM_CLOCK_FREQ / (1 << (GLOBAL_CTRL->CLK_SEL_0_b.GPIO_CLK + 1));
}

void GPIO_Init(uint8_t Group, uint32_t PositiveTrigger) {
    assert_param(IS_GPIO_GROUP(Group));

    if (Group == GPIO_GROUP_GPIO) {
      GPIO->GPIO_POSITIVE_EDGE_INT_TRIGGER = PositiveTrigger;
    } else if (Group == GPIO_GROUP_GPIO_H) {
        GPIO->GPIO_H_POSITIVE_EDGE_INT_TRIGGER = PositiveTrigger;
    } else {
        GPIO->GPIO_N_POSITIVE_EDGE_INT_TRIGGER = PositiveTrigger;
    }
}

void GPIO_EnableOutput(uint8_t Group, uint32_t Enable) {
    assert_param(IS_GPIO_GROUP(Group));

    if (Group == GPIO_GROUP_GPIO) {
      GPIO->GPIO_OE = Enable;
    } else if (Group == GPIO_GROUP_GPIO_H) {
        GPIO->GPIO_H_OE = Enable;
    } else {
        GPIO->GPIO_N_OE = Enable;
    }
}

void GPIO_EnableInt(uint8_t Group, uint32_t Enable) {
    assert_param(IS_GPIO_GROUP(Group));

    if (Group == GPIO_GROUP_GPIO) {
      GPIO->GPIO_INT_MASK = ~Enable;
    } else if (Group == GPIO_GROUP_GPIO_H) {
        GPIO->GPIO_H_INT_MASK = ~Enable;
    } else {
        GPIO->GPIO_N_INT_MASK = ~Enable;
    }
}

uint32_t GPIO_GetIntStatus(uint8_t Group) {
    assert_param(IS_GPIO_GROUP(Group));

    if (Group == GPIO_GROUP_GPIO) {
      return GPIO->GPIO_INT_STATUS;
    } else if (Group == GPIO_GROUP_GPIO_H) {
        return GPIO->GPIO_H_INT_STATUS;
    }

    return GPIO->GPIO_N_INT_STATUS;
}

void GPIO_ClearInt(uint8_t Group, uint32_t Clear) {
    assert_param(IS_GPIO_GROUP(Group));

    if (Group == GPIO_GROUP_GPIO) {
      GPIO->GPIO_INT_STATUS = Clear;
    } else if (Group == GPIO_GROUP_GPIO_H) {
        GPIO->GPIO_H_INT_STATUS = Clear;
    } else {
        GPIO->GPIO_N_INT_STATUS = Clear;
    }
}

uint32_t GPIO_Read(uint8_t Group) {
  uint32_t data;

    assert_param(IS_GPIO_GROUP(Group));

    if (Group == GPIO_GROUP_GPIO) {
      data = GPIO->GPIO_IN;
    } else if (Group == GPIO_GROUP_GPIO_H) {
        data = GPIO->GPIO_H_IN;
    } else {
        data = GPIO->GPIO_N_IN;
    }

    return data;
}

void GPIO_Write(uint8_t Group, uint32_t Unmask, uint32_t data) {
    assert_param(IS_GPIO_GROUP(Group));

    if (Group == GPIO_GROUP_GPIO) {
        GPIO->GPIO_OUT_UNMASK = Unmask;
      GPIO->GPIO_OUT_DATA = data;
    } else if (Group == GPIO_GROUP_GPIO_H) {
        GPIO->GPIO_H_OUT_UNMASK = Unmask;
      GPIO->GPIO_H_OUT_DATA = data;
    } else {
        GPIO->GPIO_N_OUT_UNMASK = Unmask;
      GPIO->GPIO_N_OUT_DATA = data;
    }
}

void GPIO_InitPwm(uint8_t Channel, uint32_t HighLevelNanoSecond, uint32_t LowLevelNanoSecond) {
    uint16_t lowTick, highTick;

    assert_param(IS_GPIO_PWM_CHANNEL(Channel));

    lowTick = LowLevelNanoSecond * (gpio_GetClock() / 1000000) / 1000;
    highTick = HighLevelNanoSecond * (gpio_GetClock() / 1000000) / 1000;
    lowTick = (lowTick < 1) ? lowTick : lowTick - 1;
    highTick = (highTick < 1) ? highTick : highTick - 1;

    if (Channel == GPIO_PWM_CHANNEL_GPIO_31) {
        GPIO->PWM_OUT0_LEN_b.LOW_LEVEL_TICK = lowTick;
        GPIO->PWM_OUT0_LEN_b.HIGH_LEVEL_TICK = highTick;
    } else if (Channel == GPIO_PWM_CHANNEL_GPIO_H_9) {
        GPIO->PWM_OUT1_LEN_b.LOW_LEVEL_TICK = lowTick;
        GPIO->PWM_OUT1_LEN_b.HIGH_LEVEL_TICK = highTick;
    } else if (Channel == GPIO_PWM_CHANNEL_GPIO_H_19) {
        GPIO->PWM_OUT2_LEN_b.LOW_LEVEL_TICK = lowTick;
        GPIO->PWM_OUT2_LEN_b.HIGH_LEVEL_TICK = highTick;
  } else {
        GPIO->PWM_OUT3_LEN_b.LOW_LEVEL_TICK = lowTick;
        GPIO->PWM_OUT3_LEN_b.HIGH_LEVEL_TICK = highTick;
    }
}

void GPIO_EnablePwm(uint8_t Channel, BOOL Enable) {
    assert_param(IS_GPIO_PWM_CHANNEL(Channel));

    if (Channel == GPIO_PWM_CHANNEL_GPIO_31) {
        GPIO->PWM_OUT_EN_b.GPIO_31 = Enable;
        GPIO->PWM_OUT_SEL_b.GPIO_31 = Enable;
    } else if (Channel == GPIO_PWM_CHANNEL_GPIO_H_9) {
        GPIO->PWM_OUT_EN_b.GPIO_H_9 = Enable;
        GPIO->PWM_OUT_SEL_b.GPIO_H_9 = Enable;
    } else if (Channel == GPIO_PWM_CHANNEL_GPIO_H_19) {
        GPIO->PWM_OUT_EN_b.GPIO_H_19 = Enable;
    GPIO->PWM_OUT_SEL_b.GPIO_H_19 = Enable;
  } else {
        GPIO->PWM_OUT_EN_b.GPIO_H_20 = Enable;
        GPIO->PWM_OUT_SEL_b.GPIO_H_20 = Enable;
    }
}

/**
   xjf 20150324

**/
void GPIO_SetBits(uint32_t mask)
{
  static uint32_t g_GPIO_OUT_UNMASK;
  static uint32_t g_GPIO_OUT_DATA;
  static uint32_t g_GPIO_OE;

    g_GPIO_OUT_UNMASK = GPIO->GPIO_OUT_UNMASK ;
  g_GPIO_OUT_DATA   = GPIO->GPIO_OUT_DATA   ;
    g_GPIO_OE         = GPIO->GPIO_OE ;
  g_GPIO_OUT_UNMASK |=mask;
  g_GPIO_OE         |=mask;
    g_GPIO_OUT_DATA   |=mask;

    GPIO->GPIO_OUT_UNMASK =g_GPIO_OUT_UNMASK ;
  GPIO->GPIO_OUT_DATA   =g_GPIO_OUT_DATA ;
    GPIO->GPIO_OE         =g_GPIO_OE       ;
}

void GPIO_clrBits(uint32_t mask)
{
  static uint32_t g_GPIO_OUT_UNMASK;
  static uint32_t g_GPIO_OUT_DATA;
  static uint32_t g_GPIO_OE;

    g_GPIO_OUT_UNMASK = GPIO->GPIO_OUT_UNMASK ;
  g_GPIO_OUT_DATA   = GPIO->GPIO_OUT_DATA   ;
    g_GPIO_OE         = GPIO->GPIO_OE ;
  g_GPIO_OUT_UNMASK |=mask;
  g_GPIO_OE         |=mask;
    g_GPIO_OUT_DATA   &=(~ mask);

    GPIO->GPIO_OUT_UNMASK =g_GPIO_OUT_UNMASK ;
  GPIO->GPIO_OUT_DATA   =g_GPIO_OUT_DATA ;
    GPIO->GPIO_OE         =g_GPIO_OE       ;
}

uint32_t GPIO_getBits(uint32_t mask)
{
  static uint32_t g_GPIO_OUT_UNMASK;
  //static uint32_t g_GPIO_OUT_DATA;
  static uint32_t g_GPIO_OE;

    uint32_t  get_delay = 0;
    uint32_t  saved_mask;

    saved_mask=mask;

    g_GPIO_OUT_UNMASK      = GPIO->GPIO_OUT_UNMASK ;
    g_GPIO_OE              = GPIO->GPIO_OE ;
  g_GPIO_OUT_UNMASK     &=(~mask);
  g_GPIO_OE             &=(~mask);
    GPIO->GPIO_OUT_UNMASK  =g_GPIO_OUT_UNMASK ;
    GPIO->GPIO_OE          =g_GPIO_OE       ;
    for(get_delay=0;get_delay<100;get_delay++)
      {
    }
    //get_delay=(GPIO->GPIO_IN)&saved_mask;
  if(((GPIO->GPIO_IN)&saved_mask)==saved_mask)
       {
             return(1);
        }
    else
    {
            return(0);
    }

}
/**
   xjf 20150324

**/
