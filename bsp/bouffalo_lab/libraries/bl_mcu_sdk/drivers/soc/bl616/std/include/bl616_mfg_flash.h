#ifndef __BL616_MFG_FLASH_H__
#define __BL616_MFG_FLASH_H__

#include "stdint.h"
#include "bflb_xip_sflash.h"

typedef struct rf_para_flash_tag {
    uint32_t magic;        //"RFPA"
    uint8_t capcode_valid; //0x5A
    uint8_t capcode;
    uint8_t poweroffset_valid; //0x5A
    int8_t poweroffset[3];
    uint8_t mac_valid; //0x5A
    uint8_t mac[6];
    uint8_t rsvd[3];
    uint32_t crc32;
} rf_para_flash_t;

int mfg_flash_init(spi_flash_cfg_type *flashCfg);
int mfg_flash_write_xtal_capcode_pre(uint8_t capcode, uint8_t program);
void mfg_flash_write_xtal_capcode(void);
int mfg_flash_read_xtal_capcode(uint8_t *capcode, uint8_t reload);
int mfg_flash_write_hp_poweroffset_pre(int8_t pwrOffset[14], uint8_t program);
void mfg_flash_write_hp_poweroffset(void);
int mfg_flash_read_hp_poweroffset(int8_t pwrOffset[14], uint8_t reload);
int mfg_flash_write_lp_poweroffset_pre(int8_t pwrOffset[14], uint8_t program);
void mfg_flash_write_lp_poweroffset(void);
int mfg_flash_read_lp_poweroffset(int8_t pwrOffset[14], uint8_t reload);
int mfg_flash_write_macaddr_pre(uint8_t mac[6], uint8_t program);
void mfg_flash_write_macaddr(void);
int mfg_flash_read_macaddr(uint8_t mac[6], uint8_t reload);
int mfg_flash_write_bz_poweroffset_pre(int8_t pwrOffset[5], uint8_t program);
void mfg_flash_write_bz_poweroffset(void);
int mfg_flash_read_bz_poweroffset(int8_t pwrOffset[20], uint8_t reload);

#endif /*__BL616_MFG_FLASH_H__*/
