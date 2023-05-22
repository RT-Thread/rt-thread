#ifndef __BL602_COMMON_H__
#define __BL602_COMMON_H__

#include "bl602.h"
#include "bflb_core.h"

/**
 * @brief Memory access macro
 */
#define BL_RD_WORD(addr)       (*((volatile uint32_t *)(uintptr_t)(addr)))
#define BL_WR_WORD(addr, val)  ((*(volatile uint32_t *)(uintptr_t)(addr)) = (val))
#define BL_RD_SHORT(addr)      (*((volatile uint16_t *)(uintptr_t)(addr)))
#define BL_WR_SHORT(addr, val) ((*(volatile uint16_t *)(uintptr_t)(addr)) = (val))
#define BL_RD_BYTE(addr)       (*((volatile uint8_t *)(uintptr_t)(addr)))
#define BL_WR_BYTE(addr, val)  ((*(volatile uint8_t *)(uintptr_t)(addr)) = (val))
#define BL_RDWD_FRM_BYTEP(p)   ((p[3] << 24) | (p[2] << 16) | (p[1] << 8) | (p[0]))

#define BL_WRWD_TO_BYTEP(p, val)   \
    {                              \
        p[0] = val & 0xff;         \
        p[1] = (val >> 8) & 0xff;  \
        p[2] = (val >> 16) & 0xff; \
        p[3] = (val >> 24) & 0xff; \
    }
/**
 * @brief Register access macro
 */
#define BL_RD_REG16(addr, regname)                BL_RD_SHORT(addr + regname##_OFFSET)
#define BL_WR_REG16(addr, regname, val)           BL_WR_SHORT(addr + regname##_OFFSET, val)
#define BL_RD_REG(addr, regname)                  BL_RD_WORD(addr + regname##_OFFSET)
#define BL_WR_REG(addr, regname, val)             BL_WR_WORD(addr + regname##_OFFSET, val)
#define BL_SET_REG_BIT(val, bitname)              ((val) | (1U << bitname##_POS))
#define BL_CLR_REG_BIT(val, bitname)              ((val)&bitname##_UMSK)
#define BL_GET_REG_BITS_VAL(val, bitname)         (((val)&bitname##_MSK) >> bitname##_POS)
#define BL_SET_REG_BITS_VAL(val, bitname, bitval) (((val)&bitname##_UMSK) | ((uint32_t)(bitval) << bitname##_POS))
#define BL_IS_REG_BIT_SET(val, bitname)           (((val) & (1U << (bitname##_POS))) != 0)
#define BL_DRV_DUMMY           \
    {                          \
        __ASM volatile("nop"); \
        __ASM volatile("nop"); \
        __ASM volatile("nop"); \
        __ASM volatile("nop"); \
    }

/** @defgroup  COMMON_Public_Types
 *  @{
 */
#ifdef BIT
#undef BIT
#define BIT(n) (1UL << (n))
#else
#define BIT(n) (1UL << (n))
#endif

/**
 * @brief Null Type definition
 */
#ifndef NULL
#define NULL 0
#endif

/**
 * @brief Error type definition
 */
typedef enum {
    SUCCESS = 0,
    ERROR = 1,
    TIMEOUT = 2,
    INVALID = 3, /* invalid arguments */
    NORESC = 4   /* no resource or resource temperary unavailable */
} BL_Err_Type;

/**
 * @brief Functional type definition
 */
typedef enum {
    DISABLE = 0,
    ENABLE = 1,
} BL_Fun_Type;

/**
 * @brief Status type definition
 */
typedef enum {
    RESET = 0,
    SET = 1,
} BL_Sts_Type;

/**
 * @brief Mask type definition
 */
typedef enum {
    UNMASK = 0,
    MASK = 1
} BL_Mask_Type;

/**
 * @brief Logical status Type definition
 */
typedef enum {
    LOGIC_LO = 0,
    LOGIC_HI = !LOGIC_LO
} LogicalStatus;

/**
 * @brief Active status Type definition
 */
typedef enum {
    DEACTIVE = 0,
    ACTIVE = !DEACTIVE
} ActiveStatus;

/**
 *  @brief Interrupt callback function type
 */
typedef void(intCallback_Type)(void);
typedef void (*pFunc)(void);

#ifdef DEBUG
void check_failed(uint8_t *file, uint32_t line);
#define CHECK_PARAM(expr) ((expr) ? (void)0 : check_failed((uint8_t *)__FILE__, __LINE__))
#else
#define CHECK_PARAM(expr) ((void)0)
#endif /* DEBUG */

#ifndef __NOP
#define __NOP() __ASM volatile("nop") /* This implementation generates debug information */
#endif
#ifndef __WFI
#define __WFI() __ASM volatile("wfi") /* This implementation generates debug information */
#endif
#ifndef __WFE
#define __WFE() __ASM volatile("wfe") /* This implementation generates debug information */
#endif
#ifndef __SEV
#define __SEV() __ASM volatile("sev") /* This implementation generates debug information */
#endif
#ifndef __set_MSP
#define __set_MSP(msp) __ASM volatile("add sp, x0, %0" ::"r"(msp))
#endif

__attribute__((always_inline)) __STATIC_INLINE uint32_t __REV(uint32_t value)
{
    //return __builtin_bswap32(value);
    uint32_t res = 0;

    res = (value << 24) | (value >> 24);
    res &= 0xFF0000FF; /* only for sure */
    res |= ((value >> 8) & 0x0000FF00) | ((value << 8) & 0x00FF0000);

    return res;
}

__attribute__((always_inline)) __STATIC_INLINE uint32_t __REV16(uint32_t value)
{
    return __builtin_bswap16(value);
}

/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by setting the IE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __enable_irq(void)
{
    __ASM volatile("csrs mstatus, 8");
}

/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by clearing the IE-bit in the PSR.
  Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __disable_irq(void)
{
    __ASM volatile("csrc mstatus, 8");
}

/** @defgroup  COMMON_Public_Constants
 *  @{
 */

/** @defgroup DRIVER_INT_PERIPH
 *  @{
 */
#define IS_INT_PERIPH(INT_PERIPH) ((INT_PERIPH) < IRQn_LAST)

/*@} end of group DRIVER_INT_PERIPH */

/** @defgroup DRIVER_INT_MASK
 *  @{
 */
#define IS_BL_MASK_TYPE(type) (((type) == MASK) || ((type) == UNMASK))

/*@} end of group COMMON_Public_Constants */

/*@} end of group DRIVER_Public_Macro */
#define BL602_MemCpy      arch_memcpy
#define BL602_MemSet      arch_memset
#define BL602_MemCmp      arch_memcmp
#define BL602_MemCpy4     arch_memcpy4
#define BL602_MemCpy_Fast arch_memcpy_fast
#define BL602_MemSet4     arch_memset4

#define BL602_Delay_US arch_delay_us
#define BL602_Delay_MS arch_delay_ms

#define BFLB_Soft_CRC32 bflb_soft_crc32
#define CPU_Interrupt_Enable(irq)
#define CPU_Interrupt_Disable(irq)
#define Interrupt_Handler_Register(irq, callback)

void BL602_Delay_US(uint32_t cnt);
void BL602_Delay_MS(uint32_t cnt);
#endif
