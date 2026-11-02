/**
 * \addtogroup PLA_DRI_PER_ANALOG
 \{
 * \addtogroup HW_SYS System Hardware Driver
 \{
 * \brief System Driver
 */

/**
 ****************************************************************************************
 *
 * @file hw_sys.h
 *
 * @brief System Driver header file.
 *
 * Copyright (C) 2017-2020 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef HW_SYS_H_
#define HW_SYS_H_

#include "sdk_defs.h"

typedef enum
{
    HW_SYS_REMAP_ADDRESS_0_TO_ROM,
    HW_SYS_REMAP_ADDRESS_0_TO_OTP,
    HW_SYS_REMAP_ADDRESS_0_TO_QSPI_FLASH,
    HW_SYS_REMAP_ADDRESS_0_TO_RAM,

    /* XXX Values for test/debugging purposes are omitted */
} HW_SYS_REMAP_ADDRESS_0;

static inline HW_SYS_REMAP_ADDRESS_0 hw_sys_get_memory_remapping (void)
{
    HW_SYS_REMAP_ADDRESS_0 value;
    GLOBAL_INT_DISABLE();
    value = REG_GETF(CRG_TOP, SYS_CTRL_REG, REMAP_ADR0);
    GLOBAL_INT_RESTORE();

    return value;
}

#if (DEVICE_FAMILY == DA1468X) || ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))
 #if dg_configUSE_HW_SYS

  #include "sdk_defs.h"
  #include "hw_pd.h"

  #if ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))
   #include <hw_memctrl.h>

/* \brief Specifies the HW BSR mask used for accessing the SW BSR */
   #define SW_BSR_HW_BSR_MASK    (0x3)

/*
 * \brief Enumerations used when accessing the HW BSR register
 */
typedef enum
{
    HW_BSR_MASTER_NONE   = 0,
    HW_BSR_MASTER_SNC    = 1,
    HW_BSR_MASTER_SYSCPU = 2,
    HW_BSR_MASTER_CMAC   = 3,
    HW_BSR_MASTER_NUM,
} HW_BSR_MASTER_ID;

/*
 * \brief HW BSR position
 */
typedef enum
{
    HW_BSR_SW_POS            = 0,
    HW_BSR_PLL_ENABLE_POS    = 2,
    HW_BSR_POWER_CTRL_POS    = 28,
    HW_BSR_WAKEUP_CONFIG_POS = 30,
} HW_BSR_POS;

/*
 * \brief Enumerations used when accessing the SW BSR variable
 */
typedef enum
{
    SW_BSR_MASTER_NONE   = 1 << HW_BSR_MASTER_NONE,
    SW_BSR_MASTER_SNC    = 1 << HW_BSR_MASTER_SNC,
    SW_BSR_MASTER_SYSCPU = 1 << HW_BSR_MASTER_SYSCPU,
    SW_BSR_MASTER_CMAC   = 1 << HW_BSR_MASTER_CMAC,
} SW_BSR_MASTER_ID;

typedef enum
{
    BSR_PERIPH_ID_SNC   = 0,
    BSR_PERIPH_ID_SPI1  = 1,
    BSR_PERIPH_ID_SPI2  = 2,
    BSR_PERIPH_ID_UART1 = 3,
    BSR_PERIPH_ID_UART2 = 4,
    BSR_PERIPH_ID_UART3 = 5,
    BSR_PERIPH_ID_I2C1  = 6,
    BSR_PERIPH_ID_I2C2  = 7,
    BSR_PERIPH_ID_MOTOR = 8,
    BSR_PERIPH_ID_GPADC = 9,
    BSR_PERIPH_ID_SDADC = 10,
    BSR_PERIPH_ID_MAX   = 16,
} HW_SYS_BSR_PERIPH_ID;

/**
 * \brief Register configuration
 *
 */
typedef struct
{
    __IO uint32_t * addr;              //!< Register address
    uint32_t        value;             //!< Register value
} hw_sys_reg_config_t;

/*
 * Export hw_sys_sw_bsr so that other masters have access to its address.
 */
extern __RETAINED uint32_t hw_sys_sw_bsr[BSR_PERIPH_ID_MAX];

  #endif                               /* DA1469X */

__STATIC_INLINE void hw_sys_set_memory_remapping (HW_SYS_REMAP_ADDRESS_0 value)
{
    GLOBAL_INT_DISABLE();
    REG_SETF(CRG_TOP, SYS_CTRL_REG, REMAP_ADR0, value);
    GLOBAL_INT_RESTORE();
}

/**
 * \brief Enable Cache retainability.
 *
 */
__STATIC_INLINE void hw_sys_set_cache_retained (void)
{
    GLOBAL_INT_DISABLE();
    REG_SET_BIT(CRG_TOP, PMU_CTRL_REG, RETAIN_CACHE);
    GLOBAL_INT_RESTORE();
}

  #if (DEVICE_FAMILY == DA1468X)

/**
 * \brief Enable ECC microcode RAM retainment.
 *
 */
__STATIC_INLINE void hw_sys_set_eccram_retained (void)
{
    GLOBAL_INT_DISABLE();
    REG_SET_BIT(CRG_TOP, PMU_CTRL_REG, RETAIN_ECCRAM);
    GLOBAL_INT_RESTORE();
}

  #endif                               /* DEVICE_FAMILY */

/**
 * \brief Setup the Retention Memory configuration.
 *
 */
__STATIC_INLINE void hw_sys_setup_retmem (void)
{
    GLOBAL_INT_DISABLE();

  #if (DEVICE_FAMILY == DA1468X)
    REG_SETF(CRG_TOP, PMU_CTRL_REG, RETAIN_RAM, dg_configMEM_RETENTION_MODE);
  #elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))
    CRG_TOP->RAM_PWR_CTRL_REG = dg_configMEM_RETENTION_MODE;
  #endif                               /* DEVICE_FAMILY */

    GLOBAL_INT_RESTORE();
}

/**
 * \brief Disable memory retention.
 *
 */
__STATIC_INLINE void hw_sys_no_retmem (void)
{
    GLOBAL_INT_DISABLE();
  #if (DEVICE_FAMILY == DA1468X)
    CRG_TOP->PMU_CTRL_REG &= ~(REG_MSK(CRG_TOP, PMU_CTRL_REG, RETAIN_RAM) |
                               REG_MSK(CRG_TOP, PMU_CTRL_REG, RETAIN_CACHE) |
                               REG_MSK(CRG_TOP, PMU_CTRL_REG, RETAIN_ECCRAM));
  #elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))
    REG_CLR_BIT(CRG_TOP, PMU_CTRL_REG, RETAIN_CACHE);
    CRG_TOP->RAM_PWR_CTRL_REG = 0x5555;
  #endif                               /* DEVICE_FAMILY */
    GLOBAL_INT_RESTORE();
}

/**
 * \brief Prepare RESET type tracking.
 */
__STATIC_FORCEINLINE void hw_sys_track_reset_type (void)
{
  #if ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X)) || ((DEVICE_FAMILY == DA1468X) && \
    (DEVICE_REVISION == DEVICE_REV_B))
    CRG_TOP->RESET_STAT_REG = 0;
  #endif
}

/**
 * \brief Enable the clock-less sleep mode.
 *
 */
__STATIC_INLINE void hw_sys_enable_clockless (void)
{
    GLOBAL_INT_DISABLE();
    REG_SET_BIT(CRG_DEEPSLP, DEEP_SLEEP_CTRL_REG, CLKLESS_ENABLE);
    GLOBAL_INT_RESTORE();
}

/**
 * \brief Disable the clock-less sleep mode.
 *
 */
__STATIC_INLINE void hw_sys_disable_clockless (void)
{
    GLOBAL_INT_DISABLE();
    REG_CLR_BIT(CRG_DEEPSLP, DEEP_SLEEP_CTRL_REG, CLKLESS_ENABLE);
    GLOBAL_INT_RESTORE();
}

/**
 * \brief Activate the "Reset on wake-up" functionality.
 *
 */
__STATIC_INLINE void hw_sys_enable_reset_on_wup (void)
{
    GLOBAL_INT_DISABLE();
    REG_SET_BIT(CRG_TOP, PMU_CTRL_REG, RESET_ON_WAKEUP);
    GLOBAL_INT_RESTORE();
}

  #if (DEVICE_FAMILY == DA1468X)

/**
 * \brief Set (part of) the preferred settings.
 *
 */
void hw_sys_set_preferred_values(void);

  #elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))

/**
 * \brief Set the preferred settings of a power domain.
 *
 * \param [in] pd power domain
 */
void hw_sys_set_preferred_values(HW_PD pd);

  #endif

/**
 * \brief Set the GPIO used for the SW cursor to High-Z.
 *
 */
void hw_sys_setup_sw_cursor(void);

/**
 * \brief Triggers the GPIO used for the SW cursor.
 *
 */
void hw_sys_trigger_sw_cursor(void);

/**
 * \brief Enable the debugger.
 *
 */
__STATIC_FORCEINLINE void hw_sys_enable_debugger (void)
{
    GLOBAL_INT_DISABLE();
    REG_SET_BIT(CRG_TOP, SYS_CTRL_REG, DEBUGGER_ENABLE);
    GLOBAL_INT_RESTORE();
}

/**
 * \brief Disable the debugger.
 *
 */
__STATIC_FORCEINLINE void hw_sys_disable_debugger (void)
{
    GLOBAL_INT_DISABLE();
    REG_CLR_BIT(CRG_TOP, SYS_CTRL_REG, DEBUGGER_ENABLE);
    GLOBAL_INT_RESTORE();
}

/**
 * \brief Check if the debugger is attached.
 *
 * \return true, if the debugger is attached, else false.
 *
 */
__STATIC_FORCEINLINE bool hw_sys_is_debugger_attached (void)
{
    return REG_GETF(CRG_TOP, SYS_STAT_REG, DBG_IS_ACTIVE) != 0;
}

/**
 * \brief  Trigger a GPIO when ASSERT_WARNING() or ASSERT_ERROR() hits.
 *
 */
__RETAINED_CODE void hw_sys_assert_trigger_gpio(void);

  #if ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))

/**
 * \brief  Try to lock a BSR entry
 *
 * \param [in] sw_bsr_master_id The SW BSR ID of the relevant master
 * \param [in] pos The position of the entry in BSR. Valid positions are provided in HW_BSR_POS.
 *
 * \return true if the BSR entry has been acquired, else false.
 *
 */
bool hw_sys_hw_bsr_try_lock(HW_BSR_MASTER_ID hw_bsr_master_id, HW_BSR_POS pos);

/**
 * \brief  Unlock a BSR entry
 *
 * \param [in] sw_bsr_master_id The SW BSR ID of the relevant master
 * \param [in] pos The position of the entry in BSR. Valid positions are provided in HW_BSR_POS.
 *
 */
void hw_sys_hw_bsr_unlock(HW_BSR_MASTER_ID hw_bsr_master_id, HW_BSR_POS pos);

/**
 * \brief Initializes the software busy status register.
 */
void hw_sys_sw_bsr_init(void);

/**
 * \brief Tries to acquire exclusive access to a specific peripheral when
 *        it is also used by other masters (SNC or CMAC).
 *
 * \param [in] sw_bsr_master_id The SW BSR ID of the relevant master
 * \param [in] periph_id The peripheral id for which exclusive access must be granted.
 *                       Valid range is (0 - BSR_PERIPH_ID_MAX). Check HW_SYS_BSR_PERIPH_ID.
 *
 * \return true if peripheral exclusive access has been acquired, else false.
 */
bool hw_sys_sw_bsr_try_acquire(SW_BSR_MASTER_ID sw_bsr_master_id, uint32_t periph_id);

/**
 * \brief Checks if exclusive access to a specific peripheral has been acquired
 *        from a given master.
 *
 * \param [in] sw_bsr_master_id The SW BSR ID of the relevant master
 * \param [in] periph_id The peripheral id for which exclusive access will be checked.
 *                       Valid range is (0 - BSR_PERIPH_ID_MAX). Check HW_SYS_BSR_PERIPH_ID.
 * \return true if peripheral exclusive access has been acquired from the specific master, else false.
 */
bool hw_sys_sw_bsr_acquired(SW_BSR_MASTER_ID sw_bsr_master_id, uint32_t periph_id);

/**
 * \brief Releases the exclusive access from a specific peripheral so it
 *        it can be also used by other masters (SNC or CMAC).
 *
 * \param [in] sw_bsr_master_id The SW BSR ID of the relevant master
 * \param [in] periph_id The peripheral id for which exclusive access must be released.
 *                       Valid range is (0 - BSR_PERIPH_ID_MAX). Check HW_SYS_BSR_PERIPH_ID.
 */
void hw_sys_sw_bsr_release(SW_BSR_MASTER_ID sw_bsr_master_id, uint32_t periph_id);

/**
 * \brief Enables the COM power domain.
 *
 */
void hw_sys_pd_com_enable(void);

/**
 * \brief Disables the COM power domain. If it has not
 *        been enabled by any other modules, it will be disabled.
 */
void hw_sys_pd_com_disable(void);

/**
 * \brief Enables the PERIPH power domain.
 *
 */
void hw_sys_pd_periph_enable(void);

/**
 * \brief Disables the PERIPH power domain. If it has not
 *        been enabled by any other modules, it will be disabled.
 */
void hw_sys_pd_periph_disable(void);

/**
 * \brief Add register configuration entries in the system register configuration table
 *
 * \param [in] config pointer to the structure containing the register configuration
 * \param [in] num_of_entries the number of entries in the register configuration structure
 *
 * \return the index of the first entry in the configuration table
 */
uint32_t hw_sys_reg_add_config(hw_sys_reg_config_t * config, uint32_t num_of_entries);

/**
 * \brief Get a register configuration entry
 *
 * \param [in] index the index of the entry in the register configuration table
 *
 * \return a pointer to the register configuration entry
 */
hw_sys_reg_config_t * hw_sys_reg_get_config(uint32_t index);

/**
 * \brief Modify a register configuration entry
 *
 * \param [in] index the index of the entry in the register configuration table
 * \param [in] addr the new register address
 * \param [in] value the new register value
 */
void hw_sys_reg_modify_config(uint32_t index, __IO uint32_t * addr, uint32_t value);

/**
 * \brief Get the number of entries in the system register configuration table
 *
 * \return a pointer to the number of entries
 */
uint32_t * hw_sys_reg_get_num_of_config_entries(void);

/**
 * \brief Apply system register configuration
 *
 * Configure non-retained system registers using the entries in the system register
 * configuration table.
 */
__RETAINED_CODE void hw_sys_reg_apply_config(void);

/**
 * \brief Checks whether there are register entries in CS for the following registers
 *       - CLK_FREQ_TRIM_REG
 *       - XTAL32M_CTRL0_REG
 * If any of the above is missing, the function applies the default values
 * for specific fields
 *       - CLK_FREQ_TRIM_REG: XTAL32M_TRIM
 *       - XTAL32M_CTRL0_REG: XTAL32M_CXCOMP_ENABLE
 */
void hw_sys_apply_default_values(void);

   #if !DEVICE_FPGA

/**
 * \brief Calculates the PLL_MIN_CURRENT value needed for tuning the PLL lock time
 *
 * \note This function has to be called only once during startup.
 */
void hw_sys_pll_calculate_min_current(void);

/**
 * \brief Sets the PLL_MIN_CURRENT value needed for tuning the PLL lock time
 *
 * \note This function should be called every time the timers power domain powers off and on.
 */
void hw_sys_pll_set_min_current(void);

   #endif                              /* !DEVICE_FPGA */
  #endif                               /* DA1469X */

 #endif                                /* dg_configUSE_HW_SYS */
#endif                                 /* DEVICE_FAMILY */
#endif                                 /* HW_SYS_H_ */

/**
 * \}
 * \}
 */
