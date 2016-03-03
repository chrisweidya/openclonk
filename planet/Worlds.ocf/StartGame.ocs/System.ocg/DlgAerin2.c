
#appendto Dialogue

public func Dlg_Aerin2_Init(object clonk)
{
	return true;
}

public func Dlg_Aerin2_1(object clonk)
{
	MessageBox(Format("$DlgAerinHelp2$", dlg_target->GetName()), clonk, dlg_target);
	return true;
}

public func Dlg_Aerin2_2(object clonk)
{
	MessageBox(Format("$DlgAerinHelpReply2$"), clonk, clonk, nil, false, ["I know a thing or two about buildings. I can help!", "I don't really care."], true);
	return true;
}

public func Dlg_Aerin2_3(object clonk)
{
	MessageBox("$DlgAerinSkylands2$", clonk, dlg_target);
	return true;
}

public func Dlg_Aerin2_4(object clonk)
{
	MessageBox("$DlgAerinSkylandsReply2$", clonk, clonk, nil, false, ["Okay I'm on it.", "Bye."], true);
	StopDialogue();
	SetDialogueProgress(5);
	return true;
}

public func Dlg_Aerin2_5(object clonk)
{
	MessageBox("$DlgAerinFindThem2$", clonk, dlg_target);
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