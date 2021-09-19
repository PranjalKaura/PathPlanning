import math
class Graph:
	def __init__(self, point):
		self.root = Node(point)
		self.lastNode = None

	def findNearest(self, node, point): #find the nearest node form the given point
		arr = [node, node.point.Euc_Dist(point)]
		for child in node.children:
			arr_temp = self.findNearest(child, point) #recursion
			if arr_temp[1] < arr[1]:
				arr = arr_temp
		return arr

	def addNode(self, point):
		node = self.findNearest(self.root, point)[0]
		newNode = Node(point)
		node.addNode(newNode)
		return newNode

	def add_lastNode(self, node):
		self.lastNode = node


	def traverseGraph(self, node): #traversal system(for my understanding)
		node.point.disp()
		print("Now children")
		for child in node.children:
			self.traverseGraph(child)

		print("END children")

	def findPath(self):
		points_Arr = []
		node = self.lastNode
		while(node!=None):
			points_Arr.append([node.point.x, node.point.y])
			node = node.parent
		return points_Arr





class Node:
	def __init__(self, point):
		self.point = point
		self.children = []
		self.parent = None

	def addNode(self, node):
		self.children.append(node)
		node.parent = self
