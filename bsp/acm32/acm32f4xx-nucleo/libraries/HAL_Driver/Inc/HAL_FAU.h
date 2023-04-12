
#ifndef __FAU_H_
#define __FAU_H_

#define RANGE 2147483648U  //2^31
#define CORDIC_F_31  0xD2C90A46 // CORDIC gain F

/**************************************************************************
* Function Name  : HAL_CORDIC_CosSin( precision 1 )
* Description    : calculate the sin & cos value of the input angle
* Input          : - angle_para   : input angle data in radians, divided by π[range[-1,1],Q31 format];
* Output		     : - * cos_data   : the cos value of the input angle[range[-1,1],Q31 format]
                   - * sin_data   : the sin value of the input angle[range[-1,1],Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_CosSin_1(int angle_para, int* cos_data, int* sin_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_CosSin( precision 2 )
* Description    : calculate the sin & cos value of the input angle
* Input          : - angle_para   : input angle data in radians, divided by π[range[-1,1],Q31 format];
* Output		     : - * cos_data   : the cos value of the input angle[range[-1,1],Q31 format]
                   - * sin_data   : the sin value of the input angle[range[-1,1],Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_CosSin_2(int angle_para, int* cos_data, int* sin_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_CosSin( precision 3 )
* Description    : calculate the sin & cos value of the input angle
* Input          : - angle_para   : input angle data in radians, divided by π[range[-1,1],Q31 format];
* Output		     : - * cos_data   : the cos value of the input angle[range[-1,1],Q31 format]
                   - * sin_data   : the sin value of the input angle[range[-1,1],Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_CosSin_3(int angle_para, int* cos_data, int* sin_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_CosSin( precision 4 )
* Description    : calculate the sin & cos value of the input angle
* Input          : - angle_para   : input angle data in radians, divided by π[range[-1,1],Q31 format];
* Output		     : - * cos_data   : the cos value of the input angle[range[-1,1],Q31 format]
                   - * sin_data   : the sin value of the input angle[range[-1,1],Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_CosSin_4(int angle_para, int* cos_data, int* sin_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_CosSin( precision 5 )
* Description    : calculate the sin & cos value of the input angle
* Input          : - angle_para   : input angle data in radians, divided by π[range[-1,1],Q31 format];
* Output		     : - * cos_data   : the cos value of the input angle[range[-1,1],Q31 format]
                   - * sin_data   : the sin value of the input angle[range[-1,1],Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_CosSin_5(int angle_para, int* cos_data, int* sin_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_CosSin( precision 6 )
* Description    : calculate the sin & cos value of the input angle
* Input          : - angle_para   : input angle data in radians, divided by π[range[-1,1],Q31 format];
* Output		     : - * cos_data   : the cos value of the input angle[range[-1,1],Q31 format]
                   - * sin_data   : the sin value of the input angle[range[-1,1],Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_CosSin_6(int angle_para, int* cos_data, int* sin_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_CosSin( precision 7 )
* Description    : calculate the sin & cos value of the input angle
* Input          : - angle_para   : input angle data in radians, divided by π[range[-1,1],Q31 format];
* Output		     : - * cos_data   : the cos value of the input angle[range[-1,1],Q31 format]
                   - * sin_data   : the sin value of the input angle[range[-1,1],Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_CosSin_7(int angle_para, int* cos_data, int* sin_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_CosSin( precision 8 )
* Description    : calculate the sin & cos value of the input angle
* Input          : - angle_para   : input angle data in radians, divided by π[range[-1,1],Q31 format];
* Output		     : - * cos_data   : the cos value of the input angle[range[-1,1],Q31 format]
                   - * sin_data   : the sin value of the input angle[range[-1,1],Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_CosSin_8(int angle_para, int* cos_data, int* sin_data);

/**************************************************************************
* Function Name  : HAL_CORDIC_AtanSqrt( precision 1 )
* Description    : calculate the atan & sqrt value of the input x,y
* Input          : - x             : input x data[range[-1,1],Q31 format];
*				         : - y             : input y data[range[-1,1],Q31 format];
                 : - precision     : the precison used in calculation
* Output		     : - * sqrt_data   : the sqrt value of the input x,y[Q31 format]
                   - * atan_data   : the atan value of the input x,y[Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_AtanSqrt_1(int x, int y, int*sqrt_data, int* atan_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_AtanSqrt( precision 2 )
* Description    : calculate the atan & sqrt value of the input x,y
* Input          : - x             : input x data[range[-1,1],Q31 format];
*				         : - y             : input y data[range[-1,1],Q31 format];
                 : - precision     : the precison used in calculation
* Output		     : - * sqrt_data   : the sqrt value of the input x,y[Q31 format]
                   - * atan_data   : the atan value of the input x,y[Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_AtanSqrt_2(int x, int y, int*sqrt_data, int* atan_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_AtanSqrt( precision 3 )
* Description    : calculate the atan & sqrt value of the input x,y
* Input          : - x             : input x data[range[-1,1],Q31 format];
*				         : - y             : input y data[range[-1,1],Q31 format];
                 : - precision     : the precison used in calculation
* Output		     : - * sqrt_data   : the sqrt value of the input x,y[Q31 format]
                   - * atan_data   : the atan value of the input x,y[Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_AtanSqrt_3(int x, int y, int*sqrt_data, int* atan_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_AtanSqrt( precision 4 )
* Description    : calculate the atan & sqrt value of the input x,y
* Input          : - x             : input x data[range[-1,1],Q31 format];
*				         : - y             : input y data[range[-1,1],Q31 format];
                 : - precision     : the precison used in calculation
* Output		     : - * sqrt_data   : the sqrt value of the input x,y[Q31 format]
                   - * atan_data   : the atan value of the input x,y[Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_AtanSqrt_4(int x, int y, int*sqrt_data, int* atan_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_AtanSqrt( precision 5 )
* Description    : calculate the atan & sqrt value of the input x,y
* Input          : - x             : input x data[range[-1,1],Q31 format];
*				         : - y             : input y data[range[-1,1],Q31 format];
                 : - precision     : the precison used in calculation
* Output		     : - * sqrt_data   : the sqrt value of the input x,y[Q31 format]
                   - * atan_data   : the atan value of the input x,y[Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_AtanSqrt_5(int x, int y, int*sqrt_data, int* atan_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_AtanSqrt( precision 6 )
* Description    : calculate the atan & sqrt value of the input x,y
* Input          : - x             : input x data[range[-1,1],Q31 format];
*				         : - y             : input y data[range[-1,1],Q31 format];
                 : - precision     : the precison used in calculation
* Output		     : - * sqrt_data   : the sqrt value of the input x,y[Q31 format]
                   - * atan_data   : the atan value of the input x,y[Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_AtanSqrt_6(int x, int y, int*sqrt_data, int* atan_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_AtanSqrt( precision 7 )
* Description    : calculate the atan & sqrt value of the input x,y
* Input          : - x             : input x data[range[-1,1],Q31 format];
*				         : - y             : input y data[range[-1,1],Q31 format];
                 : - precision     : the precison used in calculation
* Output		     : - * sqrt_data   : the sqrt value of the input x,y[Q31 format]
                   - * atan_data   : the atan value of the input x,y[Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_AtanSqrt_7(int x, int y, int*sqrt_data, int* atan_data);
/**************************************************************************
* Function Name  : HAL_CORDIC_AtanSqrt( precision 8 )
* Description    : calculate the atan & sqrt value of the input x,y
* Input          : - x             : input x data[range[-1,1],Q31 format];
*				         : - y             : input y data[range[-1,1],Q31 format];
                 : - precision     : the precison used in calculation
* Output		     : - * sqrt_data   : the sqrt value of the input x,y[Q31 format]
                   - * atan_data   : the atan value of the input x,y[Q31 format]
* Return         : None
**************************************************************************/
void HAL_CORDIC_AtanSqrt_8(int x, int y, int*sqrt_data, int* atan_data);

#endif