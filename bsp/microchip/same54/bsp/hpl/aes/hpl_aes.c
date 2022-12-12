/**
 * \file
 *
 * \brief AES Advanced Encryption Standard(Sync) functionality declaration.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
#include <string.h>
#include <utils_assert.h>
#include <hpl_aes_sync.h>
#include <hpl_aes_config.h>

/**
 * \brief Update the AES KEY Register
 */
static inline void __aes_sync_set_key(struct _aes_sync_device *const dev);

/**
 * \brief Update the Initialization Vector Register
 */
static inline void __aes_sync_set_iv(struct _aes_sync_device *const dev, uint8_t *iv);

/**
 * \brief Update the INDATA Register
 */
static inline void __aes_sync_set_indata(struct _aes_sync_device *const dev, const uint8_t *data, uint32_t words);

/**
 * \brief Get data from INDATA Register
 */
static inline void __aes_sync_get_indata(struct _aes_sync_device *const dev, uint8_t *output, uint32_t words);

/**
 * \brief UPDATE CFB IV after encrypt/decrypt
 */
static inline void __aes_sync_update_cfb_iv(const enum aes_action enc, const uint8_t *input, uint8_t *output,
                                            uint32_t length, uint8_t *iv);
/**
 * GCM crypt function, start->update->generate_tag, should be invoke
 * by sequence.
 */
static void __aes_sync_gcm_start(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *iv,
                                 uint32_t iv_len, const uint8_t *aad, uint32_t aad_len);
static void __aes_sync_gcm_update(struct _aes_sync_device *const dev, const uint8_t *input, uint8_t *output,
                                  uint32_t length);
static void __aes_sync_gcm_generate_tag(struct _aes_sync_device *const dev, uint8_t *tag, uint32_t tag_len);
/**
 * CCM encrypt decrypt function
 */
int32_t __aes_sync_ccm_crypt_and_tag(struct _aes_sync_device *const dev, const uint8_t *input, uint8_t *output,
                                     uint32_t length, const uint8_t *iv, uint32_t iv_len, const uint8_t *aad,
                                     uint32_t aad_len, uint8_t *tag, uint32_t tag_len);
int32_t __aes_sync_ccm_decrypt_and_tag(struct _aes_sync_device *const dev, const uint8_t *input, uint8_t *output,
                                       uint32_t length, const uint8_t *iv, uint32_t iv_len, const uint8_t *aad,
                                       uint32_t aad_len, uint8_t *tag, uint32_t tag_len);
/**
 * \brief AES configuration type
 */
struct aes_configuration {
	hri_aes_dbgctrl_reg_t dbgctrl; /*!< Debug Control */
};

/**
 * \brief Array of AES configurations
 */
static struct aes_configuration _aes = {(CONF_AES_DBGCTRL << AES_DBGCTRL_DBGRUN_Pos)};

static inline void __aes_sync_set_key(struct _aes_sync_device *const dev)
{
	int i;

	for (i = 0; i < ((dev->keysize + 2) << 1); i++) {
		hri_aes_write_KEYWORD_reg(dev->hw, i, (((uint32_t *)(dev->key))[i]));
	}
}

static inline void __aes_sync_set_iv(struct _aes_sync_device *const dev, uint8_t *iv)
{
	int i;

	for (i = 0; i < 4; i++) {
		if (((uint32_t)iv) & 0x3) {
			hri_aes_write_INTVECTV_reg(dev->hw,
			                           i,
			                           ((uint8_t *)iv)[i << 2] | ((uint8_t *)iv)[(i << 2) + 1] >> 8
			                               | ((uint8_t *)iv)[(i << 2) + 2] >> 16 | ((uint8_t *)iv)[(i << 2) + 3] >> 24);
		} else {
			hri_aes_write_INTVECTV_reg(dev->hw, i, ((uint32_t *)iv)[i]);
		}
	}
}

static inline void __aes_sync_set_indata(struct _aes_sync_device *const dev, const uint8_t *data, uint32_t words)
{
	uint32_t i;

	for (i = 0; i < words; i++) {
		if (((uint32_t)data) & 0x3) {
			hri_aes_write_INDATA_reg(dev->hw,
			                         ((uint8_t *)data)[i << 2] | ((uint8_t *)data)[(i << 2) + 1] << 8
			                             | ((uint8_t *)data)[(i << 2) + 2] << 16
			                             | ((uint8_t *)data)[(i << 2) + 3] << 24);
		} else {
			hri_aes_write_INDATA_reg(dev->hw, ((uint32_t *)data)[i]);
		}
	}
}

static inline void __aes_sync_get_indata(struct _aes_sync_device *const dev, uint8_t *output, uint32_t words)
{
	uint32_t i;
	uint32_t buf;

	for (i = 0; i < words; i++) {
		if (((uint32_t)output) & 0x3) {
			buf       = (uint32_t)hri_aes_read_INDATA_reg(dev->hw);
			*output++ = buf & 0xFF;
			*output++ = (buf >> 8) & 0xFF;
			*output++ = (buf >> 16) & 0xFF;
			*output++ = (buf >> 24) & 0xFF;
		} else {
			((uint32_t *)output)[i] = hri_aes_read_INDATA_reg(dev->hw);
		}
	}
}

static inline void __aes_sync_update_cfb_iv(const enum aes_action enc, const uint8_t *input, uint8_t *output,
                                            uint32_t length, uint8_t *iv)
{
	const uint8_t *ptr = ((enc == AES_ENCRYPT) ? output : input);

	if (length >= 16) {
		memcpy(iv, ptr + length - 16, 16);
	} else {
		memcpy(iv, iv + length, 16 - length);
		memcpy(iv + 16 - length, ptr, length);
	}
}
/**
 * \brief Initialize AES.
 */
int32_t _aes_sync_init(struct _aes_sync_device *const dev, void *const hw)
{
	hri_aes_write_CTRLA_reg(hw, 0);
	hri_aes_write_CTRLA_reg(hw, AES_CTRLA_SWRST);

	dev->hw = hw;

	hri_aes_write_DBGCTRL_reg(dev->hw, _aes.dbgctrl);

	return ERR_NONE;
}

/**
 * \brief De-initialize AES.
 */
int32_t _aes_sync_deinit(struct _aes_sync_device *dev)
{
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_set_CTRLA_SWRST_bit(dev->hw);
	dev->hw = NULL;

	return ERR_NONE;
}

/**
 * \brief Enable AES
 */
int32_t _aes_sync_enable(struct _aes_sync_device *const dev)
{
	(void)dev;
	return ERR_NONE;
}

/**
 * \brief Disable AES
 */
int32_t _aes_sync_disable(struct _aes_sync_device *const dev)
{
	(void)dev;
	return ERR_NONE;
}

/**
 * \brief              Set AES Key (encryption/decryption)
 */
int32_t _aes_sync_set_key(struct _aes_sync_device *const dev, const uint8_t *key, const enum aes_keysize size)
{

	dev->keysize = size;
	memcpy(dev->key, key, (size + 2) << 3);
	return ERR_NONE;
}

/**
 * \brief              AES-ECB block encryption/decryption
 */
int32_t _aes_sync_ecb_crypt(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *input,
                            uint8_t *output)
{

	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_reg(dev->hw, 0);
	hri_aes_write_CTRLB_reg(dev->hw, 0);
	hri_aes_write_CTRLA_reg(dev->hw, AES_CTRLA_KEYSIZE(dev->keysize) | (enc << AES_CTRLA_CIPHER_Pos));
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	/* Key must be set for each ECB encrypt */
	__aes_sync_set_key(dev);
	hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
	__aes_sync_set_indata(dev, input, 4);
	hri_aes_set_CTRLB_START_bit(dev->hw);
	while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
		;
	__aes_sync_get_indata(dev, output, 4);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);

	return ERR_NONE;
}

/**
 * \brief              AES-CBC block encryption/decryption
 */
int32_t _aes_sync_cbc_crypt(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *input,
                            uint8_t *output, uint32_t length, uint8_t iv[16])
{
	// uint8_t index;
	uint8_t        block; /* Number of blocks (16 bytes) */
	const uint8_t *inptr;
	uint8_t *      outptr;

	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_reg(dev->hw, 0);
	hri_aes_write_CTRLA_reg(dev->hw,
	                        AES_CTRLA_AESMODE(1) | AES_CTRLA_KEYSIZE(dev->keysize) | (enc << AES_CTRLA_CIPHER_Pos));
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLB_reg(dev->hw, 0);

	/* The Key must be write before CBC crypt */
	__aes_sync_set_key(dev);
	/* Write IV */
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_set_iv(dev, iv);

	/* Enc/Dec plain text */
	inptr  = input;
	outptr = output;
	for (block = 0; block < (length >> 4); block++) {
		hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
		__aes_sync_set_indata(dev, inptr, 4);
		inptr += 16;
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		__aes_sync_get_indata(dev, outptr, 4);
		outptr += 16;
	}

	/* IV equals last cipher text */
	memcpy(iv, (enc == AES_ENCRYPT) ? output + length - 16 : input + length - 16, 16);
	hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);

	return ERR_NONE;
}

/**
 * \brief              AES-CFB128 block encryption/decryption
 */
int32_t _aes_sync_cfb128_crypt(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *input,
                               uint8_t *output, uint32_t length, uint8_t *iv)
{
	uint8_t        block; /* Number of blocks (16 bytes) */
	const uint8_t *inptr;
	uint8_t *      outptr;

	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, enc);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 3);
	hri_aes_clear_CTRLA_CFBS_bf(dev->hw, 0x7u);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	/* Write IV */
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_set_iv(dev, iv);

	/* Enc/Dec plain text */
	inptr  = input;
	outptr = output;
	for (block = 0; block < (length >> 4); block++) {
		hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
		__aes_sync_set_indata(dev, inptr, 4);
		inptr += 16;
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		__aes_sync_get_indata(dev, outptr, 4);
		outptr += 16;
	}

	__aes_sync_update_cfb_iv(enc, input, output, length, iv);

	hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);

	return ERR_NONE;
}

/**
 * \brief              AES-CFB64 block encryption/decryption
 */
int32_t _aes_sync_cfb64_crypt(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *input,
                              uint8_t *output, uint32_t length, uint8_t *iv)
{
	uint8_t        block; /* Number of blocks (8 bytes) */
	const uint8_t *inptr;
	uint8_t *      outptr;

	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, enc);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 3);
	hri_aes_write_CTRLA_CFBS_bf(dev->hw, 1);
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	__aes_sync_set_key(dev);

	/* Write IV */
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_set_iv(dev, iv);

	/* Enc/Dec plain text */
	inptr  = input;
	outptr = output;
	for (block = 0; block < (length >> 3); block++) {
		hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
		__aes_sync_set_indata(dev, inptr, 2);
		inptr += 8;
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		__aes_sync_get_indata(dev, outptr, 2);
		outptr += 8;
	}

	hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);

	__aes_sync_update_cfb_iv(enc, input, output, length, iv);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	return ERR_NONE;
}

/**
 * \brief              AES-CFB32 block encryption/decryption
 */
int32_t _aes_sync_cfb32_crypt(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *input,
                              uint8_t *output, uint32_t length, uint8_t *iv)
{
	uint8_t        block; /* Number of blocks (4 bytes) */
	const uint8_t *inptr;
	uint8_t *      outptr;

	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, enc);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 3);
	hri_aes_write_CTRLA_CFBS_bf(dev->hw, 2);
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	__aes_sync_set_key(dev);

	/* Write IV */
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_set_iv(dev, iv);

	/* Enc/Dec plain text */
	inptr  = input;
	outptr = output;
	for (block = 0; block < (length >> 2); block++) {
		hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
		__aes_sync_set_indata(dev, inptr, 1);
		inptr += 4;
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		__aes_sync_get_indata(dev, outptr, 1);
		outptr += 4;
	}

	hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_update_cfb_iv(enc, input, output, length, iv);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	return ERR_NONE;
}

/**
 * \brief              AES-CFB16 block encryption/decryption
 */
int32_t _aes_sync_cfb16_crypt(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *input,
                              uint8_t *output, uint32_t length, uint8_t *iv)
{
	uint8_t block; /* Number of blocks (2 bytes) */

	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, enc);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 3);
	hri_aes_write_CTRLA_CFBS_bf(dev->hw, 3);
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	__aes_sync_set_key(dev);

	/* Write IV */
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_set_iv(dev, iv);

	/* Enc/Dec plain text */
	for (block = 0; block < (length >> 1); block++) {
		hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
		hri_aes_write_INDATA_reg(dev->hw, ((uint16_t *)input)[block]);
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		((uint16_t *)output)[block] = hri_aes_read_INDATA_reg(dev->hw) & 0xFFFF;
	}

	__aes_sync_update_cfb_iv(enc, input, output, length, iv);

	hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	return ERR_NONE;
}

/**
 * \brief              AES-CFB8 block encryption/decryption
 */
int32_t _aes_sync_cfb8_crypt(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *input,
                             uint8_t *output, uint32_t length, uint8_t *iv)
{
	uint8_t block; /* Number of blocks (1 bytes) */

	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_reg(dev->hw, 0);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, enc);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 3);
	hri_aes_write_CTRLA_CFBS_bf(dev->hw, 4);
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	__aes_sync_set_key(dev);

	/* Write IV */
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_set_iv(dev, iv);

	/* Enc/Dec plain text */
	for (block = 0; block < length; block++) {
		hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
		hri_aes_write_INDATA_reg(dev->hw, ((uint8_t *)input)[block]);
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		((uint8_t *)output)[block] = hri_aes_read_INDATA_reg(dev->hw) & 0xFF;
	}

	hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);

	__aes_sync_update_cfb_iv(enc, input, output, length, iv);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	return ERR_NONE;
}

/**
 * \brief              AES-OFB block encryption/decryption
 */
int32_t _aes_sync_ofb_crypt(struct _aes_sync_device *const dev, const uint8_t *input, uint8_t *output, uint32_t length,
                            uint8_t *iv)
{
	uint8_t        index;
	uint8_t        block; /* Number of blocks (16 bytes) */
	const uint8_t *inptr;
	uint8_t *      outptr;

	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_reg(dev->hw, 0);
	hri_aes_write_CTRLB_reg(dev->hw, 0);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, 1);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 2);
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	__aes_sync_set_key(dev);

	/* Write IV */
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_set_iv(dev, iv);

	/* Enc/Dec plain text */
	inptr  = input;
	outptr = output;
	for (block = 0; block < (length >> 4); block++) {
		hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
		__aes_sync_set_indata(dev, inptr, 4);
		inptr += 16;
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		__aes_sync_get_indata(dev, outptr, 4);
		outptr += 16;
	}

	/* IV equals last plain text xor cipher text */
	for (index = 0; index < 16; index++) {
		iv[index] = input[length - 16 + index] ^ output[length - 16 + index];
	}

	hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	return ERR_NONE;
}

/**
 * \brief              AES-CTR block encryption/decryption
 */
int32_t _aes_sync_ctr_crypt(struct _aes_sync_device *const dev, const uint8_t *input, uint8_t *output, uint32_t length,
                            uint8_t nc[16])
{
	uint8_t        index;
	uint8_t        block; /* Number of blocks (16 bytes) */
	const uint8_t *inptr;
	uint8_t *      outptr;

	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_reg(dev->hw, 0x00);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, 1);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 4);
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	__aes_sync_set_key(dev);
	/* Write IV */
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_set_iv(dev, nc);

	/* Enc/Dec plain text */
	inptr  = input;
	outptr = output;
	for (block = 0; block < (length >> 4); block++) {
		hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
		__aes_sync_set_indata(dev, inptr, 4);
		inptr += 16;
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		__aes_sync_get_indata(dev, outptr, 4);
		outptr += 16;

		/* NC equals last NC + 1 */
		for (index = 0; index < 16; index++) {
			nc[15 - index] += 1;
			if (nc[15 - index]) {
				break;
			}
		}
	}

	hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	return ERR_NONE;
}

/**
 * \brief              AES-GCM block encryption/decryption
 */
int32_t _aes_sync_gcm_crypt_and_tag(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *input,
                                    uint8_t *output, uint32_t length, const uint8_t *iv, uint32_t iv_len,
                                    const uint8_t *aad, uint32_t aad_len, uint8_t *tag, uint32_t tag_len)
{
	uint8_t iv_initialized[16] = {0};

	__aes_sync_gcm_start(dev, enc, iv, iv_len, aad, aad_len);

	/* Copy the initialized IV for tag generation */
	memcpy(iv_initialized, dev->iv, 16);

	__aes_sync_gcm_update(dev, input, output, length);

	/* Restore IV before generating tag */
	memcpy(dev->iv, iv_initialized, 16);

	__aes_sync_gcm_generate_tag(dev, tag, tag_len);

	return ERR_NONE;
}

/**
 * \brief              AES-GCM block start
 */
int32_t _aes_sync_gcm_start(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *iv,
                            uint32_t iv_len, const uint8_t *aad, uint32_t aad_len)
{
	__aes_sync_gcm_start(dev, enc, iv, iv_len, aad, aad_len);
	return ERR_NONE;
}

/**
 * \brief              AES-GCM block update
 */
int32_t _aes_sync_gcm_update(struct _aes_sync_device *const dev, const uint8_t *input, uint8_t *output, uint32_t length)
{
	__aes_sync_gcm_update(dev, input, output, length);
	return ERR_NONE;
}

/**
 * \brief              AES-GCM block finish
 */
int32_t _aes_sync_gcm_finish(struct _aes_sync_device *const dev, uint8_t *tag, uint32_t tag_len)
{
	/* Generate Tag, The final GHash should be present at GHASHx reg now */
	__aes_sync_gcm_generate_tag(dev, tag, tag_len);
	return ERR_NONE;
}

/**
 * \brief              AES-CCM block encryption/decryption
 */
int32_t _aes_sync_ccm_crypt_and_tag(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *input,
                                    uint8_t *output, uint32_t length, const uint8_t *iv, uint32_t iv_len,
                                    const uint8_t *aad, uint32_t aad_len, uint8_t *tag, uint32_t tag_len)
{
	if (enc) {
		__aes_sync_ccm_crypt_and_tag(dev, input, output, length, iv, iv_len, aad, aad_len, tag, tag_len);
	} else {
		__aes_sync_ccm_decrypt_and_tag(dev, input, output, length, iv, iv_len, aad, aad_len, tag, tag_len);
	}
	return ERR_NONE;
}

static void __aes_sync_gcm_start(struct _aes_sync_device *const dev, const enum aes_action enc, const uint8_t *iv,
                                 uint32_t iv_len, const uint8_t *aad, uint32_t aad_len)
{
	uint8_t        index;
	uint32_t       use_len;
	int32_t        left_len;
	uint8_t        workbuf[16];
	const uint8_t *ptr;

	/* Step 1 Generate HASHKEY */
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_reg(dev->hw, 0);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, 1);
	hri_aes_clear_CTRLA_AESMODE_bf(dev->hw, 0x7u); /* 0: ECB */
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	__aes_sync_set_key(dev);
	for (index = 0; index < 4; index++) {
		hri_aes_write_INDATA_reg(dev->hw, 0);
	}
	hri_aes_set_CTRLB_START_bit(dev->hw);
	/* HashKey is ready*/
	while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
		;

	/* Change to GCM mode */
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_STARTMODE_bit(dev->hw, 0);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, 1);
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 6); /* GCM */
	hri_aes_clear_CTRLA_CTYPE_bf(dev->hw, 0xFu);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	__aes_sync_set_key(dev);
	hri_aes_set_CTRLB_GFMUL_bit(dev->hw);

	/* Step 2: Generate pre-counter block j0 from the IV */
	if (iv_len == 12) {
		memcpy(dev->iv, iv, 12);
		memset(dev->iv + 12, 0, 3);
		dev->iv[15] = 0x01;
	} else {
		/* If iv_len != 96, then j0 = GHASH(H, {}, IV) */
		for (index = 0; index < 4; index++) {
			hri_aes_write_INDATA_reg(dev->hw, 0x00);
		}
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_GFMCMP_bit(dev->hw) == 0)
			;

		/* GHASH IV */
		ptr      = iv;
		left_len = iv_len;
		while (left_len >= 0) {
			use_len = (left_len < 16) ? left_len : 16;
			if (use_len == 16) {
				__aes_sync_set_indata(dev, ptr, 4);
				hri_aes_set_CTRLB_START_bit(dev->hw);
				while (hri_aes_get_interrupt_GFMCMP_bit(dev->hw) == 0)
					;
			} else {
				memset(workbuf, 0, 16);
				memcpy(workbuf, ptr, use_len);
				__aes_sync_set_indata(dev, workbuf, 4);
				hri_aes_set_CTRLB_START_bit(dev->hw);
				while (hri_aes_get_interrupt_GFMCMP_bit(dev->hw) == 0)
					;
			}
			left_len -= use_len;
			ptr += use_len;
			left_len = left_len ? left_len : -1;
		}
		/* GHASH len(IV)64 */
		memset(workbuf, 0, 12);
		workbuf[12] = ((iv_len << 3) >> 24) & 0xFF;
		workbuf[13] = ((iv_len << 3) >> 16) & 0xFF;
		workbuf[14] = ((iv_len << 3) >> 8) & 0xFF;
		workbuf[15] = (iv_len << 3) & 0xFF;

		__aes_sync_set_indata(dev, workbuf, 4);
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_GFMCMP_bit(dev->hw) == 0)
			;
		/* Get j0 from GHASH reg */
		for (index = 0; index < 4; index++) {
			((uint32_t *)dev->iv)[index] = hri_aes_read_GHASH_reg(dev->hw, index);
			hri_aes_write_GHASH_reg(dev->hw, index, 0x00);
		}
	}

	/* Step 3: GHASH AAD */
	ptr      = aad;
	left_len = aad_len;
	while (left_len >= 0) {
		use_len = (left_len < 16) ? left_len : 16;
		if (use_len == 16) {
			__aes_sync_set_indata(dev, ptr, 4);
			hri_aes_set_CTRLB_START_bit(dev->hw);
			while (hri_aes_get_interrupt_GFMCMP_bit(dev->hw) == 0)
				;
		} else {
			memset(workbuf, 0, 16);
			memcpy(workbuf, ptr, use_len);
			__aes_sync_set_indata(dev, workbuf, 4);
			hri_aes_set_CTRLB_START_bit(dev->hw);
			while (hri_aes_get_interrupt_GFMCMP_bit(dev->hw) == 0)
				;
		}
		left_len -= use_len;
		ptr += use_len;
		left_len = left_len ? left_len : -1;
	}

	/* GFMUL must be clear, otherwise the interrupt flag cannot be set when
	 * en/decrypt text */
	hri_aes_clear_CTRLB_GFMUL_bit(dev->hw);

	dev->aad_len = aad_len;

	/* Step 3: Change enc/dec */
	if (enc == 0) {
		hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
		hri_aes_write_CTRLA_CIPHER_bit(dev->hw, 0);
		hri_aes_set_CTRLA_ENABLE_bit(dev->hw);
	}
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	return;
}

static void __aes_sync_gcm_update(struct _aes_sync_device *const dev, const uint8_t *input, uint8_t *output,
                                  uint32_t length)
{
	int8_t         index;
	uint8_t        block; /* Number of blocks (16 bytes) */
	uint8_t        workbuf[16];
	const uint8_t *inptr;
	uint8_t *      outptr;

	/* Set iv = j1 =  j0 + 1 */
	for (index = 16; index > 12; index--) {
		if (++dev->iv[index - 1] != 0)
			break;
	}
	memcpy(workbuf, dev->iv, 16);

	/* Step 2 Plain text Processing */
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_clear_interrupt_ENCCMP_bit(dev->hw);
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	hri_aes_write_CIPLEN_reg(dev->hw, length);

	/* Step 2 Set J1 to IV */
	__aes_sync_set_iv(dev, workbuf);

	/* Enc/Dec plain text */
	inptr  = input;
	outptr = output;
	hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
	for (block = 0; block < (length >> 4); block++) {
		if (((length & 0xF) == 0) && block == ((length >> 4) - 1)) {
			hri_aes_set_CTRLB_EOM_bit(dev->hw);
		}
		__aes_sync_set_indata(dev, inptr, 4);
		inptr += 16;
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
		hri_aes_clear_CTRLB_EOM_bit(dev->hw);
		__aes_sync_get_indata(dev, outptr, 4);
		outptr += 16;
	}
	/* If length it not 16 bytes align, then process last one */
	if (length & 0xF) {
		memset(workbuf, 0, 16);
		memcpy(workbuf, input + (length & ~0xF), length & 0xF);

		hri_aes_set_CTRLB_EOM_bit(dev->hw);
		__aes_sync_set_indata(dev, workbuf, 4);
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		__aes_sync_get_indata(dev, workbuf, 4);
		memcpy(output + (length & ~0xF), workbuf, length & 0xF);
	}

	/* Generate Final GHASH by GHASH(H, A, C) */
	memset(workbuf, 0, 16);
	((uint8_t *)workbuf)[4]  = ((dev->aad_len << 3) >> 24) & 0xFF;
	((uint8_t *)workbuf)[5]  = ((dev->aad_len << 3) >> 16) & 0xFF;
	((uint8_t *)workbuf)[6]  = ((dev->aad_len << 3) >> 8) & 0xFF;
	((uint8_t *)workbuf)[7]  = (dev->aad_len << 3) & 0xFF;
	((uint8_t *)workbuf)[12] = ((length << 3) >> 24) & 0xFF;
	((uint8_t *)workbuf)[13] = ((length << 3) >> 16) & 0xFF;
	((uint8_t *)workbuf)[14] = ((length << 3) >> 8) & 0xFF;
	((uint8_t *)workbuf)[15] = (length << 3) & 0xFF;

	__aes_sync_set_indata(dev, workbuf, 4);
	hri_aes_set_CTRLB_GFMUL_bit(dev->hw);
	hri_aes_set_CTRLB_START_bit(dev->hw);
	while (hri_aes_get_interrupt_GFMCMP_bit(dev->hw) == 0)
		;
	hri_aes_clear_CTRLB_GFMUL_bit(dev->hw);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
}

/**
 * \brief              Generate Tag, The final GHash should be present at
 *                     GHASHx reg now
 */
static void __aes_sync_gcm_generate_tag(struct _aes_sync_device *const dev, uint8_t *tag, uint32_t tag_len)
{
	int8_t  index;
	uint8_t j0[16];

	memcpy(j0, dev->iv, 16);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	/* When change to Counter mode, all CTRLA should be reset */
	hri_aes_write_CTRLA_reg(dev->hw, 0);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, 1);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 4); /* Counter */
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLB_reg(dev->hw, 0);

	__aes_sync_set_key(dev);

	hri_aes_clear_DATABUFPTR_INDATAPTR_bf(dev->hw, 0x3u);
	__aes_sync_set_iv(dev, j0);
	for (index = 0; index < 4; index++) {
		hri_aes_write_INDATA_reg(dev->hw, (uint32_t)hri_aes_read_GHASH_reg(dev->hw, index));
	}
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	hri_aes_set_CTRLB_START_bit(dev->hw);
	while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
		;

	__aes_sync_get_indata(dev, j0, 4);
	memcpy(tag, j0, tag_len);

	/* Cleanup, Must be done after GCM crypt, otherwise
	 * it will effect next GCM crypt.
	 */
	for (index = 0; index < 4; index++) {
		hri_aes_write_GHASH_reg(dev->hw, index, 0x00);
		hri_aes_write_HASHKEY_reg(dev->hw, index, 0x00);
		hri_aes_write_INDATA_reg(dev->hw, 0x00);
	}
	hri_aes_write_CIPLEN_reg(dev->hw, 0x00);
	hri_aes_write_DATABUFPTR_reg(dev->hw, 0x00);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
}

/*
 * Encrypt CCM Data, the process follow the SP800-38C
 * Section 6.1 Generation-Encryption Process
 */
int32_t __aes_sync_ccm_crypt_and_tag(struct _aes_sync_device *const dev, const uint8_t *input, uint8_t *output,
                                     uint32_t length, const uint8_t *iv, uint32_t iv_len, const uint8_t *aad,
                                     uint32_t aad_len, uint8_t *tag, uint32_t tag_len)
{
	int8_t         index;
	uint8_t        block; /* Number of blocks (16 bytes) */
	uint8_t        q;
	uint8_t        b[16];
	uint8_t        ctr[16];
	const uint8_t *src;
	uint8_t *      dst;
	uint8_t        len_left;
	uint8_t        len_use;

	/* Step 1 (SP800-38C, 6.1): Apply the formatting function to (N,A,P) to
	 * produce the blocks B0,...Br */
	/* Generate first block B0 */
	memset(b, 0, 16);
	q    = (16 - 1 - (uint8_t)iv_len);
	b[0] = 0;
	b[0] |= (aad_len > 0) << 6;
	b[0] |= ((tag_len - 2) / 2) << 3;
	b[0] |= q - 1;
	memcpy(b + 1, iv, iv_len);
	for (index = 0, block = length; index < q; index++, block >>= 8) {
		b[15 - index] = (uint8_t)(block & 0xFF);
	}
	if (block > 0) {
		return ERR_INVALID_ARG;
	}

	/* Prepare CBC-MAC */
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_reg(dev->hw, 0);
	hri_aes_write_CTRLB_reg(dev->hw, 0);
	hri_aes_write_CTRLA_STARTMODE_bit(dev->hw, 0);
	hri_aes_write_CTRLA_CIPHER_bit(dev->hw, 1);
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 5); /* CCM */
	hri_aes_set_CTRLA_LOD_bit(dev->hw);         /* CBC-MAC */
	hri_aes_clear_CTRLA_CTYPE_bf(dev->hw, 0xFu);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLB_reg(dev->hw, 0);
	hri_aes_write_DATABUFPTR_reg(dev->hw, 0);
	__aes_sync_set_key(dev);
	/* For CBC-MAC, zero block is used as the IV (SP800-38C, 5.2) */
	for (index = 0; index < 4; index++) {
		hri_aes_write_INTVECTV_reg(dev->hw, index, 0x00);
	}

	/* Step 2(SP800-38C, 6.1): CBC-MAC for block0 */
	__aes_sync_set_indata(dev, b, 4);
	hri_aes_set_CTRLB_START_bit(dev->hw);
	while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
		;
	/* Not necessary read out DATA to clear ENCCMP, the ENCCMP flag is
	 * automatically cleared by writing into the INDATA register.
	 */

	/* Step 3(SP800-38C, 6.1) Continue process B1 to Br */
	/* Process additional data if have */
	if (aad_len > 0) {
		len_left = aad_len;
		src      = aad;

		memset(b, 0, 16);
		b[0] = (uint8_t)((aad_len >> 8) & 0xFF);
		b[1] = (uint8_t)((aad_len)&0xFF);

		len_use = len_left < 16 - 2 ? len_left : 16 - 2;
		for (index = 2; index < len_use + 2; index++) {
			b[index] = *src;
			src++;
		}
		len_left -= len_use;

		/* UPDATE CBC-MAC */
		__aes_sync_set_indata(dev, b, 4);
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;

		while (len_left > 0) {
			len_use = len_left > 16 ? 16 : len_left;
			memset(b, 0, 16);
			memcpy(b, src, len_use);
			src += len_use;
			/* UPDATE CBC-MAC */
			__aes_sync_set_indata(dev, b, 4);
			hri_aes_set_CTRLB_START_bit(dev->hw);
			while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
				;
			len_left -= len_use;
		}
	}

	/* Step Process plain text */
	len_left = length;
	src      = input;
	dst      = output;
	while (len_left > 0) {
		len_use = len_left > 16 ? 16 : len_left;

		if (len_use < 16) {
			memset(b, 0, 16);
		}
		memcpy(b, src, len_use);
		src += len_use;

		/* UPDATE CBC-MAC */
		__aes_sync_set_indata(dev, b, 4);
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;

		len_left -= len_use;
	}
	/* Step 4 (800-38C, 6.1) Get Tag from MSB(Br),
	 * Temporary save to output tag, the tag
	 * will be update at the final step.
	 */
	__aes_sync_get_indata(dev, b, 4);
	memcpy(tag, b, tag_len);

	/* Step 5,6,7 (800-38C, 6.1) Change to counter mode and encrypt plain text
	 * Make sure set the CTRLB->NEWMSG bit after set/change INTVECTV
	 */
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_clear_CTRLA_LOD_bit(dev->hw); /* Counter MODE */
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);
	__aes_sync_set_key(dev);
	/*
	 * Prepare counter block for encryption:
	 */
	memset(ctr, 0, 16);
	ctr[0] = q - 1;
	memcpy(ctr + 1, iv, iv_len);
	ctr[15] = 1;
	__aes_sync_set_iv(dev, ctr);

	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	len_left = length;
	src      = input;
	dst      = output;
	while (len_left > 0) {
		len_use = len_left > 16 ? 16 : len_left;
		if (len_use < 16) {
			memset(b, 0, 16);
		}
		memcpy(b, src, len_use);
		src += len_use;

		/* UPDATE Cipher text */
		__aes_sync_set_indata(dev, b, 4);
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;
		hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
		__aes_sync_get_indata(dev, b, 4);
		memcpy(dst, b, len_use);
		dst += len_use;
		len_left -= len_use;
	}

	/* Step 8 (800-38C, 6.1) Update Tag = Tag XOR MSBtlen(S0) */
	ctr[15] = 0;
	__aes_sync_set_iv(dev, ctr);
	if (tag_len < 16) {
		memset(b, 0, 16);
	}
	memcpy(b, tag, tag_len);
	__aes_sync_set_indata(dev, b, 4);
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	hri_aes_set_CTRLB_START_bit(dev->hw);
	while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
		;
	hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_get_indata(dev, b, 4);
	memcpy(tag, b, tag_len);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);

	return ERR_NONE;
}
/*
 * Encrypt CCM Data, the process follow the SP800-38C
 * Section 6.2 Decryption-Verification Process
 */
int32_t __aes_sync_ccm_decrypt_and_tag(struct _aes_sync_device *const dev, const uint8_t *input, uint8_t *output,
                                       uint32_t length, const uint8_t *iv, uint32_t iv_len, const uint8_t *aad,
                                       uint32_t aad_len, uint8_t *tag, uint32_t tag_len)
{
	int8_t         index;
	uint8_t        block; /* Number of blocks (16 bytes) */
	uint8_t        q;
	uint8_t        b[16];
	uint8_t        ctr[16];
	const uint8_t *src;
	uint8_t *      dst;
	uint8_t        len_left;
	uint8_t        len_use;

	/* Step 2(SP800-38C, 6.2) Prepare Counter for decrypt cipher text */
	memset(ctr, 0, 16);
	q      = (16 - 1 - (uint8_t)iv_len);
	ctr[0] = q - 1;
	memcpy(ctr + 1, iv, iv_len);
	ctr[15] = 1;

	/* Step 3,4,5(SP800-38C, 6.2) Decrypt cipher text */
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_write_CTRLA_reg(dev->hw, 0);
	hri_aes_write_CTRLB_reg(dev->hw, 0);
	hri_aes_write_CTRLA_STARTMODE_bit(dev->hw, 0);
	hri_aes_clear_CTRLA_CIPHER_bit(dev->hw);
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 5); /* CCM */
	hri_aes_clear_CTRLA_LOD_bit(dev->hw);       /* Counter mode */
	hri_aes_clear_CTRLA_CTYPE_bf(dev->hw, 0xFu);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);
	__aes_sync_set_key(dev);

	__aes_sync_set_iv(dev, ctr);
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	len_left = length;
	src      = input;
	dst      = output;
	while (len_left > 0) {
		size_t len_use = len_left > 16 ? 16 : len_left;
		{
			if (len_use < 16) {
				memset(b, 0, 16);
			}
			memcpy(b, src, len_use);
			src += len_use;
			/* UPDATE Cipher text */
			__aes_sync_set_indata(dev, b, 4);
			hri_aes_set_CTRLB_START_bit(dev->hw);
			while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
				;
			hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
			__aes_sync_get_indata(dev, b, 4);
			memcpy(dst, b, len_use);
			dst += len_use;
		}
		len_left -= len_use;
	}

	/* Step 6(SP800-38C, 6.2) this step was skipped, the input tag will be
	 * checked in HAL, below step will generate tag from plain text(output)
	 */
	/* Step 7(SP800-38C, 6.2) Prepare CBC-MAC */
	hri_aes_write_CTRLA_reg(dev->hw, 0);
	hri_aes_write_CTRLA_STARTMODE_bit(dev->hw, 0);
	hri_aes_write_CTRLA_KEYSIZE_bf(dev->hw, dev->keysize);
	hri_aes_write_CTRLA_AESMODE_bf(dev->hw, 5); /* CCM */
	hri_aes_set_CTRLA_LOD_bit(dev->hw);         /* CBC-MAC */
	hri_aes_set_CTRLA_CIPHER_bit(dev->hw);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);

	__aes_sync_set_key(dev);
	/* For CBC-MAC, zero block is used as the IV (SP800-38C, 5.2)*/
	for (index = 0; index < 4; index++) {
		hri_aes_write_INTVECTV_reg(dev->hw, index, 0x00);
	}

	/* Step 8(SP800-38C, 6.2) CBC-MAC for block0 */
	/* Prepare block0 (first block) */
	b[0] = 0;
	b[0] |= (aad_len > 0) << 6;
	b[0] |= ((tag_len - 2) / 2) << 3;
	b[0] |= q - 1;
	memcpy(b + 1, iv, iv_len);
	for (index = 0, block = length; index < q; index++, block >>= 8) {
		b[15 - index] = (uint8_t)(block & 0xFF);
	}
	if (block > 0) {
		return ERR_INVALID_ARG;
	}
	__aes_sync_set_indata(dev, b, 4);
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	hri_aes_set_CTRLB_START_bit(dev->hw);
	while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
		;
	/* Not necessary read out DATA to clear ENCCMP, the ENCCMP flag is
	 * automatically cleared by writing into the INDATA register.
	 * (From DataSheet)
	 */
	/* Step (SP800-38C, 6.2) Continue process B1 to Br */
	/* Process additional data */
	if (aad_len > 0) {
		len_left = aad_len;
		src      = aad;
		memset(b, 0, 16);
		b[0] = (uint8_t)((aad_len >> 8) & 0xFF);
		b[1] = (uint8_t)((aad_len)&0xFF);

		len_use = len_left < 16 - 2 ? len_left : 16 - 2;
		for (index = 2; index < len_use + 2; index++) {
			b[index] = *src;
			src++;
		}
		len_left -= len_use;

		/* UPDATE CBC-MAC */
		__aes_sync_set_indata(dev, b, 4);
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;

		while (len_left > 0) {
			len_use = len_left > 16 ? 16 : len_left;

			if (len_use < 16) {
				memset(b, 0, 16);
			}
			memcpy(b, src, len_use);
			src += len_use;
			/* UPDATE CBC-MAC */
			__aes_sync_set_indata(dev, b, 4);
			hri_aes_set_CTRLB_START_bit(dev->hw);
			while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
				;
			len_left -= len_use;
		}
	}
	/* Process plain text */
	len_left = length;
	src      = output;
	while (len_left > 0) {
		len_use = len_left > 16 ? 16 : len_left;
		if (len_use != 16) {
			memset(b, 0, 16);
		}
		memcpy(b, src, len_use);
		src += len_use;

		/* UPDATE CBC-MAC */
		__aes_sync_set_indata(dev, b, 4);
		hri_aes_set_CTRLB_START_bit(dev->hw);
		while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
			;

		len_left -= len_use;
	}
	/* Step 10(SP800-38C, 6.2) Get Tag from MSBtlen(Yr) */
	__aes_sync_get_indata(dev, b, 4);
	memcpy(tag, b, tag_len);
	/* Update Tag = Tag XOR MSBtlen(Yr) */
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);
	hri_aes_clear_CTRLA_LOD_bit(dev->hw);
	hri_aes_set_CTRLA_ENABLE_bit(dev->hw);
	ctr[15] = 0;
	__aes_sync_set_iv(dev, ctr);
	__aes_sync_set_key(dev);
	if (tag_len < 16) {
		memset(b, 0, 16);
	}
	memcpy(b, tag, tag_len);
	__aes_sync_set_indata(dev, b, 4);
	hri_aes_set_CTRLB_NEWMSG_bit(dev->hw);
	hri_aes_set_CTRLB_START_bit(dev->hw);
	while (hri_aes_get_interrupt_ENCCMP_bit(dev->hw) == 0)
		;
	hri_aes_clear_CTRLB_NEWMSG_bit(dev->hw);
	__aes_sync_get_indata(dev, b, 4);
	memcpy(tag, b, tag_len);
	hri_aes_clear_CTRLA_ENABLE_bit(dev->hw);

	return ERR_NONE;
}
