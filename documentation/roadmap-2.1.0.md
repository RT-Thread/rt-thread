# The Roadmap of RT-Thread v2.1.0 version #

Thank all of the developers and contributors, the final version of RT-Thread v2.0.0 has been released. The next version should be a small version, not always similar to the last version, which is a big version:-) The version number should be v2.1.0. There are lot of people ask me what's the features of next version. In fact, I would say, RT-Thread is an open source community, which the development of RT-Thread RTOS is depended by community, belonging to each community participants. If you want to let RT-Thread has some features, please implement it! Then share them to the community. If those part meet the RT-Thread rule (such as no license conflict), there is no reason that not to put them into the upstream of RT-Thread.

So more representatives mentioned below are my (Bernard) personal point of view:

1. CloudIDE, which is hosted on http://lab.rt-thread.org/cloudide, is an online IDE, ah, similar to mbed;-) But hope there are some own characteristics, and at least, it's faster in China. (When it's ready, we maybe setup a local IDE version.) It's in alpha phase right now, which introduces multi-tab edit mode; adding the Wi-Fi startkit hardware to update its firmware in fly; sharing snippets and components between developers; integrating help documentation and other information. The intention is to create a convenient way for newcomer, but not troubled by the development environment. Developers only need a web browser and the corresponding hardware, such as Wi-Fi startkit (which also is called as ART-wifi).

2. In embedded system salon which is held in Shanghai China, December of last year, developer Weety mentioned POSIX compatibility issue, which leading to not easy to port some Linux software to RT-Thread. The main problem here is that the BSD socket interface is entirely in lwIP protocol stack, while the file system interface of RT-Thread is another one. Therefore, RT-Thread has no unified select/read/write/poll function on socket/file descriptor/device; Another implicit problem is, POSIX implementation is not completed standard. There may be some pits inside. This issue is a big problem, since we chose the open source system, then he/she must also take into account the open source ecosystem as well. There are many open source resources you can use or re-use. Therefore, RT-Thread also need to be more open attitude to solve this problem so that it can be more open, to enhance the affinity of the POSIX standard itself. Similarly, it should be better supported for some of the C ++ standard. RT-Thread will be more POSIX, more open. RT-Thread is there, and how to create a better application, it's up to the user's innovation.

3. Some rich feature SoC, such as the number of new pop package ARM9 (With built-in SDRAM/DDR), Cortex-A7/8/9, MIPS32/64, or even x86, these SoC will be certainly and gradually evolved into the RT-Thread target hardware platform, but the work should be heavier. If the above No.2 POSIX issue resolved, it's possible to support them. The primary working is the driver implementation, and then integrated with POSIX interface, it will be easier to port other components. 

From my side of the energy can put into it, I should be focusing my working on the building up the platform, so that RT-Thread can be more POSIX, more standardized, more open and easy to use. The current planning point is to release RT-Thread v2.1.0 alpha version on the end of Q1 2015. This version should include dfs_lwIP file system interface, and then make sure the branch direction.

The others, the following list are some thought but no obligation feature list, please interested guys come to claim, thanks:

* CloudIDE related
  - Improve the NAT function, turns ART-wifi board into a Wi-Fi repeater (routing).
  - Look forward to sharing MQTT/CoAP components on CloudIDE;
  - Look forward to adding Wi-Fi/6LoWPAN gateway in the ART-wifi startkit.
  - Look forward to adding Wi-Fi/nRF51822 BLE gateway in the ART-wifi startkit.
  - Look forward to turning the ART-wifi startkit as a multi-axis flight control, and porting some algorighms in PX4 project;
  - Look forward to sharing Lewei50/Yeelink access component on CloudIDE;
  - Look forward to sharing SSL component on CloudIDE;
  - Look forward to sharing components on CloudIDE to access Ali cloud, Baidu cloud, Tencent cloud etc;

  - Add more sensors driver, e.g., barometer, thermometer, illumination, 9-axis sensor etc;

  - Look forward to integrating RealBoard LPC4088 APP development environment on CloudIDE;
  - Look forward to integrating UI design feature on CloudIDE;
  - Look forward to turnning CloudIDE become a local desktop application;

* POSIX-related
  - Implement dfs_lwIP file system interface for DFS fd/lwIP socket interface. To implement select/poll interface before DFS;
  - More better integration between DFS and device file system interface(devfs). 
  - Add more POSIX interfaces, including but not limited to aio, signal and other functions etc;
  - Improve DeviceDriver framework for device interfaces (rt_device_*). Application layer uses rt_device_* and devfs interface, firmware/driver developer uses device driver framework interface.

* Others
  - Porting TCP/IP protocol stack and POSIX environmemnt in OpenBSD;
  - CanOpen component;
  - ARM Cortex-A8/A9 + M4/M3 hardware platform;
  - Some other hardware porting;




Bernard Xiong
2015.2.26

