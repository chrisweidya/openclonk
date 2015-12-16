#include Library_Map

func InitializeMap(proplist map)
{
	var bg = CreateLayer("Sky");
	var ground = { Algo = MAPALGO_Rect, X = 0, Y = bg.Hgt / 3, Wdt = bg.Wdt, Hgt = 2 * bg.Hgt / 3 };
	var checkerboard = { Algo = MAPALGO_SimplexNoise, Ratio = 50, Octave = 3, Persistence = 1, Scale = 10, Wdt = 4, Hgt = 4 };
	var result = { Algo = MAPALGO_And, Op = [checkerboard, ground] };
//	var checkerboard = { Algo = MAPALGO_SimplexNoise, Ratio = 70, Wdt = 1, Hgt = 1 };
//	var jumbled_checkerboard = { Algo = MAPALGO_Turbulence, Amplitude = 100, Scale = 100, Op = checkerboard };
	Draw("Earth", ground);
	Draw("Tunnel", result);

	return true;
}