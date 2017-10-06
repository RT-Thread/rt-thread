
/******************************************************************************
******************************************************************************/

#ifndef __BME_H
#define __BME_H
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* BME operation code
*
*//*! @addtogroup BME_OPCode
* @{
*******************************************************************************/

#define BME_OPCODE_AND		1               /*!< AND opcode */
#define BME_OPCODE_OR		2               /*!< OR opcode */
#define BME_OPCODE_XOR		3               /*!< XOR opcode */
#define BME_OPCODE_BITFIELD	4               /*!< Bit field opcode */

#define BME_OPCODE_BIT_CLEAR    2           /*!< Bit clear opcode */
#define BME_OPCODE_BIT_SET      3           /*!< Bit set opcode */
/*! @} End of BME_OPCode                                                   */

/******************************************************************************
* BME macro used to generate hardcoded BME addresses
*
*//*! @addtogroup BME_Utilities
* @{
*******************************************************************************/

/******************************************************************************
* macro used to generate hardcoded AND address.
*
*******************************************************************************/

/*****************************************************************************//*!
   *
   * @brief  generates BME AND operation addresss (hardcoded 32-bit address).
   *        
   * @param[in]   ADDR  32-bit address.
   *  
   * @return  hardcoded 32-bit address.
   *
   * @ Pass/ Fail criteria: none.
   *
*****************************************************************************/
#define BME_AND(ADDR)           (*(volatile uint32_t *)(((uint32_t)ADDR) | (BME_OPCODE_AND<<26)))  

/******************************************************************************
* macro used to generate hardcoded OR address.
*
*******************************************************************************/

/*****************************************************************************//*!
   *
   * @brief  generates BME OR operation addresss (hardcoded 32-bit address).
   *        
   * @param[in]   ADDR  32-bit address.
   *  
   * @return  hardcoded 32-bit address.
   *
   * @ Pass/ Fail criteria: none.
   *
*****************************************************************************/

#define BME_OR(ADDR)           (*(volatile uint32_t *)(((uint32_t)ADDR) | (BME_OPCODE_OR<<26)))     


/******************************************************************************
* macro used to generate hardcoded XOR address.
*
*******************************************************************************/

/*****************************************************************************//*!
   *
   * @brief  generates BME XOR operation addresss (hardcoded 32-bit address).
   *        
   * @param[in]   ADDR  32-bit address.
   *  
   * @return  hardcoded 32-bit address.
   *
   * @ Pass/ Fail criteria: none.
   *
*****************************************************************************/

#define BME_XOR(ADDR)           (*(volatile uint32_t *)(((uint32_t)ADDR) | (BME_OPCODE_XOR<<26)))   

#if !defined(BME_SANITY_CHECK)
   /*!
     * @brief This is fastest way for BME without sanity check.
     */
  /******************************************************************************
    * macro used to generate hardcoded load 1 bit clear address (LAC1).
    *
    *******************************************************************************/
  /*****************************************************************************//*!
       *
       * @brief  generates BME bit clear operation addresss (hardcoded 32-bit address).
       *        
       * @param[in]   ADDR  32-bit address.
       * @param[in]   bit     bit number, 0-based.
       *  
       * @return  hardcoded 32-bit address.
       *
       * @ Pass/ Fail criteria: none.
       *
    *****************************************************************************/
    
    #define BME_BIT_CLEAR(ADDR,bit)        (*(volatile uint32_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_CLEAR <<26)  \
                                  | ((bit)<<21)))                                                

  /******************************************************************************
    * macro used to generate hardcoded load 1 bit set address (LAS1).
    *
    *******************************************************************************/
   /*****************************************************************************//*!
         *
         * @brief  generates BME bit set operation addresss (hardcoded 32-bit address).
         *        
         * @param[in]   ADDR  32-bit address.
         * @param[in]   bit     bit number, 0-based.
         *  
         * @return  hardcoded 32-bit address.
         *
         * @ Pass/ Fail criteria: none.
         *
      *****************************************************************************/

    #define BME_BIT_SET(ADDR,bit)        (*(volatile uint32_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_SET <<26)  \
                                  | ((bit)<<21)))                                                

  /******************************************************************************
    * macro used to generate hardcoded bit field insert address (BFI).
    *
    *******************************************************************************/
   /*****************************************************************************//*!
         *
         * @brief  generates BME bitfield insert operation addresss (hardcoded 32-bit address).
         *        
         * @param[in]   ADDR  32-bit address.
         * @param[in]   bit      bit number, 0-based.
         * @param[in]   width  bitfield width, 1-based.
         *  
         * @return  hardcoded 32-bit address.
         *
         * @ Pass/ Fail criteria: none.
         *
      *****************************************************************************/    
    #define BME_BITFIELD_INSERT(ADDR,bit,width)        (*(volatile uint32_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit)<<23) | ((width-1))<<19))                        


  /******************************************************************************
    * macro used to generate hardcoded bit field extract address (UBFX).
    *
    *******************************************************************************/
      /*****************************************************************************//*!
              *
              * @brief  generates BME bitfield extract operation addresss (hardcoded 32-bit address).
              *        
              * @param[in]   ADDR  32-bit address.
              * @param[in]   bit      bit number, 0-based.
              * @param[in]   width  bitfield width, 1-based.
              *  
              * @return  hardcoded 32-bit address.
              *
              * @ Pass/ Fail criteria: none.
              *
           *****************************************************************************/    

    #define BME_BITFIELD_EXTRACT(ADDR,bit,width)        (*(volatile uint32_t *)(((uint32_t)ADDR)    \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit)<<23) | ((width-1))<<19))                            
#else
    /*!
     * @brief This is slow way for BME as it has sanity check.
     */
    /******************************************************************************
    * macro used to generate hardcoded load 1 bit clear address (LAC1).
    *
    *******************************************************************************/
    #define BME_BIT_CLEAR(ADDR,bit)        (*(volatile uint32_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_CLEAR <<26)  \
                                  | ((bit & 0x1F)<<21)))                                                /*!< Bit clear operation */

    /******************************************************************************
    * macro used to generate hardcoded load 1 bit set address (LAS1).
    *
    *******************************************************************************/
    #define BME_BIT_SET(ADDR,bit)        (*(volatile uint32_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_SET <<26)  \
                                  | ((bit & 0x1F)<<21)))                                                /*!< Bit set operation */

    /******************************************************************************
    * macro used to generate hardcoded bit field insert address (BFI).
    *
    *******************************************************************************/
    #define BME_BITFIELD_INSERT(ADDR,bit,width)        (*(volatile uint32_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit & 0x1F)<<23) | ((width-1) & 0xF)<<19))                        /*!< Bitfield insert operation */


    /******************************************************************************
    * macro used to generate hardcoded bit field extract address (UBFX).
    *
    *******************************************************************************/
    #define BME_BITFIELD_EXTRACT(ADDR,bit,width)        (*(volatile uint32_t *)(((uint32_t)ADDR)    \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit & 0x1F)<<23) | ((width-1) & 0xF)<<19))                        /*!< Bitfield extract operation */

#endif

/******************************************************************************
* The following macros are used to generate hardcoded address for 8-bit operation.
*
*******************************************************************************/

/******************************************************************************
* macro used to generate hardcoded AND address for 8-bit operation.
*
*******************************************************************************/
/*****************************************************************************//*!
   *
   * @brief  generates BME AND operation addresss (hardcoded 32-bit address) for 8-bit data.
   *        
   * @param[in]   ADDR  32-bit address.
   *  
   * @return  hardcoded 32-bit address.
   *
   * @ Pass/ Fail criteria: none.
   *
*****************************************************************************/

#define BME_AND_8b(ADDR)           (*(volatile uint8_t *)(((uint32_t)ADDR) | (BME_OPCODE_AND<<26)))   

/******************************************************************************
* macro used to generate hardcoded OR address.
*
*******************************************************************************/
/*****************************************************************************//*!
   *
   * @brief  generates BME OR operation addresss (hardcoded 32-bit address) for 8-bit data.
   *        
   * @param[in]   ADDR  32-bit address.
   *  
   * @return  hardcoded 32-bit address.
   *
   * @ Pass/ Fail criteria: none.
   *
*****************************************************************************/

#define BME_OR_8b(ADDR)           (*(volatile uint8_t *)(((uint32_t)ADDR) | (BME_OPCODE_OR<<26)))    


/******************************************************************************
* macro used to generate hardcoded XOR address.
*
*******************************************************************************/

/*****************************************************************************//*!
   *
   * @brief  generates BME XOR operation addresss (hardcoded 32-bit address) for 8-bit data.
   *        
   * @param[in]   ADDR  32-bit address.
   *  
   * @return  hardcoded 32-bit address.
   *
   * @ Pass/ Fail criteria: none.
   *
*****************************************************************************/

#define BME_XOR_8b(ADDR)           (*(volatile uint8_t *)(((uint32_t)ADDR) | (BME_OPCODE_XOR<<26)))   

#if !defined(BME_SANITY_CHECK)
     /*!
         * @brief This is fastest way for BME without sanity check.
         */
    /******************************************************************************
        * macro used to generate hardcoded load 1 bit clear address (LAC1).
        *
        *******************************************************************************/

    /*****************************************************************************//*!
         *
         * @brief  generates BME bit clear operation addresss (hardcoded 32-bit address) for 8-bit data.
         *        
         * @param[in]   ADDR  32-bit address.
         * @param[in]   bit     bit number, 0-based.
         *  
         * @return  hardcoded 32-bit address.
         *
         * @ Pass/ Fail criteria: none.
         *
      *****************************************************************************/
    
    #define BME_BIT_CLEAR_8b(ADDR,bit)        (*(volatile uint8_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_CLEAR <<26)  \
                                  | ((bit)<<21)))                                                

    /******************************************************************************
        * macro used to generate hardcoded load 1 bit set address (LAS1).
        *
        *******************************************************************************/
    /*****************************************************************************//*!
             *
             * @brief  generates BME bit set operation addresss (hardcoded 32-bit address) for 8-bit data.
             *        
             * @param[in]   ADDR  32-bit address.
             * @param[in]   bit     bit number, 0-based.
             *  
             * @return  hardcoded 32-bit address.
             *
             * @ Pass/ Fail criteria: none.
             *
        *****************************************************************************/
    
    #define BME_BIT_SET_8b(ADDR,bit)        (*(volatile uint8_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_SET <<26)  \
                                  | ((bit)<<21)))                                                

  /******************************************************************************
    * macro used to generate hardcoded bit field insert address (BFI).
    *
    *******************************************************************************/

    /*****************************************************************************//*!
          *
          * @brief  generates BME bitfield insert operation addresss (hardcoded 32-bit address) for 8-bit data.
          *        
          * @param[in]   ADDR  32-bit address.
          * @param[in]   bit      bit number, 0-based.
          * @param[in]   width  bitfield width, 1-based.
          *  
          * @return  hardcoded 32-bit address.
          *
          * @ Pass/ Fail criteria: none.
          *
       *****************************************************************************/        

    #define BME_BITFIELD_INSERT_8b(ADDR,bit,width)        (*(volatile uint8_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit)<<23) | ((width-1))<<19))                        
  /******************************************************************************
    * macro used to generate hardcoded bit field extract address (UBFX).
    *
    *******************************************************************************/
   /*****************************************************************************//*!
         *
         * @brief  generates BME bitfield extract operation addresss (hardcoded 32-bit address) for 8-bit data.
         *        
         * @param[in]   ADDR  32-bit address.
         * @param[in]   bit      bit number, 0-based.
         * @param[in]   width  bitfield width, 1-based.
         *  
         * @return  hardcoded 32-bit address.
         *
         * @ Pass/ Fail criteria: none.
         *
      *****************************************************************************/        
    #define BME_BITFIELD_EXTRACT_8b(ADDR,bit,width)        (*(volatile uint8_t *)(((uint32_t)ADDR)    \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit<<23) | ((width-1))<<19))                        
#else
    /*!
     * @brief This is slow way for BME as it has sanity check.
     */
    /******************************************************************************
    * macro used to generate hardcoded load 1 bit clear address (LAC1).
    *
    *******************************************************************************/
    #define BME_BIT_CLEAR_8b(ADDR,bit)        (*(volatile uint8_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_CLEAR <<26)  \
                                  | ((bit & 0x1F)<<21)))                                                /*!< Bit clear operation on 8-bit*/

    /******************************************************************************
    * macro used to generate hardcoded load 1 bit set address (LAS1).
    *
    *******************************************************************************/
    #define BME_BIT_SET_8b(ADDR,bit)        (*(volatile uint8_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_SET <<26)  \
                                  | ((bit & 0x1F)<<21)))                                                /*!< Bit set operation on 8-bit */

    /******************************************************************************
    * macro used to generate hardcoded bit field insert address (BFI).
    *
    *******************************************************************************/
    #define BME_BITFIELD_INSERT_8b(ADDR,bit,width)        (*(volatile uint8_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit & 0x1F)<<23) | ((width-1) & 0xF)<<19))                        /*!< Bitfield insert operation on 8-bit */

  /******************************************************************************
    * macro used to generate hardcoded bit field extract address (UBFX).
    *
    *******************************************************************************/

    #define BME_BITFIELD_EXTRACT_8b(ADDR,bit,width)        (*(volatile uint8_t *)(((uint32_t)ADDR)    \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit & 0x1F)<<23) | ((width-1) & 0xF)<<19))                        /*!< Bitfield extract operation on 8-bit*/
#endif


/******************************************************************************
* The following macros are used to generate hardcoded address for 16-bit operation.
*
*******************************************************************************/

/******************************************************************************
* macro used to generate hardcoded AND address for 16-bit operation.
*
*******************************************************************************/
/*****************************************************************************//*!
   *
   * @brief  generates BME AND operation addresss (hardcoded 32-bit address) for 16-bit data.
   *        
   * @param[in]   ADDR  32-bit address.
   *  
   * @return  hardcoded 32-bit address.
   *
   * @ Pass/ Fail criteria: none.
   *
*****************************************************************************/

#define BME_AND_16b(ADDR)           (*(volatile uint16_t *)(((uint32_t)ADDR) | (BME_OPCODE_AND<<26)))   

/******************************************************************************
* macro used to generate hardcoded OR address.
*
*******************************************************************************/

/*****************************************************************************//*!
   *
   * @brief  generates BME OR operation addresss (hardcoded 32-bit address) for 16-bit data.
   *        
   * @param[in]   ADDR  32-bit address.
   *  
   * @return  hardcoded 32-bit address.
   *
   * @ Pass/ Fail criteria: none.
   *
*****************************************************************************/

#define BME_OR_16b(ADDR)           (*(volatile uint16_t *)(((uint32_t)ADDR) | (BME_OPCODE_OR<<26)))    


/******************************************************************************
* macro used to generate hardcoded XOR address.
*
*******************************************************************************/

/*****************************************************************************//*!
   *
   * @brief  generates BME XOR operation addresss (hardcoded 32-bit address) for 16-bit data.
   *        
   * @param[in]   ADDR  32-bit address.
   *  
   * @return  hardcoded 32-bit address.
   *
   * @ Pass/ Fail criteria: none.
   *
*****************************************************************************/

#define BME_XOR_16b(ADDR)           (*(volatile uint16_t *)(((uint32_t)ADDR) | (BME_OPCODE_XOR<<26)))   


#if !defined(BME_SANITY_CHECK)
  /*!
     * @brief This is fastest way for BME without sanity check.
     */

  /******************************************************************************
    * macro used to generate hardcoded load 1 bit clear address (LAC1).
    *
    *******************************************************************************/
    /*****************************************************************************//*!
             *
             * @brief  generates BME bit clear operation addresss (hardcoded 32-bit address) for 16-bit data.
             *        
             * @param[in]   ADDR  32-bit address.
             * @param[in]   bit     bit number, 0-based.
             *  
             * @return  hardcoded 32-bit address.
             *
             * @ Pass/ Fail criteria: none.
             *
        *****************************************************************************/
    
    #define BME_BIT_CLEAR_16b(ADDR,bit)        (*(volatile uint16_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_CLEAR <<26)  \
                                  | ((bit)<<21)))                                               

    /******************************************************************************
        * macro used to generate hardcoded load 1 bit set address (LAS1).
        *
        *******************************************************************************/
    /*****************************************************************************//*!
             *
             * @brief  generates BME bit set operation addresss (hardcoded 32-bit address) for 16-bit data.
             *        
             * @param[in]   ADDR  32-bit address.
             * @param[in]   bit     bit number, 0-based.
             *  
             * @return  hardcoded 32-bit address.
             *
             * @ Pass/ Fail criteria: none.
             *
        *****************************************************************************/
    
    #define BME_BIT_SET_16b(ADDR,bit)        (*(volatile uint16_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_SET <<26)  \
                                  | ((bit)<<21)))                                                

  /******************************************************************************
    * macro used to generate hardcoded bit field insert address (BFI).
    *
    *******************************************************************************/
    /*****************************************************************************//*!
          *
          * @brief  generates BME bitfield insert operation addresss (hardcoded 32-bit address) for 16-bit data.
          *        
          * @param[in]   ADDR  32-bit address.
          * @param[in]   bit      bit number, 0-based.
          * @param[in]   width  bitfield width, 1-based.
          *  
          * @return  hardcoded 32-bit address.
          *
          * @ Pass/ Fail criteria: none.
          *
       *****************************************************************************/        
    
    #define BME_BITFIELD_INSERT_16b(ADDR,bit,width)        (*(volatile uint16_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit)<<23) | ((width-1))<<19))                        


  /******************************************************************************
    * macro used to generate hardcoded bit field extract address (UBFX).
    *
    *******************************************************************************/
    /*****************************************************************************//*!
          *
          * @brief  generates BME bitfield extract operation addresss (hardcoded 32-bit address) for 16-bit data.
          *        
          * @param[in]   ADDR  32-bit address.
          * @param[in]   bit      bit number, 0-based.
          * @param[in]   width  bitfield width, 1-based.
          *  
          * @return  hardcoded 32-bit address.
          *
          * @ Pass/ Fail criteria: none.
          *
       *****************************************************************************/        

    #define BME_BITFIELD_EXTRACT_16b(ADDR,bit,width)        (*(volatile uint16_t *)(((uint32_t)ADDR)    \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit)<<23) | ((width-1))<<19))                        

#else
    /*!
     * @brief This is slow way for BME as it has sanity check.
     */
    /******************************************************************************
    * macro used to generate hardcoded load 1 bit clear address (LAC1).
    *
    *******************************************************************************/
    #define BME_BIT_CLEAR_16b(ADDR,bit)        (*(volatile uint16_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_CLEAR <<26)  \
                                  | ((bit & 0x1F)<<21)))                                                /*!< Bit clear operation on 16-bit*/

    /******************************************************************************
    * macro used to generate hardcoded load 1 bit set address (LAS1).
    *
    *******************************************************************************/
    #define BME_BIT_SET_16b(ADDR,bit)        (*(volatile uint16_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BIT_SET <<26)  \
                                  | ((bit & 0x1F)<<21)))                                                /*!< Bit set operation on 16-bit */

    /******************************************************************************
    * macro used to generate hardcoded bit field insert address (BFI).
    *
    *******************************************************************************/
    #define BME_BITFIELD_INSERT_16b(ADDR,bit,width)        (*(volatile uint16_t *)(((uint32_t)ADDR)   \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit & 0x1F)<<23) | ((width-1) & 0xF)<<19))                        /*!< Bitfield insert operation on 16-bit */


    /******************************************************************************
    * macro used to generate hardcoded bit field extract address (UBFX).
    *
    *******************************************************************************/
    #define BME_BITFIELD_EXTRACT_16b(ADDR,bit,width)        (*(volatile uint16_t *)(((uint32_t)ADDR)    \
                                  | (BME_OPCODE_BITFIELD <<26)  \
                                  | ((bit & 0x1F)<<23) | ((width-1) & 0xF)<<19))                        /*!< Bitfield extract operation on 16-bit*/
#endif

/*! @} End of BME_Utilities                                                   */
#ifdef __cplusplus
}
#endif
#endif /* __BME_H */


