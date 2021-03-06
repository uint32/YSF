#include "main.h"

std::vector<AMX *> CCallbackManager::m_vecAMX;

void CCallbackManager::RegisterAMX(AMX *pAMX)
{
	// Add gamemode to the first position in vector
	if (pNetGame && pNetGame->pGameModePool && &pNetGame->pGameModePool->m_amx == pAMX)
	{
		std::vector<AMX*>::iterator it = m_vecAMX.begin();
		m_vecAMX.insert(it, pAMX);
	}
	else
	{
		m_vecAMX.push_back(pAMX);
	}
}

void CCallbackManager::UnregisterAMX(AMX *pAMX)
{
	// Remove the amx from the pointers list
	std::vector<AMX *>::iterator p = std::find(m_vecAMX.begin(), m_vecAMX.end(), pAMX);
	if(p != m_vecAMX.end())
	{
		p = m_vecAMX.erase(p);
	}
}

void CCallbackManager::OnPlayerEnterGangZone(WORD playerid, WORD zoneid)
{
	int idx = -1;
	cell ret = 1;
	for(std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if(!amx_FindPublic(*iter, "OnPlayerEnterGangZone", &idx))
		{
			amx_Push(*iter, zoneid);
			amx_Push(*iter, playerid);

			amx_Exec(*iter, &ret, idx);

			if (!ret) return;
		}
	}
}

void CCallbackManager::OnPlayerLeaveGangZone(WORD playerid, WORD zoneid)
{
	int idx = -1;
	cell ret = 1;
	for(std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if(!amx_FindPublic(*iter, "OnPlayerLeaveGangZone", &idx))
		{
			amx_Push(*iter, zoneid);
			amx_Push(*iter, playerid);

			amx_Exec(*iter, &ret, idx);

			if (!ret) return;
		}
	}
}

void CCallbackManager::OnPlayerEnterPlayerGangZone(WORD playerid, WORD zoneid)
{
	int idx = -1;
	cell ret = 1;
	for(std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if(!amx_FindPublic(*iter, "OnPlayerEnterPlayerGangZone", &idx))
		{
			amx_Push(*iter, zoneid);
			amx_Push(*iter, playerid);

			amx_Exec(*iter, &ret, idx);

			if (!ret) return;
		}
	}
}

void CCallbackManager::OnPlayerLeavePlayerGangZone(WORD playerid, WORD zoneid)
{
	int idx = -1;
	cell ret = 1;
	for(std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if(!amx_FindPublic(*iter, "OnPlayerLeavePlayerGangZone", &idx))
		{
			amx_Push(*iter, zoneid);
			amx_Push(*iter, playerid);

			amx_Exec(*iter, &ret, idx);

			if (!ret) return;
		}
	}
}

void CCallbackManager::OnPlayerPauseStateChange(WORD playerid, bool pausestate)
{
	int idx = -1;
	cell ret = 1;
	for(std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if(!amx_FindPublic(*iter, "OnPlayerPauseStateChange", &idx))
		{
			amx_Push(*iter, pausestate);
			amx_Push(*iter, playerid);

			amx_Exec(*iter, &ret, idx);

			if (!ret) return;
		}
	}
}

void CCallbackManager::OnPlayerDeath(WORD playerid, WORD killerid, BYTE reason)
{
	int idx = -1;
	cell ret = 1;
	for (std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if (!amx_FindPublic(*iter, "OnPlayerDeath", &idx))
		{
			amx_Push(*iter, reason);
			amx_Push(*iter, killerid);
			amx_Push(*iter, playerid);

			amx_Exec(*iter, &ret, idx);

			if (!ret) return;
		}
	}
}

void CCallbackManager::OnPlayerSpawn(WORD playerid)
{
	int idx = -1;
	cell ret = 1;
	for (std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if (!amx_FindPublic(*iter, "OnPlayerSpawn", &idx))
		{
			amx_Push(*iter, playerid);

			amx_Exec(*iter, &ret, idx);

			if (!ret) return;
		}
	}
}

void CCallbackManager::OnPlayerPickedUpPickup(WORD playerid, WORD pickupid)
{
	int idx = -1;
	cell ret = 1;
	for(std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if(!amx_FindPublic(*iter, "OnPlayerPickUpPickup", &idx))
		{
			amx_Push(*iter, static_cast<cell>(pickupid));
			amx_Push(*iter, static_cast<cell>(playerid));

			amx_Exec(*iter, &ret, idx);

			if (!ret) return;
		}
	}
}

void CCallbackManager::OnPlayerPickedUpPlayerPickup(WORD playerid, WORD pickupid)
{
	int idx = -1;
	cell ret = 1;
	for(std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if(!amx_FindPublic(*iter, "OnPlayerPickUpPlayerPickup", &idx))
		{
			amx_Push(*iter, pickupid);
			amx_Push(*iter, playerid);

			amx_Exec(*iter, &ret, idx);

			if (!ret) return;
		}
	}
}

bool CCallbackManager::OnServerMessage(char* message)
{
	if (!message) return 0;

	int idx = -1;
	cell ret = 1;
	for(std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if (!amx_FindPublic(*iter, "OnServerMessage", &idx))
		{
			cell amx_addr, *phys_addr;
			amx_PushString(*iter, &amx_addr, &phys_addr, message, 0, 0);

			amx_Exec(*iter, &ret, idx);
			amx_Release(*iter, amx_addr);

			if (!ret) return 0;
		}
	}
	return !!ret;
}

bool CCallbackManager::OnRemoteRCONPacket(unsigned int binaryAddress, int port, char *password, bool success, char* command)
{
	int idx = -1;
	cell ret = 1;
	for(std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if(!amx_FindPublic(*iter, "OnRemoteRCONPacket", &idx))
		{
			cell amx_addr, *phys_addr;
			
			in_addr in;
			in.s_addr = binaryAddress;

			amx_PushString(*iter, &amx_addr, &phys_addr, command, 0, 0);
			amx_Push(*iter, static_cast<cell>(success));
			amx_PushString(*iter, &amx_addr, &phys_addr, password, 0, 0);
			amx_Push(*iter, port);
			amx_PushString(*iter, &amx_addr, &phys_addr, inet_ntoa(in), 0, 0);
			amx_Exec(*iter, &ret, idx);
			amx_Release(*iter, amx_addr);

			if (!ret) return 0;
		}
	}
	return !!ret;
}

void CCallbackManager::OnPlayerStatsAndWeaponsUpdate(WORD playerid)
{
	int idx = -1;
	cell ret = 1;
	for (std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if (!amx_FindPublic(*iter, "OnPlayerStatsAndWeaponsUpdate", &idx))
		{
			amx_Push(*iter, playerid);

			amx_Exec(*iter, &ret, idx);
		}
	}
}

void CCallbackManager::OnVehicleSpawn(WORD vehicleid)
{
	int idx = -1;
	cell ret = 1;
	for (std::vector<AMX*>::const_iterator iter = m_vecAMX.begin(); iter != m_vecAMX.end(); ++iter)
	{
		if (!amx_FindPublic(*iter, "OnVehicleSpawn", &idx))
		{
			amx_Push(*iter, vehicleid);

			amx_Exec(*iter, &ret, idx);
		}
	}
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		bool ret = pServer->AddPlayer(playerid);
		// Initialize pickups
#ifdef NEW_PICKUP_SYSTEM
		if (ret)
			pNetGame->pPickupPool->InitializeForPlayer(playerid);
#endif
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	pServer->RemovePlayer(playerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamIn(int playerid, int forplayerid)
{
	pServer->OnPlayerStreamIn(playerid, forplayerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStreamOut(int playerid, int forplayerid)
{
	pServer->OnPlayerStreamOut(playerid, forplayerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid)
{
	if (IsPlayerConnectedEx(playerid))
	{
		pPlayerData[playerid]->bControllable = true;
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char * inputtext)
{
	if (IsPlayerConnectedEx(playerid))
	{
		pNetGame->pPlayerPool->pPlayer[playerid]->wDialogID = 0;
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
{
	if (IsPlayerConnectedEx(playerid) && response < EDIT_RESPONSE_UPDATE)
	{
		pNetGame->pPlayerPool->pPlayer[playerid]->bEditObject = false;
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditAttachedObject(int playerid, int response, int index, int modelid, int boneid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ)
{
	if (IsPlayerConnectedEx(playerid) && response < EDIT_RESPONSE_UPDATE)
	{
		pNetGame->pPlayerPool->pPlayer[playerid]->bEditAttachedObject = false;
	}
	return false;
}