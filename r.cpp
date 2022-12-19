#include <metahook.h>
#include "plugins.h"
#include "com_model.h"
#include "util_vector.h"
#include "exportfuncs.h"
#include "r.h"
#include "r_efx.h"
#include "particle_engine.h"
#include "bsprenderer.h"
#include "decal.h"
#include "ref_int.h"

#include "studio.h"
#include "StudioModelRenderer.h"
#include "GameStudioModelRenderer.h"

extern CGameStudioModelRenderer g_StudioRenderer;

ref_funcs_t gRefFuncs;

#define R_DECALNODE_SIG "\x83\xEC\x58\x53\x8B\x5C\x24\x60\x55\x56\x85\xDB\x57\x0F\x84\x6B"
#define R_DECALCREATE_SIG "\x53\x8B\x5C\x24\x14\x56\x8B\x74\x24\x0C\x57\x8B\x7C\x24\x20\x57"
#define R_DECALCREATE_SIG_NEW "\x55\x8B\xEC\x8B\x45\x14\x53\x8B\x5D\x18\x56\x57\x8B\x7D\x08\x53"
#define DRAW_DECALTEXTURE_SIG "\x8B\x44\x24\x04\x56\x85\xC0\x57\x7D\x7B\x83\xC9\xFF\x2B\xC8\x8D"
#define DRAW_DECALTEXTURE_SIG_NEW "\x55\x8B\xEC\x8B\x4D\x08\x56\x85\xC9\x57\x7D\x79\x83\xC8\xFF\x2B"

void R_Init()
{
	/*if (g_dwEngineBuildnum >= 5971)
	{
		gRefFuncs.R_DecalCreate = (void(*)(msurface_t *, int, float, float, float))g_pMetaHookAPI->SearchPattern((void *)g_dwEngineBase, g_dwEngineSize, R_DECALCREATE_SIG_NEW, sizeof(R_DECALCREATE_SIG_NEW) - 1);
		gRefFuncs.Draw_DecalTexture = (texture_t*(*)(int))g_pMetaHookAPI->SearchPattern((void *)g_dwEngineBase, g_dwEngineSize, DRAW_DECALTEXTURE_SIG_NEW, sizeof(DRAW_DECALTEXTURE_SIG_NEW) - 1);
	}
	else
	{*/
		gRefFuncs.R_DecalNode = (void(*)(mnode_t*, float))g_pMetaHookAPI->SearchPattern((void *)g_dwEngineBase, g_dwEngineSize, R_DECALNODE_SIG, sizeof(R_DECALNODE_SIG) - 1);
		gRefFuncs.R_DecalCreate = (void(*)(msurface_t *, int, float, float, float))g_pMetaHookAPI->SearchPattern((void *)g_dwEngineBase, g_dwEngineSize, R_DECALCREATE_SIG, sizeof(R_DECALCREATE_SIG) - 1);
		gRefFuncs.Draw_DecalTexture = (texture_t*(*)(int))g_pMetaHookAPI->SearchPattern((void *)g_dwEngineBase, g_dwEngineSize, DRAW_DECALTEXTURE_SIG, sizeof(DRAW_DECALTEXTURE_SIG) - 1);
	//}

	//g_pMetaHookAPI->InlineHook(gRefFuncs.R_DecalNode, R_DecalNode, (void *&)gRefFuncs.R_DecalNode);
	g_pMetaHookAPI->InlineHook(gRefFuncs.R_DecalCreate, R_DecalCreate, (void *&)gRefFuncs.R_DecalCreate);
}

void R_BloodSprite(float* org, int colorindex, int modelIndex, int modelIndex2, float size)
{
	gParticleEngine.CreateCluster("blood_effects_cluster.txt", org, Vector(0, 0, 0), 0);
	return;
}

void R_BloodStream(float * org, float * dir, int pcolor, int speed)
{
	return;
}

void R_DecalRemoveAll(int textureIndex)
{
	gBSPRenderer.DeleteDecals();
	return;
}

#if 0
void R_Explosion(float *pos, int modelIndex, float scale, float framerate, int flags)
{
	model_s *model = IEngineStudio.GetModelByIndex(modelIndex);

	if (!strcmp(model->name, "sprites/fexplo.spr"))
	{
		gParticleEngine.CreateCluster("explosion.txt", pos, Vector(0, 0, 0), 0);
		gEngfuncs.pEfxAPI->R_Explosion(pos, 0, 0, 0, TE_EXPLFLAG_NONE);

		cl_dlight_t *dl;

		dl = gBSPRenderer.CL_AllocDLight(0);
		dl->origin = pos;
		dl->radius = 200;
		dl->color.x = 250;
		dl->color.y = 250;
		dl->color.z = 150;
		dl->die = gEngfuncs.GetClientTime() + 0.01;
		dl->decay = 80;

		dl = gBSPRenderer.CL_AllocDLight(0);
		dl->origin = pos;
		dl->radius = 150;
		dl->color.x = 255;
		dl->color.y = 190;
		dl->color.z = 40;
		dl->die = gEngfuncs.GetClientTime() + 1.0;
		dl->decay = 200;

		return;
	}

	if (!strcmp(model->name, "sprites/eexplo.spr"))
		return;
	
	return gEngfuncs.pEfxAPI->R_Explosion(pos, modelIndex, scale, framerate, flags);
}

int decalTextureIndex;
char decal[32];

int Draw_DecalIndex(int id)
{
	decalTextureIndex = id;

	return gEfxAPI.Draw_DecalIndex(id);
}
#endif

float pos[3];

void R_DecalShoot(int textureIndex, int entity, int modelIndex, float *position, int flags)
{
	memcpy(pos, position, sizeof(pos));
	
	return gEfxAPI.R_DecalShoot(textureIndex, entity, modelIndex, position, flags);
}

void R_DecalNode(mnode_t *node, float flScale)
{
	gRefFuncs.R_DecalNode(node, flScale);
}


void R_DecalCreate(msurface_t *psurface, int textureIndex, float scale, float x, float y)
{
	texture_s *ptexture = gRefFuncs.Draw_DecalTexture(textureIndex);

	if (strstr(ptexture->name, "scorch"))
		gBSPRenderer.CreateDecal(pos, psurface->plane->normal, "scorch", FALSE);
	
	if (strstr(ptexture->name, "blood"))
		gBSPRenderer.CreateDecal(pos, psurface->plane->normal, "redblood", FALSE);	
	
	return;
}