#ifndef __BL702_MEMORYMAP_H
#define __BL702_MEMORYMAP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define BL602_FLASH_XIP_BASE        0x23000000
#define BL602_FLASH_XIP_END         (0x23000000 + 16 * 1024 * 1024)
#define BL602_FLASH_XIP_REMAP0_BASE 0x33000000
#define BL602_FLASH_XIP_REMAP0_END  (0x33000000 + 16 * 1024 * 1024)
#define BL602_FLASH_XIP_REMAP1_BASE 0x43000000
#define BL602_FLASH_XIP_REMAP1_END  (0x43000000 + 16 * 1024 * 1024)
#define BL602_FLASH_XIP_REMAP2_BASE 0x53000000
#define BL602_FLASH_XIP_REMAP2_END  (0x53000000 + 16 * 1024 * 1024)

#define BL602_WRAM_BASE        0x42020000
#define BL602_WRAM_END         (0x42020000 + 176 * 1024)
#define BL602_WRAM_REMAP0_BASE 0x22020000
#define BL602_WRAM_REMAP0_END  (0x22020000 + 176 * 1024)
#define BL602_WRAM_REMAP1_BASE 0x32020000
#define BL602_WRAM_REMAP1_END  (0x32020000 + 176 * 1024)
#define BL602_WRAM_REMAP2_BASE 0x52020000
#define BL602_WRAM_REMAP2_END  (0x52020000 + 176 * 1024)

#define BL602_TCM_BASE        0x22008000
#define BL602_TCM_END         (0x22008000 + (96 + 176) * 1024)
#define BL602_TCM_REMAP0_BASE 0x32008000
#define BL602_TCM_REMAP0_END  (0x32008000 + (96 + 176) * 1024)
#define BL602_TCM_REMAP1_BASE 0x42008000
#define BL602_TCM_REMAP1_END  (0x42008000 + (96 + 176) * 1024)
#define BL602_TCM_REMAP2_BASE 0x52008000
#define BL602_TCM_REMAP2_END  (0x52008000 + (96 + 176) * 1024)
/*@} end of group Memory_Map_Section */

/* BL602 peripherals base address */
#define GLB_BASE         ((uint32_t)0x40000000)
#define RF_BASE          ((uint32_t)0x40001000)
#define GPIP_BASE        ((uint32_t)0x40002000) /*!< AUX module base address */
#define SEC_DBG_BASE     ((uint32_t)0x40003000) /*!< Security Debug module base address */
#define SEC_ENG_BASE     ((uint32_t)0x40004000) /*!< Security Engine module base address */
#define TZC_SEC_BASE     ((uint32_t)0x40005000) /*!< Trustzone control security base address */
#define TZC_NSEC_BASE    ((uint32_t)0x40006000) /*!< Trustzone control none-security base address */
#define EF_DATA_BASE     ((uint32_t)0x40007000)
#define EF_CTRL_BASE     ((uint32_t)0x40007000)
#define CCI_BASE         ((uint32_t)0x40008000)
#define L1C_BASE         ((uint32_t)0x40009000) /*!< L1 cache config base address */
#define UART0_BASE       ((uint32_t)0x4000A000)
#define UART1_BASE       ((uint32_t)0x4000A100)
#define SPI_BASE         ((uint32_t)0x4000A200)
#define I2C_BASE         ((uint32_t)0x4000A300)
#define PWM_BASE         ((uint32_t)0x4000A400)
#define TIMER_BASE       ((uint32_t)0x4000A500)
#define IR_BASE          ((uint32_t)0x4000A600)
#define SF_CTRL_BASE     ((uint32_t)0x4000B000)
#define SF_CTRL_BUF_BASE ((uint32_t)0x4000B700)
#define DMA_BASE         ((uint32_t)0x4000C000)
#define SDU_BASE         ((uint32_t)0x4000D000)
#define PDS_BASE         ((uint32_t)0x4000E000) /*!< Power down sleep module base address */
#define HBN_BASE         ((uint32_t)0x4000F000) /*!< Hibernate module base address */
#define AON_BASE         ((uint32_t)0x4000F000) /*!< Always on module base address */
#define HBN_RAM_BASE     ((uint32_t)0x40010000)

#endif