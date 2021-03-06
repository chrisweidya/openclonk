// Shows and hides the PCG guide if the [H] button is pressed.

global func PlayerControl(int plr, int ctrl, id spec_id, int x, int y, int strength, bool repeat, bool release)
{
	if (ctrl != CON_PCGGuide)
		return _inherited(plr, ctrl, spec_id, x, y, strength, repeat, release, ...);
	// Find the guide object for this player.
	var guide = FindObject(Find_ID(TutorialGuide), Find_Owner(plr));
	if (!guide)
		return;
	// If hidden, show the guide. If shown, hide the guide.
	if (guide->IsHidden())
		guide->ShowGuide();
	else
		guide->HideGuide();
	return;
}