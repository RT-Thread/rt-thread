/*
 * Copyright (c) 2023-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_tsw_drv.h"
#include "hpm_swap.h"

hpm_stat_t tsw_ep_set_mdio_config(TSW_Type *ptr, uint8_t port, uint8_t clk_div)
{
    ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MDIO_CFG = TSW_TSNPORT_MAC_MAC_MDIO_CFG_ENABLE_MASK | TSW_TSNPORT_MAC_MAC_MDIO_CFG_MDC_CLKDIV_SET(clk_div);

    return status_success;
}

hpm_stat_t tsw_ep_mdio_read(TSW_Type *ptr, uint8_t port, uint32_t phy_addr, uint32_t reg_addr, uint16_t *data)
{
    if (data == NULL) {
        return status_invalid_argument;
    }

    ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MDIO_CTRL = TSW_TSNPORT_MAC_MAC_MDIO_CTRL_OP_SET(MAC_MDIO_CTRL_OP_RD)
                                                        | TSW_TSNPORT_MAC_MAC_MDIO_CTRL_PHYAD_SET(phy_addr)
                                                        | TSW_TSNPORT_MAC_MAC_MDIO_CTRL_REGAD_SET(reg_addr)
                                                        | TSW_TSNPORT_MAC_MAC_MDIO_CTRL_INIT_SET(1);

    do {

    } while (TSW_TSNPORT_MAC_MAC_MDIO_CTRL_READY_GET(ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MDIO_CTRL) == 0);


    *data = TSW_TSNPORT_MAC_MAC_MDIO_RD_DATA_RD_DATA_GET(ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MDIO_RD_DATA);

    return status_success;
}

hpm_stat_t tsw_ep_mdio_write(TSW_Type *ptr, uint8_t port, uint32_t phy_addr, uint32_t reg_addr, uint16_t data)
{
    ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MDIO_WR_DATA = data;
    ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MDIO_CTRL = TSW_TSNPORT_MAC_MAC_MDIO_CTRL_OP_SET(MAC_MDIO_CTRL_OP_WR)
                                                        | TSW_TSNPORT_MAC_MAC_MDIO_CTRL_PHYAD_SET(phy_addr)
                                                        | TSW_TSNPORT_MAC_MAC_MDIO_CTRL_REGAD_SET(reg_addr)
                                                        | TSW_TSNPORT_MAC_MAC_MDIO_CTRL_INIT_SET(1);

    do {

    } while (TSW_TSNPORT_MAC_MAC_MDIO_CTRL_READY_GET(ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MDIO_CTRL) == 0);

    return status_success;
}

hpm_stat_t tsw_ep_enable_mac_ctrl(TSW_Type *ptr, uint8_t port, uint8_t mac_type, bool enable)
{
    uint32_t temp;

    temp = ptr->TSNPORT[port].MAC[mac_type].MAC_MAC_CTRL;
    temp &= ~(TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_MASK | TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_MASK);
    temp |= TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_SET(enable) | TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_SET(enable);

    ptr->TSNPORT[port].MAC[mac_type].MAC_MAC_CTRL = temp;

    if (!enable) {
        do {
            temp = ptr->TSNPORT[port].MAC[mac_type].MAC_MAC_CTRL;
        } while (TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_GET(temp) || TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_GET(temp));
    }

    return status_success;
}

hpm_stat_t tsw_ep_set_mac_addr(TSW_Type *ptr, uint8_t port, uint8_t *mac_addr, bool promisc)
{
    uint32_t temp;

	if (mac_addr == NULL) {
        return status_invalid_argument;
    }

    /* MAC must be disabled when changing mode */
    temp = ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MAC_CTRL;
    if (TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_GET(temp) || TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_GET(temp)) {
        return status_fail;
    }

    ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MACADDR_L = MAC_LO(mac_addr);
    ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MACADDR_H = MAC_HI(mac_addr) | TSW_TSNPORT_MAC_MAC_MACADDR_H_PROMISC_SET(promisc);

    return status_success;
}

hpm_stat_t tsw_ep_set_mac_mode(TSW_Type *ptr, uint8_t port, uint8_t gmii)
{
    uint32_t temp;

    /* MAC must be disabled when changing mode */
    temp = ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MAC_CTRL;
    if (TSW_TSNPORT_MAC_MAC_MAC_CTRL_RX_EN_GET(temp) || TSW_TSNPORT_MAC_MAC_MAC_CTRL_TX_EN_GET(temp)) {
        return status_fail;
    }

    temp &= ~(TSW_TSNPORT_MAC_MAC_MAC_CTRL_CLKSEL_MASK | TSW_TSNPORT_MAC_MAC_MAC_CTRL_PHYSEL_MASK | TSW_TSNPORT_MAC_MAC_MAC_CTRL_GMIIMODE_MASK);
    temp &= ~TSW_TSNPORT_MAC_MAC_MAC_CTRL_RESSTAT_MASK;

    temp |= TSW_TSNPORT_MAC_MAC_MAC_CTRL_CLKSEL_SET(1)
         | TSW_TSNPORT_MAC_MAC_MAC_CTRL_PHYSEL_SET(1)
         | TSW_TSNPORT_MAC_MAC_MAC_CTRL_GMIIMODE_SET(gmii);

    ptr->TSNPORT[port].MAC[TSW_RXFIFO_E1].MAC_MAC_CTRL = temp;

    return status_success;
}

/* data: the start address of data buffer must be aligned with 4 bytes */
/* length in bytes */
hpm_stat_t tsw_send(TSW_Type *ptr, uint32_t *buffer, uint32_t length, uint8_t id)
{
    uint32_t resp;

    /* Enable DMA: Write MM2S DMA CR (Run=1, SOE=0, IRQEN=0) */
    ptr->MM2S_DMA_CR |= TSW_MM2S_DMA_CR_RUN_MASK | TSW_MM2S_DMA_CR_MXLEN_SET(0xff);

    /* Set ADDRL */
    ptr->MM2S_ADDRLO = (uint32_t)buffer;

    /* Set Length */
    ptr->MM2S_LENGTH = length;

    /* Set Ctrl */
    ptr->MM2S_CTRL &= ~TSW_MM2S_CTRL_ID_MASK;
    ptr->MM2S_CTRL |= TSW_MM2S_CTRL_GO_MASK | TSW_MM2S_CTRL_ID_SET(id);

    /* Wait for DMA to finish transmission */
    do {

    } while (TSW_MM2S_DMA_SR_RBUFE_GET(ptr->MM2S_DMA_SR));

    /* Read response */
    resp = ptr->MM2S_RESP;

    if (TSW_MM2S_RESP_ID_GET(resp) == id) {


        /* Check decode error */
        if (TSW_MM2S_RESP_DECERR_GET(resp)) {

        }

        /* check slave error */
        if (TSW_MM2S_RESP_SLVERR_GET(resp)) {

        }
    }

    return status_success;
}

hpm_stat_t tsw_recv_setup(TSW_Type *ptr, uint32_t *buffer, uint32_t length, uint8_t id)
{
    /* Enable DMA-CTRL: Write S2MM_DMA_CR (Run=1, SOE=0, IRQEN=1) */
    ptr->S2MM_DMA_CR &= ~TSW_S2MM_DMA_CR_SOE_MASK; /* SOE=0 */

    ptr->S2MM_DMA_CR |= TSW_S2MM_DMA_CR_RUN_MASK;

    /* Set ADDRL */
    ptr->S2MM_ADDRLO = (uint32_t)buffer;

    /* Set Length */
    ptr->S2MM_LENGTH = length;

    /* Set Ctrl */
    ptr->S2MM_CTRL &= ~TSW_S2MM_CTRL_ID_MASK;
    ptr->S2MM_CTRL |= TSW_S2MM_CTRL_GO_MASK | TSW_S2MM_CTRL_ID_SET(id);

    return status_success;
}

uint32_t tsw_recv(TSW_Type *ptr, uint32_t *buffer, uint32_t length, uint8_t id)
{
    uint32_t resp;

    /* Wait for DMA to finish transmission */
    do {

    } while (TSW_S2MM_DMA_SR_RBUFE_GET(ptr->S2MM_DMA_SR));

     HPM_TSW->S2MM_DMA_SR = TSW_S2MM_DMA_SR_IRQ_MASK;

    /* Read response */
    resp = ptr->S2MM_RESP;

    if (TSW_S2MM_RESP_ID_GET(resp) == id) {

        /* Check decode error */
        if (TSW_S2MM_RESP_DECERR_GET(resp)) {
           /* printf("decode error\n"); */
        }

        /* check slave error */
        if (TSW_S2MM_RESP_SLVERR_GET(resp)) {
           /* printf("slave error\n"); */
        }
    }

    HPM_TSW->S2MM_CTRL |= TSW_S2MM_CTRL_GO_MASK;

    return ptr->S2MM_LENGTH;
}

void tsw_mac_lookup_bypass(TSW_Type *ptr, uint8_t dst_port)
{
    ptr->LU_MAIN_BYPASS &= ~TSW_LU_MAIN_BYPASS_DEST_MASK;
    ptr->LU_MAIN_BYPASS |= TSW_LU_MAIN_BYPASS_HIT_MASK | TSW_LU_MAIN_BYPASS_DEST_SET(dst_port);
    ptr->LU_MAIN_CTRL   |= TSW_LU_MAIN_CTRL_BYP_EN_MASK;
}

void tsw_set_cam_vlan_port(TSW_Type *ptr)
{
    ptr->APB2AXI_CAM_REQDATA_1 = 0x0f;
    ptr->APB2AXI_CAM_REQDATA_0 = (1 << 16)  /* VID = 1 */
                               | (1 << 8)   /* 1: Set one VLAN_PORT entry */
                               | (1 << 0);  /* CAM APB2AXIS channel selection. Always 1 for writing to VLAN_PORT table. */

}

/**
 *  speed: 00 1000mbps, 11 100mbps, 10 10mpbs
 *  itf: 000 MII; 001 RGMII; 100 RMII
 */
void tsw_port_gpr(TSW_Type *ptr, uint8_t port, uint8_t speed, uint8_t itf, uint8_t tx_dly, uint8_t rx_dly)
{
    ptr->TSNPORT[port].GPR_CTRL0 = TSW_TSNPORT_GPR_CTRL0_RXCLK_DLY_SEL_SET(rx_dly) | TSW_TSNPORT_GPR_CTRL0_TXCLK_DLY_SEL_SET(tx_dly);
    ptr->TSNPORT[port].GPR_CTRL2 = TSW_TSNPORT_GPR_CTRL2_MAC_SPEED_SET(speed) | TSW_TSNPORT_GPR_CTRL2_PHY_INTF_SEL_SET(itf);
}

void tsw_set_lookup_table(TSW_Type *ptr, uint16_t entry_num, uint8_t dest_port, uint64_t dest_mac)
{
    uint64_t dest_mac_temp;

    /* Create a new ALMEM entry. This will specify what will be done with those detected frames */
    if (TSW_APB2AXIS_ALMEM_STS_RDY_GET(ptr->APB2AXIS_ALMEM_STS)) {

        ptr->APB2AXIS_ALMEM_REQDATA_1 = TSW_APB2AXIS_ALMEM_REQDATA_1_WR_NRD_SET(1) | TSW_APB2AXIS_ALMEM_REQDATA_1_ENTRY_NUM_SET(entry_num);

        /* set forward to destination port, use PCP field, UTAG 1 and trigger the interface for sending the data */
        ptr->APB2AXIS_ALMEM_REQDATA_0 = TSW_APB2AXIS_ALMEM_REQDATA_0_UTAG_SET(1) |
                                        TSW_APB2AXIS_ALMEM_REQDATA_0_QSEL_SET(0) |
                                        TSW_APB2AXIS_ALMEM_REQDATA_0_DROP_SET(0) |
                                        TSW_APB2AXIS_ALMEM_REQDATA_0_QUEUE_SET(0) |
                                        TSW_APB2AXIS_ALMEM_REQDATA_0_DEST_SET(dest_port);
    }

    /* Create a new CAM entry */
    dest_mac_temp = __bswapdi2(dest_mac) >> 16;

    ptr->APB2AXI_CAM_REQDATA_2 = TSW_APB2AXI_CAM_REQDATA_2_VID_SET(1) | TSW_APB2AXI_CAM_REQDATA_2_DESTMAC_HI_SET((dest_mac_temp >> 32));
    ptr->APB2AXI_CAM_REQDATA_1 = TSW_APB2AXI_CAM_REQDATA_1_DESTMAC_LO_PORT_VEC_SET(dest_mac_temp);
    ptr->APB2AXI_CAM_REQDATA_0 = TSW_APB2AXI_CAM_REQDATA_0_ENTRY_NUM_SET(entry_num) |
                                 TSW_APB2AXI_CAM_REQDATA_0_TYPE_SET(1) |   /* Set one DEST_MAC/VLAN_ID entry */
                                 TSW_APB2AXI_CAM_REQDATA_0_CH_SET(0);      /* CAM APB2AXIS channel selection. Always 0 for writing to DEST_MAC/VLAN_ID */


    /* Add a new VLAN_PORT entry (VID 1) */
    ptr->APB2AXI_CAM_REQDATA_1 = 0x0f;
    ptr->APB2AXI_CAM_REQDATA_0 = (1 << 16)  /* VID = 1 */
                               | (1 << 8)  /* 1: Set one VLAN_PORT entry */
                               | (1 << 0); /* CAM APB2AXIS channel selection. Always 1 for writing to VLAN_PORT table. */

}

void tsw_set_internal_frame_action(TSW_Type *ptr, uint8_t dest_port)
{
    ptr->LU_MAIN_INTF_ACTION &= ~TSW_LU_MAIN_INTF_ACTION_DEST_MASK;
    ptr->LU_MAIN_INTF_ACTION |= TSW_LU_MAIN_INTF_ACTION_DEST_SET(dest_port);
}

void tsw_set_broadcast_frame_action(TSW_Type *ptr, uint8_t dest_port)
{
    ptr->LU_MAIN_BC_ACTION &= ~TSW_LU_MAIN_BC_ACTION_DEST_MASK;
    ptr->LU_MAIN_BC_ACTION |= TSW_LU_MAIN_BC_ACTION_DEST_SET(dest_port);
}

void tsw_set_unknown_frame_action(TSW_Type *ptr, uint8_t dest_port)
{
    ptr->LU_MAIN_NN_ACTION &= ~TSW_LU_MAIN_NN_ACTION_DEST_MASK;
    ptr->LU_MAIN_NN_ACTION |= TSW_LU_MAIN_NN_ACTION_DEST_SET(dest_port);
}

void tsw_clear_cam(TSW_Type *ptr)
{
    ptr->LU_MAIN_HITMEM &= ~TSW_LU_MAIN_HITMEM_CAMMEMCLR_MASK;
    ptr->LU_MAIN_HITMEM |= TSW_LU_MAIN_HITMEM_CAMMEMCLR_MASK;
}

void tsw_enable_store_forward_mode(TSW_Type *ptr, uint8_t port)
{
    ptr->TSNPORT[port].RXFIFO[TSW_RXFIFO_E1].SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG |= TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MODE_STORE_FW_MASK;
}

void tsw_disable_store_forward_mode(TSW_Type *ptr, uint8_t port)
{
    ptr->TSNPORT[port].RXFIFO[TSW_RXFIFO_E1].SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG &= ~TSW_TSNPORT_RXFIFO_SW_CTRL_IGRESS_RX_FDFIFO_E_OUT_CONFIG_MODE_STORE_FW_MASK;
}