/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif
/********************** private ************************************/

#define SPI0_BASE_ADDR     (0x01C05000)
#define SPI1_BASE_ADDR     (0x01C06000)

/**
  * @brief Serial Peripheral Interface
  */
typedef struct
{
    volatile rt_uint32_t VER;               /* SPI Version number Register,                          Address offset: 0x00   */
    volatile rt_uint32_t CTRL;              /* SPI Global Control Register,                          Address offset: 0x04   */
    volatile rt_uint32_t TCTRL;             /* SPI Transfer Control Register,                        Address offset: 0x08   */
    volatile rt_uint32_t RESERVED1[1];      /* Reserved, 0x0C                                                               */
    volatile rt_uint32_t IER;               /* SPI Interrupt Control Register,                       Address offset: 0x10   */
    volatile rt_uint32_t STA;               /* SPI Interrupt Status Register,                        Address offset: 0x14   */
    volatile rt_uint32_t FCTL;              /* SPI FIFO Control Register,                            Address offset: 0x18   */
    volatile rt_uint32_t FST;               /* SPI FIFO Status Register,                             Address offset: 0x1C   */
    volatile rt_uint32_t WAIT;              /* SPI Wait Clock Counter Register,                      Address offset: 0x20   */
    volatile rt_uint32_t CCTR;              /* SPI Clock Rate Control Register,                      Address offset: 0x24   */
    volatile rt_uint32_t RESERVED2[2];      /* Reserved, 0x28-0x2C                                                          */
    volatile rt_uint32_t BC;                /* SPI Master mode Burst Control Register,               Address offset: 0x30   */
    volatile rt_uint32_t TC;                /* SPI Master mode Transmit Counter Register,            Address offset: 0x34   */
    volatile rt_uint32_t BCC;               /* SPI Burst Control Register,                           Address offset: 0x38   */
    volatile rt_uint32_t RESERVED3[19];     /* Reserved, 0x3C-0x84                                                          */
    volatile rt_uint32_t NDMA_MODE_CTRL;    /* SPI Nomal DMA Mode Control Regist                     Address offset: 0x88   */
    volatile rt_uint32_t RESERVED4[93];     /* Reserved, 0x8C-0x1FC                                                         */
    volatile rt_uint32_t TXD;               /* SPI TX Date Register,                                 Address offset: 0x200  */
    volatile rt_uint32_t RESERVED5[63];     /* Reserved, 0x204-0x2FC                                                        */
    volatile rt_uint32_t RXD;               /* SPI RX Date Register,                                 Address offset: 0x300  */
} SPI_T;

/*
 * @brief SPI Global Control Register
 */
#define SPI_CTRL_RST_SHIFT                  (31)
#define SPI_CTRL_RST_MASK                   (0x1U << SPI_CTRL_RST_SHIFT)

#define SPI_CTRL_TP_EN_SHIFT                (7)
#define SPI_CTRL_TP_EN_MASK                 (0x1U << SPI_CTRL_TP_EN_SHIFT)

#define SPI_CTRL_MODE_SHIFT                 (1)
#define SPI_CTRL_MODE_MASK                  (0x1U << SPI_CTRL_MODE_SHIFT)
typedef enum
{
    SPI_CTRL_MODE_SLAVE = 0 << SPI_CTRL_MODE_SHIFT,
    SPI_CTRL_MODE_MASTER = 1 << SPI_CTRL_MODE_SHIFT
} SPI_CTRL_Mode;

#define SPI_CTRL_EN_SHIFT                   (0)
#define SPI_CTRL_EN_MASK                    (0x1U << SPI_CTRL_EN_SHIFT)
typedef enum
{
    SPI_CTRL_EN_DISABLE = 0 << SPI_CTRL_EN_SHIFT,
    SPI_CTRL_EN_ENABLE = 1 << SPI_CTRL_EN_SHIFT
} SPI_CTRL_En;

/*
 * @brief SPI Transfer Control Register
 */
#define SPI_TCTRL_XCH_SHIFT                 (31)
#define SPI_TCTRL_XCH_MASK                  (0x1U << SPI_TCTRL_XCH_SHIFT)
typedef enum
{
    SPI_TCTRL_XCH_IDLE = 0 << SPI_TCTRL_XCH_SHIFT,
    SPI_TCTRL_XCH_START = 1 << SPI_TCTRL_XCH_SHIFT
} SPI_TCTRL_Xch;

#define SPI_TCTRL_SDDM_SHIFT                (14)
#define SPI_TCTRL_SDDM_MASK                 (0x0U << SPI_TCTRL_SDDM_SHIFT)
typedef enum
{
    SPI_TCTRL_SDDM_SEND_NODELAY = 0 << SPI_TCTRL_SDDM_SHIFT,
    SPI_TCTRL_SDDM_SEND_DELAY = 1 << SPI_TCTRL_SDDM_SHIFT
} SPI_TCTRL_Sddm;

#define SPI_TCTRL_SDM_SHIFT                 (13)
#define SPI_TCTRL_SDM_MASK                  (0x1U << SPI_TCTRL_SDM_SHIFT)
typedef enum
{
    SPI_TCTRL_SDM_SAMPLE_NODELAY = 1 << SPI_TCTRL_SDM_SHIFT,
    SPI_TCTRL_SDM_SAMPLE_DELAY = 0 << SPI_TCTRL_SDM_SHIFT
} SPI_TCTRL_Sdm;

#define SPI_TCTRL_FBS_SHIFT                 (12)
#define SPI_TCTRL_FBS_MASK                  (0x1U << SPI_TCTRL_FBS_SHIFT)
typedef enum
{
    SPI_TCTRL_FBS_MSB = 0 << SPI_TCTRL_FBS_SHIFT,
    SPI_TCTRL_FBS_LSB = 1 << SPI_TCTRL_FBS_SHIFT
} SPI_TCTRL_Fbs;

#define SPI_TCTRL_SDC_SHIFT                 (11)
#define SPI_TCTRL_SDC_MASK                  (0x1U << SPI_TCTRL_SDC_SHIFT)

#define SPI_TCTRL_RPSM_SHIFT                (10)
#define SPI_TCTRL_RPSM_MASK                 (0x1U << SPI_TCTRL_RPSM_SHIFT)

#define SPI_TCTRL_DDB_SHIFT                 (9)
#define SPI_TCTRL_DDB_MASK                  (0x1U << SPI_TCTRL_DDB_SHIFT)

#define SPI_TCTRL_DHB_SHIFT                 (8)
#define SPI_TCTRL_DHB_MASK                  (0x1U << SPI_TCTRL_DHB_SHIFT)
typedef enum
{
    SPI_TCTRL_DHB_FULL_DUPLEX = 0 << SPI_TCTRL_DHB_SHIFT,
    SPI_TCTRL_DHB_HALF_DUPLEX = 1 << SPI_TCTRL_DHB_SHIFT
} SPI_TCTRL_DHB_Duplex;

#define SPI_TCTRL_SS_LEVEL_SHIFT            (7)
#define SPI_TCTRL_SS_LEVEL_MASK             (0x1U << SPI_TCTRL_SS_LEVEL_SHIFT)

#define SPI_TCTRL_SS_OWNER_SHIFT            (6)
#define SPI_TCTRL_SS_OWNER_MASK             (0x1U << SPI_TCTRL_SS_OWNER_SHIFT)
typedef enum
{
    SPI_TCTRL_SS_OWNER_CONTROLLER = 0 << SPI_TCTRL_SS_OWNER_SHIFT,
    SPI_TCTRL_SS_OWNER_SOFTWARE = 1 << SPI_TCTRL_SS_OWNER_SHIFT
} SPI_TCTRL_SS_OWNER;

#define SPI_TCTRL_SS_SEL_SHIFT              (4)
#define SPI_TCTRL_SS_SEL_MASK               (0x3U << SPI_TCTRL_SS_SEL_SHIFT)
typedef enum
{
    SPI_TCTRL_SS_SEL_SS0 = 0 << SPI_TCTRL_SS_SEL_SHIFT,
    SPI_TCTRL_SS_SEL_SS1 = 1 << SPI_TCTRL_SS_SEL_SHIFT,
    SPI_TCTRL_SS_SEL_SS2 = 2 << SPI_TCTRL_SS_SEL_SHIFT,
    SPI_TCTRL_SS_SEL_SS3 = 3 << SPI_TCTRL_SS_SEL_SHIFT
} SPI_TCTRL_SS_Sel;

#define SPI_TCTRL_SS_CTL_SHIFT              (3)
#define SPI_TCTRL_SS_CTL_MASK               (0x1U << SPI_TCTRL_SS_CTL_SHIFT)

#define SPI_TCTRL_SPOL_SHIFT                (2)
#define SPI_TCTRL_SPOL_MASK                 (0x1U << SPI_TCTRL_SPOL_SHIFT)

#define SPI_TCTRL_CPOL_SHIFT                (1)
#define SPI_TCTRL_CPOL_MASK                 (0x1U << SPI_TCTRL_CPOL_SHIFT)
typedef enum
{
    SPI_TCTRL_CPOL_HIGH = 0 << SPI_TCTRL_CPOL_SHIFT,
    SPI_TCTRL_CPOL_LOW = 1 << SPI_TCTRL_CPOL_SHIFT
} SPI_TCTRL_Cpol;

#define SPI_TCTRL_CPHA_SHIFT                (0)
#define SPI_TCTRL_CPHA_MASK                 (0x1U << SPI_TCTRL_CPHA_SHIFT)
typedef enum
{
    SPI_TCTRL_CPHA_PHASE0  = 0 << SPI_TCTRL_CPHA_SHIFT,
    SPI_TCTRL_CPHA_PHASE1  = 1 << SPI_TCTRL_CPHA_SHIFT
} SPI_TCTRL_Cpha;

typedef enum
{
    SPI_SCLK_Mode0 = 0 << SPI_TCTRL_CPHA_SHIFT,
    SPI_SCLK_Mode1 = 1 << SPI_TCTRL_CPHA_SHIFT,
    SPI_SCLK_Mode2 = 2 << SPI_TCTRL_CPHA_SHIFT,
    SPI_SCLK_Mode3 = 3 << SPI_TCTRL_CPHA_SHIFT
} SPI_SCLK_Mode;

/*
 * @brief SPI Interrupt Control Register
 */
#define SPI_IER_SS_INT_EN_SHIFT             (13)
#define SPI_IER_SS_INT_EN_MASK              (0x1U << SPI_IER_SS_INT_EN_SHIFT)

#define SPI_IER_TC_INT_EN_SHIFT             (12)
#define SPI_IER_TC_INT_EN_MASK              (0x1U << SPI_IER_TC_INT_EN_SHIFT)

#define SPI_IER_TF_UDR_INT_EN_SHIFT         (11)
#define SPI_IER_TF_UDR_INT_EN_MASK          (0x1U << SPI_IER_TF_UDR_INT_EN_SHIFT)

#define SPI_IER_TF_OVF_INT_EN_SHIFT         (10)
#define SPI_IER_TF_OVF_INT_EN_MASK          (0x1U << SPI_IER_TF_OVF_INT_EN_SHIFT)

#define SPI_IER_RF_UDR_INT_EN_SHIFT         (9)
#define SPI_IER_RF_UDR_INT_EN_MASK          (0x1U << SPI_IER_RF_UDR_INT_EN_SHIFT)

#define SPI_IER_RF_OVF_INT_EN_SHIFT         (8)
#define SPI_IER_RF_OVF_INT_EN_MASK          (0x1U << SPI_IER_RF_OVF_INT_EN_SHIFT)

#define SPI_IER_TF_FUL_INT_EN_SHIFT         (6)
#define SPI_IER_TF_FUL_INT_EN_MASK          (0x1U << SPI_IER_TF_FUL_INT_EN_SHIFT)

#define SPI_IER_TX_EMP_INT_EN_SHIFT         (5)
#define SPI_IER_TX_EMP_INT_EN_MASK          (0x1U << SPI_IER_TX_EMP_INT_EN_SHIFT)

#define SPI_IER_TX_ERQ_INT_EN_SHIFT         (4)
#define SPI_IER_TX_ERQ_INT_EN_MASK          (0x1U << SPI_IER_TX_ERQ_INT_EN_SHIFT)

#define SPI_IER_RF_FUL_INT_EN_SHIFT         (2)
#define SPI_IER_RF_FUL_INT_EN_MASK          (0x1U << SPI_IER_RF_FUL_INT_EN_SHIFT)

#define SPI_IER_RX_EMP_INT_EN_SHIFT         (1)
#define SPI_IER_RX_EMP_INT_EN_MASK          (0x1U << SPI_IER_RX_EMP_INT_EN_SHIFT)

#define SPI_IER_RF_RDY_INT_EN_SHIFT         (0)
#define SPI_IER_RF_RDY_INT_EN_MASK          (0x1U << SPI_IER_RF_RDY_INT_EN_SHIFT)

/*
 * @brief SPI Interrupt Status Register
 */
#define SPI_STA_SSI_SHIFT                   (13)
#define SPI_STA_SSI_MASK                    (0x1U << SPI_STA_SSI_SHIFT)

#define SPI_STA_TC_SHIFT                    (12)
#define SPI_STA_TC_MASK                     (0x1U << SPI_STA_TC_SHIFT)

#define SPI_STA_TF_UDF_SHIFT                (11)
#define SPI_STA_TF_UDF_MASK                 (0x1U << SPI_STA_TF_UDF_SHIFT)

#define SPI_STA_TF_OVF_SHIFT                (10)
#define SPI_STA_TF_OVF_MASK                 (0x1U << SPI_STA_TF_OVF_SHIFT)

#define SPI_STA_RX_UDF_SHIFT                (9)
#define SPI_STA_RX_UDF_MASK                 (0x1U << SPI_STA_RX_UDF_SHIFT)

#define SPI_STA_RX_OVF_SHIFT                (8)
#define SPI_STA_RX_OVF_MASK                 (0x1U << SPI_STA_RX_OVF_SHIFT)

#define SPI_STA_TX_FULL_SHIFT               (6)
#define SPI_STA_TX_FULL_MASK                (0x1U << SPI_STA_TX_FULL_SHIFT)

#define SPI_STA_TX_EMP_SHIFT                (5)
#define SPI_STA_TX_EMP_MASK                 (0x1U << SPI_STA_TX_EMP_SHIFT)

#define SPI_STA_TX_READY_SHIFT              (4)
#define SPI_STA_TX_READY_MASK               (0x1U << SPI_STA_TX_READY_SHIFT)

#define SPI_STA_RX_FULL_SHIFT               (2)
#define SPI_STA_RX_FULL_MASK                (0x1U << SPI_STA_RX_FULL_SHIFT)

#define SPI_STA_RX_EMP_SHIFT                (1)
#define SPI_STA_RX_EMP_MASK                 (0x1U << SPI_STA_RX_EMP_SHIFT)

#define SPI_STA_RX_RDY_SHIFT                (0)
#define SPI_STA_RX_RDY_MASK                 (0x1U << SPI_STA_RX_RDY_SHIFT)

/*
 * @brief SPI FIFO Control Register
 */
#define SPI_FCTL_TF_RST_SHIFT               (31)
#define SPI_FCTL_TF_RST_MASK                (0x1U << SPI_FCTL_TF_RST_SHIFT)

#define SPI_FCTL_TF_TEST_EN_SHIFT           (30)
#define SPI_FCTL_TF_TEST_EN_MASK            (0x1U << SPI_FCTL_TF_TEST_EN_SHIFT)

#define SPI_FCTL_TF_DRQ_EN_SHIFT            (24)
#define SPI_FCTL_TF_DRQ_EN_MASK             (0x1U << SPI_FCTL_TF_DRQ_EN_SHIFT)
#define SPI_FCTL_TF_DRQ_EN_BIT              HAL_BIT(24)

#define SPI_FCTL_TX_TRIG_LEVEL_SHIFT        (16)
#define SPI_FCTL_TX_TRIG_LEVEL_MASK         (0xFFU << SPI_FCTL_TX_TRIG_LEVEL_SHIFT)

#define SPI_FCTL_RF_RST_SHIFT               (15)
#define SPI_FCTL_RF_RST_MASK                (0x1U << SPI_FCTL_RF_RST_SHIFT)

#define SPI_FCTL_RF_TEST_SHIFT              (14)
#define SPI_FCTL_RF_TEST_MASK               (0x1U << SPI_FCTL_RF_TEST_SHIFT)

#define SPI_FCTL_RF_DRQ_EN_SHIFT            (8)
#define SPI_FCTL_RF_DRQ_EN_MASK             (0x1U << SPI_FCTL_RF_DRQ_EN_SHIFT)

#define SPI_FCTL_RX_TRIG_LEVEL_SHIFT        (0)
#define SPI_FCTL_RX_TRIG_LEVEL_MASK         (0xFFU << SPI_FCTL_RX_TRIG_LEVEL_SHIFT)

/*
 * @brief SPI FIFO Status Registe
 */
#define SPI_FST_TB_WR_SHIFT                 (31)
#define SPI_FST_TB_WR_MASK                  (0x1U << SPI_FST_TB_WR_SHIFT)

#define SPI_FST_TB_CNT_SHIFT                (28)
#define SPI_FST_TB_CNT_MASK                 (0x7U << SPI_FST_TB_CNT_SHIFT)

#define SPI_FST_TF_CNT_SHIFT                (16)
#define SPI_FST_TF_CNT_MASK                 (0xFFU << SPI_FST_TF_CNT_SHIFT)

#define SPI_FST_RB_WR_SHIFT                 (15)
#define SPI_FST_RB_WR_MASK                  (0x1U << SPI_FST_RB_WR_SHIFT)

#define SPI_FST_RB_CNT_SHIFT                (12)
#define SPI_FST_RB_CNT_MASK                 (0x7U << SPI_FST_RB_CNT_SHIFT)

#define SPI_FST_RF_CNT_SHIFT                (0)
#define SPI_FST_RF_CNT_MASK                 (0xFFU << SPI_FST_RF_CNT_SHIFT)

/*
 * @brief SPI Wait Clock Counter Register
 */
#define SPI_WAIT_SWC_SHIFT                  (16)
#define SPI_WAIT_SWC_MASK                   (0xFU << SPI_WAIT_SWC_SHIFT)

#define SPI_WAIT_WCC_SHIFT                  (0)
#define SPI_WAIT_WCC_MASK                   (0xFFFFU << SPI_WAIT_WCC_SHIFT)

/*
 * @brief SPI Clock Rate Control Register
 */
#define SPI_CCTR_DRS_SHIFT                  (12)
#define SPI_CCTR_DRS_MASK                   (0x1U << SPI_CCTR_DRS_SHIFT)
typedef enum
{
    SPI_CCTR_DRS_type_divRate1 = 0 << SPI_CCTR_DRS_SHIFT,
    SPI_CCTR_DRS_type_divRate2 = 1 << SPI_CCTR_DRS_SHIFT
} SPI_CCTR_DRS_type;

#define SPI_CCTR_CDR1_SHIFT                 (8)
#define SPI_CCTR_CDR1_MASK                  (0xFU << SPI_CCTR_CDR1_SHIFT)

#define SPI_CCTR_CDR2_SHIFT                 (0)
#define SPI_CCTR_CDR2_MASK                  (0xFFU << SPI_CCTR_CDR2_SHIFT)

/*
 * @brief SPI Master mode Burst Control Register
 */
#define SPI_BC_MBC_SHIFT                    (0)
#define SPI_BC_MBC_MASK                     (0xFFFFFFU << SPI_BC_MBC_SHIFT)

/*
 * @brief SPI Master mode Transmit Counter Register
 */
#define SPI_TC_MWTC_SHIFT                   (0)
#define SPI_TC_MWTC_MASK                    (0xFFFFFFU << SPI_TC_MWTC_SHIFT)

/*
 * @brief SPI Burst Control Register
 */
#define SPI_BCC_DRM_SHIFT                   (28)
#define SPI_BCC_DRM_MASK                    (0x1U << SPI_BCC_DRM_SHIFT)

#define SPI_BCC_DBC_SHIFT                   (24)
#define SPI_BCC_DBC_MASK                    (0xFU << SPI_BCC_DBC_SHIFT)

#define SPI_BCC_STC_SHIFT                   (0)
#define SPI_BCC_STC_MASK                    (0xFFFFFFU << SPI_BCC_STC_SHIFT)

/*
 * @brief SPI Nomal DMA Mode Control Regist
 */
#define SPI_NDMA_MODE_CTRL_SHIFT            (0)
#define SPI_NDMA_MODE_CTRL_MASK             (0xFFU << SPI_NDMA_MODE_CTRL_SHIFT)

/*
 * @brief SPI TX Date Register
 */
#define SPI_TXD_SHIFT                       (0)
#define SPI_TXD_MASK                        (0xFFFFFFFFU << SPI_TXD_SHIFT)

/*
 * @brief SPI RX Date Register
 */
#define SPI_RXD_SHIFT                       (0)
#define SPI_RXD_MASK                        (0xFFFFFFFFU << SPI_RXD_SHIFT)

/* other */
#define SPI_FIFO_SIZE                       (64)
#define SPI_MAX_WAIT_MS (2000)
#define SPI_SOURCE_CLK (24 * 1000 * 1000)

/* io ops */
#define HAL_BIT(pos)                        (1U << (pos))

#define HAL_SET_BIT(reg, mask)              ((reg) |= (mask))
#define HAL_CLR_BIT(reg, mask)              ((reg) &= ~(mask))
#define HAL_GET_BIT(reg, mask)              ((reg) & (mask))
#define HAL_GET_BIT_VAL(reg, shift, vmask)  (((reg) >> (shift)) & (vmask))

#define HAL_MODIFY_REG(reg, clr_mask, set_mask) \
    ((reg) = (((reg) & (~(clr_mask))) | (set_mask)))

/* access LSBs of a 32-bit register (little endian only) */
#define HAL_REG_32BIT(reg_addr)  (*((volatile rt_uint32_t *)(reg_addr)))
#define HAL_REG_16BIT(reg_addr)  (*((volatile rt_uint16_t *)(reg_addr)))
#define HAL_REG_8BIT(reg_addr)   (*((volatile rt_uint8_t  *)(reg_addr)))

#define HAL_WAIT_FOREVER    OS_WAIT_FOREVER

#define HAL_ARRAY_SIZE(a)   (sizeof((a)) / sizeof((a)[0]))

struct tina_spi
{
    SPI_T *spi;
    unsigned int spi_gate;
    struct rt_spi_bus *spi_bus;
};

struct tina_spi_cs
{
    SPI_TCTRL_SS_Sel cs;
};
/* public function */
rt_err_t r6_spi_bus_register(SPI_T *spi, const char *spi_bus_name);

#ifdef __cplusplus
}
#endif
#endif //
