////////////////////////////////////////////////////////////
// File: Shapes.h
// Author: Nick Smith
// Date Created: 21st July 2013
// Brief: For drawing shapes
////////////////////////////////////////////////////////////

#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "Utilities.h"

class DECLDIR Shapes
{
public:
	static Shapes* Create();
	static Shapes* Get();
	static void Delete();

	void DrawLine( Vec2 a_pStart, Vec2 a_pEnd, Vec4 a_pColour = Vec4() );

	void Render();

private:
	Shapes();
	~Shapes();

	void Init();

	static Shapes* m_pInstance;
	
	LineVertex LinesVertices[2];
	std::queue<LineShape*> LinesToDraw;

	GLuint m_uiLinesVAO;
	GLuint m_uiLinesVBO;
	GLuint m_uiLinesEBO;

	Vertex CubeVertices[36];

	GLuint m_uiCubeVAO;
	GLuint m_uiCubeVBO;
	GLuint m_uiCubeEBO;


	GLuint m_uiShaderProgram;

};

#endif // _SHAPES_H