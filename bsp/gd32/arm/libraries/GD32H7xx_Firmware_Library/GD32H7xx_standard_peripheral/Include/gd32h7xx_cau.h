/*!
    \file    gd32h7xx_cau.h
    \brief   definitions for the CAU

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

#ifndef GD32H7XX_CAU_H
#define GD32H7XX_CAU_H

#include "gd32h7xx.h"

/* CAU definitions */
#define CAU                        CAU_BASE                                           /*!< CAU base address */

/* registers definitions */
#define CAU_CTL                    REG32(CAU + 0x00000000U)                           /*!< control register  */
#define CAU_STAT0                  REG32(CAU + 0x00000004U)                           /*!< status register 0 */
#define CAU_DI                     REG32(CAU + 0x00000008U)                           /*!< data input register */
#define CAU_DO                     REG32(CAU + 0x0000000CU)                           /*!< data output register */
#define CAU_DMAEN                  REG32(CAU + 0x00000010U)                           /*!< DMA enable register */
#define CAU_INTEN                  REG32(CAU + 0x00000014U)                           /*!< interrupt enable register */
#define CAU_STAT1                  REG32(CAU + 0x00000018U)                           /*!< status register 1 */
#define CAU_INTF                   REG32(CAU + 0x0000001CU)                           /*!< interrupt flag register */
#define CAU_KEY0H                  REG32(CAU + 0x00000020U)                           /*!< key 0 high register */
#define CAU_KEY0L                  REG32(CAU + 0x00000024U)                           /*!< key 0 low register */
#define CAU_KEY1H                  REG32(CAU + 0x00000028U)                           /*!< key 1 high register */
#define CAU_KEY1L                  REG32(CAU + 0x0000002CU)                           /*!< key 1 low register */
#define CAU_KEY2H                  REG32(CAU + 0x00000030U)                           /*!< key 2 high register */
#define CAU_KEY2L                  REG32(CAU + 0x00000034U)                           /*!< key 2 low register */
#define CAU_KEY3H                  REG32(CAU + 0x00000038U)                           /*!< key 3 high register */
#define CAU_KEY3L                  REG32(CAU + 0x0000003CU)                           /*!< key 3 low register */
#define CAU_IV0H                   REG32(CAU + 0x00000040U)                           /*!< initial vector 0 high register */
#define CAU_IV0L                   REG32(CAU + 0x00000044U)                           /*!< initial vector 0 low register */
#define CAU_IV1H                   REG32(CAU + 0x00000048U)                           /*!< initial vector 1 high register */
#define CAU_IV1L                   REG32(CAU + 0x0000004CU)                           /*!< initial vector 1 low register */
#define CAU_GCMCCMCTXSx(x)         REG32(CAU + 0x00000050U + (uint32_t)(4U * (x)))    /*!< GCM or CCM mode context switch register, x = 0...7 */
#define CAU_GCMCTXSx(x)            REG32(CAU + 0x00000070U + (uint32_t)(4U * (x)))    /*!< GCM mode context switch register, x = 0...7 */

/* bits definitions */
/* CAU_CTL */
#define CAU_CTL_KEY_SEL            BIT(0)                                             /*!< key select */
#define CAU_CTL_CAUDIR             BIT(2)                                             /*!< algorithm direction */
#define CAU_CTL_ALGM               (BITS(3,5) | BIT(19))                              /*!< cryptographic algorithm mode */
#define CAU_CTL_DATAM              BITS(6,7)                                          /*!< data swapping selection */
#define CAU_CTL_KEYM               BITS(8,9)                                          /*!< key length selection when aes mode */
#define CAU_CTL_FFLUSH             BIT(14)                                            /*!< FIFO flush */
#define CAU_CTL_CAUEN              BIT(15)                                            /*!< cryptographic module enable */
#define CAU_CTL_GCM_CCMPH          BITS(16,17)                                        /*!< GCM CCM phase */
#define CAU_CTL_NBPILB             BITS(20,23)                                        /*!< number of bytes padding in last block */

/* CAU_STAT0 */
#define CAU_STAT0_IEM              BIT(0)                                             /*!< IN FIFO empty flag */
#define CAU_STAT0_INF              BIT(1)                                             /*!< IN FIFO not full flag */
#define CAU_STAT0_ONE              BIT(2)                                             /*!< OUT FIFO not empty flag */
#define CAU_STAT0_OFU              BIT(3)                                             /*!< OUT FIFO full flag */
#define CAU_STAT0_BUSY             BIT(4)                                             /*!< busy flag */

/* CAU_DI */
#define CAU_DI_DI                  BITS(0,31)                                         /*!< data input */

/* CAU_DO */
#define CAU_DO_DO                  BITS(0,31)                                         /*!< data output */

/* CAU_DMAEN */
#define CAU_DMAEN_DMAIEN           BIT(0)                                             /*!< IN FIFO DMA enable */
#define CAU_DMAEN_DMAOEN           BIT(1)                                             /*!< OUT FIFO DMA enable */

/* CAU_INTEN */
#define CAU_INTEN_IINTEN           BIT(0)                                             /*!< IN FIFO interrupt enable */
#define CAU_INTEN_OINTEN           BIT(1)                                             /*!< OUT FIFO interrupt enable */

/* CAU_STAT1 */
#define CAU_STAT1_ISTA             BIT(0)                                             /*!< flag set when there is less than 4 words in IN FIFO */
#define CAU_STAT1_OSTA             BIT(1)                                             /*!< flag set when there is one or more word in OUT FIFO */

/* CAU_INTF */
#define CAU_INTF_IINTF             BIT(0)                                             /*!< IN FIFO interrupt flag */
#define CAU_INTF_OINTF             BIT(1)                                             /*!< OUT FIFO interrupt flag */

/* CAU_KEYxH x=0..3 */
#define CAU_KEYXH_KEYXH            BITS(0,31)                                         /*!< the key for des, tdes, aes */

/* CAU_KEYxL x=0..3 */
#define CAU_KEYXL_KEYXL            BITS(0,31)                                         /*!< the key for des, tdes, aes */

/* CAU_IVxH x=0..1 */
#define CAU_IVXH_IVXH              BITS(0,31)                                         /*!< the initialization vector for des, tdes, aes */

/* CAU_IVxL x=0..1 */
#define CAU_IVXL_IVXL              BITS(0,31)                                         /*!< the initialization vector for des, tdes, aes */

/* constants definitions */
/* structure for keys initialization of the cau */
typedef struct {
    uint32_t key_0_high;   /*!< key 0 high */
    uint32_t key_0_low;    /*!< key 0 low  */
    uint32_t key_1_high;   /*!< key 1 high */
    uint32_t key_1_low;    /*!< key 1 low  */
    uint32_t key_2_high;   /*!< key 2 high */
    uint32_t key_2_low;    /*!< key 2 low  */
    uint32_t key_3_high;   /*!< key 3 high */
    uint32_t key_3_low;    /*!< key 3 low  */
} cau_key_parameter_struct;

/* structure for vectors initialization of the cau */
typedef struct {
    uint32_t iv_0_high;    /*!< init vector 0 high */
    uint32_t iv_0_low;     /*!< init vector 0 low  */
    uint32_t iv_1_high;    /*!< init vector 1 high */
    uint32_t iv_1_low;     /*!< init vector 1 low  */
} cau_iv_parameter_struct;

/* structure for cau context swapping */
typedef struct {
    uint32_t ctl_config;     /*!< current configuration */
    uint32_t iv_0_high;      /*!< init vector 0 high */
    uint32_t iv_0_low;       /*!< init vector 0 low  */
    uint32_t iv_1_high;      /*!< init vector 1 high */
    uint32_t iv_1_low;       /*!< init vector 1 low  */
    uint32_t key_0_high;     /*!< key 0 high */
    uint32_t key_0_low;      /*!< key 0 low  */
    uint32_t key_1_high;     /*!< key 1 high */
    uint32_t key_1_low;      /*!< key 1 low  */
    uint32_t key_2_high;     /*!< key 2 high */
    uint32_t key_2_low;      /*!< key 2 low  */
    uint32_t key_3_high;     /*!< key 3 high */
    uint32_t key_3_low;      /*!< key 3 low  */
    uint32_t gcmccmctxs[8];  /*!< GCM or CCM mode context switch */
    uint32_t gcmctxs[8];     /*!< GCM mode context switch */
} cau_context_parameter_struct;

/* structure for encrypt and decrypt parameters */
typedef struct {
    uint32_t alg_dir;      /*!< algorithm directory */
    uint8_t *key;          /*!< key */
    uint32_t key_size;     /*!< key size in bytes */
    uint8_t *iv;           /*!< initialization vector */
    uint32_t iv_size;      /*!< iv size in bytes */
    uint8_t *input;        /*!< input data */
    uint32_t in_length;    /*!< input data length in bytes */
    uint8_t *aad;          /*!< additional authentication data */
    uint32_t aad_size;     /*!< aad size */
} cau_parameter_struct;

/* cau_ctl register value */
#define CAU_ENCRYPT                 ((uint32_t)0x00000000U)                     /*!< encrypt */
#define CAU_DECRYPT                 CAU_CTL_CAUDIR                              /*!< decrypt */

#define CTL_ALGM(regval)            ((BITS(3,5) & ((uint32_t)(regval) << 3U)) | \
                                     (BIT(19) & ((uint32_t)(regval) << 16U)))   /*!< write value to CAU_CTL_ALGM bit field */
#define CAU_MODE_TDES_ECB           CTL_ALGM(0)                                 /*!< TDES-ECB (3DES Electronic codebook) */
#define CAU_MODE_TDES_CBC           CTL_ALGM(1)                                 /*!< TDES-CBC (3DES Cipher block chaining) */
#define CAU_MODE_DES_ECB            CTL_ALGM(2)                                 /*!< DES-ECB (simple DES Electronic codebook) */
#define CAU_MODE_DES_CBC            CTL_ALGM(3)                                 /*!< DES-CBC (simple DES Cipher block chaining) */
#define CAU_MODE_AES_ECB            CTL_ALGM(4)                                 /*!< AES-ECB (AES Electronic codebook) */
#define CAU_MODE_AES_CBC            CTL_ALGM(5)                                 /*!< AES-CBC (AES Cipher block chaining) */
#define CAU_MODE_AES_CTR            CTL_ALGM(6)                                 /*!< AES-CTR (AES counter mode) */
#define CAU_MODE_AES_KEY            CTL_ALGM(7)                                 /*!< AES decryption key preparation mode */
#define CAU_MODE_AES_GCM            CTL_ALGM(8)                                 /*!< AES-GCM (AES Galois/counter mode) */
#define CAU_MODE_AES_CCM            CTL_ALGM(9)                                 /*!< AES-CCM (AES combined cipher machine mode) */
#define CAU_MODE_AES_CFB            CTL_ALGM(10)                                /*!< AES-CFB (cipher feedback mode) */
#define CAU_MODE_AES_OFB            CTL_ALGM(11)                                /*!< AES-OFB (output feedback mode) */

#define CTL_DATAM(regval)           (BITS(6,7) & ((uint32_t)(regval) << 6U))    /*!< write value to CAU_CTL_DATAM bit field */
#define CAU_SWAPPING_32BIT          CTL_DATAM(0)                                /*!< no swapping */
#define CAU_SWAPPING_16BIT          CTL_DATAM(1)                                /*!< half-word swapping */
#define CAU_SWAPPING_8BIT           CTL_DATAM(2)                                /*!< bytes swapping */
#define CAU_SWAPPING_1BIT           CTL_DATAM(3)                                /*!< bit swapping */

#define CAU_KEY                     0x00000000U                                 /*!< use the key from CAU register */
#define CAU_EFUSE_KEY               0x00000001U                                 /*!< use the key from EFUSE */

#define CTL_KEYM(regval)            (BITS(8,9) & ((uint32_t)(regval) << 8U))    /*!< write value to CAU_CTL_KEYM bit field */
#define CAU_KEYSIZE_128BIT          CTL_KEYM(0)                                 /*!< 128 bit key length */
#define CAU_KEYSIZE_192BIT          CTL_KEYM(1)                                 /*!< 192 bit key length */
#define CAU_KEYSIZE_256BIT          CTL_KEYM(2)                                 /*!< 256 bit key length */

#define CTL_GCM_CCMPH(regval)       (BITS(16,17) & ((uint32_t)(regval) << 16U)) /*!< write value to CAU_CTL_GCM_CCMPH bit field */
#define CAU_PREPARE_PHASE           CTL_GCM_CCMPH(0)                            /*!< prepare phase */
#define CAU_AAD_PHASE               CTL_GCM_CCMPH(1)                            /*!< AAD phase */
#define CAU_ENCRYPT_DECRYPT_PHASE   CTL_GCM_CCMPH(2)                            /*!< encryption/decryption phase */
#define CAU_TAG_PHASE               CTL_GCM_CCMPH(3)                            /*!< tag phase */

#define CAU_PADDING_BYTES(regval)   (BITS(20, 23) & ((uint32_t)(regval) << 20U))

/* cau_stat0 register value */
#define CAU_FLAG_INFIFO_EMPTY       CAU_STAT0_IEM                               /*!< IN FIFO empty */
#define CAU_FLAG_INFIFO_NO_FULL     CAU_STAT0_INF                               /*!< IN FIFO is not full */
#define CAU_FLAG_OUTFIFO_NO_EMPTY   CAU_STAT0_ONE                               /*!< OUT FIFO not empty */
#define CAU_FLAG_OUTFIFO_FULL       CAU_STAT0_OFU                               /*!< OUT FIFO is full */
#define CAU_FLAG_BUSY               CAU_STAT0_BUSY                              /*!< the CAU core is busy */

/* cau_dmaen register value */
#define CAU_DMA_INFIFO              CAU_DMAEN_DMAIEN                            /*!< DMA input enable */
#define CAU_DMA_OUTFIFO             CAU_DMAEN_DMAOEN                            /*!< DMA output enable */

/* cau_inten register value */
#define CAU_INT_INFIFO              CAU_INTEN_IINTEN                            /*!< IN FIFO Interrupt */
#define CAU_INT_OUTFIFO             CAU_INTEN_OINTEN                            /*!< OUT FIFO Interrupt */

/* cau_stat1 register value */
#define CAU_FLAG_INFIFO             CAU_STAT1_ISTA                              /*!< IN FIFO flag status */
#define CAU_FLAG_OUTFIFO            CAU_STAT1_OSTA                              /*!< OUT FIFO flag status */

/* cau_intf register value */
#define CAU_INT_FLAG_INFIFO         CAU_INTF_IINTF                              /*!< IN FIFO interrupt status */
#define CAU_INT_FLAG_OUTFIFO        CAU_INTF_OINTF                              /*!< OUT FIFO interrupt status */

/* function declarations */
/* initialization functions */
/* reset the CAU peripheral */
void cau_deinit(void);
/* initialize the CAU encrypt and decrypt parameter struct with the default values */
void cau_struct_para_init(cau_parameter_struct *cau_parameter);
/* initialize the key parameter struct with the default values */
void cau_key_struct_para_init(cau_key_parameter_struct *key_initpara);
/* initialize the vectors parameter struct with the default values */
void cau_iv_struct_para_init(cau_iv_parameter_struct *iv_initpara);
/* initialize the context parameter struct with the default values */
void cau_context_struct_para_init(cau_context_parameter_struct *cau_context);

/* configuration functions */
/* enable the CAU peripheral */
void cau_enable(void);
/* disable the CAU peripheral */
void cau_disable(void);
/* enable the CAU DMA interface */
void cau_dma_enable(uint32_t dma_req);
/* disable the CAU DMA interface */
void cau_dma_disable(uint32_t dma_req);
/* initialize the CAU peripheral */
void cau_init(uint32_t alg_dir, uint32_t algo_mode, uint32_t swapping);
/* configure key selection */
void cau_aes_key_select(uint32_t key_selection);
/* configure key size if use AES algorithm */
void cau_aes_keysize_config(uint32_t key_size);
/* initialize the key parameters */
void cau_key_init(cau_key_parameter_struct *key_initpara);
/* initialize the vectors parameters */
void cau_iv_init(cau_iv_parameter_struct *iv_initpara);
/* configure phase */
void cau_phase_config(uint32_t phase);
/* flush the IN and OUT FIFOs */
void cau_fifo_flush(void);
/* return whether CAU peripheral is enabled or disabled */
ControlStatus cau_enable_state_get(void);

/* read and write functions */
/* write data to the IN FIFO */
void cau_data_write(uint32_t data);
/* return the last data entered into the output FIFO */
uint32_t cau_data_read(void);

/* context switch functions */
/* save context before context switching */
void cau_context_save(cau_context_parameter_struct *cau_context, cau_key_parameter_struct *key_initpara);
/* restore context after context switching */
void cau_context_restore(cau_context_parameter_struct *cau_context);

/* encrypt and decrypt functions */
/* encrypt and decrypt using AES in ECB mode */
ErrStatus cau_aes_ecb(cau_parameter_struct *cau_parameter, uint8_t *output);
/* encrypt and decrypt using AES in CBC mode */
ErrStatus cau_aes_cbc(cau_parameter_struct *cau_parameter, uint8_t *output);
/* encrypt and decrypt using AES in CTR mode */
ErrStatus cau_aes_ctr(cau_parameter_struct *cau_parameter, uint8_t *output);
/* encrypt and decrypt using AES in CFB mode */
ErrStatus cau_aes_cfb(cau_parameter_struct *cau_parameter, uint8_t *output);
/* encrypt and decrypt using AES in OFB mode */
ErrStatus cau_aes_ofb(cau_parameter_struct *cau_parameter, uint8_t *output);
/* encrypt and decrypt using AES in GCM mode */
ErrStatus cau_aes_gcm(cau_parameter_struct *cau_parameter, uint8_t *output, uint8_t *tag);
/* encrypt and decrypt using AES in CCM mode */
ErrStatus cau_aes_ccm(cau_parameter_struct *cau_parameter, uint8_t *output, uint8_t tag[], uint32_t tag_size, uint8_t aad_buf[]);
/* encrypt and decrypt using TDES in ECB mode */
ErrStatus cau_tdes_ecb(cau_parameter_struct *cau_parameter, uint8_t *output);
/* encrypt and decrypt using TDES in CBC mode */
ErrStatus cau_tdes_cbc(cau_parameter_struct *cau_parameter, uint8_t *output);
/* encrypt and decrypt using DES in ECB mode */
ErrStatus cau_des_ecb(cau_parameter_struct *cau_parameter, uint8_t *output);
/* encrypt and decrypt using DES in CBC mode */
ErrStatus cau_des_cbc(cau_parameter_struct *cau_parameter, uint8_t *output);

/* interrupt & flag functions */
/* get the CAU flag status */
FlagStatus cau_flag_get(uint32_t flag);
/* enable the CAU interrupts */
void cau_interrupt_enable(uint32_t interrupt);
/* disable the CAU interrupts */
void cau_interrupt_disable(uint32_t interrupt);
/* get the interrupt flag */
FlagStatus cau_interrupt_flag_get(uint32_t int_flag);

#endif /* GD32H7XX_CAU_H */
