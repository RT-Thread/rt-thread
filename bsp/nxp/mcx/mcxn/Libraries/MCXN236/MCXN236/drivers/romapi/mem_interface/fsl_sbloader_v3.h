/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SBLOADER_V3_H_
#define FSL_SBLOADER_V3_H_

#include <stdint.h>

#include "fsl_nboot_hal.h"

/*! @addtogroup sbloader */
/*! @{ */

/*******************************************************************************
 * Definitions
 *****************************************************************************/

/*!
 * @brief Defines the number of bytes in a cipher block (chunk). This is dictated by
 * the encryption algorithm.
 */
#define SB3_BYTES_PER_CHUNK 16

typedef uint8_t chunk_v3_t[SB3_BYTES_PER_CHUNK];

typedef struct _ldr_buf ldr_buf_t;

struct _ldr_buf
{
    chunk_v3_t data;
    uint32_t fillPosition;
};

/*! @brief Provides forward reference to the loader context definition. */
typedef struct _ldr_Context_v3 ldr_Context_v3_t;

/*! @brief Function pointer definition for all loader action functions. */
typedef status_t (*pLdrFnc_v3_t)(ldr_Context_v3_t *content);

/*! @brief sb3 section definitions */
/*! @brief section type */
typedef enum _sectionType
{
    kSectionNone       = 0, /*!< end or invalid */
    kSectionDataRange  = 1,
    kSectionDiffUpdate = 2,
    kSectionDDRConfig  = 3,
    kSectionRegister   = 4,
} section_type_t;

#define SB3_DATA_RANGE_HEADER_FLAGS_ERASE_MASK (0x1u) /*!< bit 0 */
#define SB3_DATA_RANGE_HEADER_FLAGS_LOAD_MASK  (0x2u) /*!< bit 1 */

/*! @brief section data range structure */
typedef struct range_header
{
    uint32_t tag;
    uint32_t startAddress;
    uint32_t length;
    uint32_t cmd;
} sb3_data_range_header_t;

typedef struct range_header_expansion
{
    uint32_t memoryId;
    uint32_t pad0;
    uint32_t pad1;
    uint32_t pad2;
} sb3_data_range_expansion_t;

typedef struct copy_memory_expansion
{
    uint32_t destAddr;
    uint32_t memoryIdFrom;
    uint32_t memoryIdTo;
    uint32_t pad;
} sb3_copy_memory_expansion_t;

typedef struct copy
{
    sb3_data_range_header_t header;
    sb3_copy_memory_expansion_t expansion;
} sb3_copy_memory_t;

typedef struct load_keyblob
{
    uint32_t tag;
    uint16_t offset;
    uint16_t keyWrapId;
    uint32_t length;
    uint32_t cmd;
} sb3_load_keyblob_t;

typedef struct fill_memory_expansion
{
    uint32_t pattern; /*!< word to be used as pattern */
    uint32_t pad0;
    uint32_t pad1;
    uint32_t pad2;
} sb3_fill_memory_expansion_t;

typedef struct fill_memory
{
    sb3_data_range_header_t header;
    sb3_fill_memory_expansion_t arg;
} sb3_fill_memory_t;

typedef struct config_memory
{
    uint32_t tag;
    uint32_t memoryId;
    uint32_t address; /*!< address of config blob */
    uint32_t cmd;
} sb3_config_memory_t;

enum
{
    kFwVerChk_Id_none      = 0,
    kFwVerChk_Id_nonsecure = 1,
    kFwVerChk_Id_secure    = 2,
};

typedef struct fw_ver_check
{
    uint32_t tag;
    uint32_t version;
    uint32_t id;
    uint32_t cmd;
} sb3_fw_ver_check_t;

/*! @brief sb3 DATA section header format */
typedef struct section_header
{
    uint32_t sectionUid;
    uint32_t sectionType;
    uint32_t length;
    uint32_t _pad;
} sb3_section_header_t;

/*! @brief loader command enum */
typedef enum _loader_command_sb3
{
    kSB3_CmdInvalid         = 0,
    kSB3_CmdErase           = 1,
    kSB3_CmdLoad            = 2,
    kSB3_CmdExecute         = 3,
    kSB3_CmdCall            = 4,
    kSB3_CmdProgramFuse     = 5,
    kSB3_CmdProgramIFR      = 6,
    kSB3_CmdLoadCmac        = 7,
    kSB3_CmdCopy            = 8,
    kSB3_CmdLoadHashLocking = 9,
    kSB3_CmdLoadKeyBlob     = 10,
    kSB3_CmdConfigMem       = 11,
    kSB3_CmdFillMem         = 12,
    kSB3_CmdFwVerCheck      = 13,
} sb3_cmd_t;

/*! @brief The all of the allowed command */
#define SBLOADER_V3_CMD_SET_ALL                                                                                      \
    ((1u << kSB3_CmdErase) | (1u << kSB3_CmdLoad) | (1u << kSB3_CmdExecute) | (1u << kSB3_CmdCall) |                 \
     (1u << kSB3_CmdProgramFuse) | (1u << kSB3_CmdProgramIFR) | (1u << kSB3_CmdCopy) | (1u << kSB3_CmdLoadKeyBlob) | \
     (1u << kSB3_CmdConfigMem) | (1u << kSB3_CmdFillMem) | (1u << kSB3_CmdFwVerCheck))
/*! @brief The allowed command set in ISP mode */
#define SBLOADER_V3_CMD_SET_IN_ISP_MODE                                                                            \
    ((1u << kSB3_CmdErase) | (1u << kSB3_CmdLoad) | (1u << kSB3_CmdExecute) | (1u << kSB3_CmdProgramFuse) |        \
     (1u << kSB3_CmdProgramIFR) | (1u << kSB3_CmdCopy) | (1u << kSB3_CmdLoadKeyBlob) | (1u << kSB3_CmdConfigMem) | \
     (1u << kSB3_CmdFillMem) | (1u << kSB3_CmdFwVerCheck))
/*! @brief The allowed command set in recovery mode */
#define SBLOADER_V3_CMD_SET_IN_REC_MODE                                                                            \
    ((1u << kSB3_CmdErase) | (1u << kSB3_CmdLoad) | (1u << kSB3_CmdExecute) | (1u << kSB3_CmdProgramFuse) |        \
     (1u << kSB3_CmdProgramIFR) | (1u << kSB3_CmdCopy) | (1u << kSB3_CmdLoadKeyBlob) | (1u << kSB3_CmdConfigMem) | \
     (1u << kSB3_CmdFillMem) | (1u << kSB3_CmdFwVerCheck))

#define SB3_DATA_BUFFER_SIZE_IN_BYTE (MAX(128, NBOOT_KEY_BLOB_SIZE_IN_BYTE_MAX))

/*! @brief Memory region definition. */
typedef struct
{
    uint32_t address;
    uint32_t length;
} kb_region_t;

/*!
 * @brief Details of the operation to be performed by the ROM.
 *
 * The #kRomAuthenticateImage operation requires the entire signed image to be
 * available to the application.
 */
typedef enum
{
    kRomAuthenticateImage = 1, /*!< Authenticate a signed image. */
    kRomLoadImage         = 2, /*!< Load SB file. */
    kRomOperationCount    = 3,
} kb_operation_t;

typedef struct
{
    uint32_t profile;
    uint32_t minBuildNumber;
    uint32_t overrideSBBootSectionID;
    uint32_t *userSBKEK;
    uint32_t regionCount;
    const kb_region_t *regions;
} kb_load_sb_t;

typedef struct
{
    uint32_t profile;
    uint32_t minBuildNumber;
    uint32_t maxImageLength;
    uint32_t *userRHK;
} kb_authenticate_t;

typedef struct
{
    uint32_t version; /*!< Should be set to #kKbootApiVersion. */
    uint8_t *buffer;  /*!< Caller-provided buffer used by Kboot. */
    uint32_t bufferLength;
    kb_operation_t op;
    union
    {
        kb_authenticate_t authenticate; /*!< Settings for #kKbootAuthenticate operation.*/
        kb_load_sb_t loadSB;            /*!< Settings for #kKbootLoadSB operation.*/
    };
} kb_options_t;

/*! @brief Loader context definition. */
struct _ldr_Context_v3
{
    pLdrFnc_v3_t Action;        /*!< pointer to loader action function */
    uint32_t block_size;        /*!< size of each block in bytes */
    uint32_t block_data_size;   /*!< data size in bytes (NBOOT_SB3_CHUNK_SIZE_IN_BYTES) */
    uint32_t block_data_total;  /*!< data max size in bytes (block_size * data_size */
    uint32_t block_buffer_size; /*!< block0 and block size */
    uint32_t block_buffer_position;
    uint8_t block_buffer[MAX(NBOOT_SB3_MANIFEST_MAX_SIZE_IN_BYTES,
                             NBOOT_SB3_BLOCK_MAX_SIZE_IN_BYTES)]; /*! will be used for both block0 and blockx */
    uint32_t processedBlocks;

    uint8_t data_block_offset; /*! data block offset in a block. */
    bool in_data_block;        /*!< in progress of handling a data block within a block */
    uint8_t *data_block;
    uint32_t data_block_position;

    bool in_data_section; /*!< in progress of handling a data section within a data block */
    uint32_t data_section_handled;
    sb3_section_header_t data_section_header;

    bool in_data_range; /*!< in progress of handling a data range within a data section */
    uint32_t data_range_handled;
    uint32_t data_range_gap;
    sb3_data_range_header_t data_range_header;
    bool has_data_range_expansion;
    sb3_data_range_expansion_t data_range_expansion;

    uint32_t commandSet; /*!< support command set during sb file handling */

    uint32_t data_position;
    uint8_t data_buffer[SB3_DATA_BUFFER_SIZE_IN_BYTE]; /*!< temporary data buffer */

    kb_options_t fromAPI; /*!< options from ROM API */
};

/*! @} */

#endif /* FSL_SBLOADER_V3_H_ */
