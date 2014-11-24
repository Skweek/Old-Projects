////////////////////////////////////////////////////////////
// File: Tile.h
// Author: Nick Smith
// Date Created: 16th April 2013
// Brief: Tile struct
////////////////////////////////////////////////////////////

#ifndef _TILE_H_
#define _TILE_H_

#include "Vec2.h"

struct Tile
{
	int m_iTileID;
	int m_iTileType;
	Vec2 m_pTilePos;

	void	operator=		( const Tile& a_Tile )	{	m_iTileID = a_Tile.m_iTileID;	m_iTileType = a_Tile.m_iTileType;	m_pTilePos = a_Tile.m_pTilePos;	 }
	
};


#endif