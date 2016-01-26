
#appendto Dialogue

public func Dlg_Warra2_Init(object clonk)
{
	return true;
}

public func Dlg_Warra2_1(object clonk)
{
	MessageBox(Format("$DlgWarraHelp2$", dlg_target->GetName()), clonk, dlg_target);
	return true;
}

public func Dlg_Warra2_2(object clonk)
{
	MessageBox(Format("$DlgWarraHelpReply2$"), clonk, clonk, nil, false, ["I'm going to help the other guy.", "Killing is my specialty."], true);
	StopDialogue();
	SetDialogueProgress(3);
	return true;
}

public func Dlg_Warra2_3(object clonk)
{
	MessageBox("$DlgWarraKill2$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(3);
	return true;
}

