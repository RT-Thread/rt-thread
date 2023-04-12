/**
  ******************************************************************************
  * @file    bl808_glb_gpio.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
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

#include "bl808_clock.h"
#include "bl808_glb.h"
#include "bl808_hbn.h"
#include "bl808_pds.h"
#include "bl808_glb_gpio.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  GLB_GPIO
 *  @{
 */

/** @defgroup  GLB_GPIO_Private_Macros
 *  @{
 */
#define GLB_GPIO_INT0_NUM           (GLB_GPIO_PIN_MAX)
#define GLB_GPIO_INT0_CLEAR_TIMEOUT (32)

/*@} end of group GLB_GPIO_Private_Macros */
#define GLB_GPIO_TIMEOUT_COUNT (320 * 1000)
/** @defgroup  GLB_GPIO_Private_Types
 *  @{
 */

/*@} end of group GLB_GPIO_Private_Types */

/** @defgroup  GLB_GPIO_Private_Variables
 *  @{
 */

#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *ATTR_TCM_CONST_SECTION glbGpioInt0CbfArra[GLB_GPIO_INT0_NUM] = { NULL };

static intCallback_Type *ATTR_TCM_CONST_SECTION glbGpioFifoCbfArra[GLB_GPIO_FIFO_INT_ALL] = { NULL };
#endif

/*@} end of group GLB_GPIO_Private_Variables */

/** @defgroup  GLB_GPIO_Global_Variables
 *  @{
 */

/*@} end of group GLB_GPIO_Global_Variables */

/** @defgroup  GLB_GPIO_Private_Fun_Declaration
 *  @{
 */

/*@} end of group GLB_GPIO_Private_Fun_Declaration */

/** @defgroup  GLB_GPIO_Private_Functions
 *  @{
 */

/*@} end of group GLB_GPIO_Private_Functions */

/** @defgroup  GLB_GPIO_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  GPIO initialization
 *
 * @param  cfg: GPIO configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Init(GLB_GPIO_Cfg_Type *cfg)
{
    uint8_t gpioPin = cfg->gpioPin;
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    /* drive strength(drive) = 0  <=>  8.0mA  @ 3.3V */
    /* drive strength(drive) = 1  <=>  9.6mA  @ 3.3V */
    /* drive strength(drive) = 2  <=>  11.2mA @ 3.3V */
    /* drive strength(drive) = 3  <=>  12.8mA @ 3.3V */

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);

    /* Disable output anyway*/
    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    /* input/output, pull up/down, drive, smt, function */
    tmpVal = BL_RD_WORD(gpioCfgAddress);

    if (cfg->gpioMode != GPIO_MODE_ANALOG) {
        /* not analog mode */

        if (cfg->gpioMode == GPIO_MODE_OUTPUT) {
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);
        } else {
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);
        }

        if (cfg->pullType == GPIO_PULL_UP) {
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
        } else if (cfg->pullType == GPIO_PULL_DOWN) {
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
        }
        if (gpioPin == GLB_GPIO_PIN_40) {
            *(uint32_t *)(HBN_BASE + HBN_PAD_CTRL_0_OFFSET) &= ~(1 << 27);
        } else if (gpioPin == GLB_GPIO_PIN_41) {
            *(uint32_t *)(HBN_BASE + HBN_PAD_CTRL_0_OFFSET) &= ~(1 << 28);
        }
    } else {
        /* analog mode */

        /* clear ie && oe */
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);

        /* clear pu && pd */
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_DRV, cfg->drive);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_SMT, cfg->smtCtrl);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_FUNC_SEL, cfg->gpioFun);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_MODE, cfg->outputMode);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  init GPIO function in pin list
 *
 * @param  gpioFun: GPIO pin function
 * @param  pinList: GPIO pin list
 * @param  cnt: GPIO pin count
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Func_Init(GLB_GPIO_FUNC_Type gpioFun, GLB_GPIO_Type *pinList, uint8_t cnt)
{
    GLB_GPIO_Cfg_Type gpioCfg = {
        .gpioPin = GLB_GPIO_PIN_0,
        .gpioFun = (uint8_t)gpioFun,
        .gpioMode = GPIO_MODE_AF,
        .pullType = GPIO_PULL_UP,
        .drive = 1,
        .smtCtrl = 1
    };

    if (gpioFun == GPIO_FUN_ANALOG) {
        gpioCfg.gpioMode = GPIO_MODE_ANALOG;
    }

    for (uint8_t i = 0; i < cnt; i++) {
        gpioCfg.gpioPin = pinList[i];
        GLB_GPIO_Init(&gpioCfg);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO set input function enable
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Input_Enable(GLB_GPIO_Type gpioPin)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);

    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Embedded flash set input function enable
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_Embedded_Flash_Pad_Enable(void)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;
    uint32_t gpioPin;

    for (gpioPin = 48; gpioPin < 52; gpioPin++) {
        gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);
        tmpVal = BL_RD_WORD(gpioCfgAddress);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
        BL_WR_WORD(gpioCfgAddress, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO set input function disable
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Input_Disable(GLB_GPIO_Type gpioPin)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);

    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO set output function enable
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Output_Enable(GLB_GPIO_Type gpioPin)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);

    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO set output function disable
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Output_Disable(GLB_GPIO_Type gpioPin)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);

    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO set High-Z
 *
 * @param  gpioPin: GPIO pin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Set_HZ(GLB_GPIO_Type gpioPin)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);

    /* Disable output anyway*/
    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    /* ie=0, oe=0, drive=0, smt=0, pu=1 (pull up), pd=0, func=swgpio */
    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_DRV, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_SMT, 0);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU); /* pull up */
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_FUNC_SEL, 0xB);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get GPIO function
 *
 * @param  gpioPin: GPIO type
 *
 * @return GPIO function
 *
*******************************************************************************/
uint8_t ATTR_TCM_SECTION GLB_GPIO_Get_Fun(GLB_GPIO_Type gpioPin)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);
    tmpVal = BL_RD_WORD(gpioCfgAddress);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_FUNC_SEL);
}

/****************************************************************************/ /**
 * @brief  Read GPIO
 *
 * @param  gpioPin: GPIO type
 *
 * @return GPIO value
 *
*******************************************************************************/
uint32_t ATTR_TCM_SECTION GLB_GPIO_Read(GLB_GPIO_Type gpioPin)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);
    tmpVal = BL_RD_WORD(gpioCfgAddress);

    return BL_GET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_I) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  Write GPIO
 *
 * @param  gpioPin: GPIO type
 * @param  val: GPIO value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Write(GLB_GPIO_Type gpioPin, uint32_t val)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);
    tmpVal = BL_RD_WORD(gpioCfgAddress);

    if (val) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_O);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_O);
    }

    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  turn GPIO output high
 *
 * @param  gpioPin: GPIO type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Set(GLB_GPIO_Type gpioPin)
{
    if (gpioPin < GLB_GPIO_PIN_32) {
        BL_WR_WORD(GLB_BASE + GLB_GPIO_CFG138_OFFSET, 1 << gpioPin);
    } else {
        BL_WR_WORD(GLB_BASE + GLB_GPIO_CFG139_OFFSET, 1 << (gpioPin - GLB_GPIO_PIN_32));
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  turn GPIO output low
 *
 * @param  gpioPin: GPIO type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Clr(GLB_GPIO_Type gpioPin)
{
    if (gpioPin < GLB_GPIO_PIN_32) {
        BL_WR_WORD(GLB_BASE + GLB_GPIO_CFG140_OFFSET, 1 << gpioPin);
    } else {
        BL_WR_WORD(GLB_BASE + GLB_GPIO_CFG141_OFFSET, 1 << (gpioPin - GLB_GPIO_PIN_32));
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO interrupt initialization
 *
 * @param  intCfg: GPIO interrupt configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Int_Init(GLB_GPIO_INT_Cfg_Type *intCfg)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;
    uint32_t gpioPin = intCfg->gpioPin;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);
    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_INT_MODE_SET, intCfg->trig);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_INT_MASK, intCfg->intMask);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set GLB GPIO interrupt mask
 *
 * @param  gpioPin: GPIO type
 * @param  intMask: GPIO interrupt MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_IntMask(GLB_GPIO_Type gpioPin, BL_Mask_Type intMask)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);
    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_INT_MASK, intMask);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get GLB GPIO interrupt status
 *
 * @param  gpioPin: GPIO type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type GLB_Get_GPIO_IntStatus(GLB_GPIO_Type gpioPin)
{
    uint32_t gpioCfgAddress;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);

    return BL_GET_REG_BITS_VAL(BL_RD_WORD(gpioCfgAddress), GLB_GPIO_0_INT_STAT) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  Clear GLB GPIO interrupt status
 *
 * @param  gpioPin: GPIO type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Clr_GPIO_IntStatus(GLB_GPIO_Type gpioPin)
{
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);

    /* clr=1 */
    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_INT_CLR);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    /* clr=0 */
    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_INT_CLR);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

#ifndef BFLB_USE_HAL_DRIVER
void GPIO_FIFO_IRQHandler(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_CFG143);

    if (BL_IS_REG_BIT_SET(tmpVal, GLB_R_GPIO_TX_END_INT) && !BL_IS_REG_BIT_SET(tmpVal, GLB_CR_GPIO_TX_END_MASK)) {
        if (glbGpioFifoCbfArra[GLB_GPIO_FIFO_INT_END] != NULL) {
            glbGpioFifoCbfArra[GLB_GPIO_FIFO_INT_END]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, GLB_R_GPIO_TX_FER_INT) && !BL_IS_REG_BIT_SET(tmpVal, GLB_CR_GPIO_TX_FER_MASK)) {
        if (glbGpioFifoCbfArra[GLB_GPIO_FIFO_INT_FER] != NULL) {
            glbGpioFifoCbfArra[GLB_GPIO_FIFO_INT_FER]();
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, GLB_R_GPIO_TX_FIFO_INT) && !BL_IS_REG_BIT_SET(tmpVal, GLB_CR_GPIO_TX_FIFO_MASK)) {
        if (glbGpioFifoCbfArra[GLB_GPIO_FIFO_INT_FIFO] != NULL) {
            glbGpioFifoCbfArra[GLB_GPIO_FIFO_INT_FIFO]();
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  GPIO INT0 IRQHandler install
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_INT0_IRQHandler_Install(void)
{
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(GPIO_INT0_IRQn, GPIO_INT0_IRQHandler);
#endif

    return SUCCESS;
}

BL_Err_Type GLB_GPIO_FIFO_IRQHandler_Install(void)
{
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(GPIO_DMA_IRQn, GPIO_FIFO_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GPIO interrupt IRQ handler callback install
 *
 * @param  gpioPin: GPIO pin type
 * @param  cbFun: callback function
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type GLB_GPIO_INT0_Callback_Install(GLB_GPIO_Type gpioPin, intCallback_Type *cbFun)
{
    if (gpioPin < GLB_GPIO_PIN_MAX) {
        glbGpioInt0CbfArra[gpioPin] = cbFun;
    }

    return SUCCESS;
}
#endif
#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type GLB_GPIO_Fifo_Callback_Install(GLB_GPIO_FIFO_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_GLB_GPIO_FIFO_INT_TYPE(intType));

    glbGpioFifoCbfArra[intType] = cbFun;

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  GPIO interrupt IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void GPIO_INT0_IRQHandler(void)
{
    GLB_GPIO_Type gpioPin;
    uint32_t timeOut = 0;

    for (gpioPin = GLB_GPIO_PIN_0; gpioPin < GLB_GPIO_PIN_MAX; gpioPin++) {
        if (SET == GLB_Get_GPIO_IntStatus(gpioPin)) {
            GLB_Clr_GPIO_IntStatus(gpioPin);

            /* timeout check */
            timeOut = GLB_GPIO_INT0_CLEAR_TIMEOUT;

            do {
                timeOut--;
            } while ((SET == GLB_Get_GPIO_IntStatus(gpioPin)) && timeOut);

            if (!timeOut) {
                //MSG("WARNING: Clear GPIO interrupt status fail.\r\n");
            }

            if (glbGpioInt0CbfArra[gpioPin] != NULL) {
                /* Call the callback function */
                glbGpioInt0CbfArra[gpioPin]();
            }
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  GPIO fifo function initialization
 *
 * @param  cfg: GPIO fifo configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Fifo_Init(GLB_GPIO_FIFO_CFG_Type *cfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GLB_GPIO_FIFO_PHASE_Type(cfg->code0Phase));
    CHECK_PARAM(IS_GLB_GPIO_FIFO_PHASE_Type(cfg->code1Phase));
    CHECK_PARAM(IS_GLB_GPIO_FIFO_PHASE_Type(cfg->latch));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_CFG143);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CR_GPIO_DMA_TX_EN, cfg->fifoDmaEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CR_GPIO_TX_FIFO_TH, cfg->fifoDmaThreshold);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CR_GPIO_DMA_OUT_SEL_LATCH, cfg->latch);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CR_GPIO_DMA_PARK_VALUE, cfg->idle);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPIO_TX_FIFO_CLR);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPIO_TX_END_CLR);
    BL_WR_REG(GLB_BASE, GLB_GPIO_CFG143, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_CFG142);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CR_CODE0_HIGH_TIME, cfg->code0FirstTime);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CR_CODE1_HIGH_TIME, cfg->code1FirstTime);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CR_CODE_TOTAL_TIME, cfg->codeTotalTime);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CR_INVERT_CODE0_HIGH, cfg->code0Phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CR_INVERT_CODE1_HIGH, cfg->code1Phase);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CR_GPIO_TX_EN);
    BL_WR_REG(GLB_BASE, GLB_GPIO_CFG142, tmpVal);

    GLB_GPIO_FIFO_IRQHandler_Install();

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Push data to GPIO fifo
 *
 * @param  data: the pointer of data buffer
 * @param  len: the len of data buffer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Fifo_Push(uint16_t *data, uint16_t len)
{
    uint32_t txLen = 0;
    uint32_t timeoutCnt = GLB_GPIO_TIMEOUT_COUNT;

    while (txLen < len) {
        if (GLB_GPIO_Fifo_GetCount() > 0) {
            BL_WR_REG(GLB_BASE, GLB_GPIO_CFG144, data[txLen++]);
            timeoutCnt = GLB_GPIO_TIMEOUT_COUNT;
        } else {
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get GPIO fifo available count
 *
 * @param  None
 *
 * @return The count of available count
 *
*******************************************************************************/
uint32_t GLB_GPIO_Fifo_GetCount(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(GLB_BASE, GLB_GPIO_CFG143), GLB_GPIO_TX_FIFO_CNT);
}

/****************************************************************************/ /**
 * @brief  Clear GPIO fifo
 *
 * @param  None
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Fifo_Clear(void)
{
    BL_WR_REG(GLB_BASE, GLB_GPIO_CFG143, BL_SET_REG_BIT(BL_RD_REG(GLB_BASE, GLB_GPIO_CFG143), GLB_GPIO_TX_FIFO_CLR));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Mask or Unmask GPIO FIFO Interrupt
 *
 * @param  intType: interrupt type
 * @param  intMask: MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Fifo_IntMask(GLB_GPIO_FIFO_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GLB_GPIO_FIFO_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_CFG143);

    /* Mask or unmask certain or all interrupt */
    if (MASK == intMask) {
        switch (intType) {
            case GLB_GPIO_FIFO_INT_FER:
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CR_GPIO_TX_FER_MASK);
                break;

            case GLB_GPIO_FIFO_INT_FIFO:
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CR_GPIO_TX_FIFO_MASK);
                break;

            case GLB_GPIO_FIFO_INT_END:
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CR_GPIO_TX_END_MASK);
                break;

            case GLB_GPIO_FIFO_INT_ALL:
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CR_GPIO_TX_END_MASK);
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CR_GPIO_TX_FIFO_MASK);
                tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CR_GPIO_TX_FER_MASK);
                break;

            default:
                break;
        }
    } else {
        switch (intType) {
            case GLB_GPIO_FIFO_INT_FER:
                tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CR_GPIO_TX_FER_MASK);
                break;

            case GLB_GPIO_FIFO_INT_FIFO:
                tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CR_GPIO_TX_FIFO_MASK);
                break;

            case GLB_GPIO_FIFO_INT_END:
                tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CR_GPIO_TX_END_MASK);
                break;

            case GLB_GPIO_FIFO_INT_ALL:
                tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CR_GPIO_TX_END_MASK);
                tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CR_GPIO_TX_FIFO_MASK);
                tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CR_GPIO_TX_FER_MASK);
                break;

            default:
                break;
        }
    }

    /* Write back */
    BL_WR_REG(GLB_BASE, GLB_GPIO_CFG143, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Clear GPIO fifo interrupt
 *
 * @param  intType: interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_GPIO_Fifo_IntClear(GLB_GPIO_FIFO_INT_Type intType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GLB_GPIO_FIFO_INT_TYPE(intType));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_CFG143);

    /* Clear certain or all interrupt */
    switch (intType) {
        case GLB_GPIO_FIFO_INT_FER:
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPIO_TX_FIFO_CLR);
            break;

        case GLB_GPIO_FIFO_INT_FIFO:
            //tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPIO_TX_FIFO_CLR);
            break;

        case GLB_GPIO_FIFO_INT_END:
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPIO_TX_END_CLR);
            break;

        case GLB_GPIO_FIFO_INT_ALL:
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPIO_TX_FIFO_CLR);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPIO_TX_END_CLR);
            break;

        default:
            break;
    }

    /* Write back */
    BL_WR_REG(GLB_BASE, GLB_GPIO_CFG143, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get GPIO fifo interrupt status
 *
 * @param  intType: interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Sts_Type GLB_GPIO_Fifo_GetIntStatus(GLB_GPIO_FIFO_INT_Type intType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GLB_GPIO_FIFO_INT_TYPE(intType));

    /* Get certain or all interrupt status */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_CFG143);

    if (GLB_GPIO_FIFO_INT_ALL == intType) {
        if (BL_IS_REG_BIT_SET(tmpVal, GLB_R_GPIO_TX_END_INT) ||
            BL_IS_REG_BIT_SET(tmpVal, GLB_R_GPIO_TX_FIFO_INT) ||
            BL_IS_REG_BIT_SET(tmpVal, GLB_R_GPIO_TX_FER_INT)) {
            return SET;
        } else {
            return RESET;
        }
    } else {
        switch (intType) {
            case GLB_GPIO_FIFO_INT_FER:
                return BL_IS_REG_BIT_SET(tmpVal, GLB_R_GPIO_TX_FER_INT);

            case GLB_GPIO_FIFO_INT_FIFO:
                return BL_IS_REG_BIT_SET(tmpVal, GLB_R_GPIO_TX_FIFO_INT);

            case GLB_GPIO_FIFO_INT_END:
                return BL_IS_REG_BIT_SET(tmpVal, GLB_R_GPIO_TX_END_INT);

            default:
                return RESET;
        }
    }
}
BL_Sts_Type GLB_GPIO_Fifo_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_CFG142);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_CR_GPIO_TX_EN);
    BL_WR_REG(GLB_BASE, GLB_GPIO_CFG142, tmpVal);

    return SUCCESS;
}
BL_Sts_Type GLB_GPIO_Fifo_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_CFG142);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_CR_GPIO_TX_EN);
    BL_WR_REG(GLB_BASE, GLB_GPIO_CFG142, tmpVal);

    return SUCCESS;
}

/*@} end of group GLB_GPIO_Public_Functions */

/*@} end of group GLB_GPIO */

/*@} end of group BL808_Peripheral_Driver */
