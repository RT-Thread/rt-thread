/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

/*
 *  CAU Header File
 *  Works with library cau_lib.a and lib_mmcau*.a
 *  Define FREESCALE_CAU if CAU coprocessor is used --Register parameter passing is assumed
 *  Define FREESCALE_MMCAU if mmCAU coprocessor is used --EABI for Kinetis ARM Cortex-Mx
 *  12/19/2013
 */

/*!
 * @addtogroup mmcau MMCAU Peripheral Driver
 * @{
 */

#if FREESCALE_MMCAU
#define cau_aes_set_key               mmcau_aes_set_key
#define cau_aes_encrypt               mmcau_aes_encrypt
#define cau_aes_decrypt               mmcau_aes_decrypt
#define cau_des_chk_parity            mmcau_des_chk_parity
#define cau_des_encrypt               mmcau_des_encrypt
#define cau_des_decrypt               mmcau_des_decrypt
#define cau_md5_initialize_output     mmcau_md5_initialize_output
#define cau_md5_hash_n                mmcau_md5_hash_n
#define cau_md5_update                mmcau_md5_update
#define cau_md5_hash                  mmcau_md5_hash
#define cau_sha1_initialize_output    mmcau_sha1_initialize_output
#define cau_sha1_hash_n               mmcau_sha1_hash_n
#define cau_sha1_update               mmcau_sha1_update
#define cau_sha1_hash                 mmcau_sha1_hash
#define cau_sha256_initialize_output  mmcau_sha256_initialize_output
#define cau_sha256_hash_n             mmcau_sha256_hash_n
#define cau_sha256_update             mmcau_sha256_update
#define cau_sha256_hash               mmcau_sha256_hash
#endif

/*!
 * @brief AES: Performs an AES key expansion
 *
 * This function performs an AES key expansion
 *
 * @param [in]    *key       pointer to input key (128, 192, 256 bits in length)
 * @param [in]    key_size   key_size in bits (128, 192, 256)
 * @param [out]   *key_sch   pointer to key schedule output (44, 52, 60 longwords)
 * @return None
 * @note Table 4 shows the requirements for the cau_aes_set_key() function when using AES128, AES192 or AES256.
 * | [in] Block Size (bits)  |  [out] Key Schedule Size (32 bit data values)  |
 * | :---------------------: | :--------------------------------------------: |
 * |          128            |                      44                        |
 * |          192            |                      52                        |
 * |          256            |                      60                        |
 * <b>Table 4: AES set_key Requirements</b>
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_aes_set_key (const unsigned char *key, const int key_size,
                 unsigned char *key_sch);

/*!
 * @brief AES: Encrypts a single 16‐byte block
 *
 * This function encrypts a single 16-byte block for AES128, AES192 or AES256
 *
 * @param [in]   *in          pointer to 16‐byte block of input plaintext
 * @param [in]   *key_sch     pointer to key schedule (44, 52, 60 longwords)
 * @param [in]   nr           number of AES rounds (10, 12, 14 = f(key_schedule))
 * @param [out]  *out         pointer to 16‐byte block of output ciphertext
 * @return None
 * @note   Input and output blocks may overlap.<br>
 *         Table 5 shows the requirements for the cau_aes_encrypt()/cau_aes_decrypt()
 *         function when using AES128, AES192 or AES256.
 * | Block Cipher | [in] Key Schedule Size (longwords) | [in] Number of AES rounds |
 * | :----------: | :--------------------------------: | :-----------------------: |
 * |    AES128    |               44                   |             10            |
 * |    AES192    |               52                   |             12            |
 * |    AES256    |               60                   |             14            |
 * <b>Table 5: AES Encryption Requirements</b>
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_aes_encrypt (const unsigned char *in, const unsigned char *key_sch,
                 const int nr, unsigned char *out);

/*!
 * @brief AES: Decrypts a single 16‐byte block
 *
 * This function decrypts a single 16‐byte block for AES128, AES192 and AES256
 *
 * @param [in]   *in          pointer to 16‐byte block of input ciphertext
 * @param [in]   *key_sch     pointer to key schedule (44, 52, 60 longwords)
 * @param [in]   nr           number of AES rounds (10, 12, 14 = f(key_schedule))
 * @param [out]  *out         pointer to 16‐byte block of output plaintext
 * @return None
 * @note   Input and output blocks may overlap.<br>
 *         Table 6 shows the requirements for the cau_aes_encrypt()/cau_aes_decrypt()
 *         function when using AES128, AES192 or AES256.
 * | Block Cipher | [in] Key Schedule Size (longwords) | [in] Number of AES rounds |
 * | :----------: | :--------------------------------: | :-----------------------: |
 * |    AES128    |               44                   |             10            |
 * |    AES192    |               52                   |             12            |
 * |    AES256    |               60                   |             14            |
 * <b>Table 6: AES Decryption Requirements</b>
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_aes_decrypt (const unsigned char *in, const unsigned char *key_sch,
                 const int nr, unsigned char *out);

/*!
 * @brief DES: Checks key parity
 *
 * This function checks the parity of a key
 *
 * @param [in]    *key        pointer to 64‐bit DES key with parity bits
 * @return  0 no error
 * @return -1 parity error
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
int
cau_des_chk_parity (const unsigned char *key);

/*!
 * @brief DES: Encrypts a single 8‐byte block
 *
 * This function encrypt a single 8-byte block
 *
 * @param [in]    *in          pointer to 8‐byte block of input plaintext
 * @param [in]    *key         pointer to 64‐bit DES key with parity bits
 * @param [out]   *out         pointer to 8‐byte block of output ciphertext
 * @return  None
 * @note  Input and output blocks may overlap.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_des_encrypt (const unsigned char *in, const unsigned char *key,
                 unsigned char *out);

/*!
 * @brief DES: Decrypts a single 8‐byte block
 *
 * This function decrypt a single 8-byte block
 *
 * @param [in]    *in          pointer to 8‐byte block of input ciphertext
 * @param [in]    *key         pointer to 64‐bit DES key with parity bits
 * @param [out]   *out         pointer to 8‐byte block of output plaintext
 * @return  None
 * @note  Input and output blocks may overlap.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_des_decrypt (const unsigned char *in, const unsigned char *key,
                 unsigned char *out);

/*!
 * @brief MD5: Initializes the MD5 state variables
 *
 * This function initializes the MD5 state variables
 *
 * @param [out]   *md5_state    pointer to 120‐bit block of md5 state variables: a,b,c,d
 * @return  None
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_md5_initialize_output (const unsigned char *md5_state);

/*!
 * @brief MD5: Updates MD5 state variables
 *
 * This function updates MD5 state variables for one or more input message blocks
 *
 * @param [in]       *msg_data    pointer to start of input message data
 * @param [in]       num_blks     number of 512‐bit blocks to process
 * @param [in,out]   *md5_state   pointer to 128‐bit block of MD5 state variables: a,b,c,d
 * @return  None
 * @note  Input message and digest output blocks must not overlap.
 *        The cau_md5_initialize_output() function must be called first.
 *        Useful when handling non‐contiguous input message blocks.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_md5_hash_n (const unsigned char *msg_data, const int num_blks,
                unsigned char *md5_state);

/*!
 * @brief MD5: Updates MD5 state variables
 *
 * This function updates MD5 state variables for one or more input message blocks
 *
 * @param [in]       *msg_data    pointer to start of input message data
 * @param [in]       num_blks     number of 512‐bit blocks to process
 * @param [in,out]   *md5_state   pointer to 128‐bit block of MD5 state variables: a,b,c,d
 * @return  None
 * @note  Input message and digest output blocks must not overlap.
 *        The cau_md5_initialize_output() function is not required.
 *        All input message blocks must be contiguous.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_md5_update (const unsigned char *msg_data, const int num_blks,
                unsigned char *md5_state);

/*!
 * @brief MD5: Performs MD5 hash algorithm
 *
 * This function performs MD5 hash algorithm for a single input message block
 *
 * @param [in]       *msg_data    pointer to start of input message data
 * @param [in,out]   *md5_state   pointer to 128‐bit block of MD5 state variables: a,b,c,d
 * @return  None
 * @note  Input message and digest output blocks must not overlap.
 *        The cau_md5_initialize_output() function must be called first.
 *        Only works for a single input message block.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_md5_hash (const unsigned char *msg_data, unsigned char *md5_state);

/*!
 * @brief SHA1: Initializes the SHA1 state variables
 *
 * This function initializes the SHA1 state variables
 *
 * @param [out]      *sha1_state pointer to 160‐bit block of SHA1 state variables: a,b,c,d,e
 * @return  None
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_sha1_initialize_output (const unsigned int *sha1_state);

/*!
 * @brief SHA1: Performs the hash and generate SHA1 state variables
 *
 * This function performs the hash and generate SHA1 state variables for one or more input message blocks
 *
 * @param [in]       *msg_data    pointer to start of input message data
 * @param [in]       num_blks     number of 512‐bit blocks to process
 * @param [in,out]   *sha1_state  pointer to 160‐bit block of SHA1 state variables: a,b,c,d,e
 * @return  None
 * @note  Input message and digest output blocks must not overlap.
 *        The cau_sha1_initialize_output() function must be called first.
 *        Useful when handling non‐contiguous input message blocks.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_sha1_hash_n (const unsigned char *msg_data, const int num_blks,
                 unsigned int *sha1_state);

/*!
 * @brief SHA1: Updates SHA1 state variables
 *
 * This function updates SHA1 state variables for one or more input message blocks arguments
 *
 * @param [in]      *msg_data    pointer to start of input message data
 * @param [in]      num_blks     number of 512‐bit blocks to process
 * @param [out]     *sha1_state pointer to 160‐bit block of SHA1 state variables: a,b,c,d,e
 * @return  None
 * @note  Input message and digest output blocks must not overlap.
 *        The cau_sha1_initialize_output() function is not required.
 *        All input message blocks must be contiguous.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_sha1_update (const unsigned char *msg_data, const int num_blks,
                 unsigned int *sha1_state);

/*!
 * @brief SHA1: Performs SHA1 hash algorithm
 *
 * This function performs SHA1 hash algorithm on a single input message block
 *
 * @param [in]      *msg_data    pointer to start of input message data
 * @param [in,out]  *sha1_state pointer to 160‐bit block of SHA1 state variables: a,b,c,d,e
 * @return  None
 * @note  Input message and digest output blocks must not overlap.
          The cau_sha1_initialize_output() function must be called first.
          Only works for a single input message block.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_sha1_hash (const unsigned char *msg_data,
               unsigned int *sha1_state);

/*!
 * @brief SHA256: Initializes the hash output and checks the CAU hardware revision
 *
 * This function initializes the hash output and checks the CAU hardware revision
 *
 * @param  [out]       *output pointer to 256‐bit message digest output
 * @return  0     No error. CAU2 hardware present. SHA256 HW support available
 * @return -1     Error. CAU2 hardware not present. No SHA256 HW support available
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
int
cau_sha256_initialize_output (const unsigned int *output);

/*!
 * @brief SHA256: Updates SHA256 digest output
 *
 * This function updates SHA256 digest output for one or more message block arguments
 *
 * @param [in]         *input       pointer to start of input message
 * @param [in]         num_blks number of 512‐bit blocks to process
 * @param [in,out]     *output      pointer to 256‐bit message digest output
 * @return  None
 * @note  Input message and digest output blocks must not overlap.
 *        The cau_sha256_initialize_output() function must be called first.
 *        Useful when handling non‐contiguous input message blocks.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_sha256_hash_n (const unsigned char *input, const int num_blks,
                   unsigned int *output);

/*!
 * @brief SHA256: Updates SHA256 state variables
 *
 * This function updates SHA256 state variables for one or more input message blocks arguments
 *
 * @param [in]         *input       pointer to start of input message data
 * @param [in]         num_blks   number of 512‐bit blocks to process
 * @param [out]        *output      pointer to 256‐bit message digest output
 * @return  None
 * @note  Input message and digest output blocks must not overlap.
 *        The cau_sha256_initialize_output() function is not required.
 *        All input message blocks must be contiguous.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_sha256_update (const unsigned char *input, const int num_blks,
                   unsigned int *output);

/*!
 * @brief SHA256: Performs SHA256 hash algorithm
 *
 * This function performs SHA256 hash algorithm for a single input message block
 *
 * @param [in]         *input       pointer to start of input message data
 * @param [in,out]     *output      pointer to 256‐bit message digest output
 * @return  None
 * @note  nput message and digest output blocks must not overlap.
 *        The cau_sha256_initialize_output() function must be called first.
 *        Only works for a single input message block.
 */
#if FREESCALE_CAU
__declspec (standard_abi)
#endif
void
cau_sha256_hash (const unsigned char *input, unsigned int *output);
