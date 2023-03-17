/**
  ******************************************************************************
  * @file    bflb_sf_ctrl.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL628_SF_CTRL_H__
#define __BL628_SF_CTRL_H__

#include "bflb_core.h"

/** @addtogroup  BL628_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SF_CTRL
 *  @{
 */

/** @defgroup  SF_CTRL_Public_Types
 *  @{
 */

#if defined(BL602) || defined(BL702) || defined(BL702L)
#define BFLB_SF_CTRL_BASE      ((uint32_t)0x4000B000)
#elif defined(BL606P) || defined(BL808) || defined(BL616)
#define BFLB_SF_CTRL_BASE      ((uint32_t)0x2000b000)
#elif defined(BL628)
#define BFLB_SF_CTRL_BASE      ((uint32_t)0x20082000)
#endif

#if defined(BL602) || defined(BL702) || defined(BL702L)
#define BFLB_FLASH_XIP_BASE    (0x23000000)
#define BFLB_FLASH_XIP_END     (0x23000000 + 16 * 1024 * 1024)
#elif defined(BL606P) || defined(BL808)
#define BFLB_FLASH_XIP_BASE    (0x58000000)
#define BFLB_FLASH_XIP_END     (0x58000000 + 64 * 1024 * 1024)
#elif defined(BL616)
#define BFLB_FLASH_XIP_BASE    (0xA0000000)
#define BFLB_FLASH_XIP_END     (0xA0000000 + 64 * 1024 * 1024)
#elif defined(BL628)
#define BFLB_FLASH_XIP_BASE    (0x80000000)
#define BFLB_FLASH_XIP_END     (0x80000000 + 64 * 1024 * 1024)
#endif

#if defined(BL628) || defined(BL616) || defined(BL808) || defined(BL606P)
#define BFLB_SF_CTRL_SBUS2_ENABLE
#define BFLB_SF_CTRL_32BITS_ADDR_ENABLE
#define BFLB_SF_CTRL_AES_XTS_ENABLE
#endif
#if defined(BL702) || defined(BL702L)
#define BFLB_SF_CTRL_PSRAM_ENABLE
#endif

/**
 *  @brief Serial flash pad type definition
 */
#define SF_CTRL_PAD1                                    0    /*!< SF Ctrl pad 1 */
#define SF_CTRL_PAD2                                    1    /*!< SF Ctrl pad 2 */
#define SF_CTRL_PAD3                                    2    /*!< SF Ctrl pad 3 */

/**
 *  @brief Serial flash config pin select type definition
 */
#if defined(BL628) || defined(BL616)
#define SF_IO_EMB_SWAP_IO3IO0                           0x0  /*!< SF select embedded flash swap io3 with io0 */
#define SF_IO_EMB_SWAP_IO3IO0_IO2CS                     0x1  /*!< SF select embedded flash swap io3 with io0 and io2 with cs */
#define SF_IO_EMB_SWAP_NONE                             0x2  /*!< SF select embedded flash no swap */
#define SF_IO_EMB_SWAP_IO2CS                            0x3  /*!< SF select embedded flash swap io2 with cs */
#define SF_IO_EXT_SF2_SWAP_IO3IO0                       0x4  /*!< SF select external flash SF2 use gpio4-9 and SF2 swap io3 with io0 */
#define SF_IO_EXT_SF3                                   0x8  /*!< SF select external flash SF3 use gpio10-15 */
#define SF_IO_EMB_SWAP_IO3IO0_AND_SF2_SWAP_IO3IO0       0x14 /*!< SF select embedded flash swap io3 with io0 and SF2 swap io3 with io0*/
#define SF_IO_EMB_SWAP_IO3IO0_IO2CS_AND_SF2_SWAP_IO3IO0 0x15 /*!< SF select embedded flash swap io3 with io0、io2 with cs and SF2 swap io3 with io0 */
#define SF_IO_EMB_SWAP_NONE_AND_SF2_SWAP_IO3IO0         0x16 /*!< SF select embedded flash no swap and SF2 swap io3 with io0 */
#define SF_IO_EMB_SWAP_IO2CS_AND_SF2_SWAP_IO3IO0        0x17 /*!< SF select embedded flash swap io2 with cs, and SF2 swap io3 with io0 */
#define SF_IO_EXT_SF2                                   0x24 /*!< SF select external flash SF2 use gpio4-9 */
#define SF_IO_EMB_SWAP_IO3IO0_AND_SF2                   0x34 /*!< SF select embedded flash swap io3 with io0 and SF2 use gpio4-9 */
#define SF_IO_EMB_SWAP_IO3IO0_IO2CS_AND_SF2             0x35 /*!< SF select embedded flash swap io3 with io0、io2 with cs and SF2 use gpio4-9 */
#define SF_IO_EMB_SWAP_NONE_AND_SF2                     0x36 /*!< SF select embedded flash no swap and SF2 use gpio4-9 */
#define SF_IO_EMB_SWAP_IO2CS_AND_SF2                    0x37 /*!< SF select embedded flash swap io2 with cs and SF2 use gpio4-9 */
#elif defined(BL808) || defined(BL606P)
#define SF_IO_EMB_SWAP_IO0_IO3                          0x0  /*!< SF select embedded flash swap io0 with io3 */
#define SF_IO_EMB_SWAP_DUAL_IO0_IO3                     0x1  /*!< SF select embedded flash swap dual io0 with io3 */
#define SF_IO_EMB_SWAP_NONE                             0x2  /*!< SF select embedded flash no swap */
#define SF_IO_EMB_SWAP_NONE_DUAL_IO0                    0x3  /*!< SF select embedded flash no swap and use dual io0 */
#define SF_IO_EXT_SF2                                   0x4  /*!< SF select external flash SF2 use gpio34-39 */
#define SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2              0x14 /*!< SF select embedded flash swap io0 with io3 and external SF2 use gpio34-39 */
#define SF_IO_EMB_SWAP_DUAL_IO0_IO3_AND_EXT_SF2         0x15 /*!< SF select embedded flash swap dual io0 with io3 and external SF2 use gpio34-39 */
#define SF_IO_EMB_SWAP_NONE_AND_EXT_SF2                 0x16 /*!< SF select embedded flash no swap and external SF2 use gpio34-39 */
#define SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2        0x17 /*!< SF select embedded flash no swap, use dual io0 and external SF2 use gpio34-39 */
#elif defined(BL702L)
#define SF_CTRL_SEL_EXTERNAL_FLASH                      0x0  /*!< SF select sf2, flash use GPIO 23-28, external flash */
#define SF_CTRL_SEL_INTERNAL_FLASH_SWAP_NONE            0x1  /*!< SF select sf1, embedded flash do not swap */
#define SF_CTRL_SEL_INTERNAL_FLASH_SWAP_CSIO2           0x2  /*!< SF select sf1, embedded flash swap cs/io2 */
#define SF_CTRL_SEL_INTERNAL_FLASH_SWAP_IO0IO3          0x3  /*!< SF select sf1, embedded flash swap io0/io3 */
#define SF_CTRL_SEL_INTERNAL_FLASH_SWAP_BOTH            0x4  /*!< SF select sf1, embedded flash swap cs/io2 and io0/io3 */
#define SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_NONE    0x5  /*!< SF select sf1, embedded flash interface reverse and do not swap */
#define SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_CSIO2   0x6  /*!< SF select sf1, embedded flash interface reverse and swap cs/io2 */
#define SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_IO0IO3  0x7  /*!< SF select sf1, embedded flash interface reverse and swap io0/io3 */
#define SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_BOTH    0x8  /*!< SF select sf1, embedded flash interface reverse and swap cs/io2 and io0/io3 */
#elif defined(BL702)
#define SF_CTRL_SEL_SF1                                 0x0  /*!< SF Ctrl select sf1, flash use GPIO 17-22, no psram */
#define SF_CTRL_SEL_SF2                                 0x1  /*!< SF Ctrl select sf2, flash use GPIO 23-28, no psram, embedded flash */
#define SF_CTRL_SEL_SF3                                 0x2  /*!< SF Ctrl select sf3, flash use GPIO 32-37, no psram */
#define SF_CTRL_SEL_DUAL_BANK_SF1_SF2                   0x3  /*!< SF Ctrl select sf1 and sf2, flash use GPIO 17-22, psram use GPIO 23-28 */
#define SF_CTRL_SEL_DUAL_BANK_SF2_SF3                   0x4  /*!< SF Ctrl select sf2 and sf3, flash use GPIO 23-28, psram use GPIO 32-37 */
#define SF_CTRL_SEL_DUAL_BANK_SF3_SF1                   0x5  /*!< SF Ctrl select sf3 and sf1, flash use GPIO 32-37, psram use GPIO 17-22 */
#define SF_CTRL_SEL_DUAL_CS_SF2                         0x6  /*!< SF Ctrl select sf2, flash/psram use GPIO 23-28, psram use GPIO 17 as CS2 */
#define SF_CTRL_SEL_DUAL_CS_SF3                         0x7  /*!< SF Ctrl select sf3, flash/psram use GPIO 32-37, psram use GPIO 23 as CS2 */
#elif defined(BL602)
#define SF_CTRL_EMBEDDED_SEL                            0x0  /*!< Embedded flash select */
#define SF_CTRL_EXTERNAL_17TO22_SEL                     0x1  /*!< External flash select gpio 17-22 */
#define SF_CTRL_EXTERNAL_0TO2_20TO22_SEL                0x2  /*!< External flash select gpio 0-2 and 20-22 */
#endif


/**
 *  @brief Serial flash select bank control type definition
 */
#if defined(BL702) || defined(BL702L)
#define SF_CTRL_SEL_FLASH                               0    /*!< SF Ctrl system bus control flash */
#define SF_CTRL_SEL_PSRAM                               1    /*!< SF Ctrl system bus control psram */
#else
#define SF_CTRL_FLASH_BANK0                             0    /*!< SF Ctrl select flash bank0 */
#define SF_CTRL_FLASH_BANK1                             1    /*!< SF Ctrl select flash bank1 */
#endif

/**
 *  @brief Serial flash controller wrap mode type definition
 */
#define SF_CTRL_WRAP_MODE_0                             0    /*!< Cmds bypass wrap commands to macro, original mode */
#define SF_CTRL_WRAP_MODE_1                             1    /*!< Cmds handle wrap commands, original mode */
#define SF_CTRL_WRAP_MODE_2                             2    /*!< Cmds bypass wrap commands to macro, cmds force wrap16*4 splitted into two wrap8*4 */
#define SF_CTRL_WRAP_MODE_3                             3    /*!< Cmds handle wrap commands, cmds force wrap16*4 splitted into two wrap8*4 */

/**
 *  @brief Serail flash controller wrap mode len type definition
 */
#define SF_CTRL_WRAP_LEN_8                              0    /*!< SF Ctrl wrap length: 8 */
#define SF_CTRL_WRAP_LEN_16                             1    /*!< SF Ctrl wrap length: 16 */
#define SF_CTRL_WRAP_LEN_32                             2    /*!< SF Ctrl wrap length: 32 */
#define SF_CTRL_WRAP_LEN_64                             3    /*!< SF Ctrl wrap length: 64 */
#define SF_CTRL_WRAP_LEN_128                            4    /*!< SF Ctrl wrap length: 128 */
#define SF_CTRL_WRAP_LEN_256                            5    /*!< SF Ctrl wrap length: 256 */
#define SF_CTRL_WRAP_LEN_512                            6    /*!< SF Ctrl wrap length: 512 */
#define SF_CTRL_WRAP_LEN_1024                           7    /*!< SF Ctrl wrap length: 1024 */
#define SF_CTRL_WRAP_LEN_2048                           8    /*!< SF Ctrl wrap length: 2048 */
#define SF_CTRL_WRAP_LEN_4096                           9    /*!< SF Ctrl wrap length: 4096 */

/**
 *  @brief Serail flash controller memory remap type define
 */
#define SF_CTRL_ORIGINAL_MEMORY_MAP                     0    /*!< Remap none, use two addr map when use dual flash */
#define SF_CTRL_REMAP_16MB                              1    /*!< Remap HADDR>16MB region to psram port HADDR[24] -> HADDR[28] */
#define SF_CTRL_REMAP_8MB                               2    /*!< Remap HADDR>8MB region to psram port HADDR[23] -> HADDR[28] */
#define SF_CTRL_REMAP_4MB                               3    /*!< Remap HADDR>4MB region to psram port HADDR[22] -> HADDR[28] */

/**
 *  @brief Serial flash controller select clock type definition
 */
#define SF_CTRL_OWNER_SAHB                              0    /*!< System AHB bus control serial flash controller */
#define SF_CTRL_OWNER_IAHB                              1    /*!< I-Code AHB bus control serial flash controller */

/**
 *  @brief Serial flash controller select clock type definition
 */
#define SF_CTRL_SAHB_CLOCK                              0    /*!< Serial flash controller select default sahb clock */
#define SF_CTRL_FLASH_CLOCK                             1    /*!< Serial flash controller select flash clock */

/**
 *  @brief Read and write type definition
 */
#define SF_CTRL_READ                                    0    /*!< Serail flash read command flag */
#define SF_CTRL_WRITE                                   1    /*!< Serail flash write command flag */

/**
 *  @brief Serail flash interface IO type definition
 */
#define SF_CTRL_NIO_MODE                                0    /*!< Normal IO mode define */
#define SF_CTRL_DO_MODE                                 1    /*!< Dual Output mode define */
#define SF_CTRL_QO_MODE                                 2    /*!< Quad Output mode define */
#define SF_CTRL_DIO_MODE                                3    /*!< Dual IO mode define */
#define SF_CTRL_QIO_MODE                                4    /*!< Quad IO mode define */

/**
 *  @brief Serail flash controller interface mode type definition
 */
#define SF_CTRL_SPI_MODE                                0    /*!< SPI mode define */
#define SF_CTRL_QPI_MODE                                1    /*!< QPI mode define */

/**
 *  @brief Serail flash controller command mode type definition
 */
#define SF_CTRL_CMD_1_LINE                              0    /*!< Command in one line mode */
#define SF_CTRL_CMD_4_LINES                             1   /*!< Command in four lines mode */

/**
 *  @brief Serail flash controller address mode type definition
 */
#define SF_CTRL_ADDR_1_LINE                             0    /*!< Address in one line mode */
#define SF_CTRL_ADDR_2_LINES                            1    /*!< Address in two lines mode */
#define SF_CTRL_ADDR_4_LINES                            2    /*!< Address in four lines mode */

/**
 *  @brief Serail flash controller dummy mode type definition
 */
#define SF_CTRL_DUMMY_1_LINE                            0    /*!< Dummy in one line mode */
#define SF_CTRL_DUMMY_2_LINES                           1    /*!< Dummy in two lines mode */
#define SF_CTRL_DUMMY_4_LINES                           2    /*!< Dummy in four lines mode */

/**
 *  @brief Serail flash controller data mode type definition
 */
#define SF_CTRL_DATA_1_LINE                             0    /*!< Data in one line mode */
#define SF_CTRL_DATA_2_LINES                            1    /*!< Data in two lines mode */
#define SF_CTRL_DATA_4_LINES                            2    /*!< Data in four lines mode */

/**
 *  @brief Serail flash controller AES mode type definition
 */
#define SF_CTRL_AES_CTR_MODE                            0    /*!< Serail flash AES CTR mode */
#define SF_CTRL_AES_XTS_MODE                            1    /*!< Serail flash AES XTS mode */

/**
 *  @brief Serail flash controller AES key len type definition
 */
#define SF_CTRL_AES_128BITS                             0    /*!< Serail flash AES key 128 bits length */
#define SF_CTRL_AES_256BITS                             1    /*!< Serail flash AES key 256 bits length */
#define SF_CTRL_AES_192BITS                             2    /*!< Serail flash AES key 192 bits length */
#define SF_CTRL_AES_128BITS_DOUBLE_KEY                  3    /*!< Serail flash AES key 128 bits length double key */

/**
 *  @brief Serail flash controller configuration structure type definition
 */
struct sf_ctrl_cfg_type {
    uint8_t owner;                       /*!< Sflash interface bus owner */
#ifdef BFLB_SF_CTRL_32BITS_ADDR_ENABLE
    uint8_t en32b_addr;                  /*!< Sflash enable 32-bits address */
#endif
    uint8_t clk_delay;                   /*!< Clock count for read due to pad delay */
    uint8_t clk_invert;                  /*!< Clock invert */
    uint8_t rx_clk_invert;               /*!< RX clock invert */
    uint8_t do_delay;                    /*!< Data out delay */
    uint8_t di_delay;                    /*!< Data in delay */
    uint8_t oe_delay;                    /*!< Output enable delay */
};

#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
/**
 *  @brief SF Ctrl bank2 controller configuration structure type definition
 */
struct sf_ctrl_bank2_cfg {
    uint8_t sbus2_select;                /*!< Select sbus2 as 2nd flash controller */
    uint8_t bank2_rx_clk_invert_src;     /*!< Select bank2 rx clock invert source */
    uint8_t bank2_rx_clk_invert_sel;     /*!< Select inveted bank2 rx clock */
    uint8_t bank2_delay_src;             /*!< Select bank2 read delay source */
    uint8_t bank2_clk_delay;             /*!< Bank2 read delay cycle = n + 1 */
    uint8_t do_delay;                    /*!< Data out delay */
    uint8_t di_delay;                    /*!< Data in delay */
    uint8_t oe_delay;                    /*!< Output enable delay */
    uint8_t remap;                       /*!< Select dual flash memory remap set */
    uint8_t remap_lock;                  /*!< Select memory remap lock */
};
#endif

#ifdef BFLB_SF_CTRL_PSRAM_ENABLE
/**
 *  @brief SF Ctrl psram controller configuration structure type definition
 */
struct sf_ctrl_psram_cfg {
    uint8_t owner;                   /*!< Psram interface bus owner */
    uint8_t pad_sel;                 /*!< SF Ctrl pad select */
    uint8_t bank_sel;                /*!< SF Ctrl bank select */
    uint8_t psram_rx_clk_invert_src; /*!< Select psram rx clock invert source */
    uint8_t psram_rx_clk_invert_sel; /*!< Select inveted psram rx clock */
    uint8_t psram_delay_src;         /*!< Select psram read delay source */
    uint8_t psram_clk_delay;         /*!< Psram read delay cycle = n + 1 */
} ;
#endif

/**
 *  @brief SF Ctrl cmds configuration structure type definition
 */
struct sf_ctrl_cmds_cfg {
    uint8_t ack_latency;                 /*!< SF Ctrl ack latency cycles */
    uint8_t cmds_core_en;                /*!< SF Ctrl cmds core enable */
#if defined(BL702)
    uint8_t burst_toggle_en;             /*!< SF Ctrl burst toggle mode enable */
#endif
    uint8_t cmds_en;                     /*!< SF Ctrl cmds enable */
    uint8_t cmds_wrap_mode;              /*!< SF Ctrl cmds wrap mode */
    uint8_t cmds_wrap_len;               /*!< SF Ctrl cmds wrap length */
};

/**
 *  @brief Serail flash command configuration structure type definition
 */
struct sf_ctrl_cmd_cfg_type {
    uint8_t rw_flag;                     /*!< Read write flag */
    uint8_t cmd_mode;                    /*!< Command mode */
    uint8_t addr_mode;                   /*!< Address mode */
    uint8_t addr_size;                   /*!< Address size */
    uint8_t dummy_clks;                  /*!< Dummy clocks */
    uint8_t dummy_mode;                  /*!< Dummy mode */
    uint8_t data_mode;                   /*!< Data mode */
    uint8_t rsv[1];                      /*!< Reserved */
    uint32_t nb_data;                    /*!< Transfer number of bytes */
    uint32_t cmd_buf[2];                 /*!< Command buffer */
};

/*@} end of group SF_CTRL_Public_Types */

/** @defgroup  SF_CTRL_Public_Macros
 *  @{
 */
#if defined(BL602) || defined(BL702) || defined(BL702L)
#define SF_CTRL_BUSY_STATE_TIMEOUT  (5 * 160 * 1000)
#else
#define SF_CTRL_BUSY_STATE_TIMEOUT  (5 * 320 * 1000)
#endif
#define SF_CTRL_NO_ADDRESS          0xFFFFFFFF
#define NOR_FLASH_CTRL_BUF_SIZE     256
#define NAND_FLASH_CTRL_BUF_SIZE    512

#if defined(BL628) || defined(BL616)
#define IS_SF_CTRL_PIN_SELECT(type) (((type) == SF_IO_EMB_SWAP_IO3IO0) ||                           \
                                     ((type) == SF_IO_EMB_SWAP_IO3IO0_IO2CS) ||                     \
                                     ((type) == SF_IO_EMB_SWAP_NONE) ||                             \
                                     ((type) == SF_IO_EMB_SWAP_IO2CS) ||                            \
                                     ((type) == SF_IO_EXT_SF2_SWAP_IO3IO0) ||                       \
                                     ((type) == SF_IO_EXT_SF3) ||                                   \
                                     ((type) == SF_IO_EMB_SWAP_IO3IO0_AND_SF2_SWAP_IO3IO0) ||       \
                                     ((type) == SF_IO_EMB_SWAP_IO3IO0_IO2CS_AND_SF2_SWAP_IO3IO0) || \
                                     ((type) == SF_IO_EMB_SWAP_NONE_AND_SF2_SWAP_IO3IO0) ||         \
                                     ((type) == SF_IO_EMB_SWAP_IO2CS_AND_SF2_SWAP_IO3IO0) ||        \
                                     ((type) == SF_IO_EXT_SF2) ||                                   \
                                     ((type) == SF_IO_EMB_SWAP_IO3IO0_AND_SF2) ||                   \
                                     ((type) == SF_IO_EMB_SWAP_IO3IO0_IO2CS_AND_SF2) ||             \
                                     ((type) == SF_IO_EMB_SWAP_NONE_AND_SF2) ||                     \
                                     ((type) == SF_IO_EMB_SWAP_IO2CS_AND_SF2))
#elif defined(BL808) || defined(BL606P)
#define IS_SF_CTRL_PIN_SELECT(type) (((type) == SF_IO_EMB_SWAP_IO0_IO3) ||                  \
                                     ((type) == SF_IO_EMB_SWAP_DUAL_IO0_IO3) ||             \
                                     ((type) == SF_IO_EMB_SWAP_NONE) ||                     \
                                     ((type) == SF_IO_EMB_SWAP_NONE_DUAL_IO0) ||            \
                                     ((type) == SF_IO_EXT_SF2) ||                           \
                                     ((type) == SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2) ||      \
                                     ((type) == SF_IO_EMB_SWAP_DUAL_IO0_IO3_AND_EXT_SF2) || \
                                     ((type) == SF_IO_EMB_SWAP_NONE_AND_EXT_SF2) ||         \
                                     ((type) == SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2))
#elif defined(BL702L)
#define IS_SF_CTRL_PIN_SELECT(type) (((type) == SF_CTRL_SEL_EXTERNAL_FLASH) ||                     \
                                     ((type) == SF_CTRL_SEL_INTERNAL_FLASH_SWAP_NONE) ||           \
                                     ((type) == SF_CTRL_SEL_INTERNAL_FLASH_SWAP_CSIO2) ||          \
                                     ((type) == SF_CTRL_SEL_INTERNAL_FLASH_SWAP_IO0IO3) ||         \
                                     ((type) == SF_CTRL_SEL_INTERNAL_FLASH_SWAP_BOTH) ||           \
                                     ((type) == SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_NONE) ||   \
                                     ((type) == SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_CSIO2) ||  \
                                     ((type) == SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_IO0IO3) || \
                                     ((type) == SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_BOTH))
#elif defined(BL702)
#define IS_SF_CTRL_PIN_SELECT(type) (((type) == SF_CTRL_SEL_SF1) ||               \
                                     ((type) == SF_CTRL_SEL_SF2) ||               \
                                     ((type) == SF_CTRL_SEL_SF3) ||               \
                                     ((type) == SF_CTRL_SEL_DUAL_BANK_SF1_SF2) || \
                                     ((type) == SF_CTRL_SEL_DUAL_BANK_SF2_SF3) || \
                                     ((type) == SF_CTRL_SEL_DUAL_BANK_SF3_SF1) || \
                                     ((type) == SF_CTRL_SEL_DUAL_CS_SF2) ||       \
                                     ((type) == SF_CTRL_SEL_DUAL_CS_SF3))
#elif defined(BL602)
#define IS_SF_CTRL_PIN_SELECT(type) (((type) == SF_CTRL_EMBEDDED_SEL) ||         \
                                     ((type) == SF_CTRL_EXTERNAL_17TO22_SEL) ||  \
                                     ((type) == SF_CTRL_EXTERNAL_0TO2_20TO22_SEL))
#endif

/*@} end of group SF_CTRL_Public_Macros */

/** @defgroup  SF_CTRL_Public_Functions
 *  @{
 */
void bflb_sf_ctrl_enable(const struct sf_ctrl_cfg_type *cfg);
void bflb_sf_ctrl_set_io_delay(uint8_t pad, uint8_t dodelay, uint8_t didelay, uint8_t oedelay);
#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
void bflb_sf_ctrl_bank2_enable(const struct sf_ctrl_bank2_cfg *bank2cfg);
void bflb_sf_ctrl_sbus2_hold_sram(void);
void bflb_sf_ctrl_sbus2_release_sram(void);
uint8_t sf_ctrl_is_sbus2_enable(void);
void bflb_sf_ctrl_sbus2_replace(uint8_t pad);
void bflb_sf_ctrl_sbus2_revoke_replace(void);
void bflb_sf_ctrl_sbus2_set_delay(uint8_t clk_delay, uint8_t rx_clk_invert);
void bflb_sf_ctrl_remap_set(uint8_t remap, uint8_t lock);
#endif
#ifdef BFLB_SF_CTRL_32BITS_ADDR_ENABLE
void bflb_sf_ctrl_32bits_addr_en(uint8_t en_32bit_saddr);
#endif
#ifdef BFLB_SF_CTRL_PSRAM_ENABLE
void bflb_sf_ctrl_psram_init(struct sf_ctrl_psram_cfg *psram_cfg);
#endif
uint8_t bflb_sf_ctrl_get_clock_delay(void);
void bflb_sf_ctrl_set_clock_delay(uint8_t delay);
uint8_t bflb_sf_ctrl_get_wrap_queue_value(void);
void bflb_sf_ctrl_cmds_set(struct sf_ctrl_cmds_cfg *cmds_cfg, uint8_t sel);
#if defined(BL702L)
void bflb_sf_ctrl_burst_toggle_set(uint8_t burst_toggle_en, uint8_t mode);
#endif
void bflb_sf_ctrl_select_pad(uint8_t sel);
void bflb_sf_ctrl_sbus_select_bank(uint8_t bank);
void bflb_sf_ctrl_set_owner(uint8_t owner);
void bflb_sf_ctrl_disable(void);
void bflb_sf_ctrl_aes_enable_be(void);
void bflb_sf_ctrl_aes_enable_le(void);
void bflb_sf_ctrl_aes_set_region(uint8_t region, uint8_t enable, uint8_t hwkey,
                                 uint32_t start_addr, uint32_t end_addr, uint8_t locked);
void bflb_sf_ctrl_aes_set_key(uint8_t region, uint8_t *key, uint8_t key_type);
void bflb_sf_ctrl_aes_set_key_be(uint8_t region, uint8_t *key, uint8_t key_type);
void bflb_sf_ctrl_aes_set_iv(uint8_t region, uint8_t *iv, uint32_t addr_offset);
void bflb_sf_ctrl_aes_set_iv_be(uint8_t region, uint8_t *iv, uint32_t addr_offset);
#ifdef BFLB_SF_CTRL_AES_XTS_ENABLE
void bflb_sf_ctrl_aes_xts_set_key(uint8_t region, uint8_t *key, uint8_t key_type);
void bflb_sf_ctrl_aes_xts_set_key_be(uint8_t region, uint8_t *key, uint8_t key_type);
void bflb_sf_ctrl_aes_xts_set_iv(uint8_t region, uint8_t *iv, uint32_t addr_offset);
void bflb_sf_ctrl_aes_xts_set_iv_be(uint8_t region, uint8_t *iv, uint32_t addr_offset);
#endif
void bflb_sf_ctrl_aes_set_mode(uint8_t mode);
void bflb_sf_ctrl_aes_enable(void);
void bflb_sf_ctrl_aes_disable(void);
uint8_t bflb_sf_ctrl_is_aes_enable(void);
void bflb_sf_ctrl_set_flash_image_offset(uint32_t addr_offset, uint8_t group, uint8_t bank);
uint32_t bflb_sf_ctrl_get_flash_image_offset(uint8_t group, uint8_t bank);
void bflb_sf_ctrl_lock_flash_image_offset(uint8_t lock);
void bflb_sf_ctrl_select_clock(uint8_t sahb_sram_sel);
void bflb_sf_ctrl_sendcmd(struct sf_ctrl_cmd_cfg_type *cfg);
void bflb_sf_ctrl_disable_wrap_access(uint8_t disable);
void bflb_sf_ctrl_xip_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid);
#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
void bflb_sf_ctrl_xip2_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid);
#endif
#ifdef BFLB_SF_CTRL_PSRAM_ENABLE
void bflb_sf_ctrl_psram_write_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid);
void bflb_sf_ctrl_psram_read_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid);
#endif
uint8_t bflb_sf_ctrl_get_busy_state(void);
#ifndef BFLB_USE_HAL_DRIVER
void bflb_sf_ctrl_irqhandler(void);
#endif

/*@} end of group SF_CTRL_Public_Functions */

/*@} end of group SF_CTRL */

/*@} end of group BL628_Peripheral_Driver */

#endif /* __BL628_SF_CTRL_H__ */
