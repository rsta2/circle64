Circle64
========

> Raspberry Pi is a trademark of the Raspberry Pi Foundation.

> If you read this file in an editor you should switch line wrapping on.

Overview
--------

The Circle64 project is discontinued. Please use the [Circle project](https://github.com/rsta2/circle) instead, which supports both 32-bit and 64-bit applications now!

Circle64 is a 64-bit C++ bare metal programming environment for the Raspberry Pi 3. It provides several ready-tested C++ classes which can be used to control different hardware features of the Raspberry Pi 3. Together with Circle there are delivered some samples which demonstrate the use of its classes.

This is a 64-bit port (using AArch64) of Circle (32-bit). At the moment there are only some basic features supported:

* 64-bit C++ build environment
* Simple delay functionality
* Get properties (model, memory size) from VideoCore
* new and delete
* Using GPIO pins
* Manipulating Act LED
* Set pixel on screen
* Use kernel options
* Formatting strings
* Using devices
* Writing characters to screen
* Writing characters to UART
* Logging output to screen or UART
* Using assertions and debug hexdump
* Using interrupts
* Timer class with clock, timers and calibrated delay loop
* Exception handler
* Using GPIO interrupts
* Switch on MMU
* Multi-core support

Have a look at [Circle (32-bit)](https://github.com/rsta2/circle) for further information.

Building
--------

Building is normally done on PC Linux. You need a toolchain with ARMv8 AArch64 (Cortex-A53) support. *gcc-linaro-7.3.1-2018.05-x86_64_aarch64-elf.tar.xz* which can be downloaded [here](https://releases.linaro.org/components/toolchain/binaries/latest-7/aarch64-elf/) should work.

First edit the file *Rules.mk* and set the *PREFIX* of your toolchain commands. Alternatively you can create a *Config.mk* file (which is ignored by git) and set the *PREFIX* variable to the prefix of your compiler like this (don't forget the dash at the end):

`PREFIX = aarch64-elf-`

Then go to the build root of Circle and do:

`./makeall clean`  
`./makeall`

By default only the latest sample (with the highest number) is build. The ready build *kernel.img* file should be in its subdirectory of sample/. If you want to build another sample after `makeall` go to its subdirectory and do `make`.

Installation
------------

Copy a recent Raspberry Pi firmware (from boot/ directory, do *make* there to get them) files along with the kernel8.img (from sample/ subdirectory) to a SD(HC) card with FAT file system. Put the SD(HC) card into the Raspberry Pi 3 and start it.

Directories
-----------

* include: The common header files, most class headers are in the include/circle/ subdirectory.
* lib: The Circle class implementation and support files.
* sample: Several sample applications using Circle in different subdirectories. The main function is implemented in the CKernel class.
* boot: Do *make* in this directory to get the Raspberry Pi firmware files required to boot.
