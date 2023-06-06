sort_funcptr_t:
    push rbp
    mov rbp, rsp
    sub rsp, 32              ; allocate 4 stack variables: i, j, pivot, and temp

    mov ecx, [rbp+16]        ; ecx = n (number of long integers in array)
    dec ecx                  ; decrement n because we are using 0-based indexing

    mov esi, [rbp+8]         ; esi = numbers (pointer to array)

    mov eax, ecx             ; eax = high = n-1
    mov ebx, 0               ; ebx = low = 0

outer_loop:
    cmp ebx, eax             ; if low >= high, exit loop
    jge done

    mov ecx, ebx             ; ecx = i = low
    mov edi, eax             ; edi = j = high
    mov edx, [esi+eax*8]     ; edx = pivot = numbers[high]

inner_loop:
    cmp ecx, edi             ; if i >= j, exit loop
    jge partition

    mov ebp, ecx             ; ebp = temp = numbers[i]
    cmp [esi+ecx*8], edx     ; if numbers[i] > pivot
    jg swap_left             ; swap with numbers[j] and decrement j
    inc ecx                  ; otherwise, increment i
    jmp inner_loop

swap_left:
    mov [esi+ecx*8], [esi+edi*8] ; numbers[i] = numbers[j]
    mov [esi+edi*8], ebp         ; numbers[j] = temp
    dec edi                      ; decrement j
    jmp inner_loop

partition:
    mov [esi+eax*8], [esi+edi*8] ; numbers[high] = numbers[j]
    mov [esi+edi*8], edx         ; numbers[j] = pivot
    mov eax, edi                 ; high = j
    sub eax, 1                   ; high -= 1
    cmp eax, ebx                 ; if high > low
    jg outer_loop                ; continue with next partition

done:
    add rsp, 32                  ; deallocate stack variables
    pop rbp
    ret
