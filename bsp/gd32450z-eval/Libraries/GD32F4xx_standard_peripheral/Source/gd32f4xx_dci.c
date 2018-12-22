/*!
    \file  gd32f4xx_dci.c
    \brief DCI driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_dci.h"

/*!
    \brief      DCI deinit
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_deinit(void)
{
    rcu_periph_reset_enable(RCU_DCIRST);
    rcu_periph_reset_disable(RCU_DCIRST);
}

/*!
    \brief      initialize DCI registers
    \param[in]  dci_struct: DCI parameter initialization stuct
                members of the structure and the member values are shown as below:
                capture_mode    : DCI_CAPTURE_MODE_CONTINUOUS, DCI_CAPTURE_MODE_SNAPSHOT
                colck_polarity  : DCI_CK_POLARITY_FALLING, DCI_CK_POLARITY_RISING
                hsync_polarity  : DCI_HSYNC_POLARITY_LOW, DCI_HSYNC_POLARITY_HIGH                                      
                vsync_polarity  : DCI_VSYNC_POLARITY_LOW, DCI_VSYNC_POLARITY_HIGH
                frame_rate      : DCI_FRAME_RATE_ALL, DCI_FRAME_RATE_1_2, DCI_FRAME_RATE_1_4
                interface_format: DCI_INTERFACE_FORMAT_8BITS, DCI_INTERFACE_FORMAT_10BITS,
                                      DCI_INTERFACE_FORMAT_12BITS, DCI_INTERFACE_FORMAT_14BITS
    \param[out] none
    \retval     none
*/
void dci_init(dci_parameter_struct* dci_struct)
{
    uint32_t reg =0U;
    /* disable capture function and DCI */
    DCI_CTL &= ~(DCI_CTL_CAP | DCI_CTL_DCIEN);
    /* config DCI parameter */
    reg |= dci_struct->capture_mode;
    reg |= dci_struct->clock_polarity;
    reg |= dci_struct->hsync_polarity;
    reg |= dci_struct->vsync_polarity;
    reg |= dci_struct->frame_rate;
    reg |= dci_struct->interface_format;

    DCI_CTL = reg;
}

/*!
    \brief      enable DCI function 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_enable(void)
{
    DCI_CTL |= DCI_CTL_DCIEN;    
}

/*!
    \brief      disable DCI function 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_disable(void)
{
    DCI_CTL &= ~DCI_CTL_DCIEN;
}

/*!
    \brief      enable DCI capture 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_capture_enable(void)
{
    DCI_CTL |= DCI_CTL_CAP;
}

/*!
    \brief      disable DCI capture 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_capture_disable(void)
{
    DCI_CTL &= ~DCI_CTL_CAP;
}

/*!
    \brief      enable DCI jpeg mode 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_jpeg_enable(void)
{
    DCI_CTL |= DCI_CTL_JM;
}

/*!
    \brief      disable DCI jpeg mode 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_jpeg_disable(void)
{
    DCI_CTL &= ~DCI_CTL_JM;
}

/*!
    \brief      enable cropping window function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_crop_window_enable(void)
{
    DCI_CTL |= DCI_CTL_WDEN;
}

/*!
    \brief      disable cropping window function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_crop_window_disable(void)
{
    DCI_CTL &= ~DCI_CTL_WDEN;
}

/*!
    \brief      config DCI cropping window 
    \param[in]  start_x: window horizontal start position
    \param[in]  start_y: window vertical start position
    \param[in]  size_height: window horizontal size
    \param[in]  size_width: window vertical size
    \param[out] none
    \retval     none
*/
void dci_crop_window_config(uint16_t start_x, uint16_t start_y, uint16_t size_width, uint16_t size_height)
{
    DCI_CWSPOS = ((uint32_t)start_x | ((uint32_t)start_y<<16));
    DCI_CWSZ = ((uint32_t)size_width | ((uint32_t)size_height<<16));
}

/*!
    \brief      enable sync codes function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_sync_codes_enable(void)
{
    DCI_CTL |= DCI_CTL_ESM;
}

/*!
    \brief      disable sync codes function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dci_sync_codes_disable(void)
{
    DCI_CTL &= ~DCI_CTL_ESM;
}
/*!
    \brief      config sync codes 
    \param[in]  frame_start: frame start code in embedded synchronous mode
    \param[in]  line_start: line start code in embedded synchronous mode
    \param[in]  line_end: line end code in embedded synchronous mode
    \param[in]  frame_end: frame end code in embedded synchronous mode
    \param[out] none
    \retval     none
*/
void dci_sync_codes_config(uint8_t frame_start, uint8_t line_start, uint8_t line_end, uint8_t frame_end)
{
    DCI_SC = ((uint32_t)frame_start | ((uint32_t)line_start<<8) | ((uint32_t)line_end<<16) | ((uint32_t)frame_end<<24));
}

/*!
    \brief      config sync codes unmask
    \param[in]  frame_start: frame start code unmask bits in embedded synchronous mode
    \param[in]  line_start: line start code unmask bits in embedded synchronous mode
    \param[in]  line_end: line end code unmask bits in embedded synchronous mode
    \param[in]  frame_end: frame end code unmask bits in embedded synchronous mode
    \param[out] none
    \retval     none
*/
void dci_sync_codes_unmask_config(uint8_t frame_start, uint8_t line_start, uint8_t line_end, uint8_t frame_end)
{
    DCI_SCUMSK = ((uint32_t)frame_start | ((uint32_t)line_start<<8) | ((uint32_t)line_end<<16) | ((uint32_t)frame_end<<24));	
}

/*!
    \brief      read DCI data register
    \param[in]  none
    \param[out] none
    \retval     data
*/
uint32_t dci_data_read(void)
{
    return DCI_DATA;
}

/*!
    \brief      enable specified DCI interrupt
    \param[in]  interrupt:
      \arg         DCI_INT_EF: end of frame interrupt
      \arg         DCI_INT_OVR: FIFO overrun interrupt
      \arg         DCI_INT_ESE: embedded synchronous error interrupt 
      \arg         DCI_INT_VS: vsync interrupt
      \arg         DCI_INT_EL: end of line interrupt
    \param[out] none
    \retval     none
*/
void dci_interrupt_enable(uint32_t interrupt)
{
    DCI_INTEN |= interrupt;
}

/*!
    \brief      disable specified DCI interrupt
    \param[in]  interrupt:
      \arg         DCI_INT_EF: end of frame interrupt
      \arg         DCI_INT_OVR: FIFO overrun interrupt
      \arg         DCI_INT_ESE: embedded synchronous error interrupt 
      \arg         DCI_INT_VS: vsync interrupt
      \arg         DCI_INT_EL: end of line interrupt
    \param[out] none
    \retval     none
*/
void dci_interrupt_disable(uint32_t interrupt)
{
    DCI_INTEN &= ~interrupt;
}

/*!
    \brief      clear specified interrupt
    \param[in]  interrupt:
      \arg         DCI_INT_EF: end of frame interrupt
      \arg         DCI_INT_OVR: FIFO overrun interrupt
      \arg         DCI_INT_ESE: embedded synchronous error interrupt 
      \arg         DCI_INT_VS: vsync interrupt
      \arg         DCI_INT_EL: end of line interrupt
    \param[out] none
    \retval     none
*/
void dci_interrupt_clear(uint32_t interrupt)
{
    DCI_INTC |= interrupt;
}

/*!
    \brief      get specified flag
    \param[in]  flag:
      \arg         DCI_FLAG_HS: HS line status
      \arg         DCI_FLAG_VS: VS line status
      \arg         DCI_FLAG_FV:FIFO valid
      \arg         DCI_FLAG_EFF: end of frame flag
      \arg         DCI_FLAG_OVRF: FIFO overrun flag
      \arg         DCI_FLAG_ESEF: embedded synchronous error flag
      \arg         DCI_FLAG_VSF: vsync flag
      \arg         DCI_FLAG_ELF: end of line flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dci_flag_get(uint32_t flag)
{
    uint32_t ret = 0U;
    
    switch(flag){
    /* get flag status from DCI_STAT0 register */
    case DCI_FLAG_HS:
        ret = (DCI_STAT0 & DCI_STAT0_HS);
        break;
    case DCI_FLAG_VS:
        ret = (DCI_STAT0 & DCI_STAT0_VS);
        break;
    case DCI_FLAG_FV:
        ret = (DCI_STAT0 & DCI_STAT0_FV);
        break;
    /* get flag status from DCI_STAT1 register */
    case DCI_FLAG_EFF:
        ret = (DCI_STAT1 & DCI_STAT1_EFF);
        break;
    case DCI_FLAG_OVRF:
        ret = (DCI_STAT1 & DCI_STAT1_OVRF);
        break;
    case DCI_FLAG_ESEF:
        ret = (DCI_STAT1 & DCI_STAT1_ESEF);
        break;
    case DCI_FLAG_VSF:
        ret = (DCI_STAT1 & DCI_STAT1_VSF);
        break;
    case DCI_FLAG_ELF:
        ret = (DCI_STAT1 & DCI_STAT1_ELF);
        break;
    default :
        break;
    }
    
    if(RESET == ret){
        return RESET;
    }else{
        return SET;
    }
}

/*!
    \brief      get specified interrupt flag
    \param[in]  interrupt:
      \arg         DCI_INT_EF: end of frame interrupt
      \arg         DCI_INT_OVR: FIFO overrun interrupt
      \arg         DCI_INT_ESE: embedded synchronous error interrupt 
      \arg         DCI_INT_VS: vsync interrupt
      \arg         DCI_INT_EL: end of line interrupt
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dci_interrupt_flag_get(uint32_t interrupt)
{
    if(RESET == (DCI_INTF & interrupt)){
        return RESET;
    }else{
        return SET;
    }
}
