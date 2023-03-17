#ifndef _BFLB_FLASH_H
#define _BFLB_FLASH_H

#include "bflb_core.h"
#include "bflb_sflash.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/** @defgroup FLASH_IOMODE flash iomode definition
  * @{
  */
#define FLASH_IOMODE_NIO 0 /*!< Normal IO mode define */
#define FLASH_IOMODE_DO  1 /*!< Dual Output mode define */
#define FLASH_IOMODE_QO  2 /*!< Quad Output mode define */
#define FLASH_IOMODE_DIO 3 /*!< Dual IO mode define */
#define FLASH_IOMODE_QIO 4 /*!< Quad IO mode define */
/**
  * @}
  */

/** @defgroup FLASH_AES_KEY_TYPE flash aes key type definition
  * @{
  */
#define FLASH_AES_KEY_128BITS        0
#define FLASH_AES_KEY_192BITS        2
#define FLASH_AES_KEY_256BITS        1
#define FLASH_AES_KEY_DOUBLE_128BITS 3
/**
  * @}
  */

#if defined(BL602) || defined(BL702) || defined(BL702L)
#define FLASH_XIP_BASE (0x23000000)
#elif defined(BL616) || defined(BL628)
#define FLASH_XIP_BASE (0xA0000000)
#elif defined(BL808) || defined(BL606P)
#define FLASH_XIP_BASE (0x58000000)
#endif

struct bflb_flash_aes_config_s {
    uint8_t region;
    uint8_t region_enable;
    uint8_t lock_enable;
    const uint8_t *key;
    uint8_t keybits;
    uint8_t *iv;
    uint32_t start_addr;
    uint32_t end_addr;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize flash.
 *
 * @return Zero on success; a negated errno value on failure
 */
int bflb_flash_init(void);

#if defined(BL616) || defined(BL606P) || defined(BL808)
/**
 * @brief flash_set_cmds
 *
 * @return None
 */
void bflb_flash_set_cmds(spi_flash_cfg_type *p_flash_cfg);
#endif

/**
 * @brief Get flash jedec id.
 *
 * @return uint32_t
 */
uint32_t bflb_flash_get_jedec_id(void);

/**
 * @brief Get flash config.
 *
 * @param [out] cfg_addr pointer to save config
 * @param [in] len flash config size
 */
void bflb_flash_get_cfg(uint8_t **cfg_addr, uint32_t *len);

/**
 * @brief Set flash iomode.
 *
 * @param [in] iomode flash iomode, use @ref FLASH_IOMODE
 */
void bflb_flash_set_iomode(uint8_t iomode);

/**
 * @brief Get flash image offset.
 *
 * @return flash image offset
 */
uint32_t bflb_flash_get_image_offset(void);

/**
 * @brief Erase flash with sectors.
 *
 * @param [in] addr
 * @param [in] len
 * @return Zero on success; a negated errno value on failure
 */
int bflb_flash_erase(uint32_t addr, uint32_t len);

/**
 * @brief Write data into flash.
 *
 * @param [in] addr flash physical address
 * @param [in] data pointer to data buffer
 * @param [in] len length of data
 * @return Zero on success; a negated errno value on failure
 */
int bflb_flash_write(uint32_t addr, uint8_t *data, uint32_t len);

/**
 * @brief Read data from flash.
 *
 * @param [in] addr flash physical address
 * @param [out] data pointer to data buffer
 * @param [in] len length of data
 * @return Zero on success; a negated errno value on failure
 */
int bflb_flash_read(uint32_t addr, uint8_t *data, uint32_t len);

/**
 * @brief Config flash cache.
 *
 * @param [in] cont_read enable or not continuous read mode.
 * @param [in] cache_enable enable cache or not
 * @param [in] cache_way_disable ways of cache to disable
 * @param [in] flash_offset flash image offset
 * @return Zero on success; a negated errno value on failure
 */
int bflb_flash_set_cache(uint8_t cont_read, uint8_t cache_enable, uint8_t cache_way_disable, uint32_t flash_offset);

/**
 * @brief Initialize flash aes controller.
 *
 * @param [in] config pointer to flash aes config.
 */
void bflb_flash_aes_init(struct bflb_flash_aes_config_s *config);

/**
 * @brief Enable flash decrypt with aes.
 *
 */
void bflb_flash_aes_enable(void);

/**
 * @brief Disable flash decrypt with aes.
 *
 */
void bflb_flash_aes_disable(void);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */

/**
  * @}
  */

#endif