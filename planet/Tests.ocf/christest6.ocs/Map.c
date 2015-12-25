#include Library_Map

func InitializeMap(proplist map)
{
	//GET PARAMETERS FROM PROFILE
	var seed = 123123;
	var groundHeightOffset = GetMapDataFromPlayer();
	var ground = draw_ground(seed, map, groundHeightOffset);
	var coal = draw_mat(seed, "Coal", ground, 30, 5, 3);
	var fireStone = draw_mat(seed, "Firestone", ground, 30, 8, 2);
	var largeTunnels = draw_mat(seed, "Tunnel", ground, 40, 8, 3);

	var sky = draw_sky(seed, map, groundHeightOffset);
	var skyLand = draw_mat(seed, "Sand", sky, 50, 8, 3);

	var platform = draw_platform(map, groundHeightOffset);
	return true;
}

func draw_platform(proplist map, int groundHeightOffset) {
	var platform = { Algo = MAPALGO_Rect, X = map.Wdt/4, Y = map.Hgt / 2 + (groundHeightOffset * map.Hgt / 8), Wdt = map.Wdt/2, Hgt = 5 };
	var clearArea = { Algo = MAPALGO_Rect, X = map.Wdt / 4 - 10, Y = map.Hgt / 2 + (groundHeightOffset * map.Hgt / 8) - 20, Wdt = map.Wdt / 2 + 20, Hgt = 20 };
	var jumbled_clearing = { Algo = MAPALGO_Turbulence, Amplitude = 10, Scale = 10, Op = clearArea };
	
	Draw("Sky", jumbled_clearing);
	Draw("Sky", clearArea);
	Draw("Brick", platform);
}

func draw_ground(int seed, proplist map, int groundHeightOffset) {
	var ground = { Algo = MAPALGO_Rect, X = 0, Y = map.Hgt / 2 + (groundHeightOffset * map.Hgt / 8), 
		Wdt = map.Wdt, Hgt = map.Hgt / 2 -  (groundHeightOffset * map.Hgt / 8)};
	Draw("Earth", ground);

	var ground2 = { Algo = MAPALGO_SimplexNoise, Seed = (seed + 1), Ratio = 50, Octave = 8, Persistence = 5, Scale = 3, Wdt = 1, Hgt = 1 };
	var result = { Algo = MAPALGO_And, Op = [ground2, ground] };
	Draw("Earth-earth_spongy", result);
	return ground;
}

func draw_sky(int seed, proplist map, int groundHeightOffset) {
	var sky = { Algo = MAPALGO_Rect, X = 0, Y = 0,
		Wdt = map.Wdt, Hgt = map.Hgt / 2 + (groundHeightOffset * map.Hgt / 8) };
	Draw("Sky", sky);

//	var ground2 = { Algo = MAPALGO_SimplexNoise, Seed = (seed + 1), Ratio = 50, Octave = 8, Persistence = 5, Scale = 3, Wdt = 1, Hgt = 1 };
//	var result = { Algo = MAPALGO_And, Op = [ground2, ground] };
//	Draw("Earth-earth_spongy", result);
	return sky;
}

func draw_mat(int seed, string type, proplist area, int ratio, int octave, int scale) {
	var mat = { Algo = MAPALGO_SimplexNoise, Seed = seed+1, Ratio = ratio, Octave = octave, Persistence = 5, Scale = scale, Wdt = 1, Hgt = 1 };
	var result = { Algo = MAPALGO_And, Op = [mat, area] };
	Draw(type, result);
	return result;
}
