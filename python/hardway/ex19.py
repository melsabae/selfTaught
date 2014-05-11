# Defines a cheese and crackers method for showing the examples on how to
# use methods and pass arguments to them
def cheese_and_crackers(cheese_count, boxes_of_crackers):
	print "You have %d cheeses!" % cheese_count
	print "You have %d boxes of crackers!" % boxes_of_crackers
	print "Man that's enough for a party!"
	print "Get a blanket.\n"


print "We can just give the function numbers directly:"
# Calls cheese_and_crackers with 20 and 30 as arguments 
# to illustrate that we can send direct variables to the method.
cheese_and_crackers(20, 30)


print "OR, we can use variables from our scripts:"
# Initilizes some variables to illustrate calling a method and passing
# variables as arguments
amount_of_cheese = 10
amount_of_crackers = 50

cheese_and_crackers(amount_of_cheese, amount_of_crackers)


print "We can even do math inside too:"
# Passes expressions to a method to show that the method does not care
cheese_and_crackers(10 + 20, 5 + 6)


print "And we can combine the two, variables and match:"
# Passes variables in expressions to show that math can be done
# and let the method handle it instead of you doing it
cheese_and_crackers(amount_of_cheese + 100, amount_of_crackers + 1000)

def shutup(who, why):
	print "Hey %s, shut up!" % who
	print "Because %s!" % why



shutup("lenny", "you're annoying")

noun = "All of you"
reason = "You're giving me a headache."
shutup(noun, reason)
