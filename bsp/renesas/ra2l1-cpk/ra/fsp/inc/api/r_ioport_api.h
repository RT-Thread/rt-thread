/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup IOPORT_API I/O Port Interface
 * @brief Interface  for accessing I/O ports and configuring I/O functionality.
 *
 * @section IOPORT_API_SUMMARY Summary
 * The IOPort shared interface provides the ability to access the IOPorts of a device at both bit and port level.
 * Port and pin direction can be changed.
 *
 * IOPORT Interface description: @ref IOPORT
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_IOPORT_API_H
#define R_IOPORT_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common error codes and definitions. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Private definition to set enumeration values. */
#define IOPORT_PRV_PFS_PSEL_OFFSET    (24)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** IO port type used with ports */
typedef uint16_t ioport_size_t;        ///< IO port size on this device

/** Superset of all peripheral functions.  */
typedef enum e_ioport_peripheral
{
    /** Pin will functions as an IO pin */
    IOPORT_PERIPHERAL_IO = 0x00,

    /** Pin will function as a DEBUG pin */
    IOPORT_PERIPHERAL_DEBUG = (0x00UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an AGT peripheral pin */
    IOPORT_PERIPHERAL_AGT = (0x01UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT0 = (0x02UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT1 = (0x03UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI peripheral pin */
    IOPORT_PERIPHERAL_SCI0_2_4_6_8 = (0x04UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI peripheral pin */
    IOPORT_PERIPHERAL_SCI1_3_5_7_9 = (0x05UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a SPI peripheral pin */
    IOPORT_PERIPHERAL_SPI = (0x06UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a IIC peripheral pin */
    IOPORT_PERIPHERAL_IIC = (0x07UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a KEY peripheral pin */
    IOPORT_PERIPHERAL_KEY = (0x08UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a clock/comparator/RTC peripheral pin */
    IOPORT_PERIPHERAL_CLKOUT_COMP_RTC = (0x09UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAC/ADC peripheral pin */
    IOPORT_PERIPHERAL_CAC_AD = (0x0AUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a BUS peripheral pin */
    IOPORT_PERIPHERAL_BUS = (0x0BUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CTSU peripheral pin */
    IOPORT_PERIPHERAL_CTSU = (0x0CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CMPHS peripheral pin */
    IOPORT_PERIPHERAL_ACMPHS = (0x0CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a segment LCD peripheral pin */
    IOPORT_PERIPHERAL_LCDC = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI peripheral DEn pin */
    IOPORT_PERIPHERAL_DE_SCI1_3_5_7_9 = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a DALI peripheral pin */
    IOPORT_PERIPHERAL_DALI = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI DEn peripheral pin */
    IOPORT_PERIPHERAL_DE_SCI0_2_4_6_8 = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAN peripheral pin */
    IOPORT_PERIPHERAL_CAN = (0x10UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a QSPI peripheral pin */
    IOPORT_PERIPHERAL_QSPI = (0x11UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SSI peripheral pin */
    IOPORT_PERIPHERAL_SSI = (0x12UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a USB full speed peripheral pin */
    IOPORT_PERIPHERAL_USB_FS = (0x13UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a USB high speed peripheral pin */
    IOPORT_PERIPHERAL_USB_HS = (0x14UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT2 = (0x14UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SD/MMC peripheral pin */
    IOPORT_PERIPHERAL_SDHI_MMC = (0x15UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT3 = (0x15UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an Ethernet MMI peripheral pin */
    IOPORT_PERIPHERAL_ETHER_MII = (0x16UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT4 = (0x16UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an Ethernet RMMI peripheral pin */
    IOPORT_PERIPHERAL_ETHER_RMII = (0x17UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PDC peripheral pin */
    IOPORT_PERIPHERAL_PDC = (0x18UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a graphics LCD peripheral pin */
    IOPORT_PERIPHERAL_LCD_GRAPHICS = (0x19UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAC peripheral pin */
    IOPORT_PERIPHERAL_CAC = (0x19UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a debug trace peripheral pin */
    IOPORT_PERIPHERAL_TRACE = (0x1AUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a OSPI peripheral pin */
    IOPORT_PERIPHERAL_OSPI = (0x1CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CEC peripheral pin */
    IOPORT_PERIPHERAL_CEC = (0x1DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PGAOUT peripheral pin */
    IOPORT_PERIPHERAL_PGAOUT0 = (0x1DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PGAOUT peripheral pin */
    IOPORT_PERIPHERAL_PGAOUT1 = (0x1EUL << IOPORT_PRV_PFS_PSEL_OFFSET),
} ioport_peripheral_t;

/* DEPRECATED Superset of Ethernet channels. */
typedef enum e_ioport_eth_ch
{
    IOPORT_ETHERNET_CHANNEL_0 = 0x10,  ///< Used to select Ethernet channel 0
    IOPORT_ETHERNET_CHANNEL_1 = 0x20,  ///< Used to select Ethernet channel 1
    IOPORT_ETHERNET_CHANNEL_END        ///< Marks end of enum - used by parameter checking
} ioport_ethernet_channel_t;

/* DEPRECATED Superset of Ethernet PHY modes. */
typedef enum e_ioport_eth_mode
{
    IOPORT_ETHERNET_MODE_RMII = 0x00,  ///< Ethernet PHY mode set to MII
    IOPORT_ETHERNET_MODE_MII  = 0x10,  ///< Ethernet PHY mode set to RMII
    IOPORT_ETHERNET_MODE_END           ///< Marks end of enum - used by parameter checking
} ioport_ethernet_mode_t;

/** Options to configure pin functions  */
typedef enum e_ioport_cfg_options
{
    IOPORT_CFG_PORT_DIRECTION_INPUT  = 0x00000000, ///< Sets the pin direction to input (default)
    IOPORT_CFG_PORT_DIRECTION_OUTPUT = 0x00000004, ///< Sets the pin direction to output
    IOPORT_CFG_PORT_OUTPUT_LOW       = 0x00000000, ///< Sets the pin level to low
    IOPORT_CFG_PORT_OUTPUT_HIGH      = 0x00000001, ///< Sets the pin level to high
    IOPORT_CFG_PULLUP_ENABLE         = 0x00000010, ///< Enables the pin's internal pull-up
    IOPORT_CFG_PIM_TTL               = 0x00000020, ///< Enables the pin's input mode
    IOPORT_CFG_NMOS_ENABLE           = 0x00000040, ///< Enables the pin's NMOS open-drain output
    IOPORT_CFG_PMOS_ENABLE           = 0x00000080, ///< Enables the pin's PMOS open-drain ouput
    IOPORT_CFG_DRIVE_MID             = 0x00000400, ///< Sets pin drive output to medium
    IOPORT_CFG_DRIVE_HS_HIGH         = 0x00000800, ///< Sets pin drive output to high along with supporting high speed
    IOPORT_CFG_DRIVE_MID_IIC         = 0x00000C00, ///< Sets pin to drive output needed for IIC on a 20mA port
    IOPORT_CFG_DRIVE_HIGH            = 0x00000C00, ///< Sets pin drive output to high
    IOPORT_CFG_EVENT_RISING_EDGE     = 0x00001000, ///< Sets pin event trigger to rising edge
    IOPORT_CFG_EVENT_FALLING_EDGE    = 0x00002000, ///< Sets pin event trigger to falling edge
    IOPORT_CFG_EVENT_BOTH_EDGES      = 0x00003000, ///< Sets pin event trigger to both edges
    IOPORT_CFG_IRQ_ENABLE            = 0x00004000, ///< Sets pin as an IRQ pin
    IOPORT_CFG_ANALOG_ENABLE         = 0x00008000, ///< Enables pin to operate as an analog pin
    IOPORT_CFG_PERIPHERAL_PIN        = 0x00010000  ///< Enables pin to operate as a peripheral pin
} ioport_cfg_options_t;

/* PFS writing enable/disable. */
typedef enum e_ioport_pwpr
{
    IOPORT_PFS_WRITE_DISABLE = 0,      ///< Disable PFS write access
    IOPORT_PFS_WRITE_ENABLE  = 1       ///< Enable PFS write access
} ioport_pwpr_t;

/** Pin identifier and pin PFS pin configuration value */
typedef struct st_ioport_pin_cfg
{
    uint32_t          pin_cfg;         ///< Pin PFS configuration - Use ioport_cfg_options_t parameters to configure
    bsp_io_port_pin_t pin;             ///< Pin identifier
} ioport_pin_cfg_t;

/** Multiple pin configuration data for loading into PFS registers by R_IOPORT_Init()  */
typedef struct st_ioport_cfg
{
    uint16_t                 number_of_pins; ///< Number of pins for which there is configuration data
    ioport_pin_cfg_t const * p_pin_cfg_data; ///< Pin configuration data
} ioport_cfg_t;

/** IOPORT control block.  Allocate an instance specific control block to pass into the IOPORT API calls.
 * @par Implemented as
 * - ioport_instance_ctrl_t
 */
typedef void ioport_ctrl_t;

/** IOPort driver structure. IOPort functions implemented at the HAL layer will follow this API. */
typedef struct st_ioport_api
{
    /** Initialize internal driver data and initial pin configurations.  Called during startup.  Do
     * not call this API during runtime.  Use @ref ioport_api_t::pinsCfg for runtime reconfiguration of
     * multiple pins.
     * @par Implemented as
     * - @ref R_IOPORT_Open()
     * @param[in]  p_cfg                Pointer to pin configuration data array.
     */
    fsp_err_t (* open)(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);

    /** Close the API.
     * @par Implemented as
     * - @ref R_IOPORT_Close()
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     **/
    fsp_err_t (* close)(ioport_ctrl_t * const p_ctrl);

    /** Configure multiple pins.
     * @par Implemented as
     * - @ref R_IOPORT_PinsCfg()
     * @param[in]  p_cfg                Pointer to pin configuration data array.
     */
    fsp_err_t (* pinsCfg)(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);

    /** Configure settings for an individual pin.
     * @par Implemented as
     * - @ref R_IOPORT_PinCfg()
     * @param[in]  pin                  Pin to be read.
     * @param[in]  cfg                  Configuration options for the pin.
     */
    fsp_err_t (* pinCfg)(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg);

    /** Read the event input data of the specified pin and return the level.
     * @par Implemented as
     * - @ref R_IOPORT_PinEventInputRead()
     * @param[in]  pin                  Pin to be read.
     * @param[in]  p_pin_event         Pointer to return the event data.
     */
    fsp_err_t (* pinEventInputRead)(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_event);

    /** Write pin event data.
     * @par Implemented as
     * - @ref R_IOPORT_PinEventOutputWrite()
     * @param[in]  pin                  Pin event data is to be written to.
     * @param[in]  pin_value            Level to be written to pin output event.
     */
    fsp_err_t (* pinEventOutputWrite)(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t pin_value);

    /* DEPRECATED Configure the PHY mode of the Ethernet channels.
     * @par Implemented as
     * - @ref R_IOPORT_EthernetModeCfg()
     * @param[in]  channel              Channel configuration will be set for.
     * @param[in]  mode                 PHY mode to set the channel to.
     */
    fsp_err_t (* pinEthernetModeCfg)(ioport_ctrl_t * const p_ctrl, ioport_ethernet_channel_t channel,
                                     ioport_ethernet_mode_t mode);

    /** Read level of a pin.
     * @par Implemented as
     * - @ref R_IOPORT_PinRead()
     * @param[in]  pin                  Pin to be read.
     * @param[in]  p_pin_value          Pointer to return the pin level.
     */
    fsp_err_t (* pinRead)(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value);

    /** Write specified level to a pin.
     * @par Implemented as
     * - @ref R_IOPORT_PinWrite()
     * @param[in]  pin                  Pin to be written to.
     * @param[in]  level                State to be written to the pin.
     */
    fsp_err_t (* pinWrite)(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t level);

    /** Set the direction of one or more pins on a port.
     * @par Implemented as
     * - @ref R_IOPORT_PortDirectionSet()
     * @param[in]  port                 Port being configured.
     * @param[in]  direction_values     Value controlling direction of pins on port (1 - output, 0 - input).
     * @param[in]  mask                 Mask controlling which pins on the port are to be configured.
     */
    fsp_err_t (* portDirectionSet)(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t direction_values,
                                   ioport_size_t mask);

    /** Read captured event data for a port.
     * @par Implemented as
     * - @ref R_IOPORT_PortEventInputRead()
     * @param[in]  port                 Port to be read.
     * @param[in]  p_event_data         Pointer to return the event data.
     */
    fsp_err_t (* portEventInputRead)(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_event_data);

    /** Write event output data for a port.
     * @par Implemented as
     * - @ref R_IOPORT_PortEventOutputWrite()
     * @param[in]  port                 Port event data will be written to.
     * @param[in]  event_data           Data to be written as event data to specified port.
     * @param[in]  mask_value           Each bit set to 1 in the mask corresponds to that bit's value in event data.
     * being written to port.
     */
    fsp_err_t (* portEventOutputWrite)(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t event_data,
                                       ioport_size_t mask_value);

    /** Read states of pins on the specified port.
     * @par Implemented as
     * - @ref R_IOPORT_PortRead()
     * @param[in]  port                 Port to be read.
     * @param[in]  p_port_value         Pointer to return the port value.
     */
    fsp_err_t (* portRead)(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_port_value);

    /** Write to multiple pins on a port.
     * @par Implemented as
     * - @ref R_IOPORT_PortWrite()
     * @param[in]  port                 Port to be written to.
     * @param[in]  value                Value to be written to the port.
     * @param[in]  mask                 Mask controlling which pins on the port are written to.
     */
    fsp_err_t (* portWrite)(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t value, ioport_size_t mask);
} ioport_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ioport_instance
{
    ioport_ctrl_t      * p_ctrl;       ///< Pointer to the control structure for this instance
    ioport_cfg_t const * p_cfg;        ///< Pointer to the configuration structure for this instance
    ioport_api_t const * p_api;        ///< Pointer to the API structure for this instance
} ioport_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup IOPORT_API)
 **********************************************************************************************************************/
