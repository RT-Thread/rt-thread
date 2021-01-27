/**
 *******************************************************************************
 * @file  hc32f4a0_efm.h
 * @brief This file contains all the functions prototypes of the EFM driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb           First version
   2020-07-03       Heqb           Add flag judgment when operate SWAP
   2020-07-07       Heqb           Modify the return value type of the function
                                   EFM_SetOperateMode from void to en_result_t
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_EFM_H__
#define __HC32F4A0_EFM_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_EFM
 * @{
 */

#if (DDL_EFM_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EFM_Global_Types EFM Global Types
 * @{
 */

/**
 * @brief EFM configure structure
 */
typedef struct
{
    uint32_t            u32WaitCycle;   /*!< Specifies the efm read wait cycles.
                                            This parameter can be a value of @ref EFM_Wait_Cycle.             */

    uint32_t            u32CacheRst;    /*!< Specifies the data cache reset on or off.
                                            This parameter can be a value of @ref EFM_CacheRst_Func.       */

    uint32_t            u32Prefetch;    /*!< Specifies the prefetch on or off.
                                            This parameter can be a value of @ref EFM_Prefetch_Func.       */

    uint32_t            u32InsCache;    /*!< Specifies the instruction cache on or off.
                                            This parameter can be a value of @ref EFM_INSCache_Func.         */

    uint32_t            u32DataCache;   /*!< Specifies the data cache on or off.
                                            This parameter can be a value of @ref EFM_DCache_Func.          */

    uint32_t            u32LowVolRead;  /*!< Specifies the read of low-voltage mode on or off.
                                            This parameter can be a value of @ref EFM_LowVolRead_Mode.        */

    uint32_t            u32BusStatus;   /*!< Specifies the bus status busy or release while program & erase.
                                            This parameter can be a value of @ref EFM_Bus_Status.           */

    uint32_t            u32OperateMode; /*!< Specifies the operate mode.
                                            This parameter can be a value of @ref EFM_OperateMode_Definition.   */

    uint32_t            u32FlashStatus; /*!< Specifies the Flash status.
                                            This parameter can be a value of @ref EFM_Status.       */
} stc_efm_cfg_t;

/**
 * @brief EFM unique ID definition
 */
typedef struct
{
    uint32_t            u32UniqueID0;      /*!< unique ID 0.       */
    uint32_t            u32UniqueID1;      /*!< unique ID 1.       */
    uint32_t            u32UniqueID2;      /*!< unique ID 2.       */
} stc_efm_unique_id_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EFM_Global_Macros EFM Global Macros
 * @{
 */
#define EFM_SWAP_ADDR                (0x03002000UL)
#define EFM_SWAP_DATA                (0x005A5A5AUL)
/**
 * @defgroup EFM_Address EFM address area
 * @{
 */
#define EFM_START_ADDR               (0x00000000UL)   /*!< Flash start address */
#define EFM_END_ADDR                 (0x001FFFFFUL)   /*!< Flash end address */
/**
 * @}
 */

/**
 * @defgroup EFM_Sector_Address EFM Sector Address
 * @{
 */
#define EFM_ADDR_SECTOR0            (0x00000000UL)   /*!< Sector 0 */
#define EFM_ADDR_SECTOR1            (0x00002000UL)   /*!< Sector 1 */
#define EFM_ADDR_SECTOR2            (0x00004000UL)   /*!< Sector 2 */
#define EFM_ADDR_SECTOR3            (0x00006000UL)   /*!< Sector 3 */
#define EFM_ADDR_SECTOR4            (0x00008000UL)   /*!< Sector 4 */
#define EFM_ADDR_SECTOR5            (0x0000A000UL)   /*!< Sector 5 */
#define EFM_ADDR_SECTOR6            (0x0000C000UL)   /*!< Sector 6 */
#define EFM_ADDR_SECTOR7            (0x0000E000UL)   /*!< Sector 7 */
#define EFM_ADDR_SECTOR8            (0x00010000UL)   /*!< Sector 8 */
#define EFM_ADDR_SECTOR9            (0x00012000UL)   /*!< Sector 9 */
#define EFM_ADDR_SECTOR10           (0x00014000UL)   /*!< Sector 10 */
#define EFM_ADDR_SECTOR11           (0x00016000UL)   /*!< Sector 11 */
#define EFM_ADDR_SECTOR12           (0x00018000UL)   /*!< Sector 12 */
#define EFM_ADDR_SECTOR13           (0x0001A000UL)   /*!< Sector 13 */
#define EFM_ADDR_SECTOR14           (0x0001C000UL)   /*!< Sector 14 */
#define EFM_ADDR_SECTOR15           (0x0001E000UL)   /*!< Sector 15 */
#define EFM_ADDR_SECTOR16           (0x00020000UL)   /*!< Sector 16 */
#define EFM_ADDR_SECTOR17           (0x00022000UL)   /*!< Sector 17 */
#define EFM_ADDR_SECTOR18           (0x00024000UL)   /*!< Sector 18 */
#define EFM_ADDR_SECTOR19           (0x00026000UL)   /*!< Sector 19 */
#define EFM_ADDR_SECTOR20           (0x00028000UL)   /*!< Sector 20 */
#define EFM_ADDR_SECTOR21           (0x0002A000UL)   /*!< Sector 21 */
#define EFM_ADDR_SECTOR22           (0x0002C000UL)   /*!< Sector 22 */
#define EFM_ADDR_SECTOR23           (0x0002E000UL)   /*!< Sector 23 */
#define EFM_ADDR_SECTOR24           (0x00030000UL)   /*!< Sector 24 */
#define EFM_ADDR_SECTOR25           (0x00032000UL)   /*!< Sector 25 */
#define EFM_ADDR_SECTOR26           (0x00034000UL)   /*!< Sector 26 */
#define EFM_ADDR_SECTOR27           (0x00036000UL)   /*!< Sector 27 */
#define EFM_ADDR_SECTOR28           (0x00038000UL)   /*!< Sector 28 */
#define EFM_ADDR_SECTOR29           (0x0003A000UL)   /*!< Sector 29 */
#define EFM_ADDR_SECTOR30           (0x0003C000UL)   /*!< Sector 30 */
#define EFM_ADDR_SECTOR31           (0x0003E000UL)   /*!< Sector 31 */
#define EFM_ADDR_SECTOR32           (0x00040000UL)   /*!< Sector 32 */
#define EFM_ADDR_SECTOR33           (0x00042000UL)   /*!< Sector 33 */
#define EFM_ADDR_SECTOR34           (0x00044000UL)   /*!< Sector 34 */
#define EFM_ADDR_SECTOR35           (0x00046000UL)   /*!< Sector 35 */
#define EFM_ADDR_SECTOR36           (0x00048000UL)   /*!< Sector 36 */
#define EFM_ADDR_SECTOR37           (0x0004A000UL)   /*!< Sector 37 */
#define EFM_ADDR_SECTOR38           (0x0004C000UL)   /*!< Sector 38 */
#define EFM_ADDR_SECTOR39           (0x0004E000UL)   /*!< Sector 39 */
#define EFM_ADDR_SECTOR40           (0x00050000UL)   /*!< Sector 40 */
#define EFM_ADDR_SECTOR41           (0x00052000UL)   /*!< Sector 41 */
#define EFM_ADDR_SECTOR42           (0x00054000UL)   /*!< Sector 42 */
#define EFM_ADDR_SECTOR43           (0x00056000UL)   /*!< Sector 43 */
#define EFM_ADDR_SECTOR44           (0x00058000UL)   /*!< Sector 44 */
#define EFM_ADDR_SECTOR45           (0x0005A000UL)   /*!< Sector 45 */
#define EFM_ADDR_SECTOR46           (0x0005C000UL)   /*!< Sector 46 */
#define EFM_ADDR_SECTOR47           (0x0005E000UL)   /*!< Sector 47 */
#define EFM_ADDR_SECTOR48           (0x00060000UL)   /*!< Sector 48 */
#define EFM_ADDR_SECTOR49           (0x00062000UL)   /*!< Sector 49 */
#define EFM_ADDR_SECTOR50           (0x00064000UL)   /*!< Sector 50 */
#define EFM_ADDR_SECTOR51           (0x00066000UL)   /*!< Sector 51 */
#define EFM_ADDR_SECTOR52           (0x00068000UL)   /*!< Sector 52 */
#define EFM_ADDR_SECTOR53           (0x0006A000UL)   /*!< Sector 53 */
#define EFM_ADDR_SECTOR54           (0x0006C000UL)   /*!< Sector 54 */
#define EFM_ADDR_SECTOR55           (0x0006E000UL)   /*!< Sector 55 */
#define EFM_ADDR_SECTOR56           (0x00070000UL)   /*!< Sector 56 */
#define EFM_ADDR_SECTOR57           (0x00072000UL)   /*!< Sector 57 */
#define EFM_ADDR_SECTOR58           (0x00074000UL)   /*!< Sector 58 */
#define EFM_ADDR_SECTOR59           (0x00076000UL)   /*!< Sector 59 */
#define EFM_ADDR_SECTOR60           (0x00078000UL)   /*!< Sector 60 */
#define EFM_ADDR_SECTOR61           (0x0007A000UL)   /*!< Sector 61 */
#define EFM_ADDR_SECTOR62           (0x0007C000UL)   /*!< Sector 62 */
#define EFM_ADDR_SECTOR63           (0x0007E000UL)   /*!< Sector 63 */
#define EFM_ADDR_SECTOR64           (0x00080000UL)   /*!< Sector 64 */
#define EFM_ADDR_SECTOR65           (0x00082000UL)   /*!< Sector 65 */
#define EFM_ADDR_SECTOR66           (0x00084000UL)   /*!< Sector 66 */
#define EFM_ADDR_SECTOR67           (0x00086000UL)   /*!< Sector 67 */
#define EFM_ADDR_SECTOR68           (0x00088000UL)   /*!< Sector 68 */
#define EFM_ADDR_SECTOR69           (0x0008A000UL)   /*!< Sector 69 */
#define EFM_ADDR_SECTOR70           (0x0008C000UL)   /*!< Sector 70 */
#define EFM_ADDR_SECTOR71           (0x0008E000UL)   /*!< Sector 71 */
#define EFM_ADDR_SECTOR72           (0x00090000UL)   /*!< Sector 72 */
#define EFM_ADDR_SECTOR73           (0x00092000UL)   /*!< Sector 73 */
#define EFM_ADDR_SECTOR74           (0x00094000UL)   /*!< Sector 74 */
#define EFM_ADDR_SECTOR75           (0x00096000UL)   /*!< Sector 75 */
#define EFM_ADDR_SECTOR76           (0x00098000UL)   /*!< Sector 76 */
#define EFM_ADDR_SECTOR77           (0x0009A000UL)   /*!< Sector 77 */
#define EFM_ADDR_SECTOR78           (0x0009C000UL)   /*!< Sector 78 */
#define EFM_ADDR_SECTOR79           (0x0009E000UL)   /*!< Sector 79 */
#define EFM_ADDR_SECTOR80           (0x000A0000UL)   /*!< Sector 80 */
#define EFM_ADDR_SECTOR81           (0x000A2000UL)   /*!< Sector 81 */
#define EFM_ADDR_SECTOR82           (0x000A4000UL)   /*!< Sector 82 */
#define EFM_ADDR_SECTOR83           (0x000A6000UL)   /*!< Sector 83 */
#define EFM_ADDR_SECTOR84           (0x000A8000UL)   /*!< Sector 84 */
#define EFM_ADDR_SECTOR85           (0x000AA000UL)   /*!< Sector 85 */
#define EFM_ADDR_SECTOR86           (0x000AC000UL)   /*!< Sector 86 */
#define EFM_ADDR_SECTOR87           (0x000AE000UL)   /*!< Sector 87 */
#define EFM_ADDR_SECTOR88           (0x000B0000UL)   /*!< Sector 88 */
#define EFM_ADDR_SECTOR89           (0x000B2000UL)   /*!< Sector 89 */
#define EFM_ADDR_SECTOR90           (0x000B4000UL)   /*!< Sector 90 */
#define EFM_ADDR_SECTOR91           (0x000B6000UL)   /*!< Sector 91 */
#define EFM_ADDR_SECTOR92           (0x000B8000UL)   /*!< Sector 92 */
#define EFM_ADDR_SECTOR93           (0x000BA000UL)   /*!< Sector 93 */
#define EFM_ADDR_SECTOR94           (0x000BC000UL)   /*!< Sector 94 */
#define EFM_ADDR_SECTOR95           (0x000BE000UL)   /*!< Sector 95 */
#define EFM_ADDR_SECTOR96           (0x000C0000UL)   /*!< Sector 96 */
#define EFM_ADDR_SECTOR97           (0x000C2000UL)   /*!< Sector 97 */
#define EFM_ADDR_SECTOR98           (0x000C4000UL)   /*!< Sector 98 */
#define EFM_ADDR_SECTOR99           (0x000C6000UL)   /*!< Sector 99 */
#define EFM_ADDR_SECTOR100          (0x000C8000UL)   /*!< Sector 100 */
#define EFM_ADDR_SECTOR101          (0x000CA000UL)   /*!< Sector 101 */
#define EFM_ADDR_SECTOR102          (0x000CC000UL)   /*!< Sector 102 */
#define EFM_ADDR_SECTOR103          (0x000CE000UL)   /*!< Sector 103 */
#define EFM_ADDR_SECTOR104          (0x000D0000UL)   /*!< Sector 104 */
#define EFM_ADDR_SECTOR105          (0x000D2000UL)   /*!< Sector 105 */
#define EFM_ADDR_SECTOR106          (0x000D4000UL)   /*!< Sector 106 */
#define EFM_ADDR_SECTOR107          (0x000D6000UL)   /*!< Sector 107 */
#define EFM_ADDR_SECTOR108          (0x000D8000UL)   /*!< Sector 108 */
#define EFM_ADDR_SECTOR109          (0x000DA000UL)   /*!< Sector 109 */
#define EFM_ADDR_SECTOR110          (0x000DC000UL)   /*!< Sector 110 */
#define EFM_ADDR_SECTOR111          (0x000DE000UL)   /*!< Sector 111 */
#define EFM_ADDR_SECTOR112          (0x000E0000UL)   /*!< Sector 112 */
#define EFM_ADDR_SECTOR113          (0x000E2000UL)   /*!< Sector 113 */
#define EFM_ADDR_SECTOR114          (0x000E4000UL)   /*!< Sector 114 */
#define EFM_ADDR_SECTOR115          (0x000E6000UL)   /*!< Sector 115 */
#define EFM_ADDR_SECTOR116          (0x000E8000UL)   /*!< Sector 116 */
#define EFM_ADDR_SECTOR117          (0x000EA000UL)   /*!< Sector 117 */
#define EFM_ADDR_SECTOR118          (0x000EC000UL)   /*!< Sector 118 */
#define EFM_ADDR_SECTOR119          (0x000EE000UL)   /*!< Sector 119 */
#define EFM_ADDR_SECTOR120          (0x000F0000UL)   /*!< Sector 120 */
#define EFM_ADDR_SECTOR121          (0x000F2000UL)   /*!< Sector 121 */
#define EFM_ADDR_SECTOR122          (0x000F4000UL)   /*!< Sector 122 */
#define EFM_ADDR_SECTOR123          (0x000F6000UL)   /*!< Sector 123 */
#define EFM_ADDR_SECTOR124          (0x000F8000UL)   /*!< Sector 124 */
#define EFM_ADDR_SECTOR125          (0x000FA000UL)   /*!< Sector 125 */
#define EFM_ADDR_SECTOR126          (0x000FC000UL)   /*!< Sector 126 */
#define EFM_ADDR_SECTOR127          (0x000FE000UL)   /*!< Sector 127 */
#define EFM_ADDR_SECTOR128          (0x00100000UL)   /*!< Sector 128 */
#define EFM_ADDR_SECTOR129          (0x00102000UL)   /*!< Sector 129 */
#define EFM_ADDR_SECTOR130          (0x00104000UL)   /*!< Sector 130 */
#define EFM_ADDR_SECTOR131          (0x00106000UL)   /*!< Sector 131 */
#define EFM_ADDR_SECTOR132          (0x00108000UL)   /*!< Sector 132 */
#define EFM_ADDR_SECTOR133          (0x0010A000UL)   /*!< Sector 133 */
#define EFM_ADDR_SECTOR134          (0x0010C000UL)   /*!< Sector 134 */
#define EFM_ADDR_SECTOR135          (0x0010E000UL)   /*!< Sector 135 */
#define EFM_ADDR_SECTOR136          (0x00110000UL)   /*!< Sector 136 */
#define EFM_ADDR_SECTOR137          (0x00112000UL)   /*!< Sector 137 */
#define EFM_ADDR_SECTOR138          (0x00114000UL)   /*!< Sector 138 */
#define EFM_ADDR_SECTOR139          (0x00116000UL)   /*!< Sector 139 */
#define EFM_ADDR_SECTOR140          (0x00118000UL)   /*!< Sector 140 */
#define EFM_ADDR_SECTOR141          (0x0011A000UL)   /*!< Sector 141 */
#define EFM_ADDR_SECTOR142          (0x0011C000UL)   /*!< Sector 142 */
#define EFM_ADDR_SECTOR143          (0x0011E000UL)   /*!< Sector 143 */
#define EFM_ADDR_SECTOR144          (0x00120000UL)   /*!< Sector 144 */
#define EFM_ADDR_SECTOR145          (0x00122000UL)   /*!< Sector 145 */
#define EFM_ADDR_SECTOR146          (0x00124000UL)   /*!< Sector 146 */
#define EFM_ADDR_SECTOR147          (0x00126000UL)   /*!< Sector 147 */
#define EFM_ADDR_SECTOR148          (0x00128000UL)   /*!< Sector 148 */
#define EFM_ADDR_SECTOR149          (0x0012A000UL)   /*!< Sector 149 */
#define EFM_ADDR_SECTOR150          (0x0012C000UL)   /*!< Sector 150 */
#define EFM_ADDR_SECTOR151          (0x0012E000UL)   /*!< Sector 151 */
#define EFM_ADDR_SECTOR152          (0x00130000UL)   /*!< Sector 152 */
#define EFM_ADDR_SECTOR153          (0x00132000UL)   /*!< Sector 153 */
#define EFM_ADDR_SECTOR154          (0x00134000UL)   /*!< Sector 154 */
#define EFM_ADDR_SECTOR155          (0x00136000UL)   /*!< Sector 155 */
#define EFM_ADDR_SECTOR156          (0x00138000UL)   /*!< Sector 156 */
#define EFM_ADDR_SECTOR157          (0x0013A000UL)   /*!< Sector 157 */
#define EFM_ADDR_SECTOR158          (0x0013C000UL)   /*!< Sector 158 */
#define EFM_ADDR_SECTOR159          (0x0013E000UL)   /*!< Sector 159 */
#define EFM_ADDR_SECTOR160          (0x00140000UL)   /*!< Sector 160 */
#define EFM_ADDR_SECTOR161          (0x00142000UL)   /*!< Sector 161 */
#define EFM_ADDR_SECTOR162          (0x00144000UL)   /*!< Sector 162 */
#define EFM_ADDR_SECTOR163          (0x00146000UL)   /*!< Sector 163 */
#define EFM_ADDR_SECTOR164          (0x00148000UL)   /*!< Sector 164 */
#define EFM_ADDR_SECTOR165          (0x0014A000UL)   /*!< Sector 165 */
#define EFM_ADDR_SECTOR166          (0x0014C000UL)   /*!< Sector 166 */
#define EFM_ADDR_SECTOR167          (0x0014E000UL)   /*!< Sector 167 */
#define EFM_ADDR_SECTOR168          (0x00150000UL)   /*!< Sector 168 */
#define EFM_ADDR_SECTOR169          (0x00152000UL)   /*!< Sector 169 */
#define EFM_ADDR_SECTOR170          (0x00154000UL)   /*!< Sector 170 */
#define EFM_ADDR_SECTOR171          (0x00156000UL)   /*!< Sector 171 */
#define EFM_ADDR_SECTOR172          (0x00158000UL)   /*!< Sector 172 */
#define EFM_ADDR_SECTOR173          (0x0015A000UL)   /*!< Sector 173 */
#define EFM_ADDR_SECTOR174          (0x0015C000UL)   /*!< Sector 174 */
#define EFM_ADDR_SECTOR175          (0x0015E000UL)   /*!< Sector 175 */
#define EFM_ADDR_SECTOR176          (0x00160000UL)   /*!< Sector 176 */
#define EFM_ADDR_SECTOR177          (0x00162000UL)   /*!< Sector 177 */
#define EFM_ADDR_SECTOR178          (0x00164000UL)   /*!< Sector 178 */
#define EFM_ADDR_SECTOR179          (0x00166000UL)   /*!< Sector 179 */
#define EFM_ADDR_SECTOR180          (0x00168000UL)   /*!< Sector 180 */
#define EFM_ADDR_SECTOR181          (0x0016A000UL)   /*!< Sector 181 */
#define EFM_ADDR_SECTOR182          (0x0016C000UL)   /*!< Sector 182 */
#define EFM_ADDR_SECTOR183          (0x0016E000UL)   /*!< Sector 183 */
#define EFM_ADDR_SECTOR184          (0x00170000UL)   /*!< Sector 184 */
#define EFM_ADDR_SECTOR185          (0x00172000UL)   /*!< Sector 185 */
#define EFM_ADDR_SECTOR186          (0x00174000UL)   /*!< Sector 186 */
#define EFM_ADDR_SECTOR187          (0x00176000UL)   /*!< Sector 187 */
#define EFM_ADDR_SECTOR188          (0x00178000UL)   /*!< Sector 188 */
#define EFM_ADDR_SECTOR189          (0x0017A000UL)   /*!< Sector 189 */
#define EFM_ADDR_SECTOR190          (0x0017C000UL)   /*!< Sector 190 */
#define EFM_ADDR_SECTOR191          (0x0017E000UL)   /*!< Sector 191 */
#define EFM_ADDR_SECTOR192          (0x00180000UL)   /*!< Sector 192 */
#define EFM_ADDR_SECTOR193          (0x00182000UL)   /*!< Sector 193 */
#define EFM_ADDR_SECTOR194          (0x00184000UL)   /*!< Sector 194 */
#define EFM_ADDR_SECTOR195          (0x00186000UL)   /*!< Sector 195 */
#define EFM_ADDR_SECTOR196          (0x00188000UL)   /*!< Sector 196 */
#define EFM_ADDR_SECTOR197          (0x0018A000UL)   /*!< Sector 197 */
#define EFM_ADDR_SECTOR198          (0x0018C000UL)   /*!< Sector 198 */
#define EFM_ADDR_SECTOR199          (0x0018E000UL)   /*!< Sector 199 */
#define EFM_ADDR_SECTOR200          (0x00190000UL)   /*!< Sector 200 */
#define EFM_ADDR_SECTOR201          (0x00192000UL)   /*!< Sector 201 */
#define EFM_ADDR_SECTOR202          (0x00194000UL)   /*!< Sector 202 */
#define EFM_ADDR_SECTOR203          (0x00196000UL)   /*!< Sector 203 */
#define EFM_ADDR_SECTOR204          (0x00198000UL)   /*!< Sector 204 */
#define EFM_ADDR_SECTOR205          (0x0019A000UL)   /*!< Sector 205 */
#define EFM_ADDR_SECTOR206          (0x0019C000UL)   /*!< Sector 206 */
#define EFM_ADDR_SECTOR207          (0x0019E000UL)   /*!< Sector 207 */
#define EFM_ADDR_SECTOR208          (0x001A0000UL)   /*!< Sector 208 */
#define EFM_ADDR_SECTOR209          (0x001A2000UL)   /*!< Sector 209 */
#define EFM_ADDR_SECTOR210          (0x001A4000UL)   /*!< Sector 210 */
#define EFM_ADDR_SECTOR211          (0x001A6000UL)   /*!< Sector 211 */
#define EFM_ADDR_SECTOR212          (0x001A8000UL)   /*!< Sector 212 */
#define EFM_ADDR_SECTOR213          (0x001AA000UL)   /*!< Sector 213 */
#define EFM_ADDR_SECTOR214          (0x001AC000UL)   /*!< Sector 214 */
#define EFM_ADDR_SECTOR215          (0x001AE000UL)   /*!< Sector 215 */
#define EFM_ADDR_SECTOR216          (0x001B0000UL)   /*!< Sector 216 */
#define EFM_ADDR_SECTOR217          (0x001B2000UL)   /*!< Sector 217 */
#define EFM_ADDR_SECTOR218          (0x001B4000UL)   /*!< Sector 218 */
#define EFM_ADDR_SECTOR219          (0x001B6000UL)   /*!< Sector 219 */
#define EFM_ADDR_SECTOR220          (0x001B8000UL)   /*!< Sector 220 */
#define EFM_ADDR_SECTOR221          (0x001BA000UL)   /*!< Sector 221 */
#define EFM_ADDR_SECTOR222          (0x001BC000UL)   /*!< Sector 222 */
#define EFM_ADDR_SECTOR223          (0x001BE000UL)   /*!< Sector 223 */
#define EFM_ADDR_SECTOR224          (0x001C0000UL)   /*!< Sector 224 */
#define EFM_ADDR_SECTOR225          (0x001C2000UL)   /*!< Sector 225 */
#define EFM_ADDR_SECTOR226          (0x001C4000UL)   /*!< Sector 226 */
#define EFM_ADDR_SECTOR227          (0x001C6000UL)   /*!< Sector 227 */
#define EFM_ADDR_SECTOR228          (0x001C8000UL)   /*!< Sector 228 */
#define EFM_ADDR_SECTOR229          (0x001CA000UL)   /*!< Sector 229 */
#define EFM_ADDR_SECTOR230          (0x001CC000UL)   /*!< Sector 230 */
#define EFM_ADDR_SECTOR231          (0x001CE000UL)   /*!< Sector 231 */
#define EFM_ADDR_SECTOR232          (0x001D0000UL)   /*!< Sector 232 */
#define EFM_ADDR_SECTOR233          (0x001D2000UL)   /*!< Sector 233 */
#define EFM_ADDR_SECTOR234          (0x001D4000UL)   /*!< Sector 234 */
#define EFM_ADDR_SECTOR235          (0x001D6000UL)   /*!< Sector 235 */
#define EFM_ADDR_SECTOR236          (0x001D8000UL)   /*!< Sector 236 */
#define EFM_ADDR_SECTOR237          (0x001DA000UL)   /*!< Sector 237 */
#define EFM_ADDR_SECTOR238          (0x001DC000UL)   /*!< Sector 238 */
#define EFM_ADDR_SECTOR239          (0x001DE000UL)   /*!< Sector 239 */
#define EFM_ADDR_SECTOR240          (0x001E0000UL)   /*!< Sector 240 */
#define EFM_ADDR_SECTOR241          (0x001E2000UL)   /*!< Sector 241 */
#define EFM_ADDR_SECTOR242          (0x001E4000UL)   /*!< Sector 242 */
#define EFM_ADDR_SECTOR243          (0x001E6000UL)   /*!< Sector 243 */
#define EFM_ADDR_SECTOR244          (0x001E8000UL)   /*!< Sector 244 */
#define EFM_ADDR_SECTOR245          (0x001EA000UL)   /*!< Sector 245 */
#define EFM_ADDR_SECTOR246          (0x001EC000UL)   /*!< Sector 246 */
#define EFM_ADDR_SECTOR247          (0x001EE000UL)   /*!< Sector 247 */
#define EFM_ADDR_SECTOR248          (0x001F0000UL)   /*!< Sector 248 */
#define EFM_ADDR_SECTOR249          (0x001F2000UL)   /*!< Sector 249 */
#define EFM_ADDR_SECTOR250          (0x001F4000UL)   /*!< Sector 250 */
#define EFM_ADDR_SECTOR251          (0x001F6000UL)   /*!< Sector 251 */
#define EFM_ADDR_SECTOR252          (0x001F8000UL)   /*!< Sector 252 */
#define EFM_ADDR_SECTOR253          (0x001FA000UL)   /*!< Sector 253 */
#define EFM_ADDR_SECTOR254          (0x001FC000UL)   /*!< Sector 254 */
#define EFM_ADDR_SECTOR255          (0x001FE000UL)   /*!< Sector 255 */
/**
 * @}
 */

/**
 * @defgroup EFM_OTP_Address EFM otp address
 * @{
 */
#define EFM_OTP_BLOCK0              (0x00000000UL)   /*!< OTP block0   8K Bytes */
#define EFM_OTP_BLOCK1              (0x00002000UL)   /*!< OTP block1   8K Bytes */
#define EFM_OTP_BLOCK2              (0x00004000UL)   /*!< OTP block2   8K Bytes */
#define EFM_OTP_BLOCK3              (0x00006000UL)   /*!< OTP block3   8K Bytes */
#define EFM_OTP_BLOCK4              (0x00008000UL)   /*!< OTP block4   8K Bytes */
#define EFM_OTP_BLOCK5              (0x0000A000UL)   /*!< OTP block5   8K Bytes */
#define EFM_OTP_BLOCK6              (0x0000C000UL)   /*!< OTP block6   8K Bytes */
#define EFM_OTP_BLOCK7              (0x0000E000UL)   /*!< OTP block7   8K Bytes */
#define EFM_OTP_BLOCK8              (0x00010000UL)   /*!< OTP block8   8K Bytes */
#define EFM_OTP_BLOCK9              (0x00012000UL)   /*!< OTP block9   8K Bytes */
#define EFM_OTP_BLOCK10             (0x00014000UL)   /*!< OTP block10  8K Bytes */
#define EFM_OTP_BLOCK11             (0x00016000UL)   /*!< OTP block11  8K Bytes */
#define EFM_OTP_BLOCK12             (0x00018000UL)   /*!< OTP block12  8K Bytes */
#define EFM_OTP_BLOCK13             (0x0001A000UL)   /*!< OTP block13  8K Bytes */
#define EFM_OTP_BLOCK14             (0x0001C000UL)   /*!< OTP block14  8K Bytes */
#define EFM_OTP_BLOCK15             (0x0001E000UL)   /*!< OTP block15  8K Bytes */

#define EFM_OTP_BLOCK16             (0x03000000UL)   /*!< OTP block16  2K Bytes */
#define EFM_OTP_BLOCK17             (0x03000800UL)   /*!< OTP block17  2K Bytes */

#define EFM_OTP_BLOCK18             (0x03001000UL)   /*!< OTP block18  256 Bytes */
#define EFM_OTP_BLOCK19             (0x03001100UL)   /*!< OTP block19  256 Bytes */
#define EFM_OTP_BLOCK20             (0x03001200UL)   /*!< OTP block20  256 Bytes */
#define EFM_OTP_BLOCK21             (0x03001300UL)   /*!< OTP block21  256 Bytes */

#define EFM_OTP_BLOCK22             (0x03001400UL)   /*!< OTP block22  16 Bytes */
#define EFM_OTP_BLOCK23             (0x03001410UL)   /*!< OTP block23  16 Bytes */
#define EFM_OTP_BLOCK24             (0x03001420UL)   /*!< OTP block24  16 Bytes */
#define EFM_OTP_BLOCK25             (0x03001430UL)   /*!< OTP block25  16 Bytes */
#define EFM_OTP_BLOCK26             (0x03001440UL)   /*!< OTP block26  16 Bytes */
#define EFM_OTP_BLOCK27             (0x03001450UL)   /*!< OTP block27  16 Bytes */
#define EFM_OTP_BLOCK28             (0x03001460UL)   /*!< OTP block28  16 Bytes */
#define EFM_OTP_BLOCK29             (0x03001470UL)   /*!< OTP block29  16 Bytes */
#define EFM_OTP_BLOCK30             (0x03001480UL)   /*!< OTP block30  16 Bytes */
#define EFM_OTP_BLOCK31             (0x03001490UL)   /*!< OTP block31  16 Bytes */
#define EFM_OTP_BLOCK32             (0x030014A0UL)   /*!< OTP block32  16 Bytes */
#define EFM_OTP_BLOCK33             (0x030014B0UL)   /*!< OTP block33  16 Bytes */
#define EFM_OTP_BLOCK34             (0x030014C0UL)   /*!< OTP block34  16 Bytes */
#define EFM_OTP_BLOCK35             (0x030014D0UL)   /*!< OTP block35  16 Bytes */
#define EFM_OTP_BLOCK36             (0x030014E0UL)   /*!< OTP block36  16 Bytes */
#define EFM_OTP_BLOCK37             (0x030014F0UL)   /*!< OTP block37  16 Bytes */
#define EFM_OTP_BLOCK38             (0x03001500UL)   /*!< OTP block38  16 Bytes */
#define EFM_OTP_BLOCK39             (0x03001510UL)   /*!< OTP block39  16 Bytes */
#define EFM_OTP_BLOCK40             (0x03001520UL)   /*!< OTP block40  16 Bytes */
#define EFM_OTP_BLOCK41             (0x03001530UL)   /*!< OTP block41  16 Bytes */
#define EFM_OTP_BLOCK42             (0x03001540UL)   /*!< OTP block42  16 Bytes */
#define EFM_OTP_BLOCK43             (0x03001550UL)   /*!< OTP block43  16 Bytes */
#define EFM_OTP_BLOCK44             (0x03001560UL)   /*!< OTP block44  16 Bytes */
#define EFM_OTP_BLOCK45             (0x03001570UL)   /*!< OTP block45  16 Bytes */
#define EFM_OTP_BLOCK46             (0x03001580UL)   /*!< OTP block46  16 Bytes */
#define EFM_OTP_BLOCK47             (0x03001590UL)   /*!< OTP block47  16 Bytes */
#define EFM_OTP_BLOCK48             (0x030015A0UL)   /*!< OTP block48  16 Bytes */
#define EFM_OTP_BLOCK49             (0x030015B0UL)   /*!< OTP block49  16 Bytes */
#define EFM_OTP_BLOCK50             (0x030015C0UL)   /*!< OTP block50  16 Bytes */
#define EFM_OTP_BLOCK51             (0x030015D0UL)   /*!< OTP block51  16 Bytes */
#define EFM_OTP_BLOCK52             (0x030015E0UL)   /*!< OTP block52  16 Bytes */
#define EFM_OTP_BLOCK53             (0x030015F0UL)   /*!< OTP block53  16 Bytes */

#define EFM_OTP_BLOCK54             (0x03001600UL)   /*!< OTP block54  4 Bytes */
#define EFM_OTP_BLOCK55             (0x03001604UL)   /*!< OTP block55  4 Bytes */
#define EFM_OTP_BLOCK56             (0x03001608UL)   /*!< OTP block56  4 Bytes */
#define EFM_OTP_BLOCK57             (0x0300160CUL)   /*!< OTP block57  4 Bytes */
#define EFM_OTP_BLOCK58             (0x03001610UL)   /*!< OTP block58  4 Bytes */
#define EFM_OTP_BLOCK59             (0x03001614UL)   /*!< OTP block59  4 Bytes */
#define EFM_OTP_BLOCK60             (0x03001618UL)   /*!< OTP block60  4 Bytes */
#define EFM_OTP_BLOCK61             (0x0300161CUL)   /*!< OTP block61  4 Bytes */
#define EFM_OTP_BLOCK62             (0x03001620UL)   /*!< OTP block62  4 Bytes */
#define EFM_OTP_BLOCK63             (0x03001624UL)   /*!< OTP block63  4 Bytes */
#define EFM_OTP_BLOCK64             (0x03001628UL)   /*!< OTP block64  4 Bytes */
#define EFM_OTP_BLOCK65             (0x0300162CUL)   /*!< OTP block65  4 Bytes */
#define EFM_OTP_BLOCK66             (0x03001630UL)   /*!< OTP block66  4 Bytes */
#define EFM_OTP_BLOCK67             (0x03001634UL)   /*!< OTP block67  4 Bytes */
#define EFM_OTP_BLOCK68             (0x03001638UL)   /*!< OTP block68  4 Bytes */
#define EFM_OTP_BLOCK69             (0x0300163CUL)   /*!< OTP block69  4 Bytes */
#define EFM_OTP_BLOCK70             (0x03001640UL)   /*!< OTP block70  4 Bytes */
#define EFM_OTP_BLOCK71             (0x03001644UL)   /*!< OTP block71  4 Bytes */
#define EFM_OTP_BLOCK72             (0x03001648UL)   /*!< OTP block72  4 Bytes */
#define EFM_OTP_BLOCK73             (0x0300164CUL)   /*!< OTP block73  4 Bytes */
#define EFM_OTP_BLOCK74             (0x03001650UL)   /*!< OTP block74  4 Bytes */
#define EFM_OTP_BLOCK75             (0x03001654UL)   /*!< OTP block75  4 Bytes */
#define EFM_OTP_BLOCK76             (0x03001658UL)   /*!< OTP block76  4 Bytes */
#define EFM_OTP_BLOCK77             (0x0300165CUL)   /*!< OTP block77  4 Bytes */
#define EFM_OTP_BLOCK78             (0x03001660UL)   /*!< OTP block78  4 Bytes */
#define EFM_OTP_BLOCK79             (0x03001664UL)   /*!< OTP block79  4 Bytes */
#define EFM_OTP_BLOCK80             (0x03001668UL)   /*!< OTP block80  4 Bytes */
#define EFM_OTP_BLOCK81             (0x0300166CUL)   /*!< OTP block81  4 Bytes */
#define EFM_OTP_BLOCK82             (0x03001670UL)   /*!< OTP block82  4 Bytes */
#define EFM_OTP_BLOCK83             (0x03001674UL)   /*!< OTP block83  4 Bytes */
#define EFM_OTP_BLOCK84             (0x03001678UL)   /*!< OTP block84  4 Bytes */
#define EFM_OTP_BLOCK85             (0x0300167CUL)   /*!< OTP block85  4 Bytes */
#define EFM_OTP_BLOCK86             (0x03001680UL)   /*!< OTP block86  4 Bytes */
#define EFM_OTP_BLOCK87             (0x03001684UL)   /*!< OTP block87  4 Bytes */
#define EFM_OTP_BLOCK88             (0x03001688UL)   /*!< OTP block88  4 Bytes */
#define EFM_OTP_BLOCK89             (0x0300168CUL)   /*!< OTP block89  4 Bytes */
#define EFM_OTP_BLOCK90             (0x03001690UL)   /*!< OTP block90  4 Bytes */
#define EFM_OTP_BLOCK91             (0x03001694UL)   /*!< OTP block91  4 Bytes */
#define EFM_OTP_BLOCK92             (0x03001698UL)   /*!< OTP block92  4 Bytes */
#define EFM_OTP_BLOCK93             (0x0300169CUL)   /*!< OTP block93  4 Bytes */
#define EFM_OTP_BLOCK94             (0x030016A0UL)   /*!< OTP block94  4 Bytes */
#define EFM_OTP_BLOCK95             (0x030016A4UL)   /*!< OTP block95  4 Bytes */
#define EFM_OTP_BLOCK96             (0x030016A8UL)   /*!< OTP block96  4 Bytes */
#define EFM_OTP_BLOCK97             (0x030016ACUL)   /*!< OTP block97  4 Bytes */
#define EFM_OTP_BLOCK98             (0x030016B0UL)   /*!< OTP block98  4 Bytes */
#define EFM_OTP_BLOCK99             (0x030016B4UL)   /*!< OTP block99  4 Bytes */
#define EFM_OTP_BLOCK100            (0x030016B8UL)   /*!< OTP block100 4 Bytes */
#define EFM_OTP_BLOCK101            (0x030016BCUL)   /*!< OTP block101 4 Bytes */
#define EFM_OTP_BLOCK102            (0x030016C0UL)   /*!< OTP block102 4 Bytes */
#define EFM_OTP_BLOCK103            (0x030016C4UL)   /*!< OTP block103 4 Bytes */
#define EFM_OTP_BLOCK104            (0x030016C8UL)   /*!< OTP block104 4 Bytes */
#define EFM_OTP_BLOCK105            (0x030016CCUL)   /*!< OTP block105 4 Bytes */
#define EFM_OTP_BLOCK106            (0x030016D0UL)   /*!< OTP block106 4 Bytes */
#define EFM_OTP_BLOCK107            (0x030016D4UL)   /*!< OTP block107 4 Bytes */
#define EFM_OTP_BLOCK108            (0x030016D8UL)   /*!< OTP block108 4 Bytes */
#define EFM_OTP_BLOCK109            (0x030016DCUL)   /*!< OTP block109 4 Bytes */
#define EFM_OTP_BLOCK110            (0x030016E0UL)   /*!< OTP block110 4 Bytes */
#define EFM_OTP_BLOCK111            (0x030016E4UL)   /*!< OTP block111 4 Bytes */
#define EFM_OTP_BLOCK112            (0x030016E8UL)   /*!< OTP block112 4 Bytes */
#define EFM_OTP_BLOCK113            (0x030016ECUL)   /*!< OTP block113 4 Bytes */
#define EFM_OTP_BLOCK114            (0x030016F0UL)   /*!< OTP block114 4 Bytes */
#define EFM_OTP_BLOCK115            (0x030016F4UL)   /*!< OTP block115 4 Bytes */
#define EFM_OTP_BLOCK116            (0x030016F8UL)   /*!< OTP block116 4 Bytes */
#define EFM_OTP_BLOCK117            (0x030016FCUL)   /*!< OTP block117 4 Bytes */
#define EFM_OTP_BLOCK118            (0x03001700UL)   /*!< OTP block118 4 Bytes */
#define EFM_OTP_BLOCK119            (0x03001704UL)   /*!< OTP block119 4 Bytes */
#define EFM_OTP_BLOCK120            (0x03001708UL)   /*!< OTP block120 4 Bytes */
#define EFM_OTP_BLOCK121            (0x0300170CUL)   /*!< OTP block121 4 Bytes */
#define EFM_OTP_BLOCK122            (0x03001710UL)   /*!< OTP block122 4 Bytes */
#define EFM_OTP_BLOCK123            (0x03001714UL)   /*!< OTP block123 4 Bytes */
#define EFM_OTP_BLOCK124            (0x03001718UL)   /*!< OTP block124 4 Bytes */
#define EFM_OTP_BLOCK125            (0x0300171CUL)   /*!< OTP block125 4 Bytes */
#define EFM_OTP_BLOCK126            (0x03001720UL)   /*!< OTP block126 4 Bytes */
#define EFM_OTP_BLOCK127            (0x03001724UL)   /*!< OTP block127 4 Bytes */
#define EFM_OTP_BLOCK128            (0x03001728UL)   /*!< OTP block128 4 Bytes */
#define EFM_OTP_BLOCK129            (0x0300172CUL)   /*!< OTP block129 4 Bytes */
#define EFM_OTP_BLOCK130            (0x03001730UL)   /*!< OTP block130 4 Bytes */
#define EFM_OTP_BLOCK131            (0x03001734UL)   /*!< OTP block131 4 Bytes */
#define EFM_OTP_BLOCK132            (0x03001738UL)   /*!< OTP block132 4 Bytes */
#define EFM_OTP_BLOCK133            (0x0300173CUL)   /*!< OTP block133 4 Bytes */
#define EFM_OTP_BLOCK134            (0x03001740UL)   /*!< OTP block134 4 Bytes */
#define EFM_OTP_BLOCK135            (0x03001744UL)   /*!< OTP block135 4 Bytes */
#define EFM_OTP_BLOCK136            (0x03001748UL)   /*!< OTP block136 4 Bytes */
#define EFM_OTP_BLOCK137            (0x0300174CUL)   /*!< OTP block137 4 Bytes */
#define EFM_OTP_BLOCK138            (0x03001750UL)   /*!< OTP block138 4 Bytes */
#define EFM_OTP_BLOCK139            (0x03001754UL)   /*!< OTP block139 4 Bytes */
#define EFM_OTP_BLOCK140            (0x03001758UL)   /*!< OTP block140 4 Bytes */
#define EFM_OTP_BLOCK141            (0x0300175CUL)   /*!< OTP block141 4 Bytes */
#define EFM_OTP_BLOCK142            (0x03001760UL)   /*!< OTP block142 4 Bytes */
#define EFM_OTP_BLOCK143            (0x03001764UL)   /*!< OTP block143 4 Bytes */
#define EFM_OTP_BLOCK144            (0x03001768UL)   /*!< OTP block144 4 Bytes */
#define EFM_OTP_BLOCK145            (0x0300176CUL)   /*!< OTP block145 4 Bytes */
#define EFM_OTP_BLOCK146            (0x03001770UL)   /*!< OTP block146 4 Bytes */
#define EFM_OTP_BLOCK147            (0x03001774UL)   /*!< OTP block147 4 Bytes */
#define EFM_OTP_BLOCK148            (0x03001778UL)   /*!< OTP block148 4 Bytes */
#define EFM_OTP_BLOCK149            (0x0300177CUL)   /*!< OTP block149 4 Bytes */
#define EFM_OTP_BLOCK150            (0x03001780UL)   /*!< OTP block150 4 Bytes */
#define EFM_OTP_BLOCK151            (0x03001784UL)   /*!< OTP block151 4 Bytes */
#define EFM_OTP_BLOCK152            (0x03001788UL)   /*!< OTP block152 4 Bytes */
#define EFM_OTP_BLOCK153            (0x0300178CUL)   /*!< OTP block153 4 Bytes */
#define EFM_OTP_BLOCK154            (0x03001790UL)   /*!< OTP block154 4 Bytes */
#define EFM_OTP_BLOCK155            (0x03001794UL)   /*!< OTP block155 4 Bytes */
#define EFM_OTP_BLOCK156            (0x03001798UL)   /*!< OTP block156 4 Bytes */
#define EFM_OTP_BLOCK157            (0x0300179CUL)   /*!< OTP block157 4 Bytes */
#define EFM_OTP_BLOCK158            (0x030017A0UL)   /*!< OTP block158 4 Bytes */
#define EFM_OTP_BLOCK159            (0x030017A4UL)   /*!< OTP block159 4 Bytes */
#define EFM_OTP_BLOCK160            (0x030017A8UL)   /*!< OTP block160 4 Bytes */
#define EFM_OTP_BLOCK161            (0x030017ACUL)   /*!< OTP block161 4 Bytes */
#define EFM_OTP_BLOCK162            (0x030017B0UL)   /*!< OTP block162 4 Bytes */
#define EFM_OTP_BLOCK163            (0x030017B4UL)   /*!< OTP block163 4 Bytes */
#define EFM_OTP_BLOCK164            (0x030017B8UL)   /*!< OTP block164 4 Bytes */
#define EFM_OTP_BLOCK165            (0x030017BCUL)   /*!< OTP block165 4 Bytes */
#define EFM_OTP_BLOCK166            (0x030017C0UL)   /*!< OTP block166 4 Bytes */
#define EFM_OTP_BLOCK167            (0x030017C4UL)   /*!< OTP block167 4 Bytes */
#define EFM_OTP_BLOCK168            (0x030017C8UL)   /*!< OTP block168 4 Bytes */
#define EFM_OTP_BLOCK169            (0x030017CCUL)   /*!< OTP block169 4 Bytes */
#define EFM_OTP_BLOCK170            (0x030017D0UL)   /*!< OTP block170 4 Bytes */
#define EFM_OTP_BLOCK171            (0x030017D4UL)   /*!< OTP block171 4 Bytes */
#define EFM_OTP_BLOCK172            (0x030017D8UL)   /*!< OTP block172 4 Bytes */
#define EFM_OTP_BLOCK173            (0x030017DCUL)   /*!< OTP block173 4 Bytes */
#define EFM_OTP_BLOCK174            (0x030017E0UL)   /*!< OTP block174 4 Bytes */
#define EFM_OTP_BLOCK175            (0x030017E4UL)   /*!< OTP block175 4 Bytes */
#define EFM_OTP_BLOCK176            (0x030017E8UL)   /*!< OTP block176 4 Bytes */
#define EFM_OTP_BLOCK177            (0x030017ECUL)   /*!< OTP block177 4 Bytes */
#define EFM_OTP_BLOCK178            (0x030017F0UL)   /*!< OTP block178 4 Bytes */
#define EFM_OTP_BLOCK179            (0x030017F4UL)   /*!< OTP block179 4 Bytes */
#define EFM_OTP_BLOCK180            (0x030017F8UL)   /*!< OTP block180 4 Bytes */
#define EFM_OTP_BLOCK181            (0x030017FCUL)   /*!< OTP block181 4 Bytes */
/**
 * @}
 */

/**
 * @defgroup EFM_Sectot_Num Efm sector number
 * @{
 */
#define EFM_SECTOR_0                (0U)
#define EFM_SECTOR_1                (1U)
#define EFM_SECTOR_2                (2U)
#define EFM_SECTOR_3                (3U)
#define EFM_SECTOR_4                (4U)
#define EFM_SECTOR_5                (5U)
#define EFM_SECTOR_6                (6U)
#define EFM_SECTOR_7                (7U)
#define EFM_SECTOR_8                (8U)
#define EFM_SECTOR_9                (9U)
#define EFM_SECTOR_10               (10U)
#define EFM_SECTOR_11               (11U)
#define EFM_SECTOR_12               (12U)
#define EFM_SECTOR_13               (13U)
#define EFM_SECTOR_14               (14U)
#define EFM_SECTOR_15               (15U)
#define EFM_SECTOR_16               (16U)
#define EFM_SECTOR_17               (17U)
#define EFM_SECTOR_18               (18U)
#define EFM_SECTOR_19               (19U)
#define EFM_SECTOR_20               (20U)
#define EFM_SECTOR_21               (21U)
#define EFM_SECTOR_22               (22U)
#define EFM_SECTOR_23               (23U)
#define EFM_SECTOR_24               (24U)
#define EFM_SECTOR_25               (25U)
#define EFM_SECTOR_26               (26U)
#define EFM_SECTOR_27               (27U)
#define EFM_SECTOR_28               (28U)
#define EFM_SECTOR_29               (29U)
#define EFM_SECTOR_30               (30U)
#define EFM_SECTOR_31               (31U)
#define EFM_SECTOR_32               (32U)
#define EFM_SECTOR_33               (33U)
#define EFM_SECTOR_34               (34U)
#define EFM_SECTOR_35               (35U)
#define EFM_SECTOR_36               (36U)
#define EFM_SECTOR_37               (37U)
#define EFM_SECTOR_38               (38U)
#define EFM_SECTOR_39               (39U)
#define EFM_SECTOR_40               (40U)
#define EFM_SECTOR_41               (41U)
#define EFM_SECTOR_42               (42U)
#define EFM_SECTOR_43               (43U)
#define EFM_SECTOR_44               (44U)
#define EFM_SECTOR_45               (45U)
#define EFM_SECTOR_46               (46U)
#define EFM_SECTOR_47               (47U)
#define EFM_SECTOR_48               (48U)
#define EFM_SECTOR_49               (49U)
#define EFM_SECTOR_50               (50U)
#define EFM_SECTOR_51               (51U)
#define EFM_SECTOR_52               (52U)
#define EFM_SECTOR_53               (53U)
#define EFM_SECTOR_54               (54U)
#define EFM_SECTOR_55               (55U)
#define EFM_SECTOR_56               (56U)
#define EFM_SECTOR_57               (57U)
#define EFM_SECTOR_58               (58U)
#define EFM_SECTOR_59               (59U)
#define EFM_SECTOR_60               (60U)
#define EFM_SECTOR_61               (61U)
#define EFM_SECTOR_62               (62U)
#define EFM_SECTOR_63               (63U)
#define EFM_SECTOR_64               (64U)
#define EFM_SECTOR_65               (65U)
#define EFM_SECTOR_66               (66U)
#define EFM_SECTOR_67               (67U)
#define EFM_SECTOR_68               (68U)
#define EFM_SECTOR_69               (69U)
#define EFM_SECTOR_70               (70U)
#define EFM_SECTOR_71               (71U)
#define EFM_SECTOR_72               (72U)
#define EFM_SECTOR_73               (73U)
#define EFM_SECTOR_74               (74U)
#define EFM_SECTOR_75               (75U)
#define EFM_SECTOR_76               (76U)
#define EFM_SECTOR_77               (77U)
#define EFM_SECTOR_78               (78U)
#define EFM_SECTOR_79               (79U)
#define EFM_SECTOR_80               (80U)
#define EFM_SECTOR_81               (81U)
#define EFM_SECTOR_82               (82U)
#define EFM_SECTOR_83               (83U)
#define EFM_SECTOR_84               (84U)
#define EFM_SECTOR_85               (85U)
#define EFM_SECTOR_86               (86U)
#define EFM_SECTOR_87               (87U)
#define EFM_SECTOR_88               (88U)
#define EFM_SECTOR_89               (89U)
#define EFM_SECTOR_90               (90U)
#define EFM_SECTOR_91               (91U)
#define EFM_SECTOR_92               (92U)
#define EFM_SECTOR_93               (93U)
#define EFM_SECTOR_94               (94U)
#define EFM_SECTOR_95               (95U)
#define EFM_SECTOR_96               (96U)
#define EFM_SECTOR_97               (97U)
#define EFM_SECTOR_98               (98U)
#define EFM_SECTOR_99               (99U)
#define EFM_SECTOR_100              (100U)
#define EFM_SECTOR_101              (101U)
#define EFM_SECTOR_102              (102U)
#define EFM_SECTOR_103              (103U)
#define EFM_SECTOR_104              (104U)
#define EFM_SECTOR_105              (105U)
#define EFM_SECTOR_106              (106U)
#define EFM_SECTOR_107              (107U)
#define EFM_SECTOR_108              (108U)
#define EFM_SECTOR_109              (109U)
#define EFM_SECTOR_110              (110U)
#define EFM_SECTOR_111              (111U)
#define EFM_SECTOR_112              (112U)
#define EFM_SECTOR_113              (113U)
#define EFM_SECTOR_114              (114U)
#define EFM_SECTOR_115              (115U)
#define EFM_SECTOR_116              (116U)
#define EFM_SECTOR_117              (117U)
#define EFM_SECTOR_118              (118U)
#define EFM_SECTOR_119              (119U)
#define EFM_SECTOR_120              (120U)
#define EFM_SECTOR_121              (121U)
#define EFM_SECTOR_122              (122U)
#define EFM_SECTOR_123              (123U)
#define EFM_SECTOR_124              (124U)
#define EFM_SECTOR_125              (125U)
#define EFM_SECTOR_126              (126U)
#define EFM_SECTOR_127              (127U)
#define EFM_SECTOR_128              (128U)
#define EFM_SECTOR_129              (129U)
#define EFM_SECTOR_130              (130U)
#define EFM_SECTOR_131              (131U)
#define EFM_SECTOR_132              (132U)
#define EFM_SECTOR_133              (133U)
#define EFM_SECTOR_134              (134U)
#define EFM_SECTOR_135              (135U)
#define EFM_SECTOR_136              (136U)
#define EFM_SECTOR_137              (137U)
#define EFM_SECTOR_138              (138U)
#define EFM_SECTOR_139              (139U)
#define EFM_SECTOR_140              (140U)
#define EFM_SECTOR_141              (141U)
#define EFM_SECTOR_142              (142U)
#define EFM_SECTOR_143              (143U)
#define EFM_SECTOR_144              (144U)
#define EFM_SECTOR_145              (145U)
#define EFM_SECTOR_146              (146U)
#define EFM_SECTOR_147              (147U)
#define EFM_SECTOR_148              (148U)
#define EFM_SECTOR_149              (149U)
#define EFM_SECTOR_150              (150U)
#define EFM_SECTOR_151              (151U)
#define EFM_SECTOR_152              (152U)
#define EFM_SECTOR_153              (153U)
#define EFM_SECTOR_154              (154U)
#define EFM_SECTOR_155              (155U)
#define EFM_SECTOR_156              (156U)
#define EFM_SECTOR_157              (157U)
#define EFM_SECTOR_158              (158U)
#define EFM_SECTOR_159              (159U)
#define EFM_SECTOR_160              (160U)
#define EFM_SECTOR_161              (161U)
#define EFM_SECTOR_162              (162U)
#define EFM_SECTOR_163              (163U)
#define EFM_SECTOR_164              (164U)
#define EFM_SECTOR_165              (165U)
#define EFM_SECTOR_166              (166U)
#define EFM_SECTOR_167              (167U)
#define EFM_SECTOR_168              (168U)
#define EFM_SECTOR_169              (169U)
#define EFM_SECTOR_170              (170U)
#define EFM_SECTOR_171              (171U)
#define EFM_SECTOR_172              (172U)
#define EFM_SECTOR_173              (173U)
#define EFM_SECTOR_174              (174U)
#define EFM_SECTOR_175              (175U)
#define EFM_SECTOR_176              (176U)
#define EFM_SECTOR_177              (177U)
#define EFM_SECTOR_178              (178U)
#define EFM_SECTOR_179              (179U)
#define EFM_SECTOR_180              (180U)
#define EFM_SECTOR_181              (181U)
#define EFM_SECTOR_182              (182U)
#define EFM_SECTOR_183              (183U)
#define EFM_SECTOR_184              (184U)
#define EFM_SECTOR_185              (185U)
#define EFM_SECTOR_186              (186U)
#define EFM_SECTOR_187              (187U)
#define EFM_SECTOR_188              (188U)
#define EFM_SECTOR_189              (189U)
#define EFM_SECTOR_190              (190U)
#define EFM_SECTOR_191              (191U)
#define EFM_SECTOR_192              (192U)
#define EFM_SECTOR_193              (193U)
#define EFM_SECTOR_194              (194U)
#define EFM_SECTOR_195              (195U)
#define EFM_SECTOR_196              (196U)
#define EFM_SECTOR_197              (197U)
#define EFM_SECTOR_198              (198U)
#define EFM_SECTOR_199              (199U)
#define EFM_SECTOR_200              (200U)
#define EFM_SECTOR_201              (201U)
#define EFM_SECTOR_202              (202U)
#define EFM_SECTOR_203              (203U)
#define EFM_SECTOR_204              (204U)
#define EFM_SECTOR_205              (205U)
#define EFM_SECTOR_206              (206U)
#define EFM_SECTOR_207              (207U)
#define EFM_SECTOR_208              (208U)
#define EFM_SECTOR_209              (209U)
#define EFM_SECTOR_210              (210U)
#define EFM_SECTOR_211              (211U)
#define EFM_SECTOR_212              (212U)
#define EFM_SECTOR_213              (213U)
#define EFM_SECTOR_214              (214U)
#define EFM_SECTOR_215              (215U)
#define EFM_SECTOR_216              (216U)
#define EFM_SECTOR_217              (217U)
#define EFM_SECTOR_218              (218U)
#define EFM_SECTOR_219              (219U)
#define EFM_SECTOR_220              (220U)
#define EFM_SECTOR_221              (221U)
#define EFM_SECTOR_222              (222U)
#define EFM_SECTOR_223              (223U)
#define EFM_SECTOR_224              (224U)
#define EFM_SECTOR_225              (225U)
#define EFM_SECTOR_226              (226U)
#define EFM_SECTOR_227              (227U)
#define EFM_SECTOR_228              (228U)
#define EFM_SECTOR_229              (229U)
#define EFM_SECTOR_230              (230U)
#define EFM_SECTOR_231              (231U)
#define EFM_SECTOR_232              (232U)
#define EFM_SECTOR_233              (233U)
#define EFM_SECTOR_234              (234U)
#define EFM_SECTOR_235              (235U)
#define EFM_SECTOR_236              (236U)
#define EFM_SECTOR_237              (237U)
#define EFM_SECTOR_238              (238U)
#define EFM_SECTOR_239              (239U)
#define EFM_SECTOR_240              (240U)
#define EFM_SECTOR_241              (241U)
#define EFM_SECTOR_242              (242U)
#define EFM_SECTOR_243              (243U)
#define EFM_SECTOR_244              (244U)
#define EFM_SECTOR_245              (245U)
#define EFM_SECTOR_246              (246U)
#define EFM_SECTOR_247              (247U)
#define EFM_SECTOR_248              (248U)
#define EFM_SECTOR_249              (249U)
#define EFM_SECTOR_250              (250U)
#define EFM_SECTOR_251              (251U)
#define EFM_SECTOR_252              (252U)
#define EFM_SECTOR_253              (253U)
#define EFM_SECTOR_254              (254U)
#define EFM_SECTOR_255              (255U)
/**
 * @}
 */

/**
 * @defgroup EFM_Wait_Cycle EFM Wait Cycle 
 * @{
 */
#define EFM_WAIT_CYCLE_0                   (0U)      /*!< Don't insert read wait cycle */
#define EFM_WAIT_CYCLE_1                   (1U)      /*!< Insert 1 read wait cycle     */
#define EFM_WAIT_CYCLE_2                   (2U)      /*!< Insert 2 read wait cycles    */
#define EFM_WAIT_CYCLE_3                   (3U)      /*!< Insert 3 read wait cycles    */
#define EFM_WAIT_CYCLE_4                   (4U)      /*!< Insert 4 read wait cycles    */
#define EFM_WAIT_CYCLE_5                   (5U)      /*!< Insert 5 read wait cycles    */
#define EFM_WAIT_CYCLE_6                   (6U)      /*!< Insert 6 read wait cycles    */
#define EFM_WAIT_CYCLE_7                   (7U)      /*!< Insert 7 read wait cycles    */
#define EFM_WAIT_CYCLE_8                   (8U)      /*!< Insert 8 read wait cycles    */
#define EFM_WAIT_CYCLE_9                   (9U)      /*!< Insert 9 read wait cycles    */
#define EFM_WAIT_CYCLE_10                  (10U)     /*!< Insert 10 read wait cycles   */
#define EFM_WAIT_CYCLE_11                  (11U)     /*!< Insert 11 read wait cycles   */
#define EFM_WAIT_CYCLE_12                  (12U)     /*!< Insert 12 read wait cycles   */
#define EFM_WAIT_CYCLE_13                  (13U)     /*!< Insert 13 read wait cycles   */
#define EFM_WAIT_CYCLE_14                  (14U)     /*!< Insert 14 read wait cycles   */
#define EFM_WAIT_CYCLE_15                  (15U)     /*!< Insert 15 read wait cycles   */
/**
 * @}
 */

/**
 * @defgroup EFM_CacheRst_Func EFM data cache reset function
 * @{
 */
#define EFM_CACHERST_ON             (EFM_FRMC_CRST)         /*!< Enable data cache reset function */
#define EFM_CACHERST_OFF            (0x0UL)                 /*!< Disable data cache reset function */
/**
 * @}
 */

/**
 * @defgroup EFM_Prefetch_Func EFM prefetch function
 * @{
 */
#define EFM_PREFETCH_ON             (EFM_FRMC_PREFE)        /*!< Enable prefetch function */
#define EFM_PREFETCH_OFF            (0x0UL)                 /*!< Disable prefetch function */
/**
 * @}
 */

/**
 * @defgroup EFM_DCache_Func EFM data cache function
 * @{
 */
#define EFM_DATACACHE_ON            (EFM_FRMC_DCACHE)       /*!< Enable data cache function */
#define EFM_DATACACHE_OFF           (0x0UL)                 /*!< Disable data cache function */
/**
 * @}
 */

/**
 * @defgroup EFM_INSCache_Func EFM instruction cache function
 * @{
 */
#define EFM_INSCACHE_ON             (EFM_FRMC_ICACHE)       /*!< Enable instruction cache function */
#define EFM_INSCACHE_OFF            (0x0UL)                 /*!< Disable instruction cache function */
/**
 * @}
 */

/**
 * @defgroup EFM_LowVolRead_Mode EFM read of low-voltage mode
 * @{
 */
#define EFM_LOWVOLREAD_ON           (EFM_FRMC_LVM)          /*!< Read of low-voltage mode */
#define EFM_LOWVOLREAD_OFF          (0x0UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Key2Lock_Status EFM key2 lock status
 * @{
 */
#define EFM_KEY2_LOCK               (EFM_FWMC_KEY2LOCK)
#define EFM_KEY2_UNLOCK             (0x0UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Key1Lock_Status EFM key1 lock status
 * @{
 */
#define EFM_KEY1_LOCK               (EFM_FWMC_KEY1LOCK)
#define EFM_KEY1_UNLOCK             (0x0UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Bus_Status EFM Bus status while flash program or erase
 * @{
 */
#define EFM_BUS_BUSY                (0x0UL)                  /*!< Bus busy while flash program or erase */
#define EFM_BUS_RELEASE             (EFM_FWMC_BUSHLDCTL)     /*!< Bus release while flash program or erase */
/**
 * @}
 */

/**
 * @defgroup EFM_OperateMode_Definition EFM program or erase mode definition
 * @{
 */
#define EFM_MODE_PROGRAMSINGLE      (0x1UL)                  /*!< Program single mode          */
#define EFM_MODE_PROGRAMREADBACK    (0x2UL)                  /*!< Program and read back mode   */
#define EFM_MODE_PROGRAMSEQUENCE    (0x3UL)                  /*!< Program sequence mode        */
#define EFM_MODE_ERASESECTOR        (0x4UL)                  /*!< Sector erase mode            */
#define EFM_MODE_ERASECHIP1         (0x5UL)                  /*!< A flash Chip erase mode      */
#define EFM_MODE_ERASEFULL          (0x6UL)                  /*!< Full erase mode    */
#define EFM_MODE_READONLY           (0x0UL)                  /*!< Read only mode               */
/**
 * @}
 */

/**
 * @defgroup EFM_Flag_definition EFM Flag definition
 * @{
 */
#define EFM_FLAG_OTPWERR0           (EFM_FSR_OTPWERR0)       /*!< EFM Flash0 otp Programming/erase error flag.       */
#define EFM_FLAG_PRTWERR0           (EFM_FSR_PRTWERR0)       /*!< EFM Flash0 write protect address error flag.       */
#define EFM_FLAG_PGSZERR0           (EFM_FSR_PGSZERR0)       /*!< EFM Flash0 programming size error flag.            */
#define EFM_FLAG_MISMTCH0           (EFM_FSR_MISMTCH0)       /*!< EFM Flash0 programming missing match error flag.   */
#define EFM_FLAG_OPTEND0            (EFM_FSR_OPTEND0)        /*!< EFM Flash0 end of operation flag.                  */
#define EFM_FLAG_CLOLERR0           (EFM_FSR_COLERR0)        /*!< EFM Flash0 read collide error flag.                */
#define EFM_FLAG_RDY0               (EFM_FSR_RDY0)           /*!< EFM Flash0 ready flag.                             */
#define EFM_FLAG_PRTWERR1           (EFM_FSR_PRTWERR1)       /*!< EFM Flash1 write protect address error flag.       */
#define EFM_FLAG_PGSZERR1           (EFM_FSR_PGSZERR1)       /*!< EFM Flash1 programming size error flag.            */
#define EFM_FLAG_MISMTCH1           (EFM_FSR_MISMTCH1)       /*!< EFM Flash1 programming missing match error flag.   */
#define EFM_FLAG_OPTEND1            (EFM_FSR_OPTEND1)        /*!< EFM Flash1 end of operation flag.                  */
#define EFM_FLAG_CLOLERR1           (EFM_FSR_COLERR1)        /*!< EFM Flash1 read collide error flag.                */
#define EFM_FLAG_RDY1               (EFM_FSR_RDY1)           /*!< EFM Flash1 ready flag.                             */

#define EFM_FLAG_CLR_OTPWERR0       (EFM_FSCLR_OTPWERRCLR0)  /*!< EFM Clear Flash0 otp Programming/erase error flag. */
#define EFM_FLAG_CLR_PRTWERR0       (EFM_FSCLR_PRTWERRCLR0)  /*!< EFM Clear Flash0 write protect address error flag. */
#define EFM_FLAG_CLR_PGSZERR0       (EFM_FSCLR_PGSZERRCLR0)  /*!< EFM Clear Flash0 programming size error flag.      */
#define EFM_FLAG_CLR_MISMTCH0       (EFM_FSCLR_MISMTCHCLR0)  /*!< EFM Clear Flash0 programming miss match error flag.*/
#define EFM_FLAG_CLR_OPTEND0        (EFM_FSCLR_OPTENDCLR0)   /*!< EFM Clear Flash0 end of operation flag.            */
#define EFM_FLAG_CLR_CLOLERR0       (EFM_FSCLR_COLERRCLR0)   /*!< EFM Clear Flash0 read collide error flag.          */
#define EFM_FLAG_CLR_PRTWERR1       (EFM_FSCLR_PRTWERRCLR1)  /*!< EFM Clear Flash1 write protect address error flag. */
#define EFM_FLAG_CLR_PGSZERR1       (EFM_FSCLR_PGSZERRCLR1)  /*!< EFM Clear Flash1 programming size error flag.      */
#define EFM_FLAG_CLR_MISMTCH1       (EFM_FSCLR_MISMTCHCLR1)  /*!< EFM Clear Flash1 programming miss match error flag.*/
#define EFM_FLAG_CLR_OPTEND1        (EFM_FSCLR_OPTENDCLR1)   /*!< EFM Clear Flash1 end of operation flag.            */
#define EFM_FLAG_CLR_CLOLERR1       (EFM_FSCLR_COLERRCLR1)   /*!< EFM Clear Flash1 read collide error flag.          */
/**
 * @}
 */

/**
 * @defgroup EFM_Interrupt_definition EFM Interrupt definition
 * @{
 */
#define EFM_INT_PEERR               (EFM_FITE_PEERRITE)      /*!< Program/erase error Interrupt source    */
#define EFM_INT_OPTEND              (EFM_FITE_OPTENDITE)     /*!< End of EFM operation Interrupt source   */
#define EFM_INT_RDCOLERR            (EFM_FITE_COLERRITE)     /*!< Read collide error Interrupt source     */

#define EFM_INT_MASK                (EFM_FITE_PEERRITE  |  \
                                    EFM_FITE_OPTENDITE  |  \
                                    EFM_FITE_COLERRITE)      /*!< Program/erase error and End of EFM operation \
                                                                  and Read collide error Interrupt source */
/**
 * @}
 */

/**
 * @defgroup EFM_WriteLock_Definition EFM Write protect lock definition
 * @{
 */
#define EFM_WRLOCK0                  (EFM_WLOCK_WLOCK0)       /*!< F0NWPRT0 controlled sector lock   */
#define EFM_WRLOCK1                  (EFM_WLOCK_WLOCK1)       /*!< F0NWPRT1 controlled sector lock   */
#define EFM_WRLOCK2                  (EFM_WLOCK_WLOCK2)       /*!< F0NWPRT2 controlled sector lock   */
#define EFM_WRLOCK3                  (EFM_WLOCK_WLOCK3)       /*!< F0NWPRT3 controlled sector lock   */
#define EFM_WRLOCK4                  (EFM_WLOCK_WLOCK4)       /*!< F1NWPRT0 controlled sector lock   */
#define EFM_WRLOCK5                  (EFM_WLOCK_WLOCK5)       /*!< F1NWPRT1 controlled sector lock   */
#define EFM_WRLOCK6                  (EFM_WLOCK_WLOCK6)       /*!< F1NWPRT2 controlled sector lock   */
#define EFM_WRLOCK7                  (EFM_WLOCK_WLOCK7)       /*!< F1NWPRT3 controlled sector lock   */
/**
 * @}
 */


/**
 * @defgroup EFM_Keys EFM Keys
 * @{
 */
#define EFM_SECRET_KEY1              (0x0123U)
#define EFM_SECRET_KEY2              (0x3210U)
/**
 * @}
 */

/**
 * @defgroup EFM_Status EFM Status
 * @{
 */
#define EFM_FLASH0_ACT_FLASH1_ACT      (0x00000000UL)  /*!< Flash 0 and 1 activity */
#define EFM_FLASH0_STP_FLASH1_ACT      (0x00000001UL)  /*!< Flash 0 stop,Flash 1 activity */
#define EFM_FLASH0_ACT_FLASH1_STP      (0x00000002UL)  /*!< Flash 0 activity,Flash 1 stop */
#define EFM_FLASH0_STP_FLASH1_STP      (0x00000003UL)  /*!< Flash 0 and 1 stop */
/**
 * @}
 */

/**
 * @defgroup EFM_ProtectReg_definition EFM Write protect for register definition 
 * @{
 */
#define EFM_PROTECT_FWMC            (0U)
#define EFM_PROTECT_OTP             (1U)
/**
 * @}
 */


/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup EFM_Global_Functions
 * @{
 */

/**
 * @brief  EFM Protect Unlock.
 * @param  None
 * @retval None
 */

__STATIC_INLINE void EFM_Unlock(void)
{
    WRITE_REG16(M4_EFM->FAPRT, EFM_SECRET_KEY1);
    WRITE_REG16(M4_EFM->FAPRT, EFM_SECRET_KEY2);
}

/**
 * @brief  EFM Protect Lock.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EFM_Lock(void)
{
    WRITE_REG16(M4_EFM->FAPRT, 0x1111U);
}

void EFM_FWMC_Unlock(void);
void EFM_FWMC_Lock(void);
void EFM_OTP_WP_Unlock(void);
void EFM_OTP_WP_Lock(void);

void EFM_Cmd(uint32_t u32EfmStatus);
void EFM_SetWaitCycle(uint32_t u32WaitCycle);
void EFM_SetBusStatus(uint32_t u32Status);
void EFM_DataCacheCmd(en_functional_state_t enNewState);
void EFM_InsCacheCmd(en_functional_state_t enNewState);
void EFM_DataCacheRstCmd(en_functional_state_t enNewState);
void EFM_PrefetchCmd(en_functional_state_t enNewState);
void EFM_InterruptCmd(uint32_t u32EfmInt, en_functional_state_t enNewState);
void EFM_LowVolReadCmd(en_functional_state_t enNewState);
void EFM_SectorRegLock(uint32_t u32EfmRegLock);
void EFM_ClearFlag(uint32_t u32Flag);
void EFM_SectorCmd_Single(uint8_t u8SectorNum, en_functional_state_t enNewState);
en_result_t EFM_StructInit(stc_efm_cfg_t *pstcEfmCfg);
en_result_t EFM_Init(const stc_efm_cfg_t *pstcEfmCfg);
en_result_t EFM_SectorCmd_Sequential(uint32_t u32StartAddr, uint16_t u16SectorCnt,
                                      en_functional_state_t enNewState);
en_result_t EFM_SingleProgram(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_ProgramReadBack(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_SequenceProgram(uint32_t u32Addr, uint32_t u32Len, const uint32_t *pu32Buf);
en_result_t EFM_SectorErase(uint32_t u32Addr);
en_result_t EFM_OTPLock(uint32_t u32Addr);
en_result_t EFM_ChipErase(uint32_t EraseMode, uint32_t u32Addr);
en_result_t EFM_SwapCmd(en_functional_state_t enNewState);
en_result_t EFM_SetOperateMode(uint32_t u32PgmMode);

en_flag_status_t EFM_GetFlagStatus(uint32_t u32Flag);
void EFM_GetUID(stc_efm_unique_id_t *stcUID);
uint32_t EFM_GetCID(void);
/**
 * @}
 */

#endif /* DDL_EFM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_EFM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
