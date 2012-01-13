#ifndef CYGONCE_ERROR_CODES_H
#define CYGONCE_ERROR_CODES_H
/*===========================================================================
//
//      codes.h
//
//      Common error code definitions
//
//===========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####
// -------------------------------------------
// This file is part of eCos, the Embedded Configurable Operating System.
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 or (at your option) any later
// version.
//
// eCos is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License
// along with eCos; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
// As a special exception, if other files instantiate templates or use
// macros or inline functions from this file, or you compile this file
// and link it with other works to produce a work based on this file,
// this file does not by itself cause the resulting work to be covered by
// the GNU General Public License. However the source code for this file
// must still be made available in accordance with section (3) of the GNU
// General Public License v2.
//
// This exception does not invalidate any other reasons why a work based
// on this file might be covered by the GNU General Public License.
// -------------------------------------------
// ####ECOSGPLCOPYRIGHTEND####
//===========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):    jlarmour
// Contributors: jlarmour
// Date:         2000-04-14
// Purpose:      To provide a common set of error codes
// Description:  This provides a common set of error codes that all
//               packages can agree on. It doesn't preclude them defining
//               their own error return system, but this is a preferable
//               system to use to help error support be as general as
//               possible.
//
//               We try and conform to the ANSI/POSIX error code format,
//               namely starting with the character 'E'
//
// Usage:        #include <cyg/error/codes.h>
//
//               Example:
//
//               err=myfun();
//               if (err != ENOERR)
//               {
//                 str=strerror(err);
//                 printf("myfun returned error: %s\n", str);
//               }
//               else ....
//
//####DESCRIPTIONEND####
//
//=========================================================================*/

/* CONFIGURATION */

//#include <pkgconf/error.h>      prife    // Configuration header

#ifdef __cplusplus
extern "C" {
#endif

/* TYPE DEFINITIONS */

/* A type for error codes which may be useful to explain the purpose of
 * a variable or return code. It shows that it contains an error code
 * of the type defined below */

typedef int Cyg_ErrNo;


/* CONSTANT DEFINITIONS */

/* If adding to this list, you must also update strerror() with its text
 * If there is a common error of the same purpose on Unix, try and use its
 * name and number. If not, use one above 200 to prevent future conflicts
 *
 * Do not use negative numbers, so that functions can return positive on
 * success and -ESOMETHING on error, and it all works consistently.
*/

#define ENOERR           0     /* No error */
#define EPERM            1     /* Not permitted */
#define ENOENT           2     /* No such entity */
#define ESRCH            3     /* No such process */
#define EINTR            4     /* Operation interrupted */
#define EIO              5     /* I/O error */
#define EBADF            9     /* Bad file handle */
#define EAGAIN           11    /* Try again later */
#define EWOULDBLOCK      EAGAIN
#define ENOMEM           12    /* Out of memory */
#define EBUSY            16    /* Resource busy */
#define EXDEV            18    /* Cross-device link */
#define ENODEV           19    /* No such device */
#define ENOTDIR          20    /* Not a directory */
#define EISDIR           21    /* Is a directory */
#define EINVAL           22    /* Invalid argument */
#define ENFILE           23    /* Too many open files in system */
#define EMFILE           24    /* Too many open files */
#define EFBIG            27    /* File too large */
#define ENOSPC           28    /* No space left on device */
#define ESPIPE           29    /* Illegal seek */
#define EROFS            30    /* Read-only file system */
#define EDOM             33    /* Argument to math function outside valid */
                               /* domain */
#define ERANGE           34    /* Math result cannot be represented */
#define EDEADLK          35    /* Resource deadlock would occur */
#define EDEADLOCK        EDEADLK
#define ENOSYS           38    /* Function not implemented */
#define ENAMETOOLONG     60    /* File name too long */
#define ENOTEMPTY        66    /* Directory not empty */
#define ENOTSUP          95    /* Not supported error */
#define EEOF             200   /* End of file reached */
#define ENOSUPP          201   /* Operation not supported */
#define EDEVNOSUPP       202   /* Device does not support this operation */

/* Additional errors used by networking */
#define ENXIO            300   /* Device not configured */
#define EACCES           301   /* Permission denied */
#define EEXIST           302   /* File exists */
#define ENOTTY           303   /* Inappropriate ioctl for device */
#define EPIPE            304   /* Broken pipe */

/* non-blocking and interrupt i/o */
#define EINPROGRESS      310   /* Operation now in progress */
#define EALREADY         311   /* Operation already in progress */

/* ipc/network software -- argument errors */
#define ENOTSOCK         320   /* Socket operation on non-socket */
#define EDESTADDRREQ     321   /* Destination address required */
#define EMSGSIZE         322   /* Message too long */
#define EPROTOTYPE       323   /* Protocol wrong type for socket */
#define ENOPROTOOPT      324   /* Protocol not available */
#define EPROTONOSUPPORT  325   /* Protocol not supported */
#define ESOCKTNOSUPPORT  326   /* Socket type not supported */
#define EOPNOTSUPP       327   /* Operation not supported */
#define EPFNOSUPPORT     328   /* Protocol family not supported */
#define EAFNOSUPPORT     329   /* Address family not supported by */
                               /* protocol family */
#define EADDRINUSE       330   /* Address already in use */
#define EADDRNOTAVAIL    331   /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define ENETDOWN         350   /* Network is down */
#define ENETUNREACH      351   /* Network is unreachable */
#define ENETRESET        352   /* Network dropped connection on reset */
#define ECONNABORTED     353   /* Software caused connection abort */
#define ECONNRESET       354   /* Connection reset by peer */
#define ENOBUFS          355   /* No buffer space available */
#define EISCONN          356   /* Socket is already connected */
#define ENOTCONN         357   /* Socket is not connected */
#define ESHUTDOWN        358   /* Can't send after socket shutdown */
#define ETOOMANYREFS     359   /* Too many references: can't splice */
#define ETIMEDOUT        360   /* Operation timed out */
#define ECONNREFUSED     361   /* Connection refused */

#define EHOSTDOWN        364   /* Host is down */
#define EHOSTUNREACH     365   /* No route to host */

#ifdef __cplusplus
}   /* extern "C" */
#endif

#endif /* CYGONCE_ERROR_CODES_H multiple inclusion protection */

/* EOF codes.h */
