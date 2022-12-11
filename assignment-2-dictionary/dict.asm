%include "lib.inc"
global find_word
%define SHIFT 8
section .text

;rdi - ponter of string
;rsi - pointer of dictionary


find_word:
    .loop:
    push rdi
    push rsi
    add rsi, SHIFT ; make a shift
    call string_equals
    pop rsi
    pop rdi
    test rax, rax
    jnz .the_word_has_found
    mov rsi,[rsi]
    test rsi, rsi
    jnz .loop
    .break:
        xor rax, rax
        ret
    .the_word_has_found:
        mov rax,rsi
        ret