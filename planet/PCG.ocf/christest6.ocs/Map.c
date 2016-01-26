#include Library_Map

func InitializeMap(proplist map)
{
	Resize(120, 160);
	var seed = GetRandomSeed();
	Log("ssed%v", seed);
	var groundHeightOffset = GetMapDataFromPlayer() * map.Hgt / 8;
	var immersion_level = GetPlayerImmLevel();
	var achievement_level = GetPlayerAchLevel();

	var ground = draw_ground(seed, map, groundHeightOffset);
//	var coal = draw_mat(seed, "Coal", ground, 30, 5, 3, 1);
	
	var largeTunnels = draw_mat(seed, "Tunnel", ground, 40, 8, 3, 1);

	var skyLand = draw_sky(seed, map, groundHeightOffset);

	if (immersion_level > 1) {
		draw_mat(seed + 2, "^Everrock", skyLand, 30, 8, 2, 1);
	}
	if (immersion_level > 0) {
		draw_mat(seed + 1, "^Rock", skyLand, 30, 6, 2, 1);
		draw_mat(seed + 1, "^Ore", skyLand, 30, 7, 2, 1);
	}
	if (achievement_level > 0) {
		var fireStone = draw_mat(seed, "Firestone", ground, 30, 8, 2, 1);
	}
	
	var sky = draw_mat(seed, "Sky", skyLand, 50, 7, 3, 2);

	var platform = draw_platform(map, groundHeightOffset);
	return true;
}

func draw_platform(proplist map, int groundHeightOffset) {
	var platform = { Algo = MAPALGO_Rect, X = map.Wdt/6, Y = map.Hgt / 2 + (groundHeightOffset), Wdt = 2*map.Wdt/3, Hgt = 2 };
	var clearArea = { Algo = MAPALGO_Rect, X = map.Wdt / 4 - 10, Y = map.Hgt / 2 + (groundHeightOffset) - 15, Wdt = map.Wdt / 2 + 20, Hgt = 15 };
//	var jumbled_clearing = { Algo = MAPALGO_Turbulence, Amplitude = 10, Scale = 10, Op = clearArea };
	
//	Draw("Sky", jumbled_clearing);
	Draw("Sky", clearArea);
	Draw("BrickSoft", platform);
}

func draw_ground(int seed, proplist map, int groundHeightOffset) {
	var ground = { Algo = MAPALGO_Rect, X = 0, Y = map.Hgt / 2 + (groundHeightOffset), 
		Wdt = map.Wdt, Hgt = map.Hgt / 2 -  (groundHeightOffset)};
	Draw("Earth", ground);

	var ground2 = { Algo = MAPALGO_SimplexNoise, Seed = (seed + 1), Ratio = 50, Octave = 8, Persistence = 5, Scale = 3, Wdt = 1, Hgt = 1 };
	var result = { Algo = MAPALGO_And, Op = [ground2, ground] };
	Draw("Earth-earth_spongy", result);
	return ground;
}

func draw_sky(int seed, proplist map, int groundHeightOffset) {
	var skyLand = { Algo = MAPALGO_Rect, X = 0, Y = 0,
		Wdt = map.Wdt, Hgt = map.Hgt / 2 + (groundHeightOffset) };
	Draw("^Sand", skyLand);

//	var ground2 = { Algo = MAPALGO_SimplexNoise, Seed = (seed + 1), Ratio = 50, Octave = 8, Persistence = 5, Scale = 3, Wdt = 1, Hgt = 1 };
//	var result = { Algo = MAPALGO_And, Op = [ground2, ground] };
//	Draw("Earth-earth_spongy", result);
	return skyLand;
}

func draw_mat(int seed, string type, proplist area, int ratio, int octave, int scale, int width) {
	var mat = { Algo = MAPALGO_SimplexNoise, Seed = seed+1, Ratio = ratio, Octave = octave, Persistence = 5, Scale = scale, Wdt = width, Hgt = 1 };
	var result = { Algo = MAPALGO_And, Op = [mat, area] };
	Draw(type, result);
	return result;
}