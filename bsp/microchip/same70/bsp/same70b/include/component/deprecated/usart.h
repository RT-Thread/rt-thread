/**
 * \file
 * \brief This file is for deprecated macro constants
 *
 *  Used to mark macro constants as deprecate.
 *  Uses a macro 'DEPRECTAED' to give warnings during compilation (GCC >= 4.8)
 *
 *  \remark To use, add defines and put a DEPRECATED statement between the macro name and the value
 *
 *  \note This file is manually maintained
 */

#ifndef _SAME70_USART_COMPONENT_DEPRECATED_H_
#define _SAME70_USART_COMPONENT_DEPRECATED_H_

#ifndef DEPRECATED
#define _DEP_STRING(X) #X

/** \hideinitializer
 * \brief Macro deprecation mark
 *
 * Putting this in a macro definition will emit deprecation warning when given
 * macro is used (GCC 4.8)
 *
 *  \code{.c}
 *  #define OLD_MACRO DEPRECATED(OLD_MACRO, "deprecated <or any other text>") <value>
 *  \endcode
 *
 *  \warning Using these macros in #if statements will not work
 */
#if defined(__GNUC__) && __GNUC__*100 + __GNUC_MINOR__ >= 408
#define DEPRECATED(macro, message) _Pragma (_DEP_STRING(GCC warning message))
#else
#define DEPRECATED(macro, message)
#endif
#endif

/* deprecated defines added below here */
#define US_CR_DTRDIS_Msk DEPRECATED(US_CR_DTRDIS_Msk, "Using deprecated macro US_CR_DTRDIS_Msk") (_U_(0x1) << US_CR_DTRDIS_Pos) /**< (US_CR) Data Terminal Ready Disable Mask */
#define US_CR_DTRDIS_Pos DEPRECATED(US_CR_DTRDIS_Pos, "Using deprecated macro US_CR_DTRDIS_Pos") 17 /**< (US_CR) Data Terminal Ready Disable Position */
#define US_CR_DTRDIS DEPRECATED(US_CR_DTRDIS, "Using deprecated macro US_CR_DTRDIS") US_CR_DTRDIS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_DTRDIS_Msk instead */
#define US_CR_DTREN_Msk DEPRECATED(US_CR_DTREN_Msk, "Using deprecated macro US_CR_DTREN_Msk") (_U_(0x1) << US_CR_DTREN_Pos) /**< (US_CR) Data Terminal Ready Enable Mask */
#define US_CR_DTREN_Pos DEPRECATED(US_CR_DTREN_Pos, "Using deprecated macro US_CR_DTREN_Pos") 16 /**< (US_CR) Data Terminal Ready Enable Position */
#define US_CR_DTREN DEPRECATED(US_CR_DTREN, "Using deprecated macro US_CR_DTREN") US_CR_DTREN_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_DTREN_Msk instead */
#define US_CR_LINABT_Msk DEPRECATED(US_CR_LINABT_Msk, "Using deprecated macro US_CR_LINABT_Msk") (_U_(0x1) << US_CR_LINABT_Pos) /**< (US_CR) Abort LIN Transmission Mask */
#define US_CR_LINABT_Pos DEPRECATED(US_CR_LINABT_Pos, "Using deprecated macro US_CR_LINABT_Pos") 20 /**< (US_CR) Abort LIN Transmission Position */
#define US_CR_LINABT DEPRECATED(US_CR_LINABT, "Using deprecated macro US_CR_LINABT") US_CR_LINABT_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_LINABT_Msk instead */
#define US_CR_LINWKUP_Msk DEPRECATED(US_CR_LINWKUP_Msk, "Using deprecated macro US_CR_LINWKUP_Msk") (_U_(0x1) << US_CR_LINWKUP_Pos) /**< (US_CR) Send LIN Wakeup Signal Mask */
#define US_CR_LINWKUP_Pos DEPRECATED(US_CR_LINWKUP_Pos, "Using deprecated macro US_CR_LINWKUP_Pos") 21 /**< (US_CR) Send LIN Wakeup Signal Position */
#define US_CR_LINWKUP DEPRECATED(US_CR_LINWKUP, "Using deprecated macro US_CR_LINWKUP") US_CR_LINWKUP_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_LINWKUP_Msk instead */
#define US_CR_RETTO_Msk DEPRECATED(US_CR_RETTO_Msk, "Using deprecated macro US_CR_RETTO_Msk") (_U_(0x1) << US_CR_RETTO_Pos) /**< (US_CR) Start Time-out Immediately Mask */
#define US_CR_RETTO_Pos DEPRECATED(US_CR_RETTO_Pos, "Using deprecated macro US_CR_RETTO_Pos") 15 /**< (US_CR) Start Time-out Immediately Position */
#define US_CR_RETTO DEPRECATED(US_CR_RETTO, "Using deprecated macro US_CR_RETTO") US_CR_RETTO_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_RETTO_Msk instead */
#define US_CR_RSTIT_Msk DEPRECATED(US_CR_RSTIT_Msk, "Using deprecated macro US_CR_RSTIT_Msk") (_U_(0x1) << US_CR_RSTIT_Pos) /**< (US_CR) Reset Iterations Mask */
#define US_CR_RSTIT_Pos DEPRECATED(US_CR_RSTIT_Pos, "Using deprecated macro US_CR_RSTIT_Pos") 13 /**< (US_CR) Reset Iterations Position */
#define US_CR_RSTIT DEPRECATED(US_CR_RSTIT, "Using deprecated macro US_CR_RSTIT") US_CR_RSTIT_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_RSTIT_Msk instead */
#define US_CR_RSTNACK_Msk DEPRECATED(US_CR_RSTNACK_Msk, "Using deprecated macro US_CR_RSTNACK_Msk") (_U_(0x1) << US_CR_RSTNACK_Pos) /**< (US_CR) Reset Non Acknowledge Mask */
#define US_CR_RSTNACK_Pos DEPRECATED(US_CR_RSTNACK_Pos, "Using deprecated macro US_CR_RSTNACK_Pos") 14 /**< (US_CR) Reset Non Acknowledge Position */
#define US_CR_RSTNACK DEPRECATED(US_CR_RSTNACK, "Using deprecated macro US_CR_RSTNACK") US_CR_RSTNACK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_RSTNACK_Msk instead */
#define US_CR_RTSDIS_Msk DEPRECATED(US_CR_RTSDIS_Msk, "Using deprecated macro US_CR_RTSDIS_Msk") (_U_(0x1) << US_CR_RTSDIS_Pos) /**< (US_CR) Request to Send Pin Control Mask */
#define US_CR_RTSDIS_Pos DEPRECATED(US_CR_RTSDIS_Pos, "Using deprecated macro US_CR_RTSDIS_Pos") 19 /**< (US_CR) Request to Send Pin Control Position */
#define US_CR_RTSDIS DEPRECATED(US_CR_RTSDIS, "Using deprecated macro US_CR_RTSDIS") US_CR_RTSDIS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_RTSDIS_Msk instead */
#define US_CR_RTSEN_Msk DEPRECATED(US_CR_RTSEN_Msk, "Using deprecated macro US_CR_RTSEN_Msk") (_U_(0x1) << US_CR_RTSEN_Pos) /**< (US_CR) Request to Send Pin Control Mask */
#define US_CR_RTSEN_Pos DEPRECATED(US_CR_RTSEN_Pos, "Using deprecated macro US_CR_RTSEN_Pos") 18 /**< (US_CR) Request to Send Pin Control Position */
#define US_CR_RTSEN DEPRECATED(US_CR_RTSEN, "Using deprecated macro US_CR_RTSEN") US_CR_RTSEN_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_RTSEN_Msk instead */
#define US_CR_SENDA_Msk DEPRECATED(US_CR_SENDA_Msk, "Using deprecated macro US_CR_SENDA_Msk") (_U_(0x1) << US_CR_SENDA_Pos) /**< (US_CR) Send Address Mask */
#define US_CR_SENDA_Pos DEPRECATED(US_CR_SENDA_Pos, "Using deprecated macro US_CR_SENDA_Pos") 12 /**< (US_CR) Send Address Position */
#define US_CR_SENDA DEPRECATED(US_CR_SENDA, "Using deprecated macro US_CR_SENDA") US_CR_SENDA_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_SENDA_Msk instead */
#define US_CR_STPBRK_Msk DEPRECATED(US_CR_STPBRK_Msk, "Using deprecated macro US_CR_STPBRK_Msk") (_U_(0x1) << US_CR_STPBRK_Pos) /**< (US_CR) Stop Break Mask */
#define US_CR_STPBRK_Pos DEPRECATED(US_CR_STPBRK_Pos, "Using deprecated macro US_CR_STPBRK_Pos") 10 /**< (US_CR) Stop Break Position */
#define US_CR_STPBRK DEPRECATED(US_CR_STPBRK, "Using deprecated macro US_CR_STPBRK") US_CR_STPBRK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_STPBRK_Msk instead */
#define US_CR_STTBRK_Msk DEPRECATED(US_CR_STTBRK_Msk, "Using deprecated macro US_CR_STTBRK_Msk") (_U_(0x1) << US_CR_STTBRK_Pos) /**< (US_CR) Start Break Mask */
#define US_CR_STTBRK_Pos DEPRECATED(US_CR_STTBRK_Pos, "Using deprecated macro US_CR_STTBRK_Pos") 9 /**< (US_CR) Start Break Position */
#define US_CR_STTBRK DEPRECATED(US_CR_STTBRK, "Using deprecated macro US_CR_STTBRK") US_CR_STTBRK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_STTBRK_Msk instead */
#define US_CR_STTTO_Msk DEPRECATED(US_CR_STTTO_Msk, "Using deprecated macro US_CR_STTTO_Msk") (_U_(0x1) << US_CR_STTTO_Pos) /**< (US_CR) Clear TIMEOUT Flag and Start Time-out After Next Character Received Mask */
#define US_CR_STTTO_Pos DEPRECATED(US_CR_STTTO_Pos, "Using deprecated macro US_CR_STTTO_Pos") 11 /**< (US_CR) Clear TIMEOUT Flag and Start Time-out After Next Character Received Position */
#define US_CR_STTTO DEPRECATED(US_CR_STTTO, "Using deprecated macro US_CR_STTTO") US_CR_STTTO_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CR_STTTO_Msk instead */
#define US_CSR_CTSIC_Msk DEPRECATED(US_CSR_CTSIC_Msk, "Using deprecated macro US_CSR_CTSIC_Msk") (_U_(0x1) << US_CSR_CTSIC_Pos) /**< (US_CSR) Clear to Send Input Change Flag (cleared on read) Mask */
#define US_CSR_CTSIC_Pos DEPRECATED(US_CSR_CTSIC_Pos, "Using deprecated macro US_CSR_CTSIC_Pos") 19 /**< (US_CSR) Clear to Send Input Change Flag (cleared on read) Position */
#define US_CSR_CTSIC DEPRECATED(US_CSR_CTSIC, "Using deprecated macro US_CSR_CTSIC") US_CSR_CTSIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_CTSIC_Msk instead */
#define US_CSR_CTS_Msk DEPRECATED(US_CSR_CTS_Msk, "Using deprecated macro US_CSR_CTS_Msk") (_U_(0x1) << US_CSR_CTS_Pos) /**< (US_CSR) Image of CTS Input Mask */
#define US_CSR_CTS_Pos DEPRECATED(US_CSR_CTS_Pos, "Using deprecated macro US_CSR_CTS_Pos") 23 /**< (US_CSR) Image of CTS Input Position */
#define US_CSR_CTS DEPRECATED(US_CSR_CTS, "Using deprecated macro US_CSR_CTS") US_CSR_CTS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_CTS_Msk instead */
#define US_CSR_DCD_Msk DEPRECATED(US_CSR_DCD_Msk, "Using deprecated macro US_CSR_DCD_Msk") (_U_(0x1) << US_CSR_DCD_Pos) /**< (US_CSR) Image of DCD Input Mask */
#define US_CSR_DCD_Pos DEPRECATED(US_CSR_DCD_Pos, "Using deprecated macro US_CSR_DCD_Pos") 22 /**< (US_CSR) Image of DCD Input Position */
#define US_CSR_DCD DEPRECATED(US_CSR_DCD, "Using deprecated macro US_CSR_DCD") US_CSR_DCD_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_DCD_Msk instead */
#define US_CSR_DSR_Msk DEPRECATED(US_CSR_DSR_Msk, "Using deprecated macro US_CSR_DSR_Msk") (_U_(0x1) << US_CSR_DSR_Pos) /**< (US_CSR) Image of DSR Input Mask */
#define US_CSR_DSR_Pos DEPRECATED(US_CSR_DSR_Pos, "Using deprecated macro US_CSR_DSR_Pos") 21 /**< (US_CSR) Image of DSR Input Position */
#define US_CSR_DSR DEPRECATED(US_CSR_DSR, "Using deprecated macro US_CSR_DSR") US_CSR_DSR_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_DSR_Msk instead */
#define US_CSR_FRAME_Msk DEPRECATED(US_CSR_FRAME_Msk, "Using deprecated macro US_CSR_FRAME_Msk") (_U_(0x1) << US_CSR_FRAME_Pos) /**< (US_CSR) Framing Error (cleared by writing a one to bit US_CR.RSTSTA) Mask */
#define US_CSR_FRAME_Pos DEPRECATED(US_CSR_FRAME_Pos, "Using deprecated macro US_CSR_FRAME_Pos") 6 /**< (US_CSR) Framing Error (cleared by writing a one to bit US_CR.RSTSTA) Position */
#define US_CSR_FRAME DEPRECATED(US_CSR_FRAME, "Using deprecated macro US_CSR_FRAME") US_CSR_FRAME_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_FRAME_Msk instead */
#define US_CSR_ITER_Msk DEPRECATED(US_CSR_ITER_Msk, "Using deprecated macro US_CSR_ITER_Msk") (_U_(0x1) << US_CSR_ITER_Pos) /**< (US_CSR) Max Number of Repetitions Reached (cleared by writing a one to bit US_CR.RSTIT) Mask */
#define US_CSR_ITER_Pos DEPRECATED(US_CSR_ITER_Pos, "Using deprecated macro US_CSR_ITER_Pos") 10 /**< (US_CSR) Max Number of Repetitions Reached (cleared by writing a one to bit US_CR.RSTIT) Position */
#define US_CSR_ITER DEPRECATED(US_CSR_ITER, "Using deprecated macro US_CSR_ITER") US_CSR_ITER_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_ITER_Msk instead */
#define US_CSR_MANERR_Msk DEPRECATED(US_CSR_MANERR_Msk, "Using deprecated macro US_CSR_MANERR_Msk") (_U_(0x1) << US_CSR_MANERR_Pos) /**< (US_CSR) Manchester Error (cleared by writing a one to the bit US_CR.RSTSTA) Mask */
#define US_CSR_MANERR_Pos DEPRECATED(US_CSR_MANERR_Pos, "Using deprecated macro US_CSR_MANERR_Pos") 24 /**< (US_CSR) Manchester Error (cleared by writing a one to the bit US_CR.RSTSTA) Position */
#define US_CSR_MANERR DEPRECATED(US_CSR_MANERR, "Using deprecated macro US_CSR_MANERR") US_CSR_MANERR_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_MANERR_Msk instead */
#define US_CSR_NACK_Msk DEPRECATED(US_CSR_NACK_Msk, "Using deprecated macro US_CSR_NACK_Msk") (_U_(0x1) << US_CSR_NACK_Pos) /**< (US_CSR) Non Acknowledge Interrupt (cleared by writing a one to bit US_CR.RSTNACK) Mask */
#define US_CSR_NACK_Pos DEPRECATED(US_CSR_NACK_Pos, "Using deprecated macro US_CSR_NACK_Pos") 13 /**< (US_CSR) Non Acknowledge Interrupt (cleared by writing a one to bit US_CR.RSTNACK) Position */
#define US_CSR_NACK DEPRECATED(US_CSR_NACK, "Using deprecated macro US_CSR_NACK") US_CSR_NACK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_NACK_Msk instead */
#define US_CSR_PARE_Msk DEPRECATED(US_CSR_PARE_Msk, "Using deprecated macro US_CSR_PARE_Msk") (_U_(0x1) << US_CSR_PARE_Pos) /**< (US_CSR) Parity Error (cleared by writing a one to bit US_CR.RSTSTA) Mask */
#define US_CSR_PARE_Pos DEPRECATED(US_CSR_PARE_Pos, "Using deprecated macro US_CSR_PARE_Pos") 7 /**< (US_CSR) Parity Error (cleared by writing a one to bit US_CR.RSTSTA) Position */
#define US_CSR_PARE DEPRECATED(US_CSR_PARE, "Using deprecated macro US_CSR_PARE") US_CSR_PARE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_PARE_Msk instead */
#define US_CSR_RI_Msk DEPRECATED(US_CSR_RI_Msk, "Using deprecated macro US_CSR_RI_Msk") (_U_(0x1) << US_CSR_RI_Pos) /**< (US_CSR) Image of RI Input Mask */
#define US_CSR_RI_Pos DEPRECATED(US_CSR_RI_Pos, "Using deprecated macro US_CSR_RI_Pos") 20 /**< (US_CSR) Image of RI Input Position */
#define US_CSR_RI DEPRECATED(US_CSR_RI, "Using deprecated macro US_CSR_RI") US_CSR_RI_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_RI_Msk instead */
#define US_CSR_RXBRK_Msk DEPRECATED(US_CSR_RXBRK_Msk, "Using deprecated macro US_CSR_RXBRK_Msk") (_U_(0x1) << US_CSR_RXBRK_Pos) /**< (US_CSR) Break Received/End of Break (cleared by writing a one to bit US_CR.RSTSTA) Mask */
#define US_CSR_RXBRK_Pos DEPRECATED(US_CSR_RXBRK_Pos, "Using deprecated macro US_CSR_RXBRK_Pos") 2 /**< (US_CSR) Break Received/End of Break (cleared by writing a one to bit US_CR.RSTSTA) Position */
#define US_CSR_RXBRK DEPRECATED(US_CSR_RXBRK, "Using deprecated macro US_CSR_RXBRK") US_CSR_RXBRK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_RXBRK_Msk instead */
#define US_CSR_TIMEOUT_Msk DEPRECATED(US_CSR_TIMEOUT_Msk, "Using deprecated macro US_CSR_TIMEOUT_Msk") (_U_(0x1) << US_CSR_TIMEOUT_Pos) /**< (US_CSR) Receiver Time-out (cleared by writing a one to bit US_CR.STTTO) Mask */
#define US_CSR_TIMEOUT_Pos DEPRECATED(US_CSR_TIMEOUT_Pos, "Using deprecated macro US_CSR_TIMEOUT_Pos") 8 /**< (US_CSR) Receiver Time-out (cleared by writing a one to bit US_CR.STTTO) Position */
#define US_CSR_TIMEOUT DEPRECATED(US_CSR_TIMEOUT, "Using deprecated macro US_CSR_TIMEOUT") US_CSR_TIMEOUT_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_CSR_TIMEOUT_Msk instead */
#define US_FIDI_FI_DI_RATIO_Msk DEPRECATED(US_FIDI_FI_DI_RATIO_Msk, "Using deprecated macro US_FIDI_FI_DI_RATIO_Msk") (_U_(0xFFFF) << US_FIDI_FI_DI_RATIO_Pos) /**< (US_FIDI) FI Over DI Ratio Value Mask */
#define US_FIDI_FI_DI_RATIO_Pos DEPRECATED(US_FIDI_FI_DI_RATIO_Pos, "Using deprecated macro US_FIDI_FI_DI_RATIO_Pos") 0 /**< (US_FIDI) FI Over DI Ratio Value Position */
#define US_FIDI_FI_DI_RATIO(value) DEPRECATED(US_FIDI_FI_DI_RATIO, "Using deprecated macro US_FIDI_FI_DI_RATIO") (US_FIDI_FI_DI_RATIO_Msk & ((value) << US_FIDI_FI_DI_RATIO_Pos))
#define US_IDR_CTSIC_Msk DEPRECATED(US_IDR_CTSIC_Msk, "Using deprecated macro US_IDR_CTSIC_Msk") (_U_(0x1) << US_IDR_CTSIC_Pos) /**< (US_IDR) Clear to Send Input Change Interrupt Disable Mask */
#define US_IDR_CTSIC_Pos DEPRECATED(US_IDR_CTSIC_Pos, "Using deprecated macro US_IDR_CTSIC_Pos") 19 /**< (US_IDR) Clear to Send Input Change Interrupt Disable Position */
#define US_IDR_CTSIC DEPRECATED(US_IDR_CTSIC, "Using deprecated macro US_IDR_CTSIC") US_IDR_CTSIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IDR_CTSIC_Msk instead */
#define US_IDR_FRAME_Msk DEPRECATED(US_IDR_FRAME_Msk, "Using deprecated macro US_IDR_FRAME_Msk") (_U_(0x1) << US_IDR_FRAME_Pos) /**< (US_IDR) Framing Error Interrupt Disable Mask */
#define US_IDR_FRAME_Pos DEPRECATED(US_IDR_FRAME_Pos, "Using deprecated macro US_IDR_FRAME_Pos") 6 /**< (US_IDR) Framing Error Interrupt Disable Position */
#define US_IDR_FRAME DEPRECATED(US_IDR_FRAME, "Using deprecated macro US_IDR_FRAME") US_IDR_FRAME_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IDR_FRAME_Msk instead */
#define US_IDR_ITER_Msk DEPRECATED(US_IDR_ITER_Msk, "Using deprecated macro US_IDR_ITER_Msk") (_U_(0x1) << US_IDR_ITER_Pos) /**< (US_IDR) Max Number of Repetitions Reached Interrupt Disable Mask */
#define US_IDR_ITER_Pos DEPRECATED(US_IDR_ITER_Pos, "Using deprecated macro US_IDR_ITER_Pos") 10 /**< (US_IDR) Max Number of Repetitions Reached Interrupt Disable Position */
#define US_IDR_ITER DEPRECATED(US_IDR_ITER, "Using deprecated macro US_IDR_ITER") US_IDR_ITER_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IDR_ITER_Msk instead */
#define US_IDR_MANE_Msk DEPRECATED(US_IDR_MANE_Msk, "Using deprecated macro US_IDR_MANE_Msk") (_U_(0x1) << US_IDR_MANE_Pos) /**< (US_IDR) Manchester Error Interrupt Disable Mask */
#define US_IDR_MANE_Pos DEPRECATED(US_IDR_MANE_Pos, "Using deprecated macro US_IDR_MANE_Pos") 24 /**< (US_IDR) Manchester Error Interrupt Disable Position */
#define US_IDR_MANE DEPRECATED(US_IDR_MANE, "Using deprecated macro US_IDR_MANE") US_IDR_MANE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IDR_MANE_Msk instead */
#define US_IDR_NACK_Msk DEPRECATED(US_IDR_NACK_Msk, "Using deprecated macro US_IDR_NACK_Msk") (_U_(0x1) << US_IDR_NACK_Pos) /**< (US_IDR) Non Acknowledge Interrupt Disable Mask */
#define US_IDR_NACK_Pos DEPRECATED(US_IDR_NACK_Pos, "Using deprecated macro US_IDR_NACK_Pos") 13 /**< (US_IDR) Non Acknowledge Interrupt Disable Position */
#define US_IDR_NACK DEPRECATED(US_IDR_NACK, "Using deprecated macro US_IDR_NACK") US_IDR_NACK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IDR_NACK_Msk instead */
#define US_IDR_PARE_Msk DEPRECATED(US_IDR_PARE_Msk, "Using deprecated macro US_IDR_PARE_Msk") (_U_(0x1) << US_IDR_PARE_Pos) /**< (US_IDR) Parity Error Interrupt Disable Mask */
#define US_IDR_PARE_Pos DEPRECATED(US_IDR_PARE_Pos, "Using deprecated macro US_IDR_PARE_Pos") 7 /**< (US_IDR) Parity Error Interrupt Disable Position */
#define US_IDR_PARE DEPRECATED(US_IDR_PARE, "Using deprecated macro US_IDR_PARE") US_IDR_PARE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IDR_PARE_Msk instead */
#define US_IDR_RXBRK_Msk DEPRECATED(US_IDR_RXBRK_Msk, "Using deprecated macro US_IDR_RXBRK_Msk") (_U_(0x1) << US_IDR_RXBRK_Pos) /**< (US_IDR) Receiver Break Interrupt Disable Mask */
#define US_IDR_RXBRK_Pos DEPRECATED(US_IDR_RXBRK_Pos, "Using deprecated macro US_IDR_RXBRK_Pos") 2 /**< (US_IDR) Receiver Break Interrupt Disable Position */
#define US_IDR_RXBRK DEPRECATED(US_IDR_RXBRK, "Using deprecated macro US_IDR_RXBRK") US_IDR_RXBRK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IDR_RXBRK_Msk instead */
#define US_IDR_TIMEOUT_Msk DEPRECATED(US_IDR_TIMEOUT_Msk, "Using deprecated macro US_IDR_TIMEOUT_Msk") (_U_(0x1) << US_IDR_TIMEOUT_Pos) /**< (US_IDR) Time-out Interrupt Disable Mask */
#define US_IDR_TIMEOUT_Pos DEPRECATED(US_IDR_TIMEOUT_Pos, "Using deprecated macro US_IDR_TIMEOUT_Pos") 8 /**< (US_IDR) Time-out Interrupt Disable Position */
#define US_IDR_TIMEOUT DEPRECATED(US_IDR_TIMEOUT, "Using deprecated macro US_IDR_TIMEOUT") US_IDR_TIMEOUT_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IDR_TIMEOUT_Msk instead */
#define US_IER_CTSIC_Msk DEPRECATED(US_IER_CTSIC_Msk, "Using deprecated macro US_IER_CTSIC_Msk") (_U_(0x1) << US_IER_CTSIC_Pos) /**< (US_IER) Clear to Send Input Change Interrupt Enable Mask */
#define US_IER_CTSIC_Pos DEPRECATED(US_IER_CTSIC_Pos, "Using deprecated macro US_IER_CTSIC_Pos") 19 /**< (US_IER) Clear to Send Input Change Interrupt Enable Position */
#define US_IER_CTSIC DEPRECATED(US_IER_CTSIC, "Using deprecated macro US_IER_CTSIC") US_IER_CTSIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_CTSIC_Msk instead */
#define US_IER_DCDIC_Msk DEPRECATED(US_IER_DCDIC_Msk, "Using deprecated macro US_IER_DCDIC_Msk") (_U_(0x1) << US_IER_DCDIC_Pos) /**< (US_IER) Data Carrier Detect Input Change Interrupt Enable Mask */
#define US_IER_DCDIC_Pos DEPRECATED(US_IER_DCDIC_Pos, "Using deprecated macro US_IER_DCDIC_Pos") 18 /**< (US_IER) Data Carrier Detect Input Change Interrupt Enable Position */
#define US_IER_DCDIC DEPRECATED(US_IER_DCDIC, "Using deprecated macro US_IER_DCDIC") US_IER_DCDIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_DCDIC_Msk instead */
#define US_IER_DSRIC_Msk DEPRECATED(US_IER_DSRIC_Msk, "Using deprecated macro US_IER_DSRIC_Msk") (_U_(0x1) << US_IER_DSRIC_Pos) /**< (US_IER) Data Set Ready Input Change Enable Mask */
#define US_IER_DSRIC_Pos DEPRECATED(US_IER_DSRIC_Pos, "Using deprecated macro US_IER_DSRIC_Pos") 17 /**< (US_IER) Data Set Ready Input Change Enable Position */
#define US_IER_DSRIC DEPRECATED(US_IER_DSRIC, "Using deprecated macro US_IER_DSRIC") US_IER_DSRIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_DSRIC_Msk instead */
#define US_IER_FRAME_Msk DEPRECATED(US_IER_FRAME_Msk, "Using deprecated macro US_IER_FRAME_Msk") (_U_(0x1) << US_IER_FRAME_Pos) /**< (US_IER) Framing Error Interrupt Enable Mask */
#define US_IER_FRAME_Pos DEPRECATED(US_IER_FRAME_Pos, "Using deprecated macro US_IER_FRAME_Pos") 6 /**< (US_IER) Framing Error Interrupt Enable Position */
#define US_IER_FRAME DEPRECATED(US_IER_FRAME, "Using deprecated macro US_IER_FRAME") US_IER_FRAME_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_FRAME_Msk instead */
#define US_IER_ITER_Msk DEPRECATED(US_IER_ITER_Msk, "Using deprecated macro US_IER_ITER_Msk") (_U_(0x1) << US_IER_ITER_Pos) /**< (US_IER) Max number of Repetitions Reached Interrupt Enable Mask */
#define US_IER_ITER_Pos DEPRECATED(US_IER_ITER_Pos, "Using deprecated macro US_IER_ITER_Pos") 10 /**< (US_IER) Max number of Repetitions Reached Interrupt Enable Position */
#define US_IER_ITER DEPRECATED(US_IER_ITER, "Using deprecated macro US_IER_ITER") US_IER_ITER_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_ITER_Msk instead */
#define US_IER_MANE_Msk DEPRECATED(US_IER_MANE_Msk, "Using deprecated macro US_IER_MANE_Msk") (_U_(0x1) << US_IER_MANE_Pos) /**< (US_IER) Manchester Error Interrupt Enable Mask */
#define US_IER_MANE_Pos DEPRECATED(US_IER_MANE_Pos, "Using deprecated macro US_IER_MANE_Po") 24 /**< (US_IER) Manchester Error Interrupt Enable Position */
#define US_IER_MANE DEPRECATED(US_IER_MANE, "Using deprecated macro US_IER_MANE") US_IER_MANE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_MANE_Msk instead */
#define US_IER_NACK_Msk DEPRECATED(US_IER_NACK_Msk, "Using deprecated macro US_IER_NACK_Msk") (_U_(0x1) << US_IER_NACK_Pos) /**< (US_IER) Non Acknowledge Interrupt Enable Mask */
#define US_IER_NACK_Pos DEPRECATED(US_IER_NACK_Pos, "Using deprecated macro US_IER_NACK_Pos") 13 /**< (US_IER) Non Acknowledge Interrupt Enable Position */
#define US_IER_NACK DEPRECATED(US_IER_NACK, "Using deprecated macro US_IER_NAC") US_IER_NACK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_NACK_Msk instead */
#define US_IER_PARE_Msk DEPRECATED(US_IER_PARE_Msk, "Using deprecated macro US_IER_PARE_Msk") (_U_(0x1) << US_IER_PARE_Pos) /**< (US_IER) Parity Error Interrupt Enable Mask */
#define US_IER_PARE_Pos DEPRECATED(US_IER_PARE_Pos, "Using deprecated macro US_IER_PARE_Pos") 7 /**< (US_IER) Parity Error Interrupt Enable Position */
#define US_IER_PARE DEPRECATED(US_IER_PARE, "Using deprecated macro US_IER_PARE") US_IER_PARE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_PARE_Msk instead */
#define US_IER_RIIC_Msk DEPRECATED(US_IER_RIIC_Msk, "Using deprecated macro US_IER_RIIC_Msk") (_U_(0x1) << US_IER_RIIC_Pos) /**< (US_IER) Ring Indicator Input Change Enable Mask */
#define US_IER_RIIC_Pos DEPRECATED(US_IER_RIIC_Pos, "Using deprecated macro US_IER_RIIC_Pos") 16 /**< (US_IER) Ring Indicator Input Change Enable Position */
#define US_IER_RIIC DEPRECATED(US_IER_RIIC, "Using deprecated macro US_IER_RIIC") US_IER_RIIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_RIIC_Msk instead */
#define US_IER_RXBRK_Msk DEPRECATED(US_IER_RXBRK_Msk, "Using deprecated macro US_IER_RXBRK_Msk") (_U_(0x1) << US_IER_RXBRK_Pos) /**< (US_IER) Receiver Break Interrupt Enable Mask */
#define US_IER_RXBRK_Pos DEPRECATED(US_IER_RXBRK_Pos, "Using deprecated macro US_IER_RXBRK_Pos") 2 /**< (US_IER) Receiver Break Interrupt Enable Position */
#define US_IER_RXBRK DEPRECATED(US_IER_RXBRK, "Using deprecated macro US_IER_RXBRK") US_IER_RXBRK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_RXBRK_Msk instead */
#define US_IER_TIMEOUT_Msk DEPRECATED(US_IER_TIMEOUT_Msk, "Using deprecated macro US_IER_TIMEOUT_Msk") (_U_(0x1) << US_IER_TIMEOUT_Pos) /**< (US_IER) Time-out Interrupt Enable Mask */
#define US_IER_TIMEOUT_Pos DEPRECATED(US_IER_TIMEOUT_Pos, "Using deprecated macro US_IER_TIMEOUT_Pos") 8 /**< (US_IER) Time-out Interrupt Enable Position */
#define US_IER_TIMEOUT DEPRECATED(US_IER_TIMEOUT, "Using deprecated macro US_IER_TIMEOUT") US_IER_TIMEOUT_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IER_TIMEOUT_Msk instead */
#define US_IMR_CTSIC_Msk DEPRECATED(US_IMR_CTSIC_Msk, "Using deprecated macro US_IMR_CTSIC_Msk") (_U_(0x1) << US_IMR_CTSIC_Pos) /**< (US_IMR) Clear to Send Input Change Interrupt Mask Mask */
#define US_IMR_CTSIC_Pos DEPRECATED(US_IMR_CTSIC_Pos, "Using deprecated macro US_IMR_CTSIC_Pos") 19 /**< (US_IMR) Clear to Send Input Change Interrupt Mask Position */
#define US_IMR_CTSIC DEPRECATED(US_IMR_CTSIC, "Using deprecated macro US_IMR_CTSIC") US_IMR_CTSIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IMR_CTSIC_Msk instead */
#define US_IMR_FRAME_Msk DEPRECATED(US_IMR_FRAME_Msk, "Using deprecated macro US_IMR_FRAME_Msk") (_U_(0x1) << US_IMR_FRAME_Pos) /**< (US_IMR) Framing Error Interrupt Mask Mask */
#define US_IMR_FRAME_Pos DEPRECATED(US_IMR_FRAME_Pos, "Using deprecated macro US_IMR_FRAME_Pos") 6 /**< (US_IMR) Framing Error Interrupt Mask Position */
#define US_IMR_FRAME DEPRECATED(US_IMR_FRAME, "Using deprecated macro US_IMR_FRAME") US_IMR_FRAME_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IMR_FRAME_Msk instead */
#define US_IMR_ITER_Msk DEPRECATED(US_IMR_ITER_Msk, "Using deprecated macro US_IMR_ITER_Msk") (_U_(0x1) << US_IMR_ITER_Pos) /**< (US_IMR) Max Number of Repetitions Reached Interrupt Mask Mask */
#define US_IMR_ITER_Pos DEPRECATED(US_IMR_ITER_Pos, "Using deprecated macro US_IMR_ITER_Pos") 10 /**< (US_IMR) Max Number of Repetitions Reached Interrupt Mask Position */
#define US_IMR_ITER DEPRECATED(US_IMR_ITER, "Using deprecated macro US_IMR_ITER") US_IMR_ITER_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IMR_ITER_Msk instead */
#define US_IMR_MANE_Msk DEPRECATED(US_IMR_MANE_Msk, "Using deprecated macro US_IMR_MANE_Msk") (_U_(0x1) << US_IMR_MANE_Pos) /**< (US_IMR) Manchester Error Interrupt Mask Mask */
#define US_IMR_MANE_Pos DEPRECATED(US_IMR_MANE_Pos, "Using deprecated macro US_IMR_MANE_Pos") 24 /**< (US_IMR) Manchester Error Interrupt Mask Position */
#define US_IMR_MANE DEPRECATED(US_IMR_MANE, "Using deprecated macro US_IMR_MANE") US_IMR_MANE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IMR_MANE_Msk instead */
#define US_IMR_NACK_Msk DEPRECATED(US_IMR_NACK_Msk, "Using deprecated macro US_IMR_NACK_Msk") (_U_(0x1) << US_IMR_NACK_Pos) /**< (US_IMR) Non Acknowledge Interrupt Mask Mask */
#define US_IMR_NACK_Pos DEPRECATED(US_IMR_NACK_Pos, "Using deprecated macro US_IMR_NACK_Pos") 13 /**< (US_IMR) Non Acknowledge Interrupt Mask Position */
#define US_IMR_NACK DEPRECATED(US_IMR_NACK, "Using deprecated macro US_IMR_NACK") US_IMR_NACK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IMR_NACK_Msk instead */
#define US_IMR_PARE_Msk DEPRECATED(US_IMR_PARE_Msk, "Using deprecated macro US_IMR_PARE_Msk") (_U_(0x1) << US_IMR_PARE_Pos) /**< (US_IMR) Parity Error Interrupt Mask Mask */
#define US_IMR_PARE_Pos DEPRECATED(US_IMR_PARE_Pos, "Using deprecated macro US_IMR_PARE_Pos") 7 /**< (US_IMR) Parity Error Interrupt Mask Position */
#define US_IMR_PARE DEPRECATED(US_IMR_PARE, "Using deprecated macro US_IMR_PARE") US_IMR_PARE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IMR_PARE_Msk instead */
#define US_IMR_RXBRK_Msk DEPRECATED(US_IMR_RXBRK_Msk, "Using deprecated macro US_IMR_RXBRK_Msk") (_U_(0x1) << US_IMR_RXBRK_Pos) /**< (US_IMR) Receiver Break Interrupt Mask Mask */
#define US_IMR_RXBRK_Pos DEPRECATED(US_IMR_RXBRK_Pos, "Using deprecated macro US_IMR_RXBRK_Pos") 2 /**< (US_IMR) Receiver Break Interrupt Mask Position */
#define US_IMR_RXBRK DEPRECATED(US_IMR_RXBRK, "Using deprecated macro US_IMR_RXBRK") US_IMR_RXBRK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IMR_RXBRK_Msk instead */
#define US_IMR_TIMEOUT_Msk DEPRECATED(US_IMR_TIMEOUT_Msk, "Using deprecated macro US_IMR_TIMEOUT_Msk") (_U_(0x1) << US_IMR_TIMEOUT_Pos) /**< (US_IMR) Time-out Interrupt Mask Mask */
#define US_IMR_TIMEOUT_Pos DEPRECATED(US_IMR_TIMEOUT_Pos, "Using deprecated macro US_IMR_TIMEOUT_Pos") 8 /**< (US_IMR) Time-out Interrupt Mask Position */
#define US_IMR_TIMEOUT DEPRECATED(US_IMR_TIMEOUT, "Using deprecated macro US_IMR_TIMEOUT") US_IMR_TIMEOUT_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_IMR_TIMEOUT_Msk instead */
#define US_MR_CHMODE_Msk DEPRECATED(US_MR_CHMODE_Msk, "Using deprecated macro US_MR_CHMODE_Msk") (_U_(0x3) << US_MR_CHMODE_Pos) /**< (US_MR) Channel Mode Mask */
#define US_MR_CHMODE_Pos DEPRECATED(US_MR_CHMODE_Pos, "Using deprecated macro US_MR_CHMODE_Pos") 14 /**< (US_MR) Channel Mode Position */
#define US_MR_CHMODE(value) DEPRECATED(US_MR_CHMODE, "Using deprecated macro US_MR_CHMODE") (US_MR_CHMODE_Msk & ((value) << US_MR_CHMODE_Pos))
#define US_MR_DSNACK_Msk DEPRECATED(US_MR_DSNACK_Msk, "Using deprecated macro US_MR_DSNACK_Msk") (_U_(0x1) << US_MR_DSNACK_Pos) /**< (US_MR) Disable Successive NACK Mask */
#define US_MR_DSNACK_Pos DEPRECATED(US_MR_DSNACK_Pos, "Using deprecated macro US_MR_DSNACK_Pos") 21 /**< (US_MR) Disable Successive NACK Position */
#define US_MR_DSNACK DEPRECATED(US_MR_DSNACK, "Using deprecated macro US_MR_DSNACK") US_MR_DSNACK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_DSNACK_Msk instead */
#define US_MR_FILTER_Msk DEPRECATED(US_MR_FILTER_Msk, "Using deprecated macro US_MR_FILTER_Msk") (_U_(0x1) << US_MR_FILTER_Pos) /**< (US_MR) Receive Line Filter Mask */
#define US_MR_FILTER_Pos DEPRECATED(US_MR_FILTER_Pos, "Using deprecated macro US_MR_FILTER_Pos") 28 /**< (US_MR) Receive Line Filter Position */
#define US_MR_FILTER DEPRECATED(US_MR_FILTER, "Using deprecated macro US_MR_FILTER") US_MR_FILTER_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_FILTER_Msk instead */
#define US_MR_INACK_Msk DEPRECATED(US_MR_INACK_Msk, "Using deprecated macro US_MR_INACK_Msk") (_U_(0x1) << US_MR_INACK_Pos) /**< (US_MR) Inhibit Non Acknowledge Mask */
#define US_MR_INACK_Pos DEPRECATED(US_MR_INACK_Pos, "Using deprecated macro US_MR_INACK_Pos") 20 /**< (US_MR) Inhibit Non Acknowledge Position */
#define US_MR_INACK DEPRECATED(US_MR_INACK, "Using deprecated macro US_MR_INACK") US_MR_INACK_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_INACK_Msk instead */
#define US_MR_INVDATA_Msk DEPRECATED(US_MR_INVDATA_Msk, "Using deprecated macro US_MR_INVDATA_Msk") (_U_(0x1) << US_MR_INVDATA_Pos) /**< (US_MR) Inverted Data Mask */
#define US_MR_INVDATA_Pos DEPRECATED(US_MR_INVDATA_Pos, "Using deprecated macro US_MR_INVDATA_Pos") 23 /**< (US_MR) Inverted Data Position */
#define US_MR_INVDATA DEPRECATED(US_MR_INVDATA, "Using deprecated macro US_MR_INVDATA") US_MR_INVDATA_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_INVDATA_Msk instead */
#define US_MR_MAN_Msk DEPRECATED(US_MR_MAN_Msk, "Using deprecated macro US_MR_MAN_Msk") (_U_(0x1) << US_MR_MAN_Pos) /**< (US_MR) Manchester Encoder/Decoder Enable Mask */
#define US_MR_MAN_Pos DEPRECATED(US_MR_MAN_Pos, "Using deprecated macro US_MR_MAN_Pos") 29 /**< (US_MR) Manchester Encoder/Decoder Enable Position */
#define US_MR_MAN DEPRECATED(US_MR_MAN, "Using deprecated macro US_MR_MAN") US_MR_MAN_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_MAN_Msk instead */
#define US_MR_MAX_ITERATION_Msk DEPRECATED(US_MR_MAX_ITERATION_Msk, "Using deprecated macro US_MR_MAX_ITERATION_Msk") (_U_(0x7) << US_MR_MAX_ITERATION_Pos) /**< (US_MR) Maximum Number of Automatic Iteration Mask */
#define US_MR_MAX_ITERATION_Pos DEPRECATED(US_MR_MAX_ITERATION_Pos, "Using deprecated macro US_MR_MAX_ITERATION_Pos") 24 /**< (US_MR) Maximum Number of Automatic Iteration Position */
#define US_MR_MAX_ITERATION(value) DEPRECATED(US_MR_MAX_ITERATION, "Using deprecated macro US_MR_MAX_ITERATION") (US_MR_MAX_ITERATION_Msk & ((value) << US_MR_MAX_ITERATION_Pos))
#define US_MR_MODE9_Msk DEPRECATED(US_MR_MODE9_Msk, "Using deprecated macro US_MR_MODE9_Msk") (_U_(0x1) << US_MR_MODE9_Pos) /**< (US_MR) 9-bit Character Length Mask */
#define US_MR_MODE9_Pos DEPRECATED(US_MR_MODE9_Pos, "Using deprecated macro US_MR_MODE9_Pos") 17 /**< (US_MR) 9-bit Character Length Position */
#define US_MR_MODE9 DEPRECATED(US_MR_MODE9, "Using deprecated macro US_MR_MODE9") US_MR_MODE9_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_MODE9_Msk instead */
#define US_MR_MODSYNC_Msk DEPRECATED(US_MR_MODSYNC_Msk, "Using deprecated macro US_MR_MODSYNC_Msk") (_U_(0x1) << US_MR_MODSYNC_Pos) /**< (US_MR) Manchester Synchronization Mode Mask */
#define US_MR_MODSYNC_Pos DEPRECATED(US_MR_MODSYNC_Pos, "Using deprecated macro US_MR_MODSYNC_Pos") 30 /**< (US_MR) Manchester Synchronization Mode Position */
#define US_MR_MODSYNC DEPRECATED(US_MR_MODSYNC, "Using deprecated macro US_MR_MODSYNC") US_MR_MODSYNC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_MODSYNC_Msk instead */
#define US_MR_MSBF_Msk DEPRECATED(US_MR_MSBF_Msk, "Using deprecated macro US_MR_MSBF_Msk") (_U_(0x1) << US_MR_MSBF_Pos) /**< (US_MR) Bit Order Mask */
#define US_MR_MSBF_Pos DEPRECATED(US_MR_MSBF_Pos, "Using deprecated macro US_MR_MSBF_Pos") 16 /**< (US_MR) Bit Order Position */
#define US_MR_MSBF DEPRECATED(US_MR_MSBF, "Using deprecated macro US_MR_MSBF") US_MR_MSBF_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_MSBF_Msk instead */
#define US_MR_NBSTOP_Msk DEPRECATED(US_MR_NBSTOP_Msk, "Using deprecated macro US_MR_NBSTOP_Msk") (_U_(0x3) << US_MR_NBSTOP_Pos) /**< (US_MR) Number of Stop Bits Mask */
#define US_MR_NBSTOP_Pos DEPRECATED(US_MR_NBSTOP_Pos, "Using deprecated macro US_MR_NBSTOP_Pos") 12 /**< (US_MR) Number of Stop Bits Position */
#define US_MR_NBSTOP(value) DEPRECATED(US_MR_NBSTOP, "Using deprecated macro US_MR_NBSTOP") (US_MR_NBSTOP_Msk & ((value) << US_MR_NBSTOP_Pos))
#define US_MR_ONEBIT_Msk DEPRECATED(US_MR_ONEBIT_Msk, "Using deprecated macro US_MR_ONEBIT_Msk") (_U_(0x1) << US_MR_ONEBIT_Pos) /**< (US_MR) Start Frame Delimiter Selector Mask */
#define US_MR_ONEBIT_Pos DEPRECATED(US_MR_ONEBIT_Pos, "Using deprecated macro US_MR_ONEBIT_Pos") 31 /**< (US_MR) Start Frame Delimiter Selector Position */
#define US_MR_ONEBIT DEPRECATED(US_MR_ONEBIT, "Using deprecated macro US_MR_ONEBIT") US_MR_ONEBIT_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_ONEBIT_Msk instead */
#define US_MR_OVER_Msk DEPRECATED(US_MR_OVER_Msk, "Using deprecated macro US_MR_OVER_Msk") (_U_(0x1) << US_MR_OVER_Pos) /**< (US_MR) Oversampling Mode Mask */
#define US_MR_OVER_Pos DEPRECATED(US_MR_OVER_Pos, "Using deprecated macro US_MR_OVER_Pos") 19 /**< (US_MR) Oversampling Mode Position */
#define US_MR_OVER DEPRECATED(US_MR_OVER, "Using deprecated macro US_MR_OVER") US_MR_OVER_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_OVER_Msk instead */
#define US_MR_PAR_Msk DEPRECATED(US_MR_PAR_Msk, "Using deprecated macro US_MR_PAR_Msk") (_U_(0x7) << US_MR_PAR_Pos) /**< (US_MR) Parity Type Mask */
#define US_MR_PAR_Pos DEPRECATED(US_MR_PAR_Pos, "Using deprecated macro US_MR_PAR_Pos") 9 /**< (US_MR) Parity Type Position */
#define US_MR_PAR(value) DEPRECATED(US_MR_PAR, "Using deprecated macro US_MR_PAR") (US_MR_PAR_Msk & ((value) << US_MR_PAR_Pos))
#define US_MR_SYNC_Msk DEPRECATED(US_MR_SYNC_Msk, "Using deprecated macro US_MR_SYNC_Msk") (_U_(0x1) << US_MR_SYNC_Pos) /**< (US_MR) Synchronous Mode Select Mask */
#define US_MR_SYNC_Pos DEPRECATED(US_MR_SYNC_Pos, "Using deprecated macro US_MR_SYNC_Pos") 8 /**< (US_MR) Synchronous Mode Select Position */
#define US_MR_SYNC DEPRECATED(US_MR_SYNC, "Using deprecated macro US_MR_SYNC") US_MR_SYNC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_SYNC_Msk instead */
#define US_MR_VAR_SYNC_Msk DEPRECATED(US_MR_VAR_SYNC_Msk, "Using deprecated macro US_MR_VAR_SYNC_Msk") (_U_(0x1) << US_MR_VAR_SYNC_Pos) /**< (US_MR) Variable Synchronization of Command/Data Sync Start Frame Delimiter Mask */
#define US_MR_VAR_SYNC_Pos DEPRECATED(US_MR_VAR_SYNC_Pos, "Using deprecated macro US_MR_VAR_SYNC_Pos") 22 /**< (US_MR) Variable Synchronization of Command/Data Sync Start Frame Delimiter Position */
#define US_MR_VAR_SYNC DEPRECATED(US_MR_VAR_SYNC, "Using deprecated macro US_MR_VAR_SYNC") US_MR_VAR_SYNC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use US_MR_VAR_SYNC_Msk instead */
#define US_TTGR_TG_Msk DEPRECATED(US_TTGR_TG_Msk, "Using deprecated macro US_TTGR_TG_Msk") (_U_(0xFF) << US_TTGR_TG_Pos) /**< (US_TTGR) Timeguard Value Mask */
#define US_TTGR_TG_Pos DEPRECATED(US_TTGR_TG_Pos, "Using deprecated macro US_TTGR_TG_Pos") 0 /**< (US_TTGR) Timeguard Value Position */
#define US_TTGR_TG(value) DEPRECATED(US_TTGR_TG, "Using deprecated macro US_TTGR_TG") (US_TTGR_TG_Msk & ((value) << US_TTGR_TG_Pos))

#endif
