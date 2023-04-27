#include "bl808_uhs_phy.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "psram_uhs_reg.h"
#include "glb_reg.h"
#include "pds_reg.h"

#define bl808_DBG_RF (0)    // 0 is for commit with only err log, 1 is for all debug log, 2 is for key debug log
#if bl808_DBG_RF == 1
    #define uhs_phy_printf_debug printf  // debug mode
    #define uhs_phy_printf printf 
    #define uhs_phy_printfe printf
#elif bl808_DBG_RF == 2
    #define uhs_phy_printf_debug(...)
    #define uhs_phy_printf printf  // commit it out in release version, use to collect data
    // #define uhs_phy_printf(...) //  used in release version
    #define uhs_phy_printfe printf
#else
    #define uhs_phy_printf_debug(...)
    #define uhs_phy_printf(...)
    #define uhs_phy_printfe(...)
#endif

#define ODT_EN (0)
// #define PSRAM_32MB (0)
#define CACHE_EN (0)        // unused !

static uhs_phy_cal_res_struct cal_res;
uhs_phy_cal_res_struct* uhs_phy_cal_res = &cal_res;
static uint8_t err_flag = 0;
#define CHECK_ERR_FLAG(func,args) {\
    func args;\
    if(err_flag)return err_flag;\
}

static uint32_t cache_state = 0;
static uint8_t uhs_latency_code = 1;
static uint32_t dqs_dq_delta = 0;
static uint32_t dcache_original = 0;
static uint32_t dcache_current = 0;
static uint32_t dcache_end = 0;
static uint8_t regr_done_err = 0;
static uint8_t reg_read_err = 0;
static uint8_t reg_write_err = 0;
static uint8_t init_array_write_err = 0;
static uint8_t array_read_err = 0;
static uint32_t addr_dump = 0x3000F000;
// 
static uint32_t addr_rarray = 0x50000000;
static uint32_t data0_rarray = 0x12345678;
static uint32_t data1_rarray = 0x87654321;
// uint32_t datarate_glb;
static uint32_t latency_wr[2] = {9,30};
static PSRAM_UHS_Cfg_Type *cfg_glb;
// static uint32_t addr_sr[3] = {0x3000f014,0x3000f018,0x3000f020};
// static uint32_t val_sr[3] = {0x0,0x0,0x0};
static uint32_t latency_wr_2kM[2] = {13,41};
static uint8_t cal_done_flag = 0;
static uint8_t print_flag = 0;
// static uint32_t latency_wr_2kM_init[2] = {13,36};
static uint8_t flag_ck1 = 0;
static uint8_t flag_ck2 = 0;

void set_uhs_latency_w(uint32_t uhs_latency);
void set_uhs_latency_r(uint32_t uhs_latency);
void uhs_reset(uint8_t ma_rb);
void uhs_phy_reg_dump(void);
void set_or_uhs(void);
uint8_t mr_read_back(void);
uint8_t uhs_phy_init_core(PSRAM_UHS_Cfg_Type *cfg);

void uhs_phy_delay_us(uint32_t us)
{
    arch_delay_us(us);
}

void uhs_phy_delay_ms(uint32_t ms)
{
    arch_delay_ms(ms);
}

void uhs_phy_af_reg(uint32_t REG_PCK_T_DIV,uint32_t REG_WIN_CYCLE,uint32_t REG_WIN_REF_CNT,uint32_t REG_REFI_CYCLE,uint32_t REG_BUST_CYCLE)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_MANUAL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_PCK_T_DIV,REG_PCK_T_DIV);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_MANUAL,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_WIN_CYCLE,REG_WIN_CYCLE);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_1,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_WIN_REF_CNT,REG_WIN_REF_CNT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_REFI_CYCLE,REG_REFI_CYCLE);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_2,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_BUST_CYCLE,REG_BUST_CYCLE);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_4,tmpVal);
    // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_AF_EN,0x1);
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
}

void uhs_phy_af_onoff(uint8_t onoff){
    uint32_t tmpVal = 0;

    if(onoff){
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_AF_EN,0x1);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
        uhs_phy_delay_us(50);
        // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_INIT_EN,0x1);
        // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
        // uhs_phy_delay_us(50);
    }else{
        // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_INIT_EN,0x0);
        // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
        // uhs_phy_delay_us(50);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_AF_EN,0x0);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
        uhs_phy_delay_us(50);
    }
}

void uhs_phy_af_cfg(void)
{
    // uint32_t tmpVal = 0;

    uhs_phy_af_onoff(0);

    if(cfg_glb->psramMemSize == PSRAM_MEM_SIZE_64MB && cfg_glb->isHighTem == PSRAM_UHS_HIGH_TEMP){
        if(cfg_glb->pck_freq == 2000){
            uhs_phy_af_reg(0x4,0xF423F,0x2000,0x79,0x6);
        }
        else if(cfg_glb->pck_freq == 1900){
            uhs_phy_af_reg(0x4,0xE7EEF,0x2000,0x72,0x6);
        }
        else if(cfg_glb->pck_freq == 1800){
            uhs_phy_af_reg(0x4,0xDBB9F,0x2000,0x6C,0x6);
        }
        else if(cfg_glb->pck_freq == 1700){
            uhs_phy_af_reg(0x4,0xCF84F,0x2000,0x66,0x5);
        }
        else if(cfg_glb->pck_freq == 1600){
            uhs_phy_af_reg(0x4,0xC34FF,0x2000,0x60,0x5);
        }
        else if(cfg_glb->pck_freq == 1500){
            uhs_phy_af_reg(0x4,0xB71AF,0x2000,0x5A,0x5);
        }
        else if(cfg_glb->pck_freq == 1400){
            uhs_phy_af_reg(0x4,0xAAE5F,0x2000,0x54,0x4);
        }
        else if(cfg_glb->pck_freq == 1300){
            uhs_phy_af_reg(0x4,0x9EB0F,0x2000,0x4E,0x4);
        }
        else if(cfg_glb->pck_freq == 1200){
            uhs_phy_af_reg(0x4,0x927BF,0x2000,0x48,0x4);
        }
        else if(cfg_glb->pck_freq == 1100){
            uhs_phy_af_reg(0x4,0x8646F,0x2000,0x42,0x4);
        }
        else if(cfg_glb->pck_freq == 1000){
            uhs_phy_af_reg(0x4,0x7A11F,0x2000,0x3C,0x3);
        }
        else if(cfg_glb->pck_freq == 900){
            uhs_phy_af_reg(0x4,0x6DDCF,0x2000,0x35,0x3);
        }
        else{
            uhs_phy_af_reg(0x4,0x61A7F,0x2000,0x2F,0x3);
        }
    }
    else if(cfg_glb->psramMemSize == PSRAM_MEM_SIZE_64MB){
        if(cfg_glb->pck_freq == 2000){
            uhs_phy_af_reg(0x4,0x1E847F,0x2000,0xF3,0x6);
        }
        else if(cfg_glb->pck_freq == 1900){
            uhs_phy_af_reg(0x4,0x1CFDDF,0x2000,0xE6,0x6);
        }
        else if(cfg_glb->pck_freq == 1800){
            uhs_phy_af_reg(0x4,0x1B773F,0x2000,0xDA,0x6);
        }
        else if(cfg_glb->pck_freq == 1700){
            uhs_phy_af_reg(0x4,0x19F09F,0x2000,0xCE,0x5);
        }
        else if(cfg_glb->pck_freq == 1600){
            uhs_phy_af_reg(0x4,0x1869FF,0x2000,0xC2,0x5);
        }
        else if(cfg_glb->pck_freq == 1500){
            uhs_phy_af_reg(0x4,0x16E35F,0x2000,0xB6,0x5);
        }
        else if(cfg_glb->pck_freq == 1400){
            uhs_phy_af_reg(0x4,0x155CBF,0x2000,0xA9,0x4);
        }
        else if(cfg_glb->pck_freq == 1300){
            uhs_phy_af_reg(0x4,0x13D61F,0x2000,0x9D,0x4);
        }
        else if(cfg_glb->pck_freq == 1200){
            uhs_phy_af_reg(0x4,0x124F7F,0x2000,0x91,0x4);
        }
        else if(cfg_glb->pck_freq == 1100){
            uhs_phy_af_reg(0x4,0x10C8DF,0x2000,0x85,0x4);
        }
        else if(cfg_glb->pck_freq == 1000){
            uhs_phy_af_reg(0x4,0xF423F,0x2000,0x79,0x3);
        }
        else if(cfg_glb->pck_freq == 900){
            uhs_phy_af_reg(0x4,0xDBB9F,0x2000,0x6C,0x3);
        }
        else{
            uhs_phy_af_reg(0x4,0xC34FF,0x2000,0x60,0x3);
        }
    }
    else if(cfg_glb->psramMemSize == PSRAM_MEM_SIZE_32MB && cfg_glb->isHighTem == PSRAM_UHS_HIGH_TEMP){
        if(cfg_glb->pck_freq == 2000){
            uhs_phy_af_reg(0x4,0xF423F,0x1000,0xF3,0x6);
        }
        else if(cfg_glb->pck_freq == 1900){
            uhs_phy_af_reg(0x4,0xE7EEF,0x1000,0xE6,0x6);
        }
        else if(cfg_glb->pck_freq == 1800){
            uhs_phy_af_reg(0x4,0xDBB9F,0x1000,0xDA,0x6);
        }
        else if(cfg_glb->pck_freq == 1700){
            uhs_phy_af_reg(0x4,0xCF84F,0x1000,0xCE,0x5);
        }
        else if(cfg_glb->pck_freq == 1600){
            uhs_phy_af_reg(0x4,0xC34FF,0x1000,0xC2,0x5);
        }
        else if(cfg_glb->pck_freq == 1500){
            uhs_phy_af_reg(0x4,0xB71AF,0x1000,0xB6,0x5);
        }
        else if(cfg_glb->pck_freq == 1400){
            uhs_phy_af_reg(0x4,0xAAE5F,0x1000,0xA9,0x4);
        }
        else if(cfg_glb->pck_freq == 1300){
            uhs_phy_af_reg(0x4,0x9EB0F,0x1000,0x9D,0x4);
        }
        else if(cfg_glb->pck_freq == 1200){
            uhs_phy_af_reg(0x4,0x927BF,0x1000,0x91,0x4);
        }
        else if(cfg_glb->pck_freq == 1100){
            uhs_phy_af_reg(0x4,0x8646F,0x1000,0x85,0x4);
        }
        else if(cfg_glb->pck_freq == 1000){
            uhs_phy_af_reg(0x4,0x7A11F,0x1000,0x79,0x3);
        }
        else if(cfg_glb->pck_freq == 900){
            uhs_phy_af_reg(0x4,0x6DDCF,0x1000,0x6C,0x3);
        }
        else{
            uhs_phy_af_reg(0x4,0x61A7F,0x1000,0x60,0x3);
        }
    }
    else{
        if(cfg_glb->pck_freq == 2000){
            uhs_phy_af_reg(0x4,0x1E847F,0x1000,0x1E7,0x6);
        }
        else if(cfg_glb->pck_freq == 1900){
            uhs_phy_af_reg(0x4,0x1CFDDF,0x1000,0x1CE,0x6);
        }
        else if(cfg_glb->pck_freq == 1800){
            uhs_phy_af_reg(0x4,0x1B773F,0x1000,0x1B6,0x6);
        }
        else if(cfg_glb->pck_freq == 1700){
            uhs_phy_af_reg(0x4,0x19F09F,0x1000,0x19E,0x5);
        }
        else if(cfg_glb->pck_freq == 1600){
            uhs_phy_af_reg(0x4,0x1869FF,0x1000,0x185,0x5);
        }
        else if(cfg_glb->pck_freq == 1500){
            uhs_phy_af_reg(0x4,0x16E35F,0x1000,0x16D,0x5);
        }
        else if(cfg_glb->pck_freq == 1400){
            uhs_phy_af_reg(0x4,0x155CBF,0x1000,0x154,0x4);
        }
        else if(cfg_glb->pck_freq == 1300){
            uhs_phy_af_reg(0x4,0x13D61F,0x1000,0x13C,0x4);
        }
        else if(cfg_glb->pck_freq == 1200){
            uhs_phy_af_reg(0x4,0x124F7F,0x1000,0x123,0x4);
        }
        else if(cfg_glb->pck_freq == 1100){
            uhs_phy_af_reg(0x4,0x10C8DF,0x1000,0x10B,0x4);
        }
        else if(cfg_glb->pck_freq == 1000){
            uhs_phy_af_reg(0x4,0xF423F,0x1000,0xF3,0x3);
        }
        else if(cfg_glb->pck_freq == 900){
            uhs_phy_af_reg(0x4,0xDBB9F,0x1000,0xDA,0x3);
        }
        else{
            uhs_phy_af_reg(0x4,0xC34FF,0x1000,0xC2,0x3);
        }
    }

    uhs_phy_af_onoff(1);
}

void Psram_UHS_Init_Override(PSRAM_UHS_Cfg_Type *cfg){
    uint32_t tmpVal = 0;

    Psram_UHS_Init(cfg);
    if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_32MB){
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PSRAM_TYPE,0x1);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48,tmpVal);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_ADDRMB_MSK,0x1f); // 3F -> 512Mb psram, 1F -> 256Mb psram
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
    }else if(cfg_glb->psramMemSize == PSRAM_MEM_SIZE_64MB){
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PSRAM_TYPE,0x2);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48,tmpVal);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_ADDRMB_MSK,0x3f); // 3F -> 512Mb psram, 1F -> 256Mb psram
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
    }

    #if CAL_MODE == 1
    uhs_phy_af_cfg();
    #endif

    set_or_uhs();

    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_LDO12UHS_VOUT_SEL, 5);
    BL_WR_REG(GLB_BASE, GLB_LDO12UHS, tmpVal);
    uhs_phy_printf("GLB_LDO12UHS: %lx\r\n",tmpVal);
    uhs_phy_delay_us(250);
}

void power_up_mm(uint8_t off)
{
    uint32_t tmpVal = 0;
    if (off == 0)
    {
        // power up MM domain
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_PWR_OFF,off);
        BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
        uhs_phy_delay_us(150);
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_ISO_EN,off);
        BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
        uhs_phy_delay_us(10);
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_GATE_CLK,off);
        BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
        uhs_phy_delay_us(10);
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_MEM_STBY,off);
        BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
        uhs_phy_delay_us(10);
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_PDS_RST,off);
        BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
        // uhs_phy_delay_us(10);
        // uhs_phy_delay_ms(1);
    }
    else
    {
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_ISO_EN,off);
        BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
        uhs_phy_delay_us(10);
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_GATE_CLK,off);
        BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
        uhs_phy_delay_us(10);
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_MEM_STBY,off);
        BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
        uhs_phy_delay_us(10);
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_PDS_RST,off);
        BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
        uhs_phy_delay_us(150);
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_PWR_OFF,off);
        BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
    }
    uhs_phy_delay_us(100);
}

void power_up_uhspll(void)
{
    // power_up_uhspll
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_UHSPLL_SFREG,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_UHSPLL,0x1);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);
    uhs_phy_delay_us(10);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_SDM_RSTB,0x0);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);
    uhs_phy_delay_us(50);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_SDM_RSTB,0x1);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);
    uhs_phy_delay_us(50);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_FBDV_RSTB,0x0);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);
    uhs_phy_delay_us(50);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_FBDV_RSTB,0x1);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);
    uhs_phy_delay_us(50);
}

void power_up_ldo12uhs(void)
{
    // use internal LDO 
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(GLB_BASE,GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_LDO12UHS,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_LDO12UHS_VOUT_SEL,0x5);
    BL_WR_REG(GLB_BASE,GLB_LDO12UHS,tmpVal);
    uhs_phy_delay_us(200);
    // use external LDO
    // tmpVal = BL_RD_REG(GLB_BASE,GLB_LDO12UHS);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_LDO12UHS_PULLDOWN,0x0);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_LDO12UHS_PULLDOWN_SEL,0x1);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_LDO12UHS,0x0);
    // BL_WR_REG(GLB_BASE,GLB_LDO12UHS,tmpVal);
}

void set_cen_ck_ckn(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ_OE_MID_N_REG,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ_OE_MID_P_REG,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50,tmpVal);
    uhs_phy_delay_us(10);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY1,0xfc);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY0,0x1);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40,tmpVal);
    uhs_phy_delay_us(10);
}

void set_or_uhs(void)
{
    uint32_t tmpVal = 0;
    
    if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_32MB){
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PSRAM_TYPE,0x1);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48,tmpVal);
    }else if(cfg_glb->psramMemSize == PSRAM_MEM_SIZE_64MB){
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PSRAM_TYPE,0x2);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48,tmpVal);
    }
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_4C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_ODT_SEL_HW,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_4C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_ODT_SEL,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_VREF_MODE,0x1);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_CEN_DLY_DRV,0x8);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_CK_DLY_DRV,0xB);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_04);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DM0_DLY_DRV,0x7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DM1_DLY_DRV,0x7);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_04,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_24);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ15_DLY_DRV,0x7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ14_DLY_DRV,0x7);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_24,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_20);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ13_DLY_DRV,0x7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ12_DLY_DRV,0x7);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_20,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_1C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ11_DLY_DRV,0x7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ10_DLY_DRV,0x7);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_1C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_18);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ9_DLY_DRV,0x7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ8_DLY_DRV,0x7);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_18,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_14);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ7_DLY_DRV,0x7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ6_DLY_DRV,0x7);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_14,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ5_DLY_DRV,0x7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ4_DLY_DRV,0x7);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_10,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_0C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ3_DLY_DRV,0x7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ2_DLY_DRV,0x7);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_0C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ1_DLY_DRV,0x7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ0_DLY_DRV,0x7);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS0_DLY_DRV,0x6);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS1_DLY_DRV,0x6);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_OE_TIMER,0x3);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_CEN_SR,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_CK_SR,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_04);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DM1_SR,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DM0_SR,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_04,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_24);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ15_SR,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ14_SR,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_24,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_20);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ13_SR,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ12_SR,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_20,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_1C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ11_SR,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ10_SR,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_1C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_18);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ9_SR,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ8_SR,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_18,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_14);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ7_SR,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ6_SR,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_14,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ5_SR,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ4_SR,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_10,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_0C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ3_SR,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ2_SR,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_0C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ1_SR,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ0_SR,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ_OE_DN_P_REG,0x3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ_OE_DN_N_REG,0x3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ_OE_UP_P_REG,0x3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ_OE_UP_N_REG,0x3);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_24);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ15_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ14_DLY_RX,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_24,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_20);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ13_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ12_DLY_RX,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_20,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_1C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ11_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ10_DLY_RX,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_1C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_18);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ9_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ8_DLY_RX,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_18,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_14);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ7_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ6_DLY_RX,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_14,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ5_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ4_DLY_RX,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_10,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_0C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ3_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ2_DLY_RX,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_0C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ1_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ0_DLY_RX,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS0_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS0N_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS0_DIFF_DLY_RX,0x3);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS1_DLY_RX,0x0); 
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS1N_DLY_RX,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS1_DIFF_DLY_RX,0x3);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C,tmpVal);
    uhs_phy_delay_us(200);
}

void switch_to_ldo12uhs(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY1,0xcc);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40,tmpVal);
    uhs_phy_delay_us(200);
}

void release_cen_ck_ckn(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY1,0xcf);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY0,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40,tmpVal);
    uhs_phy_delay_us(10);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ_OE_MID_P_REG,0x3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ_OE_MID_N_REG,0x3);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50,tmpVal);
    uhs_phy_delay_us(10);
}

void uhs_phy_pwr_down(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(GLB_BASE,GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_LDO12UHS_PULLDOWN_SEL,0x0);
    BL_WR_REG(GLB_BASE,GLB_LDO12UHS,tmpVal);
    uhs_phy_delay_us(100);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_LDO12UHS,0x0);
    BL_WR_REG(GLB_BASE,GLB_LDO12UHS,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY1,0xff);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40,tmpVal);
    uhs_phy_delay_us(100);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_UHSPLL_SFREG,0x0);
    BL_WR_REG(GLB_BASE,GLB_LDO12UHS,tmpVal);
    uhs_phy_delay_us(100);
}

void psram_init(void)
{
    uint8_t i;
    uint32_t tmpVal = 0;
    for (i = 0; i < 1; i++){
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        // if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_32MB){
        //     tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_ADDRMB_MSK,0x1f); // 3F -> 512Mb psram, 1F -> 256Mb psram
        // }else if(cfg_glb->psramMemSize == PSRAM_MEM_SIZE_64MB){
        //     tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_ADDRMB_MSK,0x3f); // 3F -> 512Mb psram, 1F -> 256Mb psram
        // }
        // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_LINEAR_BND_B,0xb);
        // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_INIT_EN,0x1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x1);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
        uhs_phy_delay_us(10);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_GLBR_PULSE,0x1);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD,tmpVal);
        uhs_phy_delay_us(100);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x0);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
        uhs_phy_delay_us(100);
    }

    // // psram auto refresh at 2000Mbps
    // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_1);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_WIN_CYCLE,0x001E0C4);
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_1,tmpVal);
    // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_2);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_WIN_REF_CNT,0x1007);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_REFI_CYCLE,0x01d);
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_2,tmpVal);
    // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_4);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_BUST_CYCLE,0x1);
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_4,tmpVal);
    // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_MANUAL);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_PCK_T_DIV,0x40);
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_MANUAL,tmpVal);
    // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_AF_EN,0x1);
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);

    // // psram cmd timing < 2000Mbps
    // BL_WR_WORD(0x3000F030,0x18090610);
}

void set_uhs_phy_init(void)
{
    // set phy & controller
    uint32_t tmpVal = 0;
    // default latency(800MHz)
    // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_ANA,0x2);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_DIG,0x7);
    // // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_ANA,0x0);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_ANA,0x1);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_DIG,0x2);
    // // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_DQ_ANA,0x1);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_DQ_ANA,0x2);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_DQ_DIG,0x2);
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_ODT_SEL,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_OE_CTRL_HW,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_VREF_MODE,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_OE_TIMER,0x3);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
    if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_32MB){
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_34,0x05000501);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_38,0x02080108);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_3C,0x03e90b0b);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_44,0x040b0308);
    }else if(cfg_glb->psramMemSize == PSRAM_MEM_SIZE_64MB){
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_34,0x09020303);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_38,0x040c0313);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_3C,0x07d11515);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_44,0x060f050c);
    }
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_CEN_ANA,0x1);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50,tmpVal);
    uhs_phy_delay_us(100);
}

void set_uhs_phy(void)
{
    uint32_t tmpVal = 0;
    // set phy & controller
    // latency code=3 (1066MHz)
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,0x0f0a1323);  // if fail than use 0x0f391323 
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,0x0f0a0313); // tDQSS -> -1
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,0x0f0a3233); // tDQSS -> 1
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_ODT_SEL,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_OE_CTRL_HW,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_VREF_MODE,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_OE_TIMER,0x3);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
    set_uhs_latency_w(latency_wr[0]);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_34,0x0b030404);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_38,0x050e0418);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_3C,0x0a6a1c1c);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_44,0x07110710);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50,0x01333333);

    uhs_phy_delay_us(100);
} 

uint8_t uhs_err_handler(uint8_t err)
{
    err_flag = 1;
    uhs_phy_cal_res->err_type = err;
#ifndef BFLB_BOOT2
    switch (err) {
        case UHS_REGR_GNT_ERR:
            uhs_phy_printfe("UHS_REGR_GNT_ERR\r\n");
            break;
        case UHS_REGR_DONE_ERR:
            uhs_phy_printfe("UHS_REGR_DONE_ERR = %d\r\n",regr_done_err);
            uhs_phy_cal_res->err_sub_type = regr_done_err;
            break;
        case UHS_REGW_GNT_ERR:
            uhs_phy_printfe("UHS_REGW_GNT_ERR\r\n");
            break;            
        case UHS_REGW_DONE_ERR:
            uhs_phy_printfe("UHS_REGW_DONE_ERR\r\n");
            break;
        case UHS_LATENCY_CODE_WRITE_ERR:
            uhs_phy_printfe("UHS_LATENCY_CODE_WRITE_ERR\r\n");
            break;
        case UHS_INIT_ARRAY_WRITE_ERR:
            uhs_phy_printfe("UHS_INIT_ARRAY_WRITE_ERR = %d\r\n",init_array_write_err);
            uhs_phy_cal_res->err_sub_type = init_array_write_err;
            break;         
        case UHS_REG_READ_CAL_ERR:
            uhs_phy_printfe("UHS_REG_READ_CAL_ERR = %d\r\n",reg_read_err);
            uhs_phy_cal_res->err_sub_type = reg_read_err;
            break;
        case UHS_REG_WRITE_CAL_ERR:
            uhs_phy_printfe("UHS_REG_WRITE_CAL_ERR = %d\r\n",reg_write_err);
            uhs_phy_cal_res->err_sub_type = reg_write_err;
            break;
        case UHS_ARRAY_READ_LAT_ERR:
            uhs_phy_printfe("UHS_ARRAY_READ_LAT_ERR = %d\r\n",array_read_err);
            uhs_phy_cal_res->err_sub_type = array_read_err;
            break;
        case UHS_ARRAY_WRITE_CK_ERR:
            uhs_phy_printfe("UHS_ARRAY_WRITE_CK_ERR\r\n");
            break;
        case UHS_ARRAY_READ_CAL_ERR:
            uhs_phy_printfe("UHS_ARRAY_READ_CAL_ERR\r\n");
            break;
        case UHS_ARRAY_WRITE_CAL_ERR:
            uhs_phy_printfe("UHS_ARRAY_WRITE_CAL_ERR\r\n");
            break;
        case UHS_CACHE_ENABLE_ERR:
            uhs_phy_printfe("UHS_CACHE_ENABLE_ERR\r\n");
            break;
        case UHS_CACHE_DISABLE_ERR:
            uhs_phy_printfe("UHS_CACHE_DISABLE_ERR\r\n");
            break;
        case UHS_CACHE_RECOVER_ERR:
            uhs_phy_printfe("UHS_CACHE_RECOVER_ERR\r\n");
            break;
        case UHS_REG_WRITE_2kM_ERR:
            uhs_phy_printfe("UHS_REG_WRITE_2kM_ERR\r\n");
            break;
        case UHS_BAD_DIE_ERR:
            uhs_phy_printfe("UHS_BAD_DIE_ERR\r\n");
            break;
        case UHS_DIAGONAL_TEST_ERR:
            uhs_phy_printfe("UHS_DIAGONAL_TEST_ERR\r\n");
            break;
        case UHS_ALL_ADDR_TEST_ERR:
            uhs_phy_printfe("UHS_ALL_ADDR_TEST_ERR\r\n");
            break;
        default:
            break;
    }
    uhs_phy_printfe("ERR_AT %ldMbps\r\n",cfg_glb->pck_freq);
    uhs_phy_reg_dump();
#else
    uhs_phy_printfe("uhs_err_handler:%d\r\n",err);
#endif
    #if CAL_MODE == 0 || CAL_MODE == 1
    while(1){
        uhs_phy_printfe("%d",err);
        uhs_phy_delay_ms(10000);
    };
    #endif
    return err_flag;
}

void uhs_phy_reg_dump(void){
    uint32_t len = 0x150;
    uint32_t i = 0;

    // uhs_phy_printf_debug("UHS_PHY_REG_DUMP_START\r\n");
    // for(i = 0;i <= len;i = i+4){
    //     uhs_phy_printf_debug("0x%lx,0x%lx\r\n",(addr_dump + i),*((volatile uint32_t*)(addr_dump + i)));
    // }
    // uhs_phy_printf_debug("UHS_PHY_REG_DUMP_END\r\n");
    uhs_phy_printfe("UHS_PHY_REG_DUMP_START\r\n");
    for(i = 0;i <= len;i = i+4){
        uhs_phy_printfe("0x%lx,0x%lx\r\n",(addr_dump + i),*((volatile uint32_t*)(addr_dump + i)));
    }
    uhs_phy_printfe("UHS_PHY_REG_DUMP_END\r\n");
}

uint8_t uhs_reg_w(uint32_t uhs_latency,uint32_t uhs_drive,uint32_t ma,uint32_t BL_32)
{
    uint32_t tmpVal = 0;
    uint32_t count = 0;
    if(ma == 0)
    {
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_PSRAM_CONFIGURE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_LATENCY,uhs_latency);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DRIVE_ST,uhs_drive); 
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_PSRAM_CONFIGURE,tmpVal);
    }
    else if(ma == 2)
    {
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_PSRAM_CONFIGURE);
        if (BL_32 == 1){
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_64,0x1);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_32,0x1);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_16,0x0);
        }else if (BL_32 == 2){
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_64,0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_32,0x1);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_16,0x1);
        }else{
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_64,0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_32,0x0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_16,0x0);
        }  
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_PSRAM_CONFIGURE,tmpVal);
    }
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_MODE_REG,ma); //reg_mode_reg
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x1);  //reg_config_req
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
    // uhs_phy_printf_debug("reg_w GNT while\r\n");
    while (1)
    {
        if (count == 100000){
            return uhs_err_handler(UHS_REGW_GNT_ERR);
        }
        uhs_phy_delay_us(10);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_GNT);
        if (tmpVal == 1)
        {
            uhs_phy_printf_debug("reg_w GNT pass\r\n");
            break;
        }
        count ++;   
    }
    
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_REGW_PULSE,0x1);  //reg_regw_pulse
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD,tmpVal);

    count = 0;
    while (1)
    {
        if (count == 100000){
            return uhs_err_handler(UHS_REGW_DONE_ERR);
        }
        uhs_phy_delay_us(10);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_STS_REGW_DONE); //regw_done
        if (tmpVal == 1)
        {
            uhs_phy_printf_debug("reg_w DONE pass\r\n");
            break;
        }
        count ++;
    }
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x0);  //reg_config_req
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
    uhs_phy_delay_us(10);

    return 0;
}

uint8_t uhs_reg_r(uint32_t ma,uint8_t flag)
{
    uint32_t tmpVal = 0;
    // uint32_t tmpInd = 0;
    uint32_t count = 0;
    uint8_t opc = 1;

    if (flag == 1){
        uhs_phy_af_onoff(0);

        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_FORCE_FSM,0x1);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48,tmpVal);
        uhs_phy_delay_us(50);
    }

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_MODE_REG,ma); //reg_mode_reg
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x1);  //reg_config_req
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);

    while (1)
    {
        if (count == 100000){
            return uhs_err_handler(UHS_REGR_GNT_ERR);
        }
        uhs_phy_delay_us(10);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_GNT);
        if (tmpVal == 1)
        {
            uhs_phy_printf_debug("reg_r GNT pass\r\n");
            break;
        }
        count ++;
    }
    
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_REGR_PULSE,0x1);  //reg_regr_pulse
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD,tmpVal);

    count = 0;
    while (1)
    {
        if (flag == 1){
            if (count == 100){
                regr_done_err = 2;
                return uhs_err_handler(UHS_REGR_DONE_ERR);
            }
            uhs_phy_delay_us(20);
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_STS_REGR_DONE); //regr_done
            if (tmpVal == 1){
                uhs_phy_printf_debug("reg_r DONE pass\r\n");
                break;
            }
            count ++;

            // if (tmpVal == 1){
            //     uhs_phy_printf_debug("reg_r DONE pass\r\n");
            //     opc = 1;
            // }else{
            //     uhs_phy_printf_debug("reg_r DONE fail\r\n");
            //     opc = 0;
            // }
            // break;
        }
        else{
            if (count == 100000){
                regr_done_err = 1;
                return uhs_err_handler(UHS_REGR_DONE_ERR);
            }
            uhs_phy_delay_us(10);
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_STS_REGR_DONE); //regr_done
            if (tmpVal == 1){
                uhs_phy_printf_debug("reg_r DONE pass\r\n");
                break;
            }
            count ++;
        }         
    }

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x0);  //reg_config_req
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);

    if (opc == 0){
        uhs_reset(0);
    }

    if (flag == 1){
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_FORCE_FSM,0x0);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48,tmpVal);
        uhs_phy_delay_us(50);

        uhs_phy_af_onoff(1);
    }

    uhs_phy_delay_us(10);
    return opc;
}


void cfg_dq_rx(uint8_t dq){
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_24);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ15_DLY_RX,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ14_DLY_RX,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_24,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_20);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ13_DLY_RX,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ12_DLY_RX,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_20,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_1C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ11_DLY_RX,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ10_DLY_RX,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_1C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_18);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ9_DLY_RX,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ8_DLY_RX,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_18,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_14);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ7_DLY_RX,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ6_DLY_RX,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_14,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ5_DLY_RX,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ4_DLY_RX,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_10,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_0C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ3_DLY_RX,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ2_DLY_RX,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_0C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ1_DLY_RX,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ0_DLY_RX,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08,tmpVal);
    uhs_phy_delay_us(10);
}

void cfg_dqs_rx(uint8_t dqs){
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS0_DIFF_DLY_RX,dqs);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS1_DIFF_DLY_RX,dqs);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C,tmpVal);
    uhs_phy_delay_us(10);
}

void cfg_ck_cen_drv(uint8_t array_ck_dly_drv,uint8_t array_cen_dly_drv){
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_CK_DLY_DRV,array_ck_dly_drv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_CEN_DLY_DRV,array_cen_dly_drv);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00,tmpVal);
    uhs_phy_delay_us(50);
}

void uhs_reset(uint8_t ma_rb)
{
	// uint32_t tmpVal = 0;
    // uint32_t len = 0x150;
    // uint32_t val_sr[len>>2];
    // int32_t i = 0;

    uhs_phy_printf("IN_UHS_RESET\r\n");

    // for( i = len ; i >= 0 ; i = i-4 ){
    //     if( i != 0x4 ){
    //         val_sr[i>>2] = *((volatile uint32_t*)(addr_dump + i));
    //     }
    // }

    // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_AF_EN,0);
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
    // uhs_phy_delay_us(100);

	// tmpVal = BL_RD_WORD(0x30007044);
	// tmpVal = tmpVal | 0x00008000;
	// BL_WR_WORD(0x30007044,tmpVal);
	// uhs_phy_delay_us(100);
	// tmpVal = tmpVal & 0xFFFF7FFF;
	// BL_WR_WORD(0x30007044,tmpVal);
    // uhs_phy_delay_us(200);
	
	// BL_WR_WORD(0x3000F030,0x18090610);

	// #if PSRAM_32MB
    // PSRAM_UHS_Cfg_Type psramCfg = {
	// 	datarate,
	// 	PSRAM_MEM_SIZE_32MB,
	// 	PSRAM_PAGE_SIZE_2KB,
	// 	0,
    // };
    // #else
	// PSRAM_UHS_Cfg_Type psramCfg = {
	// 	datarate,
	// 	PSRAM_MEM_SIZE_64MB,
	// 	PSRAM_PAGE_SIZE_2KB,
	// 	0,
    // };
    // #endif
	// Psram_UHS_Init_Override(cfg_glb); //controller init
	
    // set_or_uhs();
	// set_uhs_phy();

    // for( i = len ; i >= 0 ; i = i-4 ){
    //     if( i != 0x4 ){
    //         *((volatile uint32_t*)(addr_dump + i)) = val_sr[i>>2];
    //     }
    // }
    // uhs_phy_delay_us(400);

    if (ma_rb){
        mr_read_back();
    }else{
        power_up_mm(1);
        uhs_phy_pwr_down();
        latency_wr_2kM[1] --;
        uhs_phy_init_core(cfg_glb);
    }

    uhs_phy_printf("OUT_UHS_RESET\r\n");
}

void set_uhs_latency_r(uint32_t uhs_latency)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_ANA,uhs_latency%4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_DIG,uhs_latency/4);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
    uhs_phy_delay_us(50);
}

void set_uhs_latency_w(uint32_t uhs_latency)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_ANA,uhs_latency%4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_DIG,uhs_latency/4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_DQ_ANA,(uhs_latency+1)%4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_DQ_DIG,(uhs_latency+1)/4);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
    uhs_phy_delay_us(50);
}

uint8_t mr_read_back(void)
{
    uint8_t cnt1;
    uint32_t tmpVal;
    for (cnt1=0;cnt1<=4;cnt1++){
        if(cnt1 != 3){
            CHECK_ERR_FLAG(uhs_reg_r,(cnt1,0));
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
            uhs_phy_printf("MA%d = 0x%lx\r\n",cnt1,tmpVal);
        }
    }
    return 0;
}

uint8_t reg_read_cal(void)
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal_1 = 1;
    uint32_t uhs_latency = 42;
    int32_t i = 0;
    uint8_t dqs_dq_flag = 0;
    uint32_t reg_dqs = 0;
    uint32_t reg_dq = 0;

    // for(uhs_latency = 41; uhs_latency > 0; uhs_latency --)
    for(uhs_latency = latency_wr_2kM[1]; uhs_latency > 0; uhs_latency --)
    {
        if(uhs_latency == 34)
        {
            reg_read_err = 1;
            return uhs_err_handler(UHS_REG_READ_CAL_ERR);
        }
        uhs_phy_printf_debug("reg read cal 1st by latency= %ld\r\n",uhs_latency);
        set_uhs_latency_r(uhs_latency);
    
        // sweep dqs
        cfg_dq_rx(0);
        for(i = 15; i >= 0; i --)
        {
            cfg_dqs_rx(i);
            // tmpVal_1 = uhs_reg_r(0,1);
            CHECK_ERR_FLAG(uhs_reg_r,(0,1));
            if (cal_done_flag == 1)
                return 0;
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
            uhs_phy_printf_debug("PSRAM_UHS_UHS_CMD>>24 1st dqs--, 0x%lx\r\n",tmpVal);
            if(tmpVal == ((2<<3)+uhs_latency_code) && (tmpVal_1 == 1)){
                uhs_phy_printf_debug("reg read pass by dqs= %ld\r\n",i); 
                // reg_dqs = i;
                dqs_dq_flag = 1;
                break;
            }              
            else{
                uhs_phy_printf_debug("reg read fail by dqs= %ld\r\n",i);
            }
			// if(tmpVal_1 == 0){
			// 	uhs_phy_printf_debug("read done not found!!!\r\n");
			// 	// uhs_reset(datarate);
			// 	set_uhs_latency_r(uhs_latency);
			// 	cfg_dq_rx(0);
			// }
        }

        // sweep dq 
        cfg_dqs_rx(0);
        for(i = 15; i >=0; i --)
        {
            cfg_dq_rx(i);
            // tmpVal_1 = uhs_reg_r(0,1);
            CHECK_ERR_FLAG(uhs_reg_r,(0,1));
            if (cal_done_flag == 1)
                return 0;
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
            uhs_phy_printf_debug("PSRAM_UHS_UHS_CMD>>24 1st dq--, 0x%lx\r\n",tmpVal);
            if(tmpVal == ((2<<3)+uhs_latency_code) && (tmpVal_1 == 1)){
                uhs_phy_printf_debug("reg read pass by dq= %ld\r\n",i);
                // reg_dq = i;
                dqs_dq_flag = 1;
                break; 
            }  
            else{
                uhs_phy_printf_debug("reg read fail by dq= %ld\r\n",i);
            }
			// if(tmpVal_1 == 0){
			// 	uhs_phy_printf_debug("read done not found!!!\r\n");
			// 	// uhs_reset(datarate);
			// 	set_uhs_latency_r(uhs_latency);
			// 	cfg_dqs_rx(0);
			// }
        }    
        if (dqs_dq_flag == 1){
            dqs_dq_flag = 0;

            uhs_latency = uhs_latency - 2;
            uhs_phy_printf_debug("reg read cal 2nd by latency= %ld\r\n",uhs_latency);
            set_uhs_latency_r(uhs_latency);  //got a good robust uhs_latency
            latency_wr[1] = uhs_latency;
            //******verify the uhs_latency and get dqs/dq timing
            //sweep dqs
            cfg_dq_rx(0);
            for(i = 15; i >= 0; i --)
            {
                cfg_dqs_rx(i);
                CHECK_ERR_FLAG(uhs_reg_r,(0,0));
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
                uhs_phy_printf_debug("PSRAM_UHS_UHS_CMD>>24 2nd dqs--, 0x%lx\r\n",tmpVal);
                if(tmpVal == ((2<<3)+uhs_latency_code))
                {
                    uhs_phy_printf("reg read pass by --dqs= %ld\r\n",i);
                    reg_dqs += i;
                    dqs_dq_flag = 1;
                    break;
                }
                else{
                    uhs_phy_printf_debug("reg read fail by dqs= %ld\r\n",i);
                }
            }
            for(i = 0; i <= 15; i ++)
            {
                cfg_dqs_rx(i);
                CHECK_ERR_FLAG(uhs_reg_r,(0,0));
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
                uhs_phy_printf_debug("PSRAM_UHS_UHS_CMD>>24 2nd dqs++, 0x%lx\r\n",tmpVal);
                if(tmpVal == ((2<<3)+uhs_latency_code))
                {
                    uhs_phy_printf("reg read pass by ++dqs= %ld\r\n",i);
                    reg_dqs += i;
                    dqs_dq_flag = 1;
                    break; 
                }
                else{
                    uhs_phy_printf_debug("reg read fail by dqs= %ld\r\n",i);
                }
            }
            // sweep dq 
            cfg_dqs_rx(0);
            for(i = 15; i >= 0; i --)
            {
                cfg_dq_rx(i);
                CHECK_ERR_FLAG(uhs_reg_r,(0,0));
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
                uhs_phy_printf_debug("PSRAM_UHS_UHS_CMD>>24 2nd dq--, 0x%lx\r\n",tmpVal);
                if(tmpVal == ((2<<3)+uhs_latency_code))
                {
                    uhs_phy_printf("reg read pass by --dq= %ld\r\n",i);
                    reg_dq += i;
                    dqs_dq_flag = 1;
                    break;
                }
                else{
                    uhs_phy_printf_debug("reg read fail by dq= %ld\r\n",i);
                }
            }
            for(i = 0; i <= 15; i ++)
            {
                cfg_dq_rx(i);
                CHECK_ERR_FLAG(uhs_reg_r,(0,0));
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
                uhs_phy_printf_debug("PSRAM_UHS_UHS_CMD>>24 2nd dq++, 0x%lx\r\n",tmpVal);
                if(tmpVal == ((2<<3)+uhs_latency_code))
                {
                    uhs_phy_printf("reg read pass by ++dq= %ld\r\n",i);
                    reg_dq += i;
                    dqs_dq_flag = 1;
                    break;
                }  
                else{
                    uhs_phy_printf_debug("reg read fail by dq= %ld\r\n",i);
                }
            }
            
            if(dqs_dq_flag == 0)
            {
                reg_read_err = 2;
                return uhs_err_handler(UHS_REG_READ_CAL_ERR);
            }

            if(reg_dqs >= reg_dq)
            {
                reg_dqs = (reg_dqs-reg_dq)/2;
                reg_dq = 0;
            }
            else
            {
                reg_dq = (reg_dq-reg_dqs)/2;
                reg_dqs = 0;
            }
            
            // set dqs & dq by register read calibration result 
            cfg_dqs_rx(reg_dqs);
            cfg_dq_rx(reg_dq);
            CHECK_ERR_FLAG(mr_read_back,());
            uhs_phy_printf("reg_read_cal pass, latency= %ld, dqs= %ld, dq= %ld\r\n",uhs_latency,reg_dqs,reg_dq);
            break;
        }
    }

    return 0;
}

void cfg_dq_drv(uint32_t dq){
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_04);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DM0_DLY_DRV,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DM1_DLY_DRV,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_04,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_24);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ15_DLY_DRV,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ14_DLY_DRV,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_24,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_20);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ13_DLY_DRV,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ12_DLY_DRV,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_20,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_1C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ11_DLY_DRV,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ10_DLY_DRV,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_1C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_18);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ9_DLY_DRV,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ8_DLY_DRV,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_18,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_14);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ7_DLY_DRV,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ6_DLY_DRV,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_14,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ5_DLY_DRV,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ4_DLY_DRV,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_10,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_0C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ3_DLY_DRV,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ2_DLY_DRV,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_0C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ1_DLY_DRV,dq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ0_DLY_DRV,dq);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08,tmpVal);
    // uhs_phy_delay_us(10);
}

void cfg_dqs_drv(uint32_t dqs){
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS0_DLY_DRV,dqs);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS1_DLY_DRV,dqs);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C,tmpVal);
    uhs_phy_delay_us(10);
}

uint8_t reg_write_cal(void)  //only need sweep dqs
{
    uint32_t tmpVal = 0;
    // uint32_t tmpVal_1 = 0;
    int32_t i = 0;
    uint32_t reg_dqs;
    uint32_t reg_dq = 0;
    uint32_t reg_dqs1 = 0;
    uint32_t reg_dqs2 = 0;
    uint8_t dqs_dq_flag1 = 0;
    uint8_t dqs_dq_flag2 = 0;
    // reg_write_err = 0;

    // sweep1 dqs
    for(i = 15; i >=0; i --)
    {
        cfg_dqs_drv(i); 
        CHECK_ERR_FLAG(uhs_reg_w,(uhs_latency_code,2,2,1)); //uhs_latency_code==3,uhs_drive==2,ma==2,BL_32==1
        CHECK_ERR_FLAG(uhs_reg_r,(2,0));
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
        if(tmpVal == (16 + 32))
            {
                uhs_phy_printf("reg write pass by -- dqs1= %ld\r\n",i); 
                reg_dqs1 = i;
                dqs_dq_flag1 = 1;
                break; 
            }              
        else{
            uhs_phy_printf_debug("reg write fail by -- dqs1= %ld\r\n",i);
        }
    }        
    // sweep2 dqs 
    for(i = 0; i <=15; i ++)
    {
        cfg_dqs_drv(i);
        CHECK_ERR_FLAG(uhs_reg_w,(uhs_latency_code,2,2,2));  //uhs_latency_code==3,uhs_drive==2,ma==2,BL_32==0,BL_64==1
        CHECK_ERR_FLAG(uhs_reg_r,(2,0));
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
        if(tmpVal == (8 + 16))
            {
                uhs_phy_printf("reg write pass by ++ dqs2= %ld\r\n",i);
                reg_dqs2 = i;
                dqs_dq_flag2 = 1;
                break; 
            }              
        else{
            uhs_phy_printf_debug("reg write fail by ++ dqs2= %ld\r\n",i);
        }
    }           

    if(dqs_dq_flag1 == 1 && dqs_dq_flag2 == 1){
        reg_dqs = (reg_dqs1 + reg_dqs2) / 2 ;
    }else if(dqs_dq_flag1 == 1 && dqs_dq_flag2 == 0){
        reg_dqs = reg_dqs1;
    }else if(dqs_dq_flag1 == 0 && dqs_dq_flag2 == 1){
        reg_dqs = reg_dqs2;
    }
    else{
        reg_write_err = 1;
        return uhs_err_handler(UHS_REG_WRITE_CAL_ERR);
    }

    // if ck_dly_drv = 4, fix reg_dqs to 0
	tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00);
	tmpVal = (tmpVal >> 16) & 0xF;
	if(tmpVal == 4){
		reg_dqs = 0;
	}
    // set dqs by register write cal result 
    cfg_dqs_drv(reg_dqs);
    CHECK_ERR_FLAG(uhs_reg_w,(uhs_latency_code,2,2,0)); //uhs_latency_code==3,uhs_drive==2,ma==2,BL_32==1
    CHECK_ERR_FLAG(uhs_reg_r,(2,0));
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
    if(tmpVal == 0){   
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08);
        reg_dq = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ0_DLY_DRV);
        uhs_phy_printf("reg write cal pass dqs= %ld, dq= %ld\r\n",reg_dqs,reg_dq);
    }              
    else{
        reg_write_err = 2;
        return uhs_err_handler(UHS_REG_WRITE_CAL_ERR);
    } 
    
    dqs_dq_delta = 16 + reg_dqs - reg_dq;
    uhs_phy_printf("reg_write_cal return dqs_dq_delta= %ld\r\n",dqs_dq_delta);

    return 0;
}

void array_write_fix(uint32_t addr,uint32_t len,uint32_t data0,uint32_t data1)
{
    uint32_t addr_tmp = addr;
    uint32_t data = data0;
    uint32_t i = 0;

    if (print_flag){
        uhs_phy_printf("IN_ARRAY_WRITE_FIX\r\n");
    }
    for(i = 0; i < (len>>2); i ++)
    {
        addr_tmp = (i << 2) + addr;
        if((i % 2) == 0)
            data = data0 + i;
        else
            data = data1 + i;

        BL_WR_WORD(addr_tmp,data); 
    }
    if (print_flag){
        uhs_phy_printf("BEFORE CACHE FUCNTION\r\n");
    }
    if (cache_state){
        // #if CACHE_EN
        __DSB();
        __ISB();
        L1C_DCache_Clean_Invalid_All();
        __DSB();
        __ISB();
        // #endif
    }
    uhs_phy_delay_us(10);
    if (print_flag){
        uhs_phy_printf("OUT_ARRAY_WRITE_FIX\r\n");
    }
}

uint8_t array_read_fix(uint32_t addr,uint32_t len,uint32_t data0,uint32_t data1)
{
    uint8_t array_read_pass = 1;
    uint32_t addr_tmp = addr;
    uint32_t data = data0;
    uint32_t data_read = 0;
    uint32_t i = 0;

    if (print_flag){
        uhs_phy_printf("IN_ARRAY_READ_FIX\r\n");
    }
    for(i = 0; i < (len>>2); i ++)
    {
        // data_read = 0;
        // data_read += *((volatile uint8_t *)(addr+(i<<2)+3));
        // data_read <<= 8;
        // data_read += *((volatile uint8_t *)(addr+(i<<2)+2));
        // data_read <<= 8;
        // data_read += *((volatile uint8_t *)(addr+(i<<2)+1));
        // data_read <<= 8;
        // data_read += *((volatile uint8_t *)(addr+(i<<2)+0));

        addr_tmp = (i << 2) + addr;
        data_read = BL_RD_WORD(addr_tmp);
        if((i % 2) == 0)
            data = data0 + i;
        else
            data = data1 + i;

        if (print_flag && i == 0){
            uhs_phy_printf("addr 0x%lx, write_val 0x%lx, read_val 0x%lx\r\n",addr_tmp,data,data_read);
        }
        if(data_read != data){
            array_read_pass = 0;
            uhs_phy_printf("addr 0x%lx, write_val 0x%lx, read_val error 0x%lx\r\n",addr_tmp,data,data_read);
            break;
        }
    }
    if (print_flag){
        uhs_phy_printf("BEFORE CACHE FUCNTION\r\n");
    }
    if (cache_state){
        // #if CACHE_EN
        __DSB();
        __ISB();
        L1C_DCache_Clean_Invalid_All();
        __DSB();
        __ISB();
        // #endif
    }
    uhs_phy_delay_us(10);
    if (print_flag){
        uhs_phy_printf("OUT_ARRAY_READ_FIX\r\n");
    }
    return array_read_pass;
}

void set_ck_dly_drv(uint32_t array_ck_dly_drv)
{
    uint32_t array_dqx_dly_drv = 0;
    uint32_t array_dqsx_dly_drv = 0;
    uint32_t array_cen_dly_drv = 0;

    uhs_phy_delay_us(10);  // ck modify need time

    array_dqx_dly_drv = (array_ck_dly_drv >=4) ? (array_ck_dly_drv-4) : 0;
    array_cen_dly_drv = array_dqx_dly_drv + 1;
    array_dqx_dly_drv = (array_dqx_dly_drv > 15) ? 15 : array_dqx_dly_drv;
    array_cen_dly_drv = (array_cen_dly_drv > 15) ? 15 : array_cen_dly_drv;
    array_dqsx_dly_drv = (array_dqsx_dly_drv > 15) ? 15 : array_dqsx_dly_drv;

    cfg_dq_drv(array_dqx_dly_drv);
    // cfg_dqs_drv(array_dqsx_dly_drv);
    cfg_ck_cen_drv(array_ck_dly_drv,array_cen_dly_drv);
    // uhs_phy_printf_debug("array_dqx_dly_drv= %ld,array_dqsx_dly_drv= %ld,array_ck_dly_drv= %ld,array_cen_dly_drv= %ld\r\n",array_dqx_dly_drv,array_dqsx_dly_drv,array_ck_dly_drv,array_cen_dly_drv); //debug
    // uhs_phy_delay_us(50); // ck modify need time
}

uint8_t array_read_latency_cal(void)
{
    // uint32_t tmpVal = 0;
    uint32_t uhs_latency = 42;
    // uint8_t array_ck_dly_drv_val[3] = {15,4,9};
    uint8_t array_ck_dly_drv_val[3] = {4,9,15};
    uint8_t ck_i;
    uint32_t array_ck_dly_drv = 0;
    int32_t i = 0;
    uint32_t array_dqs = 0;
    uint32_t array_dq = 0;
    uint32_t dqs_flag;
    uint32_t dq_flag;
    uint32_t len = 128;
    uint8_t rwindow = 0;

    for(uhs_latency = latency_wr[1]; uhs_latency > 0; uhs_latency --)
    {
        if(uhs_latency == 34)
        {
            array_read_err = 1;
            return uhs_err_handler(UHS_ARRAY_READ_LAT_ERR);
        }

        uhs_phy_printf_debug("array read cal by latency= %ld\r\n",uhs_latency);
        set_uhs_latency_r(uhs_latency);

        for (ck_i = 0; ck_i < (sizeof(array_ck_dly_drv_val)/sizeof(array_ck_dly_drv_val[0])); ck_i++){
            array_ck_dly_drv = array_ck_dly_drv_val[ck_i];
            set_ck_dly_drv(array_ck_dly_drv);
            uhs_phy_printf_debug("array read cal by ck= %ld\r\n",array_ck_dly_drv);

            rwindow = 0;

            // sweep dqs
            cfg_dq_rx(0);
            for(i = 15; i >= 0; i --)
            {
                cfg_dqs_rx(i);
                dqs_flag = array_read_fix(addr_rarray,len,data0_rarray,data1_rarray);
                if(dqs_flag == 1)
                {
                    uhs_phy_printf("array_read_dqs_dq_cal pass by --dqs= %ld\r\n",i); 
                    array_dqs += i;
                    rwindow += i;
                    uhs_phy_cal_res->rwindow_end = i;
                    break; 
                }
            }
            for(i = 0; i <= 15; i ++)
            {
                cfg_dqs_rx(i);
                dqs_flag = array_read_fix(addr_rarray,len,data0_rarray,data1_rarray);
                if(dqs_flag == 1)
                {
                    uhs_phy_printf("array_read_dqs_dq_cal pass by ++dqs= %ld\r\n",i); 
                    array_dqs += i;
                    rwindow = (i > 0) ? (rwindow - i) : (rwindow + 1);
                    uhs_phy_cal_res->rwindow_begin = i;
                    break; 
                }
            }
            // sweep dq
            cfg_dqs_rx(0);
            for(i = 15; i >= 0; i --)
            {
                cfg_dq_rx(i);
                dq_flag = array_read_fix(addr_rarray,len,data0_rarray,data1_rarray);
                if(dq_flag == 1)
                {
                    uhs_phy_printf("array_read_dqs_dq_cal pass by --dq= %ld\r\n",i);  
                    array_dq += i;
                    rwindow += i;
                    break; 
                }                  
            }
            for(i = 0; i <= 15; i ++)
            {
                cfg_dq_rx(i);
                dq_flag = array_read_fix(addr_rarray,len,data0_rarray,data1_rarray);
                if(dq_flag == 1)
                {
                    uhs_phy_printf("array_read_dqs_dq_cal pass by ++dq= %ld\r\n",i);  
                    array_dq += i;
                    rwindow -= i;
                    break; 
                }                  
            }

            if(dqs_flag == 1 || dq_flag == 1){
                if(array_dqs >= array_dq)
                {
                    array_dqs = (array_dqs-array_dq)/2;
                    array_dq = 0;
                }
                else
                {
                    #if CAL_MODE == 2
                    array_read_err = 2;
                    return uhs_err_handler(UHS_ARRAY_READ_LAT_ERR);
                    #endif
                    array_dq = (array_dq-array_dqs)/2;
                    array_dqs = 0;
                }
                cfg_dq_rx(array_dq);
                cfg_dqs_rx(array_dqs);
                uhs_phy_printf("array_read_dqs_dq_cal valid code number= %d\r\n",rwindow);
                uhs_phy_cal_res->rwindow = rwindow;
                uhs_phy_cal_res->rdqs = array_dqs;
                uhs_phy_cal_res->rdq = array_dq;
                uhs_phy_printf("array_read_dqs_dq_cal pass by array_dqs= %ld, array_dq= %ld\r\n",array_dqs,array_dq);
                break;
            }
        }
        if(dqs_flag == 1 || dq_flag == 1){
            uhs_phy_cal_res->rl = uhs_latency;
            uhs_phy_printf("array_read_latency_cal pass, latency= %ld, ck= %ld\r\n",uhs_latency,array_ck_dly_drv);
            break;
        }
    }

    return 0;
}

uint8_t array_write_ck_cal(void)
{
    uint32_t array_ck_dly_drv = 0;
    uint32_t array_ck_dly_drv1 = 15;
    uint32_t array_ck_dly_drv2 = 4;
    uint32_t flag_1 = 0;
    uint32_t flag_2 = 0;
    uint32_t len = 1024<<4;

    for(array_ck_dly_drv = 4; array_ck_dly_drv <= 15; array_ck_dly_drv ++)
    {
        set_ck_dly_drv(array_ck_dly_drv);
        flag_2 = array_read_fix(addr_rarray,len,data0_rarray,data1_rarray);
        if (flag_2 == 0){
            uhs_phy_printf("array_write_ck_cal ck++ = %ld, flag_2 = %ld\r\n",array_ck_dly_drv,flag_2);
        }
        if(flag_2 == 0 && flag_ck2 == 0){
            flag_ck2 = 1;
            uhs_phy_printf("array_write_ck_cal fail by ++ck= %ld\r\n",array_ck_dly_drv);
            array_ck_dly_drv2 = array_ck_dly_drv;
            // break;
        }
    }
    if (flag_ck2 == 1)
        flag_2 = 0;
    for(array_ck_dly_drv = 15; array_ck_dly_drv >= 4; array_ck_dly_drv --)
    {
        set_ck_dly_drv(array_ck_dly_drv);
        flag_1 = array_read_fix(addr_rarray,len,data0_rarray,data1_rarray);
        if (flag_1 == 0){
            uhs_phy_printf("array_write_ck_cal ck-- = %ld, flag_1 = %ld\r\n",array_ck_dly_drv,flag_1);
        }
        if(flag_1 == 0 && flag_ck1 == 0){
            flag_ck1 = 1;
            uhs_phy_printf("array_write_ck_cal fail by --ck= %ld\r\n",array_ck_dly_drv);
            array_ck_dly_drv1 = array_ck_dly_drv;
            // break;
        }
    }
    if (flag_ck1 == 1)
        flag_1 = 0;

    if (flag_1 == 0 && flag_2 == 0){
        if(array_ck_dly_drv1 == 15 && array_ck_dly_drv2 == 4)
        {
            return uhs_err_handler(UHS_ARRAY_WRITE_CK_ERR);
        }
        else if ((15 - array_ck_dly_drv1) >= (array_ck_dly_drv2 - 4)){
            array_ck_dly_drv = 15;
        }
        else{
            array_ck_dly_drv = 4;
        }
    }
    else if (flag_1 == 0 && flag_2 == 1){
        array_ck_dly_drv = (array_ck_dly_drv1 > 9) ? 4 : 15;
    }else if (flag_1 == 1 && flag_2 == 0){
        array_ck_dly_drv = (array_ck_dly_drv2 > 9) ? 4 : 15;
    }
    else {
        array_ck_dly_drv = (15 + 4) / 2;         
    }

    set_ck_dly_drv(array_ck_dly_drv);
    uhs_phy_cal_res->ck = array_ck_dly_drv;
    uhs_phy_printf("array_write_ck_cal pass, ck= %ld\r\n",array_ck_dly_drv);

    return 0;
}

uint8_t array_read_dqs_dq_cal(void)
{
    int32_t i = 0;
    uint32_t array_dqs = 0;
    uint32_t array_dq = 0;
    uint32_t dqs_flag;
    uint32_t dq_flag;
    uint32_t len = 128;

    // sweep dqs
    cfg_dq_rx(0);

    for(i = 15; i >= 0; i --)
    {
        cfg_dqs_rx(i);
        dqs_flag = array_read_fix(addr_rarray,len,data0_rarray,data1_rarray);
        if(dqs_flag == 1)
        {
            uhs_phy_printf("array_read_dqs_dq_cal pass by dqs= %ld\r\n",i); 
            array_dqs = i;
            break; 
        }
    }
    // sweep dq 
    cfg_dqs_rx(0);
    for(i = 15; i >=0; i --)
    {
        cfg_dq_rx(i);
        dq_flag = array_read_fix(addr_rarray,len,data0_rarray,data1_rarray);
        if(dq_flag == 1)
        {
            uhs_phy_printf("array_read_dqs_dq_cal pass by dq= %ld\r\n",i);  
            array_dq = i;
            break; 
        }                  
    }
    if(dqs_flag == 0 && dq_flag == 0)
    {
        return uhs_err_handler(UHS_ARRAY_READ_CAL_ERR);
    }
    if(array_dqs > array_dq)
    {
        array_dqs = (array_dqs-array_dq)/2;
        array_dq = 0;
    }
    else
    {
        array_dq = (array_dq-array_dqs)/2;
        array_dqs = 0;
    }
    cfg_dq_rx(array_dq);
    cfg_dqs_rx(array_dqs);
    uhs_phy_printf("array_read_dqs_dq_cal pass by array_dqs= %ld, array_dq= %ld\r\n",array_dqs,array_dq);

    return 0;
}

uint8_t array_write_dqs_dq_cal(void)
{
    uint32_t tmpVal = 0;
    int32_t i = 0;
    uint32_t dqs_flag1 = 0;
    uint32_t dqs_flag2 = 0;
    uint32_t array_dqs_dly_drv = 0;
    uint32_t array_dqs_dly_drv1 = 0;
    uint32_t array_dqs_dly_drv2 = 0;

    uint32_t addr = 0x50000000;
    uint32_t len = 128;
    uint32_t data0 = 0x23456789;
    uint32_t data1 = 0x98765432;

    uint8_t wwindow = 0;

    for(i = 15; i >= 0; i --)
    {  
        cfg_dqs_drv(i);  
        array_write_fix(addr,len,data0,data1);
        dqs_flag1 = array_read_fix(addr,len,data0,data1);
        if(dqs_flag1 == 1)
        {
            uhs_phy_printf("array_write_dqs_dq_cal pass by -- dqs1= %ld\r\n",i);
            array_dqs_dly_drv1 = i;
            uhs_phy_cal_res->wwindow_end = i;
            break;  
        }              
        else
        {
            uhs_phy_printf_debug("array_write_dqs_dq_cal fail by -- dqs1= %ld\r\n",i);
        }
    }
    for(i = 0; i <= 15; i ++)
    {
        cfg_dqs_drv(i);
        array_write_fix(addr,len,data1,data0);
        dqs_flag2 = array_read_fix(addr,len,data1,data0);
        if(dqs_flag2 == 1)
        {
            uhs_phy_printf("array_write_dqs_dq_cal pass by ++ dqs2= %ld\r\n",i);
            array_dqs_dly_drv2 = i;
            uhs_phy_cal_res->wwindow_begin = i;
            break;
        }              
        else
        {
            uhs_phy_printf_debug("array_write_dqs_dq_cal fail by ++ dqs2= %ld\r\n",i);
        }
    }
    
    if(dqs_flag1 == 1 && dqs_flag2 == 1)
    {
        array_dqs_dly_drv = (array_dqs_dly_drv1 + array_dqs_dly_drv2) / 2 ;
    }
    else if(dqs_flag1 == 1 && dqs_flag2 == 0){
        array_dqs_dly_drv = array_dqs_dly_drv1;
    }else if(dqs_flag1 == 0 && dqs_flag2 == 1){
        array_dqs_dly_drv = array_dqs_dly_drv2;
    }else{
        return uhs_err_handler(UHS_ARRAY_WRITE_CAL_ERR);
    }

    //debug
    // array_dqs_dly_drv = 4;

    // if ck_dly_drv = 4, fix dqsx_dly_drv to 0
	tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00);
	tmpVal = (tmpVal >> 16) & 0xF;
	if(tmpVal == 4){
		array_dqs_dly_drv = 0;
        uhs_phy_cal_res->wwindow_begin = 0;
	}
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ0_DLY_DRV);

    wwindow = (array_dqs_dly_drv > 0) ? (array_dqs_dly_drv1 - array_dqs_dly_drv2 + 1) : (array_dqs_dly_drv1 - 0 + 1);
    uhs_phy_printf("array_write_dqs_dq_cal valid code number= %d\r\n",wwindow);
    uhs_phy_cal_res->wwindow = wwindow;
    uhs_phy_cal_res->wdqs = array_dqs_dly_drv;
    uhs_phy_cal_res->wdq = tmpVal;
    uhs_phy_printf("array_write_dqs_dq_cal pass by array_dqs_dly_drv= %ld,array_dq_dly_drv= %ld\r\n",array_dqs_dly_drv,tmpVal);
    // set dqs by register write cal result 
    cfg_dqs_drv(array_dqs_dly_drv);

    return 0;
}

BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_UHS_PLL_Freq(GLB_XTAL_Type xtalType, uint32_t pllFreq)
{
    uint32_t xtalFreq = 0;
    uint32_t factor = 0;
    GLB_MU_PLL_CFG_BASIC_Type uhsPllMCfg = {
        .clkpllRefdivRatio = 1,         /*!< pll_refdiv_ratio */
        .clkpllSelSampleClk = 2,        /*!< pll_sel_sample_clk */
        .clkpllVcoSpeed = 7,            /*!< pll_vco_speed */
        .clkpllEvenDivEn = 1,           /*!< pll_even_div_en */
        .clkpllEvenDivRatio = 2100/50,  /*!< pll_even_div_ratio */
    };
    GLB_MU_PLL_Cfg_Type uhsPllCfg[GLB_XTAL_MAX] = {
        { NULL, 0x0 },          /*!< XTAL is None */
        { &uhsPllMCfg, 0x0 },   /*!< XTAL is 24M */
        { &uhsPllMCfg, 0x0 },   /*!< XTAL is 32M */
        { &uhsPllMCfg, 0x0 },   /*!< XTAL is 38.4M */
        { &uhsPllMCfg, 0x0 },   /*!< XTAL is 40M */
        { &uhsPllMCfg, 0x0 },   /*!< XTAL is 26M */
        { &uhsPllMCfg, 0x0 },   /*!< XTAL is RC32M */
    };
    GLB_PLL_REF_CLK_Type refClk;

    /* calc clkpllRefdivRatio */
    switch(xtalType){
        case GLB_XTAL_NONE:
            return ERROR;
        case GLB_XTAL_24M:
            xtalFreq = 240;
            uhsPllMCfg.clkpllRefdivRatio = 1;
            break;
        case GLB_XTAL_32M:
            xtalFreq = 320;
            uhsPllMCfg.clkpllRefdivRatio = 2;
            break;
        case GLB_XTAL_38P4M:
            xtalFreq = 384;
            uhsPllMCfg.clkpllRefdivRatio = 2;
            break;
        case GLB_XTAL_40M:
            xtalFreq = 400;
            uhsPllMCfg.clkpllRefdivRatio = 2;
            break;
        case GLB_XTAL_26M:
            xtalFreq = 260;
            uhsPllMCfg.clkpllRefdivRatio = 1;
            break;
        case GLB_XTAL_RC32M:
            xtalFreq = 320;
            uhsPllMCfg.clkpllRefdivRatio = 2;
            break;
        default :
            break;
    }
    /* calc clkpllSelSampleClk */
    factor = pllFreq*20480/(xtalFreq/uhsPllMCfg.clkpllRefdivRatio);
    if(factor<32*2048){
        uhsPllMCfg.clkpllSelSampleClk = 0;
    }else if(factor<64*2048){
        uhsPllMCfg.clkpllSelSampleClk = 1;
    }else if(factor<128*2048){
        uhsPllMCfg.clkpllSelSampleClk = 2;
    }else{
        uhsPllMCfg.clkpllSelSampleClk = 2;
    }
    /* calc clkpllVcoSpeed */
    if(pllFreq<800){
        uhsPllMCfg.clkpllVcoSpeed = 1;
    }else if(pllFreq<1000){
        uhsPllMCfg.clkpllVcoSpeed = 2;
    }else if(pllFreq<1200){
        uhsPllMCfg.clkpllVcoSpeed = 3;
    }else if(pllFreq<1500){
        uhsPllMCfg.clkpllVcoSpeed = 4;
    }else if(pllFreq<1700){
        uhsPllMCfg.clkpllVcoSpeed = 5;
    }else if(pllFreq<1900){
        uhsPllMCfg.clkpllVcoSpeed = 6;
    }else if(pllFreq<2200){
        uhsPllMCfg.clkpllVcoSpeed = 7;
    }else{
        uhsPllMCfg.clkpllVcoSpeed = 8;
    }
    /* calc clkpllEvenDivRatio */
    uhsPllMCfg.clkpllEvenDivRatio = pllFreq/50;
    /* calc clkpllSdmin */
    uhsPllCfg[GLB_XTAL_24M].clkpllSdmin = factor;
    uhsPllCfg[GLB_XTAL_32M].clkpllSdmin = factor;
    uhsPllCfg[GLB_XTAL_38P4M].clkpllSdmin = factor;
    uhsPllCfg[GLB_XTAL_40M].clkpllSdmin = factor;
    uhsPllCfg[GLB_XTAL_26M].clkpllSdmin = factor;
    uhsPllCfg[GLB_XTAL_RC32M].clkpllSdmin = factor;
    
    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }
    
    // GLB_Power_Off_MU_PLL(GLB_MU_PLL_UHSPLL);
    GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_UHSPLL, refClk);
    GLB_Power_On_MU_PLL(GLB_MU_PLL_UHSPLL, &(uhsPllCfg[xtalType]), 1);
    
    return SUCCESS;
}

uint8_t init_reg_write(void){
    uint32_t tmpVal = 0;
    uint8_t wl_i;
    uint32_t wl;
    uint32_t wdqs;
    // uint8_t wdq_val[3] = {0,11,5};
    uint8_t wdq_val[3] = {0,5,11};
    uint8_t wdq_i;
    uint32_t wdq;
    uint32_t rl;
    uint32_t rdqs;
    uint32_t rdq;
    uint8_t rl_i;
    uint8_t wl_val_32[6] = {1,0,2,3,4,5};
    uint8_t rl_val_32[5] = {36,37,38,39,40};
    uint8_t wl_val_64[6] = {9,8,10,7,11,6};
    uint8_t rl_val_64[5] = {36,37,38,39,40};
    uint8_t wl_val[6];
    uint8_t rl_val[5];

    if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_32MB){
        for (wl_i = 0; wl_i < (sizeof(wl_val)/sizeof(wl_val[0])); wl_i++){
            wl_val[wl_i] = wl_val_32[wl_i];
        }
        for (rl_i = 0; rl_i < (sizeof(rl_val)/sizeof(rl_val[0])); rl_i++){
            rl_val[rl_i] = rl_val_32[rl_i];
        }
	}else if(cfg_glb->psramMemSize == PSRAM_MEM_SIZE_64MB){
        for (wl_i = 0; wl_i < (sizeof(wl_val)/sizeof(wl_val[0])); wl_i++){
            wl_val[wl_i] = wl_val_64[wl_i];
        }
        for (rl_i = 0; rl_i < (sizeof(rl_val)/sizeof(rl_val[0])); rl_i++){
            rl_val[rl_i] = rl_val_64[rl_i];
        }
	}

	// set to 2000Mbps
    for (rl_i = 0; rl_i < (sizeof(rl_val)/sizeof(rl_val[0])); rl_i++){
        rl = rl_val[rl_i];
        set_uhs_latency_r(rl);
        for (wl_i = 0; wl_i < (sizeof(wl_val)/sizeof(wl_val[0])); wl_i++){
            wl = wl_val[wl_i];
            latency_wr[0] = wl;
            set_uhs_latency_w(wl);
            for (wdq_i = 0; wdq_i < (sizeof(wdq_val)/sizeof(wdq_val[0])); wdq_i++){
                wdq = wdq_val[wdq_i];
                cfg_dq_drv(wdq);
                cfg_ck_cen_drv(wdq + 4,wdq + 1);
                for (wdqs = 0; wdqs <= 15; wdqs++){
                    cfg_dqs_drv(wdqs);
                    set_uhs_phy_init();
                    CHECK_ERR_FLAG(uhs_reg_w,(uhs_latency_code,2,0,0)); //uhs_latency_code==3,uhs_drive==2,ma==0,BL_32==0
                    set_uhs_phy();
                    rdq = 0;
                    cfg_dq_rx(rdq);
                    for (rdqs = 0; rdqs <= 15; rdqs++){
                        cfg_dqs_rx(rdqs);
                        CHECK_ERR_FLAG(uhs_reg_r,(0,1));
                        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
                        uhs_phy_printf_debug("PSRAM_UHS_UHS_CMD>>24 = 0x%lx, rdqs++\r\n",tmpVal);
                        if(tmpVal == ((2<<3)+uhs_latency_code)){
                            uhs_phy_printf("LATENCY_CODE_WRITE_SUCCESS, wl = %ld, wdqs = %ld, wdq = %ld, rl = %ld, rdqs = %ld, rdq = %ld\r\n",wl,wdqs,wdq,rl,rdqs,rdq);
                            return 0;
                        }
                        else{
                            uhs_phy_printf_debug("LATENCY_CODE_WRITE_FAIL, wl = %ld, wdqs = %ld, wdq = %ld, rl = %ld, rdqs = %ld, rdq = %ld\r\n",wl,wdqs,wdq,rl,rdqs,rdq);
                        }
                    }
                    rdqs = 0;
                    cfg_dqs_rx(rdqs);
                    for (rdq = 0; rdq <= 15; rdq++){
                        cfg_dq_rx(rdq);
                        CHECK_ERR_FLAG(uhs_reg_r,(0,1));
                        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
                        uhs_phy_printf_debug("PSRAM_UHS_UHS_CMD>>24 = 0x%lx, rdq++\r\n",tmpVal);
                        if(tmpVal == ((2<<3)+uhs_latency_code)){
                            uhs_phy_printf("LATENCY_CODE_WRITE_SUCCESS, wl = %ld, wdqs = %ld, wdq = %ld, rl = %ld, rdqs = %ld, rdq = %ld\r\n",wl,wdqs,wdq,rl,rdqs,rdq);
                            return 0;
                        }
                        else{
                            uhs_phy_printf_debug("LATENCY_CODE_WRITE_FAIL, wl = %ld, wdqs = %ld, wdq = %ld, rl = %ld, rdqs = %ld, rdq = %ld\r\n",wl,wdqs,wdq,rl,rdqs,rdq);
                        }
                    }
                }
            }
        }
    }
    return uhs_err_handler(UHS_LATENCY_CODE_WRITE_ERR);
}

uint8_t init_array_write(void){
    uint8_t wl_val[6] = {13,12,14,11,15,10};
    uint8_t wl_i;
    uint32_t wl;
    uint32_t wdqs;
    // uint8_t wdq_val[3] = {0,11,5};
    uint8_t wdq_val[3] = {0,5,11};
    uint8_t wdq_i;
    uint32_t wdq;
    uint32_t rl;
    uint32_t rdqs;
    uint32_t rdq;
    uint32_t len = 1024<<4;
    uint32_t flag = 0;
    print_flag = 1;

    for (wl_i = 0; wl_i < (sizeof(wl_val)/sizeof(wl_val[0])); wl_i++){
        wl = wl_val[wl_i];
        latency_wr[0] = wl;
        set_uhs_latency_w(wl);
        for (wdq_i = 0; wdq_i < (sizeof(wdq_val)/sizeof(wdq_val[0])); wdq_i++){
            wdq = wdq_val[wdq_i];
            cfg_dq_drv(wdq);
            cfg_ck_cen_drv(wdq + 4,wdq + 1);
            for (wdqs = 0; wdqs <= 15; wdqs++){
                cfg_dqs_drv(wdqs);
                array_write_fix(addr_rarray,len,data0_rarray,data1_rarray);
                for (rl = latency_wr[1]; rl >= 35; rl--){
                    set_uhs_latency_r(rl);
                    rdq = 0;
                    cfg_dq_rx(rdq);
                    for (rdqs = 0; rdqs <= 15; rdqs++){
                        cfg_dqs_rx(rdqs);
                        flag = array_read_fix(addr_rarray,len,data0_rarray,data1_rarray);
                        if(flag == 1){
                            uhs_phy_printf("INIT_ARRAY_WRITE_SUCCESS, rdqs++, wl = %ld, wdqs = %ld, wdq = %ld, rl = %ld, rdqs = %ld, rdq = %ld\r\n",wl,wdqs,wdq,rl,rdqs,rdq);
                            print_flag = 0;
                            #if CAL_MODE == 2
                            if(wl != 13){
                                init_array_write_err = 2;
                                return uhs_err_handler(UHS_INIT_ARRAY_WRITE_ERR);
                            }
                            #endif
                            uhs_phy_cal_res->wl = wl;
                            return 0;
                        }    
                        else{
                            uhs_phy_printf_debug("INIT_ARRAY_WRITE_FAIL, rdqs++, wl = %ld, wdqs = %ld, wdq = %ld, rl = %ld, rdqs = %ld, rdq = %ld\r\n",wl,wdqs,wdq,rl,rdqs,rdq);
                        }                    
                    }
                    rdqs = 0;
                    cfg_dqs_rx(rdqs);
                    for (rdq = 0; rdq <= 15; rdq++){
                        cfg_dq_rx(rdq);
                        flag = array_read_fix(addr_rarray,len,data0_rarray,data1_rarray);
                        if(flag == 1){
                            uhs_phy_printf("INIT_ARRAY_WRITE_SUCCESS, rdq++, wl = %ld, wdqs = %ld, wdq = %ld, rl = %ld, rdqs = %ld, rdq = %ld\r\n",wl,wdqs,wdq,rl,rdqs,rdq);
                            print_flag = 0;
                            #if CAL_MODE == 2
                            if(wl != 13){
                                init_array_write_err = 2;
                                return uhs_err_handler(UHS_INIT_ARRAY_WRITE_ERR);
                            }
                            #endif
                            uhs_phy_cal_res->wl = wl;
                            return 0;
                        }    
                        else{
                            uhs_phy_printf_debug("INIT_ARRAY_WRITE_FAIL, rdq++, wl = %ld, wdqs = %ld, wdq = %ld, rl = %ld, rdqs = %ld, rdq = %ld\r\n",wl,wdqs,wdq,rl,rdqs,rdq);
                        }                    
                    }
                }
            }
        }
    }
    init_array_write_err = 1;
    return uhs_err_handler(UHS_INIT_ARRAY_WRITE_ERR);
}

void set_odt_en(void){
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_RSVD_REG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_MR2_2_0,0x3);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_RSVD_REG,tmpVal);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_MODE_REG,0x2); //reg_mode_reg
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x1);  //reg_config_req
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
    uhs_phy_delay_us(10);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_REGW_PULSE,0x1);  //reg_regw_pulse
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD,tmpVal);
    uhs_phy_delay_us(10);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x0);  //reg_config_req
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_ODT_SEL,0xf);  // odt_sel
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_4C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_ODT_SEL_HW,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_ODT_SEL_DLY,0x3);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_4C,tmpVal);
}

uint8_t init_reg_write_2kM(void){
    uint32_t tmpVal = 0;
    uint8_t wl_val[6] = {13,12,14,11,15,10};
    uint8_t wl_i;
    uint32_t wl;
    uint32_t wdqs;
    // uint8_t wdq_val[3] = {0,11,5};
    uint8_t wdq_val[3] = {0,5,11};
    uint8_t wdq_i;
    uint32_t wdq;

	// set to 2000Mbps
    for (wl_i = 0; wl_i < (sizeof(wl_val)/sizeof(wl_val[0])); wl_i++){
        wl = wl_val[wl_i];
        latency_wr[0] = wl;
        set_uhs_latency_w(wl);
        for (wdq_i = 0; wdq_i < (sizeof(wdq_val)/sizeof(wdq_val[0])); wdq_i++){
            wdq = wdq_val[wdq_i];
            cfg_dq_drv(wdq);
            cfg_ck_cen_drv(wdq + 4,wdq + 1);
            for (wdqs = 0; wdqs <= 15; wdqs++){
                cfg_dqs_drv(wdqs);
                set_odt_en();
                CHECK_ERR_FLAG(uhs_reg_r,(2,0));
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
                uhs_phy_printf_debug("MA2 = 0x%lx\r\n",tmpVal);
                if(tmpVal == 3){
                    uhs_phy_printf("2kM_REG_WRITE_SUCCESS, wl = %ld, wdqs = %ld, wdq = %ld\r\n",wl,wdqs,wdq);
                    return 0;
                }
                else{
                    uhs_phy_printf_debug("2kM_REG_WRITE_FAIL, wl = %ld, wdqs = %ld, wdq = %ld\r\n",wl,wdqs,wdq);
                }
            }
        }
    }
    return uhs_err_handler(UHS_REG_WRITE_2kM_ERR);
}

uint8_t self_cal()
{
    uint32_t tmpVal = 0;
    uint32_t datarate;
    datarate = cfg_glb->pck_freq;

    if (datarate >= 933*2){
        uhs_latency_code = UHS_LATENCY_CODE_1066;
    }else if(datarate >= 800*2){
        uhs_latency_code = UHS_LATENCY_CODE_933;
    }else if(datarate >= 533*2){
        uhs_latency_code = UHS_LATENCY_CODE_800;
    }else if(datarate >= 400*2){
        uhs_latency_code = UHS_LATENCY_CODE_533;
    }else if(datarate >= 333*2){
        uhs_latency_code = UHS_LATENCY_CODE_400;
    }else if(datarate >= 200*2){
        uhs_latency_code = UHS_LATENCY_CODE_333;
    }else{
        uhs_latency_code = UHS_LATENCY_CODE_200;
    }
    // #if PSRAM_32MB
	// PSRAM_UHS_Cfg_Type psramCfg = {
    //     datarate,
    //     PSRAM_MEM_SIZE_32MB,
    //     PSRAM_PAGE_SIZE_2KB,
    //     0,
    // };
	// #else
    // PSRAM_UHS_Cfg_Type psramCfg = {
    //     datarate,
    //     PSRAM_MEM_SIZE_64MB,
    //     PSRAM_PAGE_SIZE_2KB,
    //     0,
    // };
    // #endif

    uhs_phy_printf("********** INIT_REG_WRITE **********\r\n");
    CHECK_ERR_FLAG(init_reg_write,()); //write latency code
    // uhs_phy_printf("START_CAL_AT %ldMbps\r\n",datarate);
    // datarate_glb = datarate;
    // ramsize_glb = cfg->psramMemSize;
    GLB_Config_UHS_PLL_Freq(GLB_XTAL_40M,datarate);
    Psram_UHS_Init_Override(cfg_glb); //controller init
    set_uhs_phy();

    #if CAL_MODE == 0
    return 0;
    // then load efuse, to set uhs phy regs
    // call set_odt_en(), to set psram odt MR if need
    // call mr_read_back()
    #endif

    uhs_phy_printf("********** REG_READ_CAL **********\r\n");
    // uhs_phy_reg_dump();
    // ******register read latency & dqs & dq calibration
    CHECK_ERR_FLAG(reg_read_cal,());
    if (cal_done_flag == 1)
        return 0;
    // if (datarate >= 1800){
    //     latency_wr[1] = 39;
    // }else if(datarate >= 1600){
    //     latency_wr[1] = 38;
    // }else if(datarate >= 1100){
    //     latency_wr[1] = 37;
    // }else{
    //     latency_wr[1] = 36;
    // }

    CHECK_ERR_FLAG(uhs_reg_r,(1,0));
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
    if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_32MB){
        tmpVal &= 0x10;
    }else if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_64MB){
        tmpVal &= 0x20;
    }
    if (tmpVal != 0){
        return uhs_err_handler(UHS_BAD_DIE_ERR);
    }

    uhs_phy_printf("UHS_PHY_CAL, ODT_EN = %d\r\n",ODT_EN);
    #if ODT_EN
    uhs_phy_printf("********** INIT_REG_WRITE_2kM **********\r\n");
    CHECK_ERR_FLAG(init_reg_write_2kM,());
    #endif

    uhs_phy_printf("********** INIT_ARRAY_WRITE **********\r\n");
    #if bl808_DBG_RF == 2
    uhs_phy_reg_dump();
    #endif
    // reg_write_cal();
    CHECK_ERR_FLAG(init_array_write,());
    uhs_phy_printf("********** ARRAY_READ_CAL **********\r\n");
    // uhs_phy_reg_dump();
    // ******array read latency & dqs & dq calibration
    CHECK_ERR_FLAG(array_read_latency_cal,());
    uhs_phy_printf("********** ARRAY_WRITE_CK_CAL **********\r\n");
    // uhs_phy_reg_dump();
    flag_ck1 = 0;
    flag_ck2 = 0;
    CHECK_ERR_FLAG(array_write_ck_cal,());
    uhs_phy_printf("********** ARRAY_WRITE_CAL **********\r\n");
    // uhs_phy_reg_dump();
    // array_read_dqs_dq_cal();  //calibrated in array_read_latency_cal
    CHECK_ERR_FLAG(array_write_dqs_dq_cal,());
    // uhs_phy_reg_dump();

    return 0;
}

void soft_reset(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(GLB_BASE,GLB_SWRST_CFG2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_CTRL_PWRON_RST,0x1); // soft power on reset
    BL_WR_REG(GLB_BASE,GLB_SWRST_CFG2,tmpVal);
    uhs_phy_delay_ms(1);
}

uint8_t uhs_diagonal_test(uint32_t data0,uint32_t data1)
{
    uint32_t RA = 0x0; //X_address
    uint32_t CA = 0x0; //Y_address
    uint32_t CA_init = 0x0;
    uint32_t dataTmp;
    uint32_t STRESS_TEST_BASE = 0x50000000;
    uint32_t RowAddr = 0x3fff; //256Mb X_address

    if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_32MB){
        RowAddr = 0x3fff;
    }else if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_64MB){
        RowAddr = 0x7fff;
    }

    // data0
    for (RA = 0x0; RA <= RowAddr; RA++){
        STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFC0007FF;
        STRESS_TEST_BASE = STRESS_TEST_BASE | (RA<<11); // STRESS_TEST_BASE[25:11] = RA[14:0]
        CA_init = (RA & 0x7f) << 3;
        for (CA = CA_init; CA <= CA_init + 0x7; CA = CA + 2){
            STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFFFFF800;
            STRESS_TEST_BASE = STRESS_TEST_BASE | (CA<<1); // STRESS_TEST_BASE[10:2] = CA[9:1], STRESS_TEST_BASE[1:0] = 0;
            *((volatile uint32_t*)(STRESS_TEST_BASE)) = data0;
        }
    }
    for (RA = 0x0; RA <= RowAddr; RA++){
        STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFC0007FF;
        STRESS_TEST_BASE = STRESS_TEST_BASE | (RA<<11); // STRESS_TEST_BASE[25:11] = RA[14:0]
        CA_init = (RA & 0x7f) << 3;
        for (CA = CA_init; CA <= CA_init + 0x7; CA = CA + 2){
            STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFFFFF800;
            STRESS_TEST_BASE = STRESS_TEST_BASE | (CA<<1); // STRESS_TEST_BASE[10:2] = CA[9:1], STRESS_TEST_BASE[1:0] = 0;
            dataTmp = *((volatile uint32_t*)(STRESS_TEST_BASE));
            if(dataTmp != data0){
                uhs_phy_printfe("addr: 0x%lx\r\n", STRESS_TEST_BASE);
                uhs_phy_printfe("data_w data0: 0x%lx\r\n", data0);
                uhs_phy_printfe("addr_r data0: 0x%lx\r\n", dataTmp);
                return uhs_err_handler(UHS_DIAGONAL_TEST_ERR);
            }
        }
    }
    // data1
    for (RA = 0x0; RA <= RowAddr; RA++){
        STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFC0007FF;
        STRESS_TEST_BASE = STRESS_TEST_BASE | (RA<<11); // STRESS_TEST_BASE[25:11] = RA[14:0]
        CA_init = (RA & 0x7f) << 3;
        for (CA = CA_init; CA <= CA_init + 0x7; CA = CA + 2){
            STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFFFFF800;
            STRESS_TEST_BASE = STRESS_TEST_BASE | (CA<<1); // STRESS_TEST_BASE[10:2] = CA[9:1], STRESS_TEST_BASE[1:0] = 0;
            *((volatile uint32_t*)(STRESS_TEST_BASE)) = data1;
        }
    }
    for (RA = 0x0; RA <= RowAddr; RA++){
        STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFC0007FF;
        STRESS_TEST_BASE = STRESS_TEST_BASE | (RA<<11); // STRESS_TEST_BASE[25:11] = RA[14:0]
        CA_init = (RA & 0x7f) << 3;
        for (CA = CA_init; CA <= CA_init + 0x7; CA = CA + 2){
            STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFFFFF800;
            STRESS_TEST_BASE = STRESS_TEST_BASE | (CA<<1); // STRESS_TEST_BASE[10:2] = CA[9:1], STRESS_TEST_BASE[1:0] = 0;
            dataTmp = *((volatile uint32_t*)(STRESS_TEST_BASE));
            if(dataTmp != data1){
                uhs_phy_printfe("addr: 0x%lx\r\n", STRESS_TEST_BASE);
                uhs_phy_printfe("data_w data1: 0x%lx\r\n", data1);
                uhs_phy_printfe("addr_r data1: 0x%lx\r\n", dataTmp);
                return uhs_err_handler(UHS_DIAGONAL_TEST_ERR);
            }
        }
    }

    uhs_phy_printf("uhs_diagonal_test success\r\n");
    return 0;
}

uint8_t uhs_all_addr_test(void)
{
    int32_t RA = 0x0; //X_address
    int32_t CA = 0x0; //Y_address
    uint32_t dataTmp;
    uint32_t STRESS_TEST_BASE = 0x50000000;
    uint32_t RowAddr = 0x3fff; //256Mb X_address
    uint32_t data0 = 0xffffffff;
    uint32_t data1 = 0x00000000;

    if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_32MB){
        RowAddr = 0x3fff;
    }else if (cfg_glb->psramMemSize == PSRAM_MEM_SIZE_64MB){
        RowAddr = 0x7fff;
    }

    // ****** Y_address -> X_address
    //data0
    for (RA = 0x0; RA <= RowAddr; RA++){
        STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFC0007FF;
        STRESS_TEST_BASE = STRESS_TEST_BASE | (RA<<11); // STRESS_TEST_BASE[25:11] = RA[14:0]
        for (CA = 0x0; CA <= 0x3ff; CA = CA + 2){
            STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFFFFF800;
            STRESS_TEST_BASE = STRESS_TEST_BASE | (CA<<1); // STRESS_TEST_BASE[10:2] = CA[9:1], STRESS_TEST_BASE[1:0] = 0;
            *((volatile uint32_t*)(STRESS_TEST_BASE)) = data0; 
        }
    }         
    for (RA = 0x0; RA <= RowAddr; RA++){
        STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFC0007FF;
        STRESS_TEST_BASE = STRESS_TEST_BASE | (RA<<11); // STRESS_TEST_BASE[25:11] = RA[14:0]
        for(CA = 0x0; CA <= 0x3ff; CA = CA + 2){
            STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFFFFF800;
            STRESS_TEST_BASE = STRESS_TEST_BASE | (CA<<1); // STRESS_TEST_BASE[10:2] = CA[9:1], STRESS_TEST_BASE[1:0] = 0;
            dataTmp = *((volatile uint32_t*)(STRESS_TEST_BASE));
            if(dataTmp != data0){
                uhs_phy_printfe("addr: 0x%lx\r\n", STRESS_TEST_BASE);
                uhs_phy_printfe("data_w data0 first: 0x%lx\r\n", data0);
                uhs_phy_printfe("addr_r data0 first: 0x%lx\r\n", dataTmp);
                return uhs_err_handler(UHS_ALL_ADDR_TEST_ERR);
            }
        }
    }
    // data1
    for (RA = 0x0; RA <= RowAddr; RA++){
        STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFC0007FF;
        STRESS_TEST_BASE = STRESS_TEST_BASE | (RA<<11); // STRESS_TEST_BASE[25:11] = RA[14:0]
        for (CA = 0x0; CA <= 0x3ff; CA = CA + 2){
            STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFFFFF800;
            STRESS_TEST_BASE = STRESS_TEST_BASE | (CA<<1); // STRESS_TEST_BASE[10:2] = CA[9:1], STRESS_TEST_BASE[1:0] = 0;
            *((volatile uint32_t*)(STRESS_TEST_BASE)) = data1;
        }
    }
    // ****** X_address -> Y_address    
    // data1 
    for (RA = RowAddr; RA >= 0x0; RA--){
        STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFC0007FF;
        STRESS_TEST_BASE = STRESS_TEST_BASE | (RA<<11); // STRESS_TEST_BASE[25:11] = RA[14:0]
        for(CA = 0x3ff - 1; CA >= 0x0; CA = CA - 2){
            STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFFFFF800;
            STRESS_TEST_BASE = STRESS_TEST_BASE | (CA<<1); // STRESS_TEST_BASE[10:2] = CA[9:1], STRESS_TEST_BASE[1:0] = 0;
            dataTmp = *((volatile uint32_t*)(STRESS_TEST_BASE));
            if(dataTmp != data1){
                uhs_phy_printfe("addr: 0x%lx\r\n", STRESS_TEST_BASE);
                uhs_phy_printfe("data_w data1: 0x%lx\r\n", data1);
                uhs_phy_printfe("addr_r data1: 0x%lx\r\n", dataTmp);
                return uhs_err_handler(UHS_ALL_ADDR_TEST_ERR);
            }
        }
    }
    //data0
    for (RA = RowAddr; RA >= 0x0; RA--){
        STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFC0007FF;
        STRESS_TEST_BASE = STRESS_TEST_BASE | (RA<<11); // STRESS_TEST_BASE[25:11] = RA[14:0]
        for (CA = 0x3ff - 1; CA >= 0x0; CA = CA - 2){
            STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFFFFF800;
            STRESS_TEST_BASE = STRESS_TEST_BASE | (CA<<1); // STRESS_TEST_BASE[10:2] = CA[9:1], STRESS_TEST_BASE[1:0] = 0;
            *((volatile uint32_t*)(STRESS_TEST_BASE)) = data0;
        }
    }      
    for (RA = RowAddr; RA >= 0x0; RA--){
        STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFC0007FF;
        STRESS_TEST_BASE = STRESS_TEST_BASE | (RA<<11); // STRESS_TEST_BASE[25:11] = RA[14:0]
        for(CA = 0x3ff - 1; CA >= 0x0; CA = CA - 2){
            STRESS_TEST_BASE = STRESS_TEST_BASE & 0xFFFFF800;
            STRESS_TEST_BASE = STRESS_TEST_BASE | (CA<<1); // STRESS_TEST_BASE[10:2] = CA[9:1], STRESS_TEST_BASE[1:0] = 0;
            dataTmp = *((volatile uint32_t*)(STRESS_TEST_BASE));
            if(dataTmp != data0){
                uhs_phy_printfe("addr: 0x%lx\r\n", STRESS_TEST_BASE);
                uhs_phy_printfe("data_w data0 second: 0x%lx\r\n", data0);
                uhs_phy_printfe("addr_r data0 second: 0x%lx\r\n", dataTmp);
                return uhs_err_handler(UHS_ALL_ADDR_TEST_ERR);
            }
        }
    }
    uhs_phy_printf("uhs_all_addr_test success\r\n");
    return 0;   
}


void dump_uhs_phy_cal_res(void)
{
    #if CAL_MODE != 2
    // dump uhs_phy_cal_res
    uhs_phy_printf("uhs_phy_cal_res->cal_mode = %d\r\n",uhs_phy_cal_res->cal_mode);
    uhs_phy_printf("uhs_phy_cal_res->err_type = %d\r\n",uhs_phy_cal_res->err_type);
    uhs_phy_printf("uhs_phy_cal_res->err_sub_type = %d\r\n",uhs_phy_cal_res->err_sub_type);
    uhs_phy_printf("uhs_phy_cal_res->datarate = %d\r\n",uhs_phy_cal_res->datarate);
    uhs_phy_printf("uhs_phy_cal_res->rl = %d\r\n",uhs_phy_cal_res->rl);
    uhs_phy_printf("uhs_phy_cal_res->rdqs = %d\r\n",uhs_phy_cal_res->rdqs);
    uhs_phy_printf("uhs_phy_cal_res->rdq = %d\r\n",uhs_phy_cal_res->rdq);
    uhs_phy_printf("uhs_phy_cal_res->rwindow = %d\r\n",uhs_phy_cal_res->rwindow);
    uhs_phy_printf("uhs_phy_cal_res->rwindow_begin = %d\r\n",uhs_phy_cal_res->rwindow_begin);
    uhs_phy_printf("uhs_phy_cal_res->rwindow_end = %d\r\n",uhs_phy_cal_res->rwindow_end);
    uhs_phy_printf("uhs_phy_cal_res->ck = %d\r\n",uhs_phy_cal_res->ck);
    uhs_phy_printf("uhs_phy_cal_res->wl = %d\r\n",uhs_phy_cal_res->wl);
    uhs_phy_printf("uhs_phy_cal_res->wdqs = %d\r\n",uhs_phy_cal_res->wdqs);
    uhs_phy_printf("uhs_phy_cal_res->wdq = %d\r\n",uhs_phy_cal_res->wdq);
    uhs_phy_printf("uhs_phy_cal_res->wwindow = %d\r\n",uhs_phy_cal_res->wwindow);
    uhs_phy_printf("uhs_phy_cal_res->wwindow_begin = %d\r\n",uhs_phy_cal_res->wwindow_begin);
    uhs_phy_printf("uhs_phy_cal_res->wwindow_end = %d\r\n",uhs_phy_cal_res->wwindow_end);
    uhs_phy_printf("uhs_phy_cal_res->cal_done = %d\r\n",uhs_phy_cal_res->cal_done);
    uhs_phy_printf("uhs_phy_cal_res->crc_res = %lx\r\n",uhs_phy_cal_res->crc_res);
    #else
    // dump uhs_phy_cal_res
    uhs_phy_printf("uhs_phy_cal_res->cal_mode = %ld\r\n",uhs_phy_cal_res->cal_mode);
    uhs_phy_printf("uhs_phy_cal_res->err_type = %lx\r\n",uhs_phy_cal_res->err_type);
    uhs_phy_printf("uhs_phy_cal_res->err_sub_type = %ld\r\n",uhs_phy_cal_res->err_sub_type);
    uhs_phy_printf("uhs_phy_cal_res->datarate = %ld\r\n",uhs_phy_cal_res->datarate);
    uhs_phy_printf("uhs_phy_cal_res->rl = %ld\r\n",uhs_phy_cal_res->rl);
    uhs_phy_printf("uhs_phy_cal_res->rdqs = %ld\r\n",uhs_phy_cal_res->rdqs);
    uhs_phy_printf("uhs_phy_cal_res->rdq = %ld\r\n",uhs_phy_cal_res->rdq);
    uhs_phy_printf("uhs_phy_cal_res->rwindow = %ld\r\n",uhs_phy_cal_res->rwindow);
    uhs_phy_printf("uhs_phy_cal_res->rwindow_begin = %ld\r\n",uhs_phy_cal_res->rwindow_begin);
    uhs_phy_printf("uhs_phy_cal_res->rwindow_end = %ld\r\n",uhs_phy_cal_res->rwindow_end);
    uhs_phy_printf("uhs_phy_cal_res->ck = %ld\r\n",uhs_phy_cal_res->ck);
    uhs_phy_printf("uhs_phy_cal_res->wl = %ld\r\n",uhs_phy_cal_res->wl);
    uhs_phy_printf("uhs_phy_cal_res->wdqs = %ld\r\n",uhs_phy_cal_res->wdqs);
    uhs_phy_printf("uhs_phy_cal_res->wdq = %ld\r\n",uhs_phy_cal_res->wdq);
    uhs_phy_printf("uhs_phy_cal_res->wwindow = %ld\r\n",uhs_phy_cal_res->wwindow);
    uhs_phy_printf("uhs_phy_cal_res->wwindow_begin = %ld\r\n",uhs_phy_cal_res->wwindow_begin);
    uhs_phy_printf("uhs_phy_cal_res->wwindow_end = %ld\r\n",uhs_phy_cal_res->wwindow_end);
    uhs_phy_printf("uhs_phy_cal_res->cal_done = %lx\r\n",uhs_phy_cal_res->cal_done);
    uhs_phy_printf("uhs_phy_cal_res->crc_res = %lx\r\n",uhs_phy_cal_res->crc_res);
    #endif
}

void uhs_phy_init(PSRAM_UHS_Cfg_Type *cfg)
{
    memset((void*)uhs_phy_cal_res, 0, sizeof(uhs_phy_cal_res_struct));
    uhs_phy_cal_res->cal_mode = CAL_MODE;
    uhs_phy_cal_res->datarate = cfg->pck_freq;

    err_flag = 0;

    __DSB();
    __ISB();
    cache_state = __get_MHCR();
    cache_state &= (0x1<<1);
    __DSB();
    __ISB();

    cfg_glb = cfg;
    latency_wr_2kM[1] = 41;
    uhs_phy_init_core(cfg);
}

extern uint32_t ATTR_TCM_SECTION BFLB_Soft_CRC32(void *dataIn, uint32_t len);
uint8_t uhs_phy_init_core(PSRAM_UHS_Cfg_Type *cfg)
{
    cal_done_flag = 0;
    if(latency_wr_2kM[1] == 34)
    {
        reg_read_err = 3;
        return uhs_err_handler(UHS_REG_READ_CAL_ERR);
    }

    uint32_t pck_freq_temp;

    uhs_phy_printf_debug("uhs phy init\r\n");
    if (cfg->psramMemSize == PSRAM_MEM_SIZE_32MB){
        uhs_phy_printf("\r\n########## START_CAL_AT %ldMbps, PSRAM_MEM_SIZE_32MB, CACHE_EN = %ld ##########\r\n",cfg->pck_freq,cache_state);
	}else if(cfg->psramMemSize == PSRAM_MEM_SIZE_64MB){
        uhs_phy_printf("\r\n########## START_CAL_AT %ldMbps, PSRAM_MEM_SIZE_64MB, CACHE_EN = %ld ##########\r\n",cfg->pck_freq,cache_state);
    }
    #if CAL_MODE != 2
        uhs_phy_printf("CAL_MODE = %d\r\n",uhs_phy_cal_res->cal_mode);
    #else
        uhs_phy_printf("CAL_MODE = %ld\r\n",uhs_phy_cal_res->cal_mode);
    #endif

    power_up_mm(0);
    power_up_uhspll();
    
    power_up_ldo12uhs();
    set_cen_ck_ckn();

    set_or_uhs();
    switch_to_ldo12uhs();
    release_cen_ck_ckn();

    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG9);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_SSC_EN,0x0); // uhspll_ssc_en
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG9,tmpVal);
    pck_freq_temp = cfg->pck_freq;
    if (cfg->psramMemSize == PSRAM_MEM_SIZE_32MB){
        cfg->pck_freq = 800;
        // PSRAM_UHS_Cfg_Type psramCfg = {
        //     800,
        //     PSRAM_MEM_SIZE_32MB,
        //     PSRAM_PAGE_SIZE_2KB,
        //     0,
        // };

        GLB_Config_UHS_PLL_Freq(GLB_XTAL_40M,800);    //stuck
        Psram_UHS_Init_Override(cfg);  // controller init
        set_uhs_phy_init();         // phy init
        set_uhs_latency_w(1);
        set_uhs_latency_r(17);
        psram_init();               // psram init after set freq & set_phy

        // uhs_reg_r(0,1);
        // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
        // uhs_phy_printf_debug("readout MA0 = 0x%lx\r\n",tmpVal);
        // if(tmpVal == ((2<<3)+5))    // 700M --> default uhs_latency_code == 5
        // {
        //     uhs_phy_printf_debug("register read pass at 700Mbps\r\n");
        // }
        // else{
        //     uhs_phy_printf_debug("register read fail at 700Mbps\r\n");
        // }
    }
	else if(cfg->psramMemSize == PSRAM_MEM_SIZE_64MB){
        cfg->pck_freq = 1400;
        // PSRAM_UHS_Cfg_Type psramCfg = {
        //     1400,
        //     PSRAM_MEM_SIZE_64MB,
        //     PSRAM_PAGE_SIZE_2KB,
        //     0,
        // };

        GLB_Config_UHS_PLL_Freq(GLB_XTAL_40M,1400);    //stuck
        Psram_UHS_Init_Override(cfg);  // controller init
        set_uhs_phy_init();         // phy init
        set_uhs_latency_w(9);
        set_uhs_latency_r(30);
        psram_init();               // psram init after set freq & set_phy

        // uhs_reg_r(0,1);
        // tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
        // if(tmpVal == ((2<<3)+1))    // 1400M --> default uhs_latency_code == 1
        // {
        //     uhs_phy_printf_debug("register read pass at 1400Mbps\r\n");
        // }
        // else{
        //     uhs_phy_printf_debug("register read fail at 1400Mbps\r\n");
        // }
    }
    
    cfg->pck_freq = pck_freq_temp;
    self_cal();
    uhs_phy_delay_ms(1);
    cal_done_flag = 1;
    #if CAL_MODE == 2
    if(err_flag == 0){
        uhs_phy_printf("********** UHS_DIAGONAL_TEST **********\r\n");
        uhs_diagonal_test(0x5555aaaa,0xaaaa5555);
        // uhs_phy_printf("********** UHS_ALL_ADDR_TEST **********\r\n");
        // uhs_all_addr_test();
    }
    // uhs_phy_printfe("!!!!!!!!!! uhs_phy_cal_res->err_type = %d !!!!!!!!!!\r\n",uhs_phy_cal_res->err_type);l
    uint32_t magic_os = 0x89abcdef;
    uhs_phy_cal_res->err_type += magic_os;
    uhs_phy_cal_res->cal_done = magic_os;
    uhs_phy_cal_res->crc_res = BFLB_Soft_CRC32(uhs_phy_cal_res, sizeof(uhs_phy_cal_res_struct)-4);
    #elif CAL_MODE == 1
    uhs_phy_cal_res->cal_done = 1;
    uhs_phy_cal_res->crc_res = BFLB_Soft_CRC32(uhs_phy_cal_res, sizeof(uhs_phy_cal_res_struct)-4);
    #endif

    #if CAL_MODE != 2
    uhs_phy_printf("!!!!!!!!!! uhs_phy_cal_res->err_type = %d !!!!!!!!!!\r\n",uhs_phy_cal_res->err_type);
    #else
    uhs_phy_printf("!!!!!!!!!! uhs_phy_cal_res->err_type = %lx !!!!!!!!!!\r\n",uhs_phy_cal_res->err_type);
    #endif

    dump_uhs_phy_cal_res();
    return uhs_phy_cal_res->err_type;

    //get dcache original state
    __DSB();
    __ISB();
    dcache_original = __get_MHCR();
    dcache_original &= (0x1<<1);
    __DSB();
    __ISB();
    uhs_phy_printf_debug("dcache_original= 0x%lx\r\n",dcache_original);

    uhs_phy_printf("UHS_PHY_CAL, CACHE_EN = %d\r\n",CACHE_EN);
    #if CACHE_EN
    csi_dcache_enable();
    #else
    csi_dcache_disable();
    #endif

    //get dcache current state
    __DSB();
    __ISB();
    dcache_current = __get_MHCR();
    dcache_current &= (0x1<<1);
    __DSB();
    __ISB();
    uhs_phy_printf_debug("dcache_current= 0x%lx\r\n",dcache_current);

    cfg->pck_freq = pck_freq_temp;
    #if CACHE_EN
    if(dcache_current == (0x1<<1))
    {
        self_cal();
    }
    else
    {
        uhs_phy_printf_debug("dcache enable fail\r\n");
        return uhs_err_handler(UHS_CACHE_ENABLE_ERR);
    }
    if (dcache_original == 0)
    {     
            csi_dcache_disable();       
    }  
    #else
    if(dcache_current == 0x0)
    {
        self_cal();
    }
    else
    {
        uhs_phy_printf_debug("dcache disable fail\r\n");
        return uhs_err_handler(UHS_CACHE_DISABLE_ERR);
    } 
    if (dcache_original == (0x1<<1))
    {     
        csi_dcache_enable();       
    }
    #endif

    //get dcache end state
    __DSB();
    __ISB();
    dcache_end = __get_MHCR();
    dcache_end &= (0x1<<1);
    __DSB();
    __ISB();
    if(dcache_end == dcache_original)
    {
        uhs_phy_printf_debug("dcache state right , dcache_state= 0x%lx\r\n",dcache_end);
    }
    else
    {
        uhs_phy_printf_debug("dcache state error\r\n");
        return uhs_err_handler(UHS_CACHE_RECOVER_ERR);
    }

    uhs_phy_delay_ms(1);

    if (cfg->psramMemSize == PSRAM_MEM_SIZE_32MB){
        uhs_phy_printf("########## END_CAL_AT %ldMbps, PSRAM_MEM_SIZE_32MB ##########\r\n",cfg->pck_freq);
    }else if(cfg->psramMemSize == PSRAM_MEM_SIZE_64MB){
        uhs_phy_printf("########## END_CAL_AT %ldMbps, PSRAM_MEM_SIZE_64MB ##########\r\n",cfg->pck_freq);
    }
}