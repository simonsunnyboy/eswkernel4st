# Entertainment Software Kernel for Atari ST

(c) 2016/2018 by Matthias Arndt <marndt@asmsoftware.de>

The MIT License applies to this software. Please refer to the file LICENSE for
further details.

## Abstract
The "Entertainment Software Kernel for Atari ST" helps as a starting point to
develop audiovisual applications like games or demos with a GCC crosscompiler
for Atari ST machines running classic TOS.

A user can clone the repository and directly start writing his own application
by filling the necessary software hooks and using the provided calls.

## Requirements

- GNU cross compiler toolchain for Atari ST and compatibles (http://vincent.riviere.free.fr/soft/m68k-atari-mint/)
- CMake (http://www.cmake.org/)
- Atari ST/STE/TT/Falcon 030 target machine with color display (ST-LOW)

## Provided resources

The kernel provides

- video mode setup (ST-LOW, for Falcon 030 with RGB and VGA monitor support)
- basic timer interrupt with 50Hz callback (VBL independant) based on TOS Timer C
- user defined hook for initializations
- basic cyclic loop calling a user defined handler per frame
- readily usable screen memory addresses (aligned at 256 byte boundaries)
- abstraction for flip screens and palette updates
- screen clear and copy functions
- basic .NEO, .PI1 and .PC1 support
- IKBD and Jaguar power pad support (with runtime detection of features)
- _MCH cookie interfaces
- TOS may be accessed if necessary including its VBL handler

Screen update timing and synchronization is up to the user.

## User options

The user may

- optionally provide his own VBL interrupt handler (and use TOS system variables for
- determine screen update timing and synchronization by himself

## Restrictions

The kernel does not return to TOS or the GEM desktop. If the termination callback
is used, the application will trigger a soft reset of the ST.

No support for multitasking operating systems. If the program runs with MinT or MagiC, fine but do not bet on it.
