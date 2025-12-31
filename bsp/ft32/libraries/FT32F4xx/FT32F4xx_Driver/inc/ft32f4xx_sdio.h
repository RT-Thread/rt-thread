/**
  ******************************************************************************
  * @file               ft32f4xx_sdio.h
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_SDIO_H
#define __FT32F4XX_SDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/*!< Includes ----------------------------------------------------------------*/
#include "ft32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SDIO_CTRL_Register **/
/** @defgroup SDIO_OD_PULLUP
  * @{
  */
#define SDIO_OD_PULLUP_DISABLE             ((uint32_t)0x00)
#define SDIO_OD_PULLUP_ENABLE              SDIO_CTRL_ENABLE_OD_PULLUP

#define IS_SDIO_OD_PULLUP(PULLUP) (((PULLUP) == SDIO_OD_PULLUP_DISABLE) || \
                                   ((PULLUP) == SDIO_OD_PULLUP_ENABLE))

/** @defgroup SDIO_Read_Wait
  * @{
  */
#define SDIO_READ_WAIT_DISABLE            ((uint32_t)0x00)
#define SDIO_READ_WAIT_ENABLE             SDIO_CTRL_READ_WAIT

#define IS_SDIO_READWAIT_MODE(MODE) (((MODE) == SDIO_READ_WAIT_DISABLE) || \
                                     ((MODE) == SDIO_READ_WAIT_ENABLE))

/** @defgroup SDIO_dma_enable
  * @{
  */
#define SDIO_DMA_ENABLE_DISABLE            ((uint32_t)0x00)
#define SDIO_DMA_ENABLE_ENABLE             SDIO_CTRL_DMA_ENABLE

#define IS_SDIO_DMA_ENABLE(ENABLE) (((ENABLE) == SDIO_DMA_ENABLE_DISABLE) || \
                                    ((ENABLE) == SDIO_DMA_ENABLE_ENABLE))

/** @defgroup SDIO_INT_ENABLE
  * @{
  */
#define SDIO_INT_ENABLE_DISABLE            ((uint32_t)0x00)
#define SDIO_INT_ENABLE_ENABLE             SDIO_CTRL_INT_ENABLE

#define IS_SDIO_INT_ENABLE(ENABLE) (((ENABLE) == SDIO_INT_ENABLE_DISABLE)    || \
                                    ((ENABLE) == SDIO_INT_ENABLE_ENABLE))

/** @defgroup SDIO_FIFO_RESET
  * @{
  */
#define SDIO_FIFO_RESET_DISABLE            ((uint32_t)0x00)
#define SDIO_FIFO_RESET_ENABLE             SDIO_CTRL_FIFO_RESET

#define IS_SDIO_FIFO_RESET(RESET)  (((RESET) == SDIO_FIFO_RESET_DISABLE)    || \
                                    ((RESET) == SDIO_FIFO_RESET_ENABLE))


/** @defgroup SDIO_CONTROLLER_RESET
  * @{
  */
#define SDIO_CONTROLLER_RESET_DISABLE            ((uint32_t)0x00)
#define SDIO_CONTROLLER_RESET_ENABLE             SDIO_CTRL_CONTROLLER_RESET

#define IS_SDIO_CONTROLLER_RESET(RESET) (((RESET) == SDIO_CONTROLLER_RESET_DISABLE)    || \
                                         ((RESET) == SDIO_CONTROLLER_RESET_ENABLE))

/** @defgroup SDIO_PWREN_Register **/
/** @defgroup SDIO_Power_ON
  * @{
  */
#define SDIO_POWER_ON_DISABLE         ((uint32_t)0x00)
#define SDIO_POWER_ON_ENABLE          SDIO_PWREN_POWER_ENABLE_0

#define IS_SDIO_POWER_ON(ON) (((ON) == SDIO_POWER_ON_DISABLE) || \
                              ((ON) == SDIO_POWER_ON_ENABLE))

/** @defgroup SDIO_CLKDIV_Register **/
/** @defgroup SDIO_Clock_Division
  * @{
  */
#define SDIO_CLKDIV1           ((uint32_t)0x00)
#define SDIO_CLKDIV2           ((uint32_t)0x01)
#define SDIO_CLKDIV4           ((uint32_t)0x02)
#define SDIO_CLKDIV6           ((uint32_t)0x03)
#define SDIO_CLKDIV8           ((uint32_t)0x04)
#define SDIO_CLKDIV10          ((uint32_t)0x05)
#define SDIO_CLKDIV12          ((uint32_t)0x06)
#define SDIO_CLKDIV14          ((uint32_t)0x07)
#define SDIO_CLKDIV16          ((uint32_t)0x08)
#define SDIO_CLKDIV18          ((uint32_t)0x09)
#define SDIO_CLKDIV20          ((uint32_t)0x0a)
#define SDIO_CLKDIV22          ((uint32_t)0x0b)
#define SDIO_CLKDIV24          ((uint32_t)0x0c)
#define SDIO_CLKDIV26          ((uint32_t)0x0d)
#define SDIO_CLKDIV28          ((uint32_t)0x0e)
#define SDIO_CLKDIV30          ((uint32_t)0x0f)
#define SDIO_CLKDIV32          ((uint32_t)0x10)
#define SDIO_CLKDIV34          ((uint32_t)0x11)
#define SDIO_CLKDIV36          ((uint32_t)0x12)
#define SDIO_CLKDIV38          ((uint32_t)0x13)
#define SDIO_CLKDIV40          ((uint32_t)0x14)
#define SDIO_CLKDIV42          ((uint32_t)0x15)
#define SDIO_CLKDIV44          ((uint32_t)0x16)
#define SDIO_CLKDIV46          ((uint32_t)0x17)
#define SDIO_CLKDIV48          ((uint32_t)0x18)
#define SDIO_CLKDIV50          ((uint32_t)0x19)
#define SDIO_CLKDIV52          ((uint32_t)0x1a)
#define SDIO_CLKDIV54          ((uint32_t)0x1b)
#define SDIO_CLKDIV56          ((uint32_t)0x1c)
#define SDIO_CLKDIV58          ((uint32_t)0x1d)
#define SDIO_CLKDIV60          ((uint32_t)0x1e)
#define SDIO_CLKDIV62          ((uint32_t)0x1f)
#define SDIO_CLKDIV64          ((uint32_t)0x20)
#define SDIO_CLKDIV66          ((uint32_t)0x21)
#define SDIO_CLKDIV68          ((uint32_t)0x22)
#define SDIO_CLKDIV70          ((uint32_t)0x23)
#define SDIO_CLKDIV72          ((uint32_t)0x24)
#define SDIO_CLKDIV74          ((uint32_t)0x25)
#define SDIO_CLKDIV76          ((uint32_t)0x26)
#define SDIO_CLKDIV78          ((uint32_t)0x27)
#define SDIO_CLKDIV80          ((uint32_t)0x28)
#define SDIO_CLKDIV82          ((uint32_t)0x29)
#define SDIO_CLKDIV84          ((uint32_t)0x2a)
#define SDIO_CLKDIV86          ((uint32_t)0x2b)
#define SDIO_CLKDIV88          ((uint32_t)0x2c)
#define SDIO_CLKDIV90          ((uint32_t)0x2d)
#define SDIO_CLKDIV92          ((uint32_t)0x2e)
#define SDIO_CLKDIV94          ((uint32_t)0x2f)
#define SDIO_CLKDIV96          ((uint32_t)0x30)
#define SDIO_CLKDIV98          ((uint32_t)0x31)
#define SDIO_CLKDIV100         ((uint32_t)0x32)
#define SDIO_CLKDIV102         ((uint32_t)0x33)
#define SDIO_CLKDIV104         ((uint32_t)0x34)
#define SDIO_CLKDIV106         ((uint32_t)0x35)
#define SDIO_CLKDIV108         ((uint32_t)0x36)
#define SDIO_CLKDIV110         ((uint32_t)0x37)
#define SDIO_CLKDIV112         ((uint32_t)0x38)
#define SDIO_CLKDIV114         ((uint32_t)0x39)
#define SDIO_CLKDIV116         ((uint32_t)0x3a)
#define SDIO_CLKDIV118         ((uint32_t)0x3b)
#define SDIO_CLKDIV120         ((uint32_t)0x3c)
#define SDIO_CLKDIV122         ((uint32_t)0x3d)
#define SDIO_CLKDIV124         ((uint32_t)0x3e)
#define SDIO_CLKDIV126         ((uint32_t)0x3f)
#define SDIO_CLKDIV128         ((uint32_t)0x40)
#define SDIO_CLKDIV130         ((uint32_t)0x41)
#define SDIO_CLKDIV132         ((uint32_t)0x42)
#define SDIO_CLKDIV134         ((uint32_t)0x43)
#define SDIO_CLKDIV136         ((uint32_t)0x44)
#define SDIO_CLKDIV138         ((uint32_t)0x45)
#define SDIO_CLKDIV140         ((uint32_t)0x46)
#define SDIO_CLKDIV142         ((uint32_t)0x47)
#define SDIO_CLKDIV144         ((uint32_t)0x48)
#define SDIO_CLKDIV146         ((uint32_t)0x49)
#define SDIO_CLKDIV148         ((uint32_t)0x4a)
#define SDIO_CLKDIV150         ((uint32_t)0x4b)
#define SDIO_CLKDIV152         ((uint32_t)0x4c)
#define SDIO_CLKDIV154         ((uint32_t)0x4d)
#define SDIO_CLKDIV156         ((uint32_t)0x4e)
#define SDIO_CLKDIV158         ((uint32_t)0x4f)
#define SDIO_CLKDIV160         ((uint32_t)0x50)
#define SDIO_CLKDIV162         ((uint32_t)0x51)
#define SDIO_CLKDIV164         ((uint32_t)0x52)
#define SDIO_CLKDIV166         ((uint32_t)0x53)
#define SDIO_CLKDIV168         ((uint32_t)0x54)
#define SDIO_CLKDIV170         ((uint32_t)0x55)
#define SDIO_CLKDIV172         ((uint32_t)0x56)
#define SDIO_CLKDIV174         ((uint32_t)0x57)
#define SDIO_CLKDIV176         ((uint32_t)0x58)
#define SDIO_CLKDIV178         ((uint32_t)0x59)
#define SDIO_CLKDIV180         ((uint32_t)0x5a)
#define SDIO_CLKDIV182         ((uint32_t)0x5b)
#define SDIO_CLKDIV184         ((uint32_t)0x5c)
#define SDIO_CLKDIV186         ((uint32_t)0x5d)
#define SDIO_CLKDIV188         ((uint32_t)0x5e)
#define SDIO_CLKDIV190         ((uint32_t)0x5f)
#define SDIO_CLKDIV192         ((uint32_t)0x60)
#define SDIO_CLKDIV194         ((uint32_t)0x61)
#define SDIO_CLKDIV196         ((uint32_t)0x62)
#define SDIO_CLKDIV198         ((uint32_t)0x63)
#define SDIO_CLKDIV200         ((uint32_t)0x64)
#define SDIO_CLKDIV202         ((uint32_t)0x65)
#define SDIO_CLKDIV204         ((uint32_t)0x66)
#define SDIO_CLKDIV206         ((uint32_t)0x67)
#define SDIO_CLKDIV208         ((uint32_t)0x68)
#define SDIO_CLKDIV210         ((uint32_t)0x69)
#define SDIO_CLKDIV212         ((uint32_t)0x6a)
#define SDIO_CLKDIV214         ((uint32_t)0x6b)
#define SDIO_CLKDIV216         ((uint32_t)0x6c)
#define SDIO_CLKDIV218         ((uint32_t)0x6d)
#define SDIO_CLKDIV220         ((uint32_t)0x6e)
#define SDIO_CLKDIV222         ((uint32_t)0x6f)
#define SDIO_CLKDIV224         ((uint32_t)0x70)
#define SDIO_CLKDIV226         ((uint32_t)0x71)
#define SDIO_CLKDIV228         ((uint32_t)0x72)
#define SDIO_CLKDIV230         ((uint32_t)0x73)
#define SDIO_CLKDIV232         ((uint32_t)0x74)
#define SDIO_CLKDIV234         ((uint32_t)0x75)
#define SDIO_CLKDIV236         ((uint32_t)0x76)
#define SDIO_CLKDIV238         ((uint32_t)0x77)
#define SDIO_CLKDIV240         ((uint32_t)0x78)
#define SDIO_CLKDIV242         ((uint32_t)0x79)
#define SDIO_CLKDIV244         ((uint32_t)0x7a)
#define SDIO_CLKDIV246         ((uint32_t)0x7b)
#define SDIO_CLKDIV248         ((uint32_t)0x7c)
#define SDIO_CLKDIV250         ((uint32_t)0x7d)
#define SDIO_CLKDIV252         ((uint32_t)0x7e)
#define SDIO_CLKDIV254         ((uint32_t)0x7f)
#define SDIO_CLKDIV256         ((uint32_t)0x80)
#define SDIO_CLKDIV258         ((uint32_t)0x81)
#define SDIO_CLKDIV260         ((uint32_t)0x82)
#define SDIO_CLKDIV262         ((uint32_t)0x83)
#define SDIO_CLKDIV264         ((uint32_t)0x84)
#define SDIO_CLKDIV266         ((uint32_t)0x85)
#define SDIO_CLKDIV268         ((uint32_t)0x86)
#define SDIO_CLKDIV270         ((uint32_t)0x87)
#define SDIO_CLKDIV272         ((uint32_t)0x88)
#define SDIO_CLKDIV274         ((uint32_t)0x89)
#define SDIO_CLKDIV276         ((uint32_t)0x8a)
#define SDIO_CLKDIV278         ((uint32_t)0x8b)
#define SDIO_CLKDIV280         ((uint32_t)0x8c)
#define SDIO_CLKDIV282         ((uint32_t)0x8d)
#define SDIO_CLKDIV284         ((uint32_t)0x8e)
#define SDIO_CLKDIV286         ((uint32_t)0x8f)
#define SDIO_CLKDIV288         ((uint32_t)0x90)
#define SDIO_CLKDIV290         ((uint32_t)0x91)
#define SDIO_CLKDIV292         ((uint32_t)0x92)
#define SDIO_CLKDIV294         ((uint32_t)0x93)
#define SDIO_CLKDIV296         ((uint32_t)0x94)
#define SDIO_CLKDIV298         ((uint32_t)0x95)
#define SDIO_CLKDIV300         ((uint32_t)0x96)
#define SDIO_CLKDIV302         ((uint32_t)0x97)
#define SDIO_CLKDIV304         ((uint32_t)0x98)
#define SDIO_CLKDIV306         ((uint32_t)0x99)
#define SDIO_CLKDIV308         ((uint32_t)0x9a)
#define SDIO_CLKDIV310         ((uint32_t)0x9b)
#define SDIO_CLKDIV312         ((uint32_t)0x9c)
#define SDIO_CLKDIV314         ((uint32_t)0x9d)
#define SDIO_CLKDIV316         ((uint32_t)0x9e)
#define SDIO_CLKDIV318         ((uint32_t)0x9f)
#define SDIO_CLKDIV320         ((uint32_t)0xa0)
#define SDIO_CLKDIV322         ((uint32_t)0xa1)
#define SDIO_CLKDIV324         ((uint32_t)0xa2)
#define SDIO_CLKDIV326         ((uint32_t)0xa3)
#define SDIO_CLKDIV328         ((uint32_t)0xa4)
#define SDIO_CLKDIV330         ((uint32_t)0xa5)
#define SDIO_CLKDIV332         ((uint32_t)0xa6)
#define SDIO_CLKDIV334         ((uint32_t)0xa7)
#define SDIO_CLKDIV336         ((uint32_t)0xa8)
#define SDIO_CLKDIV338         ((uint32_t)0xa9)
#define SDIO_CLKDIV340         ((uint32_t)0xaa)
#define SDIO_CLKDIV342         ((uint32_t)0xab)
#define SDIO_CLKDIV344         ((uint32_t)0xac)
#define SDIO_CLKDIV346         ((uint32_t)0xad)
#define SDIO_CLKDIV348         ((uint32_t)0xae)
#define SDIO_CLKDIV350         ((uint32_t)0xaf)
#define SDIO_CLKDIV352         ((uint32_t)0xb0)
#define SDIO_CLKDIV354         ((uint32_t)0xb1)
#define SDIO_CLKDIV356         ((uint32_t)0xb2)
#define SDIO_CLKDIV358         ((uint32_t)0xb3)
#define SDIO_CLKDIV360         ((uint32_t)0xb4)
#define SDIO_CLKDIV362         ((uint32_t)0xb5)
#define SDIO_CLKDIV364         ((uint32_t)0xb6)
#define SDIO_CLKDIV366         ((uint32_t)0xb7)
#define SDIO_CLKDIV368         ((uint32_t)0xb8)
#define SDIO_CLKDIV370         ((uint32_t)0xb9)
#define SDIO_CLKDIV372         ((uint32_t)0xba)
#define SDIO_CLKDIV374         ((uint32_t)0xbb)
#define SDIO_CLKDIV376         ((uint32_t)0xbc)
#define SDIO_CLKDIV378         ((uint32_t)0xbd)
#define SDIO_CLKDIV380         ((uint32_t)0xbe)
#define SDIO_CLKDIV382         ((uint32_t)0xbf)
#define SDIO_CLKDIV384         ((uint32_t)0xc0)
#define SDIO_CLKDIV386         ((uint32_t)0xc1)
#define SDIO_CLKDIV388         ((uint32_t)0xc2)
#define SDIO_CLKDIV390         ((uint32_t)0xc3)
#define SDIO_CLKDIV392         ((uint32_t)0xc4)
#define SDIO_CLKDIV394         ((uint32_t)0xc5)
#define SDIO_CLKDIV396         ((uint32_t)0xc6)
#define SDIO_CLKDIV398         ((uint32_t)0xc7)
#define SDIO_CLKDIV400         ((uint32_t)0xc8)
#define SDIO_CLKDIV402         ((uint32_t)0xc9)
#define SDIO_CLKDIV404         ((uint32_t)0xca)
#define SDIO_CLKDIV406         ((uint32_t)0xcb)
#define SDIO_CLKDIV408         ((uint32_t)0xcc)
#define SDIO_CLKDIV410         ((uint32_t)0xcd)
#define SDIO_CLKDIV412         ((uint32_t)0xce)
#define SDIO_CLKDIV414         ((uint32_t)0xcf)
#define SDIO_CLKDIV416         ((uint32_t)0xd0)
#define SDIO_CLKDIV418         ((uint32_t)0xd1)
#define SDIO_CLKDIV420         ((uint32_t)0xd2)
#define SDIO_CLKDIV422         ((uint32_t)0xd3)
#define SDIO_CLKDIV424         ((uint32_t)0xd4)
#define SDIO_CLKDIV426         ((uint32_t)0xd5)
#define SDIO_CLKDIV428         ((uint32_t)0xd6)
#define SDIO_CLKDIV430         ((uint32_t)0xd7)
#define SDIO_CLKDIV432         ((uint32_t)0xd8)
#define SDIO_CLKDIV434         ((uint32_t)0xd9)
#define SDIO_CLKDIV436         ((uint32_t)0xda)
#define SDIO_CLKDIV438         ((uint32_t)0xdb)
#define SDIO_CLKDIV440         ((uint32_t)0xdc)
#define SDIO_CLKDIV442         ((uint32_t)0xdd)
#define SDIO_CLKDIV444         ((uint32_t)0xde)
#define SDIO_CLKDIV446         ((uint32_t)0xdf)
#define SDIO_CLKDIV448         ((uint32_t)0xe0)
#define SDIO_CLKDIV450         ((uint32_t)0xe1)
#define SDIO_CLKDIV452         ((uint32_t)0xe2)
#define SDIO_CLKDIV454         ((uint32_t)0xe3)
#define SDIO_CLKDIV456         ((uint32_t)0xe4)
#define SDIO_CLKDIV458         ((uint32_t)0xe5)
#define SDIO_CLKDIV460         ((uint32_t)0xe6)
#define SDIO_CLKDIV462         ((uint32_t)0xe7)
#define SDIO_CLKDIV464         ((uint32_t)0xe8)
#define SDIO_CLKDIV466         ((uint32_t)0xe9)
#define SDIO_CLKDIV468         ((uint32_t)0xea)
#define SDIO_CLKDIV470         ((uint32_t)0xeb)
#define SDIO_CLKDIV472         ((uint32_t)0xec)
#define SDIO_CLKDIV474         ((uint32_t)0xed)
#define SDIO_CLKDIV476         ((uint32_t)0xee)
#define SDIO_CLKDIV478         ((uint32_t)0xef)
#define SDIO_CLKDIV480         ((uint32_t)0xf0)
#define SDIO_CLKDIV482         ((uint32_t)0xf1)
#define SDIO_CLKDIV484         ((uint32_t)0xf2)
#define SDIO_CLKDIV486         ((uint32_t)0xf3)
#define SDIO_CLKDIV488         ((uint32_t)0xf4)
#define SDIO_CLKDIV490         ((uint32_t)0xf5)
#define SDIO_CLKDIV492         ((uint32_t)0xf6)
#define SDIO_CLKDIV494         ((uint32_t)0xf7)
#define SDIO_CLKDIV496         ((uint32_t)0xf8)
#define SDIO_CLKDIV498         ((uint32_t)0xf9)
#define SDIO_CLKDIV500         ((uint32_t)0xfa)
#define SDIO_CLKDIV502         ((uint32_t)0xfb)
#define SDIO_CLKDIV504         ((uint32_t)0xfc)
#define SDIO_CLKDIV506         ((uint32_t)0xfd)
#define SDIO_CLKDIV508         ((uint32_t)0xfe)
#define SDIO_CLKDIV510         ((uint32_t)0xff)

#define IS_SDIO_CLKDIV(CLKDIV)     (((CLKDIV) == SDIO_CLKDIV1  ) || \
                                    ((CLKDIV) == SDIO_CLKDIV2  ) || \
                                    ((CLKDIV) == SDIO_CLKDIV4  ) || \
                                    ((CLKDIV) == SDIO_CLKDIV6  ) || \
                                    ((CLKDIV) == SDIO_CLKDIV8  ) || \
                                    ((CLKDIV) == SDIO_CLKDIV10 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV12 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV14 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV16 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV18 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV20 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV22 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV24 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV26 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV28 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV30 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV32 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV34 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV36 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV38 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV40 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV42 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV44 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV46 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV48 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV50 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV52 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV54 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV56 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV58 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV60 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV62 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV64 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV66 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV68 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV70 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV72 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV74 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV76 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV78 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV80 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV82 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV84 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV86 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV88 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV90 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV92 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV94 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV96 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV98 ) || \
                                    ((CLKDIV) == SDIO_CLKDIV100) || \
                                    ((CLKDIV) == SDIO_CLKDIV102) || \
                                    ((CLKDIV) == SDIO_CLKDIV104) || \
                                    ((CLKDIV) == SDIO_CLKDIV106) || \
                                    ((CLKDIV) == SDIO_CLKDIV108) || \
                                    ((CLKDIV) == SDIO_CLKDIV110) || \
                                    ((CLKDIV) == SDIO_CLKDIV112) || \
                                    ((CLKDIV) == SDIO_CLKDIV114) || \
                                    ((CLKDIV) == SDIO_CLKDIV116) || \
                                    ((CLKDIV) == SDIO_CLKDIV118) || \
                                    ((CLKDIV) == SDIO_CLKDIV120) || \
                                    ((CLKDIV) == SDIO_CLKDIV122) || \
                                    ((CLKDIV) == SDIO_CLKDIV124) || \
                                    ((CLKDIV) == SDIO_CLKDIV126) || \
                                    ((CLKDIV) == SDIO_CLKDIV128) || \
                                    ((CLKDIV) == SDIO_CLKDIV130) || \
                                    ((CLKDIV) == SDIO_CLKDIV132) || \
                                    ((CLKDIV) == SDIO_CLKDIV134) || \
                                    ((CLKDIV) == SDIO_CLKDIV136) || \
                                    ((CLKDIV) == SDIO_CLKDIV138) || \
                                    ((CLKDIV) == SDIO_CLKDIV140) || \
                                    ((CLKDIV) == SDIO_CLKDIV142) || \
                                    ((CLKDIV) == SDIO_CLKDIV144) || \
                                    ((CLKDIV) == SDIO_CLKDIV146) || \
                                    ((CLKDIV) == SDIO_CLKDIV148) || \
                                    ((CLKDIV) == SDIO_CLKDIV150) || \
                                    ((CLKDIV) == SDIO_CLKDIV152) || \
                                    ((CLKDIV) == SDIO_CLKDIV154) || \
                                    ((CLKDIV) == SDIO_CLKDIV156) || \
                                    ((CLKDIV) == SDIO_CLKDIV158) || \
                                    ((CLKDIV) == SDIO_CLKDIV160) || \
                                    ((CLKDIV) == SDIO_CLKDIV162) || \
                                    ((CLKDIV) == SDIO_CLKDIV164) || \
                                    ((CLKDIV) == SDIO_CLKDIV166) || \
                                    ((CLKDIV) == SDIO_CLKDIV168) || \
                                    ((CLKDIV) == SDIO_CLKDIV170) || \
                                    ((CLKDIV) == SDIO_CLKDIV172) || \
                                    ((CLKDIV) == SDIO_CLKDIV174) || \
                                    ((CLKDIV) == SDIO_CLKDIV176) || \
                                    ((CLKDIV) == SDIO_CLKDIV178) || \
                                    ((CLKDIV) == SDIO_CLKDIV180) || \
                                    ((CLKDIV) == SDIO_CLKDIV182) || \
                                    ((CLKDIV) == SDIO_CLKDIV184) || \
                                    ((CLKDIV) == SDIO_CLKDIV186) || \
                                    ((CLKDIV) == SDIO_CLKDIV188) || \
                                    ((CLKDIV) == SDIO_CLKDIV190) || \
                                    ((CLKDIV) == SDIO_CLKDIV192) || \
                                    ((CLKDIV) == SDIO_CLKDIV194) || \
                                    ((CLKDIV) == SDIO_CLKDIV196) || \
                                    ((CLKDIV) == SDIO_CLKDIV198) || \
                                    ((CLKDIV) == SDIO_CLKDIV200) || \
                                    ((CLKDIV) == SDIO_CLKDIV202) || \
                                    ((CLKDIV) == SDIO_CLKDIV204) || \
                                    ((CLKDIV) == SDIO_CLKDIV206) || \
                                    ((CLKDIV) == SDIO_CLKDIV208) || \
                                    ((CLKDIV) == SDIO_CLKDIV210) || \
                                    ((CLKDIV) == SDIO_CLKDIV212) || \
                                    ((CLKDIV) == SDIO_CLKDIV214) || \
                                    ((CLKDIV) == SDIO_CLKDIV216) || \
                                    ((CLKDIV) == SDIO_CLKDIV218) || \
                                    ((CLKDIV) == SDIO_CLKDIV220) || \
                                    ((CLKDIV) == SDIO_CLKDIV222) || \
                                    ((CLKDIV) == SDIO_CLKDIV224) || \
                                    ((CLKDIV) == SDIO_CLKDIV226) || \
                                    ((CLKDIV) == SDIO_CLKDIV228) || \
                                    ((CLKDIV) == SDIO_CLKDIV230) || \
                                    ((CLKDIV) == SDIO_CLKDIV232) || \
                                    ((CLKDIV) == SDIO_CLKDIV234) || \
                                    ((CLKDIV) == SDIO_CLKDIV236) || \
                                    ((CLKDIV) == SDIO_CLKDIV238) || \
                                    ((CLKDIV) == SDIO_CLKDIV240) || \
                                    ((CLKDIV) == SDIO_CLKDIV242) || \
                                    ((CLKDIV) == SDIO_CLKDIV244) || \
                                    ((CLKDIV) == SDIO_CLKDIV246) || \
                                    ((CLKDIV) == SDIO_CLKDIV248) || \
                                    ((CLKDIV) == SDIO_CLKDIV250) || \
                                    ((CLKDIV) == SDIO_CLKDIV252) || \
                                    ((CLKDIV) == SDIO_CLKDIV254) || \
                                    ((CLKDIV) == SDIO_CLKDIV256) || \
                                    ((CLKDIV) == SDIO_CLKDIV258) || \
                                    ((CLKDIV) == SDIO_CLKDIV260) || \
                                    ((CLKDIV) == SDIO_CLKDIV262) || \
                                    ((CLKDIV) == SDIO_CLKDIV264) || \
                                    ((CLKDIV) == SDIO_CLKDIV266) || \
                                    ((CLKDIV) == SDIO_CLKDIV268) || \
                                    ((CLKDIV) == SDIO_CLKDIV270) || \
                                    ((CLKDIV) == SDIO_CLKDIV272) || \
                                    ((CLKDIV) == SDIO_CLKDIV274) || \
                                    ((CLKDIV) == SDIO_CLKDIV276) || \
                                    ((CLKDIV) == SDIO_CLKDIV278) || \
                                    ((CLKDIV) == SDIO_CLKDIV280) || \
                                    ((CLKDIV) == SDIO_CLKDIV282) || \
                                    ((CLKDIV) == SDIO_CLKDIV284) || \
                                    ((CLKDIV) == SDIO_CLKDIV286) || \
                                    ((CLKDIV) == SDIO_CLKDIV288) || \
                                    ((CLKDIV) == SDIO_CLKDIV290) || \
                                    ((CLKDIV) == SDIO_CLKDIV282) || \
                                    ((CLKDIV) == SDIO_CLKDIV294) || \
                                    ((CLKDIV) == SDIO_CLKDIV296) || \
                                    ((CLKDIV) == SDIO_CLKDIV298) || \
                                    ((CLKDIV) == SDIO_CLKDIV300) || \
                                    ((CLKDIV) == SDIO_CLKDIV302) || \
                                    ((CLKDIV) == SDIO_CLKDIV304) || \
                                    ((CLKDIV) == SDIO_CLKDIV306) || \
                                    ((CLKDIV) == SDIO_CLKDIV308) || \
                                    ((CLKDIV) == SDIO_CLKDIV310) || \
                                    ((CLKDIV) == SDIO_CLKDIV312) || \
                                    ((CLKDIV) == SDIO_CLKDIV314) || \
                                    ((CLKDIV) == SDIO_CLKDIV316) || \
                                    ((CLKDIV) == SDIO_CLKDIV318) || \
                                    ((CLKDIV) == SDIO_CLKDIV320) || \
                                    ((CLKDIV) == SDIO_CLKDIV322) || \
                                    ((CLKDIV) == SDIO_CLKDIV324) || \
                                    ((CLKDIV) == SDIO_CLKDIV326) || \
                                    ((CLKDIV) == SDIO_CLKDIV328) || \
                                    ((CLKDIV) == SDIO_CLKDIV330) || \
                                    ((CLKDIV) == SDIO_CLKDIV332) || \
                                    ((CLKDIV) == SDIO_CLKDIV334) || \
                                    ((CLKDIV) == SDIO_CLKDIV336) || \
                                    ((CLKDIV) == SDIO_CLKDIV338) || \
                                    ((CLKDIV) == SDIO_CLKDIV340) || \
                                    ((CLKDIV) == SDIO_CLKDIV342) || \
                                    ((CLKDIV) == SDIO_CLKDIV344) || \
                                    ((CLKDIV) == SDIO_CLKDIV346) || \
                                    ((CLKDIV) == SDIO_CLKDIV348) || \
                                    ((CLKDIV) == SDIO_CLKDIV350) || \
                                    ((CLKDIV) == SDIO_CLKDIV352) || \
                                    ((CLKDIV) == SDIO_CLKDIV354) || \
                                    ((CLKDIV) == SDIO_CLKDIV356) || \
                                    ((CLKDIV) == SDIO_CLKDIV358) || \
                                    ((CLKDIV) == SDIO_CLKDIV360) || \
                                    ((CLKDIV) == SDIO_CLKDIV362) || \
                                    ((CLKDIV) == SDIO_CLKDIV364) || \
                                    ((CLKDIV) == SDIO_CLKDIV366) || \
                                    ((CLKDIV) == SDIO_CLKDIV368) || \
                                    ((CLKDIV) == SDIO_CLKDIV370) || \
                                    ((CLKDIV) == SDIO_CLKDIV372) || \
                                    ((CLKDIV) == SDIO_CLKDIV374) || \
                                    ((CLKDIV) == SDIO_CLKDIV376) || \
                                    ((CLKDIV) == SDIO_CLKDIV378) || \
                                    ((CLKDIV) == SDIO_CLKDIV380) || \
                                    ((CLKDIV) == SDIO_CLKDIV382) || \
                                    ((CLKDIV) == SDIO_CLKDIV384) || \
                                    ((CLKDIV) == SDIO_CLKDIV386) || \
                                    ((CLKDIV) == SDIO_CLKDIV388) || \
                                    ((CLKDIV) == SDIO_CLKDIV390) || \
                                    ((CLKDIV) == SDIO_CLKDIV392) || \
                                    ((CLKDIV) == SDIO_CLKDIV394) || \
                                    ((CLKDIV) == SDIO_CLKDIV396) || \
                                    ((CLKDIV) == SDIO_CLKDIV398) || \
                                    ((CLKDIV) == SDIO_CLKDIV400) || \
                                    ((CLKDIV) == SDIO_CLKDIV402) || \
                                    ((CLKDIV) == SDIO_CLKDIV404) || \
                                    ((CLKDIV) == SDIO_CLKDIV406) || \
                                    ((CLKDIV) == SDIO_CLKDIV408) || \
                                    ((CLKDIV) == SDIO_CLKDIV410) || \
                                    ((CLKDIV) == SDIO_CLKDIV412) || \
                                    ((CLKDIV) == SDIO_CLKDIV414) || \
                                    ((CLKDIV) == SDIO_CLKDIV416) || \
                                    ((CLKDIV) == SDIO_CLKDIV418) || \
                                    ((CLKDIV) == SDIO_CLKDIV420) || \
                                    ((CLKDIV) == SDIO_CLKDIV422) || \
                                    ((CLKDIV) == SDIO_CLKDIV424) || \
                                    ((CLKDIV) == SDIO_CLKDIV426) || \
                                    ((CLKDIV) == SDIO_CLKDIV428) || \
                                    ((CLKDIV) == SDIO_CLKDIV430) || \
                                    ((CLKDIV) == SDIO_CLKDIV432) || \
                                    ((CLKDIV) == SDIO_CLKDIV434) || \
                                    ((CLKDIV) == SDIO_CLKDIV436) || \
                                    ((CLKDIV) == SDIO_CLKDIV438) || \
                                    ((CLKDIV) == SDIO_CLKDIV440) || \
                                    ((CLKDIV) == SDIO_CLKDIV442) || \
                                    ((CLKDIV) == SDIO_CLKDIV444) || \
                                    ((CLKDIV) == SDIO_CLKDIV446) || \
                                    ((CLKDIV) == SDIO_CLKDIV448) || \
                                    ((CLKDIV) == SDIO_CLKDIV450) || \
                                    ((CLKDIV) == SDIO_CLKDIV452) || \
                                    ((CLKDIV) == SDIO_CLKDIV454) || \
                                    ((CLKDIV) == SDIO_CLKDIV456) || \
                                    ((CLKDIV) == SDIO_CLKDIV458) || \
                                    ((CLKDIV) == SDIO_CLKDIV460) || \
                                    ((CLKDIV) == SDIO_CLKDIV462) || \
                                    ((CLKDIV) == SDIO_CLKDIV464) || \
                                    ((CLKDIV) == SDIO_CLKDIV466) || \
                                    ((CLKDIV) == SDIO_CLKDIV468) || \
                                    ((CLKDIV) == SDIO_CLKDIV470) || \
                                    ((CLKDIV) == SDIO_CLKDIV472) || \
                                    ((CLKDIV) == SDIO_CLKDIV474) || \
                                    ((CLKDIV) == SDIO_CLKDIV476) || \
                                    ((CLKDIV) == SDIO_CLKDIV478) || \
                                    ((CLKDIV) == SDIO_CLKDIV480) || \
                                    ((CLKDIV) == SDIO_CLKDIV482) || \
                                    ((CLKDIV) == SDIO_CLKDIV484) || \
                                    ((CLKDIV) == SDIO_CLKDIV486) || \
                                    ((CLKDIV) == SDIO_CLKDIV488) || \
                                    ((CLKDIV) == SDIO_CLKDIV490) || \
                                    ((CLKDIV) == SDIO_CLKDIV492) || \
                                    ((CLKDIV) == SDIO_CLKDIV494) || \
                                    ((CLKDIV) == SDIO_CLKDIV496) || \
                                    ((CLKDIV) == SDIO_CLKDIV498) || \
                                    ((CLKDIV) == SDIO_CLKDIV500) || \
                                    ((CLKDIV) == SDIO_CLKDIV502) || \
                                    ((CLKDIV) == SDIO_CLKDIV504) || \
                                    ((CLKDIV) == SDIO_CLKDIV506) || \
                                    ((CLKDIV) == SDIO_CLKDIV508) || \
                                    ((CLKDIV) == SDIO_CLKDIV510))


/** @defgroup SDIO_CLKENA_Register **/
/** @defgroup SDIO_CCLK_ENABLE
  * @{
  */
#define SDIO_CCLK_ENABLE_DISABLE         ((uint32_t)0x00)
#define SDIO_CCLK_ENABLE_ENABLE          SDIO_CLKENA_CCLK_ENABLE_0

#define IS_SDIO_CCLK_ENABLE(ENABLE) (((ENABLE) == SDIO_CCLK_ENABLE_DISABLE) || \
                                     ((ENABLE) == SDIO_CCLK_ENABLE_ENABLE))


/** @defgroup SDIO_TMOUT_Register **/
/** @defgroup SDIO_response_timeout & SDIO_data_timeout
  * @{
  */
#define IS_SDIO_RESPONSE_TIMEOUT         ((uint32_t)0x00000040)
#define IS_SDIO_DATA_TIMEOUT             ((uint32_t)0xffffff00)
#define IS_SDIO_TIMEOUT(TIMEOUT)                                 \
                       (                                         \
                       ((TIMEOUT) == SDIO_RESPONSE_TIMEOUT  ) || \
                       ((TIMEOUT) == SDIO_DATA_TIMEOUT      ) || \
                       )


/** @defgroup SDIO_CTYPE_Register **/
/** @defgroup SDIO_Card_Width
  * @{
  */
#define SDIO_CARD_WIDE_1B                      ((uint32_t)0x00)
#define SDIO_CARD_WIDE_4B                      SDIO_CTYPE_CARD0_WIDTH2
#define SDIO_CARD_WIDE_8B                      SDIO_CTYPE_CARD0_WIDTH1

#define IS_SDIO_CARD_WIDE(WIDE) (((WIDE) == SDIO_CARD_WIDE_1B) || \
                                        ((WIDE) == SDIO_CARD_WIDE_4B) || \
                                        ((WIDE) == SDIO_CARD_WIDE_8B))


/** @defgroup SDIO_BLKSIZ_Register **/
/** @defgroup SDIO_Data_Block_Size  Data Block Size
  * @{
  */
#define SDIO_DATABLOCK_SIZE_1B               ((uint32_t)0x00000001)
#define SDIO_DATABLOCK_SIZE_2B               ((uint32_t)0x00000002)
#define SDIO_DATABLOCK_SIZE_4B               ((uint32_t)0x00000004)
#define SDIO_DATABLOCK_SIZE_8B               ((uint32_t)0x00000008)
#define SDIO_DATABLOCK_SIZE_16B              ((uint32_t)0x00000010)
#define SDIO_DATABLOCK_SIZE_32B              ((uint32_t)0x00000020)
#define SDIO_DATABLOCK_SIZE_64B              ((uint32_t)0x00000040)
#define SDIO_DATABLOCK_SIZE_128B             ((uint32_t)0x00000080)
#define SDIO_DATABLOCK_SIZE_256B             ((uint32_t)0x00000100)
#define SDIO_DATABLOCK_SIZE_512B             ((uint32_t)0x00000200)

#define IS_SDIO_BLOCK_SIZE(SIZE) (((SIZE) == SDIO_DATABLOCK_SIZE_1B)    || \
                                  ((SIZE) == SDIO_DATABLOCK_SIZE_2B)    || \
                                  ((SIZE) == SDIO_DATABLOCK_SIZE_4B)    || \
                                  ((SIZE) == SDIO_DATABLOCK_SIZE_8B)    || \
                                  ((SIZE) == SDIO_DATABLOCK_SIZE_16B)   || \
                                  ((SIZE) == SDIO_DATABLOCK_SIZE_32B)   || \
                                  ((SIZE) == SDIO_DATABLOCK_SIZE_64B)   || \
                                  ((SIZE) == SDIO_DATABLOCK_SIZE_128B)  || \
                                  ((SIZE) == SDIO_DATABLOCK_SIZE_256B)  || \
                                  ((SIZE) == SDIO_DATABLOCK_SIZE_512B))


/** @defgroup SDIO_BYTCCNT_Register **/
/** @defgroup SDIO_Data_Byte_Count
  * @{
  */
#define IS_SDIO_DATA_BYTE_COUNT(COUNT) ((COUNT) <= 0xFFFFFFFFU)


/** @defgroup SDIO_INTMASK_Register **/
/** @defgroup SDIO_Interrupt_Mask_sources Interrupt Sources Mask
  * @{
  */
#define SDIO_IT_MASK_CARDDETECT            SDIO_INTMASK_CD_INT_MASK
#define SDIO_IT_MASK_RE                    SDIO_INTMASK_RE_INT_MASK
#define SDIO_IT_MASK_CMDDONE               SDIO_INTMASK_CMD_INT_MASK
#define SDIO_IT_MASK_DTO                   SDIO_INTMASK_DTO_INT_MASK
#define SDIO_IT_MASK_TXDR                  SDIO_INTMASK_TXDR_INT_MASK
#define SDIO_IT_MASK_RXDR                  SDIO_INTMASK_RXDR_INT_MASK
#define SDIO_IT_MASK_RCRC                  SDIO_INTMASK_RCRC_INT_MASK
#define SDIO_IT_MASK_DCRC                  SDIO_INTMASK_DCRC_INT_MASK
#define SDIO_IT_MASK_RTO                   SDIO_INTMASK_RTO_INT_MASK
#define SDIO_IT_MASK_DRTO                  SDIO_INTMASK_DRTO_INT_MASK
#define SDIO_IT_MASK_HTO                   SDIO_INTMASK_HTO_INT_MASK
#define SDIO_IT_MASK_FRUN                  SDIO_INTMASK_FRUN_INT_MASK
#define SDIO_IT_MASK_HLE                   SDIO_INTMASK_HLE_INT_MASK
#define SDIO_IT_MASK_SBE                   SDIO_INTMASK_SBE_BCI_INT_MASK
#define SDIO_IT_MASK_ACD                   SDIO_INTMASK_ACD_INT_MASK
#define SDIO_IT_MASK_EBE                   SDIO_INTMASK_EBE_INT_MASK
#define SDIO_IT_MASK_SDIOIT                SDIO_INTMASK_SDIO_INT_MASK_CARD0

#define IS_SDIO_IT_MASK(MASK)   (((MASK)==SDIO_IT_MASK_CARDDETECT) || \
                                 ((MASK)==SDIO_IT_MASK_RE)         || \
                                 ((MASK)==SDIO_IT_MASK_CMDDONE)    || \
                                 ((MASK)==SDIO_IT_MASK_DTO)        || \
                                 ((MASK)==SDIO_IT_MASK_TXDR  )     || \
                                 ((MASK)==SDIO_IT_MASK_RXDR  )     || \
                                 ((MASK)==SDIO_IT_MASK_RCRC  )     || \
                                 ((MASK)==SDIO_IT_MASK_DCRC  )     || \
                                 ((MASK)==SDIO_IT_MASK_RTO   )     || \
                                 ((MASK)==SDIO_IT_MASK_DRTO  )     || \
                                 ((MASK)==SDIO_IT_MASK_HTO   )     || \
                                 ((MASK)==SDIO_IT_MASK_FRUN  )     || \
                                 ((MASK)==SDIO_IT_MASK_HLE   )     || \
                                 ((MASK)==SDIO_IT_MASK_SBE   )     || \
                                 ((MASK)==SDIO_IT_MASK_ACD   )     || \
                                 ((MASK)==SDIO_IT_MASK_EBE   )     || \
                                 ((MASK)==SDIO_IT_MASK_SDIOIT))

/** @defgroup SDIO_MINTSTS_Register **/
/** @defgroup SDIO_Interrupt_Flags
  * @{
  */
#define SDIO_IT_FLAG_CARDDETECT        SDIO_MINTSTS_CARD_DETECT_INTERRUPT
#define SDIO_IT_FLAG_RE                SDIO_MINTSTS_RESPONSE_ERROR_INTERRUPT
#define SDIO_IT_FLAG_CMDDONE           SDIO_MINTSTS_COMMAND_DONE_INTERRUPT
#define SDIO_IT_FLAG_DTO               SDIO_MINTSTS_DATA_TRANSFER_OVER_INTERRUPT
#define SDIO_IT_FLAG_TXDR              SDIO_MINTSTS_TRANSMIT_RECEIVE_FIFO_DATA_INTERRUPT
#define SDIO_IT_FLAG_RXDR              SDIO_MINTSTS_RECEIVE_FIFO_DATA_REQUEST_INTERRUPT
#define SDIO_IT_FLAG_RCRC              SDIO_MINTSTS_RESPONSE_CRC_ERROR_INTERRUPT
#define SDIO_IT_FLAG_DCRC              SDIO_MINTSTS_DATA_CRC_ERROR_INTERRUPT
#define SDIO_IT_FLAG_RTO               SDIO_MINTSTS_RESPONSE_TIMEOUT_INTERRUPT
#define SDIO_IT_FLAG_DRTO              SDIO_MINTSTS_DATA_READ_TIMEOUT_INTERRUPT
#define SDIO_IT_FLAG_HTO               SDIO_MINTSTS_HOST_TIMEOUT_INTERRUPT
#define SDIO_IT_FLAG_FRUN              SDIO_MINTSTS_FIFO_UNDER_OVER_RUN_INTERRUPT
#define SDIO_IT_FLAG_HLE               SDIO_MINTSTS_HARDWARE_LOCKED_WRITE_INTERRUPT
#define SDIO_IT_FLAG_SBE               SDIO_MINTSTS_BUSY_COMPLETE_INTERRUPT
#define SDIO_IT_FLAG_ACD               SDIO_MINTSTS_AUTO_COMMAND_DONE_INTERRUPT
#define SDIO_IT_FLAG_EBE               SDIO_MINTSTS_END_BIT_ERROR_INTERRUPT
#define SDIO_IT_FLAG_SDIOIT            SDIO_MINTSTS_SDIO_INTERRUPT_CARD0

#define IS_SDIO_IT_FLAG(FLAG)   (((FLAG)==SDIO_IT_FLAG_CARDDETECT) || \
                                 ((FLAG)==SDIO_IT_FLAG_RE)         || \
                                 ((FLAG)==SDIO_IT_FLAG_CMDDONE)    || \
                                 ((FLAG)==SDIO_IT_FLAG_DTO)        || \
                                 ((FLAG)==SDIO_IT_FLAG_TXDR  )     || \
                                 ((FLAG)==SDIO_IT_FLAG_RXDR  )     || \
                                 ((FLAG)==SDIO_IT_FLAG_RCRC  )     || \
                                 ((FLAG)==SDIO_IT_FLAG_DCRC  )     || \
                                 ((FLAG)==SDIO_IT_FLAG_RTO   )     || \
                                 ((FLAG)==SDIO_IT_FLAG_DRTO  )     || \
                                 ((FLAG)==SDIO_IT_FLAG_HTO   )     || \
                                 ((FLAG)==SDIO_IT_FLAG_FRUN  )     || \
                                 ((FLAG)==SDIO_IT_FLAG_HLE   )     || \
                                 ((FLAG)==SDIO_IT_FLAG_SBE   )     || \
                                 ((FLAG)==SDIO_IT_FLAG_ACD   )     || \
                                 ((FLAG)==SDIO_IT_FLAG_EBE   )     || \
                                 ((FLAG)==SDIO_IT_FLAG_SDIOIT))


/** @defgroup SDIO_RINTSTS_Register **/
/** @defgroup SDIO_Interrupt_Clean
  * @{
  */
#define SDIO_IT_CLEAN_CARDDETECT        SDIO_RINTSTS_CARD_DETECT_STATUS
#define SDIO_IT_CLEAN_RE                SDIO_RINTSTS_RESPONSE_ERROR_STATUS
#define SDIO_IT_CLEAN_CMDDONE           SDIO_RINTSTS_COMMAND_DONE_STATUS
#define SDIO_IT_CLEAN_DTO               SDIO_RINTSTS_DATA_TRANSFER_OVER_STATUS
#define SDIO_IT_CLEAN_TXDR              SDIO_RINTSTS_TRANSMIT_FIFO_DATA_REQUEST_STATUS
#define SDIO_IT_CLEAN_RXDR              SDIO_RINTSTS_RECEIVE_FIFO_DATA_REQUEST_STATUS
#define SDIO_IT_CLEAN_RCRC              SDIO_RINTSTS_RESPONSE_CRC_ERROR_STATUS
#define SDIO_IT_CLEAN_DCRC              SDIO_RINTSTS_DATA_CRC_ERROR_STATUS
#define SDIO_IT_CLEAN_RTO               SDIO_RINTSTS_RESPONSE_TIMEOUT_STATUS
#define SDIO_IT_CLEAN_DRTO              SDIO_RINTSTS_DATA_READ_TIMEOUT_STATUS
#define SDIO_IT_CLEAN_HTO               SDIO_RINTSTS_HOST_TIMEOUT_STATUS
#define SDIO_IT_CLEAN_FRUN              SDIO_RINTSTS_FIFO_UNDER_OVER_RUN_STATUS
#define SDIO_IT_CLEAN_HLE               SDIO_RINTSTS_HARDWARE_LOCKED_WRITE_STATUS
#define SDIO_IT_CLEAN_SBE               SDIO_RINTSTS_BUSY_COMPLETE_STATUS
#define SDIO_IT_CLEAN_ACD               SDIO_RINTSTS_AUTO_COMMAND_DONE_STATUS
#define SDIO_IT_CLEAN_EBE               SDIO_RINTSTS_END_BIT_ERROR_STATUS
#define SDIO_IT_CLEAN_SDIOIT            SDIO_RINTSTS_SDIO_INTERRUPT_CARD0

#define IS_SDIO_IT_CLEAN(CLEAN)   (((CLEAN)==SDIO_IT_CLEAN_CARDDETECT) || \
                                   ((CLEAN)==SDIO_IT_CLEAN_RE)         || \
                                   ((CLEAN)==SDIO_IT_CLEAN_CMDDONE)    || \
                                   ((CLEAN)==SDIO_IT_CLEAN_DTO)        || \
                                   ((CLEAN)==SDIO_IT_CLEAN_TXDR  )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_RXDR  )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_RCRC  )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_DCRC  )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_RTO   )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_DRTO  )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_HTO   )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_FRUN  )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_HLE   )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_SBE   )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_ACD   )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_EBE   )     || \
                                   ((CLEAN)==SDIO_IT_CLEAN_SDIOIT))


/** @defgroup SDIO_CMDARG_Register **/
/** @defgroup SDIO_Command_Argument
  * @{
  */
#define IS_SDIO_CMD_ARG(ARG) ((ARG) <= 0xFFFFFFFFU)


/** @defgroup SDIO_CMD_Register **/
/** @defgroup SDIO_LL_CMD_START
  * @{
  */
#define SDIO_CMD_START_DISABLE                   ((uint32_t)0x00)
#define SDIO_CMD_START_ENABLE                    SDIO_CMD_START_CMD

#define IS_SDIO_CMD_START(START) (((START) == SDIO_CMD_START_DISABLE) || \
                                  ((START) == SDIO_CMD_START_ENABLE))


/** @defgroup SDIO_Use_hold_reg
  * @{
  */
#define SDIO_USE_HOLD_REG_DISABLE         ((uint32_t)0x00)
#define SDIO_USE_HOLD_REG_ENABLE          SDIO_CMD_USE_HOLD_REG

#define IS_SDIO_USE_HOLD_REG(ENABLE) (((ENABLE) == SDIO_USE_HOLD_REG_DISABLE) || \
                              ((ENABLE) == SDIO_USE_HOLD_REG_ENABLE))


/** @defgroup SDIO_UPDATE_CLOCK_REGISTER_ONLY
  * @{
  */
#define SDIO_UPDATE_CLOCK_REGISTER_ONLY_DISABLE         ((uint32_t)0x00)
#define SDIO_UPDATE_CLOCK_REGISTER_ONLY_ENABLE          SDIO_CMD_UPDATE_CLOCK_REGISTERS_ONLY

#define IS_SDIO_UPDATE_CLOCK_REGISTER_ONLY_ENABLE(ENABLE) (((ENABLE) == SDIO_UPDATE_CLOCK_REGISTER_ONLY_DISABLE) || \
                                     ((ENABLE) == SDIO_UPDATE_CLOCK_REGISTER_ONLY_ENABLE))

/** @defgroup SDIO_SEND_AUTO_STOP
  * @{
  */
#define SDIO_SEND_AUTO_STOP_DISABLE         ((uint32_t)0x00)
#define SDIO_SEND_AUTO_STOP_ENABLE          SDIO_CMD_SEND_AUTO_STOP

#define IS_SDIO_SEND_AUTO_STOP_ENABLE(ENABLE) (((ENABLE) == SDIO_SEND_AUTO_STOP_DISABLE) || \
                                               ((ENABLE) == SDIO_SEND_AUTO_STOP_ENABLE))


/** @defgroup SDIO_Transfer_Mode Block/stream
  * @{
  */
#define SDIO_TRANSFER_MODE_BLOCK             ((uint32_t)0x00)
#define SDIO_TRANSFER_MODE_STREAM            SDIO_CMD_TRANSFER_MODE

#define IS_SDIO_TRANSFER_MODE(MODE) (((MODE) == SDIO_TRANSFER_MODE_BLOCK) || \
                                     ((MODE) == SDIO_TRANSFER_MODE_STREAM))

/** @defgroup SDIO_Transfer_Direction Read/Write
  * @{
  */
#define SDIO_TRANSFER_READ_FROM_CARD         ((uint32_t)0x00)
#define SDIO_TRANSFER_WRITE_TO_CARD          SDIO_CMD_READ_WRITE

#define IS_SDIO_TRANSFER_DIR(DIR) (((DIR) == SDIO_TRANSFER_READ_FROM_CARD) || \
                                   ((DIR) == SDIO_TRANSFER_WRITE_TO_CARD))

/** @defgroup SDIO_Data_Expected
  * @{
  */
#define SDIO_DATA_EXPECTED_DISABLE                 ((uint32_t)0x00)
#define SDIO_DATA_EXPECTED_ENABLE                  SDIO_CMD_DATA_EXPECTED

#define IS_SDIO_DATA_EXPECT(EXPECT) (((EXPECT) == SDIO_DATA_EXPECTED_DISABLE)    || \
                                     ((EXPECT) == SDIO_DATA_EXPECTED_ENABLE))

/** @defgroup SDIO_Check_Response_CRC
  * @{
  */
#define SDIO_CHECK_RESPONSE_CRC_DISABLE                 ((uint32_t)0x00)
#define SDIO_CHECK_RESPONSE_CRC_ENABLE                  SDIO_CMD_CHECK_RESPONSE_CRC

#define IS_SDIO_CHECK_RESPONSE_CRC(CRC) (((CRC) == SDIO_CHECK_RESPONSE_CRC_DISABLE)    || \
                                         ((CRC) == SDIO_CHECK_RESPONSE_CRC_ENABLE))

/** @defgroup SDIO_Response_Length
  * @{
  */
#define SDIO_RESPONSE_SHORT                 ((uint32_t)0x00)
#define SDIO_RESPONSE_LONG                  SDIO_CMD_RESPONSE_LENGTH

#define IS_SDIO_RESPONSE(RESPONSE) (((RESPONSE) == SDIO_RESPONSE_SHORT)    || \
                                    ((RESPONSE) == SDIO_RESPONSE_LONG))

/** @defgroup SDIO_Response_Expect
  * @{
  */
#define SDIO_RESPONSE_EXPECT_DISABLE                 ((uint32_t)0x00)
#define SDIO_RESPONSE_EXPECT_ENABLE                  SDIO_CMD_RESPONSE_EXPECT

#define IS_SDIO_RESPONSE_EXPECT(EXPECT) (((EXPECT) == SDIO_RESPONSE_EXPECT_DISABLE)    || \
                                         ((EXPECT) == SDIO_RESPONSE_EXPECT_ENABLE))


/** @defgroup SDIO_Command_Index Command Index
  * @{
  */
#define IS_SDIO_CMD_INDEX(INDEX)            ((INDEX) < 0x40U)


/** @defgroup SDIO_STATUS_Register **/
/** @defgroup SDIO_status
  * @{
  */
#define SDIO_STAT_FIFO_RX_WATERMARK        SDIO_STATUS_FIFO_RX_WATERMARK
#define SDIO_STAT_FIFO_TX_WATERMARK        SDIO_STATUS_FIFO_TX_WATERMARK
#define SDIO_STAT_FIFO_EMPTY               SDIO_STATUS_FIFO_EMPTY
#define SDIO_STAT_FIFO_FULL                SDIO_STATUS_FIFO_FULL
#define SDIO_STAT_FSM_IDLE                 ((uint32_t)0x00)
#define SDIO_STAT_FSM_SED_INIT_SEQ         ((uint32_t)0x01)
#define SDIO_STAT_FSM_TX_CMD_START_BIT     ((uint32_t)0x02)
#define SDIO_STAT_FSM_TX_CMD_TX_BIT        ((uint32_t)0x03)
#define SDIO_STAT_FSM_TX_CMD_INDEX_ARG     ((uint32_t)0x04)
#define SDIO_STAT_FSM_TX_CMD_CRC7          ((uint32_t)0x05)
#define SDIO_STAT_FSM_TX_CMD_END_BIT       ((uint32_t)0x06)
#define SDIO_STAT_FSM_RX_RESP_START_BIT    ((uint32_t)0x07)
#define SDIO_STAT_FSM_RX_RESP_IRQ          ((uint32_t)0x08)
#define SDIO_STAT_FSM_RX_RESP_TX_BIT       ((uint32_t)0x09)
#define SDIO_STAT_FSM_RX_RESP_CMD_IDX      ((uint32_t)0x0a)
#define SDIO_STAT_FSM_RX_RESP_DATA         ((uint32_t)0x0b)
#define SDIO_STAT_FSM_RX_RESP_CRC7         ((uint32_t)0x0c)
#define SDIO_STAT_FSM_RX_RESP_END_BIT      ((uint32_t)0x0d)
#define SDIO_STAT_FSM_CMD_PATH_WAIT_NCC    ((uint32_t)0x0e)
#define SDIO_STAT_FSM_WAIT                 ((uint32_t)0x0f)
#define SDIO_STAT_DATA_3_STATUS            SDIO_STATUS_DATA_3_STATUS
#define SDIO_STAT_DATA_BUSY                SDIO_STATUS_DATA_BUSY
#define SDIO_STAT_DATA_STATE_MC_BUSY       SDIO_STATUS_DATA_STATE_MC_BUSY
#define SDIO_STAT_RESPONSE_INDEX           SDIO_STATUS_RESPONSE_INDEX
#define SDIO_STAT_FIFO_COUNT               SDIO_STATUS_FIFO_COUNT
#define SDIO_STAT_DMA_ACK                  SDIO_STATUS_DMA_ACK
#define SDIO_STAT_DMA_REQ                  SDIO_STATUS_DMA_REQ

#define IS_SDIO_STATUS(STATUS)          (((STATUS)==SDIO_STAT_FIFO_RX_WATERMARK    ) || \
                                         ((STATUS)==SDIO_STAT_FIFO_TX_WATERMARK    ) || \
                                         ((STATUS)==SDIO_STAT_FIFO_EMPTY           ) || \
                                         ((STATUS)==SDIO_STAT_FIFO_FULL            ) || \
                                         ((STATUS)==SDIO_STAT_FSM_IDLE             ) || \
                                         ((STATUS)==SDIO_STAT_FSM_SED_INIT_SEQ     ) || \
                                         ((STATUS)==SDIO_STAT_FSM_TX_CMD_START_BIT ) || \
                                         ((STATUS)==SDIO_STAT_FSM_TX_CMD_TX_BIT    ) || \
                                         ((STATUS)==SDIO_STAT_FSM_TX_CMD_INDEX_ARG ) || \
                                         ((STATUS)==SDIO_STAT_FSM_TX_CMD_CRC7      ) || \
                                         ((STATUS)==SDIO_STAT_FSM_TX_CMD_END_BIT   ) || \
                                         ((STATUS)==SDIO_STAT_FSM_RX_RESP_START_BIT) || \
                                         ((STATUS)==SDIO_STAT_FSM_RX_RESP_IRQ      ) || \
                                         ((STATUS)==SDIO_STAT_FSM_RX_RESP_TX_BIT   ) || \
                                         ((STATUS)==SDIO_STAT_FSM_RX_RESP_CMD_IDX  ) || \
                                         ((STATUS)==SDIO_STAT_FSM_RX_RESP_DATA     ) || \
                                         ((STATUS)==SDIO_STAT_FSM_RX_RESP_CRC7     ) || \
                                         ((STATUS)==SDIO_STAT_FSM_RX_RESP_END_BIT  ) || \
                                         ((STATUS)==SDIO_STAT_FSM_CMD_PATH_WAIT_NCC) || \
                                         ((STATUS)==SDIO_STAT_FSM_WAIT             ) || \
                                         ((STATUS)==SDIO_STAT_DATA_3_STATUS        ) || \
                                         ((STATUS)==SDIO_STAT_DATA_BUSY            ) || \
                                         ((STATUS)==SDIO_STAT_DATA_STATE_MC_BUSY   ) || \
                                         ((STATUS)==SDIO_STAT_RESPONSE_INDEX       ) || \
                                         ((STATUS)==SDIO_STAT_FIFO_COUNT           ) || \
                                         ((STATUS)==SDIO_STAT_DMA_ACK              ) || \
                                         ((STATUS)==SDIO_STAT_DMA_REQ              ))


/** @defgroup SDIO_FIFOTH_Register **/
/** @defgroup SDIO_RX&Tx_WMark
  * @{
  */
#define SDIO_RX_WATERMARK        SDIO_FIFOTH_RX_WMark
#define SDIO_TX_WATERMARK        SDIO_FIFOTH_TX_WMark

#define IS_SDIO_FIFOTH_WATERMARK(WATERMARK)    (((WATERMARK)==SDIO_RX_WATERMARK) || \
                                                ((WATERMARK)==SDIO_TX_WATERMARK))



/** @defgroup all of sdio registers **/
/** @defgroup SDIO_ALL_Registers
  * @{
  */
#define SDIO_CTRL              ((uint8_t)0x00)
#define SDIO_PWREN             ((uint8_t)0x04)
#define SDIO_CLKDIV            ((uint8_t)0x08)
#define SDIO_CLKSRC            ((uint8_t)0x0C)
#define SDIO_CLKENA            ((uint8_t)0x10)
#define SDIO_TMOUT             ((uint8_t)0x14)
#define SDIO_CTYPE             ((uint8_t)0x18)
#define SDIO_BLKSIZ            ((uint8_t)0x1C)
#define SDIO_BYTCNT            ((uint8_t)0x20)
#define SDIO_INTMASK           ((uint8_t)0x24)
#define SDIO_CMDARG            ((uint8_t)0x28)
#define SDIO_CMD               ((uint8_t)0x2C)
#define SDIO_RESP0             ((uint8_t)0x30)
#define SDIO_RESP1             ((uint8_t)0x34)
#define SDIO_RESP2             ((uint8_t)0x38)
#define SDIO_RESP3             ((uint8_t)0x3C)
#define SDIO_MINTSTS           ((uint8_t)0x40)
#define SDIO_RINTSTS           ((uint8_t)0x44)
#define SDIO_STATUS            ((uint8_t)0x48)
#define SDIO_FIFOTH            ((uint8_t)0x4C)

#define IS_SDIO_REGISTER(REGISTER) (((REGISTER) == SDIO_CTRL)    || \
                                    ((REGISTER) == SDIO_PWREN)   || \
                                    ((REGISTER) == SDIO_CLKDIV)  || \
                                    ((REGISTER) == SDIO_CLKSRC)  || \
                                    ((REGISTER) == SDIO_CLKENA)  || \
                                    ((REGISTER) == SDIO_TMOUT)   || \
                                    ((REGISTER) == SDIO_CTYPE)   || \
                                    ((REGISTER) == SDIO_BLKSIZ)  || \
                                    ((REGISTER) == SDIO_BYTCNT)  || \
                                    ((REGISTER) == SDIO_INTMASK) || \
                                    ((REGISTER) == SDIO_CMDARG)  || \
                                    ((REGISTER) == SDIO_CMD)     || \
                                    ((REGISTER) == SDIO_RESP0)   || \
                                    ((REGISTER) == SDIO_RESP1)   || \
                                    ((REGISTER) == SDIO_RESP2)   || \
                                    ((REGISTER) == SDIO_RESP3)   || \
                                    ((REGISTER) == SDIO_MINTSTS) || \
                                    ((REGISTER) == SDIO_RINTSTS) || \
                                    ((REGISTER) == SDIO_STATUS)  || \
                                    ((REGISTER) == SDIO_FIFOTH))


/******************************************************************************************/
/**
  * @brief SDMMC Commands Index
  */
#define SDMMC_CMD_GO_IDLE_STATE                                 0U    /*!< Resets the SD memory card.                                                               */
#define SDMMC_CMD_SEND_OP_COND                                  1U    /*!< Sends host capacity support information and activates the card's initialization process. */
#define SDMMC_CMD_ALL_SEND_CID                                  2U    /*!< Asks any card connected to the host to send the CID numbers on the CMD line.             */
#define SDMMC_CMD_SET_REL_ADDR                                  3U    /*!< Asks the card to publish a new relative address (RCA).                                   */
#define SDMMC_CMD_SET_DSR                                       4U    /*!< Programs the DSR of all cards.                                                           */
#define SDMMC_CMD_SDMMC_SEN_OP_COND                             5U    /*!< Sends host capacity support information (HCS) and asks the accessed card to send its
                                                                           operating condition register (OCR) content in the response on the CMD line.              */
#define SDMMC_CMD_HS_SWITCH                                     6U    /*!< Checks switchable function (mode 0) and switch card function (mode 1).                   */
#define SDMMC_CMD_SEL_DESEL_CARD                                7U    /*!< Selects the card by its own relative address and gets deselected by any other address    */
#define SDMMC_CMD_HS_SEND_EXT_CSD                               8U    /*!< Sends SD Memory Card interface condition, which includes host supply voltage information
                                                                           and asks the card whether card supports voltage.                                         */
#define SDMMC_CMD_SEND_CSD                                      9U    /*!< Addressed card sends its card specific data (CSD) on the CMD line.                       */
#define SDMMC_CMD_SEND_CID                                      10U   /*!< Addressed card sends its card identification (CID) on the CMD line.                      */
#define SDMMC_CMD_READ_DAT_UNTIL_STOP                           11U   /*!< SD card doesn't support it.                                                              */
#define SDMMC_CMD_STOP_TRANSMISSION                             12U   /*!< Forces the card to stop transmission.                                                    */
#define SDMMC_CMD_SEND_STATUS                                   13U   /*!< Addressed card sends its status register.                                                */
#define SDMMC_CMD_HS_BUSTEST_READ                               14U   /*!< Reserved                                                                                 */
#define SDMMC_CMD_GO_INACTIVE_STATE                             15U   /*!< Sends an addressed card into the inactive state.                                         */
#define SDMMC_CMD_SET_BLOCKLEN                                  16U   /*!< Sets the block length (in bytes for SDSC) for all following block commands
                                                                           (read, write, lock). Default block length is fixed to 512 Bytes. Not effective 
                                                                           for SDHS and SDXC.                                                                       */
#define SDMMC_CMD_READ_SINGLE_BLOCK                             17U   /*!< Reads single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of
                                                                           fixed 512 bytes in case of SDHC and SDXC.                                                */
#define SDMMC_CMD_READ_MULT_BLOCK                               18U   /*!< Continuously transfers data blocks from card to host until interrupted by
                                                                           STOP_TRANSMISSION command.                                                               */
#define SDMMC_CMD_HS_BUSTEST_WRITE                              19U   /*!< 64 bytes tuning pattern is sent for SDR50 and SDR104.                                    */
#define SDMMC_CMD_WRITE_DAT_UNTIL_STOP                          20U   /*!< Speed class control command.                                                             */
#define SDMMC_CMD_SET_BLOCK_COUNT                               23U   /*!< Specify block count for CMD18 and CMD25.                                                 */
#define SDMMC_CMD_WRITE_SINGLE_BLOCK                            24U   /*!< Writes single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of
                                                                           fixed 512 bytes in case of SDHC and SDXC.                                                */
#define SDMMC_CMD_WRITE_MULT_BLOCK                              25U   /*!< Continuously writes blocks of data until a STOP_TRANSMISSION follows.                    */
#define SDMMC_CMD_PROG_CID                                      26U   /*!< Reserved for manufacturers.                                                              */
#define SDMMC_CMD_PROG_CSD                                      27U   /*!< Programming of the programmable bits of the CSD.                                         */
#define SDMMC_CMD_SET_WRITE_PROT                                28U   /*!< Sets the write protection bit of the addressed group.                                    */
#define SDMMC_CMD_CLR_WRITE_PROT                                29U   /*!< Clears the write protection bit of the addressed group.                                  */
#define SDMMC_CMD_SEND_WRITE_PROT                               30U   /*!< Asks the card to send the status of the write protection bits.                           */
#define SDMMC_CMD_SD_ERASE_GRP_START                            32U   /*!< Sets the address of the first write block to be erased. (For SD card only).              */
#define SDMMC_CMD_SD_ERASE_GRP_END                              33U   /*!< Sets the address of the last write block of the continuous range to be erased.           */
#define SDMMC_CMD_ERASE_GRP_START                               35U   /*!< Sets the address of the first write block to be erased. Reserved for each command
                                                                           system set by switch function command (CMD6).                                            */
#define SDMMC_CMD_ERASE_GRP_END                                 36U   /*!< Sets the address of the last write block of the continuous range to be erased.
                                                                           Reserved for each command system set by switch function command (CMD6).                  */
#define SDMMC_CMD_ERASE                                         38U   /*!< Reserved for SD security applications.                                                   */
#define SDMMC_CMD_FAST_IO                                       39U   /*!< SD card doesn't support it (Reserved).                                                   */
#define SDMMC_CMD_GO_IRQ_STATE                                  40U   /*!< SD card doesn't support it (Reserved).                                                   */
#define SDMMC_CMD_LOCK_UNLOCK                                   42U   /*!< Sets/resets the password or lock/unlock the card. The size of the data block is set by
                                                                           the SET_BLOCK_LEN command.                                                               */
#define SDMMC_CMD_APP_CMD                                       55U   /*!< Indicates to the card that the next command is an application specific command rather
                                                                           than a standard command.                                                                 */
#define SDMMC_CMD_GEN_CMD                                       56U   /*!< Used either to transfer a data block to the card or to get a data block from the card
                                                                           for general purpose/application specific commands.                                       */
#define SDMMC_CMD_NO_CMD                                        64U   /*!< No command                                                                               */

/**
  * @brief Following commands are SD Card Specific commands.
  *        SDMMC_APP_CMD should be sent before sending these commands.
  */
#define SDMMC_CMD_APP_SD_SET_BUSWIDTH                           6U    /*!< (ACMD6) Defines the data bus width to be used for data transfer. The allowed data bus
                                                                            widths are given in SCR register.                                                       */
#define SDMMC_CMD_SD_APP_STATUS                                 13U   /*!< (ACMD13) Sends the SD status.                                                            */
#define SDMMC_CMD_SD_APP_SEND_NUM_WRITE_BLOCKS                  22U   /*!< (ACMD22) Sends the number of the written (without errors) write blocks. Responds with
                                                                           32bit+CRC data block.                                                                    */
#define SDMMC_CMD_SD_APP_OP_COND                                41U   /*!< (ACMD41) Sends host capacity support information (HCS) and asks the accessed card to
                                                                           send its operating condition register (OCR) content in the response on the CMD line.     */
#define SDMMC_CMD_SD_APP_SET_CLR_CARD_DETECT                    42U   /*!< (ACMD42) Connect/Disconnect the 50 KOhm pull-up resistor on CD/DAT3 (pin 1) of the card  */
#define SDMMC_CMD_SD_APP_SEND_SCR                               51U   /*!< Reads the SD Configuration Register (SCR).                                               */
#define SDMMC_CMD_SDMMC_RW_DIRECT                               52U   /*!< For SD I/O card only, reserved for security specification.                               */
#define SDMMC_CMD_SDMMC_RW_EXTENDED                             53U   /*!< For SD I/O card only, reserved for security specification.                               */

/**
  * @brief Following commands are SD Card Specific security commands.
  *        SDMMC_CMD_APP_CMD should be sent before sending these commands.
  */
#define SDMMC_CMD_SD_APP_GET_MKB                                43U
#define SDMMC_CMD_SD_APP_GET_MID                                44U
#define SDMMC_CMD_SD_APP_SET_CER_RN1                            45U
#define SDMMC_CMD_SD_APP_GET_CER_RN2                            46U
#define SDMMC_CMD_SD_APP_SET_CER_RES2                           47U
#define SDMMC_CMD_SD_APP_GET_CER_RES1                           48U
#define SDMMC_CMD_SD_APP_SECURE_READ_MULTIPLE_BLOCK             18U
#define SDMMC_CMD_SD_APP_SECURE_WRITE_MULTIPLE_BLOCK            25U
#define SDMMC_CMD_SD_APP_SECURE_ERASE                           38U
#define SDMMC_CMD_SD_APP_CHANGE_SECURE_AREA                     49U
#define SDMMC_CMD_SD_APP_SECURE_WRITE_MKB                       48U


/******************************************************************************************/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Configuration of the SDIO **********************************/
void SDIO_DeInit(void);
void SDIO_odpullupConfig(uint32_t SDIO_odenable);
void SDIO_UseholdregConfig(uint32_t SDIO_Useholdregenable);
void SDIO_PowerEnableConfig(uint32_t SDIO_PowerEnable);
void SDIO_TimeOutConfig(uint32_t SDIO_TMOUTValue);
void SDIO_FifoThConfig(uint32_t SDIO_FIFOTHValue);
void SDIO_CardWidthConfig(uint32_t SDIO_CardWidth);
void SDIO_TransferModeConfig(uint32_t SDIO_TransferMode);
void SDIO_TransferDirectionConfig(uint32_t SDIO_ReadWrite);
void SDIO_DataExpectedConfig(uint32_t SDIO_DataExpected);
void SDIO_CheckResponseCRCConfig(uint32_t SDIO_CheckResponseCRC);
void SDIO_ResponseLengthConfig(uint32_t SDIO_ResponseLength);
void SDIO_ResponseLengthConfig(uint32_t SDIO_ResponseLength);
void SDIO_ResponseExpectConfig(uint32_t SDIO_ResponseExpect);
void SDIO_ChangeCardClock(uint32_t SDIO_Clkdiv);
void SDIO_SendCMD(uint32_t SDIO_CmdIndex);
void SDIO_CMDARGConfig(uint32_t SDIO_CmdArgument);
void SDIO_BlockSizeConfig(uint32_t SDIO_BlockSize);
void SDIO_ByteCountConfig(uint32_t SDIO_ByteCount);
void SDIO_ITConfig(uint32_t SDIO_IT);
FlagStatus SDIO_GetITFlag(uint32_t SDIO_FLAG);
void SDIO_ClearITFlag(uint32_t SDIO_FLAG);
uint32_t SDIO_GetFifoStatus(uint32_t SDIO_FIFOStatus);
uint32_t SDIO_GetStatus(uint32_t SDIO_Status);

#ifdef __cplusplus
}
#endif

#endif /* __FT32F4XX_SDIO_H */

/**
  * @}
  */


