#include Library_Map

func InitializeMap(proplist map)
{
	var seed = 123123;
	var bg = CreateLayer("Sky");
	var ground = draw_ground(seed, map);
	var coal = draw_mat(seed, "Coal", ground, 30, 5, 3);
	var fireStone = draw_mat(seed, "Firestone", ground, 30, 8, 2);
	var largeTunnels = draw_mat(seed, "Tunnel", ground, 50, 8, 3);

	return true;
}

func draw_ground(int seed, proplist map) {
	var ground = { Algo = MAPALGO_Rect, X = 0, Y = map.Hgt / 3, Wdt = map.Wdt, Hgt = 2 * map.Hgt / 3 };
	Draw("Earth", ground);

	var ground2 = { Algo = MAPALGO_SimplexNoise, Seed = (seed+1), Ratio = 50, Octave = 8, Persistence = 5, Scale = 3, Wdt = 1, Hgt = 1 };
	var result = { Algo = MAPALGO_And, Op = [ground2, ground] };
	Draw("Earth-earth_spongy", result);
	return ground;
}

func draw_mat(int seed, string type, proplist ground, int ratio, int octave, int scale) {
	var mat = { Algo = MAPALGO_SimplexNoise, Seed = seed, Ratio = ratio, Octave = octave, Persistence = 5, Scale = scale, Wdt = 1, Hgt = 1 };
	var result = { Algo = MAPALGO_And, Op = [mat, ground] };
	Draw(type, result);
	return result;
}
