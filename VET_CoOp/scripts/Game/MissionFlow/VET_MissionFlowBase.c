class VET_MissionFlowBaseClass : GenericEntityClass {}

class VET_MissionFlowBase : GenericEntity
{
	private static VET_MissionFlowBase s_Instance;
	
	protected ScriptInvoker m_missionEventInvoker;
	
	void VET_MissionFlowBase(IEntitySource src, IEntity parent)
	{
		Print("VET_MissionFlowBase, constructing mission flow");
		
		SetEventMask(EntityEvent.FRAME | EntityEvent.INIT);
		SetFlags(EntityFlags.ACTIVE, true);
		
		s_Instance = this;
	}
	
	void ~VET_MissionFlowBase() { s_Instance = null; }
	
	static VET_MissionFlowBase GetInstance() { return s_Instance; }
}