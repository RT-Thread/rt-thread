/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-06-18     thread-liu        the first version
 */

#include <board.h>

#if defined(BSP_USING_PMIC)

#include <drv_pmic.h>
#include <string.h>

//#define DRV_DEBUG
#define LOG_TAG              "drv.pmic"
#include <drv_log.h>

static struct rt_i2c_bus_device *pmic_dev = RT_NULL;

/* i2c read reg */
static rt_err_t read_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msg[2] = {0, 0};

    RT_ASSERT(bus != RT_NULL);
    
    msg[0].addr  = STPMU1_I2C_ADDRESS;     /* Slave address */
    msg[0].flags = RT_I2C_WR;              /* Write flag */
    msg[0].buf   = &reg;                   /* Slave register address */
    msg[0].len   = 1;                      /* Number of bytes sent */
        
    msg[1].addr  = STPMU1_I2C_ADDRESS;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = len;
    msg[1].buf   = buf;

    if (rt_i2c_transfer(bus, msg, 2) == 2)
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

/* i2c write reg */
static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t data)
{
    rt_uint8_t buf[2];
    struct rt_i2c_msg msgs;

    RT_ASSERT(bus != RT_NULL);
    
    buf[0] = reg; //cmd
    buf[1] = data;

    msgs.addr  = STPMU1_I2C_ADDRESS;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = buf;
    msgs.len   = 2;

    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

/* register direct access */
static rt_err_t stpmu1_read_reg(uint8_t register_id)
{
    rt_err_t status = RT_EOK;
    uint8_t result = 0;

    status = read_reg(pmic_dev, register_id, 1, &result);

    /* Check the communication status */
    if(status != RT_EOK)
    {
        Error_Handler();
    }
    
    return result;
}

static void stpmu1_write_reg(uint8_t register_id, uint8_t value)
{
    uint32_t status = RT_EOK;
    uint8_t readval = 0;
    
    status = write_reg(pmic_dev, register_id, (rt_uint8_t)value);

    /* Check the communication status */
    if(status != RT_EOK)
    {
        Error_Handler();
    }
    /* verify register content */
    if ((register_id != WATCHDOG_CONTROL_REG) && (register_id <= 0x40))
    {
        readval = stpmu1_read_reg(register_id);
        if (readval != value)
        {
            Error_Handler();
        }
    }
}

/** PMIC init  */
static uint32_t BSP_PMIC_MspInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin       = GPIO_PIN_0;
    GPIO_InitStruct.Mode      = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull      = GPIO_PULLUP; 
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = 0 ;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(EXTI0_IRQn, 0x03, 0x00);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    return RT_EOK;
}

static uint32_t BSP_PMIC_MspDeInit(void)
{
    __HAL_RCC_GPIOA_CLK_DISABLE();

    HAL_NVIC_DisableIRQ(EXTI0_IRQn);

    HAL_GPIO_DeInit(GPIOA,GPIO_PIN_0);

    return RT_EOK;
}

uint16_t buck1_voltage_table[] = {
  600,
  625,
  650,
  675,
  700,
  725,
  750,
  775,
  800,
  825,
  850,
  875,
  900,
  925,
  950,
  975,
  1000,
  1025,
  1050,
  1075,
  1100,
  1125,
  1150,
  1175,
  1200,
  1225,
  1250,
  1275,
  1300,
  1325,
  1350,
  1350,// 31  1,35
};

uint16_t buck2_voltage_table[] = {
  1000, // 1
  1000, //
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1050, // 1,05
  1050, // 1,05
  1100, // 1,1
  1100, // 1,1
  1150, // 1,15
  1150, // 1,15
  1200, // 1,2
  1200, // 1,2
  1250, // 1,25
  1250, // 1,25
  1300, // 1,3
  1300, // 1,3
  1350, // 1,35
  1350, // 1,35
  1400, // 1,4
  1400, // 1,4
  1450, // 1,45
  1450, // 1,45
  1500, // 1,5
};

uint16_t buck3_voltage_table[] = {
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1000, // 1
  1100, // 1,1
  1100, // 1,1
  1100, // 1,1
  1100, // 1,1
  1200, // 1,2
  1200, // 1,2
  1200, // 1,2
  1200, // 1,2
  1300, // 1,3
  1300, // 1,3
  1300, // 1,3
  1300, // 1,3
  1400, // 1,4
  1400, // 1,4
  1400, // 1,4
  1400, // 1,4
  1500, // 1,5
  1600, // 1,6
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
  3400, // 3,4
};

uint16_t buck4_voltage_table[] = {
  600,
  625,
  650,
  675,
  700,
  725,
  750,
  775,
  800,
  825,
  850,
  875,
  900,
  925,
  950,
  975,
  1000,
  1025,
  1050,
  1075,
  1100,
  1125,
  1150,
  1175,
  1200,
  1225,
  1250,
  1275,
  1300,
  1300,
  1350,
  1350,// 31  1,35
  1400,// 32  1,40
  1400,// 33  1,40
  1450,// 34  1,45
  1450,// 35  1,45
  1500,// 36  1,5
  1600,// 37  1,6
  1700,// 38  1,7
  1800,// 39  1,8
  1900,// 40  1,9
  2000,// 41  2,0
  2100,// 42  2,1
  2200,// 43  2,2
  2300,// 44  2,3
  2400,// 45  2,4
  2500,// 46  2,5
  2600,// 47  2,6
  2700,// 48  2,7
  2800,// 49  2,8
  2900,// 50  2,9
  3000,// 51  3,0
  3100,// 52  3,1
  3200,// 53  3,2
  3300,// 54  3,3
  3400,// 55  3,4
  3500,// 56  3,5
  3600,// 57  3,6
  3700,// 58  3,7
  3800,// 59  3,8
  3900,// 60  3,9
};

uint16_t ldo1_voltage_table[] = {
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
};

uint16_t ldo2_voltage_table[] = {
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
};

uint16_t ldo3_voltage_table[] = {
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
  3300, // 3,3
  3300, // 3,3
  3300, // 3,3
  3300, // 3,3
  3300, // 3,3
  3300, // 3,3
  0xFFFF, // VREFDDR
};


uint16_t ldo5_voltage_table[] = {
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
  3400, // 3,4
  3500, // 3,5
  3600, // 3,6
  3700, // 3,7
  3800, // 3,8
  3900, // 3,9
};

uint16_t ldo6_voltage_table[] = {
  900, // 0,9
  1000, // 1,0
  1100, // 1,1
  1200, // 1,2
  1300, // 1,3
  1400, // 1,4
  1500, // 1,5
  1600, // 1,6
  1700, // 1,7
  1800, // 1,8
  1900, // 1,9
  2000, // 2
  2100, // 2,1
  2200, // 2,2
  2300, // 2,3
  2400, // 2,4
  2500, // 2,5
  2600, // 2,6
  2700, // 2,7
  2800, // 2,8
  2900, // 2,9
  3000, // 3
  3100, // 3,1
  3200, // 3,2
  3300, // 3,3
};

uint16_t ldo4_voltage_table[] = {
  3300, // 3,3
};

uint16_t vref_ddr_voltage_table[] = {
  3300, // 3,3
};

/*
  Table of Regulators in PMIC SoC
*/
static regul_struct regulators_table[] = {
    {
      .id                 = STPMU1_BUCK1,
      .voltage_table      = buck1_voltage_table,
      .voltage_table_size = ARRAY_SIZE(buck1_voltage_table),
      .control_reg        = BUCK1_CONTROL_REG,
      .low_power_reg      = BUCK1_PWRCTRL_REG,
      .rank               = OTP_RANK_BUCK1,
    },
    {
      .id                 = STPMU1_BUCK2,
      .voltage_table      = buck2_voltage_table,
      .voltage_table_size = ARRAY_SIZE(buck2_voltage_table),
      .control_reg        = BUCK2_CONTROL_REG,
      .low_power_reg      = BUCK2_PWRCTRL_REG,
      .rank               = OTP_RANK_BUCK2,
    },
    {
      .id                 = STPMU1_BUCK3,
      .voltage_table      = buck3_voltage_table,
      .voltage_table_size = ARRAY_SIZE(buck3_voltage_table),
      .control_reg        = BUCK3_CONTROL_REG,
      .low_power_reg      = BUCK3_PWRCTRL_REG,
      .rank               = OTP_RANK_BUCK3,
    },
    {
      .id                 = STPMU1_BUCK4,
      .voltage_table      = buck4_voltage_table,
      .voltage_table_size = ARRAY_SIZE(buck4_voltage_table),
      .control_reg        = BUCK4_CONTROL_REG,
      .low_power_reg      = BUCK4_PWRCTRL_REG,
      .rank               = OTP_RANK_BUCK4,
    },
    {
      .id                 = STPMU1_LDO1,
      .voltage_table      = ldo1_voltage_table,
      .voltage_table_size = ARRAY_SIZE(ldo1_voltage_table),
      .control_reg        = LDO1_CONTROL_REG,
      .low_power_reg      = LDO1_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO1,
    },
    {
      .id                 = STPMU1_LDO2,
      .voltage_table      = ldo2_voltage_table,
      .voltage_table_size = ARRAY_SIZE(ldo2_voltage_table),
      .control_reg        = LDO2_CONTROL_REG,
      .low_power_reg      = LDO2_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO2,
    },
    {
      .id                 = STPMU1_LDO3,
      .voltage_table      = ldo3_voltage_table,
      .voltage_table_size = ARRAY_SIZE(ldo3_voltage_table),
      .control_reg        = LDO3_CONTROL_REG,
      .low_power_reg      = LDO3_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO3,
    },
    {
      .id                 = STPMU1_LDO4,
      .voltage_table      = ldo4_voltage_table,
      .voltage_table_size = ARRAY_SIZE(ldo4_voltage_table),
      .control_reg        = LDO4_CONTROL_REG,
      .low_power_reg      = LDO4_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO4,
    },
    {
      .id                 = STPMU1_LDO5,
      .voltage_table      = ldo5_voltage_table ,
      .voltage_table_size = ARRAY_SIZE(ldo5_voltage_table),
      .control_reg        = LDO5_CONTROL_REG,
      .low_power_reg      = LDO5_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO5,
    },
    {
      .id                 = STPMU1_LDO6,
      .voltage_table      = ldo6_voltage_table ,
      .voltage_table_size = ARRAY_SIZE(ldo6_voltage_table),
      .control_reg        = LDO6_CONTROL_REG,
      .low_power_reg      = LDO6_PWRCTRL_REG,
      .rank               = OTP_RANK_LDO6,
    },
    {
      .id                 = STPMU1_VREFDDR,
      .voltage_table      = vref_ddr_voltage_table ,
      .voltage_table_size = ARRAY_SIZE(vref_ddr_voltage_table),
      .control_reg        = VREF_DDR_CONTROL_REG,
      .low_power_reg      = VREF_DDR_PWRCTRL_REG,
      .rank               = OTP_RANK_VREFDDR,
    },
};

#define MAX_REGUL  ARRAY_SIZE(regulators_table)
static regul_struct *STPMU1_Get_Regulator_Data(PMIC_RegulId_TypeDef id)
{
    uint8_t i;

    for (i = 0 ; i < MAX_REGUL ; i++ )
    {
        if (id == regulators_table[i].id)
        {
            return &regulators_table[i];
        }
    }
    /* id not found */
    Error_Handler();
    return NULL;
}

static uint8_t STPMU1_Voltage_Find_Index(PMIC_RegulId_TypeDef id, uint16_t milivolts)
{
    regul_struct *regul = STPMU1_Get_Regulator_Data(id);
    uint8_t i;
    for ( i = 0 ; i < regul->voltage_table_size ; i++)
    {
        if ( regul->voltage_table[i] == milivolts ) 
        {
          LOG_D("idx:%d for %dmV\n\r", (int)i, (int)milivolts);
          return i;
        }
    }
    /* voltage not found */
    Error_Handler();
    return 0;
}

void STPMU1_Enable_Interrupt(PMIC_IRQn IRQn)
{
    uint8_t irq_reg , irq_reg_value ;

    if (IRQn >= IRQ_NR)
    {
        return ;
    }
    /* IRQ register is IRQ Number divided by 8 */
    irq_reg = IRQn >> 3 ;

    /* value to be set in IRQ register corresponds to BIT(7-N) where N is the Interrupt id modulo 8 */
    irq_reg_value = 1 << ( 7 - ( IRQn%8 ) );

    /* Clear previous event stored in latch */
    stpmu1_write_reg(ITCLEARLATCH1_REG+irq_reg, irq_reg_value );

    /* Clear relevant mask to enable interrupt */
    stpmu1_write_reg(ITCLEARMASK1_REG+irq_reg, irq_reg_value );

}

void STPMU1_Disable_Interrupt(PMIC_IRQn IRQn)
{
    uint8_t irq_reg , irq_reg_value ;

    if (IRQn >= IRQ_NR)
    {
        return ;
    }
    /* IRQ register is IRQ Number divided by 8 */
    irq_reg = IRQn >> 3 ;

    /* value to be set in IRQ register corresponds to BIT(7-N) where N is the Interrupt id modulo 8 */
    irq_reg_value = 1 << ( 7 - ( IRQn%8 ) );

    /* Clear previous event stored in latch */
    stpmu1_write_reg(ITCLEARLATCH1_REG+irq_reg, irq_reg_value );

    /* Set relevant mask to disable interrupt */
    stpmu1_write_reg(ITSETMASK1_REG+irq_reg, irq_reg_value );
}

void BSP_PMIC_INTn_Callback(PMIC_IRQn IRQn)
{
    switch (IRQn)
    {
    case IT_PONKEY_F:
        LOG_I("IT_PONKEY_F");
        break;

    case IT_PONKEY_R:
        LOG_I("IT_PONKEY_R");
        break;

    case IT_WAKEUP_F:
        LOG_I("IT_WAKEUP_F");
        break;

    case IT_WAKEUP_R:
        LOG_I("IT_WAKEUP_R");
        break;

    case IT_VBUS_OTG_F:
        LOG_I("IT_VBUS_OTG_F");
        break;

    case IT_SWOUT_F:
        LOG_I("IT_SWOUT_F");
        break;

    case IT_TWARN_R:
        LOG_I("IT_TWARN_R");
        break;

    case IT_TWARN_F:
        LOG_I("IT_TWARN_F");
        break;

    default:
        LOG_I("%d",IRQn);
        break;
    }
    LOG_I(" Interrupt received\n\r");
}

void STPMU1_INTn_Callback(PMIC_IRQn IRQn) 
{
    BSP_PMIC_INTn_Callback(IRQn);
}

void STPMU1_IrqHandler(void)
{
    uint8_t irq_reg,mask,latch_events,i;

    for (irq_reg = 0 ; irq_reg < STM32_PMIC_NUM_IRQ_REGS ; irq_reg++)
    {
        /* Get latch events & active mask from register */
        mask = stpmu1_read_reg(ITMASK1_REG+irq_reg);
        latch_events = stpmu1_read_reg(ITLATCH1_REG+irq_reg) & ~mask ;

        /* Go through all bits for each register */
        for (i = 0 ; i < 8 ; i++ )
        {
            if ( latch_events & ( 1 << i ) )
            {
                /* Callback with parameter computes as "PMIC Interrupt" enum */
                STPMU1_INTn_Callback( (PMIC_IRQn )(irq_reg*8 + (7-i)));
            }
        }
        /* Clear events in appropriate register for the event with mask set */
        stpmu1_write_reg(ITCLEARLATCH1_REG+irq_reg, latch_events );
    }
}

static void STPMU1_Register_Update(uint8_t register_id, uint8_t value, uint8_t mask)
{
    uint8_t initial_value ;

    initial_value = stpmu1_read_reg(register_id);

    /* Clear bits to update */
    initial_value &= ~mask;

    /* Update appropriate bits*/
    initial_value |= ( value & mask );

    /* Send new value on I2C Bus */
    stpmu1_write_reg(register_id, initial_value);
}

static void STPMU1_Regulator_Enable(PMIC_RegulId_TypeDef id)
{
    regul_struct *regul = STPMU1_Get_Regulator_Data(id);

    STPMU1_Register_Update(regul->control_reg,BIT(0),BIT(0));
}

static void STPMU1_Regulator_Voltage_Set(PMIC_RegulId_TypeDef id,uint16_t milivolts)
{
    uint8_t voltage_index = STPMU1_Voltage_Find_Index(id,milivolts);
    regul_struct *regul = STPMU1_Get_Regulator_Data(id);
    STPMU1_Register_Update(regul->control_reg, voltage_index<<2 , 0xFC );
}

void BSP_PMIC_INTn_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);

    STPMU1_IrqHandler();
}

static rt_err_t rt_hw_pmic_init_register(void)
{
    stpmu1_write_reg(MAIN_CONTROL_REG, 0x04);
    stpmu1_write_reg(VIN_CONTROL_REG, 0xc0);
    stpmu1_write_reg(USB_CONTROL_REG, 0x30);

    stpmu1_write_reg(MASK_RESET_BUCK_REG, 0x04);
    stpmu1_write_reg(MASK_RESET_LDO_REG, 0x00);
    stpmu1_write_reg(MASK_RANK_BUCK_REG, 0x00);
    stpmu1_write_reg(MASK_RANK_LDO_REG, 0x00);
    stpmu1_write_reg(BUCK_PULL_DOWN_REG, 0x00);
    stpmu1_write_reg(LDO14_PULL_DOWN_REG, 0x00);
    stpmu1_write_reg(LDO56_PULL_DOWN_REG, 0x00);
    stpmu1_write_reg(BUCK_ICC_TURNOFF_REG, 0x30);
    stpmu1_write_reg(LDO_ICC_TURNOFF_REG, 0x3b);

  /* vddcore */
  STPMU1_Regulator_Voltage_Set(STPMU1_BUCK1, 1200);
  STPMU1_Regulator_Enable(STPMU1_BUCK1);

  /* vddddr */
  STPMU1_Regulator_Voltage_Set(STPMU1_BUCK2, 1350);
  STPMU1_Regulator_Enable(STPMU1_BUCK2);

  /* vdd */
  STPMU1_Regulator_Voltage_Set(STPMU1_BUCK3, 3300);
  STPMU1_Regulator_Enable(STPMU1_BUCK3);

  /* 3v3 */
  STPMU1_Regulator_Voltage_Set(STPMU1_BUCK4, 3300);
  STPMU1_Regulator_Enable(STPMU1_BUCK4);

  /* vdda */
  STPMU1_Regulator_Voltage_Set(STPMU1_LDO1, 2900);
  STPMU1_Regulator_Enable(STPMU1_LDO1);

  /* 2v8 */
  STPMU1_Regulator_Voltage_Set(STPMU1_LDO2, 2800);
  STPMU1_Regulator_Enable(STPMU1_LDO2);

  /* vtt_ddr  lod3 mode buck2/2 */
  STPMU1_Regulator_Voltage_Set(STPMU1_LDO3, 0xFFFF);
  STPMU1_Regulator_Enable(STPMU1_LDO3);

  /* vdd_usb */
  STPMU1_Regulator_Voltage_Set(STPMU1_LDO4, 3300);
  STPMU1_Regulator_Enable(STPMU1_LDO4);

  /* vdd_sd */
  STPMU1_Regulator_Voltage_Set(STPMU1_LDO5, 2900);
  STPMU1_Regulator_Enable(STPMU1_LDO5);

  /* 1v8 */
  STPMU1_Regulator_Voltage_Set(STPMU1_LDO6, 1800);
  STPMU1_Regulator_Enable(STPMU1_LDO6);

  STPMU1_Regulator_Enable(STPMU1_VREFDDR);

    return RT_EOK;
}

static rt_err_t rt_hw_pmic_init(const char *bus_name)
{
    PMIC_IRQn irq;
    
    pmic_dev = rt_i2c_bus_device_find(bus_name);
    
    if (pmic_dev == RT_NULL)
    {
        LOG_E("%s bus not found\n", bus_name);
        return -RT_ERROR;
    }
    
    if (stpmu1_read_reg(VERSION_STATUS_REG) != PMIC_VERSION_ID)
    {
        return -RT_EIO;
    }

    STPMU1_Enable_Interrupt(IT_PONKEY_R);
    STPMU1_Enable_Interrupt(IT_PONKEY_F);
    /* enable all irqs  */
    for (irq = IT_SWOUT_R; irq < IRQ_NR; irq++) 
    {
        STPMU1_Enable_Interrupt(irq);
    }

    return RT_EOK;
}

static rt_err_t rt_hw_pmic_deinit(void)
{
    BSP_PMIC_MspDeInit();
    
    return RT_EOK;
}

static int pmic_init(void)
{
    rt_err_t result = RT_EOK;
    
    if (IS_ENGINEERING_BOOT_MODE())
    {
        BSP_PMIC_MspInit();
        
        result = rt_hw_pmic_init("i2c3");
        if(result != RT_EOK)
        {
            LOG_D("stpmic init failed: %02x", result);
            rt_hw_pmic_deinit();
            return RT_ERROR;
        }
        
        rt_hw_pmic_init_register();
    }
    
    LOG_I("stpmic init success!");
        
    return RT_EOK;
}

INIT_PREV_EXPORT(pmic_init);

#endif
