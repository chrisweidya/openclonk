#include Library_Map

func InitializeMap(proplist map)
{
	var bg = CreateLayer("Sky");
	var ground = { Algo = MAPALGO_Rect, X = 0, Y = bg.Hgt / 3, Wdt = bg.Wdt, Hgt = 2 * bg.Hgt / 3 };
	var smallTunnels = { Algo = MAPALGO_SimplexNoise, Seed = 123123, Ratio = 50, Octave = 10, Persistence = 5, Scale = 10, Wdt = 1, Hgt = 1 };
//	var largeTunnels = { Algo = MAPALGO_SimplexNoise, Seed = 123123, Ratio = 30, Octave = 3, Persistence = 1, Scale = 10, Wdt = 9, Hgt = 9 };
	var result = { Algo = MAPALGO_And, Op = [smallTunnels, ground] };
//	var checkerboard = { Algo = MAPALGO_SimplexNoise, Ratio = 70, Wdt = 1, Hgt = 1 };
//	var jumbled_checkerboard = { Algo = MAPALGO_Turbulence, Amplitude = 100, Scale = 100, Op = checkerboard };
	Draw("Earth", ground);
	Draw("Tunnel", result);
//	result = { Algo = MAPALGO_And, Op = [largeTunnels, ground] };
//	Draw("Tunnel", result);

	return true;
}