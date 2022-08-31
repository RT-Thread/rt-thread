/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_i2c.h"

/* Configure I2C speed to ordinary speed. */
static bool I2C_CalcBandrate(I2C_Type * I2Cx, uint32_t clk, uint32_t bandrate)
{
    /*
     * SCLH = (xSHR + 12) * I2C_CLK + tSYNC1;
     * SCLL = (xSLR + 1) * I2C_CLK + tSYNC2;
     * tSYNC1 & tSYNC2 equal 0 ~ 1 clk.
     */
    if ( (clk / 24u) < bandrate ) /* the system clock cannot meet the baud rate requirement. */
    {
        return false;
    }
    else
    {
        uint32_t tmp = clk / bandrate;
        I2Cx->SSHR = tmp / 2u - 12u;  /* Configure high level count in normal speed. */
        I2Cx->SSLR = tmp / 2u - 1u;   /* Configure low level count in normal speed. */
        I2Cx->FSHR = tmp / 2u - 14u;  /* Configure high level count in fast speed. */
        I2Cx->FSLR = tmp / 2u - 3u;   /* Configure low level count in fast speed. */
        return true;
    }
}

/* Initialize I2C, Initialization failure return false, Initialization success return true. */
bool I2C_InitMaster(I2C_Type * I2Cx, I2C_Master_Init_Type * init)
{
    I2Cx->ENR &= ~I2C_ENR_ENABLE_MASK;  /* Disable I2C. */

    if ( !I2C_CalcBandrate(I2Cx, init->ClockFreqHz, init->BaudRate) )  /* The system clock cannot meet the baud rate requirement. */
    {
        return false;
    }

    I2Cx->CR = I2C_CR_SPEED(1u);

    /* Setup I2C. */
    I2Cx->CR &= ~I2C_CR_MASTER10_MASK;  /* Address format. */
    I2Cx->CR |= I2C_CR_RESTART_MASK     /* Generate restart signal. */
             | I2C_CR_DISSLAVE_MASK     /* Disable slave module. */
             | I2C_CR_REPEN_MASK        /* Enable sending restart condition. */
             | I2C_CR_EMPINT_MASK       /* Control tx_empty interrupt generation. */
             | I2C_CR_MASTER_MASK;      /* Enable master module. */

    I2Cx->IMR   = 0u;  /* Close all interrupts. */
    I2Cx->RXTLR = 0u;  /* Configure the sending receive value. */
    I2Cx->TXTLR = 0u;  /* Configure the sending threshold value. */
    return true;       /* Initialize I2C succeeded, return true. */
}

/* Enable I2C. */
void I2C_Enable(I2C_Type * I2Cx, bool enable)
{
    if (enable)
    {
        I2Cx->ENR |= I2C_ENR_ENABLE_MASK;
    }
    else
    {
        I2Cx->ENR &= ~I2C_ENR_ENABLE_MASK;
    }
}

/* Configuration the target device address. */
void I2C_SetTargetAddr(I2C_Type * I2Cx, uint8_t addr)
{
    I2Cx->TAR = I2C_TAR_ADDR(addr);
}

/* Get I2C target device address. */
uint16_t I2C_GetTargetAddr(I2C_Type * I2Cx)
{
    return (I2Cx->TAR & I2C_TAR_ADDR_MASK);
}

/* Put data to target device. */
void I2C_PutData(I2C_Type * I2Cx, uint8_t val)
{
    I2Cx->DR = I2C_DR_DAT(val);
}

/* Control read-write bit to prepare to read data. */
void I2C_PrepareToGetData(I2C_Type * I2Cx)
{
    I2Cx->DR = I2C_DR_CMD_MASK;
}

/* Get the data received by target device. */
uint8_t I2C_GetData(I2C_Type * I2Cx)
{
    return ( (uint8_t)I2Cx->DR );
}

/* Get the current status flags of the I2C module. */
uint32_t I2C_GetStatus(I2C_Type * I2Cx)
{
    return I2Cx->SR;
}

/* Prepare for the stop, when transfer finish. */
void I2C_Stop(I2C_Type * I2Cx)
{
    I2Cx->ENR |= I2C_ENR_ABORT_MASK;  /* Prepare for the stop. */
    I2Cx->TXABRT;  /* Read register to release tx fifo. */
}

/* Enable I2C interrupt. */
void I2C_EnableInterrupts(I2C_Type * I2Cx, uint32_t interrupts, bool enable)
{
    if (enable)
    {
        I2Cx->IMR |= interrupts;
    }
    else
    {
        I2Cx->IMR &= ~interrupts;
    }
}

/* Get the current enabled interrupts the I2C module. */
uint32_t I2C_GetEnabledInterrupts(I2C_Type * I2Cx)
{
    return I2Cx->IMR;
}

/* Get the I2C interrupt status flags of the I2C module. */
uint32_t I2C_GetInterruptStatus(I2C_Type * I2Cx)
{
    return (I2Cx->RAWISR & I2Cx->IMR);  /* To ensure that the acquired interrupt is an enabled interrupt. */
}

/* Clear I2C interrupt status. */
void I2C_ClearInterruptStatus(I2C_Type * I2Cx, uint32_t interrupts)
{
    if ( (I2C_INT_RX_UNDER & interrupts) != 0u )  /* Clear receive buffer under status. */
    {
        I2Cx->RXUNDER;
    }
    if ( (I2C_INT_TX_ABORT & interrupts) != 0u )  /* Clear I2C transmit abort status. */
    {
        I2Cx->TXABRT;
    }
    if ( (I2C_INT_ACTIVE & interrupts) != 0u )    /* Clear I2C interface activation status. */
    {
        I2Cx->ACTIV;
    }
    if ( (I2C_INT_STOP & interrupts) != 0u )      /* Clear I2C stop condition detection status. */
    {
        I2Cx->STOP;
    }
    if ( (I2C_INT_START & interrupts) != 0u )     /* Clear I2C start condition detection status. */
    {
        I2Cx->START;
    }
}

/* Performs polling tx. */
bool I2C_MasterWriteBlocking(I2C_Type * I2Cx, I2C_MasterXfer_Type * xfer)
{
    /* Put register address. */
    I2C_PutData(I2Cx, xfer->TxBuf[0u]);

    uint32_t waittime1 = xfer->WaitTimes;
    /* Wait to tx fifo empty. */
    while ( (0u == (I2C_GetStatus(I2Cx) & I2C_STATUS_TX_EMPTY) ) && (0u != waittime1) )
    {
        waittime1--;
    }
    if (0u == waittime1)  /* I2C write register address timeout. */
    {
        return false;
    }

    uint32_t waittime2 = xfer->WaitTimes;
    /* Write data to target device. */
    for (uint32_t i = 1u; i < xfer->TxLen; i++)
    {
        I2C_PutData(I2Cx, xfer->TxBuf[i]);

        while ( ( 0u == (I2C_GetStatus(I2Cx) & I2C_STATUS_TX_EMPTY) ) && (0u != waittime2) )  /* Wait to tx fifo empty. */
        {
            waittime2--;
        }
        if (0u == waittime2)  /* I2C write timeout. */
        {
            return false;
        }
    }

    I2C_Stop(I2Cx);  /* Prepare to stop send data. */

    uint32_t waittime3 = xfer->WaitTimes;
    /* Wait to I2C not active, which means stop is taking effect. */
    while ( (I2C_GetStatus(I2Cx) & I2C_STATUS_ACTIVE) && (0u != waittime3) )
    {
        waittime3--;
    }
    if (0u == waittime3)  /* The wait operation is timeout. */
    {
        return false;
    }

    /* Clear fifo and flags. */
    I2C1->ICR;
    I2C1->TXABRT;
    return true;
}

/* Performs polling rx. */
bool I2C_MasterReadBlocking(I2C_Type * I2Cx, I2C_MasterXfer_Type * xfer)
{
    I2C_PutData(I2Cx, xfer->TxBuf[0u]); /* Put device register address. */

    uint32_t waittime1 = xfer->WaitTimes;
    while ( ( 0u == (I2C_GetStatus(I2Cx) & I2C_STATUS_TX_EMPTY) ) && (0u != waittime1) )  /* Wait to tx fifo empty. */
    {
        waittime1--;
    }
    if (0u == waittime1)
    {
        return false;
    }

    /* read data from target device. */
    for (uint32_t i = 0u; i < xfer->RxLen; i++)
    {
        I2C_PrepareToGetData(I2Cx);  /* Swich read-write bit, prepare to get data. */

        while ( 0u == (I2C_GetStatus(I2Cx) & I2C_STATUS_RX_NOTEMPTY) )  /* Wait to rx fifo not empty. */
        {
            if ( 0u == (I2C_GetStatus(I2Cx) & I2C_STATUS_ACTIVE) )  /* Receive is active. */
            {
                return false;
            }
        }
        xfer->RxBuf[i] = I2C_GetData(I2Cx);
    }

    I2C_Stop(I2Cx);  /* Prepare to stop I2C. */

    uint32_t waittime2 = xfer->WaitTimes;
    while ( (I2C_GetStatus(I2Cx) & I2C_STATUS_ACTIVE) && (0u != waittime2) )  /* Wait I2C not active, which means stop being effective. */
    {
        waittime2--;
    }
    if (0u == waittime2)
    {
        return false;
    }

    /* Clear fifo and flags. */
    I2C1->ICR;
    I2C1->TXABRT;

    return true;
}

/* I2C master interrupt transfer of the I2C module. */
void I2C_MasterXfer(I2C_Type * I2Cx, I2C_MasterXfer_Type * xfer)
{
    I2C_PutData(I2Cx, (uint8_t)xfer->TxBuf[0u]);  /* Put target register address. */
    I2C_EnableInterrupts(I2Cx, I2C_INT_TX_EMPTY | I2C_INT_TX_ABORT | I2C_INT_STOP, true);   /* Enable tx required interrupt. */
    xfer->TxIdx = 1u;   /* One data has been sent. */
    xfer->RxIdx = 0u;
    xfer->TxLen--;
}

/* I2C Master handler. */
void I2C_MasterXferHandler(I2C_Type * I2Cx, I2C_MasterXfer_Type * xfer, uint32_t interrupts)
{
    if ( 0u != (interrupts & I2C_INT_TX_ABORT) )  /* Early termination of program. */
    {
        I2C_EnableInterrupts(I2Cx, I2C_INT_TX_EMPTY | I2C_INT_TX_ABORT | I2C_INT_STOP, false);  /* Clear the interrupt used for tx. */
        if (NULL != xfer->AbortCallback)
        {
            xfer->AbortCallback(xfer);  /* Use abort call back. */
        }
    }
    else if ( 0u != (interrupts & I2C_INT_TX_EMPTY) )  /* Tx fifo is empty, can send data. */
    {
        if (I2C_Direction_Rx == xfer->Direction)  /* The current operation is receive, the register address has been sent. */
        {
            I2C_EnableInterrupts(I2Cx, I2C_INT_TX_EMPTY | I2C_INT_TX_ABORT, false);  /* Clear tx interrupt. */
            I2C_EnableInterrupts(I2Cx, I2C_INT_RX_NOTEMPTY, true);  /* Enable receive required interrupt. */
            if (0u != xfer->RxLen) /* The data to be received is not 0. */
            {
                I2C_PrepareToGetData(I2Cx);  /* Prepare to get data. */
                xfer->RxLen--;
            }
            else
            {
                I2C_Stop(I2Cx);  /* No more transmition, prepare to stop. */
            }
        }
        else
        {
            if (0u == xfer->TxLen)  /* Tx finish. */
            {
                I2C_EnableInterrupts(I2Cx, I2C_INT_TX_EMPTY | I2C_INT_TX_ABORT, false);  /* Clear Tx interrupt. */
                I2C_Stop(I2Cx);  /* Prepare to stop. */
            }
            else
            {
                xfer->TxLen--;
                I2C_PutData(I2Cx, xfer->TxBuf[xfer->TxIdx++]);  /* Tx is not over, continue to put data. */
            }
        }
    }
    else if ( 0u != (interrupts & I2C_INT_RX_NOTEMPTY) )  /* Receive interrupt. */
    {
        if (0u == xfer->RxLen)  /* Receive finish. */
        {
            xfer->RxBuf[xfer->RxIdx++] = I2C_GetData(I2Cx); /* Get last data from I2C bus. */
            I2C_EnableInterrupts(I2Cx, I2C_INT_RX_NOTEMPTY, false);  /* Clear receive interrupt. */
            I2C_Stop(I2Cx);  /* Prepare to stop. */
        }
        else
        {
            xfer->RxLen--;  /* Current count length count -1. */
            xfer->RxBuf[xfer->RxIdx++] = I2C_GetData(I2Cx);  /* Receive is not over, continue to get data. */
            I2C_PrepareToGetData(I2Cx);  /* Prepare to get data. */
        }
    }
    else if ( 0u != (interrupts & I2C_INT_STOP) )  /* Xfer stop. */
    {
        I2C_EnableInterrupts(I2Cx, I2C_INT_STOP, false);  /* Clear stop interrupt. */
        if ( (0u != xfer->TxLen) || (0u != xfer->RxLen) ) /* The transmission was not completed but terminated. */
        {
            if (NULL != xfer->AbortCallback)
            {
                xfer->AbortCallback(xfer);  /* Early termination of program, abort callback. */
                I2C1->ICR;
                I2C1->TXABRT;  /* Clear FIFO. */
            }
        }
        else
        {
            if (NULL != xfer->DoneCallback)
            {
                xfer->DoneCallback(xfer);  /* Transmission finish and stop, xfer done callback. */
                I2C1->ICR;
                I2C1->TXABRT;  /* Clear FIFO. */
            }
        }
    }
}

/* EOF. */

