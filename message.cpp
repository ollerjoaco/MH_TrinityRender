#include "metahook.h"
#include "util_vector.h"
#include "hud.h"
#include "message.h"

pfnUserMsgHook pmSetFOV;
pfnUserMsgHook pmSetFog;

int HookUserMsg(char *szMsgName, pfnUserMsgHook pfn)
{
	if (!strcmp(szMsgName, "SetFOV"))
	{
		pmSetFOV = pfn;
		return gEngfuncs.pfnHookUserMsg(szMsgName, __MsgFunc_SetFOV);
	}
	else if(!strcmp(szMsgName, "SetFog"))
	{
		pmSetFog = pfn;
		return gEngfuncs.pfnHookUserMsg(szMsgName, __MsgFunc_SetFog);
	}
	return gEngfuncs.pfnHookUserMsg(szMsgName, pfn);
}