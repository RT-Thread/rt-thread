/******************************************************************************
 * @file     controller_functions.h
 * @brief    Public header file for CMSIS DSP Library
 * @version  V1.10.0
 * @date     08 July 2021
 * Target Processor: Cortex-M and Cortex-A cores
 ******************************************************************************/
/*
 * Copyright (c) 2010-2020 Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 
#ifndef _CONTROLLER_FUNCTIONS_H_
#define _CONTROLLER_FUNCTIONS_H_

#include "arm_math_types.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#ifdef   __cplusplus
extern "C"
{
#endif

  /**
   * @brief Macros required for SINE and COSINE Controller functions
   */

#define CONTROLLER_Q31_SHIFT  (32 - 9)
  /* 1.31(q31) Fixed value of 2/360 */
  /* -1 to +1 is divided into 360 values so total spacing is (2/360) */
#define INPUT_SPACING         0xB60B61
  
/**
 * @defgroup groupController Controller Functions
 */


 /**
   * @ingroup groupController
   */

  /**
   * @addtogroup SinCos
   * @{
   */

/**
   * @brief  Floating-point sin_cos function.
   * @param[in]  theta   input value in degrees
   * @param[out] pSinVal  points to the processed sine output.
   * @param[out] pCosVal  points to the processed cos output.
   */
  void arm_sin_cos_f32(
        float32_t theta,
        float32_t * pSinVal,
        float32_t * pCosVal);


  /**
   * @brief  Q31 sin_cos function.
   * @param[in]  theta    scaled input value in degrees
   * @param[out] pSinVal  points to the processed sine output.
   * @param[out] pCosVal  points to the processed cosine output.
   */
  void arm_sin_cos_q31(
        q31_t theta,
        q31_t * pSinVal,
        q31_t * pCosVal);

  /**
   * @} end of SinCos group
   */

 /**
   * @ingroup groupController
   */

/**
   * @defgroup PID PID Motor Control
   *
   * A Proportional Integral Derivative (PID) controller is a generic feedback control
   * loop mechanism widely used in industrial control systems.
   * A PID controller is the most commonly used type of feedback controller.
   *
   * This set of functions implements (PID) controllers
   * for Q15, Q31, and floating-point data types.  The functions operate on a single sample
   * of data and each call to the function returns a single processed value.
   * <code>S</code> points to an instance of the PID control data structure.  <code>in</code>
   * is the input sample value. The functions return the output value.
   *
   * \par Algorithm:
   * <pre>
   *    y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
   *    A0 = Kp + Ki + Kd
   *    A1 = (-Kp ) - (2 * Kd )
   *    A2 = Kd
   * </pre>
   *
   * \par
   * where \c Kp is proportional constant, \c Ki is Integral constant and \c Kd is Derivative constant
   *
   * \par
   * \image html PID.gif "Proportional Integral Derivative Controller"
   *
   * \par
   * The PID controller calculates an "error" value as the difference between
   * the measured output and the reference input.
   * The controller attempts to minimize the error by adjusting the process control inputs.
   * The proportional value determines the reaction to the current error,
   * the integral value determines the reaction based on the sum of recent errors,
   * and the derivative value determines the reaction based on the rate at which the error has been changing.
   *
   * \par Instance Structure
   * The Gains A0, A1, A2 and state variables for a PID controller are stored together in an instance data structure.
   * A separate instance structure must be defined for each PID Controller.
   * There are separate instance structure declarations for each of the 3 supported data types.
   *
   * \par Reset Functions
   * There is also an associated reset function for each data type which clears the state array.
   *
   * \par Initialization Functions
   * There is also an associated initialization function for each data type.
   * The initialization function performs the following operations:
   * - Initializes the Gains A0, A1, A2 from Kp,Ki, Kd gains.
   * - Zeros out the values in the state buffer.
   *
   * \par
   * Instance structure cannot be placed into a const data section and it is recommended to use the initialization function.
   *
   * \par Fixed-Point Behavior
   * Care must be taken when using the fixed-point versions of the PID Controller functions.
   * In particular, the overflow and saturation behavior of the accumulator used in each function must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */


  /**
   * @brief Instance structure for the Q15 PID Control.
   */
  typedef struct
  {
          q15_t A0;           /**< The derived gain, A0 = Kp + Ki + Kd . */
#if !defined (ARM_MATH_DSP)
          q15_t A1;           /**< The derived gain A1 = -Kp - 2Kd */
          q15_t A2;           /**< The derived gain A1 = Kd. */
#else
          q31_t A1;           /**< The derived gain A1 = -Kp - 2Kd | Kd.*/
#endif
          q15_t state[3];     /**< The state array of length 3. */
          q15_t Kp;           /**< The proportional gain. */
          q15_t Ki;           /**< The integral gain. */
          q15_t Kd;           /**< The derivative gain. */
  } arm_pid_instance_q15;

  /**
   * @brief Instance structure for the Q31 PID Control.
   */
  typedef struct
  {
          q31_t A0;            /**< The derived gain, A0 = Kp + Ki + Kd . */
          q31_t A1;            /**< The derived gain, A1 = -Kp - 2Kd. */
          q31_t A2;            /**< The derived gain, A2 = Kd . */
          q31_t state[3];      /**< The state array of length 3. */
          q31_t Kp;            /**< The proportional gain. */
          q31_t Ki;            /**< The integral gain. */
          q31_t Kd;            /**< The derivative gain. */
  } arm_pid_instance_q31;

  /**
   * @brief Instance structure for the floating-point PID Control.
   */
  typedef struct
  {
          float32_t A0;          /**< The derived gain, A0 = Kp + Ki + Kd . */
          float32_t A1;          /**< The derived gain, A1 = -Kp - 2Kd. */
          float32_t A2;          /**< The derived gain, A2 = Kd . */
          float32_t state[3];    /**< The state array of length 3. */
          float32_t Kp;          /**< The proportional gain. */
          float32_t Ki;          /**< The integral gain. */
          float32_t Kd;          /**< The derivative gain. */
  } arm_pid_instance_f32;



  /**
   * @brief  Initialization function for the floating-point PID Control.
   * @param[in,out] S               points to an instance of the PID structure.
   * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
   */
  void arm_pid_init_f32(
        arm_pid_instance_f32 * S,
        int32_t resetStateFlag);


  /**
   * @brief  Reset function for the floating-point PID Control.
   * @param[in,out] S  is an instance of the floating-point PID Control structure
   */
  void arm_pid_reset_f32(
        arm_pid_instance_f32 * S);


  /**
   * @brief  Initialization function for the Q31 PID Control.
   * @param[in,out] S               points to an instance of the Q15 PID structure.
   * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
   */
  void arm_pid_init_q31(
        arm_pid_instance_q31 * S,
        int32_t resetStateFlag);


  /**
   * @brief  Reset function for the Q31 PID Control.
   * @param[in,out] S   points to an instance of the Q31 PID Control structure
   */

  void arm_pid_reset_q31(
        arm_pid_instance_q31 * S);


  /**
   * @brief  Initialization function for the Q15 PID Control.
   * @param[in,out] S               points to an instance of the Q15 PID structure.
   * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
   */
  void arm_pid_init_q15(
        arm_pid_instance_q15 * S,
        int32_t resetStateFlag);


  /**
   * @brief  Reset function for the Q15 PID Control.
   * @param[in,out] S  points to an instance of the q15 PID Control structure
   */
  void arm_pid_reset_q15(
        arm_pid_instance_q15 * S);



  /**
   * @addtogroup PID
   * @{
   */

  /**
   * @brief         Process function for the floating-point PID Control.
   * @param[in,out] S   is an instance of the floating-point PID Control structure
   * @param[in]     in  input sample to process
   * @return        processed output sample.
   */
  __STATIC_FORCEINLINE float32_t arm_pid_f32(
  arm_pid_instance_f32 * S,
  float32_t in)
  {
    float32_t out;

    /* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
    out = (S->A0 * in) +
      (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);

    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);

  }

/**
  @brief         Process function for the Q31 PID Control.
  @param[in,out] S  points to an instance of the Q31 PID Control structure
  @param[in]     in  input sample to process
  @return        processed output sample.

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 64-bit accumulator.
         The accumulator has a 2.62 format and maintains full precision of the intermediate multiplication results but provides only a single guard bit.
         Thus, if the accumulator result overflows it wraps around rather than clip.
         In order to avoid overflows completely the input signal must be scaled down by 2 bits as there are four additions.
         After all multiply-accumulates are performed, the 2.62 accumulator is truncated to 1.32 format and then saturated to 1.31 format.
 */
__STATIC_FORCEINLINE q31_t arm_pid_q31(
  arm_pid_instance_q31 * S,
  q31_t in)
  {
    q63_t acc;
    q31_t out;

    /* acc = A0 * x[n]  */
    acc = (q63_t) S->A0 * in;

    /* acc += A1 * x[n-1] */
    acc += (q63_t) S->A1 * S->state[0];

    /* acc += A2 * x[n-2]  */
    acc += (q63_t) S->A2 * S->state[1];

    /* convert output to 1.31 format to add y[n-1] */
    out = (q31_t) (acc >> 31U);

    /* out += y[n-1] */
    out += S->state[2];

    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);
  }


/**
  @brief         Process function for the Q15 PID Control.
  @param[in,out] S   points to an instance of the Q15 PID Control structure
  @param[in]     in  input sample to process
  @return        processed output sample.

  \par Scaling and Overflow Behavior
         The function is implemented using a 64-bit internal accumulator.
         Both Gains and state variables are represented in 1.15 format and multiplications yield a 2.30 result.
         The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.
         There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.
         After all additions have been performed, the accumulator is truncated to 34.15 format by discarding low 15 bits.
         Lastly, the accumulator is saturated to yield a result in 1.15 format.
 */
__STATIC_FORCEINLINE q15_t arm_pid_q15(
  arm_pid_instance_q15 * S,
  q15_t in)
  {
    q63_t acc;
    q15_t out;

#if defined (ARM_MATH_DSP)
    /* Implementation of PID controller */

    /* acc = A0 * x[n]  */
    acc = (q31_t) __SMUAD((uint32_t)S->A0, (uint32_t)in);

    /* acc += A1 * x[n-1] + A2 * x[n-2]  */
    acc = (q63_t)__SMLALD((uint32_t)S->A1, (uint32_t)read_q15x2 (S->state), (uint64_t)acc);
#else
    /* acc = A0 * x[n]  */
    acc = ((q31_t) S->A0) * in;

    /* acc += A1 * x[n-1] + A2 * x[n-2]  */
    acc += (q31_t) S->A1 * S->state[0];
    acc += (q31_t) S->A2 * S->state[1];
#endif

    /* acc += y[n-1] */
    acc += (q31_t) S->state[2] << 15;

    /* saturate the output */
    out = (q15_t) (__SSAT((q31_t)(acc >> 15), 16));

    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);
  }

  /**
   * @} end of PID group
   */

  /**
   * @ingroup groupController
   */

  /**
   * @defgroup park Vector Park Transform
   *
   * Forward Park transform converts the input two-coordinate vector to flux and torque components.
   * The Park transform can be used to realize the transformation of the <code>Ialpha</code> and the <code>Ibeta</code> currents
   * from the stationary to the moving reference frame and control the spatial relationship between
   * the stator vector current and rotor flux vector.
   * If we consider the d axis aligned with the rotor flux, the diagram below shows the
   * current vector and the relationship from the two reference frames:
   * \image html park.gif "Stator current space vector and its component in (a,b) and in the d,q rotating reference frame"
   *
   * The function operates on a single sample of data and each call to the function returns the processed output.
   * The library provides separate functions for Q31 and floating-point data types.
   * \par Algorithm
   * \image html parkFormula.gif
   * where <code>Ialpha</code> and <code>Ibeta</code> are the stator vector components,
   * <code>pId</code> and <code>pIq</code> are rotor vector components and <code>cosVal</code> and <code>sinVal</code> are the
   * cosine and sine values of theta (rotor flux position).
   * \par Fixed-Point Behavior
   * Care must be taken when using the Q31 version of the Park transform.
   * In particular, the overflow and saturation behavior of the accumulator used must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */

  /**
   * @addtogroup park
   * @{
   */

  /**
   * @brief Floating-point Park transform
   * @param[in]  Ialpha  input two-phase vector coordinate alpha
   * @param[in]  Ibeta   input two-phase vector coordinate beta
   * @param[out] pId     points to output   rotor reference frame d
   * @param[out] pIq     points to output   rotor reference frame q
   * @param[in]  sinVal  sine value of rotation angle theta
   * @param[in]  cosVal  cosine value of rotation angle theta
   * @return     none
   *
   * The function implements the forward Park transform.
   *
   */
  __STATIC_FORCEINLINE void arm_park_f32(
  float32_t Ialpha,
  float32_t Ibeta,
  float32_t * pId,
  float32_t * pIq,
  float32_t sinVal,
  float32_t cosVal)
  {
    /* Calculate pId using the equation, pId = Ialpha * cosVal + Ibeta * sinVal */
    *pId = Ialpha * cosVal + Ibeta * sinVal;

    /* Calculate pIq using the equation, pIq = - Ialpha * sinVal + Ibeta * cosVal */
    *pIq = -Ialpha * sinVal + Ibeta * cosVal;
  }


/**
  @brief  Park transform for Q31 version
  @param[in]  Ialpha  input two-phase vector coordinate alpha
  @param[in]  Ibeta   input two-phase vector coordinate beta
  @param[out] pId     points to output rotor reference frame d
  @param[out] pIq     points to output rotor reference frame q
  @param[in]  sinVal  sine value of rotation angle theta
  @param[in]  cosVal  cosine value of rotation angle theta
  @return     none

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the addition and subtraction, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void arm_park_q31(
  q31_t Ialpha,
  q31_t Ibeta,
  q31_t * pId,
  q31_t * pIq,
  q31_t sinVal,
  q31_t cosVal)
  {
    q31_t product1, product2;                    /* Temporary variables used to store intermediate results */
    q31_t product3, product4;                    /* Temporary variables used to store intermediate results */

    /* Intermediate product is calculated by (Ialpha * cosVal) */
    product1 = (q31_t) (((q63_t) (Ialpha) * (cosVal)) >> 31);

    /* Intermediate product is calculated by (Ibeta * sinVal) */
    product2 = (q31_t) (((q63_t) (Ibeta) * (sinVal)) >> 31);


    /* Intermediate product is calculated by (Ialpha * sinVal) */
    product3 = (q31_t) (((q63_t) (Ialpha) * (sinVal)) >> 31);

    /* Intermediate product is calculated by (Ibeta * cosVal) */
    product4 = (q31_t) (((q63_t) (Ibeta) * (cosVal)) >> 31);

    /* Calculate pId by adding the two intermediate products 1 and 2 */
    *pId = __QADD(product1, product2);

    /* Calculate pIq by subtracting the two intermediate products 3 from 4 */
    *pIq = __QSUB(product4, product3);
  }

  /**
   * @} end of park group
   */


  /**
   * @ingroup groupController
   */

  /**
   * @defgroup inv_park Vector Inverse Park transform
   * Inverse Park transform converts the input flux and torque components to two-coordinate vector.
   *
   * The function operates on a single sample of data and each call to the function returns the processed output.
   * The library provides separate functions for Q31 and floating-point data types.
   * \par Algorithm
   * \image html parkInvFormula.gif
   * where <code>pIalpha</code> and <code>pIbeta</code> are the stator vector components,
   * <code>Id</code> and <code>Iq</code> are rotor vector components and <code>cosVal</code> and <code>sinVal</code> are the
   * cosine and sine values of theta (rotor flux position).
   * \par Fixed-Point Behavior
   * Care must be taken when using the Q31 version of the Park transform.
   * In particular, the overflow and saturation behavior of the accumulator used must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */

  /**
   * @addtogroup inv_park
   * @{
   */

   /**
   * @brief  Floating-point Inverse Park transform
   * @param[in]  Id       input coordinate of rotor reference frame d
   * @param[in]  Iq       input coordinate of rotor reference frame q
   * @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
   * @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
   * @param[in]  sinVal   sine value of rotation angle theta
   * @param[in]  cosVal   cosine value of rotation angle theta
   * @return     none
   */
  __STATIC_FORCEINLINE void arm_inv_park_f32(
  float32_t Id,
  float32_t Iq,
  float32_t * pIalpha,
  float32_t * pIbeta,
  float32_t sinVal,
  float32_t cosVal)
  {
    /* Calculate pIalpha using the equation, pIalpha = Id * cosVal - Iq * sinVal */
    *pIalpha = Id * cosVal - Iq * sinVal;

    /* Calculate pIbeta using the equation, pIbeta = Id * sinVal + Iq * cosVal */
    *pIbeta = Id * sinVal + Iq * cosVal;
  }


/**
  @brief  Inverse Park transform for   Q31 version
  @param[in]  Id       input coordinate of rotor reference frame d
  @param[in]  Iq       input coordinate of rotor reference frame q
  @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
  @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
  @param[in]  sinVal   sine value of rotation angle theta
  @param[in]  cosVal   cosine value of rotation angle theta
  @return     none

  @par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the addition, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void arm_inv_park_q31(
  q31_t Id,
  q31_t Iq,
  q31_t * pIalpha,
  q31_t * pIbeta,
  q31_t sinVal,
  q31_t cosVal)
  {
    q31_t product1, product2;                    /* Temporary variables used to store intermediate results */
    q31_t product3, product4;                    /* Temporary variables used to store intermediate results */

    /* Intermediate product is calculated by (Id * cosVal) */
    product1 = (q31_t) (((q63_t) (Id) * (cosVal)) >> 31);

    /* Intermediate product is calculated by (Iq * sinVal) */
    product2 = (q31_t) (((q63_t) (Iq) * (sinVal)) >> 31);


    /* Intermediate product is calculated by (Id * sinVal) */
    product3 = (q31_t) (((q63_t) (Id) * (sinVal)) >> 31);

    /* Intermediate product is calculated by (Iq * cosVal) */
    product4 = (q31_t) (((q63_t) (Iq) * (cosVal)) >> 31);

    /* Calculate pIalpha by using the two intermediate products 1 and 2 */
    *pIalpha = __QSUB(product1, product2);

    /* Calculate pIbeta by using the two intermediate products 3 and 4 */
    *pIbeta = __QADD(product4, product3);
  }

  /**
   * @} end of Inverse park group
   */

/**
   * @ingroup groupController
   */

  /**
   * @defgroup clarke Vector Clarke Transform
   * Forward Clarke transform converts the instantaneous stator phases into a two-coordinate time invariant vector.
   * Generally the Clarke transform uses three-phase currents <code>Ia, Ib and Ic</code> to calculate currents
   * in the two-phase orthogonal stator axis <code>Ialpha</code> and <code>Ibeta</code>.
   * When <code>Ialpha</code> is superposed with <code>Ia</code> as shown in the figure below
   * \image html clarke.gif Stator current space vector and its components in (a,b).
   * and <code>Ia + Ib + Ic = 0</code>, in this condition <code>Ialpha</code> and <code>Ibeta</code>
   * can be calculated using only <code>Ia</code> and <code>Ib</code>.
   *
   * The function operates on a single sample of data and each call to the function returns the processed output.
   * The library provides separate functions for Q31 and floating-point data types.
   * \par Algorithm
   * \image html clarkeFormula.gif
   * where <code>Ia</code> and <code>Ib</code> are the instantaneous stator phases and
   * <code>pIalpha</code> and <code>pIbeta</code> are the two coordinates of time invariant vector.
   * \par Fixed-Point Behavior
   * Care must be taken when using the Q31 version of the Clarke transform.
   * In particular, the overflow and saturation behavior of the accumulator used must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */

  /**
   * @addtogroup clarke
   * @{
   */

  /**
   *
   * @brief  Floating-point Clarke transform
   * @param[in]  Ia       input three-phase coordinate <code>a</code>
   * @param[in]  Ib       input three-phase coordinate <code>b</code>
   * @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
   * @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
   * @return        none
   */
  __STATIC_FORCEINLINE void arm_clarke_f32(
  float32_t Ia,
  float32_t Ib,
  float32_t * pIalpha,
  float32_t * pIbeta)
  {
    /* Calculate pIalpha using the equation, pIalpha = Ia */
    *pIalpha = Ia;

    /* Calculate pIbeta using the equation, pIbeta = (1/sqrt(3)) * Ia + (2/sqrt(3)) * Ib */
    *pIbeta = (0.57735026919f * Ia + 1.15470053838f * Ib);
  }


/**
  @brief  Clarke transform for Q31 version
  @param[in]  Ia       input three-phase coordinate <code>a</code>
  @param[in]  Ib       input three-phase coordinate <code>b</code>
  @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
  @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
  @return     none

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the addition, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void arm_clarke_q31(
  q31_t Ia,
  q31_t Ib,
  q31_t * pIalpha,
  q31_t * pIbeta)
  {
    q31_t product1, product2;                    /* Temporary variables used to store intermediate results */

    /* Calculating pIalpha from Ia by equation pIalpha = Ia */
    *pIalpha = Ia;

    /* Intermediate product is calculated by (1/(sqrt(3)) * Ia) */
    product1 = (q31_t) (((q63_t) Ia * 0x24F34E8B) >> 30);

    /* Intermediate product is calculated by (2/sqrt(3) * Ib) */
    product2 = (q31_t) (((q63_t) Ib * 0x49E69D16) >> 30);

    /* pIbeta is calculated by adding the intermediate products */
    *pIbeta = __QADD(product1, product2);
  }

  /**
   * @} end of clarke group
   */


  /**
   * @ingroup groupController
   */

  /**
   * @defgroup inv_clarke Vector Inverse Clarke Transform
   * Inverse Clarke transform converts the two-coordinate time invariant vector into instantaneous stator phases.
   *
   * The function operates on a single sample of data and each call to the function returns the processed output.
   * The library provides separate functions for Q31 and floating-point data types.
   * \par Algorithm
   * \image html clarkeInvFormula.gif
   * where <code>pIa</code> and <code>pIb</code> are the instantaneous stator phases and
   * <code>Ialpha</code> and <code>Ibeta</code> are the two coordinates of time invariant vector.
   * \par Fixed-Point Behavior
   * Care must be taken when using the Q31 version of the Clarke transform.
   * In particular, the overflow and saturation behavior of the accumulator used must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */

  /**
   * @addtogroup inv_clarke
   * @{
   */

   /**
   * @brief  Floating-point Inverse Clarke transform
   * @param[in]  Ialpha  input two-phase orthogonal vector axis alpha
   * @param[in]  Ibeta   input two-phase orthogonal vector axis beta
   * @param[out] pIa     points to output three-phase coordinate <code>a</code>
   * @param[out] pIb     points to output three-phase coordinate <code>b</code>
   * @return     none
   */
  __STATIC_FORCEINLINE void arm_inv_clarke_f32(
  float32_t Ialpha,
  float32_t Ibeta,
  float32_t * pIa,
  float32_t * pIb)
  {
    /* Calculating pIa from Ialpha by equation pIa = Ialpha */
    *pIa = Ialpha;

    /* Calculating pIb from Ialpha and Ibeta by equation pIb = -(1/2) * Ialpha + (sqrt(3)/2) * Ibeta */
    *pIb = -0.5f * Ialpha + 0.8660254039f * Ibeta;
  }


/**
  @brief  Inverse Clarke transform for Q31 version
  @param[in]  Ialpha  input two-phase orthogonal vector axis alpha
  @param[in]  Ibeta   input two-phase orthogonal vector axis beta
  @param[out] pIa     points to output three-phase coordinate <code>a</code>
  @param[out] pIb     points to output three-phase coordinate <code>b</code>
  @return     none

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the subtraction, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void arm_inv_clarke_q31(
  q31_t Ialpha,
  q31_t Ibeta,
  q31_t * pIa,
  q31_t * pIb)
  {
    q31_t product1, product2;                    /* Temporary variables used to store intermediate results */

    /* Calculating pIa from Ialpha by equation pIa = Ialpha */
    *pIa = Ialpha;

    /* Intermediate product is calculated by (1/(2*sqrt(3)) * Ia) */
    product1 = (q31_t) (((q63_t) (Ialpha) * (0x40000000)) >> 31);

    /* Intermediate product is calculated by (1/sqrt(3) * pIb) */
    product2 = (q31_t) (((q63_t) (Ibeta) * (0x6ED9EBA1)) >> 31);

    /* pIb is calculated by subtracting the products */
    *pIb = __QSUB(product2, product1);
  }

  /**
   * @} end of inv_clarke group
   */



  
#ifdef   __cplusplus
}
#endif

#endif /* ifndef _CONTROLLER_FUNCTIONS_H_ */
