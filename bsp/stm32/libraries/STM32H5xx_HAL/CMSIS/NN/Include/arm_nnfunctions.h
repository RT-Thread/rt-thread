/*
 * Copyright (C) 2010-2022 Arm Limited or its affiliates.
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

/* ----------------------------------------------------------------------
 * Project:      CMSIS NN Library
 * Title:        arm_nnfunctions.h
 * Description:  Public header file for CMSIS NN Library
 *
 * $Date:        19 April 2022
 * $Revision:    V.9.0.0
 *
 * Target Processor:  Cortex-M CPUs
 * -------------------------------------------------------------------- */

/**
   \mainpage CMSIS NN Software Library
   *
   * Introduction
   * ------------
   *
   * This user manual describes the CMSIS NN software library,
   * a collection of efficient neural network kernels developed to maximize the
   * performance and minimize the memory footprint of neural networks on Cortex-M processor cores.
   *
   * The library is divided into a number of functions each covering a specific category:
   * - Convolution Functions
   * - Activation Functions
   * - Fully-connected Layer Functions
   * - SVDF Layer Functions
   * - Pooling Functions
   * - Softmax Functions
   * - Basic math Functions
   *
   * The library has separate functions for operating on different weight and activation data
   * types including 8-bit integers (q7_t) and 16-bit integers (q15_t). The descrition of the
   * kernels are included in the function description. The implementation details are also
   * described in this paper [1].
   *
   * Supported Processors
   * -------
   * CMSIS-NN targets Cortex-M processors with typically three different implementations for each function. Each
   * targets a different group of processors.
   *  - Processors without SIMD capability (e.g, Cortex-M0)
   *  - Processors with DSP extention (e.g Cortex-M4)
   *  - Processors with MVE extension (e.g Cortex-M55)
   * The right implementation is picked through feature flags and the user usually does not have to explicit set it.
   *
   * Function Classification
   * --------
   * The functions can be classified into two segments
   * - Legacy functions supporting ARM's internal symmetric quantization(8 bits).
   * - Functions that support TensorFlow Lite framework with symmetric quantization(8 bits).
   *
   * The legacy functions can be identified with their suffix of _q7 or _q15 and are no new development is done there.
   * The article in [2] describes in detail how to run a network using the legacy functions.
   *
   * The functions supporting TensorFlow Lite framework is identified by the _s8 suffix and can be invoked from TFL
   * micro. The functions are bit exact to TensorFlow Lite. Refer to the TensorFlow's documentation in [3] on how to run
   * a TensorFlow Lite model using optimized CMSIS-NN kernels.
   *
   * Block Diagram
   * --------
   * \image html CMSIS-NN-OVERVIEW.PNG
   *
   * Examples
   * --------
   *
   * The library ships with a number of examples which demonstrate how to use the library functions.
   *
   * Pre-processor Macros
   * ------------
   *
   * Each library project have different pre-processor macros.
   *
   * - ARM_MATH_DSP:
   *
   * Define macro ARM_MATH_DSP, If the silicon supports DSP instructions(DSP extension).
   *
   * - ARM_MATH_MVEI:
   *
   * Define macro ARM_MATH_MVEI, If the silicon supports M-Profile Vector Extension.

   * - ARM_MATH_AUTOVECTORIZE
   *  Used in conjucture with ARM_MATH_MVEI to let the compiler auto vectorize for the functions that uses inline
   *  assembly. It does not affect functions that use C or intrinsics.
   * - ARM_MATH_BIG_ENDIAN:
   *
   * Define macro ARM_MATH_BIG_ENDIAN to build the library for big endian targets. This is supported only for the legacy
   * functions i.e, functions targetted at TensorFlow Lite do not support big endianness. By default library builds for
   * little endian targets.
   *
   * - ARM_NN_TRUNCATE:
   *
   * Define macro ARM_NN_TRUNCATE to use floor instead of round-to-the-nearest-int for the computation.
   *
   *
   * Copyright Notice
   * ------------
   *
   * Copyright (C) 2010-2019 Arm Limited. All rights reserved.
   *
   * [1] CMSIS-NN: Efficient Neural Network Kernels for Arm Cortex-M CPUs https://arxiv.org/abs/1801.06601
   *
   * [2] Converting a Neural Network for Arm Cortex-M with CMSIS-NN
   *
   https://developer.arm.com/solutions/machine-learning-on-arm/developer-material/how-to-guides/converting-a-neural-network-for-arm-cortex-m-with-cmsis-nn/single-page
   * [3] https://www.tensorflow.org/lite/microcontrollers/library
   *
   * [4] https://github.com/ARM-software/CMSIS_5/tree/develop/CMSIS/NN#legacy-vs-tfl-micro-compliant-apis
   */

/**
 * @defgroup groupNN Neural Network Functions
 * A collection of functions to perform basic operations for neural network layers. Functions with a _s8 suffix support
 * TensorFlow Lite framework.
 */

#ifndef _ARM_NNFUNCTIONS_H
#define _ARM_NNFUNCTIONS_H

#include "arm_nn_math_types.h"
#include "arm_nn_types.h"

#define USE_INTRINSIC

//#define ARM_NN_TRUNCATE /* This config the rounding model to floor or round to the nearest int */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Struct for specifying activation function types
 *
 */
typedef enum
{
    ARM_SIGMOID = 0,
    /**< Sigmoid activation function */
    ARM_TANH = 1,
    /**< Tanh activation function */
} arm_nn_activation_type;

/**
 * @defgroup NNConv Convolution Functions
 *
 * Collection of convolution, depthwise convolution functions and their variants.
 *
 * The convolution is implemented in 2 steps: im2col and GEMM
 *
 * im2col is a process of converting each patch of image data into
 * a column. After im2col, the convolution is computed as matrix-matrix
 * multiplication.
 *
 * To reduce the memory footprint, the im2col is performed partially.
 * Each iteration, only a few column (i.e., patches) are generated and
 * computed with GEMM kernels similar to CMSIS-DSP arm_mat_mult functions.
 *
 */

/**
 * @brief s8 convolution layer wrapper function with the main purpose to call the optimal kernel available in
 cmsis-nn
 *        to perform the convolution.
 *
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
                                  arm_convolve_wrapper_s8_get_buffer_size will return the buffer_size if required
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                Range of conv_params->input_offset  : [-127, 128]
 *                                Range of conv_params->output_offset : [-128, 127]
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the
 *                                spatial filter dimensions
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Bias data pointer. Data type: int32
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int8
 *
 * @return     The function returns either
 *                  <code>ARM_MATH_SIZE_MISMATCH</code> if argument constraints fail. or,
 *                  <code>ARM_MATH_SUCCESS</code> on successful completion.
 *
 */
arm_status arm_convolve_wrapper_s8(const cmsis_nn_context *ctx,
                                   const cmsis_nn_conv_params *conv_params,
                                   const cmsis_nn_per_channel_quant_params *quant_params,
                                   const cmsis_nn_dims *input_dims,
                                   const q7_t *input_data,
                                   const cmsis_nn_dims *filter_dims,
                                   const q7_t *filter_data,
                                   const cmsis_nn_dims *bias_dims,
                                   const int32_t *bias_data,
                                   const cmsis_nn_dims *output_dims,
                                   q7_t *output_data);

/**
 * @brief Get the required buffer size for arm_convolve_wrapper_s8
 *
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                Range of conv_params->input_offset  : [-127, 128]
 *                                Range of conv_params->output_offset : [-128, 127]
 * @param[in]      input_dims     Input (activation) dimensions. Format: [N, H, W, C_IN]
 * @param[in]      filter_dims    Filter dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the spatial
 *                                filter dimensions
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 *
 * @return         The function returns  required buffer size(bytes)
 *
 */
int32_t arm_convolve_wrapper_s8_get_buffer_size(const cmsis_nn_conv_params *conv_params,
                                                const cmsis_nn_dims *input_dims,
                                                const cmsis_nn_dims *filter_dims,
                                                const cmsis_nn_dims *output_dims);

/**
 * @brief s16 convolution layer wrapper function with the main purpose to call the optimal kernel available in
 cmsis-nn
 *        to perform the convolution.
 *
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
                                  arm_convolve_wrapper_s8_get_buffer_size will return the buffer_size if required
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                conv_params->input_offset  : Not used
 *                                conv_params->output_offset : Not used
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the
 *                                spatial filter dimensions
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Bias data pointer. Data type: int64
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int16
 *
 * @return     The function returns either
 *                  <code>ARM_MATH_SIZE_MISMATCH</code> if argument constraints fail. or,
 *                  <code>ARM_MATH_SUCCESS</code> on successful completion.
 *
 */
arm_status arm_convolve_wrapper_s16(const cmsis_nn_context *ctx,
                                    const cmsis_nn_conv_params *conv_params,
                                    const cmsis_nn_per_channel_quant_params *quant_params,
                                    const cmsis_nn_dims *input_dims,
                                    const q15_t *input_data,
                                    const cmsis_nn_dims *filter_dims,
                                    const q7_t *filter_data,
                                    const cmsis_nn_dims *bias_dims,
                                    const int64_t *bias_data,
                                    const cmsis_nn_dims *output_dims,
                                    q15_t *output_data);

/**
 * @brief Get the required buffer size for arm_convolve_wrapper_s16
 *
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                conv_params->input_offset  : Not used
 *                                conv_params->output_offset : Not used
 * @param[in]      input_dims     Input (activation) dimensions. Format: [N, H, W, C_IN]
 * @param[in]      filter_dims    Filter dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the spatial
 *                                filter dimensions
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 *
 * @return         The function returns  required buffer size(bytes)
 *
 */
int32_t arm_convolve_wrapper_s16_get_buffer_size(const cmsis_nn_conv_params *conv_params,
                                                 const cmsis_nn_dims *input_dims,
                                                 const cmsis_nn_dims *filter_dims,
                                                 const cmsis_nn_dims *output_dims);

/**
 * @brief Basic s8 convolution function
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
                                  arm_convolve_s8_get_buffer_size will return the buffer_size if required
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                Range of conv_params->input_offset  : [-127, 128]
 *                                Range of conv_params->output_offset : [-128, 127]
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the
 *                                spatial filter dimensions
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Optional bias data pointer. Data type: int32
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int8

 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 *    2. q7 is used as data type eventhough it is s8 data. It is done so to be consistent with existing APIs.
 *    3. Additional memory is required for optimization. Refer to argument 'ctx' for details.
 *
 */
arm_status arm_convolve_s8(const cmsis_nn_context *ctx,
                           const cmsis_nn_conv_params *conv_params,
                           const cmsis_nn_per_channel_quant_params *quant_params,
                           const cmsis_nn_dims *input_dims,
                           const q7_t *input_data,
                           const cmsis_nn_dims *filter_dims,
                           const q7_t *filter_data,
                           const cmsis_nn_dims *bias_dims,
                           const int32_t *bias_data,
                           const cmsis_nn_dims *output_dims,
                           q7_t *output_data);

/**
 * @brief Get the required buffer size for s8 convolution function
 *
 * @param[in]       input_dims            Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]       filter_dims           Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK
 * are the spatial filter dimensions
 * @return          The function returns  required buffer size(bytes)
 *
 */
int32_t arm_convolve_s8_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @brief Basic s16 convolution function
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
                                  arm_convolve_s16_get_buffer_size will return the buffer_size if required
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                conv_params->input_offset  : Not used
 *                                conv_params->output_offset : Not used
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the
 *                                spatial filter dimensions
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Optional bias data pointer. Data type: int64
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int16

 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 *    2. q7/q15 is used as data type eventhough it is s8/s16 data. It is done so to be consistent with existing APIs.
 *    3. Additional memory is required for optimization. Refer to argument 'ctx' for details.
 *
 */
arm_status arm_convolve_s16(const cmsis_nn_context *ctx,
                            const cmsis_nn_conv_params *conv_params,
                            const cmsis_nn_per_channel_quant_params *quant_params,
                            const cmsis_nn_dims *input_dims,
                            const q15_t *input_data,
                            const cmsis_nn_dims *filter_dims,
                            const q7_t *filter_data,
                            const cmsis_nn_dims *bias_dims,
                            const int64_t *bias_data,
                            const cmsis_nn_dims *output_dims,
                            q15_t *output_data);
/**
 * @brief Optimized s16 convolution function
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
                                  arm_convolve_fast_s16_get_buffer_size will return the buffer_size if required
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                conv_params->input_offset  : Not used
 *                                conv_params->output_offset : Not used
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK are the
 *                                spatial filter dimensions. (filter_dims->w * filter_dims->h * input_dims->c) must not
 exceed 512
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Optional bias data pointer. Data type: int64
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int16

 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 *    2. q7/q15 is used as data type eventhough it is s8/s16 data. It is done so to be consistent with existing APIs.
 *    3. Additional memory is required for optimization. Refer to argument 'ctx' for details.
 *    4. Implementation supports kernel volumes (filter width * filter height * input channels) < 512.
 *
 */

arm_status arm_convolve_fast_s16(const cmsis_nn_context *ctx,
                                 const cmsis_nn_conv_params *conv_params,
                                 const cmsis_nn_per_channel_quant_params *quant_params,
                                 const cmsis_nn_dims *input_dims,
                                 const q15_t *input_data,
                                 const cmsis_nn_dims *filter_dims,
                                 const q7_t *filter_data,
                                 const cmsis_nn_dims *bias_dims,
                                 const int64_t *bias_data,
                                 const cmsis_nn_dims *output_dims,
                                 q15_t *output_data);

/**
 * @brief Get the required buffer size for s16 convolution function
 *
 * @param[in]       input_dims            Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]       filter_dims           Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK
 * are the spatial filter dimensions
 * @return          The function returns  required buffer size(bytes)
 *
 */
int32_t arm_convolve_s16_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @brief Get the required buffer size for fast s16 convolution function
 *
 * @param[in]       input_dims            Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]       filter_dims           Filter tensor dimensions. Format: [C_OUT, HK, WK, C_IN] where HK and WK
 * are the spatial filter dimensions
 * @return          The function returns required buffer size(bytes)
 *
 */
int32_t arm_convolve_fast_s16_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @brief Basic Q7 convolution function
 * @param[in]       Im_in       pointer to input tensor
 * @param[in]       dim_im_in   input tensor dimension
 * @param[in]       ch_im_in    number of input tensor channels
 * @param[in]       wt          pointer to kernel weights
 * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel  filter kernel size
 * @param[in]       padding     padding sizes
 * @param[in]       stride      convolution stride
 * @param[in]       bias        pointer to bias
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in,out]   Im_out      pointer to output tensor
 * @param[in]       dim_im_out  output tensor dimension
 * @param[in,out]   bufferA     pointer to buffer space for input
 * @param[in,out]   bufferB     pointer to buffer space for output
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 */
arm_status arm_convolve_HWC_q7_basic(const q7_t *Im_in,
                                     const uint16_t dim_im_in,
                                     const uint16_t ch_im_in,
                                     const q7_t *wt,
                                     const uint16_t ch_im_out,
                                     const uint16_t dim_kernel,
                                     const uint16_t padding,
                                     const uint16_t stride,
                                     const q7_t *bias,
                                     const uint16_t bias_shift,
                                     const uint16_t out_shift,
                                     q7_t *Im_out,
                                     const uint16_t dim_im_out,
                                     q15_t *bufferA,
                                     q7_t *bufferB);

/**
 * @brief Basic Q7 convolution function (non-square shape)
 * @param[in]       Im_in        pointer to input tensor
 * @param[in]       dim_im_in_x  input tensor dimension x
 * @param[in]       dim_im_in_y  input tensor dimension y
 * @param[in]       ch_im_in     number of input tensor channels
 * @param[in]       wt           pointer to kernel weights
 * @param[in]       ch_im_out    number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel_x filter kernel size x
 * @param[in]       dim_kernel_y filter kernel size y
 * @param[in]       padding_x    padding size x
 * @param[in]       padding_y    padding size y
 * @param[in]       stride_x     convolution stride x
 * @param[in]       stride_y     convolution stride y
 * @param[in]       bias         pointer to bias
 * @param[in]       bias_shift   amount of left-shift for bias
 * @param[in]       out_shift    amount of right-shift for output
 * @param[in,out]   Im_out       pointer to output tensor
 * @param[in]       dim_im_out_x output tensor dimension x
 * @param[in]       dim_im_out_y output tensor dimension y
 * @param[in,out]   bufferA      pointer to buffer space for input
 * @param[in,out]   bufferB      pointer to buffer space for output
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 */
arm_status arm_convolve_HWC_q7_basic_nonsquare(const q7_t *Im_in,
                                               const uint16_t dim_im_in_x,
                                               const uint16_t dim_im_in_y,
                                               const uint16_t ch_im_in,
                                               const q7_t *wt,
                                               const uint16_t ch_im_out,
                                               const uint16_t dim_kernel_x,
                                               const uint16_t dim_kernel_y,
                                               const uint16_t padding_x,
                                               const uint16_t padding_y,
                                               const uint16_t stride_x,
                                               const uint16_t stride_y,
                                               const q7_t *bias,
                                               const uint16_t bias_shift,
                                               const uint16_t out_shift,
                                               q7_t *Im_out,
                                               const uint16_t dim_im_out_x,
                                               const uint16_t dim_im_out_y,
                                               q15_t *bufferA,
                                               q7_t *bufferB);

/**
 * @brief Basic Q15 convolution function
 * @param[in]       Im_in       pointer to input tensor
 * @param[in]       dim_im_in   input tensor dimension
 * @param[in]       ch_im_in    number of input tensor channels
 * @param[in]       wt          pointer to kernel weights
 * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel  filter kernel size
 * @param[in]       padding     padding sizes
 * @param[in]       stride      convolution stride
 * @param[in]       bias        pointer to bias
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in,out]   Im_out      pointer to output tensor
 * @param[in]       dim_im_out  output tensor dimension
 * @param[in,out]   bufferA     pointer to buffer space for input
 * @param[in,out]   bufferB     pointer to buffer space for output
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 */
arm_status arm_convolve_HWC_q15_basic(const q15_t *Im_in,
                                      const uint16_t dim_im_in,
                                      const uint16_t ch_im_in,
                                      const q15_t *wt,
                                      const uint16_t ch_im_out,
                                      const uint16_t dim_kernel,
                                      const uint16_t padding,
                                      const uint16_t stride,
                                      const q15_t *bias,
                                      const uint16_t bias_shift,
                                      const uint16_t out_shift,
                                      q15_t *Im_out,
                                      const uint16_t dim_im_out,
                                      q15_t *bufferA,
                                      q7_t *bufferB);

/**
 * @brief Fast Q7 convolution function
 * @param[in]       Im_in       pointer to input tensor
 * @param[in]       dim_im_in   input tensor dimension
 * @param[in]       ch_im_in    number of input tensor channels
 * @param[in]       wt          pointer to kernel weights
 * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel  filter kernel size
 * @param[in]       padding     padding sizes
 * @param[in]       stride      convolution stride
 * @param[in]       bias        pointer to bias
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in,out]   Im_out      pointer to output tensor
 * @param[in]       dim_im_out  output tensor dimension
 * @param[in,out]   bufferA     pointer to buffer space for input
 * @param[in,out]   bufferB     pointer to buffer space for output
 * @return     The function returns either
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
 *
 * This function is the version with full list of optimization tricks, but with
 * some contraints:
 *   ch_im_in is multiple of 4
 *   ch_im_out is multiple of 2
 */
arm_status arm_convolve_HWC_q7_fast(const q7_t *Im_in,
                                    const uint16_t dim_im_in,
                                    const uint16_t ch_im_in,
                                    const q7_t *wt,
                                    const uint16_t ch_im_out,
                                    const uint16_t dim_kernel,
                                    const uint16_t padding,
                                    const uint16_t stride,
                                    const q7_t *bias,
                                    const uint16_t bias_shift,
                                    const uint16_t out_shift,
                                    q7_t *Im_out,
                                    const uint16_t dim_im_out,
                                    q15_t *bufferA,
                                    q7_t *bufferB);

/**
 * @brief Fast Q7 convolution function (non-sqaure shape)
 * @param[in]       Im_in        pointer to input tensor
 * @param[in]       dim_im_in_x  input tensor dimension x
 * @param[in]       dim_im_in_y  input tensor dimension y
 * @param[in]       ch_im_in     number of input tensor channels
 * @param[in]       wt           pointer to kernel weights
 * @param[in]       ch_im_out    number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel_x filter kernel size x
 * @param[in]       dim_kernel_y filter kernel size y
 * @param[in]       padding_x    padding size x
 * @param[in]       padding_y    padding size y
 * @param[in]       stride_x     convolution stride x
 * @param[in]       stride_y     convolution stride y
 * @param[in]       bias         pointer to bias
 * @param[in]       bias_shift   amount of left-shift for bias
 * @param[in]       out_shift    amount of right-shift for output
 * @param[in,out]   Im_out       pointer to output tensor
 * @param[in]       dim_im_out_x output tensor dimension x
 * @param[in]       dim_im_out_y output tensor dimension y
 * @param[in,out]   bufferA      pointer to buffer space for input
 * @param[in,out]   bufferB      pointer to buffer space for output
 * @return     The function returns either
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
 *
 * This function is the version with full list of optimization tricks, but with
 * some contraints:
 *   ch_im_in is multiple of 4
 *   ch_im_out is multiple of 2
 */

arm_status arm_convolve_HWC_q7_fast_nonsquare(const q7_t *Im_in,
                                              const uint16_t dim_im_in_x,
                                              const uint16_t dim_im_in_y,
                                              const uint16_t ch_im_in,
                                              const q7_t *wt,
                                              const uint16_t ch_im_out,
                                              const uint16_t dim_kernel_x,
                                              const uint16_t dim_kernel_y,
                                              const uint16_t padding_x,
                                              const uint16_t padding_y,
                                              const uint16_t stride_x,
                                              const uint16_t stride_y,
                                              const q7_t *bias,
                                              const uint16_t bias_shift,
                                              const uint16_t out_shift,
                                              q7_t *Im_out,
                                              const uint16_t dim_im_out_x,
                                              const uint16_t dim_im_out_y,
                                              q15_t *bufferA,
                                              q7_t *bufferB);

/**
 * @brief Fast Q7 version of 1x1 convolution (non-sqaure shape)
 * @param[in]       Im_in        pointer to input tensor
 * @param[in]       dim_im_in_x  input tensor dimension x
 * @param[in]       dim_im_in_y  input tensor dimension y
 * @param[in]       ch_im_in     number of input tensor channels
 * @param[in]       wt           pointer to kernel weights
 * @param[in]       ch_im_out    number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel_x filter kernel size x
 * @param[in]       dim_kernel_y filter kernel size y
 * @param[in]       padding_x    padding size x
 * @param[in]       padding_y    padding size y
 * @param[in]       stride_x     convolution stride x
 * @param[in]       stride_y     convolution stride y
 * @param[in]       bias         pointer to bias
 * @param[in]       bias_shift   amount of left-shift for bias
 * @param[in]       out_shift    amount of right-shift for output
 * @param[in,out]   Im_out       pointer to output tensor
 * @param[in]       dim_im_out_x output tensor dimension x
 * @param[in]       dim_im_out_y output tensor dimension y
 * @param[in,out]   bufferA      pointer to buffer space for input
 * @param[in,out]   bufferB      pointer to buffer space for output
 * @return     The function returns either
 *                          <code>ARM_MATH_SIZE_MISMATCH</code> if argument constraints fail. or,
 *                          <code>ARM_MATH_SUCCESS</code> on successful completion.
 *
 * This function implement convolution with 1x1 kernel size (i.e., dim_kernel_x=1
 * and dim_kernel_y=1). It can be used for
 * second half of MobileNets after depthwise separable convolution.
 *
 * This function is the version with full list of optimization tricks, but with
 * some contraints:
 *   ch_im_in is multiple of 4
 *   ch_im_out is multiple of 2
 */
arm_status arm_convolve_1x1_HWC_q7_fast_nonsquare(const q7_t *Im_in,
                                                  const uint16_t dim_im_in_x,
                                                  const uint16_t dim_im_in_y,
                                                  const uint16_t ch_im_in,
                                                  const q7_t *wt,
                                                  const uint16_t ch_im_out,
                                                  const uint16_t dim_kernel_x,
                                                  const uint16_t dim_kernel_y,
                                                  const uint16_t padding_x,
                                                  const uint16_t padding_y,
                                                  const uint16_t stride_x,
                                                  const uint16_t stride_y,
                                                  const q7_t *bias,
                                                  const uint16_t bias_shift,
                                                  const uint16_t out_shift,
                                                  q7_t *Im_out,
                                                  const uint16_t dim_im_out_x,
                                                  const uint16_t dim_im_out_y,
                                                  q15_t *bufferA,
                                                  q7_t *bufferB);

/**
 * @brief Fast s8 version for 1x1 convolution (non-square shape)
 *
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
                                  arm_convolve_1x1_s8_fast_get_buffer_size will return the buffer_size if required
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                Range of conv_params->input_offset  : [-127, 128]
 *                                Range of conv_params->output_offset : [-128, 127]
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, 1, 1, C_IN]
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Optional bias data pointer. Data type: int32
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int8
 *
 * @return     The function returns either
 *                  <code>ARM_MATH_SIZE_MISMATCH</code> if argument constraints fail. or,
 *                  <code>ARM_MATH_SUCCESS</code> on successful completion.
 *
 * @details
 *   - Supported framework : TensorFlow Lite Micro
 *   - The following constrains on the arguments apply
 *      -# input_dims->c is a multiple of 4
 *      -# conv_params->padding.w = conv_params->padding.h = 0
 *      -# conv_params->stride.w = conv_params->stride.h = 1
 *
 */
arm_status arm_convolve_1x1_s8_fast(const cmsis_nn_context *ctx,
                                    const cmsis_nn_conv_params *conv_params,
                                    const cmsis_nn_per_channel_quant_params *quant_params,
                                    const cmsis_nn_dims *input_dims,
                                    const q7_t *input_data,
                                    const cmsis_nn_dims *filter_dims,
                                    const q7_t *filter_data,
                                    const cmsis_nn_dims *bias_dims,
                                    const int32_t *bias_data,
                                    const cmsis_nn_dims *output_dims,
                                    q7_t *output_data);

/**
 * @brief Get the required buffer size for arm_convolve_1x1_s8_fast
 *
 * @param[in]       input_dims            Input (activation) dimensions
 * @return          The function returns the required buffer size in bytes
 *
 */
int32_t arm_convolve_1x1_s8_fast_get_buffer_size(const cmsis_nn_dims *input_dims);

/**
 * @brief 1xn convolution
 *
 * @param[in, out] ctx            Function context that contains the additional buffer if required by the function.
                                  arm_convolve_1_x_n_s8_get_buffer_size will return the buffer_size if required
 * @param[in]      conv_params    Convolution parameters (e.g. strides, dilations, pads,...).
 *                                Range of conv_params->input_offset  : [-127, 128]
 *                                Range of conv_params->output_offset : [-128, 127]
 * @param[in]      quant_params   Per-channel quantization info.
 *                                It contains the multiplier and shift values to be applied to each output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]      input_data     Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [C_OUT, 1, WK, C_IN] where WK is the horizontal
 *                                spatial filter dimension
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Optional bias data pointer. Data type: int32
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[out]     output_data    Output data pointer. Data type: int8
 *
 * @return     The function returns either
 *                  <code>ARM_MATH_SIZE_MISMATCH</code> if argument constraints fail. or,
 *                  <code>ARM_MATH_SUCCESS</code> on successful completion.
 *
 * @details
 *   - Supported framework : TensorFlow Lite Micro
 *   - The following constrains on the arguments apply
 *      -# input_dims->n equals 1
 *      -# ouput_dims->w is a multiple of 4
 *      -# Explicit constraints(since it is for 1xN convolution)
 *      -## input_dims->h equals 1
 *      -## output_dims->h equals 1
 *      -## filter_dims->h equals 1
 *@todo  Remove constraint on output_dims->w to make the function generic.
 *
 */
arm_status arm_convolve_1_x_n_s8(const cmsis_nn_context *ctx,
                                 const cmsis_nn_conv_params *conv_params,
                                 const cmsis_nn_per_channel_quant_params *quant_params,
                                 const cmsis_nn_dims *input_dims,
                                 const q7_t *input_data,
                                 const cmsis_nn_dims *filter_dims,
                                 const q7_t *filter_data,
                                 const cmsis_nn_dims *bias_dims,
                                 const int32_t *bias_data,
                                 const cmsis_nn_dims *output_dims,
                                 q7_t *output_data);

/**
 * @brief Get the required additional buffer size for 1xn convolution
 *
 * @param[in]       input_dims            Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 * @param[in]       filter_dims           Filter tensor dimensions. Format: [C_OUT, 1, WK, C_IN] where WK is the
 *                                        horizontal spatial filter dimension
 * @return          The function returns  required buffer size(bytes)
 *
 */
int32_t arm_convolve_1_x_n_s8_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @brief Q7 version of convolution for RGB image
 * @param[in]       Im_in       pointer to input tensor
 * @param[in]       dim_im_in   input tensor dimension
 * @param[in]       ch_im_in    number of input tensor channels
 * @param[in]       wt          pointer to kernel weights
 * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel  filter kernel size
 * @param[in]       padding     padding sizes
 * @param[in]       stride      convolution stride
 * @param[in]       bias        pointer to bias
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in,out]   Im_out      pointer to output tensor
 * @param[in]       dim_im_out  output tensor dimension
 * @param[in,out]   bufferA     pointer to buffer space for input
 * @param[in,out]   bufferB     pointer to buffer space for output
 * @return     The function returns either
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
 *
 * This kernel is written exclusively for convolution with ch_im_in
 * equals 3. This applies on the first layer of CNNs which has input
 * image with RGB format.
 */

arm_status arm_convolve_HWC_q7_RGB(const q7_t *Im_in,
                                   const uint16_t dim_im_in,
                                   const uint16_t ch_im_in,
                                   const q7_t *wt,
                                   const uint16_t ch_im_out,
                                   const uint16_t dim_kernel,
                                   const uint16_t padding,
                                   const uint16_t stride,
                                   const q7_t *bias,
                                   const uint16_t bias_shift,
                                   const uint16_t out_shift,
                                   q7_t *Im_out,
                                   const uint16_t dim_im_out,
                                   q15_t *bufferA,
                                   q7_t *bufferB);

/**
 * @brief Fast Q15 convolution function
 * @param[in]       Im_in       pointer to input tensor
 * @param[in]       dim_im_in   input tensor dimension
 * @param[in]       ch_im_in    number of input tensor channels
 * @param[in]       wt          pointer to kernel weights
 * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel  filter kernel size
 * @param[in]       padding     padding sizes
 * @param[in]       stride      convolution stride
 * @param[in]       bias        pointer to bias
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in,out]   Im_out      pointer to output tensor
 * @param[in]       dim_im_out  output tensor dimension
 * @param[in,out]   bufferA     pointer to buffer space for input
 * @param[in,out]   bufferB     pointer to buffer space for output
 * @return     The function returns either
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
 *
 * This function is the version with full list of optimization tricks, but with
 * some contraints:
 *   ch_im_in is multiple of 2
 *   ch_im_out is multiple of 2
 *   dim_im_out is a multiple of 2
 */

arm_status arm_convolve_HWC_q15_fast(const q15_t *Im_in,
                                     const uint16_t dim_im_in,
                                     const uint16_t ch_im_in,
                                     const q15_t *wt,
                                     const uint16_t ch_im_out,
                                     const uint16_t dim_kernel,
                                     const uint16_t padding,
                                     const uint16_t stride,
                                     const q15_t *bias,
                                     const uint16_t bias_shift,
                                     const uint16_t out_shift,
                                     q15_t *Im_out,
                                     const uint16_t dim_im_out,
                                     q15_t *bufferA,
                                     q7_t *bufferB);

/**
 * @brief Fast Q15 convolution function (non-sqaure shape)
 * @param[in]       Im_in        pointer to input tensor
 * @param[in]       dim_im_in_x  input tensor dimension x
 * @param[in]       dim_im_in_y  input tensor dimension y
 * @param[in]       ch_im_in     number of input tensor channels
 * @param[in]       wt           pointer to kernel weights
 * @param[in]       ch_im_out    number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel_x filter kernel size x
 * @param[in]       dim_kernel_y filter kernel size y
 * @param[in]       padding_x    padding size x
 * @param[in]       padding_y    padding size y
 * @param[in]       stride_x     convolution stride x
 * @param[in]       stride_y     convolution stride y
 * @param[in]       bias         pointer to bias
 * @param[in]       bias_shift   amount of left-shift for bias
 * @param[in]       out_shift    amount of right-shift for output
 * @param[in,out]   Im_out       pointer to output tensor
 * @param[in]       dim_im_out_x output tensor dimension x
 * @param[in]       dim_im_out_y output tensor dimension y
 * @param[in,out]   bufferA      pointer to buffer space for input
 * @param[in,out]   bufferB      pointer to buffer space for output
 * @return     The function returns either
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
 *
 * @details
 *
 * <b>Buffer size:</b>
 *
 * bufferA size: 2*ch_im_in*dim_kernel*dim_kernel
 *
 * bufferB size: 0
 *
 * <b>Input dimension constraints:</b>
 *
 * ch_im_in is multiple of 2
 *
 * ch_im_out is multipe of 2
 *
 */

arm_status arm_convolve_HWC_q15_fast_nonsquare(const q15_t *Im_in,
                                               const uint16_t dim_im_in_x,
                                               const uint16_t dim_im_in_y,
                                               const uint16_t ch_im_in,
                                               const q15_t *wt,
                                               const uint16_t ch_im_out,
                                               const uint16_t dim_kernel_x,
                                               const uint16_t dim_kernel_y,
                                               const uint16_t padding_x,
                                               const uint16_t padding_y,
                                               const uint16_t stride_x,
                                               const uint16_t stride_y,
                                               const q15_t *bias,
                                               const uint16_t bias_shift,
                                               const uint16_t out_shift,
                                               q15_t *Im_out,
                                               const uint16_t dim_im_out_x,
                                               const uint16_t dim_im_out_y,
                                               q15_t *bufferA,
                                               q7_t *bufferB);

/**
 * @brief Q7 depthwise separable convolution function
 * @param[in]       Im_in       pointer to input tensor
 * @param[in]       dim_im_in   input tensor dimension
 * @param[in]       ch_im_in    number of input tensor channels
 * @param[in]       wt          pointer to kernel weights
 * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel  filter kernel size
 * @param[in]       padding     padding sizes
 * @param[in]       stride      convolution stride
 * @param[in]       bias        pointer to bias
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in,out]   Im_out      pointer to output tensor
 * @param[in]       dim_im_out  output tensor dimension
 * @param[in,out]   bufferA     pointer to buffer space for input
 * @param[in,out]   bufferB     pointer to buffer space for output
 * @return     The function returns either
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
 *
 * This function is the version with full list of optimization tricks, but with
 * some contraints:
 *   ch_im_in is multiple of 2
 *   ch_im_out is multiple of 2
 */

arm_status arm_depthwise_separable_conv_HWC_q7(const q7_t *Im_in,
                                               const uint16_t dim_im_in,
                                               const uint16_t ch_im_in,
                                               const q7_t *wt,
                                               const uint16_t ch_im_out,
                                               const uint16_t dim_kernel,
                                               const uint16_t padding,
                                               const uint16_t stride,
                                               const q7_t *bias,
                                               const uint16_t bias_shift,
                                               const uint16_t out_shift,
                                               q7_t *Im_out,
                                               const uint16_t dim_im_out,
                                               q15_t *bufferA,
                                               q7_t *bufferB);

/**
 * @brief Q7 depthwise separable convolution function (non-square shape)
 * @param[in]       Im_in         pointer to input tensor
 * @param[in]       dim_im_in_x   input tensor dimension x
 * @param[in]       dim_im_in_y   input tensor dimension y
 * @param[in]       ch_im_in      number of input tensor channels
 * @param[in]       wt            pointer to kernel weights
 * @param[in]       ch_im_out     number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel_x  filter kernel size x
 * @param[in]       dim_kernel_y  filter kernel size y
 * @param[in]       padding_x     padding sizes x
 * @param[in]       padding_y     padding sizes y
 * @param[in]       stride_x      convolution stride x
 * @param[in]       stride_y      convolution stride y
 * @param[in]       bias          pointer to bias
 * @param[in]       bias_shift    amount of left-shift for bias
 * @param[in]       out_shift     amount of right-shift for output
 * @param[in,out]   Im_out        pointer to output tensor
 * @param[in]       dim_im_out_x  output tensor dimension x
 * @param[in]       dim_im_out_y  output tensor dimension y
 * @param[in,out]   bufferA       pointer to buffer space for input
 * @param[in,out]   bufferB       pointer to buffer space for output
 * @return     The function returns either
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
 *
 * This function is the version with full list of optimization tricks, but with
 * some contraints:
 *   ch_im_in is multiple of 2
 *   ch_im_out is multiple of 2
 */
arm_status arm_depthwise_separable_conv_HWC_q7_nonsquare(const q7_t *Im_in,
                                                         const uint16_t dim_im_in_x,
                                                         const uint16_t dim_im_in_y,
                                                         const uint16_t ch_im_in,
                                                         const q7_t *wt,
                                                         const uint16_t ch_im_out,
                                                         const uint16_t dim_kernel_x,
                                                         const uint16_t dim_kernel_y,
                                                         const uint16_t padding_x,
                                                         const uint16_t padding_y,
                                                         const uint16_t stride_x,
                                                         const uint16_t stride_y,
                                                         const q7_t *bias,
                                                         const uint16_t bias_shift,
                                                         const uint16_t out_shift,
                                                         q7_t *Im_out,
                                                         const uint16_t dim_im_out_x,
                                                         const uint16_t dim_im_out_y,
                                                         q15_t *bufferA,
                                                         q7_t *bufferB);

/**
 * @brief Wrapper function to pick the right optimized s8 depthwise convolution function
 *
 * @param[in, out] ctx            Function context (e.g. temporary buffer). Check the function
 *                                definition file to see if an additional buffer is required.
 *                                Optional function {API}_get_buffer_size() provides the buffer
 *                                size if required.
 * @param[in]      dw_conv_params Depthwise convolution parameters (e.g. strides, dilations, pads,...)
 *                                dw_conv_params->dilation is not used.
 *                                Range of dw_conv_params->input_offset : [-127, 128]
 *                                Range of dw_conv_params->output_offset : [-128, 127]
 * @param[in]      quant_params   Per-channel quantization info.
 *                               It contains the multiplier and shift values to be applied to each
 *                               output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                                Batch argument N is not used and assumed to be 1.
 * @param[in]      input_data     Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Bias data pointer. Data type: int32
 * @param[in]      output_dims    Output tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in, out] output_data    Output data pointer. Data type: int8
 * @return     The function returns
 *                <code>ARM_MATH_SUCCESS</code>   -  Successful completion.
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 *    - Picks one of the the following functions
 *        -# arm_depthwise_conv_s8()
 *        -# arm_depthwise_conv_3x3_s8() - Cortex-M CPUs with DSP extension only
 *        -# arm_depthwise_conv_s8_opt()
 *    - q7 is used as data type eventhough it is s8 data. It is done so to be consistent with existing APIs.
 *    - Check details of arm_depthwise_conv_s8_opt() for potential data that can be accessed outside of the
 * boundary.
 */
arm_status arm_depthwise_conv_wrapper_s8(const cmsis_nn_context *ctx,
                                         const cmsis_nn_dw_conv_params *dw_conv_params,
                                         const cmsis_nn_per_channel_quant_params *quant_params,
                                         const cmsis_nn_dims *input_dims,
                                         const q7_t *input_data,
                                         const cmsis_nn_dims *filter_dims,
                                         const q7_t *filter_data,
                                         const cmsis_nn_dims *bias_dims,
                                         const int32_t *bias_data,
                                         const cmsis_nn_dims *output_dims,
                                         q7_t *output_data);

/**
 * @brief Get size of additional buffer required by arm_depthwise_conv_wrapper_s8()
 *
 * @param[in]      dw_conv_params Depthwise convolution parameters (e.g. strides, dilations, pads,...)
 *                                dw_conv_params->dilation is not used.
 *                                Range of dw_conv_params->input_offset : [-127, 128]
 *                                Range of dw_conv_params->input_offset : [-128, 127]
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                                Batch argument N is not used and assumed to be 1.
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in]      output_dims    Output tensor dimensions. Format: [1, H, W, C_OUT]
 * @return                        Size of additional memory required for optimizations in bytes.
 *
 */
int32_t arm_depthwise_conv_wrapper_s8_get_buffer_size(const cmsis_nn_dw_conv_params *dw_conv_params,
                                                      const cmsis_nn_dims *input_dims,
                                                      const cmsis_nn_dims *filter_dims,
                                                      const cmsis_nn_dims *output_dims);

/**
 * @brief Basic s8 depthwise convolution function that doesn't have any constraints on the input dimensions.
 *
 * @param[in, out] ctx            Function context (e.g. temporary buffer). Check the function
 *                                definition file to see if an additional buffer is required.
 *                                Optional function {API}_get_buffer_size() provides the buffer
 *                                size if an additional buffer is required.
 *                                exists if additional memory is.
 * @param[in]      dw_conv_params Depthwise convolution parameters (e.g. strides, dilations, pads,...)
 *                                dw_conv_params->dilation is not used.
 *                                Range of dw_conv_params->input_offset : [-127, 128]
 *                                Range of dw_conv_params->input_offset : [-128, 127]
 * @param[in]      quant_params   Per-channel quantization info.
 *                               It contains the multiplier and shift values to be applied to each
 *                               output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 *                                Batch argument N is not used.
 * @param[in]      input_data     Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Bias data pointer. Data type: int32
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[in, out] output_data    Output data pointer. Data type: int8
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 *    - q7 is used as data type eventhough it is s8 data. It is done so to be consistent with existing APIs.
 */
arm_status arm_depthwise_conv_s8(const cmsis_nn_context *ctx,
                                 const cmsis_nn_dw_conv_params *dw_conv_params,
                                 const cmsis_nn_per_channel_quant_params *quant_params,
                                 const cmsis_nn_dims *input_dims,
                                 const q7_t *input_data,
                                 const cmsis_nn_dims *filter_dims,
                                 const q7_t *filter_data,
                                 const cmsis_nn_dims *bias_dims,
                                 const int32_t *bias_data,
                                 const cmsis_nn_dims *output_dims,
                                 q7_t *output_data);

/**
 * @brief Basic s16 depthwise convolution function that doesn't have any constraints on the input dimensions.
 *
 * @param[in, out] ctx            Function context (e.g. temporary buffer). Check the function
 *                                definition file to see if an additional buffer is required.
 *                                Optional function {API}_get_buffer_size() provides the buffer
 *                                size if an additional buffer is required.
 *                                exists if additional memory is.
 * @param[in]      dw_conv_params Depthwise convolution parameters (e.g. strides, dilations, pads,...)
 *                                conv_params->input_offset  : Not used
 *                                conv_params->output_offset : Not used
 * @param[in]      quant_params   Per-channel quantization info.
 *                               It contains the multiplier and shift values to be applied to each
 *                               output channel
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 *                                Batch argument N is not used.
 * @param[in]      input_data     Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 * @param[in]      bias_data      Bias data pointer. Data type: int64
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, H, W, C_OUT]
 * @param[in, out] output_data    Output data pointer. Data type: int16
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 *    - q15 is used as data type eventhough it is s16 data. It is done so to be consistent with existing APIs.
 */
arm_status arm_depthwise_conv_s16(const cmsis_nn_context *ctx,
                                  const cmsis_nn_dw_conv_params *dw_conv_params,
                                  const cmsis_nn_per_channel_quant_params *quant_params,
                                  const cmsis_nn_dims *input_dims,
                                  const q15_t *input_data,
                                  const cmsis_nn_dims *filter_dims,
                                  const q7_t *filter_data,
                                  const cmsis_nn_dims *bias_dims,
                                  const int64_t *bias_data,
                                  const cmsis_nn_dims *output_dims,
                                  q15_t *output_data);

/**
 * @brief Optimized s8 depthwise convolution function for 3x3 kernel size with some constraints on
 *        the input arguments(documented below). Refer arm_depthwise_conv_s8() for function
 *        argument details.
 *
 * @return     The function returns one of the following
 *                <code>ARM_MATH_SIZE_MISMATCH</code> - Unsupported dimension of tensors
 *                <code>ARM_MATH_ARGUMENT_ERROR</code> - Unsupported pad size along the x axis
 *                <code>ARM_MATH_SUCCESS</code> - Successful operation
 *
 * @details
 *   - Supported framework : TensorFlow Lite Micro
 *   - The following constrains on the arguments apply
 *      -# Number of input channel equals number of output channels
 *      -# Filter height and width equals 3
 *      -# Padding along x is either 0 or 1.
 *
 */
arm_status arm_depthwise_conv_3x3_s8(const cmsis_nn_context *ctx,
                                     const cmsis_nn_dw_conv_params *dw_conv_params,
                                     const cmsis_nn_per_channel_quant_params *quant_params,
                                     const cmsis_nn_dims *input_dims,
                                     const q7_t *input_data,
                                     const cmsis_nn_dims *filter_dims,
                                     const q7_t *filter_data,
                                     const cmsis_nn_dims *bias_dims,
                                     const int32_t *bias_data,
                                     const cmsis_nn_dims *output_dims,
                                     q7_t *output_data);

/**
 * @brief Optimized s8 depthwise convolution function with constraint that in_channel equals out_channel.
 *        Refer arm_depthwise_conv_s8() for function argument details.
 *
 * @return     The function returns one of the following
 *                <code>ARM_MATH_SIZE_MISMATCH</code> - input channel != output channel or
 *                                                      ch_mult != 1
 *                <code>ARM_MATH_SUCCESS</code> - Successful operation
 *
 * @note       If number of channels is not a multiple of 4, upto 3 elements outside the boundary will be read out
 *             for the following if MVE optimizations(Arm Helium Technology) are used.
 *               - Output shift
 *               - Output multiplier
 *               - Output bias
 *               - kernel
 * @details
 *    - Supported framework: TensorFlow Lite
 *    - The following constrains on the arguments apply
 *        -# Number of input channel equals number of output channels or ch_mult equals 1
 *    - q7 is used as data type eventhough it is s8 data. It is done so to be consistent with existing APIs.
 *    - Reccomended when number of channels is 4 or greater.
 *
 */
arm_status arm_depthwise_conv_s8_opt(const cmsis_nn_context *ctx,
                                     const cmsis_nn_dw_conv_params *dw_conv_params,
                                     const cmsis_nn_per_channel_quant_params *quant_params,
                                     const cmsis_nn_dims *input_dims,
                                     const q7_t *input_data,
                                     const cmsis_nn_dims *filter_dims,
                                     const q7_t *filter_data,
                                     const cmsis_nn_dims *bias_dims,
                                     const int32_t *bias_data,
                                     const cmsis_nn_dims *output_dims,
                                     q7_t *output_data);

/**
 * @brief Get the required buffer size for optimized s8 depthwise convolution
 * function with constraint that in_channel equals out_channel.
 * @param[in]       input_dims     Input (activation) tensor dimensions. Format: [1, H, W, C_IN]
 *                                 Batch argument N is not used.
 * @param[in]       filter_dims    Filter tensor dimensions. Format: [1, H, W, C_OUT]
 * @return          The function returns  required buffer size in bytes
 *
 */
int32_t arm_depthwise_conv_s8_opt_get_buffer_size(const cmsis_nn_dims *input_dims, const cmsis_nn_dims *filter_dims);

/**
 * @defgroup FC Fully-connected Layer Functions
 *
 * Collection of fully-connected and matrix multiplication functions.
 *
 * Fully-connected layer is basically a matrix-vector multiplication
 * with bias. The matrix is the weights and the input/output vectors
 * are the activation values. Supported {weight, activation} precisions
 * include {8-bit, 8-bit}, {16-bit, 16-bit}, and {8-bit, 16-bit}.
 *
 * Here we have two types of kernel functions. The basic function
 * implements the function using regular GEMV approach. The opt functions
 * operates with weights in interleaved formats.
 *
 */

/**
 *@brief Q7 basic fully-connected layer function
 *@param[in]       pV          pointer to input vector
 *@param[in]       pM          pointer to matrix weights
 *@param[in]       dim_vec     length of the vector
 *@param[in]       num_of_rows number of rows in weight matrix
 *@param[in]       bias_shift  amount of left-shift for bias
 *@param[in]       out_shift   amount of right-shift for output
 *@param[in]       bias        pointer to bias
 *@param[in,out]   pOut        pointer to output vector
 *@param[in,out]   vec_buffer  pointer to buffer space for input
 *@return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 */

arm_status arm_fully_connected_q7(const q7_t *pV,
                                  const q7_t *pM,
                                  const uint16_t dim_vec,
                                  const uint16_t num_of_rows,
                                  const uint16_t bias_shift,
                                  const uint16_t out_shift,
                                  const q7_t *bias,
                                  q7_t *pOut,
                                  q15_t *vec_buffer);

/**
 * @brief Basic s8 Fully Connected function.
 *
 * @param[in, out] ctx            Function context (e.g. temporary buffer). Check the function
 *                                definition file to see if an additional buffer is required.
 *                                Optional function {API}_get_buffer_size() provides the buffer
 *                                size if an additional buffer is required.
 * @param[in]      fc_params      Fully Connected layer parameters.
 *                                Range of fc_params->input_offset  : [-127, 128]
 *                                fc_params->filter_offset : 0
 *                                Range of fc_params->output_offset : [-128, 127]
 * @param[in]      quant_params   Per-tensor quantization info.
 *                                It contains the multiplier and shift values to be applied to the output tensor.
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 *                                Input dimension is taken as Nx(H * W * C_IN)
 * @param[in]      input_data     Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims    Two dimensional filter dimensions. Format: [N, C]
 *                                N : accumulation depth and equals (H * W * C_IN) from input_dims
 *                                C : output depth and equals C_OUT in output_dims
 *                                H & W : Not used
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 *                                N, H, W : Not used
 * @param[in]      bias_data      Bias data pointer. Data type: int32
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, C_OUT]
 *                                N : Batches
 *                                C_OUT : Output depth
 *                                H & W : Not used.
 * @param[in, out] output_data    Output data pointer. Data type: int8
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 *    - q7 is used as data type eventhough it is s8 data. It is done so to be consistent with existing APIs.
 */
arm_status arm_fully_connected_s8(const cmsis_nn_context *ctx,
                                  const cmsis_nn_fc_params *fc_params,
                                  const cmsis_nn_per_tensor_quant_params *quant_params,
                                  const cmsis_nn_dims *input_dims,
                                  const q7_t *input_data,
                                  const cmsis_nn_dims *filter_dims,
                                  const q7_t *filter_data,
                                  const cmsis_nn_dims *bias_dims,
                                  const int32_t *bias_data,
                                  const cmsis_nn_dims *output_dims,
                                  q7_t *output_data);

/**
 * @brief Get the required buffer size for S8 basic fully-connected and
 * matrix multiplication layer function for TF Lite
 * @param[in]      filter_dims             dimension of filter
 * @return         The function returns    required buffer size in bytes
 *
 */
int32_t arm_fully_connected_s8_get_buffer_size(const cmsis_nn_dims *filter_dims);

/**
 * @brief Basic s16 Fully Connected function.
 *
 * @param[in, out] ctx            Function context (e.g. temporary buffer). Check the function
 *                                definition file to see if an additional buffer is required.
 *                                Optional function {API}_get_buffer_size() provides the buffer
 *                                size if an additional buffer is required.
 * @param[in]      fc_params      Fully Connected layer parameters.
 *                                fc_params->input_offset  : 0
 *                                fc_params->filter_offset : 0
 *                                fc_params->output_offset : 0
 * @param[in]      quant_params   Per-tensor quantization info.
 *                                It contains the multiplier and shift values to be applied to the output tensor.
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [N, H, W, C_IN]
 *                                Input dimension is taken as Nx(H * W * C_IN)
 * @param[in]      input_data     Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims    Two dimensional filter dimensions. Format: [N, C]
 *                                N : accumulation depth and equals (H * W * C_IN) from input_dims
 *                                C : output depth and equals C_OUT in output_dims
 *                                H & W : Not used
 * @param[in]      filter_data    Filter data pointer. Data type: int8
 * @param[in]      bias_dims      Bias tensor dimensions. Format: [C_OUT]
 *                                N, H, W : Not used
 * @param[in]      bias_data      Bias data pointer. Data type: int64
 * @param[in]      output_dims    Output tensor dimensions. Format: [N, C_OUT]
 *                                N : Batches
 *                                C_OUT : Output depth
 *                                H & W : Not used.
 * @param[in, out] output_data    Output data pointer. Data type: int16
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 * @details
 *    - Supported framework: TensorFlow Lite
 *    - q15 is used as data type eventhough it is s16 data. It is done so to be consistent with existing APIs.
 */
arm_status arm_fully_connected_s16(const cmsis_nn_context *ctx,
                                   const cmsis_nn_fc_params *fc_params,
                                   const cmsis_nn_per_tensor_quant_params *quant_params,
                                   const cmsis_nn_dims *input_dims,
                                   const q15_t *input_data,
                                   const cmsis_nn_dims *filter_dims,
                                   const q7_t *filter_data,
                                   const cmsis_nn_dims *bias_dims,
                                   const int64_t *bias_data,
                                   const cmsis_nn_dims *output_dims,
                                   q15_t *output_data);

/**
 * @brief Get the required buffer size for S16 basic fully-connected and
 * matrix multiplication layer function for TF Lite
 * @param[in]      filter_dims             dimension of filter
 * @return         The function returns    required buffer size in bytes
 *
 */
int32_t arm_fully_connected_s16_get_buffer_size(const cmsis_nn_dims *filter_dims);

/**
 * @brief Q7 opt fully-connected layer function
 * @param[in]       pV          pointer to input vector
 * @param[in]       pM          pointer to matrix weights
 * @param[in]       dim_vec     length of the vector
 * @param[in]       num_of_rows number of rows in weight matrix
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in]       bias        pointer to bias
 * @param[in,out]   pOut        pointer to output vector
 * @param[in,out]   vec_buffer  pointer to buffer space for input
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 */

arm_status arm_fully_connected_q7_opt(const q7_t *pV,
                                      const q7_t *pM,
                                      const uint16_t dim_vec,
                                      const uint16_t num_of_rows,
                                      const uint16_t bias_shift,
                                      const uint16_t out_shift,
                                      const q7_t *bias,
                                      q7_t *pOut,
                                      q15_t *vec_buffer);

/**
 * @brief Q15 basic fully-connected layer function
 * @param[in]       pV          pointer to input vector
 * @param[in]       pM          pointer to matrix weights
 * @param[in]       dim_vec     length of the vector
 * @param[in]       num_of_rows number of rows in weight matrix
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in]       bias        pointer to bias
 * @param[in,out]   pOut        pointer to output vector
 * @param[in,out]   vec_buffer  pointer to buffer space for input
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 */

arm_status arm_fully_connected_q15(const q15_t *pV,
                                   const q15_t *pM,
                                   const uint16_t dim_vec,
                                   const uint16_t num_of_rows,
                                   const uint16_t bias_shift,
                                   const uint16_t out_shift,
                                   const q15_t *bias,
                                   q15_t *pOut,
                                   q15_t *vec_buffer);

/**
 * @brief Q15 opt fully-connected layer function
 * @param[in]       pV          pointer to input vector
 * @param[in]       pM          pointer to matrix weights
 * @param[in]       dim_vec     length of the vector
 * @param[in]       num_of_rows number of rows in weight matrix
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in]       bias        pointer to bias
 * @param[in,out]   pOut        pointer to output vector
 * @param[in,out]   vec_buffer  pointer to buffer space for input
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 */

arm_status arm_fully_connected_q15_opt(const q15_t *pV,
                                       const q15_t *pM,
                                       const uint16_t dim_vec,
                                       const uint16_t num_of_rows,
                                       const uint16_t bias_shift,
                                       const uint16_t out_shift,
                                       const q15_t *bias,
                                       q15_t *pOut,
                                       q15_t *vec_buffer);

/**
 * @brief Mixed Q15-Q7 fully-connected layer function
 * @param[in]       pV          pointer to input vector
 * @param[in]       pM          pointer to matrix weights
 * @param[in]       dim_vec     length of the vector
 * @param[in]       num_of_rows number of rows in weight matrix
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in]       bias        pointer to bias
 * @param[in,out]   pOut        pointer to output vector
 * @param[in,out]   vec_buffer  pointer to buffer space for input
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 */

arm_status arm_fully_connected_mat_q7_vec_q15(const q15_t *pV,
                                              const q7_t *pM,
                                              const uint16_t dim_vec,
                                              const uint16_t num_of_rows,
                                              const uint16_t bias_shift,
                                              const uint16_t out_shift,
                                              const q7_t *bias,
                                              q15_t *pOut,
                                              q15_t *vec_buffer);

/**
 * @brief Mixed Q15-Q7 opt fully-connected layer function
 * @param[in]       pV          pointer to input vector
 * @param[in]       pM          pointer to matrix weights
 * @param[in]       dim_vec     length of the vector
 * @param[in]       num_of_rows number of rows in weight matrix
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in]       bias        pointer to bias
 * @param[in,out]   pOut        pointer to output vector
 * @param[in,out]   vec_buffer  pointer to buffer space for input
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 */

arm_status arm_fully_connected_mat_q7_vec_q15_opt(const q15_t *pV,
                                                  const q7_t *pM,
                                                  const uint16_t dim_vec,
                                                  const uint16_t num_of_rows,
                                                  const uint16_t bias_shift,
                                                  const uint16_t out_shift,
                                                  const q7_t *bias,
                                                  q15_t *pOut,
                                                  q15_t *vec_buffer);

/**
 * @brief Matrix-Multiplication Kernels for Convolution
 *
 * These functions are used within convolution layer functions for
 * matrix multiplication.
 *
 * The implementation is similar to CMSIS-DSP arm_mat_mult functions
 * with one Q7 and one Q15 operands. The Q15 operand is the im2col
 * output which is always with 2 columns.
 *
 */

/**
 * @brief Matrix-multiplication function for convolution
 * @param[in]       pA          pointer to operand A
 * @param[in]       pInBuffer   pointer to operand B, always conssists of 2 vectors
 * @param[in]       ch_im_out   numRow of A
 * @param[in]       numCol_A    numCol of A
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in]       bias        the bias
 * @param[in,out]   pOut        pointer to output
 * @return     The function returns the incremented output pointer
 */

q7_t *arm_nn_mat_mult_kernel_q7_q15(const q7_t *pA,
                                    const q15_t *pInBuffer,
                                    const uint16_t ch_im_out,
                                    const uint16_t numCol_A,
                                    const uint16_t bias_shift,
                                    const uint16_t out_shift,
                                    const q7_t *bias,
                                    q7_t *pOut);

#ifdef __cplusplus
}
#endif

/*
 *  Other functions
 *  These layers are typically not timing critical
 *  Basic implementation is supported here
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup BasicMath Basic math functions
 *
 * Elementwise add and multiplication functions.
 *
 */

/**
 * @brief s8 elementwise add of two vectors
 * @param[in]       input_1_vect            pointer to input vector 1
 * @param[in]       input_2_vect            pointer to input vector 2
 * @param[in]       input_1_offset          offset for input 1. Range: -127 to 128
 * @param[in]       input_1_mult            multiplier for input 1
 * @param[in]       input_1_shift           shift for input 1
 * @param[in]       input_2_offset          offset for input 2. Range: -127 to 128
 * @param[in]       input_2_mult            multiplier for input 2
 * @param[in]       input_2_shift           shift for input 2
 * @param[in]       left_shift              input left shift
 * @param[in,out]   output                  pointer to output vector
 * @param[in]       out_offset              output offset.  Range: -128 to 127
 * @param[in]       out_mult                output multiplier
 * @param[in]       out_shift               output shift
 * @param[in]       out_activation_min      minimum value to clamp output to. Min: -128
 * @param[in]       out_activation_max      maximum value to clamp output to. Max: 127
 * @param[in]       block_size              number of samples
 * @return          The function returns    ARM_MATH_SUCCESS
 */
arm_status arm_elementwise_add_s8(const int8_t *input_1_vect,
                                  const int8_t *input_2_vect,
                                  const int32_t input_1_offset,
                                  const int32_t input_1_mult,
                                  const int32_t input_1_shift,
                                  const int32_t input_2_offset,
                                  const int32_t input_2_mult,
                                  const int32_t input_2_shift,
                                  const int32_t left_shift,
                                  int8_t *output,
                                  const int32_t out_offset,
                                  const int32_t out_mult,
                                  const int32_t out_shift,
                                  const int32_t out_activation_min,
                                  const int32_t out_activation_max,
                                  const int32_t block_size);

/**
 * @brief s16 elementwise add of two vectors
 * @param[in]       input_1_vect            pointer to input vector 1
 * @param[in]       input_2_vect            pointer to input vector 2
 * @param[in]       input_1_offset          offset for input 1. Not used.
 * @param[in]       input_1_mult            multiplier for input 1
 * @param[in]       input_1_shift           shift for input 1
 * @param[in]       input_2_offset          offset for input 2. Not used.
 * @param[in]       input_2_mult            multiplier for input 2
 * @param[in]       input_2_shift           shift for input 2
 * @param[in]       left_shift              input left shift
 * @param[in,out]   output                  pointer to output vector
 * @param[in]       out_offset              output offset. Not used.
 * @param[in]       out_mult                output multiplier
 * @param[in]       out_shift               output shift
 * @param[in]       out_activation_min      minimum value to clamp output to. Min: -32768
 * @param[in]       out_activation_max      maximum value to clamp output to. Max: 32767
 * @param[in]       block_size              number of samples
 * @return          The function returns    ARM_MATH_SUCCESS
 */
arm_status arm_elementwise_add_s16(const int16_t *input_1_vect,
                                   const int16_t *input_2_vect,
                                   const int32_t input_1_offset,
                                   const int32_t input_1_mult,
                                   const int32_t input_1_shift,
                                   const int32_t input_2_offset,
                                   const int32_t input_2_mult,
                                   const int32_t input_2_shift,
                                   const int32_t left_shift,
                                   int16_t *output,
                                   const int32_t out_offset,
                                   const int32_t out_mult,
                                   const int32_t out_shift,
                                   const int32_t out_activation_min,
                                   const int32_t out_activation_max,
                                   const int32_t block_size);

/**
 * @brief s8 elementwise multiplication
 * @param[in]       input_1_vect            pointer to input vector 1
 * @param[in]       input_2_vect            pointer to input vector 2
 * @param[in]       input_1_offset          offset for input 1. Range: -127 to 128
 * @param[in]       input_2_offset          offset for input 2. Range: -127 to 128
 * @param[in,out]   output                  pointer to output vector
 * @param[in]       out_offset              output offset. Range: -128 to 127
 * @param[in]       out_mult                output multiplier
 * @param[in]       out_shift               output shift
 * @param[in]       out_activation_min      minimum value to clamp output to. Min: -128
 * @param[in]       out_activation_max      maximum value to clamp output to. Max: 127
 * @param[in]       block_size              number of samples
 * @return          The function returns    ARM_MATH_SUCCESS
 *
 * @details   Supported framework: TensorFlow Lite micro
 */
arm_status arm_elementwise_mul_s8(const int8_t *input_1_vect,
                                  const int8_t *input_2_vect,
                                  const int32_t input_1_offset,
                                  const int32_t input_2_offset,
                                  int8_t *output,
                                  const int32_t out_offset,
                                  const int32_t out_mult,
                                  const int32_t out_shift,
                                  const int32_t out_activation_min,
                                  const int32_t out_activation_max,
                                  const int32_t block_size);

/**
 * @brief s16 elementwise multiplication
 * @param[in]       input_1_vect            pointer to input vector 1
 * @param[in]       input_2_vect            pointer to input vector 2
 * @param[in]       input_1_offset          offset for input 1. Not used.
 * @param[in]       input_2_offset          offset for input 2. Not used.
 * @param[in,out]   output                  pointer to output vector
 * @param[in]       out_offset              output offset. Not used.
 * @param[in]       out_mult                output multiplier
 * @param[in]       out_shift               output shift
 * @param[in]       out_activation_min      minimum value to clamp output to. Min: -32768
 * @param[in]       out_activation_max      maximum value to clamp output to. Max: 32767
 * @param[in]       block_size              number of samples
 * @return          The function returns    ARM_MATH_SUCCESS
 *
 * @details   Supported framework: TensorFlow Lite micro
 */
arm_status arm_elementwise_mul_s16(const int16_t *input_1_vect,
                                   const int16_t *input_2_vect,
                                   const int32_t input_1_offset,
                                   const int32_t input_2_offset,
                                   int16_t *output,
                                   const int32_t out_offset,
                                   const int32_t out_mult,
                                   const int32_t out_shift,
                                   const int32_t out_activation_min,
                                   const int32_t out_activation_max,
                                   const int32_t block_size);

/**
 * @defgroup Acti Activation Functions
 *
 * Perform activation layers, including ReLU (Rectified Linear Unit),
 * sigmoid and tanh
 *
 */

/**
 * @brief Q7 RELU function
 * @param[in,out]   data        pointer to input
 * @param[in]       size        number of elements
 * @return none.
 */

void arm_relu_q7(q7_t *data, uint16_t size);

/**
 * @brief s8 ReLU6 function
 * @param[in,out]   data        pointer to input
 * @param[in]       size        number of elements
 */

void arm_relu6_s8(q7_t *data, uint16_t size);

/**
 * @brief Q15 RELU function
 * @param[in,out]   data        pointer to input
 * @param[in]       size        number of elements
 * @return none.
 */

void arm_relu_q15(q15_t *data, uint16_t size);

/**
 * @brief Q7 neural network activation function using direct table look-up
 * @param[in,out]   data        pointer to input
 * @param[in]       size        number of elements
 * @param[in]       int_width   bit-width of the integer part, assume to be smaller than 3
 * @param[in]       type        type of activation functions
 * @return none.
 */

void arm_nn_activations_direct_q7(q7_t *data, uint16_t size, uint16_t int_width, arm_nn_activation_type type);

/**
 * @brief Q15 neural network activation function using direct table look-up
 * @param[in,out]   data        pointer to input
 * @param[in]       size        number of elements
 * @param[in]       int_width   bit-width of the integer part, assume to be smaller than 3
 * @param[in]       type        type of activation functions
 * @return none.
 *
 * @details
 *
 * This is the direct table look-up approach.
 *
 * Assume here the integer part of the fixed-point is <= 3.
 * More than 3 just not making much sense, makes no difference with
 * saturation followed by any of these activation functions.
 */

void arm_nn_activations_direct_q15(q15_t *data, uint16_t size, uint16_t int_width, arm_nn_activation_type type);

/**
 * @defgroup Pooling Pooling Functions
 *
 * Perform pooling functions, including max pooling and average pooling
 *
 */

/**
 * @brief Q7 max pooling function
 * @param[in]       Im_in       pointer to input tensor
 * @param[in]       dim_im_in   input tensor dimension
 * @param[in]       ch_im_in    number of input tensor channels
 * @param[in]       dim_kernel  filter kernel size
 * @param[in]       padding     padding sizes
 * @param[in]       stride      convolution stride
 * @param[in]       dim_im_out  output tensor dimension
 * @param[in,out]   bufferA     pointer to buffer space for input
 * @param[in,out]   Im_out      pointer to output tensor
 * @return none.
 *
 */

void arm_maxpool_q7_HWC(q7_t *Im_in,
                        const uint16_t dim_im_in,
                        const uint16_t ch_im_in,
                        const uint16_t dim_kernel,
                        const uint16_t padding,
                        const uint16_t stride,
                        const uint16_t dim_im_out,
                        q7_t *bufferA,
                        q7_t *Im_out);

/**
 * @brief Q7 average pooling function
 * @param[in]       Im_in       pointer to input tensor
 * @param[in]       dim_im_in   input tensor dimension
 * @param[in]       ch_im_in    number of input tensor channels
 * @param[in]       dim_kernel  filter kernel size
 * @param[in]       padding     padding sizes
 * @param[in]       stride      convolution stride
 * @param[in]       dim_im_out  output tensor dimension
 * @param[in,out]   bufferA     pointer to buffer space for input
 * @param[in,out]   Im_out      pointer to output tensor
 * @return none.
 *
 */

void arm_avepool_q7_HWC(q7_t *Im_in,
                        const uint16_t dim_im_in,
                        const uint16_t ch_im_in,
                        const uint16_t dim_kernel,
                        const uint16_t padding,
                        const uint16_t stride,
                        const uint16_t dim_im_out,
                        q7_t *bufferA,
                        q7_t *Im_out);

/**
 * @brief s8 average pooling function.
 *
 * @param[in, out] ctx            Function context (e.g. temporary buffer). Check the function
 *                                definition file to see if an additional buffer is required.
 *                                Optional function {API}_get_buffer_size() provides the buffer
 *                                size if an additional buffer is required.
 * @param[in]      pool_params    Pooling parameters
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                                Argument 'N' is not used.
 * @param[in]      input_data     Input (activation) data pointer. Data type: int8
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [H, W]
 *                                Argument N and C are not used.
 * @param[in]      output_dims    Output tensor dimensions. Format: [H, W, C_OUT]
 *                                Argument N is not used.
 *                                C_OUT equals C_IN.
 * @param[in, out] output_data    Output data pointer. Data type: int8
 * @return                        The function returns
 *                                    <code>ARM_MATH_SUCCESS</code> - Successful operation
 *
 * @details
 *    - Supported Framework: TensorFlow Lite
 *
 */
arm_status arm_avgpool_s8(const cmsis_nn_context *ctx,
                          const cmsis_nn_pool_params *pool_params,
                          const cmsis_nn_dims *input_dims,
                          const q7_t *input_data,
                          const cmsis_nn_dims *filter_dims,
                          const cmsis_nn_dims *output_dims,
                          q7_t *output_data);

/**
 * @brief Get the required buffer size for S8 average pooling function
 * @param[in]       dim_dst_width         output tensor dimension
 * @param[in]       ch_src                number of input tensor channels
 * @return          The function returns  required buffer size in bytes
 *
 */
int32_t arm_avgpool_s8_get_buffer_size(const int dim_dst_width, const int ch_src);

/**
 * @brief s16 average pooling function.
 *
 * @param[in, out] ctx            Function context (e.g. temporary buffer). Check the function
 *                                definition file to see if an additional buffer is required.
 *                                Optional function {API}_get_buffer_size() provides the buffer
 *                                size if an additional buffer is required.
 * @param[in]      pool_params    Pooling parameters
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                                Argument 'N' is not used.
 * @param[in]      input_data     Input (activation) data pointer. Data type: int16
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [H, W]
 *                                Argument N and C are not used.
 * @param[in]      output_dims    Output tensor dimensions. Format: [H, W, C_OUT]
 *                                Argument N is not used.
 *                                C_OUT equals C_IN.
 * @param[in, out] output_data    Output data pointer. Data type: int16
 * @return                        The function returns
 *                                    <code>ARM_MATH_SUCCESS</code> - Successful operation
 *
 * @details
 *    - Supported Framework: TensorFlow Lite
 *
 */
arm_status arm_avgpool_s16(const cmsis_nn_context *ctx,
                           const cmsis_nn_pool_params *pool_params,
                           const cmsis_nn_dims *input_dims,
                           const int16_t *input_data,
                           const cmsis_nn_dims *filter_dims,
                           const cmsis_nn_dims *output_dims,
                           int16_t *output_data);

/**
 * @brief Get the required buffer size for S16 average pooling function
 * @param[in]       dim_dst_width         output tensor dimension
 * @param[in]       ch_src                number of input tensor channels
 * @return          The function returns  required buffer size in bytes
 *
 */
int32_t arm_avgpool_s16_get_buffer_size(const int dim_dst_width, const int ch_src);

/**
 * @brief s8 max pooling function.
 *
 * @param[in, out] ctx            Function context (e.g. temporary buffer). Check the function
 *                                definition file to see if an additional buffer is required.
 *                                Optional function {API}_get_buffer_size() provides the buffer
 *                                size if an additional buffer is required.
 * @param[in]      pool_params    Pooling parameters
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                                Argument 'N' is not used.
 * @param[in]      input_data     Input (activation) data pointer. The input tensor must not
 *                                overlap with the output tensor. Data type: int8
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [H, W]
 *                                Argument N and C are not used.
 * @param[in]      output_dims    Output tensor dimensions. Format: [H, W, C_OUT]
 *                                Argument N is not used.
 *                                C_OUT equals C_IN.
 * @param[in, out] output_data    Output data pointer. Data type: int8
 * @return                        The function returns
 *                                    <code>ARM_MATH_SUCCESS</code> - Successful operation
 *
 * @details
 *    - Supported Framework: TensorFlow Lite
 *
 */
arm_status arm_max_pool_s8(const cmsis_nn_context *ctx,
                           const cmsis_nn_pool_params *pool_params,
                           const cmsis_nn_dims *input_dims,
                           const q7_t *input_data,
                           const cmsis_nn_dims *filter_dims,
                           const cmsis_nn_dims *output_dims,
                           q7_t *output_data);

/**
 * @brief s16 max pooling function.
 *
 * @param[in, out] ctx            Function context (e.g. temporary buffer). Check the function
 *                                definition file to see if an additional buffer is required.
 *                                Optional function {API}_get_buffer_size() provides the buffer
 *                                size if an additional buffer is required.
 * @param[in]      pool_params    Pooling parameters
 * @param[in]      input_dims     Input (activation) tensor dimensions. Format: [H, W, C_IN]
 *                                Argument 'N' is not used.
 * @param[in]      src            Input (activation) data pointer. The input tensor must not
 *                                overlap with the output tensor. Data type: int16
 * @param[in]      filter_dims    Filter tensor dimensions. Format: [H, W]
 *                                Argument N and C are not used.
 * @param[in]      output_dims    Output tensor dimensions. Format: [H, W, C_OUT]
 *                                Argument N is not used.
 *                                C_OUT equals C_IN.
 * @param[in, out] dst            Output data pointer. Data type: int16
 * @return                        The function returns
 *                                    <code>ARM_MATH_SUCCESS</code> - Successful operation
 *
 * @details
 *    - Supported Framework: TensorFlow Lite
 *
 */
arm_status arm_max_pool_s16(const cmsis_nn_context *ctx,
                            const cmsis_nn_pool_params *pool_params,
                            const cmsis_nn_dims *input_dims,
                            const int16_t *src,
                            const cmsis_nn_dims *filter_dims,
                            const cmsis_nn_dims *output_dims,
                            int16_t *dst);

/**
 * @defgroup Softmax Softmax Functions
 *
 * EXP(2) based softmax functions.
 *
 */

/**
 * @brief Q7 softmax function
 * @param[in]       vec_in      pointer to input vector
 * @param[in]       dim_vec     input vector dimension
 * @param[out]      p_out       pointer to output vector
 *
 * @note This function is an optimized version which is not bit-accurate with
 *       TensorFlow Lite's kernel
 *
 */

void arm_softmax_q7(const q7_t *vec_in, const uint16_t dim_vec, q7_t *p_out);

/**
 * @brief Q7 softmax function with batch parameter
 * @param[in]       vec_in      pointer to input vector
 * @param[in]       nb_batches  number of batches
 * @param[in]       dim_vec     input vector dimension
 * @param[out]      p_out       pointer to output vector
 * @return none.
 *
 * @note This function is an optimized version which is not bit-accurate with
 *       TensorFlow Lite's kernel
 *
 */

void arm_softmax_with_batch_q7(const q7_t *vec_in, const uint16_t nb_batches, const uint16_t dim_vec, q7_t *p_out);
/**
 * @brief Q15 softmax function
 * @param[in]       vec_in      pointer to input vector
 * @param[in]       dim_vec     input vector dimension
 * @param[out]      p_out       pointer to output vector
 * @return none.
 *
 * @note This function is an optimized version which is not bit-accurate with
 *       TensorFlow Lite's kernel
 *
 */

void arm_softmax_q15(const q15_t *vec_in, const uint16_t dim_vec, q15_t *p_out);

/**
 * @brief S8 softmax function
 * @param[in]  input     Pointer to the input tensor
 * @param[in]  num_rows  Number of rows in the input tensor
 * @param[in]  row_size  Number of elements in each input row
 * @param[in]  mult      Input quantization multiplier
 * @param[in]  shift     Input quantization shift within the range [0, 31]
 * @param[in]  diff_min  Minimum difference with max in row. Used to check if
 *                       the quantized exponential operation can be performed
 * @param[out] output    Pointer to the output tensor
 *
 * @note Supported framework: TensorFlow Lite micro (bit-accurate)
 *
 */
void arm_softmax_s8(const int8_t *input,
                    const int32_t num_rows,
                    const int32_t row_size,
                    const int32_t mult,
                    const int32_t shift,
                    const int32_t diff_min,
                    int8_t *output);

/**
 * @brief S8 to s16 softmax function
 * @param[in]  input     Pointer to the input tensor
 * @param[in]  num_rows  Number of rows in the input tensor
 * @param[in]  row_size  Number of elements in each input row
 * @param[in]  mult      Input quantization multiplier
 * @param[in]  shift     Input quantization shift within the range [0, 31]
 * @param[in]  diff_min  Minimum difference with max in row. Used to check if
 *                       the quantized exponential operation can be performed
 * @param[out] output    Pointer to the output tensor
 *
 * @note Supported framework: TensorFlow Lite micro (bit-accurate)
 *
 */
void arm_softmax_s8_s16(const int8_t *input,
                        const int32_t num_rows,
                        const int32_t row_size,
                        const int32_t mult,
                        const int32_t shift,
                        const int32_t diff_min,
                        int16_t *output);

/**
 * @brief S16 softmax function
 * @param[in]  input           Pointer to the input tensor
 * @param[in]  num_rows        Number of rows in the input tensor
 * @param[in]  row_size        Number of elements in each input row
 * @param[in]  mult            Input quantization multiplier
 * @param[in]  shift           Input quantization shift within the range [0, 31]
 * @param[in]  softmax_params  Softmax s16 layer parameters with two pointers to LUTs speficied below.
 *                             For indexing the high 9 bits are used and 7 remaining for interpolation.
 *                             That means 512 entries for the 9-bit indexing and 1 extra for interpolation, i.e. 513
 *                             values for each LUT.
 *                             - Lookup table for exp(x), where x uniform distributed between [-10.0 , 0.0]
 *                             - Lookup table for 1 / (1 + x), where x uniform distributed between [0.0 , 1.0]
 * @param[out] output          Pointer to the output tensor
 * @return                        The function returns
 *                                    <code>ARM_MATH_ARGUMENT_ERROR</code> if LUTs are NULL
 *                                    <code>ARM_MATH_SUCCESS</code> - Successful operation
 *
 * @note Supported framework: TensorFlow Lite micro (bit-accurate)
 *
 */
arm_status arm_softmax_s16(const int16_t *input,
                           const int32_t num_rows,
                           const int32_t row_size,
                           const int32_t mult,
                           const int32_t shift,
                           const cmsis_nn_softmax_lut_s16 *softmax_params,
                           int16_t *output);

/**
 * @brief U8 softmax function
 * @param[in]  input     Pointer to the input tensor
 * @param[in]  num_rows  Number of rows in the input tensor
 * @param[in]  row_size  Number of elements in each input row
 * @param[in]  mult      Input quantization multiplier
 * @param[in]  shift     Input quantization shift within the range [0, 31]
 * @param[in]  diff_min  Minimum difference with max in row. Used to check if
 *                       the quantized exponential operation can be performed
 * @param[out] output    Pointer to the output tensor
 *
 * @note Supported framework: TensorFlow Lite micro (bit-accurate)
 *
 */

void arm_softmax_u8(const uint8_t *input,
                    const int32_t num_rows,
                    const int32_t row_size,
                    const int32_t mult,
                    const int32_t shift,
                    const int32_t diff_min,
                    uint8_t *output);

/**
 * @brief uint8 depthwise convolution function with asymmetric quantization
 *        Unless specified otherwise, arguments are mandatory.
 *
 * @param[in]     input     Pointer to input tensor
 * @param[in]     input_x   Width of input tensor
 * @param[in]     input_y   Height of input tensor
 * @param[in]     input_ch  Channels in input tensor
 * @param[in]     kernel    Pointer to kernel weights
 * @param[in]     kernel_x  Width of kernel
 * @param[in]     kernel_y  Height of kernel
 * @param[in]     ch_mult   Number of channel multiplier
 * @param[in]     pad_x     Padding sizes x
 * @param[in]     pad_y     Padding sizes y
 * @param[in]     stride_x  stride along the width
 * @param[in]     stride_y  stride along the height
 * @param[in]     dilation_x Dilation along width. Not used and intended for future enhancement.
 * @param[in]     dilation_y Dilation along height. Not used and intended for future enhancement.
 * @param[in]     bias       Pointer to optional bias values. If no bias is
 *                           availble, NULL is expected
 * @param[in]     input_offset  Input tensor zero offset
 * @param[in]     filter_offset Kernel tensor zero offset
 * @param[in]     output_offset Output tensor zero offset
 * @param[in,out] output        Pointer to output tensor
 * @param[in]     output_x  Width of output tensor
 * @param[in]     output_y  Height of output tensor
 * @param[in]     output_activation_min   Minimum value to clamp the output to. Range : {0, 255}
 * @param[in]     output_activation_max   Minimum value to clamp the output to. Range : {0, 255}
 * @param[in]     out_shift  Amount of right-shift for output
 * @param[in]     out_mult   Output multiplier for requantization
 * @return        The function returns the following
 *                <code>ARM_MATH_SUCCESS</code> - Successful operation
 *
 */
arm_status arm_depthwise_conv_u8_basic_ver1(const uint8_t *input,
                                            const uint16_t input_x,
                                            const uint16_t input_y,
                                            const uint16_t input_ch,
                                            const uint8_t *kernel,
                                            const uint16_t kernel_x,
                                            const uint16_t kernel_y,
                                            const int16_t ch_mult,
                                            const int16_t pad_x,
                                            const int16_t pad_y,
                                            const int16_t stride_x,
                                            const int16_t stride_y,
                                            const int16_t dilation_x,
                                            const int16_t dilation_y,
                                            const int32_t *bias,
                                            const int32_t input_offset,
                                            const int32_t filter_offset,
                                            const int32_t output_offset,
                                            uint8_t *output,
                                            const uint16_t output_x,
                                            const uint16_t output_y,
                                            const int32_t output_activation_min,
                                            const int32_t output_activation_max,
                                            const int32_t out_shift,
                                            const int32_t out_mult);

/**
 * @defgroup Reshape Reshape Functions
 *
 */

/**
 * @brief Reshape a s8 vector into another with different shape
 * @param[in]  input      points to the s8 input vector
 * @param[out] output     points to the s8 output vector
 * @param[in]  total_size total size of the input and output vectors in bytes
 *
 * @note The output is expected to be in a memory area that does not overlap with the input's
 *
 */
void arm_reshape_s8(const int8_t *input, int8_t *output, const uint32_t total_size);

/**
 * @defgroup Concatenation Concatenation Functions
 *
 */

/**
 * @brief int8/uint8 concatenation function to be used for concatenating N-tensors along the X axis
 *        This function should be called for each input tensor to concatenate. The argument offset_x
 *        will be used to store the input tensor in the correct position in the output tensor
 *
 *        i.e.    offset_x = 0
 *                for(i = 0 i < num_input_tensors; ++i)
 *                {
 *                    arm_concatenation_s8_x(&input[i], ..., &output, ..., ..., offset_x)
 *                    offset_x += input_x[i]
 *                }
 *
 *        This function assumes that the output tensor has:
 *        -# The same height of the input tensor
 *        -# The same number of channels of the input tensor
 *        -# The same batch size of the input tensor
 *
 *        Unless specified otherwise, arguments are mandatory.
 *
 * @note This function, data layout independent, can be used to concatenate either int8 or uint8 tensors because it
 *      does not involve any arithmetic operation
 *
 * @param[in]  input    Pointer to input tensor. Input tensor must not overlap with the output tensor.
 * @param[in]  input_x  Width of input tensor
 * @param[in]  input_y  Height of input tensor
 * @param[in]  input_z  Channels in input tensor
 * @param[in]  input_w  Batch size in input tensor
 * @param[out] output   Pointer to output tensor. Expected to be at least
 *                          (input_x * input_y * input_z * input_w) + offset_x
 *                      bytes.
 * @param[in]  output_x Width of output tensor
 * @param[in]  offset_x The offset (in number of elements) on the X axis to start concatenating the input tensor
 *                      It is user responsibility to provide the correct value
 *
 * <b> Input constraints</b>
 * offset_x is less than output_x
 *
 */
void arm_concatenation_s8_x(const int8_t *input,
                            const uint16_t input_x,
                            const uint16_t input_y,
                            const uint16_t input_z,
                            const uint16_t input_w,
                            int8_t *output,
                            const uint16_t output_x,
                            const uint32_t offset_x);

/**
 * @brief int8/uint8 concatenation function to be used for concatenating N-tensors along the Y axis
 *        This function should be called for each input tensor to concatenate. The argument offset_y
 *        will be used to store the input tensor in the correct position in the output tensor
 *
 *        i.e.    offset_y = 0
 *                for(i = 0 i < num_input_tensors; ++i)
 *                {
 *                    arm_concatenation_s8_y(&input[i], ..., &output, ..., ..., offset_y)
 *                    offset_y += input_y[i]
 *                }
 *
 *        This function assumes that the output tensor has:
 *        -# The same width of the input tensor
 *        -# The same number of channels of the input tensor
 *        -# The same batch size of the input tensor
 *
 *        Unless specified otherwise, arguments are mandatory.
 *
 * @note This function, data layout independent, can be used to concatenate either int8 or uint8 tensors because it
 *       does not involve any arithmetic operation
 *
 * @param[in]  input    Pointer to input tensor. Input tensor must not overlap with the output tensor.
 * @param[in]  input_x  Width of input tensor
 * @param[in]  input_y  Height of input tensor
 * @param[in]  input_z  Channels in input tensor
 * @param[in]  input_w  Batch size in input tensor
 * @param[out] output   Pointer to output tensor. Expected to be at least
 *                          (input_z * input_w * input_x * input_y) + offset_y
 *                      bytes.
 * @param[in]  output_y Height of output tensor
 * @param[in]  offset_y The offset on the Y axis to start concatenating the input tensor
 *                      It is user responsibility to provide the correct value
 *
 * <b> Input constraints</b>
 * offset_y is less than output_y
 *
 */
void arm_concatenation_s8_y(const int8_t *input,
                            const uint16_t input_x,
                            const uint16_t input_y,
                            const uint16_t input_z,
                            const uint16_t input_w,
                            int8_t *output,
                            const uint16_t output_y,
                            const uint32_t offset_y);

/**
 * @brief int8/uint8 concatenation function to be used for concatenating N-tensors along the Z axis
 *        This function should be called for each input tensor to concatenate. The argument offset_z
 *        will be used to store the input tensor in the correct position in the output tensor
 *
 *        i.e.    offset_z = 0
 *                for(i = 0 i < num_input_tensors; ++i)
 *                {
 *                    arm_concatenation_s8_z(&input[i], ..., &output, ..., ..., offset_z)
 *                    offset_z += input_z[i]
 *                }
 *
 *        This function assumes that the output tensor has:
 *        -# The same width of the input tensor
 *        -# The same height of the input tensor
 *        -# The same batch size of the input tensor
 *
 *        Unless specified otherwise, arguments are mandatory.
 *
 * @note This function, data layout independent, can be used to concatenate either int8 or uint8 tensors because it
 *       does not involve any arithmetic operation
 *
 * @param[in]  input    Pointer to input tensor. Input tensor must not overlap with output tensor.
 * @param[in]  input_x  Width of input tensor
 * @param[in]  input_y  Height of input tensor
 * @param[in]  input_z  Channels in input tensor
 * @param[in]  input_w  Batch size in input tensor
 * @param[out] output   Pointer to output tensor. Expected to be at least
 *                          (input_x * input_y * input_z * input_w) + offset_z
 *                      bytes.
 * @param[in]  output_z Channels in output tensor
 * @param[in]  offset_z The offset on the Z axis to start concatenating the input tensor
 *                      It is user responsibility to provide the correct value
 *
 * <b> Input constraints</b>
 * offset_z is less than output_z
 *
 */
void arm_concatenation_s8_z(const int8_t *input,
                            const uint16_t input_x,
                            const uint16_t input_y,
                            const uint16_t input_z,
                            const uint16_t input_w,
                            int8_t *output,
                            const uint16_t output_z,
                            const uint32_t offset_z);

/**
 * @brief int8/uint8 concatenation function to be used for concatenating N-tensors along the W axis (Batch size)
 *        This function should be called for each input tensor to concatenate. The argument offset_w
 *        will be used to store the input tensor in the correct position in the output tensor
 *
 *        i.e.    offset_w = 0
 *                for(i = 0 i < num_input_tensors; ++i)
 *                {
 *                    arm_concatenation_s8_w(&input[i], ..., &output, ..., ..., offset_w)
 *                    offset_w += input_w[i]
 *                }
 *
 *        This function assumes that the output tensor has:
 *        -# The same width of the input tensor
 *        -# The same height of the input tensor
 *        -# The same number o channels of the input tensor
 *
 *        Unless specified otherwise, arguments are mandatory.
 *
 * @note This function, data layout independent, can be used to concatenate either int8 or uint8 tensors because it
 *       does not involve any arithmetic operation
 *
 * @param[in]  input    Pointer to input tensor
 * @param[in]  input_x  Width of input tensor
 * @param[in]  input_y  Height of input tensor
 * @param[in]  input_z  Channels in input tensor
 * @param[in]  input_w  Batch size in input tensor
 * @param[out] output   Pointer to output tensor. Expected to be at least
 *                          input_x * input_y * input_z * input_w
 *                      bytes.
 * @param[in]  offset_w The offset on the W axis to start concatenating the input tensor
 *                      It is user responsibility to provide the correct value
 *
 */
void arm_concatenation_s8_w(const int8_t *input,
                            const uint16_t input_x,
                            const uint16_t input_y,
                            const uint16_t input_z,
                            const uint16_t input_w,
                            int8_t *output,
                            const uint32_t offset_w);
/**
 * @defgroup SVDF SVDF Layer Functions
 *
 */

/**
 * @brief s8 SVDF function with 8 bit state tensor and 8 bit time weights
 *
 * @param[in]   input_ctx Temporary scratch buffer
 * @param[in]   output_ctx Temporary output scratch buffer
 * @param[in]   svdf_params SVDF Parameters
 *              Range of svdf_params->input_offset  : [-128, 127]
 *              Range of svdf_params->output_offset  : [-128, 127]
 * @param[in]   input_quant_params Input quantization parameters
 * @param[in]   output_quant_params Output quantization parameters
 * @param[in]   input_dims Input tensor dimensions
 * @param[in]   input_data Pointer to input tensor
 * @param[in]   state_dims State tensor dimensions
 * @param[in]   state_data Pointer to state tensor
 * @param[in]   weights_feature_dims Weights (feature) tensor dimensions
 * @param[in]   weights_feature_data Pointer to the weights (feature) tensor
 * @param[in]   weights_time_dims Weights (time) tensor dimensions
 * @param[in]   weights_time_data Pointer to the weights (time) tensor
 * @param[in]   bias_dims Bias tensor dimensions
 * @param[in]   bias_data Pointer to bias tensor
 * @param[in]   output_dims Output tensor dimensions
 * @param[out]  output_data Pointer to the output tensor
 *
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 *    2. q7 is used as data type eventhough it is s8 data. It is done so to be consistent with existing APIs.
 *
 */
arm_status arm_svdf_s8(const cmsis_nn_context *input_ctx,
                       const cmsis_nn_context *output_ctx,
                       const cmsis_nn_svdf_params *svdf_params,
                       const cmsis_nn_per_tensor_quant_params *input_quant_params,
                       const cmsis_nn_per_tensor_quant_params *output_quant_params,
                       const cmsis_nn_dims *input_dims,
                       const q7_t *input_data,
                       const cmsis_nn_dims *state_dims,
                       q7_t *state_data,
                       const cmsis_nn_dims *weights_feature_dims,
                       const q7_t *weights_feature_data,
                       const cmsis_nn_dims *weights_time_dims,
                       const q7_t *weights_time_data,
                       const cmsis_nn_dims *bias_dims,
                       const q31_t *bias_data,
                       const cmsis_nn_dims *output_dims,
                       q7_t *output_data);

/**
 * @brief s8 SVDF function with 16 bit state tensor and 16 bit time weights
 *
 * @param[in]   input_ctx Temporary scratch buffer
 * @param[in]   output_ctx Temporary output scratch buffer
 * @param[in]   svdf_params SVDF Parameters
 *              Range of svdf_params->input_offset  : [-128, 127]
 *              Range of svdf_params->output_offset  : [-128, 127]
 * @param[in]   input_quant_params Input quantization parameters
 * @param[in]   output_quant_params Output quantization parameters
 * @param[in]   input_dims Input tensor dimensions
 * @param[in]   input_data Pointer to input tensor
 * @param[in]   state_dims State tensor dimensions
 * @param[in]   state_data Pointer to state tensor
 * @param[in]   weights_feature_dims Weights (feature) tensor dimensions
 * @param[in]   weights_feature_data Pointer to the weights (feature) tensor
 * @param[in]   weights_time_dims Weights (time) tensor dimensions
 * @param[in]   weights_time_data Pointer to the weights (time) tensor
 * @param[in]   bias_dims Bias tensor dimensions
 * @param[in]   bias_data Pointer to bias tensor
 * @param[in]   output_dims Output tensor dimensions
 * @param[out]  output_data Pointer to the output tensor
 *
 * @return     The function returns <code>ARM_MATH_SUCCESS</code>
 *
 * @details
 *    1. Supported framework: TensorFlow Lite micro
 *    2. q7 is used as data type eventhough it is s8 data. It is done so to be consistent with existing APIs.
 *
 */
arm_status arm_svdf_state_s16_s8(const cmsis_nn_context *input_ctx,
                                 const cmsis_nn_context *output_ctx,
                                 const cmsis_nn_svdf_params *svdf_params,
                                 const cmsis_nn_per_tensor_quant_params *input_quant_params,
                                 const cmsis_nn_per_tensor_quant_params *output_quant_params,
                                 const cmsis_nn_dims *input_dims,
                                 const q7_t *input_data,
                                 const cmsis_nn_dims *state_dims,
                                 q15_t *state_data,
                                 const cmsis_nn_dims *weights_feature_dims,
                                 const q7_t *weights_feature_data,
                                 const cmsis_nn_dims *weights_time_dims,
                                 const q15_t *weights_time_data,
                                 const cmsis_nn_dims *bias_dims,
                                 const q31_t *bias_data,
                                 const cmsis_nn_dims *output_dims,
                                 q7_t *output_data);

#ifdef __cplusplus
}
#endif

#endif
