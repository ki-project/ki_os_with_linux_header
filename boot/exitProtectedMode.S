[global exitProtected]

exitProtected:
	cli
    mov eax,cr0
    and eax,0ffffffeh
    mov cr0,eax
    mov ax,data16
    mov ds,ax
    mov ax,stack16
	mov ss,ax mov sp,1000h ; assuming that stack16 is 1000h bytes in length
	mov bx,RealMemoryInterruptTableSavedWithSidt 
    litd [bx] 
    sti
    ret