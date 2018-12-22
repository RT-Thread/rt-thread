/*!
    \file  gd32f4xx_tli.h
    \brief definitions for the TLI
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.1, firmware for GD32F4xx
*/

#ifndef GD32F4XX_TLI_H
#define GD32F4XX_TLI_H

#include "gd32f4xx.h"

/* TLI definitions */
#define TLI                               TLI_BASE               /*!< TLI base address */
/* TLI layer definitions */
#define LAYER0                            TLI_BASE               /*!< Layer0 base address */
#define LAYER1                            (TLI_BASE+0x80)        /*!< Layer1 base address */

/* registers definitions */
#define TLI_SPSZ                          REG32(TLI + 0x08U)          /*!< TLI synchronous pulse size register */
#define TLI_BPSZ                          REG32(TLI + 0x0CU)          /*!< TLI back-porch size register */
#define TLI_ASZ                           REG32(TLI + 0x10U)          /*!< TLI active size register */
#define TLI_TSZ                           REG32(TLI + 0x14U)          /*!< TLI total size register */
#define TLI_CTL                           REG32(TLI + 0x18U)          /*!< TLI control register */
#define TLI_RL                            REG32(TLI + 0x24U)          /*!< TLI reload Layer register */
#define TLI_BGC                           REG32(TLI + 0x2CU)          /*!< TLI background color register */
#define TLI_INTEN                         REG32(TLI + 0x34U)          /*!< TLI interrupt enable register */
#define TLI_INTF                          REG32(TLI + 0x38U)          /*!< TLI interrupt flag register */
#define TLI_INTC                          REG32(TLI + 0x3CU)          /*!< TLI interrupt flag clear register */
#define TLI_LM                            REG32(TLI + 0x40U)          /*!< TLI line mark register */
#define TLI_CPPOS                         REG32(TLI + 0x44U)          /*!< TLI current pixel position register */
#define TLI_STAT                          REG32(TLI + 0x48U)          /*!< TLI status register */
#define TLI_LxCTL(layerx)                 REG32((layerx) + 0x84U)     /*!< TLI layer x control register */
#define TLI_LxHPOS(layerx)                REG32((layerx) + 0x88U)     /*!< TLI layer x horizontal position parameters register */
#define TLI_LxVPOS(layerx)                REG32((layerx) + 0x8CU)     /*!< TLI layer x vertical position parameters register */
#define TLI_LxCKEY(layerx)                REG32((layerx) + 0x90U)     /*!< TLI layer x color key register */
#define TLI_LxPPF(layerx)                 REG32((layerx) + 0x94U)     /*!< TLI layer x packeted pixel format register */
#define TLI_LxSA(layerx)                  REG32((layerx) + 0x98U)     /*!< TLI layer x specified alpha register */
#define TLI_LxDC(layerx)                  REG32((layerx) + 0x9CU)     /*!< TLI layer x default color register */
#define TLI_LxBLEND(layerx)               REG32((layerx) + 0xA0U)     /*!< TLI layer x blending register */
#define TLI_LxFBADDR(layerx)              REG32((layerx) + 0xACU)     /*!< TLI layer x frame base address register */
#define TLI_LxFLLEN(layerx)               REG32((layerx) + 0xB0U)     /*!< TLI layer x frame line length register */
#define TLI_LxFTLN(layerx)                REG32((layerx) + 0xB4U)     /*!< TLI layer x frame total line number register */
#define TLI_LxLUT(layerx)                 REG32((layerx) + 0xC4U)     /*!< TLI ayer x Look Up Table register */


/* bits definitions */
/* TLI_SPSZ */
#define TLI_SPSZ_VPSZ                     BITS(0,11)       /*!< size of the vertical synchronous pulse */
#define TLI_SPSZ_HPSZ                     BITS(16,27)      /*!< size of the horizontal synchronous pulse */

/* TLI_BPSZ */
#define TLI_BPSZ_VBPSZ                    BITS(0,11)       /*!< size of the vertical back porch plus synchronous pulse */
#define TLI_BPSZ_HBPSZ                    BITS(16,27)      /*!< size of the horizontal back porch plus synchronous pulse */

/* TLI_ASZ */
#define TLI_ASZ_VASZ                      BITS(0,11)       /*!< size of the vertical active area width plus back porch and synchronous pulse */
#define TLI_ASZ_HASZ                      BITS(16,27)      /*!< size of the horizontal active area width plus back porch and synchronous pulse */

/* TLI_SPSZ */
#define TLI_TSZ_VTSZ                      BITS(0,11)       /*!< vertical total size of the display, including active area, back porch, synchronous pulse and front porch */
#define TLI_TSZ_HTSZ                      BITS(16,27)      /*!< horizontal total size of the display, including active area, back porch, synchronous pulse and front porch */

/* TLI_CTL */
#define TLI_CTL_TLIEN                     BIT(0)           /*!< TLI enable bit */
#define TLI_CTL_BDB                       BITS(4,6)        /*!< blue channel dither bits number */
#define TLI_CTL_GDB                       BITS(8,10)       /*!< green channel dither bits number */
#define TLI_CTL_RDB                       BITS(12,14)      /*!< red channel dither bits number */
#define TLI_CTL_DFEN                      BIT(16)          /*!< dither function enable */
#define TLI_CTL_CLKPS                     BIT(28)          /*!< pixel clock polarity selection */
#define TLI_CTL_DEPS                      BIT(29)          /*!< data enable polarity selection */
#define TLI_CTL_VPPS                      BIT(30)          /*!< vertical pulse polarity selection */
#define TLI_CTL_HPPS                      BIT(31)          /*!< horizontal pulse polarity selection */

/* TLI_RL */
#define TLI_RL_RQR                        BIT(0)           /*!< request reload */
#define TLI_RL_FBR                        BIT(1)           /*!< frame blank reload */

/* TLI_BGC */
#define TLI_BGC_BVB                       BITS(0,7)        /*!< background value blue */
#define TLI_BGC_BVG                       BITS(8,15)       /*!< background value green */
#define TLI_BGC_BVR                       BITS(16,23)      /*!< background value red */

/* TLI_INTEN */
#define TLI_INTEN_LMIE                    BIT(0)           /*!< line mark interrupt enable */
#define TLI_INTEN_FEIE                    BIT(1)           /*!< FIFO error interrupt enable */
#define TLI_INTEN_TEIE                    BIT(2)           /*!< transaction error interrupt enable */
#define TLI_INTEN_LCRIE                   BIT(3)           /*!< layer configuration reloaded interrupt enable */

/* TLI_INTF */
#define TLI_INTF_LMF                      BIT(0)           /*!< line mark flag */
#define TLI_INTF_FEF                      BIT(1)           /*!< FIFO error flag */
#define TLI_INTF_TEF                      BIT(2)           /*!< transaction error flag */
#define TLI_INTF_LCRF                     BIT(3)           /*!< layer configuration reloaded flag */

/* TLI_INTC */
#define TLI_INTC_LMC                      BIT(0)           /*!< line mark flag clear */
#define TLI_INTC_FEC                      BIT(1)           /*!< FIFO error flag clear */
#define TLI_INTC_TEC                      BIT(2)           /*!< transaction error flag clear */
#define TLI_INTC_LCRC                     BIT(3)           /*!< layer configuration reloaded flag clear */

/* TLI_LM */
#define TLI_LM_LM                         BITS(0,10)       /*!< line mark value */

/* TLI_CPPOS */
#define TLI_CPPOS_VPOS                    BITS(0,15)       /*!< vertical position */
#define TLI_CPPOS_HPOS                    BITS(16,31)      /*!< horizontal position */

/* TLI_STAT */
#define TLI_STAT_VDE                      BIT(0)           /*!< current VDE status */
#define TLI_STAT_HDE                      BIT(1)           /*!< current HDE status */
#define TLI_STAT_VS                       BIT(2)           /*!< current VS status of the TLI */
#define TLI_STAT_HS                       BIT(3)           /*!< current HS status of the TLI  */

/* TLI_LxCTL */
#define TLI_LxCTL_LEN                     BIT(0)           /*!< layer enable */
#define TLI_LxCTL_CKEYEN                  BIT(1)           /*!< color keying enable */
#define TLI_LxCTL_LUTEN                   BIT(4)           /*!< LUT enable */

/* TLI_LxHPOS */
#define TLI_LxHPOS_WLP                    BITS(0,11)       /*!< window left position */
#define TLI_LxHPOS_WRP                    BITS(16,27)      /*!< window right position */

/* TLI_LxVPOS */
#define TLI_LxVPOS_WTP                    BITS(0,11)       /*!< window top position */
#define TLI_LxVPOS_WBP                    BITS(16,27)      /*!< window bottom position */

/* TLI_LxCKEY */
#define TLI_LxCKEY_CKEYB                  BITS(0,7)        /*!< color key blue */
#define TLI_LxCKEY_CKEYG                  BITS(8,15)       /*!< color key green */
#define TLI_LxCKEY_CKEYR                  BITS(16,23)      /*!< color key red */

/* TLI_LxPPF */
#define TLI_LxPPF_PPF                     BITS(0,2)        /*!< packeted pixel format */

/* TLI_LxSA */
#define TLI_LxSA_SA                       BITS(0,7)        /*!< specified alpha */

/* TLI_LxDC */
#define TLI_LxDC_DCB                      BITS(0,7)        /*!< the default color blue */
#define TLI_LxDC_DCG                      BITS(8,15)       /*!< the default color green */
#define TLI_LxDC_DCR                      BITS(16,23)      /*!< the default color red */
#define TLI_LxDC_DCA                      BITS(24,31)      /*!< the default color alpha */

/* TLI_LxBLEND */
#define TLI_LxBLEND_ACF2                  BITS(0,2)        /*!< alpha calculation factor 2 of blending method */
#define TLI_LxBLEND_ACF1                  BITS(8,10)       /*!< alpha calculation factor 1 of blending method */

/* TLI_LxFBADDR */
#define TLI_LxFBADDR_FBADD                BITS(0,31)       /*!< frame buffer base address */

/* TLI_LxFLLEN */
#define TLI_LxFLLEN_FLL                   BITS(0,12)       /*!< frame line length */
#define TLI_LxFLLEN_STDOFF                BITS(16,28)      /*!< frame buffer stride offset */

/* TLI_LxFTLN */
#define TLI_LxFTLN_FTLN                   BITS(0,10)       /*!< frame total line number */

/* TLI_LxLUT */
#define TLI_LxLUT_TB                      BITS(0,7)        /*!< blue channel of a LUT entry */
#define TLI_LxLUT_TG                      BITS(8,15)       /*!< green channel of a LUT entry */
#define TLI_LxLUT_TR                      BITS(16,23)      /*!< red channel of a LUT entry */
#define TLI_LxLUT_TADD                    BITS(24,31)      /*!< look up table write address */

/* constants definitions */

/* TLI parameter struct definitions */
typedef struct
{   
    uint32_t synpsz_vpsz;                     /*!< size of the vertical synchronous pulse */
    uint32_t synpsz_hpsz;                     /*!< size of the horizontal synchronous pulse */
    uint32_t backpsz_vbpsz;                   /*!< size of the vertical back porch plus synchronous pulse */
    uint32_t backpsz_hbpsz;                   /*!< size of the horizontal back porch plus synchronous pulse */
    uint32_t activesz_vasz;                   /*!< size of the vertical active area width plus back porch and synchronous pulse */
    uint32_t activesz_hasz;                   /*!< size of the horizontal active area width plus back porch and synchronous pulse */
    uint32_t totalsz_vtsz;                    /*!< vertical total size of the display */
    uint32_t totalsz_htsz;                    /*!< horizontal total size of the display */
    uint32_t backcolor_red;                   /*!< background value red */
    uint32_t backcolor_green;                 /*!< background value green */
    uint32_t backcolor_blue;                  /*!< background value blue */
    uint32_t signalpolarity_hs;               /*!< horizontal pulse polarity selection */
    uint32_t signalpolarity_vs;               /*!< vertical pulse polarity selection */
    uint32_t signalpolarity_de;               /*!< data enable polarity selection */
    uint32_t signalpolarity_pixelck;          /*!< pixel clock polarity selection */
}tli_parameter_struct; 

/* TLI Layer parameter struct definitions */
typedef struct
{   
    uint32_t layer_window_rightpos;           /*!< window right position */
    uint32_t layer_window_leftpos;            /*!< window left position */
    uint32_t layer_window_bottompos;          /*!< window bottom position */
    uint32_t layer_window_toppos;             /*!< window top position */
    uint32_t layer_ppf;                       /*!< packeted pixel format */
    uint32_t layer_sa;                        /*!< specified alpha */
    uint32_t layer_default_alpha;             /*!< the default color alpha */
    uint32_t layer_default_red;               /*!< the default color red */
    uint32_t layer_default_green;             /*!< the default color green */
    uint32_t layer_default_blue;              /*!< the default color blue */
    uint32_t layer_acf1;                      /*!< alpha calculation factor 1 of blending method */
    uint32_t layer_acf2;                      /*!< alpha calculation factor 2 of blending method */
    uint32_t layer_frame_bufaddr;             /*!< frame buffer base address */
    uint32_t layer_frame_buf_stride_offset;   /*!< frame buffer stride offset */
    uint32_t layer_frame_line_length;         /*!< frame line length */
    uint32_t layer_frame_total_line_number;   /*!< frame total line number */
}tli_layer_parameter_struct; 

/* TLI layer LUT parameter struct definitions */
typedef struct
{                                                       
    uint32_t layer_table_addr;                /*!< look up table write address */
    uint32_t layer_lut_channel_red;           /*!< red channel of a LUT entry */
    uint32_t layer_lut_channel_green;         /*!< green channel of a LUT entry */
    uint32_t layer_lut_channel_blue;          /*!< blue channel of a LUT entry */                                                       
}tli_layer_lut_parameter_struct; 

/* packeted pixel format */
typedef enum 
{
     LAYER_PPF_ARGB8888,                          /*!< layerx pixel format ARGB8888 */
     LAYER_PPF_RGB888,                            /*!< layerx pixel format RGB888 */
     LAYER_PPF_RGB565,                            /*!< layerx pixel format RGB565 */
     LAYER_PPF_ARGB1555,                          /*!< layerx pixel format ARGB1555 */
     LAYER_PPF_ARGB4444,                          /*!< layerx pixel format ARGB4444 */
     LAYER_PPF_L8,                                /*!< layerx pixel format L8 */
     LAYER_PPF_AL44,                              /*!< layerx pixel format AL44 */
     LAYER_PPF_AL88                               /*!< layerx pixel format AL88 */
} tli_layer_ppf_enum;

/* layer reload configure */
#define TLI_FRAME_BLANK_RELOAD_EN     ((uint8_t)0x00U)                 /*!< the layer configuration will be reloaded at frame blank */
#define TLI_REQUEST_RELOAD_EN         ((uint8_t)0x01U)                 /*!< the layer configuration will be reloaded after this bit sets */

/* dither Function */
#define TLI_DITHER_DISABLE            ((uint8_t)0x00U)                 /*!< dither function disable */
#define TLI_DITHER_ENABLE             ((uint8_t)0x01U)                 /*!< dither function enable */

/* horizontal pulse polarity selection */

#define TLI_HSYN_ACTLIVE_LOW          ((uint32_t)0x00000000U)          /*!< horizontal synchronous pulse active low */
#define TLI_HSYN_ACTLIVE_HIGHT        TLI_CTL_HPPS                     /*!< horizontal synchronous pulse active high */


/* vertical pulse polarity selection */

#define TLI_VSYN_ACTLIVE_LOW          ((uint32_t)0x00000000U)          /*!< vertical synchronous pulse active low */
#define TLI_VSYN_ACTLIVE_HIGHT        TLI_CTL_VPPS                     /*!< vertical synchronous pulse active high */


/* pixel Clock Polarity Selection */

#define TLI_PIXEL_CLOCK_TLI           ((uint32_t)0x00000000U)          /*!< pixel clock is TLI clock */
#define TLI_PIXEL_CLOCK_INVERTEDTLI   TLI_CTL_CLKPS                    /*!< pixel clock is inverted TLI clock */


/* data Enable Polarity Selection */

#define TLI_DE_ACTLIVE_LOW            ((uint32_t)0x00000000U)          /*!< data enable active low */
#define TLI_DE_ACTLIVE_HIGHT          TLI_CTL_DEPS                     /*!< data enable active high */

/* alpha calculation factor 1 of blending method */
#define LxBLEND_ACF1(regval)          (BITS(8,10) & ((regval)<<8))
#define LAYER_ACF1_SA                 LxBLEND_ACF1(4)                  /*!< normalization specified alpha */
#define LAYER_ACF1_PASA               LxBLEND_ACF1(6)                  /*!< normalization pixel alpha * normalization specified alpha */

/* alpha calculation factor 2 of blending method*/
#define LxBLEND_ACF2(regval)          (BITS(0,2) & ((regval)))
#define LAYER_ACF2_SA                 LxBLEND_ACF2(5)                  /*!< normalization specified alpha */
#define LAYER_ACF2_PASA               LxBLEND_ACF2(7)                  /*!< normalization pixel alpha x normalization specified alpha */
/* function declarations */

/* deinitialize TLI */
void tli_deinit(void);
/* initialize TLI */
void tli_init(tli_parameter_struct *tli_struct);
/* TLI dither function enable */
void tli_dither_config(uint8_t ditherstat);
/* enable TLI */
void tli_enable(void);
/* disable TLI */
void tli_disable(void);
/* TLI reload mode config*/
void tli_reload_config(uint8_t reloadmod);

/* TLI interrupt enable */
void tli_interrupt_enable(uint32_t inttype);
/* TLI interrupt disable */
void tli_interrupt_disable(uint32_t inttype);
/* get TLI interrupt flag */
FlagStatus tli_interrupt_flag_get(uint32_t intflag);
/* clear TLI interrupt flag */
void tli_interrupt_flag_clear(uint32_t intflag);

/* set line mark value */
void tli_line_mark_set(uint32_t linenum);
/* get current displayed position */
uint32_t tli_current_pos_get(void);
/* get TLI state */
FlagStatus tli_flag_get(uint32_t state);

/* TLI layer enable */
void tli_layer_enable(uint32_t layerx);
/* TLI layer disable */
void tli_layer_disable(uint32_t layerx);
/* TLI layer color keying enable */
void tli_color_key_enable(uint32_t layerx);
/* TLI layer color keying disable */
void tli_color_key_disable(uint32_t layerx);
/* TLI layer LUT enable */
void tli_lut_enable(uint32_t layerx);
/* TLI layer LUT disable */
void tli_lut_disable(uint32_t layerx);
/* TLI layer initialize */
void tli_layer_init(uint32_t layerx,tli_layer_parameter_struct *layer_struct);
/* TLI layer initialize */
void tli_layer_window_offset_modify(uint32_t layerx,uint32_t offset_x,uint32_t offset_y);
/* TLI layer lut initialize */
void tli_lut_init(uint32_t layerx,tli_layer_lut_parameter_struct *lut_struct);
/* TLI layer key initialize */
void tli_ckey_init(uint32_t layerx,uint32_t redkey,uint32_t greenkey,uint32_t bluekey);

#endif /* GD32F4XX_TLI_H */
