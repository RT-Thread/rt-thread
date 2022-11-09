#include "lcd.h"
#include "font.h"

#define DRV_DEBUG
#define LOG_TAG             "spi.lcd"
#include <drv_log.h>

static int32_t lcd_init(void);
static int32_t lcd_writereg(uint8_t reg,uint8_t* pdata,uint32_t length);
static int32_t lcd_readreg(uint8_t reg,uint8_t* pdata);
static int32_t lcd_senddata(uint8_t* pdata,uint32_t length);
static int32_t lcd_recvdata(uint8_t* pdata,uint32_t length);

ST7735_IO_t st7735_pIO = {
    lcd_init,
    RT_NULL,
    RT_NULL,
    lcd_writereg,
    lcd_readreg,
    lcd_senddata,
    lcd_recvdata,
    RT_NULL
};
ST7735_Object_t st7735_pObj;
uint32_t st7735_id;
static struct rt_spi_device *spi_dev_lcd;
#ifdef LCD_BACKLIGHT_USING_PWM
static struct rt_device_pwm *lcd_pwm_dev;
static uint32_t NowBrightness;
#endif
extern unsigned char WeActStudiologo[];

//LCD_RS
#define LCD_RS_SET              rt_pin_write(WR_RS_PIN, PIN_HIGH)
#define LCD_RS_RESET            rt_pin_write(WR_RS_PIN, PIN_LOW)
//LCD_CS
#define LCD_CS_SET              rt_pin_write(CS_PIN, PIN_HIGH)
#define LCD_CS_RESET            rt_pin_write(CS_PIN, PIN_LOW)


void LCD_SetBrightness(uint32_t Brightness)
{
#ifdef LCD_BACKLIGHT_USING_PWM
    Brightness = ((Brightness >= MAX_BRIGHTNESS)?(MAX_BRIGHTNESS-1):Brightness);
    rt_pwm_set(lcd_pwm_dev, LCD_PWM_DEV_CHANNEL, MAX_BRIGHTNESS, Brightness);
    NowBrightness = Brightness;
#else
    rt_pin_mode(LCD_DISP_GPIO_NUM, PIN_MODE_OUTPUT);
    rt_pin_write(LCD_DISP_GPIO_NUM, PIN_LOW);
#endif
}

uint32_t LCD_GetBrightness(void)
{
#ifdef LCD_BACKLIGHT_USING_PWM
    return NowBrightness;
#else
    return 0;
#endif
}

//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode)
{
    uint8_t temp,t1,t;
    uint16_t y0=y;
    uint16_t x0=x;
    uint32_t h,w;

    uint16_t write[size][size==12?6:8];
    uint16_t count;

    ST7735_GetXSize(&st7735_pObj,&w);
    ST7735_GetYSize(&st7735_pObj,&h);

    //设置窗口
    num=num-' ';//得到偏移后的值
    count = 0;

    if(!mode) //非叠加方式
    {
        for(t=0;t<size;t++)
        {
            if(size==12)temp=asc2_1206[num][t];  //调用1206字体
            else temp=asc2_1608[num][t];         //调用1608字体

            for(t1=0;t1<8;t1++)
            {
                if(temp&0x80)
                    write[count][t/2]=(BRUSH_POINT_COLOR&0xFF)<<8|BRUSH_POINT_COLOR>>8;
                else
                    write[count][t/2]=(BRUSH_BACK_COLOR&0xFF)<<8|BRUSH_BACK_COLOR>>8;

                count ++;
                if(count >= size) count =0;

                temp<<=1;
                y++;
                if(y>=h){return;}//超区域了
                if((y-y0)==size)
                {
                    y=y0;
                    x++;
                    if(x>=w){return;}//超区域了
                    break;
                }
            }
        }
    }
    else//叠加方式
    {
        for(t=0;t<size;t++)
        {
            if(size==12)temp=asc2_1206[num][t];  //调用1206字体
            else temp=asc2_1608[num][t];         //调用1608字体
            for(t1=0;t1<8;t1++)
            {
                if(temp&0x80)
                    write[count][t/2]=(BRUSH_POINT_COLOR&0xFF)<<8|BRUSH_POINT_COLOR>>8;
                count ++;
                if(count >= size) count =0;

                temp<<=1;
                y++;
                if(y>=h){return;}//超区域了
                if((y-y0)==size)
                {
                    y=y0;
                    x++;
                    if(x>=w){return;}//超区域了
                    break;
                }
            }
        }
    }
    ST7735_FillRGBRect(&st7735_pObj,x0,y0,(uint8_t *)&write,size==12?6:8,size);
}

//显示字符串
//x,y:起点坐标
//width,height:区域大小
//size:字体大小
//*p:字符串起始地址
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p)
{
    uint8_t x0=x;
    width+=x;
    height+=y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }
}

void LCD_FillRGBRect(uint32_t Xpos, uint32_t Ypos, uint8_t *pData, uint32_t Width, uint32_t Height)
{
    ST7735_LCD_Driver.FillRGBRect(&st7735_pObj, Xpos, Ypos, pData, Width, Height);
}

static int32_t lcd_init(void)
{
    return ST7735_OK;
}

static int32_t lcd_writereg(uint8_t reg,uint8_t* pdata,uint32_t length)
{
    int32_t result;
    LCD_CS_RESET;
    LCD_RS_RESET;
    result = rt_spi_send(spi_dev_lcd, &reg, 1);
    LCD_RS_SET;
    if(length > 0)
        result += rt_spi_send(spi_dev_lcd, pdata, length);
    LCD_CS_SET;
    return ((result == length+1)?0:-1);
}

static int32_t lcd_readreg(uint8_t reg,uint8_t* pdata)
{
    int32_t result;
    LCD_CS_RESET;
    LCD_RS_RESET;

    result = rt_spi_send(spi_dev_lcd, &reg, 1);
    LCD_RS_SET;
    result += rt_spi_recv(spi_dev_lcd, pdata, 1);
    LCD_CS_SET;
    return ((result == 2)?0:-1);
}

static int32_t lcd_senddata(uint8_t* pdata,uint32_t length)
{
    int32_t result;
    LCD_CS_RESET;
    //LCD_RS_SET;
    result =rt_spi_send(spi_dev_lcd, pdata, length);
    LCD_CS_SET;
    return ((result == length)?0:-1);
}

static int32_t lcd_recvdata(uint8_t* pdata,uint32_t length)
{
    int32_t result;
    LCD_CS_RESET;
    //LCD_RS_SET;
    result = rt_spi_recv(spi_dev_lcd, pdata, length);
    LCD_CS_SET;
    return ((result == length)?0:-1);
}

static int LCD_Init(void)
{
    rt_pin_mode(WR_RS_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(CS_PIN, PIN_MODE_OUTPUT);

    spi_dev_lcd = (struct rt_spi_device *)rt_device_find(LCD_SPI_DEVICE_NAME);
    if (!spi_dev_lcd)
    {
        LOG_E("tft-lcd init failed! can't find %s device!\n", LCD_SPI_DEVICE_NAME);
        return -RT_ERROR;
    }

    ST7735_RegisterBusIO(&st7735_pObj,&st7735_pIO);
    if(ST7735_ERROR == ST7735_LCD_Driver.Init(&st7735_pObj,ST7735_FORMAT_RBG565,ST7735_ORIENTATION_LANDSCAPE_ROT180))
    {
        LOG_E("st7735 init failed!");
        // return ;
    }
    ST7735_LCD_Driver.FillRect(&st7735_pObj,0,0,160,80,BLACK);
    ST7735_LCD_Driver.ReadID(&st7735_pObj,&st7735_id);
    ST7735_LCD_Driver.DisplayOn(&st7735_pObj);
    LOG_D("lcd id:0X%08X", st7735_id);
    LOG_D("chip id:0X%08X", HAL_GetDEVID());

#ifdef LCD_BACKLIGHT_USING_PWM
    /* turn on the LCD backlight */
    lcd_pwm_dev = (struct rt_device_pwm *)rt_device_find(LCD_PWM_DEV_NAME);
    if (!lcd_pwm_dev)
    {
        LOG_E("lcd pwm pin init failed! can't find %s device!\n", LCD_SPI_DEVICE_NAME);
        return -RT_ERROR;
    }
    /* pwm frequency:100K = 10000ns */
    rt_pwm_set(lcd_pwm_dev, LCD_PWM_DEV_CHANNEL, LCD_PWM_DEV_TIME, 5000);
    rt_pwm_enable(lcd_pwm_dev, LCD_PWM_DEV_CHANNEL);
#endif
    LCD_SetBrightness(MAX_BRIGHTNESS);

    ST7735_LCD_Driver.DrawBitmap(&st7735_pObj,0,0,WeActStudiologo);
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(LCD_Init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
static int show_logo(int argc, char **argv)
{
    uint8_t text[20];

    LCD_SetBrightness(MAX_BRIGHTNESS);

    ST7735_LCD_Driver.DrawBitmap(&st7735_pObj,0,0,WeActStudiologo);
    rt_thread_mdelay(1000);

    ST7735_LCD_Driver.FillRect(&st7735_pObj,0,0,160,80,BLACK);

    sprintf((char *)&text,"WeAct Studio");
    LCD_ShowString(4,4,160,16,16,text);
    sprintf((char *)&text,"STM32H7xx 0x%X",HAL_GetDEVID());
    LCD_ShowString(4,22,160,16,16,text);
    sprintf((char *)&text,"LCD ID: 0x%X",st7735_id);
    LCD_ShowString(4,40,160,16,16,text);
    return 0;
}
MSH_CMD_EXPORT(show_logo, show logo);
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */

