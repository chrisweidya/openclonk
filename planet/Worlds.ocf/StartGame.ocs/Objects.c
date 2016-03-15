/* Automatically created objects file */

static i_width;
static a_width;
static baseHeight;
static seed;
static immersion_level;
static achievement_level;
static lost_npc;
static immersion_npc;
static achievement_npc;
static category;
static target_npc;

func InitializeObjects()
{
	category = GetMapDataFromPlayer();
	i_width = LandscapeWidth() / 2 + LandscapeWidth()*category/ 6;
	a_width = LandscapeWidth() - i_width;

	baseHeight = (LandscapeHeight() / 2);
	seed = GetSeed();
	Log("seed %v", seed);
	immersion_level = GetPlayerImmLevel();
	achievement_level = GetPlayerAchLevel();
	Log("imm/ach level %v %v", immersion_level, achievement_level);


	InitSettlement();
	InitChest(immersion_level, achievement_level);
	InitImmersionNPC();
	InitAchievementNPC();
	InitLostNPC(seed);
	InitFoundNPC();
	InitTargetNPC(seed);
	InitBuildings();
	InitBats(achievement_level);
	InitTrees(seed, immersion_level);
	return true;
	
}

private func InitSettlement() {
	var respawn = CreateObject(Rule_BaseRespawn);
	respawn->SetInventoryTransfer(true);
	respawn->SetFreeCrew(true);

	var flagpole = CreateObjectAbove(Flagpole, LandscapeWidth() / 2 + 100, baseHeight);
	flagpole->SetNeutral(true);
	//	flagpole->SetObjectLayer(flagpole);

	var elevator = CreateObjectAbove(Elevator, LandscapeWidth() / 2 + 40, LandscapeHeight() / 2);
	elevator->SetDir(DIR_Left);
	elevator->CreateShaft(530);
	elevator->SetCasePosition(LandscapeHeight() / 2);
	elevator->SetNoPowerNeed(true);

	var cabin = CreateObjectAbove(WoodenCabin, LandscapeWidth() / 2 + 10, baseHeight - 1);
	cabin->SetObjectLayer(cabin);

}

private func InitChest(int immersion_level, int achievement_level) {
	var chest = CreateObjectAbove(Chest, LandscapeWidth() / 2 + 115, baseHeight);
	chest->CreateContents(LoamUnlimited);
	if (immersion_level > 0) {
		chest->CreateContents(Pickaxe);
		chest->CreateContents(Axe);
	}
	if (achievement_level > 0) {
		chest->CreateContents(Bow);
		var arrow = chest->CreateContents(Arrow);
		arrow->SetInfiniteStackCount();
		chest->CreateContents(Sword);
	}
	if (achievement_level > 1) {
		var javelin = chest->CreateContents(Javelin);
		javelin->SetInfiniteStackCount();
	}
	if (achievement_level > 2) {
		chest->CreateContents(Musket);
		var leadshot = chest->CreateContents(LeadShot);
		leadshot->SetInfiniteStackCount();
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
	immersion_npc.level = immersion_level;
	immersion_npc->SetDialogue("Aerin", true);
	immersion_npc->MakeInvincible();
	immersion_npc.StaticSaveVar = "immersion_npc";
}

private func InitAchievementNPC() {

	achievement_npc = CreateObjectAbove(Clonk, LandscapeWidth() / 2 + 200, baseHeight - 10);
	achievement_npc->SetColor(0x00007a);
	achievement_npc->SetName(Format("Warra"));
	achievement_npc->SetObjectLayer(achievement_npc);
	achievement_npc->SetSkin(2);
	achievement_npc->SetDir(DIR_Left);
	achievement_npc.level = achievement_level;
	achievement_npc->SetDialogue("Warra", true);
	achievement_npc->MakeInvincible();
	achievement_npc.StaticSaveVar = "achievement_npc";
}

private func InitLostNPC(int seed) {
	if (immersion_level < 1 || GetBuildingsCompleted() == 3) {
		var name_size = $ImmersionNPCNameSize$;
		var name_index = GetRandomNum(name_size, seed);
		var skin = GetRandomNum(4, seed);
		var colour = GetRandomColour(seed);
		var y = GetRandomNum(LandscapeHeight()-5, seed);
		var x = GetRandomNum(LandscapeWidth()/3 - 100, seed);

		var outer = 25;
		var inner = 15;
		DrawMaterialQuad("Sand", x - inner, y + inner, x + inner, y + inner, x + outer, y + outer, x - outer, y + outer);
		ClearFreeRect(x - outer / 2, y - outer / 2, outer, outer);

		//	lost_npc = CreateObjectAbove(Clonk, 600, baseHeight-5);
		lost_npc = CreateObjectAbove(Clonk, x, y);
		lost_npc->SetColor(colour);
		lost_npc->SetName(Translate(Format("ImmersionNPCName%d", name_index)));
		lost_npc->SetObjectLayer(lost_npc);
		lost_npc->SetSkin(skin);
		lost_npc->SetDir(DIR_Right);
		lost_npc->SetDialogue(Format("$LostNPC$"), true);
		lost_npc->MakeInvincible();
		lost_npc.StaticSaveVar = "lost_npc";
	}
}

private func InitFoundNPC() {
	var name_size = $ImmersionNPCNameSize$;
	var name_index;
	var skin;
	var colour;
	var max = 10;
	var npc_seed = -1;
	var found_npc;
	for (var i = 0; i < 5; i++) {
		npc_seed = GetFoundNPC(i);
		if (npc_seed != 0) {
			Log("npc in script: %v", npc_seed);
			name_index = GetRandomNum(name_size, npc_seed);
			skin = GetRandomNum(4, npc_seed);
			colour = GetRandomColour(npc_seed);

			found_npc = CreateObjectAbove(Clonk, LandscapeWidth()/2 - 25 + i*50, baseHeight - 5);
			found_npc->SetColor(colour);
			found_npc->SetName(Translate(Format("ImmersionNPCName%d", name_index)));
			found_npc->SetObjectLayer(found_npc);
			found_npc->SetSkin(skin);
			if (i % 2 == 0)
				found_npc->SetDir(DIR_Right);
			else
				found_npc->SetDir(DIR_Left);
			//	found_npc->SetDialogue(Format("$LostNPC$"), true);
			found_npc->CreateContents(Hammer);
			found_npc->SetDialogue("FoundNPC");
		}
		else
			break;
	}
}

private func InitTargetNPC(int seed) {
	var name_size = $AchievementNPCNameSize$;
	var name_index = GetRandomNum(name_size, seed);
	var skin = GetRandomNum(4, seed);
	var colour = GetRandomColour(seed);
	var weapon = GetRandomNum(3, seed);
	var y = GetRandomNum(LandscapeHeight(), seed);
	var x = GetRandomNum(LandscapeWidth()/3, seed);
	
	x += LandscapeWidth() * 2 / 3 + 50;
	if (x > LandscapeWidth() - 10)
		x = LandscapeWidth() - 10;

	var width = 150;	
	var height = 100;
	DigFreeRect(x - width / 2, y - height / 2, width, height);
	DrawMaterialQuad("Earth", x - width / 2, y + height / 2 - 10, x + width / 2, y + height / 2 - 10, 
		x + width / 2, y + height / 2, x - width / 2, y + height / 2, DMQ_Sub);

	target_npc = CreateObjectAbove(Clonk, x, y);
	target_npc->SetColor(colour);
	target_npc->SetName(Translate(Format("AchievementNPCName%d", name_index)));
	target_npc->SetSkin(skin);
	target_npc->SetDir(DIR_Right);
	SetWeapon(weapon, target_npc);
	target_npc.isTarget = true;
	target_npc.StaticSaveVar = "target_npc";
	AI->AddAI(target_npc);
	AI->SetGuardRange(target_npc, x, y, width/2, height/2);
	AI->SetAllyAlertRange(target_npc, 60);

	if (achievement_level > 3) {
		InitGuards(x, y, colour);
	}
}

private func InitGuards(int x, int y, int colour) {
	var guard;
	guard = CreateObjectAbove(Clonk, x-5, y);
	guard->SetColor(colour);
	guard->SetName("Guard");
	guard->SetSkin(0);
	guard->SetDir(DIR_Left);
	SetWeapon(0, guard);
	AI->AddAI(guard);
	AI->SetGuardRange(guard, x-100, y, 100, 50);
	AI->SetAllyAlertRange(guard, 60);
}

private func InitBuildings() {
	var buildingsCompleted = GetBuildingsCompleted();
	if (buildingsCompleted > 0)
		CreateObjectAbove(Foundry, LandscapeWidth() / 2 - 80, baseHeight-1);
	if (buildingsCompleted > 1)
		CreateObjectAbove(WindGenerator, LandscapeWidth() / 2 - 120, baseHeight);
	if (buildingsCompleted > 2)
		CreateObjectAbove(Shipyard, LandscapeWidth() / 2 - 230, baseHeight);
}

private func InitBats(int achievement_level) {
	var bats = Bat->Place(6 * (achievement_level - category), Rectangle( i_width, 0, a_width, LandscapeHeight()));
	// Make the bats a bit weaker so that they are killed with a single arrow.
	var extra_hp = achievement_level * 1000;
	for (var bat in bats)
	{
		bat.MaxEnergy = 3000 + extra_hp;
		bat->DoEnergy(bat.MaxEnergy - bat->GetEnergy());
		bat->AddEnergyBar();
	}
}

private func SetWeapon(int index, object npc) {
	if (index == 0) 
		npc->CreateContents(Sword);
	else if (index == 1) {
		npc->CreateContents(Bow);
		var arrow = npc->CreateContents(Arrow);
		arrow->SetInfiniteStackCount();
	}
	else if (index == 2) {
		var jav = npc->CreateContents(Javelin);
		jav->SetInfiniteStackCount();
	}
	
}

private func InitTrees(int seed, int immersion_level) {
	var num_plants = immersion_level + 2 * category;
	if (immersion_level > 0 && num_plants <= 0)
		num_plants = immersion_level;
	Fern->Place(6*num_plants, Rectangle(0, 0, i_width, LandscapeHeight()));
	Wheat->Place(3 * num_plants, Rectangle(0, 0, i_width, LandscapeHeight()));
	Cotton->Place(2 * num_plants, Rectangle(0, 0, i_width, LandscapeHeight()));
	Tree_Coniferous->Place(2 * num_plants, Rectangle(0, 0, i_width, LandscapeHeight()));
	Tree_Deciduous->Place(2 * num_plants, Rectangle(0, 0, i_width, LandscapeHeight()));
	Grass->Place(4*num_plants);
	if (immersion_level > 0) {
		Tree_Coconut->Place(2 * num_plants, Rectangle(0, 0, i_width, LandscapeHeight()));
	}
	if (immersion_level > 1) {
		Flower->Place(15 * num_plants, Rectangle(0, 0, i_width, LandscapeHeight()));
		Butterfly->Place(5 * num_plants, Rectangle(0, 0, i_width, LandscapeHeight()));
	}
}

