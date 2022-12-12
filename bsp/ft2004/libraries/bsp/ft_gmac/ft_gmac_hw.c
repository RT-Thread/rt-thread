/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-25 16:42:23
 * @Description:  This files is for gmac register
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_gmac_hw.h"
#include "ft_types.h"
#include "ft_generic_timer.h"
#include "ft_assert.h"
#include "ft_status.h"
#include "ft_io.h"
#include "ft_debug.h"
#define PHY_CONFIG_DELAY_US 100

#define GMAC_HW_DEBUG_TAG "GMAC_HW"

#define GMAC_HW_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(GMAC_HW_DEBUG_TAG, format, ##__VA_ARGS__)
#define GMAC_HW_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(GMAC_HW_DEBUG_TAG, format, ##__VA_ARGS__)
#define GMAC_HW_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(GMAC_HW_DEBUG_TAG, format, ##__VA_ARGS__)

s32 Gmac_WritePHYRegister(FGmac_Config_t *Config, u16 PHYReg, u32 RegValue)
{
    u32 TmpReg;
    u32 Wait_Counter = 0;

    TmpReg = Ft_in32(Config->BaseAddress + GMAC_MII_ADDR_OFFSET);

    TmpReg |= GMAC_MII_ADDR_CR(Config->clkMDC);
    TmpReg |= GMAC_MII_ADDR_PA(Config->PhyAddr); /* Set the PHY device address   */
    TmpReg |= GMAC_MII_ADDR_GR(PHYReg);          /* Set the PHY register address */
    TmpReg |= GMAC_MII_ADDR_GW;                  /*  Set the write mode   */
    TmpReg |= GMAC_MII_ADDR_GB;                  /* Set the MII Busy bit */

    Ft_out32(Config->BaseAddress + GMAC_MII_DATA_OFFSET, RegValue);
    Ft_out32(Config->BaseAddress + GMAC_MII_ADDR_OFFSET, TmpReg);

    /* Check for the Busy flag */
    while ((Ft_in32(Config->BaseAddress + GMAC_MII_ADDR_OFFSET) & GMAC_MII_ADDR_GB) == GMAC_MII_ADDR_GB)
    {
        if (10000000 <= ++Wait_Counter)
        {
            GMAC_HW_DEBUG_E("Gmac_WritePHYRegister FST_ERROR_COUNT_MAX \r\n");
            return FST_ERROR_COUNT_MAX;
        }
    }
    return FST_SUCCESS;
}

s32 FGmac_ReadPHYRegister(FGmac_Config_t *Config, u16 PHYReg, u32 *RegValue)
{
    u32 TmpReg;
    u32 Wait_Counter = 0;

    TmpReg = 0;
    TmpReg |= GMAC_MII_ADDR_CR(Config->clkMDC);
    TmpReg |= GMAC_MII_ADDR_PA(Config->PhyAddr); /* Set the PHY device address   */
    TmpReg |= GMAC_MII_ADDR_GR(PHYReg);          /* Set the PHY register address */
    TmpReg &= ~GMAC_MII_ADDR_GW;                 /*  Set the read mode   */
    TmpReg |= GMAC_MII_ADDR_GB;                  /* Set the MII Busy bit */

    while ((Ft_in32(Config->BaseAddress + GMAC_MII_ADDR_OFFSET) & GMAC_MII_ADDR_GB) == GMAC_MII_ADDR_GB)
    {
        if (10000000 <= ++Wait_Counter)
        {
            GMAC_HW_DEBUG_E("wait GMAC_MII_ADDR_GB is error \r\n");
            *RegValue = 0xffff;
            return FST_ERROR_COUNT_MAX;
        }
    }

    Ft_out32(Config->BaseAddress + GMAC_MII_ADDR_OFFSET, TmpReg);

    while ((Ft_in32(Config->BaseAddress + GMAC_MII_ADDR_OFFSET) & GMAC_MII_ADDR_GB) == GMAC_MII_ADDR_GB)
    {
        if (10000000 <= ++Wait_Counter)
        {
            GMAC_HW_DEBUG_E("wait GMAC_MII_ADDR_GB 2 is error \r\n");
            *RegValue = 0xffff;
            return FST_ERROR_COUNT_MAX;
        }
    }
    *RegValue = Ft_in32(Config->BaseAddress + GMAC_MII_DATA_OFFSET);
    return FST_SUCCESS;
}

static s32 FGmac_PhyAddrGet(FGmac_Config_t *Config)
{
    u32 i = 0;
    u32 phyId1;
    u32 phyId2;
    u8 flag = 0;

    for (i = 0; i < 32; i++)
    {
        Config->PhyAddr = i;
        FGmac_ReadPHYRegister(Config, PHY_ID1_REG_OFFSET, &phyId1);
        FGmac_ReadPHYRegister(Config, PHY_ID2_REG_OFFSET, &phyId2);

        if ((phyId2 & 0xffff) != 0xffff)
        {
            if ((0 == i) && (0x1c == phyId1) && ((phyId2 >> 10) == 0x32))
            {
                continue;
            }
            flag = 1;
            break;
        }
    }
    return (flag == 1) ? FST_SUCCESS : FST_FAILURE;
}


static void FGmac_MACAddressConfig(FGmac_Config_t *Config, u32 MacAddr, u8 *Addr)
{
    u32 tmpreg;
    /* Calculate the selected MAC address high register */
    tmpreg = ((u32)Addr[5] << 8) | (u32)Addr[4];
    /* Load the selected MAC address high register */
    Ft_out32(Config->BaseAddress + GMAC_MAC_ADDR0_UPPER16BIT_OFFSET + MacAddr, tmpreg);
    /* Calculate the selected MAC address low register */
    tmpreg = ((u32)Addr[3] << 24) | ((u32)Addr[2] << 16) | ((u32)Addr[1] << 8) | Addr[0];
    /* Load the selected MAC address low register */
    Ft_out32(Config->BaseAddress + GMAC_MAC_ADDR0_LOWER16BIT_OFFSET + MacAddr, tmpreg);
}


static void FGmac_MACDMAInit(FGmac_Config_t *Config)
{
    u32 RegValue = 0;
    Ft_assertVoid(FGmac_PhyAddrGet(Config) == FST_SUCCESS);
    RegValue = Ft_in32(Config->BaseAddress + GMAC_CONTROL_OFFSET);
    /* MACCR Configuration **************************************/
    /* Set the WD bit according to ETH Watchdog value */
    /* Set the JD: bit according to ETH Jabber value */
    /* Set the IFG bit according to ETH InterFrameGap value */
    /* Set the DCRS bit according to ETH CarrierSense value */
    /* Set the FES bit according to ETH Speed value */
    /* Set the DO bit according to ETH ReceiveOwn value */
    /* Set the LM bit according to ETH LoopbackMode value */
    /* Set the DM bit according to ETH Mode value */
    /* Set the IPCO bit according to ETH ChecksumOffload value */
    /* Set the DR bit according to ETH RetryTransmission value */
    /* Set the ACS bit according to ETH AutomaticPadCRCStrip value */
    /* Set the BL bit according to ETH BackOffLimit value */
    /* Set the DC bit according to ETH DeferralCheck value */
    RegValue &= ~GMAC_CONTROL_WD;
    RegValue &= ~GMAC_CONTROL_JD;
    RegValue |= GMAC_CONTROL_IFG(0);
    RegValue &= ~GMAC_CONTROL_DCRS;
    RegValue &= ~GMAC_CONTROL_DO;
    RegValue &= ~GMAC_CONTROL_LM;
    if (Config->ChecksumMode)
    {
        RegValue |= GMAC_CONTROL_IPC;
    }
    else
    {
        RegValue &= ~GMAC_CONTROL_IPC;
    }

    RegValue |= GMAC_CONTROL_DR;
    RegValue &= ~GMAC_CONTROL_ACS;
    RegValue |= GMAC_CONTROL_BL(0);
    RegValue &= ~GMAC_CONTROL_DC;
    if (Config->DuplexMode == GMAC_MODE_FULLDUPLEX)
    {
        RegValue |= GMAC_CONTROL_DM;
    }
    else
    {
        RegValue &= ~GMAC_CONTROL_DM;
    }

    RegValue &= ~GMAC_CONTROL_FES;
    Ft_out32(Config->BaseAddress + GMAC_CONTROL_OFFSET, RegValue);
    Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);

    /*----------------------- GMAC MACFFR Configuration --------------------*/
    /* Set the RA bit according to ETH ReceiveAll value */
    /* Set the SAF and SAIF bits according to ETH SourceAddrFilter value */
    /* Set the PCF bit according to ETH PassControlFrames value */
    /* Set the DBF bit according to ETH BroadcastFramesReception value */
    /* Set the DAIF bit according to ETH DestinationAddrFilter value */
    /* Set the PR bit according to ETH PromiscuousMode value */
    /* Set the PM, HMC and HPF bits according to ETH MulticastFramesFilter value */
    /* Set the HUC and HPF bits according to ETH UnicastFramesFilter value */
    /* Write to  MACFFR */
    RegValue = Ft_in32(Config->BaseAddress + GMAC_FRAME_FILTER_OFFSET);
    RegValue |= GMAC_FRAME_FILTER_RA;
    RegValue |= GMAC_FRAME_FILTER_PCF(2);
    RegValue &= ~GMAC_FRAME_FILTER_PM;
    RegValue &= ~GMAC_FRAME_FILTER_DBF;
    RegValue &= ~GMAC_FRAME_FILTER_DAIF;
    RegValue &= ~GMAC_FRAME_FILTER_PR;
    Ft_out32(Config->BaseAddress + GMAC_FRAME_FILTER_OFFSET, RegValue);
    Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);

    /*---------------  MACHTHR and MACHTLR Configuration --------------*/
    Ft_out32(Config->BaseAddress + GMAC_HASH_HIGH_OFFSET, 0);
    Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);
    Ft_out32(Config->BaseAddress + GMAC_HASH_LOW_OFFSET, 0);
    Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);

    /*----------------------- MACFCR Configuration -------------------*/
    /* Set the PT bit according to ETH PauseTime value */
    /* Set the DZPQ bit according to ETH ZeroQuantaPause value */
    /* Set the PLT bit according to ETH PauseLowThreshold value */
    /* Set the UP bit according to ETH UnicastPauseFrameDetect value */
    /* Set the RFE bit according to ETH ReceiveFlowControl value */
    /* Set the TFE bit according to ETH TransmitFlowControl value */
    RegValue = Ft_in32(Config->BaseAddress + GMAC_FLOW_CTRL_OFFSET);
    RegValue |= GMAC_FLOW_DZPQ;
    RegValue |= GMAC_FLOW_PLT(0);
    RegValue &= ~GMAC_FLOW_RFE;
    RegValue &= ~GMAC_FLOW_TFE;
    Ft_out32(Config->BaseAddress + GMAC_FLOW_CTRL_OFFSET, RegValue);
    Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);

    /*-----------------------  MACVLANTR Configuration ----------------*/
    /* Set the ETV bit according to ETH VLANTagComparison value */
    /* Set the VL bit according to ETH VLANTagIdentifier value */
    RegValue = GMAC_VLAN_TAG_VL(0);
    RegValue &= ~GMAC_VLAN_TAG_ETV;
    Ft_out32(Config->BaseAddress + GMAC_VLAN_TAG_OFFSET, RegValue);
    Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);

    /* DMA default initialization ************************************/
    /* Set the DT bit according to ETH DropTCPIPChecksumErrorFrame value */
    /* Set the RSF bit according to ETH ReceiveStoreForward value */
    /* Set the DFF bit according to ETH FlushReceivedFrame value */
    /* Set the TSF bit according to ETH TransmitStoreForward value */
    /* Set the TTC bit according to ETH TransmitThresholdControl value */
    /* Set the FEF bit according to ETH ForwardErrorFrames value */
    /* Set the FUF bit according to ETH ForwardUndersizedGoodFrames value */
    /* Set the RTC bit according to ETH ReceiveThresholdControl value */
    /* Set the OSF bit according to ETH SecondFrameOperate value */
    RegValue = Ft_in32(Config->BaseAddress + DMA_OP_OFFSET);
    RegValue &= DMA_OP_CLEAR_MASK;
    RegValue &= ~DMA_OP_DT;
    RegValue |= DMA_OP_RSF;
    RegValue &= ~DMA_OP_DFF;
    RegValue |= DMA_OP_TSF;
    RegValue |= DMA_OP_TTC(7);
    RegValue |= DMA_OP_OSF;
    Ft_out32(Config->BaseAddress + DMA_OP_OFFSET, RegValue);
    Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);

    /* DMABMR Configuration ------------------*/
    /* Set the AAL bit according to ETH AddressAlignedBeats value */
    /* Set the FB bit according to ETH FixedBurst value */
    /* Set the RPBL and 4*PBL bits according to ETH RxDMABurstLength value */
    /* Set the PBL and 4*PBL bits according to ETH TxDMABurstLength value */
    /* Set the Enhanced DMA descriptors bit according to ETH EnhancedDescriptorFormat value*/
    /* Set the DSL bit according to ETH DesciptorSkipLength value */
    /* Set the PR and DA bits according to ETH DMAArbitration value */
    RegValue = Ft_in32(Config->BaseAddress + DMA_BUS_MODE_OFFSET);
    RegValue |= DMA_BUS_AAL;
    RegValue |= DMA_BUS_FB;
    RegValue |= DMA_BUS_RPBL(32);
    RegValue |= DMA_BUS_PBL(32);
    RegValue |= DMA_BUS_ATDS;
    RegValue |= DMA_BUS_PR(0);
    RegValue |= DMA_BUS_USP;
    Ft_out32(Config->BaseAddress + DMA_BUS_MODE_OFFSET, RegValue);
    Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);
    Ft_out32(Config->BaseAddress + DMA_AXI_BUS_MOD_OFFSET, 0x0000000e);
    FGmac_MACAddressConfig(Config, 0, Config->MacAddr);
}

s32 FGmac_InitializeHw(FGmac_Config_t *Config)
{
    u32 Wait_Counter = 0;
    u32 RegValue;
    s32 ret = FST_SUCCESS;

    /*Gmac Software reset   */
    Ft_out32(Config->BaseAddress + DMA_BUS_MODE_OFFSET, DMA_BUS_SWR);

    while ((Ft_in32(Config->BaseAddress + DMA_BUS_MODE_OFFSET) & DMA_BUS_SWR) == DMA_BUS_SWR)
    {
        if (++Wait_Counter > 30)
        {
            GMAC_HW_DEBUG_E("DMA_BUS_MODE_OFFSET wait is too long ,Addr %x \r\n", Config->BaseAddress);
            return FST_ERROR_COUNT_MAX;
        }
        Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);
    }
    Wait_Counter = 0;
    Ft_out32(Config->BaseAddress + DMA_BUS_MODE_OFFSET, DMA_BUS_INIT);

    Ft_out32(Config->BaseAddress + DMA_OP_OFFSET, Ft_in32(Config->BaseAddress + DMA_OP_OFFSET) | DMA_OP_FTF);

    while ((Ft_in32(Config->BaseAddress + DMA_OP_OFFSET) & DMA_OP_FTF) == DMA_OP_FTF)
    {
        if (++Wait_Counter > 30)
        {
            GMAC_HW_DEBUG_E("DMA_OP_OFFSET wait is too long \r\n");
            return FST_ERROR_COUNT_MAX;
        }
        Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);
    }

    Wait_Counter = 0;

    /* GMAC Init */
    Ft_out32(Config->BaseAddress + GMAC_CONTROL_OFFSET, GMAC_CONTROL_INIT);
    /* disable flow control */
    Ft_out32(Config->BaseAddress + GMAC_FLOW_CTRL_OFFSET, 0);

    Ft_out32(Config->BaseAddress + DMA_STATUS_OFFSET, DMA_STATUS_INIT);

    Ft_out32(Config->BaseAddress + DMA_INTR_ENA_OFFSET, 0);

    /* get Phy addr */
    Ft_assertNonvoid(FGmac_PhyAddrGet(Config) == FST_SUCCESS);

    /*-------------------------------- MAC Initialization ----------------------*/
    /*-------------------- PHY initialization and configuration ----------------*/
    /* Put the PHY in reset mode */
    if (Gmac_WritePHYRegister(Config, PHY_BCR_OFFSET, PHY_RESET) != FST_SUCCESS)
    {
        GMAC_HW_DEBUG_E("PHY_BCR_OFFSET is error \r\n");
        return FST_FAILURE;
    }

    do
    {
        FGmac_ReadPHYRegister(Config, PHY_BCR_OFFSET, &RegValue);
        Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);

        if (++Wait_Counter > 30)
        {
            GMAC_HW_DEBUG_E("PHY_BCR_OFFSET wait is too long \r\n");
            ret = FST_ERROR_COUNT_MAX;
            goto gmac_init;
        }
    } while ((RegValue & PHY_RESET) == PHY_RESET);

    Wait_Counter = 0;
    if (Config->AutoNegotiation == GMAC_AUTONEGOTIATION_ENABLE)
    {
        do
        {
            FGmac_ReadPHYRegister(Config, PHY_BSR_OFFSET, &RegValue);

            if (++Wait_Counter > 30)
            {
                GMAC_HW_DEBUG_E("PHY_BSR_OFFSET 1 wait is too long \r\n");
                ret = FST_ERROR_COUNT_MAX;
                goto gmac_init;
            }
            Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);

        } while ((RegValue & PHY_LINKED_STATUS) != PHY_LINKED_STATUS);

        Wait_Counter = 0;
        if (Gmac_WritePHYRegister(Config, PHY_BCR_OFFSET, PHY_AUTONEGOTIATION | PHY_RESTART_AUTONEGOTIATION) != FST_SUCCESS)
        {
            GMAC_HW_DEBUG_E("PHY_BCR_OFFSET 2 is error \r\n");
            ret = FST_FAILURE;
            goto gmac_init;
        }

        do
        {
            FGmac_ReadPHYRegister(Config, PHY_BSR_OFFSET, &RegValue);
            if (++Wait_Counter > 30)
            {
                GMAC_HW_DEBUG_E("PHY_BSR_OFFSET 2 wait is too long \r\n");
                ret = FST_ERROR_COUNT_MAX;
                goto gmac_init;
            }
        } while ((RegValue & PHY_AUTONEGO_COMPLETE) != PHY_AUTONEGO_COMPLETE);

        if (FGmac_ReadPHYRegister(Config, PHY_SPECIFIC_STATUS_OFFSET, &RegValue) != FST_SUCCESS)
        {
            GMAC_HW_DEBUG_E("PHY_SPECIFIC_STATUS_OFFSET is error \r\n");
            ret = FST_FAILURE;
            goto gmac_init;
        }
        /* Configure the MAC with the Duplex Mode fixed by the auto-negotiation process */
        if ((RegValue & PHY_SPECIFIC_STATUS_DUPLEX) != PHY_SPECIFIC_STATUS_DUPLEX)
        {
            /* Set Ethernet duplex mode to Full-duplex following the auto-negotiation */
            Config->DuplexMode = GMAC_MODE_HALFDUPLEX;
        }
        else
        {
            /* Set Ethernet duplex mode to Half-duplex following the auto-negotiation */
            Config->DuplexMode = GMAC_MODE_FULLDUPLEX;
        }
    }
    else
    {
        RegValue = 0;
        if (Config->DuplexMode == GMAC_MODE_FULLDUPLEX)
        {
            if (Config->Speed == GMAC_SPEED_1000M)
            {
                RegValue = PHY_FULLDUPLEX_1000M;
            }
            else if (Config->Speed == GMAC_SPEED_100M)
            {
                RegValue = PHY_FULLDUPLEX_100M;
            }
            else if (Config->Speed == GMAC_SPEED_10M)
            {
                RegValue = PHY_FULLDUPLEX_10M;
            }
        }
        else
        {
            if (Config->Speed == GMAC_SPEED_1000M)
            {
                RegValue = PHY_HALFDUPLEX_1000M;
            }
            else if (Config->Speed == GMAC_SPEED_100M)
            {
                RegValue = PHY_HALFDUPLEX_100M;
            }
            else if (Config->Speed == GMAC_SPEED_10M)
            {
                RegValue = PHY_HALFDUPLEX_10M;
            }
        }

        /* AutoNegotiation Disable */
        if (Gmac_WritePHYRegister(Config, PHY_BCR_OFFSET, RegValue) != FST_SUCCESS)
        {
            GMAC_HW_DEBUG_E("PHY_BCR_OFFSET 3 is error \r\n");
            ret = FST_FAILURE;
            goto gmac_init;
        }
    }
    Ft_GenericTimer_UsDelay(PHY_CONFIG_DELAY_US);

gmac_init:

    FGmac_MACDMAInit(Config);
    return ret;
}

void FGmac_TransmissionEnable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + GMAC_CONTROL_OFFSET);
    RegValue |= GMAC_CONTROL_TE;
    Ft_out32(Config->BaseAddress + GMAC_CONTROL_OFFSET, RegValue);
}

void FGmac_TransmissionDisable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + GMAC_CONTROL_OFFSET);
    RegValue &= ~GMAC_CONTROL_TE;
    Ft_out32(Config->BaseAddress + GMAC_CONTROL_OFFSET, RegValue);
}

void FGmac_ReceptionEnable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + GMAC_CONTROL_OFFSET);
    RegValue |= GMAC_CONTROL_RE;
    Ft_out32(Config->BaseAddress + GMAC_CONTROL_OFFSET, RegValue);
}

void FGmac_ReceptionDisable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + GMAC_CONTROL_OFFSET);
    RegValue &= ~GMAC_CONTROL_RE;
    Ft_out32(Config->BaseAddress + GMAC_CONTROL_OFFSET, RegValue);
}

void FGmac_FlushTransmitFIFO(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + DMA_OP_OFFSET);
    RegValue |= DMA_OP_FTF;
    Ft_out32(Config->BaseAddress + DMA_OP_OFFSET, RegValue);
}

void FGmac_DMATransmissionEnable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + DMA_OP_OFFSET);
    RegValue |= DMA_OP_ST;
    Ft_out32(Config->BaseAddress + DMA_OP_OFFSET, RegValue);
}

/**
 * @name: FGmac_DMATransmissionDisable
 * @msg:  Disable the DMA transmission
 * @param {FGmac_Config_t} *Config
 * @return {*}
 */
void FGmac_DMATransmissionDisable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + DMA_OP_OFFSET);
    RegValue &= ~DMA_OP_ST;
    Ft_out32(Config->BaseAddress + DMA_OP_OFFSET, RegValue);
}

/**
 * @name: FGmac_DMAReceptionEnable
 * @msg:  Enable the DMA reception
 * @param {FGmac_Config_t} *Config
 * @return {*}
 */
void FGmac_DMAReceptionEnable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + DMA_OP_OFFSET);
    RegValue |= DMA_OP_SR;
    Ft_out32(Config->BaseAddress + DMA_OP_OFFSET, RegValue);
}

void FGmac_DMAReceptionDisable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + DMA_OP_OFFSET);
    RegValue &= ~DMA_OP_SR;
    Ft_out32(Config->BaseAddress + DMA_OP_OFFSET, RegValue);
}

void FGmac_DMAReceptionTransmissionEnable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + DMA_OP_OFFSET);
    RegValue |= (DMA_OP_SR | DMA_OP_ST);
    Ft_out32(Config->BaseAddress + DMA_OP_OFFSET, RegValue);
}

void FGmac_DMAReceptionTransmissionDisable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + DMA_OP_OFFSET);
    RegValue &= ~(DMA_OP_SR | DMA_OP_ST);
    Ft_out32(Config->BaseAddress + DMA_OP_OFFSET, RegValue);
}

void FGmac_ReceptionTransmissionEnable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + GMAC_CONTROL_OFFSET);
    RegValue |= (GMAC_CONTROL_RE | GMAC_CONTROL_TE);
    Ft_out32(Config->BaseAddress + GMAC_CONTROL_OFFSET, RegValue);
}

void FGmac_ReceptionTransmissionDisable(FGmac_Config_t *Config)
{
    u32 RegValue;
    RegValue = Ft_in32(Config->BaseAddress + GMAC_CONTROL_OFFSET);
    RegValue &= ~(GMAC_CONTROL_RE | GMAC_CONTROL_TE);
    Ft_out32(Config->BaseAddress + GMAC_CONTROL_OFFSET, RegValue);
}
