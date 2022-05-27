[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class VET_InitTimeComponentClass : SCR_BaseGameModeComponentClass
{
};

class VET_InitTimeComponent : SCR_BaseGameModeComponent
{	
	[Attribute(defvalue: "8", desc: "Takes integer up to 24 (hours) and is used to set the inital time.", params: "0 24")]
	protected int m_initialHour;
	
	[Attribute(defvalue: "15", desc: "Takes integer up to 60 (minutes) and is used to set the inital time.", params: "0 60")]
	protected int m_initialMinute;
	
	[Attribute(defvalue: "0", desc: "Takes float up to 60 (seconds) and is used to set the inital time.", params: "0 60")]
	protected int m_initialSeconds;
	
	//~ Sets initial time state when server is first loaded.
	protected void InitTimeServer()
	{
		if (!Replication.IsServer())
			return;
		
		TimeAndWeatherManagerEntity timeManager = GetGame().GetTimeAndWeatherManager();
		if (!timeManager) 
		{
			Print("VET_InitTimeComponent could not find TimeAndWeatherManagerEntity", LogLevel.WARNING);
			return;
		}
		
		timeManager.SetTime(new TimeContainer(m_initialHour, m_initialMinute, m_initialSeconds));
	}
	
	override void EOnInit(IEntity owner)
	{
		InitTimeServer();
	}
	
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT);
	}
};
