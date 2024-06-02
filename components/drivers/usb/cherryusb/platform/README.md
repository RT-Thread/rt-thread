# Platform Support

This is a platform support for other os with their own components.

| Platform  |  fs          |  net         | serial       |
|:---------:|:------------:|:------------:|:------------:|
|none       |  fatfs       | lwip         |  none        |
|rtthread   |  dfs         | lwip         |  rt_device   |
|nuttx      |  nuttx block driver | nuttx net  |  nuttx char driver|
|threadx    |  filex       | netx         | none         |

- **fs** is for usbd_msc and usbh_msc
- **net** is for cdc_ecm, cdc_rndis, cdc_ncm, asix, rtl8152 and so on.
- **serial** is for cdc_acm, ch340, ftdi, cp210x, pl2303 and so on.