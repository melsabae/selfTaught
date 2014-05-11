# Imports arguments from command line
from sys import argv

# Fills array with variables passed from command line; requires 2
script, filename = argv

# Sets txt variable to a command; opens $filename
txt = open(filename)

# Prints some text, then opens the filename and passes it to variable		placeholder
print "Here's your file %r:" % filename

# Invokes read method on the txt variable, which was == open(filename)
print txt.read()

# Prints a prompt for file name
print "Type the filename again:"

# Sets a variable to hold the file name through a prompted raw_input
file_again = raw_input("> ")

# Sets variable to open a file
txt_again = open(file_again)

# Spills contents of txt_again using the read method
print txt_again.read()

txt.close()
txt_again.close()
