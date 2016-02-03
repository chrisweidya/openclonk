
#appendto Dialogue

public func Dlg_Warra_Init(object clonk)
{
	if (clonk.level > 0)
		SetDialogueProgress(4);
	return true;
}

public func Dlg_Warra_1(object clonk)
{
	MessageBox(Format("$DlgWarraHelp$", dlg_target->GetName()), clonk, dlg_target);
	return true;
}

public func Dlg_Warra_2(object clonk)
{
	MessageBox(Format("$DlgWarraHelpReply$"), clonk, clonk, nil, false, ["How could you ignore him? He needs help!", "I prefer a challenge anyway."], true);
	return true;
}

public func Dlg_Warra_3(object clonk)
{
	MessageBox("$DlgWarraKill$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(3);
	return true;
}

public func Dlg_Warra_4(object clonk)
{
	MessageBox(Format("$DlgWarraHelp2$", dlg_target->GetName()), clonk, dlg_target);
	return true;
}

public func Dlg_Warra_5(object clonk)
{
	MessageBox(Format("$DlgWarraHelpReply2$"), clonk, clonk, nil, false, ["I'm going to help the other guy.", "Killing is my specialty."], true);
	StopDialogue();
	SetDialogueProgress(6);
	return true;
}

public func Dlg_Warra_6(object clonk)
{
	MessageBox("$DlgWarraKill2$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(6);
	return true;
}