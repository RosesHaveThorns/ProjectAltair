# Project Altair

An x86 operating system built from the ground up, based on the tutorial at https://github.com/cfenollosa/os-tutorial/.

## Goal
A basic command line based operating system, with file storage and editing, and the ability to create new commands from within the OS.

## Creator
Thats me, Rose Awen Brindle! Feel free to contribute if you have ideas to improve this!

## Installation
### Building the OS
Before building the OS, make sure the GDB, QEMU and GCC command paths are correct in the Makefile. use 'which __' to find the paths if you dont know them.
To build the OS from source, call 'make' from within the base directory.
To use GDB to debug the OS, call 'make debug'.

### Running the OS
As of present, the only supported method of running the OS is with QEMU.
It can be ran using the command 'make run', or by calling 'qemu -lda os-image.bin' after build completion.
