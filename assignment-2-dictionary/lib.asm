global exit
global string_length
global print_string
global print_char
global print_newline
global print_uint
global print_int
global string_equals
global read_char
global read_word
global parse_uint
global parse_int
global string_copy
global print_string_err
%define STDIN 0
%define STDOUT 1
%define SYSCALL_READ  0
%define SYSCALL_WRITE 1
%define SYSCALL_EXIT  60
section .text
 
 
; Принимает код возврата и завершает текущий процесс
exit: 
    mov  rax, 60            ; invoke 'exit' system call
    xor  rdi, rdi
    syscall

; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
  mov rax, 0; for loop
    .count:
      cmp byte [rdi+rax], 0
      je .end
      inc rax
      jmp .count
    .end:
      ret

; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
	push rdi
    call string_length; to know size of buffer
    pop rdi
    mov rdx, rax
    mov  rsi, rdi
    mov  rax, SYSCALL_WRITE
    mov  rdi, STDOUT
    syscall
    ret
    
print_string_err:
    push rdi
    call string_length; to know size of buffer
    pop rdi
    mov rdx, rax
    mov  rsi, rdi
    mov  rax, SYSCALL_WRITE
    mov  rdi, 2
    syscall
    ret
; Принимает код символа и выводит его в stdout
print_char:
	push rsi
    push rdi; from register to memory
    mov rdi,STDOUT
    mov rsi, rsp; adress of char to rsi
    mov rdx, 1; lenght of the string
    mov rax,SYSCALL_WRITE; number of syscall
    syscall
    pop rdi
    pop rsi
    ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
	push rdi
    mov rdi, 0xA; argument of func
    call print_char
    pop rdi
    ret

; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
    mov	rax, rdi	; put the argument in rax
	mov	rdi, 10	; our divider
	mov	r9, rsp	; save stack because it is Callee-saved register
	push word 0	; 
.loop_to_div:
	xor	rdx, rdx
	div	rdi			; we put remainder of div(rax/rdi) to rdx and quotient in rax
	or	dl, "0"		; transform remainder(rdx - edx - dx + dl)
	dec	rsp			; stack pointer --
	mov	byte [rsp], dl	; put remainder into stack
	test	rax, rax		; 
	jnz	.loop_to_div	; if not 0 repeat
	mov	rdi, rsp		; move str start adr
	call	print_string
	mov	rsp, r9		; restore
	ret



; Выводит знаковое 8-байтовое число в десятичном формате 
print_int:
    test	rdi, rdi	
	jns	.with_plus	; if the value with +
	neg	rdi	; neg the value
    push rdi; save data
	mov	rdi, "-"	; because we need to print - 
	call	print_char
    ;we write "-" in console
	pop	rdi		
	call print_uint	
    jmp .end
    .with_plus:
        call print_uint;
    .end:
        xor rax,rax
        ret
; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
   xor rax, rax; for loop
    .count:
      mov dh, [rdi+rax]; the first char
      mov dl, [rsi+rax]; the second char
      cmp dl, dh; compare chars
      jne .different; if they are different
      cmp dl, 0; examination of 0
      je .equals; if the char is 0
      inc rax; increment value for loop
      jmp .count; go to the loop
    .different:
        xor rax,rax; 0 in rax
        ret
    .equals:
        mov rax,1
        ret
; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    mov rax, SYSCALL_READ
    mov rdi, STDIN
    push 0; make a space in memory
    mov rsi, rsp; to the free space in memory
    mov rdx, 1; we need only 1 char
    syscall
    pop rax
    ret 

; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор

read_word:
    xor rdx,rdx; count chars
    xor rax, rax; 
    .loop:
        push rsi; buffer's size
        push rdi; buffer's start
        push rdx; count chars
        call read_char; return char from IO
        pop rdx
        pop rdi
        pop rsi
        cmp rax, 0x20
        je .check_the_char
        cmp rax, 0x9
        je .check_the_char
        cmp rax, 0xA
        je .check_the_char
        cmp rax, 0
        je .end_of_the_word
        ; checking for unwanted characters
        mov byte[rdi+rdx], al; write the value in the buffer
        cmp rdx, rsi ; check that we did not exceed the buffer value
        je .error_in_fucntion; if we exceed the buffer value
        inc rdx
        jmp .loop
    .check_the_char:
        cmp rdx, 0
	    je .loop
        jmp .end_of_the_word
    .error_in_fucntion:
        xor rax,rax
        ret
    .end_of_the_word:
        mov byte[rdi+rdx], 0x0
        mov rax, rdi
        ret
 

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
    xor	rax, rax	
	xor	rdx, rdx	; higher bits register for overflow
	xor	rsi, rsi	; counter for loop
	xor	rcx, rcx	; digit
	mov	r11, 10	
.loop:
	mov	cl, byte [rdi + rsi]	;take the char from rdi + rsi
	xor	cl, "0"			; transform
	cmp	cl, 9				; check that number less than 9
	ja	.end
	mul	r11				; multiply AC on 10
	add	rax, rcx			; add digit
	inc	rsi
	jmp	.loop
.end:
	mov	rdx, rsi
	ret




; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int:
    mov	cl, byte [rdi]
	cmp	cl, "-"		; check if the value < 0
	jne	.if_positive
	jmp .if_negative
.if_positive:
    call parse_uint
    jmp .end
.if_negative:
    inc	rdi
	call	parse_uint
	neg	rax
	inc	rdx
.end:
    ret


; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:
    ; in rdi pointer to string, in rsi poiter on buffer, in rdx size of buffer
    push rdi
    push rsi
    push rdx
    call string_length
    pop rdx
    pop rsi
    pop rdi
    cmp rax, rdx; check that size of string less than size of buffer
    jae .error
    xor rax,rax; for loop
    .loop:
        mov ch, byte[rdi+rax]
        mov byte[rsi+rax],ch;
        inc rax
        cmp ch, 0
        jne .loop
        ret
    .error:
        xor rax, rax
        ret
        
    
