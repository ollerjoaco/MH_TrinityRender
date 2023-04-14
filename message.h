extern pfnUserMsgHook pmSetFOV;
//extern pfnUserMsgHook pmFog;
extern pfnUserMsgHook pmSetFog;

int HookUserMsg(char *szMsgName, pfnUserMsgHook pfn);