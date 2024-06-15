/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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
///////////////////////////////////////////////////////////////////////////////
//! \addtogroup ddi_media
//! @{
//
// Copyright (c) 2004-2007 SigmaTel, Inc.
//
//! \file sectordef.h
//! \brief Contains constants for different sector sizes and related macros.
//!
//! The definitions in this file should be used exclusively to get the
//! sizes of various types of sectors. When allocating a sector buffer,
//! use either the #SECTOR_BUFFER_ALLOC_SIZE macro or one of the following:
//! - #NOMINAL_DATA_SECTOR_ALLOC_SIZE
//! - #NOMINAL_AUXILIARY_SECTOR_ALLOC_SIZE
///////////////////////////////////////////////////////////////////////////////

#ifndef _SECTORDEF_H
#define _SECTORDEF_H

//! \name Utility macros
//@{
    //! \brief Simple macro to round up an integer division
#define ROUND_UP_DIV(a, b)      (((a) + (b) - 1) / (b))

    //! \brief Macro to round an integer up to a given multiple.
#define ROUND_UP(n, m)          ((ROUND_UP_DIV((n), (m))) * (m))

    //! \brief Macro to compute the number of 32-bit words required to hold \a a bytes.
#define SIZE_IN_WORDS(a)        (ROUND_UP_DIV((a), sizeof(uint32_t)))
//@}

//! \name Cache line definitions
//@{

    //! \brief Buffer alignment and multiple size in bytes required for data cache issues.
#define BUFFER_CACHE_LINE_MULTIPLE     (32)

    //! \brief Buffer alignment and multiple size in bytes required for data cache issues.
#define BUFFER_CACHE_LINE_MULTIPLE_IN_WORDS     (SIZE_IN_WORDS(BUFFER_CACHE_LINE_MULTIPLE))

//@}

//! \name 512 byte page sizes
//@{
    //! \brief  TBD
#define MMC_SECTOR_TOTAL_SIZE                 (528)
    //! \brief  TBD
#define MMC_SECTOR_DATA_SIZE                  (512)
    //! \brief  TBD
#define MMC_SECTOR_REDUNDANT_SIZE             (16)
//@}

//! \name 2K page sizes
//@{
    //! \brief Size in bytes of a 2K NAND page.
#define LARGE_SECTOR_TOTAL_SIZE                 (2112)

    //! \brief Size in bytes of the data area of a 2K NAND page.
#define LARGE_SECTOR_DATA_SIZE                  (2048)

    //! \brief Size in bytes of the redundant area of a 2K NAND sector.
#define LARGE_SECTOR_REDUNDANT_SIZE             (64)

    //! \brief Size in 32-bit words of the redundant area of a 2K NAND sector.
#define LARGE_SECTOR_REDUNDANT_SIZE_IN_WORDS    (SIZE_IN_WORDS(LARGE_SECTOR_REDUNDANT_SIZE))
//@}

//! \name 4K page sizes
//@{
    //! \brief Size in bytes of a 4K NAND page.
#define XL_SECTOR_TOTAL_SIZE                      (4314)

    //! \brief Size in bytes of the data area of a 4K NAND page.
#define XL_SECTOR_DATA_SIZE                       (4096)

    //! \brief Size in words of the data area of a 4K NAND sector.
#define XL_SECTOR_DATA_SIZE_IN_WORDS              (SIZE_IN_WORDS(XL_SECTOR_DATA_SIZE))

    //! \brief Size in bytes of the redundant area of a 4K NAND sector.
#define XL_SECTOR_REDUNDANT_SIZE                  (218)

    //! \brief Size in 32-bit words of the redundant area of a 4K NAND sector.
#define XL_SECTOR_REDUNDANT_SIZE_IN_WORDS         (SIZE_IN_WORDS(XL_SECTOR_REDUNDANT_SIZE))
//@}

//! \name Samsung 4K page sizes
//@{
    //! \brief Size in bytes of a Samsung 4K NAND page.
#define SAMSUNG_XL_SECTOR_TOTAL_SIZE              (4224)

    //! \brief Size in bytes of the redundant area of a Samsung 4K NAND sector.
#define SAMSUNG_XL_SECTOR_REDUNDANT_SIZE          (128)

    //! \brief Size in 32-bit words of the redundant area of a Samsung 4K NAND sector.
#define SAMSUNG_XL_SECTOR_REDUNDANT_SIZE_IN_WORDS (SIZE_IN_WORDS(SAMSUNG_XL_SECTOR_REDUNDANT_SIZE))
//@}

//! \name Toshiba 8K page sizes
//@{
    //! \brief Size in bytes of a Toshiba 8K NAND page.
#define TOSHIBA_8K_SECTOR_TOTAL_SIZE (8568)

    //! \brief Size in bytes of the data area of an 8K NAND page.
#define TOSHIBA_8K_SECTOR_DATA_SIZE (8192)

    //! \brief Size in bytes of the redundant area of an 8K NAND page.
#define TOSHIBA_8K_SECTOR_REDUNDANT_SIZE (376)
//@}

//! \name Samsung 8K page sizes
//@{
    //! \brief Size in bytes of a Samsung 8K NAND page.
#define SAMSUNG_8K_SECTOR_TOTAL_SIZE (8628)

    //! \brief Size in bytes of the data area of an 8K NAND page.
#define SAMSUNG_8K_SECTOR_DATA_SIZE (8192)

    //! \brief Size in bytes of the redundant area of an 8K NAND page.
#define SAMSUNG_8K_SECTOR_REDUNDANT_SIZE (436)
//@}

//! \name Maximum supported page sizes
//!
//! On some systems, the maximum size is 8K. On others, it is set to 4K. The
//! difference is mostly based on how much the system can tolerate wasted memory.
//@{
#if defined(STMP378x) || defined(STMP377x)

        //! \brief Size in bytes of the largest sector type we support.
#define MAX_SECTOR_TOTAL_SIZE                   (SAMSUNG_8K_SECTOR_TOTAL_SIZE)

        //! \brief Size in bytes of the data area of the largest sector type we support.
#define MAX_SECTOR_DATA_SIZE                    (SAMSUNG_8K_SECTOR_DATA_SIZE)

        //! \brief Size in bytes of the redundant area of the largest sector type we support.
#define MAX_SECTOR_REDUNDANT_SIZE               (SAMSUNG_8K_SECTOR_REDUNDANT_SIZE)

#else // defined(STMP378x)

        //! \brief Size in bytes of the largest sector type we support.
#define MAX_SECTOR_TOTAL_SIZE                   (XL_SECTOR_TOTAL_SIZE)

        //! \brief Size in bytes of the data area of the largest sector type we support.
#define MAX_SECTOR_DATA_SIZE                    (XL_SECTOR_DATA_SIZE)

        //! \brief Size in bytes of the redundant area of the largest sector type we support.
#define MAX_SECTOR_REDUNDANT_SIZE               (XL_SECTOR_REDUNDANT_SIZE)

#endif // defined(STMP378x)

    //! \brief Size in 32-bit words of the redundant area of the largest sector type we support.
#define MAX_SECTOR_DATA_SIZE_IN_WORDS           (SIZE_IN_WORDS(MAX_SECTOR_DATA_SIZE))

    //! \brief Size in 32-bit words of the redundant area of the largest sector type we support.
#define MAX_SECTOR_REDUNDANT_SIZE_IN_WORDS      (SIZE_IN_WORDS(MAX_SECTOR_REDUNDANT_SIZE))
//@}

//! \name Auxiliary buffer sizes
//@{

    //! Size in bytes of the auxiliary buffer required by the ECC8 Reed-Solomon 4-bit mode,
    //! used for 2K NAND pages.
#define AUXILIARY_BUFFER_ECC_RS4_SIZE (188)

    //! Size in bytes of the auxiliary buffer required for ECC RS8 on 4K page Nands till BCH 16 on 8K Page Nands.
    //! The size has been rounded up to 500. Tested to ensure room for Samsung 8K Page Nands the Redundant area, Status Bytes and the Parity.
#define AUXILIARY_BUFFER_ECC_RS8_SIZE (500)

    //! \brief The amount of memory allocated for RA
#define REDUNDANT_AREA_BUFFER_ALLOCATION        (AUXILIARY_BUFFER_ECC_RS8_SIZE)
//@}

//! \name Nominal buffer sizes
//!
//! These defines are the sizes of buffers to use when statically allocating a buffer
//! that must be large enough to support any media type.
//@{

    //! \brief Compute the size in bytes of a buffer.
    //!
    //! Rounds up to the nearest 32-byte multiple in order to span a complete cache
    //! line. Note that you still need to align the buffer to the cache line size
    //! (i.e., #BUFFER_CACHE_LINE_MULTIPLE).
#define CACHED_BUFFER_SIZE(a)       (ROUND_UP((a), BUFFER_CACHE_LINE_MULTIPLE))

    //! \brief Compute the size in words of a buffer.
    //!
    //! Rounds up to the nearest 32-byte multiple in order to span a complete cache
    //! line. Note that you still need to align the buffer to the cache line size
    //! (i.e., #BUFFER_CACHE_LINE_MULTIPLE).
#define CACHED_BUFFER_SIZE_IN_WORDS(a)       (SIZE_IN_WORDS(CACHED_BUFFER_SIZE(a)))

    //! \brief
#define SECTOR_BUFFER_ALLOC_SIZE(a)       (CACHED_BUFFER_SIZE_IN_WORDS(a))

    //! \brief Constant to use when allocating a data sector buffer by words.
#define NOMINAL_DATA_SECTOR_ALLOC_SIZE    (SECTOR_BUFFER_ALLOC_SIZE(MAX_SECTOR_DATA_SIZE))

    //! \brief Constant to use when allocating a auxiliary sector buffer by words.
#define NOMINAL_AUXILIARY_SECTOR_ALLOC_SIZE   (SECTOR_BUFFER_ALLOC_SIZE(REDUNDANT_AREA_BUFFER_ALLOCATION))

    //! \brief Constant to use when allocating a data sector buffer by bytes.
#define NOMINAL_DATA_SECTOR_SIZE    (NOMINAL_DATA_SECTOR_ALLOC_SIZE*sizeof(uint32_t))

    //! \brief Constant to use when allocating a auxiliary sector buffer by bytes.
#define NOMINAL_AUXILIARY_SECTOR_SIZE   (NOMINAL_AUXILIARY_SECTOR_ALLOC_SIZE*sizeof(uint32_t))

//@}

#endif // _SECTORDEF_H

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
//! @}
