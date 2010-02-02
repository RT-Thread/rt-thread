/*
+-----------------------
|
| 红外自学习遥控
|
| Chang Logs:
| Date           Author       Notes
| 2010-01-02     aozima       The bate version.
+----------------------------------------------------
*/

#include <rtthread.h>
#include <dfs_posix.h>
#include <stm32f10x.h>

/* 设置允许偏差,单位0.01ms */
#define remote_deviation         15
#define remote_code_len_max      100


/* 红外模式 0:没启动,1:自学习,2:正常解码 */
unsigned int rem_mode = 0;

static unsigned int first_tick = 0;
static unsigned int rx_count = 0;
static unsigned short rm_code[remote_code_len_max];

struct rem_codes_typedef
{
    unsigned int len;
    unsigned short rem_code[remote_code_len_max];
};
struct rem_codes_typedef * p_rem_code_src = RT_NULL;

static const char  str1[]="KEY_UP";     /* 上 */
static const char  str2[]="KEY_DOWN";   /* 下 */
static const char  str3[]="KEY_LEFT";   /* 左 */
static const char  str4[]="KEY_RIGHT";  /* 右 */
static const char  str5[]="KEY_ENTER";  /* 确认 */
static const char  str6[]="KEY_RETURN"; /* 返回 */
static const char * desc_key[6]= {str1,str2,str3,str4,str5,str6};


/* tim5 configure */
static void TIM5_Configuration(void)
{
    /* 时钟及分频设置 */
    {
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        /* Time Base configuration */
        /* 72M/720 = 0.01ms */
        TIM_TimeBaseStructure.TIM_Prescaler = 720-1;
        //计数模式:向上计数
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
        //重新计数的起始值
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

        TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    }

    /* 捕获设置 */
    {
        TIM_ICInitTypeDef  TIM_ICInitStructure;

        TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;/* 每次检测到捕获输入就触发一次捕获 */
        TIM_ICInitStructure.TIM_ICFilter    = 8;/* 滤波 */

        TIM_ICInitStructure.TIM_Channel     = TIM_Channel_3;//选择通道3
        TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Falling;//下降沿
        TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//通道方向选择
        TIM_ICInit(TIM5, &TIM_ICInitStructure);

        TIM_ICInitStructure.TIM_Channel     = TIM_Channel_4;//选择通道3
        TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;//上升沿
        TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//通道方向选择
        TIM_ICInit(TIM5, &TIM_ICInitStructure);
    }

    /* 输入触发源选择:外部输入触发 */
    TIM_SelectInputTrigger(TIM5, TIM_TS_ETRF);//TIM_TS_ETRF 外部触发
    /* 从模式-复位模式 */
    /* TIM_SlaveMode_Reset 4:选中的触发输入(TRGI)的上升沿重新初始化计数器，并且产生一个更新寄存器的信号 */
    TIM_SelectSlaveMode(TIM5, TIM_SlaveMode_Reset);
    TIM_SelectMasterSlaveMode(TIM5, TIM_MasterSlaveMode_Enable);

    /* TIM enable counter */
    TIM_Cmd(TIM5, ENABLE);

    /* Enable the CC3 and CC4 Interrupt Request */
    TIM_ITConfig(TIM5, TIM_IT_CC3, ENABLE);
    TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);
}

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the TIM5 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    /* TIM5 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    /* clock enable */
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA ,ENABLE);
}

static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* TIM5 channel 3 pin (PA.02) configuration */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void rem_start(void)
{
    RCC_Configuration();
    GPIO_Configuration();

    /* configure TIM5 for remote and encoder */
    NVIC_Configuration();
    TIM5_Configuration();

    p_rem_code_src = rt_malloc( sizeof(struct rem_codes_typedef)*6 );
    rt_memset(p_rem_code_src,0, sizeof(struct rem_codes_typedef)*6 );

    /* 解读红外信息 */
    {
        int fd,size;
        char buf[7];/* 文件读取临时缓存 #####\r\n */
        unsigned int i;
        unsigned short tmp;
        unsigned int read_index = 0;
        unsigned int EOF_flag = 1;

        rt_kprintf("\r\n解读红外信息");
        fd = open("/resource/remote.txt",O_RDONLY,0);
        if( fd>0 )
        {
            rt_kprintf("\r/resource/remote.txt打开成功");
            while( EOF_flag )
            {
                /* 读取长度 */
                size = read(fd,buf,7);
                if( (size == 7) && (buf[5]=='\r') && buf[6]=='\n' )
                {
                    /* 转换得到样本数据长度 */
                    tmp =   (buf[0]-'0')*10000
                            + (buf[1]-'0')*1000
                            + (buf[2]-'0')*100
                            + (buf[3]-'0')*10
                            + (buf[4]-'0');
                    if( tmp<100 )
                    {
                        unsigned int code_len = tmp;
                        p_rem_code_src[read_index].len = code_len;
                        /* 如果样本长度符合 就开始从文件读取编码数据 */
                        for(i=0; i<code_len; i++)
                        {
                            size = read(fd,buf,7);
                            if( (size == 7) && (buf[5]=='\r') && buf[6]=='\n' )
                            {
                                /* 转换得到样本数据 */
                                tmp =   (buf[0]-'0')*10000
                                        + (buf[1]-'0')*1000
                                        + (buf[2]-'0')*100
                                        + (buf[3]-'0')*10
                                        + (buf[4]-'0');
                                p_rem_code_src[read_index].rem_code[i] = tmp;
                            }
                        }
                        read_index++;
                    }
                }
                else
                {
                    EOF_flag = 0;
                }
            }//while( EOF_flag )

            /* 判断是否正确解读编码数据文件 */
            if ( p_rem_code_src[0].len > 0 && p_rem_code_src[0].len < remote_code_len_max )
            {
                /* 设置工作模式为正常识别模式 */
                rem_mode = 2;
                rt_kprintf("\r红外遥控编码文件解读完成,已打开红外遥控功能\r\n");
            }
            else
            {
                /* 设置工作模式为正常识别模式 */
                rem_mode = 0;
                rt_kprintf("\r\n红外遥控编码文件解读失败,已关闭红外遥控功能\r\n");
            }
        }
        else
        {
            rt_kprintf("\r红外遥控编码文件 /resource/remote.txt 打开失败! fd:%d\r\n无法开启红外遥控功能.\r\n请执行rem_study()进行自动学习\r\n",fd);
        }
        close(fd);
    }/* 解读红外信息 */
}

#include <rtgui/event.h>
void rem_encoder(struct rtgui_event_kbd * p)
{
    struct rtgui_event_kbd * p_kbd_event = p;

    /* 检查是否有数据被捕获 */
    if( (rem_mode==2) && (rt_tick_get()>first_tick+10) && (rx_count > 0) )
    {
        /* 手动清零第一个捕获结果 */
        rm_code[0] = 0;
        rx_count = 0;

        /* 匹配捕获的数据 */
        {
            unsigned int tmp;
            unsigned int err_flag = 0;
            unsigned int rem_cmp_n = 6;

            /* 循环匹配所有KEY */
            while( rem_cmp_n )
            {
                unsigned int tmp2 = p_rem_code_src[ 6-rem_cmp_n ].len;
                //rt_kprintf("\r\nrem_cmp_n:%d  tmp2:%d",rem_cmp_n,tmp2);
                if( tmp2 )
                {

                    for(tmp=0; tmp<tmp2; tmp++)
                    {
                        /* 判断捕获结果是否在偏差允许范围内 */
                        if( !( (rm_code[tmp] < p_rem_code_src[6-rem_cmp_n].rem_code[tmp]+remote_deviation)
                                && (rm_code[tmp] > p_rem_code_src[6-rem_cmp_n].rem_code[tmp]-remote_deviation)) )
                        {
                            err_flag = 1;
                        }
                    }
                }
                else
                {
                    err_flag = 1;
                    rt_kprintf("\r\n解码失败");
                }

                if( err_flag==0 )
                {
                    /* 对比全部数据符合 */
                    rt_kprintf("\r\n识别到遥控按键 %s",desc_key[6-rem_cmp_n]);
                    switch( rem_cmp_n )
                    {
                    case 6:
                        p_kbd_event->key  = RTGUIK_UP;
                        break;
                    case 5:
                        p_kbd_event->key  = RTGUIK_DOWN;
                        break;
                    case 4:
                        p_kbd_event->key  = RTGUIK_LEFT;
                        break;
                    case 3:
                        p_kbd_event->key  = RTGUIK_RIGHT;
                        break;
                    case 2:
                        p_kbd_event->key  = RTGUIK_RETURN;
                        break;
                    case 1:
                        p_kbd_event->key  = RTGUIK_HOME;
                        break;
                    default:
                        break;
                    }
                    rem_cmp_n = 0;
                }
                else
                {
                    /* 对比不符合,清零错误标致,以进行下一次对比 */
                    err_flag = 0;
                    rem_cmp_n --;
                }

            }
        }
    }//红外遥控匹配
}

/* remote isr */
void remote_isr(void)
{
    static unsigned int clr_flag = 1;
    unsigned int tick_now  = rt_tick_get();

    /* 红外遥控下降沿 */
    if(TIM_GetITStatus(TIM5, TIM_IT_CC3) == SET)
    {
        switch( rem_mode )
        {
        case 0://未启动
            break;
        case 1://自学习
            if( (rx_count==0) || (rx_count>90) || (tick_now>first_tick+10) )
            {
                //需要清0
                rx_count = 0;
                clr_flag = 1;
            }
            if( rx_count < remote_code_len_max )
            {
                rm_code[rx_count++] = TIM_GetCapture3(TIM5);
            }
            break;
        case 2://正常解码
            if( (rx_count>90) || tick_now>first_tick+10 )
            {
                rx_count = 0;
                clr_flag = 1;
            }
            if(rx_count < remote_code_len_max )
            {
                rm_code[rx_count++] = TIM_GetCapture3(TIM5);
            }
            break;
        default:
            rem_mode = 0;//设置模式为未启动
            break;
        }
        TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);
    }

    /* 红外遥控上升沿 */
    if(TIM_GetITStatus(TIM5, TIM_IT_CC4) == SET)
    {
        switch( rem_mode )
        {
        case 0://未启动
            break;
        case 1://自学习
            if( rx_count < remote_code_len_max )
            {
                rm_code[rx_count++] = TIM_GetCapture4(TIM5);
            }
            break;
        case 2://正常解码
            if( rx_count < remote_code_len_max )
            {
                rm_code[rx_count++] = TIM_GetCapture4(TIM5);
            }
            break;
        default:
            rem_mode = 0;//设置模式为未启动
            break;
        }
        TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);
    }

    //更新时间戳
    first_tick = tick_now;
    //检测是否需要重置计数器
    if( clr_flag )
    {
        //重置计数器
        TIM_SetCounter(TIM5,0);
        clr_flag = 0;
    }
}

#include <finsh.h>
/* 启动红外学习程序 */
int rem_study(void)
{
    unsigned int i;

    int fd,size;
    unsigned char tmp_buf[ (remote_code_len_max+1)*7 ];

    rem_mode = 1;
    rx_count = 0;
    rt_kprintf("\r\n红外遥控自学习功能启动");
    fd = open("/resource/remote.txt",O_WRONLY | O_TRUNC,0);
    if( !(fd<0) )
    {
        rt_kprintf("\r\n红外遥控编码文件 /resource/remote.txt 创建成功");
    }
    else
    {
        rt_kprintf("\r红外遥控编码文件 /resource/remote.txt 创建失败.\r\n学习程序中止.");
        return -1;
    }

    /* 学习6个键盘 */
    for( i=0; i<6; i++)
    {
        unsigned int is_ok = 1;
        rt_kprintf("\r\npress key %s",desc_key[i]);
        while( is_ok==1 )
        {
            if( (rem_mode==1) && (rt_tick_get()>first_tick+10) && (rx_count > 0) )
            {
                unsigned int a,b;
                unsigned char * p = tmp_buf;

                rt_kprintf("\r\n%s",desc_key[i]);

                b = rx_count;
                p_rem_code_src[i].len = rx_count;

                /* TIM disable counter */
                TIM_Cmd(TIM5, DISABLE);
                /* disable the CC3 and CC4 Interrupt Request */
                TIM_ITConfig(TIM5, TIM_IT_CC3, DISABLE);
                TIM_ITConfig(TIM5, TIM_IT_CC4, DISABLE);

                p[0] = rx_count / 10000 +'0';
                rx_count = rx_count % 10000;
                p[1] = rx_count / 1000  +'0';
                rx_count = rx_count % 1000;
                p[2] = rx_count / 100   +'0';
                rx_count = rx_count % 100;
                p[3] = rx_count / 10    +'0';
                rx_count = rx_count % 10;
                p[4] = rx_count        +'0';
                rx_count = 0;
                p[5] = '\r';
                p[6] = '\n';
                p += 7;

                rm_code[0] = 0;

                for( a=0; a<b; a++)
                {
                    /* 把当前数据直接写进样品数据 */
                    p_rem_code_src[i].rem_code[a] = rm_code[a];

                    /* 然后转换成文本格式 #####\r\n */
                    p[0] = rm_code[a] / 10000 +'0';
                    rm_code[a] = rm_code[a] % 10000;
                    p[1] = rm_code[a] / 1000  +'0';
                    rm_code[a] = rm_code[a] % 1000;
                    p[2] = rm_code[a] / 100   +'0';
                    rm_code[a] = rm_code[a] % 100;
                    p[3] = rm_code[a] / 10   +'0';
                    rm_code[a] = rm_code[a] % 10;
                    p[4] = rm_code[a]        +'0';
                    p[5] = '\r';
                    p[6] = '\n';
                    p += 7;
                }
                size = write(fd,(char*)tmp_buf,(b+1)*7 );
                if( size==((b+1)*7) )
                {
                    rt_kprintf("文件写入成功");
                    is_ok++;
                    rt_thread_delay( 2 );

                    /* 重新打开 TIM5 进行捕获 */
                    TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);
                    TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);
                    /* TIM ENABLE counter */
                    TIM_Cmd(TIM5, ENABLE);
                    /* ENABLE the CC3 and CC4 Interrupt Request */
                    TIM_ITConfig(TIM5, TIM_IT_CC3, ENABLE);
                    TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);
                }
                else
                {
                    rt_kprintf("文件写入失败\r\n红外学习程序退出");
                    return -1;
                }
            }
            rt_thread_delay(1);
        }//while( is_ok==1 )
    }//for( i=0; i<6; i++)
    close(fd);
    rt_kprintf("\r\n学习完成,现在进入正常识别模式\r\n");
    rem_mode = 2;
    return 0;
}
FINSH_FUNCTION_EXPORT(rem_study, rem_study);
