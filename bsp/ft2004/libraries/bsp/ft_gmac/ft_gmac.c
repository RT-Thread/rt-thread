/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 13:23:19
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

/**
 * @name: Ft_GmacCfgInitialize
 * @msg: 
 * @param {Ft_Gmac_t} *Gmac
 * @param {FGmac_Config_t} *Config
 * @return {*}
 */
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

/**
 * @name: Ft_Gmac_Start 
 * @msg:  Enable GMAC MAC and DMA rx/tx
 * @param {Ft_Gmac_t} *Gmac
 * @return {*}
 */
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

/**
 * @name: Ft_Gmac_Stop
 * @msg: 
 * @param {Ft_Gmac_t} *Gmac
 * @return {*}
 */
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
    // FGmac_Config_t *Config;
    // Config = &Gmac->Config;
    // Gmac_WritePHYRegister(Config, PHY_DEBUG_ADDR_OFFSET, 0x12);
    // FGmac_ReadPHYRegister(Config, PHY_DEBUG_DATA_OFFSET, &RegValue);

    // Ft_printf("PHY_DEBUG_OFFSET 0x12 %x \r\n", RegValue);
    // Ft_assertVoid(Gmac_WritePHYRegister(Config, PHY_DEBUG_ADDR_OFFSET, 0x10) == FST_SUCCESS);
    // Ft_assertVoid(FGmac_ReadPHYRegister(Config, 0x1f, &RegValue) == FST_SUCCESS);
    // Ft_printf("chip  check 0x1f %x \r\n", RegValue);
    // Ft_printf("chip  check GMAC_CONTROL_OFFSET %x \r\n", Ft_in32(Config->BaseAddress + GMAC_CONTROL_OFFSET));

    // Ft_printf("MAC 配置寄存器 %x \r\n", Ft_in32(Config->BaseAddress + GMAC_CONTROL_OFFSET));
    // Ft_printf("中断状态寄存器 %x \r\n", Ft_in32(Config->BaseAddress + GMAC_ISR_STATUS_OFFSET));
    // Ft_printf("中断屏蔽寄存器 %x \r\n", Ft_in32(Config->BaseAddress + GMAC_ISR_MASK_OFFSET));
    // Ft_printf("寄存器 54 %x \r\n", Ft_in32(Config->BaseAddress + GMAC_MAC_MAC_PHY_STATUS));

    // Ft_printf("DMA 总线模式寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_BUS_MODE_OFFSET));
    // Ft_printf("DMA 状态寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_STATUS_OFFSET));
    // Ft_printf("DMA 操作模式寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_OP_OFFSET));
    // Ft_printf("DMA 中断使能寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_INTR_ENA_OFFSET));
    // Ft_printf("DMA 中断遮蔽寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_MISSED_FRAME_CTR_OFFSET));
    // Ft_printf("DMA AXI 总线模式寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_AXI_BUS_MOD_OFFSET));
    // Ft_printf("DMA  AXI 状态寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_AXI_BUS_STATUS_OFFSET));
    // Ft_printf("接收描述符列表地址寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_RCV_BASE_ADDR_OFFSET));
    // Ft_printf("发送描述符列表地址寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_TX_BASE_ADDR_OFFSET));

    // Ft_printf("当前主机接收描述符寄存器 %x \r\n", Ft_in32(Config->BaseAddress + 0x104c));
    // Ft_printf("当前接收缓冲区地址 %x \r\n", Ft_in32(Config->BaseAddress + 0x1054));

    // Ft_printf("当前主机发送描述符寄存器 %x \r\n", Ft_in32(Config->BaseAddress + 0x1048));
    // Ft_printf("当前发送缓冲区地址 %x \r\n", Ft_in32(Config->BaseAddress + 0x1050));

    // Ft_printf("接收描述符列表地址寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_RCV_BASE_ADDR_OFFSET));
    // Ft_printf("发送描述符列表地址寄存器 %x \r\n", Ft_in32(Config->BaseAddress + DMA_TX_BASE_ADDR_OFFSET));

    Ft_printf("\r\n ****************************** \r\n");
}

/**
 * @name: Ft_Gmac_UseDefaultMacAddr
 * @msg: set default mac address
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {Ft_Gmac_t} *Gmac
 * @param {u8} *MacAddr
 */
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
