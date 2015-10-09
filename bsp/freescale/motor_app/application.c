/*
 * File      : application.c
 * Change Logs:
 * Date           Author       Notes
 *
 */

/**
 * @addtogroup kinetis
 */
/*@{*/

#include <stdio.h>
#include "fsl_debug_console.h"

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "fsl_os_abstraction.h"
#include "fsl_i2c_hal.h"
#include "fsl_i2c_master_driver.h"
#include "fsl_clock_manager.h"

#include "fsl_device_registers.h"
#include "fsl_ftm_driver.h"
#include "mpu6050.h"

#include "app_config.h"

#include "inv_mpu.h"
#include "mltypes.h"


#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#include "stm32_eth.h"
#endif

extern long list_thread(void);

void rt_init_thread_entry(void* parameter)
{
    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);

        /* register ethernetif device */
        eth_system_device_init();

        rt_hw_stm32_eth_init();
        /* re-init device driver */
        rt_device_init_all();

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif

//FS

//GUI

}

ALIGN(RT_ALIGN_SIZE)
static char thread_demo_stack[1024];
static char thread_sensor_stack[1024];
static struct rt_thread demo;
static struct rt_thread sensor;
static rt_thread_t init_thread;
static int speed = 50; //duty cycle repense the speed
static int motor;
static uint32_t freq=24000u;

static ftm_pwm_param_t ftmParam = {
        .mode                   = kFtmEdgeAlignedPWM,
        .edgeMode               = kFtmHighTrue,
        .uFrequencyHZ           = 24000u,
        .uDutyCyclePercent      = 50,
        .uFirstEdgeDelayPercent = 0,
    };

static int16_t map_range( int16_t in, int32_t min, int32_t max)
{
  int16_t temp = in;
  return temp;
  //return (int16_t)(temp * (max - min) / (1<<16) + min);
}

static long getacc()
{
   uint8_t acc_range = mpu6050_getFullScaleAccelRange();
   int16_t x = 0, y = 0, z = 0;
   int16_t imin = ga_accrange[acc_range][0];
   int16_t imax = ga_accrange[acc_range][1];
   mpu6050_getAcc(&x, &y, &z);
   rt_kprintf("\r\n x = %d g\r\n", map_range(x, imin, imax));
   rt_kprintf("\r y = %d g\r\n", map_range(y, imin, imax));
   rt_kprintf("\r z = %d g\r\n", map_range(z, imin, imax));
   return 0;
}

static long gettemp()
{
   int16_t temp = mpu6050_getTemperature();
   rt_kprintf("\r\n temp = %d \r\n", temp);
   return 0;
}

static long getrotation()
{
   uint8_t gyro_range = mpu6050_getFullScaleGyroRange();
   int16_t x = 0, y = 0, z = 0;
   int16_t imin = ga_gyrorange[gyro_range][0];
   int16_t imax = ga_gyrorange[gyro_range][1];
   mpu6050_getRotation(&x, &y, &z);
   rt_kprintf("\r\n x = %d \r\n", map_range(x, imin, imax));
   rt_kprintf("\r y = %d \r\n", map_range(y, imin, imax));
   rt_kprintf("\r z = %d \r\n", map_range(z, imin, imax)); 
   return 0;
}

static long speedup()
{
  uint32_t instance;
  uint8_t ch;

  if (motor > MOTOR_NUM - 1)
  {
    motor = 0;
    return 1;
  }
  speed += 10;
  ftmParam.uFrequencyHZ = freq;
  ftmParam.uDutyCyclePercent = speed > 100? 100:speed;
  
  instance  = motor_demo_config[motor].instance;
  ch = motor_demo_config[motor].channel;
  
  // Start PWM mode with updated duty cycle.
  FTM_DRV_PwmStart(instance, &ftmParam, ch);
  FTM_HAL_SetMaxLoadingCmd(g_ftmBase[instance], true);
  // Software trigger to update registers.
  FTM_HAL_SetSoftwareTriggerCmd(g_ftmBase[instance], true);
  return 0;
}

static long speeddown()
{
  uint32_t instance;
  uint8_t ch;

  if (motor > MOTOR_NUM - 1)
  {
    motor = 0;
    return 1;
  }
  speed -= 10;
  ftmParam.uDutyCyclePercent = speed > 0? speed:0;
  
  instance  = motor_demo_config[motor].instance;
  ch = motor_demo_config[motor].channel;
  ftmParam.uFrequencyHZ = freq;
  
  // Start PWM mode with updated duty cycle.
  FTM_DRV_PwmStart(instance, &ftmParam, ch);
  FTM_HAL_SetMaxLoadingCmd(g_ftmBase[instance], true);
  // Software trigger to update registers.
  FTM_HAL_SetSoftwareTriggerCmd(g_ftmBase[instance], true);
  return 0;
}

static void rt_thread_sensor(void * parameter)
{
    uint32_t baudRate_kbps = 200;   // 400 Kbps
    uint32_t i2cClockFreq;
    I2C_Type * baseAddr = g_i2cBase[MPU6050_I2C_INSTANCE];
    // Initialize OSA
    OSA_Init();
    /* Enable clock for I2C.*/
    CLOCK_SYS_EnableI2cClock(MPU6050_I2C_INSTANCE);
    
      /* Initialize peripheral to known state.*/
    I2C_HAL_Init(baseAddr);

    /* Enable module.*/
    I2C_HAL_Enable(baseAddr);

    /* Get the current bus clock.*/
    i2cClockFreq = CLOCK_SYS_GetI2cFreq(MPU6050_I2C_INSTANCE);

    I2C_HAL_SetBaudRate(baseAddr, i2cClockFreq, baudRate_kbps, NULL);
    
    rt_thread_delay(RT_TICK_PER_SECOND*5);
    
    gpio_init(motor_gpio);
    
#if 0    
    mpu6050_init(MPU6050_I2C_INSTANCE);
    
    if (!mpu6050_testConnection())
    {
       rt_kprintf("\r\n mpu6050 init failed!!!\r\n");
    } else {
       rt_kprintf("\r\n mpu6050 init success!!!\r\n");
    }
    
    finsh_syscall_append("getacc", getacc);
    finsh_syscall_append("gettemp", gettemp);
    finsh_syscall_append("getrotation", getrotation);
    
    mpu_6050_setTempSensorEnabled(true);
#else
    mpl_function();
    
#endif    

    LED2_EN;
    while (1)
    {      
       LED2_TOGGLE;
       rt_thread_delay(RT_TICK_PER_SECOND*5);
    }
}

    
static void rt_thread_motor_demo(void* parameter)
{
    int i = 0;
    ftm_user_config_t driver_info;
    driver_info.syncMethod = kFtmUseSoftwareTrig;
    /* start the pwm first*/
    for (i = 0; i < MOTOR_NUM ; i++)
    {
       if (motor_demo_config[i].need_init)
       {
         FTM_DRV_Init(motor_demo_config[i].instance, &driver_info);
         FTM_DRV_SetClock(motor_demo_config[i].instance, kClock_source_FTM_SystemClk, kFtmDividedBy1);
       }
       FTM_DRV_PwmStart(motor_demo_config[i].instance, &ftmParam, motor_demo_config[i].channel);
       FTM_HAL_SetSoftwareTriggerCmd(g_ftmBase[motor_demo_config[i].instance], true);
    }

#ifdef RT_USING_FINSH    
    finsh_syscall_append("speedup", speedup);
    finsh_sysvar_append("speed", finsh_type_int, &speed);
    finsh_sysvar_append("activeMotor", finsh_type_int, &motor);
    finsh_sysvar_append("freq", finsh_type_int, &freq);
    finsh_syscall_append("speeddown", speeddown);
#endif    
    
    LED1_EN;
    while (1)
    {      
       LED1_TOGGLE;
       rt_thread_delay(RT_TICK_PER_SECOND*5);
    }
    /*no here*/
#if 0
    for (i = 0; i < MOTOR_NUM ; i++)
    {
       if (motor_demo_config[i].need_init)
       {
         FTM_DRV_Deinit(motor_demo_config[i].instance);
       }
    }
#endif
}

static long reset()
{
   NVIC_SystemReset();
  return 0;
}

int rt_application_init()
{
  int i;
  for (i = 0; i < PORT_INSTANCE_COUNT; i++)
  {
    CLOCK_SYS_EnablePortClock(i);
  }

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 80, 20);
#endif
    configure_ftm_pins(0);//FTM0
    configure_ftm_pins(2);//FTM2
    configure_i2c_pins(MPU6050_I2C_INSTANCE);

#ifdef RT_USING_FINSH
    finsh_syscall_append("reset", reset);
#endif

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

    //------- init demo thread
    rt_thread_init(&demo,
                   "demo",
                   rt_thread_motor_demo,
                   RT_NULL,
                   &thread_demo_stack[0],
                   sizeof(thread_demo_stack),6,5);
    rt_thread_startup(&demo);
        //------- init demo thread
    rt_thread_init(&sensor,
                   "sensor",
                   rt_thread_sensor,
                   RT_NULL,
                   &thread_sensor_stack[0],
                   sizeof(thread_sensor_stack),20,5);
    rt_thread_startup(&sensor);
    return 0;
}

/*@}*/
