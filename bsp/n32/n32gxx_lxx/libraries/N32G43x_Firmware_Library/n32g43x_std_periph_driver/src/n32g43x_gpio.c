/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
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
 * @file n32g43x_gpio.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32g43x_gpio.h"
#include "n32g43x_rcc.h"

/** @addtogroup N32G43x_StdPeriph_Driver
 * @{
 */

/** @addtogroup GPIO
 * @brief GPIO driver modules
 * @{
 */

/** @addtogroup GPIO_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup GPIO_Private_Defines
 * @{
 */

/* ------------ RCC registers bit address in the alias region ----------------*/
#define AFIO_OFFSET (AFIO_BASE - PERIPH_BASE)

/* --- Event control register -----*/

/* Alias word address of EVOE bit */
#define EVCR_OFFSET    (AFIO_OFFSET + 0x00)
#define EVOE_BitNumber ((uint8_t)0x07)
#define EVCR_EVOE_BB   (PERIPH_BB_BASE + (EVCR_OFFSET * 32) + (EVOE_BitNumber * 4))


#define GPIO_MODE                       ((uint32_t)0x00000003)
#define EXTI_MODE                       ((uint32_t)0x10000000)
#define GPIO_MODE_IT                    ((uint32_t)0x00010000)
#define GPIO_MODE_EVT                   ((uint32_t)0x00020000)
#define RISING_EDGE                     ((uint32_t)0x00100000)
#define FALLING_EDGE                    ((uint32_t)0x00200000)
#define GPIO_OUTPUT_TYPE                ((uint32_t)0x00000010)
#define GPIO_PULLUP_PULLDOWN            ((uint32_t)0x00000300)
#define GPIO_NUMBER                     ((uint32_t)16)


/**
 * @}
 */

/** @addtogroup GPIO_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup GPIO_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup GPIO_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup GPIO_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the GPIOx peripheral registers to their default reset values.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 */
void GPIO_DeInit(GPIO_Module* GPIOx)
{

    uint32_t position = 0x00U;
    uint32_t iocurrent = 0x00U;
    uint32_t tmp = 0x00U;
    uint32_t GPIO_Pin = GPIO_PIN_ALL;
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    /* Check the parameters */
    assert_param(IS_GPIO_PIN_AVAILABLE(GPIOx,GPIO_Pin));

    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOA, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOA, DISABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOB, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOB, DISABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOC, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOC, DISABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOD, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOD, DISABLE);
    }
    else
    {
        return;
    }

    /* Configure the port pins */
    while ((GPIO_Pin >> position) != 0)
    {
        /* Get the IO position */
        iocurrent = (GPIO_Pin) & ((uint32_t)0x01 << position);

        if (iocurrent)
        {
            /*------------------------- EXTI Mode Configuration --------------------*/
            /* Clear the External Interrupt or Event for the current IO */
            tmp = AFIO->EXTI_CFG[position>>2];
            tmp &= (0x0FuL << (4u*(position & 0x03u)));
            if (tmp == (GPIO_GET_INDEX(GPIOx)<<(4u * (position & 0x03u))))
            {
                /* Clear EXTI line configuration */
                EXTI->IMASK &= ~(iocurrent);
                EXTI->EMASK &= ~(iocurrent);

                /* Clear Rising Falling edge configuration */
                EXTI->RT_CFG &= ~(iocurrent);
                EXTI->FT_CFG &= ~(iocurrent);
                tmp = 0x0FuL << (4u * (position & 0x03u));
                AFIO->EXTI_CFG[position >> 2u] &= ~tmp;
            }


            /*------------------------- GPIO Mode Configuration --------------------*/
            /* Configure IO Direction in Input Floting Mode */
            GPIOx->PMODE &= ~(GPIO_PMODE0_Msk << (position * 2U));

            /* Configure the default Alternate Function in current IO */
            if (position & 0x08)
                GPIOx->AFH |= ((uint32_t)0xF << ((uint32_t)(position & (uint32_t)0x07) * 4U));
            else
                GPIOx->AFL |= ((uint32_t)0xF << ((uint32_t)(position & (uint32_t)0x07) * 4U));

            /* Configure the default value IO Output Type */
            GPIOx->POTYPE  &= ~(GPIO_POTYPE_POT_0 << position) ;

            /* Deactivate the Pull-up oand Pull-down resistor for the current IO */
            GPIOx->PUPD &= ~(GPIO_PUPD0_Msk << (position * 2U));

        }
     position++;
    }
}


/**
 * @brief  Deinitializes the Alternate Functions (remap, event control
 *   and EXTI configuration) registers to their default reset values.
 */
void GPIO_AFIOInitDefault(void)
{
    RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_AFIO, DISABLE);
}

/**
 * @brief  Initializes the GPIOx peripheral according to the specified
 *         parameters in the GPIO_InitStruct.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 * @param GPIO_InitStruct pointer to a GPIO_InitType structure that
 *         contains the configuration information for the specified GPIO peripheral.
 */

void GPIO_InitPeripheral(GPIO_Module* GPIOx, GPIO_InitType * GPIO_InitStruct)
{
    uint32_t pinpos = 0x00U;
    uint32_t tmp = 0x00U,tmpregister=0x00U;
    uint32_t position = 0x00U;
    uint32_t iocurrent = 0x00U;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->Pin));
    assert_param(IS_GPIO_PULL(GPIO_InitStruct->GPIO_Pull));
    assert_param(IS_GPIO_SLEW_RATE(GPIO_InitStruct->GPIO_Slew_Rate));

    /*---------------------------- GPIO Mode Configuration -----------------------*/

    /*---------------------------- GPIO PL_CFG Configuration ------------------------*/

    while (((GPIO_InitStruct->Pin)>>position) != 0)
    {
        iocurrent = (GPIO_InitStruct->Pin)&(1U<<position);
        if (iocurrent)
        {
            pinpos = position * 2U;

            if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF_PP) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF_OD) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Input) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Analog))
            {
                /* Check if the Alternate function is compliant with the GPIO in use */
                assert_param(IS_GPIO_AF(GPIO_InitStruct->GPIO_Alternate));
                /* Configure Alternate function mapped with the current IO */
                if (position & 0x08)
                {
                    tmp = GPIOx->AFH;
                    tmp &= ~((uint32_t)0xF << ((uint32_t)(position & (uint32_t)0x07) * 4U));
                    tmp |= ((uint32_t)(GPIO_InitStruct->GPIO_Alternate) << ((uint32_t)(position & (uint32_t)0x07) * 4U)) ;
                    GPIOx->AFH = tmp;
                }
                else
                {
                    tmp = GPIOx->AFL;
                    tmp &= ~((uint32_t)0xF << ((uint32_t)(position & (uint32_t)0x07) * 4U)) ;
                    tmp |= ((uint32_t)(GPIO_InitStruct->GPIO_Alternate) << ((uint32_t)(position & (uint32_t)0x07) * 4U)) ;
                    GPIOx->AFL = tmp;
                }
            }
            /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
            tmpregister = GPIOx->PMODE;
            tmp = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
            tmpregister &= ~(((uint32_t)0x03) << pinpos);
            tmpregister |=( tmp << pinpos);
            GPIOx->PMODE = tmpregister;

            /* Configure pull-down mode */
            tmpregister = GPIOx->PUPD;
            tmp = (GPIO_InitStruct->GPIO_Pull & (uint32_t)0x03);
            tmpregister &=~(((uint32_t)0x03) << pinpos);
            tmpregister |= (tmp <<pinpos);
            GPIOx->PUPD = tmpregister;


            /* Configure driver current*/
            if ((GPIO_InitStruct->GPIO_Mode & GPIO_MODE) && (GPIO_InitStruct->GPIO_Mode != GPIO_Mode_Analog))
            {
                assert_param(IS_GPIO_CURRENT(GPIO_InitStruct->GPIO_Current));
                tmpregister = GPIOx->DS;
                tmp = (GPIO_InitStruct->GPIO_Current &((uint32_t)0x03));
                tmpregister &= ~(((uint32_t)0x03) << pinpos);
                tmpregister |= (tmp<<pinpos);
                GPIOx->DS = tmpregister;
            }
            /* Configure slew rate*/
                tmp = GPIOx->SR;
                tmp &=((uint32_t)(~((uint16_t)0x01 << position)));
                tmp |= (GPIO_InitStruct->GPIO_Slew_Rate &((uint32_t)0x01))<<position;
                GPIOx->SR = tmp;
            /*Configure Set/Reset register*/
            if (GPIO_InitStruct->GPIO_Pull == GPIO_Pull_Down)
            {
                GPIOx->PBC |= (((uint32_t)0x01) << position);
            }
            else
            {
                /* Set the corresponding POD bit */
                if (GPIO_InitStruct->GPIO_Pull == GPIO_Pull_Up)
                {
                    GPIOx->PBSC |= (((uint32_t)0x01) << position);
                }
            }

            /* In case of Output or Alternate function mode selection */
            if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_PP) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF_PP) ||
             (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_OD) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF_OD))
            {
                /* Configure the IO Output Type */

                tmp= GPIOx->POTYPE;
                tmp &= ~(((uint32_t)0x01U) << position) ;
                tmp |= (((GPIO_InitStruct->GPIO_Mode & GPIO_OUTPUT_TYPE) >> 4U) << position);
                GPIOx->POTYPE = tmp;
            }
            /*--------------------- EXTI Mode Configuration ------------------------*/
            /* Configure the External Interrupt or event for the current IO */
            if (GPIO_InitStruct->GPIO_Mode & EXTI_MODE)
            {
                /* Clear EXTI line configuration */
                tmp = EXTI->IMASK;
                tmp &= ~((uint32_t)0x01<<position);
                if ((GPIO_InitStruct->GPIO_Mode & GPIO_MODE_IT)== GPIO_MODE_IT)
                {
                    tmp |= ((uint32_t)0x01 << position);
                }
                EXTI->IMASK = tmp;

                tmp = EXTI->EMASK;
                tmp &= ~((uint32_t)0x01<<position);
                if ((GPIO_InitStruct->GPIO_Mode & GPIO_MODE_EVT)== GPIO_MODE_EVT)
                {
                    tmp |= ((uint32_t)0x01 << position);
                }
                EXTI->EMASK = tmp;

                /* Clear Rising Falling edge configuration */

                tmp = EXTI->RT_CFG;
                tmp &= ~((uint32_t)0x01<<position);
                if ((GPIO_InitStruct->GPIO_Mode & RISING_EDGE)== RISING_EDGE)
                {
                    tmp |= ((uint32_t)0x01 << position);
                }
                EXTI->RT_CFG = tmp;

                tmp = EXTI->FT_CFG;
                tmp &= ~((uint32_t)0x01<<position);
                if ((GPIO_InitStruct->GPIO_Mode & FALLING_EDGE)== FALLING_EDGE)
                {
                    tmp |= ((uint32_t)0x01 << position);
                }
                EXTI->FT_CFG = tmp;
            }
        }
        position++;
    }
}

/**
 * @brief  Fills each GPIO_InitStruct member with its default value.
 * @param GPIO_InitStruct pointer to a GPIO_InitType structure which will
 *         be initialized.
 */
void GPIO_InitStruct(GPIO_InitType* GPIO_InitStruct)
{
    /* Reset GPIO init structure parameters values */
    GPIO_InitStruct->Pin        = GPIO_PIN_ALL;
    GPIO_InitStruct->GPIO_Slew_Rate = GPIO_Slew_Rate_High;
    GPIO_InitStruct->GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitStruct->GPIO_Alternate = GPIO_NO_AF;
    GPIO_InitStruct->GPIO_Pull = GPIO_No_Pull;
    GPIO_InitStruct->GPIO_Current = GPIO_DC_2mA;
}

/**
 * @brief  Reads the specified input port pin.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 * @param Pin specifies the port bit to read.
 *   This parameter can be GPIO_Pin_x where x can be (0..15).
 * @return The input port pin value.
 */
uint8_t GPIO_ReadInputDataBit(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint8_t bitstatus = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(Pin));

    if ((GPIOx->PID & Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
 * @brief  Reads the specified GPIO input data port.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 * @return GPIO input data port value.
 */
uint16_t GPIO_ReadInputData(GPIO_Module* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t)GPIOx->PID);
}

/**
 * @brief  Reads the specified output data port bit.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 * @param Pin specifies the port bit to read.
 *   This parameter can be GPIO_Pin_x where x can be (0..15).
 * @return The output port pin value.
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint8_t bitstatus = 0x00;
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(Pin));

    if ((GPIOx->POD & Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
 * @brief  Reads the specified GPIO output data port.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 * @return GPIO output data port value.
 */
uint16_t GPIO_ReadOutputData(GPIO_Module* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t)GPIOx->POD);
}

/**
 * @brief  Sets the selected data port bits.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 * @param Pin specifies the port bits to be written.
 *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 */
void GPIO_SetBits(GPIO_Module* GPIOx, uint16_t Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(Pin));

    GPIOx->PBSC = Pin;
}
void GPIO_SetBitsHigh16(GPIO_Module* GPIOx, uint32_t Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    // assert_param(IS_GPIO_PIN(Pin));

    GPIOx->PBSC = Pin;
}

/**
 * @brief  Clears the selected data port bits.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 * @param Pin specifies the port bits to be written.
 *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 */
void GPIO_ResetBits(GPIO_Module* GPIOx, uint16_t Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(Pin));

    GPIOx->PBC = Pin;
}

/**
 * @brief  Sets or clears the selected data port bit.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 * @param Pin specifies the port bit to be written.
 *   This parameter can be one of GPIO_Pin_x where x can be (0..15).
 * @param BitCmd specifies the value to be written to the selected bit.
 *   This parameter can be one of the Bit_OperateType enum values:
 *     @arg Bit_RESET to clear the port pin
 *     @arg Bit_SET to set the port pin
 */
void GPIO_WriteBit(GPIO_Module* GPIOx, uint16_t Pin, Bit_OperateType BitCmd)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(Pin));
    assert_param(IS_GPIO_BIT_OPERATE(BitCmd));

    if (BitCmd != Bit_RESET)
    {
        GPIOx->PBSC = Pin;
    }
    else
    {
        GPIOx->PBC = Pin;
    }
}

/**
 * @brief  Writes data to the specified GPIO data port.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 * @param PortVal specifies the value to be written to the port output data register.
 */
void GPIO_Write(GPIO_Module* GPIOx, uint16_t PortVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->POD = PortVal;
}

/**
 * @brief  Locks GPIO Pins configuration registers.
 * @param GPIOx where x can be (A..D) to select the GPIO peripheral.
 * @param Pin specifies the port bit to be written.
 *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 */
void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint32_t tmp = 0x00010000;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(Pin));

    tmp |= Pin;
    /* Set LCKK bit */
    GPIOx->PLOCK = tmp;
    /* Reset LCKK bit */
    GPIOx->PLOCK = Pin;
    /* Set LCKK bit */
    GPIOx->PLOCK = tmp;
    /* Read LCKK bit*/
    tmp = GPIOx->PLOCK;
    /* Read LCKK bit*/
    tmp = GPIOx->PLOCK;
}



/**
 * @brief  Changes the mapping of the specified pin.
 * @param PortSource selects the GPIO port to be used.
 * @param PinSource specifies the pin for the remaping.
 *   This parameter can be GPIO_PinSourcex where x can be (0..15).
 * @param AlternateFunction specifies the alternate function for the remaping.
 */
void GPIO_ConfigPinRemap(uint8_t PortSource, uint8_t PinSource, uint32_t AlternateFunction)
{
    uint32_t tmp = 0x00, tmpregister = 0x00;
    GPIO_Module *GPIOx;
    /* Check the parameters */
    assert_param(IS_GPIO_REMAP_PORT_SOURCE(PortSource));
    assert_param(IS_GPIO_PIN_SOURCE(PinSource));
    assert_param(IS_GPIO_AF(AlternateFunction));
    /*Get Peripheral point*/
    GPIOx = GPIO_GET_PERIPH(PortSource);
    /**/
    if (PinSource & (uint8_t)0x08)
    {
        tmp = (uint32_t)(PinSource & (uint8_t)0x07);
        /*Read GPIO_AFH register*/
        tmpregister  = GPIOx->AFH;
        /*Reset corresponding bits*/
        tmpregister &=~((uint32_t)0x0F <<(tmp*4U));
        /*Set corresponding bits*/
        tmpregister |= AlternateFunction << (tmp*4U);
        /*Write to the GPIO_AFH register*/
        GPIOx->AFH = tmpregister;
    }
    else
    {
        tmp = (uint32_t)(PinSource & (uint8_t)0x07);
        /*Read GPIO_AFL register*/
        tmpregister  = GPIOx->AFL;
        /*Reset corresponding bits*/
        tmpregister &=~((uint32_t)0x0F <<(tmp*4U));
        /*Set corresponding bits*/
        tmpregister |= AlternateFunction << (tmp*4U);
        /*Write to the GPIO_AFL register*/
        GPIOx->AFL = tmpregister;
    }
}

/**
 * @brief  Selects the GPIO pin used as Event output.
 * @param PortSource selects the GPIO port to be used as source
 *   for Event output.
 *   This parameter can be GPIO_PortSourceGPIOx where x can be (A..D).
 * @param PinSource specifies the pin for the Event output.
 *   This parameter can be GPIO_PinSourcex where x can be (0..15).
 */
void GPIO_ConfigEventOutput(uint8_t PortSource, uint8_t PinSource)
{
    uint32_t tmpregister = 0x00,tmp = 0x00;
    GPIO_Module *GPIOx;
    /* Check the parameters */
    assert_param(IS_GPIO_EVENTOUT_PORT_SOURCE(PortSource));
    assert_param(IS_GPIO_PIN_SOURCE(PinSource));

    /*Get Peripheral structure point*/
    GPIOx = GPIO_GET_PERIPH(PortSource);
    if (PinSource & (uint8_t)0x08)
    {
        tmp = (uint32_t)(PinSource & (uint8_t)0x07);
        /*Read GPIO_AFH register*/
        tmpregister  = GPIOx->AFH;
        /*Reset corresponding bits*/
        tmpregister &=~((uint32_t)0x0F <<(tmp*4U));
        /*Set corresponding bits*/
        tmpregister |= GPIO_AF3_EVENTOUT;
        /*Write to the GPIO_AFH register*/
        GPIOx->AFH = tmpregister;
    }
    else
    {
        tmp = (uint32_t)(PinSource & (uint8_t)0x07);
        /*Read GPIO_AFL register*/
        tmpregister  = GPIOx->AFL;
        /*Reset corresponding bits*/
        tmpregister &=~((uint32_t)0x0F <<(tmp*4U));
        /*Set corresponding bits*/
        tmpregister |= GPIO_AF3_EVENTOUT;
        /*Write to the GPIO_AFL register*/
        GPIOx->AFL = tmpregister;
    }
}

/**
 * @brief  Enables or disables the Event Output.
 * @param Cmd new state of the Event output.
 *   This parameter can be: ENABLE or DISABLE.
 */
void GPIO_CtrlEventOutput(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)EVCR_EVOE_BB = (uint32_t)Cmd;
}


/**
 * @brief  Selects the GPIO pin used as EXTI Line.
 * @param PortSource selects the GPIO port to be used as source for EXTI lines.
 *   This parameter can be GPIO_PortSourceGPIOx where x can be (A..D).
 * @param PinSource specifies the EXTI line to be configured.
 *   This parameter can be GPIO_PinSourcex where x can be (0..15).
 */
void GPIO_ConfigEXTILine(uint8_t PortSource, uint8_t PinSource)
{
    uint32_t port = (uint32_t)PortSource;
    /* Check the parameters */
    assert_param(IS_GPIO_EXTI_PORT_SOURCE(PortSource));
    assert_param(IS_GPIO_PIN_SOURCE(PinSource));

    AFIO->EXTI_CFG[(PinSource >> 0x02)] &= ~(((uint32_t)0x03) << ((PinSource & (uint8_t)0x03)*4u));
    AFIO->EXTI_CFG[(PinSource >> 0x02)] |=  (port << ((PinSource & (uint8_t)0x03) *4u));
}

/**
 * @brief  Selects the alternate function SPIx NSS mode.
 * @param AFIO_SPIx_NSS choose which SPI configuration.
 *   This parameter can be AFIO_SPI1_NSS and AFIO_SPI2_NSS.
 * @param SpiNssType specifies the SPI_NSS mode to be configured.
 *   This parameter can be AFIO_SPI1_NSS_High_IMPEDANCE and AFIO_SPI1_NSS_High_LEVEL.
 */
void AFIO_ConfigSPINSSMode(uint32_t AFIO_SPIx_NSS,AFIO_SPI_NSSType SpiNssType)
{
    uint32_t tmp = 0x00;
    /* Check the parameters */
    assert_param(IS_AFIO_SPIX(AFIO_SPIx_NSS));
    assert_param(IS_AFIO_SPI_NSS(SpiNssType));
    tmp = AFIO->RMP_CFG;
    tmp &=(~(0x01U << AFIO_SPIx_NSS));
    tmp |=(SpiNssType << AFIO_SPIx_NSS);
    AFIO->RMP_CFG = tmp;
}

/**
 * @brief  Configurate ADC external trigger.
 * @param ADCETRType choose whether to configure rule conversion or injection conversion .
 *   This parameter can be AFIO_ADC_ETRI and AFIO_ADC_ETRR.
 * @param ADCTrigRemap specifies the external trigger line be configured.
 *   This parameter can be AFIO_ADC_TRIG_EXTI_x where x can be (0..15) or AFIO_ADC_TRIG_TIM8_CHy where y can be(3..4).
 */
void AFIO_ConfigADCExternalTrigRemap(AFIO_ADC_ETRType ADCETRType,AFIO_ADC_Trig_RemapType ADCTrigRemap)
{
    uint32_t tmp = 0x00;
    /* Check the parameters */
    assert_param(IS_AFIO_ADC_ETR(ADCETRType));
    if (ADCETRType == AFIO_ADC_ETRI)
    {
        /* Check the parameters */
        assert_param(IS_AFIO_ADC_ETRI(ADCTrigRemap));
        tmp  = AFIO->RMP_CFG;
        /* clear AFIO_RMP_CFG register ETRI bit*/
        tmp &= (~(0x01U << AFIO_ADC_ETRI));
        /* if ADCETRType is AFIO_ADC_ETRI then ADCTrigRemap cannot be AFIO_ADC_TRIG_TIM8_CH3*/
        if (ADCTrigRemap == AFIO_ADC_TRIG_TIM8_CH4)
        {
            /* select TIM8_CH4 line to connect*/
            tmp |= (0x01U << AFIO_ADC_ETRI);
        }
        else
        {
            /* select which external line is connected*/
            tmp &=(~(0x0FU<<4U));
            tmp |= (ADCTrigRemap<<4U);
        }
        AFIO->RMP_CFG = tmp;
    }
    else
    {
        if (ADCETRType == AFIO_ADC_ETRR)
        {
            /* Check the parameters */
            assert_param(IS_AFIO_ADC_ETRR(ADCTrigRemap));
            tmp  = AFIO->RMP_CFG;
            /* clear AFIO_RMP_CFG register ETRR bit*/
            tmp &= (~(0x01U << AFIO_ADC_ETRR));
            /* if ADCETRType is AFIO_ADC_ETRR then ADCTrigRemap cannot be AFIO_ADC_TRIG_TIM8_CH4*/
            if (ADCTrigRemap == AFIO_ADC_TRIG_TIM8_CH3)
            {
                /* select TIM8_CH3 line to connect*/
                tmp |= (0x01U << AFIO_ADC_ETRR);
            }
            else
            {
                /* select which external line is connected*/
                tmp &=(~(0x0FU<<0));
                tmp |= ADCTrigRemap;
            }
            AFIO->RMP_CFG = tmp;
        }
    }
}

/**
 * @}
 */

/**
 * @}
 */
