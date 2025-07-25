/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-08-16     zhujiale     first version
 */
#ifndef __SDHCI_MISC_H__
#define __SDHCI_MISC_H__

#include "sdhci_host.h"

#define __BF_FIELD_CHECK(...)
#define __bf_shf(x) (__builtin_ffsll(x) - 1)
#define FIELD_GET(_mask, _reg)                                  \
    ({                                                          \
        __BF_FIELD_CHECK(_mask, _reg, 0U, "FIELD_GET: ");       \
        (typeof(_mask))(((_reg) & (_mask)) >> __bf_shf(_mask)); \
    })

#define FIELD_PREP(_mask, _val)                               \
    ({                                                        \
        __BF_FIELD_CHECK(_mask, 0ULL, _val, "FIELD_PREP: ");  \
        ((typeof(_mask))(_val) << __bf_shf(_mask)) & (_mask); \
    })

#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#define min_t(type, x, y) (((type)x < (type)y) ? x : y)
#define max_t(type, x, y) (((type)x > (type)y) ? x : y)
#define min(x, y)         ((x) < (y) ? (x) : (y))

#define from_timer(var, callback_timer, timer_fieldname) \
    container_of(callback_timer, typeof(*var), timer_fieldname)


#define le32_to_cpu(x)   (x)
#define le16_to_cpu(x)   (x)
#define cpu_to_le16(x)   (x)
#define cpu_to_le32(x)   (x)
#define lower_32_bits(n) ((rt_uint32_t)((n) & 0xffffffff))
#define upper_32_bits(n) ((rt_uint32_t)(((n) >> 16) >> 16))

#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#define do_div(n, base) ({            \
    uint32_t __base = (base);         \
    uint32_t __rem;                   \
    __rem = ((uint64_t)(n)) % __base; \
    (n)   = ((uint64_t)(n)) / __base; \
    __rem;                            \
})

#define fallthrough \
    do {            \
    } while (0)

int       regulator_is_supported_voltage(struct regulator *regulator,
                                         int min_uV, int max_uV);
int       regulator_enable(struct regulator *regulator);
rt_bool_t mmc_can_gpio_cd(struct mmc_host *host);

struct regulator
{
    const char *supply_name;
};

int regulator_get_current_limit(struct regulator *regulator);

int regulator_enable(struct regulator *regulator);

void regulator_disable(struct regulator *regulator);

#endif
