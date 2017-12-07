/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-05     Tanek        first version
 */

#include <rtthread.h>

// enter serial download mode, and run command:
//      finsh /> mem_dump(0x60000000, 512)
#if defined (__ICCARM__ )
RT_USED static const uint32_t boot_data[] @(0x60000000u) =
#elif defined ( __GNUC__ )
RT_USED static const uint32_t boot_data[] __attribute__((section (".bootdata"))) =
#elif defined ( __CC_ARM )
RT_USED static const uint32_t boot_data[] __attribute__((at(0x60000000u))) =
#endif
{
    0x42464346, 0x56010400, 0x00000000, 0x03030303, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000059, 0x01080800, 0x00000000, 0x00000000, 0x04000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000000F, 0x0001000F,
    0x8B1887A0, 0xA7048F10, 0x00000000, 0x00000000, 0x87008700, 0x87AA8700, 0x87058700, 0x87708700,
    0x8B1887A0, 0xB70B8F10, 0x0000A704, 0x00000000, 0x87008700, 0x87AA8700, 0x87058700, 0x87AA8700,
    0x87008700, 0x87558700, 0x87028700, 0x87558700, 0x87008700, 0x87AA8700, 0x87058700, 0x87808700,
    0x87008700, 0x87AA8700, 0x87058700, 0x87AA8700, 0x87008700, 0x87558700, 0x87028700, 0x87558700,
    0x8B188700, 0x87008F10, 0x00008730, 0x00000000, 0x87008700, 0x87AA8700, 0x87058700, 0x87A08700,
    0x8B188700, 0xA3808F10, 0x00000000, 0x00000000, 0x87008700, 0x87AA8700, 0x87058700, 0x87808700,
    0x87008700, 0x87AA8700, 0x87058700, 0x87AA8700, 0x87008700, 0x87558700, 0x87028700, 0x87558700,
    0x87008700, 0x87AA8700, 0x87058700, 0x87108700, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000102, 0x00000302, 0x00000504, 0x00000902, 0x00000B04, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000200, 0x00040000, 0x00000008, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

//      finsh /> mem_dump(0x60001000, 16)
#if defined (__ICCARM__ )
RT_USED static const uint32_t image_vector_table[] @(0x60001000u) =
#elif defined ( __GNUC__ )
RT_USED static const uint32_t image_vector_table[] __attribute__((section (".ivt"))) =
#elif defined ( __CC_ARM )
RT_USED static const uint32_t image_vector_table[] __attribute__((at(0x60001000u))) =
#endif
{
    0x412000D1, 0x60002000, 0x00000000, 0x00000000, 0x60001020, 0x60001000, 0x00000000, 0x00000000,
    0x60000000, 0x00800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
