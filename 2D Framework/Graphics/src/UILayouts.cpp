#include "UILayouts.h"
#include "Window.h"

UILayouts* UILayouts::m_pInstance = nullptr;

UILayouts* UILayouts::Create()
{
	if( !m_pInstance )
	{
		m_pInstance = new UILayouts();
	}

	return m_pInstance;
}

UILayouts* UILayouts::Get()
{
	return m_pInstance;
}

void UILayouts::Delete()
{
	if( m_pInstance )
	{
		delete m_pInstance;
	}
}

UILayouts::UILayouts()
{
	Layouts.clear();
	m_iNumLayouts = 0;
	Init();
}

UILayouts::~UILayouts()
{
	glDeleteBuffers( 1, &m_uiLEBO );
	glDeleteBuffers( 1, &m_uiLVBO );
	glDeleteFramebuffers( 1, &m_uiLFBO );
	glDeleteVertexArrays( 1, &m_uiLVAO );
}

int UILayouts::LoadLayout( const char* a_ccLayoutFile )
{
	// Try to open file first
	FILE* fh = fopen( a_ccLayoutFile, "r" );
	if( fh == NULL ) return false;

	// Okay, file works, now try to get it as XML
	XML::XMLDocument layout;
	if( layout.LoadFile( a_ccLayoutFile ) == 0 )
	{
		// So far, so good. Set up the pointers now
		// so we can get that out of the way.
		XML::XMLNode* pLayoutNode;
		XML::XMLElement* pInfo;
		XML::XMLElement* pElements;
		XML::XMLElement* pButtons;
		XML::XMLElement* pButtonsElement;
		XML::XMLElement* pLabels;
		XML::XMLElement* pLabelsElement;
		XML::XMLElement* pMeters;
		XML::XMLElement* pMetersElement;

		// We need to actually create a layout to store the info in
		Layout* tempLayout = new Layout();
		tempLayout->LayoutElements.clear();
		// we also need variables to store the element info in
		Vec2 pos;
		Vec2 size;
		int id;
		const char* imagefile1;
		const char* imagefile2;
		const char* text;
		Vec4 textcolour;


		// First we need the layout node
		if( ( pLayoutNode = layout.FirstChildElement( "layout" ) ) == NULL )
		{
			printf( "Error: Can't find node 'layout'\n" );
			return NULL;
		}

		// Get the layout size and position
		if( ( pInfo = pLayoutNode->FirstChildElement( "info" ) ) == NULL )
		{
			printf( "Error: Can't find node 'info'\n" );
			return NULL;
		}

		tempLayout->LayoutPos[0] = pInfo->FloatAttribute( "x" );
		tempLayout->LayoutPos[1] = pInfo->FloatAttribute( "y" );
		tempLayout->LayoutSize[0] = pInfo->FloatAttribute( "w" );
		tempLayout->LayoutSize[1] = pInfo->FloatAttribute( "h" );
		tempLayout->LayoutBG = LoadTexture( pInfo->Attribute( "BGFile" ) );		
		tempLayout->ID = m_iNumLayouts;

		// Now we need the elements node
		if( ( pElements = pLayoutNode->FirstChildElement( "elements" ) ) == NULL )
		{
			printf( "Error: Can't find node 'elements'\n" );
			return NULL;
		}

		// Get all the buttons
		if( ( pButtons = pElements->FirstChildElement( "buttons" ) ) == NULL )
		{
			printf( "Error: Can't find node 'buttons'\n" );
			return NULL;
		}

		int numbuttons = pButtons->IntAttribute( "count" );
		pButtonsElement = pButtons->FirstChildElement( "button" );

		// Loop through the buttons and load their stuff
		for( int i = 0; i < numbuttons; ++i )
		{
			id = pButtonsElement->IntAttribute( "id" );
			pos[0] = pButtonsElement->FloatAttribute( "X" );
			pos[1] = pButtonsElement->FloatAttribute( "Y" );
			size[0] = pButtonsElement->FloatAttribute( "W" );
			size[1] = pButtonsElement->FloatAttribute( "H" );
			imagefile1 = pButtonsElement->Attribute( "buttonUp" );
			imagefile2 = pButtonsElement->Attribute( "buttonDown" );

			UIButton* tempButton = new UIButton( pos + tempLayout->LayoutPos, size, id, imagefile1, imagefile2 );
			tempLayout->LayoutElements.push_back( tempButton );

			pButtonsElement = pButtonsElement->NextSiblingElement( "button" );

			// Debug info - Map Objects
			if( bDebugInfo )
			{
				printf( "Layout #%i, button #%i. \n", tempLayout->ID, id );
			}

		}

		// Get all the labels
		if( ( pLabels = pElements->FirstChildElement( "labels" ) ) == NULL )
		{
			printf( "Error: Can't find node 'meters'\n" );
			return NULL;
		}

		int numlabels = pLabels->IntAttribute( "count" );
		pLabelsElement = pLabels->FirstChildElement( "label" );

		// Loop through the labels and load their stuff
		for( int i = 0; i < numlabels; ++i )
		{
			id = pLabelsElement->IntAttribute( "id" );
			pos[0] = pLabelsElement->FloatAttribute( "X" );
			pos[1] = pLabelsElement->FloatAttribute( "Y" );
			text = pLabelsElement->Attribute( "labelText" );
			textcolour[0] = pLabelsElement->FloatAttribute( "R" );
			textcolour[1] = pLabelsElement->FloatAttribute( "G" );
			textcolour[2] = pLabelsElement->FloatAttribute( "B" );
			textcolour[3] = pLabelsElement->FloatAttribute( "A" );


			UILabel* tempLabel = new UILabel( pos + tempLayout->LayoutPos, id, text, textcolour );
			tempLayout->LayoutElements.push_back( tempLabel );

			pLabelsElement = pLabelsElement->NextSiblingElement( "label" );

			// Debug info - Map Objects
			if( bDebugInfo )
			{
				printf( "Layout #%i, label #%i. \n", tempLayout->ID, id );
			}
		}

		// Get all the meters
		if( ( pMeters = pElements->FirstChildElement( "meters" ) ) == NULL )
		{
			printf( "Error: Can't find node 'meters'\n" );
			return NULL;
		}

		int nummeters = pMeters->IntAttribute( "count" );
		pMetersElement = pMeters->FirstChildElement( "meter" );

		// Loop through the buttons and load their stuff
		for( int i = 0; i < nummeters; ++i )
		{
			id = pMetersElement->IntAttribute( "id" );
			pos[0] = pMetersElement->FloatAttribute( "X" );
			pos[1] = pMetersElement->FloatAttribute( "Y" );
			size[0] = pMetersElement->FloatAttribute( "W" );
			size[1] = pMetersElement->FloatAttribute( "H" );
			Vec2 padding = Vec2( pMetersElement->FloatAttribute( "xPad" ), 
									pMetersElement->FloatAttribute( "yPad" ) );
			imagefile1 =  pMetersElement->Attribute( "BGImage" );
			imagefile2 =  pMetersElement->Attribute( "meterImage" );
			
			UIMeter* tempMeter = new UIMeter( pos + tempLayout->LayoutPos, size, id,
												imagefile2, imagefile1, padding );

			tempLayout->LayoutElements.push_back( tempMeter );

			pMetersElement = pMetersElement->NextSiblingElement( "meter" );

			// Debug info - Map Objects
			if( bDebugInfo )
			{
				printf( "Layout #%i, meter #%i. \n", tempLayout->ID, id );
			}
		}

		++m_iNumLayouts;
		m_pCurLayout = tempLayout;
		Layouts.push_back( tempLayout );	
		
		return m_iNumLayouts - 1;
	}

	// We stuffed up, how did we even get here?
	return NULL;
}

void UILayouts::Update()
{
	if( m_pCurLayout != 0 )
	{
		// Loop through all elements
		Layout* layout = m_pCurLayout;
		std::vector<UIElement*>::iterator pIter = layout->LayoutElements.begin();
		for( ; pIter != layout->LayoutElements.end(); ++pIter )
		{		
			// Get the element and call its update function
			UIElement* pElement = (*pIter);	
			pElement->Update();
		}
	}
}

void UILayouts::Render()
{	
	// Only do stuff if we actually have an active layout
	if( m_pCurLayout != 0 && m_bDraw )
	{
		// Draw the background first		
		glBindVertexArray( m_uiLVAO );
		glUseProgram( m_uiLayoutShader );
		// Set the projection and UV coords up
		GLuint ProjectionID = glGetUniformLocation( m_uiLayoutShader, "Projection" );
		glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );

		Matrix4 mat = Matrix4( m_pCurLayout->LayoutSize[0],	0.f, 0.f, 0.f, 
								0.f, m_pCurLayout->LayoutSize[1], 0.f, 0.f, 
								0.f, 0.f, 1.f, 0.f, 
								m_pCurLayout->LayoutPos[0], m_pCurLayout->LayoutPos[1], 0.f, 1.f );

		GLuint ModelID = glGetUniformLocation( m_uiLayoutShader, "Model" );
		glUniformMatrix4fv( ModelID, 1, false, mat );	

		glBindTexture( GL_TEXTURE_2D, m_pCurLayout->LayoutBG );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

		// Loop through all elements
		std::vector<UIElement*>::iterator pIter = m_pCurLayout->LayoutElements.begin();
		for( ; pIter < m_pCurLayout->LayoutElements.end(); ++pIter )
		{		
			// Bind VAO and shader
			glBindVertexArray( m_uiLVAO );
			glUseProgram( m_uiLayoutShader );
		
			// Get the element and call its draw functions
			UIElement* pElement = (*pIter);	
			pElement->Draw( m_uiLayoutShader );

			// Unbind shader and vao
		}

	}
}

void UILayouts::Init()
{
	m_bDraw = true; 

	// Gen Buffers
	glGenBuffers( 1, &m_uiLVBO );
	glGenBuffers( 1, &m_uiLEBO );
	glGenVertexArrays( 1, &m_uiLVAO );

	//// Set up the FBO and the texture we are rendering to
	//glGenFramebuffers( 1, &m_uiLFBO );
	//glGenTextures( 1, &m_uiUIImage );
	//glBindTexture( GL_TEXTURE_2D, m_uiUIImage );
	//Vec2 size = Windows::Get()->GetWindow()->pWindowSize;
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size[0], size[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	//glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uiUIImage, 0 );

	//GLenum error = glCheckFramebufferStatus( GL_FRAMEBUFFER );
	//if( error != GL_FRAMEBUFFER_COMPLETE )
	//{
	//	printf( "%i", error );
	//}

	m_uiLayoutShader = LoadShaders( "shaders/sprite-vertex-shader.glsl", "shaders/sprite-fragment-shader.glsl" );	

	glBindVertexArray( m_uiLVAO );

	Vertices[0].Pos = Vec4( 0.f, 0.f, 0.f, 1.f );
	Vertices[0].UV = Vec2( 0.f, 1.f );

	Vertices[1].Pos = Vec4( 1.f, 0.f, 0.f, 1.f );
	Vertices[1].UV = Vec2( 1.f, 1.f );

	Vertices[2].Pos = Vec4( 0.f, 1.f, 0.f, 1.f );
	Vertices[2].UV = Vec2( 0.f, 0.f );

	Vertices[3].Pos = Vec4( 1.f, 1.f, 0.f, 1.f );
	Vertices[3].UV = Vec2( 1.f, 0.f );

	glBindBuffer( GL_ARRAY_BUFFER, m_uiLVBO );
	glBufferData( GL_ARRAY_BUFFER, 4 * sizeof( Vertex ), Vertices, GL_STATIC_DRAW );

	GLuint elements[] = {
		0, 1, 2,
		1, 3, 2
	};

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_uiLEBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

	glUseProgram( m_uiLayoutShader );

	glBindFragDataLocation( m_uiLayoutShader, 0, "outColor" );
	
	
	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation( m_uiLayoutShader, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof( Vertex ), 0 );

	GLint texAttrib = glGetAttribLocation( m_uiLayoutShader, "texcoord" );
	glEnableVertexAttribArray( texAttrib );
	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)( sizeof( Vec4 ) ) );

	glBindVertexArray( 0 );

	GLuint ProjectionID = glGetUniformLocation( m_uiLayoutShader, "Projection" );
	GLuint ViewID = glGetUniformLocation( m_uiLayoutShader, "View" );

	glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );
	glUniformMatrix4fv( ViewID, 1, false, (float*)Windows::Get()->GetWindow()->pView );

	GLuint minUV = glGetUniformLocation( m_uiLayoutShader, "minUV" );
	glUniform2fv( minUV, 1, Vec2( 0.f, 0.f ) );

	GLuint diffUV = glGetUniformLocation( m_uiLayoutShader, "diffUV" );
	glUniform2fv( diffUV, 1, Vec2( 1.f, 1.f ) );

	m_pCurLayout = 0;
}

void UILayouts::SetLayout( int a_iLayoutID )
{
	for( int i = 0; i < (int)Layouts.size(); ++i )
	{
		Layout* layout = Layouts[i];
		if( layout->ID == a_iLayoutID )
		{
			m_pCurLayout = layout;
		}
	}
}

void UILayouts::ToggleDrawLayout( bool a_bToggle )
{
	m_bDraw = a_bToggle;
}

// Element specific functions
// buttons
void UILayouts::SetButtonEvent( int a_iElementID, std::function<void()> function )
{
	UIButton* button;
	for( int i = 0; i < (int)m_pCurLayout->LayoutElements.size(); ++i )
	{
		if( button = dynamic_cast<UIButton*>( m_pCurLayout->LayoutElements[i] ) )
		{
			if( button->m_iID == a_iElementID )
			{
				button->SetClickFunction( function );
			}
		}
	}
}

// labels
void UILayouts::SetLabelVariable( int a_iElementID, int a_iType, void* p )
{
	UILabel* label;
	for( int i = 0; i < (int)m_pCurLayout->LayoutElements.size(); ++i )
	{
		if( label = dynamic_cast<UILabel*>( m_pCurLayout->LayoutElements[i] ) )
		{
			if( label->m_iID == a_iElementID )
			{
				label->SetVariablePointer( a_iType, p );
			}
		}
	}
}

// meters
void UILayouts::SetMeterFunction( int a_iElementID, void ( *p )() )
{
	UIMeter* meter;
	for( int i = 0; i < (int)m_pCurLayout->LayoutElements.size(); ++i )
	{
		if( meter = dynamic_cast<UIMeter*>( m_pCurLayout->LayoutElements[i] ) )
		{
			if( meter->m_iID == a_iElementID )
			{
				meter->SetMeterFunction( p );	
			}
		}
	}
}

void UILayouts::SetMeterVariable( int a_iElementID, void* p )
{
	UIMeter* meter;
	for( int i = 0; i < (int)m_pCurLayout->LayoutElements.size(); ++i )
	{
		if( meter = dynamic_cast<UIMeter*>( m_pCurLayout->LayoutElements[a_iElementID] ) )
		{
			if( meter->m_iID == a_iElementID )
			{
				meter->SetMeterVariable( p );		
			}
		}
	}
}

void UILayouts::SetMeterMinMax( int a_iElementID, Vec2 a_pValues )
{
	UIMeter* meter;
	for( int i = 0; i < (int)m_pCurLayout->LayoutElements.size(); ++i )
	{
		if( meter = dynamic_cast<UIMeter*>( m_pCurLayout->LayoutElements[a_iElementID] ) )
		{
			if( meter->m_iID == a_iElementID )
			{
				meter->SetMin( a_pValues[0] );
				meter->SetMax( a_pValues[1] );		
			}
		}
	}	
}