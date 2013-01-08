#include <stdbool.h>
#include "stm32f10x.h"

#include "board.h"
#include "touch.h"

#include <rtthread.h>
#include <rtgui/event.h>
#include <rtgui/kbddef.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

/*
MISO PA6
MOSI PA7
CLK  PA5
CS   PC4
*/

#define   CS_0()          GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define   CS_1()          GPIO_SetBits(GPIOC,GPIO_Pin_4)

/*
7  6 - 4  3      2     1-0
s  A2-A0 MODE SER/DFR PD1-PD0
*/
#define TOUCH_MSR_Y  0x90   //读X轴坐标指令 addr:1
#define TOUCH_MSR_X  0xD0   //读Y轴坐标指令 addr:3

struct rtgui_touch_device
{
    struct rt_device parent;

    rt_timer_t poll_timer;
    rt_uint16_t x, y;

    rt_bool_t calibrating;
    rt_touch_calibration_func_t calibration_func;

    rt_uint16_t min_x, max_x;
    rt_uint16_t min_y, max_y;
};
static struct rtgui_touch_device *touch = RT_NULL;

extern unsigned char SPI_WriteByte(unsigned char data);
rt_inline void EXTI_Enable(rt_uint32_t enable);

struct rt_semaphore spi1_lock;

void rt_hw_spi1_baud_rate(uint16_t SPI_BaudRatePrescaler)
{
    SPI1->CR1 &= ~SPI_BaudRatePrescaler_256;
    SPI1->CR1 |= SPI_BaudRatePrescaler;
}

uint8_t SPI_WriteByte(unsigned char data)
{
    //Wait until the transmit buffer is empty
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    // Send the byte
    SPI_I2S_SendData(SPI1, data);

    //Wait until a data is received
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    // Get the received data
    data = SPI_I2S_ReceiveData(SPI1);

    // Return the shifted data
    return data;
}

//SPI写数据
static void WriteDataTo7843(unsigned char num)
{
    SPI_WriteByte(num);
}

#define X_WIDTH 240
#define Y_WIDTH 320

static void rtgui_touch_calculate()
{
    if (touch != RT_NULL)
    {
        rt_sem_take(&spi1_lock, RT_WAITING_FOREVER);
        /* SPI1 configure */
        rt_hw_spi1_baud_rate(SPI_BaudRatePrescaler_64);/* 72M/64=1.125M */

        //读取触摸值
        {
            rt_uint16_t tmpx[10];
            rt_uint16_t tmpy[10];
            unsigned int i;

            /* From the datasheet:
             * When the very first CLK after the control byte comes in, the
             * DOUT of ADS7843 is not valid. So we could only get 7bits from
             * the first SPI_WriteByte. And the got the following 5 bits from
             * another SPI_WriteByte.(aligned MSB)
             */
            for(i=0; i<10; i++)
            {
                CS_0();
                WriteDataTo7843(TOUCH_MSR_X);
                tmpx[i] = (SPI_WriteByte(0x00) & 0x7F) << 5;
                tmpx[i] |= (SPI_WriteByte(TOUCH_MSR_Y) >> 3) & 0x1F;

                tmpy[i] = (SPI_WriteByte(0x00) & 0x7F) << 5;
                tmpy[i] |= (SPI_WriteByte(0x00) >> 3) & 0x1F;

                WriteDataTo7843( 1<<7 ); /* 打开中断 */
                CS_1();
            }

            //去最高值与最低值,再取平均值
            {
                rt_uint32_t min_x = 0xFFFF,min_y = 0xFFFF;
                rt_uint32_t max_x = 0,max_y = 0;
                rt_uint32_t total_x = 0;
                rt_uint32_t total_y = 0;
                unsigned int i;

                for(i=0;i<10;i++)
                {
                    if( tmpx[i] < min_x )
                    {
                        min_x = tmpx[i];
                    }
                    if( tmpx[i] > max_x )
                    {
                        max_x = tmpx[i];
                    }
                    total_x += tmpx[i];

                    if( tmpy[i] < min_y )
                    {
                        min_y = tmpy[i];
                    }
                    if( tmpy[i] > max_y )
                    {
                        max_y = tmpy[i];
                    }
                    total_y += tmpy[i];
                }
                total_x = total_x - min_x - max_x;
                total_y = total_y - min_y - max_y;
                touch->x = total_x / 8;
                touch->y = total_y / 8;
            }//去最高值与最低值,再取平均值
        }//读取触摸值

        rt_sem_release(&spi1_lock);

        /* if it's not in calibration status  */
        if (touch->calibrating != RT_TRUE)
        {
            if (touch->max_x > touch->min_x)
            {
                touch->x = (touch->x - touch->min_x) * X_WIDTH/(touch->max_x - touch->min_x);
            }
            else if (touch->max_x < touch->min_x)
            {
                touch->x = (touch->min_x - touch->x) * X_WIDTH/(touch->min_x - touch->max_x);
            }

            if (touch->max_y > touch->min_y)
            {
                touch->y = (touch->y - touch->min_y) * Y_WIDTH /(touch->max_y - touch->min_y);
            }
            else if (touch->max_y < touch->min_y)
            {
                touch->y = (touch->min_y - touch->y) * Y_WIDTH /(touch->min_y - touch->max_y);
            }

            // normalize the data
            if (touch->x & 0x8000)
                touch->x = 0;
            else if (touch->x > X_WIDTH)
                touch->x = X_WIDTH - 1;

            if (touch->y & 0x8000)
                touch->y = 0;
            else if (touch->y > Y_WIDTH)
                touch->y = Y_WIDTH - 1;
        }
    }
}

void touch_timeout(void* parameter)
{
    static unsigned int touched_down = 0;
    struct rtgui_event_mouse emouse;
    static struct _touch_previous
    {
        rt_uint32_t x;
        rt_uint32_t y;
    } touch_previous;

    /* touch time is too short and we lost the position already. */
    if ((!touched_down) && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) != 0)
        return;

    if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) != 0)
    {
        int tmer = RT_TICK_PER_SECOND/8 ;
        EXTI_Enable(1);
        emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
        emouse.button = (RTGUI_MOUSE_BUTTON_LEFT |RTGUI_MOUSE_BUTTON_UP);

        /* use old value */
        emouse.x = touch->x;
        emouse.y = touch->y;

        /* stop timer */
        rt_timer_stop(touch->poll_timer);
        rt_kprintf("touch up: (%d, %d)\n", emouse.x, emouse.y);
        touched_down = 0;

        if ((touch->calibrating == RT_TRUE) && (touch->calibration_func != RT_NULL))
        {
            /* callback function */
            touch->calibration_func(emouse.x, emouse.y);
        }
        rt_timer_control(touch->poll_timer , RT_TIMER_CTRL_SET_TIME , &tmer);
    }
    else
    {
        if(touched_down == 0)
        {
            int tmer = RT_TICK_PER_SECOND/20 ;
            /* calculation */
            rtgui_touch_calculate();

            /* send mouse event */
            emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
            emouse.parent.sender = RT_NULL;

            emouse.x = touch->x;
            emouse.y = touch->y;

            touch_previous.x = touch->x;
            touch_previous.y = touch->y;

            /* init mouse button */
            emouse.button = (RTGUI_MOUSE_BUTTON_LEFT |RTGUI_MOUSE_BUTTON_DOWN);

//            rt_kprintf("touch down: (%d, %d)\n", emouse.x, emouse.y);
            touched_down = 1;
            rt_timer_control(touch->poll_timer , RT_TIMER_CTRL_SET_TIME , &tmer);
        }
        else
        {
            /* calculation */
            rtgui_touch_calculate();

#define previous_keep      8
            //判断移动距离是否小于previous_keep,减少误动作.
            if(
                (touch_previous.x<touch->x+previous_keep)
                && (touch_previous.x>touch->x-previous_keep)
                && (touch_previous.y<touch->y+previous_keep)
                && (touch_previous.y>touch->y-previous_keep)  )
            {
                return;
            }

            touch_previous.x = touch->x;
            touch_previous.y = touch->y;

            /* send mouse event */
            emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON ;
            emouse.parent.sender = RT_NULL;

            emouse.x = touch->x;
            emouse.y = touch->y;

            /* init mouse button */
            emouse.button = (RTGUI_MOUSE_BUTTON_RIGHT |RTGUI_MOUSE_BUTTON_DOWN);
//            rt_kprintf("touch motion: (%d, %d)\n", emouse.x, emouse.y);
        }
    }

    /* send event to server */
    if (touch->calibrating != RT_TRUE)
        rtgui_server_post_event(&emouse.parent, sizeof(struct rtgui_event_mouse));
}

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the EXTI0 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

rt_inline void EXTI_Enable(rt_uint32_t enable)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Configure  EXTI  */
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//Falling下降沿 Rising上升

    if (enable)
    {
        /* enable */
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    }
    else
    {
        /* disable */
        EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    }

    EXTI_Init(&EXTI_InitStructure);
    EXTI_ClearITPendingBit(EXTI_Line1);
}

static void EXTI_Configuration(void)
{
    /* PB1 touch INT */
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_Init(GPIOB,&GPIO_InitStructure);
    }

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

    /* Configure  EXTI  */
    EXTI_Enable(1);
}

/* RT-Thread Device Interface */
static rt_err_t rtgui_touch_init (rt_device_t dev)
{
    NVIC_Configuration();
    EXTI_Configuration();

    /* PC4 touch CS */
    {
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
        GPIO_Init(GPIOC,&GPIO_InitStructure);
        CS_1();
    }

    CS_0();
    WriteDataTo7843( 1<<7 ); /* 打开中断 */
    CS_1();

    return RT_EOK;
}

static rt_err_t rtgui_touch_control (rt_device_t dev, rt_uint8_t cmd, void *args)
{
    switch (cmd)
    {
    case RT_TOUCH_CALIBRATION:
        touch->calibrating = RT_TRUE;
        touch->calibration_func = (rt_touch_calibration_func_t)args;
        break;

    case RT_TOUCH_NORMAL:
        touch->calibrating = RT_FALSE;
        break;

    case RT_TOUCH_CALIBRATION_DATA:
    {
        struct calibration_data* data;

        data = (struct calibration_data*) args;

        //update
        touch->min_x = data->min_x;
        touch->max_x = data->max_x;
        touch->min_y = data->min_y;
        touch->max_y = data->max_y;
    }
    break;
    }

    return RT_EOK;
}

void EXTI1_IRQHandler(void)
{
    /* disable interrupt */
    EXTI_Enable(0);

    /* start timer */
    rt_timer_start(touch->poll_timer);

    EXTI_ClearITPendingBit(EXTI_Line1);
}

void rtgui_touch_hw_init(void)
{
    /* SPI1 config */
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        SPI_InitTypeDef SPI_InitStructure;

        /* Enable SPI1 Periph clock */
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
                               | RCC_APB2Periph_AFIO | RCC_APB2Periph_SPI1,
                               ENABLE);

        /* Configure SPI1 pins: PA5-SCK, PA6-MISO and PA7-MOSI */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        /*------------------------ SPI1 configuration ------------------------*/
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI_Direction_1Line_Tx;
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
        SPI_InitStructure.SPI_NSS  = SPI_NSS_Soft;
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;/* 72M/64=1.125M */
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
        SPI_InitStructure.SPI_CRCPolynomial = 7;

        SPI_I2S_DeInit(SPI1);
        SPI_Init(SPI1, &SPI_InitStructure);

        /* Enable SPI_MASTER */
        SPI_Cmd(SPI1, ENABLE);
        SPI_CalculateCRC(SPI1, DISABLE);

        if (rt_sem_init(&spi1_lock, "spi1lock", 1, RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            rt_kprintf("init spi1 lock semaphore failed\n");
        }
    } /* SPI1 config */

    touch = (struct rtgui_touch_device*)rt_malloc (sizeof(struct rtgui_touch_device));
    if (touch == RT_NULL) return; /* no memory yet */

    /* clear device structure */
    rt_memset(&(touch->parent), 0, sizeof(struct rt_device));
    touch->calibrating = false;

    /* init device structure */
    touch->parent.type = RT_Device_Class_Unknown;
    touch->parent.init = rtgui_touch_init;
    touch->parent.control = rtgui_touch_control;
    touch->parent.user_data = RT_NULL;

    /* create 1/8 second timer */
    touch->poll_timer = rt_timer_create("touch", touch_timeout, RT_NULL,
                                        RT_TICK_PER_SECOND/8, RT_TIMER_FLAG_PERIODIC);

    /* register touch device to RT-Thread */
    rt_device_register(&(touch->parent), "touch", RT_DEVICE_FLAG_RDWR);
}

#ifdef RT_USING_FINSH
#include <finsh.h>

void touch_t( rt_uint16_t x , rt_uint16_t y )
{
    struct rtgui_event_mouse emouse ;
    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.parent.sender = RT_NULL;

    emouse.x = x ;
    emouse.y = y ;
    /* init mouse button */
    emouse.button = (RTGUI_MOUSE_BUTTON_LEFT |RTGUI_MOUSE_BUTTON_DOWN );
    rtgui_server_post_event(&emouse.parent, sizeof(struct rtgui_event_mouse));

    rt_thread_delay(2) ;
    emouse.button = (RTGUI_MOUSE_BUTTON_LEFT |RTGUI_MOUSE_BUTTON_UP );
    rtgui_server_post_event(&emouse.parent, sizeof(struct rtgui_event_mouse));
}

FINSH_FUNCTION_EXPORT(touch_t, x & y ) ;
#endif
