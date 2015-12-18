/*--
	Catapult
	Author: Ringwaul
	
	Tosses objects farther than a clonk can. Requires no fuel.
--*/

#include Library_ElevatorControl

local aim_anim;
local turn_anim;
local olddir;
local dir;
local clonkmesh;

public func IsVehicle() { return true; }
public func IsArmoryProduct() { return true; }
public func FitsInDoubleElevator() { return true; }

protected func Initialize()
{
	dir = 1;
	SetAction("Roll");
	olddir = 1;
	aim_anim =  PlayAnimation("ArmPosition", 1,  Anim_Const(0),Anim_Const(1000));
	turn_anim = PlayAnimation("TurnRight", 5, Anim_Const(GetAnimationLength("TurnRight")), Anim_Const(1000));
}

//some left-overs from Lorry script. Not sure of it's purpose...
protected func ContactLeft()
{
	if(Stuck() && !Random(5)) SetRDir(RandomX(-7, +7));
}
protected func ContactRight()
{
	if(Stuck() && !Random(5)) SetRDir(RandomX(-7, +7));
}

/* ---- CONTROLS ---- */

//Activate turn animations
func ControlLeft(object clonk)
{
	dir = 0;
	if(dir != olddir)
	{
		olddir = dir;

		//if the animation is playing for the other direction, turn back from where it already is in the animation
		var animstart = 0;
		if(GetAnimationPosition(turn_anim) != GetAnimationLength("TurnRight"))
		{
			animstart = GetAnimationLength("TurnRight") - GetAnimationPosition(turn_anim);
		}

		StopAnimation(turn_anim);
		turn_anim = PlayAnimation("TurnLeft", 5, Anim_Linear(animstart, 0, GetAnimationLength("TurnLeft"), Max(36 - (animstart * 204617 / 10000000), 1), ANIM_Hold), Anim_Const(1000));
	}
}

func ControlRight(object clonk)
{
	dir = 1;
	if(dir != olddir)
	{
		olddir = dir;

		//if the animation is playing for the other direction, turn back from where it already is in the animation
		var animstart = 0;
		if(GetAnimationPosition(turn_anim) != GetAnimationLength("TurnLeft"))
		{
			animstart = GetAnimationLength("TurnLeft") - GetAnimationPosition(turn_anim);
		}

		StopAnimation(turn_anim);
		turn_anim = PlayAnimation("TurnRight", 5, Anim_Linear(animstart, 0, GetAnimationLength("TurnRight"), Max(36 - (animstart * 204617 / 10000000), 1), ANIM_Hold), Anim_Const(1000));
	}
}

public func ControlUseStart(object clonk)
{
	return true;
}

public func HoldingEnabled() { return true; }


public func ControlUseHolding(object clonk, int x, int y)
{
	ArmAnimation(x, y);
	ShowTrajectory(DefinePower(x, y));
	return true;
}

public func DefinePower(int x, int y)
{
	var angle = Angle(0, 0, x, y);
	
	//balancing stats
	var padding = 20;

	var x2 = Sin(padding, angle);
	var y2 = -Cos(padding, angle);
	var power = Distance(x2, y2, x2 + x, y2 + y) - padding;
	power = BoundBy(power, 20, 100);
	return power;
}

public func ArmAnimation(int x, int y)
{
	var power = DefinePower(x, y);
	SetAnimationPosition(aim_anim, Anim_Const(759 - (power * 759 / 100)));
}

public func ShowTrajectory(int power)
{
	var exit = GetProjectileExit();
	var x = GetX() + exit[0];
	var y = GetY() + exit[1];
	var angle = exit[2] + GetR();
	var xdir = Sin(angle, power);
	var ydir = -Cos(angle, power);
	Trajectory->Create(this, x, y, xdir, ydir);
	return;
}

public func ControlUseStop(object clonk, int x, int y)
{
	DoFire(clonk, DefinePower(x,y));
}

public func ContainedUse(object clonk, int x, int y)
{
	DoFire(clonk, 70);
}

protected func DoFire(object clonk, int power)
{
	//Fire the catapult!
//	PlayAnimation("Launch", 5, Anim_Linear(0,0, GetAnimationLength("Launch"), 10, ANIM_Remove), Anim_Const(1000));
	aim_anim = PlayAnimation("ArmPosition", 1, Anim_Linear(GetAnimationPosition(aim_anim),0, GetAnimationLength("ArmPosition"), 3, ANIM_Hold), Anim_Const(1000));

	//Sound
	Sound("Objects::Catapult_Launch");

	var projectile = nil;
	if (Contents(0))
		projectile = Contents(0); //Is clonk sitting in the catapult? Then (s)he shall be the projectile!
	else
		if(clonk->GetHandItem(0)) 
			projectile = clonk->GetHandItem(0); //otherwise, fire what is in the clonk's hand
	if (projectile)
	{
		//finding the spot of the catapult's arm depending on rotation
		var exit = GetProjectileExit();
		var x = exit[0];
		var y = exit[1];
		var angle = exit[2] + GetR();

		projectile->Exit();
		//Put the ammo at the catapult's arm
		projectile->SetPosition(GetX() + x, GetY() + y);

		//Launch the clonk!
		if(projectile->~IsClonk())
		{
			CatapultDismount(projectile);
			projectile->SetAction("Tumble");
			
			// Special behavior for Clonks: make sure the Clonk can't shoot itself into solid material.
			if (projectile->Stuck())
			{
				// First, try to just put the Clonk a few pixels lower - might still look okay in some situations.
				for (var i = 0; i <= 4; ++i)
				{
					projectile->SetPosition(projectile->GetX(), projectile->GetY() + 2);
					if (!projectile->Stuck()) break;
				}
				// Then as a safeguard, just place the Clonk at the catapult's feet and do nothing.
				if (projectile->Stuck())
				{
					projectile->SetPosition(GetX(), GetY());
					// Still stuck? Then we don't actually care if stuck here or at the end of the arm.
					if (projectile->Stuck())
					{
						// Go back to normal shooting position.
						projectile->SetPosition(GetX() + x, GetY() + y);
					}
					else
					{
						// We set the Clonk back down on the ground. This is not a normal shot.
						angle = 0;
						power = 20;
					}
				}
			}
		}

		//Catapult is facing left or right?
		projectile->SetVelocity(angle + GetR(), power);
	}
	
	// Remove trajectory display.
	Trajectory->Remove(this);
}

private func GetProjectileExit()
{
	var xdir = 1;
	if (dir == 0) 
		xdir = -1;
	var x = 8 * xdir;
	var y = -28;
	var angle = 45 * xdir;
	return [x, y, angle];
}

public func ActivateEntrance(object clonk)
{
	var cnt = ObjectCount(Find_Container(this), Find_OCF(OCF_CrewMember));
	if(cnt > 0)
		if(clonk->Contained() == this)
		{
			CatapultDismount(clonk);
			clonk->Exit();
			return;
		}
		else
			return;

	if(cnt == 0)
	{
		SetAnimationPosition(aim_anim, Anim_Const(150));
		clonk->Enter(this);
		SetOwner(clonk->GetController());
		clonkmesh = AttachMesh(clonk,"shot","skeleton_body",Trans_Mul(Trans_Rotate(180, 1, 0, 0), Trans_Translate(-3000, 1000, 0)),AM_DrawBefore);
		clonk->PlayAnimation("CatapultSit", CLONK_ANIM_SLOT_Movement, Anim_Const(0), Anim_Const(1000));
		ShowTrajectory(70);
	}
}

public func CatapultDismount(object clonk)
{
	clonk->StopAnimation(clonk->GetRootAnimation(15));
	DetachMesh(clonkmesh);
	clonkmesh = nil;
	return true;
}

local ActMap = {
Roll = {
	Prototype = Action,
	Name = "Roll",
	Procedure = DFA_NONE,
	Directions = 1,
	FlipDir = 1,
	Length = 50,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 22,
	Hgt = 16,
	NextAction = "Roll",
},
};
func Definition(def)
{
	SetProperty("PictureTransformation",Trans_Mul(Trans_Translate(6000,0,0),Trans_Rotate(-20,1,0,0),Trans_Rotate(35,0,1,0),Trans_Scale(1350)),def);
}

local Name = "$Name$";
local Description = "$Description$";
local Touchable = 1;
local Rebuy = true;
