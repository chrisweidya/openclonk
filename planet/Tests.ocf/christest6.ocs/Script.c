
local immersion_npc;

func Initialize()
{	
	var groundOffset = GetMapDataFromPlayer();
//	InitAI(groundOffset);

	initQuest(LandscapeHeight() / 2 + groundOffset * LandscapeHeight() / 8);

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
	
	for (var structure in FindObjects(Find_Or(Find_Category(C4D_Structure), Find_Func("IsFlagpole"))))
		structure->SetOwner(plr);
	/*
	var site = FindObject(Find_ID(ConstructionSite));
	site->SetOwner(plr);
	*/
	
}

private func InitAI(int groundOffset)
{
	var seed = GetSeed();
	var immersion_npc_size = $ImmersionNPCSize$;
	var immersion_npc_index = GetRandomNum(immersion_npc_size, seed);
	var immersion_npc_skin = GetRandomNum(4, seed);
	var colour = GetRandomColour(seed);

	immersion_npc = CreateObjectAbove(Clonk, 380, (LandscapeHeight() / 2 + groundOffset * LandscapeHeight() / 8) - 20);
	immersion_npc->SetColor(colour);
	immersion_npc->SetName(Translate(Format("ImmersionNPC%d", immersion_npc_index)));
	immersion_npc->SetObjectLayer(immersion_npc);
	immersion_npc->SetSkin(immersion_npc_skin);
	immersion_npc->SetDir(DIR_Left);
	immersion_npc->SetDialogue(immersion_npc->GetName(), true);
	return;
}

private func initQuest(int height) {
	CreateObjectAbove(WindGenerator, 324, height-5);
//	var site = CreateObjectAbove(ConstructionSite, 364, height);
//	site.MeshTransformation = Trans_Mul(Trans_Rotate(RandomX(-30, 30), 0, 1, 0), Trans_Rotate(RandomX(-10, 10), 1, 0, 0));
//	site->Set(Sawmill);
//	site->CreateContents(Wood, 1);
//	site->CreateContents(Rock, 1);
//	var effect = AddEffect("CreatedSawmill", nil, 100, 5);
//	effect.plr = plr;
}

private func FxCreatedSawmillTimer(object target, proplist effect) {
	if (FindObject(Find_ID(Sawmill)))
	{
		// Notify lumberjack the sawmill is done.
		var dialogue_lumberjack = Dialogue->FindByName(immersion_npc->GetName());
		if (dialogue_lumberjack)
			dialogue_lumberjack->SetDialogueProgress(5, nil, true);
		return FX_Execute_Kill;
	}
}