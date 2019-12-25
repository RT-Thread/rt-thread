/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "nrf_cli.h"
#include "nrf_log.h"

static void cmd_reset(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    NVIC_SystemReset();
}


static void cmd_error(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
}


static void cmd_app_size(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    nrf_cli_fprintf(p_cli,
                    NRF_CLI_NORMAL,
                    "Application address:%d (0x%08X), size: %d (0x%08X)\r\n",
                    CODE_START,
                    CODE_START,
                    CODE_SIZE,
                    CODE_SIZE);
}


static void cmd_log_msg_error(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    switch (argc-1)
    {
        case 0:
            NRF_LOG_ERROR("test error message");
            break;
        case 1:
            NRF_LOG_ERROR("test error message: %d", strtol(argv[1], NULL, 10));
            break;
        case 2:
            NRF_LOG_ERROR("test error message: %d %d", strtol(argv[1], NULL, 10),
                                                       strtol(argv[2], NULL, 10));
            break;
        default:
            NRF_LOG_ERROR("test error message with more than 3 arguments"); 
            break;
    }
}


static void cmd_log_msg_warning(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    switch (argc-1)
    {
        case 0:
            NRF_LOG_WARNING("test warning message");
            break;
        case 1:
            NRF_LOG_WARNING("test warning message: %d", strtol(argv[1], NULL, 10));
            break;
        case 2:
            NRF_LOG_WARNING("test warning message: %d %d", strtol(argv[1], NULL, 10),
                                                       strtol(argv[2], NULL, 10));
            break;
        default:
            NRF_LOG_WARNING("test warning message with more than 3 arguments"); 
            break;
    }
}

/**
 * @brief Command set array
 * */

NRF_CLI_CMD_REGISTER(reset, NULL, "System reset.", cmd_reset);

NRF_CLI_CMD_REGISTER(error, NULL, "Trigger error.", cmd_error);

NRF_CLI_CMD_REGISTER(app_size, NULL, "Print application size.", cmd_app_size);

NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_log_msg)
{
    NRF_CLI_CMD(error,   NULL, "Error log message with parameters", cmd_log_msg_error),
    NRF_CLI_CMD(warning, NULL, "Warning log message with parameters", cmd_log_msg_warning),
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(log_msg, &m_sub_log_msg, "Trigger log message with decimal arguments", NULL);
