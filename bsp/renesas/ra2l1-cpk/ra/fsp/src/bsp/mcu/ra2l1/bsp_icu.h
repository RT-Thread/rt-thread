/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef BSP_ICU_H
#define BSP_ICU_H

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA2L1
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events to be used with the IELSR register to link interrupt events to the NVIC
 * @note This list is device specific.
 * */
typedef enum e_icu_event_ra2l1
{
    ICU_EVENT_ACMPLP0_INT            = (0x09), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_ACMPLP1_INT            = (0x07), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_ADC0_COMPARE_MATCH     = (0x08), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_ADC0_COMPARE_MISMATCH  = (0x06), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_ADC0_SCAN_END          = (0x07), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_ADC0_SCAN_END_B        = (0x05), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_ADC0_WINDOW_A          = (0x05), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_ADC0_WINDOW_B          = (0x05), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_AES_RDREQ              = (0x12), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_AES_WRREQ              = (0x15), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_AGT0_COMPARE_A         = (0x16), // group0 (IELSR0/ 8/16/24)
    ICU_EVENT_AGT0_COMPARE_B         = (0x13), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_AGT0_INT               = (0x11), // group3 (IELSR3/11/19/27)
    ICU_EVENT_AGT1_COMPARE_A         = (0x03), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_AGT1_COMPARE_B         = (0x03), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_AGT1_INT               = (0x05), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_CAC_FREQUENCY_ERROR    = (0x0B), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_CAC_MEASUREMENT_END    = (0x08), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_CAC_OVERFLOW           = (0x08), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_CAN0_ERROR             = (0x0C), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_CAN0_FIFO_RX           = (0x0C), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_CAN0_FIFO_TX           = (0x09), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_CAN0_MAILBOX_RX        = (0x09), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_CAN0_MAILBOX_TX        = (0x0D), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_CTSU_END               = (0x07), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_CTSU_READ              = (0x07), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_CTSU_WRITE             = (0x09), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_DOC_INT                = (0x0A), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_DTC_COMPLETE           = (0x02), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_ELC_SOFTWARE_EVENT_0   = (0x0A), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_ELC_SOFTWARE_EVENT_1   = (0x0A), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_FCU_FRDYI              = (0x02), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT0_CAPTURE_COMPARE_A = (0x0E), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_GPT0_CAPTURE_COMPARE_B = (0x0D), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_GPT0_COMPARE_C         = (0x0C), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT0_COMPARE_D         = (0x0C), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_GPT0_COUNTER_OVERFLOW  = (0x0F), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_GPT0_COUNTER_UNDERFLOW = (0x0E), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_GPT1_CAPTURE_COMPARE_A = (0x19), // group0 (IELSR0/ 8/16/24)
    ICU_EVENT_GPT1_CAPTURE_COMPARE_B = (0x16), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_GPT1_COMPARE_C         = (0x14), // group2 (IELSR2/10/18/26)
    ICU_EVENT_GPT1_COMPARE_D         = (0x12), // group3 (IELSR3/11/19/27)
    ICU_EVENT_GPT1_COUNTER_OVERFLOW  = (0x18), // group4 (IELSR4/12/20/28)
    ICU_EVENT_GPT1_COUNTER_UNDERFLOW = (0x15), // group5 (IELSR5/13/21/29)
    ICU_EVENT_GPT2_CAPTURE_COMPARE_A = (0x10), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_GPT2_CAPTURE_COMPARE_B = (0x0F), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_GPT2_COMPARE_C         = (0x0D), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT2_COMPARE_D         = (0x0D), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_GPT2_COUNTER_OVERFLOW  = (0x0E), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT2_COUNTER_UNDERFLOW = (0x0E), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_GPT3_CAPTURE_COMPARE_A = (0x19), // group4 (IELSR4/12/20/28)
    ICU_EVENT_GPT3_CAPTURE_COMPARE_B = (0x16), // group5 (IELSR5/13/21/29)
    ICU_EVENT_GPT3_COMPARE_C         = (0x15), // group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT3_COMPARE_D         = (0x12), // group7 (IELSR7/15/23/31)
    ICU_EVENT_GPT3_COUNTER_OVERFLOW  = (0x1A), // group0 (IELSR0/ 8/16/24)
    ICU_EVENT_GPT3_COUNTER_UNDERFLOW = (0x17), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_GPT4_CAPTURE_COMPARE_A = (0x1B), // group0 (IELSR0/ 8/16/24)
    ICU_EVENT_GPT4_CAPTURE_COMPARE_B = (0x18), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_GPT4_COMPARE_C         = (0x15), // group2 (IELSR2/10/18/26)
    ICU_EVENT_GPT4_COMPARE_D         = (0x13), // group3 (IELSR3/11/19/27)
    ICU_EVENT_GPT4_COUNTER_OVERFLOW  = (0x16), // group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT4_COUNTER_UNDERFLOW = (0x13), // group7 (IELSR7/15/23/31)
    ICU_EVENT_GPT5_CAPTURE_COMPARE_A = (0x1A), // group4 (IELSR4/12/20/28)
    ICU_EVENT_GPT5_CAPTURE_COMPARE_B = (0x17), // group5 (IELSR5/13/21/29)
    ICU_EVENT_GPT5_COMPARE_C         = (0x17), // group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT5_COMPARE_D         = (0x14), // group7 (IELSR7/15/23/31)
    ICU_EVENT_GPT5_COUNTER_OVERFLOW  = (0x16), // group2 (IELSR2/10/18/26)
    ICU_EVENT_GPT5_COUNTER_UNDERFLOW = (0x14), // group3 (IELSR3/11/19/27)
    ICU_EVENT_GPT6_CAPTURE_COMPARE_A = (0x1C), // group0 (IELSR0/ 8/16/24)
    ICU_EVENT_GPT6_CAPTURE_COMPARE_B = (0x19), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_GPT6_COMPARE_C         = (0x17), // group2 (IELSR2/10/18/26)
    ICU_EVENT_GPT6_COMPARE_D         = (0x15), // group3 (IELSR3/11/19/27)
    ICU_EVENT_GPT6_COUNTER_OVERFLOW  = (0x18), // group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT6_COUNTER_UNDERFLOW = (0x15), // group7 (IELSR7/15/23/31)
    ICU_EVENT_GPT7_CAPTURE_COMPARE_A = (0x1B), // group4 (IELSR4/12/20/28)
    ICU_EVENT_GPT7_CAPTURE_COMPARE_B = (0x18), // group5 (IELSR5/13/21/29)
    ICU_EVENT_GPT7_COMPARE_C         = (0x19), // group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT7_COMPARE_D         = (0x16), // group7 (IELSR7/15/23/31)
    ICU_EVENT_GPT7_COUNTER_OVERFLOW  = (0x18), // group2 (IELSR2/10/18/26)
    ICU_EVENT_GPT7_COUNTER_UNDERFLOW = (0x16), // group3 (IELSR3/11/19/27)
    ICU_EVENT_GPT8_CAPTURE_COMPARE_A = (0x1D), // group0 (IELSR0/ 8/16/24)
    ICU_EVENT_GPT8_CAPTURE_COMPARE_B = (0x1A), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_GPT8_COMPARE_C         = (0x19), // group2 (IELSR2/10/18/26)
    ICU_EVENT_GPT8_COMPARE_D         = (0x17), // group3 (IELSR3/11/19/27)
    ICU_EVENT_GPT8_COUNTER_OVERFLOW  = (0x1A), // group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT8_COUNTER_UNDERFLOW = (0x17), // group7 (IELSR7/15/23/31)
    ICU_EVENT_GPT9_CAPTURE_COMPARE_A = (0x1C), // group4 (IELSR4/12/20/28)
    ICU_EVENT_GPT9_CAPTURE_COMPARE_B = (0x19), // group5 (IELSR5/13/21/29)
    ICU_EVENT_GPT9_COMPARE_C         = (0x1B), // group6 (IELSR6/14/22/30)
    ICU_EVENT_GPT9_COMPARE_D         = (0x18), // group7 (IELSR7/15/23/31)
    ICU_EVENT_GPT9_COUNTER_OVERFLOW  = (0x1A), // group2 (IELSR2/10/18/26)
    ICU_EVENT_GPT9_COUNTER_UNDERFLOW = (0x18), // group3 (IELSR3/11/19/27)
    ICU_EVENT_GPT_UVWEDGE            = (0x11), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_ICU_IRQ0               = (0x01), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_ICU_IRQ1               = (0x01), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_ICU_IRQ2               = (0x01), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_ICU_IRQ3               = (0x01), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_ICU_IRQ4               = (0x16), // group4 (IELSR4/12/20/28)
    ICU_EVENT_ICU_IRQ5               = (0x13), // group5 (IELSR5/13/21/29)
    ICU_EVENT_ICU_IRQ6               = (0x13), // group6 (IELSR6/14/22/30)
    ICU_EVENT_ICU_IRQ7               = (0x11), // group7 (IELSR7/15/23/31)
    ICU_EVENT_ICU_SNOOZE_CANCEL      = (0x03), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_IIC0_ERI               = (0x06), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_IIC0_RXI               = (0x0A), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_IIC0_TEI               = (0x06), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_IIC0_TXI               = (0x08), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_IIC0_WUI               = (0x0B), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_IIC1_ERI               = (0x14), // group5 (IELSR5/13/21/29)
    ICU_EVENT_IIC1_RXI               = (0x17), // group0 (IELSR0/ 8/16/24)
    ICU_EVENT_IIC1_TEI               = (0x17), // group4 (IELSR4/12/20/28)
    ICU_EVENT_IIC1_TXI               = (0x14), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_IOPORT_EVENT_1         = (0x15), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_IOPORT_EVENT_2         = (0x13), // group2 (IELSR2/10/18/26)
    ICU_EVENT_IWDT_UNDERFLOW         = (0x03), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_KEY_INT                = (0x18), // group0 (IELSR0/ 8/16/24)
    ICU_EVENT_LPM_SNOOZE_REQUEST     = (0x02), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_LVD_LVD1               = (0x04), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_LVD_LVD2               = (0x02), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_MOSC_STOP              = (0x14), // group6 (IELSR6/14/22/30)
    ICU_EVENT_POEG0_EVENT            = (0x0B), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_POEG1_EVENT            = (0x0B), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_RTC_ALARM              = (0x04), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_RTC_CARRY              = (0x04), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_RTC_PERIOD             = (0x04), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_SCI0_AM                = (0x13), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_SCI0_ERI               = (0x0F), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_SCI0_RXI               = (0x12), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_SCI0_TEI               = (0x0F), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_SCI0_TXI               = (0x10), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_SCI1_AM                = (0x1A), // group5 (IELSR5/13/21/29)
    ICU_EVENT_SCI1_ERI               = (0x19), // group3 (IELSR3/11/19/27)
    ICU_EVENT_SCI1_RXI               = (0x1E), // group0 (IELSR0/ 8/16/24)
    ICU_EVENT_SCI1_TEI               = (0x1B), // group2 (IELSR2/10/18/26)
    ICU_EVENT_SCI1_TXI               = (0x1B), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_SCI2_AM                = (0x1C), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_SCI2_ERI               = (0x19), // group7 (IELSR7/15/23/31)
    ICU_EVENT_SCI2_RXI               = (0x1D), // group4 (IELSR4/12/20/28)
    ICU_EVENT_SCI2_TEI               = (0x1C), // group6 (IELSR6/14/22/30)
    ICU_EVENT_SCI2_TXI               = (0x1B), // group5 (IELSR5/13/21/29)
    ICU_EVENT_SCI3_AM                = (0x1D), // group6 (IELSR6/14/22/30)
    ICU_EVENT_SCI3_ERI               = (0x1A), // group3 (IELSR3/11/19/27)
    ICU_EVENT_SCI3_RXI               = (0x1F), // group0 (IELSR0/ 8/16/24)
    ICU_EVENT_SCI3_TEI               = (0x1C), // group2 (IELSR2/10/18/26)
    ICU_EVENT_SCI3_TXI               = (0x1D), // group1 (IELSR1/ 9/17/25)
    ICU_EVENT_SCI9_AM                = (0x1B), // group3 (IELSR3/11/19/27)
    ICU_EVENT_SCI9_ERI               = (0x1A), // group7 (IELSR7/15/23/31)
    ICU_EVENT_SCI9_RXI               = (0x1E), // group4 (IELSR4/12/20/28)
    ICU_EVENT_SCI9_TEI               = (0x1E), // group6 (IELSR6/14/22/30)
    ICU_EVENT_SCI9_TXI               = (0x1C), // group5 (IELSR5/13/21/29)
    ICU_EVENT_SPI0_ERI               = (0x10), // group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31)
    ICU_EVENT_SPI0_IDLE              = (0x10), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_SPI0_RXI               = (0x14), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
    ICU_EVENT_SPI0_TEI               = (0x11), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_SPI0_TXI               = (0x11), // group1 (IELSR1/ 9/17/25) or group5 (IELSR5/13/21/29)
    ICU_EVENT_SPI1_ERI               = (0x1B), // group7 (IELSR7/15/23/31)
    ICU_EVENT_SPI1_IDLE              = (0x1D), // group2 (IELSR2/10/18/26)
    ICU_EVENT_SPI1_RXI               = (0x1F), // group4 (IELSR4/12/20/28)
    ICU_EVENT_SPI1_TEI               = (0x1F), // group6 (IELSR6/14/22/30)
    ICU_EVENT_SPI1_TXI               = (0x1D), // group5 (IELSR5/13/21/29)
    ICU_EVENT_TRNG_RDREQ             = (0x12), // group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30)
    ICU_EVENT_WDT_UNDERFLOW          = (0x06), // group0 (IELSR0/ 8/16/24) or group4 (IELSR4/12/20/28)
} icu_event_t;

/** @} (end addtogroup BSP_MCU_RA2L1) */

#endif
