#include "MapManager.h"

#include "Window.h"
#include "Map.h"
#include "FontManager.h"
#include "Scripts.h"

MapManager* MapManager::m_pInstance = nullptr;

void MapManager::Create()
{
	if( !m_pInstance )
	{
		m_pInstance = new MapManager();
	}
}

MapManager* MapManager::Get()
{
	if( !m_pInstance )
	{
		m_pInstance = new MapManager();
	}

	return m_pInstance;
}

void MapManager::Delete()
{
	if( m_pInstance )
	{
		delete m_pInstance;
	}
}

MapManager::MapManager()
{
	Init();
	Maps.clear();
}

MapManager::~MapManager()
{
	for( int i = 0; i < (int)Maps.size(); ++i )
	{
		delete Maps[i];
	}
	Maps.clear();
}

void MapManager::Init()
{
	glGenBuffers( 1, &m_uiMVBO );
	glGenBuffers( 1, &m_uiMEBO );
	glGenVertexArrays( 1, &m_uiMVAO );

	m_uiMShader = LoadShaders( "shaders/sprite-vertex-shader.glsl", "shaders/sprite-fragment-shader.glsl" );	

	glBindVertexArray( m_uiMVAO );

	Vertices[0].Pos = Vec4( 0.f, 0.f, 0.f, 1.f );
	Vertices[0].UV = Vec2( 0.f, 1.f );

	Vertices[1].Pos = Vec4( 1.f, 0.f, 0.f, 1.f );
	Vertices[1].UV = Vec2( 1.f, 1.f );

	Vertices[2].Pos = Vec4( 0.f, 1.f, 0.f, 1.f );
	Vertices[2].UV = Vec2( 0.f, 0.f );

	Vertices[3].Pos = Vec4( 1.f, 1.f, 0.f, 1.f );
	Vertices[3].UV = Vec2( 1.f, 0.f );

	glBindBuffer( GL_ARRAY_BUFFER, m_uiMVBO );
	glBufferData( GL_ARRAY_BUFFER, 4 * sizeof( Vertex ), Vertices, GL_STATIC_DRAW );

	GLuint elements[] = {
		0, 1, 2,
		1, 3, 2
	};

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_uiMEBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

	glUseProgram( m_uiMShader );

	glBindFragDataLocation( m_uiMShader, 0, "outColor" );
	
	
	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation( m_uiMShader, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof( Vertex ), 0 );

	GLint texAttrib = glGetAttribLocation( m_uiMShader, "texcoord" );
	glEnableVertexAttribArray( texAttrib );
	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)( sizeof( Vec4 ) ) );

	glBindVertexArray( 0 );

	GLuint ProjectionID = glGetUniformLocation( m_uiMShader, "Projection" );
	GLuint ViewID = glGetUniformLocation( m_uiMShader, "View" );

	glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );
	glUniformMatrix4fv( ViewID, 1, false, (float*)Windows::Get()->GetWindow()->pView );
	
	GLuint minUV = glGetUniformLocation( m_uiMShader, "minUV" );
	glUniform2fv( minUV, 1, Vec2( 0.f, 0.f ) );

	GLuint diffUV = glGetUniformLocation( m_uiMShader, "diffUV" );
	glUniform2fv( diffUV, 1, Vec2( 1.f, 1.f ) );

	m_pCurMap = 0;
}

int MapManager::LoadMap( const char* a_ccMapFile )
{
	Map* tempMap;
	printf( "Loading map: %s...\n", a_ccMapFile );
	if( ( tempMap = new Map( a_ccMapFile ) ) != NULL )
	{
		Maps.push_back( tempMap );
		m_pCurMap = tempMap;

		// Create Python Map
		int iObjectCount = 0;
		
		for( int i = 0; i < GetMapLayerCount(GetMapID()); ++i )
		{
			iObjectCount += GetMapLayer( GetMapID(), i)->numObjects;
		}

		Vec4* pMapArgs = new Vec4[iObjectCount];
		std::tuple<int,int,Vec3>* pMapObjects = new std::tuple<int,int,Vec3>[iObjectCount];

		int count = 0;
		for( int i = 0; i < GetMapLayerCount(GetMapID()); ++i )
		{
			for( int j = 0; j < GetMapLayer( GetMapID(), i)->numObjects; ++j )
			{
				pMapObjects[count] = GetMapLayer( GetMapID(), i)->GetObject(j);		
				++count;
			}
		}

		for( int i = 0; i < iObjectCount; ++i )
		{
			MapObject pObject = Objects[std::get<0>(pMapObjects[i])];

			pMapArgs[i].m_fX = std::get<2>(pMapObjects[i])[0];
			pMapArgs[i].m_fY = std::get<2>(pMapObjects[i])[1];
			pMapArgs[i].m_fZ = pObject.size[0];
			pMapArgs[i].m_fW = pObject.size[1];			
		}	

		CreatePathMap( GetMap( GetMapID() )->m_pMapSize, iObjectCount, pMapArgs );

		delete pMapArgs;
		delete pMapObjects;

		return m_pCurMap->m_iMapID;
	}
	return NULL;

}

bool MapManager::LoadObjects( const char* a_ccObjectsFile )
{
	FILE* fh = fopen( a_ccObjectsFile, "r" );
	if( fh == NULL ) return false;

	// Okay, file works, now try to get it as XML
	XML::XMLDocument objects;
	if( objects.LoadFile( a_ccObjectsFile ) == 0 )
	{
		//Set up pointers
		XML::XMLNode* pObjectsNode;
		XML::XMLElement* pObjectNode;
		XML::XMLElement* pObjectElement;

		// Start looking through the xml and sorting out
		// all the information
		if( ( pObjectsNode = objects.FirstChildElement( "mapobjects" ) ) == NULL )
		{
			printf( "Error: Failed to find node 'mapobjects'\n" );
			return false;
		}

		if( ( pObjectNode = pObjectsNode->FirstChildElement( "objects" ) ) == NULL )
		{
			printf( "Error: Failed to find node 'info'\n" );
			return false;
		}

		
		// Get layers count and allocate room for them
		int iElementCount = pObjectNode->IntAttribute( "count" );
		Objects = new MapObject[iElementCount];
		pObjectElement = pObjectNode->FirstChildElement( "object" );

		// Loop through objects
		for( int i = 0; i < iElementCount; ++i )
		{
			int objectid = pObjectElement->IntAttribute( "id" );
			char Buff[256];
			sprintf( Buff, "flflf" );
			Objects[objectid].objectName = Buff;
			Objects[objectid].objectImage = LoadTexture( pObjectElement->Attribute( "imageFile" ) );
			Objects[objectid].size[0] = pObjectElement->FloatAttribute( "width" );
			Objects[objectid].size[1] = pObjectElement->FloatAttribute( "height" );
		
			pObjectElement = pObjectElement->NextSiblingElement( "object" );
		}

		return true; // SUCCESS
	}

	// Well we didn't load anything, thats not going to help
	// us out in the long run at all.
	return false;
}

void MapManager::DrawCurrentMap( int a_iLayer )
{
	if( m_pCurMap != 0 && m_bDrawMap )
	{
		// Get the map layer needed
		MapLayer layer = m_pCurMap->MapLayers[a_iLayer];
	
		// Variable stuff that we only need once	
		GLuint ModelID = glGetUniformLocation( m_uiMShader, "Model" );
		GLuint ProjectionID = glGetUniformLocation( m_uiMShader, "Projection" );
		glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );

		// If it is layer 0 ( Ground layer ) then draw the background first
		if( a_iLayer == 0 )
		{
			glBindVertexArray( m_uiMVAO );
			glUseProgram( m_uiMShader );	

			Matrix4 Size = Matrix4( m_pCurMap->m_pMapSize[0], 0.f, 0.f, 0.f, 
										0.f, m_pCurMap->m_pMapSize[1], 0.f, 0.f, 
										0.f, 0.f, 1.f, 0.f, 
										0.f, 0.f, 0.f, 1.f );

			glUniformMatrix4fv( ModelID, 1, false, Size );

			glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, m_pCurMap->m_uiMapBG );

			glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );		
		}

		// Draw Layer
		int objects = layer.numObjects;
		
		// Get the first object of that layer
		for( int j = 0; j < objects; ++j )
		{
			// Draw the object
			glBindVertexArray( m_uiMVAO );
			glUseProgram( m_uiMShader );	

			GLuint ProjectionID = glGetUniformLocation( m_uiMShader, "Projection" );
			glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );

			//Get the object
			MapObject pObject = Objects[std::get<0>(layer.Objects[j])];
	
			Vec3 size = Vec3( pObject.size[0], pObject.size[1], 0.f );
			Vec3 pos = std::get<2>(layer.Objects[j]);

			Matrix4 Size = Matrix4( size[0], 0.f, 0.f, 0.f, 
										0.f, size[1], 0.f, 0.f, 
										0.f, 0.f, 1.f, 0.f, 
										pos[0], pos[1], 0.f, 1.f );

			GLuint ModelID = glGetUniformLocation( m_uiMShader,"Model" );
			glUniformMatrix4fv( ModelID, 1, false, Size );

			glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, pObject.objectImage );

			glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );		

			glBindTexture( GL_TEXTURE_2D, 0 );
			glUseProgram( 0 );	
			glBindVertexArray( 0 );
			// Next object
		}
	}
}

void MapManager::SwapToMap( int a_iMapID )
{
	for( int i = 0; i < (int)Maps.size(); ++i )
	{
		Map* map = Maps[i];
		if( map->m_iMapID == a_iMapID )
		{
			m_pCurMap = map;
		}
	}
}

void MapManager::ToggleDrawMap( bool a_bToggle )
{
	m_bDrawMap = a_bToggle;
}

MapLayer* MapManager::GetMapLayer( int a_iID, int a_iLayerID )
{
	for( int i = 0; i < (int)Maps.size(); ++i )
	{
		Map* map = Maps[i];
		if( map->m_iMapID == a_iID )
		{
			return &map->MapLayers[a_iLayerID];
		}
	}
	return NULL;
}
	
int MapManager::GetMapLayerCount( int a_iID )
{
	for( int i = 0; i < (int)Maps.size(); ++i )
	{
		Map* map = Maps[i];
		if( map->m_iMapID == a_iID )
		{
			return map->m_iNumOfLayers;
		}
	}
	return NULL;
}

int MapManager::GetMapID()
{
	return m_pCurMap->GetID();
}