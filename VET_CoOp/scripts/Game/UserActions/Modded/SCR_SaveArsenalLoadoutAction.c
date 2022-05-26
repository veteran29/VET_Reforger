modded class SCR_SaveArsenalLoadout : ScriptedUserAction
{
	override protected void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		super.PerformAction(pOwnerEntity, pUserEntity);
		
		SCR_BaseGameMode gameMode = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		
		// TODO use Event_OnPlayerLoadoutUpdated??
		//SCR_ArsenalManagerComponent arsenalManager;
		//SCR_ArsenalManagerComponent.GetArsenalManager(arsenalManager);
		
		SCR_FactionManager factionManager = SCR_FactionManager.Cast(GetGame().GetFactionManager());
		SCR_RespawnSystemComponent respawnComponent = gameMode.GetRespawnSystemComponent();
		SCR_LoadoutManager loadoutManager = GetGame().GetLoadoutManager();
		
		array<SCR_BasePlayerLoadout> outLoadouts = {};
		loadoutManager.GetPlayerLoadouts(outLoadouts);
		
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		SCR_Faction playerFaction = SCR_Faction.Cast(respawnComponent.GetLocalPlayerFaction(pUserEntity));
		
		foreach (SCR_BasePlayerLoadout loadout : outLoadouts)
		{
			SCR_PlayerArsenalLoadout arsenalLoadout = SCR_PlayerArsenalLoadout.Cast(loadout);
			if (!arsenalLoadout)
				continue;
			
			if (arsenalLoadout.GetFactionKey() != playerFaction.GetFactionKey())
				continue;
			
			Print("Setting player respawn loadout to Arsenal loadout");
			
			int loadoutIndex = loadoutManager.GetLoadoutIndex(arsenalLoadout);
			respawnComponent.DoSetPlayerLoadout(playerId, loadoutIndex);
		}
	}
}