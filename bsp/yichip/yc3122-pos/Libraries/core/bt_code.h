#ifndef _BT_CODE_H_
#define _BT_CODE_H_

#define NO_BT       (0)
#define EXIST_BT    (1)

#define VERSIONS    EXIST_BT

#include "yc3122.h"
#if (VERSIONS == EXIST_BT)
extern const unsigned char yc_btcode[];
#elif (VERSIONS == NO_BT)
#endif

#endif
