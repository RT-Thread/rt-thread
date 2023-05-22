/**
  ******************************************************************************
  * @file    bl808_glb_gpio.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL808_GLB_GPIO_H__
#define __BL808_GLB_GPIO_H__

#include "glb_reg.h"
#include "mm_glb_reg.h"
#include "pds_reg.h"
#include "bl808_gpio.h"
#include "bl808_hbn.h"
#include "bl808_aon.h"
#include "bl808_pds.h"
#include "bl808_common.h"
#include "bflb_sf_ctrl.h"
#include "bflb_sf_cfg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  GLB_GPIO
 *  @{
 */

/** @defgroup  GLB_GPIO_Public_Types
 *  @{
 */

/**
 *  @brief GLB GPIO interrupt control mode type definition
 */
typedef enum {
    GLB_GPIO_INT_TRIG_SYNC_FALLING_EDGE = 0,        /*!< GPIO interrupt sync mode, GPIO falling edge trigger interrupt */
    GLB_GPIO_INT_TRIG_SYNC_RISING_EDGE = 1,         /*!< GPIO interrupt sync mode, GPIO rising edge trigger interrupt */
    GLB_GPIO_INT_TRIG_SYNC_LOW_LEVEL = 2,           /*!< GPIO interrupt sync mode, GPIO low level trigger interrupt (32k 3T) */
    GLB_GPIO_INT_TRIG_SYNC_HIGH_LEVEL = 3,          /*!< GPIO interrupt sync mode, GPIO high level trigger interrupt (32k 3T) */
    GLB_GPIO_INT_TRIG_SYNC_FALLING_RISING_EDGE = 4, /*!< GPIO interrupt sync mode, GPIO falling and rising edge trigger interrupt */
    GLB_GPIO_INT_TRIG_ASYNC_FALLING_EDGE = 8,       /*!< GPIO interrupt async mode, GPIO falling edge trigger interrupt */
    GLB_GPIO_INT_TRIG_ASYNC_RISING_EDGE = 9,        /*!< GPIO interrupt async mode, GPIO rising edge trigger interrupt */
    GLB_GPIO_INT_TRIG_ASYNC_LOW_LEVEL = 10,         /*!< GPIO interrupt async mode, GPIO low level trigger interrupt (32k 3T) */
    GLB_GPIO_INT_TRIG_ASYNC_HIGH_LEVEL = 11,        /*!< GPIO interrupt async mode, GPIO high level trigger interrupt (32k 3T) */
} GLB_GPIO_INT_TRIG_Type;

/**
 *  @brief GLB GPIO FIFO interrupt type definition
 */
typedef enum {
    GLB_GPIO_FIFO_INT_FER,  /*!< GLB GPIO FIFO Underflow or Overflow interrupt */
    GLB_GPIO_FIFO_INT_FIFO, /*!< GLB GPIO FIFO ready (tx_fifo_cnt > tx_fifo_th) interrupt */
    GLB_GPIO_FIFO_INT_END,  /*!< GLB GPIO FIFO Empty interrupt */
    GLB_GPIO_FIFO_INT_ALL,  /*!< All the interrupt */
} GLB_GPIO_FIFO_INT_Type;

/**
 *  @brief GLB GPIO FIFO Timing Phase type definition
 */
typedef enum {
    GPIO_FIFO_PHASE_FIRST_HIGH, /*!< GPIO first send high level */
    GPIO_FIFO_PHASE_FIRST_LOW,  /*!< GPIO first send low level */
} GLB_GPIO_FIFO_PHASE_Type;

/**
 *  @brief GLB GPIO FIFO Idle State type definition
 */
typedef enum {
    GPIO_FIFO_IDLE_LOW,
    GPIO_FIFO_IDLE_HIGH,
} GLB_GPIO_FIFO_IDLE_Type;

/**
 *  @brief GLB GPIO FIFO Latch Mode type definition
 */
typedef enum {
    GPIO_FIFO_LATCH_WRITE,    /*!< GPIO FIFO direct write I/O */
    GPIO_FIFO_LATCH_SETCLEAR, /*!< GPIO FIFO set/clr I/O */
} GLB_GPIO_FIFO_LATCH_Type;

/**
 *  @brief GPIO interrupt configuration structure type definition
 */
typedef struct
{
    GLB_GPIO_Type gpioPin;       /*!< GPIO pin num */
    GLB_GPIO_INT_TRIG_Type trig; /*!< GPIO interrupt trig mode */
    BL_Mask_Type intMask;        /*!< GPIO interrupt mask config */
} GLB_GPIO_INT_Cfg_Type;

/**
 *  @brief UART configuration structure type definition
 */
typedef struct
{
    uint8_t code0FirstTime;              /*!< The clock num of code0 first send */
    uint8_t code1FirstTime;              /*!< The clock num of code1 first send */
    uint16_t codeTotalTime;              /*!< The total clock num of code0/1(high + low */
    GLB_GPIO_FIFO_PHASE_Type code0Phase; /*!< low or high level of code0 first send */
    GLB_GPIO_FIFO_PHASE_Type code1Phase; /*!< low or high level of code1 first send */
    GLB_GPIO_FIFO_IDLE_Type idle;        /*!< the I/O idle level */
    uint8_t fifoDmaThreshold;            /*!< FIFO threshold */
    BL_Fun_Type fifoDmaEnable;           /*!< Enable or disable DMA of GPIO */
    GLB_GPIO_FIFO_LATCH_Type latch;      /*!< Write or set/clr GPIO level */
} GLB_GPIO_FIFO_CFG_Type;

/*@} end of group GLB_GPIO_Public_Types */

/** @defgroup  GLB_GPIO_Public_Constants
 *  @{
 */

/** @defgroup  GLB_GPIO_INT_TRIG_TYPE
 *  @{
 */
#define IS_GLB_GPIO_INT_TRIG_TYPE(type) (((type) == GLB_GPIO_INT_TRIG_SYNC_FALLING_EDGE) ||         \
                                         ((type) == GLB_GPIO_INT_TRIG_SYNC_RISING_EDGE) ||          \
                                         ((type) == GLB_GPIO_INT_TRIG_SYNC_LOW_LEVEL) ||            \
                                         ((type) == GLB_GPIO_INT_TRIG_SYNC_HIGH_LEVEL) ||           \
                                         ((type) == GLB_GPIO_INT_TRIG_SYNC_FALLING_RISING_EDGE) ||  \
                                         ((type) == GLB_GPIO_INT_TRIG_ASYNC_FALLING_EDGE) ||        \
                                         ((type) == GLB_GPIO_INT_TRIG_ASYNC_RISING_EDGE) ||         \
                                         ((type) == GLB_GPIO_INT_TRIG_ASYNC_LOW_LEVEL) ||           \
                                         ((type) == GLB_GPIO_INT_TRIG_ASYNC_HIGH_LEVEL))

/** @defgroup  GLB_GPIO_INT_TRIG_TYPE
 *  @{
 */
#define IS_GLB_GPIO_FIFO_INT_TYPE(type) (((type) == GLB_GPIO_INT_FER) ||  \
                                         ((type) == GLB_GPIO_INT_FIFO) || \
                                         ((type) == GLB_GPIO_INT_END) ||  \
                                         ((type) == GLB_GPIO_FIFO_INT_ALL))

/** @defgroup  GLB_GPIO_FIFO_PHASE_TYPE
 *  @{
 */
#define IS_GLB_GPIO_FIFO_PHASE_TYPE(type) (((type) == GPIO_FIFO_HIGH_FIRST_LOW_FOLLOWED) || \
                                           ((type) == GPIO_FIFO_LOW_FIRST_HIGH_FOLLOWED))

/** @defgroup  GLB_GPIO_FIFO_PHASE_TYPE
 *  @{
 */
#define IS_GLB_GPIO_FIFO_LATCH_TYPE(type) (((type) == GPIO_FIFO_LATCH_WRITE) || \
                                           ((type) == GPIO_FIFO_LATCH_SETCLEAR))

/*@} end of group GLB_GPIO_Public_Constants */

/** @defgroup  GLB_GPIO_Public_Macros
 *  @{
 */

/*@} end of group GLB_GPIO_Public_Macros */

/** @defgroup  GLB_GPIO_Public_Functions
 *  @{
 */
/*----------*/
#ifndef BFLB_USE_HAL_DRIVER
void GPIO_INT0_IRQHandler(void);
#endif
/*----------*/
BL_Err_Type GLB_GPIO_Init(GLB_GPIO_Cfg_Type *cfg);
BL_Err_Type GLB_GPIO_Func_Init(GLB_GPIO_FUNC_Type gpioFun, GLB_GPIO_Type *pinList, uint8_t cnt);
BL_Err_Type GLB_GPIO_Input_Enable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_Embedded_Flash_Pad_Enable(void);
BL_Err_Type GLB_GPIO_Input_Disable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Output_Enable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Output_Disable(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Set_HZ(GLB_GPIO_Type gpioPin);
uint8_t GLB_GPIO_Get_Fun(GLB_GPIO_Type gpioPin);
uint32_t GLB_GPIO_Read(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Write(GLB_GPIO_Type gpioPin, uint32_t val);
BL_Err_Type GLB_GPIO_Set(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Clr(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_Int_Init(GLB_GPIO_INT_Cfg_Type *intCfg);
BL_Err_Type GLB_GPIO_IntMask(GLB_GPIO_Type gpioPin, BL_Mask_Type intMask);
BL_Sts_Type GLB_Get_GPIO_IntStatus(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_Clr_GPIO_IntStatus(GLB_GPIO_Type gpioPin);
BL_Err_Type GLB_GPIO_INT0_IRQHandler_Install(void);
BL_Err_Type GLB_GPIO_INT0_Callback_Install(GLB_GPIO_Type gpioPin, intCallback_Type *cbFun);

#ifndef BFLB_USE_HAL_DRIVER
void GPIO_FIFO_IRQHandler(void);
#endif
BL_Err_Type GLB_GPIO_Fifo_Callback_Install(GLB_GPIO_FIFO_INT_Type intType, intCallback_Type *cbFun);
BL_Err_Type GLB_GPIO_Fifo_IRQHandler_Install(void);
BL_Err_Type GLB_GPIO_Fifo_Init(GLB_GPIO_FIFO_CFG_Type *cfg);
BL_Err_Type GLB_GPIO_Fifo_Push(uint16_t *data, uint16_t len);
uint32_t GLB_GPIO_Fifo_GetCount(void);
BL_Err_Type GLB_GPIO_Fifo_Clear(void);
BL_Err_Type GLB_GPIO_Fifo_IntMask(GLB_GPIO_FIFO_INT_Type intType, BL_Mask_Type intMask);
BL_Err_Type GLB_GPIO_Fifo_IntClear(GLB_GPIO_FIFO_INT_Type intType);
BL_Sts_Type GLB_GPIO_Fifo_GetIntStatus(GLB_GPIO_FIFO_INT_Type intType);
BL_Sts_Type GLB_GPIO_Fifo_Enable(void);
BL_Sts_Type GLB_GPIO_Fifo_Disable(void);

/*@} end of group GLB_GPIO_Public_Functions */

/*@} end of group GLB_GPIO */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_GLB_GPIO_H__ */
