#ifndef FTK_APP_DEMO_H
#define FTK_APP_DEMO_H

#include "ftk_app.h"

#define FTK_HIDE static

typedef int (*FtkMain)(int argc, char* argv[]);
FtkApp* ftk_app_demo_create(const char* name, FtkMain main);

#endif/*FTK_APP_DEMO_H*/

