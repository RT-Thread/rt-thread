/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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

#include "sdk.h"
#include "imx_spi_nor_atmel.h"
#include "spi/ecspi_ifc.h"

extern dev_ecspi_e dev_spi_nor;

static uint8_t spi_nor_tx_buf[SPI_NOR_XFER_SZ];
static uint8_t spi_nor_rx_buf[SPI_NOR_XFER_SZ];

/*!
 * Query the Atmel flash ID
 * Parameter:
 *     data: buffer to store the ID queried
 * Return:
 *     SUCCESS on success, otherwise FAIL
 */
int spi_nor_query_atmel(uint8_t * data)
{
    /* query id */
    spi_nor_tx_buf[3] = JEDEC_ID; // byte3 is the 1st to shift out
    //Read ID get 20 bytes repsonse
    if (ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf, 20 * 8) == FALSE) {
    	return FAIL;
    }

    /* Big-endian */
    data[0] = spi_nor_rx_buf[0];
    data[1] = spi_nor_rx_buf[1];
    data[2] = spi_nor_rx_buf[2];
    data[3] = spi_nor_rx_buf[3];

    return SUCCESS;
}

/* read atmel status register */
static int spi_nor_status_atmel(void)
{
    spi_nor_tx_buf[1] = STAT_READ;
 
    /* Send command */
    if (ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf, 2 * 8) == FALSE) {
        printf("Atmel Error - get status.\n");
        return FAIL;
    }

    return  spi_nor_rx_buf[0];
}

/* spi nor write */
int spi_nor_write_atmel(uint32_t addr, uint8_t * data, int length)
{
    uint32_t d_addr = (uint32_t) addr;
    uint8_t *s_buf = (uint8_t *) data;
    uint32_t final_addr = 0;
    int page_size = 512, trans_bytes = 0, buf_ptr = 0, bytes_sent = 0, byte_sent_per_iter = 0;
    int page_no = 0, buf_addr = 0, page_off = 0, i = 0, j = 0, k = 0, fifo_size = 32;
    int remain_len = 0, len = length;

    /* Read the status register to get the Page size */
    if (spi_nor_status_atmel() & STAT_PG_SZ) {
        page_size = 512;
    } else {
        printf("Unsupported Page Size of 528 bytes\n");
        // reprogram the page size to be 512 bytess
        spi_nor_tx_buf[0] = CONFIG_REG4;
        spi_nor_tx_buf[1] = CONFIG_REG3;
        spi_nor_tx_buf[2] = CONFIG_REG2;
        spi_nor_tx_buf[3] = CONFIG_REG1;

        if (ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf, 4 * 8) != 0) {
            printf("Error: %s(): %d\n", __FUNCTION__, __LINE__);
            return -1;
        }

        while (!(spi_nor_status_atmel() & STAT_BUSY)) {
        }

        printf("Reprogrammed the Page Size to be 512 bytes\n");
        printf("Please Power Cycle the board for the change to take effect\n");
        return 1;
    }

    /* Due to the way CSPI operates send data less that 4 bytes in a different manner */
    remain_len = len % 4;

    if (remain_len)
        len -= remain_len;

    while (1) {
        page_no = d_addr / page_size;
        page_off = (d_addr % page_size);

        /* Get the offset within the page if address is not page-aligned */
        if (page_off) {
            if (page_no == 0) {
                buf_addr = d_addr;
            } else {
                buf_addr = page_off;
            }

            trans_bytes = page_size - buf_addr;
        } else {
            buf_addr = 0;
            trans_bytes = page_size;
        }

        if (len <= 0)
            break;

        if (trans_bytes > len)
            trans_bytes = len;

        bytes_sent = trans_bytes;

        /* Write the data to the SPI-NOR Buffer first */
        while (trans_bytes > 0) {
            final_addr = (buf_addr & 0x3FF);
            spi_nor_tx_buf[0] = final_addr;
            spi_nor_tx_buf[1] = final_addr >> 8;
            spi_nor_tx_buf[2] = final_addr >> 16;
            spi_nor_tx_buf[3] = BUF1_WR;  /*Opcode */

            /* 4 bytes already used for Opcode & address bytes,
               check to ensure we do not overflow the SPI TX buffer */
            if (trans_bytes > (fifo_size - 4))
                byte_sent_per_iter = fifo_size;
            else
                byte_sent_per_iter = trans_bytes + 4;

            for (i = 4; i < byte_sent_per_iter; i += 4) {
                spi_nor_tx_buf[i + 3] = s_buf[buf_ptr++];
                spi_nor_tx_buf[i + 2] = s_buf[buf_ptr++];
                spi_nor_tx_buf[i + 1] = s_buf[buf_ptr++];
                spi_nor_tx_buf[i] = s_buf[buf_ptr++];
            }

            ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf,
                           byte_sent_per_iter * 8);

            while (!(spi_nor_status_atmel() & STAT_BUSY)) {
            }

            /* Deduct 4 bytes as it is used for Opcode & address bytes */
            trans_bytes -= (byte_sent_per_iter - 4);
            /* Update the destination buffer address */
            buf_addr += (byte_sent_per_iter - 4);
        }

        /* Send the command to write data from the SPI-NOR Buffer to Flash memory */
        if (page_size == 512) {
            final_addr = (page_no & 0x1FFF) << 9;
        } else {
            final_addr = (page_no & 0x1FFF) << 10;
        }

        /* Specify the Page address in Flash where the data should be written to */
        spi_nor_tx_buf[0] = final_addr;
        spi_nor_tx_buf[1] = final_addr >> 8;
        spi_nor_tx_buf[2] = final_addr >> 16;
        spi_nor_tx_buf[3] = BUF1_TO_MEM;  /*Opcode */
        if (ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf, 4 * 8) != 0) {
            printf("Error: %s(%d): failed\n", __FILE__, __LINE__);
            return -1;
        }

        while (!(spi_nor_status_atmel() & STAT_BUSY)) {
        }

        d_addr += bytes_sent;
        len -= bytes_sent;
    }

    if (remain_len) {
        buf_ptr += remain_len;

        /* Write the remaining data bytes first */
        for (i = 0; i < remain_len; i++) {
            spi_nor_tx_buf[i] = s_buf[buf_ptr--];
        }

        /* Write the address bytes next in the same word as the data byte from the next byte */
        for (j = i, k = 0; j < 4; j++, k++) {
            spi_nor_tx_buf[j] = final_addr >> (k * 8);
        }

        /* Write the remaining address bytes in the next word */
        j = 0;
        final_addr = (buf_addr & 0x3FF);

        for (j = 0; k < 3; j++, k++) {
            spi_nor_tx_buf[j] = final_addr >> (k * 8);
        }

        /* Finally the Opcode to write the data to the buffer */
        spi_nor_tx_buf[j] = BUF1_WR;  /*Opcode */

        if (ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf, (remain_len + 4) * 8)
            != 0) {
            printf("Error: %s(%d): failed\n", __FILE__, __LINE__);
            return -1;
        }

        while (!(spi_nor_status_atmel() & STAT_BUSY)) {
        }

        if (page_size == 512) {
            final_addr = (page_no & 0x1FFF) << 9;
        } else {
            final_addr = (page_no & 0x1FFF) << 10;
        }

        spi_nor_tx_buf[0] = final_addr;
        spi_nor_tx_buf[1] = final_addr >> 8;
        spi_nor_tx_buf[2] = final_addr >> 16;
        spi_nor_tx_buf[3] = BUF1_TO_MEM;  /*Opcode */
        if (ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf, 4 * 8) != 0) {
            printf("Error: %s(%d): failed\n", __FILE__, __LINE__);
            return -1;
        }

        while (!(spi_nor_status_atmel() & STAT_BUSY)) {
        }
    }

    return 0;
}

static int atmel_erase_pbs(uint32_t d_addr, int pbs)
{
    uint8_t cmd[3] = { 0x81, 0x50, 0x7c };   //erase page, block, sector

    spi_nor_tx_buf[0] = d_addr;
    spi_nor_tx_buf[1] = d_addr >> 8;
    spi_nor_tx_buf[2] = d_addr >> 16;
    spi_nor_tx_buf[3] = cmd[pbs]; /*Opcode */

    ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf, 4 * 8);

    while (!(spi_nor_status_atmel() & STAT_BUSY)) {
    }

    return 0;
}

static int atmel_erase_chip(void)
{
    *(uint32_t *) spi_nor_tx_buf = 0xc794809a;

    ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf, 4 * 8);

    while (!(spi_nor_status_atmel() & STAT_BUSY)) {
    }

    return 0;
}

/* spi nor erase */
int spi_nor_erase_atmel(uint32_t addr, uint32_t length)
{
    uint32_t page_size = 512, block_size = SZ_4K, sector_size = SZ_64K;
    uint32_t device_size = SZ_64K * 64;  //4MB;
    uint32_t d_addr = 0;
    uint32_t len_left = 0;

    if (length > (device_size - page_size)) {
        /* erase the whole chip */
        atmel_erase_chip();
    } else {
        d_addr = (addr / page_size) * page_size;    //must be page aligned
        len_left = (length / page_size) * page_size;    //must be page aligned

        while (len_left > 0) {
            if ((d_addr % block_size) || (len_left < block_size)) {
                atmel_erase_pbs(d_addr, 0); //erase page
                d_addr += page_size;
                len_left -= page_size;
            } else if ((d_addr % sector_size) || (len_left < sector_size)) {
                atmel_erase_pbs(d_addr, 1); //erase block
                d_addr += block_size;
                len_left -= block_size;
            } else {
                atmel_erase_pbs(d_addr, 2); //erase sector
                d_addr += sector_size;
                len_left -= sector_size;
            }
        }
    }

    return 0;
}

int spi_nor_read_atmel(void *src, void *dest, int len)
{
    unsigned int *cmd = (unsigned int *)spi_nor_tx_buf;
    unsigned int max_rx_sz = 32 - 4;    // max rx bytes per burst
    unsigned char *d_buf = (unsigned char *)dest;
    unsigned char *s_buf;
    int i;

    printf("%s(from flash=%p to ram=%p len=0x%x)\n", __FUNCTION__, src, dest, len);

    if (len == 0)
        return 0;

    *cmd = (READ << 24) | ((unsigned int)src & 0x00FFFFFF);

    while (1) {
        if (len == 0) {
            return 0;
        }

        if (len < max_rx_sz) {
            printf("last read len=0x%x\n", len);

            // deal with the last read
            if (ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf, (len + 4) * 8) !=
                0) {
                printf("Error: %s(%d): failed\n", __FILE__, __LINE__);
                return TRANS_FAIL;
            }

            s_buf = spi_nor_rx_buf + 4;   // throw away 4 bytes (5th received bytes is real)
            // now adjust the endianness
            for (i = len; i >= 0; i -= 4, s_buf += 4) {
                if (i < 4) {
                    if (i == 1) {
                        *d_buf = s_buf[0];
                    } else if (i == 2) {
                        *d_buf++ = s_buf[1];
                        *d_buf++ = s_buf[0];
                    } else if (i == 3) {
                        *d_buf++ = s_buf[2];
                        *d_buf++ = s_buf[1];
                        *d_buf++ = s_buf[0];
                    }

                    return 0;
                }
                // copy 4 bytes
                *d_buf++ = s_buf[3];
                *d_buf++ = s_buf[2];
                *d_buf++ = s_buf[1];
                *d_buf++ = s_buf[0];
            }
        }
        // now grab max_rx_sz data (+4 is needed due to 4-throw away bytes
        if (ecspi_xfer(dev_spi_nor, spi_nor_tx_buf, spi_nor_rx_buf, (max_rx_sz + 4) * 8) !=
            0) {
            printf("Error: %s(%d): failed\n", __FILE__, __LINE__);
            return TRANS_FAIL;
        }

        s_buf = spi_nor_rx_buf + 4;   // throw away 4 bytes (5th received bytes is real)
        // now adjust the endianness
        for (i = 0; i < max_rx_sz; i += 4, s_buf += 4) {
            *d_buf++ = s_buf[3];
            *d_buf++ = s_buf[2];
            *d_buf++ = s_buf[1];
            *d_buf++ = s_buf[0];
        }

        *cmd += max_rx_sz;      // increase # of bytes in NOR address as cmd == g_tx_buf
        len -= max_rx_sz;       // # of bytes left

        //printf("d_buf=%p, g_rx_buf=%p, len=0x%x\n", d_buf, g_spi_nor_rx_buf, len);
    }
}
