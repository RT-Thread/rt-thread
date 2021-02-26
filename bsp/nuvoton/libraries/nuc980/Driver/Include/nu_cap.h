/**************************************************************************//**
 * @file     cap.h
 * @brief    Image Capture Driver Header File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_CAP_H__
#define __NU_CAP_H__

#ifdef __cplusplus
    #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
    #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

#ifdef __cplusplus
extern "C"
{
#endif

/*---------------------- Capture Engine -------------------------*/
/**
    @addtogroup CAP Capture Engine(CAP)
    Memory Mapped Structure for CAP Controller
@{ */

typedef struct
{
    __IO uint32_t CTL;
    __IO uint32_t PAR;
    __IO uint32_t INT;
    __IO uint32_t POSTERIZE;
    __IO uint32_t MD;
    __IO uint32_t MDADDR;
    __IO uint32_t MDYADDR;
    __IO uint32_t SEPIA;
    __IO uint32_t CWSP;
    __IO uint32_t CWS;
    __IO uint32_t PKTSL;
    __IO uint32_t PLNSL;
    __IO uint32_t FRCTL;
    __IO uint32_t STRIDE;
    /// @cond HIDDEN_SYMBOLS
    uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t FIFOTH;
    __IO uint32_t CMPADDR;
    /// @cond HIDDEN_SYMBOLS
    uint32_t RESERVE1[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t PKTSM;
    __IO uint32_t PLNSM;
    __I  uint32_t CURADDRP;
    __I  uint32_t CURADDRY;
    __I  uint32_t CURADDRU;
    __I  uint32_t CURVADDR;
    __IO uint32_t PKTBA0;
    __IO uint32_t PKTBA1;
    /// @cond HIDDEN_SYMBOLS
    uint32_t RESERVE2[6];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t YBA;
    __IO uint32_t UBA;
    __IO uint32_t VBA;

} CAP_T;

/**
    @addtogroup CAP_CONST CAP Bit Field Definition
    Constant Definitions for CAP Controller
@{ */

#define CAP_CTL_CAPEN_Pos                (0)                                               /*!< CAP_T::CTL: CAPEN Position                */
#define CAP_CTL_CAPEN_Msk                (0x1ul << CAP_CTL_CAPEN_Pos)                      /*!< CAP_T::CTL: CAPEN Mask                    */

#define CAP_CTL_ADDRSW_Pos               (3)                                               /*!< CAP_T::CTL: ADDRSW Position               */
#define CAP_CTL_ADDRSW_Msk               (0x1ul << CAP_CTL_ADDRSW_Pos)                     /*!< CAP_T::CTL: ADDRSW Mask                   */

#define CAP_CTL_PLNEN_Pos                (5)                                               /*!< CAP_T::CTL: PLNEN Position                */
#define CAP_CTL_PLNEN_Msk                (0x1ul << CAP_CTL_PLNEN_Pos)                      /*!< CAP_T::CTL: PLNEN Mask                    */

#define CAP_CTL_PKTEN_Pos                (6)                                               /*!< CAP_T::CTL: PKTEN Position                */
#define CAP_CTL_PKTEN_Msk                (0x1ul << CAP_CTL_PKTEN_Pos)                      /*!< CAP_T::CTL: PKTEN Mask                    */

#define CAP_CTL_SHUTTER_Pos              (16)                                              /*!< CAP_T::CTL: SHUTTER Position              */
#define CAP_CTL_SHUTTER_Msk              (0x1ul << CAP_CTL_SHUTTER_Pos)                    /*!< CAP_T::CTL: SHUTTER Mask                  */

#define CAP_CTL_UPDATE_Pos               (20)                                              /*!< CAP_T::CTL: UPDATE Position               */
#define CAP_CTL_UPDATE_Msk               (0x1ul << CAP_CTL_UPDATE_Pos)                     /*!< CAP_T::CTL: UPDATE Mask                   */

#define CAP_CTL_VPRST_Pos                (24)                                              /*!< CAP_T::CTL: VPRST Position                */
#define CAP_CTL_VPRST_Msk                (0x1ul << CAP_CTL_VPRST_Pos)                      /*!< CAP_T::CTL: VPRST Mask                    */

#define CAP_PAR_INFMT_Pos                (0)                                               /*!< CAP_T::PAR: INFMT Position                */
#define CAP_PAR_INFMT_Msk                (0x1ul << CAP_PAR_INFMT_Pos)                      /*!< CAP_T::PAR: INFMT Mask                    */

#define CAP_PAR_SENTYPE_Pos              (1)                                               /*!< CAP_T::PAR: SENTYPE Position              */
#define CAP_PAR_SENTYPE_Msk              (0x1ul << CAP_PAR_SENTYPE_Pos)                    /*!< CAP_T::PAR: SENTYPE Mask                  */

#define CAP_PAR_INDATORD_Pos             (2)                                               /*!< CAP_T::PAR: INDATORD Position             */
#define CAP_PAR_INDATORD_Msk             (0x3ul << CAP_PAR_INDATORD_Pos)                   /*!< CAP_T::PAR: INDATORD Mask                 */

#define CAP_PAR_OUTFMT_Pos               (4)                                               /*!< CAP_T::PAR: OUTFMT Position               */
#define CAP_PAR_OUTFMT_Msk               (0x3ul << CAP_PAR_OUTFMT_Pos)                     /*!< CAP_T::PAR: OUTFMT Mask                   */

#define CAP_PAR_RANGE_Pos                (6)                                               /*!< CAP_T::PAR: RANGE Position                */
#define CAP_PAR_RANGE_Msk                (0x1ul << CAP_PAR_RANGE_Pos)                      /*!< CAP_T::PAR: RANGE Mask                    */

#define CAP_PAR_PLNFMT_Pos               (7)                                               /*!< CAP_T::PAR: PLNFMT Position               */
#define CAP_PAR_PLNFMT_Msk               (0x1ul << CAP_PAR_PLNFMT_Pos)                     /*!< CAP_T::PAR: PLNFMT Mask                   */

#define CAP_PAR_PCLKP_Pos                (8)                                               /*!< CAP_T::PAR: PCLKP Position                */
#define CAP_PAR_PCLKP_Msk                (0x1ul << CAP_PAR_PCLKP_Pos)                      /*!< CAP_T::PAR: PCLKP Mask                    */

#define CAP_PAR_HSP_Pos                  (9)                                               /*!< CAP_T::PAR: HSP Position                  */
#define CAP_PAR_HSP_Msk                  (0x1ul << CAP_PAR_HSP_Pos)                        /*!< CAP_T::PAR: HSP Mask                      */

#define CAP_PAR_VSP_Pos                  (10)                                              /*!< CAP_T::PAR: VSP Position                  */
#define CAP_PAR_VSP_Msk                  (0x1ul << CAP_PAR_VSP_Pos)                        /*!< CAP_T::PAR: VSP Mask                      */

#define CAP_PAR_COLORCTL_Pos             (11)                                              /*!< CAP_T::PAR: COLORCTL Position             */
#define CAP_PAR_COLORCTL_Msk             (0x3ul << CAP_PAR_COLORCTL_Pos)                   /*!< CAP_T::PAR: COLORCTL Mask                 */

#define CAP_PAR_FBB_Pos                  (18)                                              /*!< CAP_T::PAR: FBB Position                  */
#define CAP_PAR_FBB_Msk                  (0x1ul << CAP_PAR_FBB_Pos)                        /*!< CAP_T::PAR: FBB Mask                      */

#define CAP_INT_VINTF_Pos                (0)                                               /*!< CAP_T::INT: VINTF Position                */
#define CAP_INT_VINTF_Msk                (0x1ul << CAP_INT_VINTF_Pos)                      /*!< CAP_T::INT: VINTF Mask                    */

#define CAP_INT_MEINTF_Pos               (1)                                               /*!< CAP_T::INT: MEINTF Position               */
#define CAP_INT_MEINTF_Msk               (0x1ul << CAP_INT_MEINTF_Pos)                     /*!< CAP_T::INT: MEINTF Mask                   */

#define CAP_INT_ADDRMINTF_Pos            (3)                                               /*!< CAP_T::INT: ADDRMINTF Position            */
#define CAP_INT_ADDRMINTF_Msk            (0x1ul << CAP_INT_ADDRMINTF_Pos)                  /*!< CAP_T::INT: ADDRMINTF Mask                */

#define CAP_INT_MDINTF_Pos               (4)                                               /*!< CAP_T::INT: MDINTF Position               */
#define CAP_INT_MDINTF_Msk               (0x1ul << CAP_INT_MDINTF_Pos)                     /*!< CAP_T::INT: MDINTF Mask                   */

#define CAP_INT_VIEN_Pos                 (16)                                              /*!< CAP_T::INT: VIEN Position                 */
#define CAP_INT_VIEN_Msk                 (0x1ul << CAP_INT_VIEN_Pos)                       /*!< CAP_T::INT: VIEN Mask                     */

#define CAP_INT_MEIEN_Pos                (17)                                              /*!< CAP_T::INT: MEIEN Position                */
#define CAP_INT_MEIEN_Msk                (0x1ul << CAP_INT_MEIEN_Pos)                      /*!< CAP_T::INT: MEIEN Mask                    */

#define CAP_INT_ADDRMIEN_Pos             (19)                                              /*!< CAP_T::INT: ADDRMIEN Position             */
#define CAP_INT_ADDRMIEN_Msk             (0x1ul << CAP_INT_ADDRMIEN_Pos)                   /*!< CAP_T::INT: ADDRMIEN Mask                 */

#define CAP_INT_MDIEN_Pos                (20)                                              /*!< CAP_T::INT: MDIEN Position                */
#define CAP_INT_MDIEN_Msk                (0x1ul << CAP_INT_MDIEN_Pos)                      /*!< CAP_T::INT: MDIEN Mask                    */

#define CAP_POSTERIZE_VCOMP_Pos          (0)                                               /*!< CAP_T::POSTERIZE: VCOMP Position          */
#define CAP_POSTERIZE_VCOMP_Msk          (0xfful << CAP_POSTERIZE_VCOMP_Pos)               /*!< CAP_T::POSTERIZE: VCOMP Mask              */

#define CAP_POSTERIZE_UCOMP_Pos          (8)                                               /*!< CAP_T::POSTERIZE: UCOMP Position          */
#define CAP_POSTERIZE_UCOMP_Msk          (0xfful << CAP_POSTERIZE_UCOMP_Pos)               /*!< CAP_T::POSTERIZE: UCOMP Mask              */

#define CAP_POSTERIZE_YCOMP_Pos          (16)                                              /*!< CAP_T::POSTERIZE: YCOMP Position          */
#define CAP_POSTERIZE_YCOMP_Msk          (0xfful << CAP_POSTERIZE_YCOMP_Pos)               /*!< CAP_T::POSTERIZE: YCOMP Mask              */

#define CAP_MD_MDEN_Pos                  (0)                                               /*!< CAP_T::MD: MDEN Position                  */
#define CAP_MD_MDEN_Msk                  (0x1ul << CAP_MD_MDEN_Pos)                        /*!< CAP_T::MD: MDEN Mask                      */

#define CAP_MD_MDBS_Pos                  (8)                                               /*!< CAP_T::MD: MDBS Position                  */
#define CAP_MD_MDBS_Msk                  (0x1ul << CAP_MD_MDBS_Pos)                        /*!< CAP_T::MD: MDBS Mask                      */

#define CAP_MD_MDSM_Pos                  (9)                                               /*!< CAP_T::MD: MDSM Position                  */
#define CAP_MD_MDSM_Msk                  (0x1ul << CAP_MD_MDSM_Pos)                        /*!< CAP_T::MD: MDSM Mask                      */

#define CAP_MD_MDDF_Pos                  (10)                                              /*!< CAP_T::MD: MDDF Position                  */
#define CAP_MD_MDDF_Msk                  (0x3ul << CAP_MD_MDDF_Pos)                        /*!< CAP_T::MD: MDDF Mask                      */

#define CAP_MD_MDTHR_Pos                 (16)                                              /*!< CAP_T::MD: MDTHR Position                 */
#define CAP_MD_MDTHR_Msk                 (0x1ful << CAP_MD_MDTHR_Pos)                      /*!< CAP_T::MD: MDTHR Mask                     */

#define CAP_MDADDR_MDADDR_Pos            (0)                                               /*!< CAP_T::MDADDR: MDADDR Position            */
#define CAP_MDADDR_MDADDR_Msk            (0xfffffffful << CAP_MDADDR_MDADDR_Pos)           /*!< CAP_T::MDADDR: MDADDR Mask                */

#define CAP_MDYADDR_MDYADDR_Pos          (0)                                               /*!< CAP_T::MDYADDR: MDYADDR Position          */
#define CAP_MDYADDR_MDYADDR_Msk          (0xfffffffful << CAP_MDYADDR_MDYADDR_Pos)         /*!< CAP_T::MDYADDR: MDYADDR Mask              */

#define CAP_SEPIA_VCOMP_Pos              (0)                                               /*!< CAP_T::SEPIA: VCOMP Position              */
#define CAP_SEPIA_VCOMP_Msk              (0xfful << CAP_SEPIA_VCOMP_Pos)                   /*!< CAP_T::SEPIA: VCOMP Mask                  */

#define CAP_SEPIA_UCOMP_Pos              (8)                                               /*!< CAP_T::SEPIA: UCOMP Position              */
#define CAP_SEPIA_UCOMP_Msk              (0xfful << CAP_SEPIA_UCOMP_Pos)                   /*!< CAP_T::SEPIA: UCOMP Mask                  */

#define CAP_CWSP_CWSADDRH_Pos            (0)                                               /*!< CAP_T::CWSP: CWSADDRH Position            */
#define CAP_CWSP_CWSADDRH_Msk            (0xffful << CAP_CWSP_CWSADDRH_Pos)                /*!< CAP_T::CWSP: CWSADDRH Mask                */

#define CAP_CWSP_CWSADDRV_Pos            (16)                                              /*!< CAP_T::CWSP: CWSADDRV Position            */
#define CAP_CWSP_CWSADDRV_Msk            (0x7fful << CAP_CWSP_CWSADDRV_Pos)                /*!< CAP_T::CWSP: CWSADDRV Mask                */

#define CAP_CWS_CWW_Pos                  (0)                                               /*!< CAP_T::CWS: CWW Position                 */
#define CAP_CWS_CWW_Msk                  (0xffful << CAP_CWS_CWW_Pos)                      /*!< CAP_T::CWS: CWW Mask                     */

#define CAP_CWS_CWH_Pos                  (16)                                              /*!< CAP_T::CWS: CIWH Position                 */
#define CAP_CWS_CWH_Msk                  (0x7fful << CAP_CWS_CWH_Pos)                      /*!< CAP_T::CWS: CIWH Mask                     */

#define CAP_PKTSL_PKTSHML_Pos            (0)                                               /*!< CAP_T::PKTSL: PKTSHML Position            */
#define CAP_PKTSL_PKTSHML_Msk            (0xfful << CAP_PKTSL_PKTSHML_Pos)                 /*!< CAP_T::PKTSL: PKTSHML Mask                */

#define CAP_PKTSL_PKTSHNL_Pos            (8)                                               /*!< CAP_T::PKTSL: PKTSHNL Position            */
#define CAP_PKTSL_PKTSHNL_Msk            (0xfful << CAP_PKTSL_PKTSHNL_Pos)                 /*!< CAP_T::PKTSL: PKTSHNL Mask                */

#define CAP_PKTSL_PKTSVML_Pos            (16)                                              /*!< CAP_T::PKTSL: PKTSVML Position            */
#define CAP_PKTSL_PKTSVML_Msk            (0xfful << CAP_PKTSL_PKTSVML_Pos)                 /*!< CAP_T::PKTSL: PKTSVML Mask                */

#define CAP_PKTSL_PKTSVNL_Pos            (24)                                              /*!< CAP_T::PKTSL: PKTSVNL Position            */
#define CAP_PKTSL_PKTSVNL_Msk            (0xfful << CAP_PKTSL_PKTSVNL_Pos)                 /*!< CAP_T::PKTSL: PKTSVNL Mask                */

#define CAP_PLNSL_PLNSHML_Pos            (0)                                               /*!< CAP_T::PLNSL: PLNSHML Position            */
#define CAP_PLNSL_PLNSHML_Msk            (0xfful << CAP_PLNSL_PLNSHML_Pos)                 /*!< CAP_T::PLNSL: PLNSHML Mask                */

#define CAP_PLNSL_PLNSHNL_Pos            (8)                                               /*!< CAP_T::PLNSL: PLNSHNL Position            */
#define CAP_PLNSL_PLNSHNL_Msk            (0xfful << CAP_PLNSL_PLNSHNL_Pos)                 /*!< CAP_T::PLNSL: PLNSHNL Mask                */

#define CAP_PLNSL_PLNSVML_Pos            (16)                                              /*!< CAP_T::PLNSL: PLNSVML Position            */
#define CAP_PLNSL_PLNSVML_Msk            (0xfful << CAP_PLNSL_PLNSVML_Pos)                 /*!< CAP_T::PLNSL: PLNSVML Mask                */

#define CAP_PLNSL_PLNSVNL_Pos            (24)                                              /*!< CAP_T::PLNSL: PLNSVNL Position            */
#define CAP_PLNSL_PLNSVNL_Msk            (0xfful << CAP_PLNSL_PLNSVNL_Pos)                 /*!< CAP_T::PLNSL: PLNSVNL Mask                */

#define CAP_FRCTL_FRM_Pos                (0)                                               /*!< CAP_T::FRCTL: FRM Position                */
#define CAP_FRCTL_FRM_Msk                (0x3ful << CAP_FRCTL_FRM_Pos)                     /*!< CAP_T::FRCTL: FRM Mask                    */

#define CAP_FRCTL_FRN_Pos                (8)                                               /*!< CAP_T::FRCTL: FRN Position                */
#define CAP_FRCTL_FRN_Msk                (0x3ful << CAP_FRCTL_FRN_Pos)                     /*!< CAP_T::FRCTL: FRN Mask                    */

#define CAP_STRIDE_PKTSTRIDE_Pos         (0)                                               /*!< CAP_T::STRIDE: PKTSTRIDE Position         */
#define CAP_STRIDE_PKTSTRIDE_Msk         (0x3ffful << CAP_STRIDE_PKTSTRIDE_Pos)            /*!< CAP_T::STRIDE: PKTSTRIDE Mask             */

#define CAP_STRIDE_PLNSTRIDE_Pos         (16)                                              /*!< CAP_T::STRIDE: PLNSTRIDE Position         */
#define CAP_STRIDE_PLNSTRIDE_Msk         (0x3ffful << CAP_STRIDE_PLNSTRIDE_Pos)            /*!< CAP_T::STRIDE: PLNSTRIDE Mask             */

#define CAP_FIFOTH_PLNVFTH_Pos           (0)                                               /*!< CAP_T::FIFOTH: PLNVFTH Position           */
#define CAP_FIFOTH_PLNVFTH_Msk           (0xful << CAP_FIFOTH_PLNVFTH_Pos)                 /*!< CAP_T::FIFOTH: PLNVFTH Mask               */

#define CAP_FIFOTH_PLNUFTH_Pos           (8)                                               /*!< CAP_T::FIFOTH: PLNUFTH Position           */
#define CAP_FIFOTH_PLNUFTH_Msk           (0xful << CAP_FIFOTH_PLNUFTH_Pos)                 /*!< CAP_T::FIFOTH: PLNUFTH Mask               */

#define CAP_FIFOTH_PLNYFTH_Pos           (16)                                              /*!< CAP_T::FIFOTH: PLNYFTH Position           */
#define CAP_FIFOTH_PLNYFTH_Msk           (0x1ful << CAP_FIFOTH_PLNYFTH_Pos)                /*!< CAP_T::FIFOTH: PLNYFTH Mask               */

#define CAP_FIFOTH_PKTFTH_Pos            (24)                                              /*!< CAP_T::FIFOTH: PKTFTH Position            */
#define CAP_FIFOTH_PKTFTH_Msk            (0x1ful << CAP_FIFOTH_PKTFTH_Pos)                 /*!< CAP_T::FIFOTH: PKTFTH Mask                */

#define CAP_FIFOTH_OVF_Pos               (31)                                              /*!< CAP_T::FIFOTH: OVF Position               */
#define CAP_FIFOTH_OVF_Msk               (0x1ul << CAP_FIFOTH_OVF_Pos)                     /*!< CAP_T::FIFOTH: OVF Mask                   */

#define CAP_CMPADDR_CMPADDR_Pos          (0)                                               /*!< CAP_T::CMPADDR: CMPADDR Position          */
#define CAP_CMPADDR_CMPADDR_Msk          (0xfffffffful << CAP_CMPADDR_CMPADDR_Pos)         /*!< CAP_T::CMPADDR: CMPADDR Mask              */

#define CAP_PKTSM_PKTSHMH_Pos            (0)                                               /*!< CAP_T::PKTSM: PKTSHMH Position            */
#define CAP_PKTSM_PKTSHMH_Msk            (0xfful << CAP_PKTSM_PKTSHMH_Pos)                 /*!< CAP_T::PKTSM: PKTSHMH Mask                */

#define CAP_PKTSM_PKTSHNH_Pos            (8)                                               /*!< CAP_T::PKTSM: PKTSHNH Position            */
#define CAP_PKTSM_PKTSHNH_Msk            (0xfful << CAP_PKTSM_PKTSHNH_Pos)                 /*!< CAP_T::PKTSM: PKTSHNH Mask                */

#define CAP_PKTSM_PKTSVMH_Pos            (16)                                              /*!< CAP_T::PKTSM: PKTSVMH Position            */
#define CAP_PKTSM_PKTSVMH_Msk            (0xfful << CAP_PKTSM_PKTSVMH_Pos)                 /*!< CAP_T::PKTSM: PKTSVMH Mask                */

#define CAP_PKTSM_PKTSVNH_Pos            (24)                                              /*!< CAP_T::PKTSM: PKTSVNH Position            */
#define CAP_PKTSM_PKTSVNH_Msk            (0xfful << CAP_PKTSM_PKTSVNH_Pos)                 /*!< CAP_T::PKTSM: PKTSVNH Mask                */

#define CAP_PLNSM_PLNSHMH_Pos            (0)                                               /*!< CAP_T::PLNSM: PLNSHMH Position            */
#define CAP_PLNSM_PLNSHMH_Msk            (0xfful << CAP_PLNSM_PLNSHMH_Pos)                 /*!< CAP_T::PLNSM: PLNSHMH Mask                */

#define CAP_PLNSM_PLNSHNH_Pos            (8)                                               /*!< CAP_T::PLNSM: PLNSHNH Position            */
#define CAP_PLNSM_PLNSHNH_Msk            (0xfful << CAP_PLNSM_PLNSHNH_Pos)                 /*!< CAP_T::PLNSM: PLNSHNH Mask                */

#define CAP_PLNSM_PLNSVMH_Pos            (16)                                              /*!< CAP_T::PLNSM: PLNSVMH Position            */
#define CAP_PLNSM_PLNSVMH_Msk            (0xfful << CAP_PLNSM_PLNSVMH_Pos)                 /*!< CAP_T::PLNSM: PLNSVMH Mask                */

#define CAP_PLNSM_PLNSVNH_Pos            (24)                                              /*!< CAP_T::PLNSM: PLNSVNH Position            */
#define CAP_PLNSM_PLNSVNH_Msk            (0xfful << CAP_PLNSM_PLNSVNH_Pos)                 /*!< CAP_T::PLNSM: PLNSVNH Mask                */

#define CAP_CURADDRP_CURADDR_Pos         (0)                                               /*!< CAP_T::CURADDRP: CURADDR Position         */
#define CAP_CURADDRP_CURADDR_Msk         (0xfffffffful << CAP_CURADDRP_CURADDR_Pos)        /*!< CAP_T::CURADDRP: CURADDR Mask             */

#define CAP_CURADDRY_CURADDR_Pos         (0)                                               /*!< CAP_T::CURADDRY: CURADDR Position         */
#define CAP_CURADDRY_CURADDR_Msk         (0xfffffffful << CAP_CURADDRY_CURADDR_Pos)        /*!< CAP_T::CURADDRY: CURADDR Mask             */

#define CAP_CURADDRU_CURADDR_Pos         (0)                                               /*!< CAP_T::CURADDRU: CURADDR Position         */
#define CAP_CURADDRU_CURADDR_Msk         (0xfffffffful << CAP_CURADDRU_CURADDR_Pos)        /*!< CAP_T::CURADDRU: CURADDR Mask             */

#define CAP_CURVADDR_CURADDR_Pos         (0)                                               /*!< CAP_T::CURVADDR: CURADDR Position         */
#define CAP_CURVADDR_CURADDR_Msk         (0xfffffffful << CAP_CURVADDR_CURADDR_Pos)        /*!< CAP_T::CURVADDR: CURADDR Mask             */

#define CAP_PKTBA0_BASEADDR_Pos          (0)                                               /*!< CAP_T::PKTBA0: BASEADDR Position          */
#define CAP_PKTBA0_BASEADDR_Msk          (0xfffffffful << CAP_PKTBA0_BASEADDR_Pos)         /*!< CAP_T::PKTBA0: BASEADDR Mask              */

#define CAP_PKTBA1_BASEADDR_Pos          (0)                                               /*!< CAP_T::PKTBA1: BASEADDR Position          */
#define CAP_PKTBA1_BASEADDR_Msk          (0xfffffffful << CAP_PKTBA1_BASEADDR_Pos)         /*!< CAP_T::PKTBA1: BASEADDR Mask              */

#define CAP_YBA_BASEADDR_Pos             (0)                                               /*!< CAP_T::YBA: BASEADDR Position             */
#define CAP_YBA_BASEADDR_Msk             (0xfffffffful << CAP_YBA_BASEADDR_Pos)            /*!< CAP_T::YBA: BASEADDR Mask                 */

#define CAP_UBA_BASEADDR_Pos             (0)                                               /*!< CAP_T::UBA: BASEADDR Position             */
#define CAP_UBA_BASEADDR_Msk             (0xfffffffful << CAP_UBA_BASEADDR_Pos)            /*!< CAP_T::UBA: BASEADDR Mask                 */

#define CAP_VBA_BASEADDR_Pos             (0)                                               /*!< CAP_T::VBA: BASEADDR Position             */
#define CAP_VBA_BASEADDR_Msk             (0xfffffffful << CAP_VBA_BASEADDR_Pos)            /*!< CAP_T::VBA: BASEADDR Mask                 */

/**@}*/ /* CAP_CONST */
/**@}*/ /* end of CAP register group */


#define CAP0                  ((CAP_T *)   CAP0_BA)
#define CAP1                  ((CAP_T *)   CAP1_BA)

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CAP_Driver CAP Driver
  @{
*/

/** @addtogroup CAP_EXPORTED_CONSTANTS CAP Exported Constants
  @{
*/




/*---------------------------------------------------------------------------------------------------------*/
/* VINCTRL constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define CAP_CTL_CAPEN      (1ul<<CAP_CTL_CAPEN_Pos)     /*!< CAP CTL setting for enabling capture engine mode  \hideinitializer */
#define CAP_CTL_ADDRSW     (1ul<<CAP_CTL_ADDRSW_Pos)    /*!< CAP CTL setting for packet buffer address switch  \hideinitializer */
#define CAP_CTL_PKTEN      (1ul<<CAP_CTL_PKTEN_Pos)     /*!< CAP CTL setting for enabling packet output mode  \hideinitializer */
#define CAP_CTL_PLNEN      (1ul<<CAP_CTL_PLNEN_Pos)     /*!< CAP CTL setting for enabling planar output mode  \hideinitializer */
#define CAP_CTL_SHUTTER    (1ul<<CAP_CTL_SHUTTER_Pos)   /*!< CAP CTL setting for enabling shutter mode  \hideinitializer */
#define CAP_CTL_UPDATE     (1ul<<CAP_CTL_UPDATE_Pos)    /*!< CAP CTL setting for enabling update register at new frame  \hideinitializer */
#define CAP_CTL_RESET      (1ul<<CAP_CTL_VPRST_Pos)     /*!< CAP CTL setting for capture reset  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* CAPPAR constant definitions                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define CAP_PAR_INFMT_YUV422 (0ul<<CAP_PAR_INFMT_Pos)         /*!< CAP PAR setting for Sensor Input Data YUV422 Format   \hideinitializer */
#define CAP_PAR_INFMT_RGB565 (1ul<<CAP_PAR_INFMT_Pos)         /*!< CAP PAR setting for Sensor Input Data RGB565 Format   \hideinitializer */

#define CAP_PAR_SENTYPE_CCIR601  (0ul<<CAP_PAR_SENTYPE_Pos)   /*!< CAP PAR setting for Sensor Input CCIR601 Type   \hideinitializer */
#define CAP_PAR_SENTYPE_CCIR656  (1ul<<CAP_PAR_SENTYPE_Pos)   /*!< CAP PAR setting for Sensor Input CCIR656 Type   \hideinitializer */

#define CAP_PAR_INDATORD_YUYV   (0x0ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, YUYV  \hideinitializer */
#define CAP_PAR_INDATORD_YVYU   (0x1ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, YVYU  \hideinitializer */
#define CAP_PAR_INDATORD_UYVY   (0x2ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, UYVY  \hideinitializer */
#define CAP_PAR_INDATORD_VYUY   (0x3ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, VYUY  \hideinitializer */

#define CAP_PAR_INDATORD_RGGB   (0x0ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, 0byte: R[0:4] G[5:8], 1byte G[0:2] R[3:8]  \hideinitializer */
#define CAP_PAR_INDATORD_BGGR   (0x1ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, 0byte: b[0:4] G[5:8], 1byte G[0:2] R[3:8]  \hideinitializer */
#define CAP_PAR_INDATORD_GBRG   (0x2ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, 0byte: G[0:3] G[4:8], 1byte G[0:4] G[5:8]  \hideinitializer */
#define CAP_PAR_INDATORD_GRBG   (0x3ul<<CAP_PAR_INDATORD_Pos)       /*!< CAP PAR setting for Sensor Input Data Order, 0byte: G[0:3] G[4:8], 1byte G[0:4] G[5:8]  \hideinitializer */

#define CAP_PAR_OUTFMT_YUV422 (0x0ul<<CAP_PAR_OUTFMT_Pos)     /*!< CAP PAR setting for Image Data YUV422 Format Output to System Memory  \hideinitializer */
#define CAP_PAR_OUTFMT_ONLY_Y (0x1ul<<CAP_PAR_OUTFMT_Pos)     /*!< CAP PAR setting for Image Data ONLY_Y Format Output to System Memory  \hideinitializer */
#define CAP_PAR_OUTFMT_RGB555 (0x2ul<<CAP_PAR_OUTFMT_Pos)     /*!< CAP PAR setting for Image Data RGB555 Format Output to System Memory  \hideinitializer */
#define CAP_PAR_OUTFMT_RGB565 (0x3ul<<CAP_PAR_OUTFMT_Pos)     /*!< CAP PAR setting for Image Data RGB565 Format Output to System Memory  \hideinitializer */

#define CAP_PAR_PLNFMT_YUV422 (0x0ul<<CAP_PAR_PLNFMT_Pos)       /*!< CAP PAR setting for Planar Output YUV422 Format  \hideinitializer */
#define CAP_PAR_PLNFMT_YUV420 (0x1ul<<CAP_PAR_PLNFMT_Pos)       /*!< CAP PAR setting for Planar Output YUV420 Format  \hideinitializer */

#define CAP_PAR_VSP_LOW      (0x0ul<<CAP_PAR_VSP_Pos)         /*!< CAP PAR setting for Sensor Vsync Polarity  \hideinitializer */
#define CAP_PAR_VSP_HIGH     (0x1ul<<CAP_PAR_VSP_Pos)         /*!< CAP PAR setting for Sensor Vsync Polarity  \hideinitializer */
#define CAP_PAR_HSP_LOW      (0x0ul<<CAP_PAR_HSP_Pos)         /*!< CAP PAR setting for Sensor Hsync Polarity  \hideinitializer */
#define CAP_PAR_HSP_HIGH     (0x1ul<<CAP_PAR_HSP_Pos)         /*!< CAP PAR setting for Sensor Hsync Polarity  \hideinitializer */
#define CAP_PAR_PCLKP_LOW    (0x0ul<<CAP_PAR_PCLKP_Pos)       /*!< CAP PAR setting for Sensor Pixel Clock Polarity  \hideinitializer */
#define CAP_PAR_PCLKP_HIGH   (0x1ul<<CAP_PAR_PCLKP_Pos)       /*!< CAP PAR setting for Sensor Pixel Clock Polarity  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* VININT constant definitions                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define CAP_INT_VIEN_ENABLE        (0x1ul<<CAP_INT_VIEN_Pos)        /*!< VININT setting for Frame End Interrupt enable  \hideinitializer */
#define CAP_INT_MEIEN_ENABLE       (0x1ul<<CAP_INT_MEIEN_Pos)       /*!< VININT setting for Bus Master Transfer Error Interrupt enable  \hideinitializer */
#define CAP_INT_ADDRMIEN_ENABLE    (0x1ul<<CAP_INT_ADDRMIEN_Pos)    /*!< VININT setting for Memory Address Match Interrupt enable  \hideinitializer */
#define CAP_INT_MDIEN_ENABLE       (0x1ul<<CAP_INT_MDIEN_Pos)       /*!< VININT setting for Motion Detection Output Finish Interrupt Enable enable  \hideinitializer */


static uint32_t u32EscapeFrame = 0;
/*---------------------------------------------------------------------------------------------------------*/
/*  Define Error Code                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define CAP_INVALID_INT               ((int32_t)(0xFFFFFFFF-1))
#define CAP_INVALID_BUF               ((int32_t)(0xFFFFFFFF-2))
#define CAP_INVALID_PIPE              ((int32_t)(0xFFFFFFFF-3))


/*@}*/ /* end of group CAP_EXPORTED_CONSTANTS */



/** @addtogroup CAP_EXPORTED_FUNCTIONS CAP Exported Functions
  @{
*/

/**
 * @brief     Is CAP module Enable
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @return   FALSE(Enable) or TRUE(Disable)
 *
 * @details   Check Image Capture Interface module Enable or Disable
 *  \hideinitializer
 */
#define CAP_IS_STOPPED(VCAP)  ((VCAP->CTL & CAP_CTL_CAPEN_Msk)?0:1)

/**
 * @brief     Clear CAP flag
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @param[in] u32IntMask interrupt flags settings. It could be
 *                   - \ref CAP_INT_VINTF_Msk
 *                   - \ref CAP_INT_MEINTF_Msk
 *                   - \ref CAP_INT_ADDRMINTF_Msk
 *                   - \ref CAP_INT_MDINTF_Msk
 *
 * @return    TRUE(Enable) or FALSE(Disable)
 *
 * @details   Clear Image Capture Interface interrupt flag
 *  \hideinitializer
 */
#define CAP_CLR_INT_FLAG(VCAP,u32IntMask) (VCAP->INT |=u32IntMask)

/**
 * @brief     Get CAP Interrupt status
 *
 * @param[in]  VCAP: The pointer of the specified CAP module
 *
 * @return    TRUE(Enable) or FALSE(Disable)
 *
 * @details   Get Image Capture Interface interrupt status.
 * \hideinitializer
 */
#define CAP_GET_INT_STS(VCAP) (VCAP->INT)

void CAP_Open(CAP_T *VCAP, uint32_t u32InFormat, uint32_t u32OutFormet);
void CAP_SetCroppingWindow(CAP_T *VCAP, uint32_t u32VStart, uint32_t u32HStart, uint32_t u32Height, uint32_t u32Width);
void CAP_SetPacketBuf(CAP_T *VCAP, uint32_t  u32Address);
void CAP_SetPlanarBuf(CAP_T *VCAP, uint32_t u32YAddr, uint32_t u32UAddr, uint32_t u32VAddr);
void CAP_Close(CAP_T *VCAP);
void CAP_EnableInt(CAP_T *VCAP, uint32_t u32IntMask);
void CAP_DisableInt(CAP_T *VCAP, uint32_t u32IntMask);
void CAP_Start(CAP_T *VCAP);
void CAP_Stop(CAP_T *VCAP, uint32_t u32FrameComplete);
void CAP_SetPacketScaling(CAP_T *VCAP, uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator);
void CAP_SetPlanarScaling(CAP_T *VCAP, uint32_t u32VNumerator, uint32_t u32VDenominator, uint32_t u32HNumerator, uint32_t u32HDenominator);
void CAP_SetPacketStride(CAP_T *VCAP, uint32_t u32Stride);
void CAP_SetPlanarStride(CAP_T *VCAP, uint32_t u32Stride);
void CAP_EnableMotionDet(CAP_T *VCAP, uint32_t u32Freq, uint32_t u32BlockSize, uint32_t u32Format, uint32_t u32Threshold,  uint32_t u32YDetAddr, uint32_t u32DetAddr);
void CAP_DisableMotionDet(CAP_T *VCAP);

/*@}*/ /* end of group CAP_EXPORTED_FUNCTIONS */



/*@}*/ /* end of group CAP_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__CAP_H__

