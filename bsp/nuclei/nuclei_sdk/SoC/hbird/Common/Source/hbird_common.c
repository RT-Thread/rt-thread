#include "hbird.h"

static uint32_t get_timer_freq()
{
    return SOC_TIMER_FREQ;
}

uint32_t measure_cpu_freq(uint32_t n)
{
    uint32_t start_mtime, delta_mtime;
    uint32_t mtime_freq = get_timer_freq();
  
    // Don't start measuruing until we see an mtime tick
    uint32_t tmp = (uint32_t)SysTimer_GetLoadValue();
    do {
        start_mtime = (uint32_t)SysTimer_GetLoadValue();
    } while (start_mtime == tmp);
  
    uint32_t start_mcycle = __RV_CSR_READ(CSR_MCYCLE);
  
    do {
        delta_mtime = (uint32_t)SysTimer_GetLoadValue() - start_mtime;
    } while (delta_mtime < n);
  
    uint32_t delta_mcycle = __RV_CSR_READ(CSR_MCYCLE) - start_mcycle;
  
    return (delta_mcycle / delta_mtime) * mtime_freq
           + ((delta_mcycle % delta_mtime) * mtime_freq) / delta_mtime;
}

uint32_t get_cpu_freq()
{
    uint32_t cpu_freq;

    // warm up
    measure_cpu_freq(1);
    // measure for real
    cpu_freq = measure_cpu_freq(100);

    return cpu_freq;
}
