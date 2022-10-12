# nuwriter_scripts

Some scripts can help you program firmware into storages in this folder.

## Requirement

### [Python for Window](https://www.python.org/downloads/windows/)

After installing Python, some plug-in as below must be installed.
```bash
$ pip3 install pyusb usb crypto ecdsa crcmod tqdm pycryptodome
```

### [Libusb for Window](http://sourceforge.net/projects/libusb/files/libusb-1.0/libusb-1.0.20/libusb-1.0.20.7z/download)

In Windows platform, it is required to install libusb manually.

```bash
Step 1: Download the library extract the download file.
Step 2: Copy MS64\dll\libusb-1.0.dll to C:\Windows\System32.
Step 3: Copy MS64\dll\libusb-1.0.lib to C:\Users\<user name>\AppData\Local\Programs\Python\<python ver>\Lib.
```

## Double-click Scripts for Windows

### nuwriter_ddr_download_and_run.bat

Download rtthread.bin binary file into DDR. The address is 0x80400000.

### nuwriter_sd_programming.bat

Program header, DDR timing setting and rtthread.bin binary file into SD card or EMMC.

### nuwriter_spinand_programming.bat

Program header, DDR timing setting and rtthread.bin binary file into SPI NAND flash.

### nuwriter_nand_programming.bat

Program header, DDR timing setting and rtthread.bin binary file into NAND flash.


### See also
[NuWriter Repository](https://github.com/OpenNuvoton/MA35D1_NuWriter)
