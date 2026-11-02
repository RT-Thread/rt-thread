/**
 ****************************************************************************************
 *
 * @file bsp_src.c
 *
 * @brief Implementation of the Audio Unit SRC Low Level Driver.
 *
 * Copyright (c) 2016-2020 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */
#include "bsp_src.h"

#define SRC_CLK    32000               /* SRC_CLK must be 32000 Hz according to design limitation */

/**
 * \brief Clear the SRC over/underflow indications
 *
 * \param [in] id    identifies SRC1, SRC2
 * \param[in]  io    Input/Output selection (IN or OUT)
 */
#define HW_SRC_CLEAR_FLOW_ERROR(id, io)                        \
    while (SRC_IF->APU_SRC_CTRL_REG_b.SRC_ ## io ## _OVFLOW || \
           SRC_IF->APU_SRC_CTRL_REG_b.SRC_ ## io ## _UNFLOW) { \
        SRC_IF->APU_SRC_CTRL_REG_b.SRC_ ## io ## _FLOWCLR = 1; \
    }                                                          \
    SRC_IF->APU_SRC_CTRL_REG_b.SRC_ ## io ## _FLOWCLR = 0;

static uint32_t R_BSP_src_calc_sampling_frequency (uint32_t sample_rate, uint8_t divider, uint8_t * iir_setting)
{
    FSP_ASSERT(divider > 0);
    FSP_ASSERT(iir_setting != NULL);

    if (sample_rate > 170000)
    {
        *iir_setting = 3;
    }
    else if (sample_rate > 85000)
    {
        *iir_setting = 1;
    }
    else
    {
        *iir_setting = 0;
    }

    sample_rate /= (*iir_setting) + 1;
    uint64_t sampling_frequency = 4096 * (uint64_t) sample_rate * (uint64_t) divider;

    return (sampling_frequency / 100) & 0xFFFFFF;
}

void R_BSP_src_init (HW_SRC_ID id, bsp_src_config_t * config)
{
    uint8_t divider = 1;
    uint8_t iir_setting;

    config->id = id;

    CRG_APU->APU_SRC_CLK_REG_b.SRC_CLK_DIV  = 1;
    CRG_APU->APU_AUD_CLK_REG_b.AUD_PCLK_DIV = 1;

    CRG_APU->APU_SRC_CLK_REG_b.SRC_CLK_EN  = 0;
    CRG_APU->APU_SRC_CLK_REG_b.SRC_CLK_DIV = (uint8_t) (divider & 0x0F);
    CRG_APU->APU_SRC_CLK_REG_b.SRC_CLK_EN  = 1;

    if (config->in_sample_rate > 0)
    {
        uint32_t sampling_frequency = R_BSP_src_calc_sampling_frequency(config->in_sample_rate, divider, &iir_setting);
        SRC_IF->APU_SRC_IN_FS_REG_b.SRC_IN_FS = (uint32_t) (sampling_frequency & 0xFFFFFF);
        SRC_IF->APU_SRC_CTRL_REG_b.SRC_IN_DS  = (uint8_t) (iir_setting & 0x03);
    }

    if (config->out_sample_rate > 0)
    {
        uint32_t sampling_frequency = R_BSP_src_calc_sampling_frequency(config->out_sample_rate, divider, &iir_setting);
        SRC_IF->APU_SRC_OUT_FS_REG_b.SRC_OUT_FS = (uint32_t) (sampling_frequency & 0xFFFFFF);
        SRC_IF->APU_SRC_CTRL_REG_b.SRC_OUT_US   = (uint8_t) (iir_setting & 0x03);
    }

    /////////////////////////////////////////////
    ///////// CRG_APU
    /////////////////////////////////////////////

    CRG_APU->APU_AUD_CLK_REG_b.AUD_CLK_DIV = 1;
    CRG_APU->APU_AUD_CLK_REG_b.AUD_CLK_EN  = 1;

    APU_AUD->APU_MAIN_DIV_REG_b.APU_MAIN_DIV_EN = 1;
    APU_AUD->APU_MAIN_DIV_REG_b.APU_MAIN_DIV    = 1;

    CRG_APU->APU_SRC_CLK_REG_b.SRC_CLK_EN = 1;

    SRC_IF->APU_SRC_CTRL_REG_b.SRC_RESYNC = 1;

    // Clear input data registers
    R_BSP_src_write_input(config->id, 1, 0);
    R_BSP_src_write_input(config->id, 2, 0);

    HW_SRC_CLEAR_FLOW_ERROR(config->id, IN);
    HW_SRC_CLEAR_FLOW_ERROR(config->id, OUT);
}

BSP_SRC_FLOW_STATUS R_BSP_src_get_flow_status (HW_SRC_ID id, BSP_SRC_DIRECTION direction)
{
    BSP_SRC_FLOW_STATUS status = HW_SRC_FLOW_OK;
    FSP_PARAMETER_NOT_USED(id);

    switch (direction)
    {
        case HW_SRC_IN:
        {
            if (SRC_IF->APU_SRC_CTRL_REG_b.SRC_IN_OVFLOW)
            {
                status |= HW_SRC_FLOW_OVER;
            }

            if (SRC_IF->APU_SRC_CTRL_REG_b.SRC_IN_UNFLOW)
            {
                status |= HW_SRC_FLOW_UNDER;
            }

            HW_SRC_CLEAR_FLOW_ERROR(id, IN);
            break;
        }

        case HW_SRC_OUT:
        {
            if (SRC_IF->APU_SRC_CTRL_REG_b.SRC_OUT_OVFLOW)
            {
                status |= HW_SRC_FLOW_OVER;
            }

            if (SRC_IF->APU_SRC_CTRL_REG_b.SRC_OUT_UNFLOW)
            {
                status |= HW_SRC_FLOW_UNDER;
            }

            HW_SRC_CLEAR_FLOW_ERROR(id, OUT);
            break;
        }

        default:
        {
            break;
        }
    }

    return status;
}
