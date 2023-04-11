/***************************************************************************//**
* \file cy_device_headers.h
*
* \brief
* Common header file to be included by the drivers.
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef _CY_DEVICE_HEADERS_H_
#define _CY_DEVICE_HEADERS_H_

#if defined (CY_DEVICE_COMMON)
    #include "cy_device_common.h"
#elif defined (CY8C6036BZI_F04)
    #include "cy8c6036bzi_f04.h"
#elif defined (CY8C6016BZI_F04)
    #include "cy8c6016bzi_f04.h"
#elif defined (CY8C6116BZI_F54)
    #include "cy8c6116bzi_f54.h"
#elif defined (CY8C6136BZI_F14)
    #include "cy8c6136bzi_f14.h"
#elif defined (CY8C6136BZI_F34)
    #include "cy8c6136bzi_f34.h"
#elif defined (CY8C6137BZI_F14)
    #include "cy8c6137bzi_f14.h"
#elif defined (CY8C6137BZI_F34)
    #include "cy8c6137bzi_f34.h"
#elif defined (CY8C6137BZI_F54)
    #include "cy8c6137bzi_f54.h"
#elif defined (CY8C6117BZI_F34)
    #include "cy8c6117bzi_f34.h"
#elif defined (CY8C6246BZI_D04)
    #include "cy8c6246bzi_d04.h"
#elif defined (CY8C6247BZI_D44)
    #include "cy8c6247bzi_d44.h"
#elif defined (CY8C6247BZI_D34)
    #include "cy8c6247bzi_d34.h"
#elif defined (CY8C6247BZI_D54)
    #include "cy8c6247bzi_d54.h"
#elif defined (CY8C6336BZI_BLF03)
    #include "cy8c6336bzi_blf03.h"
#elif defined (CY8C6316BZI_BLF03)
    #include "cy8c6316bzi_blf03.h"
#elif defined (CY8C6316BZI_BLF53)
    #include "cy8c6316bzi_blf53.h"
#elif defined (CY8C6336BZI_BLD13)
    #include "cy8c6336bzi_bld13.h"
#elif defined (CY8C6347BZI_BLD43)
    #include "cy8c6347bzi_bld43.h"
#elif defined (CY8C6347BZI_BLD33)
    #include "cy8c6347bzi_bld33.h"
#elif defined (CY8C6347BZI_BLD53)
    #include "cy8c6347bzi_bld53.h"
#elif defined (CY8C6347FMI_BLD13)
    #include "cy8c6347fmi_bld13.h"
#elif defined (CY8C6347FMI_BLD43)
    #include "cy8c6347fmi_bld43.h"
#elif defined (CY8C6347FMI_BLD33)
    #include "cy8c6347fmi_bld33.h"
#elif defined (CY8C6347FMI_BLD53)
    #include "cy8c6347fmi_bld53.h"
#elif defined (CY8C637BZI_MD76)
    #include "cy8c637bzi_md76.h"
#elif defined (CY8C637BZI_BLD74)
    #include "cy8c637bzi_bld74.h"
#elif defined (CY8C637FMI_BLD73)
    #include "cy8c637fmi_bld73.h"
#elif defined (CY8C68237BZ_BLE)
    #include "cy8c68237bz_ble.h"
#elif defined (CY8C68237FM_BLE)
    #include "cy8c68237fm_ble.h"
#elif defined (CY8C6137FDI_F02)
    #include "cy8c6137fdi_f02.h"
#elif defined (CY8C6117FDI_F02)
    #include "cy8c6117fdi_f02.h"
#elif defined (CY8C6247FDI_D02)
    #include "cy8c6247fdi_d02.h"
#elif defined (CY8C6247FDI_D32)
    #include "cy8c6247fdi_d32.h"
#elif defined (CY8C6336BZI_BUD13)
    #include "cy8c6336bzi_bud13.h"
#elif defined (CY8C6347BZI_BUD43)
    #include "cy8c6347bzi_bud43.h"
#elif defined (CY8C6347BZI_BUD33)
    #include "cy8c6347bzi_bud33.h"
#elif defined (CY8C6347BZI_BUD53)
    #include "cy8c6347bzi_bud53.h"
#elif defined (CY8C6337BZI_BLF13)
    #include "cy8c6337bzi_blf13.h"
#elif defined (CY8C6136FDI_F42)
    #include "cy8c6136fdi_f42.h"
#elif defined (CY8C6247FDI_D52)
    #include "cy8c6247fdi_d52.h"
#elif defined (CY8C6136FTI_F42)
    #include "cy8c6136fti_f42.h"
#elif defined (CY8C6247FTI_D52)
    #include "cy8c6247fti_d52.h"
#elif defined (CY8C6247BZI_AUD54)
    #include "cy8c6247bzi_aud54.h"
#elif defined (CY8C6336BZI_BLF04)
    #include "cy8c6336bzi_blf04.h"
#elif defined (CY8C6316BZI_BLF04)
    #include "cy8c6316bzi_blf04.h"
#elif defined (CY8C6316BZI_BLF54)
    #include "cy8c6316bzi_blf54.h"
#elif defined (CY8C6336BZI_BLD14)
    #include "cy8c6336bzi_bld14.h"
#elif defined (CY8C6347BZI_BLD44)
    #include "cy8c6347bzi_bld44.h"
#elif defined (CY8C6347BZI_BLD34)
    #include "cy8c6347bzi_bld34.h"
#elif defined (CY8C6347BZI_BLD54)
    #include "cy8c6347bzi_bld54.h"
#elif defined (CY8C6247BFI_D54)
    #include "cy8c6247bfi_d54.h"
#elif defined (CYBLE_416045_02_device)
    #include "cyble_416045_02_device.h"
#elif defined (CY8C6347FMI_BUD53)
    #include "cy8c6347fmi_bud53.h"
#elif defined (CY8C6347FMI_BUD13)
    #include "cy8c6347fmi_bud13.h"
#elif defined (CY8C6347FMI_BUD43)
    #include "cy8c6347fmi_bud43.h"
#elif defined (CY8C6347FMI_BUD33)
    #include "cy8c6347fmi_bud33.h"
#elif defined (CY8C6137WI_F54)
    #include "cy8c6137wi_f54.h"
#elif defined (CY8C6117WI_F34)
    #include "cy8c6117wi_f34.h"
#elif defined (CY8C6247WI_D54)
    #include "cy8c6247wi_d54.h"
#elif defined (CY8C6336LQI_BLF02)
    #include "cy8c6336lqi_blf02.h"
#elif defined (CY8C6336LQI_BLF42)
    #include "cy8c6336lqi_blf42.h"
#elif defined (CY8C6347LQI_BLD52)
    #include "cy8c6347lqi_bld52.h"
#elif defined (CYB06447BZI_BLD54)
    #include "cyb06447bzi_bld54.h"
#elif defined (CYB06447BZI_BLD53)
    #include "cyb06447bzi_bld53.h"
#elif defined (CYB06447BZI_D54)
    #include "cyb06447bzi_d54.h"
#elif defined (CYB0644ABZI_S2D44)
    #include "cyb0644abzi_s2d44.h"
#elif defined (CYS0644ABZI_S2D44)
    #include "cys0644abzi_s2d44.h"
#elif defined (CYS0644AFNI_S2D43)
    #include "cys0644afni_s2d43.h"
#elif defined (CY8C624ABZI_S2D44A0)
    #include "cy8c624abzi_s2d44a0.h"
#elif defined (CY8C624ABZI_S2D44)
    #include "cy8c624abzi_s2d44.h"
#elif defined (CY8C624AAZI_S2D44)
    #include "cy8c624aazi_s2d44.h"
#elif defined (CY8C624AFNI_S2D43)
    #include "cy8c624afni_s2d43.h"
#elif defined (CY8C624ABZI_S2D04)
    #include "cy8c624abzi_s2d04.h"
#elif defined (CY8C624ABZI_S2D14)
    #include "cy8c624abzi_s2d14.h"
#elif defined (CY8C624AAZI_S2D14)
    #include "cy8c624aazi_s2d14.h"
#elif defined (CY8C6248AZI_S2D14)
    #include "cy8c6248azi_s2d14.h"
#elif defined (CY8C6248BZI_S2D44)
    #include "cy8c6248bzi_s2d44.h"
#elif defined (CY8C6248AZI_S2D44)
    #include "cy8c6248azi_s2d44.h"
#elif defined (CY8C6248FNI_S2D43)
    #include "cy8c6248fni_s2d43.h"
#elif defined (CY8C614ABZI_S2F04)
    #include "cy8c614abzi_s2f04.h"
#elif defined (CY8C614AAZI_S2F04)
    #include "cy8c614aazi_s2f04.h"
#elif defined (CY8C614AFNI_S2F03)
    #include "cy8c614afni_s2f03.h"
#elif defined (CY8C614AAZI_S2F14)
    #include "cy8c614aazi_s2f14.h"
#elif defined (CY8C614ABZI_S2F44)
    #include "cy8c614abzi_s2f44.h"
#elif defined (CY8C614AAZI_S2F44)
    #include "cy8c614aazi_s2f44.h"
#elif defined (CY8C614AFNI_S2F43)
    #include "cy8c614afni_s2f43.h"
#elif defined (CY8C6148BZI_S2F44)
    #include "cy8c6148bzi_s2f44.h"
#elif defined (CY8C6148AZI_S2F44)
    #include "cy8c6148azi_s2f44.h"
#elif defined (CY8C6148FNI_S2F43)
    #include "cy8c6148fni_s2f43.h"
#elif defined (CY8C624ABZI_D44)
    #include "cy8c624abzi_d44.h"
#elif defined (CY8C624AAZI_D44)
    #include "cy8c624aazi_d44.h"
#elif defined (CY8C624AFNI_D43)
    #include "cy8c624afni_d43.h"
#elif defined (CY8C624ABZI_D04)
    #include "cy8c624abzi_d04.h"
#elif defined (CY8C624ABZI_D14)
    #include "cy8c624abzi_d14.h"
#elif defined (CY8C624AAZI_D14)
    #include "cy8c624aazi_d14.h"
#elif defined (CY8C6248AZI_D14)
    #include "cy8c6248azi_d14.h"
#elif defined (CY8C6248BZI_D44)
    #include "cy8c6248bzi_d44.h"
#elif defined (CY8C6248AZI_D44)
    #include "cy8c6248azi_d44.h"
#elif defined (CY8C6248FNI_D43)
    #include "cy8c6248fni_d43.h"
#elif defined (CY8C624ALQI_D42)
    #include "cy8c624alqi_d42.h"
#elif defined (CY8C624ALQI_S2D42)
    #include "cy8c624alqi_s2d42.h"
#elif defined (CY8C624ALQI_S2D02)
    #include "cy8c624alqi_s2d02.h"
#elif defined (CY8C6248LQI_S2D42)
    #include "cy8c6248lqi_s2d42.h"
#elif defined (CY8C6248LQI_S2D02)
    #include "cy8c6248lqi_s2d02.h"
#elif defined (CY8C614ALQI_S2F42)
    #include "cy8c614alqi_s2f42.h"
#elif defined (CY8C614ALQI_S2F02)
    #include "cy8c614alqi_s2f02.h"
#elif defined (CY8C6148LQI_S2F42)
    #include "cy8c6148lqi_s2f42.h"
#elif defined (CY8C6148LQI_S2F02)
    #include "cy8c6148lqi_s2f02.h"
#elif defined (CY8C6245AZI_S3D72)
    #include "cy8c6245azi_s3d72.h"
#elif defined (CY8C6245LQI_S3D72)
    #include "cy8c6245lqi_s3d72.h"
#elif defined (CY8C6245FNI_S3D71)
    #include "cy8c6245fni_s3d71.h"
#elif defined (CY8C6245AZI_S3D62)
    #include "cy8c6245azi_s3d62.h"
#elif defined (CY8C6245LQI_S3D62)
    #include "cy8c6245lqi_s3d62.h"
#elif defined (CY8C6245AZI_S3D42)
    #include "cy8c6245azi_s3d42.h"
#elif defined (CY8C6245LQI_S3D42)
    #include "cy8c6245lqi_s3d42.h"
#elif defined (CYB06445LQI_S3D42)
    #include "cyb06445lqi_s3d42.h"
#elif defined (CY8C6245FNI_S3D41)
    #include "cy8c6245fni_s3d41.h"
#elif defined (CY8C6245AZI_S3D12)
    #include "cy8c6245azi_s3d12.h"
#elif defined (CY8C6245LQI_S3D12)
    #include "cy8c6245lqi_s3d12.h"
#elif defined (CY8C6245FNI_S3D11)
    #include "cy8c6245fni_s3d11.h"
#elif defined (CY8C6245AZI_S3D02)
    #include "cy8c6245azi_s3d02.h"
#elif defined (CY8C6245LQI_S3D02)
    #include "cy8c6245lqi_s3d02.h"
#elif defined (CY8C6145AZI_S3F72)
    #include "cy8c6145azi_s3f72.h"
#elif defined (CY8C6145LQI_S3F72)
    #include "cy8c6145lqi_s3f72.h"
#elif defined (CY8C6145FNI_S3F71)
    #include "cy8c6145fni_s3f71.h"
#elif defined (CY8C6145AZI_S3F62)
    #include "cy8c6145azi_s3f62.h"
#elif defined (CY8C6145LQI_S3F62)
    #include "cy8c6145lqi_s3f62.h"
#elif defined (CY8C6145AZI_S3F42)
    #include "cy8c6145azi_s3f42.h"
#elif defined (CY8C6145LQI_S3F42)
    #include "cy8c6145lqi_s3f42.h"
#elif defined (CY8C6145FNI_S3F41)
    #include "cy8c6145fni_s3f41.h"
#elif defined (CY8C6145AZI_S3F12)
    #include "cy8c6145azi_s3f12.h"
#elif defined (CY8C6145LQI_S3F12)
    #include "cy8c6145lqi_s3f12.h"
#elif defined (CY8C6145FNI_S3F11)
    #include "cy8c6145fni_s3f11.h"
#elif defined (CY8C6145AZI_S3F02)
    #include "cy8c6145azi_s3f02.h"
#elif defined (CY8C6145LQI_S3F02)
    #include "cy8c6145lqi_s3f02.h"
#elif defined (CY8C6244AZI_S4D92)
    #include "cy8c6244azi_s4d92.h"
#elif defined (CY8C6244LQI_S4D92)
    #include "cy8c6244lqi_s4d92.h"
#elif defined (CY8C6244AZI_S4D93)
    #include "cy8c6244azi_s4d93.h"
#elif defined (CY8C6244AZI_S4D82)
    #include "cy8c6244azi_s4d82.h"
#elif defined (CY8C6244LQI_S4D82)
    #include "cy8c6244lqi_s4d82.h"
#elif defined (CY8C6244AZI_S4D83)
    #include "cy8c6244azi_s4d83.h"
#elif defined (CY8C6244AZI_S4D62)
    #include "cy8c6244azi_s4d62.h"
#elif defined (CY8C6244LQI_S4D62)
    #include "cy8c6244lqi_s4d62.h"
#elif defined (CY8C6244AZI_S4D12)
    #include "cy8c6244azi_s4d12.h"
#elif defined (CY8C6244LQI_S4D12)
    #include "cy8c6244lqi_s4d12.h"
#elif defined (CY8C4588AZI_H685)
    #include "cy8c4588azi_h685.h"
#elif defined (CY8C4588AZI_H686)
    #include "cy8c4588azi_h686.h"
#elif defined (CY8C4588AZI_H675)
    #include "cy8c4588azi_h675.h"
#elif defined (CY8C4588AZI_H676)
    #include "cy8c4588azi_h676.h"
#elif defined (CY8C6144AZI_S4F92)
    #include "cy8c6144azi_s4f92.h"
#elif defined (CY8C6144LQI_S4F92)
    #include "cy8c6144lqi_s4f92.h"
#elif defined (CY8C6144AZI_S4F93)
    #include "cy8c6144azi_s4f93.h"
#elif defined (CY8C6144AZI_S4F82)
    #include "cy8c6144azi_s4f82.h"
#elif defined (CY8C6144LQI_S4F82)
    #include "cy8c6144lqi_s4f82.h"
#elif defined (CY8C6144AZI_S4F83)
    #include "cy8c6144azi_s4f83.h"
#elif defined (CY8C6144AZI_S4F62)
    #include "cy8c6144azi_s4f62.h"
#elif defined (CY8C6144LQI_S4F62)
    #include "cy8c6144lqi_s4f62.h"
#elif defined (CY8C6144AZI_S4F12)
    #include "cy8c6144azi_s4f12.h"
#elif defined (CY8C6144LQI_S4F12)
    #include "cy8c6144lqi_s4f12.h"
#elif defined (CY8C6244AZQ_S4D92)
    #include "cy8c6244azq_s4d92.h"
#elif defined (CY8C6244LQQ_S4D92)
    #include "cy8c6244lqq_s4d92.h"
#elif defined (CY8C6244AZQ_S4D93)
    #include "cy8c6244azq_s4d93.h"
#elif defined (CY8C6144AZQ_S4F92)
    #include "cy8c6144azq_s4f92.h"
#elif defined (CY8C6144LQQ_S4F92)
    #include "cy8c6144lqq_s4f92.h"
#elif defined (CY8C6144AZQ_S4F93)
    #include "cy8c6144azq_s4f93.h"
#elif defined (CY8C4588AZQ_H685)
    #include "cy8c4588azq_h685.h"
#elif defined (CY8C4588AZQ_H686)
    #include "cy8c4588azq_h686.h"
#else
    #include "cy_device_common.h"
#endif

#endif /* _CY_DEVICE_HEADERS_H_ */


/* [] END OF FILE */
