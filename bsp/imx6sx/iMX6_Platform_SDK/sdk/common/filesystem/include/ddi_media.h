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
////////////////////////////////////////////////////////////////////////////////
//! \addtogroup ddi_media
//! @{
//! \file ddi_media.h
//! \brief Contains public interface for the Logical Drive Layer.
////////////////////////////////////////////////////////////////////////////////
#ifndef _DDI_MEDIA_H
#define _DDI_MEDIA_H

#include <types.h>
// #include "ddi_media_errordefs.h"
//#include "drive_tags.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

//! \brief Maximum number of entries in the media allocation table.
#define MAX_MEDIA_TABLE_ENTRIES                 8

//! \brief Maximum number of media supported at once.
#define MAX_LOGICAL_MEDIA                       2

//! \brief Maximum number of drives supported at once.
//!
//! The current set of drives is as follows:
//! - Internal data
//! - External data
//! - Hidden 1
//! - Hidden 2
//! - System primary
//! - System secondary
//! - System master
//!
//! With a few extra slots added for safety, the maximum is set to 10.
#define MAX_LOGICAL_DRIVES                      8

//! \brief Constant to be passed to erase functions.
#define DDI_MAGIC_NUMBER                        0xADEADE

//! \name Write types
//!
//! These values are passed to the read and write functions to give a hint as to
//! the sequence of I/O operations that is being performed.
//@{
#define WRITE_TYPE_RANDOM    0
#define WRITE_TYPE_SEQ_FIRST 1
#define WRITE_TYPE_SEQ_NEXT  2
#define WRITE_TYPE_NOREADBACK  3
//@}

///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////

//! Abstract reference for a logical drive. This value should be unique for each drive.
typedef uint8_t DriveTag_t;

//! \brief TBD
//! \todo [PUBS] Add definition(s)...Low
typedef enum {
    //! \brief TBD
    kMediaStateUnknown,
    //! \brief TBD
    kMediaStateErased,
    //! \brief TBD
    kMediaStateAllocated
} MediaState_t;

//! \brief This initialization state type can be used to signify if media or drive 
//! or FS init has been attempted yet and whether it succeeded.
//! Note: See related SCSI_MEDIA_STATE (logical drive state) & its state machine 
//!       spec in scsi.h. and see g_eMtpExternalStoreState.
typedef enum {
    eInitPending = 0,           // Default state indicates that init attempt hasn't completed yet, so can wait on it.
    eInitFailed,
    eInitSucceeded,             // Initialized. 
    eInitTerminated             // After a shutdown, the state of entity initialization is terminated.
} InitializationState_t;

//! \brief An enumeration of physical storage media types supported by STMP3xxx SDK5
typedef enum {
    //! \brief NAND flash is typically the primary storage media
    kMediaTypeNand,

    //! \brief MultiMedia Card (MMC) or Secure Digital (SD) card may be removable.
    kMediaTypeMMC,

    //! \brief Hard Disk Drive (HDD) spinning random access R/W storge media
    kMediaTypeHDD,

    //! \brief RAM based virtual disk for mounting an FS in fast access RAM (if extra available).
    kMediaTypeRAM,

    //! \brief Toshiba LBA-NAND device.
    kMediaTypeLbaNand
} PhysicalMediaType_t;

//! \brief TBD
//! \todo [PUBS] Add definition(s)...Medium
enum _logical_media_info {
    //! \brief Count of drives belonging to this media. (uint32_t)
    kMediaInfoNumberOfDrives = 0,

    //! \brief Total size of the media in bytes. (uint64_t)
    kMediaInfoSizeInBytes = 1,

    //! \brief Size in bytes of the media's sectors. (uint32_t)
    //!
    //! \note This sector size is always "native". Only drives have the concept of a nominal
    //!     sector size.
    kMediaInfoAllocationUnitSizeInBytes = 2,

    //! \copydoc kMediaInfoAllocationUnitSizeInBytes
    //!
    //! This selector is an alias to #kMediaInfoAllocationUnitSizeInBytes.
    kMediaInfoSectorSizeInBytes = kMediaInfoAllocationUnitSizeInBytes,

    //! \brief True if the media has been initialized successfully. (bool)
    kMediaInfoIsInitialized = 3,

    //! \brief Whether the media is erased or allocated. (MediaState_t)
    kMediaInfoMediaState = 4,

    //! \brief True if the media is read-only. (bool)
    kMediaInfoIsWriteProtected = 5,

    //! \brief The type of storage device for this media. (PhysicalMediaType_t)
    kMediaInfoPhysicalMediaType = 6,

    //! \brief Number of bytes for the serial number. (uint32_t)
    kMediaInfoSizeOfSerialNumberInBytes = 7,

    //! \brief The serial number value.
    //!
    //! The length of this property is the value returned by getting the 
    //! #kMediaInfoSizeOfSerialNumberInBytes selector.
    kMediaInfoSerialNumber = 8,

    //! \brief Whether the media has any system drives belonging to it. (bool)
    kMediaInfoIsSystemMedia = 9,

    //! \brief Whether the media is currently mounted. (bool)
    //!
    //! This value will always be true unless the media is removable.
    kMediaInfoIsMediaPresent = 10,

    //! \brief Total size of the NAND page in bytes. (uint32_t)
    //!
    //! This property only applies to NAND media. It's value is the size of the entire NAND
    //! page in bytes, including both the data and metadata/redundant portion of the page.
    //! Common page sizes are 2112, 4224, and 4314 bytes.
    kMediaInfoPageSizeInBytes = 11,

    //! \brief NAND manufacturer ID. (uint32_t)
    //!
    //! For raw NAND, this value is the first byte of the NAND Read ID command results.
    //! For eMMC, this value comes from the CID register.
    kMediaInfoMediaMfgId = 12,

    //! \brief NAND Read ID command results. (uint64_t)
    kMediaInfoIdDetails = 13,

    //! \brief Active number of chip enables. (uint32_t)
    //!
    //! This property only has any meaning if the media uses chip enables.
    kMediaInfoNumChipEnables = 14,

    //! \brief Whether the media is removable. (bool)
    kMediaInfoIsRemovable = 15,

    //! \brief Expected transfer activity in this drive. (TransferActivityType_t)
    //!
    //! The value should be one of:
    //! - #kTransferActivity_Random
    //! - #kTransferActivity_Sequential
    kMediaInfoExpectedTransferActivity = 17,

    //! \brief Selector for enabling the power saving feature in the media, driver specific. (bool)
    kMediaInfoLbaNandIsPowerSaveForcedOn = 18,

    //! \brief Size in bytes of metadata portion of media sector. (uint32_t)
    //!
    //! If the media has sectors with metadata, such as with NAND pages, this value will be
    //! the size in bytes of that metadata. 
    kMediaInfoSectorMetadataSizeInBytes = 19,

    //! \brief Full size of the media's sectors in bytes. (uint32_t)
    //!
    //! This property includes both the data and metadata, if any, portions of the media's
    //! sectors. For NANDs, this would be the full page size. If the media does not have
    //! metadata, then this value will be the same as #kMediaInfoSectorSizeInBytes.
    kMediaInfoSectorTotalSizeInBytes = kMediaInfoPageSizeInBytes,

    //! \brief Whether the driver allows the media device to enter sleep.
    //!
    //! Normally this property is set to true. The driver will use its normal algorithms to put
    //! the device to sleep when it is not being used. But if this property is set to false, then
    //! the driver will not allow the device to enter its sleep mode.
    kMediaInfoIsSleepAllowed = 20,

    //! \brief Device Product Name (32 bytes)
    //!
    //! For eMMC, this value comes from the CID register. For ONFI NANDs, this value comes from
    //! the parameter page. Not all devices will return a value.
    //!
    //! The resulting value is a null-terminated string with a maximum of 31 characters plus the
    //! NULL byte.
    kMediaInfoProductName = 21
};

//! \brief List of drive info selectors.
//!
//! These selectors are passed to DriveGetInfo() and DriveSetInfo() to read and write
//! certain fields per drive. Not all selectors apply to every drive type or media type,
//! and only a few selectors are mutable with DriveSetInfo().
enum _logical_drive_info {
    //! \brief Nominal sector size in bytes for this drive. (uint32_t, r/w)
    //!
    //! This sector size is the "nominal" sector size. It may be different (i.e., smaller)
    //! from the native sector size that is determined by the underlying media. Use this value
    //! if you are using the media cache to read and write.
    //!
    //! The drive's nominal sector size can be overridden by a call to
    //! DriveSetInfo(). The new value must be a power of two between 512 and the value of
    //! the #kDriveInfoNativeSectorSizeInBytes selector. However, the sector size can only
    //! be set \i before the given drive is initialized.
    //!
    //! \retval SUCCESS
    //! \retval ERROR_DDI_LDL_LDRIVE_INVALID_SECTOR_SIZE
    //! \retval ERROR_DDI_LDL_LDRIVE_ALREADY_INITIALIZED
    kDriveInfoSectorSizeInBytes = 0,

    //! \brief The size of the minimum area that can be erased. (uint32_t, r/o)
    //!
    //! This value corresponds to the size of a block for a NAND drive. On media that don't
    //! have erase regions different from sectors, this will be the size of a native sector.
    kDriveInfoEraseSizeInBytes = 1,

    //! \brief Total size of the drive in bytes. (uint64_t, r/o)
    kDriveInfoSizeInBytes = 2,

    //! \brief Total size of the drive in megabytes. (uint32_t, r/o)
    kDriveInfoSizeInMegaBytes = 3,

    //! \brief Number of nominal sectors that the drive occupies. (uint32_t, r/o)
    kDriveInfoSizeInSectors = 4,

    //! \brief The type of the drive. (LogicalDriveType_t, r/o)
    //!
    //! Drives may be one of several distict types. Those are data drives, hidden data drives,
    //! and system drives. Both data and hidden data drives
    kDriveInfoType = 5,

    //! \brief Unique tag value for the drive. (uint32_t, r/w)
    kDriveInfoTag = 6,

    //! \brief Component version number. (SystemVersion_t, r/o)
    kDriveInfoComponentVersion = 7,

    //! \brief Project version number. (SystemVersion_t, r/o)
    kDriveInfoProjectVersion = 8,

    //! \brief Whether the drive is read only. (bool, r/o)
    kDriveInfoIsWriteProtected = 9,

    //! \brief Number of bytes occupied by the serial number. (uint32_t, r/o)
    //! \note For MMC, this returns size in unpacked ASCII chars, not bytes. Multiply by sizeof(uint32_t) to get bytes.
    kDriveInfoSizeOfSerialNumberInBytes = 10,

    //! \brief Unique serial number for the drive in ASCII form. (r/o)
    //!
    //! The size of this property's value is the value of the #kDriveInfoSizeOfSerialNumberInBytes
    //! property.
    kDriveInfoSerialNumber = 11,

    //! \brief Whether the drive's media is currently present. (bool, r/o)
    kDriveInfoMediaPresent = 12,

    //! \brief Whether the media has changed recently. (bool, r/o)
    kDriveInfoMediaChange = 13,

    //! \brief Size in bytes of the raw serial number. (uint32_t, r/o)
    kDriveInfoSizeOfRawSerialNumberInBytes = 15,

    //! \brief Unique serial number for the drive in raw form. (r/o)
    //!
    //! The #kDriveInfoSizeOfRawSerialNumberInBytes property specifies the size in bytes of
    //! this property's value.
    kDriveInfoRawSerialNumber = 16,

    //! \brief Selector for the number of non-sequential sector maps the drive uses. (uint32_t, r/w)
    //!
    //! The parameter is a single uint32_t value that is the count of NSS maps for
    //! the given drive. DriveGetInfo() with this selector will just return the current
    //! count of maps. The array of maps is shared between all data-type drives.
    //! DriveSetInfo() allows you to change the number
    //! of maps to the value passed in. All previous maps will be
    //! flushed immediately and memory for the maps reallocated.
    //!
    //! \retval SUCCESS
    //! \retval ERROR_DDI_NAND_DATA_DRIVE_CANT_ALLOCATE_USECTORS_MAPS
    //!
    //! \note This selector only applies to data drives. System drives will return an error.
    kDriveInfoNSSMCount = 19,

    //! \brief Sector size in bytes that the underlying media has given this drive. (uint32_t, r/o)
    //!
    //! Use the native sector size when working with DriveReadSector(), DriveWriteSector(),
    //! MediaRead(), and MediaWrite().
    kDriveInfoNativeSectorSizeInBytes = 20,

    //! \brief Number of native sectors consumed by this drive. (uint32_t, r/o)
    kDriveInfoSizeInNativeSectors = 21,

    //! \brief Offset to beginning of this partition from the first sector of its parent drive. (uint32_t, r/w)
    kDriveInfoSectorOffsetInParent = 23,

    //! \brief Optimal number of native sectors to read or write at once. (uint32_t, r/o)
    //!
    //! This property is the preferred number of sectors to transfer using a multisector
    //! transaction. If the value is 1, then multisector transactions are no better than a
    //! normal single sector read or write.
    kDriveInfoOptimalTransferSectorCount = 24
};

enum _ldl_media_numbers {
    //! \brief Media number for the internal, non-removable media.
    kInternalMedia = 0,

    //! \brief Media number for external media, usually SD/MMC.
    kExternalMedia = 1
};

//! \name Data drive ID
//@{
#define    DATA_DRIVE_ID_INTERNAL        0
#define    DATA_DRIVE_ID_EXTERNAL        1
//@}

//! \brief Possible types of a logical drive.
typedef enum {
    //! \brief Public data drive.
    //!
    //! Read/write with random access. Typically accessible through the filesystem. Accessible via
    //! USB mass storage and MTP.
    kDriveTypeData = 0,

    //! \brief System drive.
    //!
    //! Designed to hold firmware or system resources that are accessed frequently but written very
    //! rarely. Must be erased before it can be written, and sectors must be written in sequential
    //! order with none skipped. Also, each sector can only be written to once.
    kDriveTypeSystem,

    //! \brief Hidden data drive.
    //!
    //! Similar to #kDriveTypeData, except that hidden data drives are not accessible through
    //! USB mass storage or MTP.
    kDriveTypeHidden,

    //! \brief Unknown drive type.
    //!
    //! Drives should never be this type.
    kDriveTypeUnknown
} LogicalDriveType_t;

//! \brief Describes one drive in a media allocation table.
typedef struct {
    uint32_t u32DriveNumber;
    LogicalDriveType_t Type;
    uint32_t u32Tag;
    uint64_t u64SizeInBytes;
    bool bRequired;
} MediaAllocationTableEntry_t;

//! \brief Table used to list details of a media's drives.
//!
//! This table is used both for allocation to specify the set of drives that should be created
//! on the media, as well as to get the list of a media's current set of drives.
typedef struct {
    uint32_t u32NumEntries;
    MediaAllocationTableEntry_t Entry[MAX_MEDIA_TABLE_ENTRIES];
} MediaAllocationTable_t;

//! \brief TBD
typedef union {
    struct {
        uint8_t MinorL;
        uint8_t MinorH;
        uint8_t MiddleL;
        uint8_t MiddleH;
        uint8_t MajorL;
        uint8_t MajorH;
    } partialVersion;

    uint64_t Version;
} SystemVersion_t;

//! \brief Possible states for a logical drive.
typedef enum {
    kDriveNotPresent,
    kDriveUninitialized,
    kDriveFailedInitialization,
    kDriveReady
} DriveState_t;

//! An opaque type for a drive iterator.
typedef struct OpaqueDriveIterator *DriveIterator_t;

//! \brief Values for #kDriveInfoExpectedTransferActivity media info property.
typedef enum {
    kTransferActivity_Sequential = 0,   //!< Most accesses will be sequential to one another.
    kTransferActivity_Random    //!< There will be no predictable order to accesses.
} TransferActivityType_t;

// Forward delaration.
typedef struct _MediaDefinition MediaDefinition_t;

#if __cplusplus
class LogicalMedia;
#else
typedef struct _OpaqueLogicalMedia LogicalMedia;
#endif

//! \brief Definition of logical media factory function.
typedef LogicalMedia *(*LogicalMediaFactoryFunction_t) (const MediaDefinition_t * def);

//! \brief Struct used by application to declare media types.
struct _MediaDefinition {
    unsigned m_mediaNumber;
    LogicalMediaFactoryFunction_t m_factoryFunction;
    PhysicalMediaType_t m_mediaType;
    bool m_isRemovable;
};

///////////////////////////////////////////////////////////////////////////////
// External references
///////////////////////////////////////////////////////////////////////////////

extern bool g_bFrameworkExternalDriveOrFsInit;
extern InitializationState_t g_eFrameworkExternalMediaInit;

///////////////////////////////////////////////////////////////////////////////
// 4 Public API accessor macros to check external 'media, drive, and FS' init status. 
///////////////////////////////////////////////////////////////////////////////
#if (!defined(WIN32))

// Returns true if the external drive's FS is present and ready to be used, else false.
// See IsExternalDriveFsReady() in FSapi.h

// Returns true if the external drive is init and present, else returns false.
#define IsExternalDriveInit() (g_bFrameworkExternalDriveOrFsInit)

// After exiting the media init pending state (can poll for media init no longer pending), 
// then this becomes valid so check this to see if media init result.
#define IsExternalMediaPresentAndInit() ((g_eFrameworkExternalMediaInit==eInitSucceeded)?true:false)

// if the external media's init attempt has not yet completed, returns true; 
// else the init attempt is complete so return false.
#define IsExternalMediaInitPending()  ((g_eFrameworkExternalMediaInit==eInitPending)? true:false)

#else
#define IsExternalDriveInit()           false
#define IsExternalMediaPresentAndInit() false
#define IsExternalMediaInitPending()    false
#endif

///////////////////////////////////////////////////////////////////////////////
// Prototypes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
//! \brief Initializes the logical data drive on the selected device.
//!
//! Determines the sector location of the logical data drive on the selected
//! device. Reads the media's master boot record (MBR) from sector 0, and
//! saves the starting sector for partition 0, which is the data drive.
//!
//! \param[in]  driveNumber     Logical Drive Number
//!
//! \retval SUCCESS     Initialization completed.
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
//! \retval ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND
//! \retval ERROR_DDI_MEDIABUFMGR_ALLOC_FAILED 
//! \retval ERROR_OS_FILESYSTEM_MAX_DEVICES_EXCEEDED
////////////////////////////////////////////////////////////////////////////////
    RtStatus_t FSDataDriveInit(DriveTag_t tag);

    unsigned MediaGetCount(void);

    RtStatus_t MediaGetInfoSize(unsigned mediaNumber, uint32_t selector, uint32_t * propertySize);

    RtStatus_t MediaSetInfo(unsigned mediaNumber, uint32_t selector, const void *value);

///////////////////////////////////////////////////////////////////////////////
//! \brief Returns the runtime maximum sector size for all active media.
///////////////////////////////////////////////////////////////////////////////
    uint32_t MediaGetMaximumSectorSize(void);

///////////////////////////////////////////////////////////////////////////////
//! \brief Creates and initializes a logical media.
//!
//! The specification of the logical media to be created is defined in a
//! global array of type MediaDefinition_t with the name g_mediaDefinition.
//! This array lets the application tell the LDL what types of media drivers
//! it wants to use.
//!
//! \param[in] u32LogMediaNumber Logical media number
//!
//! \return Status of the call.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t MediaInit(uint32_t u32LogMediaNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief Partition the logical media.
//!
//! The logical media must have just been erased with a call to MediaErase(),
//! with no other calls, except for MediaGetInfo(), since then.
//!
//! \param[in] u32LogMediaNumber Logical media number
//! \param[in] pMediaTable       Pointer to Media Table structure
//!
//! \return Status of the call.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t MediaAllocate(uint32_t u32LogMediaNumber, MediaAllocationTable_t * pMediaTable);

///////////////////////////////////////////////////////////////////////////////
//! \brief Create drives for every partition on the logical media.
//!
//! Call this function after either MediaInit() or MediaAllocate(). It will
//! search the logical media for partitions and create logical drive instances
//! for each one that is found.
//!
//! \param[in] u32LogMediaNumber Logical media number
//!
//! \return Status of the call.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t MediaDiscoverAllocation(uint32_t u32LogMediaNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief Get the current description of drives for a logical media.
//!
//! This function allocates and fills in a MediaAllocationTable_t with
//! information about all of the drives or partitions the logical media knows
//! about. It should normally only be called after calling MediaDiscoverAllocation().
//!
//! The media allocation table that is returned from this API is dynamically
//! allocated, so it must be freed when the caller no longer needs it. To do
//! this, pass the table to MediaFreeMediaTable().
//!
//! \param[in] u32LogMediaNumber The logical media number.
//! \param[in] pMediaTable On successful exit, this will point to a newly
//!      allocated mediaallocation table.
//!
//! \return Status of the call.
//! \retval ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t MediaGetMediaTable(uint32_t u32LogMediaNumber,
                                  MediaAllocationTable_t ** pMediaTable);

///////////////////////////////////////////////////////////////////////////////
//! \brief Dispose of a media table.
//!
//! Frees memory for a media allocation table that was returned from a call
//! to MediaGetMediaTable().
//!
//! \param mediaNumber The logical media number.
//! \param table Pointer to the media table to free. This value must have
//!     been returned from MediaGetMediaTable().
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t MediaFreeMediaTable(uint32_t mediaNumber, MediaAllocationTable_t * table);

///////////////////////////////////////////////////////////////////////////////
//! \brief Get a property of a logical media.
//!
//! For the requested logical media number, get the info Type requested into *pInfo.
//! Type must be one of those supported by the media driver
//! as defined for example in NANDMediaGetInfo and MmcMediaGetInfo.
//!
//! \param[in] u32LogMediaNumber Logical media number
//! \param[in] Type              Logical media type
//! \param[in] pInfo             Receives media information
//!
//! \return Status of the call.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t MediaGetInfo(uint32_t u32LogMediaNumber, uint32_t Type, void *pInfo);

///////////////////////////////////////////////////////////////////////////////
//! \brief Erase all allowed portions of the media except hidden areas if requested.
//!
//! \param[in] u32LogMediaNumber Logical drive number
//! \param[in] u32MagicNumber    TBD
//! \param[in] u8NoEraseHidden   Flag to indicate hidden data drive should
//!                              not be erased.
//!
//! \return Status of the call.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t MediaErase(uint32_t u32LogMediaNumber, uint32_t u32MagicNumber,
                          uint8_t u8NoEraseHidden);

////////////////////////////////////////////////////////////////////////////////
//! \brief If the media number is valid and was init, calls media's shutdown API.
//!
//! \param[in] wLogMediaNumber     Logical Media Number such as that of NAND or MMC
//!
//! \return Status of call RtStatus_t
//! \retval SUCCESS If no error has occurred.
//! \retval ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER.
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED.
////////////////////////////////////////////////////////////////////////////////
    RtStatus_t MediaShutdown(uint32_t u32LogMediaNumber);

////////////////////////////////////////////////////////////////////////////////
//! \brief If the media number is valid and was init, calls media's flush drives API.
//!
//! \param[in] wLogMediaNumber     Logical Media Number such as that of NAND or MMC
//!
//! \return Status of call RtStatus_t
//! \retval SUCCESS If no error has occurred.
//! \retval ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER.
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED.
////////////////////////////////////////////////////////////////////////////////
    RtStatus_t MediaFlushDrives(uint32_t u32LogMediaNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief LDL API to set bootable firmware to primary or secondary firmware.
//!
//! \fntype Function
//!
//! \param[in] u32LogMediaNumber Logical drive number
//! \param[in] u32DriveTag       Drive tag, can be either DRIVE_TAG_BOOTMANAGER_S
//!                              or DRIVE_TAG_BOOTMANAGER2_S
//!
//! \return Status of the call.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t MediaSetBootDrive(uint32_t u32LogMediaNumber, DriveTag_t u32DriveTag);

    unsigned DriveGetCount(void);

    RtStatus_t DriveCreateIterator(DriveIterator_t * iter);

    RtStatus_t DriveIteratorNext(DriveIterator_t iter, DriveTag_t * tag);

    void DriveIteratorDispose(DriveIterator_t iter);

    DriveState_t DriveGetState(DriveTag_t tag);

    RtStatus_t DriveInitAll(void);

    RtStatus_t DriveGetInfoSize(DriveTag_t tag, uint32_t selector, uint32_t * propertySize);

///////////////////////////////////////////////////////////////////////////////
//! \brief Initializes the specified drive.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//!
//! \return Status of the call.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveInit(DriveTag_t tag);

///////////////////////////////////////////////////////////////////////////////
//! \brief For the requested logical drive, get the info Type into *pInfo.
//!
//! The Type must be supported by the media driver implementation such as  
//! NANDDataDriveGetInfo or ddi_mmc_DataDriveGetInfo.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//! \param[in] Type              Type of information to write to *pInfo
//! \param[out] pInfo            Buffer to fill with requested information
//!
//! \return Status of the call.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveGetInfo(DriveTag_t tag, uint32_t Type, void *pInfo);

///////////////////////////////////////////////////////////////////////////////
//! \brief For the requested logical drive, set the *pInfo of Type specified. 
//!
//! Type must be supported by the media driver implementation such as  
//! NANDDataDriveSetInfo or ddi_mmc_DataDriveSetInfo.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//! \param[in] Type              Type of information to set
//! \param[in] pInfo             Buffer to copy the information from
//!
//! \return Status of the call.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_INFO_TYPE
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveSetInfo(DriveTag_t tag, uint32_t Type, const void *pInfo);

///////////////////////////////////////////////////////////////////////////////
//! \brief Read a sector from the indicated drive.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//! \param[in] u32SectorNumber    Sector to read; 0-based at the start of the drive.
//! \param[in] pSectorData        Pointer to buffer to fill with sector data.
//!
//! \return Status of the call.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveReadSector(DriveTag_t tag, uint32_t u32SectorNumber,
                               SECTOR_BUFFER * pSectorData);

///////////////////////////////////////////////////////////////////////////////
//! \brief Virtual Memory Interface entry point for loading a sector to RAM.
//!
//! NOTHING other than the VMI component is allowed to call this function. The
//! code path for this function is guaranteed to not require paging.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//! \param[in] u32SectorNumber    Sector to read; 0-based at the start of the drive.
//! \param[in] pSectorData        Pointer to buffer to fill with sector data.
//!
//! \return Status of the call.
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER
//! \retval ERROR_DDI_LDL_LDRIVE_NOT_INITIALIZED
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveReadSectorForVMI(DriveTag_t tag, uint32_t u32SectorNumber,
                                     SECTOR_BUFFER * pSectorData);

///////////////////////////////////////////////////////////////////////////////
//! \brief Writes a sector of a logical drive.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//! \param[in] u32SectorNumber   Sector to write; 0-based at the start of the drive.
//! \param[in] pSectorData       Pointer to buffer of sector data to write.
//!
//! \return Status of the call.
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER
//! \retval ERROR_DDI_LDL_LDRIVE_NOT_INITIALIZED
//! \retval Others possible from drive type's WriteSector API
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveWriteSector(DriveTag_t tag, uint32_t u32SectorNumber,
                                const SECTOR_BUFFER * pSectorData);

///////////////////////////////////////////////////////////////////////////////
//! \brief Start a multi-sector read or write sequence.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveOpenMultisectorTransaction(DriveTag_t tag, uint32_t startSector,
                                               uint32_t sectorCount, bool isRead);

///////////////////////////////////////////////////////////////////////////////
//! \brief Complete a multi-sector transfer.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveCommitMultisectorTransaction(DriveTag_t tag);

///////////////////////////////////////////////////////////////////////////////
//! \brief Erase the logical drive if the drive num is valid and already init.
//!
//! \param[in] u32LogDriveNumber Logical drive number
//! \param[in] u32MagicNumber    Currently unused.
//!
//! \return Status of the call.
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER
//! \retval ERROR_DDI_LDL_LDRIVE_NOT_INITIALIZED
//! \retval Others possible from drive type's erase API
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveErase(DriveTag_t tag, uint32_t u32MagicNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief Attempt to repair a drive by doing a low-level format.
//!
//! \param[in] u32LogDriveNumber Logical drive number
//! \param[in] u32MagicNumber    Currently unused.
//!
//! \return Status of the call.
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER
//! \retval ERROR_DDI_LDL_LDRIVE_FS_FORMAT_REQUIRED Drive was erased.
//! \retval Others possible from drive erase API.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveRepair(DriveTag_t tag, uint32_t u32MagicNumber);

////////////////////////////////////////////////////////////////////////////////
//! \brief Flush the logical drive number's contents from RAM to physical media.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//!
//! \retval SUCCESS 
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER 
//! \retval ERROR_DDI_LDL_LDRIVE_NOT_INITIALIZED         NAND: this or above.
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED   Possible for SD or MMC. 
//! \retval MMC_DATA_DRIVE_ERROR_WRITE_SECTOR_FAIL       Possible for SD or MMC.
//! \retval ERROR_DDI_LDL_LDRIVE_HARDWARE_FAILURE        Possible for SD or MMC.
////////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveFlush(DriveTag_t tag);

////////////////////////////////////////////////////////////////////////////////
//! \brief DriveFlush and if allowed shutdown the logical data drive.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//!
//! \return RtStatus or an error the drive's flush or shutdown API.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
////////////////////////////////////////////////////////////////////////////////
    RtStatus_t DriveShutdown(DriveTag_t tag);

//! \name Media task tracking
//!
//! These functions are used by the high level code to provide debugging information
//! about the context of media operations.
//!
//! \note These functions are only available in debug builds. In release builds they
//! simply turn into empty stubs.
//@{
//! Set this macro to 1 to enable media task tracking.
#define DDI_LDL_ENABLE_MEDIA_TASKS 0

#if DEBUG && DDI_LDL_ENABLE_MEDIA_TASKS
    void ddi_ldl_push_media_task(const char *taskName);
    void ddi_ldl_pop_media_task(void);
    unsigned ddi_ldl_get_media_task_count(void);
    unsigned ddi_ldl_get_media_task_stack(const char **tasks, unsigned maxTasks);
#else
// moved to ddi_media.c to quickly fix build multiple definitions issue !
    static inline void ddi_ldl_push_media_task(const char *taskName) {
    } static inline void ddi_ldl_pop_media_task(void) {
    }
    static inline unsigned ddi_ldl_get_media_task_count(void) {
        return 0;
    }
    static inline unsigned ddi_ldl_get_media_task_stack(const char **tasks, unsigned maxTasks) {
        return 0;
    }
#endif
//@}

#ifdef __cplusplus
}                               // extern "C"

/*!
 * \brief Helper for media tasks.
 */
class MediaTask {
  public:
    MediaTask(const char *name) {
        ddi_ldl_push_media_task(name);
    } ~MediaTask() {
        ddi_ldl_pop_media_task();
    }
};

//! \brief Convenient template form of MediaGetInfo().
template < typename T > inline T MediaGetInfoTyped(uint32_t mediaNumber, uint32_t selector)
{
    T value = 0;
    MediaGetInfo(mediaNumber, selector, &value);
    return value;
}

//! \brief Convenient template form of MediaGetInfo().
template < typename T >
    inline T MediaGetInfoTyped(uint32_t mediaNumber, uint32_t selector, RtStatus_t & status)
{
    T value = 0;
    status = MediaGetInfo(mediaNumber, selector, &value);
    return value;
}

//! \brief Convenient template form of DriveGetInfo().
template < typename T > inline T DriveGetInfoTyped(DriveTag_t drive, uint32_t propertyName)
{
    T value = 0;
    DriveGetInfo(drive, propertyName, (void *)&value);
    return value;
}

//! \brief Convenient template form of DriveGetInfo().
template < typename T > inline T DriveGetInfoTyped(DriveTag_t drive, uint32_t propertyName,
                                                   RtStatus_t & status)
{
    T value = 0;
    status = DriveGetInfo(drive, propertyName, (void *)&value);
    return value;
}

//! \brief Convenient template form of DriveSetInfo().
//! \note This function is named differently than DriveSetInfo() because the GHS C++ compiler
//!     wants to create an instatiation loop if they're named the same. Maybe this is because
//!     the base function uses C linkage?
template < typename T > inline RtStatus_t DriveSetInfoTyped(DriveTag_t drive, uint32_t propertyName,
                                                            T value)
{
    return DriveSetInfo(drive, propertyName, (const void *)&value);
}

#endif // __cplusplus

#endif // _DDI_MEDIA_H
//! @}
