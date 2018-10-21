#include <sourcemod>
#include <taunt_controller>

#define CONFIG_TAUNT_BLACKLIST		"configs/taunts_blacklist.cfg"

KeyValues g_kvTaunts;

public void OnPluginStart()
{
	char sFile[256];
	BuildPath(Path_SM, sFile, sizeof(sFile), CONFIG_TAUNT_BLACKLIST);
	
	g_kvTaunts = new KeyValues("taunt_blacklist");
	if (!g_kvTaunts.ImportFromFile(sFile)) 
	{
		SetFailState("Could not load file %s.", sFile);
		delete g_kvTaunts;
	}
	g_kvTaunts.Rewind();
}

public Action CTFPlayer_PlayTauntSceneFromItem(int iClient, int iTauntIndex, bool &bTauntSuccess)
{
	if (g_kvTaunts == null) return Plugin_Continue;
	
	char sTauntIndex[32];
	IntToString(iTauntIndex, sTauntIndex, sizeof(sTauntIndex));
	bool bAllowed = view_as<bool>(g_kvTaunts.GetNum(sTauntIndex, true));
	if (!bAllowed) // Is taunt blacklisted?
	{
		bTauntSuccess = false;
		return Plugin_Stop;
	}
	return Plugin_Continue;
}