/**
  ******************************************************************************
  * @file    lib_lcd.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   LCD library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_LCD_H
#define __LIB_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/* LCD COMx IO typedef */
typedef struct 
{
  __IO uint32_t    *GPIO;
       uint16_t     Pin;
}LCD_COMIO;

typedef struct 
{
  uint32_t Type;
  uint32_t Drv;
  uint32_t FRQ;
  uint32_t SWPR;
  uint32_t FBMODE;
  uint32_t BKFILL;
} LCD_InitType;

typedef struct
{
  uint32_t SegCtrl0;
  uint32_t SegCtrl1;
  uint16_t SegCtrl2;
  uint32_t COMMode;
} LCD_IOInitType;

/**************  Bits definition for ANA_REG6 register       ******************/
#define ANA_REG6_VLCD_0               (0x0U << ANA_REG6_VLCD_Pos) 
#define ANA_REG6_VLCD_1               (0x1U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_2               (0x2U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_3               (0x3U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_4               (0x4U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_5               (0x5U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_6               (0x6U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_7               (0x7U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_8               (0x8U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_9               (0x9U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_A               (0xAU << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_B               (0xBU << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_C               (0xCU << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_D               (0xDU << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_E               (0xEU << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_F               (0xFU << ANA_REG6_VLCD_Pos)

/**************  Bits definition for LCD_CTRL register       ******************/

/**************  Bits definition for LCD_CTRL2 register      ******************/

//Type
#define LCD_TYPE_4COM          (0x0U << LCD_CTRL_TYPE_Pos)              /*!< 0x00000000 */
#define LCD_TYPE_6COM          (0x1U << LCD_CTRL_TYPE_Pos)              /*!< 0x00000010 */
#define LCD_TYPE_8COM          (0x2U << LCD_CTRL_TYPE_Pos)              /*!< 0x00000020 */
#define IS_LCD_TYPE(__TYPE__)  (((__TYPE__) == LCD_TYPE_4COM) ||\
                                ((__TYPE__) == LCD_TYPE_6COM) ||\
                                ((__TYPE__) == LCD_TYPE_8COM))

//DrivingRes
#define LCD_DRV_300            (0x0U << LCD_CTRL_DRV_Pos)               /*!< 0x00000000 */
#define LCD_DRV_600            (0x1U << LCD_CTRL_DRV_Pos)               /*!< 0x00000004 */
#define LCD_DRV_150            (0x2U << LCD_CTRL_DRV_Pos)               /*!< 0x00000008 */
#define LCD_DRV_200            (0x3U << LCD_CTRL_DRV_Pos)               /*!< 0x0000000C */
#define IS_LCD_DRV(__DRV__)    (((__DRV__) == LCD_DRV_300) ||\
                                ((__DRV__) == LCD_DRV_600) ||\
                                ((__DRV__) == LCD_DRV_150) ||\
                                ((__DRV__) == LCD_DRV_200)) 

//ScanFRQ
#define LCD_FRQ_64H            (0x0U << LCD_CTRL_FRQ_Pos)               /*!< 0x00000000 */
#define LCD_FRQ_128H           (0x1U << LCD_CTRL_FRQ_Pos)               /*!< 0x00000001 */
#define LCD_FRQ_256H           (0x2U << LCD_CTRL_FRQ_Pos)               /*!< 0x00000002 */
#define LCD_FRQ_512H           (0x3U << LCD_CTRL_FRQ_Pos)               /*!< 0x00000003 */
#define IS_LCD_FRQ(__FRQ__)    (((__FRQ__) == LCD_FRQ_64H)  ||\
                                ((__FRQ__) == LCD_FRQ_128H) ||\
                                ((__FRQ__) == LCD_FRQ_256H) ||\
                                ((__FRQ__) == LCD_FRQ_512H))

#define IS_LCD_SWPR(__SWPR__)  ((__SWPR__) <= 0xFFUL)   

//SwitchMode
#define LCD_FBMODE_BUFA            (0x0U << LCD_CTRL2_FBMODE_Pos)           /*!< 0x00000000 */
#define LCD_FBMODE_BUFAB           (0x1U << LCD_CTRL2_FBMODE_Pos)           /*!< 0x00000040 */
#define LCD_FBMODE_BUFABLANK       (0x2U << LCD_CTRL2_FBMODE_Pos)           /*!< 0x00000080 */
#define IS_LCD_FBMODE(__FBMODE__)  (((__FBMODE__) == LCD_FBMODE_BUFA)  ||\
                                    ((__FBMODE__) == LCD_FBMODE_BUFAB) ||\
                                    ((__FBMODE__) == LCD_FBMODE_BUFABLANK))                                   

//BlankFill
#define LCD_BKFILL_1       LCD_CTRL2_BKFILL
#define LCD_BKFILL_0       0 
#define IS_LCD_BKFILL(__BKFILL__)  (((__BKFILL__) == LCD_BKFILL_1) || ((__BKFILL__) == LCD_BKFILL_0))

//ComMode
#define LCD_COMMOD_4COM     1
#define LCD_COMMOD_6COM     3
#define LCD_COMMOD_8COM     7
#define IS_LCD_COMMOD(__COMMOD__)  (((__COMMOD__) == LCD_COMMOD_4COM) ||\
                                    ((__COMMOD__) == LCD_COMMOD_6COM) ||\
                                    ((__COMMOD__) == LCD_COMMOD_8COM))

//BiasSelection
#define LCD_BMODE_DIV3           0
#define LCD_BMODE_DIV4           ANA_REG6_LCDBMODE
#define IS_LCD_BMODE(__BMODE__)  (((__BMODE__) == LCD_BMODE_DIV3) ||\
                                  ((__BMODE__) == LCD_BMODE_DIV4))

/****************************** LCD Instances *********************************/
#define IS_LCD_ALL_INSTANCE(INSTANCE) ((INSTANCE) == LCD)

/* Exported Functions ------------------------------------------------------- */
/* LCD Exported Functions Group1: 
                                  (De)Initialization -------------------------*/
void LCD_DeInit(void);
void LCD_StructInit(LCD_InitType *LCD_InitStruct);
void LCD_Init(LCD_InitType *InitStruct);
/* LCD Exported Functions Group1: 
                                  MISC Configuration -------------------------*/
void LCD_Cmd(LCD_IOInitType *IOInitType, uint32_t NewState);
void LCD_BiasModeConfig(uint32_t BiasSelection);

#ifdef __cplusplus
}
#endif
     
#endif /* __LIB_LCD_H */

/*********************************** END OF FILE ******************************/

