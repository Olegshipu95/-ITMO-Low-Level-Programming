extern find_word
%include "lib.inc"
%include "colon.inc"
%include "words.inc"
%define SHIFT 8
%define BUFFER_SIZE 256

global _start

section .rodata
welcome_message: db "Hi",0
error_overfl_message: db "overflow", 0
error_not_found_message: db "no word", 0
found_message:db "Nice word, sir. We found it", 0
write_the_word_message: db "You should wite a word here ",0
key_value_separator: db ": ", 0

section .bss
BUFFER: resb BUFFER_SIZE

section .text
_start:
    mov rdi, welcome_message
    call print_string
    call print_newline
    
    .read:
        mov rdi, write_the_word_message
        call print_string
        mov rdi, BUFFER
        mov rsi, BUFFER_SIZE
        call read_word
        test rax, rax
        jz .overflow
        push rdx
        mov rdi, rax
        mov rsi, POINTER; from colon.inc
        call find_word
        test rax,rax
        je .not_found
    .found:
        push rax
        mov rdi, found_message
        call print_string
        call print_newline
        pop rdi
        add rdi, SHIFT
        push rdi
        call    print_string
        mov rdi, key_value_separator
        call print_string
        pop rdi

        pop rdx
        add rdi, rdx
        inc rdi
        call print_string
        call print_newline
        jmp .read

    .overflow:
        mov rdi, error_overfl_message
        call print_string_err
        call print_newline
        jmp .read
    
    .not_found:
        
        mov rdi, error_not_found_message
        call print_string_err
        call print_newline
        jmp .read