
from classFile import point_2D, obstacles
from Graph import Graph, Node
from random import randint
import math
import matplotlib.pyplot as plt
import matplotlib.animation
import numpy as np

def get_Point(point_near, point_far, delta): #get the point at delta distance from point_near, using point_rand(point_far)
	if point_near.x == point_far.x:
		return point_2D(point_near.x, point_near.y + delta)
	if point_near.y == point_far.y:
		return point_2D(point_near.x + delta, point_near.y)

	Theta = math.atan((point_far.y - point_near.y)/(point_far.x - point_near.x))
	if point_far.x < point_near.x:
		x_new = point_near.x - abs(math.cos(Theta)*delta)
	else:
		x_new = point_near.x + abs(math.cos(Theta)*delta)
	if point_far.y < point_near.y:
		y_new = point_near.y - abs(math.sin(Theta)*delta)
	else:
		y_new = point_near.y + abs(math.sin(Theta)*delta)
	
	return point_2D(x_new, y_new)

def addObstacles(Obs): #function to add obstacles
	Obs.add_Obs(2, 4.5, 3)#r, x, y
	Obs.add_Obs(2, 2, 12)
	Obs.add_Obs(3, 15, 15)

def plotObstacles(Obs, ax):
	color = ['yellow', 'green', 'orange', 'black']
	for index in range(len(Obs.radius)):
		x = Obs.centre[index].x
		y = Obs.centre[index].y
		r = Obs.radius[index]
		circle = plt.Circle((x,y),r, edgecolor = color[index%len(color)], facecolor = color[index%len(color)], fill = True)
		ax.add_artist(circle)

def plotStart_Goal_points(start, goal, ax):
	ax.scatter([start.x, goal.x], [start.y, goal.y], color = 'purple', marker = 's' )
	ax.text(goal.x + 0.5, goal.y + 0.5, 'GOAL', style='italic', bbox={'facecolor': 'pink', 'alpha': 0.2, 'pad': 6})
	ax.text(start.x + 0.5, start.y + 0.5, 'START', style='italic', bbox={'facecolor': 'pink', 'alpha': 0.2, 'pad': 6})

def ConnectGraphs(graph, point, Obs, ax, threshold_dist): #function that checks for graph connection
	node_near = graph.findNearest(graph.root, point)[0]
	point_near = node_near.point
	if point_near.Euc_Dist(point) <= threshold_dist and (not Obs.check_Collision_Line(point_near, point)):
		graph.add_lastNode(node_near)
		Line = ax.plot([point_near.x, point.x], [point_near.y, point.y], linewidth = 1, color = 'black', linestyle = '--')
		# ax.add_artist(Line)
		return True
	return False


xBound = 30
yBound = 30
delta = 1
start = point_2D(1, 1)
goal = point_2D(20, 20)
Obs = obstacles()
addObstacles(Obs)
numSamples = 100
curSamples = 0
threshold_dist = 2
G = Graph(start)
G_goal = Graph(goal)
cur_Graph = 0 #0 for start, 1 for goal

plt.ion()
fig, ax = plt.subplots()
plotStart_Goal_points(start, goal, ax)
x_arr, y_arr = [],[]
x_arr_g, y_arr_g = [],[]
sc = ax.scatter(x_arr,y_arr, marker = '*')
sc_g = ax.scatter(x_arr,y_arr, marker = '.', color = 'red')

plt.title('Finding Path')
plt.xlim(0,xBound)
plt.ylim(0,yBound)
plotObstacles(Obs, ax)
plt.draw()

while curSamples < numSamples:
	x = randint(0, xBound)
	y = randint(0, yBound)
	point_rand = point_2D(x, y)
	if cur_Graph == 0: #alternating between the 2 graphs(Target and start)
		point_near = G.findNearest(G.root, point_rand)[0].point
	else:
		point_near = G_goal.findNearest(G_goal.root, point_rand)[0].point
	point_new = get_Point(point_near, point_rand, delta)
	if not Obs.check_Collision_Line(point_near, point_new):

		if cur_Graph == 0:
			node = G.addNode(point_new)
			x_arr.append(point_new.x)
			y_arr.append(point_new.y)
			sc.set_offsets(np.c_[x_arr,y_arr])
			if ConnectGraphs(G_goal, point_new, Obs, ax, threshold_dist):
				G.add_lastNode(node)
				break
		else:
			node = G_goal.addNode(point_new)
			x_arr_g.append(point_new.x)
			y_arr_g.append(point_new.y)
			sc_g.set_offsets(np.c_[x_arr_g,y_arr_g])
			curSamples+=1		
			if ConnectGraphs(G, point_new, Obs, ax, threshold_dist):

				G_goal.add_lastNode(node)
				break

		fig.canvas.draw_idle()
		plt.pause(0.01)
		cur_Graph = 1 - cur_Graph




plt.waitforbuttonpress()
G_path = np.array(G.findPath()) 
G_goal_path = np.array(G_goal.findPath())

fig2, ax2 = plt.subplots()
plotObstacles(Obs, ax2)
plotStart_Goal_points(start, goal, ax2)
plt.xlim(0,xBound)
plt.ylim(0,yBound)
ax2.plot(G_path[:, 0], G_path[:, 1])
ax2.plot(G_goal_path[:, 0], G_goal_path[:, 1])
ax2.plot([G.lastNode.point.x, G_goal.lastNode.point.x], [G.lastNode.point.y, G_goal.lastNode.point.y], linewidth = 1, color = 'black', linestyle = '--')
plt.title("Final Path")
plt.show()
plt.waitforbuttonpress()


#Reference Paper: https://www.sciencedirect.com/science/article/pii/S2405896319323250
#Video: https://www.youtube.com/watch?v=xAmN8WnltRY