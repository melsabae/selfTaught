numbers = []

def loop(increment):
	last = 6
	i = 0
	while i < last:
		print "At the top i is %d" % i
		numbers.append(i)
		i += increment
		print "Numbers now: ", numbers
		print "At the bottom i is %d" % i

loop(5)

print "The numbers:"

for num in numbers:
	print num
