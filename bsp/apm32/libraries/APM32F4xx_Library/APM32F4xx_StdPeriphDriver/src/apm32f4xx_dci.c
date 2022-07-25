/*!
 * @file        apm32f4xx_dci.c
 *
 * @brief       This file provides all the DCI firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f4xx_dci.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup DCI_Driver
  * @brief DCI driver modules
  @{
*/

/** @defgroup DCI_Functions
  @{
*/

/*!
 * @brief     Reast the DCI registers to their default reset values.
 *
 * @param     None
 *
 * @retval    None
 */
void DCI_Rest(void)
{
    DCI->CTRL      = 0x00;
    DCI->INTEN     = 0x00;
    DCI->INTCLR    = 0x1F;
    DCI->ESYNCC    = 0x00;
    DCI->ESYNCUM   = 0x00;
    DCI->CROPWSTAT = 0x00;
    DCI->CROPWSIZE = 0x00;
}

/*!
 * @brief     Configure DCI by configuring the structure
 *
 * @param     dciConfig: pointer to a DCI_Config_T structure
 *
 * @retval    None
 */
void DCI_Config(DCI_Config_T *dciConfig)
{
    DCI->CTRL_B.CMODE    = dciConfig->captureMode;
    DCI->CTRL_B.ESYNCSEL = dciConfig->synchroMode;
    DCI->CTRL_B.PXCLKPOL = dciConfig->pckPolarity;
    DCI->CTRL_B.VSYNCPOL = dciConfig->vsyncPolarity;
    DCI->CTRL_B.HSYNCPOL = dciConfig->hsyncPolarity;
    DCI->CTRL_B.FCRCFG   = dciConfig->capturerate;
    DCI->CTRL_B.EXDMOD   = dciConfig->extendedDataMode;
}

/*!
 * @brief     Fills each DCI InitStruct member with its default value.
 *
 * @param     dciConfig : pointer to a DCI_Config_T structure
 *
 * @retval    None
 */
void DCI_ConfigStructInit(DCI_Config_T *dciConfig)
{
    dciConfig->captureMode      = DCI_CAPTURE_MODE_CONTINUOUS;
    dciConfig->synchroMode      = DCI_SYNCHRO_MODE_HARDWARE;
    dciConfig->pckPolarity      = DCI_PCK_POL_FALLING;
    dciConfig->vsyncPolarity    = DCI_VSYNC_POL_LOW;
    dciConfig->hsyncPolarity    = DCI_HSYNC_POL_LOW;
    dciConfig->capturerate      = DCI_CAPTURE_RATE_ALL_FRAME;
    dciConfig->extendedDataMode = DCI_EXTENDED_DATA_MODE_8B;
}

/*!
 * @brief       Configure DCI CROP mode by configuring the structure
 *
 * @param       cropConfig:  pointer to a DCI_CropConfig_T structure
 *
 * @retval      None
 */
void DCI_ConfigCROP(DCI_CropConfig_T *cropConfig)
{
    DCI->CROPWSTAT_B.HOFSCNT   = (uint16_t)cropConfig->horizontalOffsetCount;
    DCI->CROPWSTAT_B.VSLINECNT = (uint16_t)cropConfig->verticalStartLine;

    DCI->CROPWSIZE_B.CCNT     = (uint16_t)cropConfig->captureCount;
    DCI->CROPWSIZE_B.VLINECNT = (uint16_t)cropConfig->verticalLineCount;
}

/*!
 * @brief     Enable the DCI Crop.
 *
 * @param     None
 *
 * @retval    None
 */
void DCI_EnableCROP(void)
{
    DCI->CTRL_B.CROPF = SET;
}

/*!
 * @brief     Disable the DCI Crop.
 *
 * @param     None
 *
 * @retval    None
 */
void DCI_DisableCROP(void)
{
    DCI->CTRL_B.CROPF = RESET;
}

/*!
 * @brief     Sets the embedded synchronization codes
 *
 * @param     CodeConfig: pointer to a DCI_CodeConfig_T structure
 *
 * @retval    None
 */
void DCI_ConfigSynchroCode(DCI_CodeConfig_T *codeConfig)
{
    DCI->ESYNCC_B.FSDC = (uint8_t)codeConfig->frameStartCode;
    DCI->ESYNCC_B.LSDC = (uint8_t)codeConfig->lineStartCode;
    DCI->ESYNCC_B.LEDC = (uint8_t)codeConfig->lineEndCode;
    DCI->ESYNCC_B.FEDC = (uint8_t)codeConfig->frameEndCode;
}

/*!
 * @brief     Enable the DCI JPEG.
 *
 * @param     None
 *
 * @retval    None
 */
void  DCI_EnableJPEG(void)
{
    DCI->CTRL_B.JPGFM = SET;
}

/*!
 * @brief     Disable the DCI JPEG.
 *
 * @param     None
 *
 * @retval    None
 */
void  DCI_DisableJPEG(void)
{

    DCI->CTRL_B.JPGFM = RESET;
}

/*!
* @brief     Enable the DCI interface.
*
* @param     None
*
* @retval    None
*/
void  DCI_Enable(void)
{
    DCI->CTRL_B.DCIEN = SET;
}

/*!
 * @brief     Disable the DCI interface.
 *
 * @param     None
 *
 * @retval    None
 */
void  DCI_Disable(void)
{
    DCI->CTRL_B.DCIEN = RESET;
}

/*!
 * @brief     Enable the DCI Capture.
 *
 * @param     None
 *
 * @retval    None
 */
void  DCI_EnableCapture(void)
{
    DCI->CTRL_B.CEN = SET;
}

/*!
 * @brief     Disable the DCI Capture.
 *
 * @param     None
 *
 * @retval    None
 */
void  DCI_DisableCapture(void)
{
    DCI->CTRL_B.CEN = RESET;
}

/*!
 * @brief     Read the data stored in the DATA register.
 *
 * @param     None
 *
 * @retval    Data register value
 */
uint32_t DCI_ReadData(void)
{
    return DCI->DATA;
}

/*!
 * @brief     Enable the DCI interface interrupts.
 *
 * @param     interrupt: specifies the DCI interrupt sources
 *            This parameter can be any combination of the following values:
 *              @arg DCI_INT_CC:    Frame capture complete interrupt mask
 *              @arg DCI_INT_OVR:   Overflow interrupt mask
 *              @arg DCI_INT_ERR:   Synchronization error interrupt mask
 *              @arg DCI_INT_VSYNC: VSYNC interrupt mask
 *              @arg DCI_INT_LINE:  Line interrupt mask
 *
 * @retval    None
 */
void DCI_EnableInterrupt(uint32_t interrupt)
{
    DCI->INTEN |= (uint32_t)interrupt;
}

/*!
 * @brief     Disable the DCI interface interrupts.
 *
 * @param     interrupt: specifies the DCI interrupt sources
 *            This parameter can be any combination of the following values:
 *              @arg DCI_INT_CC:    Frame capture complete interrupt mask
 *              @arg DCI_INT_OVR:   Overflow interrupt mask
 *              @arg DCI_INT_ERR:   Synchronization error interrupt mask
 *              @arg DCI_INT_VSYNC: VSYNC interrupt mask
 *              @arg DCI_INT_LINE:  Line interrupt mask
 *
 * @retval    None
 */
void DCI_DisableInterrupt(uint32_t interrupt)
{
    DCI->INTEN &= ~(uint32_t)interrupt;
}

/*!
 * @brief     Reads the DCI flag.
 *
 * @param     flag: specifies the flag to check.
 *            This parameter can be one of the following values:
 *              @arg DCI_FLAG_CCI:     Frame capture complete Raw flag mask
 *              @arg DCI_FLAG_OVRI:    Overflow Raw flag mask
 *              @arg DCI_FLAG_ERRI:    Synchronization error Raw flag mask
 *              @arg DCI_FLAG_VSYNCI:  VSYNC Raw flag mask
 *              @arg DCI_FLAG_LINEI:   Line Raw flag mask
 *              @arg DCI_FLAG_CCMI:    Frame capture complete Masked flag mask
 *              @arg DCI_FLAG_OVRMI:   Overflow Masked flag mask
 *              @arg DCI_FLAG_ERRMI:   Synchronization error Masked flag mask
 *              @arg DCI_FLAG_VSYNCMI: VSYNC Masked flag mask
 *              @arg DCI_FLAG_LINEMI:  Line Masked flag mask
 *              @arg DCI_FLAG_HSYNC:   HSYNC flag mask
 *              @arg DCI_FLAG_VSYNC:   VSYNC flag mask
 *              @arg DCI_FLAG_FNE:     Fifo not empty flag mask
 *
 * @retval    SET or RESET.
 */
uint16_t DCI_ReadStatusFlag(DCI_FLAG_T flag)
{
    uint32_t offset, temp = 0;
    offset = (flag >> 12);

    if (offset == 0x00)
    {
        temp = DCI->RINTSTS;
    }
    else if (offset == 0x01)
    {
        temp = DCI->MINTSTS;
    }
    else
    {
        temp = DCI->STS;
    }
    return (temp & flag) ? SET : RESET;
}

/*!
 * @brief     Clears the DCI flag.
 *
 * @param     flag: specifies the flag to clear.
 *            This parameter can be any combination of the following values:
 *              @arg DCI_FLAG_CCI:     Frame capture complete Raw flag mask
 *              @arg DCI_FLAG_OVRI:    Overflow Raw flag mask
 *              @arg DCI_FLAG_ERRI:    Synchronization error Raw flag mask
 *              @arg DCI_FLAG_VSYNCI:  VSYNC Raw flag mask
 *              @arg DCI_FLAG_LINEI:   Line Raw flag mask

 * @retval    None
 */
void DCI_ClearStatusFlag(uint16_t flag)
{
    DCI->INTCLR = (uint16_t)flag;
}

/*!
 * @brief     Read the DCI interrupt flag.
 *
 * @param     flag: specifies the DCI interrupt source to check.
 *            This parameter can be one of the following values:
 *              @arg DCI_INT_CC:    Frame capture complete interrupt mask
 *              @arg DCI_INT_OVR:   Overflow interrupt mask
 *              @arg DCI_INT_ERR:   Synchronization error interrupt mask
 *              @arg DCI_INT_VSYNC: VSYNC interrupt mask
 *              @arg DCI_INT_LINE:  Line interrupt mask
 *
 * @retval    None
 */
uint16_t DCI_ReadIntFlag(DCI_INT_T flag)
{
    return (DCI->MINTSTS & flag) ? SET : RESET;
}

/*!
 * @brief     Clear the DCI interrupt flag.
 *
 * @param     flag: specifies the DCI interrupt pending bit to clear.
 *            This parameter can be any combination of the following values:
 *              @arg DCI_INT_CC:    Frame capture complete interrupt mask
 *              @arg DCI_INT_OVR:   Overflow interrupt mask
 *              @arg DCI_INT_ERR:   Synchronization error interrupt mask
 *              @arg DCI_INT_VSYNC: VSYNC interrupt mask
 *              @arg DCI_INT_LINE:  Line interrupt mask
 *
 * @retval    None
 */
void DCI_ClearIntFlag(uint16_t flag)
{
    DCI->INTCLR = (uint16_t)flag;
}

/**@} end of group DCI_Functions */
/**@} end of group DCI_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
