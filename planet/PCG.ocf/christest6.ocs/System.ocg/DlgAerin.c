
#appendto Dialogue

public func Dlg_Aerin_Init(object clonk)
{
	if (clonk.level == 1 || GetBuildingsCompleted() == 3)
		SetDialogueProgress(21);
	else if (clonk.level >= 2)
		SetDialogueProgress(11);
	return true;
}

public func Dlg_Aerin_1(object clonk)
{
	GameCall("IsTalking", clonk);
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
	return true;
}

public func Dlg_Aerin_5(object clonk)
{
	GameCall("OnHasTalkedToAerin", clonk);
	return true;
}

public func Dlg_Aerin_6(object clonk)
{
	MessageBox("$DlgAerinFindThem$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(6);
	return true;
}

public func Dlg_Aerin_11(object clonk)
{
	GameCall("IsTalking", clonk);
	MessageBox(Format("$DlgAerinHelp2$", dlg_target->GetName()), clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_12(object clonk)
{
	MessageBox(Format("$DlgAerinHelpReply2$"), clonk, clonk, nil, false, ["I know a thing or two about buildings. I can help!", "I don't really care."], true);
	return true;
}

public func Dlg_Aerin_13(object clonk)
{
	MessageBox("$DlgAerinSkylands2$", clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_14(object clonk)
{
	MessageBox("$DlgAerinSkylandsReply2$", clonk, clonk, nil, false, ["Okay I'm on it.", "Bye."], true);
	return true;
}

public func Dlg_Aerin_15(object clonk)
{
	GameCall("OnHasTalkedToAerin", clonk);
	return true;
}

public func Dlg_Aerin_16(object clonk)
{
	MessageBox("$DlgAerinFindThem2$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(16);
	return true;
}

public func Dlg_Aerin_21(object clonk)
{
	GameCall("IsTalking", clonk);
	MessageBox("$DlgAerinHelp3$", clonk, dlg_target);
	return true;
}

public func Dlg_Aerin_22(object clonk)
{
	MessageBox(Format("$DlgAerinHelpReply3$"), clonk, clonk, nil, false, ["Okay. Don't worry I'm on it.", "I don't really care."], true);
	return true;
}

public func Dlg_Aerin_23(object clonk)
{
	GameCall("OnHasTalkedToAerin", clonk);
	return true;
}

public func Dlg_Aerin_24(object clonk)
{
	MessageBox("$DlgAerinSkylands3$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(24);
	return true;
}

/*
public func Dlg_Aerin_Closed(object clonk)
{
	GameCall("OnHasTalkedToAerin", clonk);
	return true;
}
*/