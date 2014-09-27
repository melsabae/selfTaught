#!/usr/bin/env python2.7

with open( 'text/problem8.txt', 'r' ) as _file:
    digits = _file.readline().rstrip('\n')

separated = []
# pop each digit off into its own int item
for digit in digits:
    separated.append( int( digit ))

# no need to keep that ~1kb of memory used
del digits

highest = 0

for indexes in range( len( separated )):
    # if we dont have 13 numbers left, stop
    if indexes > len( separated ) - 13:
        break

    product = 1

    # grabs the next 12 list items
    for digits in separated[ indexes: indexes + 13 ]:
        if digits == 0:
            break

        product *= digits
        
    if product > highest:
        highest = product

print highest
