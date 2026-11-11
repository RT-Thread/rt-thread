@page page_device_nvmem NVMEM subsystem

# Non-volatile memory (NVMEM)

Header: **`components/drivers/include/drivers/nvmem.h`**. Core: **`components/drivers/nvmem/nvmem.c`**.

NVMEM models **OTP, eFuse, EEPROM slices, PMIC trim, MAC/calibration blobs** as a **provider device** plus **cells** (named or indexed byte/bit ranges). Consumers resolve cells from device tree phandles—see @ref page_device_nvmem_dm.

There is **no in-tree OTP driver** under **`components/drivers/nvmem/`**; SoC providers live under **`SOC_DM_NVMEM_DIR`** in the BSP.

---

## When to use NVMEM

| Use **`rt_nvmem_*`** when… | Use a dedicated driver when… |
| --- | --- |
| **Multiple consumers** need slices of one OTP/eFuse controller. | Only one driver reads a fixed offset once at boot. |
| DT uses **`nvmem-cells`** / **`nvmem-cell-names`** (Linux-style). | MAC/calibration is hard-coded in BSP C sources. |
| You want refcounted **`rt_nvmem_cell`** handles. | Direct MMIO in a single platform driver is enough. |

---

## Data structures

```c
struct rt_nvmem_device {
    struct rt_device parent;
    int cells_nr;
    rt_list_t cell_nodes;
    rt_ssize_t (*reg_read)(struct rt_nvmem_device *, int offset, void *val, rt_size_t bytes);
    rt_ssize_t (*reg_write)(struct rt_nvmem_device *, int offset, void *val, rt_size_t bytes);
    rt_ssize_t size;
    int word_size;
    int stride;
    rt_bool_t read_only;
    rt_bool_t ignore_wp;
    rt_base_t wp_pin;
    rt_uint8_t wp_pin_active;
    struct rt_ref ref;
    struct rt_spinlock spinlock;
    void *priv;
};
```

| Field | Role |
| --- | --- |
| **`reg_read` / `reg_write`** | Byte access at **`offset`** |
| **`read_only`** | DT **`read-only`**, no **`reg_write`**, or preset flag |
| **`wp_pin`** | Optional **`wp`** GPIO for EEPROM |

---

## Provider API

```c
rt_err_t rt_nvmem_device_register(struct rt_nvmem_device *ndev);
rt_err_t rt_nvmem_device_unregister(struct rt_nvmem_device *ndev);
rt_err_t rt_nvmem_device_append_cell(struct rt_nvmem_device *ndev, struct rt_nvmem_cell *cell);
```

**`register`**: optional **`wp`** pin, **`read_only`** from DT / missing **`reg_write`**, **`rt_ofw_data(np)=ndev`**.

**`unregister`**: only if **`rt_ref_read(&ndev->ref)==1`**.

**`append_cell`**: static cells (**`free_able` false**) known at probe time.

---

## Consumer API

```c
struct rt_nvmem_cell *rt_nvmem_get_cell_by_index(struct rt_device *dev, int index);
struct rt_nvmem_cell *rt_nvmem_get_cell_by_name(struct rt_device *dev, const char *id);
void rt_nvmem_put_cell(struct rt_nvmem_cell *cell);
rt_ssize_t rt_nvmem_cell_read(struct rt_nvmem_cell *cell, void *buffer, rt_size_t len);
rt_ssize_t rt_nvmem_cell_write(struct rt_nvmem_cell *cell, void *buffer, rt_size_t len);
```

- **`len <= cell->bytes`** and **`<= nvmem->size`**
- Bit fields: **`bit_offset`**, **`nbits`** — read shifts/masks; write read-modify-write
- **`wp_pin`** deasserted during **`reg_write`**
- Typed helpers: **`rt_nvmem_cell_read_u8/u16/u32/u64`**

---

## Example

```c
cell = rt_nvmem_get_cell_by_name(&pdev->parent, "mac-address");
if (!cell || rt_is_err_ptr(cell)) return -RT_ERROR;
rt_nvmem_cell_read(cell, mac, 6);
rt_nvmem_put_cell(cell);
```

---

## Pitfalls

| Issue | Mitigation |
| --- | --- |
| Forgot **`put_cell`** | Blocks unregister |
| OTP write | Omit **`reg_write`** |
| No BSP provider | **`SOC_DM_NVMEM_DIR`** |

---

## See also

- @ref page_device_nvmem_dm
- @ref page_device_iio_dm
- `components/drivers/nvmem/Kconfig`