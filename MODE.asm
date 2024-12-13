# Data Section
data 6        # Array length (n = 6)
data 4        # Array[0] = 4
data 5        # Array[1] = 5
data 4        # Array[2] = 4
data 6        # Array[3] = 6
data 5        # Array[4] = 5
data 5        # Array[5] = 5
data 0        # Mode (initialize to 0)
data 0        # Max count (initialize to 0)

# Initialize Loop Variables
ldc 0         # i = 0
stl 1         # Store i in SP+1 (local variable)

# Outer Loop
loop_outer:
ldl 1         # Load i
ldc 6         # Load n
sub           # i - n
brz end_outer # If i == n, exit outer loop

ldc 0         # count = 0
stl 3         # Store count in SP+3 (local variable)

ldl 1         # Load i
ldc 4         # Base address
add           # Base + i
ldnl 0        # Load Array[i]
stl 2         # Store Array[i] in SP+2 (local variable)

ldc 0         # j = 0
stl 4         # Store j in SP+4 (local variable)

# Inner Loop
loop_inner:
ldl 4         # Load j
ldc 6         # Load n
sub           # j - n
brz end_inner # If j == n, exit inner loop

ldl 4         # Load j
ldc 4         # Base address
add           # Base + j
ldnl 0        # Load Array[j]
ldl 2         # Load Array[i]
sub           # Array[j] - Array[i]
brz incr_count # If Array[j] == Array[i], increment count

# Continue inner loop
ldl 4         # Load j
ldc 1         # j + 1
add           # Increment j
stl 4         # Store j
br loop_inner # Jump back to start of inner loop

# Increment Count
incr_count:
ldl 3         # Load count
ldc 1         # count + 1
add           # Increment count
stl 3         # Store count

ldl 4         # Load j
ldc 1         # j + 1
add           # Increment j
stl 4         # Store j
br loop_inner # Jump back to start of inner loop

# End Inner Loop
end_inner:
ldl 3         # Load count
ldl 7         # Load max_count
sub           # count - max_count
blz skip_update # If count <= max_count, skip update

ldl 2         # Load Array[i]
stl 6         # Update mode
ldl 3         # Load count
stl 7         # Update max_count

# Skip Update
skip_update:
ldl 1         # Load i
ldc 1         # i + 1
add           # Increment i
stl 1         # Store i
br loop_outer # Jump back to start of outer loop

# End Outer Loop
end_outer:
hlt           # Halt program
