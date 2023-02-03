/**
  ******************************************************************************
  * @file    bl808_sf_ctrl.h
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
#ifndef __BL808_SF_CTRL_H__
#define __BL808_SF_CTRL_H__

#include "sf_ctrl_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SF_CTRL
 *  @{
 */

/** @defgroup  SF_CTRL_Public_Types
 *  @{
 */

/**
 *  @brief Serial flash pad type definition
 */
typedef enum {
    SF_CTRL_PAD1, /*!< SF Ctrl pad 1 */
    SF_CTRL_PAD2, /*!< SF Ctrl pad 2 */
    SF_CTRL_PAD3, /*!< SF Ctrl pad 3 */
} SF_Ctrl_Pad_Type;

/**
 *  @brief Serial flash config pin select type definition
 */
typedef enum {
    SF_IO_EMB_SWAP_IO0_IO3 = 0x0,                    /*!< SF select embedded flash swap io0 with io3 */
    SF_IO_EMB_SWAP_DUAL_IO0_IO3 = 0x1,               /*!< SF select embedded flash swap dual io0 with io3 */
    SF_IO_EMB_SWAP_NONE = 0x2,                       /*!< SF select embedded flash no swap */
    SF_IO_EMB_SWAP_NONE_DUAL_IO0 = 0x3,              /*!< SF select embedded flash no swap and use dual io0 */
    SF_IO_EXT_SF2 = 0x4,                             /*!< SF select external flash SF2 use gpio34-39 */
    SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2 = 0x14,       /*!< SF select embedded flash swap io0 with io3 and external SF2 use gpio34-39 */
    SF_IO_EMB_SWAP_DUAL_IO0_IO3_AND_EXT_SF2 = 0x15,  /*!< SF select embedded flash swap dual io0 with io3 and external SF2 use gpio34-39 */
    SF_IO_EMB_SWAP_NONE_AND_EXT_SF2 = 0x16,          /*!< SF select embedded flash no swap and external SF2 use gpio34-39 */
    SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2 = 0x17, /*!< SF select embedded flash no swap, use dual io0 and external SF2 use gpio34-39 */
} SF_Ctrl_Pin_Select;

/**
 *  @brief Serial flash select bank control type definition
 */
typedef enum {
    SF_CTRL_FLASH_BANK0, /*!< SF Ctrl select flash bank0 */
    SF_CTRL_FLASH_BANK1, /*!< SF Ctrl select flash bank1 */
} SF_Ctrl_Bank_Select;

/**
 *  @brief Serial flash controller wrap mode type definition
 */
typedef enum {
    SF_CTRL_WRAP_MODE_0, /*!< Cmds bypass wrap commands to macro, original mode */
    SF_CTRL_WRAP_MODE_1, /*!< Cmds handle wrap commands, original mode */
    SF_CTRL_WRAP_MODE_2, /*!< Cmds bypass wrap commands to macro, cmds force wrap16*4 splitted into two wrap8*4 */
    SF_CTRL_WRAP_MODE_3, /*!< Cmds handle wrap commands, cmds force wrap16*4 splitted into two wrap8*4 */
} SF_Ctrl_Wrap_Mode;

/**
 *  @brief Serail flash controller wrap mode len type definition
 */
typedef enum {
    SF_CTRL_WRAP_LEN_8,    /*!< SF Ctrl wrap length: 8 */
    SF_CTRL_WRAP_LEN_16,   /*!< SF Ctrl wrap length: 16 */
    SF_CTRL_WRAP_LEN_32,   /*!< SF Ctrl wrap length: 32 */
    SF_CTRL_WRAP_LEN_64,   /*!< SF Ctrl wrap length: 64 */
    SF_CTRL_WRAP_LEN_128,  /*!< SF Ctrl wrap length: 128 */
    SF_CTRL_WRAP_LEN_256,  /*!< SF Ctrl wrap length: 256 */
    SF_CTRL_WRAP_LEN_512,  /*!< SF Ctrl wrap length: 512 */
    SF_CTRL_WRAP_LEN_1024, /*!< SF Ctrl wrap length: 1024 */
    SF_CTRL_WRAP_LEN_2048, /*!< SF Ctrl wrap length: 2048 */
    SF_CTRL_WRAP_LEN_4096, /*!< SF Ctrl wrap length: 4096 */
} SF_Ctrl_Wrap_Len_Type;

/**
 *  @brief Serail flash controller memory remap type define
 */
typedef enum {
    SF_CTRL_ORIGINAL_MEMORY_MAP, /*!< Remap none, use two addr map when use dual flash */
    SF_CTRL_REMAP_16MB,          /*!< Remap HADDR>16MB region to psram port HADDR[24] -> HADDR[28] */
    SF_CTRL_REMAP_8MB,           /*!< Remap HADDR>8MB region to psram port HADDR[23] -> HADDR[28] */
    SF_CTRL_REMAP_4MB,           /*!< Remap HADDR>4MB region to psram port HADDR[22] -> HADDR[28] */
} SF_Ctrl_Remap_Type;

/**
 *  @brief Serial flash controller owner type definition
 */
typedef enum {
    SF_CTRL_OWNER_SAHB, /*!< System AHB bus control serial flash controller */
    SF_CTRL_OWNER_IAHB, /*!< I-Code AHB bus control serial flash controller */
} SF_Ctrl_Owner_Type;

/**
 *  @brief Read and write type definition
 */
typedef enum {
    SF_CTRL_READ,  /*!< Serail flash read command flag */
    SF_CTRL_WRITE, /*!< Serail flash write command flag */
} SF_Ctrl_RW_Type;

/**
 *  @brief Serail flash interface IO type definition
 */
typedef enum {
    SF_CTRL_NIO_MODE, /*!< Normal IO mode define */
    SF_CTRL_DO_MODE,  /*!< Dual Output mode define */
    SF_CTRL_QO_MODE,  /*!< Quad Output mode define */
    SF_CTRL_DIO_MODE, /*!< Dual IO mode define */
    SF_CTRL_QIO_MODE, /*!< Quad IO mode define */
} SF_Ctrl_IO_Type;

/**
 *  @brief Serail flash controller interface mode type definition
 */
typedef enum {
    SF_CTRL_SPI_MODE, /*!< SPI mode define */
    SF_CTRL_QPI_MODE, /*!< QPI mode define */
} SF_Ctrl_Mode_Type;

/**
 *  @brief Serail flash controller command mode type definition
 */
typedef enum {
    SF_CTRL_CMD_1_LINE,  /*!< Command in one line mode */
    SF_CTRL_CMD_4_LINES, /*!< Command in four lines mode */
} SF_Ctrl_Cmd_Mode_Type;

/**
 *  @brief Serail flash controller address mode type definition
 */
typedef enum {
    SF_CTRL_ADDR_1_LINE,  /*!< Address in one line mode */
    SF_CTRL_ADDR_2_LINES, /*!< Address in two lines mode */
    SF_CTRL_ADDR_4_LINES, /*!< Address in four lines mode */
} SF_Ctrl_Addr_Mode_Type;

/**
 *  @brief Serail flash controller dummy mode type definition
 */
typedef enum {
    SF_CTRL_DUMMY_1_LINE,  /*!< Dummy in one line mode */
    SF_CTRL_DUMMY_2_LINES, /*!< Dummy in two lines mode */
    SF_CTRL_DUMMY_4_LINES, /*!< Dummy in four lines mode */
} SF_Ctrl_Dmy_Mode_Type;

/**
 *  @brief Serail flash controller data mode type definition
 */
typedef enum {
    SF_CTRL_DATA_1_LINE,  /*!< Data in one line mode */
    SF_CTRL_DATA_2_LINES, /*!< Data in two lines mode */
    SF_CTRL_DATA_4_LINES, /*!< Data in four lines mode */
} SF_Ctrl_Data_Mode_Type;

/**
 *  @brief Serail flash controller AES mode type definition
 */
typedef enum {
    SF_CTRL_AES_CTR_MODE, /*!< Serail flash AES CTR mode */
    SF_CTRL_AES_XTS_MODE, /*!< Serail flash AES XTS mode */
} SF_Ctrl_AES_Mode_Type;

/**
 *  @brief Serail flash controller AES key len type definition
 */
typedef enum {
    SF_CTRL_AES_128BITS,            /*!< Serail flash AES key 128 bits length */
    SF_CTRL_AES_256BITS,            /*!< Serail flash AES key 256 bits length */
    SF_CTRL_AES_192BITS,            /*!< Serail flash AES key 192 bits length */
    SF_CTRL_AES_128BITS_DOUBLE_KEY, /*!< Serail flash AES key 128 bits length double key */
} SF_Ctrl_AES_Key_Type;

/**
 *  @brief Serail flash controller configuration structure type definition
 */
typedef struct
{
    SF_Ctrl_Owner_Type owner; /*!< Sflash interface bus owner */
    BL_Fun_Type en32bAddr;    /*!< Sflash enable 32-bits address */
    uint8_t clkDelay;         /*!< Clock count for read due to pad delay */
    uint8_t clkInvert;        /*!< Clock invert */
    uint8_t rxClkInvert;      /*!< RX clock invert */
    uint8_t doDelay;          /*!< Data out delay */
    uint8_t diDelay;          /*!< Data in delay */
    uint8_t oeDelay;          /*!< Output enable delay */
} SF_Ctrl_Cfg_Type;

/**
 *  @brief SF Ctrl bank2 controller configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type sbus2Select;         /*!< Select sbus2 as 2nd flash controller */
    BL_Fun_Type bank2RxClkInvertSrc; /*!< Select bank2 rx clock invert source */
    BL_Fun_Type bank2RxClkInvertSel; /*!< Select inveted bank2 rx clock */
    BL_Fun_Type bank2DelaySrc;       /*!< Select bank2 read delay source */
    uint8_t bank2ClkDelay;           /*!< Bank2 read delay cycle = n + 1 */
    uint8_t doDelay;                 /*!< Data out delay */
    uint8_t diDelay;                 /*!< Data in delay */
    uint8_t oeDelay;                 /*!< Output enable delay */
    SF_Ctrl_Remap_Type remap;        /*!< Select dual flash memory remap set */
    uint8_t remapLock;               /*!< Select memory remap lock */
} SF_Ctrl_Bank2_Cfg;

/**
 *  @brief SF Ctrl cmds configuration structure type definition
 */
typedef struct
{
    uint8_t ackLatency;                /*!< SF Ctrl ack latency cycles */
    BL_Fun_Type cmdsCoreEn;            /*!< SF Ctrl cmds core enable */
    BL_Fun_Type cmdsEn;                /*!< SF Ctrl cmds enable */
    SF_Ctrl_Wrap_Mode cmdsWrapMode;    /*!< SF Ctrl cmds wrap mode */
    SF_Ctrl_Wrap_Len_Type cmdsWrapLen; /*!< SF Ctrl cmds wrap length */
} SF_Ctrl_Cmds_Cfg;

/**
 *  @brief Serail flash command configuration structure type definition
 */
typedef struct
{
    uint8_t rwFlag;                  /*!< Read write flag */
    SF_Ctrl_Cmd_Mode_Type cmdMode;   /*!< Command mode */
    SF_Ctrl_Addr_Mode_Type addrMode; /*!< Address mode */
    uint8_t addrSize;                /*!< Address size */
    uint8_t dummyClks;               /*!< Dummy clocks */
    SF_Ctrl_Dmy_Mode_Type dummyMode; /*!< Dummy mode */
    SF_Ctrl_Data_Mode_Type dataMode; /*!< Data mode */
    uint8_t rsv[1];                  /*!<  */
    uint32_t nbData;                 /*!< Transfer number of bytes */
    uint32_t cmdBuf[2];              /*!< Command buffer */
} SF_Ctrl_Cmd_Cfg_Type;

/*@} end of group SF_CTRL_Public_Types */

/** @defgroup  SF_CTRL_Public_Constants
 *  @{
 */

/** @defgroup  SF_CTRL_PAD_TYPE
 *  @{
 */
#define IS_SF_CTRL_PAD_TYPE(type) (((type) == SF_CTRL_PAD1) || \
                                   ((type) == SF_CTRL_PAD2) || \
                                   ((type) == SF_CTRL_PAD3))

/** @defgroup  SF_CTRL_PIN_SELECT
 *  @{
 */
#define IS_SF_CTRL_PIN_SELECT(type) (((type) == SF_IO_EMB_SWAP_IO0_IO3) ||                   \
                                     ((type) == SF_IO_EMB_SWAP_DUAL_IO0_IO3) ||              \
                                     ((type) == SF_IO_EMB_SWAP_NONE) ||                      \
                                     ((type) == SF_IO_EMB_SWAP_NONE_DUAL_IO0) ||             \
                                     ((type) == SF_IO_EXT_SF2) ||                            \
                                     ((type) == SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2) ||       \
                                     ((type) == SF_IO_EMB_SWAP_DUAL_IO0_IO3_AND_EXT_SF2) ||  \
                                     ((type) == SF_IO_EMB_SWAP_NONE_AND_EXT_SF2) ||          \
                                     ((type) == SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2))

/** @defgroup  SF_CTRL_BANK_SELECT
 *  @{
 */
#define IS_SF_CTRL_BANK_SELECT(type) (((type) == SF_CTRL_FLASH_BANK0) || \
                                      ((type) == SF_CTRL_FLASH_BANK1))

/** @defgroup  SF_CTRL_WRAP_MODE
 *  @{
 */
#define IS_SF_CTRL_WRAP_MODE(type) (((type) == SF_CTRL_WRAP_MODE_0) || \
                                    ((type) == SF_CTRL_WRAP_MODE_1) || \
                                    ((type) == SF_CTRL_WRAP_MODE_2) || \
                                    ((type) == SF_CTRL_WRAP_MODE_3))

/** @defgroup  SF_CTRL_WRAP_LEN_TYPE
 *  @{
 */
#define IS_SF_CTRL_WRAP_LEN_TYPE(type) (((type) == SF_CTRL_WRAP_LEN_8) ||    \
                                        ((type) == SF_CTRL_WRAP_LEN_16) ||   \
                                        ((type) == SF_CTRL_WRAP_LEN_32) ||   \
                                        ((type) == SF_CTRL_WRAP_LEN_64) ||   \
                                        ((type) == SF_CTRL_WRAP_LEN_128) ||  \
                                        ((type) == SF_CTRL_WRAP_LEN_256) ||  \
                                        ((type) == SF_CTRL_WRAP_LEN_512) ||  \
                                        ((type) == SF_CTRL_WRAP_LEN_1024) || \
                                        ((type) == SF_CTRL_WRAP_LEN_2048) || \
                                        ((type) == SF_CTRL_WRAP_LEN_4096))

/** @defgroup  SF_CTRL_REMAP_TYPE
 *  @{
 */
#define IS_SF_CTRL_REMAP_TYPE(type) (((type) == SF_CTRL_ORIGINAL_MEMORY_MAP) || \
                                     ((type) == SF_CTRL_REMAP_16MB) ||          \
                                     ((type) == SF_CTRL_REMAP_8MB) ||           \
                                     ((type) == SF_CTRL_REMAP_4MB))

/** @defgroup  SF_CTRL_OWNER_TYPE
 *  @{
 */
#define IS_SF_CTRL_OWNER_TYPE(type) (((type) == SF_CTRL_OWNER_SAHB) || \
                                     ((type) == SF_CTRL_OWNER_IAHB))

/** @defgroup  SF_CTRL_RW_TYPE
 *  @{
 */
#define IS_SF_CTRL_RW_TYPE(type) (((type) == SF_CTRL_READ) || \
                                  ((type) == SF_CTRL_WRITE))

/** @defgroup  SF_CTRL_IO_TYPE
 *  @{
 */
#define IS_SF_CTRL_IO_TYPE(type) (((type) == SF_CTRL_NIO_MODE) || \
                                  ((type) == SF_CTRL_DO_MODE) ||  \
                                  ((type) == SF_CTRL_QO_MODE) ||  \
                                  ((type) == SF_CTRL_DIO_MODE) || \
                                  ((type) == SF_CTRL_QIO_MODE))

/** @defgroup  SF_CTRL_MODE_TYPE
 *  @{
 */
#define IS_SF_CTRL_MODE_TYPE(type) (((type) == SF_CTRL_SPI_MODE) || \
                                    ((type) == SF_CTRL_QPI_MODE))

/** @defgroup  SF_CTRL_CMD_MODE_TYPE
 *  @{
 */
#define IS_SF_CTRL_CMD_MODE_TYPE(type) (((type) == SF_CTRL_CMD_1_LINE) || \
                                        ((type) == SF_CTRL_CMD_4_LINES))

/** @defgroup  SF_CTRL_ADDR_MODE_TYPE
 *  @{
 */
#define IS_SF_CTRL_ADDR_MODE_TYPE(type) (((type) == SF_CTRL_ADDR_1_LINE) ||  \
                                         ((type) == SF_CTRL_ADDR_2_LINES) || \
                                         ((type) == SF_CTRL_ADDR_4_LINES))

/** @defgroup  SF_CTRL_DMY_MODE_TYPE
 *  @{
 */
#define IS_SF_CTRL_DMY_MODE_TYPE(type) (((type) == SF_CTRL_DUMMY_1_LINE) ||  \
                                        ((type) == SF_CTRL_DUMMY_2_LINES) || \
                                        ((type) == SF_CTRL_DUMMY_4_LINES))

/** @defgroup  SF_CTRL_DATA_MODE_TYPE
 *  @{
 */
#define IS_SF_CTRL_DATA_MODE_TYPE(type) (((type) == SF_CTRL_DATA_1_LINE) ||  \
                                         ((type) == SF_CTRL_DATA_2_LINES) || \
                                         ((type) == SF_CTRL_DATA_4_LINES))

/** @defgroup  SF_CTRL_AES_MODE_TYPE
 *  @{
 */
#define IS_SF_CTRL_AES_MODE_TYPE(type) (((type) == SF_CTRL_AES_CTR_MODE) || \
                                        ((type) == SF_CTRL_AES_XTS_MODE))

/** @defgroup  SF_CTRL_AES_KEY_TYPE
 *  @{
 */
#define IS_SF_CTRL_AES_KEY_TYPE(type) (((type) == SF_CTRL_AES_128BITS) || \
                                       ((type) == SF_CTRL_AES_256BITS) || \
                                       ((type) == SF_CTRL_AES_192BITS) || \
                                       ((type) == SF_CTRL_AES_128BITS_DOUBLE_KEY))

/*@} end of group SF_CTRL_Public_Constants */

/** @defgroup  SF_CTRL_Public_Macros
 *  @{
 */
#define SF_CTRL_NO_ADDRESS       0xFFFFFFFF
#define NOR_FLASH_CTRL_BUF_SIZE  256
#define NAND_FLASH_CTRL_BUF_SIZE 512

/*@} end of group SF_CTRL_Public_Macros */

/** @defgroup  SF_CTRL_Public_Functions
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
void SF_Ctrl_IRQHandler(void);
#endif
void SF_Ctrl_Enable(const SF_Ctrl_Cfg_Type *cfg);
void SF_Ctrl_Bank2_Enable(const SF_Ctrl_Bank2_Cfg *bank2Cfg);
void SF_Ctrl_Set_IO_Delay(SF_Ctrl_Pad_Type pad, uint8_t doDelay, uint8_t diDelay, uint8_t oeDelay);
void SF_Ctrl_Sbus2_Hold_Sram(void);
void SF_Ctrl_Sbus2_Release_Sram(void);
BL_Sts_Type SF_Ctrl_Is_Sbus2_Enable(void);
void SF_Ctrl_Sbus2_Replace(SF_Ctrl_Pad_Type pad);
void SF_Ctrl_Sbus2_Revoke_replace(void);
void SF_Ctrl_Sbus2_Set_Delay(uint8_t clkDelay, uint8_t rxClkInvert);
void SF_Ctrl_32bits_Addr_En(BL_Fun_Type en32BitsAddr);
uint8_t SF_Ctrl_Get_Clock_Delay(void);
void SF_Ctrl_Set_Clock_Delay(uint8_t delay);
uint8_t SF_Ctrl_Get_Wrap_Queue_Value(void);
void SF_Ctrl_Cmds_Set(SF_Ctrl_Cmds_Cfg *cmdsCfg, SF_Ctrl_Bank_Select bank);
void SF_Ctrl_Remap_Set(SF_Ctrl_Remap_Type remap, uint8_t lock);
void SF_Ctrl_Select_Pad(SF_Ctrl_Pin_Select sel);
void SF_Ctrl_Sbus_Select_Bank(SF_Ctrl_Bank_Select bank);
void SF_Ctrl_Set_Owner(SF_Ctrl_Owner_Type owner);
void SF_Ctrl_Disable(void);
void SF_Ctrl_AES_Enable_BE(void);
void SF_Ctrl_AES_Enable_LE(void);
void SF_Ctrl_AES_Set_Region(uint8_t region, uint8_t enable, uint8_t hwKey, uint32_t startAddr, uint32_t endAddr,
                            uint8_t locked);
void SF_Ctrl_AES_Set_Key(uint8_t region, uint8_t *key, SF_Ctrl_AES_Key_Type keyType);
void SF_Ctrl_AES_Set_Key_BE(uint8_t region, uint8_t *key, SF_Ctrl_AES_Key_Type keyType);
void SF_Ctrl_AES_XTS_Set_Key(uint8_t region, uint8_t *key, SF_Ctrl_AES_Key_Type keyType);
void SF_Ctrl_AES_Set_Key_BE(uint8_t region, uint8_t *key, SF_Ctrl_AES_Key_Type keyType);
void SF_Ctrl_AES_XTS_Set_Key(uint8_t region, uint8_t *key, SF_Ctrl_AES_Key_Type keyType);
void SF_Ctrl_AES_XTS_Set_Key_BE(uint8_t region, uint8_t *key, SF_Ctrl_AES_Key_Type keyType);
void SF_Ctrl_AES_Set_IV(uint8_t region, uint8_t *iv, uint32_t addrOffset);
void SF_Ctrl_AES_XTS_Set_IV(uint8_t region, uint8_t *iv, uint32_t addrOffset);
void SF_Ctrl_AES_Set_IV_BE(uint8_t region, uint8_t *iv, uint32_t addrOffset);
void SF_Ctrl_AES_XTS_Set_IV_BE(uint8_t region, uint8_t *iv, uint32_t addrOffset);
void SF_Ctrl_AES_Set_Mode(SF_Ctrl_AES_Mode_Type mode);
void SF_Ctrl_AES_Enable(void);
void SF_Ctrl_AES_Disable(void);
BL_Sts_Type SF_Ctrl_Is_AES_Enable(void);
void SF_Ctrl_Set_Flash_Image_Offset(uint32_t addrOffset, uint8_t group, SF_Ctrl_Bank_Select bank);
uint32_t SF_Ctrl_Get_Flash_Image_Offset(uint8_t group, SF_Ctrl_Bank_Select bank);
void SF_Ctrl_Lock_Flash_Image_Offset(uint8_t lock);
void SF_Ctrl_SendCmd(SF_Ctrl_Cmd_Cfg_Type *cfg);
void SF_Ctrl_Disable_Wrap_Access(uint8_t disable);
void SF_Ctrl_Flash_Read_Icache_Set(SF_Ctrl_Cmd_Cfg_Type *cfg, uint8_t cmdValid);
void SF_Ctrl_Flash2_Read_Icache_Set(SF_Ctrl_Cmd_Cfg_Type *cfg, uint8_t cmdValid);
BL_Sts_Type SF_Ctrl_GetBusyState(void);

/*@} end of group SF_CTRL_Public_Functions */

/*@} end of group SF_CTRL */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_SF_CTRL_H__ */
