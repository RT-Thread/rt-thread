/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-11-12     Bernard      The first version
 */

#ifndef LIBC_ERRNO_H__
#define LIBC_ERRNO_H__

#include <rtconfig.h>

#if defined(RT_USING_NEWLIB) || defined(_WIN32) || (defined( __GNUC__ ) && !defined(__ARMCC_VERSION))
/* use errno.h file in toolchains */
#include <errno.h>
#endif

#if defined(__CC_ARM)
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

#if !defined(RT_USING_NEWLIB) && !defined(_WIN32) && !(defined( __GNUC__ ) && !defined(__ARMCC_VERSION))

#define EPERM            (ERROR_BASE_NO + 1)
#define ENOENT           (ERROR_BASE_NO + 2)
#define ESRCH            (ERROR_BASE_NO + 3)
#define EINTR            (ERROR_BASE_NO + 4)
#define EIO              (ERROR_BASE_NO + 5)
#define ENXIO            (ERROR_BASE_NO + 6)
#define E2BIG            (ERROR_BASE_NO + 7)
#define ENOEXEC          (ERROR_BASE_NO + 8)
#define EBADF            (ERROR_BASE_NO + 9)
#define ECHILD          (ERROR_BASE_NO + 10)
#define EAGAIN          (ERROR_BASE_NO + 11)

#ifndef ENOMEM
#define ENOMEM          (ERROR_BASE_NO + 12)
#endif

#define EACCES          (ERROR_BASE_NO + 13)
#define EFAULT          (ERROR_BASE_NO + 14)
#define ENOTBLK         (ERROR_BASE_NO + 15)
#define EBUSY           (ERROR_BASE_NO + 16)
#define EEXIST          (ERROR_BASE_NO + 17)
#define EXDEV           (ERROR_BASE_NO + 18)
#define ENODEV          (ERROR_BASE_NO + 19)
#define ENOTDIR         (ERROR_BASE_NO + 20)
#define EISDIR          (ERROR_BASE_NO + 21)

#ifndef EINVAL
#define EINVAL          (ERROR_BASE_NO + 22)
#endif

#define ENFILE          (ERROR_BASE_NO + 23)
#define EMFILE          (ERROR_BASE_NO + 24)
#define ENOTTY          (ERROR_BASE_NO + 25)
#define ETXTBSY         (ERROR_BASE_NO + 26)
#define EFBIG           (ERROR_BASE_NO + 27)
#define ENOSPC          (ERROR_BASE_NO + 28)
#define ESPIPE          (ERROR_BASE_NO + 29)
#define EROFS           (ERROR_BASE_NO + 30)
#define EMLINK          (ERROR_BASE_NO + 31)
#define EPIPE           (ERROR_BASE_NO + 32)

#ifndef EDOM
#define EDOM            (ERROR_BASE_NO + 33)
#endif

#ifndef ERANGE
#define ERANGE          (ERROR_BASE_NO + 34)
#endif

#define EDEADLK         (ERROR_BASE_NO + 35)
#define ENAMETOOLONG    (ERROR_BASE_NO + 36)
#define ENOLCK          (ERROR_BASE_NO + 37)
#define ENOSYS          (ERROR_BASE_NO + 38)
#define ENOTEMPTY       (ERROR_BASE_NO + 39)
#define ELOOP           (ERROR_BASE_NO + 40)
#define EWOULDBLOCK     EAGAIN
#define ENOMSG          (ERROR_BASE_NO + 42)
#define EIDRM           (ERROR_BASE_NO + 43)
#define ECHRNG          (ERROR_BASE_NO + 44)
#define EL2NSYNC        (ERROR_BASE_NO + 45)
#define EL3HLT          (ERROR_BASE_NO + 46)
#define EL3RST          (ERROR_BASE_NO + 47)
#define ELNRNG          (ERROR_BASE_NO + 48)
#define EUNATCH         (ERROR_BASE_NO + 49)
#define ENOCSI          (ERROR_BASE_NO + 50)
#define EL2HLT          (ERROR_BASE_NO + 51)
#define EBADE           (ERROR_BASE_NO + 52)
#define EBADR           (ERROR_BASE_NO + 53)
#define EXFULL          (ERROR_BASE_NO + 54)
#define ENOANO          (ERROR_BASE_NO + 55)
#define EBADRQC         (ERROR_BASE_NO + 56)
#define EBADSLT         (ERROR_BASE_NO + 57)
#define EDEADLOCK       EDEADLK
#define EBFONT          (ERROR_BASE_NO + 59)
#define ENOSTR          (ERROR_BASE_NO + 60)
#define ENODATA         (ERROR_BASE_NO + 61)
#define ETIME           (ERROR_BASE_NO + 62)
#define ENOSR           (ERROR_BASE_NO + 63)
#define ENONET          (ERROR_BASE_NO + 64)
#define ENOPKG          (ERROR_BASE_NO + 65)
#define EREMOTE         (ERROR_BASE_NO + 66)
#define ENOLINK         (ERROR_BASE_NO + 67)
#define EADV            (ERROR_BASE_NO + 68)
#define ESRMNT          (ERROR_BASE_NO + 69)
#define ECOMM           (ERROR_BASE_NO + 70)
#define EPROTO          (ERROR_BASE_NO + 71)
#define EMULTIHOP       (ERROR_BASE_NO + 72)
#define EDOTDOT         (ERROR_BASE_NO + 73)
#define EBADMSG         (ERROR_BASE_NO + 74)
#define EOVERFLOW       (ERROR_BASE_NO + 75)
#define ENOTUNIQ        (ERROR_BASE_NO + 76)
#define EBADFD          (ERROR_BASE_NO + 77)
#define EREMCHG         (ERROR_BASE_NO + 78)
#define ELIBACC         (ERROR_BASE_NO + 79)
#define ELIBBAD         (ERROR_BASE_NO + 80)
#define ELIBSCN         (ERROR_BASE_NO + 81)
#define ELIBMAX         (ERROR_BASE_NO + 82)
#define ELIBEXEC        (ERROR_BASE_NO + 83)

#ifndef EILSEQ
#define EILSEQ          (ERROR_BASE_NO + 84)
#endif

#define ERESTART        (ERROR_BASE_NO + 85)
#define ESTRPIPE        (ERROR_BASE_NO + 86)
#define EUSERS          (ERROR_BASE_NO + 87)
#define ENOTSOCK        (ERROR_BASE_NO + 88)
#define EDESTADDRREQ    (ERROR_BASE_NO + 89)
#define EMSGSIZE        (ERROR_BASE_NO + 90)
#define EPROTOTYPE      (ERROR_BASE_NO + 91)
#define ENOPROTOOPT     (ERROR_BASE_NO + 92)
#define EPROTONOSUPPORT (ERROR_BASE_NO + 93)
#define ESOCKTNOSUPPORT (ERROR_BASE_NO + 94)
#define EOPNOTSUPP      (ERROR_BASE_NO + 95)
#define ENOTSUP         EOPNOTSUPP
#define EPFNOSUPPORT    (ERROR_BASE_NO + 96)
#define EAFNOSUPPORT    (ERROR_BASE_NO + 97)
#define EADDRINUSE      (ERROR_BASE_NO + 98)
#define EADDRNOTAVAIL   (ERROR_BASE_NO + 99)
#define ENETDOWN        (ERROR_BASE_NO + 100)
#define ENETUNREACH     (ERROR_BASE_NO + 101)
#define ENETRESET       (ERROR_BASE_NO + 102)
#define ECONNABORTED    (ERROR_BASE_NO + 103)
#define ECONNRESET      (ERROR_BASE_NO + 104)
#define ENOBUFS         (ERROR_BASE_NO + 105)
#define EISCONN         (ERROR_BASE_NO + 106)
#define ENOTCONN        (ERROR_BASE_NO + 107)
#define ESHUTDOWN       (ERROR_BASE_NO + 108)
#define ETOOMANYREFS    (ERROR_BASE_NO + 109)
#define ETIMEDOUT       (ERROR_BASE_NO + 110)
#define ECONNREFUSED    (ERROR_BASE_NO + 111)
#define EHOSTDOWN       (ERROR_BASE_NO + 112)
#define EHOSTUNREACH    (ERROR_BASE_NO + 113)
#define EALREADY        (ERROR_BASE_NO + 114)
#define EINPROGRESS     (ERROR_BASE_NO + 115)
#define ESTALE          (ERROR_BASE_NO + 116)
#define EUCLEAN         (ERROR_BASE_NO + 117)
#define ENOTNAM         (ERROR_BASE_NO + 118)
#define ENAVAIL         (ERROR_BASE_NO + 119)
#define EISNAM          (ERROR_BASE_NO + 120)
#define EREMOTEIO       (ERROR_BASE_NO + 121)
#define EDQUOT          (ERROR_BASE_NO + 122)
#define ENOMEDIUM       (ERROR_BASE_NO + 123)
#define EMEDIUMTYPE     (ERROR_BASE_NO + 124)
#define ECANCELED       (ERROR_BASE_NO + 125)
#define ENOKEY          (ERROR_BASE_NO + 126)
#define EKEYEXPIRED     (ERROR_BASE_NO + 127)
#define EKEYREVOKED     (ERROR_BASE_NO + 128)
#define EKEYREJECTED    (ERROR_BASE_NO + 129)
#define EOWNERDEAD      (ERROR_BASE_NO + 130)
#define ENOTRECOVERABLE (ERROR_BASE_NO + 131)
#define ERFKILL         (ERROR_BASE_NO + 132)
#define EHWPOISON       (ERROR_BASE_NO + 133)

#endif

#endif
