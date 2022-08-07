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
	};
};