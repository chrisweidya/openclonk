
#appendto Dialogue

public func Dlg_Aunt_Init(object clonk)
{
	return true;
}

public func Dlg_Aunt_1(object clonk)
{
	MessageBox(Format("$DlgAuntHello$", dlg_target->GetName()), clonk, dlg_target, nil, false, ["hihi", "hihihi", "fuuu", "fuuuuuuu"]);
	return true;
}

public func Dlg_Aunt_2(object clonk)
{
	MessageBox(Format("$DlgAuntReply$", clonk->GetName()), clonk, clonk);
	return true;
}

public func Dlg_Aunt_3(object clonk)
{
	MessageBox("$DlgAuntSawmill$", clonk, dlg_target, nil, false, ["hihi", "hihihi", "fuuu", "fuuuuuuu"], true);
	return true;
}

public func Dlg_Aunt_4(object clonk)
{
	MessageBox("$DlgAuntRock$", clonk, clonk);
	StopDialogue();
	SetDialogueProgress(1);	
	return true;
}

public func Dlg_Aunt_5(object clonk)
{
	MessageBox("$DlgAuntWellDone$", clonk, dlg_target);
	return true;
}

public func Dlg_Aunt_6(object clonk)
{
	MessageBox("$DlgAuntFavor$", clonk, clonk);
	return true;
}

public func Dlg_Aunt_7(object clonk)
{
	MessageBox("$DlgAuntMines$", clonk, dlg_target);
	return true;
}

public func Dlg_Aunt_8(object clonk)
{
	MessageBox("$DlgAuntLook$", clonk, clonk);
	StopDialogue();
	SetDialogueProgress(5);
	return true;
}

public func Dlg_Aunt_Closed(object clonk)
{
	GameCall("OnHasTalkedToAunt", clonk);
	return true;
}