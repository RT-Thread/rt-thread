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
#include <string.h>

#include <bl_sec.h>
#include <utils_psk_fast.h>
#include <utils_hex.h>
#include <utils_hmac_sha1_fast.h>

#define A_SHA_DIGEST_LEN 20
static void Bl_F_fast(unsigned char digest[36], unsigned char digest1[A_SHA_DIGEST_LEN], char *password, unsigned char *ssid, int ssidlength, int iterations, int count, unsigned char *output)
{
    int i, j;
    int len = strlen(password);
    int tmpLen = ssidlength + 4;
    unsigned char * pTemp = digest;

    /* U1 = PRF(P, S || int(i)) */
    memcpy(digest, ssid, ssidlength);
    digest[ssidlength] = (unsigned char)((count>>24) & 0xff);
    digest[ssidlength+1] = (unsigned char)((count>>16) & 0xff);
    digest[ssidlength+2] = (unsigned char)((count>>8) & 0xff);
    digest[ssidlength+3] = (unsigned char)(count & 0xff);

    bl_sha_mutex_take();
    utils_hmac_sha1_fast(&pTemp,
                   &tmpLen,
                   1,
                   (unsigned char*) password,
                   len,
                   digest1,
                   A_SHA_DIGEST_LEN);

    /* output = U1 */
    memcpy(output, digest1, A_SHA_DIGEST_LEN);
    pTemp = digest1;
    for (i = 1; i < iterations; i++)
    {
        tmpLen = A_SHA_DIGEST_LEN;

        /* Un = PRF(P, Un-1) */
        utils_hmac_sha1_fast(&pTemp,
                       &tmpLen,
                       1,
                       (unsigned char*) password,
                       len,
                       digest,
                       A_SHA_DIGEST_LEN);

        memcpy(digest1, digest, A_SHA_DIGEST_LEN);

        /* output = output xor Un */
        for (j = 0; j < A_SHA_DIGEST_LEN; j++)
        {
            output[j] ^= digest[j];
        }
    }
    bl_sha_mutex_give();
}

int utils_wifi_psk_cal_fast_bin(char *password, unsigned char *ssid, int ssidlength, unsigned char *output)
{
    unsigned char digest[36], digest1[A_SHA_DIGEST_LEN];

    if ((strlen(password) > 63) || (ssidlength > 32)) {
        return -1;
    }

    Bl_F_fast(digest, digest1, password, ssid, ssidlength, 4096, 2, output);
    memcpy(output + A_SHA_DIGEST_LEN, output, 12);
    Bl_F_fast(digest, digest1, password, ssid, ssidlength, 4096, 1, output);

    return 0;
}

int utils_wifi_psk_cal_fast(char *password, char *ssid, int ssid_len, char *output)
{
    int ret;
    char psk[32];

    ret = utils_wifi_psk_cal_fast_bin(password, (unsigned char *)ssid, ssid_len, (unsigned char *)psk);
    if (0 == ret) {
        utils_bin2hex(output, psk, 32);
    }

    return ret;
}
