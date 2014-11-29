#!/usr/bin/env python2.7
import urllib2, sys, urllib

default = '36608'
url = 'http://thefuckingweather.com/?where='

# this will crash depending on inputs, definitely if you use a pipe
if len( sys.argv ) > 1:
    url = url + urllib.quote_plus( sys.argv[ 1 ])
else:
    url = url + default

html = urllib2.urlopen( url )
# if split is removed, you get the entirety of the page's html as a string, split
# turns it into a list
html = html.read().split( '\r\n' )

where = ''
temp = ''
remark = ''
flavor = ''

for line in html:
    if "FIND THAT SHIT" in line:
        print "I CAN'T FIND THAT SHIT"
        sys.exit()
    # magic numbers and dark voodoo
    if 'locationDisplaySpan' in line:
        where = line.strip()[ 71:-13 ]
    if 'p class="large"><span class="temperature"' in line:
        temp = line.strip()[ 54:-48 ]
    if 'remark' in line:
        remark = line.strip()[ 18:-4 ]
    if 'flavor' in line:
        flavor = line.strip()[ 24:-4 ]

temp = temp + u'\u00B0' + '?!'

print where
print temp
print remark
print flavor
