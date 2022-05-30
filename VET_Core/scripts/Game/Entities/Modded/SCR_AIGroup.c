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
	
#ifdef WORKBENCH
	
	override void _WB_AfterWorldUpdate(float timeSlice)
	{
		super._WB_AfterWorldUpdate(timeSlice);
		
		// draw spawned waypoints positions
		foreach (SCR_WaypointPrefabLocation spawnedWaypoint : m_aSpawnedWaypoints)
		{
			float radius;
			if (spawnedWaypoint.m_WPRadiusOverride)
			{
				radius = spawnedWaypoint.m_WPRadiusOverride;
			}
			else
			{
				Resource wpRes = Resource.Load(spawnedWaypoint.m_WPPrefabName);
				wpRes.GetResource().ToBaseContainer().Get("CompletionRadius", radius);
			}
			
			vector waypointPosition = spawnedWaypoint.m_WPWorldLocation;
			//Shape shape = Shape.CreateSphere(COLOR_YELLOW, ShapeFlags.ONCE | ShapeFlags.NOOUTLINE, waypointPosition, radius);
			Color color = Color.FromRGBA(0, 0, 255, 128);
			Shape shape = Shape.CreateCylinder(color.PackToInt(), ShapeFlags.ONCE | ShapeFlags.NOOUTLINE | ShapeFlags.TRANSP, waypointPosition, radius, 2);
			Shape arrow = Shape.CreateArrow(GetOrigin() + "0 3 0", waypointPosition + "0 1 0", 1.5, COLOR_YELLOW, ShapeFlags.ONCE);
		}		
	}
	
#endif
	
}