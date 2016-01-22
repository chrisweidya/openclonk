
#appendto Dialogue

public func Dlg_Warra_Init(object clonk)
{
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
	StopDialogue();
	SetDialogueProgress(3);
	return true;
}

public func Dlg_Warra_3(object clonk)
{
	MessageBox("$DlgWarraKill$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(3);
	return true;
}

