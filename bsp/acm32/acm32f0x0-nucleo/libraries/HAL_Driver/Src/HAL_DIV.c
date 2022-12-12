#include "HAL_DIV.h"

//Computes q = b div c and a = b mod c
//cDigits must be 1, and *c < 0xffffffff
void hardwareNN_Div_q32(UINT32 *q,UINT32 *a,UINT32 *b,UINT32 bDigits,UINT32 *c,UINT32 cDigits)
{
    UINT32 * p;
    int i;

    DIV->REMAIN = 0;
    DIV->DIVISOR = *c;
    for(i = (bDigits-1); i >= 0 ; i -- )
    {
        p = (UINT32*) (b + i);
        DIV->DIVIDENED = *p;

        while((DIV->STATUS&0x01)!=0x01);
        DIV->STATUS = 0x01;
        (*(q+i)) = (UINT32)DIV->QUOTIENT;
    }
    (*a) = DIV->REMAIN;
}
