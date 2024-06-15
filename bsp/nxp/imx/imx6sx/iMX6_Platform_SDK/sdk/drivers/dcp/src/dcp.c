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

#include "dcp/dcp.h"

#ifdef DCP_DEBUG
#define TRACE(fmt, arg...) 	printf(fmt, ##arg)
#else
#define TRACE(fmt, arg...)	
#endif

/*! 
 * @brief Configure the dcp channel
 *  
 * @para    ch   	 the channel index
 * @para    pkt_list	 pointer to work packet chain 
 * @return  0 if succeed 
 */
int dcp_config_channel(uint32_t ch, dcp_work_pkt_p pkt_list)
{	
    HW_DCP_CHnCMDPTR_WR(ch, (uint32_t)pkt_list);
	
    return 0;
}

/*! 
 * @brief Get the status of the dcp channel
 *  
 * @para    ch    the channel index
 * @return	0 if succeed 
 */
int dcp_start_channel(uint32_t ch, uint32_t pkt_num)
{
	 HW_DCP_CHnSEMA_WR(ch, pkt_num);

	 return 0;
}

/*! 
 * @brief Get the status of the dcp channel
 *  
 * @para    ch    the channel index
 * @return	0 if succeed 
 */
int dcp_wait_channel_cmpl(uint32_t ch)
{
	while(((HW_DCP_STAT.B.IRQ) & (0x1<<ch)) == 0);
	HW_DCP_STAT_CLR(0x1<<ch);
	
	return 0;
}

/*!
 * @breif	Initialize the DCP module
 * @para	none
 * @return 	none
 */
int dcp_init(void)
{
	// reset the dcp module
    HW_DCP_CTRL_SET(BF_DCP_CTRL_SFTRST(1));
    HW_DCP_CTRL_CLR(BF_DCP_CTRL_SFTRST(1));
	// gate on the clk
    HW_DCP_CTRL_CLR(BF_DCP_CTRL_CLKGATE(1));
	// all the channle shared the same IRQ, enable all the channels
    HW_DCP_CHANNELCTRL_SET(BM_DCP_CHANNELCTRL_CH0_IRQ_MERGED | BM_DCP_CHANNELCTRL_ENABLE_CHANNEL);
	// enable channle interrupt
    HW_DCP_CTRL_SET(BM_DCP_CTRL_CHANNEL_INTERRUPT_ENABLE);
	
    return 0;
}

/*! 
 * @brief Put the dcp into rst mode and gate off its clock
 *
 *  @para	none
 *  @return 	none
 */
int dcp_deinit(void)
{
    HW_DCP_CTRL_SET(BF_DCP_CTRL_SFTRST(1));
    HW_DCP_CTRL_CLR(BF_DCP_CTRL_CLKGATE(1));

    return 0;
}

/*! 
 * @brief memory copy routine impletemented using DCP channel 1
 *
 *  @para	dst	pointer to destination address
 *  @para	src	pointer to source address
 *  @para	size	bytes to copy
 *  @return 	0 if succeed
 */
int dcp_memcpy(void* dst, void* src, uint32_t size)
{
    dcp_work_pkt_p pkt = (dcp_work_pkt_p)malloc(sizeof(dcp_work_pkt_t));
	
    pkt->next_pkt = 0;
    pkt->ctrl0.U = 0;
    pkt->ctrl0.B.ENABLE_MEMCOPY = 1;
    pkt->ctrl0.B.DECR_SEMAPHORE = 1;
    pkt->ctrl0.B.ENABLE_BLIT = 0;
    pkt->ctrl0.B.INTERRUPT = 1;
    pkt->ctrl1.U = 0;
    pkt->dst_buf = dst;
    pkt->src_buf = src;
    pkt->buf_size = size;
    HW_DCP_CHnCMDPTR_WR(DCP_CHANNEL_1, (unsigned int)pkt);

    dcp_start_channel(DCP_CHANNEL_1, 1);
    dcp_wait_channel_cmpl(DCP_CHANNEL_1);
	
    free(pkt);
	
    return 0;
}

/*! 
 * @brief memory copy routine impletemented using all the four DCP channels
 *
 *  @para	dst	pointer to destination address
 *  @para	src	pointer to source address
 *  @para	size	bytes to copy
 *  @return 	0 if succeed
 */
int dcp_memcpy_4ch(void* dst, void* src, uint32_t size)
{
    dcp_work_pkt_p pkt = (dcp_work_pkt_p)malloc(DCP_CHANNEL_MAX * sizeof(dcp_work_pkt_t));
    dcp_work_pkt_p pkt_ptr;
    int i;

    pkt_ptr = pkt;
    for(i = 0; i < DCP_CHANNEL_MAX; i++, pkt_ptr++) {
	pkt_ptr->next_pkt = 0;
	pkt_ptr->ctrl0.U = 0;
	pkt_ptr->ctrl0.B.ENABLE_MEMCOPY = 1;
	pkt_ptr->ctrl0.B.DECR_SEMAPHORE = 1;
	pkt_ptr->ctrl0.B.ENABLE_BLIT = 0;
	pkt_ptr->ctrl0.B.INTERRUPT = 1;
	pkt_ptr->ctrl1.U = 0;
	pkt_ptr->dst_buf = dst + (size/DCP_CHANNEL_MAX) * i;
	pkt_ptr->src_buf = src + (size/DCP_CHANNEL_MAX) * i;
	pkt_ptr->buf_size = size/DCP_CHANNEL_MAX;
	HW_DCP_CHnCMDPTR_WR(DCP_CHANNEL_1, (unsigned int)pkt_ptr);
    }  
    pkt_ptr->buf_size = size - (size/DCP_CHANNEL_MAX) * i;

    dcp_start_channel(DCP_CHANNEL_1, 1);
    dcp_start_channel(DCP_CHANNEL_2, 1);
    dcp_start_channel(DCP_CHANNEL_3, 1);
    dcp_start_channel(DCP_CHANNEL_4, 1);

    dcp_wait_channel_cmpl(DCP_CHANNEL_1);
    dcp_wait_channel_cmpl(DCP_CHANNEL_2);
    dcp_wait_channel_cmpl(DCP_CHANNEL_3);
    dcp_wait_channel_cmpl(DCP_CHANNEL_4);

    free(pkt);

    return 0;
}
