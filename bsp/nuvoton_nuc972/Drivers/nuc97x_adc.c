/*
 * File      : nuc97x_adc.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2017/11/13     EvalZero  first version
 */
 
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "nuc97x_conf.h"

#include "nuc97x.h"
#include "nuc97x_sys.h"
#include "nuc97x_adc.h"

#define ADC_FIFO_LENGTH 128
volatile int mst_complete;
typedef struct 
{
    ADC_CALLBACK touch_callback;
    UINT32 touch_userData;

    ADC_CALLBACK touchz_callback;
    UINT32 touchz_userData;

    ADC_CALLBACK touch_wakeup_callback;
    UINT32 touch_wakeup_userData;

    ADC_CALLBACK pendown_callback;
    UINT32 pendown_userData;

    ADC_CALLBACK penup_callback;
    UINT32 penup_userData;

    ADC_CALLBACK keypad_conv_callback;
    UINT32 keypad_conv_userData;

    ADC_CALLBACK keypad_press_callback;
    UINT32 keypad_press_userData;

    ADC_CALLBACK keypad_up_callback;
    UINT32 keypad_up_userData;

    ADC_CALLBACK keypad_wakeup_callback;
    UINT32 keypad_wakeup_userData;

    ADC_CALLBACK voltage_battery_callback;
    UINT32 voltage_battery_userData;

    ADC_CALLBACK normal_callback;
    UINT32 normal_userData;
    
    INT16 fifoX[ADC_FIFO_LENGTH];
    INT32 fifoHeadX;
    INT32 fifoTailX;
    INT32 fifoLengthX;

    INT16 fifoY[ADC_FIFO_LENGTH];
    INT32 fifoHeadY;
    INT32 fifoTailY;
    INT32 fifoLengthY;

    INT16 fifoZ1[ADC_FIFO_LENGTH];
    INT32 fifoHeadZ1;
    INT32 fifoTailZ1;
    INT32 fifoLengthZ1;

    INT16 fifoZ2[ADC_FIFO_LENGTH];
    INT32 fifoHeadZ2;
    INT32 fifoTailZ2;
    INT32 fifoLengthZ2;
} ADC_HANDLE;
/// @endcond HIDDEN_SYMBOLS 

static ADC_HANDLE adcHandler;

void adcISR(void);


/**
 * @brief       Open ADC Function.
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to open adc function.
 */
INT adcOpen(void)
{
  return adcOpen2(1000);
}

/**
 * @brief       Open ADC2 Function.
 *
 * @param[in]   freqKhz  The ADC engine clock. It should be 1000Khz~3000Khz
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to open adc function.
 */
INT adcOpen2(uint32_t freqKhz)
{
     uint32_t div;
    /* Enable ADC engine clock */
    outpw(REG_CLK_PCLKEN1, 1<<24);

    /* Reset the ADC IP */
    outpw(REG_SYS_APBIPRST1, (1<<24));
    outpw(REG_SYS_APBIPRST1, 0);

    /* ADC Engine Clock is set to freq Khz */
    if(freqKhz>3000) freqKhz=3000;
    if(freqKhz<1000) freqKhz=1000;
    div=12000/freqKhz;
    outpw(REG_CLK_DIVCTL7, inpw(REG_CLK_DIVCTL7) & ~((0x3<<19)|(0x7<<16)|(0xFFul<<24)));
    outpw(REG_CLK_DIVCTL7, (0<<19)|(0<<16)|((div-1)<<24));

    /* Enable ADC Power */
    outpw(REG_ADC_CTL, ADC_CTL_ADEN);

    /* Enable ADC to high speed mode */
    outpw(REG_ADC_CONF, inpw(REG_ADC_CONF)|ADC_CONF_HSPEED);

    /* Set interrupt */   
    rt_hw_interrupt_set_type(ADC_IRQn, HIGH_LEVEL_SENSITIVE);
    rt_hw_interrupt_install(ADC_IRQn, (rt_isr_handler_t)adcISR, NULL, "ADC_IRQ");
    rt_hw_local_interrupt_set(ENABLE_IRQ);                            /* enable CPSR I bit */
    rt_hw_interrupt_umask(ADC_IRQn);

    /* Init the FIFO buffer */
    adcHandler.fifoHeadX = 0;
    adcHandler.fifoTailX = 0;
    adcHandler.fifoLengthX = 0;
    adcHandler.fifoHeadY = 0;
    adcHandler.fifoTailY = 0;
    adcHandler.fifoLengthY = 0;
    adcHandler.fifoHeadZ1 = 0;
    adcHandler.fifoTailZ1 = 0;
    adcHandler.fifoLengthZ1 = 0;
    adcHandler.fifoHeadZ2 = 0;
    adcHandler.fifoTailZ2 = 0;
    adcHandler.fifoLengthZ2 = 0;

    adcHandler.touch_callback=NULL;
    adcHandler.touch_userData=NULL;

    adcHandler.touchz_callback=NULL;
    adcHandler.touchz_userData=NULL;

    adcHandler.pendown_callback=NULL;
    adcHandler.pendown_userData=NULL;

    adcHandler.penup_callback=NULL;
    adcHandler.penup_userData=NULL;

    adcHandler.keypad_conv_callback=NULL;
    adcHandler.keypad_conv_userData=NULL;

    adcHandler.keypad_press_callback=NULL;
    adcHandler.keypad_press_userData=NULL;

    adcHandler.keypad_up_callback=NULL;
    adcHandler.keypad_up_userData=NULL;

    adcHandler.voltage_battery_callback=NULL;
    adcHandler.voltage_battery_userData=NULL;

    adcHandler.normal_callback=NULL;
    adcHandler.normal_userData=NULL;

    return Successful;
}

/**
 * @brief       Close ADC Function.
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to close adc function.
 */
int adcClose(void)
{
    /* Disable interrupt */   
    rt_hw_interrupt_mask(ADC_IRQn);
    rt_hw_local_interrupt_set(DISABLE_IRQ);   /* Disable CPSR I bit */

    /* Disable ADC Power */
    outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) & ~ADC_CTL_ADEN);

    /* Disable ADC engine clock */
    outpw(REG_CLK_PCLKEN1, inpw(REG_CLK_PCLKEN1) & ~(1<<24));

    return Successful;
}

/**
 * @brief       The read touch xy data of ADC.
 *
 * @param[out]  bufX     Data buffer for x-position data
 * @param[out]  bufY     Data buffer for y-position data
 * @param[in]   dataCnt  The length of ADC x- and y-position data from FIFO
 *
 * @return      Data count actually
 *
 * @details     This function is used to read touch x-position data and touch y-position data .
 */
INT adcReadXY(INT16 *bufX, INT16 *bufY,int dataCnt)
{
    INT32 i;
    volatile INT16 *fifoX, *fifoY;
    volatile INT32 headX, headY;
    volatile INT32 fifoLengthX, readLengthX;
    volatile INT32 fifoLengthY, readLengthY;

    fifoX = adcHandler.fifoX;
    fifoY = adcHandler.fifoY;
    headX = adcHandler.fifoHeadX;
    headY = adcHandler.fifoHeadY;
    fifoLengthX = adcHandler.fifoLengthX;
    fifoLengthY = adcHandler.fifoLengthY;    
   
    readLengthX = 0;
    readLengthY = 0;
    
    for (i = 0; i < dataCnt; i++)
    {
        if (fifoLengthX > readLengthX)
        {
           bufX[i] = fifoX[headX];
           readLengthX++;
           headX++;
           if (headX >= ADC_FIFO_LENGTH)
           {
              headX = 0;
           }
        }
        else
        {
           /* FIFO is empty, just return */
           break;
        }
    }
    
    for (i = 0; i < dataCnt; i++)
    {
        if (fifoLengthY > readLengthY)
        {
           bufY[i] = fifoY[headY];
           readLengthY++;
           headY++;
           if (headY >= ADC_FIFO_LENGTH)
           {
              headY = 0;
           }
        }
        else
        {
           /* FIFO is empty, just return */
           break;
        }     
    }
        
    /* Update FIFO information */
    adcHandler.fifoHeadX = headX;
    adcHandler.fifoLengthX -= readLengthX;
    adcHandler.fifoHeadY = headY;
    adcHandler.fifoLengthY -= readLengthY;    
    return i;
}

/**
 * @brief       The read touch z data of ADC.
 *
 * @param[out]  bufZ1    Data buffer for pressure measure Z1 data
 * @param[out]  bufZ2    Data buffer for pressure measure Z2 data
 * @param[in]   dataCnt  The length of ADC x- and y-position data from FIFO
 *
 * @return      Data count actually
 *
 * @details     This function is used to read touch pressure measure Z1 data and touch pressure measure Z2 data .
 */
int adcReadZ(short *bufZ1, short *bufZ2, int dataCnt)
{
    INT32 i;
    volatile INT16 *fifoZ1, *fifoZ2;
    volatile INT32 headZ1, headZ2;
    volatile INT32 fifoLengthZ1, readLengthZ1;
    volatile INT32 fifoLengthZ2, readLengthZ2;

    fifoZ1 = adcHandler.fifoZ1;
    fifoZ2 = adcHandler.fifoZ2;
    headZ1 = adcHandler.fifoHeadZ1;
    headZ2 = adcHandler.fifoHeadZ2;
    fifoLengthZ1 = adcHandler.fifoLengthZ1;
    fifoLengthZ2 = adcHandler.fifoLengthZ2;    
   
    readLengthZ1 = 0;
    readLengthZ2 = 0;
    
    for (i = 0; i < dataCnt; i++)
    {
        if (fifoLengthZ1 > readLengthZ1)
        {
           bufZ1[i] = fifoZ1[headZ1];
           readLengthZ1++;
           headZ1++;
           if (headZ1 >= ADC_FIFO_LENGTH)
           {
              headZ1 = 0;
           }
        }
        else
        {
           /* FIFO is empty, just return */
           break;
        }
    }
    
    for (i = 0; i < dataCnt; i++)
    {
        if (fifoLengthZ2 > readLengthZ2)
        {
           bufZ2[i] = fifoZ2[headZ2];
           readLengthZ2++;
           headZ2++;
           if (headZ2 >= ADC_FIFO_LENGTH)
           {
              headZ2 = 0;
           }
        }
        else
        {
           /* FIFO is empty, just return */
           break;
        }     
    }
        
    /* Update FIFO information */
    adcHandler.fifoHeadZ1 = headZ1;
    adcHandler.fifoLengthZ1 -= readLengthZ1;
    adcHandler.fifoHeadZ2 = headZ2;
    adcHandler.fifoLengthZ2 -= readLengthZ2;    
    return i;
}

/**
 * @brief       The ioctl function of ADC device library.
 *
 * @param[in]   cmd   The command of adcIoctl function
 * @param[in]   arg1  The first argument of adcIoctl function
 * @param[in]   arg2  The second argument of adcIoctl function
 *
 * @retval      <0              Wrong command of adcIoctl
 * @retval      0               Success
 *
 * @details     This function is used to ioctl of ADC device library.
 *              Valid parameter combinations listed in following table:
 * |cmd                   |arg1                               |arg2                         |
 * | :------------------- | :-------------------------------  | :-------------------------  |
 * |\ref START_MST        | NULL                              | NULL                        |
 * |\ref VBPOWER_ON       | NULL                              | NULL                        |
 * |\ref VBPOWER_OFF      | NULL                              | NULL                        |
 * |\ref VBAT_ON          | Callback function                 | UserData                    |
 * |\ref VBAT_OFF         | NULL                              | NULL                        |
 * |\ref KPPOWER_ON       | NULL                              | NULL                        |
 * |\ref KPPOWER_OFF      | NULL                              | NULL                        |
 * |\ref KPCONV_ON        | Callback function                 | UserData                    |
 * |\ref KPCONV_OFF       | NULL                              | NULL                        |
 * |\ref KPPRESS_ON       | Callback function                 | UserData                    |
 * |\ref KPPRESS_OFF      | NULL                              | NULL                        |
 * |\ref KPUP_ON          | Callback function                 | UserData                    |
 * |\ref KPUP_OFF         | NULL                              | NULL                        |
 * |\ref PEPOWER_ON       | NULL                              | NULL                        |
 * |\ref PEPOWER_OFF      | NULL                              | NULL                        |
 * |\ref PEDEF_ON         | Callback function                 | UserData                    |
 * |\ref PEDEF_OFF        | NULL                              | NULL                        |
 * |\ref WKP_ON           | NULL                              | NULL                        |
 * |\ref WKP_OFF          | NULL                              | NULL                        |
 * |\ref WKT_ON           | NULL                              | NULL                        |
 * |\ref WKT_OFF          | NULL                              | NULL                        |
 * |\ref SWITCH_5WIRE_ON  | NULL                              | NULL                        |
 * |\ref SWITCH_5WIRE_OFF | NULL                              | NULL                        |
 * |\ref T_ON             | Callback function                 | UserData                    |
 * |\ref T_OFF            | NULL                              | NULL                        |
 * |\ref TAVG_ON          | NULL                              | NULL                        |
 * |\ref TAVG_OFF         | NULL                              | NULL                        |
 * |\ref Z_ON             | Callback function                 | UserData                    |
 * |\ref Z_OFF            | NULL                              | NULL                        |
 * |\ref TZAVG_ON         | NULL                              | NULL                        |
 * |\ref TZAVG_OFF        | NULL                              | NULL                        |
 * |\ref NAC_ON           | Callback function                 | UserData                    |
 * |\ref NAC_OFF          | NULL                              | NULL                        |
 */
INT adcIoctl(ADC_CMD cmd, INT32 arg1, INT32 arg2)
{
    UINT32 reg;
    switch(cmd)
    {
       case START_MST:             //Menu Start Conversion
       {
          mst_complete=0;
          reg = inpw(REG_ADC_IER);
          reg = reg | ADC_IER_MIEN;
          outpw(REG_ADC_IER, reg);
          reg = inpw(REG_ADC_CTL);
          reg = reg | ADC_CTL_MST;
          outpw(REG_ADC_CTL, reg);
          while(!mst_complete);
       }
       break;
       case VBPOWER_ON:           //Enable ADC Internal Bandgap Power 
       {
          reg = inpw(REG_ADC_CTL);
          reg = reg | ADC_CTL_VBGEN;
          outpw(REG_ADC_CTL, reg);
       }
       break;
       case VBPOWER_OFF:          //Disable ADC Internal Bandgap Power 
       {
          reg = inpw(REG_ADC_CTL);
          reg = reg & ~ADC_CTL_VBGEN;
          outpw(REG_ADC_CTL, reg);
       }
       break;
       case KPPOWER_ON:          //Enable ADC Keypad Power
       {
          reg = inpw(REG_ADC_CTL);
          reg = reg | ADC_CTL_PWKPEN;
          outpw(REG_ADC_CTL, reg);
       }
       break;
       case KPPOWER_OFF:         //Disable ADC Keypad Power
       {
          reg = inpw(REG_ADC_CTL);
          reg = reg & ~ADC_CTL_PWKPEN;
          outpw(REG_ADC_CTL, reg);
       }
       break;
       case PEPOWER_ON:          //Enable Pen Power
       {
          UINT32 treg;
           
          treg = inpw(REG_ADC_IER);
          outpw(REG_ADC_IER, treg & ~(ADC_IER_PEDEIEN | ADC_IER_PEUEIEN));

          reg = inpw(REG_ADC_CTL);
          reg = reg | ADC_CTL_PEDEEN;
          outpw(REG_ADC_CTL, reg);
      
         do{
          reg = (ADC_ISR_PEDEF | ADC_ISR_PEUEF);
          outpw(REG_ADC_ISR, reg);
         }while(inpw(REG_ADC_ISR)&(ADC_ISR_PEDEF | ADC_ISR_PEUEF));
         outpw(REG_ADC_IER,treg);    
       }
       break;
       case PEPOWER_OFF:         //Disable Pen Power
       {
          reg = inpw(REG_ADC_CTL);
          reg = reg & ~ADC_CTL_PEDEEN;
          outpw(REG_ADC_CTL, reg);
       }
       break;
       case KPPRESS_ON:         //Enable Keypad press event
       {
          ADC_CALLBACK keypad_press_callback;
          reg = inpw(REG_ADC_IER);
          reg = reg | ADC_IER_KPEIEN;
          outpw(REG_ADC_IER, reg);
          keypad_press_callback = (ADC_CALLBACK) arg1;
          if (keypad_press_callback != NULL )
          {
             adcHandler.keypad_press_callback = keypad_press_callback;
             adcHandler.keypad_press_userData = (UINT32)arg2;
          }
       }
       break;
       case KPPRESS_OFF:        //Disable Keypad press event
       {
          reg = inpw(REG_ADC_IER);
          reg = reg & ~ADC_IER_KPEIEN;
          outpw(REG_ADC_IER, reg);
          adcHandler.keypad_press_callback = NULL;
          adcHandler.keypad_press_userData = NULL;
       }
       break;
       case KPUP_ON:           //Enable Keypad up event
       {
          ADC_CALLBACK keypad_up_callback;
          reg = inpw(REG_ADC_IER);
          reg = reg | ADC_IER_KPUEIEN;
          outpw(REG_ADC_IER, reg);
          keypad_up_callback = (ADC_CALLBACK) arg1;
          if (keypad_up_callback != NULL )
          {
             adcHandler.keypad_up_callback = keypad_up_callback;
             adcHandler.keypad_up_userData = (UINT32)arg2;
          }
       }
       break;
       case KPUP_OFF:         //Disable Keypad up event
       {
          reg = inpw(REG_ADC_IER);
          reg = reg & ~ADC_IER_KPUEIEN;
          outpw(REG_ADC_IER, reg);
          adcHandler.keypad_up_callback = NULL;
          adcHandler.keypad_up_userData = NULL;
       }
       break;
       case PEDEF_ON:          //Enable Pen Down Event
       {
          ADC_CALLBACK pendown_callback;
          reg = inpw(REG_ADC_IER);
          reg = reg | ADC_IER_PEDEIEN;
          outpw(REG_ADC_IER, reg);
          pendown_callback = (ADC_CALLBACK) arg1;
          if (pendown_callback != NULL )
          {
             adcHandler.pendown_callback = pendown_callback;
             adcHandler.pendown_userData = (UINT32)arg2;
          }
       }
       break;
       case PEDEF_OFF:         //Disable Pen Down Event
       {
          reg = inpw(REG_ADC_IER);
          reg = reg & ~ADC_IER_PEDEIEN;
          outpw(REG_ADC_IER, reg);
          adcHandler.pendown_callback = NULL;
          adcHandler.pendown_userData = NULL;
       }
       break;
#if 1       
       case PEUEF_ON:          //Enable Pen Up Event
       {
          ADC_CALLBACK penup_callback;
          reg = inpw(REG_ADC_IER);
          reg = reg | ADC_IER_PEUEIEN;
          outpw(REG_ADC_IER, reg);
          penup_callback = (ADC_CALLBACK) arg1;
          if (penup_callback != NULL )
          {
             adcHandler.penup_callback = penup_callback;
             adcHandler.penup_userData = (UINT32)arg2;
          }
       }
       break;
       case PEUEF_OFF:         //Disable Pen Up Event
       {
          reg = inpw(REG_ADC_IER);
          reg = reg & ~ADC_IER_PEUEIEN;
          outpw(REG_ADC_IER, reg);
          adcHandler.penup_callback = NULL;
          adcHandler.penup_userData = NULL;
       }
       break;
#endif       
       case WKP_ON:           //Enable Keypad Press Wake Up
       {
          ADC_CALLBACK keypad_wakeup_callback;
          reg = inpw(REG_ADC_CTL);
          reg = reg | ADC_CTL_WKPEN;
          outpw(REG_ADC_CTL, reg);
          reg = inpw(REG_ADC_IER);
          reg = reg | ADC_IER_WKPIEN;
          outpw(REG_ADC_IER, reg);
          reg=inpw(REG_SYS_WKUPSER);
          reg = reg | (1<<26); //Enable ADC Wake System Up.
          outpw(REG_SYS_WKUPSER,reg);
          keypad_wakeup_callback = (ADC_CALLBACK) arg1;
          if (keypad_wakeup_callback != NULL )
          {
             adcHandler.keypad_wakeup_callback = keypad_wakeup_callback;
             adcHandler.keypad_wakeup_userData = (UINT32)arg2;
          }
       }
       break;
       case WKP_OFF:          //Disable Keypad Press Wake Up
       {
          reg = inpw(REG_ADC_CTL);
          reg = reg & ~ADC_CTL_WKPEN;
          outpw(REG_ADC_CTL, reg);
          reg = inpw(REG_ADC_IER);
          reg = reg & ~ADC_IER_WKPIEN;
          outpw(REG_ADC_IER, reg);
          reg=inpw(REG_SYS_WKUPSER);
          reg = reg & ~(1<<26); //Enable ADC Wake System Up.
          outpw(REG_SYS_WKUPSER,reg);
          adcHandler.keypad_wakeup_callback = NULL;
          adcHandler.keypad_wakeup_userData = NULL;
       }
       break;
       case WKT_ON:           //Enable Touch Wake Up
       {
          ADC_CALLBACK touch_wakeup_callback;
          reg = inpw(REG_ADC_CTL);
          reg = reg | ADC_CTL_WKTEN;
          outpw(REG_ADC_CTL, reg);
          reg = inpw(REG_ADC_IER);
          reg = reg | ADC_IER_WKTIEN;
          outpw(REG_ADC_IER, reg);
          reg=inpw(REG_SYS_WKUPSER);
          reg = reg | (1<<26); //Enable ADC Wake System Up.
          outpw(REG_SYS_WKUPSER,reg);
          touch_wakeup_callback = (ADC_CALLBACK) arg1;
          if (touch_wakeup_callback != NULL )
          {
             adcHandler.touch_wakeup_callback = touch_wakeup_callback;
             adcHandler.touch_wakeup_userData = (UINT32)arg2;
          }
       }
       break;
       case WKT_OFF:          //Disable Touch Wake Up
       {
          reg = inpw(REG_ADC_CTL);
          reg = reg & ~ADC_CTL_WKTEN;
          outpw(REG_ADC_CTL, reg);
          reg = inpw(REG_ADC_IER);
          reg = reg & ~ADC_IER_WKTIEN;
          outpw(REG_ADC_IER, reg);
          adcHandler.touch_wakeup_callback = NULL;
          adcHandler.touch_wakeup_userData = NULL;
       }
       break;
       case SWITCH_5WIRE_ON:  //Wire Mode Switch to 5-Wire
       {
          reg = inpw(REG_ADC_CTL);
          reg = reg | ADC_CTL_WMSWCH;
          outpw(REG_ADC_CTL, reg);
       }
       break;
       case SWITCH_5WIRE_OFF: //Wire Mode Switch to 4-Wire
       {
          reg = inpw(REG_ADC_CTL);
          reg = reg & ~ADC_CTL_WMSWCH;
          outpw(REG_ADC_CTL, reg);
       }
       break;

       case T_ON: //Enable Touch detection function
       {
          ADC_CALLBACK touch_callback;
          reg = inpw(REG_ADC_CONF);
          reg = reg | ADC_CONF_TEN;
          outpw(REG_ADC_CONF, reg);
          touch_callback = (ADC_CALLBACK) arg1;
          if (touch_callback != NULL )
          {
             adcHandler.touch_callback = touch_callback;
             adcHandler.touch_userData = (UINT32)arg2;
          }
          /* Flush the FIFO */
          adcHandler.fifoHeadX = 0;
          adcHandler.fifoTailX = 0;
          adcHandler.fifoLengthX = 0;
          adcHandler.fifoHeadY = 0;
          adcHandler.fifoTailY = 0;
          adcHandler.fifoLengthY = 0;
       }
       break;
       case T_OFF: //Disable Touch detection function
       {
          reg = inpw(REG_ADC_CONF);
          reg = reg & ~ADC_CONF_TEN;
          outpw(REG_ADC_CONF, reg);
          adcHandler.touch_callback = NULL;
          adcHandler.touch_userData = NULL;
       }
       break;
       case TAVG_ON: //Enable Touch Mean average for X and Y function
       {
          reg = inpw(REG_ADC_CONF);
          reg = reg | ADC_CONF_DISTMAVEN;
          outpw(REG_ADC_CONF, reg);
       }
       break;
       case TAVG_OFF: //Disable Touch Mean average for X and Y function
       {
          reg = inpw(REG_ADC_CONF);
          reg = reg & ~ADC_CONF_DISTMAVEN;
          outpw(REG_ADC_CONF, reg);
       }
       break;
       case Z_ON: //Enable Press measure function
       {
          ADC_CALLBACK touchz_callback;
          reg = inpw(REG_ADC_CONF);
          reg = reg | ADC_CONF_ZEN;
          outpw(REG_ADC_CONF, reg);
          touchz_callback = (ADC_CALLBACK) arg1;
          if (touchz_callback != NULL )
          {
             adcHandler.touchz_callback = touchz_callback;
             adcHandler.touchz_userData = (UINT32)arg2;
          }
          /* Flush the FIFO */
          adcHandler.fifoHeadZ1 = 0;
          adcHandler.fifoTailZ1 = 0;
          adcHandler.fifoLengthZ1 = 0;
          adcHandler.fifoHeadZ2 = 0;
          adcHandler.fifoTailZ2 = 0;
          adcHandler.fifoLengthZ2 = 0;
       }
       break;
       case Z_OFF: //Disable Press measure function
       {
          reg = inpw(REG_ADC_CONF);
          reg = reg & ~ADC_CONF_ZEN;
          outpw(REG_ADC_CONF, reg);
       }
       break;
       case TZAVG_ON: //Enable Pressure Mean average for Z1 and Z2 function
       {
          reg = inpw(REG_ADC_CONF);
          reg = reg | ADC_CONF_DISZMAVEN;
          outpw(REG_ADC_CONF, reg);
       }
       break;
       case TZAVG_OFF: //Disable Pressure Mean average for Z1 and Z2 function
       {
          reg = inpw(REG_ADC_CONF);
          reg = reg & ~ADC_CONF_DISZMAVEN;
          outpw(REG_ADC_CONF, reg);
       }
       break;
       case NAC_ON: //Enable Normal AD Conversion
       {
          ADC_CALLBACK normal_callback;
          reg = inpw(REG_ADC_CONF);
          reg = reg | ADC_CONF_NACEN | ADC_CONF_REFSEL_AVDD33;
          outpw(REG_ADC_CONF, reg);
          normal_callback = (ADC_CALLBACK) arg1;
          if (normal_callback != NULL )
          {
             adcHandler.normal_callback = normal_callback;
             adcHandler.normal_userData = (UINT32)arg2;
          }
       }
       break;
       case NAC_OFF: //Disable Normal AD Conversion
       {
          reg = inpw(REG_ADC_CONF);
          reg = reg & ~ADC_CONF_NACEN;
          outpw(REG_ADC_CONF, reg);
          adcHandler.normal_callback = NULL;
          adcHandler.normal_userData = NULL;
       }
       break;
       case VBAT_ON: //Enable Voltage Battery Conversion
       {
          ADC_CALLBACK voltage_battery_callback;
          reg = inpw(REG_ADC_CONF);
          reg = reg | ADC_CONF_VBATEN;
          outpw(REG_ADC_CONF, reg);
          voltage_battery_callback = (ADC_CALLBACK) arg1;
          if (voltage_battery_callback != NULL )
          {
             adcHandler.voltage_battery_callback = voltage_battery_callback;
             adcHandler.voltage_battery_userData = (UINT32)arg2;
          }
       }
       break;
       case VBAT_OFF: //Disable Voltage Battery
       {
          reg = inpw(REG_ADC_CONF);
          reg = reg & ~ADC_CONF_VBATEN;
          outpw(REG_ADC_CONF, reg);
          adcHandler.voltage_battery_callback = NULL;
          adcHandler.voltage_battery_userData = NULL;
       }
       break;
       case KPCONV_ON: //Enable Keypad conversion function
       {
          ADC_CALLBACK keypad_conv_callback;
          reg = inpw(REG_ADC_CONF);
          reg = reg | ADC_CONF_KPCEN;
          outpw(REG_ADC_CONF, reg);

          reg = inpw(REG_ADC_IER);
          reg = reg | ADC_IER_KPEIEN;
          outpw(REG_ADC_IER, reg);

          keypad_conv_callback = (ADC_CALLBACK) arg1;
          if (keypad_conv_callback != NULL )
          {
             adcHandler.keypad_conv_callback = keypad_conv_callback;
             adcHandler.keypad_conv_userData = (UINT32)arg2;
          }
       }
       break;
       case KPCONV_OFF: //Disable Keypad conversion function
       {
          reg = inpw(REG_ADC_CONF);
          reg = reg & ~ADC_CONF_KPCEN;
          outpw(REG_ADC_CONF, reg);
          adcHandler.keypad_conv_callback = NULL;
          adcHandler.keypad_conv_userData = NULL;
       }
       break;
       default:
          return ADC_ERR_CMD;
    }
    return Successful;
}

/// @cond HIDDEN_SYMBOLS
#if 0
#define DbgPrintf rt_kprintf
#else
#define DbgPrintf(...)
#endif
/// @endcond HIDDEN_SYMBOLS 
/**
 * @brief       The interrupt service routines of ADC
 * @return      None
 * @details     This function is used to ADC interrupt handler.
 */
void adcISR(void)
{
  unsigned int isr,ier,wkisr,conf;
  conf=inpw(REG_ADC_CONF);
  isr=inpw(REG_ADC_ISR);
  ier=inpw(REG_ADC_IER);
  wkisr=inpw(REG_ADC_WKISR);
  //sysprintf("ADC_IRQHandler Interrupt(0x%08x): ",isr); 
#if 0    
  DbgPrintf("REG_ADC_CTL=0x%08x\n",inpw(REG_ADC_CTL));
  DbgPrintf("REG_ADC_IER=0x%08x\n",inpw(REG_ADC_IER));
  DbgPrintf("REG_ADC_ISR=0x%08x\n",inpw(REG_ADC_ISR));
  DbgPrintf("REG_ADC_WKISR=0x%08x\n",inpw(REG_ADC_WKISR));
  DbgPrintf("SYS_WKUPSSR=0x%08x\n",inpw(REG_SYS_WKUPSSR));
  DbgPrintf("SYS_WKUPSER=0x%08x\n",inpw(REG_SYS_WKUPSER));
#endif
 
  if(isr & ADC_ISR_SELFTF)
  {
    outpw(REG_ADC_ISR, inpw(REG_ADC_ISR) | ADC_ISR_SELFTF);
    DbgPrintf("menu self-test complete\n");
  }

  if(isr & ADC_ISR_TF)
  {
    unsigned int value;
    INT32 tailX, lengthX;
    INT32 tailY, lengthY;
    INT16 *fifoX, *fifoY;
    tailX   = adcHandler.fifoTailX;
    lengthX = adcHandler.fifoLengthX;
    tailY   = adcHandler.fifoTailY;
    lengthY = adcHandler.fifoLengthY;
    fifoX  = adcHandler.fifoX;
    fifoY  = adcHandler.fifoY;
    outpw(REG_ADC_ISR, inpw(REG_ADC_ISR) | ADC_ISR_TF); //Clear TF flags
    value = inpw(REG_ADC_XYDATA);
    if(adcHandler.touch_callback!=NULL)
       adcHandler.touch_callback(value, adcHandler.touch_userData);

    if ( (lengthX<ADC_FIFO_LENGTH) && (lengthY<ADC_FIFO_LENGTH))
    {
       fifoX[tailX] = value & 0xFFF;
       lengthX++;
       tailX++;
       if (tailX == ADC_FIFO_LENGTH) tailX = 0;

       fifoY[tailY] = (value >>16) & 0xFFF;
       lengthY++;
       tailY++;
       if (tailY == ADC_FIFO_LENGTH) tailY = 0;
    }
    /* Update FIFO status */
    adcHandler.fifoTailX = tailX;
    adcHandler.fifoLengthX = lengthX;
    adcHandler.fifoTailY = tailY;
    adcHandler.fifoLengthY = lengthY;
    DbgPrintf("touch detect complete\n");
  }

  if((isr & ADC_ISR_KPEF) && (ier & ADC_IER_KPEIEN))
  {
    outpw(REG_ADC_ISR,ADC_ISR_KPEF);
    if(adcHandler.keypad_press_callback!=NULL)
       adcHandler.keypad_press_callback(1, adcHandler.keypad_press_userData);
    DbgPrintf("key press complete\n");
  }

  if((isr & ADC_ISR_ZF) && (conf & ADC_CONF_ZEN))
  {
    unsigned int value;
    volatile INT32 tailZ1, lengthZ1;
    volatile INT32 tailZ2, lengthZ2;
    volatile INT16 *fifoZ1, *fifoZ2;
    tailZ1   = adcHandler.fifoTailZ1;
    lengthZ1 = adcHandler.fifoLengthZ1;
    tailZ2   = adcHandler.fifoTailZ2;
    lengthZ2 = adcHandler.fifoLengthZ2;

    fifoZ1  = adcHandler.fifoZ1;
    fifoZ2  = adcHandler.fifoZ2;
    outpw(REG_ADC_ISR, inpw(REG_ADC_ISR) | ADC_ISR_ZF); //clear TF flags
    value = inpw(REG_ADC_ZDATA);
    if(adcHandler.touchz_callback!=NULL)
       adcHandler.touchz_callback(value, adcHandler.touchz_userData);
    if ( (lengthZ1<ADC_FIFO_LENGTH) && (lengthZ2<ADC_FIFO_LENGTH))
    {
       fifoZ1[tailZ1] = value & 0xFFF;
       lengthZ1++;
       tailZ1++;
       if (tailZ1 == ADC_FIFO_LENGTH) tailZ1 = 0;

       fifoZ2[tailZ2] = (value >>16) & 0xFFF;
       lengthZ2++;
       tailZ2++;
       if (tailZ2 == ADC_FIFO_LENGTH) tailZ2 = 0;
    }
    /* Update FIFO status */
    adcHandler.fifoTailZ1 = tailZ1;
    adcHandler.fifoLengthZ1 = lengthZ1;
    adcHandler.fifoTailZ2 = tailZ2;
    adcHandler.fifoLengthZ2 = lengthZ2;
    DbgPrintf("z conversion complete\n");
  }

  if((isr & ADC_ISR_NACF) && (conf & ADC_CONF_NACEN))
  {
    outpw(REG_ADC_ISR, inpw(REG_ADC_ISR) | ADC_ISR_NACF);
    if(adcHandler.normal_callback!=NULL)
       adcHandler.normal_callback(inpw(REG_ADC_DATA), adcHandler.normal_userData);
    DbgPrintf("normal AD conversion complete\n");
  }

  if((isr & ADC_ISR_VBF) && (conf & ADC_CONF_VBATEN))
  {
    if(adcHandler.voltage_battery_callback!=NULL)
       adcHandler.voltage_battery_callback(inpw(REG_ADC_VBADATA), adcHandler.voltage_battery_userData);
    outpw(REG_ADC_ISR, inpw(REG_ADC_ISR) | ADC_ISR_VBF);
    DbgPrintf("bettery volage complete\n");
  }

  if((isr & ADC_ISR_KPCF)&& (conf & ADC_CONF_KPCEN))
  {
    unsigned int value;
    outpw(REG_ADC_ISR, inpw(REG_ADC_ISR) | ADC_ISR_KPCF);
    value=inpw(REG_ADC_KPDATA);
    if(adcHandler.keypad_conv_callback!=NULL)
       adcHandler.keypad_conv_callback(value, adcHandler.keypad_conv_userData);
    DbgPrintf("Menu Keypad Press Conversion Finish\n");
  }

  if((isr & ADC_ISR_KPUEF) && (ier & ADC_IER_KPUEIEN))
  {
    outpw(REG_ADC_ISR,ADC_ISR_KPUEF);
    if(adcHandler.keypad_up_callback!=NULL)
       adcHandler.keypad_up_callback(0, adcHandler.keypad_press_userData);
    DbgPrintf("keypad up\n");
  }
  
  if((isr & ADC_ISR_PEUEF) && (ier & ADC_IER_PEUEIEN))
  {
    outpw(REG_ADC_ISR, inpw(REG_ADC_ISR) | ADC_ISR_PEUEF);
    DbgPrintf("menu pen up complete\n");
  }else if((isr & ADC_ISR_PEDEF) && (ier & ADC_IER_PEDEIEN))
  {
    if(adcHandler.pendown_callback!=NULL)
      adcHandler.pendown_callback(isr, adcHandler.pendown_userData);
    outpw(REG_ADC_ISR, inpw(REG_ADC_ISR) | ADC_ISR_PEDEF);
    DbgPrintf("pen down complete\n");
  }
  
  if(isr & ADC_ISR_MF)
  {
    outpw(REG_ADC_ISR, inpw(REG_ADC_ISR) | ADC_ISR_MF);
    mst_complete=1;
    DbgPrintf("menu complete\n");
  }
  
  if((wkisr & ADC_WKISR_WKPEF) && (ier & ADC_IER_WKPIEN))
  {
    if(adcHandler.keypad_wakeup_callback!=NULL)
      adcHandler.keypad_wakeup_callback(wkisr, adcHandler.keypad_wakeup_userData);
    outpw(REG_ADC_WKISR,ADC_WKISR_WKPEF);

    if(inpw(REG_SYS_WKUPSSR) & (1<<26))
      outpw(REG_SYS_WKUPSSR,(1<<26));
    DbgPrintf("key press event wakeup\n");
  }
  
  if((wkisr & ADC_WKISR_WPEDEF) && (ier & ADC_IER_WKTIEN) )
  {
   if(adcHandler.touch_wakeup_callback!=NULL)
      adcHandler.touch_wakeup_callback(wkisr, adcHandler.touch_wakeup_userData);
   outpw(REG_ADC_WKISR,ADC_WKISR_WPEDEF);
   if(inpw(REG_SYS_WKUPSSR) & (1<<26))
      outpw(REG_SYS_WKUPSSR,(1<<26));
    DbgPrintf("pen down event wakeup\n");
  }
}

/**
 * @brief       The ChangeChannel function of ADC device library
 *
 * @param       channel    Select ADC input for normal mode.Including:
 *                         - \ref AIN0
 *                         - \ref AIN1
 *                         - \ref AIN2
 *                         - \ref AIN3
 *                         - \ref AIN4
 *                         - \ref AIN5
 *                         - \ref AIN6
 *                         - \ref AIN7
 *
 * @retval      <0         Wrong argument
 * @retval      0          Success
 *
 * @details     This function is used to set channel for normal mode.
 */
INT adcChangeChannel(int channel)
{
    UINT32 reg;
    if ((channel>>3) < 0 || (channel>>3) > 7)
    {
       return ADC_ERR_ARGS;
    }
    reg = inpw(REG_ADC_CONF);
    reg = (reg & ~ADC_CONF_CHSEL_Msk) | channel;
    outpw(REG_ADC_CONF,reg);
    return Successful;
}

