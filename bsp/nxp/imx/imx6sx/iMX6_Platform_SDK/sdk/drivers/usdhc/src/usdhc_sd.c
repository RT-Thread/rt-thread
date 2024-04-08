/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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

#include "usdhc.h"
#include "sdk.h"
#include "usdhc_host.h"
#include "registers/regsusdhc.h"
#include "timer/timer.h"

const unsigned int sd_ocr_value[SD_OCR_VALUE_COUNT] = {
    SD_OCR_VALUE_HV_HC,
    SD_OCR_VALUE_LV_HC,
    SD_OCR_VALUE_HV_LC,
};

const unsigned int sd_if_cmd_arg[SD_IF_CMD_ARG_COUNT] = {
    SD_IF_HV_COND_ARG,
    SD_IF_LV_COND_ARG,
};

/********************************************* Static Function ******************************************/
/*!
 * @brief Read RCA (relative card address) of SD card
 * 
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
static int sd_get_rca(uint32_t instance)
{
    command_t cmd;
    int port, card_state, status = FAIL;
    command_response_t response;

    /* Check uSDHC Port */
    port = card_get_port(instance);
    if (port == USDHC_NUMBER_PORTS) {
        printf("Base address: 0x%x not in address table.\n", REGS_USDHC_BASE(instance));
        return status;
    }

    /* Configure CMD3 */
    card_cmd_config(&cmd, CMD3, NO_ARG, READ, RESPONSE_48, DATA_PRESENT_NONE, TRUE, TRUE);

    usdhc_printf("Send CMD3.\n");

    /* Send CMD3 */
    if (host_send_cmd(instance, &cmd) == SUCCESS) {
        response.format = RESPONSE_48;
        host_read_response(instance, &response);

        /* Set RCA to Value Read */
        usdhc_device[port].rca = response.cmd_rsp0 >> RCA_SHIFT;

        /* Check the IDENT card state */
        card_state = CURR_CARD_STATE(response.cmd_rsp0);

        if (card_state == IDENT) {
            status = SUCCESS;
        }
    }

    return status;
}

/*!
 * @brief Set SD card bus width
 * 
 * @param instance     Instance number of the uSDHC module.
 * @param data_width   Data transfer width
 * 
 * @return             0 if successful; 1 otherwise
 */
static int sd_set_bus_width(uint32_t instance, int bus_width)
{
    command_t cmd;
    int port, address, status = FAIL;
    command_response_t response;

    /* Check uSDHC Port */
    port = card_get_port(instance);
    if (port == USDHC_NUMBER_PORTS) {
        printf("Base address: 0x%x not in address table.\n", REGS_USDHC_BASE(instance));
        return status;
    }

    address = usdhc_device[port].rca << RCA_SHIFT;

    /* Check Bus Width */
    if ((bus_width != FOUR) && (bus_width != ONE)) {
        printf("Invalid bus_width: %d\n", bus_width);
        return status;
    }

    /* Configure CMD55 */
    card_cmd_config(&cmd, CMD55, address, READ, RESPONSE_48, DATA_PRESENT_NONE, TRUE, TRUE);

    usdhc_printf("Send CMD55.\n");

    /* Send ACMD6 */
    if (host_send_cmd(instance, &cmd) == SUCCESS) {
        /* Check Response of Application Command */
        response.format = RESPONSE_48;
        host_read_response(instance, &response);

        if (response.cmd_rsp0 & SD_R1_STATUS_APP_CMD_MSK) {
            bus_width = bus_width >> ONE;

            /* Configure ACMD6 */
            card_cmd_config(&cmd, ACMD6, bus_width, READ, RESPONSE_48, DATA_PRESENT_NONE, TRUE, TRUE);

            usdhc_printf("Send CMD6.\n");

            /* Send ACMD6 */
            if (host_send_cmd(instance, &cmd) == SUCCESS) {
                status = SUCCESS;
            }
        }
    }

    return status;
}

/********************************************* Global Function ******************************************/
/*!
 * @brief Initialize SD - Get Card ID, Set RCA, Frequency and bus width.
 * 
 * @param instance     Instance number of the uSDHC module.
 * @param bus_width    bus width to be configured.
 * 
 * @return             0 if successful; 1 otherwise
 */
int sd_init(uint32_t instance, int bus_width)
{
    int status = FAIL;

    usdhc_printf("Get CID.\n");

    /* Read CID */
    if (card_get_cid(instance) == SUCCESS) {
        usdhc_printf("Get RCA.\n");

        /* Obtain RCA */
        if (sd_get_rca(instance) == SUCCESS) {
            usdhc_printf("Set operating frequency.\n");

            /* Enable Operating Freq */
            host_cfg_clock(instance, OPERATING_FREQ);

            if (bus_width == EIGHT) {
                bus_width = FOUR;
            }

            usdhc_printf("Enter transfer state.\n");

            /* Enter Transfer State */
            if (card_enter_trans(instance) == SUCCESS) {
                usdhc_printf("Set bus width.\n");

                /* Set Bus Width for SD card */
                if (sd_set_bus_width(instance, bus_width) == SUCCESS) {
                    /* Set Bus Width for Controller */
                    host_set_bus_width(instance, bus_width);

                    /* Set High Speed Here */
                    {
                        status = SUCCESS;
                    }
                }
            }
        }
    }

    return status;
}

/*!
 * @brief Valid the voltage.
 * 
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
int sd_voltage_validation(uint32_t instance)
{
    command_t cmd;
    command_response_t response;
    int port, loop = ZERO, status = FAIL;
    unsigned int ocr_value = ZERO, card_usable = FAIL;

    /* Check uSDHC Port from Base Address */
    port = card_get_port(instance);
    if (port == USDHC_NUMBER_PORTS) {
        printf("Base address: 0x%x not in address table.\n", REGS_USDHC_BASE(instance));
        return status;
    }

    usdhc_printf("Send CMD8.\n");

    while (loop < SD_IF_CMD_ARG_COUNT) {
        card_cmd_config(&cmd, CMD8, sd_if_cmd_arg[loop], READ, RESPONSE_48, DATA_PRESENT_NONE, TRUE, TRUE);
        if (host_send_cmd(instance, &cmd) == FAIL) {
            loop++;

            if ((loop >= SD_IF_CMD_ARG_COUNT) && (loop < SD_OCR_VALUE_COUNT)) {
                /* Card is of SD-1.x spec with LC */
                ocr_value = sd_ocr_value[loop];
                card_usable = SUCCESS;
            }
        } else {
            /* Card is supporting SD spec version >= 2.0 */
            response.format = RESPONSE_48;
            host_read_response(instance, &response);

            /* Check if response lies in the expected volatge range */
            if ((response.cmd_rsp0 & sd_if_cmd_arg[loop]) == sd_if_cmd_arg[loop]) {
                ocr_value = sd_ocr_value[loop];
                card_usable = SUCCESS;

                break;
            } else {
                ocr_value = ZERO;
                card_usable = FAIL;

                break;
            }
        }
    }

    loop = ZERO;

    if (card_usable == FAIL) {
        return status;
    }

    usdhc_printf("Send ACMD41.\n");

    while ((loop < SD_VOLT_VALID_COUNT) && (status == FAIL)) {
        card_cmd_config(&cmd, CMD55, ZERO, READ, RESPONSE_48, DATA_PRESENT_NONE, TRUE, TRUE);

        if (host_send_cmd(instance, &cmd) == FAIL) {
            usdhc_printf("Send CMD55 failed.\n");
            break;
        } else {
            card_cmd_config(&cmd, ACMD41, ocr_value, READ, RESPONSE_48, DATA_PRESENT_NONE, FALSE, FALSE);

            if (host_send_cmd(instance, &cmd) == FAIL) {
                usdhc_printf("Send ACMD41 failed.\n");
                break;
            } else {
                /* Check Response */
                response.format = RESPONSE_48;
                host_read_response(instance, &response);

                /* Check Busy Bit Cleared or NOT */
                if (response.cmd_rsp0 & CARD_BUSY_BIT) {
                    /* Check card is HC or LC from card response */
                    if ((response.cmd_rsp0 & SD_OCR_HC_RES) == SD_OCR_HC_RES) {
                        usdhc_device[port].addr_mode = SECT_MODE;
                    } else {
                        usdhc_device[port].addr_mode = BYTE_MODE;
                    }

                    status = SUCCESS;
                } else {
                    loop++;
                    hal_delay_us(SD_VOLT_VALID_DELAY);
                }
            }
        }
    }

    return status;
}
