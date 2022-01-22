/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-25 16:43:14
 * @Description:  This files is for gmac ctrl
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_gmac.h"
#include "ft_gmac_hw.h"
#include "ft_assert.h"
#include "ft_io.h"
#include "ft_status.h"
#include "ft_printf.h"
#include "ft_parameters.h"

static void Ft_Gmac_StubHandler(void *args)
{
    Ft_assertVoidAlways();
}

static void Ft_Gmac_StubErrorHandler(void *CallBackRef, u32 ErrorWord)
{
    // Ft_assertVoidAlways();
}

s32 Ft_Gmac_HwInitialize(Ft_Gmac_t *Gmac)
{
    Ft_assertNonvoid(Gmac != NULL);
    Ft_assertNonvoid(Gmac->IsReady == FT_COMPONENT_IS_READLY);
    return FGmac_InitializeHw(&Gmac->Config);
}

s32 Ft_GmacCfgInitialize(Ft_Gmac_t *Gmac, FGmac_Config_t *Config)
{
    Ft_assertNonvoid(Gmac != NULL);
    Ft_assertNonvoid(Config != NULL);

    Gmac->Config = *Config;
    Gmac->IsReady = FT_COMPONENT_IS_READLY;

    FGmac_SetHandler(Gmac, FT_GMAC_TX_COMPLETE_CB_ID, Ft_Gmac_StubHandler, Gmac);
    FGmac_SetHandler(Gmac, FT_GMAC_RX_COMPLETE_CB_ID, Ft_Gmac_StubHandler, Gmac);
    FGmac_SetHandler(Gmac, FT_GMAC_DMA_ERROR_CB_ID, Ft_Gmac_StubErrorHandler, Gmac);

    return FST_SUCCESS;
}

s32 Ft_Gmac_Start(Ft_Gmac_t *Gmac)
{
    FGmac_Config_t *Config = NULL;
    Ft_assertNonvoid(Gmac != NULL);
    Ft_assertNonvoid(Gmac->IsReady == FT_COMPONENT_IS_READLY);
    Config = &Gmac->Config;

    FGmac_DMAReceptionTransmissionEnable(Config);
    FGmac_ReceptionTransmissionEnable(Config);

    /* Clear Tx and Rx process stopped flags */
    Ft_out32(Gmac->Config.BaseAddress + DMA_INTR_ENA_OFFSET, DMA_INTR_ENA_RIE | DMA_INTR_ENA_AIE | DMA_INTR_ENA_NIE);

    return FST_SUCCESS;
}

s32 Ft_Gmac_Stop(Ft_Gmac_t *Gmac)
{
    FGmac_Config_t *Config = NULL;
    Ft_assertNonvoid(Gmac != NULL);
    Ft_assertNonvoid(Gmac->IsReady == FT_COMPONENT_IS_READLY);
    Config = &Gmac->Config;

    FGmac_TransmissionDisable(Config);
    FGmac_ReceptionDisable(Config);
    FGmac_DMATransmissionDisable(Config);
    FGmac_DMAReceptionDisable(Config);
    return FST_SUCCESS;
}

void Ft_Gmac_Phy_Debug(Ft_Gmac_t *Gmac)
{

    Ft_printf("\r\n ****************************** \r\n");
}


void Ft_Gmac_UseDefaultMacAddr(Ft_Gmac_t *Gmac, u8 *MacAddr)
{
    u32 MacAddrLo;
    u32 MacAddrHi;
    FGmac_Config_t *pConfig;
    Ft_assertNoneReturn(Gmac != NULL);
    pConfig = &Gmac->Config;

    MacAddrLo = Ft_in32(pConfig->BaseAddress + GMAC_MAC_ADDR0_LOWER16BIT_OFFSET);
    MacAddrHi = Ft_in32(pConfig->BaseAddress + GMAC_MAC_ADDR0_UPPER16BIT_OFFSET);

    MacAddr[0] = MacAddrLo & 0xFF;
    MacAddr[1] = (MacAddrLo >> 8) & 0xFF;
    MacAddr[2] = (MacAddrLo >> 16) & 0xFF;
    MacAddr[3] = (MacAddrLo >> 24) & 0xFF;
    MacAddr[4] = MacAddrHi & 0xFF;
    MacAddr[5] = (MacAddrHi >> 8) & 0xFF;
}
