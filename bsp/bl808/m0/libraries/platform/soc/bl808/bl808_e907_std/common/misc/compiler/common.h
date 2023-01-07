#ifndef __COMMON_H
#define __COMMON_H

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

/* Std driver attribute macro*/
#ifndef BFLB_USE_CUSTOM_LD_SECTIONS
//#define ATTR_UNI_SYMBOL
#define ATTR_STRINGIFY(x)          #x
#define ATTR_TOSTRING(x)           ATTR_STRINGIFY(x)
#define ATTR_UNI_SYMBOL            __FILE__ ATTR_TOSTRING(__LINE__)
#define ATTR_CLOCK_SECTION         __attribute__((section(".sclock_rlt_code." ATTR_UNI_SYMBOL)))
#define ATTR_CLOCK_CONST_SECTION   __attribute__((section(".sclock_rlt_const." ATTR_UNI_SYMBOL)))
#define ATTR_TCM_SECTION           __attribute__((section(".tcm_code." ATTR_UNI_SYMBOL)))
#define ATTR_TCM_CONST_SECTION     __attribute__((section(".tcm_const." ATTR_UNI_SYMBOL)))
#define ATTR_DTCM_SECTION          __attribute__((section(".tcm_data")))
#define ATTR_HSRAM_SECTION         __attribute__((section(".hsram_code")))
#define ATTR_DMA_RAM_SECTION       __attribute__((section(".system_ram")))
#define ATTR_HBN_RAM_SECTION       __attribute__((section(".hbn_ram_code")))
#define ATTR_HBN_RAM_CONST_SECTION __attribute__((section(".hbn_ram_data")))
#define ATTR_EALIGN(x)             __attribute__((aligned(x)))
#define ATTR_FALLTHROUGH()         __attribute__((fallthrough))
#define ATTR_USED                  __attribute__((__used__))
#else
#include "bl_ld_sections.h"
#endif /* BFLB_USE_CUSTOM_LD_SECTIONS */
#endif
