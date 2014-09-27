#!/usr/bin/env python2.7
import time

num_nums = 4 # yum, number of numbers we need to operate on for valid answer

# default movement is to the right, otherwise down
def Straight( r, c, direction = "Right" ):
    product = 1

    for index in xrange( num_nums ):
        if direction == "Right": # next element in row
                var = int( grid[ r ][ c + index ])
        else: # next element in column
                var = int( grid[ r + index ][ c ])

        if( var == 0 ):
            return 0

        product *= var

    return product

# default y value moves downwards, or can be sent upwards
def Diag( r, c, y = 1 ):
    # y is inverse direction from x,y coord plane
    # traversing a list of lists causes downward movement to increase, while upwards is decreasing y values
    product = 1
    for index in xrange( num_nums ):
        # gets diagonal elements by addressing them by _index_ and the y direction, moves right and up|down
        var = int( grid[ r + ( y * index )][ c + index ])
        if( var == 0 ):
            return 0

        product *= var

    return product

"""
store 20x20 grid
"""
grid = []

with open( "text/problem11.txt", 'r' ) as _file:
    for row in _file:
        # removes newlines, puts each split into new list item per list
        grid.append( row.rstrip( '\r\n' ).split( ' ' ))

"""
bring forth the answer
"""
LOW = num_nums - 1 # index for checking if right-up operation is valid
HIGH = len( grid ) - num_nums # index to check if down and/or right operations are valid
contenders = [] # store for all answers

for row_index in xrange( len( grid )):
    for column_index in xrange( len( grid[ row_index ] )):

        # if we can still go right
        if( column_index <= HIGH ):
            contenders.append( Straight( row_index, column_index ))

            if( row_index >= LOW ):
                contenders.append( Diag( row_index, column_index, -1 )) # right and up

            # if we can still go downwards
            if( row_index <= HIGH ):
                contenders.append( Straight( row_index, column_index, "Down" ))
                contenders.append( Diag( row_index, column_index )) # right and down

"""
sort list and get last item for winner
"""
contenders.sort()
print contenders[ -1 ]
