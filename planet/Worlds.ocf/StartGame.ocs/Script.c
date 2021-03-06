//Created by Chris
//Handles in game events and scripts, player generation

local seed;
local baseHeight;
local site;
local player;
local playerNum;
static guide;
local goal;
local bat_deaths;
local tree_chopped;
local offset;

//Main function, sets variable default values
func Initialize()
{	
	//resetProfile(); //use this to clear save data settings
	offset = GetMapDataFromPlayer();
	baseHeight = LandscapeHeight() / 2 ;
	bat_deaths = tree_chopped = 0;
	seed = GetSeed();
	InitAI();
	InitGoal();
	
	return true;
}

//Creates goal events and info
protected func InitGoal()
{
	goal = CreateObject(Goal_PCG);
	goal.Name = "$MsgGoalName$";
	goal.Description = "$MsgGoalDescription$";
	target_npc.goal = goal;
	var effect = AddEffect("TargetDeath", target_npc, 100, 10);
	InitBuildQuest();
}

//Creates and positions main player, sets parameters for in-game variable tracking
protected func InitializePlayer(int plr)
{
//	SetPlayerZoomByViewRange(plr, 400, 0, PLRZOOM_LimitMin);

	//Player spawn parameters and items
	playerNum = plr;
	DisablePlrControls(plr);
	player = GetCrew(plr);	
	player->CreateContents(Shovel);
	player->CreateContents(GrappleBow);
	ItemGiver(player);
	player->SetPosition(LandscapeWidth()/2 + 100, baseHeight - 20);
	player->MakeInvincible();

	//Player in-game variable saving
	InitGuide(plr);
	player.deaths = 0;
	player.secs_spent_in_immersion = 0;
	player.secs_spent_in_achievement = 0;
	AddEffect("TrackDeaths", player, 100, 5);
	AddEffect("TrackPlayer", player, 100, 60);
}

//Gives a player a random weapon depending on achievement progression
private func ItemGiver(object clonk) {
	var index = GetRandomNum(4, seed);
	if (achievement_level == 0)
		index = 0;

	if (index == 0)
		clonk->CreateContents(Sword);
	else if (index == 1) {
		var jav = clonk->CreateContents(Javelin);
		jav->SetInfiniteStackCount();
	}
	else if (index == 2) {
		clonk->CreateContents(Bow);
		var arr = clonk->CreateContents(Arrow);
		arr->SetInfiniteStackCount();
	}
	else if (index == 3) {
		clonk->CreateContents(Musket);
		var leadshot = clonk->CreateContents(LeadShot);
		leadshot->SetInfiniteStackCount();
	}
	if (immersion_level > 0) {
		clonk->CreateContents(Pickaxe);
		clonk->CreateContents(Axe);
	}
}

//Starts the tutorial interface and the tutorial
protected func InitGuide(int plr) {
	var left = GetPlayerControlAssignment(plr, CON_Left, true, true);
	var right = GetPlayerControlAssignment(plr, CON_Right, true, true);
	var up = GetPlayerControlAssignment(plr, CON_Up, true, true);
	var down = GetPlayerControlAssignment(plr, CON_Down, true, true);
	var jump = GetPlayerControlAssignment(plr, CON_Jump, true, true);
	var control_keys = Format("[%s] [%s] [%s] [%s]", up, left, down, right);

	// Create tutorial guide, add messages, show first.
	guide = CreateObjectAbove(TutorialGuide, 0, 0, plr);
	if (immersion_level == 0 && achievement_level == 0) {
		guide->AddGuideMessage(Format("$MsgTutorialWelcome$", control_keys));
		guide->AddGuideMessage("$MsgTutorialHUD$");
	}
	else {
		guide->AddGuideMessage("$MsgTutorialRound$");
		guide->AddGuideMessage("$MsgTutorialChest$");
	}
	guide->AddGuideMessage(Format("$MsgTutorialHelpThem$"));
	guide->ShowGuideMessage(0);
}

// Sets next mission
protected func OnGoalsFulfilled()
{	
	SetNextMission("Worlds.ocf\\StartGame.ocs", "$MsgNext$", "$MsgNextDesc$");
	return false;
}

private func InitAI()
{
	InitEnemyHealth();
	return;
}

//Creates build quest and goal
private func InitBuildQuest() {
	var immersion_level = GetPlayerImmLevel();
	InitConstructionGoal(immersion_level);
}

//Sets enemy health depending on achievement level progression (difficulty setting)
private func InitEnemyHealth() {
	var fx;
	var hp = 12000;
	hp += (achievement_level + offset) * 12000;
	if (hp <= 0)
		hp = 12000;
	for (var npc in FindObjects(Find_ID(Clonk), Find_Owner(NO_OWNER))) {
		if (fx = AI->GetAI(npc))
		{
			fx.weapon = fx.target = nil;
			AI->BindInventory(npc);
			if (npc.isTarget) {
				target_npc = npc;
				npc.MaxEnergy = hp;
				npc->DoEnergy((npc.MaxEnergy - npc->GetEnergy()) / 1000);
				npc->AddEnergyBar();
			}
			else {
				npc.MaxEnergy = 25000;
				npc->AddEnergyBar();
			}
		}
	}
}

//Sets the construction goal and generates construction site depending on current building progress
private func InitConstructionGoal(int level) {
	var effect;
	var buildingsCompleted = GetBuildingsCompleted();
	if (level > 0) {
		if (!FindObject(Find_ID(Foundry)) && buildingsCompleted == 0) {
			immersion_npc.objective = Foundry;
			site = CreateObjectAbove(ConstructionSite, LandscapeWidth() / 2 - 80, baseHeight+2);
			site.MeshTransformation = Trans_Mul(Trans_Rotate(RandomX(-30, 30), 0, 1, 0), Trans_Rotate(RandomX(-10, 10), 1, 0, 0));
			site->Set(Foundry);
		}
		else if (!FindObject(Find_ID(WindGenerator)) && buildingsCompleted == 1) {
			immersion_npc.objective = WindGenerator;
			site = CreateObjectAbove(ConstructionSite, LandscapeWidth() / 2 - 120, baseHeight+2);
			site.MeshTransformation = Trans_Mul(Trans_Rotate(RandomX(-30, 30), 0, 1, 0), Trans_Rotate(RandomX(-10, 10), 1, 0, 0));
			site->Set(WindGenerator);
		}
		else if (!FindObject(Find_ID(Shipyard)) && buildingsCompleted == 2) {
			immersion_npc.objective = Shipyard;
			site = CreateObjectAbove(ConstructionSite, LandscapeWidth() / 2 - 230, baseHeight);
			site->Set(Shipyard);
		}
		else {
			CreateObjectAbove(Airship, LandscapeWidth() / 2 - 230, baseHeight-10);
		}
		if (site) {
			immersion_npc.goal = goal;
			effect = AddEffect("CheckConstruction", immersion_npc, 100, 5);
			effect.player = player;
		}
	}
}

//Saves lost NPC seed and progresses immersion level if lost NPC is rescued
public func OnHasTalkedToLostNPC()
{	
//	guide->AddGuideMessage("$GameCompleted$");
//	guide->ShowGuideMessage(0);
//	guide->ShowGuide();
	UpdateFoundNPC(seed);
	SetPlayerImmLevel(-1);
	SaveProfileData(player.deaths, bat_deaths, tree_chopped, player.secs_spent_in_immersion, player.secs_spent_in_achievement, -1);
	goal->Fulfill();
	return;
}

//Clears save data
private func resetProfile() {
	ResetProfile();
	return;
}

//Checks for construction completion
global func FxCheckConstructionTimer(object target, proplist effect) {
	if (FindObject(Find_ID(target.objective)))
	{
		SetPlayerImmLevel(-1);
		UpdateBuildingsCompleted();
		GameCall("UpdateProfile", -1);
		target.goal->Fulfill();
		return FX_Execute_Kill;
	}
}

//Saves player profile data and in-game variables
private func UpdateProfile(int objectiveCompleted) {
	SaveProfileData(player.deaths, bat_deaths, tree_chopped, player.secs_spent_in_immersion, player.secs_spent_in_achievement, objectiveCompleted);
}

//Game checks and updates game if target enemy dies
global func FxTargetDeathStop(object target, effect, int reason, bool  temporary)
{
	if (reason == 3 || reason == 4)
	{
		SetPlayerAchLevel(-1);
		GameCall("UpdateProfile", 1);
		target.goal->Fulfill();
		return FX_Execute_Kill;
	}
	return FX_OK;
}
global func FxTargetDeathTimer(object target)
{
	return FX_OK;
}

//Tracks how many seconds are spent in each zone
global func FxTrackPlayerTimer(object target, proplist effect, int time)
{
	var x = target->GetX();
	if (x < LandscapeWidth() / 3)
		target.secs_spent_in_immersion++;
	else if (x > LandscapeWidth() * 2 / 3)
		target.secs_spent_in_achievement++;
	return FX_OK;
}

global func FxTrackDeathsTimer(object target, proplist effect, int time)
{
	return FX_OK;
}

// Relaunches the clonk, from death or removal, increases player death count
global func FxTrackDeathsStop(object target, effect, int reason, bool  temporary)
{
	if (reason == 3 || reason == 4)
	{
		target.deaths++;
	}
	return FX_OK;
}

private func OnBatDeath() {
	bat_deaths++;
}

private func OnTreeChopped() {
	tree_chopped++;
}

//Allows player to move and become vulnerable once instructions are read at the start
private func OnFinishedTutorialIntro(int plr)
{
	// enable crew
	EnablePlrControls(plr);
	GetCrew(plr)->ClearInvincible();
}

//Index list of tutorial messages and arrow point locations
protected func OnGuideMessageShown(int plr, int index)
{
	// Show the player his clonk and the guide.
	if (index == 0)
	{
		TutArrowShowTarget(GetCrew(GetPlayerByIndex()), 225, 24);
	}
	// Show the player HUD.
	if (index == 1)
	{
		if (immersion_level == 0 && achievement_level == 0) {
			TutArrowShowGUITarget(FindObject(Find_ID(GUI_Controller_CrewBar)), 0);
			TutArrowShowGUITarget(FindObject(Find_ID(GUI_Controller_Goal)), 0);
		}
		else {
			TutArrowShowPos(LandscapeWidth()/2 + 120, LandscapeHeight()/2-10, 225);
		}
	}
	//Show npcs
	if (index == 2)
	{
		OnFinishedTutorialIntro(plr);
		TutArrowShowTarget(immersion_npc);
		TutArrowShowTarget(achievement_npc);
	}

	return;
}

protected func OnGuideMessageRemoved(int plr, int index)
{
	TutArrowClear();
	return;
}

//Updates tutorial guide once immersion NPC is talked to
public func OnHasTalkedToAerin()
{
	guide->ShowGuide();
	if (site) {
		guide->AddGuideMessage("$MsgTutorialBuild$");
		guide->ShowGuideMessage();
		guide->AddGuideMessage("$MsgTutorialBuild2$");
		TutArrowShowTarget(site);
	}
	else {
		guide->AddGuideMessage("$MsgTutorialFindNPC$");
		guide->ShowGuideMessage();
		TutArrowShowTarget(lost_npc);
	}
	guide->AddGuideMessage("$MsgTutorialHide$");
	
	return;
}

//Updates tutorial guide once achievement NPC is talked to
public func OnHasTalkedToWarra()
{
	guide->ShowGuide();
	guide->AddGuideMessage("$MsgTutorialKillNPC$");
	guide->ShowGuideMessage();
	guide->AddGuideMessage("$MsgTutorialHide$");	
	TutArrowShowTarget(target_npc);
	return;
}

//Hides the guide when player is talking to NPC
public func IsTalking()
{
	guide->HideGuide();
	return;
}