/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <stdlib.h>
#include "utils_base64.h"
#include <utils_log.h>

static int8_t g_encodingTable[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                   'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                   'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                   'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                   'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                   'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                   'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                   '4', '5', '6', '7', '8', '9', '+', '/'
                                  };

static int8_t g_decodingTable[256];
static int32_t g_modTable[] = { 0, 2, 1 };

static void build_decoding_table()
{
    static int32_t signal = 0;
    int32_t i = 0;

    if (signal != 0) {
        return;
    }

    for (i = 0; i < 64; i++) {
        g_decodingTable[(uint8_t) g_encodingTable[i]] = i;
    }

    signal = 1;
    return;
}

iotx_err_t utils_base64encode(const uint8_t *data, uint32_t inputLength, uint32_t outputLenMax,
                              uint8_t *encodedData, uint32_t *outputLength)
{
    uint32_t i = 0;
    uint32_t j = 0;

    if (NULL == encodedData) {
        log_error("pointer of encodedData is NULL!\r\n");
        return FAIL_RETURN;
    }

    *outputLength = 4 * ((inputLength + 2) / 3);

    if (outputLenMax < *outputLength) {
        log_error("the length of output memory is not enough!\r\n");
        return FAIL_RETURN;
    }

    for (i = 0, j = 0; i < inputLength;) {
        uint32_t octet_a = i < inputLength ? (uint8_t) data[i++] : 0;
        uint32_t octet_b = i < inputLength ? (uint8_t) data[i++] : 0;
        uint32_t octet_c = i < inputLength ? (uint8_t) data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encodedData[j++] = g_encodingTable[(triple >> 3 * 6) & 0x3F];
        encodedData[j++] = g_encodingTable[(triple >> 2 * 6) & 0x3F];
        encodedData[j++] = g_encodingTable[(triple >> 1 * 6) & 0x3F];
        encodedData[j++] = g_encodingTable[(triple >> 0 * 6) & 0x3F];
    }

    for (i = 0; i < g_modTable[inputLength % 3]; i++) {
        encodedData[*outputLength - 1 - i] = '=';
    }

    return SUCCESS_RETURN;
}

/*
 * Streaming Base64 encoder
 * param:
 *  read_data: The callback function when the encoder absorbs data.
 *             A non-zero return indicates the end of the data.
 *  write_data: The callback function when the encoder releases data.
 *  opaque: Callback function context.
 */
void utils_base64_encode_stream(int (*read_data)(uint8_t *data, void *opaque), void (*write_data)(const uint8_t data[4], void *opaque), void *opaque)
{
  uint8_t encodedData[4], c;
  int end = 0, remainder = -1, i;

  while (!end) {
    uint32_t octet_a = (end = read_data(&c, opaque)) ? (remainder = (remainder >= 0 ? remainder : 0), 0) : c;
    uint32_t octet_b = (end = read_data(&c, opaque)) ? (remainder = (remainder >= 0 ? remainder : 1), 0) : c;
    uint32_t octet_c = (end = read_data(&c, opaque)) ? (remainder = (remainder >= 0 ? remainder : 2), 0) : c;

    uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

    if (end && remainder == 0) {
      return;
    }

    encodedData[0] = g_encodingTable[(triple >> 3 * 6) & 0x3F];
    encodedData[1] = g_encodingTable[(triple >> 2 * 6) & 0x3F];
    encodedData[2] = g_encodingTable[(triple >> 1 * 6) & 0x3F];
    encodedData[3] = g_encodingTable[(triple >> 0 * 6) & 0x3F];

    if (!end) {
      write_data(encodedData, opaque);
    }
  }

  for (i = 0; i < g_modTable[remainder]; i++) {
    encodedData[3 - i] = '=';
  }

  write_data(encodedData, opaque);

  return;
}

iotx_err_t utils_base64decode(const uint8_t *data, uint32_t inputLength, uint32_t outputLenMax,
                              uint8_t *decodedData, uint32_t *outputLength)
{
    uint32_t i = 0;
    uint32_t j = 0;

    build_decoding_table();

    if (inputLength % 4 != 0) {
        log_error("the input length is error!\r\n");
        return FAIL_RETURN;
    }

    *outputLength = inputLength / 4 * 3;


    if (data[inputLength - 1] == '=') {
        (*outputLength)--;
    }

    if (data[inputLength - 2] == '=') {
        (*outputLength)--;
    }

    if (outputLenMax < *outputLength) {
        log_error("the length of output memory is not enough!\r\n");
        return FAIL_RETURN;
    }

    uint32_t sextet_a = 0;
    uint32_t sextet_b = 0;
    uint32_t sextet_c = 0;
    uint32_t sextet_d = 0;
    uint32_t triple = 0;

    for (i = 0, j = 0; i < inputLength;) {
        sextet_a = data[i] == '=' ? 0 & i++ : g_decodingTable[data[i++]];
        sextet_b = data[i] == '=' ? 0 & i++ : g_decodingTable[data[i++]];
        sextet_c = data[i] == '=' ? 0 & i++ : g_decodingTable[data[i++]];
        sextet_d = data[i] == '=' ? 0 & i++ : g_decodingTable[data[i++]];

        triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

        if (j < *outputLength) {
            decodedData[j++] = (triple >> 2 * 8) & 0xFF;
        }

        if (j < *outputLength) {
            decodedData[j++] = (triple >> 1 * 8) & 0xFF;
        }

        if (j < *outputLength) {
            decodedData[j++] = (triple >> 0 * 8) & 0xFF;
        }
    }

    return SUCCESS_RETURN;
}


