#ifndef __BL602_MFG_EFUSE_H__
#define __BL602_MFG_EFUSE_H__

#include "stdint.h"

uint8_t mfg_efuse_get_rf_cal_slots(void);
void mfg_efuse_set_rf_cal_slots(uint8_t slots);
uint8_t mfg_efuse_is_xtal_capcode_slot_empty(uint8_t reload);
int8_t mfg_efuse_write_xtal_capcode_pre(uint8_t capcode,uint8_t program);
void mfg_efuse_write_xtal_capcode(void);
int8_t mfg_efuse_read_xtal_capcode(uint8_t *capcode,uint8_t reload);
uint8_t mfg_efuse_is_poweroffset_slot_empty(uint8_t reload);
int8_t mfg_efuse_write_poweroffset_pre(int8_t pwrOffset[14],uint8_t program);
void mfg_efuse_write_poweroffset(void);
int8_t mfg_efuse_read_poweroffset(int8_t pwrOffset[14],uint8_t reload);
uint8_t mfg_efuse_is_macaddr_slot_empty(uint8_t reload);
int8_t mfg_efuse_write_macaddr_pre(uint8_t mac[6],uint8_t program);
void mfg_efuse_write_macaddr(void);
int8_t mfg_efuse_read_macaddr(uint8_t mac[6],uint8_t reload);
int8_t mfg_efuse_read(uint32_t addr,uint32_t *data,uint32_t countInword,uint8_t reload);
int8_t mfg_efuse_program(void);
int8_t mfg_efuse_write_pre(uint32_t addr,uint32_t *data,uint32_t countInword);
int8_t mfg_efuse_read_poweroffset_ate(int8_t *pwrOffset);

#endif/*__BL602_MFG_EFUSE_H__*/
