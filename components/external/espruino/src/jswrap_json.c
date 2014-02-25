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
 * JavaScript JSON-handling Functions
 * ----------------------------------------------------------------------------
 */
#include "jswrap_json.h"
#include "jsparse.h"
#include "jsinteractive.h"
#include "jswrapper.h"

/*JSON{ "type":"staticmethod",
         "class" : "JSON", "name" : "stringify",
         "description" : "Convert the given object into a JSON string which can subsequently be parsed with JSON.parse or eval",
         "generate" : "jswrap_json_stringify",
         "params" : [ [ "data", "JsVar", "The data to be converted to a JSON string"] ],
         "return" : ["JsVar", "A JSON string"]
}*/
JsVar *jswrap_json_stringify(JsVar *v) {
  JsVar *result = jsvNewFromEmptyString();
  if (result) // could be out of memory
    jsfGetJSON(v, result);
  return result;
}

/*JSON{ "type":"staticmethod",
         "class" : "JSON", "name" : "parse",
         "description" : "Parse the given JSON string into a JavaScript object",
         "generate" : "jswrap_json_parse",
         "params" : [ [ "string", "JsVar", "A JSON string"] ],
         "return" : ["JsVar", "The JavaScript object created by parsing the data string"]
}*/
JsVar *jswrap_json_parse(JsVar *v) {
  JsVar *res = 0;
  JsVar *bracketed = jsvNewFromString("(");
  if (bracketed) { // could be out of memory
    v = jsvAsString(v, true); // try and get this as a string
    jsvAppendStringVarComplete(bracketed, v);
    jsvAppendString(bracketed, ")");
    res = jspEvaluateVar(jsiGetParser(), bracketed, 0);
    jsvUnLock(bracketed);
  }
  return res;
}

/* This is like jsfGetJSONWithCallback, but handles ONLY functions (and does not print the initial 'function' text) */
void jsfGetJSONForFunctionWithCallback(JsVar *var, JsfGetJSONCallbackString callbackString, JsfGetJSONCallbackVar callbackVar, void *callbackData) {
  assert(jsvIsFunction(var));
  JsVarRef coderef = 0; // TODO: this should really be in jsvAsString
  JsVarRef childref = var->firstChild;
  bool firstParm = true;
  callbackString(callbackData, "(");
  while (childref) {
    JsVar *child = jsvLock(childref);
    childref = child->nextSibling;
    if (jsvIsFunctionParameter(child)) {
      if (firstParm)
        firstParm=false;
      else
        callbackString(callbackData, ",");
      callbackVar(callbackData, child); // FIXME: escape the string
    } else if (jsvIsString(child) && jsvIsStringEqual(child, JSPARSE_FUNCTION_CODE_NAME)) {
      coderef = child->firstChild;
    }
    jsvUnLock(child);
  }
  callbackString(callbackData, ") ");
  if (coderef) {
     JsVar *codeVar = jsvLock(coderef);
     callbackVar(callbackData, codeVar);
     jsvUnLock(codeVar);
  } else callbackString(callbackData, "{}");
}

void jsfGetJSONWithCallback(JsVar *var, JsfGetJSONCallbackString callbackString, JsfGetJSONCallbackVar callbackVar, void *callbackData) {
  if (jsvIsUndefined(var)) {
    callbackString(callbackData, "undefined");
  } else if (jsvIsArray(var)) {
    int length = (int)jsvGetArrayLength(var);
    int i;
    callbackString(callbackData, "[");
    for (i=0;i<length;i++) {
      JsVar *item = jsvGetArrayItem(var, i);
      jsfGetJSONWithCallback(item, callbackString, callbackVar, callbackData);
      jsvUnLock(item);
      if (i<length-1) callbackString(callbackData, ",");
    }
    callbackString(callbackData, "]");
  } else if (jsvIsArrayBuffer(var)) {
    callbackString(callbackData, "new ");
    callbackString(callbackData, jswGetBasicObjectName(var));
    callbackString(callbackData, "([");
    callbackVar(callbackData, jsvAsString(var, false));
    callbackString(callbackData, "])");
  } else if (jsvIsObject(var)) {
    bool first = true;
    JsVarRef childref = var->firstChild;
    callbackString(callbackData, "{");
    while (childref) {
      JsVar *child = jsvLock(childref);
      bool hidden = jsvIsInternalObjectKey(child);
      if (!hidden) {
        if (first)
          first = false;
        else
          callbackString(callbackData, ",");

        callbackString(callbackData, "\"");
        callbackVar(callbackData, child); // FIXME: escape the string
        callbackString(callbackData, "\":");
      }
      JsVar *childVar = child->firstChild ? jsvLock(child->firstChild) : 0;
      childref = child->nextSibling;
      jsvUnLock(child);

      if (!hidden) {
        jsfGetJSONWithCallback(childVar, callbackString, callbackVar, callbackData);
      }
      jsvUnLock(childVar);
    }
    callbackString(callbackData, "}");
  } else if (jsvIsFunction(var)) {
    callbackString(callbackData, "function ");
    jsfGetJSONForFunctionWithCallback(var, callbackString, callbackVar, callbackData);
  } else if (jsvIsString(var) && !jsvIsName(var)) {
    // escape the string
    callbackString(callbackData, "\"");
    JsvStringIterator it;
    jsvStringIteratorNew(&it, var, 0);
    while (jsvStringIteratorHasChar(&it)) {
      char ch = jsvStringIteratorGetChar(&it);
      callbackString(callbackData, escapeCharacter(ch));
      jsvStringIteratorNext(&it);
    }
    jsvStringIteratorFree(&it);
    callbackString(callbackData, "\"");
  } else {
    JsVar *str = jsvAsString(var, false);
    if (str) {
      callbackVar(callbackData, str);
      jsvUnLock(str);
    }
  }
}

void jsfGetJSON(JsVar *var, JsVar *result) {
  assert(jsvIsString(result));
  jsfGetJSONWithCallback(var, (JsfGetJSONCallbackString)jsvAppendString, (JsfGetJSONCallbackVar)jsvAppendStringVarComplete, result);
}

void _jsfPrintJSON_str(void *data, const char *str) { NOT_USED(data); jsiConsolePrint(str); }
void _jsfPrintJSON_var(void *data, JsVar *var) { NOT_USED(data); jsiConsolePrintStringVar(var); }
void jsfPrintJSON(JsVar *var) {
  jsfGetJSONWithCallback(var, _jsfPrintJSON_str, _jsfPrintJSON_var, 0);
}
void jsfPrintJSONForFunction(JsVar *var) {
  jsfGetJSONForFunctionWithCallback(var, _jsfPrintJSON_str, _jsfPrintJSON_var, 0);
}
