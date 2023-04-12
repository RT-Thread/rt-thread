#ifndef __UHS_PHY_H__
#define __UHS_PHY_H__

#include "bl808_common.h"
#include "bl808_psram_uhs.h"
#include "bl808_glb.h"

#ifndef CAL_MODE
#define CAL_MODE (0)        // 0 is for sw call, 1 is for phy test, 2 is for ate cal
#endif

enum {
    UHS_LATENCY_CODE_533 = 3, // "0"
    UHS_LATENCY_CODE_800 = 3, // "1"
    UHS_LATENCY_CODE_933 = 3, // "2"
    UHS_LATENCY_CODE_1066 = 3,
    UHS_LATENCY_CODE_RESERVED = 3, //"4"
    UHS_LATENCY_CODE_400 = 3, //"5"
    UHS_LATENCY_CODE_333 = 3, //"6"
    UHS_LATENCY_CODE_200 = 3, //"7"
};

enum{
    UHS_REGR_GNT_ERR = 1,
    UHS_REGR_DONE_ERR,
    UHS_REGW_GNT_ERR,
    UHS_REGW_DONE_ERR,
    UHS_LATENCY_CODE_WRITE_ERR,
    UHS_INIT_ARRAY_WRITE_ERR,
    UHS_REG_READ_CAL_ERR,
    UHS_REG_WRITE_CAL_ERR,
    UHS_ARRAY_READ_LAT_ERR,
    UHS_ARRAY_WRITE_CK_ERR,
    UHS_ARRAY_READ_CAL_ERR,
    UHS_ARRAY_WRITE_CAL_ERR,
    UHS_CACHE_ENABLE_ERR,
    UHS_CACHE_DISABLE_ERR,
    UHS_CACHE_RECOVER_ERR,
    UHS_REG_WRITE_2kM_ERR,
    UHS_BAD_DIE_ERR,
    UHS_DIAGONAL_TEST_ERR,
    UHS_ALL_ADDR_TEST_ERR,
};

#if CAL_MODE != 2
typedef struct
{
    uint8_t rl              :6;
    uint8_t rdqs            :4;
    uint8_t rdq             :4;
    uint8_t wl              :5;
    uint8_t wdqs            :4;
    uint8_t wdq             :4;
    uint8_t ck              :4;
    uint8_t err_type;
    uint8_t err_sub_type;
    uint8_t cal_mode;
    uint16_t datarate;
    uint8_t rwindow;
    uint8_t rwindow_begin;
    uint8_t rwindow_end;
    uint8_t wwindow;
    uint8_t wwindow_begin;
    uint8_t wwindow_end;
    uint8_t cal_done;
    uint32_t crc_res;
} uhs_phy_cal_res_struct;
#else
typedef struct
{
    uint32_t rl;
    uint32_t rdqs;
    uint32_t rdq;
    uint32_t wl;
    uint32_t wdqs;
    uint32_t wdq;
    uint32_t ck;
    uint32_t err_type;
    uint32_t err_sub_type;
    uint32_t cal_mode;
    uint32_t datarate;
    uint32_t rwindow;
    uint32_t rwindow_begin;
    uint32_t rwindow_end;
    uint32_t wwindow;
    uint32_t wwindow_begin;
    uint32_t wwindow_end;
    uint32_t cal_done;
    uint32_t crc_res;
} uhs_phy_cal_res_struct;
#endif
extern uhs_phy_cal_res_struct* uhs_phy_cal_res;

// function call
void uhs_phy_init(PSRAM_UHS_Cfg_Type *cfg);
void uhs_phy_pwr_down(void);
uint8_t mr_read_back(void);
void set_odt_en(void);
// for htol test api
uint8_t uhs_all_addr_test(void);

// for test or debug in example main.c
void soft_reset(void);
void uhs_reset(uint8_t ma_rb);
void array_write_fix(uint32_t addr,uint32_t len,uint32_t data0,uint32_t data1);
uint8_t array_read_fix(uint32_t addr,uint32_t len,uint32_t data0,uint32_t data1);
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_UHS_PLL_Freq(GLB_XTAL_Type xtalType, uint32_t pllFreq);
//
void set_uhs_latency_r(uint32_t uhs_latency);
void set_uhs_latency_w(uint32_t uhs_latency);
void cfg_dq_drv(uint32_t dq);
void cfg_dqs_drv(uint32_t dqs);
void cfg_ck_cen_drv(uint8_t array_ck_dly_drv,uint8_t array_cen_dly_drv);
void cfg_dq_rx(uint8_t dq);
void cfg_dqs_rx(uint8_t dqs);

#endif  // __UHS_PHY_H__