from math import sqrt
import math
class point_2D:
	def __init__(self, x, y):
		self.x = x
		self.y = y

	def Euc_Dist(self, other):
		distance = sqrt((self.x - other.x)**2 + (self.y - other.y)**2)
		return distance

	def disp(self):
		print("x:", self.x, "y:", self.y)


class obstacles:
	radius = []
	centre = []
	def add_Obs(self, r, x, y, verbose = 0):
		c = point_2D(x, y)
		self.radius.append(r)
		self.centre.append(c)
		self.verbose = verbose

	def show_Obs(self):
		for index in range(len(self.radius)):
			print(self.radius[index], self.centre[index].x, self.centre[index].y)

	def check_Collision_Point(self, point):
		for index in range(len(self.radius)):
			if self.radius[index] >= point.Euc_Dist(self.centre[index]):
				if self.verbose == 1:
					print("Collision with ", self.centre[index].x, self.centre[index].y)
				return True
		return False


	def check_Collision_Line(self, point1, point2):
		# Referenced from https://stackoverflow.com/a/1079478
		if(self.check_Collision_Point(point1) or self.check_Collision_Point(point2)):
			return True # if one (or two) point is inside the circle

		m = 0
		if (point2.x==point1.x):
			m = (point2.y - point1.y)/(point2.x - (point1.x - 0.00001))
		else:
			m = (point2.y - point1.y)/(point2.x - point1.x)
		for index in range(len(self.radius)):
			if self.centre[index].x != point1.x:
				m1 = (self.centre[index].y - point1.y)/( self.centre[index].x - point1.x)
			else:
				m1 = (self.centre[index].y - point1.y)/( self.centre[index].x - (point1.x - 0.00001))
			if m*m1 == -1:
				Theta = math.pi/2
			else:
				Theta = math.atan((m - m1)/(1 + m*m1))
			dist = self.centre[index].Euc_Dist(point1)
			if (dist*math.sin(Theta) <= self.radius[index] and dist*math.cos(Theta) <= point1.Euc_Dist(point2)):
				#See figure from link: CD > r and AD < AB
				if self.verbose == 1:
					print("Collision with ", self.centre[index].x, self.centre[index].y)
				return True

		return False





	 