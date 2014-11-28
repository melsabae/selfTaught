#!/usr/bin/env python2.7
import urllib2, sys

default = '36608'
url = 'http://thefuckingweather.com/?where='

# this will crash depending on inputs
if len( sys.argv ) > 1:
    url = url + sys.argv[ 1 ]
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
    # magic numbers and dark voodoo
    if 'locationDisplaySpan' in line:
        where = line.strip()[71:-13]
    if 'temperature' in line:
        temp = line.strip()[-7:-5] + '?!'
    if 'remark' in line:
        remark = line.strip()[18:-4]
    if 'flavor' in line:
        flavor = line.strip()[24:-4]

print where
print temp
print remark
print flavor
