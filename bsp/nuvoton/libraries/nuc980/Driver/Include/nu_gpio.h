/**************************************************************************//**
 * @file     GPIO.h
 * @brief    GPIO driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_GPIO_H__
#define __NU_GPIO_H__

#ifdef __cplusplus
    #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
    #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */


#ifdef __cplusplus
extern "C"
{
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup GPIO General Purpose Input/Output Controller(GPIO)
    Memory Mapped Structure for GPIO Controller
@{ */


typedef struct
{

    /**
     * @var GPIO_T::MODE
     * Offset: 0x00/0x40/0x80/0xC0/0x100/0x140/0x180/0x1C0  Port A-H I/O Mode Control
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2n+1:2n]|MODEn    |Port A-H I/O Pin[n] Mode Control
     * |        |          |Determine each I/O mode of Px.n pins.
     * |        |          |00 = Px.n is in Input mode.
     * |        |          |01 = Px.n is in Push-pull Output mode.
     * |        |          |10 = Px.n is in Open-drain Output mode.
     * |        |          |11 = Px.n is in Quasi-bidirectional mode.
     * |        |          |Note1: The initial value of this field is defined by CIOINI (CONFIG0 [10]).
     * |        |          |If CIOINI is set to 0, the default value is 0xFFFF_FFFF and all pins will be quasi-bidirectional mode after chip powered on.
     * |        |          |If CIOINI is set to 1, the default value is 0x0000_0000 and all pins will be input mode after chip powered on.
     * |        |          |Note2:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::DINOFF
     * Offset: 0x04/0x44/0x84/0xC4/0x104/0x144/0x184/0x1C4  Port A-H Digital Input Path Disable Control
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n+16]  |DINOFFn   |Port A-H Pin[n] Digital Input Path Disable Control
     * |        |          |Each of these bits is used to control if the digital input path of corresponding Px.n pin is disabled.
     * |        |          |If input is analog signal, users can disable Px.n digital input path to avoid input current leakage.
     * |        |          |0 = Px.n digital input path Enabled.
     * |        |          |1 = Px.n digital input path Disabled (digital input tied to low).
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::DOUT
     * Offset: 0x08/0x48/0x88/0xC8/0x108/0x148/0x188/0x1C8  Port A-H Data Output Value
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n]     |DOUTn     |Port A-H Pin[n] Output Value
     * |        |          |Each of these bits controls the status of a Px.n pin when the Px.n is configured as Push-pull output, Open-drain output or Quasi-bidirectional mode.
     * |        |          |0 = Px.n will drive Low if the Px.n pin is configured as Push-pull output, Open-drain output or Quasi-bidirectional mode.
     * |        |          |1 = Px.n will drive High if the Px.n pin is configured as Push-pull output or Quasi-bidirectional mode.
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::DATMSK
     * Offset: 0x0C/0x4C/0x8C/0xCC/0x10C/0x14C/0x18C/0x1CC  Port A-H Data Output Write Mask
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n]     |DATMSKn    |Port A-H Pin[n] Data Output Write Mask
     * |        |          |These bits are used to protect the corresponding DOUT (Px_DOUT[n]) bit.
     * |        |          |When the DATMSK (Px_DATMSK[n]) bit is set to 1, the corresponding DOUT (Px_DOUT[n]) bit is protected.
     * |        |          |If the write signal is masked, writing data to the protect bit is ignored.
     * |        |          |0 = Corresponding DOUT (Px_DOUT[n]) bit can be updated.
     * |        |          |1 = Corresponding DOUT (Px_DOUT[n]) bit protected.
     * |        |          |Note1: This function only protects the corresponding DOUT (Px_DOUT[n]) bit, and will not protect the corresponding PDIO (Pxn_PDIO[n]) bit.
     * |        |          |Note2:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::PIN
     * Offset: 0x10/0x50/0x90/0xD0/0x110/0x150/0x190/0x1D0  Port A-H Pin Value
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n]     |PINn      |Port A-H Pin[n] Pin Value
     * |        |          |Each bit of the register reflects the actual status of the respective Px.n pin.
     * |        |          |If the bit is 1, it indicates the corresponding pin status is high; else the pin status is low.
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::DBEN
     * Offset: 0x14/0x54/0x94/0xD4/0x114/0x154/0x194/0x1D4  Port A-H De-Bounce Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n]     |DBENn     |Port A-H Pin[n] Input Signal De-Bounce Enable Bit
     * |        |          |The DBEN[n] bit is used to enable the de-bounce function for each corresponding bit.
     * |        |          |If the input signal pulse width cannot be sampled by continuous two de-bounce sample cycle, the input signal transition is seen as the signal bounce and will not trigger the interrupt.
     * |        |          |The de-bounce clock source is controlled by DBCLKSRC (GPIO_DBCTL [4]), one de-bounce sample cycle period is controlled by DBCLKSEL (GPIO_DBCTL [3:0]).
     * |        |          |0 = Px.n de-bounce function Disabled.
     * |        |          |1 = Px.n de-bounce function Enabled.
     * |        |          |The de-bounce function is valid only for edge triggered interrupt.
     * |        |          |If the interrupt mode is level triggered, the de-bounce enable bit is ignored.
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::INTTYPE
     * Offset: 0x18/0x58/0x98/0xD8/0x118/0x158/0x198/0x1D8  Port A-H Interrupt Trigger Type Control
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n]     |TYPEn     |Port A-H Pin[n] Edge or Level Detection Interrupt Trigger Type Control
     * |        |          |TYPE (Px_INTTYPE[n]) bit is used to control the triggered interrupt is by level trigger or by edge trigger.
     * |        |          |If the interrupt is by edge trigger, the trigger source can be controlled by de-bounce.
     * |        |          |If the interrupt is by level trigger, the input source is sampled by one HCLK clock and generates the interrupt.
     * |        |          |0 = Edge trigger interrupt.
     * |        |          |1 = Level trigger interrupt.
     * |        |          |If the pin is set as the level trigger interrupt, only one level can be set on the registers RHIEN (Px_INTEN[n+16])/FLIEN (Px_INTEN[n]).
     * |        |          |If both levels to trigger interrupt are set, the setting is ignored and no interrupt will occur.
     * |        |          |The de-bounce function is valid only for edge triggered interrupt.
     * |        |          |If the interrupt mode is level triggered, the de-bounce enable bit is ignored.
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::INTEN
     * Offset: 0x1C/0x5C/0x9C/0xDC/0x11C/0x15C/0x19C/0x1DC  Port A-H Interrupt Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n]     |FLIENn    |Port A-H Pin[n] Falling Edge or Low Level Interrupt Trigger Type Enable Bit
     * |        |          |The FLIEN (Px_INTEN[n]) bit is used to enable the interrupt for each of the corresponding input Px.n pin.
     * |        |          |Set bit to 1 also enable the pin wake-up function.
     * |        |          |When setting the FLIEN (Px_INTEN[n]) bit to 1 :
     * |        |          |If the interrupt is level trigger (TYPE (Px_INTTYPE[n]) bit is set to 1), the input Px.n pin will generate the interrupt while this pin state is at low level.
     * |        |          |If the interrupt is edge trigger(TYPE (Px_INTTYPE[n]) bit is set to 0), the input Px.n pin will generate the interrupt while this pin state changed from high to low.
     * |        |          |0 = Px.n level low or high to low interrupt Disabled.
     * |        |          |1 = Px.n level low or high to low interrupt Enabled.
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * |[n+16]  |RHIENn    |Port A-H Pin[n] Rising Edge or High Level Interrupt Trigger Type Enable Bit
     * |        |          |The RHIEN (Px_INTEN[n+16]) bit is used to enable the interrupt for each of the corresponding input Px.n pin
     * |        |          |Set bit to 1 also enable the pin wake-up function.
     * |        |          |When setting the RHIEN (Px_INTEN[n+16]) bit to 1 :
     * |        |          |If the interrupt is level trigger (TYPE (Px_INTTYPE[n]) bit is set to 1), the input Px.n pin will generate the interrupt while this pin state is at high level.
     * |        |          |If the interrupt is edge trigger (TYPE (Px_INTTYPE[n]) bit is set to 0), the input Px.n pin will generate the interrupt while this pin state changed from low to high.
     * |        |          |0 = Px.n level high or low to high interrupt Disabled.
     * |        |          |1 = Px.n level high or low to high interrupt Enabled.
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::INTSRC
     * Offset: 0x20/0x60/0xA0/0xE0/0x120/0x160/0x1A0/0x1E0  Port A-H Interrupt Source Flag
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n]     |INTSRCn   |Port A-H Pin[n] Interrupt Source Flag
     * |        |          |Write Operation :
     * |        |          |0 = No action.
     * |        |          |1 = Clear the corresponding pending interrupt.
     * |        |          |Read Operation :
     * |        |          |0 = No interrupt at Px.n.
     * |        |          |1 = Px.n generates an interrupt.
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::SMTEN
     * Offset: 0x24/0x64/0xA4/0xE4/0x124/0x164/0x1A4/0x1E4  Port A-H Input Schmitt Trigger Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n]     |SMTENn    |Port A-H Pin[n] Input Schmitt Trigger Enable Bit
     * |        |          |0 = Px.n input Schmitt trigger function Disabled.
     * |        |          |1 = Px.n input Schmitt trigger function Enabled.
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::SLEWCTL
     * Offset: 0x28/0x68/0xA8/0xE8/0x128/0x168/0x1A8/0x1E8  Port A-H High Slew Rate Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2n+1:2n]|HSRENn    |Port A-H Pin[n] High Slew Rate Control
     * |        |          |00 = Px.n output with normal slew rate mode (maximum 40 MHz at 2.7V).
     * |        |          |01 = Px.n output with high slew rate mode (maximum 80 MHz at 2.7V).
     * |        |          |10 = Px.n output with fast slew rate mode (maximum 100 MHz at 2.7V.
     * |        |          |11 = Reserved.
     * |        |          |Note:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     * @var GPIO_T::PUSEL
     * Offset: 0x30/0x70/0xB0/0xF0/0x130/0x170/0x1B0/0x1F0  Port A-H Pull-up and Pull-down Selection Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2n+1:2n]|PUSELn    |Port A-H Pin[n] Pull-up and Pull-down Enable Register
     * |        |          |Determine each I/O Pull-up/pull-down of Px.n pins.
     * |        |          |00 = Px.n pull-up and pull-up disable.
     * |        |          |01 = Px.n pull-up enable.
     * |        |          |10 = Px.n pull-down enable.
     * |        |          |11 = Px.n pull-up and pull-up disable.
     * |        |          |Note1:
     * |        |          |Basically, the pull-up control and pull-down control has following behavior limitation
     * |        |          |The independent pull-up control register only valid when MODEn set as tri-state and open-drain mode
     * |        |          |The independent pull-down control register only valid when MODEn set as tri-state mode
     * |        |          |When both pull-up pull-down is set as 1 at tri-state mode, keep I/O in tri-state mode
     * |        |          |Note2:
     * |        |          |Max. n=15 for port A/B/E/G.
     * |        |          |Max. n=14 for port C/D.
     * |        |          |Max. n=11 for port F/H.
     */

    __IO uint32_t MODE;          /* Offset: 0x00/0x40/0x80/0xC0/0x100/0x140/0x180/0x1C0  Port A-H I/O Mode Control                       */
    __IO uint32_t DINOFF;        /* Offset: 0x04/0x44/0x84/0xC4/0x104/0x144/0x184/0x1C4  Port A-H Digital Input Path Disable Control     */
    __IO uint32_t DOUT;          /* Offset: 0x08/0x48/0x88/0xC8/0x108/0x148/0x188/0x1C8  Port A-H Data Output Value                      */
    __IO uint32_t DATMSK;        /* Offset: 0x0C/0x4C/0x8C/0xCC/0x10C/0x14C/0x18C/0x1CC  Port A-H Data Output Write Mask                 */
    __I  uint32_t PIN;           /* Offset: 0x10/0x50/0x90/0xD0/0x110/0x150/0x190/0x1D0  Port A-H Pin Value                              */
    __IO uint32_t DBEN;          /* Offset: 0x14/0x54/0x94/0xD4/0x114/0x154/0x194/0x1D4  Port A-H De-Bounce Enable Control Register      */
    __IO uint32_t INTTYPE;       /* Offset: 0x18/0x58/0x98/0xD8/0x118/0x158/0x198/0x1D8  Port A-H Interrupt Trigger Type Control         */
    __IO uint32_t INTEN;         /* Offset: 0x1C/0x5C/0x9C/0xDC/0x11C/0x15C/0x19C/0x1DC  Port A-H Interrupt Enable Control Register      */
    __IO uint32_t INTSRC;        /* Offset: 0x20/0x60/0xA0/0xE0/0x120/0x160/0x1A0/0x1E0  Port A-H Interrupt Source Flag                  */
    __IO uint32_t SMTEN;         /* Offset: 0x24/0x64/0xA4/0xE4/0x124/0x164/0x1A4/0x1E4  Port A-H Input Schmitt Trigger Enable Register  */
    __IO uint32_t SLEWCTL;       /* Offset: 0x28/0x68/0xA8/0xE8/0x128/0x168/0x1A8/0x1E8  Port A-H High Slew Rate Control Register        */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t PUSEL;         /* Offset: 0x30/0x70/0xB0/0xF0/0x130/0x170/0x1B0/0x1F0  Port A-H Pull-up and Pull-down Enable Register  */

} GPIO_T;

typedef struct
{

    /**
     * @var GPIO_DBCTL_T::DBCTL
     * Offset: 0x440  Interrupt De-bounce Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DBCLKSEL  |De-Bounce Sampling Cycle Selection
     * |        |          |0000 = Sample interrupt input once per 1 clocks.
     * |        |          |0001 = Sample interrupt input once per 2 clocks.
     * |        |          |0010 = Sample interrupt input once per 4 clocks.
     * |        |          |0011 = Sample interrupt input once per 8 clocks.
     * |        |          |0100 = Sample interrupt input once per 16 clocks.
     * |        |          |0101 = Sample interrupt input once per 32 clocks.
     * |        |          |0110 = Sample interrupt input once per 64 clocks.
     * |        |          |0111 = Sample interrupt input once per 128 clocks.
     * |        |          |1000 = Sample interrupt input once per 256 clocks.
     * |        |          |1001 = Sample interrupt input once per 2*256 clocks.
     * |        |          |1010 = Sample interrupt input once per 4*256 clocks.
     * |        |          |1011 = Sample interrupt input once per 8*256 clocks.
     * |        |          |1100 = Sample interrupt input once per 16*256 clocks.
     * |        |          |1101 = Sample interrupt input once per 32*256 clocks.
     * |        |          |1110 = Sample interrupt input once per 64*256 clocks.
     * |        |          |1111 = Sample interrupt input once per 128*256 clocks.
     * |[4]     |DBCLKSRC  |De-Bounce Counter Clock Source Selection
     * |        |          |0 = De-bounce counter clock source is the HCLK.
     * |        |          |1 = De-bounce counter clock source is the 10 kHz internal low speed RC oscillator (LIRC).
     * |[5]     |ICLKON    |Interrupt Clock On Mode
     * |        |          |0 = Edge detection circuit is active only if I/O pin corresponding RHIEN (Px_INTEN[n+16])/FLIEN (Px_INTEN[n]) bit is set to 1.
     * |        |          |1 = All I/O pins edge detection circuit is always active after reset.
     * |        |          |Note: It is recommended to disable this bit to save system power if no special application concern.
     */

    __IO uint32_t DBCTL;         /* Offset: 0x440  Interrupt De-bounce Control Register                              */

} GPIO_DBCTL_T;

/**
    @addtogroup GPIO_CONST GPIO Bit Field Definition
    Constant Definitions for GPIO Controller
@{ */

#define GPIO_DBCTL_DBCLKSEL_Pos          (0)                                               /*!< GPIO_T::DBCTL: DBCLKSEL Position          */
#define GPIO_DBCTL_DBCLKSEL_Msk          (0xFul << GPIO_DBCTL_DBCLKSEL_Pos)                /*!< GPIO_T::DBCTL: DBCLKSEL Mask              */

#define GPIO_DBCTL_DBCLKSRC_Pos          (4)                                               /*!< GPIO_T::DBCTL: DBCLKSRC Position          */
#define GPIO_DBCTL_DBCLKSRC_Msk          (1ul << GPIO_DBCTL_DBCLKSRC_Pos)                  /*!< GPIO_T::DBCTL: DBCLKSRC Mask              */

#define GPIO_DBCTL_ICLKON_Pos            (5)                                               /*!< GPIO_T::DBCTL: ICLKON Position            */
#define GPIO_DBCTL_ICLKON_Msk            (1ul << GPIO_DBCTL_ICLKON_Pos)                    /*!< GPIO_T::DBCTL: ICLKON Mask                */

/**@}*/ /* GPIO_CONST */
/**@}*/ /* end of GPIO register group */
/**@}*/ /* end of REGISTER group */

/** @addtogroup PERIPHERAL_DECLARATION Peripheral Pointer
  The Declaration of Peripherals
  @{
 */

#define GPIO_DBCTL_BASE       (0xB0004440ul)
#define PA                    ((GPIO_T *)  PA_BA)
#define PB                    ((GPIO_T *)  PB_BA)
#define PC                    ((GPIO_T *)  PC_BA)
#define PD                    ((GPIO_T *)  PD_BA)
#define PE                    ((GPIO_T *)  PE_BA)
#define PF                    ((GPIO_T *)  PF_BA)
#define PG                    ((GPIO_T *)  PG_BA)
#define GPIOA                 ((GPIO_T *)  PA_BA)
#define GPIOB                 ((GPIO_T *)  PB_BA)
#define GPIOC                 ((GPIO_T *)  PC_BA)
#define GPIOD                 ((GPIO_T *)  PD_BA)
#define GPIOE                 ((GPIO_T *)  PE_BA)
#define GPIOF                 ((GPIO_T *)  PF_BA)
#define GPIOG                 ((GPIO_T *)  PG_BA)
#define GPIO                  ((GPIO_DBCTL_T *) GPIO_DBCTL_BASE)
#define GPIO_PIN_DATA_BASE    (0xB0004800ul)
/*@}*/ /* end of group ERIPHERAL_DECLARATION */




/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup GPIO_EXPORTED_CONSTANTS GPIO Exported Constants
  @{
*/


#define GPIO_PIN_MAX            16UL /*!< Specify Maximum Pins of Each GPIO Port \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO_MODE Constant Definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_MODE_INPUT          0x0UL /*!< Input Mode \hideinitializer */
#define GPIO_MODE_OUTPUT         0x1UL /*!< Output Mode \hideinitializer */
#define GPIO_MODE_OPEN_DRAIN     0x2UL /*!< Open-Drain Mode \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO Interrupt Type Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_INT_RISING         0x00010000UL /*!< Interrupt enable by Input Rising Edge \hideinitializer */
#define GPIO_INT_FALLING        0x00000001UL /*!< Interrupt enable by Input Falling Edge \hideinitializer */
#define GPIO_INT_BOTH_EDGE      0x00010001UL /*!< Interrupt enable by both Rising Edge and Falling Edge \hideinitializer */
#define GPIO_INT_HIGH           0x01010000UL /*!< Interrupt enable by Level-High \hideinitializer */
#define GPIO_INT_LOW            0x01000001UL /*!< Interrupt enable by Level-Level \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO_INTTYPE Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_INTTYPE_EDGE           0UL /*!< GPIO_INTTYPE Setting for Edge Trigger Mode \hideinitializer */
#define GPIO_INTTYPE_LEVEL          1UL /*!< GPIO_INTTYPE Setting for Edge Level Mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO Slew Rate Type Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_SLEWCTL_NORMAL         0x0UL           /*!< GPIO slew setting for nornal Mode \hideinitializer */
#define GPIO_SLEWCTL_HIGH           0x1UL           /*!< GPIO slew setting for high Mode \hideinitializer */
#define GPIO_SLEWCTL_FAST           0x2UL           /*!< GPIO slew setting for fast Mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO Pull-up And Pull-down Type Constant Definitions                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_PUSEL_DISABLE          0x0UL           /*!< GPIO PUSEL setting for Disable Mode \hideinitializer */
#define GPIO_PUSEL_PULL_UP          0x1UL           /*!< GPIO PUSEL setting for Pull-up Mode \hideinitializer */
#define GPIO_PUSEL_PULL_DOWN        0x2UL           /*!< GPIO PUSEL setting for Pull-down Mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO External interrupt Constant Definitions                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_MFP_PA0MFP_EINT0   outpw(REG_SYS_GPA_MFPL, ((inpw(REG_SYS_GPA_MFPL) & 0xFFFFFFF0) | 0x00000005)) /*!< PA0 MFP setting for EINT0  \hideinitializer */
#define GPIO_MFP_PA13MFP_EINT0  outpw(REG_SYS_GPA_MFPH, ((inpw(REG_SYS_GPA_MFPH) & 0xFF0FFFFF) | 0x00D00000)) /*!< PA13 MFP setting for EINT0  \hideinitializer */
#define GPIO_MFP_PA1MFP_EINT1   outpw(REG_SYS_GPA_MFPL, ((inpw(REG_SYS_GPA_MFPL) & 0xFFFFFF0F) | 0x000000D0)) /*!< PA1 MFP setting for EINT1  \hideinitializer */
#define GPIO_MFP_PA14MFP_EINT1  outpw(REG_SYS_GPA_MFPH, ((inpw(REG_SYS_GPA_MFPH) & 0xF0FFFFFF) | 0x08000000)) /*!< PA14 MFP setting for EINT1  \hideinitializer */
#define GPIO_MFP_PD0MFP_EINT2   outpw(REG_SYS_GPD_MFPL, ((inpw(REG_SYS_GPD_MFPL) & 0xFFFFFFF0) | 0x00000004)) /*!< PD0 MFP setting for EINT2  \hideinitializer */
#define GPIO_MFP_PE10MFP_EINT2  outpw(REG_SYS_GPE_MFPH, ((inpw(REG_SYS_GPE_MFPH) & 0xFFFFF0FF) | 0x00000500)) /*!< PE10 MFP setting for EINT2  \hideinitializer */
#define GPIO_MFP_PB3MFP_EINT2   outpw(REG_SYS_GPB_MFPL, ((inpw(REG_SYS_GPB_MFPL) & 0xFFFF0FFF) | 0x00003000)) /*!< PB3 MFP setting for EINT2  \hideinitializer */
#define GPIO_MFP_PB13MFP_EINT2  outpw(REG_SYS_GPB_MFPH, ((inpw(REG_SYS_GPB_MFPH) & 0xFF0FFFFF) | 0x00200000)) /*!< PB13 MFP setting for EINT2  \hideinitializer */
#define GPIO_MFP_PD1MFP_EINT3   outpw(REG_SYS_GPD_MFPL, ((inpw(REG_SYS_GPD_MFPL) & 0xFFFFFF0F) | 0x00000040)) /*!< PD1 MFP setting for EINT3  \hideinitializer */
#define GPIO_MFP_PE12MFP_EINT3  outpw(REG_SYS_GPE_MFPH, ((inpw(REG_SYS_GPE_MFPH) & 0xFFF0FFFF) | 0x00050000)) /*!< PE12 MFP setting for EINT3  \hideinitializer */
#define GPIO_MFP_PG15MFP_EINT3  outpw(REG_SYS_GPG_MFPH, ((inpw(REG_SYS_GPG_MFPH) & 0x0FFFFFFF) | 0x40000000)) /*!< PG15 MFP setting for EINT3  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO_DBCTL Constant Definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_DBCTL_ICLK_ON            0x00000020UL /*!< GPIO_DBCTL setting for all IO pins edge detection circuit is always active after reset \hideinitializer */
#define GPIO_DBCTL_ICLK_OFF           0x00000000UL /*!< GPIO_DBCTL setting for edge detection circuit is active only if IO pin corresponding GPIOx_IEN bit is set to 1 \hideinitializer */

#define GPIO_DBCTL_DBCLKSRC_LIRC      0x00000010UL /*!< GPIO_DBCTL setting for de-bounce counter clock source is the internal 10 kHz \hideinitializer */
#define GPIO_DBCTL_DBCLKSRC_HCLK      0x00000000UL /*!< GPIO_DBCTL setting for de-bounce counter clock source is the HCLK \hideinitializer */

#define GPIO_DBCTL_DBCLKSEL_1         0x00000000UL /*!< GPIO_DBCTL setting for sampling cycle = 1 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_2         0x00000001UL /*!< GPIO_DBCTL setting for sampling cycle = 2 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_4         0x00000002UL /*!< GPIO_DBCTL setting for sampling cycle = 4 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_8         0x00000003UL /*!< GPIO_DBCTL setting for sampling cycle = 8 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_16        0x00000004UL /*!< GPIO_DBCTL setting for sampling cycle = 16 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_32        0x00000005UL /*!< GPIO_DBCTL setting for sampling cycle = 32 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_64        0x00000006UL /*!< GPIO_DBCTL setting for sampling cycle = 64 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_128       0x00000007UL /*!< GPIO_DBCTL setting for sampling cycle = 128 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_256       0x00000008UL /*!< GPIO_DBCTL setting for sampling cycle = 256 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_512       0x00000009UL /*!< GPIO_DBCTL setting for sampling cycle = 512 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_1024      0x0000000AUL /*!< GPIO_DBCTL setting for sampling cycle = 1024 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_2048      0x0000000BUL /*!< GPIO_DBCTL setting for sampling cycle = 2048 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_4096      0x0000000CUL /*!< GPIO_DBCTL setting for sampling cycle = 4096 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_8192      0x0000000DUL /*!< GPIO_DBCTL setting for sampling cycle = 8192 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_16384     0x0000000EUL /*!< GPIO_DBCTL setting for sampling cycle = 16384 clocks \hideinitializer */
#define GPIO_DBCTL_DBCLKSEL_32768     0x0000000FUL /*!< GPIO_DBCTL setting for sampling cycle = 32768 clocks \hideinitializer */


/* Define GPIO Pin Data Input/Output. It could be used to control each I/O pin by pin address mapping.
   Example 1:

       PA0 = 1;

   It is used to set GPIO PA.0 to high;

   Example 2:

       if (PA0)
           PA0 = 0;

   If GPIO PA.0 pin status is high, then set GPIO PA.0 data output to low.
 */
#define GPIO_PIN_DATA(port, pin)    (*((volatile uint32_t *)((GPIO_PIN_DATA_BASE+(0x40*(port))) + ((pin)<<2)))) /*!< Pin Data Input/Output \hideinitializer */
#define PA0             GPIO_PIN_DATA(0, 0 ) /*!< Specify PA.0 Pin Data Input/Output \hideinitializer */
#define PA1             GPIO_PIN_DATA(0, 1 ) /*!< Specify PA.1 Pin Data Input/Output \hideinitializer */
#define PA2             GPIO_PIN_DATA(0, 2 ) /*!< Specify PA.2 Pin Data Input/Output \hideinitializer */
#define PA3             GPIO_PIN_DATA(0, 3 ) /*!< Specify PA.3 Pin Data Input/Output \hideinitializer */
#define PA4             GPIO_PIN_DATA(0, 4 ) /*!< Specify PA.4 Pin Data Input/Output \hideinitializer */
#define PA5             GPIO_PIN_DATA(0, 5 ) /*!< Specify PA.5 Pin Data Input/Output \hideinitializer */
#define PA6             GPIO_PIN_DATA(0, 6 ) /*!< Specify PA.6 Pin Data Input/Output \hideinitializer */
#define PA7             GPIO_PIN_DATA(0, 7 ) /*!< Specify PA.7 Pin Data Input/Output \hideinitializer */
#define PA8             GPIO_PIN_DATA(0, 8 ) /*!< Specify PA.8 Pin Data Input/Output \hideinitializer */
#define PA9             GPIO_PIN_DATA(0, 9 ) /*!< Specify PA.9 Pin Data Input/Output \hideinitializer */
#define PA10            GPIO_PIN_DATA(0, 10) /*!< Specify PA.10 Pin Data Input/Output \hideinitializer */
#define PA11            GPIO_PIN_DATA(0, 11) /*!< Specify PA.11 Pin Data Input/Output \hideinitializer */
#define PA12            GPIO_PIN_DATA(0, 12) /*!< Specify PA.12 Pin Data Input/Output \hideinitializer */
#define PA13            GPIO_PIN_DATA(0, 13) /*!< Specify PA.13 Pin Data Input/Output \hideinitializer */
#define PA14            GPIO_PIN_DATA(0, 14) /*!< Specify PA.14 Pin Data Input/Output \hideinitializer */
#define PA15            GPIO_PIN_DATA(0, 15) /*!< Specify PA.15 Pin Data Input/Output \hideinitializer */
#define PB0             GPIO_PIN_DATA(1, 0 ) /*!< Specify PB.0 Pin Data Input/Output \hideinitializer */
#define PB1             GPIO_PIN_DATA(1, 1 ) /*!< Specify PB.1 Pin Data Input/Output \hideinitializer */
#define PB2             GPIO_PIN_DATA(1, 2 ) /*!< Specify PB.2 Pin Data Input/Output \hideinitializer */
#define PB3             GPIO_PIN_DATA(1, 3 ) /*!< Specify PB.3 Pin Data Input/Output \hideinitializer */
#define PB4             GPIO_PIN_DATA(1, 4 ) /*!< Specify PB.4 Pin Data Input/Output \hideinitializer */
#define PB5             GPIO_PIN_DATA(1, 5 ) /*!< Specify PB.5 Pin Data Input/Output \hideinitializer */
#define PB6             GPIO_PIN_DATA(1, 6 ) /*!< Specify PB.6 Pin Data Input/Output \hideinitializer */
#define PB7             GPIO_PIN_DATA(1, 7 ) /*!< Specify PB.7 Pin Data Input/Output \hideinitializer */
#define PB8             GPIO_PIN_DATA(1, 8 ) /*!< Specify PB.8 Pin Data Input/Output \hideinitializer */
#define PB9             GPIO_PIN_DATA(1, 9 ) /*!< Specify PB.9 Pin Data Input/Output \hideinitializer */
#define PB10            GPIO_PIN_DATA(1, 10) /*!< Specify PB.10 Pin Data Input/Output \hideinitializer */
#define PB11            GPIO_PIN_DATA(1, 11) /*!< Specify PB.11 Pin Data Input/Output \hideinitializer */
#define PB12            GPIO_PIN_DATA(1, 12) /*!< Specify PB.12 Pin Data Input/Output \hideinitializer */
#define PB13            GPIO_PIN_DATA(1, 13) /*!< Specify PB.13 Pin Data Input/Output \hideinitializer */
#define PB14            GPIO_PIN_DATA(1, 14) /*!< Specify PB.14 Pin Data Input/Output \hideinitializer */
#define PB15            GPIO_PIN_DATA(1, 15) /*!< Specify PB.15 Pin Data Input/Output \hideinitializer */
#define PC0             GPIO_PIN_DATA(2, 0 ) /*!< Specify PC.0 Pin Data Input/Output \hideinitializer */
#define PC1             GPIO_PIN_DATA(2, 1 ) /*!< Specify PC.1 Pin Data Input/Output \hideinitializer */
#define PC2             GPIO_PIN_DATA(2, 2 ) /*!< Specify PC.2 Pin Data Input/Output \hideinitializer */
#define PC3             GPIO_PIN_DATA(2, 3 ) /*!< Specify PC.3 Pin Data Input/Output \hideinitializer */
#define PC4             GPIO_PIN_DATA(2, 4 ) /*!< Specify PC.4 Pin Data Input/Output \hideinitializer */
#define PC5             GPIO_PIN_DATA(2, 5 ) /*!< Specify PC.5 Pin Data Input/Output \hideinitializer */
#define PC6             GPIO_PIN_DATA(2, 6 ) /*!< Specify PC.6 Pin Data Input/Output \hideinitializer */
#define PC7             GPIO_PIN_DATA(2, 7 ) /*!< Specify PC.7 Pin Data Input/Output \hideinitializer */
#define PC8             GPIO_PIN_DATA(2, 8 ) /*!< Specify PC.8 Pin Data Input/Output \hideinitializer */
#define PC9             GPIO_PIN_DATA(2, 9 ) /*!< Specify PC.9 Pin Data Input/Output \hideinitializer */
#define PC10            GPIO_PIN_DATA(2, 10) /*!< Specify PC.10 Pin Data Input/Output \hideinitializer */
#define PC11            GPIO_PIN_DATA(2, 11) /*!< Specify PC.11 Pin Data Input/Output \hideinitializer */
#define PC12            GPIO_PIN_DATA(2, 12) /*!< Specify PC.12 Pin Data Input/Output \hideinitializer */
#define PC13            GPIO_PIN_DATA(2, 13) /*!< Specify PC.13 Pin Data Input/Output \hideinitializer */
#define PC14            GPIO_PIN_DATA(2, 14) /*!< Specify PC.14 Pin Data Input/Output \hideinitializer */
#define PC15            GPIO_PIN_DATA(2, 15) /*!< Specify PC.15 Pin Data Input/Output \hideinitializer */
#define PD0             GPIO_PIN_DATA(3, 0 ) /*!< Specify PD.0 Pin Data Input/Output \hideinitializer */
#define PD1             GPIO_PIN_DATA(3, 1 ) /*!< Specify PD.1 Pin Data Input/Output \hideinitializer */
#define PD2             GPIO_PIN_DATA(3, 2 ) /*!< Specify PD.2 Pin Data Input/Output \hideinitializer */
#define PD3             GPIO_PIN_DATA(3, 3 ) /*!< Specify PD.3 Pin Data Input/Output \hideinitializer */
#define PD4             GPIO_PIN_DATA(3, 4 ) /*!< Specify PD.4 Pin Data Input/Output \hideinitializer */
#define PD5             GPIO_PIN_DATA(3, 5 ) /*!< Specify PD.5 Pin Data Input/Output \hideinitializer */
#define PD6             GPIO_PIN_DATA(3, 6 ) /*!< Specify PD.6 Pin Data Input/Output \hideinitializer */
#define PD7             GPIO_PIN_DATA(3, 7 ) /*!< Specify PD.7 Pin Data Input/Output \hideinitializer */
#define PD8             GPIO_PIN_DATA(3, 8 ) /*!< Specify PD.8 Pin Data Input/Output \hideinitializer */
#define PD9             GPIO_PIN_DATA(3, 9 ) /*!< Specify PD.9 Pin Data Input/Output \hideinitializer */
#define PD10            GPIO_PIN_DATA(3, 10) /*!< Specify PD.10 Pin Data Input/Output \hideinitializer */
#define PD11            GPIO_PIN_DATA(3, 11) /*!< Specify PD.11 Pin Data Input/Output \hideinitializer */
#define PD12            GPIO_PIN_DATA(3, 12) /*!< Specify PD.12 Pin Data Input/Output \hideinitializer */
#define PD13            GPIO_PIN_DATA(3, 13) /*!< Specify PD.13 Pin Data Input/Output \hideinitializer */
#define PD14            GPIO_PIN_DATA(3, 14) /*!< Specify PD.14 Pin Data Input/Output \hideinitializer */
#define PE0             GPIO_PIN_DATA(4, 0 ) /*!< Specify PE.0 Pin Data Input/Output \hideinitializer */
#define PE1             GPIO_PIN_DATA(4, 1 ) /*!< Specify PE.1 Pin Data Input/Output \hideinitializer */
#define PE2             GPIO_PIN_DATA(4, 2 ) /*!< Specify PE.2 Pin Data Input/Output \hideinitializer */
#define PE3             GPIO_PIN_DATA(4, 3 ) /*!< Specify PE.3 Pin Data Input/Output \hideinitializer */
#define PE4             GPIO_PIN_DATA(4, 4 ) /*!< Specify PE.4 Pin Data Input/Output \hideinitializer */
#define PE5             GPIO_PIN_DATA(4, 5 ) /*!< Specify PE.5 Pin Data Input/Output \hideinitializer */
#define PE6             GPIO_PIN_DATA(4, 6 ) /*!< Specify PE.6 Pin Data Input/Output \hideinitializer */
#define PE7             GPIO_PIN_DATA(4, 7 ) /*!< Specify PE.7 Pin Data Input/Output \hideinitializer */
#define PE8             GPIO_PIN_DATA(4, 8 ) /*!< Specify PE.8 Pin Data Input/Output \hideinitializer */
#define PE9             GPIO_PIN_DATA(4, 9 ) /*!< Specify PE.9 Pin Data Input/Output \hideinitializer */
#define PE10            GPIO_PIN_DATA(4, 10) /*!< Specify PE.10 Pin Data Input/Output \hideinitializer */
#define PE11            GPIO_PIN_DATA(4, 11) /*!< Specify PE.11 Pin Data Input/Output \hideinitializer */
#define PE12            GPIO_PIN_DATA(4, 12) /*!< Specify PE.12 Pin Data Input/Output \hideinitializer */
#define PE13            GPIO_PIN_DATA(4, 13) /*!< Specify PE.13 Pin Data Input/Output \hideinitializer */
#define PE14            GPIO_PIN_DATA(4, 14) /*!< Specify PE.14 Pin Data Input/Output \hideinitializer */
#define PE15            GPIO_PIN_DATA(4, 15) /*!< Specify PE.15 Pin Data Input/Output \hideinitializer */
#define PF0             GPIO_PIN_DATA(5, 0 ) /*!< Specify PF.0 Pin Data Input/Output \hideinitializer */
#define PF1             GPIO_PIN_DATA(5, 1 ) /*!< Specify PF.1 Pin Data Input/Output \hideinitializer */
#define PF2             GPIO_PIN_DATA(5, 2 ) /*!< Specify PF.2 Pin Data Input/Output \hideinitializer */
#define PF3             GPIO_PIN_DATA(5, 3 ) /*!< Specify PF.3 Pin Data Input/Output \hideinitializer */
#define PF4             GPIO_PIN_DATA(5, 4 ) /*!< Specify PF.4 Pin Data Input/Output \hideinitializer */
#define PF5             GPIO_PIN_DATA(5, 5 ) /*!< Specify PF.5 Pin Data Input/Output \hideinitializer */
#define PF6             GPIO_PIN_DATA(5, 6 ) /*!< Specify PF.6 Pin Data Input/Output \hideinitializer */
#define PF7             GPIO_PIN_DATA(5, 7 ) /*!< Specify PF.7 Pin Data Input/Output \hideinitializer */
#define PF8             GPIO_PIN_DATA(5, 8 ) /*!< Specify PF.8 Pin Data Input/Output \hideinitializer */
#define PF9             GPIO_PIN_DATA(5, 9 ) /*!< Specify PF.9 Pin Data Input/Output \hideinitializer */
#define PF10            GPIO_PIN_DATA(5, 10) /*!< Specify PF.10 Pin Data Input/Output \hideinitializer */
#define PF11            GPIO_PIN_DATA(5, 11) /*!< Specify PF.11 Pin Data Input/Output \hideinitializer */
#define PG0             GPIO_PIN_DATA(6, 0 ) /*!< Specify PG.0 Pin Data Input/Output \hideinitializer */
#define PG1             GPIO_PIN_DATA(6, 1 ) /*!< Specify PG.1 Pin Data Input/Output \hideinitializer */
#define PG2             GPIO_PIN_DATA(6, 2 ) /*!< Specify PG.2 Pin Data Input/Output \hideinitializer */
#define PG3             GPIO_PIN_DATA(6, 3 ) /*!< Specify PG.3 Pin Data Input/Output \hideinitializer */
#define PG4             GPIO_PIN_DATA(6, 4 ) /*!< Specify PG.4 Pin Data Input/Output \hideinitializer */
#define PG5             GPIO_PIN_DATA(6, 5 ) /*!< Specify PG.5 Pin Data Input/Output \hideinitializer */
#define PG6             GPIO_PIN_DATA(6, 6 ) /*!< Specify PG.6 Pin Data Input/Output \hideinitializer */
#define PG7             GPIO_PIN_DATA(6, 7 ) /*!< Specify PG.7 Pin Data Input/Output \hideinitializer */
#define PG8             GPIO_PIN_DATA(6, 8 ) /*!< Specify PG.8 Pin Data Input/Output \hideinitializer */
#define PG9             GPIO_PIN_DATA(6, 9 ) /*!< Specify PG.9 Pin Data Input/Output \hideinitializer */
#define PG10            GPIO_PIN_DATA(6, 10) /*!< Specify PG.10 Pin Data Input/Output \hideinitializer */
#define PG11            GPIO_PIN_DATA(6, 11) /*!< Specify PG.11 Pin Data Input/Output \hideinitializer */
#define PG12            GPIO_PIN_DATA(6, 12) /*!< Specify PG.12 Pin Data Input/Output \hideinitializer */
#define PG13            GPIO_PIN_DATA(6, 13) /*!< Specify PG.13 Pin Data Input/Output \hideinitializer */
#define PG14            GPIO_PIN_DATA(6, 14) /*!< Specify PG.14 Pin Data Input/Output \hideinitializer */
#define PG15            GPIO_PIN_DATA(6, 15) /*!< Specify PG.15 Pin Data Input/Output \hideinitializer */
#define PH0             GPIO_PIN_DATA(7, 0 ) /*!< Specify PH.0 Pin Data Input/Output \hideinitializer */
#define PH1             GPIO_PIN_DATA(7, 1 ) /*!< Specify PH.1 Pin Data Input/Output \hideinitializer */
#define PH2             GPIO_PIN_DATA(7, 2 ) /*!< Specify PH.2 Pin Data Input/Output \hideinitializer */
#define PH3             GPIO_PIN_DATA(7, 3 ) /*!< Specify PH.3 Pin Data Input/Output \hideinitializer */
#define PH4             GPIO_PIN_DATA(7, 4 ) /*!< Specify PH.4 Pin Data Input/Output \hideinitializer */
#define PH5             GPIO_PIN_DATA(7, 5 ) /*!< Specify PH.5 Pin Data Input/Output \hideinitializer */
#define PH6             GPIO_PIN_DATA(7, 6 ) /*!< Specify PH.6 Pin Data Input/Output \hideinitializer */
#define PH7             GPIO_PIN_DATA(7, 7 ) /*!< Specify PH.7 Pin Data Input/Output \hideinitializer */
#define PH8             GPIO_PIN_DATA(7, 8 ) /*!< Specify PH.8 Pin Data Input/Output \hideinitializer */
#define PH9             GPIO_PIN_DATA(7, 9 ) /*!< Specify PH.9 Pin Data Input/Output \hideinitializer */
#define PH10            GPIO_PIN_DATA(7, 10) /*!< Specify PH.10 Pin Data Input/Output \hideinitializer */
#define PH11            GPIO_PIN_DATA(7, 11) /*!< Specify PH.11 Pin Data Input/Output \hideinitializer */


/*@}*/ /* end of group GPIO_EXPORTED_CONSTANTS */


/** @addtogroup GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Clear GPIO Pin Interrupt Flag
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD, PF and PH GPIO port.
 *                          It could be BIT0 ~ BIT13 for PE GPIO port.
 *                          It could be BIT0 ~ BIT11 for PG GPIO port.
 *
 * @return      None
 *
 * @details     Clear the interrupt status of specified GPIO pin.
 * \hideinitializer
 */
#define GPIO_CLR_INT_FLAG(port, u32PinMask)         ((port)->INTSRC = (u32PinMask))

/**
 * @brief       Disable Pin De-bounce Function
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD, PF and PH GPIO port.
 *                          It could be BIT0 ~ BIT13 for PE GPIO port.
 *                          It could be BIT0 ~ BIT11 for PG GPIO port.
 *
 * @return      None
 *
 * @details     Disable the interrupt de-bounce function of specified GPIO pin.
 * \hideinitializer
 */
#define GPIO_DISABLE_DEBOUNCE(port, u32PinMask)     ((port)->DBEN &= ~(u32PinMask))

/**
 * @brief       Enable Pin De-bounce Function
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD, PF and PH GPIO port.
 *                          It could be BIT0 ~ BIT13 for PE GPIO port.
 *                          It could be BIT0 ~ BIT11 for PG GPIO port.
 * @return      None
 *
 * @details     Enable the interrupt de-bounce function of specified GPIO pin.
 * \hideinitializer
 */
#define GPIO_ENABLE_DEBOUNCE(port, u32PinMask)      ((port)->DBEN |= (u32PinMask))

/**
 * @brief       Disable I/O Digital Input Path
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD, PF and PH GPIO port.
 *                          It could be BIT0 ~ BIT13 for PE GPIO port.
 *                          It could be BIT0 ~ BIT11 for PG GPIO port.
 *
 * @return      None
 *
 * @details     Disable I/O digital input path of specified GPIO pin.
 * \hideinitializer
 */
#define GPIO_DISABLE_DIGITAL_PATH(port, u32PinMask) ((port)->DINOFF |= ((u32PinMask)<<16))

/**
 * @brief       Enable I/O Digital Input Path
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD, PF and PH GPIO port.
 *                          It could be BIT0 ~ BIT13 for PE GPIO port.
 *                          It could be BIT0 ~ BIT11 for PG GPIO port.
 *
 * @return      None
 *
 * @details     Enable I/O digital input path of specified GPIO pin.
 * \hideinitializer
 */
#define GPIO_ENABLE_DIGITAL_PATH(port, u32PinMask)  ((port)->DINOFF &= ~((u32PinMask)<<16))

/**
 * @brief       Disable I/O DOUT mask
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD, PF and PH GPIO port.
 *                          It could be BIT0 ~ BIT13 for PE GPIO port.
 *                          It could be BIT0 ~ BIT11 for PG GPIO port.
 *
 * @return      None
 *
 * @details     Disable I/O DOUT mask of specified GPIO pin.
 * \hideinitializer
 */
#define GPIO_DISABLE_DOUT_MASK(port, u32PinMask)    ((port)->DATMSK &= ~(u32PinMask))

/**
 * @brief       Enable I/O DOUT mask
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD, PF and PH GPIO port.
 *                          It could be BIT0 ~ BIT13 for PE GPIO port.
 *                          It could be BIT0 ~ BIT11 for PG GPIO port.
 *
 * @return      None
 *
 * @details     Enable I/O DOUT mask of specified GPIO pin.
 * \hideinitializer
 */
#define GPIO_ENABLE_DOUT_MASK(port, u32PinMask) ((port)->DATMSK |= (u32PinMask))

/**
 * @brief       Get GPIO Pin Interrupt Flag
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD, PF and PH GPIO port.
 *                          It could be BIT0 ~ BIT13 for PE GPIO port.
 *                          It could be BIT0 ~ BIT11 for PG GPIO port.
 *
 * @retval      0           No interrupt at specified GPIO pin
 * @retval      1           The specified GPIO pin generate an interrupt
 *
 * @details     Get the interrupt status of specified GPIO pin.
 * \hideinitializer
 */
#define GPIO_GET_INT_FLAG(port, u32PinMask)     ((port)->INTSRC & (u32PinMask))

/**
 * @brief       Set De-bounce Sampling Cycle Time
 *
 * @param[in]   u32ClkSrc   The de-bounce counter clock source. It could be GPIO_DBCTL_DBCLKSRC_HCLK or GPIO_DBCTL_DBCLKSRC_LIRC.
 * @param[in]   u32ClkSel   The de-bounce sampling cycle selection. It could be
 *                            - \ref GPIO_DBCTL_DBCLKSEL_1
 *                            - \ref GPIO_DBCTL_DBCLKSEL_2
 *                            - \ref GPIO_DBCTL_DBCLKSEL_4
 *                            - \ref GPIO_DBCTL_DBCLKSEL_8
 *                            - \ref GPIO_DBCTL_DBCLKSEL_16
 *                            - \ref GPIO_DBCTL_DBCLKSEL_32
 *                            - \ref GPIO_DBCTL_DBCLKSEL_64
 *                            - \ref GPIO_DBCTL_DBCLKSEL_128
 *                            - \ref GPIO_DBCTL_DBCLKSEL_256
 *                            - \ref GPIO_DBCTL_DBCLKSEL_512
 *                            - \ref GPIO_DBCTL_DBCLKSEL_1024
 *                            - \ref GPIO_DBCTL_DBCLKSEL_2048
 *                            - \ref GPIO_DBCTL_DBCLKSEL_4096
 *                            - \ref GPIO_DBCTL_DBCLKSEL_8192
 *                            - \ref GPIO_DBCTL_DBCLKSEL_16384
 *                            - \ref GPIO_DBCTL_DBCLKSEL_32768
 *
 * @return      None
 *
 * @details     Set the interrupt de-bounce sampling cycle time based on the debounce counter clock source. \n
 *              Example: _GPIO_SET_DEBOUNCE_TIME(GPIO_DBCTL_DBCLKSRC_LIRC, GPIO_DBCTL_DBCLKSEL_4). \n
 *              It's meaning the De-debounce counter clock source is internal 10 KHz and sampling cycle selection is 4. \n
 *              Then the target de-bounce sampling cycle time is (4)*(1/(10*1000)) s = 4*0.0001 s = 400 us,
 *              and system will sampling interrupt input once per 00 us.
 * \hideinitializer
 */
#define GPIO_SET_DEBOUNCE_TIME(u32ClkSrc, u32ClkSel)    (GPIO->DBCTL = (GPIO_DBCTL_ICLKON_Msk | (u32ClkSrc) | (u32ClkSel)))

/**
 * @brief       Get GPIO Port IN Data
 *
* @param[in]    port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 *
 * @return      The specified port data
 *
 * @details     Get the PIN register of specified GPIO port.
 * \hideinitializer
 */
#define GPIO_GET_IN_DATA(port)  ((port)->PIN)

/**
 * @brief       Set GPIO Port OUT Data
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32Data     GPIO port data.
 *
 * @return      None
 *
 * @details     Set the Data into specified GPIO port.
 * \hideinitializer
 */
#define GPIO_SET_OUT_DATA(port, u32Data)    ((port)->DOUT = (u32Data))

/**
 * @brief       Toggle Specified GPIO pin
 *
 * @param[in]   u32Pin      Pxy
 *
 * @return      None
 *
 * @details     Toggle the specified GPIO pint.
 * \hideinitializer
 */
#define GPIO_TOGGLE(u32Pin) ((u32Pin) ^= 1)


/**
 * @brief       Enable External GPIO interrupt
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32Pin      The pin of specified GPIO port.
 *                          It could be 0 ~ 15 for PA, PB, PC, PD, PF and PH GPIO port.
 *                          It could be 0 ~ 13 for PE GPIO port.
 *                          It could be 0 ~ 11 for PG GPIO port.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *                              GPIO_INT_RISING, GPIO_INT_FALLING, GPIO_INT_BOTH_EDGE, GPIO_INT_HIGH, GPIO_INT_LOW.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 * \hideinitializer
 */
#define GPIO_EnableEINT     GPIO_EnableInt

/**
 * @brief       Disable External GPIO interrupt
 *
 * @param[in]   port        GPIO port. It could be It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32Pin      The pin of specified GPIO port.
 *                          It could be 0 ~ 15 for PA, PB, PC, PD, PF and PH GPIO port.
 *                          It could be 0 ~ 13 for PE GPIO port.
 *                          It could be 0 ~ 11 for PG GPIO port.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 * \hideinitializer
 */
#define GPIO_DisableEINT    GPIO_DisableInt


void GPIO_SetMode(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode);
void GPIO_EnableInt(GPIO_T *port, uint32_t u32Pin, uint32_t u32IntAttribs);
void GPIO_DisableInt(GPIO_T *port, uint32_t u32Pin);
void GPIO_SetSlewCtl(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode);
void GPIO_SetPullCtl(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode);


/*@}*/ /* end of group GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group GPIO_Driver */

/*@}*/ /* end of group Standard_Driver */


#ifdef __cplusplus
}
#endif

#endif  /* __GPIO_H__ */
