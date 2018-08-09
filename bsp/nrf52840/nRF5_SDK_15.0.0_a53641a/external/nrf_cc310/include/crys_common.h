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




#ifndef CRYS_COMMON_H
#define CRYS_COMMON_H

#include "crys_common_error.h"


#ifdef __cplusplus
extern "C"
{
#endif


/************************ Defines ******************************/

#define CRYS_AES_SECRET_KEY_SIZE_IN_WORDS           4

/* the ROT13 definition - relevant only on SW low level engines compiled in the ROT mode */
#define CRYS_COMMON_ROT_13_OFFSET                   13



/************************ Enums ********************************/

/************************ Typedefs  ****************************/

/************************ Structs  *****************************/

/************************ Public Variables *********************/

/************************ Public Functions *********************/



/***********************************************************************
 **
 * @brief This function executes a reverse bytes copying from one buffer to another buffer.
 *
 *        Overlapping of buffers is not allowed, excluding the case, when destination and source
 *        buffers are the same.
 *        Example of a 5 byte buffer:
 *
 *        dst_ptr[4] = src_ptr[0]
 *        dst_ptr[3] = src_ptr[1]
 *        dst_ptr[2] = src_ptr[2]
 *        dst_ptr[1] = src_ptr[3]
 *        dst_ptr[0] = src_ptr[4]
 *
 * @param[in] dst_ptr - The pointer to destination buffer.
 * @param[in] src_ptr - The pointer to source buffer.
 * @param[in] size    - The size in bytes.
 *
 */
 CRYSError_t CRYS_COMMON_ReverseMemcpy( uint8_t *dst_ptr , uint8_t *src_ptr , uint32_t size );


/***********************************************************************
 **
 * @brief This function converts aligned words array to bytes array/
 *
 *            1. Assumed, that input buffer is aligned to 4-bytes word and
 *               bytes order is set according to machine endianness.
 *            2. Output buffer receives data as bytes stream from LSB to MSB.
 *               For increasing performance on small buffers, the output data is given
 *               by rounded down pointer and alignment.
 *            3. This implementation is given for both Big and Little endian machines.
 *
 *
 * @param[in] in32_ptr - The pointer to aligned input buffer.
 * @param[in] out32_ptr - The 32-bits pointer to output buffer (rounded down to 4 bytes) .
 * @param[in] outAlignBits - The actual output data alignment;
 * @param[in] sizeWords - The size in words (sizeWords >= 1).
 *
 *  return - no return value.
 */
 void CRYS_COMMON_AlignedWordsArrayToBytes( uint32_t *in32_ptr , uint32_t *out32_ptr ,
                                            uint32_t outAlignBits, uint32_t sizeWords );

/***********************************************************************/
 /**
  * @brief This function converts in place words byffer to bytes buffer with
  *        reversed endianity of output array.
  *
  *        The function can convert:
  *           - big endian bytes array to words array with little endian order
  *             of words and backward.
  *
  *      Note:
  *      1. Endianness of each word in words buffer should be set allways
  *      according to processor used.
  *      2. Implementation is given for both big and little endianness of
  *      processor.
  *
  * @param[in]  buf_ptr - The 32-bits pointer to input/output buffer.
  * @param[in]  sizeWords - The size in words (sizeWords > 0).
  *
  * @return - no return value.
  */
void CRYS_COMMON_InPlaceConvertBytesWordsAndArrayEndianness(
                    uint32_t *buf_ptr,
                    uint32_t  sizeWords);


/***********************************************************************/
  /**
  * @brief This function converts big endianness bytes array to aligned words
  *        array with words order according to little endian /
  *
  *            1. Assumed, that input bytes order is set according
  *           to big endianness: MS Byte is most left, i.e. order is from
  *           Msb to Lsb.
  *            2. Output words array should set according to
  *           little endianness words order: LSWord is most left, i.e. order
  *           is from Lsw to Msw. Order bytes in each word - according to
  *            3. Implementation is given for both big and little
  *           endianness of processor.
  *
  * @param[out] out32_ptr - The 32-bits pointer to output buffer.
  * @param[in] sizeOutBuffBytes - The size in bytes of output buffer, must be
  *            aligned to 4 bytes and not less than sizeInBytes.
  * @param[in] in8_ptr - The pointer to input buffer.
  * @param[in] sizeInBytes - The size in bytes of input data(sizeBytes >= 1).
  *
  * @return CRYSError_t - On success CRYS_OK is returned, on failure a
  *                        value MODULE_* as defined in .
  */
CRYSError_t CRYS_COMMON_ConvertMsbLsbBytesToLswMswWords(
                    uint32_t *out32_ptr,
                    uint32_t  sizeOutBuffBytes,
                    const uint8_t  *in8_ptr,
                    uint32_t  sizeInBytes);


/***********************************************************************/
  /**
  * @brief This function converts LE 32bit-words array to BE bytes array.
  *
  *     Note: The function allows output full size of the data and also output
  *           without leading zeros, if the user gives appropriate exact output
  *           size < input size.
  *
  *     Assuming:
  *            1. Output bytes order is according to big endianness:
  *               MS Byte is most left, i.e. order is from Msb to Lsb.
  *            2. Input array words order is set according to
  *           little endianness words order: LSWord is most left, i.e. order
  *           is from Lsw to Msw. Bytes order in each word - according to
  *           processor endianness.
  *            3. Owerlapping of buffers is not allowed, besides in
  *           place operation and size aligned to full words.
  *            4. Implementation is given for both big and little
  *               endianness of processor.
  *
  * @param[in] out8_ptr - The bytes pointer to the output buffer.
  * @param[in] sizeOutBuffBytes - The size of the data in bytes to output; must
  *       be not less, than sizeInBytes.
  * @param[out] in32_ptr - The pointer to the input buffer.
  * @param[in] sizeInpBytes - The size of the input data in bytes. The size must
  *       be > 0 and aligned to 4 bytes.
  *
  * @return CRYSError_t - On success CRYS_OK is returned, on failure a
  *                        value MODULE_* as defined in .
  */
CRYSError_t CRYS_COMMON_ConvertLswMswWordsToMsbLsbBytes(
                    uint8_t  *out8_ptr,
                    uint32_t  sizeOutBytes,
                    uint32_t *in32_ptr,
                    uint32_t  sizeInpBytes);


/***********************************************************************/
/**
 * @brief VOS_GetGlobalData get the global random key hidden inside the function
 *  the global data implemented for now are random key buffer and AES secret key buffer
 *
 * When no_rtos is declared then we allow a global data. The random key/AES secret key are hidden as static inside the function
 *
 *
 * @param[in] Globalid     select the buffer
 * @param[in] GlobalDataSizeWords      - the global data buffer size needed in words - this value must be a predetermined value
 * @param[out] GlobalData_ptr - Pointer to the global buffer returned. The buffer must be at least GlobalDataSizeWords size
 *
 * @return CRYSError_t - On success CRYS_OK is returned, on failure an Error as defined in VOS_error
 */
CRYSError_t CRYS_COMMON_GetGlobalData(uint16_t Globalid, uint32_t *GlobalData_ptr, uint16_t GlobalDataSizeWords);


/***********************************************************************/
/**
* @brief CRYS_COMMON_StoreGlobalData store the global random key into the global buffer hidden inside the function
*   the global data implemented for now are random key buffer and AES secret key buffer
*
*
* @param[in] Globalid      - random key / AES secret key
* @param[in] GlobalDataSizeWords       - the global data buffer size needed in words - this value must be a predetermined value
* @param[in] GlobalData_ptr - Pointer to the global buffer to be saved. The buffer must be at least GlobalDataSizeWords size
*
*   Return Value:
*/
CRYSError_t CRYS_COMMON_StoreGlobalData(uint16_t Globalid, uint32_t *GlobalData_ptr, uint16_t GlobalDataSizeWords);


/***********************************************************************/
/**
 * @brief The CRYS_COMMON_CutAndSaveEndOfLliData() function saves the data from end of source
 *        memory, pointed by LLI table, to destination memory, and decreases the LLI table accordingly.
 *
 *        The function executes the following major steps:
 *
 *        1. Starts copy bytes from last byte of last chunk of source LLI table into
 *           last byte of destination memory.
 *        2. Continues copy bytes in reverse order while not completes copying of all amount of data.
 *        3. If last chunk of source or destination data is not enough, the function crosses
 *           to next chunk of LLI table.
 *        4. Decreases the Data size of last updated LLI entry and sets the LAST bit.
 *        5. Exits with the OK code.
 *
 *
 * @param[in] SrcLliTab_ptr - The pointer to the LLI table, containing pointers and sizes of
 *                            chunks of source data. The table need to be aligned and placed
 *                            in SEP SRAM.
 * @param[in] SrcLliTabSize_ptr -   The pointer to buffer, containing th size of the LLI table in words.
 * @param[in] Dest_ptr  -  The destination address for copying the data.
 * @param[in] DataSize  -  The count of bytes to copy.
 *
 * @return CRYSError_t - On success CRYS_OK is returned,
 *                     - CRYS_COMMON_ERROR_IN_SAVING_LLI_DATA_ERROR
 *
 * NOTE: 1. Because the function is intended for internal using, it is presumed that all input parameters
 *          are valid.
 *       2. Assumed, that copied source not may to take more than two last chunks of source memory.
 */
 CRYSError_t  CRYS_COMMON_CutAndSaveEndOfLliData(
                                         uint32_t   *SrcLliTab_ptr,
                                         uint32_t   *SrcLliTabSize_ptr,
                                         uint8_t    *Dst_ptr,
                                         uint32_t    DataSize);

/***********************************************************************/
/**
 * @brief The CRYS_COMMON_CutAndSaveBeginOfLliData() function saves the data from beginning of source
 *        memory, pointed by LLI table, to destination memory, and decreases the LLI table accordingly.
 *
 *        The function executes the following major steps:
 *
 *        1. Starts copy bytes from first byte of first chunk of source LLI table into
 *           destination memory.
 *        2. If first chunk of source is not enough, the function crosses
 *           to next chunk of LLI table.
 *        3. Updates LLI table pointer and size according to copied amount of data.
 *        5. Exits with the OK code.
 *
 * @param[in/out] SrcLliTab_ptr_ptr - The pointer to pointer to the LLI table, containing pointers and
 *                            sizes of the chunks of source data. The table need to be aligned and
 *                            placed in SRAM.
 * @param[in/out] SrcLliTabSize_ptr -   The pointer to buffer, containing th size of the LLI table in words.
 * @param[in] Dest_ptr  -  The destination address for copying the data.
 * @param[in] DataSize  -  The count of bytes to copy.
 *
 * @return - no return value.
 *
 * NOTE: 1. Because the function is intended for internal using, it is presumed that all input parameters
 *          are valid.
 *       2. Assumed, that copied source not may to take more than two first chunks of source memory.
 */
 void  CRYS_COMMON_CutAndSaveBeginOfLliData(
                                         uint32_t  **SrcLliTab_ptr_ptr,
                                         uint32_t   *SrcLliTabSize_ptr,
                                         uint8_t    *Dst_ptr,
                                         uint32_t    DataSize);

/***********************************************************************/
  /**
  * @brief This function converts 32-bit words array with little endian
  *        order of words to bytes array with little endian (LE) order of bytes.
  *
  *    Assuming: no buffers overlapping, in/out pointers and sizes not equall to NULL,
                 the buffer size must be not less, than input data size.
  *
  * @param[out] out8Le - The bytes pointer to output buffer.
  * @param[in] in32Le - The pointer to input 32-bit words buffer.
  * @param[in] sizeInWords - The size in words of input data (sizeWords >= 0).
  *
  * @return CRYSError_t - On success CRYS_OK is returned, on failure a
  *                        value MODULE_* as defined in .
  */
void CRYS_COMMON_ConvertLswMswWordsToLsbMsbBytes(
                    uint8_t  *out8Le,
                    const uint32_t *in32Le,
                    size_t  sizeInWords);


/***********************************************************************/
/**
 * @brief This function converts bytes array with little endian (LE) order of
 *        bytes to 32-bit words array with little endian order of words and bytes.
 *
 *   Assuming:  No owerlapping of buffers; in/out pointers and sizes are not equall to NULL.
 *              If is in-place conversion, then the size must be multiple of 4 bytes.
 * @param[out] out32Le - The 32-bits pointer to output buffer. The buffer size must be
 *                       not less, than input data size.
 * @param[in] in8Le - The pointer to input buffer.
 * @param[in] sizeInBytes - The size in bytes of input data(sizeBytes > 0).
 *
 * @return CRYSError_t - On success CRYS_OK is returned, on failure a
 *                        value MODULE_* as defined in .
 */
void CRYS_COMMON_ConvertLsbMsbBytesToLswMswWords(
                    uint32_t *out32Le,
                    const uint8_t  *in8Le,
                    size_t  sizeInBytes);


/**
 * The function compares value of byte vector to null.
 *
 * @author reuvenl (6/20/2016)
 *
 * @param vect - a pointer to bytes vector.
 * @param sizeBytes - size of the vector.
 *
 * @return uint32_t - if vector's value iz zero, then returns 1, else - 0;
 */
uint32_t  CRYS_COMMON_CheckIsVectorZero(uint8_t *vect, uint32_t sizeBytes);




#ifdef __cplusplus
}
#endif

#endif


