#include "Map.h"

#include "Scripts.h"

Map::Map()
{
	
}

Map::Map( const char* a_ccMapFile )
{
	if( !LoadMap( a_ccMapFile ) )
	{
		ASSERT( 0, "Map can't be loaded" );
	}
}

Map::~Map()
{
	delete MapLayers;
}

bool Map::LoadMap( const char* a_ccMapFile )
{
	// Variable for counts
	static int iElementCount; 
	iElementCount = 0;


	FILE* fh = fopen( a_ccMapFile, "r" );
	if( fh == NULL ) return false;

	// Okay, file works, now try to get it as XML
	XML::XMLDocument map;
	if( map.LoadFile( a_ccMapFile ) == 0 )
	{
		//Set up pointers
		XML::XMLNode* pMapNode;
		XML::XMLElement* pInfoNode;
		XML::XMLElement* pLayersNode;
		XML::XMLElement* pLayersElement;
		XML::XMLElement* pObjectsElement;
		XML::XMLElement* pObjectElement;

		// Start looking through the xml and sorting out
		// all the information
		if( ( pMapNode = map.FirstChildElement( "map" ) ) == NULL )
		{
			printf( "Error: Failed to find node 'map'\n" );
			return false;
		}

		if( ( pInfoNode = pMapNode->FirstChildElement( "info" ) ) == NULL )
		{
			printf( "Error: Failed to find node 'info'\n" );
			return false;
		}

		// General Map information
		m_iMapID = pInfoNode->IntAttribute( "id" );
		m_ccMapName = pInfoNode->Attribute( "title" );
		m_pMapSize[0] = pInfoNode->FloatAttribute( "width" );
		m_pMapSize[1] = pInfoNode->FloatAttribute( "height" );
		m_ccMapMusic = pInfoNode->Attribute( "BGMFile" );
		m_uiMapBG = LoadTexture( pInfoNode->Attribute( "BGImage" ) );

		if( ( pLayersNode = pMapNode->FirstChildElement( "layers" ) ) == NULL )
		{
			printf( "Error: Failed to find node 'layers'\n" );
			return false;
		}

		// Get layers count and allocate room for them
		iElementCount = pLayersNode->IntAttribute( "count" );
		MapLayers = new MapLayer[iElementCount];
		m_iNumOfLayers = iElementCount;
		pLayersElement = pLayersNode->FirstChildElement( "layer" );

		// Loop through layers
		for( int i = 0; i < iElementCount; ++i )
		{
			MapLayers[i].id = i;
			MapLayers[i].mapName = pLayersElement->Attribute( "id" );

			// Now loop through and get the objects on the layer
			pObjectsElement = pLayersElement->FirstChildElement( "objects" );
			int iObjectCount = pObjectsElement->IntAttribute( "count" );
			pObjectElement = pObjectsElement->FirstChildElement( "object" );
			MapLayers[i].Objects = new std::tuple<int,int,Vec3>[iObjectCount];

			for( int j = 0; j < iObjectCount; ++j )
			{
				int iObjectID, attribute;
				Vec3 pObjectPos;

				iObjectID = pObjectElement->IntAttribute( "id" );
				pObjectPos[0] = pObjectElement->FloatAttribute( "x" );
				pObjectPos[1] = pObjectElement->FloatAttribute( "y" );
				pObjectPos[2] = pObjectElement->FloatAttribute( "z" );
				attribute = pObjectElement->IntAttribute( "attribute" );

				MapLayers[i].Objects[j] = std::tuple<int,int,Vec3>(iObjectID, attribute, pObjectPos);

				pObjectElement = pObjectElement->NextSiblingElement( "object" );
				// Debug info - Map Objects
				if( bDebugInfo )
				{
					printf( "Map Object #%i: %f, %f. Layer #%i. \n", iObjectID, pObjectPos[0], pObjectPos[1], i );
				}
			}
			
			MapLayers[i].numObjects = iObjectCount;
			pLayersElement = pLayersElement->NextSiblingElement( "layer" );			

		}

		return true; // SUCCESS
	}

	// Well we didn't load anything, thats not going to help
	// us out in the long run at all.
	return false;
}
