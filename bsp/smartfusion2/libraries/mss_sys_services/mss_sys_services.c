/*******************************************************************************
 * (c) Copyright 2012-2016 Microsemi SoC Products Group.  All rights reserved.
 *
 * SmartFusion2 system services.
 *
 * SVN $Revision: 8688 $
 * SVN $Date: 2016-11-27 17:46:49 +0530 (Sun, 27 Nov 2016) $
 */
#include "mss_sys_services.h"
#include "mss_comblk.h"
#include "../../CMSIS/mss_assert.h"
#include <string.h>

/*==============================================================================
 *
 */
/*
 * Service request command opcodes:
 */
#define DEVICE_CERTIFICATE_REQUEST_CMD                  0u
#define SERIAL_NUMBER_REQUEST_CMD                       1u
#define FLASH_FREEZE_REQUEST_CMD                        2u
#define AES128_REQUEST_CMD                              3u
#define USERCODE_REQUEST_CMD                            4u
#define DESIGNVER_REQUEST_CMD                           5u
#define AES256_REQUEST_CMD                              6u
#define KEYTREE_REQUEST_CMD                             9u
#define SHA256_REQUEST_CMD                              10u
#define HMAC_REQUEST_CMD                                12u
#define PPUF_CHALLENGE_RESP_REQUEST_CMD                 14u
#define POINT_MULTIPLICATION_REQUEST_CMD                16u
#define POINT_ADDITION_REQUEST_CMD                      17u  
#define IAP_PROGRAMMING_REQUEST_CMD                     20u
#define ISP_PROGRAMMING_REQUEST_CMD                     21u
#define DIGEST_CHECK_REQUEST_CMD                        23u
#define PUF_ACTIVATION_CODE_REQUEST_CMD                 25u
#define PUF_USER_KEY_CODE_REQUEST_CMD                   26u
#define PUF_FETCH_KEY_REQUEST_CMD                       27u
#define PUF_ECC_PUBLIC_KEY_REQUEST_CMD                  28u
#define PUF_SEED_REQUEST_CMD                            29u
#define SECONDARY_DEVICE_CERTIFICATE_REQUEST_CMD        30u
#define TAMPER_CONTROL_REQUEST_CMD                      31u
#define NRBG_SELF_TEST_REQUEST_CMD                      40u
#define NRBG_INSTANTIATE_REQUEST_CMD                    41u
#define NRBG_GENERATE_REQUEST_CMD                       42u
#define NRBG_RESEED_REQUEST_CMD                         43u
#define NRBG_UNINSTANTIATE_REQUEST_CMD                  44u
#define NRBG_RESET_REQUEST_CMD                          45u
#define FLASHFREEZE_SHUTDOWN_CMD                        224u
#define ZEROIZATION_REQUEST_CMD                         240u
#define POWER_ON_RESET_DIGEST_ERROR_CMD                 241u

/*
 * System Services requests length:
 */
#define FLASH_FREEZE_REQUEST_LENGTH                     2u

/*
 * Service response lengths:
 */
#define STANDARD_SERV_RESP_LENGTH                       6u
#define SERIAL_NUMBER_SERV_RESP_LENGTH                  6u
#define USERCODE_SERV_RESP_LENGTH                       6u
#define DESIGNVER_SERV_RESP_LENGTH                      6u
#define DEVICE_CERT_SERV_RESP_LENGTH                    6u
#define SECONDARY_DEVICE_CERT_SERV_RESP_LENGTH          6u
#define ISP_PROG_SERV_RESP_LENGTH                       2u
#define IAP_PROG_SERV_RESP_LENGTH                       2u
#define NRBG_RESET_SERV_RESP_LENGTH                     2u
#define NRBG_SELF_TEST_SERV_RESP_LENGTH                 2u
#define NRBG_UNINST_SERV_RESP_LENGTH                    3u
#define DRBG_RESET_SERV_RESP_LENGTH                     2u
#define DIGEST_CHECK_SERV_RESP_LENGTH                   2u
#define FLASH_FREEZE_SERV_RESP_LENGTH                   2u
#define PORDIGEST_CHECK_SERV_RESP_LENGTH                2u
#define TAMPER_CONTROL_SERV_RESP_LENGTH                 2u
#define PUF_USER_ACTIVATION_CODE_RESP_LENGTH            2u
#define PUF_GET_NUMBER_OF_KEYS_RESP_LENGTH              6u
#define PUF_ENROLL_KEYS_RESP_LENGTH                     6u
#define PUF_EXPORT_ALL_KEYCODES_RESP_LENGTH             6u
#define PUF_IMPORT_ALL_KEYCODES_RESP_LENGTH             6u
#define FACC_STANDBY_SEL                                0u
#define MSS_25_50MHZ_EN                                 1u
#define MSS_1MHZ_EN                                     1u
#define FACC_STANDBY_SHIFT                              6u
#define MSS_25_50MHZ_EN_SHIFT                           9u
#define MSS_1MHZ_EN_SHIFT                               10u
#define FACC_STANDBY_SEL_MASK                           0x000001C0u
#define MSS_25_50MHZ_EN_MASK                            0x00000200u
#define MSS_1MHZ_EN_MASK                                0x00000400u

/*
 * Non Deterministic Random Bit Generator defines:
 */
#define INVALID_NRBG_HANDLE                 0xFFu

/*
 * RTC_WAKEUP_CR system register bit masks:
 */
#define RTC_WAKEUP_G4C_EN_MASK      0x00000004u
#define RTC_WAKEUP_FAB_EN_MASK      0x00000002u

/*
 * PUF user activation code sub command
 */
#define PUF_CREATE_USER_ACTIVATION_CODE     0u
#define PUF_DELETE_USER_ACTIVATION_CODE     1u

/*
 * Sub Command for PUF service
 */
#define PUF_GET_NUMBER_OF_KC_SUBCOMMAND      0u
#define PUF_CREATE_EXT_KC_SUBCOMMAND         1u
#define PUF_CREATE_INT_KC_SUBCOMMAND         2u
#define PUF_EXPORT_ALL_KC_SUBCOMMAND         3u
#define PUF_IMPORT_ALL_KC_SUBCOMMAND         4u
#define PUF_DELETE_KC_SUBCOMMAND             5u

/*==============================================================================
 * Local functions.
 */
static void request_completion_handler(uint8_t * p_response, uint16_t response_size);
static void signal_request_start(void);
static uint16_t wait_for_request_completion(void);
static uint8_t execute_service
(
    uint8_t cmd_opcode,
    uint8_t * cmd_params_ptr,
    uint8_t * response,
    uint16_t response_length
);

static void asynchronous_event_handler(uint8_t event_opcode);

static void write_ptr_value_into_array
(
    const uint8_t * pointer,
    uint8_t target_array[],
    uint32_t array_index
);

static void write_array_into_ptr_value
(
    uint8_t** pointer,
    uint8_t target_array[],
    uint32_t array_index
);
static void revert_clk_config(void);
static uint8_t clk_switching_fix(void);
static uint8_t* determine_seq(uint8_t val, uint8_t* len);

/*==============================================================================
 * Global variables
 */
static volatile uint8_t g_request_in_progress = 0u;
static volatile uint16_t g_last_response_length = 0u;
static sys_serv_async_event_handler_t g_event_handler = 0;
static uint8_t g_response[PORDIGEST_CHECK_SERV_RESP_LENGTH] = {0u};
static uint32_t g_initial_mssddr_facc1_cr = 0U;

/*==============================================================================
 * See mss_sys_services.h for details.
 */
void MSS_SYS_init(sys_serv_async_event_handler_t event_handler)
{   
    g_event_handler = event_handler;
    g_last_response_length = 0u;
    g_request_in_progress = 0u;
    
    /*
     * Set a default good value for g_initial_mssddr_facc1_cr used to control
     * the clock dividers coming in and out of Flash*Freeze.
     */
    g_initial_mssddr_facc1_cr = SYSREG->MSSDDR_FACC1_CR;
    
    /*
     * Initialize the COMBLK used to communicate with the System Controller.
     */
    MSS_COMBLK_init(asynchronous_event_handler, g_response);
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
/* Tamper attempt/failure range */
#define TAMPER_ATTEMPT_DETECT_OPCODE_RANGE_MIN           0x80u
#define TAMPER_ATTEMPT_DETECT_OPCODE_RANGE_MAX           0x8Fu
#define TAMPER_FAILURE_DETECT_OPCODE_RANGE_MIN           0x90u
#define TAMPER_FAILURE_DETECT_OPCODE_RANGE_MAX           0x9Fu
#define TAMPER_CLOCK_MONITOR_ERROR_OPCODE                0xA0u
#define TAMPER_HARDWARE_MONITOR_ERROR_OPCODE_RANGE_MIN   0xB1u
#define TAMPER_HARDWARE_MONITOR_ERROR_OPCODE_RANGE_MAX   0xB7u

#define FACC_GLMUX_SEL_MASK         0x00001000u
#define DELAY_MORE_THAN_10US        5000U
static void asynchronous_event_handler(uint8_t event_opcode)
{
    if (event_opcode == FLASH_FREEZE_SHUTDOWN_OPCODE)
    {
        uint32_t running_on_standby_clock;
        volatile uint32_t timeout;

        /*
         * Wait for the System Controller to switch the system's clock
         * from the main clock to the  standby clock. This should take place
         * within 10us of receiving the shut-down event.
         */
        timeout = DELAY_MORE_THAN_10US;
        do
        {
            running_on_standby_clock = SYSREG->MSSDDR_FACC1_CR & FACC_GLMUX_SEL_MASK;
            --timeout;
        }
        while ((running_on_standby_clock == 0U) && (timeout != 0U));

        /* Call the user's event handler. */
        if(g_event_handler != 0)
        {
            g_event_handler(event_opcode, g_response[1]);
        }
    }
    else if (event_opcode == FLASH_FREEZE_EXIT_OPCODE)
    {
        uint32_t running_on_standby_clock;
        volatile uint32_t timeout;
        
        /*
         * Wait for the System Controller to switch the system's clock
         * from the standby clock to the main clock. This should take place
         * within 10us of receiving the shut-down event.
         */
        timeout = DELAY_MORE_THAN_10US;
        do
        {
            running_on_standby_clock = SYSREG->MSSDDR_FACC1_CR & FACC_GLMUX_SEL_MASK;
            --timeout;
        }
        while ((running_on_standby_clock != 0U) && (timeout != 0U));
        
        /* Restore the clock dividers values of FACC1 register. */
        revert_clk_config();
        
        if(g_event_handler != 0)
        {
            /* Call the user's event handler. */
            g_event_handler(event_opcode, g_response[1]);
        }
    }
    else
    {
        if ((event_opcode == POR_DIGEST_ERROR_OPCODE) || \
            ((event_opcode >= TAMPER_ATTEMPT_DETECT_OPCODE_RANGE_MIN) && \
            (event_opcode <= TAMPER_FAILURE_DETECT_OPCODE_RANGE_MAX)) || \
            (event_opcode == TAMPER_CLOCK_MONITOR_ERROR_OPCODE) || \
            ((event_opcode >= TAMPER_HARDWARE_MONITOR_ERROR_OPCODE_RANGE_MIN) && \
            (event_opcode <= TAMPER_HARDWARE_MONITOR_ERROR_OPCODE_RANGE_MAX)))
        {
            /* 
             * Inform to the application that new asynchronous message is received, 
             * only if application call-back function is registered during 
             * initialization. 
             */
            if(g_event_handler != 0)
            {
                /* Call the user's event handler. */
                g_event_handler(event_opcode, g_response[1]);
            }
        }
    }
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_get_serial_number
(
    uint8_t * p_serial_number
)
{
    uint8_t response[SERIAL_NUMBER_SERV_RESP_LENGTH];
    uint8_t status;
    
    status = execute_service(SERIAL_NUMBER_REQUEST_CMD,
                             p_serial_number,
                             response,
                             SERIAL_NUMBER_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_get_user_code
(
    uint8_t * p_user_code
)
{
    uint8_t response[USERCODE_SERV_RESP_LENGTH];
    uint8_t status;
    
    status = execute_service(USERCODE_REQUEST_CMD,
                             p_user_code,
                             response,
                             USERCODE_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_get_design_version
(
    uint8_t * p_design_version
)
{
    uint8_t response[DESIGNVER_SERV_RESP_LENGTH];
    uint8_t status;
    
    status = execute_service(DESIGNVER_REQUEST_CMD,
                             p_design_version,
                             response,
                             DESIGNVER_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_get_device_certificate
(
    uint8_t * p_device_certificate
)
{
    uint8_t response[DEVICE_CERT_SERV_RESP_LENGTH];
    uint8_t status;
    
    status = execute_service(DEVICE_CERTIFICATE_REQUEST_CMD,
                             p_device_certificate,
                             response,
                             DEVICE_CERT_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_get_secondary_device_certificate
(
    uint8_t * p_secondary_device_certificate
)
{
    uint8_t response[SECONDARY_DEVICE_CERT_SERV_RESP_LENGTH];
    uint8_t status;

    /*
     * The get secondary device certificate system service is not available on 
     * M2S050 rev A, rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    status = execute_service(SECONDARY_DEVICE_CERTIFICATE_REQUEST_CMD,
                             p_secondary_device_certificate,
                             response,
                             SECONDARY_DEVICE_CERT_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
#define CONFIG_CLOCK_DIV_MASK         0xFFC7F103u
#define CONFIG_CLOCK_DIV_32_RATIO     0x00301CD8u

/* Sequence array for divisor */
uint8_t div1_seq[]={ 0x00, 0x01, 0x05, 0x07};
uint8_t div2_seq[]={ 0x01, 0x05, 0x07};
uint8_t div4_seq[]={ 0x02, 0x03, 0x01, 0x05, 0x07};
uint8_t div8_seq[]={ 0x04, 0x06, 0x07};
uint8_t div16_seq[]={ 0x05, 0x07};
uint8_t div32_seq[]={ 0x06, 0x07 };

/* Divisor array is used to store the values of APB0_DIVISOR, APB1_DIVISOR, 
 * M3_CLK_DIVISOR and FIC64_DIVISOR bit-fields before entering flash freeze. 
  * This value will be used to revert back the value of FACC1 register after 
  * exiting from Flash Freeze/IAP/Fabric digest check.
 */
uint32_t divisor[4] = {0x00};
volatile uint8_t ind = 0;

static uint8_t* determine_seq(uint8_t val, uint8_t* len)
{
    uint8_t*seq;
    
    switch(val)
    {
        case 0:
                seq = &div1_seq[0];
                *len = 4;
            break;

        case 1:
                seq = &div2_seq[0];
                *len = 3;
            break;

        case 2:
                seq = &div4_seq[0];
                *len = 5;
            break;

        case 4:
                seq = &div8_seq[0];
                *len = 3;
            break;

        case 5:
                seq = &div16_seq[0];
                *len = 2;
            break;

        case 6:
                seq = &div32_seq[0];
                *len = 2;
            break;

        default:
                *len = 0;
                seq = NULL;
            break;
    }
    
    return seq;
}

#define CLOCK_SWITCHING_SUCCESS         0x00u
#define CLOCK_SWITCHING_ERROR           0x01u

/* SAR 80563 - Workaround for Glitchless Clock Multiplexer Switching Issue
 * If user has requested for fabric digest check/IAP/Flash Freeze service, then 
 * the firmware will change the clock divisor values of FACC1 register based on 
 * device version to avoid Glitchless Clock Multiplexer Switching Issue. 
 * If the device is 010/025/050/090/150 device, Cortex-M3 firmware 
 * dynamically divides down fclk, pclk0, pclk1 and clk_fic64 to the divided 
 * by 32 versions. If the device is 05 device, firmware will load the 
 * divisor values in sequenced from the start setting to the divide by 32 
 * setting. If the device is 060 device, then firmware will compare the 
 * divisor values of fclk, pclk0, pclk1 and clk_fic64, and if the divisor 
 * values are equal to each other, then firmware will send requested command to 
 * system controller otherwise return CLOCK_SWITCHING_ERROR error.
 */
static uint8_t clk_switching_fix(void)
{
    uint8_t* sequence;
    uint8_t len;
    volatile uint32_t g_mssddr_facc1_cr =  SYSREG->MSSDDR_FACC1_CR;
    uint32_t var = 0;
    uint32_t temp = 0;
    uint32_t device_version;
    uint8_t status = CLOCK_SWITCHING_SUCCESS;
    
    device_version = (SYSREG->DEVICE_VERSION & 0xFFFFu);

    /* For 10/25/50/90/150 devices */
    if((0xF802u == device_version) || \
       (0xF803u == device_version) || \
       (0xF804u == device_version)||  \
       (0xF807u == device_version) || \
       (0xF806u == device_version))
    {
        /* Dynamically divides down fclk, pclk0, pclk1 and clk_fic64
         * to the divided by 32 versions and M3_CLK, PCLK0, PCLK1, 
         * CLK_FIC64 all driven from CLK_STANDBY clock.
         */
        SYSREG->MSSDDR_FACC1_CR = (SYSREG->MSSDDR_FACC1_CR & CONFIG_CLOCK_DIV_MASK) | \
                                   CONFIG_CLOCK_DIV_32_RATIO;
        status = CLOCK_SWITCHING_SUCCESS;
    }
    
    /* For 05 devices
     * When modifying clock divisor settings on M2S005, it is necessary to 
     * sequence them, depending on the starting configuration.
     */
    else if(0xF805u == device_version)
    {
        /* For APB0_DIVISOR setting */
        divisor[0] = ((g_mssddr_facc1_cr >> 2) & 0x00000007);
        sequence = determine_seq(divisor[0], &len);

        for(var = 1; var < len; var++)
        {
            temp = SYSREG->MSSDDR_FACC1_CR;
            temp &= 0xFFFFFFE3u;
            temp |= ((uint32_t)(sequence[var]) << 2);
            SYSREG->MSSDDR_FACC1_CR = temp;
        }

        /* For APB1_DIVISOR setting */
        divisor[1] = ((g_mssddr_facc1_cr >> 5) & 0x00000007);
        sequence = determine_seq(divisor[1], &len);

        for(var = 1; var < len; var++)
        {
            temp = SYSREG->MSSDDR_FACC1_CR;
            temp &= 0xFFFFFF1Fu;
            temp |= ((uint32_t)(sequence[var]) << 5);
            SYSREG->MSSDDR_FACC1_CR = temp;
        }

        /* For M3_CLK_DIVISOR setting */
        divisor[2] = ((g_mssddr_facc1_cr >> 9) & 0x00000007);
        sequence = determine_seq(divisor[2], &len);
        
        for(var = 1; var < len; var++)
        {
            temp = SYSREG->MSSDDR_FACC1_CR;
            temp &= 0xFFFFF1FFu;
            temp |= ((uint32_t)(sequence[var]) << 9);
            SYSREG->MSSDDR_FACC1_CR = temp;
        }

        /* For FIC64_DIVISOR setting */
        divisor[3] = ((g_mssddr_facc1_cr >> 19) & 0x00000007);
        sequence = determine_seq(divisor[3], &len);
        for(var = 1; var < len; var++)
        {
            temp = SYSREG->MSSDDR_FACC1_CR;
            temp &= 0xFFC7FFFFu;
            temp |= ((uint32_t)(sequence[var]) << 19);
            SYSREG->MSSDDR_FACC1_CR = temp;
        }

        /* Set the value of FACC_GLMUX_SEL bitfield of FACC1 register to 1 so 
         * that M3_CLK, PCLK0, PCLK1, CLK_FIC64 all driven from CLK_STANDBY
         * clock.
         */
        SYSREG->MSSDDR_FACC1_CR = SYSREG->MSSDDR_FACC1_CR | 0x00001000u;
        
        status = CLOCK_SWITCHING_SUCCESS;
    }
    /* For 060 devices */
    else if(0xF808u == device_version)
    {
        /* The divisor setting should be such that all the divisor should be 
         * equal to each other and set to divide by 1,2,4,8, and 16 (but not 32)
         */
        divisor[0] = ((g_mssddr_facc1_cr >> 2) & 0x00000007);
        divisor[1] = ((g_mssddr_facc1_cr >> 5) & 0x00000007);
        divisor[2] = ((g_mssddr_facc1_cr >> 9) & 0x00000007);
        divisor[3] = ((g_mssddr_facc1_cr >> 19) & 0x00000007);
       
        for(var = 1; var < 4; var++)
        {
            if((divisor[var] != divisor[0]) || \
               (divisor[0] > 5) || (divisor[var] > 5))
            {
                /* If the divisor value does meet the criteria, log the clock 
                 * switching error.
                 */
                status = CLOCK_SWITCHING_ERROR;
                break;
            }
        }      
    }
    else
    {
         /* Do Nothing. */
    }
    
    return status;
}

/* SAR 80563 - Workaround for Glitchless Clock Multiplexer Switching Issue
 * Revert back original values of various divisor in FACC1 register after 
 * completing the fabric digest check/IAP/Flash Freeze service. 
 */
static void revert_clk_config(void)
{
    uint8_t* sequence;
    uint8_t len;
    uint8_t var = 0;
    uint32_t temp = 0;
    uint32_t device_version;

    device_version = (SYSREG->DEVICE_VERSION & 0xFFFFu);

    /* Revert back values for 10/25/50/90/150 devices */
    if((0xF802u == device_version) || (0xF803u == device_version) || \
       (0xF804u == device_version)||(0xF807u == device_version) ||   \
       (0xF806u == device_version))
    {
        /* Restore the MSS clock dividers to their normal operations value. */
        SYSREG->MSSDDR_FACC1_CR = g_initial_mssddr_facc1_cr;
    }

    /* Revert back values for 05 devices in reverse sequence. */
    else if(0xF805u == device_version)
    {
        sequence = determine_seq(divisor[0], &len);
        for(var = len; var > 0; var--)
        {
            temp = SYSREG->MSSDDR_FACC1_CR;
            temp &= 0xFFFFFFE3u;
            temp |= ((uint32_t)(sequence[var - 1]) << 2);
            SYSREG->MSSDDR_FACC1_CR = temp;
        }

        /* For APB1_DIVISOR setting */
        sequence = determine_seq(divisor[1], &len);
        for(var = len; var > 0; var--)
        {
            temp = SYSREG->MSSDDR_FACC1_CR;
            temp &= 0xFFFFFF1Fu;
            temp |= ((uint32_t)(sequence[var - 1]) << 5);
            SYSREG->MSSDDR_FACC1_CR = temp;
        }

        /* For M3_CLK_DIVISOR setting */
        sequence = determine_seq(divisor[2], &len);
        for(var = len; var > 0; var--)
        {
            temp = SYSREG->MSSDDR_FACC1_CR;
            temp &= 0xFFFFF1FFu;
            temp |= ((uint32_t)(sequence[var - 1]) << 9);
            SYSREG->MSSDDR_FACC1_CR = temp;
        }

        /* For FIC64_DIVISOR setting */
        sequence = determine_seq(divisor[3], &len);
        for(var = len; var > 0; var--)
        {
            temp = SYSREG->MSSDDR_FACC1_CR;
            temp &= 0xFFC7FFFFu;
            temp |= ((uint32_t)(sequence[var - 1]) << 19);
            SYSREG->MSSDDR_FACC1_CR = temp;
        }
        
        /* Set the value of FACC_GLMUX_SEL bitfield of FACC1 register to 0 so 
         * that M3_CLK, PCLK0, PCLK1, CLK_FIC64 all driven from stage 2 
         * dividers (from CLK_SRC).
         */
        SYSREG->MSSDDR_FACC1_CR = SYSREG->MSSDDR_FACC1_CR & 0xFFFFEFFFu;
    }
    else
    {
        /* Do Nothing. */
    }
}

uint8_t MSS_SYS_flash_freeze(uint8_t options)
{
    uint8_t status;
    uint8_t clk_switch_status = CLOCK_SWITCHING_SUCCESS;
    uint16_t actual_response_length;
    uint8_t flash_freeze_req[FLASH_FREEZE_REQUEST_LENGTH];
    uint8_t response[FLASH_FREEZE_SERV_RESP_LENGTH];

    /*
     * The Flash Freeze system service is not available on M2S050 rev A and rev B.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    
    /*
     * Keep track of the clocks configuration before entering Flash*Freeze so
     * that it can be restored on Flash*Freeze exit.
     */
    g_initial_mssddr_facc1_cr = SYSREG->MSSDDR_FACC1_CR;
    
    /* SAR 80563
     * Cortex-M3 firmware dynamically divides down fclk, pclk0, pclk1 and
     * clk_fic64 to the divided by 32 versions based on device version.
     */
    clk_switch_status = clk_switching_fix();

    if(clk_switch_status == CLOCK_SWITCHING_SUCCESS)
    {
        /*
         * Enable RTC wake-up interrupt to System Controller and FPGA fabric.
         */
        SYSREG->RTC_WAKEUP_CR |= (RTC_WAKEUP_G4C_EN_MASK | RTC_WAKEUP_FAB_EN_MASK);

        signal_request_start();

        flash_freeze_req[0] = FLASH_FREEZE_REQUEST_CMD;
        flash_freeze_req[1] = options;

        MSS_COMBLK_send_cmd(flash_freeze_req,               /* p_cmd */
                            FLASH_FREEZE_REQUEST_LENGTH,    /* cmd_size */
                            0,                              /* p_data */
                            0u,                             /* data_size */
                            response,                       /* p_response */
                            FLASH_FREEZE_SERV_RESP_LENGTH,  /* response_size */
                            request_completion_handler);    /* completion_handler */

        actual_response_length = wait_for_request_completion();
        
        if((FLASH_FREEZE_SERV_RESP_LENGTH == actual_response_length) &&
           (FLASH_FREEZE_REQUEST_CMD == response[0]))
        {
            status = response[1];
        }
        else
        {
            status = MSS_SYS_UNEXPECTED_ERROR;
        }
    }
    else
    {
        /* SAR 80563
         * CLK Divisor error occurs on 060 device. The user should make sure 
         * that the all divisor i.e fclk, pclk0, pclk1 and clk_fic64 divisor 
         * must be equal to each other and set to to divide by 1,2, 4, 8, 16(but
         * not 32). If the divisor value does not meet the above criteria, the 
         * function will not send Flash Freeze command to system controller and 
         * will return CLK divisor error.
         */
        status = MSS_SYS_CLK_DIVISOR_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
#define AES128_KEY_LENGTH   16u
#define IV_LENGTH           16u

#define AES256_KEY_LENGTH   32u

#define HMAC_KEY_LENGTH     32u

uint8_t MSS_SYS_128bit_aes
(
    const uint8_t * key,
    const uint8_t * iv,
    uint16_t nb_blocks,
    uint8_t mode,
    uint8_t * dest_addr,
    const uint8_t * src_addr)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[44];
    uint8_t status;
    
    memcpy(&params[0], key, AES128_KEY_LENGTH);
    memcpy(&params[16], iv, IV_LENGTH);
    
    params[32] = (uint8_t)nb_blocks;
    params[33] = (uint8_t)(nb_blocks >> 8u);
    params[34] = mode;
    params[35] = 0u;

    write_ptr_value_into_array(dest_addr, params, 36u);
    write_ptr_value_into_array(src_addr, params, 40u);

    status = execute_service(AES128_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
                             
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_256bit_aes
( 
    const uint8_t * key,
    const uint8_t * iv,
    uint16_t nb_blocks,
    uint8_t mode,
    uint8_t * dest_addr,
    const uint8_t * src_addr
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[60];
    uint8_t status;
    
    memcpy(&params[0], key, AES256_KEY_LENGTH);
    memcpy(&params[32], iv, IV_LENGTH);
    
    params[48] = (uint8_t)nb_blocks;
    params[49] = (uint8_t)(nb_blocks >> 8u);
    params[50] = mode;
    params[51] = 0u;

    write_ptr_value_into_array(dest_addr, params, 52u);
    write_ptr_value_into_array(src_addr, params, 56u);

    status = execute_service(AES256_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
                             
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_sha256
(
    const uint8_t * p_data_in,
    uint32_t length,
    uint8_t * result
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[12];
    uint8_t status;
    
    params[0] = (uint8_t)((uint32_t)length);
    params[1] = (uint8_t)((uint32_t)length >> 8u);
    params[2] = (uint8_t)((uint32_t)length >> 16u);
    params[3] = (uint8_t)((uint32_t)length >> 24u);
    
    write_ptr_value_into_array(result, params, 4u);
    write_ptr_value_into_array(p_data_in, params, 8u);

    status = execute_service(SHA256_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
                             
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_hmac
(
    const uint8_t * key,
    const uint8_t * p_data_in,
    uint32_t length,
    uint8_t * p_result
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[58];
    uint8_t status;
    
    memcpy(&params[0], key, HMAC_KEY_LENGTH);
    
    params[32] = (uint8_t)((uint32_t)length);
    params[33] = (uint8_t)((uint32_t)length >> 8u);
    params[34] = (uint8_t)((uint32_t)length >> 16u);
    params[35] = (uint8_t)((uint32_t)length >> 24u);

    write_ptr_value_into_array(p_data_in, params, 36u);
    write_ptr_value_into_array(p_result, params, 40u);

    status = execute_service(HMAC_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
                             
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
#define KEYTREE_KEY_LENGTH      32
#define KEYTREE_PATH_LENGTH     16

uint8_t MSS_SYS_key_tree
(
    uint8_t* p_key,
    uint8_t op_type,
    const uint8_t* path
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[49];
    uint8_t status;
    
    memcpy(&params[0], p_key, KEYTREE_KEY_LENGTH);
    
    params[32] = op_type;
    
    memcpy(&params[33], path, KEYTREE_PATH_LENGTH);
    
    status = execute_service(KEYTREE_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
    
    if(status == MSS_SYS_SUCCESS)
    {
       memcpy(p_key, &params[0], KEYTREE_KEY_LENGTH);
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_challenge_response
(
    uint8_t* p_key,
    uint8_t op_type,
    const uint8_t* path
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[21];
    uint8_t status;
    
    params[0] = (uint8_t)((uint32_t)p_key);
    params[1] = (uint8_t)((uint32_t)p_key >> 8u);
    params[2] = (uint8_t)((uint32_t)p_key >> 16u);
    params[3] = (uint8_t)((uint32_t)p_key >> 24u);
    
    params[4] = op_type;
    
    memcpy(&params[5], path, KEYTREE_PATH_LENGTH);
    
    status = execute_service(PPUF_CHALLENGE_RESP_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
                             
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_nrbg_reset(void)
{
    uint8_t status;
    uint16_t actual_response_length;
    uint8_t reset_cmd[4];
    uint8_t response[NRBG_RESET_SERV_RESP_LENGTH];
    
    signal_request_start();
    
    reset_cmd[0] = NRBG_RESET_REQUEST_CMD;
    reset_cmd[1] = 0u;
    reset_cmd[2] = 0u;
    reset_cmd[3] = 0u;

    MSS_COMBLK_send_cmd(reset_cmd,                      /* p_cmd */
                        sizeof(reset_cmd),              /* cmd_size */
                        0,                              /* p_data */
                        0,                              /* data_size */
                        response,                       /* p_response */
                        DRBG_RESET_SERV_RESP_LENGTH,    /* response_size */
                        request_completion_handler);    /* completion_handler */
    
     actual_response_length = wait_for_request_completion();
    
    if((NRBG_RESET_SERV_RESP_LENGTH == actual_response_length) &&
       (NRBG_RESET_REQUEST_CMD == response[0]))
    {
        status = response[1];
    }
    else
    {
        status = MSS_SYS_UNEXPECTED_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_nrbg_self_test(void)
{
    uint8_t status;
    uint16_t actual_response_length;
    uint8_t self_test;
    uint8_t response[NRBG_SELF_TEST_SERV_RESP_LENGTH];
    
    signal_request_start();
    
    self_test = NRBG_SELF_TEST_REQUEST_CMD;

    MSS_COMBLK_send_cmd(&self_test,                         /* p_cmd */
                        sizeof(self_test),                  /* cmd_size */
                        0,                                  /* p_data */
                        0,                                  /* data_size */
                        response,                           /* p_response */
                        NRBG_SELF_TEST_SERV_RESP_LENGTH,    /* response_size */
                        request_completion_handler);        /* completion_handler */
    
    actual_response_length = wait_for_request_completion();
    
    if((NRBG_SELF_TEST_SERV_RESP_LENGTH == actual_response_length) &&
       (NRBG_SELF_TEST_REQUEST_CMD == response[0]))
    {
        status = response[1];
    }
    else
    {
        status = MSS_SYS_UNEXPECTED_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_nrbg_instantiate
(
    const uint8_t * personalization_str,
    uint16_t personalization_str_length,
    uint8_t * p_nrbg_handle
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t instantiate_params[7];
    uint8_t status;
    
    write_ptr_value_into_array(personalization_str, instantiate_params, 0u);
    
    instantiate_params[4] = (uint8_t)personalization_str_length;
    instantiate_params[5] = (uint8_t)(personalization_str_length >> 8u);
    instantiate_params[6] = INVALID_NRBG_HANDLE;
    
    status = execute_service(NRBG_INSTANTIATE_REQUEST_CMD,
                             instantiate_params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
                             
    if(MSS_SYS_SUCCESS == status)
    {
        *p_nrbg_handle = instantiate_params[6];
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_nrbg_generate
(
    const uint8_t * p_requested_data,
    const uint8_t * p_additional_input,
    uint8_t requested_length,
    uint8_t additional_input_length,
    uint8_t pr_req,
    uint8_t nrbg_handle
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t generate_params[12];
    uint8_t status;

    write_ptr_value_into_array(p_requested_data, generate_params, 0u);
    write_ptr_value_into_array(p_additional_input, generate_params, 4u);

    generate_params[8] = requested_length;
    generate_params[9] = additional_input_length;
    generate_params[10] = pr_req;
    generate_params[11] = nrbg_handle;
    
    status = execute_service(NRBG_GENERATE_REQUEST_CMD,
                             generate_params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_nrbg_reseed
(
    const uint8_t * p_additional_input,
    uint8_t additional_input_length,
    uint8_t nrbg_handle
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[6];
    uint8_t status;

    write_ptr_value_into_array(p_additional_input, params, 0u);

    params[4] = (uint8_t)additional_input_length;
    params[5] = nrbg_handle;
    
    status = execute_service(NRBG_RESEED_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_nrbg_uninstantiate
(
    uint8_t nrbg_handle
)
{
    uint8_t status;
    uint16_t actual_response_length;
    uint8_t uninstantiate_req[2];
    uint8_t response[NRBG_UNINST_SERV_RESP_LENGTH];
    
    signal_request_start();
    
    uninstantiate_req[0] = NRBG_UNINSTANTIATE_REQUEST_CMD;
    uninstantiate_req[1] = nrbg_handle;

    MSS_COMBLK_send_cmd(uninstantiate_req,              /* p_cmd */
                        sizeof(uninstantiate_req),      /* cmd_size */
                        0,                              /* p_data */
                        0,                              /* data_size */
                        response,                       /* p_response */
                        NRBG_UNINST_SERV_RESP_LENGTH,   /* response_size */
                        request_completion_handler);    /* completion_handler */
    
    actual_response_length = wait_for_request_completion();
    
    if((NRBG_UNINST_SERV_RESP_LENGTH == actual_response_length) &&
       (NRBG_UNINSTANTIATE_REQUEST_CMD == response[0]))
    {
        status = response[1];
    }
    else
    {
        status = MSS_SYS_UNEXPECTED_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
void MSS_SYS_zeroize_device(void)
{
    /*
     * We only need to send one command byte to initiate zeroization.
     * The zeroization process should result in the Cortex-M3 being reset. This
     * means we should never reach the end of this function if zeroization is
     * actually performed.
     */
    uint8_t zeroization_req = ZEROIZATION_REQUEST_CMD;
    
    /*
     * The Zeroization system service is not available on M2S050 rev A, rev B
     * and rev C.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    
    signal_request_start();
    
    MSS_COMBLK_send_cmd(&zeroization_req,               /* p_cmd */
                        sizeof(zeroization_req),        /* cmd_size */
                        0,                              /* p_data */
                        0,                              /* data_size */
                        0,                              /* p_response */
                        0,                              /* response_size */
                        request_completion_handler);    /* completion_handler */
    
    /* SAR 74647
     * Zeroization is only performed if the user has instantiated the tamper 
     * macro (from the Libero Catalog) in the hardware design, configured the
     * tamper macro to enable zeroization and set the required zeroization 
     * options. If program execution idles here, or in the 
     * wait_for_request_completion() function that follows, you should verify 
     * that zeroization is properly enabled in the hardware design.
     */
    ASSERT(g_request_in_progress == 0u);
    
    /*
     * Handle case where Zeroization is not enabled in the device in Release 
     * mode.
     */
    wait_for_request_completion();
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
#define NVM_FREQRNG_MASK        0x00001FE0U
#define NVM_FREQRNG_MAX         ((uint32_t)0xFFU << 5U)

static uint8_t g_isp_response[ISP_PROG_SERV_RESP_LENGTH];
sys_serv_isp_complete_handler_t g_isp_completion_handler = 0;
comblk_page_handler_t g_isp_page_read_handler = 0;

/*
 * g_initial_envm_cr contains the hardware design's original eNVM configuration
 * set through the ENVM_CR system register. This global variable is used to
 * store the eNVM's configuration while the ISP/IAP is executing with an eNVM
 * configuration ensuring successful eNVM programming on all SamrtFusion2
 * devices. It is then used to restore the eNVM's configuration once ISP/IAP has
 * completed. SAR 57545.
 */
static uint32_t g_initial_envm_cr = 0x00001FF1U;
/*
 * g_initial_mssddr_facc2_cr contains the hardware design's original MSS DDR 
 * Fabric Alignment Clock Controller (FACC) 2 configuration set through the 
 * MSSDDR_FACC2_CR system register. This global variable is used to
 * store the FACC2's configuration while the ISP/IAP is executing on all 
 * SamrtFusion2 devices. It is then used to restore the Fabric alignment clock 
 * configuration once ISP/IAP has completed.
 */
static uint32_t g_initial_mssddr_facc2_cr = 0x00;
static uint8_t g_mode = 0;
static uint8_t wait_for_clock_switch = 1;

static uint32_t isp_page_read_handler
(
    uint8_t const ** pp_next_page
)
{
    uint32_t remaining_length = 0;
    uint32_t running_on_standby_clock;
    volatile uint32_t timeout;
    
    if((g_mode !=  MSS_SYS_PROG_AUTHENTICATE) & (wait_for_clock_switch == 1))
    {
        timeout = DELAY_MORE_THAN_10US;
        do
        {
            running_on_standby_clock = SYSREG->MSSDDR_FACC1_CR & FACC_GLMUX_SEL_MASK;
            --timeout;
        }
        while ((running_on_standby_clock == 0U) && (timeout != 0U));
        wait_for_clock_switch = 0;
    }
    
    if(g_isp_page_read_handler != 0)
    {
        remaining_length = g_isp_page_read_handler(pp_next_page);
    }
    
    return remaining_length;
}

static void isp_sys_completion_handler
(
    uint8_t * p_response, 
    uint16_t length
)
{    
    if(g_mode != MSS_SYS_PROG_AUTHENTICATE)
    {
        /*
         * Restore the eNVM's frequency range to the values used before ISP was
         * started.
         */
        SYSREG->ENVM_CR = g_initial_envm_cr;
      
        /*
         * Restore the MSS DDR FACC 2 configuration to the values used before ISP 
         * was started.
         */
        SYSREG->MSSDDR_FACC2_CR = g_initial_mssddr_facc2_cr;
    }
    
    if(g_isp_completion_handler != 0)
    {
        g_isp_completion_handler(p_response[1]);
    }
}

uint8_t MSS_SYS_start_isp
(
    uint8_t mode,
    comblk_page_handler_t page_read_handler,
    sys_serv_isp_complete_handler_t isp_completion_handler
)
{
    uint8_t isp_prog_request[2];
    uint8_t clk_switch_status = CLOCK_SWITCHING_SUCCESS;
    uint8_t status = MSS_SYS_SUCCESS;
    
    if(mode == MSS_SYS_PROG_VERIFY)
    {
        /*
         * Check fabric digest before performing ISP verify
         */
        MSS_SYS_check_digest(MSS_SYS_DIGEST_CHECK_FABRIC);
    }
    
    g_mode = mode;
    
    if(mode != MSS_SYS_PROG_AUTHENTICATE)
    {
        /*
         * Keep a copy of the initial eNVM configuration used before ISP was
         * initiated. The eNVM configuration will be restored, as part of the ISP
         * completion handler, when ISP completes.
         */
        g_initial_envm_cr = SYSREG->ENVM_CR;

        /* Store the MSS DDR FACC 2 register value so that its can be restored back 
         * when the ISP operation is completed in asynchronous_event_handler. */
        g_initial_mssddr_facc2_cr = SYSREG->MSSDDR_FACC2_CR;

        /*
         * Set the eNVM's frequency range to its maximum. This is required to ensure
         * successful eNVM programming on all devices.
         */
        SYSREG->ENVM_CR = (g_initial_envm_cr & ~NVM_FREQRNG_MASK) | NVM_FREQRNG_MAX;        
    
        /* Select output of MUX 0, MUX 1 and MUX 2 during standby */
        SYSREG->MSSDDR_FACC2_CR = SYSREG->MSSDDR_FACC2_CR & ((uint32_t)(FACC_STANDBY_SEL << FACC_STANDBY_SHIFT) | ~FACC_STANDBY_SEL_MASK);
        
        /* Enable the signal for the 50 MHz RC oscillator */
        SYSREG->MSSDDR_FACC2_CR = SYSREG->MSSDDR_FACC2_CR | ((uint32_t)(MSS_25_50MHZ_EN << MSS_25_50MHZ_EN_SHIFT) & MSS_25_50MHZ_EN_MASK);
        
        /* Enable the signal for the 1 MHz RC oscillator */
        SYSREG->MSSDDR_FACC2_CR = SYSREG->MSSDDR_FACC2_CR | ((uint32_t)(MSS_1MHZ_EN << MSS_1MHZ_EN_SHIFT) & MSS_1MHZ_EN_MASK);
        
        /* SAR 80563
         * Cortex-M3 firmware dynamically divides down fclk, pclk0, pclk1 and
         * clk_fic64 to the divided by 32 versions based on device version.
         */
        clk_switch_status = clk_switching_fix();
        
        wait_for_clock_switch = 1;
    }
    
    if(clk_switch_status == CLOCK_SWITCHING_SUCCESS)
    {
        signal_request_start();
        
        isp_prog_request[0] = ISP_PROGRAMMING_REQUEST_CMD;
        isp_prog_request[1] = mode;
        
        g_isp_completion_handler = isp_completion_handler;
        
        g_isp_page_read_handler = page_read_handler;
        
        MSS_COMBLK_send_paged_cmd(isp_prog_request,                 /* p_cmd */
                                  sizeof(isp_prog_request),         /* cmd_size */
                                  g_isp_response,                   /* p_response */
                                  ISP_PROG_SERV_RESP_LENGTH,        /* response_size */
                                  isp_page_read_handler,            /* page_handler */
                                  isp_sys_completion_handler);      /* completion_handler */
    }
    else
    {
        /* SAR 80563
         * On 060 device. The user should make sure that the all divisor i.e 
         * fclk, pclk0, pclk1 and clk_fic64 divisor must be equal to each other 
         * and set to to divide by 1,2, 4, 8, 16(but not 32). 
         */
        status = MSS_SYS_CLK_DIVISOR_ERROR;
    }
    
    return status;
}


/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_initiate_iap
(
    uint8_t mode,
    uint32_t bitstream_spi_addr
)
{
    uint8_t status = MSS_SYS_SUCCESS;
    uint8_t clk_switch_status = CLOCK_SWITCHING_SUCCESS;
    uint16_t actual_response_length;
    uint8_t iap_prog_req[6];
    uint8_t response[IAP_PROG_SERV_RESP_LENGTH];
    
    if(mode == MSS_SYS_PROG_VERIFY)
    {
        /*
         * Check fabric digest before performing IAP verify
         */
        MSS_SYS_check_digest(MSS_SYS_DIGEST_CHECK_FABRIC);
    }
    
    if(mode != MSS_SYS_PROG_AUTHENTICATE)
    { 
        /*
         * Keep a copy of the initial eNVM configuration used before IAP was
         * initiated. The eNVM configuration will be restored, as part of the IAP
         * completion handler, when IAP completes.
         */
        g_initial_envm_cr = SYSREG->ENVM_CR;
     
        /* Store the MSS DDR FACC 2 register value so that its can be restored back 
         * when the IAP operation is completed.asynchronous_event_handler. */
        g_initial_mssddr_facc2_cr = SYSREG->MSSDDR_FACC2_CR;
        
        /*
         * Set the eNVM's frequency range to its maximum. This is required to ensure
         * successful eNVM programming on all devices.
         */
        SYSREG->ENVM_CR = (g_initial_envm_cr & ~NVM_FREQRNG_MASK) | NVM_FREQRNG_MAX;                

        /* Select output of MUX 0, MUX 1 and MUX 2 during standby */
        SYSREG->MSSDDR_FACC2_CR = SYSREG->MSSDDR_FACC2_CR & ((uint32_t)(FACC_STANDBY_SEL << FACC_STANDBY_SHIFT) | ~FACC_STANDBY_SEL_MASK);
        
        /* Enable the signal for the 50 MHz RC oscillator */
        SYSREG->MSSDDR_FACC2_CR = SYSREG->MSSDDR_FACC2_CR | ((uint32_t)(MSS_25_50MHZ_EN << MSS_25_50MHZ_EN_SHIFT) & MSS_25_50MHZ_EN_MASK);
        
        /* Enable the signal for the 1 MHz RC oscillator */
        SYSREG->MSSDDR_FACC2_CR = SYSREG->MSSDDR_FACC2_CR | ((uint32_t)(MSS_1MHZ_EN << MSS_1MHZ_EN_SHIFT) & MSS_1MHZ_EN_MASK);
        
        /* SAR 80563
         * Cortex-M3 firmware dynamically divides down fclk, pclk0, pclk1 and
         * clk_fic64 to the divided by 32 versions based on device version.
         */
        clk_switch_status = clk_switching_fix();
    }
    
    if(clk_switch_status == CLOCK_SWITCHING_SUCCESS)
    {
        /*
         * There is no response for Program mode because the Cortex-M3 will
         * get reset on completion of the system service.
         */
        iap_prog_req[0] = IAP_PROGRAMMING_REQUEST_CMD;
        iap_prog_req[1] = mode;

        iap_prog_req[2] = (uint8_t)(bitstream_spi_addr);
        iap_prog_req[3] = (uint8_t)(bitstream_spi_addr >> 8u);
        iap_prog_req[4] = (uint8_t)(bitstream_spi_addr >> 16u);
        iap_prog_req[5] = (uint8_t)(bitstream_spi_addr >> 24u);

        signal_request_start();
        
        MSS_COMBLK_send_cmd(iap_prog_req,                   /* p_cmd */
                            sizeof(iap_prog_req),           /* cmd_size */
                            0,                              /* p_data */
                            0,                              /* data_size */
                            response,                      /* p_response */
                            IAP_PROG_SERV_RESP_LENGTH,      /* response_size */
                            request_completion_handler);    /* completion_handler */
            
        /*
         * Handle case where service is not implemented/enabled in the device.
         */
        actual_response_length = wait_for_request_completion();
        
        if((IAP_PROG_SERV_RESP_LENGTH == actual_response_length) &&
           (IAP_PROGRAMMING_REQUEST_CMD == response[0]))
        {
            status = response[1];
        }
        else
        {
            status = MSS_SYS_UNEXPECTED_ERROR;
        }
        
        if(mode != MSS_SYS_PROG_AUTHENTICATE)
        {
            /* Restore back to original value. */
            SYSREG->ENVM_CR = g_initial_envm_cr;
            SYSREG->MSSDDR_FACC2_CR = g_initial_mssddr_facc2_cr;
        }
    }
    else
    {
        /* SAR 80563
         * On 060 device. The user should make sure that the all divisor i.e 
         * fclk, pclk0, pclk1 and clk_fic64 divisor must be equal to each other 
         * and set to to divide by 1,2, 4, 8, 16(but not 32). 
         */
        status = MSS_SYS_CLK_DIVISOR_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_check_digest
(
    uint8_t options
)
{
    uint8_t status;
    uint8_t clk_switch_status = CLOCK_SWITCHING_SUCCESS;
    uint16_t actual_response_length;
    uint8_t digest_check_req[2];
    uint8_t response[DIGEST_CHECK_SERV_RESP_LENGTH];
    
    /*
     * The Digest Check system service is not available on M2S050 rev A, rev B and rev C.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    
    /* 
     * Private ENVM factory digest and user digest is available only on G4X 
     * devices
     */
    if((options & 0x30u) != 0x00)
    {
        ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    }
    
    /* SAR 80563
     * Cortex-M3 firmware dynamically divides down fclk, pclk0, pclk1 and
     * clk_fic64 to the divided by 32 versions based on device version.
     */
    if(MSS_SYS_DIGEST_CHECK_FABRIC == (options & 0x01u))
    {
        clk_switch_status = clk_switching_fix();
    }
    
    if(clk_switch_status == CLOCK_SWITCHING_SUCCESS)
    {
      
        signal_request_start();

        digest_check_req[0] = DIGEST_CHECK_REQUEST_CMD;
        digest_check_req[1] = options;

        MSS_COMBLK_send_cmd(digest_check_req,               /* p_cmd */
                            sizeof(digest_check_req),       /* cmd_size */
                            0,                              /* p_data */
                            0u,                             /* data_size */
                            response,                       /* p_response */
                            DIGEST_CHECK_SERV_RESP_LENGTH,  /* response_size */
                            request_completion_handler);    /* completion_handler */

        actual_response_length = wait_for_request_completion();

        if((DIGEST_CHECK_SERV_RESP_LENGTH == actual_response_length) &&
           (DIGEST_CHECK_REQUEST_CMD == response[0]))
        {
            status = response[1];
        }
        else
        {
            status = MSS_SYS_UNEXPECTED_ERROR;
        }
    }
    else
    {
        /* SAR 80563
         * On 060 device. The user should make sure that the all divisor i.e 
         * fclk, pclk0, pclk1 and clk_fic64 divisor must be equal to each other 
         * and set to to divide by 1,2, 4, 8, 16(but not 32). 
         */
        status = MSS_SYS_CLK_DIVISOR_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_puf_create_activation_code
(
    void
)
{
    uint8_t response[PUF_USER_ACTIVATION_CODE_RESP_LENGTH];
    uint8_t status;
    uint8_t params;
    uint8_t key_numbers = 0u;
    
    /*
     * The user activation code system service is not available on M2S050 rev A,
     * rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);

    params = PUF_CREATE_USER_ACTIVATION_CODE;
    
    status = execute_service(PUF_ACTIVATION_CODE_REQUEST_CMD,
                             &params,
                             response,
                             PUF_USER_ACTIVATION_CODE_RESP_LENGTH);  
    
    /*
     * System controller is locking eNVM-1 while executing create activation 
     * code service, but system controller is not releasing back after 
     * completing the operation. In order to unlock eNVM-1, call get number of 
     * key service. PUF get number of key service will release the eNVM-1 lock
     * after reading the number of keys enrolled.
     */
    MSS_SYS_puf_get_number_of_keys(&key_numbers);
    
    return status;
}
    
/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_puf_delete_activation_code
(
    void
)
{
    uint8_t response[PUF_USER_ACTIVATION_CODE_RESP_LENGTH];
    uint8_t status;
    uint8_t params;
    uint8_t key_numbers = 0u;
    
    /*
     * The user activation code system service is not available on M2S050 rev A,
     * rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    params = PUF_DELETE_USER_ACTIVATION_CODE;
    
    status = execute_service(PUF_ACTIVATION_CODE_REQUEST_CMD,
                             &params,
                             response,
                             PUF_USER_ACTIVATION_CODE_RESP_LENGTH);
    /*
     * System controller is locking eNVM-1 while executing delete activation 
     * code service, but system controller is not releasing back after 
     * completing the operation. In order to unlock eNVM-1, call get number of 
     * key service. PUF get number of key service will release the eNVM-1 lock
     * after reading the number of keys enrolled.
     */
    MSS_SYS_puf_get_number_of_keys(&key_numbers);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_puf_get_number_of_keys
(
    uint8_t* p_number_of_keys
)
{
    uint8_t response[6u] = { 0x00 };
    uint8_t params[11u] =  { 0x00 };
    uint8_t status;
    
    /*
     * The user key code system service is not available on M2S050 rev A,
     * rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);

    params[0] = PUF_GET_NUMBER_OF_KC_SUBCOMMAND;    
    
    status = execute_service(PUF_USER_KEY_CODE_REQUEST_CMD,
                             params,
                             response,
                             PUF_GET_NUMBER_OF_KEYS_RESP_LENGTH);
    
    *p_number_of_keys = params[9];
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_puf_enroll_key
(
    uint8_t key_number,
    uint16_t key_size,
    uint8_t* p_key_value,
    uint8_t* p_key_location
)
{
    uint8_t response[6u];
    uint8_t params[11u];
    uint8_t status;
    uint8_t key_numbers = 0u;
    
    /*
     * The PUF enroll key system service is not available on M2S050 rev A,
     * rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);

    if(p_key_value == 0)
    {
        params[0] = PUF_CREATE_INT_KC_SUBCOMMAND;
    }
    else
    {
        params[0] = PUF_CREATE_EXT_KC_SUBCOMMAND;
    }
    
    write_ptr_value_into_array(p_key_location, params, 1u);
    write_ptr_value_into_array(p_key_value, params, 5u);
    
    params[9] = key_number;
    params[10] = key_size;
    
    status = execute_service(PUF_USER_KEY_CODE_REQUEST_CMD,
                             params,
                             response,
                             PUF_ENROLL_KEYS_RESP_LENGTH);
    
    /*
     * System controller is locking eNVM-1 while executing create key code 
     * service, but system controller is not releasing back after completing the
     * operation. In order to unlock eNVM-1, call get number of key service. PUF
     * get number of key service will release the eNVM-1 lock after reading the 
     * number of keys enrolled.
     */
    MSS_SYS_puf_get_number_of_keys(&key_numbers);
       
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_puf_delete_key
(
    uint8_t key_number
)
{
    uint8_t response[6u];
    uint8_t params[11u];
    uint8_t status;
    uint8_t key_numbers = 0u;
    
    /*
     * The delete PUF key system service is not available on M2S050 rev A,
     * rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);

    params[0] = PUF_DELETE_KC_SUBCOMMAND;
    params[9] = key_number;
        
    status = execute_service(PUF_USER_KEY_CODE_REQUEST_CMD,
                             params,
                             response,
                             PUF_ENROLL_KEYS_RESP_LENGTH);
       
    /*
     * System controller is locking eNVM-1 while executing delete key code 
     * service, but system controller is not releasing back after completing the
     * operation. In order to unlock eNVM-1, call get number of key service. PUF
     * get number of key service will release the eNVM-1 lock after reading the 
     * number of keys enrolled.
     */
    MSS_SYS_puf_get_number_of_keys(&key_numbers);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_puf_fetch_key
(
    uint8_t key_number,
    uint8_t ** pp_key
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[5];
    uint8_t status;
    
    /*
     * The fetch user key system service is not available on M2S050 rev A,
     * rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    write_ptr_value_into_array(*pp_key, params, 0u);
    
    params[4] = key_number;
    
    status = execute_service(PUF_FETCH_KEY_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
    if(pp_key != NULL)
    {
        write_array_into_ptr_value(&(*pp_key), params, 0);
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_puf_export_keycodes
(
    uint8_t * p_keycodes
)
{
    uint8_t response[PUF_EXPORT_ALL_KEYCODES_RESP_LENGTH];
    uint8_t params[11u];
    uint8_t status;
    
    /*
     * The export all user key system service is not available on M2S050 rev A,
     * rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);

    params[0] = PUF_EXPORT_ALL_KC_SUBCOMMAND;
    
    write_ptr_value_into_array(p_keycodes, params, 1u);
        
    status = execute_service(PUF_USER_KEY_CODE_REQUEST_CMD,
                             params,
                             response,
                             PUF_EXPORT_ALL_KEYCODES_RESP_LENGTH);
       
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_puf_import_keycodes
(
    uint8_t * p_keycodes
)
{
    uint8_t response[PUF_IMPORT_ALL_KEYCODES_RESP_LENGTH];
    uint8_t params[11u];
    uint8_t status;
    
    /*
     * The import all key code system service is not available on M2S050 rev A,
     * rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);

    params[0] = PUF_IMPORT_ALL_KC_SUBCOMMAND;
    
    write_ptr_value_into_array(p_keycodes, params, 1u);
    
    status = execute_service(PUF_USER_KEY_CODE_REQUEST_CMD,
                             params,
                             response,
                             PUF_IMPORT_ALL_KEYCODES_RESP_LENGTH);
        
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_puf_fetch_ecc_public_key
(
    uint8_t* p_puf_public_key
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[4];
    uint8_t status;

    /*
     * The fetch puf ecc public key system service is not available on M2S050
     * rev A, rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    write_ptr_value_into_array(p_puf_public_key, params, 0u);
    
    status = execute_service(PUF_ECC_PUBLIC_KEY_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_puf_get_random_seed
(
    uint8_t* p_puf_seed
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[4];
    uint8_t status;
    
    /*
     * The get puf seed system service is not available on M2S050 rev A, rev B,
     * rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    write_ptr_value_into_array(p_puf_seed, params, 0u);
    
    status = execute_service(PUF_SEED_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_ecc_point_multiplication
(
    uint8_t* p_scalar_d,
    uint8_t* p_point_p,
    uint8_t* p_point_q
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[12];
    uint8_t status;
    
    /*
     * The ECC point multiplication system service is not available on M2S050 
     * rev A, rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    write_ptr_value_into_array(p_scalar_d, params, 0u);
    write_ptr_value_into_array(p_point_p, params, 4u);
    write_ptr_value_into_array(p_point_q, params, 8u);
    
    status = execute_service(POINT_MULTIPLICATION_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_ecc_point_addition
(
    uint8_t* p_point_p,
    uint8_t* p_point_q,
    uint8_t* p_point_r
)
{
    uint8_t response[STANDARD_SERV_RESP_LENGTH];
    uint8_t params[12];
    uint8_t status;
    
    /*
     * The ECC point addition system service is not available on M2S050 
     * rev A, rev B, rev C and rev D.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    write_ptr_value_into_array(p_point_p, params, 0u);
    write_ptr_value_into_array(p_point_q, params, 4u);
    write_ptr_value_into_array(p_point_r, params, 8u);
    
    status = execute_service(POINT_ADDITION_REQUEST_CMD,
                             params,
                             response,
                             STANDARD_SERV_RESP_LENGTH);
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
void MSS_SYS_ecc_get_base_point
(
    uint8_t* p_point_g
)
{
    const uint8_t base_point_g[] = 
    {
        0xaa, 0x87, 0xca, 0x22, 0xbe, 0x8b, 0x05, 0x37, 0x8e, 0xb1, 0xc7, 0x1e,
        0xf3, 0x20, 0xad, 0x74, 0x6e, 0x1d, 0x3b, 0x62, 0x8b, 0xa7, 0x9b, 0x98,
        0x59, 0xf7, 0x41, 0xe0, 0x82, 0x54, 0x2a, 0x38, 0x55, 0x02, 0xf2, 0x5d,
        0xbf, 0x55, 0x29, 0x6c, 0x3a, 0x54, 0x5e, 0x38, 0x72, 0x76, 0x0a, 0xB7,
        0x36, 0x17, 0xde, 0x4a, 0x96, 0x26, 0x2c, 0x6f, 0x5d, 0x9e, 0x98, 0xbf,
        0x92, 0x92, 0xdc, 0x29, 0xf8, 0xf4, 0x1d, 0xbd, 0x28, 0x9a, 0x14, 0x7c,
        0xe9, 0xda, 0x31, 0x13, 0xb5, 0xf0, 0xb8, 0xc0, 0x0a, 0x60, 0xb1, 0xce,
        0x1d, 0x7e, 0x81, 0x9d, 0x7a, 0x43, 0x1d, 0x7c, 0x90, 0xea, 0x0e, 0x5F
    };
    
    memcpy(p_point_g, &base_point_g[0], sizeof(base_point_g));
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_start_clock_monitor
(
    void
)
{
    uint8_t status;
    uint8_t tamper_control_req[2];
    uint8_t response[TAMPER_CONTROL_SERV_RESP_LENGTH];
    uint16_t actual_response_length;
    
    /*
     * The Start clock monitoring tamper Control service is available only on 
     * G4X device.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    signal_request_start();
    
    tamper_control_req[0] = TAMPER_CONTROL_REQUEST_CMD;
    tamper_control_req[1] = 0x01u;

    MSS_COMBLK_send_cmd(tamper_control_req,                 /* p_cmd */
                        sizeof(tamper_control_req),         /* cmd_size */
                        0,                                  /* p_data */
                        0u,                                 /* data_size */
                        response,                           /* p_response */
                        TAMPER_CONTROL_SERV_RESP_LENGTH,    /* response_size */
                        request_completion_handler);        /* completion_handler */
    
    actual_response_length = wait_for_request_completion();
    
    if((TAMPER_CONTROL_SERV_RESP_LENGTH == actual_response_length) &&
       (TAMPER_CONTROL_REQUEST_CMD == response[0]))
    {
        status = response[1];
    }
    else
    {
        status = MSS_SYS_UNEXPECTED_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_stop_clock_monitor
(
    void
)
{
    uint8_t status;
    uint8_t tamper_control_req[2];
    uint8_t response[TAMPER_CONTROL_SERV_RESP_LENGTH];
    uint16_t actual_response_length;
    
    /*
     * The Stop clock monitoring tamper Control service is available only on 
     * G4X device.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    signal_request_start();
    
    tamper_control_req[0] = TAMPER_CONTROL_REQUEST_CMD;
    tamper_control_req[1] = 0x02u;

    MSS_COMBLK_send_cmd(tamper_control_req,                 /* p_cmd */
                        sizeof(tamper_control_req),         /* cmd_size */
                        0,                                  /* p_data */
                        0u,                                 /* data_size */
                        response,                           /* p_response */
                        TAMPER_CONTROL_SERV_RESP_LENGTH,    /* response_size */
                        request_completion_handler);        /* completion_handler */
    
    actual_response_length = wait_for_request_completion();
    
    if((TAMPER_CONTROL_SERV_RESP_LENGTH == actual_response_length) &&
       (TAMPER_CONTROL_REQUEST_CMD == response[0]))
    {
        status = response[1];
    }
    else
    {
        status = MSS_SYS_UNEXPECTED_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_enable_puf_power_down
(
    void
)
{
    uint8_t status;
    uint8_t tamper_control_req[2];
    uint8_t response[TAMPER_CONTROL_SERV_RESP_LENGTH];
    uint16_t actual_response_length;
    
    /*
     * The Enable PUF power down service is available only on G4X device.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    signal_request_start();
    
    tamper_control_req[0] = TAMPER_CONTROL_REQUEST_CMD;
    tamper_control_req[1] = 0x04u;

    MSS_COMBLK_send_cmd(tamper_control_req,                 /* p_cmd */
                        sizeof(tamper_control_req),         /* cmd_size */
                        0,                                  /* p_data */
                        0u,                                 /* data_size */
                        response,                           /* p_response */
                        TAMPER_CONTROL_SERV_RESP_LENGTH,    /* response_size */
                        request_completion_handler);        /* completion_handler */
    
    actual_response_length = wait_for_request_completion();
    
    if((TAMPER_CONTROL_SERV_RESP_LENGTH == actual_response_length) &&
       (TAMPER_CONTROL_REQUEST_CMD == response[0]))
    {
        status = response[1];
    }
    else
    {
        status = MSS_SYS_UNEXPECTED_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_disable_puf_power_down
(
    void
)
{
    uint8_t status;
    uint8_t tamper_control_req[2];
    uint8_t response[TAMPER_CONTROL_SERV_RESP_LENGTH];
    uint16_t actual_response_length;
    
    /*
     * Disable PUF power down is available only on G4X device.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    signal_request_start();
    
    tamper_control_req[0] = TAMPER_CONTROL_REQUEST_CMD;
    tamper_control_req[1] = 0x08u;

    MSS_COMBLK_send_cmd(tamper_control_req,                 /* p_cmd */
                        sizeof(tamper_control_req),         /* cmd_size */
                        0,                                  /* p_data */
                        0u,                                 /* data_size */
                        response,                           /* p_response */
                        TAMPER_CONTROL_SERV_RESP_LENGTH,    /* response_size */
                        request_completion_handler);        /* completion_handler */
    
    actual_response_length = wait_for_request_completion();
    
    if((TAMPER_CONTROL_SERV_RESP_LENGTH == actual_response_length) &&
       (TAMPER_CONTROL_REQUEST_CMD == response[0]))
    {
        status = response[1];
    }
    else
    {
        status = MSS_SYS_UNEXPECTED_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_clear_lock_parity
(
    void
)
{
    uint8_t status;
    uint8_t tamper_control_req[2];
    uint8_t response[TAMPER_CONTROL_SERV_RESP_LENGTH];
    uint16_t actual_response_length;
    
    /*
     * The Clear Lock parity is available only on G4X device.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    signal_request_start();
    
    tamper_control_req[0] = TAMPER_CONTROL_REQUEST_CMD;
    tamper_control_req[1] = 0x10u;

    MSS_COMBLK_send_cmd(tamper_control_req,                 /* p_cmd */
                        sizeof(tamper_control_req),         /* cmd_size */
                        0,                                  /* p_data */
                        0u,                                 /* data_size */
                        response,                           /* p_response */
                        TAMPER_CONTROL_SERV_RESP_LENGTH,    /* response_size */
                        request_completion_handler);        /* completion_handler */
    
    actual_response_length = wait_for_request_completion();
    
    if((TAMPER_CONTROL_SERV_RESP_LENGTH == actual_response_length) &&
       (TAMPER_CONTROL_REQUEST_CMD == response[0]))
    {
        status = response[1];
    }
    else
    {
        status = MSS_SYS_UNEXPECTED_ERROR;
    }
    
    return status;
}

/*==============================================================================
 * See mss_sys_services.h for details.
 */
uint8_t MSS_SYS_clear_mesh_short
(
    void
)
{
    uint8_t status;
    uint8_t tamper_control_req[2];
    uint8_t response[TAMPER_CONTROL_SERV_RESP_LENGTH];
    uint16_t actual_response_length;
    
    /*
     * The Clear mesh short service is available only on G4X device.
     */
    ASSERT(0x0000F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0001F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0002F802u != SYSREG->DEVICE_VERSION);
    ASSERT(0x0003F802u != SYSREG->DEVICE_VERSION);
    
    signal_request_start();
    
    tamper_control_req[0] = TAMPER_CONTROL_REQUEST_CMD;
    tamper_control_req[1] = 0x20u;

    MSS_COMBLK_send_cmd(tamper_control_req,                 /* p_cmd */
                        sizeof(tamper_control_req),         /* cmd_size */
                        0,                                  /* p_data */
                        0u,                                 /* data_size */
                        response,                           /* p_response */
                        TAMPER_CONTROL_SERV_RESP_LENGTH,    /* response_size */
                        request_completion_handler);        /* completion_handler */
    
    actual_response_length = wait_for_request_completion();
    
    if((TAMPER_CONTROL_SERV_RESP_LENGTH == actual_response_length) &&
       (TAMPER_CONTROL_REQUEST_CMD == response[0]))
    {
        status = response[1];
    }
    else
    {
        status = MSS_SYS_UNEXPECTED_ERROR;
    }
    
    return status;
}

/*==============================================================================
 *
 */
static uint8_t execute_service
(
    uint8_t cmd_opcode,
    uint8_t * cmd_params_ptr,
    uint8_t * response,
    uint16_t response_length
)
{
    uint8_t status;
    uint16_t actual_response_length;
    
    signal_request_start();
    
    MSS_COMBLK_send_cmd_with_ptr(cmd_opcode,                    /* cmd_opcode */
                                 (uint32_t)cmd_params_ptr,      /* cmd_params_ptr */
                                 response,                      /* p_response */
                                 response_length,               /* response_size */
                                 request_completion_handler);   /* completion_handler */
    
    actual_response_length = wait_for_request_completion();
    
    if((response_length == actual_response_length) && (cmd_opcode == response[0]))
    {
        status = response[1];
    }
    else
    {
        status = MSS_SYS_UNEXPECTED_ERROR;
    }
    
    return status;
}

/*==============================================================================
 *
 */
static void request_completion_handler
(
    uint8_t * p_response,
    uint16_t response_size
)
{
    g_request_in_progress = 0u;
    g_last_response_length = response_size;
}

/*==============================================================================
 *
 */
static void signal_request_start(void)
{
    /* Wait for current request to complete. */
    while(g_request_in_progress)
    {
        ;
    }
    
    g_request_in_progress = 1u;
    g_last_response_length = 0u;
}

/*==============================================================================
 *
 */
static uint16_t wait_for_request_completion(void)
{
    while(g_request_in_progress)
    {
        ;
    }
    
    return g_last_response_length;
}

/*==============================================================================
 *
 */
static void write_ptr_value_into_array
(
    const uint8_t * pointer,
    uint8_t target_array[],
    uint32_t array_index
)
{
    target_array[array_index] = (uint8_t)((uint32_t)pointer);
    target_array[array_index + 1] = (uint8_t)((uint32_t)pointer >> 8u);
    target_array[array_index + 2] = (uint8_t)((uint32_t)pointer >> 16u);
    target_array[array_index + 3] = (uint8_t)((uint32_t)pointer >> 24u);
}

/*==============================================================================
  Function to write array address to pointer location.
 */
static void write_array_into_ptr_value
(
    uint8_t** pointer,
    uint8_t target_array[],
    uint32_t array_index
)
{
    uint32_t var;
    
    var = (uint32_t)target_array[array_index + 3];
    var = ((var << 8u) & 0xFFFFFF00) | target_array[array_index + 2];
    var = ((var << 8u) & 0xFFFFFF00) | target_array[array_index + 1];
    var = ((var << 8u) & 0xFFFFFF00) | target_array[array_index];
    
    *pointer = (uint8_t*)var;
}

