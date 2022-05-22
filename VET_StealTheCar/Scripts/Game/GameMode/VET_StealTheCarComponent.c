class VET_StealTheCarComponentClass : SCR_BaseGameModeComponentClass
{
};

class VET_StealTheCarComponent : SCR_BaseGameModeComponent
{
	protected SCR_BaseGameMode m_gameMode;
	
	protected override void OnPostInit(IEntity owner)
	{
		// do not init the component in Workbench
		if (!GetGame().InPlayMode())
			return;
		
		m_gameMode =  GetGameMode();
		if (!m_gameMode)
		{
			Print("#StealTheCar: COULD NOT GET GAMEMODE", LogLevel.ERROR);
			return;
		}
		
		PrintFormat("#StealTheCar: INIT");
		
		GetGame().GetCallqueue().CallLater(InitTasks, 1000);
	}
	
	override void OnPlayerRegistered(int playerId)
	{
		super.OnPlayerRegistered(playerId);
		PrintFormat("#StealTheCar: Player registered - %1", playerId);
		
		PlayerController playerController = GetGame().GetPlayerManager().GetPlayerController(playerId);
		
		SCR_RespawnSystemComponent respawnComponent = m_gameMode.GetRespawnSystemComponent();
		if (!respawnComponent)
			Print("#StealTheCar: COULD NOT GET RESPAWN COMPONENT", LogLevel.ERROR);
		
		FactionManager factionManager = GetGame().GetFactionManager();
		if (!factionManager)
			Print("#StealTheCar: COULD NOT GET FACTION MANAGER", LogLevel.ERROR);
		
		//SCR_Faction playerFaction;
		//GetFirstPlayableFaction(factionManager, playerFaction);
		
		SCR_Faction playerFaction = GetFirstPlayableFaction(factionManager);
	
		if (!playerFaction)
			Print("#StealTheCar: NO PLAYABLE FACTION FOUND");
		
		array<SCR_SpawnPoint> availableSpawnpoints = SCR_SpawnPoint.GetSpawnPoints();
		SCR_SpawnPoint playerSpawn = availableSpawnpoints.GetRandomElement();
		
//		Print("Spawning player as faction - %1", playerFaction.GetFactionName());
		
		respawnComponent.DoSetPlayerFaction(playerId, respawnComponent.GetFactionIndex(playerFaction));
		respawnComponent.DoSetPlayerLoadout(playerId, 0);
		respawnComponent.SetPlayerSpawnPoint(playerId, SCR_SpawnPoint.GetSpawnPointRplId(playerSpawn));
		
		playerController.RequestRespawn();
	}
	
	protected void InitTasks()
	{
		SCR_PopUpNotification.GetInstance().PopupMsg("Steal the car!");
	}
	
	protected SCR_Faction GetFirstPlayableFaction(notnull FactionManager factionManager, /*out SCR_Faction outFaction*/)
	{
		array<Faction> allFactions = {};
		factionManager.GetFactionsList(allFactions);
		
		foreach (Faction faction: allFactions)
		{
			SCR_Faction scrFaction = SCR_Faction.Cast(faction);
			if (scrFaction.IsPlayable())
			{
				//outFaction = scrFaction;
				return scrFaction;
			}
		}
		
		return null;
	}
	
};