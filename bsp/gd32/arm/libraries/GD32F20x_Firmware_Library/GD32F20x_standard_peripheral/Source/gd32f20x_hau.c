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

#include "gd32f20x_hau.h"
#include "gd32f20x_rcu.h"

/*!
    \brief      reset the HAU peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hau_deinit(void)
{
    /* enable HAU reset state */
    rcu_periph_reset_enable(RCU_HAURST);
    /* release HAU from reset state */
    rcu_periph_reset_disable(RCU_HAURST);
}

/*!
    \brief      initialize the HAU peripheral parameters
    \param[in]  initpara: HAU init parameter struct
                members of the structure and the member values are shown as below:
                  algo: HAU_ALGO_SHA1, HAU_ALGO_SHA224, HAU_ALGO_SHA256, HAU_ALGO_MD5
                  mode: HAU_MODE_HASH, HAU_MODE_HMAC
                  datatype: HAU_SWAPPING_32BIT, HAU_SWAPPING_16BIT, HAU_SWAPPING_8BIT, HAU_SWAPPING_1BIT
                  keytype: HAU_KEY_SHORTER_64, HAU_KEY_LONGGER_64
    \param[out] none
    \retval     none
*/
void hau_init(hau_init_parameter_struct* initpara)
{
    /* configure the algorithm, mode and the data type */
    HAU_CTL &= ~(HAU_CTL_ALGM_0 | HAU_CTL_ALGM_1 | HAU_CTL_DATAM | HAU_CTL_HMS);
    HAU_CTL |= (initpara->algo | initpara->datatype | initpara->mode);

    /* when mode is HMAC, set the key */
    if(HAU_MODE_HMAC == initpara->mode){
        HAU_CTL &= ~HAU_CTL_KLM;
        HAU_CTL |= initpara->keytype;
    }

    /* start the digest of a new message */
    HAU_CTL |= HAU_CTL_START;
}

/*!
    \brief      initialize the sturct hau_initpara
    \param[in]  initpara: HAU init parameter struct
                members of the structure and the member values are shown as below:
                  algo: HAU_ALGO_SHA1, HAU_ALGO_SHA224, HAU_ALGO_SHA256, HAU_ALGO_MD5
                  mode: HAU_MODE_HASH, HAU_MODE_HMAC
                  datatype: HAU_SWAPPING_32BIT, HAU_SWAPPING_16BIT, HAU_SWAPPING_8BIT, HAU_SWAPPING_1BIT
                  keytype: HAU_KEY_SHORTER_64, HAU_KEY_LONGGER_64
    \param[out] none
    \retval     none
*/
void hau_init_parameter_init(hau_init_parameter_struct* initpara)
{
    initpara->algo = HAU_ALGO_SHA1;
    initpara->mode = HAU_MODE_HASH;
    initpara->datatype = HAU_SWAPPING_32BIT;
    initpara->keytype = HAU_KEY_SHORTER_64;
}

/*!
    \brief      reset the HAU processor core
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hau_reset(void)
{
    /* set to 1 to reset the HAU processor core, then it is ready to start the digest calculation */
    HAU_CTL |= HAU_CTL_START;
}

/*!
    \brief      configure the number of valid bits in last word of the message
    \param[in]  valid_num: number of valid bits in last word of the message
      \arg        0x00: all 32 bits of the last data written are valid
      \arg        0x01: only bit [31] of the last data written to HAU_DI after data swapping are valid
      \arg        0x02: only bits [31:30] of the last data written to HAU_DI after data swapping are valid
      \arg        0x03: only bits [31:29] of the last data written to HAU_DI after data swapping are valid
                  ...
      \arg        0x1F: only bit [0] of the last data written to HAU_DI after data swapping are valid
    \param[out] none
    \retval     none
*/
void hau_last_word_validbits_num_config(uint32_t valid_num)
{
    HAU_CFG &= ~(HAU_CFG_VBL);
    HAU_CFG |= CFG_VBL(valid_num);
}

/*!
    \brief      write data to the IN FIFO
    \param[in]  data: data to write
    \param[out] none
    \retval     none
*/
void hau_data_write(uint32_t data)
{
    HAU_DI = data;
}

/*!
    \brief      return the number of words already written into the IN FIFO
    \param[in]  none
    \param[out] none
    \retval     number of words in the input FIFO
*/
uint32_t hau_infifo_words_num_get(void)
{
    uint32_t ret = 0U;
    ret = GET_CTL_NWIF(HAU_CTL);
    return ret;
}

/*!
    \brief      read the message digest result
    \param[in]  none
    \param[out] digestpara: HAU digest parameter struct
                  out[7:0]: message digest result 0-7
    \retval     none
*/
void hau_digest_read(hau_digest_parameter_struct* digestpara)
{
    digestpara->out[0] = HAU_DO0;
    digestpara->out[1] = HAU_DO1;
    digestpara->out[2] = HAU_DO2;
    digestpara->out[3] = HAU_DO3;
    digestpara->out[4] = HAU_DO4;
    digestpara->out[5] = HAU_DO5;
    digestpara->out[6] = HAU_DO6;
    digestpara->out[7] = HAU_DO7;
}

/*!
    \brief      enable digest calculation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hau_digest_calculation_enable(void)
{
    HAU_CFG |= HAU_CFG_CALEN;
}

/*!
    \brief      configure single or multiple DMA is used, and digest calculation at the end of a DMA transfer or not
    \param[in]  multi_single
                only one parameter can be selected which is shown as below
      \arg        SINGLE_DMA_AUTO_DIGEST: message padding and message digest calculation at the end of a DMA transfer
      \arg        MULTIPLE_DMA_NO_DIGEST: multiple DMA transfers needed and CALEN bit is not automatically set at the end of a DMA transfer
    \param[out] none
    \retval     none
*/
void hau_multiple_single_dma_config(uint32_t multi_single)
{
    HAU_CTL &= ~HAU_CTL_MDS;
    HAU_CTL |= multi_single;
}

/*!
    \brief      enable the HAU DMA interface
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hau_dma_enable(void)
{
    HAU_CTL |= HAU_CTL_DMAE;
}

/*!
    \brief      disable the HAU DMA interface
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hau_dma_disable(void)
{
    HAU_CTL &= ~HAU_CTL_DMAE;
}

/*!
    \brief      get the HAU flag status
    \param[in]  flag: HAU flag status
                only one parameter can be selected which is shown as below
      \arg        HAU_FLAG_DATA_INPUT: there is enough space (16 bytes) in the input FIFO
      \arg        HAU_FLAG_CALCULATION_COMPLETE: digest calculation is completed
      \arg        HAU_FLAG_DMA: DMA is enabled (DMAE =1) or a transfer is processing
      \arg        HAU_FLAG_BUSY: data block is in process
      \arg        HAU_FLAG_INFIFO_NO_EMPTY: the input FIFO is not empty
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hau_flag_get(uint32_t flag)
{
    uint32_t ret = 0U;
    FlagStatus ret_flag = RESET;

    /* check if the flag is in HAU_CTL register */
    if(RESET != (flag & HAU_FLAG_INFIFO_NO_EMPTY)){
        ret = HAU_CTL;
    }else{
        ret = HAU_STAT;
    }

    if (RESET != (ret & flag)){
        ret_flag = SET;
    }

    return ret_flag;
}

/*!
    \brief      clear the HAU flag status
    \param[in]  flag: HAU flag status
                one or more parameters can be selected which are shown as below
      \arg        HAU_FLAG_DATA_INPUT: there is enough space (16 bytes) in the input FIFO
      \arg        HAU_FLAG_CALCULATION_COMPLETE: digest calculation is completed
    \param[out] none
    \retval     none
*/
void hau_flag_clear(uint32_t flag)
{
    HAU_STAT = ~(uint32_t)(flag);
}

/*!
    \brief      enable the HAU interrupts
    \param[in]  interrupt: specify the HAU interrupt source to be enabled
                one or more parameters can be selected which are shown as below
      \arg        HAU_INT_DATA_INPUT: a new block can be entered into the IN buffer
      \arg        HAU_INT_CALCULATION_COMPLETE: calculation complete
    \param[out] none
    \retval     none
*/
void hau_interrupt_enable(uint32_t interrupt)
{
    HAU_INTEN |= interrupt;
}

/*!
    \brief      disable the HAU interrupts
    \param[in]  interrupt: specify the HAU interrupt source to be disabled
                one or more parameters can be selected which are shown as below
      \arg        HAU_INT_DATA_INPUT: a new block can be entered into the IN buffer
      \arg        HAU_INT_CALCULATION_COMPLETE: calculation complete
    \param[out] none
    \retval     none
*/
void hau_interrupt_disable(uint32_t interrupt)
{
    HAU_INTEN &= ~(uint32_t)(interrupt);
}

/*!
    \brief      get the HAU interrupt flag status
    \param[in]  int_flag: HAU interrupt flag status
                only one parameter can be selected which is shown as below
      \arg        HAU_INT_FLAG_DATA_INPUT: there is enough space (16 bytes) in the input FIFO
      \arg        HAU_INT_FLAG_CALCULATION_COMPLETE: digest calculation is completed
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hau_interrupt_flag_get(uint32_t int_flag)
{
    uint32_t ret = 0U;
    FlagStatus flag = RESET;

    /* return the status of the interrupt */
    ret =  HAU_STAT;

    if(RESET != ((HAU_INTEN & ret) & int_flag)){
        flag = SET;
    }

    return flag;
}

/*!
    \brief      clear the HAU interrupt flag status
    \param[in]  int_flag: HAU interrupt flag status
                one or more parameters can be selected which are shown as below
      \arg        HAU_INT_FLAG_DATA_INPUT: there is enough space (16 bytes) in the input FIFO
      \arg        HAU_INT_FLAG_CALCULATION_COMPLETE: digest calculation is completed
    \param[out] none
    \retval     none
*/
void hau_interrupt_flag_clear(uint32_t int_flag)
{
    HAU_STAT = ~(uint32_t)(int_flag);
}
