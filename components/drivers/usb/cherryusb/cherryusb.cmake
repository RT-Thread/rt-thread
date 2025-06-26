#
# Copyright (c) 2024, sakumisu
#
# SPDX-License-Identifier: Apache-2.0
#

# cmake-format: off

# set(CONFIG_CHERRYUSB_DEVICE 1)
# set(CONFIG_CHERRYUSB_DEVICE_CDC 1)
# set(CONFIG_CHERRYUSB_DEVICE_HID 1)
# set(CONFIG_CHERRYUSB_DEVICE_MSC 1)
# set(CONFIG_CHERRYUSB_DEVICE_AUDIO 1)
# set(CONFIG_CHERRYUSB_DEVICE_VIDEO 1)
# set(CONFIG_CHERRYUSB_DEVICE_DWC2_ST 1)

# set(CONFIG_CHERRYUSB_HOST 1)
# set(CONFIG_CHERRYUSB_HOST_CDC_ACM 1)
# set(CONFIG_CHERRYUSB_HOST_CDC_ECM 1)
# set(CONFIG_CHERRYUSB_HOST_CDC_NCM 1)
# set(CONFIG_CHERRYUSB_HOST_HID 1)
# set(CONFIG_CHERRYUSB_HOST_MSC 1)
# set(CONFIG_CHERRYUSB_HOST_VIDEO 1)
# set(CONFIG_CHERRYUSB_HOST_AUDIO 1)
# set(CONFIG_CHERRYUSB_HOST_CDC_RNDIS 1)
# set(CONFIG_CHERRYUSB_HOST_BLUETOOTH 1)
# set(CONFIG_CHERRYUSB_HOST_ASIX 1)
# set(CONFIG_CHERRYUSB_HOST_RTL8152 1)
# set(CONFIG_CHERRYUSB_HOST_DWC2_ST 1)

# set(CONFIG_CHERRYUSB_OSAL "freertos")
# cmake-format: on

list(
    APPEND
    cherryusb_incs
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/common
    ${CMAKE_CURRENT_LIST_DIR}/core
    ${CMAKE_CURRENT_LIST_DIR}/class/hub
    ${CMAKE_CURRENT_LIST_DIR}/class/cdc
    ${CMAKE_CURRENT_LIST_DIR}/class/hid
    ${CMAKE_CURRENT_LIST_DIR}/class/msc
    ${CMAKE_CURRENT_LIST_DIR}/class/audio
    ${CMAKE_CURRENT_LIST_DIR}/class/video
    ${CMAKE_CURRENT_LIST_DIR}/class/wireless
    ${CMAKE_CURRENT_LIST_DIR}/class/midi
    ${CMAKE_CURRENT_LIST_DIR}/class/adb
    ${CMAKE_CURRENT_LIST_DIR}/class/dfu
    ${CMAKE_CURRENT_LIST_DIR}/class/vendor/net
    ${CMAKE_CURRENT_LIST_DIR}/class/vendor/serial
    ${CMAKE_CURRENT_LIST_DIR}/class/vendor/wifi
    ${CMAKE_CURRENT_LIST_DIR}/class/aoa
)

if(CONFIG_CHERRYUSB_DEVICE)
    list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/core/usbd_core.c)
    if(CONFIG_CHERRYUSB_DEVICE_CDC_ACM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/cdc/usbd_cdc_acm.c)
    endif()
    if(CONFIG_CHERRYUSB_DEVICE_HID)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/hid/usbd_hid.c)
    endif()
    if(CONFIG_CHERRYUSB_DEVICE_MSC)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/msc/usbd_msc.c)
    endif()
    if(CONFIG_CHERRYUSB_DEVICE_AUDIO)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/audio/usbd_audio.c)
    endif()
    if(CONFIG_CHERRYUSB_DEVICE_VIDEO)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/video/usbd_video.c)
    endif()
    if(CONFIG_CHERRYUSB_DEVICE_CDC_ECM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/cdc/usbd_cdc_ecm.c)
    endif()
    if(CONFIG_CHERRYUSB_DEVICE_CDC_NCM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/cdc/usbd_cdc_ncm.c)
    endif()
    if(CONFIG_CHERRYUSB_DEVICE_CDC_RNDIS)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/wireless/usbd_rndis.c)
    endif()
    if(CONFIG_CHERRYUSB_DEVICE_DFU)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/dfu/usbd_dfu.c)
    endif()
    if(CONFIG_CHERRYUSB_DEVICE_ADB)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/adb/usbd_adb.c)
    endif()

    if(CONFIG_CHERRYUSB_DEVICE_FSDEV_ST)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/fsdev/usb_dc_fsdev.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/fsdev/usb_glue_st.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_FSDEV_CUSTOM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/fsdev/usb_dc_fsdev.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_DWC2_ST)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_dc_dwc2.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_glue_st.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_DWC2_ESP)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_dc_dwc2.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_glue_esp.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_DWC2_KENDRYTE)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_dc_dwc2.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_glue_kendryte.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_DWC2_AT)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_dc_dwc2.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_glue_at.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_DWC2_HC)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_dc_dwc2.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_glue_hc.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_DWC2_GD)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_dc_dwc2.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_glue_gd.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_DWC2_CUSTOM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_dc_dwc2.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_MUSB_ES)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_dc_musb.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_glue_es.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_MUSB_SUNXI)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_dc_musb.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_glue_sunxi.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_MUSB_BK)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_dc_musb.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_glue_bk.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_MUSB_CUSTOM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_dc_musb.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_CHIPIDEA_MCX)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/chipidea/usb_dc_chipidea.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/nxp/usb_glue_mcx.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_KINETIS_MCX)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/kinetis/usb_dc_kinetis.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/kinetis/usb_glue_mcx.c)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/chipidea)
    elseif(CONFIG_CHERRYUSB_DEVICE_CHIPIDEA_CUSTOM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/chipidea/usb_dc_chipidea.c)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/chipidea)
    elseif(CONFIG_CHERRYUSB_DEVICE_HPM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/hpmicro/usb_dc_hpm.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/hpmicro/usb_glue_hpm.c)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/hpmicro)
    elseif(CONFIG_CHERRYUSB_DEVICE_BL)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/bouffalolab/usb_dc_bl.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_AIC)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/aic/usb_dc_aic.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/aic/usb_dc_aic_ll.c)
    elseif(CONFIG_CHERRYUSB_DEVICE_RP2040)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/rp2040/usb_dc_rp2040.c)
    endif()

endif()

if(CONFIG_CHERRYUSB_HOST)
    list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/core/usbh_core.c
         ${CMAKE_CURRENT_LIST_DIR}/class/hub/usbh_hub.c
    )

    if(CONFIG_CHERRYUSB_HOST_CDC_ACM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/cdc/usbh_cdc_acm.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_CDC_ECM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/cdc/usbh_cdc_ecm.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_CDC_RNDIS)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/wireless/usbh_rndis.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_CDC_NCM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/cdc/usbh_cdc_ncm.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_HID)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/hid/usbh_hid.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_MSC)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/msc/usbh_msc.c)

        if(CONFIG_CHERRYUSB_HOST_MSC_FATFS)
            list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/third_party/fatfs-0.14/source/port/fatfs_usbh.c)
            list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/third_party/fatfs-0.14/source/diskio.c)
            list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/third_party/fatfs-0.14/source/ff.c)
            list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/third_party/fatfs-0.14/source/ffsystem.c)
            list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/third_party/fatfs-0.14/source/ffunicode.c)

            list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/third_party/fatfs-0.14/source)
        endif()
    endif()
    if(CONFIG_CHERRYUSB_HOST_VIDEO)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/video/usbh_video.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_AUDIO)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/audio/usbh_audio.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_BLUETOOTH)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/wireless/usbh_bluetooth.c)

        set(BLUETOOTH_PATH ${CMAKE_CURRENT_LIST_DIR}/third_party/zephyr_bluetooth-2.7.5)

        list(
            APPEND
            cherryusb_srcs
            ${BLUETOOTH_PATH}/ble_hci_usbh.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/beacon/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/central/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/central_hr/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/central_ht/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/central_multilink/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/central_multilink/src/central_multilink.c
            # ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/handsfree/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/ibeacon/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral/src/cts.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_csc/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_dis/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_esp/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_hids/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_hids/src/hog.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_hr/src/main.c
            # ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_ht/src/main.c
            # ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_ht/src/hts.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_identity/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_identity/src/peripheral_identity.c
            # ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_ots/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/peripheral_sc_only/src/main.c
            ${BLUETOOTH_PATH}/zephyr_bluetooth/examples/scan_adv/src/main.c
        )

        include(${BLUETOOTH_PATH}/zephyr_bluetooth/zephyr_bluetooth.cmake)
        list(APPEND cherryusb_srcs ${zephyr_bluetooth_srcs})
        list(APPEND cherryusb_incs ${zephyr_bluetooth_incs})
    endif()

    if(CONFIG_CHERRYUSB_HOST_ASIX)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/vendor/net/usbh_asix.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_RTL8152)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/vendor/net/usbh_rtl8152.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_CH34X)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/vendor/serial/usbh_ch34x.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_CP210X)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/vendor/serial/usbh_cp210x.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_FTDI)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/vendor/serial/usbh_ftdi.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_PL2303)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/vendor/serial/usbh_pl2303.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_BL616)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/vendor/wifi/usbh_bl616.c)
    endif()
    if(CONFIG_CHERRYUSB_HOST_AOA)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/class/aoa/usbh_aoa.c)
    endif()

    if(CONFIG_CHERRYUSB_HOST_CDC_ECM
    OR CONFIG_CHERRYUSB_HOST_CDC_RNDIS
    OR CONFIG_CHERRYUSB_HOST_CDC_NCM
    OR CONFIG_CHERRYUSB_HOST_ASIX
    OR CONFIG_CHERRYUSB_HOST_RTL8152
    OR CONFIG_CHERRYUSB_HOST_BL616
    )
        if("${CONFIG_CHERRYUSB_OSAL}" STREQUAL "idf")
            list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/platform/idf/usbh_net.c)
        else()
            list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/platform/lwip/usbh_lwip.c)
        endif()
    endif()

    if(CONFIG_CHERRYUSB_HOST_EHCI_BL)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_hc_ehci.c)
        # list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_hc_ehci_iso.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_glue_bouffalo.c)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/ehci)
    elseif(CONFIG_CHERRYUSB_HOST_EHCI_HPM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_hc_ehci.c)
        # list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_hc_ehci_iso.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/hpmicro/usb_hc_hpm.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/hpmicro/usb_glue_hpm.c)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/hpmicro)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/ehci)
    elseif(CONFIG_CHERRYUSB_HOST_EHCI_AIC)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_hc_ehci.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ohci/usb_hc_ohci.c)
        # list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_hc_ehci_iso.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_glue_aic.c)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/ehci)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/ohci)
    elseif(CONFIG_CHERRYUSB_HOST_EHCI_MCX)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_hc_ehci.c)
        # list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_hc_ehci_iso.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/nxp/usb_glue_mcx.c)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/ehci)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/chipidea)
    elseif(CONFIG_CHERRYUSB_HOST_EHCI_CUSTOM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_hc_ehci.c)
        # list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/ehci/usb_hc_ehci_iso.c)
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/port/ehci)
    elseif(CONFIG_CHERRYUSB_HOST_DWC2_ST)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_hc_dwc2.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_glue_st.c)
    elseif(CONFIG_CHERRYUSB_HOST_DWC2_ESP)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_hc_dwc2.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_glue_esp.c)
    elseif(CONFIG_CHERRYUSB_HOST_DWC2_KENDRYTE)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_hc_dwc2.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_glue_kendryte.c)
    elseif(CONFIG_CHERRYUSB_HOST_DWC2_HC)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_hc_dwc2.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_glue_hc.c)
    elseif(CONFIG_CHERRYUSB_HOST_DWC2_CUSTOM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/dwc2/usb_hc_dwc2.c)
    elseif(CONFIG_CHERRYUSB_HOST_MUSB_ES)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_hc_musb.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_glue_es.c)
    elseif(CONFIG_CHERRYUSB_HOST_MUSB_SUNXI)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_hc_musb.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_glue_sunxi.c)
    elseif(CONFIG_CHERRYUSB_HOST_MUSB_BK)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_hc_musb.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_glue_bk.c)
    elseif(CONFIG_CHERRYUSB_HOST_MUSB_CUSTOM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_hc_musb.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/musb/usb_glue_bk.c)
    elseif(CONFIG_CHERRYUSB_HOST_KINETIS_MCX)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/kinetis/usb_hc_kinetis.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/kinetis/usb_glue_mcx.c)
    elseif(CONFIG_CHERRYUSB_HOST_KINETIS_CUSTOM)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/kinetis/usb_hc_kinetis.c)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/kinetis/usb_glue_mcx.c)
    elseif(CONFIG_CHERRYUSB_HOST_RP2040)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/port/rp2040/usb_hc_rp2040.c)
    endif()

    if(CHERRYUSB_HOST_TEMPLATE)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/demo/usb_host.c)
    endif()
endif()

if(DEFINED CONFIG_CHERRYUSB_OSAL)
    if("${CONFIG_CHERRYUSB_OSAL}" STREQUAL "freertos")
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/osal/usb_osal_freertos.c)
    elseif("${CONFIG_CHERRYUSB_OSAL}" STREQUAL "rtthread")
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/osal/usb_osal_rtthread.c)
    elseif("${CONFIG_CHERRYUSB_OSAL}" STREQUAL "idf")
        list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/osal/idf)
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/osal/idf/usb_osal_idf.c)
    elseif("${CONFIG_CHERRYUSB_OSAL}" STREQUAL "threadx")
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/osal/usb_osal_threadx.c)
    elseif("${CONFIG_CHERRYUSB_OSAL}" STREQUAL "zephyr")
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/osal/usb_osal_zephyr.c)
    endif()
endif()

if(CONFIG_CHERRYRB)
    list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/third_party/cherryrb/chry_ringbuffer.c)
    list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/third_party/cherryrb)
endif()

if(CONFIG_CHERRYMP)
    list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/third_party/cherrymp/chry_mempool.c)
    list(APPEND cherryusb_incs ${CMAKE_CURRENT_LIST_DIR}/third_party/cherrymp)
    if("${CONFIG_CHERRYUSB_OSAL}" STREQUAL "freertos")
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/third_party/cherrymp/chry_mempool_osal_freertos.c)
    elseif("${CONFIG_CHERRYUSB_OSAL}" STREQUAL "rtthread")
        list(APPEND cherryusb_srcs ${CMAKE_CURRENT_LIST_DIR}/third_party/cherrymp/chry_mempool_osal_rtthread.c)
    endif()
endif()
