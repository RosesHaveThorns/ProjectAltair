[org 0x7c00]
KERNEL_OFFSET equ 0x1000 ; must be the same as used when linking kernel

    mov [BOOT_DRIVE], dl ; BIOS sets boot drive in dl during bootup, we store it in case dl gets overwritten

    mov bp, 0x9000 ; set stack address
    mov sp, bp
    
    mov bx, MSG_REAL_MODE
    call print
    call printnl
    
    call loadkernel ; read kernel from disk
    call switch_protmode ; calls BEGIN_PM when complete

; real mode hang (sholdn't be reached)
    jmp $

  
; includes
%include "boot_sect_print.asm"
%include "32bit_print.asm"
%include "boot_sect_disk.asm"
%include "32bit_gdt.asm"
%include "32bit_switch.asm"
    

; load kernel from disk
[bits 16]
loadkernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call printnl
    
    mov bx, KERNEL_OFFSET ; store kernel in 0x1000
    mov dh, 2 ; load in 2 sectors of data
    mov dl, [BOOT_DRIVE] ; in case dl has changed
    call diskload ; read kernel and store to KERNEL_OFFSET
    ret

    
; 32 bit protected mode, called by switch method
[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_pm
    
    call KERNEL_OFFSET ; hand kernel control

; prot mode hang, incase kernel hands back control
    jmp $
    
    
; data
BOOT_DRIVE db 0

MSG_REAL_MODE db "Started in 16-bit real mode", 0   
MSG_PROT_MODE db "Loaded into 32-bit protected mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0


; boot sector padding
times 510 - ($-$$) db 0
dw 0xaa55