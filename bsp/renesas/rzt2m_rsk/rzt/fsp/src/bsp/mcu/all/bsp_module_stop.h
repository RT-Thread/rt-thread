/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef BSP_MODULE_H
#define BSP_MODULE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Cancels the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MODULE_START(ip, channel)            {FSP_CRITICAL_SECTION_DEFINE;                                   \
                                                    FSP_CRITICAL_SECTION_ENTER;                                    \
                                                    BSP_MSTP_REG_ ## ip(channel) &= ~BSP_MSTP_BIT_ ## ip(channel); \
                                                    BSP_MSTP_REG_ ## ip(channel);                                  \
                                                    BSP_MSTP_DMY_ ## ip(channel);                                  \
                                                    BSP_MSTP_DMY_ ## ip(channel);                                  \
                                                    BSP_MSTP_DMY_ ## ip(channel);                                  \
                                                    BSP_MSTP_DMY_ ## ip(channel);                                  \
                                                    BSP_MSTP_DMY_ ## ip(channel);                                  \
                                                    FSP_CRITICAL_SECTION_EXIT;}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MODULE_STOP(ip, channel)             {FSP_CRITICAL_SECTION_DEFINE;                                  \
                                                    FSP_CRITICAL_SECTION_ENTER;                                   \
                                                    BSP_MSTP_REG_ ## ip(channel) |= BSP_MSTP_BIT_ ## ip(channel); \
                                                    BSP_MSTP_REG_ ## ip(channel);                                 \
                                                    FSP_CRITICAL_SECTION_EXIT;}

/** @} (end addtogroup BSP_MCU) */

#define BSP_MSTP_REG_FSP_IP_BSC(channel)           R_SYSC_NS->MSTPCRA
#define BSP_MSTP_BIT_FSP_IP_BSC(channel)           (1U);
#define BSP_MSTP_DMY_FSP_IP_BSC(channel)           R_BSC->SDCR;

#define BSP_MSTP_REG_FSP_IP_XSPI(channel)          R_SYSC_NS->MSTPCRA
#define BSP_MSTP_BIT_FSP_IP_XSPI(channel)          (1U << (4U + channel));
#define BSP_MSTP_DMY_FSP_IP_XSPI(channel)          (0 >= channel) ? R_XSPI0->WRAPCFG : R_XSPI1->WRAPCFG

#define BSP_MSTP_REG_FSP_IP_SCI(channel)           *((4U >= channel) ? &R_SYSC_NS->MSTPCRA : &R_SYSC_S->MSTPCRG)
#define BSP_MSTP_BIT_FSP_IP_SCI(channel)           ((4U >= channel) ? (1U << (8U + channel)) : (1U));
#define BSP_MSTP_DMY_FSP_IP_SCI(channel)           (0 >= channel) ? R_SCI0->RDR : ((1 >= channel) ? R_SCI1->RDR :         \
                                                                                   ((2 >=                                 \
                                                                                     channel) ? R_SCI2->RDR : ((3 >=      \
                                                                                                                channel)  \
                                                                                                               ? R_SCI3   \
                                                                                                               ->RDR :    \
                                                                                                               ((4        \
                                                                                                                 >=       \
                                                                                                                 channel) \
                                                                                                                ? R_SCI4  \
                                                                                                                ->RDR :   \
                                                                                                                R_SCI5->  \
                                                                                                                RDR))))

#define BSP_MSTP_REG_FSP_IP_IIC(channel)           *((1U >= channel) ? &R_SYSC_NS->MSTPCRB : &R_SYSC_S->MSTPCRG)
#define BSP_MSTP_BIT_FSP_IP_IIC(channel)           ((1U >= channel) ? (1U << (0U + channel)) : (1U << (1U)));
#define BSP_MSTP_DMY_FSP_IP_IIC(channel)           (0 >= channel) ? R_IIC0->ICCR1 : ((1 >= channel) ? R_IIC1->ICCR1 \
                                                                                     : R_IIC2->ICCR1)

#define BSP_MSTP_REG_FSP_IP_SPI(channel)           *((2U >= channel) ? &R_SYSC_NS->MSTPCRB : &R_SYSC_S->MSTPCRG)
#define BSP_MSTP_BIT_FSP_IP_SPI(channel)           ((2U >= channel) ? (1U << (4U + channel)) : (1U << (2U)));
#define BSP_MSTP_DMY_FSP_IP_SPI(channel)           (0 >= channel) ? R_SPI0->SPCKD : ((1 >= channel) ? R_SPI1->SPCKD :    \
                                                                                     ((2 >=                              \
                                                                                       channel) ? R_SPI2->SPCKD : R_SPI3 \
                                                                                      ->SPCKD))

#define BSP_MSTP_REG_FSP_IP_MTU3(channel)          R_SYSC_NS->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_MTU3(channel)          (1U);
#define BSP_MSTP_DMY_FSP_IP_MTU3(channel)          R_MTU0->TCR;

#define BSP_MSTP_REG_FSP_IP_GPT(channel)           *((13U >= channel) ? &R_SYSC_NS->MSTPCRC : &R_SYSC_S->MSTPCRG)
#define BSP_MSTP_BIT_FSP_IP_GPT(channel)           ((6U >= channel) ? (1U << (1U)) : ((13U >= channel) ? \
                                                                                      (1U << (2U)) : (1U << (3U))));
#define BSP_MSTP_DMY_FSP_IP_GPT(channel)           (6 >=                                                              \
                                                    channel) ? R_GPT0->GTSTR : ((13 >=                                \
                                                                                 channel) ? R_GPT7->GTSTR : R_GPT14-> \
                                                                                GTSTR);
#define BSP_MSTP_REG_FSP_IP_TFU(channel)           R_SYSC_NS->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_TFU(channel)           (1U << (5U));
#define BSP_MSTP_DMY_FSP_IP_TFU(channel)           R_TFU->TRGSTS;

#define BSP_MSTP_REG_FSP_IP_ADC12(channel)         R_SYSC_NS->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_ADC12(channel)         (1U << (6U + channel));
#define BSP_MSTP_DMY_FSP_IP_ADC12(channel)         (0 >= channel) ? R_ADC120->ADCSR : R_ADC121->ADCSR;

#define BSP_MSTP_REG_FSP_IP_DSMIF(channel)         R_SYSC_NS->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_DSMIF(channel)         (1U << (0U + channel));
#define BSP_MSTP_DMY_FSP_IP_DSMIF(channel)         (0 >= channel) ? R_DSMIF0->DSSEICR : R_DSMIF1->DSSEICR

#define BSP_MSTP_REG_FSP_IP_CMT(channel)           R_SYSC_NS->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_CMT(channel)           (1U << (2U + channel));
#define BSP_MSTP_DMY_FSP_IP_CMT(channel)           (0 >=                                                                \
                                                    channel) ? R_CMT->UNT[0].CMSTR0 : ((1 >=                            \
                                                                                        channel) ? R_CMT->UNT[1].CMSTR0 \
                                                                                       : R_CMT->UNT[2].CMSTR0)

#define BSP_MSTP_REG_FSP_IP_CMTW(channel)          R_SYSC_NS->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_CMTW(channel)          (1U << (5U + channel));
#define BSP_MSTP_DMY_FSP_IP_CMTW(channel)          (0 >= channel) ? R_CMTW0->CMWSTR : R_CMTW1->CMWSTR

#define BSP_MSTP_REG_FSP_IP_TSU(channel)           R_SYSC_NS->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_TSU(channel)           (1U << (7U));
#define BSP_MSTP_DMY_FSP_IP_TSU(channel)           R_TSU->TSUSM;

#define BSP_MSTP_REG_FSP_IP_DOC(channel)           R_SYSC_NS->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_DOC(channel)           (1U << (8U));
#define BSP_MSTP_DMY_FSP_IP_DOC(channel)           R_DOC->DOCR

#define BSP_MSTP_REG_FSP_IP_CRC(channel)           *((0U == channel) ? &R_SYSC_NS->MSTPCRD : &R_SYSC_S->MSTPCRG)
#define BSP_MSTP_BIT_FSP_IP_CRC(channel)           ((0U == channel) ? (1U << (9U)) : (1U << (4U)));
#define BSP_MSTP_DMY_FSP_IP_CRC(channel)           (0 >= channel) ? R_CRC0->CRCDIR : R_CRC1->CRCDIR;

#define BSP_MSTP_REG_FSP_IP_CANFD(channel)         R_SYSC_NS->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_CANFD(channel)         (1U << (10U));
#define BSP_MSTP_DMY_FSP_IP_CANFD(channel)         R_CANFD->CFDGIPV;

#define BSP_MSTP_REG_FSP_IP_CKIO(channel)          R_SYSC_NS->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_CKIO(channel)          (1U << (11U));
#define BSP_MSTP_DMY_FSP_IP_CKIO(channel)          ;

#define BSP_MSTP_REG_FSP_IP_GMAC(channel)          R_SYSC_NS->MSTPCRE
#define BSP_MSTP_BIT_FSP_IP_GMAC(channel)          (1U);
#define BSP_MSTP_DMY_FSP_IP_GMAC(channel)          R_GMAC->MAC_Configuration

#define BSP_MSTP_REG_FSP_IP_ETHSW(channel)         R_SYSC_NS->MSTPCRE
#define BSP_MSTP_BIT_FSP_IP_ETHSW(channel)         (1U << (1U));
#define BSP_MSTP_DMY_FSP_IP_ETHSW(channel)         R_ETHSW->REVISION

#define BSP_MSTP_REG_FSP_IP_ESC(channel)           R_SYSC_NS->MSTPCRE
#define BSP_MSTP_BIT_FSP_IP_ESC(channel)           (1U << (2U));
#define BSP_MSTP_DMY_FSP_IP_ESC(channel)           R_ESC->TYPE;

#define BSP_MSTP_REG_FSP_IP_ETHSS(channel)         R_SYSC_NS->MSTPCRE
#define BSP_MSTP_BIT_FSP_IP_ETHSS(channel)         (1U << (3U));
#define BSP_MSTP_DMY_FSP_IP_ETHSS(channel)         R_ETHSS->PRCMD

#define BSP_MSTP_REG_FSP_IP_ENCIF(channel)         R_SYSC_NS->MSTPCRE
#define BSP_MSTP_BIT_FSP_IP_ENCIF(channel)         (1U << (4U));
#define BSP_MSTP_DMY_FSP_IP_ENCIF(channel)         ;

#define BSP_MSTP_REG_FSP_IP_USBHS(channel)         R_SYSC_NS->MSTPCRE
#define BSP_MSTP_BIT_FSP_IP_USBHS(channel)         (1U << (8U));
#define BSP_MSTP_DMY_FSP_IP_USBHS(channel)         R_USBHC->HCREVISION;

#define BSP_MSTP_REG_FSP_IP_TRACECLOCK(channel)    R_SYSC_S->MSTPCRF
#define BSP_MSTP_BIT_FSP_IP_TRACECLOCK(channel)    (1U << (0U));
#define BSP_MSTP_DMY_FSP_IP_TRACECLOCK(channel)    ;

#define BSP_MSTP_REG_FSP_IP_RTC(channel)           R_SYSC_S->MSTPCRG
#define BSP_MSTP_BIT_FSP_IP_RTC(channel)           (1U << (5U));
#define BSP_MSTP_DMY_FSP_IP_RTC(channel)           R_RTC->RTCA0CTL0;

#define BSP_MSTP_REG_FSP_IP_CLMA(channel)          R_SYSC_S->MSTPCRG
#define BSP_MSTP_BIT_FSP_IP_CLMA(channel)          ((2U >= channel) ? \
                                                    (1U << (9U + channel)) : (1U << (8U)));
#define BSP_MSTP_DMY_FSP_IP_CLMA(channel)          (0 >=                                                                 \
                                                    channel) ? R_CLMA0->CTL0 : ((1 >=                                    \
                                                                                 channel) ? R_CLMA1->CTL0 : ((2 >=       \
                                                                                                              channel) ? \
                                                                                                             R_CLMA2->   \
                                                                                                             CTL0 :      \
                                                                                                             R_CLMA3->   \
                                                                                                             CTL0));
#if BSP_FEATURE_BSP_SHOSTIF_SUPPORTED
 #define BSP_MSTP_REG_FSP_IP_SHOSTIF(channel)      R_SYSC_S->MSTPCRI
 #define BSP_MSTP_BIT_FSP_IP_SHOSTIF(channel)      (1U << (1U));
 #define BSP_MSTP_DMY_FSP_IP_SHOSTIF(channel)      R_SHOSTIF->CTRLR0;
#endif

#if (2 == BSP_FEATURE_BSP_AFMT_UNIT)
 #define BSP_MSTP_REG_FSP_IP_AFMT(channel)         *((0U == channel) ? &R_SYSC_NS->MSTPCRJ : &R_SYSC_NS->MSTPCRK)
 #define BSP_MSTP_BIT_FSP_IP_AFMT(channel)         (1U << (0U));
 #define BSP_MSTP_DMY_FSP_IP_AFMT(channel)         (0 == channel) ? R_AFMT0->COMMAND : R_AFMT1->COMMAND;
#endif

#if (2 == BSP_FEATURE_BSP_HDSL_UNIT)
 #define BSP_MSTP_REG_FSP_IP_HDSL(channel)         *((0U == channel) ? &R_SYSC_NS->MSTPCRJ : &R_SYSC_NS->MSTPCRK)
 #define BSP_MSTP_BIT_FSP_IP_HDSL(channel)         (1U << (1U));
 #define BSP_MSTP_DMY_FSP_IP_HDSL(channel)         (0 == channel) ? R_HDSLD0->SYS_CTRL : R_HDSLD1->SYS_CTRL;
#endif

#if (2 == BSP_FEATURE_BSP_BISS_UNIT)
 #define BSP_MSTP_REG_FSP_IP_BISS(channel)         *((0U == channel) ? &R_SYSC_NS->MSTPCRJ : &R_SYSC_NS->MSTPCRK)
 #define BSP_MSTP_BIT_FSP_IP_BISS(channel)         (1U << (2U));
 #define BSP_MSTP_DMY_FSP_IP_BISS(channel)         (0 == channel) ? R_BISS0->SCDATA[0].L : R_BISS1->SCDATA[0].L;
#endif

#if (2 == BSP_FEATURE_BSP_ENDAT_UNIT)
 #define BSP_MSTP_REG_FSP_IP_ENDAT(channel)        *((0U == channel) ? &R_SYSC_NS->MSTPCRJ : &R_SYSC_NS->MSTPCRK)
 #define BSP_MSTP_BIT_FSP_IP_ENDAT(channel)        (1U << (3U));
 #define BSP_MSTP_DMY_FSP_IP_ENDAT(channel)        (0 == channel) ? R_ENDAT0->SEND : R_ENDAT1->SEND;
#endif

#if BSP_FEATURE_BSP_ENCOUT_SUPPORTED
 #define BSP_MSTP_REG_FSP_IP_ENCOUT(channel)       R_SYSC_NS->MSTPCRL
 #define BSP_MSTP_BIT_FSP_IP_ENCOUT(channel)       (1U << (0U));
 #define BSP_MSTP_DMY_FSP_IP_ENCOUT(channel)       R_ENCOUT->CTL;
#endif

#if BSP_FEATURE_BSP_MSTP_CR52_CPU1_HAS_MSTPCRH
 #define BSP_MSTP_REG_FSP_IP_CPU1(channel)         R_SYSC_S->MSTPCRH
 #define BSP_MSTP_BIT_FSP_IP_CPU1(channel)         (1U << (1U));
 #define BSP_MSTP_DMY_FSP_IP_CPU1(channel)         ;
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
