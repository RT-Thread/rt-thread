/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_dmamux.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef N32H76x_78x_DMAMUX_H
#define N32H76x_78x_DMAMUX_H

#include "n32h76x_78x.h"


typedef enum
{
    DMAMUX1_ID     =0,
    DMAMUX2_ID     =1
}DMAMUX_ID;


/* Define used to get DMAMUX CHxCTRL register size */
#define DMAMUX_CHCTRL_SIZE                (0x00000004U)

/* Define used to get DMAMUX status register offset */
#define DMAMUX_CH_STATUS_OFFSET           (0x80U)
/* Define used to get DMAMUX RequestGenerator offset */
#define DMAMUX_REQ_GEN_OFFSET             (0x100U)
/* Define used to get DMAMUX Request Generator status register offset */
#define DMAMUX_REQ_GEN_STATUS_OFFSET      (0x180U)


/** DMAMUX1_Request_selection DMAMUX1 Request selection  */
#define DMAMUX_REQUEST_ID_MASK           (DMAMUX_CHxCTRL_REQID_MASK)
/* DMAMUX1 requests */
#define DMAMUX1_REQUEST_GENERATOR0       ((uint16_t)0x01U-1U)  /* DMAMUX1 request generator 0      */
#define DMAMUX1_REQUEST_GENERATOR1       ((uint16_t)0x02U-1U)  /* DMAMUX1 request generator 1      */
#define DMAMUX1_REQUEST_GENERATOR2       ((uint16_t)0x03U-1U)  /* DMAMUX1 request generator 2      */
#define DMAMUX1_REQUEST_GENERATOR3       ((uint16_t)0x04U-1U)  /* DMAMUX1 request generator 3      */
#define DMAMUX1_REQUEST_GENERATOR4       ((uint16_t)0x05U-1U)  /* DMAMUX1 request generator 4      */
#define DMAMUX1_REQUEST_GENERATOR5       ((uint16_t)0x06U-1U)  /* DMAMUX1 request generator 5      */
#define DMAMUX1_REQUEST_GENERATOR6       ((uint16_t)0x07U-1U)  /* DMAMUX1 request generator 6      */
#define DMAMUX1_REQUEST_GENERATOR7       ((uint16_t)0x08U-1U)  /* DMAMUX1 request generator 7      */
#define DMAMUX1_REQUEST_ADC1             ((uint16_t)0x09U-1U)  /* DMAMUX1 ADC1 request             */
#define DMAMUX1_REQUEST_ADC2             ((uint16_t)0x0AU-1U)  /* DMAMUX1 ADC2 request             */
#define DMAMUX1_REQUEST_ADC3             ((uint16_t)0x0BU-1U)  /* DMAMUX1 ADC3 request             */
//SHRTIM_DMA0-6 SHRTIM1-2 12-25
#define DMAMUX1_REQUEST_SHRTIM1_DMA0     ((uint16_t)0x0CU-1U)  /* DMAMUX1 SHRTIM1 request          */ 
#define DMAMUX1_REQUEST_SHRTIM1_DMA1     ((uint16_t)0x0DU-1U)  /* DMAMUX1 SHRTIM1 request          */ 
#define DMAMUX1_REQUEST_SHRTIM1_DMA2     ((uint16_t)0x0EU-1U)  /* DMAMUX1 SHRTIM1 request          */ 
#define DMAMUX1_REQUEST_SHRTIM1_DMA3     ((uint16_t)0x0FU-1U)  /* DMAMUX1 SHRTIM1 request          */ 
#define DMAMUX1_REQUEST_SHRTIM1_DMA4     ((uint16_t)0x10U-1U)  /* DMAMUX1 SHRTIM1 request          */ 
#define DMAMUX1_REQUEST_SHRTIM1_DMA5     ((uint16_t)0x11U-1U)  /* DMAMUX1 SHRTIM1 request          */ 
#define DMAMUX1_REQUEST_SHRTIM1_DMA6     ((uint16_t)0x12U-1U)  /* DMAMUX1 SHRTIM1 request          */ 
#define DMAMUX1_REQUEST_SHRTIM2_DMA0     ((uint16_t)0x13U-1U)  /* DMAMUX1 SHRTIM2 request          */ 
#define DMAMUX1_REQUEST_SHRTIM2_DMA1     ((uint16_t)0x14U-1U)  /* DMAMUX1 SHRTIM2 request          */ 
#define DMAMUX1_REQUEST_SHRTIM2_DMA2     ((uint16_t)0x15U-1U)  /* DMAMUX1 SHRTIM2 request          */ 
#define DMAMUX1_REQUEST_SHRTIM2_DMA3     ((uint16_t)0x16U-1U)  /* DMAMUX1 SHRTIM2 request          */ 
#define DMAMUX1_REQUEST_SHRTIM2_DMA4     ((uint16_t)0x17U-1U)  /* DMAMUX1 SHRTIM2 request          */ 
#define DMAMUX1_REQUEST_SHRTIM2_DMA5     ((uint16_t)0x18U-1U)  /* DMAMUX1 SHRTIM2 request          */ 
#define DMAMUX1_REQUEST_SHRTIM2_DMA6     ((uint16_t)0x19U-1U)  /* DMAMUX1 SHRTIM2 request          */ 
//ATIM 26-53
#define DMAMUX1_REQUEST_ATIM1_UP         ((uint16_t)0x1AU-1U)   /* DMAMUX1 ATIM1 UP request         */
#define DMAMUX1_REQUEST_ATIM1_CH1        ((uint16_t)0x1BU-1U)   /* DMAMUX1 ATIM1 CH1 request        */
#define DMAMUX1_REQUEST_ATIM1_CH2        ((uint16_t)0x1CU-1U)   /* DMAMUX1 ATIM1 CH2 request        */
#define DMAMUX1_REQUEST_ATIM1_CH3        ((uint16_t)0x1DU-1U)   /* DMAMUX1 ATIM1 CH3 request        */
#define DMAMUX1_REQUEST_ATIM1_CH4        ((uint16_t)0x1EU-1U)   /* DMAMUX1 ATIM1 CH4 request        */
#define DMAMUX1_REQUEST_ATIM1_TRIG       ((uint16_t)0x1FU-1U)   /* DMAMUX1 ATIM1 TRIG request       */
#define DMAMUX1_REQUEST_ATIM1_COM        ((uint16_t)0x20U-1U)   /* DMAMUX1 ATIM1 COM request        */
#define DMAMUX1_REQUEST_ATIM2_UP         ((uint16_t)0x21U-1U)   /* DMAMUX1 ATIM2 UP request         */
#define DMAMUX1_REQUEST_ATIM2_CH1        ((uint16_t)0x22U-1U)   /* DMAMUX1 ATIM2 CH1 request        */
#define DMAMUX1_REQUEST_ATIM2_CH2        ((uint16_t)0x23U-1U)   /* DMAMUX1 ATIM2 CH2 request        */
#define DMAMUX1_REQUEST_ATIM2_CH3        ((uint16_t)0x24U-1U)   /* DMAMUX1 ATIM2 CH3 request        */
#define DMAMUX1_REQUEST_ATIM2_CH4        ((uint16_t)0x25U-1U)   /* DMAMUX1 ATIM2 CH4 request        */
#define DMAMUX1_REQUEST_ATIM2_TRIG       ((uint16_t)0x26U-1U)   /* DMAMUX1 ATIM2 TRIG request       */
#define DMAMUX1_REQUEST_ATIM2_COM        ((uint16_t)0x27U-1U)   /* DMAMUX1 ATIM2 COM request        */
#define DMAMUX1_REQUEST_ATIM3_UP         ((uint16_t)0x28U-1U)   /* DMAMUX1 ATIM3 UP request         */
#define DMAMUX1_REQUEST_ATIM3_CH1        ((uint16_t)0x29U-1U)   /* DMAMUX1 ATIM3 CH1 request        */
#define DMAMUX1_REQUEST_ATIM3_CH2        ((uint16_t)0x2AU-1U)   /* DMAMUX1 ATIM3 CH2 request        */
#define DMAMUX1_REQUEST_ATIM3_CH3        ((uint16_t)0x2BU-1U)   /* DMAMUX1 ATIM3 CH3 request        */
#define DMAMUX1_REQUEST_ATIM3_CH4        ((uint16_t)0x2CU-1U)   /* DMAMUX1 ATIM3 CH4 request        */
#define DMAMUX1_REQUEST_ATIM3_TRIG       ((uint16_t)0x2DU-1U)   /* DMAMUX1 ATIM3 TRIG request       */
#define DMAMUX1_REQUEST_ATIM3_COM        ((uint16_t)0x2EU-1U)   /* DMAMUX1 ATIM1 COM request        */
#define DMAMUX1_REQUEST_ATIM4_UP         ((uint16_t)0x2FU-1U)   /* DMAMUX1 ATIM4 UP request         */
#define DMAMUX1_REQUEST_ATIM4_CH1        ((uint16_t)0x30U-1U)   /* DMAMUX1 ATIM4 CH1 request        */
#define DMAMUX1_REQUEST_ATIM4_CH2        ((uint16_t)0x31U-1U)   /* DMAMUX1 ATIM4 CH2 request        */
#define DMAMUX1_REQUEST_ATIM4_CH3        ((uint16_t)0x32U-1U)   /* DMAMUX1 ATIM4 CH3 request        */
#define DMAMUX1_REQUEST_ATIM4_CH4        ((uint16_t)0x33U-1U)   /* DMAMUX1 ATIM4 CH4 request        */
#define DMAMUX1_REQUEST_ATIM4_TRIG       ((uint16_t)0x34U-1U)   /* DMAMUX1 ATIM4 TRIG request       */
#define DMAMUX1_REQUEST_ATIM4_COM        ((uint16_t)0x35U-1U)   /* DMAMUX1 ATIM1 COM request        */
//GTIM 54-113
#define DMAMUX1_REQUEST_GTIMA1_CH1      ((uint16_t)0x36U-1U)   /* DMAMUX1 GTIMA1 CH1 request     */
#define DMAMUX1_REQUEST_GTIMA1_CH2      ((uint16_t)0x37U-1U)   /* DMAMUX1 GTIMA1 CH2 request     */
#define DMAMUX1_REQUEST_GTIMA1_CH3      ((uint16_t)0x38U-1U)   /* DMAMUX1 GTIMA1 CH3 request     */
#define DMAMUX1_REQUEST_GTIMA1_CH4      ((uint16_t)0x39U-1U)   /* DMAMUX1 GTIMA1 CH4 request     */
#define DMAMUX1_REQUEST_GTIMA1_TRIG     ((uint16_t)0x3AU-1U)   /* DMAMUX1 GTIMA1 TRIG request    */
#define DMAMUX1_REQUEST_GTIMA1_UP       ((uint16_t)0x3BU-1U)   /* DMAMUX1 GTIMA1 UP request      */
#define DMAMUX1_REQUEST_GTIMA2_CH1      ((uint16_t)0x3CU-1U)   /* DMAMUX1 GTIMA2 CH1 request     */
#define DMAMUX1_REQUEST_GTIMA2_CH2      ((uint16_t)0x3DU-1U)   /* DMAMUX1 GTIMA2 CH2 request     */
#define DMAMUX1_REQUEST_GTIMA2_CH3      ((uint16_t)0x3EU-1U)   /* DMAMUX1 GTIMA2 CH3 request     */
#define DMAMUX1_REQUEST_GTIMA2_CH4      ((uint16_t)0x3FU-1U)   /* DMAMUX1 GTIMA2 CH4 request     */
#define DMAMUX1_REQUEST_GTIMA2_TRIG     ((uint16_t)0x40U-1U)   /* DMAMUX1 GTIMA2 TRIG request    */
#define DMAMUX1_REQUEST_GTIMA2_UP       ((uint16_t)0x41U-1U)   /* DMAMUX1 GTIMA2 UP request      */
#define DMAMUX1_REQUEST_GTIMA3_CH1      ((uint16_t)0x42U-1U)   /* DMAMUX1 GTIMA3 CH1 request     */
#define DMAMUX1_REQUEST_GTIMA3_CH2      ((uint16_t)0x43U-1U)   /* DMAMUX1 GTIMA3 CH2 request     */
#define DMAMUX1_REQUEST_GTIMA3_CH3      ((uint16_t)0x44U-1U)   /* DMAMUX1 GTIMA3 CH3 request     */
#define DMAMUX1_REQUEST_GTIMA3_CH4      ((uint16_t)0x45U-1U)   /* DMAMUX1 GTIMA3 CH4 request     */
#define DMAMUX1_REQUEST_GTIMA3_TRIG     ((uint16_t)0x46U-1U)   /* DMAMUX1 GTIMA3 TRIG request    */
#define DMAMUX1_REQUEST_GTIMA3_UP       ((uint16_t)0x47U-1U)   /* DMAMUX1 GTIMA3 UP request      */
#define DMAMUX1_REQUEST_GTIMA4_CH1      ((uint16_t)0x48U-1U)   /* DMAMUX1 GTIMA4 CH1 request     */
#define DMAMUX1_REQUEST_GTIMA4_CH2      ((uint16_t)0x49U-1U)   /* DMAMUX1 GTIMA4 CH2 request     */
#define DMAMUX1_REQUEST_GTIMA4_CH3      ((uint16_t)0x4AU-1U)   /* DMAMUX1 GTIMA4 CH3 request     */
#define DMAMUX1_REQUEST_GTIMA4_CH4      ((uint16_t)0x4BU-1U)   /* DMAMUX1 GTIMA4 CH4 request     */
#define DMAMUX1_REQUEST_GTIMA4_TRIG     ((uint16_t)0x4CU-1U)   /* DMAMUX1 GTIMA4 TRIG request    */
#define DMAMUX1_REQUEST_GTIMA4_UP       ((uint16_t)0x4DU-1U)   /* DMAMUX1 GTIMA4 UP request      */
#define DMAMUX1_REQUEST_GTIMA5_CH1      ((uint16_t)0x4EU-1U)   /* DMAMUX1 GTIMA5 CH1 request     */
#define DMAMUX1_REQUEST_GTIMA5_CH2      ((uint16_t)0x4FU-1U)   /* DMAMUX1 GTIMA5 CH2 request     */
#define DMAMUX1_REQUEST_GTIMA5_CH3      ((uint16_t)0x50U-1U)   /* DMAMUX1 GTIMA5 CH3 request     */
#define DMAMUX1_REQUEST_GTIMA5_CH4      ((uint16_t)0x51U-1U)   /* DMAMUX1 GTIMA5 CH4 request     */
#define DMAMUX1_REQUEST_GTIMA5_TRIG     ((uint16_t)0x52U-1U)   /* DMAMUX1 GTIMA5 TRIG request    */
#define DMAMUX1_REQUEST_GTIMA5_UP       ((uint16_t)0x53U-1U)   /* DMAMUX1 GTIMA5 UP request      */
#define DMAMUX1_REQUEST_GTIMA6_CH1      ((uint16_t)0x54U-1U)   /* DMAMUX1 GTIMA6 CH1 request     */
#define DMAMUX1_REQUEST_GTIMA6_CH2      ((uint16_t)0x55U-1U)   /* DMAMUX1 GTIMA6 CH2 request     */
#define DMAMUX1_REQUEST_GTIMA6_CH3      ((uint16_t)0x56U-1U)   /* DMAMUX1 GTIMA6 CH3 request     */
#define DMAMUX1_REQUEST_GTIMA6_CH4      ((uint16_t)0x57U-1U)   /* DMAMUX1 GTIMA6 CH4 request     */
#define DMAMUX1_REQUEST_GTIMA6_TRIG     ((uint16_t)0x58U-1U)   /* DMAMUX1 GTIMA6 TRIG request    */
#define DMAMUX1_REQUEST_GTIMA6_UP       ((uint16_t)0x59U-1U)   /* DMAMUX1 GTIMA6 UP request      */
#define DMAMUX1_REQUEST_GTIMA7_CH1      ((uint16_t)0x5AU-1U)   /* DMAMUX1 GTIMA7 CH1 request     */
#define DMAMUX1_REQUEST_GTIMA7_CH2      ((uint16_t)0x5BU-1U)   /* DMAMUX1 GTIMA7 CH2 request     */
#define DMAMUX1_REQUEST_GTIMA7_CH3      ((uint16_t)0x5CU-1U)   /* DMAMUX1 GTIMA7 CH3 request     */
#define DMAMUX1_REQUEST_GTIMA7_CH4      ((uint16_t)0x5DU-1U)   /* DMAMUX1 GTIMA7 CH4 request     */
#define DMAMUX1_REQUEST_GTIMA7_TRIG     ((uint16_t)0x5EU-1U)   /* DMAMUX1 GTIMA7 TRIG request    */
#define DMAMUX1_REQUEST_GTIMA7_UP       ((uint16_t)0x5FU-1U)   /* DMAMUX1 GTIMA7 UP request      */
#define DMAMUX1_REQUEST_GTIMB1_CH1      ((uint16_t)0x60U-1U)   /* DMAMUX1 GTIMB1 CH1 request     */
#define DMAMUX1_REQUEST_GTIMB1_CH2      ((uint16_t)0x61U-1U)   /* DMAMUX1 GTIMB1 CH2 request     */
#define DMAMUX1_REQUEST_GTIMB1_CH3      ((uint16_t)0x62U-1U)   /* DMAMUX1 GTIMB1 CH3 request     */
#define DMAMUX1_REQUEST_GTIMB1_CH4      ((uint16_t)0x63U-1U)   /* DMAMUX1 GTIMB1 CH4 request     */
#define DMAMUX1_REQUEST_GTIMB1_TRIG     ((uint16_t)0x64U-1U)   /* DMAMUX1 GTIMB1 TRIG request    */
#define DMAMUX1_REQUEST_GTIMB1_UP       ((uint16_t)0x65U-1U)   /* DMAMUX1 GTIMB1 UP request      */
#define DMAMUX1_REQUEST_GTIMB2_CH1      ((uint16_t)0x66U-1U)   /* DMAMUX1 GTIMB2 CH1 request     */
#define DMAMUX1_REQUEST_GTIMB2_CH2      ((uint16_t)0x67U-1U)   /* DMAMUX1 GTIMB2 CH2 request     */
#define DMAMUX1_REQUEST_GTIMB2_CH3      ((uint16_t)0x68U-1U)   /* DMAMUX1 GTIMB2 CH3 request     */
#define DMAMUX1_REQUEST_GTIMB2_CH4      ((uint16_t)0x69U-1U)   /* DMAMUX1 GTIMB2 CH4 request     */
#define DMAMUX1_REQUEST_GTIMB2_TRIG     ((uint16_t)0x6AU-1U)   /* DMAMUX1 GTIMB2 TRIG request    */
#define DMAMUX1_REQUEST_GTIMB2_UP       ((uint16_t)0x6BU-1U)   /* DMAMUX1 GTIMB2 UP request      */
#define DMAMUX1_REQUEST_GTIMB3_CH1      ((uint16_t)0x6CU-1U)   /* DMAMUX1 GTIMB3 CH1 request     */
#define DMAMUX1_REQUEST_GTIMB3_CH2      ((uint16_t)0x6DU-1U)   /* DMAMUX1 GTIMB3 CH2 request     */
#define DMAMUX1_REQUEST_GTIMB3_CH3      ((uint16_t)0x6EU-1U)   /* DMAMUX1 GTIMB3 CH3 request     */
#define DMAMUX1_REQUEST_GTIMB3_CH4      ((uint16_t)0x6FU-1U)   /* DMAMUX1 GTIMB3 CH4 request     */
#define DMAMUX1_REQUEST_GTIMB3_TRIG     ((uint16_t)0x70U-1U)   /* DMAMUX1 GTIMB3 TRIG request    */
#define DMAMUX1_REQUEST_GTIMB3_UP       ((uint16_t)0x71U-1U)   /* DMAMUX1 GTIMB3 UP request      */
//I2C 114-133
#define DMAMUX1_REQUEST_I2C1_RX         ((uint16_t)0x72U-1U)   /* DMAMUX1 I2C1 RX request        */
#define DMAMUX1_REQUEST_I2C1_TX         ((uint16_t)0x73U-1U)   /* DMAMUX1 I2C1 TX request        */
#define DMAMUX1_REQUEST_I2C2_RX         ((uint16_t)0x74U-1U)   /* DMAMUX1 I2C2 RX request        */
#define DMAMUX1_REQUEST_I2C2_TX         ((uint16_t)0x75U-1U)   /* DMAMUX1 I2C2 TX request        */
#define DMAMUX1_REQUEST_I2C3_RX         ((uint16_t)0x76U-1U)   /* DMAMUX1 I2C3 RX request        */
#define DMAMUX1_REQUEST_I2C3_TX         ((uint16_t)0x77U-1U)   /* DMAMUX1 I2C3 TX request        */
#define DMAMUX1_REQUEST_I2C4_RX         ((uint16_t)0x78U-1U)   /* DMAMUX1 I2C4 RX request        */
#define DMAMUX1_REQUEST_I2C4_TX         ((uint16_t)0x79U-1U)   /* DMAMUX1 I2C4 TX request        */
#define DMAMUX1_REQUEST_I2C5_RX         ((uint16_t)0x7AU-1U)   /* DMAMUX1 I2C5 RX request        */
#define DMAMUX1_REQUEST_I2C5_TX         ((uint16_t)0x7BU-1U)   /* DMAMUX1 I2C5 TX request        */
#define DMAMUX1_REQUEST_I2C6_RX         ((uint16_t)0x7CU-1U)   /* DMAMUX1 I2C6 RX request        */
#define DMAMUX1_REQUEST_I2C6_TX         ((uint16_t)0x7DU-1U)   /* DMAMUX1 I2C6 TX request        */
#define DMAMUX1_REQUEST_I2C7_RX         ((uint16_t)0x7EU-1U)   /* DMAMUX1 I2C7 RX request        */
#define DMAMUX1_REQUEST_I2C7_TX         ((uint16_t)0x7FU-1U)   /* DMAMUX1 I2C7 TX request        */
#define DMAMUX1_REQUEST_I2C8_RX         ((uint16_t)0x80U-1U)   /* DMAMUX1 I2C8 RX request        */
#define DMAMUX1_REQUEST_I2C8_TX         ((uint16_t)0x81U-1U)   /* DMAMUX1 I2C8 TX request        */
#define DMAMUX1_REQUEST_I2C9_RX         ((uint16_t)0x82U-1U)   /* DMAMUX1 I2C9 RX request        */
#define DMAMUX1_REQUEST_I2C9_TX         ((uint16_t)0x83U-1U)   /* DMAMUX1 I2C9 TX request        */
#define DMAMUX1_REQUEST_I2C10_RX        ((uint16_t)0x84U-1U)   /* DMAMUX1 I2C10 RX request       */
#define DMAMUX1_REQUEST_I2C10_TX        ((uint16_t)0x85U-1U)   /* DMAMUX1 I2C10 TX request       */
//USART 134-149
#define DMAMUX1_REQUEST_USART1_RX        ((uint16_t)0x86U-1U)   /* DMAMUX1 USART1 RX request        */
#define DMAMUX1_REQUEST_USART1_TX        ((uint16_t)0x87U-1U)   /* DMAMUX1 USART1 TX request        */
#define DMAMUX1_REQUEST_USART2_RX        ((uint16_t)0x88U-1U)   /* DMAMUX1 USART2 RX request        */
#define DMAMUX1_REQUEST_USART2_TX        ((uint16_t)0x89U-1U)   /* DMAMUX1 USART2 TX request        */
#define DMAMUX1_REQUEST_USART3_RX        ((uint16_t)0x8AU-1U)   /* DMAMUX1 USART3 RX request        */
#define DMAMUX1_REQUEST_USART3_TX        ((uint16_t)0x8BU-1U)   /* DMAMUX1 USART3 TX request        */
#define DMAMUX1_REQUEST_USART4_RX        ((uint16_t)0x8CU-1U)   /* DMAMUX1 USART4 RX request        */
#define DMAMUX1_REQUEST_USART4_TX        ((uint16_t)0x8DU-1U)   /* DMAMUX1 USART4 TX request        */
#define DMAMUX1_REQUEST_USART5_RX        ((uint16_t)0x8EU-1U)   /* DMAMUX1 USART5 RX request        */
#define DMAMUX1_REQUEST_USART5_TX        ((uint16_t)0x8FU-1U)   /* DMAMUX1 USART5 TX request        */
#define DMAMUX1_REQUEST_USART6_RX        ((uint16_t)0x90U-1U)   /* DMAMUX1 USART6 RX request        */
#define DMAMUX1_REQUEST_USART6_TX        ((uint16_t)0x91U-1U)   /* DMAMUX1 USART6 TX request        */
#define DMAMUX1_REQUEST_USART7_RX        ((uint16_t)0x92U-1U)   /* DMAMUX1 USART7 RX request        */
#define DMAMUX1_REQUEST_USART7_TX        ((uint16_t)0x93U-1U)   /* DMAMUX1 USART7 TX request        */
#define DMAMUX1_REQUEST_USART8_RX        ((uint16_t)0x94U-1U)   /* DMAMUX1 USART8 RX request        */
#define DMAMUX1_REQUEST_USART8_TX        ((uint16_t)0x95U-1U)   /* DMAMUX1 USART8 TX request        */
//UART9-15 150-163
#define DMAMUX1_REQUEST_UART9_RX         ((uint16_t)0x96U-1U)   /* DMAMUX1 UART9 RX  request        */
#define DMAMUX1_REQUEST_UART9_TX         ((uint16_t)0x97U-1U)   /* DMAMUX1 UART9 TX  request        */
#define DMAMUX1_REQUEST_UART10_RX        ((uint16_t)0x98U-1U)   /* DMAMUX1 UART10 RX  request        */
#define DMAMUX1_REQUEST_UART10_TX        ((uint16_t)0x99U-1U)   /* DMAMUX1 UART10 TX  request        */
#define DMAMUX1_REQUEST_UART11_RX        ((uint16_t)0x9AU-1U)   /* DMAMUX1 UART11 RX  request        */
#define DMAMUX1_REQUEST_UART11_TX        ((uint16_t)0x9BU-1U)   /* DMAMUX1 UART11 TX  request        */
#define DMAMUX1_REQUEST_UART12_RX        ((uint16_t)0x9CU-1U)   /* DMAMUX1 UART12 RX  request        */
#define DMAMUX1_REQUEST_UART12_TX        ((uint16_t)0x9DU-1U)   /* DMAMUX1 UART12 TX  request        */
#define DMAMUX1_REQUEST_UART13_RX        ((uint16_t)0x9EU-1U)   /* DMAMUX1 UART13 RX  request        */
#define DMAMUX1_REQUEST_UART13_TX        ((uint16_t)0x9FU-1U)   /* DMAMUX1 UART13 TX  request        */
#define DMAMUX1_REQUEST_UART14_RX        ((uint16_t)0xA0U-1U)   /* DMAMUX1 UART14 RX  request        */
#define DMAMUX1_REQUEST_UART14_TX        ((uint16_t)0xA1U-1U)   /* DMAMUX1 UART14 TX  request        */
#define DMAMUX1_REQUEST_UART15_RX        ((uint16_t)0xA2U-1U)   /* DMAMUX1 UART15 RX  request        */
#define DMAMUX1_REQUEST_UART15_TX        ((uint16_t)0xA3U-1U)   /* DMAMUX1 UART15 TX  request        */
//SPI1-7 164-185
#define DMAMUX1_REQUEST_SPI1_RX          ((uint16_t)0xA4U-1U)   /* DMAMUX1 SPI1 RX request      */
#define DMAMUX1_REQUEST_I2S1_TX          ((uint16_t)0xA5U-1U)   /* DMAMUX1 I2S1 TX request      */
#define DMAMUX1_REQUEST_SPI2_RX          ((uint16_t)0xA6U-1U)   /* DMAMUX1 SPI2 RX request      */
#define DMAMUX1_REQUEST_I2S2_TX          ((uint16_t)0xA7U-1U)   /* DMAMUX1 I2S2 TX request      */
#define DMAMUX1_REQUEST_SPI3_RX          ((uint16_t)0xA8U-1U)   /* DMAMUX1 SPI3 RX request      */
#define DMAMUX1_REQUEST_I2S3_TX          ((uint16_t)0xA9U-1U)   /* DMAMUX1 I2S3 TX request      */
#define DMAMUX1_REQUEST_SPI4_RX          ((uint16_t)0xAAU-1U)   /* DMAMUX1 SPI4 RX request      */
#define DMAMUX1_REQUEST_I2S4_TX          ((uint16_t)0xABU-1U)   /* DMAMUX1 I2S4 TX request      */
#define DMAMUX1_REQUEST_SPI5_RX          ((uint16_t)0xACU-1U)   /* DMAMUX1 SPI5 RX request      */
#define DMAMUX1_REQUEST_SPI1_TX          ((uint16_t)0xADU-1U)   /* DMAMUX1 SPI1 TX request      */
#define DMAMUX1_REQUEST_SPI6_RX          ((uint16_t)0xAEU-1U)   /* DMAMUX1 SPI6 RX request      */
#define DMAMUX1_REQUEST_SPI2_TX          ((uint16_t)0xAFU-1U)   /* DMAMUX1 SPI2 TX request      */
#define DMAMUX1_REQUEST_SPI7_RX          ((uint16_t)0xB0U-1U)   /* DMAMUX1 SPI7 RX request      */
#define DMAMUX1_REQUEST_SPI3_TX          ((uint16_t)0xB1U-1U)   /* DMAMUX1 SPI3 TX request      */
#define DMAMUX1_REQUEST_I2S1_RX          ((uint16_t)0xB2U-1U)   /* DMAMUX1 I2S1 RX request      */
#define DMAMUX1_REQUEST_SPI4_TX          ((uint16_t)0xB3U-1U)   /* DMAMUX1 SPI4 TX request      */
#define DMAMUX1_REQUEST_I2S2_RX          ((uint16_t)0xB4U-1U)   /* DMAMUX1 I2S2 RX request      */
#define DMAMUX1_REQUEST_SPI5_TX          ((uint16_t)0xB5U-1U)   /* DMAMUX1 SPI5 TX request      */
#define DMAMUX1_REQUEST_I2S3_RX          ((uint16_t)0xB6U-1U)   /* DMAMUX1 I2S3 RX request      */
#define DMAMUX1_REQUEST_SPI6_TX          ((uint16_t)0xB7U-1U)   /* DMAMUX1 SPI6 TX request      */
#define DMAMUX1_REQUEST_I2S4_RX          ((uint16_t)0xB8U-1U)   /* DMAMUX1 I2S4 RX request      */
#define DMAMUX1_REQUEST_SPI7_TX          ((uint16_t)0xB9U-1U)   /* DMAMUX1 SPI7 TX request      */
//LPUART 1-2
#define DMAMUX1_REQUEST_LPUART1_RX       ((uint16_t)0xBAU-1U)   /* DMAMUX1 LPUART1 RX request   */
#define DMAMUX1_REQUEST_LPUART1_TX       ((uint16_t)0xBBU-1U)   /* DMAMUX1 LPUART1 RX request   */
#define DMAMUX1_REQUEST_LPUART2_RX       ((uint16_t)0xBCU-1U)   /* DMAMUX1 LPUART2 RX request   */
#define DMAMUX1_REQUEST_LPUART2_TX       ((uint16_t)0xBDU-1U)   /* DMAMUX1 LPUART2 RX request   */
//DAC1-2 190-191
#define DMAMUX1_REQUEST_DAC1             ((uint16_t)0xBEU-1U)   /* DMAMUX1 DAC1 request         */
#define DMAMUX1_REQUEST_DAC2             ((uint16_t)0xBFU-1U)   /* DMAMUX1 DAC2 request         */
//DSMU  192-195   
#define DMAMUX1_REQUEST_DSMU_CH1         ((uint16_t)0xC0U-1U)  /* DMAMUX1 DSMU1 request         */
#define DMAMUX1_REQUEST_DSMU_CH2         ((uint16_t)0xC1U-1U)  /* DMAMUX1 DSMU2 request         */
#define DMAMUX1_REQUEST_DSMU_CH3         ((uint16_t)0xC2U-1U)  /* DMAMUX1 DSMU3 request         */
#define DMAMUX1_REQUEST_DSMU_CH4         ((uint16_t)0xC3U-1U)  /* DMAMUX1 DSMU4 request         */
//CANFD 1-2 196-203
#define DMAMUX1_REQUEST_CANFD1           ((uint16_t)0xC4U-1U)  /* DMAMUX1 CANFD1 request      */
#define DMAMUX1_REQUEST_CANFD2           ((uint16_t)0xC5U-1U)  /* DMAMUX1 CANFD2 request      */
#define DMAMUX1_REQUEST_CANFD3           ((uint16_t)0xC6U-1U)  /* DMAMUX1 CANFD3 request      */
#define DMAMUX1_REQUEST_CANFD4           ((uint16_t)0xC7U-1U)  /* DMAMUX1 CANFD4 request      */
#define DMAMUX1_REQUEST_CANFD5           ((uint16_t)0xC8U-1U)  /* DMAMUX1 CANFD5 request      */
#define DMAMUX1_REQUEST_CANFD6           ((uint16_t)0xC9U-1U)  /* DMAMUX1 CANFD6 request      */
#define DMAMUX1_REQUEST_CANFD7           ((uint16_t)0xCAU-1U)  /* DMAMUX1 CANFD7 request      */
#define DMAMUX1_REQUEST_CANFD8           ((uint16_t)0xCBU-1U)  /* DMAMUX1 CANFD8 request      */
//CORDIC 204-205
#define DMAMUX1_REQUEST_CORDIC_READ      ((uint16_t)0xCCU-1U)  /* DMAMUX1 CORDIC Read request  */
#define DMAMUX1_REQUEST_CORDIC_WRITE     ((uint16_t)0xCDU-1U)  /* DMAMUX1 CORDIC Write request */
//CORDIC 206-207
#define DMAMUX1_REQUEST_FMAC_READ        ((uint16_t)0xCEU-1U)  /* DMAMUX1 FMAC Read request    */
#define DMAMUX1_REQUEST_FMAC_WRITE       ((uint16_t)0xCFU-1U)  /* DMAMUX1 FMAC Write request   */
//BTIM1-4 208-211UEST
#define DMAMUX1_REQUEST_BTIM1            ((uint16_t)0xD0U-1U)  /* DMAMUX1 BTIM1 request        */
#define DMAMUX1_REQUEST_BTIM2            ((uint16_t)0xD1U-1U)  /* DMAMUX1 BTIM2 request        */
#define DMAMUX1_REQUEST_BTIM3            ((uint16_t)0xD2U-1U)  /* DMAMUX1 BTIM3 request        */
#define DMAMUX1_REQUEST_BTIM4            ((uint16_t)0xD3U-1U)  /* DMAMUX1 BTIM4 request        */
//GTIMB1-3 212-214UEST
#define DMAMUX1_REQUEST_GTIMB1_COM     ((uint16_t)0xD4U-1U)  /* DMAMUX1 GTIMB1 COM request   */
#define DMAMUX1_REQUEST_GTIMB2_COM     ((uint16_t)0xD5U-1U)  /* DMAMUX1 GTIMB2 COM request   */
#define DMAMUX1_REQUEST_GTIMB3_COM     ((uint16_t)0xD6U-1U)  /* DMAMUX1 GTIMB3 COM request   */
//DAC3-6 215-218
#define DMAMUX1_REQUEST_DAC3             ((uint16_t)0xB7U-1U)   /* DMAMUX1 DAC3 request         */
#define DMAMUX1_REQUEST_DAC4             ((uint16_t)0xB8U-1U)   /* DMAMUX1 DAC4 request         */
#define DMAMUX1_REQUEST_DAC5             ((uint16_t)0xB9U-1U)   /* DMAMUX1 DAC5 request         */
#define DMAMUX1_REQUEST_DAC6             ((uint16_t)0xBAU-1U)   /* DMAMUX1 DAC6 request         */


/* DMAMUX_2 requests */
#define DMAMUX2_REQUEST_GENERATOR0       ((uint16_t)0x01U-1U)  /* DMAMUX2 request generator 0      */
#define DMAMUX2_REQUEST_GENERATOR1       ((uint16_t)0x02U-1U)  /* DMAMUX2 request generator 1      */
#define DMAMUX2_REQUEST_GENERATOR2       ((uint16_t)0x03U-1U)  /* DMAMUX2 request generator 2      */
#define DMAMUX2_REQUEST_GENERATOR3       ((uint16_t)0x04U-1U)  /* DMAMUX2 request generator 3      */
#define DMAMUX2_REQUEST_GENERATOR4       ((uint16_t)0x05U-1U)  /* DMAMUX2 request generator 4      */
#define DMAMUX2_REQUEST_GENERATOR5       ((uint16_t)0x06U-1U)  /* DMAMUX2 request generator 5      */
#define DMAMUX2_REQUEST_GENERATOR6       ((uint16_t)0x07U-1U)  /* DMAMUX2 request generator 6      */
#define DMAMUX2_REQUEST_GENERATOR7       ((uint16_t)0x08U-1U)  /* DMAMUX2 request generator 7      */
#define DMAMUX2_REQUEST_GENERATOR8       ((uint16_t)0x09U-1U)  /* DMAMUX2 request generator 8      */
#define DMAMUX2_REQUEST_GENERATOR9       ((uint16_t)0x0AU-1U)  /* DMAMUX2 request generator 9      */
#define DMAMUX2_REQUEST_GENERATOR10      ((uint16_t)0x0BU-1U)  /* DMAMUX2 request generator 10     */
#define DMAMUX2_REQUEST_GENERATOR11      ((uint16_t)0x0CU-1U)  /* DMAMUX2 request generator 11     */
#define DMAMUX2_REQUEST_GENERATOR12      ((uint16_t)0x0DU-1U)  /* DMAMUX2 request generator 12     */
#define DMAMUX2_REQUEST_GENERATOR13      ((uint16_t)0x0EU-1U)  /* DMAMUX2 request generator 13     */
#define DMAMUX2_REQUEST_GENERATOR14      ((uint16_t)0x0FU-1U)  /* DMAMUX2 request generator 14     */
#define DMAMUX2_REQUEST_GENERATOR15      ((uint16_t)0x10U-1U)  /* DMAMUX2 request generator 15     */
//xSPI1-2 1-4
#define DMAMUX2_REQUEST_REQ_XSPI1_RX     ((uint16_t)0x19U-1U)  /* DMAMUX2 XSPI1 RX request         */
#define DMAMUX2_REQUEST_REQ_XSPI1_TX     ((uint16_t)0x1AU-1U)  /* DMAMUX2 XSPI1 TX request         */
#define DMAMUX2_REQUEST_REQ_XSPI2_RX     ((uint16_t)0x1BU-1U)  /* DMAMUX2 XSPI2 RX request         */
#define DMAMUX2_REQUEST_REQ_XSPI2_TX     ((uint16_t)0x1CU-1U)  /* DMAMUX2 XSPI2 TX request         */

#define DMAMUX_SYNC_ID_MASK              (DMAMUX_CHxCTRL_SYID_MASK)
/** DMAMUX_SYNC_EVT Synchronization Signal Event */
#define DMAMUX1_SYNC_DMAMUX1_EVT0_7      ((uint32_t)0x00000000U)   /* DMAMUX1 synchronization Signal is DMAMUX1 Channel0~7 Event   */
#define DMAMUX1_SYNC_DMAMUX1_EVT8_15     ((uint32_t)0x01000000U)   /* DMAMUX1 synchronization Signal is DMAMUX1 Channel8~15 Event  */
#define DMAMUX1_SYNC_DMAMUX1_EVT16_23    ((uint32_t)0x02000000U)   /* DMAMUX1 synchronization Signal is DMAMUX1 Channel16~23 Event */
#define DMAMUX1_SYNC_LPTIM5_OUT          ((uint32_t)0x03000000U)   /* DMAMUX1 synchronization Signal is LPTIM5 OUT                 */
#define DMAMUX1_SYNC_LPTIM4_OUT          ((uint32_t)0x04000000U)   /* DMAMUX1 synchronization Signal is LPTIM4 OUT                 */
#define DMAMUX1_SYNC_LPTIM3_OUT          ((uint32_t)0x05000000U)   /* DMAMUX1 synchronization Signal is LPTIM3 OUT                 */
#define DMAMUX1_SYNC_LPTIM2_OUT          ((uint32_t)0x06000000U)   /* DMAMUX1 synchronization Signal is LPTIM2 OUT                 */
#define DMAMUX1_SYNC_LPTIM1_OUT          ((uint32_t)0x07000000U)   /* DMAMUX1 synchronization Signal is LPTIM1 OUT                 */
#define DMAMUX1_SYNC_EXTI0               ((uint32_t)0x08000000U)   /* DMAMUX1 synchronization Signal is EXTI0 IT                   */
#define DMAMUX2_SYNC_INTERNAL_USED       ((uint32_t)0x00000000U)   /* DMAMUX2 synchronization Signal is Internal used or unused    */


#define DMAMUX_REQ_NUMBER_MASK           (DMAMUX_CHxCTRL_NUMREQ_MASK)
#define DMAMUX_REQ_NUMBER_Pos            (19U)

/** DMAMUX Synchronization Signal Polarity*/
#define DMAMUX_SYNC_POL_MASK            (DMAMUX_CHxCTRL_SYPOL_MASK)                        
#define DMAMUX_SYNC_NO_EVENT            (0x00000000U)                                       /* All requests are blocked                            */
#define DMAMUX_SYNC_POL_RISING          (DMAMUX_CHxCTRL_SYPOL_0)                            /* Synchronization on event on rising edge             */
#define DMAMUX_SYNC_POL_FALLING         (DMAMUX_CHxCTRL_SYPOL_1)                            /* Synchronization on event on falling edge            */
#define DMAMUX_SYNC_POL_RISING_FALLING  (DMAMUX_CHxCTRL_SYPOL_0 | DMAMUX_CHxCTRL_SYPOL_1)   /* Synchronization on event on rising and falling edge */

#define DMAMUX_EVENT_GEN_MASK           (DMAMUX_CHxCTRL_EVEGEN)
#define DMAMUX_SYN_ENABLE_MASK          (DMAMUX_CHxCTRL_SYEN)
#define DMAMUX_SYNOVERRUN_INTEN_MASK    (DMAMUX_CHxCTRL_SOIEN)

#define DMAMUX_GEN_ENABLE_MASK          (DMAMUX_CHxCFG_GEN)

/** DMAMUX_REQUEST_GENERATOR Request Generator Channel */
#define DMAMUX_REQ_GEN_0                (0x00000000U)
#define DMAMUX_REQ_GEN_1                (0x00000001U)
#define DMAMUX_REQ_GEN_2                (0x00000002U)
#define DMAMUX_REQ_GEN_3                (0x00000003U)
#define DMAMUX_REQ_GEN_4                (0x00000004U)
#define DMAMUX_REQ_GEN_5                (0x00000005U)
#define DMAMUX_REQ_GEN_6                (0x00000006U)
#define DMAMUX_REQ_GEN_7                (0x00000007U)
#define DMAMUX_REQ_GEN_8                (0x00000008U)
#define DMAMUX_REQ_GEN_9                (0x00000009U)
#define DMAMUX_REQ_GEN_10               (0x0000000AU)
#define DMAMUX_REQ_GEN_11               (0x0000000BU)
#define DMAMUX_REQ_GEN_12               (0x0000000CU)
#define DMAMUX_REQ_GEN_13               (0x0000000DU)
#define DMAMUX_REQ_GEN_14               (0x0000000EU)
#define DMAMUX_REQ_GEN_15               (0x0000000FU)

/** DMAMUX_REQUEST_GEN_POLARITY External Request Signal Generation Polarity  */
#define DMAMUX_REQ_GEN_POL_MASK           (DMAMUX_CHxCFG_GPOL_MASK) 
#define DMAMUX_REQ_GEN_NO_EVENT           (0x00000000U)                                 /* No external DMA request  generation                        */
#define DMAMUX_REQ_GEN_POL_RISING         (DMAMUX_CHxCFG_GPOL_0)                        /* External DMA request generation on event on rising edge    */
#define DMAMUX_REQ_GEN_POL_FALLING        (DMAMUX_CHxCFG_GPOL_1)                        /* External DMA request generation on event on falling edge   */
#define DMAMUX_REQ_GEN_POL_RISING_FALLING (DMAMUX_CHxCFG_GPOL_0 | DMAMUX_CHxCFG_GPOL_1) /* External DMA request generation on rising and falling edge */

#define DMAMUX_REQ_GEN_NUMBER_MASK        (DMAMUX_CHxCFG_GNUMREQ_MASK)
#define DMAMUX_REQ_GEN_NUMBER_Pos         (19U)

#define DMAMUX_TRIGOVERRUN_INTEN_MASK     (DMAMUX_CHxCFG_TOVIEN)

#define DMAMUX_REQ_GEN_SIG_ID_MASK        (DMAMUX_CHxCFG_SYID_MASK)

/** DMAMUX1 External Request Signal Generation */
#define DMAMUX1_REQ_GEN_DMAMUX1_EVT0_EVT7             ((uint32_t)0x00000001U-1U)   /*  DMAMUX1 Request generator Signal is DMAMUX1 Channel0-7 Event         */
#define DMAMUX1_REQ_GEN_DMAMUX1_EVT8_EVT5             ((uint32_t)0x00000002U-1U)   /*  DMAMUX1 Request generator Signal is DMAMUX1 Channel8_15 Event         */
#define DMAMUX1_REQ_GEN_DMAMUX1_EVT16_EVT23           ((uint32_t)0x00000003U-1U)   /*  DMAMUX1 Request generator Signal is DMAMUX1 Channel16_23 Event        */
#define DMAMUX1_REQ_GEN_LPTIM4_OUT                    ((uint32_t)0x00000004U-1U)   /*  DMAMUX1 Request generator Signal is LPTIM4 OUT                        */
#define DMAMUX1_REQ_GEN_LPTIM3_OUT                    ((uint32_t)0x00000005U-1U)   /*  DMAMUX1 Request generator Signal is LPTIM3 OUT                        */
#define DMAMUX1_REQ_GEN_LPTIM2_OUT                    ((uint32_t)0x00000006U-1U)   /*  DMAMUX1 Request generator Signal is LPTIM2 OUT                        */
#define DMAMUX1_REQ_GEN_LPTIM1_OUT                    ((uint32_t)0x00000007U-1U)   /*  DMAMUX1 Request generator Signal is LPTIM1 OUT                        */
#define DMAMUX1_REQ_GEN_EXTI0                         ((uint32_t)0x00000008U-1U)   /*  DMAMUX1 Request generator Signal is EXTI0 IT                          */
#define DMAMUX1_REQ_GEN_CANFD1_INT0                   ((uint32_t)0x00000009U-1U)   /*  DMAMUX1 Request generator Signal is CANFD1 golgal interrupt 0         */
#define DMAMUX1_REQ_GEN_CANFD2_INT0                   ((uint32_t)0x0000000AU-1U)   /*  DMAMUX1 Request generator Signal is CANFD2 golgal interrupt 0         */
#define DMAMUX1_REQ_GEN_CANFD3_INT0                   ((uint32_t)0x0000000BU-1U)   /*  DMAMUX1 Request generator Signal is CANFD3 golgal interrupt 0         */
#define DMAMUX1_REQ_GEN_CANFD4_INT0                   ((uint32_t)0x0000000CU-1U)   /*  DMAMUX1 Request generator Signal is CANFD4 golgal interrupt 0         */
#define DMAMUX1_REQ_GEN_CANFD5_INT0                   ((uint32_t)0x0000000DU-1U)   /*  DMAMUX1 Request generator Signal is CANFD5 golgal interrupt 0         */
#define DMAMUX1_REQ_GEN_CANFD6_INT0                   ((uint32_t)0x0000000EU-1U)   /*  DMAMUX1 Request generator Signal is CANFD6 golgal interrupt 0         */
#define DMAMUX1_REQ_GEN_CANFD7_INT0                   ((uint32_t)0x0000000FU-1U)   /*  DMAMUX1 Request generator Signal is CANFD7 golgal interrupt 0         */
#define DMAMUX1_REQ_GEN_CANFD8_INT0                   ((uint32_t)0x00000010U-1U)   /*  DMAMUX1 Request generator Signal is CANFD8 golgal interrupt 0         */
#define DMAMUX1_REQ_GEN_LPTIM5_OUT                    ((uint32_t)0x00000011U-1U)   /*  DMAMUX1 Request generator Signal is LPTIM4 OUT                        */
#define DMAMUX1_REQ_GEN_ESC_INT                       ((uint32_t)0x00000012U-1U)   /*  DMAMUX1 Request generator Signal is ESC golgal interrupt              */
#define DMAMUX1_REQ_GEN_CANFD1_INT1                   ((uint32_t)0x00000013U-1U)   /*  DMAMUX1 Request generator Signal is CANFD1 golgal interrupt 1         */
#define DMAMUX1_REQ_GEN_CANFD2_INT1                   ((uint32_t)0x00000014U-1U)   /*  DMAMUX1 Request generator Signal is CANFD2 golgal interrupt 1         */
#define DMAMUX1_REQ_GEN_CANFD3_INT1                   ((uint32_t)0x00000015U-1U)   /*  DMAMUX1 Request generator Signal is CANFD3 golgal interrupt 1         */
#define DMAMUX1_REQ_GEN_CANFD4_INT1                   ((uint32_t)0x00000016U-1U)   /*  DMAMUX1 Request generator Signal is CANFD4 golgal interrupt 1         */
#define DMAMUX1_REQ_GEN_CANFD5_INT1                   ((uint32_t)0x00000017U-1U)   /*  DMAMUX1 Request generator Signal is CANFD5 golgal interrupt 1         */
#define DMAMUX1_REQ_GEN_CANFD6_INT1                   ((uint32_t)0x00000018U-1U)   /*  DMAMUX1 Request generator Signal is CANFD6 golgal interrupt 1         */
#define DMAMUX1_REQ_GEN_CANFD7_INT1                   ((uint32_t)0x00000019U-1U)   /*  DMAMUX1 Request generator Signal is CANFD7 golgal interrupt 1         */
#define DMAMUX1_REQ_GEN_CANFD8_INT1                   ((uint32_t)0x0000001AU-1U)   /*  DMAMUX1 Request generator Signal is CANFD8 golgal interrupt 1         */
/** DMAMUX2 External Request Signal Generation */
#define DMAMUX2_DMA1_CH0_TC_INT                       ((uint32_t)0x00000001U-1U)    /*  DMAMUX2 Request generator Signal is DMA1 Channel0 Transfer complete inttrupt   */
#define DMAMUX2_DMA1_CH1_TC_INT                       ((uint32_t)0x00000002U-1U)    /*  DMAMUX2 Request generator Signal is DMA1 Channel1 Transfer complete inttrupt   */
#define DMAMUX2_DMA1_CH2_TC_INT                       ((uint32_t)0x00000003U-1U)    /*  DMAMUX2 Request generator Signal is DMA1 Channel2 Transfer complete inttrupt   */
#define DMAMUX2_DMA1_CH3_TC_INT                       ((uint32_t)0x00000004U-1U)    /*  DMAMUX2 Request generator Signal is DMA1 Channel3 Transfer complete inttrupt   */
#define DMAMUX2_DMA1_CH4_TC_INT                       ((uint32_t)0x00000005U-1U)    /*  DMAMUX2 Request generator Signal is DMA1 Channel4 Transfer complete inttrupt   */
#define DMAMUX2_DMA1_CH5_TC_INT                       ((uint32_t)0x00000006U-1U)    /*  DMAMUX2 Request generator Signal is DMA1 Channel5 Transfer complete inttrupt   */
#define DMAMUX2_DMA1_CH6_TC_INT                       ((uint32_t)0x00000007U-1U)    /*  DMAMUX2 Request generator Signal is DMA1 Channel6 Transfer complete inttrupt   */
#define DMAMUX2_DMA1_CH7_TC_INT                       ((uint32_t)0x00000008U-1U)    /*  DMAMUX2 Request generator Signal is DMA1 Channel7 Transfer complete inttrupt   */
#define DMAMUX2_DMA2_CH0_TC_INT                       ((uint32_t)0x00000009U-1U)    /*  DMAMUX2 Request generator Signal is DMA2 Channel0 Transfer complete inttrupt   */
#define DMAMUX2_DMA2_CH1_TC_INT                       ((uint32_t)0x0000000AU-1U)    /*  DMAMUX2 Request generator Signal is DMA2 Channel1 Transfer complete inttrupt   */
#define DMAMUX2_DMA2_CH2_TC_INT                       ((uint32_t)0x0000000BU-1U)    /*  DMAMUX2 Request generator Signal is DMA2 Channel2 Transfer complete inttrupt   */
#define DMAMUX2_DMA2_CH3_TC_INT                       ((uint32_t)0x0000000CU-1U)    /*  DMAMUX2 Request generator Signal is DMA2 Channel3 Transfer complete inttrupt   */
#define DMAMUX2_DMA2_CH4_TC_INT                       ((uint32_t)0x0000000DU-1U)    /*  DMAMUX2 Request generator Signal is DMA2 Channel4 Transfer complete inttrupt   */
#define DMAMUX2_DMA2_CH5_TC_INT                       ((uint32_t)0x0000000EU-1U)    /*  DMAMUX2 Request generator Signal is DMA2 Channel5 Transfer complete inttrupt   */
#define DMAMUX2_DMA2_CH6_TC_INT                       ((uint32_t)0x0000000FU-1U)    /*  DMAMUX2 Request generator Signal is DMA2 Channel6 Transfer complete inttrupt   */
#define DMAMUX2_DMA2_CH7_TC_INT                       ((uint32_t)0x00000010U-1U)    /*  DMAMUX2 Request generator Signal is DMA2 Channel7 Transfer complete inttrupt   */
#define DMAMUX2_DMA3_CH0_TC_INT                       ((uint32_t)0x00000011U-1U)    /*  DMAMUX2 Request generator Signal is DMA3 Channel0 Transfer complete inttrupt   */
#define DMAMUX2_DMA3_CH1_TC_INT                       ((uint32_t)0x00000012U-1U)    /*  DMAMUX2 Request generator Signal is DMA3 Channel1 Transfer complete inttrupt   */
#define DMAMUX2_DMA3_CH2_TC_INT                       ((uint32_t)0x00000013U-1U)    /*  DMAMUX2 Request generator Signal is DMA3 Channel2 Transfer complete inttrupt   */
#define DMAMUX2_DMA3_CH3_TC_INT                       ((uint32_t)0x00000014U-1U)    /*  DMAMUX2 Request generator Signal is DMA3 Channel3 Transfer complete inttrupt   */
#define DMAMUX2_DMA3_CH4_TC_INT                       ((uint32_t)0x00000015U-1U)    /*  DMAMUX2 Request generator Signal is DMA3 Channel4 Transfer complete inttrupt   */
#define DMAMUX2_DMA3_CH5_TC_INT                       ((uint32_t)0x00000016U-1U)    /*  DMAMUX2 Request generator Signal is DMA3 Channel5 Transfer complete inttrupt   */
#define DMAMUX2_DMA3_CH6_TC_INT                       ((uint32_t)0x00000017U-1U)    /*  DMAMUX2 Request generator Signal is DMA3 Channel6 Transfer complete inttrupt   */
#define DMAMUX2_DMA3_CH7_TC_INT                       ((uint32_t)0x00000018U-1U)    /*  DMAMUX2 Request generator Signal is DMA3 Channel7 Transfer complete inttrupt   */
#define DMAMUX2_REQ_GEN_DMAMUX2_LCDC_INT              ((uint32_t)0x00000019U-1U)    /*  DMAMUX2 Request generator Signal is LCD interrupt        */
#define DMAMUX2_REQ_GEN_DMAMUX2_GPU_INT               ((uint32_t)0x0000001AU-1U)    /*  DMAMUX2 Request generator Signal is GPU interrupt        */
#define DMAMUX2_REQ_GEN_DMAMUX2_JEPG_SGDMA_H2P_INT    ((uint32_t)0x0000001BU-1U)    /*  DMAMUX2 Request generator Signal is JEPG_SGDMA_H2P interrupt        */
#define DMAMUX2_REQ_GEN_DMAMUX2_JEPG_SGDMA_P2H_INT    ((uint32_t)0x0000001CU-1U)    /*  DMAMUX2 Request generator Signal is JEPG_SGDMA_P2H interrupt        */
#define DMAMUX2_REQ_GEN_DMAMUX2_MIPI_INT              ((uint32_t)0x0000001DU-1U)    /*  DMAMUX2 Request generator Signal is MIPI interrupt        */
#define DMAMUX2_REQ_GEN_DMAMUX2_USB1_INT              ((uint32_t)0x0000001EU-1U)    /*  DMAMUX2 Request generator Signal is USB1 interrupt        */
#define DMAMUX2_REQ_GEN_DMAMUX2_USB2_INT              ((uint32_t)0x0000001FU-1U)    /*  DMAMUX2 Request generator Signal is USB2 interrupt        */
#define DMAMUX2_REQ_GEN_SDMMC1_INT                    ((uint32_t)0x00000020U-1U)    /*  DMAMUX2 Request generator Signal is USB2 interrupt        */
#define DMAMUX2_REQ_GEN_SDMMC2_INT                    ((uint32_t)0x00000021U-1U)    /*  DMAMUX2 Request generator Signal is USB2 interrupt        */
#define DMAMUX2_REQ_GEN_DVP1_INT                      ((uint32_t)0x00000022U-1U)    /*  DMAMUX2 Request generator Signal is USB2 interrupt        */
#define DMAMUX2_REQ_GEN_DVP2_INT                      ((uint32_t)0x00000023U-1U)    /*  DMAMUX2 Request generator Signal is USB2 interrupt        */
#define DMAMUX2_REQ_GEN_EHT1_INT                      ((uint32_t)0x00000024U-1U)    /*  DMAMUX2 Request generator Signal is USB2 interrupt        */
#define DMAMUX2_REQ_GEN_EHT2_INT                      ((uint32_t)0x00000025U-1U)    /*  DMAMUX2 Request generator Signal is USB2 interrupt        */
#define DMAMUX2_REQ_GEN_SDPU_INT                      ((uint32_t)0x00000026U-1U)    /*  DMAMUX2 Request generator Signal is USB2 interrupt        */


/* DMAMUX_CHANNEL DMAMUX Channel */
#define DMAMUX_CHANNEL_0                              ((uint32_t)0x00000000U)  /*  DMAMUX1 Channel 0  connected to DMA1 Channel 0 ,  DMAMUX_MDMA Channel 0  connected to MDMA Channel 0  */
#define DMAMUX_CHANNEL_1                              ((uint32_t)0x00000001U)  /*  DMAMUX1 Channel 1  connected to DMA1 Channel 1 ,  DMAMUX_MDMA Channel 1  connected to MDMA Channel 1  */
#define DMAMUX_CHANNEL_2                              ((uint32_t)0x00000002U)  /*  DMAMUX1 Channel 2  connected to DMA1 Channel 2 ,  DMAMUX_MDMA Channel 2  connected to MDMA Channel 2  */
#define DMAMUX_CHANNEL_3                              ((uint32_t)0x00000003U)  /*  DMAMUX1 Channel 3  connected to DMA1 Channel 3 ,  DMAMUX_MDMA Channel 3  connected to MDMA Channel 3  */
#define DMAMUX_CHANNEL_4                              ((uint32_t)0x00000004U)  /*  DMAMUX1 Channel 4  connected to DMA1 Channel 4 ,  DMAMUX_MDMA Channel 4  connected to MDMA Channel 4  */
#define DMAMUX_CHANNEL_5                              ((uint32_t)0x00000005U)  /*  DMAMUX1 Channel 5  connected to DMA1 Channel 5 ,  DMAMUX_MDMA Channel 5  connected to MDMA Channel 5  */
#define DMAMUX_CHANNEL_6                              ((uint32_t)0x00000006U)  /*  DMAMUX1 Channel 6  connected to DMA1 Channel 6 ,  DMAMUX_MDMA Channel 6  connected to MDMA Channel 6  */
#define DMAMUX_CHANNEL_7                              ((uint32_t)0x00000007U)  /*  DMAMUX1 Channel 7  connected to DMA1 Channel 7 ,  DMAMUX_MDMA Channel 7  connected to MDMA Channel 7  */
#define DMAMUX_CHANNEL_8                              ((uint32_t)0x00000008U)  /*  DMAMUX1 Channel 8  connected to DMA2 Channel 0 ,  DMAMUX_MDMA Channel 8  connected to MDMA Channel 8  */
#define DMAMUX_CHANNEL_9                              ((uint32_t)0x00000009U)  /*  DMAMUX1 Channel 9  connected to DMA2 Channel 1 ,  DMAMUX_MDMA Channel 9  connected to MDMA Channel 9  */
#define DMAMUX_CHANNEL_10                             ((uint32_t)0x0000000AU)  /*  DMAMUX1 Channel 10 connected to DMA2 Channel 2 , DMAMUX_MDMA Channel 10 connected to MDMA Channel 10 */
#define DMAMUX_CHANNEL_11                             ((uint32_t)0x0000000BU)  /*  DMAMUX1 Channel 11 connected to DMA2 Channel 3 , DMAMUX_MDMA Channel 11 connected to MDMA Channel 11 */
#define DMAMUX_CHANNEL_12                             ((uint32_t)0x0000000CU)  /*  DMAMUX1 Channel 12 connected to DMA2 Channel 4 , DMAMUX_MDMA Channel 12 connected to MDMA Channel 12 */
#define DMAMUX_CHANNEL_13                             ((uint32_t)0x0000000DU)  /*  DMAMUX1 Channel 13 connected to DMA2 Channel 5 , DMAMUX_MDMA Channel 13 connected to MDMA Channel 13 */
#define DMAMUX_CHANNEL_14                             ((uint32_t)0x0000000EU)  /*  DMAMUX1 Channel 14 connected to DMA2 Channel 6 , DMAMUX_MDMA Channel 14 connected to MDMA Channel 14 */
#define DMAMUX_CHANNEL_15                             ((uint32_t)0x0000000FU)  /*  DMAMUX1 Channel 15 connected to DMA2 Channel 7 , DMAMUX_MDMA Channel 15 connected to MDMA Channel 15 */
#define DMAMUX_CHANNEL_16                             ((uint32_t)0x00000010U)  /*  DMAMUX1 Channel 16 connected to DMA3 Channel 0 , invailed for MDMA*/
#define DMAMUX_CHANNEL_17                             ((uint32_t)0x00000011U)  /*  DMAMUX1 Channel 17 connected to DMA3 Channel 1 , invailed for MDMA */
#define DMAMUX_CHANNEL_18                             ((uint32_t)0x00000012U)  /*  DMAMUX1 Channel 18 connected to DMA3 Channel 2 , invailed for MDMA */
#define DMAMUX_CHANNEL_19                             ((uint32_t)0x00000013U)  /*  DMAMUX1 Channel 19 connected to DMA3 Channel 3 , invailed for MDMA */
#define DMAMUX_CHANNEL_20                             ((uint32_t)0x00000014U)  /*  DMAMUX1 Channel 20 connected to DMA3 Channel 4 , invailed for MDMA */
#define DMAMUX_CHANNEL_21                             ((uint32_t)0x00000015U)  /*  DMAMUX1 Channel 21 connected to DMA3 Channel 5 , invailed for MDMA */
#define DMAMUX_CHANNEL_22                             ((uint32_t)0x00000016U)  /*  DMAMUX1 Channel 22 connected to DMA3 Channel 6 , invailed for MDMA */
#define DMAMUX_CHANNEL_23                             ((uint32_t)0x00000017U)  /*  DMAMUX1 Channel 23 connected to DMA3 Channel 7 , invailed for MDMA */


void DMAMUX_DeInit(DMAMUX_ID DMAMUXx);

void DMAMUX_SetRequestID(DMAMUX_ID DMAMUXx, uint32_t Channel, uint32_t Request);
uint32_t DMAMUX_GetRequestID(DMAMUX_ID DMAMUXx, uint32_t Channel);
void DMAMUX_SetSyncID(DMAMUX_ID DMAMUXx, uint32_t Channel, uint32_t SyncID);
uint32_t DMAMUX_GetSyncID(DMAMUX_ID DMAMUXx, uint32_t Channel);
void DMAMUX_SetSyncRequestNumber(DMAMUX_ID DMAMUXx, uint32_t Channel, uint32_t RequestNumber);
uint32_t DMAMUX_GetSyncRequestNumber(DMAMUX_ID DMAMUXx, uint32_t Channel);
void DMAMUX_SetSyncPolarity(DMAMUX_ID DMAMUXx, uint32_t Channel, uint32_t Polarity);
uint32_t DMAMUX_GetSyncPolarity(DMAMUX_ID DMAMUXx, uint32_t Channel);
void DMAMUX_EnableEventGeneration(DMAMUX_ID DMAMUXx, uint32_t Channel, FunctionalState Cmd);
void DMAMUX_EnableSync(DMAMUX_ID DMAMUXx, uint32_t Channel, FunctionalState Cmd);
void DMAMUX_EnableRequestGen(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel, FunctionalState Cmd);
void DMAMUX_SetRequestGenPolarity(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel, uint32_t Polarity);
uint32_t DMAMUX_GetRequestGenPolarity(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel);
void DMAMUX_SetGenRequestNumber(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel, uint32_t RequestNumber);
uint32_t DMAMUX_GetGenRequestNumber(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel);
void DMAMUX_SetRequestSignalID(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel, uint32_t RequestSignalID);
uint32_t DMAMUX_GetRequestSignalID(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel);

void DMAMUX_EnableSynEventOverrunInt(DMAMUX_ID DMAMUXx, uint32_t Channel, FunctionalState Cmd);
void DMAMUX_EnableTrigOverrunInt(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel, FunctionalState Cmd);

FlagStatus DMAMUX_GetSynOverrunStatus(DMAMUX_ID DMAMUXx, uint32_t Channel);
FlagStatus DMAMUX_GetTrigOverrunStatus(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel);
void DMAMUX_ClearSynOverrunStatus(DMAMUX_ID DMAMUXx, uint32_t Channel);
void DMAMUX_ClearTrigOverrunStatus(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel);


#ifdef __cplusplus
}
#endif



#endif /*N32H76x_H78x_DMAMUX_H */


