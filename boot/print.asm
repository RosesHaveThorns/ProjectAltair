; prints a string stored in 'bx'
print:
    ; ie while string[i] print string[i] i++
    
    pusha
    
    start:
        mov al, [bx] ; value at string base address
        cmp al, 0
        je done
        
        mov ah, 0x0e
        int 0x10
        
        add bx, 1 ; increment pointer
        jmp start
    done:
        popa
        ret

; prints a hex value stored in 'dx'
printhex:
    pusha
    
    mov cx, 0 ; index var
    
    hexloop:
        cmp cx, 4; if looped 4 times, end
        je end
        
        mov ax, dx ; ax is working reg
        and ax, 0x00f ; mask first three digits
        add al, 0x30 ; convert to ascii int char
        
        cmp al, 0x39 ; if > 9 add extra 7 to rep A to F
        jle step2
        
        add al, 7
        
        step2:
            ; set bx to base addr + str len - char index
            mov bx, HEXOUT + 5 ; base addr + str len
            sub bx, cx ; sub char index
            
            mov [bx], al ; copy ASCII char into position bx points to
            ror dx, 4
            
            add cx, 1
            jmp hexloop
            
    end:
        mov bx, HEXOUT
        call print
        
        popa
        ret

; prints a new line
printnl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; new line char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret
    
HEXOUT: ; reserve memory for the new HEX string used by printhex 
    db '0x0000', 0