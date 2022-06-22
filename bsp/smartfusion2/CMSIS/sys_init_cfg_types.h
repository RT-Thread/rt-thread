/*******************************************************************************
 * (c) Copyright 2012 Microsemi SoC Products Group.  All rights reserved.
 * 
 *  
 *
 * SVN $Revision: 4410 $
 * SVN $Date: 2012-07-16 14:36:17 +0100 (Mon, 16 Jul 2012) $
 */
 
#ifndef SYSTEM_INIT_CFG_TYPES_H_
#define SYSTEM_INIT_CFG_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif 

/*============================================================================*/
/*                              DDR Configuration                             */
/*============================================================================*/
typedef struct
{
    /*--------------------------------------------------------------------------
     * DDR Controller registers.
     */
    struct
    {
        uint16_t DYN_SOFT_RESET_CR;
        uint16_t RESERVED0;
        uint16_t DYN_REFRESH_1_CR;
        uint16_t DYN_REFRESH_2_CR;
        uint16_t DYN_POWERDOWN_CR;
        uint16_t DYN_DEBUG_CR;
        uint16_t MODE_CR;
        uint16_t ADDR_MAP_BANK_CR;
        uint16_t ECC_DATA_MASK_CR;
        uint16_t ADDR_MAP_COL_1_CR;
        uint16_t ADDR_MAP_COL_2_CR;
        uint16_t ADDR_MAP_ROW_1_CR;
        uint16_t ADDR_MAP_ROW_2_CR;
        uint16_t INIT_1_CR;
        uint16_t CKE_RSTN_CYCLES_1_CR;
        uint16_t CKE_RSTN_CYCLES_2_CR;
        uint16_t INIT_MR_CR;
        uint16_t INIT_EMR_CR;
        uint16_t INIT_EMR2_CR;
        uint16_t INIT_EMR3_CR;
        uint16_t DRAM_BANK_TIMING_PARAM_CR;
        uint16_t DRAM_RD_WR_LATENCY_CR;
        uint16_t DRAM_RD_WR_PRE_CR;
        uint16_t DRAM_MR_TIMING_PARAM_CR;
        uint16_t DRAM_RAS_TIMING_CR;
        uint16_t DRAM_RD_WR_TRNARND_TIME_CR;
        uint16_t DRAM_T_PD_CR;
        uint16_t DRAM_BANK_ACT_TIMING_CR;
        uint16_t ODT_PARAM_1_CR;
        uint16_t ODT_PARAM_2_CR;
        uint16_t ADDR_MAP_COL_3_CR;
        uint16_t MODE_REG_RD_WR_CR;
        uint16_t MODE_REG_DATA_CR;
        uint16_t PWR_SAVE_1_CR;
        uint16_t PWR_SAVE_2_CR;
        uint16_t ZQ_LONG_TIME_CR;
        uint16_t ZQ_SHORT_TIME_CR;
        uint16_t ZQ_SHORT_INT_REFRESH_MARGIN_1_CR;
        uint16_t ZQ_SHORT_INT_REFRESH_MARGIN_2_CR;
        uint16_t PERF_PARAM_1_CR;
        uint16_t HPR_QUEUE_PARAM_1_CR;
        uint16_t HPR_QUEUE_PARAM_2_CR;
        uint16_t LPR_QUEUE_PARAM_1_CR;
        uint16_t LPR_QUEUE_PARAM_2_CR;
        uint16_t WR_QUEUE_PARAM_CR;
        uint16_t PERF_PARAM_2_CR;
        uint16_t PERF_PARAM_3_CR;
        uint16_t DFI_RDDATA_EN_CR;
        uint16_t DFI_MIN_CTRLUPD_TIMING_CR;
        uint16_t DFI_MAX_CTRLUPD_TIMING_CR;
        uint16_t DFI_WR_LVL_CONTROL_1_CR;
        uint16_t DFI_WR_LVL_CONTROL_2_CR;
        uint16_t DFI_RD_LVL_CONTROL_1_CR;
        uint16_t DFI_RD_LVL_CONTROL_2_CR;
        uint16_t DFI_CTRLUPD_TIME_INTERVAL_CR;
        uint16_t DYN_SOFT_RESET_CR2;
        uint16_t AXI_FABRIC_PRI_ID_CR;
    } ddrc;
    
    /*--------------------------------------------------------------------------
     * DDR PHY configuration registers
     */
    struct 
    {
        uint16_t LOOPBACK_TEST_CR;
        uint16_t BOARD_LOOPBACK_CR;
        uint16_t CTRL_SLAVE_RATIO_CR;
        uint16_t CTRL_SLAVE_FORCE_CR;
        uint16_t CTRL_SLAVE_DELAY_CR;
        uint16_t DATA_SLICE_IN_USE_CR;
        uint16_t LVL_NUM_OF_DQ0_CR;
        uint16_t DQ_OFFSET_1_CR;
        uint16_t DQ_OFFSET_2_CR;
        uint16_t DQ_OFFSET_3_CR;
        uint16_t DIS_CALIB_RST_CR;
        uint16_t DLL_LOCK_DIFF_CR;
        uint16_t FIFO_WE_IN_DELAY_1_CR;
        uint16_t FIFO_WE_IN_DELAY_2_CR;
        uint16_t FIFO_WE_IN_DELAY_3_CR;
        uint16_t FIFO_WE_IN_FORCE_CR;
        uint16_t FIFO_WE_SLAVE_RATIO_1_CR;
        uint16_t FIFO_WE_SLAVE_RATIO_2_CR;
        uint16_t FIFO_WE_SLAVE_RATIO_3_CR;
        uint16_t FIFO_WE_SLAVE_RATIO_4_CR;
        uint16_t GATELVL_INIT_MODE_CR;
        uint16_t GATELVL_INIT_RATIO_1_CR;
        uint16_t GATELVL_INIT_RATIO_2_CR;
        uint16_t GATELVL_INIT_RATIO_3_CR;
        uint16_t GATELVL_INIT_RATIO_4_CR;
        uint16_t LOCAL_ODT_CR;
        uint16_t INVERT_CLKOUT_CR;
        uint16_t RD_DQS_SLAVE_DELAY_1_CR;
        uint16_t RD_DQS_SLAVE_DELAY_2_CR;
        uint16_t RD_DQS_SLAVE_DELAY_3_CR;
        uint16_t RD_DQS_SLAVE_FORCE_CR;
        uint16_t RD_DQS_SLAVE_RATIO_1_CR;
        uint16_t RD_DQS_SLAVE_RATIO_2_CR;
        uint16_t RD_DQS_SLAVE_RATIO_3_CR;
        uint16_t RD_DQS_SLAVE_RATIO_4_CR;
        uint16_t WR_DQS_SLAVE_DELAY_1_CR;
        uint16_t WR_DQS_SLAVE_DELAY_2_CR;
        uint16_t WR_DQS_SLAVE_DELAY_3_CR;
        uint16_t WR_DQS_SLAVE_FORCE_CR;
        uint16_t WR_DQS_SLAVE_RATIO_1_CR;
        uint16_t WR_DQS_SLAVE_RATIO_2_CR;
        uint16_t WR_DQS_SLAVE_RATIO_3_CR;
        uint16_t WR_DQS_SLAVE_RATIO_4_CR;
        uint16_t WR_DATA_SLAVE_DELAY_1_CR;
        uint16_t WR_DATA_SLAVE_DELAY_2_CR;
        uint16_t WR_DATA_SLAVE_DELAY_3_CR;
        uint16_t WR_DATA_SLAVE_FORCE_CR;
        uint16_t WR_DATA_SLAVE_RATIO_1_CR;
        uint16_t WR_DATA_SLAVE_RATIO_2_CR;
        uint16_t WR_DATA_SLAVE_RATIO_3_CR;
        uint16_t WR_DATA_SLAVE_RATIO_4_CR;
        uint16_t WRLVL_INIT_MODE_CR;
        uint16_t WRLVL_INIT_RATIO_1_CR;
        uint16_t WRLVL_INIT_RATIO_2_CR;
        uint16_t WRLVL_INIT_RATIO_3_CR;
        uint16_t WRLVL_INIT_RATIO_4_CR;
        uint16_t WR_RD_RL_CR;
        uint16_t RDC_FIFO_RST_ERRCNTCLR_CR;
        uint16_t RDC_WE_TO_RE_DELAY_CR;
        uint16_t USE_FIXED_RE_CR;
        uint16_t USE_RANK0_DELAYS_CR;
        uint16_t USE_LVL_TRNG_LEVEL_CR;
        uint16_t CONFIG_CR;
        uint16_t RD_WR_GATE_LVL_CR;
        uint16_t DYN_RESET_CR;
    } phy;
    
    /*--------------------------------------------------------------------------
     * FIC-64 registers
     * These registers are 16-bit wide and 32-bit aligned.
     */
    struct 
    {
        uint16_t NB_ADDR_CR;
        uint16_t NBRWB_SIZE_CR;
        uint16_t WB_TIMEOUT_CR;
        uint16_t HPD_SW_RW_EN_CR;
        uint16_t HPD_SW_RW_INVAL_CR;
        uint16_t SW_WR_ERCLR_CR;
        uint16_t ERR_INT_ENABLE_CR;
        uint16_t NUM_AHB_MASTERS_CR;
        uint16_t LOCK_TIMEOUTVAL_1_CR;
        uint16_t LOCK_TIMEOUTVAL_2_CR;
        uint16_t LOCK_TIMEOUT_EN_CR;
    } fic;
} ddr_subsys_cfg_t;

/*============================================================================*/
/*                             FDDR Configuration                             */
/*============================================================================*/

typedef struct 
{
    uint16_t PLL_CONFIG_LOW_1;
    uint16_t PLL_CONFIG_LOW_2;
    uint16_t PLL_CONFIG_HIGH;
    uint16_t FACC_CLK_EN;
    uint16_t FACC_MUX_CONFIG;
    uint16_t FACC_DIVISOR_RATIO;
    uint16_t PLL_DELAY_LINE_SEL;
    uint16_t SOFT_RESET; 
    uint16_t IO_CALIB;
    uint16_t INTERRUPT_ENABLE;
    uint16_t AXI_AHB_MODE_SEL;
    uint16_t PHY_SELF_REF_EN;
} fddr_sysreg_t;

/*============================================================================*/
/*                 PCI Express Bridge IP Core configuration.                  */
/*============================================================================*/

typedef struct
{
    uint32_t * p_reg;
    uint32_t value;
} cfg_addr_value_pair_t;

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_INIT_CFG_TYPES_H_ */
