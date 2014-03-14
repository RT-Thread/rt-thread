/**********************************************************************
* $Id$      lpc_i2c.c           2011-06-02
*//**
* @file     lpc_i2c.c
* @brief    Contains all functions support for I2C firmware library
*           on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup I2C
 * @{
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _I2C

/* Includes ------------------------------------------------------------------- */
#include "lpc_i2c.h"
#include "lpc_clkpwr.h"
#include "lpc_pinsel.h"

/* Private Types -------------------------------------------------------------- */
/** @defgroup I2C_Private_Types I2C Private Types
 * @{
 */

/**
 * @brief I2C device configuration structure type
 */
typedef struct
{
  uint32_t      txrx_setup;                         /* Transmission setup */
  int32_t       dir;                                /* Current direction phase, 0 - write, 1 - read */
} I2C_CFG_T;

/**
 * @}
 */

/* Private Variables ---------------------------------------------------------- */
/**
 * @brief II2C driver data for I2C0, I2C1 and I2C2
 */
static I2C_CFG_T i2cdat[3];

static uint32_t I2C_MasterComplete[3];
static uint32_t I2C_SlaveComplete[3];

static uint32_t I2C_MonitorBufferIndex;

/* Private Functions ---------------------------------------------------------- */

/* Get pointer to expected I2C */
static LPC_I2C_TypeDef* I2C_GetPointer(en_I2C_unitId compId);

/* Generate a start condition on I2C bus (in master mode only) */
static uint32_t I2C_Start (LPC_I2C_TypeDef *I2Cx, I2C_TRANSFER_OPT_Type Opt);

/* Generate a stop condition on I2C bus (in master mode only) */
static void I2C_Stop (LPC_I2C_TypeDef *I2Cx, I2C_TRANSFER_OPT_Type Opt);

/* I2C send byte subroutine */
static uint32_t I2C_SendByte (LPC_I2C_TypeDef *I2Cx, uint8_t databyte);

/* I2C get byte subroutine */
static uint32_t I2C_GetByte (LPC_I2C_TypeDef *I2Cx, uint8_t *retdat, Bool ack);

/* I2C set clock (hz) */
static void I2C_SetClock (LPC_I2C_TypeDef *I2Cx, uint32_t target_clock);

/*--------------------------------------------------------------------------------*/

/********************************************************************//**
 * @brief       Convert from I2C peripheral to number
 * @param[in]   I2Cx: I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @return      I2C number, could be: 0..2
 *********************************************************************/
static LPC_I2C_TypeDef* I2C_GetPointer(en_I2C_unitId compId)
{
    LPC_I2C_TypeDef* pI2C;

    switch (compId)
    {
        case I2C_0:
            pI2C = LPC_I2C0;
            break;

        case I2C_1:
            pI2C = LPC_I2C1;
            break;

        case I2C_2:
            pI2C = LPC_I2C2;
            break;

        default:
            pI2C = NULL;
            break;
    }

    return pI2C;
}


/********************************************************************//**
 * @brief       Generate a start condition on I2C bus (in master mode only)
 * @param[in]   I2Cx: I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   Opt   a I2C_TRANSFER_OPT_Type type that selected for
 *                  interrupt or polling mode.
 * @return      value of I2C status register after generate a start condition
 *********************************************************************/
static uint32_t I2C_Start (LPC_I2C_TypeDef *I2Cx, I2C_TRANSFER_OPT_Type Opt)
{
    // Reset STA, STO, SI
    I2Cx->CONCLR = I2C_I2CONCLR_SIC|I2C_I2CONCLR_STOC|I2C_I2CONCLR_STAC;

    // Enter to Master Transmitter mode
    I2Cx->CONSET = I2C_I2CONSET_STA;

    if(Opt == I2C_TRANSFER_POLLING)
    {
        // Wait for complete
        while (!(I2Cx->CONSET & I2C_I2CONSET_SI));
    }

    return (I2Cx->STAT & I2C_STAT_CODE_BITMASK);
}

/********************************************************************//**
 * @brief       Generate a stop condition on I2C bus (in master mode only)
 * @param[in]   I2Cx: I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   Opt   a I2C_TRANSFER_OPT_Type type that selected for
 *                  interrupt or polling mode.
 * @return      None
 *********************************************************************/
static void I2C_Stop (LPC_I2C_TypeDef *I2Cx, I2C_TRANSFER_OPT_Type Opt)
{
    /* Make sure start bit is not active */
    if (I2Cx->CONSET & I2C_I2CONSET_STA)
    {
        I2Cx->CONCLR = I2C_I2CONCLR_STAC;
    }

    I2Cx->CONSET = I2C_I2CONSET_STO;

    I2Cx->CONCLR = I2C_I2CONCLR_SIC;
    
    if(Opt == I2C_TRANSFER_POLLING)
    {
        // wait for stop is sent
        while(I2Cx->CONSET & I2C_I2CONSET_STO)
        {
            if(I2Cx->CONSET & I2C_I2CONSET_SI)
                I2Cx->CONCLR = I2C_I2CONCLR_SIC;
        }
    }
}

/********************************************************************//**
 * @brief       Send a byte
 * @param[in]   I2Cx: I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   databyte: number of byte
 * @return      value of I2C status register after sending
 *********************************************************************/
static uint32_t I2C_SendByte (LPC_I2C_TypeDef *I2Cx, uint8_t databyte)
{
    uint32_t CodeStatus = I2Cx->STAT & I2C_STAT_CODE_BITMASK;

    if((CodeStatus != I2C_I2STAT_M_TX_START) &&
        (CodeStatus != I2C_I2STAT_M_TX_RESTART) &&
        (CodeStatus != I2C_I2STAT_M_TX_SLAW_ACK)  &&
        (CodeStatus != I2C_I2STAT_M_TX_DAT_ACK)  )
    {
        return CodeStatus;
    }

    I2Cx->DAT = databyte & I2C_I2DAT_BITMASK;

    I2Cx->CONSET = I2C_I2CONSET_AA;

    I2Cx->CONCLR = I2C_I2CONCLR_SIC;

    return (I2Cx->STAT & I2C_STAT_CODE_BITMASK);
}

/********************************************************************//**
 * @brief       Get a byte
 * @param[in]   I2Cx: I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[out]  retdat  pointer to return data
 * @param[in]   ack     assert acknowledge or not, should be: TRUE/FALSE
 * @return      value of I2C status register after sending
 *********************************************************************/
static uint32_t I2C_GetByte (LPC_I2C_TypeDef *I2Cx, uint8_t *retdat, Bool ack)
{
    *retdat = (uint8_t) (I2Cx->DAT & I2C_I2DAT_BITMASK);
    
    if (ack == TRUE)
    {
        I2Cx->CONSET = I2C_I2CONSET_AA;
    }
    else
    {
        I2Cx->CONCLR = I2C_I2CONCLR_AAC;
    }

    I2Cx->CONCLR = I2C_I2CONCLR_SIC;
    
    return (I2Cx->STAT & I2C_STAT_CODE_BITMASK);
}

/*********************************************************************//**
 * @brief       Setup clock rate for I2C peripheral
 * @param[in]   I2Cx    I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   target_clock : clock of SSP (Hz)
 * @return      None
 ***********************************************************************/
static void I2C_SetClock (LPC_I2C_TypeDef *I2Cx, uint32_t target_clock)
{
    uint32_t temp;

    temp = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER) / target_clock;

    /* Set the I2C clock value to register */
    I2Cx->SCLH = (uint32_t)(temp / 2);

    I2Cx->SCLL = (uint32_t)(temp - I2Cx->SCLH);
}


/* End of Private Functions --------------------------------------------------- */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup I2C_Public_Functions
 * @{
 */

/********************************************************************//**
 * @brief       Initializes the I2Cx peripheral with specified parameter.
 * @param[in]   I2Cx    I2C peripheral selected, should be
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   clockrate Target clock rate value to initialized I2C
 *              peripheral (Hz)
 * @return      None
 *********************************************************************/
void I2C_Init(en_I2C_unitId i2cId, uint32_t clockrate)
{
    uint32_t clkSetting;

    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);

    switch (i2cId)
    {
        case I2C_0:
            clkSetting = CLKPWR_PCONP_PCI2C0;
            break;


        case I2C_1:
            clkSetting = CLKPWR_PCONP_PCI2C1;
            break;

        case I2C_2:
            clkSetting = CLKPWR_PCONP_PCI2C2;
            break;

        default:

            return;
    }

    CLKPWR_ConfigPPWR (clkSetting, ENABLE);

    /* Set clock rate */
    I2C_SetClock(I2Cx,clockrate);

    /* Set I2C operation to default */
    I2Cx->CONCLR = (I2C_I2CONCLR_AAC | I2C_I2CONCLR_STAC | I2C_I2CONCLR_I2ENC);
}

/*********************************************************************//**
 * @brief       De-initializes the I2C peripheral registers to their
 *                  default reset values.
 * @param[in]   I2Cx    I2C peripheral selected, should be
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @return      None
 **********************************************************************/
void I2C_DeInit(en_I2C_unitId i2cId)
{
    uint32_t clkSetting;

    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);

    /* Disable I2C control */
    I2Cx->CONCLR = 0xFF;

    switch (i2cId)
    {
        case I2C_0:
            clkSetting = CLKPWR_PCONP_PCI2C0;
            break;


        case I2C_1:
            clkSetting = CLKPWR_PCONP_PCI2C1;
            break;

        case I2C_2:
            clkSetting = CLKPWR_PCONP_PCI2C2;
            break;

        default:

            return;
    }

    CLKPWR_ConfigPPWR (clkSetting, DISABLE);
}

/*********************************************************************//**
 * @brief       Enable or disable I2C peripheral's operation
 * @param[in]   I2Cx I2C peripheral selected, should be
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   NewState New State of I2Cx peripheral's operation
 * @return      none
 **********************************************************************/
void I2C_Cmd(en_I2C_unitId i2cId, en_I2C_Mode Mode, FunctionalState NewState)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);

    if (NewState == ENABLE)
    {
        if(Mode != I2C_SLAVE_MODE)
            I2Cx->CONSET = I2C_I2CONSET_I2EN;
        else
            I2Cx->CONSET = I2C_I2CONSET_I2EN | I2C_I2CONSET_AA;
    }
    else
    {
        I2Cx->CONCLR = I2C_I2CONCLR_I2ENC;
    }
}

/*********************************************************************//**
 * @brief       Enable/Disable interrupt for I2C peripheral
 * @param[in]   I2Cx    I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   NewState    New State of I2C peripheral interrupt in NVIC core
 *              should be:
 *              - ENABLE: enable interrupt for this I2C peripheral
 *              - DISABLE: disable interrupt for this I2C peripheral
 * @return      None
 **********************************************************************/
void I2C_IntCmd (en_I2C_unitId i2cId, Bool NewState)
{
    IRQn_Type irq;

    switch (i2cId)
    {
        case I2C_0:
            irq = I2C0_IRQn;
            break;

        case I2C_1:
            irq = I2C1_IRQn;
            break;

        case I2C_2:
            irq = I2C2_IRQn;
            break;

        default:

            return;
    }

    if (NewState)
    {
        NVIC_EnableIRQ(irq);
    }
    else
    {
        NVIC_DisableIRQ(irq);
    }

    return;
}
/*********************************************************************//**
 * @brief       Handle I2C Master states.
 * @param[in]   I2Cx    I2C peripheral selected, should be:
 *              - I2C_0
 *              - I2C_1
 *              - I2C_2
 * @param[in]   CodeStatus  I2C state
 * @param[in]   TransferCfg   Pointer to a I2C_S_SETUP_Type structure that
 *                              contains specified information about the
 *                              configuration for master transfer.
 * @param[in]   Opt             a I2C_TRANSFER_OPT_Type type that selected for
 *                              interrupt or polling mode.
 * @return      It can be
 *              - I2C_OK
 *              -I2C_BYTE_RECV
 *              -I2C_BYTE_SENT
 *              -I2C_SEND_END
 *              -I2C_RECV_END
 *              - I2C_ERR
 *              - I2C_NAK_RECV
 **********************************************************************/
int32_t I2C_MasterHanleStates(en_I2C_unitId i2cId, 
                                uint32_t CodeStatus, 
                                I2C_M_SETUP_Type *TransferCfg,
                                I2C_TRANSFER_OPT_Type Opt
                                )
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);
    uint8_t *txdat;
    uint8_t *rxdat;
    uint8_t tmp;
    int32_t Ret = I2C_OK;
    
    //get buffer to send/receive
    txdat = (uint8_t *) &TransferCfg->tx_data[TransferCfg->tx_count];
    rxdat = (uint8_t *) &TransferCfg->rx_data[TransferCfg->rx_count];

    switch(CodeStatus)
    {
        case I2C_I2STAT_M_TX_START:
        case I2C_I2STAT_M_TX_RESTART:
        //case I2C_I2STAT_M_RX_START:
        //case I2C_I2STAT_M_RX_RESTART
            // Send data first
            if(TransferCfg->tx_count < TransferCfg->tx_length)
            {
                /* Send slave address + WR direction bit = 0 ----------------------------------- */
                I2C_SendByte(I2Cx, (TransferCfg->sl_addr7bit << 1));
                Ret = I2C_BYTE_SENT;
            }
            else if (TransferCfg->rx_count  < TransferCfg->rx_length)
            {
                /* Send slave address + RD direction bit = 1 ----------------------------------- */
                I2C_SendByte(I2Cx, ((TransferCfg->sl_addr7bit << 1) | 0x01));
                Ret = I2C_BYTE_SENT;
            }
            // Clear STA bit after the slave address is sent
            I2Cx->CONCLR = I2C_I2CONCLR_STAC;
            break;
        case I2C_I2STAT_M_TX_SLAW_ACK:
        case I2C_I2STAT_M_TX_DAT_ACK:
            
            if(TransferCfg->tx_count < TransferCfg->tx_length)
            {
                I2C_SendByte(I2Cx, *txdat);
                
                txdat++;

                TransferCfg->tx_count++;

                Ret = I2C_BYTE_SENT;
            }
            else
            {
                if(TransferCfg->rx_count >= TransferCfg->rx_length)
                {
                    I2C_Stop(I2Cx, Opt);
                }
                Ret = I2C_SEND_END;
                
                
            }
            
            break;
        case I2C_I2STAT_M_TX_DAT_NACK:
            if(TransferCfg->rx_count >= TransferCfg->rx_length)
            {
                I2C_Stop(I2Cx, Opt);
            }
            Ret = I2C_SEND_END;
            break;
        case I2C_I2STAT_M_RX_ARB_LOST:
        case I2C_I2STAT_S_RX_ARB_LOST_M_GENCALL:
        case I2C_I2STAT_S_TX_ARB_LOST_M_SLA:
        //case I2C_I2STAT_M_TX_ARB_LOST:
            I2C_Stop(I2Cx, Opt);
            Ret = I2C_ERR;
            break;
        case I2C_I2STAT_M_RX_SLAR_ACK:
            if(TransferCfg->rx_length > 1)
                I2Cx->CONSET = I2C_I2CONSET_AA;
            else
                I2Cx->CONCLR = I2C_I2CONCLR_AAC;
            I2Cx->CONCLR = I2C_I2CONCLR_SIC;

            Ret = I2C_BYTE_RECV;
            break;
        case I2C_I2STAT_M_RX_DAT_ACK:
            if (TransferCfg->rx_count <TransferCfg->rx_length)
            {
                if ((TransferCfg->rx_length > 1) && (TransferCfg->rx_count < (TransferCfg->rx_length - 2)))
                {
                    I2C_GetByte(I2Cx, &tmp, TRUE);

                    Ret = I2C_BYTE_RECV;
                    
                }
                else  // the next byte is the last byte, send NACK instead.
                 {
                    I2C_GetByte(I2Cx, &tmp, FALSE);
                    Ret = I2C_BYTE_RECV;
                 }
                *rxdat++ = tmp;

                TransferCfg->rx_count++;
            }
            else
            {
                I2C_Stop(I2Cx, Opt);
                Ret = I2C_RECV_END;
            }
            
            break;
        case I2C_I2STAT_M_RX_DAT_NACK:
            I2C_GetByte(I2Cx, &tmp, FALSE);
            if (TransferCfg->rx_count < TransferCfg->rx_length)
            {
                *rxdat++ = tmp;
                TransferCfg->rx_count++;
            }
            I2C_Stop(I2Cx, Opt);
            Ret = I2C_RECV_END;
            break;
        
        case I2C_I2STAT_M_RX_SLAR_NACK:
        case I2C_I2STAT_M_TX_SLAW_NACK:
        case I2C_I2STAT_BUS_ERROR:
            // Send STOP condition
            I2C_Stop(I2Cx, Opt);
            Ret = I2C_ERR;
            break;
        /* No status information */
        case I2C_I2STAT_NO_INF:
          if ((TransferCfg->tx_count <TransferCfg->tx_length)||
               (TransferCfg->rx_count <TransferCfg->rx_length))
          {
            I2C_Stop(I2Cx, Opt);
            Ret = I2C_ERR;
          }
          else
          {
            Ret = I2C_RECV_END;
          }
          break;
        default:
            I2Cx->CONCLR = I2C_I2CONCLR_SIC;
            break;
    }
    
    return Ret;
}

/*********************************************************************//**
 * @brief       Handle I2C Slave states.
 * @param[in]   I2Cx    I2C peripheral selected, should be:
 *              - I2C_0
 *              - I2C_1
 *              - I2C_2
 * @param[in]   CodeStatus  I2C state
 * @param[in]   TransferCfg   Pointer to a I2C_S_SETUP_Type structure that
 *                              contains specified information about the
 *                              configuration for master transfer.
 * @return      It can be
 *              - I2C_OK
 *              -I2C_BYTE_RECV
 *              -I2C_BYTE_SENT
 *              -I2C_SEND_END
 *              -I2C_RECV_END
 *              - I2C_ERR
 *              - I2C_NAK_RECV
 **********************************************************************/
int32_t I2C_SlaveHanleStates(en_I2C_unitId i2cId, 
                             uint32_t CodeStatus, 
                             I2C_S_SETUP_Type *TransferCfg)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);
    int32_t Ret = I2C_OK;
    uint8_t *txdat;
    uint8_t *rxdat;

    //get buffer to send/receive
    txdat = (uint8_t *) &TransferCfg->tx_data[TransferCfg->tx_count];
    rxdat = (uint8_t *) &TransferCfg->rx_data[TransferCfg->rx_count];
    
    switch (CodeStatus)
    {
        /* Reading phase -------------------------------------------------------- */
        /* Own SLA+R has been received, ACK has been returned */
        case I2C_I2STAT_S_RX_SLAW_ACK:

        /* General call address has been received, ACK has been returned */
        case I2C_I2STAT_S_RX_GENCALL_ACK:
            I2Cx->CONSET = I2C_I2CONSET_AA;
            I2Cx->CONCLR = I2C_I2CONCLR_SIC;
            break;
        /* Arbitration has been lost in Slave Address + R/W bit as bus Master. General Call has
            been received and ACK has been returned.*/
        case I2C_I2STAT_S_RX_ARB_LOST_M_GENCALL:
            I2Cx->CONSET = I2C_I2CONSET_AA|I2C_I2CONSET_STA;
            I2Cx->CONCLR = I2C_I2CONCLR_SIC;
            break;
        /* Previously addressed with own SLA;
         * DATA byte has been received;
         * ACK has been returned */
        case I2C_I2STAT_S_RX_ARB_LOST_M_SLA:
        case I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK:

            /*
             * All data bytes that over-flow the specified receive
             * data length, just ignore them.
             */
            if ((TransferCfg->rx_count < TransferCfg->rx_length) && (TransferCfg->rx_data != NULL))
            {
                *rxdat++ = (uint8_t)I2Cx->DAT;

                TransferCfg->rx_count++;

                Ret = I2C_BYTE_RECV;
            }
            if(TransferCfg->rx_count == (TransferCfg->rx_length) ) {
                I2Cx->CONCLR = I2C_I2CONCLR_AAC|I2C_I2CONCLR_SIC;
                Ret = I2C_BYTE_RECV;
            }
            else {
                I2Cx->CONSET = I2C_I2CONSET_AA;
                I2Cx->CONCLR = I2C_I2CONCLR_SIC;
            }
            
            break;
        /* DATA has been received, Only the first data byte will be received with ACK. Additional
                data will be received with NOT ACK. */
        case I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK:
            if ((TransferCfg->rx_count < TransferCfg->rx_length) && (TransferCfg->rx_data != NULL))
            {
                *rxdat++ = (uint8_t)I2Cx->DAT;

                TransferCfg->rx_count++;

                Ret = I2C_BYTE_RECV;
            }
            I2Cx->CONCLR = I2C_I2CONCLR_AAC|I2C_I2CONCLR_SIC;
            break;

        /* Writing phase -------------------------------------------------------- */
        /* Own SLA+R has been received, ACK has been returned */
        case I2C_I2STAT_S_TX_SLAR_ACK:

        /* Data has been transmitted, ACK has been received */
        case I2C_I2STAT_S_TX_DAT_ACK:
            /*
             * All data bytes that over-flow the specified receive
             * data length, just ignore them.
             */
            if ((TransferCfg->tx_count < TransferCfg->tx_length) && (TransferCfg->tx_data != NULL))
            {
                I2Cx->DAT = *txdat++;

                TransferCfg->tx_count++;

                Ret = I2C_BYTE_SENT;
            }

            I2Cx->CONSET = I2C_I2CONSET_AA;
            I2Cx->CONCLR = I2C_I2CONCLR_SIC;
            break;
        /* Arbitration lost in Slave Address and R/W bit as bus Master. Own Slave Address + Read
                has been received, ACK has been returned. */
        case I2C_I2STAT_S_TX_ARB_LOST_M_SLA:
            if ((TransferCfg->tx_count < TransferCfg->tx_length) && (TransferCfg->tx_data != NULL))
            {
                I2Cx->DAT = *txdat++;

                TransferCfg->tx_count++;

                Ret = I2C_BYTE_SENT;
            }
            I2Cx->CONSET = I2C_I2CONSET_AA|I2C_I2CONSET_STA;
            I2Cx->CONCLR = I2C_I2CONCLR_SIC;
            break;
            
        case I2C_I2STAT_S_TX_LAST_DAT_ACK:
        /* Data has been transmitted, NACK has been received,
         * that means there's no more data to send, exit now */
        /*
         * Note: Don't wait for stop event since in slave transmit mode,
         * since there no proof lets us know when a stop signal has been received
         * on slave side.
         */
        case I2C_I2STAT_S_TX_DAT_NACK:
            I2Cx->CONSET = I2C_I2CONSET_AA;
            I2Cx->CONCLR = I2C_I2CONCLR_SIC;
            Ret = I2C_SEND_END;
            break;

        /* Previously addressed with own SLA;
         * DATA byte has been received;
         * NOT ACK has been returned */
        case I2C_I2STAT_S_RX_PRE_SLA_DAT_NACK:

        /* DATA has been received, NOT ACK has been returned */
        case I2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK:
            I2Cx->CONSET = I2C_I2CONSET_AA;
            I2Cx->CONCLR = I2C_I2CONCLR_SIC;
            Ret = I2C_RECV_END;
            break;

        /*
         * Note that: Return code only let us know a stop condition mixed
         * with a repeat start condition in the same code value.
         * So we should provide a time-out. In case this is really a stop
         * condition, this will return back after time out condition. Otherwise,
         * next session that is slave receive data will be completed.
         */

        /* A Stop or a repeat start condition */
        case I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX:
            I2Cx->CONSET = I2C_I2CONSET_AA;
            I2Cx->CONCLR = I2C_I2CONCLR_SIC;
            Ret = I2C_STA_STO_RECV;
            break;

        /* No status information */
        case I2C_I2STAT_NO_INF:
        /* Other status must be captured */
        default:
            I2Cx->CONSET = I2C_I2CONSET_AA;
            I2Cx->CONCLR = I2C_I2CONCLR_SIC;
            break;

    }

    return Ret;
}
/*********************************************************************//**
 * @brief       General Master Interrupt handler for I2C peripheral
 * @param[in]   I2Cx    I2C peripheral selected, should be:
 *              - LPC_I2C
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @return      None
 **********************************************************************/
void I2C_MasterHandler(en_I2C_unitId i2cId)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);
    uint8_t returnCode;
    I2C_M_SETUP_Type *txrx_setup;
    int32_t Ret = I2C_OK;

    txrx_setup = (I2C_M_SETUP_Type *) i2cdat[i2cId].txrx_setup;

    returnCode = (I2Cx->STAT & I2C_STAT_CODE_BITMASK);

    // Save current status
    txrx_setup->status = returnCode;

    Ret = I2C_MasterHanleStates(i2cId, returnCode, txrx_setup, I2C_TRANSFER_INTERRUPT);

    if(I2C_CheckError(Ret))
    {
        if(txrx_setup->retransmissions_count < txrx_setup->retransmissions_max)
        {
            // Retry
            txrx_setup->retransmissions_count ++;
            txrx_setup->tx_count = 0;
            txrx_setup->rx_count = 0;
            // Reset STA, STO, SI
            I2C_Start(I2Cx, I2C_TRANSFER_INTERRUPT);
            return;
        }
        else
        {
            goto s_int_end;
        }
    }
    else if (Ret & I2C_SEND_END)
    {
        // If no need to wait for data from Slave
        if(txrx_setup->rx_count >= (txrx_setup->rx_length)) 
        {
            goto s_int_end;
        }
        else    // Start to wait for data from Slave
        {
            // Reset STA, STO, SI
            I2C_Start(I2Cx, I2C_TRANSFER_INTERRUPT);
            return;
        }
    }
    else if (Ret & I2C_RECV_END) 
    {
        goto s_int_end;
    }
    else
    {
        return;
    }

s_int_end:
    // Disable interrupt
    I2C_IntCmd(i2cId, FALSE);

    I2Cx->CONCLR = I2C_I2CONCLR_AAC | I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC;

    I2C_MasterComplete[i2cId] = TRUE;
        
}


/*********************************************************************//**
 * @brief       General Slave Interrupt handler for I2C peripheral
 * @param[in]   I2Cx    I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @return      None
 **********************************************************************/
void I2C_SlaveHandler (en_I2C_unitId i2cId)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);

    uint8_t returnCode;
    I2C_S_SETUP_Type *txrx_setup;
    uint32_t timeout;
    int32_t Ret = I2C_OK;

    txrx_setup = (I2C_S_SETUP_Type *) i2cdat[i2cId].txrx_setup;

handle_state:

    returnCode = (I2Cx->STAT & I2C_STAT_CODE_BITMASK);
    // Save current status
    txrx_setup->status = returnCode;


    Ret = I2C_SlaveHanleStates(i2cId, returnCode, txrx_setup);

    if(I2C_CheckError(Ret))
    {
        goto s_int_end;
    }
    else if (Ret & I2C_STA_STO_RECV)
    {
        if((txrx_setup->tx_count >= (txrx_setup->tx_length)) &&
            (txrx_setup->rx_count >= (txrx_setup->rx_length)))
        {
            goto s_int_end;
        }
        // Temporally lock the interrupt for timeout condition
        I2C_IntCmd(i2cId, FALSE);
        // enable time out
        timeout = I2C_SLAVE_TIME_OUT;
        while(1)
        {
            if (I2Cx->CONSET & I2C_I2CONSET_SI)
            {
                // re-Enable interrupt
                I2C_IntCmd(i2cId, TRUE);
                goto handle_state;
            }
            else
            {
                timeout--;
                if (timeout == 0)
                {
                    // timeout occur, it's really a stop condition
                    txrx_setup->status |= I2C_SETUP_STATUS_DONE;
                    goto s_int_end;
                }
            }
        }   
    }
    else if(Ret &I2C_SEND_END)
    {
        goto s_int_end;
    }
    else
    {
        return;
    }

s_int_end:
    // Disable interrupt
    I2C_IntCmd(i2cId, FALSE);
    I2Cx->CONCLR = I2C_I2CONCLR_AAC | I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC;

    I2C_SlaveComplete[i2cId] = TRUE;
}

/*********************************************************************//**
 * @brief       Transmit and Receive data in master mode
 * @param[in]   I2Cx            I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   TransferCfg     Pointer to a I2C_M_SETUP_Type structure that
 *                              contains specified information about the
 *                              configuration for master transfer.
 * @param[in]   Opt             a I2C_TRANSFER_OPT_Type type that selected for
 *                              interrupt or polling mode.
 * @return      SUCCESS or ERROR
 *
 * Note:
 * - In case of using I2C to transmit data only, either transmit length set to 0
 * or transmit data pointer set to NULL.
 * - In case of using I2C to receive data only, either receive length set to 0
 * or receive data pointer set to NULL.
 * - In case of using I2C to transmit followed by receive data, transmit length,
 * transmit data pointer, receive length and receive data pointer should be set
 * corresponding.
 **********************************************************************/
Status I2C_MasterTransferData(en_I2C_unitId i2cId, I2C_M_SETUP_Type *TransferCfg,
                                                                    I2C_TRANSFER_OPT_Type Opt)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);

    uint32_t CodeStatus;
    int32_t Ret = I2C_OK;

    // Reset I2C setup value to default state
    TransferCfg->tx_count = 0;
    TransferCfg->rx_count = 0;
    TransferCfg->status = 0;

    if (Opt == I2C_TRANSFER_POLLING)
    {
        /* First Start condition -------------------------------------------------------------- */
        TransferCfg->retransmissions_count = 0;
retry:
        // Reset I2C setup value to default state
        TransferCfg->tx_count = 0;
        TransferCfg->rx_count = 0;

        // Start command
        CodeStatus = I2C_Start(I2Cx, I2C_TRANSFER_POLLING);
        
        while(1)    // send data first and then receive data from Slave.
        {
            Ret = I2C_MasterHanleStates(i2cId, CodeStatus, TransferCfg, I2C_TRANSFER_POLLING);
            if(I2C_CheckError(Ret))
            {
                TransferCfg->retransmissions_count++;
                if (TransferCfg->retransmissions_count > TransferCfg->retransmissions_max){
                        // save status
                        TransferCfg->status = CodeStatus | I2C_SETUP_STATUS_NOACKF;
                        goto error;
                    } else {
                        goto retry;
                    }
            }
            else if( (Ret & I2C_BYTE_SENT) ||
                    (Ret & I2C_BYTE_RECV))
            {
                // Wait for sending ends/ Wait for next byte            
                while (!(I2Cx->CONSET & I2C_I2CONSET_SI));
            }
            else if (Ret & I2C_SEND_END) // already send all data
            {
                // If no need to wait for data from Slave
                if(TransferCfg->rx_count >= (TransferCfg->rx_length)) 
                {
                    break;
                }
                else
                {
                    I2C_Start(I2Cx, I2C_TRANSFER_POLLING);
                }
            }
            else if (Ret & I2C_RECV_END) // already receive all data
            {
                break;
            }
            CodeStatus = I2Cx->STAT & I2C_STAT_CODE_BITMASK;
        }
        return SUCCESS;
error:
        return ERROR;
    }

    else if (Opt == I2C_TRANSFER_INTERRUPT)
    {
        // Setup tx_rx data, callback and interrupt handler
        i2cdat[i2cId].txrx_setup = (uint32_t) TransferCfg;

        // Set direction phase, write first
        i2cdat[i2cId].dir = 0;

        /* First Start condition -------------------------------------------------------------- */
        // Reset STA, STO, SI
        I2C_Start(I2Cx, I2C_TRANSFER_INTERRUPT);

        I2C_IntCmd(i2cId, TRUE);

        return (SUCCESS);
    }

    return ERROR;
}

/*********************************************************************//**
 * @brief       Receive and Transmit data in slave mode
 * @param[in]   I2Cx            I2C peripheral selected, should be
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   TransferCfg     Pointer to a I2C_S_SETUP_Type structure that
 *                              contains specified information about the
 *                              configuration for master transfer.
 * @param[in]   Opt             I2C_TRANSFER_OPT_Type type that selected for
 *                              interrupt or polling mode.
 * @return      SUCCESS or ERROR
 *
 * Note:
 * The mode of slave's operation depends on the command sent from master on
 * the I2C bus. If the master send a SLA+W command, this sub-routine will
 * use receive data length and receive data pointer. If the master send a SLA+R
 * command, this sub-routine will use transmit data length and transmit data
 * pointer.
 * If the master issue an repeat start command or a stop command, the slave will
 * enable an time out condition, during time out condition, if there's no activity
 * on I2C bus, the slave will exit, otherwise (i.e. the master send a SLA+R/W),
 * the slave then switch to relevant operation mode. The time out should be used
 * because the return status code can not show difference from stop and repeat
 * start command in slave operation.
 * In case of the expected data length from master is greater than data length
 * that slave can support:
 * - In case of reading operation (from master): slave will return I2C_I2DAT_IDLE_CHAR
 * value.
 * - In case of writing operation (from master): slave will ignore remain data from master.
 **********************************************************************/
Status I2C_SlaveTransferData(en_I2C_unitId i2cId, I2C_S_SETUP_Type *TransferCfg,
                                                                    I2C_TRANSFER_OPT_Type Opt)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);
    int32_t   Ret = I2C_OK;
    
    uint32_t CodeStatus;
    uint32_t timeout;
    int32_t time_en;
    
    // Reset I2C setup value to default state
    TransferCfg->tx_count = 0;
    TransferCfg->rx_count = 0;
    TransferCfg->status = 0;

    // Polling option
    if (Opt == I2C_TRANSFER_POLLING)
    {
        /* Set AA bit to ACK command on I2C bus */
        I2Cx->CONSET = I2C_I2CONSET_AA;
        
        /* Clear SI bit to be ready ... */
        I2Cx->CONCLR = (I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC|I2C_I2CONCLR_STOC);

        time_en = 0;
        timeout = 0;

        while (1)
        {
            /* Check SI flag ready */
            if (I2Cx->CONSET & I2C_I2CONSET_SI)
            {
                time_en = 0;

                CodeStatus = (I2Cx->STAT & I2C_STAT_CODE_BITMASK);

                Ret = I2C_SlaveHanleStates(i2cId, CodeStatus, TransferCfg);
                if(I2C_CheckError(Ret))
                {
                    goto s_error;
                }
                else if(Ret & I2C_STA_STO_RECV)
                {
                    if((TransferCfg->tx_count >= (TransferCfg->tx_length)) &&
                        (TransferCfg->rx_count >= (TransferCfg->rx_length)))
                    {
                        goto s_end_stage;
                    }
                    time_en = 1;
                    timeout = 0;
                }
                else if (Ret & I2C_SEND_END)
                {
                    goto s_end_stage;
                }
            }
            else if (time_en)
            {
                if (timeout++ > I2C_SLAVE_TIME_OUT)
                {
                    // it's really a stop condition, goto end stage
                    goto s_end_stage;
                }
            }
        }

s_end_stage:
        /* Clear AA bit to disable ACK on I2C bus */
        I2Cx->CONCLR = I2C_I2CONCLR_AAC;

        // Check if there's no error during operation
        // Update status
        TransferCfg->status = CodeStatus | I2C_SETUP_STATUS_DONE;
        return SUCCESS;

s_error:
        /* Clear AA bit to disable ACK on I2C bus */
        I2Cx->CONCLR = I2C_I2CONCLR_AAC;

        // Update status
        TransferCfg->status = CodeStatus;
        return ERROR;
    }

    else if (Opt == I2C_TRANSFER_INTERRUPT)
    {
        // Setup tx_rx data, callback and interrupt handler
        i2cdat[i2cId].txrx_setup = (uint32_t) TransferCfg;

        // Set direction phase, read first
        i2cdat[i2cId].dir = 1;

        // Enable AA
        I2Cx->CONSET = I2C_I2CONSET_AA;
        I2Cx->CONCLR = I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC;
        I2C_IntCmd(i2cId, TRUE);

        return (SUCCESS);
    }

    return ERROR;
}

/*********************************************************************//**
 * @brief       Set Own slave address in I2C peripheral corresponding to
 *              parameter specified in OwnSlaveAddrConfigStruct.
 * @param[in]   I2Cx    I2C peripheral selected, should be
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   OwnSlaveAddrConfigStruct    Pointer to a I2C_OWNSLAVEADDR_CFG_Type
 *              structure that contains the configuration information for the
*               specified I2C slave address.
 * @return      None
 **********************************************************************/
void I2C_SetOwnSlaveAddr(en_I2C_unitId i2cId, I2C_OWNSLAVEADDR_CFG_Type *OwnSlaveAddrConfigStruct)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);

    uint32_t tmp;

    tmp = (((uint32_t)(OwnSlaveAddrConfigStruct->SlaveAddr_7bit << 1)) \
            | ((OwnSlaveAddrConfigStruct->GeneralCallState == ENABLE) ? 0x01 : 0x00))& I2C_I2ADR_BITMASK;

    switch (OwnSlaveAddrConfigStruct->SlaveAddrChannel)
    {
        case 0:
            I2Cx->ADR0 = tmp;

            I2Cx->MASK0 = I2C_I2MASK_MASK((uint32_t) \
                            (OwnSlaveAddrConfigStruct->SlaveAddrMaskValue));
            break;

        case 1:
            I2Cx->ADR1 = tmp;

            I2Cx->MASK1 = I2C_I2MASK_MASK((uint32_t) \
                            (OwnSlaveAddrConfigStruct->SlaveAddrMaskValue));
            break;

        case 2:
            I2Cx->ADR2 = tmp;

            I2Cx->MASK2 = I2C_I2MASK_MASK((uint32_t) \
                            (OwnSlaveAddrConfigStruct->SlaveAddrMaskValue));
            break;

        case 3:
            I2Cx->ADR3 = tmp;

            I2Cx->MASK3 = I2C_I2MASK_MASK((uint32_t) \
                            (OwnSlaveAddrConfigStruct->SlaveAddrMaskValue));
            break;
    }
}


/*********************************************************************//**
 * @brief       Configures functionality in I2C monitor mode
 * @param[in]   I2Cx    I2C peripheral selected, should be
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   Monitor configuration. It can include:
 *              - I2C_I2MMCTRL_ENA_SCL: I2C module can 'stretch'
 *              the clock line (hold it low) until it has had time to
 *              respond to an I2C interrupt.
 *              - I2C_I2MMCTRL_MATCH_ALL: When the I2C is in monitor mode, 
 *              an interrupt will be generated on ANY address received.
 * @param[in]   NewState New State of this function, should be:
 *              - ENABLE: Enable this function.
 *              - DISABLE: Disable this function.
 * @return      None
 **********************************************************************/
void I2C_MonitorModeConfig(en_I2C_unitId i2cId, uint32_t MonitorCfgType, FunctionalState NewState)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);

    if (NewState == ENABLE)
    {
        I2Cx->MMCTRL |= MonitorCfgType;
    }
    else
    {
        I2Cx->MMCTRL &= (~MonitorCfgType) & I2C_I2MMCTRL_BITMASK;
    }
}


/*********************************************************************//**
 * @brief       Enable/Disable I2C monitor mode
 * @param[in]   I2Cx    I2C peripheral selected, should be
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @param[in]   NewState New State of this function, should be:
 *              - ENABLE: Enable monitor mode.
 *              - DISABLE: Disable monitor mode.
 * @return      None
 **********************************************************************/
void I2C_MonitorModeCmd(en_I2C_unitId i2cId, FunctionalState NewState)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);

    if (NewState == ENABLE)
    {
        I2Cx->MMCTRL |= I2C_I2MMCTRL_MM_ENA;
        I2Cx->CONSET = I2C_I2CONSET_AA;
        I2Cx->CONCLR = I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC;
    }
    else
    {
        I2Cx->MMCTRL &= (~I2C_I2MMCTRL_MM_ENA) & I2C_I2MMCTRL_BITMASK;
        I2Cx->CONCLR = I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC | I2C_I2CONCLR_AAC;
    }

    I2C_MonitorBufferIndex = 0;
}


/*********************************************************************//**
 * @brief       Get data from I2C data buffer in monitor mode.
 * @param[in]   I2Cx    I2C peripheral selected, should be
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @return      None
 * Note:    In monitor mode, the I2C module may lose the ability to stretch
 * the clock (stall the bus) if the ENA_SCL bit is not set. This means that
 * the processor will have a limited amount of time to read the contents of
 * the data received on the bus. If the processor reads the DAT shift
 * register, as it ordinarily would, it could have only one bit-time to
 * respond to the interrupt before the received data is overwritten by
 * new data.
 **********************************************************************/
uint8_t I2C_MonitorGetDatabuffer(en_I2C_unitId i2cId)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);

    return ((uint8_t)(I2Cx->DATA_BUFFER));
}

/*********************************************************************//**
 * @brief       Get data from I2C data buffer in monitor mode.
 * @param[in]   I2Cx    I2C peripheral selected, should be
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @return      None
 * Note:    In monitor mode, the I2C module may lose the ability to stretch
 * the clock (stall the bus) if the ENA_SCL bit is not set. This means that
 * the processor will have a limited amount of time to read the contents of
 * the data received on the bus. If the processor reads the DAT shift
 * register, as it ordinarily would, it could have only one bit-time to
 * respond to the interrupt before the received data is overwritten by
 * new data.
 **********************************************************************/
BOOL_8 I2C_MonitorHandler(en_I2C_unitId i2cId, uint8_t *buffer, uint32_t size)
{
    LPC_I2C_TypeDef* I2Cx = I2C_GetPointer(i2cId);

    BOOL_8 ret=FALSE;

    I2Cx->CONCLR = I2C_I2CONCLR_SIC;

    buffer[I2C_MonitorBufferIndex] = (uint8_t)(I2Cx->DATA_BUFFER);

    I2C_MonitorBufferIndex++;

    if(I2C_MonitorBufferIndex >= size)
    {
        ret = TRUE;
    }
    return ret;
}
/*********************************************************************//**
 * @brief       Get status of Master Transfer
 * @param[in]   I2Cx    I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @return      Master transfer status, could be:
 *              - TRUE  master transfer completed
 *              - FALSE master transfer have not completed yet
 **********************************************************************/
uint32_t I2C_MasterTransferComplete(en_I2C_unitId i2cId)
{
    uint32_t retval;

    retval = I2C_MasterComplete[i2cId];

    I2C_MasterComplete[i2cId] = FALSE;

    return retval;
}

/*********************************************************************//**
 * @brief       Get status of Slave Transfer
 * @param[in]   I2Cx    I2C peripheral selected, should be:
 *              - LPC_I2C0
 *              - LPC_I2C1
 *              - LPC_I2C2
 * @return      Complete status, could be: TRUE/FALSE
 **********************************************************************/
uint32_t I2C_SlaveTransferComplete(en_I2C_unitId i2cId)
{
    uint32_t retval;

    retval = I2C_SlaveComplete[i2cId];

    I2C_SlaveComplete[i2cId] = FALSE;

    return retval;
}

#endif /*_I2C*/

/**
 * @}
 */


/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
