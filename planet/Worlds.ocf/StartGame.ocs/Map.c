//Created by Chris
//Handles terrain creation, constructive PCG algorithm

#include Library_Map

local i_width;
local a_width;

func InitializeMap(proplist map)
{
	//Gets achievement and immersion portion of map
	var offset = GetMapDataFromPlayer();
	i_width = map.Wdt / 2 + map.Wdt*offset / 6;
	a_width = map.Wdt - i_width;

	//Gets random seed and player's progression on immersion and achievement
	var seed = GetRandomSeed();	
	var immersion_level = GetPlayerImmLevel();
	var achievement_level = GetPlayerAchLevel();

	//Draws tunnel, ground and sky
	var ground = draw_ground(seed, map);	
	var largeTunnels = draw_mat(seed, "Tunnel", ground, 48, 7, 3, 2);
	var skyLand = draw_sky(seed, map);

	//Creates resources depending on immersion progression
	if (immersion_level > 1) {
		draw_mat(seed + 1, "^Ore", skyLand, 30, 7, 2, 1);
		draw_mat(seed + 2, "^Coal", skyLand, 32, 8, 3, 1);
	}
	if (immersion_level > 0) {
		draw_mat(seed + 1, "^Rock", skyLand, 26, 6, 2, 1);		
	}

	//Creates hazard depending on achievement progression
	if (achievement_level > 0) {
		var fireStone = draw_mat(seed, "Firestone", ground, 28, 8, 2, 1);
	}
	
	//Draws sky and sand ground in sky
	var sky = draw_mat(seed, "Sky", skyLand, 48, 7, 3, 2);

	//Creates player platform and elevator navigation tunnels
	var platform = draw_platform(map);
	var underground_tunnel = draw_underground(map);

	Log("====== Map terrain generated, seed no: %v ======", seed);
	return true;
}

//Platform generation
func draw_platform(proplist map) {
	var platform = { Algo = MAPALGO_Rect, X = map.Wdt / 3, Y = map.Hgt / 2 , Wdt = map.Wdt / 3, Hgt = 3 };
	
	Draw("BrickSoft", platform);
}

//Creates earth terrain for achievement zone
func draw_ground(int seed, proplist map) {
	var ground = { Algo = MAPALGO_Rect, X = i_width, Y = 0, Wdt = a_width + 1, Hgt = map.Hgt};
	Draw("Earth", ground);

	var ground2 = { Algo = MAPALGO_SimplexNoise, Seed = (seed + 1), Ratio = 50, Octave = 8, Persistence = 5, Scale = 3, Wdt = 1, Hgt = 1 };
	var result = { Algo = MAPALGO_And, Op = [ground2, ground] };
	Draw("Earth-earth_spongy", result);
	return ground;
}

//Creates land in sky
func draw_sky(int seed, proplist map) {
	var skyLand = { Algo = MAPALGO_Rect, X = 0, Y = 0,
		Wdt = i_width, Hgt = map.Hgt};
	Draw("^Sand", skyLand);

	return skyLand;
}

//Generic function to create simplex noise generated terrain
//"string type" refers to material type, refer to openclonk map documentation for the available options
//"proplist area" is the area mask in the map to generate the terrain
//"int ratio" refers to the threshold percentage of filling the area given to simplex noise algo, higher value means the terrain is more dense
//"int octave, scale, width"  are simplex noise parameters that change the design of terrain pattern
func draw_mat(int seed, string type, proplist area, int ratio, int octave, int scale, int width) {
	var mat = { Algo = MAPALGO_SimplexNoise, Seed = seed+1, Ratio = ratio, Octave = octave, Persistence = 5, Scale = scale, Wdt = width, Hgt = 1 };
	var result = { Algo = MAPALGO_And, Op = [mat, area] };
	Draw(type, result);
	return result;
}

//Creates the tunnels at the bottom of map and for elevator
func draw_underground(proplist map) {
	var undersky = { Algo = MAPALGO_Rect, X = map.Wdt / 3, Y = map.Hgt - 4, Wdt = i_width - map.Wdt / 3, Hgt = 4 };
	Draw("Sky", undersky);
	var underground = { Algo = MAPALGO_Rect, X = i_width, Y = map.Hgt - 4, Wdt = a_width - map.Wdt / 3, Hgt = 4 };
	Draw("Tunnel", underground);
	var clearArea = { Algo = MAPALGO_Rect, X = map.Wdt / 3, Y = map.Hgt / 2 - 15, Wdt = map.Wdt / 3, Hgt = 15 };
	Draw("Sky", clearArea);
}