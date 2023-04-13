#ifndef __BL616_MFG_EFUSE_H__
#define __BL616_MFG_EFUSE_H__

#include "stdint.h"

uint8_t mfg_efuse_get_rf_cal_slots(void);
void mfg_efuse_set_rf_cal_slots(uint8_t slots);
uint8_t mfg_efuse_is_xtal_capcode_slot_empty(uint8_t reload);
int mfg_efuse_write_xtal_capcode_pre(uint8_t capcode, uint8_t program);
void mfg_efuse_write_xtal_capcode(void);
int mfg_efuse_read_xtal_capcode(uint8_t *capcode, uint8_t reload);
uint8_t mfg_efuse_is_hp_poweroffset_slot_empty(uint8_t reload);
int mfg_efuse_write_hp_poweroffset_pre(int8_t pwr_offset[14], uint8_t program);
void mfg_efuse_write_hp_poweroffset(void);
int mfg_efuse_read_hp_poweroffset(int8_t pwr_offset[14], uint8_t reload);
uint8_t mfg_efuse_is_lp_poweroffset_slot_empty(uint8_t reload);
int mfg_efuse_write_lp_poweroffset_pre(int8_t pwr_offset[14], uint8_t program);
void mfg_efuse_write_lp_poweroffset(void);
int mfg_efuse_read_lp_poweroffset(int8_t pwr_offset[14], uint8_t reload);
uint8_t mfg_efuse_is_macaddr_slot_empty(uint8_t reload);
int8_t mfg_efuse_write_macaddr_pre(uint8_t mac[6], uint8_t program);
void mfg_efuse_write_macaddr(void);
int8_t mfg_efuse_read_macaddr(uint8_t mac[6], uint8_t reload);
uint8_t mfg_efuse_is_bz_poweroffset_slot_empty(uint8_t reload);
int mfg_efuse_write_bz_poweroffset_pre(int8_t pwr_offset[5], uint8_t program);
void mfg_efuse_write_bz_poweroffset(void);
int mfg_efuse_read_bz_poweroffset(int8_t pwr_offset[20], uint8_t reload);
void mfg_efuse_program(uint32_t addr,uint32_t *pword,uint32_t countInword,uint32_t program);
void mfg_efuse_read(uint32_t addr,uint32_t *pword,uint32_t countInword,uint8_t reload);

#endif /*__BL616_MFG_EFUSE_H__*/
