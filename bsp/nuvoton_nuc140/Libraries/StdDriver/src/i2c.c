/**************************************************************************//**
 * @file     i2c.c
 * @version  V3.00
 * $Revision: 5 $
 * $Date: 15/05/20 3:49p $
 * @brief    I2C driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NUC100Series.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup I2C_Driver I2C Driver
  @{
*/


/** @addtogroup I2C_EXPORTED_FUNCTIONS I2C Exported Functions
  @{
*/

/**
  * @brief      Enable specify I2C Controller and set Clock Divider
  *
  * @param[in]  i2c         Specify I2C port
  * @param[in]  u32BusClock The target I2C Bus clock in Hz
  *
  * @return     Actual I2C bus clock frequency
  *
  * @details    The function enable the specify I2C Controller and set proper Clock Divider
  *             in I2C CLOCK DIVIDED REGISTER (I2CLK) according to the target I2C Bus clock.
  *             I2C Bus clock = PCLK / (4*(divider+1).
  *
  */
uint32_t I2C_Open(I2C_T *i2c, uint32_t u32BusClock)
{
    uint32_t u32Div;

    u32Div = (uint32_t)(((SystemCoreClock * 10) / (u32BusClock * 4) + 5) / 10 - 1); /* Compute proper divider for I2C clock */
    i2c->I2CLK = u32Div;

    /* Enable I2C */
    i2c->I2CON |= I2C_I2CON_ENS1_Msk;

    return (SystemCoreClock / ((u32Div + 1) << 2));
}

/**
  * @brief      Disable specify I2C Controller
  *
  * @param[in]  i2c         Specify I2C port
    *
  * @return     None
  *
  * @details    Reset I2C Controller and disable specify I2C port.
    *
  */

void I2C_Close(I2C_T *i2c)
{
    /* Reset I2C Controller */
    if((uint32_t)i2c == I2C0_BASE)
    {
        SYS->IPRSTC2 |= SYS_IPRSTC2_I2C0_RST_Msk;
        SYS->IPRSTC2 &= ~SYS_IPRSTC2_I2C0_RST_Msk;
    }
    else if((uint32_t)i2c == I2C1_BASE)
    {
        SYS->IPRSTC2 |= SYS_IPRSTC2_I2C1_RST_Msk;
        SYS->IPRSTC2 &= ~SYS_IPRSTC2_I2C1_RST_Msk;
    }

    /* Disable I2C */
    i2c->I2CON &= ~I2C_I2CON_ENS1_Msk;
}

/**
  * @brief      Clear Time-out Counter flag
  *
  * @param[in]  i2c         Specify I2C port
    *
  * @return     None
  *
  * @details    When Time-out flag will be set, use this function to clear I2C Bus Time-out Counter flag .
    *
  */
void I2C_ClearTimeoutFlag(I2C_T *i2c)
{
    i2c->I2CTOC |= I2C_I2CTOC_TIF_Msk;
}

/**
  * @brief      Set control bit of I2C Controller
  *
  * @param[in]  i2c         Specify I2C port
  * @param[in]  u8Start     Set I2C START condition
  * @param[in]  u8Stop      Set I2C STOP condition
  * @param[in]  u8Si        Clear SI flag
  * @param[in]  u8Ack       Set I2C ACK bit
  *
  * @return     None
  *
  * @details    The function set I2C control bit of I2C Bus protocol.
  *
  */
void I2C_Trigger(I2C_T *i2c, uint8_t u8Start, uint8_t u8Stop, uint8_t u8Si, uint8_t u8Ack)
{
    uint32_t u32Reg = 0;

    if(u8Start)
        u32Reg |= I2C_I2CON_STA;
    if(u8Stop)
        u32Reg |= I2C_I2CON_STO;
    if(u8Si)
        u32Reg |= I2C_I2CON_SI;
    if(u8Ack)
        u32Reg |= I2C_I2CON_AA;

    i2c->I2CON = (i2c->I2CON & ~0x3C) | u32Reg;
}

/**
  * @brief      Disable Interrupt of I2C Controller
  *
  * @param[in]  i2c         Specify I2C port
  *
  * @return     None
  *
  * @details    The function is used for disable I2C interrupt
  *
  */
void I2C_DisableInt(I2C_T *i2c)
{
    i2c->I2CON &= ~I2C_I2CON_EI_Msk;
}

/**
  * @brief      Enable Interrupt of I2C Controller
  *
  * @param[in]  i2c         Specify I2C port
  *
  * @return     None
  *
  * @details    The function is used for enable I2C interrupt
  *
  */
void I2C_EnableInt(I2C_T *i2c)
{
    i2c->I2CON |= I2C_I2CON_EI_Msk;
}

/**
 * @brief      Get I2C Bus clock
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     The actual I2C Bus clock in Hz
 *
 * @details    To get the actual I2C Bus clock frequency.
 */
uint32_t I2C_GetBusClockFreq(I2C_T *i2c)
{
    uint32_t u32Divider = i2c->I2CLK;

    return (SystemCoreClock / ((u32Divider + 1) << 2));
}

/**
 * @brief      Set I2C Bus clock
 *
 * @param[in]  i2c          Specify I2C port
 * @param[in]  u32BusClock  The target I2C Bus clock in Hz
 *
 * @return     The actual I2C Bus clock in Hz
 *
 * @details    To set the actual I2C Bus clock frequency.
 */
uint32_t I2C_SetBusClockFreq(I2C_T *i2c, uint32_t u32BusClock)
{
    uint32_t u32Div;

    u32Div = (uint32_t)(((SystemCoreClock * 10) / (u32BusClock * 4) + 5) / 10 - 1); /* Compute proper divider for I2C clock */
    i2c->I2CLK = u32Div;

    return (SystemCoreClock / ((u32Div + 1) << 2));
}

/**
 * @brief      Get Interrupt Flag
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     I2C interrupt flag status
 *
 * @details    To get I2C Bus interrupt flag.
 */
uint32_t I2C_GetIntFlag(I2C_T *i2c)
{
    return ((i2c->I2CON & I2C_I2CON_SI_Msk) == I2C_I2CON_SI_Msk ? 1 : 0);
}

/**
 * @brief      Get I2C bus Status Code
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     I2C Status Code
 *
 * @details    To get I2C bus Status Code.
 */
uint32_t I2C_GetStatus(I2C_T *i2c)
{
    return (i2c->I2CSTATUS);
}

/**
 * @brief      Read a byte from I2C Bus
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     I2C Data
 *
 * @details    To read a byte data from specify I2C port.
 */
uint8_t I2C_GetData(I2C_T *i2c)
{
    return (i2c->I2CDAT);
}

/**
 * @brief      Send a byte to I2C Bus
 *
 * @param[in]  i2c          I2C port
 * @param[in]  u8Data       The data to send to I2C Bus
 *
 * @return     None
 *
 * @details    This function is used to write a byte to specified I2C port
 */
void I2C_SetData(I2C_T *i2c, uint8_t u8Data)
{
    i2c->I2CDAT = u8Data;
}

/**
 * @brief      Set 7-bit Slave Address and GC Mode
 *
 * @param[in]  i2c          I2C port
 * @param[in]  u8SlaveNo    Set the number of I2C address register (0~3)
 * @param[in]  u8SlaveAddr  7-bit slave address
 * @param[in]  u8GCMode     Enable/Disable GC Mode (I2C_GCMODE_ENABLE / I2C_GCMODE_DISABLE)
 *
 * @return     None
 *
 * @details    This function is used to set 7-bit slave addresses in I2C SLAVE ADDRESS REGISTER (I2CADDR0~3)
 *             and enable GC Mode.
 *
 */
void I2C_SetSlaveAddr(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddr, uint8_t u8GCMode)
{
    switch(u8SlaveNo)
    {
    case 1:
        i2c->I2CADDR1  = (u8SlaveAddr << 1) | u8GCMode;
        break;
    case 2:
        i2c->I2CADDR2  = (u8SlaveAddr << 1) | u8GCMode;
        break;
    case 3:
        i2c->I2CADDR3  = (u8SlaveAddr << 1) | u8GCMode;
        break;
    case 0:
    default:
        i2c->I2CADDR0  = (u8SlaveAddr << 1) | u8GCMode;
        break;
    }
}

/**
 * @brief      Configure the mask bits of 7-bit Slave Address
 *
 * @param[in]  i2c              I2C port
 * @param[in]  u8SlaveNo        Set the number of I2C address mask register (0~3)
 * @param[in]  u8SlaveAddrMask  A byte for slave address mask
 *
 * @return     None
 *
 * @details    This function is used to set 7-bit slave addresses.
 *
 */
void I2C_SetSlaveAddrMask(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddrMask)
{
    switch(u8SlaveNo)
    {
    case 1:
        i2c->I2CADM1  = u8SlaveAddrMask << 1;
        break;
    case 2:
        i2c->I2CADM2  = u8SlaveAddrMask << 1;
        break;
    case 3:
        i2c->I2CADM3  = u8SlaveAddrMask << 1;
        break;
    case 0:
    default:
        i2c->I2CADM0  = u8SlaveAddrMask << 1;
        break;
    }
}

/**
 * @brief      Enable Time-out Counter Function and support Long Time-out
 *
 * @param[in]  i2c              I2C port
 * @param[in]  u8LongTimeout    Configure DIV4 to enable Long Time-out (0/1)
 *
 * @return     None
 *
 * @details    This function enable Time-out counter function and configure DIV4 to support Long
 *             Time-out.
 *
 */
void I2C_EnableTimeout(I2C_T *i2c, uint8_t u8LongTimeout)
{
    if(u8LongTimeout)
        i2c->I2CTOC |= I2C_I2CTOC_DIV4_Msk;
    else
        i2c->I2CTOC &= ~I2C_I2CTOC_DIV4_Msk;

    i2c->I2CTOC |= I2C_I2CTOC_ENTI_Msk;
}

/**
 * @brief      Disable Time-out Counter Function
 *
 * @param[in]  i2c          I2C port
 *
 * @return     None
 *
 * @details    To disable Time-out counter function in I2CTOC register.
 *
 */
void I2C_DisableTimeout(I2C_T *i2c)
{
    i2c->I2CTOC &= ~I2C_I2CTOC_ENTI_Msk;
}

/**
 * @brief      Enable I2C Wake-up Function
 *
 * @param[in]  i2c          I2C port
 *
 * @return     None
 *
 * @details    To enable Wake-up function of I2C Wake-up control register.
 *
 */
void I2C_EnableWakeup(I2C_T *i2c)
{
    i2c->I2CWKUPCON |= I2C_I2CWKUPCON_WKUPEN_Msk;
}

/**
 * @brief      Disable I2C Wake-up Function
 *
 * @param[in]  i2c          I2C port
 *
 * @return     None
 *
 * @details    To disable Wake-up function of I2C Wake-up control register.
 *
 */
void I2C_DisableWakeup(I2C_T *i2c)
{
    i2c->I2CWKUPCON &= ~I2C_I2CWKUPCON_WKUPEN_Msk;
}

/*@}*/ /* end of group I2C_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group I2C_Driver */

/*@}*/ /* end of group Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
