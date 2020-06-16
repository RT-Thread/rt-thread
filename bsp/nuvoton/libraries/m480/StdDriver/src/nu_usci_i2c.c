/****************************************************************************//**
 * @file     usci_i2c.c
 * @version  V3.00
 * @brief    M480 series USCI I2C(UI2C) driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup USCI_I2C_Driver USCI_I2C Driver
  @{
*/


/** @addtogroup USCI_I2C_EXPORTED_FUNCTIONS USCI_I2C Exported Functions
  @{
*/

/**
 *    @brief        This function makes USCI_I2C module be ready and set the wanted bus clock
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u32BusClock     The target bus speed of USCI_I2C module.
 *
 *    @return       Actual USCI_I2C bus clock frequency.
 *
 *    @details      Enable USCI_I2C module and configure USCI_I2C module(bus clock, data format).
 */
uint32_t UI2C_Open(UI2C_T *ui2c, uint32_t u32BusClock)
{
    uint32_t u32ClkDiv;
    uint32_t u32Pclk;

    if( ui2c == UI2C0 )
    {
        u32Pclk = CLK_GetPCLK0Freq();
    }
    else
    {
        u32Pclk = CLK_GetPCLK1Freq();
    }

    u32ClkDiv = (uint32_t) ((((((u32Pclk/2U)*10U)/(u32BusClock))+5U)/10U)-1U); /* Compute proper divider for USCI_I2C clock */

    /* Enable USCI_I2C protocol */
    ui2c->CTL &= ~UI2C_CTL_FUNMODE_Msk;
    ui2c->CTL = 4U << UI2C_CTL_FUNMODE_Pos;

    /* Data format configuration */
    /* 8 bit data length */
    ui2c->LINECTL &= ~UI2C_LINECTL_DWIDTH_Msk;
    ui2c->LINECTL |= 8U << UI2C_LINECTL_DWIDTH_Pos;

    /* MSB data format */
    ui2c->LINECTL &= ~UI2C_LINECTL_LSB_Msk;

    /* Set USCI_I2C bus clock */
    ui2c->BRGEN &= ~UI2C_BRGEN_CLKDIV_Msk;
    ui2c->BRGEN |=  (u32ClkDiv << UI2C_BRGEN_CLKDIV_Pos);
    ui2c->PROTCTL |=  UI2C_PROTCTL_PROTEN_Msk;

    return ( u32Pclk / ((u32ClkDiv+1U)<<1U) );
}

/**
 *    @brief        This function closes the USCI_I2C module
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      Close USCI_I2C protocol function.
 */
void UI2C_Close(UI2C_T *ui2c)
{
    /* Disable USCI_I2C function */
    ui2c->CTL &= ~UI2C_CTL_FUNMODE_Msk;
}

/**
 *    @brief        This function clears the time-out flag
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      Clear time-out flag when time-out flag is set.
 */
void UI2C_ClearTimeoutFlag(UI2C_T *ui2c)
{
    ui2c->PROTSTS = UI2C_PROTSTS_TOIF_Msk;
}

/**
 *    @brief        This function sets the control bit of the USCI_I2C module.
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u8Start         Set START bit to USCI_I2C module.
 *    @param[in]    u8Stop Set      STOP bit to USCI_I2C module.
 *    @param[in]    u8Ptrg Set      PTRG bit to USCI_I2C module.
 *    @param[in]    u8Ack Set       ACK bit to USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      The function set USCI_I2C control bit of USCI_I2C bus protocol.
 */
void UI2C_Trigger(UI2C_T *ui2c, uint8_t u8Start, uint8_t u8Stop, uint8_t u8Ptrg, uint8_t u8Ack)
{
    uint32_t u32Reg = 0U;
    uint32_t u32Val = ui2c->PROTCTL & ~(UI2C_PROTCTL_STA_Msk | UI2C_PROTCTL_STO_Msk | UI2C_PROTCTL_AA_Msk);

    if (u8Start)
    {
        u32Reg |= UI2C_PROTCTL_STA_Msk;
    }
    if (u8Stop)
    {
        u32Reg |= UI2C_PROTCTL_STO_Msk;
    }
    if (u8Ptrg)
    {
        u32Reg |= UI2C_PROTCTL_PTRG_Msk;
    }
    if (u8Ack)
    {
        u32Reg |= UI2C_PROTCTL_AA_Msk;
    }

    ui2c->PROTCTL = u32Val | u32Reg;
}

/**
 *    @brief        This function disables the interrupt of USCI_I2C module
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u32Mask         The combination of all related interrupt enable bits.
 *                                  Each bit corresponds to an interrupt enable bit.
 *                                  This parameter decides which interrupts will be disabled. It is combination of:
 *                                  - \ref UI2C_TO_INT_MASK
 *                                  - \ref UI2C_STAR_INT_MASK
 *                                  - \ref UI2C_STOR_INT_MASK
 *                                  - \ref UI2C_NACK_INT_MASK
 *                                  - \ref UI2C_ARBLO_INT_MASK
 *                                  - \ref UI2C_ERR_INT_MASK
 *                                  - \ref UI2C_ACK_INT_MASK
 *
 *    @return       None
 *
 *    @details      The function is used to disable USCI_I2C bus interrupt events.
 */
void UI2C_DisableInt(UI2C_T *ui2c, uint32_t u32Mask)
{
    /* Disable time-out interrupt flag */
    if((u32Mask & UI2C_TO_INT_MASK) == UI2C_TO_INT_MASK)
    {
        ui2c->PROTIEN &= ~UI2C_PROTIEN_TOIEN_Msk;
    }

    /* Disable start condition received interrupt flag */
    if((u32Mask & UI2C_STAR_INT_MASK) == UI2C_STAR_INT_MASK)
    {
        ui2c->PROTIEN &= ~UI2C_PROTIEN_STARIEN_Msk;
    }

    /* Disable stop condition received interrupt flag */
    if((u32Mask & UI2C_STOR_INT_MASK) == UI2C_STOR_INT_MASK)
    {
        ui2c->PROTIEN &= ~UI2C_PROTIEN_STORIEN_Msk;
    }

    /* Disable non-acknowledge interrupt flag */
    if((u32Mask & UI2C_NACK_INT_MASK) == UI2C_NACK_INT_MASK)
    {
        ui2c->PROTIEN &= ~UI2C_PROTIEN_NACKIEN_Msk;
    }

    /* Disable arbitration lost interrupt flag */
    if((u32Mask & UI2C_ARBLO_INT_MASK) == UI2C_ARBLO_INT_MASK)
    {
        ui2c->PROTIEN &= ~UI2C_PROTIEN_ARBLOIEN_Msk;
    }

    /* Disable error interrupt flag */
    if((u32Mask & UI2C_ERR_INT_MASK) == UI2C_ERR_INT_MASK)
    {
        ui2c->PROTIEN &= ~UI2C_PROTIEN_ERRIEN_Msk;
    }

    /* Disable acknowledge interrupt flag */
    if((u32Mask & UI2C_ACK_INT_MASK) == UI2C_ACK_INT_MASK)
    {
        ui2c->PROTIEN &= ~UI2C_PROTIEN_ACKIEN_Msk;
    }
}

/**
 *    @brief        This function enables the interrupt of USCI_I2C module.
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u32Mask         The combination of all related interrupt enable bits.
 *                                  Each bit corresponds to a interrupt enable bit.
 *                                  This parameter decides which interrupts will be enabled. It is combination of:
 *                                  - \ref UI2C_TO_INT_MASK
 *                                  - \ref UI2C_STAR_INT_MASK
 *                                  - \ref UI2C_STOR_INT_MASK
 *                                  - \ref UI2C_NACK_INT_MASK
 *                                  - \ref UI2C_ARBLO_INT_MASK
 *                                  - \ref UI2C_ERR_INT_MASK
 *                                  - \ref UI2C_ACK_INT_MASK
 *    @return None
 *
 *    @details      The function is used to enable USCI_I2C bus interrupt events.
 */
void UI2C_EnableInt(UI2C_T *ui2c, uint32_t u32Mask)
{
    /* Enable time-out interrupt flag */
    if((u32Mask & UI2C_TO_INT_MASK) == UI2C_TO_INT_MASK)
    {
        ui2c->PROTIEN |= UI2C_PROTIEN_TOIEN_Msk;
    }

    /* Enable start condition received interrupt flag */
    if((u32Mask & UI2C_STAR_INT_MASK) == UI2C_STAR_INT_MASK)
    {
        ui2c->PROTIEN |= UI2C_PROTIEN_STARIEN_Msk;
    }

    /* Enable stop condition received interrupt flag */
    if((u32Mask & UI2C_STOR_INT_MASK) == UI2C_STOR_INT_MASK)
    {
        ui2c->PROTIEN |= UI2C_PROTIEN_STORIEN_Msk;
    }

    /* Enable non-acknowledge interrupt flag */
    if((u32Mask & UI2C_NACK_INT_MASK) == UI2C_NACK_INT_MASK)
    {
        ui2c->PROTIEN |= UI2C_PROTIEN_NACKIEN_Msk;
    }

    /* Enable arbitration lost interrupt flag */
    if((u32Mask & UI2C_ARBLO_INT_MASK) == UI2C_ARBLO_INT_MASK)
    {
        ui2c->PROTIEN |= UI2C_PROTIEN_ARBLOIEN_Msk;
    }

    /* Enable error interrupt flag */
    if((u32Mask & UI2C_ERR_INT_MASK) == UI2C_ERR_INT_MASK)
    {
        ui2c->PROTIEN |= UI2C_PROTIEN_ERRIEN_Msk;
    }

    /* Enable acknowledge interrupt flag */
    if((u32Mask & UI2C_ACK_INT_MASK) == UI2C_ACK_INT_MASK)
    {
        ui2c->PROTIEN |= UI2C_PROTIEN_ACKIEN_Msk;
    }
}

/**
 *    @brief        This function returns the real bus clock of USCI_I2C module
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *
 *    @return       Actual USCI_I2C bus clock frequency.
 *
 *    @details      The function returns the actual USCI_I2C module bus clock.
 */
uint32_t UI2C_GetBusClockFreq(UI2C_T *ui2c)
{
    uint32_t u32Divider;
    uint32_t u32Pclk;

    if (ui2c == UI2C0)
    {
        u32Pclk = CLK_GetPCLK0Freq();
    }
    else
    {
        u32Pclk = CLK_GetPCLK1Freq();
    }

    u32Divider = (ui2c->BRGEN & UI2C_BRGEN_CLKDIV_Msk) >> UI2C_BRGEN_CLKDIV_Pos;

    return ( u32Pclk / ((u32Divider+1U)<<1U) );
}

/**
 *    @brief        This function sets bus clock frequency of USCI_I2C module
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u32BusClock     The target bus speed of USCI_I2C module.
 *
 *    @return Actual USCI_I2C bus clock frequency.
 *
 *    @details      Use this function set USCI_I2C bus clock frequency and return actual bus clock.
 */
uint32_t UI2C_SetBusClockFreq(UI2C_T *ui2c, uint32_t u32BusClock)
{
    uint32_t u32ClkDiv;
    uint32_t u32Pclk;

    if( ui2c == UI2C0 )
    {
        u32Pclk = CLK_GetPCLK0Freq();
    }
    else
    {
        u32Pclk = CLK_GetPCLK1Freq();
    }

    u32ClkDiv = (uint32_t) ((((((u32Pclk/2U)*10U)/(u32BusClock))+5U)/10U)-1U); /* Compute proper divider for USCI_I2C clock */

    /* Set USCI_I2C bus clock */
    ui2c->BRGEN &= ~UI2C_BRGEN_CLKDIV_Msk;
    ui2c->BRGEN |=  (u32ClkDiv << UI2C_BRGEN_CLKDIV_Pos);

    return ( u32Pclk / ((u32ClkDiv+1U)<<1U) );
}

/**
 *    @brief        This function gets the interrupt flag of USCI_I2C module
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u32Mask         The combination of all related interrupt sources.
 *                                  Each bit corresponds to a interrupt source.
 *                                  This parameter decides which interrupt flags will be read. It is combination of:
 *                                  - \ref UI2C_TO_INT_MASK
 *                                  - \ref UI2C_STAR_INT_MASK
 *                                  - \ref UI2C_STOR_INT_MASK
 *                                  - \ref UI2C_NACK_INT_MASK
 *                                  - \ref UI2C_ARBLO_INT_MASK
 *                                  - \ref UI2C_ERR_INT_MASK
 *                                  - \ref UI2C_ACK_INT_MASK
 *
 *    @return       Interrupt flags of selected sources.
 *
 *    @details      Use this function to get USCI_I2C interrupt flag when module occurs interrupt event.
 */
uint32_t UI2C_GetIntFlag(UI2C_T *ui2c, uint32_t u32Mask)
{
    uint32_t u32IntFlag = 0U;
    uint32_t u32TmpValue;

    u32TmpValue = ui2c->PROTSTS & UI2C_PROTSTS_TOIF_Msk;
    /* Check Time-out Interrupt Flag */
    if((u32Mask & UI2C_TO_INT_MASK) && (u32TmpValue))
    {
        u32IntFlag |= UI2C_TO_INT_MASK;
    }

    u32TmpValue = ui2c->PROTSTS & UI2C_PROTSTS_STARIF_Msk;
    /* Check Start Condition Received Interrupt Flag */
    if((u32Mask & UI2C_STAR_INT_MASK) && (u32TmpValue))
    {
        u32IntFlag |= UI2C_STAR_INT_MASK;
    }

    u32TmpValue = ui2c->PROTSTS & UI2C_PROTSTS_STORIF_Msk;
    /* Check Stop Condition Received Interrupt Flag */
    if((u32Mask & UI2C_STOR_INT_MASK) && (u32TmpValue))
    {
        u32IntFlag |= UI2C_STOR_INT_MASK;
    }

    u32TmpValue = ui2c->PROTSTS & UI2C_PROTSTS_NACKIF_Msk;
    /* Check Non-Acknowledge Interrupt Flag */
    if((u32Mask & UI2C_NACK_INT_MASK) && (u32TmpValue))
    {
        u32IntFlag |= UI2C_NACK_INT_MASK;
    }

    u32TmpValue = ui2c->PROTSTS & UI2C_PROTSTS_ARBLOIF_Msk;
    /* Check Arbitration Lost Interrupt Flag */
    if((u32Mask & UI2C_ARBLO_INT_MASK) && (u32TmpValue))
    {
        u32IntFlag |= UI2C_ARBLO_INT_MASK;
    }

    u32TmpValue = ui2c->PROTSTS & UI2C_PROTSTS_ERRIF_Msk;
    /* Check Error Interrupt Flag */
    if((u32Mask & UI2C_ERR_INT_MASK) && (u32TmpValue))
    {
        u32IntFlag |= UI2C_ERR_INT_MASK;
    }

    u32TmpValue = ui2c->PROTSTS & UI2C_PROTSTS_ACKIF_Msk;
    /* Check Acknowledge Interrupt Flag */
    if((u32Mask & UI2C_ACK_INT_MASK) && (u32TmpValue))
    {
        u32IntFlag |= UI2C_ACK_INT_MASK;
    }

    return u32IntFlag;
}

/**
 *    @brief        This function clears the interrupt flag of USCI_I2C module.
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u32Mask         The combination of all related interrupt sources.
 *                                  Each bit corresponds to a interrupt source.
 *                                  This parameter decides which interrupt flags will be cleared. It is combination of:
 *                                  - \ref UI2C_TO_INT_MASK
 *                                  - \ref UI2C_STAR_INT_MASK
 *                                  - \ref UI2C_STOR_INT_MASK
 *                                  - \ref UI2C_NACK_INT_MASK
 *                                  - \ref UI2C_ARBLO_INT_MASK
 *                                  - \ref UI2C_ERR_INT_MASK
 *                                  - \ref UI2C_ACK_INT_MASK
 *
 *    @return       None
 *
 *    @details      Use this function to clear USCI_I2C interrupt flag when module occurs interrupt event and set flag.
 */
void UI2C_ClearIntFlag(UI2C_T *ui2c, uint32_t u32Mask)
{
    /* Clear Time-out Interrupt Flag */
    if(u32Mask & UI2C_TO_INT_MASK)
    {
        ui2c->PROTSTS = UI2C_PROTSTS_TOIF_Msk;
    }

    /* Clear Start Condition Received Interrupt Flag */
    if(u32Mask & UI2C_STAR_INT_MASK)
    {
        ui2c->PROTSTS = UI2C_PROTSTS_STARIF_Msk;
    }

    /* Clear Stop Condition Received Interrupt Flag */
    if(u32Mask & UI2C_STOR_INT_MASK)
    {
        ui2c->PROTSTS = UI2C_PROTSTS_STORIF_Msk;
    }

    /* Clear Non-Acknowledge Interrupt Flag */
    if(u32Mask & UI2C_NACK_INT_MASK)
    {
        ui2c->PROTSTS = UI2C_PROTSTS_NACKIF_Msk;
    }

    /* Clear Arbitration Lost Interrupt Flag */
    if(u32Mask & UI2C_ARBLO_INT_MASK)
    {
        ui2c->PROTSTS = UI2C_PROTSTS_ARBLOIF_Msk;
    }

    /* Clear Error Interrupt Flag */
    if(u32Mask & UI2C_ERR_INT_MASK)
    {
        ui2c->PROTSTS = UI2C_PROTSTS_ERRIF_Msk;
    }

    /* Clear Acknowledge Interrupt Flag */
    if(u32Mask & UI2C_ACK_INT_MASK)
    {
        ui2c->PROTSTS = UI2C_PROTSTS_ACKIF_Msk;
    }
}

/**
 *    @brief        This function returns the data stored in data register of USCI_I2C module.
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *
 *    @return       USCI_I2C data.
 *
 *    @details      To read a byte data from USCI_I2C module receive data register.
 */
uint32_t UI2C_GetData(UI2C_T *ui2c)
{
    return ( ui2c->RXDAT );
}

/**
 *    @brief        This function writes a byte data to data register of USCI_I2C module
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u8Data          The data which will be written to data register of USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      To write a byte data to transmit data register to transmit data.
 */
void UI2C_SetData(UI2C_T *ui2c, uint8_t u8Data)
{
    ui2c->TXDAT = u8Data;
}

/**
 *    @brief        Configure slave address and enable GC mode
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u8SlaveNo       Slave channel number [0/1]
 *    @param[in]    u16SlaveAddr    The slave address.
 *    @param[in]    u8GCMode        GC mode enable or not. Valid values are:
 *                                  - \ref UI2C_GCMODE_ENABLE
 *                                  - \ref UI2C_GCMODE_DISABLE
 *
 *    @return None
 *
 *    @details      To configure USCI_I2C module slave address and GC mode.
 */
void UI2C_SetSlaveAddr(UI2C_T *ui2c, uint8_t u8SlaveNo, uint16_t u16SlaveAddr, uint8_t u8GCMode)
{
    if(u8SlaveNo)
    {
        ui2c->DEVADDR1  = u16SlaveAddr;
    }
    else
    {
        ui2c->DEVADDR0  = u16SlaveAddr;
    }

    ui2c->PROTCTL  = (ui2c->PROTCTL & ~UI2C_PROTCTL_GCFUNC_Msk) |u8GCMode;
}

/**
 *    @brief        Configure the mask bit of slave address.
 *
 *    @param[in]    ui2c             The pointer of the specified USCI_I2C module.
 *    @param[in]    u8SlaveNo        Slave channel number [0/1]
 *    @param[in]    u16SlaveAddrMask The slave address mask.
 *
 *    @return None
 *
 *    @details      To configure USCI_I2C module slave  address mask bit.
 *    @note         The corresponding address bit is "Don't Care".
 */
void UI2C_SetSlaveAddrMask(UI2C_T *ui2c, uint8_t u8SlaveNo, uint16_t u16SlaveAddrMask)
{
    if(u8SlaveNo)
    {
        ui2c->ADDRMSK1  = u16SlaveAddrMask;
    }
    else
    {
        ui2c->ADDRMSK0  = u16SlaveAddrMask;
    }
}

/**
 *    @brief        This function enables time-out function and configures timeout counter
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u32TimeoutCnt   Timeout counter. Valid values are between 0~0x3FF
 *
 *    @return       None
 *
 *    @details      To enable USCI_I2C bus time-out function and set time-out counter.
 */
void UI2C_EnableTimeout(UI2C_T *ui2c, uint32_t u32TimeoutCnt)
{
    ui2c->PROTCTL = (ui2c->PROTCTL & ~UI2C_PROTCTL_TOCNT_Msk) | (u32TimeoutCnt << UI2C_PROTCTL_TOCNT_Pos);
    ui2c->BRGEN = (ui2c->BRGEN & ~UI2C_BRGEN_TMCNTSRC_Msk) | UI2C_BRGEN_TMCNTEN_Msk;
}

/**
 *    @brief        This function disables time-out function
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      To disable USCI_I2C bus time-out function.
 */
void UI2C_DisableTimeout(UI2C_T *ui2c)
{
    ui2c->PROTCTL &= ~UI2C_PROTCTL_TOCNT_Msk;
    ui2c->BRGEN &= ~UI2C_BRGEN_TMCNTEN_Msk;
}

/**
 *    @brief        This function enables the wakeup function of USCI_I2C module
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *    @param[in]    u8WakeupMode    The wake-up mode selection. Valid values are:
 *                                  - \ref UI2C_DATA_TOGGLE_WK
 *                                  - \ref UI2C_ADDR_MATCH_WK
 *
 *    @return       None
 *
 *    @details      To enable USCI_I2C module wake-up function.
 */
void UI2C_EnableWakeup(UI2C_T *ui2c, uint8_t u8WakeupMode)
{
    ui2c->WKCTL = (ui2c->WKCTL & ~UI2C_WKCTL_WKADDREN_Msk) | (u8WakeupMode | UI2C_WKCTL_WKEN_Msk);
}

/**
 *    @brief        This function disables the wakeup function of USCI_I2C module
 *
 *    @param[in]    ui2c            The pointer of the specified USCI_I2C module.
 *
 *    @return       None
 *
 *    @details      To disable USCI_I2C module wake-up function.
 */
void UI2C_DisableWakeup(UI2C_T *ui2c)
{
    ui2c->WKCTL &= ~UI2C_WKCTL_WKEN_Msk;
}

/**
  * @brief      Write a byte to Slave
  *
  * @param[in]  *ui2c           The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[in]  data            Write a byte data to Slave
  *
  * @retval     0               Write data success
  * @retval     1               Write data fail, or bus occurs error events
  *
  * @details    The function is used for USCI_I2C Master write a byte data to Slave.
  *
  */

uint8_t UI2C_WriteByte(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t data)
{
    uint8_t u8Xfering = 1U, u8Err = 0U, u8Ctrl = 0U;
    enum UI2C_MASTER_EVENT eEvent = MASTER_SEND_START;

    UI2C_START(ui2c);                                                       /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);     /* Clear START INT Flag */
            UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x00U);             /* Write SLA+W to Register UI2C_TXDAT */
            eEvent = MASTER_SEND_ADDRESS;
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);      /* Clear ACK INT Flag */

            if (eEvent == MASTER_SEND_ADDRESS)
            {
                UI2C_SET_DATA(ui2c, data);                              /* Write data to UI2C_TXDAT */
                eEvent = MASTER_SEND_DATA;
            }
            else
            {
                u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                /* Clear SI and send STOP */
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);     /* Clear NACK INT Flag */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            u8Err = 1U;
            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                  /* Arbitration Lost */
        default:                                                        /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            u8Err = 1U;
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                 /* Write controlbit to UI2C_PROTCTL register */
    }

    return (u8Err | u8Xfering);                                             /* return (Success)/(Fail) status */
}

/**
  * @brief      Write multi bytes to Slave
  *
  * @param[in]  *ui2c           The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[in]  *data           Pointer to array to write data to Slave
  * @param[in]  u32wLen         How many bytes need to write to Slave
  *
  * @return     A length of how many bytes have been transmitted.
  *
  * @details    The function is used for USCI_I2C Master write multi bytes data to Slave.
  *
  */

uint32_t UI2C_WriteMultiBytes(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t *data, uint32_t u32wLen)
{
    uint8_t u8Xfering = 1U, u8Ctrl = 0U;
    uint32_t u32txLen = 0U;

    UI2C_START(ui2c);                                                       /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);     /* Clear START INT Flag */
            UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x00U);             /* Write SLA+W to Register UI2C_TXDAT */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);      /* Clear ACK INT Flag */

            if (u32txLen < u32wLen)
                UI2C_SET_DATA(ui2c, data[u32txLen++]);                  /* Write data to UI2C_TXDAT */
            else
            {
                u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                /* Clear SI and send STOP */
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);     /* Clear NACK INT Flag */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                  /* Arbitration Lost */
        default:                                                        /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                 /* Write controlbit to UI2C_CTL register */
    }

    return u32txLen;                                                        /* Return bytes length that have been transmitted */
}

/**
  * @brief      Specify a byte register address and write a byte to Slave
  *
  * @param[in]  *ui2c           The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[in]  u8DataAddr      Specify a address (1 byte) of data write to
  * @param[in]  data            A byte data to write it to Slave
  *
  * @retval     0               Write data success
  * @retval     1               Write data fail, or bus occurs error events
  *
  * @details    The function is used for USCI_I2C Master specify a address that data write to in Slave.
  *
  */

uint8_t UI2C_WriteByteOneReg(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t data)
{
    uint8_t u8Xfering = 1U, u8Err = 0U, u8Ctrl = 0U;
    uint32_t u32txLen = 0U;

    UI2C_START(ui2c);                                                       /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);     /* Clear START INT Flag */
            UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x00U);             /* Write SLA+W to Register UI2C_TXDAT */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);      /* Clear ACK INT Flag */

            if (u32txLen == 0U)
            {
                UI2C_SET_DATA(ui2c, u8DataAddr);                        /* Write data address to UI2C_TXDAT */
                u32txLen++;
            }
            else if (u32txLen == 1U)
            {
                UI2C_SET_DATA(ui2c, data);                              /* Write data to UI2C_TXDAT */
                u32txLen++;
            }
            else
            {
                u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                /* Clear SI and send STOP */
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);     /* Clear NACK INT Flag */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            u8Err = 1U;
            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                  /* Arbitration Lost */
        default:                                                        /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            u8Err = 1U;
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                 /* Write controlbit to UI2C_CTL register */
    }

    return (u8Err | u8Xfering);                                             /* return (Success)/(Fail) status */
}


/**
  * @brief      Specify a byte register address and write multi bytes to Slave
  *
  * @param[in]  *ui2c           The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[in]  u8DataAddr      Specify a address (1 byte) of data write to
  * @param[in]  *data           Pointer to array to write data to Slave
  * @param[in]  u32wLen         How many bytes need to write to Slave
  *
  * @return     A length of how many bytes have been transmitted.
  *
  * @details    The function is used for USCI_I2C Master specify a byte address that multi data bytes write to in Slave.
  *
  */

uint32_t UI2C_WriteMultiBytesOneReg(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t *data, uint32_t u32wLen)
{
    uint8_t u8Xfering = 1U, u8Ctrl = 0U;
    uint32_t u32txLen = 0U;
    enum UI2C_MASTER_EVENT eEvent = MASTER_SEND_START;

    UI2C_START(ui2c);                                                       /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);     /* Clear START INT Flag */
            UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x00U);             /* Write SLA+W to Register UI2C_TXDAT */
            eEvent = MASTER_SEND_ADDRESS;
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);      /* Clear ACK INT Flag */

            if (eEvent == MASTER_SEND_ADDRESS)
            {
                UI2C_SET_DATA(ui2c, u8DataAddr);                        /* Write data address to UI2C_TXDAT */
                eEvent = MASTER_SEND_DATA;
            }
            else
            {
                if (u32txLen < u32wLen)
                    UI2C_SET_DATA(ui2c, data[u32txLen++]);              /* Write data to UI2C_TXDAT */
                else
                {
                    u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);            /* Clear SI and send STOP */
                }
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);     /* Clear NACK INT Flag */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                  /* Arbitration Lost */
        default:                                                        /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                 /* Write controlbit to UI2C_CTL register */
    }

    return u32txLen;                                                        /* Return bytes length that have been transmitted */
}

/**
  * @brief      Specify two bytes register address and Write a byte to Slave
  *
  * @param[in]  *ui2c            The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[in]  u16DataAddr     Specify a address (2 byte) of data write to
  * @param[in]  data            Write a byte data to Slave
  *
  * @retval     0               Write data success
  * @retval     1               Write data fail, or bus occurs error events
  *
  * @details    The function is used for USCI_I2C Master specify two bytes address that data write to in Slave.
  *
  */

uint8_t UI2C_WriteByteTwoRegs(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, uint8_t data)
{
    uint8_t u8Xfering = 1U, u8Err = 0U, u8Ctrl = 0U;
    uint32_t u32txLen = 0U;

    UI2C_START(ui2c);                                                           /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);         /* Clear START INT Flag */
            UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x00U);                 /* Write SLA+W to Register UI2C_TXDAT */
            u8Ctrl = UI2C_CTL_PTRG;                                         /* Clear SI */
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);          /* Clear ACK INT Flag */

            if (u32txLen == 0U)
            {
                UI2C_SET_DATA(ui2c, (uint8_t)((u16DataAddr & 0xFF00U) >> 8U));  /* Write Hi byte data address to UI2C_TXDAT */
                u32txLen++;
            }
            else if (u32txLen == 1U)
            {
                UI2C_SET_DATA(ui2c, (uint8_t)(u16DataAddr & 0xFFU));         /* Write Lo byte data address to UI2C_TXDAT */
                u32txLen++;
            }
            else if (u32txLen == 2U)
            {
                UI2C_SET_DATA(ui2c, data);                                  /* Write data to UI2C_TXDAT */
                u32txLen++;
            }
            else
            {
                u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                /* Clear SI and send STOP */
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);         /* Clear NACK INT Flag */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                        /* Clear SI and send STOP */
            u8Err = 1U;
            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                      /* Arbitration Lost */
        default:                                                            /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                        /* Clear SI and send STOP */
            u8Err = 1U;
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                     /* Write controlbit to UI2C_CTL register */
    }

    return (u8Err | u8Xfering);
}


/**
  * @brief      Specify two bytes register address and write multi bytes to Slave
  *
  * @param[in]  *ui2c           The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[in]  u16DataAddr     Specify a address (2 bytes) of data write to
  * @param[in]  *data           Pointer to array to write data to Slave
  * @param[in]  u32wLen         How many bytes need to write to Slave
  *
  * @return     A length of how many bytes have been transmitted.
  *
  * @details    The function is used for USCI_I2C Master specify a byte address that multi data write to in Slave.
  *
  */

uint32_t UI2C_WriteMultiBytesTwoRegs(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, uint8_t *data, uint32_t u32wLen)
{
    uint8_t u8Xfering = 1U, u8Addr = 1U, u8Ctrl = 0U;
    uint32_t u32txLen = 0U;
    enum UI2C_MASTER_EVENT eEvent = MASTER_SEND_START;

    UI2C_START(ui2c);                                                           /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);         /* Clear START INT Flag */
            UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x00U);                 /* Write SLA+W to Register UI2C_TXDAT */
            eEvent = MASTER_SEND_ADDRESS;
            u8Ctrl = UI2C_CTL_PTRG;                                         /* Clear SI */
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);          /* Clear ACK INT Flag */

            if (eEvent == MASTER_SEND_ADDRESS)
            {
                UI2C_SET_DATA(ui2c, (uint8_t)((u16DataAddr & 0xFF00U) >> 8U));  /* Write Hi byte data address to UI2C_TXDAT */
                eEvent = MASTER_SEND_DATA;
            }
            else if (eEvent == MASTER_SEND_DATA)
            {
                if (u8Addr)
                {
                    UI2C_SET_DATA(ui2c, (uint8_t)(u16DataAddr & 0xFFU));         /* Write Lo byte data address to UI2C_TXDAT */
                    u8Addr = 0;
                }
                else
                {
                    if (u32txLen < u32wLen)
                    {
                        UI2C_SET_DATA(ui2c, data[u32txLen++]);                  /* Write data to UI2C_TXDAT */
                    }
                    else
                    {
                        u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                /* Clear SI and send STOP */
                    }
                }
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);         /* Clear NACK INT Flag */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                        /* Clear SI and send STOP */
            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                      /* Arbitration Lost */
        default:                                                            /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                        /* Clear SI and send STOP */
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                     /* Write controlbit to UI2C_CTL register */
    }

    return u32txLen;                                                            /* Return bytes length that have been transmitted */
}

/**
  * @brief      Read a byte from Slave
  *
  * @param[in]  *ui2c           The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  *
  * @return     Read a byte data from Slave
  *
  * @details    The function is used for USCI_I2C Master to read a byte data from Slave.
  *
  */
uint8_t UI2C_ReadByte(UI2C_T *ui2c, uint8_t u8SlaveAddr)
{
    uint8_t u8Xfering = 1U, u8Err = 0U, rdata = 0U, u8Ctrl = 0U;
    enum UI2C_MASTER_EVENT eEvent = MASTER_SEND_START;

    UI2C_START(ui2c);                                                       /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);     /* Clear START INT Flag */
            UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x01U);             /* Write SLA+R to Register UI2C_TXDAT */
            eEvent = MASTER_SEND_H_RD_ADDRESS;
            u8Ctrl = UI2C_CTL_PTRG;
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);      /* Clear ACK INT Flag */
            eEvent = MASTER_READ_DATA;
            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);     /* Clear NACK INT Flag */

            if (eEvent == MASTER_SEND_H_RD_ADDRESS)
            {
                u8Err = 1U;
            }
            else
            {
                rdata = (unsigned char) UI2C_GET_DATA(ui2c);            /* Receive Data */
            }

            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                        /* Clear SI and send STOP */

            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                  /* Arbitration Lost */
        default:                                                        /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            u8Err = 1U;
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                 /* Write controlbit to UI2C_PROTCTL register */
    }

    if (u8Err)
        rdata = 0U;

    return rdata;                                                           /* Return read data */
}


/**
  * @brief      Read multi bytes from Slave
  *
  * @param[in]  *ui2c           The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[out] *rdata          Point to array to store data from Slave
  * @param[in]  u32rLen         How many bytes need to read from Slave
  *
  * @return     A length of how many bytes have been received
  *
  * @details    The function is used for USCI_I2C Master to read multi data bytes from Slave.
  *
  *
  */
uint32_t UI2C_ReadMultiBytes(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t *rdata, uint32_t u32rLen)
{
    uint8_t u8Xfering = 1U, u8Ctrl = 0U;
    uint32_t u32rxLen = 0U;
    enum UI2C_MASTER_EVENT eEvent = MASTER_SEND_START;

    UI2C_START(ui2c);                                                       /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);     /* Clear START INT Flag */
            UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x01U);             /* Write SLA+R to Register UI2C_TXDAT */
            eEvent = MASTER_SEND_H_RD_ADDRESS;
            u8Ctrl = UI2C_CTL_PTRG;
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);      /* Clear ACK INT Flag */

            if (eEvent == MASTER_SEND_H_RD_ADDRESS)
            {
                u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_AA);
                eEvent = MASTER_READ_DATA;
            }
            else
            {
                rdata[u32rxLen++] = (unsigned char) UI2C_GET_DATA(ui2c);    /* Receive Data */

                if (u32rxLen < (u32rLen - 1U))
                    u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_AA);
                else
                    u8Ctrl = UI2C_CTL_PTRG;
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);     /* Clear NACK INT Flag */

            if (eEvent == MASTER_READ_DATA)
                rdata[u32rxLen++] = (unsigned char) UI2C_GET_DATA(ui2c);    /* Receive Data */

            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                        /* Clear SI and send STOP */

            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                  /* Arbitration Lost */
        default:                                                        /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                 /* Write controlbit to UI2C_PROTCTL register */
    }

    return u32rxLen;                                                        /* Return bytes length that have been received */
}


/**
  * @brief      Specify a byte register address and read a byte from Slave
  *
  * @param[in]  *ui2c            The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[in]  u8DataAddr      Specify a address(1 byte) of data read from
  *
  * @return     Read a byte data from Slave
  *
  * @details    The function is used for USCI_I2C Master specify a byte address that a data byte read from Slave.
  *
  *
  */
uint8_t UI2C_ReadByteOneReg(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr)
{
    uint8_t u8Xfering = 1U, u8Err = 0U, rdata = 0U, u8Ctrl = 0U;
    enum UI2C_MASTER_EVENT eEvent = MASTER_SEND_START;

    UI2C_START(ui2c);                                                       /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);     /* Clear START INT Flag */

            if (eEvent == MASTER_SEND_START)
            {
                UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x00U);         /* Write SLA+W to Register UI2C_TXDAT */
                eEvent = MASTER_SEND_ADDRESS;
            }
            else if (eEvent == MASTER_SEND_REPEAT_START)
            {
                UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x01U);        /* Write SLA+R to Register TXDAT */
                eEvent = MASTER_SEND_H_RD_ADDRESS;
            }

            u8Ctrl = UI2C_CTL_PTRG;
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);      /* Clear ACK INT Flag */

            if (eEvent == MASTER_SEND_ADDRESS)
            {
                UI2C_SET_DATA(ui2c, u8DataAddr);                        /* Write data address of register */
                u8Ctrl = UI2C_CTL_PTRG;
                eEvent = MASTER_SEND_DATA;
            }
            else if (eEvent == MASTER_SEND_DATA)
            {
                u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STA);                /* Send repeat START signal */
                eEvent = MASTER_SEND_REPEAT_START;
            }
            else
            {
                /* SLA+R ACK */
                u8Ctrl = UI2C_CTL_PTRG;
                eEvent = MASTER_READ_DATA;
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);     /* Clear NACK INT Flag */

            if (eEvent == MASTER_READ_DATA)
            {
                rdata = (uint8_t) UI2C_GET_DATA(ui2c);                  /* Receive Data */
            }
            else
            {
                u8Err = 1U;
            }

            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                        /* Clear SI and send STOP */

            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                  /* Arbitration Lost */
        default:                                                        /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            u8Err = 1U;
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                 /* Write controlbit to UI2C_PROTCTL register */
    }

    if (u8Err)
        rdata = 0U;                                                 /* If occurs error, return 0 */

    return rdata;                                                  /* Return read data */
}

/**
  * @brief      Specify a byte register address and read multi bytes from Slave
  *
  * @param[in]  *ui2c           The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[in]  u8DataAddr      Specify a address (1 bytes) of data read from
  * @param[out] *rdata          Point to array to store data from Slave
  * @param[in]  u32rLen         How many bytes need to read from Slave
  *
  * @return     A length of how many bytes have been received
  *
  * @details    The function is used for USCI_I2C Master specify a byte address that multi data bytes read from Slave.
  *
  *
  */
uint32_t UI2C_ReadMultiBytesOneReg(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t *rdata, uint32_t u32rLen)
{
    uint8_t u8Xfering = 1U, u8Ctrl = 0U;
    uint32_t u32rxLen = 0U;
    enum UI2C_MASTER_EVENT eEvent = MASTER_SEND_START;

    UI2C_START(ui2c);                                                       /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);     /* Clear START INT Flag */

            if (eEvent == MASTER_SEND_START)
            {
                UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x00U);         /* Write SLA+W to Register UI2C_TXDAT */
                eEvent = MASTER_SEND_ADDRESS;
            }
            else if (eEvent == MASTER_SEND_REPEAT_START)
            {
                UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x01U);        /* Write SLA+R to Register TXDAT */
                eEvent = MASTER_SEND_H_RD_ADDRESS;
            }

            u8Ctrl = UI2C_CTL_PTRG;
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);      /* Clear ACK INT Flag */

            if (eEvent == MASTER_SEND_ADDRESS)
            {
                UI2C_SET_DATA(ui2c, u8DataAddr);                        /* Write data address of register */
                u8Ctrl = UI2C_CTL_PTRG;
                eEvent = MASTER_SEND_DATA;
            }
            else if (eEvent == MASTER_SEND_DATA)
            {
                u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STA);                /* Send repeat START signal */
                eEvent = MASTER_SEND_REPEAT_START;
            }
            else if (eEvent == MASTER_SEND_H_RD_ADDRESS)
            {
                /* SLA+R ACK */
                u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_AA);
                eEvent = MASTER_READ_DATA;
            }
            else
            {
                rdata[u32rxLen++] = (uint8_t) UI2C_GET_DATA(ui2c);      /* Receive Data */

                if (u32rxLen < u32rLen - 1U)
                    u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_AA);
                else
                    u8Ctrl = UI2C_CTL_PTRG;
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);     /* Clear NACK INT Flag */

            if (eEvent == MASTER_READ_DATA)
                rdata[u32rxLen++] = (uint8_t) UI2C_GET_DATA(ui2c);                  /* Receive Data */

            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                        /* Clear SI and send STOP */

            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                  /* Arbitration Lost */
        default:                                                        /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                 /* Write controlbit to UI2C_PROTCTL register */
    }

    return u32rxLen;                                               /* Return bytes length that have been received */
}

/**
  * @brief      Specify two bytes register address and read a byte from Slave
  *
  * @param[in]  *ui2c           The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[in]  u16DataAddr     Specify a address(2 byte) of data read from
  *
  * @return     Read a byte data from Slave
  *
  * @details    The function is used for USCI_I2C Master specify two bytes address that a data byte read from Slave.
  *
  *
  */
uint8_t UI2C_ReadByteTwoRegs(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr)
{
    uint8_t u8Xfering = 1U, u8Err = 0U, rdata = 0U, u8Addr = 1U, u8Ctrl = 0U;
    enum UI2C_MASTER_EVENT eEvent = MASTER_SEND_START;

    UI2C_START(ui2c);                                                       /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);     /* Clear START INT Flag */

            if (eEvent == MASTER_SEND_START)
            {
                UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x00U);        /* Write SLA+W to Register UI2C_TXDAT */
                eEvent = MASTER_SEND_ADDRESS;
            }
            else if (eEvent == MASTER_SEND_REPEAT_START)
            {
                UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x01U);        /* Write SLA+R to Register TXDAT */
                eEvent = MASTER_SEND_H_RD_ADDRESS;
            }

            u8Ctrl = UI2C_CTL_PTRG;
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);      /* Clear ACK INT Flag */

            if (eEvent == MASTER_SEND_ADDRESS)
            {
                UI2C_SET_DATA(ui2c, (uint8_t)((u16DataAddr & 0xFF00U) >> 8U));  /* Write Hi byte address of register */
                eEvent = MASTER_SEND_DATA;
            }
            else if (eEvent == MASTER_SEND_DATA)
            {
                if (u8Addr)
                {
                    UI2C_SET_DATA(ui2c, (uint8_t)(u16DataAddr & 0xFFU));       /* Write Lo byte address of register */
                    u8Addr = 0;
                }
                else
                {
                    u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STA);                /* Send repeat START signal */
                    eEvent = MASTER_SEND_REPEAT_START;
                }
            }
            else
            {
                /* SLA+R ACK */
                u8Ctrl = UI2C_CTL_PTRG;
                eEvent = MASTER_READ_DATA;
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);     /* Clear NACK INT Flag */

            if (eEvent == MASTER_READ_DATA)
            {
                rdata = (uint8_t) UI2C_GET_DATA(ui2c);                  /* Receive Data */
            }
            else
            {
                u8Err = 1U;
            }

            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                        /* Clear SI and send STOP */

            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                  /* Arbitration Lost */
        default:                                                        /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            u8Err = 1U;
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                 /* Write controlbit to UI2C_PROTCTL register */
    }

    if (u8Err)
        rdata = 0U;                                                 /* If occurs error, return 0 */

    return rdata;                                                  /* Return read data */
}

/**
  * @brief      Specify two bytes register address and read multi bytes from Slave
  *
  * @param[in]  *ui2c            The pointer of the specified USCI_I2C module.
  * @param[in]  u8SlaveAddr     Access Slave address(7-bit)
  * @param[in]  u16DataAddr     Specify a address (2 bytes) of data read from
  * @param[out] *rdata          Point to array to store data from Slave
  * @param[in]  u32rLen         How many bytes need to read from Slave
  *
  * @return     A length of how many bytes have been received
  *
  * @details    The function is used for USCI_I2C Master specify two bytes address that multi data bytes read from Slave.
  *
  *
  */
uint32_t UI2C_ReadMultiBytesTwoRegs(UI2C_T *ui2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, uint8_t *rdata, uint32_t u32rLen)
{
    uint8_t u8Xfering = 1U, u8Addr = 1U, u8Ctrl = 0U;
    uint32_t u32rxLen = 0U;
    enum UI2C_MASTER_EVENT eEvent = MASTER_SEND_START;

    UI2C_START(ui2c);                                                       /* Send START */

    while (u8Xfering)
    {
        while (!(UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U));                     /* Wait UI2C new status occur */

        switch (UI2C_GET_PROT_STATUS(ui2c) & 0x3F00U)
        {
        case UI2C_PROTSTS_STARIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STARIF_Msk);     /* Clear START INT Flag */

            if (eEvent == MASTER_SEND_START)
            {
                UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x00U);         /* Write SLA+W to Register UI2C_TXDAT */
                eEvent = MASTER_SEND_ADDRESS;
            }
            else if (eEvent == MASTER_SEND_REPEAT_START)
            {
                UI2C_SET_DATA(ui2c, (u8SlaveAddr << 1U) | 0x01U);        /* Write SLA+R to Register TXDAT */
                eEvent = MASTER_SEND_H_RD_ADDRESS;
            }

            u8Ctrl = UI2C_CTL_PTRG;
            break;

        case UI2C_PROTSTS_ACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_ACKIF_Msk);      /* Clear ACK INT Flag */

            if (eEvent == MASTER_SEND_ADDRESS)
            {
                UI2C_SET_DATA(ui2c, (uint8_t)((u16DataAddr & 0xFF00U) >> 8U));  /* Write Hi byte address of register */
                eEvent = MASTER_SEND_DATA;
            }
            else if (eEvent == MASTER_SEND_DATA)
            {
                if (u8Addr)
                {
                    UI2C_SET_DATA(ui2c, (uint8_t)(u16DataAddr & 0xFFU));       /* Write Lo byte address of register */
                    u8Addr = 0;
                }
                else
                {
                    u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STA);                /* Send repeat START signal */
                    eEvent = MASTER_SEND_REPEAT_START;
                }
            }
            else if (eEvent == MASTER_SEND_H_RD_ADDRESS)
            {
                u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_AA);
                eEvent = MASTER_READ_DATA;
            }
            else
            {
                rdata[u32rxLen++] = (uint8_t) UI2C_GET_DATA(ui2c);      /* Receive Data */

                if (u32rxLen < u32rLen - 1U)
                    u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_AA);
                else
                    u8Ctrl = UI2C_CTL_PTRG;
            }

            break;

        case UI2C_PROTSTS_NACKIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_NACKIF_Msk);     /* Clear NACK INT Flag */

            if (eEvent == MASTER_READ_DATA)
                rdata[u32rxLen++] = (uint8_t) UI2C_GET_DATA(ui2c);                  /* Receive Data */

            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                        /* Clear SI and send STOP */

            break;

        case UI2C_PROTSTS_STORIF_Msk:
            UI2C_CLR_PROT_INT_FLAG(ui2c, UI2C_PROTSTS_STORIF_Msk);     /* Clear STOP INT Flag */
            u8Ctrl = UI2C_CTL_PTRG;                                     /* Clear SI */
            u8Xfering = 0U;
            break;

        case UI2C_PROTSTS_ARBLOIF_Msk:                                  /* Arbitration Lost */
        default:                                                        /* Unknow status */
            u8Ctrl = (UI2C_CTL_PTRG | UI2C_CTL_STO);                    /* Clear SI and send STOP */
            break;
        }

        UI2C_SET_CONTROL_REG(ui2c, u8Ctrl);                                 /* Write controlbit to UI2C_PROTCTL register */
    }

    return u32rxLen;                                                        /* Return bytes length that have been received */
}

/*@}*/ /* end of group USCI_I2C_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USCI_I2C_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
