[global CheckA20]

CheckA20:
	PUSH ax
    PUSH ds
    PUSH es
    XOR ax,ax
    MOV ds,ax
    NOT ax
    MOV es,ax
    MOV ah,[ds:0]
    CMP ah,[es:10h]
    JNZ A20_ON
    CLI
    INC ah
    MOV [ds:0],ah
    CMP [es:10h],ah
    PUSHF
    DEC ah
    MOV [ds:0],ah
    STI
    POPF
    JNZ A20_ON
    CLC
    POP es
    POP ds
    POP ax
    RET

A20_ON:
	STC
    POP es
    POP ds
    POP ax
    RET