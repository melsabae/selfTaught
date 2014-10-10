#!/usr/bin/env python2.7

class Falafel:
    def __init__( self ):
        self.isTasty = True
        self.imgPic = ""

    def WhatDanielThinks( self ):
        if( True == self.isTasty ):
            print "boooom"

    def MakeMeHungry( self ):
        with open( "falafel.txt", "r" ) as _file:
                for line in _file:
                    self.imgPic = self.imgPic +  line

        print self.imgPic
