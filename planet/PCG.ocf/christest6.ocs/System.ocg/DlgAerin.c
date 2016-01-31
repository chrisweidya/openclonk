
#appendto Dialogue

public func Dlg_Aerin_Init(object clonk)
{
	if (clonk.level == 1)
		SetDialogueProgress(11);
	else if (clonk.level >= 2)
		SetDialogueProgress(6);
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
	MessageBox(Format("$DlgAerinHelp2$", dlg_target->GetName()), clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_7(object clonk)
{
	MessageBox(Format("$DlgAerinHelpReply2$"), clonk, clonk, nil, false, ["I know a thing or two about buildings. I can help!", "I don't really care."], true);
	return true;
}

public func Dlg_Aerin_8(object clonk)
{
	MessageBox("$DlgAerinSkylands2$", clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_9(object clonk)
{
	MessageBox("$DlgAerinSkylandsReply2$", clonk, clonk, nil, false, ["Okay I'm on it.", "Bye."], true);
	StopDialogue();
	SetDialogueProgress(10);
	return true;
}

public func Dlg_Aerin_10(object clonk)
{
	MessageBox("$DlgAerinFindThem2$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(10);
	return true;
}

public func Dlg_Aerin_11(object clonk)
{
	MessageBox("$DlgAerinHelp3$", clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_12(object clonk)
{
	MessageBox(Format("$DlgAerinHelpReply3$"), clonk, clonk, nil, false, ["Okay. Don't worry I'm on it.", "I don't really care."], true);
	return true;
}

public func Dlg_Aerin_13(object clonk)
{
	MessageBox("$DlgAerinSkylands3$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(13);
	return true;
}

/*
public func Dlg_Aerin_Closed(object clonk)
{
	GameCall("OnHasTalkedToAerin", clonk);
	return true;
}
*/