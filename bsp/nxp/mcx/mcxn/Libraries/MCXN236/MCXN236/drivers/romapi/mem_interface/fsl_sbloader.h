/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_SBLOADER_H_
#define FSL_SBLOADER_H_

#include "fsl_flash.h"
#include "fsl_flexspi_nor_flash.h"
#include "fsl_sbloader_v3.h"
#include "fsl_common.h"
/*!
 * @addtogroup sbloader
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Determines the version of SB loader implementation (1: sb1.0; 2: sb2.0; 3.1: sb3.1) */
#define SB_FILE_MAJOR_VERSION (3)
#define SB_FILE_MINOR_VERSION (1)

/*! @brief Bootloader status group numbers */
#define kStatusGroup_SBLoader (101U)

/*! @brief Contiguous RAM region count */
#define RAM_REGION_COUNT (2U)

/*! @brief Contiguous FLASH region count */
#define FLASH_REGION_COUNT (1U)

/*! @brief Contiguous FFR region count */
#define FFR_REGION_COUNT (1U)

/*! @brief Memory Interface count */
#define MEM_INTERFACE_COUNT (4U)

/*! @brief Contiguous FLEXSPINOR meomry count */
#define FLEXSPINOR_REGION_COUNT (1U)

/*! @brief SB loader status codes.*/
enum
{
    kStatusRomLdrSectionOverrun  = MAKE_STATUS(kStatusGroup_SBLoader, 0),
    kStatusRomLdrSignature       = MAKE_STATUS(kStatusGroup_SBLoader, 1),
    kStatusRomLdrSectionLength   = MAKE_STATUS(kStatusGroup_SBLoader, 2),
    kStatusRomLdrUnencryptedOnly = MAKE_STATUS(kStatusGroup_SBLoader, 3),
    kStatusRomLdrEOFReached      = MAKE_STATUS(kStatusGroup_SBLoader, 4),
    kStatusRomLdrChecksum        = MAKE_STATUS(kStatusGroup_SBLoader, 5),
    kStatusRomLdrCrc32Error      = MAKE_STATUS(kStatusGroup_SBLoader, 6),
    kStatusRomLdrUnknownCommand  = MAKE_STATUS(kStatusGroup_SBLoader, 7),
    kStatusRomLdrIdNotFound      = MAKE_STATUS(kStatusGroup_SBLoader, 8),
    kStatusRomLdrDataUnderrun    = MAKE_STATUS(kStatusGroup_SBLoader, 9),
    kStatusRomLdrJumpReturned    = MAKE_STATUS(kStatusGroup_SBLoader, 10),
    kStatusRomLdrCallFailed      = MAKE_STATUS(kStatusGroup_SBLoader, 11),
    kStatusRomLdrKeyNotFound     = MAKE_STATUS(kStatusGroup_SBLoader, 12),
    kStatusRomLdrSecureOnly      = MAKE_STATUS(kStatusGroup_SBLoader, 13),
    kStatusRomLdrResetReturned   = MAKE_STATUS(kStatusGroup_SBLoader, 14),

    kStatusRomLdrRollbackBlocked        = MAKE_STATUS(kStatusGroup_SBLoader, 15),
    kStatusRomLdrInvalidSectionMacCount = MAKE_STATUS(kStatusGroup_SBLoader, 16),
    kStatusRomLdrUnexpectedCommand      = MAKE_STATUS(kStatusGroup_SBLoader, 17),
    kStatusRomLdrBadSBKEK               = MAKE_STATUS(kStatusGroup_SBLoader, 18),
    kStatusRomLdrPendingJumpCommand     = MAKE_STATUS(kStatusGroup_SBLoader, 19),
};

/*!
 * @brief Defines the number of bytes in a cipher block (chunk). This is dictated by
 * the encryption algorithm.
 */
#define BYTES_PER_CHUNK 16

#define SB_SECTION_COUNT_MAX 8

/*! @brief Boot image signature in 32-bit little-endian format "PMTS" */
#define BOOT_SIGNATURE 0x504d5453

/*! @brief Boot image signature in 32-bit little-endian format "ltgs" */
#define BOOT_SIGNATURE2 0x6c746773

/*! @brief These define file header flags */
#define FFLG_DISPLAY_PROGRESS 0x0001

/*! @brief These define section header flags */
#define SFLG_SECTION_BOOTABLE 0x0001

/*! @brief These define boot command flags */
#define CFLG_LAST_TAG 0x01

/*! @brief ROM_ERASE_CMD flags */
#define ROM_ERASE_ALL_MASK          0x01
#define ROM_ERASE_ALL_UNSECURE_MASK 0x02

/*! @brief ROM_JUMP_CMD flags */
#define ROM_JUMP_SP_MASK 0x02

/*! @brief Memory device id shift at sb command flags */
#define ROM_MEM_DEVICE_ID_SHIFT 0x8

/*! @brief Memory device id mask */
#define ROM_MEM_DEVICE_ID_MASK 0xff00

/*! @brief Memory group id shift at sb command flags */
#define ROM_MEM_GROUP_ID_SHIFT 0x4

/*! @brief Memory group id flags mask */
#define ROM_MEM_GROUP_ID_MASK 0xf0

/*! @brief ROM_PROG_CMD flags */
#define ROM_PROG_8BYTE_MASK 0x01

/*! @brief These define the boot command tags */
#define ROM_NOP_CMD        0x00
#define ROM_TAG_CMD        0x01
#define ROM_LOAD_CMD       0x02
#define ROM_FILL_CMD       0x03
#define ROM_JUMP_CMD       0x04
#define ROM_CALL_CMD       0x05
#define ROM_MODE_CMD       0x06
#define ROM_ERASE_CMD      0x07
#define ROM_RESET_CMD      0x08
#define ROM_MEM_ENABLE_CMD 0x09
#define ROM_PROG_CMD       0x0a
#define ROM_FW_VER_CHK     0x0b

#if SB_FILE_MAJOR_VERSION == 2
#define SBLOADER_CMD_SET_IN_ISP_MODE (SBLOADER_V2_CMD_SET_IN_ISP_MODE)
#define SBLOADER_CMD_SET_IN_REC_MODE (SBLOADER_V2_CMD_SET_IN_REC_MODE)
#elif SB_FILE_MAJOR_VERSION == 3
#define SBLOADER_CMD_SET_IN_ISP_MODE (SBLOADER_V3_CMD_SET_IN_ISP_MODE)
#define SBLOADER_CMD_SET_IN_REC_MODE (SBLOADER_V3_CMD_SET_IN_REC_MODE)
#endif

/*! @brief Plugin return codes */
#define ROM_BOOT_SECTION_ID 1
#define ROM_BOOT_IMAGE_ID   2

enum _fw_version_check_option
{
    kRomLdr_FwCheckOption_SecureVersion    = 0x0U,
    kRomLdr_FwCheckOption_NonSecureVersion = 0x1U,
};

typedef uint8_t chunk_t[BYTES_PER_CHUNK];

/*! @brief Boot command definition */
typedef struct _boot_cmd
{
    uint8_t checksum; /*!< 8-bit checksum over command chunk */
    uint8_t tag;      /*!< command tag (identifier) */
    uint16_t flags;   /*!< command flags (modifier) */
    uint32_t address; /*!< address argument */
    uint32_t count;   /*!< count argument */
    uint32_t data;    /*!< data argument */
} boot_cmd_t;

/*! @brief Definition for boot image file header chunk 1 */
typedef struct _boot_hdr1
{
    uint32_t hash;       /*!< last 32-bits of SHA-1 hash */
    uint32_t signature;  /*!< must equal "STMP" */
    uint8_t major;       /*!< major file format version */
    uint8_t minor;       /*!< minor file format version */
    uint16_t fileFlags;  /*!< global file flags */
    uint32_t fileChunks; /*!< total chunks in the file */
} boot_hdr1_t;

/*! @brief Definition for boot image file header chunk 2 */
typedef struct _boot_hdr2
{
    uint32_t bootOffset; /*!< chunk offset to the first boot section */
    uint32_t bootSectID; /*!< section ID of the first boot section */
    uint16_t keyCount;   /*!< number of keys in the key dictionary */
    uint16_t keyOffset;  /*!< chunk offset to the key dictionary */
    uint16_t hdrChunks;  /*!< number of chunks in the header */
    uint16_t sectCount;  /*!< number of sections in the image */
} boot_hdr2_t;

/*! @brief Provides forward reference to the loader context definition. */
typedef struct _ldr_Context ldr_Context_t;

/*! @brief Function pointer definition for all loader action functions. */
typedef status_t (*pLdrFnc_t)(ldr_Context_t *context);

/*! @brief Jump command function pointer definition. */
typedef status_t (*pJumpFnc_t)(uint32_t parameter);

/*! @brief Call command function pointer definition. */
typedef status_t (*pCallFnc_t)(uint32_t parameter, uint32_t *func);

/*! @brief State information for the CRC32 algorithm. */
typedef struct Crc32Data
{
    uint32_t currentCrc;   /*!< Current CRC value. */
    uint32_t byteCountCrc; /*!< Number of bytes processed. */
} crc32_data_t;

/*! @brief Loader context definition. */
struct _ldr_Context
{
    pLdrFnc_t Action;        /*!<  pointer to loader action function */
    uint32_t fileChunks;     /*!<  chunks remaining in file */
    uint32_t sectChunks;     /*!<  chunks remaining in section */
    uint32_t bootSectChunks; /*!<  number of chunks we need to complete the boot section */
    uint32_t receivedChunks; /*!<  number of chunks we need to complete the boot section */
    uint16_t fileFlags;      /*!<  file header flags */
    uint16_t keyCount;       /*!<  number of keys in the key dictionary */
    uint32_t objectID;       /*!<  ID of the current boot section or image */
    crc32_data_t crc32;      /*!<  crc calculated over load command payload */
    uint8_t *src;            /*!<  source buffer address */
    chunk_t initVector;      /*!<  decryption initialization vector */
    chunk_t dek;             /*!<  chunk size DEK if the image is encrypted */
    chunk_t scratchPad;      /*!<  chunk size scratch pad area */
    boot_cmd_t bootCmd;      /*!<  current boot command */
    uint32_t skipCount;      /*!<  Number of chunks to skip */
    bool skipToEnd;          /*!<  true if skipping to end of file */

    /* extended for SB 2.0*/
    uint32_t nonce[4];
    uint32_t keyBlobBlock;
    uint32_t keyBlobBlockCount;
    uint8_t *keyBlobBuffer;
    uint32_t offsetSignatureBytes; /*!< offset to signagure block header in bytesn */
    uint8_t *headerBuffer;
};

typedef struct soc_memory_map_struct
{
    struct
    {
        uint32_t start;
        uint32_t end;
    } ramRegions[RAM_REGION_COUNT];
    struct
    {
        uint32_t start;
        uint32_t end;
    } flashRegions[FLASH_REGION_COUNT];
    struct
    {
        uint32_t start;
        uint32_t end;
    } ffrRegions[FFR_REGION_COUNT];
    struct
    {
        uint32_t start;
        uint32_t end;
    } flexspiNorRegions[FLEXSPINOR_REGION_COUNT];
} soc_mem_regions_t;

typedef struct arena_context
{
    uint32_t start;
    uint32_t end;
    uint32_t nextAddr;
} arena_context_t;

/*! @brief Memory region information table */
typedef struct mem_region
{
    uint32_t start;
    uint32_t end;
} mem_region_t;

/*! @brief Memory Attribute Structure */
typedef struct memory_attribute_struct
{
    uint32_t memId;
    uint32_t regionCount;
    mem_region_t *memRegions;
    void *context;
} mem_attribute_t;

/*! @brief Memory context structure */
typedef struct memory_context_struct
{
    status_t (*flush)(mem_attribute_t *attr);
    mem_attribute_t *attr;
} mem_context_t;

/*! @brief Memory region interface structure */
typedef struct api_memory_region_interface
{
    status_t (*init)(mem_attribute_t *attr);
#if ROM_API_HAS_FEATURE_MEM_READ
    status_t (*read)(mem_attribute_t *attr, uint32_t addr, uint32_t leth, uint8_t *buf);
#endif
    status_t (*write)(mem_attribute_t *attr, uint32_t addr, uint32_t len, const uint8_t *buf);
    status_t (*fill)(mem_attribute_t *attr, uint32_t addr, uint32_t len, uint32_t pattern);
    status_t (*flush)(mem_attribute_t *attr);
    status_t (*erase)(mem_attribute_t *attr, uint32_t addr, uint32_t len);
    status_t (*config)(mem_attribute_t *attr, uint32_t *buf);
    status_t (*erase_all)(mem_attribute_t *attr);
    status_t (*alloc_ctx)(arena_context_t *ctx, mem_attribute_t *attr, void *miscParams);
} api_memory_region_interface_t;

/*! @brief Memory entry data structure */
typedef struct memory_map_entry
{
    mem_attribute_t *memoryAttribute;
    const api_memory_region_interface_t *memoryInterface;
} api_memory_map_entry_t;

/*! @brief The API context structure */
typedef struct api_core_context
{
    soc_mem_regions_t memRegions;
    arena_context_t arenaCtx;
    flash_config_t flashConfig;
    flexspi_nor_config_t flexspinorCfg;
    mem_context_t memCtx;
    ldr_Context_v3_t *sbloaderCtx;
    nboot_context_t *nbootCtx;
    uint8_t *sharedBuf;
    api_memory_map_entry_t memEntries[MEM_INTERFACE_COUNT];
} api_core_context_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @brief Perform the Sbloader runtime environment initialization
 * This API is used for initializing the sbloader state machine before calling
 * the api_sbloader_pump. This API should be called after the iap_api_init API.
 *
 * @param ctx Pointer to IAP API core context structure.
 *
 * @retval #kStatus_Success Api was executed succesfuly.
 */
status_t Sbloader_Init(api_core_context_t *ctx);

/*!
 * @brief Handle the SB data stream
 * This API is used for handling the secure binary(SB3.1 format) data stream,
 * which is used for image update, lifecycle advancing, etc.
 * This API should be called after the iap_api_init and api_sbloader_init APIs.

 * @param ctx Pointer to IAP API core context structure.
 * @param data Pointer to source data that is the sb file buffer data.
 * @param length The size of the process buffer data.
 *
 * @retval #kStatus_Success Api was executed succesfuly.
 * @retval #kStatus_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_Fail API execution failed.
 */
status_t Sbloader_Pump(api_core_context_t *ctx, uint8_t *data, uint32_t length);

/*!
 * @brief Finish the sbloader handling
 * The API is used for finalizing the sbloader operations.
 *
 * @param ctx Pointer to IAP API core context structure.
 *
 * @retval #kStatus_Success Api was executed succesfuly.
 */
status_t Sbloader_Finalize(api_core_context_t *ctx);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_SBLOADER_H_ */
