/*!
    \file    gd32e230_crc.h
    \brief   definitions for the CRC
    
    \version 2018-06-19, V1.0.0, firmware for GD32E230
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#ifndef GD32E230_CRC_H
#define GD32E230_CRC_H

#include "gd32e230.h"

/* CRC definitions */
#define CRC                            CRC_BASE

/* registers definitions */
#define CRC_DATA                       REG32((CRC) + 0x00U)            /*!< CRC data register */
#define CRC_FDATA                      REG32((CRC) + 0x04U)            /*!< CRC free data register */
#define CRC_CTL                        REG32((CRC) + 0x08U)            /*!< CRC control register */
#define CRC_IDATA                      REG32((CRC) + 0x10U)            /*!< CRC initialization data register */
#define CRC_POLY                       REG32((CRC) + 0x14U)            /*!< CRC polynomial register */

/* bits definitions */
/* CRC_DATA */
#define CRC_DATA_DATA                  BITS(0,31)                      /*!< CRC data bits */

/* CRC_FDATA */
#define CRC_FDATA_FDATA                BITS(0,7)                       /*!< CRC free data bits */

/* CRC_CTL */
#define CRC_CTL_RST                    BIT(0)                          /*!< CRC reset bit */
#define CRC_CTL_PS                     BITS(3,4)                       /*!< size of polynomial function bits */
#define CRC_CTL_REV_I                  BITS(5,6)                       /*!< input data reverse function bits */
#define CRC_CTL_REV_O                  BIT(7)                          /*!< output data reverse function bit */

/* CRC_INIT */
#define CRC_IDATA_IDATA                BITS(0,31)                      /*!< CRC initialization data bits */

/* CRC_POLY */
#define CRC_POLY_POLY                  BITS(0,31)                      /*!< CRC polynomial value bits */

/* constants definitions */
/* size of polynomial function */
#define CTL_PS(regval)                 (BITS(3, 4) & ((regval) << 3))
#define CRC_CTL_PS_32                  CTL_PS(0)                       /*!< 32-bit polynomial for CRC calculation */
#define CRC_CTL_PS_16                  CTL_PS(1)                       /*!< 16-bit polynomial for CRC calculation */
#define CRC_CTL_PS_8                   CTL_PS(2)                       /*!< 8-bit polynomial for CRC calculation */
#define CRC_CTL_PS_7                   CTL_PS(3)                       /*!< 7-bit polynomial for CRC calculation */

/* input data reverse function */
#define CTL_REV_I(regval)              (BITS(5, 6) & ((regval) << 5))
#define CRC_INPUT_DATA_NOT             CTL_REV_I(0)                    /*!< input data not reverse */
#define CRC_INPUT_DATA_BYTE            CTL_REV_I(1)                    /*!< input data reversed by byte type */
#define CRC_INPUT_DATA_HALFWORD        CTL_REV_I(2)                    /*!< input data reversed by half-word type */
#define CRC_INPUT_DATA_WORD            CTL_REV_I(3)                    /*!< input data reversed by word type */

/* function declarations */
/* deinit CRC calculation unit */
void crc_deinit(void);

/* enable the reverse operation of output data */
void crc_reverse_output_data_enable(void);
/* disable the reverse operation of output data */
void crc_reverse_output_data_disable(void);

/* reset data register to the value of initializaiton data register */
void crc_data_register_reset(void);
/* read the data register  */
uint32_t crc_data_register_read(void);

/* read the free data register */
uint8_t crc_free_data_register_read(void);
/* write the free data register */
void crc_free_data_register_write(uint8_t free_data);

/* write the initial value register */
void crc_init_data_register_write(uint32_t init_data);
/* configure the CRC input data function */
void crc_input_data_reverse_config(uint32_t data_reverse);

/* configure the CRC size of polynomial function */
void crc_polynomial_size_set(uint32_t poly_size);
/* configure the CRC polynomial value function */
void crc_polynomial_set(uint32_t poly);

/* CRC calculate a 32-bit data */
uint32_t crc_single_data_calculate(uint32_t sdata);
/* CRC calculate a 32-bit data array */
uint32_t crc_block_data_calculate(uint32_t array[], uint32_t size);

#endif /* GD32E230_CRC_H */
