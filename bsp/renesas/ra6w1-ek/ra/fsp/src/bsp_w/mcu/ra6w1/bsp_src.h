/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**
 ****************************************************************************************
 *
 * @file bsp_src.h
 *
 * @brief Definition of the API for the Audio Unit SRC Low Level Driver.
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

#ifndef BSP_SRC_RA6W1_H
#define BSP_SRC_RA6W1_H

#include <stdbool.h>
#include <stdint.h>
#include "bsp_api.h"

typedef void * HW_SRC_ID;

#define HW_SRC1                       ((void *) SRC_IF_BASE)

#define SRC_FIFO_ENABLE               (0x1 << 0)
#define SRC_FIFO_ENABLE_CH1_INPUT     (0x1 << 10)
#define SRC_FIFO_ENABLE_CH2_INPUT     (0x1 << 11)
#define SRC_FIFO_ENABLE_CH1_OUTPUT    (0x1 << 26)
#define SRC_FIFO_ENABLE_CH2_OUTPUT    (0x1 << 27)

/**
 * \brief Input/Output direction
 */
typedef enum
{
    HW_SRC_IN,                         /**< SRC input */
    HW_SRC_OUT,                        /**< SRC output */
} BSP_SRC_DIRECTION;

/**
 * \brief Flow status
 */
typedef enum
{
    HW_SRC_FLOW_OK = 0,                /**< No flow errors */
    HW_SRC_FLOW_OVER,                  /**< Overflow errors */
    HW_SRC_FLOW_UNDER,                 /**< Underflow errors */
    HW_SRC_FLOW_OVER_UNDER,            /**< Both overflow and underflow errors */
} BSP_SRC_FLOW_STATUS;

/**
 * \brief Input/Output selection
 */
typedef enum
{
    HW_SRC_PCM = 1,                    /**< PCM interface */
    HW_SRC_PDM,                        /**< PDM interface */
    HW_SRC_REGS,                       /**< SRC registers */
    HW_SRC_FIFO,                       /**< SRC FIFO */
    HW_SRC_SELECTION_SIZE
} BSP_SRC_SELECTION;

/**
 * \brief SRC sync multiplexer
 *
 */
typedef enum
{
    HW_SRC_INPUT_MUX_SRC_IN_REG,       /**< SRC IN REG */
    HW_SRC_INPUT_MUX_SRC_OUT_REG,      /**< SRC OUT REG */
    HW_SRC_INPUT_MUX_PCM_OUT_REG,      /**< set to PCM_OUT_REG */
    HW_SRC_INPUT_MUX_SYNC_DIV,         /**< set to SYNC DIV */
    HW_SRCx_MUX_IN_SIZE
} BSP_SRC_SYNC;

/**
 * \brief SRC configuration structure definition
 */
typedef struct
{
    HW_SRC_ID id;                      /**< identifies SRC */
    uint16_t  src_clk;                 /**< SRC clock in kHz with allowed values (in kHz):
                                        *    128,  160,  200,  250,  256,  320,  400,  500,  640,   800,
                                        *    1000, 1280, 1600, 2000, 3200, 4000, 6400, 8000, 16000, 32000 */
    uint32_t in_sample_rate;           /**< Input sampling rate in Hz with allowed values:
                                        *    0, 8000, 11025, 16000, 22050, 32000, 44100, 48000, 96000, 192000 */
    uint32_t out_sample_rate;          /**< Input sampling rate in Hz with allowed values:
                                        *    0, 8000, 11025, 16000, 22050, 32000, 44100, 48000, 96000, 192000 */
    BSP_SRC_SELECTION data_input;      /**< The SRC input */
    BSP_SRC_SELECTION data_output;     /**< The SRC output */
} bsp_src_config_t;

/* *************************************************************************
 *
 *                       ENABLE-DISABLE FUNCTIONS
 *
 * ************************************************************************* */

/**
 * \brief Enable SRC
 *
 * \param [in] id identifies SRC1
 */
__STATIC_INLINE void R_BSP_src_enable (HW_SRC_ID id)
{
    FSP_PARAMETER_NOT_USED(id);

    /*
     * The under/overflows that occur due to the reconfiguration can be
     * ignored, so we disable under/overflow notifications until
     * (SRC_IN_OK == 1 && SRC_OUT_OK == 1).
     */
    SRC_IF->APU_SRC_CTRL_REG_b.SRC_IN_FLOWCLR  = 1;
    SRC_IF->APU_SRC_CTRL_REG_b.SRC_OUT_FLOWCLR = 1;

    SRC_IF->APU_SRC_CTRL_REG_b.SRC_EN = 1;
#if 0
    while (REG_GETF(SRC_IF, APU_SRC_CTRL_REG, SRC_IN_OK) == 0 &&
           REG_GETF(SRC_IF, APU_SRC_CTRL_REG, SRC_OUT_OK) == 0)
    {
        ;
    }
#endif
    while (SRC_IF->APU_SRC_CTRL_REG_b.SRC_IN_OK == 0 &&
           SRC_IF->APU_SRC_CTRL_REG_b.SRC_OUT_OK == 0)
    {
        ;
    }

    SRC_IF->APU_SRC_CTRL_REG_b.SRC_IN_FLOWCLR  = 0;
    SRC_IF->APU_SRC_CTRL_REG_b.SRC_OUT_FLOWCLR = 0;
}

/**
 * \brief Disable SRC
 *
 * \param [in] id identifies SRC1
 */
__STATIC_INLINE void R_BSP_src_disable (HW_SRC_ID id)
{
    FSP_PARAMETER_NOT_USED(id);
    SRC_IF->APU_SRC_CTRL_REG_b.SRC_EN = 0;
}

/**
 * \brief Check if SRC is enabled
 *
 * \param [in] id       identifies SRC1,
 * \return
 *                     \retval True if it is enabled
 *                     \retval False if it is disabled
 *
 */
__STATIC_INLINE bool R_BSP_src_is_enabled (HW_SRC_ID id)
{
    FSP_PARAMETER_NOT_USED(id);

    return SRC_IF->APU_SRC_CTRL_REG_b.SRC_EN;
}

/**
 * \brief Enable SRC FIFO. FIFO is used to store samples from/to SRC
 *
 * \param [in] id       identifies SRC1
 * \param[in] direction The SRC FIFO direction.
 *                       HW_SRC_IN  - FIFO is used to store samples from memory to SRC
 *                       HW_SRC_OUT - FIFO is used to store samples from SRC to memory
 */

__STATIC_INLINE void R_BSP_src_enable_fifo (HW_SRC_ID id, BSP_SRC_DIRECTION direction)
{
    FSP_PARAMETER_NOT_USED(id);
    uint32_t reg_rd = SRC_IF->APU_SRC_FIFO_CTRL_REG_b.FIFO_CTRL;
    switch (direction)
    {
        case HW_SRC_IN:
        {
            SRC_IF->APU_SRC_FIFO_CTRL_REG_b.FIFO_CTRL = reg_rd | SRC_FIFO_ENABLE | SRC_FIFO_ENABLE_CH1_INPUT |
                                                        SRC_FIFO_ENABLE_CH2_INPUT;
            SRC_IF->APU_SRC_CTRL_REG_b.SRC_FIFO_IN1_ENABLE = 1;
            SRC_IF->APU_SRC_CTRL_REG_b.SRC_FIFO_IN2_ENABLE = 1;
            break;
        }

        case HW_SRC_OUT:
        {
            SRC_IF->APU_SRC_FIFO_CTRL_REG_b.FIFO_CTRL = reg_rd | SRC_FIFO_ENABLE | SRC_FIFO_ENABLE_CH1_OUTPUT |
                                                        SRC_FIFO_ENABLE_CH2_OUTPUT;
            SRC_IF->APU_SRC_CTRL_REG_b.SRC_FIFO_OUT1_ENABLE = 1;
            SRC_IF->APU_SRC_CTRL_REG_b.SRC_FIFO_OUT2_ENABLE = 1;
            break;
        }

        default:
        {
            break;
        }
    }
}

/**
 * \brief Disable SRC FIFO. On each SRC request, one sample is serviced.
 *
 * \param [in] id identifies SRC1
 */
__STATIC_INLINE void R_BSP_src_disable_fifo (HW_SRC_ID id)
{
    FSP_PARAMETER_NOT_USED(id);
    SRC_IF->APU_SRC_FIFO_CTRL_REG_b.FIFO_CTRL       = 0;
    SRC_IF->APU_SRC_CTRL_REG_b.SRC_FIFO_OUT2_ENABLE = 0;
}

/**
 * \brief Check if SRC FIFO is enabled. FIFO is used to store samples from/to SRC
 *
 * \param [in]   id identifies SRC1
 * \return
 *              \retval True if it is enabled
 *              \retval False if it is disabled
 */
__STATIC_INLINE bool R_BSP_src_is_fifo_enabled (HW_SRC_ID id)
{
    FSP_PARAMETER_NOT_USED(id);
    FSP_ASSERT(id == HW_SRC1);

    return SRC_IF->APU_SRC_FIFO_CTRL_REG_b.FIFO_CTRL;
}

/* *************************************************************************
 *
 *                              SET FUNCTIONS
 *
 * ************************************************************************* */

/**
 * \brief Set Automatic Conversion mode
 *
 * \param [in] id               identifies SRC1
 * \param[in] direction         Input/Output direction of data flow allowed values:
 *                                       HW_SRC_IN, HW_SRC_OUT
 */
__STATIC_INLINE void R_BSP_src_set_automode (HW_SRC_ID id, BSP_SRC_DIRECTION direction)
{
    FSP_PARAMETER_NOT_USED(id);
    if (direction == HW_SRC_IN)
    {
        SRC_IF->APU_SRC_CTRL_REG_b.SRC_IN_AMODE = 1;
    }
    else
    {
        SRC_IF->APU_SRC_CTRL_REG_b.SRC_OUT_AMODE = 1;
    }
}

/**
 * \brief Clear Automatic Conversion mode. Use manual mode
 *
 * \param [in] id               identifies SRC1
 * \param[in] direction         Input/Output direction of data flow allowed values:
 *                                       HW_SRC_IN, HW_SRC_OUT
 */
__STATIC_INLINE void R_BSP_src_set_manual_mode (HW_SRC_ID id, BSP_SRC_DIRECTION direction)
{
    FSP_PARAMETER_NOT_USED(id);
    if (direction == HW_SRC_IN)
    {
        SRC_IF->APU_SRC_CTRL_REG_b.SRC_IN_AMODE = 0;
    }
    else
    {
        SRC_IF->APU_SRC_CTRL_REG_b.SRC_OUT_AMODE = 0;
    }
}

/**
 * \brief Set Automatic Conversion mode sync
 *
 * \param [in] id               identifies SRC1
 * \param[in] direction         Input/Output direction of data flow allowed values:
 *                                       HW_SRC_IN, HW_SRC_OUT
 * \param[in] sync              SRC Automode sync
 */
__STATIC_INLINE void R_BSP_src_set_automode_sync (HW_SRC_ID id, BSP_SRC_DIRECTION direction, BSP_SRC_SYNC sync)
{
    FSP_PARAMETER_NOT_USED(id);
    if (direction == HW_SRC_IN)
    {
        APU_DSP->APU_SYNC_SRC1IN_SEL_REG_b.SRC1_IN_A_SEL = sync;
    }
    else
    {
        APU_DSP->APU_SYNC_SRC1OUT_SEL_REG_b.SRC1_OUT_A_SEL = sync;
    }
}

/**
 * \brief Select the SRC mux
 *
 * \note call this function once SRC interface initialization is done
 *
 * \param[in] input          the SRC input
 * \param[in] output         the SRC output
 * \param[in, out] config    the configuration structure of SRC
 */
__STATIC_INLINE void R_BSP_src_select_mux (BSP_SRC_SELECTION input, BSP_SRC_SELECTION output, bsp_src_config_t * config)
{
    uint32_t temp_read;

    config->data_input = input;

    switch (input)
    {
        case HW_SRC_PDM:
        {
            SRC_IF->APU_SRC_CTRL_REG_b.SRC_PDM_EN = 1;
            break;
        }

        case HW_SRC_PCM:
        {
            SRC_IF->APU_SRC_CTRL_REG_b.SRC_PDM_EN = 0;
            temp_read = APU_DSP->APU_MUX_CTRL_REG_b.APU_DSP_MUX_CTL;
            APU_DSP->APU_MUX_CTRL_REG_b.APU_DSP_MUX_CTL = (uint8_t) (temp_read & ~(0x3UL));
            break;
        }

        case HW_SRC_REGS:
        {
            SRC_IF->APU_SRC_CTRL_REG_b.SRC_PDM_EN = 0;
            temp_read = APU_DSP->APU_MUX_CTRL_REG_b.APU_DSP_MUX_CTL;
            APU_DSP->APU_MUX_CTRL_REG_b.APU_DSP_MUX_CTL = (uint8_t) (temp_read | (0x1 << 0));

            break;
        }

        case HW_SRC_FIFO:
        {
            SRC_IF->APU_SRC_CTRL_REG_b.SRC_PDM_EN = 0;
            temp_read = APU_DSP->APU_MUX_CTRL_REG_b.APU_DSP_MUX_CTL;
            APU_DSP->APU_MUX_CTRL_REG_b.APU_DSP_MUX_CTL = (uint8_t) ((temp_read | (0x1 << 1)) & ~(0x1UL << 0));
            break;
        }

        default:
        {
            break;
        }
    }

    switch (output)
    {
        case HW_SRC_REGS:
        {
            temp_read = APU_DSP->APU_MUX_CTRL_REG_b.APU_DSP_MUX_CTL;
            APU_DSP->APU_MUX_CTRL_REG_b.APU_DSP_MUX_CTL = (uint8_t) ((temp_read | (0x1 << 2)) & ~(0x1UL << 3));
            break;
        }

        case HW_SRC_FIFO:
        {
            temp_read = APU_DSP->APU_MUX_CTRL_REG_b.APU_DSP_MUX_CTL;
            APU_DSP->APU_MUX_CTRL_REG_b.APU_DSP_MUX_CTL = (uint8_t) ((temp_read | (0x1 << 3)) & ~(0x1UL << 2));
            break;
        }

        default:
        {
            break;
        }
    }
}

/**
 * \brief Write data to an input SRC register
 *
 * \param [in] id       identifies SRC1
 * \param[in] stream    The input stream (1 or 2)
 * \param[in] value     The data to be written
 */
__STATIC_INLINE void R_BSP_src_write_input (HW_SRC_ID id, uint8_t stream, uint32_t value)
{
    FSP_PARAMETER_NOT_USED(id);
    switch (stream)
    {
        case 1:
        {
            SRC_IF->APU_SRC_IN1_REG_b.SRC_IN = value;
            break;
        }

        case 2:
        {
            SRC_IF->APU_SRC_IN2_REG_b.SRC_IN = value;
            break;
        }

        default:
        {
            break;
        }
    }
}

/**
 * \brief Write data to an input SRC FIFO register
 *
 * \param [in] id       identifies SRC1
 * \param[in] stream    The input stream (1 or 2)
 * \param[in] value     The data to be written
 */
__STATIC_INLINE void R_BSP_src_write_fifo_input (HW_SRC_ID id, uint8_t stream, uint32_t value)
{
    FSP_PARAMETER_NOT_USED(id);
    switch (stream)
    {
        case 1:
        {
            SRC_FIFO_IF->APU_SRC_FIFO_IN1_REG_b.SRC_IN = value;
            break;
        }

        case 2:
        {
            SRC_FIFO_IF->APU_SRC_FIFO_IN2_REG_b.SRC_IN = value;
            break;
        }

        default:
        {
            break;
        }
    }
}

/* *************************************************************************
 *
 *                              GET FUNCTIONS
 *
 * ************************************************************************* */

/**
 * \brief Get the mode
 *
 * \param [in] id            identifies SRC1
 * \param[in] direction      Input/Output direction of data flow allowed values:
 *                                       HW_SRC_IN, HW_SRC_OUT
 * \return mode
 *                            \retval 0 for manual mode
 *                            \retval 1 for automatic mode
 */
__STATIC_INLINE bool R_BSP_src_is_auto_mode (HW_SRC_ID id, BSP_SRC_DIRECTION direction)
{
    FSP_ASSERT(id == HW_SRC1);

    if (direction == HW_SRC_IN)
    {
        return SRC_IF->APU_SRC_CTRL_REG_b.SRC_IN_AMODE;
    }
    else
    {
        return SRC_IF->APU_SRC_CTRL_REG_b.SRC_OUT_AMODE;
    }
}

/**
 * \brief Read data from an output SRC register
 *
 * \param [in] id       identifies SRC1
 * \param[in] stream    The output stream (1 or 2)
 *
 * \return              The data read
 */
__STATIC_INLINE uint32_t R_BSP_src_read_output (HW_SRC_ID id, uint8_t stream)
{
    FSP_ASSERT(id == HW_SRC1);

    switch (stream)
    {
        case 1:
        {
            return SRC_IF->APU_SRC_OUT1_REG_b.SRC_OUT;
        }

        case 2:
        {
            return SRC_IF->APU_SRC_OUT2_REG_b.SRC_OUT;
        }

        default:
            FSP_ASSERT(0);

            return 0;
    }
}

/**
 * \brief Read data from an output SRC FIFO register
 *
 * \param [in] id       identifies SRC1
 * \param[in] stream    The output stream (1 or 2)
 *
 * \return              The data read
 */
__STATIC_INLINE uint32_t R_BSP_src_read_fifo_output (HW_SRC_ID id, uint8_t stream)
{
    FSP_ASSERT(id == HW_SRC1);

    switch (stream)
    {
        case 1:
        {
            return SRC_FIFO_IF->APU_SRC_FIFO_OUT1_REG_b.SRC_OUT;
        }

        case 2:
        {
            return SRC_FIFO_IF->APU_SRC_FIFO_OUT2_REG_b.SRC_OUT;
        }

        default:
            FSP_ASSERT(1);

            return 0;
    }
}

/**
 * \brief Check if SRC flow errors have occurred and clear the indication
 *
 * \param [in] id               identifies SRC1
 * \param[in] direction         Input/Output direction
 *
 * \return                      The flow status
 */
BSP_SRC_FLOW_STATUS R_BSP_src_get_flow_status(HW_SRC_ID id, BSP_SRC_DIRECTION direction);

/**
 * \brief Initialize the SRC
 *
 * Configure the SRC sampling frequencies, the input down-sampler and output up-sampler IIR filters,
 * the conversion modes, the divider of the internally generated clock and enable the clock
 *
 * \note call R_BSP_src_enable() once SRC interface initialization is done
 *
 * \param[in]   id          identifies SRC1
 * \param[out]  config      configuration structure of SRC
 */
void R_BSP_src_init(HW_SRC_ID id, bsp_src_config_t * config);

#endif                                 /* BSP_SRC_RA6W1_H */

/**
 * \}
 * \}
 */
