from sys import argv

# Unpacks arguments from CLI into variables
script, input_file = argv

# method to print a file, f, passed into it as an argument
def print_all(f):
	print f.read()

# this method goes to the start of a file
def rewind(f):
	f.seek(0)

# this method prints a line count, then prints that line from file
def print_a_line(line_count, f):
	print line_count, f.readline(),

# Preps the file for printing
current_file = open(input_file)

print "First let's print the whole file:\n"

print_all(current_file)

print "Now let's rewind, kind of like a tape."

rewind(current_file)

print "Let's print three lines:"

# Starts the variable to line 1
current_line = 1
print_a_line(current_line, current_file)

current_line += 1
print_a_line(current_line, current_file)

current_line += 1
print_a_line(current_line, current_file)
