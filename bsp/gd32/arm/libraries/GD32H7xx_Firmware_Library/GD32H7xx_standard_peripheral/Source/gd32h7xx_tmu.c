/*!
    \file    gd32h7xx_tmu.c
    \brief   TMU driver

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

#include "gd32h7xx_tmu.h"

#define MASK_LOW_HALFWORD       ((uint32_t)0xFFFF0000U)
#define MASK_HIGH_HALFWORD      ((uint32_t)0x0000FFFFU)

/*!
    \brief      reset the TMU registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_deinit(void)
{
    rcu_periph_reset_enable(RCU_TMURST);
    rcu_periph_reset_disable(RCU_TMURST);
}

/*!
    \brief      initialize the parameters of TMU struct with the default values
    \param[in]  init_struct: pointer to init parameter struct
    \param[out] none
    \retval     none
*/
void tmu_struct_para_init(tmu_parameter_struct* init_struct)
{
    /* set the struct with the default values */
    init_struct->mode               = TMU_MODE_COS;
    init_struct->iterations_number  = TMU_ITERATION_STEPS_20;
    init_struct->scale              = TMU_SCALING_FACTOR_1;
    init_struct->dma_read           = TMU_READ_DMA_DISABLE;
    init_struct->dma_write          = TMU_WRITE_DMA_DISABLE;
    init_struct->read_times         = TMU_READ_TIMES_1;
    init_struct->write_times        = TMU_WRITE_TIMES_1;
    init_struct->output_width       = TMU_OUTPUT_WIDTH_32;
    init_struct->input_width        = TMU_INPUT_WIDTH_32;
}

/*!
    \brief      initialize TMU
    \param[in]  init_struct: pointer to init parameter struct
                  mode: TMU_MODE_COS,TMU_MODE_SIN,TMU_MODE_ATAN2,TMU_MODE_MODULUS,TMU_MODE_ATAN,
                        TMU_MODE_COSH,TMU_MODE_SINH,TMU_MODE_ATANH,TMU_MODE_LN,TMU_MODE_SQRT
                  iterations_number: TMU_ITERATION_STEPS_x(x=4,8,12,..24)
                  scale: TMU_SCALING_FACTOR_x(x=1,2,4,8,16,32,64,128)
                  dma_read: TMU_READ_DMA_DISABLE, TMU_READ_DMA_ENABLE
                  dma_write: TMU_WRITE_DMA_DISABLE, TMU_WRITE_DMA_ENABLE
                  read_times: TMU_READ_TIMES_1, TMU_READ_TIMES_2
                  write_times: TMU_WRITE_TIMES_1, TMU_WRITE_TIMES_2
                  output_width: TMU_OUTPUT_WIDTH_32, TMU_OUTPUT_WIDTH_16
                  input_width: TMU_INPUT_WIDTH_32, TMU_INPUT_WIDTH_16
    \param[out] none
    \retval     none
*/
void tmu_init(tmu_parameter_struct* init_struct)
{
    uint32_t reg = 0U;
    reg |= ( init_struct->mode | init_struct->iterations_number | init_struct->scale |\
             init_struct->dma_read | init_struct->dma_write | init_struct->read_times |\
             init_struct->write_times | init_struct->output_width | init_struct->input_width);
    TMU_CS = reg;
}

/*!
    \brief      enable TMU read interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_read_interrupt_enable(void)
{
    TMU_CS |= TMU_CS_RIE;
}

/*!
    \brief      disable TMU read interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_read_interrupt_disable(void)
{
    TMU_CS &= ~TMU_CS_RIE;
}

/*!
    \brief      enable TMU DMA read request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_dma_read_enable(void)
{
    TMU_CS |= TMU_CS_RDEN;
}

/*!
    \brief      disable TMU DMA read request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_dma_read_disable(void)
{
    TMU_CS &= ~TMU_CS_RDEN;
}

/*!
    \brief      enable TMU DMA write request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_dma_write_enable(void)
{
    TMU_CS |= TMU_CS_WDEN;
}

/*!
    \brief      disable TMU DMA write request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_dma_write_disable(void)
{
    TMU_CS &= ~TMU_CS_WDEN;
}

/*!
    \brief      write one data in q1.31 format
    \param[in]  data: the first input data only
    \param[out] none
    \retval     none
*/
void tmu_one_q31_write(uint32_t data)
{
    TMU_IDATA = data;
}

/*!
    \brief      write two data in q1.31 format
    \param[in]  data1: the first input data
    \param[in]  data2: the second input data
    \param[out] none
    \retval     none
*/
void tmu_two_q31_write(uint32_t data1, uint32_t data2)
{
    TMU_IDATA = data1;
    TMU_IDATA = data2;
}

/*!
    \brief      write two data in q1.15 format
    \param[in]  data1: the first input data
    \param[in]  data2: the second input data (this data is meaningless in mode4 ~ mode9)
    \param[out] none
    \retval     none
*/
void tmu_two_q15_write(uint16_t data1, uint16_t data2)
{
    TMU_IDATA = ((((uint32_t)data1) & MASK_HIGH_HALFWORD)| (((uint32_t)data2 << 16U) & MASK_LOW_HALFWORD));
}

/*!
    \brief      read one data in q1.31 format
    \param[in]  none
    \param[out] p: pointer to the first output data only
    \retval     none
*/
void tmu_one_q31_read(uint32_t* p)
{
    *p = TMU_ODATA;
}

/*!
    \brief      read two data in q1.31 format
    \param[in]  none
    \param[out] p1: pointer to the first output data
    \param[out] p2: pointer to the second output data
    \retval     none
*/
void tmu_two_q31_read(uint32_t* p1, uint32_t* p2)
{
    *p1 = TMU_ODATA;
    *p2 = TMU_ODATA;
}

/*!
    \brief      read two data in q1.15 format
    \param[in]  none
    \param[out] p1: pointer to the first output data
    \param[out] p2: pointer to the second output data (this data is meaningless in mode4, mode7 ~ mode9)
    \retval     none
*/
void tmu_two_q15_read(uint16_t* p1, uint16_t* p2)
{
    uint32_t data;
    data = TMU_ODATA;
    *p1 = (uint16_t)data;
    *p2 = (uint16_t)(data >> 16U);
}
