[EntityEditorProps(category: "GameScripted/Misc", description: "")]
class VET_GroupSpawnerTriggerClass: SCR_BaseTriggerEntityClass
{
};

class VET_GroupSpawnerTrigger: SCR_BaseTriggerEntity
{
	protected ref array<SCR_AIGroup> m_groupsToSpawn = {};
	
	void VET_GroupSpawnerTrigger(IEntitySource src, IEntity parent)
	{	
		SetFlags(EntityFlags.ACTIVE, false);
		SetEventMask(EntityEvent.INIT);
	}
	
	override protected void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		GetOnActivate().Insert(OnActivatedSpawnGroups);
		HandleChildGroups();
	}
	
	//! Handle child groups and save them in an array for spawning.
	protected void HandleChildGroups()
	{
		IEntity child = GetChildren();
		while (child != null)
		{			
			SCR_AIGroup group = SCR_AIGroup.Cast(child);
			if (group)
			{
				m_groupsToSpawn.Insert(group);
			}
			
			child = GetSibling();
		}

		#ifdef WORKBENCH	
		if (m_groupsToSpawn.IsEmpty())
			Print("VET_GroupSpawnerTrigger, no groups to spawn, child groups need Hierarchy component", LogLevel.WARNING);
		else
			PrintFormat("VET_GroupSpawnerTrigger, found %1 groups to spawn", m_groupsToSpawn.Count());
		#endif
	}
	
	protected void OnActivatedSpawnGroups()
	{
		#ifdef WORKBENCH
		Print("VET_GroupSpawnerTrigger, Spawn groups");
		#endif
		
		GetOnActivate().Remove(OnActivatedSpawnGroups);
		
		foreach (SCR_AIGroup spawnedGroup : m_groupsToSpawn)
		{
			spawnedGroup.SpawnUnits();
		}
	}
	
	// Filter out only player controlled characters
	override bool ScriptedEntityFilterForQuery(IEntity ent)
	{
		if (!super.ScriptedEntityFilterForQuery(ent) || !IsAlive(ent))
			return false;
		
		return SCR_PossessingManagerComponent.GetPlayerIdFromMainEntity(ent) > 0;
	}
};
