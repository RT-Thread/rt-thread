#ifndef _HAL_DIV_H_
#define _HAL_DIV_H_

#include "ACM32Fxx_HAL.h"

/************************************************************************
* function   : hardwareNN_Div_q32
* Description: Computes q = b div c and a = b mod c.
               cDigits must be 1, and *c < 0xffffffff
* input :      UINT32 *b -- input b databuffer
               UINT32 *c -- input c databuffer
* output:      UINT32 *q -- quotient of result
               UINT32 *a -- remainder of result

* return:      none
************************************************************************/
void HAL_DIV_Q32(UINT32 *q,UINT32 *a,UINT32 *b,UINT32 bDigits,UINT32 *c,UINT32 cDigits);



#endif



