/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @defgroup BSP_IO BSP I/O access
 * @ingroup RENESAS_COMMON
 * @brief This module provides basic read/write access to port pins.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BSP_IO_H
#define BSP_IO_H

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/

/* Gets MCU configuration information. */
#include "bsp_api.h"

#if BSP_MCU_GROUP_RA6B1
 #include "../ra6b1/bsp_io.h"
#elif BSP_MCU_GROUP_RA6U1
 #include "../ra6u1/bsp_io.h"
#elif BSP_MCU_GROUP_RA6B2
 #include "../ra6b2/bsp_io.h"
#elif BSP_MCU_GROUP_RA6W1
 #include "../ra6w1/bsp_io.h"
#elif BSP_MCU_GROUP_RA6W3
 #include "../ra6w3/bsp_io.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define BSP_IO_PORT_BITS      (0xC0U)
#define BSP_IO_PIN_BITS       (0x3FU)

/* Shift to get port in bsp_io_port_t and bsp_io_port_pin_t enums. */
#define BSP_IO_PORT_OFFSET    (6U)

#define BSP_IO_PXX_MODE_REG(_port, _pin)                                            \
    *(&(GPIO->P0_00_MODE_REG) + (((_port) == 0) ? 0 :                               \
                                 ((_port) == 1) ? BSP_FEATURE_IO_PORT0_GPIO_COUNT : \
                                 BSP_FEATURE_IO_PORT0_GPIO_COUNT + BSP_FEATURE_IO_PORT1_GPIO_COUNT) + (_pin))

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Levels that can be set and read for individual pins */
typedef enum e_bsp_io_level
{
    BSP_IO_LEVEL_LOW = 0,              ///< Low
    BSP_IO_LEVEL_HIGH                  ///< High
} bsp_io_level_t;

/** Direction of individual pins */
typedef enum e_bsp_io_dir
{
    BSP_IO_DIRECTION_INPUT  = 0x0,     ///< Input
    BSP_IO_DIRECTION_OUTPUT = 0x300,   ///< Output
} bsp_io_direction_t;

/** Superset list of all possible IO ports. */
typedef enum e_bsp_io_port
{
    BSP_IO_PORT_00 = 0x00,             ///< IO port 0
    BSP_IO_PORT_01 = 0x01,             ///< IO port 1
    BSP_IO_PORT_02 = 0x02,             ///< IO port 2

    /** Marks end of enum */
    BSP_IO_PORT_MAX,
} bsp_io_port_t;

/** Superset list of all possible IO port pins. */
typedef enum e_bsp_io_port_pin_t
{
    BSP_IO_PORT_00_PIN_00 = 0x00,      ///< IO port 0 pin 0
    BSP_IO_PORT_00_PIN_01 = 0x01,      ///< IO port 0 pin 1
    BSP_IO_PORT_00_PIN_02 = 0x02,      ///< IO port 0 pin 2
    BSP_IO_PORT_00_PIN_03 = 0x03,      ///< IO port 0 pin 3
    BSP_IO_PORT_00_PIN_04 = 0x04,      ///< IO port 0 pin 4
    BSP_IO_PORT_00_PIN_05 = 0x05,      ///< IO port 0 pin 5
    BSP_IO_PORT_00_PIN_06 = 0x06,      ///< IO port 0 pin 6
    BSP_IO_PORT_00_PIN_07 = 0x07,      ///< IO port 0 pin 7
    BSP_IO_PORT_00_PIN_08 = 0x08,      ///< IO port 0 pin 8
    BSP_IO_PORT_00_PIN_09 = 0x09,      ///< IO port 0 pin 9
    BSP_IO_PORT_00_PIN_10 = 0x0A,      ///< IO port 0 pin 10
    BSP_IO_PORT_00_PIN_11 = 0x0B,      ///< IO port 0 pin 11
    BSP_IO_PORT_00_PIN_12 = 0x0C,      ///< IO port 0 pin 12
    BSP_IO_PORT_00_PIN_13 = 0x0D,      ///< IO port 0 pin 13
    BSP_IO_PORT_00_PIN_14 = 0x0E,      ///< IO port 0 pin 14
    BSP_IO_PORT_00_PIN_15 = 0x0F,      ///< IO port 0 pin 15
    BSP_IO_PORT_00_PIN_16 = 0x10,      ///< IO port 0 pin 16
    BSP_IO_PORT_00_PIN_17 = 0x11,      ///< IO port 0 pin 17
    BSP_IO_PORT_00_PIN_18 = 0x12,      ///< IO port 0 pin 18
    BSP_IO_PORT_00_PIN_19 = 0x13,      ///< IO port 0 pin 19
    BSP_IO_PORT_00_PIN_20 = 0x14,      ///< IO port 0 pin 20
    BSP_IO_PORT_00_PIN_21 = 0x15,      ///< IO port 0 pin 21
    BSP_IO_PORT_00_PIN_22 = 0x16,      ///< IO port 0 pin 22
    BSP_IO_PORT_00_PIN_23 = 0x17,      ///< IO port 0 pin 23
    BSP_IO_PORT_00_PIN_24 = 0x18,      ///< IO port 0 pin 24
    BSP_IO_PORT_00_PIN_25 = 0x19,      ///< IO port 0 pin 25
    BSP_IO_PORT_00_PIN_26 = 0x1A,      ///< IO port 0 pin 26
    BSP_IO_PORT_00_PIN_27 = 0x1B,      ///< IO port 0 pin 27
    BSP_IO_PORT_00_PIN_28 = 0x1C,      ///< IO port 0 pin 28
    BSP_IO_PORT_00_PIN_29 = 0x1D,      ///< IO port 0 pin 29
    BSP_IO_PORT_00_PIN_30 = 0x1E,      ///< IO port 0 pin 30
    BSP_IO_PORT_00_PIN_31 = 0x1F,      ///< IO port 0 pin 31
    BSP_IO_PORT_01_PIN_00 = 0x40,      ///< IO port 1 pin 0
    BSP_IO_PORT_01_PIN_01 = 0x41,      ///< IO port 1 pin 1
    BSP_IO_PORT_01_PIN_02 = 0x42,      ///< IO port 1 pin 2
    BSP_IO_PORT_01_PIN_03 = 0x43,      ///< IO port 1 pin 3
    BSP_IO_PORT_01_PIN_04 = 0x44,      ///< IO port 1 pin 4
    BSP_IO_PORT_01_PIN_05 = 0x45,      ///< IO port 1 pin 5
    BSP_IO_PORT_01_PIN_06 = 0x46,      ///< IO port 1 pin 6
    BSP_IO_PORT_01_PIN_07 = 0x47,      ///< IO port 1 pin 7
    BSP_IO_PORT_01_PIN_08 = 0x48,      ///< IO port 1 pin 8
    BSP_IO_PORT_01_PIN_09 = 0x49,      ///< IO port 1 pin 9
    BSP_IO_PORT_01_PIN_10 = 0x4A,      ///< IO port 1 pin 10
    BSP_IO_PORT_01_PIN_11 = 0x4B,      ///< IO port 1 pin 11
    BSP_IO_PORT_01_PIN_12 = 0x4C,      ///< IO port 1 pin 12
    BSP_IO_PORT_01_PIN_13 = 0x4D,      ///< IO port 1 pin 13
    BSP_IO_PORT_01_PIN_14 = 0x4E,      ///< IO port 1 pin 14
    BSP_IO_PORT_01_PIN_15 = 0x4F,      ///< IO port 1 pin 15
    BSP_IO_PORT_01_PIN_16 = 0x50,      ///< IO port 1 pin 16
    BSP_IO_PORT_01_PIN_17 = 0x51,      ///< IO port 1 pin 17

    BSP_IO_PORT_02_PIN_00 = 0x80,      ///< IO port 2 pin 0
    BSP_IO_PORT_02_PIN_01 = 0x81,      ///< IO port 2 pin 1
    BSP_IO_PORT_02_PIN_02 = 0x82,      ///< IO port 2 pin 2
    BSP_IO_PORT_02_PIN_03 = 0x83,      ///< IO port 2 pin 3
    BSP_IO_PORT_02_PIN_04 = 0x84,      ///< IO port 2 pin 4
    BSP_IO_PORT_02_PIN_05 = 0x85,      ///< IO port 2 pin 5
    BSP_IO_PORT_02_PIN_06 = 0x86,      ///< IO port 2 pin 6
    BSP_IO_PORT_02_PIN_07 = 0x87,      ///< IO port 2 pin 7
    BSP_IO_PORT_02_PIN_08 = 0x88,      ///< IO port 2 pin 8
    BSP_IO_PORT_02_PIN_09 = 0x89,      ///< IO port 2 pin 9
    BSP_IO_PORT_02_PIN_10 = 0x8A,      ///< IO port 2 pin 10
    BSP_IO_PORT_02_PIN_11 = 0x8B,      ///< IO port 2 pin 11
    BSP_IO_PORT_02_PIN_12 = 0x8C,      ///< IO port 2 pin 12

    /* TIN-TODO: Only used in Tin, remove if possible. */
    BSP_IO_PORT_FF_PIN_FF = 0xFF,      ///< Invalid IO port
} bsp_io_port_pin_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Read the current input level of the pin.
 *
 * @param[in]  pin             The pin
 *
 * @retval     Current input level
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_BSP_PinRead (bsp_io_port_pin_t pin)
{
    uint32_t         pin_id = pin & BSP_IO_PIN_BITS;
    uint32_t         port   = pin >> BSP_IO_PORT_OFFSET;
    __IOM uint32_t * reg    = &(GPIO->P0_DATA_REG) + port;

    return ((*reg) >> pin_id) & 1U;
}

/*******************************************************************************************************************//**
 * Set a pin to output and set the output level to the level provided.
 *
 * @param[in]  pin      The pin
 * @param[in]  level    The level
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinWrite (bsp_io_port_pin_t pin, bsp_io_level_t level)
{
    uint32_t         pin_id = pin & BSP_IO_PIN_BITS;
    uint32_t         port   = pin >> BSP_IO_PORT_OFFSET;
    __IOM uint32_t * reg;
#if !defined(BSP_MCU_GROUP_RA6W1)      // TIN-TODO: Unify R_BSP_PinWrite()
    BSP_IO_PXX_MODE_REG(port, pin_id) = GPIO_W_CFG_PORT_DIRECTION_OUTPUT;
#endif

    if (BSP_IO_LEVEL_LOW == level)
    {
        reg = &(GPIO->P0_RESET_DATA_REG) + port;
    }
    else
    {
        reg = &(GPIO->P0_SET_DATA_REG) + port;
    }

    *reg = 1 << pin_id;
}

/*******************************************************************************************************************//**
 * Configure a pin.
 *
 * @param[in]  pin      The pin
 * @param[in]  cfg      Configuration for the pin
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinCfg (bsp_io_port_pin_t pin, uint32_t cfg)
{
    uint32_t pin_id = pin & BSP_IO_PIN_BITS;
    uint32_t port   = pin >> BSP_IO_PORT_OFFSET;

#if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
    if (BSP_IO_PORT_01 == port)
    {
        PMU_ANA->POWER_CTRL_REG_b.EN_HSGND = 1;
        FSP_HARDWARE_REGISTER_WAIT(PMU_ANA->ANA_STATUS_REG_b.HSGND_OK, 1U);
    }
#endif

    BSP_IO_PXX_MODE_REG(port, pin_id) = cfg;
}

/*******************************************************************************************************************//**
 * Enable access to the PFS registers. Uses a reference counter to protect against interrupts that could occur
 * via multiple threads or an ISR re-entering this code.
 *
 * @note: The DA HW does not provide such protection, so this function is a NOP.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinAccessEnable (void)
{
#if BSP_CFG_PFS_PROTECT

    /* Nothing to do. */
#endif
}

/*******************************************************************************************************************//**
 * Disable access to the PFS registers. Uses a reference counter to protect against interrupts that could occur via
 * multiple threads or an ISR re-entering this code.
 *
 * @note: The DA HW does not provide such protection, so this function is a NOP.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinAccessDisable (void)
{
#if BSP_CFG_PFS_PROTECT

    /* Nothing to do. */
#endif
}

#if BSP_FEATURE_IO_HAS_LATCHING

/*******************************************************************************************************************//**
 * Isolate pads, by disabling the latches of all GPIOs
 *
 * @note    Effectively, the GPIO pads are disconnected from their internal drives and retain their
 *          current level.
 **********************************************************************************************************************/
__STATIC_INLINE void bsp_io_pads_isolation_enable_all (void)
{
    CRG_TOP->P0_RESET_PAD_LATCH_REG = CRG_TOP_P0_RESET_PAD_LATCH_REG_P0_RESET_LATCH_OPEN_Msk;
    CRG_TOP->P1_RESET_PAD_LATCH_REG = CRG_TOP_P1_RESET_PAD_LATCH_REG_P1_RESET_LATCH_OPEN_Msk;
 #ifdef CRG_TOP_P2_RESET_PAD_LATCH_REG_P2_RESET_LATCH_OPEN_Msk
    CRG_TOP->P2_RESET_PAD_LATCH_REG = CRG_TOP_P2_RESET_PAD_LATCH_REG_P2_RESET_LATCH_OPEN_Msk;
 #endif
}

/*******************************************************************************************************************//**
 * De-isolate pads, by enabling the latches of all GPIOs
 *
 * @note    Effectively, the GPIO pads are connected to their internal drives
 **********************************************************************************************************************/
__STATIC_INLINE void bsp_io_pads_isolation_disable_all (void)
{
    CRG_TOP->P0_SET_PAD_LATCH_REG = CRG_TOP_P0_SET_PAD_LATCH_REG_P0_SET_LATCH_OPEN_Msk;
    CRG_TOP->P1_SET_PAD_LATCH_REG = CRG_TOP_P1_SET_PAD_LATCH_REG_P1_SET_LATCH_OPEN_Msk;
 #ifdef CRG_TOP_P2_SET_PAD_LATCH_REG_P2_SET_LATCH_OPEN_Msk
    CRG_TOP->P2_SET_PAD_LATCH_REG = CRG_TOP_P2_SET_PAD_LATCH_REG_P2_SET_LATCH_OPEN_Msk;
 #endif
}

/*******************************************************************************************************************//**
 * Disables the latch for the specific gpio.
 *
 * @param [in] pin The GPIO pin to unlatch
 ***********************************************************************************************************************/
__STATIC_INLINE void bsp_io_pad_isolation_enable (bsp_io_port_pin_t pin)
{
    bsp_io_port_pin_t pin_id  = (bsp_io_port_pin_t) (BSP_IO_PIN_BITS & (uint16_t) pin);
    bsp_io_port_t     port_id =
        (bsp_io_port_t) ((BSP_IO_PORT_BITS & (uint16_t) pin) >> BSP_IO_PORT_OFFSET);

    if (BSP_IO_PORT_00 == port_id)
    {
        BSP_CHECK_DEBUG(pin_id < BSP_FEATURE_IO_PORT0_GPIO_COUNT);
        CRG_TOP->P0_RESET_PAD_LATCH_REG = 1 << pin_id;
    }
    else if (BSP_IO_PORT_01 == port_id)
    {
        BSP_CHECK_DEBUG(pin_id < BSP_FEATURE_IO_PORT1_GPIO_COUNT);
        CRG_TOP->P1_RESET_PAD_LATCH_REG = 1 << pin_id;
    }

 #if BSP_FEATURE_IO_PORT2_GPIO_COUNT > 0
    else if (BSP_IO_PORT_02 == port_id)
    {
        BSP_CHECK_DEBUG(pin_id < BSP_FEATURE_IO_PORT2_GPIO_COUNT);
        CRG_TOP->P2_RESET_PAD_LATCH_REG = 1 << pin_id;
    }
 #endif
    else
    {
        /* Invalid port_id. */
        BSP_CHECK_DEBUG(0);
    }
}

/*******************************************************************************************************************//**
 * Enables the latch for the specific gpio.
 *
 * @param[in] pin The GPIO pin to latch
 **********************************************************************************************************************/
__STATIC_INLINE void bsp_io_pad_isolation_disable (bsp_io_port_pin_t pin)
{
    bsp_io_port_pin_t pin_id  = (bsp_io_port_pin_t) (BSP_IO_PIN_BITS & (uint16_t) pin);
    bsp_io_port_t     port_id =
        (bsp_io_port_t) ((BSP_IO_PORT_BITS & (uint16_t) pin) >> BSP_IO_PORT_OFFSET);

    if (BSP_IO_PORT_00 == port_id)
    {
        BSP_CHECK_DEBUG(pin_id < BSP_FEATURE_IO_PORT0_GPIO_COUNT);
        CRG_TOP->P0_SET_PAD_LATCH_REG = 1 << pin_id;
    }
    else if (BSP_IO_PORT_01 == port_id)
    {
        BSP_CHECK_DEBUG(pin_id < BSP_FEATURE_IO_PORT1_GPIO_COUNT);
        CRG_TOP->P1_SET_PAD_LATCH_REG = 1 << pin_id;
    }

 #if BSP_FEATURE_IO_PORT2_GPIO_COUNT > 0
    else if (BSP_IO_PORT_02 == port_id)
    {
        BSP_CHECK_DEBUG(pin_id < BSP_FEATURE_IO_PORT2_GPIO_COUNT);
        CRG_TOP->P2_SET_PAD_LATCH_REG = 1 << pin_id;
    }
 #endif
    else
    {
        /* Invalid port_id. */
        BSP_CHECK_DEBUG(0);
    }
}

/*******************************************************************************************************************//**
 * Checks if the specific GPIO is latched or not.
 *
 * @param[in] pin The GPIO pin to check latch status for
 **********************************************************************************************************************/
__STATIC_INLINE bool bsp_io_pad_isolation_is_disabled (bsp_io_port_pin_t pin)
{
    bsp_io_port_pin_t pin_id  = (bsp_io_port_pin_t) (BSP_IO_PIN_BITS & (uint16_t) pin);
    bsp_io_port_t     port_id =
        (bsp_io_port_t) ((BSP_IO_PORT_BITS & (uint16_t) pin) >> BSP_IO_PORT_OFFSET);

    if (BSP_IO_PORT_00 == port_id)
    {
        BSP_CHECK_DEBUG(pin_id < BSP_FEATURE_IO_PORT0_GPIO_COUNT);

        return CRG_TOP->P0_PAD_LATCH_REG & (1 << pin_id);
    }
    else if (BSP_IO_PORT_01 == port_id)
    {
        BSP_CHECK_DEBUG(pin_id < BSP_FEATURE_IO_PORT1_GPIO_COUNT);

        return CRG_TOP->P1_PAD_LATCH_REG & (1 << pin_id);
    }

 #if BSP_FEATURE_IO_PORT2_GPIO_COUNT > 0
    else if (BSP_IO_PORT_02 == port_id)
    {
        BSP_CHECK_DEBUG(pin_id < BSP_FEATURE_IO_PORT2_GPIO_COUNT);

        return CRG_TOP->P2_PAD_LATCH_REG & (1 << pin_id);
    }
 #endif
    else
    {
        /* Invalid port_id. */
        BSP_CHECK_DEBUG(0);
    }

    return false;
}

#endif

/** @} (end addtogroup BSP_IO) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
