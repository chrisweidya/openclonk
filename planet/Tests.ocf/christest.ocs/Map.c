#include Library_Map

func InitializeMap(proplist map)
{
	// Create a big map
	Resize(150, 150);
	// Draw earth
	DrawRegularGround();
	// Draw some resources into the ground
	DrawWaterVeins(3, [0, map.Hgt / 3, map.Wdt, map.Hgt * 2 / 3]);
	DrawCoal(6);
	DrawFirestone(4);
	DrawRock(15);
	DrawOre(4);
	DrawGold(2 * GetStartupPlayerCount()); // amount of gold depends on player count!
	// Make sure liquids don't border tunnel or sky sideways
	FixLiquidBorders();
	// Done. Use this map.
	return true;
}