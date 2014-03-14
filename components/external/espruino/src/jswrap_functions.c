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
 * This file is designed to be parsed during the build process
 *
 * JavaScript methods and functions in the global namespace
 * ----------------------------------------------------------------------------
 */
#include "jswrap_functions.h"
#include "jslex.h"
#include "jsparse.h"
#include "jsinteractive.h"

/*JSON{ "type":"variable", "name" : "arguments",
         "description" : "A variable containing the arguments given to the function",
         "generate" : "jswrap_arguments",
         "return" : ["JsVar", "An array containing all the arguments given to the function"]
}*/
extern JsExecInfo execInfo;
JsVar *jswrap_arguments() {
  JsVar *scope = 0;
  if (execInfo.scopeCount>0)
    scope = jsvLock(execInfo.scopes[execInfo.scopeCount-1]);
  if (!jsvIsFunction(scope)) {
    jsvUnLock(scope);
    jsError("Can only use 'arguments' variable inside a function");
    return 0;
  }

  JsVar *args = jsvNewWithFlags(JSV_ARRAY);
  if (!args) return 0; // out of memory

  JsObjectIterator it;
  jsvObjectIteratorNew(&it, scope);
  while (jsvObjectIteratorHasElement(&it)) {
    JsVar *idx = jsvObjectIteratorGetKey(&it);
    if (jsvIsFunctionParameter(idx)) {
      JsVar *val = jsvSkipOneName(idx);
      jsvArrayPushAndUnLock(args, val);
    }
    jsvUnLock(idx);
    jsvObjectIteratorNext(&it);
  }
  jsvObjectIteratorFree(&it);
  jsvUnLock(scope);

  return args;
}


/*JSON{ "type":"function", "name" : "eval",
         "description" : "Evaluate a string containing JavaScript code",
         "generate" : "jswrap_eval",
         "params" : [ [ "code", "JsVar", ""] ],
         "return" : ["JsVar", "The result of evaluating the string"]
}*/
JsVar *jswrap_eval(JsVar *v) {
  if (!v) return 0;
  JsVar *s = jsvAsString(v, false); // get as a string
  JsVar *result = jspEvaluateVar(jsiGetParser(), s, 0);
  jsvUnLock(s);
  return result;
}

/*JSON{ "type":"function", "name" : "parseInt",
         "description" : "Convert a string representing a number into an integer",
         "generate" : "jswrap_parseInt",
         "params" :  [ [ "string", "JsVar", ""],
                       [ "radix", "JsVar", "The Radix of the string (optional)"] ],
         "return" : ["JsVar", "The integer value of the string (or NaN)"]
}*/
JsVar *jswrap_parseInt(JsVar *v, JsVar *radixVar) {
  int radix = 0/*don't force radix*/;
  if (jsvIsNumeric(radixVar))
    radix = (int)jsvGetInteger(radixVar);

  char buffer[JS_NUMBER_BUFFER_SIZE];
  jsvGetString(v, buffer, JS_NUMBER_BUFFER_SIZE);
  bool hasError;
  JsVarInt i = stringToIntWithRadix(buffer, radix, &hasError);
  if (hasError) return jsvNewFromFloat(NAN);
  return jsvNewFromInteger(i);
}

/*JSON{ "type":"function", "name" : "parseFloat",
         "description" : "Convert a string representing a number into an float",
         "generate" : "jswrap_parseFloat",
         "params" :  [ [ "string", "JsVar", ""] ],
         "return" : ["float", "The value of the string"]
}*/
JsVarFloat jswrap_parseFloat(JsVar *v) {
  char buffer[JS_NUMBER_BUFFER_SIZE];
  jsvGetString(v, buffer, JS_NUMBER_BUFFER_SIZE);
  return stringToFloat(buffer);
}
