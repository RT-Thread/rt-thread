/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>
#include "bsp_api.h"
#include "r_ioport.h"
#include "r_ioport_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "PORT" in ASCII, used to determine if the module is open */
#define IOPORT_OPEN                (0x504F5254U)
#define IOPORT_CLOSED              (0x00000000U)

/* Shift to get port in bsp_io_port_t and bsp_io_port_pin_t enums. */
#define IOPORT_PRV_PORT_OFFSET     (8U)

#define IOPORT_PRV_PORT_BITS       (0xFF00U)
#define IOPORT_PRV_PIN_BITS        (0x00FFU)

#define IOPORT_PRV_8BIT_MASK       (0x00FFU)

/* Added definitions */
#define IOPORT_PIN_NUM_MUX         (8U)
#define IOPORT_REGION_SEL_SAFE     (0U)
#define IOPORT_REGION_SEL_NSAFE    (1U)
#define IOPORT_RSEL_MASK           (0x01U)
#define IOPORT_PM_BIT_MASK         (0x0003U)
#define IOPORT_PFC_BIT_MASK        (0x0000000FU)
#define IOPORT_DRTCL_BIT_MASK      (0x000000FFU)
#define IOPORT_ELC_PEL_MASK        (0x80)
#define IOOPRT_ELC_PGC_MASK        (0x88)
#define IOPORT_ELC_PEL_PSM_HIGH    (0x20)

/* Switch IOPORT register region either safety or non safety */
#define IOPORT_PRV_PORT_ADDRESS(region_sel)    (region_sel == 1 ? (R_PORT_NSR) : (R_PORT_SR))

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct st_ioport_cfg_data
{
    uint32_t p_reg    : 1;
    uint32_t pm_reg   : 2;
    uint32_t pmc_reg  : 1;
    uint32_t pfc_reg  : 4;
    uint32_t drct_reg : 6;
    uint32_t rsel_reg : 1;
    uint32_t reserved : 17;
} ioport_cfg_data_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_ioport_pins_config(const ioport_cfg_t * p_cfg);
static void r_ioport_pin_set(bsp_io_port_pin_t pin, ioport_cfg_data_t * p_cfg_data);
static void r_ioport_event_config(const ioport_extend_cfg_t * p_extend_cfg_data);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* IOPort Implementation of IOPort Driver  */
const ioport_api_t g_ioport_on_ioport =
{
    .open                 = R_IOPORT_Open,
    .close                = R_IOPORT_Close,
    .pinsCfg              = R_IOPORT_PinsCfg,
    .pinCfg               = R_IOPORT_PinCfg,
    .pinEventInputRead    = R_IOPORT_PinEventInputRead,
    .pinEventOutputWrite  = R_IOPORT_PinEventOutputWrite,
    .pinRead              = R_IOPORT_PinRead,
    .pinWrite             = R_IOPORT_PinWrite,
    .portDirectionSet     = R_IOPORT_PortDirectionSet,
    .portEventInputRead   = R_IOPORT_PortEventInputRead,
    .portEventOutputWrite = R_IOPORT_PortEventOutputWrite,
    .portRead             = R_IOPORT_PortRead,
    .portWrite            = R_IOPORT_PortWrite,
};

/*******************************************************************************************************************//**
 * @addtogroup IOPORT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes internal driver data, then calls pin configuration function to configure pins.
 *
 * @retval FSP_SUCCESS                  Pin configuration data written to the multiple registers
 * @retval FSP_ERR_ASSERTION            NULL pointer
 * @retval FSP_ERR_ALREADY_OPEN         Module is already open.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_Open (ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg)
{
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_pin_cfg_data);
    FSP_ERROR_RETURN(IOPORT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Set driver status to open */
    p_instance_ctrl->open = IOPORT_OPEN;

    p_instance_ctrl->p_cfg = p_cfg;

    r_ioport_pins_config(p_cfg);

    r_ioport_event_config(p_cfg->p_extend);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets IOPORT registers. Implements @ref ioport_api_t::close
 *
 * @retval FSP_SUCCESS             The IOPORT was successfully uninitialized
 * @retval FSP_ERR_ASSERTION       p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_Close (ioport_ctrl_t * const p_ctrl)
{
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Set state to closed */
    p_instance_ctrl->open = IOPORT_CLOSED;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the functions of multiple pins by loading configuration data into the multiple registers.
 * Implements @ref ioport_api_t::pinsCfg.
 *
 * This function initializes the supplied list of the multiple registers with the supplied values. This data can be generated
 * by the Pins tab of the RZ/N2L Configuration editor or manually by the developer. Different pin configurations can be
 * loaded for different situations such as low power modes and testing.
 *
 * @retval FSP_SUCCESS             Pin configuration data written to the multiple registers
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 * @retval FSP_ERR_ASSERTION       NULL pointer
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinsCfg (ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_pin_cfg_data);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    r_ioport_pins_config(p_cfg);

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
fsp_err_t R_IOPORT_PinCfg (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    R_BSP_PinAccessEnable();

    r_ioport_pin_set(pin, (ioport_cfg_data_t *) &cfg);

    R_BSP_PinAccessDisable();

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the level on a pin. Implements @ref ioport_api_t::pinRead.
 *
 * The level for the specifed pin will be reterned by PINm register.
 *
 * @retval FSP_SUCCESS             Pin read
 * @retval FSP_ERR_ASSERTION       NULL pointer
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 * @note This function is re-entrant for different pins.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_pin_value);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    *p_pin_value = (bsp_io_level_t) R_BSP_FastPinRead(R_BSP_IoRegionGet(pin), pin);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the value on an IO port. Implements @ref ioport_api_t::portRead.
 *
 * The specified port will be read, and the levels for all the pins will be returned by PINm register.
 * Each bit in the returned value corresponds to a pin on the port. For example, bit 7 corresponds
 * to pin 7, bit 6 to pin 6, and so on.
 *
 * @retval FSP_SUCCESS             Port read
 * @retval FSP_ERR_ASSERTION       NULL pointer
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 * @note This function is re-entrant for different ports.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_port_value)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_port_value);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    R_PORT_COMMON_Type * p_ioport_regs;
    ioport_size_t        safe_value;
    ioport_size_t        nsafe_value;

    /* Get port number */
    uint32_t port_num = (IOPORT_PRV_PORT_BITS & (ioport_size_t) port) >> IOPORT_PRV_PORT_OFFSET;

    /* Get the RSELP register value */
    ioport_size_t rselp_value = (ioport_size_t) R_PTADR->RSELP[port_num];

    /* Get the port register address in non safety region */
    p_ioport_regs = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_NSAFE);

    /* Read the specified port states in non safety region */
    nsafe_value = (ioport_size_t) (p_ioport_regs->PIN[port_num] & rselp_value);

    /* Get the port register address in safety region */
    p_ioport_regs = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_SAFE);

    /* Read the specified port states in safety region */
    safe_value = (ioport_size_t) (p_ioport_regs->PIN[port_num] & ~(rselp_value));

    /* Read the specified port states */
    *p_port_value = nsafe_value | safe_value;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes to multiple pins on a port. Implements @ref ioport_api_t::portWrite.
 *
 * The output value will be written to the specified port. Each bit in the value parameter corresponds to a bit
 * on the port. For example, bit 7 corresponds to pin 7, bit 6 to pin 6, and so on.
 * Each bit in the mask parameter corresponds to a pin on the port.
 *
 * Only the bits with the corresponding bit in the mask value set will be updated.
 * For example, value = 0x00FF, mask = 0x0003 results in only bits 0 and 1 being updated.
 *
 * @retval FSP_SUCCESS                  Port written to
 * @retval FSP_ERR_INVALID_ARGUMENT     The port and/or mask not valid
 * @retval FSP_ERR_NOT_OPEN             The module has not been opened
 * @retval FSP_ERR_ASSERTION            NULL pointerd
 *
 * @note This function is re-entrant for different ports. This function makes use of the Pm register to atomically
 * modify the levels on the specified pins on a port.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortWrite (ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t value, ioport_size_t mask)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(mask > (ioport_size_t) 0, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    R_PORT_COMMON_Type * p_ioport_regs;
    ioport_size_t        temp_value;
    ioport_size_t        write_mask;

    /* mask value: lower word is valid, upper word is invalid */
    mask &= IOPORT_PRV_8BIT_MASK;

    /* Get port number */
    uint32_t port_num = (IOPORT_PRV_PORT_BITS & (ioport_size_t) port) >> IOPORT_PRV_PORT_OFFSET;

    /* Get the RSELP register value */
    ioport_size_t rselp_value = R_PTADR->RSELP[port_num];

    /* Set value to non safety region register */
    write_mask = rselp_value & mask;
    if (write_mask)
    {
        /* Get the port register address */
        p_ioport_regs = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_NSAFE);

        /* Output data store of the specified pins sets to low output */
        temp_value = (ioport_size_t) (p_ioport_regs->P[port_num] & (~write_mask));

        /* Write output data to P register of the specified pins */
        p_ioport_regs->P[port_num] = (uint8_t) (temp_value | (value & write_mask));
    }

    /* Set value to safety region register */
    write_mask = (ioport_size_t) ((~rselp_value) & mask);
    if (write_mask)
    {
        /* Get the port register address */
        p_ioport_regs = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_SAFE);

        /* Output data store of the specified pins sets to low output */
        temp_value = (ioport_size_t) (p_ioport_regs->P[port_num] & (~write_mask));

        /* Write output data to P register of the specified pins */
        p_ioport_regs->P[port_num] = (uint8_t) (temp_value | (value & write_mask));
    }

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
 * @note This function is re-entrant for different pins. This function makes use of the Pm register to atomically
 * modify the level on the specified pin on a port.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinWrite (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t level)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(level <= BSP_IO_LEVEL_HIGH, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    R_PORT_COMMON_Type * p_ioport_regs;

    /* Get port and pin number */
    uint32_t port_num = (IOPORT_PRV_PORT_BITS & (ioport_size_t) pin) >> IOPORT_PRV_PORT_OFFSET;
    uint32_t pin_num  = (IOPORT_PRV_PIN_BITS & (ioport_size_t) pin);

    /* Get the port register address */
    p_ioport_regs = (IOPORT_PRV_PORT_ADDRESS(((uint16_t) (R_PTADR->RSELP[port_num] >> pin_num) &
                                              IOPORT_RSEL_MASK)));

    /* Set output level to P register of the specified pin */
    if (BSP_IO_LEVEL_LOW == level)
    {
        p_ioport_regs->P[port_num] &= (uint8_t) (~(1U << pin_num));
    }
    else
    {
        p_ioport_regs->P[port_num] |= (uint8_t) (1U << pin_num);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets the direction of individual pins on a port. Implements @ref ioport_api_t::portDirectionSet().
 *
 * Multiple pins on a port can be set to inputs or outputs at once.
 * Each bit in the mask parameter corresponds to a pin on the port. For example, bit 7 corresponds to
 * pin 7, bit 6 to pin 6, and so on. If a mask bit is set to 1 then the corresponding pin will be changed to
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
fsp_err_t R_IOPORT_PortDirectionSet (ioport_ctrl_t * const p_ctrl,
                                     bsp_io_port_t         port,
                                     ioport_size_t         direction_values,
                                     ioport_size_t         mask)
{
    uint32_t pin_num;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(mask > (uint16_t) 0, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* mask value: lower word is valid, upper word is invalid */
    mask &= IOPORT_PRV_8BIT_MASK;

    for (pin_num = 0U; pin_num < IOPORT_PIN_NUM_MUX; pin_num++)
    {
        if (mask & (1U << pin_num))
        {
            /* Get port number */
            uint32_t port_num = (IOPORT_PRV_PORT_BITS & (ioport_size_t) port) >> IOPORT_PRV_PORT_OFFSET;

            /* Get the port register address */
            R_PORT_COMMON_Type * p_ioport_regs =
                IOPORT_PRV_PORT_ADDRESS(((uint16_t) (R_PTADR->RSELP[port_num] >> pin_num) &
                                         IOPORT_RSEL_MASK));

            /* Set  */
            uint16_t set_bits = (uint16_t) (direction_values & (IOPORT_PM_BIT_MASK << (pin_num * 2U)));

            /* Set the direction value */
            uint16_t temp_value = (uint16_t) (p_ioport_regs->PM[port_num] & ~(IOPORT_PM_BIT_MASK << (pin_num * 2U)));
            p_ioport_regs->PM[port_num] = temp_value | set_bits;
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
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortEventInputRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_event_data)
{
    uint8_t portgroup = 0U;
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_event_data);
    FSP_ERROR_RETURN((port == BSP_IO_PORT_16) || (port == BSP_IO_PORT_18), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    const ioport_extend_cfg_t * elc_cfg = p_instance_ctrl->p_cfg->p_extend;

    /* Get register address */
    R_PORT_COMMON_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_NSAFE);

    /* Get port group number for the specified port */
    if (BSP_IO_PORT_16 == port)
    {
        portgroup = 0U;
    }
    else if (BSP_IO_PORT_18 == port)
    {
        portgroup = 1U;
    }
    else
    {
        /* Do Nothing */
    }

    /* Read current value of buffer value from ELC_PDBF register for the specified port group */
    *p_event_data =
        (uint16_t) (p_ioport_regs->ELC_PDBF[portgroup].BY & elc_cfg->port_group_input_cfg[portgroup].pin_select);

    return FSP_SUCCESS;
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
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinEventInputRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_event)
{
    uint8_t portgroup = 0U;
    uint8_t portvalue;
    uint8_t mask;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_pin_event);
    uint32_t port_number = pin >> IOPORT_PRV_PORT_OFFSET;
    FSP_ERROR_RETURN((port_number == BSP_IO_PORT_16 >> IOPORT_PRV_PORT_OFFSET) ||
                     (port_number == BSP_IO_PORT_18 >> IOPORT_PRV_PORT_OFFSET),
                     FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Get port and pin number */
    uint32_t port_num = (IOPORT_PRV_PORT_BITS & (ioport_size_t) pin);
    uint32_t pin_num  = (IOPORT_PRV_PIN_BITS & (ioport_size_t) pin);

    /* Get register address */
    R_PORT_COMMON_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_NSAFE);

    /* Get port group number for the specified port */
    if (BSP_IO_PORT_16 == port_num)
    {
        portgroup = 0U;
    }
    else if (BSP_IO_PORT_18 == port_num)
    {
        portgroup = 1U;
    }
    else
    {
        /* Do Nothing */
    }

    /* Read current value of buffer value from ELC_PDBF register for the specified port group */
    portvalue = p_ioport_regs->ELC_PDBF[portgroup].BY;
    mask      = (uint8_t) (1U << pin_num);

    if ((portvalue & mask) == mask)
    {
        *p_pin_event = BSP_IO_LEVEL_HIGH;
    }
    else
    {
        *p_pin_event = BSP_IO_LEVEL_LOW;
    }

    return FSP_SUCCESS;
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
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortEventOutputWrite (ioport_ctrl_t * const p_ctrl,
                                         bsp_io_port_t         port,
                                         ioport_size_t         event_data,
                                         ioport_size_t         mask_value)
{
    uint8_t       portgroup = 0U;
    ioport_size_t temp_value;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(mask_value > (ioport_size_t) 0, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((port == BSP_IO_PORT_16) || (port == BSP_IO_PORT_18), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    R_BSP_PinAccessEnable();           // Unlock Register Write Protection

    /* Get register address */
    R_PORT_COMMON_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_NSAFE);

    /* Get port group number for the specified port */
    if (BSP_IO_PORT_16 == port)
    {
        portgroup = 0U;
    }
    else if (BSP_IO_PORT_18 == port)
    {
        portgroup = 1U;
    }
    else
    {
        /* Do Nothing */
    }

    temp_value  = p_ioport_regs->ELC_PDBF[portgroup].BY;
    temp_value &= (ioport_size_t) (~mask_value);

    p_ioport_regs->ELC_PDBF[portgroup].BY = (uint8_t) (temp_value | event_data);

    R_BSP_PinAccessDisable();          // Lock Register Write Protection

    return FSP_SUCCESS;
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
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinEventOutputWrite (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t pin_value)
{
    uint8_t singleport = 0U;
    uint8_t cnt;
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((pin_value == BSP_IO_LEVEL_HIGH) || (pin_value == BSP_IO_LEVEL_LOW), FSP_ERR_INVALID_ARGUMENT);
    uint32_t port_number = pin >> IOPORT_PRV_PORT_OFFSET;
    FSP_ERROR_RETURN((port_number == BSP_IO_PORT_16 >> IOPORT_PRV_PORT_OFFSET) ||
                     (port_number == BSP_IO_PORT_18 >> IOPORT_PRV_PORT_OFFSET),
                     FSP_ERR_INVALID_ARGUMENT);
#endif

    const ioport_extend_cfg_t * elc_cfg = p_instance_ctrl->p_cfg->p_extend;

    R_BSP_PinAccessEnable();           // Unlock Register Write Protection

    /* Get register address */
    R_PORT_COMMON_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_NSAFE);

    for (cnt = 0; cnt < IOPORT_SINGLE_PORT_NUM; cnt++)
    {
        if ((bsp_io_port_pin_t) elc_cfg->single_port_cfg[cnt].port_num == pin)
        {
            singleport = cnt;
        }
    }

    if (BSP_IO_LEVEL_HIGH == pin_value)
    {
        p_ioport_regs->ELC_PEL[singleport] |= (uint8_t) IOPORT_ELC_PEL_PSM_HIGH;
    }
    else
    {
        p_ioport_regs->ELC_PEL[singleport] &= (uint8_t) (~IOPORT_ELC_PEL_PSM_HIGH);
    }

    R_BSP_PinAccessDisable();          // Lock Register Write Protection

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup IOPORT)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures pins.
 *
 * @param[in]    p_cfg          Pin configuration data
 **********************************************************************************************************************/
void r_ioport_pins_config (const ioport_cfg_t * p_cfg)
{
    uint16_t       pin_count;
    ioport_cfg_t * p_pin_data;

    p_pin_data = (ioport_cfg_t *) p_cfg;

    R_BSP_PinAccessEnable();           // Unlock Register Write Protection

    for (pin_count = 0U; pin_count < p_pin_data->number_of_pins; pin_count++)
    {
        r_ioport_pin_set(p_pin_data->p_pin_cfg_data[pin_count].pin,
                         (ioport_cfg_data_t *) &p_pin_data->p_pin_cfg_data[pin_count].pin_cfg);
    }

    R_BSP_PinAccessDisable();          // Lock Register Write Protection
}

/*******************************************************************************************************************//**
 * Writes to the specified pin's multiple registers
 *
 * @param[in]    pin        Pin to write parameter data for
 * @param[in]    p_cfg_data Value to be written to the multiple registers
 *
 **********************************************************************************************************************/
static void r_ioport_pin_set (bsp_io_port_pin_t pin, ioport_cfg_data_t * p_cfg_data)
{
    R_PORT_COMMON_Type * p_ioport_regs;
    uint32_t             temp_value;

    /* Get port and pin number */
    uint32_t port    = (IOPORT_PRV_PORT_BITS & (ioport_size_t) pin) >> IOPORT_PRV_PORT_OFFSET;
    uint32_t pin_num = (IOPORT_PRV_PIN_BITS & (ioport_size_t) pin);

    /* Setting for Safety region or Non safety region */
    if (p_cfg_data->rsel_reg == 1U)    // Setting for Non safety region
    {
        R_PTADR->RSELP[port] |= (uint8_t) (1U << pin_num);
        p_ioport_regs         = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_NSAFE);
    }
    else                               // Setting for Safety region
    {
        R_PTADR->RSELP[port] &= (uint8_t) (~(1U << pin_num));
        p_ioport_regs         = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_SAFE);
    }

    /* Setting DRCTL register */
    if (3U >= pin_num)
    {
        temp_value = p_ioport_regs->DRCTL[port].L & ~(IOPORT_DRTCL_BIT_MASK << (pin_num * 8U));
        p_ioport_regs->DRCTL[port].L = temp_value | (uint32_t) (p_cfg_data->drct_reg << (pin_num * 8U));
    }
    else if (3U < pin_num)
    {
        temp_value = p_ioport_regs->DRCTL[port].H & ~(IOPORT_DRTCL_BIT_MASK << ((pin_num - 4U) * 8U));
        p_ioport_regs->DRCTL[port].H = temp_value | (uint32_t) (p_cfg_data->drct_reg << ((pin_num - 4U) * 8U));
    }
    else
    {
        /* Do Nothing */
    }

    /* Setting for GPIO or peripheral */
    if (1U == p_cfg_data->pmc_reg)                                                                  // Setting for peripheral
    {
        temp_value               = p_ioport_regs->PFC[port] & ~(IOPORT_PFC_BIT_MASK << (pin_num * 4U));
        p_ioport_regs->PFC[port] = temp_value | (uint32_t) (p_cfg_data->pfc_reg << (pin_num * 4U)); // Setting PFC register

        /* Setting peripheral for port mode */
        p_ioport_regs->PMC[port] |= (uint8_t) (p_cfg_data->pmc_reg << pin_num);                     // Setting PMC register
    }
    else // Setting for GPIO
    {
        /* Setting GPIO for port mode */
        p_ioport_regs->PMC[port] &= (uint8_t) (~(1U << pin_num)); // Setting PMC register

        /* Setting for input or output */
        if (1U == p_cfg_data->pm_reg)                             // Setting for input
        {
            /* Setting PM register. */
            /* 01b: Input           */
            temp_value              = (uint32_t) (p_ioport_regs->PM[port] & ~(IOPORT_PM_BIT_MASK << (pin_num * 2U)));
            p_ioport_regs->PM[port] = (uint16_t) (temp_value | (uint32_t) (1U << (pin_num * 2U)));
        }
        else if (1U < p_cfg_data->pm_reg)     // Setting for two kinds of Output
        {
            /* Setting P register */
            if (0U == p_cfg_data->p_reg)      // Low output setting
            {
                p_ioport_regs->P[port] &= (uint8_t) (~(1U << pin_num));
            }
            else if (1U == p_cfg_data->p_reg) // High output setting
            {
                p_ioport_regs->P[port] |= (uint8_t) (1U << pin_num);
            }
            else
            {
                /* Do Nothing */
            }

            /* Setting PM register.                              */
            /* 10b: Output                                       */
            /* 11b: Output(output data is input to input buffer) */
            temp_value              = (uint32_t) (p_ioport_regs->PM[port] & ~(IOPORT_PM_BIT_MASK << (pin_num * 2U)));
            p_ioport_regs->PM[port] = (uint16_t) (temp_value | (uint32_t) (p_cfg_data->pm_reg << (pin_num * 2U)));
        }
        else
        {
            /* Do Nothing */
        }
    }
}

/*******************************************************************************************************************//**
 * Writes to the specified pin's multiple registers to generate event link function
 *
 * @param[in]    p_extend_cfg_data Value to be written to the multiple registers
 *
 **********************************************************************************************************************/
static void r_ioport_event_config (const ioport_extend_cfg_t * p_extend_cfg_data)
{
    uint8_t               event_num;
    uint8_t               temp_value    = 0x00;
    uint8_t               single_enable = 0x00;
    uint8_t               group_enable  = 0x00;
    R_PORT_COMMON_Type  * p_ioport_regs;
    ioport_extend_cfg_t * ex_cfg;

    ex_cfg = (ioport_extend_cfg_t *) p_extend_cfg_data;

    R_BSP_PinAccessEnable();           // Unlock Register Write Protection

    /* Get register address */
    p_ioport_regs = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_NSAFE);

    /* Single port configuration */
    for (event_num = 0U; event_num < IOPORT_SINGLE_PORT_NUM; event_num++)
    {
        uint8_t port =
            (uint8_t) ((ex_cfg->single_port_cfg[event_num].port_num & IOPORT_PRV_PORT_BITS) >> IOPORT_PRV_PORT_OFFSET);
        uint8_t pin_num = (uint8_t) ex_cfg->single_port_cfg[event_num].port_num & IOPORT_PRV_PIN_BITS;

        temp_value = p_ioport_regs->ELC_PEL[event_num] & IOPORT_ELC_PEL_MASK;

        /* Port selection */
        if ((BSP_IO_PORT_16 >> IOPORT_PRV_PORT_OFFSET) == port)
        {
            temp_value |= 1U << 3;
        }
        else if ((BSP_IO_PORT_18 >> IOPORT_PRV_PORT_OFFSET) == port)
        {
            temp_value |= 1U << 4;
        }
        else
        {
            /* Do Nothing */
        }

        temp_value |= pin_num;         // Pin number setting

        /* When the pin specified as single input port, Set edge detection */
        /* When the pin specified as single output port, Set output operation */
        if (IOPORT_EVENT_DIRECTION_INPUT == ex_cfg->single_port_cfg[event_num].direction)
        {
            temp_value |= (uint8_t) (ex_cfg->single_port_cfg[event_num].edge_detection << 5); // Edge detection

            /* Edge detection enable */
            p_ioport_regs->ELC_DPTC |= (uint8_t) (1U << event_num);
        }
        else
        {
            temp_value |= (uint8_t) (ex_cfg->single_port_cfg[event_num].operation << 5); // Output operation
        }

        /* Set to ELC port setting register */
        p_ioport_regs->ELC_PEL[event_num] = temp_value;

        /* Single port event link function enable */
        if (IOPORT_EVENT_CONTROL_ENABLE == ex_cfg->single_port_cfg[event_num].event_control)
        {
            single_enable |= (uint8_t) (1U << event_num);
        }
    }

    /* Port group configuration */
    for (event_num = 0U; event_num < IOPORT_PORT_GROUP_NUM; event_num++)
    {
        /* Pin selection */
        uint8_t group_pin = ex_cfg->port_group_input_cfg[event_num].pin_select |
                            ex_cfg->port_group_output_cfg[event_num].pin_select;
        p_ioport_regs->ELC_PGR[event_num] = group_pin;

        if (IOPORT_EVENT_CONTROL_ENABLE == ex_cfg->port_group_input_cfg[event_num].event_control)
        {
            /* Input port group control */
            temp_value  = p_ioport_regs->ELC_PGC[event_num] & IOOPRT_ELC_PGC_MASK;
            temp_value |= ex_cfg->port_group_input_cfg[event_num].edge_detection;                      // Edge detection
            temp_value |= (uint8_t) (ex_cfg->port_group_input_cfg[event_num].overwrite_control << 2U); // Overwrite setting

            /* Buffer register initialization */
            p_ioport_regs->ELC_PDBF[event_num].BY = ex_cfg->port_group_input_cfg[event_num].buffer_init_value;

            /* Input port group event link function enable */
            group_enable |= (uint8_t) (1U << event_num);
        }

        /* Output port group operation */
        temp_value |= (uint8_t) (ex_cfg->port_group_output_cfg[event_num].operation << 4);

        /* Set to port group control register */
        p_ioport_regs->ELC_PGC[event_num] = temp_value;
    }

    /* Set to ELC port event control register */
    p_ioport_regs->ELC_ELSR2 = (uint8_t) ((single_enable << 4) | (group_enable << 2));

    R_BSP_PinAccessDisable();          // Lock Register Write Protection
}
