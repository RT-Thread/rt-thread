#include "bl808_uhs_phy.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "psram_uhs_reg.h"
#include "glb_reg.h"
#include "pds_reg.h"
#include "bl808_common.h"
#include "bl808_psram_uhs.h"
#include "bl808_glb.h"

#define bl808_DBG_RF (0)
#if bl808_DBG_RF
#define uhs_phy_printf_debug printf  //  debug mode
#define uhs_phy_printf printf 
#else
#define uhs_phy_printf_debug(...)
// #define uhs_phy_printf printf  // commit it out in release version
#define uhs_phy_printf(...) //  useed in release version
#endif

uint8_t uhs_latency_code = 1;
int32_t dqs_dq_delta = 0;
uint32_t dcache_original = 0;
uint32_t dcache_current = 0;
uint32_t dcache_end = 0;


void uhs_phy_delay_us(uint32_t us)
{
    arch_delay_us(us);
}

void power_up_mm(void)
{
    // power up MM domain
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_PWR_OFF,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_ISO_EN,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_GATE_CLK,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_MEM_STBY,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_FORCE_MM_PDS_RST,0x0);
    BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal); 
}

void power_up_uhspll(void)
{
    // power_up_uhspll
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_UHSPLL_SFREG,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_UHSPLL,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_FBDV_RSTB,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_FBDV_RSTB,0x1);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal); 
}

void power_up_ldo12uhs(void)
{
    // use internal LDO 
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(GLB_BASE,GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_LDO12UHS,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_LDO12UHS_VOUT_SEL,0x5);
    BL_WR_REG(GLB_BASE,GLB_LDO12UHS,tmpVal);
    uhs_phy_delay_us(1);
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
    uhs_phy_delay_us(1);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY1,0xfc);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY0,0x1);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40,tmpVal);
    uhs_phy_delay_us(1);
}

void set_or_uhs(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_4C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_ODT_SEL_HW,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_4C,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PSRAM_TYPE,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_48,tmpVal);
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
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C);
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
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS1_DLY_RX,0x0); 
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS1N_DLY_RX,0x0);   
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C,tmpVal);
    uhs_phy_delay_us(300);
}

void switch_to_ldo12uhs(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY1,0xcc);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40,tmpVal);
    uhs_phy_delay_us(150);
}

void release_cen_ck_ckn(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY1,0xcf);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY0,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40,tmpVal);
    uhs_phy_delay_us(1);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ_OE_MID_P_REG,0x3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ_OE_MID_N_REG,0x3);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50,tmpVal);
    uhs_phy_delay_us(1);
}

void uhs_phy_pwr_down(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(GLB_BASE,GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_LDO12UHS_PULLDOWN_SEL,0x0);
    BL_WR_REG(GLB_BASE,GLB_LDO12UHS,tmpVal);
    uhs_phy_delay_us(1);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_LDO12UHS,0x0);
    BL_WR_REG(GLB_BASE,GLB_LDO12UHS,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DMY1,0xff);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_40,tmpVal);
    uhs_phy_delay_us(2);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_PU_UHSPLL_SFREG,0x0);
    BL_WR_REG(GLB_BASE,GLB_LDO12UHS,tmpVal);
    uhs_phy_delay_us(1);  
}

void psram_init(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_ADDRMB_MSK,0x3f); // 3F -> 512Mb psram, 1F -> 256Mb psram
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_LINEAR_BND_B,0xb);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_INIT_EN,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x1);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
    uhs_phy_delay_us(1);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_GLBR_PULSE,0x1);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD,tmpVal);  
    uhs_phy_delay_us(10);   // wait for reg_config_gnt
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x0);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);

    // psram auto refresh at 2000Mbps
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_WIN_CYCLE,0x001E0C4);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_1,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_WIN_REF_CNT,0x1007);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_REFI_CYCLE,0x01d);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_2,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_BUST_CYCLE,0x1);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_4,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_MANUAL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_PCK_T_DIV,0x40);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_MANUAL,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_AF_EN,0x1);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);

    // psram cmd timing < 2000Mbps
    BL_WR_WORD(0x3000F030,0x18090610);
}

void set_uhspll_freq(uint32_t datarate)
{
    uint32_t tmpVal = 0;
    uint32_t uhspll_sdmin = 0;
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_SEL_SAMPLE_CLK,0x1);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG4,tmpVal);
    uhspll_sdmin = (datarate/(40/2))<<11;
    if(datarate > 1000)
    {
        tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG5);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_VCO_POSTDIV_SEL,0x0);
        BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG5,tmpVal);
    }
    else if(datarate > 500)
    {
        uhspll_sdmin = uhspll_sdmin<<1;
        tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG5);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_VCO_POSTDIV_SEL,0x1);
        BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG5,tmpVal);
    }
    else
    {
        uhspll_sdmin = uhspll_sdmin<<2;
        tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG5);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_VCO_POSTDIV_SEL,0x2);
        BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG5,tmpVal);
    }
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG6);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_UHSPLL_SDMIN,uhspll_sdmin);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG6,tmpVal);
    uhs_phy_delay_us(30);

    //reset PLL
        /* toggle sdm_reset (pulse 0 > 1us) */
    /* cfg0 : aupll_sdm_reset */
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UHSPLL_SDM_RSTB, 1);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UHSPLL_SDM_RSTB, 0);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UHSPLL_SDM_RSTB, 1);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);

    /* Step3:reset pll */
    /* cfg0 : toggle aupll_reset_fbdv, pulse 0 > 1us */
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UHSPLL_FBDV_RSTB, 1);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UHSPLL_FBDV_RSTB, 0);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);
    arch_delay_us(2);
    tmpVal = BL_RD_REG(GLB_BASE,GLB_UHS_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UHSPLL_FBDV_RSTB, 1);
    BL_WR_REG(GLB_BASE,GLB_UHS_PLL_CFG0,tmpVal);
        
    uhs_phy_delay_us(30);
}

void set_uhs_phy_init(void)
{
    // set phy & controller
    uint32_t tmpVal = 0;
    // default latency(800MHz)
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_ANA,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_DIG,0x7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_ANA,0x0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_DIG,0x2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_DQ_ANA,0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_DQ_DIG,0x2);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_34,0x09020303);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_38,0x040c0313);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_3C,0x07d11515);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_44,0x060f050c);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_WL_CEN_ANA,0x1);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50,tmpVal);     
}  

void set_uhs_phy(void)
{
    // set phy & controller
    // latency code=3 (1066MHz)
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,0x0f0a1323);  // if fail than use 0x0f391323 
    // BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,0x0f0a0313);  //for 400Mbps
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_34,0x0b030404);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_38,0x050e0418);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_3C,0x0a6a1c1c);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_44,0x07110710);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_50,0x01333333);    
} 

void uhs_reg_w(uint32_t uhs_latency,uint32_t uhs_drive,uint32_t ma,uint32_t BL_32)
{
    uint32_t tmpVal = 0;
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
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_64,0x0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_32,BL_32);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_BL_16,0x0);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_PSRAM_CONFIGURE,tmpVal);
    }
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_MODE_REG,ma); //reg_mode_reg
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x1);  //reg_config_req
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
    while (1)
    {
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_GNT);
        if (tmpVal == 1)
            break;
    }
    
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_REGW_PULSE,0x1);  //reg_regw_pulse
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD,tmpVal);
    while (1)
    {
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_STS_REGR_DONE);
        if (tmpVal == 1)
            break;
    }
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x0);  //reg_config_req
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
}

void uhs_reg_r(uint32_t ma)
{
    uint32_t tmpVal = 0;
    uint32_t tmpInd = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_MODE_REG,ma); //reg_mode_reg
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x1);  //reg_config_req
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);

    // uhs_phy_delay_us(10);
    while (1)
    {
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_GNT);
        if (tmpVal == 1)
            break;
    }
    
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_REGR_PULSE,0x1);  //reg_regw_pulse
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD,tmpVal);
    // uhs_phy_delay_us(1);
    tmpInd = 0;
    while (1)
    {
        tmpInd++;
        uhs_phy_delay_us(1);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
        tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_STS_REGR_DONE);
        if (tmpVal == 1 || tmpInd == 2){
            //debug
			if (tmpInd == 2){
                uhs_phy_printf_debug("tmpInd = %ld\r\n",tmpInd);
            }
            break;
        }          
    }

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_CONFIG_REQ,0x0);  //reg_config_req
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);
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
}

void cfg_dqs_rx(uint8_t dqs){
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS0_DIFF_DLY_RX,dqs);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS1_DIFF_DLY_RX,dqs);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C,tmpVal);    
}

void cfg_ck_cen_drv(uint8_t array_ck_dly_drv,uint8_t array_cen_dly_drv){
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_CK_DLY_DRV,array_ck_dly_drv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_CEN_DLY_DRV,array_cen_dly_drv);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00,tmpVal);
}

void uhs_reset(uint32_t datarate)
{
	uint32_t tmpVal = 0;
	
	tmpVal = BL_RD_WORD(0x30007044);
	tmpVal = tmpVal | 0x00008000;
	BL_WR_WORD(0x30007044,tmpVal);
	uhs_phy_delay_us(10);
	tmpVal = tmpVal & 0xFFFF7FFF;
	BL_WR_WORD(0x30007044,tmpVal);
	
	BL_WR_WORD(0x3000F030,0x18090610);
	
	PSRAM_UHS_Cfg_Type psramCfg = {
		datarate,
		PSRAM_MEM_SIZE_64MB,
		PSRAM_PAGE_SIZE_2KB,
		0,
    };
	Psram_UHS_Init(&psramCfg); //controller init
	
    set_or_uhs();
	set_uhs_phy();
}

void reg_read_cal(uint32_t datarate)
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal_1 = 0;
    uint32_t uhs_latency = 42;
    int32_t i = 0;
    uint8_t dqs_dq_flag = 0;
    uint32_t reg_dqs = 0;
    uint32_t reg_dq = 0;

    for(uhs_latency = 41; uhs_latency > 0; uhs_latency --)
    {
        if(uhs_latency == 34)
        {
            uhs_phy_printf("reg read cal error\r\n");
            while(1){
                uhs_phy_printf(".");
                uhs_phy_delay_us(100000);
            };
            // break;
        }

        uhs_phy_printf_debug("reg read cal by latency=%ld\r\n",uhs_latency);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_ANA,uhs_latency%4);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_DIG,uhs_latency/4);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
    
        // sweep dqs
        cfg_dq_rx(0);
        for(i = 15; i >= 0; i --)
        {
            cfg_dqs_rx(i);

            uhs_reg_r(0); 
			tmpVal_1 = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);  //high temp failure workaround 
            tmpVal_1 = BL_GET_REG_BITS_VAL(tmpVal_1,PSRAM_UHS_STS_REGR_DONE);
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
            if(tmpVal == ((2<<3)+uhs_latency_code)&& (tmpVal_1 == 1))
            {
                uhs_phy_printf_debug("reg read pass by dqs=%ld\r\n",i); 
                reg_dqs = i;
                dqs_dq_flag = 1;
                break;
            }              
            else
            {
                uhs_phy_printf_debug("reg read fail by dqs=%ld\r\n",i);
            }
			
			tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
			tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_STS_REGR_DONE);
			if(tmpVal == 0)
			{
				uhs_phy_printf_debug("read done not found!!!");
				uhs_reset(datarate);
				tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
				tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_ANA,uhs_latency%4);
				tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_DIG,uhs_latency/4);
				BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
				cfg_dq_rx(0);
			}
                
        }

        // sweep dq 
        cfg_dqs_rx(0);
        for(i = 15; i >=0; i --)
        {
            cfg_dq_rx(i);

            uhs_reg_r(0);
            tmpVal_1 = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);  //high temp failure workaround 
            tmpVal_1 = BL_GET_REG_BITS_VAL(tmpVal_1,PSRAM_UHS_STS_REGR_DONE);
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
            if(tmpVal == ((2<<3)+uhs_latency_code)&& (tmpVal_1 == 1))
            {
                uhs_phy_printf_debug("reg read pass by dq=%ld\r\n",i);
                reg_dq = i;
                dqs_dq_flag = 1;
                break; 
            }  
            else
            {
                uhs_phy_printf_debug("reg read fail by dq=%ld\r\n",i);
            }
            
			tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);
			tmpVal = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_STS_REGR_DONE);
			if(tmpVal == 0)
			{
				uhs_phy_printf_debug("read done not found!!!");
				uhs_reset(datarate);
				tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
				tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_ANA,uhs_latency%4);
				tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_DIG,uhs_latency/4);
				BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
				cfg_dqs_rx(0);
			}
			
        }    

        if (dqs_dq_flag == 1){
            uhs_latency = uhs_latency - 2;
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_ANA,uhs_latency%4);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_DIG,uhs_latency/4);
            BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
            //sweep dqs
            cfg_dq_rx(0);
            for(i = 15; i >= 0; i --)
            {
                cfg_dqs_rx(i);
                uhs_reg_r(0); 
                tmpVal_1 = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);  //high temp failure workaround 
                tmpVal_1 = BL_GET_REG_BITS_VAL(tmpVal_1,PSRAM_UHS_STS_REGR_DONE);
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
                if(tmpVal == ((2<<3)+uhs_latency_code)&& (tmpVal_1 == 1))
                {
                    uhs_phy_printf_debug("reg read pass by dqs=%ld\r\n",i); 
                    reg_dqs = i;
                    dqs_dq_flag = 1;
                    break; 
                }              
                else{
                    uhs_phy_printf_debug("reg read fail by dqs=%ld\r\n",i);
                }
            }
            // sweep dq 
            cfg_dqs_rx(0);
            for(i = 15; i >=0; i --)
            {
                cfg_dq_rx(i);

                uhs_reg_r(0);
                tmpVal_1 = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);  //high temp failure workaround 
                tmpVal_1 = BL_GET_REG_BITS_VAL(tmpVal_1,PSRAM_UHS_STS_REGR_DONE);
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
                if(tmpVal == ((2<<3)+uhs_latency_code)&& (tmpVal_1 == 1))
                {
                    uhs_phy_printf_debug("reg read pass by dq=%ld\r\n",i);
                    reg_dq = i;
                    dqs_dq_flag = 1;
                    break;
                }  
                else{
                    uhs_phy_printf_debug("reg read fail by dq=%ld\r\n",i);
                }
            }
            
            if(reg_dqs > reg_dq)
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
            uhs_reg_r(0);
            uhs_phy_printf("reg read cal pass, latency=%ld, dqs=%ld, dq=%ld\r\n",uhs_latency,reg_dqs,reg_dq);

            break;
        }
    }
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
}

void cfg_dqs_drv(uint32_t dqs){
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS0_DLY_DRV,dqs);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_28,tmpVal);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQS1_DLY_DRV,dqs);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_2C,tmpVal);
}

void reg_write_cal(void)  //only need sweep dqs
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal_1 = 0;
    int32_t i = 0;
    uint32_t reg_dqs;
    uint32_t reg_dq = 0;
    uint32_t reg_dqs1 = 0;
    uint32_t reg_dqs2 = 0;
    uint8_t dqs_dq_flag = 0;

    // sweep1 dqs
    for(i = 15; i >=0; i --)
    {
        cfg_dqs_drv(i); 
        uhs_reg_w(uhs_latency_code,2,2,1); //BL_32 == 1
        uhs_reg_r(2);
        tmpVal_1 = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);  //high temp failure workaround 
        tmpVal_1 = BL_GET_REG_BITS_VAL(tmpVal_1,PSRAM_UHS_STS_REGR_DONE);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
        if((tmpVal == 16) && (tmpVal_1 == 1))
            {
                uhs_phy_printf("reg write pass by -- dqs1=%ld\r\n",i); 
                reg_dqs1 = i;
                dqs_dq_flag = 1;
                break; 
            }              
        else{
            uhs_phy_printf_debug("reg write fail by -- dqs1=%ld\r\n",i);
        }
    }        
    // sweep2 dqs 
    for(i = 0; i <=15; i ++)
    {
        cfg_dqs_drv(i);
        uhs_reg_w(uhs_latency_code,2,2,1);  //BL_32 == 1
        uhs_reg_r(2);
        tmpVal_1 = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);  //high temp failure workaround 
        tmpVal_1 = BL_GET_REG_BITS_VAL(tmpVal_1,PSRAM_UHS_STS_REGR_DONE);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
        if((tmpVal == 16) && (tmpVal_1 == 1))
            {
                uhs_phy_printf("reg write pass by ++ dqs2=%ld\r\n",i);
                reg_dqs2 = i;
                dqs_dq_flag = 1;
                break; 
            }              
        else{
            uhs_phy_printf_debug("reg write fail by ++ dqs2=%ld\r\n",i);
        }
    }           

    if(dqs_dq_flag == 0)
    {
        uhs_phy_printf("reg write cal error 0\r\n");
        while(1){
            uhs_phy_printf(".");
            uhs_phy_delay_us(100000);
        };
        // break;
    }
    
    reg_dqs = (reg_dqs1 + reg_dqs2) / 2 ;
    // set dqs by register write cal result 
    cfg_dqs_drv(reg_dqs);
    uhs_reg_w(uhs_latency_code,2,2,0); //BL_32 == 0
    uhs_reg_r(2);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
    if(tmpVal == 0)
    {
        uhs_phy_printf("reg write cal pass dqs=%ld, dq=%ld\r\n",reg_dqs,reg_dq);
    }              
    else{
        uhs_phy_printf("reg write cal error 1\r\n");
        while(1){
            uhs_phy_printf(".");
            uhs_phy_delay_us(100000);
        };
        // break;
    }
    
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_08);
    reg_dq = BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_DQ0_DLY_DRV);
    dqs_dq_delta = 16 + reg_dqs - reg_dq;
    uhs_phy_printf("reg_write_cal return dqs_dq_delta=%ld\r\n",dqs_dq_delta);
    // return dqs_dq_delta;
}

void array_write_fix(uint32_t addr,uint32_t len,uint32_t data0,uint32_t data1)
{
    uint32_t addr_tmp = addr;
    uint32_t data = data0;
    int32_t i = 0;
    for(i = 0; i < (len>>2); i ++)
    {
        addr_tmp = (i << 2) + addr;
        if(i % 2 == 0)
            data = data0 + i;
        else
            data = data1 + i;
        BL_WR_WORD(addr_tmp,data); 
    }
}
uint32_t array_read_fix(uint32_t addr,uint32_t len,uint32_t data0,uint32_t data1)
{
    uint32_t array_read_pass = 1;
    uint32_t addr_tmp = addr;
    uint32_t data = data0;
    uint32_t data_read = 0;
    int32_t i = 0;
  
    for(i = 0; i < (len>>2); i ++)
    {
        addr_tmp = (i << 2) + addr;
        data_read = BL_RD_WORD(addr_tmp);
        if(i % 2 == 0)
            data = data0 + i;
        else
            data = data1 + i;
        if(data_read != data){
            array_read_pass = 0;
            break;
        }
    }
    return array_read_pass;
}

void set_ck_dly_drv(uint32_t array_ck_dly_drv)
{
    uint32_t array_dqx_dly_drv = 0;
    uint32_t array_dqsx_dly_drv = 0;
    uint32_t array_cen_dly_drv = 0;

    arch_delay_us(1);  // ck modify need time

    array_dqx_dly_drv = (array_ck_dly_drv >=4) ? (array_ck_dly_drv-4) : 0;
    array_cen_dly_drv = array_dqx_dly_drv + 1;
    // array_dqsx_dly_drv = ((int32_t)((int32_t)(dqs_dq_delta)+(int32_t)(array_dqx_dly_drv))<0)?0:(array_dqx_dly_drv + dqs_dq_delta);
    array_dqsx_dly_drv =  (dqs_dq_delta + array_dqx_dly_drv >= 16) ? (dqs_dq_delta + array_dqx_dly_drv - 16) : 0;

    // array_dqsx_dly_drv = (array_dqx_dly_drv > 15) ? 15 : array_dqsx_dly_drv;
    array_dqx_dly_drv = (array_dqx_dly_drv > 15) ? 15 : array_dqx_dly_drv;
    array_cen_dly_drv = (array_cen_dly_drv > 15) ? 15 : array_cen_dly_drv;
    array_dqsx_dly_drv = (array_dqsx_dly_drv > 15) ? 15 : array_dqsx_dly_drv;

    cfg_dq_drv(array_dqx_dly_drv);
    cfg_dqs_drv(array_dqsx_dly_drv);
    cfg_ck_cen_drv(array_ck_dly_drv,array_cen_dly_drv);

    arch_delay_us(10); // ck modify need time
}

void array_read_latency_cal(void)
{
    uint32_t tmpVal = 0;
    uint32_t uhs_latency = 42;
    uint32_t array_ck_dly_drv = 0;
    uint32_t flag = 0;

    uint32_t dig = 0;
    uint32_t ana = 0;
    uint32_t latency = 0;

    array_write_fix(0x50000000,128,0x12345678,0x87654321);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
    dig = (tmpVal >> 16) & 0xF;
    ana = (tmpVal >> 20) & 0x7;
    latency = (dig<<2) + ana;

    for(uhs_latency = latency; uhs_latency > 0; uhs_latency --)
    {
        if(uhs_latency == 34)
        {
            uhs_phy_printf("array read latency cal error\r\n");
            while(1){
                uhs_phy_printf(".");
                uhs_phy_delay_us(100000);
            };
            // break;
        }

        uhs_phy_printf_debug("array read cal by latency=%ld\r\n",uhs_latency);
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_ANA,uhs_latency%4);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_DIG,uhs_latency/4);
        BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);

        array_ck_dly_drv = 11;
        set_ck_dly_drv(array_ck_dly_drv);

        flag = array_read_fix(0x50000000,128,0x12345678,0x87654321);

        if(flag == 1)
        {
            uhs_phy_printf_debug("array read pass by ck == 11\r\n"); 
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_ANA,uhs_latency%4);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_DIG,uhs_latency/4);
            BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
            uhs_phy_printf("array read latency cal pass, latency=%ld, ck=%ld\r\n",uhs_latency,array_ck_dly_drv);
            break;
        }              
        else
        {
            uhs_phy_printf_debug("array read fail by ck == 11\r\n");
            array_ck_dly_drv = 4;
            set_ck_dly_drv(array_ck_dly_drv);
            flag = array_read_fix(0x50000000,128,0x12345678,0x87654321);
            if(flag == 1)
            {
                uhs_phy_printf_debug("array read pass by ck == 4\r\n"); 
                // uhs_latency = uhs_latency - 2;
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_ANA,uhs_latency%4);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_PHY_RL_DIG,uhs_latency/4);
                BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_30,tmpVal);
                uhs_phy_printf("array read latency cal pass, latency=%ld, ck=%ld\r\n",uhs_latency,array_ck_dly_drv);
                break;
            }              
            else{
                uhs_phy_printf_debug("array read fail by ck == 4\r\n");
            }
        }   
    }
}

void array_write_ck_cal(void) 
{
    uint32_t array_ck_dly_drv = 0;
    uint32_t array_ck_dly_drv1 = 0;
    uint32_t array_ck_dly_drv2 = 0;
    uint32_t flag = 0;

    array_write_fix(0x50000000,1024,0x12345678,0x87654321);

    for(array_ck_dly_drv = 15; array_ck_dly_drv >= 4; array_ck_dly_drv --)
    {
        set_ck_dly_drv(array_ck_dly_drv);
            
        flag = array_read_fix(0x50000000,1024,0x12345678,0x87654321);
        if(flag == 0){
            uhs_phy_printf_debug("array write ck cal fail by ck=%ld\r\n",array_ck_dly_drv);
            array_ck_dly_drv1 = array_ck_dly_drv;
            break;
        }
    }

    if(flag == 1){
        array_ck_dly_drv = (15 + 4) / 2;
        set_ck_dly_drv(array_ck_dly_drv);

        uhs_phy_printf("array write ck cal pass, ck=%ld\r\n",array_ck_dly_drv);
        return;
    }

    for(array_ck_dly_drv = 4; array_ck_dly_drv <= 15; array_ck_dly_drv ++)
    {
        set_ck_dly_drv(array_ck_dly_drv);
            
        flag = array_read_fix(0x50000000,1024,0x12345678,0x87654321);
        if(flag == 0){
            uhs_phy_printf_debug("array write ck cal fail by ck=%ld\r\n",array_ck_dly_drv);
            array_ck_dly_drv2 = array_ck_dly_drv;
            break;
        }
    }

    if(array_ck_dly_drv1 == 15 && array_ck_dly_drv2 == 4)
    {
        uhs_phy_printf_debug("array write ck cal error\r\n");
        while(1){
            uhs_phy_printf(".");
            uhs_phy_delay_us(100000);
        };
        // break;
    }
    if ((15 - array_ck_dly_drv1) >= (array_ck_dly_drv2 - 4))
    {
        array_ck_dly_drv = 15;
    }
    else
    {
        array_ck_dly_drv = 4;
    } 
    
    set_ck_dly_drv(array_ck_dly_drv);
    
    uhs_phy_printf("array write ck cal pass, ck=%ld\r\n",array_ck_dly_drv);

}

void array_read_dqs_dq_cal(void)
{
    // uint32_t tmpVal = 0;
    int32_t i = 0;
    uint32_t array_dqs = 0;
    uint32_t array_dq = 0;
    uint32_t dqs_flag;
    uint32_t dq_flag;
    array_write_fix(0x50000000,128,0x12345678,0x87654321);
    // sweep dqs
    cfg_dq_rx(0);

    for(i = 15; i >= 0; i --)
    {
        cfg_dqs_rx(i);
        dqs_flag = array_read_fix(0x50000000,128,0x12345678,0x87654321);
        if(dqs_flag == 1)
        {
            uhs_phy_printf_debug("array_read_dqs_dq_cal pass by dqs%ld\r\n",i); 
            array_dqs = i;
            break; 
        }
    }
    // sweep dq 
    cfg_dqs_rx(0);
    for(i = 15; i >=0; i --)
    {
        cfg_dq_rx(i);
        dq_flag = array_read_fix(0x50000000,128,0x12345678,0x87654321);
        if(dq_flag == 1)
        {
            uhs_phy_printf_debug("array_read_dqs_dq_cal pass by dq%ld\r\n",i);  
            array_dq = i;
            break; 
        }                  
    }
    if(dqs_flag == 0 && dq_flag == 0)
    {
        uhs_phy_printf("array_read_dqs_dq_cal error\r\n");
        while(1)
        {
            uhs_phy_printf(".");
            uhs_phy_delay_us(100000);
        };
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
    uhs_phy_printf("array_read_dqs_dq_cal pass by array_dqs=%ld, array_dq=%ld\r\n",array_dqs,array_dq);
}

void array_write_dqs_dq_cal(void)
{
    uint32_t tmpVal = 0;
    int32_t i = 0;
    uint32_t dqs_flag = 0;
    uint32_t array_dqs_dly_drv = 0;
    uint32_t array_dqs_dly_drv1 = 0;
    uint32_t array_dqs_dly_drv2 = 0;

    for(i = 15; i >= 0; i --)
    {  
        cfg_dqs_drv(i);  
        array_write_fix(0x50000000,128,0x12345678,0x87654321);
        dqs_flag = array_read_fix(0x50000000,128,0x12345678,0x87654321);
        if(dqs_flag == 1)
        {
            uhs_phy_printf("array_write_dqs_dq_cal pass by -- dqs1=%ld\r\n",i);
            array_dqs_dly_drv1 = i;
            break;  
        }              
        else
        {
            uhs_phy_printf_debug("array_write_dqs_dq_cal fail by -- dqs1=%ld\r\n",i);
        }
    }
    for(i = 0; i <= 15; i ++)
    {
        cfg_dqs_drv(i);
        array_write_fix(0x50000000,128,0x12345678,0x87654321);
        dqs_flag = array_read_fix(0x50000000,128,0x12345678,0x87654321);
        if(dqs_flag == 1)
        {
            uhs_phy_printf("array_write_dqs_dq_cal pass by ++ dqs2=%ld\r\n",i);
            array_dqs_dly_drv2 = i;
            break;
        }              
        else
        {
            uhs_phy_printf_debug("array_write_dqs_dq_cal fail by ++ dqs2=%ld\r\n",i);
        }
    }
    if(dqs_flag == 0)
    {
        uhs_phy_printf("array_write_dqs_dq_cal error\r\n");
        while(1)
        {
            uhs_phy_printf(".");
            uhs_phy_delay_us(100000);
        };
    }
    array_dqs_dly_drv = (array_dqs_dly_drv1 + array_dqs_dly_drv2) / 2 ;
    // if ck_dly_drv = 4, fix dqsx_dly_drv to 0
	tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_PHY_CFG_00);
	tmpVal = (tmpVal >> 16) & 0xF;
	if(tmpVal == 4)
	{
		array_dqs_dly_drv = 0;
	}
    uhs_phy_printf("array_write_dqs_dq_cal pass by array_dqs_dly_drv=%ld\r\n",array_dqs_dly_drv);
    // set dqs by register write cal result 
    cfg_dqs_drv(array_dqs_dly_drv);
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
    
    GLB_Power_Off_MU_PLL(GLB_MU_PLL_UHSPLL);
    GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_UHSPLL, refClk);
    GLB_Power_On_MU_PLL(GLB_MU_PLL_UHSPLL, &(uhsPllCfg[xtalType]), 1);
    
    return SUCCESS;
}

void self_cal(uint32_t datarate)
{   
    // int32_t P1= 0;
    uint32_t tmpVal = 0;
    // uint32_t uhs_latency = 0;

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

    PSRAM_UHS_Cfg_Type psramCfg = {
        datarate,
        PSRAM_MEM_SIZE_64MB,
        PSRAM_PAGE_SIZE_2KB,
        0,
    };

	// set to 2000Mbps
    uhs_reg_w(uhs_latency_code,2,0,0); // BL_32 == 0
    // set_uhspll_freq(datarate); // use SW function later
    GLB_Config_UHS_PLL_Freq(GLB_XTAL_40M,datarate);   //stuck
    Psram_UHS_Init(&psramCfg); //controller init
    set_uhs_phy();
	
    // check reg read 
    uhs_reg_r(0);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
    if(tmpVal == ((2<<3)+uhs_latency_code)){
        uhs_phy_printf("register write pass at 1400Mbps and read pass at %ldMbps\r\n",datarate);
    }    
    else{
        uhs_phy_printf("register write fail at 1400Mbps or read fail at %ldMbps\r\n",datarate);
    }

    // register read latency & dqs & dq calibration
    reg_read_cal(datarate);
    // register write dqs & dq calibration
    reg_write_cal();
    uhs_reg_w(uhs_latency_code,2,2,0); // BL_32 == 0
    uhs_reg_r(2);
    // array read latency calibration 
    array_read_latency_cal();
    // array write ck calibration
    array_write_ck_cal();
    // array read dqs & dq calibration
    array_read_dqs_dq_cal();
    // array write dqs & dq calibration
    array_write_dqs_dq_cal();
}

void soft_reset(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(GLB_BASE,GLB_SWRST_CFG2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_CTRL_PWRON_RST,0x1); // soft power on reset
    BL_WR_REG(GLB_BASE,GLB_SWRST_CFG2,tmpVal);
}

void uhs_phy_init(uint32_t datarate)
{
    uhs_phy_printf_debug("uhs phy init\r\n");
    power_up_mm();
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

    PSRAM_UHS_Cfg_Type psramCfg = {
        1400,
        PSRAM_MEM_SIZE_64MB,
        PSRAM_PAGE_SIZE_2KB,
        0,
    };

    // set_uhspll_freq(1400);      // 700MHz is prefer , use SW function later
    GLB_Config_UHS_PLL_Freq(GLB_XTAL_40M,1400);    //stuck
    Psram_UHS_Init(&psramCfg);  // controller init
    set_uhs_phy_init();         // phy init
    psram_init();               // psram init after set freq & set_phy

    uhs_reg_r(0);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD)>>24;
    if(tmpVal == ((2<<3)+1))    // 1400M --> default uhs_latency_code == 1
    {
        uhs_phy_printf_debug("register read pass at datarate at 1400Mbps\r\n");
    }  
    else{
        uhs_phy_printf_debug("register read fail at datarate at 1400Mbps\r\n");
    }  
    
    //get dcache original state
    __DSB();
    __ISB();
    dcache_original = __get_MHCR();
    dcache_original &= (0x1<<1);
    __DSB();
    __ISB();
    uhs_phy_printf("dcache_original=%lx\r\n",dcache_original);

    csi_dcache_disable();

    //get dcache current state
    __DSB();
    __ISB();
    dcache_current = __get_MHCR();
    dcache_current &= (0x1<<1);
    __DSB();
    __ISB();
    uhs_phy_printf("dcache_current=%lx\r\n",dcache_current);

    if(dcache_current == 0x0)
    {
        self_cal(datarate);
    }
    else
    {
        uhs_phy_printf("dcache disable fail\r\n");
    }
     
    if (dcache_original == (0x1<<1))
    {     
            csi_dcache_enable();       
    }

    //get dcache end state
    __DSB();
    __ISB();
    dcache_end = __get_MHCR();
    dcache_end &= (0x1<<1);
    __DSB();
    __ISB();
    if(dcache_end == dcache_original)
    {
        uhs_phy_printf("dcache state right , dcache_state=%lx\r\n",dcache_end);
    }
    else
    {
        uhs_phy_printf("dcache state error\r\n");
    }

    uhs_phy_delay_us(1000);

}