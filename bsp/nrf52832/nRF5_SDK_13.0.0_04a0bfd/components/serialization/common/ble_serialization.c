/**
 * Copyright (c) 2013 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include "ble_serialization.h"
#include "nrf_error.h"
#include "app_util.h"
#include <stddef.h>
#include <string.h>

uint32_t ser_ble_cmd_rsp_status_code_enc(uint8_t          op_code,
                                         uint32_t         command_status,
                                         uint8_t * const  p_buf,
                                         uint32_t * const p_buf_len)
{
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_buf_len);
    uint32_t index = 0;

    SER_ASSERT_LENGTH_LEQ(SER_CMD_RSP_HEADER_SIZE, *p_buf_len);

    //Encode Op Code.
    p_buf[index++] = op_code;

    //Encode Status.
    index     += uint32_encode(command_status, &(p_buf[index]));
    *p_buf_len = index;

    return NRF_SUCCESS;
}


uint32_t ser_ble_cmd_rsp_result_code_dec(uint8_t const * const p_buf,
                                         uint32_t * const      p_pos,
                                         uint32_t              packet_len,
                                         uint8_t               op_code,
                                         uint32_t * const      p_result_code)
{
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_pos);
    SER_ASSERT_NOT_NULL(p_result_code);

    if (packet_len < SER_CMD_RSP_HEADER_SIZE)
    {
        return NRF_ERROR_DATA_SIZE;
    }

    if (p_buf[(*p_pos)] != op_code)
    {
        return NRF_ERROR_INVALID_DATA;
    }

    *p_result_code = uint32_decode(&(p_buf[(*p_pos) + SER_CMD_RSP_STATUS_CODE_POS]));
    *p_pos        += SER_CMD_RSP_HEADER_SIZE;

    return NRF_SUCCESS;
}


uint32_t ser_ble_cmd_rsp_dec(uint8_t const * const p_buf,
                             uint32_t              packet_len,
                             uint8_t               op_code,
                             uint32_t * const      p_result_code)
{
    uint32_t index       = 0;
    uint32_t result_code = ser_ble_cmd_rsp_result_code_dec(p_buf, &index, packet_len, op_code,
                                                           p_result_code);

    if (result_code != NRF_SUCCESS)
    {
        return result_code;
    }

    if (index != packet_len)
    {
        return NRF_ERROR_DATA_SIZE;
    }

    return NRF_SUCCESS;
}

uint32_t uint32_t_enc(void const * const p_field,
                      uint8_t * const    p_buf,
                      uint32_t           buf_len,
                      uint32_t * const   p_index)
{
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_field);
    SER_ASSERT_NOT_NULL(p_index);

    uint32_t * p_uint32 = (uint32_t *)p_field;

    SER_ASSERT_LENGTH_LEQ(4, buf_len - *p_index);

    *p_index += uint32_encode(*p_uint32, &p_buf[*p_index]);

    return NRF_SUCCESS;
}

uint32_t uint32_t_dec(uint8_t const * const p_buf,
                      uint32_t              buf_len,
                      uint32_t * const      p_index,
                      void *                p_field)
{
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_index);
    SER_ASSERT_NOT_NULL(p_field);

    uint32_t * p_uint32 = (uint32_t *)p_field;

    SER_ASSERT_LENGTH_LEQ(4, ((int32_t)buf_len - *p_index));

    *p_uint32 = uint32_decode(&p_buf[*p_index]);
    *p_index += 4;

    return NRF_SUCCESS;
}

uint32_t uint16_t_enc(const void * const p_field,
                      uint8_t * const    p_buf,
                      uint32_t           buf_len,
                      uint32_t * const   p_index)
{
    uint16_t * p_u16 = (uint16_t *)p_field;

    SER_ASSERT_LENGTH_LEQ(2, buf_len - *p_index);

    *p_index += uint16_encode(*p_u16, &p_buf[*p_index]);

    return NRF_SUCCESS;
}

uint32_t uint16_t_dec(uint8_t const * const p_buf,
                      uint32_t              buf_len,
                      uint32_t * const      p_index,
                      void *                p_field)
{
    uint16_t * p_u16 = (uint16_t *)p_field;

    SER_ASSERT_LENGTH_LEQ(2, ((int32_t)buf_len - *p_index));

    *p_u16    = uint16_decode(&p_buf[*p_index]);
    *p_index += 2;

    return NRF_SUCCESS;
}

void uint16_dec(uint8_t const * const p_buf,
                uint32_t              buf_len,
                uint32_t * const      index,
                uint16_t * const      value)
{
    SER_ASSERT_VOID_RETURN(*index + 2 <= buf_len);
    *value  = uint16_decode(&p_buf[*index]);
    *index += 2;
}

uint32_t uint8_t_enc(const void * const p_field,
                     uint8_t * const    p_buf,
                     uint32_t           buf_len,
                     uint32_t * const   p_index)
{
    SER_ASSERT_LENGTH_LEQ(1, buf_len - *p_index);

    uint8_t * p_u8 = (uint8_t *)p_field;
    p_buf[*p_index] = *p_u8;
    *p_index       += 1;

    return NRF_SUCCESS;
}

uint32_t uint8_t_dec(uint8_t const * const p_buf,
                     uint32_t              buf_len,
                     uint32_t * const      p_index,
                     void *                p_field)
{
    uint8_t * p_u8 = (uint8_t *)p_field;

    SER_ASSERT_LENGTH_LEQ(1, ((int32_t)buf_len - *p_index));
    *p_u8     = p_buf[*p_index];
    *p_index += 1;

    return NRF_SUCCESS;
}

void uint8_dec(uint8_t const * const p_buf,
               uint32_t              buf_len,
               uint32_t * const      index,
               uint8_t * const       value)
{
    SER_ASSERT_VOID_RETURN(*index + 1 <= buf_len);
    *value  = p_buf[*index];
    *index += 1;
}


void int8_dec(uint8_t const * const p_buf,
              uint32_t              buf_len,
              uint32_t * const      index,
              int8_t * const        value)
{
    SER_ASSERT_VOID_RETURN(*index + 1 <= buf_len);
    *value  = p_buf[*index];
    *index += 1;
}

uint32_t len8data_enc(uint8_t const * const p_data,
                      uint8_t const         dlen,
                      uint8_t * const       p_buf,
                      uint32_t              buf_len,
                      uint32_t * const      p_index)
{
    uint32_t err_code = NRF_SUCCESS;

    err_code = uint8_t_enc(&dlen, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = buf_enc(p_data, dlen, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t len8data_dec(uint8_t const * const p_buf,
                      uint32_t              buf_len,
                      uint32_t * const      p_index,
                      uint8_t * * const     pp_data,
                      uint8_t * const       p_len)
{
    uint32_t err_code    = NRF_SUCCESS;
    uint16_t out_buf_len = *p_len;

    err_code = uint8_t_dec(p_buf, buf_len, p_index, p_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = buf_dec(p_buf, buf_len, p_index, pp_data, out_buf_len, *p_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t len16data_enc(uint8_t const * const p_data,
                       uint16_t const        dlen,
                       uint8_t * const       p_buf,
                       uint32_t              buf_len,
                       uint32_t * const      p_index)
{
    uint32_t err_code = NRF_SUCCESS;

    err_code = uint16_t_enc(&dlen, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = buf_enc(p_data, dlen, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t len16data_dec(uint8_t const * const p_buf,
                       uint32_t              buf_len,
                       uint32_t * const      p_index,
                       uint8_t * * const     pp_data,
                       uint16_t * const      p_dlen)
{
    uint32_t err_code    = NRF_SUCCESS;
    uint16_t out_buf_len = *p_dlen;

    err_code = uint16_t_dec(p_buf, buf_len, p_index, p_dlen);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = buf_dec(p_buf, buf_len, p_index, pp_data, out_buf_len, *p_dlen);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t count16_cond_data16_enc(uint16_t const * const p_data,
                                 uint16_t const         count,
                                 uint8_t * const        p_buf,
                                 uint32_t               buf_len,
                                 uint32_t * const       p_index)
{
    uint32_t i = 0;

    SER_ASSERT_LENGTH_LEQ(3, ((int32_t)buf_len - *p_index));
    *p_index += uint16_encode(count, &p_buf[*p_index]);

    if (p_data)
    {
        SER_ASSERT_LENGTH_LEQ((int32_t)(2 * count + 1), ((int32_t)buf_len - (int32_t) * p_index));
        p_buf[*p_index] = SER_FIELD_PRESENT;
        *p_index       += 1;

        //memcpy may fail in case of Endianness difference between application and connectivity processor
        for (i = 0; i < count; i++)
        {
            *p_index += uint16_encode(p_data[i], &p_buf[*p_index]);
        }
    }
    else
    {
        SER_ASSERT_LENGTH_LEQ((1), ((int32_t)buf_len - *p_index));
        p_buf[*p_index] = SER_FIELD_NOT_PRESENT;
        *p_index       += 1;
    }

    return NRF_SUCCESS;
}

uint32_t count16_cond_data16_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 uint16_t * * const    pp_data,
                                 uint16_t * const      p_count)

{
    uint16_t count      = 0;
    uint8_t  is_present = 0;
    uint16_t i;

    SER_ASSERT_NOT_NULL(p_count);
    SER_ASSERT_NOT_NULL(pp_data);
    SER_ASSERT_NOT_NULL(*pp_data);

    SER_ASSERT_LENGTH_LEQ(3, ((int32_t)buf_len - (*p_index)));

    uint16_dec(p_buf, buf_len, p_index, &count);

    if (count > *p_count)
    {
        return NRF_ERROR_DATA_SIZE;
    }

    SER_ASSERT_LENGTH_LEQ(count, *p_count);

    uint8_dec(p_buf, buf_len, p_index, &is_present);

    if (!is_present)
    {
        *p_count = count;
        *pp_data = NULL;
        return NRF_SUCCESS;
    }
    else
    {
        for (i = 0; i < count; i++ )
        {
            uint16_dec(p_buf, buf_len, p_index, &((&(**pp_data))[i]) );
        }
        *p_count = i;
    }
    return NRF_SUCCESS;
}



uint32_t cond_len16_cond_data_dec(uint8_t const * const p_buf,
                                  uint32_t              buf_len,
                                  uint32_t * const      p_index,
                                  uint8_t * * const     pp_data,
                                  uint16_t * * const    pp_len)
{
    SER_ASSERT_NOT_NULL(pp_len);
    SER_ASSERT_NOT_NULL(*pp_len);
    SER_ASSERT_NOT_NULL(pp_data);
    SER_ASSERT_NOT_NULL(*pp_data);

    SER_ASSERT_LENGTH_LEQ(2, ((int32_t)buf_len - (*p_index)));
    uint8_t is_present = 0;

    uint8_dec(p_buf, buf_len, p_index, &is_present);

    if (!is_present)
    {
        *pp_len = NULL; //if length field is not present
        (*p_index)++;   //then data can not be present
        *pp_data = NULL;
        return NRF_SUCCESS;
    }
    else
    {
        return len16data_dec(p_buf, buf_len, p_index, pp_data, *pp_len);
    }
}

uint32_t op_status_enc(uint8_t          op_code,
                       uint32_t         return_code,
                       uint8_t * const  p_buff,
                       uint32_t * const p_buff_len,
                       uint32_t * const p_index)
{
    SER_ASSERT_NOT_NULL(p_buff);
    SER_ASSERT_NOT_NULL(p_buff_len);
    SER_ASSERT_NOT_NULL(p_index);
    SER_ASSERT_LENGTH_LEQ(SER_CMD_RSP_HEADER_SIZE, *p_buff_len - *p_index);

    //Encode Op Code.
    p_buff[(*p_index)++] = op_code;
    //Encode Status.
    *p_index += uint32_encode(return_code, &(p_buff[*p_index]));
    //update size of used buffer
    *p_buff_len = *p_index;

    return NRF_SUCCESS;
}

uint32_t op_status_cond_uint16_enc(uint8_t          op_code,
                                   uint32_t         return_code,
                                   uint16_t         value,
                                   uint8_t * const  p_buff,
                                   uint32_t * const p_buff_len,
                                   uint32_t * const p_index)
{
    uint32_t status_code;
    uint32_t init_buff_len = *p_buff_len;

    status_code = op_status_enc(op_code, return_code, p_buff, p_buff_len, p_index);
    SER_ASSERT(status_code == NRF_SUCCESS, status_code);

    if (return_code == NRF_SUCCESS) //Add 16bit value when return_code is a success
    {
        *p_buff_len = init_buff_len; //restore original value - it has been modified by op_status_enc
        status_code = uint16_t_enc(&value, p_buff, *p_buff_len, p_index);
        *p_buff_len = *p_index;
        SER_ASSERT(status_code == NRF_SUCCESS, status_code);
    }

    return status_code;
}

uint32_t buf_enc(uint8_t const * const p_data,
                 uint16_t const        dlen,
                 uint8_t * const       p_buf,
                 uint32_t              buf_len,
                 uint32_t * const      p_index)
{
    uint32_t err_code   = NRF_SUCCESS;
    uint8_t  is_present = (p_data == NULL) ? SER_FIELD_NOT_PRESENT : SER_FIELD_PRESENT;

    err_code = uint8_t_enc(&is_present, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    if (p_data)
    {
        SER_ASSERT_LENGTH_LEQ(dlen, ((int32_t)buf_len - *p_index));
        memcpy(&p_buf[*p_index], p_data, dlen);
        *p_index += dlen;
    }

    return err_code;
}

uint32_t buf_dec(uint8_t const * const p_buf,
                 uint32_t              buf_len,
                 uint32_t * const      p_index,
                 uint8_t * * const     pp_data,
                 uint16_t              data_len,
                 uint16_t              dlen)
{
    uint8_t is_present = 0;

    SER_ASSERT_LENGTH_LEQ(1, ((int32_t)buf_len - *p_index));
    uint8_dec(p_buf, buf_len, p_index, &is_present);

    if (is_present == SER_FIELD_PRESENT)
    {
        SER_ASSERT_NOT_NULL(pp_data);
        SER_ASSERT_NOT_NULL(*pp_data);
        SER_ASSERT_LENGTH_LEQ(dlen, data_len);
        SER_ASSERT_LENGTH_LEQ(dlen, ((int32_t)buf_len - *p_index));
        memcpy(*pp_data, &p_buf[*p_index], dlen);
        *p_index += dlen;
    }
    else
    {
        if (pp_data)
        {
            *pp_data = NULL;
        }
    }
    return NRF_SUCCESS;
}

uint32_t uint8_vector_enc(uint8_t const * const p_data,
                        uint16_t const        dlen,
                        uint8_t * const       p_buf,
                        uint32_t              buf_len,
                        uint32_t * const      p_index)
{

    SER_ASSERT_NOT_NULL(p_data);
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_index);
    SER_ASSERT_LENGTH_LEQ(dlen, ((int32_t)buf_len - *p_index));
    memcpy(&p_buf[*p_index], p_data, dlen);
    *p_index += dlen;

    return NRF_SUCCESS;
}

uint32_t uint8_vector_dec(uint8_t const * const p_buf,
                 uint32_t              buf_len,
                 uint32_t * const      p_index,
                 uint8_t *  const      p_data,
                 uint16_t              dlen)
{
    SER_ASSERT_NOT_NULL(p_data);
    SER_ASSERT_LENGTH_LEQ(dlen, ((int32_t)buf_len - *p_index));
    memcpy(p_data, &p_buf[*p_index], dlen);
    *p_index += dlen;

    return NRF_SUCCESS;
}

