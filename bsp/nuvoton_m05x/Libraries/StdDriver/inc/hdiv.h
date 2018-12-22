/**************************************************************************//**
 * @file     DIV.h
 * @version  V2.1
 * $Revision: 4 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 Series DIV Driver Header File
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __DIVIDER_H__
#define __DIVIDER_H__


/**
 * @brief      Division function to calculate (x/y)
 *
 * @param[in]  x the dividend of the division
 * @param[in]  y the divisor of the division
 *
 * @return     The result of (x/y)
 *
 * @details    This is a division function to calculate x/y
 *
 */
static __INLINE int32_t HDIV_Div(int32_t x, int16_t y)
{
    uint32_t *p32;

    p32 = (uint32_t *)HDIV_BASE;
    *p32++ = x;
    *p32++ = y;
    return *p32;
}


/**
 * @brief      To calculate the remainder of x/y, i.e., the result of x mod y.
 *
 * @param[in]  x the dividend of the division
 * @param[in]  y the divisor of the division
 *
 * @return     The remainder of (x/y)
 *
 * @details    This function is used to calculate the remainder of x/y.
 */
static __INLINE int16_t HDIV_Mod(int32_t x, int16_t y)
{
    uint32_t *p32;

    p32 = (uint32_t *)HDIV_BASE;
    *p32++ = x;
    *p32++ = y;
    return p32[1];
}


#endif


