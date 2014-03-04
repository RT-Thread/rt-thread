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
 * JavaScript Serial Port Functions
 * ----------------------------------------------------------------------------
 */
#include "jswrap_serial.h"
#include "jsdevices.h"
#include "jsinteractive.h"

/*JSON{ "type":"class",
        "class" : "Serial",
        "description" : ["This class allows use of the built-in USARTs",
                         "Methods may be called on the USB, Serial1, Serial2, Serial3, Serial4, Serial5 and Serial6 objects. While different processors provide different numbers of USARTs, you can always rely on at least Serial1 and Serial2" ]
}*/

/*JSON{ "type":"object", "name":"USB", "instanceof" : "Serial",
        "description" : ["The USB Serial port" ],
        "#if" : "defined(USB)"
}*/
/*JSON{ "type":"object", "name":"Serial1", "instanceof" : "Serial",
        "description" : ["The first Serial (USART) port" ],
        "#if" : "USARTS>=1"
}*/
/*JSON{ "type":"object", "name":"Serial2", "instanceof" : "Serial",
        "description" : ["The second Serial (USART) port" ],
        "#if" : "USARTS>=2"
}*/
/*JSON{ "type":"object", "name":"Serial3", "instanceof" : "Serial",
        "description" : ["The third Serial (USART) port" ],
        "#if" : "USARTS>=3"
}*/
/*JSON{ "type":"object", "name":"Serial4", "instanceof" : "Serial",
        "description" : ["The fourth Serial (USART) port" ],
        "#if" : "USARTS>=4"
}*/
/*JSON{ "type":"object", "name":"Serial5", "instanceof" : "Serial",
        "description" : ["The fifth Serial (USART) port" ],
        "#if" : "USARTS>=5"
}*/
/*JSON{ "type":"object", "name":"Serial6", "instanceof" : "Serial",
        "description" : ["The sixth Serial (USART) port" ],
        "#if" : "USARTS>=6"
}*/



/*JSON{ "type":"method", "class": "Serial", "name" : "setConsole",
         "description" : "Set this Serial port as the port for the console",
         "generate_full" : "jsiSetConsoleDevice(jsiGetDeviceFromClass(parent))"
}*/

/*JSON{ "type":"method", "class": "Serial", "name" : "setup",
         "description" : "Setup this Serial port with the given baud rate and options",
         "generate" : "jswrap_serial_setup",
         "params" : [ [ "baudrate", "int", "The baud rate - the default is 9600"],
                      [ "options", "JsVar", ["An optional structure containing extra information on initialising the serial port.",
                                             "```{rx:pin,tx:pin}```",
                                             "Note that even after changing the RX and TX pins, if you have called setup before then the previous RX and TX pins will still be connected to the Serial port as well - until you set them to something else using digitalWrite" ] ] ]
}*/
void jswrap_serial_setup(JsVar *parent, JsVarInt baud, JsVar *options) {
  IOEventFlags device = jsiGetDeviceFromClass(parent);
  JshUSARTInfo inf;
  jshUSARTInitInfo(&inf);

  if (baud>0) inf.baudRate = (int)baud;

  if (jsvIsObject(options)) {

    inf.pinRX = jshGetPinFromVarAndUnLock(jsvObjectGetChild(options, "rx", 0));
    inf.pinTX = jshGetPinFromVarAndUnLock(jsvObjectGetChild(options, "tx", 0));
    inf.bytesize = (unsigned char)jsvGetIntegerAndUnLock(jsvObjectGetChild(options, "bytesize", 0));

    JsVar *v;
    v = jsvObjectGetChild(options, "parity", 0);
    
    if(jsvIsNull(v)) {
      inf.parity = 0;
    }
    else if(jsvIsString(v)) {
      inf.parity = 0xFF;
      char s[8] = "";

      jsvGetString(v, s, sizeof(s) - 1);

      if(!strcmp(s, "o") || !strcmp(s, "odd")) {
        inf.parity = 1;
      }
      else if(!strcmp(s, "e") || !strcmp(s, "even")) {
        inf.parity = 2;
      }
    }
    else if(jsvIsInt(v)) {
      inf.parity = (unsigned char)jsvGetInteger(v);
    }

    jsvUnLock(v);

    v = jsvObjectGetChild(options, "stopbits", 0);
    inf.stopbits = (unsigned char)jsvGetInteger(v);
    jsvUnLock(v);
  }

  jshUSARTSetup(device, &inf);
  // Set baud rate in object, so we can initialise it on startup
  if (baud != DEFAULT_BAUD_RATE) {
    JsVar *baudVar = jsvNewFromInteger(baud);
    jsvUnLock(jsvSetNamedChild(parent, baudVar, USART_BAUDRATE_NAME));
    jsvUnLock(baudVar);
  } else
    jsvRemoveNamedChild(parent, USART_BAUDRATE_NAME);
  // Do the same for options
  if (options)
    jsvUnLock(jsvSetNamedChild(parent, options, DEVICE_OPTIONS_NAME));
  else
    jsvRemoveNamedChild(parent, DEVICE_OPTIONS_NAME);
}

/*JSON{ "type":"method", "class": "Serial", "name" : "print",
         "description" : "Print a string to the serial port - without a line feed",
         "generate" : "jswrap_serial_print",
         "params" : [ [ "string", "JsVar", "A String to print"] ]
}*/
/*JSON{  "type":"method", "class": "Serial", "name" : "println",
         "description" : "Print a line to the serial port (newline character sent are '\r\n')",
         "generate" : "jswrap_serial_println",
         "params" : [ [ "string", "JsVar", "A String to print"] ]
}*/
void _jswrap_serial_print(JsVar *parent, JsVar *str, bool newLine) {
  NOT_USED(parent);
  IOEventFlags device = jsiGetDeviceFromClass(parent);
  str = jsvAsString(str, false);
  jsiTransmitStringVar(device,str);
  jsvUnLock(str);
  if (newLine) {
    jshTransmit(device, (unsigned char)'\r');
    jshTransmit(device, (unsigned char)'\n');
  }
}
void jswrap_serial_print(JsVar *parent, JsVar *str) {
  _jswrap_serial_print(parent, str, false);
}
void jswrap_serial_println(JsVar *parent,  JsVar *str) {
  _jswrap_serial_print(parent, str, true);
}
/*JSON{ "type":"method", "class": "Serial", "name" : "write",
         "description" : "Write a character or array of characters to the serial port - without a line feed",
         "generate" : "jswrap_serial_write",
         "params" : [ [ "data", "JsVar", "A byte, a string, or an array of bytes to write"] ]
}*/
void jswrap_serial_write(JsVar *parent, JsVar *data) {
  NOT_USED(parent);
  IOEventFlags device = jsiGetDeviceFromClass(parent);
  if (jsvIsNumeric(data)) {
    jshTransmit(device, (unsigned char)jsvGetInteger(data));
  } else if (jsvIsIterable(data)) {
    JsvIterator it;
    jsvIteratorNew(&it, data);
    while (jsvIteratorHasElement(&it)) {
      jshTransmit(device, (unsigned char)jsvIteratorGetIntegerValue(&it));
      jsvIteratorNext(&it);
    }
    jsvIteratorFree(&it);
  } else {
    jsWarn("Data supplied was not an integer - or iterable");
  }
}

/*JSON{ "type":"method", "class": "Serial", "name" : "onData",
         "description" : ["When a character is received on this serial port, the function supplied to onData gets called.",
                          "Only one function can ever be supplied, so calling onData(undefined) will stop any function being called"],
         "generate" : "jswrap_serial_onData",
         "params" : [ [ "function", "JsVarName", "A function to call when data arrives. It takes one argument, which is an object with a 'data' field"] ]
}*/
void jswrap_serial_onData(JsVar *parent, JsVar *funcVar) {
  JsVar *skippedFunc = jsvSkipName(funcVar);
  if (!jsvIsFunction(skippedFunc) && !jsvIsString(skippedFunc)) {
    jsiConsolePrint("Function or String not supplied - removing onData handler.\n");
    JsVar *handler = jsvFindChildFromString(parent, USART_CALLBACK_NAME, false);
    if (handler) {
      jsvRemoveChild(parent, handler);
      jsvUnLock(handler);
    }
  } else {
    jsvUnLock(jsvSetNamedChild(parent, funcVar, USART_CALLBACK_NAME));
  }
  jsvUnLock(skippedFunc);
}
