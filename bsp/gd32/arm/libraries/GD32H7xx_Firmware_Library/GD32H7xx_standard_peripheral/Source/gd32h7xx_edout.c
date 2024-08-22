/*!
    \file    gd32h7xx_edout.c
    \brief   EDOUT driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
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

#include "gd32h7xx_edout.h"

/* EDOUT register bit offset */
#define LOC_LOCMAX_MIN             ((uint32_t)0x0000000FU)    /*!< LOCMAX fields minimum value */
#define LOC_LOCMAX_STEP            ((uint32_t)0x00000004U)    /*!< LOCMAX fields step value */
#define OCNT_PDC_OFFSET            ((uint32_t)0x00000010U)    /*!< bit offset of PDC in EDOUT_OCNT */
#define ZCR_ZOWH_OFFSET            ((uint32_t)0x00000010U)    /*!< bit offset of ZOWH in EDOUT_ZCR */

/*!
    \brief      deinitialize EDOUT
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edout_deinit(void)
{
    /* reset EDOUT */
    rcu_periph_reset_enable(RCU_EDOUTRST);
    rcu_periph_reset_disable(RCU_EDOUTRST);
}

/*!
    \brief      initialize EDOUT
    \param[in]  pol: the active polarity of the B-phase output signal selection
                only one parameter can be selected which is shown as below:
      \arg        EDOUT_POL_POSITIVE: active polarity is positive
      \arg        EDOUT_POL_NEGATIVE: active polarity is negative
    \param[in]  max_loc: (max_loc+1) must be a multiple of four between 16~65536 (e.g. 0x000F: The maximum location value is 16 (16=4*4))
    \param[in]  cur_loc: current location value, 0~locmax (locmax is the LOCMAX bit fields value of EDOUT_LOC register)
    \param[out] none
    \retval     none
*/
void edout_init(uint32_t pol, uint32_t max_loc, uint32_t cur_loc)
{
    /* reset polarity of the B-phase */
    EDOUT_CTL &= ~EDOUT_CTL_POL;
    /* set polarity of the B-phase */
    EDOUT_CTL = pol;

    /* reset the maximum location value */
    EDOUT_LOC &= ~EDOUT_LOC_LOCMAX;
    /* check the maximum location value */
    if(LOC_LOCMAX_MIN > max_loc)
    {
        max_loc = LOC_LOCMAX_MIN;
    }
    while(0U != ((max_loc + 1U) % LOC_LOCMAX_STEP))
    {
        max_loc++;
    }
    /* set the maximum location value */
    EDOUT_LOC = max_loc & EDOUT_LOC_LOCMAX;

    /* reset the current location value */
    EDOUT_LCNT &= ~EDOUT_LCNT_LOCCNT;
    /* set the current location value */
    EDOUT_LCNT = cur_loc & EDOUT_LCNT_LOCCNT;
}

/*!
    \brief      enable EDOUT
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edout_enable(void)
{
    EDOUT_ENABLE |= EDOUT_ENABLE_EDOUTEN;
}

/*!
    \brief      disable EDOUT
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edout_disable(void)
{
    EDOUT_ENABLE &= ~EDOUT_ENABLE_EDOUTEN;
}

/*!
    \brief      set B-phase active polarity
    \param[in]  pol: the active polarity of the B-phase output signal selection
                only one parameter can be selected which is shown as below:
      \arg        EDOUT_POL_POSITIVE: active polarity is positive
      \arg        EDOUT_POL_NEGATIVE: active polarity is negative
    \param[out] none
    \retval     none
*/
void edout_polarity_config(uint32_t pol)
{
    EDOUT_CTL = pol;
}

/*!
    \brief      set the maximum location value for one rotation
    \param[in]  max_loc: (max_loc+1) must be a multiple of four between 16~65536, e.g. 0x000F: The maximum location value is 16
    \param[out] none
    \retval     none
*/
void edout_max_location_value_config(uint32_t max_loc)
{
    EDOUT_LOC = max_loc & EDOUT_LOC_LOCMAX;
}

/*!
    \brief      update the output counter, used to set the phase difference and the number of edges for the next update period
    \param[in]  num_edges: edge count, value range is -32768~32767, positive means clockwise rotation, negative means counter-clockwise rotation
    \param[in]  phase_diff: phase difference, value range is 2~65535, in units of PCLK
    \param[out] none
    \retval     none
*/
void edout_output_counter_update(int16_t num_edges, uint16_t phase_diff)
{
    EDOUT_OCNT = ((uint32_t)num_edges & EDOUT_OCNT_EDGC) | ((uint32_t)phase_diff << OCNT_PDC_OFFSET);
}

/*!
    \brief      set the current location value
    \param[in]  cur_loc: current location value, 0~locmax (locmax is the LOCMAX bit fields value of EDOUT_LOC register)
    \param[out] none
    \retval     none
*/
void edout_current_location_config(uint32_t cur_loc)
{
    EDOUT_LCNT = cur_loc & EDOUT_LCNT_LOCCNT;
}

/*!
    \brief      get the current location value
    \param[in]  none
    \param[out] none
    \retval     current location value, 0~locmax (locmax is the LOCMAX bit fields value of EDOUT_LOC register)
*/
uint16_t edout_current_location_get(void)
{
    return (uint16_t)EDOUT_LCNT;
}

/*!
    \brief      configure Z-phase output mode
    \param[in]  mode: Z-phase output mode
                only one parameter can be selected which is shown as below:
      \arg        EDOUT_Z_OUTPUT_MODE0: output according to the current location
      \arg        EDOUT_Z_OUTPUT_MODE1: output according to the number of edges
    \param[out] none
    \retval     none
*/
void edout_z_output_mode_config(uint32_t mode)
{
    /* reset the Z-phase output mode */
    EDOUT_ZCR &= ~EDOUT_ZCR_ZOMD;
    /* set the Z-phase output mode */
    EDOUT_ZCR |= mode;
}

/*!
    \brief      configure Z-phase output start location and width
    \param[in]  start_loc: Z-phase output start location,
                  when Z-phase output mode select EDOUT_Z_OUTPUT_MODE0: 0~locmax (locmax is the LOCMAX bit fields value of EDOUT_LOC register)
                  when Z-phase output mode select EDOUT_Z_OUTPUT_MODE1: 0~edges (edges is the EDGC bit fields value of EDOUT_OCNT register)
    \param[in]  width: Z-phase output width
                  when Z-phase output mode select EDOUT_Z_OUTPUT_MODE0: 0~(locmax - start_loc) (locmax is the LOCMAX bit fields value of EDOUT_LOC register)
                  when Z-phase output mode select EDOUT_Z_OUTPUT_MODE1: 0~(edges - start_loc) (edges is the EDGC bit fields value of EDOUT_OCNT register)
    \param[out] none
    \retval     none
*/
void edout_z_output_start_loc_and_width_config(uint32_t start_loc, uint32_t width)
{
    /* reset the Z-phase output start location and output width */
    EDOUT_ZCR &= ~(EDOUT_ZCR_ZOSP | EDOUT_ZCR_ZOWH);
    /* set the Z-phase output start location and output width */
    EDOUT_ZCR |= (start_loc & EDOUT_ZCR_ZOSP) | ((width << ZCR_ZOWH_OFFSET) & EDOUT_ZCR_ZOWH);
}
