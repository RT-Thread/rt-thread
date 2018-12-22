/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sdk.h"
#include "caam/caam.h"

/* These defines could be customized */
#define DEK_PLAINTEXT_ADDR  0x10700000
#define DEK_BLOB_ADDR       0x10701000

/* Known test vector from NIST specific publication 800-38A (section F.1.1)*/
/* AES ECB 128-bit encryption mode:
 * Encryption key = 2b7e151628aed2a6abf7158809cf4f3c
 * Initialization vector = not used in ECB mode
 * Test vector = 6bc1bee22e409f96e93d7e117393172a
 * Cipher text = 3ad77bb40d7a3660a89ecaf32466ef97
 */
/* Data Encryption Key - i.e. the key will be wrapped in the blob */
uint8_t dek[16] = 
{
    0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
    0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C
};
/* Test vector to encrypt */
uint8_t test_vect[16] = 
{
    0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96,
    0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A
};
/* Cipher text */
uint8_t cipher_text[16] = 
{
    0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60,
    0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97
};

/* This is the required header added to the DEK blob for encrypted boot */
uint8_t wrapped_key_hdr[8] = {0x81, 0x00, 0x48, 0x41, 0x66, 0x55, 0x10, 0x00};

/*!
 * CAAM blob test for encrypted boot.
 *
 * @return  0
 */
int32_t caam_test(void)
{
    uint8_t i, sel;
    uint32_t key_addr, ret = SUCCESS;
    uint8_t enc_result[16];

    printf("Start CAAM blob unit test:\n");

    do {
        printf("\n  To wrapped the DEK into a blob:\n");
        printf("  1 - with code built-in DEK.\n");
        printf("  2 - with provisionned DEK at 0x%X.\n",DEK_PLAINTEXT_ADDR);
        printf("  x - to exit.\n\n");

        do {
            sel = getchar();
        } while (sel == NONE_CHAR);

        if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        printf("-- Executing option %d -- \n\n",sel-48);
        if (sel == '1')
        {
            /* Set the key address to built-in example dek[]. */
            key_addr = (uint32_t) &dek[0];
            printf("DEK is the built-in:\n");
        }
        if (sel == '2')
        {
            printf("Note: the comparison with the reference cipher text is"
                   " expected to fail!\n\n");
            /* Set the key address to the one of the DEK in DDR loaded
             * through the manufacturing tool.
             */
            key_addr = DEK_PLAINTEXT_ADDR;
            printf("DEK is the provisionned one:\n");
        }

        caam_open();

        /* Print the DEK that is going to be used */
        for(i=0;i<16;i++)
            printf("%02X ",((uint8_t *)key_addr)[i]);
        printf("\n\n");

        /* Generate the blob to encapsulate the DEK */
        ret = caam_gen_blob((uint32_t)key_addr, (uint32_t)(DEK_BLOB_ADDR+8));
        if(ret != SUCCESS)
            printf("Error during blob decap operation: 0x%d\n",ret);

        /* Copy the header into the DEK blob buffer */
        memcpy((uint32_t *)DEK_BLOB_ADDR, wrapped_key_hdr,
                    sizeof(wrapped_key_hdr));

        /* Print the generated DEK blob */
        printf("DEK blob is available at 0x%08X and equals:\n",DEK_BLOB_ADDR);
        for(i=0;i<(8+64);i++)
            printf("%02X ",((uint8_t *)DEK_BLOB_ADDR)[i]);
        printf("\n\n");
        printf("Note: the first 8 Bytes are the required header and wrp_dat of"
                " the wrapped key structure!\n\n");

        /* Get the DEK by decrypting its previously generated blob */
        ret = caam_decap_blob((uint32_t)(DEK_BLOB_ADDR+8));
        if(ret != SUCCESS)
            printf("Error during blob decap operation: 0x%d\n",ret);

        /* The decrypted DEK cannot be read from the secure memory.
         * So, it is needed to run an encryption test of a known data with
         * that known key to compare the result against the known reference.
         * This ensures that the whole flow of enc/decap is functional.
         */
        ret = caam_enc_data((uint32_t) &test_vect[0], 
                            (uint32_t) &enc_result[0], 0);
        if(ret != SUCCESS)
            printf("Error during encryption operation: 0x%d\n",ret);

        /* Compare the reference cipher text with the obtained encoded data */
        if(memcmp(enc_result, cipher_text, sizeof(enc_result)))
        {
            printf("Error: Encoded result is different from the"
                   " reference cipher text!\n");
            /* Print the obtained encoded text for debug */
            printf("Obtained encoded text is:\n");
            for(i=0;i<16;i++)
                printf("%02X ",enc_result[i]);
            printf("\n");
            /* Print the reference cipher text for debug */
            printf("Reference cipher text is:\n");
            for(i=0;i<16;i++)
                printf("%02X ",cipher_text[i]);
            printf("\n");
        }
        else
        {
            printf("Success: Encoded result equals the reference"
                   " cipher text.\nThe DEK enc/decap flow is functional.\n");
        }

    } while(1);

    return 0;
}
