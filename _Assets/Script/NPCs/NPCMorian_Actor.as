class NPCMorian
{
	Actor@ actor;
	Controller@ controller;

	NPCMorian(Actor @in_actor)
	{
		@actor = in_actor;
		@controller = actor.GetController();
	}

	void Start()
	{
		controller.Walk(0);
	}

	void Update()
	{
		bool isKeyPressed = false;
		controller.Stand();
	}
}