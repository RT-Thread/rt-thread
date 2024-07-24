/*!
    \file    gd32h7xx_crc.c
    \brief   CRC driver

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

#include "gd32h7xx_crc.h"

#define CRC_IDATA_RESET_VALUE     ((uint32_t)0xFFFFFFFFU)
#define CRC_DATA_RESET_VALUE      ((uint32_t)0xFFFFFFFFU)
#define CRC_FDATA_RESET_VALUE     ((uint32_t)0x00000000U)
#define CRC_POLY_RESET_VALUE      ((uint32_t)0x04C11DB7U)

/*!
    \brief      deinit CRC calculation unit
    \param[in]  none
    \param[out] none
    \retval     none
*/
void crc_deinit(void)
{
    CRC_IDATA = CRC_IDATA_RESET_VALUE;
    CRC_DATA  = CRC_DATA_RESET_VALUE;
    CRC_FDATA = CRC_FDATA_RESET_VALUE;
    CRC_POLY  = CRC_POLY_RESET_VALUE;
    CRC_CTL   = (uint32_t)CRC_CTL_RST;
}

/*!
    \brief      enable the reverse operation of output data
    \param[in]  none
    \param[out] none
    \retval     none
*/
void crc_reverse_output_data_enable(void)
{
    CRC_CTL &= (uint32_t)(~CRC_CTL_REV_O);
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
    CRC_CTL &= (uint32_t)(~CRC_CTL_REV_O);
}

/*!
    \brief      reset data register to the value of initialization data register
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
    \brief      write the initialization data register
    \param[in]  init_data:specify 32-bit data
    \param[out] none
    \retval     none
*/
void crc_init_data_register_write(uint32_t init_data)
{
    CRC_IDATA = init_data;
}

/*!
    \brief      configure the CRC input data function
    \param[in]  data_reverse: specify input data reverse function
                only one parameter can be selected which is shown as below:
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
                only one parameter can be selected which is shown as below:
      \arg        CRC_CTL_PS_32: 32-bit polynomial for CRC calculation
      \arg        CRC_CTL_PS_16: 16-bit polynomial for CRC calculation
      \arg        CRC_CTL_PS_8: 8-bit polynomial for CRC calculation
      \arg        CRC_CTL_PS_7: 7-bit polynomial for CRC calculation
    \param[out] none
    \retval     none
*/
void crc_polynomial_size_set(uint32_t poly_size)
{
    CRC_CTL &= (uint32_t)(~CRC_CTL_PS);
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
    \brief      CRC calculate single data
    \param[in]  sdata: specify input data
    \param[in]  data_format: input data format
                only one parameter can be selected which is shown as below:
      \arg        INPUT_FORMAT_WORD: input data in word format
      \arg        INPUT_FORMAT_HALFWORD: input data in half-word format
      \arg        INPUT_FORMAT_BYTE: input data in byte format
    \param[out] none
    \retval     CRC calculate value
*/
uint32_t crc_single_data_calculate(uint32_t sdata, uint8_t data_format)
{
    if(INPUT_FORMAT_WORD == data_format)
    {
        REG32(CRC) = sdata;
    } else if(INPUT_FORMAT_HALFWORD == data_format)
    {
        REG16(CRC) = (uint16_t)sdata;
    } else if(INPUT_FORMAT_BYTE == data_format)
    {
        REG8(CRC) = (uint8_t)sdata;
    } else {
    }

    return(CRC_DATA);
}

/*!
    \brief      CRC calculate a data array
    \param[in]  array: pointer to the input data array
    \param[in]  size: size of the array
    \param[in]  data_format: input data format
                only one parameter can be selected which is shown as below:
      \arg        INPUT_FORMAT_WORD: input data in word format
      \arg        INPUT_FORMAT_HALFWORD: input data in half-word format
      \arg        INPUT_FORMAT_BYTE: input data in byte format
    \param[out] none
    \retval     CRC calculate value
*/
uint32_t crc_block_data_calculate(void *array, uint32_t size, uint8_t data_format)
{
    uint8_t *data8;
    uint16_t *data16;
    uint32_t *data32;
    uint32_t index;

    if(INPUT_FORMAT_WORD == data_format)
    {
        data32 = (uint32_t *)array;
        for(index = 0U; index < size; index++)
        {
            REG32(CRC) = data32[index];
        }
    } else if(INPUT_FORMAT_HALFWORD == data_format)
    {
        data16 = (uint16_t *)array;
        for(index = 0U; index < size; index++)
        {
            REG16(CRC) = data16[index];
        }
    } else {
        data8 = (uint8_t *)array;
        for(index = 0U; index < size; index++)
        {
            REG8(CRC) = data8[index];
        }
    }

    return (CRC_DATA);
}
