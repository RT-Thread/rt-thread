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
 * Lexer (convert JsVar strings into a series of tokens)
 * ----------------------------------------------------------------------------
 */
#include "jslex.h"


void jslSeek(JsLex *lex, JslCharPos seekToChar) {
  jsvStringIteratorFree(&lex->it);
  jsvStringIteratorNew(&lex->it, lex->sourceVar, seekToChar);
}

void NO_INLINE jslGetNextCh(JsLex *lex) {
  lex->currCh = lex->nextCh;
  lex->nextCh = jsvStringIteratorGetChar(&lex->it);
  jsvStringIteratorNextInline(&lex->it);
}

static inline void jslTokenAppendChar(JsLex *lex, char ch) {
  /* Add character to buffer but check it isn't too big.
   * Also Leave ONE character at the end for null termination */
  if (lex->tokenl < JSLEX_MAX_TOKEN_LENGTH-1) {
    lex->token[lex->tokenl++] = ch;
  }
#ifdef DEBUG
  else {
    jsWarnAt("Token name is too long! skipping character", lex, lex->tokenStart);
  }
#endif
}

static bool jslIsToken(JsLex *lex, const char *token, int startOffset) {
  int i;
  for (i=startOffset;i<lex->tokenl;i++) {
    if (lex->token[i]!=token[i]) return false;
    // if token is smaller than lex->token, there will be a null char
    // which will be different from the token
  }
  return token[lex->tokenl] == 0; // only match if token ends now
}

void jslGetNextToken(JsLex *lex) {
  lex->tk = LEX_EOF;
  lex->tokenl = 0; // clear token string
  if (lex->tokenValue) {
    jsvUnLock(lex->tokenValue);
    lex->tokenValue = 0;
  }
  while (lex->currCh && isWhitespace(lex->currCh)) jslGetNextCh(lex);
  // newline comments
  if (lex->currCh=='/' && lex->nextCh=='/') {
      while (lex->currCh && lex->currCh!='\n') jslGetNextCh(lex);
      jslGetNextCh(lex);
      jslGetNextToken(lex);
      return;
  }
  // block comments
  if (lex->currCh=='/' && lex->nextCh=='*') {
      while (lex->currCh && !(lex->currCh=='*' && lex->nextCh=='/'))
        jslGetNextCh(lex);
      if (!lex->currCh) {
        lex->tk = LEX_UNFINISHED_COMMENT;
        return; /* an unfinished multi-line comment. When in interactive console,
                   detect this and make sure we accept new lines */
      }
      jslGetNextCh(lex);
      jslGetNextCh(lex);
      jslGetNextToken(lex);
      return;
  }
  // record beginning of this token
  lex->tokenLastStart = lex->tokenStart;
  lex->tokenStart = (JslCharPos)(lex->it.index-2);
  // tokens
  if (isAlpha(lex->currCh) || lex->currCh=='$') { //  IDs
      while (isAlpha(lex->currCh) || isNumeric(lex->currCh) || lex->currCh=='$') {
          jslTokenAppendChar(lex, lex->currCh);
          jslGetNextCh(lex);
      }
      lex->tk = LEX_ID;
      // We do fancy stuff here to reduce number of compares (hopefully GCC creates a jump table)
      switch (lex->token[0]) {
      case 'b': if (jslIsToken(lex,"break", 1)) lex->tk = LEX_R_BREAK;
                break;
      case 'c': if (jslIsToken(lex,"case", 1)) lex->tk = LEX_R_CASE;
                else if (jslIsToken(lex,"continue", 1)) lex->tk = LEX_R_CONTINUE;
                break;
      case 'd': if (jslIsToken(lex,"default", 1)) lex->tk = LEX_R_DEFAULT;
                else if (jslIsToken(lex,"do", 1)) lex->tk = LEX_R_DO;
                break;
      case 'e': if (jslIsToken(lex,"else", 1)) lex->tk = LEX_R_ELSE;
                break;
      case 'f': if (jslIsToken(lex,"false", 1)) lex->tk = LEX_R_FALSE;
                else if (jslIsToken(lex,"for", 1)) lex->tk = LEX_R_FOR;
                else if (jslIsToken(lex,"function", 1)) lex->tk = LEX_R_FUNCTION;
                break;
      case 'i': if (jslIsToken(lex,"if", 1)) lex->tk = LEX_R_IF;
                else if (jslIsToken(lex,"in", 1)) lex->tk = LEX_R_IN;
                else if (jslIsToken(lex,"instanceof", 1)) lex->tk = LEX_R_INSTANCEOF;
                break;
      case 'n': if (jslIsToken(lex,"new", 1)) lex->tk = LEX_R_NEW;
                else if (jslIsToken(lex,"null", 1)) lex->tk = LEX_R_NULL;
                break;
      case 'r': if (jslIsToken(lex,"return", 1)) lex->tk = LEX_R_RETURN;
                break;
      case 's': if (jslIsToken(lex,"switch", 1)) lex->tk = LEX_R_SWITCH;
                break;
      case 't': if (jslIsToken(lex,"this", 1)) lex->tk = LEX_R_THIS;
                else if (jslIsToken(lex,"true", 1)) lex->tk = LEX_R_TRUE;
                else if (jslIsToken(lex,"typeof", 1)) lex->tk = LEX_R_TYPEOF;
                break;
      case 'u': if (jslIsToken(lex,"undefined", 1)) lex->tk = LEX_R_UNDEFINED;
                break;
      case 'w': if (jslIsToken(lex,"while", 1)) lex->tk = LEX_R_WHILE;
                break;
      case 'v': if (jslIsToken(lex,"var", 1)) lex->tk = LEX_R_VAR;
                else if (jslIsToken(lex,"void", 1)) lex->tk = LEX_R_VOID;
                break;
      default: break;
      }
  } else if (isNumeric(lex->currCh)) { // Numbers
      // TODO: check numbers aren't the wrong format
      bool canBeFloating = true;
      if (lex->currCh=='0') {
        jslTokenAppendChar(lex, lex->currCh);
        jslGetNextCh(lex);
      }

      if ((lex->currCh=='x' || lex->currCh=='X') ||
          (lex->currCh=='b' || lex->currCh=='B') ||
          (lex->currCh=='o' || lex->currCh=='O')) {
        canBeFloating = false;
        jslTokenAppendChar(lex, lex->currCh); jslGetNextCh(lex);
      }
      lex->tk = LEX_INT;
      while (isNumeric(lex->currCh) || (!canBeFloating && isHexadecimal(lex->currCh))) {
        jslTokenAppendChar(lex, lex->currCh);
        jslGetNextCh(lex);
      }
      if (canBeFloating && lex->currCh=='.') {
          lex->tk = LEX_FLOAT;
          jslTokenAppendChar(lex, '.');
          jslGetNextCh(lex);
          while (isNumeric(lex->currCh)) {
            jslTokenAppendChar(lex, lex->currCh);
            jslGetNextCh(lex);
          }
      }
      // do fancy e-style floating point
      if (canBeFloating && (lex->currCh=='e'||lex->currCh=='E')) {
        lex->tk = LEX_FLOAT;
        jslTokenAppendChar(lex, lex->currCh); jslGetNextCh(lex);
        if (lex->currCh=='-' || lex->currCh=='+') { jslTokenAppendChar(lex, lex->currCh); jslGetNextCh(lex); }
        while (isNumeric(lex->currCh)) {
          jslTokenAppendChar(lex, lex->currCh); jslGetNextCh(lex);
        }
      }
  } else if (lex->currCh=='"' || lex->currCh=='\'') {
      char delim = lex->currCh;
      lex->tokenValue = jsvNewFromEmptyString();
      // strings...
      jslGetNextCh(lex);
      while (lex->currCh && lex->currCh!=delim) {
          if (lex->currCh == '\\') {
              jslGetNextCh(lex);
              char ch = lex->currCh;
              switch (lex->currCh) {
              case 'n'  : ch = '\n'; jslGetNextCh(lex); break;
              case 'a'  : ch = '\a'; jslGetNextCh(lex); break;
              case 'r'  : ch = '\r'; jslGetNextCh(lex); break;
              case 't'  : ch = '\t'; jslGetNextCh(lex); break;
              case 'x' : { // hex digits
                            char buf[5] = "0x??";
                            jslGetNextCh(lex);
                            buf[2] = lex->currCh; jslGetNextCh(lex);
                            buf[3] = lex->currCh; jslGetNextCh(lex);
                            ch = (char)stringToInt(buf);
                         } break;
              default:
                       if (lex->currCh>='0' && lex->currCh<='7') {
                         // octal digits
                         char buf[5] = "0";
                         buf[1] = lex->currCh;
                         int n=2;
                         jslGetNextCh(lex);
                         if (lex->currCh>='0' && lex->currCh<='7') {
                           buf[n++] = lex->currCh; jslGetNextCh(lex);
                           if (lex->currCh>='0' && lex->currCh<='7') {
                             buf[n++] = lex->currCh; jslGetNextCh(lex);
                           }
                         }
                         buf[n]=0;
                         ch = (char)stringToInt(buf);
                       } else {
                         // for anything else, just push the character through
                         jslGetNextCh(lex);
                       }
                       break;
              }
              if (lex->tokenValue) {
                jslTokenAppendChar(lex, ch);
                jsvAppendCharacter(lex->tokenValue, ch);
              }
          } else {
            if (lex->tokenValue) {
              jslTokenAppendChar(lex, lex->currCh);
              jsvAppendCharacter(lex->tokenValue, lex->currCh);
            }
            jslGetNextCh(lex);
          }
      }
      jslGetNextCh(lex);
      lex->tk = LEX_STR;
  } else {
      // single chars
      lex->tk = lex->currCh;
      jslGetNextCh(lex);
      if (lex->tk=='=' && lex->currCh=='=') { // ==
          lex->tk = LEX_EQUAL;
          jslGetNextCh(lex);
          if (lex->currCh=='=') { // ===
            lex->tk = LEX_TYPEEQUAL;
            jslGetNextCh(lex);
          }
      } else if (lex->tk=='!' && lex->currCh=='=') { // !=
          lex->tk = LEX_NEQUAL;
          jslGetNextCh(lex);
          if (lex->currCh=='=') { // !==
            lex->tk = LEX_NTYPEEQUAL;
            jslGetNextCh(lex);
          }
      } else if (lex->tk=='<') {
        if (lex->currCh=='=') {
          lex->tk = LEX_LEQUAL;
          jslGetNextCh(lex);
        } else if (lex->currCh=='<') {
            lex->tk = LEX_LSHIFT;
            jslGetNextCh(lex);
            if (lex->currCh=='=') { // <<=
              lex->tk = LEX_LSHIFTEQUAL;
              jslGetNextCh(lex);
            }
        }
      } else if (lex->tk=='>') {
        if (lex->currCh=='=') {
          lex->tk = LEX_GEQUAL;
          jslGetNextCh(lex);
        } else if (lex->currCh=='>') {
          lex->tk = LEX_RSHIFT;
          jslGetNextCh(lex);
          if (lex->currCh=='=') { // >>=
            lex->tk = LEX_RSHIFTEQUAL;
            jslGetNextCh(lex);
          } else if (lex->currCh=='>') { // >>>
            jslGetNextCh(lex);
            if (lex->currCh=='=') { // >>>=
              lex->tk = LEX_RSHIFTUNSIGNEDEQUAL;
              jslGetNextCh(lex);
            } else {
              lex->tk = LEX_RSHIFTUNSIGNED;
            }
          }
        }
      }  else if (lex->tk=='+') {
          if (lex->currCh=='=') {
            lex->tk = LEX_PLUSEQUAL;
            jslGetNextCh(lex);
          } else if (lex->currCh=='+') {
            lex->tk = LEX_PLUSPLUS;
            jslGetNextCh(lex);
          }
      }  else if (lex->tk=='-') {
          if (lex->currCh=='=') {
            lex->tk = LEX_MINUSEQUAL;
            jslGetNextCh(lex);
          } else if (lex->currCh=='-') {
            lex->tk = LEX_MINUSMINUS;
            jslGetNextCh(lex);
          }
      } else if (lex->tk=='&') {
          if (lex->currCh=='=') {
            lex->tk = LEX_ANDEQUAL;
            jslGetNextCh(lex);
          } else if (lex->currCh=='&') {
            lex->tk = LEX_ANDAND;
            jslGetNextCh(lex);
          }
      } else if (lex->tk=='|') {
          if (lex->currCh=='=') {
            lex->tk = LEX_OREQUAL;
            jslGetNextCh(lex);
          } else if (lex->tk=='|' && lex->currCh=='|') {
            lex->tk = LEX_OROR;
            jslGetNextCh(lex);
          }
      } else if (lex->tk=='^' && lex->currCh=='=') {
          lex->tk = LEX_XOREQUAL;
          jslGetNextCh(lex);
      } else if (lex->tk=='*' && lex->currCh=='=') {
          lex->tk = LEX_MULEQUAL;
          jslGetNextCh(lex);
      } else if (lex->tk=='/' && lex->currCh=='=') {
          lex->tk = LEX_DIVEQUAL;
          jslGetNextCh(lex);
      } else if (lex->tk=='%' && lex->currCh=='=') {
          lex->tk = LEX_MODEQUAL;
          jslGetNextCh(lex);
      }
  }
  /* This isn't quite right yet */
  lex->tokenLastEnd = lex->tokenEnd;
  lex->tokenEnd = (JslCharPos)(lex->it.index-3)/*because of nextCh/currCh/etc */;
}

static inline void jslPreload(JsLex *lex) {
  // set up..
  jslGetNextCh(lex);
  jslGetNextCh(lex);
  jslGetNextToken(lex);
}

void jslInit(JsLex *lex, JsVar *var) {
  lex->sourceVar = jsvLockAgain(var);
  // reset stuff
  lex->tk = 0;
  lex->tokenStart = 0;
  lex->tokenEnd = 0;
  lex->tokenLastStart = 0;
  lex->tokenLastEnd = 0;
  lex->tokenl = 0;
  lex->tokenValue = 0;
  // set up iterator
  jsvStringIteratorNew(&lex->it, lex->sourceVar, 0);
  jslPreload(lex);
}

void jslKill(JsLex *lex) {
  lex->tk = LEX_EOF; // safety ;)
  jsvStringIteratorFree(&lex->it);
  if (lex->tokenValue) {
    jsvUnLock(lex->tokenValue);
    lex->tokenValue = 0;
  }
  jsvUnLock(lex->sourceVar);
}

void jslSeekTo(JsLex *lex, JslCharPos seekToChar) {
  jslSeek(lex, seekToChar);
  jslPreload(lex);
}

void jslReset(JsLex *lex) {
  jslSeekTo(lex, 0);
}

void jslTokenAsString(int token, char *str, size_t len) {
  // see JS_ERROR_TOKEN_BUF_SIZE
  if (token>32 && token<128) {
      assert(len>=4);
      str[0] = '\'';
      str[1] = (char)token;
      str[2] = '\'';
      str[3] = 0;
      return;
  }

  switch (token) {
      case LEX_EOF : strncpy(str, "EOF", len); return;
      case LEX_ID : strncpy(str, "ID", len); return;
      case LEX_INT : strncpy(str, "INT", len); return;
      case LEX_FLOAT : strncpy(str, "FLOAT", len); return;
      case LEX_STR : strncpy(str, "STRING", len); return;
  }
  if (token>=LEX_EQUAL && token<LEX_R_LIST_END) {
    const char tokenNames[] =
      /* LEX_EQUAL      :   */ "==\0"
      /* LEX_TYPEEQUAL  :   */ "===\0"
      /* LEX_NEQUAL     :   */ "!=\0"
      /* LEX_NTYPEEQUAL :   */ "!==\0"
      /* LEX_LEQUAL    :    */ "<=\0"
      /* LEX_LSHIFT     :   */ "<<\0"
      /* LEX_LSHIFTEQUAL :  */ "<<=\0"
      /* LEX_GEQUAL      :  */ ">=\0"
      /* LEX_RSHIFT      :  */ ">>\0"
      /* LEX_RSHIFTUNSIGNED */ ">>>\0"
      /* LEX_RSHIFTEQUAL :  */ ">>=\0"
      /* LEX_RSHIFTUNSIGNEDEQUAL */ ">>>=\0"
      /* LEX_PLUSEQUAL   :  */ "+=\0"
      /* LEX_MINUSEQUAL  :  */ "-=\0"
      /* LEX_PLUSPLUS :     */ "++\0"
      /* LEX_MINUSMINUS     */ "--\0"
      /* LEX_MULEQUAL :     */ "*=\0"
      /* LEX_DIVEQUAL :     */ "/=\0"
      /* LEX_MODEQUAL :     */ "%=\0"
      /* LEX_ANDEQUAL :     */ "&=\0"
      /* LEX_ANDAND :       */ "&&\0"
      /* LEX_OREQUAL :      */ "|=\0"
      /* LEX_OROR :         */ "||\0"
      /* LEX_XOREQUAL :     */ "^=\0"

      // reserved words
      /*LEX_R_IF :       */ "if\0"
      /*LEX_R_ELSE :     */ "else\0"
      /*LEX_R_DO :       */ "do\0"
      /*LEX_R_WHILE :    */ "while\0"
      /*LEX_R_FOR :      */ "for\0"
      /*LEX_R_BREAK :    */ "return\0"
      /*LEX_R_CONTINUE   */ "continue\0"
      /*LEX_R_FUNCTION   */ "function\0"
      /*LEX_R_RETURN     */ "return\0"
      /*LEX_R_VAR :      */ "var\0"
      /*LEX_R_THIS :     */ "this\0"
      /*LEX_R_TRUE :     */ "true\0"
      /*LEX_R_FALSE :    */ "false\0"
      /*LEX_R_NULL :     */ "null\0"
      /*LEX_R_UNDEFINED  */ "undefined\0"
      /*LEX_R_NEW :      */ "new\0"
      /*LEX_R_IN :       */ "in\0"
      /*LEX_R_INSTANCEOF */ "instanceof\0"
      /*LEX_R_SWITCH */     "switch\0"
      /*LEX_R_CASE */       "case\0"
      /*LEX_R_DEFAULT */    "default\0"
      /*LEX_R_TYPEOF :   */ "typeof\0"
      /*LEX_R_VOID :     */ "void\0"
        ;
    unsigned int p = 0;
    int n = token-LEX_EQUAL;
    while (n>0 && p<sizeof(tokenNames)) {
      while (tokenNames[p] && p<sizeof(tokenNames)) p++;
      p++; // skip the zero
      n--; // next token
    }
    assert(n==0);
    strncpy(str, &tokenNames[p], len);
    return;
  }

  assert(len>=10);
  strncpy(str, "?[",len);
  itoa(token, &str[2], 10);
  strncat(str, "]",len);
}

void jslGetTokenString(JsLex *lex, char *str, size_t len) {
  if (lex->tk == LEX_ID) {
    strncpy(str, "ID:", len);
    strncat(str, jslGetTokenValueAsString(lex), len);
  } else if (lex->tk == LEX_STR) {
    strncpy(str, "String:'", len);
    strncat(str, jslGetTokenValueAsString(lex), len);
    strncat(str, "'", len);
  } else
    jslTokenAsString(lex->tk, str, len);
}

char *jslGetTokenValueAsString(JsLex *lex) {
  assert(lex->tokenl < JSLEX_MAX_TOKEN_LENGTH);
  lex->token[lex->tokenl]  = 0; // add final null
  return lex->token;
}

JsVar *jslGetTokenValueAsVar(JsLex *lex) {
  if (lex->tokenValue) {
    return jsvLockAgain(lex->tokenValue);
  } else {
    assert(lex->tokenl < JSLEX_MAX_TOKEN_LENGTH);
    lex->token[lex->tokenl]  = 0; // add final null
    return jsvNewFromString(lex->token);
  }
}

/// Match, and return true on success, false on failure
bool jslMatch(JsLex *lex, int expected_tk) {
  if (lex->tk!=expected_tk) {
      char buf[JS_ERROR_BUF_SIZE];
      size_t bufpos = 0;
      strncpy(&buf[bufpos], "Got ", JS_ERROR_BUF_SIZE-bufpos);
      bufpos = strlen(buf);
      jslGetTokenString(lex, &buf[bufpos], JS_ERROR_BUF_SIZE-bufpos);
      bufpos = strlen(buf);
      strncpy(&buf[bufpos], " expected ", JS_ERROR_BUF_SIZE-bufpos);
      bufpos = strlen(buf);
      jslTokenAsString(expected_tk, &buf[bufpos], JS_ERROR_BUF_SIZE-bufpos);
      jsErrorAt(buf, lex, lex->tokenStart);
      // Sod it, skip this token anyway - stops us looping
      jslGetNextToken(lex);
      return false;
  }
  jslGetNextToken(lex);
  return true;
}

