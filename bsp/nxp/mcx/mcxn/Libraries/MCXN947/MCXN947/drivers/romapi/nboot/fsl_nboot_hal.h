/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_NBOOT_HAL_H_
#define _FSL_NBOOT_HAL_H_

#include "fsl_nboot.h"

/*! @addtogroup nbot_hal */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The size of the UUID. */
#define NBOOT_UUID_SIZE_IN_WORD (4)
#define NBOOT_UUID_SIZE_IN_BYTE (NBOOT_UUID_SIZE_IN_WORD * 4)

/*! @brief The size of the PUF activation code. */
#define NBOOT_PUF_AC_SIZE_IN_BYTE (996)
/*! @brief The size of the PUF key code. */
#define NBOOT_PUF_KC_SIZE_IN_BYTE (84)

/*! @brief The size of the key store. */
#define NBOOT_KEY_STORE_SIZE_IN_BYTE (NBOOT_PUF_AC_SIZE_IN_BYTE + 8)

/*! @brief The size of the root of trust key table hash. */
#define NBOOT_ROOT_ROTKH_SIZE_IN_WORD (12)
#define NBOOT_ROOT_ROTKH_SIZE_IN_BYTE (NBOOT_ROOT_ROTKH_SIZE_IN_WORD * 4)

/*! @brief The size of the blob with Key Blob. */
#define NBOOT_KEY_BLOB_SIZE_IN_BYTE_256 (32)
#define NBOOT_KEY_BLOB_SIZE_IN_BYTE_384 (48)
#define NBOOT_KEY_BLOB_SIZE_IN_BYTE_MAX (NBOOT_KEY_BLOB_SIZE_IN_BYTE_384)

/*! @brief The mask of the value of the debug state . */
#define NBOOT_DBG_AUTH_DBG_STATE_MASK (0x0000FFFFu)
/*! @brief The shift inverted value of the debug state. */
#define NBOOT_DBG_AUTH_DBG_STATE_SHIFT (16)
/*! @brief The value with all debug feature disabled. */
#define NBOOT_DBG_AUTH_DBG_STATE_ALL_DISABLED (0xFFFF0000u)

#define NBOOT_ROOT_OF_TRUST_HASH_SIZE_IN_BYTES (48u)

#define NBOOT_EC_COORDINATE_384_SIZE_IN_BYTES (48u)
#define NBOOT_EC_COORDINATE_MAX_SIZE          NBOOT_EC_COORDINATE_384_SIZE_IN_BYTES

/* SB3.1 */
#define NBOOT_SB3_CHUNK_SIZE_IN_BYTES         (256u)
#define NBOOT_SB3_BLOCK_HASH256_SIZE_IN_BYTES (32u)
#define NBOOT_SB3_BLOCK_HASH384_SIZE_IN_BYTES (48u)

/*!
 * @brief NBOOT type for a timestamp
 *
 * This type defines the NBOOT timestamp
 *
 */
typedef uint32_t nboot_timestamp_t[2];

/*!
 * @brief NBOOT SB3.1 header type
 *
 * This type defines the header used in the SB3.1 manifest
 *
 */
typedef struct _nboot_sb3_header
{
    uint32_t magic;         /*!< offset 0x00: Fixed 4-byte string of 'sbv3' without the trailing NULL */
    uint32_t formatVersion; /*!< offset 0x04: (major = 3, minor = 1); The format version determines the manifest
                               (block0) size. */
    uint32_t flags;         /*!< offset 0x08: not defined yet, keep zero for future compatibility */
    uint32_t blockCount;    /*!< offset 0x0C: Number of blocks not including the manifest (block0). */
    uint32_t
        blockSize; /*!< offset 0x10: Size in bytes of data block (repeated blockCount times for SB3 data stream). */
    nboot_timestamp_t timeStamp;     /*!< offset 0x14: 64-bit value used as key derivation data. */
    uint32_t firmwareVersion;        /*!< offset 0x1c: Version number of the included firmware */
    uint32_t imageTotalLength;       /*!< offset 0x20: Total manifest length in bytes, including signatures etc. */
    uint32_t imageType;              /*!< offset 0x24: image type and flags */
    uint32_t certificateBlockOffset; /*!< offset 0x28: Offset from start of header block to the certificate block. */
    uint8_t description[16];         /*!< offset 0x32: This field provides description of the file. It is an arbitrary
                                                      string injected by the signing tool, which helps to identify the file. */
} nboot_sb3_header_t;

/*!
 * @brief NBOOT type for the header of the certificate block
 *
 * This type defines the NBOOT header of the certificate block, it is part of the nboot_certificate_block_t
 *
 */
typedef struct _nboot_certificate_header_block
{
    uint32_t magic;                   /*!< magic number. */
    uint32_t formatMajorMinorVersion; /*!< format major minor version */
    uint32_t certBlockSize;           /*!< Size of the full certificate block */
} nboot_certificate_header_block_t;

typedef uint8_t nboot_ctrk_hash_t[NBOOT_ROOT_OF_TRUST_HASH_SIZE_IN_BYTES];

/*!
 * @brief NBOOT type for the hash table
 *
 * This type defines the NBOOT hash table
 *
 */
typedef struct _nboot_ctrk_hash_table
{
    nboot_ctrk_hash_t ctrkHashTable[NBOOT_ROOT_CERT_COUNT];
} nboot_ctrk_hash_table_t;

/*!
 * @brief NBOOT type for an ECC coordinate
 *
 * This type defines the NBOOT ECC coordinate type
 *
 */
typedef uint8_t
    nboot_ecc_coordinate_t[NBOOT_EC_COORDINATE_MAX_SIZE]; /*!< ECC point coordinate, up to 384-bits. big endian. */

/*!
 * @brief NBOOT type for an ECC point
 *
 * This type defines the NBOOT ECC point type
 */
typedef struct
{
    nboot_ecc_coordinate_t x; /*!< x portion of the ECDSA public key, up to 384-bits. big endian. */
    nboot_ecc_coordinate_t y; /*!< y portion of the ECDSA public key, up to 384-bits. big endian. */
} nboot_ecdsa_public_key_t;

/*!
 * @brief NBOOT type for the root certificate block
 *
 * This type defines the NBOOT root certificate block, it is part of the nboot_certificate_block_t
 */
typedef struct _nboot_root_certificate_block
{
    uint32_t flags;                         /*!< root certificate flags */
    nboot_ctrk_hash_table_t ctrkHashTable;  /*!< hash table */
    nboot_ecdsa_public_key_t rootPublicKey; /*!< root public key */
} nboot_root_certificate_block_t;

/*!
 * @brief NBOOT type for an ECC signature
 *
 * This type defines the NBOOT ECC signature type
 */
typedef struct
{
    nboot_ecc_coordinate_t r; /*!< r portion of the ECDSA signature, up to 384-bits. big endian. */
    nboot_ecc_coordinate_t s; /*!< s portion of the ECDSA signature, up to 384-bits. big endian. */
} nboot_ecdsa_signature_t;

/*!
 * @brief NBOOT type for the isk block
 *
 * This type defines the constant length part of an NBOOT isk block
 */
typedef struct
{
    uint32_t signatureOffset; /*!< Offset of signature in ISK block. */
    uint32_t constraints;     /*!< Version number of signing certificate. */
    uint32_t iskFlags;        /*!< Reserved for definiton of ISK certificate flags. */
    nboot_ecdsa_public_key_t
        iskPubKey; /*!< Public key of signing certificate. Variable length; only used to determine start address*/
    nboot_ecdsa_public_key_t userData; /*!< Space for at lest one addition public key*/
    nboot_ecdsa_signature_t iskSign;   /*!< ISK signature*/
} nboot_isk_block_t;

/*!
 * @brief NBOOT type for the certificate block
 *
 * This type defines the constant length part of an NBOOT certificate block
 */
typedef struct _nboot_certificate_block
{
    nboot_certificate_header_block_t header;
    nboot_root_certificate_block_t rootCertBlock; /*! Details of selected root certificate (root certificate which will
                                                     be used for ISK signing/SB3 header signing) */
    nboot_isk_block_t iskBlock;
} nboot_certificate_block_t;

#define NBOOT_SB3_MANIFEST_MAX_SIZE_IN_BYTES                                                                  \
    (sizeof(nboot_sb3_header_t) + NBOOT_SB3_BLOCK_HASH384_SIZE_IN_BYTES + sizeof(nboot_certificate_block_t) + \
     NBOOT_EC_COORDINATE_MAX_SIZE * 2)
#define NBOOT_SB3_BLOCK_MAX_SIZE_IN_BYTES \
    (4 /* blockNumber */ + NBOOT_SB3_BLOCK_HASH384_SIZE_IN_BYTES + NBOOT_SB3_CHUNK_SIZE_IN_BYTES)

/*! @brief The size of the DICE certificate. */
#define NBOOT_DICE_CSR_SIZE_IN_WORD  (36)
#define NBOOT_DICE_CSR_SIZE_IN_BYTES (NBOOT_DICE_CSR_SIZE_IN_WORD * 4)

/*! @brief The physical address to put the DICE certificate. */
#define NBOOT_DICE_CSR_ADDRESS (0x30000000u)

/*! @brief The offset for the PRCINE/IPED erase region return by nboot mem checker. */
#define NBOOT_IPED_IV_OFFSET (3U)

#define NBOOT_IMAGE_CMAC_UPDATE_NONE   (0u)
#define NBOOT_IMAGE_CMAC_UPDATE_INDEX0 (1u)
#define NBOOT_IMAGE_CMAC_UPDATE_INDEX1 (2u)
#define NBOOT_IMAGE_CMAC_UPDATE_BOTH   (3u)
#define NBOOT_IMAGE_CMAC_UPDATE_MASK   (3u)

#define NBOOT_CMPA_CMAC_UPDATE_MASK  (0x1Cu)
#define NBOOT_CMPA_CMAC_UPDATE_SHIFT (0x2u)

#define NBOOT_CMPA_UPDATE_CMAC_PFR                (0x2u)
#define NBOOT_CMPA_UPDATE_CMAC_PFR_OTP_OEM_SECURE (0x3u)
#define NBOOT_CMPA_UPDATE_CMAC_PFR_OTP_OEM_CLOSE  (0x5u)
#define NBOOT_CMPA_UPDATE_CMAC_PFR_OTP_OEM_LOCKED (0x6u)

/*! @brief Algorithm used for nboot HASH operation */
typedef enum _nboot_hash_algo_t
{
    kHASH_Sha1   = 1, /*!< SHA_1 */
    kHASH_Sha256 = 2, /*!< SHA_256 */
    kHASH_Sha512 = 3, /*!< SHA_512 */
    kHASH_Aes    = 4, /*!< AES */
    kHASH_AesIcb = 5, /*!< AES_ICB */
} nboot_hash_algo_t;

/*! @} */

#endif /*_FSL_NBOOT_HAL_H_ */
