@page page_device_tee TEE subsystem

# TEE subsystem (API)

Header: **`components/drivers/include/drivers/tee.h`**. Core: **`components/drivers/tee/tee.c`**.

The TEE layer provides a **GlobalPlatform-style** client API for talking to a **Trusted Execution Environment** from the normal world. Hardware or firmware backends implement **`rt_tee_ops`** (version query, session management, command invocation, shared memory registration). The core serializes access with a per-device mutex, tracks registered shared-memory objects, and registers a searchable device node (`tee0`, `tee1`, …).

An **OP-TEE** backend lives under **`components/drivers/tee/optee/`** and is selected when **`RT_TEE_OPTEE`** is enabled.

Requires **`RT_USING_TEE`** (Kconfig) and **`RT_USING_DM`**.

---

## When to use this API

| Use TEE when… | Prefer something else when… |
| --- | --- |
| The platform runs **OP-TEE** (or another GP-compliant TEE) and exposes **Trusted Applications (TAs)**. | Secrets can stay in normal-world software with adequate isolation — no TEE required. |
| You need **crypto, secure storage, or RNG** inside a TA with a defined UUID/command model. | Single-purpose on-chip crypto — a dedicated **hwcrypto** driver may suffice. |
| Firmware provides a DT node such as **`linaro,optee-tz`**. | No secure world firmware — enable and port a TEE OS first. |

---

## Enable in menuconfig

```text
RT-Thread Components →
    Device Drivers →
        [*] Using Trusted Execution Environment (TEE) support
            [*] OP-TEE                    # ARCH_ARM_CORTEX_A || ARCH_ARMV8
                [*] Examples              # FinSH command optee_example_rng
```

SoC-specific backends may be added under **`$(SOC_DM_TEE_DIR)/Kconfig`** when present.

---

## Roles

| Role | Responsibility |
| --- | --- |
| **TEE backend driver** | Embeds **`struct rt_tee_device`**, fills **`rt_tee_ops`**, calls **`rt_tee_device_register`**. Translates GP requests to SMC/HVC, mailbox, or other transport. |
| **Client / TA user** | Finds **`tee0`**, opens a session to a TA UUID, registers shared memory, invokes TA commands. Checks both **`rt_err_t`** (transport) and **`arg->ret`** (TEE status). |

The core registers each device as **`RT_Device_Class_Char`** with **`RT_DEVICE_FLAG_DEACTIVATE`**. There is **no** generic `read`/`write`/`control` path in **`tee.c`** — use the **`rt_tee_*`** helpers.

All public entry points take **`tdev->mutex`** except registration helpers.

---

## Data structures

### Device object

```c
struct rt_tee_device {
    struct rt_device parent;
    rt_list_t shm_nodes;              /* registered struct rt_tee_shm */
    const struct rt_tee_ops *ops;
    struct rt_mutex mutex;
};

#define rt_device_to_tee_device(dev) rt_container_of(dev, struct rt_tee_device, parent)
```

### Version and capabilities

```c
struct rt_tee_version {
    rt_uint32_t impl_id;    /* TEE_IMPL_ID_OPTEE, TEE_IMPL_ID_AMDTEE, … */
    rt_uint32_t impl_caps;  /* e.g. TEE_OPTEE_CAP_TZ */
    rt_uint32_t gen_caps;   /* TEE_GEN_CAP_GP, TEE_GEN_CAP_REG_MEM, … */
};
```

### Parameters (open session / invoke)

Parameters follow GlobalPlatform attribute encoding:

| `attr` | Meaning |
| --- | --- |
| `TEE_PARAM_ATTR_TYPE_NONE` | Unused slot |
| `TEE_PARAM_ATTR_TYPE_VALUE_IN/OUT/IN_OUT` | Three 64-bit values in **`value.a/b/c`** |
| `TEE_PARAM_ATTR_TYPE_MEMREF_IN/OUT/IN_OUT` | Shared memory reference via **`memref.shm`**, offset, size |

Flexible arrays append parameters to the end of open/invoke argument blocks:

```c
struct rt_tee_open_session_arg {
    rt_uint8_t uuid[16];
    rt_uint8_t clnt_uuid[16];
    rt_uint32_t clnt_login;
    rt_uint32_t cancel_id;
    rt_uint32_t session;       /* output: session id from TEE */
    rt_uint32_t ret;           /* output: TEE result code */
    rt_uint32_t ret_origin;    /* output: RT_TEE_ORIGIN_* */
    rt_uint32_t params_nr;
    struct rt_tee_param params[];
};

struct rt_tee_invoke_arg {
    rt_uint32_t func;
    rt_uint32_t session;
    rt_uint32_t cancel_id;
    rt_uint32_t ret;
    rt_uint32_t ret_origin;
    rt_uint32_t params_nr;
    struct rt_tee_param params[];
};
```

### Shared memory

```c
struct rt_tee_shm {
    rt_list_t list;
    struct rt_tee_device *tdev;
    void *vaddr;
    rt_ubase_t paddr;
    rt_size_t size;
    rt_size_t align;
    rt_uint32_t flags;   /* TEE_SHM_DRV | TEE_SHM_SYS | TEE_SHM_USER */
};
```

| Flag | Usage |
| --- | --- |
| **`TEE_SHM_SYS`** | Core allocates backing store in **`rt_tee_shm_register`** via **`rt_tee_shm_alloc_helper`** (page allocator or aligned malloc). Caller must **`rt_tee_shm_free_helper`** after unregister. |
| **`TEE_SHM_USER`** | Caller supplies **`vaddr`** (and optionally **`paddr`**); core resolves physical address when missing. |
| **`TEE_SHM_DRV`** | Driver-owned buffer; registration requires **`vaddr`** already set. |

### Driver operations

```c
struct rt_tee_ops {
    rt_err_t (*get_version)(struct rt_tee_device *tdev, struct rt_tee_version *out_version);
    rt_err_t (*open_session)(struct rt_tee_device *tdev, struct rt_tee_open_session_arg *arg);
    rt_err_t (*close_session)(struct rt_tee_device *tdev, rt_uint32_t session);
    rt_err_t (*invoke)(struct rt_tee_device *tdev, struct rt_tee_invoke_arg *arg);
    rt_err_t (*cancel)(struct rt_tee_device *tdev, rt_uint32_t session, rt_uint32_t cancel_id);
    rt_err_t (*shm_register)(struct rt_tee_device *tdev, struct rt_tee_shm *shm);
    rt_err_t (*shm_unregister)(struct rt_tee_device *tdev, struct rt_tee_shm *shm);
};
```

---

## TEE result codes

Transport failures use **`rt_err_t`** (`-RT_EINVAL`, `-RT_ENOMEM`, `-RT_ENOSYS`, …). TEE-side status is returned in **`arg->ret`** with origin **`arg->ret_origin`**:

| Code | Macro |
| --- | --- |
| Success | **`RT_TEE_SUCCESS`** (`0`) |
| Bad parameters | **`RT_TEE_ERROR_BAD_PARAMETERS`** |
| Not supported | **`RT_TEE_ERROR_NOT_SUPPORTED`** |
| Out of memory | **`RT_TEE_ERROR_OUT_OF_MEMORY`** |
| Communication error | **`RT_TEE_ERROR_COMMUNICATION`** |
| … | See **`tee.h`** for the full list |

Origins: **`RT_TEE_ORIGIN_COMMS`**, **`RT_TEE_ORIGIN_TEE`**, **`RT_TEE_ORIGIN_TRUSTED_APP`**.

Always check **both** the function return value and **`arg->ret`** on open/invoke.

---

## Register and unregister

```c
rt_err_t rt_tee_device_register(struct rt_tee_device *tdev);
rt_err_t rt_tee_device_unregister(struct rt_tee_device *tdev);
```

**`rt_tee_device_register`** requires **`tdev`** and **`tdev->ops`**. Device name is **`tee<N>`**.

**`rt_tee_device_unregister`**:

- Fails if **`ref_count != 0`**
- Warns and force-unregisters SHM entries if any remain on **`shm_nodes`**
- Detaches **`mutex`** after successful device unregister

---

## Session and command API

```c
rt_err_t rt_tee_get_version(struct rt_tee_device *tdev, struct rt_tee_version *out_version);

rt_err_t rt_tee_open_session(struct rt_tee_device *tdev, struct rt_tee_open_session_arg *arg);
rt_err_t rt_tee_close_session(struct rt_tee_device *tdev, rt_uint32_t session);

rt_err_t rt_tee_invoke(struct rt_tee_device *tdev, struct rt_tee_invoke_arg *arg);
rt_err_t rt_tee_cancel(struct rt_tee_device *tdev, rt_uint32_t session, rt_uint32_t cancel_id);
```

Typical flow:

1. Allocate **`open_session_arg`** with room for trailing **`params[]`**
2. Fill **`uuid`** (TA) and optional client identity fields
3. **`rt_tee_open_session`** — on success read **`arg->session`**, verify **`arg->ret == RT_TEE_SUCCESS`**
4. Register SHM if the TA command needs buffers
5. Allocate **`invoke_arg`**, set **`func`**, **`session`**, parameters
6. **`rt_tee_invoke`** — verify **`arg->ret`**
7. **`rt_tee_close_session`**, unregister/free SHM, close device

---

## Shared memory helpers

```c
rt_err_t rt_tee_shm_alloc_helper(struct rt_tee_shm *shm);
rt_err_t rt_tee_shm_free_helper(struct rt_tee_shm *shm);
rt_err_t rt_tee_shm_register(struct rt_tee_device *tdev, struct rt_tee_shm *shm);
rt_err_t rt_tee_shm_unregister(struct rt_tee_device *tdev, struct rt_tee_shm *shm);
```

**`rt_tee_shm_register`**:

- For **`TEE_SHM_SYS`** (without **`TEE_SHM_DRV`**): allocates memory, then calls **`ops->shm_register`**
- On backend failure after allocation, frees the buffer automatically
- On success, links **`shm`** into **`tdev->shm_nodes`**

**`rt_tee_shm_unregister`** removes the node and calls **`ops->shm_unregister`**. Call **`rt_tee_shm_free_helper`** afterward when the core allocated the buffer.

---

## OP-TEE backend

**Files:** `components/drivers/tee/optee/optee.c`, `optee_msg.h`, `optee_smc.h`

**Platform driver:** `optee-smc`, compatible **`linaro,optee-tz`**

### Device tree

| Property | Values | Notes |
| --- | --- | --- |
| **`compatible`** | `"linaro,optee-tz"` | Required |
| **`method`** | `"smc"` (default) or `"hvc"` | Selects **`arm_smccc_smc`** vs **`arm_smccc_hvc`** |

### Probe requirements

At probe time the driver:

1. Selects SMC or HVC call path from **`method`**
2. Verifies OP-TEE UID via **`OPTEE_SMC_CALLS_UID`**
3. Requires **`OPTEE_SMC_SEC_CAP_DYNAMIC_SHM`** from capability exchange
4. Registers **`struct rt_tee_device`** with **`optee_ops`**

### Normal-world supplicant (RPC)

**`call_with_arg`** handles OP-TEE **RPC** returns while a secure-world call is in flight:

| RPC function | Handled behavior |
| --- | --- |
| **`OPTEE_SMC_RPC_FUNC_ALLOC` / `FREE`** | Temporary RPC buffer alloc/free |
| **`OPTEE_SMC_RPC_FUNC_CMD`** | **`supplicant_cmd`**: SHM alloc/free, optional **I2C transfer** (`RT_USING_I2C`) |
| **`OPTEE_SMC_RPC_FUNC_FOREIGN_INTR`** | No-op placeholder |

Shared memory passed to the secure world uses **non-contiguous page lists** built from physically contiguous normal-world pages.

### FinSH example

With **`RT_TEE_OPTEE_EXAMPLES`**, build OP-TEE for your platform with the **hwrng** TA (see [OP-TEE QEMU documentation](https://optee.readthedocs.io/en/latest/building/devices/qemu.html#qemu-v8)), then run:

```text
optee_example_rng
```

The example opens **`tee0`**, opens a session to the hwrng TA UUID, registers a 32-byte output buffer, invokes command **`0x0` (GET_ENTROPY)**, and prints the result.

Source: **`components/drivers/tee/optee/optee_examples.c`**

---

## Example (client sketch)

```c
#include <drivers/tee.h>

static struct rt_tee_open_session_arg *open_arg_alloc(rt_uint32_t n)
{
    return rt_calloc(1, sizeof(struct rt_tee_open_session_arg) +
                        sizeof(struct rt_tee_param) * n);
}

static void uuid_to_bytes(rt_uint8_t *d, struct rt_tee_uuid *s)
{
    d[0] = s->time_low >> 24;
    d[1] = s->time_low >> 16;
    d[2] = s->time_low >> 8;
    d[3] = s->time_low;
    d[4] = s->time_mid >> 8;
    d[5] = s->time_mid;
    d[6] = s->time_hi_and_version >> 8;
    d[7] = s->time_hi_and_version;
    rt_memcpy(d + 8, s->clock_seq_and_node, 8);
}

static int ta_example(struct rt_tee_device *tdev)
{
    rt_err_t err;
    struct rt_tee_shm shm = { .size = 64, .align = RT_MM_PAGE_SIZE, .flags = TEE_SHM_SYS };
    struct rt_tee_open_session_arg *open;
    struct rt_tee_invoke_arg *invoke;
    struct rt_tee_uuid ta_uuid = { /* TA UUID fields */ };

    open = open_arg_alloc(0);
    uuid_to_bytes(open->uuid, &ta_uuid);

    if ((err = rt_tee_open_session(tdev, open)) != RT_EOK || open->ret != RT_TEE_SUCCESS)
        goto out;

    if ((err = rt_tee_shm_register(tdev, &shm)) != RT_EOK)
        goto close;

    invoke = rt_calloc(1, sizeof(*invoke) + sizeof(struct rt_tee_param));
    invoke->func = 1;
    invoke->session = open->session;
    invoke->params_nr = 1;
    invoke->params[0].attr = TEE_PARAM_ATTR_TYPE_MEMREF_OUT;
    invoke->params[0].memref.shm = &shm;
    invoke->params[0].memref.size = shm.size;

    err = rt_tee_invoke(tdev, invoke);
    if (err == RT_EOK && invoke->ret == RT_TEE_SUCCESS) {
        /* use shm.vaddr */
    }

    rt_free(invoke);
    rt_tee_shm_unregister(tdev, &shm);
    rt_tee_shm_free_helper(&shm);

close:
    rt_tee_close_session(tdev, open->session);
out:
    rt_free(open);
    return (int)err;
}
```

### Device lookup

```c
struct rt_device *dev = rt_device_find("tee0");
struct rt_tee_device *tdev;

if (dev && rt_device_open(dev, 0) == RT_EOK)
    tdev = rt_device_to_tee_device(dev);
```

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| **Ignoring `arg->ret`** | **`RT_EOK`** from **`rt_tee_invoke`** only means the message reached the backend; check **`invoke->ret`**. |
| **SHM leak** | Always **`rt_tee_shm_unregister`** then **`rt_tee_shm_free_helper`** for **`TEE_SHM_SYS`** buffers. |
| **Unregister with active refs** | **`rt_tee_device_unregister`** fails when **`ref_count != 0`** — close clients first. |
| **OP-TEE without dynamic SHM** | Probe fails if **`OPTEE_SMC_SEC_CAP_DYNAMIC_SHM`** is absent — use a matching OP-TEE build. |
| **Missing TA** | **`RT_TEE_ERROR_ITEM_NOT_FOUND`** / session open failure — deploy the TA binary to OP-TEE. |
| **I2C RPC** | OP-TEE I2C supplicant calls require **`RT_USING_I2C`** and a bus named **`i2c<N>`**. |
| **Cache coherency** | OP-TEE backend flushes/invalidates caches around shared message buffers; user SHM must remain in memory visible to both worlds. |

---

## See also

- [OP-TEE documentation](https://optee.readthedocs.io/)
- `components/drivers/tee/tee.c`
- `components/drivers/tee/optee/optee.c`
- `components/drivers/include/drivers/tee.h`
