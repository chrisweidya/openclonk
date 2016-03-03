
#appendto Dialogue

public func Dlg_FoundNPC_Init(object clonk)
{

	AddEffect("NewtonHammering", clonk, 1, 30, this);
}

public func Dlg_FoundNPC_1(object clonk)
{
	MessageBox(Format("$DlgFoundNPCSaved$", dlg_target->GetName()), clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(1);
	return true;
}

func FxNewtonHammeringTimer(object c, proplist fx, int time)
{
	if (FrameCounter() < this.anim_continue_frame || c.has_sequence) { fx.phase = false; return FX_OK; }
	var len = c->GetAnimationLength("StrikePickaxe");
	var a = len * 70 / 100;
	var b = len * 94 / 100;
	if (fx.phase = !fx.phase)
	{
			// No movement: Swing hammer
			this.anim = c->PlayAnimation("StrikePickaxe", 10, Anim_Linear(a, a, b, 30, ANIM_Remove), Anim_Const(1000));
	}
	else
	{
		// Hammer backswing
		this.anim = c->PlayAnimation("StrikePickaxe", 10, Anim_Linear(b, b, a, 30, ANIM_Remove), Anim_Const(1000));
		c->Sound("Objects::Pickaxe::Clang?");
		var x = (c->GetDir() * 2 - 1) * 9;
		var y = -16;
		c->CreateParticle("Dust", x, y, PV_Random(-10, 10), PV_Random(-10, 20), PV_Random(10, 20), new Particles_Dust(){ R = 120, G = 100, B = 80 }, 10);
		if (Random(3)) c->CreateParticle("StarSpark", x, y, PV_Random(-5, 5), PV_Random(-5, 5), PV_Random(10, 20), Particles_Glimmer(), Random(10) + 3);
	}
	return FX_OK;
}

/*
public func Dlg_Aerin_Closed(object clonk)
{
	GameCall("OnHasTalkedToAerin", clonk);
	return true;
}
*/