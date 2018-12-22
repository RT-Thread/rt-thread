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
//! \defgroup media_cache Media Sector Cache
//! \ingroup ddi_media
//! \brief Manages a cache of media sectors.
//!
//! \section intro Introduction
//!
//! The media cache library provides a sector-server interface to media
//! drivers such as the NAND and SD/MMC drivers. In the layer cake, it sits on
//! top of the LDL (Logical Drive Layer) but below the filesystem. In addition
//! to the obvious caching of sectors, the media cache is where support comes
//! in for sector sizes smaller than the native block or page size of the
//! underlying media. 
//!
//! \section owners Ownership
//!
//! Read/write ownership is managed at the native sector level rather than for
//! each nominal sector. This means that a single thread cannot overlap a
//! read and write or two write calls for sequential nominal sectors that belong
//! to the same native sector. (You can never overlap those calls on the same
//! sector.)
//!
//! \section pbs Param blocks
//!
//! The documentation of each API function lists the fields of the param
//! block that are read and written for that particular operation. These symbols
//! are used to identify the direction of each field:
//!     - \b => input to API (read)
//!     - \b <= output from API (write)
//!     - \b X  don't care
//!
//! The fields that are read only are guaranteed to not be modified during the call.
//! Also, don't-care fields can be set to any value and are completely ignored.
//! This allows the caller to reuse a param block for several distinct
//! calls, only changing the fields that are different. For instance, a
//! caller could set up a param block for a read operation and reuse most
//! of the fields for a write.
//!
//! The best way to declare a local param block is like this:
//! \code
//!     MediaCacheParamBlock_t pb = {0};
//! \endcode
//! This will ensure that all fields are initialized to zero, even if
//! additional fields are added in the future.
//!
//! @{
//! \file media_cache.h
//! \brief Public API to manage cache of media sectors.
///////////////////////////////////////////////////////////////////////////////

#if !defined(_media_cache_h_)
#define _media_cache_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include "types.h"
// #include "ddi_media_errordefs.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

//! \brief Flags for media cache calls.
//!
//! These flags should be set in the \a flags field of the #MediaCacheParamBlock_t
//! that is passed to the core media cache API functions for reading, writing,
//! and flushing. Not all flags apply to all functions. See the documentation for
//! each function for a list to applicable flags.
enum media_cache_flags {
    //! Operate on buffers the size of the underlying media sectors rather than
    //! software-defined sector sizes. This size is equivalent to the value returned
    //! from DriveGetInfo() with the #kDriveInfoNativeSectorSizeInBytes selector.
    //! Note that this means that the #MediaCacheParamBlock_t::sector field of the
    //! param block must be in units of native sectors and not the normal nominal
    //! sectors.
    kMediaCacheFlag_UseNativeSectors = 1 << 0,

    //! This flag does not actually bypass the cache. Instead, it causes the cache
    //! entry for the targeted sector to be reused immediately. More specifically, it
    //! places the entry at the head of the LRU list (the least recently used end),
    //! instead of the tail of the list (the most recently used end). This is very
    //! useful for cases where the caller knows in advance that the sector is highly
    //! unlikely to be accessed any time soon. Yet, by not completely bypassing the cache,
    //! nominal sector sizes smaller than the native sector size can still be
    //! transparently supported.
    kMediaCacheFlag_BypassCache = 1 << 1,

    //! Set this flag when calling media_cache_flush() to flush a single drive,
    //! specified by the \a drive field of the param block.
    kMediaCacheFlag_FlushDrive = 1 << 2,

    //! Set this flag when calling media_cache_flush() to flush the entire cache.
    //! If this flag is not set, the \a drive parameter is used to determine which
    //! drive to flush. 
    kMediaCacheFlag_FlushAllDrives = 1 << 3,

    //! When set, a write operation will cause the cache entry to immediately be flushed
    //! to media. Please be aware that if nominal sector size is not equal to native
    //! sector size, then this option can cause a great deal of thrashing.
    kMediaCacheFlag_WriteThrough = 1 << 4,

    //! Normally, the offset to the beginning of the PBS for the FAT partition,
    //! for drives that have an MBR, is added to any sector number passed into the
    //! media cache operations. When this flag is set, the PBS offset is no longer
    //! added, thus allowing the caller to read and write the MBR and other sectors
    //! before the FAT partition.
    kMediaCacheFlag_NoPartitionOffset = 1 << 5,

    //! When applied to pinned write operations, this flag indicates that the caller
    //! does not care about the previous contents of the sectors being written. If
    //! a new cache entry has to be used, evicting an older one, an initial read to
    //! fill the entry with the previous sector contents will not be performed. In
    //! the case that the sector is already in the cache, this flag has no effect.
    kMediaCacheFlag_NoReadback = 1 << 6,

    //! Set this flag to enable the use of the \a media_cache_param_block::weight
    //! field of the param block. Without this flag set, that field is ignored
    //! and the weighting is assumed to be #kMediaCacheWeight_Low.
    kMediaCacheFlag_ApplyWeight = 1 << 7,

    //! Invalidates all flushed cache entries in addition to writing them to media.
    //! This option is most useful when the contents of a sector change are changed
    //! on the media without going through the media cache (i.e., a direct write
    //! through the LDL).
    kMediaCacheFlag_Invalidate = 1 << 8,

    //! Setting this flag in conjunction with #kMediaCacheFlag_NoReadback will cause
    //! the media cache to not perform a readback when loading a sector into the cache,
    //! regardless of whether the write fills the complete native sector. The implication
    //! is that there will be further writes coming that will fill the rest of the native
    //! sector.
    kMediaCacheFlag_SequentialWrite = 1 << 9,

    // Don't release this cache entry to the media cache pool even if this cache is free
    kMediaCacheFlag_RemoveEntry = 1 << 10
};

//! \brief Constants for sector weights in the cache.
enum media_cache_weights {
    kMediaCacheWeight_Low = 0,
    kMediaCacheWeight_Medium = 5,
    kMediaCacheWeight_High = 10
};

/*!
 * \brief Param block structure for media cache read/write API.
 *
 * See the API documentation for a list of which fields are inputs to and which
 * are outputs from the various functions.
 *
 * \todo Do we really need #media_cache_param_block::mode?
 */
struct media_cache_param_block {
    int16_t weight;             //!< Weight value used to modify cache entry persistence.
    uint8_t mode;               //!< One of WRITE_TYPE_xxx in ddi_media.h.
    uint8_t drive;              //!< Index of the drive to which the sector belongs.
    uint32_t sector;            //!< Sector or starting sector.
    uint32_t flags;             //!< Optional flags to modify the operation.
    uint8_t *buffer;            //!< Pointer to the buffer.
    uint16_t requestSectorCount;    //!< Requested number of sectors.
    uint16_t actualSectorCount; //!< Number of sectors big the buffer is.
    uint32_t token;             //!< The token passed to media_cache_release() when done with the buffer.
    uint16_t writeOffset;       //!< Offset into the sector buffer to write the source buffer.
    uint16_t writeByteCount;    //!< Number of bytes to write from the source buffer.
};

//! Typedef for media cache param block structure.
typedef struct media_cache_param_block MediaCacheParamBlock_t;

///////////////////////////////////////////////////////////////////////////////
// Prototypes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

//! \brief Initalizes the media sector cache.
//!
//! The \a cacheBuffer parameter is memory allocated by the caller that is used to
//! hold the sector data for cache entries. It is divided into as many sectors as
//! will fit, using the largest sector size of attached media. This allows all cache
//! entries to be used for any drive on any media.
//!
//! \param cacheBuffer Pointer to a block of memory that will be used to hold cached
//!     media sectors. It is important that this memory be physically contiguous,
//!     because it will be used with DMA operations. The buffer must also be aligned
//!     to the size of a cache line in the CPU's data cache (32 bytes for the ARM9).
//! \param cacheBufferLength The number of bytes in the buffer pointed to by \a cacheBuffer.
//!     The buffer must be at least large enough to hold one sector.
//!
//! \retval SUCCESS The media cache was successfully initialized.
//! \retval ERROR_DDI_MEDIA_CACHE_INVALID_BUFFER If the \a cacheBuffer is not large
//!     enough for at least a single sector, or if it is not data cache aligned, then
//!     this error is returned.
    RtStatus_t media_cache_init(uint8_t * cacheBuffer, uint32_t cacheBufferLength);

//! \brief Clean up the media cache and free allocated memory.
//!
//! \retval SUCCESS The media cache was shut down and all dynamically allocated memory
//!     was freed.
    RtStatus_t media_cache_shutdown(void);

//! \brief Performs a cached read operation.
//!
//! This function loads one or more sectors into cache entries and returns a
//! pointer to the sector data. The caller can request more than one sector in
//! sequential order and the function will return as many as it can.
//!
//! \note If an error is returned, there is no need to call media_cache_release().
//!
//! \par Param block fields:
//! - \b => \em weight
//! - \b => \em drive
//! - \b => \em sector
//! - \b => \em flags
//! - \b <= \em buffer
//! - \b => \em requestSectorCount
//! - \b <= \em actualSectorCount
//! - \b <= \em token
//! - \b X \em writeOffset
//! - \b X \em writeByteCount
//! - \b => \em mode
//!
//! \par Honored flags:
//! - #kMediaCacheFlag_UseNativeSectors
//! - #kMediaCacheFlag_BypassCache
//! - #kMediaCacheFlag_NoPartitionOffset
//! - #kMediaCacheFlag_ApplyWeight
//!
//! \param pb Pointer to the parameter block.
//! \retval SUCCESS The read was completed without error.
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER An invalid drive number was passed in the param block.
//! \retval ERROR_DDI_LDL_LDRIVE_SECTOR_OUT_OF_BOUNDS The sector passed in the param block is larger than
//!     the actual number of sectors that the drive has.
    RtStatus_t media_cache_read(MediaCacheParamBlock_t * pb);

//! \brief Performs a cached write operation.
//!
//! Use this function to write a buffer that you already have to a given sector.
//! The buffer does not have to be the full size of the sector, and can be written
//! to any offset within the sector. Only one sector may be written to per call
//! of this function.
//!
//! If there are owners of the sector that is being written, i.e. unreleased
//! media_cache_read() calls, this function will wait until all owners release the
//! sector before performing the write. Keep this in mind so that you do not
//! introduce deadlocks by trying to write to a sector from the same thread that
//! owns that sector due to an unreleased read call.
//!
//! \par Param block fields:
//! - \b => \em weight
//! - \b => \em drive
//! - \b => \em sector
//! - \b => \em flags
//! - \b => \em buffer
//! - \b X \em requestSectorCount
//! - \b X \em actualSectorCount
//! - \b X \em token
//! - \b => \em writeOffset
//! - \b => \em writeByteCount
//! - \b => \em mode
//!
//! \par Honored flags:
//! - #kMediaCacheFlag_UseNativeSectors
//! - #kMediaCacheFlag_BypassCache
//! - #kMediaCacheFlag_NoPartitionOffset
//! - #kMediaCacheFlag_WriteThrough
//! - #kMediaCacheFlag_NoReadback
//! - #kMediaCacheFlag_ApplyWeight
//!
//! \param pb Pointer to the parameter block.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER An invalid drive number was passed in the param block.
//! \retval ERROR_DDI_LDL_LDRIVE_SECTOR_OUT_OF_BOUNDS The sector passed in the param block is larger than
//!     the actual number of sectors that the drive has.
    RtStatus_t media_cache_write(MediaCacheParamBlock_t * pb);

//! \brief Returns a sector buffer into which the caller can write.
//!
//! Unlike media_cache_write(), this function does not take a buffer from the caller
//! and copy it into the sector cache entry. Instead, it returns a buffer into which
//! the caller can write data. In particular, this makes it possible to DMA directly
//! into the sector cache entry.
//!
//! An additional feature of this function is that the caller can request to write
//! to a sequential run of more than one sector, starting at the sector indicated by
//! the \a sector field of the param block. The number of requested sectors is
//! placed into the \a requestSectorCount field of the param block. The function will
//! return a buffer large enough to hold as many sectors as it can arrange. It puts
//! this actual number of sectors in the \a actualSectorCount field.
//!
//! After the caller has filled the returned buffer with data, the media_cache_release()
//! function must be called and the \a token field of the param block passed to it.
//! Doing so completes the write operation. If the #kMediaCacheFlag_WriteThrough flag
//! is set, the sector contents are immediately written to media. Otherwise the
//! contents will only be written when the cache entry is either evicted or explicitly
//! flushed with a call to media_cache_flush().
//!
//! \note If an error is returned, there is no need to call media_cache_release().
//!
//! \par Param block fields:
//! - \b => \em weight
//! - \b => \em drive
//! - \b => \em sector
//! - \b => \em flags
//! - \b <= \em buffer
//! - \b => \em requestSectorCount
//! - \b <= \em actualSectorCount
//! - \b <= \em token
//! - \b X \em writeOffset
//! - \b X \em writeByteCount
//! - \b => \em mode
//!
//! \par Honored flags:
//! - #kMediaCacheFlag_UseNativeSectors
//! - #kMediaCacheFlag_NoPartitionOffset
//! - #kMediaCacheFlag_WriteThrough
//! - #kMediaCacheFlag_NoReadback
//! - #kMediaCacheFlag_ApplyWeight
//!
//! \param pb Pointer to the parameter block.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER An invalid drive number was passed in the param block.
//! \retval ERROR_DDI_LDL_LDRIVE_SECTOR_OUT_OF_BOUNDS The sector passed in the param block is larger than
//!     the actual number of sectors that the drive has.
    RtStatus_t media_cache_pinned_write(MediaCacheParamBlock_t * pb);

//! \brief Flushes part or all of the cache.
//!
//! This function causes one or more dirty cache entries to be immediately written
//! to media. It has three modes, selected based on the flags that are set:
//! - Flush a single sector.
//! - Flush all sectors of a specified drive. Set the #kMediaCacheFlag_FlushDrive flag.
//! - Flush every sector in the cache. Set the #kMediaCacheFlag_FlushAllDrives flag.
//!
//! If both #kMediaCacheFlag_FlushDrive and #kMediaCacheFlag_FlushAllDrives are set,
//! then the latter takes precedence.
//!
//! In addition to just writing dirty entries to media, this function can mark all
//! chosen entries, depending on the mode, as invalid. To enable this option, set the
//! #kMediaCacheFlag_Invalidate flag in the param block.
//!
//! Control does not return to the caller until all writes are complete. This may take
//! a while when flushing a drive or the entire cache.
//!
//! \par Param block fields:
//! - \b => \em drive
//! - \b => \em sector
//! - \b => \em flags
//! - \b X \em buffer
//! - \b X \em requestSectorCount
//! - \b X \em actualSectorCount
//! - \b X \em token
//! - \b X \em writeOffset
//! - \b X \em writeByteCount
//! - \b X \em mode
//!
//! \par Honored flags:
//! - #kMediaCacheFlag_UseNativeSectors - Only applies if flushing a single sector.
//! - #kMediaCacheFlag_NoPartitionOffset - Only applies if flushing a single sector.
//! - #kMediaCacheFlag_FlushDrive
//! - #kMediaCacheFlag_FlushAllDrives
//! - #kMediaCacheFlag_Invalidate
//!
//! \param pb Pointer to the parameter block.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER An invalid drive number was passed in the param block.
//! \retval ERROR_DDI_LDL_LDRIVE_SECTOR_OUT_OF_BOUNDS The sector passed in the param block is larger than
//!     the actual number of sectors that the drive has.
    RtStatus_t media_cache_flush(MediaCacheParamBlock_t * pb);

//! \brief Releases the lock on a cache entry.
//!
//! After a successful call to media_cache_read(), the \a buffer member of the param block
//! points into a media cache entry. The caller can read directly out of this buffer without
//! worry about the contents changing, because the cache entry is locked from further access
//! until this function is called to unlock it. After this function returns, the buffer
//! should not be used as its contents may change at any moment.
//!
//! \param token The \a token member of the #MediaCacheParamBlock_t structure that was
//!     returned from a media_cache_read() call. This token value uniquely identifies which
//!     cache entry to unlock.
//! \retval SUCCESS The specified cache entry was unlocked.
    RtStatus_t media_cache_release(uint32_t token);

    RtStatus_t media_cache_resume(void);
    RtStatus_t media_cache_increase(int32_t cacheNumIncreased);
    RtStatus_t media_cache_DiscardDrive(int32_t iDrive);
#ifdef __cplusplus
}
#endif
////////////////////////////////////////////////////////////////////////////////// End of file////////////////////////////////////////////////////////////////////////////////
#endif                          // _media_cache_h_
//! @}
