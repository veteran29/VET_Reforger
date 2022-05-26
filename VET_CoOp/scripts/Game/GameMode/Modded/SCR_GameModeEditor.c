modded class SCR_GameModeEditor : SCR_BaseGameMode
{
	override protected void OnPlayerTerminated(int playerId)
	{
		Print("OnPlayerTerminated override, prevent player from being forced into Game Master camera", LogLevel.DEBUG);
	}
}