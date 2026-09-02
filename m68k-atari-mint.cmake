# --- Atari ST cross toolchain (reusable) ---

# Disable strange gcc assumptions
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# Select Atari ST cross compiler and enable assembly language
enable_language(ASM)

# Core toolchain programs
set(CMAKE_C_COMPILER     m68k-atari-mint-gcc)
set(CMAKE_ASM_COMPILER   m68k-atari-mint-as)
set(CMAKE_AR             m68k-atari-mint-ar)
set(CMAKE_RANLIB         m68k-atari-mint-ranlib)

# Base flags (project may append)
set(ATARI_BASE_CFLAGS "-m68000 -O3 -fomit-frame-pointer -Wextra -Wall -mshort -nostdlib -std=c99"
    CACHE STRING "Base C flags for Atari toolchain")

# Project-specific include directory for ASM
set(ATARI_ASM_INCLUDE "" CACHE PATH "Path to ASM include directory")

# Apply flags
set(CMAKE_C_FLAGS "${ATARI_BASE_CFLAGS} ${ATARI_EXTRA_CFLAGS}")
set(CMAKE_ASM_FLAGS "-m68000 -I${ATARI_ASM_INCLUDE}")

