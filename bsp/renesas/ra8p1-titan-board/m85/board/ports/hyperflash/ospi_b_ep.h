/***********************************************************************************************************************
 * File Name    : ospi_b_ep.h
 * Description  : Contains data structures and functions used in ospi_ep.h.
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

#ifndef OSPI_B_EP_H_
#define OSPI_B_EP_H_

/* Macro for flash device */
#define OSPI_B_DEVICE_ID                    (0x21A5BEF)    // For W35T51NW flash  //(0x0F1A5B34)    // For S28HS512T flash
#define OSPI_B_DEVICE_HL_ID                 (0x21A5BEF)    // For W35T51NW flash  //(0x0F1A5A34)    // For S28HL512T flash
#define OSPI_B_MANUFACTURER_ID              (0xEF)         // For W35T51NW flash  //(0x34)          // For S28HL512T flash
#define OSPI_B_DEVICE_ID_TYPE               (0x5B)         // For S28HS512T flash
#define OSPI_B_DEVICE_HL_ID_TYPE            (0x5A)         // For S28HL512T flash
#define OSPI_B_DEVICE_ID_DENSITY            (0x1A)

/* Flash device sector size */
#define OSPI_B_SECTOR_SIZE_4K               (0x1000)
#define OSPI_B_SECTOR_SIZE_256K             (0x40000)
#define OSPI_B_SECTOR_SIZE_512K             (0x80000)
#define OSPI_B_SECTOR_4K_END_ADDRESS        (0x9001FFFF)

/* Flash device timing */
#define OSPI_B_TIME_UNIT                    (BSP_DELAY_UNITS_MICROSECONDS)
#define OSPI_B_TIME_RESET_SETUP             (2U)             //  Type 50ns
#define OSPI_B_TIME_RESET_PULSE             (1000U)          //  Type 500us
#define OSPI_B_TIME_ERASE_256K              (1500000U)       //  Type 256KB sector is 331 KBps -> Type 0.773s
#define OSPI_B_TIME_ERASE_4K                (100000U)        //  Type 4KB sector is 95 KBps -> Type 0.042s
#define OSPI_B_TIME_WRITE                   (10000U)         //  Type 256B page (4KB/256KB) is 595/533 KBps -> Type

/* Flash device status bit */
#define OSPI_B_WEN_BIT_MASK                 (0x00000002)
#define OSPI_B_BUSY_BIT_MASK                (0x00000001)

/* Flash device address space mapping */
#define OSPI_B_CS0_START_ADDRESS            (0x80000000)
#define OSPI_B_CS1_START_ADDRESS            (0x90000000)
#define OSPI_B_APP_ADDRESS(sector_no)       ((uint8_t *)(OSPI_B_CS1_START_ADDRESS + ((sector_no) * OSPI_B_SECTOR_SIZE_4K)))
#define OSPI_B_SECTOR_FIRST                 (0U)
#define OSPI_B_SECTOR_SECOND                (1U)
#define OSPI_B_SECTOR_THREE                 (2U)
#define OSPI_B_SECTOR_FOUR                  (3U)
#define OSPI_B_SECTOR_FIVE                  (4U)
#define OSPI_B_SECTOR_SIX                   (5U)
#define OSPI_B_SECTOR_SEVEN                 (6U)
#define OSPI_B_SECTOR_EIGHT                 (7U)
#define OSPI_B_APP_DATA_SIZE                (64U)

/* Macro for RTT Viewer handle */
#define RTT_SELECT_SPI_MODE_CHAR            ('1')
#define RTT_SELECT_OPI_MODE_CHAR            ('2')
#define RTT_SELECT_DMA_SPI_MODE_CHAR        ('3')
#define RTT_SELECT_DMA_OPI_MODE_CHAR        ('4')
#define RTT_SELECT_WRITE_OPERATION_CHAR     ('1')
#define RTT_SELECT_READ_OPERATION_CHAR      ('2')
#define RTT_SELECT_ERASE_OPERATION_CHAR     ('3')
#define RTT_EXIT_SUB_MENU_CHAR              ('4')
#define RTT_NULL_CHAR                       ('\0')
#define RTT_CHECK_INDEX                     (0U)

#define MAIN_MENU           "\r\nOSPI Main Menu, Protocol Mode Option:"\
                            "\r\n1. SPI 1S-1S-1S Protocol Mode"\
                            "\r\n2. OPI 8D-8D-8D Protocol Mode"\
                            "\r\nProtocol Mode Select: \r\n"

#define SUB_MENU            "\r\nOSPI Sub Menu, %s Operation Option:"\
                            "\r\n1. Write Operation"\
                            "\r\n2. Read Operation"\
                            "\r\n3. Erase Operation"\
                            "\r\n4. Go Back To Main menu"\
                            "\r\nOperation Select: \r\n"

#define EP_INFO             "\r\nThis example project demonstrates basic functionalities of OSPI driver\r\n"\
                            "on Renesas RA MCUs based on Renesas FSP. Based on the User input, EP performs\r\n"\
                            "read/write/erase operation in SPI mode (1S-1S-1S) or DOPI mode (8D-8D-8D).\r\n"\
                            "On successful completion of each operation, success message will be printed\r\n"\
                            "on RTT viewer. Error and info messages will be printed on JlinkRTTViewer.\r\n\n"

#define RESET_VALUE         (0x00)

typedef enum {
    flash_write,
    flash_read,
    flash_erase
} flash_opration_t;

/* function declarations*/
fsp_err_t ospi_b_init (void);
fsp_err_t ospi_b_set_protocol_to_spi (void);
fsp_err_t ospi_b_set_protocol_to_opi (void);
//fsp_err_t ospi_b_operation (uint8_t * p_address);
fsp_err_t ospi_b_operation (uint8_t *p_address, flash_opration_t operation);
fsp_err_t ospi_b_read_device_id (uint32_t * const p_id);
fsp_err_t timer_init (void);

#endif /* OSPI_B_EP_H_ */
