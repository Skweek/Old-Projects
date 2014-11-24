////////////////////////////////////////////////////////////
// File: Map.h
// Author: Nick Smith
// Date Created: 10th July 2013
// Brief: Map Class
////////////////////////////////////////////////////////////
#ifndef _MAP_H_
#define _MAP_H_

#include "Utilities.h"

class DECLDIR Map
{
public:
	Map();
	Map( const char* a_ccMapFile );
	~Map();

	bool LoadMap( const char* a_ccMapFile );

	inline std::tuple<int,int,Vec3>* GetObjects( int a_iLayerID )
	{
		return MapLayers[a_iLayerID].Objects;
	}
	
	inline int GetID()
	{
		return m_iMapID;
	}

	friend class MapManager;

protected:
	int m_iMapID;
	const char* m_ccMapName;
	Vec2 m_pMapSize;
	const char* m_ccMapMusic;
	GLuint m_uiMapBG;

	int m_iNumOfLayers;
	int m_iNumOfAttribs;

	MapLayer* MapLayers;
	MapAttribute* MapAttributes;
	
};

#endif // _MAP_H_