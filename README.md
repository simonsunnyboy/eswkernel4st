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
- (optional) IKBD and Jaguar power pad support (with runtime detection of features)
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

The code assumes the regular Atari ST stack usage for 16bit words, e.g. -mshort is assumed for 
compilation and linkage.

## Integration manual

Link your sources to a TOS executable without AES usage, creating a classic .TOS application.

The ready compiled static library (.a file) of the kernel shall be linked to the executable.

1. use a minimal C startup to free TOS memory with mshrink(), example from tests can be reused
2. implement the required API from eswkernel4st.h
3. use the kernel services if necessary, see eswkernel4st_services.h

If included into another CMake project, the test will not be build.
The C compiler configuration of the wrapping project will be used to compile to library.

If build standalone, the compiler configuration from m68k-atari-mint.cmake will be used.

## Interrupt service routines

### VBL handler

The VBL handler should be used for video synchronization exclusively.
Its call rate may vary depending on the monitor type used by the users.

This is typically 50Hz for PAL systems or 60Hz for NTSC systems.

As the application cannot know which is in use, it is best practice to handle
all non-video timing from Timer C.

The callback can be used to hook rasterbar handling if necessary.

### Timer C

The regular TOS Timer C interrupt at 200Hz is still in use.

This is also necessary for operation of certain harddisk drivers so disabling it
might lead to problems when accesses files on disk.

The kernel keeps calling the 200Hz routine and allows a user routine to be called
in this interval.

This also allows to call SNDH music playback routines that derive their own playback
rate from the 200Hz calls.


Additionally every 4th time a 50Hz routine is called.
The kernel itself does not use this but a user routine can be used to determine
steady time points for updates.

This is a good location to count how often your game logic shall update.

### IKBD handler

The IKBD handling interupt is not enabled by the kernel itself.

The application must enable it if desired.

Its input input state can then be queried with the associated service functions.

Cyclic handling is best placed in the VBL or 50Hz handler.

The kernel may be compiled without the ikbd_*.* source files if desired.

## Screen buffer allocation

Screen buffer allocation in memory is optional.
All screen buffer addresses must be aligned on 256 byte boundaries (ST Shifter limitation)

By default a simple flip screen with 2 pages is provided.
Screens are cleared. They are consecutive in memory without overspill areas.

The application may opt not to enable this regular routine and provide its own.

## Jagpad handling

Atari Jaguar Powerpads are optionally supported if the machine has the physical ports.

Presence of ports is determined through the _MCH cookie. 
If enabled, their state is polled during the 50Hz interrupt.

### Supported machines

- Atari 1040STE
- Atari Falcon 030

### Unsupported machines

- Atari STF
- Atari Mega ST
- Atari Mega STE

## STE only software

The kernel is designed to handle STF, STE, TT and Falcon software.

If the applications desires to not support a specific machine, it is recommended to
intercept the _MCH cookie inside the screen buffer allocation function accordingly.

Alternatively do this in your startup code.
