/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fpl011_options.c
 * Date: 2021-11-02 14:53:42
 * LastEditTime: 2022-02-18 09:06:45
 * Description:  This file is for uart option setting
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  huanghe 2021/11/2  first commit
 * 1.1  liushengming 2022/02/18  fix bug
 */


/***************************** Include Files *********************************/

#include "fpl011.h"
#include "fpl011_hw.h"
#include "ftypes.h"

/************************** Variable Definitions ****************************/
/************************** Constant Definitions *****************************/
/**************************** Type Definitions *******************************/
/*
 * The following data type is a map from an option to the offset in the
 * register to which it belongs as well as its bit mask in that register.
 */
typedef struct
{
    u32 option;
    u32 register_offset;
    u32 mask;
} Mapping;

static Mapping option_table[] =
{
    {FPL011_OPTION_UARTEN, FPL011CR_OFFSET, FPL011CR_UARTEN},
    {FPL011_OPTION_RXEN, FPL011CR_OFFSET, FPL011CR_RXE},
    {FPL011_OPTION_TXEN, FPL011CR_OFFSET, FPL011CR_TXE},
    {FPL011_OPTION_FIFOEN, FPL011LCR_H_OFFSET, FPL011LCR_H_FEN},
    {FPL011_OPTION_RTS, FPL011CR_OFFSET, FPL011CR_RTS},
    {FPL011_OPTION_DTR, FPL011CR_OFFSET, FPL011CR_DTR},
    {FPL011_OPTION_RTSEN, FPL011CR_OFFSET, FPL011CR_RTSEN},
    {FPL011_OPTION_CTSEN, FPL011CR_OFFSET, FPL011CR_CTSEN},
    {FPL011_OPTION_TXDMAEN, FPL011DMACR_OFFSET, FPL011DMACR_TXDMAE},
    {FPL011_OPTION_RXDMAEN, FPL011DMACR_OFFSET, FPL011DMACR_RXDMAE}
};

/***************** Macros (Inline Functions) Definitions *********************/

#define FUART_NUM_OPITIONS (sizeof(option_table) / sizeof(Mapping))
/************************** Function Prototypes ******************************/
/*****************************************************************************/
/**
 * @name: FPl011SetOptions
 * @msg:  Sets the options for the specified driver instance. The options are implemented as bit masks such that multiple options may be enabled or disabled simultaneously.
 * @param uart_p is a pointer to the uart instance.
 * @param options contains the options to be set which are bit masks
 *      contained in the file FPl011_uart.h and named FUART_OPTION_*.
 */
void FPl011SetOptions(FPl011 *uart_p, u32 options)
{
    u32 index;
    u32 reg_value;
    FASSERT(uart_p != NULL);
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);

    for (index = 0; index < FUART_NUM_OPITIONS; index++)
    {
        reg_value = FUART_READREG32(uart_p->config.base_address, option_table[index].register_offset);

        if ((options & option_table[index].option) != (u32)(0))
        {
            reg_value |= option_table[index].mask;
        }
        else
        {
            reg_value &= ~option_table[index].mask;
        }

        FUART_WRITEREG32(uart_p->config.base_address, option_table[index].register_offset, reg_value);
    }
}

/**
 * @name: FPl011SetSpecificOptions
 * @msg:  Sets the options for the specified driver instance.
 * @param {FPl011} *uart_p is a pointer to the uart instance.
 * @param {u32} options contains the options to be set which are bit masks
 *      contained in the file FPl011_uart.h and named FUART_OPTION_*.
 */
void FPl011SetSpecificOptions(FPl011 *uart_p, u32 options)
{
    u32 index;
    u32 reg_value;
    FASSERT(uart_p != NULL);

    for (index = 0; index < FUART_NUM_OPITIONS; index++)
    {
        if ((options & option_table[index].option) == (u32)(0))
        {
            continue;
        }
        reg_value = FUART_READREG32(uart_p->config.base_address, option_table[index].register_offset);

        /* set specific options */
        reg_value |= option_table[index].mask;
        FUART_WRITEREG32(uart_p->config.base_address, option_table[index].register_offset, reg_value);
    }
}

/**
 * @name: FPl011ClearSpecificOptions
 * @msg:  Clear the options for the specified driver instance.
 * @param uart_p is a pointer to the uart instance.
 * @param options contains the options to be set which are bit masks
 *      contained in the file FPl011_uart.h and named FUART_OPTION_*.
 */
void FPl011ClearSpecificOptions(FPl011 *uart_p, u32 options)
{
    u32 index;
    u32 reg_value;
    FASSERT(uart_p != NULL);

    for (index = 0; index < FUART_NUM_OPITIONS; index++)
    {
        if ((options & option_table[index].option) == (u32)(0))
        {
            continue;
        }
        reg_value = FUART_READREG32(uart_p->config.base_address, option_table[index].register_offset);

        /* remove specific options */
        reg_value &= ~option_table[index].mask;
        FUART_WRITEREG32(uart_p->config.base_address, option_table[index].register_offset, reg_value);
    }
}



/**
 * @name: FPl011SetDataFormat
 * @msg:  Sets the data format for the specified UART.
 * @param uart_p    is a pointer to the uart instance.
 * @param format_p  is a pointer to a format structure that will
 *      contain the data format after this call completes.
 * @return
 *          FT_SUCCESS if everything configured as expected
 *          FPL011_ERROR_PARAM if one of the parameters was not valid.
 */
FError FPl011SetDataFormat(FPl011 *uart_p, FPl011Format *format_p)
{
    FError ret ;
    u32 line_ctrl_reg ;
    FPl011Config *config_p;
    FASSERT(uart_p != NULL);
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(format_p != NULL) ;

    config_p = &uart_p->config;

    if ((format_p->data_bits > ((u32)(FPL011_FORMAT_WORDLENGTH_8BIT))) ||
        (format_p->parity > ((u32)(FPL011_FORMAT_PARITY_MASK))) ||
        (format_p->stopbits > ((u32)(FPL011_FORMAT_PARITY_MASK)))
       )
    {
        return FPL011_ERROR_PARAM ;
    }
    else
    {
        /*
         * Try to set the baud rate and if it's not successful then
         * don't continue altering the data format, this is done
         * first to avoid the format from being altered when an
         * error occurs
         */
        ret = FPl011SetBaudRate(uart_p, format_p->baudrate) ;
        if (ret != FT_SUCCESS)
        {

        }
        else
        {
            line_ctrl_reg = FUART_READREG32(config_p->base_address, FPL011LCR_H_OFFSET);

            /*
            * Set the length of data (8,7,6) by first clearing
            * out the bits that control it in the register,
            * then set the length in the register
            */
            line_ctrl_reg &= ~(u32)FPL011LCR_H_WLEN ;
            line_ctrl_reg |= (format_p->data_bits <<
                              FPL011LCR_H_WLEN_SHIFT);

            /*
            * Set the number of stop bits in the mode register by
            * first clearing out the bits that control it in the
            * register, then set the number of stop bits in the
            * register.
            */
            line_ctrl_reg &= ~FPL011LCR_H_STP_MASK;
            line_ctrl_reg |= (format_p->stopbits <<
                              FPL011LCR_H_STP_SHIFT);

            /*
            * Set the parity by first clearing out the bits that
            * control it in the register, then set the bits in
            * the register, the default is no parity after
            * clearing the register bits
            */
            line_ctrl_reg &= ~FPL011LCR_H_PARITY_MASK;
            line_ctrl_reg |= ((format_p->parity &
                               FPL011_FORMAT_EN_PARITY) <<
                              FPL011LCR_H_PARITY_SHIFT);

            /* Even/Odd parity set */
            line_ctrl_reg |= ((format_p->parity &
                               FPL011_FORMAT_EVEN_PARITY) <<
                              FPL011_FORMAT_EVEN_PARITY_SHIFT);

            /* Stick parity enable/disable */
            line_ctrl_reg |= ((format_p->parity &
                               FPL011_FORMAT_EN_STICK_PARITY) <<
                              FPL011_FORMAT_EN_STICK_PARITY_SHIFT);

            /* Update the Line control register */
            FUART_WRITEREG32(config_p->base_address, FPL011LCR_H_OFFSET, line_ctrl_reg) ;

            return FT_SUCCESS ;
        }
    }

    return ret ;
}

/**
 * @name: FPl011GetDataFormat
 * @msg:  Gets the data format for the specified UART.
 * @param uart_p    is a pointer to the uart instance.
 * @param format_p  is a pointer to a format structure that will
 *      contain the data format after this call completes.
 */
void FPl011GetDataFormat(FPl011 *uart_p, FPl011Format *format_p)
{
    u32 line_ctrl_reg ;
    FPl011Config *config_p;
    /* Assert validates the input arguments */
    FASSERT(uart_p != NULL);
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(format_p != NULL) ;

    config_p = &uart_p->config;
    /*
     * Get the baud rate from the instance, this is not retrieved from
     * the hardware because it is only kept as a divisor such that it
     * is more difficult to get back to the baud rate
     */
    format_p->baudrate = uart_p->config.baudrate ;

    line_ctrl_reg = FUART_READREG32(config_p->base_address, FPL011LCR_H_OFFSET);

    /* Get the length of data (8,7,6,5) */
    format_p->data_bits = ((line_ctrl_reg & FPL011LCR_H_WLEN) >> FPL011LCR_H_WLEN_SHIFT) ;

    /* Get the number of stop bits */
    format_p->stopbits = (u8)((line_ctrl_reg & FPL011LCR_H_STP_MASK) >> FPL011LCR_H_STP_SHIFT) ;

    /* Determine what parity is */
    format_p->parity = (u32)((line_ctrl_reg & (u32)FPL011LCR_H_PARITY_MASK) >> FPL011LCR_H_PARITY_SHIFT) ;
}



/**
 * @name: FPl011SetTxFifoThreadHold
 * @msg: This functions sets the Tx FIFO trigger level to the 'TriggerLevel'
 * argument.
 * @param uart_p is a pointer to the uart instance.
 * @param  trigger_level contains the trigger level to set. This is a value
 *              from 0-32  (FPL011IFLS_TXIFLSEL_1_8 - FPL011IFLS_TXIFLSEL_7_8)
 */
void FPl011SetTxFifoThreadHold(FPl011 *uart_p, u8 trigger_level)
{
    u32 fifo_trig_reg;
    FPl011Config *config_p;
    FASSERT(uart_p != NULL);
    FASSERT(trigger_level <= (u8)FPL011IFLS_TXIFLSEL_MASK) ;
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);
    config_p = &uart_p->config;

    trigger_level = trigger_level & (u8)FPL011IFLS_TXIFLSEL_MASK;

    fifo_trig_reg = FUART_READREG32(config_p->base_address,
                                    FPL011IFLS_OFFSET);

    fifo_trig_reg &= ~(FPL011IFLS_TXIFLSEL_MASK);

    fifo_trig_reg |= (u32)trigger_level;

    /*
     * Write the new value for the FIFO control register to it such that
     * the threshold is changed
     */
    FUART_WRITEREG32(config_p->base_address,
                     FPL011IFLS_OFFSET, fifo_trig_reg);
}



/**
 * @name: FPl011SetRxFifoThreadhold
 * @msg: This functions sets the Rx FIFO trigger level to the 'TriggerLevel'
 * argument.
 * @param uart_p is a pointer to the uart instance.
 * @param trigger_level contains the trigger level to set. This is a value
 *              from 0-32  (FPL011IFLS_RXIFLSEL_1_8 - FPL011IFLS_RXIFLSEL_7_8)
 */
void FPl011SetRxFifoThreadhold(FPl011 *uart_p, u8 trigger_level)
{
    u32 fifo_trig_reg;
    FPl011Config *config_p;
    FASSERT(uart_p != NULL);
    FASSERT(trigger_level <= (u8)FPL011IFLS_RXIFLSEL_MASK) ;
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);
    config_p = &uart_p->config;

    trigger_level = trigger_level & (u8)FPL011IFLS_RXIFLSEL_MASK;

    fifo_trig_reg = FUART_READREG32(config_p->base_address,
                                    FPL011IFLS_OFFSET);

    fifo_trig_reg &= ~FPL011IFLS_RXIFLSEL_MASK;

    fifo_trig_reg |= (u32)trigger_level ;

    /*
     * Write the new value for the FIFO control register to it such that
     * the threshold is changed
     */
    FUART_WRITEREG32(config_p->base_address,
                     FPL011IFLS_OFFSET, fifo_trig_reg);
}

/**
 * @name: FPl011SetBaudRate
 * @msg: Sets the baud rate for the device.
 * @param  uart_p is a pointer to the FPl011 instance
 * @param  BaudRate to be set
 * @return
 *          FT_SUCCESS if everything configured as expected
 *          FPL011_ERROR_PARAM if the requested rate is not available
 *        because there was too much error
 */
FError FPl011SetBaudRate(FPl011 *uart_p, u32 baudrate)
{
    u32 temp;
    u32 divider;
    u32 remainder;
    u32 fraction;

    FASSERT(NULL != uart_p);
    if ((baudrate * 2) > uart_p->config.ref_clock_hz)
    {
        return FPL011_ERROR_PARAM;
    }

    /* calculate baud rate divisor */
    temp = 16 * baudrate;
    divider = uart_p->config.ref_clock_hz / temp;
    remainder = uart_p->config.ref_clock_hz % temp;
    temp = (128 * remainder) / temp;
    fraction = temp / 2;

    if (0 != (temp & 1))
    {
        fraction++;
    }

    FPl011ClearSpecificOptions(uart_p, FPL011_OPTION_RXEN | FPL011_OPTION_TXEN);
    /* set baud register */
    FUART_WRITEREG32(uart_p->config.base_address, FPL011IBRD_OFFSET, divider);
    FUART_WRITEREG32(uart_p->config.base_address, FPL011FBRD_OFFSET, fraction);
    FPl011SetSpecificOptions(uart_p, FPL011_OPTION_RXEN | FPL011_OPTION_TXEN);
    uart_p->config.baudrate = baudrate;
    return FT_SUCCESS;
}

/**
 * @name: FPl011ProgramCtlReg
 * @msg: This function reprograms the control register according to the following
 * sequence mentioned in the TRM
 * @param uart_p is a pointer to the FPl011 instance
 * @param  ctrl_reg value to be written
 */
void FPl011ProgramCtlReg(FPl011 *uart_p, u32 ctrl_reg)
{
    u32 line_ctrl_reg;
    u32 temp_ctrl_reg;
    u32 isbusy;
    u32 addr = uart_p->config.base_address;
    FASSERT(uart_p);

    /*
    * Check is TX completed. If Uart is disabled in the middle, cannot
    * recover. So, keep this check before disable.
    */
    isbusy =  FUART_ISTRANSMITBUSY(addr);
    while (isbusy == (u32)TRUE)
    {
        isbusy = (u32)FUART_ISTRANSMITBUSY(addr);
    }

    /* Disable UART */
    temp_ctrl_reg = FUART_READREG32(addr, FPL011CR_OFFSET);
    temp_ctrl_reg &= (~FPL011CR_UARTEN);
    FUART_WRITEREG32(addr, FPL011CR_OFFSET, temp_ctrl_reg);

    /*
     * Flush the transmit FIFO by setting the FEN bit to 0 in the
     * Line Control Register
     */
    line_ctrl_reg = FUART_READREG32(addr, FPL011LCR_H_OFFSET);
    line_ctrl_reg &= ~FPL011LCR_H_FEN;
    FUART_WRITEREG32(addr, FPL011LCR_H_OFFSET, line_ctrl_reg);

    /* Setup the Control Register with the passed argument.*/
    FUART_WRITEREG32(addr, FPL011CR_OFFSET, ctrl_reg);

    /* By default, driver works in FIFO mode, so set FEN as it is
     * cleared above
     */
    line_ctrl_reg |= FPL011LCR_H_FEN;
    FUART_WRITEREG32(addr, FPL011LCR_H_OFFSET, line_ctrl_reg);

    /* Enable UART */
    temp_ctrl_reg = FUART_READREG32(addr, FPL011CR_OFFSET);
    temp_ctrl_reg |= FPL011CR_UARTEN;
    FUART_WRITEREG32(addr, FPL011CR_OFFSET, temp_ctrl_reg);
}

/**
 * @name: FPl011SetOperMode
 * @msg:  This function sets the operational mode of the UART. The UART can operate
 *        in one of four modes: Normal, Local Loopback.
 * @param uart_p is a pointer to the FPl011 instance.
 * @param  operation_mode is the mode of the UART.
 */
void FPl011SetOperMode(FPl011 *uart_p, u8 operation_mode)
{
    u32 ctrl_reg;
    FPl011Config *config_p;
    FASSERT(uart_p != NULL);
    FASSERT(operation_mode <= (u8)FPL011_OPER_MODE_LOCAL_LOOP) ;
    FASSERT(uart_p->is_ready == FT_COMPONENT_IS_READY);
    config_p = &uart_p->config;

    ctrl_reg = FUART_READREG32(config_p->base_address, FPL011CR_OFFSET) ;

    /* Set the correct value by masking the bits, then ORing the const. */
    ctrl_reg &= ~(u32)FPL011CR_LBE;

    switch (operation_mode)
    {
        case FPL011_OPER_MODE_NORMAL:
            ctrl_reg |= FPL011CR_MODE_NORMAL;
            break;
        case FPL011_OPER_MODE_LOCAL_LOOP:
            ctrl_reg |= FPL011CR_LBE;
            break;
        default:
            break;
    }

    /* Setup the Control Register with the passed argument.*/
    FPl011ProgramCtlReg(uart_p, ctrl_reg);
}
