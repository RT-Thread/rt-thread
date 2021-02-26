/**
  ******************************************************************************
  * @brief   I2C functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_i2c.h"
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup I2C
  * @brief I2C driver modules
  * @{
  */

/** @defgroup I2C_Private_Defines
  * @{
  */

/* I2C CTLR1_I2CEN mask */
#define CTLR1_I2CEN_SET             I2C_CTLR1_I2CEN
#define CTLR1_I2CEN_RESET           ((uint16_t)~I2C_CTLR1_I2CEN)

/* I2C CTLR1_GENSTA mask */
#define CTLR1_GENSTA_SET            I2C_CTLR1_GENSTA
#define CTLR1_GENSTA_RESET          ((uint16_t)~I2C_CTLR1_GENSTA)

/* I2C CTLR1_GENSTP mask */
#define CTLR1_GENSTP_SET            I2C_CTLR1_GENSTP
#define CTLR1_GENSTP_RESET          ((uint16_t)~I2C_CTLR1_GENSTP)

/* I2C CTLR1_ACKEN mask */
#define CTLR1_ACKEN_SET             I2C_CTLR1_ACKEN
#define CTLR1_ACKEN_RESET           ((uint16_t)~I2C_CTLR1_ACKEN)

/* I2C CTLR1_GCEN mask */
#define CTLR1_GCEN_SET              I2C_CTLR1_GCEN
#define CTLR1_GCEN_RESET            ((uint16_t)~I2C_CTLR1_GCEN)

/* I2C CTLR1_SRESET mask */
#define CTLR1_SRESET_SET            I2C_CTLR1_SRESET
#define CTLR1_SRESET_RESET          ((uint16_t)~I2C_CTLR1_SRESET)

/* I2C CTLR1_SALT mask */
#define CTLR1_SALT_SET              I2C_CTLR1_SALT
#define CTLR1_SALT_RESET            ((uint16_t)~I2C_CTLR1_SALT)

/* I2C CTLR1_PECTRANS mask */
#define CTLR1_PECTRANS_SET          I2C_CTLR1_PECTRANS
#define CTLR1_PECTRANS_RESET        ((uint16_t)~I2C_CTLR1_PECTRANS)

/* I2C CTLR1_PECEN mask */
#define CTLR1_PECEN_SET             I2C_CTLR1_PECEN
#define CTLR1_PECEN_RESET           ((uint16_t)~I2C_CTLR1_PECEN)

/* I2C CTLR1_ARPEN mask */
#define CTLR1_ARPEN_SET             I2C_CTLR1_ARPEN
#define CTLR1_ARPEN_RESET           ((uint16_t)~I2C_CTLR1_ARPEN)

/* I2C CTLR1_DISSTRC mask */
#define CTLR1_DISSTRC_SET           I2C_CTLR1_DISSTRC
#define CTLR1_DISSTRC_RESET         ((uint16_t)~I2C_CTLR1_DISSTRC)

/* I2C registers Masks */
#define CTLR1_CLEAR_MASK            ((uint16_t)0xFBF5)

/* I2C CTLR2_DMAON mask */
#define CTLR2_DMAON_SET             I2C_CTLR2_DMAON
#define CTLR2_DMAON_RESET           ((uint16_t)~I2C_CTLR2_DMAON)

/* I2C CTLR2_DMALST mask */
#define CTLR2_DMALST_SET            I2C_CTLR2_DMALST
#define CTLR2_DMALST_RESET          ((uint16_t)~I2C_CTLR2_DMALST)

/* I2C CTLR2_I2CCLK mask */
#define CTLR2_I2CCLK_RESET          ((uint16_t)0xFFC0)

/* I2C I2CCLK_Freq_MAX */
#define I2CCLK_FREQ_MAX             I2C_CTLR2_I2CCLK

/* I2C AR1_ADDRESS0 mask */
#define AR1_ADDRESS0_SET            I2C_AR1_ADDRESS0
#define AR1_ADDRESS0_RESET          ((uint16_t)~I2C_AR1_ADDRESS0)

/* I2C AR2_DUADEN mask */
#define AR2_DUADEN_SET              ((uint16_t)0x0001)
#define AR2_DUADEN_RESET            ((uint16_t)0xFFFE)

/* I2C AR2_ADDRESS2 mask */
#define AR2_ADDRESS2_RESET          ((uint16_t)0xFF01)

/* I2C CLKR_FAST mask */
#define CLKR_FAST_SET               ((uint16_t)0x8000)

/* I2C CLKR_CLKC mask */
#define CLKR_CLKC_SET               ((uint16_t)0x0FFF)

/* I2C STR_FLAG mask */
#define STR_FLAG_MASK               ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define INTEN_MASK                  ((uint32_t)0x07000000)

/**
  * @}
  */

/** @defgroup I2C_Private_Functions
  * @{
  */

/**
  * @brief  Reset the I2Cx interface.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @retval None.
  */
void I2C_DeInit(I2C_TypeDef *I2Cx)
{
    if (I2Cx == I2C1) {
        /* Enable I2C1 reset state */
        RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_I2C1RST, ENABLE);
        /* Release I2C1 from reset state */
        RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_I2C1RST, DISABLE);
    } else {
        /* Enable I2C2 reset state */
        RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_I2C2RST, ENABLE);
        /* Release I2C2 from reset state */
        RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_I2C2RST, DISABLE);
    }
}

/**
  * @brief  Initialize the I2Cx interface parameters.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_InitParaStruct: the sturct I2C_InitPara pointer.
  * @retval None.
  */
void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitPara *I2C_InitParaStruct)
{
    uint16_t temp = 0, freqrange = 0;
    uint16_t result = 0x04;
    uint32_t pclk1 = 8000000;
    RCC_ClocksPara rcc_clocks;

    /* Disable I2C */
    I2Cx->CTLR1 &= CTLR1_I2CEN_RESET;

    /* CTLR2 */
    temp = I2Cx->CTLR2;

    /* I2CCLK[5:0] */
    temp &= CTLR2_I2CCLK_RESET;
    RCC_GetClocksFreq(&rcc_clocks);
    pclk1 = rcc_clocks.APB1_Frequency;
    freqrange = (uint16_t)(pclk1 / 1000000);
    if (freqrange > I2CCLK_FREQ_MAX) {
        freqrange = I2CCLK_FREQ_MAX;
    }
    temp |= freqrange;
    I2Cx->CTLR2 = temp;

    /* RTR and CLKR */
    temp = 0;

    if (I2C_InitParaStruct->I2C_BitRate <= 100000) {
        /* Standard mode */
        result = (uint16_t)(pclk1 / (I2C_InitParaStruct->I2C_BitRate << 1));
        if (result < 0x04) {
            /* The CLKR.CLKC higher than 0x04 in standard mode*/
            result = 0x04;
        }
        temp |= result;
        I2Cx->CLKR = temp;

        /* RTR */
        if (freqrange >= I2CCLK_FREQ_MAX) {
            I2Cx->RTR = I2CCLK_FREQ_MAX;
        } else {
            I2Cx->RTR = freqrange + 1;
        }
    } else {
        /* Fast mode */
        if (I2C_InitParaStruct->I2C_DutyCycle == I2C_DUTYCYCLE_2) {
            /* I2C_DutyCycle == 2 */
            result = (uint16_t)(pclk1 / (I2C_InitParaStruct->I2C_BitRate * 3));
        } else {
            /* I2C_DutyCycle == 16/9 */
            result = (uint16_t)(pclk1 / (I2C_InitParaStruct->I2C_BitRate * 25));
            result |= I2C_DUTYCYCLE_16_9;
        }

        if ((result & CLKR_CLKC_SET) == 0) {
            /* The CLKR.CLKC higher than 0x01 in fast mode*/
            result |= (uint16_t)0x0001;
        }
        temp |= (uint16_t)(result | CLKR_FAST_SET);

        /* RTR */
        I2Cx->RTR = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);
    }
    I2Cx->CLKR = temp;

    /* CTLR1 */
    I2Cx->CTLR1 |= CTLR1_I2CEN_SET;

    temp = I2Cx->CTLR1;
    temp &= CTLR1_CLEAR_MASK;
    temp |= (uint16_t)((uint32_t)I2C_InitParaStruct->I2C_Protocol | CTLR1_ACKEN_SET);
    I2Cx->CTLR1 = temp;

    /* AR1 */
    I2Cx->AR1 = (I2C_InitParaStruct->I2C_AddressingMode | I2C_InitParaStruct->I2C_DeviceAddress);
}

/**
  * @brief  Initial the sturct I2C_InitPara.
  * @param  I2C_InitParaStruct: the sturct I2C_InitPara pointer.
  * @retval None.
  */
void I2C_ParaInit(I2C_InitPara *I2C_InitParaStruct)
{
    I2C_InitParaStruct->I2C_Protocol = I2C_PROTOCOL_I2C;
    I2C_InitParaStruct->I2C_DutyCycle = I2C_DUTYCYCLE_2;
    I2C_InitParaStruct->I2C_BitRate = 10000;
    I2C_InitParaStruct->I2C_AddressingMode = I2C_ADDRESSING_MODE_7BIT;
    I2C_InitParaStruct->I2C_DeviceAddress = 0x08;
}

/**
  * @brief  Enable or disable the I2Cx interface.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2Cx interface.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the I2Cx interface */
        I2Cx->CTLR1 |= CTLR1_I2CEN_SET;
    } else {
        /* Disable the I2Cx interface */
        I2Cx->CTLR1 &= CTLR1_I2CEN_RESET;
    }
}

/**
  * @brief  Enable or disable the I2Cx DMA requests.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2C DMA transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_DMA_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the I2Cx DMA requests */
        I2Cx->CTLR2 |= CTLR2_DMAON_SET;
    } else {
        /* Disable the I2Cx DMA requests */
        I2Cx->CTLR2 &= CTLR2_DMAON_RESET;
    }
}

/**
  * @brief  Enable or disable the DMA last.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2C DMA last transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_DMALastTransfer_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Next DMA transfer is the last transfer */
        I2Cx->CTLR2 |= CTLR2_DMALST_SET;
    } else {
        /* Next DMA transfer is not the last transfer */
        I2Cx->CTLR2 &= CTLR2_DMALST_RESET;
    }
}

/**
  * @brief  Enable or disable I2C_CTLR1_GENSTA control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2C START condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_StartOnBus_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable I2C_CTLR1_GENSTA control bit */
        I2Cx->CTLR1 |= CTLR1_GENSTA_SET;
    } else {
        /* Disable I2C_CTLR1_GENSTA control bit */
        I2Cx->CTLR1 &= CTLR1_GENSTA_RESET;
    }
}

/**
  * @brief  Enable or disable I2C_CTLR1_GENSTP control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2C STOP condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_StopOnBus_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable I2C_CTLR1_GENSTP control bit */
        I2Cx->CTLR1 |= CTLR1_GENSTP_SET;
    } else {
        /* Disable I2C_CTLR1_GENSTP control bit */
        I2Cx->CTLR1 &= CTLR1_GENSTP_RESET;
    }
}

/**
  * @brief  Enable or disable the I2C_CTLR1_ACKEN control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2C Acknowledgement.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_Acknowledge_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable I2C_CTLR1_ACKEN control bit */
        I2Cx->CTLR1 |= CTLR1_ACKEN_SET;
    } else {
        /* Disable I2C_CTLR1_ACKEN control bit */
        I2Cx->CTLR1 &= CTLR1_ACKEN_RESET;
    }
}

/**
  * @brief  Set the I2Cx own address2.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  Address: specifies the 7bit I2C own address2.
  * @retval None.
  */
void I2C_OwnAddress2(I2C_TypeDef *I2Cx, uint8_t Address)
{
    uint16_t temp = 0;

    temp = I2Cx->AR2;
    temp &= AR2_ADDRESS2_RESET;
    temp |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);
    /* I2C_AR2_ADDRESS2 */
    I2Cx->AR2 = temp;
}

/**
  * @brief  Enable or disable the I2C_AR2_DUADEN control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2C dual addressing mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_DualAddress_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the I2C_AR2_DUADEN control bit */
        I2Cx->AR2 |= AR2_DUADEN_SET;
    } else {
        /* Disable the I2C_AR2_DUADEN control bit */
        I2Cx->AR2 &= AR2_DUADEN_RESET;
    }
}

/**
  * @brief  Enable or disable I2C_CTLR1_GCEN control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2C General call.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GeneralCall_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable I2C_CTLR1_GCEN control bit */
        I2Cx->CTLR1 |= CTLR1_GCEN_SET;
    } else {
        /* Disable I2C_CTLR1_GCEN control bit */
        I2Cx->CTLR1 &= CTLR1_GCEN_RESET;
    }
}

/**
  * @brief  Enable or disable the specified I2C interrupt.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_INT: the I2C interrupt sources.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_INT_EIE: Error interrupt
  *     @arg I2C_INT_EE: Event interrupt
  *     @arg I2C_INT_BIE: Buffer interrupt
  * @param  NewValue: new value of the specified I2C interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_INTConfig(I2C_TypeDef *I2Cx, uint16_t I2C_INT, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the I2C interrupt */
        I2Cx->CTLR2 |= I2C_INT;
    } else {
        /* Disable the I2C interrupt */
        I2Cx->CTLR2 &= (uint16_t)~I2C_INT;
    }
}

/**
  * @brief  Send one byte to bus.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  Data: Byte to be transmitted.
  * @retval None.
  */
void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t Data)
{
    /* Write Data to DTR */
    I2Cx->DTR = Data;
}

/**
  * @brief  Receive one byte from the bus.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @retval The received data.
  */
uint8_t I2C_ReceiveData(I2C_TypeDef *I2Cx)
{
    /* Read the DTR register */
    return (uint8_t)I2Cx->DTR;
}

/**
  * @brief  Addressing a device on the I2C bus.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  Address: the slave device's address.
  * @param  I2C_Direction: Transmitter or a Receiver.
  *   This parameter can be one of the following values:
  *     @arg I2C_DIRECTION_TRANSMITTER: Transmitter mode
  *     @arg I2C_DIRECTION_RECEIVER: Receiver mode
  * @retval None.
  */
void I2C_AddressingDevice_7bit(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
    if (I2C_Direction != I2C_DIRECTION_TRANSMITTER) {
        /* Receiver mode */
        Address |= AR1_ADDRESS0_SET;
    } else {
        /* Transmitter mode */
        Address &= AR1_ADDRESS0_RESET;
    }
    I2Cx->DTR = Address;
}

/**
  * @brief  Read the I2Cx register.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_Register: the I2Cx register.
  *   This parameter can be one of the following values:
  *     @arg I2C_REGISTER_CTLR1: CTLR1 register.
  *     @arg I2C_REGISTER_CTLR2: CTLR2 register.
  *     @arg I2C_REGISTER_AR1: AR1 register.
  *     @arg I2C_REGISTER_AR2: AR2 register.
  *     @arg I2C_REGISTER_DTR: DTR register.
  *     @arg I2C_REGISTER_STR1: STR1 register.
  *     @arg I2C_REGISTER_STR2: STR2 register.
  *     @arg I2C_REGISTER_CLKR: CLKR register.
  *     @arg I2C_REGISTER_RTR: RTR register.
  * @retval The value of the read register.
  */
uint16_t I2C_ReadRegister(I2C_TypeDef *I2Cx, uint8_t I2C_Register)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t) I2Cx;
    temp += I2C_Register;

    /* Return the selected register value */
    return (*(__IO uint16_t *) temp);
}

/**
  * @brief  Enable or disable the I2C_CTLR1_SRESET control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2C software reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_SoftwareReset_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable I2C_CTLR1_SRESET control bit */
        I2Cx->CTLR1 |= CTLR1_SRESET_SET;
    } else {
        /* Disable I2C_CTLR1_SRESET control bit */
        I2Cx->CTLR1 &= CTLR1_SRESET_RESET;
    }
}

/**
  * @brief  Enable or disable the I2C_CTLR1_POAP control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_NACKPosition: the position of NACK.
  *   This parameter can be one of the following values:
  *     @arg I2C_NACKPOSITION_NEXT: the next byte is the last received byte
  *     @arg I2C_NACKPOSITION_CURRENT: the current byte is the last received byte
  * @retval None.
  */
void I2C_NACKPosition_Enable(I2C_TypeDef *I2Cx, uint16_t I2C_NACKPosition)
{
    if (I2C_NACKPosition == I2C_NACKPOSITION_NEXT) {
        /* Next byte will be the last received byte */
        I2Cx->CTLR1 |= I2C_NACKPOSITION_NEXT;
    } else {
        /* Current byte is the last received byte */
        I2Cx->CTLR1 &= I2C_NACKPOSITION_CURRENT;
    }
}

/**
  * @brief  Enable or disable the I2C_CTLR1_SALT control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2C software reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_SMBusAlertSend_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable I2C_CTLR1_SALT control bit */
        I2Cx->CTLR1 |= CTLR1_SALT_SET;
    } else {
        /* Disable I2C_CTLR1_SALT control bit */
        I2Cx->CTLR1 &= CTLR1_SALT_RESET;
    }
}

/**
  * @brief  Enable or disable the I2C_CTLR1_PECTRANS control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2C PEC transmission.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_PECTransmit_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable I2C_CTLR1_PECTRANS control bit */
        I2Cx->CTLR1 |= CTLR1_PECTRANS_SET;
    } else {
        /* Disable I2C_CTLR1_PECTRANS control bit */
        I2Cx->CTLR1 &= CTLR1_PECTRANS_RESET;
    }
}

/**
  * @brief  Enable or disable the I2C_CTLR1_POAP control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_PECPosition: the position of PEC.
  *   This parameter can be one of the following values:
  *     @arg I2C_PECPOSITION_NEXT: the next byte is PEC
  *     @arg I2C_PECPOSITION_CURRENT: the current byte is PEC
  * @retval None.
  */
void I2C_PECPosition_Enable(I2C_TypeDef *I2Cx, uint16_t I2C_PECPosition)
{
    if (I2C_PECPosition == I2C_PECPOSITION_NEXT) {
        /* The next byte is PEC */
        I2Cx->CTLR1 |= I2C_PECPOSITION_NEXT;
    } else {
        /* The current byte is PEC */
        I2Cx->CTLR1 &= I2C_PECPOSITION_CURRENT;
    }
}

/**
  * @brief  Enable or disable the I2C_CTLR1_PECEN control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2Cx PEC value calculation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_PEC_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable I2C_CTLR1_PECEN control bit */
        I2Cx->CTLR1 |= CTLR1_PECEN_SET;
    } else {
        /* Disable I2C_CTLR1_PECEN control bit */
        I2Cx->CTLR1 &= CTLR1_PECEN_RESET;
    }
}

/**
  * @brief  The Packet Error Checking value.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @retval The PEC value.
  */
uint8_t I2C_GetPECValue(I2C_TypeDef *I2Cx)
{
    /* I2C_STR2_ECV */
    return ((I2Cx->STR2) >> 8);
}

/**
  * @brief  Enable or disable the I2C_CTLR1_ARPEN control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2Cx ARP.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_ARP_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable I2C_CTLR1_ARPEN control bit */
        I2Cx->CTLR1 |= CTLR1_ARPEN_SET;
    } else {
        /* Disable I2C_CTLR1_ARPEN control bit */
        I2Cx->CTLR1 &= CTLR1_ARPEN_RESET;
    }
}

/**
  * @brief  Enable or disable the I2C_CTLR1_DISSTRC control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  NewValue: new value of the I2Cx Clock stretching.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_StretchClock_Enable(I2C_TypeDef *I2Cx, TypeState NewValue)
{
    if (NewValue == DISABLE) {
        /* Enable I2C_CTLR1_DISSTRC control bit */
        I2Cx->CTLR1 |= CTLR1_DISSTRC_SET;
    } else {
        /* Enable I2C_CTLR1_DISSTRC control bit */
        I2Cx->CTLR1 &= CTLR1_DISSTRC_RESET;
    }
}

/**
  * @brief  Enable or disable the I2C_CLKR_DTCY control bit.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_DutyCycle: the duty cycle in fast mode.
  *   This parameter can be one of the following values:
  *     @arg I2C_DUTYCYCLE_2: I2C fast mode Tlow/Thigh = 2
  *     @arg I2C_DUTYCYCLE_16_9: I2C fast mode Tlow/Thigh = 16/9
  * @retval None.
  */
void I2C_FastModeDutyCycle(I2C_TypeDef *I2Cx, uint16_t I2C_DutyCycle)
{
    if (I2C_DutyCycle != I2C_DUTYCYCLE_16_9) {
        /* DutyCycle=2:1 */
        I2Cx->CLKR &= I2C_DUTYCYCLE_2;
    } else {
        /* DutyCycle=16:9 */
        I2Cx->CLKR |= I2C_DUTYCYCLE_16_9;
    }
}

/**
  * @brief  Detect I2Cx State Machine.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_State: I2Cx State Machine.
  *   This parameter can be one of the following values:
  *     @arg I2C_PROGRAMMINGMODE_SLAVE_TRANSMITTER_ADDSEND
  *     @arg I2C_PROGRAMMINGMODE_SLAVE_RECEIVER_ADDSEND
  *     @arg I2C_PROGRAMMINGMODE_SLAVE_TRANSMITTER_SECONDADDRESS_SELECTED
  *     @arg I2C_PROGRAMMINGMODE_SLAVE_RECEIVER_SECONDADDRESS_SELECTED
  *     @arg I2C_PROGRAMMINGMODE_SLAVE_GENERALCALLADDRESS_SELECTED
  *     @arg I2C_PROGRAMMINGMODE_SLAVE_BYTE_RECEIVED
  *     @arg (I2C_PROGRAMMINGMODE_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUMODF)
  *     @arg (I2C_PROGRAMMINGMODE_SLAVE_BYTE_RECEIVED | I2C_FLAG_RXGC)
  *     @arg I2C_PROGRAMMINGMODE_SLAVE_BYTE_TRANSMITTED
  *     @arg (I2C_PROGRAMMINGMODE_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUMODF)
  *     @arg (I2C_PROGRAMMINGMODE_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_RXGC)
  *     @arg I2C_PROGRAMMINGMODE_SLAVE_ACK_FAILURE
  *     @arg I2C_PROGRAMMINGMODE_SLAVE_STOP_DETECTED
  *     @arg I2C_PROGRAMMINGMODE_MASTER_SBSEND
  *     @arg I2C_PROGRAMMINGMODE_MASTER_TRANSMITTER_ADDSEND
  *     @arg I2C_PROGRAMMINGMODE_MASTER_RECEIVER_ADDSEND
  *     @arg I2C_PROGRAMMINGMODE_MASTER_BYTE_RECEIVED
  *     @arg I2C_PROGRAMMINGMODE_MASTER_BYTE_TRANSMITTING
  *     @arg I2C_PROGRAMMINGMODE_MASTER_BYTE_TRANSMITTED
  *     @arg I2C_PROGRAMMINGMODE_MASTER_ADD10SEND
  * @retval The detected result(SUCCESS or ERROR).
  */
TypeState I2C_StateDetect(I2C_TypeDef *I2Cx, uint32_t I2C_State)
{
    uint32_t currentstate = 0;
    uint32_t flag1 = 0, flag2 = 0;
    TypeState state = ERROR;

    /* Read the I2Cx status register */
    flag1 = I2Cx->STR1;
    flag2 = I2Cx->STR2;
    flag2 = flag2 << 16;

    /* Get the state value from I2C status register */
    currentstate = (flag1 | flag2) & STR_FLAG_MASK;

    if ((currentstate & I2C_State) == I2C_State) {
        /* I2C_State is detected */
        state = SUCCESS;
    } else {
        /* I2C_State is not detected */
        state = ERROR;
    }
    return state;
}

/**
  * @brief  Get the I2Cx Current State.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @retval The current state.
  */
uint32_t I2C_GetCurrentState(I2C_TypeDef *I2Cx)
{
    uint32_t currentstate = 0;
    uint32_t flag1 = 0, flag2 = 0;

    /* Read the I2Cx status register */
    flag1 = I2Cx->STR1;
    flag2 = I2Cx->STR2;
    flag2 = flag2 << 16;

    /* Get the last event value from I2C status register */
    currentstate = (flag1 | flag2) & STR_FLAG_MASK;

    return currentstate;
}

/**
  * @brief  Get the bit flag of STRx registers.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_FLAG: the flag of STRx registers.
  *   This parameter can be one of the following values:
  *     @arg I2C_FLAG_DUMODF: Dual flag (Slave mode)
  *     @arg I2C_FLAG_HSTSMB: SMBus host header (Slave mode)
  *     @arg I2C_FLAG_DEFSMB: SMBus default header (Slave mode)
  *     @arg I2C_FLAG_RXGC: General call header flag (Slave mode)
  *     @arg I2C_FLAG_TRS: Transmitter or Receiver flag
  *     @arg I2C_FLAG_I2CBSY: Bus busy flag
  *     @arg I2C_FLAG_MASTER: Master or Slave flag
  *     @arg I2C_FLAG_SMBALTS: SMBus Alert flag
  *     @arg I2C_FLAG_SMBTO: Timeout or Tlow error flag
  *     @arg I2C_FLAG_PECE: PEC error in reception flag
  *     @arg I2C_FLAG_RXORE: Overrun or Underrun flag (Slave mode)
  *     @arg I2C_FLAG_AE: Acknowledge failure flag
  *     @arg I2C_FLAG_LOSTARB: Arbitration lost flag (Master mode)
  *     @arg I2C_FLAG_BE: Bus error flag
  *     @arg I2C_FLAG_TBE: Data register empty flag (Transmitter)
  *     @arg I2C_FLAG_RBNE: Data register not empty (Receiver) flag
  *     @arg I2C_FLAG_STPSEND: Stop detection flag (Slave mode)
  *     @arg I2C_FLAG_ADD10SEND: 10-bit header sent flag (Master mode)
  *     @arg I2C_FLAG_BTC: Byte transfer finished flag
  *     @arg I2C_FLAG_ADDSEND: Address sent flag (Master mode) or Address matched flag (Slave mode)
  *     @arg I2C_FLAG_SBSEND: Start bit flag (Master mode)
  * @retval The new value of I2C_FLAG (SET or RESET).
  */
TypeState I2C_GetBitState(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG)
{
    __IO uint32_t i2creg = 0, i2cxbase = 0;

    /* Get the I2Cx peripheral base address */
    i2cxbase = (uint32_t)I2Cx;

    /* Read flag register index */
    i2creg = I2C_FLAG >> 28;

    /* Get bit[23:0] of the flag */
    I2C_FLAG &= STR_FLAG_MASK;

    if (i2creg != 0) {
        /* Flag in I2Cx STR1 register */
        i2cxbase += 0x14;
    } else {
        /* Flag in I2Cx STR2 Register */
        I2C_FLAG = (uint32_t)(I2C_FLAG >> 16);
        /* Get the I2Cx STR2 register address */
        i2cxbase += 0x18;
    }

    if (((*(__IO uint32_t *)i2cxbase) & I2C_FLAG) != (uint32_t)RESET) {
        /* I2C_FLAG is set */
        return SET;
    } else {
        /* I2C_FLAG is reset */
        return RESET;
    }
}

/**
  * @brief  Clear the bit flag of STRx registers.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_FLAG: the flag of STRx registers.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_FLAG_SMBALTS: SMBus Alert flag
  *     @arg I2C_FLAG_SMBTO: Timeout or Tlow error flag
  *     @arg I2C_FLAG_PECE: PEC error in reception flag
  *     @arg I2C_FLAG_RXORE: Overrun or Underrun flag (Slave mode)
  *     @arg I2C_FLAG_AE: Acknowledge failure flag
  *     @arg I2C_FLAG_LOSTARB: Arbitration lost flag (Master mode)
  *     @arg I2C_FLAG_BE: Bus error flag
  * @retval None.
  */
void I2C_ClearBitState(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG)
{
    uint32_t flagpos = 0;

    /* Get the I2C flag position */
    flagpos = I2C_FLAG & STR_FLAG_MASK;
    /* Clear the selected I2C flag */
    I2Cx->STR1 = (uint16_t)~flagpos;
}

/**
  * @brief  Get the interrupt bit flag.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_INT: the interrupt bit flag.
  *   This parameter can be one of the following values:
  *     @arg I2C_INT_SMBALTS: SMBus Alert flag
  *     @arg I2C_INT_SMBTO: Timeout or Tlow error flag
  *     @arg I2C_INT_PECE: PEC error in reception flag
  *     @arg I2C_INT_RXORE: Overrun or Underrun flag (Slave mode)
  *     @arg I2C_INT_AE: Acknowledge failure flag
  *     @arg I2C_INT_LOSTARB: Arbitration lost flag (Master mode)
  *     @arg I2C_INT_BE: Bus error flag
  *     @arg I2C_INT_TBE: Data register empty flag (Transmitter)
  *     @arg I2C_INT_RBNE: Data register not empty (Receiver) flag
  *     @arg I2C_INT_STPSEND: Stop detection flag (Slave mode)
  *     @arg I2C_INT_ADD10SEND: 10-bit header sent flag (Master mode)
  *     @arg I2C_INT_BTC: Byte transfer finished flag
  *     @arg I2C_INT_ADDSEND: Address sent flag (Master mode) or Address matched flag (Slave mode)
  *     @arg I2C_INT_SBSEND: Start bit flag (Master mode)
  * @retval The new value of I2C_INT (SET or RESET).
  */
TypeState I2C_GetIntBitState(I2C_TypeDef *I2Cx, uint32_t I2C_INT)
{
    uint32_t enablestatus = 0;

    /* Check if the interrupt source is enabled or not */
    enablestatus = (uint32_t)(((I2C_INT & INTEN_MASK) >> 16) & (I2Cx->CTLR2)) ;

    /* Get bit[23:0] of the flag */
    I2C_INT &= STR_FLAG_MASK;

    if (((I2Cx->STR1 & I2C_INT) != (uint32_t)RESET) && enablestatus) {
        /* I2C_INT is set */
        return SET;
    } else {
        /* I2C_INT is reset */
        return RESET;
    }
}

/**
  * @brief  Clear the interrupt bit flag.
  * @param  I2Cx: the I2C interface where x can be 1 or 2.
  * @param  I2C_INT: the interrupt bit flag.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_INT_SMBALTS: SMBus Alert interrupt
  *     @arg I2C_INT_SMBTO: Timeout or Tlow error interrupt
  *     @arg I2C_INT_PECE: PEC error in reception  interrupt
  *     @arg I2C_INT_RXORE: Overrun or Underrun interrupt (Slave mode)
  *     @arg I2C_INT_AE: Acknowledge failure interrupt
  *     @arg I2C_INT_LOSTARB: Arbitration lost interrupt (Master mode)
  *     @arg I2C_INT_BE: Bus error interrupt
  * @retval None.
  */
void I2C_ClearIntBitState(I2C_TypeDef *I2Cx, uint32_t I2C_INT)
{
    uint32_t flagpos = 0;

    /* Get the I2C flag position */
    flagpos = I2C_INT & STR_FLAG_MASK;
    /* Clear the selected I2C flag */
    I2Cx->STR1 = (uint16_t)~flagpos;
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

