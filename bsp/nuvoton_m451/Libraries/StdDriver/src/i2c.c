/**************************************************************************//**
 * @file     i2c.c
 * @version  V3.00
 * $Revision: 23 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 series I2C driver source file
 *
 * @note
 * Copyright (C) 2014~2015 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "M451Series.h"

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
  * @param[in]  u32BusClock The target I2C bus clock in Hz
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
    i2c->CLKDIV = u32Div;

    /* Enable I2C */
    i2c->CTL |= I2C_CTL_I2CEN_Msk;

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
        SYS->IPRST1 |= SYS_IPRST1_I2C0RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_I2C0RST_Msk;
    }
    else if((uint32_t)i2c == I2C1_BASE)
    {
        SYS->IPRST1 |= SYS_IPRST1_I2C1RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_I2C1RST_Msk;
    }

    /* Disable I2C */
    i2c->CTL &= ~I2C_CTL_I2CEN_Msk;
}

/**
  * @brief      Clear Time-out Counter flag
  *
  * @param[in]  i2c         Specify I2C port
    *
  * @return     None
  *
  * @details    When Time-out flag will be set, use this function to clear I2C Bus Time-out counter flag .
    *
  */
void I2C_ClearTimeoutFlag(I2C_T *i2c)
{
    i2c->TOCTL |= I2C_TOCTL_TOIF_Msk;
}

/**
  * @brief      Set Control bit of I2C Controller
  *
  * @param[in]  i2c         Specify I2C port
  * @param[in]  u8Start     Set I2C START condition
  * @param[in]  u8Stop      Set I2C STOP condition
  * @param[in]  u8Si        Clear SI flag
  * @param[in]  u8Ack       Set I2C ACK bit
  *
  * @return     None
  *
  * @details    The function set I2C Control bit of I2C Bus protocol.
  *
  */
void I2C_Trigger(I2C_T *i2c, uint8_t u8Start, uint8_t u8Stop, uint8_t u8Si, uint8_t u8Ack)
{
    uint32_t u32Reg = 0;

    if(u8Start)
        u32Reg |= I2C_CTL_STA;
    if(u8Stop)
        u32Reg |= I2C_CTL_STO;
    if(u8Si)
        u32Reg |= I2C_CTL_SI;
    if(u8Ack)
        u32Reg |= I2C_CTL_AA;

    i2c->CTL = (i2c->CTL & ~0x3C) | u32Reg;
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
    i2c->CTL &= ~I2C_CTL_INTEN_Msk;
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
    i2c->CTL |= I2C_CTL_INTEN_Msk;
}

/**
 * @brief      Get I2C Bus Clock
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     The actual I2C Bus clock in Hz
 *
 * @details    To get the actual I2C Bus Clock frequency.
 */
uint32_t I2C_GetBusClockFreq(I2C_T *i2c)
{
    uint32_t u32Divider = i2c->CLKDIV;

    return (SystemCoreClock / ((u32Divider + 1) << 2));
}

/**
 * @brief      Set I2C Bus Clock
 *
 * @param[in]  i2c          Specify I2C port
 * @param[in]  u32BusClock  The target I2C Bus Clock in Hz
 *
 * @return     The actual I2C Bus Clock in Hz
 *
 * @details    To set the actual I2C Bus Clock frequency.
 */
uint32_t I2C_SetBusClockFreq(I2C_T *i2c, uint32_t u32BusClock)
{
    uint32_t u32Div;

    u32Div = (uint32_t)(((SystemCoreClock * 10) / (u32BusClock * 4) + 5) / 10 - 1); /* Compute proper divider for I2C clock */
    i2c->CLKDIV = u32Div;

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
    return ((i2c->CTL & I2C_CTL_SI_Msk) == I2C_CTL_SI_Msk ? 1 : 0);
}

/**
 * @brief      Get I2C Bus Status Code
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     I2C Status Code
 *
 * @details    To get I2C Bus Status Code.
 */
uint32_t I2C_GetStatus(I2C_T *i2c)
{
    return (i2c->STATUS);
}

/**
 * @brief      Read a Byte from I2C Bus
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     I2C Data
 *
 * @details    To read a bytes data from specify I2C port.
 */
uint8_t I2C_GetData(I2C_T *i2c)
{
    return (i2c->DAT);
}

/**
 * @brief      Send a byte to I2C Bus
 *
 * @param[in]  i2c          Specify I2C port
 * @param[in]  u8Data       The data to send to I2C bus
 *
 * @return     None
 *
 * @details    This function is used to write a byte to specified I2C port
 */
void I2C_SetData(I2C_T *i2c, uint8_t u8Data)
{
    i2c->DAT = u8Data;
}

/**
 * @brief      Set 7-bit Slave Address and GC Mode
 *
 * @param[in]  i2c          Specify I2C port
 * @param[in]  u8SlaveNo    Set the number of I2C address register (0~3)
 * @param[in]  u8SlaveAddr  7-bit slave address
 * @param[in]  u8GCMode     Enable/Disable GC mode (I2C_GCMODE_ENABLE / I2C_GCMODE_DISABLE)
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
            i2c->ADDR1  = (u8SlaveAddr << 1) | u8GCMode;
            break;
        case 2:
            i2c->ADDR2  = (u8SlaveAddr << 1) | u8GCMode;
            break;
        case 3:
            i2c->ADDR3  = (u8SlaveAddr << 1) | u8GCMode;
            break;
        case 0:
        default:
            i2c->ADDR0  = (u8SlaveAddr << 1) | u8GCMode;
            break;
    }
}

/**
 * @brief      Configure the mask bits of 7-bit Slave Address
 *
 * @param[in]  i2c              Specify I2C port
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
            i2c->ADDRMSK1  = u8SlaveAddrMask << 1;
            break;
        case 2:
            i2c->ADDRMSK2  = u8SlaveAddrMask << 1;
            break;
        case 3:
            i2c->ADDRMSK3  = u8SlaveAddrMask << 1;
            break;
        case 0:
        default:
            i2c->ADDRMSK0  = u8SlaveAddrMask << 1;
            break;
    }
}

/**
 * @brief      Enable Time-out Counter Function and support Long Time-out
 *
 * @param[in]  i2c              Specify I2C port
 * @param[in]  u8LongTimeout    Configure DIV4 to enable Long Time-out (0/1)
 *
 * @return     None
 *
 * @details    This function enable Time-out Counter function and configure DIV4 to support Long
 *             Time-out.
 *
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
 * @brief      Disable Time-out Counter Function
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     None
 *
 * @details    To disable Time-out Counter function in I2CTOC register.
 *
 */
void I2C_DisableTimeout(I2C_T *i2c)
{
    i2c->TOCTL &= ~I2C_TOCTL_TOCEN_Msk;
}

/**
 * @brief      Enable I2C Wake-up Function
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     None
 *
 * @details    To enable Wake-up function of I2C Wake-up control register.
 *
 */
void I2C_EnableWakeup(I2C_T *i2c)
{
    i2c->WKCTL |= I2C_WKCTL_WKEN_Msk;
}

/**
 * @brief      Disable I2C Wake-up Function
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     None
 *
 * @details    To disable Wake-up function of I2C Wake-up control register.
 *
 */
void I2C_DisableWakeup(I2C_T *i2c)
{
    i2c->WKCTL &= ~I2C_WKCTL_WKEN_Msk;
}

/**
 * @brief      To get SMBus Status
 *
 * @param[in]  i2c          Specify I2C port
 *
 * @return     SMBus status
 *
 * @details    To get the Bus Management status of I2C_BUSSTS register
 *
 */
uint32_t I2C_SMBusGetStatus(I2C_T *i2c)
{
    return (i2c->BUSSTS);
}

/**
 * @brief      Clear SMBus Interrupt Flag
 *
 * @param[in]  i2c              Specify I2C port
 * @param[in]  u8SMBusIntFlag   Specify SMBus interrupt flag
 *
 * @return     None
 *
 * @details    To clear flags of I2C_BUSSTS status register if interrupt set.
 *
 */
void I2C_SMBusClearInterruptFlag(I2C_T *i2c, uint8_t u8SMBusIntFlag)
{
    i2c->BUSSTS |= u8SMBusIntFlag;
}

/**
 * @brief      Set SMBus Bytes Counts of Transmission or Reception
 *
 * @param[in]  i2c              Specify I2C port
 * @param[in]  u32PktSize       Transmit / Receive bytes
 *
 * @return     None
 *
 * @details    The transmission or receive byte number in one transaction when PECEN is set. The maximum is 255 bytes.
 *
 */
void I2C_SMBusSetPacketByteCount(I2C_T *i2c, uint32_t u32PktSize)
{
    i2c->PKTSIZE = u32PktSize;
}

/**
 * @brief      Init SMBus Host/Device Mode
 *
 * @param[in]  i2c              Specify I2C port
 * @param[in]  u8HostDevice     Init SMBus port mode(I2C_SMBH_ENABLE(1)/I2C_SMBD_ENABLE(0))
 *
 * @return     None
 *
 * @details    Using SMBus communication must specify the port is a Host or a Device.
 *
 */
void I2C_SMBusOpen(I2C_T *i2c, uint8_t u8HostDevice)
{
    /* Clear  BMHEN, BMDEN of BUSCTL Register */
    i2c->BUSCTL &=  ~(I2C_BUSCTL_BMHEN_Msk | I2C_BUSCTL_BMDEN_Msk);

    /* Set SMBus Host/Device Mode, and enable Bus Management*/
    if(u8HostDevice == I2C_SMBH_ENABLE)
        i2c->BUSCTL |= (I2C_BUSCTL_BMHEN_Msk | I2C_BUSCTL_BUSEN_Msk);
    else
        i2c->BUSCTL |= (I2C_BUSCTL_BMDEN_Msk | I2C_BUSCTL_BUSEN_Msk);
}

/**
 * @brief      Disable SMBus function
 *
 * @param[in]  i2c              Specify I2C port
 *
 * @return     None
 *
 * @details    Disable all SMBus function include Bus disable, CRC check, Acknowledge by manual, Host/Device Mode.
 *
 */
void I2C_SMBusClose(I2C_T *i2c)
{

    i2c->BUSCTL = 0x00;
}

/**
 * @brief      Enable SMBus PEC Transmit Function
 *
 * @param[in]  i2c              Specify I2C port
 * @param[in]  u8PECTxEn        CRC transmit enable(PECTX_ENABLE) or disable(PECTX_DISABLE)
 *
 * @return     None
 *
 * @details    When enable CRC check function, the Host or Device needs to transmit CRC byte.
 *
 */
void I2C_SMBusPECTxEnable(I2C_T *i2c, uint8_t u8PECTxEn)
{
    i2c->BUSCTL &= ~I2C_BUSCTL_PECTXEN_Msk;

    if(u8PECTxEn)
        i2c->BUSCTL |= (I2C_BUSCTL_PECEN_Msk | I2C_BUSCTL_PECTXEN_Msk);
    else
        i2c->BUSCTL |= I2C_BUSCTL_PECEN_Msk;
}

/**
 * @brief      Get SMBus CRC value
 *
 * @param[in]  i2c              Specify I2C port
 *
 * @return     A byte is packet error check value
 *
 * @details    The CRC check value after a transmission or a reception by count by using CRC8
 *
 */
uint8_t I2C_SMBusGetPECValue(I2C_T *i2c)
{
    return i2c->PKTCRC;
}

/**
 * @brief      Calculate Time-out of SMBus idle period
 *
 * @param[in]  i2c              Specify I2C port
 * @param[in]  us               Time-out length(us)
 * @param[in]  u32Hclk          I2C peripheral clock frequency
 *
 * @return     None
 *
 * @details    This function is used to set SMBus Time-out length when bus is in Idle state.
 *
 */

void I2C_SMBusIdleTimeout(I2C_T *i2c, uint32_t us, uint32_t u32Hclk)
{
    uint32_t  u32Div, u32Hclk_kHz;

    i2c->BUSCTL |= I2C_BUSCTL_TIDLE_Msk;
    u32Hclk_kHz = u32Hclk / 1000;
    u32Div = (((us * u32Hclk_kHz) / 1000) >> 2) - 1;
    if(u32Div > 255)
    {
        i2c->BUSTOUT = 0xFF;
    }
    else
    {
        i2c->BUSTOUT = u32Div;
    }

}

/**
 * @brief      Calculate Time-out of SMBus active period
 *
 * @param[in]  i2c              Specify I2C port
 * @param[in]  ms               Time-out length(ms)
 * @param[in]  u32Pclk          peripheral clock frequency
 *
 * @return     None
 *
 * @details    This function is used to set SMBus Time-out length when bus is in active state.
 *             Time-out length is calculate the SCL line "one clock" pull low timing.
 *
 */

void I2C_SMBusTimeout(I2C_T *i2c, uint32_t ms, uint32_t u32Pclk)
{
    uint32_t u32Div, u32Pclk_kHz;

    i2c->BUSCTL &= ~I2C_BUSCTL_TIDLE_Msk;

    /* DIV4 disabled */
    i2c->TOCTL &= ~I2C_TOCTL_TOCEN_Msk;
    u32Pclk_kHz = u32Pclk / 1000;
    u32Div = ((ms * u32Pclk_kHz) / (16 * 1024)) - 1;
    if(u32Div <= 0xFF)
    {
        i2c->BUSTOUT = u32Div;
        return;
    }

    /* DIV4 enabled */
    i2c->TOCTL |= I2C_TOCTL_TOCEN_Msk;

    i2c->BUSTOUT = (((ms * u32Pclk_kHz) / (16 * 1024 * 4)) - 1) & 0xFF; //The max value is 255
}

/**
 * @brief      Calculate Cumulative Clock low Time-out of SMBus active period
 *
 * @param[in]  i2c              Specify I2C port
 * @param[in]  ms               Time-out length(ms)
 * @param[in]  u32Pclk          peripheral clock frequency
 *
 * @return     None
 *
 * @details    This function is used to set SMBus Time-out length when bus is in Active state.
 *             Time-out length is calculate the SCL line "clocks" low cumulative timing.
 *
 */

void I2C_SMBusClockLoTimeout(I2C_T *i2c, uint32_t ms, uint32_t u32Pclk)
{
    uint32_t u32Div, u32Pclk_kHz;

    i2c->BUSCTL &= ~I2C_BUSCTL_TIDLE_Msk;

    /* DIV4 disabled */
    i2c->TOCTL &= ~I2C_TOCTL_TOCEN_Msk;
    u32Pclk_kHz = u32Pclk / 1000;
    u32Div = ((ms * u32Pclk_kHz) / (16 * 1024)) - 1;
    if(u32Div <= 0xFF)
    {
        i2c->CLKTOUT = u32Div;
        return;
    }

    /* DIV4 enabled */
    i2c->TOCTL |= I2C_TOCTL_TOCEN_Msk;
    i2c->CLKTOUT = (((ms * u32Pclk_kHz) / (16 * 1024 * 4)) - 1) & 0xFF; //The max value is 255
}

/*@}*/ /* end of group I2C_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group I2C_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2014~2015 Nuvoton Technology Corp. ***/
