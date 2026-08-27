SECTION .text

START:
    MOV EAX, 10
    MOV EBX, 20
    ADD EAX, EBX
    SUB EAX, 5
    AND EAX, EBX
    OR EAX, EBX
    XOR EAX, EBX
    CMP EAX, EBX
    NOT EAX
    MUL EBX
    DIV EBX
    INC EAX
    DEC EBX
    MOV ECX, VALUE
    MOV EDX, [EBX+4]
    JMP LOOP

LOOP:
    JZ START
    JNE START
    CALL FUNC
    RET

FUNC:
    MOV ESI, 25
    XYZ EAX, 50

SECTION .data

