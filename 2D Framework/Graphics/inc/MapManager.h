////////////////////////////////////////////////////////////
// File: MapManager.h
// Author: Nick Smith
// Date Created: 10th July 2013
// Brief: Map Class
////////////////////////////////////////////////////////////
#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_

#include "Utilities.h"
class Map;

class DECLDIR MapManager
{
public:
	static void Create();
	static MapManager* Get();
	static void Delete();

	int LoadMap( const char* a_ccMapFile );
	bool LoadObjects( const char* a_ccObjectsFile );

	void DrawCurrentMap( int a_iLayer );

	void SwapToMap( int a_iMapID );
	void ToggleDrawMap( bool a_bToggle );

	inline Map* GetMap( int a_iID )
	{
		return Maps[a_iID-1];
	}
	
	inline MapObject* GetObjects()
	{
		return Objects;
	}
	
	MapLayer* GetMapLayer( int a_iID, int a_iLayerID );
	
	int GetMapLayerCount( int a_iID );
	int GetMapID();

protected:	
	MapManager();
	~MapManager();
	
	void Init();

	static MapManager* m_pInstance;
	bool m_bDrawMap;

	std::vector<Map*> Maps;
	MapObject* Objects;

	Map* m_pCurMap;
	Map* m_pPrevMap;

	// Drawing stuff
	GLuint m_uiMVAO;
	GLuint m_uiMVBO;
	GLuint m_uiMEBO;
	GLuint m_uiMShader;

	Vertex Vertices[4];

		
};

#endif // _MAP_MANAGER_H_