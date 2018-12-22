/*!
    \file  gd32f4xx_ipa.c
    \brief IPA driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_ipa.h"

/*!
    \brief      deinitialize IPA registers 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ipa_deinit(void)
{
    rcu_periph_reset_enable(RCU_IPAENRST);
    rcu_periph_reset_disable(RCU_IPAENRST);
}

/*!
    \brief      IPA transfer enable 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ipa_transfer_enable(void)
{
    IPA_CTL |= IPA_CTL_TEN;
}

/*!
    \brief      IPA transfer hang up enable
    \param[in]  none.
    \param[out] none
    \retval     none
*/
void ipa_transfer_hangup_enable(void)
{
    IPA_CTL |= IPA_CTL_THU;
}

/*!
    \brief      IPA transfer hang up disable
    \param[in]  none.
    \param[out] none
    \retval     none
*/
void ipa_transfer_hangup_disable(void)
{
    IPA_CTL &= ~(IPA_CTL_THU);
}

/*!
    \brief      IPA transfer stop enable 
    \param[in]  none.
    \param[out] none
    \retval     none
*/
void ipa_transfer_stop_enable(void)
{
    IPA_CTL |= IPA_CTL_TST;
}

/*!
    \brief      IPA transfer stop disable 
    \param[in]  none.
    \param[out] none
    \retval     none
*/
void ipa_transfer_stop_disable(void)
{
    IPA_CTL &= ~(IPA_CTL_TST);
}
/*!
    \brief      IPA foreground LUT loading enable 
    \param[in]  none.
    \param[out] none
    \retval     none
*/
void ipa_foreground_lut_loading_enable(void)
{
    IPA_FPCTL |= IPA_FPCTL_FLLEN;
}

/*!
    \brief      IPA background LUT loading enable 
    \param[in]  none.
    \param[out] none
    \retval     none
*/
void ipa_background_lut_loading_enable(void)
{
    IPA_BPCTL |= IPA_BPCTL_BLLEN;
}

/*!
    \brief      Pixel format convert mode 
    \param[in]  pfcm:
      \arg        IPA_FGTODE: foreground memory to destination memory without pixel format convert 
      \arg        IPA_FGTODE_PF_CONVERT: foreground memory to destination memory with pixel format convert 
      \arg        IPA_FGBGTODE: blending foreground and background memory to destination memory 
      \arg        IPA_FILL_UP_DE: fill up destination memory with specific color 
    \param[out] none
    \retval     none
*/
void ipa_pixel_format_convert_mod(uint32_t pfcm)
{
    IPA_CTL |= pfcm;
}

/*!
    \brief      initialize foreground parameters 
    \param[in]  foreground_struct: the data needed to initialize fore.
                  foreground_memaddr: foreground memory base address
                  foreground_lineoff: foreground line offset
                  foreground_prealpha: foreground pre-defined alpha value 
                  foreground_alpha_algorithm: IPA_FG_ALPHA_MODE_0,IPA_FG_ALPHA_MODE_1,IPA_FG_ALPHA_MODE_2
                  foreground_pf: foreground pixel format
                  foreground_prered: foreground pre-defined red value
                  foreground_pregreen: foreground pre-defined green value 
                  foreground_preblue: foreground pre-defined blue value
    \param[out] none
    \retval     none
*/
void ipa_foreground_init(ipa_foreground_parameter_struct* foreground_struct)
{
    /* foreground memory base address configuration */
    IPA_FMADDR &= ~(IPA_FMADDR_FMADDR);
    IPA_FMADDR = foreground_struct->foreground_memaddr;
    /* foreground line offset configuration */
    IPA_FLOFF &= ~(IPA_FLOFF_FLOFF);
    IPA_FLOFF = foreground_struct->foreground_lineoff;
    /* foreground pixel format pre-defined alpha, alpha calculation algorithm configuration */    
    IPA_FPCTL &= ~(IPA_FPCTL_FAVCA|IPA_FPCTL_FAVCA|IPA_FPCTL_FPF);
    IPA_FPCTL |= (foreground_struct->foreground_prealpha<<24U);
    IPA_FPCTL |= foreground_struct->foreground_alpha_algorithm;
    IPA_FPCTL |= foreground_struct->foreground_pf;
    /* foreground pre-defined red green blue configuration */    
    IPA_FPV &= ~(IPA_FPV_FPDRV|IPA_FPV_FPDGV|IPA_FPV_FPDBV);
    IPA_FPV |= ((foreground_struct->foreground_prered<<16U)|(foreground_struct->foreground_pregreen<<8U)|(foreground_struct->foreground_preblue));
}

/*!
    \brief      initialize background parameters 
    \param[in]  background_struct: the data needed to initialize fore.
                  background_memaddr: background memory base address
                  background_lineoff: background line offset
                  background_prealpha: background pre-defined alpha value 
                  background_alpha_algorithm: IPA_BG_ALPHA_MODE_0,IPA_FG_ALPHA_MODE_1,IPA_FG_ALPHA_MODE_2
                  background_pf: background pixel format
                  background_prered: background pre-defined red value
                  background_pregreen: background pre-defined green value 
                  background_preblue: background pre-defined blue value
    \param[out] none
    \retval     none
*/
void ipa_background_init(ipa_background_parameter_struct* background_struct)
{
    /* background memory base address configuration */
    IPA_BMADDR &= ~(IPA_BMADDR_BMADDR);
    IPA_BMADDR = background_struct->background_memaddr;
    /* background line offset configuration */
    IPA_BLOFF &= ~(IPA_BLOFF_BLOFF);
    IPA_BLOFF =background_struct->background_lineoff;
    /* background pixel format pre-defined alpha, alpha calculation algorithm configuration */    
    IPA_BPCTL &= ~(IPA_BPCTL_BAVCA|IPA_BPCTL_BAVCA|IPA_BPCTL_BPF);
    IPA_BPCTL |= (background_struct->background_prealpha<<24U);
    IPA_BPCTL |= background_struct->background_alpha_algorithm;
    IPA_BPCTL |= background_struct->background_pf; 
    /* background pre-defined red green blue configuration */  
    IPA_BPV &= ~(IPA_BPV_BPDRV|IPA_BPV_BPDGV|IPA_BPV_BPDBV);
    IPA_BPV |= ((background_struct->background_prered<<16U)|(background_struct->background_pregreen<<8U)|(background_struct->background_preblue));
}

/*!
    \brief      initialize destination parameters  
    \param[in]  destination_struct: the data needed to initialize tli.
                  destination_pf: refer to ipa_dpf_enum 
                  destination_lineoff: destination line offset
                  destination_prealpha: destination pre-defined alpha value 
                  destination_prered: destination pre-defined red value
                  destination_pregreen: destination pre-defined green value
                  destination_preblue: destination pre-defined blue value
                  destination_memaddr: destination memory base address 
                  image_width: width of the image to be processed
                  image_height: height of the image to be processed
    \param[out] none
    \retval     none
*/
void ipa_destination_init(ipa_destination_parameter_struct* destination_struct)
{
    uint32_t destination_pixelformat;
    /* destination pixel format configuration */
    IPA_DPCTL &= ~(IPA_DPCTL_DPF);
    IPA_DPCTL = destination_struct->destination_pf;
    destination_pixelformat = destination_struct->destination_pf;
    /* destination pixel format ARGB8888 */
    switch(destination_pixelformat){
    case IPA_DPF_ARGB8888:
        IPA_DPV &= ~(IPA_DPV_DPDBV_0|(IPA_DPV_DPDGV_0)|(IPA_DPV_DPDRV_0)|(IPA_DPV_DPDAV_0));
        IPA_DPV = (destination_struct->destination_preblue|(destination_struct->destination_pregreen<<8U)
                                                            |(destination_struct->destination_prered<<16U)
                                                            |(destination_struct->destination_prealpha<<24U));
        break;
    /* destination pixel format RGB888 */
    case IPA_DPF_RGB888:
        IPA_DPV &= ~(IPA_DPV_DPDBV_1|(IPA_DPV_DPDGV_1)|(IPA_DPV_DPDRV_1));
        IPA_DPV = (destination_struct->destination_preblue|(destination_struct->destination_pregreen<<8U)
                                                            |(destination_struct->destination_prered<<16U));
        break;
    /* destination pixel format RGB565 */
    case IPA_DPF_RGB565:
        IPA_DPV &= ~(IPA_DPV_DPDBV_2|(IPA_DPV_DPDGV_2)|(IPA_DPV_DPDRV_2));
        IPA_DPV = (destination_struct->destination_preblue|(destination_struct->destination_pregreen<<5U)
                                                            |(destination_struct->destination_prered<<11U));
        break;
    /* destination pixel format ARGB1555 */
    case IPA_DPF_ARGB1555:
        IPA_DPV &= ~(IPA_DPV_DPDBV_3|(IPA_DPV_DPDGV_3)|(IPA_DPV_DPDRV_3)|(IPA_DPV_DPDAV_3));
        IPA_DPV = (destination_struct->destination_preblue|(destination_struct->destination_pregreen<<5U)
                                                            |(destination_struct->destination_prered<<10U)
                                                            |(destination_struct->destination_prealpha<<15U));
        break;
    /* destination pixel format ARGB4444 */
    case IPA_DPF_ARGB4444:
        IPA_DPV &= ~(IPA_DPV_DPDBV_4|(IPA_DPV_DPDGV_4)|(IPA_DPV_DPDRV_4)|(IPA_DPV_DPDAV_4));
        IPA_DPV = (destination_struct->destination_preblue|(destination_struct->destination_pregreen<<5U)
                                                            |(destination_struct->destination_prered<<10U)
                                                            |(destination_struct->destination_prealpha<<15U));
        break;
    default:
        break;
    }
    /* destination memory base address configuration */
    IPA_DMADDR &= ~(IPA_DMADDR_DMADDR);
    IPA_DMADDR =destination_struct->destination_memaddr;
    /* destination line offset configuration */    
    IPA_DLOFF &= ~(IPA_DLOFF_DLOFF);
    IPA_DLOFF =destination_struct->destination_lineoff;
    /* image size configuration */    
    IPA_IMS &= ~(IPA_IMS_HEIGHT|IPA_IMS_WIDTH);
    IPA_IMS |= ((destination_struct->image_width<<16)|(destination_struct->image_height));
}

/*!
    \brief      initialize IPA foreground LUT parameters  
    \param[in]  fg_lut_num: foreground LUT number of pixel.
    \param[in]  fg_lut_pf: foreground LUT pixel format,IPA_LUT_PF_ARGB8888,IPA_LUT_PF_RGB888.
    \param[in]  fg_lut_addr: foreground LUT memory base address.
    \param[out] none
    \retval     none
*/
void ipa_foreground_lut_init(uint32_t fg_lut_num,uint8_t fg_lut_pf, uint32_t fg_lut_addr)
{
    /* foreground LUT number of pixel configuration */
    IPA_FPCTL |= (fg_lut_num<<8U);
    /* foreground LUT pixel format configuration */
    if(IPA_LUT_PF_RGB888 == fg_lut_pf){
        IPA_FPCTL |= IPA_FPCTL_FLPF;
    }else{
        IPA_FPCTL &= ~(IPA_FPCTL_FLPF);
    }
    /* foreground LUT memory base address configuration */
    IPA_FLMADDR &= ~(IPA_FLMADDR_FLMADDR);
    IPA_FLMADDR = fg_lut_addr;
}

/*!
    \brief      initialize IPA background LUT parameters  
    \param[in]  bg_lut_num: background LUT number of pixel.
    \param[in]  bg_lut_pf: background LUT pixel format, IPA_LUT_PF_ARGB8888,IPA_LUT_PF_RGB888.
    \param[in]  bg_lut_addr: background LUT memory base address.
    \param[out] none
    \retval     none
*/
void ipa_background_lut_init(uint32_t bg_lut_num,uint8_t bg_lut_pf, uint32_t bg_lut_addr)
{
    /* background LUT number of pixel configuration */
    IPA_BPCTL|=(bg_lut_num<<8U);
    /* background LUT pixel format configuration */
    if(IPA_LUT_PF_RGB888 == bg_lut_pf){
        IPA_BPCTL |= IPA_BPCTL_BLPF;
    }else{
        IPA_BPCTL &= ~(IPA_BPCTL_BLPF);
    }
    /* background LUT memory base address configuration */
    IPA_BLMADDR &= ~(IPA_BLMADDR_BLMADDR);
    IPA_BLMADDR = bg_lut_addr;
}

/*!
    \brief      configure line mark 
    \param[in]  linenum: line number.
    \param[out] none
    \retval     none
*/
void ipa_line_mark_config(uint32_t linenum)
{
    IPA_LM &= ~(IPA_LM_LM);
    IPA_LM = linenum;
}

/*!
    \brief      Inter-timer enable or disable 
    \param[in]  timercfg: IPA_INTER_TIMER_ENABLE,IPA_INTER_TIMER_DISABLE
    \param[out] none
    \retval     none
*/
void ipa_inter_timer_config(uint8_t timercfg)
{
    if(IPA_INTER_TIMER_ENABLE == timercfg){
        IPA_ITCTL |= IPA_ITCTL_ITEN;
    }else{
        IPA_ITCTL &= ~(IPA_ITCTL_ITEN);
    }
}

/*!
    \brief      number of clock cycles interval set 
    \param[in]  clk_num: the number of clock cycles.
    \param[out] none
    \retval     none
*/
void ipa_interval_clock_num_config(uint32_t clk_num )
{
    IPA_ITCTL &= ~(IPA_ITCTL_NCCI);
    IPA_ITCTL |= (clk_num<<8U);
}

/*!
    \brief      IPA interrupt enable 
    \param[in]  inttype: IPA interrupt bits.
      \arg        IPA_CTL_TAEIE: transfer access error interrupt 
      \arg        IPA_CTL_FTFIE: full transfer finish interrupt 
      \arg        IPA_CTL_TLMIE: transfer line mark interrupt   
      \arg        IPA_CTL_LACIE: LUT access conflict interrupt 
      \arg        IPA_CTL_LLFIE: LUT loading finish interrupt
      \arg        IPA_CTL_WCFIE: wrong configuration interrupt 
    \param[out] none
    \retval     none
*/
void ipa_interrupt_enable(uint32_t inttype)
{
    IPA_CTL |= (inttype);
}

/*!
    \brief      IPA interrupt disable 
    \param[in]  inttype: IPA interrupt bits.
      \arg        IPA_CTL_TAEIE: transfer access error interrupt 
      \arg        IPA_CTL_FTFIE: full transfer finish interrupt 
      \arg        IPA_CTL_TLMIE: transfer line mark interrupt   
      \arg        IPA_CTL_LACIE: LUT access conflict interrupt 
      \arg        IPA_CTL_LLFIE: LUT loading finish interrupt
      \arg        IPA_CTL_WCFIE: wrong configuration interrupt 
    \param[out] none
    \retval     none
*/
void ipa_interrupt_disable(uint32_t inttype)
{
    IPA_CTL &= ~(inttype);
}

/*!
    \brief      get IPA interrupt flag 
    \param[in]  intflag: tli interrupt flag bits.
      \arg        IPA_INTF_TAEIF: transfer access error interrupt flag 
      \arg        IPA_INTF_FTFIF: full transfer finish interrupt flag 
      \arg        IPA_INTF_TLMIF: transfer line mark interrupt flag
      \arg        IPA_INTF_LACIF: LUT access conflict interrupt flag 
      \arg        IPA_INTF_LLFIF: LUT loading finish interrupt flag 
      \arg        IPA_INTF_WCFIF: wrong configuration interrupt flag 
    \param[out] none
    \retval     none
*/
FlagStatus ipa_interrupt_flag_get(uint32_t intflag)
{
    uint32_t state;
    state = IPA_INTF;
    if(state & intflag){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear IPA interrupt flag 
    \param[in]  intflag: tli interrupt flag bits.
      \arg        IPA_INTC_TAEIFC: transfer access error interrupt flag 
      \arg        IPA_INTC_FTFIFC: full transfer finish interrupt flag 
      \arg        IPA_INTC_TLMIFC: transfer line mark interrupt flag
      \arg        IPA_INTC_LACIFC: LUT access conflict interrupt flag 
      \arg        IPA_INTC_LLFIFC: LUT loading finish interrupt flag 
      \arg        IPA_INTC_WCFIFC: wrong configuration interrupt flag 
    \param[out] none
    \retval     none
*/
void ipa_interrupt_flag_clear(uint32_t intflag)
{
    IPA_INTC |= (intflag);
}

