keywords = ['and', 'del', 'from', 'not', 'while', 'as', 'elif', 'global',
		'or', 'with', 'assert', 'else', 'if', 'pass', 'yield',
		'break', 'except', 'import', 'print', 'class', 'exec',
		'in', 'raise', 'continue', 'finally', 'is', 'return',
		'def', 'for', 'lambda', 'try']

dataTypes = ['True', 'False', 'None', 'strings', 'numbers', 'floats',
		'lists']

stringEscapes = ['\\\\', '\\\'', '\\\"', '\\a', '\\b', '\\f', '\\n', '\\r',
		'\\t', '\\v']

stringFormats = ['%d', '%i', '%o', '%u', '%x', '%X', '%e', '%E', '%f', '%F',
		'%g', '%G', '%c', '%r', '%s', '%t']

operators = ['+', '-', '*', '**', '/', '//', '%', '<', '>' ,'<=', '>=',
		'==', '!=', '<>', '( )', '[ ]', '{ }', '@', '\'', ':',
		'.', '=', ';', '+=', '-=', '*=', '/=', '//=', '%=', '**=']

def printFunction(kword, does):
	print "%s" % kword + '  -  ' + does

# keywords
print("\t\tkeywords")
printFunction(keywords[0], "tests inclusive conditions using boolean logic.")
printFunction(keywords[1], "deletes objects, IE, elements from an array or list")
printFunction(keywords[2], "imports a specific variable, class, or function from a module")
printFunction(keywords[3], "reverses a the outcome of a logical test")
printFunction(keywords[4], "initiates a while loop")
printFunction(keywords[5], "creates an alias for a module")
printFunction(keywords[6], "inserts an else-if clause to an if block")
printFunction(keywords[7], "makes a local variable global")
printFunction(keywords[8], "tests coditions non-inclusively")
printFunction(keywords[9], "")
printFunction(keywords[10], "logical test that if it fails, will fail the entire script")
printFunction(keywords[11], "inserts an else clause into an if block")
printFunction(keywords[12], "logical test to determine if its code block should run")
printFunction(keywords[13], "does nothing, allows you to write a function declaration without implementing the function")
printFunction(keywords[14], "")
printFunction(keywords[15], "breaks execution out of a currently running loop")
printFunction(keywords[16], "raises an exception to be caught")
printFunction(keywords[17], "used to bring in other modules into a script")
printFunction(keywords[18], "prints text to stdout")
printFunction(keywords[19], "intitiates the creation of a class for user defined objects")
printFunction(keywords[20], "executes python code dynamically, IE, inline")
printFunction(keywords[21], "tests if a data object is in a container, or to traverse a range in a for loop")
printFunction(keywords[22], "used to raise a user defined exception")
printFunction(keywords[23], "used to force a loop to move to its next iteration, discarding the rest of its instruction set")
printFunction(keywords[24], "used to force an code block to execute after a try/catch block, always runs")
printFunction(keywords[25], "tests for identity, rather than congruency; IE checks to see if an object refers to the same memory location, rather than if they object is equivalent to another")
printFunction(keywords[26], "returns a value or an object at the end of a code path; returns different values based on location in an if/else block or a function will have a single return statement")
printFunction(keywords[27], "starts the creation of a user defined function")
printFunction(keywords[28], "used to iterate over items of a collection, in the order they are contained")
printFunction(keywords[29], "creates a new anonymous function, used inline")
printFunction(keywords[30], "attempts to execute its code, and gracefully handles exceptions instead of becoming fatal")

# dataTypes
print "\t\tdata types"
printFunction(dataTypes[0], "checks a condition to see if it is True as written")
printFunction(dataTypes[1], "checks a condition to see if it is False as written")
printFunction(dataTypes[2], "the data type is non existent, not known, or null/empty")
printFunction(dataTypes[3], "representation of words, an array/list of characters, used to represent textual data")
printFunction(dataTypes[4], "integer, floating point, and complex numbers represent numerical data")
printFunction(dataTypes[5], "represents real numbers in computing, measures continuous quantities in approxmiation")
printFunction(dataTypes[6], "equivalent to an array in C, a container that holds multiple items inside of it, however can containt multiple data types")

# stringEscapes
print "\t\tstring escapes"
printFunction(stringEscapes[0], "prints a double backslash")
printFunction(stringEscapes[1], "prints a single apostrophe/single quote")
printFunction(stringEscapes[2], "prints a single quotation mark/double quote")
printFunction(stringEscapes[3], "prints an ASCII Bell (BEL)")
printFunction(stringEscapes[4], "prints an ASCII Backspace (BS)")
printFunction(stringEscapes[5], "prints an ASCII Formfeed (FF)")
printFunction(stringEscapes[6], "prints an ASCII Linefeed (LF)")
printFunction(stringEscapes[7], "prints an ASCII Carriage Return (CR)")
printFunction(stringEscapes[8], "prints an ASCII horizontal tab (TAB)")
printFunction(stringEscapes[9], "prints an ASCII Vertical Tab (VT)")

# stringFormats
print "\t\t string formatters"
printFunction(stringFormats[0], "formats a string as Base 10 decimal integer")
printFunction(stringFormats[1], "formats string as an integer value")
printFunction(stringFormats[2], "octal format, outputs number in base 8")
printFunction(stringFormats[3], "deprecated - identical to \%d")
printFunction(stringFormats[4], "formats string as a lowercase hex value")
printFunction(stringFormats[5], "formats string as an uppercase hex value")
printFunction(stringFormats[6], "formats string as lowercase exponential floating point")
printFunction(stringFormats[7], "formats string as uppercase exponential floating point")
printFunction(stringFormats[8], "formats string as floating point decimal")
printFunction(stringFormats[9], "formats string as floating point decimcal")
printFunction(stringFormats[10], "formats string as floating point, uses lowercase exponential format if exponent is < -4 or not less than precision, decimal format otherwise")
printFunction(stringFormats[11], "formats string as floating point, uses uppercase exponential format if exponent is < -4 or not less than precision, decimal format otherwise")
printFunction(stringFormats[12], "formats strins as single character")
printFunction(stringFormats[13], "returns a string representation of an object, used for debugging")
printFunction(stringFormats[14], "returns a string representation of an object, prints nicely")
printFunction(stringFormats[15], "")

# operators
print "\t\toperators"
printFunction(operators[0], "adds")
printFunction(operators[1], "subtracts")
printFunction(operators[2], "multiplies")
printFunction(operators[3], "performs exponential calculations")
printFunction(operators[4], "divides")
printFunction(operators[5], "floor division, truncates the digits after a
		decimal point")
printFunction(operators[6], "performs modulo arithmetic")
printFunction(operators[7], "compares two expressions; greater than")
printFunction(operators[8], "compares two expressions; lesser than")
printFunction(operators[9], "comparison; lesser than or equal to")
printFunction(operators[10], "comparison; greater than or equal to")
printFunction(operators[11], "equivalent or congruent to")
printFunction(operators[12], "not equal to")
printFunction(operators[13], "deprecated; not equal to")
printFunction(operators[14], "")
printFunction(operators[15], "")
printFunction(operators[16], "")
printFunction(operators[17], "")
printFunction(operators[18], "")
printFunction(operators[19], "")
printFunction(operators[20], "")
printFunction(operators[21], "")
printFunction(operators[22], "")
printFunction(operators[23], "compound, adds and assigns to the left operand")
printFunction(operators[24], "compound, subrtracts and assigns to the left
		operand")
printFunction(operators[25], "compound, multiplies and assigns to the left
		operand")
printFunction(operators[26], "compound, divides and assigns to the left operand")
printFunction(operators[27], "compound, floor division and assigns to the left
operand")
printFunction(operators[28], "compound, modulo and assign to the left operand")
printFunction(operators[29], "compound, raise to power and assign to the left
operand")
