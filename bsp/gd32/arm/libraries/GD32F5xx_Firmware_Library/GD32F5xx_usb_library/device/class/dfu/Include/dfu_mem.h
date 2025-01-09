/*!
    \file    dfu_mem.h
    \brief   USB DFU device media access layer header file

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef DFU_MEM_H
#define DFU_MEM_H

#include "usb_conf.h"

#define _1ST_BYTE(x)              (uint8_t)((x) & 0xFFU)                /*!< addressing cycle 1st byte */
#define _2ND_BYTE(x)              (uint8_t)(((x) & 0xFF00U) >> 8)       /*!< addressing cycle 2nd byte */
#define _3RD_BYTE(x)              (uint8_t)(((x) & 0xFF0000U) >> 16)    /*!< addressing cycle 3rd byte */

#define POLLING_TIMEOUT_SET(x)    buffer[0] = _1ST_BYTE(x); \
                                  buffer[1] = _2ND_BYTE(x); \
                                  buffer[2] = _3RD_BYTE(x);

/* USB DFU property structure */
typedef struct _dfu_mem_prop {
    const uint8_t *pstr_desc;     /*!< pointer to the string descriptor */

    uint8_t (*mem_init)(void);
    uint8_t (*mem_deinit)(void);
    uint8_t (*mem_erase)(uint32_t addr);
    uint8_t (*mem_write)(uint8_t *buf, uint32_t addr, uint32_t len);
    uint8_t *(*mem_read)(uint8_t *buf, uint32_t addr, uint32_t len);
    uint8_t (*mem_checkaddr)(uint32_t addr);

    const uint32_t erase_timeout; /*!< erase memory timeout */
    const uint32_t write_timeout; /*!< write memory timeout */
} dfu_mem_prop;

typedef enum {
    MEM_OK = 0U,  /*!< memory operation succeed */
    MEM_FAIL      /*!< memory operation fail */
} mem_status;

/* function declarations */
/* initialize the memory media */
uint8_t dfu_mem_init(void);
/* deinitialize the memory media */
uint8_t dfu_mem_deinit(void);
/* erase a memory sector */
uint8_t dfu_mem_erase(uint32_t addr);
/* write data to sectors of memory */
uint8_t dfu_mem_write(uint8_t *buf, uint32_t addr, uint32_t len);
/* read data from sectors of memory */
uint8_t *dfu_mem_read(uint8_t *buf, uint32_t addr, uint32_t len);
/* get the status of a given memory and store in buffer */
uint8_t dfu_mem_getstatus(uint32_t addr, uint8_t cmd, uint8_t *buffer);

#endif /* DFU_MEM_H */
