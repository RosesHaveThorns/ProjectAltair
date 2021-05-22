gdt_start:
    dd 0x0
    dd 0x0
    
; code segment GDT
gdt_code:
    dw 0xffff       ; segment length (bits 0-15)
    dw 0x0          ; segemnt base (bits 0-15)
    db 0x0          ; segment base (bits 16-23)
    db 10011010b    ; flags (8 bits)
    db 11001111b    ; flags (4 bits) + segment length (bits 16-19)
    db 0x0          ; segment base (bits 24-31)
    
; data segment GDT, in same location and size as code segment
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
    
gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; GDT size (16 bits)
    dd gdt_start ; GDT address (32 bits)
    
; constants
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start 