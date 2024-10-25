/*!
    \file    gd32e50x_sqpi.c
    \brief   SQPI driver

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

#include "gd32e50x_sqpi.h"

/*!
    \brief      reset SQPI
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sqpi_deinit(void)
{
    rcu_periph_reset_enable(RCU_SQPIRST);
    rcu_periph_reset_disable(RCU_SQPIRST);
}

/*!
    \brief      initialize the parameters of SQPI struct with the default values
    \param[in]  sqpi_struct: SQPI parameter stuct
    \param[out] none
    \retval     none
*/
void sqpi_struct_para_init(sqpi_parameter_struct* sqpi_struct)
{
    /* set the SQPI struct with the default values */
    sqpi_struct->polarity = SQPI_SAMPLE_POLARITY_RISING;
    sqpi_struct->id_length = SQPI_ID_LENGTH_32_BITS;
    sqpi_struct->addr_bit = 24U;
    sqpi_struct->clk_div = 2U;
    sqpi_struct->cmd_bit = SQPI_CMDBIT_8_BITS;
}

/*!
    \brief      initialize SQPI parameter
    \param[in]  sqpi_struct: SQPI parameter initialization stuct members of the structure
                            and the member values are shown as below:
                  polarity: SQPI_SAMPLE_POLARITY_RISING, SQPI_SAMPLE_POLARITY_FALLING
                  id_length: SQPI_ID_LENGTH_n_BITS (n=8,16,32,64)
                  addr_bit: 0x00 - 0x1F
                  clk_div: 0x01 - 0x3F
                  cmd_bit: SQPI_CMDBIT_n_BITS (n=4,8,16)
    \param[out] none
    \retval     none
*/
void sqpi_init(sqpi_parameter_struct *sqpi_struct)
{
    __IO uint32_t temp = 0U;

    temp |= ((sqpi_struct->polarity)|sqpi_struct->id_length|sqpi_struct->cmd_bit);
    temp |= ((sqpi_struct->addr_bit << 24U) | sqpi_struct->clk_div << 18U);
    SQPI_INIT = temp;
}

/*!
    \brief      send SQPI read ID command
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sqpi_read_id_command(void)
{
    while((SQPI_RCMD & SQPI_RCMD_RID) != RESET)
    {
    }

    SQPI_RCMD |=  SQPI_RCMD_RID;

    while((SQPI_RCMD & SQPI_RCMD_RID) != RESET)
    {
    }
}

/*!
    \brief      send SQPI special command
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sqpi_special_command(void)
{
    while((SQPI_WCMD & SQPI_WCMD_SCMD) != RESET)
    {
    }

    SQPI_WCMD |=  SQPI_WCMD_SCMD;

    while((SQPI_WCMD & SQPI_WCMD_SCMD) != RESET)
    {
    }
}

/*!
    \brief      configure SQPI read command
    \param[in]  rmode: SQPI_MODE_SSQ, SQPI_MODE_SSS, SQPI_MODE_SQQ, SQPI_MODE_QQQ, SQPI_MODE_SSD, SQPI_MODE_SDD
                rwaitcycle: 0x00 - 0x1F
                rcmd: 0x00 - 0xFF
    \param[out] none
    \retval     none
*/
void sqpi_read_command_config(uint32_t rmode, uint32_t rwaitcycle, uint32_t rcmd)
{
    __IO uint32_t temp = 0U;
    temp |= (rcmd | (rwaitcycle << 16U) | rmode);
    SQPI_RCMD = temp;
}

/*!
    \brief      configure SQPI write command
    \param[in]  wmode: SQPI_MODE_SSQ, SQPI_MODE_SSS, SQPI_MODE_SQQ, SQPI_MODE_QQQ, SQPI_MODE_SSD, SQPI_MODE_SDD
                wwaitcycle: 0x00 - 0x1F
                wcmd: 0x00 - 0xFF
    \param[out] none
    \retval     none
*/
void sqpi_write_command_config(uint32_t wmode, uint32_t wwaitcycle, uint32_t wcmd)
{
    __IO uint32_t temp = 0U;
    temp |= (wcmd | (wwaitcycle << 16U) | wmode);
    SQPI_WCMD = temp;
}

/*!
    \brief      SQPI receive low ID
    \param[in]  none
    \param[out] none
    \retval     32-bit low ID
*/
uint32_t sqpi_low_id_receive(void)
{
    __IO uint32_t temp = 0U;
    temp = SQPI_IDL;
    return temp;
}

/*!
    \brief      SQPI receive high ID
    \param[in]  none
    \param[out] none
    \retval     32-bit high ID
*/
uint32_t sqpi_high_id_receive(void)
{
    __IO uint32_t temp = 0U;
    temp = SQPI_IDH;
    return temp;
}
