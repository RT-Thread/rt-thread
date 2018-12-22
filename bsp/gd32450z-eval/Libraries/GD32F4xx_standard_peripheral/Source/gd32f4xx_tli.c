/*!
    \file  gd32f4xx_tli.c
    \brief TLI driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.1, firmware for GD32F4xx
*/

#include "gd32f4xx_tli.h"

/*!
    \brief      deinitialize TLI registers 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tli_deinit(void)
{
    rcu_periph_reset_enable(RCU_TLIRST);
    rcu_periph_reset_disable(RCU_TLIRST);
}

/*!
    \brief      initialize TLI display timing parameters 
    \param[in]  tli_struct: the data needed to initialize tli.
                  synpsz_vpsz: size of the vertical synchronous pulse
                  synpsz_hpsz: size of the horizontal synchronous pulse
                  backpsz_vbpsz: size of the vertical back porch plus synchronous pulse 
                  backpsz_hbpsz: size of the horizontal back porch plus synchronous pulse
                  activesz_vasz: size of the vertical active area width plus back porch and synchronous pulse
                  activesz_hasz: size of the horizontal active area width plus back porch and synchronous pulse
                  totalsz_vtsz: vertical total size of the display, including active area, back porch, synchronous 
                  totalsz_htsz: vorizontal total size of the display, including active area, back porch, synchronous
                  backcolor_red: background value red
                  backcolor_green: background value green
                  backcolor_blue: background value blue
                  signalpolarity_hs: TLI_HSYN_ACTLIVE_LOW,TLI_HSYN_ACTLIVE_HIGHT
                  signalpolarity_vs: TLI_VSYN_ACTLIVE_LOW,TLI_VSYN_ACTLIVE_HIGHT
                  signalpolarity_de: TLI_DE_ACTLIVE_LOW,TLI_DE_ACTLIVE_HIGHT
                  signalpolarity_pixelck: TLI_PIXEL_CLOCK_TLI,TLI_PIXEL_CLOCK_INVERTEDTLI
    \param[out] none
    \retval     none
*/
void tli_init(tli_parameter_struct *tli_struct)
{
    /* synchronous pulse size configuration */
    TLI_SPSZ &= ~(TLI_SPSZ_VPSZ|TLI_SPSZ_HPSZ);
    TLI_SPSZ = (tli_struct->synpsz_vpsz|(tli_struct->synpsz_hpsz<<16U));
    /* back-porch size configuration */
    TLI_BPSZ &= ~(TLI_BPSZ_VBPSZ|TLI_BPSZ_HBPSZ);
    TLI_BPSZ = (tli_struct->backpsz_vbpsz|(tli_struct->backpsz_hbpsz<<16U));
    /* active size configuration */    
    TLI_ASZ &= ~(TLI_ASZ_VASZ|TLI_ASZ_HASZ);
    TLI_ASZ = (tli_struct->activesz_vasz|(tli_struct->activesz_hasz<<16U));
    /* total size configuration */    
    TLI_TSZ &= ~(TLI_TSZ_VTSZ|TLI_TSZ_HTSZ);
    TLI_TSZ = (tli_struct->totalsz_vtsz|(tli_struct->totalsz_htsz<<16U));
    /* background color configuration */    
    TLI_BGC &= ~(TLI_BGC_BVB|(TLI_BGC_BVG)|(TLI_BGC_BVR));
    TLI_BGC = (tli_struct->backcolor_blue|(tli_struct->backcolor_green<<8U)|(tli_struct->backcolor_red<<16U));    
    TLI_CTL &= ~(TLI_CTL_HPPS|TLI_CTL_VPPS|TLI_CTL_DEPS|TLI_CTL_CLKPS);
    TLI_CTL |= (tli_struct->signalpolarity_hs|tli_struct->signalpolarity_vs|\
                tli_struct->signalpolarity_de|tli_struct->signalpolarity_pixelck);

}

/*!
    \brief      dither function configure 
    \param[in]  ditherstat: TLI_DITHER_ENABLE,TLI_DITHER_DISABLE
    \param[out] none
    \retval     none
*/
void tli_dither_config(uint8_t ditherstat)
{
    if(TLI_DITHER_ENABLE == ditherstat){
        TLI_CTL |= TLI_CTL_DFEN;
    }else{
        TLI_CTL &= ~(TLI_CTL_DFEN);
    }
}

/*!
    \brief      TLI enable 
    \param[in]  none.
    \param[out] none
    \retval     none
*/
void tli_enable(void)
{
    TLI_CTL |= TLI_CTL_TLIEN;
}

/*!
    \brief      TLI disable 
    \param[in]  none.
    \param[out] none
    \retval     none
*/
void tli_disable(void)
{
    TLI_CTL &= ~(TLI_CTL_DFEN);
}

/*!
    \brief      TLI reload layer configure 
    \param[in]  reloadmod: TLI_FRAME_BLANK_RELOAD_EN,TLI_REQUEST_RELOAD_EN
    \param[out] none
    \retval     none
*/
void tli_reload_config(uint8_t reloadmod)
{
    if(TLI_FRAME_BLANK_RELOAD_EN == reloadmod){
        TLI_RL |= TLI_RL_FBR;
    }else{
        TLI_RL |= TLI_RL_RQR;
    }
}

/*!
    \brief      TLI interrupt enable 
    \param[in]  inttype: TLI interrupt bits.
      \arg        TLI_INTEN_LMIE: line mark interrupt 
      \arg        TLI_INTEN_FEIE: FIFO error interrupt  
      \arg        TLI_INTEN_TEIE: transaction error interrupt   
      \arg        TLI_INTEN_LCRIE: layer configuration reloaded interrupt 
    \param[out] none
    \retval     none
*/
void tli_interrupt_enable(uint32_t inttype)
{
    TLI_INTEN |= (inttype);
}

/*!
    \brief      TLI interrupt disable 
    \param[in]  inttype: TLI interrupt bits.
      \arg        TLI_INTEN_LMIE: line mark interrupt 
      \arg        TLI_INTEN_FEIE: FIFO error interrupt  
      \arg        TLI_INTEN_TEIE: transaction error interrupt   
      \arg        TLI_INTEN_LCRIE: layer configuration reloaded interrupt 
    \param[out] none
    \retval     none
*/
void tli_interrupt_disable(uint32_t inttype)
{
    TLI_INTEN &= ~(inttype);
}

/*!
    \brief      get TLI interrupt flag 
    \param[in]  intflag: TLI interrupt flag bits.
      \arg        TLI_INTF_LMF: line mark flag 
      \arg        TLI_INTF_FEF: FIFO error flag  
      \arg        TLI_INTF_TEF: transaction error flag   
      \arg        TLI_INTF_LCRF: layer configuration reloaded flag 
    \param[out] none
    \retval     none
*/
FlagStatus tli_interrupt_flag_get(uint32_t intflag)
{
    uint32_t state;
    state = TLI_INTF;
    if(state & intflag){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear TLI interrupt flag 
    \param[in]  intflag: TLI interrupt flag bits.
      \arg        TLI_INTC_LMC: line mark flag 
      \arg        TLI_INTC_FEC: FIFO error flag  
      \arg        TLI_INTC_TEC: transaction error flag   
      \arg        TLI_INTC_LCRC: layer configuration reloaded flag 
    \param[out] none
    \retval     none
*/
void tli_interrupt_flag_clear(uint32_t intflag)
{
    TLI_INTC |= (intflag);
}

/*!
    \brief      set line mark value 
    \param[in]  linenum: line number. 
    \param[out] none
    \retval     none
*/
void tli_line_mark_set(uint32_t linenum)
{
    TLI_LM &= ~(TLI_LM_LM);
    TLI_LM = linenum;
}

/*!
    \brief      get current displayed position 
    \param[in]  none 
    \param[out] none
    \retval     none
*/
uint32_t tli_current_pos_get(void)
{
    return TLI_CPPOS;
}


/*!
    \brief      get TLI state 
    \param[in]  state: TLI state.
      \arg        TLI_STAT_VDE: current VDE state 
      \arg        TLI_STAT_HDE: current HDE state
      \arg        TLI_STAT_VS: current vs state
      \arg        TLI_STAT_HS: current hs state 
    \param[out] none
    \retval     none
*/
FlagStatus tli_flag_get(uint32_t state)
{
    uint32_t stat;
    stat = TLI_STAT;
    if(state & stat){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      TLI layer enable 
    \param[in]  layerx: LAYERx(x=0,1).
    \param[out] none
    \retval     none
*/
void tli_layer_enable(uint32_t layerx)
{
    TLI_LxCTL(layerx) |= TLI_LxCTL_LEN;
}

/*!
    \brief      TLI layer disable 
    \param[in]  layerx: LAYERx(x=0,1).
    \param[out] none
    \retval     none
*/
void tli_layer_disable(uint32_t layerx)
{
    TLI_LxCTL(layerx) &= ~(TLI_LxCTL_LEN);
}

/*!
    \brief      TLI layer color keying enable 
    \param[in]  layerx: LAYERx(x=0,1).
    \param[out] none
    \retval     none
*/
void tli_color_key_enable(uint32_t layerx)
{
    TLI_LxCTL(layerx) |= TLI_LxCTL_CKEYEN;
}

/*!
    \brief      TLI layer color keying disable 
    \param[in]  layerx: LAYERx(x=0,1).
    \param[out] none
    \retval     none
*/
void tli_color_key_disable(uint32_t layerx)
{
    TLI_LxCTL(layerx) &= ~(TLI_LxCTL_CKEYEN);
}

/*!
    \brief      TLI layer LUT enable 
    \param[in]  layerx: LAYERx(x=0,1).
    \param[out] none
    \retval     none
*/
void tli_lut_enable(uint32_t layerx)
{
    TLI_LxCTL(layerx) |= TLI_LxCTL_LUTEN;
}

/*!
    \brief      TLI layer LUT disable 
    \param[in]  layerx: LAYERx(x=0,1).
    \param[out] none
    \retval     none
*/
void tli_lut_disable(uint32_t layerx)
{
    TLI_LxCTL(layerx) &= ~(TLI_LxCTL_LUTEN);
}

/*!
    \brief      TLI layer initialize 
    \param[in]  layerx: LAYERx(x=0,1)
    \param[in]  layer_struct: TLI Layer parameter struct
                  layer_window_rightpos: window right position
                  layer_window_leftpos: window left position
                  layer_window_bottompos: window bottom position 
                  layer_window_toppos: window top position
                  layer_ppf: LAYER_PPF_ARGB8888,LAYER_PPF_RGB888,LAYER_PPF_RGB565,
                                 LAYER_PPF_ARG1555,LAYER_PPF_ARGB4444,LAYER_PPF_L8,
                                 LAYER_PPF_AL44,LAYER_PPF_AL88
                  layer_sa: specified alpha
                  layer_default_alpha: the default color alpha
                  layer_default_red: the default color red
                  layer_default_green: the default color green
                  layer_default_blue: the default color blue
                  layer_acf1: LAYER_ACF1_SA,LAYER_ACF1_PASA
                  layer_acf2: LAYER_ACF2_SA,LAYER_ACF2_PASA
                  layer_frame_bufaddr: frame buffer base address
                  layer_frame_buf_stride_offset: frame buffer stride offset
                  layer_frame_line_length: frame line length
                  layer_frame_total_line_number: frame total line number
    \param[out] none
    \retval     none
*/
void tli_layer_init(uint32_t layerx,tli_layer_parameter_struct *layer_struct)
{
    /* configure layer window horizontal position */
    TLI_LxHPOS(layerx) &= ~(TLI_LxHPOS_WLP|(TLI_LxHPOS_WRP));
    TLI_LxHPOS(layerx) = (layer_struct->layer_window_leftpos | (layer_struct->layer_window_rightpos<<16U));
    /* configure layer window vertical position */
    TLI_LxVPOS(layerx) &= ~(TLI_LxVPOS_WTP|(TLI_LxVPOS_WBP));
    TLI_LxVPOS(layerx) = (layer_struct->layer_window_toppos |(layer_struct->layer_window_bottompos<<16U));
    /* configure layer packeted pixel format */
    TLI_LxPPF(layerx) &= ~(TLI_LxPPF_PPF);
    TLI_LxPPF(layerx) = layer_struct->layer_ppf;
    /* configure layer specified alpha */
    TLI_LxSA(layerx) &= ~(TLI_LxSA_SA);
    TLI_LxSA(layerx) = layer_struct->layer_sa;
    /* configure layer default color */
    TLI_LxDC(layerx) &= ~(TLI_LxDC_DCB|(TLI_LxDC_DCG)|(TLI_LxDC_DCR)|(TLI_LxDC_DCA));
    TLI_LxDC(layerx) = (layer_struct->layer_default_blue |(layer_struct->layer_default_green<<8U)
                                                               |(layer_struct->layer_default_red<<16U)
                                                               |(layer_struct->layer_default_alpha<<24U));

    /* configure layer alpha calculation factors */
    TLI_LxBLEND(layerx) &= ~(TLI_LxBLEND_ACF2|(TLI_LxBLEND_ACF1));
    TLI_LxBLEND(layerx) = ((layer_struct->layer_acf2)|(layer_struct->layer_acf1));
    /* configure layer frame buffer base address */
    TLI_LxFBADDR(layerx) &= ~(TLI_LxFBADDR_FBADD);
    TLI_LxFBADDR(layerx) = (layer_struct->layer_frame_bufaddr);
    /* configure layer frame line length */
    TLI_LxFLLEN(layerx) &= ~(TLI_LxFLLEN_FLL|(TLI_LxFLLEN_STDOFF));
    TLI_LxFLLEN(layerx) = (layer_struct->layer_frame_line_length|(layer_struct->layer_frame_buf_stride_offset<<16U));
    /* configure layer frame buffer base address */
    TLI_LxFBADDR(layerx) &= ~(TLI_LxFBADDR_FBADD);
    TLI_LxFBADDR(layerx) = (layer_struct->layer_frame_bufaddr);
    /* configure layer frame total line number */
    TLI_LxFTLN(layerx) &= ~(TLI_LxFTLN_FTLN); 
    TLI_LxFTLN(layerx) = (layer_struct->layer_frame_total_line_number);

}

/*!
    \brief      reconfigure window position 
    \param[in]  layerx: LAYERx(x=0,1).
    \param[in]  offset_x: new horizontal offset .
    \param[in]  offset_y: new vertical offset.
    \param[out] none
    \retval     none
*/
void tli_layer_window_offset_modify(uint32_t layerx,uint32_t offset_x,uint32_t offset_y)
{
    /* configure window start position */
    uint32_t layer_ppf,line_length,line_num,hstart,vstart;
    TLI_LxHPOS(layerx) &= ~(TLI_LxHPOS_WLP|(TLI_LxHPOS_WRP));
    TLI_LxVPOS(layerx) &= ~(TLI_LxVPOS_WTP|(TLI_LxVPOS_WBP));
    hstart = offset_x+(((TLI_BPSZ & TLI_BPSZ_HBPSZ)>>16U)+1U);
    vstart = offset_y+((TLI_BPSZ & TLI_BPSZ_VBPSZ)+1U);
    line_num = (TLI_LxFTLN(layerx) & TLI_LxFTLN_FTLN);
    layer_ppf = (TLI_LxPPF(layerx) & TLI_LxPPF_PPF);
    /* the bytes of a line equal TLI_LxFLLEN_FLL bits value minus 3 */
    switch(layer_ppf){
    case LAYER_PPF_ARGB8888:
        /* each pixel includes 4bytes,when pixel format is ARGB8888 */
        line_length = (((TLI_LxFLLEN(layerx) & TLI_LxFLLEN_FLL)-3U)/4U);
        break;
    case LAYER_PPF_RGB888:
        /* each pixel includes 3bytes,when pixel format is RGB888 */
        line_length = (((TLI_LxFLLEN(layerx) & TLI_LxFLLEN_FLL)-3U)/3U);
        break;
    case LAYER_PPF_RGB565:
    case LAYER_PPF_ARGB1555:
    case LAYER_PPF_ARGB4444:
    case LAYER_PPF_AL88:
        /* each pixel includes 2bytes,when pixel format is RGB565,ARG1555,ARGB4444 or AL88 */
        line_length = (((TLI_LxFLLEN(layerx) & TLI_LxFLLEN_FLL)-3U)/2U);
        break;
    case LAYER_PPF_L8:
    case LAYER_PPF_AL44:
        /* each pixel includes 1byte,when pixel format is L8 or AL44 */
        line_length = (((TLI_LxFLLEN(layerx) & TLI_LxFLLEN_FLL)-3U));
        break;
    default:
        break;
    }
    /* reconfigure window position */
    TLI_LxHPOS(layerx) = (hstart|((hstart+line_length-1U)<<16U));
    TLI_LxVPOS(layerx) = (vstart|((vstart+line_num-1U)<<16U));
    
    
}

/*!
    \brief      TLI layer lut initialize 
    \param[in]  layerx: LAYERx(x=0,1)
    \param[in]  lut_struct: TLI layer LUT parameter struct
                  layer_table_addr: window right position
                  layer_lut_channel_red: window left position
                  layer_window_bottompos: window bottom position 
                  layer_window_toppos: window top position
    \param[out] none
    \retval     none
*/
void tli_lut_init(uint32_t layerx,tli_layer_lut_parameter_struct *lut_struct)
{
    TLI_LxLUT(layerx) &= ~(TLI_LxLUT_TB|TLI_LxLUT_TG|TLI_LxLUT_TR|TLI_LxLUT_TADD);
    TLI_LxLUT(layerx) = ((lut_struct->layer_lut_channel_blue)|(lut_struct->layer_lut_channel_green<<8)
                                                                   |(lut_struct->layer_lut_channel_red<<16
                                                                   |(lut_struct->layer_table_addr<<24)));
}

/*!
    \brief      TLI layer key initialize 
    \param[in]  layerx: LAYERx(x=0,1).
    \param[in]  redkey: color key red.
    \param[in]  greenkey: color key green 
    \param[in]  bluekey: color key blue.
    \param[out] none
    \retval     none
*/
void tli_ckey_init(uint32_t layerx,uint32_t redkey,uint32_t greenkey,uint32_t bluekey)
{
    TLI_LxCKEY(layerx) = ((bluekey)|(greenkey<<8U)|(redkey<<16U));
}
