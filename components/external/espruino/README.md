Espruino JavaScript for Microcontrollers
========================================
<pre>
 _____                 _
|   __|___ ___ ___ _ _|_|___ ___
|   __|_ -| . |  _| | | |   | . |
|_____|___|  _|_| |___|_|_|_|___|
          |_|      
</pre>
http://www.espruino.com

**NOTE:** This software is beta and is provided as-is, and won't be considered even remotely final until we've released the Espruino Board. As such, don't expect support, and do expect it to change rapidly and without warning. Build your own documentation (see **Building**), as the API may be different from the one described on the Espruino website.

The KickStarter campaign said the Espruino Board will have some things which this repository does not yet have (like working CC3000 support). These are works in progress and should be done by the time you get your board (or will be available as a software update).


About
-----

It'd probably help to read the [FAQ](http://www.espruino.com/FAQ), and specifically the page about [Performance](http://www.espruino.com/Performance) as it contains information about how Espruino itself works.

There's also the auto-generated [Reference](http://www.espruino.com/Reference) for JavaScript commands as well as the [Tutorials](http://www.espruino.com/Tutorials) on the website. However please note that this repository is under heavy development, and the documentation on the Espruino website will match the version [available for download](http://www.espruino.com/Download) but **not** the latest version from Git.


License
-------

Please see the [LICENSE](LICENSE) file


Found a Bug?
------------

Please check that:
* It hasn't [already been found](https://github.com/espruino/Espruino/issues) or [been covered on our forum](www.espruino.com/Forum)
* You're not just looking at outdated documentation (See the [Building](#Building) section to see how to build documentation)

Please [submit bugs](https://github.com/espruino/Espruino/issues) with clear steps to reproduce them (and ideally a test case for the ```tests``` directory), and if at all possible try and include a patch to fix them. Please be aware that we have a whole bunch of outstanding issues (some quite large), so if you report something (especially if it doesn't contain a test or a pull request) it may not be fixed for quite some time.


Contributing
------------

Please see [CONTRIBUTING.md](CONTRIBUTING.md)

Current State
-------------

You can download binaries from http://www.espruino.com/Download (these aren't the latest, but are more likely to work with your board)

Please note that this is BETA. We've been working hard on the Espruino Board support but we haven't had time to check the other boards properly.

* Espruino Board - working
* Linux - working
* STM32VLDISCOVERY - WORKING
* STM32F3DISCOVERY - WORKING
* STM32F4DISCOVERY - WORKING
* STM32F429IDISCOVERY - not working, currently no LCD support
* HY STM32 2.4" - NOT WORKING - appears to crash after startup
* HY STM32 2.8" - WORKING, but screen is not black at startup
* HY STM32 3.2" - WORKING
* Olimexino - WORKING
* Carambola - ?
* Raspberry Pi - WORKING
* Sony SmartWatch - USB VCP support still needed
* MBed platforms - have not worked for a while - hardware wrapper still needed
* Arduino - has never worked. Compiles but doesn't even get past init
* LC-TECH STM32F103RBT6 - WORKING, but with some issues (LED inverted logic, BTN needs pullup to work)

Using
-----

If you're using Espruino for your own personal projects - go ahead, we hope you have fun - and please let us know what you do with it on http://www.espruino.com/Forum!

However if you're planning on selling the Espruino software on your own board, please talk to us:

* Read the terms of the MPLv2 Licence that Espruino is distributed under, and make sure you comply with it
* You won't be able to call your board 'Espruino' but you must explain clearly that it uses 'Espruino' internally (we own the trademark)
* If you're profiting from Espruino without contributing anything back, we won't support you (or your users)


Building
--------
  
Espruino is easy to build under Linux, and it is possible to build under MacOS. We'd strongly suggest that you DO NOT TRY AND BUILD UNDER WINDOWS, and instead use a Virtual Machine. There's a good post on this here: http://forum.espruino.com/conversations/151
  
We suggest that you use the CodeSourcery GCC compiler, but paths in Makefile may need changing...

```  BOARDNAME=1 RELEASE=1 make```

* See the top of Makefile for board names
* Without `RELEASE=1`, assertions are kept in the code (which is good for debugging, bad for performance + code size)
* `BOARDNAME=1 RELEASE=1 make serialflash` will flash to /dev/ttyUSB0 using the STM32 serial bootloader (what's needed for Espruino + HY boards)
* `BOARDNAME=1 RELEASE=1 make flash` will flash using st-flash if discovery, or maple bootloader if using that board

You can build documentation by running:

```  python scripts/build_docs.py ```

This will create a file called ```functions.html```

Directories and Files
---------------------

* `ChangeLog`:          What's new
* `TODO`:               List of things to do
* `boards/`:            Information on boards, used to auto-generate a lot of the code
* `code/`:              Example JavaScript code
* `gen/`:               Auto-Generated Source Files
* `libs/`:              Optional libraries to include in Espruino (Math, Filesystem, Graphics, etc)
* `linker/`:            Linker files for various processors
* `misc/`:              random other stuff
* `scripts/`:           Scripts for generating files in gen, and for analysing code/compilation/etc
* `src/`:               Main source code
* `targetlibs/`:        Libraries for targeted architectures
* `targets/`:           Specific code for targeted architectures
* `tests/`:             JavaScript Testcases
* `benchmark/`:         JavaScript Benchmarks
* `dist_*`:             files to be copied into distribution zip file

Adding more devices
-------------------

Currently there are a bunch of different files to modify. Eventually the plan is to fit everything into boards/BOARDNAME.py and to auto-generate the rest of the config files.

* Most build options handled in `Makefile`
* Extra libraries like USB/LCD/filesystem in `Makefile`
* Linker Scripts are in `linker/`
* `boards/*.py` files handle loading the list of available pins so the relevant headers + docs can be created
* Processor-specific code in `targets/stm32`, `targets/linux`, etc.
* Processor-specific libs in `targetlibs/foo` 
* `src/jshardware.h` is effectively a simple abstraction layer for SPI/I2C/etc
* `targets/stm32/jshardware.c` also has flash-size-specific defines
* `libs/fat_sd` and `libs/lcd` still have some device-specific defines in too

Adding libraries
-------------------

* Create `jswrap_mylib.c/h` in `libs/`
* Create library functions (see examples in other jswrap files, also the comments in `scripts/common.py`)


Arduino Compile (beta)
----------------------
* Ensure that `targets/arduino/utility` is symlinked to `src`
* Symlink `...arduino_workspace/libraries/Espruino` to `targets/arduino`

Cross Compile for Raspberry Pi
------------------------------
```
cd targetlibs
mkdir raspberrypi
cd raspberrypi
git clone git://github.com/raspberrypi/tools.git
sudo apt-get install ia32-libs
```

Cross Compile for Carambola (OpenWRT)
-------------------------------------
* Follow instructions at <https://github.com/8devices/carambola> to set toolchain up in ```~/workspace/carambola```
* Run ```CARAMBOLA=1 make```
