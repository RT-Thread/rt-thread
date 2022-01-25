////////////////////////////////////////////////////////////////////////////////
/// @file     types.h
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE TYPE FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#ifndef __TYPES_H
#define __TYPES_H

// Files includes
#include <stdint.h>
#include <stdbool.h>



#ifdef __cplusplus
#define     __I     volatile                        ///< Defines 'read only' permissions
#else
#define     __I     volatile const                  ///< Defines 'read only' permissions
#endif
#define     __O     volatile                        ///< Defines 'write only' permissions
#define     __IO    volatile                        ///< Defines 'read / write' permissions

typedef long long    s64;                           ///< used for signed 64bit

typedef signed int   s32;
typedef signed short s16;
typedef signed char  s8;

typedef signed int  const  sc32;                    ///< Read Only
typedef signed short const sc16;                    ///< Read Only
typedef signed char  const sc8;                     ///< Read Only

typedef volatile signed int   vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;

typedef volatile signed int  const  vsc32;          ///< Read Only
typedef volatile signed short const vsc16;          ///< Read Only
typedef volatile signed char  const vsc8;           ///< Read Only

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned int  const  uc32;                  ///< Read Only
typedef unsigned short const uc16;                  ///< Read Only
typedef unsigned char  const uc8;                   ///< Read Only

typedef volatile unsigned int   vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned int  const  vuc32;        ///< Read Only
typedef volatile unsigned short const vuc16;        ///< Read Only
typedef volatile unsigned char  const vuc8;         ///< Read Only
typedef bool    BOOL;
#ifndef NULL
#define NULL ((void *)0)
#endif
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;


#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648uL)

#define MAX(a,b)((a)>(b)?(a):(b))
#define MIN(a,b)((a)<(b)?(a):(b))

#define SET_BIT(reg, bit)     ((reg) |= (bit))
#define CLEAR_BIT(reg, bit)   ((reg) &= ~(bit))
#define READ_BIT(reg, bit)    ((reg) & (bit))
#define CLEAR_REG(reg)        ((reg) = (0x0))
#define WRITE_REG(reg, value)   ((reg) = (value))
#define READ_REG(reg)         ((reg))
#define MODIFY_REG(reg, CLEARMASK, SETMASK)  WRITE_REG((reg), (((READ_REG(reg)) & (~(CLEARMASK))) | (SETMASK)))
#define POSITION_VAL(value)     (__CLZ(__RBIT(value)))

#define LEFT_SHIFT_BIT(x)   (1 << x)


#endif
