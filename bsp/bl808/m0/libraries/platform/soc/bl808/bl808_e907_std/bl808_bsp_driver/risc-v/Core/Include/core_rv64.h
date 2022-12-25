/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     core_rv64.h
 * @brief    CSI RV32 Core Peripheral Access Layer Header File
 * @version  V1.0
 * @date     01. Sep 2018
 ******************************************************************************/

#ifndef __CORE_RV32_H_GENERIC
#define __CORE_RV32_H_GENERIC

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *                 CSI definitions
 ******************************************************************************/
/**
  \ingroup RV32
  @{
 */

#ifndef __RV64
#define __RV64 (0x01U)
#endif

/** __FPU_USED indicates whether an FPU is used or not.
    This core does not support an FPU at all
*/
#define __FPU_USED 0U

#if defined(__GNUC__)
#if defined(__VFP_FP__) && !defined(__SOFTFP__)
#error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CORE_RV32_H_GENERIC */

#ifndef __CSI_GENERIC

#ifndef __CORE_RV32_H_DEPENDANT
#define __CORE_RV32_H_DEPENDANT

#ifdef __cplusplus
extern "C" {
#endif

/* check device defines and use defaults */
#ifndef __RV64_REV
#define __RV64_REV 0x0000U
#endif

#ifndef __VIC_PRIO_BITS
#define __VIC_PRIO_BITS 2U
#endif

#ifndef __Vendor_SysTickConfig
#define __Vendor_SysTickConfig 1U
#endif

#ifndef __MPU_PRESENT
#define __MPU_PRESENT 1U
#endif

#ifndef __ICACHE_PRESENT
#define __ICACHE_PRESENT 1U
#endif

#ifndef __DCACHE_PRESENT
#define __DCACHE_PRESENT 1U
#endif

#ifndef __L2CACHE_PRESENT
#define __L2CACHE_PRESENT 1U
#endif

#include <csi_rv64_gcc.h>

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CSI_glob_defs CSI Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
#ifdef __cplusplus
#define __I volatile /*!< Defines 'read only' permissions */
#else
#define __I volatile const /*!< Defines 'read only' permissions */
#endif
#define __O  volatile /*!< Defines 'write only' permissions */
#define __IO volatile /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define __IM  volatile const /*! Defines 'read only' structure member permissions */
#define __OM  volatile /*! Defines 'write only' structure member permissions */
#define __IOM volatile /*! Defines 'read / write' structure member permissions */

/*@} end of group C910 */

/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
  - Core CLINT Register
 ******************************************************************************/
/**
  \defgroup CSI_core_register Defines and Type Definitions
  \brief Type definitions and defines for CK80X processor based devices.
*/

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_CORE  Status and Control Registers
  \brief      Core Register type definitions.
  @{
 */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_CLINT Core-Local Interrupt Controller (CLINT)
  \brief      Type definitions for the CLINT Registers
  @{
 */

/**
  \brief Access to the structure of a vector interrupt controller.
 */

typedef struct
{
    // uint32_t RESERVED0;                 /*!< Offset: 0x000 (R/W)  CLINT configure register */
    __IOM uint32_t PLIC_PRIO[1024];
    __IOM uint32_t PLIC_IP[32];
    uint32_t RESERVED1[3972 / 4 - 1];
    __IOM uint32_t PLIC_H0_MIE[32];
    __IOM uint32_t PLIC_H0_SIE[32];
    __IOM uint32_t PLIC_H1_MIE[32];
    __IOM uint32_t PLIC_H1_SIE[32];
    __IOM uint32_t PLIC_H2_MIE[32];
    __IOM uint32_t PLIC_H2_SIE[32];
    __IOM uint32_t PLIC_H3_MIE[32];
    __IOM uint32_t PLIC_H3_SIE[32];
    uint32_t RESERVED2[(0x01FFFFC - 0x00023FC) / 4 - 1];
    __IOM uint32_t PLIC_PER;
    __IOM uint32_t PLIC_H0_MTH;
    __IOM uint32_t PLIC_H0_MCLAIM;
    uint32_t RESERVED3[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H0_STH;
    __IOM uint32_t PLIC_H0_SCLAIM;
    uint32_t RESERVED4[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H1_MTH;
    __IOM uint32_t PLIC_H1_MCLAIM;
    uint32_t RESERVED5[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H1_STH;
    __IOM uint32_t PLIC_H1_SCLAIM;
    uint32_t RESERVED6[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H2_MTH;
    __IOM uint32_t PLIC_H2_MCLAIM;
    uint32_t RESERVED7[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H2_STH;
    __IOM uint32_t PLIC_H2_SCLAIM;
    uint32_t RESERVED8[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H3_MTH;
    __IOM uint32_t PLIC_H3_MCLAIM;
    uint32_t RESERVED9[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H3_STH;
    __IOM uint32_t PLIC_H3_SCLAIM;
    uint32_t RESERVED10[0xFFC / 4 - 1];
} PLIC_Type;

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_PMP Physical Memory Protection (PMP)
  \brief      Type definitions for the PMP Registers
  @{
 */

#define PMP_PMPCFG_R_Pos 0U /*!< PMP PMPCFG: R Position */
#define PMP_PMPCFG_R_Msk (0x1UL << PMP_PMPCFG_R_Pos) /*!< PMP PMPCFG: R Mask */

#define PMP_PMPCFG_W_Pos 1U /*!< PMP PMPCFG: W Position */
#define PMP_PMPCFG_W_Msk (0x1UL << PMP_PMPCFG_W_Pos) /*!< PMP PMPCFG: W Mask */

#define PMP_PMPCFG_X_Pos 2U /*!< PMP PMPCFG: X Position */
#define PMP_PMPCFG_X_Msk (0x1UL << PMP_PMPCFG_X_Pos) /*!< PMP PMPCFG: X Mask */

#define PMP_PMPCFG_A_Pos 3U /*!< PMP PMPCFG: A Position */
#define PMP_PMPCFG_A_Msk (0x3UL << PMP_PMPCFG_A_Pos) /*!< PMP PMPCFG: A Mask */

#define PMP_PMPCFG_L_Pos 7U /*!< PMP PMPCFG: L Position */
#define PMP_PMPCFG_L_Msk (0x1UL << PMP_PMPCFG_L_Pos) /*!< PMP PMPCFG: L Mask */

typedef enum {
    REGION_SIZE_4B = -1,
    REGION_SIZE_8B = 0,
    REGION_SIZE_16B = 1,
    REGION_SIZE_32B = 2,
    REGION_SIZE_64B = 3,
    REGION_SIZE_128B = 4,
    REGION_SIZE_256B = 5,
    REGION_SIZE_512B = 6,
    REGION_SIZE_1KB = 7,
    REGION_SIZE_2KB = 8,
    REGION_SIZE_4KB = 9,
    REGION_SIZE_8KB = 10,
    REGION_SIZE_16KB = 11,
    REGION_SIZE_32KB = 12,
    REGION_SIZE_64KB = 13,
    REGION_SIZE_128KB = 14,
    REGION_SIZE_256KB = 15,
    REGION_SIZE_512KB = 16,
    REGION_SIZE_1MB = 17,
    REGION_SIZE_2MB = 18,
    REGION_SIZE_4MB = 19,
    REGION_SIZE_8MB = 20,
    REGION_SIZE_16MB = 21,
    REGION_SIZE_32MB = 22,
    REGION_SIZE_64MB = 23,
    REGION_SIZE_128MB = 24,
    REGION_SIZE_256MB = 25,
    REGION_SIZE_512MB = 26,
    REGION_SIZE_1GB = 27,
    REGION_SIZE_2GB = 28,
    REGION_SIZE_4GB = 29,
    REGION_SIZE_8GB = 30,
    REGION_SIZE_16GB = 31
} region_size_e;

typedef enum {
    ADDRESS_MATCHING_TOR = 1,
    ADDRESS_MATCHING_NAPOT = 3
} address_matching_e;

typedef struct
{
    uint32_t r           : 1; /* readable enable */
    uint32_t w           : 1; /* writeable enable */
    uint32_t x           : 1; /* execable enable */
    address_matching_e a : 2; /* address matching mode */
    uint32_t reserved    : 2; /* reserved */
    uint32_t l           : 1; /* lock enable */
} mpu_region_attr_t;

/*@} end of group CSI_PMP */

/* CACHE Register Definitions */
#define CACHE_MHCR_L0BTB_Pos 6U /*!< CACHE MHCR: L0BTB Position */
#define CACHE_MHCR_L0BTB_Msk (0x1UL << CACHE_MHCR_L0BTB_Pos) /*!< CACHE MHCR: WA Mask */

#define CACHE_MHCR_BPE_Pos 5U /*!< CACHE MHCR: BPE Position */
#define CACHE_MHCR_BPE_Msk (0x1UL << CACHE_MHCR_BPE_Pos) /*!< CACHE MHCR: BPE Mask */

#define CACHE_MHCR_RS_Pos 4U /*!< CACHE MHCR: RS Position */
#define CACHE_MHCR_RS_Msk (0x1UL << CACHE_MHCR_RS_Pos) /*!< CACHE MHCR: RS Mask */

#define CACHE_MHCR_WB_Pos 3U /*!< CACHE MHCR: WB Position */
#define CACHE_MHCR_WB_Msk (0x1UL << CACHE_MHCR_WB_Pos) /*!< CACHE MHCR: WB Mask */

#define CACHE_MHCR_WA_Pos 2U /*!< CACHE MHCR: WA Position */
#define CACHE_MHCR_WA_Msk (0x1UL << CACHE_MHCR_WA_Pos) /*!< CACHE MHCR: WA Mask */

#define CACHE_MHCR_DE_Pos 1U /*!< CACHE MHCR: DE Position */
#define CACHE_MHCR_DE_Msk (0x1UL << CACHE_MHCR_DE_Pos) /*!< CACHE MHCR: DE Mask */

#define CACHE_MHCR_IE_Pos 0U /*!< CACHE MHCR: IE Position */
#define CACHE_MHCR_IE_Msk (0x1UL << CACHE_MHCR_IE_Pos) /*!< CACHE MHCR: IE Mask */

#define CACHE_INV_ADDR_Pos 6U
#define CACHE_INV_ADDR_Msk (0xFFFFFFFFUL << CACHE_INV_ADDR_Pos)

/*@} end of group CSI_CACHE */

/**
  \ingroup  CSI_core_register
  \defgroup CSI_SysTick     System Tick Timer (CORET)
  \brief    Type definitions for the System Timer Registers.
  @{
 */

/**
  \brief  The data structure of the access system timer.
 */
typedef struct
{
    __IOM uint32_t MSIP0;
    __IOM uint32_t MSIP1;
    __IOM uint32_t MSIP2;
    __IOM uint32_t MSIP3;
    uint32_t RESERVED0[(0x4004000 - 0x400000C) / 4 - 1];
    __IOM uint32_t MTIMECMPL0;
    __IOM uint32_t MTIMECMPH0;
    __IOM uint32_t MTIMECMPL1;
    __IOM uint32_t MTIMECMPH1;
    __IOM uint32_t MTIMECMPL2;
    __IOM uint32_t MTIMECMPH2;
    __IOM uint32_t MTIMECMPL3;
    __IOM uint32_t MTIMECMPH3;
    uint32_t RESERVED1[(0x400C000 - 0x400401C) / 4 - 1];
    __IOM uint32_t SSIP0;
    __IOM uint32_t SSIP1;
    __IOM uint32_t SSIP2;
    __IOM uint32_t SSIP3;
    uint32_t RESERVED2[(0x400D000 - 0x400C00C) / 4 - 1];
    __IOM uint32_t STIMECMPL0;
    __IOM uint32_t STIMECMPH0;
    __IOM uint32_t STIMECMPL1;
    __IOM uint32_t STIMECMPH1;
    __IOM uint32_t STIMECMPL2;
    __IOM uint32_t STIMECMPH2;
    __IOM uint32_t STIMECMPL3;
    __IOM uint32_t STIMECMPH3;
} CORET_Type;
/*@} end of group CSI_SysTick */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_core_bitfield     Core register bit field macros
  \brief      Macros for use with bit field definitions (xxx_Pos, xxx_Msk).
  @{
 */

/**
  \brief   Mask and shift a bit field value for use in a register bit range.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of the bit field.
  \return           Masked and shifted value.
*/
#define _VAL2FLD(field, value) ((value << field##_Pos) & field##_Msk)

/**
  \brief     Mask and shift a register value to extract a bit filed value.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of register.
  \return           Masked and shifted bit field value.
*/
#define _FLD2VAL(field, value) ((value & field##_Msk) >> field##_Pos)

/*@} end of group CSI_core_bitfield */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */
#define CORET_BASE (PLIC_BASE + 0x4000000UL) /*!< CORET Base Address */
#define PLIC_BASE  (0x00E0000000UL) /*!< PLIC Base Address */
//#define PLIC_BASE           (0x4000000000UL)                          /*!< PLIC Base Address */

#define CORET ((CORET_Type *)CORET_BASE) /*!< SysTick configuration struct */
#define CLINT ((CORET_Type *)CORET_BASE) /*!< CLINT configuration struct */
#define PLIC  ((PLIC_Type *)PLIC_BASE) /*!< PLIC configuration struct */

/*@} */

/*******************************************************************************
 *                Hardware Abstraction Layer
  Core Function Interface contains:
  - Core VIC Functions
  - Core CORET Functions
  - Core Register Access Functions
 ******************************************************************************/
/**
  \defgroup CSI_Core_FunctionInterface Functions and Instructions Reference
*/

/* ##########################   VIC functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_VICFunctions VIC Functions
  \brief    Functions that manage interrupts and exceptions via the VIC.
  @{
 */

/* The following MACROS handle generation of the register offset and byte masks */
#define _BIT_SHIFT(IRQn) (((((uint32_t)(int32_t)(IRQn))) & 0x03UL) * 8UL)
#define _IP_IDX(IRQn)    ((((uint32_t)(int32_t)(IRQn)) >> 5UL))
#define _IP2_IDX(IRQn)   ((((uint32_t)(int32_t)(IRQn)) >> 2UL))

/**
  \brief   Enable External Interrupt
  \details Enable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_enable_irq(int32_t IRQn)
{
    //    CLINT->CLINTINT[IRQn].IE |= CLINT_INTIE_IE_Msk;

    PLIC->PLIC_H0_MIE[IRQn / 32] = PLIC->PLIC_H0_MIE[IRQn / 32] | (0x1 << (IRQn % 32));
}

/**
  \brief   Disable External Interrupt
  \details Disable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_disable_irq(int32_t IRQn)
{
    //CLINT->CLINTINT[IRQn].IE &= ~CLINT_INTIE_IE_Msk;
    PLIC->PLIC_H0_MIE[IRQn / 32] = PLIC->PLIC_H0_MIE[IRQn / 32] & (~(0x1 << (IRQn % 32)));
}

/**
  \brief   Enable External Interrupt targeted for S-mode
  \details Enable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_enable_irq_supervisor(int32_t IRQn)
{
    //    CLINT->CLINTINT[IRQn].IE |= CLINT_INTIE_IE_Msk;

    PLIC->PLIC_H0_SIE[IRQn / 32] = PLIC->PLIC_H0_SIE[IRQn / 32] | (0x1 << (IRQn % 32));
}

/**
  \brief   Disable External Interrupt targeted for S-mode
  \details Disable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_disable_irq_supervisor(int32_t IRQn)
{
    //CLINT->CLINTINT[IRQn].IE &= ~CLINT_INTIE_IE_Msk;
    PLIC->PLIC_H0_SIE[IRQn / 32] = PLIC->PLIC_H0_SIE[IRQn / 32] & (~(0x1 << (IRQn % 32)));
}

/**
  \brief   Set permission for S-mode PLIC access, can be set in M-mode ONLY
  \details Disable/Enable access to PLIC registers in S-mode.
  \param [in]      permission  Enable/Disable S-mode PLIC access.
 */
__STATIC_INLINE void csi_vic_supervisor_permission(int32_t permission)
{
    PLIC->PLIC_PER = !!permission ? 1 : 0;
}

/**
  \brief   Set interrupt priority threshold for M-mode
  \details Set interrupt priority threshold for M-mode, can be 0.
  \param [in]      th  interrupt threshold (5-bit).
 */
__STATIC_INLINE void csi_vic_pri_threashold_Machine(int32_t th)
{
    PLIC->PLIC_H0_MTH = th;
}

/**
  \brief   Set interrupt priority threshold for S-mode
  \details Set interrupt priority threshold for S-mode, can be 0.
  \param [in]      th  interrupt threshold (5-bit).
 */
__STATIC_INLINE void csi_vic_pri_threashold_Supervisor(int32_t th)
{
    PLIC->PLIC_H0_STH = th;
}

/**
  \brief   Enable External Secure Interrupt
  \details Enable a secure device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_enable_sirq(int32_t IRQn)
{
    //CLINT->CLINTINT[IRQn].IE |= (CLINT_INTIE_IE_Msk | CLINT_INTIE_T_Msk);
    csi_vic_enable_irq(IRQn);
}

/**
  \brief   Disable External Secure Interrupt
  \details Disable a secure device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_disable_sirq(int32_t IRQn)
{
    //CLINT->CLINTINT[IRQn].IE &= ~(CLINT_INTIE_IE_Msk | CLINT_INTIE_T_Msk);
    csi_vic_disable_irq(IRQn);
}

/**
  \brief   Check Interrupt is Enabled or not
  \details Read the enabled register in the VIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not enabled.
  \return             1  Interrupt status is enabled.
 */
__STATIC_INLINE uint32_t csi_vic_get_enabled_irq(int32_t IRQn)
{
    //    return (uint32_t)(CLINT->CLINTINT[IRQn].IE & CLINT_INTIE_IE_Msk);
    return (uint32_t)((PLIC->PLIC_H0_MIE[IRQn / 32] >> IRQn % 32) & 0x1);
}

/**
  \brief   Check Interrupt is Pending or not
  \details Read the pending register in the VIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
 */
__STATIC_INLINE uint32_t csi_vic_get_pending_irq(int32_t IRQn)
{
    //    return (uint32_t)(CLINT->CLINTINT[IRQn].IP & CLINT_INTIP_IP_Msk);

    return (uint32_t)((PLIC->PLIC_IP[IRQn / 32] >> IRQn % 32) & 0x1);
}

/**
  \brief   Set Pending Interrupt
  \details Set the pending bit of an external interrupt.
  \param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_set_pending_irq(int32_t IRQn)
{
    //    CLINT->CLINTINT[IRQn].IP |= CLINT_INTIP_IP_Msk;
    PLIC->PLIC_IP[IRQn / 32] = PLIC->PLIC_IP[IRQn / 32] | (0x1 << (IRQn % 32));
}

/**
  \brief   Clear Pending Interrupt
  \details Clear the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_clear_pending_irq(int32_t IRQn)
{
    //    CLINT->CLINTINT[IRQn].IP &= ~CLINT_INTIP_IP_Msk;
    //    PLIC->PLIC_H0_SCLAIM = IRQn;
    PLIC->PLIC_IP[IRQn / 32] = PLIC->PLIC_IP[IRQn / 32] & (~(0x1 << (IRQn % 32)));
}

/**
  \brief   Set Interrupt Priority
  \details Set the priority of an interrupt.
  \note    The priority cannot be set for every core interrupt.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
 */
__STATIC_INLINE void csi_vic_set_prio(int32_t IRQn, uint32_t priority)
{
    //    uint8_t nlbits = (CLINT->CLINTINFO & CLINT_INFO_CLINTINTCTLBITS_Msk) >> CLINT_INFO_CLINTINTCTLBITS_Pos;
    //    CLINT->CLINTINT[IRQn].CTL = (CLINT->CLINTINT[IRQn].CTL & (~CLINT_INTCFG_PRIO_Msk)) | (priority << (8 - nlbits));

    PLIC->PLIC_PRIO[IRQn] = priority;
}

/**
  \brief   Get Interrupt Priority
  \details Read the priority of an interrupt.
           The interrupt number can be positive to specify an external (device specific) interrupt,
           or negative to specify an internal (core) interrupt.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
__STATIC_INLINE uint32_t csi_vic_get_prio(int32_t IRQn)
{
    //    uint8_t nlbits = (CLINT->CLINTINFO & CLINT_INFO_CLINTINTCTLBITS_Msk) >> CLINT_INFO_CLINTINTCTLBITS_Pos;
    //    return CLINT->CLINTINT[IRQn].CTL >> (8 - nlbits);

    uint32_t prio = PLIC->PLIC_PRIO[IRQn];
    return prio;
}

/**
  \brief   Set interrupt handler
  \details Set the interrupt handler according to the interrupt num, the handler will be filled in irq vectors.
  \param [in]      IRQn  Interrupt number.
  \param [in]   handler  Interrupt handler.
 */
__STATIC_INLINE void csi_vic_set_vector(int32_t IRQn, uint64_t handler)
{
    if (IRQn >= 0 && IRQn < 1024) {
        uint64_t *vectors = (uint64_t *)__get_MTVT();
        vectors[IRQn] = handler;
    }
}

/**
  \brief   Get interrupt handler
  \details Get the address of interrupt handler function.
  \param [in]      IRQn  Interrupt number.
 */
__STATIC_INLINE uint32_t csi_vic_get_vector(int32_t IRQn)
{
    if (IRQn >= 0 && IRQn < 1024) {
        uint64_t *vectors = (uint64_t *)__get_MTVT();
        return (uint32_t)vectors[IRQn];
    }

    return 0;
}

/*@} end of CSI_Core_VICFunctions */

/* ##########################   PMP functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_PMPFunctions PMP Functions
  \brief    Functions that manage interrupts and exceptions via the VIC.
  @{
 */

/**
  \brief  configure memory protected region.
  \details
  \param [in]  idx        memory protected region (0, 1, 2, ..., 15).
  \param [in]  base_addr  base address must be aligned with page size.
  \param [in]  size       \ref region_size_e. memory protected region size.
  \param [in]  attr       \ref region_size_t. memory protected region attribute.
  \param [in]  enable     enable or disable memory protected region.
  */
__STATIC_INLINE void csi_mpu_config_region(uint32_t idx, uint32_t base_addr, region_size_e size,
                                           mpu_region_attr_t attr, uint32_t enable)
{
    uint8_t pmpxcfg = 0;
    uint32_t addr = 0;

    if (idx > 15) {
        return;
    }

    if (!enable) {
        attr.a = 0;
    }

    if (attr.a == ADDRESS_MATCHING_TOR) {
        addr = base_addr >> 2;
    } else {
        if (size == REGION_SIZE_4B) {
            addr = base_addr >> 2;
            attr.a = 2;
        } else {
            addr = ((base_addr >> 2) & (0xFFFFFFFFU - ((1 << (size + 1)) - 1))) | ((1 << size) - 1);
        }
    }

    __set_PMPADDRx(idx, addr);

    pmpxcfg |= (attr.r << PMP_PMPCFG_R_Pos) | (attr.w << PMP_PMPCFG_W_Pos) |
               (attr.x << PMP_PMPCFG_X_Pos) | (attr.a << PMP_PMPCFG_A_Pos) |
               (attr.l << PMP_PMPCFG_L_Pos);

    __set_PMPxCFG(idx, pmpxcfg);
}

/**
  \brief  disable mpu region by idx.
  \details
  \param [in]  idx        memory protected region (0, 1, 2, ..., 15).
  */
__STATIC_INLINE void csi_mpu_disable_region(uint32_t idx)
{
    __set_PMPxCFG(idx, __get_PMPxCFG(idx) & (~PMP_PMPCFG_A_Msk));
}

/*@} end of CSI_Core_PMPFunctions */

/* ##################################    SysTick function  ############################################ */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_SysTickFunctions SysTick Functions
  \brief    Functions that configure the System.
  @{
 */

/**
  \brief   CORE timer Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \param [in]  IRQn   core timer Interrupt number.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
__STATIC_INLINE uint32_t csi_coret_config(uint32_t ticks, int32_t IRQn)
{
    uint64_t value = (((uint64_t)CORET->MTIMECMPH0) << 32) + (uint64_t)CORET->MTIMECMPL0;

#if 0

	if(value)
	{
		value = value + (uint64_t)ticks;
		CORET->MTIMECMPH0 = (uint32_t)(value >> 32);
		CORET->MTIMECMPL0 = (uint32_t)value;
	}
	else
	{
		uint64_t result;
		__ASM volatile("csrr %0, 0xc01" : "=r"(result));

		value = result + (uint64_t)ticks;
		CORET->MTIMECMPH0 = (uint32_t)(value >> 32);
		CORET->MTIMECMPL0 = (uint32_t)value;
	}

#else
    value = value + (uint64_t)ticks;
    CORET->MTIMECMPH0 = (uint32_t)(value >> 32);
    CORET->MTIMECMPL0 = (uint32_t)value;
#endif

    return (0UL);
}

/**
  \brief   CORE timer Configuration in use
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \param [in]  IRQn   core timer Interrupt number.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
__STATIC_INLINE uint32_t csi_coret_config_use(uint32_t ticks, int32_t IRQn)
{
    uint64_t value;
    __ASM volatile("csrr %0, time"
                   : "=r"(value));
    value = value + (uint64_t)ticks;
    CORET->MTIMECMPH0 = (uint32_t)(value >> 32);
    CORET->MTIMECMPL0 = (uint32_t)value;

    return (0UL);
}

/**
  \brief   get CORE timer reload value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint64_t csi_coret_get_load(void)
{
    uint64_t value = (((uint64_t)CORET->MTIMECMPH0) << 32) + (uint64_t)CORET->MTIMECMPL0;
    return value;
}

/**
  \brief   get CORE timer reload high value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint32_t csi_coret_get_loadh(void)
{
    uint64_t value = (((uint64_t)CORET->MTIMECMPH0) << 32) + (uint64_t)CORET->MTIMECMPL0;
    return (value >> 32) & 0xFFFFFFFF;
}

/**
  \brief   get CORE timer counter value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint64_t csi_coret_get_value(void)
{
    uint64_t result;
    __ASM volatile("csrr %0, 0xc01"
                   : "=r"(result));
    return result;
}

/**
  \brief   get CORE timer counter high value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint32_t csi_coret_get_valueh(void)
{
    uint64_t result;
    __ASM volatile("csrr %0, time"
                   : "=r"(result));
    return (result >> 32) & 0xFFFFFFFF;
}

/*@} end of CSI_core_DebugFunctions */

/* ##########################  Cache functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_CacheFunctions Cache Functions
  \brief    Functions that configure Instruction and Data cache.
  @{
 */

/**
  \brief   Enable I-Cache
  \details Turns on I-Cache
  */
__STATIC_INLINE void csi_icache_enable(void)
{
#if (__ICACHE_PRESENT == 1U)
    uint32_t cache;
    __DSB();
    __ISB();
    __ICACHE_IALL();
    cache = __get_MHCR();
    cache |= CACHE_MHCR_IE_Msk;
    __set_MHCR(cache);
    __DSB();
    __ISB();
#endif
}

/**
  \brief   Disable I-Cache
  \details Turns off I-Cache
  */
__STATIC_INLINE void csi_icache_disable(void)
{
#if (__ICACHE_PRESENT == 1U)
    uint32_t cache;
    __DSB();
    __ISB();
    cache = __get_MHCR();
    cache &= ~CACHE_MHCR_IE_Msk; /* disable icache */
    __set_MHCR(cache);
    __ICACHE_IALL(); /* invalidate all icache */
    __DSB();
    __ISB();
#endif
}

/**
  \brief   Invalidate I-Cache
  \details Invalidates I-Cache
  */
__STATIC_INLINE void csi_icache_invalid(void)
{
#if (__ICACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __ICACHE_IALL(); /* invalidate all icache */
    __DSB();
    __ISB();
#endif
}

/**
  \brief   Enable D-Cache
  \details Turns on D-Cache
  \note    I-Cache also turns on.
  */
__STATIC_INLINE void csi_dcache_enable(void)
{
#if (__DCACHE_PRESENT == 1U)
    uint32_t cache;
    __DSB();
    __ISB();
    __DCACHE_IALL(); /* invalidate all dcache */
    cache = __get_MHCR();
    cache |= (CACHE_MHCR_DE_Msk | CACHE_MHCR_WB_Msk | CACHE_MHCR_WA_Msk | CACHE_MHCR_RS_Msk | CACHE_MHCR_BPE_Msk | CACHE_MHCR_L0BTB_Msk); /* enable all Cache */
    __set_MHCR(cache);

    __DSB();
    __ISB();
#endif
}

/**
  \brief   Disable D-Cache
  \details Turns off D-Cache
  \note    I-Cache also turns off.
  */
__STATIC_INLINE void csi_dcache_disable(void)
{
#if (__DCACHE_PRESENT == 1U)
    uint32_t cache;
    __DSB();
    __ISB();
    cache = __get_MHCR();
    cache &= ~(uint32_t)CACHE_MHCR_DE_Msk; /* disable all Cache */
    __set_MHCR(cache);
    __DCACHE_IALL(); /* invalidate all Cache */
    __DSB();
    __ISB();
#endif
}

/**
  \brief   Invalidate D-Cache
  \details Invalidates D-Cache
  \note    I-Cache also invalid
  */
__STATIC_INLINE void csi_dcache_invalid(void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __DCACHE_IALL(); /* invalidate all Cache */
    __DSB();
#endif
}

/**
  \brief   Clean D-Cache
  \details Cleans D-Cache
  \note    I-Cache also cleans
  */
__STATIC_INLINE void csi_dcache_clean(void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __DCACHE_CALL(); /* clean all Cache */
    __DSB();
#endif
}

/**
  \brief   Clean & Invalidate D-Cache
  \details Cleans and Invalidates D-Cache
  \note    I-Cache also flush.
  */
__STATIC_INLINE void csi_dcache_clean_invalid(void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __DCACHE_CIALL(); /* clean and inv all Cache */
    __DSB();
#endif
}

/**
  \brief   Invalidate L2-Cache
  \details Invalidates L2-Cache
  \note
  */
__STATIC_INLINE void csi_l2cache_invalid(void)
{
#if (__L2CACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __L2CACHE_IALL(); /* invalidate l2 Cache */
    __DSB();
    __ISB();
#endif
}

/**
  \brief   Clean L2-Cache
  \details Cleans L2-Cache
  \note
  */
__STATIC_INLINE void csi_l2cache_clean(void)
{
#if (__L2CACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __L2CACHE_CALL(); /* clean l2 Cache */
    __DSB();
    __ISB();
#endif
}

/**
  \brief   Clean & Invalidate L2-Cache
  \details Cleans and Invalidates L2-Cache
  \note
  */
__STATIC_INLINE void csi_l2cache_clean_invalid(void)
{
#if (__L2CACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __L2CACHE_CIALL(); /* clean and inv l2 Cache */
    __DSB();
    __ISB();
#endif
}

/**
  \brief   D-Cache Invalidate by address
  \details Invalidates D-Cache for the given address
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void csi_dcache_invalid_range(uint64_t *addr, int64_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int64_t op_size = dsize + (uint64_t)addr % 64;
    uint64_t op_addr = (uint64_t)addr;
    int64_t linesize = 64;

    __DSB();

    while (op_size > 0) {
        __DCACHE_IPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
#endif
}

/**
  \brief   D-Cache Clean by address
  \details Cleans D-Cache for the given address
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void csi_dcache_clean_range(uint64_t *addr, int64_t dsize)
{
#if (__DCACHE_PRESENT == 1)
    int64_t op_size = dsize + (uint64_t)addr % 64;
    uint64_t op_addr = (uint64_t)addr & CACHE_INV_ADDR_Msk;
    int64_t linesize = 64;

    __DSB();

    while (op_size > 0) {
        __DCACHE_CPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
#endif
}

/**
  \brief   D-Cache Clean and Invalidate by address
  \details Cleans and invalidates D_Cache for the given address
  \param[in]   addr    address (aligned to 16-byte boundary)
  \param[in]   dsize   size of memory block (aligned to 16-byte boundary)
*/
__STATIC_INLINE void csi_dcache_clean_invalid_range(uint64_t *addr, int64_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int64_t op_size = dsize + (uint64_t)addr % 64;
    uint64_t op_addr = (uint64_t)addr;
    int64_t linesize = 64;

    __DSB();

    while (op_size > 0) {
        __DCACHE_CIPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
#endif
}

/**
  \brief   setup cacheable range Cache
  \details setup Cache range
  */
__STATIC_INLINE void csi_cache_set_range(uint32_t index, uint32_t baseAddr, uint32_t size, uint32_t enable)
{
    ;
}

/**
  \brief   Enable cache profile
  \details Turns on Cache profile
  */
__STATIC_INLINE void csi_cache_enable_profile(void)
{
    ;
}

/**
  \brief   Disable cache profile
  \details Turns off Cache profile
  */
__STATIC_INLINE void csi_cache_disable_profile(void)
{
    ;
}

/**
  \brief   Reset cache profile
  \details Reset Cache profile
  */
__STATIC_INLINE void csi_cache_reset_profile(void)
{
    ;
}

/**
  \brief   cache access times
  \details Cache access times
  \note    every 256 access add 1.
  \return          cache access times, actual times should be multiplied by 256
  */
__STATIC_INLINE uint32_t csi_cache_get_access_time(void)
{
    return 0;
}

/**
  \brief   cache miss times
  \details Cache miss times
  \note    every 256 miss add 1.
  \return          cache miss times, actual times should be multiplied by 256
  */
__STATIC_INLINE uint32_t csi_cache_get_miss_time(void)
{
    return 0;
}

/*@} end of CSI_Core_CacheFunctions */

/*@} end of CSI_core_DebugFunctions */

/* ##################################    IRQ Functions  ############################################ */

/**
  \brief   Save the Irq context
  \details save the psr result before disable irq.
 */
__STATIC_INLINE uint32_t csi_irq_save(void)
{
    uint32_t result;
    result = __get_MSTATUS();
    __disable_irq();
    return (result);
}

/**
  \brief   Restore the Irq context
  \details restore saved primask state.
  \param [in]      irq_state  psr irq state.
 */
__STATIC_INLINE void csi_irq_restore(uint32_t irq_state)
{
    __set_MSTATUS(irq_state);
}

/*@} end of IRQ Functions */

#ifdef __cplusplus
}
#endif

#endif /* __CORE_RV32_H_DEPENDANT */

#endif /* __CSI_GENERIC */
