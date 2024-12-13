; Outline of Bubble Sort Program
ldc 0x1000        ; Load address into accumulator (A)
a2sp              ; Transfer A to SP (set stack pointer)
adj -1            ; Adjust SP to reserve space
ldc 10            ; Load the number of elements into A
stl 0             ; Store it in local offset 0 (SP+0 = count)
ldc array         ; Load the address of the array into A
call sort         ; Call the sort function
HALT              ; Halt the program

; Function to sort array in descending order
sort: adj -1      ; Adjust SP to reserve space for return address
stl 0             ; Save return address in local variable
stl 2             ; Save address of elements in local variable
adj -3            ; Adjust stack for temporary variables

; Initialize loop counters
ldc 0             ; Load 0 to A
stl 0             ; Save it as temp
ldc 1             ; Load 1 to A
stl 1             ; Save it as y
ldc 0             ; Load 0 to A
stl 2             ; Save it as x

loop_out:
ldl 4             ; Load count (number of elements)
ldl 2             ; Load x
sub               ; Calculate count - x
ldc 1
sub               ; Calculate count - 1 - x
brz done          ; If count - 1 - x is zero, jump to done

ldc 1             ; Load 1 to A
stl 1             ; Set y = 1

loop_in:
ldl 4             ; Load count
ldl 2             ; Load x
sub               ; Calculate count - x
ldl 1             ; Load y
sub               ; Calculate count - x - y
brz addx          ; If count - x - y is zero, jump to addx

ldl 5             ; Load base address of the array
ldnl 0            ; Load array[0] to A
ldc 0             ; Load 0 to A (initialize B)
ldnl 1            ; Load array[1]
sub               ; Calculate array[0] - array[1]
brlz swap         ; If array[0] - array[1] < 0, swap

br addy           ; Jump to increment y

swap:
ldl 5             ; Load base address of the array
ldnl 0            ; Load array[0] to A
stl 0             ; Store array[0] in temp
ldl 5
ldnl 1            ; Load array[1]
ldl 5
stnl 0            ; Store array[1] in array[0]
ldl 0             ; Load temp
ldl 5
stnl 1            ; Store temp in array[1]

; Increment y
addy:
ldc 1
ldl 1             ; Load y
add               ; Increment y
stl 1             ; Save updated y
br loop_in        ; Jump to inner loop

addx:
ldc 1
ldl 2             ; Load x
add               ; Increment x
stl 2             ; Save updated x
ldc 1
ldl 5
add               ; Increment array pointer
br loop_out       ; Jump to outer loop

done:
ldl 3             ; Load return address
adj 5             ; Adjust SP to clean up and restore state
return            ; Return from the procedure

; Array data
array: data -559038737 
data 1592639189 
data -1058161986 
data 1588527317 
data -1420028582 
data -899895827 
data -17958194 
data -1061097459 
data -556882451 
data 1358610133 
