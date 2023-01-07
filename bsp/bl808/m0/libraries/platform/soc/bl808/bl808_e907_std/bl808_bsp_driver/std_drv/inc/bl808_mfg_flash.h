#ifndef __BL602_MFG_FLASH_H__
#define __BL602_MFG_FLASH_H__

#include "stdint.h"
#include "bl808_xip_sflash.h"

typedef struct rf_para_flash_tag{
    uint32_t magic;            //"RFPA"
    uint8_t capcode_valid;     //0x5A
    uint8_t capcode;
    uint8_t poweroffset_valid; //0x5A
    int8_t poweroffset[3];
    uint8_t mac_valid;         //0x5A
    uint8_t mac[6];
    uint8_t rsvd[3];
    uint32_t crc32;
}rf_para_flash_t;

int8_t mfg_flash_init( SPI_Flash_Cfg_Type *flashCfg);
int8_t mfg_flash_write_xtal_capcode_pre(uint8_t capcode,uint8_t program);
void mfg_flash_write_xtal_capcode(void);
int8_t mfg_flash_read_xtal_capcode(uint8_t *capcode,uint8_t reload);
int8_t mfg_flash_write_poweroffset_pre(int8_t pwrOffset[14],uint8_t program);
void mfg_flash_write_poweroffset(void);
int8_t mfg_flash_read_poweroffset(int8_t pwrOffset[14],uint8_t reload);
int8_t mfg_flash_write_macaddr_pre(uint8_t mac[6],uint8_t program);
void mfg_flash_write_macaddr(void);
int8_t mfg_flash_read_macaddr(uint8_t mac[6],uint8_t reload);

#endif/*__BL602_MFG_FLASH_H__*/
