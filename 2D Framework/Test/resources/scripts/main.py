### Main Entry point to scripts
import Game, pathfinding

GameProperties = {'resolutionX':500, 'resolutionY':500, 'fullScreen':False, 'windowTitle':"Window Title"}
map = None

reload(pathfinding)

def InitialiseScript():
	# Call any functions required for game setup
	# None so far...
	return None

def GetResolution():
	return (GameProperties['resolutionX'], GameProperties['resolutionY'])
	
def GetWindowTitle():
	return GameProperties['windowTitle']

def GetFullScreen():
	return GameProperties['fullScreen']
	
def CreateMap(x, y, count, blockedX, blockedY, blockedW, blockedH):
	global map
	map = pathfinding.NodeMap(x, y, count, blockedX, blockedY, blockedW, blockedH)
	return 0
	
def GetPath(start, end):
	path = map.FindPath(start, end)
	return path

def FindPathNode(start, end):
	pos = map.FindNextStep(start, end)
	return pos
	
def Wander( start ):
	pos = (start[0], start[1])
	newPos = map.Wander( start )
	return newPos
	
def Follow( start, end ):
	newVelocity = map.Follow( start, end )
	return newVelocity

def Flee( start, end ):
	newVelocity = map.Flee( start, end )
	return newVelocity
	
def FindClosest( start, numtargets, targets ):
	pos = map.FindClosest( start, numtargets, targets )
	return pos