/**
  ******************************************************************************
  * @file    bl808_psram_uhs.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL808_PSRAM_UHS_H__
#define __BL808_PSRAM_UHS_H__

#include "psram_uhs_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PSRAM_UHS
 *  @{
 */

/** @defgroup  PSRAM_UHS_Public_Types
 *  @{
 */

/**
 *  @brief Psram UHS Size
 */
typedef enum {
    PSRAM_MEM_SIZE_4MB = 0x03,  /*!< PSRAM Memory Size 4M */
    PSRAM_MEM_SIZE_8MB = 0x07,  /*!< PSRAM Memory Size 8M */
    PSRAM_MEM_SIZE_16MB = 0x0f, /*!< PSRAM Memory Size 16M */
    PSRAM_MEM_SIZE_32MB = 0x1f, /*!< PSRAM Memory Size 32M */
    PSRAM_MEM_SIZE_64MB = 0x3f, /*!< PSRAM Memory Size 64M */
} PSRAM_UHS_Mem_Size_Type;

/**
 *  @brief Psram UHS Page Type
 */
typedef enum {
    PSRAM_PAGE_SIZE_2KB = 0x0B, /*!< PSRAM Page Size 2KB */
    PSRAM_PAGE_SIZE_4KB = 0x16, /*!< PSRAM Page Size 4KB */
} PSRAM_UHS_Page_Size_Type;

/**
 *  @brief Psram UHS Burst Size
 */
typedef enum {
    PSRAM_UHS_WARP_BURST_64,        /*!< PSRAM Warp Burst Size 64 */
    PSRAM_UHS_WARP_BURST_32,        /*!< PSRAM Warp Burst Size 32 */
    PSRAM_UHS_WARP_BURST_16,        /*!< PSRAM Warp Burst Size 16 */
    PSRAM_UHS_WARP_BURST_NONE,      /*!< PSRAM Warp Burst NONE */
    PSRAM_UHS_WARP_BURST_NO_CHANGE, /*!< Not change this value */
} PSRAM_UHS_WARP_BURST_Type;

/**
 *  @brief Psram UHS Driver Strength
 */
typedef enum {
    PSRAM_UHS_DRIVER_ST_34P3_PDPU = 0x1,     /*!< 34.3 PD/PU */
    PSRAM_UHS_DRIVER_ST_40_PDPU = 0x2,       /*!< 40 PD/PU */
    PSRAM_UHS_DRIVER_ST_48_PDPU = 0x3,       /*!< 48 PD/PU */
    PSRAM_UHS_DRIVER_ST_60_PDPU = 0x4,       /*!< 60 PD/PU */
    PSRAM_UHS_DRIVER_ST_80_PDPU = 0x6,       /*!< 80 PD/PU */
    PSRAM_UHS_DRIVER_ST_34P3_PD_40_PU = 0x9, /*!< 34.3 PD & 40 PU */
    PSRAM_UHS_DRIVER_ST_40_PD_48_PU = 0xa,   /*!< 40 PD & 48 PU */
    PSRAM_UHS_DRIVER_ST_34P3_PD_48_PU = 0xb, /*!< 34.3 PD & 48 PU */
    PSRAM_UHS_DRIVER_ST_NO_CHANGE = 0xf,     /*!< Not change this value */
} PSRAM_UHS_DRIVER_ST_Type;

/**
 *  @brief Psram UHS LATENCY
 */
typedef enum {
    PSRAM_UHS_LATENCY_W10_R20_MAX_FRE_533_MHZ,  /*!< MAX freq. = 533 MHz / Write LATENCY=10 / Read LATENCY=20 */
    PSRAM_UHS_LATENCY_W14_R29_MAX_FRE_800_MHZ,  /*!< MAX freq. = 800 MHz / Write LATENCY=14 / Read LATENCY=29 */
    PSRAM_UHS_LATENCY_W16_R33_MAX_FRE_933_MHZ,  /*!< MAX freq. = 933 MHz / Write LATENCY=16 / Read LATENCY=33 */
    PSRAM_UHS_LATENCY_W18_R37_MAX_FRE_1066_MHZ, /*!< MAX freq. = 1066 MHz / Write LATENCY=18 / Read LATENCY=37 */
    PSRAM_UHS_LATENCY_RESERVED,                 /*!< Reserved */
    PSRAM_UHS_LATENCY_W6_R16_MAX_FRE_400_MHZ,   /*!< MAX freq. = 400 MHz / Write LATENCY=6 / Read LATENCY=16 */
    PSRAM_UHS_LATENCY_W5_R13_MAX_FRE_333_MHZ,   /*!< MAX freq. = 333 MHz / Write LATENCY=5 / Read LATENCY=13 */
    PSRAM_UHS_LATENCY_W5_R9_MAX_FRE_200_MHZ,    /*!< MAX freq. = 200 MHz / Write LATENCY=5 / Read LATENCY=9 */
    PSRAM_UHS_LATENCY_NO_CHANGE,                /*!< Not change this value */
} PSRAM_UHS_LATENCY_Type;

/**
 *  @brief Psram UHS CMD Type
 */
typedef enum {
    PSRAM_UHS_CMD_SELF_REFRESH_IN,   /*!< pSRAM self-refresh in command */
    PSRAM_UHS_CMD_SELF_REFRESH_EXIT, /*!< pSRAM self-refresh exit command */
    PSRAM_UHS_CMD_GLOBAL_RESET,      /*!< pSRAM global reset command */
    PSRAM_UHS_CMD_ZQ_CAL_LONG,       /*!<ZQ calibration, long> */
    PSRAM_UHS_CMD_ZQ_CAL_SHORT,      /*!<ZQ calibration, short>*/
    PSRAM_UHS_CMD_ZQ_CAL_RESET,      /*!<ZQ calibration,reset>*/
} PSRAM_UHS_CMD_Type;

/**
 * @brief PSRAM UHS Temperature
 *
 */
typedef enum {
    PSRAM_UHS_NORMAL_TEMP,
    PSRAM_UHS_HIGH_TEMP,
} PSRAM_UHS_TEMP_Type;

/**
 *  @brief PSRAM_UHS_Cfg_Type
 */
typedef struct {
    uint32_t pck_freq;                      /*!< pck frequency unit is MHZ */
    PSRAM_UHS_Mem_Size_Type psramMemSize;   /*!< psram uhm memory size */
    PSRAM_UHS_Page_Size_Type psramPageSize; /*!< psram uhm page size */
    PSRAM_UHS_TEMP_Type isHighTem;          /*!< auto refresh work temperature */
} PSRAM_UHS_Cfg_Type;

/**
 *  @brief PSRAM_UHS_Phy_Latency_Pra_Type
 */
typedef struct {
    uint8_t phy_rl_ana;    /*!< phy_rl_ana */
    uint8_t phy_rl_dig;    /*!< phy_rl_dig*/
    uint8_t phy_wl_ana;    /*!< phy_wl_ana */
    uint8_t phy_wl_dig;    /*!< phy_wl_dig*/
    uint8_t phy_wl_dq_ana; /*!< phy_wl_dq_ana */
    uint8_t phy_wl_dq_dig; /*!< phy_wl_dq_dig */

    uint8_t reg_timer_array_read;     /*!< reg_timer_array_read */
    uint8_t reg_timer_array_write;    /*!< reg_timer_array_write */
    uint8_t reg_timer_dqs_array_stop; /*!< reg_timer_dqs_array_stop */
    uint8_t reg_timer_dqs_start;      /*!< reg_timer_dqs_start */

    uint8_t reg_timer_dqs_stop;     /*!< reg_timer_dqs_stop */
    uint8_t reg_timer_reg_read;     /*!< reg_timer_reg_read */
    uint8_t reg_timer_reg_write;    /*!< reg_timer_reg_write */
    uint8_t reg_timer_auto_refresh; /*!< reg_timer_auto_refresh */

    uint16_t reg_timer_global_rst;        /*!< reg_timer_global_rst */
    uint8_t reg_timer_self_refresh1_in;   /*!< reg_timer_self_refresh1_in */
    uint8_t reg_timer_self_refresh1_exit; /*!< reg_timer_self_refresh1_exit */

    uint8_t reg_timer_reg_write_busy;    /*!< reg_timer_reg_write_busy */
    uint8_t reg_timer_reg_read_busy;     /*!< reg_timer_reg_read_busy */
    uint8_t reg_timer_arrary_write_busy; /*!< reg_timer_arrary_write_busy */
    uint8_t reg_timer_arrary_read_busy;  /*!< reg_timer_arrary_read_busy */

    uint8_t en_rx_fe_dly; /*!< en_rx_fe_dly */
    uint8_t odt_sel_dly;  /*!< odt_sel_dly */

    uint8_t reg_trc_cycle;   /*!< reg_trc_cycle */
    uint8_t reg_trfc_cycle;  /*!< reg_trfc_cycle */
    uint8_t reg_tcphr_cycle; /*!< reg_tcphr_cycle */
    uint8_t reg_tcphw_cycle; /*!< reg_tcphw_cycle */

} PSRAM_UHS_Phy_Latency_Pra_Type;

/**
 *  @brief PSRAM_UHS_Write_Reg_Cfg_Type
 */
typedef struct {
    PSRAM_UHS_DRIVER_ST_Type driver_st;   /*!< driver strength */
    PSRAM_UHS_WARP_BURST_Type burst_size; /*!< burst size */
    PSRAM_UHS_LATENCY_Type lentency;      /*!< lentency */
} PSRAM_UHS_Write_Reg_Cfg_Type;

/*@} end of group PSRAM_UHS_Public_Types */

/** @defgroup  PSRAM_UHS_Public_Constants
 *  @{
 */

/** @defgroup  PSRAM_UHS_MEM_SIZE_TYPE
 *  @{
 */
#define IS_PSRAM_UHS_MEM_SIZE_TYPE(type) (((type) == PSRAM_MEM_SIZE_4MB) ||  \
                                          ((type) == PSRAM_MEM_SIZE_8MB) ||  \
                                          ((type) == PSRAM_MEM_SIZE_16MB) || \
                                          ((type) == PSRAM_MEM_SIZE_32MB))

/** @defgroup  PSRAM_UHS_PAGE_SIZE_TYPE
 *  @{
 */
#define IS_PSRAM_UHS_PAGE_SIZE_TYPE(type) (((type) == PSRAM_PAGE_SIZE_2KB) || \
                                           ((type) == PSRAM_PAGE_SIZE_4KB))

/** @defgroup  PSRAM_UHS_WARP_BURST_TYPE
 *  @{
 */
#define IS_PSRAM_UHS_WARP_BURST_TYPE(type) (((type) == PSRAM_UHS_WARP_BURST_64) || \
                                            ((type) == PSRAM_UHS_WARP_BURST_32) || \
                                            ((type) == PSRAM_UHS_WARP_BURST_16))

/** @defgroup  PSRAM_UHS_DRIVER_ST_TYPE
 *  @{
 */
#define IS_PSRAM_UHS_DRIVER_ST_TYPE(type) (((type) == PSRAM_UHS_DRIVER_ST_34P3_PUPU) ||     \
                                           ((type) == PSRAM_UHS_DRIVER_ST_40_PUPU) ||       \
                                           ((type) == PSRAM_UHS_DRIVER_ST_48_PUPU) ||       \
                                           ((type) == PSRAM_UHS_DRIVER_ST_60_PUPU) ||       \
                                           ((type) == PSRAM_UHS_DRIVER_ST_80_PUPU) ||       \
                                           ((type) == PSRAM_UHS_DRIVER_ST_34P3_PD_40_PU) || \
                                           ((type) == PSRAM_UHS_DRIVER_ST_40_PD_48_PU) ||   \
                                           ((type) == PSRAM_UHS_DRIVER_ST_34P3_PD_48_PU))

/** @defgroup  PSRAM_UHS_LATENCY_TYPE
 *  @{
 */
#define IS_PSRAM_UHS_LATENCY_TYPE(type) (((type) == PSRAM_UHS_LATENCY_W10_R20_MAX_FRE_533_MHZ) ||  \
                                         ((type) == PSRAM_UHS_LATENCY_W14_R29_MAX_FRE_800_MHZ) ||  \
                                         ((type) == PSRAM_UHS_LATENCY_W16_R33_MAX_FRE_933_MHZ) ||  \
                                         ((type) == PSRAM_UHS_LATENCY_W18_R37_MAX_FRE_1066_MHZ) || \
                                         ((type) == PSRAM_UHS_LATENCY_W6_R16_MAX_FRE_400_MHZ) ||   \
                                         ((type) == PSRAM_UHS_LATENCY_W5_R13_MAX_FRE_333_MHZ) ||   \
                                         ((type) == PSRAM_UHS_LATENCY_W5_R9_MAX_FRE_200_MHZ))
/** @defgroup  PSRAM_UHS_CMD_Type
 *  @{
 */
#define IS_PSRAM_UHS_CMD_TYPE(type)                      (((type) == PSRAM_UHS_CMD_SELF_REFRESH_IN) || \
                                                          ((type) == PSRAM_UHS_CMD_SELF_REFRESH_EXIT) || \
                                                          ((type) == PSRAM_UHS_CMD_GLOBAL_RESET)

/*@} end of group PSRAM_UHS_Public_Constants */

/** @defgroup  PSRAM_UHS_Public_Macros
 *  @{
 */

/*@} end of group PSRAM_UHS_Public_Macros */

/** @defgroup  PSRAM_UHS_Public_Functions
 *  @{
 */
void Psram_UHS_Init(PSRAM_UHS_Cfg_Type *cfg);
int PSram_UHS_Read_Reg(uint32_t reg_addr, uint8_t *regVal);
int PSram_UHS_Write_Reg(PSRAM_UHS_Write_Reg_Cfg_Type *regCfg);
int PSram_UHS_Construct_Cmd(PSRAM_UHS_CMD_Type cmd);
void Psram_UHS_x16_Init(uint32_t uhs_pll_clk);
void Psram_UHS_x16_Init_Override(PSRAM_UHS_Cfg_Type *cfg);
/*@} end of group PSRAM_UHS_Public_Functions */

/*@} end of group PSRAM_UHS */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_PSRAM_UHS_H__ */
