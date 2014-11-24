from datetime import datetime # Used to time how long it takes to calculate paths (for debugging/testing)
from math import sqrt # Used for vector magnitudes
import random # Used for wander path

# Node class
class Node:
# x/y positions are the center of the node which is 
# the center of a map grid point
	x = 0
	y = 0
	G = 0 # cost from start point
	H = 0 # cost to destination
	F = 0 # total cost
	ParentNode = None
	
	
	def __init__( self, ax, ay ):
		self.x = ax
		self.y = ay
		self.G = 0
		self.H = 0
		self.F = 0
		self.open = True

class NodeMap:
# Each node will be 10px by 10px for now to make things faster, need to figure out the
# ideal ratio of actual size:nodes

	# Dictionary of directions around the node map and where we move in the array
	# For this north is to the top of the screen.
	""" (Direction).(Dictionary key)
	NW.1	N.2		NE.3
	W.4		P		E.5
	SW.6	S.7		SE.8
	"""
	directions = {2: (0,-1), 5: (1,0), 7: (0,1), 4: (-1,0), 1: (-1,-1), 3: (1,-1), 6: (-1,1), 8: (1,1)}
	firstWander = True
	# Seed our number generator 
	random.seed(None)

	def __init__( self, x, y, count, blockedX, blockedY, blockedW, blockedH ):
		self.sizeX = x / 10
		self.sizeY = y / 10
		# loop through size and add an empty node to the nodeslist
		self.openlist = []
		self.closedlist = []
		self.currentpath = []
		self.blockednodes = []
		self.nodeslist = [[Node(0,0) for x in range(self.sizeY)] for y in range(self.sizeX)]
		for j in range(self.sizeY):
			for i in range(self.sizeX):
				tn = Node(i,j)
				self.nodeslist[i][j] = tn
		# now loop through 'count' and get the pos/size
		# of the blocked objects
		for i in range(count):
			tnode = Node(blockedX[i]/10,blockedY[i]/10)
			tnode.open = False
			self.nodeslist[blockedX[i]/10][blockedY[i]/10] = tnode
			self.closedlist.append(tnode)
			for h in range(blockedH[i]/10):				
				for w in range(blockedW[i]/10):
					x1 = w+(blockedX[i]/10)
					y1 = h+(blockedY[i]/10)
					if x1 >= self.sizeX:
						x1 = self.sizeX - 1
					if y1 >= self.sizeY:
						y1 = self.sizeY - 1	
					tnode = Node(x1,y1)
					tnode.open = False
					self.nodeslist[x1][y1] = tnode
					self.blockednodes.append(tnode)
		print str(len(self.blockednodes)) + " on blocked list."
	
	def CheckSurroundingNodes( self, node ):
		count = 0
		for v in ((0,-1),(-1,0),(1,0),(0,1), (-1,-1),(1,-1),(-1,1),(1,1)):
			x2 = node.x + v[0]
			y2 = node.y + v[1]
			if x2 < 0:
				continue
			if y2 < 0:
				continue
			try:			
				tnode = self.nodeslist[x2][y2]
				if (tnode in self.closedlist):	
					count += 1
			except:
				pass # Out of bounds, disregard it
		return count 
		
	def OpenSurroundingNodes( self, node, end ):
		for v in ((0,-1),(-1,0),(1,0),(0,1), (-1,-1),(1,-1),(-1,1),(1,1)):
			x2 = node.x + v[0]
			y2 = node.y + v[1]
			if x2 < 0:
				continue
			if y2 < 0:
				continue
			try:			
				tnode = self.nodeslist[x2][y2]
				if (tnode.open == True):	
					if (tnode not in self.openlist):
						tnode.ParentNode = node
						if abs(v[0]) == abs(v[1]):
							tnode.G = node.G + 40
						else:
							tnode.G = node.G + 10
						tnode.H = (tnode.x - end[0])**2 + (tnode.y - end[1])**2
						tnode.F = node.G + tnode.H
						self.openlist.append(tnode)
				if tnode.F > ( node.G + tnode.H ): 
					tnode.ParentNode = node 
					tnode.F = tnode.G + tnode.H 
			except:
				pass # Out of bounds, disregard it
				
	def FindPath( self, start, end ):
		for j in range(self.sizeY):
			for i in range(self.sizeX):
				tempNode = self.nodeslist[i][j]
				if(tempNode not in self.blockednodes):
					self.nodeslist[i][j].open = True
		
		start[0] /= 10
		start[1] /= 10
		end[0] /= 10
		end[1] /= 10
		CurrentNode = Node(0,0)
		self.currentpath = []
		self.openlist = []
		returnpath = []
		
		# If either are blocked it will give up
		if(self.nodeslist[start[0]][start[1]].open == False):
			print "Start point is blocked."
		elif(self.nodeslist[end[0]][end[1]].open == False):
			print "End point is blocked."
		else:
			# set start node as current node
			CurrentNode = self.nodeslist[start[0]][start[1]]
			iterations = 0
			# Now we find the path, super fun times
			
			starttime = datetime.now()
			while True:
				iterations += 1
				# add current node to closed list
				CurrentNode.open = False
				
				# If it is the final node then stop looking. Obviously.
				if CurrentNode.x == end[0] and CurrentNode.y == end[1]:
					break
				# add intitial surrounding 8 nodes to open list so we can check them
				self.OpenSurroundingNodes( CurrentNode, end )	
				
				if len(self.openlist) > 0:				
					# pick the one with the lowest F value and set it as current	
					self.openlist.sort( key=lambda x:x.F )
					n = self.openlist[0]
					CurrentNode = n
					self.openlist.remove(n)
					
			elapsed = datetime.now() - starttime
			while True:
				# Now we go backwards and try to find the actual path
				if( CurrentNode not in self.currentpath):
					self.currentpath.append(CurrentNode)
					CurrentNode = CurrentNode.ParentNode
					if CurrentNode == None:
						break
				else:
					break
			print str(elapsed)
					
			for n in reversed(self.currentpath):
				returnpath.append(n.x*10)
				returnpath.append(n.y*10)
			return (len(self.currentpath), returnpath)
	
	def FindClosest( self, start, numtargets, targets ):
		for j in range(self.sizeY):
			for i in range(self.sizeX):
				tempNode = self.nodeslist[i][j]
				if(tempNode not in self.blockednodes):
					self.nodeslist[i][j].open = True
		
		start[0] /= 10
		start[1] /= 10
		
		self.currentpath = []
		self.openlist = []
		CurrentNode = Node(0,0)
		returnpath = []
		
		# populate targets list 
		targetslist = [Node(0,0) for x in range(numtargets)]
		for i in range(numtargets):
			targetnode = Node(targets[i][0]/10,targets[i][1]/10)
			targetslist[i] = targetnode
		
		# If either are blocked it will give up
		if(self.nodeslist[start[0]][start[1]].open == False):
			print "Start point is blocked."
		else:
			# set start node as current node
			CurrentNode = self.nodeslist[start[0]][start[1]]
			iterations = 0
			# Now we find the path, super fun times
			
			starttime = datetime.now()
			while True:
				iterations += 1
				# add current node to closed list
				CurrentNode.open = False
				
				# If it is the final node then stop looking. Obviously.
				done = False
				for node in targetslist:
					if CurrentNode.x == node.x:
						if CurrentNode.y == node.y:
							done = True
				if( done ):
					break
				# add intitial surrounding 8 nodes to open list so we can check them
				self.OpenSurroundingNodes( CurrentNode, [0,0] )	
				
				if len(self.openlist) > 0:				
					# pick the one with the lowest F value and set it as current	
					self.openlist.sort( key=lambda x:x.G )
					n = self.openlist[0]
					CurrentNode = n
					self.openlist.remove(n)
				else:
					print "Couldn't find close things"					
					elapsed = datetime.now() - starttime			
					print str(elapsed)
					
					return (start[0], start[1])
					
			elapsed = datetime.now() - starttime
			
			print str(elapsed)
							
		return (CurrentNode.x, CurrentNode.y)
	
	def FindNextStep( self, start, end ):
		for j in range(self.sizeY):
			for i in range(self.sizeX):
				tempNode = self.nodeslist[i][j]
				if(tempNode not in self.blockednodes):
					self.nodeslist[i][j].open = True
		start[0] /= 10
		start[1] /= 10
		end[0] /= 10
		end[1] /= 10
		self.currentpath = []
		self.openlist = []
		CurrentNode = Node(0,0)
		returnpath = []
		
		# If either are blocked it will give up
		if(self.nodeslist[start[0]][start[1]].open == False):
			print "Start point is blocked."
		elif(self.nodeslist[end[0]][end[1]].open == False):
			print "End point is blocked."
		else:
			# set start node as current node
			CurrentNode = self.nodeslist[start[0]][start[1]]
			iterations = 0
			# Now we find the path, super fun times
			
			starttime = datetime.now()
			while True:
				iterations += 1
				# add current node to closed list
				CurrentNode.open = False
				
				# If it is the final node then stop looking. Obviously.
				if CurrentNode.x == end[0] and CurrentNode.y == end[1]:
					break
				# add intitial surrounding 8 nodes to open list so we can check them
				self.OpenSurroundingNodes( CurrentNode, end )	
				
				if len(self.openlist) > 0:				
					# pick the one with the lowest F value and set it as current	
					self.openlist.sort( key=lambda x:x.F )
					n = self.openlist[0]
					CurrentNode = n
					self.openlist.remove(n)
					
			elapsed = datetime.now() - starttime
			while True:
				# Now we go backwards and try to find the actual path
				if( CurrentNode not in self.currentpath):
					self.currentpath.append(CurrentNode)
					CurrentNode = CurrentNode.ParentNode
					if CurrentNode == None:
						break
				else:
					break
			print str(elapsed)
			
			for n in reversed(self.currentpath):
				returnpath.append(n.x*10)
				returnpath.append(n.y*10)
				
			return (returnpath[0], returnpath[1])
	
	def Follow( self, start, end ):
		newVelocity = ( ( end[0] - start[0] ), ( end[1] - start[1] ) )
	
		magnitude = sqrt( ( newVelocity[0] * newVelocity[0] ) + ( newVelocity[1] * newVelocity[1] ) );
		
		if( magnitude != 0 ):
			xVelocity = newVelocity[0] / magnitude
			yVelocity = newVelocity[1] / magnitude
		else:
			xVelocity = 0
			yVelocity = 0
		
		# If either the xVelocity or yVelocity is going to put us on a blocked node we return 0
		# This is not exactly a good approach as things can get stuck. What should be happening is
		# if we notice we are stuck with do a quick djikstra/A* to find the path to the closest open node
		# to our target
		
		# We need to get velocity to either -1 or 1
		if( xVelocity < 0 ):
			xVelocity = -1
		if( xVelocity > 0 ):
			xVelocity = 1
		if( yVelocity < 0 ):
			yVelocity = -1
		if( yVelocity > 0 ):
			yVelocity = 1
			
		nodetocheckX = start[0]/10 + int(xVelocity)
		nodetocheckY = start[1]/10 + int(yVelocity)
		try:
			if self.nodeslist[nodetocheckX][start[1]/10] in self.blockednodes:
				xVelocity = 0
		except:
			pass # out of bounds
		try:
			if self.nodeslist[start[0]/10][nodetocheckY] in self.blockednodes:
				yVelocity = 0
		except:
			pass # out of bounds
		# return our final velocity
		return (xVelocity, yVelocity)
		
	def Flee( self, start, end ):
		newVelocity = ( ( end[0] - start[0] ) * -1, ( end[1] - start[1] ) * -1)
		
		magnitude = sqrt( ( newVelocity[0] * newVelocity[0] ) + ( newVelocity[1] * newVelocity[1] ) );

		if( magnitude != 0 ):
			xVelocity = newVelocity[0] / magnitude
			yVelocity = newVelocity[1] / magnitude
		else:
			xVelocity = 0
			yVelocity = 0
		
		# If either the xVelocity or yVelocity is going to put us on a blocked node we return 0
		# This is not exactly a good approach as things can get stuck. What should be happening is
		# if we notice we are stuck with do a quick djikstra/A* to find the path to the closest open node
		# to our target
		
		# We need to get velocity to either -1 or 1
		if( xVelocity < 0 ):
			xVelocity = -1
		if( xVelocity > 0 ):
			xVelocity = 1
		if( yVelocity < 0 ):
			yVelocity = -1
		if( yVelocity > 0 ):
			yVelocity = 1
			
		nodetocheckX = start[0]/10 + int(xVelocity)
		nodetocheckY = start[1]/10 + int(yVelocity)
		
		try:
			if self.nodeslist[nodetocheckX][start[1]/10] in self.blockednodes:
				xVelocity = 0
		except:
			pass # out of bounds
		try:
			if self.nodeslist[start[0]/10][nodetocheckY] in self.blockednodes:
				yVelocity = 0
		except:
			pass # out of bounds
		# return our final velocity
		return (xVelocity, yVelocity)
	
	def Wander( self, pos ):
		# We pick a random spot in front of us or diagonally in front of us
		# and if it isn't blocked move there.
		newDirection = random.randint(1,8)	
		
		movement = self.directions[newDirection]
		
		newVelocity = ( ( ( pos[0] + ( movement[0] * 10 ) ) - pos[0] ), ( ( pos[1] + ( movement[1] * 10 ) ) - pos[1] ) )
		"""
		|cos(15)  sin(15) |	|start[0] + ProjectionDistance|
		|-sin(15)  cos(15)|	|start[1] + ProjectionDistance|
		
		Project point out and then find normalise to find the velocity
		
		We need to pass through the current position and the previous velocity
		Get the angle of the previous velocity and add or subtract 0-45 to it
		Project out again, find new velocity, repeat.
		"""
		
		magnitude = sqrt( ( newVelocity[0] * newVelocity[0] ) + ( newVelocity[1] * newVelocity[1] ) );

		if( magnitude != 0 ):
			return ( newVelocity[0] / magnitude, newVelocity[1] / magnitude )
		else:
			return ( 0, 0 )		
		print "Wondering around"