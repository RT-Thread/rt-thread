#ifndef __RV_HPM_H__
#define __RV_HPM_H__

#include <stdint.h>

#if (__riscv_xlen == 32)

#define RV_HPM_SET_COUNTER(name, val)                      \
    do {                                                   \
        uint32_t value = (uint32_t)val;                    \
        __asm volatile("csrw " #name ", %0"                \
                       :                                   \
                       : "r"(value)                        \
                       : "memory");                        \
        uint32_t valueh = (uint32_t)((uint64_t)val >> 32); \
        __asm volatile("csrw " #name "h, %0"               \
                       :                                   \
                       : "r"(valueh)                       \
                       : "memory");                        \
    } while (0);

#define RV_HPM_GET_COUNTER(name, val)                         \
    do {                                                      \
        uint32_t countl0, counth0;                            \
        uint32_t countl1, counth1;                            \
        do {                                                  \
            __asm volatile("csrr %0, " #name                  \
                           : "=r"(countl0)                    \
                           :                                  \
                           : "memory");                       \
            __asm volatile("csrr %0, " #name "h"              \
                           : "=r"(counth0)                    \
                           :                                  \
                           : "memory");                       \
            __asm volatile("csrr %0, " #name                  \
                           : "=r"(countl1)                    \
                           :                                  \
                           : "memory");                       \
            __asm volatile("csrr %0, " #name "h"              \
                           : "=r"(counth1)                    \
                           :                                  \
                           : "memory");                       \
        } while ((countl1 < countl0) || (counth1 < counth0)); \
        val = (((uint64_t)counth1) << 32) + countl1;          \
    } while (0);

#else

#define RV_HPM_SET_COUNTER(name, val)       \
    do {                                    \
        uint64_t value = val;               \
        __asm volatile("csrw " #name ", %0" \
                       :                    \
                       : "r"(value)         \
                       : "memory");         \
    } while (0);

#define RV_HPM_GET_COUNTER(name, val)    \
    do {                                 \
        uint64_t value;                  \
        __asm volatile("csrr %0, " #name \
                       : "=r"(value)     \
                       :                 \
                       : "memory");      \
        val = value;                     \
    } while (0);

#endif

/* Give permission for S-Mode */
inline __attribute__((always_inline)) void RV_HPM_Set_mcounteren(uint32_t mcounteren)
{
    __asm volatile("csrw mcounteren, %0"
                   :
                   : "r"(mcounteren)
                   : "memory");
}

/* Give permission for U-Mode */
inline __attribute__((always_inline)) void RV_HPM_Set_scounteren(uint32_t scounteren)
{
    __asm volatile("csrw mcounteren, %0"
                   :
                   : "r"(scounteren)
                   : "memory");
}

/* disable counter for power saving */
inline __attribute__((always_inline)) void RV_HPM_Set_mcountinhibit(uint32_t mcountinhibit)
{
    __asm volatile("csrw mcountinhibit, %0"
                   :
                   : "r"(mcountinhibit)
                   : "memory");
}

/* allow S-mode to write to counters */
inline __attribute__((always_inline)) void RV_HPM_Set_mcounterwen(uint32_t mcounterwen)
{
    __asm volatile("csrw mcounterwen, %0"
                   :
                   : "r"(mcounterwen)
                   : "memory");
}

/* M-mode: L1 ICache Miss rate measure Init               */
inline __attribute__((always_inline)) void RV_HPM_L1_ICache_Miss_Init_M(void)
{
    __asm volatile("csrw mhpmevent3, 1"
                   :
                   :
                   : "memory");
    __asm volatile("csrw mhpmevent4, 2"
                   :
                   :
                   : "memory");
    RV_HPM_SET_COUNTER(mhpmcounter3, 0);
    RV_HPM_SET_COUNTER(mhpmcounter4, 0);
}

/* M-mode: L1 ICache Miss rate measure end              */
inline __attribute__((always_inline)) void RV_HPM_L1_ICache_Miss_Stop_M(uint64_t *m, uint64_t *c)
{
    uint64_t miss, count;

    RV_HPM_GET_COUNTER(mhpmcounter3, count);
    RV_HPM_GET_COUNTER(mhpmcounter4, miss);

    *m = miss;
    *c = count;
}

/* M-mode: Conditional Branch Mispredict rate measure Init      */
inline __attribute__((always_inline)) void RV_HPM_L1_BrPredict_Miss_Init_M(void)
{
#ifdef CPU_M0
    __asm volatile("csrw mhpmevent8, 6"
                   :
                   :
                   : "memory");
    __asm volatile("csrw mhpmevent9, 7"
                   :
                   :
                   : "memory");
    RV_HPM_SET_COUNTER(mhpmcounter8, 0);
    RV_HPM_SET_COUNTER(mhpmcounter9, 0);
#endif
#ifdef CPU_D0
    __asm volatile("csrw mhpmevent9, 6"
                   :
                   :
                   : "memory");
    __asm volatile("csrw mhpmevent10, 7"
                   :
                   :
                   : "memory");
    RV_HPM_SET_COUNTER(mhpmcounter9, 0);
    RV_HPM_SET_COUNTER(mhpmcounter10, 0);
#endif
}

/* M-mode: Conditional Branch Mispredict rate measure end      */
inline __attribute__((always_inline)) void RV_HPM_L1_BrPredict_Miss_Stop_M(uint64_t *m, uint64_t *c)
{
    uint64_t miss, count;
#ifdef CPU_M0
    RV_HPM_GET_COUNTER(mhpmcounter9, count);
    RV_HPM_GET_COUNTER(mhpmcounter8, miss);
#endif
#ifdef CPU_D0
    RV_HPM_GET_COUNTER(mhpmcounter10, count);
    RV_HPM_GET_COUNTER(mhpmcounter9, miss);
#endif
    *m = miss;
    *c = count;
}

/* M-mode: L1 DCache read miss rate measure Init      */
inline __attribute__((always_inline)) void RV_HPM_L1_DCache_RdMiss_Init_M(void)
{
#ifdef CPU_M0
    __asm volatile("csrw mhpmevent14, 12"
                   :
                   :
                   : "memory");
    __asm volatile("csrw mhpmevent15, 13"
                   :
                   :
                   : "memory");
    RV_HPM_SET_COUNTER(mhpmcounter14, 0);
    RV_HPM_SET_COUNTER(mhpmcounter15, 0);
#endif
#ifdef CPU_D0
    __asm volatile("csrw mhpmevent5, 12"
                   :
                   :
                   : "memory");
    __asm volatile("csrw mhpmevent6, 13"
                   :
                   :
                   : "memory");
    RV_HPM_SET_COUNTER(mhpmcounter5, 0);
    RV_HPM_SET_COUNTER(mhpmcounter6, 0);
#endif
}

/* M-mode: L1 DCache read miss rate measure end      */
inline __attribute__((always_inline)) void RV_HPM_L1_DCache_RdMiss_Stop_M(uint64_t *m, uint64_t *c)
{
    uint64_t miss, count;
#ifdef CPU_M0
    RV_HPM_GET_COUNTER(mhpmcounter14, count);
    RV_HPM_GET_COUNTER(mhpmcounter15, miss);
#endif
#ifdef CPU_D0
    RV_HPM_GET_COUNTER(mhpmcounter5, count);
    RV_HPM_GET_COUNTER(mhpmcounter6, miss);
#endif
    *m = miss;
    *c = count;
}

/* M-mode: L1 DCache write miss rate measure Init      */
inline __attribute__((always_inline)) void RV_HPM_L1_DCache_WrMiss_Init_M(void)
{
#ifdef CPU_M0
    __asm volatile("csrw mhpmevent16, 14"
                   :
                   :
                   : "memory");
    __asm volatile("csrw mhpmevent17, 15"
                   :
                   :
                   : "memory");
    RV_HPM_SET_COUNTER(mhpmcounter16, 0);
    RV_HPM_SET_COUNTER(mhpmcounter17, 0);
#endif
#ifdef CPU_D0
    __asm volatile("csrw mhpmevent7, 14"
                   :
                   :
                   : "memory");
    __asm volatile("csrw mhpmevent8, 15"
                   :
                   :
                   : "memory");
    RV_HPM_SET_COUNTER(mhpmcounter7, 0);
    RV_HPM_SET_COUNTER(mhpmcounter8, 0);
#endif
}

/* M-mode: L1 DCache write miss rate measure end      */
inline __attribute__((always_inline)) void RV_HPM_L1_DCache_WrMiss_Stop_M(uint64_t *m, uint64_t *c)
{
    uint64_t miss, count;
#ifdef CPU_M0
    RV_HPM_GET_COUNTER(mhpmcounter16, count);
    RV_HPM_GET_COUNTER(mhpmcounter17, miss);
#endif
#ifdef CPU_D0
    RV_HPM_GET_COUNTER(mhpmcounter7, count);
    RV_HPM_GET_COUNTER(mhpmcounter8, miss);
#endif
    *m = miss;
    *c = count;
}

/* M-mode: TLB miss count measure Init      */
inline __attribute__((always_inline)) void RV_HPM_TLB_Miss_Init_M(void)
{
    __asm volatile("csrw mhpmevent5, 3"
                   :
                   :
                   : "memory");
    __asm volatile("csrw mhpmevent6, 4"
                   :
                   :
                   : "memory");
    __asm volatile("csrw mhpmevent7, 5"
                   :
                   :
                   : "memory");
    RV_HPM_SET_COUNTER(mhpmcounter5, 0);
    RV_HPM_SET_COUNTER(mhpmcounter6, 0);
    RV_HPM_SET_COUNTER(mhpmcounter7, 0);
}

/* M-mode: TLB miss count measure end      */
inline __attribute__((always_inline)) void RV_HPM_TLB_Miss_Stop_M(uint64_t *IuTLB, uint64_t *DuTLB, uint64_t *jTLB)
{
    uint64_t du, iu, j;

    RV_HPM_GET_COUNTER(mhpmcounter5, iu);
    RV_HPM_GET_COUNTER(mhpmcounter6, du);
    RV_HPM_GET_COUNTER(mhpmcounter7, j);

    *IuTLB = iu;
    *DuTLB = du;
    *jTLB = j;
}

/* M-mode: Store Instruction counter measure Init      */
/* C906 mhpmevent13 none */
inline __attribute__((always_inline)) void RV_HPM_Store_Insn_Init_M(void)
{
    __asm volatile("csrw mhpmevent13, 11"
                   :
                   :
                   : "memory");
    RV_HPM_SET_COUNTER(mhpmcounter13, 0);
}

/* M-mode: Store Instruction counter measure end      */
inline __attribute__((always_inline)) void RV_HPM_Store_Insn_Stop_M(uint64_t *sc)
{
    uint64_t count;

    RV_HPM_GET_COUNTER(mhpmcounter13, count);

    *sc = count;
}

/* M-Mode: Set cycle counter */
inline __attribute__((always_inline)) void RV_HPM_Cycle_Init_M(void)
{
    RV_HPM_SET_COUNTER(mcycle, 0);
}

/* M-Mode: Get cycle counter */
inline __attribute__((always_inline)) void RV_HPM_Cycle_Get_M(uint64_t *cycle)
{
    uint64_t count;

    RV_HPM_GET_COUNTER(mcycle, count);
    *cycle = count;
}

/* M-Mode: Set minstret counter */
inline __attribute__((always_inline)) void RV_HPM_Instret_Init_M(void)
{
    RV_HPM_SET_COUNTER(minstret, 0);
}

/* M-Mode: Get minstret counter */
inline __attribute__((always_inline)) void RV_HPM_Instret_Get_M(uint64_t *instret)
{
    uint64_t count;

    RV_HPM_GET_COUNTER(minstret, count);
    *instret = count;
}

#endif
