[bits 16]
switch_protmode:
    cli ; disable interrupts

    lgdt [gdt_descriptor] ; load gdt through descriptor
    
    ; disable paging
    mov eax, cr0
    or eax, 0x1	; Disable paging bit & disable 16-bit pmode.
    mov cr0, eax ; set 32-bit mode bit in cr0 register

    jmp CODE_SEG:init_protmode ; farjump using different segment
    
[bits 32] ; switch to 32-bit instructions
init_protmode:

    mov ax, DATA_SEG ; update segment registers (all use the code/data segment)
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ebp, 0x9000 ; move stack to top of the free space
    mov esp, ebp
    
    ;sti
    
    call BEGIN_PM ; return to main code
        