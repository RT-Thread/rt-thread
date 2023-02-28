/*
 * =====================================================================================
 *
 *       Filename:  hal_efuse.c
 *
 *    Description:  efuse
 *
 *        Version:  1.0
 *        Created:  2019-07-19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wangwei
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <sunxi_hal_efuse.h>
#include <sunxi_hal_common.h>
#include <hal_osal.h>

#include "platform_efuse.h"
#include "efuse.h"

#define EFUSE_CHIPID_NAME            "chipid"
#define EFUSE_BROM_CONF_NAME         "brom_conf"
#define EFUSE_BROM_TRY_NAME          "brom_try"
#define EFUSE_THM_SENSOR_NAME        "thermal_sensor"

#define EFUSE_FT_ZONE_NAME           "ft_zone"
#define EFUSE_TV_OUT_NAME            "tvout"
#define EFUSE_OEM_NAME               "oem"
#define EFUSE_OEM_SEC_NAME           "oem_secure"
#define EFUSE_EMAC_NAME              "emac"

#define EFUSE_WR_PROTECT_NAME        "write_protect"
#define EFUSE_RD_PROTECT_NAME        "read_protect"
#define EFUSE_IN_NAME                "in"
#define EFUSE_ID_NAME                "id"
#define EFUSE_ROTPK_NAME             "rotpk"
#define EFUSE_SSK_NAME               "ssk"
#define EFUSE_RSSK_NAME              "rssk"
#define EFUSE_HDCP_HASH_NAME         "hdcp_hash"
#define EFUSE_HDCP_PKF_NAME          "hdcp_pkf"
#define EFUSE_HDCP_DUK_NAME          "hdcp_duk"
#define EFUSE_EK_HASH_NAME           "ek_hash"
#define EFUSE_SN_NAME                "sn"
#define EFUSE_NV1_NAME               "nv1"
#define EFUSE_NV2_NAME               "nv2"
#define EFUSE_BACKUP_KEY_NAME        "backup_key"
#define EFUSE_RSAKEY_HASH_NAME       "rsakey_hash"
#define EFUSE_RENEW_NAME             "renewability"
#define EFUSE_IPTV_MAC              "efusemac"
#define EFUSE_OPT_ID_NAME            "operator_id"
#define EFUSE_LIFE_CYCLE_NAME        "life_cycle"
#define EFUSE_JTAG_SECU_NAME         "jtag_security"
#define EFUSE_JTAG_ATTR_NAME         "jtag_attr"
#define EFUSE_CHIP_CONF_NAME         "chip_config"
#define EFUSE_RESERVED_NAME          "reserved"
#define EFUSE_RESERVED2_NAME         "reserved2"
#define EFUSE_HUK_NAME               "huk"
#define EFUSE_ANTI_BLUSH_NAME        "anti_blushing"
#define EFUSE_TVE_NAME               "tve"

/* For KeyLadder */
#define EFUSE_KL_SCK0_NAME           "keyladder_sck0"
#define EFUSE_KL_KEY0_NAME           "keyladder_master_key0"
#define EFUSE_KL_SCK1_NAME           "keyladder_sck1"
#define EFUSE_KL_KEY1_NAME           "keyladder_master_key1"

#define SUNXI_KEY_NAME_LEN  64


#if EFUSE_DBG_EN
#define EFUSE_DBG(fmt,args...)  hal_log_debug(fmt ,##args)
#define EFUSE_DBG_E   1
static unsigned int g_err_flg = 0;
#else
#define EFUSE_DBG_DUMP(...) do{} while(0);
#define EFUSE_DBG(...) do{} while(0);
#define EFUSE_DBG_E   0
#endif

static hal_spinlock_t efuse_lock;

int __efuse_acl_ck(efuse_key_map_new_t *key_map,int burn);


static efuse_key_map_new_t g_key_info[] = {
EFUSE_DEF_ITEM(EFUSE_CHIPID_NAME, 0x0, 128, -1, 0, EFUSE_RO),
EFUSE_DEF_ITEM(EFUSE_THM_SENSOR_NAME, EFUSE_THERMAL_SENSOR, 64, -1, 0, EFUSE_RO),
EFUSE_DEF_ITEM(EFUSE_FT_ZONE_NAME, EFUSE_TF_ZONE, 128, -1, 0, EFUSE_RO),
#ifdef EFUSE_ROTPK
EFUSE_DEF_ITEM(EFUSE_ROTPK_NAME, EFUSE_ROTPK, 256, -1, 12, EFUSE_RO),
#endif
#ifdef EFUSE_NV1
EFUSE_DEF_ITEM(EFUSE_NV1_NAME, EFUSE_NV1, 32, -1, 15, EFUSE_RO),
#endif
#ifdef EFUSE_PSENSOR
EFUSE_DEF_ITEM("psensor", EFUSE_PSENSOR, 32, -1, 15, EFUSE_RO),
#endif
#ifdef EFUSE_TVOUT
EFUSE_DEF_ITEM(EFUSE_TV_OUT_NAME, EFUSE_TVOUT, SID_TVOUT_SIZE, -1, -1, EFUSE_RO),
#endif
//EFUSE_DEF_ITEM("anti_blushing", EFUSE_ANTI_BLUSHING, 32, -1, 15, EFUSE_RO),
//EFUSE_DEF_ITEM(EFUSE_RESERVED_NAME, EFUSE_CLIENT_RESERVE, 256, -1, 12, EFUSE_RO),
EFUSE_DEF_ITEM("", 0, 0, 0, 0, EFUSE_PRIVATE),
};


static uint _efuse_reg_read_key(uint key_index)
{
    uint reg_val;
    uint32_t cpu_sr;

//  taskENTER_CRITICAL(cpu_sr);
    //rt_enter_critical();
    cpu_sr = hal_spin_lock_irqsave(&efuse_lock);

    reg_val = hal_readl((unsigned long)SID_PRCTL);
    reg_val &= ~((0x1ff<<16)|0x3);
    reg_val |= key_index<<16;
    hal_writel(reg_val, (unsigned long)SID_PRCTL);
    reg_val &= ~((0xff<<8)|0x3);
    reg_val |= (SID_OP_LOCK<<8) | 0x2;
    hal_writel(reg_val, (unsigned long)SID_PRCTL);
    while(hal_readl(SID_PRCTL)&0x2){};
    reg_val &= ~((0x1ff<<16)|(0xff<<8)|0x3);
    hal_writel(reg_val, (unsigned long)SID_PRCTL);
    reg_val = hal_readl((unsigned long)SID_RDKEY);

    hal_spin_unlock_irqrestore(&efuse_lock, cpu_sr);
    //rt_exit_critical();
//  taskEXIT_CRITICAL(cpu_sr);
    return reg_val;
}


static void _efuse_program_key(uint key_index, uint key_value)
{
    uint reg_val;
    uint32_t cpu_sr;

//  taskENTER_CRITICAL(cpu_sr);
    cpu_sr = hal_spin_lock_irqsave(&efuse_lock);

#ifdef EFUSE_HV_SWITCH
    hal_writel(0x1, (unsigned long)EFUSE_HV_SWITCH);
#endif
    hal_writel(key_value, SID_PRKEY);
    reg_val = hal_readl((unsigned long)SID_PRCTL);
    reg_val &= ~((0x1ff<<16)|0x3);
    reg_val |= key_index<<16;
    hal_writel(reg_val, (unsigned long)SID_PRCTL);
    reg_val &= ~((0xff<<8)|0x3);
    reg_val |= (SID_OP_LOCK<<8) | 0x1;
    hal_writel(reg_val, (unsigned long)SID_PRCTL);
    while(hal_readl((unsigned long)SID_PRCTL)&0x1){};
    reg_val &= ~((0x1ff<<16)|(0xff<<8)|0x3);
    hal_writel(reg_val, (unsigned long)SID_PRCTL);

#ifdef EFUSE_HV_SWITCH
    hal_writel(0x0, (unsigned long)EFUSE_HV_SWITCH);
#endif
    hal_spin_unlock_irqrestore(&efuse_lock, cpu_sr);
//  taskEXIT_CRITICAL(cpu_sr);
    return ;
}

static int _get_burned_flag(efuse_key_map_new_t *key_map)
{
    if(key_map->burned_flg_offset < 0)
    {
        EFUSE_DBG("_get_burned_flag offset:%d\n", key_map->burned_flg_offset);
        return 0;
    }
    else
    {
        EFUSE_DBG("_get_burned_flag val:%d\n", _efuse_reg_read_key(EFUSE_WRITE_PROTECT));
        return (_efuse_reg_read_key(EFUSE_WRITE_PROTECT)
               >> (key_map->burned_flg_offset & EFUSE_BRUN_RD_OFFSET_MASK)) & 1;
    }
}

static int _sw_acl_ck(efuse_key_map_new_t *key_map,int burn)
{
    if(key_map->sw_rule == EFUSE_PRIVATE)
    {
        EFUSE_DBG("\n[efuse]%s: PRIVATE\n",key_map->name);
        return EFUSE_ERR_PRIVATE;
    }
    if(burn==0)
    {
        if(key_map->sw_rule == EFUSE_NACCESS)
        {
            EFUSE_DBG("\n[efuse]%s:NACCESS\n",key_map->name);
            return EFUSE_ERR_NO_ACCESS;
        }
    }
    else
    {
        /*If already burned:*/
        if(_get_burned_flag(key_map))
        {
            EFUSE_DBG("\n[efuse]%s: already burned\n",key_map->name);
            EFUSE_DBG("config reg:0x%x\n",efuse_sram_read_key(EFUSE_WRITE_PROTECT));
            if(key_map->sw_rule == EFUSE_NACCESS)
                return EFUSE_ERR_NO_ACCESS;
            return EFUSE_ERR_ALREADY_BURNED;
        }
        if(key_map->sw_rule == EFUSE_RW)
        {
            /*modify burned_flg_offset&&rd_fbd_offset in case of the config bits been burned*/
            key_map->burned_flg_offset |= EFUSE_ACL_SET_BRUN_BIT;
            key_map->rd_fbd_offset |= EFUSE_ACL_SET_RD_FORBID_BIT;
        }
        else if(key_map->sw_rule == EFUSE_RO)
        {
            /*modify rd_fbd_offset in case of the config bit been burned*/
            key_map->rd_fbd_offset |= EFUSE_ACL_SET_RD_FORBID_BIT;
        }
    }
    return 0;
}


uint efuse_sram_read_key(uint key_index)
{
    return hal_readl((unsigned long)EFUSE_SRAM + key_index);
}


/*Please reference 1728 spec page11 to know why to call _efuse_reg_read_key
* but efuse_sram_read_key
*burn efuse :efuse sram can not get the latest value
*unless via sid read or reboot.
*/
int efuse_uni_burn_key(uint key_index, uint key_value)
{
    #define EFUSE_BURN_MAX_TRY_CNT 3
    uint key_burn_bitmask = ~(efuse_sram_read_key(key_index)) & key_value;
    int fail = 0;

    while(key_burn_bitmask)
    {
        _efuse_program_key(key_index,key_burn_bitmask);

        if(fail > EFUSE_BURN_MAX_TRY_CNT)
        {
            EFUSE_DBG("%s: **failed **",
            __func__);
            #if EFUSE_DBG_E
            g_err_flg++;
            #endif
            return -1;
        }
        key_burn_bitmask &= (~(_efuse_reg_read_key(key_index)));
        fail++;
    }
    return 0;
}


void efuse_set_cfg_flg(int efuse_cfg_base,int bit_offset)
{
    if(efuse_uni_burn_key(efuse_cfg_base,(1<<bit_offset)))
    {
        EFUSE_DBG("[efuse] %s %d fatal err: **_set_cfg_flg [base:%d][offset:%d] **",
        __FILE__,__LINE__,efuse_cfg_base,bit_offset);
    }
    return;
}



/*Efuse access control rule check.*/
int efuse_acl_ck(efuse_key_map_new_t *key_map,int burn)
{
    /*For normal solution only check EFUSE_PRIVATE,other will be seemed as EFUSE_RW */
    if(hal_efuse_get_security_mode() == 0)
    {
        if(key_map->sw_rule == EFUSE_PRIVATE)
        {
            return EFUSE_ERR_PRIVATE;
        }
        return 0;
    }

    int ret = _sw_acl_ck(key_map,burn);
    if(ret)
    {
        EFUSE_DBG("[efuse]%s sw check failed\n",key_map->name);
        return ret;
    }
    if(burn)
    {
        EFUSE_DBG("[efuse]burn %s burned bit check begin\n",key_map->name);
        if(_get_burned_flag(key_map))
        {
            /*already burned*/
            EFUSE_DBG("[efuse]%s:already burned\n",key_map->name);
            EFUSE_DBG("config reg:0x%x\n",efuse_sram_read_key(EFUSE_WRITE_PROTECT));
            return EFUSE_ERR_ALREADY_BURNED;
        }
        EFUSE_DBG("[efuse]burn %s burned bit check end\n",key_map->name);
    }
    else
    {
        if((key_map->rd_fbd_offset>=0)&&
         ((efuse_sram_read_key(EFUSE_READ_PROTECT) >>
           (key_map->rd_fbd_offset & EFUSE_BRUN_RD_OFFSET_MASK)) & 1))
        {
            /*Read is not allowed because of the read forbidden bit was set*/
            EFUSE_DBG("[efuse]%s forbid bit set\n",key_map->name);
            EFUSE_DBG("config reg:0x%x\n",efuse_sram_read_key(EFUSE_READ_PROTECT));
            return EFUSE_ERR_READ_FORBID;
        }

    }
    return 0;
}

efuse_key_map_new_t *efuse_search_key_by_name(const char *key_name)
{
    efuse_key_map_new_t *key_map = g_key_info;

    for (; key_map->size != 0; key_map++) {
        if (strlen(key_map->name) != strlen(key_name)) {
            continue;
        }
        if (!memcmp(key_name, key_map->name, strlen(key_map->name))) {
            break;
        }
    }
    return key_map;
}

