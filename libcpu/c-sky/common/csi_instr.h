/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     csi_instr.h
 * @brief    CSI Header File for instruct.
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_INSTR_H_
#define _CSI_INSTR_H_


#define __CSI_GCC_OUT_REG(r) "=r" (r)
#define __CSI_GCC_USE_REG(r) "r" (r)

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
__ALWAYS_INLINE void __NOP(void)
{
    __ASM volatile("nop");
}


/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
 */
__ALWAYS_INLINE void __WFI(void)
{
    __ASM volatile("wait");
}

/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_INLINE void __WAIT(void)
{
    __ASM volatile("wait");
}

/**
  \brief   Doze For Interrupt
  \details Doze For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_INLINE void __DOZE(void)
{
    __ASM volatile("doze");
}

/**
  \brief   Stop For Interrupt
  \details Stop For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_INLINE void __STOP(void)
{
    __ASM volatile("stop");
}

/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
__ALWAYS_INLINE void __ISB(void)
{
    __ASM volatile("sync"::: "memory");
}


/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__ALWAYS_INLINE void __DSB(void)
{
    __ASM volatile("sync"::: "memory");
}


/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
__ALWAYS_INLINE void __DMB(void)
{
    __ASM volatile("sync"::: "memory");
}


/**
  \brief   Reverse byte order (32 bit)
  \details Reverses the byte order in integer value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_INLINE uint32_t __REV(uint32_t value)
{
    return __builtin_bswap32(value);
}


/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order in two unsigned short values.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_INLINE uint32_t __REV16(uint32_t value)
{
    uint32_t result;
#if (__CK80X >= 2)
    __ASM volatile("revh %0, %1" : __CSI_GCC_OUT_REG(result) : __CSI_GCC_USE_REG(value));
#else
    result = ((value & 0xFF000000) >> 8) | ((value & 0x00FF0000) << 8) |
             ((value & 0x0000FF00) >> 8) | ((value & 0x000000FF) << 8);
#endif
    return (result);
}


/**
  \brief   Reverse byte order in signed short value
  \details Reverses the byte order in a signed short value with sign extension to integer.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_INLINE int32_t __REVSH(int32_t value)
{
    return (short)(((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8));
}


/**
  \brief   Rotate Right in unsigned value (32 bit)
  \details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
  \param [in]    op1  Value to rotate
  \param [in]    op2  Number of Bits to rotate
  \return               Rotated value
 */
__ALWAYS_INLINE uint32_t __ROR(uint32_t op1, uint32_t op2)
{
    return (op1 >> op2) | (op1 << (32U - op2));
}


/**
  \brief   Breakpoint
  \details Causes the processor to enter Debug state
           Debug tools can use this to investigate system state when the instruction at a particular address is reached.
 */
__ALWAYS_INLINE void __BKPT()
{
    __ASM volatile("bkpt");
}

/**
  \brief   Reverse bit order of value
  \details Reverses the bit order of the given value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_INLINE uint32_t __RBIT(uint32_t value)
{
    uint32_t result;

#if       (__CK80X >= 0x03U)
    __ASM volatile("brev %0, %1" : "=r"(result) : "r"(value));
#else
    int32_t s = 4 /*sizeof(v)*/ * 8 - 1; /* extra shift needed at end */

    result = value;                      /* r will be reversed bits of v; first get LSB of v */

    for (value >>= 1U; value; value >>= 1U)
    {
        result <<= 1U;
        result |= value & 1U;
        s--;
    }

    result <<= s;                        /* shift when v's highest bits are zero */
#endif
    return (result);
}


/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
#define __CLZ             __builtin_clz
/**
  \details This function saturates a signed value.
  \param [in]    x   Value to be saturated
  \param [in]    y   Bit position to saturate to [1..32]
  \return            Saturated value.
 */
__ALWAYS_INLINE int32_t __SSAT(int32_t x, uint32_t y)
{
    int32_t posMax, negMin;
    uint32_t i;

    posMax = 1;

    for (i = 0; i < (y - 1); i++)
    {
        posMax = posMax * 2;
    }

    if (x > 0)
    {
        posMax = (posMax - 1);

        if (x > posMax)
        {
            x = posMax;
        }

//    x &= (posMax * 2 + 1);
    }
    else
    {
        negMin = -posMax;

        if (x < negMin)
        {
            x = negMin;
        }

//    x &= (posMax * 2 - 1);
    }

    return (x);
}

/**
  \brief   Unsigned Saturate
  \details Saturates an unsigned value.
  \param [in]  value  Value to be saturated
  \param [in]    sat  Bit position to saturate to (0..31)
  \return             Saturated value
 */
__ALWAYS_INLINE uint32_t __USAT(uint32_t value, uint32_t sat)
{
    uint32_t result;

    if ((((0xFFFFFFFF >> sat) << sat) & value) != 0)
    {
        result = 0xFFFFFFFF >> (32 - sat);
    }
    else
    {
        result = value;
    }

    return (result);
}

/**
  \brief   Unsigned Saturate for internal use
  \details Saturates an unsigned value, should not call directly.
  \param [in]  value  Value to be saturated
  \param [in]    sat  Bit position to saturate to (0..31)
  \return             Saturated value
 */
__ALWAYS_INLINE uint32_t __IUSAT(uint32_t value, uint32_t sat)
{
    uint32_t result;

    if (value & 0x80000000)   /* only overflow set bit-31 */
    {
        result = 0;
    }
    else if ((((0xFFFFFFFF >> sat) << sat) & value) != 0)
    {
        result = 0xFFFFFFFF >> (32 - sat);
    }
    else
    {
        result = value;
    }

    return (result);
}

/**
  \brief   Rotate Right with Extend
  \details This function moves each bit of a bitstring right by one bit.
           The carry input is shifted in at the left end of the bitstring.
  \note    carry input will always 0.
  \param [in]    op1  Value to rotate
  \return               Rotated value
 */
__ALWAYS_INLINE uint32_t __RRX(uint32_t op1)
{
#if (__CK80X >= 2)
    uint32_t res = 0;
    __ASM volatile("bgeni    t0, 31\n\t"
                   "lsri     %0, 1\n\t"
                   "movt     %1, t0\n\t"
                   "or       %1, %1, %0\n\t"
                   : "=r"(op1), "=r"(res): "0"(op1), "1"(res): "t0");
    return res;
#else
    uint32_t res = 0;
    __ASM volatile("movi     r7, 0\n\t"
                   "bseti    r7, 31\n\t"
                   "lsri     %0, 1\n\t"
                   "bf       1f\n\t"
                   "mov     %1, r7\n\t"
                   "1:\n\t"
                   "or       %1, %1, %0\n\t"
                   : "=r"(op1), "=r"(res): "0"(op1), "1"(res): "r7");
    return res;
#endif
}

/**
  \brief   LDRT Unprivileged (8 bit)
  \details Executes a Unprivileged LDRT instruction for 8 bit value.
  \param [in]    addr  Pointer to location
  \return             value of type uint8_t at (*ptr)
 */
__ALWAYS_INLINE uint8_t __LDRBT(volatile uint8_t *addr)
{
    uint32_t result;
//#warning "__LDRBT"
    __ASM volatile("ldb %0, (%1, 0)" : "=r"(result) : "r"(addr));
    return ((uint8_t) result);    /* Add explicit type cast here */
}


/**
  \brief   LDRT Unprivileged (16 bit)
  \details Executes a Unprivileged LDRT instruction for 16 bit values.
  \param [in]    addr  Pointer to location
  \return        value of type uint16_t at (*ptr)
 */
__ALWAYS_INLINE uint16_t __LDRHT(volatile uint16_t *addr)
{
    uint32_t result;

//#warning "__LDRHT"
    __ASM volatile("ldh %0, (%1, 0)" : "=r"(result) : "r"(addr));
    return ((uint16_t) result);    /* Add explicit type cast here */
}


/**
  \brief   LDRT Unprivileged (32 bit)
  \details Executes a Unprivileged LDRT instruction for 32 bit values.
  \param [in]    addr  Pointer to location
  \return        value of type uint32_t at (*ptr)
 */
__ALWAYS_INLINE uint32_t __LDRT(volatile uint32_t *addr)
{
    uint32_t result;

//#warning "__LDRT"
    __ASM volatile("ldw %0, (%1, 0)" : "=r"(result) : "r"(addr));
    return (result);
}


/**
  \brief   STRT Unprivileged (8 bit)
  \details Executes a Unprivileged STRT instruction for 8 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_INLINE void __STRBT(uint8_t value, volatile uint8_t *addr)
{
//#warning "__STRBT"
    __ASM volatile("stb %1, (%0, 0)" :: "r"(addr), "r"((uint32_t)value) : "memory");
}


/**
  \brief   STRT Unprivileged (16 bit)
  \details Executes a Unprivileged STRT instruction for 16 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_INLINE void __STRHT(uint16_t value, volatile uint16_t *addr)
{
//#warning "__STRHT"
    __ASM volatile("sth %1, (%0, 0)" :: "r"(addr), "r"((uint32_t)value) : "memory");
}


/**
  \brief   STRT Unprivileged (32 bit)
  \details Executes a Unprivileged STRT instruction for 32 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_INLINE void __STRT(uint32_t value, volatile uint32_t *addr)
{
//#warning "__STRT"
    __ASM volatile("stw %1, (%0, 0)" :: "r"(addr), "r"(value) : "memory");
}

/*@}*/ /* end of group CSI_Core_InstructionInterface */


/* ##########################  FPU functions  #################################### */

/**
  \brief   get FPU type
  \details returns the FPU type, always 0.
  \returns
   - \b  0: No FPU
   - \b  1: Single precision FPU
   - \b  2: Double + Single precision FPU
 */
__ALWAYS_INLINE uint32_t __get_FPUType(void)
{
    uint32_t result;

    __ASM volatile("mfcr %0, cr<13, 0>" : "=r"(result));
    return 0;
}


#endif /* _CSI_INSTR_H_ */
