#include "extension.h"

CTauntExtension g_TauntExtension;
SMEXT_LINK(&g_TauntExtension);

CDetour *g_pDetourPlayTaunt;
IGameConfig *g_pGameConf;

IForward *g_pForwardPlayTauntSceneFromItem = NULL;

class CEconItemView;

DETOUR_DECL_MEMBER1(CTFPlayer_PlayTauntSceneFromItem, bool, const CEconItemView *, pTauntItem)
{
	cell_t iPlayer = gamehelpers->EntityToBCompatRef((CBaseEntity *)this);
	cell_t iTauntIndex = *(unsigned short *)((uint8_t *)pTauntItem + 4);
	
	cell_t result = 0;
	
	g_pForwardPlayTauntSceneFromItem->PushCell(iPlayer);
	g_pForwardPlayTauntSceneFromItem->PushCell(iTauntIndex);
	g_pForwardPlayTauntSceneFromItem->PushCellByRef(&result);

	cell_t retValue = Pl_Continue;
	g_pForwardPlayTauntSceneFromItem->Execute(&retValue);
	
	bool bOriginalResult = false;
	if (retValue != Pl_Stop)
		bOriginalResult = DETOUR_MEMBER_CALL(CTFPlayer_PlayTauntSceneFromItem)(pTauntItem);
	
	if(retValue > Pl_Continue)
		return result == 1;
	return bOriginalResult;
}

bool CTauntExtension::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
	if (!gameconfs->LoadGameConfigFile("taunt_controller", &g_pGameConf, error, maxlength)) return false;
	
	CDetourManager::Init(g_pSM->GetScriptingEngine(), g_pGameConf);
	
	g_pDetourPlayTaunt = DETOUR_CREATE_MEMBER(CTFPlayer_PlayTauntSceneFromItem, "CTFPlayer::PlayTauntSceneFromItem");
	if(g_pDetourPlayTaunt != NULL)
	{
		g_pDetourPlayTaunt->EnableDetour();
		g_pSM->LogMessage(myself, "CTFPlayer::PlayTauntSceneFromItem detour enabled.");
	}
	
	g_pForwardPlayTauntSceneFromItem = forwards->CreateForward("CTFPlayer_PlayTauntSceneFromItem", ET_Hook, 3, NULL, Param_Cell, Param_Cell, Param_CellByRef);
	
	return true;
}

void CTauntExtension::SDK_OnUnload()
{
	if (g_pDetourPlayTaunt != NULL) g_pDetourPlayTaunt->Destroy();
	forwards->ReleaseForward(g_pForwardPlayTauntSceneFromItem);
}