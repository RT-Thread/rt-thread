/**
    *****************************************************************************
    * @file     cmem7_gpio.h
    *
    * @brief    CMEM7 GPIO header file
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

#ifndef __CMEM7_GPIO_H
#define __CMEM7_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

/** @defgroup GPIO_GROUP
  * @{
  */
typedef enum {
    GPIO_GROUP_GPIO,
} GPIO_GROUP;

#define IS_GPIO_GROUP(GROUP)  (((GROUP) == GPIO_GROUP_GPIO))
/**
  * @}
  */

/** @defgroup GPIO_PWM_CHANNEL
  * @{
  */
typedef enum {
    GPIO_PWM_CHANNEL_GPIO_31,
} GPIO_PWM_CHANNEL;

#define IS_GPIO_PWM_CHANNEL(CHANNEL)  (((CHANNEL) == GPIO_PWM_CHANNEL_GPIO_31))
/**
  * @}
  */

/**
  * @brief  GPIO initialization
  * @note   This function should be called at first before any other interfaces.
    * @param[in] Group GPIO group, which is a value of @ref GPIO_GROUP
    * @param[in] PositiveTrigger Positive edge interrupt trigger if true, or negative edge
  * @retval None
    */
void GPIO_Init(uint8_t Group, uint32_t PositiveTrigger);

/**
  * @brief  Enable or disable GPIO output in the specific group.
    * @param[in] Group GPIO group, which is a value of @ref GPIO_GROUP
    * @param[in] Enable each bit indicates if the corresponding GPIO pin
    *                       in the specific GPIO group is enable or not
  * @retval None
    */
void GPIO_EnableOutput(uint8_t Group, uint32_t Enable);

/**
  * @brief  Enable or disable GPIO interrupt in the specific group.
    * @param[in] Group GPIO group, which is a value of @ref GPIO_GROUP
    * @param[in] Enable each bit indicates if the corresponding GPIO pin interrupt
    *                       in the specific GPIO group is enable or not
  * @retval None
    */
void GPIO_EnableInt(uint8_t Group, uint32_t Enable);

/**
  * @brief  Check specific interrupts are set or not
    * @param[in] Group GPIO group, which is a value of @ref GPIO_GROUP
    * @retval uint32_t each bit indicates if the corresponding GPIO pin interrupt
    *                   in the specific GPIO group is set or not
    */
uint32_t GPIO_GetIntStatus(uint8_t Group);

/**
  * @brief  Clear GPIO interrupt in the specific group.
    * @param[in] Group GPIO group, which is a value of @ref GPIO_GROUP
    * @param[in] Clear each bit indicates if the corresponding GPIO pin interrupt
    *                       in the specific GPIO group is clear or not
  * @retval None
    */
void GPIO_ClearInt(uint8_t Group, uint32_t Clear);

/**
  * @brief  Get value of each GPIO pin in the specific group
    * @param[in] Group GPIO group, which is a value of @ref GPIO_GROUP
    * @retval uint32_t each bit indicates value of the corresponding GPIO pin
    *                   in the specific GPIO group
    */
uint32_t GPIO_Read(uint8_t Group);

/**
  * @brief  Set value of each GPIO pin in the specific group
    * @param[in] Group GPIO group, which is a value of @ref GPIO_GROUP
    * @param[in] Unmask each bit indicates value of the corresponding GPIO pin
    *                        in the specific GPIO group is set or not
    * @param[in] data each bit indicates value of the corresponding GPIO pin
    *                        in the specific GPIO group to be set
  * @retval None
    */
void GPIO_Write(uint8_t Group, uint32_t Unmask, uint32_t data);

/**
  * @brief  Initialize PWM for the specific GPIO pin
    * @note     It can work before call GPIO_EnableOutput for the specific GPIO pin
    * @param[in] Channel PWM channel, which is a value of @ref GPIO_PWM_CHANNEL
    * @param[in] HighLevelNanoSecond Nanosecond which high level lasts
    * @param[in] LowLevelNanoSecond Nanosecond which low level lasts
  * @retval None
    * @see      GPIO_EnableOutput
    */
void GPIO_InitPwm(uint8_t Channel, uint32_t HighLevelNanoSecond, uint32_t LowLevelNanoSecond);

/**
  * @brief  Enable or disable GPIO PWM in the specific channel.
    *   @param[in] Channel PWM channel, which is a value of @ref GPIO_PWM_CHANNEL
    * @param[in] Enable The bit indicates if the specific channel is enable or not
  * @retval None
    */
void GPIO_EnablePwm(uint8_t Channel, BOOL Enable);



/**
  xjf 20150324

**/
void GPIO_SetBits(uint32_t mask);
void GPIO_clrBits(uint32_t mask);
uint32_t GPIO_getBits(uint32_t mask);


#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_GPIO_H */

