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

#define SHARED_SECRET_MAX_LENGHT         250
#define ECC_KEY_MAX_LENGHT               0x256
#define AES_KEY_MAX_LENGHT_IN_BYTES      0x10



#define HASH_TESTS_NUMBER                0x3
#define AES_TESTS_NUMBER                 0x4
#define AES_CCM_TESTS_NUMBER             0x1
#define ECC_SIGN_TESTS_NUMBER            0x2
#define ECC_DH_TESTS_NUMBER              0x2
#define CHACHA_TESTS_NUMBER              0xA
#define CHACHA_POLY_TESTS_NUMBER         0x2
#define HMAC_TESTS_NUMBER                0x2
#define RSA_ENCDEC_OEP_TESTS_NUMBER      0x2
#define RSA_SIGN_VERIFY_OEP_TESTS_NUMBER 0x1
#define HKDF_TESTS_NUMBER                0x8
#define OPERATIONS_NUMBER                0x2//Integrated/noniNtegrated


typedef enum OperationType_enum
{
	 INTEGRATED_OPERATION   ,
	 NON_INTEGRATED_OPERATION  ,
	 OperationTypeLast= 0x7FFFFFFF,

}OperationType_t; 

typedef enum BufferType_enum
{
	 NON_INPLACE_BUFFER   ,
	 INPLACE_BUFFER  ,
	 BufferTypeLast= 0x7FFFFFFF,

}BufferType_t; 

typedef enum RSAType_enum
{
	 NON_CRT_MODE   ,
	 CRT_MODE  ,
	 RSATypeLast= 0x7FFFFFFF,

}RSAType_enum; 

