/*!
    \file    gd32f20x_hau.h
    \brief   definitions for the HAU

    \version 2015-07-15, V1.0.0, firmware for GD32F20x
    \version 2017-06-05, V2.0.0, firmware for GD32F20x
    \version 2018-10-31, V2.1.0, firmware for GD32F20x
    \version 2020-09-30, V2.2.0, firmware for GD32F20x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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

#ifndef GD32F20X_HAU_H
#define GD32F20X_HAU_H

#include "gd32f20x.h"

/* HAU definitions */
#define HAU                        HAU_BASE

/* registers definitions */
#define HAU_CTL                    REG32(HAU + 0x00U)        /*!< control register  */
#define HAU_DI                     REG32(HAU + 0x04U)        /*!< data input register */
#define HAU_CFG                    REG32(HAU + 0x08U)        /*!< configuration register */
#define HAU_DO0                    REG32(HAU + 0x0CU)        /*!< data output register 0 */
#define HAU_DO1                    REG32(HAU + 0x10U)        /*!< data output register 1 */
#define HAU_DO2                    REG32(HAU + 0x14U)        /*!< data output register 2 */
#define HAU_DO3                    REG32(HAU + 0x18U)        /*!< data output register 3 */
#define HAU_DO4                    REG32(HAU + 0x1CU)        /*!< data output register 4 */
#define HAU_DO5                    REG32(HAU + 0x324U)       /*!< data output register 5 */
#define HAU_DO6                    REG32(HAU + 0x328U)       /*!< data output register 6 */
#define HAU_DO7                    REG32(HAU + 0x32CU)       /*!< data output register 7 */
#define HAU_INTEN                  REG32(HAU + 0x20U)        /*!< interrupt enable register */
#define HAU_STAT                   REG32(HAU + 0x24U)        /*!< status and interrupt flag register */

/* bits definitions */
/* HAU_CTL */
#define HAU_CTL_START              BIT(2)                    /*!< set to 1 to reset the HAU processor core, so that it is ready to start the digest calculation */
#define HAU_CTL_DMAE               BIT(3)                    /*!< DMA enable */
#define HAU_CTL_DATAM              BITS(4,5)                 /*!< data type mode */
#define HAU_CTL_HMS                BIT(6)                    /*!< HAU mode selection */
#define HAU_CTL_ALGM_0             BIT(7)                    /*!< algorithm selection bit 0 */
#define HAU_CTL_NWIF               BITS(8,11)                /*!< number of words in the input FIFO */
#define HAU_CTL_DINE               BIT(12)                   /*!< DI register not empty */
#define HAU_CTL_MDS                BIT(13)                   /*!< multiple DMA selection */
#define HAU_CTL_KLM                BIT(16)                   /*!< key length mode */
#define HAU_CTL_ALGM_1             BIT(18)                   /*!< algorithm selection bit 1 */

/* HAU_DI */
#define HAU_DI_DI                  BITS(0,31)                /*!< message data input */

/* HAU_CFG */
#define HAU_CFG_VBL                BITS(0,4)                 /*!< valid bits length in the last word */
#define HAU_CFG_CALEN              BIT(8)                    /*!< digest calculation enable */

/* HAU_DOx x=0..7 */
#define HAU_DOX_DOX                BITS(0,31)                /*!< message digest result of hash algorithm */

/* HAU_INTEN */
#define HAU_INTEN_DIIE             BIT(0)                    /*!< data input interrupt enable */
#define HAU_INTEN_CCIE             BIT(1)                    /*!< calculation completion interrupt enable */

/* HAU_STAT */
#define HAU_STAT_DINT              BIT(0)                    /*!< data input interrupt flag */
#define HAU_STAT_CINT              BIT(1)                    /*!< digest calculation completion interrupt flag */
#define HAU_STAT_DMAS              BIT(2)                    /*!< DMA status */
#define HAU_STAT_BUSY              BIT(3)                    /*!< busy bit */

/* constants definitions */
/* structure for initialization of the hau */
typedef struct
{
    uint32_t algo;      /*!< algorithm selection */
    uint32_t mode;      /*!< HAU mode selection */
    uint32_t datatype;  /*!< data type mode */
    uint32_t keytype;   /*!< key length mode */
}hau_init_parameter_struct;

/* structure for message digest result of the hau */
typedef struct
{
    uint32_t out[8];     /* message digest result 0-7 */
}hau_digest_parameter_struct;

/* hau_ctl register value */
#define HAU_ALGO_SHA1                     ((uint32_t)0x00000000U)                        /*!< HAU function is SHA1 */
#define HAU_ALGO_SHA224                   HAU_CTL_ALGM_1                                 /*!< HAU function is SHA224 */
#define HAU_ALGO_SHA256                   (HAU_CTL_ALGM_1 | HAU_CTL_ALGM_0)              /*!< HAU function is SHA256 */
#define HAU_ALGO_MD5                      HAU_CTL_ALGM_0                                 /*!< HAU function is MD5 */

#define HAU_MODE_HASH                     ((uint32_t)0x00000000U)                        /*!< HAU mode is HASH */
#define HAU_MODE_HMAC                     HAU_CTL_HMS                                    /*!< HAU mode is HMAC */

#define CTL_DATAM_1(regval)               (BITS(4,5) & ((uint32_t)(regval) << 4))        /*!< write value to HAU_CTL_DATAM bit field */
#define HAU_SWAPPING_32BIT                CTL_DATAM_1(0)                                 /*!< no swapping */
#define HAU_SWAPPING_16BIT                CTL_DATAM_1(1)                                 /*!< half-word swapping */
#define HAU_SWAPPING_8BIT                 CTL_DATAM_1(2)                                 /*!< bytes swapping */
#define HAU_SWAPPING_1BIT                 CTL_DATAM_1(3)                                 /*!< bit swapping */

#define HAU_KEY_SHORTER_64                ((uint32_t)0x00000000U)                        /*!< HMAC key is <= 64 bytes */
#define HAU_KEY_LONGGER_64                HAU_CTL_KLM                                    /*!< HMAC key is > 64 bytes  */

#define GET_CTL_NWIF(regval)              GET_BITS((regval),8,11)                        /*!< get value of HAU_CTL_NWIF bit field */

#define SINGLE_DMA_AUTO_DIGEST            ((uint32_t)0x00000000U)                        /*!< message padding and message digest calculation at the end of a DMA transfer */
#define MULTIPLE_DMA_NO_DIGEST            HAU_CTL_MDS                                    /*!< multiple DMA transfers needed and CALEN bit is not automatically set at the end of a DMA transfer */

/* hau_cfg register value */
#define CFG_VBL(regval)                   (BITS(0,4) & ((regval) << 0))                  /*!< write value to HAU_CFG_VBL bit field */

/* hau_inten register value */
#define HAU_INT_DATA_INPUT                HAU_INTEN_DIIE                                 /*!< a new block can be entered into the IN buffer */
#define HAU_INT_CALCULATION_COMPLETE      HAU_INTEN_CCIE                                 /*!< calculation complete */

#define HAU_FLAG_DATA_INPUT               HAU_STAT_DINT                                  /*!< there is enough space (16 bytes) in the input FIFO */
#define HAU_FLAG_CALCULATION_COMPLETE     HAU_STAT_CINT                                  /*!< digest calculation is completed */
#define HAU_FLAG_DMA                      HAU_STAT_DMAS                                  /*!< DMA is enabled (DMAE =1) or a transfer is processing */
#define HAU_FLAG_BUSY                     HAU_STAT_BUSY                                  /*!< data block is in process */
#define HAU_FLAG_INFIFO_NO_EMPTY          HAU_CTL_DINE                                   /*!< the input FIFO is not empty */

#define HAU_INT_FLAG_DATA_INPUT           HAU_STAT_DINT                                  /*!< there is enough space (16 bytes) in the input FIFO */
#define HAU_INT_FLAG_CALCULATION_COMPLETE HAU_STAT_CINT                                  /*!< digest calculation is completed */

/* function declarations */
/* initialization functions */
/* reset the HAU peripheral */
void hau_deinit(void);
/* initialize the HAU peripheral parameters */
void hau_init(hau_init_parameter_struct* initpara);
/* initialize the structure hau_initpara */
void hau_init_parameter_init(hau_init_parameter_struct* initpara);
/* reset the HAU processor core */
void hau_reset(void);
/* configure the number of valid bits in last word of the message */
void hau_last_word_validbits_num_config(uint32_t valid_num);
/* write data to the IN FIFO */
void hau_data_write(uint32_t data);
/* return the number of words already written into the IN FIFO */
uint32_t hau_infifo_words_num_get(void);
/* read the message digest result */
void hau_digest_read(hau_digest_parameter_struct* digestpara);
/* enable digest calculation */
void hau_digest_calculation_enable(void);
/* configure single or multiple DMA is used, and digest calculation at the end of a DMA transfer or not */
void hau_multiple_single_dma_config(uint32_t multi_single);
/* enable the HAU DMA interface */
void hau_dma_enable(void);
/* disable the HAU DMA interface */
void hau_dma_disable(void);

/* calculate digest in HASH mode */
/* calculate digest using SHA1 in HASH mode */
ErrStatus hau_hash_sha_1(uint8_t *input, uint32_t in_length, uint8_t output[20]);
/* calculate digest using SHA1 in HMAC mode */
ErrStatus hau_hmac_sha_1(uint8_t *key, uint32_t keysize, uint8_t *input, uint32_t in_length, uint8_t output[20]);
/* calculate digest using SHA224 in HASH mode */
ErrStatus hau_hash_sha_224(uint8_t *input, uint32_t in_length, uint8_t output[28]);
/* calculate digest using SHA224 in HMAC mode */
ErrStatus hau_hmac_sha_224(uint8_t *key, uint32_t keysize, uint8_t *input, uint32_t in_length, uint8_t output[28]);
/* calculate digest using SHA256 in HASH mode */
ErrStatus hau_hash_sha_256(uint8_t *input, uint32_t in_length, uint8_t output[32]);
/* calculate digest using SHA256 in HMAC mode */
ErrStatus hau_hmac_sha_256(uint8_t *key, uint32_t keysize, uint8_t *input, uint32_t in_length, uint8_t output[32]);
/* calculate digest using MD5 in HASH mode */
ErrStatus hau_hash_md5(uint8_t *input, uint32_t in_length, uint8_t output[16]);
/* calculate digest using MD5 in HMAC mode */
ErrStatus hau_hmac_md5(uint8_t *key, uint32_t keysize, uint8_t *input, uint32_t in_length, uint8_t output[16]);

/* interrupt & flag functions */
/* get the HAU flag status */
FlagStatus hau_flag_get(uint32_t flag);
/* clear the HAU flag status */
void hau_flag_clear(uint32_t flag);
/* enable the HAU interrupts */
void hau_interrupt_enable(uint32_t interrupt);
/* disable the HAU interrupts */
void hau_interrupt_disable(uint32_t interrupt);
/* get the HAU interrupt flag status */
FlagStatus hau_interrupt_flag_get(uint32_t int_flag);
/* clear the HAU interrupt flag status */
void hau_interrupt_flag_clear(uint32_t int_flag);

#endif /*GD32F20X_HAU_H */
