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
#include "jsutils.h"
#include "jslex.h"
#include "jshardware.h"
#include "jsinteractive.h"

// needed for isnan / isfinite
#ifdef ARM
#include "mconf.h"
#include "protos.h"
#else
#include <math.h>
#endif

extern double jswrap_math_pow(double x, double y); // for pow

bool isIDString(const char *s) {
    if (!isAlpha(*s))
        return false;
    while (*s) {
        if (!(isAlpha(*s) || isNumeric(*s)))
            return false;
        s++;
    }
    return true;
}

/** escape a character - if it is required. This may return a reference to a static array,
so you can't store the value it returns in a variable and call it again. */
const char *escapeCharacter(char ch) {
  if (ch=='\b') return "\\b";
  if (ch=='\f') return "\\f";
  if (ch=='\n') return "\\n";
  if (ch=='\a') return "\\a";
  if (ch=='\r') return "\\r";
  if (ch=='\t') return "\\t";
  if (ch=='\\') return "\\\\";
  if (ch=='"') return "\\\"";
  static char buf[5];
  if (ch<32) {
    /** just encode as hex - it's more understandable
     * and doesn't have the issue of "\16"+"1" != "\161" */
    buf[0]='\\';
    buf[1]='x';
    int n = (ch>>4)&15;
    buf[2] = (char)((n<10)?('0'+n):('A'+n-10));
    n=ch&15;
    buf[3] = (char)((n<10)?('0'+n):('A'+n-10));
    buf[4] = 0;
    return buf;
  }
  buf[1] = 0;
  buf[0] = ch;
  return buf;
}

/* convert a number in the given radix to an int. if radix=0, autodetect */
JsVarInt stringToIntWithRadix(const char *s, int forceRadix, bool *hasError) {
  bool isNegated = false;
  JsVarInt v = 0;
  JsVarInt radix = 10;
  if (*s == '-') {
    isNegated = true;
    s++;
  }
  if (*s == '0') {
    radix = 8;
    s++;

    // OctalIntegerLiteral: 0o01, 0O01
    if (*s == 'o' || *s == 'O') {
      radix = 8;
      s++;

    // HexIntegerLiteral: 0x01, 0X01
    } else if (*s == 'x' || *s == 'X') {
      radix = 16;
      s++;

    // BinaryIntegerLiteral: 0b01, 0B01
    } else if (*s == 'b' || *s == 'B') {
      radix = 2;
      s++;
    }
  }
  if (forceRadix>0 && forceRadix<=36)
    radix = forceRadix;

  while (*s) {
    int digit = 0;
    if (*s >= '0' && *s <= '9')
      digit = (*s - '0');
    else if (*s >= 'a' && *s <= 'f')
      digit = (10 + *s - 'a');
    else if (*s >= 'A' && *s <= 'F')
      digit = (10 + *s - 'A');
    else break;
    if (digit>=radix)
      break;
    v = v*radix + digit;
    s++;
  }

  if (hasError) *hasError = *s!=0; // we're ok if we reached the end of the string

  if (isNegated) return -v;
  return v;
}

/* convert hex, binary, octal or decimal string into an int */
JsVarInt stringToInt(const char *s) {
    return stringToIntWithRadix(s,0,0);
}

void jsError(const char *fmt, ...) {
  jsiConsoleRemoveInputLine();
  jsiConsolePrint("ERROR: ");
  va_list argp;
  va_start(argp, fmt);
  vcbprintf((vcbprintf_callback)jsiConsolePrint,0, fmt, argp);
  va_end(argp);
  jsiConsolePrint("\n");
}

void jsErrorInternal(const char *fmt, ...) {
  jsiConsoleRemoveInputLine();
  jsiConsolePrint("INTERNAL ERROR: ");
  va_list argp;
  va_start(argp, fmt);
  vcbprintf((vcbprintf_callback)jsiConsolePrint,0, fmt, argp);
  va_end(argp);
  jsiConsolePrint("\n");
}

void jsErrorAt(const char *message, struct JsLex *lex, int tokenPos) {
  jsiConsoleRemoveInputLine();
  jsiConsolePrint("ERROR: ");
  jsiConsolePrint(message);
  jsiConsolePrint(" at ");
  jsiConsolePrintPosition(lex, tokenPos);
  jsiConsolePrintTokenLineMarker(lex, tokenPos);
}

void jsWarn(const char *fmt, ...) {
  jsiConsoleRemoveInputLine();
  jsiConsolePrint("WARNING: ");
  va_list argp;
  va_start(argp, fmt);
  vcbprintf((vcbprintf_callback)jsiConsolePrint,0, fmt, argp);
  va_end(argp);
  jsiConsolePrint("\n");
}

void jsWarnAt(const char *message, struct JsLex *lex, int tokenPos) {
  jsiConsoleRemoveInputLine();
  jsiConsolePrint("WARNING: ");
  jsiConsolePrint(message);
  jsiConsolePrint(" at ");
  jsiConsolePrintPosition(lex, tokenPos);
}

void jsAssertFail(const char *file, int line, const char *expr) {
  jsiConsoleRemoveInputLine();
  if (expr) {
    jsiConsolePrintf("ASSERT(%s) FAILED AT ", expr);
  } else
    jsiConsolePrint("ASSERT FAILED AT ");
  jsiConsolePrintf("%s:%d\n",file,line);

  jsvTrace(jsvGetRef(jsvFindOrCreateRoot()), 2);
  exit(1);
}

#ifdef SDCC
void exit(int errcode) {dst;
    jsiConsolePrint("EXIT CALLED.\n");
}
#endif

#ifdef FAKE_STDLIB
int __errno;

void exit(int errcode) {
    NOT_USED(errcode);
    jsiConsolePrint("EXIT CALLED.\n");
    while (1);
}

char * strncat(char *dst, const char *src, size_t c) {
        char *dstx = dst;
        while (*(++dstx)) c--;
        while (*src && c>1) {
          *(dstx++) = *(src++);
          c--;
        }
        if (c>0) *dstx = 0;
        return dst;
}
char *strncpy(char *dst, const char *src, size_t c) {
        char *dstx = dst;
        while (*src && c>1) {
          *(dstx++) = *(src++);
          c--;
        }
        if (c>0) *dstx = 0;
        return dst;
}
size_t strlen(const char *s) {
        size_t l=0;
        while (*(s++)) l++;
        return l;
}
int strcmp(const char *a, const char *b) {
        while (*a && *b) {
                if (*a != *b)
                        return *a - *b; // correct?
                a++;b++;
        }
        return *a - *b;
}
void *memcpy(void *dst, const void *src, size_t size) {
        size_t i;
        for (i=0;i<size;i++)
                ((char*)dst)[i] = ((char*)src)[i];
        return dst;
}

void *memset(void *dst, int val, size_t size) {
  unsigned char *d = (unsigned char*)dst;
  unsigned int i;
  for (i=0;i<size;i++)
    d[i]=(unsigned char)val;
  return dst;
}

unsigned int rand() {
    static unsigned int m_w = 0xDEADBEEF;    /* must not be zero */
    static unsigned int m_z = 0xCAFEBABE;    /* must not be zero */

    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}
#endif

JsVarFloat stringToFloat(const char *s) {
  bool isNegated = false;
  JsVarFloat v = 0;
  JsVarFloat mul = 0.1;
  if (*s == '-') {
    isNegated = true;
    s++;
  }
  // handle integer part
  while (*s) {
    if (*s >= '0' && *s <= '9')
      v = (v*10) + (*s - '0');
    else break;
    s++;
  }
  // handle decimal point
  if (*s == '.') {
    s++; // skip .

    while (*s) {
      if (*s >= '0' && *s <= '9')
        v += mul*(*s - '0');
      else break;
      mul /= 10;
      s++;
    }
  }

  // handle exponentials
  if (*s == 'e' || *s == 'E') {
    s++;  // skip E
    bool isENegated = false;
    if (*s == '-' || *s == '+') {
      isENegated = *s=='-';
      s++;
    }
    int e = 0;
    while (*s) {
      if (*s >= '0' && *s <= '9')
        e = (e*10) + (*s - '0');
      else break;
      s++;
    }
    if (isENegated) e=-e;
    v = v * jswrap_math_pow(10, e);
  }
  // check we have parsed everything
  if (*s!=0) return NAN;

  if (isNegated) return -v;
  return v;
}


char itoch(int val) {
  if (val<10) return (char)('0'+val);
  return (char)('A'+val-10);
}

#ifndef HAS_STDLIB
void itoa(JsVarInt vals,char *str,unsigned int base) {
  JsVarIntUnsigned val;
  if (vals<0) {
    *(str++)='-';
    val = (JsVarIntUnsigned)(-vals);
  } else {
    val = (JsVarIntUnsigned)vals;
  }
  JsVarIntUnsigned d = 1;
  while (d*base <= val) d*=base;
  while (d > 1) {
    unsigned int v = (unsigned int)(val / d);
    val -= v*d;
    *(str++) = itoch((int)v);
    d /= base;
  }
  *(str++)=itoch((int)val);
  *(str++)=0;
}
#endif

void ftoa(JsVarFloat val,char *str) {
  if (isnan(val)) strncpy(str,"NaN",4);
  else if (!isfinite(val)) {
    if (val<0) strncpy(str,"-Infinity",10);
    else strncpy(str,"Infinity",10);
  } else {
    const JsVarFloat base = 10;
    if (val<0) {
      *(str++)='-';
      val = -val;
    }
    JsVarFloat d = 1;
    while (d*base <= val) d*=base;
    while (d >= 1) {
      int v = (int)(val / d);
      val -= v*d;
      *(str++)=itoch(v);
      d /= base;
    }
  #ifndef USE_NO_FLOATS
    if (val>0) {
      *(str++)='.';
      while (val>0.000001) {
        int v = (int)((val / d) + 0.0000005);
        val -= v*d;
        *(str++)=itoch(v);
        d /= base;
      }
    }
  #endif

    *(str++)=0;
  }
}


/// Wrap a value so it is always between 0 and size (eg. wrapAround(angle, 360))
JsVarFloat wrapAround(JsVarFloat val, JsVarFloat size) {
  val = val / size;
  val = val - (int)val;
  return val * size;
}

/** Espruino-special printf with a callback
 * Supported are:
 *   %d = int
 *   %x = int as hex
 *   %L = JsVarInt
 *   %Lx = JsVarInt as hex
 *   %f = JsVarFloat
 *   %s = string (char *)
 *   %c = char
 *   %v = JsVar * (prints var as string)
 *   %t = JsVar * (prints type of var)
 *   %p = Pin
 *
 * Anything else will assert
 */
void vcbprintf(vcbprintf_callback user_callback, void *user_data, const char *fmt, va_list argp) {
  char buf[32];
  while (*fmt) {
    if (*fmt == '%') {
      fmt++;
      switch (*fmt++) {
      case 'd': itoa(va_arg(argp, int), buf, 10); user_callback(buf,user_data); break;
      case 'x': itoa(va_arg(argp, int), buf, 16); user_callback(buf,user_data); break;
      case 'L': {
        unsigned int rad = 10;
        if (*fmt=='x') { rad=16; fmt++; }
        itoa(va_arg(argp, JsVarInt), buf, rad); user_callback(buf,user_data);
      } break;
      case 'f': ftoa(va_arg(argp, JsVarFloat), buf); user_callback(buf,user_data);  break;
      case 's': user_callback(va_arg(argp, char *), user_data); break;
      case 'c': buf[0]=(char)va_arg(argp, int/*char*/);buf[1]=0; user_callback(buf, user_data); break;
      case 'v': {
        JsVar *v = jsvAsString(va_arg(argp, JsVar*), false/*no unlock*/);
        buf[1] = 0;
        JsvStringIterator it;
        jsvStringIteratorNew(&it, v, 0);
        // OPT: this could be faster than it is (sending whole blocks at once)
        while (jsvStringIteratorHasChar(&it)) {
          buf[0] = jsvStringIteratorGetChar(&it);
          user_callback(buf,user_data);
          jsvStringIteratorNext(&it);
        }
        jsvStringIteratorFree(&it);
        jsvUnLock(v);
      } break;
      case 't': user_callback(jsvGetTypeOf(va_arg(argp, JsVar*)), user_data); break;
      case 'p': jshGetPinString(buf, (Pin)va_arg(argp, int/*Pin*/)); user_callback(buf, user_data); break;
      default: assert(0); return; // eep
      }
    } else {
      buf[0] = *(fmt++);
      buf[1] = 0;
      user_callback(&buf[0], user_data);
    }
  }
}


