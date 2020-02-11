#ifndef _RT_NRF_GPIO_H_
#define _RT_NRF_GPIO_H_

#define RT_GPIO_SENSE_Pos (0UL) /*!< Position of SENSE field. */
#define RT_GPIO_SENSE_Msk (0x3UL << RT_GPIO_SENSE_Pos) /*!< Bit mask of SENSE field. */

#define RT_GPIO_POLARITY_Pos (2UL) /*!< Position of SENSE field. */
#define RT_GPIO_POLARITY_Msk (0x3UL << RT_GPIO_POLARITY_Pos) /*!< Bit mask of SENSE field. */

#define RT_GPIO_MODE_SET(polarity,sense)   (((polarity << RT_GPIO_POLARITY_Pos) & RT_GPIO_POLARITY_Msk) | ((sense << RT_GPIO_SENSE_Pos) & RT_GPIO_SENSE_Msk)) /*!< Bit mask of SENSE field. */

int rt_hw_pin_init(void);

#endif

