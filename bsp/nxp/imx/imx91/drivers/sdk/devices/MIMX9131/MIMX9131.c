/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-10     Siwei Xu     Add i.MX91 SDK
 * 2025-09-15     Siwei Xu     Fix LPUART driver
 * 2025-10-08     Siwei Xu     Fix MMU Enable issues
 */

#include "MIMX9131.h"

CCM_Type* CCM_CTRL = (CCM_Type *)CCM_CTRL_BASE;

LPUART_Type* LPUART1 = (LPUART_Type *)LPUART1_BASE;
LPUART_Type* LPUART2 = (LPUART_Type *)LPUART2_BASE;
LPUART_Type* LPUART3 = (LPUART_Type *)LPUART3_BASE;
LPUART_Type* LPUART4 = (LPUART_Type *)LPUART4_BASE;
LPUART_Type* LPUART5 = (LPUART_Type *)LPUART5_BASE;
LPUART_Type* LPUART6 = (LPUART_Type *)LPUART6_BASE;
LPUART_Type* LPUART7 = (LPUART_Type *)LPUART7_BASE;
LPUART_Type* LPUART8 = (LPUART_Type *)LPUART8_BASE;
