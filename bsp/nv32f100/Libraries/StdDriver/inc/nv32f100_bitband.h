
/******************************************************************************
* @brief Provide Bit-band utilities. 
******************************************************************************/

#ifndef __BIT_BAND_H
#define __BIT_BAND_H
#ifdef __cplusplus
extern "C" {
#endif
                                      
/******************************************************************************
* 
*
*//*! @addtogroup BIT_BandType
* @{
*******************************************************************************/
/*!
 * @brief bit band type.
 *
 */
typedef struct
{
		uint32_t bBit0;				/*!< aliase to 0th bit */
		uint32_t bBit1;				/*!< aliase to 1th bit */
		uint32_t bBit2;				/*!< aliase to 2th bit */
		uint32_t bBit3;				/*!< aliase to 3th bit */
		uint32_t bBit4;				/*!< aliase to 4th bit */
		uint32_t bBit5;				/*!< aliase to 5th bit */
		uint32_t bBit6;				/*!< aliase to 6th bit */
		uint32_t bBit7;				/*!< aliase to 7th bit */
		uint32_t bBit8;				/*!< aliase to 8th bit */
		uint32_t bBit9;				/*!< aliase to 9th bit */
		uint32_t bBit10;				/*!< aliase to 10th bit */
		uint32_t bBit11;				/*!< aliase to 11th bit */
		uint32_t bBit12;				/*!< aliase to 12th bit */
		uint32_t bBit13;				/*!< aliase to 13th bit */
		uint32_t bBit14;				/*!< aliase to 14th bit */
		uint32_t bBit15;				/*!< aliase to 15th bit */
		uint32_t bBit16;				/*!< aliase to 16th bit */
		uint32_t bBit17;				/*!< aliase to 17th bit */
		uint32_t bBit18;				/*!< aliase to 18th bit */
		uint32_t bBit19;				/*!< aliase to 19th bit */
		uint32_t bBit20;				/*!< aliase to 20th bit */
		uint32_t bBit21;				/*!< aliase to 21th bit */
		uint32_t bBit22;				/*!< aliase to 22th bit */
		uint32_t bBit23;				/*!< aliase to 23th bit */
		uint32_t bBit24;				/*!< aliase to 24th bit */
		uint32_t bBit25;				/*!< aliase to 25th bit */
		uint32_t bBit26;				/*!< aliase to 26th bit */
		uint32_t bBit27;				/*!< aliase to 27th bit */
		uint32_t bBit28;				/*!< aliase to 28th bit */
		uint32_t bBit29;				/*!< aliase to 29th bit */
		uint32_t bBit30;				/*!< aliase to 30th bit */
		uint32_t bBit31;				/*!< aliase to 31th bit */
}BIT_BandType,*BIT_BandPtr;
/*! @} End of BIT_BandType                                               */

/******************************************************************************
* define  API list
*
*//*! @addtogroup bit_band_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
   *
   * @brief bit-band initialize pointer, so that invoke the pointer to access alisaed bitband.
   *        
   * @param[in]  pVariableAddress - point to variable.
   * @param[in]  pBitbandPtr - point to alisaed bitband address. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
__STATIC_INLINE void BIT_BandVariableInit( uint32_t *pVariableAddress,BIT_BandPtr *pBitbandPtr )
{
#if defined(CPU_NV32M3)
	ASSERT( ((uint32)pVariableAddress >= 0x20000000)&&((uint32_t)pVariableAddress <= 0x200002FF) );
#elif defined(CPU_NV32M4)
	ASSERT( ((uint32)pVariableAddress >= 0x20000000)&&((uint32_t)pVariableAddress <= (0x20000000+12*1024)));
#else
	#error "don't support this function on this device"
#endif
    *pBitbandPtr = (BIT_BandPtr)(((uint32_t)pVariableAddress-0x20000000)*32+0x22000000);   
}
/*! @} End of bit_band_api_list                                                    					*/
#ifdef __cplusplus
}
#endif
#endif /* __BIT_BAND_H */


