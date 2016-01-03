
#appendto Dialogue

public func Dlg_LostNPC_Init(object clonk)
{
	return true;
}

public func Dlg_LostNPC_1(object clonk)
{
	MessageBox(Format("$DlgLostNPCPlease$", dlg_target->GetName()), clonk);
	return true;
}

public func Dlg_LostNPC_2(object clonk)
{
	MessageBox(Format("$DlgLostNPCPleaseReply$", clonk->GetName()), clonk, clonk);
	return true;
}

public func Dlg_LostNPC_3(object clonk)
{
	MessageBox("$DlgLostNPCThanks$", clonk, dlg_target);
	StopDialogue();
	SetDialogueProgress(3);
	return true;
}


public func Dlg_LostNPC_Closed(object clonk)
{
	GameCall("OnHasTalkedToLostNPC", clonk);
	return true;
}
