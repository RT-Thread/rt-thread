/**
  ******************************************************************************
  * @file    type_def.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   Typedef file
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __TYPE_DEF_H
#define __TYPE_DEF_H

#define ENABLE  1
#define DISABLE 0
#define IS_FUNCTIONAL_STATE(__STATE__) (((__STATE__) == DISABLE) || ((__STATE__) == ENABLE))

#define BIT_BAND(addr, bitnum)        *((volatile unsigned long *)((((uint32_t)addr) & 0xF0000000) + \
                                        0x2000000 + ((((uint32_t)addr) & 0xFFFFF) << 5) + (bitnum << 2)))

#define BIT0      0x00000001
#define BIT1      0x00000002
#define BIT2      0x00000004
#define BIT3      0x00000008
#define BIT4      0x00000010
#define BIT5      0x00000020
#define BIT6      0x00000040
#define BIT7      0x00000080
#define BIT8      0x00000100
#define BIT9      0x00000200
#define BIT10     0x00000400
#define BIT11     0x00000800
#define BIT12     0x00001000
#define BIT13     0x00002000
#define BIT14     0x00004000
#define BIT15     0x00008000
#define BIT16     0x00010000
#define BIT17     0x00020000
#define BIT18     0x00040000
#define BIT19     0x00080000
#define BIT20     0x00100000
#define BIT21     0x00200000
#define BIT22     0x00400000
#define BIT23     0x00800000
#define BIT24     0x01000000
#define BIT25     0x02000000
#define BIT26     0x04000000
#define BIT27     0x08000000
#define BIT28     0x10000000
#define BIT29     0x20000000
#define BIT30     0x40000000
#define BIT31     0x80000000

#if  defined ( __GNUC__ )
  #ifndef __weak
    #define __weak   __attribute__((weak))
  #endif /* __weak */
  #ifndef __packed
    #define __packed __attribute__((__packed__))
  #endif /* __packed */
#endif /* __GNUC__ */


/* Macro to get variable aligned on 4-bytes, for __ICCARM__ the directive "#pragma data_alignment=4" must be used instead */
#if defined   (__GNUC__)        /* GNU Compiler */
  #ifndef __ALIGN_END
    #define __ALIGN_END    __attribute__ ((aligned (4)))
  #endif /* __ALIGN_END */
  #ifndef __ALIGN_BEGIN
    #define __ALIGN_BEGIN
  #endif /* __ALIGN_BEGIN */
#else
  #ifndef __ALIGN_END
    #define __ALIGN_END
  #endif /* __ALIGN_END */
  #ifndef __ALIGN_BEGIN
    #if defined   (__CC_ARM)      /* ARM Compiler */
      #define __ALIGN_BEGIN    __align(4)
    #elif defined (__ICCARM__)    /* IAR Compiler */
      #define __ALIGN_BEGIN
    #endif /* __CC_ARM */
  #endif /* __ALIGN_BEGIN */
#endif /* __GNUC__ */

/**
  * @brief  __NOINLINE definition
  */
#if defined ( __CC_ARM   ) || defined   (  __GNUC__  )
/* ARM & GNUCompiler
   ----------------
*/
#define __NOINLINE __attribute__ ( (noinline) )

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
*/
#define __NOINLINE _Pragma("optimize = no_inline")

#endif

#endif /* __TYPE_DEF_H */

/*********************************** END OF FILE ******************************/
