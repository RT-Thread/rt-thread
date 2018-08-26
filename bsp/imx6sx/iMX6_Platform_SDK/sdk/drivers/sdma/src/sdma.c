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
 * @file sdma.c
 * @brief SDMA library

 * @ingroup diag_sdma
 */

#include "sdk.h"
#include "sdma_priv.h"
#include "core/interrupt.h"
#include "registers/regssdmaarm.h"

extern sdma_script_info_t script_info;

static sdma_env_p sdma_envp;

static int32_t sdma_initialized = FALSE;

/*---------------------------------------- static functions --------------------------------------------*/
static void set_channel_override(int32_t channel, int32_t hostovr, int32_t dspovr, int32_t evtovr)
{
    if (hostovr == TRUE)
        HW_SDMAARM_HOSTOVR_SET(1 << channel);
    else
        HW_SDMAARM_HOSTOVR_CLR(1 << channel);

    if (dspovr == TRUE)
        HW_SDMAARM_DSPOVR_SET(1 << channel);
    else
        HW_SDMAARM_DSPOVR_CLR(1 << channel);

    if (evtovr == TRUE)
        HW_SDMAARM_EVTOVR_SET(1 << channel);
    else
        HW_SDMAARM_EVTOVR_CLR(1 << channel);
}

static int32_t sdma_load_init_script(uint32_t sdma_dst, uint32_t ram_src, uint32_t count)
{
    HW_SDMAARM_SDMA_CHNPRIn_WR(0,SDMA_CHANNEL_PRIORITY_HIGH);

    /* Set up buffer descriptor */
    sdma_envp->chan0BD.mode = (SDMA_CMD_C0_SET_PM << SDMA_BD_MODE_CMD_SHIFT)
        | SDMA_FLAGS_BUSY | (SDMA_BD_MODE_CNT_MASK & (count >> 1));
    sdma_envp->chan0BD.buf_addr = (uint32_t)ram_src;
    sdma_envp->chan0BD.ext_buf_addr = sdma_dst;

    /* Set current BD pointer therefore could be reused */
    sdma_envp->sdma_ccb[0].currentBDptr = (uint32_t)&sdma_envp->chan0BD;

    /* Start channel 0 - start DMA transfer */
    if (SDMA_RETV_FAIL == sdma_channel_start(0)) {
        return FALSE;
    }

    /* Wait for channel transfer complete */
    while ((HW_SDMAARM_STOP_STAT_RD()& 1) != 0) ;

    /* Check BD mode flags */
    if ((sdma_envp->chan0BD.mode & SDMA_FLAGS_BUSY) == SDMA_FLAGS_BUSY) {
        return FALSE;
    }

    if ((sdma_envp->chan0BD.mode & SDMA_FLAGS_ERROR) == SDMA_FLAGS_ERROR) {
        return FALSE;
    }

    HW_SDMAARM_SDMA_CHNPRIn_WR(0,SDMA_CHANNEL_PRIORITY_FREE);

    return TRUE;
}

static int32_t sdma_write_channel_context(unsigned char channel, uint32_t source_addr)
{
    /* Enable channel 0 */
    HW_SDMAARM_SDMA_CHNPRIn_WR(0,SDMA_CHANNEL_PRIORITY_HIGH);

    /* Setup BD, extended buffer not used */
    sdma_envp->chan0BD.mode = ((((channel << 3) | SDMA_CMD_C0_SETCTX) << SDMA_BD_MODE_CMD_SHIFT) |
                               SDMA_FLAGS_BUSY | (sizeof(sdma_channel_context_t) / 4));
    sdma_envp->chan0BD.buf_addr = (uint32_t)source_addr;

    /* Reset current BD pointer since it would be incremented after each transfer */
    sdma_envp->sdma_ccb[0].currentBDptr = (uint32_t)&sdma_envp->chan0BD;

    /* Start channel 0 - start DMA transfer */
    if (SDMA_RETV_FAIL == sdma_channel_start(0)) {
        return FALSE;
    }

    /* Wait for channel transfer complete */
    while ((HW_SDMAARM_STOP_STAT_RD()& 1) != 0) ;

    /* Check BD mode flags */
    if ((sdma_envp->chan0BD.mode & SDMA_FLAGS_BUSY) == SDMA_FLAGS_BUSY) {
        return FALSE;
    }

    if ((sdma_envp->chan0BD.mode & SDMA_FLAGS_ERROR) == SDMA_FLAGS_ERROR) {
        return FALSE;
    }

    HW_SDMAARM_SDMA_CHNPRIn_WR(0,SDMA_CHANNEL_PRIORITY_FREE);

    return TRUE;
}

static int32_t validate_buffer_descriptor(sdma_bd_p bdp, uint32_t *num_bd)
{
    uint32_t idx = 0;

    while (idx < (uint32_t)SDMA_NUM_BUF_DESC) {
        if ((bdp[idx].mode & SDMA_FLAGS_CONT) == 0) {
            break;
        }

        idx++;
    }

    if (idx < SDMA_NUM_BUF_DESC) {
        *num_bd = idx + 1;
        return TRUE;
    }

    return FALSE;
}

static void sdma_channel_default_isr(uint32_t channel)
{
    printf("Channel%d interupt.\n", channel);
}

static sdma_channel_isr sdma_channel_isr_list[SDMA_NUM_CHANNELS] = { NULL };

static void sdma_interrupt_handler(void)
{
    uint32_t int_flag = HW_SDMAARM_INTR_RD();

    uint32_t i;
    for (i = 0; i < 32; i++) {
        if (int_flag & (0x01 << i)) {
            if (NULL != sdma_channel_isr_list[i]) {
                sdma_channel_isr_list[i] (i);
            }

            HW_SDMAARM_INTR_SET(0x01 << i);
        }
    }
}

/*---------------------------------------- global functions --------------------------------------------*/

/*! 
 * Initialize the system environment for SDMA. In this function will:
 *    1. Reset SDMA controller
 *    2. Setup configurations like AP DMA/SDMA clock ratio, CCB base address etc
 *    3. Use channel 0 script to load the RAM scripts into SDMA RAM
 *
 * @param    env_buf un-cacheable and un-bufferable buffer allocated by user
 * @param    base_addr base address of SDMA registers in AP
 *
 * @return   0 on success, -1 when fail to download RAM scripts to SDMA RAM,
 *           -2 when environment pointer is NULL
 */
int32_t sdma_init(uint32_t *env_buf, uint32_t base_addr)
{
    sdma_env_p envp = (sdma_env_p) env_buf;
    int32_t idx;

    if (sdma_initialized == TRUE) {
        return SDMA_RETV_SUCCESS;
    }

    if (envp == NULL) {
        return SDMA_RETV_NULLP;
    }

    sdma_envp = envp;
    HW_SDMAARM_RESET.B.RESCHED = 1;
    HW_SDMAARM_RESET.B.RESET = 1;
    while(HW_SDMAARM_RESET.B.RESET == 1);
    HW_SDMAARM_CONFIG.B.ACR = 0;//AP DMA/SDMA clock ratio: 2:1
    HW_SDMAARM_MC0PTR_WR((uint32_t)sdma_envp->sdma_ccb);  //Set CCB base address    

    sdma_envp->sdma_ccb[0].baseBDptr = (uint32_t)&sdma_envp->chan0BD;

#ifdef SDMA_SCRATCH_ENABLE
    HW_SDMAARM_CHN0ADDR_SET(SDMA_REG_CHN0ADDR_BIT_SMSZ);  //Enable scratch area
#endif

    for (idx = 0; idx < SDMA_NUM_REQUESTS; idx++) {
    HW_SDMAARM_CHNENBLn_WR(idx,0);
    }

    /* Set overrides for channel 0 */
    set_channel_override(0, FALSE, TRUE, TRUE);

    /* Download RAM script code to SDMA RAM region */
    if (FALSE ==
        sdma_load_init_script(SDMA_RAMSCRIPT_CODE_START, (uint32_t)script_info.ram_code,
                              script_info.ram_code_size << 1)) {
        return SDMA_RETV_FAIL;
    }

    sdma_initialized = TRUE;

    return SDMA_RETV_SUCCESS;
}

/*!
 * De-initialize the SDMA environment. In this function will:
 *    1. Close and free all the channels
 *    2. Clear all the EP and overrides of channels
 *
 * @return   none
 */
void sdma_deinit(void)
{
    int32_t idx;

    /* Stop and free all channels */
    for (idx = 0; idx < SDMA_NUM_CHANNELS; idx++) {
        sdma_channel_stop(idx);
        HW_SDMAARM_SDMA_CHNPRIn_WR(idx,SDMA_CHANNEL_PRIORITY_FREE);
    }

    /* Clear all EP */
    for (idx = 0; idx < SDMA_NUM_REQUESTS; idx++) {
    HW_SDMAARM_CHNENBLn_WR(idx,0);
    }

    /* Clear all overrides */
    HW_SDMAARM_HOSTOVR_WR(0);
    HW_SDMAARM_DSPOVR_WR(0);
    HW_SDMAARM_EVTOVR_WR(0);
    sdma_envp = NULL;
    sdma_initialized = FALSE;
}

/*!
 * Start the channel selected. The channel start condition is: (EO or EP) and DO and (HO or HE). 
 * In this function HE is set. There're 2 cases to consider:
 *    1. Channel started by DMA event(EP). In this case, EO should not be set and to start the 
 *       channel, need to enable the peripheral DMA then set the HE
 *    2. Channel started by the bit in HSTART(HE). In this case, there's no DMA event binding to
 *       the channel. Thus EO is set first, then set the HE
 *
 * @param channel the number of the channel to start
 * @return   0 on success, -1 when channel number is out of range(0-31) or channel is free
 */
int32_t sdma_channel_start(uint32_t channel)
{
    if (channel >= SDMA_NUM_CHANNELS) {
        return SDMA_RETV_FAIL;
    }

    if (HW_SDMAARM_SDMA_CHNPRIn_RD(channel) == SDMA_CHANNEL_PRIORITY_FREE) {
        return SDMA_RETV_FAIL;
    }

    if ((HW_SDMAARM_HSTART_RD() & (1 << channel)) == 0) {
        HW_SDMAARM_HSTART_SET(1 << channel);
    }

    return SDMA_RETV_SUCCESS;
}

/*!
 * Stop the channel selected. In this function just clear the HE.
 *
 * @param   channel the number of the channel to start
 * @return   0 on success, -1 when channel number out of range(0-31)
 */
int32_t sdma_channel_stop(uint32_t channel)
{
    if (channel >= SDMA_NUM_CHANNELS) {
        return SDMA_RETV_FAIL;
    }

    HW_SDMAARM_STOP_STAT_SET(1 << channel);

    return SDMA_RETV_SUCCESS;
}

/*!
 * Allocate a free channel and open it. In this function will:
 *    1. Validate the input parameters
 *    2. Find and allocate a free channel
 *    3. Setup the channel overrides, DMA masks, buffer descriptors, channel priority etc
 *    4. Write the channel context to SDMA RAM
 *
 * @param
 *    cdp: A pointer to user provided data. It includes necessary channel descriptors of:
 *        script_addr: script address in SDMA defined in sdma_script_code.h
 *        gpr[8]:      normally it includes the FIFO address, DMA mask, watermark etc. User 
 *                     could refer to the script manual released with the sdma_script_code.h
 *                     for details
 *        dma_mask[2]: DMA mask to set in register of channel enable. Normally it's also 
 *                     provided in gpr[8]. We separate it here is to support some special 
 *                     script that may have some different usage of GPRs
 *        priority:    the channel priority
 *
 * @param
 *    bdp: A pointer to the un-cacheable and un-bufferable buffer descriptor table allocated by user. User could refer to the 
 *    script manual on how to set the fields inside according to different scripts. To know 
 *    the details user may look into the "Application Notes" section of "SDMA controller"
 *    paragraph of the i.MX user guide.
 *
 * @return
 *    On success, return the channel number. Otherwise return failures as below:
 *    -2: at least one of user provided pointers is NULL
 *    -3: channel priority exceeds limitation(1-7)
 *    -4: no free channel that could allocate
 *    -5: got failure when download channel context to SDMA RAM
 *    -6: too many buffer descriptors in table(>64)
 *    -7: SDMA is not initialized yet
 */
int32_t sdma_channel_request(sdma_chan_desc_p cdp, sdma_bd_p bdp)
{
    int32_t channel, idx;

    if (sdma_initialized == FALSE) {
        return SDMA_RETV_NOT_INITED;
    }

    if ((cdp == NULL) || (bdp == NULL)) {
        return SDMA_RETV_NULLP;
    }

    if ((cdp->priority == SDMA_CHANNEL_PRIORITY_FREE)
        || (cdp->priority > SDMA_CHANNEL_PRIORITY_HIGH)) {
        return SDMA_RETV_PRIORITY;
    }

    uint32_t bd_num;
    if (FALSE == validate_buffer_descriptor(bdp, &bd_num)) {
        return SDMA_RETV_BD_VALIDATE;
    }

    /* Allocate a free channel */
    for (channel = 1; channel < SDMA_NUM_CHANNELS; channel++) {
        if (SDMA_CHANNEL_PRIORITY_FREE == HW_SDMAARM_SDMA_CHNPRIn_RD(channel)) {
        HW_SDMAARM_SDMA_CHNPRIn_WR(channel,cdp->priority);
            break;
        }
    }

    if (channel >= SDMA_NUM_CHANNELS) {
        return SDMA_RETV_NO_FREE_CHANNEL;
    }

    sdma_envp->sdma_ccb[channel].chanDesc = 0;
    sdma_envp->sdma_ccb[channel].status = 0;

    /* Set EP channel enable registers */
    if (cdp->dma_mask[0] == 0 && cdp->dma_mask[1] == 0) {
        set_channel_override(channel, FALSE, TRUE, TRUE);
    } else {
        for (idx = 0; idx < 32; idx++) {
            if ((cdp->dma_mask[0] & (1 << idx)) != 0) {
                HW_SDMAARM_CHNENBLn_SET(idx,1 << channel);
            }
        }

        for (idx = 0; idx < (SDMA_NUM_REQUESTS - 32); idx++) {
            if ((cdp->dma_mask[1] & (1 << idx)) != 0) {
            HW_SDMAARM_CHNENBLn_SET(idx+32,1 << channel);
		}
        }

        set_channel_override(channel, FALSE, TRUE, FALSE);
    }

    /* Setup channel context */
    sdma_envp->chan_cnxt.pc_rpc = cdp->script_addr;
    for (idx = 0; idx < 8; idx++) {
        sdma_envp->chan_cnxt.gr[idx] = cdp->gpr[idx];
    }

    /* Load channel context to SDMA context region */
    if (FALSE == sdma_write_channel_context(channel, (uint32_t)&sdma_envp->chan_cnxt)) {
        return SDMA_RETV_SET_CONTEXT;
    }

    sdma_envp->sdma_bd_num[channel] = bd_num;

    /* Setup BD pointer */
    sdma_envp->sdma_ccb[channel].baseBDptr = (uint32_t)bdp;
    sdma_envp->sdma_ccb[channel].currentBDptr = (uint32_t)bdp;

    sdma_envp->sdma_bdp[channel] = bdp;

    return channel;
}

/*!
 * Close the channel selected. In this function will:
 *    1. Stop and free the channel
 *    2. Clear the EP is set
 *    3. Reset the channel override
 *    4. Reset the channel control block
 *
 * @param    channel number
 * @return   0 on success, -1 when channel number not in range(0-31) or
 *           SDMA not initialized yet
 */
int32_t sdma_channel_release(uint32_t channel)
{
    int32_t idx;

    if (sdma_initialized == FALSE) {
        return SDMA_RETV_FAIL;
    }

    if (channel >= SDMA_NUM_CHANNELS) {
        return SDMA_RETV_FAIL;
    }

    if (HW_SDMAARM_SDMA_CHNPRIn_RD(channel) == SDMA_CHANNEL_PRIORITY_FREE) {
        return SDMA_RETV_SUCCESS;
    }

    /* Stop channel first */
    sdma_channel_stop(channel);

    /* Clear EP enable */
    for (idx = 0; idx < SDMA_NUM_REQUESTS; idx++) {
        if ((HW_SDMAARM_CHNENBLn_RD(idx) & (1 << channel)) != 0) {
            HW_SDMAARM_CHNENBLn_CLR(idx,(1 << channel));
            break;
        }
    }

    /* Reset channel override */
    set_channel_override(channel, FALSE, TRUE, FALSE);

    /* Clear CCB */
    sdma_envp->sdma_ccb[channel].baseBDptr = 0;
    sdma_envp->sdma_ccb[channel].currentBDptr = 0;
    sdma_envp->sdma_ccb[channel].chanDesc = 0;
    sdma_envp->sdma_ccb[channel].status = 0;
    sdma_envp->sdma_bdp[channel] = NULL;
    sdma_envp->sdma_bd_num[channel] = 0;

    /* Set priority to 0 */
    HW_SDMAARM_SDMA_CHNPRIn_WR(channel,SDMA_CHANNEL_PRIORITY_FREE);
    return SDMA_RETV_SUCCESS;
}

/*! 
 * Get the channel's status had been started. 
 *
 * @param   channel the channel which status to be check
 * @param   status a pointer hold the status of the channel: ERROR, BUSY and DONE
 *
 * @return   0 on success, -1 when failed 
 */
uint32_t sdma_channel_status(uint32_t channel, uint32_t *status)
{
    uint32_t i;
    uint32_t st = 0;

    if (channel >= SDMA_NUM_CHANNELS) {
        return SDMA_RETV_FAIL;
    }

    if (HW_SDMAARM_SDMA_CHNPRIn_RD(channel) == SDMA_CHANNEL_PRIORITY_FREE) {
        return SDMA_RETV_FAIL;
    }

    for (i = 0; i < sdma_envp->sdma_bd_num[channel]; i++) {
        st |= sdma_envp->sdma_bdp[channel][i].mode;
    }

    if (st & SDMA_FLAGS_ERROR) {
        *status = SDMA_CHANNEL_STATUS_ERROR;
    } else if (st & SDMA_FLAGS_BUSY) {
        *status = SDMA_CHANNEL_STATUS_BUSY;
    } else {
        *status = SDMA_CHANNEL_STATUS_DONE;
    }

    return SDMA_RETV_SUCCESS;
}

/*! 
 * Lookup the script's address mapped in the SDMA's memory. 
 *
 * @param    script the script to be lookup
 * @param    addr a pointer hold the script's address.
 *
 * @return   0 on success, -1 when failed 
 */
int32_t sdma_lookup_script(script_name_e script, uint32_t *addr)
{
    if (script >= SDMA_NUM_SCRIPTS) {
        return SDMA_RETV_FAIL;
    }

    uint32_t i;
    for (i = 0; i < SDMA_NUM_SCRIPTS; i++) {
        if (script_info.script_maps[i].script_index == script)
            break;
    }

    if (script_info.script_maps[i].script_addr != 0) {
        *addr = script_info.script_maps[i].script_addr;
        return SDMA_RETV_SUCCESS;
    }

    return SDMA_RETV_FAIL;
}

/*! 
 * Setup sdma interrupt. This function attach sdma_interrupt_handler to system and 
 * set the isr for every single channel to default one. 
 *
 * @return   none
 */
void sdma_setup_interrupt(void)
{
    register_interrupt_routine(IMX_INT_SDMA, sdma_interrupt_handler);

    uint32_t i;
    for (i = 0; i < SDMA_NUM_CHANNELS; i++) {
        sdma_channel_isr_list[i] = sdma_channel_default_isr;
    }

    enable_interrupt(IMX_INT_SDMA, CPU_0, 0);
}

/*! 
 * This function attach isr for the channel to SDMA lib. The isr will be called  
 * in sdma_interrupt_handler.
 * @param    channel channel number to be attached.	
 * @param    isr the interrupt service routine for the channel
 * @return   0 on success,
 *           -1 if invalid channel number
 *           -2 if isr is NULL
 */
int32_t sdma_channel_isr_attach(uint32_t channel, sdma_channel_isr isr)
{
    if (channel >= SDMA_NUM_CHANNELS) {
        return SDMA_RETV_FAIL;
    }

    if (NULL == isr) {
        return SDMA_RETV_NULLP;
    }

    sdma_channel_isr_list[channel] = isr;

    return SDMA_RETV_SUCCESS;
}
