//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#if !defined( GAMESTUDIOMODELRENDERER_H )
#define GAMESTUDIOMODELRENDERER_H
#if defined( _WIN32 )
#pragma once
#endif

/*
====================
CGameStudioModelRenderer

====================
*/
class CGameStudioModelRenderer : public CStudioModelRenderer
{
public:
	CGameStudioModelRenderer( void );
};

int HUD_GetStudioModelInterface(int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio);
#endif // GAMESTUDIOMODELRENDERER_H