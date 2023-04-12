#ifndef __BL616_MFG_MEDIA_H__
#define __BL616_MFG_MEDIA_H__

#include "stdint.h"
#include "bl616_mfg_efuse.h"
#include "bl616_mfg_flash.h"

int mfg_media_init_need_lock(spi_flash_cfg_type *flashCfg);
int mfg_media_init_with_lock(spi_flash_cfg_type *flashCfg);
uint8_t mfg_media_is_xtal_capcode_slot_empty(uint8_t reload);
int mfg_media_write_xtal_capcode_pre_need_lock(uint8_t capcode, uint8_t program);
int mfg_media_write_xtal_capcode_pre_with_lock(uint8_t capcode, uint8_t program);
void mfg_media_write_xtal_capcode_need_lock(void);
void mfg_media_write_xtal_capcode_with_lock(void);
int mfg_media_read_xtal_capcode_need_lock(uint8_t *capcode, uint8_t reload);
int mfg_media_read_xtal_capcode_with_lock(uint8_t *capcode, uint8_t reload);
int mfg_media_read_xtal_capcode(uint8_t *capcode, uint8_t reload);
uint8_t mfg_media_is_hp_poweroffset_slot_empty(uint8_t reload);
int mfg_media_write_hp_poweroffset_pre_need_lock(int8_t pwrOffset[14], uint8_t program);
int mfg_media_write_hp_poweroffset_pre_with_lock(int8_t pwrOffset[14], uint8_t program);
void mfg_media_write_hp_poweroffset_need_lock(void);
void mfg_media_write_hp_poweroffset_with_lock(void);
int mfg_media_read_hp_poweroffset_need_lock(int8_t pwrOffset[14], uint8_t reload);
int mfg_media_read_hp_poweroffset_with_lock(int8_t pwrOffset[14], uint8_t reload);
int mfg_media_read_hp_poweroffset(int8_t pwrOffset[14], uint8_t reload);
uint8_t mfg_media_is_lp_poweroffset_slot_empty(uint8_t reload);
int mfg_media_write_lp_poweroffset_pre_need_lock(int8_t pwrOffset[14], uint8_t program);
int mfg_media_write_lp_poweroffset_pre_with_lock(int8_t pwrOffset[14], uint8_t program);
void mfg_media_write_lp_poweroffset_need_lock(void);
void mfg_media_write_lp_poweroffset_with_lock(void);
int mfg_media_read_lp_poweroffset_need_lock(int8_t pwrOffset[14], uint8_t reload);
int mfg_media_read_lp_poweroffset_with_lock(int8_t pwrOffset[14], uint8_t reload);
int mfg_media_read_lp_poweroffset(int8_t pwrOffset[14], uint8_t reload);
uint8_t mfg_media_is_macaddr_slot_empty(uint8_t reload);
int mfg_media_write_macaddr_pre_need_lock(uint8_t mac[6], uint8_t program);
int mfg_media_write_macaddr_pre_with_lock(uint8_t mac[6], uint8_t program);
void mfg_media_write_macaddr_need_lock(void);
void mfg_media_write_macaddr_with_lock(void);
int mfg_media_read_macaddr_need_lock(uint8_t mac[6], uint8_t reload);
int mfg_media_read_macaddr_with_lock(uint8_t mac[6], uint8_t reload);
int mfg_media_read_macaddr(uint8_t mac[6], uint8_t reload);
uint8_t mfg_media_is_bz_poweroffset_slot_empty(uint8_t reload);
int mfg_media_write_bz_poweroffset_pre_need_lock(int8_t pwrOffset[5], uint8_t program);
int mfg_media_write_bz_poweroffset_pre_with_lock(int8_t pwrOffset[5], uint8_t program);
void mfg_media_write_bz_poweroffset_need_lock(void);
void mfg_media_write_bz_poweroffset_with_lock(void);
int mfg_media_read_bz_poweroffset_need_lock(int8_t pwrOffset[5], uint8_t reload);
int mfg_media_read_bz_poweroffset_with_lock(int8_t pwrOffset[5], uint8_t reload);
int mfg_media_read_bz_poweroffset(int8_t pwrOffset[5], uint8_t reload);


#endif /*__BL616_MFG_MEDIA_H__*/
