/**************************************************************************//**
 * @file
 * @brief efm32g_dac Register and Bit Field definitions
 * @author Energy Micro AS
 * @version 3.0.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
/**************************************************************************//**
 * @defgroup EFM32G_DAC
 * @{
 * @brief EFM32G_DAC Register Declaration
 *****************************************************************************/
typedef struct
{
  __IO uint32_t CTRL;     /**< Control Register  */
  __I uint32_t  STATUS;   /**< Status Register  */
  __IO uint32_t CH0CTRL;  /**< Channel 0 Control Register  */
  __IO uint32_t CH1CTRL;  /**< Channel 1 Control Register  */
  __IO uint32_t IEN;      /**< Interrupt Enable Register  */
  __I uint32_t  IF;       /**< Interrupt Flag Register  */
  __IO uint32_t IFS;      /**< Interrupt Flag Set Register  */
  __IO uint32_t IFC;      /**< Interrupt Flag Clear Register  */
  __IO uint32_t CH0DATA;  /**< Channel 0 Data Register  */
  __IO uint32_t CH1DATA;  /**< Channel 1 Data Register  */
  __IO uint32_t COMBDATA; /**< Combined Data Register  */
  __IO uint32_t CAL;      /**< Calibration Register  */
  __IO uint32_t BIASPROG; /**< Bias Programming Register  */
} DAC_TypeDef;            /** @} */

/**************************************************************************//**
 * @defgroup EFM32G_DAC_BitFields
 * @{
 *****************************************************************************/

/* Bit fields for DAC CTRL */
#define _DAC_CTRL_RESETVALUE              0x00000010UL                         /**< Default value for DAC_CTRL */
#define _DAC_CTRL_MASK                    0x0037D3FFUL                         /**< Mask for DAC_CTRL */
#define DAC_CTRL_DIFF                     (0x1UL << 0)                         /**< Differential Mode */
#define _DAC_CTRL_DIFF_SHIFT              0                                    /**< Shift value for DAC_DIFF */
#define _DAC_CTRL_DIFF_MASK               0x1UL                                /**< Bit mask for DAC_DIFF */
#define _DAC_CTRL_DIFF_DEFAULT            0x00000000UL                         /**< Mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_DIFF_DEFAULT             (_DAC_CTRL_DIFF_DEFAULT << 0)        /**< Shifted mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_SINEMODE                 (0x1UL << 1)                         /**< Sine Mode */
#define _DAC_CTRL_SINEMODE_SHIFT          1                                    /**< Shift value for DAC_SINEMODE */
#define _DAC_CTRL_SINEMODE_MASK           0x2UL                                /**< Bit mask for DAC_SINEMODE */
#define _DAC_CTRL_SINEMODE_DEFAULT        0x00000000UL                         /**< Mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_SINEMODE_DEFAULT         (_DAC_CTRL_SINEMODE_DEFAULT << 1)    /**< Shifted mode DEFAULT for DAC_CTRL */
#define _DAC_CTRL_CONVMODE_SHIFT          2                                    /**< Shift value for DAC_CONVMODE */
#define _DAC_CTRL_CONVMODE_MASK           0xCUL                                /**< Bit mask for DAC_CONVMODE */
#define _DAC_CTRL_CONVMODE_DEFAULT        0x00000000UL                         /**< Mode DEFAULT for DAC_CTRL */
#define _DAC_CTRL_CONVMODE_CONTINUOUS     0x00000000UL                         /**< Mode CONTINUOUS for DAC_CTRL */
#define _DAC_CTRL_CONVMODE_SAMPLEHOLD     0x00000001UL                         /**< Mode SAMPLEHOLD for DAC_CTRL */
#define _DAC_CTRL_CONVMODE_SAMPLEOFF      0x00000002UL                         /**< Mode SAMPLEOFF for DAC_CTRL */
#define DAC_CTRL_CONVMODE_DEFAULT         (_DAC_CTRL_CONVMODE_DEFAULT << 2)    /**< Shifted mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_CONVMODE_CONTINUOUS      (_DAC_CTRL_CONVMODE_CONTINUOUS << 2) /**< Shifted mode CONTINUOUS for DAC_CTRL */
#define DAC_CTRL_CONVMODE_SAMPLEHOLD      (_DAC_CTRL_CONVMODE_SAMPLEHOLD << 2) /**< Shifted mode SAMPLEHOLD for DAC_CTRL */
#define DAC_CTRL_CONVMODE_SAMPLEOFF       (_DAC_CTRL_CONVMODE_SAMPLEOFF << 2)  /**< Shifted mode SAMPLEOFF for DAC_CTRL */
#define _DAC_CTRL_OUTMODE_SHIFT           4                                    /**< Shift value for DAC_OUTMODE */
#define _DAC_CTRL_OUTMODE_MASK            0x30UL                               /**< Bit mask for DAC_OUTMODE */
#define _DAC_CTRL_OUTMODE_DISABLE         0x00000000UL                         /**< Mode DISABLE for DAC_CTRL */
#define _DAC_CTRL_OUTMODE_DEFAULT         0x00000001UL                         /**< Mode DEFAULT for DAC_CTRL */
#define _DAC_CTRL_OUTMODE_PIN             0x00000001UL                         /**< Mode PIN for DAC_CTRL */
#define _DAC_CTRL_OUTMODE_ADC             0x00000002UL                         /**< Mode ADC for DAC_CTRL */
#define _DAC_CTRL_OUTMODE_PINADC          0x00000003UL                         /**< Mode PINADC for DAC_CTRL */
#define DAC_CTRL_OUTMODE_DISABLE          (_DAC_CTRL_OUTMODE_DISABLE << 4)     /**< Shifted mode DISABLE for DAC_CTRL */
#define DAC_CTRL_OUTMODE_DEFAULT          (_DAC_CTRL_OUTMODE_DEFAULT << 4)     /**< Shifted mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_OUTMODE_PIN              (_DAC_CTRL_OUTMODE_PIN << 4)         /**< Shifted mode PIN for DAC_CTRL */
#define DAC_CTRL_OUTMODE_ADC              (_DAC_CTRL_OUTMODE_ADC << 4)         /**< Shifted mode ADC for DAC_CTRL */
#define DAC_CTRL_OUTMODE_PINADC           (_DAC_CTRL_OUTMODE_PINADC << 4)      /**< Shifted mode PINADC for DAC_CTRL */
#define DAC_CTRL_OUTENPRS                 (0x1UL << 6)                         /**< PRS Controlled Output Enable */
#define _DAC_CTRL_OUTENPRS_SHIFT          6                                    /**< Shift value for DAC_OUTENPRS */
#define _DAC_CTRL_OUTENPRS_MASK           0x40UL                               /**< Bit mask for DAC_OUTENPRS */
#define _DAC_CTRL_OUTENPRS_DEFAULT        0x00000000UL                         /**< Mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_OUTENPRS_DEFAULT         (_DAC_CTRL_OUTENPRS_DEFAULT << 6)    /**< Shifted mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_CH0PRESCRST              (0x1UL << 7)                         /**< Channel 0 Start Reset Prescaler */
#define _DAC_CTRL_CH0PRESCRST_SHIFT       7                                    /**< Shift value for DAC_CH0PRESCRST */
#define _DAC_CTRL_CH0PRESCRST_MASK        0x80UL                               /**< Bit mask for DAC_CH0PRESCRST */
#define _DAC_CTRL_CH0PRESCRST_DEFAULT     0x00000000UL                         /**< Mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_CH0PRESCRST_DEFAULT      (_DAC_CTRL_CH0PRESCRST_DEFAULT << 7) /**< Shifted mode DEFAULT for DAC_CTRL */
#define _DAC_CTRL_REFSEL_SHIFT            8                                    /**< Shift value for DAC_REFSEL */
#define _DAC_CTRL_REFSEL_MASK             0x300UL                              /**< Bit mask for DAC_REFSEL */
#define _DAC_CTRL_REFSEL_DEFAULT          0x00000000UL                         /**< Mode DEFAULT for DAC_CTRL */
#define _DAC_CTRL_REFSEL_1V25             0x00000000UL                         /**< Mode 1V25 for DAC_CTRL */
#define _DAC_CTRL_REFSEL_2V5              0x00000001UL                         /**< Mode 2V5 for DAC_CTRL */
#define _DAC_CTRL_REFSEL_VDD              0x00000002UL                         /**< Mode VDD for DAC_CTRL */
#define DAC_CTRL_REFSEL_DEFAULT           (_DAC_CTRL_REFSEL_DEFAULT << 8)      /**< Shifted mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_REFSEL_1V25              (_DAC_CTRL_REFSEL_1V25 << 8)         /**< Shifted mode 1V25 for DAC_CTRL */
#define DAC_CTRL_REFSEL_2V5               (_DAC_CTRL_REFSEL_2V5 << 8)          /**< Shifted mode 2V5 for DAC_CTRL */
#define DAC_CTRL_REFSEL_VDD               (_DAC_CTRL_REFSEL_VDD << 8)          /**< Shifted mode VDD for DAC_CTRL */
#define _DAC_CTRL_PRESC_SHIFT             16                                   /**< Shift value for DAC_PRESC */
#define _DAC_CTRL_PRESC_MASK              0x70000UL                            /**< Bit mask for DAC_PRESC */
#define _DAC_CTRL_PRESC_DEFAULT           0x00000000UL                         /**< Mode DEFAULT for DAC_CTRL */
#define _DAC_CTRL_PRESC_NODIVISION        0x00000000UL                         /**< Mode NODIVISION for DAC_CTRL */
#define DAC_CTRL_PRESC_DEFAULT            (_DAC_CTRL_PRESC_DEFAULT << 16)      /**< Shifted mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_PRESC_NODIVISION         (_DAC_CTRL_PRESC_NODIVISION << 16)   /**< Shifted mode NODIVISION for DAC_CTRL */
#define _DAC_CTRL_REFRSEL_SHIFT           20                                   /**< Shift value for DAC_REFRSEL */
#define _DAC_CTRL_REFRSEL_MASK            0x300000UL                           /**< Bit mask for DAC_REFRSEL */
#define _DAC_CTRL_REFRSEL_DEFAULT         0x00000000UL                         /**< Mode DEFAULT for DAC_CTRL */
#define _DAC_CTRL_REFRSEL_8CYCLES         0x00000000UL                         /**< Mode 8CYCLES for DAC_CTRL */
#define _DAC_CTRL_REFRSEL_16CYCLES        0x00000001UL                         /**< Mode 16CYCLES for DAC_CTRL */
#define _DAC_CTRL_REFRSEL_32CYCLES        0x00000002UL                         /**< Mode 32CYCLES for DAC_CTRL */
#define _DAC_CTRL_REFRSEL_64CYCLES        0x00000003UL                         /**< Mode 64CYCLES for DAC_CTRL */
#define DAC_CTRL_REFRSEL_DEFAULT          (_DAC_CTRL_REFRSEL_DEFAULT << 20)    /**< Shifted mode DEFAULT for DAC_CTRL */
#define DAC_CTRL_REFRSEL_8CYCLES          (_DAC_CTRL_REFRSEL_8CYCLES << 20)    /**< Shifted mode 8CYCLES for DAC_CTRL */
#define DAC_CTRL_REFRSEL_16CYCLES         (_DAC_CTRL_REFRSEL_16CYCLES << 20)   /**< Shifted mode 16CYCLES for DAC_CTRL */
#define DAC_CTRL_REFRSEL_32CYCLES         (_DAC_CTRL_REFRSEL_32CYCLES << 20)   /**< Shifted mode 32CYCLES for DAC_CTRL */
#define DAC_CTRL_REFRSEL_64CYCLES         (_DAC_CTRL_REFRSEL_64CYCLES << 20)   /**< Shifted mode 64CYCLES for DAC_CTRL */

/* Bit fields for DAC STATUS */
#define _DAC_STATUS_RESETVALUE            0x00000000UL                     /**< Default value for DAC_STATUS */
#define _DAC_STATUS_MASK                  0x00000003UL                     /**< Mask for DAC_STATUS */
#define DAC_STATUS_CH0DV                  (0x1UL << 0)                     /**< Channel 0 Data Valid */
#define _DAC_STATUS_CH0DV_SHIFT           0                                /**< Shift value for DAC_CH0DV */
#define _DAC_STATUS_CH0DV_MASK            0x1UL                            /**< Bit mask for DAC_CH0DV */
#define _DAC_STATUS_CH0DV_DEFAULT         0x00000000UL                     /**< Mode DEFAULT for DAC_STATUS */
#define DAC_STATUS_CH0DV_DEFAULT          (_DAC_STATUS_CH0DV_DEFAULT << 0) /**< Shifted mode DEFAULT for DAC_STATUS */
#define DAC_STATUS_CH1DV                  (0x1UL << 1)                     /**< Channel 1 Data Valid */
#define _DAC_STATUS_CH1DV_SHIFT           1                                /**< Shift value for DAC_CH1DV */
#define _DAC_STATUS_CH1DV_MASK            0x2UL                            /**< Bit mask for DAC_CH1DV */
#define _DAC_STATUS_CH1DV_DEFAULT         0x00000000UL                     /**< Mode DEFAULT for DAC_STATUS */
#define DAC_STATUS_CH1DV_DEFAULT          (_DAC_STATUS_CH1DV_DEFAULT << 1) /**< Shifted mode DEFAULT for DAC_STATUS */

/* Bit fields for DAC CH0CTRL */
#define _DAC_CH0CTRL_RESETVALUE           0x00000000UL                       /**< Default value for DAC_CH0CTRL */
#define _DAC_CH0CTRL_MASK                 0x00000077UL                       /**< Mask for DAC_CH0CTRL */
#define DAC_CH0CTRL_EN                    (0x1UL << 0)                       /**< Channel 0 Enable */
#define _DAC_CH0CTRL_EN_SHIFT             0                                  /**< Shift value for DAC_EN */
#define _DAC_CH0CTRL_EN_MASK              0x1UL                              /**< Bit mask for DAC_EN */
#define _DAC_CH0CTRL_EN_DEFAULT           0x00000000UL                       /**< Mode DEFAULT for DAC_CH0CTRL */
#define DAC_CH0CTRL_EN_DEFAULT            (_DAC_CH0CTRL_EN_DEFAULT << 0)     /**< Shifted mode DEFAULT for DAC_CH0CTRL */
#define DAC_CH0CTRL_REFREN                (0x1UL << 1)                       /**< Channel 0 Automatic Refresh Enable */
#define _DAC_CH0CTRL_REFREN_SHIFT         1                                  /**< Shift value for DAC_REFREN */
#define _DAC_CH0CTRL_REFREN_MASK          0x2UL                              /**< Bit mask for DAC_REFREN */
#define _DAC_CH0CTRL_REFREN_DEFAULT       0x00000000UL                       /**< Mode DEFAULT for DAC_CH0CTRL */
#define DAC_CH0CTRL_REFREN_DEFAULT        (_DAC_CH0CTRL_REFREN_DEFAULT << 1) /**< Shifted mode DEFAULT for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSEN                 (0x1UL << 2)                       /**< Channel 0 PRS Trigger Enable */
#define _DAC_CH0CTRL_PRSEN_SHIFT          2                                  /**< Shift value for DAC_PRSEN */
#define _DAC_CH0CTRL_PRSEN_MASK           0x4UL                              /**< Bit mask for DAC_PRSEN */
#define _DAC_CH0CTRL_PRSEN_DEFAULT        0x00000000UL                       /**< Mode DEFAULT for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSEN_DEFAULT         (_DAC_CH0CTRL_PRSEN_DEFAULT << 2)  /**< Shifted mode DEFAULT for DAC_CH0CTRL */
#define _DAC_CH0CTRL_PRSSEL_SHIFT         4                                  /**< Shift value for DAC_PRSSEL */
#define _DAC_CH0CTRL_PRSSEL_MASK          0x70UL                             /**< Bit mask for DAC_PRSSEL */
#define _DAC_CH0CTRL_PRSSEL_DEFAULT       0x00000000UL                       /**< Mode DEFAULT for DAC_CH0CTRL */
#define _DAC_CH0CTRL_PRSSEL_PRSCH0        0x00000000UL                       /**< Mode PRSCH0 for DAC_CH0CTRL */
#define _DAC_CH0CTRL_PRSSEL_PRSCH1        0x00000001UL                       /**< Mode PRSCH1 for DAC_CH0CTRL */
#define _DAC_CH0CTRL_PRSSEL_PRSCH2        0x00000002UL                       /**< Mode PRSCH2 for DAC_CH0CTRL */
#define _DAC_CH0CTRL_PRSSEL_PRSCH3        0x00000003UL                       /**< Mode PRSCH3 for DAC_CH0CTRL */
#define _DAC_CH0CTRL_PRSSEL_PRSCH4        0x00000004UL                       /**< Mode PRSCH4 for DAC_CH0CTRL */
#define _DAC_CH0CTRL_PRSSEL_PRSCH5        0x00000005UL                       /**< Mode PRSCH5 for DAC_CH0CTRL */
#define _DAC_CH0CTRL_PRSSEL_PRSCH6        0x00000006UL                       /**< Mode PRSCH6 for DAC_CH0CTRL */
#define _DAC_CH0CTRL_PRSSEL_PRSCH7        0x00000007UL                       /**< Mode PRSCH7 for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSSEL_DEFAULT        (_DAC_CH0CTRL_PRSSEL_DEFAULT << 4) /**< Shifted mode DEFAULT for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSSEL_PRSCH0         (_DAC_CH0CTRL_PRSSEL_PRSCH0 << 4)  /**< Shifted mode PRSCH0 for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSSEL_PRSCH1         (_DAC_CH0CTRL_PRSSEL_PRSCH1 << 4)  /**< Shifted mode PRSCH1 for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSSEL_PRSCH2         (_DAC_CH0CTRL_PRSSEL_PRSCH2 << 4)  /**< Shifted mode PRSCH2 for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSSEL_PRSCH3         (_DAC_CH0CTRL_PRSSEL_PRSCH3 << 4)  /**< Shifted mode PRSCH3 for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSSEL_PRSCH4         (_DAC_CH0CTRL_PRSSEL_PRSCH4 << 4)  /**< Shifted mode PRSCH4 for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSSEL_PRSCH5         (_DAC_CH0CTRL_PRSSEL_PRSCH5 << 4)  /**< Shifted mode PRSCH5 for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSSEL_PRSCH6         (_DAC_CH0CTRL_PRSSEL_PRSCH6 << 4)  /**< Shifted mode PRSCH6 for DAC_CH0CTRL */
#define DAC_CH0CTRL_PRSSEL_PRSCH7         (_DAC_CH0CTRL_PRSSEL_PRSCH7 << 4)  /**< Shifted mode PRSCH7 for DAC_CH0CTRL */

/* Bit fields for DAC CH1CTRL */
#define _DAC_CH1CTRL_RESETVALUE           0x00000000UL                       /**< Default value for DAC_CH1CTRL */
#define _DAC_CH1CTRL_MASK                 0x00000077UL                       /**< Mask for DAC_CH1CTRL */
#define DAC_CH1CTRL_EN                    (0x1UL << 0)                       /**< Channel 1 Enable */
#define _DAC_CH1CTRL_EN_SHIFT             0                                  /**< Shift value for DAC_EN */
#define _DAC_CH1CTRL_EN_MASK              0x1UL                              /**< Bit mask for DAC_EN */
#define _DAC_CH1CTRL_EN_DEFAULT           0x00000000UL                       /**< Mode DEFAULT for DAC_CH1CTRL */
#define DAC_CH1CTRL_EN_DEFAULT            (_DAC_CH1CTRL_EN_DEFAULT << 0)     /**< Shifted mode DEFAULT for DAC_CH1CTRL */
#define DAC_CH1CTRL_REFREN                (0x1UL << 1)                       /**< Channel 1 Automatic Refresh Enable */
#define _DAC_CH1CTRL_REFREN_SHIFT         1                                  /**< Shift value for DAC_REFREN */
#define _DAC_CH1CTRL_REFREN_MASK          0x2UL                              /**< Bit mask for DAC_REFREN */
#define _DAC_CH1CTRL_REFREN_DEFAULT       0x00000000UL                       /**< Mode DEFAULT for DAC_CH1CTRL */
#define DAC_CH1CTRL_REFREN_DEFAULT        (_DAC_CH1CTRL_REFREN_DEFAULT << 1) /**< Shifted mode DEFAULT for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSEN                 (0x1UL << 2)                       /**< Channel 1 PRS Trigger Enable */
#define _DAC_CH1CTRL_PRSEN_SHIFT          2                                  /**< Shift value for DAC_PRSEN */
#define _DAC_CH1CTRL_PRSEN_MASK           0x4UL                              /**< Bit mask for DAC_PRSEN */
#define _DAC_CH1CTRL_PRSEN_DEFAULT        0x00000000UL                       /**< Mode DEFAULT for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSEN_DEFAULT         (_DAC_CH1CTRL_PRSEN_DEFAULT << 2)  /**< Shifted mode DEFAULT for DAC_CH1CTRL */
#define _DAC_CH1CTRL_PRSSEL_SHIFT         4                                  /**< Shift value for DAC_PRSSEL */
#define _DAC_CH1CTRL_PRSSEL_MASK          0x70UL                             /**< Bit mask for DAC_PRSSEL */
#define _DAC_CH1CTRL_PRSSEL_DEFAULT       0x00000000UL                       /**< Mode DEFAULT for DAC_CH1CTRL */
#define _DAC_CH1CTRL_PRSSEL_PRSCH0        0x00000000UL                       /**< Mode PRSCH0 for DAC_CH1CTRL */
#define _DAC_CH1CTRL_PRSSEL_PRSCH1        0x00000001UL                       /**< Mode PRSCH1 for DAC_CH1CTRL */
#define _DAC_CH1CTRL_PRSSEL_PRSCH2        0x00000002UL                       /**< Mode PRSCH2 for DAC_CH1CTRL */
#define _DAC_CH1CTRL_PRSSEL_PRSCH3        0x00000003UL                       /**< Mode PRSCH3 for DAC_CH1CTRL */
#define _DAC_CH1CTRL_PRSSEL_PRSCH4        0x00000004UL                       /**< Mode PRSCH4 for DAC_CH1CTRL */
#define _DAC_CH1CTRL_PRSSEL_PRSCH5        0x00000005UL                       /**< Mode PRSCH5 for DAC_CH1CTRL */
#define _DAC_CH1CTRL_PRSSEL_PRSCH6        0x00000006UL                       /**< Mode PRSCH6 for DAC_CH1CTRL */
#define _DAC_CH1CTRL_PRSSEL_PRSCH7        0x00000007UL                       /**< Mode PRSCH7 for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSSEL_DEFAULT        (_DAC_CH1CTRL_PRSSEL_DEFAULT << 4) /**< Shifted mode DEFAULT for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSSEL_PRSCH0         (_DAC_CH1CTRL_PRSSEL_PRSCH0 << 4)  /**< Shifted mode PRSCH0 for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSSEL_PRSCH1         (_DAC_CH1CTRL_PRSSEL_PRSCH1 << 4)  /**< Shifted mode PRSCH1 for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSSEL_PRSCH2         (_DAC_CH1CTRL_PRSSEL_PRSCH2 << 4)  /**< Shifted mode PRSCH2 for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSSEL_PRSCH3         (_DAC_CH1CTRL_PRSSEL_PRSCH3 << 4)  /**< Shifted mode PRSCH3 for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSSEL_PRSCH4         (_DAC_CH1CTRL_PRSSEL_PRSCH4 << 4)  /**< Shifted mode PRSCH4 for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSSEL_PRSCH5         (_DAC_CH1CTRL_PRSSEL_PRSCH5 << 4)  /**< Shifted mode PRSCH5 for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSSEL_PRSCH6         (_DAC_CH1CTRL_PRSSEL_PRSCH6 << 4)  /**< Shifted mode PRSCH6 for DAC_CH1CTRL */
#define DAC_CH1CTRL_PRSSEL_PRSCH7         (_DAC_CH1CTRL_PRSSEL_PRSCH7 << 4)  /**< Shifted mode PRSCH7 for DAC_CH1CTRL */

/* Bit fields for DAC IEN */
#define _DAC_IEN_RESETVALUE               0x00000000UL                  /**< Default value for DAC_IEN */
#define _DAC_IEN_MASK                     0x00000033UL                  /**< Mask for DAC_IEN */
#define DAC_IEN_CH0                       (0x1UL << 0)                  /**< Channel 0 Conversion Complete Interrupt Enable */
#define _DAC_IEN_CH0_SHIFT                0                             /**< Shift value for DAC_CH0 */
#define _DAC_IEN_CH0_MASK                 0x1UL                         /**< Bit mask for DAC_CH0 */
#define _DAC_IEN_CH0_DEFAULT              0x00000000UL                  /**< Mode DEFAULT for DAC_IEN */
#define DAC_IEN_CH0_DEFAULT               (_DAC_IEN_CH0_DEFAULT << 0)   /**< Shifted mode DEFAULT for DAC_IEN */
#define DAC_IEN_CH1                       (0x1UL << 1)                  /**< Channel 1 Conversion Complete Interrupt Enable */
#define _DAC_IEN_CH1_SHIFT                1                             /**< Shift value for DAC_CH1 */
#define _DAC_IEN_CH1_MASK                 0x2UL                         /**< Bit mask for DAC_CH1 */
#define _DAC_IEN_CH1_DEFAULT              0x00000000UL                  /**< Mode DEFAULT for DAC_IEN */
#define DAC_IEN_CH1_DEFAULT               (_DAC_IEN_CH1_DEFAULT << 1)   /**< Shifted mode DEFAULT for DAC_IEN */
#define DAC_IEN_CH0UF                     (0x1UL << 4)                  /**< Channel 0 Conversion Data Underflow Interrupt Enable */
#define _DAC_IEN_CH0UF_SHIFT              4                             /**< Shift value for DAC_CH0UF */
#define _DAC_IEN_CH0UF_MASK               0x10UL                        /**< Bit mask for DAC_CH0UF */
#define _DAC_IEN_CH0UF_DEFAULT            0x00000000UL                  /**< Mode DEFAULT for DAC_IEN */
#define DAC_IEN_CH0UF_DEFAULT             (_DAC_IEN_CH0UF_DEFAULT << 4) /**< Shifted mode DEFAULT for DAC_IEN */
#define DAC_IEN_CH1UF                     (0x1UL << 5)                  /**< Channel 1 Conversion Data Underflow Interrupt Enable */
#define _DAC_IEN_CH1UF_SHIFT              5                             /**< Shift value for DAC_CH1UF */
#define _DAC_IEN_CH1UF_MASK               0x20UL                        /**< Bit mask for DAC_CH1UF */
#define _DAC_IEN_CH1UF_DEFAULT            0x00000000UL                  /**< Mode DEFAULT for DAC_IEN */
#define DAC_IEN_CH1UF_DEFAULT             (_DAC_IEN_CH1UF_DEFAULT << 5) /**< Shifted mode DEFAULT for DAC_IEN */

/* Bit fields for DAC IF */
#define _DAC_IF_RESETVALUE                0x00000000UL                 /**< Default value for DAC_IF */
#define _DAC_IF_MASK                      0x00000033UL                 /**< Mask for DAC_IF */
#define DAC_IF_CH0                        (0x1UL << 0)                 /**< Channel 0 Conversion Complete Interrupt Flag */
#define _DAC_IF_CH0_SHIFT                 0                            /**< Shift value for DAC_CH0 */
#define _DAC_IF_CH0_MASK                  0x1UL                        /**< Bit mask for DAC_CH0 */
#define _DAC_IF_CH0_DEFAULT               0x00000000UL                 /**< Mode DEFAULT for DAC_IF */
#define DAC_IF_CH0_DEFAULT                (_DAC_IF_CH0_DEFAULT << 0)   /**< Shifted mode DEFAULT for DAC_IF */
#define DAC_IF_CH1                        (0x1UL << 1)                 /**< Channel 1 Conversion Complete Interrupt Flag */
#define _DAC_IF_CH1_SHIFT                 1                            /**< Shift value for DAC_CH1 */
#define _DAC_IF_CH1_MASK                  0x2UL                        /**< Bit mask for DAC_CH1 */
#define _DAC_IF_CH1_DEFAULT               0x00000000UL                 /**< Mode DEFAULT for DAC_IF */
#define DAC_IF_CH1_DEFAULT                (_DAC_IF_CH1_DEFAULT << 1)   /**< Shifted mode DEFAULT for DAC_IF */
#define DAC_IF_CH0UF                      (0x1UL << 4)                 /**< Channel 0 Data Underflow Interrupt Flag */
#define _DAC_IF_CH0UF_SHIFT               4                            /**< Shift value for DAC_CH0UF */
#define _DAC_IF_CH0UF_MASK                0x10UL                       /**< Bit mask for DAC_CH0UF */
#define _DAC_IF_CH0UF_DEFAULT             0x00000000UL                 /**< Mode DEFAULT for DAC_IF */
#define DAC_IF_CH0UF_DEFAULT              (_DAC_IF_CH0UF_DEFAULT << 4) /**< Shifted mode DEFAULT for DAC_IF */
#define DAC_IF_CH1UF                      (0x1UL << 5)                 /**< Channel 1 Data Underflow Interrupt Flag */
#define _DAC_IF_CH1UF_SHIFT               5                            /**< Shift value for DAC_CH1UF */
#define _DAC_IF_CH1UF_MASK                0x20UL                       /**< Bit mask for DAC_CH1UF */
#define _DAC_IF_CH1UF_DEFAULT             0x00000000UL                 /**< Mode DEFAULT for DAC_IF */
#define DAC_IF_CH1UF_DEFAULT              (_DAC_IF_CH1UF_DEFAULT << 5) /**< Shifted mode DEFAULT for DAC_IF */

/* Bit fields for DAC IFS */
#define _DAC_IFS_RESETVALUE               0x00000000UL                  /**< Default value for DAC_IFS */
#define _DAC_IFS_MASK                     0x00000033UL                  /**< Mask for DAC_IFS */
#define DAC_IFS_CH0                       (0x1UL << 0)                  /**< Channel 0 Conversion Complete Interrupt Flag Set */
#define _DAC_IFS_CH0_SHIFT                0                             /**< Shift value for DAC_CH0 */
#define _DAC_IFS_CH0_MASK                 0x1UL                         /**< Bit mask for DAC_CH0 */
#define _DAC_IFS_CH0_DEFAULT              0x00000000UL                  /**< Mode DEFAULT for DAC_IFS */
#define DAC_IFS_CH0_DEFAULT               (_DAC_IFS_CH0_DEFAULT << 0)   /**< Shifted mode DEFAULT for DAC_IFS */
#define DAC_IFS_CH1                       (0x1UL << 1)                  /**< Channel 1 Conversion Complete Interrupt Flag Set */
#define _DAC_IFS_CH1_SHIFT                1                             /**< Shift value for DAC_CH1 */
#define _DAC_IFS_CH1_MASK                 0x2UL                         /**< Bit mask for DAC_CH1 */
#define _DAC_IFS_CH1_DEFAULT              0x00000000UL                  /**< Mode DEFAULT for DAC_IFS */
#define DAC_IFS_CH1_DEFAULT               (_DAC_IFS_CH1_DEFAULT << 1)   /**< Shifted mode DEFAULT for DAC_IFS */
#define DAC_IFS_CH0UF                     (0x1UL << 4)                  /**< Channel 0 Data Underflow Interrupt Flag Set */
#define _DAC_IFS_CH0UF_SHIFT              4                             /**< Shift value for DAC_CH0UF */
#define _DAC_IFS_CH0UF_MASK               0x10UL                        /**< Bit mask for DAC_CH0UF */
#define _DAC_IFS_CH0UF_DEFAULT            0x00000000UL                  /**< Mode DEFAULT for DAC_IFS */
#define DAC_IFS_CH0UF_DEFAULT             (_DAC_IFS_CH0UF_DEFAULT << 4) /**< Shifted mode DEFAULT for DAC_IFS */
#define DAC_IFS_CH1UF                     (0x1UL << 5)                  /**< Channel 1 Data Underflow Interrupt Flag Set */
#define _DAC_IFS_CH1UF_SHIFT              5                             /**< Shift value for DAC_CH1UF */
#define _DAC_IFS_CH1UF_MASK               0x20UL                        /**< Bit mask for DAC_CH1UF */
#define _DAC_IFS_CH1UF_DEFAULT            0x00000000UL                  /**< Mode DEFAULT for DAC_IFS */
#define DAC_IFS_CH1UF_DEFAULT             (_DAC_IFS_CH1UF_DEFAULT << 5) /**< Shifted mode DEFAULT for DAC_IFS */

/* Bit fields for DAC IFC */
#define _DAC_IFC_RESETVALUE               0x00000000UL                  /**< Default value for DAC_IFC */
#define _DAC_IFC_MASK                     0x00000033UL                  /**< Mask for DAC_IFC */
#define DAC_IFC_CH0                       (0x1UL << 0)                  /**< Channel 0 Conversion Complete Interrupt Flag Clear */
#define _DAC_IFC_CH0_SHIFT                0                             /**< Shift value for DAC_CH0 */
#define _DAC_IFC_CH0_MASK                 0x1UL                         /**< Bit mask for DAC_CH0 */
#define _DAC_IFC_CH0_DEFAULT              0x00000000UL                  /**< Mode DEFAULT for DAC_IFC */
#define DAC_IFC_CH0_DEFAULT               (_DAC_IFC_CH0_DEFAULT << 0)   /**< Shifted mode DEFAULT for DAC_IFC */
#define DAC_IFC_CH1                       (0x1UL << 1)                  /**< Channel 1 Conversion Complete Interrupt Flag Clear */
#define _DAC_IFC_CH1_SHIFT                1                             /**< Shift value for DAC_CH1 */
#define _DAC_IFC_CH1_MASK                 0x2UL                         /**< Bit mask for DAC_CH1 */
#define _DAC_IFC_CH1_DEFAULT              0x00000000UL                  /**< Mode DEFAULT for DAC_IFC */
#define DAC_IFC_CH1_DEFAULT               (_DAC_IFC_CH1_DEFAULT << 1)   /**< Shifted mode DEFAULT for DAC_IFC */
#define DAC_IFC_CH0UF                     (0x1UL << 4)                  /**< Channel 0 Data Underflow Interrupt Flag Clear */
#define _DAC_IFC_CH0UF_SHIFT              4                             /**< Shift value for DAC_CH0UF */
#define _DAC_IFC_CH0UF_MASK               0x10UL                        /**< Bit mask for DAC_CH0UF */
#define _DAC_IFC_CH0UF_DEFAULT            0x00000000UL                  /**< Mode DEFAULT for DAC_IFC */
#define DAC_IFC_CH0UF_DEFAULT             (_DAC_IFC_CH0UF_DEFAULT << 4) /**< Shifted mode DEFAULT for DAC_IFC */
#define DAC_IFC_CH1UF                     (0x1UL << 5)                  /**< Channel 1 Data Underflow Interrupt Flag Clear */
#define _DAC_IFC_CH1UF_SHIFT              5                             /**< Shift value for DAC_CH1UF */
#define _DAC_IFC_CH1UF_MASK               0x20UL                        /**< Bit mask for DAC_CH1UF */
#define _DAC_IFC_CH1UF_DEFAULT            0x00000000UL                  /**< Mode DEFAULT for DAC_IFC */
#define DAC_IFC_CH1UF_DEFAULT             (_DAC_IFC_CH1UF_DEFAULT << 5) /**< Shifted mode DEFAULT for DAC_IFC */

/* Bit fields for DAC CH0DATA */
#define _DAC_CH0DATA_RESETVALUE           0x00000000UL                     /**< Default value for DAC_CH0DATA */
#define _DAC_CH0DATA_MASK                 0x00000FFFUL                     /**< Mask for DAC_CH0DATA */
#define _DAC_CH0DATA_DATA_SHIFT           0                                /**< Shift value for DAC_DATA */
#define _DAC_CH0DATA_DATA_MASK            0xFFFUL                          /**< Bit mask for DAC_DATA */
#define _DAC_CH0DATA_DATA_DEFAULT         0x00000000UL                     /**< Mode DEFAULT for DAC_CH0DATA */
#define DAC_CH0DATA_DATA_DEFAULT          (_DAC_CH0DATA_DATA_DEFAULT << 0) /**< Shifted mode DEFAULT for DAC_CH0DATA */

/* Bit fields for DAC CH1DATA */
#define _DAC_CH1DATA_RESETVALUE           0x00000000UL                     /**< Default value for DAC_CH1DATA */
#define _DAC_CH1DATA_MASK                 0x00000FFFUL                     /**< Mask for DAC_CH1DATA */
#define _DAC_CH1DATA_DATA_SHIFT           0                                /**< Shift value for DAC_DATA */
#define _DAC_CH1DATA_DATA_MASK            0xFFFUL                          /**< Bit mask for DAC_DATA */
#define _DAC_CH1DATA_DATA_DEFAULT         0x00000000UL                     /**< Mode DEFAULT for DAC_CH1DATA */
#define DAC_CH1DATA_DATA_DEFAULT          (_DAC_CH1DATA_DATA_DEFAULT << 0) /**< Shifted mode DEFAULT for DAC_CH1DATA */

/* Bit fields for DAC COMBDATA */
#define _DAC_COMBDATA_RESETVALUE          0x00000000UL                          /**< Default value for DAC_COMBDATA */
#define _DAC_COMBDATA_MASK                0x0FFF0FFFUL                          /**< Mask for DAC_COMBDATA */
#define _DAC_COMBDATA_CH0DATA_SHIFT       0                                     /**< Shift value for DAC_CH0DATA */
#define _DAC_COMBDATA_CH0DATA_MASK        0xFFFUL                               /**< Bit mask for DAC_CH0DATA */
#define _DAC_COMBDATA_CH0DATA_DEFAULT     0x00000000UL                          /**< Mode DEFAULT for DAC_COMBDATA */
#define DAC_COMBDATA_CH0DATA_DEFAULT      (_DAC_COMBDATA_CH0DATA_DEFAULT << 0)  /**< Shifted mode DEFAULT for DAC_COMBDATA */
#define _DAC_COMBDATA_CH1DATA_SHIFT       16                                    /**< Shift value for DAC_CH1DATA */
#define _DAC_COMBDATA_CH1DATA_MASK        0xFFF0000UL                           /**< Bit mask for DAC_CH1DATA */
#define _DAC_COMBDATA_CH1DATA_DEFAULT     0x00000000UL                          /**< Mode DEFAULT for DAC_COMBDATA */
#define DAC_COMBDATA_CH1DATA_DEFAULT      (_DAC_COMBDATA_CH1DATA_DEFAULT << 16) /**< Shifted mode DEFAULT for DAC_COMBDATA */

/* Bit fields for DAC CAL */
#define _DAC_CAL_RESETVALUE               0x00400000UL                      /**< Default value for DAC_CAL */
#define _DAC_CAL_MASK                     0x007F3F3FUL                      /**< Mask for DAC_CAL */
#define _DAC_CAL_CH0OFFSET_SHIFT          0                                 /**< Shift value for DAC_CH0OFFSET */
#define _DAC_CAL_CH0OFFSET_MASK           0x3FUL                            /**< Bit mask for DAC_CH0OFFSET */
#define _DAC_CAL_CH0OFFSET_DEFAULT        0x00000000UL                      /**< Mode DEFAULT for DAC_CAL */
#define DAC_CAL_CH0OFFSET_DEFAULT         (_DAC_CAL_CH0OFFSET_DEFAULT << 0) /**< Shifted mode DEFAULT for DAC_CAL */
#define _DAC_CAL_CH1OFFSET_SHIFT          8                                 /**< Shift value for DAC_CH1OFFSET */
#define _DAC_CAL_CH1OFFSET_MASK           0x3F00UL                          /**< Bit mask for DAC_CH1OFFSET */
#define _DAC_CAL_CH1OFFSET_DEFAULT        0x00000000UL                      /**< Mode DEFAULT for DAC_CAL */
#define DAC_CAL_CH1OFFSET_DEFAULT         (_DAC_CAL_CH1OFFSET_DEFAULT << 8) /**< Shifted mode DEFAULT for DAC_CAL */
#define _DAC_CAL_GAIN_SHIFT               16                                /**< Shift value for DAC_GAIN */
#define _DAC_CAL_GAIN_MASK                0x7F0000UL                        /**< Bit mask for DAC_GAIN */
#define _DAC_CAL_GAIN_DEFAULT             0x00000040UL                      /**< Mode DEFAULT for DAC_CAL */
#define DAC_CAL_GAIN_DEFAULT              (_DAC_CAL_GAIN_DEFAULT << 16)     /**< Shifted mode DEFAULT for DAC_CAL */

/* Bit fields for DAC BIASPROG */
#define _DAC_BIASPROG_RESETVALUE          0x00000047UL                          /**< Default value for DAC_BIASPROG */
#define _DAC_BIASPROG_MASK                0x0000004FUL                          /**< Mask for DAC_BIASPROG */
#define _DAC_BIASPROG_BIASPROG_SHIFT      0                                     /**< Shift value for DAC_BIASPROG */
#define _DAC_BIASPROG_BIASPROG_MASK       0xFUL                                 /**< Bit mask for DAC_BIASPROG */
#define _DAC_BIASPROG_BIASPROG_DEFAULT    0x00000007UL                          /**< Mode DEFAULT for DAC_BIASPROG */
#define DAC_BIASPROG_BIASPROG_DEFAULT     (_DAC_BIASPROG_BIASPROG_DEFAULT << 0) /**< Shifted mode DEFAULT for DAC_BIASPROG */
#define DAC_BIASPROG_HALFBIAS             (0x1UL << 6)                          /**< Half Bias Current */
#define _DAC_BIASPROG_HALFBIAS_SHIFT      6                                     /**< Shift value for DAC_HALFBIAS */
#define _DAC_BIASPROG_HALFBIAS_MASK       0x40UL                                /**< Bit mask for DAC_HALFBIAS */
#define _DAC_BIASPROG_HALFBIAS_DEFAULT    0x00000001UL                          /**< Mode DEFAULT for DAC_BIASPROG */
#define DAC_BIASPROG_HALFBIAS_DEFAULT     (_DAC_BIASPROG_HALFBIAS_DEFAULT << 6) /**< Shifted mode DEFAULT for DAC_BIASPROG */

/** @} End of group EFM32G_DAC */


