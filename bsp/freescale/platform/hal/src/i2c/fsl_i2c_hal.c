/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_i2c_hal.h"
#include "fsl_misc_utilities.h" /* For ARRAY_SIZE*/

#if FSL_FEATURE_SOC_I2C_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief An entry in the I2C divider table.
 *
 * This struct pairs the value of the I2C_F.ICR bitfield with the resulting
 * clock divider value.
 */
typedef struct I2CDividerTableEntry {
    uint8_t icr;            /*!< F register ICR value.*/
    uint16_t sclDivider;    /*!< SCL clock divider.*/
} i2c_divider_table_entry_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*!
 * @brief I2C divider values.
 *
 * This table is taken from the I2C Divider and Hold values section of the
 * reference manual. In the original table there are, in some cases, multiple
 * entries with the same divider but different hold values. This table
 * includes only one entry for every divider, selecting the lowest hold value.
 */
const i2c_divider_table_entry_t kI2CDividerTable[] = {
        /* ICR  Divider*/
        { 0x00, 20 },
        { 0x01, 22 },
        { 0x02, 24 },
        { 0x03, 26 },
        { 0x04, 28 },
        { 0x05, 30 },
        { 0x09, 32 },
        { 0x06, 34 },
        { 0x0a, 36 },
        { 0x07, 40 },
        { 0x0c, 44 },
        { 0x10, 48 },
        { 0x11, 56 },
        { 0x12, 64 },
        { 0x0f, 68 },
        { 0x13, 72 },
        { 0x14, 80 },
        { 0x15, 88 },
        { 0x19, 96 },
        { 0x16, 104 },
        { 0x1a, 112 },
        { 0x17, 128 },
        { 0x1c, 144 },
        { 0x1d, 160 },
        { 0x1e, 192 },
        { 0x22, 224 },
        { 0x1f, 240 },
        { 0x23, 256 },
        { 0x24, 288 },
        { 0x25, 320 },
        { 0x26, 384 },
        { 0x2a, 448 },
        { 0x27, 480 },
        { 0x2b, 512 },
        { 0x2c, 576 },
        { 0x2d, 640 },
        { 0x2e, 768 },
        { 0x32, 896 },
        { 0x2f, 960 },
        { 0x33, 1024 },
        { 0x34, 1152 },
        { 0x35, 1280 },
        { 0x36, 1536 },
        { 0x3a, 1792 },
        { 0x37, 1920 },
        { 0x3b, 2048 },
        { 0x3c, 2304 },
        { 0x3d, 2560 },
        { 0x3e, 3072 },
        { 0x3f, 3840 }
    };

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_Init
 * Description   : Initialize I2C peripheral to reset state.
 *
 *END**************************************************************************/
void I2C_HAL_Init(I2C_Type * base)
{

    I2C_WR_A1(base, 0u);
    I2C_WR_F(base, 0u);
    I2C_WR_C1(base, 0u);
    I2C_WR_S(base, 0u);
    I2C_WR_C2(base, 0u);
    I2C_WR_FLT(base, 0u);
    I2C_WR_RA(base, 0u);

#if FSL_FEATURE_I2C_HAS_SMBUS
    I2C_WR_SMB(base, 0u);
    I2C_WR_A2(base, 0xc2u);
    I2C_WR_SLTH(base, 0u);
    I2C_WR_SLTL(base, 0u);
#endif /* FSL_FEATURE_I2C_HAS_SMBUS*/
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SetBaudRate
 * Description   : Sets the I2C bus frequency for master transactions.
 *
 *END**************************************************************************/
void I2C_HAL_SetBaudRate(I2C_Type * base,
                         uint32_t sourceClockInHz,
                         uint32_t kbps,
                         uint32_t * absoluteError_Hz)
{
    uint32_t mult, i, multiplier, computedRate, absError;
    uint32_t hz = kbps * 1000u;
    uint32_t bestError = 0xffffffffu;
    uint32_t bestMult = 0u;
    uint32_t bestIcr = 0u;

    /* Search for the settings with the lowest error.
     * mult is the MULT field of the I2C_F register, and ranges from 0-2. It selects the
     * multiplier factor for the divider. */
    for (mult = 0u; (mult <= 2u) && (bestError != 0); ++mult)
    {
        multiplier = 1u << mult;

        /* Scan table to find best match.*/
        for (i = 0u; i < ARRAY_SIZE(kI2CDividerTable); ++i)
        {
            computedRate = sourceClockInHz / (multiplier * kI2CDividerTable[i].sclDivider);
            absError = hz > computedRate ? hz - computedRate : computedRate - hz;

            if (absError < bestError)
            {
                bestMult = mult;
                bestIcr = kI2CDividerTable[i].icr;
                bestError = absError;

                /* If the error is 0, then we can stop searching
                 * because we won't find a better match.*/
                if (absError == 0)
                {
                    break;
                }
            }
        }
    }

    /* Set the resulting error.*/
    if (absoluteError_Hz)
    {
        *absoluteError_Hz = bestError;
    }

    /* Set frequency register based on best settings.*/
    I2C_WR_F(base, I2C_F_MULT(bestMult) | I2C_F_ICR(bestIcr));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SendStart
 * Description   : Send a START or Repeated START signal on the I2C bus.
 * This function is used to initiate a new master mode transfer by sending the
 * START signal. It is also used to send a Repeated START signal when a transfer
 * is already in progress.
 *
 *END**************************************************************************/
void I2C_HAL_SendStart(I2C_Type * base)
{
    /* Check if we're in a master mode transfer.*/
    if (I2C_BRD_C1_MST(base))
    {
#if FSL_FEATURE_I2C_HAS_ERRATA_6070
        /* Errata 6070: Repeat start cannot be generated if the I2Cx_F[MULT]
         * field is set to a non- zero value.
         * The workaround is to either always keep MULT set to 0, or to
         * temporarily set it to 0 while performing the repeated start and then
         * restore it.*/
        uint32_t savedMult = 0;
        if (I2C_BRD_F_MULT(base) != 0)
        {
            savedMult = I2C_BRD_F_MULT(base);
            I2C_BWR_F_MULT(base, 0U);
        }
#endif /* FSL_FEATURE_I2C_HAS_ERRATA_6070*/

        /* We are already in a transfer, so send a repeated start.*/
        I2C_BWR_C1_RSTA(base, 1U);

#if FSL_FEATURE_I2C_HAS_ERRATA_6070
        if (savedMult)
        {
            I2C_BWR_F_MULT(base, savedMult);
        }
#endif /* FSL_FEATURE_I2C_HAS_ERRATA_6070*/
    }
    else
    {
        /* Initiate a transfer by sending the start signal.*/
        I2C_SET_C1(base, I2C_C1_MST_MASK | I2C_C1_TX_MASK);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SendStop
 * Description   : Sends a STOP signal on the I2C bus.
 * This function changes the direction to receive.
 *
 *END**************************************************************************/
i2c_status_t I2C_HAL_SendStop(I2C_Type * base)
{
    assert(I2C_BRD_C1_MST(base) == 1);
    uint32_t i = 0;

    /* Start the STOP signal */
    I2C_CLR_C1(base, I2C_C1_MST_MASK | I2C_C1_TX_MASK);

    /* Wait for the STOP signal finish. */
    while(I2C_HAL_GetStatusFlag(base, kI2CBusBusy))
    {
        if (++i == 0x400U)
        {
            /* Something is wrong because the bus is still busy. */
            return kStatus_I2C_StopSignalFail;
        }
        else
        {
            __asm("nop");
        }
    }

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SetAddress7bit
 * Description   : Sets the primary 7-bit slave address.
 *
 *END**************************************************************************/
void I2C_HAL_SetAddress7bit(I2C_Type * base, uint8_t address)
{
    /* Set 7-bit slave address.*/
    I2C_WR_A1(base, address << 1U);

    /* Disable the address extension option, selecting 7-bit mode.*/
    I2C_BWR_C2_ADEXT(base, 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SetAddress10bit
 * Description   : Sets the primary slave address and enables 10-bit address mode.
 *
 *END**************************************************************************/
void I2C_HAL_SetAddress10bit(I2C_Type * base, uint16_t address)
{
    /* Set bottom 7 bits of slave address.*/
    uint8_t temp = address & 0x7FU;

    I2C_WR_A1(base, temp << 1U);

    /* Enable 10-bit address extension.*/
    I2C_BWR_C2_ADEXT(base, 1U);

    /* Set top 3 bits of slave address.*/
    I2C_BWR_C2_AD(base, (address & 0x0380U) >> 7U);
}
#if FSL_FEATURE_I2C_HAS_SMBUS
/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_ClearTimeoutStatus
 * Description   : Clear SMBus timeout status.
 *
 *END**************************************************************************/
void I2C_HAL_ClearTimeoutStatus(I2C_Type *base, smb_timeout_status_flag_t status)
{
    uint8_t val =  I2C_RD_SMB(base);
    I2C_WR_SMB(base, val|status);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SetSMBusAddressCmd
 * Description   : Enables/Disables SMBus device default address.
 *
 *END**************************************************************************/
void I2C_HAL_SetSMBusAddressCmd(I2C_Type *base, bool enable, uint8_t address)
{
    I2C_BWR_SMB_SIICAEN(base, enable);
    I2C_BWR_A2_SAD(base, address);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_ConfigSMBCLKLowTimeout
 * Description   : Config SMBCLK low timeout period.
 *
 *END**************************************************************************/
void I2C_HAL_ConfigSMBCLKLowTimeout(I2C_Type *base, uint16_t timeout)
{
    uint16_t highVal = timeout&0xFF00;
    I2C_WR_SLTH(base, highVal>>8);
    I2C_WR_SLTL(base,(timeout&0xFF));
}
#endif
/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_ReadByteBlocking
 * Description   : Returns the last byte of data read from the bus and initiate
 * another read. It will wait till the transfer is actually completed.
 *
 *END**************************************************************************/
uint8_t I2C_HAL_ReadByteBlocking(I2C_Type * base)
{
    /* Read byte from I2C data register. */
    uint8_t byte = I2C_RD_D(base);

    /* Wait till byte transfer complete. */
    while (!I2C_BRD_S_IICIF(base))
    {}

    /* Clear interrupt flag */
    I2C_BWR_S_IICIF(base, 0x1U);

    return byte;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_WriteByteBlocking
 * Description   : Writes one byte of data to the I2C bus and wait till that
 * byte is transfered successfully.
 *
 *END**************************************************************************/
bool I2C_HAL_WriteByteBlocking(I2C_Type * base, uint8_t byte)
{
#if FSL_FEATURE_I2C_HAS_DOUBLE_BUFFERING
    while (!I2C_BRD_S2_EMPTY(base))
    {}
#endif

    /* Write byte into I2C data register. */
    I2C_WR_D(base, byte);

    /* Wait till byte transfer complete. */
    while (!I2C_BRD_S_IICIF(base))
    {}

    /* Clear interrupt flag */
    I2C_BWR_S_IICIF(base, 0x1U);

    /* Return 0 if no acknowledge is detected. */
    return !I2C_BRD_S_RXAK(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_MasterReceiveDataPolling
 * Description   : Performs a polling receive transaction on the I2C bus.
 *
 *END**************************************************************************/
i2c_status_t I2C_HAL_MasterReceiveDataPolling(I2C_Type * base,
                                              uint16_t slaveAddr,
                                              const uint8_t * cmdBuff,
                                              uint32_t cmdSize,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize)
{
    int32_t i;
    uint8_t directionBit, address;

    /* Return if current I2C is already set as master. */
    if (I2C_BRD_C1_MST(base))
    {
        return kStatus_I2C_Busy;
    }

    /* Get r/w bit according to CMD buffer setting
     * read is 1, write is 0. */
    directionBit = (cmdBuff) ? 0x0U : 0x1U;

    address = (uint8_t)slaveAddr << 1U;

    /* Set direction to send */
    I2C_HAL_SetDirMode(base, kI2CSend);

    /* Generate START signal. */
    I2C_HAL_SendStart(base);

    /* Send slave address */
    if (!I2C_HAL_WriteByteBlocking(base, address | directionBit))
    {
        /* Send STOP if no ACK received */
        I2C_HAL_SendStop(base);
        return kStatus_I2C_ReceivedNak;
    }

    /* Send CMD buffer */
    if (cmdBuff != NULL)
    {
        while (cmdSize--)
        {
            if (!I2C_HAL_WriteByteBlocking(base, *cmdBuff--))
            {
                /* Send STOP if no ACK received */
                I2C_HAL_SendStop(base);
                return kStatus_I2C_ReceivedNak;
            }
        }

        /* Need to generate a repeat start before changing to receive. */
        I2C_HAL_SendStart(base);

        /* Send slave address again */
        if (!I2C_HAL_WriteByteBlocking(base, address | 1U))
        {
            /* Send STOP if no ACK received */
            I2C_HAL_SendStop(base);
            return kStatus_I2C_ReceivedNak;
        }
    }

    /* Change direction to receive. */
    I2C_HAL_SetDirMode(base, kI2CReceive);

    /* Send NAK if only one byte to read. */
    if (rxSize == 0x1U)
    {
        I2C_HAL_SendNak(base);
    }
    else
    {
        I2C_HAL_SendAck(base);
    }

    /* Dummy read to trigger receive of next byte. */
    I2C_HAL_ReadByteBlocking(base);

    /* Receive data */
    for(i=rxSize-1; i>=0; i--)
    {
        switch (i)
        {
            case 0x0U:
                /* Generate STOP signal. */
                I2C_HAL_SendStop(base);
                break;
            case 0x1U:
                /* For the byte before last, we need to set NAK */
                I2C_HAL_SendNak(base);
                break;
            default :
                I2C_HAL_SendAck(base);
                break;
        }

        /* Read recently received byte into buffer and update buffer index */
        if (i==0)
        {
            *rxBuff++ = I2C_HAL_ReadByte(base);
        }
        else
        {
            *rxBuff++ = I2C_HAL_ReadByteBlocking(base);
        }
    }

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_MasterSendDataPolling
 * Description   : Performs a polling send transaction on the I2C bus.
 *
 *END**************************************************************************/
i2c_status_t I2C_HAL_MasterSendDataPolling(I2C_Type * base,
                                           uint16_t slaveAddr,
                                           const uint8_t * cmdBuff,
                                           uint32_t cmdSize,
                                           const uint8_t * txBuff,
                                           uint32_t txSize)
{
    uint16_t slaveAddress;
    slaveAddress = (slaveAddr << 1U) & 0x00FFU;

    /* Return if current I2C is already set as master. */
    if (I2C_BRD_C1_MST(base))
    {
        return kStatus_I2C_Busy;
    }

    /* Set direction to send. */
    I2C_HAL_SetDirMode(base, kI2CSend);

    /* Generate START signal. */
    I2C_HAL_SendStart(base);

    /* Send slave address */
    if (!I2C_HAL_WriteByteBlocking(base, slaveAddress))
    {
        /* Send STOP if no ACK received */
        I2C_HAL_SendStop(base);
        return kStatus_I2C_ReceivedNak;
    }

    /* Send CMD buffer */
    if (cmdBuff != NULL)
    {
        while (cmdSize--)
        {
            if (!I2C_HAL_WriteByteBlocking(base, *cmdBuff--))
            {
                /* Send STOP if no ACK received */
                I2C_HAL_SendStop(base);
                return kStatus_I2C_ReceivedNak;
            }
        }
    }

    /* Send data buffer */
    while (txSize--)
    {
        if (!I2C_HAL_WriteByteBlocking(base, *txBuff++))
        {
            /* Send STOP if no ACK received */
            I2C_HAL_SendStop(base);
            return kStatus_I2C_ReceivedNak;
        }
    }

    /* Generate STOP signal. */
    I2C_HAL_SendStop(base);

    /* Set direction back to receive. */
    I2C_HAL_SetDirMode(base, kI2CReceive);

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SlaveSendDataPolling
 * Description   : Send out multiple bytes of data using polling method.
 *
 *END**************************************************************************/
i2c_status_t I2C_HAL_SlaveSendDataPolling(I2C_Type * base, const uint8_t* txBuff, uint32_t txSize)
{
#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    /* Wait until start detected */
   while(!I2C_HAL_GetStartFlag(base))
   {}
   I2C_HAL_ClearStartFlag(base);
#endif
    /* Wait until addressed as a slave */
    while(!I2C_HAL_GetStatusFlag(base, kI2CAddressAsSlave))
    {}

    /* Wait interrupt flag is set */
    while(!I2C_HAL_IsIntPending(base))
    {}
        /* Clear interrupt flag */
    I2C_HAL_ClearInt(base);

    /* Set direction mode */
    if (I2C_HAL_GetStatusFlag(base, kI2CSlaveTransmit))
    {
        /* Switch to TX mode*/
        I2C_HAL_SetDirMode(base, kI2CSend);
    }
    else
    {
        /* Switch to RX mode.*/
        I2C_HAL_SetDirMode(base, kI2CReceive);

        /* Read dummy character.*/
        I2C_HAL_ReadByte(base);
    }

    /* While loop to transmit data */
    while(txSize--)
    {
        /* Write byte to data register */
        I2C_HAL_WriteByte(base, *txBuff++);

        /* Wait tranfer byte complete */
        while(!I2C_HAL_IsIntPending(base))
        {}

        /* Clear interrupt flag */
        I2C_HAL_ClearInt(base);

        /* if NACK received */
        if ((I2C_HAL_GetStatusFlag(base, kI2CReceivedNak)) && (txSize != 0))
        {
            return kStatus_I2C_ReceivedNak;
        }
    }
    /* Switch to RX mode.*/
    I2C_HAL_SetDirMode(base, kI2CReceive);

    /* Read dummy character.*/
    I2C_HAL_ReadByte(base);

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_HAL_SlaveReceiveDataPolling
 * Description   : Receive multiple bytes of data using polling method.
 *
 *END**************************************************************************/
i2c_status_t I2C_HAL_SlaveReceiveDataPolling(I2C_Type * base, uint8_t *rxBuff, uint32_t rxSize)
{
#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    /* Wait until start detected */
   while(!I2C_HAL_GetStartFlag(base))
   {}
   I2C_HAL_ClearStartFlag(base);
#endif
    /* Wait until addressed as a slave */
    while(!I2C_HAL_GetStatusFlag(base, kI2CAddressAsSlave))
    {}

    /* Wait interrupt flag is set */
    while(!I2C_HAL_IsIntPending(base))
    {}
        /* Clear interrupt flag */
    I2C_HAL_ClearInt(base);

    /* Set direction mode */
    if (I2C_HAL_GetStatusFlag(base, kI2CSlaveTransmit))
    {
        /* Switch to TX mode*/
        I2C_HAL_SetDirMode(base, kI2CSend);
    }
    else
    {
        /* Switch to RX mode.*/
        I2C_HAL_SetDirMode(base, kI2CReceive);

        /* Read dummy character.*/
        I2C_HAL_ReadByte(base);
    }

    /* While loop to receive data */
    while(rxSize--)
    {
        /* Wait interrupt flag is set */
        while(!I2C_HAL_IsIntPending(base))
        {}

        /* Read byte from data register  */
        *rxBuff++ = I2C_HAL_ReadByte(base);

        /* Clear interrupt flag */
        I2C_HAL_ClearInt(base);
    }
    return kStatus_I2C_Success;
}

#endif /* FSL_FEATURE_SOC_I2C_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

