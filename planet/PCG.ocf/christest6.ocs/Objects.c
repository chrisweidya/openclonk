/* Automatically created objects file */


func InitializeObjects()
{
	var groundOffset = GetMapDataFromPlayer();
	var baseHeight = (LandscapeHeight() / 2 + groundOffset * LandscapeHeight() / 8);

	var respawn = CreateObject(Rule_BaseRespawn);
	respawn->SetInventoryTransfer(true);
	respawn->SetFreeCrew(true);

	var flagpole = CreateObjectAbove(Flagpole, LandscapeWidth() / 2, baseHeight);
	flagpole->SetNeutral(true);

	CreateObjectAbove(WoodenCabin, LandscapeWidth() / 2 - 120, baseHeight);

	return true;
	
}
