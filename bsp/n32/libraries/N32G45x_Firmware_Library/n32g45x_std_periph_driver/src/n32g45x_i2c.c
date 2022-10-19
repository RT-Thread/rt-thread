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
 * @file n32g45x_i2c.c
 * @author Nations
 * @version v1.0.2
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_i2c.h"
#include "n32g45x_rcc.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup I2C
 * @brief I2C driver modules
 * @{
 */

/** @addtogroup I2C_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup I2C_Private_Defines
 * @{
 */

/* I2C SPE mask */
#define CTRL1_SPEN_SET   ((uint16_t)0x0001)
#define CTRL1_SPEN_RESET ((uint16_t)0xFFFE)

/* I2C START mask */
#define CTRL1_START_SET   ((uint16_t)0x0100)
#define CTRL1_START_RESET ((uint16_t)0xFEFF)

/* I2C STOP mask */
#define CTRL1_STOP_SET   ((uint16_t)0x0200)
#define CTRL1_STOP_RESET ((uint16_t)0xFDFF)

/* I2C ACK mask */
#define CTRL1_ACK_SET   ((uint16_t)0x0400)
#define CTRL1_ACK_RESET ((uint16_t)0xFBFF)

/* I2C ENGC mask */
#define CTRL1_GCEN_SET   ((uint16_t)0x0040)
#define CTRL1_GCEN_RESET ((uint16_t)0xFFBF)

/* I2C SWRST mask */
#define CTRL1_SWRESET_SET   ((uint16_t)0x8000)
#define CTRL1_SWRESET_RESET ((uint16_t)0x7FFF)

/* I2C PEC mask */
#define CTRL1_PEC_SET   ((uint16_t)0x1000)
#define CTRL1_PEC_RESET ((uint16_t)0xEFFF)

/* I2C ENPEC mask */
#define CTRL1_PECEN_SET   ((uint16_t)0x0020)
#define CTRL1_PECEN_RESET ((uint16_t)0xFFDF)

/* I2C ENARP mask */
#define CTRL1_ARPEN_SET   ((uint16_t)0x0010)
#define CTRL1_ARPEN_RESET ((uint16_t)0xFFEF)

/* I2C NOSTRETCH mask */
#define CTRL1_NOEXTEND_SET   ((uint16_t)0x0080)
#define CTRL1_NOEXTEND_RESET ((uint16_t)0xFF7F)

/* I2C registers Masks */
#define CTRL1_CLR_MASK ((uint16_t)0xFBF5)

/* I2C DMAEN mask */
#define CTRL2_DMAEN_SET   ((uint16_t)0x0800)
#define CTRL2_DMAEN_RESET ((uint16_t)0xF7FF)

/* I2C LAST mask */
#define CTRL2_DMALAST_SET   ((uint16_t)0x1000)
#define CTRL2_DMALAST_RESET ((uint16_t)0xEFFF)

/* I2C FREQ mask */
#define CTRL2_CLKFREQ_RESET ((uint16_t)0xFFC0)

/* I2C ADD0 mask */
#define OADDR1_ADDR0_SET   ((uint16_t)0x0001)
#define OADDR1_ADDR0_RESET ((uint16_t)0xFFFE)

/* I2C ENDUAL mask */
#define OADDR2_DUALEN_SET   ((uint16_t)0x0001)
#define OADDR2_DUALEN_RESET ((uint16_t)0xFFFE)

/* I2C ADD2 mask */
#define OADDR2_ADDR2_RESET ((uint16_t)0xFF01)

/* I2C F/S mask */
#define CLKCTRL_FSMODE_SET ((uint16_t)0x8000)

/* I2C CHCFG mask */
#define CLKCTRL_CLKCTRL_SET ((uint16_t)0x0FFF)

/* I2C FLAG mask */
#define FLAG_MASK ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define INTEN_MASK ((uint32_t)0x07000000)

/**
 * @}
 */

/** @addtogroup I2C_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup I2C_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup I2C_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup I2C_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the I2Cx peripheral registers to their default reset values.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 */
void I2C_DeInit(I2C_Module* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));

    if (I2Cx == I2C1)
    {
        /* Enable I2C1 reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C1, ENABLE);
        /* Release I2C1 from reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C1, DISABLE);
    }
    else if (I2Cx == I2C2)
    {
        /* Enable I2C2 reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C2, ENABLE);
        /* Release I2C2 from reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C2, DISABLE);
    }
    else if (I2Cx == I2C3)
    {
        /* Enable I2C2 reset state */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_I2C3, ENABLE);
        /* Release I2C2 from reset state */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_I2C3, DISABLE);
    }
    else if (I2Cx == I2C4)
    {
        /* Enable I2C4 reset state */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_I2C4, ENABLE);
        /* Release I2C4 from reset state */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_I2C4, DISABLE);
    }
    else
    {

    }
}

/**
 * @brief  Initializes the I2Cx peripheral according to the specified
 *   parameters in the I2C_InitStruct.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_InitStruct pointer to a I2C_InitType structure that
 *   contains the configuration information for the specified I2C peripheral.
 */
void I2C_Init(I2C_Module* I2Cx, I2C_InitType* I2C_InitStruct)
{
    uint16_t tmpregister = 0, freqrange = 0;
    uint16_t result = 0x04;
    uint32_t pclk  = 8000000;
    RCC_ClocksType rcc_clocks;
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_CLK_SPEED(I2C_InitStruct->ClkSpeed));
    assert_param(IS_I2C_BUS_MODE(I2C_InitStruct->BusMode));
    assert_param(IS_I2C_FM_DUTY_CYCLE(I2C_InitStruct->FmDutyCycle));
    assert_param(IS_I2C_OWN_ADDR1(I2C_InitStruct->OwnAddr1));
    assert_param(IS_I2C_ACK_STATE(I2C_InitStruct->AckEnable));
    assert_param(IS_I2C_ADDR_MODE(I2C_InitStruct->AddrMode));

    /*---------------------------- I2Cx CTRL2 Configuration ------------------------*/
    /* Get the I2Cx CTRL2 value */
    tmpregister = I2Cx->CTRL2;
    /* Clear frequency FREQ[5:0] bits */
    tmpregister &= CTRL2_CLKFREQ_RESET;
    /* Get APB1/2 frequency value */
    RCC_GetClocksFreqValue(&rcc_clocks);

    if ((I2Cx == I2C1) || (I2Cx == I2C2))
    {
        pclk = rcc_clocks.Pclk1Freq;
    }
    else if ((I2Cx == I2C3) || (I2Cx == I2C4))
    {
        pclk = rcc_clocks.Pclk2Freq;
    }

    /* Set frequency bits depending on pclk1 value */
    freqrange = (uint16_t)(pclk / 1000000);
    if (freqrange > 36)
    {
        freqrange = 36;
    }
    /* Write to I2Cx CTRL2 */
    tmpregister |= freqrange;
    I2Cx->CTRL2 = tmpregister;

    /*---------------------------- I2Cx CHCFG Configuration ------------------------*/
    /* Disable the selected I2C peripheral to configure TMRISE */
    I2Cx->CTRL1 &= CTRL1_SPEN_RESET;
    /* Reset tmpregister value */
    /* Clear F/S, DUTY and CHCFG[11:0] bits */
    tmpregister = 0;

    /* Configure speed in standard mode */
    if (I2C_InitStruct->ClkSpeed <= 100000)
    {
        /* Standard mode speed calculate */
        result = (uint16_t)(pclk / (I2C_InitStruct->ClkSpeed << 1));
        /* Test if CHCFG value is under 0x4*/
        if (result < 0x04)
        {
            /* Set minimum allowed value */
            result = 0x04;
        }
        /* Set speed value for standard mode */
        tmpregister |= result;
        /* Set Maximum Rise Time for standard mode */
        I2Cx->TMRISE = freqrange + 1;
    }
    /* Configure speed in fast mode */
    else
    {
        if (I2C_InitStruct->FmDutyCycle == I2C_FMDUTYCYCLE_2)
        {
            /* Fast mode speed calculate: Tlow/Thigh = 2 */
            result = (uint16_t)(pclk / (I2C_InitStruct->ClkSpeed * 3));
        }
        else /*I2C_InitStruct->FmDutyCycle == I2C_FMDUTYCYCLE_16_9*/
        {
            /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
            result = (uint16_t)(pclk / (I2C_InitStruct->ClkSpeed * 25));
            /* Set DUTY bit */
            result |= I2C_FMDUTYCYCLE_16_9;
        }

        /* Test if CHCFG value is under 0x1*/
        if ((result & CLKCTRL_CLKCTRL_SET) == 0)
        {
            /* Set minimum allowed value */
            result |= (uint16_t)0x0001;
        }
        /* Set speed value and set F/S bit for fast mode */
        tmpregister |= (uint16_t)(result | CLKCTRL_FSMODE_SET);

        /* Set Maximum Rise Time for fast mode */
        I2Cx->TMRISE = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);
    }
    /* Write to I2Cx CHCFG */
    I2Cx->CLKCTRL = tmpregister;
    /* Enable the selected I2C peripheral */
    I2Cx->CTRL1 |= CTRL1_SPEN_SET;

    /*---------------------------- I2Cx CTRL1 Configuration ------------------------*/
    /* Get the I2Cx CTRL1 value */
    tmpregister = I2Cx->CTRL1;
    /* Clear ACK, SMBTYPE and  SMBUS bits */
    tmpregister &= CTRL1_CLR_MASK;
    /* Configure I2Cx: mode and acknowledgement */
    /* Set SMBTYPE and SMBUS bits according to BusMode value */
    /* Set ACK bit according to AckEnable value */
    tmpregister |= (uint16_t)((uint32_t)I2C_InitStruct->BusMode | I2C_InitStruct->AckEnable);
    /* Write to I2Cx CTRL1 */
    I2Cx->CTRL1 = tmpregister;

    /*---------------------------- I2Cx OADDR1 Configuration -----------------------*/
    /* Set I2Cx Own Address1 and acknowledged address */
    I2Cx->OADDR1 = (I2C_InitStruct->AddrMode | I2C_InitStruct->OwnAddr1);
}

/**
 * @brief  Fills each I2C_InitStruct member with its default value.
 * @param I2C_InitStruct pointer to an I2C_InitType structure which will be initialized.
 */
void I2C_InitStruct(I2C_InitType* I2C_InitStruct)
{
    /*---------------- Reset I2C init structure parameters values ----------------*/
    /* initialize the ClkSpeed member */
    I2C_InitStruct->ClkSpeed = 5000;
    /* Initialize the BusMode member */
    I2C_InitStruct->BusMode = I2C_BUSMODE_I2C;
    /* Initialize the FmDutyCycle member */
    I2C_InitStruct->FmDutyCycle = I2C_FMDUTYCYCLE_2;
    /* Initialize the OwnAddr1 member */
    I2C_InitStruct->OwnAddr1 = 0;
    /* Initialize the AckEnable member */
    I2C_InitStruct->AckEnable = I2C_ACKDIS;
    /* Initialize the AddrMode member */
    I2C_InitStruct->AddrMode = I2C_ADDR_MODE_7BIT;
}

/**
 * @brief  Enables or disables the specified I2C peripheral.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2Cx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_Enable(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C peripheral */
        I2Cx->CTRL1 |= CTRL1_SPEN_SET;
    }
    else
    {
        /* Disable the selected I2C peripheral */
        I2Cx->CTRL1 &= CTRL1_SPEN_RESET;
    }
}

/**
 * @brief  Enables or disables the specified I2C DMA requests.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2C DMA transfer.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_EnableDMA(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C DMA requests */
        I2Cx->CTRL2 |= CTRL2_DMAEN_SET;
    }
    else
    {
        /* Disable the selected I2C DMA requests */
        I2Cx->CTRL2 &= CTRL2_DMAEN_RESET;
    }
}

/**
 * @brief  Specifies if the next DMA transfer will be the last one.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2C DMA last transfer.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_EnableDmaLastSend(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Next DMA transfer is the last transfer */
        I2Cx->CTRL2 |= CTRL2_DMALAST_SET;
    }
    else
    {
        /* Next DMA transfer is not the last transfer */
        I2Cx->CTRL2 &= CTRL2_DMALAST_RESET;
    }
}

/**
 * @brief  Generates I2Cx communication START condition.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2C START condition generation.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_GenerateStart(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Generate a START condition */
        I2Cx->CTRL1 |= CTRL1_START_SET;
    }
    else
    {
        /* Disable the START condition generation */
        I2Cx->CTRL1 &= CTRL1_START_RESET;
    }
}

/**
 * @brief  Generates I2Cx communication STOP condition.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2C STOP condition generation.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_GenerateStop(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Generate a STOP condition */
        I2Cx->CTRL1 |= CTRL1_STOP_SET;
    }
    else
    {
        /* Disable the STOP condition generation */
        I2Cx->CTRL1 &= CTRL1_STOP_RESET;
    }
}

/**
 * @brief  Enables or disables the specified I2C acknowledge feature.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2C Acknowledgement.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_ConfigAck(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the acknowledgement */
        I2Cx->CTRL1 |= CTRL1_ACK_SET;
    }
    else
    {
        /* Disable the acknowledgement */
        I2Cx->CTRL1 &= CTRL1_ACK_RESET;
    }
}

/**
 * @brief  Configures the specified I2C own address2.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Address specifies the 7bit I2C own address2.
 */
void I2C_ConfigOwnAddr2(I2C_Module* I2Cx, uint8_t Address)
{
    uint16_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));

    /* Get the old register value */
    tmpregister = I2Cx->OADDR2;

    /* Reset I2Cx Own address2 bit [7:1] */
    tmpregister &= OADDR2_ADDR2_RESET;

    /* Set I2Cx Own address2 */
    tmpregister |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);

    /* Store the new register value */
    I2Cx->OADDR2 = tmpregister;
}

/**
 * @brief  Enables or disables the specified I2C dual addressing mode.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2C dual addressing mode.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_EnableDualAddr(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable dual addressing mode */
        I2Cx->OADDR2 |= OADDR2_DUALEN_SET;
    }
    else
    {
        /* Disable dual addressing mode */
        I2Cx->OADDR2 &= OADDR2_DUALEN_RESET;
    }
}

/**
 * @brief  Enables or disables the specified I2C general call feature.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2C General call.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_EnableGeneralCall(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable generall call */
        I2Cx->CTRL1 |= CTRL1_GCEN_SET;
    }
    else
    {
        /* Disable generall call */
        I2Cx->CTRL1 &= CTRL1_GCEN_RESET;
    }
}

/**
 * @brief  Enables or disables the specified I2C interrupts.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_IT specifies the I2C interrupts sources to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg I2C_INT_BUF Buffer interrupt mask
 *     @arg I2C_INT_EVENT Event interrupt mask
 *     @arg I2C_INT_ERR Error interrupt mask
 * @param Cmd new state of the specified I2C interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_ConfigInt(I2C_Module* I2Cx, uint16_t I2C_IT, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    assert_param(IS_I2C_CFG_INT(I2C_IT));

    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C interrupts */
        I2Cx->CTRL2 |= I2C_IT;
    }
    else
    {
        /* Disable the selected I2C interrupts */
        I2Cx->CTRL2 &= (uint16_t)~I2C_IT;
    }
}

/**
 * @brief  Sends a data byte through the I2Cx peripheral.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Data Byte to be transmitted..
 */
void I2C_SendData(I2C_Module* I2Cx, uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    /* Write in the DAT register the data to be sent */
    I2Cx->DAT = Data;
}

/**
 * @brief  Returns the most recent received data by the I2Cx peripheral.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @return The value of the received data.
 */
uint8_t I2C_RecvData(I2C_Module* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    /* Return the data in the DAT register */
    return (uint8_t)I2Cx->DAT;
}

/**
 * @brief  Transmits the address byte to select the slave device.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Address specifies the slave address which will be transmitted
 * @param I2C_Direction specifies whether the I2C device will be a
 *   Transmitter or a Receiver. This parameter can be one of the following values
 *     @arg I2C_DIRECTION_SEND Transmitter mode
 *     @arg I2C_DIRECTION_RECV Receiver mode
 */
void I2C_SendAddr7bit(I2C_Module* I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_DIRECTION(I2C_Direction));
    /* Test on the direction to set/reset the read/write bit */
    if (I2C_Direction != I2C_DIRECTION_SEND)
    {
        /* Set the address bit0 for read */
        Address |= OADDR1_ADDR0_SET;
    }
    else
    {
        /* Reset the address bit0 for write */
        Address &= OADDR1_ADDR0_RESET;
    }
    /* Send the address */
    I2Cx->DAT = Address;
}

/**
 * @brief  Reads the specified I2C register and returns its value.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_Register specifies the register to read.
 *   This parameter can be one of the following values:
 *     @arg I2C_REG_CTRL1 CTRL1 register.
 *     @arg I2C_REG_CTRL2 CTRL2 register.
 *     @arg I2C_REG_OADDR1 OADDR1 register.
 *     @arg I2C_REG_OADDR2 OADDR2 register.
 *     @arg I2C_REG_DAT DAT register.
 *     @arg I2C_REG_STS1 STS1 register.
 *     @arg I2C_REG_STS2 STS2 register.
 *     @arg I2C_REG_CLKCTRL CHCFG register.
 *     @arg I2C_REG_TMRISE TMRISE register.
 * @return The value of the read register.
 */
uint16_t I2C_GetRegister(I2C_Module* I2Cx, uint8_t I2C_Register)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_REG(I2C_Register));

    tmp = (uint32_t)I2Cx;
    tmp += I2C_Register;

    /* Return the selected register value */
    return (*(__IO uint16_t*)tmp);
}

/**
 * @brief  Enables or disables the specified I2C software reset.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2C software reset.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_EnableSoftwareReset(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Peripheral under reset */
        I2Cx->CTRL1 |= CTRL1_SWRESET_SET;
    }
    else
    {
        /* Peripheral not under reset */
        I2Cx->CTRL1 &= CTRL1_SWRESET_RESET;
    }
}

/**
 * @brief  Selects the specified I2C NACK position in master receiver mode.
 *         This function is useful in I2C Master Receiver mode when the number
 *         of data to be received is equal to 2. In this case, this function
 *         should be called (with parameter I2C_NACK_POS_NEXT) before data
 *         reception starts,as described in the 2-byte reception procedure
 *         recommended in Reference Manual in Section: Master receiver.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_NACKPosition specifies the NACK position.
 *   This parameter can be one of the following values:
 *     @arg I2C_NACK_POS_NEXT indicates that the next byte will be the last
 *          received byte.
 *     @arg I2C_NACK_POS_CURRENT indicates that current byte is the last
 *          received byte.
 *
 * @note    This function configures the same bit (POS) as I2C_ConfigPecLocation()
 *          but is intended to be used in I2C mode while I2C_ConfigPecLocation()
 *          is intended to used in SMBUS mode.
 *
 */
void I2C_ConfigNackLocation(I2C_Module* I2Cx, uint16_t I2C_NACKPosition)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_NACK_POS(I2C_NACKPosition));

    /* Check the input parameter */
    if (I2C_NACKPosition == I2C_NACK_POS_NEXT)
    {
        /* Next byte in shift register is the last received byte */
        I2Cx->CTRL1 |= I2C_NACK_POS_NEXT;
    }
    else
    {
        /* Current byte in shift register is the last received byte */
        I2Cx->CTRL1 &= I2C_NACK_POS_CURRENT;
    }
}

/**
 * @brief  Drives the SMBusAlert pin high or low for the specified I2C.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_SMBusAlert specifies SMBAlert pin level.
 *   This parameter can be one of the following values:
 *     @arg I2C_SMBALERT_LOW SMBAlert pin driven low
 *     @arg I2C_SMBALERT_HIGH SMBAlert pin driven high
 */
void I2C_ConfigSmbusAlert(I2C_Module* I2Cx, uint16_t I2C_SMBusAlert)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_SMB_ALERT(I2C_SMBusAlert));
    if (I2C_SMBusAlert == I2C_SMBALERT_LOW)
    {
        /* Drive the SMBusAlert pin Low */
        I2Cx->CTRL1 |= I2C_SMBALERT_LOW;
    }
    else
    {
        /* Drive the SMBusAlert pin High  */
        I2Cx->CTRL1 &= I2C_SMBALERT_HIGH;
    }
}

/**
 * @brief  Enables or disables the specified I2C PEC transfer.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2C PEC transmission.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_SendPEC(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C PEC transmission */
        I2Cx->CTRL1 |= CTRL1_PEC_SET;
    }
    else
    {
        /* Disable the selected I2C PEC transmission */
        I2Cx->CTRL1 &= CTRL1_PEC_RESET;
    }
}

/**
 * @brief  Selects the specified I2C PEC position.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_PECPosition specifies the PEC position.
 *   This parameter can be one of the following values:
 *     @arg I2C_PEC_POS_NEXT indicates that the next byte is PEC
 *     @arg I2C_PEC_POS_CURRENT indicates that current byte is PEC
 *
 * @note    This function configures the same bit (POS) as I2C_ConfigNackLocation()
 *          but is intended to be used in SMBUS mode while I2C_ConfigNackLocation()
 *          is intended to used in I2C mode.
 *
 */
void I2C_ConfigPecLocation(I2C_Module* I2Cx, uint16_t I2C_PECPosition)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_PEC_POS(I2C_PECPosition));
    if (I2C_PECPosition == I2C_PEC_POS_NEXT)
    {
        /* Next byte in shift register is PEC */
        I2Cx->CTRL1 |= I2C_PEC_POS_NEXT;
    }
    else
    {
        /* Current byte in shift register is PEC */
        I2Cx->CTRL1 &= I2C_PEC_POS_CURRENT;
    }
}

/**
 * @brief  Enables or disables the PEC value calculation of the transferred bytes.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2Cx PEC value calculation.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_ComputePec(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C PEC calculation */
        I2Cx->CTRL1 |= CTRL1_PECEN_SET;
    }
    else
    {
        /* Disable the selected I2C PEC calculation */
        I2Cx->CTRL1 &= CTRL1_PECEN_RESET;
    }
}

/**
 * @brief  Returns the PEC value for the specified I2C.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @return The PEC value.
 */
uint8_t I2C_GetPec(I2C_Module* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    /* Return the selected I2C PEC value */
    return ((I2Cx->STS2) >> 8);
}

/**
 * @brief  Enables or disables the specified I2C ARP.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2Cx ARP.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_EnableArp(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C ARP */
        I2Cx->CTRL1 |= CTRL1_ARPEN_SET;
    }
    else
    {
        /* Disable the selected I2C ARP */
        I2Cx->CTRL1 &= CTRL1_ARPEN_RESET;
    }
}

/**
 * @brief  Enables or disables the specified I2C Clock stretching.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param Cmd new state of the I2Cx Clock stretching.
 *   This parameter can be: ENABLE or DISABLE.
 */
void I2C_EnableExtendClk(I2C_Module* I2Cx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd == DISABLE)
    {
        /* Enable the selected I2C Clock stretching */
        I2Cx->CTRL1 |= CTRL1_NOEXTEND_SET;
    }
    else
    {
        /* Disable the selected I2C Clock stretching */
        I2Cx->CTRL1 &= CTRL1_NOEXTEND_RESET;
    }
}

/**
 * @brief  Selects the specified I2C fast mode duty cycle.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param FmDutyCycle specifies the fast mode duty cycle.
 *   This parameter can be one of the following values:
 *     @arg I2C_FMDUTYCYCLE_2 I2C fast mode Tlow/Thigh = 2
 *     @arg I2C_FMDUTYCYCLE_16_9 I2C fast mode Tlow/Thigh = 16/9
 */
void I2C_ConfigFastModeDutyCycle(I2C_Module* I2Cx, uint16_t FmDutyCycle)
{
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_FM_DUTY_CYCLE(FmDutyCycle));
    if (FmDutyCycle != I2C_FMDUTYCYCLE_16_9)
    {
        /* I2C fast mode Tlow/Thigh=2 */
        I2Cx->CLKCTRL &= I2C_FMDUTYCYCLE_2;
    }
    else
    {
        /* I2C fast mode Tlow/Thigh=16/9 */
        I2Cx->CLKCTRL |= I2C_FMDUTYCYCLE_16_9;
    }
}

/**
 * @brief
 ****************************************************************************************
 *
 *                         I2C State Monitoring Functions
 *
 ****************************************************************************************
 * This I2C driver provides three different ways for I2C state monitoring
 *  depending on the application requirements and constraints:
 *
 *
 * 1) Basic state monitoring:
 *    Using I2C_CheckEvent() function:
 *    It compares the status registers (STS1 and STS2) content to a given event
 *    (can be the combination of one or more flags).
 *    It returns SUCCESS if the current status includes the given flags
 *    and returns ERROR if one or more flags are missing in the current status.
 *    - When to use:
 *      - This function is suitable for most applications as well as for startup
 *      activity since the events are fully described in the product reference manual
 *      (RM0008).
 *      - It is also suitable for users who need to define their own events.
 *    - Limitations:
 *      - If an error occurs (ie. error flags are set besides to the monitored flags),
 *        the I2C_CheckEvent() function may return SUCCESS despite the communication
 *        hold or corrupted real state.
 *        In this case, it is advised to use error interrupts to monitor the error
 *        events and handle them in the interrupt IRQ handler.
 *
 *        @note
 *        For error management, it is advised to use the following functions:
 *          - I2C_ConfigInt() to configure and enable the error interrupts (I2C_INT_ERR).
 *          - I2Cx_ER_IRQHandler() which is called when the error interrupt occurs.
 *            Where x is the peripheral instance (I2C1, I2C2 ...)
 *          - I2C_GetFlag() or I2C_GetIntStatus() to be called into I2Cx_ER_IRQHandler()
 *            in order to determine which error occured.
 *          - I2C_ClrFlag() or I2C_ClrIntPendingBit() and/or I2C_EnableSoftwareReset()
 *            and/or I2C_GenerateStop() in order to clear the error flag and source,
 *            and return to correct communication status.
 *
 *
 *  2) Advanced state monitoring:
 *     Using the function I2C_GetLastEvent() which returns the image of both status
 *     registers in a single word (uint32_t) (Status Register 2 value is shifted left
 *     by 16 bits and concatenated to Status Register 1).
 *     - When to use:
 *       - This function is suitable for the same applications above but it allows to
 *         overcome the mentioned limitation of I2C_GetFlag() function.
 *         The returned value could be compared to events already defined in the
 *         library (n32g45x_i2c.h) or to custom values defined by user.
 *       - This function is suitable when multiple flags are monitored at the same time.
 *       - At the opposite of I2C_CheckEvent() function, this function allows user to
 *         choose when an event is accepted (when all events flags are set and no
 *         other flags are set or just when the needed flags are set like
 *         I2C_CheckEvent() function).
 *     - Limitations:
 *       - User may need to define his own events.
 *       - Same remark concerning the error management is applicable for this
 *         function if user decides to check only regular communication flags (and
 *         ignores error flags).
 *
 *
 *  3) Flag-based state monitoring:
 *     Using the function I2C_GetFlag() which simply returns the status of
 *     one single flag (ie. I2C_FLAG_RXDATNE ...).
 *     - When to use:
 *        - This function could be used for specific applications or in debug phase.
 *        - It is suitable when only one flag checking is needed (most I2C events
 *          are monitored through multiple flags).
 *     - Limitations:
 *        - When calling this function, the Status register is accessed. Some flags are
 *          cleared when the status register is accessed. So checking the status
 *          of one Flag, may clear other ones.
 *        - Function may need to be called twice or more in order to monitor one
 *          single event.
 *
 *  For detailed description of Events, please refer to section I2C_Events in
 *  n32g45x_i2c.h file.
 *
 */

/**
 * @brief  Checks whether the last I2Cx Event is equal to the one passed
 *   as parameter.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_EVENT specifies the event to be checked.
 *   This parameter can be one of the following values:
 *     @arg I2C_EVT_SLAVE_SEND_ADDR_MATCHED EV1
 *     @arg I2C_EVT_SLAVE_RECV_ADDR_MATCHED EV1
 *     @arg I2C_EVT_SLAVE_SEND_ADDR2_MATCHED EV1
 *     @arg I2C_EVT_SLAVE_RECV_ADDR2_MATCHED EV1
 *     @arg I2C_EVT_SLAVE_GCALLADDR_MATCHED EV1
 *     @arg I2C_EVT_SLAVE_DATA_RECVD EV2
 *     @arg (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_DUALFLAG)  EV2
 *     @arg (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_GCALLADDR) EV2
 *     @arg I2C_EVT_SLAVE_DATA_SENDED EV3
 *     @arg (I2C_EVT_SLAVE_DATA_SENDED | I2C_FLAG_DUALFLAG) EV3
 *     @arg (I2C_EVT_SLAVE_DATA_SENDED | I2C_FLAG_GCALLADDR) EV3
 *     @arg I2C_EVT_SLAVE_ACK_MISS EV3_2
 *     @arg I2C_EVT_SLAVE_STOP_RECVD EV4
 *     @arg I2C_EVT_MASTER_MODE_FLAG EV5
 *     @arg I2C_EVT_MASTER_TXMODE_FLAG EV6
 *     @arg I2C_EVT_MASTER_RXMODE_FLAG EV6
 *     @arg I2C_EVT_MASTER_DATA_RECVD_FLAG EV7
 *     @arg I2C_EVT_MASTER_DATA_SENDING EV8
 *     @arg I2C_EVT_MASTER_DATA_SENDED EV8_2
 *     @arg I2C_EVT_MASTER_MODE_ADDRESS10_FLAG EV9
 *
 * @note: For detailed description of Events, please refer to section
 *    I2C_Events in n32g45x_i2c.h file.
 *
 * @return An ErrorStatus enumeration value:
 * - SUCCESS: Last event is equal to the I2C_EVENT
 * - ERROR: Last event is different from the I2C_EVENT
 */
ErrorStatus I2C_CheckEvent(I2C_Module* I2Cx, uint32_t I2C_EVENT)
{
    uint32_t lastevent = 0;
    uint32_t flag1 = 0, flag2 = 0;
    ErrorStatus status = ERROR;

    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_EVT(I2C_EVENT));

    /* Read the I2Cx status register */
    flag1 = I2Cx->STS1;
    flag2 = I2Cx->STS2;
    flag2 = flag2 << 16;

    /* Get the last event value from I2C status register */
    lastevent = (flag1 | flag2) & FLAG_MASK;

    /* Check whether the last event contains the I2C_EVENT */
    if ((lastevent & I2C_EVENT) == I2C_EVENT)
    {
        /* SUCCESS: last event is equal to I2C_EVENT */
        status = SUCCESS;
    }
    else
    {
        /* ERROR: last event is different from I2C_EVENT */
        status = ERROR;
    }
    /* Return status */
    return status;
}

/**
 * @brief  Returns the last I2Cx Event.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 *
 * @note: For detailed description of Events, please refer to section
 *    I2C_Events in n32g45x_i2c.h file.
 *
 * @return The last event
 */
uint32_t I2C_GetLastEvent(I2C_Module* I2Cx)
{
    uint32_t lastevent = 0;
    uint32_t flag1 = 0, flag2 = 0;

    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));

    /* Read the I2Cx status register */
    flag1 = I2Cx->STS1;
    flag2 = I2Cx->STS2;
    flag2 = flag2 << 16;

    /* Get the last event value from I2C status register */
    lastevent = (flag1 | flag2) & FLAG_MASK;

    /* Return status */
    return lastevent;
}

/**
 * @brief  Checks whether the specified I2C flag is set or not.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg I2C_FLAG_DUALFLAG Dual flag (Slave mode)
 *     @arg I2C_FLAG_SMBHADDR SMBus host header (Slave mode)
 *     @arg I2C_FLAG_SMBDADDR SMBus default header (Slave mode)
 *     @arg I2C_FLAG_GCALLADDR General call header flag (Slave mode)
 *     @arg I2C_FLAG_TRF Transmitter/Receiver flag
 *     @arg I2C_FLAG_BUSY Bus busy flag
 *     @arg I2C_FLAG_MSMODE Master/Slave flag
 *     @arg I2C_FLAG_SMBALERT SMBus Alert flag
 *     @arg I2C_FLAG_TIMOUT Timeout or Tlow error flag
 *     @arg I2C_FLAG_PECERR PEC error in reception flag
 *     @arg I2C_FLAG_OVERRUN Overrun/Underrun flag (Slave mode)
 *     @arg I2C_FLAG_ACKFAIL Acknowledge failure flag
 *     @arg I2C_FLAG_ARLOST Arbitration lost flag (Master mode)
 *     @arg I2C_FLAG_BUSERR Bus error flag
 *     @arg I2C_FLAG_TXDATE Data register empty flag (Transmitter)
 *     @arg I2C_FLAG_RXDATNE Data register not empty (Receiver) flag
 *     @arg I2C_FLAG_STOPF Stop detection flag (Slave mode)
 *     @arg I2C_FLAG_ADDR10F 10-bit header sent flag (Master mode)
 *     @arg I2C_FLAG_BYTEF Byte transfer finished flag
 *     @arg I2C_FLAG_ADDRF Address sent flag (Master mode) "ADSL"
 *   Address matched flag (Slave mode)"ENDA"
 *     @arg I2C_FLAG_STARTBF Start bit flag (Master mode)
 * @return The new state of I2C_FLAG (SET or RESET).
 */
FlagStatus I2C_GetFlag(I2C_Module* I2Cx, uint32_t I2C_FLAG)
{
    FlagStatus bitstatus = RESET;
    __IO uint32_t i2creg = 0, i2cxbase = 0;

    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_GET_FLAG(I2C_FLAG));

    /* Get the I2Cx peripheral base address */
    i2cxbase = (uint32_t)I2Cx;

    /* Read flag register index */
    i2creg = I2C_FLAG >> 28;

    /* Get bit[23:0] of the flag */
    I2C_FLAG &= FLAG_MASK;

    if (i2creg != 0)
    {
        /* Get the I2Cx STS1 register address */
        i2cxbase += 0x14;
    }
    else
    {
        /* Flag in I2Cx STS2 Register */
        I2C_FLAG = (uint32_t)(I2C_FLAG >> 16);
        /* Get the I2Cx STS2 register address */
        i2cxbase += 0x18;
    }

    if (((*(__IO uint32_t*)i2cxbase) & I2C_FLAG) != (uint32_t)RESET)
    {
        /* I2C_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* I2C_FLAG is reset */
        bitstatus = RESET;
    }

    /* Return the I2C_FLAG status */
    return bitstatus;
}

/**
 * @brief  Clears the I2Cx's pending flags.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_FLAG specifies the flag to clear.
 *   This parameter can be any combination of the following values:
 *     @arg I2C_FLAG_SMBALERT SMBus Alert flag
 *     @arg I2C_FLAG_TIMOUT Timeout or Tlow error flag
 *     @arg I2C_FLAG_PECERR PEC error in reception flag
 *     @arg I2C_FLAG_OVERRUN Overrun/Underrun flag (Slave mode)
 *     @arg I2C_FLAG_ACKFAIL Acknowledge failure flag
 *     @arg I2C_FLAG_ARLOST Arbitration lost flag (Master mode)
 *     @arg I2C_FLAG_BUSERR Bus error flag
 *
 * @note
 *   - STOPF (STOP detection) is cleared by software sequence: a read operation
 *     to I2C_STS1 register (I2C_GetFlag()) followed by a write operation
 *     to I2C_CTRL1 register (I2C_Enable() to re-enable the I2C peripheral).
 *   - ADD10 (10-bit header sent) is cleared by software sequence: a read
 *     operation to I2C_STS1 (I2C_GetFlag()) followed by writing the
 *     second byte of the address in DAT register.
 *   - BTF (Byte Transfer Finished) is cleared by software sequence: a read
 *     operation to I2C_STS1 register (I2C_GetFlag()) followed by a
 *     read/write to I2C_DAT register (I2C_SendData()).
 *   - ADDR (Address sent) is cleared by software sequence: a read operation to
 *     I2C_STS1 register (I2C_GetFlag()) followed by a read operation to
 *     I2C_STS2 register ((void)(I2Cx->STS2)).
 *   - SB (Start Bit) is cleared software sequence: a read operation to I2C_STS1
 *     register (I2C_GetFlag()) followed by a write operation to I2C_DAT
 *     register  (I2C_SendData()).
 */
void I2C_ClrFlag(I2C_Module* I2Cx, uint32_t I2C_FLAG)
{
    uint32_t flagpos = 0;
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_CLR_FLAG(I2C_FLAG));
    /* Get the I2C flag position */
    flagpos = I2C_FLAG & FLAG_MASK;
    /* Clear the selected I2C flag */
    I2Cx->STS1 = (uint16_t)~flagpos;
}

/**
 * @brief  Checks whether the specified I2C interrupt has occurred or not.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_IT specifies the interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg I2C_INT_SMBALERT SMBus Alert flag
 *     @arg I2C_INT_TIMOUT Timeout or Tlow error flag
 *     @arg I2C_INT_PECERR PEC error in reception flag
 *     @arg I2C_INT_OVERRUN Overrun/Underrun flag (Slave mode)
 *     @arg I2C_INT_ACKFAIL Acknowledge failure flag
 *     @arg I2C_INT_ARLOST Arbitration lost flag (Master mode)
 *     @arg I2C_INT_BUSERR Bus error flag
 *     @arg I2C_INT_TXDATE Data register empty flag (Transmitter)
 *     @arg I2C_INT_RXDATNE Data register not empty (Receiver) flag
 *     @arg I2C_INT_STOPF Stop detection flag (Slave mode)
 *     @arg I2C_INT_ADDR10F 10-bit header sent flag (Master mode)
 *     @arg I2C_INT_BYTEF Byte transfer finished flag
 *     @arg I2C_INT_ADDRF Address sent flag (Master mode) "ADSL"
 *                       Address matched flag (Slave mode)"ENDAD"
 *     @arg I2C_INT_STARTBF Start bit flag (Master mode)
 * @return The new state of I2C_IT (SET or RESET).
 */
INTStatus I2C_GetIntStatus(I2C_Module* I2Cx, uint32_t I2C_IT)
{
    INTStatus bitstatus   = RESET;
    uint32_t enablestatus = 0;

    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_GET_INT(I2C_IT));

    /* Check if the interrupt source is enabled or not */
    enablestatus = (uint32_t)(((I2C_IT & INTEN_MASK) >> 16) & (I2Cx->CTRL2));

    /* Get bit[23:0] of the flag */
    I2C_IT &= FLAG_MASK;

    /* Check the status of the specified I2C flag */
    if (((I2Cx->STS1 & I2C_IT) != (uint32_t)RESET) && enablestatus)
    {
        /* I2C_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* I2C_IT is reset */
        bitstatus = RESET;
    }
    /* Return the I2C_IT status */
    return bitstatus;
}

/**
 * @brief  Clears the I2Cx's interrupt pending bits.
 * @param I2Cx where x can be 1 or 2 to select the I2C peripheral.
 * @param I2C_IT specifies the interrupt pending bit to clear.
 *   This parameter can be any combination of the following values:
 *     @arg I2C_INT_SMBALERT SMBus Alert interrupt
 *     @arg I2C_INT_TIMOUT Timeout or Tlow error interrupt
 *     @arg I2C_INT_PECERR PEC error in reception  interrupt
 *     @arg I2C_INT_OVERRUN Overrun/Underrun interrupt (Slave mode)
 *     @arg I2C_INT_ACKFAIL Acknowledge failure interrupt
 *     @arg I2C_INT_ARLOST Arbitration lost interrupt (Master mode)
 *     @arg I2C_INT_BUSERR Bus error interrupt
 *
 * @note
 *   - STOPF (STOP detection) is cleared by software sequence: a read operation
 *     to I2C_STS1 register (I2C_GetIntStatus()) followed by a write operation to
 *     I2C_CTRL1 register (I2C_Enable() to re-enable the I2C peripheral).
 *   - ADD10 (10-bit header sent) is cleared by software sequence: a read
 *     operation to I2C_STS1 (I2C_GetIntStatus()) followed by writing the second
 *     byte of the address in I2C_DAT register.
 *   - BTF (Byte Transfer Finished) is cleared by software sequence: a read
 *     operation to I2C_STS1 register (I2C_GetIntStatus()) followed by a
 *     read/write to I2C_DAT register (I2C_SendData()).
 *   - ADDR (Address sent) is cleared by software sequence: a read operation to
 *     I2C_STS1 register (I2C_GetIntStatus()) followed by a read operation to
 *     I2C_STS2 register ((void)(I2Cx->STS2)).
 *   - SB (Start Bit) is cleared by software sequence: a read operation to
 *     I2C_STS1 register (I2C_GetIntStatus()) followed by a write operation to
 *     I2C_DAT register (I2C_SendData()).
 */
void I2C_ClrIntPendingBit(I2C_Module* I2Cx, uint32_t I2C_IT)
{
    uint32_t flagpos = 0;
    /* Check the parameters */
    assert_param(IS_I2C_PERIPH(I2Cx));
    assert_param(IS_I2C_CLR_INT(I2C_IT));
    /* Get the I2C flag position */
    flagpos = I2C_IT & FLAG_MASK;
    /* Clear the selected I2C flag */
    I2Cx->STS1 = (uint16_t)~flagpos;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
