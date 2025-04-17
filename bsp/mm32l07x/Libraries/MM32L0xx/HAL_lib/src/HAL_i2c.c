/**
******************************************************************************
* @file  HAL_i2c.c
* @author  AE Team
* @version  V2.0.0
* @date  22/08/2017
* @brief  This file provides all the I2C firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2017 MindMotion</center></h2>
*/

/* Includes ------------------------------------------------------------------*/
#include "HAL_i2c.h"
#include "HAL_rcc.h"


/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup I2C
* @brief I2C driver modules
* @{
*/

/** @defgroup I2C_Private_TypesDefinitions
* @{
*/

/**
* @}
*/

/** @defgroup I2C_Private_Defines
* @{
*/

/* I2c Enable disable */
#define IC_ENABLE_Reset         ((uint16_t)0xFFFE)
#define IC_ENABLE_Set           ((uint16_t)0x0001)
#define IC_CON_RESET                        ((uint16_t)0xFE8A)
#define INTR_MASK               ((uint16_t)0xC000)

/* I2c DMA  reset */
#define DMA_CR_TDMAE_RDMAE_Reset ((uint16_t)0xFFFC)

/* I2C START mask */
#define IC_CON_START_Set           ((uint16_t)0x0020)
#define IC_CON_START_Reset         ((uint16_t)0xFFDF)

/* I2C STOP mask */
#define IC_DATA_CMD_STOP_Set     ((uint16_t)0x0200)
#define IC_DATA_CMD_STOP_Reset   ((uint16_t)0xFDFF)

/* I2C ADD2 mask */
#define IC_TAR_Reset         ((uint16_t)0xFF00)

/* I2C IC_10BITADDR_MASTER bit mask */
#define IC_TAR_ENDUAL_Set         ((uint16_t)0x1000)
#define IC_TAR_ENDUAL_Reset       ((uint16_t)0xEFFF)

/* I2C SPECIAL GC_OR_START bits mask */
#define IC_TAR_GC_Set            ((uint16_t)0x0800)
#define IC_TAR_GC_Reset          ((uint16_t)0xF7FF)

/* I2C FLAG mask */
#define FLAG_Mask               ((uint32_t)0x00793FFF)


static uint8_t I2C_CMD_DIR = 0;

uint16_t I2C_DMA_DIR = 0;

/**
* @}
*/

/** @defgroup I2C_Private_Macros
* @{
*/

/**
* @}
*/

/** @defgroup I2C_Private_Variables
* @{
*/

/**
* @}
*/

/** @defgroup I2C_Private_FunctionPrototypes
* @{
*/

/**
* @}
*/

/** @defgroup I2C_Private_Functions
* @{
*/

/**
* @brief  Deinitializes the I2Cx peripheral registers to their default
*   reset values.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @retval : None
*/
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    switch (*(uint32_t*)&I2Cx)
    {
    case I2C1_BASE:
        /* Enable I2C1 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
        /* Release I2C1 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
        break;

    default:
        break;
    }
}

/**
* @brief  Initializes the I2Cx peripheral according to the specified
*   parameters in the I2C_InitStruct.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
*   contains the configuration information for the specified
*   I2C peripheral.
* @retval : None
*/
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{

    uint16_t tmpreg = 0;
    uint32_t pclk1 = 8000000;
    /* uint32_t minSclLowTime = 0; */
    uint32_t i2cPeriod = 0;
    uint32_t pclk1Period = 0;
    RCC_ClocksTypeDef  rcc_clocks;
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
    assert_param(IS_I2C_CLOCK_SPEED(I2C_InitStruct->I2C_ClockSpeed));
    /*---------------------------- I2Cx IC_ENABLE Configuration ------------------------*/
    /* Disable the selected I2C peripheral */
    I2Cx->IC_ENABLE &= IC_ENABLE_Reset;

    /* Get pclk1 frequency value */
    RCC_GetClocksFreq(&rcc_clocks);
    pclk1 = rcc_clocks.PCLK1_Frequency;

    /* Set pclk1 period value */
    pclk1Period = 1000000000/pclk1;

    i2cPeriod = 1000000000/I2C_InitStruct->I2C_ClockSpeed; /*ns unit*/
    tmpreg = 0;
    /* Configure speed in standard mode */
    if (I2C_InitStruct->I2C_ClockSpeed <= 100000)
    {
        tmpreg = (i2cPeriod/pclk1Period)/2;
        I2Cx->IC_SS_SCL_LCNT = tmpreg;
        tmpreg = (i2cPeriod - pclk1Period*I2Cx->IC_SS_SCL_LCNT)/pclk1Period;
        /* Write to I2Cx IC_SS_SCL_HCNT */
        I2Cx->IC_SS_SCL_HCNT = tmpreg;


    }
    else /* (I2C_InitStruct->I2C_ClockSpeed <= 400000) */
    {
        tmpreg = (i2cPeriod/pclk1Period)/2;
        I2Cx->IC_FS_SCL_LCNT = tmpreg;
        tmpreg = (i2cPeriod - pclk1Period*I2Cx->IC_FS_SCL_LCNT)/pclk1Period;
        /* Write to I2Cx IC_FS_SCL_HCNT */
        I2Cx->IC_FS_SCL_HCNT = tmpreg;
    }

    /* Get the I2Cx IC_CON value */
    tmpreg = I2Cx->IC_CON;
    /* Clear TX_EMPTY_CTRL,IC_SLAVE_DISABLE,IC_RESTART_EN,IC_10BITADDR_SLAVE,SPEED,MASTER_MODE bits */
    tmpreg &= IC_CON_RESET;
    /* Set TX_EMPTY_CTRL,IC_SLAVE_DISABLE,IC_RESTART_EN,IC_10BITADDR_SLAVE,SPEED,MASTER_MODE bits */
    tmpreg = TX_EMPTY_CTRL | IC_SLAVE_DISABLE | IC_RESTART_EN |IC_7BITADDR_MASTER | I2C_InitStruct->I2C_Speed | I2C_InitStruct->I2C_Mode;
    /* Write to I2Cx IC_CON */
    I2Cx->IC_CON = tmpreg;

    /*---------------------------- I2Cx IC_INTR_MASK Configuration ------------------------*/
    /* Get the I2Cx IC_INTR_MASK value */
    tmpreg = I2Cx->IC_INTR_MASK;
    /* clear the I2Cx IC_INTR_MASK value */
    tmpreg &= INTR_MASK;
    /* Write to IC_INTR_MASK */
    I2Cx->IC_INTR_MASK = tmpreg;

    /* Write to IC_RX_TL */
    I2Cx->IC_RX_TL = 0x0; /* rxfifo depth is 1 */
    /* Write to IC_TX_TL */
    I2Cx->IC_TX_TL = 0x1; /* tcfifo depth is 1 */

}

/**
* @brief  Fills each I2C_InitStruct member with its default value.
* @param I2C_InitStruct: pointer to an I2C_InitTypeDef structure
*   which will be initialized.
* @retval : None
*/
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
    /*---------------- Reset I2C init structure parameters values ----------------*/
    /* Initialize the I2C_Mode member */
    I2C_InitStruct->I2C_Mode = I2C_Mode_MASTER;
    /* Initialize the I2C_OwnAddress member */
    I2C_InitStruct->I2C_OwnAddress = 0xA8;
    /* Initialize the I2C_Speed member */
    I2C_InitStruct->I2C_Speed = I2C_Speed_STANDARD;
    /* initialize the I2C_ClockSpeed member */
    I2C_InitStruct->I2C_ClockSpeed = 100000;
}

/**
* @brief  Enables or disables the specified I2C peripheral.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param NewState: new state of the I2Cx peripheral. This parameter
*   can be: ENABLE or DISABLE.
* @retval : None
*/
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected I2C peripheral */
        I2Cx->IC_ENABLE |= IC_ENABLE_Set;
    }
    else
    {
        /* Disable the selected I2C peripheral */
        I2Cx->IC_ENABLE &= IC_ENABLE_Reset;
    }
}

/**
* @brief  Enables or disables the specified I2C DMA requests.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param    DMA_Direcction : TDMAE_SET,RDMAE_SET
*   This parameter can be any combination of the following values:
* @arg TDMAE_SET    :DMA TX set
* @arg RDMAE_SET    :DMA RX set
* @param NewState: new state of the I2C DMA transfer.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected I2C DMA requests */
        if(I2C_DMA_DIR==TDMAE_SET)
        {
            /* Enable the selected I2C TX DMA requests */
            I2Cx->IC_DMA_CR |= TDMAE_SET;
        }
        else if(I2C_DMA_DIR==RDMAE_SET)
        {
            /* Enable the selected I2C TX DMA requests */
            I2Cx->IC_DMA_CR |= RDMAE_SET;
        }
    }
    else
    {
        /* Disable the selected I2C DMA requests */
        I2Cx->IC_DMA_CR &= DMA_CR_TDMAE_RDMAE_Reset;
    }
}


/**
* @brief  Generates I2Cx communication START condition.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param NewState: new state of the I2C START condition generation.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None.
*/
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Generate a START condition */
        I2Cx->IC_CON |= IC_CON_START_Set;
    }
    else
    {
        /* Disable the START condition generation */
        I2Cx->IC_CON &= IC_CON_START_Reset;
    }
}

/**
* @brief  Generates I2Cx communication STOP condition.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param NewState: new state of the I2C STOP condition generation.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None.
*/
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    u8 tempReg=0;
    tempReg=tempReg;
    I2Cx->IC_ENABLE |= 0x02;
    while(I2Cx->IC_ENABLE&0x02);
    tempReg = I2Cx->IC_CLR_TX_ABRT;
}

/**
* @brief  Configures the specified I2C own address2.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param Address: specifies the 7bit I2C own address2.
* @retval : None.
*/
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address)
/* void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint16_t Address) */
{
    uint16_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Get the old register value */
    tmpreg = I2Cx->IC_TAR;
    /* Reset I2Cx Own address2 bit [7:0] */
    tmpreg &= IC_TAR_Reset;
    /* Set I2Cx Own address2 */
    tmpreg |= Address>>1;
    /* Store the new register value */
    I2Cx->IC_TAR = tmpreg;
}

/**
* @brief  Enables or disables the specified I2C dual addressing mode.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param NewState: new state of the I2C dual addressing mode.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable dual addressing mode */
        I2Cx->IC_TAR |= IC_TAR_ENDUAL_Set;
    }
    else
    {
        /* Disable dual addressing mode */
        I2Cx->IC_TAR &= IC_TAR_ENDUAL_Reset;
    }
}

/**
* @brief  Enables or disables the specified I2C general call feature.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param NewState: new state of the I2C General call.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable generall call */
        I2Cx->IC_TAR |= IC_TAR_GC_Set;
    }
    else
    {
        /* Disable generall call */
        I2Cx->IC_TAR &= IC_TAR_GC_Reset;
    }
}

/**
* @brief  Enables or disables the specified I2C interrupts.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param I2C_IT: specifies the I2C interrupts sources to be enabled
*   or disabled.
*   This parameter can be any combination of the following values:
* @arg I2C_IT_RX_UNDER: Rx Buffer is empty interrupt mask
* @arg I2C_IT_RX_OVER : RX  Buffer Overrun interrupt mask
* @arg I2C_IT_RX_FULL : Rx buffer full interrupt mask
* @arg I2C_IT_TX_OVER : TX  Buffer Overrun interrupt mask
* @arg I2C_IT_TX_EMPTY  : TX_FIFO empty interrupt mask
* @arg I2C_IT_RD_REQ    : I2C work as slave or master interrupt mask
* @arg I2C_IT_TX_ABRT   : TX error interrupt  mask(Master mode)
* @arg I2C_IT_RX_DONE   : Master not ack interrupt mask(slave mode)
* @arg I2C_IT_ACTIVITY  : I2C activity interrupt mask
* @arg I2C_IT_STOP_DET  : stop condition  interrupt mask
* @arg I2C_IT_START_DET : start condition  interrupt mask
* @arg I2C_IT_GEN_CALL  : a general call address and ack interrupt mask
* @param NewState: new state of the specified I2C interrupts.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_I2C_CONFIG_IT(I2C_IT));

    if(I2C_IT == I2C_IT_RX_FULL)
    {
        I2Cx->IC_DATA_CMD = CMD_READ;
    }

    if (NewState != DISABLE)
    {
        /* Enable the selected I2C interrupts */
        I2Cx->IC_INTR_MASK |= I2C_IT;
    }
    else
    {
        /* Disable the selected I2C interrupts */
        I2Cx->IC_INTR_MASK &= (uint16_t)~I2C_IT;
    }
}

/**
* @brief  Sends a data byte through the I2Cx peripheral.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param Data: Byte to be transmitted..
* @retval : None
*/
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Write in the IC_DATA_CMD register the data to be sent */
    I2Cx->IC_DATA_CMD = CMD_WRITE | Data;
}

/**
* @brief  Sends last data byte through the I2Cx peripheral.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param Data: Byte to be transmitted..
* @retval : None
*/
void I2C_SendLastDataOrStop(I2C_TypeDef* I2Cx, uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Write in the IC_DATA_CMD register the data to be sent */
    I2Cx->IC_DATA_CMD = 0x200 | Data;
}

/**
* @brief  Read last data byte through the I2Cx peripheral.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param Data: Byte to be Recieved..
* @retval : None
*/
uint8_t I2C_ReadLastDataOrStop(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Write in the IC_DATA_CMD register the data to be sent */
    I2Cx->IC_DATA_CMD = 0x300 ;
    return 0;
}
/**
* @brief  Returns the most recent received data by the I2Cx peripheral.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @retval : The value of the received data.

*/
void I2C_ReadCmd(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    I2Cx->IC_DATA_CMD = CMD_READ;
}

/**
* @brief  Returns the most recent received data by the I2Cx peripheral.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @retval : The value of the received data.
*/
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    I2C_CMD_DIR= 0;
    /* Return the data in the IC_DATA_CMD register */
    return (uint8_t)I2Cx->IC_DATA_CMD;
}

/**
* @brief  Transmits the address byte to select the slave device.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param Address: specifies the slave address which will be transmitted
* @param I2C_Direction: specifies whether the I2C device will be a
*   Transmitter or a Receiver.
*   This parameter can be one of the following values
* @arg I2C_Direction_Transmitter: Transmitter mode
* @arg I2C_Direction_Receiver: Receiver mode
* @retval : None.
*/
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
    /* Store the new register value */
    I2Cx->IC_TAR = Address>>1;
}

/**
* @brief  Reads the specified I2C register and returns its value.
* @param I2C_Register: specifies the register to read.
*   This parameter can be one of the following values:
* @retval : The value of the read register.
*/
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_REGISTER(I2C_Register));
    /* Return the selected register value */
    return (*(__IO uint16_t *)(*((__IO uint32_t *)&I2Cx) + I2C_Register));
}

/**
* @brief  Returns the last I2Cx Event.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @retval : The last event
*/
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx)
{
    uint32_t lastevent = 0;
    uint32_t flag1 = 0;
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Read the I2Cx status register */
    flag1 = I2Cx->IC_RAW_INTR_STAT;

    /* Get the last event value from I2C status register */
    lastevent = (flag1 ) & FLAG_Mask;
    /* Return status */
    return lastevent;
}



/**
* @brief  Checks whether the last I2Cx Event is equal to the one passed
*   as parameter.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param I2C_EVENT: specifies the event to be checked.
*   This parameter can be one of the following values:
* @arg I2C_EVENT_RX_UNDER: Rx Buffer is empty event
* @arg I2C_EVENT_RX_OVER : RX  Buffer Overrun event
* @arg I2C_EVENTT_RX_FULL : Rx buffer full event
* @arg I2C_EVENT_TX_OVER : TX  Buffer Overrun event
* @arg I2C_EVENT_TX_EMPTY   : TX_FIFO empty event
* @arg I2C_EVENT_RD_REQ : I2C work as slave or master event
* @arg I2C_EVENT_TX_ABRT    : TX error event(Master mode)
* @arg I2C_EVENT_RX_DONE    : Master not ack event(slave mode)
* @arg I2C_EVENT_ACTIVITY   : I2C activity event
* @arg I2C_EVENT_STOP_DET   : stop condition  event
* @arg I2C_EVENT_START_DET  : start condition  event
* @arg I2C_EVENT_GEN_CALL   : a general call address and ack event
* - SUCCESS: Last event is equal to the I2C_EVENT
* - ERROR: Last event is different from the I2C_EVENT
*/
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
    uint32_t lastevent = 0;
    uint32_t flag1 = 0;
    ErrorStatus status = ERROR;
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_EVENT(I2C_EVENT));

    if((I2C_EVENT == I2C_EVENT_RX_FULL)&&(I2C_CMD_DIR==0))
    {
        I2Cx->IC_DATA_CMD = CMD_READ;
        I2C_CMD_DIR = 1;
    }
    /* Read the I2Cx status register */
    flag1 = I2Cx->IC_RAW_INTR_STAT;
    /* flag1 = I2Cx->IC_INTR_STAT; */
    /* Get the last event value from I2C status register */
    lastevent = (flag1 ) & I2C_EVENT;

    /* Check whether the last event is equal to I2C_EVENT */
    if (lastevent == I2C_EVENT )
        /* if((I2Cx->IC_RAW_INTR_STAT & I2C_EVENT) != (uint32_t)RESET) */
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
* @brief  Checks whether the specified I2C flag is set or not.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param I2C_FLAG: specifies the flag to check.
*   This parameter can be one of the following values:
* @arg I2C_FLAG_RX_UNDER: Rx Buffer is empty flag
* @arg I2C_FLAG_RX_OVER : RX  Buffer Overrun flag
* @arg I2C_FLAG_RX_FULL : Rx buffer full flag
* @arg I2C_FLAG_TX_OVER : TX  Buffer Overrun flag
* @arg I2C_FLAG_TX_EMPTY: TX_FIFO empty flag
* @arg I2C_FLAG_RD_REQ  : I2C work as slave or master flag
* @arg I2C_FLAG_TX_ABRT : TX error flag(Master mode)
* @arg I2C_FLAG_RX_DONE : Master not ack flag(slave mode)
* @arg I2C_FLAG_ACTIVITY: I2C activity flag
* @arg I2C_FLAG_STOP_DET: stop condition  flag
* @arg I2C_FLAG_START_DET: start condition  flag
* @arg I2C_FLAG_GEN_CALL : a general call address and ack flag
* @arg I2C_STATUS_FLAG_ACTIVITY
* @arg I2C_STATUS_FLAG_TFNF
* @arg I2C_STATUS_FLAG_TFE
* @arg I2C_STATUS_FLAG_RFNE
* @arg I2C_STATUS_FLAG_RFF
* @arg I2C_STATUS_FLAG_M_ACTIVITY
* @arg I2C_STATUS_FLAG_S_ACTIVITY
* @retval : The new state of I2C_FLAG (SET or RESET).
*/
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
    FlagStatus bitstatus = RESET;
    __IO uint32_t i2creg = 0, i2cxbase = 0;
    ((void)i2creg);
    ((void)i2cxbase);

    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_GET_FLAG(I2C_FLAG));

    if(I2C_FLAG & 0x8000)
    {
        if((I2Cx->IC_STATUS & I2C_FLAG) != (uint32_t)RESET)
        {
            /* I2C_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* I2C_FLAG is reset */
            bitstatus = RESET;
        }
    }
    else
    {
        if((I2C_FLAG == I2C_FLAG_RX_FULL)&&(I2C_CMD_DIR==0))
        {
            I2Cx->IC_DATA_CMD = CMD_READ;
            I2C_CMD_DIR = 1;
        }
        /* Check the status of the specified I2C flag */
        if((I2Cx->IC_RAW_INTR_STAT & I2C_FLAG) != (uint32_t)RESET)
        {
            /* I2C_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* I2C_FLAG is reset */
            bitstatus = RESET;
        }
    }
    /* Return the I2C_FLAG status */
    return  bitstatus;
}

/**
* @brief  Clears the I2Cx's pending flags.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param I2C_FLAG: specifies the flag to clear.
*   This parameter can be any combination of the following values:
* @arg I2C_FLAG_RX_UNDER: Rx Buffer is empty flag
* @arg I2C_FLAG_RX_OVER : RX  Buffer Overrun flag
* @arg I2C_FLAG_RX_FULL : Rx buffer full flag
* @arg I2C_FLAG_TX_OVER : TX  Buffer Overrun flag
* @arg I2C_FLAG_TX_EMPTY: TX_FIFO empty flag
* @arg I2C_FLAG_RD_REQ  : I2C work as slave or master flag
* @arg I2C_FLAG_TX_ABRT : TX error flag(Master mode)
* @arg I2C_FLAG_RX_DONE : Master not ack flag(slave mode)
* @arg I2C_FLAG_ACTIVITY: I2C activity flag
* @arg I2C_FLAG_STOP_DET: stop condition  flag
* @arg I2C_FLAG_START_DET: start condition  flag
* @arg I2C_FLAG_GEN_CALL : a general call address and ack flag
* @retval : None
*/
void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));

    if((I2C_FLAG & I2C_FLAG_RX_UNDER)   == I2C_FLAG_RX_UNDER)
    {((void)I2Cx->IC_CLR_RX_UNDER);}
    if((I2C_FLAG & I2C_FLAG_RX_OVER)    == I2C_FLAG_RX_OVER)
    {((void)I2Cx->IC_CLR_RX_OVER);}
    if((I2C_FLAG & I2C_FLAG_TX_OVER)    == I2C_FLAG_TX_OVER)
    {((void)I2Cx->IC_CLR_TX_OVER);}
    if((I2C_FLAG & I2C_FLAG_RD_REQ)     == I2C_FLAG_RD_REQ)
    {((void)I2Cx->IC_CLR_RD_REQ);}
    if((I2C_FLAG & I2C_FLAG_TX_ABRT)    == I2C_FLAG_TX_ABRT)
    {((void)I2Cx->IC_CLR_TX_ABRT);}
    if((I2C_FLAG & I2C_FLAG_RX_DONE)    == I2C_FLAG_RX_DONE)
    {((void)I2Cx->IC_CLR_RX_DONE);}
    if((I2C_FLAG & I2C_FLAG_ACTIVITY)   == I2C_FLAG_ACTIVITY)
    {((void)I2Cx->IC_CLR_ACTIVITY);}
    if((I2C_FLAG & I2C_FLAG_STOP_DET)   == I2C_FLAG_STOP_DET)
    {((void)I2Cx->IC_CLR_STOP_DET);}
    if((I2C_FLAG & I2C_FLAG_START_DET)  == I2C_FLAG_START_DET)
    {((void)I2Cx->IC_CLR_START_DET);}
    if((I2C_FLAG & I2C_FLAG_GEN_CALL)   == I2C_FLAG_GEN_CALL)
    {((void)I2Cx->IC_CLR_GEN_CALL);}
}

/**
* @brief  Checks whether the specified I2C interrupt has occurred or not.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param I2C_IT: specifies the interrupt source to check.
*   This parameter can be one of the following values:
* @arg I2C_IT_RX_UNDER: Rx Buffer is empty interrupt
* @arg I2C_IT_RX_OVER : RX  Buffer Overrun interrupt
* @arg I2C_IT_RX_FULL : Rx buffer full interrupt
* @arg I2C_IT_TX_OVER : TX  Buffer Overrun interrupt
* @arg I2C_IT_TX_EMPTY  : TX_FIFO empty interrupt
* @arg I2C_IT_RD_REQ    : I2C work as slave or master interrupt
* @arg I2C_IT_TX_ABRT   : TX error interrupt  (Master mode)
* @arg I2C_IT_RX_DONE   : Master not ack interrupt (slave mode)
* @arg I2C_IT_ACTIVITY  : I2C activity interrupt
* @arg I2C_IT_STOP_DET  : stop condition  interrupt
* @arg I2C_IT_START_DET : start condition  interrupt
* @arg I2C_IT_GEN_CALL  : a general call address and ack interrupt
* @retval : The new state of I2C_IT (SET or RESET).
*/
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
    ITStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_GET_IT(I2C_IT));

    /* Check the status of the specified I2C flag */
    if((I2Cx->IC_RAW_INTR_STAT & I2C_IT) != (uint32_t)RESET)
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
    return  bitstatus;
}

/**
* @brief  Clears the I2Cx interrupt pending bits.
* @param I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param I2C_IT: specifies the interrupt pending bit to clear.
*   This parameter can be any combination of the following values:
* @arg I2C_IT_RX_UNDER: Rx Buffer is empty interrupt
* @arg I2C_IT_RX_OVER : RX  Buffer Overrun interrupt
* @arg I2C_IT_RX_FULL : Rx buffer full interrupt
* @arg I2C_IT_TX_OVER : TX  Buffer Overrun interrupt
* @arg I2C_IT_TX_EMPTY  : TX_FIFO empty interrupt
* @arg I2C_IT_RD_REQ    : I2C work as slave or master interrupt
* @arg I2C_IT_TX_ABRT   : TX error interrupt  (Master mode)
* @arg I2C_IT_RX_DONE   : Master not ack interrupt (slave mode)
* @arg I2C_IT_ACTIVITY  : I2C activity interrupt
* @arg I2C_IT_STOP_DET  : stop condition  interrupt
* @arg I2C_IT_START_DET : start condition  interrupt
* @arg I2C_IT_GEN_CALL  : a general call address and ack interrupt
* @retval : None
*/
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLEAR_IT(I2C_IT));

    /* Clear the selected I2C flag */

    if((I2C_IT & I2C_IT_RX_UNDER)   == I2C_FLAG_RX_UNDER)
    {((void)I2Cx->IC_CLR_RX_UNDER);}
    if((I2C_IT & I2C_IT_RX_OVER)    == I2C_FLAG_RX_OVER)
    {((void)I2Cx->IC_CLR_RX_OVER);}
    if((I2C_IT & I2C_IT_TX_OVER)    == I2C_FLAG_TX_OVER)
    {((void)I2Cx->IC_CLR_TX_OVER);}
    if((I2C_IT & I2C_IT_RD_REQ)     == I2C_FLAG_RD_REQ)
    {((void)I2Cx->IC_CLR_RD_REQ);}
    if((I2C_IT & I2C_IT_TX_ABRT)    == I2C_FLAG_TX_ABRT)
    {((void)I2Cx->IC_CLR_TX_ABRT);}
    if((I2C_IT & I2C_IT_RX_DONE)    == I2C_FLAG_RX_DONE)
    {((void)I2Cx->IC_CLR_RX_DONE);}
    if((I2C_IT & I2C_IT_ACTIVITY)   == I2C_FLAG_ACTIVITY)
    {((void)I2Cx->IC_CLR_ACTIVITY);}
    if((I2C_IT & I2C_IT_STOP_DET)   == I2C_FLAG_STOP_DET)
    {((void)I2Cx->IC_CLR_STOP_DET);}
    if((I2C_IT & I2C_IT_START_DET)  == I2C_FLAG_START_DET)
    {((void)I2Cx->IC_CLR_START_DET);}
    if((I2C_IT & I2C_IT_GEN_CALL)   == I2C_FLAG_GEN_CALL)
    {((void)I2Cx->IC_CLR_GEN_CALL);}

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

/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
