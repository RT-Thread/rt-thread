/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-2-7        Wayne            First version
*
******************************************************************************/

#ifndef NU_MISC_UTIL_H
#define NU_MISC_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#define NU_MAX(a,b) ((a)>(b)?(a):(b))
#define NU_MIN(a,b) ((a)<(b)?(a):(b))
#define NU_CLAMP(x, min, max)   NU_MIN(NU_MAX((x), (min)), (max))
#define NU_ALIGN_DOWN(X, ALIGN)     ((X) & ~((ALIGN) - 1))
#define NU_ALIGN_UP(X, ALIGN)       (((X) + (ALIGN) - 1) & ~((ALIGN) - 1))
#define NU_ISALIGNED(a, b)       (((a) & (b - 1)) == 0)

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#ifdef __cplusplus
}
#endif

#endif
