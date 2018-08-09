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

#include "ssi_pal_types.h"

#ifdef AES_INTEGTEST
#include "ssi_aes.h"
#include "crys_aesccm.h"
#endif

#ifdef ECC_INTEGTEST
#include "crys_ecpki_types.h"
#endif

#ifdef HASH_INTEGTEST
#include "crys_hash.h"
#endif

#ifdef HMAC_INTEGTEST
#include "crys_hash.h"
#include "crys_hmac.h"
#endif

#ifdef RSA_INTEGTEST
#include "crys_rsa_types.h"
#endif

#ifdef CHACHA_INTEGTEST
#include "crys_chacha.h"
#include "crys_poly.h"
#endif


#ifdef HKDF_INTEGTEST
#include "crys_hkdf.h"
#endif

#define MAX_TEST_DATA_SIZE               256
#define MAX_AES_CCM_DATA_SIZE_VECTOR     0x40
#define MAX_RND_SIZE_VECTOR              0x20

#ifdef AES_INTEGTEST
typedef struct aesDataStuct{	
	uint8_t			        aesTest_name[MAX_TEST_DATA_SIZE];
	uint8_t                 TST_KeyData[SASI_AES_KEY_MAX_SIZE_IN_BYTES];
	uint8_t                 TST_KeySize;
	SaSiAesIv_t         	aesTest_IvCounter;
	uint8_t 			aesTest_input_data[MAX_TEST_DATA_SIZE];
	uint8_t 			aesTest_output_data[MAX_TEST_DATA_SIZE];
	uint8_t 			aesTest_Expected_output_data[MAX_TEST_DATA_SIZE];
	uint16_t			aesTest_DataSize;	
	SaSiAesOperationMode_t  	aesTest_OperationMode;
	SaSiAesEncryptMode_t		aesTest_EncDecMode;
	uint32_t                       	aesTest_OutputDataSize;
} aesDataStuct;

typedef struct aesCCMDataStuct{	
	uint8_t			        aesCCMTest_name[MAX_TEST_DATA_SIZE];
	CRYS_AESCCM_Key_t 		aesCCMTest_Key;
	CRYS_AESCCM_KeySize_t	aesCCMTest_KeySize;
	uint8_t 			    aesCCMTest_NData[MAX_AES_CCM_DATA_SIZE_VECTOR];
	uint32_t		     	aesCCMTest_NDataSize;
	uint8_t 			    aesCCMTest_AddData[MAX_AES_CCM_DATA_SIZE_VECTOR];
	uint32_t		     	aesCCMTest_AddDataSize;
	uint8_t 			    aesCCMTest_TextData[MAX_AES_CCM_DATA_SIZE_VECTOR];
	uint32_t		     	aesCCMTest_TextdataSize;
	uint8_t 			    aesCCMTest_Expected_output_data[MAX_AES_CCM_DATA_SIZE_VECTOR];
	uint8_t 			    aesCCMTest_Output_data[MAX_AES_CCM_DATA_SIZE_VECTOR];
	uint32_t                aesCCMTest_OutputDataSize;
	uint8_t 		    	aesCCMTest_Expected_MAC_output_data[MAX_AES_CCM_DATA_SIZE_VECTOR];
	uint8_t 		    	aesCCMTest_Output_MAC_data[MAX_AES_CCM_DATA_SIZE_VECTOR];
	uint32_t                aesCCMTest_Output_CCM_MACSize;
} aesCCMDataStuct;
#endif

#ifdef ECC_INTEGTEST
typedef struct eccSignDataStuct{	
	uint8_t			        eccTest_name[MAX_TEST_DATA_SIZE];
	CRYS_ECPKI_DomainID_t		eccTest_DomainID;
	CRYS_ECPKI_HASH_OpMode_t   	eccTest_HashMode;
	uint8_t  			eccTest_InputData[MAX_TEST_DATA_SIZE];
	uint32_t                        eccTest_InputDataSize; 
	uint8_t  			eccTest_PubKey[MAX_TEST_DATA_SIZE];
	uint32_t                        eccTest_PubKeySize; 
	uint8_t  			eccTest_PrivKey[MAX_TEST_DATA_SIZE];
	uint32_t                        eccTest_PrivKeySize;
	uint32_t                        eccTest_SignitureSize;  
		
} eccSignDataStuct;
	
typedef struct eccDHDataStuct{	
	uint8_t			        eccDHTest_name[MAX_TEST_DATA_SIZE];
	CRYS_ECPKI_DomainID_t		eccDHTest_DomainID;
	uint8_t  			eccDHTest_PubKey1[MAX_TEST_DATA_SIZE];
	uint32_t                        eccDHTest_PubKeySize1; 
	uint8_t  			eccDHTest_PrivKey1[MAX_TEST_DATA_SIZE];
	uint32_t                        eccDHTest_PrivKeySize1;
	uint8_t  			eccDHTest_PubKey2[MAX_TEST_DATA_SIZE];
	uint32_t                        eccDHTest_PubKeySize2; 
	uint8_t  			eccDHTest_PrivKey2[MAX_TEST_DATA_SIZE];
	uint32_t                        eccDHTest_PrivKeySize2;

} eccDHDataStuct; 
#endif

#ifdef CHACHA_INTEGTEST
typedef struct CHACHA_DataStruct {
        uint8_t                     testName[MAX_TEST_DATA_SIZE];       
        CRYS_CHACHA_Nonce_t         pIVCounter;
        CRYS_CHACHA_NonceSize_t     IVSize;
        CRYS_CHACHA_Key_t           pKey;
        uint32_t                    initialCounter;
        CRYS_CHACHA_EncryptMode_t   encryptDecryptFlag;
        uint8_t                     pDataIn[MAX_TEST_DATA_SIZE];
        uint32_t                    dataInSize;
        uint8_t                     pExpectedDataOut[MAX_TEST_DATA_SIZE];
        CRYSError_t                 expectedRc;
} CHACHA_DataStruct;

#define TEST_CHACHA_POLY_DATA_SIZE_MAX   272
typedef struct CHACHA_POLY_DataStruct {
        uint8_t                     testName[MAX_TEST_DATA_SIZE];       
        CRYS_CHACHA_EncryptMode_t   encryptDecryptFlag;
        CRYS_CHACHA_Key_t           pKey;
        uint8_t                     pDataIn[TEST_CHACHA_POLY_DATA_SIZE_MAX];
        uint32_t                    dataInSize;
        CRYS_CHACHA_Nonce_t	        pNonce;
        uint8_t                     pAddData[TEST_CHACHA_POLY_DATA_SIZE_MAX];
        uint32_t                    addDataSize;
        uint8_t                     pExpectedDataOut[TEST_CHACHA_POLY_DATA_SIZE_MAX];
        uint8_t                     pExpectedMac[CRYS_POLY_MAC_SIZE_IN_BYTES];
        CRYSError_t                 expectedRc;
} CHACHA_POLY_DataStruct_t;
#endif

#ifdef HASH_INTEGTEST

typedef struct hashDataStuct{	
	uint8_t			        hashTest_Name[MAX_TEST_DATA_SIZE];
	CRYS_HASH_OperationMode_t	hashTest_TST_OperationMode;
	uint8_t 			hashTest_InputData[MAX_TEST_DATA_SIZE];
	uint32_t			hashTest_InputDataSize;
	CRYS_HASH_Result_t	hashTest_ExpOutData;
	uint32_t			hashTest_ExpOutDataSize;
} hashDataStuct;
#endif

#ifdef HMAC_INTEGTEST
typedef struct hmacDataStuct{	
	uint8_t			        hmacTest_Name[MAX_TEST_DATA_SIZE];
	CRYS_HASH_OperationMode_t	hmacTest_TST_OperationMode;
	uint8_t				hmacTest_Key[CRYS_HMAC_KEY_SIZE_IN_BYTES];
	uint16_t                        hmacTest_KeySize;	
	uint8_t 			hmacTest_InputData[MAX_TEST_DATA_SIZE];
	uint32_t			hmacTest_InputDataSize;
	CRYS_HASH_Result_t	hmacTest_ExpOutData;
	uint32_t			hmacTest_ExpOutDataSize;
} hmacDataStuct;	
#endif

#ifdef RND_INTEGTEST
typedef struct rndDataStuct{
	uint8_t			        hmacTest_Name[MAX_TEST_DATA_SIZE];
	uint32_t	                rndTest_AddInputSize;
	uint8_t				rndTest_AddInputData[MAX_RND_SIZE_VECTOR];
	uint32_t	                rndTest_RandomVectorSize;
	uint8_t				rndTest_RandomVectorData1[MAX_RND_SIZE_VECTOR];
	uint8_t				rndTest_RandomVectorData2[MAX_RND_SIZE_VECTOR];
	uint32_t	                rndTest_RandomVectorInRangeSize1;
	uint8_t				rndTest_RandomVectorInRangeData[MAX_RND_SIZE_VECTOR];
	uint32_t	                rndTest_RandomVectorInRangeSize2;
	uint8_t				rndTest_MaxVectorInRange2[MAX_RND_SIZE_VECTOR];
	uint8_t				rndTest_RandomVectorInRangeData2[MAX_RND_SIZE_VECTOR];

} rndDataStuct;
#endif


#ifdef RSA_INTEGTEST

#define TST_MAX_PRVT_EXP_SIZE_IN_BYTES              256
#define TST_MAX_PUB_EXP_SIZE_IN_BYTES               3
#define TST_MAX_MOD_SIZE_IN_BYTES                   256
#define TST_MAX_ENCDEC_DATA_IN_BYTES                256
#define TST_MAX_SIGN_VERIFY_DATA_IN_BYTES           512
#define TST_MAX_PUB_EXP_SIZE_IN_BYTES               3
#define TST_MAX_SINGLE_RSA_SIGN_BLOCK_SIZE_IN_BYTS  16
#define TST_LESS_DATA_FOR_PKCS1V15_ENCRYPT	    11 
#define TST_LESS_DATA_FOR_OAEP_ENCRYPT_SHA1	    42
#define TST_LESS_DATA_FOR_OAEP_ENCRYPT_SHA224	    58
#define TST_LESS_DATA_FOR_OAEP_ENCRYPT_SHA256	    66
#define TST_LESS_DATA_FOR_OAEP_ENCRYPT_SHA384	    98
#define TST_LESS_DATA_FOR_OAEP_ENCRYPT_SHA512	    130
#define TST_NO_CRT 	                            0
#define TST_CRT_MODE                                1
#define TST_RSA_512_KEY_SIZE_IN_BYTES               64
#define TST_RSA_1024_KEY_SIZE_IN_BYTES              128
#define TST_LESS_DATA_FOR_PKCS1V15_ENCRYPT	    11
#define TST_LESS_DATA_FOR_OAEP_ENCRYPT_SHA1	    42
#define TST_LESS_DATA_FOR_OAEP_ENCRYPT_SHA224	    58
#define TST_LESS_DATA_FOR_OAEP_ENCRYPT_SHA256	    66
#define TST_LESS_DATA_FOR_OAEP_ENCRYPT_SHA384	    98
#define TST_LESS_DATA_FOR_OAEP_ENCRYPT_SHA512	    130


typedef struct rsaEncDecDataStuct{	
    uint8_t					rsaEncDec_Name[MAX_TEST_DATA_SIZE];
    uint8_t					rsaEncDec_PrivetExponent_D[TST_MAX_PRVT_EXP_SIZE_IN_BYTES];
    uint8_t					rsaEncDec_PublicExponent_E[TST_MAX_PUB_EXP_SIZE_IN_BYTES];
    uint8_t					rsaEncDec_Modulus_N[TST_MAX_MOD_SIZE_IN_BYTES];
    uint8_t					rsaEncDec_P[TST_MAX_PRVT_EXP_SIZE_IN_BYTES/2]; 
    uint8_t					rsaEncDec_Q[TST_MAX_PRVT_EXP_SIZE_IN_BYTES/2];  	   
    uint8_t					rsaEncDec_dP[TST_MAX_PRVT_EXP_SIZE_IN_BYTES/2];
    uint8_t					rsaEncDec_dQ[TST_MAX_PRVT_EXP_SIZE_IN_BYTES/2];
    uint8_t					rsaEncDec_Qinv[TST_MAX_PRVT_EXP_SIZE_IN_BYTES/2];		  	
    uint16_t					rsaEncDec_KeySize;
    uint16_t					rsaEncDec_DPSize;
    uint16_t					rsaEncDec_PubExponentSize; 
    uint8_t 					rsaEncDec_input_data[TST_MAX_ENCDEC_DATA_IN_BYTES];	
    uint8_t 					rsaEncDec_output_data[TST_MAX_ENCDEC_DATA_IN_BYTES];	
    uint8_t 					rsaEncDec_Expected_output_data[TST_MAX_ENCDEC_DATA_IN_BYTES];	      
} rsaEncDecDataStuct;


typedef struct rsaSignVerifyDataStuct{	
    char				        rsaSignVerify_Name[MAX_TEST_DATA_SIZE];
    uint8_t 		                        rsaSignVerify_PrivetExponent_D[TST_MAX_PRVT_EXP_SIZE_IN_BYTES];
    uint8_t					rsaSignVerify_PublicExponent_E[TST_MAX_PRVT_EXP_SIZE_IN_BYTES];
    uint8_t					rsaSignVerify_Modulus_N[TST_MAX_MOD_SIZE_IN_BYTES];
    uint8_t					rsaSignVerify_P[TST_MAX_PRVT_EXP_SIZE_IN_BYTES/2]; 
    uint8_t					rsaSignVerify_Q[TST_MAX_PRVT_EXP_SIZE_IN_BYTES/2];  	   
    uint8_t					rsaSignVerify_dP[TST_MAX_PRVT_EXP_SIZE_IN_BYTES/2];
    uint8_t					rsaSignVerify_dQ[TST_MAX_PRVT_EXP_SIZE_IN_BYTES/2];
    uint8_t					rsaSignVerify_Qinv[TST_MAX_PRVT_EXP_SIZE_IN_BYTES/2];		  	
    uint16_t					rsaSignVerify_KeySize;
    uint16_t					rsaSignVerify_DPSize;
    uint16_t					rsaSignVerify_PubExponentSize; 
    uint16_t					rsaSignVerify_SaltLength;
    uint8_t 					rsaSignVerify_input_data[TST_MAX_SIGN_VERIFY_DATA_IN_BYTES];
    uint16_t 					rsaSignVerify_input_dataSize;
    uint8_t 					rsaSignVerify_output_signiture[TST_MAX_PRVT_EXP_SIZE_IN_BYTES];	
    uint8_t                   	                rsaSignVerify_hash_SHA1[CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES];
    uint8_t                   	                rsaSignVerify_hash_SHA256[CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES];
    uint8_t                   	                rsaSignVerify_hash_SHA512[CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES];
    
} rsaSignVerifyDataStuct;
#endif

#ifdef HKDF_INTEGTEST
#define TST_NAME_STRING_LEN             150

#define TST_HKDF_MAX_IKM_SIZE           512  
#define TST_HKDF_MAX_SALT_SIZE         	512 
#define TST_HKDF_MAX_INFO_SIZE        	128 
#define TST_HKDF_MAX_PRK_SIZE        	2048 
#define TST_HKDF_MAX_OKM_SIZE        	4096 

typedef struct hkdfDataStuct{	
	char			    hkdf_Name[TST_NAME_STRING_LEN];
	CRYS_HKDF_HASH_OpMode_t	    hkdfHashMode;
	uint8_t		    	hkdf_IKM[TST_HKDF_MAX_IKM_SIZE];
	uint32_t		    hkdf_IKMSize;
	uint8_t 		    hkdf_Salt[TST_HKDF_MAX_SALT_SIZE];
	uint32_t		    hkdf_SaltSize;
	uint8_t 		    hkdf_Info[TST_HKDF_MAX_INFO_SIZE];
	uint32_t		    hkdf_InfoSize;
	uint8_t 		    hkdf_ExpectedPRK[TST_HKDF_MAX_PRK_SIZE];
	uint32_t		    hkdf_ExpectedPRKSize;
	uint8_t 	        hkdf_ExpectOKM[TST_HKDF_MAX_OKM_SIZE];
	uint32_t		    hkdf_LSize;
} hkdfDataStuct;

#endif
