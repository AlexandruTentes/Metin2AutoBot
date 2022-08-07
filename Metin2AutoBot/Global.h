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
	};
};