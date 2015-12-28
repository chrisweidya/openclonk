
#appendto Dialogue

public func Dlg_Aerin_Init(object clonk)
{
	return true;
}

public func Dlg_Aerin_1(object clonk)
{
	MessageBox(Format("$DlgAerinHello$", dlg_target->GetName()), clonk, dlg_target, nil, false, ["hihi", "hihihi", "fuuu", "fuuuuuuu"], true);
	return true;
}

public func Dlg_Aerin_2(object clonk)
{
	MessageBox(Format("$DlgAerinReply$", clonk->GetName()), clonk, clonk);
	return true;
}

public func Dlg_Aerin_3(object clonk)
{
	MessageBox("$DlgAerinSawmill$", clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_4(object clonk)
{
	MessageBox("$DlgAerinRock$", clonk, clonk);
	StopDialogue();
	SetDialogueProgress(1);	
	return true;
}

public func Dlg_Aerin_5(object clonk)
{
	MessageBox("$DlgAerinWellDone$", clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_6(object clonk)
{
	MessageBox("$DlgAerinFavor$", clonk, clonk);
	return true;
}

public func Dlg_Aerin_7(object clonk)
{
	MessageBox("$DlgAerinMines$", clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_8(object clonk)
{
	MessageBox("$DlgAerinLook$", clonk, clonk);
	StopDialogue();
	SetDialogueProgress(5);
	return true;
}

public func Dlg_Aerin_Closed(object clonk)
{
	GameCall("OnHasTalkedToAerin", clonk);
	return true;
}