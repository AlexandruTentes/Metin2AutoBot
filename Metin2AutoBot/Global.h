#pragma once

#include "Include.h"
#include "Macro.h"

namespace mt2
{
	class Global
	{
	public:
		SINGLETONIZE(Global)
		char title[256] = "DEV";
		char map_title[256] = "MAP";
		char game_name[256] = "NOSTALGIA2";

		//Map
		float map_width = 0.175;
		float map_height = 0.225;
		float map_x = 0.825;
		float map_y = 0.02;

		//Colors
		int lower_map_metin_r1 = 140;
		int lower_map_metin_g1 = 40;
		int lower_map_metin_b1 = 0;
		int upper_map_metin_r1 = 170;
		int upper_map_metin_g1 = 63;
		int upper_map_metin_b1 = 5;
		
		int lower_map_metin_r2 = 200;
		int lower_map_metin_g2 = 50;
		int lower_map_metin_b2 = 0;
		int upper_map_metin_r2 = 255;
		int upper_map_metin_g2 = 93;
		int upper_map_metin_b2 = 5;

		int lower_map_player_r = 170;
		int lower_map_player_g = 170;
		int lower_map_player_b = 150;
		int upper_map_player_r = 255;
		int upper_map_player_g = 255;
		int upper_map_player_b = 200;
	};
};