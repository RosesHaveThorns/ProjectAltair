; load sectors 'dh' from drive 'dl' into es:bx (input params: dh=num sectors, dl=drive num)
diskload:
    pusha
    
    ; will overwrite input params in dx, so store to stack
    push dx
    
    mov ah, 0x02    ; set ah to read
    mov al, dh      ; set al to num of sectors to read
    mov cl, 0x02    ; set cl to sector (0x02 is first sector after boot sector)
    mov ch, 0x00    ; set ch to cylinder
                    ; dl is drive number (0=floppy, 1=floppy2, 0x80=hdd, 0x81=hdd2). passed as parameter so already set
    mov dh, 0x00    ; set dh head number
    
    ; [es:bx] is pointer to buffer where data will be stored. setup by caller
    
    int 0x13 ; send read disk interrupt
    jc diskerror ; if error, stored in carry bit
    
    pop dx
    cmp al, dh ; BIOS has set al to num of sectors, compare if as expected
    jne sectorerror
    
    popa
    ret
    
    diskerror:
        mov bx, DISKERROR
        call print
        call printnl
    
        mov dh, ah ; ah is error code, al is disk drive that caused error
        call printhex
        jmp diskloop
        
    sectorerror:
        mov bx, SECTORSERROR
        call print
        jmp diskloop
    
diskloop:
    jmp $
    
 DISKERROR: db "Disk read error: ", 0
 SECTORSERROR: db "Incorrect number of sectors read", 0