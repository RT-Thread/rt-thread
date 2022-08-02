/*!
    \file    gd32f20x_cau.c
    \brief   CAU driver

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

#include "gd32f20x_cau.h"
#include "gd32f20x_rcu.h"

#define FLAG_MASK     ((uint32_t)0x00000020U)

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
                one or more parameters can be selected which are shown as below
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
                one or more parameters can be selected which are shown as below
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
    \param[in]  algo_dir: algorithm direction
                only one parameter can be selected which is shown as below
      \arg        CAU_ENCRYPT: encrypt
      \arg        CAU_DECRYPT: decrypt
    \param[in]  algo_mode: algorithm mode selection
                only one parameter can be selected which is shown as below
      \arg        CAU_MODE_TDES_ECB: TDES-ECB (3DES Electronic codebook)
      \arg        CAU_MODE_TDES_CBC: TDES-CBC (3DES Cipher block chaining)
      \arg        CAU_MODE_DES_ECB: DES-ECB (simple DES Electronic codebook)
      \arg        CAU_MODE_DES_CBC: DES-CBC (simple DES Cipher block chaining)
      \arg        CAU_MODE_AES_ECB: AES-ECB (AES Electronic codebook)
      \arg        CAU_MODE_AES_CBC: AES-CBC (AES Cipher block chaining)
      \arg        CAU_MODE_AES_CTR: AES-CTR (AES counter mode)
      \arg        CAU_MODE_AES_KEY: AES decryption key preparation mode
    \param[in]  swapping: data swapping selection
                only one parameter can be selected which is shown as below
      \arg        CAU_SWAPPING_32BIT: no swapping
      \arg        CAU_SWAPPING_16BIT: half-word swapping
      \arg        CAU_SWAPPING_8BIT: bytes swapping
      \arg        CAU_SWAPPING_1BIT: bit swapping
    \param[out] none
    \retval     none
*/
void cau_init(uint32_t algo_dir, uint32_t algo_mode, uint32_t swapping)
{
    /* select algorithm mode */
    CAU_CTL &= ~CAU_CTL_ALGM;
    CAU_CTL |= algo_mode;

    /* select data swapping */
    CAU_CTL &= ~CAU_CTL_DATAM;
    CAU_CTL |= swapping;

    /* select algorithm direction */
    CAU_CTL &= ~CAU_CTL_CAUDIR;
    CAU_CTL |= algo_dir;
}

/*!
    \brief      configure key size if used AES algorithm
    \param[in]  key_size: key length selection when aes mode
                only one parameter can be selected which is shown as below
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
void cau_key_init(cau_key_parameter_struct* key_initpara)
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
    \brief      initialize the sturct cau_key_initpara
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
void cau_key_parameter_init(cau_key_parameter_struct* key_initpara)
{
    key_initpara->key_0_high = 0U;
    key_initpara->key_0_low  = 0U;
    key_initpara->key_1_high = 0U;
    key_initpara->key_1_low  = 0U;
    key_initpara->key_2_high = 0U;
    key_initpara->key_2_low  = 0U;
    key_initpara->key_3_high = 0U;
    key_initpara->key_3_low  = 0U;
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
void cau_iv_init(cau_iv_parameter_struct* iv_initpara)
{
    CAU_IV0H = iv_initpara->iv_0_high;
    CAU_IV0L = iv_initpara->iv_0_low;
    CAU_IV1H = iv_initpara->iv_1_high;
    CAU_IV1L = iv_initpara->iv_1_low;
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
void cau_iv_parameter_init(cau_iv_parameter_struct* iv_initpara)
{
    iv_initpara->iv_0_high = 0U;
    iv_initpara->iv_0_low  = 0U;
    iv_initpara->iv_1_high = 0U;
    iv_initpara->iv_1_low  = 0U;
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
    if(RESET != (CAU_CTL & CAU_CTL_CAUEN)){
        ret = ENABLE;
    }
    return ret;
}

/*!
    \brief      write data to the IN FIFO
    \param[in]  data: data to write
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
    \brief      get the CAU flag status
    \param[in]  flag: CAU flag status
                only one parameter can be selected which is shown as below
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
    if(RESET != (flag & FLAG_MASK)){
        reg = CAU_STAT1;
    }else{
        /* the flag is in CAU_STAT0 register */
        reg = CAU_STAT0;
    }

    /* check the status of the specified CAU flag */
    if(RESET != (reg & flag)){
        ret_flag = SET;
    }

    return ret_flag;
}

/*!
    \brief      enable the CAU interrupts
    \param[in]  interrupt: specify the CAU interrupt source to be enabled
                one or more parameters can be selected which are shown as below
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
                one or more parameters can be selected which are shown as below
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
    \param[in]  int_flag: CAU interrupt flag
                only one parameter can be selected which is shown as below
      \arg        CAU_INT_FLAG_INFIFO: input FIFO interrupt
      \arg        CAU_INT_FLAG_OUTFIFO: output FIFO interrupt
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cau_interrupt_flag_get(uint32_t int_flag)
{
    FlagStatus flag = RESET;

    /* check the status of the specified CAU interrupt */
    if(RESET != (CAU_INTF & int_flag)){
        flag = SET;
    }

    return flag;
}
