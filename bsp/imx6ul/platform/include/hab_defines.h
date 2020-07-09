/*
 * Copyright (c) 2008-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file hab_defines.h
 * @brief defines for data structures and macros used for enabling secure boot
 *
 * @ingroup diag_init
 */
#ifndef HAB_DEFINES_H
#define HAB_DEFINES_H
/*===========================================================================
                            INCLUDE FILES
=============================================================================*/
#include <stdint.h>             /* for integer types */
#include <stdbool.h>            /* for bool type */
#include <stddef.h>             /* for NULL and offsetof() */
/*===========================================================================
                              CONSTANTS
=============================================================================*/
/** @addtogroup struct
 *  @{ 
 */

#define HDR_BYTES 4  /* cannot use sizeof(hab_hdr_t) in preprocessor */

/** @name External data structure tags
 * @anchor dat_tag
 *
 * Tag values 0x00 .. 0xef are reserved for HAB.  Values 0xf0 .. 0xff
 * are available for custom use.
 */
/*@{*/
#define HAB_TAG_IVT  0xd1       /**< Image Vector Table */
#define HAB_TAG_DCD  0xd2       /**< Device Configuration Data */
#define HAB_TAG_CSF  0xd4       /**< Command Sequence File */
#define HAB_TAG_CRT  0xd7       /**< Certificate */
#define HAB_TAG_SIG  0xd8       /**< Signature */
#define HAB_TAG_EVT  0xdb       /**< Event */
#define HAB_TAG_RVT  0xdd       /**< ROM Vector Table */
#define HAB_TAG_WRP  0x81       /**< Wrapped Key */
#define HAB_TAG_MAC  0xac       /**< Message Authentication Code */
/* Values 00 ... 7e reserved for internal use.  Values b0 ... cf reserved for
 * CSF commands.  Values e0 ... ef reserved for key types.
 *
 * Available values: 82, 84, 87, 88, 8b, 8d, 8e, 90, 93, 95, 96, 99, 9a,
 * 9c, 9f, a0, a3, a5, a6, a9, aa, af
 *
 * Custom values: f0, f3, f5, f6, f9, fa, fc, ff
 */
/*@}*/

/** @name HAB version */
/*@{*/
#define HAB_MAJOR_VERSION  4    /**< Major version of this HAB release */
#define HAB_MINOR_VERSION  1    /**< Minor version of this HAB release */
#define HAB_VER_MAJ_WIDTH 4     /**< Major version field width  */
#define HAB_VER_MAJ_SHIFT 4     /**< Major version field offset  */
#define HAB_VER_MIN_WIDTH 4     /**< Minor version field width  */
#define HAB_VER_MIN_SHIFT 0     /**< Minor version field offset  */
/** Full version of this HAB release @hideinitializer */
#define HAB_VERSION HAB_VER(HAB_MAJOR_VERSION, HAB_MINOR_VERSION) 
/** Base version for this HAB release @hideinitializer */
#define HAB_BASE_VERSION HAB_VER(HAB_MAJOR_VERSION, 0) 

/*@}*/

/*  @} struct */

/*---------------------------------------------------------------------------*/

/** @addtogroup cmd
 *  @{ 
 */

/** @name Command tags
 * @anchor cmd_tag
 *
 * Tag values 0xb0 .. 0xcf are reserved for HAB.  Values 0xf0 .. 0xff
 * are available for custom use.
 */
/*@{*/
#define HAB_CMD_SET       0xb1  /**< Set */
#define HAB_CMD_INS_KEY   0xbe  /**< Install Key */
#define HAB_CMD_AUT_DAT   0xca  /**< Authenticate Data */
#define HAB_CMD_WRT_DAT   0xcc  /**< Write Data */
#define HAB_CMD_CHK_DAT   0xcf  /**< Check Data */
#define HAB_CMD_NOP       0xc0  /**< No Operation */
#define HAB_CMD_INIT      0xb4  /**< Initialise */
#define HAB_CMD_UNLK      0xb2  /**< Unlock */
#ifdef HAB_FUTURE
#define HAB_CMD_RMV_KEY         /**< Remove Key */
#define HAB_CMD_INS_REF         /**< Install Reference Data */
#define HAB_CMD_INS_PLG         /**< Install Plugin */
#define HAB_CMD_RMV_PLG         /**< Remove Plugin */
#define HAB_CMD_CHK_VER         /**< Check SW Version */
#endif
/* Remaining values: b7, b8, bb, bd, c3, c5, c6, c9 */
/*@}*/

/*  @} cmd */

/*---------------------------------------------------------------------------*/

/** @addtogroup pcl
 *  @{ 
 */

/** @name Protocol tags
 * @anchor pcl_tag 
 *
 * Tag values 0x00 .. 0xef are reserved for HAB.  Values 0xf0 .. 0xff are
 * available for custom use.
 */
/*@{*/
#define HAB_PCL_SRK      0x03   /**< SRK certificate format */
#define HAB_PCL_X509     0x09   /**< X.509v3 certificate format */
#define HAB_PCL_CMS      0xc5   /**< CMS/PKCS#7 signature format */
#define HAB_PCL_BLOB     0xbb   /**< SHW-specific wrapped key format */
#define HAB_PCL_AEAD     0xa3   /**< Proprietary AEAD MAC format */
#ifdef HAB_FUTURE
#define HAB_PCL_WTLS     0x05   /**< OMA WTLS certificate format */
#define HAB_PCL_FSL      0x0f   /**< FSL bound signature protocol */
#define HAB_PCL_HMAC     0x30   /**< NIST HMAC message authentication */
#define HAB_PCL_CBCMAC   0x33   /**< CBC-MAC message authentication */
#endif
/*@}*/

/* Available values: 06, 0a, 0c, 11, 12, 14, 17, 18, 1b, 1d, 1e, 21, 22, 24,
 * 27, 28, 2b, 2d, 2e, 35, 36, 39, 3a, 3c, 3f, 41, 42, 44, 47, 48, 4b, 4d, 4e,
 * 50, 53, 55, 56, 59, 5a, 5c, 5f, 60, 63, 65, 66, 69, 6a, 6c, 6f, 71, 72, 74,
 * 77, 78, 7b, 7d, 7e, 81, 82, 84, 87, 88, 8b, 8d, 8e, 90, 93, 95, 96, 99, 9a,
 * 9c, 9f, a0, a5, a6, a9, aa, ac, af, b1, b2, b4, b7, b8, bd, be, c0, c3, c6,
 * c9, ca, cc, cf, d1, d2, d4, d7, d8, db, dd, de, e1, e2, e4, e7, e8, eb, ed,
 * ee
 *
 * Custom values: f0, f3, f5, f6, f9, fa, fc, ff
 */

/*  @} pcl */

/*---------------------------------------------------------------------------*/

/** @addtogroup alg
 *  @{ 
 */

/** @name Algorithm types
 * @anchor alg_typ
 *
 * The most-significant nibble of an algorithm ID denotes the algorithm
 * type.  Algorithms of the same type share the same interface.
 *
 * Types 0x0 .. 0xc are reserved for HAB.  Types 0xd .. 0xf are available for
 * custom use.  Within each reserved type N in 0 .. c, tag values 0xN0 .. 0xNc
 * are reserved for HAB.  Values 0xNd .. 0xNf are available for custom use.
 */
/*@{*/
#define HAB_ALG_ANY      0x0    /**< Algorithm type ANY */
#define HAB_ALG_HASH     0x1    /**< Hash algorithm type */
#define HAB_ALG_SIG      0x2    /**< Signature algorithm type */
#define HAB_ALG_FF       0x3    /**< Finite field arithmetic */
#define HAB_ALG_EC       0x4    /**< Elliptic curve arithmetic */
#define HAB_ALG_CIPHER   0x5    /**< Cipher algorithm type */
#define HAB_ALG_MODE     0x6    /**< Cipher/hash modes */
#define HAB_ALG_WRAP     0x7    /**< Key wrap algorithm type */
/*@}*/

/** @name Algorithm type ANY
 *
 * Algorithms of type ANY have no common interface: the protocol must know
 * what to do.
 */
/*@{*/
#ifdef HAB_FUTURE
#define HAB_ALG_RANDOM          /**< Random number generation */
#endif
/* Available values: 03, 05, 06, 09, 0a, 0c, 0f
 */
/*@}*/

/** @name Hash algorithms */
/*@{*/
#define HAB_ALG_SHA1     0x11   /**< SHA-1 algorithm ID */
#define HAB_ALG_SHA256   0x17   /**< SHA-256 algorithm ID */
#define HAB_ALG_SHA512   0x1b   /**< SHA-512 algorithm ID */
/* Available values: 0x14, 0x12, 18, 1d, 1e
 */
/*@}*/

/** @name Signature algorithms */
/*@{*/
#define HAB_ALG_PKCS1    0x21   /**< PKCS#1 RSA signature algorithm  */
#ifdef HAB_FUTURE
#define HAB_ALG_DSA             /**< NIST DSA signature algorithm */
#define HAB_ALG_ECDSA           /**< NIST ECDSA signature algorithm */
#endif
/* Available values: 22, 24, 27, 28, 2b, 2d, 2e
 */
/*@}*/

/** @name Cipher algorithms */
/*@{*/
#define HAB_ALG_AES      0x55   /**< AES algorithm ID */
/* Available values: 50, 53, 56, 59, 5a, 5c, 5f
 */
/*@}*/

/** @name Cipher or hash modes */
/*@{*/
#define HAB_MODE_CCM      0x66  /**< Counter with CBC-MAC */
#ifdef HAB_FUTURE
#define HAB_MODE_HMAC           /**< HMAC hash mode */
#endif
/* Available values: 60, 63, 65, 69, 6a, 6c, 6f
 */
/*@}*/

/** @name Key wrap algorithms */
/*@{*/
#define HAB_ALG_BLOB      0x71  /**< SHW-specific key wrap */
/* Available values: 72, 74, 77, 78, 7b, 7d, 7e
 */
/*@}*/

/* Available values: 81, 82, 84, 87, 88, 8b, 8d, 8e, 90, 93, 95, 96, 99, 9a,
 * 9c, 9f, a0, a3, a5, a6, a9, aa, ac, af, b1, b2, b4, b7, b8, bb, bd, be, c0,
 * c3, c5, c6, c9, ca, cc, cf, d1, d2, d4, d7, d8, db, dd, de, e1, e2, e4, e7,
 * e8, eb, ed, ee, f0, f3, f5, f6, f9, fa, fc, ff
 */

/*  @} alg */

/*---------------------------------------------------------------------------*/

/** @addtogroup eng
 *  @{ 
 */

/** @name Engine plugin tags 
 *  @anchor eng_tag
 *
 * Tag values 0x00 .. 0xef and 0xff are reserved for HAB.  Values 0xf0 .. 0xfe
 * are available for custom use.
 */
/*@{*/
#define HAB_ENG_ANY      0x00   /**< First compatible engine will be
                                 * selected automatically (no engine
                                 * configuration parameters are allowed).
                                 */
#define HAB_ENG_SCC      0x03   /**< Security controller */
#define HAB_ENG_RTIC     0x05   /**< Run-time integrity checker */
#define HAB_ENG_SAHARA   0x06   /**< Crypto accelerator */
#define HAB_ENG_CSU      0x0a   /**< Central Security Unit */
#define HAB_ENG_SRTC     0x0c   /**< Secure clock */
#ifdef HAB_FUTURE
#define HAB_ENG_RNG      0x09   /**< Standalone random number generator */
#define HAB_ENG_SJC      0x0f   /**< Secure JTAG controller */
#define HAB_ENG_WDOG     0x11   /**< Watchdog timer */
#define HAB_ENG_SRC      0x12   /**< System Reset Controller */
#define HAB_ENG_SPBA     0x14   /**< Shared Peripheral Bus Arbiter */
#define HAB_ENG_IIM      0x17   /**< Fuse controller */
#define HAB_ENG_IOMUX    0x18   /**< IO multiplexer */
#endif
#define HAB_ENG_DCP      0x1b   /**< Data Co-Processor */
#define HAB_ENG_CAAM     0x1d   /**< Cryptographic Acceleration and
                                     Assurance Module */
#define HAB_ENG_SNVS     0x1e   /**< Secure Non-Volatile Storage */
#define HAB_ENG_OCOTP    0x21   /**< Fuse controller */
/** @cond rom */
#define HAB_ENG_DTCP     0x22   /**< DTCP co-processor */
#define HAB_ENG_ROM      0x36   /**< Protected ROM area */
#define HAB_ENG_HDCP     0x24   /**< HDCP co-processor */
#define HAB_ENG_RTL      0x77   /**< @rom RTL simulation engine */
/** @endcond */
#define HAB_ENG_SW       0xff   /**< Software engine */
/* Available values: 27, 28, 2b, 2d, 2e, 30, 33, 35,
 * 39, 3a, 3c, 3f, 41, 42, 44, 47, 48, 4b, 4d, 4e, 50, 53, 55, 56, 59, 5a,
 * 5c, 5f, 60, 63, 65, 66, 69, 6a, 6c, 6f, 71, 72, 74, 78, 7b, 7d, 7e, 81,
 * 82, 84, 87, 88, 8b, 8d, 8e, 90, 93, 95, 96, 99, 9a, 9c, 9f, a0, a3, a5, a6,
 * a9, aa, ac, af, b1, b2, b4, b7, b8, bb, bd, be, c0, c3, c5, c6, c9, ca, cc,
 * cf, d1, d2, d4, d7, d8, db, dd, de, e1, e2, e4, e7, e8, eb, ed, ee
 *
 * Custom values: f0, f3, f5, f6, f9, fa, fc
 */
/*@}*/

/*  @} eng */

/*---------------------------------------------------------------------------*/

/** @addtogroup sah
 *  @{ 
 */

/** Maximum data blocks in a single hash  */
#define HAB_SAHARA_BLOCK_MAX 12

/** @cond rom */
/** @rom DMA storage requirement
 *
 * This figure is derived in several parts:
 * - each hash operation needs a 6-word descriptor structure
 * - each data block needs a 3-word link structure
 * - the result needs a 3-word link structure
 * - at least 40 bytes are required for SHA-256 result and memory manager
 * overhead: 64 bytes allows some small overhead.
 */
#define HAB_SAHARA_DMA_MIN_BYTES (24 + HAB_SAHARA_BLOCK_MAX * 12 + 12 + 64)
/** @endcond */

/*  @} sah */

/*---------------------------------------------------------------------------*/

/** @addtogroup dcp
 *  @{ 
 */

/** Maximum data blocks in a single hash */
#define HAB_DCP_BLOCK_MAX 6

/** @cond rom */
/** @rom DMA storage requirement
 *
 * This figure is derived in two parts:
 * - each data block needs an 8-word work packet (descriptor)
 * - at least 40 bytes are required for SHA-256 result and memory manager
 * overhead: 64 bytes allows some small overhead.
 */
#define HAB_DCP_DMA_MIN_BYTES (64 + HAB_DCP_BLOCK_MAX * 32)
/** @endcond */

/*  @} dcp */

/*---------------------------------------------------------------------------*/

/** @addtogroup rtic
 *  @{ 
 */

/** Maximum data blocks in a single hash */
#define HAB_RTIC_BLOCK_MAX 2

/*  @} rtic */

/*---------------------------------------------------------------------------*/

/** @addtogroup scc
 *  @{ 
 */

/** @cond rom */
/** @rom DMA storage requirement
 *
 * This figure is derived in several stages, and assumes plaintext and
 * ciphertext buffers are both allocated in the DMA region :
 * - 4 blocks of plaintext required
 * - 4 blocks of ciphertext required
 * - each block is 16 bytes long
 * - the plaintext address must be block-aligned (up to 15 bytes overhead)
 * - the ciphertext address must be block-aligned (up to 3 bytes overhead)
 * - at least 8 bytes of memory manager overhead: allow 32 for comfort
 */
#define HAB_SCC_DMA_MIN_BYTES ( (4+4)*16 + 15 + 3 + 32)
/** @endcond */

/*  @} scc */

/*---------------------------------------------------------------------------*/

/** @addtogroup caam
 *  @{ 
 */

/** Maximum data blocks in an @ref cmd_aut_dat command */
#define HAB_CAAM_BLOCK_MAX 8

/** @cond rom */
/** @rom Hash DMA storage requirement
 *
 * This figure is derived in several parts:
 * - each hash operation needs
 *   - a 7-word descriptor, and
 *   - a 32-byte result buffer (for SHA-256),
 *   - giving a base requirement of (7*4 + 32) = 60 bytes
 * - each data block needs a 4-word link structure
 * - memory manager overhead is at least 8 bytes: 16 bytes allows flexibility
 */
#define HAB_CAAM_HSH_DMA_MIN_BYTES (60 + HAB_CAAM_BLOCK_MAX * 16 + 16)

/** @rom AEAD DMA storage requirement
 *
 * This figure is derived in several parts:
 * - each AEAD operation needs
 *   - a 16-word descriptor, 
 *   - a 32-byte initial context value (B0 and CTR0), and
 *   - a 16-byte MAC value,
 *   - giving a base requirement of (16*4 + 32 + 16) = 112 bytes
 * - each data block needs a 4-word link structure
 * - memory manager overhead is at least 8 bytes: 16 bytes allows flexibility
 */
#define HAB_CAAM_CCM_DMA_MIN_BYTES (112 + HAB_CAAM_BLOCK_MAX * 16 + 16)

/** @rom RNG DMA storage requirement
 *
 * This figure is derived in several parts:
 * - each DRNG test operation allocates a DMA area with
 *   - a 1-word header, and
 *   - a 3-word job ring area, and
 *   - a 54-word descriptor,
 *   - requiring a total 58*4 = 232 bytes
 * - each DRNG test operation also allocates a DMA area with
 *   - a 1-word header, and
 *   - a 32-byte result buffer
 *   - requiring a total 4 + 32 = 36 bytes
 */
#define HAB_CAAM_RNG_DMA_MIN_BYTES (232 + 32)
/** @endcond */

/*  @} caam */

/*---------------------------------------------------------------------------*/

/** @addtogroup key
 *  @{ 
 */

/** @name Key types
 * @anchor key_types
 *
 * Tag values 0xe0 .. 0xef are reserved for HAB.  Values 0xf0 .. 0xff
 * are available for custom use.
 */
/*@{*/
#define HAB_KEY_PUBLIC 0xe1     /**< Public key type: data present */
#define HAB_KEY_SECRET 0xe2     /**< Secret key type: data present */
#define HAB_KEY_MASTER 0xed     /**< Master KEK type */
#define HAB_KEY_HASH   0xee     /**< Any key type: hash only */
/* Available values: e4, e7, e8, eb
 *
 * Custom values: f0, f3, f5, f6, f9, fa, fc, ff
 */
/*@}*/

/** @name Public key store indices */
/*@{*/
#define HAB_IDX_SRK 0           /**< Super-Root Key index */
#define HAB_IDX_CSFK 1          /**< CSF key index */
/*@}*/

/** @name Key Counts */
/*@{*/
#define HAB_SRK_MIN 1           /**< Minimum Super-Root Key count */
#define HAB_SRK_MAX 4           /**< Maximum Super-Root Key count */
#define HAB_KEY_PUBLIC_MAX 5    /**< Maximum installed public key count
                                 *   (incl Super-Root Key)
                                 */
#define HAB_KEY_SECRET_MAX 4    /**< Maximum installed secret key count
                                 *   (excl Master KEKs)
                                 */
/*@}*/

/*  @} key */

/*---------------------------------------------------------------------------*/

#ifdef HAB_FUTURE
/** @addtogroup key_ecdsa
 *  @{ 
 */

/** @name Bitfield definitions */
/*@{*/
#define HAB_KEY_ECDSA_FLG_WIDTH 8 /**< Width of @a flg field */
#define HAB_KEY_ECDSA_FLG_SHIFT 0 /**< Offset of @a flg field */
#define HAB_KEY_ECDSA_TYP_WIDTH 8 /**< Width of @a typ field */
#define HAB_KEY_ECDSA_TYP_SHIFT 24 /**< Offset of @a typ field */
#define HAB_KEY_ECDSA_SIZ_WIDTH 8 /**< Width of @a siz field */
#define HAB_KEY_ECDSA_SIZ_SHIFT 16 /**< Offset of @a siz field */
#define HAB_KEY_ECDSA_REDBITS_WIDTH 16 /**< Width of @a red_bits field */
#define HAB_KEY_ECDSA_REDBITS_SHIFT 0 /**< Offset of @a red_bits field */
/*@}*/

/*  @} key_ecdsa */
#endif

/*---------------------------------------------------------------------------*/

/** @addtogroup key_pkcs1
 *  @{ 
 */

/** @name Bitfield definitions */
/*@{*/
#define HAB_KEY_PKCS1_FLG_WIDTH 8 /**< Width of @a flg field */
#define HAB_KEY_PKCS1_FLG_SHIFT 0 /**< Offset of @a flg field */
#define HAB_KEY_PKCS1_MODBYTES_WIDTH 16 /**< Width of mod_bytes field */
#define HAB_KEY_PKCS1_MODBYTES_SHIFT 16 /**< Offset of mod_bytes field */
#define HAB_KEY_PKCS1_EXPBYTES_WIDTH 16 /**< Width of exp_bytes field */
#define HAB_KEY_PKCS1_EXPBYTES_SHIFT 0 /**< Offset of exp_bytes field */
/*@}*/

/** @name Binding flag bitfield definitions */
/*@}*/
#define HAB_KEY_BND_FLG_WIDTH 5 /**< Width of binding flags */
#define HAB_KEY_BND_FLG_SHIFT 2 /**< Offset of binding flags */
/*@}*/

/*  @} key_pkcs1 */

/*---------------------------------------------------------------------------*/

/** @addtogroup cmd_wrt_dat
 *  @{
 */

/** @name Parameter bitfield definitions.
 *
 *  Apply to both @ref cmd_wrt_dat and @ref cmd_chk_dat commands. */
/*@{*/
#define HAB_CMD_WRT_DAT_FLAGS_WIDTH 5   /**< @a flags field width */
#define HAB_CMD_WRT_DAT_FLAGS_SHIFT 3   /**< @a flags field offset */
#define HAB_CMD_WRT_DAT_BYTES_WIDTH 3   /**< @a bytes field width */
#define HAB_CMD_WRT_DAT_BYTES_SHIFT 0   /**< @a bytes field offset */
/*@}*/

/*  @} cmd_wrt_dat */

/*---------------------------------------------------------------------------*/

/** @addtogroup bnd_obj
 *  @{
 */

/** @name Binding object IDs 
 * @anchor bnd_ids
 *
 * The ASN.1 object identifiers used to identify HAB binding attributes are
 * defined in the following arc:
 *
@verbatim
      id-fsl  OBJECT IDENTIFIER ::= {
           joint-iso-itu-t(2) country(16) us(840) organization(1) fsl(123456) }
  
      id-habBnd OBJECT IDENTIFIER  ::=  {
           id-fsl hab(32) binding-objects(16) }

      id-habBnd-dat OBJECT IDENTIFIER  ::=  {
           id-habBnd dat(1) }

      id-habBnd-cfg OBJECT IDENTIFIER  ::=  {
           id-habBnd cfg(3) }

      id-habBnd-fid OBJECT IDENTIFIER  ::=  {
           id-habBnd fid(5) }

      id-habBnd-mid OBJECT IDENTIFIER  ::=  {
           id-habBnd mid(6) }

      id-habBnd-cid OBJECT IDENTIFIER  ::=  {
           id-habBnd cid(9) }
@endverbatim
 *
 * The ASN.1 object identifiers used to identify HAB binding attributes are
 * single component extensions of id-habBnd using a component value less than
 * 128 (so that the component can be DER-encoded in a single byte).
 *
 * The DER encoding of an object identifier in this arc is the concatenation
 * of the DER prefix with the single byte identifier for the required binding
 * object. Binding object attribute values are encoded as an ASN.1 SET with
 * a single OCTET STRING member.
 */
/*@{*/

/** DER prefix
 *
 * @todo update description and encoding of binding object identifiers with
 * real fsl value instead of fsl(123456) encoded as 0x87, 0xc4, 0x40, and
 * confirm chosen values for hab(32) and binding-objects(16).
 */
#define HAB_BND_DER_PREFIX \
    {0x06, 0x0a, 0x60, 0x86, 0x48, 0x01, 0x87, 0xc4, 0x40, 0x20, 0x10}
#define HAB_BND_DAT 0x01        /**< Data type (mandatory) */
#define HAB_BND_CFG 0x03        /**< Security configuration */
#define HAB_BND_FID 0x05        /**< Fabrication UID */
#define HAB_BND_MID 0x06        /**< Manufacturing ID */
#define HAB_BND_CID 0x09        /**< Caller ID */
/* Available values: 0a, 0c, 0f, 11, 12, 14, 17, 18, 1b, 1d, 1e, 21, 22, 24,
 * 27, 28, 2b, 2d, 2e, 30, 33, 35, 36, 39, 3a, 3c, 3f, 41, 42, 44, 47, 48, 4b,
 * 4d, 4e, 50, 53, 55, 56, 59, 5a, 5c, 5f, 60, 63, 65, 66, 69, 6a, 6c, 6f, 71,
 * 72, 74, 77, 78, 7b, 7d, 7e
 */
/*@}*/


/** @name Caller IDs
 *
 * Only the ROM caller ID is defined, but other caller IDs may be defined by
 * later boot stages.
 */
/*@{*/
#define HAB_CID_ROM 0   /**< ROM Caller ID */
/*@}*/

/*  @} bnd_obj */

#ifdef HAB_FUTURE
/** @addtogroup sig_fsl
 *  @{
 */

#define HAB_BND_DAT_BYTES 512   /**< Maximum binding data size */

/*  @} sig_fsl */
#endif

/*===========================================================================
                                MACROS
=============================================================================*/
/*
 *    Helper macros
 */
#define HAB_CMD_UNS     0xff

#define DEFAULT_IMG_KEY_IDX     2

#define GEN_MASK(width)                         \
    ((1UL << (width)) - 1)

#define GEN_FIELD(f, width, shift)              \
    (((f) & GEN_MASK(width)) << (shift))

#define PACK_UINT32(a, b, c, d)                          \
    ((uint32_t) ( (((uint32_t)(a) & 0xFF) << 24)          \
                  |(((uint32_t)(b) & 0xFF) << 16)         \
                  |(((uint32_t)(c) & 0xFF) << 8)          \
                  |(((uint32_t)(d) & 0xFF)) ) )

#define EXPAND_UINT32(w)                                                \
    (uint8_t)((w)>>24), (uint8_t)((w)>>16), (uint8_t)((w)>>8), (uint8_t)(w)

#define EXPAND_UINT16(w)                                                \
    (uint8_t)((w)>>8), (uint8_t)(w)

#define HDR(tag, bytes, par)                                            \
    (uint8_t)(tag), (uint8_t)((bytes)>>8), (uint8_t)(bytes), (uint8_t)(par)

#define HAB_VER(maj, min)                                       \
    (GEN_FIELD((maj), HAB_VER_MAJ_WIDTH, HAB_VER_MAJ_SHIFT)     \
     | GEN_FIELD((min), HAB_VER_MIN_WIDTH, HAB_VER_MIN_SHIFT))

#define DCD_DATA(addr, data)    EXPAND_UINT32(addr), EXPAND_UINT32(data)

/*
 *    CSF header
 */

#define CSF_HDR(bytes, HABVER)                  \
    HDR(HAB_TAG_CSF, (bytes), HABVER)
    
    
/*
 *    DCD  header
 */

#define DCD_HDR(bytes, HABVER)                  \
    HDR(HAB_TAG_DCD, (bytes), HABVER)

/*
 *   IVT  header (goes in the struct's hab_hdr_t field, not a byte array)
 */
#define IVT_HDR(bytes, HABVER)                  \
    {HAB_TAG_IVT, {(uint8_t)((bytes)>>8), (uint8_t)(bytes)}, HABVER}

/*
 *    Write Data     
 */

#define WRT_DAT(flags, bytes, address, val_msk)                         \
    HDR(HAB_CMD_WRT_DAT, WRT_DAT_BYTES, WRT_DAT_PAR((flags), (bytes))), \
        EXPAND_UINT32(address),                                         \
        EXPAND_UINT32(val_msk)

#define WRT_DAT_BYTES 12

#define MULTI_WRT_DAT(flags, bytes, address1, val_msk1, address2,       \
                            val_msk2, address3, val_msk3)               \
    HDR(HAB_CMD_WRT_DAT, MULTI_WRT_DAT_BYTES, WRT_DAT_PAR((flags), (bytes))), \
        EXPAND_UINT32(address1),                                        \
        EXPAND_UINT32(val_msk1),                                        \
        EXPAND_UINT32(address2),                                        \
        EXPAND_UINT32(val_msk2),                                        \
        EXPAND_UINT32(address3),                                        \
        EXPAND_UINT32(val_msk3)

#define MULTI_WRT_DAT_BYTES 28

#define WRT_DAT_PAR(flags, bytes)               \
    (GEN_FIELD((flags),                         \
               HAB_CMD_WRT_DAT_FLAGS_WIDTH,     \
               HAB_CMD_WRT_DAT_FLAGS_SHIFT)     \
     | GEN_FIELD((bytes),                       \
                 HAB_CMD_WRT_DAT_BYTES_WIDTH,   \
                 HAB_CMD_WRT_DAT_BYTES_SHIFT))

/*
 *    Check Data (forever)
 */

#define CHK_DAT_FOREVER(flags, bytes, address, mask)                    \
    HDR(HAB_CMD_CHK_DAT, CHK_DAT_FOREVER_BYTES, WRT_DAT_PAR((flags), (bytes))), \
        EXPAND_UINT32(address),                                         \
        EXPAND_UINT32(mask)

#define CHK_DAT_FOREVER_BYTES 12

/*
 *    Check Data (polled)
 */
#define HAB_CMD_CHK_DAT_COUNT 100

#define CHK_DAT(flags, bytes, address, mask, count)                     \
    HDR(HAB_CMD_CHK_DAT, CHK_DAT_BYTES, WRT_DAT_PAR((flags), (bytes))), \
        EXPAND_UINT32(address),                                         \
        EXPAND_UINT32(mask),                                            \
        EXPAND_UINT32(count)

#define CHK_DAT_BYTES 16

/*
 *    Set (generic - used internally only, or to generate invalid commands)
 */

#define SET(bytes, itm, value)                  \
    HDR(HAB_CMD_SET, (bytes), (itm)),           \
        EXPAND_UINT32(value)

/*
 *    Set (MID location)
 */

#define SET_MID(bank, row, bit, fuses)                          \
    HDR(HAB_CMD_SET, SET_MID_BYTES, HAB_VAR_CFG_ITM_MID),       \
        (bank), (row), (bit), (fuses)

#define SET_MID_BYTES 8

/*
 *    Set (default ENG)
 */

#define SET_ENG(alg, eng, cfg)                                  \
    HDR(HAB_CMD_SET, SET_ENG_BYTES, HAB_VAR_CFG_ITM_ENG),       \
        0, (alg), (eng), (cfg)

#define SET_ENG_BYTES 8

/*
 *    Init (engine)
 */

#define INIT(eng)                                               \
    HDR(HAB_CMD_INIT, INIT_BYTES, (eng))

#define INIT_BYTES 4

/*
 *    Unlk (engine)
 */

#define UNLK(eng, ...)                          \
    UNLK_ ## eng(__VA_ARGS__)

#define UNLK_BYTES(eng, ...)                    \
    UNLK_BYTES_ ## eng(__VA_ARGS__)

#define UNLK_HDR(eng, ...)                                      \
    HDR(HAB_CMD_UNLK, UNLK_BYTES_ ## eng(__VA_ARGS__), eng)

#define UNLK_FLG(flg)  \
    0, 0, 0, (uint8_t)(flg)

#define UNLK_FLG_BYTES 4

#define UNLK_HAB_ENG_SRTC(dnc) UNLK_HDR(HAB_ENG_SRTC)
#define UNLK_BYTES_HAB_ENG_SRTC(dnc) HDR_BYTES

#define UNLK_HAB_ENG_SNVS(flg) UNLK_HDR(HAB_ENG_SNVS), UNLK_FLG(flg)
#define UNLK_BYTES_HAB_ENG_SNVS(flg) (HDR_BYTES + UNLK_FLG_BYTES)

#define UNLK_HAB_ENG_CAAM(flg) UNLK_HDR(HAB_ENG_CAAM), UNLK_FLG(flg)
#define UNLK_BYTES_HAB_ENG_CAAM(flg) (HDR_BYTES + UNLK_FLG_BYTES)

/* The next definition uses a GCC extension employing ## to swallow the
 * trailing comma in case the macro is called with only the fixed arguments
 * (i.e. flg here).  This extension appears to work in the GNU compatible mode
 * of RVDS and GHS compilers.
 */
#define UNLK_HAB_ENG_OCOTP(flg, ...)                            \
    UNLK_HDR(HAB_ENG_OCOTP, flg), UNLK_FLG(flg), ## __VA_ARGS__

#define UNLK_BYTES_HAB_ENG_OCOTP(flg, ...)              \
    (HDR_BYTES + UNLK_FLG_BYTES                         \
     + ( ((flg) & (HAB_OCOTP_UNLOCK_FIELD_RETURN        \
                   |HAB_OCOTP_UNLOCK_JTAG               \
                   |HAB_OCOTP_UNLOCK_SCS))              \
         ? STUB_FAB_UID_BYTES                           \
         : 0 ))

#if 0
/* Note: no comma after HDR().  Supplied by _VAL macro if needed */
#define UNLK(eng, val)                               \
    HDR(HAB_CMD_UNLK, UNLK_BYTES_ ## eng, (eng))     \
    UNLK_VAL_ ## eng(val)

#define UNLK_BYTES(eng)                         \
    UNLK_BYTES_ ## eng

#define UNLK_BYTES_HAB_ENG_SRTC HDR_BYTES
#define UNLK_VAL_HAB_ENG_SRTC(val)      /* no val field */
#define UNLK_BYTES_HAB_ENG_SNVS (HDR_BYTES + 4)
#define UNLK_VAL_HAB_ENG_SNVS(val) ,0,0,0,((val)&0xff)
#define UNLK_BYTES_HAB_ENG_CAAM (HDR_BYTES + 4)
#define UNLK_VAL_HAB_ENG_CAAM(val) ,0,0,0,((val)&0xff)
#endif

/*
 *    NOP
 */

#define NOP()                                                           \
    HDR(HAB_CMD_NOP, NOP_BYTES, 0xae) /* third param is ignored */

#define NOP_BYTES 4

/*
 *    Install Key (generic - used internally only)
 */

#define INS_KEY(bytes, flg, pcl, alg, src, tgt, crt)    \
    HDR(HAB_CMD_INS_KEY, (bytes), (flg)),               \
        (pcl), (alg), (src), (tgt),                     \
        EXPAND_UINT32(crt)

#define INS_KEY_BASE_BYTES 12

/*
 *    Install Key (SRK)
 */

#define INS_SRK(flg, alg, src, crt)                     \
    INS_KEY(INS_SRK_BYTES, (flg),                       \
            HAB_PCL_SRK, (alg), (src), HAB_IDX_SRK,     \
            (crt))

#define INS_SRK_BYTES INS_KEY_BASE_BYTES

/*
 *    Install Key (CSFK)
 */

#define INS_CSFK(flg, pcl, crt)                                 \
    INS_KEY(INS_CSFK_BYTES, (flg) | HAB_CMD_INS_KEY_CSF,        \
            (pcl), HAB_ALG_ANY, HAB_IDX_SRK, HAB_IDX_CSFK,      \
            (crt))

#define INS_CSFK_BYTES INS_KEY_BASE_BYTES

/*
 *    Install Key (IMGK - no hash)
 */

#define INS_IMGK(flg, pcl, src, tgt, crt)       \
    INS_KEY(INS_IMGK_BYTES, (flg),              \
            (pcl), HAB_ALG_ANY, (src), (tgt),   \
            (crt))

#define INS_IMGK_BYTES INS_KEY_BASE_BYTES


/*
 *    Install Key (IMGK - with hash). Must be followed by the crt_hsh contents
 *    (e.g. using #include).  The length field depends on using one of the
 *    standard HAB algorithm names, with no adornments like casts or
 *    parentheses.  Note that the length macro cannot be used here: the ##
 *    must appear in the body of this macro to prevent the alg parameter from
 *    being expanded first.
 */

#define INS_IMGK_HASH(flg, pcl, alg, src, tgt, crt)                     \
    INS_KEY(INS_KEY_BASE_BYTES + BYTES_ ## alg, (flg) | HAB_CMD_INS_KEY_HSH, \
            (pcl), (alg), (src), (tgt),                                 \
            (crt))

/*
 * Same as above but the hash length is fixed to the length of SHA1,
 * but the algorithm remains unchanged.
 */
#define INS_IMGK_INV_HASH(flg, pcl, alg, src, tgt, crt)                 \
    INS_KEY(INS_IMGK_HASH_BYTES(HAB_ALG_SHA1), (flg) | HAB_CMD_INS_KEY_HSH, \
            (pcl), (alg), (src), (tgt),                                 \
            (crt))


#define INS_IMGK_HASH_BYTES(alg)                \
    (INS_KEY_BASE_BYTES + BYTES_ ## alg)

#define BYTES_HAB_ALG_SHA1   20
#define BYTES_HAB_ALG_SHA256 32
#define BYTES_HAB_ALG_SHA512 64
/* dummy value for invalid hash alg - same as default hash algorithm */
#define DEFAULT_HASH_ALG_BYTES BYTES_HAB_ALG_SHA256
#define BYTES_HAB_ALG_PKCS1  DEFAULT_HASH_ALG_BYTES

/*
 *    Authenticate Data (generic - used internally only)
 */

#define AUT_DAT(bytes, flg, key, pcl, eng, cfg, sig_start)      \
    HDR(HAB_CMD_AUT_DAT, (bytes), (flg)),                       \
        (key), (pcl), (eng), (cfg),                             \
        EXPAND_UINT32(sig_start)

#define AUT_DAT_BASE_BYTES 12

/*
 *    Authenticate Data (CSF)
 */

#define AUT_CSF(flg, pcl, eng, cfg, sig_start)  \
    AUT_DAT(AUT_CSF_BYTES, (flg),               \
            HAB_IDX_CSFK, (pcl), (eng), (cfg),  \
            (sig_start))

#define AUT_CSF_BYTES AUT_DAT_BASE_BYTES

/*
 *    Authenticate Data (Image)
 */

#define AUT_IMG(blocks, flg, key, pcl, eng, cfg, sig_start)     \
    AUT_DAT(AUT_IMG_BYTES(blocks), (flg),                       \
            (key), (pcl), (eng), (cfg),                         \
            (sig_start))

#define AUT_IMG_BYTES(blocks)                   \
    (AUT_DAT_BASE_BYTES + 8*(blocks))

/** Supported widths of data commands.
 * @ingroup cmd_wrt_dat
 */
typedef enum hab_data_width
{
    HAB_DATA_WIDTH_BYTE = 1,    /**< 8-bit value */
    HAB_DATA_WIDTH_HALF = 2,    /**< 16-bit value */
    HAB_DATA_WIDTH_WORD = 4     /**< 32-bit value */
} hab_data_width_t;
    

/** Flags for Write Data commands.
 * @ingroup cmd_wrt_dat
 */
typedef enum hab_cmd_wrt_dat_flg
{
    HAB_CMD_WRT_DAT_MSK = 1,    /**< Mask/value flag: if set, only specific
                                 * bits may be overwritten at target address
                                 * (otherwise all bits may be overwritten)
                                 */
    HAB_CMD_WRT_DAT_SET = 2     /**< Set/clear flag: if #HAB_CMD_WRT_DAT_MSK
                                 * set, bits at the target address overwritten
                                 * with this flag (otherwise it is ignored)
                                 */
} hab_cmd_wrt_dat_flg_t;

/** Flags for Check Data commands.
 * @ingroup cmd_chk_dat
 */
typedef enum hab_cmd_chk_dat_flg
{
    HAB_CMD_CHK_DAT_SET = 2,    /**< Set/clear flag: bits set in mask must
                                 * match this flag
                                 */
    HAB_CMD_CHK_DAT_ANY = 4     /**< Any/all flag: if clear, all bits set in
                                 * mask must match (otherwise any bit
                                 * suffices)
                                 */
} hab_cmd_chk_dat_flg_t;

/** Flags for Authenticate Data commands.
 * @ingroup cmd_aut_dat
 */
typedef enum hab_cmd_aut_dat_flg
{
    HAB_CMD_AUT_DAT_CLR = 0,    /**< No flags set */
    HAB_CMD_AUT_DAT_ABS = 1     /**< Absolute signature address */
} hab_cmd_aut_dat_flg_t;

/** Flags for Install Key commands.
 * @ingroup cmd_ins_key
 */
typedef enum hab_cmd_ins_key_flg
{
    HAB_CMD_INS_KEY_CLR = 0,    /**< No flags set */
    HAB_CMD_INS_KEY_ABS = 1,    /**< Absolute certificate address */
    HAB_CMD_INS_KEY_CSF = 2,    /**< Install CSF key */
    HAB_CMD_INS_KEY_DAT = 4,    /**< Key binds to Data Type */
    HAB_CMD_INS_KEY_CFG = 8,    /**< Key binds to Configuration */
    HAB_CMD_INS_KEY_FID = 16,   /**< Key binds to Fabrication UID */
    HAB_CMD_INS_KEY_MID = 32,   /**< Key binds to Manufacturing ID */
    HAB_CMD_INS_KEY_CID = 64,   /**< Key binds to Caller ID */
    HAB_CMD_INS_KEY_HSH = 128   /**< Certificate hash present */
} hab_cmd_ins_key_flg_t;

/** Key flags.
 * @ingroup key_pkcs1
 *
 * @ifrom
 *
 * The binding flags given here align with those in #hab_cmd_ins_key_flg
 *
 * @endrom
 *
 */
typedef enum hab_key_flg
{
    /* Two more flag values available */
    HAB_KEY_FLG_DAT = 4,    /**< Key binds to Data Type */
    HAB_KEY_FLG_CFG = 8,    /**< Key binds to Configuration */
    HAB_KEY_FLG_FID = 16,   /**< Key binds to Fabrication UID */
    HAB_KEY_FLG_MID = 32,   /**< Key binds to Manufacturing ID */
    HAB_KEY_FLG_CID = 64,   /**< Key binds to Caller ID */
    HAB_KEY_FLG_CA  = 128   /**< CA key */
} hab_key_flg_t;

/** Secret key flags.
 * @ingroup crt_blob
 */
typedef enum hab_key_secret_flg
{
    /* Seven more flag values available */
    HAB_KEY_FLG_KEK  = 128   /**< KEK */
} hab_key_secret_flg_t;

/** Binding data types
 * @ingroup bnd_obj
 */
typedef enum hab_dat {
    HAB_DAT_CSF = 0x0f,         /**< CSF signature */
    HAB_DAT_IMG = 0x33,         /**< Image signature */
#ifdef HAB_FUTURE
    HAB_DAT_PLG = 0x3c,         /**< Plugin signature */
#endif
    HAB_DAT_MAX
} hab_dat_t;

/* Available values: 55, 5a, 66, 69, 96, 99, a5, aa, c3, cc, f0, ff
 */

/** Target check types
 * @ingroup chk_tgt
 */
typedef enum hab_target {
    HAB_TGT_MEMORY = 0x0f,      /**< Check memory white list */
    HAB_TGT_PERIPHERAL = 0xf0,  /**< Check peripheral white list */
    HAB_TGT_ANY = 0x55,         /**< Check memory & peripheral white list */
    HAB_TGT_MAX
} hab_target_t;

/** Security configuration types
 * @ingroup status
 */
typedef enum hab_config {
/** @cond rom */
    HAB_CFG_FAB = 0x00,         /**< @rom Un-programmed IC */
/** @endcond */
    HAB_CFG_RETURN = 0x33,      /**< Field Return IC */
    HAB_CFG_OPEN = 0xf0,        /**< Non-secure IC */
    HAB_CFG_CLOSED = 0xcc       /**< Secure IC */
} hab_config_t;
/* Available values: 0f, 3c, 55, 5a, 66, 69, 96, 99, a5, aa, ff
 */

/** Security state types
 * @ingroup status
 */
typedef enum hab_state {
    HAB_STATE_INITIAL = 0x33,   /**< Initialising state (transitory) */
    HAB_STATE_CHECK = 0x55,     /**< Check state (non-secure) */
    HAB_STATE_NONSECURE = 0x66, /**< Non-secure state */
    HAB_STATE_TRUSTED = 0x99,   /**< Trusted state */
    HAB_STATE_SECURE = 0xaa,    /**< Secure state */
    HAB_STATE_FAIL_SOFT = 0xcc, /**< Soft fail state */
    HAB_STATE_FAIL_HARD = 0xff, /**< Hard fail state (terminal) */
    HAB_STATE_NONE = 0xf0,      /**< No security state machine */
    HAB_STATE_MAX
} hab_state_t;
/* Available values: 00, 0f, 3c, 5a, 69, 96, a5, c3
 */

/** HAB status types
 * @ingroup status
 */
typedef enum hab_status {
    HAB_STS_ANY = 0x00,         /**< Match any status in
                                 * hab_rvt.report_event()
                                 */
    HAB_FAILURE = 0x33,         /**< Operation failed */
    HAB_WARNING = 0x69,         /**< Operation completed with warning */
    HAB_SUCCESS = 0xf0,         /**< Operation completed successfully */
    HAB_STS_MAX
} hab_status_t;

/** Failure or warning reasons
 * @ingroup evt
 *
 * Values 0x80 ... 0xff are reserved for internal use.
 */
typedef enum hab_reason {
    HAB_RSN_ANY = 0x00,         /**< Match any reason in
                                 * hab_rvt.report_event()
                                 */
    HAB_ENG_FAIL = 0x30,        /**< Engine failure. */
    HAB_INV_ADDRESS = 0x22,     /**< Invalid address: access denied. */
    HAB_INV_ASSERTION = 0x0c,   /**< Invalid assertion. */
    HAB_INV_CALL = 0x28,        /**< Function called out of sequence. */
    HAB_INV_CERTIFICATE = 0x21, /**< Invalid certificate. */
    HAB_INV_COMMAND = 0x06,     /**< Invalid command: command malformed. */
    HAB_INV_CSF = 0x11,         /**< Invalid @ref csf. */
    HAB_INV_DCD = 0x27,         /**< Invalid @ref dcd. */
    HAB_INV_INDEX = 0x0f,       /**< Invalid index: access denied. */
    HAB_INV_IVT = 0x05,         /**< Invalid @ref ivt. */
    HAB_INV_KEY = 0x1d,         /**< Invalid key. */
    HAB_INV_RETURN = 0x1e,      /**< Failed callback function. */
    HAB_INV_SIGNATURE = 0x18,   /**< Invalid signature. */
    HAB_INV_SIZE = 0x17,        /**< Invalid data size. */
    HAB_MEM_FAIL = 0x2e,        /**< Memory failure. */
    HAB_OVR_COUNT = 0x2b,       /**< Expired poll count. */
    HAB_OVR_STORAGE = 0x2d,     /**< Exhausted storage region. */
    HAB_UNS_ALGORITHM = 0x12,   /**< Unsupported algorithm. */
    HAB_UNS_COMMAND = 0x03,     /**< Unsupported command. */
    HAB_UNS_ENGINE = 0x0a,      /**< Unsupported engine. */
    HAB_UNS_ITEM = 0x24,        /**< Unsupported configuration item. */
    HAB_UNS_KEY = 0x1b,         /**< Unsupported key type or parameters. */
    HAB_UNS_PROTOCOL = 0x14,    /**< Unsupported protocol. */
    HAB_UNS_STATE = 0x09,       /**< Unsuitable state. */
    HAB_RSN_MAX
} hab_reason_t;
/* Available values: 33, 35, 36, 39, 3a, 3c, 3f, 41, 42, 44,
 * 47, 48, 4b, 4d, 4e, 50, 53, 55, 56, 59, 5a, 5c, 5f, 60, 63, 65, 66, 69, 6a,
 * 6c, 6f, 71, 72, 74, 77, 78, 7b, 7d, 7e
 */

/** Audit logging contexts.
 * @ingroup evt
 *
 * This list is sorted in order of increasing priority: where two contexts
 * might apply, the latter one is used.
 *
 * Values 0x40 .. 0x5f are reserved for internal use.
 */
typedef enum hab_context {
    HAB_CTX_ANY = 0x00,         /**< Match any context in
                                 * hab_rvt.report_event()
                                 */
/** @cond rom */
    HAB_CTX_FAB = 0xff,         /**< @rom Event logged in hab_fab_test() */
/** @endcond */
    HAB_CTX_ENTRY = 0xe1,       /**< Event logged in hab_rvt.entry() */
    HAB_CTX_TARGET = 0x33,      /**< Event logged in hab_rvt.check_target() */
    HAB_CTX_AUTHENTICATE = 0x0a, /**< Event logged in
                                  *   hab_rvt.authenticate_image() 
                                  */
    HAB_CTX_DCD = 0xdd,         /**< Event logged in hab_rvt.run_dcd() */
    HAB_CTX_CSF = 0xcf,         /**< Event logged in hab_rvt.run_csf() */
    HAB_CTX_COMMAND = 0xc0,     /**< Event logged executing @ref csf or @ref
                                 *   dcd command
                                 */
    HAB_CTX_AUT_DAT = 0xdb,     /**< Authenticated data block */
    HAB_CTX_ASSERT = 0xa0,      /**< Event logged in hab_rvt.assert() */
    HAB_CTX_EXIT = 0xee,        /**< Event logged in hab_rvt.exit() */
    HAB_CTX_MAX
} hab_context_t;

/** Assertion types.
 * @ingroup assert
 */
typedef enum hab_assertion {
    HAB_ASSERT_BLOCK = 0, /**< Assert that a memory block was authenticated */
    HAB_ASSERT_MAX
} hab_assertion_t;

/** RTIC configuration flags 
 * @ingroup rtic
 */
typedef enum hab_rtic_config {
    HAB_RTIC_IN_SWAP8 = 0x01,   /**< Set BYTE SWAP bit (reverse bytes within
                                 *   word on input to RTIC) */
    HAB_RTIC_IN_SWAP16 = 0x02,  /**< Set HALF WORD SWAP bit (reverse
                                 *   half-words within word on input to
                                 *   RTIC)  */
    HAB_RTIC_OUT_SWAP8 = 0x08,  /**< Set HASH RESULT BYTE SWAP bit (reverse
                                 *   bytes within word on output from RTIC) */
    HAB_RTIC_KEEP = 0x80        /**< Retain reference hash value for later
                                 *   monitoring */
} hab_rtic_config_t;

/** SAHARA configuration flags 
 * @ingroup sah
 */
typedef enum hab_sahara_config {
    HAB_SAHARA_IN_SWAP8 = 0x01,   /**< Set MESS BYTE SWAP bit (reverse message
                                   *   bytes within word on input to
                                   *   SAHARA) */
    HAB_SAHARA_IN_SWAP16 = 0x02,  /**< Set MESS HALF WORD SWAP bit (reverse
                                   *   message half-words within word on input
                                   *   to SAHARA)  */
    /* no SWAP32 for SAHARA message - leave 0x04 value unassigned */
    /* no SWAP8 for SAHARA descriptors/links - leave 0x08 value unassigned */
    HAB_SAHARA_DSC_BE8_16 = 0x10, /**< Interpret descriptors and links as for
                                   *   BE-8 16-bit memory. */
    HAB_SAHARA_DSC_BE8_32 = 0x20  /**< Interpret descriptors and links as for
                                   *   BE-8 32-bit memory. */
} hab_sahara_config_t;

/** CAAM configuration flags 
 * @ingroup caam
 */
typedef enum hab_caam_config {
    HAB_CAAM_IN_SWAP8 = 0x01,   /**< Set Message Byte Swap Input bit (reverse
                                 *   message bytes within word on input to
                                 *   CAAM) */
    HAB_CAAM_IN_SWAP16 = 0x02,  /**< Set Message Half Word Swap Input bit
                                 *   (reverse message half-words within word
                                 *   on input to CAAM)  */
    /* no SWAP32 for CAAM message - leave 0x04 value unassigned */
    HAB_CAAM_OUT_SWAP8 = 0x08,   /**< Set Message Byte Swap Output bit
                                  *   (reverse message bytes within word on
                                  *   output from CAAM) */
    HAB_CAAM_OUT_SWAP16 = 0x10,  /**< Set Message Half Word Swap Output bit
                                  *   (reverse message half-words within word
                                  *   on output from CAAM)  */
    /* no SWAP32 for CAAM message - leave 0x20 value unassigned */
    HAB_CAAM_DSC_SWAP8 = 0x40,   /**< Set Control Byte Swap Input/Output bits
                                  *   (reverse descriptor/link bytes within
                                  *   word on input to or output from CAAM) */
    HAB_CAAM_DSC_SWAP16 = 0x80  /**< Set Control Half Word Swap Input/Output
                                  *   bits (reverse descriptor/link half-words
                                  *   within word on input to or output from
                                  *   CAAM) */
} hab_caam_config_t;

/** CAAM unlock flags 
 * @ingroup caam
 */
typedef enum hab_caam_unlock_flag {
    HAB_CAAM_UNLOCK_MID = 0x01,   /**< Leave Job Ring and DECO master ID
                                   *   registers unlocked */
    HAB_CAAM_UNLOCK_RNG = 0x02    /**< Leave RNG state handle 0
                                   *   uninstantiated, do not generate
                                   *   descriptor keys, do not set AES DPA
                                   *   mask, do not block state handle 0 test
                                   *   instantiation */
} hab_caam_unlock_flag_t;

/** SNVS unlock flags 
 * @ingroup snvs
 */
typedef enum hab_snvs_unlock_flag {
    HAB_SNVS_UNLOCK_LP_SWR = 0x01,    /**< Leave LP SW reset unlocked */
    HAB_SNVS_UNLOCK_ZMK_WRITE = 0x02  /**< Leave Zeroisable Master Key write
                                       *   unlocked */
} hab_snvs_unlock_flag_t;

/** SNVS master keys 
 * @ingroup snvs
 *
 * @remark Note that the first two master key selections are completely
 * interchangeable.
 */
typedef enum hab_snvs_keys {
    HAB_SNVS_OTPMK = 0,                 /**< OTP master key */
    HAB_SNVS_OTPMK_ALIAS = 1,           /**< OTP master key (alias) */
    HAB_SNVS_ZMK = 2,                   /**< Zeroisable master key */
    HAB_SNVS_CMK = 3                    /**< Combined master key  */
} hab_snvs_keys_t;


/** OCOTP unlock flags 
 * @ingroup ocotp
 */
typedef enum hab_ocotp_unlock_flag {
    HAB_OCOTP_UNLOCK_FIELD_RETURN = 0x01, /**< Leave Field Return activation
                                           *   unlocked */
    HAB_OCOTP_UNLOCK_SRK_REVOKE = 0x02,   /**< Leave SRK revocation unlocked */
    HAB_OCOTP_UNLOCK_SCS = 0x04,          /**< Leave SCS register unlocked */
    HAB_OCOTP_UNLOCK_JTAG = 0x08          /**< Unlock JTAG using SCS HAB_JDE
                                           *   bit */
} hab_ocotp_unlock_flag_t;

/** DCP configuration flags 
 * @ingroup dcp
 *
 * @warning The byte-swapping controls produce unpredictable results unless
 * the input data block lengths are multiples of 4 bytes.
 */
typedef enum hab_dcp_config {
    HAB_DCP_IN_SWAP8 = 0x01,    /**< Set INPUT BYTE SWAP bit (reverse bytes
                                 *   within words on input to DCP) */
    /* no SWAP16 for DCP - leave 0x02 value unassigned */
    HAB_DCP_IN_SWAP32 = 0x04,   /**< Set INPUT WORD SWAP bit (ignored for
                                 *   hashing)  */
    HAB_DCP_OUT_SWAP8 = 0x08,   /**< Set OUPUT BYTE SWAP bit (reverse bytes
                                 *   within words on output from DCP) */
    /* no SWAP16 for DCP - leave 0x10 value unassigned */
    HAB_DCP_OUT_SWAP32 = 0x20   /**< Set OUTPUT WORD SWAP bit (ignored for
                                 *   hashing)  */
} hab_dcp_config_t;

#ifdef HAB_FUTURE
/** EC key specification types.
 * @ingroup key_ecdsa
 */
typedef enum hab_ec_spec {
    /** Named curve specification. The curve specification is a DER-encoded
     * object identifier.  Supported object identifiers are listed under @ref
     * key_ecdsa_profile "ECDSA key profile".
     */
    HAB_EC_SPEC_NAMED_CURVE = 0x01 
} hab_ec_spec_t;
#endif

/** Variable configuration items
 * @ingroup cmd_set
 */
typedef enum hab_var_cfg_itm {
    HAB_VAR_CFG_ITM_MID = 0x01, /**< Manufacturing ID (MID) fuse locations */
    HAB_VAR_CFG_ITM_ENG = 0x03  /**< Preferred engine for a given algorithm */
} hab_var_cfg_itm_t;

/*===========================================================================
                                ENUMS
=============================================================================*/

/*===========================================================================
                    STRUCTURES AND OTHER TYPEDEFS
=============================================================================*/

/** Header field components
 * @ingroup hdr
 */
typedef struct hab_hdr {
    uint8_t tag;              /**< Tag field */
    uint8_t len[2];           /**< Length field in bytes (big-endian) */
    uint8_t par;              /**< Parameters field */
} hab_hdr_t;

/** Loader callback.
 * @ingroup auth_img
 *
 * @par Purpose
 *
 * This function must be supplied by the library caller if required. It is
 * intended to finalise image loading in those boot modes where only a portion
 * of the image is loaded to a temporary initial location prior to device
 * configuration.
 * 
 * @par Operation 
 *
 * This function is called during hab_rvt.authenticate_image() between running
 * the @ref dcd and @ref csf.  The operation of this function is defined by
 * the caller.
 *
 * @param[in,out] start Initial (possibly partial) image load address on
 * entry.  Final image load address on exit.
 *
 * @param[in,out] bytes Initial (possibly partial) image size on entry.  Final
 * image size on exit.
 *
 * @param[in] boot_data Initial @ref ivt Boot Data load address.
 *
 * @remark The interpretation of the Boot Data is defined by the caller.
 * Different boot components or modes may use different boot data, or even
 * different loader callback functions.
 *
 * @warning It should not be assumed by this function that the Boot Data is
 * valid or authentic.
 *
 * @warning It is the responsibility of the loader callback to check the final
 * image load addresses using hab_rvt.check_target() prior to copying any image
 * data.
 *
 * @pre The (possibly partial) image has been loaded in the initial load
 * address, and the Boot Data is within the initial image.
 *
 * @pre The @ref dcd has been run, if provided.
 *
 * @post The final image load addresses pass hab_rvt.check_target().
 *
 * @retval #HAB_SUCCESS if all operations completed successfully,
 *
 * @retval #HAB_FAILURE otherwise.
 */
typedef hab_status_t (*hab_loader_callback_f)(
    void** start, 
    size_t* bytes, 
    const void* boot_data);

/*---------------------------------------------------------------------------*/

/** Image entry function prototype
 *  @ingroup rvt
 *
 * This typedef serves as the return type for hab_rvt.authenticate_image().  It
 * specifies a void-void function pointer, but can be cast to another function
 * pointer type if required.
 */
typedef void (*hab_image_entry_f)(void);

/*---------------------------------------------------------------------------*/

/** @ref rvt structure
 *  @ingroup rvt
 *
 * @par Format
 *
 * The @ref rvt consists of a @ref hdr followed by a list of addresses as
 * described further below.
 */
struct hab_rvt {

    /** @ref hdr with tag #HAB_TAG_RVT, length and HAB version fields
     *  (see @ref data)
     */
    hab_hdr_t hdr;

    /** Enter and initialise HAB library.
     * @ingroup entry
     *
     * @par Purpose
     *
     * This function initialises the HAB library and @ref shw plugins.  It is
     * intended for use by post-ROM boot stage components, via the @ref rvt,
     * prior to calling any other HAB functions other than
     * hab_rvt.report_event() and hab_rvt.report_status().
     * 
     * @ifrom It is also intended for use by the boot ROM via hab_rvt.entry().
     * @endrom
     * 
     * @par Operation 
     *
     * This function performs the following operations every time it is called:
     *
     * - Initialise the HAB library internal state
     * - Initialise the internal secret key store (cleared at the next
     * hab_rvt.exit())
     * - Run the entry sequence of each available @ref shw plugin
     *
     * When first called from boot ROM, this function also performs the
     * following operations prior to those given above:
     *
     * - Initialise the internal public key store (persists beyond
     * hab_rvt.exit())
     * - Run the self-test sequence of each available @ref shw plugin
     * - If a state machine is present and enabled, change the security state
     * as follows:
     *   - If the IC is configured as #HAB_CFG_OPEN or #HAB_CFG_RETURN, move to
     *   #HAB_STATE_NONSECURE
     *   - If the IC is configured as #HAB_CFG_CLOSED, move to
     *   #HAB_STATE_TRUSTED
     *   - Otherwise, leave the security state unchanged
     *
     * If any failure occurs in the operations above:
     *
     * - An audit event is logged
     * - All remaining operations are abandoned (except that all @ref shw
     * self-test and entry sequences are still executed)
     * - If a state machine is present and enabled, the security state is set
     * as follows:
     *   - @ifrom Unless the IC is configured as #HAB_CFG_FAB,@endrom move to
     *   #HAB_STATE_NONSECURE.  Note that if a security violation has been
     *   detected by the HW, the final state will be #HAB_STATE_FAIL_SOFT or
     *   #HAB_STATE_FAIL_HARD depending on the HW configuration.
     *
     * @warning Boot sequences may comprise several images with each launching
     * the next as well as alternative images should one boot device or boot
     * image be unavailable or unusable.  The authentication of each image in
     * a boot sequence must be bracketed by its own hab_rvt.entry()
     * ... hab_rvt.exit() pair in order to ensure that security state
     * information gathered for one image cannot be misapplied to another
     * image.
     *
     * @ifrom 
     *
     * @warning This applies to each boot path in boot ROM as well, except for
     * the fabrication test path.
     *
     * @endrom
     *
     * @post HAB library internal state is initialised.
     *
     * @post Available @ref shw plugins are initialised.
     *
     * @post If a failure or warning occurs during @ref shw plugin
     * initialisation, an audit event is logged with the relevant @ref eng
     * tag.  The status and reason logged are described in the relevant @ref
     * shw plugin documentation.
     *
     * @post Security state is initialised, if a state machine is present and
     * enabled.
     *
     * @retval #HAB_SUCCESS on an IC not configured as #HAB_CFG_CLOSED,
     * although unsuccessful operations will still generate audit log events,
     *
     * @retval #HAB_SUCCESS on other ICs if all commands completed
     * without failure (even if warnings were generated),
     *
     * @retval #HAB_FAILURE otherwise.
     */
    hab_status_t (*entry)(void);

    /** Finalise and exit HAB library.
     * @ingroup exit
     *
     * @par Purpose
     *
     * This function finalises the HAB library and @ref shw plugins.  It is
     * intended for use by post-ROM boot stage components, via the @ref rvt,
     * after calling other HAB functions and prior to launching the next boot
     * stage or switching to another boot path.
     *
     * @ifrom It is also intended for use by the boot ROM via hab_rvt.exit().
     * @endrom
     * 
     * @par Operation 
     *
     * This function performs the following operations:
     *
     * - Finalise the HAB library internal state
     * - Clear the internal secret key store
     * - Run the finalisation sequence of each available @ref shw plugin
     *
     * If any failure occurs, an audit event is logged and all remaining
     * operations are abandoned (except that all @ref shw exit sequences are
     * still executed).
     *
     * @warning See warnings for hab_rvt.entry().
     *
     * @post #HAB_ASSERT_BLOCK records are cleared from audit log.  Note that
     * other event records are not cleared.
     *
     * @post Any public keys installed by @ref csf commands remain active.
     *
     * @post Any secret keys installed by @ref csf commands are deleted.
     *
     * @post Available @ref shw plugins are in their final state as described
     * in the relevant sections.
     *
     * @post If a failure or warning occurs, an audit event is logged with the
     * @ref eng tag of the @ref shw plugin concerned.  The status and reason
     * logged are described in the relevant @ref shw plugin documentation.
     *
     * @retval #HAB_SUCCESS on an IC not configured as #HAB_CFG_CLOSED,
     * although unsuccessful operations will still generate audit log events,
     *
     * @retval #HAB_SUCCESS on other ICs if all commands completed
     * without failure (even if warnings were generated),
     *
     * @retval #HAB_FAILURE otherwise.
     */
    hab_status_t (*exit)(void);

    /** Check target address
     * @ingroup chk_tgt
     *
     * @par Purpose
     *
     * This function reports whether or not a given target region is allowed
     * for either peripheral configuration or image loading in memory.  It is
     * intended for use by post-ROM boot stage components, via the @ref rvt,
     * in order to avoid configuring security-sensitive peripherals, or
     * loading images over sensitive memory regions or outside recognised
     * memory devices in the address map.
     * 
     * @ifrom It is also available for use by the boot ROM, both directly via
     * hab_rvt.check_target() and indirectly via hab_rvt.authenticate_image(). 
     * @endrom
     *
     * @par Operation 
     *
     * The lists of allowed target regions vary by IC and core, and should be
     * taken from the @ref ref_rug.
     *
     * @ifrom The allowed register sets for peripheral configuration and memory
     * regions for image loading are defined in the @ref hal by
     * #hab_hal_peripheral and #hab_hal_memory respectively. @endrom
     * 
     * @param[in] type Type of target (memory, peripheral or any in which both
     * the memory and peripheral regions are checked)
     *
     * @param[in] start Address of target region
     *
     * @param[in] bytes Size of target region
     *
     * @post if the given target region goes beyond the allowed regions, an
     * audit event is logged with status #HAB_FAILURE and reason
     * #HAB_INV_ADDRESS, together with the call parameters.  See the @ref evt
     * record documentation for details.
     *
     * @post For successful commands, no audit event is logged.
     *
     * @retval #HAB_SUCCESS on an IC not configured as #HAB_CFG_CLOSED,
     * although unsuccessful operations will still generate audit log events,
     *
     * @retval #HAB_SUCCESS if the given target region lies wholly within the
     * allowed regions for the requested type of target.
     *
     * @retval #HAB_FAILURE otherwise
     */
    hab_status_t (*check_target)(hab_target_t type, 
                                 const void* start,
                                 size_t bytes);

    /** Authenticate image.
     * @ingroup auth_img
     *
     * @par Purpose
     *
     * This function combines DCD, CSF and Assert functions in a standard
     * sequence in order to authenticate a loaded image.  It is intended for
     * use by post-ROM boot stage components, via the @ref rvt.  Support for
     * images partially loaded to an initial location is provided via a
     * callback function.
     * 
     * @ifrom It is also available for use by the boot ROM via
     * hab_rvt.authenticate_image(). @endrom
     * 
     * @par Operation 
     *
     * This function performs the following sequence of operations:
     * - Check that the initial image load addresses pass
     * hab_rvt.check_target().
     * - Check that the IVT offset lies within the initial image bounds.
     * - Check that the @ref ivt @a self and @a entry pointers are not NULL
     * - Check the @ref ivt header for consistency and compatability.
     * - If provided in the @ref ivt, calculate the @ref dcd initial location,
     * check that it lies within the initial image bounds, and run the @ref
     * dcd commands.
     * - If provided in the @ref ivt, calculate the Boot Data initial location
     * and check that it lies within the initial image bounds.
     * - If provided in the parameters, invoke the callback function with the
     * initial image bounds and initial location of the @ref ivt Boot Data.
     * 
     * From this point on, the full image is assumed to be in its final
     * location. The following operations will be performed on all IC 
     * configurations (#hab_config), but will be only enforced on an IC 
     * configured as #HAB_CFG_CLOSED:
     * - Check that the final image load addresses pass hab_rvt.check_target().
     * - Check that the CSF lies within the image bounds, and run the CSF
     * commands.
     * - Check that all of the following data have been authenticated (using
     * their final locations):
     *   - IVT;
     *   - DCD (if provided);
     *   - Boot Data (initial byte if provided);
     *   - Entry point (initial word).
     *
     * @param[in] cid Caller ID, used to identify which SW issued this call.
     *
     * @param[in] ivt_offset Offset in bytes of the IVT from the image start
     * address.
     *
     * @param[in,out] start Initial (possibly partial) image load address on
     * entry.  Final image load address on exit.
     *
     * @param[in,out] bytes Initial (possibly partial) image size on entry.
     * Final image size on exit.
     *
     * @param[in] loader Callback function to load the full image to its final
     * load address.  Set to NULL if not required.
     *
     * @remark Caller ID may be bound to signatures verified using keys
     * installed with #HAB_CMD_INS_KEY_CID flag. See @ref cmd_ins_key and @ref
     * bnd_obj for details.
     *
     * @remark A @a loader callback function may be supplied even if the image
     * is already loaded to its final location on entry.
     *
     * @remark Boot Data (boot_data in @ref ivt) will be ignored if the 
     * @a loader callback function point is set to Null.
     *
     * @warning The @a loader callback function should lie within existing
     * authenticated areas. @ifrom Or within the ROM. @endrom
     *
     * @warning It is the responsibility of the caller to check the initial
     * image load addresses using hab_rvt.check_target() prior to loading the
     * initial image and calling this function.
     *
     * @warning After completion of hab_rvt.authenticate_image(), the caller
     * should test using hab_rvt.assert() that the Boot Data was
     * authenticated.
     *
     * @post The post-conditions of the functions hab_rvt.check_target(),
     * hab_rvt.run_dcd(), hab_rvt.run_csf() and hab_rvt.assert() apply also to
     * this function.  In particular, any audit events logged within the given
     * functions have the context field appropriate to that function rather
     * than #HAB_CTX_AUTHENTICATE.  In addition, the side-effects and
     * post-conditions of any callback function supplied apply.
     *
     * @post If a failure or warning occurs outside these contexts, an audit
     * event is logged with status:
     *   - #HAB_FAILURE, with further reasons:
     *     - #HAB_INV_ADDRESS: initial or final image addresses outside allowed
     *     regions
     *     - #HAB_INV_ADDRESS: IVT, DCD, Boot Data or CSF outside image bounds
     *     - #HAB_INV_ADDRESS: IVT @a self or @a entry pointer is NULL 
     *     - #HAB_INV_CALL: hab_rvt.entry() not run successfully prior to call
     *     - #HAB_INV_IVT: IVT malformed
     *     - #HAB_INV_IVT: IVT version number is less than HAB library version
     *     - #HAB_INV_RETURN: Callback function failed
     *
     * @retval entry field from @ref ivt on an IC not configured as
     * #HAB_CFG_CLOSED provided that the following conditions are met
     * (other unsuccessful operations will generate audit log events):
     *  - the @a start pointer and the pointer it locates are not NULL
     *  - the initial @ref ivt location is not NULL
     *  - the @ref ivt @ref hdr (given in the @a hdr field) is valid
     *  - the final @ref ivt location (given by the @a self field) is not NULL 
     *  - any loader callback completed successfully,
     *
     * @retval entry field from @ref ivt on other ICs if all operations
     * completed without failure (even if warnings were generated),
     *
     * @retval NULL otherwise.
     */
    hab_image_entry_f (*authenticate_image)(uint8_t cid,
                                            ptrdiff_t ivt_offset, 
                                            void** start, 
                                            size_t* bytes, 
                                            hab_loader_callback_f loader);

    /** Execute a boot configuration script.
     * @ingroup run_dcd
     *
     * @par Purpose
     *
     * This function configures the IC based upon a @ref dcd table.  It is
     * intended for use by post-ROM boot stage components, via the @ref rvt.
     * This function may be invoked as often as required for each boot stage.
     *
     * @ifrom It is also intended for use by the boot ROM, both directly via
     * hab_rvt.run_dcd() and indirectly via hab_rvt.authenticate_image().
     * @endrom
     * 
     * The difference between the configuration functionality in this function
     * and hab_rvt.run_csf() arises because the @ref dcd table is not
     * authenticated prior to running the commands.  Hence, there is a more
     * limited range of commands allowed, and a limited range of parameters to
     * allowed commands.
     * 
     * @par Operation 
     *
     * This function performs the following operations:
     * - Checks the @ref hdr for compatibility and consistency
     * - Makes an internal copy of the @ref dcd table
     * - Executes the commands in sequence from the internal copy of the @ref
     * dcd
     *
     * If any failure occurs, an audit event is logged and all remaining
     * operations are abandoned.
     *
     * @param[in] dcd   Address of the @ref dcd.
     *
     * @warning It is the responsibility of the caller to ensure that the @a
     * dcd parameter points to a valid memory location.
     *
     * @warning The @ref dcd must be authenticated by a subsequent @ref csf
     * command prior to launching the next boot image, in order to avoid
     * unauthorised configurations which may subvert secure operation.
     * Although the content of the next boot stage's CSF may be out of scope
     * for the hab_rvt.run_dcd() caller, it is possible to enforce this
     * constraint by using hab_rvt.assert() to ensure that both the DCD and
     * any pointers used to locate it have been authenticated.
     *
     * @warning Each invocation of hab_rvt.run_dcd() must occur between a pair
     * of hab_rvt.entry() and hab_rvt.exit() calls, although multiple
     * hab_rvt.run_dcd() calls (and other HAB calls) may be made in one
     * bracket.  This constraint applies whether hab_rvt.run_dcd() is
     * successful or not: a subsequent call to hab_rvt.exit() is required
     * prior to launching the authenticated image or switching to another boot
     * target.
     *
     * @post Many commands may cause side-effects. See the @ref dcd
     * documentation.
     *
     * @post If a failure or warning occurs within a command handler, an audit
     * event is logged with the offending command, copied from the DCD.  The
     * status and reason logged are described in the relevant command
     * documentation.
     *
     * @post For other failures or warning, the status logged is:
     *   - #HAB_WARNING, with further reasons:
     *     - #HAB_UNS_COMMAND: unsupported command encountered, where DCD
     *     version and HAB library version differ
     *   - #HAB_FAILURE, with further reasons:
     *     - #HAB_INV_ADDRESS: NULL @a dcd parameter
     *     - #HAB_INV_CALL: hab_rvt.entry() not run successfully prior to call
     *     - #HAB_INV_COMMAND: command not allowed in DCD
     *     - #HAB_UNS_COMMAND: unrecognised command encountered, where DCD
     *     version and HAB library version match
     *     - #HAB_INV_DCD: DCD malformed or too large
     *     - #HAB_INV_DCD: DCD version number is less than HAB library version
     * @retval #HAB_SUCCESS on an IC not configured as #HAB_CFG_CLOSED,
     * although unsuccessful operations will still generate audit log events,
     *
     * @retval #HAB_SUCCESS on other ICs if all commands completed
     * without failure (even if warnings were generated),
     *
     * @retval #HAB_FAILURE otherwise.
     */
    hab_status_t (*run_dcd)(const uint8_t* dcd);

    /** Execute an authentication script.
     * @ingroup run_csf
     *
     * @par Purpose
     *
     * This function authenticates SW images and configures the IC based upon
     * a @ref csf.  It is intended for use by post-ROM boot stage components,
     * via the @ref rvt.  This function may be invoked as often as required
     * for each boot stage.
     * 
     * @ifrom It is also available for use by the boot ROM via hab_rvt.run_csf,
     * although it is anticipated that the boot ROM will mostly call this
     * function indirectly via hab_rvt.authenticate_image(). @endrom
     *
     * @par Operation 
     *
     * This function performs the following operations:
     * - Checks the @ref hdr for compatibility and consistency
     * - Makes an internal copy of the @ref csf
     * - Executes the commands in sequence from the internal copy of the @ref
     * csf
     *
     * The internal copy of the @ref csf is authenticated by an explicit
     * command in the sequence.  Prior to authentication, a limited set of
     * commands is available to:
     * - Install a Super-Root key (unless previously installed)
     * - Install a CSF key (unless previously installed)
     * - Specify any variable configuration items
     * - Authenticate the CSF
     *
     * Subsequent to CSF authentication, the full set of commands is available.
     *
     * If any failure occurs, an audit event is logged and all remaining
     * operations are abandoned.
     *
     * @param[in] csf   Address of the @ref csf.
     *
     * @param[in] cid Caller ID, used to identify which SW issued this call.
     *
     * @remark Caller ID may be bound to signatures verified using keys
     * installed with #HAB_CMD_INS_KEY_CID flag. See @ref cmd_ins_key and @ref
     * bnd_obj for details.
     *
     * @warning It is the responsibility of the caller to ensure that the @a
     * csf parameter points to a valid memory location.
     *
     * @warning Each invocation of hab_rvt.run_csf() must occur between a pair
     * of hab_rvt.entry() and hab_rvt.exit() calls, although multiple
     * hab_rvt.run_csf() calls (and other HAB calls) may be made in one
     * bracket.  This constraint applies whether hab_rvt.run_csf() is
     * successful or not: a subsequent call to hab_rvt.exit() is required
     * prior to launching the authenticated image or switching to another boot
     * target.
     *
     * @post Many commands may cause side-effects. See the @ref csf
     * documentation.  In particular, note that keys installed by the @ref csf
     * remain available for use in subsequent operations.
     *
     * @post If a failure or warning occurs within a command handler, an audit
     * event is logged with the offending command, copied from the CSF.  The
     * status and reason logged are described in the relevant command
     * documentation.
     *
     * @post For other failures or warning, the status logged is:
     *   - #HAB_WARNING, with further reasons:
     *     - #HAB_UNS_COMMAND: unsupported command encountered, where CSF
     *     version and HAB library version differ
     *   - #HAB_FAILURE, with further reasons:
     *     - #HAB_INV_ADDRESS: NULL @a csf parameter
     *     - #HAB_INV_CALL: hab_rvt.entry() not run successfully prior to call
     *     - #HAB_INV_COMMAND: command not allowed prior to CSF authentication
     *     - #HAB_UNS_COMMAND: unrecognised command encountered, where CSF
     *     version and HAB library version match
     *     - #HAB_INV_CSF: CSF not authenticated
     *     - #HAB_INV_CSF: CSF malformed or too large
     *     - #HAB_INV_CSF: CSF version number is less than HAB library version
     *
     * @retval #HAB_SUCCESS on an IC not configured as #HAB_CFG_CLOSED,
     * although unsuccessful operations will still generate audit log events,
     *
     * @retval #HAB_SUCCESS on other ICs if all commands completed
     * without failure (even if warnings were generated),
     *
     * @retval #HAB_FAILURE otherwise.
     */
    hab_status_t (*run_csf)(const uint8_t* csf, 
                            uint8_t cid);

    /** Test an assertion against the audit log.
     * @ingroup assert
     *
     * @par Purpose
     *
     * This function allows the audit log to be interrogated.  It is intended
     * for use by post-ROM boot stage components, via the @ref rvt, to
     * determine the state of authentication operations.  This function may be
     * invoked as often as required for each boot stage.
     *
     * @ifrom It is also available for use by the boot ROM, both directly via
     * hab_rvt.assert() and indirectly via hab_rvt.authenticate_image().
     * @endrom
     *
     * @par Operation 
     *
     * This function checks the required assertion as detailed below.
     *
     * @param[in] type Assertion type.
     *
     * @param[in] data Assertion data.
     *
     * @param[in] count Data size or count.
     *
     * @par Memory block authentication:
     * For #HAB_ASSERT_BLOCK assertion type, hab_rvt.assert() checks that the
     * given memory block has been authenticated after running a CSF. The
     * parameters are interpreted as follows:
     *
     * @par
     * - @a data: memory block starting address
     * - @a count: memory block size (in bytes)
     *
     * @par 
     *
     * A simple interpretation of "memory block has been authenticated" is
     * taken, such that the given block must lie wholly within a single
     * contiguous block authenticated while running a CSF.  A given memory
     * block covered by the union of several neighboring or overlapping
     * authenticated blocks could fail the test with this interpretation, but
     * it is assumed that such cases will not arise in practice.
     *
     * @post If the assertion fails, an audit event is logged with status
     * #HAB_FAILURE and reason #HAB_INV_ASSERTION, together with the call
     * parameters.  See the @ref evt record documentation for details.
     *
     * @post For successful commands, no audit event is logged.
     *
     * @retval #HAB_SUCCESS on an IC not configured as #HAB_CFG_CLOSED,
     * although unsuccessful operations will still generate audit log events,
     *
     * @retval #HAB_SUCCESS on other ICs if the assertion is confirmed
     *
     * @retval #HAB_FAILURE otherwise
     */
    hab_status_t (*assert)(hab_assertion_t type, 
                           const void* data, 
                           uint32_t count);

    /** Report an event from the audit log.
     * @ingroup event
     *
     * @par Purpose
     *
     * This function allows the audit log to be interrogated.  It is intended
     * for use by post-ROM boot stage components, via the @ref rvt, to
     * determine the state of authentication operations.  This function may
     * be called outside an hab_rvt.entry() / hab_rvt.exit() pair.
     * 
     * @ifrom It is also available for use by the boot ROM, where it may be
     * used to report boot failures as part of a tethered boot
     * protocol. @endrom
     *
     * @par Operation 
     *
     * This function performs the following operations:
     * - Scans the audit log for a matching event
     * - Copies the required details to the output parameters (if found)
     *
     * @param[in] status Status level of required event.
     *
     * @param[in] index Index of required event at given status level.
     *
     * @param[out] event @ref evt record.
     *
     * @param[in,out] bytes Size of @a event buffer on entry, size of event
     * record on exit.
     *
     * @remark Use @a status = #HAB_STS_ANY to match any logged event,
     * regardless of the status value logged.
     *
     * @remark Use @a index = 0 to return the first matching event, @a index =
     * 1 to return the second matching event, and so on.
     *
     * @remark The data logged with each event is context-dependent.  Refer to
     * @ref evt record documentation.
     *
     * @warning Parameter @a bytes may not be NULL.
     *
     * @warning If the @a event buffer is a NULL pointer or too small to fit
     * the event record, the required size is written to @a bytes, but no 
     * part of the event record is copied to the output buffer.
     *
     * @retval #HAB_SUCCESS if the required event is found, and the event
     * record is copied to the output buffer.
     * 
     * @retval #HAB_SUCCESS if the required event is found and @a event buffer 
     * passed is a NULL pointer.
     *
     * @retval #HAB_FAILURE otherwise
     */
    hab_status_t (*report_event)(hab_status_t status,
                                 uint32_t index,
                                 uint8_t* event,
                                 size_t* bytes);

    /** Report security status.
     * @ingroup status
     *
     * @par Purpose
     *
     * This function reports the security configuration and state of the IC as
     * well as searching the audit log to determine the status of the boot
     * process.  It is intended for use by post-ROM boot stage components, via
     * the @ref rvt.  This function may be called outside an
     * hab_rvt.entry() / hab_rvt.exit() pair.
     * 
     * @ifrom It is also available for use by the boot ROM, and should be used
     * rather than the HAL function hab_hal_read_sec_cfg(). @endrom
     *
     * @par Operation 
     *
     * This function reads the fuses which indicate the security
     * configuration.  The fusemap varies by IC, and should be taken from the
     * @ref ref_rug.  It also uses the @ref shw state machine, if present and
     * enabled, to report on the security state.
     *
     * @param[out] config Security configuration, NULL if not required
     *
     * @param[out] state Security state, NULL if not required
     *
     * @remark If no @ref shw state machine is present and enabled, the state
     * #HAB_STATE_NONE will be output.
     *
     * @retval #HAB_SUCCESS if no warning or failure audit events have been
     * logged.
     *
     * @retval #HAB_WARNING otherwise, if only warning events have been logged.
     *
     * @retval #HAB_FAILURE otherwise
     */
    hab_status_t (*report_status)(hab_config_t* config, hab_state_t* state);

    /** Enter failsafe boot mode.
     * @ingroup safe
     *
     * @par Purpose
     *
     * This function provides a safe path when image authentication has failed
     * and all possible boot paths have been exhausted.  It is intended for
     * use by post-ROM boot stage components, via the @ref rvt.
     * 
     * @ifrom It is also available for use by the boot ROM via
     * hab_rvt.failsafe(). @endrom
     *
     * @par Operation 
     *
     * The precise details of this function vary by IC and core, and should be
     * taken from @ref ref_rug.
     *
     * @warning This function does not return.
     *
     * @remark Since this function does not return, it implicitly performs the
     * functionality of hab_rvt.exit() in order to ensure an appropriate
     * configuration of the @ref shw plugins.
     *
     * @remark Two typical implementations are:
     * - a low-level provisioning protocol in which an image is downloaded to
     * RAM from an external host, authenticated and launched.  The downloaded
     * image may communicate with tools on the external host to report the
     * reasons for boot failure, and may re-provision the end-product with
     * authentic boot images.
     * - a failsafe boot mode which does not allow execution to leave the ROM
     * until the IC is reset.
     */
    void (*failsafe)(void);
};

/** @ref rvt type
 * @ingroup rvt
 */
typedef struct hab_rvt hab_rvt_t;

/*---------------------------------------------------------------------------*/

/** @ref ivt structure
 * @ingroup ivt
 *
 * @par Format
 *
 * An @ref ivt consists of a @ref hdr followed by a list of addresses as
 * described further below.
 *
 * @warning The @a entry address may not be NULL.
 *
 * @warning On an IC not configured as #HAB_CFG_CLOSED, the
 * @a csf address may be NULL.  If it is not NULL, the @ref csf will be
 * processed, but any failures should be non-fatal.
 *
 * @warning On an IC configured as #HAB_CFG_CLOSED, the @a
 * csf address may not be NULL, and @ref csf failures are typically fatal.
 *
 * @remark The Boot Data located using the @a boot_data field is interpreted
 * by the HAB caller in a boot-mode specific manner.  This may be used by the
 * boot ROM as to determine the load address and boot device configuration for
 * images loaded from block devices (see @ref ref_rug for details).
 *
 * @remark All addresses given in the IVT, including the Boot Data (if
 * present) are those for the final load location. 
 *
 * @anchor ila
 *
 * @par Initial load addresses
 *
 * The @a self field is used to calculate addresses in boot modes where an
 * initial portion of the image is loaded to an initial location.  In such
 * cases, the IVT, Boot Data (if present) and DCD (if present) are used in
 * configuring the IC and loading the full image to its final location.  Only
 * the IVT, Boot Data (if present) and DCD (if present) are required to be
 * within the initial image portion.
 *
 * The method for calculating an initial load address for the DCD is
 * illustrated in the following C fragment.  Similar calculations apply to
 * other fields.
 *
@verbatim
        hab_ivt_t* ivt_initial = <initial IVT load address>;
        const void* dcd_initial = ivt_initial->dcd;
        if (ivt_initial->dcd != NULL)
            dcd_initial = (const uint8_t*)ivt_initial 
                          + (ivt_initial->dcd - ivt_initial->self)
@endverbatim
 */
struct hab_ivt {
    /** @ref hdr with tag #HAB_TAG_IVT, length and HAB version fields
     *  (see @ref data)
     */
    hab_hdr_t hdr;
    /** Absolute address of the first instruction to execute from the
     *  image
     */
    hab_image_entry_f entry;
    /** Reserved in this version of HAB: should be NULL. */
    const void* reserved1;
    /** Absolute address of the image DCD: may be NULL. */
    const void* dcd;
    /** Absolute address of the Boot Data: may be NULL, but not interpreted
     *  any further by HAB
     */
    const void* boot_data;
    /** Absolute address of the IVT.*/
    const void* self;
    /** Absolute address of the image CSF.*/
    const void* csf;
    /** Reserved in this version of HAB: should be zero. */
    uint32_t reserved2;
};

/** @ref ivt type
 * @ingroup ivt
 */
typedef struct hab_ivt hab_ivt_t;

/*===========================================================================
                         FUNCTION PROTOTYPES
=============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* HAB_DEFINES_H */
