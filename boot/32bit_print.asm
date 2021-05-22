[bits 32] ; use 32 bit protected mode

; constants
VIDEO_MEM equ 0xb8000 ; address of video memory
WHITE_ON_BLACK equ 0x0f ; character colour byte

print_pm:
    pusha
    mov edx, VIDEO_MEM
    
print_pm_loop:
    mov al, [ebx] ; [ebx] is addr of char to be printed
    mov ah, WHITE_ON_BLACK ; each char in video mem is made up of ascii char and colour byte
    
    cmp al, 0 ; if end of string
    je print_pm_end
    
    mov [edx], ax ; store char + colour byte in video mem
    
    add ebx, 1 ; next char in string (each char is 1 byte)
    add edx, 2 ; next video mem location (each location is 2 bytes)
    
    jmp print_pm_loop
    
print_pm_end:
    popa
    ret