/**
 *
 * \file
 *
 * \brief SAM Advanced Encryption Standard driver.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup asfdoc_sam0_drivers_aes_group SAM Advanced Encryption Standard (AES) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for the configuration
 * and management of the device's Advanced Encryption Standard functionality. The following
 * driver API modes are covered by this manual:
 *
 *  - Polled APIs
 *  - Callback APIs
 *
 * The Advanced Encryption Standard module supports all five confidentiality
 * modes of operation for symmetrical key block cipher algorithms (as specified
 * in the NIST Special Publication 800-38A Recommendation):
 * - Electronic Code Book (ECB)
 * - Cipher Block Chaining (CBC)
 * - Output Feedback (OFB)
 * - Cipher Feedback (CFB)
 * - Counter (CTR)
 *
 * The following peripheral is used by this module:
 *  - AES (Advanced Encryption Standard)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM L21
 *  - Atmel | SMART SAM L22
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_drivers_aes_prerequisites
 *  - \ref asfdoc_sam0_drivers_aes_module_overview
 *  - \ref asfdoc_sam0_drivers_aes_special_considerations
 *  - \ref asfdoc_sam0_drivers_aes_extra_info
 *  - \ref asfdoc_sam0_drivers_aes_examples
 *  - \ref asfdoc_sam0_drivers_aes_api_overview
 *
 *
 * \section asfdoc_sam0_drivers_aes_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_drivers_aes_module_overview Module Overview
 *
 * The Advanced Encryption Standard (AES) is a specification for the encryption of
 * electronic data established by the U.S. National Institute of Standards and
 * Technology (NIST) in 2001. It is compliant with the American FIPS
 * (Federal Information Processing Standard) Publication 197 specification.
 *
 * The AES supports all five confidentiality modes of operation for symmetrical
 * key block cipher algorithms (as specified in the NIST Special Publication
 * 800-38A Recommendation):
 * - Electronic Code Book (ECB)
 * - Cipher Block Chaining (CBC)
 * - Output Feedback (OFB)
 * - Cipher Feedback (CFB)
 * - Counter (CTR)
 *
 * Data transfers both to and from the AES module can occur using the peripheral
 * DMA controller channels, thus minimizing processor intervention for
 * large data buffer transfers.
 *
 * As soon as the initialization vector, the input data and the key are
 * configured, the encryption/decryption process may be started. Once the
 * process has completed the encrypted/decrypted data can be read out via
 * registers or through DMA channels.
 *
 * \subsection asfdoc_sam0_drivers_aes_module_overview_en_de Encryption and Decryption
 * The AES is capable of using cryptographic keys of 128/192/256 bits to
 * encrypt and decrypt data in blocks of 128 bits. In Cipher Feedback Mode (CFB),
 * five data sizes are possible (8, 16, 32, 64, or 128 bits).
 *
 * The input to the encryption processes of the CBC, CFB, and OFB modes includes,
 * in addition to the plaintext, a 128-bit data block called the Initialization
 * Vector (IV). The Initialization Vector is used in the initial step in the
 * encryption of a message and in the corresponding decryption of the message.
 *
 * There are three encryption/decryption start modes:
 * - Manual Mode: Start encryption/decryption manually
 * - Auto Start Mode: Once the correct number of input data registers is written,
 * processing is automatically started, DMA operation uses this mode
 * - Last Output Data Mode (LOD): This mode is used to generate message
 * authentication code (MAC) on data in CCM mode of operation
 *
 * \subsection asfdoc_sam0_drivers_aes_module_overview_hardware_countermeasures Hardware Countermeasures
 * The AES module features four types of hardware countermeasures that are
 * useful for protecting data against differential power analysis attacks:
 * - Type 1: Randomly add one cycle to data processing
 * - Type 2: Randomly add one cycle to data processing (other version)
 * - Type 3: Add a random number of clock cycles to data processing, subject to
 * a maximum of 11/13/15 clock cycles for key sizes of 128/192/256 bits
 * - Type 4: Add random spurious power consumption during data processing
 *
 * \subsection asfdoc_sam0_drivers_aes_module_overview_gcm Galois Counter Mode (GCM)
 * GCM is comprised of the AES engine in CTR mode along with a universal hash
 * function (GHASH engine) that is defined over a binary Galois field to produce
 * a message authentication tag. The GHASH engine processes data packets after the
 * AES operation. GCM provides assurance of the confidentiality of data through the
 * AES Counter mode of operation for DRAFT 920 encryption. Authenticity of the
 * confidential data is assured through the GHASH engine. Refer to the NIST Special
 * Publication 800-38D Recommendation for more complete information.
 *
 * \section asfdoc_sam0_drivers_aes_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 * \section asfdoc_sam0_drivers_aes_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam0_drivers_aes_extra. This includes:
 *  - \ref asfdoc_sam0_drivers_aes_extra_acronyms
 *  - \ref asfdoc_sam0_drivers_aes_extra_dependencies
 *  - \ref asfdoc_sam0_drivers_aes_extra_errata
 *  - \ref asfdoc_sam0_drivers_aes_extra_history
 *
 * \section asfdoc_sam0_drivers_aes_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_drivers_aes_exqsg.
 *
 *
 * \section asfdoc_sam0_drivers_aes_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <system.h>

#ifdef __cplusplus
extern "C" {
#endif

/** AES processing mode. */
enum aes_encrypt_mode {
	AES_DECRYPTION = 0,     /**< Decryption of data will be performed */
	AES_ENCRYPTION,         /**< Encryption of data will be performed */
};

/** AES cryptographic key size. */
enum aes_key_size {
	AES_KEY_SIZE_128 = 0,   /**< AES key size is 128-bit */
	AES_KEY_SIZE_192,       /**< AES key size is 192-bit */
	AES_KEY_SIZE_256,       /**< AES key size is 256-bit */
};

/** AES start mode. */
enum aes_start_mode {
	AES_MANUAL_START = 0,   /**< Manual start mode */
	AES_AUTO_START,         /**< Auto start mode */
};

/** AES operation mode. */
enum aes_operation_mode {
	AES_ECB_MODE = 0,       /**< Electronic Codebook (ECB) */
	AES_CBC_MODE,           /**< Cipher Block Chaining (CBC) */
	AES_OFB_MODE,           /**< Output Feedback (OFB) */
	AES_CFB_MODE,           /**< Cipher Feedback (CFB) */
	AES_CTR_MODE,           /**< Counter (CTR) */
	AES_CCM_MODE,           /**< Counter (CCM) */
	AES_GCM_MODE,           /**< Galois Counter Mode (GCM) */
};

/** AES Cipher FeedBack (CFB) size. */
enum aes_cfb_size {
	AES_CFB_SIZE_128 = 0,   /**< Cipher feedback data size is 128-bit */
	AES_CFB_SIZE_64,        /**< Cipher feedback data size is 64-bit */
	AES_CFB_SIZE_32,        /**< Cipher feedback data size is 32-bit */
	AES_CFB_SIZE_16,        /**< Cipher feedback data size is 16-bit */
	AES_CFB_SIZE_8,         /**< Cipher feedback data size is 8-bit */
};

/** AES countermeasure type */
enum aes_countermeature_type {
	AES_COUNTERMEASURE_TYPE_disabled = 0x0,    /**< Countermeasure type all disabled */
	AES_COUNTERMEASURE_TYPE_1 = 0x01,          /**< Countermeasure1 enabled */
	AES_COUNTERMEASURE_TYPE_2 = 0x02,          /**< Countermeasure2 enabled */
	AES_COUNTERMEASURE_TYPE_3 = 0x04,          /**< Countermeasure3 enabled */
	AES_COUNTERMEASURE_TYPE_4 = 0x08,          /**< Countermeasure4 enabled */
	AES_COUNTERMEASURE_TYPE_ALL = 0x0F,        /**< Countermeasure type all enabled */
};

/**
 * \name Module Status Flags
 *
 * AES status flags, returned by \ref aes_get_status() and cleared by
 * \ref aes_clear_status().
 *
 * @{
 */

/** AES encryption complete.
 */
#define AES_ENCRYPTION_COMPLETE  (1UL << 0)

/** AES GF multiplication complete.
 */
#define AES_GF_MULTI_COMPLETE    (1UL << 1)
/** @} */


/** AES Configuration structure. */
struct aes_config {
	/** AES data mode (decryption or encryption) */
	enum aes_encrypt_mode encrypt_mode;
	/** AES key size */
	enum aes_key_size key_size;
	/** Start mode */
	enum aes_start_mode start_mode;
	/** AES cipher operation mode*/
	enum aes_operation_mode opmode;
	/** Cipher feedback data size */
	enum aes_cfb_size cfb_size;
	/** Countermeasure type */
	enum aes_countermeature_type ctype;
	/** Enable XOR key */
	bool enable_xor_key;
	/** Enable key generation */
	bool enable_key_gen;
	/** Last output data mode enable/disable */
	bool lod;
};

#if !defined(__DOXYGEN__)
/**
 * \brief Device structure.
 */
struct aes_module {
	/** AES hardware module. */
	Aes *hw;
	/** AES cipher operation mode.*/
	enum aes_operation_mode opmode;
	/** AES key size. */
	enum aes_key_size key_size;
	/** Cipher feedback data size. */
	enum aes_cfb_size cfb_size;
};
#endif

/**
 * \name Configuration and Initialization
 * @{
 */
void aes_get_config_defaults(struct aes_config *const config);

void aes_set_config(struct aes_module *const module,
					Aes *const hw,
					struct aes_config *const config);

void aes_init(struct aes_module *const module,
				Aes *const hw,
				struct aes_config *const config);

/** @} */

/**
 * \name Start, Enable, and Write
 * @{
 */

/**
 * \brief Start a manual encryption/decryption process.
 *
 * \param[in] module Pointer to the AES software instance struct
 */
static inline void aes_start(struct aes_module *const module)
{
	Assert(module);
	Assert(module->hw);

	module->hw->CTRLB.reg |= AES_CTRLB_START;
}
/**
 * \brief Notifies the module that the next input data block
 * is the beginning of a new message.
 *
 * \param[in] module Pointer to the AES software instance struct
 *
 */
static inline void aes_set_new_message(struct aes_module *const module)
{
	Assert(module);
	Assert(module->hw);
	module->hw->CTRLB.reg |= AES_CTRLB_NEWMSG;
}
/**
 * \brief Clear the indication of the beginning for a new message
 *
 * \param[in] module Pointer to the AES software instance struct
 *
 */
static inline void aes_clear_new_message(struct aes_module *const module)
{
	Assert(module);
	Assert(module->hw);
	module->hw->CTRLB.reg &= ~AES_CTRLB_NEWMSG;
}

void aes_enable(struct aes_module *const module);

void aes_disable(struct aes_module *const module);

void aes_write_key(struct aes_module *const module, const uint32_t *key);

void aes_write_init_vector(struct aes_module *const module, const uint32_t *vector);

void aes_write_input_data(struct aes_module *const module,
		const uint32_t *p_input_data_buffer);

void aes_read_output_data(struct aes_module *const module,
		uint32_t *p_output_data_buffer);

/**
 * \brief Write AES random seed.
 *
 * \param[in] module Pointer to the AES software instance struct
 * \param[in] seed Seed for the random number generator
 */
static inline void aes_write_random_seed(struct aes_module *const module,
										uint32_t seed)
{
	Assert(module);
	Assert(module->hw);

	module->hw->RANDSEED.reg = seed;
}

/** @} */

/**
 * \name Status Management
 * @{
 */

/**
 * \brief Retrieves the current module status.
 *
 * Retrieves the status of the module, giving overall state information.
 *
 * \param[in] module Pointer to the AES software instance struct
 *
 * \retval AES_ENCRYPTION_COMPLETE   AES encryption complete
 * \retval AES_GF_MULTI_COMPLETE   AES GF multiplication complete
 */
static inline uint32_t aes_get_status(struct aes_module *const module)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	uint32_t int_flags = module->hw->INTFLAG.reg;
	uint32_t status_flags = 0;

	if (int_flags & AES_INTFLAG_ENCCMP) {
		status_flags |= AES_ENCRYPTION_COMPLETE;
	}

	if (int_flags & AES_INTFLAG_GFMCMP) {
		status_flags |= AES_GF_MULTI_COMPLETE;
	}

	return status_flags;
}

/**
 * \brief Clears a module status flag.
 *
 * Clears the given status flag of the module.
 *
 * \param[in] module Pointer to the AES software instance struct
 * \param[in] status_flags Bitmask flags to clear
 */
static inline void aes_clear_status(
		struct aes_module *const module,
		const uint32_t status_flags)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	uint32_t int_flags = 0;

	if (status_flags & AES_ENCRYPTION_COMPLETE) {
		int_flags |= AES_INTENCLR_ENCCMP;
	}

	if (status_flags & AES_GF_MULTI_COMPLETE) {
		int_flags |= AES_INTENCLR_GFMCMP;
	}

	/* Clear interrupt flag */
	module->hw->INTFLAG.reg = int_flags;
}

/** @} */

/**
 * \name Galois Counter Mode
 * @{
 */

/**
 * \brief  Get the AES GCM Hash Value.
 *
 * \param[in] module Pointer to the AES software instance struct
 * \param[in] id Index into the GHASH array (range 0 to 3)
 *
 * \return The content of the GHASHRx[x = 0...3] value.
 */
static inline uint32_t aes_gcm_read_ghash(struct aes_module *const module, uint32_t id)
{
	Assert(module);
	Assert(module->hw);

	return module->hw->GHASH[id].reg;
}

/**
 * \brief  Set the AES GCM Hash Value.
 *
 * \param[in] module Pointer to the AES software instance struct
 * \param[in] id Index into the GHASHx array (range 0 to 3)
 * \param[in] ghash GCM hash value
 */
static inline void aes_gcm_write_ghash(struct aes_module *const module,
									uint32_t id,uint32_t ghash)
{
	Assert(module);
	Assert(module->hw);

	module->hw->GHASH[id].reg = ghash;
}


/**
 * \brief  Get AES GCM Hash key.
 *
 * \param[in] module Pointer to the AES software instance struct
 * \param[in]  id    Index into the Hash key array (range 0 to 3)
 *
 * \return The contents of the HASHKEYx[x = 0...3] specified.
 */
static inline uint32_t aes_gcm_read_hash_key(struct aes_module *const module,
											uint32_t id)
{
	Assert(module);
	Assert(module->hw);

	return module->hw->HASHKEY[id].reg;
}

/**
 * \brief  Set the AES GCM Hash key.
 *
 * \param[in] module Pointer to the AES software instance struct
 * \param[in] id Index into the Hash key array (range 0 to 3)
 * \param[in] key GCM Hash key
 */
static inline void aes_gcm_write_hash_key(struct aes_module *const module,
										uint32_t id, uint32_t key)
{
	Assert(module);
	Assert(module->hw);

	module->hw->HASHKEY[id].reg = key;
}

/**
 * \brief  Get the AES GCM cipher length.
 *
 * \param[in] module Pointer to the AES software instance struct
 *
 * \return The contents of the HASHKEYx[x = 0...3] specified.
 */
static inline uint32_t aes_gcm_read_cipher_len(struct aes_module *const module)
{
	Assert(module);
	Assert(module->hw);

	return (module->hw->CIPLEN.reg);
}

/**
 * \brief  Set the AES GCM cipher length.
 *
 * \param[in] module Pointer to the AES software instance struct
 * \param[in] len Cipher length
 */
static inline void aes_gcm_write_cipher_len(struct aes_module *const module,
										uint32_t len)
{
	Assert(module);
	Assert(module->hw);

	module->hw->CIPLEN.reg = len;
}

/**
 * \brief  Set GCM end of input message status.
 *
 * \param[in] module Pointer to the AES software instance struct
 */
static inline void aes_gcm_set_end_message_status(struct aes_module *const module)
{
	Assert(module);
	Assert(module->hw);

	module->hw->CTRLB.reg |= AES_CTRLB_EOM;
}

/**
 * \brief  Clear GCM end of input message status.
 *
 * \param[in] module Pointer to the AES software instance struct
 */
static inline void aes_gcm_clear_end_message_status(struct aes_module *const module)
{
	Assert(module);
	Assert(module->hw);

	module->hw->CTRLB.reg &= ~AES_CTRLB_EOM;
}

/**
 * \brief  Set GF multiplication of GCM mode.
 *
 * \param[in] module Pointer to the AES software instance struct
 */
static inline void aes_gcm_set_gf_multiplication(struct aes_module *const module)
{
	Assert(module);
	Assert(module->hw);

	module->hw->CTRLB.reg |= AES_CTRLB_GFMUL;
}

/** @} */

#ifdef __cplusplus
}
#endif

 /** @} */

/**
 * \page asfdoc_sam0_drivers_aes_extra Extra Information for Advanced Encryption Standard
 *
 * \section asfdoc_sam0_drivers_aes_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *  <tr>
 *      <th>Acronym</th>
 *      <th>Definition</th>
 *  </tr>
 *  <tr>
 *      <td>AAD</td>
 *      <td>Additional Authenticated Data</td>
 * </tr>
 *  <tr>
 *      <td>CBC</td>
 *      <td>Cipher Block Chaining</td>
 * </tr>
 *  <tr>
 *      <td>CFB</td>
 *      <td>Cipher Feedback</td>
 * </tr>
 *  <tr>
 *      <td>CTR</td>
 *      <td> Counter</td>
 * </tr>
 *  <tr>
 *      <td>DMA</td>
 *      <td>Direct Memory Access</td>
 * </tr>
 *  <tr>
 *      <td>DMAC</td>
 *      <td>DMA Controller</td>
 * </tr>
 *  <tr>
 *      <td>ECB</td>
 *      <td>Electronic Codebook</td>
 * </tr>
 *  <tr>
 *      <td>GCM</td>
 *      <td>Galois Counter Mode</td>
 * </tr>
 *  <tr>
 *      <td>OFB</td>
 *      <td>Output Feedback</td>
 * </tr>
 *  <tr>
 *      <td>QSG</td>
 *      <td>Quick Start Guide</td>
 * </tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_drivers_aes_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - None
 *
 *
 * \section asfdoc_sam0_drivers_aes_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_drivers_aes_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
 *	<tr>
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_sam0_drivers_aes_exqsg Examples for Advanced Encryption Standard
 *
 * This is a list of the available Quick Start Guides (QSGs) and example
 * applications for \ref asfdoc_sam0_drivers_aes_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_aes_basic_use_case
 *  - \subpage asfdoc_sam0_aes_callback_use_case
 *  - \subpage asfdoc_sam0_aes_dma_use_case
 *
 * \page asfdoc_sam0_drivers_aes_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *      <th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *      <td>42445B</td>
 *		<td>12/2015</td>
 *		<td>Added support for SAM L22</td>
 *	</tr>
 *	<tr>
 *      <td>42445A</td>
 *		<td>06/2015</td>
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 *
 */

 #ifdef __cplusplus
}
#endif

#endif  /* AES_H_INCLUDED */
