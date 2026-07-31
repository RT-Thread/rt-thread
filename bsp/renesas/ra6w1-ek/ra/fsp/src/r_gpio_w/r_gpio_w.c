/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "r_gpio_w.h"
#if BSP_MCU_GROUP_RA6W1
 #if CFG_PMGR
  #include "rm_pmgr_w_instance.h"
 #endif
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
 #define GPIO_PD                         BSP_PD_COM
#elif BSP_MCU_GROUP_RA6W3
 #define GPIO_PD                         BSP_PD_SYS
#endif

/* "PORT" in ASCII, used to determine if the module is open */
#define GPIO_W_OPEN                      (0x504F5254U)
#define GPIO_W_CLOSED                    (0x00000000U)
#if !defined(BSP_MCU_GROUP_RA6W1)
 #define GPIO_W_CLK_SEL_REG_FUNC_MASK    (0xF)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_gpio_w_pins_config(gpio_w_instance_ctrl_t * p_ctrl, const ioport_cfg_t * p_cfg);
static void r_gpio_w_pin_config(gpio_w_instance_ctrl_t * p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg);

#if defined(BSP_MCU_GROUP_RA6W1)
bool r_gpio_w_retained_io_set(bsp_io_port_pin_t pin);

 #if CFG_PMGR
static fsp_err_t r_gpio_w_enter_sleep(ioport_ctrl_t * p_ctrl);
static fsp_err_t r_gpio_w_wakeup(ioport_ctrl_t * p_ctrl);
static void      r_gpio_w_pmgr_callback(pmgr_callback_args_t * p_args);
static fsp_err_t r_gpio_w_subscribe_for_pmgr_notifications(ioport_ctrl_t * const p_ctrl);
static fsp_err_t r_gpio_w_unsubscribe_from_pmgr_notifications(void);

 #endif
#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* GPIO_W Implementation of IOPort Driver  */
const ioport_api_t g_ioport_on_gpio_w =
{
    .open                 = R_GPIO_W_Open,
    .close                = R_GPIO_W_Close,
    .pinsCfg              = R_GPIO_W_PinsCfg,
    .pinCfg               = R_GPIO_W_PinCfg,
    .pinEventInputRead    = R_GPIO_W_PinEventInputRead,
    .pinEventOutputWrite  = R_GPIO_W_PinEventOutputWrite,
    .pinRead              = R_GPIO_W_PinRead,
    .pinWrite             = R_GPIO_W_PinWrite,
    .portDirectionSet     = R_GPIO_W_PortDirectionSet,
    .portEventInputRead   = R_GPIO_W_PortEventInputRead,
    .portEventOutputWrite = R_GPIO_W_PortEventOutputWrite,
    .portRead             = R_GPIO_W_PortRead,
    .portWrite            = R_GPIO_W_PortWrite,
};

#if CFG_PMGR
static pmgr_instance_info_t g_r_gpio_w_pmgr_info =
{
    .power_mode  = PMGR_LLD_POWER_MODE_SLEEP4,
    .wake_source = PMGR_WAKE_SOURCE_NONE,
};

static pmgr_callback_args_t g_r_gpio_w_pmgr_args =
{
    .constraints     = PMGR_CONSTRAINT_NONE,
    .event           = PMGR_EVENT_NOT_SET,
    .p_context       = NULL,
    .p_instance_info = &g_r_gpio_w_pmgr_info,
};

static pmgr_w_notifier_extend_t g_r_gpio_w_pmgr_notifier_extend =
{
    .order = PMGR_W_NOTIFIER_ORDER_HIGHEST,
};

static uint32_t gpio_w_sel[BSP_FEATURE_IO_PORT_COUNT];
static uint32_t gpio_w_sel1[BSP_FEATURE_IO_PORT_COUNT];
static uint32_t gpio_w_pol[BSP_FEATURE_IO_PORT_COUNT];
#endif                                 // #if CFG_PMGR

/*******************************************************************************************************************//**
 * @addtogroup GPIO_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes internal driver data, then calls pin configuration function to configure pins.
 *
 * @retval FSP_SUCCESS                  Pin configuration data written to MODE, Set port pins and Reset port pins register(s)
 * @retval FSP_ERR_ASSERTION            NULL pointer
 * @retval FSP_ERR_ALREADY_OPEN         Module is already open.
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_Open (ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg)
{
    gpio_w_instance_ctrl_t * p_instance_ctrl = (gpio_w_instance_ctrl_t *) p_ctrl;
#if defined(BSP_MCU_GROUP_RA6W1)
 #if CFG_PMGR
    bool is_sleep3_wakeup;
 #endif
#endif

#if (1 == GPIO_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_pin_cfg_data || 0 == p_cfg->number_of_pins);
    FSP_ERROR_RETURN(GPIO_W_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
 #if !BSP_MCU_GROUP_RA6W1 && !BSP_MCU_GROUP_RA6B2 // TIN-TODO
    FSP_ERROR_RETURN(bsp_pd_is_up_check(GPIO_PD), FSP_ERR_INVALID_HW_CONDITION);
 #endif
#endif

    /* Set driver status to open */
    p_instance_ctrl->open = GPIO_W_OPEN;

    /* Init P0 reg addresses. The regs for other ports are right after P0's regs. */
    p_instance_ctrl->p_reg_p0_data       = &GPIO->P0_DATA_REG;
    p_instance_ctrl->p_reg_p0_set_data   = &GPIO->P0_SET_DATA_REG;
    p_instance_ctrl->p_reg_p0_reset_data = &GPIO->P0_RESET_DATA_REG;
    p_instance_ctrl->p_reg_p0_00_mode    = &GPIO->P0_00_MODE_REG;

#if defined(BSP_MCU_GROUP_RA6W1)
 #if CFG_PMGR
    r_gpio_w_subscribe_for_pmgr_notifications(p_ctrl);
    is_sleep3_wakeup = RM_PMGR_W_IsSleep3Wakeup();

    if (is_sleep3_wakeup)
    {
        R_BSP_RetainedIoRecovery(false);
    }
    else
 #endif

    {
        R_BSP_RetainedIoClear();
        r_gpio_w_pins_config(p_instance_ctrl, p_cfg);
    }

#else
    r_gpio_w_pins_config(p_instance_ctrl, p_cfg);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets GPIO_W registers. Implements @ref ioport_api_t::close
 *
 * @retval FSP_SUCCESS             The GPIO_W was successfully uninitialized
 * @retval FSP_ERR_ASSERTION       p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_Close (ioport_ctrl_t * const p_ctrl)
{
    gpio_w_instance_ctrl_t * p_instance_ctrl = (gpio_w_instance_ctrl_t *) p_ctrl;
#if defined(BSP_MCU_GROUP_RA6W1)
 #if CFG_PMGR
    r_gpio_w_unsubscribe_from_pmgr_notifications();
 #endif
#endif
#if (1 == GPIO_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPIO_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set state to closed */
    p_instance_ctrl->open = GPIO_W_CLOSED;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the functions of multiple pins by loading configuration data into pin MODE,Set port pins and Reset port pins registers.
 * Implements @ref ioport_api_t::pinsCfg.
 *
 * This function initializes the supplied list of MODE, Set port pins and Reset port pins registers with the supplied values. This data can be generated
 * by the Pins tab of the RAFW Configuration editor or manually by the developer. Different pin configurations can be
 * loaded for different situations such as low power modes and testing.
 *
 * @retval FSP_SUCCESS             Pin configuration data written to MODE,Set port pins and Reset port pins register(s)
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 * @retval FSP_ERR_ASSERTION       NULL pointer
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PinsCfg (ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg)
{
    gpio_w_instance_ctrl_t * p_instance_ctrl = (gpio_w_instance_ctrl_t *) p_ctrl;

#if (1 == GPIO_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPIO_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_pin_cfg_data);
#endif

    r_gpio_w_pins_config(p_instance_ctrl, p_cfg);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the settings of a pin. Implements @ref ioport_api_t::pinCfg.
 *
 * @retval FSP_SUCCESS             Pin configured
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 * @retval FSP_ERR_ASSERTION       NULL pointer
 *
 * @note This function is re-entrant for different pins.
 * This function will change the configuration of the pin with the new configuration. For example it is not possible
 * with this function to change the drive strength of a pin while leaving all the other pin settings unchanged. To
 * achieve this the original settings with the required change will need to be written using this function.
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PinCfg (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg)
{
    gpio_w_instance_ctrl_t * p_instance_ctrl = (gpio_w_instance_ctrl_t *) p_ctrl;

#if (1 == GPIO_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPIO_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    R_BSP_PinAccessEnable();

    r_gpio_w_pin_config(p_instance_ctrl, pin, cfg);

    R_BSP_PinAccessDisable();

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the level on a pin. Implements @ref ioport_api_t::pinRead.
 *
 * @retval FSP_SUCCESS             Pin read
 * @retval FSP_ERR_ASSERTION       NULL pointer
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 * @note This function is re-entrant for different pins.
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PinRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value)
{
#if (1 == GPIO_W_CFG_PARAM_CHECKING_ENABLE)
    gpio_w_instance_ctrl_t * p_instance_ctrl = (gpio_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPIO_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_pin_value);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    *p_pin_value = (bsp_io_level_t) R_BSP_PinRead(pin);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the value on an IO port. Implements @ref ioport_api_t::portRead.
 *
 * The specified port will be read, and the levels for all the pins will be returned.
 * Each bit in the returned value corresponds to a pin on the port. For example, bit 7 corresponds
 * to pin 7, bit 6 to pin 6, and so on.
 *
 * @retval FSP_SUCCESS             Port read
 * @retval FSP_ERR_ASSERTION       NULL pointer
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 * @note This function is re-entrant for different ports.
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PortRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_port_value)
{
    gpio_w_instance_ctrl_t * p_instance_ctrl = (gpio_w_instance_ctrl_t *) p_ctrl;

#if (1 == GPIO_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPIO_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_port_value);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    *p_port_value = (ioport_size_t) *(p_instance_ctrl->p_reg_p0_data + port);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes to multiple pins on a port. Implements @ref ioport_api_t::portWrite.
 *
 * The input value will be written to the specified port. Each bit in the value parameter corresponds to a bit
 * on the port. For example, bit 7 corresponds to pin 7, bit 6 to pin 6, and so on.
 * Each bit in the mask parameter corresponds to a pin on the port.
 *
 * Only the bits with the corresponding bit in the mask value set will be updated.
 * For example, value = 0xFFFF, mask = 0x0003 results in only bits 0 and 1 being updated.
 *
 * @retval FSP_SUCCESS                  Port written to
 * @retval FSP_ERR_INVALID_ARGUMENT     The port and/or mask not valid
 * @retval FSP_ERR_NOT_OPEN             The module has not been opened
 * @retval FSP_ERR_ASSERTION            NULL pointerd
 *
 * @note This function is re-entrant for different ports. This function makes use of the Set port pins and Reset port pins registers to atomically
 * modify the levels on the specified pins on a port.
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PortWrite (ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t value, ioport_size_t mask)
{
    gpio_w_instance_ctrl_t * p_instance_ctrl = (gpio_w_instance_ctrl_t *) p_ctrl;

#if (1 == GPIO_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPIO_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(mask > (ioport_size_t) 0, FSP_ERR_INVALID_ARGUMENT);
#endif

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    *(p_instance_ctrl->p_reg_p0_set_data + port)   = value & mask;
    *(p_instance_ctrl->p_reg_p0_reset_data + port) = (ioport_size_t) (~value) & mask;

    FSP_CRITICAL_SECTION_EXIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets a pin's output either high or low. Implements @ref ioport_api_t::pinWrite.
 *
 * @retval FSP_SUCCESS                  Pin written to
 * @retval FSP_ERR_INVALID_ARGUMENT     The pin and/or level not valid
 * @retval FSP_ERR_NOT_OPEN             The module has not been opene
 * @retval FSP_ERR_ASSERTION            NULL pointerd
 *
 * @note This function is re-entrant for different pins. This function makes use of the Set port pins and Reset port pins registers to atomically
 * modify the level on the specified pin on a port.
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PinWrite (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t level)
{
    gpio_w_instance_ctrl_t * p_instance_ctrl = (gpio_w_instance_ctrl_t *) p_ctrl;

#if (1 == GPIO_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPIO_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(level <= BSP_IO_LEVEL_HIGH, FSP_ERR_INVALID_ARGUMENT);
#elif defined(BSP_MCU_GROUP_RA6W1)
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

#if !defined(BSP_MCU_GROUP_RA6W1)
    bsp_io_port_t port = (bsp_io_port_t) ((BSP_IO_PORT_BITS & (uint16_t) pin) >> BSP_IO_PORT_OFFSET);

    uint32_t gpio_id = BSP_IO_PIN_BITS & (uint16_t) pin;

    if (BSP_IO_LEVEL_HIGH == level)
    {
        *(p_instance_ctrl->p_reg_p0_set_data + port) = 1 << gpio_id;
    }
    else
    {
        *(p_instance_ctrl->p_reg_p0_reset_data + port) = 1 << gpio_id;
    }

#else
    R_BSP_PinWrite(pin, level);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets the direction of individual pins on a port. Implements @ref ioport_api_t::portDirectionSet().
 *
 * Multiple pins on a port can be set to inputs or outputs at once.
 * Each bit in the mask parameter corresponds to a pin on the port. For example, bit 7 corresponds to
 * pin 7, bit 6 to pin 6, and so on. If a bit is set to 1 then the corresponding pin will be changed to
 * an input or an output as specified by the direction values. If a mask bit is set to 0 then the direction of
 * the pin will not be changed.
 *
 * @retval FSP_SUCCESS                 Port direction updated
 * @retval FSP_ERR_INVALID_ARGUMENT    The port and/or mask not valid
 * @retval FSP_ERR_NOT_OPEN            The module has not been opened
 * @retval FSP_ERR_ASSERTION           NULL pointer
 *
 * @note This function is re-entrant for different ports.
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PortDirectionSet (ioport_ctrl_t * const p_ctrl,
                                     bsp_io_port_t         port,
                                     ioport_size_t         direction_values,
                                     ioport_size_t         mask)
{
    gpio_w_instance_ctrl_t * p_instance_ctrl = (gpio_w_instance_ctrl_t *) p_ctrl;

#if (1 == GPIO_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPIO_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(mask > (ioport_size_t) 0, FSP_ERR_INVALID_ARGUMENT);
#endif

    volatile uint32_t * mode_reg;
    uint16_t            port_gpio_count;

    if (BSP_IO_PORT_00 == port)
    {
        port_gpio_count = BSP_FEATURE_IO_PORT0_GPIO_COUNT;
        mode_reg        = p_instance_ctrl->p_reg_p0_00_mode;
    }
    else if (BSP_IO_PORT_01 == port)
    {
        port_gpio_count = BSP_FEATURE_IO_PORT1_GPIO_COUNT;
        mode_reg        = p_instance_ctrl->p_reg_p0_00_mode + BSP_FEATURE_IO_PORT0_GPIO_COUNT;
    }
    else                               /* Port 2 */
    {
        port_gpio_count = BSP_FEATURE_IO_PORT2_GPIO_COUNT;
        mode_reg        = p_instance_ctrl->p_reg_p0_00_mode + BSP_FEATURE_IO_PORT0_GPIO_COUNT +
                          BSP_FEATURE_IO_PORT1_GPIO_COUNT;
    }

    for (uint16_t gpio = 0U; gpio < port_gpio_count; gpio++, mode_reg++)
    {
        if (mask & (1U << gpio))
        {
            if (0 != ((direction_values >> gpio) & 1))
            {
                *mode_reg = ((*mode_reg) & ~GPIO_P0_00_MODE_REG_PUPD_Msk) | GPIO_W_CFG_PORT_DIRECTION_OUTPUT;
            }
            else
            {
                *mode_reg = ((*mode_reg) & ~GPIO_P0_00_MODE_REG_PUPD_Msk) | GPIO_W_CFG_PORT_DIRECTION_INPUT;
            }
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the value of the event input data. Implements @ref ioport_api_t::portEventInputRead().
 *
 * The event input data for the port will be read. Each bit in the returned value corresponds to a pin on the port.
 * For example, bit 7 corresponds to pin 7, bit 6 to pin 6, and so on.
 *
 * The port event data is captured in response to a trigger from the ELC. This function enables this data to be read.
 * Using the event system allows the captured data to be stored when it occurs and then read back at a later time.
 *
 * @retval FSP_SUCCESS              Port read
 * @retval FSP_ERR_INVALID_ARGUMENT Port not a valid ELC port
 * @retval FSP_ERR_ASSERTION        NULL pointer
 * @retval FSP_ERR_NOT_OPEN         The module has not been opened
 * @retval FSP_ERR_UNSUPPORTED      Function not supported.
 *
 * @note This function is re-entrant for different ports.
 *
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PortEventInputRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_event_data)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(port);
    FSP_PARAMETER_NOT_USED(p_event_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Reads the value of the event input data of a specific pin. Implements @ref ioport_api_t::pinEventInputRead.
 *
 * The pin event data is captured in response to a trigger from the ELC. This function enables this data to be read.
 * Using the event system allows the captured data to be stored when it occurs and then read back at a later time.
 *
 * @retval FSP_SUCCESS                  Pin read
 * @retval FSP_ERR_ASSERTION            NULL pointer
 * @retval FSP_ERR_NOT_OPEN             The module has not been opened
 * @retval FSP_ERR_INVALID_ARGUMENT     Port is not valid ELC PORT.
 * @retval FSP_ERR_UNSUPPORTED          Function not supported.
 *
 * @note This function is re-entrant.
 *
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PinEventInputRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_event)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(pin);
    FSP_PARAMETER_NOT_USED(p_pin_event);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * This function writes the set and reset event output data for a port. Implements
 * @ref ioport_api_t::portEventOutputWrite.
 *
 * Using the event system enables a port state to be stored by this function in advance of being output on the port.
 * The output to the port will occur when the ELC event occurs.
 *
 * The input value will be written to the specified port when an ELC event configured for that port occurs.
 * Each bit in the value parameter corresponds to a bit on the port. For example, bit 7 corresponds to pin 7,
 * bit 6 to pin 6, and so on. Each bit in the mask parameter corresponds to a pin on the port.
 *
 * @retval FSP_SUCCESS                Port event data written
 * @retval FSP_ERR_INVALID_ARGUMENT   Port or Mask not valid
 * @retval FSP_ERR_NOT_OPEN           The module has not been opened
 * @retval FSP_ERR_ASSERTION          NULL pointer
 *
 * @note This function is re-entrant for different ports.
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PortEventOutputWrite (ioport_ctrl_t * const p_ctrl,
                                         bsp_io_port_t         port,
                                         ioport_size_t         event_data,
                                         ioport_size_t         mask_value)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(port);
    FSP_PARAMETER_NOT_USED(event_data);
    FSP_PARAMETER_NOT_USED(mask_value);

    return FSP_ERR_UNSUPPORTED;
}

/**********************************************************************************************************************//**
 * This function writes the event output data value to a pin. Implements @ref ioport_api_t::pinEventOutputWrite.
 *
 * Using the event system enables a pin state to be stored by this function in advance of being output on the pin.
 * The output to the pin will occur when the ELC event occurs.
 *
 * @retval FSP_SUCCESS               Pin event data written
 * @retval FSP_ERR_INVALID_ARGUMENT  Port or Pin or value not valid
 * @retval FSP_ERR_NOT_OPEN          The module has not been opened
 * @retval FSP_ERR_ASSERTION         NULL pointer
 *
 * @note This function is re-entrant for different ports.
 *
 **********************************************************************************************************************/
fsp_err_t R_GPIO_W_PinEventOutputWrite (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t pin_value)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(pin);
    FSP_PARAMETER_NOT_USED(pin_value);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup GPIO_W)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures gpios with cfg setting. It calls r_gpio_w_pin_config internally repeatedly
 * to have required gpios configured one by one
 *
 * @param[in]    p_ctrl         Instance ctrl
 * @param[in]    p_cfg          Pin configuration data
 **********************************************************************************************************************/
static void r_gpio_w_pins_config (gpio_w_instance_ctrl_t * p_ctrl, const ioport_cfg_t * p_cfg)
{
    uint16_t pin_count;
#if !defined(BSP_MCU_GROUP_RA6W1)
    const gpio_w_extended_cfg_t * gpio_w_extend_struct = p_cfg->p_extend;

    if (NULL != gpio_w_extend_struct)
    {
 #if defined GPIO_P2_1P8_MODE_REG_P2_00_1P8_MODE_Msk
        GPIO->P2_1P8_MODE_REG = gpio_w_extend_struct->power.p2_pwr;
 #elif !BSP_MCU_GROUP_RA6W1            // TIN-TODO
        GPIO->P1_PADPWR_CTRL_REG = gpio_w_extend_struct->power.p1_pwr;
 #endif

 #if BSP_FEATURE_IO_HAS_WEAK_CONFIG_PER_PORT
        GPIO->P0_WEAK_CTRL_REG = gpio_w_extend_struct->weak_pad_power.p0_pwr;
        GPIO->P1_WEAK_CTRL_REG = gpio_w_extend_struct->weak_pad_power.p1_pwr;
  #if (0 != BSP_FEATURE_IO_PORT2_GPIO_COUNT)
        GPIO->P2_WEAK_CTRL_REG = gpio_w_extend_struct->weak_pad_power.p2_pwr;
  #endif
 #elif !BSP_MCU_GROUP_RA6W1            // TIN-TODO
        GPIO->PAD_WEAK_CTRL_REG = gpio_w_extend_struct->weak_pad_power.aggregate;
 #endif

        uint32_t temp = GPIO->GPIO_CLK_SEL_REG & GPIO_W_CLK_SEL_REG_FUNC_MASK;
        GPIO->GPIO_CLK_SEL_REG = gpio_w_extend_struct->fixed_pin_clk_out | temp;

        GPIO->GPIO_CLK_SEL_REG_b.FUNC_CLOCK_SEL = gpio_w_extend_struct->sel_pin_clk_out.clk_sel;
        GPIO->GPIO_CLK_SEL_REG_b.FUNC_CLOCK_EN  = gpio_w_extend_struct->sel_pin_clk_out.clk_en;
    }
#endif

    for (pin_count = 0U; pin_count < p_cfg->number_of_pins; pin_count++)
    {
        r_gpio_w_pin_config(p_ctrl, p_cfg->p_pin_cfg_data[pin_count].pin, p_cfg->p_pin_cfg_data[pin_count].pin_cfg);
    }
}

/*******************************************************************************************************************//**
 * Writes to the specified pin's register
 *
 * @param[in]    p_ctrl     Instance ctrl
 * @param[in]    pin        Pin to write Mux data for
 * @param[in]    cfg        Value to be written
 *
 **********************************************************************************************************************/
static void r_gpio_w_pin_config (gpio_w_instance_ctrl_t * p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg)
{
#if BSP_MCU_GROUP_RA6W1
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    bsp_io_port_pin_t pin_id  = (bsp_io_port_pin_t) (BSP_IO_PIN_BITS & (uint16_t) pin);
    bsp_io_port_t     port_id =
        (bsp_io_port_t) ((BSP_IO_PORT_BITS & (uint16_t) pin) >> BSP_IO_PORT_OFFSET);
    bsp_io_level_t level = (bsp_io_level_t) ((cfg & GPIO_W_PRV_LEVEL_BITS) >> GPIO_W_PRV_LEVEL_OFFSET);
#if !defined(BSP_MCU_GROUP_RA6W1)
    uint32_t mode = cfg & GPIO_W_MODE_REG_VALID_BITS_MSK;
#else
    uint16_t mode = cfg & GPIO_W_PRV_MODE_BITS;
#endif
#if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
    if (BSP_IO_PORT_01 == port_id)
    {
        PMU_ANA->POWER_CTRL_REG_b.EN_HSGND = 1;
        FSP_HARDWARE_REGISTER_WAIT(PMU_ANA->ANA_STATUS_REG_b.HSGND_OK, 1U);
    }
#endif
#if !defined(BSP_MCU_GROUP_RA6W1)
    if (GPIO_W_PERIPHERAL_GPIO == (mode & GPIO_W_PRV_FUNC_BITS))
    {
        if (BSP_IO_LEVEL_HIGH == level)
        {
            *(p_ctrl->p_reg_p0_set_data + port_id) = 1 << pin_id;
        }
        else
        {
            *(p_ctrl->p_reg_p0_reset_data + port_id) = 1 << pin_id;
        }
    }

    GPIO_W_PXX_MODE_REG(port_id, pin_id) = mode;
#else
    if (GPIO_W_PERIPHERAL_GPIO == (mode & GPIO_W_PRV_FUNC_BITS))
    {
        R_BSP_PinWrite(pin, level);
    }

    if (GPIO_W_CFG_RETENTION == (cfg & GPIO_W_CFG_RETENTION))
    {
        R_BSP_PinCfg(pin, mode);
        R_BSP_RetainedIoSet(pin);
    }
    else
    {
        R_BSP_PinCfg(pin, mode);
    }

    if (GPIO_W_CFG_IRQ_ENABLE == (cfg & GPIO_W_CFG_IRQ_ENABLE))
    {
        BSP_IO_PXX_SEL_REG(port_id) |= (uint32_t) (0x01 << pin_id);
    }
    else
    {
        BSP_IO_PXX_SEL_REG(port_id) &= ~((uint32_t) (0x01 << pin_id));
    }
#endif
}

#if BSP_MCU_GROUP_RA6W1
 #if CFG_PMGR
static fsp_err_t r_gpio_w_enter_sleep (ioport_ctrl_t * p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    fsp_err_t err = FSP_SUCCESS;

    for (uint8_t port = 0; port < BSP_FEATURE_IO_PORT_COUNT; port++)
    {
        /* Store GPIO IRQ settings */
        gpio_w_pol[port]  = BSP_IO_PXX_POL_REG(port);
        gpio_w_sel1[port] = BSP_IO_PXX_SEL1_REG(port);
        gpio_w_sel[port]  = BSP_IO_PXX_SEL_REG(port);
    }

    R_BSP_RetainedIoExecute();

    return err;
}

static fsp_err_t r_gpio_w_wakeup (ioport_ctrl_t * p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    fsp_err_t           err = FSP_SUCCESS;
    bsp_io_wakeup_pin_t wakeup_pin;

    wakeup_pin = R_BSP_WakeupSourcePinGet();
    R_BSP_RetainedIoRecovery(false);

    for (uint8_t port = 0; port < BSP_FEATURE_IO_PORT_COUNT; port++)
    {
        /* Restore GPIO IRQ settings */
        BSP_IO_PXX_POL_REG(port)  = gpio_w_pol[port];  // Restore polarity (High/Low)
        BSP_IO_PXX_SEL1_REG(port) = gpio_w_sel1[port]; // Restore sensitivity (Level/Edge)
        BSP_IO_PXX_SEL_REG(port)  = gpio_w_sel[port];  // Restore mode (Enable/Disable)
    }

    if (wakeup_pin != 0)
    {
        bsp_io_port_pin_t port_pin = bsp_prv_wakeup_pin_to_port_pin(wakeup_pin);

        if (port_pin != BSP_IO_PORT_FF_PIN_FF)
        {
            uint8_t port = (uint8_t) ((port_pin >> BSP_IO_PORT_OFFSET) & BSP_IO_PORT_BITS);
            uint8_t pin  = (uint8_t) (port_pin & BSP_IO_PIN_BITS);

            bool irq_enabled    = !!(gpio_w_sel[port] & (1 << pin));
            bool edge_sensitive = !!(gpio_w_sel1[port] & (1 << pin));

            if (irq_enabled && edge_sensitive)
            {
                bool irq_edge    = !!(gpio_w_pol[port] & (1 << pin));
                bool wakeup_edge = !!(RTC->GPIO_WAKEUP0_REG_b.GPIO_WAKEUP_EDGE_INVERSION_SEL & wakeup_pin);

                if (irq_edge == wakeup_edge)
                {
                    R_BSP_IrqSetPending(GPIO_P0_IRQn + port);
                }
            }
        }
    }

    return err;
}

static void r_gpio_w_pmgr_callback (pmgr_callback_args_t * p_args)
{
    pmgr_instance_info_t * p_pmgr_info = (pmgr_instance_info_t *) p_args->p_instance_info;

    if (p_pmgr_info->power_mode == PMGR_LLD_POWER_MODE_SLEEP4)
    {
        if (p_args->event == PMGR_EVENT_ENTERING_SLEEP)
        {
            r_gpio_w_enter_sleep((ioport_ctrl_t *) p_args->p_context);
        }
        else if (p_args->event == PMGR_EVENT_EXITING_SLEEP)
        {
            r_gpio_w_wakeup((ioport_ctrl_t *) p_args->p_context);
        }
    }
}

static fsp_err_t r_gpio_w_subscribe_for_pmgr_notifications (ioport_ctrl_t * const p_ctrl)
{
    fsp_err_t     err       = FSP_SUCCESS;
    pmgr_ctrl_t * pmgr_ctrl = NULL;

    g_r_gpio_w_pmgr_args.p_context = (void *) p_ctrl;

    pmgr_ctrl = RM_PMGR_W_get_ctrl();
    FSP_ASSERT(pmgr_ctrl != NULL);

    err = RM_PMGR_W_notifier_register(pmgr_ctrl,
                                      r_gpio_w_pmgr_callback,
                                      &g_r_gpio_w_pmgr_args,
                                      &g_r_gpio_w_pmgr_notifier_extend);
    FSP_ASSERT(FSP_SUCCESS == err);

    return FSP_SUCCESS;
}

static fsp_err_t r_gpio_w_unsubscribe_from_pmgr_notifications (void)
{
    fsp_err_t     err       = FSP_SUCCESS;
    pmgr_ctrl_t * pmgr_ctrl = NULL;
    FSP_ASSERT(pmgr_ctrl != NULL);

    pmgr_ctrl = RM_PMGR_W_get_ctrl();
    FSP_ASSERT(pmgr_ctrl != NULL);

    err = RM_PMGR_W_notifier_unregister(pmgr_ctrl, g_r_gpio_w_pmgr_notifier_extend.notifier_id);
    FSP_ASSERT(FSP_SUCCESS == err);

    return FSP_SUCCESS;
}

 #endif                                // #if CFG_PMGR
#endif
