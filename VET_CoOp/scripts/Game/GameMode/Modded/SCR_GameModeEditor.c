modded class SCR_GameModeEditor : SCR_BaseGameMode
{
	[Attribute(defvalue: "1", category: "Game Mode: Editor", desc: "Open the editor automatically after death when playing solo.")]
	protected bool m_openEditorAfterDeath;
	
	override protected void OnPlayerTerminated(int playerId)
	{
		if (!m_openEditorAfterDeath)
		{
			Print("OnPlayerTerminated override, prevent player from being forced into Game Master camera", LogLevel.DEBUG);
			return;
		}
		
		super.OnPlayerTerminated(playerId);
	}
}
