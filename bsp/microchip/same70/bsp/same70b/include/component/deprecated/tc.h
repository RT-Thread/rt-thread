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

#ifndef _SAME70_TC_COMPONENT_DEPRECATED_H_
#define _SAME70_TC_COMPONENT_DEPRECATED_H_

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
#define TC_CMR_ABETRG_Msk DEPRECATED(TC_CMR_ABETRG_Msk, "Using deprecated macro TC_CMR_ABETRG_Msk") (_U_(0x1) << TC_CMR_ABETRG_Pos) /**< (TC_CMR) TIOAx or TIOBx External Trigger Selection Mask */
#define TC_CMR_ABETRG_Pos DEPRECATED(TC_CMR_ABETRG_Pos, "Using deprecated macro TC_CMR_ABETRG_Pos") 10 /**< (TC_CMR) TIOAx or TIOBx External Trigger Selection Position */
#define TC_CMR_ABETRG DEPRECATED(TC_CMR_ABETRG, "Using deprecated macro TC_CMR_ABETRG") TC_CMR_ABETRG_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use TC_CMR_ABETRG_Msk instead */
#define TC_CMR_CPCTRG_Msk DEPRECATED(TC_CMR_CPCTRG_Msk, "Using deprecated macro TC_CMR_CPCTRG_Msk") (_U_(0x1) << TC_CMR_CPCTRG_Pos) /**< (TC_CMR) RC Compare Trigger Enable Mask */
#define TC_CMR_CPCTRG_Pos DEPRECATED(TC_CMR_CPCTRG_Pos, "Using deprecated macro TC_CMR_CPCTRG_Pos") 14 /**< (TC_CMR) RC Compare Trigger Enable Position */
#define TC_CMR_CPCTRG DEPRECATED(TC_CMR_CPCTRG, "Using deprecated macro TC_CMR_CPCTRG") TC_CMR_CPCTRG_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use TC_CMR_CPCTRG_Msk instead */
#define TC_CMR_ETRGEDG_Msk DEPRECATED(TC_CMR_ETRGEDG_Msk, "Using deprecated macro TC_CMR_ETRGEDG_Msk") (_U_(0x3) << TC_CMR_ETRGEDG_Pos) /**< (TC_CMR) External Trigger Edge Selection Mask */
#define TC_CMR_ETRGEDG_Pos DEPRECATED(TC_CMR_ETRGEDG_Pos, "Using deprecated macro TC_CMR_ETRGEDG_Pos") 8 /**< (TC_CMR) External Trigger Edge Selection Position */
#define TC_CMR_ETRGEDG(value) DEPRECATED(TC_CMR_ETRGEDG, "Using deprecated macro TC_CMR_ETRGEDG") (TC_CMR_ETRGEDG_Msk & ((value) << TC_CMR_ETRGEDG_Pos))
#define TC_CMR_LDBDIS_Msk DEPRECATED(TC_CMR_LDBDIS_Msk, "Using deprecated macro TC_CMR_LDBDIS_Msk") (_U_(0x1) << TC_CMR_LDBDIS_Pos) /**< (TC_CMR) Counter Clock Disable with RB Loading Mask */
#define TC_CMR_LDBDIS_Pos DEPRECATED(TC_CMR_LDBDIS_Pos, "Using deprecated macro TC_CMR_LDBDIS_Pos") 7 /**< (TC_CMR) Counter Clock Disable with RB Loading Position */
#define TC_CMR_LDBDIS DEPRECATED(TC_CMR_LDBDIS, "Using deprecated macro TC_CMR_LDBDIS") TC_CMR_LDBDIS_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use TC_CMR_LDBDIS_Msk instead */
#define TC_CMR_LDBSTOP_Msk DEPRECATED(TC_CMR_LDBSTOP_Msk, "Using deprecated macro TC_CMR_LDBSTOP_Msk") (_U_(0x1) << TC_CMR_LDBSTOP_Pos) /**< (TC_CMR) Counter Clock Stopped with RB Loading Mask */
#define TC_CMR_LDBSTOP_Pos DEPRECATED(TC_CMR_LDBSTOP_Pos, "Using deprecated macro TC_CMR_LDBSTOP_Pos") 6 /**< (TC_CMR) Counter Clock Stopped with RB Loading Position */
#define TC_CMR_LDBSTOP DEPRECATED(TC_CMR_LDBSTOP, "Using deprecated macro TC_CMR_LDBSTOP") TC_CMR_LDBSTOP_Msk /**< \deprecated Old style mask definition for 1 bit bitfield. Use TC_CMR_LDBSTOP_Msk instead */
#define TC_CMR_LDRA_Msk DEPRECATED(TC_CMR_LDRA_Msk, "Using deprecated macro TC_CMR_LDRA_Msk") (_U_(0x3) << TC_CMR_LDRA_Pos) /**< (TC_CMR) RA Loading Edge Selection Mask */
#define TC_CMR_LDRA_Pos DEPRECATED(TC_CMR_LDRA_Pos, "Using deprecated macro TC_CMR_LDRA_Pos") 16 /**< (TC_CMR) RA Loading Edge Selection Position */
#define TC_CMR_LDRA(value) DEPRECATED(TC_CMR_LDRA, "Using deprecated macro TC_CMR_LDRA") (TC_CMR_LDRA_Msk & ((value) << TC_CMR_LDRA_Pos))
#define TC_CMR_LDRB_Msk DEPRECATED(TC_CMR_LDRB_Msk, "Using deprecated macro TC_CMR_LDRB_Msk") (_U_(0x3) << TC_CMR_LDRB_Pos) /**< (TC_CMR) RB Loading Edge Selection Mask */
#define TC_CMR_LDRB_Pos DEPRECATED(TC_CMR_LDRB_Pos, "Using deprecated macro TC_CMR_LDRB_Pos") 18 /**< (TC_CMR) RB Loading Edge Selection Position */
#define TC_CMR_LDRB(value) DEPRECATED(TC_CMR_LDRB, "Using deprecated macro TC_CMR_LDRB") (TC_CMR_LDRB_Msk & ((value) << TC_CMR_LDRB_Pos))
#define TC_CMR_SBSMPLR_Msk DEPRECATED(TC_CMR_SBSMPLR_Msk, "Using deprecated macro TC_CMR_SBSMPLR_Msk") (_U_(0x7) << TC_CMR_SBSMPLR_Pos) /**< (TC_CMR) Loading Edge Subsampling Ratio Mask */
#define TC_CMR_SBSMPLR_Pos DEPRECATED(TC_CMR_SBSMPLR_Pos, "Using deprecated macro TC_CMR_SBSMPLR_Pos") 20 /**< (TC_CMR) Loading Edge Subsampling Ratio Position */
#define TC_CMR_SBSMPLR(value) DEPRECATED(TC_CMR_SBSMPLR, "Using deprecated macro TC_CMR_SBSMPLR") (TC_CMR_SBSMPLR_Msk & ((value) << TC_CMR_SBSMPLR_Pos))
#endif
