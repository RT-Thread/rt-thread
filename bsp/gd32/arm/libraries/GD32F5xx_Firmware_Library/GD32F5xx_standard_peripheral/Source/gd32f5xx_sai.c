/*!
    \file    gd32f5xx_sai.c
    \brief   SAI driver

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f5xx_sai.h"

/*!< bit offset of MTFCNT in SAI_CFG1 */
#define CFG1_MTFCNT_OFFSET                   ((uint32_t)0x00000007U)

/*!
    \brief      reset SAI
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sai_deinit(void)
{
    /* reset SAI */
    rcu_periph_reset_enable(RCU_SAIRST);
    rcu_periph_reset_disable(RCU_SAIRST);
}

/*!
    \brief      initialize the parameter of SAI structure with a default value
    \param[in]  none
    \param[out] sai_init_stuct: the initialization data needed to initialize SAI
    \retval     none
*/
void sai_struct_para_init(sai_parameter_struct *sai_init_stuct)
{
    /* initialize the initpara struct member with the default value */
    sai_init_stuct->operating_mode         = SAI_MASTER_TRANSMITTER;
    sai_init_stuct->protocol               = SAI_PROTOCOL_POLYMORPHIC;
    sai_init_stuct->data_width             = SAI_DATAWIDTH_32BIT;
    sai_init_stuct->shift_dir              = SAI_SHIFT_MSB;
    sai_init_stuct->sample_edge            = SAI_SAMPEDGE_FALLING;
    sai_init_stuct->sync_mode              = SAI_SYNCMODE_ASYNC;
    sai_init_stuct->output_drive           = SAI_OUTPUT_WITH_SAIEN;
    sai_init_stuct->clk_div_bypass         = SAI_CLKDIV_BYPASS_OFF;
    sai_init_stuct->mclk_div               = SAI_MCLKDIV_1;
    sai_init_stuct->mclk_oversampling      = SAI_MCLK_OVERSAMP_256;
    sai_init_stuct->mclk_enable            = SAI_MCLK_DISABLE;
    sai_init_stuct->fifo_threshold         = SAI_FIFOTH_EMPTY;
}

/*!
    \brief      initialize the parameter of SAI frame structure with a default value
    \param[in]  none
    \param[out] sai_frame_init_struct: the initialization data needed to initialize SAI frame
    \retval     none
*/
void sai_frame_struct_para_init(sai_frame_parameter_struct *sai_frame_init_struct)
{
    /* initialize the initpara struct member with the default value */
    sai_frame_init_struct->frame_width                = 256U;
    sai_frame_init_struct->frame_sync_width           = 128U;
    sai_frame_init_struct->frame_sync_function        = SAI_FS_FUNC_START;
    sai_frame_init_struct->frame_sync_polarity        = SAI_FS_POLARITY_LOW;
    sai_frame_init_struct->frame_sync_offset          = SAI_FS_OFFSET_BEGINNING;
}

/*!
    \brief      initialize the parameter of SAI slot structure with a default value
    \param[in]  none
    \param[out] sai_slot_init_struct: the initialization data needed to initialize SAI slot
    \retval     none
*/
void sai_slot_struct_para_init(sai_slot_parameter_struct *sai_slot_init_struct)
{
    /* initialize the initpara struct member with the default value */
    sai_slot_init_struct->slot_number            = 16U;
    sai_slot_init_struct->slot_width             = SAI_SLOT_WIDTH_DATA;
    sai_slot_init_struct->data_offset            = 0U;
    sai_slot_init_struct->slot_active            = SAI_SLOT_ACTIVE_NONE;
}

/*!
    \brief      initialize SAI
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x = 0,1)
    \param[in]  sai_struct: SAI parameter initialization stuct members of the structure
                            and the member values are shown as below:
                  operating_mode: SAI_MASTER_TRANSMITTER, SAI_MASTER_RECEIVER, SAI_SLAVE_TRANSMITTER, SAI_SLAVE_RECEIVER;
                  protocol: SAI_PROTOCOL_POLYMORPHIC, SAI_PROTOCOL_SPDIF, SAI_PROTOCOL_AC97
                  data_width: SAI_DATA_WIDTH_xBIT (x = 8, 10, 16, 20, 24, 32)
                  shift_dir: SAI_SHIFT_MSB, SAI_SHIFT_LSB
                  sample_edge: SAI_SAMPEDGE_FALLING, SAI_SAMPEDGE_RISING
                  sync_mode: SAI_SYNCMODE_ASYNC, SAI_SYNCMODE_OTHERBLOCK, SAI_SYNCMODE_EXTERNALSAI
                  output_drive: SAI_OUTPUT_WITH_SAIEN, SAI_OUTPUT_NOW
                  clk_div_bypass: SAI_CLKDIV_BYPASS_OFF, SAI_CLKDIV_BYPASS_ON
                  mck_div: SAI_MCLKDIV_x (x = 1,2,..,63)
                  mck_oversampling: SAI_MASTERCLK_OVERSAMP_256, SAI_MASTERCLK_OVERSAMP_512
                  mck_enable: SAI_MASTERCLK_DISABLE, SAI_MASTERCLK_ENABLE
                  fifo_threshold: SAI_FIFOTH_EMPTY, SAI_FIFOTH_QUARTER, SAI_FIFOTH_HALF, SAI_FIFOTH_THREE_QUARTER, SAI_FIFOTH_FULL
    \param[out] none
    \retval     none
*/
void sai_init(uint32_t block, sai_parameter_struct *sai_struct)
{
    uint32_t reg = 0U;

    /* configure the SAI CFGR0 value */
    reg = SAI_CFG0(block);
    reg &= ~(SAI_CFG0_OPTMOD | SAI_CFG0_PROT | \
             SAI_CFG0_DATAWD | SAI_CFG0_SHIFTDIR | \
             SAI_CFG0_SAMPEDGE | SAI_CFG0_SYNCMOD | \
             SAI_CFG0_ODRIV | SAI_CFG0_BYPASS | \
             SAI_CFG0_MDIV | SAI_CFG0_MOSPR | \
             SAI_CFG0_MCLKEN | SAI_CFG0_SAIEN);

    reg |= (uint32_t)(sai_struct->operating_mode | sai_struct->protocol | \
                      sai_struct->data_width | sai_struct->shift_dir | \
                      sai_struct->sample_edge | sai_struct->sync_mode | \
                      sai_struct->output_drive | sai_struct->clk_div_bypass | \
                      sai_struct->mclk_div | sai_struct->mclk_oversampling | \
                      sai_struct->mclk_enable);
    SAI_CFG0(block) = reg;

    /* configure the SAI CFGR1 FIFO threshold */
    reg = SAI_CFG1(block);
    reg &= ~SAI_CFG1_FFTH;
    reg |= (uint32_t)(sai_struct->fifo_threshold);
    SAI_CFG1(block) = reg;
}

/*!
    \brief      initialize SAI frame
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[in]  sai_frame_struct: SAI frame parameter initialization stuct members of the structure
                                  and the member values are shown as below:
                  frame_width: 1~256, frame width
                  frame_sync_width: 1~128, frame synchronization active width
                  frame_sync_function: SAI_FS_FUNC_START, SAI_FS_FUNC_START_CHANNEL
                  frame_sync_polarity: SAI_FS_POLARITY_LOW, SAI_FS_POLARITY_HIGH
                  frame_sync_offset: SAI_FS_OFFSET_BEGINNING, SAI_FS_OFFSET_ONEBITBEFORE
    \param[out] none
    \retval     none
*/
void sai_frame_init(uint32_t block, sai_frame_parameter_struct *sai_frame_struct)
{
    uint32_t reg = 0U;
    reg = SAI_FCFG(block);
    reg &= ~(SAI_FCFG_FWD | SAI_FCFG_FSAWD | SAI_FCFG_FSFUNC | \
             SAI_FCFG_FSPL | SAI_FCFG_FSOST);
    reg |= (uint32_t)(sai_frame_struct->frame_sync_offset | \
                      sai_frame_struct->frame_sync_polarity | \
                      sai_frame_struct->frame_sync_function | \
                      ((sai_frame_struct->frame_sync_width - 1U) << 8U) | \
                      (sai_frame_struct->frame_width - 1U));
    /* configure the SAI frame */
    SAI_FCFG(block) = reg;
}

/*!
    \brief      initialize SAI slot
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[in]  sai_slot_struct: SAI slot parameter initialization stuct members of the structure
                                 and the member values are shown as below:
                  slot_number: 1~16, slot number
                  slot_width: SAI_SLOTWIDTH_DATA, SAI_SLOTWIDTH_16BIT, SAI_SLOTWIDTH_32BIT
                  data_offset: 0~31, data offset
                  slot_active: one or more parameters can be selected, SAI_SLOT_ACTIVE_NONE, SAI_SLOT_ACTIVE_x(x=0..15), SAI_SLOT_ACTIVE_ALL
    \param[out] none
    \retval     none
*/
void sai_slot_init(uint32_t block, sai_slot_parameter_struct *sai_slot_struct)
{
    uint32_t reg = 0U;
    reg = SAI_SCFG(block);
    reg &= ~(SAI_SCFG_DATAOST | SAI_SCFG_SLOTWD | SAI_SCFG_SLOTNUM | SAI_SCFG_SLOTAV);
    reg = (uint32_t)(((sai_slot_struct->slot_number - 1U) << 8U) | \
                     sai_slot_struct->slot_width | \
                     sai_slot_struct->data_offset | \
                     sai_slot_struct->slot_active);
    /* configure the SAI slot */
    SAI_SCFG(block) = reg;
}

/*!
    \brief      SAI enable

    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[out] none
    \retval     none
*/
void sai_enable(uint32_t block)
{
    SAI_CFG0(block) |= SAI_CFG0_SAIEN;
}

/*!
    \brief      SAI disable
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[out] none
    \retval     none
*/
void sai_disable(uint32_t block)
{
    SAI_CFG0(block) &= ~SAI_CFG0_SAIEN;
}

/*!
    \brief      SAI serial data near inactive slot output management
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[in]  sdout: serial data output management
                only one parameter can be selected which is shown as below:
      \arg        SAI_SDLINE_DRIVE: SD line output is driven entirely during the audio frame
      \arg        SAI_SDLINE_RELEASE: SD line output is released near inactive slots
    \param[out] none
    \retval     none
*/
void sai_sdoutput_config(uint32_t block, uint32_t sdout)
{
    SAI_CFG1(block) &= ~SAI_CFG1_SDOM;
    SAI_CFG1(block) |= sdout;
}

/*!
    \brief      configure SAI mono mode

    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[in]  mono: stereo and mono mode selection
                only one parameter can be selected which is shown as below:
      \arg        SAI_STEREO_MODE: stereo mode
      \arg        SAI_MONO_MODE: mono mode
    \param[out] none
    \retval     none
*/
void sai_monomode_config(uint32_t block, uint32_t mono)
{
    SAI_CFG0(block) &= ~SAI_CFG0_MONO;
    SAI_CFG0(block) |= mono;
}

/*!
    \brief      configure SAI companding mode
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[in]  compander: compander mode
                only one parameter can be selected which is shown as below:
      \arg        SAI_COMPANDER_OFF: no compansion applies
      \arg        SAI_COMPANDER_ULAW: u-law algorithm
      \arg        SAI_COMPANDER_ALAW: A-law algorithm
    \param[in]  complement:complement mode
                only one parameter can be selected which is shown as below:
      \arg        SAI_COMPLEMENT_1S: data represented in 1's complement form
      \arg        SAI_COMPLEMENT_2S: data represented in 2's complement form
    \param[out] none
    \retval     none
*/
void sai_companding_config(uint32_t block, uint32_t compander, uint32_t complement)
{
    uint32_t reg = 0U;
    reg = SAI_CFG1(block);
    reg &= ~(SAI_CFG1_CPLMOD | SAI_CFG1_CPAMOD);
    reg |= (compander | complement);
    SAI_CFG1(block) = reg;
}

/*!
    \brief      SAI mute detected enable or mute send enable
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[out] none
    \retval     none
*/
void sai_mute_enable(uint32_t block)
{
    SAI_CFG1(block) |= SAI_CFG1_MT;
}

/*!
    \brief      SAI mute detected disable or mute send disable

    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[out] none
    \retval     none
*/
void sai_mute_disable(uint32_t block)
{
    SAI_CFG1(block) &= ~SAI_CFG1_MT;
}

/*!
    \brief      configure SAI mute value
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[in]  value: mute value
                only one parameter can be selected which are shown as below:
      \arg        SAI_MUTESENT_0: 0 is sent via the serial data line when mute is on
      \arg        SAI_MUTESENT_LASTFREAM: If SLOTNUM is less or equals to two, last frame is sent via the serial data line
    \param[out] none
    \retval     none
*/
void sai_mute_value_config(uint32_t block, uint32_t value)
{
    SAI_CFG1(block) &= ~SAI_CFG1_MTVAL;
    SAI_CFG1(block) |= value;
}

/*!
    \brief      configure SAI mute frame count
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[in]  count: 0~63, mute frame count
    \param[out] none
    \retval     none
*/
void sai_mute_count_config(uint32_t block, uint32_t count)
{
    uint32_t reg = 0U;
    reg = SAI_CFG1(block);
    reg &= ~SAI_CFG1_MTFCNT;
    reg |= count << CFG1_MTFCNT_OFFSET;
    SAI_CFG1(block) = reg;
}

/*!
    \brief      SAI transmit data
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[in]  data: 32-bit data
    \param[out] none
    \retval     none
*/
void sai_data_transmit(uint32_t block, uint32_t data)
{
    SAI_DATA(block) = data;
}

/*!
    \brief      SAI receive data

    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[out] none
    \retval     received data
*/
uint32_t sai_data_receive(uint32_t block)
{
    return SAI_DATA(block);
}

/*!
    \brief      get SAI fifo status
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[out] none
    \retval     state of fifo
      \arg        FIFO_EMPTY: empty
      \arg        FIFO_EMPTY_TO_1_4_FULL: empty < fifo_level <= 1/4_full
      \arg        FIFO_1_4_FULL_TO_1_2_FULL: 1/4_full < fifo_level <= 1/2_full
      \arg        FIFO_1_2_FULL_TO_3_4_FULL: 1/2_full < fifo_level <= 3/4_full
      \arg        FIFO_3_4_FULL_TO_FULL: 3/4_full < fifo_level < full
      \arg        FIFO_FULL: full
*/
sai_fifo_state_enum sai_fifo_status_get(uint32_t block)
{
    sai_fifo_state_enum sai_fifo_state = FIFO_EMPTY;

    if(SAI_FIFO_STAT_EMPTY == (SAI_STAT(block) & SAI_STAT_FFSTAT)) {
        sai_fifo_state = FIFO_EMPTY;
    } else if(SAI_FIFO_STAT_QUARTER == (SAI_STAT(block) & SAI_STAT_FFSTAT)) {
        sai_fifo_state = FIFO_EMPTY_TO_1_4_FULL;
    } else if(SAI_FIFO_STAT_HALF == (SAI_STAT(block) & SAI_STAT_FFSTAT)) {
        sai_fifo_state = FIFO_1_4_FULL_TO_1_2_FULL;
    } else if(SAI_FIFO_STAT_THREE_QUARTER == (SAI_STAT(block) & SAI_STAT_FFSTAT)) {
        sai_fifo_state = FIFO_1_2_FULL_TO_3_4_FULL;
    } else if(SAI_FIFO_STAT_NEARFULL == (SAI_STAT(block) & SAI_STAT_FFSTAT)) {
        sai_fifo_state = FIFO_3_4_FULL_TO_FULL;
    } else {
        sai_fifo_state = FIFO_FULL;
    }

    return sai_fifo_state;
}

/*!
    \brief      SAI fifo flush
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[out] none
    \retval     none
*/
void sai_fifo_flush(uint32_t block)
{
    SAI_CFG1(block) = SAI_CFG1_FLUSH;
}

/*!
    \brief      enable SAI dma

    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[out] none
    \retval     none
*/
void sai_dma_enable(uint32_t block)
{
    SAI_CFG0(block) |= SAI_CFG0_DMAEN;
}

/*!
    \brief      disable SAI dma

    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx (x=0,1)
    \param[out] none
    \retval     none
*/
void sai_dma_disable(uint32_t block)
{
    SAI_CFG0(block) &= ~SAI_CFG0_DMAEN;
}

/*!
    \brief      enable the SAI interrupt
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[in]  interrupt: specify which interrupt to enable
                one or more parameters can be selected which are shown as below:
      \arg        SAI_INT_OUERR: FIFO overrun or underrun interrupt enable
      \arg        SAI_INT_MTDET: mute detection interrupt enable
      \arg        SAI_INT_ERRCK: error clock interrupt enable
      \arg        SAI_INT_FFREQ: FIFO request interrupt enable
      \arg        SAI_INT_ACNRDY: audio codec not ready interrupt enable
      \arg        SAI_INT_FSADET: frame synchronization advanced detection interrupt enable
      \arg        SAI_INT_FSPDET: frame synchronization postpone detection interrupt enable
    \param[out] none
    \retval     none
*/
void sai_interrupt_enable(uint32_t block, uint32_t interrupt)
{
    SAI_INTEN(block) |= interrupt;
}

/*!
    \brief      disable the SAI interrupt
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[in]  interrupt: specify which interrupt to disable
                one or more parameters can be selected which are shown as below:
      \arg        SAI_INT_OUERR: FIFO overrun or underrun interrupt
      \arg        SAI_INT_MTDET: mute detection interrupt
      \arg        SAI_INT_ERRCK: error clock interrupt
      \arg        SAI_INT_FFREQ: FIFO request interrupt
      \arg        SAI_INT_ACNRDY: audio codec not ready interrupt
      \arg        SAI_INT_FSADET: frame synchronization advanced detection interrupt
      \arg        SAI_INT_FSPDET: frame synchronization postpone detection interrupt
    \param[out] none
    \retval     none
*/
void sai_interrupt_disable(uint32_t block, uint32_t interrupt)
{
    SAI_INTEN(block) &= ~interrupt;
}

/*!
    \brief      get the SAI interrupt flag
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[in]  interrupt: specify which interrupt flag to get
                only one parameter can be selected which are shown as below:
      \arg        SAI_FLAG_OUERR: FIFO overrun or underrun interrupt flag
      \arg        SAI_FLAG_MTDET: mute detection interrupt flag
      \arg        SAI_FLAG_ERRCK: error clock interrupt flag
      \arg        SAI_FLAG_FFREQ: FIFO request interrupt flag
      \arg        SAI_FLAG_ACNRDY: audio codec not ready interrupt flag
      \arg        SAI_FLAG_FSADET: frame synchronization advanced detection interrupt flag
      \arg        SAI_FLAG_FSPDET: frame synchronization postpone detection interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus sai_interrupt_flag_get(uint32_t block, uint32_t interrupt)
{
    uint32_t inten = 0U;
    inten = SAI_INTEN(block) & interrupt;
    if((RESET != (SAI_STAT(block) & interrupt)) && (RESET != inten)) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear the SAI interrupt flag
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[in]  interrupt: specify which interrupt flag to clear
                one or more parameters can be selected which are shown as below:
      \arg        SAI_FLAG_OUERR: FIFO overrun or underrun interrupt flag
      \arg        SAI_FLAG_MTDET: mute detection interrupt flag
      \arg        SAI_FLAG_ERRCK: error clock interrupt flag
      \arg        SAI_FLAG_ACNRDY: audio codec not ready interrupt flag
      \arg        SAI_FLAG_FSADET: frame synchronization advanced detection interrupt flag
      \arg        SAI_FLAG_FSPDET: frame synchronization postpone detection interrupt flag
    \param[out] none
    \retval     none
*/
void sai_interrupt_flag_clear(uint32_t block, uint32_t interrupt)
{
    SAI_INTC(block) = interrupt;
}

/*!
    \brief      get the SAI flag
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[in]  flag: specify which flag to get
                only one parameter can be selected which are shown as below:
      \arg        SAI_FLAG_OUERR: FIFO overrun or underrun flag
      \arg        SAI_FLAG_MTDET: mute detection flag
      \arg        SAI_FLAG_ERRCK: error clock flag
      \arg        SAI_FLAG_FFREQ: FIFO request flag
      \arg        SAI_FLAG_ACNRDY: audio codec not ready flag
      \arg        SAI_FLAG_FSADET: frame synchronization advanced detection flag
      \arg        SAI_FLAG_FSPDET: frame synchronization postpone detection flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus sai_flag_get(uint32_t block, uint32_t flag)
{
    if(RESET != (SAI_STAT(block) & flag)) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear the SAI flag
    \param[in]  block: specify which bolck is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCKx(x=0,1)
    \param[in]  flag: specify which flag to clear
                one or more parameters can be selected which are shown as below:
      \arg        SAI_FLAG_OUERR: FIFO overrun or underrun flag
      \arg        SAI_FLAG_MTDET: mute detection flag
      \arg        SAI_FLAG_ERRCK: error clock flag
      \arg        SAI_FLAG_ACNRDY: audio codec not ready flag
      \arg        SAI_FLAG_FSADET: frame synchronization advanced detection flag
      \arg        SAI_FLAG_FSPDET: frame synchronization postpone detection flag
    \param[out] none
    \retval     none
*/
void sai_flag_clear(uint32_t block, uint32_t flag)
{
    SAI_INTC(block) = flag;
}
