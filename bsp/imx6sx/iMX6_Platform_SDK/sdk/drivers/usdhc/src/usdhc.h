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
#ifndef __USDHC_H__
#define __USDHC_H__

#include "sdk.h"

#ifdef USDHC_DEBUG
#define usdhc_printf(args...) printf(args)
#else
#define usdhc_printf(args...)
#endif

/*------------------------------------------- Macros --------------------------------------------*/

#define ZERO 0
#define ONE 1
#define FOUR 4
#define EIGHT 8

#define NO_ARG 0
#define RCA_SHIFT 16
#define CURR_CARD_STATE(r) ((int) ((r) & 0x1E00) >> 9)

#define BYTE_MODE 0
#define SECT_MODE 1

#define BLK_LEN 512

#define CARD_BUSY_BIT 0x80000000

/* MMC Defines */
#define MMC_SWITCH_SETBW_ARG(bus_width) (unsigned int)(0x03b70001 | ((bus_width >> 2) << 8))
#define MMC_HV_HC_OCR_VALUE 0x40FF8000
#define MMC_OCR_HC_RESP_VAL 0x40000000
#define MMC_OCR_HC_BIT_MASK 0x60000000

#define MMC_VOLT_VALID_COUNT 3000
#define MMC_VOLT_VALID_DELAY 300

/* SD Defines */
#define SD_VOLT_VALID_COUNT 3000
#define SD_VOLT_VALID_DELAY 300

#define SD_R1_STATUS_APP_CMD_MSK 0x20

#define SD_OCR_VALUE_HV_LC 0x00ff8000
#define SD_OCR_VALUE_HV_HC 0x40ff8000
#define SD_OCR_VALUE_LV_HC 0x40000080
#define SD_OCR_HC_RES      0x40000000
#define SD_IF_HV_COND_ARG  0x000001AA
#define SD_IF_LV_COND_ARG  0x000002AA

#define SD_OCR_VALUE_COUNT  3
#define SD_IF_CMD_ARG_COUNT 2

/*------------------------------------------- Enumerations --------------------------------------------*/
enum card_type_e {
    CARD_SD = 0,
    CARD_MMC = 1,
    CARD_ESD = 2,
    CARD_EMMC = 3
};

enum commands {
    CMD0 = 0,
    CMD1 = 1,
    CMD2 = 2,
    CMD3 = 3,
    CMD5 = 5,
    CMD6 = 6,
    ACMD6 = 6,
    CMD7 = 7,
    CMD8 = 8,
    CMD9 = 9,
    CMD12 = 12,
    CMD13 = 13,
    CMD16 = 16,
    CMD17 = 17,
    CMD18 = 18,
    CMD24 = 24,
    CMD25 = 25,
    CMD26 = 26,
    CMD32 = 32,
    CMD33 = 33,
    CMD35 = 35,
    CMD36 = 36,
    CMD37 = 37,
    CMD38 = 38,
    CMD39 = 39,
    ACMD41 = 41,
    CMD43 = 43,
    ACMD51 = 51,
    CMD55 = 55,
    CMD60 = 60,
    CMD61 = 61,
    CMD62 = 62,
};

enum states {
    IDLE,
    READY,
    IDENT,
    STBY,
    TRAN,
    DATA,
    RCV,
    PRG,
    DIS
};

enum usdhc_port_e {
    USDHC_PORT1 = 0,
    USDHC_PORT2 = 1,
    USDHC_PORT3 = 2,
    USDHC_PORT4 = 3,
    USDHC_NUMBER_PORTS = 4
};

typedef enum {
    WRITE = 0,
    READ = 1,
    SD_COMMAND = 2
} xfer_type_t;

typedef enum {
    RESPONSE_NONE,
    RESPONSE_136,
    RESPONSE_48,
    RESPONSE_48_CHECK_BUSY
} response_format_t;

typedef enum {
    DATA_PRESENT_NONE = 0,
    DATA_PRESENT = 1
} data_present_select;

typedef enum {
    DISABLE = 0,
    ENABLE = 1
} crc_check_enable, cmdindex_check_enable, block_count_enable, ddren_enable;

typedef enum {
    SINGLE = 0,
    MULTIPLE = 1
} multi_single_block_select;

enum intr_status {
    INTR_BUSY = 0,
    INTR_TC = 1,
    INTR_ERROR = 2
};

typedef struct {
    unsigned int command;
    unsigned int arg;
    xfer_type_t data_transfer;
    response_format_t response_format;
    data_present_select data_present;
    crc_check_enable crc_check;
    cmdindex_check_enable cmdindex_check;
    block_count_enable block_count_enable_check;
    multi_single_block_select multi_single_block;
    unsigned int dma_enable;
    unsigned int acmd12_enable;
    ddren_enable ddren;
} command_t;

typedef struct {
    response_format_t format;
    unsigned int cmd_rsp0;
    unsigned int cmd_rsp1;
    unsigned int cmd_rsp2;
    unsigned int cmd_rsp3;
} command_response_t;

typedef struct {
    unsigned int reg_base;      //register base address
    unsigned int adma_ptr;      //ADMA buffer address
    void (*isr) (void);         //interrupt service routine

    unsigned short rca;         //relative card address
    unsigned char addr_mode;    //addressing mode
    unsigned char intr_id;      //interrupt ID
    unsigned char status;       //interrupt status
} usdhc_inst_t;

/* uSDHC device table */
extern usdhc_inst_t usdhc_device[];

/*------------------------------------------- Function Defines --------------------------------------------*/
/*!
 * @brief Set Card access mode
 *
 * @param mode     Set card access mode
 * 
 * @return           
 */
extern void set_card_access_mode(uint32_t sdma, uint32_t intr);
extern uint32_t read_usdhc_adma_mode();
extern uint32_t read_usdhc_intr_mode(); 
/*!
 * @brief Card initialization
 *
 * @param instance     Instance number of the uSDHC module.
 * @param bus_width    Bus width
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int card_init(uint32_t instance, int bus_width);

/*!
 * @brief eMMC Card initialization
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int card_emmc_init(uint32_t instance);

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
                     crc_check_enable crc, cmdindex_check_enable cmdindex);

/*!
 * @brief Get Card CID
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int card_get_cid(uint32_t instance);                     

/*!
 * @brief Toggle the card between the standby and transfer states
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int card_enter_trans(uint32_t instance);

/*!
 * @brief Addressed card send its status register
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int card_trans_status(uint32_t instance);

/*!
 * @brief Get the card port 
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             The index of port
 */
extern int card_get_port(uint32_t instance);

/*!
 * @brief Set block length (in bytes) for read and write
 *
 * @param instance     Instance number of the uSDHC module.
 * @param len          Block length to be set
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int card_set_blklen(uint32_t instance, int len);

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
extern int card_data_read(uint32_t instance, int *dst_ptr, int length, uint32_t offset);

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
extern int card_data_write(uint32_t instance, int *src_ptr, int length, int offset);

/*!
 * @brief Get card status
 *
 * @param instance     Instance number of the uSDHC module.
 * @param result       Card status
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int card_xfer_result(uint32_t instance, int *result);

/*!
 * @brief Wait for the transfer complete. It covers the interrupt mode, DMA mode and PIO mode
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int card_wait_xfer_done(uint32_t instance);

/*!
 * @brief Initialize MMC - Get Card ID, Set RCA, Frequency and bus width.
 * 
 * @param instance     Instance number of the uSDHC module.
 * @param bus_width    bus width to be configured.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int mmc_init(uint32_t instance, int bus_width);

/*!
 * @brief Initialize eMMC - Get Card ID, Set RCA, Frequency and bus width.
 * 
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int emmc_init(uint32_t instance);

/*!
 * @brief Valid the voltage.
 * 
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int mmc_voltage_validation(uint32_t instance);

/*!
 * @brief Initialize SD - Get Card ID, Set RCA, Frequency and bus width.
 * 
 * @param instance     Instance number of the uSDHC module.
 * @param bus_width    bus width to be configured.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int sd_init(uint32_t instance, int bus_width);

/*!
 * @brief Valid the voltage.
 * 
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int sd_voltage_validation(uint32_t instance);

#endif
