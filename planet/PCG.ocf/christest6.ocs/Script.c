local seed;
local baseHeight;
local immersion_npc;
local lost_npc;
local player;
local guide;
local goal;

func Initialize()
{	
	resetProfile();
	var groundOffset = GetMapDataFromPlayer();
	baseHeight = (LandscapeHeight() / 2 + groundOffset * LandscapeHeight() / 8);

	InitGoal();
	CreateObjectAbove(WoodenCabin, LandscapeWidth() / 2 - 120, baseHeight );
	InitAI();	

	return true;
}
protected func InitGoal()
{
	goal = CreateObject(Goal_PCG);
	goal.Name = "$MsgGoalName$";
	goal.Description = "$MsgGoalDescription$";
}
protected func InitializePlayer(int plr)
{
	// Position player's clonk.
//	SetPlayerZoomByViewRange(plr, 400, 0, PLRZOOM_LimitMin);
	player = plr;
	var clonk = GetCrew(plr, 0);
	clonk->CreateContents(Shovel);
	clonk->CreateContents(GrappleBow);
	clonk->CreateContents(Hammer);
	clonk->CreateContents(Rock, 3);

	var effect = AddEffect("ClonkRestore", clonk, 100, 10);
	effect.to_x = 48;
	effect.to_y = 374;

	clonk->SetPosition(LandscapeWidth()/2, baseHeight - 20);
	
	/*
	for (var structure in FindObjects(Find_Or(Find_Category(C4D_Structure), Find_Func("IsFlagpole"))))
		structure->SetOwner(plr);
	var site = FindObject(Find_ID(ConstructionSite));
	site->SetOwner(plr);
	
	*/

//	guide = CreateObject(PCGGuide, 0, 0, plr);
//	guide->HideGuide();
}

// Gamecall from goals, set next mission.
protected func OnGoalsFulfilled()
{
	UpdateFoundNPC(seed, player);
	SetNextMission("PCG.ocf\\christest6.ocs", "$MsgNext$", "$MsgNextDesc$");
	return false;
}

private func InitAI()
{
	seed = GetSeed();
	InitImmersionNPC(seed);
	InitFoundNPC();
	InitLostNPC(seed);
	return;
}


private func InitImmersionNPC(int seed) {
	
	immersion_npc = CreateObjectAbove(Clonk, LandscapeWidth() / 2 - 100, baseHeight - 20);
	immersion_npc->SetColor(0x00997a);
	immersion_npc->SetName(Format("Aerin"));
//	immersion_npc->SetName(Translate(Format("ImmersionNPC%d", immersion_npc_index)));
	immersion_npc->SetObjectLayer(immersion_npc);
	immersion_npc->SetSkin(3);
	immersion_npc->SetDir(DIR_Right);
	immersion_npc->SetDialogue(immersion_npc->GetName(), true);

}

private func InitLostNPC(int seed) {
	var name_size = $ImmersionNPCNameSize$;
	var name_index = GetRandomNum(name_size, seed);
	var skin = GetRandomNum(4, seed);
	var colour = GetRandomColour(seed);
	var y = GetRandomNum(baseHeight - 100, seed);
	var x = GetRandomNum(LandscapeWidth(), seed);

	var outer = 25;
	var inner = 15;
	DrawMaterialQuad("Sand", x -inner, y + inner, x + inner, y + inner, x + outer, y + outer, x - outer, y + outer);
	DigFree(x, y, 15);

//	lost_npc = CreateObjectAbove(Clonk, 600, baseHeight-5);
	lost_npc = CreateObjectAbove(Clonk, x, y);
	lost_npc->SetColor(colour);
	lost_npc->SetName(Translate(Format("ImmersionNPCName%d", name_index)));
	lost_npc->SetObjectLayer(lost_npc);
	lost_npc->SetSkin(skin);
	lost_npc->SetDir(DIR_Right);
	lost_npc->SetDialogue(Format("$LostNPC$"), true);
}

private func InitFoundNPC() {
	var name_size = $ImmersionNPCNameSize$;
	var name_index;
	var skin;
	var colour;
	var max = 10;
	var npc_seed = -1;
	var found_npc;
	npc_seed = GetFoundNPC(0);
	Log("%vseed", npc_seed);
	if (npc_seed != 0) {		
		name_index = GetRandomNum(name_size, npc_seed);
		skin = GetRandomNum(4, npc_seed);
		colour = GetRandomColour(npc_seed);

		found_npc = CreateObjectAbove(Clonk, 700, baseHeight - 5);
		//	lost_npc = CreateObjectAbove(Clonk, x, y);
		found_npc->SetColor(colour);
		found_npc->SetName(Translate(Format("ImmersionNPCName%d", name_index)));
		found_npc->SetObjectLayer(found_npc);
		found_npc->SetSkin(skin);
		found_npc->SetDir(DIR_Right);
	//	found_npc->SetDialogue(Format("$LostNPC$"), true);
	}
	else
		Log("not init");
}

/*
private func initQuest() {
	var site = CreateObjectAbove(ConstructionSite, 364, baseHeight +5);
	site.MeshTransformation = Trans_Mul(Trans_Rotate(RandomX(-30, 30), 0, 1, 0), Trans_Rotate(RandomX(-10, 10), 1, 0, 0));
	site->Set(Sawmill);
	site->CreateContents(Wood, 1);
	site->CreateContents(Rock, 1);
	addImmersionObjective(1);
}

private func addImmersionObjective(int index) {
	var effect;
	if(index == 1)
		effect = AddEffect("CheckConstruction", immersion_npc, 100, 5);
	effect.player = player;
}
*/
public func OnHasTalkedToLostNPC()
{	
//	guide->AddGuideMessage("$GameCompleted$");
//	guide->ShowGuideMessage(0);
//	guide->ShowGuide();
	
	goal->Fulfill();
	return;
}

private func resetProfile() {
	ResetProfile();
	return;
}

/*
global func FxCheckConstructionTimer(object target, proplist effect) {
	if (FindObject(Find_ID(target.objective)))
	{
		// Notify lumberjack the sawmill is done.
		var dialogue_lumberjack = Dialogue->FindByName(target->GetName());
		if (dialogue_lumberjack)
			dialogue_lumberjack->SetDialogueProgress(5, nil, true);
		return FX_Execute_Kill;
	}
}
*/