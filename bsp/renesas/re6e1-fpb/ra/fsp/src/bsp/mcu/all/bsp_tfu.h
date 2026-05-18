/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RENESAS_TFU
#define RENESAS_TFU

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/* Mathematical Functions includes. */
#ifdef __cplusplus
 #include <cmath>
#else
 #include <math.h>
#endif

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

#if BSP_FEATURE_TFU_SUPPORTED

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

 #define R_TFU_HYPOT_SCALING_FACTOR    0.607252935f

 #ifdef __GNUC__                       /* and (arm)clang */
  #if (__STDC_VERSION__ < 199901L) && defined(__STRICT_ANSI__) && !defined(__cplusplus)

/* No form of inline is available, it happens only when -std=c89, gnu89 and
 * above are OK */
   #warning \
    "-std=c89 doesn't support type checking on TFU. Please use -std=gnu89 or higher for example -std=c99"
  #else
   #ifdef __GNUC_GNU_INLINE__

/* gnu89 semantics of inline and extern inline are essentially the exact
 * opposite of those in C99 */
    #define BSP_TFU_INLINE    extern inline __attribute__((always_inline))
   #else                               /* __GNUC_STDC_INLINE__ */
    #define BSP_TFU_INLINE    static inline __attribute__((always_inline))
   #endif
  #endif
 #elif __ICCARM__
  #define BSP_TFU_INLINE
 #else
  #error "Compiler not supported!"
 #endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Inline Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Calculates sine of the given angle.
 * @param[in]    angle  The value of an angle in radian.
 *
 * @retval Sine value of an angle.
 **********************************************************************************************************************/
 #if __ICCARM__
  #pragma inline = forced
 #endif
BSP_TFU_INLINE float __sinf (float angle)
{
    /* Set the angle to R_TFU->SCDT1 */
    R_TFU->SCDT1 = angle;

    /* Read sin from R_TFU->SCDT1 */
    return R_TFU->SCDT1;
}

/*******************************************************************************************************************//**
 * Calculates cosine of the given angle.
 * @param[in]    angle  The value of an angle in radian.
 *
 * @retval Cosine value of an angle.
 **********************************************************************************************************************/
 #if __ICCARM__
  #pragma inline = forced
 #endif
BSP_TFU_INLINE float __cosf (float angle)
{
    /* Set the angle to R_TFU->SCDT1 */
    R_TFU->SCDT1 = angle;

    /* Read cos from R_TFU->SCDT1 */
    return R_TFU->SCDT0;
}

/*******************************************************************************************************************//**
 * Calculates sine and cosine of the given angle.
 * @param[in]    angle  The value of an angle in radian.
 * @param[out]   sin    Sine value of an angle.
 * @param[out]   cos    Cosine value of an angle.
 **********************************************************************************************************************/
 #if __ICCARM__
  #pragma inline = forced
 #endif
BSP_TFU_INLINE void __sincosf (float angle, float * sin, float * cos)
{
    /* Set the angle to R_TFU->SCDT1 */
    R_TFU->SCDT1 = angle;

    /* Read sin from R_TFU->SCDT1 */
    *sin = R_TFU->SCDT1;

    /* Read sin from R_TFU->SCDT1 */
    *cos = R_TFU->SCDT0;
}

/*******************************************************************************************************************//**
 * Calculates the arc tangent based on given X-cordinate and Y-cordinate values.
 * @param[in]    y_cord  Y-Axis cordinate value.
 * @param[in]    x_cord  X-Axis cordinate value.
 *
 * @retval Arc tangent for given values.
 **********************************************************************************************************************/
 #if __ICCARM__
  #pragma inline = forced
 #endif
BSP_TFU_INLINE float __atan2f (float y_cord, float x_cord)
{
    /* Set X-cordinate to R_TFU->ATDT0 */
    R_TFU->ATDT0 = x_cord;

    /* set Y-cordinate to R_TFU->ATDT1 */
    R_TFU->ATDT1 = y_cord;

    /* Read arctan(y/x) from R_TFU->ATDT1 */
    return R_TFU->ATDT1;
}

/*******************************************************************************************************************//**
 * Calculates the hypotenuse based on given X-cordinate and Y-cordinate values.
 * @param[in]    y_cord  Y-cordinate value.
 * @param[in]    x_cord  X-cordinate value.
 *
 * @retval Hypotenuse for given values.
 **********************************************************************************************************************/
 #if __ICCARM__
  #pragma inline = forced
 #endif
BSP_TFU_INLINE float __hypotf (float x_cord, float y_cord)
{
    /* Set X-coordinate to R_TFU->ATDT0 */
    R_TFU->ATDT0 = x_cord;

    /* set Y-coordinate to R_TFU->ATDT1 */
    R_TFU->ATDT1 = y_cord;

    /* Read sqrt (x_cord2 + y_cord2) from R_TFU->ATDT0 */
    return R_TFU->ATDT0 * R_TFU_HYPOT_SCALING_FACTOR;
}

/*******************************************************************************************************************//**
 * Calculates the arc tangent and hypotenuse based on given X-cordinate and Y-cordinate values.
 * @param[in]    y_cord  Y-cordinate value.
 * @param[in]    x_cord  X-cordinate value.
 * @param[out]   atan2   Arc tangent for given values.
 * @param[out]   hypot   Hypotenuse for given values.
 **********************************************************************************************************************/
 #if __ICCARM__
  #pragma inline = forced
 #endif
BSP_TFU_INLINE void __atan2hypotf (float y_cord, float x_cord, float * atan2, float * hypot)
{
    /* Set X-coordinate to R_TFU->ATDT0 */
    R_TFU->ATDT0 = x_cord;

    /* set Y-coordinate to R_TFU->ATDT1 */
    R_TFU->ATDT1 = y_cord;

    /* Read arctan(y/x) from R_TFU->ATDT1 */
    *atan2 = R_TFU->ATDT1;

    /* Read sqrt (x_cord2 + y_cord2) from R_TFU->ATDT0 */
    *hypot = R_TFU->ATDT0 * R_TFU_HYPOT_SCALING_FACTOR;
}

 #if BSP_CFG_USE_TFU_MATHLIB
  #define sinf(x)                    __sinf(x)
  #define cosf(x)                    __cosf(x)
  #define atan2f(y, x)               __atan2f(y, x)
  #define hypotf(x, y)               __hypotf(x, y)
  #define atan2hypotf(y, x, a, h)    __atan2hypotf(y, x, a, h)
  #define sincosf(a, s, c)           __sincosf(a, s, c)
 #endif

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif

/** @} (end addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RENESAS_TFU */
