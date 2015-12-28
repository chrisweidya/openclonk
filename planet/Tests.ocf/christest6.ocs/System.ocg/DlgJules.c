
#appendto Dialogue

public func Dlg_Jules_Init(object clonk)
{
	return true;
}

public func Dlg_Jules_1(object clonk)
{
	MessageBox(Format("$DlgJulesHello$", dlg_target->GetName()), clonk, dlg_target, nil, false, ["hihi", "hihihi", "fuuu", "fuuuuuuu"], true);
	return true;
}

public func Dlg_Jules_2(object clonk)
{
	MessageBox(Format("$DlgJulesReply$", clonk->GetName()), clonk, clonk);
	return true;
}

public func Dlg_Jules_3(object clonk)
{
	MessageBox("$DlgJulesSawmill$", clonk, dlg_target);
	return true;
}

public func Dlg_Jules_4(object clonk)
{
	MessageBox("$DlgJulesRock$", clonk, clonk);
	StopDialogue();
	SetDialogueProgress(1);	
	return true;
}

public func Dlg_Jules_5(object clonk)
{
	MessageBox("$DlgJulesWellDone$", clonk, dlg_target);
	return true;
}

public func Dlg_Jules_6(object clonk)
{
	MessageBox("$DlgJulesFavor$", clonk, clonk);
	return true;
}

public func Dlg_Jules_7(object clonk)
{
	MessageBox("$DlgJulesMines$", clonk, dlg_target);
	return true;
}

public func Dlg_Jules_8(object clonk)
{
	MessageBox("$DlgJulesLook$", clonk, clonk);
	StopDialogue();
	SetDialogueProgress(5);
	return true;
}

public func Dlg_Jules_Closed(object clonk)
{
	GameCall("OnHasTalkedToJules", clonk);
	return true;
}