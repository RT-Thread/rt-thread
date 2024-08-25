/*!
    \file    gd32h7xx_rtdec.h
    \brief   definitions for the RTDEC

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
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

#ifndef GD32H7XX_RTDEC_H
#define GD32H7XX_RTDEC_H

#include "gd32h7xx.h"

/* RTDEC definitions */
#define RTDEC0                                          RTDEC_BASE                     /*!<  RTDEC0 bsae address */
#define RTDEC1                                          (RTDEC_BASE + 0x00000400U)     /*!<  RTDEC1 bsae address */
#define RTDEC_AREA0                                     ((uint8_t)0x00U)               /*!<  RTDEC area0 */
#define RTDEC_AREA1                                     ((uint8_t)0x01U)               /*!<  RTDEC area1 */
#define RTDEC_AREA2                                     ((uint8_t)0x02U)               /*!<  RTDEC area2 */
#define RTDEC_AREA3                                     ((uint8_t)0x03U)               /*!<  RTDEC area3 */
#define RTDEC_ARE(rtdecx, rtdec_areax)                  ((rtdecx) + 0x00000030U * (rtdec_areax))

/* registers definitions */
#define RTDEC_ARE_CFG(rtdecx, rtdec_areax)              REG32(RTDEC_ARE((rtdecx), (rtdec_areax)) + 0x00000020U)    /*!< area configuration register */
#define RTDEC_ARE_SADDR(rtdecx, rtdec_areax)            REG32(RTDEC_ARE((rtdecx), (rtdec_areax)) + 0x00000024U)    /*!< area start address register */
#define RTDEC_ARE_EADDR(rtdecx, rtdec_areax)            REG32(RTDEC_ARE((rtdecx), (rtdec_areax)) + 0x00000028U)    /*!< area end address register */
#define RTDEC_ARE_NONCE0(rtdecx, rtdec_areax)           REG32(RTDEC_ARE((rtdecx), (rtdec_areax)) + 0x0000002CU)    /*!< area random number register 0 */
#define RTDEC_ARE_NONCE1(rtdecx, rtdec_areax)           REG32(RTDEC_ARE((rtdecx), (rtdec_areax)) + 0x00000030U)    /*!< area random number register 1 */
#define RTDEC_ARE_KEY0(rtdecx, rtdec_areax)             REG32(RTDEC_ARE((rtdecx), (rtdec_areax)) + 0x00000034U)    /*!< area key register 0 */
#define RTDEC_ARE_KEY1(rtdecx, rtdec_areax)             REG32(RTDEC_ARE((rtdecx), (rtdec_areax)) + 0x00000038U)    /*!< area key register 1 */
#define RTDEC_ARE_KEY2(rtdecx, rtdec_areax)             REG32(RTDEC_ARE((rtdecx), (rtdec_areax)) + 0x0000003CU)    /*!< area key register 2 */
#define RTDEC_ARE_KEY3(rtdecx, rtdec_areax)             REG32(RTDEC_ARE((rtdecx), (rtdec_areax)) + 0x00000040U)    /*!< area key register 3 */
#define RTDEC_INTF(rtdecx)                              REG32((rtdecx) + 0x00000300U)                              /*!< interrupt flag register */
#define RTDEC_INTC(rtdecx)                              REG32((rtdecx) + 0x00000304U)                              /*!< interrupt flag clear register */
#define RTDEC_INTEN(rtdecx)                             REG32((rtdecx) + 0x00000308U)                              /*!< interrupt enable register */

/* bits definitions */
/* RTDEC_AREx_CFG */
#define RTDEC_ARE_EN                   BIT(0)           /*!< area real-time decryption enable bit */
#define RTDEC_ARE_CFG_LK               BIT(1)           /*!< area configure lock bit */
#define RTDEC_ARE_K_LK                 BIT(2)           /*!< area key lock bit */
#define RTDEC_MODE                     BITS(4, 5)       /*!< RTDEC mode bits */
#define RTDEC_ARE_K_CRC                BITS(8, 15)      /*!< 8-bit CRC of area key bits */
#define RTDEC_ARE_FMVER                BITS(16, 31)     /*!< area firmware version bits */

/* RTDEC_AREx_SADDR */
#define RTDEC_ARE_SADDR_SADDR          BITS(0, 31)      /*!< area start address bits */

/* RTDEC_AREx_EADDR */
#define RTDEC_ARE_EADDR_EADDR          BITS(0, 31)      /*!< area end address bits */

/* RTDEC_AREx_NONCE */
#define RTDEC_ARE_NONCE_NONCE          BITS(0, 31)      /*!< area random number address bits */

/* RTDEC_AREx_KEY */
#define RTDEC_ARE_KEY_KEY              BITS(0, 31)      /*!< area key bits */

/* RTDEC_INTF */
#define RTDEC_SECEF                    BIT(0)           /*!< security error interrupt flag */
#define RTDEC_ECONEF                   BIT(1)           /*!< execute-only or execute-never error interrupt flag */
#define RTDEC_KEF                      BIT(2)           /*!< key error interrupt flag */

/* RTDEC_INTEN */
#define RTDEC_SECEIE                   BIT(0)           /*!< enable bit for security error interrupt */
#define RTDEC_ECONEIE                  BIT(1)           /*!< enable bit for execute-only or execute-never error interrupt */
#define RTDEC_KEIE                     BIT(2)           /*!< enable bit for key error interrupt */

/* constants definitions */
/* RTDEC modes definitions */
#define RTDEC_MODE_SEL(regval)         (RTDEC_MODE & ((uint32_t)(regval) << 4U))
#define RTDEC_MODE_CODE_ACCESS         RTDEC_MODE_SEL(0)                                   /*!< only code accesses are decrypted */
#define RTDEC_MODE_DATA_ACCESS         RTDEC_MODE_SEL(1)                                   /*!< only data accesses are decrypted */
#define RTDEC_MODE_BOTH_ACCESS         RTDEC_MODE_SEL(2)                                   /*!< all read accesses are decrypted (code or data) */

/* RTDEC interrupt flag definitions */
#define RTDEC_INT_FLAG_SEC_ERROR       RTDEC_SECEF                                         /*!< bit constant of security error interrupt flag */
#define RTDEC_INT_FLAG_MODE_ERROR      RTDEC_ECONEF                                        /*!< bit constant of execute-only or execute-never error interrupt flag */
#define RTDEC_INT_FLAG_KEY_ERROR       RTDEC_KEF                                           /*!< bit constant of key error interrupt flag */

/* RTDEC interrupt enable definitions */
#define RTDEC_INT_SEC                  RTDEC_SECEIE                                        /*!< enable bit for security error interrupt */
#define RTDEC_INT_MODE                 RTDEC_ECONEIE                                       /*!< enable bit for execute-only or execute-never error interrupt */
#define RTDEC_INT_KEY                  RTDEC_KEIE                                          /*!< enable bit for key error interrupt */

/* RTDEC flag definitions */
#define RTDEC_FLAG_SEC_ERROR           RTDEC_SECEF                                         /*!< bit constant of security error flag */
#define RTDEC_FLAG_MODE_ERROR          RTDEC_ECONEF                                        /*!< bit constant of execute-only or execute-never error flag */
#define RTDEC_FLAG_KEY_ERROR           RTDEC_KEF                                           /*!< bit constant of key error flag */

/* structure for rtdec initialization parameter */
typedef struct {
    uint8_t access_mode;                    /*!< area access mode */
    uint8_t key_crc;                        /*!< key CRC value */
    uint16_t fw_version;                    /*!< area firmware version */
    uint32_t *key;                          /*!< area key bits */
    uint32_t *nonce;                        /*!< area nonce bits */
    uint32_t start_addr;                    /*!< area start address */
    uint32_t end_addr;                      /*!< area end address */
} rtdec_parameter_struct;

/* function declarations */
/* initialization functions */
/* reset RTDEC */
void rtdec_deinit(uint32_t rtdec_periph);
/* initialize the parameters of RTDEC struct with default values */
void rtdec_struct_para_init(rtdec_parameter_struct* rtdec_struct);
/* initialize RTDEC */
ErrStatus rtdec_init(uint32_t rtdec_periph, uint32_t rtdec_area, rtdec_parameter_struct *rtdec_struct);
/* configure RTDEC area data attribute */
void rtdec_config(uint32_t rtdec_periph, uint32_t rtdec_area, uint8_t access_mode, uint16_t firmware_version);
/* configure RTDEC key or register lock */
void rtdec_lock(uint32_t rtdec_periph, uint32_t rtdec_area, uint32_t lock_type);
/* initialize RTDEC area address */
void rtdec_addr_init(uint32_t rtdec_periph, uint32_t rtdec_area, uint32_t saddr, uint32_t eaddr);
/* initialize RTDEC nonce, nonce follows little endian format */
void rtdec_nonce_init(uint32_t rtdec_periph, uint32_t rtdec_area, uint32_t *nonce);
/* initialize RTDEC key, key follows little endian format */
void rtdec_key_init(uint32_t rtdec_periph, uint32_t rtdec_area, uint32_t *key);
/* get CRC value of RTDEC key data */
uint8_t rtdec_key_crc_get(uint32_t rtdec_periph, uint32_t rtdec_area);
/* enable RTDEC area */
void rtdec_enable(uint32_t rtdec_periph, uint32_t rtdec_area);
/* disable RTDEC area */
void rtdec_disable(uint32_t rtdec_periph, uint32_t rtdec_area);

/* flag & interrupt functions */
/* get RTDEC error flag */
FlagStatus rtdec_flag_get(uint32_t rtdec_periph, uint32_t flag);
/* clear RTDEC error flag */
void rtdec_flag_clear(uint32_t rtdec_periph, uint32_t flag);
/* enable RTDEC interrupt */
void rtdec_interrupt_enable(uint32_t rtdec_periph, uint32_t interrupt);
/* disable RTDEC interrupt */
void rtdec_interrupt_disable(uint32_t rtdec_periph, uint32_t interrupt);
/* get RTDEC interrupt flag */
FlagStatus rtdec_interrupt_flag_get(uint32_t rtdec_periph, uint32_t int_flag);
/* clear RTDEC interrupt flag */
void rtdec_interrupt_flag_clear(uint32_t rtdec_periph, uint32_t int_flag);

#endif /* GD32H7XX_RTDEC_H */
