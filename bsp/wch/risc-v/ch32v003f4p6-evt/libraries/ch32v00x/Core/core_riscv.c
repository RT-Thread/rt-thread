/********************************** (C) COPYRIGHT  *******************************
* File Name          : core_riscv.c
* Author             : WCH
* Version            : V1.0.1
* Date               : 2024/10/28
* Description        : RISC-V V2 Core Peripheral Access Layer Source File for CH32V003
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include <stdint.h>

/* define compiler specific symbols */
#if defined(__CC_ARM)
  #define __ASM       __asm     /*!< asm keyword for ARM Compiler          */
  #define __INLINE    __inline  /*!< inline keyword for ARM Compiler       */

#elif defined(__ICCARM__)
  #define __ASM       __asm   /*!< asm keyword for IAR Compiler          */
  #define __INLINE    inline  /*!< inline keyword for IAR Compiler. Only avaiable in High optimization mode! */

#elif defined(__GNUC__)
  #define __ASM       __asm   /*!< asm keyword for GNU Compiler          */
  #define __INLINE    inline  /*!< inline keyword for GNU Compiler       */

#elif defined(__TASKING__)
  #define __ASM       __asm   /*!< asm keyword for TASKING Compiler      */
  #define __INLINE    inline  /*!< inline keyword for TASKING Compiler   */

#endif

/*********************************************************************
 * @fn      __get_MSTATUS
 *
 * @brief   Return the Machine Status Register
 *
 * @return  mstatus value
 */
uint32_t __get_MSTATUS(void)
{
    uint32_t result;

    __ASM volatile("csrr %0," "mstatus": "=r"(result));
    return (result);
}

/*********************************************************************
 * @fn      __set_MSTATUS
 *
 * @brief   Set the Machine Status Register
 *
 * @param   value  - set mstatus value
 *
 * @return  none
 */
void __set_MSTATUS(uint32_t value)
{
    __ASM volatile("csrw mstatus, %0" : : "r"(value));
}

/*********************************************************************
 * @fn      __get_MISA
 *
 * @brief   Return the Machine ISA Register
 *
 * @return  misa value
 */
uint32_t __get_MISA(void)
{
    uint32_t result;

    __ASM volatile("csrr %0,""misa" : "=r"(result));
    return (result);
}

/*********************************************************************
 * @fn      __set_MISA
 *
 * @brief   Set the Machine ISA Register
 *
 * @param   value - set misa value
 *
 * @return  none
 */
void __set_MISA(uint32_t value)
{
    __ASM volatile("csrw misa, %0" : : "r"(value));
}

/*********************************************************************
 * @fn      __get_MTVEC
 *
 * @brief   Return the Machine Trap-Vector Base-Address Register
 *
 * @return  mtvec value
 */
uint32_t __get_MTVEC(void)
{
    uint32_t result;

    __ASM volatile("csrr %0," "mtvec": "=r"(result));
    return (result);
}

/*********************************************************************
 * @fn      __set_MTVEC
 *
 * @brief   Set the Machine Trap-Vector Base-Address Register
 *
 * @param   value  - set mtvec value
 *
 * @return  none
 */
void __set_MTVEC(uint32_t value)
{
    __ASM volatile("csrw mtvec, %0":: "r"(value));
}

/*********************************************************************
 * @fn      __get_MSCRATCH
 *
 * @brief   Return the Machine Seratch Register
 *
 * @return  mscratch value
 */
uint32_t __get_MSCRATCH(void)
{
    uint32_t result;

    __ASM volatile("csrr %0," "mscratch" : "=r"(result));
    return (result);
}

/*********************************************************************
 * @fn      __set_MSCRATCH
 *
 * @brief   Set the Machine Seratch Register
 *
 * @param   value  - set mscratch value
 *
 * @return  none
 */
void __set_MSCRATCH(uint32_t value)
{
    __ASM volatile("csrw mscratch, %0" : : "r"(value));
}

/*********************************************************************
 * @fn      __get_MEPC
 *
 * @brief   Return the Machine Exception Program Register
 *
 * @return  mepc value
 */
uint32_t __get_MEPC(void)
{
    uint32_t result;

    __ASM volatile("csrr %0," "mepc" : "=r"(result));
    return (result);
}

/*********************************************************************
 * @fn      __set_MEPC
 *
 * @brief   Set the Machine Exception Program Register
 *
 * @return  mepc value
 */
void __set_MEPC(uint32_t value)
{
    __ASM volatile("csrw mepc, %0" : : "r"(value));
}

/*********************************************************************
 * @fn      __get_MCAUSE
 *
 * @brief   Return the Machine Cause Register
 *
 * @return  mcause value
 */
uint32_t __get_MCAUSE(void)
{
    uint32_t result;

    __ASM volatile("csrr %0," "mcause": "=r"(result));
    return (result);
}

/*********************************************************************
 * @fn      __set_MEPC
 *
 * @brief   Set the Machine Cause Register
 *
 * @return  mcause value
 */
void __set_MCAUSE(uint32_t value)
{
    __ASM volatile("csrw mcause, %0":: "r"(value));
}

/*********************************************************************
 * @fn      __get_MVENDORID
 *
 * @brief   Return Vendor ID Register
 *
 * @return  mvendorid value
 */
uint32_t __get_MVENDORID(void)
{
    uint32_t result;

    __ASM volatile("csrr %0,""mvendorid": "=r"(result));
    return (result);
}

/*********************************************************************
 * @fn      __get_MARCHID
 *
 * @brief   Return Machine Architecture ID Register
 *
 * @return  marchid value
 */
uint32_t __get_MARCHID(void)
{
    uint32_t result;

    __ASM volatile("csrr %0,""marchid": "=r"(result));
    return (result);
}

/*********************************************************************
 * @fn      __get_MIMPID
 *
 * @brief   Return Machine Implementation ID Register
 *
 * @return  mimpid value
 */
uint32_t __get_MIMPID(void)
{
    uint32_t result;

    __ASM volatile("csrr %0,""mimpid": "=r"(result));
    return (result);
}

/*********************************************************************
 * @fn      __get_MHARTID
 *
 * @brief   Return Hart ID Register
 *
 * @return  mhartid value
 */
uint32_t __get_MHARTID(void)
{
    uint32_t result;

    __ASM volatile("csrr %0,""mhartid": "=r"(result));
    return (result);
}

/*********************************************************************
 * @fn      __get_SP
 *
 * @brief   Return SP Register
 *
 * @return  SP value
 */
uint32_t __get_SP(void)
{
    uint32_t result;

    __ASM volatile("mv %0,""sp": "=r"(result):);
    return (result);
}

/*********************************************************************
 * @fn      _WFE
 *
 * @brief   Wait for Events
 *
 * @return  none
 */
__attribute__( (section(".highcode")) ) void WFE(uint32_t t)
{
  asm volatile ("wfi");
  asm volatile ("1:addi a0, a0, -1\n\t" \
                "bnez a0, 1b\n\t"  \
          );
}
