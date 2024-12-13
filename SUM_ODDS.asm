ldc 0       ; Load 0 into A (initialize sum to 0)
stl 0       ; Store A (sum) at memory offset 0

ldc 1       ; Load 1 into A (first odd number)
stl 1       ; Store A (current odd number) at memory offset 1

ldc 10      ; Load 10 into A (loop counter)
stl 2       ; Store A (counter) at memory offset 2

loop:       
ldl 2       ; Load the loop counter into A
brz end     ; If counter == 0, branch to "end"

ldl 0       ; Load the current sum into A
ldl 1       ; Load the current odd number into A
add         ; Add the odd number to the sum
stl 0       ; Store the updated sum at memory offset 0

ldl 1       ; Load the current odd number into A
adc 2       ; Add 2 to get the next odd number
stl 1       ; Store the next odd number at memory offset 1

ldl 2       ; Load the loop counter into A
adc -1      ; Subtract 1 from the counter
stl 2       ; Store the updated counter at memory offset 2

br loop     ; Unconditional branch back to "loop"

end:        
ldc 0       ; Load 0 into A (to stop execution gracefully)
