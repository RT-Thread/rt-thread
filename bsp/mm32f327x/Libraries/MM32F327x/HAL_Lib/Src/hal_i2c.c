////////////////////////////////////////////////////////////////////////////////
/// @file     hal_i2c.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE I2C FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _HAL_I2C_C_

// Files includes
#include "hal_i2c.h"
#include "hal_rcc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup I2C_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup I2C_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the i2c peripheral registers to their default
///         reset values.
/// @param  i2c: where n can be 1 or 2 to select the I2C peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_DeInit(I2C_TypeDef* i2c)
{
    switch (*(vu32*)&i2c) {
        case (u32)I2C1:  // I2C1_BASE:
            exRCC_APB1PeriphReset(RCC_APB1ENR_I2C1);
            break;
        case (u32)I2C2:  // I2C2_BASE:
            exRCC_APB1PeriphReset(RCC_APB1ENR_I2C2);
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the i2c peripheral according to the specified
///         parameters in the init_struct.
/// @param  i2c: select the I2C peripheral.
/// @param  init_struct: pointer to a I2C_InitTypeDef structure that
///         contains the configuration information for the specified
///         I2C peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_Init(I2C_TypeDef* i2c, I2C_InitTypeDef* init_struct)
{
    u32 pclk1         = HSI_VALUE;
    u32 minSclLowTime = 0;
    u32 i2cPeriod     = 0;
    u32 pclk1Period   = 0;


    i2c->IC_ENABLE &= ~I2C_ENR_ENABLE;


    pclk1       = RCC_GetPCLK1Freq();
    pclk1Period = 1000000000 / pclk1;
    i2cPeriod   = 1000000000 / init_struct->I2C_ClockSpeed;

    minSclLowTime = pclk1 / init_struct->I2C_ClockSpeed ;
    i2cPeriod = 82 / pclk1Period;

    if (init_struct->I2C_ClockSpeed <= 100000) {
        i2c->IC_SS_SCL_LCNT = (minSclLowTime - 13 - i2cPeriod) / 2;
        i2c->IC_SS_SCL_HCNT = (minSclLowTime - 13 - i2cPeriod - i2c->IC_SS_SCL_LCNT);
    }
    else {
        i2c->IC_FS_SCL_LCNT = (minSclLowTime - 13 - i2cPeriod ) / 2 + 4;
        i2c->IC_FS_SCL_HCNT = (minSclLowTime - 13 - i2c->IC_FS_SCL_LCNT - i2cPeriod);
    }

    i2c->IC_CON &= ~(I2C_CR_EMPINT     |   \
                     I2C_CR_SLAVEDIS   |   \
                     I2C_CR_REPEN      |   \
                     I2C_CR_MASTER10   |   \
                     I2C_CR_SLAVE10    |   \
                     I2C_CR_FAST       |   \
                     I2C_CR_MASTER);

    i2c->IC_CON =  I2C_CR_EMPINT       |   \
                   I2C_CR_REPEN        |   \
                   ((init_struct->I2C_Speed == I2C_CR_FAST) ? I2C_CR_FAST : I2C_CR_STD) | \
                   ((init_struct->I2C_Mode)  ? I2C_CR_MASTER : 0x00);
    i2c->IC_INTR_MASK &= INTR_MASK;

    i2c->IC_RX_TL = 0x00;
    i2c->IC_TX_TL = 0x00;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each init_struct member with its default value.
/// @param  init_struct: pointer to an I2C_InitTypeDef structure
///         which will be initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_StructInit(I2C_InitTypeDef* init_struct)
{
    init_struct->I2C_Mode       = I2C_CR_MASTER;
    init_struct->I2C_OwnAddress = I2C_OWN_ADDRESS;
    init_struct->I2C_Speed      = I2C_CR_STD;
    init_struct->I2C_ClockSpeed = 100000;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified I2C peripheral.
/// @param  i2c: select the I2C peripheral.
/// @param  state: new state of the i2c peripheral. This parameter
///         can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_Cmd(I2C_TypeDef* i2c, FunctionalState state)
{
    (state) ? (i2c->IC_ENABLE |= I2C_ENR_ENABLE) : (i2c->IC_ENABLE &= ~I2C_ENR_ENABLE);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified I2C DMA requests.
/// @param  i2c: select the I2C peripheral.
/// @param  state: new state of the I2C DMA transfer.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_DMACmd(I2C_TypeDef* i2c, FunctionalState state)
{
    if (state) {
        if (I2C_DMA_DIR == TDMAE_SET)
            i2c->IC_DMA_CR |= TDMAE_SET;

        else
            i2c->IC_DMA_CR |= RDMAE_SET;
    }
    else
        i2c->IC_DMA_CR &= ~(I2C_DMA_RXEN | I2C_DMA_TXEN);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Generates i2c communication START condition.
/// @param  i2c: select the I2C peripheral.
/// @param  state: new state of the I2C START condition generation.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_GenerateSTART(I2C_TypeDef* i2c, FunctionalState state)
{
    (state) ? (i2c->IC_CON |= I2C_CR_REPEN) : (i2c->IC_CON &= ~I2C_CR_REPEN);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Generates i2c communication STOP condition.
/// @param  i2c: select the I2C peripheral.
/// @param  state: new state of the I2C STOP condition generation.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_GenerateSTOP(I2C_TypeDef* i2c, FunctionalState state)
{
    u16 overTime = 3000;

    i2c->IC_ENABLE |= I2C_ENR_ABORT;

    while (i2c->IC_ENABLE & I2C_ENR_ABORT) {
        if (overTime-- == 0)
            break;
    }
    i2c->IC_CLR_TX_ABRT;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the specified I2C own address2.
/// @param  i2c: select the I2C peripheral.
/// @param  addr: specifies the 7bit I2C own address2.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_OwnAddress2Config(I2C_TypeDef* i2c, u8 addr)
{
    MODIFY_REG(i2c->IC_TAR, (u16)I2C_TAR_ADDR, (u16)(addr >> 1));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified I2C dual addressing mode.
/// @param  i2c: select the I2C peripheral.
/// @param  state: new state of the I2C dual addressing mode.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_DualAddressCmd(I2C_TypeDef* i2c, FunctionalState state)
{
    (state) ? (i2c->IC_TAR |= IC_TAR_ENDUAL_Set) : (i2c->IC_TAR &= IC_TAR_ENDUAL_Reset);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified I2C general call feature.
/// @param  i2c: select the I2C peripheral.
/// @param  state: new state of the I2C General call.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_GeneralCallCmd(I2C_TypeDef* i2c, FunctionalState state)
{
    (state) ? (i2c->IC_TAR |= I2C_TAR_SPECIAL) : (i2c->IC_TAR &= ~I2C_TAR_SPECIAL);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified I2C interrupts.
/// @param  i2c: select the I2C peripheral.
/// @param  it: specifies the I2C interrupts sources to be enabled
///         or disabled.
///         This parameter can be any combination of the following values:
/// @arg    I2C_IT_RX_UNDER   : Rx Buffer is empty interrupt mask
/// @arg    I2C_IT_RX_OVER    : RX  Buffer Overrun interrupt mask
/// @arg    I2C_IT_RX_FULL    : Rx buffer full interrupt mask
/// @arg    I2C_IT_TX_OVER    : TX  Buffer Overrun interrupt mask
/// @arg    I2C_IT_TX_EMPTY   : TX_FIFO empty interrupt mask
/// @arg    I2C_IT_RD_REQ     : I2C work as slave or master interrupt mask
/// @arg    I2C_IT_TX_ABRT    : TX error interrupt  mask(Master mode)
/// @arg    I2C_IT_RX_DONE    : Master not ack interrupt mask(slave mode)
/// @arg    I2C_IT_ACTIVITY   : I2C activity interrupt mask
/// @arg    I2C_IT_STOP_DET   : stop condition  interrupt mask
/// @arg    I2C_IT_START_DET  : start condition  interrupt mask
/// @arg    I2C_IT_GEN_CALL   : a general call address and ack interrupt mask
/// @param  state: new state of the specified I2C interrupts.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_ITConfig(I2C_TypeDef* i2c, u16 it, FunctionalState state)
{
    if (it == I2C_IT_RX_FULL)
        I2C_ReadCmd(i2c);
    (state) ? SET_BIT(i2c->IC_INTR_MASK, it) : CLEAR_BIT(i2c->IC_INTR_MASK, (u16)it);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sends a data byte through the i2c peripheral.
/// @param  i2c: select the I2C peripheral.
/// @param  dat: Byte to be transmitted..
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_SendData(I2C_TypeDef* i2c, u8 dat)
{
    i2c->IC_DATA_CMD = dat;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the most recent received data by the i2c peripheral.
/// @param  i2c: select the I2C peripheral.
/// @retval The value of the received data.
////////////////////////////////////////////////////////////////////////////////
void I2C_ReadCmd(I2C_TypeDef* i2c)
{
    i2c->IC_DATA_CMD = I2C_DR_CMD;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the most recent received data by the i2c peripheral.
/// @param  i2c: select the I2C peripheral.
/// @retval The value of the received data.
////////////////////////////////////////////////////////////////////////////////
u8 I2C_ReceiveData(I2C_TypeDef* i2c)
{
    I2C_CMD_DIR = 0;
    return (u8)i2c->IC_DATA_CMD;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Transmits the address byte to select the slave device.
/// @param  i2c: select the I2C peripheral.
/// @param  addr: specifies the slave address which will be transmitted
/// @param  dir: specifies whether the I2C device will be a
///   Transmitter or a Receiver.
///   This parameter can be one of the following values
/// @arg  I2C_Direction_Transmitter: Transmitter mode
/// @arg  I2C_Direction_Receiver: Receiver mode
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_Send7bitAddress(I2C_TypeDef* i2c, u8 addr, u8 dir)
{
    i2c->IC_TAR = addr >> 1;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads the specified I2C register and returns its value.
/// @param  i2c: select the I2C peripheral.
/// @param  reg: specifies the register to read.
///         This parameter can be one of the following values:
/// @retval The value of the read register.
////////////////////////////////////////////////////////////////////////////////
u16 I2C_ReadRegister(I2C_TypeDef* i2c, u8 reg)
{
    return (*(vu16*)(*((u32*)&i2c) + reg));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the last i2c Event.
/// @param  i2c: select the I2C peripheral.
/// @retval The last event
////////////////////////////////////////////////////////////////////////////////
u32 I2C_GetLastEvent(I2C_TypeDef* i2c)
{
    return (u32)i2c->IC_RAW_INTR_STAT & FLAG_Mask;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the last i2c Event is equal to the one passed
///   as parameter.
/// @param  i2c: select the I2C peripheral.
/// @param  event: specifies the event to be checked.
///   This parameter can be one of the following values:
/// @arg  I2C_EVENT_RX_UNDER : Rx Buffer is empty event
/// @arg  I2C_EVENT_RX_OVER  : RX  Buffer Overrun event
/// @arg  I2C_EVENTT_RX_FULL : Rx buffer full event
/// @arg  I2C_EVENT_TX_OVER  : TX  Buffer Overrun event
/// @arg  I2C_EVENT_TX_EMPTY : TX_FIFO empty event
/// @arg  I2C_EVENT_RD_REQ   : I2C work as slave or master event
/// @arg  I2C_EVENT_TX_ABRT  : TX error event(Master mode)
/// @arg  I2C_EVENT_RX_DONE  : Master not ack event(slave mode)
/// @arg  I2C_EVENT_ACTIVITY : I2C activity event
/// @arg  I2C_EVENT_STOP_DET : stop condition  event
/// @arg  I2C_EVENT_START_DET: start condition  event
/// @arg  I2C_EVENT_GEN_CALL : a general call address and ack event
/// - SUCCESS: Last event is equal to the I2C_EVENT
/// - ERROR: Last event is different from the I2C_EVENT
////////////////////////////////////////////////////////////////////////////////
ErrorStatus I2C_CheckEvent(I2C_TypeDef* i2c, u32 event)
{
    if ((event == I2C_EVENT_RX_FULL) && (I2C_CMD_DIR == 0)) {
        i2c->IC_DATA_CMD = I2C_DR_CMD;
        I2C_CMD_DIR       = 1;
    }

    return (ErrorStatus)((i2c->IC_RAW_INTR_STAT & event) == event);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified I2C flag is set or not.
/// @param  i2c: select the I2C peripheral.
/// @param  flag: specifies the flag to check.
///   This parameter can be one of the following values:
/// @arg  I2C_FLAG_RX_UNDER : Rx Buffer is empty flag
/// @arg  I2C_FLAG_RX_OVER  : RX  Buffer Overrun flag
/// @arg  I2C_FLAG_RX_FULL  : Rx buffer full flag
/// @arg  I2C_FLAG_TX_OVER  : TX  Buffer Overrun flag
/// @arg  I2C_FLAG_TX_EMPTY : TX_FIFO empty flag
/// @arg  I2C_FLAG_RD_REQ   : I2C work as slave or master flag
/// @arg  I2C_FLAG_TX_ABRT  : TX error flag(Master mode)
/// @arg  I2C_FLAG_RX_DONE  : Master not ack flag(slave mode)
/// @arg  I2C_FLAG_ACTIVITY : I2C activity flag
/// @arg  I2C_FLAG_STOP_DET : stop condition  flag
/// @arg  I2C_FLAG_START_DET: start condition  flag
/// @arg  I2C_FLAG_GEN_CALL : a general call address and ack flag
/// @retval The new state of I2C_FLAG (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* i2c, u32 flag)
{
    if (flag & 0x8000)
        return ((i2c->IC_STATUS & flag) ? SET : RESET);

    if ((flag == I2C_FLAG_RX_FULL) && (I2C_CMD_DIR == 0)) {
        i2c->IC_DATA_CMD = I2C_DR_CMD;
        I2C_CMD_DIR       = 1;
    }
    return (((i2c->IC_RAW_INTR_STAT & flag)) ? SET : RESET);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the i2c's pending flags.
/// @param  i2c: select the I2C peripheral.
/// @param  flag: specifies the flag to clear.
///   This parameter can be any combination of the following values:
/// @arg  I2C_FLAG_RX_UNDER : Rx Buffer is empty flag
/// @arg  I2C_FLAG_RX_OVER  : RX  Buffer Overrun flag
/// @arg  I2C_FLAG_RX_FULL  : Rx buffer full flag
/// @arg  I2C_FLAG_TX_OVER  : TX  Buffer Overrun flag
/// @arg  I2C_FLAG_TX_EMPTY : TX_FIFO empty flag
/// @arg  I2C_FLAG_RD_REQ   : I2C work as slave or master flag
/// @arg  I2C_FLAG_TX_ABRT  : TX error flag(Master mode)
/// @arg  I2C_FLAG_RX_DONE  : Master not ack flag(slave mode)
/// @arg  I2C_FLAG_ACTIVITY : I2C activity flag
/// @arg  I2C_FLAG_STOP_DET : stop condition  flag
/// @arg  I2C_FLAG_START_DET: start condition  flag
/// @arg  I2C_FLAG_GEN_CALL : a general call address and ack flag
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_ClearFlag(I2C_TypeDef* i2c, u32 flag)
{
    if ((flag & I2C_FLAG_RX_UNDER) == I2C_FLAG_RX_UNDER)
        i2c->IC_CLR_RX_UNDER;
    if ((flag & I2C_FLAG_RX_OVER) == I2C_FLAG_RX_OVER)
        i2c->IC_CLR_RX_OVER;
    if ((flag & I2C_FLAG_TX_OVER) == I2C_FLAG_TX_OVER)
        i2c->IC_CLR_TX_OVER;
    if ((flag & I2C_FLAG_RD_REQ) == I2C_FLAG_RD_REQ)
        i2c->IC_CLR_RD_REQ;
    if ((flag & I2C_FLAG_TX_ABRT) == I2C_FLAG_TX_ABRT)
        i2c->IC_CLR_TX_ABRT;
    if ((flag & I2C_FLAG_RX_DONE) == I2C_FLAG_RX_DONE)
        i2c->IC_CLR_RX_DONE;
    if ((flag & I2C_FLAG_ACTIVITY) == I2C_FLAG_ACTIVITY)
        i2c->IC_CLR_ACTIVITY;
    if ((flag & I2C_FLAG_STOP_DET) == I2C_FLAG_STOP_DET)
        i2c->IC_CLR_STOP_DET;
    if ((flag & I2C_FLAG_START_DET) == I2C_FLAG_START_DET)
        i2c->IC_CLR_START_DET;
    if ((flag & I2C_FLAG_GEN_CALL) == I2C_FLAG_GEN_CALL)
        i2c->IC_CLR_GEN_CALL;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified I2C interrupt has occurred or not.
/// @param  i2c: select the I2C peripheral.
/// @param  it: specifies the interrupt source to check.
///   This parameter can be one of the following values:
/// @arg  I2C_IT_RX_UNDER : Rx Buffer is empty interrupt
/// @arg  I2C_IT_RX_OVER  : RX  Buffer Overrun interrupt
/// @arg  I2C_IT_RX_FULL  : Rx buffer full interrupt
/// @arg  I2C_IT_TX_OVER  : TX  Buffer Overrun interrupt
/// @arg  I2C_IT_TX_EMPTY : TX_FIFO empty interrupt
/// @arg  I2C_IT_RD_REQ   : I2C work as slave or master interrupt
/// @arg  I2C_IT_TX_ABRT  : TX error interrupt  (Master mode)
/// @arg  I2C_IT_RX_DONE  : Master not ack interrupt (slave mode)
/// @arg  I2C_IT_ACTIVITY : I2C activity interrupt
/// @arg  I2C_IT_STOP_DET : stop condition  interrupt
/// @arg  I2C_IT_START_DET: start condition  interrupt
/// @arg  I2C_IT_GEN_CALL : a general call address and ack interrupt
/// @retval The new state of I2C_IT (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
ITStatus I2C_GetITStatus(I2C_TypeDef* i2c, u32 it)
{
    return ((i2c->IC_RAW_INTR_STAT & it) ? SET : RESET);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the i2c interrupt pending bits.
/// @param  i2c: select the I2C peripheral.
/// @param  it: specifies the interrupt pending bit to clear.
///   This parameter can be any combination of the following values:
/// @arg  I2C_IT_RX_UNDER : Rx Buffer is empty interrupt
/// @arg  I2C_IT_RX_OVER  : RX  Buffer Overrun interrupt
/// @arg  I2C_IT_RX_FULL  : Rx buffer full interrupt
/// @arg  I2C_IT_TX_OVER  : TX  Buffer Overrun interrupt
/// @arg  I2C_IT_TX_EMPTY : TX_FIFO empty interrupt
/// @arg  I2C_IT_RD_REQ   : I2C work as slave or master interrupt
/// @arg  I2C_IT_TX_ABRT  : TX error interrupt  (Master mode)
/// @arg  I2C_IT_RX_DONE  : Master not ack interrupt (slave mode)
/// @arg  I2C_IT_ACTIVITY : I2C activity interrupt
/// @arg  I2C_IT_STOP_DET : stop condition  interrupt
/// @arg  I2C_IT_START_DET: start condition  interrupt
/// @arg  I2C_IT_GEN_CALL : a general call address and ack interrupt
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_ClearITPendingBit(I2C_TypeDef* i2c, u32 it)
{
    if ((it & I2C_IT_RX_UNDER) == I2C_FLAG_RX_UNDER)
        i2c->IC_CLR_RX_UNDER;
    if ((it & I2C_IT_RX_OVER) == I2C_FLAG_RX_OVER)
        i2c->IC_CLR_RX_OVER;
    if ((it & I2C_IT_TX_OVER) == I2C_FLAG_TX_OVER)
        i2c->IC_CLR_TX_OVER;
    if ((it & I2C_IT_RD_REQ) == I2C_FLAG_RD_REQ)
        i2c->IC_CLR_RD_REQ;
    if ((it & I2C_IT_TX_ABRT) == I2C_FLAG_TX_ABRT)
        i2c->IC_CLR_TX_ABRT;
    if ((it & I2C_IT_RX_DONE) == I2C_FLAG_RX_DONE)
        i2c->IC_CLR_RX_DONE;
    if ((it & I2C_IT_ACTIVITY) == I2C_FLAG_ACTIVITY)
        i2c->IC_CLR_ACTIVITY;
    if ((it & I2C_IT_STOP_DET) == I2C_FLAG_STOP_DET)
        i2c->IC_CLR_STOP_DET;
    if ((it & I2C_IT_START_DET) == I2C_FLAG_START_DET)
        i2c->IC_CLR_START_DET;
    if ((it & I2C_IT_GEN_CALL) == I2C_FLAG_GEN_CALL)
        i2c->IC_CLR_GEN_CALL;
}

////////////////////////////////////////////////////////////////////////////////
//
//  New Function Interface
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures slave address.
/// @param  i2c: select the I2C peripheral.
/// @param  addr: specifies the slave address which will be transmitted
///   This parameter can be one of the following values
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_SendSlaveAddress(I2C_TypeDef* i2c, u8 addr)
{
    WRITE_REG(i2c->IC_SAR, addr >> 1);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the I2C slave mode.
/// @param  i2c: select the I2C peripheral.
/// @param  state: new state of the specified I2C interrupts.
///   This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void I2C_SlaveConfigure(I2C_TypeDef* i2c, FunctionalState state)
{
    (state) ? CLEAR_BIT(i2c->IC_CON, I2C_CR_SLAVEDIS) : SET_BIT(i2c->IC_CON, I2C_CR_SLAVEDIS);
}
/// @}

/// @}

/// @}
