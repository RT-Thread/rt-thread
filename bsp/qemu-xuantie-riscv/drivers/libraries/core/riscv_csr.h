/*
 * Copyright (C) 2018-2024 Alibaba Group Holding Limited
 */

/*
 * attention: don't modify this file as a suggest
 * you should copy from chip_riscv_dummy/include/asm/riscv_csr.h and keep it newer
 * please contact xuantie-rtos os team if have question
 */

#ifndef __RISCV_CSR_H__
#define __RISCV_CSR_H__

#if __riscv_xlen == 64
    #define portWORD_SIZE 8
    #define store_x       sd
    #define load_x        ld
#elif __riscv_xlen == 32
    #define store_x       sw
    #define load_x        lw
    #define portWORD_SIZE 4
#else
    #error Assembler did not define __riscv_xlen
#endif

#if __riscv_flen == 64
    #define fstore_x      fsd
    #define fload_x       fld
#elif __riscv_flen == 32
    #define fstore_x      fsw
    #define fload_x       flw
#endif

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
#define MODE_PREFIX(suffix) s##suffix
#else
#define MODE_PREFIX(suffix) m##suffix
#endif

/* Status register flags */
#define SR_SIE      0x00000002UL        /*  Supervisor Interrupt Enable */
#define SR_MIE      0x00000008UL        /*  Machine Interrupt Enable */
#define SR_SPIE     0x00000020UL        /*  Previous Supervisor IE */
#define SR_MPIE     0x00000080UL        /*  Previous Machine IE */
#define SR_SPP_U    0x00000000UL        /*  Previously User mode */
#define SR_SPP_S    0x00000100UL        /*  Previously Supervisor mode */
#define SR_MPP_U    0x00000000UL        /*  Previously User mode */
#define SR_MPP_S    0x00000800UL        /*  Previously Supervisor mode */
#define SR_MPP_M    0x00001800UL        /*  Previously Machine mode */
#define SR_SUM      0x00040000UL        /*  Supervisor User Memory Access */

#define SR_FS           0x00006000UL    /*  Floating-point Status */
#define SR_FS_OFF       0x00000000UL
#define SR_FS_INITIAL   0x00002000UL
#define SR_FS_CLEAN     0x00004000UL
#define SR_FS_DIRTY     0x00006000UL

#if CONFIG_CPU_C906 || CONFIG_CPU_C906FD || CONFIG_CPU_C906FDV || CONFIG_CPU_C910 || CONFIG_CPU_C920
#define SR_VS          0x01800000
#define SR_VS_OFF      0x00000000
#define SR_VS_INITIAL  0x00800000
#define SR_VS_CLEAN    0x01000000
#define SR_VS_DIRTY    0x01800000
#else
#define SR_VS          0x00000600
#define SR_VS_OFF      0x00000000
#define SR_VS_INITIAL  0x00000200
#define SR_VS_CLEAN    0x00000400
#define SR_VS_DIRTY    0x00000600
#endif

#if __riscv_matrix
#define SR_MS          0x06000000
#define SR_MS_OFF      0x00000000
#define SR_MS_INITIAL  0x02000000
#define SR_MS_CLEAN    0x04000000
#define SR_MS_DIRTY    0x06000000
#endif

/* Interrupt-enable Registers */
#define IE_MTIE         0x00000080UL
#define IE_MEIE         0x00000800UL

/*  ===== Trap/Exception Causes ===== */
#define CAUSE_MISALIGNED_FETCH          0x0
#define CAUSE_FETCH_ACCESS              0x1
#define CAUSE_ILLEGAL_INSTRUCTION       0x2
#define CAUSE_BREAKPOINT                0x3
#define CAUSE_MISALIGNED_LOAD           0x4
#define CAUSE_LOAD_ACCESS               0x5
#define CAUSE_MISALIGNED_STORE          0x6
#define CAUSE_STORE_ACCESS              0x7
#define CAUSE_USER_ECALL                0x8
#define CAUSE_SUPERVISOR_ECALL          0x9
#define CAUSE_VIRTUAL_SUPERVISOR_ECALL  0xa
#define CAUSE_MACHINE_ECALL             0xb
#define CAUSE_FETCH_PAGE_FAULT          0xc
#define CAUSE_LOAD_PAGE_FAULT           0xd
#define CAUSE_STORE_PAGE_FAULT          0xf

#define PRV_U                           0
#define PRV_S                           1
#define PRV_M                           3


#define MSTATUS_SIE                     0x00000002
#define MSTATUS_MIE                     0x00000008
#define MSTATUS_SPIE_SHIFT              5
#define MSTATUS_SPIE                    (1 << MSTATUS_SPIE_SHIFT)
#define MSTATUS_UBE                     0x00000040
#define MSTATUS_MPIE                    0x00000080
#define MSTATUS_SPP_SHIFT               8
#define MSTATUS_SPP                     (1 << MSTATUS_SPP_SHIFT)
#define MSTATUS_MPP_SHIFT               11
#define MSTATUS_MPP                     (3 << MSTATUS_MPP_SHIFT)

#if CONFIG_CPU_C906 || CONFIG_CPU_C906FD || CONFIG_CPU_C906FDV || CONFIG_CPU_C910 || CONFIG_CPU_C920
#define MSTATUS_VS_SHIFT                23
#else
#define MSTATUS_VS_SHIFT                9
#endif
#define MSTATUS_FS_SHIFT                13
#define MSTATUS_MS_SHIFT                25

#define INSERT_FIELD(val, which, fieldval)  (((val) & ~(which)) | ((fieldval) * ((which) & ~((which)-1))))

#if CONFIG_CPU_C906 || CONFIG_CPU_C906FD || CONFIG_CPU_C906FDV || CONFIG_CPU_C910 || CONFIG_CPU_C920 || CONFIG_CPU_C908 || CONFIG_CPU_C908V ||CONFIG_CPU_C908I
#define ATTR_SO                 (1ull << 4)
#define ATTR_CA                 (1ull << 3)
#define ATTR_BU                 (1ull << 2)
#define ATTR_SH                 (1ull << 1)
#define ATTR_SE                 (1ull << 0)

#define UPPER_ATTRS_SHIFT       (59)
#define UPPER_ATTRS(x)          (((x) & 0x1f) << UPPER_ATTRS_SHIFT)
#else
#if __riscv_xlen == 32
#define PTE_PBMT_SHIFT          (30)
#else
#define PTE_PBMT_SHIFT          (61)
#endif /* end __riscv_xlen */
#define SVPBMT_PMA              ((unsigned long)0x0 << PTE_PBMT_SHIFT)
#define SVPBMT_NC               ((unsigned long)0x1 << PTE_PBMT_SHIFT)
#define SVPBMT_IO               ((unsigned long)0x2 << PTE_PBMT_SHIFT)
#define SVPBMT_MASK             ((unsigned long)0x3 << PTE_PBMT_SHIFT)

#endif

#define DIRTY_FLAG              (1 << 6)
#define ACCESS_FLAG             (1 << 5)
#define GLOBAL_FLAG             (1 << 4)
#define AP_UNPRIV               (1 << 3)
#define AP_X                    (1 << 2)
#define AP_W                    (1 << 1)
#define AP_R                    (1 << 0)

#define LOWER_ATTRS_SHIFT               1
#define LOWER_ATTRS(x)                  (((x) & 0x1ff) << LOWER_ATTRS_SHIFT)



#endif /* __RISCV_CSR_H__ */