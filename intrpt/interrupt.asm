[extern isr_handler] ; defined in isr.c

; isr common code
isr_common:
    ; save cpu state
    pusha ; push edi esi ebp esp ebx edx ecx eax

    mov ax, ds ; lower 16bits of eax = ds
    push eax ; save data segment descriptor in lower 16 bits

    mov ax, 0x10 ; set all to kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; call c handler
    call isr_handler

    ; restore state
    pop eax

    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa

    add esp, 8 ; cleanup pushed error code and ISR num
    sti
    iret ; pops CS EIP EFLAGS SS ESP

; make ISRs global
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; ISRs

; divide by zero exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common

; debug exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common

; non maskable interrupt exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common

; int 3 exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common

; INTO exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common

; out of bounds exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common

; invalid opcode exception
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common

; coprocessor not available exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common

; double fault exception (error code already pushed)
isr8:
    cli
    push byte 8
    jmp isr_common

; coprocessor segment overrun exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common

; bad TSS exception (error code already pushed)
isr10:
    cli
    push byte 10
    jmp isr_common

; segment not present exception (error code already pushed)
isr11:
    cli
    push byte 11
    jmp isr_common

; stack fault exception (error code already pushed)
isr12:
    cli
    push byte 12
    jmp isr_common

; general protection exception (error code already pushed)
isr13:
    cli
    push byte 13
    jmp isr_common

; page fault exception (error code already pushed)
isr14:
    cli
    push byte 14
    jmp isr_common

; reserved exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common

; floating point exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common

; alignment check exception (error code already pushed)
isr17:
    cli
    push byte 17
    jmp isr_common

; machine check exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common

; reserved interrupt
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common

; reserved interrupt
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common

; reserved interrupt (error code already pushed)
isr21:
    cli
    push byte 21
    jmp isr_common

; reserved interrupt
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common

; reserved interrupt
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common

; reserved interrupt
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common

; reserved interrupt
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common

; reserved interrupt
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common

; reserved interrupt
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common

; reserved interrupt
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common

; reserved interrupt
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common

; reserved interrupt
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common

; reserved interrupt
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common