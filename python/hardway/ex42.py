## Animal is-a object (yes, sort of confusing) look at the extra credit
class Animal(object):
	pass

## Dog is-a Animal 
class Dog(Animal):

	def __init__(self, name):
		## Dog has-a name
		self.name = name

##  Cat is-a Animal
class Cat(Animal):

	def __init__(self, name):
		## Cat has-a name
		self.name = name

##  Person is-a Object
class Person(object):

	def __init__(self, name):
		## Person has-a name
		self.name = name

		## Person has-a pet of some kind
		self.pet = None

## Employee is-a Person
class Employee(Person):

	def __init__(self, name, salary):
		## Initializes itself and sets its name in one go
		## Employee has-a name
		super(Employee, self).__init__(name)
		## Employee has-a salary
		self.salary = salary

## Fish is-a object
class Fish(object):
	pass

## Salmon is-a Fish
class Salmon(Fish):
	pass

## Halibut is-a Fish
class Halibut(Fish):
	pass


## rover is-a Dog
rover = Dog("Rover")

## Satan is-a cat
satan = cat("Satan")

## Mary is-a person
mary = Person("Mary")

## Mary has-a pet
mary.pet = satan

## Frank is-a employee, has-a salary
frank = Employee("Frank", 120000)

## Frank has-a pet
frank.pet = rover

## Flipper is-a fish
flipper = Fish()

## Crouse is-a Salmon
crouse = Salmon()

## Harry is-a Halibut, is-a Fish, has-a name
harry = Halibut()
