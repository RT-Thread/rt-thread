/*!
    \file    gd32f5xx_cau.c
    \brief   CAU driver

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

#include "gd32f5xx_cau.h"
#include "gd32f5xx_rcu.h"

#define STAT0_AESDES_MASK    ((uint32_t)0x00000015U)
#define STAT0_TDES_MASK      ((uint32_t)0x00000014U)

/*!
    \brief      reset the CAU peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cau_deinit(void)
{
    /* enable CAU reset state */
    rcu_periph_reset_enable(RCU_CAURST);
    /* release CAU from reset state */
    rcu_periph_reset_disable(RCU_CAURST);
}


/*!
    \brief      initialize the CAU encrypt and decrypt parameter struct with the default values
    \param[in]  none
    \param[out] cau_parameter:
                  alg_dir: algorithm direction
                    CAU_ENCRYPT, CAU_DECRYPT
                  key: key
                  key_size: key size in bytes
                  iv: initialization vector
                  iv_size: iv size in bytes
                  input: input data
                  in_length: input data length in bytes
                  aad: additional authentication data
                  aad_size: header size
    \retval     none
*/
void cau_struct_para_init(cau_parameter_struct *cau_parameter)
{
    /* set the CAU encrypt and decrypt parameters struct with the default values */
    cau_parameter->alg_dir     = CAU_ENCRYPT;
    cau_parameter->key         = 0U;
    cau_parameter->key_size    = 0U;
    cau_parameter->iv          = 0U;
    cau_parameter->iv_size     = 0U;
    cau_parameter->input       = 0U;
    cau_parameter->in_length   = 0U;
    cau_parameter->aad         = 0U;
    cau_parameter->aad_size    = 0U;
}

/*!
    \brief      initialize the key parameter structure with the default values
    \param[in]  none
    \param[out] key_initpara:
                  key_0_high: key 0 high
                  key_0_low:  key 0 low
                  key_1_high: key 1 high
                  key_1_low:  key 1 low
                  key_2_high: key 2 high
                  key_2_low:  key 2 low
                  key_3_high: key 3 high
                  key_3_low:  key 3 low
    \retval     none
*/
void cau_key_struct_para_init(cau_key_parameter_struct *key_initpara)
{
    /* set the key parameters struct with the default values */
    key_initpara->key_0_high   = 0U;
    key_initpara->key_0_low    = 0U;
    key_initpara->key_1_high   = 0U;
    key_initpara->key_1_low    = 0U;
    key_initpara->key_2_high   = 0U;
    key_initpara->key_2_low    = 0U;
    key_initpara->key_3_high   = 0U;
    key_initpara->key_3_low    = 0U;
}

/*!
    \brief      initialize the vectors parameter struct with the default values
    \param[in]  none
    \param[out] iv_initpara:
                  iv_0_high: init vector 0 high
                  iv_0_low:  init vector 0 low
                  iv_1_high: init vector 1 high
                  iv_1_low:  init vector 1 low
    \retval     none
*/
void cau_iv_struct_para_init(cau_iv_parameter_struct *iv_initpara)
{
    /* set the vectors parameters struct with the default values */
    iv_initpara->iv_0_high   = 0U;
    iv_initpara->iv_0_low    = 0U;
    iv_initpara->iv_1_high   = 0U;
    iv_initpara->iv_1_low    = 0U;
}

/*!
    \brief      initialize the context parameter struct with the default values
    \param[in]  none
    \param[out] cau_context:
                  ctl_config: current configuration
                  iv_0_high: init vector 0 high
                  iv_0_low:  init vector 0 low
                  iv_1_high: init vector 1 high
                  iv_1_low:  init vector 1 low
                  key_0_high: key 0 high
                  key_0_low:  key 0 low
                  key_1_high: key 1 high
                  key_1_low:  key 1 low
                  key_2_high: key 2 high
                  key_2_low:  key 2 low
                  key_3_high: key 3 high
                  key_3_low:  key 3 low
                  gcmccmctxs[8]: GCM or CCM mode context switch
                  gcmctxs[8]: GCM mode context switch
    \retval     none
*/
void cau_context_struct_para_init(cau_context_parameter_struct *cau_context)
{
    cau_context->ctl_config = 0U;

    /* set the vectors parameters with the default values */
    cau_context->iv_0_high  = 0U;
    cau_context->iv_0_low   = 0U;
    cau_context->iv_1_high  = 0U;
    cau_context->iv_1_low   = 0U;

    /* set the key parameters with the default values */
    cau_context->key_0_high = 0U;
    cau_context->key_0_low  = 0U;
    cau_context->key_1_high = 0U;
    cau_context->key_1_low  = 0U;
    cau_context->key_2_high = 0U;
    cau_context->key_2_low  = 0U;
    cau_context->key_3_high = 0U;
    cau_context->key_3_low  = 0U;

    /* set the context switch with the default values */
    cau_context->gcmccmctxs[0] = 0U;
    cau_context->gcmccmctxs[1] = 0U;
    cau_context->gcmccmctxs[2] = 0U;
    cau_context->gcmccmctxs[3] = 0U;
    cau_context->gcmccmctxs[4] = 0U;
    cau_context->gcmccmctxs[5] = 0U;
    cau_context->gcmccmctxs[6] = 0U;
    cau_context->gcmccmctxs[7] = 0U;

    cau_context->gcmctxs[0] = 0U;
    cau_context->gcmctxs[1] = 0U;
    cau_context->gcmctxs[2] = 0U;
    cau_context->gcmctxs[3] = 0U;
    cau_context->gcmctxs[4] = 0U;
    cau_context->gcmctxs[5] = 0U;
    cau_context->gcmctxs[6] = 0U;
    cau_context->gcmctxs[7] = 0U;
}

/*!
    \brief      enable the CAU peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cau_enable(void)
{
    /* enable the CAU processor */
    CAU_CTL |= CAU_CTL_CAUEN;
}

/*!
    \brief      disable the CAU peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cau_disable(void)
{
    /* disable the CAU processor */
    CAU_CTL &= ~CAU_CTL_CAUEN;
}

/*!
    \brief      enable the CAU DMA interface
    \param[in]  dma_req: specify the CAU DMA transfer request to be enabled
                one or more parameters can be selected which are shown as below:
      \arg        CAU_DMA_INFIFO: DMA for incoming(Rx) data transfer
      \arg        CAU_DMA_OUTFIFO: DMA for outgoing(Tx) data transfer
    \param[out] none
    \retval     none
*/
void cau_dma_enable(uint32_t dma_req)
{
    /* enable the selected CAU DMA request */
    CAU_DMAEN |= dma_req;
}

/*!
    \brief      disable the CAU DMA interface
    \param[in]  dma_req: specify the CAU DMA transfer request to be disabled
                one or more parameters can be selected which are shown as below:
      \arg        CAU_DMA_INFIFO: DMA for incoming(Rx) data transfer
      \arg        CAU_DMA_OUTFIFO: DMA for outgoing(Tx) data transfer
    \param[out] none
    \retval     none
*/
void cau_dma_disable(uint32_t dma_req)
{
    /* disable the selected CAU DMA request */
    CAU_DMAEN &= ~(dma_req);
}

/*!
    \brief      initialize the CAU peripheral
    \param[in]  alg_dir: algorithm direction
                only one parameter can be selected which is shown as below:
      \arg        CAU_ENCRYPT: encrypt
      \arg        CAU_DECRYPT: decrypt
    \param[in]  algo_mode: algorithm mode selection
                only one parameter can be selected which is shown as below:
      \arg        CAU_MODE_TDES_ECB: TDES-ECB (3DES Electronic codebook)
      \arg        CAU_MODE_TDES_CBC: TDES-CBC (3DES Cipher block chaining)
      \arg        CAU_MODE_DES_ECB: DES-ECB (simple DES Electronic codebook)
      \arg        CAU_MODE_DES_CBC: DES-CBC (simple DES Cipher block chaining)
      \arg        CAU_MODE_AES_ECB: AES-ECB (AES Electronic codebook)
      \arg        CAU_MODE_AES_CBC: AES-CBC (AES Cipher block chaining)
      \arg        CAU_MODE_AES_CTR: AES-CTR (AES counter mode)
      \arg        CAU_MODE_AES_KEY: AES decryption key preparation mode
      \arg        CAU_MODE_AES_GCM: AES-GCM (AES Galois/counter mode)
      \arg        CAU_MODE_AES_CCM: AES-CCM (AES combined cipher machine mode)
      \arg        CAU_MODE_AES_CFB: AES-CFB (cipher feedback mode)
      \arg        CAU_MODE_AES_OFB: AES-OFB (output feedback mode)
    \param[in]  swapping: data swapping selection
                only one parameter can be selected which is shown as below:
      \arg        CAU_SWAPPING_32BIT: no swapping
      \arg        CAU_SWAPPING_16BIT: half-word swapping
      \arg        CAU_SWAPPING_8BIT: bytes swapping
      \arg        CAU_SWAPPING_1BIT: bit swapping
    \param[out] none
    \retval     none
*/
void cau_init(uint32_t alg_dir, uint32_t algo_mode, uint32_t swapping)
{
    /* select algorithm mode */
    CAU_CTL &= ~CAU_CTL_ALGM;
    CAU_CTL |= algo_mode;

    /* select data swapping */
    CAU_CTL &= ~CAU_CTL_DATAM;
    CAU_CTL |= swapping;

    /* select algorithm direction */
    CAU_CTL &= ~CAU_CTL_CAUDIR;
    CAU_CTL |= alg_dir;
}

/*!
    \brief      configure key size if use AES algorithm
    \param[in]  key_size: key length selection when aes mode
                only one parameter can be selected which is shown as below:
      \arg        CAU_KEYSIZE_128BIT: 128 bit key length
      \arg        CAU_KEYSIZE_192BIT: 192 bit key length
      \arg        CAU_KEYSIZE_256BIT: 256 bit key length
    \param[out] none
    \retval     none
*/
void cau_aes_keysize_config(uint32_t key_size)
{
    CAU_CTL &= ~CAU_CTL_KEYM;
    CAU_CTL |= key_size;
}

/*!
    \brief      initialize the key parameters
    \param[in]  key_initpara: key init parameter struct
                  key_0_high: key 0 high
                  key_0_low:  key 0 low
                  key_1_high: key 1 high
                  key_1_low:  key 1 low
                  key_2_high: key 2 high
                  key_2_low:  key 2 low
                  key_3_high: key 3 high
                  key_3_low:  key 3 low
    \param[out] none
    \retval     none
*/
void cau_key_init(cau_key_parameter_struct *key_initpara)
{
    CAU_KEY0H = key_initpara->key_0_high;
    CAU_KEY0L = key_initpara->key_0_low;
    CAU_KEY1H = key_initpara->key_1_high;
    CAU_KEY1L = key_initpara->key_1_low;
    CAU_KEY2H = key_initpara->key_2_high;
    CAU_KEY2L = key_initpara->key_2_low;
    CAU_KEY3H = key_initpara->key_3_high;
    CAU_KEY3L = key_initpara->key_3_low;
}

/*!
    \brief      initialize the vectors parameters
    \param[in]  iv_initpara: vectors init parameter struct
                  iv_0_high: init vector 0 high
                  iv_0_low:  init vector 0 low
                  iv_1_high: init vector 1 high
                  iv_1_low:  init vector 1 low
    \param[out] none
    \retval     none
*/
void cau_iv_init(cau_iv_parameter_struct *iv_initpara)
{
    CAU_IV0H = iv_initpara->iv_0_high;
    CAU_IV0L = iv_initpara->iv_0_low;
    CAU_IV1H = iv_initpara->iv_1_high;
    CAU_IV1L = iv_initpara->iv_1_low;
}

/*!
    \brief      configure phase
    \param[in]  phase: gcm or ccm phase
                only one parameter can be selected which is shown as below:
      \arg        CAU_PREPARE_PHASE: prepare phase
      \arg        CAU_AAD_PHASE: AAD phase
      \arg        CAU_ENCRYPT_DECRYPT_PHASE: encryption/decryption phase
      \arg        CAU_TAG_PHASE: tag phase
    \param[out] none
    \retval     none
*/
void cau_phase_config(uint32_t phase)
{
    uint32_t temp;
    /* Get the CTL register */
    temp = CAU_CTL;
    /* Reset the phase configuration bits */
    temp &= ~CAU_CTL_GCM_CCMPH;
    /* Set the selected phase */
    temp |= phase;
    /* Set the CTL register */
    CAU_CTL = temp;
}

/*!
    \brief      flush the IN and OUT FIFOs
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cau_fifo_flush(void)
{
    /* reset the read and write pointers of the FIFOs */
    CAU_CTL |= CAU_CTL_FFLUSH;
}

/*!
    \brief      return whether CAU peripheral is enabled or disabled
    \param[in]  none
    \param[out] none
    \retval     ControlStatus: ENABLE or DISABLE
*/
ControlStatus cau_enable_state_get(void)
{
    ControlStatus ret = DISABLE;
    if(RESET != (CAU_CTL & CAU_CTL_CAUEN)) {
        ret = ENABLE;
    }
    return ret;
}

/*!
    \brief      write data to the IN FIFO
    \param[in]  data: data to write (0 - 0xFFFFFFFF)
    \param[out] none
    \retval     none
*/
void cau_data_write(uint32_t data)
{
    CAU_DI = data;
}

/*!
    \brief      return the last data entered into the output FIFO
    \param[in]  none
    \param[out] none
    \retval     last data entered into the output FIFO
*/
uint32_t cau_data_read(void)
{
    return CAU_DO;
}

/*!
    \brief      save context before context switching
    \param[in]  key_initpara: key init parameter struct
                  key_0_high: key 0 high
                  key_0_low:  key 0 low
                  key_1_high: key 1 high
                  key_1_low:  key 1 low
                  key_2_high: key 2 high
                  key_2_low:  key 2 low
                  key_3_high: key 3 high
                  key_3_low:  key 3 low
    \param[out] cau_context:
                  ctl_config: current configuration
                  iv_0_high: init vector 0 high
                  iv_0_low:  init vector 0 low
                  iv_1_high: init vector 1 high
                  iv_1_low:  init vector 1 low
                  key_0_high: key 0 high
                  key_0_low:  key 0 low
                  key_1_high: key 1 high
                  key_1_low:  key 1 low
                  key_2_high: key 2 high
                  key_2_low:  key 2 low
                  key_3_high: key 3 high
                  key_3_low:  key 3 low
                  gcmccmctxs[8]: GCM or CCM mode context switch
                  gcmctxs[8]: GCM mode context switch
    \retval     none
*/
void cau_context_save(cau_context_parameter_struct *cau_context, cau_key_parameter_struct *key_initpara)
{
    uint32_t checkmask = 0U;
    uint32_t checkbits = 0U;
    uint32_t algm_reg = 0U;

    /* stop DMA transfers on the IN FIFO by clearing the DMAIEN bit in the CAU_DMAEN */
    CAU_DMAEN &= ~CAU_DMA_INFIFO;

    algm_reg = CAU_CTL & CAU_CTL_ALGM;
    /* AES or DES */
    if((uint32_t)0 != (algm_reg & (~CAU_MODE_TDES_CBC))) {
        /* wait until both the IN and OUT FIFOs are empty (IEM=1 and ONE=0 in the CAU_STAT0 register) and BUSY=0 */
        checkbits = CAU_STAT0_IEM;
        checkmask = STAT0_AESDES_MASK;
        /* TDES */
    } else {
        /* wait until OUT FIFO is empty (ONE=0 in the CAU_STAT0 register) and BUSY=0 */
        checkbits = 0U;
        checkmask = STAT0_TDES_MASK;
    }

    while((CAU_STAT0 & checkmask) != checkbits) {
    }

    /* stop DMA transfers on the OUT FIFO by clear CAU_DMAEN_DMAOEN=0 */
    CAU_DMAEN &= ~CAU_DMAEN_DMAOEN;
    /* disable CAU */
    CAU_CTL &= ~CAU_CTL_CAUEN;

    /* save the current configuration (bit 19, bit[17:16] and bit[9:2] in the CAU_CTL register) */
    cau_context->ctl_config  = CAU_CTL & (CAU_CTL_GCM_CCMPH |
                                          CAU_CTL_KEYM  |
                                          CAU_CTL_DATAM |
                                          CAU_CTL_ALGM  |
                                          CAU_CTL_CAUDIR |
                                          CAU_CTL_NBPILB);

    /* save the key value */
    cau_context->key_0_high = key_initpara->key_0_high;
    cau_context->key_0_low  = key_initpara->key_0_low;
    cau_context->key_1_high = key_initpara->key_1_high;
    cau_context->key_1_low  = key_initpara->key_1_low;
    cau_context->key_2_high = key_initpara->key_2_high;
    cau_context->key_2_low  = key_initpara->key_2_low;
    cau_context->key_3_high = key_initpara->key_3_high;
    cau_context->key_3_low  = key_initpara->key_3_low;

    if((CAU_MODE_TDES_ECB != algm_reg) && (CAU_MODE_DES_ECB != algm_reg) && (CAU_MODE_AES_ECB != algm_reg)) {
        /* if not in ECB mode, save the initialization vectors */
        cau_context->iv_0_high = CAU_IV0H;
        cau_context->iv_0_low = CAU_IV0L;
        cau_context->iv_1_high = CAU_IV1H;
        cau_context->iv_1_low = CAU_IV1L;
    }

    /* if in GCM/CCM mode, save the context switch registers */
    if((CAU_MODE_AES_GCM == algm_reg) || (CAU_MODE_AES_CCM == algm_reg)) {
        cau_context->gcmccmctxs[0U] = CAU_GCMCCMCTXSx(0U);
        cau_context->gcmccmctxs[1U] = CAU_GCMCCMCTXSx(1U);
        cau_context->gcmccmctxs[2U] = CAU_GCMCCMCTXSx(2U);
        cau_context->gcmccmctxs[3U] = CAU_GCMCCMCTXSx(3U);
        cau_context->gcmccmctxs[4U] = CAU_GCMCCMCTXSx(4U);
        cau_context->gcmccmctxs[5U] = CAU_GCMCCMCTXSx(5U);
        cau_context->gcmccmctxs[6U] = CAU_GCMCCMCTXSx(6U);
        cau_context->gcmccmctxs[7U] = CAU_GCMCCMCTXSx(7U);
    }

    /* if in GCM mode, save the context switch registers */
    if(CAU_MODE_AES_GCM == algm_reg) {
        cau_context->gcmctxs[0U] = CAU_GCMCTXSx(0U);
        cau_context->gcmctxs[1U] = CAU_GCMCTXSx(1U);
        cau_context->gcmctxs[2U] = CAU_GCMCTXSx(2U);
        cau_context->gcmctxs[3U] = CAU_GCMCTXSx(3U);
        cau_context->gcmctxs[4U] = CAU_GCMCTXSx(4U);
        cau_context->gcmctxs[5U] = CAU_GCMCTXSx(5U);
        cau_context->gcmctxs[6U] = CAU_GCMCTXSx(6U);
        cau_context->gcmctxs[7U] = CAU_GCMCTXSx(7U);
    }
}

/*!
    \brief      restore context after context switching
    \param[in]  cau_context:
                  ctl_config: current configuration
                  iv_0_high: init vector 0 high
                  iv_0_low:  init vector 0 low
                  iv_1_high: init vector 1 high
                  iv_1_low:  init vector 1 low
                  key_0_high: key 0 high
                  key_0_low:  key 0 low
                  key_1_high: key 1 high
                  key_1_low:  key 1 low
                  key_2_high: key 2 high
                  key_2_low:  key 2 low
                  key_3_high: key 3 high
                  key_3_low:  key 3 low
                  gcmccmctxs[8]: GCM or CCM mode context switch
                  gcmctxs[8]: GCM mode context switch
    \param[out] none
    \retval     none
*/
void cau_context_restore(cau_context_parameter_struct *cau_context)
{
    uint32_t algm_reg, aes_decrypt;

    /* configure the processor with the saved configuration */
    CAU_CTL = cau_context->ctl_config;

    algm_reg = CAU_CTL & CAU_CTL_ALGM;

    /* restore the key value */
    CAU_KEY0H = cau_context->key_0_high;
    CAU_KEY0L = cau_context->key_0_low;
    CAU_KEY1H = cau_context->key_1_high;
    CAU_KEY1L = cau_context->key_1_low;
    CAU_KEY2H = cau_context->key_2_high;
    CAU_KEY2L = cau_context->key_2_low;
    CAU_KEY3H = cau_context->key_3_high;
    CAU_KEY3L = cau_context->key_3_low;

    if((CAU_MODE_TDES_ECB != algm_reg) && (CAU_MODE_DES_ECB != algm_reg) && (CAU_MODE_AES_ECB != algm_reg)) {
        /* restore the initialization vectors */
        CAU_IV0H = cau_context->iv_0_high;
        CAU_IV0L = cau_context->iv_0_low;
        CAU_IV1H = cau_context->iv_1_high;
        CAU_IV1L = cau_context->iv_1_low;
    }

    /* if in GCM/CCM mode, restore the context switch registers */
    if((CAU_MODE_AES_GCM == algm_reg) || (CAU_MODE_AES_CCM == algm_reg)) {
        CAU_GCMCCMCTXSx(0U) = cau_context->gcmccmctxs[0U];
        CAU_GCMCCMCTXSx(1U) = cau_context->gcmccmctxs[1U];
        CAU_GCMCCMCTXSx(2U) = cau_context->gcmccmctxs[2U];
        CAU_GCMCCMCTXSx(3U) = cau_context->gcmccmctxs[3U];
        CAU_GCMCCMCTXSx(4U) = cau_context->gcmccmctxs[4U];
        CAU_GCMCCMCTXSx(5U) = cau_context->gcmccmctxs[5U];
        CAU_GCMCCMCTXSx(6U) = cau_context->gcmccmctxs[6U];
        CAU_GCMCCMCTXSx(7U) = cau_context->gcmccmctxs[7U];
    }

    /* if in GCM mode, restore the context switch registers */
    if(CAU_MODE_AES_GCM == algm_reg) {
        CAU_GCMCTXSx(0U) = cau_context->gcmctxs[0U];
        CAU_GCMCTXSx(1U) = cau_context->gcmctxs[1U];
        CAU_GCMCTXSx(2U) = cau_context->gcmctxs[2U];
        CAU_GCMCTXSx(3U) = cau_context->gcmctxs[3U];
        CAU_GCMCTXSx(4U) = cau_context->gcmctxs[4U];
        CAU_GCMCTXSx(5U) = cau_context->gcmctxs[5U];
        CAU_GCMCTXSx(6U) = cau_context->gcmctxs[6U];
        CAU_GCMCTXSx(7U) = cau_context->gcmctxs[7U];
    }

    /* if it is AES ECB/CBC decryption, then first prepare key */
    aes_decrypt = CAU_CTL & (CAU_CTL_ALGM | CAU_CTL_CAUDIR);
    if(((CAU_MODE_AES_ECB | CAU_DECRYPT) == aes_decrypt) || ((CAU_MODE_AES_CBC | CAU_DECRYPT) == aes_decrypt)) {
        uint32_t alg_dir, algo_mode, swapping;

        /* flush IN/OUT FIFOs */
        cau_fifo_flush();
        /* parameters for key preparation for AES decryption */
        alg_dir = CAU_DECRYPT;
        algo_mode = CAU_MODE_AES_KEY;
        swapping = CAU_SWAPPING_32BIT;
        cau_init(alg_dir, algo_mode, swapping);

        /* enable CAU */
        cau_enable();

        /* wait until BUSY=0 */
        while((uint32_t)0U != cau_flag_get(CAU_FLAG_BUSY)) {
        }

        /* parameters for decryption */
        CAU_CTL = cau_context->ctl_config;
    }

    /* enable CAU */
    cau_enable();
}

/*!
    \brief      get the CAU flag status
    \param[in]  flag: CAU flag status
                only one parameter can be selected which is shown as below:
      \arg        CAU_FLAG_INFIFO_EMPTY: input FIFO empty
      \arg        CAU_FLAG_INFIFO_NO_FULL: input FIFO is not full
      \arg        CAU_FLAG_OUTFIFO_NO_EMPTY: output FIFO not empty
      \arg        CAU_FLAG_OUTFIFO_FULL: output FIFO is full
      \arg        CAU_FLAG_BUSY: the CAU core is busy
      \arg        CAU_FLAG_INFIFO: input FIFO flag status
      \arg        CAU_FLAG_OUTFIFO: output FIFO flag status
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cau_flag_get(uint32_t flag)
{
    uint32_t reg = 0U;
    FlagStatus ret_flag = RESET;

    /* check if the flag is in CAU_STAT1 register */
    if(1U == (flag >> 31U)) {
        reg = CAU_STAT1;
    } else {
        /* the flag is in CAU_STAT0 register */
        reg = CAU_STAT0;
    }

    /* check the status of the specified CAU flag */
    if(0U != (reg & flag)) {
        ret_flag = SET;
    }

    return ret_flag;
}

/*!
    \brief      enable the CAU interrupts
    \param[in]  interrupt: specify the CAU interrupt source to be enabled
                one or more parameters can be selected which are shown as below:
      \arg        CAU_INT_INFIFO: input FIFO interrupt
      \arg        CAU_INT_OUTFIFO: output FIFO interrupt
    \param[out] none
    \retval     none
*/
void cau_interrupt_enable(uint32_t interrupt)
{
    /* enable the selected CAU interrupt */
    CAU_INTEN |= interrupt;
}

/*!
    \brief      disable the CAU interrupts
    \param[in]  interrupt: specify the CAU interrupt source to be disabled
                one or more parameters can be selected which are shown as below:
      \arg        CAU_INT_INFIFO: input FIFO interrupt
      \arg        CAU_INT_OUTFIFO: output FIFO interrupt
    \param[out] none
    \retval     none
*/
void cau_interrupt_disable(uint32_t interrupt)
{
    /* disable the selected CAU interrupt */
    CAU_INTEN &= ~(interrupt);
}

/*!
    \brief      get the interrupt flag
    \param[in]  interrupt: CAU interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        CAU_INT_FLAG_INFIFO: input FIFO interrupt
      \arg        CAU_INT_FLAG_OUTFIFO: output FIFO interrupt
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cau_interrupt_flag_get(uint32_t interrupt)
{
    FlagStatus flag = RESET;

    /* check the status of the specified CAU interrupt */
    if(RESET != (CAU_INTF & interrupt)) {
        flag = SET;
    }

    return flag;
}
