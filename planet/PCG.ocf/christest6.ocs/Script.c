local seed;
local baseHeight;
local immersion_npc;
local lost_npc;
local target_npc;
local site;
local player;
local guide;
local goal;

func Initialize()
{	
	resetProfile();
	var groundOffset = GetMapDataFromPlayer();
	baseHeight = (LandscapeHeight() / 2 + groundOffset * LandscapeHeight() / 8);
	seed = GetSeed();
	InitAI();
	InitGoal();
	
	return true;
}

protected func InitGoal()
{
	goal = CreateObject(Goal_PCG);
	goal.Name = "$MsgGoalName$";
	goal.Description = "$MsgGoalDescription$";
	target_npc.goal = goal;
	var effect = AddEffect("TargetDeath", target_npc, 100, 10);
	InitBuildQuest();
}

protected func InitializePlayer(int plr)
{
	// Position player's clonk.
//	SetPlayerZoomByViewRange(plr, 400, 0, PLRZOOM_LimitMin);
	player = plr;
	var clonk = GetCrew(plr);
	clonk->CreateContents(Shovel);
	clonk->CreateContents(GrappleBow);
	clonk->CreateContents(Sword);
	clonk->CreateContents(TeleportScroll);
	clonk->SetPosition(LandscapeWidth()/2, baseHeight - 20);	
	/*
	for (var structure in FindObjects(Find_Or(Find_Category(C4D_Structure), Find_Func("IsFlagpole"))))
		structure->SetOwner(plr);
	var site = FindObject(Find_ID(ConstructionSite));
	site->SetOwner(plr);
	
	*/

//	guide = CreateObject(PCGGuide, 0, 0, plr);
//	guide->HideGuide();
//	var effect = AddEffect("ClonkRestore", clonk, 100, 10);
//	effect.to_x = 300;
//	effect.to_y = 374;
}

// Gamecall from goals, set next mission.
protected func OnGoalsFulfilled()
{	
	SetNextMission("PCG.ocf\\christest6.ocs", "$MsgNext$", "$MsgNextDesc$");
	return false;
}

private func InitAI()
{
	
//	InitImmersionNPC(seed);
//	InitFoundNPC();
//	InitLostNPC(seed);
//	InitTargetNPC(seed);
	
	InitEnemyHealth();
	return;
}

private func InitBuildQuest() {
	var immersion_level = GetPlayerImmLevel();
	InitConstructionGoal(immersion_level);
}

private func InitEnemyHealth() {
	var fx;
	for (var npc in FindObjects(Find_ID(Clonk), Find_Owner(NO_OWNER))) {
		if (fx = AI->GetAI(npc))
		{
			if (npc.isTarget)
				target_npc = npc;
			fx.weapon = fx.target = nil;
			AI->BindInventory(npc);
			npc->DoEnergy(10000);
			npc->AddEnergyBar();
		}
		if (npc->GetName() == "Aerin")
			immersion_npc = npc;
	}
}


private func InitConstructionGoal(int index) {
	var effect;
	if (index == 2) {
		if (!FindObject(Find_ID(Sawmill))) {
			immersion_npc.objective = Sawmill;
			immersion_npc.goal = goal;
			site = CreateObjectAbove(ConstructionSite, 300, baseHeight);
			site.MeshTransformation = Trans_Mul(Trans_Rotate(RandomX(-30, 30), 0, 1, 0), Trans_Rotate(RandomX(-10, 10), 1, 0, 0));
			site->Set(Sawmill);
			effect = AddEffect("CheckConstruction", immersion_npc, 100, 5);
			effect.player = player;
		}
	}
}


public func OnHasTalkedToLostNPC()
{	
//	guide->AddGuideMessage("$GameCompleted$");
//	guide->ShowGuideMessage(0);
//	guide->ShowGuide();
	UpdateFoundNPC(seed, player);
	goal->Fulfill();
	return;
}

private func resetProfile() {
	ResetProfile();
	return;
}

public func EncounterOutpost(object enemy, object player)
{
	Dialogue->MessageBoxAll("$MsgEncounterOutpost$", enemy, true);
	return true;
}


global func FxCheckConstructionTimer(object target, proplist effect) {
	if (FindObject(Find_ID(target.objective)))
	{
		target.goal->Fulfill();
		return FX_Execute_Kill;
	}
}

global func FxTargetDeathStop(object target, effect, int reason, bool  temporary)
{
	if (reason == 3 || reason == 4)
	{
		target.goal->Fulfill();
		return FX_Execute_Kill;
	}
	return FX_OK;
}
global func FxTargetDeathTimer(object target)
{
	return FX_OK;
}

/*-- Clonk restoring --*/

global func FxClonkRestoreTimer(object target, proplist effect, int time)
{
	// Respawn clonk to new location if reached certain position.
	return FX_OK;
}

// Relaunches the clonk, from death or removal.
global func FxClonkRestoreStop(object target, effect, int reason, bool  temporary)
{
	if (reason == 3 || reason == 4)
	{
		var restorer = CreateObjectAbove(ObjectRestorer, 0, 0, NO_OWNER);
		var x = BoundBy(target->GetX(), 0, LandscapeWidth());
		var y = BoundBy(target->GetY(), 0, LandscapeHeight());
		restorer->SetPosition(x, y);
		var to_x = effect.to_x;
		var to_y = effect.to_y;
		// Respawn new clonk.
		var plr = target->GetOwner();
		var clonk = CreateObjectAbove(Clonk, 0, 0, plr);
		clonk->GrabObjectInfo(target);
		Rule_BaseRespawn->TransferInventory(target, clonk);
		SetCursor(plr, clonk);
		clonk->DoEnergy(100000);
		restorer->SetRestoreObject(clonk, nil, to_x, to_y, 0, "ClonkRestore");
	}
	return FX_OK;
}