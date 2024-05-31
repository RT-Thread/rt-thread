/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_sysctl_drv.h"
#include "hpm_soc_feature.h"

#define SYSCTL_RESOURCE_GROUP0 0

#define SYSCTL_CPU_RELEASE_KEY(cpu) (0xC0BEF1A9UL | ((cpu & 1) << 24))

hpm_stat_t sysctl_get_cpu0_gpr(SYSCTL_Type *ptr, uint32_t *data, uint32_t size)
{
    uint32_t i;
    for (i = 0; i < size; i++) {
        *(data + i) = ptr->CPU[0].GPR[i];
    }
    return status_success;
}

hpm_stat_t sysctl_cpu0_get_gpr(SYSCTL_Type *ptr, uint8_t start, uint8_t count, uint32_t *data)
{
    uint8_t i, size = ARRAY_SIZE(ptr->CPU[0].GPR);
    if ((data == NULL) || !count || start > size || count > size ||
        (start + count) > size) {
        return status_invalid_argument;
    }
    for (i = 0; i < count; i++) {
        *(data + i) = ptr->CPU[0].GPR[start + i];
    }
    return status_success;
}

hpm_stat_t sysctl_cpu0_set_gpr(SYSCTL_Type *ptr, uint8_t start, uint8_t count, uint32_t *data, bool lock)
{
    uint8_t i, size = ARRAY_SIZE(ptr->CPU[0].GPR);
    uint32_t gpr_mask;
    if ((data == NULL) || !count || start > size || count > size ||
        (start + count) > size) {
        return status_invalid_argument;
    }
    for (i = 0; i < count; i++) {
        ptr->CPU[0].GPR[start + i] = *(data + i);
    }
    if (lock) {
        gpr_mask = ((1 << count) - 1) << start;
        sysctl_cpu0_lock_gpr_with_mask(ptr, gpr_mask);
    }
    return status_success;
}

void sysctl_monitor_get_default_config(SYSCTL_Type *ptr, monitor_config_t *config)
{
    (void) ptr;
    config->mode = monitor_work_mode_record;
    config->accuracy = monitor_accuracy_1khz;
    config->reference = monitor_reference_24mhz;
    config->divide_by = 1;
    config->high_limit = 0;
    config->low_limit = 0;
    config->start_measure = true;
    config->enable_output = false;
    config->target = monitor_target_clk_top_cpu0;
}

void sysctl_monitor_init(SYSCTL_Type *ptr, uint8_t monitor_index, monitor_config_t *config)
{
    ptr->MONITOR[monitor_index].CONTROL &= ~(SYSCTL_MONITOR_CONTROL_START_MASK | SYSCTL_MONITOR_CONTROL_OUTEN_MASK);

    if (config->mode == monitor_work_mode_compare) {
        ptr->MONITOR[monitor_index].HIGH_LIMIT = SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_SET(config->high_limit);
        ptr->MONITOR[monitor_index].LOW_LIMIT = SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SET(config->low_limit);
    }

    ptr->MONITOR[monitor_index].CONTROL = (ptr->MONITOR[monitor_index].CONTROL &
        ~(SYSCTL_MONITOR_CONTROL_DIV_MASK | SYSCTL_MONITOR_CONTROL_MODE_MASK | SYSCTL_MONITOR_CONTROL_ACCURACY_MASK |
            SYSCTL_MONITOR_CONTROL_REFERENCE_MASK | SYSCTL_MONITOR_CONTROL_SELECTION_MASK)) |
        (SYSCTL_MONITOR_CONTROL_DIV_SET(config->divide_by - 1) | SYSCTL_MONITOR_CONTROL_MODE_SET(config->mode) |
            SYSCTL_MONITOR_CONTROL_ACCURACY_SET(config->accuracy) |
            SYSCTL_MONITOR_CONTROL_REFERENCE_SET(config->reference) |
            SYSCTL_MONITOR_CONTROL_START_SET(config->start_measure) |
            SYSCTL_MONITOR_CONTROL_OUTEN_SET(config->enable_output) |
            SYSCTL_MONITOR_CONTROL_SELECTION_SET(config->target));
}

uint32_t
sysctl_monitor_measure_frequency(SYSCTL_Type *ptr, uint8_t monitor_index, monitor_target_t target, bool enable_output)
{
    uint32_t frequency = 0;
    monitor_config_t monitor = { 0 };
    sysctl_monitor_get_default_config(ptr, &monitor);
    monitor.target = target;
    monitor.enable_output = enable_output;
    sysctl_monitor_init(ptr, monitor_index, &monitor);
    if (monitor_index < SYSCTL_SOC_MONITOR_SLICE_COUNT) {
        frequency = sysctl_monitor_get_current_result(ptr, monitor_index);
    }
    return frequency;
}

hpm_stat_t sysctl_set_cpu0_entry(SYSCTL_Type *ptr, uint32_t entry)
{
    ptr->CPU[0].GPR[0] = entry;
    ptr->CPU[0].GPR[1] = SYSCTL_CPU_RELEASE_KEY(0);
    return status_success;
}

hpm_stat_t sysctl_set_cpu0_lp_mode(SYSCTL_Type *ptr, cpu_lp_mode_t mode)
{
    ptr->CPU[0].LP = (ptr->CPU[0].LP & ~(SYSCTL_CPU_LP_MODE_MASK)) | (mode);
    return status_success;
}

hpm_stat_t
sysctl_enable_group_resource(SYSCTL_Type *ptr, uint8_t group, sysctl_resource_t resource, bool enable)
{
    uint32_t index, offset;
    if (resource < sysctl_resource_linkable_start) {
        return status_invalid_argument;
    }

    index = (resource - sysctl_resource_linkable_start) / 32;
    offset = (resource - sysctl_resource_linkable_start) % 32;
    switch (group) {
    case SYSCTL_RESOURCE_GROUP0:
        ptr->GROUP0[index].VALUE = (ptr->GROUP0[index].VALUE & ~(1UL << offset)) | (enable ? (1UL << offset) : 0);
        if (enable) {
            while (sysctl_resource_target_is_busy(ptr, resource)) {
                ;
            }
        }
        break;
    default:
        return status_invalid_argument;
    }

    return status_success;
}

bool sysctl_check_group_resource_enable(SYSCTL_Type *ptr,
                                        uint8_t group,
                                        sysctl_resource_t resource)
{
    uint32_t index, offset;
    bool enable;

    index = (resource - sysctl_resource_linkable_start) / 32;
    offset = (resource - sysctl_resource_linkable_start) % 32;
    switch (group) {
    case SYSCTL_RESOURCE_GROUP0:
        enable = ((ptr->GROUP0[index].VALUE & (1UL << offset)) != 0) ? true : false;
        break;
    default:
        enable =  false;
        break;
    }

    return enable;
}

uint32_t sysctl_get_group_resource_value(SYSCTL_Type *ptr, uint8_t group, uint8_t index)
{
    uint32_t value;
    switch (group) {
    case SYSCTL_RESOURCE_GROUP0:
        value = ptr->GROUP0[index].VALUE;
        break;
    default:
        value = 0;
        break;
    }
    return value;
}

hpm_stat_t sysctl_add_resource_to_cpu0(SYSCTL_Type *ptr, sysctl_resource_t resource)
{
    return sysctl_enable_group_resource(ptr, SYSCTL_RESOURCE_GROUP0, resource, true);
}

hpm_stat_t sysctl_remove_resource_from_cpu0(SYSCTL_Type *ptr, sysctl_resource_t resource)
{
    return sysctl_enable_group_resource(ptr, SYSCTL_RESOURCE_GROUP0, resource, false);
}

hpm_stat_t sysctl_update_divider(SYSCTL_Type *ptr, clock_node_t node, uint32_t divide_by)
{
    if (node >= clock_node_adc_start) {
        return status_invalid_argument;
    }

    ptr->CLOCK[node] = (ptr->CLOCK[node] & ~(SYSCTL_CLOCK_DIV_MASK)) | SYSCTL_CLOCK_DIV_SET(divide_by - 1);
    while (sysctl_clock_target_is_busy(ptr, node)) {
    }
    return status_success;
}

hpm_stat_t sysctl_config_clock(SYSCTL_Type *ptr, clock_node_t node, clock_source_t source, uint32_t divide_by)
{
    if (node >= clock_node_adc_start) {
        return status_invalid_argument;
    }

    if (source >= clock_source_general_source_end) {
        return status_invalid_argument;
    }
    ptr->CLOCK[node] = (ptr->CLOCK[node] & ~(SYSCTL_CLOCK_MUX_MASK | SYSCTL_CLOCK_DIV_MASK)) |
        (SYSCTL_CLOCK_MUX_SET(source) | SYSCTL_CLOCK_DIV_SET(divide_by - 1));
    while (sysctl_clock_target_is_busy(ptr, node)) {
    }
    return status_success;
}

hpm_stat_t sysctl_set_adc_clock_mux(SYSCTL_Type *ptr, clock_node_t node, clock_source_adc_t source)
{
    if (source >= clock_source_adc_clk_end) {
        return status_invalid_argument;
    }
    uint32_t adc_index = (uint32_t)(node - clock_node_adc_start);
    if (adc_index >= ARRAY_SIZE(ptr->ADCCLK)) {
        return status_invalid_argument;
    }

    ptr->ADCCLK[adc_index] = (ptr->ADCCLK[adc_index] & ~SYSCTL_ADCCLK_MUX_MASK) | SYSCTL_ADCCLK_MUX_SET(source);

    return status_success;
}

hpm_stat_t sysctl_set_i2s_clock_mux(SYSCTL_Type *ptr, clock_node_t node, clock_source_i2s_t source)
{
    if (source >= clock_source_i2s_clk_end) {
        return status_invalid_argument;
    }
    uint32_t i2s_index = (uint32_t)(node - clock_node_i2s_start);
    if (i2s_index >= ARRAY_SIZE(ptr->I2SCLK)) {
        return status_invalid_argument;
    }

    ptr->I2SCLK[i2s_index] = (ptr->I2SCLK[i2s_index] & ~SYSCTL_I2SCLK_MUX_MASK) | SYSCTL_I2SCLK_MUX_SET(source);

    return status_success;
}
