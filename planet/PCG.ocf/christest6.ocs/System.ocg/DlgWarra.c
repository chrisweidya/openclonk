
#appendto Dialogue

public func Dlg_Warra_Init(object clonk)
{
	if (clonk.level > 0)
		SetDialogueProgress(11);
	return true;
}

public func Dlg_Warra_1(object clonk)
{
	GameCall("IsTalking", clonk);
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
	GameCall("OnHasTalkedToWarra", clonk);
	return true;
}

public func Dlg_Warra_4(object clonk)
{
	MessageBox("$DlgWarraKill$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(4);
	return true;
}

public func Dlg_Warra_11(object clonk)
{
	GameCall("IsTalking", clonk);
	MessageBox(Format("$DlgWarraHelp2$", dlg_target->GetName()), clonk, dlg_target);
	return true;
}

public func Dlg_Warra_12(object clonk)
{
	MessageBox(Format("$DlgWarraHelpReply2$"), clonk, clonk, nil, false, ["I'm going to help the other guy.", "Killing is my specialty."], true);	
	return true;
}

public func Dlg_Warra_13(object clonk)
{
	GameCall("OnHasTalkedToWarra", clonk);
	return true;
}

public func Dlg_Warra_14(object clonk)
{
	MessageBox("$DlgWarraKill2$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(14);
	return true;
}

/*
public func Dlg_Warra_Closed(object clonk)
{
	GameCall("OnHasTalkedToWarra", clonk);
	return true;
}
*/