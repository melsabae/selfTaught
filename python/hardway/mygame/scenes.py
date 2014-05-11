from sys import exit
import random


class Scene(object):
	
	actions = {
			"suicide": "You beat your head into the ground until your cranium shatters,\n\t\tspilling your brains out. That's not good for your health.\n\t\tAlso, the shotgun would have been quicker and less painful."
			}

	consequences = {
			'suicide': 'gamelost'
			}

	actionTaken = None


	def enter(self):
		print "This scene is not yet configured. Subclass it and implement enter()."
		exit(1)

	def finalizeScene(self):
		print "\n\t\tWhat do you do?"

		for key in self.actions:
			print "\t\t\t:  %s" % key
		
		while self.actionTaken not in self.actions:

			self.actionTaken = raw_input('> ')

			if self.actionTaken in self.actions:
				print "\t\t", self.actions[self.actionTaken]
				return  self.consequences[self.actionTaken]
			else:
				print "Try again."


class GameEnd(Scene):

	def __init__(self, status):
		self.status = status

	def enter(self):
		snark = [
				"You'd have to try hard to fail harder than that.",
				"umad?",
				"Game over son.",
				"Go play something else."
				]
		
		if self.status == "win":
			print "You win!"
		elif self.status == "lose":
			print random.choice(snark), "\n"
		elif self.status == "gaveup":
			print "You give up, go back home, sleep off the headache, and die old over many years. Probably the best choice all in all."
		else:
			print "Invalid status passed to GameEnd object."
			exit(1)
			
		exit(0)


class Road(Scene):

	def enter(self):
		print """
		You leave your home and in front of you sprawls a road that
		you have traveled before, however, it looks alien tonight.
		This road is not occupied by anything or anyone, and is
		dead quiet. Living outside of the city limits has its
		advantages, but tonight you don't trust this road. You
		don't trust this county.
		
		Fuck this world in general.

		You go back inside the house, and grab your 12 gauge.
		Checking what you have loaded: 3 in the tube, 1 in the pipe,
		and a full 7 round side saddle. You pull 5 from the saddle
		and feed them into the pipe - then sling the rig over your
		shoulder, pulling the sling tight.


		Tonight, of all nights, you need a headache powder.

		Tonight of all nights, you will earn that headache powder.
		"""

		self.actions['continue'] = "You go on down the road, towards the dimly lit sign\n\t\tof a gas station."

		self.consequences['continue'] = 'gas_station'

		return self.finalizeScene()


class GasStation(Scene):

	def enter(self):
		pass


class AbandonedMarket(Scene):

	def enter(self):
		pass


class PowerPlant(Scene):

	def enter(self):
		pass
