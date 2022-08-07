#pragma once

#include "../../Global.h"

#include <opencv2/opencv.hpp>

using namespace cv;

namespace mt2
{
	class OpenCVWrapper
	{
	public:
		SINGLETONIZE_INIT(OpenCVWrapper)

		virtual ~OpenCVWrapper();
	private:
		void init();
	};
}