SDK_INSTALL_DIR ?= $(abspath ../../../../../../..)

include $(SDK_INSTALL_DIR)/imports.mak

CC = "$(GCC_ARMCOMPILER)/bin/arm-none-eabi-gcc"
AR = "$(GCC_ARMCOMPILER)/bin/arm-none-eabi-ar"

NAME = arm_cortexM4lf_math

OBJ_DIR = ../../../obj/gcc/m4f/arm_cortexM4lf_math
SRC_DIR = ../../../Source

CFLAGS = "-I$(GCC_ARMCOMPILER)/arm-none-eabi/include" "-I$(SDK_INSTALL_DIR)/source/third_party/CMSIS/Include" "-I$(SDK_INSTALL_DIR)/source/third_party/CMSIS/DSP_Lib/Include" "-I$(SDK_INSTALL_DIR)/source/third_party/CMSIS/DSP_Lib/PrivateInclude" "-I$(SDK_INSTALL_DIR)/source" -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -Wall -ffunction-sections -fdata-sections -std=c99 -c -g -gstrict-dwarf
AFLAGS = -cr --target=elf32-little
ASMFLAGS = "-I$(GCC_ARMCOMPILER)/arm-none-eabi/include" 

OBJECTS = $(OBJ_DIR)/arm_abs_f32.o $(OBJ_DIR)/arm_abs_q15.o $(OBJ_DIR)/arm_abs_q31.o $(OBJ_DIR)/arm_abs_q7.o $(OBJ_DIR)/arm_add_f32.o $(OBJ_DIR)/arm_add_q15.o $(OBJ_DIR)/arm_add_q31.o $(OBJ_DIR)/arm_add_q7.o $(OBJ_DIR)/arm_and_u16.o $(OBJ_DIR)/arm_and_u32.o $(OBJ_DIR)/arm_and_u8.o $(OBJ_DIR)/arm_dot_prod_f32.o $(OBJ_DIR)/arm_dot_prod_q15.o $(OBJ_DIR)/arm_dot_prod_q31.o $(OBJ_DIR)/arm_dot_prod_q7.o $(OBJ_DIR)/arm_mult_f32.o $(OBJ_DIR)/arm_mult_q15.o $(OBJ_DIR)/arm_mult_q31.o $(OBJ_DIR)/arm_mult_q7.o $(OBJ_DIR)/arm_negate_f32.o $(OBJ_DIR)/arm_negate_q15.o $(OBJ_DIR)/arm_negate_q31.o $(OBJ_DIR)/arm_negate_q7.o $(OBJ_DIR)/arm_not_u16.o $(OBJ_DIR)/arm_not_u32.o $(OBJ_DIR)/arm_not_u8.o $(OBJ_DIR)/arm_offset_f32.o $(OBJ_DIR)/arm_offset_q15.o $(OBJ_DIR)/arm_offset_q31.o $(OBJ_DIR)/arm_offset_q7.o $(OBJ_DIR)/arm_or_u16.o $(OBJ_DIR)/arm_or_u32.o $(OBJ_DIR)/arm_or_u8.o $(OBJ_DIR)/arm_scale_f32.o $(OBJ_DIR)/arm_scale_q15.o $(OBJ_DIR)/arm_scale_q31.o $(OBJ_DIR)/arm_scale_q7.o $(OBJ_DIR)/arm_shift_q15.o $(OBJ_DIR)/arm_shift_q31.o $(OBJ_DIR)/arm_shift_q7.o $(OBJ_DIR)/arm_sub_f32.o $(OBJ_DIR)/arm_sub_q15.o $(OBJ_DIR)/arm_sub_q31.o $(OBJ_DIR)/arm_sub_q7.o $(OBJ_DIR)/arm_xor_u16.o $(OBJ_DIR)/arm_xor_u32.o $(OBJ_DIR)/arm_xor_u8.o $(OBJ_DIR)/arm_gaussian_naive_bayes_predict_f32.o $(OBJ_DIR)/arm_common_tables.o $(OBJ_DIR)/arm_const_structs.o $(OBJ_DIR)/arm_mve_tables.o $(OBJ_DIR)/arm_cmplx_conj_f32.o $(OBJ_DIR)/arm_cmplx_conj_q15.o $(OBJ_DIR)/arm_cmplx_conj_q31.o $(OBJ_DIR)/arm_cmplx_dot_prod_f32.o $(OBJ_DIR)/arm_cmplx_dot_prod_q15.o $(OBJ_DIR)/arm_cmplx_dot_prod_q31.o $(OBJ_DIR)/arm_cmplx_mag_f32.o $(OBJ_DIR)/arm_cmplx_mag_q15.o $(OBJ_DIR)/arm_cmplx_mag_q31.o $(OBJ_DIR)/arm_cmplx_mag_squared_f32.o $(OBJ_DIR)/arm_cmplx_mag_squared_q15.o $(OBJ_DIR)/arm_cmplx_mag_squared_q31.o $(OBJ_DIR)/arm_cmplx_mult_cmplx_f32.o $(OBJ_DIR)/arm_cmplx_mult_cmplx_q15.o $(OBJ_DIR)/arm_cmplx_mult_cmplx_q31.o $(OBJ_DIR)/arm_cmplx_mult_real_f32.o $(OBJ_DIR)/arm_cmplx_mult_real_q15.o $(OBJ_DIR)/arm_cmplx_mult_real_q31.o $(OBJ_DIR)/arm_pid_init_f32.o $(OBJ_DIR)/arm_pid_init_q15.o $(OBJ_DIR)/arm_pid_init_q31.o $(OBJ_DIR)/arm_pid_reset_f32.o $(OBJ_DIR)/arm_pid_reset_q15.o $(OBJ_DIR)/arm_pid_reset_q31.o $(OBJ_DIR)/arm_sin_cos_f32.o $(OBJ_DIR)/arm_sin_cos_q31.o $(OBJ_DIR)/arm_boolean_distance.o $(OBJ_DIR)/arm_braycurtis_distance_f32.o $(OBJ_DIR)/arm_canberra_distance_f32.o $(OBJ_DIR)/arm_chebyshev_distance_f32.o $(OBJ_DIR)/arm_cityblock_distance_f32.o $(OBJ_DIR)/arm_correlation_distance_f32.o $(OBJ_DIR)/arm_cosine_distance_f32.o $(OBJ_DIR)/arm_dice_distance.o $(OBJ_DIR)/arm_euclidean_distance_f32.o $(OBJ_DIR)/arm_hamming_distance.o $(OBJ_DIR)/arm_jaccard_distance.o $(OBJ_DIR)/arm_jensenshannon_distance_f32.o $(OBJ_DIR)/arm_kulsinski_distance.o $(OBJ_DIR)/arm_minkowski_distance_f32.o $(OBJ_DIR)/arm_rogerstanimoto_distance.o $(OBJ_DIR)/arm_russellrao_distance.o $(OBJ_DIR)/arm_sokalmichener_distance.o $(OBJ_DIR)/arm_sokalsneath_distance.o $(OBJ_DIR)/arm_yule_distance.o $(OBJ_DIR)/arm_cos_f32.o $(OBJ_DIR)/arm_cos_q15.o $(OBJ_DIR)/arm_cos_q31.o $(OBJ_DIR)/arm_sin_f32.o $(OBJ_DIR)/arm_sin_q15.o $(OBJ_DIR)/arm_sin_q31.o $(OBJ_DIR)/arm_sqrt_q15.o $(OBJ_DIR)/arm_sqrt_q31.o $(OBJ_DIR)/arm_vexp_f32.o $(OBJ_DIR)/arm_vlog_f32.o $(OBJ_DIR)/arm_biquad_cascade_df1_32x64_init_q31.o $(OBJ_DIR)/arm_biquad_cascade_df1_32x64_q31.o $(OBJ_DIR)/arm_biquad_cascade_df1_f32.o $(OBJ_DIR)/arm_biquad_cascade_df1_fast_q15.o $(OBJ_DIR)/arm_biquad_cascade_df1_fast_q31.o $(OBJ_DIR)/arm_biquad_cascade_df1_init_f32.o $(OBJ_DIR)/arm_biquad_cascade_df1_init_q15.o $(OBJ_DIR)/arm_biquad_cascade_df1_init_q31.o $(OBJ_DIR)/arm_biquad_cascade_df1_q15.o $(OBJ_DIR)/arm_biquad_cascade_df1_q31.o $(OBJ_DIR)/arm_biquad_cascade_df2T_f32.o $(OBJ_DIR)/arm_biquad_cascade_df2T_f64.o $(OBJ_DIR)/arm_biquad_cascade_df2T_init_f32.o $(OBJ_DIR)/arm_biquad_cascade_df2T_init_f64.o $(OBJ_DIR)/arm_biquad_cascade_stereo_df2T_f32.o $(OBJ_DIR)/arm_biquad_cascade_stereo_df2T_init_f32.o $(OBJ_DIR)/arm_conv_f32.o $(OBJ_DIR)/arm_conv_fast_opt_q15.o $(OBJ_DIR)/arm_conv_fast_q15.o $(OBJ_DIR)/arm_conv_fast_q31.o $(OBJ_DIR)/arm_conv_opt_q15.o $(OBJ_DIR)/arm_conv_opt_q7.o $(OBJ_DIR)/arm_conv_partial_f32.o $(OBJ_DIR)/arm_conv_partial_fast_opt_q15.o $(OBJ_DIR)/arm_conv_partial_fast_q15.o $(OBJ_DIR)/arm_conv_partial_fast_q31.o $(OBJ_DIR)/arm_conv_partial_opt_q15.o $(OBJ_DIR)/arm_conv_partial_opt_q7.o $(OBJ_DIR)/arm_conv_partial_q15.o $(OBJ_DIR)/arm_conv_partial_q31.o $(OBJ_DIR)/arm_conv_partial_q7.o $(OBJ_DIR)/arm_conv_q15.o $(OBJ_DIR)/arm_conv_q31.o $(OBJ_DIR)/arm_conv_q7.o $(OBJ_DIR)/arm_correlate_f32.o $(OBJ_DIR)/arm_correlate_fast_opt_q15.o $(OBJ_DIR)/arm_correlate_fast_q15.o $(OBJ_DIR)/arm_correlate_fast_q31.o $(OBJ_DIR)/arm_correlate_opt_q15.o $(OBJ_DIR)/arm_correlate_opt_q7.o $(OBJ_DIR)/arm_correlate_q15.o $(OBJ_DIR)/arm_correlate_q31.o $(OBJ_DIR)/arm_correlate_q7.o $(OBJ_DIR)/arm_fir_decimate_f32.o $(OBJ_DIR)/arm_fir_decimate_fast_q15.o $(OBJ_DIR)/arm_fir_decimate_fast_q31.o $(OBJ_DIR)/arm_fir_decimate_init_f32.o $(OBJ_DIR)/arm_fir_decimate_init_q15.o $(OBJ_DIR)/arm_fir_decimate_init_q31.o $(OBJ_DIR)/arm_fir_decimate_q15.o $(OBJ_DIR)/arm_fir_decimate_q31.o $(OBJ_DIR)/arm_fir_f32.o $(OBJ_DIR)/arm_fir_fast_q15.o $(OBJ_DIR)/arm_fir_fast_q31.o $(OBJ_DIR)/arm_fir_init_f32.o $(OBJ_DIR)/arm_fir_init_q15.o $(OBJ_DIR)/arm_fir_init_q31.o $(OBJ_DIR)/arm_fir_init_q7.o $(OBJ_DIR)/arm_fir_interpolate_f32.o $(OBJ_DIR)/arm_fir_interpolate_init_f32.o $(OBJ_DIR)/arm_fir_interpolate_init_q15.o $(OBJ_DIR)/arm_fir_interpolate_init_q31.o $(OBJ_DIR)/arm_fir_interpolate_q15.o $(OBJ_DIR)/arm_fir_interpolate_q31.o $(OBJ_DIR)/arm_fir_lattice_f32.o $(OBJ_DIR)/arm_fir_lattice_init_f32.o $(OBJ_DIR)/arm_fir_lattice_init_q15.o $(OBJ_DIR)/arm_fir_lattice_init_q31.o $(OBJ_DIR)/arm_fir_lattice_q15.o $(OBJ_DIR)/arm_fir_lattice_q31.o $(OBJ_DIR)/arm_fir_q15.o $(OBJ_DIR)/arm_fir_q31.o $(OBJ_DIR)/arm_fir_q7.o $(OBJ_DIR)/arm_fir_sparse_f32.o $(OBJ_DIR)/arm_fir_sparse_init_f32.o $(OBJ_DIR)/arm_fir_sparse_init_q15.o $(OBJ_DIR)/arm_fir_sparse_init_q31.o $(OBJ_DIR)/arm_fir_sparse_init_q7.o $(OBJ_DIR)/arm_fir_sparse_q15.o $(OBJ_DIR)/arm_fir_sparse_q31.o $(OBJ_DIR)/arm_fir_sparse_q7.o $(OBJ_DIR)/arm_iir_lattice_f32.o $(OBJ_DIR)/arm_iir_lattice_init_f32.o $(OBJ_DIR)/arm_iir_lattice_init_q15.o $(OBJ_DIR)/arm_iir_lattice_init_q31.o $(OBJ_DIR)/arm_iir_lattice_q15.o $(OBJ_DIR)/arm_iir_lattice_q31.o $(OBJ_DIR)/arm_lms_f32.o $(OBJ_DIR)/arm_lms_init_f32.o $(OBJ_DIR)/arm_lms_init_q15.o $(OBJ_DIR)/arm_lms_init_q31.o $(OBJ_DIR)/arm_lms_norm_f32.o $(OBJ_DIR)/arm_lms_norm_init_f32.o $(OBJ_DIR)/arm_lms_norm_init_q15.o $(OBJ_DIR)/arm_lms_norm_init_q31.o $(OBJ_DIR)/arm_lms_norm_q15.o $(OBJ_DIR)/arm_lms_norm_q31.o $(OBJ_DIR)/arm_lms_q15.o $(OBJ_DIR)/arm_lms_q31.o $(OBJ_DIR)/arm_mat_add_f32.o $(OBJ_DIR)/arm_mat_add_q15.o $(OBJ_DIR)/arm_mat_add_q31.o $(OBJ_DIR)/arm_mat_cmplx_mult_f32.o $(OBJ_DIR)/arm_mat_cmplx_mult_q15.o $(OBJ_DIR)/arm_mat_cmplx_mult_q31.o $(OBJ_DIR)/arm_mat_init_f32.o $(OBJ_DIR)/arm_mat_init_q15.o $(OBJ_DIR)/arm_mat_init_q31.o $(OBJ_DIR)/arm_mat_inverse_f32.o $(OBJ_DIR)/arm_mat_inverse_f64.o $(OBJ_DIR)/arm_mat_mult_f32.o $(OBJ_DIR)/arm_mat_mult_fast_q15.o $(OBJ_DIR)/arm_mat_mult_fast_q31.o $(OBJ_DIR)/arm_mat_mult_q15.o $(OBJ_DIR)/arm_mat_mult_q31.o $(OBJ_DIR)/arm_mat_scale_f32.o $(OBJ_DIR)/arm_mat_scale_q15.o $(OBJ_DIR)/arm_mat_scale_q31.o $(OBJ_DIR)/arm_mat_sub_f32.o $(OBJ_DIR)/arm_mat_sub_q15.o $(OBJ_DIR)/arm_mat_sub_q31.o $(OBJ_DIR)/arm_mat_trans_f32.o $(OBJ_DIR)/arm_mat_trans_q15.o $(OBJ_DIR)/arm_mat_trans_q31.o $(OBJ_DIR)/arm_svm_linear_init_f32.o $(OBJ_DIR)/arm_svm_linear_predict_f32.o $(OBJ_DIR)/arm_svm_polynomial_init_f32.o $(OBJ_DIR)/arm_svm_polynomial_predict_f32.o $(OBJ_DIR)/arm_svm_rbf_init_f32.o $(OBJ_DIR)/arm_svm_rbf_predict_f32.o $(OBJ_DIR)/arm_svm_sigmoid_init_f32.o $(OBJ_DIR)/arm_svm_sigmoid_predict_f32.o $(OBJ_DIR)/arm_entropy_f32.o $(OBJ_DIR)/arm_entropy_f64.o $(OBJ_DIR)/arm_kullback_leibler_f32.o $(OBJ_DIR)/arm_kullback_leibler_f64.o $(OBJ_DIR)/arm_logsumexp_dot_prod_f32.o $(OBJ_DIR)/arm_logsumexp_f32.o $(OBJ_DIR)/arm_max_f32.o $(OBJ_DIR)/arm_max_no_idx_f32.o $(OBJ_DIR)/arm_max_q15.o $(OBJ_DIR)/arm_max_q31.o $(OBJ_DIR)/arm_max_q7.o $(OBJ_DIR)/arm_mean_f32.o $(OBJ_DIR)/arm_mean_q15.o $(OBJ_DIR)/arm_mean_q31.o $(OBJ_DIR)/arm_mean_q7.o $(OBJ_DIR)/arm_min_f32.o $(OBJ_DIR)/arm_min_q15.o $(OBJ_DIR)/arm_min_q31.o $(OBJ_DIR)/arm_min_q7.o $(OBJ_DIR)/arm_power_f32.o $(OBJ_DIR)/arm_power_q15.o $(OBJ_DIR)/arm_power_q31.o $(OBJ_DIR)/arm_power_q7.o $(OBJ_DIR)/arm_rms_f32.o $(OBJ_DIR)/arm_rms_q15.o $(OBJ_DIR)/arm_rms_q31.o $(OBJ_DIR)/arm_std_f32.o $(OBJ_DIR)/arm_std_q15.o $(OBJ_DIR)/arm_std_q31.o $(OBJ_DIR)/arm_var_f32.o $(OBJ_DIR)/arm_var_q15.o $(OBJ_DIR)/arm_var_q31.o $(OBJ_DIR)/arm_barycenter_f32.o $(OBJ_DIR)/arm_bitonic_sort_f32.o $(OBJ_DIR)/arm_bubble_sort_f32.o $(OBJ_DIR)/arm_copy_f32.o $(OBJ_DIR)/arm_copy_q15.o $(OBJ_DIR)/arm_copy_q31.o $(OBJ_DIR)/arm_copy_q7.o $(OBJ_DIR)/arm_fill_f32.o $(OBJ_DIR)/arm_fill_q15.o $(OBJ_DIR)/arm_fill_q31.o $(OBJ_DIR)/arm_fill_q7.o $(OBJ_DIR)/arm_float_to_q15.o $(OBJ_DIR)/arm_float_to_q31.o $(OBJ_DIR)/arm_float_to_q7.o $(OBJ_DIR)/arm_heap_sort_f32.o $(OBJ_DIR)/arm_insertion_sort_f32.o $(OBJ_DIR)/arm_merge_sort_f32.o $(OBJ_DIR)/arm_merge_sort_init_f32.o $(OBJ_DIR)/arm_q15_to_float.o $(OBJ_DIR)/arm_q15_to_q31.o $(OBJ_DIR)/arm_q15_to_q7.o $(OBJ_DIR)/arm_q31_to_float.o $(OBJ_DIR)/arm_q31_to_q15.o $(OBJ_DIR)/arm_q31_to_q7.o $(OBJ_DIR)/arm_q7_to_float.o $(OBJ_DIR)/arm_q7_to_q15.o $(OBJ_DIR)/arm_q7_to_q31.o $(OBJ_DIR)/arm_quick_sort_f32.o $(OBJ_DIR)/arm_selection_sort_f32.o $(OBJ_DIR)/arm_sort_f32.o $(OBJ_DIR)/arm_sort_init_f32.o $(OBJ_DIR)/arm_spline_interp_f32.o $(OBJ_DIR)/arm_spline_interp_init_f32.o $(OBJ_DIR)/arm_weighted_sum_f32.o $(OBJ_DIR)/arm_bitreversal.o $(OBJ_DIR)/arm_cfft_f32.o $(OBJ_DIR)/arm_cfft_f64.o $(OBJ_DIR)/arm_cfft_init_f32.o $(OBJ_DIR)/arm_cfft_init_f64.o $(OBJ_DIR)/arm_cfft_init_q15.o $(OBJ_DIR)/arm_cfft_init_q31.o $(OBJ_DIR)/arm_cfft_q15.o $(OBJ_DIR)/arm_cfft_q31.o $(OBJ_DIR)/arm_cfft_radix2_f32.o $(OBJ_DIR)/arm_cfft_radix2_init_f32.o $(OBJ_DIR)/arm_cfft_radix2_init_q15.o $(OBJ_DIR)/arm_cfft_radix2_init_q31.o $(OBJ_DIR)/arm_cfft_radix2_q15.o $(OBJ_DIR)/arm_cfft_radix2_q31.o $(OBJ_DIR)/arm_cfft_radix4_f32.o $(OBJ_DIR)/arm_cfft_radix4_init_f32.o $(OBJ_DIR)/arm_cfft_radix4_init_q15.o $(OBJ_DIR)/arm_cfft_radix4_init_q31.o $(OBJ_DIR)/arm_cfft_radix4_q15.o $(OBJ_DIR)/arm_cfft_radix4_q31.o $(OBJ_DIR)/arm_cfft_radix8_f32.o $(OBJ_DIR)/arm_dct4_f32.o $(OBJ_DIR)/arm_dct4_init_f32.o $(OBJ_DIR)/arm_dct4_init_q15.o $(OBJ_DIR)/arm_dct4_init_q31.o $(OBJ_DIR)/arm_dct4_q15.o $(OBJ_DIR)/arm_dct4_q31.o $(OBJ_DIR)/arm_rfft_f32.o $(OBJ_DIR)/arm_rfft_fast_f32.o $(OBJ_DIR)/arm_rfft_fast_f64.o $(OBJ_DIR)/arm_rfft_fast_init_f32.o $(OBJ_DIR)/arm_rfft_fast_init_f64.o $(OBJ_DIR)/arm_rfft_init_f32.o $(OBJ_DIR)/arm_rfft_init_q15.o $(OBJ_DIR)/arm_rfft_init_q31.o $(OBJ_DIR)/arm_rfft_q15.o $(OBJ_DIR)/arm_rfft_q31.o $(OBJ_DIR)/arm_bitreversal2.o

all: $(NAME).a

$(NAME).a: $(OBJECTS)
	@ echo Archiving $@
	@ $(AR) $(AFLAGS) $@ $^

$(OBJ_DIR)/arm_abs_f32.o: $(SRC_DIR)/BasicMathFunctions/arm_abs_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_abs_q15.o: $(SRC_DIR)/BasicMathFunctions/arm_abs_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_abs_q31.o: $(SRC_DIR)/BasicMathFunctions/arm_abs_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_abs_q7.o: $(SRC_DIR)/BasicMathFunctions/arm_abs_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_add_f32.o: $(SRC_DIR)/BasicMathFunctions/arm_add_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_add_q15.o: $(SRC_DIR)/BasicMathFunctions/arm_add_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_add_q31.o: $(SRC_DIR)/BasicMathFunctions/arm_add_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_add_q7.o: $(SRC_DIR)/BasicMathFunctions/arm_add_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_and_u16.o: $(SRC_DIR)/BasicMathFunctions/arm_and_u16.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_and_u32.o: $(SRC_DIR)/BasicMathFunctions/arm_and_u32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_and_u8.o: $(SRC_DIR)/BasicMathFunctions/arm_and_u8.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dot_prod_f32.o: $(SRC_DIR)/BasicMathFunctions/arm_dot_prod_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dot_prod_q15.o: $(SRC_DIR)/BasicMathFunctions/arm_dot_prod_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dot_prod_q31.o: $(SRC_DIR)/BasicMathFunctions/arm_dot_prod_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dot_prod_q7.o: $(SRC_DIR)/BasicMathFunctions/arm_dot_prod_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mult_f32.o: $(SRC_DIR)/BasicMathFunctions/arm_mult_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mult_q15.o: $(SRC_DIR)/BasicMathFunctions/arm_mult_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mult_q31.o: $(SRC_DIR)/BasicMathFunctions/arm_mult_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mult_q7.o: $(SRC_DIR)/BasicMathFunctions/arm_mult_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_negate_f32.o: $(SRC_DIR)/BasicMathFunctions/arm_negate_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_negate_q15.o: $(SRC_DIR)/BasicMathFunctions/arm_negate_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_negate_q31.o: $(SRC_DIR)/BasicMathFunctions/arm_negate_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_negate_q7.o: $(SRC_DIR)/BasicMathFunctions/arm_negate_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_not_u16.o: $(SRC_DIR)/BasicMathFunctions/arm_not_u16.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_not_u32.o: $(SRC_DIR)/BasicMathFunctions/arm_not_u32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_not_u8.o: $(SRC_DIR)/BasicMathFunctions/arm_not_u8.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_offset_f32.o: $(SRC_DIR)/BasicMathFunctions/arm_offset_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_offset_q15.o: $(SRC_DIR)/BasicMathFunctions/arm_offset_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_offset_q31.o: $(SRC_DIR)/BasicMathFunctions/arm_offset_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_offset_q7.o: $(SRC_DIR)/BasicMathFunctions/arm_offset_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_or_u16.o: $(SRC_DIR)/BasicMathFunctions/arm_or_u16.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_or_u32.o: $(SRC_DIR)/BasicMathFunctions/arm_or_u32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_or_u8.o: $(SRC_DIR)/BasicMathFunctions/arm_or_u8.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_scale_f32.o: $(SRC_DIR)/BasicMathFunctions/arm_scale_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_scale_q15.o: $(SRC_DIR)/BasicMathFunctions/arm_scale_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_scale_q31.o: $(SRC_DIR)/BasicMathFunctions/arm_scale_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_scale_q7.o: $(SRC_DIR)/BasicMathFunctions/arm_scale_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_shift_q15.o: $(SRC_DIR)/BasicMathFunctions/arm_shift_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_shift_q31.o: $(SRC_DIR)/BasicMathFunctions/arm_shift_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_shift_q7.o: $(SRC_DIR)/BasicMathFunctions/arm_shift_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sub_f32.o: $(SRC_DIR)/BasicMathFunctions/arm_sub_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sub_q15.o: $(SRC_DIR)/BasicMathFunctions/arm_sub_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sub_q31.o: $(SRC_DIR)/BasicMathFunctions/arm_sub_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sub_q7.o: $(SRC_DIR)/BasicMathFunctions/arm_sub_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_xor_u16.o: $(SRC_DIR)/BasicMathFunctions/arm_xor_u16.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_xor_u32.o: $(SRC_DIR)/BasicMathFunctions/arm_xor_u32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_xor_u8.o: $(SRC_DIR)/BasicMathFunctions/arm_xor_u8.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_gaussian_naive_bayes_predict_f32.o: $(SRC_DIR)/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_common_tables.o: $(SRC_DIR)/CommonTables/arm_common_tables.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_const_structs.o: $(SRC_DIR)/CommonTables/arm_const_structs.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mve_tables.o: $(SRC_DIR)/CommonTables/arm_mve_tables.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_conj_f32.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_conj_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_conj_q15.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_conj_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_conj_q31.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_conj_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_dot_prod_f32.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_dot_prod_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_dot_prod_q15.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_dot_prod_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_dot_prod_q31.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_dot_prod_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mag_f32.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mag_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mag_q15.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mag_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mag_q31.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mag_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mag_squared_f32.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mag_squared_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mag_squared_q15.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mag_squared_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mag_squared_q31.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mag_squared_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mult_cmplx_f32.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mult_cmplx_q15.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mult_cmplx_q31.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mult_real_f32.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mult_real_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mult_real_q15.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mult_real_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cmplx_mult_real_q31.o: $(SRC_DIR)/ComplexMathFunctions/arm_cmplx_mult_real_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_pid_init_f32.o: $(SRC_DIR)/ControllerFunctions/arm_pid_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_pid_init_q15.o: $(SRC_DIR)/ControllerFunctions/arm_pid_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_pid_init_q31.o: $(SRC_DIR)/ControllerFunctions/arm_pid_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_pid_reset_f32.o: $(SRC_DIR)/ControllerFunctions/arm_pid_reset_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_pid_reset_q15.o: $(SRC_DIR)/ControllerFunctions/arm_pid_reset_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_pid_reset_q31.o: $(SRC_DIR)/ControllerFunctions/arm_pid_reset_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sin_cos_f32.o: $(SRC_DIR)/ControllerFunctions/arm_sin_cos_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sin_cos_q31.o: $(SRC_DIR)/ControllerFunctions/arm_sin_cos_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_boolean_distance.o: $(SRC_DIR)/DistanceFunctions/arm_boolean_distance.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_braycurtis_distance_f32.o: $(SRC_DIR)/DistanceFunctions/arm_braycurtis_distance_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_canberra_distance_f32.o: $(SRC_DIR)/DistanceFunctions/arm_canberra_distance_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_chebyshev_distance_f32.o: $(SRC_DIR)/DistanceFunctions/arm_chebyshev_distance_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cityblock_distance_f32.o: $(SRC_DIR)/DistanceFunctions/arm_cityblock_distance_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_correlation_distance_f32.o: $(SRC_DIR)/DistanceFunctions/arm_correlation_distance_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cosine_distance_f32.o: $(SRC_DIR)/DistanceFunctions/arm_cosine_distance_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dice_distance.o: $(SRC_DIR)/DistanceFunctions/arm_dice_distance.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_euclidean_distance_f32.o: $(SRC_DIR)/DistanceFunctions/arm_euclidean_distance_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_hamming_distance.o: $(SRC_DIR)/DistanceFunctions/arm_hamming_distance.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_jaccard_distance.o: $(SRC_DIR)/DistanceFunctions/arm_jaccard_distance.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_jensenshannon_distance_f32.o: $(SRC_DIR)/DistanceFunctions/arm_jensenshannon_distance_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_kulsinski_distance.o: $(SRC_DIR)/DistanceFunctions/arm_kulsinski_distance.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_minkowski_distance_f32.o: $(SRC_DIR)/DistanceFunctions/arm_minkowski_distance_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rogerstanimoto_distance.o: $(SRC_DIR)/DistanceFunctions/arm_rogerstanimoto_distance.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_russellrao_distance.o: $(SRC_DIR)/DistanceFunctions/arm_russellrao_distance.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sokalmichener_distance.o: $(SRC_DIR)/DistanceFunctions/arm_sokalmichener_distance.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sokalsneath_distance.o: $(SRC_DIR)/DistanceFunctions/arm_sokalsneath_distance.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_yule_distance.o: $(SRC_DIR)/DistanceFunctions/arm_yule_distance.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cos_f32.o: $(SRC_DIR)/FastMathFunctions/arm_cos_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cos_q15.o: $(SRC_DIR)/FastMathFunctions/arm_cos_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cos_q31.o: $(SRC_DIR)/FastMathFunctions/arm_cos_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sin_f32.o: $(SRC_DIR)/FastMathFunctions/arm_sin_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sin_q15.o: $(SRC_DIR)/FastMathFunctions/arm_sin_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sin_q31.o: $(SRC_DIR)/FastMathFunctions/arm_sin_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sqrt_q15.o: $(SRC_DIR)/FastMathFunctions/arm_sqrt_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sqrt_q31.o: $(SRC_DIR)/FastMathFunctions/arm_sqrt_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_vexp_f32.o: $(SRC_DIR)/FastMathFunctions/arm_vexp_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_vlog_f32.o: $(SRC_DIR)/FastMathFunctions/arm_vlog_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df1_32x64_init_q31.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df1_32x64_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df1_32x64_q31.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df1_32x64_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df1_f32.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df1_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df1_fast_q15.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df1_fast_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df1_fast_q31.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df1_fast_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df1_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df1_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df1_init_q15.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df1_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df1_init_q31.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df1_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df1_q15.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df1_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df1_q31.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df1_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df2T_f32.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df2T_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df2T_f64.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df2T_f64.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df2T_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df2T_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_df2T_init_f64.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_df2T_init_f64.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_stereo_df2T_f32.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_stereo_df2T_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_biquad_cascade_stereo_df2T_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_biquad_cascade_stereo_df2T_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_f32.o: $(SRC_DIR)/FilteringFunctions/arm_conv_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_fast_opt_q15.o: $(SRC_DIR)/FilteringFunctions/arm_conv_fast_opt_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_fast_q15.o: $(SRC_DIR)/FilteringFunctions/arm_conv_fast_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_fast_q31.o: $(SRC_DIR)/FilteringFunctions/arm_conv_fast_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_opt_q15.o: $(SRC_DIR)/FilteringFunctions/arm_conv_opt_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_opt_q7.o: $(SRC_DIR)/FilteringFunctions/arm_conv_opt_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_partial_f32.o: $(SRC_DIR)/FilteringFunctions/arm_conv_partial_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_partial_fast_opt_q15.o: $(SRC_DIR)/FilteringFunctions/arm_conv_partial_fast_opt_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_partial_fast_q15.o: $(SRC_DIR)/FilteringFunctions/arm_conv_partial_fast_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_partial_fast_q31.o: $(SRC_DIR)/FilteringFunctions/arm_conv_partial_fast_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_partial_opt_q15.o: $(SRC_DIR)/FilteringFunctions/arm_conv_partial_opt_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_partial_opt_q7.o: $(SRC_DIR)/FilteringFunctions/arm_conv_partial_opt_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_partial_q15.o: $(SRC_DIR)/FilteringFunctions/arm_conv_partial_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_partial_q31.o: $(SRC_DIR)/FilteringFunctions/arm_conv_partial_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_partial_q7.o: $(SRC_DIR)/FilteringFunctions/arm_conv_partial_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_q15.o: $(SRC_DIR)/FilteringFunctions/arm_conv_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_q31.o: $(SRC_DIR)/FilteringFunctions/arm_conv_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_conv_q7.o: $(SRC_DIR)/FilteringFunctions/arm_conv_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_correlate_f32.o: $(SRC_DIR)/FilteringFunctions/arm_correlate_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_correlate_fast_opt_q15.o: $(SRC_DIR)/FilteringFunctions/arm_correlate_fast_opt_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_correlate_fast_q15.o: $(SRC_DIR)/FilteringFunctions/arm_correlate_fast_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_correlate_fast_q31.o: $(SRC_DIR)/FilteringFunctions/arm_correlate_fast_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_correlate_opt_q15.o: $(SRC_DIR)/FilteringFunctions/arm_correlate_opt_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_correlate_opt_q7.o: $(SRC_DIR)/FilteringFunctions/arm_correlate_opt_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_correlate_q15.o: $(SRC_DIR)/FilteringFunctions/arm_correlate_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_correlate_q31.o: $(SRC_DIR)/FilteringFunctions/arm_correlate_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_correlate_q7.o: $(SRC_DIR)/FilteringFunctions/arm_correlate_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_decimate_f32.o: $(SRC_DIR)/FilteringFunctions/arm_fir_decimate_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_decimate_fast_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_decimate_fast_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_decimate_fast_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_decimate_fast_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_decimate_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_fir_decimate_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_decimate_init_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_decimate_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_decimate_init_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_decimate_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_decimate_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_decimate_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_decimate_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_decimate_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_f32.o: $(SRC_DIR)/FilteringFunctions/arm_fir_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_fast_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_fast_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_fast_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_fast_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_fir_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_init_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_init_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_init_q7.o: $(SRC_DIR)/FilteringFunctions/arm_fir_init_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_interpolate_f32.o: $(SRC_DIR)/FilteringFunctions/arm_fir_interpolate_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_interpolate_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_fir_interpolate_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_interpolate_init_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_interpolate_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_interpolate_init_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_interpolate_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_interpolate_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_interpolate_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_interpolate_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_interpolate_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_lattice_f32.o: $(SRC_DIR)/FilteringFunctions/arm_fir_lattice_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_lattice_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_fir_lattice_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_lattice_init_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_lattice_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_lattice_init_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_lattice_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_lattice_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_lattice_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_lattice_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_lattice_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_q7.o: $(SRC_DIR)/FilteringFunctions/arm_fir_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_sparse_f32.o: $(SRC_DIR)/FilteringFunctions/arm_fir_sparse_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_sparse_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_fir_sparse_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_sparse_init_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_sparse_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_sparse_init_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_sparse_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_sparse_init_q7.o: $(SRC_DIR)/FilteringFunctions/arm_fir_sparse_init_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_sparse_q15.o: $(SRC_DIR)/FilteringFunctions/arm_fir_sparse_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_sparse_q31.o: $(SRC_DIR)/FilteringFunctions/arm_fir_sparse_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fir_sparse_q7.o: $(SRC_DIR)/FilteringFunctions/arm_fir_sparse_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_iir_lattice_f32.o: $(SRC_DIR)/FilteringFunctions/arm_iir_lattice_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_iir_lattice_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_iir_lattice_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_iir_lattice_init_q15.o: $(SRC_DIR)/FilteringFunctions/arm_iir_lattice_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_iir_lattice_init_q31.o: $(SRC_DIR)/FilteringFunctions/arm_iir_lattice_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_iir_lattice_q15.o: $(SRC_DIR)/FilteringFunctions/arm_iir_lattice_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_iir_lattice_q31.o: $(SRC_DIR)/FilteringFunctions/arm_iir_lattice_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_f32.o: $(SRC_DIR)/FilteringFunctions/arm_lms_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_lms_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_init_q15.o: $(SRC_DIR)/FilteringFunctions/arm_lms_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_init_q31.o: $(SRC_DIR)/FilteringFunctions/arm_lms_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_norm_f32.o: $(SRC_DIR)/FilteringFunctions/arm_lms_norm_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_norm_init_f32.o: $(SRC_DIR)/FilteringFunctions/arm_lms_norm_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_norm_init_q15.o: $(SRC_DIR)/FilteringFunctions/arm_lms_norm_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_norm_init_q31.o: $(SRC_DIR)/FilteringFunctions/arm_lms_norm_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_norm_q15.o: $(SRC_DIR)/FilteringFunctions/arm_lms_norm_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_norm_q31.o: $(SRC_DIR)/FilteringFunctions/arm_lms_norm_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_q15.o: $(SRC_DIR)/FilteringFunctions/arm_lms_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_lms_q31.o: $(SRC_DIR)/FilteringFunctions/arm_lms_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_add_f32.o: $(SRC_DIR)/MatrixFunctions/arm_mat_add_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_add_q15.o: $(SRC_DIR)/MatrixFunctions/arm_mat_add_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_add_q31.o: $(SRC_DIR)/MatrixFunctions/arm_mat_add_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_cmplx_mult_f32.o: $(SRC_DIR)/MatrixFunctions/arm_mat_cmplx_mult_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_cmplx_mult_q15.o: $(SRC_DIR)/MatrixFunctions/arm_mat_cmplx_mult_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_cmplx_mult_q31.o: $(SRC_DIR)/MatrixFunctions/arm_mat_cmplx_mult_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_init_f32.o: $(SRC_DIR)/MatrixFunctions/arm_mat_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_init_q15.o: $(SRC_DIR)/MatrixFunctions/arm_mat_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_init_q31.o: $(SRC_DIR)/MatrixFunctions/arm_mat_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_inverse_f32.o: $(SRC_DIR)/MatrixFunctions/arm_mat_inverse_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_inverse_f64.o: $(SRC_DIR)/MatrixFunctions/arm_mat_inverse_f64.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_mult_f32.o: $(SRC_DIR)/MatrixFunctions/arm_mat_mult_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_mult_fast_q15.o: $(SRC_DIR)/MatrixFunctions/arm_mat_mult_fast_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_mult_fast_q31.o: $(SRC_DIR)/MatrixFunctions/arm_mat_mult_fast_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_mult_q15.o: $(SRC_DIR)/MatrixFunctions/arm_mat_mult_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_mult_q31.o: $(SRC_DIR)/MatrixFunctions/arm_mat_mult_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_scale_f32.o: $(SRC_DIR)/MatrixFunctions/arm_mat_scale_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_scale_q15.o: $(SRC_DIR)/MatrixFunctions/arm_mat_scale_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_scale_q31.o: $(SRC_DIR)/MatrixFunctions/arm_mat_scale_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_sub_f32.o: $(SRC_DIR)/MatrixFunctions/arm_mat_sub_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_sub_q15.o: $(SRC_DIR)/MatrixFunctions/arm_mat_sub_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_sub_q31.o: $(SRC_DIR)/MatrixFunctions/arm_mat_sub_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_trans_f32.o: $(SRC_DIR)/MatrixFunctions/arm_mat_trans_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_trans_q15.o: $(SRC_DIR)/MatrixFunctions/arm_mat_trans_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mat_trans_q31.o: $(SRC_DIR)/MatrixFunctions/arm_mat_trans_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_svm_linear_init_f32.o: $(SRC_DIR)/SVMFunctions/arm_svm_linear_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_svm_linear_predict_f32.o: $(SRC_DIR)/SVMFunctions/arm_svm_linear_predict_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_svm_polynomial_init_f32.o: $(SRC_DIR)/SVMFunctions/arm_svm_polynomial_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_svm_polynomial_predict_f32.o: $(SRC_DIR)/SVMFunctions/arm_svm_polynomial_predict_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_svm_rbf_init_f32.o: $(SRC_DIR)/SVMFunctions/arm_svm_rbf_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_svm_rbf_predict_f32.o: $(SRC_DIR)/SVMFunctions/arm_svm_rbf_predict_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_svm_sigmoid_init_f32.o: $(SRC_DIR)/SVMFunctions/arm_svm_sigmoid_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_svm_sigmoid_predict_f32.o: $(SRC_DIR)/SVMFunctions/arm_svm_sigmoid_predict_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_entropy_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_entropy_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_entropy_f64.o: $(SRC_DIR)/StatisticsFunctions/arm_entropy_f64.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_kullback_leibler_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_kullback_leibler_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_kullback_leibler_f64.o: $(SRC_DIR)/StatisticsFunctions/arm_kullback_leibler_f64.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_logsumexp_dot_prod_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_logsumexp_dot_prod_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_logsumexp_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_logsumexp_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_max_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_max_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_max_no_idx_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_max_no_idx_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_max_q15.o: $(SRC_DIR)/StatisticsFunctions/arm_max_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_max_q31.o: $(SRC_DIR)/StatisticsFunctions/arm_max_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_max_q7.o: $(SRC_DIR)/StatisticsFunctions/arm_max_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mean_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_mean_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mean_q15.o: $(SRC_DIR)/StatisticsFunctions/arm_mean_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mean_q31.o: $(SRC_DIR)/StatisticsFunctions/arm_mean_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_mean_q7.o: $(SRC_DIR)/StatisticsFunctions/arm_mean_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_min_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_min_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_min_q15.o: $(SRC_DIR)/StatisticsFunctions/arm_min_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_min_q31.o: $(SRC_DIR)/StatisticsFunctions/arm_min_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_min_q7.o: $(SRC_DIR)/StatisticsFunctions/arm_min_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_power_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_power_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_power_q15.o: $(SRC_DIR)/StatisticsFunctions/arm_power_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_power_q31.o: $(SRC_DIR)/StatisticsFunctions/arm_power_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_power_q7.o: $(SRC_DIR)/StatisticsFunctions/arm_power_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rms_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_rms_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rms_q15.o: $(SRC_DIR)/StatisticsFunctions/arm_rms_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rms_q31.o: $(SRC_DIR)/StatisticsFunctions/arm_rms_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_std_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_std_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_std_q15.o: $(SRC_DIR)/StatisticsFunctions/arm_std_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_std_q31.o: $(SRC_DIR)/StatisticsFunctions/arm_std_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_var_f32.o: $(SRC_DIR)/StatisticsFunctions/arm_var_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_var_q15.o: $(SRC_DIR)/StatisticsFunctions/arm_var_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_var_q31.o: $(SRC_DIR)/StatisticsFunctions/arm_var_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_barycenter_f32.o: $(SRC_DIR)/SupportFunctions/arm_barycenter_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_bitonic_sort_f32.o: $(SRC_DIR)/SupportFunctions/arm_bitonic_sort_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_bubble_sort_f32.o: $(SRC_DIR)/SupportFunctions/arm_bubble_sort_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_copy_f32.o: $(SRC_DIR)/SupportFunctions/arm_copy_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_copy_q15.o: $(SRC_DIR)/SupportFunctions/arm_copy_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_copy_q31.o: $(SRC_DIR)/SupportFunctions/arm_copy_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_copy_q7.o: $(SRC_DIR)/SupportFunctions/arm_copy_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fill_f32.o: $(SRC_DIR)/SupportFunctions/arm_fill_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fill_q15.o: $(SRC_DIR)/SupportFunctions/arm_fill_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fill_q31.o: $(SRC_DIR)/SupportFunctions/arm_fill_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_fill_q7.o: $(SRC_DIR)/SupportFunctions/arm_fill_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_float_to_q15.o: $(SRC_DIR)/SupportFunctions/arm_float_to_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_float_to_q31.o: $(SRC_DIR)/SupportFunctions/arm_float_to_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_float_to_q7.o: $(SRC_DIR)/SupportFunctions/arm_float_to_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_heap_sort_f32.o: $(SRC_DIR)/SupportFunctions/arm_heap_sort_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_insertion_sort_f32.o: $(SRC_DIR)/SupportFunctions/arm_insertion_sort_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_merge_sort_f32.o: $(SRC_DIR)/SupportFunctions/arm_merge_sort_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_merge_sort_init_f32.o: $(SRC_DIR)/SupportFunctions/arm_merge_sort_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_q15_to_float.o: $(SRC_DIR)/SupportFunctions/arm_q15_to_float.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_q15_to_q31.o: $(SRC_DIR)/SupportFunctions/arm_q15_to_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_q15_to_q7.o: $(SRC_DIR)/SupportFunctions/arm_q15_to_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_q31_to_float.o: $(SRC_DIR)/SupportFunctions/arm_q31_to_float.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_q31_to_q15.o: $(SRC_DIR)/SupportFunctions/arm_q31_to_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_q31_to_q7.o: $(SRC_DIR)/SupportFunctions/arm_q31_to_q7.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_q7_to_float.o: $(SRC_DIR)/SupportFunctions/arm_q7_to_float.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_q7_to_q15.o: $(SRC_DIR)/SupportFunctions/arm_q7_to_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_q7_to_q31.o: $(SRC_DIR)/SupportFunctions/arm_q7_to_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_quick_sort_f32.o: $(SRC_DIR)/SupportFunctions/arm_quick_sort_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_selection_sort_f32.o: $(SRC_DIR)/SupportFunctions/arm_selection_sort_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sort_f32.o: $(SRC_DIR)/SupportFunctions/arm_sort_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_sort_init_f32.o: $(SRC_DIR)/SupportFunctions/arm_sort_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_spline_interp_f32.o: $(SRC_DIR)/SupportFunctions/arm_spline_interp_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_spline_interp_init_f32.o: $(SRC_DIR)/SupportFunctions/arm_spline_interp_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_weighted_sum_f32.o: $(SRC_DIR)/SupportFunctions/arm_weighted_sum_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_bitreversal.o: $(SRC_DIR)/TransformFunctions/arm_bitreversal.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_f32.o: $(SRC_DIR)/TransformFunctions/arm_cfft_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_f64.o: $(SRC_DIR)/TransformFunctions/arm_cfft_f64.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_init_f32.o: $(SRC_DIR)/TransformFunctions/arm_cfft_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_init_f64.o: $(SRC_DIR)/TransformFunctions/arm_cfft_init_f64.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_init_q15.o: $(SRC_DIR)/TransformFunctions/arm_cfft_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_init_q31.o: $(SRC_DIR)/TransformFunctions/arm_cfft_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_q15.o: $(SRC_DIR)/TransformFunctions/arm_cfft_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_q31.o: $(SRC_DIR)/TransformFunctions/arm_cfft_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix2_f32.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix2_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix2_init_f32.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix2_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix2_init_q15.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix2_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix2_init_q31.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix2_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix2_q15.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix2_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix2_q31.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix2_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix4_f32.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix4_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix4_init_f32.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix4_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix4_init_q15.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix4_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix4_init_q31.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix4_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix4_q15.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix4_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix4_q31.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix4_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_cfft_radix8_f32.o: $(SRC_DIR)/TransformFunctions/arm_cfft_radix8_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dct4_f32.o: $(SRC_DIR)/TransformFunctions/arm_dct4_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dct4_init_f32.o: $(SRC_DIR)/TransformFunctions/arm_dct4_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dct4_init_q15.o: $(SRC_DIR)/TransformFunctions/arm_dct4_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dct4_init_q31.o: $(SRC_DIR)/TransformFunctions/arm_dct4_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dct4_q15.o: $(SRC_DIR)/TransformFunctions/arm_dct4_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_dct4_q31.o: $(SRC_DIR)/TransformFunctions/arm_dct4_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rfft_f32.o: $(SRC_DIR)/TransformFunctions/arm_rfft_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rfft_fast_f32.o: $(SRC_DIR)/TransformFunctions/arm_rfft_fast_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rfft_fast_f64.o: $(SRC_DIR)/TransformFunctions/arm_rfft_fast_f64.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rfft_fast_init_f32.o: $(SRC_DIR)/TransformFunctions/arm_rfft_fast_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rfft_fast_init_f64.o: $(SRC_DIR)/TransformFunctions/arm_rfft_fast_init_f64.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rfft_init_f32.o: $(SRC_DIR)/TransformFunctions/arm_rfft_init_f32.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rfft_init_q15.o: $(SRC_DIR)/TransformFunctions/arm_rfft_init_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rfft_init_q31.o: $(SRC_DIR)/TransformFunctions/arm_rfft_init_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rfft_q15.o: $(SRC_DIR)/TransformFunctions/arm_rfft_q15.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_rfft_q31.o: $(SRC_DIR)/TransformFunctions/arm_rfft_q31.c
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/arm_bitreversal2.o: $(SRC_DIR)/TransformFunctions/arm_bitreversal2.S
	@ echo Building $@
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $< -o $@

clean:
	@ echo Cleaning...
	@ $(RM) $(OBJECTS) > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).a > $(DEVNULL) 2>&1
