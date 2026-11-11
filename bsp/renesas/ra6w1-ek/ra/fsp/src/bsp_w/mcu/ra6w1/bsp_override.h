#ifndef BSP_OVERRIDE_H
#define BSP_OVERRIDE_H

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Define overrides required for this MCU. */
#define BSP_OVERRIDE_TIMER_MODE_T
#define BSP_OVERRIDE_TIMER_EVENT_T
#define BSP_OVERRIDE_TIMER_SOURCE_DIV_T

// #define BSP_OVERRIDE_LPM_STANDBY_WAKE_SOURCE_T
#define BSP_OVERRIDE_LPM_DEEP_STANDBY_WAKE_SOURCE_T
#define BSP_OVERRIDE_LPM_SNOOZE_REQUEST_T
#define BSP_OVERRIDE_LPM_SNOOZE_END_T
#define BSP_OVERRIDE_LPM_SNOOZE_CANCEL_T
#define BSP_OVERRIDE_ADC_INCLUDE

#define BSP_OVERRIDE_ADC_EVENT_T

/** ADC callback event definitions  */
typedef enum e_adc_event
{
    ADC_EVENT_SCAN_COMPLETE,           ///< Normal/Group A scan complete
    ADC_EVENT_SCAN_COMPLETE_GROUP_B,   ///< Group B scan complete
    ADC_EVENT_SCAN_COMPLETE_GROUP_C,   ///< Group C scan complete
    ADC_EVENT_CALIBRATION_COMPLETE,    ///< Calibration complete
    ADC_EVENT_CONVERSION_COMPLETE,     ///< Conversion complete
    ADC_EVENT_CALIBRATION_REQUEST,     ///< Calibration requested
    ADC_EVENT_CONVERSION_ERROR,        ///< Scan error
    ADC_EVENT_OVERFLOW,                ///< Overflow occurred
    ADC_EVENT_LIMIT_CLIP,              ///< Limiter clipping occurred
    ADC_EVENT_FIFO_READ_REQUEST,       ///< FIFO read requested
    ADC_EVENT_FIFO_OVERFLOW,           ///< FIFO overflow occurred
    ADC_EVENT_THD_UNDER,               ///< Conversion result was below the threshold
    ADC_EVENT_THD_OVER,                ///< Conversion result exceeded the threshold
} adc_event_t;

#define BSP_OVERRIDE_ADC_RESOLUTION_T

/** ADC data resolution definitions */
typedef enum e_adc_resolution
{
    ADC_RESOLUTION_12_BIT = 0,         ///< 12 bit resolution
    ADC_RESOLUTION_10_BIT = 1,         ///< 10 bit resolution
    ADC_RESOLUTION_7_BIT  = 2,         ///< 7 bit resolution
    ADC_RESOLUTION_4_BIT  = 3,         ///< 4 bit resolution
} adc_resolution_t;

#define BSP_OVERRIDE_ADC_INFO_T

/** ADC Information Structure for Transfer Interface */
typedef struct st_adc_info
{
    void   * p_address;                ///< The address to start reading the data from
    uint32_t length;                   ///< The total number of transfers to read
} adc_info_t;

#define BSP_OVERRIDE_WDT_TIMEOUT_T

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Options to configure pin functions  */
typedef enum e_gpio_w_cfg_options
{
    /* PUPD */
    GPIO_W_CFG_PERIPHERAL_PIN        = 0x00000000, ///< Enables pin to operate as a peripheral pin
    GPIO_W_CFG_PULLDOWN_ENABLE       = 0x00000200, ///< Enables pull down
    GPIO_W_CFG_PULLUP_ENABLE         = 0x00000100, ///< Enables pull up
    GPIO_W_CFG_PORT_DIRECTION_INPUT  = 0x00000000, ///< Sets the pin direction to input
    GPIO_W_CFG_PORT_DIRECTION_OUTPUT = 0x00000300, ///< Sets the pin direction to output

    /* PPOD */
    GPIO_W_CFG_OPEN_DRAIN_ENABLE = 0x00000700,     ///< Enables open-drain output

    /* PAD input selection */
    GPIO_W_CFG_SCHMITT_TRIG_ENABLE = 0x00000800,   ///< Enables Schmitt trigger for input pin

    /* Drive Strength */
    GPIO_W_CFG_DRV_2mA  = 0x00000000,              ///< 2mA
    GPIO_W_CFG_DRV_4mA  = 0x00001000,              ///< 4mA
    GPIO_W_CFG_DRV_8mA  = 0x00002000,              ///< 8mA
    GPIO_W_CFG_DRV_14mA = 0x00003000,              ///< 14mA

    /* Standard PAD slew rate control */
    GPIO_W_CFG_SLW_FAST = 0x00000000,              ///< Fast
    GPIO_W_CFG_SLW_SLOW = 0x00004000,              ///< Slow

    /* Standard PAD Parametric Output control, parametric inverted data */

    // TIN-TODO: Most probably the name of this field was copy pasted from the corresponding RA enum & needs to be changed to match the actual functionality of the corresponding register field.
    GPIO_W_CFG_ANALOG_ENABLE = 0x00008000,    ///< Enabled

    /* PIN LEVEL */
    GPIO_W_CFG_PORT_OUTPUT_LOW  = 0x00000000, ///< Sets the pin level to low
    GPIO_W_CFG_PORT_OUTPUT_HIGH = 0x00400000, ///< Sets the pin level to high

    /* GPIO CFG */
    GPIO_W_CFG_RETENTION    = 0x20000000,     ///< The pin should not float during sleep
    GPIO_W_CFG_IRQ_ENABLE   = 0x40000000,     ///< Enables IRQ
} gpio_w_cfg_options_t;

typedef uint32_t wdt_timeout_t;

/** Timer operational modes */
typedef enum e_timer_mode
{
    TIMER_MODE_PERIODIC,               ///< Timer restarts after period elapses.
    TIMER_MODE_ONE_SHOT,               ///< Timer stops after period elapses.
    TIMER_MODE_PWM,                    ///< Timer generates square-wave PWM output.
    TIMER_MODE_EDGE_DETECT,            ///< Timer asynchronously counting up edges.
} timer_mode_t;

/** Events that can trigger a callback function */
typedef enum e_timer_event
{
    TIMER_EVENT_CYCLE_END,                    ///< Requested timer delay has expired or timer has wrapped around
    TIMER_EVENT_PULSE_CNT_CYCLE_END,          ///< Requested number of pulses were triggered
    TIMER_EVENT_SEQUENTIAL_CAPTURE_CYCLE_END, ///< Requested number of captures were triggered
    TIMER_EVENT_OVERFLOW,                     ///< Timer overflow event (counter reached 32-bit value)
    TIMER_EVENT_UNDERFLOW,                    ///< Timer underflow event (counter went under zero (0) value)
    TIMER_EVENT_CAPTURE_A,                    ///< A capture has occurred on signal A
    TIMER_EVENT_CAPTURE_B,                    ///< A capture has occurred on signal B
    TIMER_EVENT_CAPTURE_C,                    ///< A capture has occurred on signal C
    TIMER_EVENT_CAPTURE_D,                    ///< A capture has occurred on signal D
    TIMER_EVENT_CAPTURE_E,                    ///< A capture has occurred on signal E
    TIMER_EVENT_CAPTURE_F,                    ///< A capture has occurred on signal F
    TIMER_EVENT_CAPTURE_G,                    ///< A capture has occurred on signal G
    TIMER_EVENT_CAPTURE_H,                    ///< A capture has occurred on signal H
    TIMER_EVENT_COMPARE_A,                    ///< A compare has occurred on signal A
    TIMER_EVENT_COMPARE_B,                    ///< A compare has occurred on signal B
    TIMER_EVENT_COMPARE_C,                    ///< A compare has occurred on signal C
    TIMER_EVENT_COMPARE_D,                    ///< A compare has occurred on signal D
    TIMER_EVENT_COMPARE_E,                    ///< A compare has occurred on signal E
    TIMER_EVENT_COMPARE_F,                    ///< A compare has occurred on signal F
    TIMER_EVENT_COMPARE_G,                    ///< A compare has occurred on signal G
    TIMER_EVENT_COMPARE_H,                    ///< A compare has occurred on signal H
} timer_event_t;

typedef enum e_timer_source_div
{
    TIMER_SOURCE_DIV_1  = 0,           ///< Timer clock source divided by 1
    TIMER_SOURCE_DIV_2  = 1,           ///< Timer clock source divided by 2
    TIMER_SOURCE_DIV_3  = 2,           ///< Timer clock source divided by 3
    TIMER_SOURCE_DIV_4  = 3,           ///< Timer clock source divided by 4
    TIMER_SOURCE_DIV_5  = 4,           ///< Timer clock source divided by 5
    TIMER_SOURCE_DIV_6  = 5,           ///< Timer clock source divided by 6
    TIMER_SOURCE_DIV_7  = 6,           ///< Timer clock source divided by 7
    TIMER_SOURCE_DIV_8  = 7,           ///< Timer clock source divided by 8
    TIMER_SOURCE_DIV_9  = 8,           ///< Timer clock source divided by 9
    TIMER_SOURCE_DIV_10 = 9,           ///< Timer clock source divided by 10
    TIMER_SOURCE_DIV_11 = 10,          ///< Timer clock source divided by 11
    TIMER_SOURCE_DIV_12 = 11,          ///< Timer clock source divided by 12
    TIMER_SOURCE_DIV_13 = 12,          ///< Timer clock source divided by 13
    TIMER_SOURCE_DIV_14 = 13,          ///< Timer clock source divided by 14
    TIMER_SOURCE_DIV_15 = 14,          ///< Timer clock source divided by 15
    TIMER_SOURCE_DIV_16 = 15,          ///< Timer clock source divided by 16
    TIMER_SOURCE_DIV_17 = 16,          ///< Timer clock source divided by 17
    TIMER_SOURCE_DIV_18 = 17,          ///< Timer clock source divided by 18
    TIMER_SOURCE_DIV_19 = 18,          ///< Timer clock source divided by 19
    TIMER_SOURCE_DIV_20 = 19,          ///< Timer clock source divided by 20
    TIMER_SOURCE_DIV_21 = 20,          ///< Timer clock source divided by 21
    TIMER_SOURCE_DIV_22 = 21,          ///< Timer clock source divided by 22
    TIMER_SOURCE_DIV_23 = 22,          ///< Timer clock source divided by 23
    TIMER_SOURCE_DIV_24 = 23,          ///< Timer clock source divided by 24
    TIMER_SOURCE_DIV_25 = 24,          ///< Timer clock source divided by 25
    TIMER_SOURCE_DIV_26 = 25,          ///< Timer clock source divided by 26
    TIMER_SOURCE_DIV_27 = 26,          ///< Timer clock source divided by 27
    TIMER_SOURCE_DIV_28 = 27,          ///< Timer clock source divided by 28
    TIMER_SOURCE_DIV_29 = 28,          ///< Timer clock source divided by 29
    TIMER_SOURCE_DIV_30 = 29,          ///< Timer clock source divided by 30
    TIMER_SOURCE_DIV_31 = 30,          ///< Timer clock source divided by 31
    TIMER_SOURCE_DIV_32 = 31,          ///< Timer clock source divided by 32
} timer_source_div_t;
#endif
