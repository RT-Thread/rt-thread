// 软件延时头文件



#ifndef __OPENLOONGSON_DELAY_H
#define __OPENLOONGSON_DELAY_H



/*
 * 延时指定时间，单位ms
 * @j 延时时间，单位ms
 */
void delay_ms(int j);


/*
 * 延时指定时间，单位us
 * @n 延时时间，单位us
 */
void delay_us(int n);


/*
 * 延时指定时间，单位s
 * @i 延时时间，单位s
 */
void delay_s(int i);




#endif

