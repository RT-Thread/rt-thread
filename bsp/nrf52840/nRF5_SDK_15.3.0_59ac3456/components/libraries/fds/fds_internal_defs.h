/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef FDS_INTERNAL_DEFS_H__
#define FDS_INTERNAL_DEFS_H__
#include "sdk_config.h"
#include <stdint.h>
#include <stdbool.h>

#if defined (FDS_THREADS)
    #include "nrf_soc.h"
    #include "app_util_platform.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define FDS_PAGE_TAG_SIZE       (2) // Page tag size, in 4-byte words.
#define FDS_PAGE_TAG_WORD_0     (0) // Offset of the first word in the page tag from the page address.
#define FDS_PAGE_TAG_WORD_1     (1) // Offset of the second word in the page tag from the page address.

// Page tag constants
#define FDS_PAGE_TAG_MAGIC      (0xDEADC0DE)
#define FDS_PAGE_TAG_SWAP       (0xF11E01FF)
#define FDS_PAGE_TAG_DATA       (0xF11E01FE)

#define FDS_ERASED_WORD         (0xFFFFFFFF)

#define FDS_OFFSET_TL           (0) // Offset of TL from the record base address, in 4-byte words.
#define FDS_OFFSET_IC           (1) // Offset of IC from the record base address, in 4-byte words.
#define FDS_OFFSET_ID           (2) // Offset of ID from the record base address, in 4-byte words.
#define FDS_OFFSET_DATA         (3) // Offset of the data from the record base address, in 4-byte words.

#define FDS_HEADER_SIZE_TL      (1) // Size of the TL part of the header, in 4-byte words.
#define FDS_HEADER_SIZE_IC      (1) // Size of the IC part of the header, in 4-byte words.
#define FDS_HEADER_SIZE_ID      (1) // Size of the record ID in the header, in 4-byte words.
#define FDS_HEADER_SIZE         (3) // Size of the whole header, in 4-byte words.

#define FDS_OP_EXECUTING        (NRF_SUCCESS)
#define FDS_OP_COMPLETED        (0x1D1D)

#define NRF_FSTORAGE_NVMC       1
#define NRF_FSTORAGE_SD         2

// The size of a physical page, in 4-byte words.
#if defined(NRF51)
    #define FDS_PHY_PAGE_SIZE   (256)
#else
    #define FDS_PHY_PAGE_SIZE   (1024)
#endif

// The number of physical pages to be used. This value is configured indirectly.
#define FDS_PHY_PAGES               ((FDS_VIRTUAL_PAGES * FDS_VIRTUAL_PAGE_SIZE) / FDS_PHY_PAGE_SIZE)

// The number of physical pages at the end of the flash that are reserved by other modules.
#define FDS_PHY_PAGES_RESERVED      ((FDS_VIRTUAL_PAGES_RESERVED * FDS_VIRTUAL_PAGE_SIZE) / FDS_PHY_PAGE_SIZE)

// The size of a virtual page, in number of physical pages.
#define FDS_PHY_PAGES_IN_VPAGE      (FDS_VIRTUAL_PAGE_SIZE / FDS_PHY_PAGE_SIZE)

// The number of pages available to store data; which is the total minus one (the swap).
#define FDS_DATA_PAGES              (FDS_VIRTUAL_PAGES - 1)

 // Just a shorter name for the size, in words, of a virtual page.
#define FDS_PAGE_SIZE               (FDS_VIRTUAL_PAGE_SIZE)

#if (FDS_VIRTUAL_PAGE_SIZE % FDS_PHY_PAGE_SIZE != 0)
    #error "FDS_VIRTUAL_PAGE_SIZE must be a multiple of the size of a physical page."
#endif

#if (FDS_VIRTUAL_PAGES < 2)
    #error "FDS requires at least two virtual pages."
#endif


// Page types.
typedef enum
{
    FDS_PAGE_DATA,      // Page is ready for storage.
    FDS_PAGE_SWAP,      // Page is reserved for garbage collection.
    FDS_PAGE_ERASED,    // Page is erased.
    FDS_PAGE_UNDEFINED, // Undefined page type.
} fds_page_type_t;


typedef enum
{
    FDS_HEADER_VALID,   // Valid header.
    FDS_HEADER_DIRTY,   // Header is incomplete, or record has been deleted.
    FDS_HEADER_CORRUPT  // Header contains corrupt information, not related to CRC.
} fds_header_status_t;


typedef struct
{
    fds_page_type_t         page_type;      // The page type.
    uint32_t        const * p_addr;         // The address of the page.
    uint16_t                write_offset;   // The page write offset, in 4-byte words.
    uint16_t                words_reserved; // The amount of words reserved.
    uint32_t volatile       records_open;   // The number of open records.
    bool                    can_gc;         // Indicates that there are some records that have been deleted.
} fds_page_t;


typedef struct
{
    uint32_t const * p_addr;
    uint16_t         write_offset;
} fds_swap_page_t;


// FDS op-codes.
typedef enum
{
    FDS_OP_NONE,
    FDS_OP_INIT,        // Initialize the module.
    FDS_OP_WRITE,       // Write a record to flash.
    FDS_OP_UPDATE,      // Update a record.
    FDS_OP_DEL_RECORD,  // Delete a record.
    FDS_OP_DEL_FILE,    // Delete a file.
    FDS_OP_GC           // Run garbage collection.
} fds_op_code_t;


typedef enum
{
    FDS_OP_INIT_TAG_SWAP,
    FDS_OP_INIT_TAG_DATA,
    FDS_OP_INIT_ERASE_SWAP,
    FDS_OP_INIT_PROMOTE_SWAP,
} fds_init_step_t;


typedef enum
{
    FDS_OP_WRITE_HEADER_BEGIN,      // Write the record key and length.
    FDS_OP_WRITE_HEADER_FINALIZE,   // Write the file ID and CRC.
    FDS_OP_WRITE_RECORD_ID,         // Write the record ID.
    FDS_OP_WRITE_DATA,              // Write the record data.
    FDS_OP_WRITE_FIND_RECORD,
    FDS_OP_WRITE_FLAG_DIRTY,        // Flag a record as dirty (as part of an update operation).
    FDS_OP_WRITE_DONE,
} fds_write_step_t;


typedef enum
{
    FDS_OP_DEL_RECORD_FLAG_DIRTY,   // Flag a record as dirty.
    FDS_OP_DEL_FILE_FLAG_DIRTY,     // Flag multiple records as dirty.
    FDS_OP_DEL_DONE,
} fds_delete_step_t;


#if defined(__CC_ARM)
    #pragma push
    #pragma anon_unions
#elif defined(__ICCARM__)
    #pragma language=extended
#elif defined(__GNUC__)
    // anonymous unions are enabled by default
#endif

typedef struct
{
    fds_op_code_t op_code;                      // The opcode for the operation.
    union
    {
        struct
        {
            fds_init_step_t   step;               // The current step the operation is at.
        } init;
        struct
        {
            fds_header_t      header;
            void const      * p_data;
            uint16_t          page;             // The page the flash space for this command was reserved.
            fds_write_step_t  step;             // The current step the operation is at.
            uint32_t          record_to_delete; // The record to delete in case this is an update.
        } write;
        struct
        {
            fds_delete_step_t step;
            uint16_t          file_id;
            uint16_t          record_key;
            uint32_t          record_to_delete;
        } del;
    };
} fds_op_t;

#if defined(__CC_ARM)
    #pragma pop
#elif defined(__ICCARM__)
    // leave anonymous unions enabled
#elif defined(__GNUC__)
    // anonymous unions are enabled by default
#endif


enum
{
    PAGE_ERASED     = 0x1,  // One or more erased pages found.
    PAGE_DATA       = 0x2,  // One or more data pages found.
    PAGE_SWAP_CLEAN = 0x4,  // A clean (empty) swap page was found.
    PAGE_SWAP_DIRTY = 0x8,  // A dirty (non-empty) swap page was found.
};


typedef enum
{
    // No erased pages or FDS pages found.
    // This is a fatal error.
    NO_PAGES,

    // The filesystem can not be garbage collected.
    // This is a fatal error.
    NO_SWAP             = (PAGE_DATA),

    // Perform a fresh installation.
    FRESH_INSTALL       = (PAGE_ERASED),

    // Tag an erased page as swap.
    TAG_SWAP            = (PAGE_ERASED | PAGE_DATA),

    // Tag all erased pages as data.
    TAG_DATA            = (PAGE_ERASED | PAGE_SWAP_CLEAN),

    // Tag all remaining erased pages as data.
    TAG_DATA_INST       = (PAGE_ERASED | PAGE_DATA | PAGE_SWAP_CLEAN),

    // The swap is dirty, likely because the device powered off during GC.
    // Because there is also an erased page, assume that that page has been garbage collected.
    // Hence, tag the swap as data (promote), an erased page as swap and remaining pages as data.
    PROMOTE_SWAP        = (PAGE_ERASED | PAGE_SWAP_DIRTY),

    // Tag the swap as data (promote), an erased page as swap and remaining pages as data.
    PROMOTE_SWAP_INST   = (PAGE_ERASED | PAGE_DATA | PAGE_SWAP_DIRTY),

    // The swap is dirty (written) and there are no erased pages. It is likely that the device
    // powered off during GC. It is safe to discard (erase) the swap, since data that was
    // swapped out still lies in one of the valid pages.
    DISCARD_SWAP        = (PAGE_DATA  | PAGE_SWAP_DIRTY),

    // Do nothing.
    ALREADY_INSTALLED   = (PAGE_DATA  | PAGE_SWAP_CLEAN),

} fds_init_opts_t;


typedef enum
{
    GC_BEGIN,               // Begin GC.
    GC_NEXT_PAGE,           // GC a page.
    GC_FIND_NEXT_RECORD,    // Find a valid record to copy.
    GC_COPY_RECORD,         // Copy a valid record to swap.
    GC_ERASE_PAGE,          // Erase the page being garbage collected.
    GC_DISCARD_SWAP,        // Erase (discard) the swap page.
    GC_PROMOTE_SWAP,        // Tag the swap as valid.
    GC_TAG_NEW_SWAP         // Tag a freshly erased (GCed) page as swap.
} fds_gc_state_t;


// Holds garbage collection status and related data.
typedef struct
{
    fds_gc_state_t   state;                      // The current GC step.
    uint16_t         cur_page;                   // The current page being garbage collected.
    uint32_t const * p_record_src;               // The current record being copied to swap.
    uint16_t         run_count;                  // Total number of times GC was run.
    bool             do_gc_page[FDS_DATA_PAGES]; // Controls which pages to garbage collect.
    bool             resume;                     // Whether or not GC should be resumed.
} fds_gc_data_t;


// Macros to enable and disable application interrupts.
#if defined (FDS_THREADS)

    #define CRITICAL_SECTION_ENTER()    CRITICAL_REGION_ENTER()
    #define CRITICAL_SECTION_EXIT()     CRITICAL_REGION_EXIT()

#else

    #define CRITICAL_SECTION_ENTER()
    #define CRITICAL_SECTION_EXIT()

#endif


#ifdef __cplusplus
}
#endif

#endif // FDS_INTERNAL_DEFS_H__
