/*!
    \file    gd32h7xx_ipa.h
    \brief   definitions for the IPA

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

#ifndef GD32H7XX_IPA_H
#define GD32H7XX_IPA_H

#include "gd32h7xx.h"

/* IPA definitions */
#define IPA                               IPA_BASE                      /*!< IPA base address */

/* bits definitions */
/* registers definitions */
#define IPA_CTL                           REG32(IPA + 0x00000000U)      /*!< IPA control register */
#define IPA_INTF                          REG32(IPA + 0x00000004U)      /*!< IPA interrupt flag register */
#define IPA_INTC                          REG32(IPA + 0x00000008U)      /*!< IPA interrupt flag clear register */
#define IPA_FMADDR                        REG32(IPA + 0x0000000CU)      /*!< IPA foreground memory base address register */
#define IPA_FLOFF                         REG32(IPA + 0x00000010U)      /*!< IPA foreground line offset register */
#define IPA_BMADDR                        REG32(IPA + 0x00000014U)      /*!< IPA background memory base address register */
#define IPA_BLOFF                         REG32(IPA + 0x00000018U)      /*!< IPA background line offset register */
#define IPA_FPCTL                         REG32(IPA + 0x0000001CU)      /*!< IPA foreground pixel control register */
#define IPA_FPV                           REG32(IPA + 0x00000020U)      /*!< IPA foreground pixel value register */
#define IPA_BPCTL                         REG32(IPA + 0x00000024U)      /*!< IPA background pixel control register */
#define IPA_BPV                           REG32(IPA + 0x00000028U)      /*!< IPA background pixel value register */
#define IPA_FLMADDR                       REG32(IPA + 0x0000002CU)      /*!< IPA foreground LUT memory base address register */
#define IPA_BLMADDR                       REG32(IPA + 0x00000030U)      /*!< IPA background LUT memory base address register */
#define IPA_DPCTL                         REG32(IPA + 0x00000034U)      /*!< IPA destination pixel control register */
#define IPA_DPV                           REG32(IPA + 0x00000038U)      /*!< IPA destination pixel value register */
#define IPA_DMADDR                        REG32(IPA + 0x0000003CU)      /*!< IPA destination memory base address register */
#define IPA_DLOFF                         REG32(IPA + 0x00000040U)      /*!< IPA destination line offset register */
#define IPA_IMS                           REG32(IPA + 0x00000044U)      /*!< IPA image size register */
#define IPA_LM                            REG32(IPA + 0x00000048U)      /*!< IPA line mark register */
#define IPA_ITCTL                         REG32(IPA + 0x0000004CU)      /*!< IPA inter-timer control register */
#define IPA_BSCTL                         REG32(IPA + 0x00000050U)      /*!< IPA bilinear scaling control register */
#define IPA_DIMS                          REG32(IPA + 0x00000054U)      /*!< IPA scaling image size register */
#define IPA_EF_UV_MADDR                   REG32(IPA + 0x0000005CU)      /*!< IPA foreground even frame/UV memory base address register */
#define IPA_CSCC_CFG0                     REG32(IPA + 0x00000060U)      /*!< IPA color space conversion coefficient 0 */
#define IPA_CSCC_CFG1                     REG32(IPA + 0x00000064U)      /*!< IPA color space conversion coefficient 1 */
#define IPA_CSCC_CFG2                     REG32(IPA + 0x00000068U)      /*!< IPA color space conversion coefficient 2 */

/* IPA_CTL */
#define IPA_CTL_TEN                       BIT(0)                        /*!< transfer enable */
#define IPA_CTL_THU                       BIT(1)                        /*!< transfer hang up */
#define IPA_CTL_TST                       BIT(2)                        /*!< transfer stop */
#define IPA_CTL_TAEIE                     BIT(8)                        /*!< enable bit for transfer access error interrupt */
#define IPA_CTL_FTFIE                     BIT(9)                        /*!< enable bit for full transfer finish interrup */
#define IPA_CTL_TLMIE                     BIT(10)                       /*!< enable bit for transfer line mark interrupt */
#define IPA_CTL_LACIE                     BIT(11)                       /*!< enable bit for LUT access conflict interrupt */
#define IPA_CTL_LLFIE                     BIT(12)                       /*!< enable bit for LUT loading finish interrupt */
#define IPA_CTL_WCFIE                     BIT(13)                       /*!< enable bit for wrong configuration interrupt */
#define IPA_CTL_PFCM                      BITS(16,17)                   /*!< pixel format convert mode */

/* IPA_INTF */
#define IPA_INTF_TAEIF                    BIT(0)                        /*!< transfer access error interrupt flag */
#define IPA_INTF_FTFIF                    BIT(1)                        /*!< full transfer finish interrupt flag */
#define IPA_INTF_TLMIF                    BIT(2)                        /*!< transfer line mark interrupt flag */
#define IPA_INTF_LACIF                    BIT(3)                        /*!< LUT access conflict interrupt flag */
#define IPA_INTF_LLFIF                    BIT(4)                        /*!< LUT loading finish interrupt flag */
#define IPA_INTF_WCFIF                    BIT(5)                        /*!< wrong configuration interrupt flag */

/* IPA_INTC */
#define IPA_INTC_TAEIFC                   BIT(0)                        /*!< clear bit for transfer access error interrupt flag */
#define IPA_INTC_FTFIFC                   BIT(1)                        /*!< clear bit for full transfer finish interrupt flag */
#define IPA_INTC_TLMIFC                   BIT(2)                        /*!< clear bit for transfer line mark interrupt flag */
#define IPA_INTC_LACIFC                   BIT(3)                        /*!< clear bit for LUT access conflict interrupt flag */
#define IPA_INTC_LLFIFC                   BIT(4)                        /*!< clear bit for LUT loading finish interrupt flag */
#define IPA_INTC_WCFIFC                   BIT(5)                        /*!< clear bit for wrong configuration interrupt flag */

/* IPA_FMADDR */
#define IPA_FMADDR_FMADDR                 BITS(0,31)                    /*!< foreground memory base address */

/* IPA_FLOFF */
#define IPA_FLOFF_FLOFF                   BITS(0,13)                    /*!< foreground line offset */

/* IPA_BMADDR */
#define IPA_BMADDR_BMADDR                 BITS(0,31)                    /*!< background memory base address */

/* IPA_BLOFF */
#define IPA_BLOFF_BLOFF                   BITS(0,13)                    /*!< background line offset */

/* IPA_FPCTL */
#define IPA_FPCTL_FPF                     BITS(0,3)                     /*!< foreground pixel format */
#define IPA_FPCTL_FLPF                    BIT(4)                        /*!< foreground LUT pixel format */
#define IPA_FPCTL_FLLEN                   BIT(5)                        /*!< foreground LUT loading enable */
#define IPA_FPCTL_FCNP                    BITS(8,15)                    /*!< foreground LUT number of pixel */
#define IPA_FPCTL_FAVCA                   BITS(16,17)                   /*!< foreground alpha value calculation algorithm */
#define IPA_FPCTL_FIIMEN                  BIT(23)                       /*!< foreground input interlace mode enable */
#define IPA_FPCTL_FPDAV                   BITS(24,31)                   /*!< foreground pre-defined alpha value */

/* IPA_FPV */
#define IPA_FPV_FPDBV                     BITS(0,7)                     /*!< foreground pre-defined red value */
#define IPA_FPV_FPDGV                     BITS(8,15)                    /*!< foreground pre-defined green value */
#define IPA_FPV_FPDRV                     BITS(16,23)                   /*!< foreground pre-defined red value */

/* IPA_BPCTL */
#define IPA_BPCTL_BPF                     BITS(0,3)                     /*!< background pixel format */
#define IPA_BPCTL_BLPF                    BIT(4)                        /*!< background LUT pixel format */
#define IPA_BPCTL_BLLEN                   BIT(5)                        /*!< background LUT loading enable */
#define IPA_BPCTL_BCNP                    BITS(8,15)                    /*!< background LUT number of pixel */
#define IPA_BPCTL_BAVCA                   BITS(16,17)                   /*!< background alpha value calculation algorithm */
#define IPA_BPCTL_BPDAV                   BITS(24,31)                   /*!< background pre-defined alpha value */

/* IPA_BPV */
#define IPA_BPV_BPDBV                     BITS(0,7)                     /*!< background pre-defined blue value */
#define IPA_BPV_BPDGV                     BITS(8,15)                    /*!< background pre-defined green value */
#define IPA_BPV_BPDRV                     BITS(16,23)                   /*!< background pre-defined red value */

/* IPA_FLMADDR */
#define IPA_FLMADDR_FLMADDR               BITS(0,31)                    /*!< foreground LUT memory base address */

/* IPA_BLMADDR */
#define IPA_BLMADDR_BLMADDR               BITS(0,31)                    /*!< background LUT memory base address */

/* IPA_DPCTL */
#define IPA_DPCTL_DPF                     BITS(0,2)                     /*!< destination pixel control register */
#define IPA_DPCTL_ROT                     BITS(8,9)                     /*!< destination image rotation angle */
#define IPA_DPCTL_HORDEC                  BITS(16,17)                   /*!< destination horizontal pre decimation filter control */
#define IPA_DPCTL_VERDEC                  BITS(18,19)                   /*!< destination verticle pre decimation filter control */

/* IPA_DPV */
/* destination pixel format ARGB8888 */
#define IPA_DPV_DPDBV_0                   BITS(0,7)                     /*!< destination pre-defined blue value */
#define IPA_DPV_DPDGV_0                   BITS(8,15)                    /*!< destination pre-defined green value */
#define IPA_DPV_DPDRV_0                   BITS(16,23)                   /*!< destination pre-defined red value */
#define IPA_DPV_DPDAV_0                   BITS(24,31)                   /*!< destination pre-defined alpha value */

/* destination pixel format RGB888 */
#define IPA_DPV_DPDBV_1                   BITS(0,7)                     /*!< destination pre-defined blue value */
#define IPA_DPV_DPDGV_1                   BITS(8,15)                    /*!< destination pre-defined green value */
#define IPA_DPV_DPDRV_1                   BITS(16,23)                   /*!< destination pre-defined red value */

/* destination pixel format RGB565 */
#define IPA_DPV_DPDBV_2                   BITS(0,4)                     /*!< destination pre-defined blue value */
#define IPA_DPV_DPDGV_2                   BITS(5,10)                    /*!< destination pre-defined green value */
#define IPA_DPV_DPDRV_2                   BITS(11,15)                   /*!< destination pre-defined red value */

/* destination pixel format ARGB1555 */
#define IPA_DPV_DPDBV_3                   BITS(0,4)                     /*!< destination pre-defined blue value */
#define IPA_DPV_DPDGV_3                   BITS(5,9)                     /*!< destination pre-defined green value */
#define IPA_DPV_DPDRV_3                   BITS(10,14)                   /*!< destination pre-defined red value */
#define IPA_DPV_DPDAV_3                   BIT(15)                       /*!< destination pre-defined alpha value */

/* destination pixel format ARGB4444 */
#define IPA_DPV_DPDBV_4                   BITS(0,3)                     /*!< destination pre-defined blue value */
#define IPA_DPV_DPDGV_4                   BITS(4,7)                     /*!< destination pre-defined green value */
#define IPA_DPV_DPDRV_4                   BITS(8,11)                    /*!< destination pre-defined red value */
#define IPA_DPV_DPDAV_4                   BITS(12,15)                   /*!< destination pre-defined alpha value */

/* IPA_DMADDR */
#define IPA_DMADDR_DMADDR                 BITS(0,31)                    /*!< destination memory base address */

/* IPA_DLOFF */
#define IPA_DLOFF_DLOFF                   BITS(0,13)                    /*!< destination line offset */

/* IPA_IMS */
#define IPA_IMS_HEIGHT                    BITS(0,15)                    /*!< height of the image to be processed */
#define IPA_IMS_WIDTH                     BITS(16,29)                   /*!< width of the image to be processed */

/* IPA_LM */
#define IPA_LM_LM                         BITS(0,15)                    /*!< line mark */

/* IPA_ITCTL */
#define IPA_ITCTL_ITEN                    BIT(0)                        /*!< inter-timer enable */
#define IPA_ITCTL_NCCI                    BITS(8,15)                    /*!< number of clock cycles interval */

/* IPA_BSCTL */
#define IPA_BSCTL_XSCALE                  BITS(0,13)                    /*!< foreground X scaling factor */
#define IPA_BSCTL_YSCALE                  BITS(16,29)                   /*!< foreground Y scaling factor */

/* IPA_DIMS */
#define IPA_DIMS_DHEIGHT                  BITS(0,15)                    /*!< destination height after scaling */
#define IPA_DIMS_DWIDTH                   BITS(16,29)                   /*!< destination width after scaling */

/* IPA_EF_UV_MADDR */
#define IPA_EF_UV_MADDR_EFUVMADDR         BITS(0,31)                    /*!< foreground even frame/UV memory base address */

/* IPA_CSCC_CFG0 */
#define IPA_CSCC_CFG0_YOFF                BITS(0,8)                     /*!< offset implicit in the Y data */
#define IPA_CSCC_CFG0_UVOFF               BITS(9,17)                    /*!< offset implicit in the UV data */
#define IPA_CSCC_CFG0_C0                  BITS(18,28)                   /*!< Y multiplier coefficient */
#define IPA_CSCC_CFG0_CONVMOD             BIT(31)                       /*!< color space convert mode */

/* IPA_CSCC_CFG1 */
#define IPA_CSCC_CFG1_C4                  BITS(0,10)                    /*!< blue U/Cb multiplier coefficient */
#define IPA_CSCC_CFG1_C1                  BITS(16,26)                   /*!< red V/Cr multiplier coefficient */

/* IPA_CSCC_CFG2 */
#define IPA_CSCC_CFG2_C3                  BITS(0,10)                    /*!< green U/Cb multiplier coefficient */
#define IPA_CSCC_CFG2_C2                  BITS(16,26)                   /*!< green V/Cr multiplier coefficient */

/* constants definitions */
/* IPA foreground parameter struct definitions */
typedef struct {
    uint32_t foreground_memaddr;                          /*!< foreground memory base address */
    uint32_t foreground_lineoff;                          /*!< foreground line offset */
    uint32_t foreground_prealpha;                         /*!< foreground pre-defined alpha value */
    uint32_t foreground_alpha_algorithm;                  /*!< foreground alpha value calculation algorithm */
    uint32_t foreground_pf;                               /*!< foreground pixel format */
    uint32_t foreground_prered;                           /*!< foreground pre-defined red value */
    uint32_t foreground_pregreen;                         /*!< foreground pre-defined green value */
    uint32_t foreground_preblue;                          /*!< foreground pre-defined blue value */
    uint32_t foreground_interlace_mode;                   /*!< foreground input interlace mode enable */
    uint32_t foreground_efuv_memaddr;                     /*!< foreground even frame / UV memory base address */
} ipa_foreground_parameter_struct;

/* IPA background parameter struct definitions */
typedef struct {
    uint32_t background_memaddr;                          /*!< background memory base address */
    uint32_t background_lineoff;                          /*!< background line offset */
    uint32_t background_prealpha;                         /*!< background pre-defined alpha value */
    uint32_t background_alpha_algorithm;                  /*!< background alpha value calculation algorithm */
    uint32_t background_pf;                               /*!< background pixel format */
    uint32_t background_prered;                           /*!< background pre-defined red value */
    uint32_t background_pregreen;                         /*!< background pre-defined green value */
    uint32_t background_preblue;                          /*!< background pre-defined blue value */
} ipa_background_parameter_struct;

/* IPA destination parameter struct definitions */
typedef struct {
    uint32_t destination_memaddr;                         /*!< destination memory base address */
    uint32_t destination_lineoff;                         /*!< destination line offset */
    uint32_t destination_prealpha;                        /*!< destination pre-defined alpha value */
    uint32_t destination_pf;                              /*!< destination pixel format */
    uint32_t destination_prered;                          /*!< destination pre-defined red value */
    uint32_t destination_pregreen;                        /*!< destination pre-defined green value */
    uint32_t destination_preblue;                         /*!< destination pre-defined blue value */
    uint32_t image_width;                                 /*!< width of the image to be processed */
    uint32_t image_height;                                /*!< height of the image to be processed */
    uint32_t image_rotate;                                /*!< angle of image rotation */
    uint32_t image_hor_decimation;                        /*!< image horizontal pre-decimation in width */
    uint32_t image_ver_decimation;                        /*!< image vertical pre-decimation in height */
    uint32_t image_bilinear_xscale;                       /*!< bilinear scaling x factor */
    uint32_t image_bilinear_yscale;                       /*!< bilinear scaling y factor */
    uint32_t image_scaling_width;                         /*!< width of the image after scaling */
    uint32_t image_scaling_height;                        /*!< height of the image after scaling */
} ipa_destination_parameter_struct;

/* destination pixel format */
typedef enum {
    IPA_DPF_ARGB8888 = 0U,                                /*!< destination pixel format ARGB8888 */
    IPA_DPF_RGB888,                                       /*!< destination pixel format RGB888 */
    IPA_DPF_RGB565,                                       /*!< destination pixel format RGB565 */
    IPA_DPF_ARGB1555,                                     /*!< destination pixel format ARGB1555 */
    IPA_DPF_ARGB4444                                      /*!< destination pixel format ARGB4444 */
} ipa_dpf_enum;

/* IPA color conversion parameter struct definitions */
typedef struct {
    uint32_t color_space;                                 /*!< color space convert mode */
    uint32_t y_offset;                                    /*!< offset implicit in the Y data */
    uint32_t uv_offset;                                   /*!< offset implicit in the UV data */
    uint32_t coef_c0;                                     /*!< Y multiplier coefficient */
    uint32_t coef_c1;                                     /*!< V/Cr red multiplier coefficient */
    uint32_t coef_c2;                                     /*!< V/Cr green multiplier coefficient */
    uint32_t coef_c3;                                     /*!< U/Cb green multiplier coefficient */
    uint32_t coef_c4;                                     /*!< U/Cb blue multiplier coefficient */
} ipa_conversion_parameter_struct;

/* destination pixel format */
typedef enum {
    IPA_COLORSPACE_YUV = 0U,                              /*!< IPA color conversion using YUV parameter */
    IPA_COLORSPACE_YCBCR                                  /*!< IPA color conversion using YCbCr parameter */
} ipa_colorspace_enum;

/* LUT pixel format */
#define IPA_LUT_PF_ARGB8888             ((uint8_t)0x00U)                 /*!< LUT pixel format ARGB8888 */
#define IPA_LUT_PF_RGB888               ((uint8_t)0x01U)                 /*!< LUT pixel format RGB888 */

/* Inter-timer */
#define IPA_INTER_TIMER_DISABLE         ((uint8_t)0x00U)                 /*!< inter-timer disable */
#define IPA_INTER_TIMER_ENABLE          ((uint8_t)0x01U)                 /*!< inter-timer enable */

/* IPA pixel format convert mode */
#define CTL_PFCM(regval)                (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define IPA_FGTODE                      CTL_PFCM(0)                      /*!< foreground memory to destination memory without pixel format convert */
#define IPA_FGTODE_PF_CONVERT           CTL_PFCM(1)                      /*!< foreground memory to destination memory with pixel format convert */
#define IPA_FGBGTODE                    CTL_PFCM(2)                      /*!< blending foreground and background memory to destination memory */
#define IPA_FILL_UP_DE                  CTL_PFCM(3)                      /*!< fill up destination memory with specific color */

/* foreground alpha value calculation algorithm */
#define FPCTL_FAVCA(regval)             (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define IPA_FG_ALPHA_MODE_0             FPCTL_FAVCA(0)                   /*!< no effect */
#define IPA_FG_ALPHA_MODE_1             FPCTL_FAVCA(1)                   /*!< FPDAV[7:0] is selected as the foreground alpha value */
#define IPA_FG_ALPHA_MODE_2             FPCTL_FAVCA(2)                   /*!< FPDAV[7:0] multiplied by read alpha value */

/* background alpha value calculation algorithm */
#define BPCTL_BAVCA(regval)             (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define IPA_BG_ALPHA_MODE_0             BPCTL_BAVCA(0)                   /*!< no effect */
#define IPA_BG_ALPHA_MODE_1             BPCTL_BAVCA(1)                   /*!< BPDAV[7:0] is selected as the background alpha value */
#define IPA_BG_ALPHA_MODE_2             BPCTL_BAVCA(2)                   /*!< BPDAV[7:0] multiplied by read alpha value */

/* foreground pixel format */
#define FPCTL_PPF(regval)               (BITS(0,3) & ((uint32_t)(regval)))
#define FOREGROUND_PPF_ARGB8888         FPCTL_PPF(0)                     /*!< foreground pixel format ARGB8888 */
#define FOREGROUND_PPF_RGB888           FPCTL_PPF(1)                     /*!< foreground pixel format RGB888 */
#define FOREGROUND_PPF_RGB565           FPCTL_PPF(2)                     /*!< foreground pixel format RGB565 */
#define FOREGROUND_PPF_ARGB1555         FPCTL_PPF(3)                     /*!< foreground pixel format ARGB1555 */
#define FOREGROUND_PPF_ARGB4444         FPCTL_PPF(4)                     /*!< foreground pixel format ARGB4444 */
#define FOREGROUND_PPF_L8               FPCTL_PPF(5)                     /*!< foreground pixel format L8 */
#define FOREGROUND_PPF_AL44             FPCTL_PPF(6)                     /*!< foreground pixel format AL44 */
#define FOREGROUND_PPF_AL88             FPCTL_PPF(7)                     /*!< foreground pixel format AL88 */
#define FOREGROUND_PPF_L4               FPCTL_PPF(8)                     /*!< foreground pixel format L4 */
#define FOREGROUND_PPF_A8               FPCTL_PPF(9)                     /*!< foreground pixel format A8 */
#define FOREGROUND_PPF_A4               FPCTL_PPF(10)                    /*!< foreground pixel format A4 */
#define FOREGROUND_PPF_YUV444_1P        FPCTL_PPF(11)                    /*!< foreground pixel format YUV444 */
#define FOREGROUND_PPF_UYVY422_1P       FPCTL_PPF(12)                    /*!< foreground pixel format UYVY422 1 plane */
#define FOREGROUND_PPF_VYUY422_1P       FPCTL_PPF(13)                    /*!< foreground pixel format VYUY422 1 plane */
#define FOREGROUND_PPF_YUV420_2P        FPCTL_PPF(14)                    /*!< foreground pixel format YUV420 2 plane */
#define FOREGROUND_PPF_YVU420_2P        FPCTL_PPF(15)                    /*!< foreground pixel format YVU420 2 plane */

/* background pixel format */
#define BPCTL_PPF(regval)               (BITS(0,3) & ((uint32_t)(regval)))
#define BACKGROUND_PPF_ARGB8888         BPCTL_PPF(0)                     /*!< background pixel format ARGB8888 */
#define BACKGROUND_PPF_RGB888           BPCTL_PPF(1)                     /*!< background pixel format RGB888 */
#define BACKGROUND_PPF_RGB565           BPCTL_PPF(2)                     /*!< background pixel format RGB565 */
#define BACKGROUND_PPF_ARGB1555         BPCTL_PPF(3)                     /*!< background pixel format ARGB1555 */
#define BACKGROUND_PPF_ARGB4444         BPCTL_PPF(4)                     /*!< background pixel format ARGB4444 */
#define BACKGROUND_PPF_L8               BPCTL_PPF(5)                     /*!< background pixel format L8 */
#define BACKGROUND_PPF_AL44             BPCTL_PPF(6)                     /*!< background pixel format AL44 */
#define BACKGROUND_PPF_AL88             BPCTL_PPF(7)                     /*!< background pixel format AL88 */
#define BACKGROUND_PPF_L4               BPCTL_PPF(8)                     /*!< background pixel format L4 */
#define BACKGROUND_PPF_A8               BPCTL_PPF(9)                     /*!< background pixel format A8 */
#define BACKGROUND_PPF_A4               BPCTL_PPF(10)                    /*!< background pixel format A4 */

/* rotation angle */
#define DPCTL_ROT(regval)               (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define DESTINATION_ROTATE_0            DPCTL_ROT(0)                     /*!< destination rotate 0 degree */
#define DESTINATION_ROTATE_90           DPCTL_ROT(1)                     /*!< destination rotate 90 degree */
#define DESTINATION_ROTATE_180          DPCTL_ROT(2)                     /*!< destination rotate 180 degree */
#define DESTINATION_ROTATE_270          DPCTL_ROT(3)                     /*!< destination rotate 270 degree */

/* vertical pre-decimation filter control */
#define DPCTL_HORDEC(regval)            (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define DESTINATION_HORDECIMATE_DISABLE DPCTL_HORDEC(0)                  /*!< disable horizontal decimate */
#define DESTINATION_HORDECIMATE_2       DPCTL_HORDEC(1)                  /*!< horizontal decimated by 2 */
#define DESTINATION_HORDECIMATE_4       DPCTL_HORDEC(2)                  /*!< horizontal decimated by 4 */
#define DESTINATION_HORDECIMATE_8       DPCTL_HORDEC(3)                  /*!< horizontal decimated by 8 */

/* horizontal pre-decimation filter control */
#define DPCTL_VERDEC(regval)            (BITS(18,19) & ((uint32_t)(regval) << 18U))
#define DESTINATION_VERDECIMATE_DISABLE DPCTL_VERDEC(0)                  /*!< disable verticle decimate */
#define DESTINATION_VERDECIMATE_2       DPCTL_VERDEC(1)                  /*!< verticle decimated by 2 */
#define DESTINATION_VERDECIMATE_4       DPCTL_VERDEC(2)                  /*!< verticle decimated by 4 */
#define DESTINATION_VERDECIMATE_8       DPCTL_VERDEC(3)                  /*!< verticle decimated by 8 */

/* IPA flags */
#define IPA_FLAG_TAE                    IPA_INTF_TAEIF                   /*!< transfer access error interrupt flag */
#define IPA_FLAG_FTF                    IPA_INTF_FTFIF                   /*!< full transfer finish interrupt flag */
#define IPA_FLAG_TLM                    IPA_INTF_TLMIF                   /*!< transfer line mark interrupt flag */
#define IPA_FLAG_LAC                    IPA_INTF_LACIF                   /*!< LUT access conflict interrupt flag */
#define IPA_FLAG_LLF                    IPA_INTF_LLFIF                   /*!< LUT loading finish interrupt flag */
#define IPA_FLAG_WCF                    IPA_INTF_WCFIF                   /*!< wrong configuration interrupt flag */

/* IPA interrupt enable or disable */
#define IPA_INT_TAE                     IPA_CTL_TAEIE                    /*!< transfer access error interrupt */
#define IPA_INT_FTF                     IPA_CTL_FTFIE                    /*!< full transfer finish interrupt */
#define IPA_INT_TLM                     IPA_CTL_TLMIE                    /*!< transfer line mark interrupt */
#define IPA_INT_LAC                     IPA_CTL_LACIE                    /*!< LUT access conflict interrupt */
#define IPA_INT_LLF                     IPA_CTL_LLFIE                    /*!< LUT loading finish interrupt */
#define IPA_INT_WCF                     IPA_CTL_WCFIE                    /*!< wrong configuration interrupt */

/* IPA interrupt flags */
#define IPA_INT_FLAG_TAE                IPA_INTF_TAEIF                   /*!< transfer access error interrupt flag */
#define IPA_INT_FLAG_FTF                IPA_INTF_FTFIF                   /*!< full transfer finish interrupt flag */
#define IPA_INT_FLAG_TLM                IPA_INTF_TLMIF                   /*!< transfer line mark interrupt flag */
#define IPA_INT_FLAG_LAC                IPA_INTF_LACIF                   /*!< LUT access conflict interrupt flag */
#define IPA_INT_FLAG_LLF                IPA_INTF_LLFIF                   /*!< LUT loading finish interrupt flag */
#define IPA_INT_FLAG_WCF                IPA_INTF_WCFIF                   /*!< wrong configuration interrupt flag */

/* function declarations */
/* functions enable or disable, pixel format convert mode set */
/* deinitialize IPA registers */
void ipa_deinit(void);
/* enable IPA transfer */
void ipa_transfer_enable(void);
/* enable IPA transfer hang up */
void ipa_transfer_hangup_enable(void);
/* disable IPA transfer hang up */
void ipa_transfer_hangup_disable(void);
/* enable IPA transfer stop */
void ipa_transfer_stop_enable(void);
/* disable IPA transfer stop */
void ipa_transfer_stop_disable(void);
/* enable IPA foreground LUT loading */
void ipa_foreground_lut_loading_enable(void);
/* enable IPA background LUT loading */
void ipa_background_lut_loading_enable(void);
/* set pixel format convert mode, the function is invalid when the IPA transfer is enabled */
void ipa_pixel_format_convert_mode_set(uint32_t pfcm);
/* enable foreground interlace mode */
void ipa_foreground_interlace_mode_enable(void);
/* disable foreground interlace mode */
void ipa_foreground_interlace_mode_disable(void);

/* structure initialization, foreground, background, destination and LUT initialization */
/* initialize the structure of IPA foreground parameter struct with the default values, it is
  suggested that call this function after an ipa_foreground_parameter_struct structure is defined */
void ipa_foreground_struct_para_init(ipa_foreground_parameter_struct *foreground_struct);
/* initialize foreground parameters */
void ipa_foreground_init(ipa_foreground_parameter_struct *foreground_struct);
/* initialize the structure of IPA background parameter struct with the default values, it is
  suggested that call this function after an ipa_background_parameter_struct structure is defined */
void ipa_background_struct_para_init(ipa_background_parameter_struct *background_struct);
/* initialize background parameters */
void ipa_background_init(ipa_background_parameter_struct *background_struct);
/* initialize the structure of IPA destination parameter struct with the default values, it is
  suggested that call this function after an ipa_destination_parameter_struct structure is defined */
void ipa_destination_struct_para_init(ipa_destination_parameter_struct *destination_struct);
/* initialize destination parameters */
void ipa_destination_init(ipa_destination_parameter_struct *destination_struct);
/* initialize IPA foreground LUT parameters */
void ipa_foreground_lut_init(uint8_t fg_lut_num, uint8_t fg_lut_pf, uint32_t fg_lut_addr);
/* initialize IPA background LUT parameters */
void ipa_background_lut_init(uint8_t bg_lut_num, uint8_t bg_lut_pf, uint32_t bg_lut_addr);

/* configuration functions */
/* configure IPA line mark */
void ipa_line_mark_config(uint16_t line_num);
/* inter-timer enable or disable */
void ipa_inter_timer_config(uint8_t timer_cfg);
/* configure the number of clock cycles interval */
void ipa_interval_clock_num_config(uint8_t clk_num);
/* initialize the structure of IPA color conversion parameter struct with the YUV or YCbCr conversion parameter,
it is suggested that call this function after an ipa_conversion_parameter_struct structure is defined */
void ipa_color_conversion_struct_para_init(ipa_conversion_parameter_struct *conversion_struct, ipa_colorspace_enum colorspace);
/* configure the color space conversion parameter */
void ipa_color_conversion_config(ipa_conversion_parameter_struct *conversion_struct);
/* configure IPA foreground scaling, including horizontal/vertical pre-decimation factors and X/Y scaling factors */
void ipa_foreground_scaling_config(uint32_t horizontal_decimation, uint32_t vertical_decimation, uint32_t image_scaling_width,
                                   uint32_t image_scaling_height);
/* configure IPA destination scaling, including width/height of image to be processed */
void ipa_destination_scaling_config(uint32_t dest_scaling_width, uint32_t dest_scaling_height);

/* flag and interrupt functions */
/* get IPA flag status in IPA_INTF register */
FlagStatus ipa_flag_get(uint32_t flag);
/* clear IPA flag in IPA_INTF register */
void ipa_flag_clear(uint32_t flag);
/* enable IPA interrupt */
void ipa_interrupt_enable(uint32_t int_flag);
/* disable IPA interrupt */
void ipa_interrupt_disable(uint32_t int_flag);
/* get IPA interrupt flag */
FlagStatus ipa_interrupt_flag_get(uint32_t int_flag);
/* clear IPA interrupt flag */
void ipa_interrupt_flag_clear(uint32_t int_flag);

#endif /* GD32H7XX_IPA_H */
