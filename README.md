# libvpx++

A C++ wrapper of [libvpx](http://www.webmproject.org)

## Build and install

### Arch Linux

Download [AUR package](https://aur.archlinux.org/packages/libvpx++).

### Others OS

#### Prerequisite

CMake installed.

#### Command in Linux

##### Build

	cd <path of the source>
	mkdir build
	cd build
	cmake ..
	make

##### Install

	make install

## Usage

Include vpx++_encoder.h or vpx++_decoder.h for encoder or decoder functions respectively.

Compile your program with `-lvpx++_common <-lvpx++_encoder | -lvpx++_decoder>`, depending on whether you are using the functions of encoder or decoder, or both.

## Version Number

Format: a.b.c

- a: Major version. Changes for major achievements. This library will go to to 1.0.0 when all functions of [libvpx](http://www.webmproject.org) are fully suppprted.

- b: Minor version. Changes when new functions are added, or major improvements or bug fixes are done.

- c: Minor fixes. Changes when some minor improvements or bug fixes are done.

