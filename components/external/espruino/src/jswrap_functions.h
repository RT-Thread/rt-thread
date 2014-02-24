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
 * JavaScript methods and functions in the global namespace
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"

JsVar *jswrap_arguments();
JsVar *jswrap_eval(JsVar *v);
JsVar *jswrap_parseInt(JsVar *v, JsVar *radixVar);
JsVarFloat jswrap_parseFloat(JsVar *v);
