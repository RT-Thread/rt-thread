/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_BTSTACK_CHIPSET_CYW43_H
#define _PICO_BTSTACK_CHIPSET_CYW43_H

#include "btstack_chipset.h"

/**
 * \brief Return the singleton BTstack chipset CY43 API instance
 * \ingroup pico_btstack
 */
const btstack_chipset_t * btstack_chipset_cyw43_instance(void);

#endif
