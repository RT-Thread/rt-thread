/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-25 14:00:25
 * @LastEditTime: 2021-05-24 14:34:28
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_assert.h"
#include "ft_spi.h"
#include "ft_spi_hw.h"
#include "ft_generic_timer.h"
#include "ft_gpio.h"

void FSpi_DumpAllStatus(FT_IN FSpi_Ctrl_t *pCtrl, FT_IN char *tag)
{
    FT_SPI_DEBUG_I("***%s status******\r\n", tag);
    FT_SPI_DEBUG_I("busy: %d", SPI_STATUS_REG(pCtrl)->val.Busy);
    FT_SPI_DEBUG_I("tx fifo not empty: %d", SPI_STATUS_REG(pCtrl)->val.Tfnf);
    FT_SPI_DEBUG_I("tx fifo empty: %d", SPI_STATUS_REG(pCtrl)->val.Tfe);
    FT_SPI_DEBUG_I("rx fifo not empty: %d", SPI_STATUS_REG(pCtrl)->val.Rfne);
    FT_SPI_DEBUG_I("rx fifo full: %d", SPI_STATUS_REG(pCtrl)->val.Rff);
    FT_SPI_DEBUG_I("trans error: %d", SPI_STATUS_REG(pCtrl)->val.Txe);
    FT_SPI_DEBUG_I("trans conflict error: %d", SPI_STATUS_REG(pCtrl)->val.Dcol);
}

u32 FSpi_ReadWriteByte(FT_INOUT FSpi_Ctrl_t *pCtrl, FT_IN u8 TxData,
                       FT_OUT u8 *pRxData)
{
    u32 Retry = 0;
    u32 Ret = ERR_SPI_OK;
    u16 RxData;

    if (!pCtrl->IsReady)
    {
        return ERR_SPI_NOT_READY;
    }

    while (FSPI_TX_FIFO_NOT_EMPTY(pCtrl))
    {
        //Ft_GenericTimer_UsDelay(2);
        if ((Retry++) > SPI_TIMEOUT)
        {
            Ret = ERR_SPI_TX_TIMEOUT;
            goto __EXIT;
        }
    }
    FSPI_WRITE_DATA(pCtrl, (u16)TxData);

    Retry = 0;

    while (FSPI_RX_FIFO_EMPTY(pCtrl))
    {
        //Ft_GenericTimer_UsDelay(2);
        if ((Retry++) > SPI_TIMEOUT)
        {
            Ret = ERR_SPI_RX_TIMEOUT;
            goto __EXIT;
        }
    }
    RxData = FSPI_READ_DATA(pCtrl);

    if (pRxData)
    {
        *pRxData = (u8)RxData;
    }

__EXIT:
    return Ret;
}

u32 FSpi_Init(FT_INOUT FSpi_Ctrl_t *pCtrl)
{
    u32 Ret = ERR_SPI_OK;

    FSPI_DISABLE(pCtrl);

    /* config spi ctrl register */
    SPI_CTRL0_REG(pCtrl)->val.Dfs = SPI_DFS_DEFAULT;
    SPI_CTRL0_REG(pCtrl)->val.Frf = SPI_FRF_DEFAULT;

    if (SPI_CTRL_CPHA_1EDGE == pCtrl->Config.Cpha)
    {
        SPI_CTRL0_REG(pCtrl)->val.Scph = SPI_SCPH_SW_CLK_AT_DATA_BEG;
    }
    else if (SPI_CTRL_CPHA_2EDGE == pCtrl->Config.Cpha)
    {
        SPI_CTRL0_REG(pCtrl)->val.Scph = SPI_SCPH_SW_CLK_AT_DATA_MID;
    }
    else
    {
        Ft_assertNoneReturn(0);
    }

    if (SPI_CTRL_CPOL_LOW == pCtrl->Config.Cpol)
    {
        SPI_CTRL0_REG(pCtrl)->val.Scpol = SPI_SCPOL_NOT_ACT_LOW;
    }
    else if (SPI_CTRL_CPOL_HIGH == pCtrl->Config.Cpol)
    {
        SPI_CTRL0_REG(pCtrl)->val.Scpol = SPI_SCPOL_NOT_ACT_HIGH;
    }
    else
    {
        Ft_assertNoneReturn(0);
    }

    SPI_CTRL0_REG(pCtrl)->val.Tmod = SPI_TMOD_TX_RX_MODE;
    SPI_CTRL0_REG(pCtrl)->val.SlvOE = SPI_SLV_OE_DISABLE;
    SPI_CTRL0_REG(pCtrl)->val.Srl = SPI_SRL_NORMAL_MODE;
    SPI_CTRL0_REG(pCtrl)->val.Cfs = SPI_CFS_DEFAULT;

    /* config spi clock */
    FSPI_SET_BAUDR(pCtrl, pCtrl->Config.BaudRDiv);

    /* config rx and tx fifo, fifo depth to trigger intr */
    SPI_TXFTL_REG(pCtrl)->val.Tft = 0;
    SPI_RXFTL_REG(pCtrl)->val.Rft = 0;
    SPI_TXFL_REG(pCtrl)->val.Txtfl = 0;
    SPI_RXFL_REG(pCtrl)->val.Rxtfl = 0;

    SPI_RXSAMPLE_DLY_REG(pCtrl)->val.Rsd = SPI_DEFAULT_RSD;

    FSPI_ENABLE(pCtrl);

    /* set spi ready flag */
    if (ERR_SPI_OK == Ret)
    {
        pCtrl->IsReady = TRUE;
    }

    return Ret;
}

static void FSpi_ToggleCSPin(FT_INOUT FSpi_Ctrl_t *pCtrl, FT_IN FSpi_DevId_t DevId,
                             FT_IN bool_t select)
{
    u32 setVal = ((TRUE == select) ? GPIO_OFF : GPIO_ON);

    Ft_assertNoneReturn(NULL != pCtrl);

    if (FGpio_ReadPinA(GPIO_CTRL_ID_1, pCtrl->CsPin) != setVal)
    {
        FGpio_WritePinA(GPIO_CTRL_ID_1, pCtrl->CsPin, setVal);
    }

    Ft_GenericTimer_UsDelay(10);
    return;
}

void FSpi_SelectSlave(FT_INOUT FSpi_Ctrl_t *pCtrl, FT_IN FSpi_DevId_t DevId,
                      FT_IN bool_t select)
{
    FSpi_SeReg_t *pSelReg;
    u32 setVal = ((TRUE == select) ? SPI_SE_SELECTED : SPI_SE_UNSELECTED);

    FSPI_DISABLE(pCtrl);
    /* enable or disable specific spi slave device */
    pSelReg = SPI_SE_REG(pCtrl);
    switch (DevId)
    {
    case SPI_DEV_ID_0:
        pSelReg->val.SelSlave_0 = setVal;
        break;
    case SPI_DEV_ID_1:
        pSelReg->val.SelSlave_1 = setVal;
        Ft_assertNoneReturn(0);
        break;
    case SPI_DEV_ID_2:
        pSelReg->val.SelSlave_2 = setVal;
        Ft_assertNoneReturn(0);
        break;
    case SPI_DEV_ID_3:
        pSelReg->val.SelSlave_3 = setVal;
        Ft_assertNoneReturn(0);
        break;
    default:
        Ft_assertNoneReturn(0);
        break;
    }

    FSpi_ToggleCSPin(pCtrl, DevId, select);
    FSPI_ENABLE(pCtrl);

    return;
}
