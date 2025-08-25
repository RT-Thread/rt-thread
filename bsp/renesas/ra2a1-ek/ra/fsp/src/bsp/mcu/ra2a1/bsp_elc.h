/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_ELC_H
#define BSP_ELC_H

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA2A1
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/* UNCRUSTIFY-OFF */

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list is device specific.
 * */
typedef enum e_elc_event_ra2a1
{
    ELC_EVENT_NONE                          = (0x0),   // Link disabled
    ELC_EVENT_ICU_IRQ0                      = (0x001), // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1                      = (0x002), // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2                      = (0x003), // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3                      = (0x004), // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4                      = (0x005), // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5                      = (0x006), // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6                      = (0x007), // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7                      = (0x008), // External pin interrupt 7
    ELC_EVENT_DTC_COMPLETE                  = (0x009), // DTC transfer complete
    ELC_EVENT_DTC_END                       = (0x00A), // DTC transfer end
    ELC_EVENT_ICU_SNOOZE_CANCEL             = (0x00B), // Canceling from Snooze mode
    ELC_EVENT_FCU_FRDYI                     = (0x00C), // Flash ready interrupt
    ELC_EVENT_LVD_LVD1                      = (0x00D), // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2                      = (0x00E), // Voltage monitor 2 interrupt
    ELC_EVENT_CGC_MOSC_STOP                 = (0x00F), // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST            = (0x010), // Snooze entry
    ELC_EVENT_AGT0_INT                      = (0x011), // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A                = (0x012), // Compare match A
    ELC_EVENT_AGT0_COMPARE_B                = (0x013), // Compare match B
    ELC_EVENT_AGT1_INT                      = (0x014), // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A                = (0x015), // Compare match A
    ELC_EVENT_AGT1_COMPARE_B                = (0x016), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW                = (0x017), // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW                 = (0x018), // WDT underflow
    ELC_EVENT_RTC_ALARM                     = (0x019), // Alarm interrupt
    ELC_EVENT_RTC_PERIOD                    = (0x01A), // Periodic interrupt
    ELC_EVENT_RTC_CARRY                     = (0x01B), // Carry interrupt
    ELC_EVENT_ADC0_SCAN_END                 = (0x01C), // End of A/D scanning operation
    ELC_EVENT_ADC0_SCAN_END_B               = (0x01D), // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A                 = (0x01E), // Window A Compare match interrupt
    ELC_EVENT_ADC0_WINDOW_B                 = (0x01F), // Window B Compare match interrupt
    ELC_EVENT_ADC0_COMPARE_MATCH            = (0x020), // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH         = (0x021), // Compare mismatch
    ELC_EVENT_ACMPHS0_INT                   = (0x022), // High Speed Comparator channel 0 interrupt
    ELC_EVENT_ACMPLP0_INT                   = (0x023), // Low Power Comparator channel 0 interrupt
    ELC_EVENT_ACMPLP1_INT                   = (0x024), // Low Power Comparator channel 1 interrupt
    ELC_EVENT_USBFS_INT                     = (0x025), // USBFS interrupt
    ELC_EVENT_USBFS_RESUME                  = (0x026), // USBFS resume interrupt
    ELC_EVENT_IIC0_RXI                      = (0x027), // Receive data full
    ELC_EVENT_IIC0_TXI                      = (0x028), // Transmit data empty
    ELC_EVENT_IIC0_TEI                      = (0x029), // Transmit end
    ELC_EVENT_IIC0_ERI                      = (0x02A), // Transfer error
    ELC_EVENT_IIC0_WUI                      = (0x02B), // Wakeup interrupt
    ELC_EVENT_IIC1_RXI                      = (0x02C), // Receive data full
    ELC_EVENT_IIC1_TXI                      = (0x02D), // Transmit data empty
    ELC_EVENT_IIC1_TEI                      = (0x02E), // Transmit end
    ELC_EVENT_IIC1_ERI                      = (0x02F), // Transfer error
    ELC_EVENT_CTSU_WRITE                    = (0x030), // Write request interrupt
    ELC_EVENT_CTSU_READ                     = (0x031), // Measurement data transfer request interrupt
    ELC_EVENT_CTSU_END                      = (0x032), // Measurement end interrupt
    ELC_EVENT_KEY_INT                       = (0x033), // Key interrupt
    ELC_EVENT_DOC_INT                       = (0x034), // Data operation circuit interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR           = (0x035), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END           = (0x036), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW                  = (0x037), // Overflow interrupt
    ELC_EVENT_CAN0_ERROR                    = (0x038), // Error interrupt
    ELC_EVENT_CAN0_FIFO_RX                  = (0x039), // Receive FIFO interrupt
    ELC_EVENT_CAN0_FIFO_TX                  = (0x03A), // Transmit FIFO interrupt
    ELC_EVENT_CAN0_MAILBOX_RX               = (0x03B), // Reception complete interrupt
    ELC_EVENT_CAN0_MAILBOX_TX               = (0x03C), // Transmission complete interrupt
    ELC_EVENT_IOPORT_EVENT_1                = (0x03D), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2                = (0x03E), // Port 2 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0          = (0x03F), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1          = (0x040), // Software event 1
    ELC_EVENT_POEG0_EVENT                   = (0x041), // Port Output disable 0 interrupt
    ELC_EVENT_POEG1_EVENT                   = (0x042), // Port Output disable 1 interrupt
    ELC_EVENT_SDADC0_ADI                    = (0x043), // End of SD A/D conversion (type 1)
    ELC_EVENT_SDADC0_SCANEND                = (0x044), // End of SD A/D scan
    ELC_EVENT_SDADC0_CALIEND                = (0x045), // End of SD A/D A/D calibration
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A        = (0x046), // Capture/Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B        = (0x047), // Capture/Compare match B
    ELC_EVENT_GPT0_COMPARE_C                = (0x048), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D                = (0x049), // Compare match D
    ELC_EVENT_GPT0_COUNTER_OVERFLOW         = (0x04A), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW        = (0x04B), // Underflow
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A        = (0x04C), // Capture/Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B        = (0x04D), // Capture/Compare match B
    ELC_EVENT_GPT1_COMPARE_C                = (0x04E), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D                = (0x04F), // Compare match D
    ELC_EVENT_GPT1_COUNTER_OVERFLOW         = (0x050), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW        = (0x051), // Underflow
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A        = (0x052), // Capture/Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B        = (0x053), // Capture/Compare match B
    ELC_EVENT_GPT2_COMPARE_C                = (0x054), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D                = (0x055), // Compare match D
    ELC_EVENT_GPT2_COUNTER_OVERFLOW         = (0x056), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW        = (0x057), // Underflow
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A        = (0x058), // Capture/Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B        = (0x059), // Capture/Compare match B
    ELC_EVENT_GPT3_COMPARE_C                = (0x05A), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D                = (0x05B), // Compare match D
    ELC_EVENT_GPT3_COUNTER_OVERFLOW         = (0x05C), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW        = (0x05D), // Underflow
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A        = (0x05E), // Capture/Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B        = (0x05F), // Capture/Compare match B
    ELC_EVENT_GPT4_COMPARE_C                = (0x060), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D                = (0x061), // Compare match D
    ELC_EVENT_GPT4_COUNTER_OVERFLOW         = (0x062), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW        = (0x063), // Underflow
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A        = (0x064), // Capture/Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B        = (0x065), // Capture/Compare match B
    ELC_EVENT_GPT5_COMPARE_C                = (0x066), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D                = (0x067), // Compare match D
    ELC_EVENT_GPT5_COUNTER_OVERFLOW         = (0x068), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW        = (0x069), // Underflow
    ELC_EVENT_GPT6_CAPTURE_COMPARE_A        = (0x06A), // Capture/Compare match A
    ELC_EVENT_GPT6_CAPTURE_COMPARE_B        = (0x06B), // Capture/Compare match B
    ELC_EVENT_GPT6_COMPARE_C                = (0x06C), // Compare match C
    ELC_EVENT_GPT6_COMPARE_D                = (0x06D), // Compare match D
    ELC_EVENT_GPT6_COUNTER_OVERFLOW         = (0x06E), // Overflow
    ELC_EVENT_GPT6_COUNTER_UNDERFLOW        = (0x06F), // Underflow
    ELC_EVENT_OPS_UVW_EDGE                  = (0x070), // UVW edge event
    ELC_EVENT_SCI0_RXI                      = (0x071), // Receive data full
    ELC_EVENT_SCI0_TXI                      = (0x072), // Transmit data empty
    ELC_EVENT_SCI0_TEI                      = (0x073), // Transmit end
    ELC_EVENT_SCI0_ERI                      = (0x074), // Receive error
    ELC_EVENT_SCI0_AM                       = (0x075), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI               = (0x076), // Receive data full/Receive error
    ELC_EVENT_SCI1_RXI                      = (0x077), // Receive data full
    ELC_EVENT_SCI1_TXI                      = (0x078), // Transmit data empty
    ELC_EVENT_SCI1_TEI                      = (0x079), // Transmit end
    ELC_EVENT_SCI1_ERI                      = (0x07A), // Receive error
    ELC_EVENT_SCI1_AM                       = (0x07B), // Address match event
    ELC_EVENT_SCI9_RXI                      = (0x07C), // Receive data full
    ELC_EVENT_SCI9_TXI                      = (0x07D), // Transmit data empty
    ELC_EVENT_SCI9_TEI                      = (0x07E), // Transmit end
    ELC_EVENT_SCI9_ERI                      = (0x07F), // Receive error
    ELC_EVENT_SCI9_AM                       = (0x080), // Address match event
    ELC_EVENT_SPI0_RXI                      = (0x081), // Receive buffer full
    ELC_EVENT_SPI0_TXI                      = (0x082), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE                     = (0x083), // Idle
    ELC_EVENT_SPI0_ERI                      = (0x084), // Error
    ELC_EVENT_SPI0_TEI                      = (0x085), // Transmission complete event
    ELC_EVENT_SPI1_RXI                      = (0x086), // Receive buffer full
    ELC_EVENT_SPI1_TXI                      = (0x087), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE                     = (0x088), // Idle
    ELC_EVENT_SPI1_ERI                      = (0x089), // Error
    ELC_EVENT_SPI1_TEI                      = (0x08A), // Transmission complete event
    ELC_EVENT_AES_WRREQ                     = (0x08B), // AES Write Request
    ELC_EVENT_AES_RDREQ                     = (0x08C), // AES Read Request
    ELC_EVENT_TRNG_RDREQ                    = (0x08D)  // TRNG Read Request
} elc_event_t;

#define BSP_PRV_VECT_ENUM(event,group)  (ELC_ ## event)

#define ELC_PERIPHERAL_NUM    (23U)
#define BSP_OVERRIDE_ELC_PERIPHERAL_T
/** Possible peripherals to be linked to event signals
 * @note This list is device specific.
 * */
typedef enum e_elc_peripheral
{
    ELC_PERIPHERAL_GPT_A         = (0),
    ELC_PERIPHERAL_GPT_B         = (1),
    ELC_PERIPHERAL_GPT_C         = (2),
    ELC_PERIPHERAL_GPT_D         = (3),
    ELC_PERIPHERAL_ADC0          = (8),
    ELC_PERIPHERAL_ADC0_B        = (9),
    ELC_PERIPHERAL_DAC0          = (12),
    ELC_PERIPHERAL_IOPORT1       = (14),
    ELC_PERIPHERAL_IOPORT2       = (15),
    ELC_PERIPHERAL_CTSU          = (18),
    ELC_PERIPHERAL_DA8_0         = (19),
    ELC_PERIPHERAL_DA8_1         = (20),
    ELC_PERIPHERAL_SDADC0        = (22)
} elc_peripheral_t;

/** Positions of event link set registers (ELSRs) available on this MCU */
#define BSP_ELC_PERIPHERAL_MASK  (0x005CD30FU)

/* UNCRUSTIFY-ON */
/** @} (end addtogroup BSP_MCU_RA2A1) */

#endif
