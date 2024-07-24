/*!
    \file    gd32h7xx_fac.c
    \brief   FAC driver

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

#include "gd32h7xx_fac.h"
#include <stdio.h>

/*!
    \brief      reset FAC peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fac_deinit(void)
{
    rcu_periph_reset_enable(RCU_FACRST);
    rcu_periph_reset_disable(RCU_FACRST);
}

/*!
    \brief      initialize the FAC filter parameter struct with the default values
    \param[in]  fac_parameter: fac parameter struct
    \param[out] none
    \retval     none
*/
void fac_struct_para_init(fac_parameter_struct *fac_parameter)
{
    fac_parameter->input_addr       = 0U;
    fac_parameter->input_size       = 0U;
    fac_parameter->input_threshold  = 0U;
    fac_parameter->coeff_addr       = 0U;
    fac_parameter->coeff_size       = 0U;
    fac_parameter->output_addr      = 0U;
    fac_parameter->output_size      = 0U;
    fac_parameter->output_threshold = 0U;
    fac_parameter->clip             = 0U;
    fac_parameter->func             = 0U;
    fac_parameter->ipp              = 0U;
    fac_parameter->ipq              = 0U;
    fac_parameter->ipr              = 0U;
}

/*!
    \brief      initialize the FAC fixed data preload parameter struct with the default values
    \param[in]  fac_parameter: fac parameter struct
    \param[out] none
    \retval     none
*/
void fac_fixed_data_preload_init(fac_fixed_data_preload_struct *init_struct)
{
    init_struct->coeffa_size       = 0U;
    init_struct->coeffa_ctx        = 0U;
    init_struct->coeffb_size       = 0U;
    init_struct->coeffb_ctx        = 0U;
    init_struct->input_size        = 0U;
    init_struct->input_ctx         = 0U;
    init_struct->output_size       = 0U;
    init_struct->output_ctx        = 0U;
}

/*!
    \brief      initialize the FAC float data preload parameter struct with the default values
    \param[in]  fac_parameter: fac parameter struct
    \param[out] none
    \retval     none
*/
void fac_float_data_preload_init(fac_float_data_preload_struct *init_struct)
{
    init_struct->coeffa_size       = 0U;
    init_struct->coeffa_ctx        = 0U;
    init_struct->coeffb_size       = 0U;
    init_struct->coeffb_ctx        = 0U;
    init_struct->input_size        = 0U;
    init_struct->input_ctx         = 0U;
    init_struct->output_size       = 0U;
    init_struct->output_ctx        = 0U;
}

/*!
    \brief      initialize the FAC peripheral
    \param[in]  init_struct: the data needed to initialize FAC
                  input_addr: x0 buffer base address, 0..255
                  input_size: x0 buffer size, 0..255
                  input_threshold: FAC_THRESHOLD_1, FAC_THRESHOLD_2,
                                   FAC_THRESHOLD_4, FAC_THRESHOLD_8
                  coeff_addr: x1 buffer base address, 0..255
                  coeff_size: x1 buffer size, 0..255
                  output_addr: Y buffer base address, 0..255
                  output_size: Y buffer size, 0..255
                  output_threshold: FAC_THRESHOLD_1, FAC_THRESHOLD_2,
                                    FAC_THRESHOLD_4, FAC_THRESHOLD_8
                  clip: enable or disable the clipping feature
                  ipp: value IPP (vector length, number of filter taps, etc.)
                  ipq: value IPQ (vector length, etc.)
                  ipr: value IPR (gain, etc.)
    \param[out] none
    \retval     none
*/
void fac_init(fac_parameter_struct *fac_parameter)
{
    /* FAC_X0BCFG: configure the input X0 buffer */
    FAC_X0BCFG = ((((uint32_t)fac_parameter->input_addr) & FAC_X0BCFG_X0B_ADDR) | \
                  ((((uint32_t)fac_parameter->input_size) << 8U) & FAC_X0BCFG_X0B_SIZE));

    /* FAC_X0BCFG: configure the input X0 threshold */
    FAC_X0BCFG |= (((uint32_t)fac_parameter->input_threshold) & FAC_X0BCFG_X0_WBFF);

    /* FAC_X1BCFG: configure the coefficient X1 buffer */
    FAC_X1BCFG = ((((uint32_t)fac_parameter->coeff_addr) & FAC_X1BCFG_X1B_ADDR) | \
                  ((((uint32_t)fac_parameter->coeff_size) << 8U) & FAC_X1BCFG_X1B_SIZE));

    /* FAC_YBCFG: configure the output Y buffer */
    FAC_YBCFG = ((((uint32_t)fac_parameter->output_addr) & FAC_YBCFG_YB_ADDR) | \
                 ((((uint32_t)fac_parameter->output_size) << 8U) & FAC_YBCFG_YB_SIZE));

    /* FAC_YBCFG: configure the output Y threshold */
    FAC_YBCFG |= (((uint32_t)fac_parameter->output_threshold) & FAC_YBCFG_Y_WBEF);

    /* FAC_CTL: configure the state of clip */
    FAC_CTL |= ((((uint32_t)fac_parameter->clip) << 15U) & FAC_CTL_CPEN);
}

/*!
    \brief      FAC preload X0 X1 Y fixed buffer
    \param[in]  init_struct: FAC preload init struct
                  coeffa_size: size of the coefficient vector A,0~255
                  coeffa_ctx: [IIR only] content of the coefficient vector A
                  coeffb_size: size of the coefficient vector B
                  coeffb_ctx: size of the coefficient vector B
                  input_size: size of the input data,0~255
                  input_ctx: content of the input data
                  output_size: size of the output data,0~255
                  output_ctx: content of the output data
                only one parameter can be selected which is shown as below:
      \arg      PRELOAD_DMA_MODE: preload access buffer mode with dma
      \arg      PRELOAD_POLLING_MODE: preload access buffer mode with polling
    \param[out] none
    \retval     none
*/
void fac_fixed_buffer_preload(fac_fixed_data_preload_struct *init_struct)
{
    /* FAC_PARACFG: configure parameter of filter preload */
    FAC_PARACFG = ((uint32_t)init_struct->input_size & FAC_PARACFG_IPP) | \
                  FUNC_LOAD_X0 | FAC_PARACFG_EXE;

    /* load the X0 buffer for input data */
    fac_fixed_data_preload(init_struct->input_size, init_struct->input_ctx);
    /* configure dma for X0 preload */

    /* FAC_PARACFG: configure parameter of filter preload */
    FAC_PARACFG = (((uint32_t)init_struct->coeffb_size) & FAC_PARACFG_IPP) | \
                  ((((uint32_t)init_struct->coeffa_size) << 8) & FAC_PARACFG_IPQ) | \
                  FUNC_LOAD_X1 | FAC_PARACFG_EXE;

    /* load the x1 buffer for cofficientB */
    fac_fixed_data_preload(init_struct->coeffb_size, (init_struct->coeffb_ctx));

    /* load the x1 buffer for cofficientA */
    if((NULL != init_struct->coeffa_ctx) && (0U != init_struct->coeffa_size))
    {
        /* Load the buffer into the internal memory */
        fac_fixed_data_preload(init_struct->coeffa_size, (init_struct->coeffa_ctx));
    }
    /* if need configure to preload output buffer */
    if((NULL != init_struct->output_ctx) && (0U != init_struct->output_size))
    {
        FAC_PARACFG = ((uint32_t)init_struct->output_size & FAC_PARACFG_IPP) |  \
                      FUNC_LOAD_Y | FAC_PARACFG_EXE;

        /* load the Y buffer for input data */
        fac_fixed_data_preload(init_struct->output_size, init_struct->output_ctx);
    }
}

/*!
    \brief      FAC preload X0 X1 Y float buffer
    \param[in]  init_struct: FAC preload init struct
                  coeffa_size: size of the coefficient vector A,0~255
                  coeffa_ctx: [IIR only] content of the coefficient vector A
                  coeffb_size: size of the coefficient vector B
                  coeffb_ctx: size of the coefficient vector B
                  input_size: size of the input data,0~255
                  input_ctx: content of the input data
                  output_size: size of the output data,0~255
                  output_ctx: content of the output data
                only one parameter can be selected which is shown as below:
      \arg      PRELOAD_DMA_MODE: preload access buffer mode with dma
      \arg      PRELOAD_POLLING_MODE: preload access buffer mode with polling
    \param[out] none
    \retval     none
*/
void fac_float_buffer_preload(fac_float_data_preload_struct *init_struct)
{
    /* FAC_PARACFG: Config parameter of filter preload */
    FAC_PARACFG = ((uint32_t)init_struct->input_size & FAC_PARACFG_IPP) | \
                  FUNC_LOAD_X0 | FAC_PARACFG_EXE;

    /* load the x0 buffer for input data */
    fac_float_data_preload(init_struct->input_size, init_struct->input_ctx);
    /* configure dma for x0 preload */
    /* FAC_PARACFG: Config parameter of filter preload */
    FAC_PARACFG = (((uint32_t)init_struct->coeffb_size) & FAC_PARACFG_IPP) | \
              ((((uint32_t)init_struct->coeffa_size) << 8) & FAC_PARACFG_IPQ) | \
              FUNC_LOAD_X1 | FAC_PARACFG_EXE;

    /* load the x1 buffer for cofficientB */
    fac_float_data_preload(init_struct->coeffb_size, (init_struct->coeffb_ctx));

    /* load the x1 buffer for cofficientA */
    if((NULL != init_struct->coeffa_ctx) && (0U != init_struct->coeffa_size))
    {
        /* load the buffer into the internal memory */
        fac_float_data_preload(init_struct->coeffa_size, (init_struct->coeffa_ctx));
    }
    /* if need configure to preload output buffer */
    if((NULL != init_struct->output_ctx) && (0U != init_struct->output_size))
    {
        FAC_PARACFG = ((uint32_t)init_struct->output_size & FAC_PARACFG_IPP) | \
                      FUNC_LOAD_Y | FAC_PARACFG_EXE;

        /* load the Y buffer for input data */
        fac_float_data_preload(init_struct->output_size, init_struct->output_ctx);
    }
}
/*!
    \brief      FAC preload fixed data pointer
    \param[in]  array: 16-bit data
    \param[in]  size: size of data
    \param[out] none
    \retval     none
*/
void fac_fixed_data_preload(uint8_t size, int16_t array[])
{
    uint8_t i;
    for(i = 0U; i < size; i++)
    {
        FAC_WDATA = ((*((uint16_t*)&array[i])) & FAC_WDATA_WDATA);
    }
}

/*!
    \brief      FAC preload float data pointer
    \param[in]  data: 32-bit data
    \param[in]  size: size of data
    \param[out] none
    \retval     none
*/
void fac_float_data_preload(uint8_t size, float array[])
{
    uint8_t i;
    for(i = 0U; i < size; i++)
    {
        FAC_WDATA = ((*((uint32_t*) & array[i])));
    }
}

/*!
    \brief      FAC reset write and read pointers. the internal control logic,FAC_STAT register and the FAC_PARACFG register is reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fac_reset(void)
{
    FAC_CTL |= FAC_CTL_RST;
}

/*!
    \brief      configure the FAC clip feature
    \param[in]  cpmod: the state of clip
                only one parameter can be selected which is shown as below:
      \arg        FAC_CP_ENABLE: ENABLE CLIP
      \arg        FAC_CP_DISABLE: DISABLE CLIP
    \param[out] none
    \retval     none
*/
void fac_clip_config(uint8_t cpmod)
{
    if(FAC_CP_ENABLE == cpmod)
    {
        FAC_CTL |= FAC_CTL_CPEN;
    } else {
        FAC_CTL &= ~(FAC_CTL_CPEN);
    }
}

/*!
    \brief      enable FAC float point format
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fac_float_enable(void)
{
    FAC_CTL |= FAC_CTL_FLTEN;
}

/*!
    \brief      disable FAC float point format
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fac_float_disable(void)
{
    FAC_CTL &= ~FAC_CTL_FLTEN;
}

/*!
    \brief      enable the FAC DMA
    \param[in]  dma_req: dma transfer type
                only one parameter can be selected which is shown as below:
      \arg        FAC_DMA_READ: read buffer dma
      \arg        FAC_DMA_WRITE: write buffer dma
    \param[out] none
    \retval     none
*/
void fac_dma_enable(uint32_t dma_req)
{
    FAC_CTL |= dma_req;
}

/*!
    \brief      disable the FAC DMA
    \param[in]  dma_req: dma transfer type
                only one parameter can be selected which is shown as below:
      \arg        FAC_DMA_READ: read buffer dma
      \arg        FAC_DMA_WRITE: write buffer dma
    \param[out] none
    \retval     none
*/
void fac_dma_disable(uint32_t dma_req)
{
    FAC_CTL &= ~dma_req;
}

/*!
    \brief      FAC configure input buffer
    \param[in]  watermark: threshold of input buffer
                  FAC_THRESHOLD_1, FAC_THRESHOLD_2,
                  FAC_THRESHOLD_4, FAC_THRESHOLD_8
    \param[in]  baseaddr: base address of input buffer, 0..255
    \param[in]  bufsize: buffer size of input buffer, 0..255
    \param[out] none
    \retval     none
*/
void fac_x0_config(uint32_t watermark, uint8_t baseaddr, uint8_t bufsize)
{
    /* set base address */
    FAC_X0BCFG &= ~FAC_X0BCFG_X0B_ADDR;
    FAC_X0BCFG |= ((uint32_t)baseaddr);

    /* set buffer size */
    FAC_X0BCFG &= ~FAC_X0BCFG_X0B_SIZE;
    FAC_X0BCFG |= (((uint32_t)bufsize) << 8U);

    /* set watermark */
    FAC_X0BCFG &= ~FAC_X0BCFG_X0_WBFF;
    FAC_X0BCFG |= watermark;
}

/*!
    \brief      FAC configure coefficient buffer
    \param[in]  baseaddr: base address of coefficient buffer, 0..255
    \param[in]  bufsize: buffer size of coefficient buffer, 0..255
    \param[out] none
    \retval     none
*/
void fac_x1_config(uint8_t baseaddr, uint8_t bufsize)
{
    /* set base address */
    FAC_X1BCFG &= ~FAC_X1BCFG_X1B_ADDR;
    FAC_X1BCFG |= ((uint32_t)baseaddr);

    /* set buffer size */
    FAC_X1BCFG &= ~FAC_X1BCFG_X1B_SIZE;
    FAC_X1BCFG |= (((uint32_t)bufsize) << 8U);
}

/*!
    \brief      FAC configure output buffer
    \param[in]  watermark: threshold of output buffer
                  FAC_THRESHOLD_1, FAC_THRESHOLD_2,
                  FAC_THRESHOLD_4, FAC_THRESHOLD_8
    \param[in]  baseaddr: base address of output buffer, 0..255
    \param[in]  bufsize: buffer size of output buffer, 0..255
    \param[out] none
    \retval     none
*/
void fac_y_config(uint32_t watermark, uint8_t baseaddr, uint8_t bufsize)
{
    /* set base address */
    FAC_YBCFG &= ~FAC_YBCFG_YB_ADDR;
    FAC_YBCFG |= ((uint32_t)baseaddr);

    /* set buffer size */
    FAC_YBCFG &= ~FAC_YBCFG_YB_SIZE;
    FAC_YBCFG |= (((uint32_t)bufsize) << 8U);

    /* set watermark */
    FAC_YBCFG &= ~FAC_YBCFG_Y_WBEF;
    FAC_YBCFG |= watermark;
}

/*!
    \brief      FAC configure execute function
    \param[in]  func: select function to excute
                  FUNC_CONVO_FIR, FUNC_IIR_DIRECT_FORM_1
    \param[in]  ipp: parameter of forward coefficient, 2..64
    \param[in]  ipq: parameter of backward coefficient, 1..63
    \param[in]  ipr: parameter of gain, 0..7
    \param[out] none
    \retval     none
*/
void fac_function_config(fac_parameter_struct *fac_parameter)
{
    /* set function */
    FAC_PARACFG &= ~FAC_PARACFG_FUN;
    FAC_PARACFG |= fac_parameter->func;

    /* set filter parameter */
    FAC_PARACFG &= ~(FAC_PARACFG_IPP | FAC_PARACFG_IPQ | FAC_PARACFG_IPR);
    FAC_PARACFG |= ((uint32_t)fac_parameter->ipp) | (((uint32_t)fac_parameter->ipq) << 8U) | (((uint32_t)fac_parameter->ipr) << 16U);
}

/*!
    \brief      start the fac
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fac_start(void)
{
    /* set start */
    FAC_PARACFG |= FAC_PARACFG_EXE;
}

/*!
    \brief      stop the fac
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fac_stop(void)
{
    /* set start */
    FAC_PARACFG &= ~FAC_PARACFG_EXE;
}

/*!
    \brief      finish the filter calculate
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fac_finish_calculate(void)
{
    /* clear execute */
    FAC_PARACFG &= ~FAC_PARACFG_EXE;

    /* disable read and write interrupt */
    fac_interrupt_disable(FAC_CTL_RIE | FAC_CTL_WIE);

    /* disable read and write dma */
    fac_dma_disable(FAC_DMA_READ);
    fac_dma_disable(FAC_DMA_WRITE);

    /* reset register and pointer */
    FAC_CTL |= FAC_CTL_RST;
}

/*!
    \brief      FAC write data with fixed ponit format
    \param[in]  data: 16-bit data
    \param[out] none
    \retval     none
*/
void fac_fixed_data_write(int16_t data)
{
    FAC_WDATA_INT = (int16_t)data;
}

/*!
    \brief      FAC read data with fixed point format
    \param[in]  none
    \param[out] none
    \retval     16-bit data
*/
int16_t fac_fixed_data_read(void)
{   int16_t value;
    value = (int16_t)FAC_RDATA_INT;
    return value;
}

/*!
    \brief      FAC write data with float ponit format
    \param[in]  data: 16-bit data
    \param[out] none
    \retval     none
*/
void fac_float_data_write(float data)
{
    FAC_WDATA_FLOAT = (float)data;
}

/*!
    \brief      FAC read data with fixed point format
    \param[in]  none
    \param[out] none
    \retval     16-bit data
*/
float fac_float_data_read(void)
{
    float value;
    value = (float)FAC_RDATA_FLOAT;
    return value;
}

/*!
    \brief      enable the FAC Interrupt
    \param[in]  interrupt: FAC Interrupt
                only one parameter can be selected which is shown as below:
      \arg        FAC_CTL_RIE: Read buffer interrupt
      \arg        FAC_CTL_WIE: Write buffer interrupt
      \arg        FAC_CTL_OFEIE: Overflow error interrupt
      \arg        FAC_CTL_UFEIE: Underflow error interrupt
      \arg        FAC_CTL_STEIE: Saturation error interrupt
      \arg        FAC_CTL_GSTEIE: gain saturation error interrupt
    \param[out] none
    \retval     none
*/
void fac_interrupt_enable(uint32_t interrupt)
{
    FAC_CTL |= interrupt;
}

/*!
    \brief      disable the FAC Interrupt
    \param[in]  interrupt: FAC Interrupt
                only one parameter can be selected which is shown as below:
      \arg        FAC_CTL_RIE: Read buffer interrupt
      \arg        FAC_CTL_WIE: Write buffer interrupt
      \arg        FAC_CTL_OFEIE: Overflow error interrupt
      \arg        FAC_CTL_UFEIE: Underflow error interrupt
      \arg        FAC_CTL_STEIE: Saturation error interrupt
      \arg        FAC_CTL_GSTEIE: gain saturation error interrupt
    \param[out] none
    \retval     none
*/
void fac_interrupt_disable(uint32_t interrupt)
{
    FAC_CTL &= ~interrupt;
}

/*!
    \brief      get FAC interrupt flag status
    \param[in]  interrupt: FAC interrupt flag status
                only one parameter can be selected which is shown as below:
      \arg        FAC_INT_FLAG_YBEF: Y buffer read interrupt flag
      \arg        FAC_INT_FLAG_X0BFF: X0 buffer write interrupt flag
      \arg        FAC_INT_FLAG_OFEF: overflow error interrupt flag
      \arg        FAC_INT_FLAG_UFEF: underflow error interrupt flag
      \arg        FAC_INT_FLAG_STEF: saturation error interrupt flag
      \arg        FAC_INT_FLAG_GSTEF: gain saturation error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fac_interrupt_flag_get(uint8_t interrupt)
{
    uint32_t reg1 = FAC_CTL;
    uint32_t reg2 = FAC_STAT;

    switch(interrupt)
    {
        /*  Y buffer read interrupt */
        case FAC_INT_FLAG_YBEF:
            reg1 = reg1 & FAC_CTL_RIE;
            reg2 = (((reg2 & FAC_STAT_YBEF) == 0U)?FAC_STAT_YBEF:0U);
            break;
        /* X0 buffer write interrupt */
        case FAC_INT_FLAG_X0BFF:
            reg1 = reg1 & FAC_CTL_WIE;
            reg2 = (((reg2 & FAC_STAT_X0BFF) == 0U)?FAC_STAT_X0BFF:0U);
            break;
        /* overflow error interrupt */
        case FAC_INT_FLAG_OFEF:
            reg1 = reg1 & FAC_CTL_OFEIE;
            reg2 = reg2 & FAC_STAT_OFEF;
            break;
        /* underflow error interrupt */
        case FAC_INT_FLAG_UFEF:
            reg1 = reg1 & FAC_CTL_UFEIE;
            reg2 = reg2 & FAC_STAT_UFEF;
            break;
        /* saturation error interrupt */
        case FAC_INT_FLAG_STEF:
            reg1 = reg1 & FAC_CTL_STEIE;
            reg2 = reg2 & FAC_STAT_STEF;
            break;
        /* saturation error interrupt */
        case FAC_INT_FLAG_GSTEF:
            reg1 = reg1 & FAC_CTL_GSTEIE;
            reg2 = reg2 & FAC_STAT_GSTEF;
            break;
        default :
            break;
    }
    /*get FAC interrupt flag status */
    if(reg1 && reg2)
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      get FAC flag status
    \param[in]  flag: FAC flag status
                only one parameter can be selected which is shown as below:
      \arg        FAC_FLAG_YBEF: Y buffer empty flag
      \arg        FAC_FLAG_X0BFF: X0 buffer full flag
      \arg        FAC_FLAG_OFEF: overflow error flag
      \arg        FAC_FLAG_UFEF: underflow error flag
      \arg        FAC_FLAG_STEF: saturation error flag
      \arg        FAC_FLAG_GSTEF: gain saturation error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fac_flag_get(uint32_t flag)
{
    if(FAC_STAT & flag)
    {
        return SET;
    } else {
        return RESET;
    }
}

