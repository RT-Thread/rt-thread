/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-13 21:52:20
 * @LastEditTime: 2021-04-13 21:52:20
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#ifndef FT_CACHE_H
#define FT_CACHE_H

#include "ft_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void FCache_cpuDcacheInvalidate(void *addr, ft_base_t size);
    void FCache_cpuDcacheClean(void *addr, ft_base_t size);
    void FCache_cpuIcacheInvalidate(void *addr, ft_base_t size);

#ifdef __cplusplus
}
#endif

#endif // !FT_CACHE_H
