/*!
    \file    gd32e50x_sqpi.h
    \brief   definitions for the SQPI

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#ifndef GD32E50X_SQPI_H
#define GD32E50X_SQPI_H

#include "gd32e50x.h"

/* SQPI definitions */
#define SQPI                             SQPI_BASE
/* SQPI registers definitions */
#define SQPI_INIT                        REG32((SQPI) + 0x00000000U)            /*!< SQPI initial register*/
#define SQPI_RCMD                        REG32((SQPI) + 0x00000004U)            /*!< SQPI read command register */
#define SQPI_WCMD                        REG32((SQPI) + 0x00000008U)            /*!< SQPI write command register */
#define SQPI_IDL                         REG32((SQPI) + 0x0000000CU)            /*!< SQPI ID low register */
#define SQPI_IDH                         REG32((SQPI) + 0x00000010U)            /*!< SQPI ID high register */


/* bits definitions */
/* SQPI_INIT */
#define SQPI_INIT_CMDBIT                 BITS(16,17)                            /*!< bit number of SQPI controller command phase */
#define SQPI_INIT_CLKDIV                 BITS(18,23)                            /*!< clock divider for SQPI output clock */
#define SQPI_INIT_ADDRBIT                BITS(24,28)                            /*!< bit number of SPI PSRAM address phase*/
#define SQPI_INIT_IDLEN                  BITS(29,30)                            /*!< external memory ID length */
#define SQPI_INIT_PL                     BIT(31)                                /*!< SQPI read data sample polarity */

/* SQPI_RCMD */
#define SQPI_RCMD_RCMD                   BITS(0,15)                             /*!< SQPI read command for AHB read transfer */
#define SQPI_RCMD_RWAITCYCLE             BITS(16,19)                            /*!< read command waitcycle number */
#define SQPI_RCMD_RMODE                  BITS(20,22)                            /*!< read command mode */
#define SQPI_RCMD_RID                    BIT(31)                                /*!< send read ID command */

/* SQPI_WCMD */
#define SQPI_WCMD_WCMD                   BITS(0,15)                             /*!< SQPI write command for AHB write transfer */
#define SQPI_WCMD_WWAITCYCLE             BITS(16,19)                            /*!< write command waitcycle number */
#define SQPI_WCMD_WMODE                  BITS(20,22)                            /*!< write command mode */
#define SQPI_WCMD_SCMD                   BIT(31)                                /*!< send special command */

/* SQPI_IDL */
#define SQPI_IDL_IDL                     BITS(0,31)                             /*!< ID low register */

/* SQPI_IDH */
#define SQPI_IDH_IDH                     BITS(0,31)                             /*!< ID high register */


/* constants definitions */
/* SQPI parameter struct definitions */
typedef struct
{
    uint32_t polarity;                                                          /*!< SQPI sample polarity*/
    uint32_t id_length;                                                         /*!< external memory ID length */
    uint32_t addr_bit;                                                          /*!< bit number of SPI PSRAM address phase */
    uint32_t clk_div;                                                           /*!< clock divider for SQPI output clock */
    uint32_t cmd_bit;                                                           /*!< bit number of SQPI controller command phase */
}sqpi_parameter_struct;
/* SQPI sample shift */
#define SQPI_SAMPLE_POLARITY_RISING           ((uint32_t)0x00000000U)           /*!< SQPI read data at rising edge */
#define SQPI_SAMPLE_POLARITY_FALLING          (SQPI_INIT_PL)                    /*!< SQPI read data at falling edge */

/* SQPI ID length */
#define INIT_IDLEN(regval)                    (BITS(29,30) & ((uint32_t)(regval) << 29))
#define SQPI_ID_LENGTH_64_BITS                INIT_IDLEN(0)                     /*!< 64 bits ID */
#define SQPI_ID_LENGTH_32_BITS                INIT_IDLEN(1)                     /*!< 32 bits ID */
#define SQPI_ID_LENGTH_16_BITS                INIT_IDLEN(2)                     /*!< 16 bits ID */
#define SQPI_ID_LENGTH_8_BITS                 INIT_IDLEN(3)                     /*!< 8 bits ID */

/* SQPI command bits */
#define INIT_CMDBIT(regval)                   (BITS(16,17) & ((uint32_t)(regval) << 16))
#define SQPI_CMDBIT_4_BITS                    INIT_CMDBIT(0)                    /*!< 4 bits command */
#define SQPI_CMDBIT_8_BITS                    INIT_CMDBIT(1)                    /*!< 8 bits command */
#define SQPI_CMDBIT_16_BITS                   INIT_CMDBIT(2)                    /*!< 16 bits command */

/* SQPI mode */
#define SQPI_MODE(regval)                     (BITS(20,22) & ((uint32_t)(regval) << 20))
#define SQPI_MODE_SSQ                         SQPI_MODE(0)                      /*!< SQPI SSQ mode */
#define SQPI_MODE_SSS                         SQPI_MODE(1)                      /*!< SQPI SSS mode */
#define SQPI_MODE_SQQ                         SQPI_MODE(2)                      /*!< SQPI SQQ mode */
#define SQPI_MODE_QQQ                         SQPI_MODE(3)                      /*!< SQPI QQQ mode */
#define SQPI_MODE_SSD                         SQPI_MODE(4)                      /*!< SQPI SSD mode */
#define SQPI_MODE_SDD                         SQPI_MODE(5)                      /*!< SQPI SDD mode */

/* function declarations */
/* SQPI deinitialization and initialization functions */
/* reset SQPI */
void sqpi_deinit(void);
/* initialize the parameters of SQPI struct with the default values */
void sqpi_struct_para_init(sqpi_parameter_struct* sqpi_struct);
/* initialize SQPI parameter */
void sqpi_init(sqpi_parameter_struct *sqpi_struct);

/* send SQPI read ID command */
void sqpi_read_id_command(void);
/* send SQPI special command */
void sqpi_special_command(void);
/* configure SQPI read command */
void sqpi_read_command_config(uint32_t rmode, uint32_t rwaitcycle, uint32_t rcmd);
/* configure SQPI write command */
void sqpi_write_command_config(uint32_t wmode, uint32_t wwaitcycle, uint32_t wcmd);
/* SQPI receive low ID */
uint32_t sqpi_low_id_receive(void);
/* SQPI receive high ID*/
uint32_t sqpi_high_id_receive(void);

#endif /* GD32E50X_SQPI_H */
