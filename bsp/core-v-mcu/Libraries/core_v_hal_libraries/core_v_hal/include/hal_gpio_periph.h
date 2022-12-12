/*
 * Copyright (C) 2019 ETH Zurich, University of Bologna
 * and GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HAL_INCLUDE_HAL_GPIO_PERIPH_H_
#define HAL_INCLUDE_HAL_GPIO_PERIPH_H_


/* ----------------------------------------------------------------------------
   -- GPIO Peripheral Access Layer --
   ---------------------------------------------------------------------------- */

/** GPIO_Type Register Layout Typedef */
typedef struct
{
	volatile uint32_t paddir; /**< GPIO pad direction configuration register. */
	volatile uint32_t gpioen; /**< GPIO pad enable configuration register. */
	volatile uint32_t padin; /**< GPIO pad input value register. */
	volatile uint32_t padout; /**< GPIO pad output value register. */
	volatile uint32_t padoutset; /**< GPIO pad output set register. */
	volatile uint32_t padoutclr; /**< GPIO pad output clear register. */
	volatile uint32_t inten; /**< GPIO pad interrupt enable configuration register. */
	volatile uint32_t inttype[2]; /**< GPIO pad interrupt type bit 0 & 1 configuration register. */
	volatile uint32_t intstatus; /**< GPIO pad interrupt status register. */
	volatile uint32_t padcfg[4]; /**< GPIO pad pin configuration register : 0-7, 8-15, 16-23, 23-31. */
} gpio_t;


/* ----------------------------------------------------------------------------
   -- GPIO Register Bitfield Access --
   ---------------------------------------------------------------------------- */

/*! @name PADDIR */
/* GPIO direction configuration bitfield:
  - bit[i]=1'b0: Input mode for GPIO[i]
  - bit[i]=1'b1: Output mode for GPIO[i] */
#define GPIO_PADDIR_DIR_MASK                                         (0xffffffff)
#define GPIO_PADDIR_DIR_SHIFT                                        (0)
#define GPIO_PADDIR_DIR(val)                                         (((uint32_t)(((uint32_t)(val)) << GPIO_PADDIR_DIR_SHIFT)) & GPIO_PADDIR_DIR_MASK)


/*! @name GPIOEN */
/* GPIO clock enable configuration bitfield:
  - bit[i]=1'b0: disable clock for GPIO[i]
  - bit[i]=1'b1: enable clock for GPIO[i]
  GPIOs are gathered by groups of 4. The clock gating of one group is done only if all 4 GPIOs are disabled.
  Clock must be enabled for a GPIO if it's direction is configured in input mode. */
#define GPIO_GPIOEN_GPIOEN_MASK                                      (0xffffffff)
#define GPIO_GPIOEN_GPIOEN_SHIFT                                     (0)
#define GPIO_GPIOEN_GPIOEN(val)                                      (((uint32_t)(((uint32_t)(val)) << GPIO_GPIOEN_GPIOEN_SHIFT)) & GPIO_GPIOEN_GPIOEN_MASK)


/*! @name PADIN */
/* GPIO input data read bitfield. DATA_IN[i] corresponds to input data of GPIO[i]. */
#define GPIO_PADIN_DATA_IN_MASK                                      (0xffffffff)
#define GPIO_PADIN_DATA_IN_SHIFT                                     (0)
#define GPIO_PADIN_DATA_IN(val)                                      (((uint32_t)(((uint32_t)(val)) << GPIO_PADIN_DATA_IN_SHIFT)) & GPIO_PADIN_DATA_IN_MASK)


/*! @name PADOUT */
/* GPIO output data read bitfield. DATA_OUT[i] corresponds to output data set on GPIO[i]. */
#define GPIO_PADOUT_DATA_OUT_MASK                                    (0xffffffff)
#define GPIO_PADOUT_DATA_OUT_SHIFT                                   (0)
#define GPIO_PADOUT_DATA_OUT(val)                                    (((uint32_t)(((uint32_t)(val)) << GPIO_PADOUT_DATA_OUT_SHIFT)) & GPIO_PADOUT_DATA_OUT_MASK)


/*! @name PADOUTSET */
/* GPIO output data read bitfield. DATA_OUT[i] corresponds to output data set on GPIO[i]. */
#define GPIO_PADOUTSET_DATA_OUT_MASK                                    (0xffffffff)
#define GPIO_PADOUTSET_DATA_OUT_SHIFT                                   (0)
#define GPIO_PADOUTSET_DATA_OUT(val)                                    (((uint32_t)(((uint32_t)(val)) << GPIO_PADOUTSET_DATA_OUT_SHIFT)) & GPIO_PADOUTSET_DATA_OUT_MASK)


/*! @name PADOUTCLEAR */
/* GPIO output data read bitfield. DATA_OUT[i] corresponds to output data set on GPIO[i]. */
#define GPIO_PADOUTCLR_DATA_OUT_MASK                                    (0xffffffff)
#define GPIO_PADOUTCLR_DATA_OUT_SHIFT                                   (0)
#define GPIO_PADOUTCLR_DATA_OUT(val)                                    (((uint32_t)(((uint32_t)(val)) << GPIO_PADOUTCLR_DATA_OUT_SHIFT)) & GPIO_PADOUTCLR_DATA_OUT_MASK)


/*! @name INTEN */
/* GPIO interrupt enable configuration bitfield:
  - bit[i]=1'b0: disable interrupt for GPIO[i]
  - bit[i]=1'b1: enable interrupt for GPIO[i] */
#define GPIO_INTEN_INTEN_MASK                                        (0xffffffff)
#define GPIO_INTEN_INTEN_SHIFT                                       (0)
#define GPIO_INTEN_INTEN(val)                                        (((uint32_t)(((uint32_t)(val)) << GPIO_INTEN_INTEN_SHIFT)) & GPIO_INTEN_INTEN_MASK)


/*! @name INTTYPE0 */
/* GPIO[15:0] interrupt type configuration bitfield:
  - bit[2*i+1:2*i]=2'b00: interrupt on falling edge for GPIO[i]
  - bit[2*i+1:2*i]=2'b01: interrupt on rising edge for GPIO[i]
  - bit[2*i+1:2*i]=2'b10: interrupt on rising and falling edge for GPIO[i]
  - bit[2*i+1:2*i]=2'b11: RFU */
#define GPIO_INTTYPE_INTTYPE_MASK                                    (0xffffffff)
#define GPIO_INTTYPE_INTTYPE_SHIFT                                   (0)
#define GPIO_INTTYPE_INTTYPE(val)                                    (((uint32_t)(((uint32_t)(val)) << GPIO_INTTYPE_INTTYPE_SHIFT)) & GPIO_INTTYPE_INTTYPE_MASK)


/*! @name INTSTATUS */
/* GPIO Interrupt status flags bitfield. INTSTATUS[i]=1 when interrupt received on GPIO[i]. INTSTATUS is cleared when it is red. GPIO interrupt line is also cleared when INTSTATUS register is red. */
#define GPIO_INTSTATUS_INTSTATUS_MASK                                (0xffffffff)
#define GPIO_INTSTATUS_INTSTATUS_SHIFT                               (0)
#define GPIO_INTSTATUS_INTSTATUS(val)                                (((uint32_t)(((uint32_t)(val)) << GPIO_INTSTATUS_INTSTATUS_SHIFT)) & GPIO_INTSTATUS_INTSTATUS_MASK)


/*! @name PADCFG */
/* GPIO[i] pull activation configuration bitfield:
  - 1'b0: pull disabled
  - 1'b1: pull enabled */
#define GPIO_PADCFG_GPIO_PE_MASK                                     (0x1)
#define GPIO_PADCFG_GPIO_PE_SHIFT                                    (0)
#define GPIO_PADCFG_GPIO_PE(val)                                     (((uint32_t)(((uint32_t)(val)) << GPIO_PADCFG_GPIO_PE_SHIFT)) & GPIO_PADCFG_GPIO_PE_MASK)


/* GPIO[i] drive strength configuration bitfield:
  - 1'b0: low drive strength
  - 1'b1: high drive strength */
#define GPIO_PADCFG_GPIO_DS_MASK                                     (0x2)
#define GPIO_PADCFG_GPIO_DS_SHIFT                                    (1)
#define GPIO_PADCFG_GPIO_DS(val)                                     (((uint32_t)(((uint32_t)(val)) << GPIO_PADCFG_GPIO_DS_SHIFT)) & GPIO_PADCFG_GPIO_DS_MASK)


/*! @name PADDIR */
typedef union
{
    struct
    {
	/* GPIO direction configuration bitfield:
	- bit[i]=1'b0: Input mode for GPIO[i]
	- bit[i]=1'b1: Output mode for GPIO[i] */
	uint32_t dir:32;
    } field;
    uint32_t word;
} gpio_paddir_t;

/*! @name PADIN */
typedef union
{
    struct
    {
	/* GPIO input data read bitfield. DATA_IN[i] corresponds to input data of GPIO[i]. */
	uint32_t data_in:32;
    } field;
    uint32_t word;
} gpio_padin_t;

/*! @name PADOUT */
typedef union
{
    struct
    {
	/* GPIO output data read bitfield. DATA_OUT[i] corresponds to output data set on GPIO[i]. */
	uint32_t data_out:32;
    } field;
    uint32_t word;
} gpio_padout_t;

/*! @name INTEN */
typedef union
{
    struct
    {
	/* GPIO interrupt enable configuration bitfield:
	- bit[i]=1'b0: disable interrupt for GPIO[i]
	- bit[i]=1'b1: enable interrupt for GPIO[i] */
	uint32_t inten:32;
    } field;
    uint32_t word;
} gpio_inten_t;

/*! @name INTTYPE */
typedef union
{
    struct
    {
	/* GPIO[15:0] interrupt type configuration bitfield:
	- bit[2*i+1:2*i]=2'b00: interrupt on falling edge for GPIO[i]
	- bit[2*i+1:2*i]=2'b01: interrupt on rising edge for GPIO[i]
	- bit[2*i+1:2*i]=2'b10: interrupt on rising and falling edge for GPIO[i]
	- bit[2*i+1:2*i]=2'b11: RFU */
	uint32_t inttype:32;
    } field;
    uint32_t word;
} gpio_inttype0_t;

/*! @name INTSTATUS */
typedef union
{
    struct
    {
	/* GPIO Interrupt status flags bitfield. INTSTATUS[i]=1 when interrupt received on GPIO[i]. INTSTATUS is cleared when it is red. GPIO interrupt line is also cleared when INTSTATUS register is red. */
	uint32_t intstatus:32;
    } field;
    uint32_t word;
} gpio_intstatus_t;

/*! @name GPIOEN */
typedef union
{
    struct
    {
	/* GPIO clock enable configuration bitfield:
	- bit[i]=1'b0: disable clock for GPIO[i]
	- bit[i]=1'b1: enable clock for GPIO[i]
	GPIOs are gathered by groups of 4. The clock gating of one group is done only if all 4 GPIOs are disabled.
	Clock must be enabled for a GPIO if it's direction is configured in input mode. */
	uint32_t gpioen:32;
    } field;
    uint32_t word;
} gpio_gpioen_t;

/*! @name PADCFG */
typedef union
{
    struct
    {
	/* GPIO[0] pull activation configuration bitfield:
	- 1'b0: pull disabled
	- 1'b1: pull enabled */
	uint32_t gpio0_pe:1;
	/* GPIO[0] drive strength configuration bitfield:
	- 1'b0: low drive strength
	- 1'b1: high drive strength */
	uint32_t gpio0_ds:1;
	uint32_t reserved_0:6;
	/* GPIO[1] pull activation configuration bitfield:
	- 1'b0: pull disabled
	- 1'b1: pull enabled */
	uint32_t gpio1_pe:1;
	/* GPIO[1] drive strength configuration bitfield:
	- 1'b0: low drive strength
	- 1'b1: high drive strength */
	uint32_t gpio1_ds:1;
	uint32_t reserved_1:6;
	/* GPIO[2] pull activation configuration bitfield:
	- 1'b0: pull disabled
	- 1'b1: pull enabled */
	uint32_t gpio2_pe:1;
	/* GPIO[2] drive strength configuration bitfield:
	- 1'b0: low drive strength
	- 1'b1: high drive strength */
	uint32_t gpio2_ds:1;
	uint32_t reserved_2:6;
	/* GPIO[3] pull activation configuration bitfield:
	- 1'b0: pull disabled
	- 1'b1: pull enabled */
	uint32_t gpio3_pe:1;
	/* GPIO[3] drive strength configuration bitfield:
	- 1'b0: low drive strength
	- 1'b1: high drive strength */
	uint32_t gpio3_ds:1;
    } field;
    uint32_t word;
} gpio_padcfg_t;


/* ----------------------------------------------------------------------------

 CMD IDs and macros

----------------------------------------------------------------------------*/

#endif /* HAL_INCLUDE_HAL_GPIO_PERIPH_H_ */
