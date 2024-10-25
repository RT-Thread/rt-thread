/*!
    \file    gd32e50x_tmu.c
    \brief   TMU driver

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

#include "gd32e50x_tmu.h"

#if defined(GD32E50X_CL) || defined(GD32E508)

/*!
    \brief      reset the TMU
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_deinit(void)
{
    /* reset TMU */
    rcu_periph_reset_enable(RCU_TMURST);
    rcu_periph_reset_disable(RCU_TMURST);
}

/*!
    \brief      enable the TMU
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_enable(void)
{
    TMU_CTL |= (uint32_t)TMU_CTL_TMUEN;
}

/*!
    \brief      configure the TMU mode
    \param[in]  modex: the operation mode of TMU
      \arg        TMU_MODE0: the operation mode0
      \arg        TMU_MODE1: the operation mode1
      \arg        TMU_MODE2: the operation mode2
      \arg        TMU_MODE2: the operation mode3
      \arg        TMU_MODE2: the operation mode4
      \arg        TMU_MODE1: the operation mode5
      \arg        TMU_MODE2: the operation mode6
      \arg        TMU_MODE2: the operation mode7
      \arg        TMU_MODE2: the operation mode8
    \param[out] none
    \retval     none
*/
void tmu_mode_set(uint32_t modex)
{
    TMU_CTL &= (uint32_t)(~ TMU_CTL_MODE);
    TMU_CTL |= (uint32_t)modex;

}

/*!
    \brief      write the data to TMU input data0 regisetr
    \param[in]  idata0: the value write to input data0
                idata0 must meet IEEE 32-Bit Single Precision Floating-Point Format.
    \param[out] none
    \retval     none
*/
void tmu_idata0_write(uint32_t idata0)
{
    TMU_IDATA0 &= (uint32_t)(~ TMU_IDATA0_IDATA0);
    TMU_IDATA0 = idata0;
}

/*!
    \brief      write the data to TMU input data1 regisetr
    \param[in]  idata1: the value write to input data1(idata1 only uesed for MODE6,MODE7,MODE8)
                idata1 must meet IEEE 32-Bit Single Precision Floating-Point Format
    \param[out] none
    \retval     none
*/
void tmu_idata1_write(uint32_t idata1)
{
    TMU_IDATA1 &= (uint32_t)(~ TMU_IDATA1_IDATA1);
    TMU_IDATA1 = idata1;
}

/*!
    \brief      read the data from TMU data0 regisetr
    \param[in]  none
    \param[out] none
    \retval     32-bit value of the data0 register.
                the value of data0 register meet IEEE 32-Bit Single Precision Floating-Point Format
*/
uint32_t tmu_data0_read(void)
{
    uint32_t data0;
    data0 = TMU_DATA0;
    return (data0);
}

/*!
    \brief      read the data from TMU data1 regisetr
    \param[in]  none
    \param[out] none
    \retval     32-bit value of the data1 register.
                the value of data1 register meet IEEE 32-Bit Single Precision Floating-Point Format
*/
uint32_t tmu_data1_read(void)
{
    uint32_t data1;
    data1 = TMU_DATA1;
    return (data1);
}

/*!
    \brief      enable TMU interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_interrupt_enable(void)
{
    TMU_CTL &= (uint32_t)(~ TMU_CTL_CFIE);
    TMU_CTL |= (uint32_t)TMU_CTL_CFIE;
}

/*!
    \brief      disable TMU interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_interrupt_disable(void)
{
    TMU_CTL &= (uint32_t)(~ TMU_CTL_CFIE);
}

/*!
    \brief      check the TMU status flag
    \param[in]  flag: teh TMU status flag
                only one parameter can be selected which is shown as below:
      \arg        TMU_FLAG_OVRF: the flag of TMU overflow
      \arg        TMU_FLAG_UDRF: the flag of TMU underflow
    \param[out] none
    \retval     none
*/
FlagStatus tmu_flag_get(uint32_t flag)
{
    if(TMU_STAT & flag)
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      check teh TMU interrupt flag
    \param[in]  int_flag: teh TMU interrupt flag
      \arg        TMU_INT_FLAG_CFIF: the interrupt flag of calculation finished
    \param[out] none
    \retval     none
*/
FlagStatus tmu_interrupt_flag_get(uint32_t int_flag)
{
    uint32_t reg = TMU_CTL;
    if(reg & TMU_CTL_CFIE)
    {
        return SET;
    }else{
        return RESET;
    }
}

#endif /* GD32E50x_CL and GD32E508 */
