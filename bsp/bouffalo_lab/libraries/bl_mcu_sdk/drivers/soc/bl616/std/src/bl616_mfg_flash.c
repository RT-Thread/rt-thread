#include "bl616_mfg_flash.h"

//static rf_para_flash_t rf_para;
//static uint32_t rf_para_addr = 0;
//static spi_flash_cfg_type *pFlashCfg;

//#define RF_PARA_MAGIC_FLAG      0x41504652
#define RF_PARA_MAGIC_FLAG 0x41
#define RF_PARA_VALID_FLAG 0x5A
#define RF_PARA_PART_NAME  "rf_para"

static int PtTable_Flash_Read(uint32_t addr, uint8_t *data, uint32_t len)
{
    return 0;
}

int mfg_flash_init(spi_flash_cfg_type *flashCfg)
{
    PtTable_Flash_Read(0, NULL, 0);
    return -1;
}

static int mfg_flash_program(void)
{
    return 0;
}

static int mfg_flash_read(void)
{
    return 0;
}

int mfg_flash_write_xtal_capcode_pre(uint8_t capcode, uint8_t program)
{
    mfg_flash_program();
    return 0;
}

void mfg_flash_write_xtal_capcode(void)
{
    mfg_flash_program();
}

int mfg_flash_read_xtal_capcode(uint8_t *capcode, uint8_t reload)
{
    mfg_flash_read();
    return 0;
}

int mfg_flash_write_hp_poweroffset_pre(int8_t pwrOffset[14], uint8_t program)
{
    mfg_flash_program();
    return 0;
}

void mfg_flash_write_hp_poweroffset(void)
{
    mfg_flash_program();
}

int mfg_flash_read_hp_poweroffset(int8_t pwrOffset[14], uint8_t reload)
{
    mfg_flash_read();
    return 0;
}

int mfg_flash_write_lp_poweroffset_pre(int8_t pwrOffset[14], uint8_t program)
{
    mfg_flash_program();
    return 0;
}

void mfg_flash_write_lp_poweroffset(void)
{
    mfg_flash_program();
}

int mfg_flash_read_lp_poweroffset(int8_t pwrOffset[14], uint8_t reload)
{
    mfg_flash_read();
    return 0;
}

int mfg_flash_write_macaddr_pre(uint8_t mac[6], uint8_t program)
{
    mfg_flash_program();
    return 0;
}

void mfg_flash_write_macaddr(void)
{
    mfg_flash_program();
}

int mfg_flash_read_macaddr(uint8_t mac[6], uint8_t reload)
{
    mfg_flash_read();
    return 0;
}

int mfg_flash_write_bz_poweroffset_pre(int8_t pwrOffset[5], uint8_t program)
{
    mfg_flash_program();
    return 0;
}

void mfg_flash_write_bz_poweroffset(void)
{
    mfg_flash_program();
}

int mfg_flash_read_bz_poweroffset(int8_t pwrOffset[5], uint8_t reload)
{
    mfg_flash_read();
    return 0;
}
