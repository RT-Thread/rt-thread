#ifndef __RV_SV39_H__
#define __RV_SV39_H__

#include <stdint.h>
#include "bl808_common.h"

#define SV39_VPN2(va) (((va) >> (9 + 9 + 12)) & 0x1FF)
#define SV39_VPN1(va) (((va) >> (0 + 9 + 12)) & 0x1FF)
#define SV39_VPN0(va) (((va) >> (0 + 0 + 12)) & 0x1FF)

#define SV39_PA2PPN(pa)   (((pa) >> (0 + 0 + 12)) & 0xFFFFFFFFFF)
#define SV39_PTE2PPN(pte) (((pte) >> (10)) & 0xFFFFFFF)
#define SV39_PTE2PA(pte)  ((uint64_t)(SV39_PTE2PPN(pte) << 12))

#define SV39_JTLB_ENTRY_CNT (256)

/* SMCIR */
#define SMCIR_ASID_OFFSET (0)
#define SMCIR_ASID_LEN    (16)

#define SMCIR_TLBII_OFFSET (25)
#define SMCIR_TLBII_LEN    (1)
#define SMCIR_TLBII        (1 << 25)

#define SMCIR_TLBIALL_OFFSET (26)
#define SMCIR_TLBIALL_LEN    (1)
#define SMCIR_TLBIALL        (1 << 26)

#define SMCIR_TLBIASID_OFFSET (27)
#define SMCIR_TLBIASID_LEN    (1)
#define SMCIR_TLBIASID        (1 << 27)

#define SMCIR_TLBWR_OFFSET (28)
#define SMCIR_TLBWR_LEN    (1)
#define SMCIR_TLBWR        (1 << 28)

#define SMCIR_TLBWI_OFFSET (29)
#define SMCIR_TLBWI_LEN    (1)
#define SMCIR_TLBWI        (1 << 29)

#define SMCIR_TLBR_OFFSET (30)
#define SMCIR_TLBR_LEN    (1)
#define SMCIR_TLBR        (1 << 30)

#define SMCIR_TLBP_OFFSET (31)
#define SMCIR_TLBP_LEN    (1)
#define SMCIR_TLBP        (1 << 31)

/* SMIR */
#define SMIR_INDEX_OFFSET (0)
#define SMIR_INDEX_LEN    (9)

#define SMCIR_T_OFFSET (30)
#define SMCIR_TF_LEN   (1)
#define SMCIR_TF       (1 << 30)

#define SMCIR_P_OFFSET (31)
#define SMCIR_PF_LEN   (1)
#define SMCIR_PF       (1 << 31)

/* SMEH */
#define SMEH_ASID_OFFSET (0)
#define SMEH_ASID_LEN    (16)

#define SMEH_PAGESIZE_OFFSET (16)
#define SMEH_PAGESIZE_LEN    (3)
#define SMEH_PAGESIZE_4KB    (1 << 16)
#define SMEH_PAGESIZE_2MB    (2 << 16)
#define SMEH_PAGESIZE_1GB    (4 << 16)

#define SMEH_VPN_OFFSET (19)
#define SMEH_VPN_LEN    (27)

#undef PTE_V
#undef PTE_U
#undef PTE_G
#undef PTE_A
#undef PTE_D

/* SMEL & PTE */
#define PTE_V_OFFSET (0)
#define PTE_V_LEN    (1)
#define PTE_V        (1 << 0)

#define PTE_R_OFFSET (1)
#define PTE_R_LEN    (1)

#define PTE_W_OFFSET (2)
#define PTE_W_LEN    (1)

#define PTE_X_OFFSET (3)
#define PTE_X_LEN    (1)

#define PTE_XWR_MASK     (~(0xE))
#define PTE_XWR_NEXT     (0 << 1)
#define PTE_XWR_RO_PAGE  (1 << 1)
#define PTE_XWR_WR_PAGE  (3 << 1)
#define PTE_XWR_XO_PAGE  (4 << 1)
#define PTE_XWR_XR_PAGE  (5 << 1)
#define PTE_XWR_XWR_PAGE (7 << 1)

#define PTE_U_OFFSET (4)
#define PTE_U_LEN    (1)
#define PTE_U        (1 << 4)

#define PTE_G_OFFSET (5)
#define PTE_G_LEN    (1)
#define PTE_G        (1 << 5)

#define PTE_A_OFFSET (6)
#define PTE_A_LEN    (1)
#define PTE_A        (1 << 6)

#define PTE_D_OFFSET (7)
#define PTE_D_LEN    (1)
#define PTE_D        (1 << 7)

#define SMEL_PPN_OFFSET (8)
#define PTE_PPN_OFFSET  (10)
#define PTE_PPN_LEN     (28)

#define PTE_SEC_OFFSET (59)
#define PTE_SEC_LEN    (1)

#define PTE_B_OFFSET (61)
#define PTE_B_LEN    (1)
#define PTE_B        ((uintptr_t)1 << 61)

#define PTE_C_OFFSET (62)
#define PTE_C_LEN    (1)
#define PTE_C        ((uintptr_t)1 << 62)

#define PTE_SO_OFFSET (63)
#define PTE_SO_LEN    (1)
#define PTE_SO        ((uintptr_t)1 << 63)

/* SATP */
#define SATP_PPN_OFFSET (0)
#define SATP_PPN_LEN    (28)

#define SATP_ASID_OFFSET (44)
#define SATP_ASID_LEN    (16)

#define SATP_MODE_OFFSET (60)
#define SATP_MODE_LEN    (4)
#define SATP_MODE_SV39   ((uintptr_t)8 << 60)

typedef enum {
    Sv39_PAGESIZE_4KB = SMEH_PAGESIZE_4KB,
    Sv39_PAGESIZE_2MB = SMEH_PAGESIZE_2MB,
    Sv39_PAGESIZE_1GB = SMEH_PAGESIZE_1GB,
    Sv39_PAGESIZE_NUM,
    Sv39_PAGESIZE_MAX = 0x7FFFFFFFFFFFFFFF
} Sv39_PAGESIZE_Type;

typedef enum {
    Sv39_PTE_LOC_JTLB = 0,
    Sv39_PTE_LOC_PAGETABLE,
    Sv39_PTE_LOC_NUM,
    Sv39_PTE_LOC_MAX = 0x7FFFFFFFFFFFFFFF
} Sv39_PTE_LOC_Type;

typedef struct _Sv39_PTE_cfg {
    uintptr_t va;
    uintptr_t pa;
    Sv39_PAGESIZE_Type size;
    uintptr_t flags;
    uintptr_t asid;
    Sv39_PTE_LOC_Type where;
    uintptr_t tlb_entry;
} Sv39_PTE_cfg_t;

__ALWAYS_STATIC_INLINE void RV_Sv39_INVALID_VMA(void)
{
    __asm volatile("fence"
                   :
                   :
                   : "memory");
    __asm volatile("sfence.vma x0,x0"
                   :
                   :
                   : "memory");
    __asm volatile("fence"
                   :
                   :
                   : "memory");
}

__ALWAYS_STATIC_INLINE void RV_Sv39_Set_SMCIR(uintptr_t smcir)
{
    __asm volatile("csrw smcir, %0"
                   :
                   : "r"(smcir)
                   : "memory");
}

__ALWAYS_STATIC_INLINE uintptr_t RV_Sv39_Get_SMIR(void)
{
    uintptr_t result;

    __asm volatile("csrr %0, smir"
                   : "=r"(result)
                   :
                   : "memory");
    return (result);
}

__ALWAYS_STATIC_INLINE void RV_Sv39_Set_SMIR(uintptr_t smir)
{
    __asm volatile("csrw smir, %0"
                   :
                   : "r"(smir)
                   : "memory");
}

__ALWAYS_STATIC_INLINE void RV_Sv39_Set_SATP(uintptr_t asid, uintptr_t *ppn)
{
    __asm volatile("csrw satp, %0"
                   :
                   : "r"(SATP_MODE_SV39 | (asid << SATP_ASID_OFFSET) | ((uintptr_t)(ppn) >> 12))
                   : "memory");
}

/* cache config into jTLB, return tlb index if success */
BL_Err_Type RV_Sv39_Create_PageMapping(Sv39_PTE_cfg_t *cfg, uintptr_t *tlb_index, volatile uint64_t *ttb0);

#endif /* __RV_SV39_H__ */
