[global enterProtected]

enterProtected:
	cli
    mov eax,cr0
    or eax,1
    mov cr0,eax
    db 0eah ; Opcode for far jump
	dw StartPM ; Offset to start, 16-bit
	dw 018h ; This is the selector for CODE16_DESCRIPTOR,
	; assuming that StartPM resides in code16
    db 66h ; Prefix for 32-bit
	db 0eah ; Opcode for far jump
	dd StartPM ; Offset to start, 32-bit
	dw 08h ; This is the selector for CODE32_DESCRIPTOR,
	; assuming that StartPM resides in code32
    mov ax, data_selector
    mov ds,ax
    mov ax, stack_selector
    mov ss,ax
    mov esp,1000h ; assuming that the limit of the stack segment
	; selected by stack_selector is 1000h bytes.
	sti
    ret