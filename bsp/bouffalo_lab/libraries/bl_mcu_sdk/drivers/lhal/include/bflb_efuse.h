#ifndef _BFLB_EFUSE_H
#define _BFLB_EFUSE_H

#include "bflb_core.h"

#ifdef __cplusplus
extern "C" {
#endif

void bflb_efuse_get_chipid(uint8_t chipid[8]);

uint8_t bflb_efuse_is_mac_address_slot_empty(uint8_t slot, uint8_t reload);
int bflb_efuse_write_mac_address_opt(uint8_t slot, uint8_t mac[6], uint8_t program);
int bflb_efuse_read_mac_address_opt(uint8_t slot, uint8_t mac[6], uint8_t reload);

float bflb_efuse_get_adc_trim(void);
uint32_t bflb_efuse_get_adc_tsen_trim(void);

void bflb_efuse_read_secure_boot(uint8_t *sign, uint8_t *aes);
void bflb_efuse_write_aes_key(uint8_t index, uint8_t *data, uint32_t len);
void bflb_efuse_read_aes_key(uint8_t index, uint8_t *data, uint32_t len);

void bflb_efuse_write_sw_usage(uint32_t index, uint32_t usage, uint8_t program);
void bflb_efuse_read_sw_usage(uint32_t index, uint32_t *usage);

#ifdef __cplusplus
}
#endif

#endif
