/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-25 13:59:44
 * @LastEditTime: 2021-04-30 15:42:30
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */
#ifndef FT_BSP_SPI_HW_H
#define FT_BSP_SPI_HW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"

/* offset map of SPI register */
#define SPI_CTRL_R0 0x00       //Ctrl register 0
#define SPI_CTRL_R1 0x04       //Ctrl register 1
#define SPI_SSI_EN_R 0x08      //SPI enable register
#define SPI_MW_CR 0x0c         //Microwire ctrl register
#define SPI_SE_R 0x10          //Slave enable register
#define SPI_BAUD_R 0x14        //Baudrate set register
#define SPI_TXFTL_R 0x18       //Tx threshold register
#define SPI_RXFTL_R 0x1c       //Rx threshold register
#define SPI_TXFL_R 0x20        //Tx level register
#define SPI_RXFL_R 0x24        //Rx level register
#define SPI_S_R 0x28           //Status register
#define SPI_IM_R 0x2c          //Intr mask register
#define SPI_RIS_R 0x34         //Intr status register
#define SPI_TXOI_CR 0x38       //TX FIFO overflow intr clear register
#define SPI_RXOI_CR 0x3c       //RX FIFO overflow intr clear register
#define SPI_RXUI_CR 0x40       //TX FIFO underflow intr clear register
#define SPI_MSTI_CR 0x44       //Multi slave intr clear register
#define SPI_IC_R 0x48          //Intr clear register
#define SPI_DMA_CR 0x4c        //DMA ctrl register
#define SPI_DMA_TDL_R 0x50     //DMA TX Data level register
#define SPI_DMA_RDL_R 0x54     //DMA RX Data level register
#define SPI_ID_R 0x58          //Identification register
#define SPI_D_R 0xec           //Data register
#define SPI_RX_SAMPLE_DLY 0xfc //RX Data delay register

    typedef enum
    {
        SPI_CTRL_ID_0 = 0,
        SPI_CTRL_ID_1,

        NUM_OF_SPI_CTRL,
    } FSpi_CtrlId_t;

    typedef enum
    {
        SPI_DEV_ID_0 = 0,
        SPI_DEV_ID_1,
        SPI_DEV_ID_2,
        SPI_DEV_ID_3,

        NUM_OF_SPI_DEV,
    } FSpi_DevId_t;

    /* base address of SPI register */
    const static u32 g_SpiBaseAddr[NUM_OF_SPI_CTRL] = {0x2800c000, 0x28013000};

    typedef union
    {
        u32 data;
        struct
        {
            u32 Dfs : 4; /* 3:0, select data length */
#define SPI_DFS_DEFAULT 0x7
            u32 Frf : 2; /* 5:4, selcet trans mode */
#define SPI_FRF_DEFAULT 0x0
            u32 Scph : 1;               /* 6, serial clock phase */
#define SPI_SCPH_SW_CLK_AT_DATA_MID 0x0 /* second edge */
#define SPI_SCPH_SW_CLK_AT_DATA_BEG 0x1 /* first edge */
            u32 Scpol : 1;              /* 7, serial clock Polarity */
#define SPI_SCPOL_NOT_ACT_LOW 0x0
#define SPI_SCPOL_NOT_ACT_HIGH 0x1
            u32 Tmod : 2; /* 9:8, ctrl trans mode, indicate if tx rx data is valid */
#define SPI_TMOD_TX_RX_MODE 0x0
#define SPI_TMOD_TX_MODE 0x1
#define SPI_TMOD_RX_MODE 0x2
#define SPI_TMOD_EEPROM_MODE 0x3
            u32 SlvOE : 1; /* 10, enable slave tx logic */
#define SPI_SLV_OE_ENABLE 0x0
#define SPI_SLV_OE_DISABLE 0x1
            u32 Srl : 1; /* 11, shift register loopback */
#define SPI_SRL_NORMAL_MODE 0x0
#define SPI_SRL_TEST_MODE 0x1
            u32 Cfs : 4; /* 15:12, ctrl data size, applied in Microwire mode */
#define SPI_CFS_DEFAULT 0x0
            u32 Reserve : 16;
        } val;
    } FSpi_CtrlReg0_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 ndf : 16; /* 15:0 valid when TMOD = 10, TMOD = 11 */
#define SPI_NDF_DEFAULT 16
            u32 Reserve : 16;
        } val;
    } FSpi_CtrlReg1_t;

    typedef struct
    {
        u32 CPOL;
        u32 CPHA;
    } FSpi_ClockMode_t;

    static const FSpi_ClockMode_t g_FSpi_ClockMode[4] =
        {
            {.CPOL = SPI_SCPOL_NOT_ACT_LOW, .CPHA = SPI_SCPH_SW_CLK_AT_DATA_BEG},  /* low level logic, sample at rising edge, shift at falling edge  */
            {.CPOL = SPI_SCPOL_NOT_ACT_LOW, .CPHA = SPI_SCPH_SW_CLK_AT_DATA_MID},  /* low level logic, sample at falling edge, shift at rising edge */
            {.CPOL = SPI_SCPOL_NOT_ACT_HIGH, .CPHA = SPI_SCPH_SW_CLK_AT_DATA_MID}, /* high level logic, sample at falling edge, shift at rising edge */
            {.CPOL = SPI_SCPOL_NOT_ACT_HIGH, .CPHA = SPI_SCPH_SW_CLK_AT_DATA_BEG}, /* high level logic, sample at rising edge, shift at falling edge */
    };

    typedef union
    {
        u32 data;
        struct
        {
            u32 SsiEn : 1; /* 0, enable or disable all SPI op */
            u32 Reserve : 31;
        } val;
    } FSpi_SsiEnReg_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 MwMod : 1; /* 0 microwire trans mode */
#define SPI_MWMODE_NO_CONTINUOUES 0
#define SPI_MWMODE_CONTINUOUES 1
            u32 Mdd : 1; /* 1 microwire ctrl bit */
#define SPI_MWMDD_RXFROM_EXT_DEV 0
#define SPI_MWMDD_TXTO_EXT_DEV 1
            u32 Mhs : 1; /* 2 microwire handshake */
#define SPI_MWMHS_DISABLE 0
#define SPI_MWMHS_ENABLE 1
            u32 Reserve : 29;
        } val;
    } FSpi_MwcrReg_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 SelSlave_0 : 1; /* 3:0, select specifc slave device */
            u32 SelSlave_1 : 1;
            u32 SelSlave_2 : 1;
            u32 SelSlave_3 : 1;
#define SPI_SE_SELECTED 0x1
#define SPI_SE_UNSELECTED 0x0
            u32 Reserve : 28;
        } val;
    } FSpi_SeReg_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 Sckdv : 16; /* 15:0, SSI clk divider, must be times of 2 */
#define SPI_SCKDV_MIN (2)
#define SPI_SCKDV_4 (4)
#define SPI_SCKDV_8 (8)
#define SPI_SCKDV_16 (16)
#define SPI_SCKDV_32 (20)
#define SPI_SCKDV_64 (28)
#define SPI_SCKDV_128 (128)
#define SPI_SCKDV_256 (256)
#define SPI_SCKDV_1024 (1024)
#define SPI_SCKDV_4096 (4096)
#define SPI_SCKDV_12800 (12800)
#define SPI_SCKDV_56800 (56800)
#define SPI_SCKDV_MAX (65534)
            u32 Reserve : 16;
        } val;
    } FSpi_BaudrReg_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 Tft : 8; /* 7:0, TX FIFO threshold */
            u32 Reserve : 24;
        } val;

    } FSpi_TxFtlrReg_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 Rft : 8; /* 7:0, RX FIFO threshold */
            u32 Reserve : 24;
        } val;

    } FSpi_RxFtlrReg_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 Txtfl : 8; /* 7:0, TX FIFO level, num of valid num */
            u32 Reserve : 24;
        } val;

    } FSpi_TxFlrReg_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 Rxtfl : 8; /* 7:0, RX FIFO level, num of valid num */
            u32 Reserve : 24;
        } val;

    } FSpi_RxFlrReg_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 Busy : 1; /* 0, SPI bus busy bit */
            u32 Tfnf : 1; /* 1, tx FIFO not empty */
#define SPI_TX_FIFO_FULL 0x0
#define SPI_TX_FIFO_NOT_FULL 0x1
            u32 Tfe : 1; /* 2, tx FIFO empty */
#define SPI_TX_FIFO_NOT_EMPTY 0x0
#define SPI_TX_FIFO_EMPTY 0x1
            u32 Rfne : 1; /* 3, rx FIFO not emptu */
#define SPI_RX_FIFO_EMPTY 0x0
#define SPI_RX_FIFO_NOT_EMPTY 0x1
            u32 Rff : 1; /* 4, rx FIFO full */
#define SPI_RX_FIFO_NOT_FULL 0x0
#define SPI_RX_FIFO_FULL 0x1
            u32 Txe : 1; /* 5, trans error */
#define SPI_TX_NO_ERR 0x0
#define SPI_TX_ERR 0x1
            u32 Dcol : 1; /* 6, trans conflict error */
#define SPI_TX_NO_COLERR 0x0
#define SPI_TX_COLERR 0x1
            u32 Reserve : 25;
        } val;
    } FSpi_StatusReg_t; /* Read-Only */

    typedef union
    {
        u32 IdCode : 32;
    } FSpi_IDReg_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 Dr : 16; /* 15:0, RX and TX fifo */
#define SPI_8BIT_MASK 0xFF
#define SPI_16BIT_MASK 0xFFFF
            u32 Reserve : 16;
        } val;
    } FSpi_DataReg_t;

    typedef union
    {
        u32 data;
        struct
        {
            u32 Rsd : 8; /* 7:0, RX data delay */
#define SPI_DEFAULT_RSD 0x6
            u32 Reserve : 24;
        } val;
    } FSpi_RxSampleDlyReg_t;

#define SPI_CTL_ID(pCtrl) ((pCtrl)->CtrlId)
#define SPI_BASE_ADDR(pCtrl) (g_SpiBaseAddr[SPI_CTL_ID(pCtrl)])

/* select slave device */
#define SPI_SE_REG(pCtrl) ((FSpi_SeReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_SE_R))
/* set speed */
#define SPI_BAUDR_REG(pCtrl) ((FSpi_BaudrReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_BAUD_R))
#define FSPI_SET_BAUDR(pCtrl, div) (SPI_BAUDR_REG(pCtrl)->val.Sckdv = (div))
#define FSPI_GET_BAUDR(pCtrl) (SPI_BAUDR_REG(pCtrl)->val.Sckdv)
/* check status */
#define SPI_STATUS_REG(pCtrl) ((FSpi_StatusReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_S_R))
#define FSPI_TX_FIFO_NOT_EMPTY(pCtrl) (SPI_TX_FIFO_NOT_EMPTY == (SPI_STATUS_REG(pCtrl)->val.Tfe))
#define FSPI_RX_FIFO_EMPTY(pCtrl) (SPI_RX_FIFO_EMPTY == (SPI_STATUS_REG(pCtrl)->val.Rfne))
/* enable/disable spi bus */
#define SPI_SSIEN_REG(pCtrl) ((FSpi_SsiEnReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_SSI_EN_R))
#define FSPI_ENABLE(pCtrl) (SPI_SSIEN_REG(pCtrl)->val.SsiEn = 1)
#define FSPI_DISABLE(pCtrl) (SPI_SSIEN_REG(pCtrl)->val.SsiEn = 0)
/* shortcut to access register */
#define SPI_CTRL0_REG(pCtrl) ((FSpi_CtrlReg0_t *)(SPI_BASE_ADDR(pCtrl) + SPI_CTRL_R0))
#define SPI_CTRL1_REG(pCtrl) ((FSpi_CtrlReg1_t *)(SPI_BASE_ADDR(pCtrl) + SPI_CTRL_R1))
#define SPI_TXFTL_REG(pCtrl) ((FSpi_TxFtlrReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_TXFTL_R))
#define SPI_RXFTL_REG(pCtrl) ((FSpi_RxFtlrReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_RXFTL_R))
#define SPI_TXFL_REG(pCtrl) ((FSpi_TxFlrReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_TXFL_R))
#define SPI_RXFL_REG(pCtrl) ((FSpi_RxFlrReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_RXFL_R))
#define SPI_ID_REG(pCtrl) ((FSpi_IDReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_ID_R))
#define FSPI_GET_ID(pCtrl) (SPI_ID_REG(pCtrl)->IdCode)
#define SPI_DATA_REG(pCtrl) ((FSpi_DataReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_D_R))
#define FSPI_READ_DATA(pCtrl) (u16)(SPI_DATA_REG(pCtrl)->val.Dr)
#define FSPI_WRITE_DATA(pCtrl, dat) (SPI_DATA_REG(pCtrl)->val.Dr = (u16)(dat))
#define SPI_RXSAMPLE_DLY_REG(pCtrl) ((FSpi_RxSampleDlyReg_t *)(SPI_BASE_ADDR(pCtrl) + SPI_RX_SAMPLE_DLY))
#define SPI_MWCTRL_REG(pCtrl) ((FSpi_MwcrReg_t *)SPI_BASE_ADDR(pCtrl) + SPI_MW_CR)

#ifdef __cplusplus
}
#endif

#endif
