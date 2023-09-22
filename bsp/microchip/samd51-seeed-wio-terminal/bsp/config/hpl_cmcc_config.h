/* Auto-generated config file hpl_cmcc_config.h */
#ifndef HPL_CMCC_CONFIG_H
#define HPL_CMCC_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Basic Configuration

// <q> Cache enable
//<i> Defines the cache should be enabled or not.
// <id> cmcc_enable
#ifndef CONF_CMCC_ENABLE
#define CONF_CMCC_ENABLE 0x0
#endif

// <o> Cache Size
//<i> Defines the cache memory size to be configured.
// <0x0=>1 KB
// <0x1=>2 KB
// <0x2=>4 KB
// <id> cache_size
#ifndef CONF_CMCC_CACHE_SIZE
#define CONF_CMCC_CACHE_SIZE 0x2
#endif

// <e> Advanced Configuration
// <id> cmcc_advanced_configuration
// <q> Data cache disable
//<i> Defines the data cache should be disabled or not.
// <id> cmcc_data_cache_disable
#ifndef CONF_CMCC_DATA_CACHE_DISABLE
#define CONF_CMCC_DATA_CACHE_DISABLE 0x0
#endif

// <q> Instruction cache disable
//<i> Defines the Instruction cache should be disabled or not.
// <id> cmcc_inst_cache_disable
#ifndef CONF_CMCC_INST_CACHE_DISABLE
#define CONF_CMCC_INST_CACHE_DISABLE 0x0
#endif

// <q> Clock Gating disable
//<i> Defines the clock gating should be disabled or not.
// <id> cmcc_clock_gating_disable
#ifndef CONF_CMCC_CLK_GATING_DISABLE
#define CONF_CMCC_CLK_GATING_DISABLE 0x0
#endif

// </e>
// </h>

// <<< end of configuration section >>>

#endif // HPL_CMCC_CONFIG_H
