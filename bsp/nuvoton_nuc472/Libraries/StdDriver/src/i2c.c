/****************************************************************************//**
 * @file     i2c.c
 * @version  V0.10
 * $Revision: 13 $
 * $Date: 14/09/30 1:10p $
 * @brief    NUC472/NUC442 I2C driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "NUC472_442.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_I2C_Driver I2C Driver
  @{
*/


/** @addtogroup NUC472_442_I2C_EXPORTED_FUNCTIONS I2C Exported Functions
  @{
*/

/**
  * @brief This function make I2C module be ready and set the wanted bus clock.
  * @param[in] i2c is the base address of I2C module.
  * @param[in] u32BusClock is the target bus speed of I2C module.
  * @return Actual I2C bus clock frequency.
  */
uint32_t I2C_Open(I2C_T *i2c, uint32_t u32BusClock)
{
    uint32_t u32Div;
    uint32_t u32Pclk = CLK_GetPCLKFreq();

    u32Div = (uint32_t) ((( u32Pclk * 10)/(u32BusClock * 4) + 5) / 10 - 1); /* Compute proper divider for I2C clock */
    i2c->CLKDIV = u32Div;

    /* Enable I2C */
    i2c->CTL |= I2C_CTL_I2CEN_Msk;

    return ( u32Pclk / ((u32Div+1)<<2) );
}

/**
  * @brief  This function closes the I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  */
void I2C_Close(I2C_T *i2c)
{
    /* Reset SPI */
    if((uint32_t)i2c == I2C0_BASE) {
        SYS->IPRST1 |= SYS_IPRST1_I2C0RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_I2C0RST_Msk;
    } else if((uint32_t)i2c == I2C1_BASE) {
        SYS->IPRST1 |= SYS_IPRST1_I2C1RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_I2C1RST_Msk;
    } else if((uint32_t)i2c == I2C2_BASE) {
        SYS->IPRST1 |= SYS_IPRST1_I2C2RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_I2C2RST_Msk;
    } else {
        SYS->IPRST1 |= SYS_IPRST1_I2C3RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_I2C3RST_Msk;
    }

    /* Disable I2C */
    i2c->CTL &= ~I2C_CTL_I2CEN_Msk;
}

/**
  * @brief This function clears the time-out flag.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  */
void I2C_ClearTimeoutFlag(I2C_T *i2c)
{
    i2c->TOCTL |= I2C_TOCTL_TOIF_Msk;
}

/**
  * @brief This function sets the control bit of the I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @param[in] u8Start sets START bit to I2C module.
  * @param[in] u8Stop sets STOP bit to I2C module.
  * @param[in] u8Si sets SI bit to I2C module.
  * @param[in] u8Ack sets ACK bit to I2C module.
  * @return none
  */
void I2C_Trigger(I2C_T *i2c, uint8_t u8Start, uint8_t u8Stop, uint8_t u8Si, uint8_t u8Ack)
{
    uint32_t u32Reg = 0;
    uint32_t u32Val = i2c->CTL & ~(I2C_STA | I2C_STO | I2C_AA);

    if (u8Start)
        u32Reg |= I2C_STA;
    if (u8Stop)
        u32Reg |= I2C_STO;
    if (u8Si)
        u32Reg |= I2C_SI;
    if (u8Ack)
        u32Reg |= I2C_AA;

    i2c->CTL = u32Val | u32Reg;
}

/**
  * @brief This function disables the interrupt of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  */
void I2C_DisableInt(I2C_T *i2c)
{
    i2c->CTL &= ~I2C_CTL_INTEN_Msk;
}

/**
  * @brief This function enables the interrupt (EI bit) of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  */
void I2C_EnableInt(I2C_T *i2c)
{
    i2c->CTL |= I2C_CTL_INTEN_Msk;
}

/**
  * @brief This function returns the real bus clock of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return Actual I2C bus clock frequency.
  */
uint32_t I2C_GetBusClockFreq(I2C_T *i2c)
{
    uint32_t u32Divider = i2c->CLKDIV;

    return ( CLK_GetPCLKFreq() / ((u32Divider+1)<<2) );
}

/**
  * @brief This function sets bus frequency of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @param[in] u32BusClock is the target bus speed of I2C module.
  * @return Actual I2C bus clock frequency.
  */
uint32_t I2C_SetBusClockFreq(I2C_T *i2c, uint32_t u32BusClock)
{
    uint32_t u32Div;
    uint32_t u32Pclk = CLK_GetPCLKFreq();

    u32Div = (uint32_t) (((u32Pclk * 10)/(u32BusClock * 4) + 5) / 10 - 1); /* Compute proper divider for I2C clock */
    i2c->CLKDIV = u32Div;

    return ( u32Pclk / ((u32Div+1)<<2) );
}

/**
  * @brief This function gets the interrupt flag of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return Interrupt flag.
  * @retval 0 Flag is not set.
  * @retval 1 Flag is set.
  */
uint32_t I2C_GetIntFlag(I2C_T *i2c)
{
    return ( (i2c->CTL & I2C_CTL_SI_Msk) == I2C_CTL_SI_Msk ? 1:0 );
}

/**
  * @brief This function returns the status of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return I2C status
  */
uint32_t I2C_GetStatus(I2C_T *i2c)
{
    return ( i2c->STATUS );
}

/**
  * @brief This function returns the data stored in data register of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return I2C data.
  */
uint32_t I2C_GetData(I2C_T *i2c)
{
    return ( i2c->DAT );
}

/**
  * @brief This function writes the data to data register of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @param[in] u8Data is the data which will be write to data register of I2C module.
  * @return none
  */
void I2C_SetData(I2C_T *i2c, uint8_t u8Data)
{
    i2c->DAT = u8Data;
}

/**
  * @brief Configure slave address and enable GC mode.
  * @param[in] i2c is the base address of I2C module.
  * @param[in] u8SlaveNo is the set number of salve address.
  * @param[in] u8SlaveAddr is the slave address.
  * @param[in] u8GCMode GC mode enable or not. Valid values are:
  *              - \ref I2C_GCMODE_ENABLE
  *              - \ref I2C_GCMODE_DISABLE
  * @return none
  */
void I2C_SetSlaveAddr(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddr, uint8_t u8GCMode)
{
    switch (u8SlaveNo) {
    case 0:
        i2c->ADDR0  = (u8SlaveAddr << 1) | u8GCMode;
        break;
    case 1:
        i2c->ADDR1  = (u8SlaveAddr << 1) | u8GCMode;
        break;
    case 2:
        i2c->ADDR2  = (u8SlaveAddr << 1) | u8GCMode;
        break;
    case 3:
        i2c->ADDR3  = (u8SlaveAddr << 1) | u8GCMode;
        break;
    default:
        i2c->ADDR0  = (u8SlaveAddr << 1) | u8GCMode;
    }
}

/**
  * @brief Configure the mask of slave address. The corresponding address bit is "Don't Care".
  * @param[in] i2c is the base address of I2C module.
  * @param[in] u8SlaveNo is the set number of salve address.
  * @param[in] u8SlaveAddrMask is the slave address mask.
  * @return none
  */
void I2C_SetSlaveAddrMask(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddrMask)
{
    switch (u8SlaveNo) {
    case 0:
        i2c->ADDRMSK0  = u8SlaveAddrMask << 1;
        break;
    case 1:
        i2c->ADDRMSK1  = u8SlaveAddrMask << 1;
        break;
    case 2:
        i2c->ADDRMSK2  = u8SlaveAddrMask << 1;
        break;
    case 3:
        i2c->ADDRMSK3  = u8SlaveAddrMask << 1;
        break;
    default:
        i2c->ADDRMSK0  = u8SlaveAddrMask << 1;
    }
}

/**
  * @brief This function enables timeout function and configures DIV4 function to support long timeout.
  * @param[in] i2c is the base address of I2C module.
  * @param[in] u8LongTimeout Enable timeout counter input clock is divide by 4.
  * @return none
  */
void I2C_EnableTimeout(I2C_T *i2c, uint8_t u8LongTimeout)
{
    if(u8LongTimeout)
        i2c->TOCTL |= I2C_TOCTL_TOCDIV4_Msk;
    else
        i2c->TOCTL &= ~I2C_TOCTL_TOCDIV4_Msk;

    i2c->TOCTL |= I2C_TOCTL_TOCEN_Msk;
}

/**
  * @brief This function disables time-out function.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  */
void I2C_DisableTimeout(I2C_T *i2c)
{
    i2c->TOCTL &= ~I2C_TOCTL_TOCEN_Msk;
}

/**
  * @brief This function enables the wakeup function of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  */
void I2C_EnableWakeup(I2C_T *i2c)
{
    i2c->WKCTL |= I2C_WKCTL_WKEN_Msk;
}

/**
  * @brief This function disables the wakeup function of I2C module.
  * @param[in] i2c is the base address of I2C module.
  * @return none
  */
void I2C_DisableWakeup(I2C_T *i2c)
{
    i2c->WKCTL &= ~I2C_WKCTL_WKEN_Msk;
}

/*@}*/ /* end of group NUC472_442_I2C_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_I2C_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
