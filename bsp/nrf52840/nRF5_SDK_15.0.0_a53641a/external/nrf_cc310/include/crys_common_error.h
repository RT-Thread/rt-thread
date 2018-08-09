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



 #ifndef CRYS_COMMON_ERROR_H
#define CRYS_COMMON_ERROR_H

#include "crys_error.h"

#ifdef __cplusplus
extern "C"
{
#endif


/************************ Defines ******************************/

/* CRYS COMMON module errors. Base address - 0x00F00D00 */

#define CRYS_COMMON_INIT_HW_SEM_CREATION_FAILURE    (CRYS_COMMON_MODULE_ERROR_BASE + 0x0UL)
#define CRYS_COMMON_DATA_IN_POINTER_INVALID_ERROR   (CRYS_COMMON_MODULE_ERROR_BASE + 0x4UL)
#define CRYS_COMMON_DATA_SIZE_ILLEGAL           (CRYS_COMMON_MODULE_ERROR_BASE + 0x5UL)
#define CRYS_COMMON_DATA_OUT_DATA_IN_OVERLAP_ERROR  (CRYS_COMMON_MODULE_ERROR_BASE + 0x6UL)
#define CRYS_COMMON_DATA_OUT_POINTER_INVALID_ERROR  (CRYS_COMMON_MODULE_ERROR_BASE + 0x7UL)
#define CRYS_COMMON_OUTPUT_BUFF_SIZE_ILLEGAL        (CRYS_COMMON_MODULE_ERROR_BASE + 0x9UL)

#define CRYS_COMMON_TST_UTIL_CHUNK_SIZE_SMALL_ERROR (CRYS_COMMON_MODULE_ERROR_BASE + 0x10UL)
#define CRYS_COMMON_ERROR_IN_SAVING_LLI_DATA_ERROR  (CRYS_COMMON_MODULE_ERROR_BASE + 0x11UL)


#define CRYS_COMMON_TST_UTIL_LLI_ENTRY_SIZE_TOO_SMALL_ERROR   (CRYS_COMMON_MODULE_ERROR_BASE + 0x12UL)
#define CRYS_COMMON_TST_CSI_DATA_SIZE_EXCEED_ERROR            (CRYS_COMMON_MODULE_ERROR_BASE + 0x13UL)
#define CRYS_COMMON_TST_CSI_MODULE_ID_OUT_OF_RANGE            (CRYS_COMMON_MODULE_ERROR_BASE + 0x14UL)
#define CRYS_COMMON_TST_CSI_MEMORY_MAPPING_ERROR              (CRYS_COMMON_MODULE_ERROR_BASE + 0x15UL)

#define CRYS_COMMON_TERM_HW_SEM_DELETE_FAILURE                (CRYS_COMMON_MODULE_ERROR_BASE + 0x16UL)

#define CRYS_COMMON_TST_UTIL_NOT_INTEGER_CHAR_ERROR           (CRYS_COMMON_MODULE_ERROR_BASE + 0x17UL)
#define CRYS_COMMON_TST_UTIL_BUFFER_IS_SMALL_ERROR            (CRYS_COMMON_MODULE_ERROR_BASE + 0x18UL)
#define CRYS_COMMON_POINTER_NOT_ALIGNED_ERROR                 (CRYS_COMMON_MODULE_ERROR_BASE + 0x19UL)


/************************ Enums ********************************/


/************************ Typedefs  ****************************/


/************************ Structs  ******************************/


/************************ Public Variables **********************/


/************************ Public Functions **********************/

#ifdef __cplusplus
}
#endif

#endif


