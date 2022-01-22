/**************************************************************************//**
 * @file
 * @brief Operational Amplifier (OPAMP) peripheral API
 * @author Energy Micro AS
 * @version 3.0.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
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
#include "em_part.h"
#if defined( OPAMP_PRESENT ) && ( OPAMP_COUNT == 1 )

#include "em_system.h"
#include "em_assert.h"
#include "em_opamp.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/


/***************************************************************************//**
 * @addtogroup OPAMP
 * @brief Operational Amplifier (OPAMP) peripheral API
 * @details
 *  This module contains functions to:
 *   @li OPAMP_Enable()       Configure and enable an opamp.
 *   @li OPAMP_Disable()      Disable an opamp.
 *
 * All OPAMP functions assume that the DAC clock is running. If the DAC is not
 * used, the clock can be turned off when the opamp's are configured.
 *
 * If the available gain values dont suit the application at hand, the resistor
 * ladders can be disabled and external gain programming resistors used.
 *
 * A number of predefined opamp setup macros are available for configuration
 * of the most common opamp topologies (see figures below).
 *
 * @note
 * <em>The terms POSPAD and NEGPAD in the figures are used to indicate that these
 * pads should be connected to a suitable signal ground.</em>
 *
 * \n<b>Unity gain voltage follower.</b>\n
 * Use predefined macros @ref OPA_INIT_UNITY_GAIN and
 * @ref OPA_INIT_UNITY_GAIN_OPA2.
 * @verbatim

                       |\
            ___________|+\
                       |  \_______
                    ___|_ /    |
                   |   | /     |
                   |   |/      |
                   |___________|
   @endverbatim
 *
 * \n<b>Non-inverting amplifier.</b>\n
 * Use predefined macros @ref OPA_INIT_NON_INVERTING and
 * @ref OPA_INIT_NON_INVERTING_OPA2.
 * @verbatim

                       |\
            ___________|+\
                       |  \_______
                    ___|_ /    |
                   |   | /     |
                   |   |/      |
                   |_____R2____|
                   |
                   R1
                   |
                 NEGPAD @endverbatim
 *
 * \n<b>Inverting amplifier.</b>\n
 * Use predefined macros @ref OPA_INIT_INVERTING and
 * @ref OPA_INIT_INVERTING_OPA2.
 * @verbatim

                    _____R2____
                   |           |
                   |   |\      |
            ____R1_|___|_\     |
                       |  \____|___
                    ___|  /
                   |   |+/
                   |   |/
                   |
                 POSPAD @endverbatim
 *
 * \n<b>Cascaded non-inverting amplifiers.</b>\n
 * Use predefined macros @ref OPA_INIT_CASCADED_NON_INVERTING_OPA0,
 * @ref OPA_INIT_CASCADED_NON_INVERTING_OPA1 and
 * @ref OPA_INIT_CASCADED_NON_INVERTING_OPA2.
 * @verbatim

                       |\                       |\                       |\
            ___________|+\ OPA0      ___________|+\ OPA1      ___________|+\ OPA2
                       |  \_________|           |  \_________|           |  \_______
                    ___|_ /    |             ___|_ /    |             ___|_ /    |
                   |   | /     |            |   | /     |            |   | /     |
                   |   |/      |            |   |/      |            |   |/      |
                   |_____R2____|            |_____R2____|            |_____R2____|
                   |                        |                        |
                   R1                       R1                       R1
                   |                        |                        |
                 NEGPAD                   NEGPAD                   NEGPAD @endverbatim
 *
 * \n<b>Cascaded inverting amplifiers.</b>\n
 * Use predefined macros @ref OPA_INIT_CASCADED_INVERTING_OPA0,
 * @ref OPA_INIT_CASCADED_INVERTING_OPA1 and
 * @ref OPA_INIT_CASCADED_INVERTING_OPA2.
 * @verbatim

                    _____R2____              _____R2____              _____R2____
                   |           |            |           |            |           |
                   |   |\      |            |   |\      |            |   |\      |
            ____R1_|___|_\     |     ____R1_|___|_\     |     ____R1_|___|_\     |
                       |  \____|____|           |  \____|___|            |  \____|__
                    ___|  /                  ___|  /                  ___|  /
                   |   |+/ OPA0             |   |+/ OPA1             |   |+/ OPA2
                   |   |/                   |   |/                   |   |/
                   |                        |                        |
                 POSPAD                   POSPAD                   POSPAD @endverbatim
 *
 * \n<b>Differential driver with two opamp's.</b>\n
 * Use predefined macros @ref OPA_INIT_DIFF_DRIVER_OPA0 and
 * @ref OPA_INIT_DIFF_DRIVER_OPA1.
 * @verbatim

                                     __________________________
                                    |                          +
                                    |        _____R2____
                       |\           |       |           |
            ___________|+\ OPA0     |       |   |\ OPA1 |
                       |  \_________|____R1_|___|_\     |      _
                    ___|_ /         |           |  \____|______
                   |   | /          |        ___|  /
                   |   |/           |       |   |+/
                   |________________|       |   |/
                                            |
                                          POSPAD @endverbatim
 *
 * \n<b>Differential receiver with three opamp's.</b>\n
 * Use predefined macros @ref OPA_INIT_DIFF_RECEIVER_OPA0,
 * @ref OPA_INIT_DIFF_RECEIVER_OPA1 and @ref OPA_INIT_DIFF_RECEIVER_OPA2.
 * @verbatim

                       |\
             __________|+\ OPA1
            _          |  \_________
                    ___|_ /    |    |        _____R2____
                   |   | /     |    |       |           |
                   |   |/      |    |       |   |\      |
                   |___________|    |____R1_|___|_\     |
                                                |  \____|___
                       |\            ____R1_ ___|  /
            +__________|+\ OPA0     |       |   |+/ OPA2
                       |  \_________|       |   |/
                    ___|_ /    |            R2
                   |   | /     |            |
                   |   |/      |          NEGPAD OPA0
                   |___________|
   @endverbatim
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Disable an Operational Amplifier.
 *
 * @param[in] dac
 *   Pointer to DAC peripheral register block.
 *
 * @param[in] opa
 *   Selects an OPA, valid vaules are @ref OPA0, @ref OPA1 and @ref OPA2.
 ******************************************************************************/
void OPAMP_Disable( DAC_TypeDef *dac, OPAMP_TypeDef opa )
{
  EFM_ASSERT( DAC_REF_VALID( dac ) );
  EFM_ASSERT( DAC_OPA_VALID( opa ) );

  if ( opa == OPA0 )
  {
    dac->CH0CTRL &= ~DAC_CH0CTRL_EN;
    dac->OPACTRL &= ~DAC_OPACTRL_OPA0EN;
  }
  else if ( opa == OPA1 )
  {
    dac->CH1CTRL &= ~DAC_CH1CTRL_EN;
    dac->OPACTRL &= ~DAC_OPACTRL_OPA1EN;
  }
  else /* OPA2 */
  {
    dac->OPACTRL &= ~DAC_OPACTRL_OPA2EN;
  }
}


/***************************************************************************//**
 * @brief
 *   Configure and enable an Operational Amplifier.
 *
 * @details
 *
 * @param[in] dac
 *   Pointer to DAC peripheral register block.
 *
 * @param[in] opa
 *   Selects an OPA, valid vaules are @ref OPA0, @ref OPA1 and @ref OPA2.
 *
 * @param[in] init
 *   Pointer to a structure containing OPAMP init information.
 ******************************************************************************/
void OPAMP_Enable( DAC_TypeDef *dac, OPAMP_TypeDef opa, const OPAMP_Init_TypeDef *init )
{
  uint32_t offset;

  EFM_ASSERT( DAC_REF_VALID( dac ) );
  EFM_ASSERT( DAC_OPA_VALID( opa ) );
  EFM_ASSERT( init->bias <= ( _DAC_BIASPROG_BIASPROG_MASK  >>
                              _DAC_BIASPROG_BIASPROG_SHIFT    ) );

  if ( opa == OPA0 )
  {
    EFM_ASSERT( ( init->outPen & ~_DAC_OPA0MUX_OUTPEN_MASK ) == 0 );

    dac->BIASPROG = ( dac->BIASPROG
                      & ~( _DAC_BIASPROG_BIASPROG_MASK             |
                            DAC_BIASPROG_HALFBIAS                    )  ) |
                    ( init->bias      << _DAC_BIASPROG_BIASPROG_SHIFT   ) |
                    ( init->halfBias   ? DAC_BIASPROG_HALFBIAS      : 0 );

    if ( init->defaultOffset )
    {
      offset = SYSTEM_GetCalibrationValue( &dac->CAL );
      dac->CAL = ( dac->CAL & ~_DAC_CAL_CH0OFFSET_MASK ) |
                 ( offset   &  _DAC_CAL_CH0OFFSET_MASK );
    }
    else
    {
      EFM_ASSERT( init->offset <= ( _DAC_CAL_CH0OFFSET_MASK >>
                                    _DAC_CAL_CH0OFFSET_SHIFT   ) );

      dac->CAL = ( dac->CAL      & ~_DAC_CAL_CH0OFFSET_MASK  ) |
                 ( init->offset <<  _DAC_CAL_CH0OFFSET_SHIFT );
    }

    dac->OPA0MUX  = (uint32_t)init->resSel                                |
                    (uint32_t)init->outMode                               |
                    init->outPen                                          |
                    (uint32_t)init->resInMux                              |
                    (uint32_t)init->negSel                                |
                    (uint32_t)init->posSel                                |
                    ( init->nextOut     ? DAC_OPA0MUX_NEXTOUT       : 0 ) |
                    ( init->npEn        ? DAC_OPA0MUX_NPEN          : 0 ) |
                    ( init->ppEn        ? DAC_OPA0MUX_PPEN          : 0 );

    dac->CH0CTRL |= DAC_CH0CTRL_EN;
    dac->OPACTRL  = ( dac->OPACTRL
                      & ~(  DAC_OPACTRL_OPA0SHORT                  |
                           _DAC_OPACTRL_OPA0LPFDIS_MASK            |
                            DAC_OPACTRL_OPA0HCMDIS                   )  ) |
                    ( init->shortInputs ?  DAC_OPACTRL_OPA0SHORT    : 0 ) |
                    ( init->lpfPosPadDisable ?
                                     DAC_OPACTRL_OPA0LPFDIS_PLPFDIS : 0 ) |
                    ( init->lpfNegPadDisable ?
                                     DAC_OPACTRL_OPA0LPFDIS_NLPFDIS : 0 ) |
                    ( init->hcmDisable  ?  DAC_OPACTRL_OPA0HCMDIS   : 0 ) |
                    ( DAC_OPACTRL_OPA0EN                                );
  }
  else if ( opa == OPA1 )
  {
    EFM_ASSERT( ( init->outPen & ~_DAC_OPA1MUX_OUTPEN_MASK ) == 0 );

    dac->BIASPROG = ( dac->BIASPROG
                      & ~( _DAC_BIASPROG_BIASPROG_MASK             |
                            DAC_BIASPROG_HALFBIAS                    )  ) |
                    ( init->bias      << _DAC_BIASPROG_BIASPROG_SHIFT   ) |
                    ( init->halfBias   ? DAC_BIASPROG_HALFBIAS      : 0 );

    if ( init->defaultOffset )
    {
      offset = SYSTEM_GetCalibrationValue( &dac->CAL );
      dac->CAL = ( dac->CAL & ~_DAC_CAL_CH1OFFSET_MASK ) |
                 ( offset   &  _DAC_CAL_CH1OFFSET_MASK );
    }
    else
    {
      EFM_ASSERT( init->offset <= ( _DAC_CAL_CH1OFFSET_MASK >>
                                    _DAC_CAL_CH1OFFSET_SHIFT   ) );

      dac->CAL = ( dac->CAL      & ~_DAC_CAL_CH1OFFSET_MASK  ) |
                 ( init->offset <<  _DAC_CAL_CH1OFFSET_SHIFT );
    }

    dac->OPA1MUX  = (uint32_t)init->resSel                                |
                    (uint32_t)init->outMode                               |
                    init->outPen                                          |
                    (uint32_t)init->resInMux                              |
                    (uint32_t)init->negSel                                |
                    (uint32_t)init->posSel                                |
                    ( init->nextOut     ? DAC_OPA1MUX_NEXTOUT       : 0 ) |
                    ( init->npEn        ? DAC_OPA1MUX_NPEN          : 0 ) |
                    ( init->ppEn        ? DAC_OPA1MUX_PPEN          : 0 );

    dac->CH1CTRL |= DAC_CH1CTRL_EN;
    dac->OPACTRL  = ( dac->OPACTRL
                      & ~(  DAC_OPACTRL_OPA1SHORT                  |
                           _DAC_OPACTRL_OPA1LPFDIS_MASK            |
                             DAC_OPACTRL_OPA1HCMDIS                  )  ) |
                    ( init->shortInputs ?  DAC_OPACTRL_OPA1SHORT    : 0 ) |
                    ( init->lpfPosPadDisable ?
                                     DAC_OPACTRL_OPA1LPFDIS_PLPFDIS : 0 ) |
                    ( init->lpfNegPadDisable ?
                                     DAC_OPACTRL_OPA1LPFDIS_NLPFDIS : 0 ) |
                    ( init->hcmDisable  ?  DAC_OPACTRL_OPA1HCMDIS   : 0 ) |
                    ( DAC_OPACTRL_OPA1EN                                );
  }
  else /* OPA2 */
  {
    EFM_ASSERT( ( init->posSel == DAC_OPA2MUX_POSSEL_DISABLE ) ||
                ( init->posSel == DAC_OPA2MUX_POSSEL_POSPAD  ) ||
                ( init->posSel == DAC_OPA2MUX_POSSEL_OPA1INP ) ||
                ( init->posSel == DAC_OPA2MUX_POSSEL_OPATAP  )    );

    EFM_ASSERT( ( init->outMode & ~DAC_OPA2MUX_OUTMODE ) == 0 );

    EFM_ASSERT( ( init->outPen & ~_DAC_OPA2MUX_OUTPEN_MASK ) == 0 );

    dac->BIASPROG = ( dac->BIASPROG
                      & ~( _DAC_BIASPROG_OPA2BIASPROG_MASK         |
                            DAC_BIASPROG_OPA2HALFBIAS                )  ) |
                    ( init->bias   << _DAC_BIASPROG_OPA2BIASPROG_SHIFT  ) |
                    ( init->halfBias   ? DAC_BIASPROG_OPA2HALFBIAS  : 0 );

    if ( init->defaultOffset )
    {
      offset = SYSTEM_GetCalibrationValue( &dac->OPAOFFSET );
      dac->OPAOFFSET = ( dac->OPAOFFSET & ~_DAC_OPAOFFSET_OPA2OFFSET_MASK ) |
                       ( offset         &  _DAC_OPAOFFSET_OPA2OFFSET_MASK );
    }
    else
    {
      EFM_ASSERT( init->offset <= ( _DAC_OPAOFFSET_OPA2OFFSET_MASK >>
                                    _DAC_OPAOFFSET_OPA2OFFSET_SHIFT   ) );

      dac->CAL = ( dac->CAL      & ~_DAC_OPAOFFSET_OPA2OFFSET_MASK  ) |
                 ( init->offset <<  _DAC_OPAOFFSET_OPA2OFFSET_SHIFT );
    }

    dac->OPA2MUX  = (uint32_t)init->resSel                                |
                    (uint32_t)init->outMode                               |
                    init->outPen                                          |
                    (uint32_t)init->resInMux                              |
                    (uint32_t)init->negSel                                |
                    (uint32_t)init->posSel                                |
                    ( init->nextOut     ? DAC_OPA2MUX_NEXTOUT       : 0 ) |
                    ( init->npEn        ? DAC_OPA2MUX_NPEN          : 0 ) |
                    ( init->ppEn        ? DAC_OPA2MUX_PPEN          : 0 );

    dac->OPACTRL  = ( dac->OPACTRL
                      & ~(  DAC_OPACTRL_OPA2SHORT                  |
                           _DAC_OPACTRL_OPA2LPFDIS_MASK            |
                            DAC_OPACTRL_OPA2HCMDIS                   )  ) |
                    ( init->shortInputs ?  DAC_OPACTRL_OPA2SHORT    : 0 ) |
                    ( init->lpfPosPadDisable ?
                                     DAC_OPACTRL_OPA2LPFDIS_PLPFDIS : 0 ) |
                    ( init->lpfNegPadDisable ?
                                     DAC_OPACTRL_OPA2LPFDIS_NLPFDIS : 0 ) |
                    ( init->hcmDisable  ?  DAC_OPACTRL_OPA2HCMDIS   : 0 ) |
                    ( DAC_OPACTRL_OPA2EN                                );
  }
}

/** @} (end addtogroup OPAMP) */
/** @} (end addtogroup EM_Library) */

#endif /* defined( OPAMP_PRESENT ) && ( OPAMP_COUNT == 1 ) */
