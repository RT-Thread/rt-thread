
#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


#if defined(__cplusplus)
extern "C" {
#endif


#define PCR_IBE_ibe1 0x01u /*!<@brief Input Buffer Enable: Enables */



#define FLEXIO_DATA0_FXIOD_INDEX    16U

#define FLEXIO_DATA0_PORT           PORT2
#define FLEXIO_DATA0_PIN            8U
#define FLEXIO_DATA0_MUX            6U

#define FLEXIO_DATA1_PORT           PORT2
#define FLEXIO_DATA1_PIN            9U
#define FLEXIO_DATA1_MUX            6U

#define FLEXIO_DATA2_PORT           PORT2
#define FLEXIO_DATA2_PIN            10U
#define FLEXIO_DATA2_MUX            6U

#define FLEXIO_DATA3_PORT           PORT2
#define FLEXIO_DATA3_PIN            11U
#define FLEXIO_DATA3_MUX            6U

#define FLEXIO_DATA4_PORT           PORT4
#define FLEXIO_DATA4_PIN            12U
#define FLEXIO_DATA4_MUX            6U

#define FLEXIO_DATA5_PORT           PORT4
#define FLEXIO_DATA5_PIN            13U
#define FLEXIO_DATA5_MUX            6U

#define FLEXIO_DATA6_PORT           PORT4
#define FLEXIO_DATA6_PIN            14U
#define FLEXIO_DATA6_MUX            6U

#define FLEXIO_DATA7_PORT           PORT4
#define FLEXIO_DATA7_PIN            15U
#define FLEXIO_DATA7_MUX            6U

#define FLEXIO_DATA8_PORT           PORT4
#define FLEXIO_DATA8_PIN            16U
#define FLEXIO_DATA8_MUX            6U

#define FLEXIO_DATA9_PORT           PORT4
#define FLEXIO_DATA9_PIN            17U
#define FLEXIO_DATA9_MUX            6U

#define FLEXIO_DATA10_PORT          PORT4
#define FLEXIO_DATA10_PIN           18U
#define FLEXIO_DATA10_MUX           6U

#define FLEXIO_DATA11_PORT          PORT4
#define FLEXIO_DATA11_PIN           19U
#define FLEXIO_DATA11_MUX           6U

#define FLEXIO_DATA12_PORT          PORT4
#define FLEXIO_DATA12_PIN           20U
#define FLEXIO_DATA12_MUX           6U

#define FLEXIO_DATA13_PORT          PORT4
#define FLEXIO_DATA13_PIN           21U
#define FLEXIO_DATA13_MUX           6U

#define FLEXIO_DATA14_PORT          PORT4
#define FLEXIO_DATA14_PIN           22U
#define FLEXIO_DATA14_MUX           6U

#define FLEXIO_DATA15_PORT          PORT4
#define FLEXIO_DATA15_PIN           23U
#define FLEXIO_DATA15_MUX           6U

#define FLEXIO_WR_PIN_FXIOD_INDEX   1U                     /* WR pin */
#define FLEXIO_WR_PORT              PORT0
#define FLEXIO_WR_PIN               9U
#define FLEXIO_WR_GPIO              GPIO0
#define FLEXIO_WR_PIN_MUX           6U

#define FLEXIO_RD_PIN_FXIOD_INDEX   0U                     /* RD pin */
#define FLEXIO_RD_PORT              PORT0
#define FLEXIO_RD_PIN               8U
#define FLEXIO_RD_GPIO              GPIO0
#define FLEXIO_RD_PIN_MUX           6U

#define FLEXIO_CS_PORT              PORT0
#define FLEXIO_CS_PIN               12U                     /* CS pin */
#define FLEXIO_CS_GPIO              GPIO0

#define FLEXIO_RS_PORT              PORT0
#define FLEXIO_RS_PIN               7U                     /* RS pin */
#define FLEXIO_RS_GPIO              GPIO0

#define FLEXIO_ReSet_PORT              PORT4
#define FLEXIO_ReSet_PIN               7U                     /* RS pin */
#define FLEXIO_ReSet_GPIO              GPIO4

void BOARD_InitBootPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/* Configure port mux of FlexIO data pins */
void FLEXIO_8080_Config_Data_Pin(void);

/* Configure WR pin as FlexIO function */
void FLEXIO_8080_Config_WR_FlexIO(void);

/* Configure WR pin as GPIO function and outputting high level */
void FLEXIO_8080_Config_WR_GPIO(void);

/* Configure RD pin as FlexIO function */
void FLEXIO_8080_Config_RD_FlexIO(void);

/* Configure RD pin as GPIO function and outputting high level */
void FLEXIO_8080_Config_RD_GPIO(void);

/* Configure CS pin as GPIO function and outputting high level */
void FLEXIO_8080_Config_CS_GPIO(void);

/* Set CS pin's level */
void FLEXIO_8080_Set_CS_Pin(bool level);

/* Configure RS pin as GPIO function and outputting high level */
void FLEXIO_8080_Config_RS_GPIO(void);

/* Set RS pin's level */
void FLEXIO_8080_Set_RS_Pin(bool level);


/* Configure ReSet pin as GPIO function and outputting high level */
void FLEXIO_8080_Config_ReSet_GPIO(void);

/* Set ReSet pin's level */
void FLEXIO_8080_Set_ReSet_Pin(bool level);

void LPSPI1_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
