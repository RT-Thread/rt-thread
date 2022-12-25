#include "bl808_glb.h"
#include "bl808_mfg_efuse.h"
#include "bl808_ef_ctrl.h"
#include "bl808_ef_cfg.h"

static uint8_t rf_cal_slots=3;
extern void main(void);
#define RF_CAL_SLOT_CFG_OFFSET      (4*13)
#ifdef BFLB_MCU_SDK
#include "bflb_platform.h"
#define mfg_print   MSG
#else
#define mfg_print   printf
#endif

uint8_t mfg_efuse_get_rf_cal_slots(void)
{
    return rf_cal_slots;
}

void mfg_efuse_set_rf_cal_slots(uint8_t slots)
{
    rf_cal_slots=slots;
}

uint8_t mfg_efuse_is_macaddr_slot_empty(uint8_t reload)
{
    uint8_t empty=0;    
    
    
    if(rf_cal_slots>=1&&EF_Ctrl_Is_MAC_Address_Slot_Empty(0,reload)){
        empty=1;
    }else if(rf_cal_slots>=2&&EF_Ctrl_Is_MAC_Address_Slot_Empty(1,reload)){
        empty=1;
    }else if(rf_cal_slots>=3&&EF_Ctrl_Is_MAC_Address_Slot_Empty(2,reload)){
        empty=1;
    }else{   
    }
 
   
    return empty;
}

int8_t mfg_efuse_write_macaddr_pre(uint8_t mac[6],uint8_t program)
{
    BL_Err_Type ret=SUCCESS;
    uint8_t slot=0xff;   
    
    if(rf_cal_slots>=1&&EF_Ctrl_Is_MAC_Address_Slot_Empty(0,1)){
        slot=0;
    }else if(rf_cal_slots>=2&&EF_Ctrl_Is_MAC_Address_Slot_Empty(1,1)){
        slot=1;
    }else if(rf_cal_slots>=3&&EF_Ctrl_Is_MAC_Address_Slot_Empty(2,1)){
        slot=2;
    }else{
        mfg_print("No empty slot found\r\n");
    }
    
    if(slot!=0xff){
        ret=EF_Ctrl_Write_MAC_Address_Opt(slot,mac,program);
        mfg_print("Write slot:%d\r\n",slot);
    }
    
    
    if(ret==SUCCESS){
        return 0;
    }else{
        return -1;
    }
}

void mfg_efuse_write_macaddr(void)
{ 
    EF_Ctrl_Program_Direct_R0(0,NULL,0);
    while(SET==EF_Ctrl_Busy());
}

int8_t mfg_efuse_read_macaddr(uint8_t mac[6],uint8_t reload)
{
    uint8_t slot=0xff;
    BL_Err_Type ret=ERROR;
    
    
    if(rf_cal_slots>=3&&(!EF_Ctrl_Is_MAC_Address_Slot_Empty(2,reload))){
        slot=2;
    }else if(rf_cal_slots>=2&&(!EF_Ctrl_Is_MAC_Address_Slot_Empty(1,reload))){
        slot=1;
    }else if(rf_cal_slots>=1&&(!EF_Ctrl_Is_MAC_Address_Slot_Empty(0,reload))){
        slot=0;
    }
    
    if(slot!=0xff){
        mfg_print("Read slot:%d\r\n",slot);
        ret=EF_Ctrl_Read_MAC_Address_Opt(slot,mac,reload);
    }else{
        mfg_print("No written slot found\r\n");
    }
    
    
    if(ret==SUCCESS){
        return 0;
    }else{
        return -1;
    }
}
