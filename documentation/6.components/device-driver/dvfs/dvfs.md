@page page_device_dvfs DVFS

# Dynamic Voltage and Frequency Scaling (DVFS)

Headers: **`components/drivers/include/drivers/dvfs.h`**. Core: **`components/drivers/dvfs/dvfs.c`**, governors: **`components/drivers/dvfs/governor/`**, shell: **`components/drivers/dvfs/dvfs_cmd.c`**.

DVFS selects an **OPP (Operating Performance Point)** — a frequency and supply voltage pair — according to a **governor** policy. The framework owns the OPP table, governor lifecycle, and MSH commands; **BSP or SoC drivers** implement how a given OPP is applied (clock, regulator, firmware calls).

**Kconfig**: **`RT_USING_DVFS`** (requires **`RT_USING_DM`**, **`RT_USING_CLK`**, **`RT_USING_REGULATOR`**). Optional: **`RT_USING_DVFS_EVENT`**, **`RT_DVFS_SCMI_CPUFREQ`**, and BSP options under **`SOC_DM_DVFS_*`**.

---

## Architecture

```
Device tree (operating-points-v2, supplies, clocks)
        |
        v
BSP cpufreq / devfreq driver (SOC_DM_DVFS_CPUFREQ_DIR, …)
  fills rt_dvfs_scaling_ops (set_opp, parse_opp, …)
        |
        v
rt_dvfs_cpufreq_register() / rt_dvfs_devfreq_register()
        |
        v
rt_dvfs_scaling  (OPP table, cur_freq, governor)
        |
        +-- governor (performance / ondemand / …)
        +-- thermal-cool-dvfs (optional, RT_THERMAL_COOL_DVFS)
        +-- rt_dvfs_scaling_set_frequency() / apply_opp()
```

| Layer | Location | Role |
| --- | --- | --- |
| Framework | `components/drivers/dvfs/` | OPP table, governors, load stats, PM hooks, MSH |
| Generic SCMI | `dvfs-scmi-cpufreq.c` | Optional SCMI-based CPUfreq (**`RT_DVFS_SCMI_CPUFREQ`**) |
| BSP | **`SOC_DM_DVFS_CPUFREQ_DIR`**, **`SOC_DM_DVFS_DEVFREQ_DIR`**, **`SOC_DM_DVFS_EVENT_DIR`** | Platform probe, **`set_opp`**, DT parsing |
| Thermal | `thermal-cool-dvfs.c` | Map cooling levels to OPP indices — @ref page_device_thermal_cool |

When **`RT_USING_DVFS`** is enabled, **`struct rt_device::dvfs_scaling`** links a device to its scaling domain for **`list_dvfs`** / **`dvfs dump`**.

---

## Registering a scaling domain (BSP driver)

Typical CPU path:

1. Allocate **`struct rt_dvfs_cpufreq`** (embeds **`struct rt_dvfs_scaling`**).
2. Fill **`scaling->ops`** — at minimum **`set_opp`** and **`parse_opp`** for DT-backed OPP tables.
3. Obtain **`scaling->clk`** and **`scaling->supply`** from the CPU / cluster device node.
4. Parse OPP nodes ( **`operating-points-v2`** ) into the scaling OPP table.
5. Call **`rt_dvfs_cpufreq_register()`**, then **`rt_dvfs_scaling_set_governor()`** with the desired default governor.

Devfreq devices follow the same pattern with **`struct rt_dvfs_devfreq`** and optional **`struct rt_dvfs_event`** for load feedback (**`RT_USING_DVFS_EVENT`**).

If the driver does not provide **`ops->set_opp`**, the framework falls back to a generic sequence using **`rt_clk_set_rate`** and **`rt_regulator_set_voltage`** on **`scaling->clk`** / **`scaling->supply`**.

---

## Governors

| Name | Behavior |
| --- | --- |
| **`performance`** | Always **`max_freq`** |
| **`powersave`** | Always **`min_freq`** |
| **`freedom`** | No automatic changes; user sets frequency manually |
| **`ondemand`** | Periodic load sampling; high load → max, low load → scaled down |
| **`conservative`** | Step up/down by **`freq_step`** |
| **`schedutil`** | Target frequency proportional to estimated load |

Dynamic governors depend on **`RT_USING_IDLE_HOOK`** (load estimation) and **`RT_USING_SYSTEM_WORKQUEUE`** (monitor timer). The default governor is chosen by the BSP driver at registration time.

Governor parameters (**`up_threshold`**, **`sampling_rate_ms`**, …) live in **`struct rt_dvfs_governor_params`** and can be adjusted via **`rt_dvfs_governor_set_params()`**.

---

## MSH commands

Requires **`RT_USING_CONSOLE`** and **`RT_USING_MSH`** (**`dvfs_cmd.c`**).

```text
list_dvfs
dvfs dump <name>
dvfs set_governor <name> <governor>
dvfs set_frequency <name> <Hz>
```

**`set_frequency`** switches to **`freedom`** automatically when the active governor is not freedom.

Example:

```text
msh />dvfs set_governor cpu0 performance
msh />dvfs dump cpu0
```

The scaling device **`<name>`** is assigned by the BSP driver (commonly **`cpufreq0`**, **`dmc`**, etc.).

---

## Device tree (typical CPU)

Minimal pattern (details vary by SoC BSP):

```dts
cpu0: cpu@0 {
    device_type = "cpu";
    compatible = "arm,cortex-a55";
    operating-points-v2 = <&cpu0_opp_table>;
    cpu-supply = <&cpu_reg>;
    /* optional: #cooling-cells for thermal-cool-dvfs */
};

cpu0_opp_table: opp-table {
    compatible = "operating-points-v2";
    opp-1000000000 {
        opp-hz = /bits/ 64 <1000000000>;
        opp-microvolt = <900000>;
    };
    /* additional OPP nodes … */
};
```

| Binding | Role |
| --- | --- |
| **`operating-points-v2`** | OPP table phandle on the scaling device |
| **`opp-hz` / `opp-microvolt`** | Frequency (Hz) and voltage (µV) per OPP |
| **`*-supply`** | Regulator phandle(s) used when scaling voltage |
| **`#cooling-cells`** | Enables **`dvfs-cool`** thermal device on the CPU node |

Passive thermal **`cooling-maps`** can reference the DVFS cooling device to cap OPP on trip — see @ref page_device_thermal_cool.

---

## Kconfig

| Option | Role |
| --- | --- |
| **`RT_USING_DVFS`** | Core framework + governors |
| **`RT_USING_DVFS_EVENT`** | **`dvfs_event.c`**, devfreq load via event devices |
| **`RT_USING_DVFS_OPP_RETRY_MAX`** | Retries on **`-RT_EBUSY`** during OPP transition |
| **`RT_DVFS_SCMI_CPUFREQ`** | Generic **`dvfs-scmi-cpufreq.c`** |
| **`RT_THERMAL_COOL_DVFS`** | **`thermal-cool-dvfs.c`** (also needs **`RT_USING_THERMAL`**) |
| **`RT_USING_IDLE_HOOK`** | Required for meaningful dynamic governor load stats |
| **`SOC_DM_DVFS_CPUFREQ_DIR`** | BSP CPUfreq driver(s) |
| **`SOC_DM_DVFS_DEVFREQ_DIR`** | BSP devfreq driver(s) |
| **`SOC_DM_DVFS_EVENT_DIR`** | BSP devfreq event source(s) |

---

## OPP transition order

When **`ops->set_opp`** is provided, the BSP defines the safe ramp sequence ( voltage-before-frequency on scale-up, etc.).

When the framework generic path is used (**`dvfs.c`**):

- **Scale up**: raise voltage (if needed) → optional **`transition_latency`** delay → **`rt_clk_set_rate`**
- **Scale down**: lower clock rate → lower voltage (if needed)

On failure, **`cur_freq`** and **`current_opp`** are not updated. **`RT_USING_DVFS_OPP_RETRY_MAX`** controls busy retries on regulator or clock calls.

---

## Pitfalls

- **BSP `set_opp` must match hardware**: clocks, regulators, and any bus used to change voltage must remain usable across the full OPP range. Broken I2C/SPI/regulator access during a transition surfaces as stuck frequency or **`-RT_EBUSY`** retries.
- **Governor switch vs. pending work**: dynamic governors schedule work on the system workqueue. After **`set_governor`**, monitor callbacks must verify the active governor type before changing frequency (see governor sources).
- **Thermal cooling levels**: **`thermal-cool-dvfs`** maps cooling **level** to an OPP index; releasing cooling must restore full performance (highest OPP), not the most restrictive level. See **`rt_thermal_cooling_device_kick`** in **`thermal.c`**.
- **Verifying dynamic governors**: do not run a tight CPU loop inside the **FinSH / shell thread** — it usually has higher priority than the system workqueue and can prevent load sampling. Use a **separate background thread** at lower priority, or compare **`performance`** vs **`powersave`** (static governors) to confirm the scaling path works before testing **`ondemand`** / **`schedutil`**.

---

## Related pages

- @ref page_device_clk — **`rt_clk_set_rate`**, consumer clock API
- @ref page_device_regulator — supply rails referenced from OPP / CPU nodes
- @ref page_device_scmi — SCMI clock/regulator when firmware owns scaling resources
- @ref page_device_thermal_cool — **`thermal-cool-dvfs`**
