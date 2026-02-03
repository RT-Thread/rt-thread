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
 * @file system_n32h76x_78x.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x.h"

#if !defined  (HSE_VALUE)
#define HSE_VALUE    ((uint32_t)8000000UL) /* Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (CSI_VALUE)
  #define CSI_VALUE           ((uint32_t)4000000UL) /* Value of the Internal oscillator in Hz*/
#endif /* CSI_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE           ((uint32_t)64000000UL) /* Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#define VECT_TAB_OFFSET       ((uint32_t)0x00000000UL) /* Vector Table base offset field.   */

#define FLASH_BANK1_BASE      (0x15000000U)

#define FLASH_BANK2_BASE      (0x15080000U)

uint32_t SystemCoreClock = 600000000;

#define TCM_SIZE_VALUE        (0x20) /*TCM_SIZE=0x20 :256 KB ITCM,256 KB DTCM,512 KB AXI_SRAM*/

/** Private_Functions  */

/* defaule power supply is extern LDO. User can change the way of power supply*/
//#define PWR_SUPPLY_SELECTION       (PWR_LDO_SUPPLY)  /* External LDO Supply  */
#define PWR_SUPPLY_SELECTION       (PWR_DIRECT_SMPS_SUPPLY)  /* DCDC Supply  */
//#define PWR_SUPPLY_SELECTION       (PWR_EXTERNAL_SOURCE_SUPPLY)  /* VCAP Supply  */

/**
 *\*\name   ConfigTcmSize.
 *\*\fun    Config TCM_SIZE
 *\*\param  tcmSizeValue : 
 *\*\           0x00 :1024KB ITCM,0   KB DTCM,0   KB AXI_SRAM
 *\*\           0x01 :896 KB ITCM,128 KB DTCM,0   KB AXI_SRAM
 *\*\           0x02 :768 KB ITCM,256 KB DTCM,0   KB AXI_SRAM
 *\*\           0x03 :640 KB ITCM,384 KB DTCM,0   KB AXI_SRAM
 *\*\           0x04 :512 KB ITCM,512 KB DTCM,0   KB AXI_SRAM
 *\*\           0x05 :384 KB ITCM,640 KB DTCM,0   KB AXI_SRAM
 *\*\           0x06 :256 KB ITCM,768 KB DTCM,0   KB AXI_SRAM
 *\*\           0x07 :128 KB ITCM,896 KB DTCM,0   KB AXI_SRAM
 *\*\           0x08 :0   KB ITCM,1024KB DTCM,0   KB AXI_SRAM
 *\*\           0x09 :896 KB ITCM,0   KB DTCM,128 KB AXI_SRAM
 *\*\           0x0A :768 KB ITCM,128 KB DTCM,128 KB AXI_SRAM
 *\*\           0x0B :640 KB ITCM,256 KB DTCM,128 KB AXI_SRAM
 *\*\           0x0C :512 KB ITCM,384 KB DTCM,128 KB AXI_SRAM
 *\*\           0x0D :384 KB ITCM,512 KB DTCM,128 KB AXI_SRAM
 *\*\           0x0E :256 KB ITCM,640 KB DTCM,128 KB AXI_SRAM
 *\*\           0x0F :128 KB ITCM,768 KB DTCM,128 KB AXI_SRAM
 *\*\           0x10 :0   KB ITCM,896 KB DTCM,128 KB AXI_SRAM
 *\*\           0x11 :768 KB ITCM,0   KB DTCM,256 KB AXI_SRAM
 *\*\           0x12 :640 KB ITCM,128 KB DTCM,256 KB AXI_SRAM
 *\*\           0x13 :512 KB ITCM,256 KB DTCM,256 KB AXI_SRAM
 *\*\           0x14 :384 KB ITCM,384 KB DTCM,256 KB AXI_SRAM
 *\*\           0x15 :256 KB ITCM,512 KB DTCM,256 KB AXI_SRAM
 *\*\           0x16 :128 KB ITCM,640 KB DTCM,256 KB AXI_SRAM
 *\*\           0x17 :0   KB ITCM,768 KB DTCM,256 KB AXI_SRAM
 *\*\           0x18 :640 KB ITCM,0   KB DTCM,384 KB AXI_SRAM
 *\*\           0x19 :512 KB ITCM,128 KB DTCM,384 KB AXI_SRAM
 *\*\           0x1A :384 KB ITCM,256 KB DTCM,384 KB AXI_SRAM
 *\*\           0x1B :256 KB ITCM,384 KB DTCM,384 KB AXI_SRAM
 *\*\           0x1C :128 KB ITCM,512 KB DTCM,384 KB AXI_SRAM
 *\*\           0x1D :0   KB ITCM,640 KB DTCM,384 KB AXI_SRAM
 *\*\           0x1E :512 KB ITCM,0   KB DTCM,512 KB AXI_SRAM
 *\*\           0x1F :384 KB ITCM,128 KB DTCM,512 KB AXI_SRAM
 *\*\           0x20 :256 KB ITCM,256 KB DTCM,512 KB AXI_SRAM
 *\*\           0x21 :128 KB ITCM,384 KB DTCM,512 KB AXI_SRAM
 *\*\           0x22 :0   KB ITCM,512 KB DTCM,512 KB AXI_SRAM
 *\*\           0x23 :384 KB ITCM,0   KB DTCM,640 KB AXI_SRAM
 *\*\           0x24 :256 KB ITCM,128 KB DTCM,640 KB AXI_SRAM
 *\*\           0x25 :128 KB ITCM,256 KB DTCM,640 KB AXI_SRAM
 *\*\           0x26 :0   KB ITCM,384 KB DTCM,640 KB AXI_SRAM
 *\*\           0x27 :256 KB ITCM,0   KB DTCM,768 KB AXI_SRAM
 *\*\           0x28 :128 KB ITCM,128 KB DTCM,768 KB AXI_SRAM
 *\*\           0x29 :0   KB ITCM,256 KB DTCM,768 KB AXI_SRAM
 *\*\           0x2A :128 KB ITCM,0   KB DTCM,896 KB AXI_SRAM
 *\*\           0x2B :0   KB ITCM,128 KB DTCM,896 KB AXI_SRAM
 *\*\           0x2C~2F :0KB ITCM,0   KB DTCM,1024KB AXI_SRAM
 *\*\return none  
 */               
void ConfigTcmSize(uint32_t tcmSizeValue)
{
    uint32_t currValue = (*(uint32_t(*)(void))0x1ff00f01)();
    if((currValue == 0x2c) && (currValue != tcmSizeValue))
    {
        *(uint32_t*)0x51105280 = tcmSizeValue;
        NVIC_SystemReset();
    }
}
#ifdef CORE_CM7
/**
*\*\name    PWR_ConfigSupply.
*\*\fun     Configure the PWR supply.
*\*\param   SupplySource (The input parameters must be the following values):
*\*\          - PWR_LDO_SUPPLY               :External LDO  SUPPLY 
*\*\          - PWR_DIRECT_SMPS_SUPPLY       :DCDC SUPPLY 
*\*\          - PWR_EXTERNAL_SOURCE_SUPPLY   :External VCAP SUPPLY 
*\*\return  none
**/
static void PWR_ConfigSupply(uint32_t SupplySource)
{
    __IO uint32_t tempreg;
    /* Get the old register value */
    tempreg = PWR->SYSCTRL4;
    /* Clear the old  value */
    tempreg &= (~PWR_SUPPLY_MODE_MASK);
    /* Set the new values */
    tempreg |= SupplySource;
    /* Set the power supply configuration */
    PWR->SYSCTRL4 = tempreg;
}
#endif
/**
 *\*\name   SystemInit.
 *\*\fun    Setup the microcontroller system.Initialize the FPU setting, vector table location and External memory configuration.
 *\*\param  none
 *\*\return none
 */
void SystemInit (void)
{    
  /* FPU settings ------------------------------------------------------------*/
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << (10*2))|(3UL << (11*2)));  /* set CP10 and CP11 Full Access */
  #endif

    /*SEVONPEND enabled so that an interrupt coming from the CPU(n) interrupt signal is
     detectable by the CPU after a WFI/WFE instruction.*/ 
 SCB->SCR |= SCB_SCR_SEVONPEND_Msk;

#ifdef CORE_CM7 
  
#endif /* CORE_CM7*/

#ifdef CORE_CM4

  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = 0x30000000; /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = FLASH_BANK2_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif  

#else
#ifdef CORE_CM7

  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = 0x24000000;       /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = FLASH_BANK1_BASE | VECT_TAB_OFFSET;       /* Vector Table Relocation in Internal FLASH */
#endif

   /*defaule TCM_SIZE=0x3f,All TCMSRAM are AXI_SRAM,if you want to use ITCM/DTCM, define INIT_TCM_SIZE*/
#ifdef USING_TCM
    ConfigTcmSize(TCM_SIZE_VALUE);
#endif
    /*User can change the way of power supply */
    PWR_ConfigSupply(PWR_SUPPLY_SELECTION);

#else
#error Please #define CORE_CM4 or CORE_CM7
#endif                       
#endif
}


/**
 *\*\name   N32SysTick_Handler.
 *\*\fun    This function handles N32SysTick Handler.
 *\*\param  none
 *\*\return none
 */
void N32SysTick_Handler(void)
{

}

