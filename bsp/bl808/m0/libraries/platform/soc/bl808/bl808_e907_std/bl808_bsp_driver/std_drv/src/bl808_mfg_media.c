#include "bl808_mfg_media.h"

static uint8_t rf_para_on_flash=0;

#if 0
int8_t mfg_media_init_need_lock( SPI_Flash_Cfg_Type *flashCfg)
{
    if(0==mfg_flash_init(flashCfg)){
        rf_para_on_flash=1;
    }else{
        rf_para_on_flash=0;
    }
    return 0;
}

int8_t mfg_media_init_with_lock( SPI_Flash_Cfg_Type *flashCfg)
{
    int8_t ret;

    __disable_irq();
    ret=mfg_media_init_need_lock(flashCfg);
    __enable_irq();

    return ret;
}

uint8_t mfg_media_is_xtal_capcode_slot_empty(uint8_t reload)
{
    if(rf_para_on_flash){
        return 1;
    }else{
        return mfg_efuse_is_xtal_capcode_slot_empty(reload);
    }
}

int8_t mfg_media_write_xtal_capcode_pre_need_lock(uint8_t capcode,uint8_t program)
{
    if(rf_para_on_flash){
        return mfg_flash_write_xtal_capcode_pre(capcode,program);
    }else{
        return mfg_efuse_write_xtal_capcode_pre(capcode,program);
    }
}

int8_t mfg_media_write_xtal_capcode_pre_with_lock(uint8_t capcode,uint8_t program)
{
    int8_t ret;

    __disable_irq();
    ret=mfg_media_write_xtal_capcode_pre_need_lock(capcode,program);
    __enable_irq();

    return ret;
}

void mfg_media_write_xtal_capcode_need_lock(void)
{
    if(rf_para_on_flash){
       return mfg_flash_write_xtal_capcode();
    }else{
       return mfg_efuse_write_xtal_capcode();
    }
}

void mfg_media_write_xtal_capcode_with_lock(void)
{
    __disable_irq();
    mfg_media_write_xtal_capcode_need_lock();
    __enable_irq();
}

int8_t mfg_media_read_xtal_capcode_need_lock(uint8_t *capcode,uint8_t reload)
{
    if(rf_para_on_flash){
       return mfg_flash_read_xtal_capcode(capcode,reload);
    }else{
       return mfg_efuse_read_xtal_capcode(capcode,reload);
    }
}

int8_t mfg_media_read_xtal_capcode_with_lock(uint8_t *capcode,uint8_t reload)
{
    int8_t ret;

    __disable_irq();
    ret=mfg_media_read_xtal_capcode_need_lock(capcode,reload);
    __enable_irq();

    return ret;
}

int8_t mfg_media_read_xtal_capcode(uint8_t *capcode,uint8_t reload)
{
    return mfg_media_read_xtal_capcode_need_lock(capcode,reload);
}

uint8_t mfg_media_is_poweroffset_slot_empty(uint8_t reload)
{
    if(rf_para_on_flash){
        return 1;
    }else{
        return mfg_efuse_is_poweroffset_slot_empty(reload);
    }
}

int8_t mfg_media_write_poweroffset_pre_need_lock(int8_t pwrOffset[14],uint8_t program)
{
    if(rf_para_on_flash){
        return mfg_flash_write_poweroffset_pre(pwrOffset,program);
    }else{
        return mfg_efuse_write_poweroffset_pre(pwrOffset,program);
    }
}

int8_t mfg_media_write_poweroffset_pre_with_lock(int8_t pwrOffset[14],uint8_t program)
{
    int ret;

    __disable_irq();
    ret=mfg_media_write_poweroffset_pre_need_lock(pwrOffset,program);
    __enable_irq();

    return ret;
}

void mfg_media_write_poweroffset_need_lock(void)
{
    if(rf_para_on_flash){
        return mfg_flash_write_poweroffset();
    }else{
        return mfg_efuse_write_poweroffset();
    }
}

void mfg_media_write_poweroffset_with_lock(void)
{
    __disable_irq();
    mfg_media_write_poweroffset_need_lock();
    __enable_irq();
}

int8_t mfg_media_read_poweroffset_need_lock(int8_t pwrOffset[14],uint8_t reload)
{
    if(rf_para_on_flash){
        return mfg_flash_read_poweroffset(pwrOffset,reload);
    }else{
        return mfg_efuse_read_poweroffset(pwrOffset,reload);
    }
}

int8_t mfg_media_read_poweroffset_with_lock(int8_t pwrOffset[14],uint8_t reload)
{
    int ret;

    __disable_irq();
    ret=mfg_media_read_poweroffset_need_lock(pwrOffset,reload);
    __enable_irq();
    
    return ret;
}

int8_t mfg_media_read_poweroffset(int8_t pwrOffset[14],uint8_t reload)
{
    return mfg_media_read_poweroffset_need_lock(pwrOffset,reload);
}
#endif
uint8_t mfg_media_is_macaddr_slot_empty(uint8_t reload)
{
    if(rf_para_on_flash){
        return 1;
    }else{
        return mfg_efuse_is_macaddr_slot_empty(reload);
    }
}

int8_t mfg_media_write_macaddr_pre_need_lock(uint8_t mac[6],uint8_t program)
{
    if(rf_para_on_flash){
        return mfg_flash_write_macaddr_pre(mac,program);
    }else{
        return mfg_efuse_write_macaddr_pre(mac,program);
    }
}

int8_t mfg_media_write_macaddr_pre_with_lock(uint8_t mac[6],uint8_t program)
{
    int ret;

    __disable_irq();
    ret=mfg_media_write_macaddr_pre_need_lock(mac,program);    
    __enable_irq();
    
    return ret;
}

void mfg_media_write_macaddr_need_lock(void)
{
    if(rf_para_on_flash){
        return mfg_flash_write_macaddr();
    }else{
        return mfg_efuse_write_macaddr();
    }
}

void mfg_media_write_macaddr_with_lock(void)
{
    __disable_irq();
    mfg_media_write_macaddr_need_lock();    
    __enable_irq();
}

int8_t mfg_media_read_macaddr_need_lock(uint8_t mac[6],uint8_t reload)
{
    if(rf_para_on_flash){
        return mfg_flash_read_macaddr(mac,reload);
    }else{
        return mfg_efuse_read_macaddr(mac,reload);
    }
}

int8_t mfg_media_read_macaddr_with_lock(uint8_t mac[6],uint8_t reload)
{
    int ret;

    __disable_irq();
    ret=mfg_media_read_macaddr_need_lock(mac,reload);       
    __enable_irq();

    return ret;
}

int8_t mfg_media_read_macaddr(uint8_t mac[6],uint8_t reload)
{

    return mfg_media_read_macaddr_need_lock(mac,reload);
}

