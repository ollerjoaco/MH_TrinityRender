#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "metahook.h"
#include "util_vector.h"

#include "hud.h"
#include "cl_util.h"
#include "message.h"
#include "pm_shared.h"
#include "player.h"


//RENDERERS START
#include "bsprenderer.h"
#include "propmanager.h"
#include "textureloader.h"
#include "particle_engine.h"
#include "watershader.h"
#include "mirrormanager.h"
#include "r_efx.h"

#include "studio.h"
#include "StudioModelRenderer.h"
#include "GameStudioModelRenderer.h"

extern CGameStudioModelRenderer g_StudioRenderer;
extern engine_studio_api_t IEngineStudio;
//RENDERERS END

//RENDERERS START
extern CGameStudioModelRenderer g_StudioRenderer;
extern engine_studio_api_t IEngineStudio;

cvar_s *cl_righthand = NULL;
cvar_t *cl_lw = NULL;

/*CBSPRenderer gBSPRenderer;
CParticleEngine gParticleEngine;
CWaterShader gWaterShader;
CTextureLoader gTextureLoader;
CPropManager gPropManager;
CMirrorManager gMirrorManager;*/
//RENDERERS END

CHud gHUD;

int __MsgFunc_SetFOV(const char *pszName, int iSize, void *pbuf)
{
	return gHUD.MsgFunc_SetFOV(pszName, iSize, pbuf);
}

int __MsgFunc_Fog(const char *pszName, int iSize, void *pbuf)
{
	return gHUD.MsgFunc_Fog(pszName, iSize, pbuf);
}


// This is called every time the DLL is loaded
void CHud::Init(void)
{
	HOOK_MESSAGE(SetFOV);

	cl_righthand = gEngfuncs.pfnGetCvarPointer("cl_righthand");
	//RENDERERS START
	/*
	HOOK_MESSAGE( SetFog );
	HOOK_MESSAGE( LightStyle );
	HOOK_MESSAGE( CreateDecal );
	HOOK_MESSAGE( StudioDecal );
	HOOK_MESSAGE( SkyMark_S );
	HOOK_MESSAGE( SkyMark_W );
	HOOK_MESSAGE( DynLight );
	HOOK_MESSAGE( FreeEnt );
	HOOK_MESSAGE( Particle );
	*/

	//R_Init2();

	//RENDERERS END
}



void CHud::VidInit(void)
{
	m_scrinfo.iSize = sizeof(m_scrinfo);
	gEngfuncs.pfnGetScreenInfo(&m_scrinfo);

	m_pFogSettings.end = 0.0;
	m_pFogSettings.start = 0.0;
	m_pFogSettings.active = false;
	m_pSkyFogSettings.end = 0.0;
	m_pSkyFogSettings.start = 0.0;
	m_pSkyFogSettings.active = false;

	//R_VidInit();

}

CHud:: ~CHud()
{
	//R_Shutdown();
}

//RENDERERS START
extern void HUD_PrintSpeeds(void);
//RENDERERS END


int CHud::Redraw(float flTime, int intermission)
{
	m_fOldTime = m_flTime;	// save time of previous redraw
	m_flTime = flTime;
	m_flTimeDelta = (double)m_flTime - m_fOldTime;

	/*m_pFogSettings.active = true;
	m_pFogSettings.color.x = m_pFogSettings.color.y = m_pFogSettings.color.z = 0;
	m_pFogSettings.start = 200;
	m_pFogSettings.end = 1000;
	m_pFogSettings.affectsky = false;*/

	/*m_pSkyFogSettings.active = false;
	m_pSkyFogSettings.color.x = m_pSkyFogSettings.color.y = m_pSkyFogSettings.color.z = 0;
	m_pSkyFogSettings.start = 200;
	m_pSkyFogSettings.end = 1000;
	m_pSkyFogSettings.affectsky = true;*/

	//RENDERERS START
	HUD_PrintSpeeds();
	//RENDERERS END

	return 1;
}


int CHud::MsgFunc_SetFOV(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);

	int newfov = READ_BYTE();
	int def_fov = CVAR_GET_FLOAT("default_fov");

	if (newfov == 0)
		m_iFOV = def_fov;
	else
		m_iFOV = newfov;

	return pmSetFOV(pszName, iSize, pbuf);
}

int CHud::MsgFunc_Fog(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);

	gHUD.m_pFogSettings.active = true;
	gHUD.m_pFogSettings.color.x = (float)READ_BYTE() / 255;
	gHUD.m_pFogSettings.color.y = (float)READ_BYTE() / 255;
	gHUD.m_pFogSettings.color.z = (float)READ_BYTE() / 255;
	gHUD.m_pFogSettings.start = 300;
	gHUD.m_pFogSettings.end = 1500;
	//gHUD.m_pFogSettings.affectsky = (READ_SHORT() == 1) ? false : true;

	return pmFog(pszName, iSize, pbuf);
}