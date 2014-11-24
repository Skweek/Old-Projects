#include "Actor.h"
#include "ActorLimb.h"


Actor::Actor( const char* a_ccFile, Vec2 a_pPos )
{
	// Set the origin position of the actor, this is the centre
	// and is what each limb will be relative to
	m_pPos = a_pPos;

	LoadActor( a_ccFile );
	m_ccActorFile = a_ccFile;
}

void Actor::LoadActor( const char* a_ccFile )
{
	// Load in the XML file and create the limbs
	// Try to open file first
	FILE* fh = fopen( a_ccFile, "r" );
	if( fh != NULL ) 
	{
		// Okay, file works, now try to get it as XML
		XML::XMLDocument actor;
		if( actor.LoadFile( a_ccFile ) == 0 )
		{
			// First we should ge the modification time for our real time reloading
			HANDLE file;
			file = CreateFile( a_ccFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
			if( !GetFileTime( file, NULL, NULL, &m_FTLastModdified ) )
			{
				printf( "Cant access time.\n" );
			}			
			CloseHandle( file );

			// So far, so good. Set up the pointers now
			// so we can get that out of the way.
			XML::XMLNode* pActorNode;
			XML::XMLElement* pLimbs;
			XML::XMLElement* pLimbsElement;

			int iID;
			int iRowNum;
			Vec2 pSize;
			Vec2 pPos;
			Vec2 pOrigin;
			const char* ccImageFile;

			if( ( pActorNode = actor.FirstChildElement( "actor" ) ) != NULL )
			{
				if( ( pLimbs = pActorNode->FirstChildElement( "limbs" ) ) != NULL )
				{
					int iNumLimbs = pLimbs->IntAttribute( "count" );
					pLimbsElement = pLimbs->FirstChildElement( "limb" );

					for( int i = 0; i < iNumLimbs; ++i )
					{
						iID = pLimbsElement->IntAttribute( "id" );
						pPos[0] = pLimbsElement->FloatAttribute( "X" );
						pPos[1] = pLimbsElement->FloatAttribute( "Y" );

						pSize[0] = pLimbsElement->FloatAttribute( "W" );
						pSize[1] = pLimbsElement->FloatAttribute( "H" );

						pOrigin[0] = pLimbsElement->FloatAttribute( "originX" );
						pOrigin[1] = pLimbsElement->FloatAttribute( "originY" );

						iRowNum = pLimbsElement->IntAttribute( "imagerow" );
						//ccImageFile = pLimbsElement->Attribute( "image" );

						m_pParts.push_back( ActorLimb( iID, pSize, pPos, iRowNum, true ) );

						pLimbsElement = pLimbsElement->NextSiblingElement( "limb" );
					}
				}
				else
				{
					printf( "Error: Can't find node 'limbs'\n" );
				}
			}
			else
			{
				printf( "Error: Can't find node 'actor'\n" );
			}
		}
		else
		{
			printf( "Error: Can't open actor file(%s)\n", a_ccFile );
		}
	}	
	else
	{
		printf( "Error: Can't open actor file(%s)\n", a_ccFile );
	}
}

void Actor::ReloadActor()
{
	FILETIME FT_TimeModified;
	HANDLE file;
	file = CreateFile( m_ccActorFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	if( !GetFileTime( file, NULL, NULL, &FT_TimeModified ) )
	{
		printf( "Cant access time.\n" );
	}

	if( CompareFileTime( &FT_TimeModified, &m_FTLastModdified ) != 0 )
	{
		m_pParts.clear();
		LoadActor( m_ccActorFile );
		m_FTLastModdified = FT_TimeModified;
	}
	CloseHandle( file );
}

void Actor::FaceDirection( int a_iDirection )
{
	std::vector<ActorLimb>::reverse_iterator pIter = m_pParts.rbegin();

	for( ; pIter != m_pParts.rend(); ++pIter )
	{
		ActorLimb* pActorLimb = &(*pIter);	
		pActorLimb->FaceDirection( a_iDirection );
	}	

}

Actor::~Actor()
{

}

void Actor::Draw( GLuint a_uiShader, GLuint uiVBO, GLuint uiVAO, GLuint* a_uiTextures )
{
	std::vector<ActorLimb>::reverse_iterator pIter = m_pParts.rbegin();

	for( ; pIter != m_pParts.rend(); ++pIter )
	{
		glUseProgram( a_uiShader );	
		glBindVertexArray( uiVAO );

		ActorLimb pActorLimb = (*pIter);	
		pActorLimb.Draw( m_pPos, a_uiShader, a_uiTextures );

		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
		glUseProgram( 0 );
	}	
}