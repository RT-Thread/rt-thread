/*
 * Copyright (c) 2020-2021, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_IAP_KBP_H_
#define _FSL_IAP_KBP_H_

#include "fsl_common.h"

/*!
 * @addtogroup kb_driver
 * @{
 */
/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief ROM API status group number */
#define kStatusGroup_RomApi (108U)

/*! @brief ROM API status codes. */
enum
{
    kStatus_RomApiExecuteCompleted = kStatus_Success, /*!< ROM successfully process the whole sb file/boot image.*/
    kStatus_RomApiNeedMoreData =
        MAKE_STATUS(kStatusGroup_RomApi, 1), /*!< ROM needs more data to continue processing the boot image.*/
    kStatus_RomApiBufferSizeNotEnough =
        MAKE_STATUS(kStatusGroup_RomApi,
                    2), /*!< The user buffer is not enough for use by Kboot during execution of the operation.*/
    kStatus_RomApiInvalidBuffer =
        MAKE_STATUS(kStatusGroup_RomApi, 3), /*!< The user buffer is not ok for sbloader or authentication.*/
};

/*!
 *  @brief Details of the operation to be performed by the ROM.
 *
 * The #kRomAuthenticateImage operation requires the entire signed image to be
 * available to the application.
 */
typedef enum _kb_operation
{
    kRomAuthenticateImage = 1, /*!< Authenticate a signed image.*/
    kRomLoadImage         = 2, /*!< Load SB file.*/
    kRomOperationCount    = 3,
} kb_operation_t;

/*!
 * @brief Security constraint flags, Security profile flags.
 */
enum _kb_security_profile
{
    kKbootMinRSA4096 = (1 << 16),
};

/*!
 * @brief Memory region definition.
 */
typedef struct _kb_region
{
    uint32_t address;
    uint32_t length;
} kb_region_t;

/*!
 * @brief User-provided options passed into kb_init().
 *
 * The buffer field is a pointer to memory provided by the caller for use by
 * Kboot during execution of the operation. Minimum size is the size of each
 * certificate in the chain plus 432 bytes additional per certificate.
 *
 * The profile field is a mask that specifies which features are required in
 * the SB file or image being processed. This includes the minimum AES and RSA
 * key sizes. See the _kb_security_profile enum for profile mask constants.
 * The image being loaded or authenticated must match the profile or an error will
 * be returned.
 *
 * minBuildNumber is an optional field that can be used to prevent version
 * rollback. The API will check the build number of the image, and if it is less
 * than minBuildNumber will fail with an error.
 *
 * maxImageLength is used to verify the offsetToCertificateBlockHeaderInBytes
 * value at the beginning of a signed image. It should be set to the length of
 * the SB file. If verifying an image in flash, it can be set to the internal
 * flash size or a large number like 0x10000000.
 *
 * userRHK can optionally be used by the user to override the RHK in IFR. If
 * userRHK is not NULL, it points to a 32-byte array containing the SHA-256 of
 * the root certificate's RSA public key.
 *
 * The regions field points to an array of memory regions that the SB file being
 * loaded is allowed to access. If regions is NULL, then all memory is
 * accessible by the SB file. This feature is required to prevent a malicious
 * image from erasing good code or RAM contents while it is being loaded, only
 * for us to find that the image is inauthentic when we hit the end of the
 * section.
 *
 * overrideSBBootSectionID lets the caller override the default section of the
 * SB file that is processed during a kKbootLoadSB operation. By default,
 * the section specified in the firstBootableSectionID field of the SB header
 * is loaded. If overrideSBBootSectionID is non-zero, then the section with
 * the given ID will be loaded instead.
 *
 * The userSBKEK field lets a user provide their own AES-256 key for unwrapping
 * keys in an SB file during the kKbootLoadSB operation. userSBKEK should point
 * to a 32-byte AES-256 key. If userSBKEK is NULL then the IFR SBKEK will be used.
 * After kb_init() returns, the caller should zero out the data pointed to by
 * userSBKEK, as the API will have installed the key in the CAU3.
 */

typedef struct _kb_load_sb
{
    uint32_t profile;
    uint32_t minBuildNumber;
    uint32_t overrideSBBootSectionID;
    uint32_t *userSBKEK;
    uint32_t regionCount;
    const kb_region_t *regions;
} kb_load_sb_t;

typedef struct _kb_authenticate
{
    uint32_t profile;
    uint32_t minBuildNumber;
    uint32_t maxImageLength;
    uint32_t *userRHK;
} kb_authenticate_t;

typedef struct _kb_options
{
    uint32_t version; /*!< Should be set to kKbootApiVersion.*/
    uint8_t *buffer;  /*!< Caller-provided buffer used by Kboot.*/
    uint32_t bufferLength;
    kb_operation_t op;
    union
    {
        kb_authenticate_t authenticate; /*! Settings for kKbootAuthenticate operation.*/
        kb_load_sb_t loadSB;            /*! Settings for kKbootLoadSB operation.*/
    };
} kb_options_t;

/*!
 * @brief Interface to memory operations for one region of memory.
 */
typedef struct _memory_region_interface
{
    status_t (*init)(void);
    status_t (*read)(uint32_t address, uint32_t length, uint8_t *buffer);
    status_t (*write)(uint32_t address, uint32_t length, const uint8_t *buffer);
    status_t (*fill)(uint32_t address, uint32_t length, uint32_t pattern);
    status_t (*flush)(void);
    status_t (*erase)(uint32_t address, uint32_t length);
    status_t (*config)(uint32_t *buffer);
    status_t (*erase_all)(void);
} memory_region_interface_t;

/*!
 * @brief Structure of a memory map entry.
 */
typedef struct _memory_map_entry
{
    uint32_t startAddress;
    uint32_t endAddress;
    uint32_t memoryProperty;
    uint32_t memoryId;
    const memory_region_interface_t *memoryInterface;
} memory_map_entry_t;

typedef struct _kb_opaque_session_ref
{
    kb_options_t context;
    bool cau3Initialized;
    memory_map_entry_t *memoryMap;
} kb_session_ref_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize ROM API for a given operation.
 *
 * Inits the ROM API based on the options provided by the application in the second
 * argument. Every call to rom_init() should be paired with a call to rom_deinit().
 *
 * @retval #kStatus_Success API was executed successfully.
 * @retval #kStatus_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_RomApiBufferSizeNotEnough The user buffer is not enough for use by Kboot during execution of the
 * operation.
 * @retval #kStatus_RomApiInvalidBuffer The user buffer is not ok for sbloader or authentication.
 * @retval #kStatus_SKBOOT_Fail Return the failed status of secure boot.
 * @retval #kStatus_SKBOOT_KeyStoreMarkerInvalid The key code for the particular PRINCE region is not present in the
 * keystore
 * @retval #kStatus_SKBOOT_Success Return the successful status of secure boot.
 */
status_t kb_init(kb_session_ref_t **session, const kb_options_t *options);

/*!
 * @brief Cleans up the ROM API context.
 *
 * After this call, the context parameter can be reused for another operation
 * by calling rom_init() again.
 *
 * @retval #kStatus_Success API was executed successfully
 */
status_t kb_deinit(kb_session_ref_t *session);

/*!
 * Perform the operation configured during init.
 *
 * This application must call this API repeatedly, passing in sequential chunks of
 * data from the boot image (SB file) that is to be processed. The ROM will perform
 * the selected operation on this data and return. The application may call this
 * function with as much or as little data as it wishes, which can be used to select
 * the granularity of time given to the application in between executing the operation.
 *
 * @param session Current ROM context pointer.
 * @param data Buffer of boot image data provided to the ROM by the application.
 * @param dataLength Length in bytes of the data in the buffer provided to the ROM.
 *
 * @retval #kStatus_Success ROM successfully process the part of sb file/boot image.
 * @retval #kStatus_RomApiExecuteCompleted ROM successfully process the whole sb file/boot image.
 * @retval #kStatus_Fail An error occurred while executing the operation.
 * @retval #kStatus_RomApiNeedMoreData No error occurred, but the ROM needs more data to
 * continue processing the boot image.
 * @retval #kStatus_RomApiBufferSizeNotEnough user buffer is not enough for
 * use by Kboot during execution of the operation.
 */
status_t kb_execute(kb_session_ref_t *session, const uint8_t *data, uint32_t dataLength);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* _FSL_IAP_KBP_H_ */
