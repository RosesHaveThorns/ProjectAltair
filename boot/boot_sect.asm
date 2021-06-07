[org 0x7c00]
[bits 16]

KERNEL_OFFSET equ 0x1000 ; must be the same as used when linking kernel
    
    mov [BOOT_DRIVE], dl ; BIOS sets boot drive in dl during bootup, we store it in case dl gets overwritten

    
    mov ax, 0
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov bp, 0x9000 ; move stack to top of the free space
    mov sp, bp
    
    mov bx, MSG_REAL_MODE
    call print
    call printnl
    
    call loadkernel ; read kernel from disk
    call switch_protmode ; calls BEGIN_PM when complete
   

; real mode hang (sholdn't be reached)
    jmp $

  
; includes
%include "boot/print.asm"
%include "boot/32bit_print.asm"
%include "boot/disk.asm"
%include "boot/32bit_gdt.asm"
%include "boot/32bit_switch_prot.asm"
    

; load kernel from disk
[bits 16]
loadkernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call printnl
    
    mov bx, KERNEL_OFFSET ; store kernel in 0x1000
    mov dh, 30 ; load in kernel data !!! IF ISSUES WITH KERNEL FUNCTIONS NOT RETURNING, INCREASE AMOUNT OF SECTORS LOADED !!!
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

MSG_REAL_MODE db "Started real mode", 0   
MSG_PROT_MODE db "Loaded protected mode", 0
MSG_LOAD_KERNEL db "Loading kernel", 0

; boot sector padding
times 510 - ($-$$) db 0
dw 0xaa55