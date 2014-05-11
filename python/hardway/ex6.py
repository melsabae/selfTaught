# Normal string with 10 passed as the argument to the format specifier
x = "There are %d types of people." % 10

# Normal string variable
binary = "binary"

# Normal string variable
do_not = "don't"

# Variable that stores format specifiers for other variables
y = "Those who know %s and those who %s." % (binary, do_not)

print x
print y

# Prints the x variable out with single quotes to denote debugging
print "I said: %r." % x

# Manually enters the single quotes around the y string variable
print "I also said: '%s'." % y

# Boolean false variable
hilarious = False

# String with a debugging literal variable placeholder
joke_evaluation = "Isn't that joke so funny?! %r"

# Passes hilarious as an argument to joke_evaluation so that joke_evaluation
# can operate as it has a stored format specifier
print joke_evaluation % hilarious

# String variable
w = "This is the left side of..."

# String variable
e = "a string with a right side."

# Concatenation of 2 string variables
print w + e
