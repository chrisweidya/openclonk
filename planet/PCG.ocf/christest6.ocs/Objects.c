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
	Log("seed %v", seed);
	Log(" offset %v ", groundOffset);
	immersion_level = GetPlayerImmLevel();
	achievement_level = GetPlayerAchLevel();
	Log("imm/ach level %v %v", immersion_level, achievement_level);

	var respawn = CreateObject(Rule_BaseRespawn);
	respawn->SetInventoryTransfer(true);
	respawn->SetFreeCrew(true);

	var flagpole = CreateObjectAbove(Flagpole, LandscapeWidth() / 2 + 100, baseHeight);
	flagpole->SetNeutral(true);
//	flagpole->SetObjectLayer(flagpole);
	
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
	InitBats(achievement_level);
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
	if (achievement_level > 0) {
		chest->CreateContents(Bow);
		var arrow = chest->CreateContents(Arrow);
		arrow->SetInfiniteStackCount();
	}
	if (achievement_level > 1) {
		var javelin = chest->CreateContents(Javelin);
		javelin->SetInfiniteStackCount();
	}
	if (achievement_level > 2) {chest->CreateContents(Musket);
		var leadshot = chest->CreateContents(LeadShot);
		leadshot->SetInfiniteStackCount();
	}
	if (achievement_level > 3) {
		chest->CreateContents(GrenadeLauncher);
		chest->CreateContents(IronBomb, 10);
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
}

private func InitAchievementNPC() {

	achievement_npc = CreateObjectAbove(Clonk, LandscapeWidth() / 2 + 200, baseHeight - 10);
	achievement_npc->SetColor(0x00007a);
	achievement_npc->SetName(Format("Warra"));
	achievement_npc->SetObjectLayer(achievement_npc);
	achievement_npc->SetSkin(2);
	achievement_npc->SetDir(DIR_Left);
	if(achievement_level > 1)
		achievement_npc->SetDialogue("Warra2", true);
	else
		achievement_npc->SetDialogue("Warra", true);
	achievement_npc->MakeInvincible();
}

private func InitLostNPC(int seed) {
	if (immersion_level < 2) {
		var name_size = $ImmersionNPCNameSize$;
		var name_index = GetRandomNum(name_size, seed);
		var skin = GetRandomNum(4, seed);
		var colour = GetRandomColour(seed);
		var y = GetRandomNum(baseHeight - 150, seed);
		var x = GetRandomNum(LandscapeWidth(), seed);

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

			found_npc = CreateObjectAbove(Clonk, 450 + i*50, baseHeight - 5);
			found_npc->SetColor(colour);
			found_npc->SetName(Translate(Format("ImmersionNPCName%d", name_index)));
			found_npc->SetObjectLayer(found_npc);
			found_npc->SetSkin(skin);
			if (i % 2 == 0)
				found_npc->SetDir(DIR_Right);
			else
				found_npc->SetDir(DIR_Left);
			//	found_npc->SetDialogue(Format("$LostNPC$"), true);
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
	var y = GetRandomNum(LandscapeHeight() - baseHeight, seed);
	var x = GetRandomNum(LandscapeWidth(), seed);
	
	y += baseHeight + 50;
	if (y >= LandscapeHeight() - 10) {
		y = LandscapeHeight() - 20;
	}
	
	var width = 150;	
	var height = 100;
	DigFreeRect(x - width / 2, y - height / 2, width, height);
	DrawMaterialQuad("Brick", x - width / 2, y + height / 2 - 10, x + width / 2, y + height / 2 - 10, 
		x + width / 2, y + height / 2, x - width / 2, y + height / 2);	

	target_npc = CreateObjectAbove(Clonk, x, y);
	target_npc->SetColor(colour);
	target_npc->SetName(Translate(Format("AchievementNPCName%d", name_index)));
	target_npc->SetSkin(skin);
	target_npc->SetDir(DIR_Right);
	SetWeapon(weapon, target_npc);
	target_npc.isTarget = true;
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

private func InitBats(int achievement_level) {
	var bats = Bat->Place(6 * achievement_level, 0, 0, LandscapeWidth(), baseHeight);
	// Make the bats a bit weaker so that they are killed with a single arrow.
	var extra_hp = achievement_level * 2000;
	for (var bat in bats)
	{
		bat.MaxEnergy = 7000 + extra_hp;
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
	var num_plants = immersion_level + 1;
	Fern->Place(12*num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight));
	Wheat->Place(5 * num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight));
	Cotton->Place(3 * num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight));
	Tree_Coniferous->Place(3 * num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight-100));
	Tree_Deciduous->Place(3 * num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight-100));
	Grass->Place(10*num_plants);
	if (immersion_level > 0) {
		Tree_Coconut->Place(3 * num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight));
	}
	if (immersion_level > 1) {
		Flower->Place(20 * num_plants, Rectangle(0, 0, LandscapeWidth(), baseHeight));
		Butterfly->Place(10, Rectangle(0, 0, LandscapeWidth(), baseHeight));
	}

//	CreateObjectAbove(Tree_Coniferous, 790, baseHeight);
//	CreateObjectAbove(Tree_Coniferous, 770, baseHeight);
//	CreateObjectAbove(Tree_Coniferous, 780, baseHeight);
}