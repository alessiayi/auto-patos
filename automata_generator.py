import random
from math import floor, sqrt

print("-------- Automata Generator --------\n")
size = int(input("Number of states: "))


initial_state = 0

# size initState |fstates| fstates...
number_fstates = random.randint(1,floor(sqrt(size)))
fstates = random.sample(range(1,size), number_fstates)

print(size, initial_state, number_fstates, end="")
for fs in fstates: print("", fs, end="")

print()

# transitions
first_bulk = floor(size/2)
for i in range(first_bulk):
    print(i, 0, random.randint(1, floor(size/2) ) )
    print(i, 1, random.randint(floor(size/2), size-1 ) )

second_bulk = size-first_bulk-1
for i in range(first_bulk, size):
    print(i, 0, random.randint(1, floor(size/2) ) )
    print(i, 1, random.randint(floor(size/2), size-1))




