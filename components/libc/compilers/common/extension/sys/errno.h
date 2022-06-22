/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-22     Meco Man     The first version.
 */

#ifndef __SYS_ERRNO_H__
#define __SYS_ERRNO_H__

#if defined(__ARMCC_VERSION)
/*
defined in armcc/errno.h

#define EDOM    1
#define ERANGE  2
#define EILSEQ  4
#define ESIGNUM 3
#define EINVAL  5
#define ENOMEM  6
*/

#define ERROR_BASE_NO    7

#elif defined(__IAR_SYSTEMS_ICC__)
/* defined in iar/errno.h
#define EDOM    33
#define ERANGE  34
#define EFPOS   35
#define EILSEQ  36
*/
#define ERROR_BASE_NO    36

#else
#define ERROR_BASE_NO    0
#endif

#if defined(__ARMCC_VERSION) || defined(__IAR_SYSTEMS_ICC__)
#include <errno.h>

#ifndef EPERM
#define EPERM            (ERROR_BASE_NO + 1)
#endif

#ifndef ENOENT
#define ENOENT           (ERROR_BASE_NO + 2)
#endif

#ifndef ESRCH
#define ESRCH            (ERROR_BASE_NO + 3)
#endif

#ifndef EINTR
#define EINTR            (ERROR_BASE_NO + 4)
#endif

#ifndef EIO
#define EIO              (ERROR_BASE_NO + 5)
#endif

#ifndef ENXIO
#define ENXIO            (ERROR_BASE_NO + 6)
#endif

#ifndef E2BIG
#define E2BIG            (ERROR_BASE_NO + 7)
#endif

#ifndef ENOEXEC
#define ENOEXEC          (ERROR_BASE_NO + 8)
#endif

#ifndef EBADF
#define EBADF            (ERROR_BASE_NO + 9)
#endif

#ifndef ECHILD
#define ECHILD          (ERROR_BASE_NO + 10)
#endif

#ifndef EAGAIN
#define EAGAIN          (ERROR_BASE_NO + 11)
#endif

#ifndef ENOMEM
#define ENOMEM          (ERROR_BASE_NO + 12)
#endif

#ifndef EACCES
#define EACCES          (ERROR_BASE_NO + 13)
#endif

#ifndef EFAULT
#define EFAULT          (ERROR_BASE_NO + 14)
#endif

#ifndef ENOTBLK
#define ENOTBLK         (ERROR_BASE_NO + 15)
#endif

#ifndef EBUSY
#define EBUSY           (ERROR_BASE_NO + 16)
#endif

#ifndef EEXIST
#define EEXIST          (ERROR_BASE_NO + 17)
#endif

#ifndef EXDEV
#define EXDEV           (ERROR_BASE_NO + 18)
#endif

#ifndef ENODEV
#define ENODEV          (ERROR_BASE_NO + 19)
#endif

#ifndef ENOTDIR
#define ENOTDIR         (ERROR_BASE_NO + 20)
#endif

#ifndef EISDIR
#define EISDIR          (ERROR_BASE_NO + 21)
#endif

#ifndef EINVAL
#define EINVAL          (ERROR_BASE_NO + 22)
#endif

#ifndef ENFILE
#define ENFILE          (ERROR_BASE_NO + 23)
#endif

#ifndef EMFILE
#define EMFILE          (ERROR_BASE_NO + 24)
#endif

#ifndef ENOTTY
#define ENOTTY          (ERROR_BASE_NO + 25)
#endif

#ifndef ETXTBSY
#define ETXTBSY         (ERROR_BASE_NO + 26)
#endif

#ifndef EFBIG
#define EFBIG           (ERROR_BASE_NO + 27)
#endif

#ifndef ENOSPC
#define ENOSPC          (ERROR_BASE_NO + 28)
#endif

#ifndef ESPIPE
#define ESPIPE          (ERROR_BASE_NO + 29)
#endif

#ifndef EROFS
#define EROFS           (ERROR_BASE_NO + 30)
#endif

#ifndef EMLINK
#define EMLINK          (ERROR_BASE_NO + 31)
#endif

#ifndef EPIPE
#define EPIPE           (ERROR_BASE_NO + 32)
#endif

#ifndef EDOM
#define EDOM            (ERROR_BASE_NO + 33)
#endif

#ifndef ERANGE
#define ERANGE          (ERROR_BASE_NO + 34)
#endif

#ifndef EDEADLK
#define EDEADLK         (ERROR_BASE_NO + 35)
#endif

#ifndef ENAMETOOLONG
#define ENAMETOOLONG    (ERROR_BASE_NO + 36)
#endif

#ifndef ENOLCK
#define ENOLCK          (ERROR_BASE_NO + 37)
#endif

#ifndef ENOSYS
#define ENOSYS          (ERROR_BASE_NO + 38)
#endif

#ifndef ENOTEMPTY
#define ENOTEMPTY       (ERROR_BASE_NO + 39)
#endif

#ifndef ELOOP
#define ELOOP           (ERROR_BASE_NO + 40)
#endif

#ifndef EWOULDBLOCK
#define EWOULDBLOCK     EAGAIN
#endif

#ifndef ENOMSG
#define ENOMSG          (ERROR_BASE_NO + 42)
#endif

#ifndef EIDRM
#define EIDRM           (ERROR_BASE_NO + 43)
#endif

#ifndef ECHRNG
#define ECHRNG          (ERROR_BASE_NO + 44)
#endif

#ifndef EL2NSYNC
#define EL2NSYNC        (ERROR_BASE_NO + 45)
#endif

#ifndef EL3HLT
#define EL3HLT          (ERROR_BASE_NO + 46)
#endif

#ifndef EL3RST
#define EL3RST          (ERROR_BASE_NO + 47)
#endif

#ifndef ELNRNG
#define ELNRNG          (ERROR_BASE_NO + 48)
#endif

#ifndef EUNATCH
#define EUNATCH         (ERROR_BASE_NO + 49)
#endif

#ifndef ENOCSI
#define ENOCSI          (ERROR_BASE_NO + 50)
#endif

#ifndef EL2HLT
#define EL2HLT          (ERROR_BASE_NO + 51)
#endif

#ifndef EBADE
#define EBADE           (ERROR_BASE_NO + 52)
#endif

#ifndef EBADR
#define EBADR           (ERROR_BASE_NO + 53)
#endif

#ifndef EXFULL
#define EXFULL          (ERROR_BASE_NO + 54)
#endif

#ifndef ENOANO
#define ENOANO          (ERROR_BASE_NO + 55)
#endif

#ifndef EBADRQC
#define EBADRQC         (ERROR_BASE_NO + 56)
#endif

#ifndef EBADSLT
#define EBADSLT         (ERROR_BASE_NO + 57)
#endif

#ifndef EDEADLOCK
#define EDEADLOCK       EDEADLK
#endif

#ifndef EBFONT
#define EBFONT          (ERROR_BASE_NO + 59)
#endif

#ifndef ENOSTR
#define ENOSTR          (ERROR_BASE_NO + 60)
#endif

#ifndef ENODATA
#define ENODATA         (ERROR_BASE_NO + 61)
#endif

#ifndef ETIME
#define ETIME           (ERROR_BASE_NO + 62)
#endif

#ifndef ENOSR
#define ENOSR           (ERROR_BASE_NO + 63)
#endif

#ifndef ENONET
#define ENONET          (ERROR_BASE_NO + 64)
#endif

#ifndef ENOPKG
#define ENOPKG          (ERROR_BASE_NO + 65)
#endif

#ifndef EREMOTE
#define EREMOTE         (ERROR_BASE_NO + 66)
#endif

#ifndef ENOLINK
#define ENOLINK         (ERROR_BASE_NO + 67)
#endif

#ifndef EADV
#define EADV            (ERROR_BASE_NO + 68)
#endif

#ifndef ESRMNT
#define ESRMNT          (ERROR_BASE_NO + 69)
#endif

#ifndef ECOMM
#define ECOMM           (ERROR_BASE_NO + 70)
#endif

#ifndef EPROTO
#define EPROTO          (ERROR_BASE_NO + 71)
#endif

#ifndef EMULTIHOP
#define EMULTIHOP       (ERROR_BASE_NO + 72)
#endif

#ifndef EDOTDOT
#define EDOTDOT         (ERROR_BASE_NO + 73)
#endif

#ifndef EBADMSG
#define EBADMSG         (ERROR_BASE_NO + 74)
#endif

#ifndef EOVERFLOW
#define EOVERFLOW       (ERROR_BASE_NO + 75)
#endif

#ifndef ENOTUNIQ
#define ENOTUNIQ        (ERROR_BASE_NO + 76)
#endif

#ifndef EBADFD
#define EBADFD          (ERROR_BASE_NO + 77)
#endif

#ifndef EREMCHG
#define EREMCHG         (ERROR_BASE_NO + 78)
#endif

#ifndef ELIBACC
#define ELIBACC         (ERROR_BASE_NO + 79)
#endif

#ifndef ELIBBAD
#define ELIBBAD         (ERROR_BASE_NO + 80)
#endif

#ifndef ELIBSCN
#define ELIBSCN         (ERROR_BASE_NO + 81)
#endif

#ifndef ELIBMAX
#define ELIBMAX         (ERROR_BASE_NO + 82)
#endif

#ifndef ELIBEXEC
#define ELIBEXEC        (ERROR_BASE_NO + 83)
#endif

#ifndef EILSEQ
#define EILSEQ          (ERROR_BASE_NO + 84)
#endif

#ifndef ERESTART
#define ERESTART        (ERROR_BASE_NO + 85)
#endif

#ifndef ESTRPIPE
#define ESTRPIPE        (ERROR_BASE_NO + 86)
#endif

#ifndef EUSERS
#define EUSERS          (ERROR_BASE_NO + 87)
#endif

#ifndef ENOTSOCK
#define ENOTSOCK        (ERROR_BASE_NO + 88)
#endif

#ifndef EDESTADDRREQ
#define EDESTADDRREQ    (ERROR_BASE_NO + 89)
#endif

#ifndef EMSGSIZE
#define EMSGSIZE        (ERROR_BASE_NO + 90)
#endif

#ifndef EPROTOTYPE
#define EPROTOTYPE      (ERROR_BASE_NO + 91)
#endif

#ifndef ENOPROTOOPT
#define ENOPROTOOPT     (ERROR_BASE_NO + 92)
#endif

#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT (ERROR_BASE_NO + 93)
#endif

#ifndef ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT (ERROR_BASE_NO + 94)
#endif

#ifndef EOPNOTSUPP
#define EOPNOTSUPP      (ERROR_BASE_NO + 95)
#endif

#ifndef ENOTSUP
#define ENOTSUP         EOPNOTSUPP
#endif

#ifndef EPFNOSUPPORT
#define EPFNOSUPPORT    (ERROR_BASE_NO + 96)
#endif

#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT    (ERROR_BASE_NO + 97)
#endif

#ifndef EADDRINUSE
#define EADDRINUSE      (ERROR_BASE_NO + 98)
#endif

#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL   (ERROR_BASE_NO + 99)
#endif

#ifndef ENETDOWN
#define ENETDOWN        (ERROR_BASE_NO + 100)
#endif

#ifndef ENETUNREACH
#define ENETUNREACH     (ERROR_BASE_NO + 101)
#endif

#ifndef ENETRESET
#define ENETRESET       (ERROR_BASE_NO + 102)
#endif

#ifndef ECONNABORTED
#define ECONNABORTED    (ERROR_BASE_NO + 103)
#endif

#ifndef ECONNRESET
#define ECONNRESET      (ERROR_BASE_NO + 104)
#endif

#ifndef ENOBUFS
#define ENOBUFS         (ERROR_BASE_NO + 105)
#endif

#ifndef EISCONN
#define EISCONN         (ERROR_BASE_NO + 106)
#endif

#ifndef ENOTCONN
#define ENOTCONN        (ERROR_BASE_NO + 107)
#endif

#ifndef ESHUTDOWN
#define ESHUTDOWN       (ERROR_BASE_NO + 108)
#endif

#ifndef ETOOMANYREFS
#define ETOOMANYREFS    (ERROR_BASE_NO + 109)
#endif

#ifndef ETIMEDOUT
#define ETIMEDOUT       (ERROR_BASE_NO + 110)
#endif

#ifndef ECONNREFUSED
#define ECONNREFUSED    (ERROR_BASE_NO + 111)
#endif

#ifndef EHOSTDOWN
#define EHOSTDOWN       (ERROR_BASE_NO + 112)
#endif

#ifndef EHOSTUNREACH
#define EHOSTUNREACH    (ERROR_BASE_NO + 113)
#endif

#ifndef EALREADY
#define EALREADY        (ERROR_BASE_NO + 114)
#endif

#ifndef EINPROGRESS
#define EINPROGRESS     (ERROR_BASE_NO + 115)
#endif

#ifndef ESTALE
#define ESTALE          (ERROR_BASE_NO + 116)
#endif

#ifndef EUCLEAN
#define EUCLEAN         (ERROR_BASE_NO + 117)
#endif

#ifndef ENOTNAM
#define ENOTNAM         (ERROR_BASE_NO + 118)
#endif

#ifndef ENAVAIL
#define ENAVAIL         (ERROR_BASE_NO + 119)
#endif

#ifndef EISNAM
#define EISNAM          (ERROR_BASE_NO + 120)
#endif

#ifndef EREMOTEIO
#define EREMOTEIO       (ERROR_BASE_NO + 121)
#endif

#ifndef EDQUOT
#define EDQUOT          (ERROR_BASE_NO + 122)
#endif

#ifndef ENOMEDIUM
#define ENOMEDIUM       (ERROR_BASE_NO + 123)
#endif

#ifndef EMEDIUMTYPE
#define EMEDIUMTYPE     (ERROR_BASE_NO + 124)
#endif

#ifndef ECANCELED
#define ECANCELED       (ERROR_BASE_NO + 125)
#endif

#ifndef ENOKEY
#define ENOKEY          (ERROR_BASE_NO + 126)
#endif

#ifndef EKEYEXPIRED
#define EKEYEXPIRED     (ERROR_BASE_NO + 127)
#endif

#ifndef EKEYREVOKED
#define EKEYREVOKED     (ERROR_BASE_NO + 128)
#endif

#ifndef EKEYREJECTED
#define EKEYREJECTED    (ERROR_BASE_NO + 129)
#endif

#ifndef EOWNERDEAD
#define EOWNERDEAD      (ERROR_BASE_NO + 130)
#endif

#ifndef ENOTRECOVERABLE
#define ENOTRECOVERABLE (ERROR_BASE_NO + 131)
#endif

#ifndef ERFKILL
#define ERFKILL         (ERROR_BASE_NO + 132)
#endif

#ifndef EHWPOISON
#define EHWPOISON       (ERROR_BASE_NO + 133)
#endif

#elif defined(_WIN32)
#include <errno.h>

#endif /* defined(__ARMCC_VERSION) || defined(__IAR_SYSTEMS_ICC__) */

#endif /* __SYS_ERRNO_H__ */
