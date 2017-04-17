/*
 * Copyright (c) 2004, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/**
 * \file
 *         CFS header file.
 * \author
 *         Adam Dunkels <adam@sics.se>
 *
 */

/**
 * \addtogroup sys
 * @{
 */

/**
 * \defgroup cfs The Contiki file system interface
 *
 * The Contiki file system interface (CFS) defines an abstract API for
 * reading directories and for reading and writing files. The CFS API
 * is intentionally simple. The CFS API is modeled after the POSIX
 * file API, and slightly simplified.
 *
 * @{
 */

#ifndef CFS_H_
#define CFS_H_

//#include "contiki.h"
#include <stdint.h>
#include <stddef.h>

#include "cfs-coffee_arch.h"

#ifndef CFS_CONF_OFFSET_TYPE
typedef int cfs_offset_t;
#else
typedef CFS_CONF_OFFSET_TYPE cfs_offset_t;
#endif

#ifndef CCIF
#   define CCIF
#endif



/* Micro logs enable modifications on storage types that do not support
   in-place updates. This applies primarily to flash memories. */
#ifndef COFFEE_MICRO_LOGS
#define COFFEE_MICRO_LOGS 1
#endif

/* If the files are expected to be appended to only, this parameter
   can be set to save some code space. */
#ifndef COFFEE_APPEND_ONLY
#define COFFEE_APPEND_ONLY  0
#endif

#if COFFEE_MICRO_LOGS && COFFEE_APPEND_ONLY
#error "Cannot have COFFEE_APPEND_ONLY set when COFFEE_MICRO_LOGS is set."
#endif

/* I/O semantics can be set on file descriptors in order to optimize
   file access on certain storage types. */
#ifndef COFFEE_IO_SEMANTICS
#define COFFEE_IO_SEMANTICS 0
#endif

/*
 * Prevent sectors from being erased directly after file removal.
 * This will level the wear across sectors better, but may lead
 * to longer garbage collection procedures.
 */
#ifndef COFFEE_EXTENDED_WEAR_LEVELLING
#define COFFEE_EXTENDED_WEAR_LEVELLING  1
#endif

//#if COFFEE_START & (COFFEE_SECTOR_SIZE - 1)
//#error COFFEE_START must point to the first byte in a sector.
//#endif

struct cfs_dir {
  char dummy_space[32];
};

struct cfs_dirent {
  char name[32];
  cfs_offset_t size;
};

/* The structure of cached file objects. */
struct file {
  cfs_offset_t end;
  coffee_page_t page;
  coffee_page_t max_pages;
  int16_t record_count;
  uint8_t references;
  uint8_t flags;
};


/* The file descriptor structure. */
struct file_desc
{
  cfs_offset_t offset;
  struct file *file;
  uint8_t flags;
#if COFFEE_IO_SEMANTICS
  uint8_t io_flags;
#endif
};

/* The file header structure mimics the representation of file headers
   in the physical storage medium. */
struct file_header {
  coffee_page_t log_page;
  uint16_t log_records;
  uint16_t log_record_size;
  coffee_page_t max_pages;
  uint8_t deprecated_eof_hint;
  uint8_t flags;
  char name[COFFEE_NAME_LENGTH];
};

typedef struct {
    int                 fd;
    struct file_desc   *desc;
}CFS_FILE;

/**
 * Specify that cfs_open() should open a file for reading.
 *
 * This constant indicates to cfs_open() that a file should be opened
 * for reading. CFS_WRITE should be used if the file is opened for
 * writing, and CFS_READ + CFS_WRITE indicates that the file is opened
 * for both reading and writing.
 *
 * \sa cfs_open()
 */
#ifndef CFS_READ
#define CFS_READ  1
#endif

/**
 * Specify that cfs_open() should open a file for writing.
 *
 * This constant indicates to cfs_open() that a file should be opened
 * for writing. CFS_READ should be used if the file is opened for
 * reading, and CFS_READ + CFS_WRITE indicates that the file is opened
 * for both reading and writing.
 *
 * \sa cfs_open()
 */
#ifndef CFS_WRITE
#define CFS_WRITE 2
#endif

/**
 * Specify that cfs_open() should append written data to the file rather than overwriting it.
 *
 * This constant indicates to cfs_open() that a file that should be
 * opened for writing gets written data appended to the end of the
 * file. The default behaviour (without CFS_APPEND) is that the file
 * is overwritten with the new data.
 *
 * \sa cfs_open()
 */
#ifndef CFS_APPEND
#define CFS_APPEND 4
#endif

/**
 * Specify that cfs_seek() should compute the offset from the beginning of the file.
 *
 * \sa cfs_seek()
 */
#ifndef CFS_SEEK_SET
#define CFS_SEEK_SET 0
#endif

/**
 * Specify that cfs_seek() should compute the offset from the current position of the file pointer.
 *
 * \sa cfs_seek()
 */
#ifndef CFS_SEEK_CUR
#define CFS_SEEK_CUR 1
#endif

/**
 * Specify that cfs_seek() should compute the offset from the end of the file.
 *
 * \sa cfs_seek()
 */
#ifndef CFS_SEEK_END
#define CFS_SEEK_END 2
#endif

/**
 * \brief      Open a file.
 * \param name The name of the file.
 * \param flags CFS_READ, or CFS_WRITE/CFS_APPEND, or both.
 * \return     A file descriptor, if the file could be opened, or -1 if
 *             the file could not be opened.
 *
 *             This function opens a file and returns a file
 *             descriptor for the opened file. If the file could not
 *             be opened, the function returns -1. The function can
 *             open a file for reading or writing, or both.
 *
 *             An opened file must be closed with cfs_close().
 *
 * \sa         CFS_READ
 * \sa         CFS_WRITE
 * \sa         cfs_close()
 */
#ifndef cfs_open
CCIF int cfs_open(const char *name, int flags);
#endif

/**
 * \brief      Close an open file.
 * \param fd   The file descriptor of the open file.
 *
 *             This function closes a file that has previously been
 *             opened with cfs_open().
 */
#ifndef cfs_close
CCIF void cfs_close(int fd);
#endif

/**
 * \brief      Read data from an open file.
 * \param fd   The file descriptor of the open file.
 * \param buf  The buffer in which data should be read from the file.
 * \param len  The number of bytes that should be read.
 * \return     The number of bytes that was actually read from the file.
 *
 *             This function reads data from an open file into a
 *             buffer. The file must have first been opened with
 *             cfs_open() and the CFS_READ flag.
 */
#ifndef cfs_read
CCIF int cfs_read(int fd, void *buf, unsigned int len);
#endif

/**
 * \brief      Write data to an open file.
 * \param fd   The file descriptor of the open file.
 * \param buf  The buffer from which data should be written to the file.
 * \param len  The number of bytes that should be written.
 * \return     The number of bytes that was actually written to the file.
 *
 *             This function reads writes data from a memory buffer to
 *             an open file. The file must have been opened with
 *             cfs_open() and the CFS_WRITE flag.
 */
#ifndef cfs_write
CCIF int cfs_write(int fd, const void *buf, unsigned int len);
#endif

/**
 * \brief      Seek to a specified position in an open file.
 * \param fd   The file descriptor of the open file.
 * \param offset A position, either relative or absolute, in the file.
 * \param whence Determines how to interpret the offset parameter.
 * \return     The new position in the file, or (cfs_offset_t)-1 if the seek failed.
 *
 *             This function moves the file position to the specified
 *             position in the file. The next byte that is read from
 *             or written to the file will be at the position given
 *             determined by the combination of the offset parameter
 *             and the whence parameter.
 *
 * \sa         CFS_SEEK_CUR
 * \sa         CFS_SEEK_END
 * \sa         CFS_SEEK_SET
 */
#ifndef cfs_seek
CCIF cfs_offset_t cfs_seek(int fd, cfs_offset_t offset, int whence);
#endif

/**
 * \brief      Remove a file.
 * \param name The name of the file.
 * \retval 0   If the file was removed.
 * \return -1  If the file could not be removed or if it doesn't exist.
 */
#ifndef cfs_remove
CCIF int cfs_remove(const char *name);
#endif

/**
 * \brief      Open a directory for reading directory entries.
 * \param dirp A pointer to a struct cfs_dir that is filled in by the function.
 * \param name The name of the directory.
 * \return     0 or -1 if the directory could not be opened.
 *
 * \sa         cfs_readdir()
 * \sa         cfs_closedir()
 */
#ifndef cfs_opendir
CCIF int cfs_opendir(struct cfs_dir *dirp, const char *name);
#endif

/**
 * \brief      Read a directory entry
 * \param dirp A pointer to a struct cfs_dir that has been opened with cfs_opendir().
 * \param dirent A pointer to a struct cfs_dirent that is filled in by cfs_readdir()
 * \retval 0   If a directory entry was read.
 * \retval -1  If no more directory entries can be read.
 *
 * \sa         cfs_opendir()
 * \sa         cfs_closedir()
 */
#ifndef cfs_readdir
CCIF int cfs_readdir(struct cfs_dir *dirp, struct cfs_dirent *dirent);
#endif

/**
 * \brief      Close a directory opened with cfs_opendir().
 * \param dirp A pointer to a struct cfs_dir that has been opened with cfs_opendir().
 *
 * \sa         cfs_opendir()
 * \sa         cfs_readdir()
 */
#ifndef cfs_closedir
CCIF void cfs_closedir(struct cfs_dir *dirp);
#endif

/**
 *  添加获取文件描述符接口
 */
#ifndef cfs_getdesc
CCIF struct file_desc* cfs_getdesc(int fd);
#endif

#endif /* CFS_H_ */

/** @} */
/** @} */
