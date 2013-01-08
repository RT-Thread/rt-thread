/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  UFFS is free software; you can redistribute it and/or modify it under
  the GNU Library General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any
  later version.

  UFFS is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  or GNU Library General Public License, as applicable, for more details.
 
  You should have received a copy of the GNU General Public License
  and GNU Library General Public License along with UFFS; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301, USA.

  As a special exception, if other files instantiate templates or use
  macros or inline functions from this file, or you compile this file
  and link it with other works to produce a work based on this file,
  this file does not by itself cause the resulting work to be covered
  by the GNU General Public License. However the source code for this
  file must still be made available in accordance with section (3) of
  the GNU General Public License v2.
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/
/** 
 * \file uffs.h
 * \brief uffs basic defines
 * \author Ricky Zheng
 */

#ifndef _UFFS_H_
#define _UFFS_H_

#ifdef __cplusplus
extern "C"{
#endif

#define UO_RDONLY		0x0000		/** read only */
#define UO_WRONLY		0x0001		/** write only */
#define UO_RDWR			0x0002		/** read and write */
#define UO_APPEND		0x0008		/** append */

#define UO_BINARY		0x0000		/** no used in uffs */

#define UO_CREATE		0x0100
#define UO_TRUNC		0x0200
#define UO_EXCL			0x0400

#define UO_NOECC		0x0800		/** skip ECC when reading file data from media */


#define UO_DIR			0x1000		/** open a directory */



#define UENOERR 0		/** no error */
#define UEACCES	1		/** Tried to open read-only file
						 for writing, or files sharing mode
						 does not allow specified operations,
						 or given path is directory */

#define UEEXIST	2		/** _O_CREAT and _O_EXCL flags specified,
							but filename already exists */
#define UEINVAL	3		/** Invalid oflag or pmode argument */
#define UEMFILE	4		/** No more file handles available
						  (too many open files)  */
#define UENOENT	5		/** file or path not found */
#define UETIME	6		/** can't set file time */
#define UEBADF	9		/** invalid file handle */
#define UENOMEM	10		/** no enough memory */
#define UEIOERR	11		/** I/O error from lower level flash operation */
#define UENOTDIR 12		/** Not a directory */
#define UEISDIR 13		/** Is a directory */    

#define UEUNKNOWN_ERR	100	/** unknown error */



#define _SEEK_CUR		0		/** seek from current position */
#define _SEEK_SET		1		/** seek from beginning of file */
#define _SEEK_END		2		/** seek from end of file */

#define USEEK_CUR		_SEEK_CUR
#define USEEK_SET		_SEEK_SET
#define USEEK_END		_SEEK_END


#ifdef __cplusplus
}
#endif


#endif

