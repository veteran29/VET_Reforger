modded class SCR_AIGroup: ChimeraAIGroup
{
	bool VET_GetSpawnImmediately()
	{
		return m_bSpawnImmediately;
	}
	
	void VET_SetSpawnImmediately(bool spawnImmediately)
	{
		m_bSpawnImmediately = spawnImmediately;
	}
};