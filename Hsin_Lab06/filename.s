sort_funcptr_t:          ; rdi is the first param, rsi is the second param
    push rbp
    mov rbp, rsp
    sub rsp, 16          ; allocate 2 stack variables: i and j  

    mov ecx, [rbp+16]    ; ecx = n (number of long integers in array)
    dec ecx              ; decrement n because we are using 0-based indexing

    mov esi, [rbp+8]     ; esi = numbers (pointer to array)

outer_loop:
    mov edi, esi         ; edi = numbers (pointer to array)
    xor edx, edx         ; edx = 0 (initialize swap flag)

inner_loop:
    mov ebx, edi
    add ebx, 8           ; ebx = &numbers[j+1]
    mov eax, [edi]
    cmp eax, [ebx]
    jle skip_swap
    xchg eax, [ebx]
    mov [edi], eax
    mov edx, 1           ; set swap flag to indicate a swap occurred
skip_swap:
    add edi, 8           ; increment j
    cmp edi, [rbp+8]     ; compare j to the end of the array
    jb inner_loop        ; if j < n, continue inner loop

    cmp edx, 0           ; if no swaps occurred, the array is sorted
    jne outer_loop       ; otherwise, continue outer loop

done:
    add rsp, 16          ; deallocate stack variables
    pop rbp
    ret
