#!/usr/bin/env python2.7

_sum = 0

with open( "text/problem13.txt", 'r' ) as _file:
    for line in _file:
        _sum += int( line )

print str( _sum )[ :10 ]
