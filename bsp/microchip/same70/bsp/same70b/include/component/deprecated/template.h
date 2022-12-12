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

#ifndef _<DEVICE>_<MODULE>_COMPONENT_DEPRECATED_H_
#define _<DEVICE>_<MODULE>_COMPONENT_DEPRECATED_H_

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
#define <MODULE>_OLD_MACRO DEPRECATED(<MODULE>_OLD_MACRO, "deprecated") <value>

#endif
