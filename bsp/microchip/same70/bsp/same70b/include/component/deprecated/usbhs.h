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

#ifndef _SAME70_USBHS_COMPONENT_DEPRECATED_H_
#define _SAME70_USBHS_COMPONENT_DEPRECATED_H_

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
#define USBHS_DEVEPTICR_NAKINIC_Msk DEPRECATED(USBHS_DEVEPTICR_NAKINIC_Msk, "Using deprecated macro USBHS_DEVEPTICR_NAKINIC_Msk") (_U_(0x1) << USBHS_DEVEPTICR_NAKINIC_Pos) /**< (USBHS_DEVEPTICR) NAKed IN Interrupt Clear Mask */
#define USBHS_DEVEPTICR_NAKINIC_Pos DEPRECATED(USBHS_DEVEPTICR_NAKINIC_Pos, "Using deprecated macro USBHS_DEVEPTICR_NAKINIC_Pos") 4 /**< (USBHS_DEVEPTICR) NAKed IN Interrupt Clear Position */
#define USBHS_DEVEPTICR_NAKINIC DEPRECATED(USBHS_DEVEPTICR_NAKINIC, "Using deprecated macro USBHS_DEVEPTICR_NAKINIC") USBHS_DEVEPTICR_NAKINIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTICR_NAKINIC_Msk instead */
#define USBHS_DEVEPTICR_NAKOUTIC_Msk DEPRECATED(USBHS_DEVEPTICR_NAKOUTIC_Msk, "Using deprecated macro USBHS_DEVEPTICR_NAKOUTIC_Msk") (_U_(0x1) << USBHS_DEVEPTICR_NAKOUTIC_Pos) /**< (USBHS_DEVEPTICR) NAKed OUT Interrupt Clear Mask */
#define USBHS_DEVEPTICR_NAKOUTIC_Pos DEPRECATED(USBHS_DEVEPTICR_NAKOUTIC_Pos, "Using deprecated macro USBHS_DEVEPTICR_NAKOUTIC_Pos") 3 /**< (USBHS_DEVEPTICR) NAKed OUT Interrupt Clear Position */
#define USBHS_DEVEPTICR_NAKOUTIC DEPRECATED(USBHS_DEVEPTICR_NAKOUTIC, "Using deprecated macro USBHS_DEVEPTICR_NAKOUTIC") USBHS_DEVEPTICR_NAKOUTIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTICR_NAKOUTIC_Msk instead */
#define USBHS_DEVEPTICR_RXSTPIC_Msk DEPRECATED(USBHS_DEVEPTICR_RXSTPIC_Msk, "Using deprecated macro USBHS_DEVEPTICR_RXSTPIC_Msk") (_U_(0x1) << USBHS_DEVEPTICR_RXSTPIC_Pos) /**< (USBHS_DEVEPTICR) Received SETUP Interrupt Clear Mask */
#define USBHS_DEVEPTICR_RXSTPIC_Pos DEPRECATED(USBHS_DEVEPTICR_RXSTPIC_Pos, "Using deprecated macro USBHS_DEVEPTICR_RXSTPIC_Pos") 2 /**< (USBHS_DEVEPTICR) Received SETUP Interrupt Clear Position */
#define USBHS_DEVEPTICR_RXSTPIC DEPRECATED(USBHS_DEVEPTICR_RXSTPIC, "Using deprecated macro USBHS_DEVEPTICR_RXSTPIC") USBHS_DEVEPTICR_RXSTPIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTICR_RXSTPIC_Msk instead */
#define USBHS_DEVEPTICR_STALLEDIC_Msk DEPRECATED(USBHS_DEVEPTICR_STALLEDIC_Msk, "Using deprecated macro USBHS_DEVEPTICR_STALLEDIC_Msk") (_U_(0x1) << USBHS_DEVEPTICR_STALLEDIC_Pos) /**< (USBHS_DEVEPTICR) STALLed Interrupt Clear Mask */
#define USBHS_DEVEPTICR_STALLEDIC_Pos DEPRECATED(USBHS_DEVEPTICR_STALLEDIC_Pos, "Using deprecated macro USBHS_DEVEPTICR_STALLEDIC_Pos") 6 /**< (USBHS_DEVEPTICR) STALLed Interrupt Clear Position */
#define USBHS_DEVEPTICR_STALLEDIC DEPRECATED(USBHS_DEVEPTICR_STALLEDIC, "Using deprecated macro USBHS_DEVEPTICR_STALLEDIC") USBHS_DEVEPTICR_STALLEDIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTICR_STALLEDIC_Msk instead */
#define USBHS_DEVEPTIDR_NAKINEC_Msk DEPRECATED(USBHS_DEVEPTIDR_NAKINEC_Msk, "Using deprecated macro USBHS_DEVEPTIDR_NAKINEC_Msk") (_U_(0x1) << USBHS_DEVEPTIDR_NAKINEC_Pos) /**< (USBHS_DEVEPTIDR) NAKed IN Interrupt Clear Mask */
#define USBHS_DEVEPTIDR_NAKINEC_Pos DEPRECATED(USBHS_DEVEPTIDR_NAKINEC_Pos, "Using deprecated macro USBHS_DEVEPTIDR_NAKINEC_Pos") 4 /**< (USBHS_DEVEPTIDR) NAKed IN Interrupt Clear Position */
#define USBHS_DEVEPTIDR_NAKINEC DEPRECATED(USBHS_DEVEPTIDR_NAKINEC, "Using deprecated macro USBHS_DEVEPTIDR_NAKINEC") USBHS_DEVEPTIDR_NAKINEC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIDR_NAKINEC_Msk instead */
#define USBHS_DEVEPTIDR_NAKOUTEC_Msk DEPRECATED(USBHS_DEVEPTIDR_NAKOUTEC_Msk, "Using deprecated macro USBHS_DEVEPTIDR_NAKOUTEC_Msk") (_U_(0x1) << USBHS_DEVEPTIDR_NAKOUTEC_Pos) /**< (USBHS_DEVEPTIDR) NAKed OUT Interrupt Clear Mask */
#define USBHS_DEVEPTIDR_NAKOUTEC_Pos DEPRECATED(USBHS_DEVEPTIDR_NAKOUTEC_Pos, "Using deprecated macro USBHS_DEVEPTIDR_NAKOUTEC_Pos") 3 /**< (USBHS_DEVEPTIDR) NAKed OUT Interrupt Clear Position */
#define USBHS_DEVEPTIDR_NAKOUTEC DEPRECATED(USBHS_DEVEPTIDR_NAKOUTEC, "Using deprecated macro USBHS_DEVEPTIDR_NAKOUTEC") USBHS_DEVEPTIDR_NAKOUTEC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIDR_NAKOUTEC_Msk instead */
#define USBHS_DEVEPTIDR_NYETDISC_Msk DEPRECATED(USBHS_DEVEPTIDR_NYETDISC_Msk, "Using deprecated macro USBHS_DEVEPTIDR_NYETDISC_Msk") (_U_(0x1) << USBHS_DEVEPTIDR_NYETDISC_Pos) /**< (USBHS_DEVEPTIDR) NYET Token Disable Clear Mask */
#define USBHS_DEVEPTIDR_NYETDISC_Pos DEPRECATED(USBHS_DEVEPTIDR_NYETDISC_Pos, "Using deprecated macro USBHS_DEVEPTIDR_NYETDISC_Pos") 17 /**< (USBHS_DEVEPTIDR) NYET Token Disable Clear Position */
#define USBHS_DEVEPTIDR_NYETDISC DEPRECATED(USBHS_DEVEPTIDR_NYETDISC, "Using deprecated macro USBHS_DEVEPTIDR_NYETDISC") USBHS_DEVEPTIDR_NYETDISC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIDR_NYETDISC_Msk instead */
#define USBHS_DEVEPTIDR_RXSTPEC_Msk DEPRECATED(USBHS_DEVEPTIDR_RXSTPEC_Msk, "Using deprecated macro USBHS_DEVEPTIDR_RXSTPEC_Msk") (_U_(0x1) << USBHS_DEVEPTIDR_RXSTPEC_Pos) /**< (USBHS_DEVEPTIDR) Received SETUP Interrupt Clear Mask */
#define USBHS_DEVEPTIDR_RXSTPEC_Pos DEPRECATED(USBHS_DEVEPTIDR_RXSTPEC_Pos, "Using deprecated macro USBHS_DEVEPTIDR_RXSTPEC_Pos") 2 /**< (USBHS_DEVEPTIDR) Received SETUP Interrupt Clear Position */
#define USBHS_DEVEPTIDR_RXSTPEC DEPRECATED(USBHS_DEVEPTIDR_RXSTPEC, "Using deprecated macro USBHS_DEVEPTIDR_RXSTPEC") USBHS_DEVEPTIDR_RXSTPEC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIDR_RXSTPEC_Msk instead */
#define USBHS_DEVEPTIDR_STALLEDEC_Msk DEPRECATED(USBHS_DEVEPTIDR_STALLEDEC_Msk, "Using deprecated macro USBHS_DEVEPTIDR_STALLEDEC_Msk") (_U_(0x1) << USBHS_DEVEPTIDR_STALLEDEC_Pos) /**< (USBHS_DEVEPTIDR) STALLed Interrupt Clear Mask */
#define USBHS_DEVEPTIDR_STALLEDEC_Pos DEPRECATED(USBHS_DEVEPTIDR_STALLEDEC_Pos, "Using deprecated macro USBHS_DEVEPTIDR_STALLEDEC_Pos") 6 /**< (USBHS_DEVEPTIDR) STALLed Interrupt Clear Position */
#define USBHS_DEVEPTIDR_STALLEDEC DEPRECATED(USBHS_DEVEPTIDR_STALLEDEC, "Using deprecated macro USBHS_DEVEPTIDR_STALLEDEC") USBHS_DEVEPTIDR_STALLEDEC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIDR_STALLEDEC_Msk instead */
#define USBHS_DEVEPTIDR_STALLRQC_Msk DEPRECATED(USBHS_DEVEPTIDR_STALLRQC_Msk, "Using deprecated macro USBHS_DEVEPTIDR_STALLRQC_Msk") (_U_(0x1) << USBHS_DEVEPTIDR_STALLRQC_Pos) /**< (USBHS_DEVEPTIDR) STALL Request Clear Mask */
#define USBHS_DEVEPTIDR_STALLRQC_Pos DEPRECATED(USBHS_DEVEPTIDR_STALLRQC_Pos, "Using deprecated macro USBHS_DEVEPTIDR_STALLRQC_Pos") 19 /**< (USBHS_DEVEPTIDR) STALL Request Clear Position */
#define USBHS_DEVEPTIDR_STALLRQC DEPRECATED(USBHS_DEVEPTIDR_STALLRQC, "Using deprecated macro USBHS_DEVEPTIDR_STALLRQC") USBHS_DEVEPTIDR_STALLRQC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIDR_STALLRQC_Msk instead */
#define USBHS_DEVEPTIER_NAKINES_Msk DEPRECATED(USBHS_DEVEPTIER_NAKINES_Msk, "Using deprecated macro USBHS_DEVEPTIER_NAKINES_Msk") (_U_(0x1) << USBHS_DEVEPTIER_NAKINES_Pos) /**< (USBHS_DEVEPTIER) NAKed IN Interrupt Enable Mask */
#define USBHS_DEVEPTIER_NAKINES_Pos DEPRECATED(USBHS_DEVEPTIER_NAKINES_Pos, "Using deprecated macro USBHS_DEVEPTIER_NAKINES_Pos") 4 /**< (USBHS_DEVEPTIER) NAKed IN Interrupt Enable Position */
#define USBHS_DEVEPTIER_NAKINES DEPRECATED(USBHS_DEVEPTIER_NAKINES, "Using deprecated macro USBHS_DEVEPTIER_NAKINES") USBHS_DEVEPTIER_NAKINES_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIER_NAKINES_Msk instead */
#define USBHS_DEVEPTIER_NAKOUTES_Msk DEPRECATED(USBHS_DEVEPTIER_NAKOUTES_Msk, "Using deprecated macro USBHS_DEVEPTIER_NAKOUTES_Msk") (_U_(0x1) << USBHS_DEVEPTIER_NAKOUTES_Pos) /**< (USBHS_DEVEPTIER) NAKed OUT Interrupt Enable Mask */
#define USBHS_DEVEPTIER_NAKOUTES_Pos DEPRECATED(USBHS_DEVEPTIER_NAKOUTES_Pos, "Using deprecated macro USBHS_DEVEPTIER_NAKOUTES_Pos") 3 /**< (USBHS_DEVEPTIER) NAKed OUT Interrupt Enable Position */
#define USBHS_DEVEPTIER_NAKOUTES DEPRECATED(USBHS_DEVEPTIER_NAKOUTES, "Using deprecated macro USBHS_DEVEPTIER_NAKOUTES") USBHS_DEVEPTIER_NAKOUTES_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIER_NAKOUTES_Msk instead */
#define USBHS_DEVEPTIER_NYETDISS_Msk DEPRECATED(USBHS_DEVEPTIER_NYETDISS_Msk, "Using deprecated macro USBHS_DEVEPTIER_NYETDISS_Msk") (_U_(0x1) << USBHS_DEVEPTIER_NYETDISS_Pos) /**< (USBHS_DEVEPTIER) NYET Token Disable Enable Mask */
#define USBHS_DEVEPTIER_NYETDISS_Pos DEPRECATED(USBHS_DEVEPTIER_NYETDISS_Pos, "Using deprecated macro USBHS_DEVEPTIER_NYETDISS_Pos") 17 /**< (USBHS_DEVEPTIER) NYET Token Disable Enable Position */
#define USBHS_DEVEPTIER_NYETDISS DEPRECATED(USBHS_DEVEPTIER_NYETDISS, "Using deprecated macro USBHS_DEVEPTIER_NYETDISS") USBHS_DEVEPTIER_NYETDISS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIER_NYETDISS_Msk instead */
#define USBHS_DEVEPTIER_RXSTPES_Msk DEPRECATED(USBHS_DEVEPTIER_RXSTPES_Msk, "Using deprecated macro USBHS_DEVEPTIER_RXSTPES_Msk") (_U_(0x1) << USBHS_DEVEPTIER_RXSTPES_Pos) /**< (USBHS_DEVEPTIER) Received SETUP Interrupt Enable Mask */
#define USBHS_DEVEPTIER_RXSTPES_Pos DEPRECATED(USBHS_DEVEPTIER_RXSTPES_Pos, "Using deprecated macro USBHS_DEVEPTIER_RXSTPES_Pos") 2 /**< (USBHS_DEVEPTIER) Received SETUP Interrupt Enable Position */
#define USBHS_DEVEPTIER_RXSTPES DEPRECATED(USBHS_DEVEPTIER_RXSTPES, "Using deprecated macro USBHS_DEVEPTIER_RXSTPES") USBHS_DEVEPTIER_RXSTPES_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIER_RXSTPES_Msk instead */
#define USBHS_DEVEPTIER_STALLEDES_Msk DEPRECATED(USBHS_DEVEPTIER_STALLEDES_Msk, "Using deprecated macro USBHS_DEVEPTIER_STALLEDES_Msk") (_U_(0x1) << USBHS_DEVEPTIER_STALLEDES_Pos) /**< (USBHS_DEVEPTIER) STALLed Interrupt Enable Mask */
#define USBHS_DEVEPTIER_STALLEDES_Pos DEPRECATED(USBHS_DEVEPTIER_STALLEDES_Pos, "Using deprecated macro USBHS_DEVEPTIER_STALLEDES_Pos") 6 /**< (USBHS_DEVEPTIER) STALLed Interrupt Enable Position */
#define USBHS_DEVEPTIER_STALLEDES DEPRECATED(USBHS_DEVEPTIER_STALLEDES, "Using deprecated macro USBHS_DEVEPTIER_STALLEDES") USBHS_DEVEPTIER_STALLEDES_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIER_STALLEDES_Msk instead */
#define USBHS_DEVEPTIER_STALLRQS_Msk DEPRECATED(USBHS_DEVEPTIER_STALLRQS_Msk, "Using deprecated macro USBHS_DEVEPTIER_STALLRQS_Msk") (_U_(0x1) << USBHS_DEVEPTIER_STALLRQS_Pos) /**< (USBHS_DEVEPTIER) STALL Request Enable Mask */
#define USBHS_DEVEPTIER_STALLRQS_Pos DEPRECATED(USBHS_DEVEPTIER_STALLRQS_Pos, "Using deprecated macro USBHS_DEVEPTIER_STALLRQS_Pos") 19 /**< (USBHS_DEVEPTIER) STALL Request Enable Position */
#define USBHS_DEVEPTIER_STALLRQS DEPRECATED(USBHS_DEVEPTIER_STALLRQS, "Using deprecated macro USBHS_DEVEPTIER_STALLRQS") USBHS_DEVEPTIER_STALLRQS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIER_STALLRQS_Msk instead */
#define USBHS_DEVEPTIFR_NAKINIS_Msk DEPRECATED(USBHS_DEVEPTIFR_NAKINIS_Msk, "Using deprecated macro USBHS_DEVEPTIFR_NAKINIS_Msk") (_U_(0x1) << USBHS_DEVEPTIFR_NAKINIS_Pos) /**< (USBHS_DEVEPTIFR) NAKed IN Interrupt Set Mask */
#define USBHS_DEVEPTIFR_NAKINIS_Pos DEPRECATED(USBHS_DEVEPTIFR_NAKINIS_Pos, "Using deprecated macro USBHS_DEVEPTIFR_NAKINIS_Pos") 4 /**< (USBHS_DEVEPTIFR) NAKed IN Interrupt Set Position */
#define USBHS_DEVEPTIFR_NAKINIS DEPRECATED(USBHS_DEVEPTIFR_NAKINIS, "Using deprecated macro USBHS_DEVEPTIFR_NAKINIS") USBHS_DEVEPTIFR_NAKINIS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIFR_NAKINIS_Msk instead */
#define USBHS_DEVEPTIFR_NAKOUTIS_Msk DEPRECATED(USBHS_DEVEPTIFR_NAKOUTIS_Msk, "Using deprecated macro USBHS_DEVEPTIFR_NAKOUTIS_Msk") (_U_(0x1) << USBHS_DEVEPTIFR_NAKOUTIS_Pos) /**< (USBHS_DEVEPTIFR) NAKed OUT Interrupt Set Mask */
#define USBHS_DEVEPTIFR_NAKOUTIS_Pos DEPRECATED(USBHS_DEVEPTIFR_NAKOUTIS_Pos, "Using deprecated macro USBHS_DEVEPTIFR_NAKOUTIS_Pos") 3 /**< (USBHS_DEVEPTIFR) NAKed OUT Interrupt Set Position */
#define USBHS_DEVEPTIFR_NAKOUTIS DEPRECATED(USBHS_DEVEPTIFR_NAKOUTIS, "Using deprecated macro USBHS_DEVEPTIFR_NAKOUTIS") USBHS_DEVEPTIFR_NAKOUTIS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIFR_NAKOUTIS_Msk instead */
#define USBHS_DEVEPTIFR_RXSTPIS_Msk DEPRECATED(USBHS_DEVEPTIFR_RXSTPIS_Msk, "Using deprecated macro USBHS_DEVEPTIFR_RXSTPIS_Msk") (_U_(0x1) << USBHS_DEVEPTIFR_RXSTPIS_Pos) /**< (USBHS_DEVEPTIFR) Received SETUP Interrupt Set Mask */
#define USBHS_DEVEPTIFR_RXSTPIS_Pos DEPRECATED(USBHS_DEVEPTIFR_RXSTPIS_Pos, "Using deprecated macro USBHS_DEVEPTIFR_RXSTPIS_Pos") 2 /**< (USBHS_DEVEPTIFR) Received SETUP Interrupt Set Position */
#define USBHS_DEVEPTIFR_RXSTPIS DEPRECATED(USBHS_DEVEPTIFR_RXSTPIS, "Using deprecated macro USBHS_DEVEPTIFR_RXSTPIS") USBHS_DEVEPTIFR_RXSTPIS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIFR_RXSTPIS_Msk instead */
#define USBHS_DEVEPTIFR_STALLEDIS_Msk DEPRECATED(USBHS_DEVEPTIFR_STALLEDIS_Msk, "Using deprecated macro USBHS_DEVEPTIFR_STALLEDIS_Msk") (_U_(0x1) << USBHS_DEVEPTIFR_STALLEDIS_Pos) /**< (USBHS_DEVEPTIFR) STALLed Interrupt Set Mask */
#define USBHS_DEVEPTIFR_STALLEDIS_Pos DEPRECATED(USBHS_DEVEPTIFR_STALLEDIS_Pos, "Using deprecated macro USBHS_DEVEPTIFR_STALLEDIS_Pos") 6 /**< (USBHS_DEVEPTIFR) STALLed Interrupt Set Position */
#define USBHS_DEVEPTIFR_STALLEDIS DEPRECATED(USBHS_DEVEPTIFR_STALLEDIS, "Using deprecated macro USBHS_DEVEPTIFR_STALLEDIS") USBHS_DEVEPTIFR_STALLEDIS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIFR_STALLEDIS_Msk instead */
#define USBHS_DEVEPTIMR_NAKINE_Msk DEPRECATED(USBHS_DEVEPTIMR_NAKINE_Msk, "Using deprecated macro USBHS_DEVEPTIMR_NAKINE_Msk") (_U_(0x1) << USBHS_DEVEPTIMR_NAKINE_Pos) /**< (USBHS_DEVEPTIMR) NAKed IN Interrupt Mask */
#define USBHS_DEVEPTIMR_NAKINE_Pos DEPRECATED(USBHS_DEVEPTIMR_NAKINE_Pos, "Using deprecated macro USBHS_DEVEPTIMR_NAKINE_Pos") 4 /**< (USBHS_DEVEPTIMR) NAKed IN Interrupt Position */
#define USBHS_DEVEPTIMR_NAKINE DEPRECATED(USBHS_DEVEPTIMR_NAKINE, "Using deprecated macro USBHS_DEVEPTIMR_NAKINE") USBHS_DEVEPTIMR_NAKINE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIMR_NAKINE_Msk instead */
#define USBHS_DEVEPTIMR_NAKOUTE_Msk DEPRECATED(USBHS_DEVEPTIMR_NAKOUTE_Msk, "Using deprecated macro USBHS_DEVEPTIMR_NAKOUTE_Msk") (_U_(0x1) << USBHS_DEVEPTIMR_NAKOUTE_Pos) /**< (USBHS_DEVEPTIMR) NAKed OUT Interrupt Mask */
#define USBHS_DEVEPTIMR_NAKOUTE_Pos DEPRECATED(USBHS_DEVEPTIMR_NAKOUTE_Pos, "Using deprecated macro USBHS_DEVEPTIMR_NAKOUTE_Pos") 3 /**< (USBHS_DEVEPTIMR) NAKed OUT Interrupt Position */
#define USBHS_DEVEPTIMR_NAKOUTE DEPRECATED(USBHS_DEVEPTIMR_NAKOUTE, "Using deprecated macro USBHS_DEVEPTIMR_NAKOUTE") USBHS_DEVEPTIMR_NAKOUTE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIMR_NAKOUTE_Msk instead */
#define USBHS_DEVEPTIMR_NYETDIS_Msk DEPRECATED(USBHS_DEVEPTIMR_NYETDIS_Msk, "Using deprecated macro USBHS_DEVEPTIMR_NYETDIS_Msk") (_U_(0x1) << USBHS_DEVEPTIMR_NYETDIS_Pos) /**< (USBHS_DEVEPTIMR) NYET Token Disable Mask */
#define USBHS_DEVEPTIMR_NYETDIS_Pos DEPRECATED(USBHS_DEVEPTIMR_NYETDIS_Pos, "Using deprecated macro USBHS_DEVEPTIMR_NYETDIS_Pos") 17 /**< (USBHS_DEVEPTIMR) NYET Token Disable Position */
#define USBHS_DEVEPTIMR_NYETDIS DEPRECATED(USBHS_DEVEPTIMR_NYETDIS, "Using deprecated macro USBHS_DEVEPTIMR_NYETDIS") USBHS_DEVEPTIMR_NYETDIS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIMR_NYETDIS_Msk instead */
#define USBHS_DEVEPTIMR_RXSTPE_Msk DEPRECATED(USBHS_DEVEPTIMR_RXSTPE_Msk, "Using deprecated macro USBHS_DEVEPTIMR_RXSTPE_Msk") (_U_(0x1) << USBHS_DEVEPTIMR_RXSTPE_Pos) /**< (USBHS_DEVEPTIMR) Received SETUP Interrupt Mask */
#define USBHS_DEVEPTIMR_RXSTPE_Pos DEPRECATED(USBHS_DEVEPTIMR_RXSTPE_Pos, "Using deprecated macro USBHS_DEVEPTIMR_RXSTPE_Pos") 2 /**< (USBHS_DEVEPTIMR) Received SETUP Interrupt Position */
#define USBHS_DEVEPTIMR_RXSTPE DEPRECATED(USBHS_DEVEPTIMR_RXSTPE, "Using deprecated macro USBHS_DEVEPTIMR_RXSTPE") USBHS_DEVEPTIMR_RXSTPE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIMR_RXSTPE_Msk instead */
#define USBHS_DEVEPTIMR_STALLEDE_Msk DEPRECATED(USBHS_DEVEPTIMR_STALLEDE_Msk, "Using deprecated macro USBHS_DEVEPTIMR_STALLEDE_Msk") (_U_(0x1) << USBHS_DEVEPTIMR_STALLEDE_Pos) /**< (USBHS_DEVEPTIMR) STALLed Interrupt Mask */
#define USBHS_DEVEPTIMR_STALLEDE_Pos DEPRECATED(USBHS_DEVEPTIMR_STALLEDE_Pos, "Using deprecated macro USBHS_DEVEPTIMR_STALLEDE_Pos") 6 /**< (USBHS_DEVEPTIMR) STALLed Interrupt Position */
#define USBHS_DEVEPTIMR_STALLEDE DEPRECATED(USBHS_DEVEPTIMR_STALLEDE, "Using deprecated macro USBHS_DEVEPTIMR_STALLEDE") USBHS_DEVEPTIMR_STALLEDE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIMR_STALLEDE_Msk instead */
#define USBHS_DEVEPTIMR_STALLRQ_Msk DEPRECATED(USBHS_DEVEPTIMR_STALLRQ_Msk, "Using deprecated macro USBHS_DEVEPTIMR_STALLRQ_Msk") (_U_(0x1) << USBHS_DEVEPTIMR_STALLRQ_Pos) /**< (USBHS_DEVEPTIMR) STALL Request Mask */
#define USBHS_DEVEPTIMR_STALLRQ_Pos DEPRECATED(USBHS_DEVEPTIMR_STALLRQ_Pos, "Using deprecated macro USBHS_DEVEPTIMR_STALLRQ_Pos") 19 /**< (USBHS_DEVEPTIMR) STALL Request Position */
#define USBHS_DEVEPTIMR_STALLRQ DEPRECATED(USBHS_DEVEPTIMR_STALLRQ, "Using deprecated macro USBHS_DEVEPTIMR_STALLRQ") USBHS_DEVEPTIMR_STALLRQ_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTIMR_STALLRQ_Msk instead */
#define USBHS_DEVEPTISR_CTRLDIR_Msk DEPRECATED(USBHS_DEVEPTISR_CTRLDIR_Msk, "Using deprecated macro USBHS_DEVEPTISR_CTRLDIR_Msk") (_U_(0x1) << USBHS_DEVEPTISR_CTRLDIR_Pos) /**< (USBHS_DEVEPTISR) Control Direction Mask */
#define USBHS_DEVEPTISR_CTRLDIR_Pos DEPRECATED(USBHS_DEVEPTISR_CTRLDIR_Pos, "Using deprecated macro USBHS_DEVEPTISR_CTRLDIR_Pos") 17 /**< (USBHS_DEVEPTISR) Control Direction Position */
#define USBHS_DEVEPTISR_CTRLDIR DEPRECATED(USBHS_DEVEPTISR_CTRLDIR, "Using deprecated macro USBHS_DEVEPTISR_CTRLDIR") USBHS_DEVEPTISR_CTRLDIR_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTISR_CTRLDIR_Msk instead */
#define USBHS_DEVEPTISR_NAKINI_Msk DEPRECATED(USBHS_DEVEPTISR_NAKINI_Msk, "Using deprecated macro USBHS_DEVEPTISR_NAKINI_Msk") (_U_(0x1) << USBHS_DEVEPTISR_NAKINI_Pos) /**< (USBHS_DEVEPTISR) NAKed IN Interrupt Mask */
#define USBHS_DEVEPTISR_NAKINI_Pos DEPRECATED(USBHS_DEVEPTISR_NAKINI_Pos, "Using deprecated macro USBHS_DEVEPTISR_NAKINI_Pos") 4 /**< (USBHS_DEVEPTISR) NAKed IN Interrupt Position */
#define USBHS_DEVEPTISR_NAKINI DEPRECATED(USBHS_DEVEPTISR_NAKINI, "Using deprecated macro USBHS_DEVEPTISR_NAKINI") USBHS_DEVEPTISR_NAKINI_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTISR_NAKINI_Msk instead */
#define USBHS_DEVEPTISR_NAKOUTI_Msk DEPRECATED(USBHS_DEVEPTISR_NAKOUTI_Msk, "Using deprecated macro USBHS_DEVEPTISR_NAKOUTI_Msk") (_U_(0x1) << USBHS_DEVEPTISR_NAKOUTI_Pos) /**< (USBHS_DEVEPTISR) NAKed OUT Interrupt Mask */
#define USBHS_DEVEPTISR_NAKOUTI_Pos DEPRECATED(USBHS_DEVEPTISR_NAKOUTI_Pos, "Using deprecated macro USBHS_DEVEPTISR_NAKOUTI_Pos") 3 /**< (USBHS_DEVEPTISR) NAKed OUT Interrupt Position */
#define USBHS_DEVEPTISR_NAKOUTI DEPRECATED(USBHS_DEVEPTISR_NAKOUTI, "Using deprecated macro USBHS_DEVEPTISR_NAKOUTI") USBHS_DEVEPTISR_NAKOUTI_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTISR_NAKOUTI_Msk instead */
#define USBHS_DEVEPTISR_RXSTPI_Msk DEPRECATED(USBHS_DEVEPTISR_RXSTPI_Msk, "Using deprecated macro USBHS_DEVEPTISR_RXSTPI_Msk") (_U_(0x1) << USBHS_DEVEPTISR_RXSTPI_Pos) /**< (USBHS_DEVEPTISR) Received SETUP Interrupt Mask */
#define USBHS_DEVEPTISR_RXSTPI_Pos DEPRECATED(USBHS_DEVEPTISR_RXSTPI_Pos, "Using deprecated macro USBHS_DEVEPTISR_RXSTPI_Pos") 2 /**< (USBHS_DEVEPTISR) Received SETUP Interrupt Position */
#define USBHS_DEVEPTISR_RXSTPI DEPRECATED(USBHS_DEVEPTISR_RXSTPI, "Using deprecated macro USBHS_DEVEPTISR_RXSTPI") USBHS_DEVEPTISR_RXSTPI_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTISR_RXSTPI_Msk instead */
#define USBHS_DEVEPTISR_STALLEDI_Msk DEPRECATED(USBHS_DEVEPTISR_STALLEDI_Msk, "Using deprecated macro USBHS_DEVEPTISR_STALLEDI_Msk") (_U_(0x1) << USBHS_DEVEPTISR_STALLEDI_Pos) /**< (USBHS_DEVEPTISR) STALLed Interrupt Mask */
#define USBHS_DEVEPTISR_STALLEDI_Pos DEPRECATED(USBHS_DEVEPTISR_STALLEDI_Pos, "Using deprecated macro USBHS_DEVEPTISR_STALLEDI_Pos") 6 /**< (USBHS_DEVEPTISR) STALLed Interrupt Position */
#define USBHS_DEVEPTISR_STALLEDI DEPRECATED(USBHS_DEVEPTISR_STALLEDI, "Using deprecated macro USBHS_DEVEPTISR_STALLEDI") USBHS_DEVEPTISR_STALLEDI_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_DEVEPTISR_STALLEDI_Msk instead */
#define USBHS_HSTIDR_DMA_7_Msk DEPRECATED(USBHS_HSTIDR_DMA_7_Msk, "Using deprecated macro USBHS_HSTIDR_DMA_7_Msk") (_U_(0x1) << USBHS_HSTIDR_DMA_7_Pos) /**< (USBHS_HSTIDR) DMA Channel 7 Interrupt Disable Mask */
#define USBHS_HSTIDR_DMA_7_Pos DEPRECATED(USBHS_HSTIDR_DMA_7_Pos, "Using deprecated macro USBHS_HSTIDR_DMA_7_Pos") 31 /**< (USBHS_HSTIDR) DMA Channel 7 Interrupt Disable Position */
#define USBHS_HSTIDR_DMA_7 DEPRECATED(USBHS_HSTIDR_DMA_7, "Using deprecated macro USBHS_HSTIDR_DMA_7") USBHS_HSTIDR_DMA_7_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTIDR_DMA_7_Msk instead */
#define USBHS_HSTIER_DMA_7_Msk DEPRECATED(USBHS_HSTIER_DMA_7_Msk, "Using deprecated macro USBHS_HSTIER_DMA_7_Msk") (_U_(0x1) << USBHS_HSTIER_DMA_7_Pos) /**< (USBHS_HSTIER) DMA Channel 7 Interrupt Enable Mask */
#define USBHS_HSTIER_DMA_7_Pos DEPRECATED(USBHS_HSTIER_DMA_7_Pos, "Using deprecated macro USBHS_HSTIER_DMA_7_Pos") 31 /**< (USBHS_HSTIER) DMA Channel 7 Interrupt Enable Position */
#define USBHS_HSTIER_DMA_7 DEPRECATED(USBHS_HSTIER_DMA_7, "Using deprecated macro USBHS_HSTIER_DMA_7") USBHS_HSTIER_DMA_7_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTIER_DMA_7_Msk instead */
#define USBHS_HSTIFR_DMA_7_Msk DEPRECATED(USBHS_HSTIFR_DMA_7_Msk, "Using deprecated macro USBHS_HSTIFR_DMA_7_Msk") (_U_(0x1) << USBHS_HSTIFR_DMA_7_Pos) /**< (USBHS_HSTIFR) DMA Channel 7 Interrupt Set Mask */
#define USBHS_HSTIFR_DMA_7_Pos DEPRECATED(USBHS_HSTIFR_DMA_7_Pos, "Using deprecated macro USBHS_HSTIFR_DMA_7_Pos") 31 /**< (USBHS_HSTIFR) DMA Channel 7 Interrupt Set Position */
#define USBHS_HSTIFR_DMA_7 DEPRECATED(USBHS_HSTIFR_DMA_7, "Using deprecated macro USBHS_HSTIFR_DMA_7") USBHS_HSTIFR_DMA_7_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTIFR_DMA_7_Msk instead */
#define USBHS_HSTIMR_DMA_7_Msk DEPRECATED(USBHS_HSTIMR_DMA_7_Msk, "Using deprecated macro USBHS_HSTIMR_DMA_7_Msk") (_U_(0x1) << USBHS_HSTIMR_DMA_7_Pos) /**< (USBHS_HSTIMR) DMA Channel 7 Interrupt Enable Mask */
#define USBHS_HSTIMR_DMA_7_Pos DEPRECATED(USBHS_HSTIMR_DMA_7_Pos, "Using deprecated macro USBHS_HSTIMR_DMA_7_Pos") 31 /**< (USBHS_HSTIMR) DMA Channel 7 Interrupt Enable Position */
#define USBHS_HSTIMR_DMA_7 DEPRECATED(USBHS_HSTIMR_DMA_7, "Using deprecated macro USBHS_HSTIMR_DMA_7") USBHS_HSTIMR_DMA_7_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTIMR_DMA_7_Msk instead */
#define USBHS_HSTISR_DMA_7_Msk DEPRECATED(USBHS_HSTISR_DMA_7_Msk, "Using deprecated macro USBHS_HSTISR_DMA_7_Msk") (_U_(0x1) << USBHS_HSTISR_DMA_7_Pos) /**< (USBHS_HSTISR) DMA Channel 7 Interrupt Mask */
#define USBHS_HSTISR_DMA_7_Pos DEPRECATED(USBHS_HSTISR_DMA_7_Pos, "Using deprecated macro USBHS_HSTISR_DMA_7_Pos") 31 /**< (USBHS_HSTISR) DMA Channel 7 Interrupt Position */
#define USBHS_HSTISR_DMA_7 DEPRECATED(USBHS_HSTISR_DMA_7, "Using deprecated macro USBHS_HSTISR_DMA_7") USBHS_HSTISR_DMA_7_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTISR_DMA_7_Msk instead */
#define USBHS_HSTPIPICR_RXSTALLDIC_Msk DEPRECATED(USBHS_HSTPIPICR_RXSTALLDIC_Msk, "Using deprecated macro USBHS_HSTPIPICR_RXSTALLDIC_Msk") (_U_(0x1) << USBHS_HSTPIPICR_RXSTALLDIC_Pos) /**< (USBHS_HSTPIPICR) Received STALLed Interrupt Clear Mask */
#define USBHS_HSTPIPICR_RXSTALLDIC_Pos DEPRECATED(USBHS_HSTPIPICR_RXSTALLDIC_Pos, "Using deprecated macro USBHS_HSTPIPICR_RXSTALLDIC_Pos") 6 /**< (USBHS_HSTPIPICR) Received STALLed Interrupt Clear Position */
#define USBHS_HSTPIPICR_RXSTALLDIC DEPRECATED(USBHS_HSTPIPICR_RXSTALLDIC, "Using deprecated macro USBHS_HSTPIPICR_RXSTALLDIC") USBHS_HSTPIPICR_RXSTALLDIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPICR_RXSTALLDIC_Msk instead */
#define USBHS_HSTPIPICR_TXSTPIC_Msk DEPRECATED(USBHS_HSTPIPICR_TXSTPIC_Msk, "Using deprecated macro USBHS_HSTPIPICR_TXSTPIC_Msk") (_U_(0x1) << USBHS_HSTPIPICR_TXSTPIC_Pos) /**< (USBHS_HSTPIPICR) Transmitted SETUP Interrupt Clear Mask */
#define USBHS_HSTPIPICR_TXSTPIC_Pos DEPRECATED(USBHS_HSTPIPICR_TXSTPIC_Pos, "Using deprecated macro USBHS_HSTPIPICR_TXSTPIC_Pos") 2 /**< (USBHS_HSTPIPICR) Transmitted SETUP Interrupt Clear Position */
#define USBHS_HSTPIPICR_TXSTPIC DEPRECATED(USBHS_HSTPIPICR_TXSTPIC, "Using deprecated macro USBHS_HSTPIPICR_TXSTPIC") USBHS_HSTPIPICR_TXSTPIC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPICR_TXSTPIC_Msk instead */
#define USBHS_HSTPIPIDR_RXSTALLDEC_Msk DEPRECATED(USBHS_HSTPIPIDR_RXSTALLDEC_Msk, "Using deprecated macro USBHS_HSTPIPIDR_RXSTALLDEC_Msk") (_U_(0x1) << USBHS_HSTPIPIDR_RXSTALLDEC_Pos) /**< (USBHS_HSTPIPIDR) Received STALLed Interrupt Disable Mask */
#define USBHS_HSTPIPIDR_RXSTALLDEC_Pos DEPRECATED(USBHS_HSTPIPIDR_RXSTALLDEC_Pos, "Using deprecated macro USBHS_HSTPIPIDR_RXSTALLDEC_Pos") 6 /**< (USBHS_HSTPIPIDR) Received STALLed Interrupt Disable Position */
#define USBHS_HSTPIPIDR_RXSTALLDEC DEPRECATED(USBHS_HSTPIPIDR_RXSTALLDEC, "Using deprecated macro USBHS_HSTPIPIDR_RXSTALLDEC") USBHS_HSTPIPIDR_RXSTALLDEC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPIDR_RXSTALLDEC_Msk instead */
#define USBHS_HSTPIPIDR_TXSTPEC_Msk DEPRECATED(USBHS_HSTPIPIDR_TXSTPEC_Msk, "Using deprecated macro USBHS_HSTPIPIDR_TXSTPEC_Msk") (_U_(0x1) << USBHS_HSTPIPIDR_TXSTPEC_Pos) /**< (USBHS_HSTPIPIDR) Transmitted SETUP Interrupt Disable Mask */
#define USBHS_HSTPIPIDR_TXSTPEC_Pos DEPRECATED(USBHS_HSTPIPIDR_TXSTPEC_Pos, "Using deprecated macro USBHS_HSTPIPIDR_TXSTPEC_Pos") 2 /**< (USBHS_HSTPIPIDR) Transmitted SETUP Interrupt Disable Position */
#define USBHS_HSTPIPIDR_TXSTPEC DEPRECATED(USBHS_HSTPIPIDR_TXSTPEC, "Using deprecated macro USBHS_HSTPIPIDR_TXSTPEC") USBHS_HSTPIPIDR_TXSTPEC_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPIDR_TXSTPEC_Msk instead */
#define USBHS_HSTPIPIER_RXSTALLDES_Msk DEPRECATED(USBHS_HSTPIPIER_RXSTALLDES_Msk, "Using deprecated macro USBHS_HSTPIPIER_RXSTALLDES_Msk") (_U_(0x1) << USBHS_HSTPIPIER_RXSTALLDES_Pos) /**< (USBHS_HSTPIPIER) Received STALLed Interrupt Enable Mask */
#define USBHS_HSTPIPIER_RXSTALLDES_Pos DEPRECATED(USBHS_HSTPIPIER_RXSTALLDES_Pos, "Using deprecated macro USBHS_HSTPIPIER_RXSTALLDES_Pos") 6 /**< (USBHS_HSTPIPIER) Received STALLed Interrupt Enable Position */
#define USBHS_HSTPIPIER_RXSTALLDES DEPRECATED(USBHS_HSTPIPIER_RXSTALLDES, "Using deprecated macro USBHS_HSTPIPIER_RXSTALLDES") USBHS_HSTPIPIER_RXSTALLDES_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPIER_RXSTALLDES_Msk instead */
#define USBHS_HSTPIPIER_TXSTPES_Msk DEPRECATED(USBHS_HSTPIPIER_TXSTPES_Msk, "Using deprecated macro USBHS_HSTPIPIER_TXSTPES_Msk") (_U_(0x1) << USBHS_HSTPIPIER_TXSTPES_Pos) /**< (USBHS_HSTPIPIER) Transmitted SETUP Interrupt Enable Mask */
#define USBHS_HSTPIPIER_TXSTPES_Pos DEPRECATED(USBHS_HSTPIPIER_TXSTPES_Pos, "Using deprecated macro USBHS_HSTPIPIER_TXSTPES_Pos") 2 /**< (USBHS_HSTPIPIER) Transmitted SETUP Interrupt Enable Position */
#define USBHS_HSTPIPIER_TXSTPES DEPRECATED(USBHS_HSTPIPIER_TXSTPES, "Using deprecated macro USBHS_HSTPIPIER_TXSTPES") USBHS_HSTPIPIER_TXSTPES_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPIER_TXSTPES_Msk instead */
#define USBHS_HSTPIPIFR_RXSTALLDIS_Msk DEPRECATED(USBHS_HSTPIPIFR_RXSTALLDIS_Msk, "Using deprecated macro USBHS_HSTPIPIFR_RXSTALLDIS_Msk") (_U_(0x1) << USBHS_HSTPIPIFR_RXSTALLDIS_Pos) /**< (USBHS_HSTPIPIFR) Received STALLed Interrupt Set Mask */
#define USBHS_HSTPIPIFR_RXSTALLDIS_Pos DEPRECATED(USBHS_HSTPIPIFR_RXSTALLDIS_Pos, "Using deprecated macro USBHS_HSTPIPIFR_RXSTALLDIS_Pos") 6 /**< (USBHS_HSTPIPIFR) Received STALLed Interrupt Set Position */
#define USBHS_HSTPIPIFR_RXSTALLDIS DEPRECATED(USBHS_HSTPIPIFR_RXSTALLDIS, "Using deprecated macro USBHS_HSTPIPIFR_RXSTALLDIS") USBHS_HSTPIPIFR_RXSTALLDIS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPIFR_RXSTALLDIS_Msk instead */
#define USBHS_HSTPIPIFR_TXSTPIS_Msk DEPRECATED(USBHS_HSTPIPIFR_TXSTPIS_Msk, "Using deprecated macro USBHS_HSTPIPIFR_TXSTPIS_Msk") (_U_(0x1) << USBHS_HSTPIPIFR_TXSTPIS_Pos) /**< (USBHS_HSTPIPIFR) Transmitted SETUP Interrupt Set Mask */
#define USBHS_HSTPIPIFR_TXSTPIS_Pos DEPRECATED(USBHS_HSTPIPIFR_TXSTPIS_Pos, "Using deprecated macro USBHS_HSTPIPIFR_TXSTPIS_Pos") 2 /**< (USBHS_HSTPIPIFR) Transmitted SETUP Interrupt Set Position */
#define USBHS_HSTPIPIFR_TXSTPIS DEPRECATED(USBHS_HSTPIPIFR_TXSTPIS, "Using deprecated macro USBHS_HSTPIPIFR_TXSTPIS") USBHS_HSTPIPIFR_TXSTPIS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPIFR_TXSTPIS_Msk instead */
#define USBHS_HSTPIPIMR_RXSTALLDE_Msk DEPRECATED(USBHS_HSTPIPIMR_RXSTALLDE_Msk, "Using deprecated macro USBHS_HSTPIPIMR_RXSTALLDE_Msk") (_U_(0x1) << USBHS_HSTPIPIMR_RXSTALLDE_Pos) /**< (USBHS_HSTPIPIMR) Received STALLed Interrupt Enable Mask */
#define USBHS_HSTPIPIMR_RXSTALLDE_Pos DEPRECATED(USBHS_HSTPIPIMR_RXSTALLDE_Pos, "Using deprecated macro USBHS_HSTPIPIMR_RXSTALLDE_Pos") 6 /**< (USBHS_HSTPIPIMR) Received STALLed Interrupt Enable Position */
#define USBHS_HSTPIPIMR_RXSTALLDE DEPRECATED(USBHS_HSTPIPIMR_RXSTALLDE, "Using deprecated macro USBHS_HSTPIPIMR_RXSTALLDE") USBHS_HSTPIPIMR_RXSTALLDE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPIMR_RXSTALLDE_Msk instead */
#define USBHS_HSTPIPIMR_TXSTPE_Msk DEPRECATED(USBHS_HSTPIPIMR_TXSTPE_Msk, "Using deprecated macro USBHS_HSTPIPIMR_TXSTPE_Msk") (_U_(0x1) << USBHS_HSTPIPIMR_TXSTPE_Pos) /**< (USBHS_HSTPIPIMR) Transmitted SETUP Interrupt Enable Mask */
#define USBHS_HSTPIPIMR_TXSTPE_Pos DEPRECATED(USBHS_HSTPIPIMR_TXSTPE_Pos, "Using deprecated macro USBHS_HSTPIPIMR_TXSTPE_Pos") 2 /**< (USBHS_HSTPIPIMR) Transmitted SETUP Interrupt Enable Position */
#define USBHS_HSTPIPIMR_TXSTPE DEPRECATED(USBHS_HSTPIPIMR_TXSTPE, "Using deprecated macro USBHS_HSTPIPIMR_TXSTPE") USBHS_HSTPIPIMR_TXSTPE_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPIMR_TXSTPE_Msk instead */
#define USBHS_HSTPIPISR_RXSTALLDI_Msk DEPRECATED(USBHS_HSTPIPISR_RXSTALLDI_Msk, "Using deprecated macro USBHS_HSTPIPISR_RXSTALLDI_Msk") (_U_(0x1) << USBHS_HSTPIPISR_RXSTALLDI_Pos) /**< (USBHS_HSTPIPISR) Received STALLed Interrupt Mask */
#define USBHS_HSTPIPISR_RXSTALLDI_Pos DEPRECATED(USBHS_HSTPIPISR_RXSTALLDI_Pos, "Using deprecated macro USBHS_HSTPIPISR_RXSTALLDI_Pos") 6 /**< (USBHS_HSTPIPISR) Received STALLed Interrupt Position */
#define USBHS_HSTPIPISR_RXSTALLDI DEPRECATED(USBHS_HSTPIPISR_RXSTALLDI, "Using deprecated macro USBHS_HSTPIPISR_RXSTALLDI") USBHS_HSTPIPISR_RXSTALLDI_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPISR_RXSTALLDI_Msk instead */
#define USBHS_HSTPIPISR_TXSTPI_Msk DEPRECATED(USBHS_HSTPIPISR_TXSTPI_Msk, "Using deprecated macro USBHS_HSTPIPISR_TXSTPI_Msk") (_U_(0x1) << USBHS_HSTPIPISR_TXSTPI_Pos) /**< (USBHS_HSTPIPISR) Transmitted SETUP Interrupt Mask */
#define USBHS_HSTPIPISR_TXSTPI_Pos DEPRECATED(USBHS_HSTPIPISR_TXSTPI_Pos, "Using deprecated macro USBHS_HSTPIPISR_TXSTPI_Pos") 2 /**< (USBHS_HSTPIPISR) Transmitted SETUP Interrupt Position */
#define USBHS_HSTPIPISR_TXSTPI DEPRECATED(USBHS_HSTPIPISR_TXSTPI, "Using deprecated macro USBHS_HSTPIPISR_TXSTPI") USBHS_HSTPIPISR_TXSTPI_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use USBHS_HSTPIPISR_TXSTPI_Msk instead */

#endif
