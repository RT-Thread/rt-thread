/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     core_rv32.h
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

#ifndef __RV32
#define __RV32 (0x01U)
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
#ifndef __RV32_REV
#define __RV32_REV 0x0000U
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

#include <csi_rv32_gcc.h>

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

/*@} end of group RV32 */

/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
  - Core CLIC Register
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
  \defgroup   CSI_CLIC Core-Local Interrupt Controller (CLIC)
  \brief      Type definitions for the CLIC Registers
  @{
 */

/**
  \brief Access to the structure of a vector interrupt controller.
 */
typedef struct
{
    __IOM uint8_t IP;   /*!< Offset: 0x000 (R/W)  Interrupt set pending register */
    __IOM uint8_t IE;   /*!< Offset: 0x004 (R/W)  Interrupt set enable register */
    __IOM uint8_t ATTR; /*!< Offset: 0x008 (R/W)  Interrupt set attribute register */
    __IOM uint8_t CTL;  /*!< Offset: 0x00C (R/W)  Interrupt control register */
} CLIC_INT_Control;

typedef struct
{
    __IOM uint32_t CLICCFG : 8; /*!< Offset: 0x000 (R/W)  CLIC configure register */
    __IM uint32_t CLICINFO;
    __IOM uint32_t MINTTHRESH;
    uint32_t RESERVED[1021];
    CLIC_INT_Control CLICINT[4096];
} CLIC_Type;

#define CLIC_INFO_CLICINTCTLBITS_Pos 21U
#define CLIC_INFO_CLICINTCTLBITS_Msk (0xFUL << CLIC_INFO_CLICINTCTLBITS_Pos)

#define CLIC_INTIP_IP_Pos 0U /*!< CLIC INTIP: IP Position */
#define CLIC_INTIP_IP_Msk (0x1UL << CLIC_INTIP_IP_Pos) /*!< CLIC INTIP: IP Mask */

#define CLIC_INTIE_IE_Pos 0U /*!< CLIC INTIE: IE Position */
#define CLIC_INTIE_IE_Msk (0x1UL << CLIC_INTIE_IE_Pos) /*!< CLIC INTIE: IE Mask */

#define CLIC_INTIE_T_Pos 7U /*!< CLIC INTIE: T Position */
#define CLIC_INTIE_T_Msk (0x1UL << CLIC_INTIE_T_Pos) /*!< CLIC INTIE: T Mask */

#define CLIC_INTATTR_TRIG_Pos 1U /*!< CLIC INTATTR: TRIG Position */
#define CLIC_INTATTR_TRIG_Msk (0x3UL << CLIC_INTATTR_TRIG_Pos) /*!< CLIC INTATTR: TRIG Mask */

#define CLIC_INTATTR_SHV_Pos 0U /*!< CLIC INTATTR: SHV Position */
#define CLIC_INTATTR_SHV_Msk (0x1UL << CLIC_INTATTR_SHV_Pos) /*!< CLIC INTATTR: SHV Mask */

#define CLIC_INTCFG_NVBIT_Pos 5U /*!< CLIC INTCFG: NVBIT Position */
#define CLIC_INTCFG_NVBIT_Msk (0x1UL << CLIC_INTCFG_NVBIT_Pos) /*!< CLIC INTCFG: NVBIT Mask */

#define CLIC_INTCFG_PRIO_Pos 4U /*!< CLIC INTCFG: INTCFG Position */
#define CLIC_INTCFG_PRIO_Msk (0xFUL << CLIC_INTCFG_PRIO_Pos) /*!< CLIC INTCFG: INTCFG Mask */

#define CLIC_CLICCFG_NVBIT_Pos 0U /*!< CLIC CLICCFG: NVBIT Position */
#define CLIC_CLICCFG_NVBIT_Msk (0x1UL << CLIC_CLICCFG_NVBIT_Pos) /*!< CLIC CLICCFG: NVBIT Mask */

#define CLIC_CLICCFG_NLBIT_Pos 1U /*!< CLIC CLICCFG: NLBIT Position */
#define CLIC_CLICCFG_NLBIT_Msk (0xFUL << CLIC_CLICCFG_NLBIT_Pos) /*!< CLIC CLICCFG: NLBIT Mask */

#define CLIC_CLICCFG_NMBIT_Pos 5U /*!< CLIC CLICCFG: NMBIT Position */
#define CLIC_CLICCFG_NMBIT_Msk (0x3UL << CLIC_CLICCFG_NMBIT_Pos) /*!< CLIC CLICCFG: NMBIT Mask */

/*@} end of group CSI_CLIC */

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
#define CACHE_MHCR_L0BTB_Pos 12U /*!< CACHE MHCR: L0BTB Position */
#define CACHE_MHCR_L0BTB_Msk (0x1UL << CACHE_MHCR_L0BTB_Pos) /*!< CACHE MHCR: WA Mask */

#define CACHE_MHCR_BPE_Pos 5U /*!< CACHE MHCR: BPE Position */
#define CACHE_MHCR_BPE_Msk (0x1UL << CACHE_MHCR_BPE_Pos) /*!< CACHE MHCR: BPE Mask */

#define CACHE_MHCR_RS_Pos 4U /*!< CACHE MHCR: RS Position */
#define CACHE_MHCR_RS_Msk (0x1UL << CACHE_MHCR_RS_Pos) /*!< CACHE MHCR: RS Mask */

#define CACHE_MHCR_WA_Pos 3U /*!< CACHE MHCR: WA Position */
#define CACHE_MHCR_WA_Msk (0x1UL << CACHE_MHCR_WA_Pos) /*!< CACHE MHCR: WA Mask */

#define CACHE_MHCR_WB_Pos 2U /*!< CACHE MHCR: WB Position */
#define CACHE_MHCR_WB_Msk (0x1UL << CACHE_MHCR_WB_Pos) /*!< CACHE MHCR: WB Mask */

#define CACHE_MHCR_DE_Pos 1U /*!< CACHE MHCR: DE Position */
#define CACHE_MHCR_DE_Msk (0x1UL << CACHE_MHCR_DE_Pos) /*!< CACHE MHCR: DE Mask */

#define CACHE_MHCR_IE_Pos 0U /*!< CACHE MHCR: IE Position */
#define CACHE_MHCR_IE_Msk (0x1UL << CACHE_MHCR_IE_Pos) /*!< CACHE MHCR: IE Mask */

#define CACHE_INV_ADDR_Pos 5U
#define CACHE_INV_ADDR_Msk (0xFFFFFFFFUL << CACHE_INV_ADDR_Pos)

/*@} end of group CSI_CACHE */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_SYSMAP system map (SYSMAP)
  \brief      Type definitions for the SYSMAP Registers
  @{
 */

#define SYSMAP_SYSMAPCFG_B_Pos 0U /*!< SYSMAP SYSMAPCFG: B Position */
#define SYSMAP_SYSMAPCFG_B_Msk (0x1UL << SYSMAP_SYSMAPCFG_B_Pos) /*!< SYSMAP SYSMAPCFG: B Mask */

#define SYSMAP_SYSMAPCFG_C_Pos 1U /*!< SYSMAP SYSMAPCFG: C Position */
#define SYSMAP_SYSMAPCFG_C_Msk (0x1UL << SYSMAP_SYSMAPCFG_C_Pos) /*!< SYSMAP SYSMAPCFG: C Mask */

#define SYSMAP_SYSMAPCFG_SO_Pos 2U /*!< SYSMAP SYSMAPCFG: SO Position */
#define SYSMAP_SYSMAPCFG_SO_Msk (0x1UL << SYSMAP_SYSMAPCFG_SO_Pos) /*!< SYSMAP SYSMAPCFG: SO Mask */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_SYSMAP system map (SYSMAP)
  \brief      Type definitions for the SYSMAP Registers
  @{
 */
typedef struct
{
    __IOM uint32_t SYSMAPADDR0; /*!< Offset: 0x000 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG0;  /*!< Offset: 0x004 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR1; /*!< Offset: 0x008 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG1;  /*!< Offset: 0x00c (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR2; /*!< Offset: 0x010 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG2;  /*!< Offset: 0x014 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR3; /*!< Offset: 0x018 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG3;  /*!< Offset: 0x01c (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR4; /*!< Offset: 0x020 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG4;  /*!< Offset: 0x024 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR5; /*!< Offset: 0x028 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG5;  /*!< Offset: 0x02c (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR6; /*!< Offset: 0x030 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG6;  /*!< Offset: 0x034 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR7; /*!< Offset: 0x038 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG7;  /*!< Offset: 0x03c (R/W)  SYSMAP configure register */
} SYSMAP_Type;

/*@} end of group CSI_SYSMAP */

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
    __IOM unsigned long long MTIMECMP; /*!< Offset: 0x000 (R/W) Timer compare register */
    uint32_t RESERVED[8187];
    __IM unsigned long long MTIME; /*!< Offset: 0x7FFC (R)  Timer current register */
} CORET_Type;

/*@} end of group CSI_SysTick */

/**
  \ingroup  CSI_core_register
  \defgroup CSI_DCC
  \brief    Type definitions for the DCC.
  @{
 */

/**
  \brief  Access to the data structure of DCC.
 */
typedef struct
{
    uint32_t RESERVED0[13U];
    __IOM uint32_t HCR; /*!< Offset: 0x034 (R/W) */
    __IM uint32_t EHSR; /*!< Offset: 0x03C (R/ ) */
    uint32_t RESERVED1[6U];
    union {
        __IM uint32_t DERJW; /*!< Offset: 0x058 (R/ )  Data exchange register CPU read*/
        __OM uint32_t DERJR; /*!< Offset: 0x058 ( /W)  Data exchange register CPU writer*/
    };

} DCC_Type;

#define DCC_HCR_JW_Pos 18U /*!< DCC HCR: jw_int_en Position */
#define DCC_HCR_JW_Msk (1UL << DCC_HCR_JW_Pos) /*!< DCC HCR: jw_int_en Mask */

#define DCC_HCR_JR_Pos 19U /*!< DCC HCR: jr_int_en Position */
#define DCC_HCR_JR_Msk (1UL << DCC_HCR_JR_Pos) /*!< DCC HCR: jr_int_en Mask */

#define DCC_EHSR_JW_Pos 1U /*!< DCC EHSR: jw_vld Position */
#define DCC_EHSR_JW_Msk (1UL << DCC_EHSR_JW_Pos) /*!< DCC EHSR: jw_vld Mask */

#define DCC_EHSR_JR_Pos 2U /*!< DCC EHSR: jr_vld Position */
#define DCC_EHSR_JR_Msk (1UL << DCC_EHSR_JR_Pos) /*!< DCC EHSR: jr_vld Mask */

/*@} end of group CSI_DCC */

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

/* Memory mapping of THEAD CPU */
#define TCIP_BASE   (0xE000E000UL) /*!< Titly Coupled IP Base Address */
#define CORET_BASE  (0xE0004000UL) /*!< CORET Base Address */
#define CLIC_BASE   (0xE0800000UL) /*!< CLIC Base Address */
#define SYSMAP_BASE (0xEFFFF000UL) /*!< SYSMAP Base Address */
#define DCC_BASE    (0xE4010000UL) /*!< DCC Base Address */
#define CACHE_BASE  (TCIP_BASE + 0x1000UL) /*!< CACHE Base Address */

#define CORET  ((CORET_Type *)CORET_BASE) /*!< SysTick configuration struct */
#define CLIC   ((CLIC_Type *)CLIC_BASE) /*!< CLIC configuration struct */
#define DCC    ((DCC_Type *)DCC_BASE) /*!< DCC configuration struct */
#define SYSMAP ((SYSMAP_Type *)SYSMAP_BASE) /*!< SYSMAP configuration struct */
#define CACHE  ((CACHE_Type *)CACHE_BASE) /*!< cache configuration struct */

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
    CLIC->CLICINT[IRQn].IE |= CLIC_INTIE_IE_Msk;
}

/**
  \brief   Disable External Interrupt
  \details Disable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_disable_irq(int32_t IRQn)
{
    CLIC->CLICINT[IRQn].IE &= ~CLIC_INTIE_IE_Msk;
}

/**
  \brief   Enable External Secure Interrupt
  \details Enable a secure device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_enable_sirq(int32_t IRQn)
{
    CLIC->CLICINT[IRQn].IE |= (CLIC_INTIE_IE_Msk | CLIC_INTIE_T_Msk);
}

/**
  \brief   Disable External Secure Interrupt
  \details Disable a secure device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_disable_sirq(int32_t IRQn)
{
    CLIC->CLICINT[IRQn].IE &= ~(CLIC_INTIE_IE_Msk | CLIC_INTIE_T_Msk);
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
    return (uint32_t)(CLIC->CLICINT[IRQn].IE & CLIC_INTIE_IE_Msk);
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
    return (uint32_t)(CLIC->CLICINT[IRQn].IP & CLIC_INTIP_IP_Msk);
}

/**
  \brief   Set Pending Interrupt
  \details Set the pending bit of an external interrupt.
  \param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_set_pending_irq(int32_t IRQn)
{
    CLIC->CLICINT[IRQn].IP |= CLIC_INTIP_IP_Msk;
}

/**
  \brief   Clear Pending Interrupt
  \details Clear the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_clear_pending_irq(int32_t IRQn)
{
    CLIC->CLICINT[IRQn].IP &= ~CLIC_INTIP_IP_Msk;
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
    uint8_t nlbits = (CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;
    CLIC->CLICINT[IRQn].CTL = (CLIC->CLICINT[IRQn].CTL & (~CLIC_INTCFG_PRIO_Msk)) | (priority << (8 - nlbits));
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
    uint8_t nlbits = (CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;
    return CLIC->CLICINT[IRQn].CTL >> (8 - nlbits);
}

/**
  \brief   Set interrupt handler
  \details Set the interrupt handler according to the interrupt num, the handler will be filled in irq vectors.
  \param [in]      IRQn  Interrupt number.
  \param [in]   handler  Interrupt handler.
 */
__STATIC_INLINE void csi_vic_set_vector(int32_t IRQn, uint32_t handler)
{
    if (IRQn >= 0 && IRQn < 1024) {
        uint32_t *vectors = (uint32_t *)__get_MTVT();
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
        uint32_t *vectors = (uint32_t *)__get_MTVT();
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
    if ((CORET->MTIMECMP != 0) && (CORET->MTIMECMP != 0xffffffffffffffff)) {
        CORET->MTIMECMP = CORET->MTIMECMP + ticks;
    } else {
        CORET->MTIMECMP = CORET->MTIME + ticks;
    }

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
    CORET->MTIMECMP = CORET->MTIME + ticks;

    return (0UL);
}

/**
  \brief   get CORE timer reload value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint32_t csi_coret_get_load(void)
{
    return CORET->MTIMECMP & 0xFFFFFFFF;
}

/**
  \brief   get CORE timer reload high value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint32_t csi_coret_get_loadh(void)
{
    return (CORET->MTIMECMP >> 32) & 0xFFFFFFFF;
}

/**
  \brief   get CORE timer counter value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint32_t csi_coret_get_value(void)
{
    return CORET->MTIME & 0xFFFFFFFF;
}

/**
  \brief   get CORE timer counter high value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint32_t csi_coret_get_valueh(void)
{
    return (CORET->MTIME >> 32) & 0xFFFFFFFF;
}

/*@} end of CSI_Core_SysTickFunctions */

/* ##########################   SYSMAP functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_SYSMAPFunctions SYSMAP Functions
  \brief    Functions that manage system map attribute
  @{
 */

/**
  \brief   Get SYSMAPCFGx Register by index
  \details Returns the content of the SYSMAPxCFG Register.
  \param [in]    idx    SYSMAP region index
  \return               SYSMAPxCFG Register value
 */
__STATIC_INLINE uint8_t __get_SYSMAPCFGx(uint32_t idx)
{
    switch (idx) {
        case 0:
            return SYSMAP->SYSMAPCFG0;

        case 1:
            return SYSMAP->SYSMAPCFG1;

        case 2:
            return SYSMAP->SYSMAPCFG2;

        case 3:
            return SYSMAP->SYSMAPCFG3;

        case 4:
            return SYSMAP->SYSMAPCFG4;

        case 5:
            return SYSMAP->SYSMAPCFG5;

        case 6:
            return SYSMAP->SYSMAPCFG6;

        case 7:
            return SYSMAP->SYSMAPCFG7;

        default:
            return 0;
    }
}

/**
  \brief   Set SYSMAPCFGx by index
  \details Writes the given value to the SYSMAPxCFG Register.
  \param [in]    idx      SYSMAPx region index
  \param [in]    sysmapxcfg  SYSMAPxCFG Register value to set
 */
__STATIC_INLINE void __set_SYSMAPCFGx(uint32_t idx, uint32_t sysmapxcfg)
{
    switch (idx) {
        case 0:
            SYSMAP->SYSMAPCFG0 = sysmapxcfg;
            break;

        case 1:
            SYSMAP->SYSMAPCFG1 = sysmapxcfg;
            break;

        case 2:
            SYSMAP->SYSMAPCFG2 = sysmapxcfg;
            break;

        case 3:
            SYSMAP->SYSMAPCFG3 = sysmapxcfg;
            break;

        case 4:
            SYSMAP->SYSMAPCFG4 = sysmapxcfg;
            break;

        case 5:
            SYSMAP->SYSMAPCFG5 = sysmapxcfg;
            break;

        case 6:
            SYSMAP->SYSMAPCFG6 = sysmapxcfg;
            break;

        case 7:
            SYSMAP->SYSMAPCFG7 = sysmapxcfg;
            break;

        default:
            return;
    }
}

/**
  \brief   Get SYSMAPADDRx Register by index
  \details Returns the content of the SYSMAPADDRx Register.
  \param [in]    idx    SYSMAP region index
  \return               SYSMAPADDRx Register value
 */
__STATIC_INLINE uint32_t __get_SYSMAPADDRx(uint32_t idx)
{
    switch (idx) {
        case 0:
            return SYSMAP->SYSMAPADDR0;

        case 1:
            return SYSMAP->SYSMAPADDR1;

        case 2:
            return SYSMAP->SYSMAPADDR2;

        case 3:
            return SYSMAP->SYSMAPADDR3;

        case 4:
            return SYSMAP->SYSMAPADDR4;

        case 5:
            return SYSMAP->SYSMAPADDR5;

        case 6:
            return SYSMAP->SYSMAPADDR6;

        case 7:
            return SYSMAP->SYSMAPADDR7;

        default:
            return 0;
    }
}

/**
  \brief   Set SYSMAPADDRx by index
  \details Writes the given value to the SYSMAPADDRx Register.
  \param [in]    idx      SYSMAP region index
  \param [in]    sysmapaddr  SYSMAPADDRx Register value to set
 */
__STATIC_INLINE void __set_SYSMAPADDRx(uint32_t idx, uint32_t sysmapxaddr)
{
    switch (idx) {
        case 0:
            SYSMAP->SYSMAPADDR0 = sysmapxaddr;
            break;

        case 1:
            SYSMAP->SYSMAPADDR1 = sysmapxaddr;
            break;

        case 2:
            SYSMAP->SYSMAPADDR2 = sysmapxaddr;
            break;

        case 3:
            SYSMAP->SYSMAPADDR3 = sysmapxaddr;
            break;

        case 4:
            SYSMAP->SYSMAPADDR4 = sysmapxaddr;
            break;

        case 5:
            SYSMAP->SYSMAPADDR5 = sysmapxaddr;
            break;

        case 6:
            SYSMAP->SYSMAPADDR6 = sysmapxaddr;
            break;

        case 7:
            SYSMAP->SYSMAPADDR7 = sysmapxaddr;
            break;

        default:
            return;
    }
}

/**
  \brief  configure system map attribute.
  \details
  \param [in]  idx        system map region (0, 1, 2, ..., 7).
  \param [in]  base_addr  base address must be aligned with page size.
  \param [in]  enable     enable or disable memory protected region.
  */
__STATIC_INLINE void csi_sysmap_config_region(uint32_t idx, uint32_t base_addr, uint32_t attr)
{
    uint32_t addr = 0;

    if (idx > 7) {
        return;
    }

    addr = base_addr >> 12;
    attr = attr << 2;

    __set_SYSMAPADDRx(idx, addr);
    __set_SYSMAPCFGx(idx, attr);
}

/*@} end of CSI_Core_SYSMAPFunctions */

/* ##################################### DCC function ########################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_core_DebugFunctions HAD Functions
  \brief    Functions that access the HAD debug interface.
  @{
 */

/**
  \brief   HAD Send Character
  \details Transmits a character via the HAD channel 0, and
           \li Just returns when no debugger is connected that has booked the output.
           \li Is blocking when a debugger is connected, but the previous character sent has not been transmitted.
  \param [in]     ch  Character to transmit.
  \returns            Character to transmit.
 */
__STATIC_INLINE uint32_t csi_had_send_char(uint32_t ch)
{
    DCC->DERJR = (uint8_t)ch;

    return (ch);
}

/**
  \brief   HAD Receive Character
  \details Inputs a character via the external variable \ref HAD_RxBuffer.
  \return             Received character.
  \return         -1  No character pending.
 */
__STATIC_INLINE int32_t csi_had_receive_char(void)
{
    int32_t ch = -1; /* no character available */

    if (_FLD2VAL(DCC_EHSR_JW, DCC->EHSR)) {
        ch = DCC->DERJW;
    }

    return (ch);
}

/**
  \brief   HAD Check Character
  \details Check whether a character is pending for reading in the variable \ref HAD_RxBuffer.
  \return          0  No character available.
  \return          1  Character available.
 */
__STATIC_INLINE int32_t csi_had_check_char(void)
{
    return _FLD2VAL(DCC_EHSR_JW, DCC->EHSR); /* no character available */
}

/*@} end of CSI_core_DebugFunctions */

/* ##########################  sleep and Reset functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_SleepAndResetFunctions Sleep and Reset Functions
  \brief    Functions that configure Sleep and Reset.
  @{
 */

/* MEXSTATUS Register Definitions */
#define MEXSTATUS_RESET_Pos 0U
#define MEXSTATUS_RESET_Msk (0x3UL << MEXSTATUS_RESET_Pos) /*!< MEXSTATUS: RESET Position */
#define MEXSTATUS_SLEEP_Pos 2U
#define MEXSTATUS_SLEEP_Msk (0x3UL << MEXSTATUS_SLEEP_Pos) /*!< MEXSTATUS: RESET Position */
/*@} end of group CSI_MEXSTATUS */

/**
  \brief   CPU System Reset
  \details Triggle CPU System Reset
  */
__STATIC_INLINE void csi_system_reset(void)
{
    uint32_t mexstatus;
    mexstatus = __get_MEXSTATUS();
    mexstatus &= (~(MEXSTATUS_RESET_Msk));
    mexstatus |= (uint32_t)(0x2 << MEXSTATUS_RESET_Pos);
    __set_MEXSTATUS(mexstatus);
}

/**
  \brief   CPU Core Reset
  \details Triggle CPU Core Reset
  */
__STATIC_INLINE void csi_core_reset(void)
{
    uint32_t mexstatus;
    mexstatus = __get_MEXSTATUS();
    mexstatus &= (~(MEXSTATUS_RESET_Msk));
    mexstatus |= (uint32_t)(0x1 << MEXSTATUS_RESET_Pos);
    __set_MEXSTATUS(mexstatus);
}

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
  \brief   D-Cache Invalidate by address
  \details Invalidates D-Cache for the given address
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void csi_dcache_invalid_range(uint32_t *addr, int32_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int32_t op_size = dsize + (uint32_t)addr % 32;
    uint32_t op_addr = (uint32_t)addr;
    int32_t linesize = 32;

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
__STATIC_INLINE void csi_dcache_clean_range(uint32_t *addr, int32_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int32_t op_size = dsize + (uint32_t)addr % 32;
    uint32_t op_addr = (uint32_t)addr & CACHE_INV_ADDR_Msk;
    int32_t linesize = 32;

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
__STATIC_INLINE void csi_dcache_clean_invalid_range(uint32_t *addr, int32_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int32_t op_size = dsize + (uint32_t)addr % 32;
    uint32_t op_addr = (uint32_t)addr;
    int32_t linesize = 32;

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
