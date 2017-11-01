/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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

#include "usdhc/usdhc_ifc.h"
#include "usdhc.h"
#include "sdk.h"
#include "interrupt.h"
#include "usdhc_host.h"
#include "registers/regsusdhc.h"
#include "buffers.h"
#include "core/cortex_a9.h"
#include "utility/menu.h"

/* Global Variables */

usdhc_inst_t usdhc_device[USDHC_NUMBER_PORTS] = {
    {
     REGS_USDHC1_BASE,          //register base
     USDHC_ADMA_BUFFER1,        //ADMA base
     usdhc1_isr,                //ISR
     0,                         //RCA
     0,                         //addressing mode
     IMX_INT_USDHC1,            //interrupt ID
     1,                         //status
     }
    ,

    {
     REGS_USDHC2_BASE,          //register base
     USDHC_ADMA_BUFFER2,        //ADMA base
     usdhc2_isr,                //ISR
     0,                         //RCA
     0,                         //addressing mode
     IMX_INT_USDHC2,            //interrupt ID
     1,                         //status
     }
    ,

    {
     REGS_USDHC3_BASE,          //register base
     USDHC_ADMA_BUFFER3,        //ADMA base
     usdhc3_isr,                //ISR
     0,                         //RCA
     0,                         //addressing mode
     IMX_INT_USDHC3,            //interrupt ID
     1,                         //status
     }
    ,

    {
     REGS_USDHC4_BASE,          //register base
     USDHC_ADMA_BUFFER4,        //ADMA base
     usdhc4_isr,                //ISR
     0,                         //RCA
     0,                         //addressing mode
     IMX_INT_USDHC4,            //interrupt ID
     1,                         //status
     }
    ,
};

/* Whether to enable Card Detect Test in card_init() */
int card_detect_test_en = 1;
extern bool usdhc_card_detected(uint32_t instance);

/* Whether to enable Card Protect Test in card_init() */
int write_protect_test_en = 1;
extern bool usdhc_write_protected(uint32_t instance);

/* Whether to enable ADMA */
static int SDHC_ADMA_mode = FALSE;

/* Whether to enable Interrupt */
static int SDHC_INTR_mode = FALSE;

/********************************************* Static Function ******************************************/
/*!
 * @brief Softreset card and then send CMD0 to card
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
static int card_software_reset(uint32_t instance)
{
    command_t cmd;
    int response = FAIL;

    /* Configure CMD0 */
    card_cmd_config(&cmd, CMD0, NO_ARG, READ, RESPONSE_NONE, DATA_PRESENT_NONE, FALSE, FALSE);

    usdhc_printf("Send CMD0.\n");

    /* Issue CMD0 to Card */
    if (host_send_cmd(instance, &cmd) == SUCCESS) {
        response = SUCCESS;
    }

    return response;
}

/*!
 * @brief Enable interrupt for the card
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
static int card_init_interrupt(uint32_t instance)
{
    int idx = card_get_port(instance);

    if (idx == USDHC_NUMBER_PORTS) {
        printf("Base address: 0x%x not in address table.\n", REGS_USDHC_BASE(instance));
        return FAIL;
    }

    /* Disable interrupt */
    disable_interrupt(usdhc_device[idx].intr_id, CPU_0);

    /* Register interrupt */
    register_interrupt_routine(usdhc_device[idx].intr_id, usdhc_device[idx].isr);

    /* Enable interrupt */
    enable_interrupt(usdhc_device[idx].intr_id, CPU_0, 0);

    return SUCCESS;
}

/********************************************* Global Function ******************************************/
/*!
 * @brief Set Card access mode
 *
 * @param mode     Set card access mode
 * 
 * @return           
 */
extern void set_card_access_mode(uint32_t sdma, uint32_t intr)
{
	/* Whether to enable ADMA */
    SDHC_ADMA_mode = sdma;

	/* Whether to enable Interrupt */
    SDHC_INTR_mode = intr; 	
}
 
uint32_t read_usdhc_adma_mode()
{
	return SDHC_ADMA_mode;
}
uint32_t read_usdhc_intr_mode() 
{
	return SDHC_INTR_mode;
}

/*!
 * @brief Card initialization
 *
 * @param instance     Instance number of the uSDHC module.
 * @param bus_width    Bus width
 * 
 * @return             0 if successful; 1 otherwise
 */
int card_init(uint32_t instance, int bus_width)
{
    int init_status = FAIL;
    const char* indent = menu_get_indent();

    /* Initialize uSDHC Controller */
    host_init(instance);

    /* Software Reset to Interface Controller */
    host_reset(instance, ESDHC_ONE_BIT_SUPPORT, ESDHC_LITTLE_ENDIAN_MODE);

    /* card detect */
    if(card_detect_test_en) {
        if(usdhc_card_detected(instance) == false) {
            printf("%s   *Card on SD%d is not inserted.\n", indent, instance);
            return FAIL;
        } else {
            printf("%s   Card on SD%d is inserted.\n", indent, instance);
        }
    }

    /* write protect */
    if(write_protect_test_en) {
        if(usdhc_write_protected(instance) == true) {
            printf("%s   *Card on SD%d is write protected.\n", indent, instance);
            return FAIL;
        } else {
            printf("%s   Card on SD%d is not write protected.\n", indent, instance);
        }
    }

    /* Initialize interrupt */
    if (card_init_interrupt(instance) == FAIL) {
        printf("%s   Interrupt initialize failed.\n", indent);
        return FAIL;
    }

    /* Enable Identification Frequency */
    host_cfg_clock(instance, IDENTIFICATION_FREQ);

    /* Send Init 80 Clock */
    host_init_active(instance);

    usdhc_printf("Reset card.\n");

    /* Issue Software Reset to card */
    if (card_software_reset(instance) == FAIL) {
        return FAIL;
    }

    /* SD Voltage Validation */
    if (sd_voltage_validation(instance) == SUCCESS) {
        usdhc_printf("SD voltage validation passed.\n");

        /* SD Initialization */
        init_status = sd_init(instance, bus_width);
    }

    /* MMC Voltage Validation */
    else if (mmc_voltage_validation(instance) == SUCCESS) {
        usdhc_printf("MMC voltage validation passed.\n");

        /* MMC Initialization */
        init_status = mmc_init(instance, bus_width);
    }

    return init_status;
}

/*!
 * @brief eMMC Card initialization
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
int card_emmc_init(uint32_t instance)
{
    int init_status = FAIL;

    /* Initialize uSDHC Controller */
    host_init(instance);

    /* Software Reset to Interface Controller */
    host_reset(instance, ESDHC_ONE_BIT_SUPPORT, ESDHC_LITTLE_ENDIAN_MODE);

    /* Enable Identification Frequency */
    host_cfg_clock(instance, IDENTIFICATION_FREQ);

    /* Send Init 80 Clock */
    host_init_active(instance);

    /* Issue Software Reset to card */
    if (card_software_reset(instance) == FAIL) {
        return init_status;
    }

    /* MMC Voltage Validation */
    else if (mmc_voltage_validation(instance) == SUCCESS) {

        /* MMC Initialization */
        init_status = emmc_init(instance);
    }

    return init_status;
}

#if 0
int card_get_csd(int base_address)
{

    command_t cmd;
    command_response_t response;
    int status = FAIL;
    int card_address = (card_rca << RCA_SHIFT);

    /* Configure CMD9 for MMC/SD card */
    mxcmci_cmd_config(&cmd, CMD9, card_address, READ, RESPONSE_136, DATA_PRESENT_NONE, TRUE, FALSE);

    if (host_send_cmd(base_address, &cmd) == SUCCESS) {
        response.format = RESPONSE_136;
        host_read_response(base_address, &response);

        csd.csd0 = response.cmd_rsp0;
        csd.csd1 = response.cmd_rsp1;
        csd.csd2 = response.cmd_rsp2;
        csd.csd3 = response.cmd_rsp3;

        status = SUCCESS;
    }

    return status;
}
#endif

/*!
 * @brief Build up command
 *
 * @param cmd      IPointer of command to be build up.
 * @param index    Command index.
 * @param argument Argument of the command.
 * @param transfer Command transfer type - Read, Write or SD command.
 * @param format   Command response format
 * @param data     0 - no data present, 1 - data present.
 * @param src      0 - no CRC check, 1 - do CRC check
 * @param cmdindex 0 - no check on command index, 1 - Check comamnd index
 */
void card_cmd_config(command_t * cmd, int index, int argument, xfer_type_t transfer,
                     response_format_t format, data_present_select data,
                     crc_check_enable crc, cmdindex_check_enable cmdindex)
{
    cmd->command = index;
    cmd->arg = argument;
    cmd->data_transfer = transfer;
    cmd->response_format = format;
    cmd->data_present = data;
    cmd->crc_check = crc;
    cmd->cmdindex_check = cmdindex;
    cmd->dma_enable = FALSE;
    cmd->block_count_enable_check = FALSE;
    cmd->multi_single_block = SINGLE;
    cmd->acmd12_enable = FALSE;
    cmd->ddren = FALSE;

    /* Multi Block R/W Setting */
    if ((CMD18 == index) || (CMD25 == index)) {
        if (SDHC_ADMA_mode == TRUE) {
            cmd->dma_enable = TRUE;
        }

        cmd->block_count_enable_check = TRUE;
        cmd->multi_single_block = MULTIPLE;
        cmd->acmd12_enable = TRUE;
    }
}

/*!
 * @brief Get Card CID
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
int card_get_cid(uint32_t instance)
{
    command_t cmd;
    int status = FAIL;
    command_response_t response;

    /* Configure CMD2 */
    card_cmd_config(&cmd, CMD2, NO_ARG, READ, RESPONSE_136, DATA_PRESENT_NONE, TRUE, FALSE);

    usdhc_printf("Send CMD2.\n");

    /* Send CMD2 */
    if (host_send_cmd(instance, &cmd) == SUCCESS) {
        response.format = RESPONSE_136;
        host_read_response(instance, &response);

        /* No Need to Save CID */

        status = SUCCESS;
    }

    return status;
}

/*!
 * @brief Toggle the card between the standby and transfer states
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
int card_enter_trans(uint32_t instance)
{
    command_t cmd;
    int card_address, port, status = FAIL;

    /* Get port from base address */
    port = card_get_port(instance);

    /* Get RCA */
    card_address = usdhc_device[port].rca << RCA_SHIFT;

    /* Configure CMD7 */
    card_cmd_config(&cmd, CMD7, card_address, READ, RESPONSE_48_CHECK_BUSY,
                    DATA_PRESENT_NONE, TRUE, TRUE);

    usdhc_printf("Send CMD7.\n");

    /* Send CMD7 */
    if (host_send_cmd(instance, &cmd) == SUCCESS) {
        /* Check if the card in TRAN state */
        if (card_trans_status(instance) == SUCCESS) {
            status = SUCCESS;
        }
    }

    return status;
}

/*!
 * @brief Addressed card send its status register
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
int card_trans_status(uint32_t instance)
{
    command_t cmd;
    command_response_t response;
    int card_state, card_address, port, status = FAIL;

    /* Get Port */
    port = card_get_port(instance);

    /* Get RCA */
    card_address = usdhc_device[port].rca << RCA_SHIFT;

    /* Configure CMD13 */
    card_cmd_config(&cmd, CMD13, card_address, READ, RESPONSE_48, DATA_PRESENT_NONE, TRUE, TRUE);

    usdhc_printf("Send CMD13.\n");

    /* Send CMD13 */
    if (host_send_cmd(instance, &cmd) == SUCCESS) {
        /* Get Response */
        response.format = RESPONSE_48;
        host_read_response(instance, &response);

        /* Read card state from response */
        card_state = CURR_CARD_STATE(response.cmd_rsp0);
        if (card_state == TRAN) {
            status = SUCCESS;
        }
    }

    return status;
}

/*!
 * @brief Get the card port 
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             The index of port
 */
int card_get_port(uint32_t instance)
{
    int idx;
    int base_address = REGS_USDHC_BASE(instance);
    
    for (idx = 0; idx < USDHC_NUMBER_PORTS; idx++) {
        if (usdhc_device[idx].reg_base == base_address) {
            break;
        }
    }

    return idx;
}

/*!
 * @brief Set block length (in bytes) for read and write
 *
 * @param instance     Instance number of the uSDHC module.
 * @param len          Block length to be set
 * 
 * @return             0 if successful; 1 otherwise
 */
int card_set_blklen(uint32_t instance, int len)
{
    command_t cmd;
    int status = FAIL;

    /* Configure CMD16 */
    card_cmd_config(&cmd, CMD16, len, READ, RESPONSE_48, DATA_PRESENT_NONE, TRUE, TRUE);

    usdhc_printf("Send CMD16.\n");

    /* Send CMD16 */
    if (host_send_cmd(instance, &cmd) == SUCCESS) {
        status = SUCCESS;
    } 
    
    return status;
}

static void card_buffer_flush(void *buffer, int length)
{
    if(!arm_dcache_state_query())
        return;

        arm_dcache_flush_mlines(buffer, length);
        arm_dcache_invalidate_mlines(buffer, length);
}

/*!
 * @brief Read data from card
 *
 * @param instance     Instance number of the uSDHC module.
 * @param dst_ptr      Data destination pointer
 * @param length       Data length to be read
 * @param offset       Data reading offset
 * 
 * @return             0 if successful; 1 otherwise
 */
int card_data_read(uint32_t instance, int *dst_ptr, int length, uint32_t offset)
{
    int port, sector;
    command_t cmd;

    /* Get uSDHC port according to instance */
    port = card_get_port(instance);
    if (port == USDHC_NUMBER_PORTS) {
        printf("Base address: 0x%x not in address table.\n", REGS_USDHC_BASE(instance));
        return FAIL;
    }

    usdhc_printf("card_data_read: Read 0x%x bytes from SD%d offset 0x%x to 0x%x.\n",
                 length, port + 1, offset, (int)dst_ptr);

    /* Get sector number */
    if (SDHC_ADMA_mode == TRUE) {
        /* For DMA mode, length should be sector aligned */
        if ((length % BLK_LEN) != 0) {
            length = length + BLK_LEN - (length % BLK_LEN);
        }

        sector = length / BLK_LEN;
    } else {
        /* For PIO mode, not neccesary */
        sector = length / BLK_LEN;

        if ((length % BLK_LEN) != 0) {
            sector++;
        }
    }

    /* Offset should be sectors */
    if (usdhc_device[port].addr_mode == SECT_MODE) {
        offset = offset / BLK_LEN;
    }

    /* Set block length to card */
    if (card_set_blklen(instance, BLK_LEN) == FAIL) {
        printf("Fail to set block length to card in reading sector %d.\n", offset / BLK_LEN);
        return FAIL;
    }

    /* Clear Rx FIFO */
    host_clear_fifo(instance);

    /* Configure block length/number and watermark */
    host_cfg_block(instance, BLK_LEN, sector, ESDHC_BLKATTR_WML_BLOCK);

    /* If DMA mode enabled, configure BD chain */
    if (SDHC_ADMA_mode == TRUE) {
        host_setup_adma(instance, dst_ptr, length);
        card_buffer_flush(dst_ptr, length);
    }

    /* Use CMD18 for multi-block read */
    card_cmd_config(&cmd, CMD18, offset, READ, RESPONSE_48, DATA_PRESENT, TRUE, TRUE);

    usdhc_printf("card_data_read: Send CMD18.\n");

    /* Send CMD18 */
    if (host_send_cmd(instance, &cmd) == FAIL) {
        printf("Fail to send CMD18.\n");
        return FAIL;
    } else {
        /* In polling IO mode, manually read data from Rx FIFO */
        if (SDHC_ADMA_mode == FALSE) {
            usdhc_printf("Non-DMA mode, read data from FIFO.\n");

            if (host_data_read(instance, dst_ptr, length, ESDHC_BLKATTR_WML_BLOCK) == FAIL) {
                printf("Fail to read data from card.\n");
                return FAIL;
            }
        }
    }

    usdhc_printf("card_data_read: Data read successful.\n");

    return SUCCESS;
}

/*!
 * @brief Write data to card
 *
 * @param instance     Instance number of the uSDHC module.
 * @param src_ptr      Data source pointer
 * @param length       Data length to be writen
 * @param offset       Data writing offset
 * 
 * @return             0 if successful; 1 otherwise
 */
int card_data_write(uint32_t instance, int *src_ptr, int length, int offset)
{
    int port, sector;
    command_t cmd;

    /* Get uSDHC port according to base address */
    port = card_get_port(instance);
    if (port == USDHC_NUMBER_PORTS) {
        printf("Base address: 0x%x not in address table.\n", REGS_USDHC_BASE(instance));
        return FAIL;
    }

    usdhc_printf("card_data_write: write 0x%x bytes to SD%d offset 0x%x from 0x%x.\n",
                 length, port + 1, offset, (int)src_ptr);

    /* Get sector number */
    if (SDHC_ADMA_mode == TRUE) {
        /* For DMA mode, length should be sector aligned */
        if ((length % BLK_LEN) != 0) {
            length = length + BLK_LEN - (length % BLK_LEN);
        }

        sector = length / BLK_LEN;
    } else {
        /* For PIO mode, not neccesary */
        sector = length / BLK_LEN;

        if ((length % BLK_LEN) != 0) {
            sector++;
        }
    }

    /* Offset should be sectors */
    if (usdhc_device[port].addr_mode == SECT_MODE) {
        offset = offset / BLK_LEN;
    }

    /* Set block length to card */
    if (card_set_blklen(instance, BLK_LEN) == FAIL) {
        printf("Fail to set block length to card in writing sector %d.\n", offset / BLK_LEN);
        return FAIL;
    }

    /* Configure block length/number and watermark */
    host_cfg_block(instance, BLK_LEN, sector, ESDHC_BLKATTR_WML_BLOCK << ESDHC_WML_WRITE_SHIFT);

    /* If DMA mode enabled, configure BD chain */
    if (SDHC_ADMA_mode == TRUE) {
        host_setup_adma(instance, src_ptr, length);
        card_buffer_flush(src_ptr, length);        
    }

    /* Use CMD25 for multi-block write */
    card_cmd_config(&cmd, CMD25, offset, WRITE, RESPONSE_48, DATA_PRESENT, TRUE, TRUE);

    usdhc_printf("card_data_write: Send CMD25.\n");

    /* Send CMD25 */
    if (host_send_cmd(instance, &cmd) == FAIL) {
        printf("Fail to send CMD25.\n");
        return FAIL;
    } else {
        if (SDHC_ADMA_mode == FALSE) {
            usdhc_printf("Non-DMA mode, write to FIFO.\n");

            if (host_data_write(instance, src_ptr, length, ESDHC_BLKATTR_WML_BLOCK) == FAIL) {
                printf("Fail to write data to card.\n");
                return FAIL;
            }
        }

        usdhc_printf("card_data_write: Data written successful.\n");
    }

    return SUCCESS;
}

/*!
 * @brief Get card status
 *
 * @param instance     Instance number of the uSDHC module.
 * @param result       Card status
 * 
 * @return             0 if successful; 1 otherwise
 */
int card_xfer_result(uint32_t instance, int *result)
{
    int idx = card_get_port(instance);

    if (idx == USDHC_NUMBER_PORTS) {
        printf("Base address: 0x%x not in address table.\n", REGS_USDHC_BASE(instance));
        return FAIL;
    }

    *result = usdhc_device[idx].status;

    return SUCCESS;
}

/*!
 * @brief Wait for the transfer complete. It covers the interrupt mode, DMA mode and PIO mode
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
int card_wait_xfer_done(uint32_t instance)
{
    int usdhc_status = 0;
    int timeout = 0x40000000;
    if(SDHC_INTR_mode)
    {
        while (timeout--) {
            card_xfer_result(instance, &usdhc_status);
            if (usdhc_status == 1)
                return SUCCESS;
        }
     } else {
            /*do nothing, since in PIO/DMA mode, will check the flag in host send data*/
            return SUCCESS;
     }

     return FAIL;
}
