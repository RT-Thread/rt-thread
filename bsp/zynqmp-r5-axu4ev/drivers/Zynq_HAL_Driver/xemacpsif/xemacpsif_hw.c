/*
 * Copyright (C) 2010 - 2019 Xilinx, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 */

#include "netif/xemacpsif.h"
#include "lwipopts.h"

#if XPAR_GIGE_PCS_PMA_1000BASEX_CORE_PRESENT == 1 || \
    XPAR_GIGE_PCS_PMA_SGMII_CORE_PRESENT == 1
#define PCM_PMA_CORE_PRESENT
#else
#undef PCM_PMA_CORE_PRESENT
#endif

u32_t link_speed = 100;
extern XEmacPs_Config XEmacPs_ConfigTable[];
extern u32_t phymapemac0[32];
extern u32_t phymapemac1[32];
extern u32_t phyaddrforemac;
extern enum ethernet_link_status eth_link_status;

#ifdef OS_IS_FREERTOS
extern long xInsideISR;
#endif

XEmacPs_Config *xemacps_lookup_config(unsigned mac_base)
{
    XEmacPs_Config *cfgptr = NULL;
    s32_t i;

    for (i = 0; i < XPAR_XEMACPS_NUM_INSTANCES; i++) {
        if (XEmacPs_ConfigTable[i].BaseAddress == mac_base) {
            cfgptr = &XEmacPs_ConfigTable[i];
            break;
        }
    }

    return (cfgptr);
}

void init_emacps(xemacpsif_s *xemacps, struct netif *netif)
{
    XEmacPs *xemacpsp;
    s32_t status = XST_SUCCESS;
    u32_t i;
    u32_t phyfoundforemac0 = FALSE;
    u32_t phyfoundforemac1 = FALSE;

    xemacpsp = &xemacps->emacps;

#ifdef ZYNQMP_USE_JUMBO
    XEmacPs_SetOptions(xemacpsp, XEMACPS_JUMBO_ENABLE_OPTION);
#endif

#ifdef LWIP_IGMP
    XEmacPs_SetOptions(xemacpsp, XEMACPS_MULTICAST_OPTION);
#endif

    /* set mac address */
    status = XEmacPs_SetMacAddress(xemacpsp, (void*)(netif->hwaddr), 1);
    if (status != XST_SUCCESS) {
        xil_printf("In %s:Emac Mac Address set failed...\r\n",__func__);
    }

    XEmacPs_SetMdioDivisor(xemacpsp, MDC_DIV_224);

/*  Please refer to file header comments for the file xemacpsif_physpeed.c
 *  to know more about the PHY programming sequence.
 *  For PCS PMA core, phy_setup_emacps is called with the predefined PHY address
 *  exposed through xaparemeters.h
 *  For RGMII case, assuming multiple PHYs can be present on the MDIO bus,
 *  detect_phy is called to get the addresses of the PHY present on
 *  a particular MDIO bus (emac0 or emac1). This address map is populated
 *  in phymapemac0 or phymapemac1.
 *  phy_setup_emacps is then called for each PHY present on the MDIO bus.
 */
#ifdef PCM_PMA_CORE_PRESENT
#ifdef  XPAR_GIGE_PCS_PMA_1000BASEX_CORE_PRESENT
    link_speed = phy_setup_emacps(xemacpsp, XPAR_PCSPMA_1000BASEX_PHYADDR);
#elif XPAR_GIGE_PCS_PMA_SGMII_CORE_PRESENT
    link_speed = phy_setup_emacps(xemacpsp, XPAR_PCSPMA_SGMII_PHYADDR);
#endif
#else
    detect_phy(xemacpsp);
    for (i = 31; i > 0; i--) {
        if (xemacpsp->Config.BaseAddress == XPAR_XEMACPS_0_BASEADDR) {
            if (phymapemac0[i] == TRUE) {
                link_speed = phy_setup_emacps(xemacpsp, i);
                phyfoundforemac0 = TRUE;
                phyaddrforemac = i;
            }
        } else {
            if (phymapemac1[i] == TRUE) {
                link_speed = phy_setup_emacps(xemacpsp, i);
                phyfoundforemac1 = TRUE;
                phyaddrforemac = i;
            }
        }
    }
    /* If no PHY was detected, use broadcast PHY address of 0 */
    if (xemacpsp->Config.BaseAddress == XPAR_XEMACPS_0_BASEADDR) {
        if (phyfoundforemac0 == FALSE)
            link_speed = phy_setup_emacps(xemacpsp, 0);
    } else {
        if (phyfoundforemac1 == FALSE)
            link_speed = phy_setup_emacps(xemacpsp, 0);
    }
#endif

    if (link_speed == XST_FAILURE) {
        eth_link_status = ETH_LINK_DOWN;
        xil_printf("Phy setup failure %s \n\r",__func__);
        return;
    } else {
        eth_link_status = ETH_LINK_UP;
    }

    XEmacPs_SetOperatingSpeed(xemacpsp, link_speed);
    /* Setting the operating speed of the MAC needs a delay. */
    {
        volatile s32_t wait;
        for (wait=0; wait < 20000; wait++);
    }
}

void init_emacps_on_error (xemacpsif_s *xemacps, struct netif *netif)
{
    XEmacPs *xemacpsp;
    s32_t status = XST_SUCCESS;

    xemacpsp = &xemacps->emacps;

    /* set mac address */
    status = XEmacPs_SetMacAddress(xemacpsp, (void*)(netif->hwaddr), 1);
    if (status != XST_SUCCESS) {
        xil_printf("In %s:Emac Mac Address set failed...\r\n",__func__);
    }

    XEmacPs_SetOperatingSpeed(xemacpsp, link_speed);

    /* Setting the operating speed of the MAC needs a delay. */
    {
        volatile s32_t wait;
        for (wait=0; wait < 20000; wait++);
    }
}

void setup_isr (struct xemac_s *xemac)
{
    xemacpsif_s   *xemacpsif;

    xemacpsif = (xemacpsif_s *)(xemac->state);
    /*
     * Setup callbacks
     */
    XEmacPs_SetHandler(&xemacpsif->emacps, XEMACPS_HANDLER_DMASEND,
                     (void *) emacps_send_handler,
                     (void *) xemac);

    XEmacPs_SetHandler(&xemacpsif->emacps, XEMACPS_HANDLER_DMARECV,
                    (void *) emacps_recv_handler,
                    (void *) xemac);

    XEmacPs_SetHandler(&xemacpsif->emacps, XEMACPS_HANDLER_ERROR,
                    (void *) emacps_error_handler,
                    (void *) xemac);
}

void start_emacps (xemacpsif_s *xemacps)
{
    /* start the temac */
    XEmacPs_Start(&xemacps->emacps);
}

void restart_emacps_transmitter (xemacpsif_s *xemacps) {
    u32_t Reg;
    Reg = XEmacPs_ReadReg(xemacps->emacps.Config.BaseAddress,
                    XEMACPS_NWCTRL_OFFSET);
    Reg = Reg & (~XEMACPS_NWCTRL_TXEN_MASK);
    XEmacPs_WriteReg(xemacps->emacps.Config.BaseAddress,
                                        XEMACPS_NWCTRL_OFFSET, Reg);

    Reg = XEmacPs_ReadReg(xemacps->emacps.Config.BaseAddress,
                        XEMACPS_NWCTRL_OFFSET);
    Reg = Reg | (XEMACPS_NWCTRL_TXEN_MASK);
    XEmacPs_WriteReg(xemacps->emacps.Config.BaseAddress,
                                        XEMACPS_NWCTRL_OFFSET, Reg);
}

void emacps_error_handler(void *arg,u8 Direction, u32 ErrorWord)
{
    struct xemac_s *xemac;
    xemacpsif_s   *xemacpsif;
    XEmacPs_BdRing *rxring;
    XEmacPs_BdRing *txring;
#ifdef OS_IS_FREERTOS
    xInsideISR++;
#endif

    xemac = (struct xemac_s *)(arg);
    xemacpsif = (xemacpsif_s *)(xemac->state);
    rxring = &XEmacPs_GetRxRing(&xemacpsif->emacps);
    txring = &XEmacPs_GetTxRing(&xemacpsif->emacps);

    if (ErrorWord != 0) {
        switch (Direction) {
            case XEMACPS_RECV:
            if (ErrorWord & XEMACPS_RXSR_HRESPNOK_MASK) {
                LWIP_DEBUGF(NETIF_DEBUG, ("Receive DMA error\r\n"));
                HandleEmacPsError(xemac);
            }
            if (ErrorWord & XEMACPS_RXSR_RXOVR_MASK) {
                LWIP_DEBUGF(NETIF_DEBUG, ("Receive over run\r\n"));
                emacps_recv_handler(arg);
                setup_rx_bds(xemacpsif, rxring);
            }
            if (ErrorWord & XEMACPS_RXSR_BUFFNA_MASK) {
                LWIP_DEBUGF(NETIF_DEBUG, ("Receive buffer not available\r\n"));
                emacps_recv_handler(arg);
                setup_rx_bds(xemacpsif, rxring);
            }
            break;
            case XEMACPS_SEND:
            if (ErrorWord & XEMACPS_TXSR_HRESPNOK_MASK) {
                LWIP_DEBUGF(NETIF_DEBUG, ("Transmit DMA error\r\n"));
                HandleEmacPsError(xemac);
            }
            if (ErrorWord & XEMACPS_TXSR_URUN_MASK) {
                LWIP_DEBUGF(NETIF_DEBUG, ("Transmit under run\r\n"));
                HandleTxErrors(xemac);
            }
            if (ErrorWord & XEMACPS_TXSR_BUFEXH_MASK) {
                LWIP_DEBUGF(NETIF_DEBUG, ("Transmit buffer exhausted\r\n"));
                HandleTxErrors(xemac);
            }
            if (ErrorWord & XEMACPS_TXSR_RXOVR_MASK) {
                LWIP_DEBUGF(NETIF_DEBUG, ("Transmit retry excessed limits\r\n"));
                HandleTxErrors(xemac);
            }
            if (ErrorWord & XEMACPS_TXSR_FRAMERX_MASK) {
                LWIP_DEBUGF(NETIF_DEBUG, ("Transmit collision\r\n"));
                // process_sent_bds(xemacpsif, txring);
            }
            break;
        }
    }
#ifdef OS_IS_FREERTOS
    xInsideISR--;
#endif
}
