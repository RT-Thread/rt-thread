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
 * JavaScript Functions for handling Modules
 * ----------------------------------------------------------------------------
 */
#include "jswrap_functions.h"
#include "jslex.h"
#include "jsvar.h"
#include "jsparse.h"
#include "jsinteractive.h"
#include "jswrapper.h"
#ifdef USE_FILESYSTEM
#include "../libs/jswrap_fat.h"
#endif

static JsVar *jswrap_modules_getModuleList() {
  JsVar *moduleListName = jsvFindChildFromString(jsiGetParser()->root, JSPARSE_MODULE_CACHE_NAME, true);
  if (!moduleListName) return 0; // out of memory
  JsVar *moduleList = jsvSkipName(moduleListName);
  if (!moduleList) {
    moduleList = jsvNewWithFlags(JSV_OBJECT);
    if (!moduleList) { jsvUnLock(moduleListName); return 0; } // out of memory
    jsvSetValueOfName(moduleListName, moduleList); // no need to unlock
  }
  jsvUnLock(moduleListName);
  return moduleList;
}

/*JSON{ "type":"function", "name" : "require",
         "description" : "Load the given module, and return the exported functions",
         "generate" : "jswrap_require",
         "params" : [ [ "moduleName", "JsVar", "A String containing the name of the given module"] ],
         "return" : ["JsVar", "The result of evaluating the string"]
}*/
JsVar *jswrap_require(JsVar *moduleName) {
  if (!jsvIsString(moduleName)) {
    jsWarn("Expecting a module name as a string, but got %t", moduleName);
    return 0;
  }
  // Search to see if we have already loaded this module

  JsVar *moduleList = jswrap_modules_getModuleList();
  if (!moduleList) return 0; // out of memory
  JsVar *moduleExportName = jsvFindChildFromVar(moduleList, moduleName, true);
  jsvUnLock(moduleList);
  if (!moduleExportName) return 0; // out of memory
  JsVar *moduleExport = jsvSkipName(moduleExportName);
  if (moduleExport) {
    // Found the module!
    jsvUnLock(moduleExportName);
    return moduleExport;
  }

  // Now check if it is built-in
  char moduleNameBuf[32];
  jsvGetString(moduleName, moduleNameBuf, sizeof(moduleNameBuf));
  if (jswIsBuiltInLibrary(moduleNameBuf)) {
    // create a 'fake' module that Espruino can use to map its built-in functions against
    moduleExport = jspNewBuiltin(moduleNameBuf);
  } else {
    // Now try and load it
    JsVar *fileContents = 0;
    //if (jsvIsStringEqual(moduleName,"http")) {}
    //if (jsvIsStringEqual(moduleName,"fs")) {}
  #ifdef USE_FILESYSTEM
    JsVar *modulePath = jsvNewFromString(
  #ifdef LINUX
        "node_modules/"
  #else
        "NODE_M~1/"
  #endif
        );
    if (!modulePath) { jsvUnLock(moduleExportName); return 0; } // out of memory
    jsvAppendStringVarComplete(modulePath, moduleName);
    jsvAppendString(modulePath,".js");
    fileContents = wrap_fat_readFile(modulePath);
    jsvUnLock(modulePath);
  #endif
    if (!fileContents || jsvIsStringEqual(fileContents,"")) {
      jsvUnLock(moduleExportName);
      jsvUnLock(fileContents);
      jsWarn("Module not found");
      return 0;
    }
    moduleExport = jspEvaluateModule(jsiGetParser(), fileContents);
    jsvUnLock(fileContents);
  }

  assert(moduleExport);
  jsvSetValueOfName(moduleExportName, moduleExport); // save in cache
  jsvUnLock(moduleExportName);
  return moduleExport;
}

/*JSON{ "type":"staticmethod",
         "class" : "Modules", "name" : "getCached",
         "description" : "Return an array of module names that have been cached",
         "generate" : "jswrap_modules_getCached",
         "return" : ["JsVar", "An array of module names"]
}*/
JsVar *jswrap_modules_getCached() {
  JsVar *arr = jsvNewWithFlags(JSV_ARRAY);
  if (!arr) return 0; // out of memory

  JsVar *moduleList = jswrap_modules_getModuleList();
  if (!moduleList) return arr; // out of memory

  JsObjectIterator it;
  jsvObjectIteratorNew(&it, moduleList);
  while (jsvObjectIteratorHasElement(&it)) {
    JsVar *idx = jsvObjectIteratorGetKey(&it);
    JsVar *idxCopy  = jsvCopyNameOnly(idx, false, false);
    jsvArrayPushAndUnLock(arr, idxCopy);
    jsvUnLock(idx);
    jsvObjectIteratorNext(&it);
  }
  jsvObjectIteratorFree(&it);
  jsvUnLock(moduleList);
  return arr;
}

/*JSON{ "type":"staticmethod",
         "class" : "Modules", "name" : "removeCached",
         "description" : "Remove the given module from the list of cached modules",
         "generate" : "jswrap_modules_removeCached",
         "params" : [ [ "id", "JsVar", "The module name to remove"] ]
}*/
void jswrap_modules_removeCached(JsVar *id) {
  if (!jsvIsString(id)) {
    jsError("The argument to removeCached must be a string");
    return;
  }
  JsVar *moduleList = jswrap_modules_getModuleList();
  if (!moduleList) return; // out of memory

  JsVar *moduleExportName = jsvFindChildFromVar(moduleList, id, false);
  if (!moduleExportName) {
    jsWarn("Module not found");
  } else {
    jsvRemoveChild(moduleList, moduleExportName);
    jsvUnLock(moduleExportName);
  }

  jsvUnLock(moduleList);
}

/*JSON{ "type":"staticmethod",
         "class" : "Modules", "name" : "removeAllCached",
         "description" : "Remove all cached modules",
         "generate" : "jswrap_modules_removeAllCached"
}*/
void jswrap_modules_removeAllCached() {
  JsVar *moduleList = jswrap_modules_getModuleList();
  if (!moduleList) return; // out of memory
  jsvRemoveAllChildren(moduleList);
  jsvUnLock(moduleList);
}

/*JSON{ "type":"staticmethod",
         "class" : "Modules", "name" : "addCached",
         "description" : "Add the given module to the cache",
         "generate" : "jswrap_modules_addCached",
         "params" : [ [ "id", "JsVar", "The module name to add" ],
                      [  "sourcecode", "JsVar", "The module's sourcecode" ] ]
}*/
void jswrap_modules_addCached(JsVar *id, JsVar *sourceCode) {
  if (!jsvIsString(id) || !jsvIsString(sourceCode)) {
    jsError("Both arguments to addCached must be strings");
    return;
  }

  JsVar *moduleList = jswrap_modules_getModuleList();
  if (!moduleList) return; // out of memory

  JsVar *moduleExport = jspEvaluateModule(jsiGetParser(), sourceCode);
  if (!moduleExport) {
    jsWarn("Unable to load module");
  } else {
    JsVar *moduleName = jsvFindChildFromVar(moduleList, id, true);
    if (moduleName) jsvSetValueOfName(moduleName, moduleExport);
    jsvUnLock(moduleExport);
  }
  jsvUnLock(moduleList);

}
