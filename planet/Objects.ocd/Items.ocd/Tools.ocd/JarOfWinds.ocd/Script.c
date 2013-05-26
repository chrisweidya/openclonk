/*--
	Jar of Winds
	Author: MimmoO

	Collect air until you're full, then release it with a blast.

--*/

local Amount;
local MaxCap;
local sound;

func Hit()
{
	Sound("GlassHit?");
}

public func GetCarryMode(clonk) { return CARRY_BothHands; }
public func GetCarryPhase() { return 600; }

public func FxJarReloadTimer(object target, effect, int time)
{
	target->Load();
}

public func DoFullLoad()
{
	Amount = MaxCap;
	return;
}

protected func Initialize()
{
	MaxCap = 60; //Changes duration and power of the Jar
	SetR(-45);
	AddEffect("JarReload",this,100,2,this);
	sound=false;
}

func RejectUse(object clonk)
{
	return clonk->GetProcedure() == "ATTACH";
}

// used by this object
func ReadyToBeUsed(proplist data)
{
	var clonk = data.clonk;
	return !RejectUse(clonk) && !GetEffect("JarReload", this);
}

protected func ControlUse(object clonk, iX, iY)
{
	if(!GetEffect("JarReload",this))
	{
		if(!GBackLiquid())
		{
			FireWeapon(clonk, iX, iY);
			Amount=0;
			AddEffect("JarReload",this,100,1,this);
			Sound("WindCharge",false,nil,nil,1);
			sound=true;
		}
		
		return true;
	}
	else
	{
		clonk->Message("Reloading!");
		clonk->PauseUse(this, "ReadyToBeUsed", {clonk = clonk});
		return true;
	}
}

protected func Load()
{
	
	if(Amount <= MaxCap)
	{
		var R=RandomX(-25,25);
		var D=RandomX(19,50);
		var A=Random(360);
		var SX=Sin(A + R,D);
		var SY=Cos(A + R,D);
		
		if(!GBackSolid(SX,SY) && !GBackLiquid(SX,SY) && !GBackSolid(0,0) && !GBackLiquid(0,0)) //when on a random spot in front is air...
		{
			if(!sound)
			{
				Sound("WindCharge",false,nil,nil,1);
				sound=true;
			}
			Amount += 2; //Air is sucked in.
			CreateParticle("AirIntake",
				SX,SY,
				Sin(A + R,-D / 2),
				Cos(A + R,-D / 2),
				RandomX(35,80),
				RGBa(255,255,255,128)
			);
		}
		else if(GBackSolid(0,0) || GBackLiquid(0,0))
		{
			if(sound)
			ChargeSoundStop();
		}

	}
	else
	{
		RemoveEffect("JarReload",this);
		ChargeSoundStop();
		
	}
}

protected func ChargeSoundStop()
{
	Sound("WindCharge",false,nil,nil,-1);
	Sound("WindChargeStop");
	sound=false;
}

private func FireWeapon(object pClonk,iX,iY)
{
	var iAngle=Angle(0,0,iX,iY);
	
	ChargeSoundStop();
	Sound("WindGust");

	//Find Victims to push
	for(var i=10; i<32; i++)
	{
		var R = RandomX(-20,20);
		var SX = Sin(180 - iAngle + R,i);
		var SY = Cos(180 - iAngle + R,i);
		
		if(!GBackSolid(SX,SY))
		{
			CreateParticle("Air",
					SX,SY,
					Sin(180 - iAngle + (R),(Amount / 2) + 25),
					Cos(180 - iAngle + (R),(Amount / 2) + 25),
					Max(i + 30, 90) + 75,
					);
		}
	}
	
	var sinspeed = Sin(180 - iAngle + (R / 2),(Amount) + 15);
	var cosspeed = Cos(180 - iAngle + (R / 2),(Amount) + 15);
	
	if(pClonk->GetAction() != "Walk")
	{									//Makes the clonk firing it be pushed backwards a bit
		var x = pClonk->GetXDir();
		var y = pClonk->GetYDir();
		pClonk->SetXDir((x) - (sinspeed / 3));
		pClonk->SetYDir((y) - (cosspeed / 3));
	}
	
	for( var obj in FindObjects(
		Find_Or(
			Find_Distance(10,Sin(180 - iAngle,20),Cos(180 - iAngle,20)),
			Find_Distance(18,Sin(180 - iAngle,40),Cos(180 - iAngle,40)),
			Find_Distance(25,Sin(180 - iAngle,70),Cos(180 - iAngle,70))
				),
		Find_Not(Find_Category(C4D_Structure)),
		Find_Not(Find_Func("IsEnvironment")),
		Find_Not(Find_Func("NoWindjarForce")),
		Find_Layer(GetObjectLayer()), Find_NoContainer()
								)
		)
		{
		if(obj != pClonk && PathFree(pClonk->GetX(),pClonk->GetY(),obj->GetX(),obj->GetY()))
		{
		//enemys are pushed back
			var x = obj->GetXDir();
			var y = obj->GetYDir();
			obj->SetXDir((x) + sinspeed);
			obj->SetYDir((y) + cosspeed);
		}
	}
}

func IsInventorProduct() { return true; }

local Name = "$Name$";
local Description = "$Description$";
local UsageHelp = "$UsageHelp$";
local Collectible = 1;
local Rebuy = true;