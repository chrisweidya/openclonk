

func Initialize()
{	
	var groundOffset = GetMapDataFromPlayer();
	InitAI(groundOffset);
	CreateObjectAbove(Tree_Coniferous, 188, 384);

	return true;
}
protected func InitializePlayer(int plr)
{
	// Position player's clonk.
//	SetPlayerZoomByViewRange(plr, 400, 0, PLRZOOM_LimitMin);
	var groundOffset = GetMapDataFromPlayer();
	var clonk = GetCrew(plr, 0);
	clonk->CreateContents(Shovel);
	clonk->CreateContents(GrappleBow);
	clonk->CreateContents(Axe);
	var effect = AddEffect("ClonkRestore", clonk, 100, 10);
	effect.to_x = 48;
	effect.to_y = 374;

	clonk->SetPosition(320, (LandscapeHeight() / 2 + groundOffset * LandscapeHeight() / 8 ) - 20);
}

private func InitAI(int groundOffset)
{
	var seed = GetSeed();
	var immersion_npc_size = $ImmersionNPCSize$;
	var immersion_npc_index = GetRandomNum(immersion_npc_size, seed);
	var immersion_npc_skin = GetRandomNum(4, seed);
	var colour = GetRandomColour(seed);

	var immersion_npc = CreateObjectAbove(Clonk, 380, (LandscapeHeight() / 2 + groundOffset * LandscapeHeight() / 8) - 20);
	immersion_npc->SetColor(colour);
	immersion_npc->SetName(Translate(Format("ImmersionNPC%d", immersion_npc_index)));
	immersion_npc->SetObjectLayer(immersion_npc);
	immersion_npc->SetSkin(immersion_npc_skin);
	immersion_npc->SetDir(DIR_Left);
	immersion_npc->SetDialogue(immersion_npc->GetName(), true);
	
	return;
}

