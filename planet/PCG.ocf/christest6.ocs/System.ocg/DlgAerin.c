
#appendto Dialogue

public func Dlg_Aerin_Init(object clonk)
{
	return true;
}

public func Dlg_Aerin_1(object clonk)
{
	MessageBox(Format("$DlgAerinHelp$", dlg_target->GetName()), clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_2(object clonk)
{
	MessageBox(Format("$DlgAerinHelpReply$"), clonk, clonk, nil, false, ["That sounds horrible, any way I can help?", "I don't really care."], true);
	return true;
}

public func Dlg_Aerin_3(object clonk)
{
	MessageBox("$DlgAerinSkylands$", clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_4(object clonk)
{
	MessageBox("$DlgAerinSkylandsReply$", clonk, clonk, nil, false, ["Okay I'm on it.", "Bye."], true);
	StopDialogue();
	SetDialogueProgress(5);	
	return true;
}

public func Dlg_Aerin_5(object clonk)
{
	MessageBox("$DlgAerinFindThem$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(5);
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
/*
public func Dlg_Aerin_Closed(object clonk)
{
	GameCall("OnHasTalkedToAerin", clonk);
	return true;
}
*/