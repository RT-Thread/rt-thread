/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file fec_test.c
 * @brief Test for the ethernet interface through the FEC + PHY.
 *
 * @ingroup diag_fec
 */

#include "sdk.h"
#include "fec/fec.h"
#include "utility/menu.h"
#include "registers/regsccmanalog.h"
#include "registers/regsiomuxc.h"

const char g_fec_enet_test_name[] = "FEC Ethernet Test";

static imx_fec_priv_t fec0;
static unsigned char pkt_send[2048], pkt_recv[2048];
static unsigned char mac_addr0[6] = { 0x00, 0x04, 0x9f, 0x00, 0x00, 0x01 };

extern int imx_fec_mii_type(imx_fec_priv_t * dev, enum imx_mii_type mii_type);

static int imx_fec_setup(void)
{
	unsigned int reg=0;
//	unsigned int timeout = 100000;
	
	/* config iomux */
	fec_iomux_config();
	
	/* gpio4_21 controls the power of FEC PHY */
	gpio_set_direction(GPIO_PORT4, 21, GPIO_GDIR_OUTPUT);
	gpio_set_level(GPIO_PORT4, 21, GPIO_HIGH_LEVEL);
	hal_delay_us(100000);
	
	/* get enet tx reference clk from internal clock from anatop
	 * GPR1[14] = 0, GPR1[18:17] = 00
	 */
	reg = HW_IOMUXC_GPR1_RD();
	reg &= ~(BM_IOMUXC_GPR1_ENET_CLK_SEL_FROM_ANALOG_LOOPBACK);
	reg &= ~(BM_IOMUXC_GPR1_ENET_CLK_SEL);
	HW_IOMUXC_GPR1_WR(reg);
	
	/* Enable ENET PLLs */
	/* already done in ccm_init() */

	return 0;
}

static void pkt_fill(unsigned char *packet, unsigned char *eth_addr, unsigned char seed, int length)
{
    unsigned char *pkt = packet;
    unsigned char eth_type[2] = { 0x08, 0x00 };
    int i;
    memset(pkt, 0xff, 6);
    pkt += 6;
    memcpy(pkt, eth_addr, 6);
    pkt += 6;
    memcpy(pkt, eth_type, 2);
    pkt += 2;

    for (i = 0; i < (length - 14); i++)
        *pkt++ = (seed + i) & 0xff;

    return;
}

static int pkt_compare(unsigned char *packet1, unsigned char *packet2, int length)
{
    int i = 0;
    unsigned char *pkt1 = packet1, *pkt2 = packet2;

    for (i = 0; i < length; i++) {
        if (*(pkt1 + i) != *(pkt2 + i))
            break;
    }

    if (i < length)
        return TEST_FAILED;
    else
        return 0;
}


/*!
 * This test performs a loopback transfer on the RGMII interface through
 * an external AR8031 giga ethernet PHY.
 * 
 * @return TEST_PASSED or TEST_FAILED
 */
test_return_t fec_test(void)
{
    imx_fec_priv_t *dev0 = &fec0;
    int pkt_len_send = 0, pkt_len_recv = 0, ret = 0, i;
    unsigned int fec_events = 0;
    const char* indent = menu_get_indent();

    // Enet loopback test
    printf("\n%sWould you like to run the Ethernet loopback test?\n \
           (Please note that in order to run the test, you need to\n \
           first plug in a loopback cable to the Ethernet port) \n", indent);
    if (!is_input_char('y', NULL))
        return TEST_BYPASSED;
	
    //setup iomux and power for FEC
	imx_fec_setup();

    //init fec0
    imx_fec_init(dev0, REGS_FEC_BASE, 0);
    imx_fec_mii_type(dev0, RMII);
    //init phy0.
    imx_fec_phy_init(dev0);

    printf("FEC %0d: [ %s ] [ %s ] [ %s ]:\n", dev0->phy_addr,
           (dev0->status & FEC_STATUS_FULL_DPLX) ? "FULL_DUPLEX" : "HALF_DUPLEX",
           (dev0->status & FEC_STATUS_LINK_ON) ? "connected" : "disconnected",
           (dev0->status & FEC_STATUS_1000M) ? "1000M bps" : (dev0->status & FEC_STATUS_100M) ?
           "100M bps" : "10M bps");

    //check phy status
    if (!(dev0->status & FEC_STATUS_LINK_ON)) {
        printf("%sFEC link status check fail\n", indent);
        return TEST_FAILED;
    }

    imx_fec_start(dev0, mac_addr0);

    //send packet
    printf("send packet\n");
    pkt_len_send = 1500;
    pkt_fill(pkt_send, mac_addr0, 0x23, pkt_len_send);
    imx_fec_send(dev0, pkt_send, pkt_len_send, 1);
    fec_events = 0;

    for (i = 0; i < 100; i++) {
        fec_events = imx_fec_poll(dev0);

        if (FEC_EVENT_TX & fec_events) {
            printf("fec_events = %08x\n", fec_events);
            break;
        }

        hal_delay_us(100);
    }

    if (!(FEC_EVENT_TX & fec_events)) {
        printf("%sFEC tx fail\n", indent);
        return TEST_FAILED;
    }

    if (!(FEC_EVENT_RX & fec_events)) {
        printf("%sFEC rx fail\n", indent);
        return TEST_FAILED;
    }

    pkt_len_recv = 0;
    imx_fec_recv(dev0, pkt_recv, &pkt_len_recv);

    if (pkt_len_recv != pkt_len_send) {
        printf("%sFEC rx length check fail \n", indent);
        return TEST_FAILED;
    }

    ret = pkt_compare(pkt_send, pkt_recv, pkt_len_send);

    if (ret != 0) {
        printf("%sFEC rx packet check fail \n", indent);
        return TEST_FAILED;
    }
#ifdef DEBUG_PRINT
    printf("FEC rx ok\n");
#endif

    printf("%s FEC loopback test pass\n", indent);

    imx_fec_stop(dev0);
    return TEST_PASSED;
}
