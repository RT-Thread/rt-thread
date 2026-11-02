/***********************************************************************************************************************
 * File Name    : ospi_b_commands.c
 * Description  : Contains function definition.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

#include "ospi_b_commands.h"
#include "ospi_b_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup ospi_b_commands.c
 * @{
 **********************************************************************************************************************/

spi_flash_direct_transfer_t g_ospi_b_direct_transfer [OSPI_B_TRANSFER_MAX] =
{
 /* Transfer structure for SPI mode */
    [OSPI_B_TRANSFER_WRITE_ENABLE_SPI] =
    {
    .command        = OSPI_B_COMMAND_WRITE_ENABLE_SPI,
    .address        = OSPI_B_ADDRESS_DUMMY,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_SPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_ZERO,
    .data_length    = OSPI_B_DATA_LENGTH_ZERO,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_WRITE_SPI
    },
    [OSPI_B_TRANSFER_WRITE_CFR2V_SPI] =
    {
    .command        = OSPI_B_COMMAND_WRITE_REGISTER_SPI,
    .address        = OSPI_B_ADDRESS_CFR2V_REGISTER,
    .data           = OSPI_B_DATA_CFR2V_REGISTER,
    .command_length = OSPI_B_COMMAND_LENGTH_SPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_ONE,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_WRITE_SPI
    },
    [OSPI_B_TRANSFER_WRITE_CFR3V_SPI] =
    {
    .command        = OSPI_B_COMMAND_WRITE_REGISTER_SPI,
    .address        = OSPI_B_ADDRESS_CFR3V_REGISTER,
    .data           = OSPI_B_DATA_CFR3V_REGISTER,
    .command_length = OSPI_B_COMMAND_LENGTH_SPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_ONE,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_WRITE_SPI
    },
    [OSPI_B_TRANSFER_WRITE_CFR5V_SPI] =
    {
    .command        = OSPI_B_COMMAND_WRITE_REGISTER_SPI,
    .address        = OSPI_B_ADDRESS_CFR5V_REGISTER,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_SPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_ONE,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_WRITE_SPI
    },
    [OSPI_B_TRANSFER_READ_STATUS_SPI] =
    {
    .command        = OSPI_B_COMMAND_READ_STATUS_SPI,
    .address        = OSPI_B_ADDRESS_DUMMY,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_SPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_ZERO,
    .data_length    = OSPI_B_DATA_LENGTH_ONE,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_READ_STATUS_SPI
    },
    [OSPI_B_TRANSFER_READ_CFR2V_SPI] =
    {
    .command        = OSPI_B_COMMAND_READ_REGISTER_SPI,
    .address        = OSPI_B_ADDRESS_CFR2V_REGISTER,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_SPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_ONE,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_READ_REGISTER_SPI
    },
    [OSPI_B_TRANSFER_READ_CFR3V_SPI] =
    {
    .command        = OSPI_B_COMMAND_READ_REGISTER_SPI,
    .address        = OSPI_B_ADDRESS_CFR3V_REGISTER,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_SPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_ONE,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_READ_REGISTER_SPI
    },
    [OSPI_B_TRANSFER_READ_CFR5V_SPI] =
    {
    .command        = OSPI_B_COMMAND_READ_REGISTER_SPI,
    .address        = OSPI_B_ADDRESS_CFR5V_REGISTER,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_SPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_ONE,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_READ_REGISTER_SPI
    },
    [OSPI_B_TRANSFER_READ_DEVICE_ID_SPI] =
    {
    .command        = OSPI_B_COMMAND_READ_DEVICE_ID_SPI,
    .address        = OSPI_B_ADDRESS_DUMMY,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_SPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_ZERO,
    .data_length    = OSPI_B_DATA_LENGTH_FOUR,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_READ_STATUS_SPI
    },

    /* Transfer structure for OPI mode */
    [OSPI_B_TRANSFER_WRITE_ENABLE_OPI] =
    {
    .command        = OSPI_B_COMMAND_WRITE_ENABLE_OPI,
    .address        = OSPI_B_ADDRESS_DUMMY,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_OPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_ZERO,
    .data_length    = OSPI_B_DATA_LENGTH_ZERO,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_WRITE_OPI
    },
    [OSPI_B_TRANSFER_WRITE_CFR2V_OPI] =
    {
    .command        = OSPI_B_COMMAND_WRITE_REGISTER_OPI,
    .address        = OSPI_B_ADDRESS_CFR2V_REGISTER,
    .data           = OSPI_B_DATA_CFR2V_REGISTER,
    .command_length = OSPI_B_COMMAND_LENGTH_OPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_TWO,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_WRITE_OPI
    },
    [OSPI_B_TRANSFER_WRITE_CFR3V_OPI] =
    {
    .command        = OSPI_B_COMMAND_WRITE_REGISTER_OPI,
    .address        = OSPI_B_ADDRESS_CFR3V_REGISTER,
    .data           = OSPI_B_DATA_CFR3V_REGISTER,
    .command_length = OSPI_B_COMMAND_LENGTH_OPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_TWO,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_WRITE_OPI
    },
    [OSPI_B_TRANSFER_WRITE_CFR5V_OPI] =
    {
    .command        = OSPI_B_COMMAND_WRITE_REGISTER_OPI,
    .address        = OSPI_B_ADDRESS_CFR5V_REGISTER,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_OPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_TWO,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_WRITE_OPI
    },
    [OSPI_B_TRANSFER_READ_STATUS_OPI] =
    {
    .command        = OSPI_B_COMMAND_READ_STATUS_OPI,
    .address        = OSPI_B_ADDRESS_DUMMY,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_OPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_TWO,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_READ_STATUS_OPI
    },
    [OSPI_B_TRANSFER_READ_CFR2V_OPI] =
    {
    .command        = OSPI_B_COMMAND_READ_REGISTER_OPI,
    .address        = OSPI_B_ADDRESS_CFR2V_REGISTER,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_OPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_TWO,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_READ_REGISTER_OPI
    },
    [OSPI_B_TRANSFER_READ_CFR3V_OPI] =
    {
    .command        = OSPI_B_COMMAND_READ_REGISTER_OPI,
    .address        = OSPI_B_ADDRESS_CFR3V_REGISTER,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_OPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_TWO,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_READ_REGISTER_OPI
    },
    [OSPI_B_TRANSFER_READ_CFR5V_OPI] =
    {
    .command        = OSPI_B_COMMAND_READ_REGISTER_OPI,
    .address        = OSPI_B_ADDRESS_CFR5V_REGISTER,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_OPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_FOUR,
    .data_length    = OSPI_B_DATA_LENGTH_TWO,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_READ_REGISTER_OPI
    },
    [OSPI_B_TRANSFER_READ_DEVICE_ID_OPI] =
    {
    .command        = OSPI_B_COMMAND_READ_DEVICE_ID_OPI,
    .address        = OSPI_B_ADDRESS_DUMMY,
    .data           = OSPI_B_DATA_DUMMY,
    .command_length = OSPI_B_COMMAND_LENGTH_OPI,
    .address_length = OSPI_B_ADDRESS_LENGTH_ZERO,
    .data_length    = OSPI_B_DATA_LENGTH_FOUR,
    .dummy_cycles   = OSPI_B_DUMMY_CYCLE_READ_STATUS_OPI
    },
};

/*******************************************************************************************************************//**
 * @} (end addtogroup ospi_b_commands.c)
 **********************************************************************************************************************/
