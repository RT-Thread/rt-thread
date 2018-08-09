/**************************************************************************************
* Copyright (c) 2016-2017, ARM Limited or its affiliates. All rights reserved         *
*                                                                                     *
* This file and the related binary are licensed under the following license:          *
*                                                                                     *
* ARM Object Code and Header Files License, v1.0 Redistribution.                      *
*                                                                                     *
* Redistribution and use of object code, header files, and documentation, without     *
* modification, are permitted provided that the following conditions are met:         *
*                                                                                     *
* 1) Redistributions must reproduce the above copyright notice and the                *
*    following disclaimer in the documentation and/or other materials                 *
*    provided with the distribution.                                                  *
*                                                                                     *
* 2) Unless to the extent explicitly permitted by law, no reverse                     *
*    engineering, decompilation, or disassembly of is permitted.                      *
*                                                                                     *
* 3) Redistribution and use is permitted solely for the purpose of                    *
*    developing or executing applications that are targeted for use                   *
*    on an ARM-based product.                                                         *
*                                                                                     *
* DISCLAIMER. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                  *
* CONTRIBUTORS "AS IS." ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT             *
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT,        *
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED            *
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR              *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF              *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                  *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                        *
**************************************************************************************/


#ifndef CRYS_RSA_TYPES_H
#define CRYS_RSA_TYPES_H

#include "crys_hash.h"
#include "crys_pka_defs_hw.h"
#include "ssi_pal_types.h"
#include "ssi_pal_compiler.h"

#ifdef DX_SOFT_KEYGEN
#include "ccsw_crys_rsa_shared_types.h"
#endif


#ifdef __cplusplus
extern "C"
{
#endif
/*!
@file 
@brief This file contains all of the enums and definitions that are used for the CRYS RSA APIs. 
@defgroup crys_rsa_types CryptoCell RSA used definitions and enums
@{
@ingroup crys_rsa
*/

/************************ Defines ******************************/

/*! Definition of HASH context size. */
#define CRYS_PKA_RSA_HASH_CTX_SIZE_IN_WORDS CRYS_HASH_USER_CTX_SIZE_IN_WORDS

/*! Maximal key size in bytes. */
#define CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BYTES    (CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BITS / SASI_BITS_IN_BYTE)

/*! Minimal key size in bits. */
#define CRYS_RSA_MIN_VALID_KEY_SIZE_VALUE_IN_BITS              512
/*! Valid key size multiplications in RSA. */
#define CRYS_RSA_VALID_KEY_SIZE_MULTIPLE_VALUE_IN_BITS         256

/*! Maximal RSA generated key size in bits. */
#define CRYS_RSA_MAX_KEY_GENERATION_SIZE_BITS   CRYS_RSA_MAX_KEY_GENERATION_HW_SIZE_BITS

/* FIPS 184-4 definitions for allowed RSA and FFC DH key sizes */
/*! FIPS 184-4 allowed key size - 1024 bits. */
#define CRYS_RSA_FIPS_KEY_SIZE_1024_BITS   1024
/*! FIPS 184-4 allowed key size - 2048 bits. */
#define CRYS_RSA_FIPS_KEY_SIZE_2048_BITS   2048
/*! FIPS 184-4 allowed key size - 3072 bits. */
#define CRYS_RSA_FIPS_KEY_SIZE_3072_BITS   3072
/*! FIPS 184-4 allowed modulus size in bits. */
#define CRYS_RSA_FIPS_MODULUS_SIZE_BITS    CRYS_RSA_FIPS_KEY_SIZE_2048_BITS

/*! FIPS 184-4 DH key size - 1024 bits. */
#define CRYS_DH_FIPS_KEY_SIZE_1024_BITS    1024
/*! FIPS 184-4 DH key size - 2048 bits. */
#define CRYS_DH_FIPS_KEY_SIZE_2048_BITS    2048


/*! Salt length definition - if the salt length is not available in verify operation, the user can use this define and the algorithm will
    calculate the salt length alone*/
/*!\note Security wise: it is not recommended to use this flag.*/
#define CRYS_RSA_VERIFY_SALT_LENGTH_UNKNOWN                     0xFFFF

/*! Minimal public exponent value */
#define CRYS_RSA_MIN_PUB_EXP_VALUE  3
/*! Minimal private exponent value */
#define CRYS_RSA_MIN_PRIV_EXP_VALUE 1

/* The maximum buffer size for the 'H' value */
/*! Temporary buffer size definition.*/
#define CRYS_RSA_TMP_BUFF_SIZE (CRYS_RSA_OAEP_ENCODE_MAX_MASKDB_SIZE + CRYS_RSA_OAEP_ENCODE_MAX_SEEDMASK_SIZE + CRYS_PKA_RSA_HASH_CTX_SIZE_IN_WORDS*sizeof(uint32_t) + sizeof(CRYS_HASH_Result_t))

/*! Hash structure definition.*/
#define CRYS_PKCS1_HashFunc_t CRYS_HASH_OperationMode_t

/*! OAEP maximal H length.*/
#define CRYS_RSA_OAEP_MAX_HLEN							CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES

/*! MGF1 definitions */
#define CRYS_RSA_MGF_2_POWER_32              			65535 /*!< \internal 0xFFFF This is the 2^32 of the 2^32*hLen boundary check */
/*! MGF1 definitions */
#define CRYS_RSA_SIZE_OF_T_STRING_BYTES	    			(CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS*sizeof(uint32_t)) 

/***********************************************************
 *
 * RSA PKCS#1 v2.1 DEFINES
 *
 ***********************************************************/     
/*! Size of OEAP seed. */
#define CRYS_RSA_OAEP_ENCODE_MAX_SEEDMASK_SIZE 			CRYS_RSA_OAEP_MAX_HLEN
/*! Maximal PSS salt size. */
#define CRYS_RSA_PSS_SALT_LENGTH 				CRYS_RSA_OAEP_MAX_HLEN
/*! PSS padding length. */
#define CRYS_RSA_PSS_PAD1_LEN					8
	 
/*! OAEP encode mask size. */
#define CRYS_RSA_OAEP_ENCODE_MAX_MASKDB_SIZE  			(CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS*sizeof(uint32_t)) /*!< \internal For OAEP Encode; the max size is emLen */
/*! OAEP decode mask size. */
#define CRYS_RSA_OAEP_DECODE_MAX_DBMASK_SIZE  			(CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS*sizeof(uint32_t)) /*!< \internal For OAEP Decode; the max size is emLen */

/************************ Enums ********************************/

/*! Defines the enum for the HASH operation mode. */
typedef enum
{
	CRYS_RSA_HASH_MD5_mode  = 0,	/*!< For PKCS1 v1.5 only. The input data will be hashed with MD5 */
	CRYS_RSA_HASH_SHA1_mode = 1,	/*!< The input data will be hashed with SHA1. */
	CRYS_RSA_HASH_SHA224_mode = 2,  /*!< The input data will be hashed with SHA224. */
	CRYS_RSA_HASH_SHA256_mode = 3,  /*!< The input data will be hashed with SHA256. */
	CRYS_RSA_HASH_SHA384_mode = 4,  /*!< The input data will be hashed with SHA384. */
	CRYS_RSA_HASH_SHA512_mode = 5,	/*!< The input data will be hashed with SHA512. */
	CRYS_RSA_After_MD5_mode = 6,		/*!< For PKCS1 v1.5 only. The input data is a digest of MD5 and will not be hashed. */
	CRYS_RSA_After_SHA1_mode = 7,	/*!< The input data is a digest of SHA1 and will not be hashed. */
	CRYS_RSA_After_SHA224_mode = 8,	/*!< The input data is a digest of SHA224 and will not be hashed. */
	CRYS_RSA_After_SHA256_mode = 9,	/*!< The input data is a digest of SHA256 and will not be hashed. */
	CRYS_RSA_After_SHA384_mode = 10,	/*!< The input data is a digest of SHA384 and will not be hashed. */
	CRYS_RSA_After_SHA512_mode = 11,	/*!< The input data is a digest of SHA512 and will not be hashed. */
	CRYS_RSA_After_HASH_NOT_KNOWN_mode = 12,    /*!< \internal used only for PKCS#1 Ver 1.5 - possible to perform verify operation without hash mode input, 
						the hash mode is derived from the signature.*/
	CRYS_RSA_HASH_NO_HASH_mode = 13,	/*!< Used for PKCS1 v1.5 Encrypt and Decrypt.*/
	CRYS_RSA_HASH_NumOfModes,		/*!< Maximal number of hash operations modes. */
	
	CRYS_RSA_HASH_OpModeLast  = 0x7FFFFFFF, /*! Reserved.*/

}CRYS_RSA_HASH_OpMode_t;   


/*! Defines the enum of the RSA decryption mode. */
typedef enum
{
	CRYS_RSA_NoCrt = 10, /*!< Decryption no CRT mode.*/
	CRYS_RSA_Crt   = 11, /*!< Decryption CRT mode.*/
	
	CRYS_RSADecryptionNumOfOptions, /*! Reserved.*/
	
	CRYS_RSA_DecryptionModeLast= 0x7FFFFFFF, /*! Reserved.*/

}CRYS_RSA_DecryptionMode_t;

/*! RSA Key source definition. */
typedef enum
{
	CRYS_RSA_ExternalKey = 1, /*!< External key.*/
	CRYS_RSA_InternalKey = 2, /*!< Internal key.*/
	
	CRYS_RSA_KeySourceLast= 0x7FFFFFFF, /*!< Reserved. */

}CRYS_RSA_KeySource_t;     

/*! MGF values. */
typedef enum
{
	CRYS_PKCS1_MGF1 = 0, /*! MGF1. */
	CRYS_PKCS1_NO_MGF = 1, /*! No MGF. */
	CRYS_RSA_NumOfMGFFunctions, /*! Maximal number of MGF options. */

	CRYS_PKCS1_MGFLast= 0x7FFFFFFF, /*! Reserved.*/

}CRYS_PKCS1_MGF_t;

/*! Defines the enum of the various PKCS1 versions. */
typedef enum
{
	CRYS_PKCS1_VER15 = 0, /*! PKCS1 version 15. */
	CRYS_PKCS1_VER21 = 1, /*! PKCS1 version 21. */
	
	CRYS_RSA_NumOf_PKCS1_versions, /*! Maximal number of PKCS versions. */
	
	CRYS_PKCS1_versionLast= 0x7FFFFFFF, /*! Reserved.*/

}CRYS_PKCS1_version;


/*! Enum defining primality testing mode in Rabin-Miller 
   and Lucas-Lehmer tests (internal tests). */					 
typedef enum
{
        /* P and Q primes */
	CRYS_RSA_PRIME_TEST_MODE     = 0, /*!< PRIME test. */
        /* FFC (DH, DSA) primes */ 
	CRYS_DH_PRIME_TEST_MODE      = 1, /*!< DH Prime test. */

	CRYS_RSA_DH_PRIME_TEST_OFF_MODE /*!< Reserved.*/ 
	
}CRYS_RSA_DH_PrimeTestMode_t;					 

/************************ Public and private key database Structs ******************************/

/* .................. The public key definitions ...................... */
/* --------------------------------------------------------------------- */

/*! Public key data structure (used internally). */
typedef struct 
{ 
	/*! RSA modulus buffer. */
	uint32_t n[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
	/*! RSA modulus size in bits. */
	uint32_t nSizeInBits;
	
	/*! RSA public exponent buffer. */
	uint32_t e[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
	/*! RSA public exponent buffer. */
	uint32_t eSizeInBits;
	
	/*! Buffer for internal usage.*/
	uint32_t crysRSAIntBuff[CRYS_PKA_BARRETT_MOD_TAG_BUFF_SIZE_IN_WORDS];
   
}CRYSRSAPubKey_t;

/*! The public key's user structure prototype. This structure must be saved by the user, and is used as input to the RSA functions 
(such as ::SaSi_RsaSchemesEncrypt etc.) */
typedef struct CRYS_RSAUserPubKey_t 
{
	/*! Validation tag. */
	uint32_t valid_tag;   
	/*! Public key data. */        
	uint32_t  PublicKeyDbBuff[ sizeof(CRYSRSAPubKey_t)/sizeof(uint32_t) + 1 ]; 
   

}CRYS_RSAUserPubKey_t;

/* .................. The private key definitions ...................... */
/* --------------------------------------------------------------------- */

/*! Private key on non-CRT mode data structure (used internally). */
typedef struct 
{    
	/*! RSA private exponent buffer. */
	uint32_t d[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
	/*! RSA private exponent size in bits. */
	uint32_t dSizeInBits;
	
	/*! RSA public exponent buffer. */
	uint32_t e[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
	/*! RSA public exponent size in bits. */
	uint32_t eSizeInBits;
      
}CRYSRSAPrivNonCRTKey_t;

/*! Private key on CRT mode data structure (used internally). */
#ifndef CRYS_NO_RSA_SMALL_CRT_BUFFERS_SUPPORT
/* use small CRT buffers */
typedef struct 
{
	/*! First factor buffer. */
	uint32_t P[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS/2]; 
	/*! First factor size in bits. */
	uint32_t PSizeInBits;
	
	/*! Second factor buffer. */
	uint32_t Q[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS/2]; 
	/*! Second factor size in bits. */
	uint32_t QSizeInBits;
	
	/*! First CRT exponent buffer. */
	uint32_t dP[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS/2]; 
	/*! First CRT exponent size in bits. */
	uint32_t dPSizeInBits;
	
	/*! Second CRT exponent buffer. */
	uint32_t dQ[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS/2]; 
	/*! Second CRT exponent size in bits. */
	uint32_t dQSizeInBits;
	
	/*! First CRT coefficient buffer. */
	uint32_t qInv[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS/2];
	/*! First CRT coefficient size in bits. */
	uint32_t qInvSizeInBits;
   
}CRYSRSAPrivCRTKey_t;

/*! Size of CRYSRSAPrivCRTKey_t structure in words (used for temp buffers allocation). */
#define CRYS_RSA_SIZE_IN_WORDS_OF_CRYSRSAPrivCRTKey_t  (CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS*7/2 + 5)

#else /* use large CRT buffers */
typedef struct 
{ 
	/* The first factor buffer and size in bits */
	uint32_t P[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS]; 
	uint32_t PSizeInBits;

	/* The second factor buffer and its size in bits */
	uint32_t Q[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS]; 
	uint32_t QSizeInBits;

	/* The first CRT exponent buffer and its size in bits */
	uint32_t dP[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS]; 
	uint32_t dPSizeInBits;

	/* The second CRT exponent buffer and its size in bits */
	uint32_t dQ[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS]; 
	uint32_t dQSizeInBits;

	/* The first CRT coefficient buffer and its size in bits */
	uint32_t qInv[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
	uint32_t qInvSizeInBits;

}CRYSRSAPrivCRTKey_t;

/* size of CRYSRSAPrivCRTKey_t structure in words (used for temp buffers allocation) */
#define CRYS_RSA_SIZE_IN_WORDS_OF_CRYSRSAPrivCRTKey_t  (CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS*5 + 5)

#endif

/*! Private key data structure (used internally). */
typedef struct
{
	/*! RSA modulus buffer. */
	uint32_t n[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
	/*! RSA modulus size in bits. */
	uint32_t nSizeInBits;   
	
	/*! Decryption operation mode. */
	CRYS_RSA_DecryptionMode_t OperationMode;
	
	/*! Key source ( internal or external ). */
	CRYS_RSA_KeySource_t KeySource;  
	
	
	/*! Union between the CRT and non-CRT data structures. */
	union 
	{ 
		CRYSRSAPrivNonCRTKey_t NonCrt; /*!< Non CRT data structure. */
		CRYSRSAPrivCRTKey_t    Crt;    /*!< CRT data structure. */
	}PriveKeyDb;
      
	/*! Internal buffer. */
	uint32_t crysRSAPrivKeyIntBuff[CRYS_PKA_PRIV_KEY_BUFF_SIZE_IN_WORDS];

}CRYSRSAPrivKey_t;

/*! The private key's user structure prototype. This structure must be saved by the user, and is used as input to the RSA functions 
(such as ::SaSi_RsaSchemesDecrypt etc.). */
typedef struct CRYS_RSAUserPrivKey_t 
{
	/*! Validation tag.*/
	uint32_t valid_tag;  
	/*! Private key data. */         
	uint32_t  PrivateKeyDbBuff[ sizeof(CRYSRSAPrivKey_t)/sizeof(uint32_t) + 1 ] ; 

}CRYS_RSAUserPrivKey_t;

/*! Temporary buffers for RSA usage. */
typedef struct CRYS_RSAPrimeData_t
{
   /* The aligned input and output data buffers */
	uint32_t DataIn[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];  /*!< Temporary buffer for data in.*/
	uint32_t DataOut[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS]; /*!< Temporary buffer for data out.*/
	/*! Temporary buffer for internal data.*/
	SASI_PAL_COMPILER_ALIGN(4) uint8_t  InternalBuff[CRYS_RSA_TMP_BUFF_SIZE]; 

}CRYS_RSAPrimeData_t; 

/*! KG data type. */
typedef union CRYS_RSAKGData_t
{
	/*! RSA Key Generation buffers definitions. */
	struct
	{
		/* The aligned input and output data buffers */
		/*! First factor buffer. */
		uint32_t p[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS / 2];
		/*! Second factor buffer. */
		uint32_t q[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS / 2];
		union {
			/*! Internal buffer. */			
			uint32_t crysRSAKGDataIntBuff[CRYS_PKA_KGDATA_BUFF_SIZE_IN_WORDS];
			#ifdef DX_SOFT_KEYGEN
			/* # added for compatibility with size of KGData SW type */
			uint32_t TempbuffExp[PKI_KEY_GEN_TEMP_BUFF_SIZE_WORDS];
			#endif
		}kg_buf;
	}KGData;

	/*! Buffers for internal usage. */
	union {
		/*! Internally used buffer.*/
	        struct {
			CRYS_RSAPrimeData_t   	PrimData;
		}primExt;
		#ifdef DX_SOFT_KEYGEN
		/* # added for compatibility with size of SW CRYSRSAPrivKey_t type */
	        SW_Shared_CRYS_RSAPrimeData_t SW_Shared_PrimData;
		#endif
	}prim; 
}CRYS_RSAKGData_t; 

 /*************
 *	RSA contexts 
 **************/
/************************ CRYS RSA struct for Private Key ******************************/

/*! Context definition for operations that use the RSA private key. */
typedef struct 
{

	/*! Private key data.  */
	CRYS_RSAUserPrivKey_t PrivUserKey;
	
	/*! RSA PKCS#1 Version 1.5 or 2.1 */
	uint8_t   PKCS1_Version;
	
	/*! MGF to be used for the PKCS1 Ver 2.1 sign or verify operations. */
	uint8_t MGF_2use;
	   
	/*! Salt random length for PKCS#1 PSS Ver 2.1*/
	uint16_t SaltLen;
		   
	/*! Internal buffer. */
	CRYS_RSAPrimeData_t  PrimeData;
	   
	/*! HASH context buffer. */
	uint32_t CRYSPKAHashCtxBuff[CRYS_PKA_RSA_HASH_CTX_SIZE_IN_WORDS];
	/*! HASH result buffer. */
	CRYS_HASH_Result_t        HASH_Result;
	/*! HASH result size in words. */
	uint16_t                  HASH_Result_Size;     /*in words*/
	/*! RSA HASH operation mode (all modes RSA supports).*/
	CRYS_RSA_HASH_OpMode_t    RsaHashOperationMode; /*RSA HASH enum. */
	/*! HASH operation mode.*/
	CRYS_HASH_OperationMode_t HashOperationMode;    /*CRYS HASH enum. */
	/*! HASH block size (in words).*/
	uint16_t                  HashBlockSize;        /*in words*/
	/*! HASH flag. */
	bool doHash;
	
	/* Used for sensitive data manipulation in the context space, which is safer and which saves stack space */
	/*! Internal buffer.*/
	uint32_t EBD[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
	/*! Internal bufffer used size in bits. */
	uint32_t EBDSizeInBits;
	   
	/* Used for sensitive data manipulation in the context space, which is safer and which saves stack space */
	/*! Internal buffer.*/
	uint8_t  T_Buf[CRYS_RSA_SIZE_OF_T_STRING_BYTES];
	/*! Internal buffer used size.*/
	uint16_t T_BufSize;
	   
	/*! Buffer for the use of the Ber encoder in the case of PKCS#1 Ver 1.5. */
	uint32_t  BER[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
	/*! Ber encoder buffer size.*/
	uint16_t  BERSize;
	
	/*! Internal buffer.*/
	uint8_t DummyBufAESBlockSize[16];
    
}RSAPrivContext_t;

/*! The user's context prototype - the argument type that is passed by the user
   to the RSA APIs. The context saves the state of the operation and must be saved by the user 
   till the end of the APIs flow . */
typedef struct CRYS_RSAPrivUserContext_t 
{
	/*! Validation tag. */
	uint32_t valid_tag; 
	/*! Internally used value.*/
	uint32_t AES_iv; 
	/*! Private data context buffer. */
	SASI_PAL_COMPILER_ALIGN(4) uint8_t  context_buff[ sizeof(RSAPrivContext_t) + sizeof(uint32_t)];  /* must be aligned to 4 */
 
}CRYS_RSAPrivUserContext_t;


/************************ CRYS RSA struct for Public Key ******************************/   
   
/*! Context definition for operations that use the RSA public key. */
typedef struct 
{

	/*! RSA public key structure. */
	CRYS_RSAUserPubKey_t PubUserKey;
	
	/*! Public key size in bytes */
	uint32_t nSizeInBytes;
	
	/*! RSA PKCS#1 Version 1.5 or 2.1 */
	uint8_t   PKCS1_Version;
	
	/*! MGF to be used for the PKCS1 Ver 2.1 Sign or Verify operations */
	uint8_t MGF_2use;
	   
	/*! Salt random length for PKCS#1 PSS Ver 2.1*/
	uint16_t SaltLen;
	   
	/*! Internal buffer. */
	CRYS_RSAPrimeData_t  PrimeData;
	   
	/*! HASH context. */
	uint32_t CRYSPKAHashCtxBuff[CRYS_PKA_RSA_HASH_CTX_SIZE_IN_WORDS];
	/*! HASH result buffer. */
	CRYS_HASH_Result_t        HASH_Result;
	/*! HASH result size. */
	uint16_t                  HASH_Result_Size; /* denotes the length, in words, of the hash function output */
	/*! RSA HASH operation mode (all modes RSA supports). */
	CRYS_RSA_HASH_OpMode_t    RsaHashOperationMode; /*RSA HASH enum. */
	/*! HASH operation mode. */
	CRYS_HASH_OperationMode_t HashOperationMode;    /*CRYS HASH enum. */
	/*! HASH block size. */
	uint16_t                  HashBlockSize; /*in words*/
	/*! HASH flag.*/
	bool doHash;
	
	/* Used for sensitive data manipulation in the context space, which is safer and which saves stack space */
	/*! Internal buffer.*/
	uint32_t EBD[CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
	/*! Internal bufffer used size in bits. */
	uint32_t EBDSizeInBits;
	   
	/* Used for sensitive data manipulation in the context space, which is safer and which saves stack space */
	/*! Internal buffer.*/
	uint8_t T_Buf[CRYS_RSA_SIZE_OF_T_STRING_BYTES];
	/*! Internal buffer used size.*/
	uint16_t T_BufSize;
	
	/*! Internal buffer.*/
	uint8_t DummyBufAESBlockSize[16];

}RSAPubContext_t;

/*! Temporary buffers for the RSA usage. */
typedef struct CRYS_RSAPubUserContext_t 
{
	/*! Validation tag. */
	uint32_t valid_tag; 
	/*! Internally used value.*/
	uint32_t AES_iv; /* For the use of the AES CBC mode of Encryption and Decryption of the context in CCM */              
	/*! Public data context buffer. */
	uint32_t  context_buff[ sizeof(RSAPubContext_t)/sizeof(uint32_t) + 1] ; 
 
}CRYS_RSAPubUserContext_t;



/*! Required for internal FIPS verification for RSA key generation. */ 
typedef struct CRYS_RSAKGFipsContext_t{
	/*! Internal buffer. */
	CRYS_RSAPrimeData_t 	primData;
	/*! Buffer used for decryption. */
	uint8_t			decBuff[((CRYS_RSA_MIN_VALID_KEY_SIZE_VALUE_IN_BITS/SASI_BITS_IN_BYTE) - 2*(CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES) -2)];
	/*! Buffer used for encryption. */
	uint8_t			encBuff[CRYS_RSA_FIPS_MODULUS_SIZE_BITS/SASI_BITS_IN_BYTE];
}CRYS_RSAKGFipsContext_t;

/*! Required for internal FIPS verification for RSA KAT. The RSA KAT tests defined for scheme 2.1 with modulus key size of 2048.      */
typedef struct CRYS_RSAFipsKatContext_t{
	/*! RSA user's key (either public or private).*/
	union {
		/*! RSA user's public key. */
		CRYS_RSAUserPubKey_t 	userPubKey; 	// used for RsaEnc and RsaVerify
		/*! RSA user's private key. */
		CRYS_RSAUserPrivKey_t   userPrivKey;  // used for RsaDec and RsaSign
	}userKey;
	/*! RSA user's context (either public or private).*/
	union {
		/*! RSA user's private context. */
		CRYS_RSAPrivUserContext_t userPrivContext;  // used for RsaSign
		/*! RSA public user's context. */
		CRYS_RSAPubUserContext_t userPubContext;  // used for RsaVerify
		/*! Internal buffers. */
		CRYS_RSAPrimeData_t 	primData;  // used for RsaEnc and RsaDec
	}userContext;
	/*! RSA user's data. */
	union {
		struct {   // used for RsaEnc and RsaDec
			/*! Buffer for encrypted data. */
			uint8_t		encBuff[CRYS_RSA_FIPS_MODULUS_SIZE_BITS/SASI_BITS_IN_BYTE];
			/*! Buffer for decrypted data. */
			uint8_t		decBuff[((CRYS_RSA_FIPS_MODULUS_SIZE_BITS/SASI_BITS_IN_BYTE) - 2*(CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES) -2)];
		}userOaepData;
		/*! Buffer for Signed data. */
		uint8_t			signBuff[CRYS_RSA_FIPS_MODULUS_SIZE_BITS/SASI_BITS_IN_BYTE]; // used for RsaSign and RsaVerify
	}userData;
}CRYS_RSAFipsKatContext_t;


#ifdef __cplusplus
}
#endif
/** 
@}
 */
#endif
