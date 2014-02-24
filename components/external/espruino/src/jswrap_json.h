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
 * JavaScript JSON-handling Functions
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"

JsVar *jswrap_json_stringify(JsVar *v);
JsVar *jswrap_json_parse(JsVar *v);

typedef void (*JsfGetJSONCallbackString)(void *data, const char *string);
typedef void (*JsfGetJSONCallbackVar)(void *data, JsVar *var);

/* This is like jsfGetJSONWithCallback, but handles ONLY functions (and does not print the initial 'function' text) */
void jsfGetJSONForFunctionWithCallback(JsVar *var, JsfGetJSONCallbackString callbackString, JsfGetJSONCallbackVar callbackVar, void *callbackData);
/* Dump to JSON, using the given callbacks for printing data */
void jsfGetJSONWithCallback(JsVar *var, JsfGetJSONCallbackString callbackString, JsfGetJSONCallbackVar callbackVar, void *callbackData);

/* Convenience function for using jsfGetJSONWithCallback - print to var */
void jsfGetJSON(JsVar *var, JsVar *result);

/* Convenience function for using jsfGetJSONWithCallback - print to console */
void jsfPrintJSON(JsVar *var);
/* Convenience function for using jsfGetJSONForFunctionWithCallback - print to console */
void jsfPrintJSONForFunction(JsVar *var);
