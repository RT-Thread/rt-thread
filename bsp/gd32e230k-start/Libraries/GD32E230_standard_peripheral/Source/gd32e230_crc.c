/*!
    \file    gd32e230_crc.c
    \brief   CRC driver
    
    \version 2018-06-19, V1.0.0, firmware for GD32E230
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#include "gd32e230_crc.h"

/*!
    \brief      deinit CRC calculation unit
    \param[in]  none
    \param[out] none
    \retval     none
*/
void crc_deinit(void)
{
    CRC_IDATA = (uint32_t)0xFFFFFFFFU;
    CRC_DATA  = (uint32_t)0xFFFFFFFFU;
    CRC_FDATA = (uint32_t)0x00000000U;
    CRC_POLY  = (uint32_t)0x04C11DB7U;
    CRC_CTL   = CRC_CTL_RST;   
}

/*!
    \brief      enable the reverse operation of output data
    \param[in]  none
    \param[out] none
    \retval     none
*/
void crc_reverse_output_data_enable(void)
{
    CRC_CTL &= (uint32_t)(~ CRC_CTL_REV_O);
    CRC_CTL |= (uint32_t)CRC_CTL_REV_O;
}

/*!
    \brief      disable the reverse operation of output data
    \param[in]  none
    \param[out] none
    \retval     none
*/
void crc_reverse_output_data_disable(void)
{
    CRC_CTL &= (uint32_t)(~ CRC_CTL_REV_O);
}

/*!
    \brief      reset data register to the value of initializaiton data register
    \param[in]  none
    \param[out] none
    \retval     none
*/
void crc_data_register_reset(void)
{
    CRC_CTL |= (uint32_t)CRC_CTL_RST;
}

/*!
    \brief      read the data register 
    \param[in]  none
    \param[out] none
    \retval     32-bit value of the data register
*/
uint32_t crc_data_register_read(void)
{
    uint32_t data;
    data = CRC_DATA;
    return (data);
}

/*!
    \brief      read the free data register
    \param[in]  none
    \param[out] none
    \retval     8-bit value of the free data register
*/
uint8_t crc_free_data_register_read(void)
{
    uint8_t fdata;
    fdata = (uint8_t)CRC_FDATA;
    return (fdata);
}

/*!
    \brief      write the free data register
    \param[in]  free_data: specify 8-bit data
    \param[out] none
    \retval     none
*/
void crc_free_data_register_write(uint8_t free_data)
{
    CRC_FDATA = (uint32_t)free_data;
}

/*!
    \brief      write the initializaiton data register
    \param[in]  init_data:specify 32-bit data
    \param[out] none
    \retval     none
*/
void crc_init_data_register_write(uint32_t init_data)
{
    CRC_IDATA = (uint32_t)init_data;
}

/*!
    \brief      configure the CRC input data function
    \param[in]  data_reverse: specify input data reverse function
      \arg        CRC_INPUT_DATA_NOT: input data is not reversed
      \arg        CRC_INPUT_DATA_BYTE: input data is reversed on 8 bits
      \arg        CRC_INPUT_DATA_HALFWORD: input data is reversed on 16 bits
      \arg        CRC_INPUT_DATA_WORD: input data is reversed on 32 bits
    \param[out] none
    \retval     none
*/
void crc_input_data_reverse_config(uint32_t data_reverse)
{
    CRC_CTL &= (uint32_t)(~CRC_CTL_REV_I);
    CRC_CTL |= (uint32_t)data_reverse;
}

/*!
    \brief      configure the CRC size of polynomial function
    \param[in]  poly_size: size of polynomial
      \arg        CRC_CTL_PS_32: 32-bit polynomial for CRC calculation
      \arg        CRC_CTL_PS_16: 16-bit polynomial for CRC calculation
      \arg        CRC_CTL_PS_8: 8-bit polynomial for CRC calculation
      \arg        CRC_CTL_PS_7: 7-bit polynomial for CRC calculation
    \param[out] none
    \retval     none
*/
void crc_polynomial_size_set(uint32_t poly_size)
{
    CRC_CTL &= (uint32_t)(~(CRC_CTL_PS));
    CRC_CTL |= (uint32_t)poly_size;
}

/*!
    \brief      configure the CRC polynomial value function
    \param[in]  poly: configurable polynomial value
    \param[out] none
    \retval     none
*/
void crc_polynomial_set(uint32_t poly)
{
    CRC_POLY &= (uint32_t)(~CRC_POLY_POLY);
    CRC_POLY = poly;
}

/*!
    \brief      CRC calculate a 32-bit data
    \param[in]  sdata: specify 32-bit data
    \param[out] none
    \retval     32-bit CRC calculate value
*/
uint32_t crc_single_data_calculate(uint32_t sdata)
{
    CRC_DATA = sdata;
    return(CRC_DATA);
}

/*!
    \brief      CRC calculate a 32-bit data array
    \param[in]  array: pointer to an array of 32 bit data words
    \param[in]  size: size of the array
    \param[out] none
    \retval     32-bit CRC calculate value
*/
uint32_t crc_block_data_calculate(uint32_t array[], uint32_t size)
{  
    uint32_t index;
    for(index = 0U; index < size; index++){
        CRC_DATA = array[index];
    }
    return (CRC_DATA);    
}
