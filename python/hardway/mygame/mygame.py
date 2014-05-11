from scenes import Scene, GameEnd, Road, GasStation, AbandonedMarket, PowerPlant


class Engine(object):

	def __init__(self, scene_map):
		self.scene_map = scene_map

	def play(self):
		current_scene = self.scene_map.opening_scene()

		try:
			while True:
				print "\n----------"
				next_scene = current_scene.enter()
				current_scene = self.scene_map.next_scene(next_scene)
		except EOFError:
			pass
		except KeyboardInterrupt:
			pass

		print "\n\t\t\tBye!"
		exit(0)


class Map(object):

	scenes = {
			'road': Road(),
			'gas_station': GasStation(),
			'abandoned_market': AbandonedMarket(),
			'power_plant': PowerPlant(),
			'gamelost': GameEnd("lose"),
			'gamewin': GameEnd("win"),
			'gaveup': GameEnd("gaveup")
			}


	def __init__(self, start_scene):
		self.start_scene = start_scene 

	def next_scene(self, scene_name):
		return Map.scenes[scene_name]

	def opening_scene(self):
		return self.next_scene(self.start_scene)


a_map = Map('road')
a_game = Engine(a_map)
a_game.play()
