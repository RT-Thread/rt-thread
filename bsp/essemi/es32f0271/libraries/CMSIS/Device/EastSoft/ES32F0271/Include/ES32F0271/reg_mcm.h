/**
  **************************************************************************************
  * @file    reg_MCM.h
  * @brief   MCM Head File
  *
  * @version V1.00.01
  * @data    19/10/2018
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __MCM_H__
#define __MCM_H__

typedef struct
{
    __IO uint32_t      RAMP_INI;    // 0x00  MCM Ramp Generator Initialization Register
    __IO uint32_t    RAMP_IDATA;    // 0x04  MCM Ramp Generator Initial Data Register
    __IO uint32_t      RAMP_DIV;    // 0x08  MCM Ramp Clock Divider Register
    __IO uint32_t    RAMP_SCALE;    // 0x0C  MCM Ramp Generator Output Scale Register
    __IO uint32_t     RAMP_STEP;    // 0x10  MCM Step Increment of the Ramp Output Register
    __IO uint32_t      RAMP_SET;    // 0x14  MCM Ramp Generator Reference Data Register
    __IO uint32_t       RAMP_EN;    // 0x18  MCM Ramp Generator Enable Register
    __I  uint32_t       RAMP_DO;    // 0x1C  MCM Ramp Generator Output Register
    __IO uint32_t      RMAP_CON;    // 0x20  MCM Connect Ramp Generator to PI control Register
    __IO uint32_t        IX_UPD;    // 0x24  MCM Inverse Transform Update Register
    __IO uint32_t         IX_VQ;    // 0x28  MCM Inverse Park Transform Vq Input Register
    __IO uint32_t         IX_VD;    // 0x2C  MCM Inverse Park Transform Vd Input Register
    __I  uint32_t         IX_VA;    // 0x30  MCM Inverse Clarke Transform Va Output Register
    __I  uint32_t         IX_VB;    // 0x34  MCM Inverse Clarke Transform Vb Output Register
    __I  uint32_t         IX_VC;    // 0x38  MCM Inverse Clarke Transform Vc Output Register
    __I  uint32_t     IX_VALPHA;    // 0x3C  MCM Inverse Clarke Transform Valpha Output Register
    __I  uint32_t      IX_VBETA;    // 0x40  MCM Inverse Clarke Transform Vbeta Output Register
    __I  uint32_t      IX_SVMVA;    // 0x44  MCM Inverse Clarke Transform SVPWM Va Output Register
    __I  uint32_t      IX_SVMVB;    // 0x48  MCM Inverse Clarke Transform SVPWM Vb Output Register
    __I  uint32_t      IX_SVMVC;    // 0x4C  MCM Inverse Clarke Transform SVPWM Vc Output Register
    __I  uint32_t       IX_DONE;    // 0x50  MCM Inverse Transform Processing Status Register
    __I  uint32_t      IX_SDONE;    // 0x54  MCM Inverse SVPWM Process Status Register
    __IO uint32_t        IX_CON;    // 0x58  MCM Connect PI Control To The Inverse Transform Register
    __IO uint32_t     IX_NORMAL;    // 0x5C  MCM Normal Clarke Inverse Transform Register
    __IO uint32_t         X_UPD;    // 0x60  MCM Transform Function Update Register
    __IO uint32_t          X_IA;    // 0x64  MCM Clarke Transform Ia Input Register
    __IO uint32_t          X_IB;    // 0x68  MCM Clarke Transform Ib Input Register
    __IO uint32_t          X_IC;    // 0x6C  MCM Clarke Transform Ic Input Register
    __I  uint32_t      X_IALPHA;    // 0x70  MCM Clarke Transform Ialpha Output Register
    __I  uint32_t       X_IBETA;    // 0x74  MCM Clarke Transform Ibeta Output Register
    __I  uint32_t          X_ID;    // 0x78  MCM Park Transform Id Output Register
    __I  uint32_t          X_IQ;    // 0x7C  MCM Park Transform Iq Output Register
    __I  uint32_t        X_DONE;    // 0x80  MCM Transform Process Status Register
    __IO uint32_t         X_CON;    // 0x84  MCM Forward Transform Input Source Selection Register
         uint32_t         REV88;    // 0x88  RESERVED
    __IO uint32_t       PI0_UPD;    // 0x8C  MCM PI Control 0 Update Register
    __IO uint32_t       PI0_INI;    // 0x90  MCM Initialize PI Control 0 Register
    __IO uint32_t     PI0_IDATA;    // 0x94  MCM PI Control 0 Initial Data Register
    __IO uint32_t    PI0_ELIMIT;    // 0x98  MCM PI Control 0 Error Limit Register
    __IO uint32_t        PI0_KP;    // 0x9C  MCM PI Control 0 Kp Coefficient Register
    __IO uint32_t        PI0_KI;    // 0xA0  MCM PI Control 0 Ki Coefficient Register
    __IO uint32_t       PI0_REF;    // 0xA4  MCM PI Control 0 Reference Value Register
    __IO uint32_t    PI0_ACTUAL;    // 0xA8  MCM PI Control 0 Actual Value Register
    __IO uint32_t       PI0_MIN;    // 0xAC  MCM PI Control 0 Minimum Output Register
    __IO uint32_t       PI0_MAX;    // 0xB0  MCM PI Control 0 Maximum Output Register
    __I  uint32_t        PI0_DO;    // 0xB4  MCM PI Control 0 Data Out Register
    __IO uint32_t    PI0_OSCALE;    // 0xB8  MCM PI Control 0 Data Output Scale Register
    __I  uint32_t       PI_DONE;    // 0xBC  MCM PI Control Processing Status Register
    __IO uint32_t       PI1_UPD;    // 0xC0  MCM PI Control 1 Update Register
    __IO uint32_t       PI1_INI;    // 0xC4  MCM Initialize PI Control 1 Register
    __IO uint32_t     PI1_IDATA;    // 0xC8  MCM PI Control 1 Initial Data Register
    __IO uint32_t    PI1_ELIMIT;    // 0xCC  MCM PI Control 1 Error Limit Register
    __IO uint32_t        PI1_KP;    // 0xD0  MCM PI Control 1 Kp Coefficient Register
    __IO uint32_t        PI1_KI;    // 0xD4  MCM PI Control 1 Ki Coefficient Register
    __IO uint32_t       PI1_REF;    // 0xD8  MCM PI Control 1 Reference Value Register
    __IO uint32_t    PI1_ACTUAL;    // 0xDC  MCM PI Control 1 Actual Value Register
    __IO uint32_t       PI1_MIN;    // 0xE0  MCM PI Control 1 Minimum Output Register
    __IO uint32_t       PI1_MAX;    // 0xE4  MCM PI Control 1 Maximum Output Register
    __I  uint32_t        PI1_DO;    // 0xE8  MCM PI Control 1 Data Out Register
    __IO uint32_t    PI1_OSCALE;    // 0xEC  MCM PI Control 1 Data Output Scale Register
    __IO uint32_t       PI2_UPD;    // 0xF0  MCM PI Control 2 Update Register
    __IO uint32_t       PI2_INI;    // 0xF4  MCM Initialize PI Control 2 Register
    __IO uint32_t     PI2_IDATA;    // 0xF8  MCM PI Control 2 Initial Data Register
    __IO uint32_t    PI2_ELIMIT;    // 0xFC  MCM PI Control 2 Error Limit Register
    __IO uint32_t        PI2_KP;    // 0x100 MCM PI Control 2 Kp Coefficient Register
    __IO uint32_t        PI2_KI;    // 0x104 MCM PI Control 2 Ki Coefficient Register
    __IO uint32_t       PI2_REF;    // 0x108 MCM PI Control 2 Reference Value Register
    __IO uint32_t    PI2_ACTUAL;    // 0x10C MCM PI Control 2 Actual Value Register
    __IO uint32_t       PI2_MIN;    // 0x110 MCM PI Control 2 Minimum Output Register
    __IO uint32_t       PI2_MAX;    // 0x114 MCM PI Control 2 Maximum Output Register
    __I  uint32_t        PI2_DO;    // 0x118 MCM PI Control 2 Data Out Register
    __IO uint32_t    PI2_OSCALE;    // 0x11C MCM PI Control 2 Data Output Scale Register
    __IO uint32_t     COR_START;    // 0x120 MCM Start CORDIC Calculation Register
    __IO uint32_t         COR_X;    // 0x124 MCM CORDIC X Input Register
    __IO uint32_t         COR_Y;    // 0x128 MCM CORDIC Y Input Register
    __I  uint32_t       COR_RES;    // 0x12C MCM CORDIC Result Register
    __I  uint32_t      COR_DONE;    // 0x130 MCM CORDIC Processing Status Register
    __IO uint32_t       COR_CON;    // 0x134 MCM CORDIC Input Selection Register
         uint32_t        REV138;    // 0x138 RESERVED
         uint32_t        REV13C;    // 0x13C RESERVED
    __IO uint32_t      LPFA_INI;    // 0x140 MCM LPF A Channel Initialize Register
    __IO uint32_t      LPFA_UPD;    // 0x144 MCM LPF A Channel Update Register
    __IO uint32_t      LPFA_DIN;    // 0x148 MCM LPF A Input Register
    __IO uint32_t       LPFA_A0;    // 0x14C MCM LPF A a0 Coefficient Register
    __IO uint32_t       LPFA_B0;    // 0x150 MCM LPF A b0 Coefficient Register
    __IO uint32_t       LPFA_B1;    // 0x154 MCM LPF A b1 Coefficient Register

    __IO uint32_t  LPFA_A0SCALE;    // 0x158 MCM LPF A a0 Coefficient Scale Register
    __IO uint32_t  LPFA_B0SCALE;    // 0x15C MCM LPF A b0 Coefficient Scale Register
    __IO uint32_t  LPFA_B1SCALE;    // 0x160 MCM LPF A b1 Coefficient Scale Register

    __I  uint32_t       LPFA_DO;    // 0x164 MCM LPF A Data Output Register
    __I  uint32_t     LPFA_DONE;    // 0x168 MCM LPF A Process Status Register
    __IO uint32_t      LPFB_INI;    // 0x16C MCM LPF B Channel Initialize Register
    __IO uint32_t      LPFB_UPD;    // 0x170 MCM LPF B Channel Update Register
    __IO uint32_t      LPFB_DIN;    // 0x174 MCM LPF B Input Register
    __IO uint32_t       LPFB_A0;    // 0x178 MCM LPF B a0 Coefficient Register
    __IO uint32_t       LPFB_B0;    // 0x17C MCM LPF B b0 Coefficient Register
    __IO uint32_t       LPFB_B1;    // 0x180 MCM LPF B b1 Coefficient Register

    __IO uint32_t  LPFB_A0SCALE;    // 0x184 MCM LPF B a0 Coefficient Scale Register
    __IO uint32_t  LPFB_B0SCALE;    // 0x188 MCM LPF B b0 Coefficient Scale Register
    __IO uint32_t  LPFB_B1SCALE;    // 0x18C MCM LPF B b1 Coefficient Scale Register

    __I  uint32_t       LPFB_DO;    // 0x190 MCM LPF B Data Output Register
    __I  uint32_t     LPFB_DONE;    // 0x194 MCM LPF B Process Status Register
    __IO uint32_t      LPFC_INI;    // 0x198 MCM LPF C Channel Initialize Register
    __IO uint32_t      LPFC_UPD;    // 0x19C MCM LPF C Channel Update Register
    __IO uint32_t      LPFC_DIN;    // 0x1A0 MCM LPF C Input Register
    __IO uint32_t       LPFC_A0;    // 0x1A4 MCM LPF C a0 Coefficient Register
    __IO uint32_t       LPFC_B0;    // 0x1A8 MCM LPF C b0 Coefficient Register
    __IO uint32_t       LPFC_B1;    // 0x1AC MCM LPF C b1 Coefficient Register

    __IO uint32_t  LPFC_A0SCALE;    // 0x1B0 MCM LPF C a0 Coefficient Scale Register
    __IO uint32_t  LPFC_B0SCALE;    // 0x1B4 MCM LPF C b0 Coefficient Scale Register
    __IO uint32_t  LPFC_B1SCALE;    // 0x1B8 MCM LPF C b1 Coefficient Scale Register

    __I  uint32_t       LPFC_DO;    // 0x1BC MCM LPF C Data Output Register
    __I  uint32_t     LPFC_DONE;    // 0x1C0 MCM LPF C Process Status Register
    __IO uint32_t        GL_UPD;    // 0x1C4 MCM Global Update Register
    __IO uint32_t       GL_STAT;    // 0x1C8 MCM Global Status Register
    __IO uint32_t     THETA_SIN;    // 0x1CC MCM Sine Angle Register
    __IO uint32_t     THETA_COS;    // 0x1D0 MCM Cosine Angle Register
    __IO uint32_t       PI_TYPE;    // 0x1D4 MCM PI Control Type Register
    __IO uint32_t     MOTOR_DIR;    // 0x1D8 MCM Motor Direction Register
    __I  uint32_t       MCM_VER;    // 0x1DC MCM Version Register
    __IO uint32_t       SMC_UPD;    // 0x1E0 MCM Slide Mode Controller Update Register
    __IO uint32_t       SMC_INI;    // 0x1E4 MCM Slide Mode Controller Initialization Register
    __IO uint32_t  SMC_ALPHAINI;    // 0x1E8 MCM Slide Mode Controller Alpha Initial Data Register
    __IO uint32_t   SMC_BETAINI;    // 0x1EC MCM Slide Mode Controller Beta Initial Data Register
    __IO uint32_t        SMC_A0;    // 0x1F0 MCM Slide Mode Controller Dynamic LPF coefficient Register
    __IO uint32_t    SMC_ELIMIT;    // 0x1F4 MCM Slide Mode Controller Error Limit Register
    __IO uint32_t    SMC_KSLIDE;    // 0x1F8 MCM Slide Mode Controller Z Factor Error Amplification Register
    __I  uint32_t      SMC_DONE;    // 0x1FC MCM Slide Mode Controller Process Status Register
    __IO uint32_t   SMC_IEALPHA;    // 0x200 MCM SMC Estimated Current Alpha Register
    __IO uint32_t    SMC_IEBETA;    // 0x204 MCM SMC Estimated Current Beta Register
    __IO uint32_t    SMC_IALPHA;    // 0x208 MCM SMC Measured Current Alpha Register
    __IO uint32_t     SMC_IBETA;    // 0x20C MCM SMC Measured Current Beta Register
    __IO uint32_t      SMC_DISI;    // 0x210 MCM SMC Estimated Current Input Selection Register
    __I  uint32_t    SMC_ZALPHA;    // 0x214 MCM SMC Z Factor Alpha Register
    __I  uint32_t     SMC_ZBETA;    // 0x218 MCM SMC Z Factor Beta Register
    __I  uint32_t    SMC_BEMF1A;    // 0x21C MCM SMC Estimated BEMF Alpha Register
    __I  uint32_t    SMC_BEMF1B;    // 0x220 MCM SMC Estimated BEMF Beta Register
    __I  uint32_t    SMC_BEMF2A;    // 0x224 MCM SMC BEMF Filtered Alpha Register
    __I  uint32_t    SMC_BEMF2B;    // 0x228 MCM SMC BEMF Filtered Beta Register
    __IO uint32_t  SMC_LPFSCALE;    // 0x22C MCM SMC LPF Coefficient Scale Factor Register
         uint32_t        REV230;    // 0x230 RESERVED
    __IO uint32_t        VM_UPD;    // 0x234 MCM Virtual Motor Update Register
    __IO uint32_t        VM_INI;    // 0x238 MCM Virtual Motor Initialization Register
    __IO uint32_t   VM_ALPHAINI;    // 0x23C MCM Virtual Motor Initial Data Alpha Register
    __IO uint32_t    VM_BETAINI;    // 0x240 MCM Virtual Motor Initial Data Beta Register
    __IO uint32_t         VM_KF;    // 0x244 MCM Virtual Motor F Constant Register
    __IO uint32_t         VM_KG;    // 0x248 MCM Virtual Motor G Constant Register
    __IO uint32_t     VM_VALPHA;    // 0x24C MCM Virtual Motor Voltage Vector Alpha Register
    __IO uint32_t      VM_VBETA;    // 0x250 MCM Virtual Motor Voltage Vector BETA Register
    __IO uint32_t      VM_BEMFA;    // 0x254 MCM Virtual Motor BEMF Vector Alpha Register
    __IO uint32_t      VM_BEMFB;    // 0x258 MCM Virtual Motor BEMF Vector BETA Register
    __IO uint32_t     VM_ZALPHA;    // 0x25C MCM Virtual Motor Z Vector Alpha Register
    __IO uint32_t      VM_ZBETA;    // 0x260 MCM Virtual Motor Z Vector BETA Register
    __IO uint32_t       VM_DISZ;    // 0x264 MCM Virtual Motor Z Factor Input Selection Register
    __I  uint32_t       VM_DONE;    // 0x268 MCM Virtual Motor Process Status Register
    __I  uint32_t    VM_IEALPHA;    // 0x26C MCM Virtual Motor Estimated IS Result Alpha Register
    __I  uint32_t     VM_IEBETA;    // 0x270 MCM Virtual Motor Estimated IS Result BETA Register
    __IO uint32_t        VM_CON;    // 0x274 MCM Virtual Motor Connect Register

    __IO uint32_t    VM_KFSCALE;    // 0x278 MCM Virtual Motor F Constant Scale Register
    __IO uint32_t    VM_KGSCALE;    // 0x27C MCM Virtual Motor G Constant Scale Register
    __IO uint32_t      VM_CONVS;    // 0x280 MCM Virtual Motor Voltage Connect Register

         uint32_t        REV284;    // 0x284 RESERVED
    __IO uint32_t       SVM_UPD;    // 0x288 MCM SVM Update Register
    __IO uint32_t       SVM_CON;    // 0x28C MCM SVM Source Input Select Register
    __IO uint32_t      SVM_DINA;    // 0x290 MCM SVM Phase A Register
    __IO uint32_t      SVM_DINB;    // 0x294 MCM SVM Phase B Register
    __IO uint32_t      SVM_DINC;    // 0x298 MCM SVM Phase C Register
} MCM_TypeDef;

/******************************************************************************/
/*                              暫存器內部位元定義                            */
/******************************************************************************/

/* #pragma anon_unions */

/****************** Bit definition for WWDG_CR register ************************/




#else
/* */
#endif
