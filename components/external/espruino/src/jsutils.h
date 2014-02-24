/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * Misc utils and cheapskate stdlib implementation
 * ----------------------------------------------------------------------------
 */
#ifndef JSUTILS_H_
#define JSUTILS_H_

#include "platform_config.h"

#ifndef FAKE_STDLIB
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#endif
#include <stdarg.h> // for va_args

#define JS_VERSION "1v46"
/*
  In code:
  TODO - should be fixed
  FIXME - will probably break if used
  OPT - potential for speed optimisation
*/

// surely bool is defined??
#ifdef RT_USING_JS
typedef unsigned int size_t;
#else
#ifdef ARM
typedef unsigned int size_t;
#define alloca(x) __builtin_alloca(x)
#endif
#endif

#if !defined(__USB_TYPE_H) && !defined(CPLUSPLUS) // it is defined in this file too!
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
//typedef unsigned char bool;
//#define TRUE (1)
//#define FALSE (0)
#endif

#define true (1)
#define false (0)
#define NAN (((JsVarFloat)0)/(JsVarFloat)0)

/* Number of Js Variables allowed and Js Reference format.

   JsVarRef = char -> 15 bytes/JsVar   so JSVAR_CACHE_SIZE = (RAM - 3000) / 15
   JsVarRef = short -> 20 bytes/JsVar   so JSVAR_CACHE_SIZE = (RAM - 3000) / 20
   JsVarRef = int -> 26 bytes/JsVar   so JSVAR_CACHE_SIZE = (RAM - 3000) / 26

   NOTE: JSVAR_CACHE_SIZE must be at least 2 less than the number we can fit in JsVarRef
         See jshardware.c FLASH constants - all this must be able to fit in flash


*/

#ifdef RESIZABLE_JSVARS
 //  probably linux - allow us to allocate more blocks of variables
  typedef unsigned int JsVarRef;
  #define JSVAR_SIZE 30
  #define JSVAR_DATA_STRING_LEN  8 // Actually 9 seems like a good number as 'prototype'==9
  #define JSVAR_DATA_STRING_MAX_LEN 24 // (JSVAR_DATA_STRING_LEN + sizeof(JsVarRef)*3 + sizeof(JsVarRefCounter)) - but see JSV_STRING_LEN_MAX - WE HAVE TO CLIP!
#else
   /** JsVerRef stores References for variables - We treat 0 as null
   *  NOTE: we store JSVAR_DATA_STRING_* as actual values so we can do #if on them below
   *
   */
  #if JSVAR_CACHE_SIZE <= 254
    typedef unsigned char JsVarRef;
    #define JSVAR_SIZE 15
    #define JSVAR_DATA_STRING_LEN  8 // Actually 9 seems like a good number as 'prototype'==9
    #define JSVAR_DATA_STRING_MAX_LEN 12 // (JSVAR_DATA_STRING_LEN + sizeof(JsVarRef)*3 + sizeof(JsVarRefCounter)) - but see JSV_STRING_LEN_MAX too
  #else
    typedef unsigned short JsVarRef;
    #define JSVAR_SIZE 20
    #define JSVAR_DATA_STRING_LEN  8 // Actually 9 seems like a good number as 'prototype'==9
    #define JSVAR_DATA_STRING_MAX_LEN 16 // (JSVAR_DATA_STRING_LEN + sizeof(JsVarRef)*3 + sizeof(JsVarRefCounter)) - but see JSV_STRING_LEN_MAX too - WE HAVE TO CLIP!
  #endif
#endif

typedef long long JsVarInt;
typedef unsigned long long JsVarIntUnsigned;
#ifdef USE_FLOATS
typedef float JsVarFloat;
#else
typedef double JsVarFloat;
#endif

typedef short JslCharPos;
#define JSSYSTIME_MAX 0x7FFFFFFFFFFFFFFFLL
typedef long long JsSysTime;

#define JSLEX_MAX_TOKEN_LENGTH  64
#define JS_ERROR_BUF_SIZE 64 // size of buffer error messages are written into
#define JS_ERROR_TOKEN_BUF_SIZE 16 // see jslTokenAsString

#define JS_NUMBER_BUFFER_SIZE 24

#define JSPARSE_MAX_SCOPES  8
// Don't restrict number of iterations now
//#define JSPARSE_MAX_LOOP_ITERATIONS 8192

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)
#define NOT_USED(x) ( (void)(x) )

// javascript specific names
#define JSPARSE_RETURN_VAR "return" // variable name used for returning function results
#define JSPARSE_PROTOTYPE_VAR "prototype"
#define JSPARSE_CONSTRUCTOR_VAR "constructor"
#define JSPARSE_INHERITS_VAR "__proto__"
// internal names that hopefully nobody will be able to access
#define JS_HIDDEN_CHAR '>' // initial character of var name determines that we shouldn't see this stuff
#define JS_HIDDEN_CHAR_STR ">"
#define JSPARSE_FUNCTION_CODE_NAME JS_HIDDEN_CHAR_STR"code"
#define JSPARSE_FUNCTION_SCOPE_NAME JS_HIDDEN_CHAR_STR"scope"
#define JSPARSE_MODULE_CACHE_NAME JS_HIDDEN_CHAR_STR"modules"

#if !defined(NO_ASSERT)
 #ifdef __STRING
   #define assert(X) if (!(X)) jsAssertFail(__FILE__,__LINE__,__STRING(X));
 #else
   #define assert(X) if (!(X)) jsAssertFail(__FILE__,__LINE__,"");
 #endif
#else
 #define assert(X)
#endif

/// Used when we have enums we want to squash down
#define PACKED_FLAGS  __attribute__ ((__packed__))

/// Used before functions that we want to ensure are not inlined (eg. "void NO_INLINE foo() {}")
#define NO_INLINE __attribute__ ((noinline))

/// Maximum amount of locks we ever expect to have on a variable (this could limit recursion) must be 2^n-1
#define JSV_LOCK_MAX  15

/// preprocessor power of 2 - suitable up to 16 bits
#define NEXT_POWER_2(X) \
   (((X) | (X)>>1 | (X)>>2 | (X)>>3 | \
    (X)>>4 | (X)>>5 | (X)>>6 | (X)>>7 | \
    (X)>>8 | (X)>>9 | (X)>>10 | (X)>>11 | \
    (X)>>12 | (X)>>13 | (X)>>14 | (X)>>15)+1)
/// Proprocessor get bit number
#define GET_BIT_NUMBER(X) \
  (((X)==    1)? 0: \
   ((X)==    2)? 1: \
   ((X)==    4)? 2: \
   ((X)==    8)? 3: \
   ((X)==   16)? 4: \
   ((X)==   32)? 5: \
   ((X)==   64)? 6: \
   ((X)==  128)? 7: \
   ((X)==  256)? 8: \
   ((X)==  512)? 9: \
   ((X)== 1024)?10: \
   ((X)== 2048)?11: \
   ((X)== 4096)?12: \
   ((X)== 8192)?13: \
   ((X)==16384)?14: \
   ((X)==32768)?15:10000/*error*/)



/** These flags are at the top of each JsVar and provide information about what it is, as
 * well as how many Locks it has. Everything is packed in as much as possible to allow us to
 * get down to within 2 bytes. */
typedef enum {
    JSV_UNUSED      = 0, ///< Variable not used for anything
    JSV_ROOT        = JSV_UNUSED+1, ///< The root of everything - there is only one of these
    // UNDEFINED is now just stored using '0' as the variable Ref
    JSV_NULL        = JSV_ROOT+1, ///< it seems null is its own data type
    JSV_STRING      = JSV_NULL+1, ///< string
    JSV_STRING_0    = JSV_STRING, // string of length 0
    JSV_STRING_MAX  = JSV_STRING_0+JSVAR_DATA_STRING_LEN,
    JSV_STRING_EXT  = JSV_STRING_MAX+1, ///< extra character data for string (if it didn't fit in first JsVar). These use unused pointer fields for extra characters
    JSV_STRING_EXT_0 = JSV_STRING_EXT,
    JSV_STRING_EXT_MAX = JSV_STRING_EXT_0+JSVAR_DATA_STRING_MAX_LEN,
    JSV_ARRAY = JSV_STRING_EXT_MAX+1, ///< A JavaScript Array Buffer - Implemented just like a String at the moment
    JSV_ARRAYBUFFER  = JSV_ARRAY+1,
    JSV_OBJECT      = JSV_ARRAYBUFFER+1,
    JSV_FUNCTION    = JSV_OBJECT+1,
    JSV_NUMERICSTART = JSV_FUNCTION+1, ///< --------- Start of numeric variable types
    JSV_INTEGER     = JSV_NUMERICSTART, ///< integer number (note JSV_NUMERICMASK)
    JSV_FLOAT       = JSV_INTEGER+1, ///< floating point double (note JSV_NUMERICMASK)
    JSV_BOOLEAN     = JSV_FLOAT+1, ///< boolean (note JSV_NUMERICMASK)
    JSV_PIN         = JSV_BOOLEAN+1, ///< pin (note JSV_NUMERICMASK)
    JSV_NUMERICEND  = JSV_PIN, ///< --------- End of numeric variable types
    JSV_VAR_END     = JSV_NUMERICEND, ///< End of numeric variable types

    JSV_VARTYPEMASK = NEXT_POWER_2(JSV_VAR_END)-1,

    // names can be STRING,
    JSV_NAME        = JSV_VARTYPEMASK+1, ///< a NAME of a variable - this isn't a variable itself (and can be an int/string/etc.)
    JSV_NATIVE      = JSV_NAME<<1, ///< to specify this is a native function, root, function parameter, OR that it should not be freed
    JSV_GARBAGE_COLLECT = JSV_NATIVE<<1, ///< When garbage collecting, this flag is true IF we should GC!
    JSV_IS_RECURSING = JSV_GARBAGE_COLLECT<<1, ///< used to stop recursive loops in jsvTrace
    JSV_LOCK_ONE    = JSV_IS_RECURSING<<1,
    JSV_LOCK_MASK   = JSV_LOCK_MAX * JSV_LOCK_ONE,



    JSV_ARRAYBUFFERNAME = JSV_NAME|JSV_ARRAYBUFFER, ///< used for indexing into an ArrayBuffer. varData is an INT in this case
    JSV_FUNCTION_PARAMETER = JSV_NATIVE | JSV_NAME, ///< this is inside a function, so it should be quite obvious

} PACKED_FLAGS JsVarFlags; // aiming to get this in 2 bytes!

/// The amount of bits we must shift to get the number of locks - forced to be a constant
static const int JSV_LOCK_SHIFT = GET_BIT_NUMBER(JSV_LOCK_ONE);

typedef enum LEX_TYPES {
    LEX_EOF = 0,
    LEX_ID = 256,
    LEX_INT,
    LEX_FLOAT,
    LEX_STR,
    LEX_UNFINISHED_COMMENT,

    LEX_EQUAL,
    LEX_TYPEEQUAL,
    LEX_NEQUAL,
    LEX_NTYPEEQUAL,
    LEX_LEQUAL,
    LEX_LSHIFT,
    LEX_LSHIFTEQUAL,
    LEX_GEQUAL,
    LEX_RSHIFT,
    LEX_RSHIFTUNSIGNED,
    LEX_RSHIFTEQUAL,
    LEX_RSHIFTUNSIGNEDEQUAL,
    LEX_PLUSEQUAL,
    LEX_MINUSEQUAL,
    LEX_PLUSPLUS,
    LEX_MINUSMINUS,
    LEX_MULEQUAL,
    LEX_DIVEQUAL,
    LEX_MODEQUAL,
    LEX_ANDEQUAL,
    LEX_ANDAND,
    LEX_OREQUAL,
    LEX_OROR,
    LEX_XOREQUAL,
    // reserved words
#define LEX_R_LIST_START LEX_R_IF
    LEX_R_IF,
    LEX_R_ELSE,
    LEX_R_DO,
    LEX_R_WHILE,
    LEX_R_FOR,
    LEX_R_BREAK,
    LEX_R_CONTINUE,
    LEX_R_FUNCTION,
    LEX_R_RETURN,
    LEX_R_VAR,
    LEX_R_THIS,
    LEX_R_TRUE,
    LEX_R_FALSE,
    LEX_R_NULL,
    LEX_R_UNDEFINED,
    LEX_R_NEW,
    LEX_R_IN,
    LEX_R_INSTANCEOF,
    LEX_R_SWITCH,
    LEX_R_CASE,
    LEX_R_DEFAULT,
    LEX_R_TYPEOF,
    LEX_R_VOID,

    LEX_R_LIST_END /* always the last entry */
} LEX_TYPES;

// To handle variable size bit fields
#define BITFIELD_DECL(BITFIELD, N) unsigned int BITFIELD[(N+31)/32]
#define BITFIELD_GET(BITFIELD, N) ((BITFIELD[(N)>>5] >> ((N)&31))&1)
#define BITFIELD_SET(BITFIELD, N, VALUE) (BITFIELD[(N)>>5] = (BITFIELD[(N)>>5]& (unsigned int)~(1 << ((N)&31))) | (unsigned int)((VALUE)?(1 << ((N)&31)):0)  )


static inline bool isWhitespace(char ch) {
    return (ch==' ') || (ch=='\t') || (ch=='\n') || (ch=='\r');
}

static inline bool isNumeric(char ch) {
    return (ch>='0') && (ch<='9');
}

static inline bool isHexadecimal(char ch) {
    return ((ch>='0') && (ch<='9')) ||
           ((ch>='a') && (ch<='f')) ||
           ((ch>='A') && (ch<='F'));
}
static inline bool isAlpha(char ch) {
    return ((ch>='a') && (ch<='z')) || ((ch>='A') && (ch<='Z')) || ch=='_';
}


bool isIDString(const char *s);

/** escape a character - if it is required. This may return a reference to a static array,
so you can't store the value it returns in a variable and call it again. */
const char *escapeCharacter(char ch);
/* convert a number in the given radix to an int. if radix=0, autodetect */
JsVarInt stringToIntWithRadix(const char *s, int radix, bool *hasError);
/* convert hex, binary, octal or decimal string into an int */
JsVarInt stringToInt(const char *s);

// forward decl
struct JsLex;
// ------------

void jsError(const char *fmt, ...);
void jsErrorInternal(const char *fmt, ...);
void jsErrorAt(const char *message, struct JsLex *lex, int tokenPos);
void jsWarn(const char *fmt, ...);
void jsWarnAt(const char *message, struct JsLex *lex, int tokenPos);
void jsAssertFail(const char *file, int line, const char *expr);

#ifdef FAKE_STDLIB
void exit(int errcode);
char *strncat(char *dst, const char *src, size_t c);
char *strncpy(char *dst, const char *src, size_t c);
size_t strlen(const char *s);
int strcmp(const char *a, const char *b);
void *memcpy(void *dst, const void *src, size_t size);
void *memset(void *dst, int val, size_t size);
#define RAND_MAX (0xFFFFFFFFU)
unsigned int rand();
#else
// FIXME: use itoa/ftoa direct - sprintf is huge
//#define itoa(val,str,base) sprintf(str,"%d",(int)val)
//#define ftoa(val,str) sprintf(str,"%f",val)

#endif

JsVarFloat stringToFloat(const char *str);

#ifndef HAS_STDLIB
void itoa(JsVarInt val,char *str,unsigned int base);
#endif
char itoch(int val);
void ftoa(JsVarFloat val,char *str);

/// Wrap a value so it is always between 0 and size (eg. wrapAround(angle, 360))
JsVarFloat wrapAround(JsVarFloat val, JsVarFloat size);


typedef void (*vcbprintf_callback)(const char *str, void *user_data);
/** Espruino-special printf with a callback
 * Supported are:
 *   %d = int
 *   %x = int as hex
 *   %L = JsVarInt
 *   %Lx = JsVarInt as hex
 *   %f = JsVarFloat
 *   %s = string (char *)
 *   %c = char
 *   %v = JsVar *
 *   %p = Pin
 *
 * Anything else will assert
 */
void vcbprintf(vcbprintf_callback user_callback, void *user_data, const char *fmt, va_list argp);


#endif /* JSUTILS_H_ */
