/*
 * This is a generated file
 * 
 * Copyright 2021 QuickLogic
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __EFPGA_H_
#define __EFPGA_H_

//---------------------------------//
//
// Module: eFPGA
//
//---------------------------------//

#ifndef __IO
#define __IO volatile
#endif

#ifndef __I
#define __I volatile
#endif

#ifndef __O
#define __O volatile
#endif

#include "stdint.h"

typedef struct {

  // Offset = 0x0000
  union {
    __IO uint32_t tcdm_ctl_p0;
    struct {
      __IO uint32_t  tcdm_addr_p0 : 20;
      __IO uint32_t  tcdm_be_p0 :  4;
      __IO uint32_t             :  7;
      __IO uint32_t  tcdm_wen_p0 :  1;
    } tcdm_ctl_p0_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t tcdm_ctl_p1;
    struct {
      __IO uint32_t  tcdm_addr_p1 : 20;
      __IO uint32_t  tcdm_be_p1 :  4;
      __IO uint32_t             :  7;
      __IO uint32_t  tcdm_wen_p1 :  1;
    } tcdm_ctl_p1_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t tcdm_ctl_p2;
    struct {
      __IO uint32_t  tcdm_addr_p2 : 20;
      __IO uint32_t  tcdm_be_p2 :  4;
      __IO uint32_t             :  7;
      __IO uint32_t  tcdm_wen_p2 :  1;
    } tcdm_ctl_p2_b;
  };

  // Offset = 0x000c
  union {
    __IO uint32_t tcdm_ctl_p3;
    struct {
      __IO uint32_t  tcdm_addr_p3 : 20;
      __IO uint32_t  tcdm_be_p3 :  4;
      __IO uint32_t             :  7;
      __IO uint32_t  tcdm_wen_p3 :  1;
    } tcdm_ctl_p3_b;
  };

  // Offset = 0x0010
  union {
    __IO uint32_t m0_m0_control;
    struct {
      __IO uint32_t  m0_m0_outsel :  6;
      __IO uint32_t             :  6;
      __IO uint32_t  m0_m0_mode :  2;
      __IO uint32_t  m0_m0_osel :  1;
      __IO uint32_t  m0_m0_csel :  1;
      __IO uint32_t  m0_m0_rnd  :  1;
      __IO uint32_t  m0_m0_clr  :  1;
      __IO uint32_t  m0_m0_sat  :  1;
      __IO uint32_t             : 12;
      __IO uint32_t  m0_m0_reset :  1;
    } m0_m0_control_b;
  };

  // Offset = 0x0014
  union {
    __IO uint32_t m0_m1_control;
    struct {
      __IO uint32_t  m0_m1_outsel :  6;
      __IO uint32_t             :  6;
      __IO uint32_t  m0_m1_mode :  2;
      __IO uint32_t  m0_m1_osel :  1;
      __IO uint32_t  m0_m1_csel :  1;
      __IO uint32_t  m0_m1_rnd  :  1;
      __IO uint32_t  m0_m1_clr  :  1;
      __IO uint32_t  m0_m1_sat  :  1;
      __IO uint32_t             : 12;
      __IO uint32_t  m0_m1_reset :  1;
    } m0_m1_control_b;
  };

  // Offset = 0x0018
  union {
    __IO uint32_t m1_m0_control;
    struct {
      __IO uint32_t  m1_m0_outsel :  6;
      __IO uint32_t             :  6;
      __IO uint32_t  m1_m0_mode :  2;
      __IO uint32_t  m1_m0_osel :  1;
      __IO uint32_t  m1_m0_csel :  1;
      __IO uint32_t  m1_m0_rnd  :  1;
      __IO uint32_t  m1_m0_clr  :  1;
      __IO uint32_t  m1_m1_sat  :  1;
      __IO uint32_t             : 12;
      __IO uint32_t  m1_m0_reset :  1;
    } m1_m0_control_b;
  };

  // Offset = 0x001c
  union {
    __IO uint32_t m1_m1_control;
    struct {
      __IO uint32_t  m1_m1_outsel :  6;
      __IO uint32_t             :  6;
      __IO uint32_t  m1_m1_mode :  2;
      __IO uint32_t  m1_m1_osel :  1;
      __IO uint32_t  m1_m1_csel :  1;
      __IO uint32_t  m1_m1_rnd  :  1;
      __IO uint32_t  m1_m1_clr  :  1;
      __IO uint32_t  m1_m1_sat  :  1;
      __IO uint32_t             : 12;
      __IO uint32_t  m1_m1_reset :  1;
    } m1_m1_control_b;
  };

  // Offset = 0x0020
  union {
    __IO uint32_t m0_ram_control;
    struct {
      __IO uint32_t  m0_oper0_rmode :  2;
      __IO uint32_t  m0_oper0_wmode :  2;
      __IO uint32_t  m0_oper1_rmode :  2;
      __IO uint32_t  m0_oper1_wmode :  2;
      __IO uint32_t  m0_coef_rmode :  2;
      __IO uint32_t  m0_coef_wmode :  2;
      __IO uint32_t  m0_oper0_wdsel :  1;
      __IO uint32_t  m0_oper1_wdsel :  1;
      __IO uint32_t  m0_coef_wdsel :  1;
    } m0_ram_control_b;
  };

  // Offset = 0x0024
  union {
    __IO uint32_t m1_ram_control;
    struct {
      __IO uint32_t  m1_oper0_rmode :  2;
      __IO uint32_t  m1_oper0_wmode :  2;
      __IO uint32_t  m1_oper1_rmode :  2;
      __IO uint32_t  m1_oper1_wmode :  2;
      __IO uint32_t  m1_coef_rmode :  2;
      __IO uint32_t  m1_coef_wmode :  2;
      __IO uint32_t  m1_oper0_wdsel :  1;
      __IO uint32_t  m1_oper1_wdsel :  1;
      __IO uint32_t  m1_coef_wdsel :  1;
    } m1_ram_control_b;
  };
  __I uint32_t    unused0[2];

  // Offset = 0x0030
  union {
    __IO uint32_t m0_m0_clken;
    struct {
      __IO uint32_t  m0_m0_clken :  1;
    } m0_m0_clken_b;
  };

  // Offset = 0x0034
  union {
    __IO uint32_t m0_m1_clken;
    struct {
      __IO uint32_t  m0_m1_clken :  1;
    } m0_m1_clken_b;
  };

  // Offset = 0x0038
  union {
    __IO uint32_t m1_m0_clken;
    struct {
      __IO uint32_t  m1_m0_clken :  1;
    } m1_m0_clken_b;
  };

  // Offset = 0x003c
  union {
    __IO uint32_t m1_m1_clken;
    struct {
      __IO uint32_t  m1_m1_clken :  1;
    } m1_m1_clken_b;
  };

  // Offset = 0x0040
  union {
    __IO uint32_t fpgaio_out31_00;
    struct {
      __IO uint32_t  fpgaio_o_0 :  1;
      __IO uint32_t  fpgaio_o_1 :  1;
      __IO uint32_t  fpgaio_o_2 :  1;
      __IO uint32_t  fpgaio_o_3 :  1;
      __IO uint32_t  fpgaio_o_4 :  1;
      __IO uint32_t  fpgaio_o_5 :  1;
      __IO uint32_t  fpgaio_o_6 :  1;
      __IO uint32_t  fpgaio_o_7 :  1;
      __IO uint32_t  fpgaio_o_8 :  1;
      __IO uint32_t  fpgaio_o_9 :  1;
      __IO uint32_t  fpgaio_o_10 :  1;
      __IO uint32_t  fpgaio_o_11 :  1;
      __IO uint32_t  fpgaio_o_12 :  1;
      __IO uint32_t  fpgaio_o_13 :  1;
      __IO uint32_t  fpgaio_o_14 :  1;
      __IO uint32_t  fpgaio_o_15 :  1;
      __IO uint32_t  fpgaio_o_16 :  1;
      __IO uint32_t  fpgaio_o_17 :  1;
      __IO uint32_t  fpgaio_o_18 :  1;
      __IO uint32_t  fpgaio_o_19 :  1;
      __IO uint32_t  fpgaio_o_20 :  1;
      __IO uint32_t  fpgaio_o_21 :  1;
      __IO uint32_t  fpgaio_o_22 :  1;
      __IO uint32_t  fpgaio_o_23 :  1;
      __IO uint32_t  fpgaio_o_24 :  1;
      __IO uint32_t  fpgaio_o_25 :  1;
      __IO uint32_t  fpgaio_o_26 :  1;
      __IO uint32_t  fpgaio_o_27 :  1;
      __IO uint32_t  fpgaio_o_28 :  1;
      __IO uint32_t  fpgaio_o_29 :  1;
      __IO uint32_t  fpgaio_o_30 :  1;
      __IO uint32_t  fpgaio_o_31 :  1;
    } fpgaio_out31_00_b;
  };

  // Offset = 0x0044
  union {
    __IO uint32_t fpgaio_out63_32;
    struct {
      __IO uint32_t  fpgaio_o_32 :  1;
      __IO uint32_t  fpgaio_o_33 :  1;
      __IO uint32_t  fpgaio_o_34 :  1;
      __IO uint32_t  fpgaio_o_35 :  1;
      __IO uint32_t  fpgaio_o_36 :  1;
      __IO uint32_t  fpgaio_o_37 :  1;
      __IO uint32_t  fpgaio_o_38 :  1;
      __IO uint32_t  fpgaio_o_39 :  1;
      __IO uint32_t  fpgaio_o_40 :  1;
      __IO uint32_t  fpgaio_o_41 :  1;
      __IO uint32_t  fpgaio_o_42 :  1;
      __IO uint32_t  fpgaio_o_43 :  1;
      __IO uint32_t  fpgaio_o_44 :  1;
      __IO uint32_t  fpgaio_o_45 :  1;
      __IO uint32_t  fpgaio_o_46 :  1;
      __IO uint32_t  fpgaio_o_47 :  1;
      __IO uint32_t  fpgaio_o_48 :  1;
      __IO uint32_t  fpgaio_o_49 :  1;
      __IO uint32_t  fpgaio_o_50 :  1;
      __IO uint32_t  fpgaio_o_51 :  1;
      __IO uint32_t  fpgaio_o_52 :  1;
      __IO uint32_t  fpgaio_o_53 :  1;
      __IO uint32_t  fpgaio_o_54 :  1;
      __IO uint32_t  fpgaio_o_55 :  1;
      __IO uint32_t  fpgaio_o_56 :  1;
      __IO uint32_t  fpgaio_o_57 :  1;
      __IO uint32_t  fpgaio_o_58 :  1;
      __IO uint32_t  fpgaio_o_59 :  1;
      __IO uint32_t  fpgaio_o_60 :  1;
      __IO uint32_t  fpgaio_o_61 :  1;
      __IO uint32_t  fpgaio_o_62 :  1;
      __IO uint32_t  fpgaio_o_63 :  1;
    } fpgaio_out63_32_b;
  };

  // Offset = 0x0048
  union {
    __IO uint32_t fpgaio_out79_64;
    struct {
      __IO uint32_t  fpgaio_o_64 :  1;
      __IO uint32_t  fpgaio_o_65 :  1;
      __IO uint32_t  fpgaio_o_66 :  1;
      __IO uint32_t  fpgaio_o_67 :  1;
      __IO uint32_t  fpgaio_o_68 :  1;
      __IO uint32_t  fpgaio_o_69 :  1;
      __IO uint32_t  fpgaio_o_70 :  1;
      __IO uint32_t  fpgaio_o_71 :  1;
      __IO uint32_t  fpgaio_o_72 :  1;
      __IO uint32_t  fpgaio_o_73 :  1;
      __IO uint32_t  fpgaio_o_74 :  1;
      __IO uint32_t  fpgaio_o_75 :  1;
      __IO uint32_t  fpgaio_o_76 :  1;
      __IO uint32_t  fpgaio_o_77 :  1;
      __IO uint32_t  fpgaio_o_78 :  1;
      __IO uint32_t  fpgaio_o_79 :  1;
    } fpgaio_out79_64_b;
  };
  __I uint32_t    unused1[1];

  // Offset = 0x0050
  union {
    __IO uint32_t fpgaio_oe31_00;
    struct {
      __IO uint32_t  fpgaio_oe_0 :  1;
      __IO uint32_t  fpgaio_oe_1 :  1;
      __IO uint32_t  fpgaio_oe_2 :  1;
      __IO uint32_t  fpgaio_oe_3 :  1;
      __IO uint32_t  fpgaio_oe_4 :  1;
      __IO uint32_t  fpgaio_oe_5 :  1;
      __IO uint32_t  fpgaio_oe_6 :  1;
      __IO uint32_t  fpgaio_oe_7 :  1;
      __IO uint32_t  fpgaio_oe_8 :  1;
      __IO uint32_t  fpgaio_oe_9 :  1;
      __IO uint32_t  fpgaio_oe_10 :  1;
      __IO uint32_t  fpgaio_oe_11 :  1;
      __IO uint32_t  fpgaio_oe_12 :  1;
      __IO uint32_t  fpgaio_oe_13 :  1;
      __IO uint32_t  fpgaio_oe_14 :  1;
      __IO uint32_t  fpgaio_oe_15 :  1;
      __IO uint32_t  fpgaio_oe_16 :  1;
      __IO uint32_t  fpgaio_oe_17 :  1;
      __IO uint32_t  fpgaio_oe_18 :  1;
      __IO uint32_t  fpgaio_oe_19 :  1;
      __IO uint32_t  fpgaio_oe_20 :  1;
      __IO uint32_t  fpgaio_oe_21 :  1;
      __IO uint32_t  fpgaio_oe_22 :  1;
      __IO uint32_t  fpgaio_oe_23 :  1;
      __IO uint32_t  fpgaio_oe_24 :  1;
      __IO uint32_t  fpgaio_oe_25 :  1;
      __IO uint32_t  fpgaio_oe_26 :  1;
      __IO uint32_t  fpgaio_oe_27 :  1;
      __IO uint32_t  fpgaio_oe_28 :  1;
      __IO uint32_t  fpgaio_oe_29 :  1;
      __IO uint32_t  fpgaio_oe_30 :  1;
      __IO uint32_t  fpgaio_oe_31 :  1;
    } fpgaio_oe31_00_b;
  };

  // Offset = 0x0054
  union {
    __IO uint32_t fpgaio_oe63_32;
    struct {
      __IO uint32_t  fpgaio_oe_32 :  1;
      __IO uint32_t  fpgaio_oe_33 :  1;
      __IO uint32_t  fpgaio_oe_34 :  1;
      __IO uint32_t  fpgaio_oe_35 :  1;
      __IO uint32_t  fpgaio_oe_36 :  1;
      __IO uint32_t  fpgaio_oe_37 :  1;
      __IO uint32_t  fpgaio_oe_38 :  1;
      __IO uint32_t  fpgaio_oe_39 :  1;
      __IO uint32_t  fpgaio_oe_40 :  1;
      __IO uint32_t  fpgaio_oe_41 :  1;
      __IO uint32_t  fpgaio_oe_42 :  1;
      __IO uint32_t  fpgaio_oe_43 :  1;
      __IO uint32_t  fpgaio_oe_44 :  1;
      __IO uint32_t  fpgaio_oe_45 :  1;
      __IO uint32_t  fpgaio_oe_46 :  1;
      __IO uint32_t  fpgaio_oe_47 :  1;
      __IO uint32_t  fpgaio_oe_48 :  1;
      __IO uint32_t  fpgaio_oe_49 :  1;
      __IO uint32_t  fpgaio_oe_50 :  1;
      __IO uint32_t  fpgaio_oe_51 :  1;
      __IO uint32_t  fpgaio_oe_52 :  1;
      __IO uint32_t  fpgaio_oe_53 :  1;
      __IO uint32_t  fpgaio_oe_54 :  1;
      __IO uint32_t  fpgaio_oe_55 :  1;
      __IO uint32_t  fpgaio_oe_56 :  1;
      __IO uint32_t  fpgaio_oe_57 :  1;
      __IO uint32_t  fpgaio_oe_58 :  1;
      __IO uint32_t  fpgaio_oe_59 :  1;
      __IO uint32_t  fpgaio_oe_60 :  1;
      __IO uint32_t  fpgaio_oe_61 :  1;
      __IO uint32_t  fpgaio_oe_62 :  1;
      __IO uint32_t  fpgaio_oe_63 :  1;
    } fpgaio_oe63_32_b;
  };

  // Offset = 0x0058
  union {
    __IO uint32_t fpgaio_oe79_64;
    struct {
      __IO uint32_t  fpgaio_oe_64 :  1;
      __IO uint32_t  fpgaio_oe_65 :  1;
      __IO uint32_t  fpgaio_oe_66 :  1;
      __IO uint32_t  fpgaio_oe_67 :  1;
      __IO uint32_t  fpgaio_oe_68 :  1;
      __IO uint32_t  fpgaio_oe_69 :  1;
      __IO uint32_t  fpgaio_oe_70 :  1;
      __IO uint32_t  fpgaio_oe_71 :  1;
      __IO uint32_t  fpgaio_oe_72 :  1;
      __IO uint32_t  fpgaio_oe_73 :  1;
      __IO uint32_t  fpgaio_oe_74 :  1;
      __IO uint32_t  fpgaio_oe_75 :  1;
      __IO uint32_t  fpgaio_oe_76 :  1;
      __IO uint32_t  fpgaio_oe_77 :  1;
      __IO uint32_t  fpgaio_oe_78 :  1;
      __IO uint32_t  fpgaio_oe_79 :  1;
    } fpgaio_oe79_64_b;
  };
  __I uint32_t    unused2[1];

  // Offset = 0x0060
  union {
    __IO uint32_t fpgaio_in31_00;
    struct {
      __IO uint32_t  fpgaio_i_0 :  1;
      __IO uint32_t  fpgaio_i_1 :  1;
      __IO uint32_t  fpgaio_i_2 :  1;
      __IO uint32_t  fpgaio_i_3 :  1;
      __IO uint32_t  fpgaio_i_4 :  1;
      __IO uint32_t  fpgaio_i_5 :  1;
      __IO uint32_t  fpgaio_i_6 :  1;
      __IO uint32_t  fpgaio_i_7 :  1;
      __IO uint32_t  fpgaio_i_8 :  1;
      __IO uint32_t  fpgaio_i_9 :  1;
      __IO uint32_t  fpgaio_i_10 :  1;
      __IO uint32_t  fpgaio_i_11 :  1;
      __IO uint32_t  fpgaio_i_12 :  1;
      __IO uint32_t  fpgaio_i_13 :  1;
      __IO uint32_t  fpgaio_i_14 :  1;
      __IO uint32_t  fpgaio_i_15 :  1;
      __IO uint32_t  fpgaio_i_16 :  1;
      __IO uint32_t  fpgaio_i_17 :  1;
      __IO uint32_t  fpgaio_i_18 :  1;
      __IO uint32_t  fpgaio_i_19 :  1;
      __IO uint32_t  fpgaio_i_20 :  1;
      __IO uint32_t  fpgaio_i_21 :  1;
      __IO uint32_t  fpgaio_i_22 :  1;
      __IO uint32_t  fpgaio_i_23 :  1;
      __IO uint32_t  fpgaio_i_24 :  1;
      __IO uint32_t  fpgaio_i_25 :  1;
      __IO uint32_t  fpgaio_i_26 :  1;
      __IO uint32_t  fpgaio_i_27 :  1;
      __IO uint32_t  fpgaio_i_28 :  1;
      __IO uint32_t  fpgaio_i_29 :  1;
      __IO uint32_t  fpgaio_i_30 :  1;
      __IO uint32_t  fpgaio_i_31 :  1;
    } fpgaio_in31_00_b;
  };

  // Offset = 0x0064
  union {
    __IO uint32_t fpgaio_in63_32;
    struct {
      __IO uint32_t  fpgaio_i_32 :  1;
      __IO uint32_t  fpgaio_i_33 :  1;
      __IO uint32_t  fpgaio_i_34 :  1;
      __IO uint32_t  fpgaio_i_35 :  1;
      __IO uint32_t  fpgaio_i_36 :  1;
      __IO uint32_t  fpgaio_i_37 :  1;
      __IO uint32_t  fpgaio_i_38 :  1;
      __IO uint32_t  fpgaio_i_39 :  1;
      __IO uint32_t  fpgaio_i_40 :  1;
      __IO uint32_t  fpgaio_i_41 :  1;
      __IO uint32_t  fpgaio_i_42 :  1;
      __IO uint32_t  fpgaio_i_43 :  1;
      __IO uint32_t  fpgaio_i_44 :  1;
      __IO uint32_t  fpgaio_i_45 :  1;
      __IO uint32_t  fpgaio_i_46 :  1;
      __IO uint32_t  fpgaio_i_47 :  1;
      __IO uint32_t  fpgaio_i_48 :  1;
      __IO uint32_t  fpgaio_i_49 :  1;
      __IO uint32_t  fpgaio_i_50 :  1;
      __IO uint32_t  fpgaio_i_51 :  1;
      __IO uint32_t  fpgaio_i_52 :  1;
      __IO uint32_t  fpgaio_i_53 :  1;
      __IO uint32_t  fpgaio_i_54 :  1;
      __IO uint32_t  fpgaio_i_55 :  1;
      __IO uint32_t  fpgaio_i_56 :  1;
      __IO uint32_t  fpgaio_i_57 :  1;
      __IO uint32_t  fpgaio_i_58 :  1;
      __IO uint32_t  fpgaio_i_59 :  1;
      __IO uint32_t  fpgaio_i_60 :  1;
      __IO uint32_t  fpgaio_i_61 :  1;
      __IO uint32_t  fpgaio_i_62 :  1;
      __IO uint32_t  fpgaio_i_63 :  1;
    } fpgaio_in63_32_b;
  };

  // Offset = 0x0068
  union {
    __IO uint32_t fpgaio_in79_64;
    struct {
      __IO uint32_t  fpgaio_i_64 :  1;
      __IO uint32_t  fpgaio_i_65 :  1;
      __IO uint32_t  fpgaio_i_66 :  1;
      __IO uint32_t  fpgaio_i_67 :  1;
      __IO uint32_t  fpgaio_i_68 :  1;
      __IO uint32_t  fpgaio_i_69 :  1;
      __IO uint32_t  fpgaio_i_70 :  1;
      __IO uint32_t  fpgaio_i_71 :  1;
      __IO uint32_t  fpgaio_i_72 :  1;
      __IO uint32_t  fpgaio_i_73 :  1;
      __IO uint32_t  fpgaio_i_74 :  1;
      __IO uint32_t  fpgaio_i_75 :  1;
      __IO uint32_t  fpgaio_i_76 :  1;
      __IO uint32_t  fpgaio_i_77 :  1;
      __IO uint32_t  fpgaio_i_78 :  1;
      __IO uint32_t  fpgaio_i_79 :  1;
    } fpgaio_in79_64_b;
  };

  // Offset = 0x006c
  union {
    __IO uint32_t fpga_event15_00;
    struct {
      __IO uint32_t  event_0    :  1;
      __IO uint32_t  event_1    :  1;
      __IO uint32_t  event_2    :  1;
      __IO uint32_t  event_3    :  1;
      __IO uint32_t  event_4    :  1;
      __IO uint32_t  event_5    :  1;
      __IO uint32_t  event_6    :  1;
      __IO uint32_t  event_7    :  1;
      __IO uint32_t  event_8    :  1;
      __IO uint32_t  event_9    :  1;
      __IO uint32_t  event_10   :  1;
      __IO uint32_t  event_11   :  1;
      __IO uint32_t  event_12   :  1;
      __IO uint32_t  event_13   :  1;
      __IO uint32_t  event_14   :  1;
      __IO uint32_t  event_15   :  1;
    } fpga_event15_00_b;
  };
  __I uint32_t    unused3[4];

  // Offset = 0x0080
  union {
    __IO uint32_t tcdm_run_p0;
    struct {
      __IO uint32_t  tcdm_wdata_p0 : 32;
    } tcdm_run_p0_b;
  };

  // Offset = 0x0084
  union {
    __IO uint32_t tcdm_run_p1;
    struct {
      __IO uint32_t  tcdm_wdata_p0 : 32;
    } tcdm_run_p1_b;
  };

  // Offset = 0x0088
  union {
    __IO uint32_t tcdm_run_p2;
    struct {
      __IO uint32_t  tcdm_wdata_p0 : 32;
    } tcdm_run_p2_b;
  };

  // Offset = 0x008c
  union {
    __IO uint32_t tcdm_run_p3;
    struct {
      __IO uint32_t  tcdm_wdata_p0 : 32;
    } tcdm_run_p3_b;
  };

  // Offset = 0x0090
  union {
    __IO uint32_t m0_m0_odata;
    struct {
      __IO uint32_t  odata      : 32;
    } m0_m0_odata_b;
  };

  // Offset = 0x0094
  union {
    __IO uint32_t m0_m1_odata;
    struct {
      __IO uint32_t  odata      : 32;
    } m0_m1_odata_b;
  };

  // Offset = 0x0098
  union {
    __IO uint32_t m0_m0_cdata;
    struct {
      __IO uint32_t  cdata      : 32;
    } m0_m0_cdata_b;
  };

  // Offset = 0x009c
  union {
    __IO uint32_t m0_m1_cdata;
    struct {
      __IO uint32_t  cdata      : 32;
    } m0_m1_cdata_b;
  };

  // Offset = 0x00a0
  union {
    __IO uint32_t m1_m0_odata;
    struct {
      __IO uint32_t  odata      : 32;
    } m1_m0_odata_b;
  };

  // Offset = 0x00a4
  union {
    __IO uint32_t m1_m1_odata;
    struct {
      __IO uint32_t  odata      : 32;
    } m1_m1_odata_b;
  };

  // Offset = 0x00a8
  union {
    __IO uint32_t m1_m0_cdata;
    struct {
      __IO uint32_t  cdata      : 32;
    } m1_m0_cdata_b;
  };

  // Offset = 0x00ac
  union {
    __IO uint32_t m1_m1_cdata;
    struct {
      __IO uint32_t  cdata      : 32;
    } m1_m1_cdata_b;
  };
  __I uint32_t    unused4[20];

  // Offset = 0x0100
  union {
    __IO uint32_t m0_m0_multout;
    struct {
      __IO uint32_t  multout    : 32;
    } m0_m0_multout_b;
  };

  // Offset = 0x0104
  union {
    __IO uint32_t m0_m1_multout;
    struct {
      __IO uint32_t  multout    : 32;
    } m0_m1_multout_b;
  };

  // Offset = 0x0108
  union {
    __IO uint32_t m1_m0_multout;
    struct {
      __IO uint32_t  multout    : 32;
    } m1_m0_multout_b;
  };

  // Offset = 0x010c
  union {
    __IO uint32_t m1_m01multout;
    struct {
      __IO uint32_t  multout    : 32;
    } m1_m01multout_b;
  };
  __I uint32_t    unused5[956];

  // Offset = 0x1000
  union {
    __IO uint32_t m0_oper0[0x400];
  };
  __I uint32_t    unused6[1023];

  // Offset = 0x2000
  union {
    __IO uint32_t m0_oper1[0x400];
  };
  __I uint32_t    unused7[1023];

  // Offset = 0x3000
  union {
    __IO uint32_t m0_coef[0x400];
  };
  __I uint32_t    unused8[1023];

  // Offset = 0x4000
  union {
    __IO uint32_t m1_oper0[0x400];
  };
  __I uint32_t    unused9[1023];

  // Offset = 0x5000
  union {
    __IO uint32_t m1_oper1[0x400];
  };
  __I uint32_t    unused10[1023];

  // Offset = 0x6000
  union {
    __IO uint32_t m1_coef[0x400];
  };
} Efpga_t;


#define REG_TCDM_CTL_P0                0x00
#define   REG_TCDM_CTL_P0_tcdm_wen_p0_LSB          31
#define   REG_TCDM_CTL_P0_tcdm_wen_p0_MASK         0x1
#define   REG_TCDM_CTL_P0_tcdm_be_p0_LSB           20
#define   REG_TCDM_CTL_P0_tcdm_be_p0_MASK          0xf
#define   REG_TCDM_CTL_P0_tcdm_addr_p0_LSB         0
#define   REG_TCDM_CTL_P0_tcdm_addr_p0_MASK        0xfffff
#define REG_TCDM_CTL_P1                0x04
#define   REG_TCDM_CTL_P1_tcdm_wen_p1_LSB          31
#define   REG_TCDM_CTL_P1_tcdm_wen_p1_MASK         0x1
#define   REG_TCDM_CTL_P1_tcdm_be_p1_LSB           20
#define   REG_TCDM_CTL_P1_tcdm_be_p1_MASK          0xf
#define   REG_TCDM_CTL_P1_tcdm_addr_p1_LSB         0
#define   REG_TCDM_CTL_P1_tcdm_addr_p1_MASK        0xfffff
#define REG_TCDM_CTL_P2                0x08
#define   REG_TCDM_CTL_P2_tcdm_wen_p2_LSB          31
#define   REG_TCDM_CTL_P2_tcdm_wen_p2_MASK         0x1
#define   REG_TCDM_CTL_P2_tcdm_be_p2_LSB           20
#define   REG_TCDM_CTL_P2_tcdm_be_p2_MASK          0xf
#define   REG_TCDM_CTL_P2_tcdm_addr_p2_LSB         0
#define   REG_TCDM_CTL_P2_tcdm_addr_p2_MASK        0xfffff
#define REG_TCDM_CTL_P3                0x0C
#define   REG_TCDM_CTL_P3_tcdm_wen_p3_LSB          31
#define   REG_TCDM_CTL_P3_tcdm_wen_p3_MASK         0x1
#define   REG_TCDM_CTL_P3_tcdm_be_p3_LSB           20
#define   REG_TCDM_CTL_P3_tcdm_be_p3_MASK          0xf
#define   REG_TCDM_CTL_P3_tcdm_addr_p3_LSB         0
#define   REG_TCDM_CTL_P3_tcdm_addr_p3_MASK        0xfffff
#define REG_M0_M0_CONTROL              0x10
#define   REG_M0_M0_CONTROL_m0_m0_reset_LSB        31
#define   REG_M0_M0_CONTROL_m0_m0_reset_MASK       0x1
#define   REG_M0_M0_CONTROL_m0_m0_sat_LSB          18
#define   REG_M0_M0_CONTROL_m0_m0_sat_MASK         0x1
#define   REG_M0_M0_CONTROL_m0_m0_clr_LSB          17
#define   REG_M0_M0_CONTROL_m0_m0_clr_MASK         0x1
#define   REG_M0_M0_CONTROL_m0_m0_rnd_LSB          16
#define   REG_M0_M0_CONTROL_m0_m0_rnd_MASK         0x1
#define   REG_M0_M0_CONTROL_m0_m0_csel_LSB         15
#define   REG_M0_M0_CONTROL_m0_m0_csel_MASK        0x1
#define   REG_M0_M0_CONTROL_m0_m0_osel_LSB         14
#define   REG_M0_M0_CONTROL_m0_m0_osel_MASK        0x1
#define   REG_M0_M0_CONTROL_m0_m0_mode_LSB         12
#define   REG_M0_M0_CONTROL_m0_m0_mode_MASK        0x3
#define   REG_M0_M0_CONTROL_m0_m0_outsel_LSB       0
#define   REG_M0_M0_CONTROL_m0_m0_outsel_MASK      0x3f
#define REG_M0_M1_CONTROL              0x14
#define   REG_M0_M1_CONTROL_m0_m1_reset_LSB        31
#define   REG_M0_M1_CONTROL_m0_m1_reset_MASK       0x1
#define   REG_M0_M1_CONTROL_m0_m1_sat_LSB          18
#define   REG_M0_M1_CONTROL_m0_m1_sat_MASK         0x1
#define   REG_M0_M1_CONTROL_m0_m1_clr_LSB          17
#define   REG_M0_M1_CONTROL_m0_m1_clr_MASK         0x1
#define   REG_M0_M1_CONTROL_m0_m1_rnd_LSB          16
#define   REG_M0_M1_CONTROL_m0_m1_rnd_MASK         0x1
#define   REG_M0_M1_CONTROL_m0_m1_csel_LSB         15
#define   REG_M0_M1_CONTROL_m0_m1_csel_MASK        0x1
#define   REG_M0_M1_CONTROL_m0_m1_osel_LSB         14
#define   REG_M0_M1_CONTROL_m0_m1_osel_MASK        0x1
#define   REG_M0_M1_CONTROL_m0_m1_mode_LSB         12
#define   REG_M0_M1_CONTROL_m0_m1_mode_MASK        0x3
#define   REG_M0_M1_CONTROL_m0_m1_outsel_LSB       0
#define   REG_M0_M1_CONTROL_m0_m1_outsel_MASK      0x3f
#define REG_M1_M0_CONTROL              0x18
#define   REG_M1_M0_CONTROL_m1_m0_reset_LSB        31
#define   REG_M1_M0_CONTROL_m1_m0_reset_MASK       0x1
#define   REG_M1_M0_CONTROL_m1_m1_sat_LSB          18
#define   REG_M1_M0_CONTROL_m1_m1_sat_MASK         0x1
#define   REG_M1_M0_CONTROL_m1_m0_clr_LSB          17
#define   REG_M1_M0_CONTROL_m1_m0_clr_MASK         0x1
#define   REG_M1_M0_CONTROL_m1_m0_rnd_LSB          16
#define   REG_M1_M0_CONTROL_m1_m0_rnd_MASK         0x1
#define   REG_M1_M0_CONTROL_m1_m0_csel_LSB         15
#define   REG_M1_M0_CONTROL_m1_m0_csel_MASK        0x1
#define   REG_M1_M0_CONTROL_m1_m0_osel_LSB         14
#define   REG_M1_M0_CONTROL_m1_m0_osel_MASK        0x1
#define   REG_M1_M0_CONTROL_m1_m0_mode_LSB         12
#define   REG_M1_M0_CONTROL_m1_m0_mode_MASK        0x3
#define   REG_M1_M0_CONTROL_m1_m0_outsel_LSB       0
#define   REG_M1_M0_CONTROL_m1_m0_outsel_MASK      0x3f
#define REG_M1_M1_CONTROL              0x1C
#define   REG_M1_M1_CONTROL_m1_m1_reset_LSB        31
#define   REG_M1_M1_CONTROL_m1_m1_reset_MASK       0x1
#define   REG_M1_M1_CONTROL_m1_m1_sat_LSB          18
#define   REG_M1_M1_CONTROL_m1_m1_sat_MASK         0x1
#define   REG_M1_M1_CONTROL_m1_m1_clr_LSB          17
#define   REG_M1_M1_CONTROL_m1_m1_clr_MASK         0x1
#define   REG_M1_M1_CONTROL_m1_m1_rnd_LSB          16
#define   REG_M1_M1_CONTROL_m1_m1_rnd_MASK         0x1
#define   REG_M1_M1_CONTROL_m1_m1_csel_LSB         15
#define   REG_M1_M1_CONTROL_m1_m1_csel_MASK        0x1
#define   REG_M1_M1_CONTROL_m1_m1_osel_LSB         14
#define   REG_M1_M1_CONTROL_m1_m1_osel_MASK        0x1
#define   REG_M1_M1_CONTROL_m1_m1_mode_LSB         12
#define   REG_M1_M1_CONTROL_m1_m1_mode_MASK        0x3
#define   REG_M1_M1_CONTROL_m1_m1_outsel_LSB       0
#define   REG_M1_M1_CONTROL_m1_m1_outsel_MASK      0x3f
#define REG_M0_RAM_CONTROL             0x20
#define   REG_M0_RAM_CONTROL_m0_coef_wdsel_LSB     14
#define   REG_M0_RAM_CONTROL_m0_coef_wdsel_MASK    0x1
#define   REG_M0_RAM_CONTROL_m0_oper1_wdsel_LSB    13
#define   REG_M0_RAM_CONTROL_m0_oper1_wdsel_MASK   0x1
#define   REG_M0_RAM_CONTROL_m0_oper0_wdsel_LSB    12
#define   REG_M0_RAM_CONTROL_m0_oper0_wdsel_MASK   0x1
#define   REG_M0_RAM_CONTROL_m0_coef_wmode_LSB     10
#define   REG_M0_RAM_CONTROL_m0_coef_wmode_MASK    0x3
#define   REG_M0_RAM_CONTROL_m0_coef_rmode_LSB     8
#define   REG_M0_RAM_CONTROL_m0_coef_rmode_MASK    0x3
#define   REG_M0_RAM_CONTROL_m0_oper1_wmode_LSB    6
#define   REG_M0_RAM_CONTROL_m0_oper1_wmode_MASK   0x3
#define   REG_M0_RAM_CONTROL_m0_oper1_rmode_LSB    4
#define   REG_M0_RAM_CONTROL_m0_oper1_rmode_MASK   0x3
#define   REG_M0_RAM_CONTROL_m0_oper0_wmode_LSB    2
#define   REG_M0_RAM_CONTROL_m0_oper0_wmode_MASK   0x3
#define   REG_M0_RAM_CONTROL_m0_oper0_rmode_LSB    0
#define   REG_M0_RAM_CONTROL_m0_oper0_rmode_MASK   0x3
#define REG_M1_RAM_CONTROL             0x24
#define   REG_M1_RAM_CONTROL_m1_coef_wdsel_LSB     14
#define   REG_M1_RAM_CONTROL_m1_coef_wdsel_MASK    0x1
#define   REG_M1_RAM_CONTROL_m1_oper1_wdsel_LSB    13
#define   REG_M1_RAM_CONTROL_m1_oper1_wdsel_MASK   0x1
#define   REG_M1_RAM_CONTROL_m1_oper0_wdsel_LSB    12
#define   REG_M1_RAM_CONTROL_m1_oper0_wdsel_MASK   0x1
#define   REG_M1_RAM_CONTROL_m1_coef_wmode_LSB     10
#define   REG_M1_RAM_CONTROL_m1_coef_wmode_MASK    0x3
#define   REG_M1_RAM_CONTROL_m1_coef_rmode_LSB     8
#define   REG_M1_RAM_CONTROL_m1_coef_rmode_MASK    0x3
#define   REG_M1_RAM_CONTROL_m1_oper1_wmode_LSB    6
#define   REG_M1_RAM_CONTROL_m1_oper1_wmode_MASK   0x3
#define   REG_M1_RAM_CONTROL_m1_oper1_rmode_LSB    4
#define   REG_M1_RAM_CONTROL_m1_oper1_rmode_MASK   0x3
#define   REG_M1_RAM_CONTROL_m1_oper0_wmode_LSB    2
#define   REG_M1_RAM_CONTROL_m1_oper0_wmode_MASK   0x3
#define   REG_M1_RAM_CONTROL_m1_oper0_rmode_LSB    0
#define   REG_M1_RAM_CONTROL_m1_oper0_rmode_MASK   0x3
#define REG_M0_M0_CLKEN                0x30
#define   REG_M0_M0_CLKEN_m0_m0_clken_LSB          0
#define   REG_M0_M0_CLKEN_m0_m0_clken_MASK         0x1
#define REG_M0_M1_CLKEN                0x34
#define   REG_M0_M1_CLKEN_m0_m1_clken_LSB          0
#define   REG_M0_M1_CLKEN_m0_m1_clken_MASK         0x1
#define REG_M1_M0_CLKEN                0x38
#define   REG_M1_M0_CLKEN_m1_m0_clken_LSB          0
#define   REG_M1_M0_CLKEN_m1_m0_clken_MASK         0x1
#define REG_M1_M1_CLKEN                0x3C
#define   REG_M1_M1_CLKEN_m1_m1_clken_LSB          0
#define   REG_M1_M1_CLKEN_m1_m1_clken_MASK         0x1
#define REG_FPGAIO_OUT31_00            0x40
#define   REG_FPGAIO_OUT31_00_fpgaio_o_31_LSB      31
#define   REG_FPGAIO_OUT31_00_fpgaio_o_31_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_30_LSB      30
#define   REG_FPGAIO_OUT31_00_fpgaio_o_30_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_29_LSB      29
#define   REG_FPGAIO_OUT31_00_fpgaio_o_29_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_28_LSB      28
#define   REG_FPGAIO_OUT31_00_fpgaio_o_28_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_27_LSB      27
#define   REG_FPGAIO_OUT31_00_fpgaio_o_27_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_26_LSB      26
#define   REG_FPGAIO_OUT31_00_fpgaio_o_26_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_25_LSB      25
#define   REG_FPGAIO_OUT31_00_fpgaio_o_25_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_24_LSB      24
#define   REG_FPGAIO_OUT31_00_fpgaio_o_24_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_23_LSB      23
#define   REG_FPGAIO_OUT31_00_fpgaio_o_23_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_22_LSB      22
#define   REG_FPGAIO_OUT31_00_fpgaio_o_22_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_21_LSB      21
#define   REG_FPGAIO_OUT31_00_fpgaio_o_21_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_20_LSB      20
#define   REG_FPGAIO_OUT31_00_fpgaio_o_20_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_19_LSB      19
#define   REG_FPGAIO_OUT31_00_fpgaio_o_19_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_18_LSB      18
#define   REG_FPGAIO_OUT31_00_fpgaio_o_18_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_17_LSB      17
#define   REG_FPGAIO_OUT31_00_fpgaio_o_17_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_16_LSB      16
#define   REG_FPGAIO_OUT31_00_fpgaio_o_16_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_15_LSB      15
#define   REG_FPGAIO_OUT31_00_fpgaio_o_15_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_14_LSB      14
#define   REG_FPGAIO_OUT31_00_fpgaio_o_14_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_13_LSB      13
#define   REG_FPGAIO_OUT31_00_fpgaio_o_13_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_12_LSB      12
#define   REG_FPGAIO_OUT31_00_fpgaio_o_12_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_11_LSB      11
#define   REG_FPGAIO_OUT31_00_fpgaio_o_11_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_10_LSB      10
#define   REG_FPGAIO_OUT31_00_fpgaio_o_10_MASK     0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_9_LSB       9
#define   REG_FPGAIO_OUT31_00_fpgaio_o_9_MASK      0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_8_LSB       8
#define   REG_FPGAIO_OUT31_00_fpgaio_o_8_MASK      0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_7_LSB       7
#define   REG_FPGAIO_OUT31_00_fpgaio_o_7_MASK      0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_6_LSB       6
#define   REG_FPGAIO_OUT31_00_fpgaio_o_6_MASK      0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_5_LSB       5
#define   REG_FPGAIO_OUT31_00_fpgaio_o_5_MASK      0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_4_LSB       4
#define   REG_FPGAIO_OUT31_00_fpgaio_o_4_MASK      0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_3_LSB       3
#define   REG_FPGAIO_OUT31_00_fpgaio_o_3_MASK      0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_2_LSB       2
#define   REG_FPGAIO_OUT31_00_fpgaio_o_2_MASK      0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_1_LSB       1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_1_MASK      0x1
#define   REG_FPGAIO_OUT31_00_fpgaio_o_0_LSB       0
#define   REG_FPGAIO_OUT31_00_fpgaio_o_0_MASK      0x1
#define REG_FPGAIO_OUT63_32            0x44
#define   REG_FPGAIO_OUT63_32_fpgaio_o_63_LSB      31
#define   REG_FPGAIO_OUT63_32_fpgaio_o_63_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_62_LSB      30
#define   REG_FPGAIO_OUT63_32_fpgaio_o_62_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_61_LSB      29
#define   REG_FPGAIO_OUT63_32_fpgaio_o_61_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_60_LSB      28
#define   REG_FPGAIO_OUT63_32_fpgaio_o_60_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_59_LSB      27
#define   REG_FPGAIO_OUT63_32_fpgaio_o_59_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_58_LSB      26
#define   REG_FPGAIO_OUT63_32_fpgaio_o_58_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_57_LSB      25
#define   REG_FPGAIO_OUT63_32_fpgaio_o_57_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_56_LSB      24
#define   REG_FPGAIO_OUT63_32_fpgaio_o_56_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_55_LSB      23
#define   REG_FPGAIO_OUT63_32_fpgaio_o_55_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_54_LSB      22
#define   REG_FPGAIO_OUT63_32_fpgaio_o_54_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_53_LSB      21
#define   REG_FPGAIO_OUT63_32_fpgaio_o_53_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_52_LSB      20
#define   REG_FPGAIO_OUT63_32_fpgaio_o_52_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_51_LSB      19
#define   REG_FPGAIO_OUT63_32_fpgaio_o_51_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_50_LSB      18
#define   REG_FPGAIO_OUT63_32_fpgaio_o_50_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_49_LSB      17
#define   REG_FPGAIO_OUT63_32_fpgaio_o_49_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_48_LSB      16
#define   REG_FPGAIO_OUT63_32_fpgaio_o_48_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_47_LSB      15
#define   REG_FPGAIO_OUT63_32_fpgaio_o_47_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_46_LSB      14
#define   REG_FPGAIO_OUT63_32_fpgaio_o_46_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_45_LSB      13
#define   REG_FPGAIO_OUT63_32_fpgaio_o_45_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_44_LSB      12
#define   REG_FPGAIO_OUT63_32_fpgaio_o_44_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_43_LSB      11
#define   REG_FPGAIO_OUT63_32_fpgaio_o_43_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_42_LSB      10
#define   REG_FPGAIO_OUT63_32_fpgaio_o_42_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_41_LSB      9
#define   REG_FPGAIO_OUT63_32_fpgaio_o_41_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_40_LSB      8
#define   REG_FPGAIO_OUT63_32_fpgaio_o_40_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_39_LSB      7
#define   REG_FPGAIO_OUT63_32_fpgaio_o_39_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_38_LSB      6
#define   REG_FPGAIO_OUT63_32_fpgaio_o_38_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_37_LSB      5
#define   REG_FPGAIO_OUT63_32_fpgaio_o_37_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_36_LSB      4
#define   REG_FPGAIO_OUT63_32_fpgaio_o_36_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_35_LSB      3
#define   REG_FPGAIO_OUT63_32_fpgaio_o_35_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_34_LSB      2
#define   REG_FPGAIO_OUT63_32_fpgaio_o_34_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_33_LSB      1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_33_MASK     0x1
#define   REG_FPGAIO_OUT63_32_fpgaio_o_32_LSB      0
#define   REG_FPGAIO_OUT63_32_fpgaio_o_32_MASK     0x1
#define REG_FPGAIO_OUT79_64            0x48
#define   REG_FPGAIO_OUT79_64_fpgaio_o_79_LSB      15
#define   REG_FPGAIO_OUT79_64_fpgaio_o_79_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_78_LSB      14
#define   REG_FPGAIO_OUT79_64_fpgaio_o_78_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_77_LSB      13
#define   REG_FPGAIO_OUT79_64_fpgaio_o_77_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_76_LSB      12
#define   REG_FPGAIO_OUT79_64_fpgaio_o_76_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_75_LSB      11
#define   REG_FPGAIO_OUT79_64_fpgaio_o_75_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_74_LSB      10
#define   REG_FPGAIO_OUT79_64_fpgaio_o_74_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_73_LSB      9
#define   REG_FPGAIO_OUT79_64_fpgaio_o_73_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_72_LSB      8
#define   REG_FPGAIO_OUT79_64_fpgaio_o_72_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_71_LSB      7
#define   REG_FPGAIO_OUT79_64_fpgaio_o_71_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_70_LSB      6
#define   REG_FPGAIO_OUT79_64_fpgaio_o_70_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_69_LSB      5
#define   REG_FPGAIO_OUT79_64_fpgaio_o_69_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_68_LSB      4
#define   REG_FPGAIO_OUT79_64_fpgaio_o_68_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_67_LSB      3
#define   REG_FPGAIO_OUT79_64_fpgaio_o_67_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_66_LSB      2
#define   REG_FPGAIO_OUT79_64_fpgaio_o_66_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_65_LSB      1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_65_MASK     0x1
#define   REG_FPGAIO_OUT79_64_fpgaio_o_64_LSB      0
#define   REG_FPGAIO_OUT79_64_fpgaio_o_64_MASK     0x1
#define REG_FPGAIO_OE31_00             0x50
#define   REG_FPGAIO_OE31_00_fpgaio_oe_31_LSB      31
#define   REG_FPGAIO_OE31_00_fpgaio_oe_31_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_30_LSB      30
#define   REG_FPGAIO_OE31_00_fpgaio_oe_30_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_29_LSB      29
#define   REG_FPGAIO_OE31_00_fpgaio_oe_29_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_28_LSB      28
#define   REG_FPGAIO_OE31_00_fpgaio_oe_28_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_27_LSB      27
#define   REG_FPGAIO_OE31_00_fpgaio_oe_27_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_26_LSB      26
#define   REG_FPGAIO_OE31_00_fpgaio_oe_26_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_25_LSB      25
#define   REG_FPGAIO_OE31_00_fpgaio_oe_25_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_24_LSB      24
#define   REG_FPGAIO_OE31_00_fpgaio_oe_24_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_23_LSB      23
#define   REG_FPGAIO_OE31_00_fpgaio_oe_23_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_22_LSB      22
#define   REG_FPGAIO_OE31_00_fpgaio_oe_22_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_21_LSB      21
#define   REG_FPGAIO_OE31_00_fpgaio_oe_21_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_20_LSB      20
#define   REG_FPGAIO_OE31_00_fpgaio_oe_20_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_19_LSB      19
#define   REG_FPGAIO_OE31_00_fpgaio_oe_19_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_18_LSB      18
#define   REG_FPGAIO_OE31_00_fpgaio_oe_18_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_17_LSB      17
#define   REG_FPGAIO_OE31_00_fpgaio_oe_17_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_16_LSB      16
#define   REG_FPGAIO_OE31_00_fpgaio_oe_16_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_15_LSB      15
#define   REG_FPGAIO_OE31_00_fpgaio_oe_15_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_14_LSB      14
#define   REG_FPGAIO_OE31_00_fpgaio_oe_14_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_13_LSB      13
#define   REG_FPGAIO_OE31_00_fpgaio_oe_13_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_12_LSB      12
#define   REG_FPGAIO_OE31_00_fpgaio_oe_12_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_11_LSB      11
#define   REG_FPGAIO_OE31_00_fpgaio_oe_11_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_10_LSB      10
#define   REG_FPGAIO_OE31_00_fpgaio_oe_10_MASK     0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_9_LSB       9
#define   REG_FPGAIO_OE31_00_fpgaio_oe_9_MASK      0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_8_LSB       8
#define   REG_FPGAIO_OE31_00_fpgaio_oe_8_MASK      0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_7_LSB       7
#define   REG_FPGAIO_OE31_00_fpgaio_oe_7_MASK      0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_6_LSB       6
#define   REG_FPGAIO_OE31_00_fpgaio_oe_6_MASK      0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_5_LSB       5
#define   REG_FPGAIO_OE31_00_fpgaio_oe_5_MASK      0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_4_LSB       4
#define   REG_FPGAIO_OE31_00_fpgaio_oe_4_MASK      0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_3_LSB       3
#define   REG_FPGAIO_OE31_00_fpgaio_oe_3_MASK      0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_2_LSB       2
#define   REG_FPGAIO_OE31_00_fpgaio_oe_2_MASK      0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_1_LSB       1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_1_MASK      0x1
#define   REG_FPGAIO_OE31_00_fpgaio_oe_0_LSB       0
#define   REG_FPGAIO_OE31_00_fpgaio_oe_0_MASK      0x1
#define REG_FPGAIO_OE63_32             0x54
#define   REG_FPGAIO_OE63_32_fpgaio_oe_63_LSB      31
#define   REG_FPGAIO_OE63_32_fpgaio_oe_63_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_62_LSB      30
#define   REG_FPGAIO_OE63_32_fpgaio_oe_62_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_61_LSB      29
#define   REG_FPGAIO_OE63_32_fpgaio_oe_61_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_60_LSB      28
#define   REG_FPGAIO_OE63_32_fpgaio_oe_60_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_59_LSB      27
#define   REG_FPGAIO_OE63_32_fpgaio_oe_59_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_58_LSB      26
#define   REG_FPGAIO_OE63_32_fpgaio_oe_58_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_57_LSB      25
#define   REG_FPGAIO_OE63_32_fpgaio_oe_57_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_56_LSB      24
#define   REG_FPGAIO_OE63_32_fpgaio_oe_56_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_55_LSB      23
#define   REG_FPGAIO_OE63_32_fpgaio_oe_55_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_54_LSB      22
#define   REG_FPGAIO_OE63_32_fpgaio_oe_54_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_53_LSB      21
#define   REG_FPGAIO_OE63_32_fpgaio_oe_53_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_52_LSB      20
#define   REG_FPGAIO_OE63_32_fpgaio_oe_52_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_51_LSB      19
#define   REG_FPGAIO_OE63_32_fpgaio_oe_51_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_50_LSB      18
#define   REG_FPGAIO_OE63_32_fpgaio_oe_50_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_49_LSB      17
#define   REG_FPGAIO_OE63_32_fpgaio_oe_49_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_48_LSB      16
#define   REG_FPGAIO_OE63_32_fpgaio_oe_48_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_47_LSB      15
#define   REG_FPGAIO_OE63_32_fpgaio_oe_47_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_46_LSB      14
#define   REG_FPGAIO_OE63_32_fpgaio_oe_46_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_45_LSB      13
#define   REG_FPGAIO_OE63_32_fpgaio_oe_45_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_44_LSB      12
#define   REG_FPGAIO_OE63_32_fpgaio_oe_44_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_43_LSB      11
#define   REG_FPGAIO_OE63_32_fpgaio_oe_43_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_42_LSB      10
#define   REG_FPGAIO_OE63_32_fpgaio_oe_42_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_41_LSB      9
#define   REG_FPGAIO_OE63_32_fpgaio_oe_41_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_40_LSB      8
#define   REG_FPGAIO_OE63_32_fpgaio_oe_40_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_39_LSB      7
#define   REG_FPGAIO_OE63_32_fpgaio_oe_39_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_38_LSB      6
#define   REG_FPGAIO_OE63_32_fpgaio_oe_38_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_37_LSB      5
#define   REG_FPGAIO_OE63_32_fpgaio_oe_37_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_36_LSB      4
#define   REG_FPGAIO_OE63_32_fpgaio_oe_36_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_35_LSB      3
#define   REG_FPGAIO_OE63_32_fpgaio_oe_35_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_34_LSB      2
#define   REG_FPGAIO_OE63_32_fpgaio_oe_34_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_33_LSB      1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_33_MASK     0x1
#define   REG_FPGAIO_OE63_32_fpgaio_oe_32_LSB      0
#define   REG_FPGAIO_OE63_32_fpgaio_oe_32_MASK     0x1
#define REG_FPGAIO_OE79_64             0x58
#define   REG_FPGAIO_OE79_64_fpgaio_oe_79_LSB      15
#define   REG_FPGAIO_OE79_64_fpgaio_oe_79_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_78_LSB      14
#define   REG_FPGAIO_OE79_64_fpgaio_oe_78_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_77_LSB      13
#define   REG_FPGAIO_OE79_64_fpgaio_oe_77_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_76_LSB      12
#define   REG_FPGAIO_OE79_64_fpgaio_oe_76_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_75_LSB      11
#define   REG_FPGAIO_OE79_64_fpgaio_oe_75_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_74_LSB      10
#define   REG_FPGAIO_OE79_64_fpgaio_oe_74_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_73_LSB      9
#define   REG_FPGAIO_OE79_64_fpgaio_oe_73_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_72_LSB      8
#define   REG_FPGAIO_OE79_64_fpgaio_oe_72_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_71_LSB      7
#define   REG_FPGAIO_OE79_64_fpgaio_oe_71_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_70_LSB      6
#define   REG_FPGAIO_OE79_64_fpgaio_oe_70_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_69_LSB      5
#define   REG_FPGAIO_OE79_64_fpgaio_oe_69_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_68_LSB      4
#define   REG_FPGAIO_OE79_64_fpgaio_oe_68_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_67_LSB      3
#define   REG_FPGAIO_OE79_64_fpgaio_oe_67_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_66_LSB      2
#define   REG_FPGAIO_OE79_64_fpgaio_oe_66_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_65_LSB      1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_65_MASK     0x1
#define   REG_FPGAIO_OE79_64_fpgaio_oe_64_LSB      0
#define   REG_FPGAIO_OE79_64_fpgaio_oe_64_MASK     0x1
#define REG_FPGAIO_IN31_00             0x60
#define   REG_FPGAIO_IN31_00_fpgaio_i_31_LSB       31
#define   REG_FPGAIO_IN31_00_fpgaio_i_31_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_30_LSB       30
#define   REG_FPGAIO_IN31_00_fpgaio_i_30_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_29_LSB       29
#define   REG_FPGAIO_IN31_00_fpgaio_i_29_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_28_LSB       28
#define   REG_FPGAIO_IN31_00_fpgaio_i_28_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_27_LSB       27
#define   REG_FPGAIO_IN31_00_fpgaio_i_27_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_26_LSB       26
#define   REG_FPGAIO_IN31_00_fpgaio_i_26_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_25_LSB       25
#define   REG_FPGAIO_IN31_00_fpgaio_i_25_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_24_LSB       24
#define   REG_FPGAIO_IN31_00_fpgaio_i_24_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_23_LSB       23
#define   REG_FPGAIO_IN31_00_fpgaio_i_23_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_22_LSB       22
#define   REG_FPGAIO_IN31_00_fpgaio_i_22_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_21_LSB       21
#define   REG_FPGAIO_IN31_00_fpgaio_i_21_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_20_LSB       20
#define   REG_FPGAIO_IN31_00_fpgaio_i_20_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_19_LSB       19
#define   REG_FPGAIO_IN31_00_fpgaio_i_19_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_18_LSB       18
#define   REG_FPGAIO_IN31_00_fpgaio_i_18_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_17_LSB       17
#define   REG_FPGAIO_IN31_00_fpgaio_i_17_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_16_LSB       16
#define   REG_FPGAIO_IN31_00_fpgaio_i_16_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_15_LSB       15
#define   REG_FPGAIO_IN31_00_fpgaio_i_15_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_14_LSB       14
#define   REG_FPGAIO_IN31_00_fpgaio_i_14_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_13_LSB       13
#define   REG_FPGAIO_IN31_00_fpgaio_i_13_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_12_LSB       12
#define   REG_FPGAIO_IN31_00_fpgaio_i_12_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_11_LSB       11
#define   REG_FPGAIO_IN31_00_fpgaio_i_11_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_10_LSB       10
#define   REG_FPGAIO_IN31_00_fpgaio_i_10_MASK      0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_9_LSB        9
#define   REG_FPGAIO_IN31_00_fpgaio_i_9_MASK       0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_8_LSB        8
#define   REG_FPGAIO_IN31_00_fpgaio_i_8_MASK       0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_7_LSB        7
#define   REG_FPGAIO_IN31_00_fpgaio_i_7_MASK       0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_6_LSB        6
#define   REG_FPGAIO_IN31_00_fpgaio_i_6_MASK       0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_5_LSB        5
#define   REG_FPGAIO_IN31_00_fpgaio_i_5_MASK       0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_4_LSB        4
#define   REG_FPGAIO_IN31_00_fpgaio_i_4_MASK       0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_3_LSB        3
#define   REG_FPGAIO_IN31_00_fpgaio_i_3_MASK       0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_2_LSB        2
#define   REG_FPGAIO_IN31_00_fpgaio_i_2_MASK       0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_1_LSB        1
#define   REG_FPGAIO_IN31_00_fpgaio_i_1_MASK       0x1
#define   REG_FPGAIO_IN31_00_fpgaio_i_0_LSB        0
#define   REG_FPGAIO_IN31_00_fpgaio_i_0_MASK       0x1
#define REG_FPGAIO_IN63_32             0x64
#define   REG_FPGAIO_IN63_32_fpgaio_i_63_LSB       31
#define   REG_FPGAIO_IN63_32_fpgaio_i_63_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_62_LSB       30
#define   REG_FPGAIO_IN63_32_fpgaio_i_62_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_61_LSB       29
#define   REG_FPGAIO_IN63_32_fpgaio_i_61_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_60_LSB       28
#define   REG_FPGAIO_IN63_32_fpgaio_i_60_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_59_LSB       27
#define   REG_FPGAIO_IN63_32_fpgaio_i_59_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_58_LSB       26
#define   REG_FPGAIO_IN63_32_fpgaio_i_58_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_57_LSB       25
#define   REG_FPGAIO_IN63_32_fpgaio_i_57_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_56_LSB       24
#define   REG_FPGAIO_IN63_32_fpgaio_i_56_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_55_LSB       23
#define   REG_FPGAIO_IN63_32_fpgaio_i_55_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_54_LSB       22
#define   REG_FPGAIO_IN63_32_fpgaio_i_54_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_53_LSB       21
#define   REG_FPGAIO_IN63_32_fpgaio_i_53_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_52_LSB       20
#define   REG_FPGAIO_IN63_32_fpgaio_i_52_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_51_LSB       19
#define   REG_FPGAIO_IN63_32_fpgaio_i_51_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_50_LSB       18
#define   REG_FPGAIO_IN63_32_fpgaio_i_50_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_49_LSB       17
#define   REG_FPGAIO_IN63_32_fpgaio_i_49_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_48_LSB       16
#define   REG_FPGAIO_IN63_32_fpgaio_i_48_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_47_LSB       15
#define   REG_FPGAIO_IN63_32_fpgaio_i_47_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_46_LSB       14
#define   REG_FPGAIO_IN63_32_fpgaio_i_46_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_45_LSB       13
#define   REG_FPGAIO_IN63_32_fpgaio_i_45_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_44_LSB       12
#define   REG_FPGAIO_IN63_32_fpgaio_i_44_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_43_LSB       11
#define   REG_FPGAIO_IN63_32_fpgaio_i_43_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_42_LSB       10
#define   REG_FPGAIO_IN63_32_fpgaio_i_42_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_41_LSB       9
#define   REG_FPGAIO_IN63_32_fpgaio_i_41_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_40_LSB       8
#define   REG_FPGAIO_IN63_32_fpgaio_i_40_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_39_LSB       7
#define   REG_FPGAIO_IN63_32_fpgaio_i_39_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_38_LSB       6
#define   REG_FPGAIO_IN63_32_fpgaio_i_38_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_37_LSB       5
#define   REG_FPGAIO_IN63_32_fpgaio_i_37_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_36_LSB       4
#define   REG_FPGAIO_IN63_32_fpgaio_i_36_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_35_LSB       3
#define   REG_FPGAIO_IN63_32_fpgaio_i_35_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_34_LSB       2
#define   REG_FPGAIO_IN63_32_fpgaio_i_34_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_33_LSB       1
#define   REG_FPGAIO_IN63_32_fpgaio_i_33_MASK      0x1
#define   REG_FPGAIO_IN63_32_fpgaio_i_32_LSB       0
#define   REG_FPGAIO_IN63_32_fpgaio_i_32_MASK      0x1
#define REG_FPGAIO_IN79_64             0x68
#define   REG_FPGAIO_IN79_64_fpgaio_i_79_LSB       15
#define   REG_FPGAIO_IN79_64_fpgaio_i_79_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_78_LSB       14
#define   REG_FPGAIO_IN79_64_fpgaio_i_78_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_77_LSB       13
#define   REG_FPGAIO_IN79_64_fpgaio_i_77_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_76_LSB       12
#define   REG_FPGAIO_IN79_64_fpgaio_i_76_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_75_LSB       11
#define   REG_FPGAIO_IN79_64_fpgaio_i_75_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_74_LSB       10
#define   REG_FPGAIO_IN79_64_fpgaio_i_74_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_73_LSB       9
#define   REG_FPGAIO_IN79_64_fpgaio_i_73_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_72_LSB       8
#define   REG_FPGAIO_IN79_64_fpgaio_i_72_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_71_LSB       7
#define   REG_FPGAIO_IN79_64_fpgaio_i_71_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_70_LSB       6
#define   REG_FPGAIO_IN79_64_fpgaio_i_70_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_69_LSB       5
#define   REG_FPGAIO_IN79_64_fpgaio_i_69_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_68_LSB       4
#define   REG_FPGAIO_IN79_64_fpgaio_i_68_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_67_LSB       3
#define   REG_FPGAIO_IN79_64_fpgaio_i_67_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_66_LSB       2
#define   REG_FPGAIO_IN79_64_fpgaio_i_66_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_65_LSB       1
#define   REG_FPGAIO_IN79_64_fpgaio_i_65_MASK      0x1
#define   REG_FPGAIO_IN79_64_fpgaio_i_64_LSB       0
#define   REG_FPGAIO_IN79_64_fpgaio_i_64_MASK      0x1
#define REG_FPGA_EVENT15_00            0x6C
#define   REG_FPGA_EVENT15_00_Event_15_LSB         15
#define   REG_FPGA_EVENT15_00_Event_15_MASK        0x1
#define   REG_FPGA_EVENT15_00_Event_14_LSB         14
#define   REG_FPGA_EVENT15_00_Event_14_MASK        0x1
#define   REG_FPGA_EVENT15_00_Event_13_LSB         13
#define   REG_FPGA_EVENT15_00_Event_13_MASK        0x1
#define   REG_FPGA_EVENT15_00_Event_12_LSB         12
#define   REG_FPGA_EVENT15_00_Event_12_MASK        0x1
#define   REG_FPGA_EVENT15_00_Event_11_LSB         11
#define   REG_FPGA_EVENT15_00_Event_11_MASK        0x1
#define   REG_FPGA_EVENT15_00_Event_10_LSB         10
#define   REG_FPGA_EVENT15_00_Event_10_MASK        0x1
#define   REG_FPGA_EVENT15_00_Event_9_LSB          9
#define   REG_FPGA_EVENT15_00_Event_9_MASK         0x1
#define   REG_FPGA_EVENT15_00_Event_8_LSB          8
#define   REG_FPGA_EVENT15_00_Event_8_MASK         0x1
#define   REG_FPGA_EVENT15_00_Event_7_LSB          7
#define   REG_FPGA_EVENT15_00_Event_7_MASK         0x1
#define   REG_FPGA_EVENT15_00_Event_6_LSB          6
#define   REG_FPGA_EVENT15_00_Event_6_MASK         0x1
#define   REG_FPGA_EVENT15_00_Event_5_LSB          5
#define   REG_FPGA_EVENT15_00_Event_5_MASK         0x1
#define   REG_FPGA_EVENT15_00_Event_4_LSB          4
#define   REG_FPGA_EVENT15_00_Event_4_MASK         0x1
#define   REG_FPGA_EVENT15_00_Event_3_LSB          3
#define   REG_FPGA_EVENT15_00_Event_3_MASK         0x1
#define   REG_FPGA_EVENT15_00_Event_2_LSB          2
#define   REG_FPGA_EVENT15_00_Event_2_MASK         0x1
#define   REG_FPGA_EVENT15_00_Event_1_LSB          1
#define   REG_FPGA_EVENT15_00_Event_1_MASK         0x1
#define   REG_FPGA_EVENT15_00_Event_0_LSB          0
#define   REG_FPGA_EVENT15_00_Event_0_MASK         0x1
#define REG_TCDM_RUN_P0                0x80
#define   REG_TCDM_RUN_P0_tcdm_wdata_p0_LSB        0
#define   REG_TCDM_RUN_P0_tcdm_wdata_p0_MASK       0xffffffff
#define REG_TCDM_RUN_P1                0x84
#define   REG_TCDM_RUN_P1_tcdm_wdata_p0_LSB        0
#define   REG_TCDM_RUN_P1_tcdm_wdata_p0_MASK       0xffffffff
#define REG_TCDM_RUN_P2                0x88
#define   REG_TCDM_RUN_P2_tcdm_wdata_p0_LSB        0
#define   REG_TCDM_RUN_P2_tcdm_wdata_p0_MASK       0xffffffff
#define REG_TCDM_RUN_P3                0x8C
#define   REG_TCDM_RUN_P3_tcdm_wdata_p0_LSB        0
#define   REG_TCDM_RUN_P3_tcdm_wdata_p0_MASK       0xffffffff
#define REG_M0_M0_ODATA                0x90
#define   REG_M0_M0_ODATA_odata_LSB                0
#define   REG_M0_M0_ODATA_odata_MASK               0xffffffff
#define REG_M0_M1_ODATA                0x94
#define   REG_M0_M1_ODATA_odata_LSB                0
#define   REG_M0_M1_ODATA_odata_MASK               0xffffffff
#define REG_M0_M0_CDATA                0x98
#define   REG_M0_M0_CDATA_cdata_LSB                0
#define   REG_M0_M0_CDATA_cdata_MASK               0xffffffff
#define REG_M0_M1_CDATA                0x9C
#define   REG_M0_M1_CDATA_cdata_LSB                0
#define   REG_M0_M1_CDATA_cdata_MASK               0xffffffff
#define REG_M1_M0_ODATA                0xA0
#define   REG_M1_M0_ODATA_odata_LSB                0
#define   REG_M1_M0_ODATA_odata_MASK               0xffffffff
#define REG_M1_M1_ODATA                0xA4
#define   REG_M1_M1_ODATA_odata_LSB                0
#define   REG_M1_M1_ODATA_odata_MASK               0xffffffff
#define REG_M1_M0_CDATA                0xA8
#define   REG_M1_M0_CDATA_cdata_LSB                0
#define   REG_M1_M0_CDATA_cdata_MASK               0xffffffff
#define REG_M1_M1_CDATA                0xAC
#define   REG_M1_M1_CDATA_cdata_LSB                0
#define   REG_M1_M1_CDATA_cdata_MASK               0xffffffff
#define REG_M0_M0_MULTOUT              0x100
#define   REG_M0_M0_MULTOUT_multout_LSB            0
#define   REG_M0_M0_MULTOUT_multout_MASK           0xffffffff
#define REG_M0_M1_MULTOUT              0x104
#define   REG_M0_M1_MULTOUT_multout_LSB            0
#define   REG_M0_M1_MULTOUT_multout_MASK           0xffffffff
#define REG_M1_M0_MULTOUT              0x108
#define   REG_M1_M0_MULTOUT_multout_LSB            0
#define   REG_M1_M0_MULTOUT_multout_MASK           0xffffffff
#define REG_M1_M1_MULTOUT              0x10C
#define   REG_M1_M01MULTOUT_multout_LSB            0
#define   REG_M1_M01MULTOUT_multout_MASK           0xffffffff
#define REG_M0_OPER0                   0x1000
#define REG_M0_OPER1                   0x2000
#define REG_M0_COEF                    0x3000
#define REG_M1_OPER0                   0x4000
#define REG_M1_OPER1                   0x5000
#define REG_M1_COEF                    0x6000

#ifndef __REGFIELD_OPS_
#define __REGFIELD_OPS_
static inline uint32_t regfield_read(uint32_t reg, uint32_t mask, uint32_t lsb) {
  return (reg >> lsb) & mask;
}
static inline uint32_t regfield_write(uint32_t reg, uint32_t mask, uint32_t lsb, uint32_t value) {
  reg &= ~(mask << lsb);
  reg |= (value & mask) << lsb;
  return reg;
}
#endif  // __REGFIELD_OPS_

#endif // __EFPGA_H_
