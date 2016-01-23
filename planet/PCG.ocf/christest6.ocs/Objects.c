/* Automatically created objects file */

static baseHeight;
static seed;
static immersion_level;
static achievement_level;
static lost_npc;
static immersion_npc;
static achievement_npc;
static target_npc;

func InitializeObjects()
{
	var groundOffset = GetMapDataFromPlayer();
	baseHeight = (LandscapeHeight() / 2 + groundOffset * LandscapeHeight() / 8);
	seed = GetSeed();
	immersion_level = GetPlayerImmLevel();
	achievement_level = GetPlayerAchLevel();
	Log("base height: %v %v", seed, LandscapeHeight());

	var respawn = CreateObject(Rule_BaseRespawn);
	respawn->SetInventoryTransfer(true);
	respawn->SetFreeCrew(true);

	var flagpole = CreateObjectAbove(Flagpole, LandscapeWidth() / 2 + 100, baseHeight);
	flagpole->SetNeutral(true);
	flagpole->SetObjectLayer(flagpole);
	
	var cabin = CreateObjectAbove(WoodenCabin, LandscapeWidth() / 2 + 10, baseHeight-1);
	cabin->SetObjectLayer(cabin);

//	var sm = CreateObjectAbove(Foundry, 400, baseHeight - 1);
//	var sm = CreateObjectAbove(WindGenerator, 360, baseHeight - 1);
//	var sm = CreateObjectAbove(Shipyard, 250, baseHeight - 1);

	InitChest(immersion_level, achievement_level);
	InitImmersionNPC();
	InitAchievementNPC();
	InitLostNPC(seed);
	InitFoundNPC();
	InitTargetNPC(seed);
	InitTrees(seed, immersion_level);
	return true;
	
}

private func InitChest(int immersion_level, int achievement_level) {
	var chest = CreateObjectAbove(Chest, LandscapeWidth() / 2 + 115, baseHeight);
	chest->CreateContents(LoamUnlimited);
	if (immersion_level > 0) {
		chest->CreateContents(Pickaxe);
		chest->CreateContents(Axe);
		chest->CreateContents(Rock, 8);
		chest->CreateContents(Wood, 8);
		chest->CreateContents(Coal, 8);
		chest->CreateContents(Ore, 8);
	}
}

private func InitImmersionNPC() {

	immersion_npc = CreateObjectAbove(Clonk, LandscapeWidth() / 2 , baseHeight - 10);
	immersion_npc->SetColor(0x00997a);
	immersion_npc->SetName(Format("Aerin"));
	//	immersion_npc->SetName(Translate(Format("ImmersionNPC%d", immersion_npc_index)));
	immersion_npc->SetObjectLayer(immersion_npc);
	immersion_npc->SetSkin(3);
	immersion_npc->SetDir(DIR_Right);	
	if (immersion_level > 1) {
		immersion_npc->SetDialogue("Aerin2", true);
	}
	else {
		immersion_npc->SetDialogue("Aerin", true);
	}
	immersion_npc->MakeInvincible();
}

private func InitAchievementNPC() {

	achievement_npc = CreateObjectAbove(Clonk, LandscapeWidth() / 2 + 200, baseHeight - 10);
	achievement_npc->SetColor(0x00007a);
	achievement_npc->SetName(Format("Warra"));
	achievement_npc->SetObjectLayer(achievement_npc);
	achievement_npc->SetSkin(2);
	achievement_npc->SetDir(DIR_Left);
	achievement_npc->SetDialogue(achievement_npc->GetName(), true);
	achievement_npc->MakeInvincible();
}

private func InitLostNPC(int seed) {
	var name_size = $ImmersionNPCNameSize$;
	var name_index = GetRandomNum(name_size, seed);
	var skin = GetRandomNum(4, seed);
	var colour = GetRandomColour(seed);
	var y = GetRandomNum(baseHeight - 150, seed);
	var x = GetRandomNum(LandscapeWidth(), seed);

	var outer = 25;
	var inner = 15;
	DrawMaterialQuad("Sand", x - inner, y + inner, x + inner, y + inner, x + outer, y + outer, x - outer, y + outer);
	ClearFreeRect(x - outer/2, y - outer/2, outer, outer);

	//	lost_npc = CreateObjectAbove(Clonk, 600, baseHeight-5);
	lost_npc = CreateObjectAbove(Clonk, x, y);
	lost_npc->SetColor(colour);
	lost_npc->SetName(Translate(Format("ImmersionNPCName%d", name_index)));
	lost_npc->SetObjectLayer(lost_npc);
	lost_npc->SetSkin(skin);
	lost_npc->SetDir(DIR_Right);
	lost_npc->SetDialogue(Format("$LostNPC$"), true);
	lost_npc->MakeInvincible();
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
	if (npc_seed != 0) {
		name_index = GetRandomNum(name_size, npc_seed);
		skin = GetRandomNum(4, npc_seed);
		colour = GetRandomColour(npc_seed);

		found_npc = CreateObjectAbove(Clonk, 700, baseHeight - 5);
		found_npc->SetColor(colour);
		found_npc->SetName(Translate(Format("ImmersionNPCName%d", name_index)));
		found_npc->SetObjectLayer(found_npc);
		found_npc->SetSkin(skin);
		found_npc->SetDir(DIR_Right);
		//	found_npc->SetDialogue(Format("$LostNPC$"), true);
	}
}

private func InitTargetNPC(int seed) {
	var name_size = $AchievementNPCNameSize$;
	var name_index = GetRandomNum(name_size, seed);
	var skin = GetRandomNum(4, seed);
	var colour = GetRandomColour(seed);
	var y = GetRandomNum(LandscapeHeight() - baseHeight, seed);
	var x = GetRandomNum(LandscapeWidth(), seed);

	
	y += baseHeight + 50;
	if (y >= LandscapeHeight() - 10) {
		Log("exceeded y ");
		y = LandscapeHeight() - 20;
	}
	Log("Base height %v", y);
	var width = 150;	
	var height = 100;

	DigFreeRect(x - width / 2, y - height / 2, width, height);
	DrawMaterialQuad("Granite", x - width / 2, y + height / 2 - 10, x + width / 2, y + height / 2 - 10, 
		x + width / 2, y + height / 2, x - width / 2, y + height / 2);
	

	target_npc = CreateObjectAbove(Clonk, x, y);
	target_npc->SetColor(colour);
	target_npc->SetName(Translate(Format("AchievementNPCName%d", name_index)));
	target_npc->SetSkin(skin);
	target_npc->SetDir(DIR_Right);
	target_npc->CreateContents(Sword);
	target_npc.isTarget = true;
	AI->AddAI(target_npc);
	AI->SetGuardRange(target_npc, x, y, width/2, height/2);
	//	AI->SetEncounterCB(target_npc, "EncounterKing");
	//	target_npc->SetDialogue(Format("$LostNPC$"), true);
}

private func InitTrees(int seed, int immersion_level) {
	var x = 123, y = baseHeight;
	var inner = 15;
	var num_plants = immersion_level + 1;
	Fern->Place(12*num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight));
	Wheat->Place(5 * num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight));
	Cotton->Place(3 * num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight));
	Tree_Coniferous->Place(3 * num_plants, Rectangle(0, baseHeight / 2, LandscapeWidth(), baseHeight / 2));
	Tree_Deciduous->Place(3 * num_plants, Rectangle(0, baseHeight / 2, LandscapeWidth(), baseHeight / 2));
	Grass->Place(100*num_plants);
	if (immersion_level > 0) {
		Tree_Coconut->Place(3 * num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight));
	}
	if (immersion_level > 1) {
		Flower->Place(20 * num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight));
		Butterfly->Place(10, Rectangle(0, 0, LandscapeWidth(), baseHeight));
	}
}