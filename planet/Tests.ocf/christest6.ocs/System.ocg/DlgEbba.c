
#appendto Dialogue

public func Dlg_Ebba_Init(object clonk)
{
	return true;
}

public func Dlg_Ebba_1(object clonk)
{
	MessageBox(Format("$DlgEbbaHello$", dlg_target->GetName()), clonk, dlg_target, nil, false, ["hihi", "hihihi", "fuuu", "fuuuuuuu"], true);
	return true;
}

public func Dlg_Ebba_2(object clonk)
{
	MessageBox(Format("$DlgEbbaReply$", clonk->GetName()), clonk, clonk);
	return true;
}

public func Dlg_Ebba_3(object clonk)
{
	MessageBox("$DlgEbbaSawmill$", clonk, dlg_target);
	return true;
}

public func Dlg_Ebba_4(object clonk)
{
	MessageBox("$DlgEbbaRock$", clonk, clonk);
	StopDialogue();
	SetDialogueProgress(1);	
	return true;
}

public func Dlg_Ebba_5(object clonk)
{
	MessageBox("$DlgEbbaWellDone$", clonk, dlg_target);
	return true;
}

public func Dlg_Ebba_6(object clonk)
{
	MessageBox("$DlgEbbaFavor$", clonk, clonk);
	return true;
}

public func Dlg_Ebba_7(object clonk)
{
	MessageBox("$DlgEbbaMines$", clonk, dlg_target);
	return true;
}

public func Dlg_Ebba_8(object clonk)
{
	MessageBox("$DlgEbbaLook$", clonk, clonk);
	StopDialogue();
	SetDialogueProgress(5);
	return true;
}

public func Dlg_Ebba_Closed(object clonk)
{
	GameCall("OnHasTalkedToEbba", clonk);
	return true;
}