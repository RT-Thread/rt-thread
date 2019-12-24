/* ------------------------------------------
 * Copyright (c) 2016, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \version 2016.05
 * \date 2014-06-17
 * \author Huaqi Fang(Huaqi.Fang@synopsys.com)
--------------------------------------------- */

/**
 * \defgroup	DEVICE_HAL_GPIO		GPIO Device HAL Interface
 * \ingroup	DEVICE_HAL_DEF
 * \brief	definitions for gpio device hardware layer (\ref dev_gpio.h)
 * \details	provide interfaces for gpio driver to implement
 *  Here is a diagram for the gpio interface.
 *
 *  \htmlonly
 *  <div class="imagebox">
 *      <div style="width: 600px">
 *          <img src="pic/dev_gpio_hal.jpg" alt="GPIO Device HAL Interface Diagram"/>
 *          <p>GPIO Device HAL Interface Diagram</p>
 *      </div>
 *  </div>
 *  \endhtmlonly
 *
 * @{
 *
 * \file
 * \brief	gpio device hardware layer definitions
 * \details	Provide common definitions for gpio device,
 * 	then the software developer can develop gpio driver
 * 	following these definitions, and the applications
 * 	can directly call this definition to realize functions
 *
 */

#ifndef _DEVICE_HAL_GPIO_H_
#define _DEVICE_HAL_GPIO_H_

#include "device/device_hal/inc/dev_common.h"

/**
 * \defgroup	DEVICE_HAL_GPIO_DEFDIR	GPIO Port Direction Definition
 * \ingroup	DEVICE_HAL_GPIO
 * \brief	Define macros to indicate gpio directions
 * @{
 */
/*
 * defines for gpio directions
 */
#define GPIO_DIR_INPUT				(0)		/*!< gpio works as input */
#define GPIO_DIR_OUTPUT				(1)		/*!< gpio works as output */
/** @} */

/**
 * \defgroup	DEVICE_HAL_GPIO_CTRLCMD		GPIO Device Control Commands
 * \ingroup	DEVICE_HAL_GPIO
 * \brief	Definitions for gpio control command, used in \ref dev_gpio::gpio_control "GPIO IO Control"
 * \details	These commands defined here can be used in user code directly.
 * - Parameters Usage
 *   - For passing parameters like integer, just use uint32_t/int32_t to directly pass values
 *   - For passing parameters for a structure, please use pointer to pass values
 *   - For getting some data, please use pointer to store the return data
 * - Common Return Values
 *   - \ref E_OK,	Control device successfully
 *   - \ref E_CLSED,	Device is not opened
 *   - \ref E_OBJ,	Device object is not valid or not exists
 *   - \ref E_PAR,	Parameter is not valid for current control command
 *   - \ref E_SYS,	Control device failed, due to hardware issues such as device is disabled
 *   - \ref E_NOSPT,	Control command is not supported or not valid
 * @{
 */
/**
 * Set the \ref dev_gpio_info::direction "direction" of masked bits of gpio port into \ref GPIO_DIR_INPUT "input"
 * - Param type : uint32_t
 * - Param usage : 1 in each bit will be masked.
 * - Return value explanation :
 */
#define GPIO_CMD_SET_BIT_DIR_INPUT			DEV_SET_SYSCMD(0)
/**
 * Set the \ref dev_gpio_info::direction "direction" of masked bits of gpio port into \ref GPIO_DIR_OUTPUT "output"
 * - Param type : uint32_t
 * - Param usage : 1 in each bit will be masked.
 * - Return value explanation :
 */
#define GPIO_CMD_SET_BIT_DIR_OUTPUT			DEV_SET_SYSCMD(1)
/**
 * Get \ref dev_gpio_info::direction "gpio port direction".
 * - Param type : uint32_t
 * - Param usage : 1 bit for 1 bit of gpio port, 0 for input, 1 for output
 * - Return value explanation :
 */
#define GPIO_CMD_GET_BIT_DIR				DEV_SET_SYSCMD(2)
/**
 * Set gpio interrupt configuration for each bit.
 * - Param type : \ref DEV_GPIO_INT_CFG *
 * - Param usage : store gpio interrupt configuration for each bit.
 * - Return value explanation :
 */
#define GPIO_CMD_SET_BIT_INT_CFG			DEV_SET_SYSCMD(3)
/**
 * Get gpio interrupt configuration for each bit.
 * - Param type : \ref DEV_GPIO_INT_CFG *
 * - Param usage : First set int_bit_mask in DEV_GPIO_INT_CFG structure to
 * the mask of which bit of GPIO you want to get. And the interrupt configuration
 * will be stored in the structure DEV_GPIO_INT_CFG, each bit stand for each bit of port.
 * - Return value explanation :
 */
#define GPIO_CMD_GET_BIT_INT_CFG			DEV_SET_SYSCMD(4)
/**
 * Set gpio service routine for each bit.
 * - Param type : \ref DEV_GPIO_BIT_ISR *
 * - Param usage : store gpio handler information for each bit, int handler's param will be DEV_GPIO *.
 * - Return value explanation :
 */
#define GPIO_CMD_SET_BIT_ISR				DEV_SET_SYSCMD(5)
/**
 * Get gpio service routine for each bit.
 * - Param type : \ref DEV_GPIO_BIT_ISR *
 * - Param usage : By passing int_bit_ofs in DEV_GPIO_BIT_ISR,
 * it will return interrupt handler for this bit and store it in int_bit_handler.
 * - Return value explanation :
 */
#define GPIO_CMD_GET_BIT_ISR				DEV_SET_SYSCMD(6)
/**
 * Enable gpio interrupt of the masked bits.
 * - Param type : uint32_t
 * - Param usage : 1 in each bit will be masked.
 * - Return value explanation :
 */
#define GPIO_CMD_ENA_BIT_INT				DEV_SET_SYSCMD(7)
/**
 * Disable gpio interrupt of the masked bits.
 * - Param type : uint32_t
 * - Param usage : 1 in each bit will be masked.
 * - Return value explanation :
 */
#define GPIO_CMD_DIS_BIT_INT				DEV_SET_SYSCMD(8)
/**
 * Get \ref dev_gpio_info::method "gpio interrupt enable status".
 * - Param type : uint32_t *
 * - Param usage : 1 bit for 1 bit of gpio port, 0 for poll, 1 for interrupt
 * - Return value explanation :
 */
#define GPIO_CMD_GET_BIT_MTHD				DEV_SET_SYSCMD(9)
/* @} */

/**
 * \defgroup	DEVICE_HAL_GPIO_INT_CFG_SET	GPIO Device Int Configuration Settings
 * \ingroup	DEVICE_HAL_GPIO
 * \brief	definition of gpio interrupt type
 * @{
 */

/* GPIO Mask Defintions */
/** Mask none bits of the max 32bits */
#define GPIO_BITS_MASK_NONE			(0)
/** Mask all bits of the max 32bits */
#define GPIO_BITS_MASK_ALL			(0XFFFFFFFF)

/* GPIO Interrupt Type Related Definitions */

/** Level sensitive interrupt type for 1 bit */
#define GPIO_INT_LEVEL_TRIG			(0)
/** Edge sensitive interrupt type for 1 bit */
#define GPIO_INT_EDGE_TRIG			(1)
/** Level sensitive interrupt type for all 32 bits */
#define GPIO_INT_LEVEL_TRIG_ALL			(0)
/** Edge sensitive interrupt type for all 32 bits */
#define GPIO_INT_EDGE_TRIG_ALL			(0XFFFFFFFF)

/* For bit settings */
/** Set bit interrupt type of gpio into level sensitive */
#define GPIO_INT_BIT_LEVEL_TRIG(bit_ofs)	(GPIO_INT_LEVEL_TRIG<<(bit_ofs))
/** Set bit interrupt type of gpio into edge sensitive */
#define GPIO_INT_BIT_EDGE_TRIG(bit_ofs)		(GPIO_INT_EDGE_TRIG<<(bit_ofs))
/* For bits settings */
/** Set interrupt type of masked bits of gpio into level sensitive */
#define GPIO_INT_BITS_LEVEL_TRIG(bit_mask)	(GPIO_INT_LEVEL_TRIG_ALL&(bit_mask))
/** Set bit interrupt type of gpio into edge sensitive */
#define GPIO_INT_BITS_EDGE_TRIG(bit_mask)	(GPIO_INT_EDGE_TRIG_ALL&(bit_mask))

/* GPIO Interrupt Polarity Related Definitions */

/** GPIO Interrupt polarity type enum */
typedef enum gpio_int_polarity {
	/* Polarity for 1 bit */
	GPIO_INT_ACTIVE_LOW   = 0, /*!< Active low for level-sensitive interrupt for 1 bit */
	GPIO_INT_FALLING_EDGE = 0, /*!< Falling-edge for edge-sensitive interrupt for 1 bit */
	GPIO_INT_ACTIVE_HIGH =  1, /*!< Active high for level-sensitive interrupt for 1 bit */
	GPIO_INI_RISING_EDGE = 1, /*!< Rising-edge for edge-sensitive interrupt for 1 bit */
	/* Polartiy for all 32 bits */
	GPIO_INT_ACTIVE_LOW_ALL   = 0, /*!< Active low for level-sensitive interrupt for all bits */
	GPIO_INT_FALLING_EDGE_ALL = 0, /*!< Falling-edge for edge-sensitive interrupt for all bits */
	GPIO_INT_ACTIVE_HIGH_ALL =  0XFFFFFFFF, /*!< Active high for level-sensitive interrupt for all bits */
	GPIO_INI_RISING_EDGE_ALL = 0XFFFFFFFF /*!< Rising-edge for edge-sensitive interrupt for all bits */
} GPIO_INT_POLARITY;

/* For bit settings */
/** Set bit polarity of gpio into active low */
#define GPIO_INT_BIT_POL_ACT_LOW(bit_ofs)	(GPIO_INT_ACTIVE_LOW<<(bit_ofs))
/** Set bit polarity of gpio into active high */
#define GPIO_INT_BIT_POL_ACT_HIGH(bit_ofs)	(GPIO_INT_ACTIVE_HIGH<<(bit_ofs))
/** Set bit polarity of gpio into falling edge */
#define GPIO_INT_BIT_POL_FALL_EDGE(bit_ofs)	(GPIO_INT_FALLING_EDGE<<(bit_ofs))
/** Set bit polarity of gpio into rising edge */
#define GPIO_INT_BIT_POL_RISE_EDGE(bit_ofs)	(GPIO_INI_RISING_EDGE<<(bit_ofs))

/* For bits settings */
/** Set polarity of masked bits of gpio into active low */
#define GPIO_INT_BITS_POL_ACT_LOW(bit_mask)	(GPIO_INT_ACTIVE_LOW_ALL&(bit_mask))
/** Set polarity of masked bits of gpio into active high */
#define GPIO_INT_BITS_POL_ACT_HIGH(bit_mask)	(GPIO_INT_ACTIVE_HIGH_ALL&(bit_mask))
/** Set polarity of masked bits of gpio into falling edge */
#define GPIO_INT_BITS_POL_FALL_EDGE(bit_mask)	(GPIO_INT_FALLING_EDGE_ALL&(bit_mask))
/** Set polarity of masked bits of gpio into rising edge */
#define GPIO_INT_BITS_POL_RISE_EDGE(bit_mask)	(GPIO_INI_RISING_EDGE_ALL&(bit_mask))

/* GPIO Interrupt Debounce Related Definitions */

/* For bit settings */
/** Disable debounce circuitry for 1 bit */
#define GPIO_INT_NO_DEBOUNCE			(0)
/** Enable debounce circuitry for 1 bit */
#define GPIO_INT_DEBOUNCE			(1)

/* For bits settings */
/** Disable debounce circuitry for all bits */
#define GPIO_INT_NO_DEBOUNCE_ALL		(0)
/** Enable debounce circuitry for all bits */
#define GPIO_INT_DEBOUNCE_ALL			(0XFFFFFFFF)

/* For bit settings */
/** Set bit interrupt debounce of gpio into enabled */
#define GPIO_INT_BIT_ENA_DEBOUNCE(bit_ofs)	(GPIO_INT_DEBOUNCE<<(bit_ofs))
/** Set bit interrupt debounce of gpio into disabled */
#define GPIO_INT_BIT_DIS_DEBOUNCE(bit_ofs)	(GPIO_INT_NO_DEBOUNCE<<(bit_ofs))
/* For bits settings */
/** Set bit interrupt debounce of gpio into enabled */
#define GPIO_INT_BITS_ENA_DEBOUNCE(bit_mask)	(GPIO_INT_DEBOUNCE_ALL&(bit_mask))
/** Set bit interrupt debounce of gpio into disabled */
#define GPIO_INT_BITS_DIS_DEBOUNCE(bit_mask)	(GPIO_INT_NO_DEBOUNCE_ALL&(bit_mask))

/** GPIO interrupt configuration */
typedef struct dev_gpio_int_cfg {
	uint32_t int_bit_mask;		/*!< interrupt bit mask for gpio */
	uint32_t int_bit_type;		/*!< \ref GPIO_INT_LEVEL_TRIG "level sensitive" or \ref GPIO_INT_EDGE_TRIG "edge sensitive" for each gpio bit */
	uint32_t int_bit_polarity;	/*!< active high or low, refer to \ref GPIO_INT_POLARITY for each gpio bit */
	uint32_t int_bit_debounce;	/*!< \ref GPIO_INT_DEBOUNCE "enable" or \ref GPIO_INT_NO_DEBOUNCE "disable" debounce logic for each gpio bit */
} DEV_GPIO_INT_CFG, * DEV_GPIO_INT_CFG_PTR;

/** Default interrupt configuration for all gpio bits */
static const DEV_GPIO_INT_CFG gpio_int_cfg_default = \
	{GPIO_BITS_MASK_ALL, GPIO_INT_LEVEL_TRIG_ALL, \
		GPIO_INT_ACTIVE_LOW_ALL, GPIO_INT_NO_DEBOUNCE_ALL};

/** GPIO interrupt handler or Interrupt Service Routine(ISR) */
typedef void (*DEV_GPIO_HANDLER) (void *ptr);

/** interrupt handler for each port bit */
typedef struct dev_gpio_bit_isr {
	uint32_t int_bit_ofs;			/*!< int bit offset */
	DEV_GPIO_HANDLER int_bit_handler;	/*!< interrupt handler */
} DEV_GPIO_BIT_ISR, * DEV_GPIO_BIT_ISR_PTR;
/* @} */

/**
 * \defgroup	DEVICE_HAL_GPIO_DEVSTRUCT	GPIO Device Interface Definition
 * \ingroup	DEVICE_HAL_GPIO
 * \brief	contains definitions of gpio device structure.
 * \details	This structure will be used in user implemented code, which was called
 *     \ref DEVICE_IMPL "Device Driver Implement Layer" for gpio to use in implementation code.
 *     Application developer should use the GPIO API provided here to access to GPIO devices.
 *     BSP developer should follow the API definition to implement GPIO device drivers.
 * @{
 */
/**
 * \brief	gpio information struct definition
 * \details	informations about gpio open count, working status
 * 	gpio registers and control block, gpio io direction and interrupt/poll for each bit of gpio
 * \note	Only available for gpio with max 32bits
 */
typedef struct dev_gpio_info {
	void *gpio_ctrl;	/*!< gpio control related pointer, implemented by bsp developer, and this should be set during gpio object implementation */
	uint32_t opn_cnt;	/*!< gpio open count, open it will increase 1, close it will decrease 1, 0 for close, >0 for open */
	uint32_t direction;	/*!< each bit direction of this GPIO, default all \ref GPIO_DIR_INPUT "input" for first open */
	uint32_t method;	/*!< int/poll method for each bit of GPIO, 0 for poll, 1 for interrupt, default all \ref DEV_POLL_METHOD "poll" for first open */
	void * extra;		/*!< a extra pointer to get hook to applications which should not used by bsp developer,
					this should be NULL for first open and you can \ref DEV_GPIO_INFO_SET_EXTRA_OBJECT "set"
					or \ref DEV_GPIO_INFO_GET_EXTRA_OBJECT "get" the extra information pointer */
} DEV_GPIO_INFO, * DEV_GPIO_INFO_PTR;
/** Set extra information pointer of gpio info */
#define DEV_GPIO_INFO_SET_EXTRA_OBJECT(gpio_info_ptr, extra_info)	(gpio_info_ptr)->extra = (void *)(extra_info)
/** Get extra information pointer of gpio info */
#define DEV_GPIO_INFO_GET_EXTRA_OBJECT(gpio_info_ptr)			((gpio_info_ptr)->extra)

/** Method of all gpio bits set to poll */
#define DEV_GPIO_BITS_MTHD_POLL			(0)
/** Method of all gpio bits set to interrupt */
#define DEV_GPIO_BITS_MTHD_INTERRUPT		(0xFFFFFFFF)
/** Default method of all gpio bits should be poll for first open */
#define DEV_GPIO_BITS_MTHD_DEFAULT		(DEV_GPIO_BITS_MTHD_POLL)

/**
 * \brief	gpio device interface definition
 * \details	define gpio device interface, like gpio information structure,
 * 	fuctions to open/close/control gpio, write or read data via gpio
 * \note	all this details are implemented by user in user porting code
 */
typedef struct dev_gpio {
	DEV_GPIO_INFO gpio_info;		/*!< gpio device information */
	int32_t (*gpio_open) (uint32_t dir);	/*!< open gpio device with pre-defined gpio direction */
	int32_t (*gpio_close) (void);		/*!< close gpio device */
	int32_t (*gpio_control) (uint32_t ctrl_cmd, void *param);	/*!< control gpio device */
	int32_t (*gpio_write) (uint32_t val, uint32_t mask);	/*!< write gpio device with val, only write the masked bits */
	int32_t (*gpio_read) (uint32_t *val, uint32_t mask);	/*!< read gpio device val, only read the masked bits */
} DEV_GPIO, * DEV_GPIO_PTR;

/**
 * \fn		int32_t (* dev_gpio::gpio_open) (uint32_t dir)
 * \details	Open a gpio device with pre-defined io direction.
 * \param[in]	dir	gpio direction for each bit
 * \retval	E_OK	Open successfully without any issues
 * \retval	E_OPNED	If device was opened before with different parameters,
 *			then just increase the \ref dev_gpio_info::opn_cnt "opn_cnt" and return \ref E_OPNED
 * \retval	E_OBJ	Device object is not valid
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_NOSPT	Open settings are not supported
 */

/**
 * \fn		int32_t (* dev_gpio::gpio_close) (void)
 * \details	Close an gpio device, just decrease the \ref dev_gpio_info::opn_cnt "opn_cnt",
 *      if \ref dev_gpio_info::opn_cnt "opn_cnt" equals 0, then close the device
 * \retval	E_OK	Close successfully without any issues(including scenario that device is already closed)
 * \retval	E_OPNED	Device is still opened, the device \ref dev_gpio_info::opn_cnt "opn_cnt" decreased by 1
 * \retval	E_OBJ	Device object is not valid
 */

/**
 * \fn		int32_t (* dev_gpio::gpio_control) (uint32_t ctrl_cmd, void *param)
 * \details	Control an gpio device by \ref ctrl_cmd, with passed \ref param.
 * 	you can control gpio device using predefined gpio control commands defined using \ref DEV_SET_SYSCMD
 * 	(which must be implemented by bsp developer), such as \ref GPIO_CMD_SET_BIT_DIR_INPUT
 * 	"change masked gpio direction to input", and \ref DEVICE_HAL_GPIO_CTRLCMD "more".
 * 	And you can also control gpio device using your own specified commands defined using \ref DEV_SET_USRCMD,
 * 	but these specified commands should be defined in your own gpio device driver implementation.
 * \param[in]		ctrl_cmd	\ref DEVICE_HAL_GPIO_CTRLCMD "control command", to change or get some thing related to gpio
 * \param[in,out]	param		parameters that maybe argument of the command, or return values of the command
 * \retval	E_OK	Control device successfully
 * \retval	E_CLSED	Device is not opened
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid for current control command
 * \retval	E_SYS	Control device failed, due to hardware issues
 * \retval	E_CTX	Control device failed, due to different reasons like in transfer state
 * \retval	E_NOSPT	Control command is not supported or not valid, such as interrupt is not supported
 */

/**
 * \fn		int32_t (* dev_gpio::gpio_write) (uint32_t val, uint32_t mask)
 * \details	Write gpio with \ref val, and only change the masked bits of gpio.
 * \param[in]	val	the data that need to write to gpio
 * \param[in]	mask	gpio bit mask
 * \retval	E_OK	Write gpio with specified value successfully
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid
 */

/**
 * \fn		int32_t (* dev_gpio::gpio_read) (uint32_t *val, uint32_t mask)
 * \details	Read the masked gpio value
 * \param[out]	val	pointer to data need to read from gpio
 * \param[in]	mask	gpio bit mask
 * \retval	E_OK	Read gpio data successfully
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid
 */

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief	get an \ref dev_gpio "gpio device" by gpio device id.
 * 	For how to use gpio device hal refer to \ref dev_gpio "Functions in gpio device structure"
 * \param[in]	gpio_id	id of gpio, defined by user
 * \retval	!NULL	pointer to an \ref dev_gpio "gpio device structure"
 * \retval	NULL	failed to find the gpio device by \ref gpio_id
 * \note	need to implemented by user in user code
 */
extern DEV_GPIO_PTR gpio_get_dev(int32_t gpio_id);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* _DEVICE_HAL_GPIO_H_ */
