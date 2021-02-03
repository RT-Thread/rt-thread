/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/02/01     BalanceTWK   The unify TriCore porting code.
 */

#ifndef CPUPORT_H__
#define CPUPORT_H__

#include <rtconfig.h>
#include "IfxCpu.h"
#include "IfxCpu_reg.h"
#include "Bsp.h"
#include "Stm/Timer/IfxStm_Timer.h"

#define LINKWORD_TO_ADDRESS( LinkWord )             ( ( unsigned long * )( ( ( ( LinkWord ) & 0x000F0000 ) << 12 ) | ( ( ( LinkWord ) & 0x0000FFFF ) << 6 ) ) )
#define ADDRESS_TO_LINKWORD( Address )              ( ( unsigned long )( ( ( ( (unsigned long)( Address ) ) & 0xF0000000 ) >> 12 ) | ( ( ( unsigned long )( Address ) & 0x003FFFC0 ) >> 6 ) ) )

#define TRICORE_NUM_WORDS_IN_CSA                    ( 16 )
#define TRICORE_SYSTEM_PROGRAM_STATUS_WORD          ( 0x000008FFUL ) /* Supervisor Mode, MPU Register Set 0 and Call Depth Counting disabled. */
#define TRICORE_INITIAL_PCXI_UPPER_CONTEXT_WORD     ( 0x00300000UL ) // ATEN, default value as read from the CPU after init
#define TRICORE_INITIAL_SYSCON                      ( 0x00000000UL ) /* MPU Disable. */
#define TRICORE_RESTORE_PSW_MASK                    ( ~( 0x000000FFUL ) )
#define TRICORE_CPU_ID                              (__mfcr(CPU_CORE_ID) & 0x0f)

#endif
