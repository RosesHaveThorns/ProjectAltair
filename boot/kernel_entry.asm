[bits 32]
[extern kernel_main] ; defines calling point
global _start;
_start:
call kernel_main
jmp $