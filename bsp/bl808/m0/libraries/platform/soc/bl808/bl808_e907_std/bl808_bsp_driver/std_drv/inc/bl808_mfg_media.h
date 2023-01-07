#ifndef __BL602_MFG_MEDIA_H__
#define __BL602_MFG_MEDIA_H__

#include "stdint.h"
#include "bl808_mfg_efuse.h"
#include "bl808_mfg_flash.h"

int8_t mfg_media_init_need_lock( SPI_Flash_Cfg_Type *flashCfg);
int8_t mfg_media_init_with_lock( SPI_Flash_Cfg_Type *flashCfg);
uint8_t mfg_media_is_xtal_capcode_slot_empty(uint8_t reload);
int8_t mfg_media_write_xtal_capcode_pre_need_lock(uint8_t capcode,uint8_t program);
void mfg_media_write_xtal_capcode_need_lock(void);
int8_t mfg_media_read_xtal_capcode_need_lock(uint8_t *capcode,uint8_t reload);
int8_t mfg_media_write_xtal_capcode_pre_with_lock(uint8_t capcode,uint8_t program);
void mfg_media_write_xtal_capcode_with_lock(void);
int8_t mfg_media_read_xtal_capcode_with_lock(uint8_t *capcode,uint8_t reload);
int8_t mfg_media_read_xtal_capcode(uint8_t *capcode,uint8_t reload);
uint8_t mfg_media_is_poweroffset_slot_empty(uint8_t reload);
int8_t mfg_media_write_poweroffset_pre_need_lock(int8_t pwrOffset[14],uint8_t program);
void mfg_media_write_poweroffset_need_lock(void);
int8_t mfg_media_read_poweroffset_need_lock(int8_t pwrOffset[14],uint8_t reload);
int8_t mfg_media_read_poweroffset(int8_t pwrOffset[14],uint8_t reload);
int8_t mfg_media_write_poweroffset_pre_with_lock(int8_t pwrOffset[14],uint8_t program);
void mfg_media_write_poweroffset_with_lock(void);
int8_t mfg_media_read_poweroffset_with_lock(int8_t pwrOffset[14],uint8_t reload);
uint8_t mfg_media_is_macaddr_slot_empty(uint8_t reload);
int8_t mfg_media_write_macaddr_pre_need_lock(uint8_t mac[6],uint8_t program);
void mfg_media_write_macaddr_need_lock(void);
int8_t mfg_media_read_macaddr_need_lock(uint8_t mac[6],uint8_t reload);
int8_t mfg_media_write_macaddr_pre_with_lock(uint8_t mac[6],uint8_t program);
void mfg_media_write_macaddr_with_lock(void);
int8_t mfg_media_read_macaddr_with_lock(uint8_t mac[6],uint8_t reload);
int8_t mfg_media_read_macaddr(uint8_t mac[6],uint8_t reload);

#endif/*__BL602_MFG_MEDIA_H__*/
