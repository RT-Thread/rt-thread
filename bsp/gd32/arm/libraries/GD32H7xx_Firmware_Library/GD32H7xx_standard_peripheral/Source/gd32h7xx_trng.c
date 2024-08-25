/*!
    \file    gd32h7xx_trng.c
    \brief   TRNG driver

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

#include "gd32h7xx_trng.h"

/*!
    \brief      deinitialize the TRNG
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_deinit(void)
{
    rcu_periph_reset_enable(RCU_TRNGRST);
    rcu_periph_reset_disable(RCU_TRNGRST);
}

/*!
    \brief      enable the TRNG interface
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_enable(void)
{
    uint32_t trng_config = TRNG_CTL;
    trng_config &= ~TRNG_CTL_CONDRST;
    trng_config |= TRNG_CTL_TRNGEN;
    TRNG_CTL = trng_config;
}

/*!
    \brief      disable the TRNG interface
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_disable(void)
{
    TRNG_CTL &= ~TRNG_CTL_TRNGEN;
}

/*!
    \brief      lock the TRNG control bits
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_lock(void)
{
    TRNG_CTL |= TRNG_CTL_LK;
}

/*!
    \brief      configure TRNG working mode
    \param[in]  mode_select: the TRNG working mode
                only one parameter can be selected which is shown as below:
      \arg        TRNG_MODSEL_LFSR: TRNG working in LFSR mode
      \arg        TRNG_MODSEL_NIST: TRNG working in NIST mode
    \param[out] none
    \retval     none
*/
void trng_mode_config(trng_modsel_enum mode_select)
{
    uint32_t trng_config = TRNG_CTL;

    trng_config &= ~TRNG_CTL_MODSEL;
    trng_config |= mode_select;
    TRNG_CTL = trng_config;
}

/*!
    \brief      enable the TRNG post-processing module
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_postprocessing_enable(void)
{
    TRNG_CTL |= TRNG_CTL_PPEN;
}

/*!
    \brief      disable the TRNG post-processing module
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_postprocessing_disable(void)
{
    TRNG_CTL &= ~TRNG_CTL_PPEN;
}

/*!
    \brief      enable the TRNG conditioning module
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_conditioning_enable(void)
{
    TRNG_CTL |= TRNG_CTL_CONDEN;
}

/*!
    \brief      disable the TRNG conditioning module
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_conditioning_disable(void)
{
    TRNG_CTL &= ~TRNG_CTL_CONDEN;
}

/*!
    \brief      configure TRNG conditioning module input bitwidth
    \param[in]  input_bitwidth: the input bit width
                only one parameter can be selected which is shown as below:
      \arg        TRNG_INMOD_256BIT: conditioning module input bitwidth 256bits
      \arg        TRNG_INMOD_440BIT: conditioning module input bitwidth 440bits
    \param[out] none
    \retval     none
*/
void trng_conditioning_input_bitwidth(trng_inmod_enum input_bitwidth)
{
    uint32_t trng_config = TRNG_CTL;

    trng_config &= ~TRNG_CTL_INMOD;
    trng_config |= input_bitwidth;
    TRNG_CTL = trng_config;
}

/*!
    \brief      configure TRNG conditioning module output bitwidth
    \param[in]  output_bitwidth:
                only one parameter can be selected which is shown as below:
      \arg        TRNG_OUTMOD_128BIT: conditioning module output bitwidth 128bits
      \arg        TRNG_OUTMOD_256BIT: conditioning module output bitwidth 256bits
    \param[out] none
    \retval     none
*/
void trng_conditioning_output_bitwidth(trng_outmod_enum output_bitwidth)
{
    uint32_t trng_config = TRNG_CTL;

    trng_config &= ~TRNG_CTL_OUTMOD;
    trng_config |= (uint32_t)output_bitwidth;
    TRNG_CTL = trng_config;
}

/*!
    \brief      enable TRNG replace test
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_replace_test_enable(void)
{
    TRNG_CTL |= TRNG_CTL_RTEN;
}

/*!
    \brief      disable TRNG replace test
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_replace_test_disable(void)
{
    TRNG_CTL &= ~TRNG_CTL_RTEN;
}

/*!
    \brief      enable hash algorithm init when conditioning module enabled
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_hash_init_enable(void)
{
    TRNG_CTL |= TRNG_CTL_INIT;
}

/*!
    \brief      disable hash algorithm init when conditioning module enabled
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_hash_init_disable(void)
{
    TRNG_CTL &= ~TRNG_CTL_INIT;
}

/*!
    \brief      configure TRNG analog power mode
    \param[in]  powermode: the power mode selection
                only one parameter can be selected which is shown as below:
      \arg        TRNG_NR_ULTRALOW: TRNG analog power mode ultralow
      \arg        TRNG_NR_LOW:      TRNG analog power mode low
      \arg        TRNG_NR_MEDIUM:   TRNG analog power mode medium
      \arg        TRNG_NR_HIGH:     TRNG analog power mode high
    \param[out] none
    \retval     none
*/
void trng_powermode_config(uint32_t powermode)
{
    uint32_t trng_config = TRNG_CTL;

    trng_config &= ~TRNG_CTL_NR;
    trng_config |= powermode;
    TRNG_CTL = trng_config;
}

/*!
    \brief      configure TRNG clock divider
    \param[in]  clkdiv: TRNG clock divider
                only one parameter can be selected which is shown as below:
      \arg        TRNG_CLK_DIVx (x=1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768)
    \param[out] none
    \retval     none
*/
void trng_clockdiv_config(uint32_t clkdiv)
{
    uint32_t trng_config = TRNG_CTL;

    trng_config &= ~TRNG_CTL_CLKDIV;
    trng_config |= clkdiv;
    TRNG_CTL = trng_config;
}

/*!
    \brief      enable the TRNG clock error detection
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_clockerror_detection_enable(void)
{
    TRNG_CTL |= TRNG_CTL_CED;
}

/*!
    \brief      disable the TRNG clock error detection
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_clockerror_detection_disable(void)
{
    TRNG_CTL &= ~TRNG_CTL_CED;
}

/*!
    \brief      get the true random data
    \param[in]  none
    \param[out] none
    \retval     the generated random data
*/
uint32_t trng_get_true_random_data(void)
{
    return (TRNG_DATA);
}

/*!
    \brief      enable the conditioning logic reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_conditioning_reset_enable(void)
{
    TRNG_CTL |= TRNG_CTL_CONDRST;
}

/*!
    \brief      disable the conditioning logic reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_conditioning_reset_disable(void)
{
    TRNG_CTL &= ~TRNG_CTL_CONDRST;
}

/*!
    \brief      configure the conditioning module hash algorithm
    \param[in]  module_algo: module hash algorithm
                only one parameter can be selected which is shown as below:
      \arg        TRNG_ALGO_SHA1:   TRNG conditioning module hash SHA1
      \arg        TRNG_ALGO_MD5:    TRNG conditioning module hash MD5
      \arg        TRNG_ALGO_SHA224: TRNG conditioning module hash SHA224
      \arg        TRNG_ALGO_SHA256: TRNG conditioning module hash SHA256
    \param[out] none
    \retval     none
*/
void trng_conditioning_algo_config(uint32_t module_algo)
{
    uint32_t tmp = TRNG_CTL;

    tmp &= ~(TRNG_CTL_ALGO);
    tmp |= module_algo;
    TRNG_CTL = tmp;
}

/*!
    \brief      configure health tests default value
    \param[in]  adpo_threshold: adaptive proportion test threshold value
    \param[in]  rep_threshold: repetitive (00/11) test threshold value
    \param[out] none
    \retval     none
*/
void trng_health_tests_config(uint32_t adpo_threshold, uint8_t rep_threshold)
{
    uint32_t tmp = TRNG_HTCFG;

    tmp &= ~(TRNG_HTCFG_APTTH | TRNG_HTCFG_RCTTH);
    tmp |= (((uint32_t)(adpo_threshold << 16U) & TRNG_HTCFG_APTTH) | (rep_threshold & TRNG_HTCFG_RCTTH));
    TRNG_HTCFG = tmp;
}

/*!
    \brief      get the TRNG status flags
    \param[in]  flag: TRNG status flag, refer to trng_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        TRNG_FLAG_DRDY: random data ready status
      \arg        TRNG_FLAG_CECS: clock error current status
      \arg        TRNG_FLAG_SECS: seed error current status
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus trng_flag_get(trng_flag_enum flag)
{
    if(RESET != (TRNG_STAT & flag))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      enable the TRNG interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_interrupt_enable(void)
{
    TRNG_CTL |= TRNG_CTL_IE;
}

/*!
    \brief      disable the TRNG interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_interrupt_disable(void)
{
    TRNG_CTL &= ~TRNG_CTL_IE;
}

/*!
    \brief      get the TRNG interrupt flags
    \param[in]  int_flag: TRNG interrupt flag, refer to trng_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        TRNG_INT_FLAG_CEIF: clock error interrupt flag
      \arg        TRNG_INT_FLAG_SEIF: seed error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus trng_interrupt_flag_get(trng_int_flag_enum int_flag)
{
    if(RESET != (TRNG_STAT & int_flag))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear the TRNG interrupt flags
    \param[in]  int_flag: TRNG interrupt flag, refer to trng_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        TRNG_INT_FLAG_CEIF: clock error interrupt flag
      \arg        TRNG_INT_FLAG_SEIF: seed error interrupt flag
    \param[out] none
    \retval     none
*/
void trng_interrupt_flag_clear(trng_int_flag_enum int_flag)
{
    TRNG_STAT &= ~(uint32_t)int_flag;
}
