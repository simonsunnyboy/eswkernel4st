# Entertainment Software Kernel for Atari ST

(c) 2016/2018/2026 by Matthias Arndt <marndt@final-memory.org>

The MIT License applies to this software. Please refer to the file LICENSE for
further details.

## Abstract
The "Entertainment Software Kernel for Atari ST" serves as a starting point for
developing audiovisual applications such as games or demos with a GCC cross
compiler for Atari ST machines running classic TOS.

A user can clone the repository and directly start writing their own application
by filling in the necessary software hooks and using the provided calls.

## Changelog

V0.0.1alpha
- initial version from 2016 with some fixes

## Requirements

- GNU cross compiler toolchain for Atari ST and compatibles (https://vincent.riviere.free.fr/soft/m68k-atari-mint/)
- CMake (https://www.cmake.org/)
- Atari ST/STE/TT/Falcon 030 target machine with color display (ST-LOW)

## Provided resources

The kernel provides

- video mode setup (ST-LOW, for Falcon 030 with RGB and VGA monitor support)
- basic timer interrupt with 50 Hz callback (VBL independent) based on TOS Timer C
- user-defined hook for initialization
- basic cyclic loop calling a user-defined handler per frame
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

- optionally provide their own VBL interrupt handler and use TOS system variables to
  determine screen update timing and synchronization themselves

## Restrictions

The kernel does not return to TOS or the GEM desktop. If the termination callback
is used, the application will trigger a soft reset of the ST.

No support for multitasking operating systems. If the program runs with MinT or MagiC, fine but do not bet on it.

The kernel switches to supervisor mode for full hardware access.

## Integration manual

Link your sources to a TOS executable without AES usage, creating a classic .TOS application.

The ready compiled static library (.a file) of the kernel shall be linked to the executable.

1. use a minimal C startup to free TOS memory with mshrink(), example from tests can be reused
2. implement the required API from eswkernel4st.h
3. use the kernel services if necessary, see eswkernel4st_services.h