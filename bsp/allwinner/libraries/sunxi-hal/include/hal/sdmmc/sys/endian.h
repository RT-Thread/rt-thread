/*-
 * Copyright (c) 2002 Thomas Moestl <tmm@FreeBSD.org>
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: releng/10.1/sys/sys/endian.h 208331 2010-05-20 06:16:13Z phk $
 */

#ifndef _SYS_ENDIAN_H_
#define _SYS_ENDIAN_H_

#include <rtthread.h>
#include "sunxi_hal_common.h"

#ifdef CONFIG_RTTKERNEL

#ifndef _LITTLE_ENDIAN
#define _LITTLE_ENDIAN 1
#endif

#define _BYTE_ORDER _LITTLE_ENDIAN

#ifndef __bswap32

#if ((defined(__GNUC__) && !defined(__CC_ARM)))

#define __bswap16(x) ((uint16_t)__builtin_bswap16(x))
#define __bswap32(x) ((uint32_t)__builtin_bswap32(x))
#define __bswap64(x) ((uint64_t)__builtin_bswap64(x))

#else /* ((defined(__GNUC__) && !defined(__CC_ARM))) */

#define __bswap16(x) ((uint16_t)(                   \
    (((uint16_t)(x) & (uint16_t)0x00ffU) << 8) |    \
    (((uint16_t)(x) & (uint16_t)0xff00U) >> 8)))

#define __bswap32(x) ((uint32_t)(                       \
    (((uint32_t)(x) & (uint32_t)0x000000ffUL) << 24) |  \
    (((uint32_t)(x) & (uint32_t)0x0000ff00UL) <<  8) |  \
    (((uint32_t)(x) & (uint32_t)0x00ff0000UL) >>  8) |  \
    (((uint32_t)(x) & (uint32_t)0xff000000UL) >> 24)))

#define __bswap64(x) ((uint64_t)(                               \
    (((uint64_t)(x) & (uint64_t)0x00000000000000ffULL) << 56) | \
    (((uint64_t)(x) & (uint64_t)0x000000000000ff00ULL) << 40) | \
    (((uint64_t)(x) & (uint64_t)0x0000000000ff0000ULL) << 24) | \
    (((uint64_t)(x) & (uint64_t)0x00000000ff000000ULL) <<  8) | \
    (((uint64_t)(x) & (uint64_t)0x000000ff00000000ULL) >>  8) | \
    (((uint64_t)(x) & (uint64_t)0x0000ff0000000000ULL) >> 24) | \
    (((uint64_t)(x) & (uint64_t)0x00ff000000000000ULL) >> 40) | \
    (((uint64_t)(x) & (uint64_t)0xff00000000000000ULL) >> 56)))

#endif /* ((defined(__GNUC__) && !defined(__CC_ARM))) */

#else /* __bswap32 */

#undef __bswap32
#define __bswap32(x) (uint32_t)__builtin_bswap32(x)

#endif /* __bswap32 */

/*
 * General byte order swapping functions.
 */
#define bswap16(x)  __bswap16(x)
#define bswap32(x)  __bswap32(x)
#define bswap64(x)  __bswap64(x)

/*
 * Host to big endian, host to little endian, big endian to host, and little
 * endian to host byte order functions as detailed in byteorder(9).
 */
#if _BYTE_ORDER == _LITTLE_ENDIAN
#define htobe16(x)  bswap16((x))
#define htobe32(x)  bswap32((x))
#define htobe64(x)  bswap64((x))
#define htole16(x)  ((uint16_t)(x))
#define htole32(x)  ((uint32_t)(x))
#define htole64(x)  ((uint64_t)(x))

#define be16toh(x)  bswap16((x))
#define be32toh(x)  bswap32((x))
#define be64toh(x)  bswap64((x))
#define le16toh(x)  ((uint16_t)(x))
#define le32toh(x)  ((uint32_t)(x))
#define le64toh(x)  ((uint64_t)(x))
#elif (_BYTE_ORDER == _BIG_ENDIAN)
#define htobe16(x)  ((uint16_t)(x))
#define htobe32(x)  ((uint32_t)(x))
#define htobe64(x)  ((uint64_t)(x))
#define htole16(x)  bswap16((x))
#define htole32(x)  bswap32((x))
#define htole64(x)  bswap64((x))

#define be16toh(x)  ((uint16_t)(x))
#define be32toh(x)  ((uint32_t)(x))
#define be64toh(x)  ((uint64_t)(x))
#define le16toh(x)  bswap16((x))
#define le32toh(x)  bswap32((x))
#define le64toh(x)  bswap64((x))
#else
#error "Endian not defined!"
#endif /* _BYTE_ORDER == _LITTLE_ENDIAN */
#endif

#define __cpu_to_le64(x) htole64(x)
#define __le64_to_cpu(x) le64toh(x)
#define __cpu_to_le32(x) htole32(x)
#define __le32_to_cpu(x) le32toh(x)
#define __cpu_to_le16(x) htole16(x)
#define __le16_to_cpu(x) le16toh(x)
#define __cpu_to_be64(x) htobe64(x)
#define __be64_to_cpu(x) be64toh(x)
#define __cpu_to_be32(x) htobe32(x)
#define __be32_to_cpu(x) be32toh(x)
#define __cpu_to_be16(x) htobe16(x)
#define __be16_to_cpu(x) be16toh(x)

#define cpu_to_le64 __cpu_to_le64
#define le64_to_cpu __le64_to_cpu
#define cpu_to_le32 __cpu_to_le32
#define le32_to_cpu __le32_to_cpu
#define cpu_to_le16 __cpu_to_le16
#define le16_to_cpu __le16_to_cpu
#define cpu_to_be64 __cpu_to_be64
#define be64_to_cpu __be64_to_cpu
#define cpu_to_be32 __cpu_to_be32
#define be32_to_cpu __be32_to_cpu
#define cpu_to_be16 __cpu_to_be16
#define be16_to_cpu __be16_to_cpu


/* Alignment-agnostic encode/decode bytestream to/from little/big endian. */

static __inline uint16_t
be16dec(const void *pp)
{
    uint8_t const *p = (uint8_t const *)pp;

    return ((p[0] << 8) | p[1]);
}

static __inline uint32_t
be32dec(const void *pp)
{
    uint8_t const *p = (uint8_t const *)pp;

    return (((unsigned)p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static __inline uint64_t
be64dec(const void *pp)
{
    uint8_t const *p = (uint8_t const *)pp;

    return (((uint64_t)be32dec(p) << 32) | be32dec(p + 4));
}

static __inline uint16_t
le16dec(const void *pp)
{
    uint8_t const *p = (uint8_t const *)pp;

    return ((p[1] << 8) | p[0]);
}

static __inline uint32_t
le32dec(const void *pp)
{
    uint8_t const *p = (uint8_t const *)pp;

    return (((unsigned)p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0]);
}

static __inline uint64_t
le64dec(const void *pp)
{
    uint8_t const *p = (uint8_t const *)pp;

    return (((uint64_t)le32dec(p + 4) << 32) | le32dec(p));
}

static __inline void
be16enc(void *pp, uint16_t u)
{
    uint8_t *p = (uint8_t *)pp;

    p[0] = (u >> 8) & 0xff;
    p[1] = u & 0xff;
}

static __inline void
be32enc(void *pp, uint32_t u)
{
    uint8_t *p = (uint8_t *)pp;

    p[0] = (u >> 24) & 0xff;
    p[1] = (u >> 16) & 0xff;
    p[2] = (u >> 8) & 0xff;
    p[3] = u & 0xff;
}

static __inline void
be64enc(void *pp, uint64_t u)
{
    uint8_t *p = (uint8_t *)pp;

    be32enc(p, (uint32_t)(u >> 32));
    be32enc(p + 4, (uint32_t)(u & 0xffffffffU));
}

static __inline void
le16enc(void *pp, uint16_t u)
{
    uint8_t *p = (uint8_t *)pp;

    p[0] = u & 0xff;
    p[1] = (u >> 8) & 0xff;
}

static __inline void
le32enc(void *pp, uint32_t u)
{
    uint8_t *p = (uint8_t *)pp;

    p[0] = u & 0xff;
    p[1] = (u >> 8) & 0xff;
    p[2] = (u >> 16) & 0xff;
    p[3] = (u >> 24) & 0xff;
}

static __inline void
le64enc(void *pp, uint64_t u)
{
    uint8_t *p = (uint8_t *)pp;

    le32enc(p, (uint32_t)(u & 0xffffffffU));
    le32enc(p + 4, (uint32_t)(u >> 32));
}

#endif  /* _SYS_ENDIAN_H_ */
