/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fswap.h
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:35:24
 * Description:  This files is for endian conversion.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu  2021/06/15        first release
 */

#ifndef FSWAP_H
#define FSWAP_H

#ifdef __cplusplus
extern "C"
{
#endif

#define __swab16(x) (uint16_t)__builtin_bswap16((uint16_t)(x))
#define __swab32(x) (uint32_t)__builtin_bswap32((uint32_t)(x))
#define __swab64(x) (uint64_t)__builtin_bswap64((uint64_t)(x))

#define cpu_to_le64(x) ((__u64)(x))
#define le64_to_cpu(x) ((__le64)(x))
#define cpu_to_le32(x) ((__u32)(x))
#define le32_to_cpu(x) ((__le32)(x))
#define cpu_to_le16(x) ((__u16)(x))
#define le16_to_cpu(x) ((__le16)(x))
#define cpu_to_be64(x) __swab64((x))
#define be64_to_cpu(x) __swab64((x))
#define cpu_to_be32(x) __swab32((x))
#define be32_to_cpu(x) __swab32((x))
#define cpu_to_be16(x) __swab16((x))
#define be16_to_cpu(x) __swab16((x))

#define ___htonl(x) cpu_to_be32(x)
#define ___htons(x) cpu_to_be16(x)
#define ___ntohl(x) be32_to_cpu(x)
#define ___ntohs(x) be16_to_cpu(x)

#define htonl(x) ___htonl(x)
#define ntohl(x) ___ntohl(x)
#define htons(x) ___htons(x)
#define ntohs(x) ___ntohs(x)

#ifdef __cplusplus
}
#endif

#endif