 /**********************************************************************
 * Copyright (C) 2014-2015 Cadence Design Systems, Inc.- http://www.cadence.com
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ***********************************************************************
 * cdn_errno.h
 * Cadence error codes
 ***********************************************************************/

#ifndef __INCLUDE_CDN_ERRNO_H__
#define __INCLUDE_CDN_ERRNO_H__

#ifndef ERRNO_H_NOT_PRESENT
#include <errno.h>
#endif //ERRNO_H_NOT_PRESENT

#ifndef EOK
#define EOK             0      /* no error */
#endif //EOK

#ifndef EPERM
#define EPERM           1      /* Operation not permitted */
#endif //EPERM

#ifndef ENOENT
#define ENOENT          2      /* No such file or directory */
#endif //ENOENT

#ifndef EIO
#define EIO             5      /* I/O error */
#endif //EIO

#ifndef ENOEXEC
#define ENOEXEC         8      /* Exec format error */
#endif //ENOEXEC

#ifndef EAGAIN
#define EAGAIN          11      /* Try again */
#endif //EAGAIN

#ifndef ENOMEM
#define ENOMEM          12      /* Out of memory */
#endif //ENOMEM

#ifndef EFAULT
#define EFAULT          14      /* Bad address */
#endif //EFAULT

#ifndef EBUSY
#define EBUSY           16      /* Device or resource busy */
#endif //EBUSY

#ifndef EINVAL
#define EINVAL          22      /* Invalid argument */
#endif //EINVAL

#ifndef ENOSPC
#define ENOSPC          28      /* No space left on device */
#endif //ENOSPC

#ifndef EBADSLT
#define EBADSLT         57      /* Invalid slot */
#endif //EBADSLT

#ifndef EPROTO
#define EPROTO          71      /* Protocol error */
#endif //EPROTO

#ifndef EOVERFLOW
#define EOVERFLOW       75      /* Value too large for defined data type */
#endif //EOVERFLOW

#ifndef EOPNOTSUPP
#define EOPNOTSUPP      95      /* Operation not supported */
#endif //EOPNOTSUPP

#ifndef EINPROGRESS
#define EINPROGRESS     115     /* Operation now in progress */
#endif //EINPROGRESS

#ifndef EDQUOT
#define EDQUOT          122     /* Quota exceeded */
#endif //EDQUOT

#ifndef ENOTSUP
#define ENOTSUP         EOPNOTSUPP
#endif //ENOTSUP

#ifndef ECANCELED
#define ECANCELED       126      /* Cancelled */
#endif //ECANCELED

#endif //__INCLUDE_CDN_ERRNO_H__
