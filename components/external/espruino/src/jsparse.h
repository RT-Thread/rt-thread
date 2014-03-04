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
 * Recursive descent parser for code execution
 * ----------------------------------------------------------------------------
 */
#ifndef JSPARSE_H_
#define JSPARSE_H_

#include "jsvar.h"
#include "jslex.h"


typedef struct {
  JsVar  *root;   ///< root of symbol table
} JsParse;

void jspInit(JsParse *parse);
void jspKill(JsParse *parse);

// jspSoft* - 'release' or 'claim' anything we are using, but ensure that it doesn't get freed
void jspSoftInit(JsParse *parse); ///< used when recovering from or saving to flash
void jspSoftKill(JsParse *parse); ///< used when recovering from or saving to flash
bool jspIsCreatedObject(JsParse *parse, JsVar *v); ///< Is v likely to have been created by this parser?
/** Returns true if the constructor function given is the same as that
 * of the object with the given name. */
bool jspIsConstructor(JsVar *constructor, const char *constructorName);

/// Create a new built-in object that jswrapper can use to check for built-in functions
JsVar *jspNewBuiltin(const char *name);
/** Create a new object of the given instance and add it to root with name 'name'.
 * If name!=0, added to root with name, and the name is returned
 * If name==0, not added to root and Object itself returned */
JsVar *jspNewObject(JsParse *parse, const char *name, const char *instanceOf);

/// if interrupting execution, this is set
bool jspIsInterrupted();
/// if interrupting execution, this is set
void jspSetInterrupted(bool interrupt);
/// Has there been an error during parsing
bool jspHasError();

bool jspAddNativeFunction(JsParse *parse, const char *funcDesc, JsCallback callbackPtr);
JsVar *jspEvaluateVar(JsParse *parse, JsVar *str, JsVar *scope);
JsVar *jspEvaluate(JsParse *parse, const char *str);
bool jspExecuteFunction(JsParse *parse, JsVar *func, JsVar *parent, int argCount, JsVar **argPtr);

/// Evaluate a JavaScript module and return its exports
JsVar *jspEvaluateModule(JsParse *parse, JsVar *moduleContents);

/** When parsing, this enum defines whether
 we are executing or not */
typedef enum  {
  EXEC_NO = 0,
  EXEC_YES = 1,
  EXEC_BREAK = 2,
  EXEC_CONTINUE = 4,

  EXEC_INTERRUPTED = 8, // true if execution has been interrupted
  EXEC_ERROR = 16,
  EXEC_ERROR_LINE_REPORTED = 32, // if an error has been reported, set this so we don't do it too much

  EXEC_FOR_INIT = 64, // when in for initialiser parsing - hack to avoid getting confused about multiple use for IN
  EXEC_IN_LOOP = 128, // when in a loop, set this - we can then block break/continue outside it
  EXEC_IN_SWITCH = 256, // when in a switch, set this - we can then block break outside it/loops

  EXEC_RUN_MASK = EXEC_YES|EXEC_BREAK|EXEC_CONTINUE|EXEC_INTERRUPTED,
  EXEC_ERROR_MASK = EXEC_INTERRUPTED|EXEC_ERROR,
  EXEC_SAVE_RESTORE_MASK = EXEC_YES|EXEC_IN_LOOP|EXEC_IN_SWITCH, // the things JSP_SAVE/RESTORE_EXECUTE should keep track of
} JsExecFlags;

/** This structure is used when parsing the JavaScript. It contains
 * everything that should be needed. */
typedef struct {
  JsParse *parse;
  JsLex *lex;

  // TODO: could store scopes as JsVar array for speed
  JsVarRef scopes[JSPARSE_MAX_SCOPES];
  int scopeCount;
  /// Value of 'this' reserved word
  JsVar *thisVar;

  JsExecFlags execute;
} JsExecInfo;

/// flags for jspParseFunction
typedef enum {
  JSP_NOSKIP_A = 1,
  JSP_NOSKIP_B = 2,
  JSP_NOSKIP_C = 4,
  JSP_NOSKIP_D = 8,
  JSP_NOSKIP_E = 16,
  JSP_NOSKIP_F = 32,
  JSP_NOSKIP_G = 64,
  JSP_NOSKIP_H = 128,
} JspSkipFlags;

/// parse function with max 4 arguments (can set arg to 0 to avoid parse). Usually first arg will be 0, but if we DON'T want to skip names on an arg stuff, we can say
bool jspParseFunction(JspSkipFlags skipName, JsVar **a, JsVar **b, JsVar **c, JsVar **d);
/// parse function with max 8 arguments (can set arg to 0 to avoid parse). Usually first arg will be 0, but if we DON'T want to skip names on an arg stuff, we can say
bool jspParseFunction8(JspSkipFlags skipName, JsVar **a, JsVar **b, JsVar **c, JsVar **d, JsVar **e, JsVar **f, JsVar **g, JsVar **h);

bool jspParseVariableName();     ///< parse single variable name
bool jspParseEmptyFunction();    ///< parse function with no arguments
JsVar *jspParseSingleFunction(); ///< parse function with a single argument, return its value (no names!)
JsVar *jspParseFunctionAsArray(); ///< parse a function with any number of argument, and return an array of de-named aruments

/** Handle a function call (assumes we've parsed the function name and we're
 * on the start bracket). 'thisArg' is the value of the 'this' variable when the
 * function is executed (it's usually the parent object)
 *
 * If !isParsing and arg0!=0, argument 0 is set to what is supplied (same with arg1)
 *
 * functionName is used only for error reporting - and can be 0
 */
JsVar *jspeFunctionCall(JsVar *function, JsVar *functionName, JsVar *thisArg, bool isParsing, int argCount, JsVar **argPtr);

#endif /* JSPARSE_H_ */
