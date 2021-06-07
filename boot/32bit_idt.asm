[GLOBAL idt_flush]

idt_flush:
    mov eax, [esp + 4] ; pntr to IDT was passed as param
    lidt [eax] ; load IDT
    ret
