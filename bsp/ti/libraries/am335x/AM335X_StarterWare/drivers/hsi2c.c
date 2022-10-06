/**
 *  \file   hsi2c.c
 *
 *  \brief  HIGH SPEED I2C APIs.
 *
 *   This file contains the device abstraction layer APIs for High Speed I2c
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "hw_hsi2c.h"
#include "hw_types.h"
#include "hsi2c.h"


/*******************************************************************************
*                        API FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * \brief   This API will divide the system clock fed to I2C module between
 *          12 and 100Mhz.It will also configure the I2C bus clock frequency.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used.
 * \param   sysClk      It is the System clock fed to I2C module.
 * \param   internalClk It is the internal clock used by I2C module.Which is
 *                      obtained by scaling System clock fed to I2C module.
 * \param   outputClk   It is the required I2C bus speed or frequency.
 *
 * \return  None.
 **/ 
void I2CMasterInitExpClk(unsigned int baseAdd, unsigned int sysClk,
                         unsigned int internalClk, unsigned int outputClk)
{
    unsigned int prescalar;
    unsigned int divider;

    /* Calculate prescalar value */
    prescalar = (sysClk / internalClk) - 1;

    HWREG(baseAdd + I2C_PSC) = prescalar;

    divider = internalClk/outputClk;

    divider = divider / 2;

    HWREG(baseAdd + I2C_SCLL) = divider - 7;

    HWREG(baseAdd + I2C_SCLH) = divider - 5; 
}

/**
 * \brief   Enables the I2C module.This will bring the I2C module out of reset.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  None.
 *
 **/
void I2CMasterEnable(unsigned int baseAdd)
{
    /* Bring the I2C module out of reset */
    HWREG(baseAdd + I2C_CON) |= I2C_CON_I2C_EN;
}

/**
 * \brief   Disables the I2C Module.This will put the I2C module in reset.
 *          Only Tx and Rx are cleared,status bits are set their default
 *          values and all configuration registers are not reset,they keep
 *          their initial values.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  None.
 *
 **/
void I2CMasterDisable(unsigned int baseAdd)
{
    /* Put I2C module in reset */
    HWREG(baseAdd + I2C_CON) &= ~(I2C_CON_I2C_EN);
}

/**
 * \brief   This API determines whether bus is busy or not.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  returns 1 if bus is busy.
 *          returns 0 if bus is free.
 *
 **/
unsigned int I2CMasterBusBusy(unsigned int baseAdd)
{
    unsigned int status;

    if(HWREG(baseAdd + I2C_IRQSTATUS_RAW) & I2C_IRQSTATUS_RAW_BB)
    {
         status = 1;
    }
    else
    {
         status = 0;
    }

    return status; 
}

/**
 * \brief   This API determines whether Master is busy or not.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  returns 1 if bus is busy.
 *          returns 0 if bus is free.
 *
 **/
unsigned int I2CMasterBusy(unsigned int baseAdd)
{
    return (HWREG(baseAdd + I2C_CON) & I2C_CON_MST);
}

/**
 * \brief   This API determines whether error occured or not during
 *          I2C operation.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \returns error status.If error has occured it returns a non zero value.
 *          If no error has occured then return status will be zero.       
 *
 * Error may occur during I2C operation due to arbitration lost,access error,
 * receive overrun and transmit underrun.
 **/
unsigned int I2CMasterErr(unsigned int baseAdd)
{
    unsigned int err;

    err = HWREG(baseAdd + I2C_IRQSTATUS_RAW) & (  I2C_IRQSTATUS_RAW_AL   |
                                                  I2C_IRQSTATUS_RAW_AERR |
                                                  I2C_IRQSTATUS_RAW_NACK |
                                                  I2C_IRQSTATUS_RAW_ROVR);

    return err;
}

/**
 * \brief   This API configure I2C in different modes of operation.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 * \param   cmd       It is the value which configures I2C in different mode's
 *                    of operation.\n
 * 
 *          cmd can take follwing macros.\n
 *
 *          I2C_CFG_MST_TX             - Configure's I2C as Master-Transmitter.\n
 *          I2C_CFG_MST_RX             - Configure's I2C as Master-Receiver.\n
 *          I2C_CFG_STOP               - Configure's I2C to generate stop 
 *                                       condition when DCOUNT counts down to
 *                                       zero.\n
 *          I2C_CFG_N0RMAL_MODE        - Configure's I2C in normal mode.\n
 *          I2C_CFG_SRT_BYTE_MODE      - Configure's I2C in start byte mode.\n
 *          I2C_CFG_7BIT_SLAVE_ADDR    - Configure's I2C to address seven bit
 *                                       addressed slave.\n
 *          I2C_CFG_10BIT_SLAVE_ADDR   - Configure's I2C to address ten bit
 *                                       addressed slave.\n 
 *          I2C_CFG_10BIT_OWN_ADDR_0   - Enable 10bit addressing mode for own
 *                                       address 0.\n
 *          I2C_CFG_10BIT_OWN_ADDR_1   - Enable 10bit addressing mode for own
 *                                       address 1.\n
 *          I2C_CFG_10BIT_OWN_ADDR_2   - Enable 10bit addressing mode for own
 *                                       address 2.\n
 *          I2C_CFG_10BIT_OWN_ADDR_3   - Enable 10bit addressing mode for own
 *                                       address 3.\n
 *          I2C_CFG_7BIT_OWN_ADDR_0   -  Enable 7bit addressing mode for own
 *                                       address 0.\n
 *          I2C_CFG_7BIT_OWN_ADDR_1   -  Enable 7bit addressing mode for own
 *                                       address 1 .\n
 *          I2C_CFG_7BIT_OWN_ADDR_2   -  Enable 7bit addressing mode for own
 *                                       address 2.\n
 *          I2C_CFG_7BIT_OWN_ADDR_3   -  Enable 7bit addressing mode for own
 *                                       address 3.\n
 * \return None.
 *
 **/
void I2CMasterControl(unsigned int baseAdd, unsigned int cmd)
{
    HWREG(baseAdd + I2C_CON) = cmd | I2C_CON_I2C_EN;
}

/**
 * \brief   This API start's a I2C transaction on the bus. This API must
 *          be called after all the configuration for the i2c module is 
 *          done and after bringing I2C out of local reset
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
void I2CMasterStart(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_CON) |= I2C_CON_STT;
}

/**
 * \brief  This API stops a I2C transaction on the bus.
 *         This API must be used in case a deliberate STOP needs to be sent
 *         on the bus.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
void I2CMasterStop(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_CON) |= I2C_CON_STP;
}

/**
 * \brief  This API enables only specified I2C interrupts in master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag   It specifies the interrupts that are rquired to be enabled.\n
 *
 *         intFlag can take following values.\n
 *         
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers are ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n   
 *
 * \return None.
 **/
void I2CMasterIntEnableEx(unsigned int baseAdd, unsigned int intFlag)
{
    HWREG(baseAdd + I2C_IRQENABLE_SET) |= intFlag;
}


/**
 * \brief  This API disables only specified I2C interrupts in master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag   It specifies the interrupts that are rquired to be disabled\n
 *
 *         intFlag can take following values.\n
 *         
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers are ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n   
 *
 * \return None.
 **/
void I2CMasterIntDisableEx(unsigned int baseAdd, unsigned int intFlag)
{
    HWREG(baseAdd + I2C_IRQENABLE_CLR) = intFlag;
}

/**
 * \brief  This API returns the status of  interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns status of interrupts.
 **/
unsigned int I2CMasterIntStatus(unsigned int baseAdd)
{
    return ((HWREG(baseAdd + I2C_IRQSTATUS)));
}

/**
 * \brief  This API returns the status of specified interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag  It specifies the interrupts whose status needs to be
 *                  returned.\n
 *
 *         intFlag can take following macros.\n
 *         
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C register ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt.\n
 *         I2C_INT_BUS_BUSY             - Bus busy.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n
 *
 * \returns status of specified interrupts.
 **/
unsigned int I2CMasterIntStatusEx(unsigned int baseAdd, unsigned int intFlag)
{
    return ((HWREG(baseAdd + I2C_IRQSTATUS)) & (intFlag));
}

/**
 * \brief  This API returns the raw status of interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns Raw status of interrupts.
 **/
unsigned int I2CMasterIntRawStatus(unsigned int baseAdd)
{
    return ((HWREG(baseAdd + I2C_IRQSTATUS_RAW)));
}

/**
 * \brief  This API returns the raw status of specified interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag  It specifies the interrupts whose raw status needs to be
 *                  returned.\n
 *
 *         intFlag can take following macros.\n
 *         
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers are ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt.\n
 *         I2C_INT_BUS_BUSY             - Bus busy.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n
 *
 * \returns status of specified interrupts.
 **/
unsigned int I2CMasterIntRawStatusEx(unsigned int baseAdd, unsigned int intFlag)
{
    return ((HWREG(baseAdd + I2C_IRQSTATUS_RAW)) & (intFlag));
}

/**
 * \brief  This API Clears the status of specified interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag  It specifies the interrupts whose status needs to be cleared\n
 *
 *         intFlag can take following macros.\n
 *         
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n   
 *
 * \returns None
 **/
void I2CMasterIntClearEx(unsigned int baseAdd, unsigned int intFlag)
{
    HWREG(baseAdd + I2C_IRQSTATUS) = intFlag; 
}

/**
 * \brief  This API Clears the raw status of specified interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag  It specifies the interrupts whose status needs to be cleared\n
 *
 *         intFlag can take following macros.\n
 *         
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers are ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *
 * \returns None
 **/
void I2CMasterIntRawStatusClearEx(unsigned int baseAdd, unsigned int intFlag)
{
    HWREG(baseAdd + I2C_IRQSTATUS_RAW) = intFlag; 
}

/**
 * \brief   This API sets the address of the slave device with which I2C wants to
 *          communicate.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 * \param   slaveAddr  slave address.
 *
 * \return None.
 **/
void I2CMasterSlaveAddrSet(unsigned int baseAdd, unsigned int slaveAdd)
{
    /*Set the address of the slave with which the master will communicate.*/
    HWREG(baseAdd + I2C_SA) = slaveAdd;
}

/**
 * \brief   This API returns the address of the slave device with which I2C wants to
 *          communicate.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 * \param   slaveAddr slave address.
 *
 * \return  slave address.
 **/
unsigned int I2CMasterSlaveAddrGet(unsigned int baseAdd, unsigned int slaveAdd)
{
    /* Returns the address of the slave with which the master will communicate.*/
    return (HWREG(baseAdd + I2C_SA) & I2C_SA_SA);
}

/**
 * \brief   This API configure I2C data count register with a value. 
 *          The value in the I2C data count register indicate how many data
 *          words to transfer when the I2C is configured as a  master-transmitter
 *          and repeat mode is off.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 * \param   count    It is value which is set to I2C data count register.
 *
 * \return None.
 **/
void I2CSetDataCount(unsigned int baseAdd, unsigned int count)
{
    HWREG(baseAdd + I2C_CNT) = count;
}


/**
 * \brief   This API configure I2C data count register with a value. 
 *          The value in the I2C data count register indicate how many data
 *          words to transfer when the I2C is configured as a  master-transmitter
 *          and repeat mode is off.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \return  number of bytes transfered over the I2C bus.
 **/
unsigned int I2CDataCountGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + I2C_CNT));
}

/**
 * \brief   This API configure's the threshold value for FIFO buffer.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used.
 * \param   thresholdVal It is the threshold value for FIFO buffer.Which is 
 *                       used to specify the trigger level for data transfer or
 *                       data receive transfers.
 * \param   flag         It specifies FIFO buffer in TX mode or RX mode.\n
 *     
 *          flag can take following macros.\n
 *
 *          I2C_TX_MODE.\n
 *          I2C_RX_MODE.\n
 *
 * \return None.
 **/
void I2CFIFOThresholdConfig(unsigned int baseAdd, unsigned int threshlodVal,
                            unsigned int flag)
{
    if(I2C_TX_MODE == flag)
    {
         HWREG(baseAdd + I2C_BUF) &= ~I2C_BUF_TXTRSH;

         HWREG(baseAdd + I2C_BUF) |= threshlodVal;
    }
    else
    {
         HWREG(baseAdd + I2C_BUF) &= ~I2C_BUF_RXTRSH;

         HWREG(baseAdd + I2C_BUF) |= threshlodVal <<  I2C_BUF_RXTRSH_SHIFT;
    }
}

/**
 * \brief   This API Clear's Transmit and Receive FIFO.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used..
 * \param   flag        It specifies Transmit FIFO or Receive FIFO.\n
 *     
 *         flag can take following macros.\n
 *
 *         I2C_TX_MODE - .\n
 *         I2C_RX_MODE - .\n
 *
 * \return None.
 **/
void I2CFIFOClear(unsigned int baseAdd, unsigned int flag)
{
    if(I2C_TX_MODE == flag)
    {
         HWREG(baseAdd + I2C_BUF) |= (I2C_BUF_TXFIFO_CLR);
    }
    else
    {
         HWREG(baseAdd + I2C_BUF) |= (I2C_BUF_RXFIFO_CLR);
    }
}

/**
 * \brief   This API Enables generation of Transmit Event,when
 *          I2C_DATA register is empty.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
void I2CDMATxEventEnable(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_BUF) |= (I2C_BUF_XDMA_EN);

    HWREG(baseAdd + I2C_DMATXENABLE_SET) =  \
                                      (I2C_DMATXENABLE_SET_DMATX_ENABLE_SET);
}

/**
 * \brief   This API Enables generation of Receive DMA Event,when
 *          I2C_DATA register is full.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
void I2CDMARxEventEnable(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_BUF) |= (I2C_BUF_RDMA_EN);

    HWREG(baseAdd + I2C_DMARXENABLE_SET) =   
                                       (I2C_DMARXENABLE_SET_DMARX_ENABLE_SET);
}

/**
 * \brief   This API Disables Transmit event.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used..
 *
 * \return None.
 **/
void I2CDMATxEventDisable(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_BUF) &= ~(I2C_BUF_XDMA_EN);

    HWREG(baseAdd + I2C_DMATXENABLE_CLR) =   
                                    (I2C_DMATXENABLE_CLR_DMATX_ENABLE_CLEAR);
}

/**
 * \brief   This API Disables Receive event.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
void I2CDMARxEventDisable(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_BUF) &= ~(I2C_BUF_RDMA_EN);

    HWREG(baseAdd + I2C_DMARXENABLE_CLR) =  
                                     (I2C_DMARXENABLE_CLR_DMARX_ENABLE_CLEAR);
}

/**
 * \brief   This API returns the status of the internal buffers.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used..
 * \param   flag        It specifies required status field.\n
 *     
 *          flag can take following macros.\n
 *
 *          I2C_TX_BUFFER_STATUS - Indicates the number of data bytes still.
 *                                 left to be written in TXFIFO\n
 *          I2C_RX_BUFFER_STATUS - Indicates the number of bytes to be
 *                                 transfered from the fifo at the end
 *                                 of the I2C transfer.\n
 *          I2C_FIFO_DEPTH       - Internal FIFO buffer depth.\n
 *
 * \returns required status of internal buffer.
 **/
unsigned int I2CBufferStatus(unsigned int baseAdd, unsigned int flag)
{
    unsigned int status = 0;

    switch(flag)
    {
         case 0:
               status = HWREG(baseAdd + I2C_BUFSTAT) & I2C_BUFSTAT_TXSTAT;
               break;

         case 1:
               status = (HWREG(baseAdd + I2C_BUFSTAT) & I2C_BUFSTAT_RXSTAT) 
                        >> I2C_BUFSTAT_RXSTAT_SHIFT;
               break;

         case 2:
               status = (HWREG(baseAdd + I2C_BUFSTAT) & I2C_BUFSTAT_FIFODEPTH) 
                        >> I2C_BUFSTAT_FIFODEPTH_SHIFT;
               break;

         default:
               break;
    }

    return status;
}

/**
 * \brief   This API returns one of the module's four own addresses,which
 *          external master used when addressing the module.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns one of the module's four own address the external master used 
 *          when addressing the module.
 **/
unsigned int I2CActiveOwnAddressGet(unsigned int baseAdd)
{
    if((HWREG(baseAdd + I2C_ACTOA) & (I2C_ACTOA_OA0_ACT)))
    {
         return((HWREG(baseAdd + I2C_OA)));
    }
    else if((HWREG(baseAdd + I2C_ACTOA) & (I2C_ACTOA_OA1_ACT)))
    {
         return((HWREG(baseAdd + I2C_OAn(0))));
    }
    else if((HWREG(baseAdd + I2C_ACTOA) & (I2C_ACTOA_OA2_ACT)))
    {
         return((HWREG(baseAdd + I2C_OAn(1))));
    }
    else if((HWREG(baseAdd + I2C_ACTOA) & (I2C_ACTOA_OA3_ACT)))
    {
         return((HWREG(baseAdd + I2C_OAn(2))));
    }

    return 0;
}
    
/**
 * \brief   This API blocks or unblocks the clock for any of the module's four own
 *          addresses.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \param   ownAdd0  It is value which blocks or unblocks clock to i2c if 
 *                   an external master using own address 0.
 *
 * \param   ownAdd1  It is value which blocks or unblocks clock to i2c if 
 *                   an external master using own address 1.
 *
 * \param   ownAdd2  It is value which blocks or unblocks clock to i2c if 
 *                   an external master using own address 2.
 *
 * \param   ownAdd3  It is value which blocks or unblocks clock to i2c if 
 *                   an external master using own address 0.
 *
 *                   0 - Unblocks clock to i2c
 *                   1 - Blocks clock to i2c
 * \returns None.
 *          
 **/
void I2CClockBlockingControl(unsigned int baseAdd, unsigned int ownAdd0,
                             unsigned int ownAdd1, unsigned int ownAdd2,
                             unsigned int ownAdd3)
{
    HWREG(baseAdd + I2C_SBLOCK) &= ~(I2C_SBLOCK_OA0_EN);
    HWREG(baseAdd + I2C_SBLOCK) |=  ownAdd0 << I2C_SBLOCK_OA0_EN_SHIFT;

    HWREG(baseAdd + I2C_SBLOCK) &= ~(I2C_SBLOCK_OA1_EN);
    HWREG(baseAdd + I2C_SBLOCK) |=  ownAdd1 << I2C_SBLOCK_OA1_EN_SHIFT;

    HWREG(baseAdd + I2C_SBLOCK) &= ~(I2C_SBLOCK_OA2_EN);
    HWREG(baseAdd + I2C_SBLOCK) |=  ownAdd2 << I2C_SBLOCK_OA2_EN_SHIFT;

    HWREG(baseAdd + I2C_SBLOCK) &= ~(I2C_SBLOCK_OA3_EN);
    HWREG(baseAdd + I2C_SBLOCK) |=  ownAdd3 << I2C_SBLOCK_OA3_EN_SHIFT;
}

/**
 * \brief   This API configuers any one of the own address field out of four
 *          present in I2C controller.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 * \param   slaveAdd  Slave address to be set.
 * \param   flag      It specifies the any one of the own address field
 *                    out of four.\n
 *
 *          flag can take following values.\n
 *      
 *          I2C_OWN_ADDR_0.\n
 *          I2C_OWN_ADDR_1.\n
 *          I2C_OWN_ADDR_2.\n
 *          I2C_OWN_ADDR_3.\n
 *
 * \returns None.
 *          
 **/
void I2COwnAddressSet(unsigned int baseAdd, unsigned int slaveAdd,
                        unsigned int flag)
{
    switch(flag)
    {
         case 0 : 
               HWREG(baseAdd + I2C_OA) = slaveAdd;

         case 1 : 
               HWREG(baseAdd + I2C_OAn(0)) = slaveAdd;

         case 2 : 
               HWREG(baseAdd + I2C_OAn(1)) = slaveAdd;

         case 3 :
               HWREG(baseAdd + I2C_OAn(2)) = slaveAdd;
    }
}

/**
 * \brief   This API reset the entire I2C module.On reset,are set to power
 *          up reset values.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *          
 **/
void I2CSoftReset(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_SYSC) |= I2C_SYSC_SRST;
}

/**
 * \brief   This API enables autoidle mechanism
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *          
 **/
void I2CAutoIdleEnable(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_SYSC) |= I2C_SYSC_AUTOIDLE;
}

/**
 * \brief   This API disables autoidle mechanism
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *          
 **/
void I2CAutoIdleDisable(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_SYSC) &= ~I2C_SYSC_AUTOIDLE;
}

/**
 * \brief   This API enables wakeup mechanism
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *          
 **/
void I2CGlobalWakeUpEnable(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_SYSC) |= I2C_SYSC_ENAWAKEUP;
}

/**
 * \brief   This API disables wakeup mechanism
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *          
 **/
void I2CGlobalWakeUpDisable(unsigned int baseAdd)
{
    HWREG(baseAdd + I2C_SYSC) &= ~I2C_SYSC_ENAWAKEUP;
}
/**
 * \brief   This API selects one of the idel mode operation mechanism.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 * \param   flag      It is the value which determines the type of idel
 *                    mode operation.\n
 *
 *          flag can take following values.\n
 *
 *          I2C_FORCE_IDLE_MODE          - selects forced idel mode operation.\n
 *          I2C_NO_IDLE_MODE             - selects no idel mode operation.\n
 *          I2C_SMART_IDLE_MODE          - selects smart idel mode operation.\n
 *          I2C_SMART_IDLE_WAKEUP_MODE   - selects smart idel wakeup mode
 *                                         of operation.\n
 *
 * \returns None.
 *          
 **/
void I2CIdleModeSelect(unsigned int baseAdd, unsigned int flag)
{
    HWREG(baseAdd + I2C_SYSC) &= ~(I2C_SYSC_IDLEMODE);

    HWREG(baseAdd + I2C_SYSC) |= flag;
}

/**
 * \brief   This API disable external clock gating mechanism by selecting
 *          approriate type of clock activity.
 *
 * \param   flag      It is the value which determines the type of clock
 *                    activity.\n
 *
 *          flag can take following values.\n
 *
 *          I2C_CUT_OFF_BOTH_CLCK       - Both OCP and SYS Clk are cut off.\n
 *          I2C_CUT_OFF_SYS_CLK         - system clock is cut off;OCP clock
 *                                        is kept alive.\n
 *          I2C_CUT_OFF_OCP_CLK         - OCP clock is cut off;system clock is
 *                                        is kept alive\n
 *          I2C_KEEP_ALIVE_BOTH_CLK     - BOTH OCP and SYS Clk are kept alive.\n
 *
 * \returns None.
 *          
 **/
void I2CClockActivitySelect(unsigned int baseAdd, unsigned int flag)
{
    HWREG(baseAdd + I2C_SYSC) &= ~(I2C_SYSC_CLKACTIVITY);

    HWREG(baseAdd + I2C_SYSC) |= flag;
}

/**
 * \brief  This API Enables a specific IRQ/DMA request source to generate an
 *         asynchronous wakeup signal.A wakeup is signaled to the local
 *         host if the corresponding event is captured by the core of
 *         the I2C controller.
 *
 * \param  baseAdd    It is the Memory address of the I2C instance used.
 * \param  eventFlag   It specifies for which event wakeup sinal has to 
 *                     Enable.\n
 *
 *         intFlag can take following values.\n
 *         
 *         I2C_WAKE_UP_ARBITRATION_LOST    - Arbitration-lost wakeup signal.\n
 *         I2C_WAKE_UP_NO_ACK              - No-acknowledgment wakeup signal.\n
 *         I2C_WAKE_UP_ADRR_READY_ACCESS   - No-acknowledgment wakeup signal.\n
 *         I2C_WAKE_UP_GENERAL_CALL        - General call wakeup signal.\n
 *         I2C_WAKE_UP_START               - Start condition wakeup signal.\n
 *         I2C_WAKE_UP_STOP_CONDITION      - Stop condition wakeup signal.\n
 *         I2C_WAKE_UP_ADRR_SLAVE          - Address-as-slave wakeup signal.\n
 *         I2C_WAKE_UP_TX_UNDER_FLOW       - Transmit under flow wakeup siganl.\n
 *         I2C_WAKE_UP_RECV_OVER_RUN       - Receive overrun wakeup signal.\n
 *         I2C_WAKE_UP_RECV_DRAIN          - Receive drain wakeup signal.\n
 *         I2C_WAKE_UP_TRANSMIT_DRAIN      - Transmit drain wakeup siganl.\n   
 *         I2C_WAKE_UP_DATA_RECV_TX_RDY    - Receive-data-ready
 *                                                  wakeup signal.\n
 *
 * \param  flag        It specifies IRQ or DMA Transmit or DMA receive 
 *                     request source to generate asynchronous wake up
 *                     signal.\n
 *
 *         flag can take following values.\n
 *
 *         I2C_WAKE_UP_IRQ.\n
 *         I2C_WAKE_UP_DMA_RECV.\n
 *         I2C_WAKE_UP_DMA_TRANMIT.\n
 *
 * \returns None.
 **/
void I2CWakeUpEnable(unsigned int baseAdd, unsigned int eventFlag,
                     unsigned int flag)
{
    if(I2C_WAKE_UP_IRQ == flag)
    {
         HWREG(baseAdd + I2C_WE) |= eventFlag;
    }
    else if(I2C_WAKE_UP_DMA_RECV == flag)
    {
         HWREG(baseAdd + I2C_DMARXWAKE_EN) |= eventFlag;
    }
    else if(I2C_WAKE_UP_DMA_TRANSMIT == flag)
    {
         HWREG(baseAdd + I2C_DMATXWAKE_EN) |= eventFlag;
    }
     
}

/**
 * \brief  This API Disables a specific IRQ/DMA request source to generate an
 *         asynchronous wakeup signal.A wakeup is signaled to the local
 *         host if the corresponding event is captured by the core of
 *         the I2C controller.
 *
 * \param  baseAdd    It is the Memory address of the I2C instance used.
 * \param  eventflag   It specifies for which event wakeup sinal has to 
 *                     disabled.\n
 *
 *         intFlag can take following macros.\n
 *         
 *         I2C_WAKE_UP_ARBITRATION_LOST    - Arbitration-lost wakeup signal.\n
 *         I2C_WAKE_UP_NO_ACK              - No-acknowledgment wakeup signal.\n
 *         I2C_WAKE_UP_ADRR_RDY_ACCESS     - No-acknowledgment wakeup signal.\n
 *         I2C_WAKE_UP_GENERAL_CALL        - General call wakeup signal.\n
 *         I2C_WAKE_UP_START               - Start condition wakeup signal.\n
 *         I2C_WAKE_UP_STOP_CONDITION      - Stop condition wakeup signal.\n
 *         I2C_WAKE_UP_ADRR_SLAVE          - Address-as-slave wakeup signal.\n
 *         I2C_WAKE_UP_TX_UNDER_FLOW       - Transmit under flow wakeup siganl.\n
 *         I2C_WAKE_UP_RECV_OVER_RUN       - Receive overrun wakeup signal.\n
 *         I2C_WAKE_UP_RECV_DRAIN          - Receive drain wakeup signal.\n
 *         I2C_WAKE_UP_TRANSMIT_DRAIN      - Transmit drain wakeup siganl.\n   
 *         I2C_WAKE_UP_DATA_RECV_TX_RDY    - Receive-data-ready
 *                                              wakeup signal.\n
 *
 * \param  flag        It specifies IRQ or DMA Transmit or DMA receive 
 *                     request source to generate asynchronous wake up
 *                     signal.\n
 *
 *         flag can take following values.\n
 *
 *         I2C_WAKE_UP_IRQ.\n
 *         I2C_WAKE_UP_DMA_RECV.\n
 *         I2C_WAKE_UP_DMA_TRANMIT.\n
 *
 * \returns None.
 **/
void I2CWakeUpDisable(unsigned int baseAdd, unsigned int eventFlag,
                      unsigned int flag)
{
    if(I2C_WAKE_UP_IRQ == flag)
    {
         HWREG(baseAdd + I2C_WE) &= ~eventFlag;
    }
    else if(I2C_WAKE_UP_DMA_RECV == flag)
    {
         HWREG(baseAdd + I2C_DMARXWAKE_EN) &= ~eventFlag;
    }
    else if(I2C_WAKE_UP_DMA_TRANSMIT == flag)
    {
         HWREG(baseAdd + I2C_DMATXWAKE_EN) &= ~eventFlag;
    }
}

/**
 * \brief   This API indicates the state of the reset in case of
 *          hardware reset,global reset or paratial reset.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns returns "1" if reset is completed. 
 *          returns "0" if internal module reset is ongoing.
 *          
 **/
unsigned int I2CSystemStatusGet(unsigned int baseAdd)
{
    return(HWREG(baseAdd + I2C_SYSS) & I2C_SYSS_RDONE);
}

/**
 * \brief  This function Transmits a byte from the I2C in Master mode.
 * 
 * \param  baseAdd is the Memory address of the I2C instance used.
 * \param  data data to be transmitted from the I2C Master.
 * 
 * \return None.\n
 *
 **/
void I2CMasterDataPut(unsigned int baseAdd, unsigned char data)
{
     /*write data to be transmited to Data transmit register */
    HWREG(baseAdd + I2C_DATA) = data;
}

/**
 *  \brief  This Receives a byte that has been sent to the I2C in Master mode.
 * 
 *  \param  baseAdd is the Memory address of the I2C instance used.
 * 
 *  \return Returns the byte received from by the I2C in Master mode.
 *
 **/
unsigned char I2CMasterDataGet(unsigned int baseAdd)
{
    unsigned char rData;

    rData = (unsigned char)HWREG(baseAdd + I2C_DATA);
    return rData;
}

/**
 * \brief   This API can be used to save the register context of I2C
 *
 * \param   i2cBase       Base address of I2C instance
 * \param   contextPtr    Pointer to the structure where I2C register
 *                        context need to be saved
 *
 * \return  None
 *
 **/
void I2CContextSave(unsigned int i2cBase, I2CCONTEXT *contextPtr)
{
    contextPtr->prescalar	= HWREG(i2cBase + I2C_PSC);
    contextPtr->lowdivider 	= HWREG(i2cBase + I2C_SCLL);
    contextPtr->highdivider = HWREG(i2cBase + I2C_SCLH);
    contextPtr->ownaddr 	= HWREG(i2cBase + I2C_OA);
}


/**
 * \brief   This API can be used to restore the register context of I2C
 *
 * \param   i2cBase       Base address of I2C instance
 * \param   contextPtr    Pointer to the structure where I2C register
 *                        context need to be saved
 *
 * \return  None
 *
 **/
void I2CContextRestore(unsigned int i2cBase, I2CCONTEXT *contextPtr)
{
	HWREG(i2cBase + I2C_CON) &= ~(I2C_CON_I2C_EN);	// Disable
	HWREG(i2cBase + I2C_SYSC) |= I2C_SYSC_SRST;		// reset
	HWREG(i2cBase + I2C_SYSC) &= ~I2C_SYSC_AUTOIDLE;// Autoidle disable

    HWREG(i2cBase + I2C_PSC)	=	contextPtr->prescalar;
    HWREG(i2cBase + I2C_SCLL)	=	contextPtr->lowdivider;
    HWREG(i2cBase + I2C_SCLH)	=	contextPtr->highdivider;
    HWREG(i2cBase + I2C_OA)		=	contextPtr->ownaddr;
	
	HWREG(i2cBase + I2C_CON) |= I2C_CON_I2C_EN; 	// Enable 
	while((!HWREG(i2cBase + I2C_SYSS) & I2C_SYSS_RDONE)); 	// reset complete...?
}

