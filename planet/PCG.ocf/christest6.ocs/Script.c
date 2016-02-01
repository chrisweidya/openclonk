local seed;
local baseHeight;
local lost_npc;
local target_npc;
local site;
local player;
local guide;
local goal;

func Initialize()
{	
	//resetProfile();
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
	clonk->CreateContents(TeleportScroll);
	clonk->CreateContents(Sword);
	clonk->SetPosition(LandscapeWidth()/2 + 100, baseHeight - 20);	
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
	var hp = 40000;
	hp += achievement_level * 15000;
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


private func InitConstructionGoal(int level) {
	var effect;
	var buildingsCompleted = GetBuildingsCompleted();
	if (level > 1) {
		if (!FindObject(Find_ID(Foundry)) && buildingsCompleted == 0) {
			immersion_npc.objective = Foundry;
			site = CreateObjectAbove(ConstructionSite, 400, baseHeight+2);
			site.MeshTransformation = Trans_Mul(Trans_Rotate(RandomX(-30, 30), 0, 1, 0), Trans_Rotate(RandomX(-10, 10), 1, 0, 0));
			site->Set(Foundry);
		}
		else if (!FindObject(Find_ID(WindGenerator)) && buildingsCompleted == 1) {
			immersion_npc.objective = WindGenerator;
			site = CreateObjectAbove(ConstructionSite, 360, baseHeight+2);
			site.MeshTransformation = Trans_Mul(Trans_Rotate(RandomX(-30, 30), 0, 1, 0), Trans_Rotate(RandomX(-10, 10), 1, 0, 0));
			site->Set(WindGenerator);
		}
		else if (!FindObject(Find_ID(Shipyard)) && buildingsCompleted == 2) {
			immersion_npc.objective = Shipyard;
			site = CreateObjectAbove(ConstructionSite, 250, baseHeight);
			site->Set(Shipyard);
		}
		else {
			CreateObjectAbove(Airship, 250, baseHeight-10);
		}
		if (site) {
			immersion_npc.goal = goal;
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
	SetPlayerImmLevel(-1);
	goal->Fulfill();
	return;
}

private func resetProfile() {
	ResetProfile();
	return;
}


global func FxCheckConstructionTimer(object target, proplist effect) {
	if (FindObject(Find_ID(target.objective)))
	{
		SetPlayerImmLevel(-1);
		UpdateBuildingsCompleted();
		target.goal->Fulfill();
		return FX_Execute_Kill;
	}
}

global func FxTargetDeathStop(object target, effect, int reason, bool  temporary)
{
	if (reason == 3 || reason == 4)
	{
		SetPlayerAchLevel(-1);
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

