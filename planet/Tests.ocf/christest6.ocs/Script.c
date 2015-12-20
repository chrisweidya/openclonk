

func Initialize()
{	
	InitAI();
	Log("Destruction of %v!", LandscapeHeight());
	return true;
}
protected func InitializePlayer(int plr)
{
	// Position player's clonk.
	var clonk = GetCrew(plr, 0);
	clonk->CreateContents(Sword);
	var effect = AddEffect("ClonkRestore", clonk, 100, 10);
	effect.to_x = 48;
	effect.to_y = 374;

	clonk->SetPosition(20, LandscapeHeight() / 3 - 10);
}

private func InitAI()
{
	var npc_aunt = CreateObjectAbove(Clonk, 80, LandscapeHeight() / 3 - 10);
	npc_aunt->SetColor(0xeaa444);
	npc_aunt->SetName("Aunt Julie");
	npc_aunt->SetObjectLayer(npc_aunt);
	npc_aunt->SetSkin(3);
	npc_aunt->SetDir(DIR_Left);
	npc_aunt->SetDialogue("Aunt", true);
	/*
	// A fireman NPC who extinguishes a burning cabin.	
	var npc_fireman = CreateObjectAbove(Clonk, 200, 384);
	npc_fireman->SetColor(0xff0000);
	npc_fireman->SetName("Hubert");
	var barrel = npc_fireman->CreateContents(Barrel);
	barrel->SetFilled("Water", 300);
	npc_fireman->SetObjectLayer(npc_fireman);
	npc_fireman->SetSkin(2);
	npc_fireman->SetDir(DIR_Left);
	npc_fireman->SetDialogue("Fireman", true);

	// A builder which tells you where to place the flagpole.
	var npc_builder = CreateObjectAbove(Clonk, 504, 376);
	npc_builder->SetColor(0x440088);
	npc_builder->SetName("Kummerog");
	npc_builder->CreateContents(Hammer);
	npc_builder->SetObjectLayer(npc_builder);
	npc_builder->SetDir(DIR_Left);
	npc_builder->SetDialogue("Builder", true);

	// A farmer near the grain field.
	var npc_farmer = CreateObjectAbove(Clonk, 720, 392);
	npc_farmer->SetColor(0x00ffff);
	npc_farmer->SetName("Genhered");
	npc_farmer->SetObjectLayer(npc_farmer);
	npc_farmer->SetSkin(1);
	npc_farmer->SetDir(DIR_Left);
	npc_farmer->SetDialogue("Farmer", true);

	// Lookout.
	*/
	// Village head.
	return;
}