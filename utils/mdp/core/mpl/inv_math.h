/* math.h has many functions and defines that are not consistent across 
* platforms. This address that */

#ifdef _WINDOWS
#define _USE_MATH_DEFINES
#endif

#include <math.h>