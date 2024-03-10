/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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

#include "sdk.h"
#include "flexcan/flexcan.h"
#include "registers/regsflexcan.h"

void can2_rx_handler(void);

/* CAN module data structures */
uint32_t can1_port = HW_FLEXCAN1;
uint32_t can2_port = HW_FLEXCAN2;

uint32_t can_test_count;

/*! ------------------------------------------------------------
 * CAN Test (loopback can1/can2 ports)
 *  ------------------------------------------------------------
 */
void flexcan_test(void)
{
    int i;
	uint8_t ch;
    //struct imx_flexcan can1, can2;    

    //can_set_can_attributes(&can1, KBPS_500, &can1_port);
    //can_set_can_attributes(&can2, KBPS_500, &can2_port);
    //can_update_bitrate(&can1);
    //can_update_bitrate(&can2);

    printf("\n---- Running CAN1/2 loopback test ----\n");
	printf("Please plugin Sabre_ai board onto the main base board\n");
	printf("Connect pin 6 in J35 to slot 7 in J34\n");
	printf("Connect pin 7 in J35 to slot 2 in J34\n");
    printf("Please make sure accessories are availalbe. Type \"y\" or \"Y\" to confirm.\n");
	do {
		ch = getchar();
	} while (ch == (uint8_t) 0xFF);
	
	if((ch != 'Y') && (ch != 'y')){
		printf("\nTest exit.\n");
		return ;
	}
    can_test_count = 0;

    can_init(can1_port, CAN_LAST_MB);  // max 64 MB 0-63
    can_init(can2_port, CAN_LAST_MB);  // last mb is MB[63]

    printf("CAN1-TX and CAN2-RX\n");
    // configure CAN1 MBs as Tx, and CAN2 MBs as Rx
    // set-up 8 MBs for the test
    for (i = 1; i < 9; i++) {
        set_can_mb(can1_port, i, 0x0c000000 + (i << 16), 0x0a000000 + (i << 20), 0x12345678,
                   0x87654321);
        set_can_mb(can2_port, i, 0x04000000 + (i << 16), 0x0a000000 + (i << 20), 0, 0);
        can_enable_mb_interrupt(can2_port, i); // enable MB interrupt for idMB=i
    }

    //enable CAN2 interrupt
    can_setup_interrupt(can2_port, can2_rx_handler, true);

    // init CAN1 MB0
    can_exit_freeze(can2_port);    // Rx
    can_exit_freeze(can1_port);    // Tx

    while (!(can_test_count)) ;

    can_freeze(can2_port);     // Rx
    can_freeze(can1_port);     // Tx

    printf("%d MBs were transmitted \n", can_test_count);
    printf("---- CAN1/2 test complete ----\n");
}

/*!
 * Can2 receive ISR function
 */
void can2_rx_handler(void)
{
    int i = 0;
    uint64_t iflag;

    iflag = can_mb_int_flag(can2_port);
    if(iflag !=0L){
        for (i = 0; i < 64; i++) {
            if (iflag & (1L << i)) {
		can_mb_int_ack(can2_port, i);
                printf("\tCAN2 MB:%d Recieved:\n", i);
                print_can_mb(can2_port, i);
                can_test_count++;
            }
        }
    }
}
