/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
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
#define IOPORT_OPEN                       (0x504F5254U)
#define IOPORT_CLOSED                     (0x00000000U)

/* Mask to get PSEL bitfield from PFS register. */
#define BSP_PRV_PFS_PSEL_MASK             (0x1F000000UL)

/* Shift to get pin 0 on a package in extended data. */
#define IOPORT_PRV_EXISTS_B0_SHIFT        (16UL)

/* Mask to determine if any pins on port exist on this package. */
#define IOPORT_PRV_PORT_EXISTS_MASK       (0xFFFF0000U)

/* Shift to get port in bsp_io_port_t and bsp_io_port_pin_t enums. */
#define IOPORT_PRV_PORT_OFFSET            (8U)

#define IOPORT_PRV_PORT_BITS              (0xFF00U)
#define IOPORT_PRV_PIN_BITS               (0x00FFU)

#define IOPORT_PRV_PCNTR_OFFSET           0x00000020U

#define IOPORT_PRV_PERIPHERAL_FUNCTION    (1U << 16)
#define IOPORT_PRV_CLEAR_BITS_MASK        (0x1F01FCD5U) ///< Zero bits in mask must be written as zero to PFS register

#define IOPORT_PRV_8BIT_MASK              (0xFFU)
#define IOPORT_PRV_16BIT_MASK             (0xFFFFU)
#define IOPORT_PRV_UPPER_16BIT_MASK       (0xFFFF0000U)
#define IOPORT_PRV_PFENET_MASK            (0x30U)

#define IOPORT_PRV_SET_PWPR_PFSWE         (0x40U)
#define IOPORT_PRV_SET_PWPR_BOWI          (0x80U)

#define IOPORT_PRV_PORT_ADDRESS(port_number)    ((uint32_t) (R_PORT1 - R_PORT0) * (port_number) + R_PORT0)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_ioport_pins_config(const ioport_cfg_t * p_cfg);

static void r_ioport_hw_pin_event_output_data_write(bsp_io_port_t  port,
                                                    ioport_size_t  set_value,
                                                    ioport_size_t  reset_value,
                                                    bsp_io_level_t pin_level);

static void r_ioport_pfs_write(bsp_io_port_pin_t pin, uint32_t value);

#if BSP_FEATURE_SYSC_HAS_VBTICTLR || BSP_FEATURE_RTC_HAS_TCEN
static void bsp_vbatt_init(ioport_cfg_t const * const p_pin_cfg); // Used internally by BSP

#endif

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

#if BSP_FEATURE_SYSC_HAS_VBTICTLR || BSP_FEATURE_RTC_HAS_TCEN
static const bsp_io_port_pin_t g_vbatt_pins_input[] =
{
    BSP_IO_PORT_04_PIN_02,             ///< Associated with VBTICTLR->VCH0INEN
    BSP_IO_PORT_04_PIN_03,             ///< Associated with VBTICTLR->VCH1INEN
    BSP_IO_PORT_04_PIN_04              ///< Associated with VBTICTLR->VCH2INEN
};
#endif

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
 * @retval FSP_SUCCESS                  Pin configuration data written to PFS register(s)
 * @retval FSP_ERR_ASSERTION            NULL pointer
 * @retval FSP_ERR_ALREADY_OPEN         Module is already open.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_Open (ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg)
{
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_pin_cfg_data || 0 == p_cfg->number_of_pins);
    FSP_ERROR_RETURN(IOPORT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Set driver status to open */
    p_instance_ctrl->open = IOPORT_OPEN;

    r_ioport_pins_config(p_cfg);

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
 * Configures the functions of multiple pins by loading configuration data into pin PFS registers.
 * Implements @ref ioport_api_t::pinsCfg.
 *
 * This function initializes the supplied list of PmnPFS registers with the supplied values. This data can be generated
 * by the Pins tab of the RA Configuration editor or manually by the developer. Different pin configurations can be
 * loaded for different situations such as low power modes and testing.
 *
 * @retval FSP_SUCCESS             Pin configuration data written to PFS register(s)
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

#if BSP_FEATURE_SYSC_HAS_VBTICTLR || BSP_FEATURE_RTC_HAS_TCEN

    /* Create temporary structure for handling VBATT pins. */
    ioport_cfg_t     temp_cfg;
    ioport_pin_cfg_t temp_pin_cfg;

    temp_pin_cfg.pin     = pin;
    temp_pin_cfg.pin_cfg = cfg;

    temp_cfg.number_of_pins = 1U;
    temp_cfg.p_pin_cfg_data = &temp_pin_cfg;

    /* Handle any VBATT domain pin configuration. */
    bsp_vbatt_init(&temp_cfg);
#endif

    R_BSP_PinAccessEnable();

    r_ioport_pfs_write(pin, cfg);

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

    /* Get the port address */
    R_PORT0_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS((port >> IOPORT_PRV_PORT_OFFSET) & IOPORT_PRV_8BIT_MASK);

    /* Read current value of PCNTR2 register for the specified port */
    *p_port_value = p_ioport_regs->PCNTR2 & IOPORT_PRV_16BIT_MASK;

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
 * @note This function is re-entrant for different ports. This function makes use of the PCNTR3 register to atomically
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

    ioport_size_t setbits;
    ioport_size_t clrbits;

    /* High bits */
    setbits = value & mask;

    /* Low bits */
    /* Cast to ensure size */
    clrbits = (ioport_size_t) ((~value) & mask);

    /* Get the port address */
    R_PORT0_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS((port >> IOPORT_PRV_PORT_OFFSET) & IOPORT_PRV_8BIT_MASK);

    /* PCNTR3 register: lower word = set data, upper word = reset_data */
    p_ioport_regs->PCNTR3 = (uint32_t) (((uint32_t) clrbits << 16) | setbits);

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
 * @note This function is re-entrant for different pins. This function makes use of the PCNTR3 register to atomically
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

    ioport_size_t setbits = 0U;
    ioport_size_t clrbits = 0U;
    bsp_io_port_t port    = (bsp_io_port_t) (IOPORT_PRV_PORT_BITS & (ioport_size_t) pin);

    ioport_size_t shift    = IOPORT_PRV_PIN_BITS & (ioport_size_t) pin;
    ioport_size_t pin_mask = (ioport_size_t) (1U << shift);

    if (BSP_IO_LEVEL_LOW == level)
    {
        clrbits = pin_mask;
    }
    else
    {
        setbits = pin_mask;
    }

    /* PCNTR register is updated instead of using PFS as access is atomic and PFS requires seperate enable/disable
     * using PWPR register */

    /* Get the port address */
    R_PORT0_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS((port >> IOPORT_PRV_PORT_OFFSET) & IOPORT_PRV_8BIT_MASK);

    /* PCNTR3 register: lower word = set data, upper word = reset_data */
    p_ioport_regs->PCNTR3 = (uint32_t) (((uint32_t) clrbits << 16) | setbits);

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
fsp_err_t R_IOPORT_PortDirectionSet (ioport_ctrl_t * const p_ctrl,
                                     bsp_io_port_t         port,
                                     ioport_size_t         direction_values,
                                     ioport_size_t         mask)
{
    uint32_t orig_value;
    uint32_t set_bits;
    uint32_t clr_bits;
    uint32_t write_value;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(mask > (ioport_size_t) 0, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Get the port address */
    R_PORT0_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS((port >> IOPORT_PRV_PORT_OFFSET) & IOPORT_PRV_8BIT_MASK);

    /* Read current value of PCNTR1 register for the specified port */
    orig_value = p_ioport_regs->PCNTR1;

    /* High bits */
    set_bits = direction_values & mask;

    /*  Low bits */
    /* Cast to ensure size */
    clr_bits = (uint32_t) ((~direction_values) & mask);

    /* New value to write to port direction register */
    write_value  = orig_value;
    write_value |= set_bits;

    /* Clear bits as needed */
    write_value &= ~clr_bits;

    p_ioport_regs->PCNTR1 = write_value;

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
 *
 * @note This function is re-entrant for different ports.
 *
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortEventInputRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_event_data)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_event_data);
    uint32_t port_number = port >> IOPORT_PRV_PORT_OFFSET;
    FSP_ERROR_RETURN((BSP_FEATURE_IOPORT_ELC_PORTS & (1 << port_number)), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Get the port address */
    R_PORT0_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS(port >> IOPORT_PRV_PORT_OFFSET & IOPORT_PRV_8BIT_MASK);

    /* Read current value of EIDR value from PCNTR2 register for the specified port */
    *p_event_data = p_ioport_regs->PCNTR2_b.EIDR;

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
 *
 * @note This function is re-entrant.
 *
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinEventInputRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_event)
{
    ioport_size_t portvalue;
    ioport_size_t mask;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_pin_event);
    uint32_t port_number = pin >> IOPORT_PRV_PORT_OFFSET;
    FSP_ERROR_RETURN((BSP_FEATURE_IOPORT_ELC_PORTS & (1 << port_number)), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Get the port address */
    R_PORT0_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS((pin >> IOPORT_PRV_PORT_OFFSET) & IOPORT_PRV_8BIT_MASK);

    /* Read current value of EIDR value from PCNTR2 register for the specified port */
    portvalue = p_ioport_regs->PCNTR2_b.EIDR;
    mask      = (ioport_size_t) (1U << (IOPORT_PRV_PIN_BITS & (bsp_io_port_t) pin));

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
 *
 * @note This function is re-entrant for different ports.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortEventOutputWrite (ioport_ctrl_t * const p_ctrl,
                                         bsp_io_port_t         port,
                                         ioport_size_t         event_data,
                                         ioport_size_t         mask_value)
{
    ioport_size_t set_bits;
    ioport_size_t reset_bits;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(mask_value > (ioport_size_t) 0, FSP_ERR_INVALID_ARGUMENT);
    uint32_t port_number = port >> IOPORT_PRV_PORT_OFFSET;
    FSP_ERROR_RETURN((BSP_FEATURE_IOPORT_ELC_PORTS & (1 << port_number)), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    set_bits = event_data & mask_value;

    /* Cast to ensure size */
    reset_bits = (ioport_size_t) ((~event_data) & mask_value);

    /* Get the port address */
    R_PORT0_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS((port >> IOPORT_PRV_PORT_OFFSET) & IOPORT_PRV_8BIT_MASK);

    /* PCNTR4 register: lower word = set data, upper word = reset_data */
    p_ioport_regs->PCNTR4 = (uint32_t) (((uint32_t) reset_bits << 16) | set_bits);

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
 *
 * @note This function is re-entrant for different ports.
 *
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinEventOutputWrite (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t pin_value)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((pin_value == BSP_IO_LEVEL_HIGH) || (pin_value == BSP_IO_LEVEL_LOW), FSP_ERR_INVALID_ARGUMENT);
    uint32_t port_number = pin >> IOPORT_PRV_PORT_OFFSET;
    FSP_ERROR_RETURN((BSP_FEATURE_IOPORT_ELC_PORTS & (1 << port_number)), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    ioport_size_t set_bits;
    ioport_size_t reset_bits;
    bsp_io_port_t port;
    uint16_t      pin_to_port;

    /* Cast to ensure correct conversion of parameter. */
    pin_to_port = (uint16_t) pin;
    pin_to_port = pin_to_port & (uint16_t) IOPORT_PRV_PORT_BITS;
    port        = (bsp_io_port_t) pin_to_port;
    set_bits    = (ioport_size_t) 0;
    reset_bits  = (ioport_size_t) 0;

    if (BSP_IO_LEVEL_HIGH == pin_value)
    {
        /* Cast to ensure size */
        set_bits = (ioport_size_t) (1U << ((ioport_size_t) pin & IOPORT_PRV_PIN_BITS));
    }
    else
    {
        /* Cast to ensure size */
        reset_bits = (ioport_size_t) (1U << ((ioport_size_t) pin & IOPORT_PRV_PIN_BITS));
    }

    r_ioport_hw_pin_event_output_data_write(port, set_bits, reset_bits, pin_value);

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
#if BSP_FEATURE_SYSC_HAS_VBTICTLR || BSP_FEATURE_RTC_HAS_TCEN

    /* Handle any VBATT domain pin configuration. */
    bsp_vbatt_init(p_cfg);
#endif

    uint16_t       pin_count;
    ioport_cfg_t * p_pin_data;

    p_pin_data = (ioport_cfg_t *) p_cfg;

    R_BSP_PinAccessEnable();           // Protect PWPR from re-entrancy

    for (pin_count = 0U; pin_count < p_pin_data->number_of_pins; pin_count++)
    {
        r_ioport_pfs_write(p_pin_data->p_pin_cfg_data[pin_count].pin, p_pin_data->p_pin_cfg_data[pin_count].pin_cfg);
    }

    R_BSP_PinAccessDisable();
}

/*******************************************************************************************************************//**
 * Writes the set and clear values on a pin of the port when an ELC event occurs. This allows accurate timing of
 * pin output level.
 *
 * @param[in]    port           Port to read event data
 * @param[in]    set_value      Bit in the port to set high (1 = that bit will be set high)
 * @param[in]    reset_value    Bit in the port to clear low (1 = that bit will be cleared low)
 * @param[in]    pin_level      Event data for pin
 **********************************************************************************************************************/
static void r_ioport_hw_pin_event_output_data_write (bsp_io_port_t  port,
                                                     ioport_size_t  set_value,
                                                     ioport_size_t  reset_value,
                                                     bsp_io_level_t pin_level)
{
    uint32_t port_value = 0;

    /* Get the port address */
    R_PORT0_Type * p_ioport_regs = IOPORT_PRV_PORT_ADDRESS((port >> IOPORT_PRV_PORT_OFFSET) & IOPORT_PRV_8BIT_MASK);

    /* Read current value of PCNTR4 register */
    port_value = p_ioport_regs->PCNTR4;

    if (BSP_IO_LEVEL_HIGH == pin_level)
    {
        /* set value contains the bit to be set high (bit mask) */
        port_value |= (uint32_t) (set_value);

        /* reset value contains the mask to clear the corresponding bit in EOSR because both EOSR and EORR
         *  bit of a particular pin should not be high at the same time */
        port_value &= (((uint32_t) reset_value << 16) | IOPORT_PRV_16BIT_MASK);
    }
    else
    {
        /* reset_value contains the bit to be cleared low */
        port_value |= (uint32_t) reset_value << 16;

        /* set value contains the mask to clear the corresponding bit in EOSR because both EOSR and EORR bit of a
         *  particular pin should not be high at the same time */
        port_value &= (uint32_t) ((set_value | IOPORT_PRV_UPPER_16BIT_MASK));
    }

    p_ioport_regs->PCNTR4 = port_value;
}

/*******************************************************************************************************************//**
 * Writes to the specified pin's PFS register
 *
 * @param[in]    pin        Pin to write PFS data for
 * @param[in]    value      Value to be written to the PFS register
 *
 **********************************************************************************************************************/
static void r_ioport_pfs_write (bsp_io_port_pin_t pin, uint32_t value)
{
    /* PMR bits should be cleared before specifying PSEL. Reference section "20.7 Notes on the PmnPFS Register Setting"
     * in the RA6M3 manual R01UH0886EJ0100. */
    if ((value & IOPORT_PRV_PERIPHERAL_FUNCTION) > 0)
    {
        /* Clear PMR */
        R_PFS->PORT[pin >> IOPORT_PRV_PORT_OFFSET].PIN[pin & BSP_IO_PRV_8BIT_MASK].PmnPFS_b.PMR = 0;

        /* New config with PMR = 0 */
        R_PFS->PORT[pin >> IOPORT_PRV_PORT_OFFSET].PIN[pin &
                                                       BSP_IO_PRV_8BIT_MASK].PmnPFS =
            (value & ~((uint32_t) IOPORT_PRV_PERIPHERAL_FUNCTION));
    }

    /* Write configuration */
    R_PFS->PORT[pin >> IOPORT_PRV_PORT_OFFSET].PIN[pin & BSP_IO_PRV_8BIT_MASK].PmnPFS = value;
}

#if BSP_FEATURE_SYSC_HAS_VBTICTLR || BSP_FEATURE_RTC_HAS_TCEN

/*******************************************************************************************************************//**
 * @brief Initializes VBTICTLR register based on pin configuration.
 *
 * The VBTICTLR register may need to be modified based on the project's pin configuration. There is a set of pins that
 * needs to be checked. If one of these pins is found in the pin configuration table then it will be tested to see if
 * the appropriate VBTICTLR bit needs to be set or cleared. If one of the pins that is being searched for is not found
 * then the accompanying VBTICTLR bit is left as-is.
 **********************************************************************************************************************/
static void bsp_vbatt_init (ioport_cfg_t const * const p_pin_cfg)
{
    uint32_t pin_index;
    uint32_t vbatt_index;

 #if BSP_FEATURE_SYSC_HAS_VBTICTLR
    R_SYSTEM_Type * p_system = R_SYSTEM;
 #endif
 #if BSP_FEATURE_RTC_HAS_TCEN
    R_RTC_Type * p_rtc = R_RTC;
 #endif

 #if BSP_TZ_SECURE_BUILD && BSP_FEATURE_TZ_NS_OFFSET > 0
  #if BSP_FEATURE_SYSC_HAS_VBTICTLR
    if (1 == R_SYSTEM->BBFSAR_b.NONSEC2)
    {
        /* If security attribution of VBTICTLR is set to non-secure, then use the non-secure alias. */
        p_system = (R_SYSTEM_Type *) ((uint32_t) p_system | BSP_FEATURE_TZ_NS_OFFSET);
    }
  #endif

  #if BSP_FEATURE_RTC_HAS_TCEN
    if (1 == R_PSCU->PSARE_b.PSARE2)
    {
        /* If security attribution of RTC is set to non-secure, then use the non-secure alias. */
        p_rtc = (R_RTC_Type *) ((uint32_t) p_rtc | BSP_FEATURE_TZ_NS_OFFSET);
    }
  #endif
 #endif

    /* Must loop over all pins as pin configuration table is unordered. */
    for (pin_index = 0U; pin_index < p_pin_cfg->number_of_pins; pin_index++)
    {
        /* Loop over VBATT input pins. */
        for (vbatt_index = 0U;
             vbatt_index < (sizeof(g_vbatt_pins_input) / sizeof(g_vbatt_pins_input[0]));
             vbatt_index++)
        {
            if (p_pin_cfg->p_pin_cfg_data[pin_index].pin == g_vbatt_pins_input[vbatt_index])
            {
                /* Get PSEL value for pin. */
                uint32_t pfs_psel_value = p_pin_cfg->p_pin_cfg_data[pin_index].pin_cfg & BSP_PRV_PFS_PSEL_MASK;

                /* Check if pin is being used for RTC or AGT use. */
                if ((IOPORT_PERIPHERAL_AGT == pfs_psel_value) || (IOPORT_PERIPHERAL_CLKOUT_COMP_RTC == pfs_psel_value))
                {
                    /* Bit should be set to 1. */
 #if BSP_FEATURE_SYSC_HAS_VBTICTLR
  #if BSP_TZ_NONSECURE_BUILD
                    if (0 == R_SYSTEM->BBFSAR_b.NONSEC2)
                    {
                        /* Do nothing: non secure build can't configure secure VBTICTLR register. */
                    }
                    else
  #endif
                    if (0 == (p_system->VBTICTLR & (uint8_t) (1U << vbatt_index)))
                    {
                        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);
                        p_system->VBTICTLR |= (uint8_t) (1U << vbatt_index);
                        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);
                    }
                    else
                    {
                        /* Do nothing: it is already enabled. */
                    }
 #endif
 #if BSP_FEATURE_RTC_HAS_TCEN
  #if BSP_TZ_NONSECURE_BUILD
                    if (0 == R_PSCU->PSARE_b.PSARE2)
                    {
                        /* Do nothing: non secure build can't configure secure RTC registers. */
                    }
                    else
  #endif
                    {
                        if (0 == p_rtc->RTCCR[vbatt_index].RTCCR_b.TCEN)
                        {
                            p_rtc->RTCCR[vbatt_index].RTCCR_b.TCEN = 1;
                            R_BSP_SoftwareDelay(BSP_PRV_RTC_RESET_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
                        }
                        else
                        {
                            /* Do nothing: it is already enabled. */
                        }
                    }
 #endif
                }
                else
                {
                    /* Bit should be cleared to 0. */
 #if BSP_FEATURE_SYSC_HAS_VBTICTLR
  #if BSP_TZ_NONSECURE_BUILD
                    if (0 == R_SYSTEM->BBFSAR_b.NONSEC2)
                    {
                        /* Do nothing: non secure build can't configure secure VBTICTLR register. */
                    }
                    else
  #endif
                    if ((p_system->VBTICTLR & (uint8_t) (1U << vbatt_index)) > 0)
                    {
                        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);
                        p_system->VBTICTLR &= (uint8_t) ~(1U << vbatt_index);
                        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);
                    }
                    else
                    {
                        /* Do nothing: it is already disabled. */
                    }
 #endif
 #if BSP_FEATURE_RTC_HAS_TCEN
  #if BSP_TZ_NONSECURE_BUILD
                    if (0 == R_PSCU->PSARE_b.PSARE2)
                    {
                        /* Do nothing: non secure build can't configure secure RTC registers. */
                    }
                    else
  #endif
                    {
                        if (p_rtc->RTCCR[vbatt_index].RTCCR_b.TCEN > 0)
                        {
                            p_rtc->RTCCR[vbatt_index].RTCCR_b.TCEN = 0;
                            R_BSP_SoftwareDelay(BSP_PRV_RTC_RESET_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
                        }
                        else
                        {
                            /* Do nothing: it is already disabled. */
                        }
                    }
 #endif
                }
            }
        }
    }
}

#endif
